//#############################################################################
//
// FILE:   lin_ex2_sci_loopback.c
//
// TITLE:   LIN SCI Mode Internal Loopback with Interrupts
//
//! \addtogroup driver_example_list
//! <h1> LIN SCI Mode Internal Loopback with Interrupts </h1>
//!
//!  This example configures the LIN module in SCI mode for internal loopback
//!  with interrupts. The LIN module performs as a SCI with a set character
//!  and frame length in a non-multi-buffer mode. The module is setup to 
//!  continuously transmit a character, wait to receive that character, and 
//!  repeat.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - rxCount - The number of RX interrupts
//!  - transmitChar - The character being transmitted
//!  - receivedChar - The character received
//!
//
//#############################################################################

//
// Included Files
//
#include "board.h"

//
// Defines
//
#define CHAR_LENGTH     8
#define FRAME_LENGTH    1

//
// Globals
//
volatile uint32_t rxCount = 0;
volatile uint32_t vectorOffset = 0;
volatile uint16_t error = 0;
uint16_t transmitChar = 0x0;
uint16_t receivedChar = 0x0;


//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

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
    // Continuously transmit an 8-bit character, wait for ISR to run, and 
    // verify everything was received correctly
    //
    for(;;)
    {
        vectorOffset = 0;

        //
        // Increment transmit character to new value
        //
        transmitChar++;

        //
        // Reset transmit character when larger than a byte
        //
        if(transmitChar > 0xFF)
        {
            transmitChar = 0;
        }

        //
        // Wait for the SCI receiver to be idle
        //
        while(!LIN_isSCIReceiverIdle(myLIN0_BASE));

        //
        // Transmit the byte of data
        //
        LIN_writeSCICharBlocking(myLIN0_BASE, transmitChar);

        //
        // Wait for ISR to trigger and read the transmitted character
        //
        while(vectorOffset != LIN_VECT_RX);

        //
        // Halt the example if any errors occurred
        //
        if(error != 0)
        {
            ESTOP0;
        }
    }
}

//
// Received Data ISR - An interrupt service routine (ISR) to handle when new
// data is received. Once received, the data is read and interrupt status 
// cleared.
//
void dataRxISR(void)
{
    //
    // Increment the interrupt count
    //
    rxCount++;

    //
    // Read the highest priority interrupt vector
    //
    vectorOffset = LIN_getInterruptLine0Offset(myLIN0_BASE);

    //
    // Read the transmitted character
    //
    receivedChar = LIN_readSCICharBlocking(myLIN0_BASE, false);

    //
    // Check that the received character matches the transmitted character
    //
    if(receivedChar != transmitChar)
    {
        error++;
    }

    //
    // Clear module interrupt flag and global interrupt flag for line 0
    //
    LIN_clearSCIInterruptStatus(myLIN0_BASE, LIN_SCI_INT_RX);
    LIN_clearGlobalInterruptStatus(myLIN0_BASE, LIN_INTERRUPT_LINE0);
}

//
// End of File
//
