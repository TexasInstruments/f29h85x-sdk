// #############################################################################
//
//  FILE:   i2c_ex2_eeprom.c
//
//  TITLE:  I2C EEPROM
//
//! \addtogroup driver_example_list
//! <h1>I2C EEPROM</h1>
//!
//! This program will write 1-14 words to EEPROM and read them back. The data
//! written and the EEPROM address written to are contained in the message
//! structure, i2cMsgOut. The data read back will be contained in the message
//! structure i2cMsgIn.
//!
//! \b External \b Connections \n
//!  - Connect external I2C EEPROM at address 0x50
//!  - Connect DEVICE_GPIO_PIN_SDAA on to external EEPROM SDA (serial data)
//!      pin
//!  - Connect DEVICE_GPIO_PIN_SCLA on to external EEPROM SCL (serial clock)
//!      pin
//!
//! \b Watch \b Variables \n
//!  - \b i2cMsgOut - Message containing data to write to EEPROM
//!  - \b i2cMsgIn - Message containing data read from EEPROM
//!
//
// #############################################################################
//
//
// $Copyright:
// #############################################################################

//
// Included Files
//
#include "board.h"

//
// Defines
//
#define TARGET_ADDRESS 0x50
#define EEPROM_HIGH_ADDR 0x00
#define EEPROM_LOW_ADDR 0x30
#define NUM_BYTES 8
#define MAX_BUFFER_SIZE 14 // Max is currently 14 because of
                           // 2 address bytes and the 16-byte
                           // FIFO

//
// I2C message states for I2CMsg struct
//
#define MSG_STATUS_INACTIVE 0x0000         // Message not in use, do not send
#define MSG_STATUS_SEND_WITHSTOP 0x0010    // Send message with stop bit
#define MSG_STATUS_WRITE_BUSY 0x0011       // Message sent, wait for stop
#define MSG_STATUS_SEND_NOSTOP 0x0020      // Send message without stop bit
#define MSG_STATUS_SEND_NOSTOP_BUSY 0x0021 // Message sent, wait for ARDY
#define MSG_STATUS_RESTART 0x0022          // Ready to become controller-receiver
#define MSG_STATUS_READ_BUSY 0x0023        // Wait for stop before reading data

//
// Error messages for read and write functions
//
#define ERROR_BUS_BUSY 0x1000
#define ERROR_STOP_NOT_READY 0x5555
#define SUCCESS 0x0000

//
// Typedefs
//
struct I2CMsg
{
    uint16_t msgStatus;                  // Word stating what state msg is in.
                                         // See MSG_STATUS_* defines above.
    uint16_t TargetAddr;                 // Target address tied to the message.
    uint16_t numBytes;                   // Number of valid bytes in message.
    uint16_t memoryHighAddr;             // EEPROM address of data associated
                                         // with message (high byte).
    uint16_t memoryLowAddr;              // EEPROM address of data associated
                                         // with message (low byte).
    uint16_t msgBuffer[MAX_BUFFER_SIZE]; // Array holding message data.
};

//
// Globals
//
struct I2CMsg i2cMsgOut = {MSG_STATUS_SEND_WITHSTOP,
                           TARGET_ADDRESS,
                           NUM_BYTES,
                           EEPROM_HIGH_ADDR,
                           EEPROM_LOW_ADDR,
                           0x01, // Message bytes
                           0x23,
                           0x45,
                           0x67,
                           0x89,
                           0xAB,
                           0xCD,
                           0xEF};
struct I2CMsg i2cMsgIn = {MSG_STATUS_SEND_NOSTOP,
                          TARGET_ADDRESS,
                          NUM_BYTES,
                          EEPROM_HIGH_ADDR,
                          EEPROM_LOW_ADDR};

struct I2CMsg *currentMsgPtr; // Used in interrupt

uint16_t passCount = 0;
uint16_t failCount = 0;

//
// Function Prototypes
//
uint16_t readData(struct I2CMsg *msg);
uint16_t writeData(struct I2CMsg *msg);

void fail(void);
void pass(void);

void INT_myI2C0_ISR(void);
void INT_myI2C0_FIFO_ISR(void);

//
// Main
//
int main(void)
{
    uint16_t error;
    uint16_t i;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Clear incoming message buffer
    //
    for (i = 0; i < MAX_BUFFER_SIZE; i++)
    {
        i2cMsgIn.msgBuffer[i] = 0x0000;
    }

    //
    // Set message pointer used in interrupt to point to outgoing message
    //
    currentMsgPtr = &i2cMsgOut;

    //
    // Board initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //

    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop indefinitely
    //
    while (1)
    {
        //
        // **** Write data to EEPROM section ****
        //
        // Check the outgoing message to see if it should be sent. In this
        // example it is initialized to send with a stop bit.
        //
        if (i2cMsgOut.msgStatus == MSG_STATUS_SEND_WITHSTOP)
        {
            //
            // Send the data to the EEPROM
            //
            error = writeData(&i2cMsgOut);

            //
            // If communication is correctly initiated, set msg status to busy
            // and update currentMsgPtr for the interrupt service routine.
            // Otherwise, do nothing and try again next loop. Once message is
            // initiated, the I2C interrupts will handle the rest. See the
            // function INT_myI2C0_ISR().
            //
            if (error == SUCCESS)
            {
                currentMsgPtr = &i2cMsgOut;
                i2cMsgOut.msgStatus = MSG_STATUS_WRITE_BUSY;
            }
        }

        //
        // **** Read data from EEPROM section ****
        //
        // Check outgoing message status. Bypass read section if status is
        // not inactive.
        //
        if (i2cMsgOut.msgStatus == MSG_STATUS_INACTIVE)
        {
            //
            // Check incoming message status
            //
            if (i2cMsgIn.msgStatus == MSG_STATUS_SEND_NOSTOP)
            {
                //
                // Send EEPROM address setup
                //
                while (readData(&i2cMsgIn) != SUCCESS)
                {
                    //
                    // Maybe setup an attempt counter to break an infinite
                    // while loop. The EEPROM will send back a NACK while it is
                    // performing a write operation. Even though the write
                    // is complete at this point, the EEPROM could still be
                    // busy programming the data. Therefore, multiple
                    // attempts are necessary.
                    //
                }

                //
                // Update current message pointer and message status
                //
                currentMsgPtr = &i2cMsgIn;
                i2cMsgIn.msgStatus = MSG_STATUS_SEND_NOSTOP_BUSY;
            }

            //
            // Once message has progressed past setting up the internal address
            // of the EEPROM, send a restart to read the data bytes from the
            // EEPROM. Complete the communique with a stop bit. msgStatus is
            // updated in the interrupt service routine.
            //
            else if (i2cMsgIn.msgStatus == MSG_STATUS_RESTART)
            {
                //
                // Read data portion
                //
                while (readData(&i2cMsgIn) != SUCCESS)
                {
                    //
                    // Maybe setup an attempt counter to break an infinite
                    // while loop.
                    //
                }

                //
                // Update current message pointer and message status
                //
                currentMsgPtr = &i2cMsgIn;
                i2cMsgIn.msgStatus = MSG_STATUS_READ_BUSY;
            }
        }
    }
}

//
// Function to send the data that is to be written to the EEPROM
//
uint16_t writeData(struct I2CMsg *msg)
{
    uint16_t i;

    //
    // Wait until the STP bit is cleared from any previous controller
    // communication. Clearing of this bit by the module is delayed until after
    // the SCD bit is set. If this bit is not checked prior to initiating a new
    // message, the I2C could get confused.
    //
    if (I2C_getStopConditionStatus(myI2C0_BASE))
    {
        return (ERROR_STOP_NOT_READY);
    }

    //
    // Setup target address
    //
    I2C_setTargetAddress(myI2C0_BASE, TARGET_ADDRESS);

    //
    // Check if bus busy
    //
    if (I2C_isBusBusy(myI2C0_BASE))
    {
        return (ERROR_BUS_BUSY);
    }

    //
    // Setup number of bytes to send msgBuffer and address
    //
    I2C_setDataCount(myI2C0_BASE, (msg->numBytes + 2));

    //
    // Setup data to send
    //
    I2C_putData(myI2C0_BASE, msg->memoryHighAddr);
    I2C_putData(myI2C0_BASE, msg->memoryLowAddr);

    for (i = 0; i < msg->numBytes; i++)
    {
        I2C_putData(myI2C0_BASE, msg->msgBuffer[i]);
    }

    //
    // Send start as controller transmitter
    //
    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_sendStartCondition(myI2C0_BASE);
    I2C_sendStopCondition(myI2C0_BASE);

    return (SUCCESS);
}

//
// Function to prepare for the data that is to be read from the EEPROM
//
uint16_t readData(struct I2CMsg *msg)
{
    //
    // Wait until the STP bit is cleared from any previous controller
    // communication. Clearing of this bit by the module is delayed until after
    // the SCD bit is set. If this bit is not checked prior to initiating a new
    // message, the I2C could get confused.
    //
    if (I2C_getStopConditionStatus(myI2C0_BASE))
    {
        return (ERROR_STOP_NOT_READY);
    }

    //
    // Setup target address
    //
    I2C_setTargetAddress(myI2C0_BASE, TARGET_ADDRESS);

    //
    // If we are in the the address setup phase, send the address without a
    // stop condition.
    //
    if (msg->msgStatus == MSG_STATUS_SEND_NOSTOP)
    {
        //
        // Check if bus busy
        //
        if (I2C_isBusBusy(myI2C0_BASE))
        {
            return (ERROR_BUS_BUSY);
        }

        //
        // Send data to setup EEPROM address
        //
        I2C_setDataCount(myI2C0_BASE, 2);
        I2C_putData(myI2C0_BASE, msg->memoryHighAddr);
        I2C_putData(myI2C0_BASE, msg->memoryLowAddr);
        I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
        I2C_sendStartCondition(myI2C0_BASE);
    }
    else if (msg->msgStatus == MSG_STATUS_RESTART)
    {
        //
        // Address setup phase has completed. Now setup how many bytes expected
        // and send restart as controller-receiver.
        //
        I2C_setDataCount(myI2C0_BASE, (msg->numBytes));
        I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_RECEIVE_MODE);
        I2C_sendStartCondition(myI2C0_BASE);
        I2C_sendStopCondition(myI2C0_BASE);
    }

    return (SUCCESS);
}

//
// I2C A ISR (non-FIFO)
//
void INT_myI2C0_ISR(void)
{
    I2C_InterruptSource intSource;
    uint16_t i;

    //
    // Read interrupt source
    //
    intSource = I2C_getInterruptSource(myI2C0_BASE);

    //
    // Interrupt source = stop condition detected
    //
    if (intSource == I2C_INTSRC_STOP_CONDITION)
    {
        //
        // If completed message was writing data, reset msg to inactive state
        //
        if (currentMsgPtr->msgStatus == MSG_STATUS_WRITE_BUSY)
        {
            currentMsgPtr->msgStatus = MSG_STATUS_INACTIVE;
        }
        else
        {
            //
            // If a message receives a NACK during the address setup portion of
            // the EEPROM read, the code further below included in the register
            // access ready interrupt source code will generate a stop
            // condition. After the stop condition is received (here), set the
            // message status to try again. User may want to limit the number
            // of retries before generating an error.
            //
            if (currentMsgPtr->msgStatus == MSG_STATUS_SEND_NOSTOP_BUSY)
            {
                currentMsgPtr->msgStatus = MSG_STATUS_SEND_NOSTOP;
            }
            //
            // If completed message was reading EEPROM data, reset message to
            // inactive state and read data from FIFO.
            //
            else if (currentMsgPtr->msgStatus == MSG_STATUS_READ_BUSY)
            {
                currentMsgPtr->msgStatus = MSG_STATUS_INACTIVE;
                for (i = 0; i < NUM_BYTES; i++)
                {
                    currentMsgPtr->msgBuffer[i] = I2C_getData(myI2C0_BASE);
                }

                //
                // Check received data
                //
                for (i = 0; i < NUM_BYTES; i++)
                {
                    if (i2cMsgIn.msgBuffer[i] == i2cMsgOut.msgBuffer[i])
                    {
                        passCount++;
                    }
                    else
                    {
                        failCount++;
                    }
                }

                if (passCount == NUM_BYTES)
                {
                    pass();
                }
                else
                {
                    fail();
                }
            }
        }
    }
    //
    // Interrupt source = Register Access Ready
    //
    // This interrupt is used to determine when the EEPROM address setup
    // portion of the read data communication is complete. Since no stop bit
    // is commanded, this flag tells us when the message has been sent
    // instead of the SCD flag.
    //
    else if (intSource == I2C_INTSRC_REG_ACCESS_RDY)
    {
        //
        // If a NACK is received, clear the NACK bit and command a stop.
        // Otherwise, move on to the read data portion of the communication.
        //
        if ((I2C_getStatus(myI2C0_BASE) & I2C_STS_NO_ACK) != 0)
        {
            I2C_sendStopCondition(myI2C0_BASE);
            I2C_clearStatus(myI2C0_BASE, I2C_STS_NO_ACK);
        }
        else if (currentMsgPtr->msgStatus == MSG_STATUS_SEND_NOSTOP_BUSY)
        {
            currentMsgPtr->msgStatus = MSG_STATUS_RESTART;
        }
    }
    else
    {
        //
        // Generate some error from invalid interrupt source
        //
        ESTOP0;
    }
}

void INT_myI2C0_FIFO_ISR(void)
{
    ESTOP0;
}

//
// Function to be called if data written matches data read
//
void pass(void)
{
    ESTOP0;
}

//
// Function to be called if data written does NOT match data read
//
void fail(void)
{
    ESTOP0;
}
