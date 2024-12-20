//#############################################################################
//
// FILE:   i2c_ex3_external_loopback.c
//
// TITLE:  I2C Digital External Loopback with FIFO Interrupts
//
//! \addtogroup driver_example_list
//! <h1>I2C Digital External Loopback with FIFO Interrupts</h1>
//!
//! This program uses the I2CA and I2CB modules for achieving external
//! loopback. The I2CA TX FIFO and the I2CB RX FIFO are used along with
//! their interrupts.
//!
//! A stream of data is sent on I2CA and then compared to the received stream
//! on I2CB.
//! The sent data looks like this: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  00FE 00FF \n
//!  00FF 0000 \n
//!  etc.. \n
//! This pattern is repeated forever.
//!
//! \b External \b Connections \n
//!   - Connect SCLA(DEVICE_GPIO_PIN_SCLA) to SCLB (DEVICE_GPIO_PIN_SCLB) 
//!   - and SDAA(DEVICE_GPIO_PIN_SDAA) to SDAB (DEVICE_GPIO_PIN_SDAB)
//!   - Connect DEVICE_GPIO_PIN_LED1 to an LED used to depict data transfers.
//!
//! \b Watch \b Variables \n
//!  - \b sData - Data to send
//!  - \b rData - Received data
//!  - \b rDataPoint - Used to keep track of the last position in the receive
//!    stream for error checking
//!
//
//#############################################################################
//
//
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//#############################################################################

//
// Included Files
//
#include "board.h"

//
// Defines
//

//
// Globals
//
uint8_t sData[2] = {0,0};                  // Send data buffer
uint8_t rData[2] = {0,0};                  // Receive data buffer
uint8_t rDataPoint = 0;                    // To keep track of where we are in the
                                            // data stream to check received data

//
// Function Prototypes
//
void INT_myI2C0_FIFO_ISR(void);
void INT_myI2C0_ISR(void);
void INT_myI2C1_FIFO_ISR(void);
void INT_myI2C1_ISR(void);
void I2CB_init(void);

//
// Main
//
int main(void)
{
    uint8_t i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();
    
    //
    //
    //
    Board_init();
    
    //
    // Initialize the data buffers
    //
    for(i = 0; i < 2; i++)
    {
        sData[i] = i;
        rData[i]= 0;
    }

  

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    while(1)
    {
     // A FIFO interrupt will be generated for each Tx and Rx based
     // on the Interrupt levels configured.
     // The ISR will handle pushing/pulling data to/from the TX and
     // RX FIFOs resp.
    }

}



//
// I2C A Transmit & Receive FIFO ISR.
//
void INT_myI2C0_FIFO_ISR(void)
{
    uint8_t i;

 
    //
    // If transmit FIFO interrupt flag is set, put data in the buffer
    //
    if((I2C_getInterruptStatus(myI2C0_BASE) & I2C_INT_TXFF) != 0)
    {
        for(i = 0; i < 2; i++)
        {
            I2C_putData(myI2C0_BASE, sData[i]);
        }

        //
        // Send the start condition
        //
        I2C_sendStartCondition(myI2C0_BASE);

        //
        // Increment data for next cycle
        //
        for(i = 0; i < 2; i++)
        {
           sData[i] = (sData[i] + 1);
        }

        //
        // Clear interrupt flag
        //
        I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_TXFF);
    }
}

//
// I2C B Transmit & Receive FIFO ISR.
//
void INT_myI2C1_FIFO_ISR(void)
{
    uint8_t i;

    //
    // If receive FIFO interrupt flag is set, read data
    //
    if((I2C_getInterruptStatus(myI2C1_BASE) & I2C_INT_RXFF) != 0)
    {
        for(i = 0; i < 2; i++)
        {
            rData[i] = I2C_getData(myI2C1_BASE);
        }

        //
        // Check received data
        //
        for(i = 0; i < 2; i++)
        {
            if(rData[i] != (uint8_t)(rDataPoint + i))
            {
                //
                // Something went wrong. rData doesn't contain expected data.
                //
                ESTOP0;
            }
        }

        //
        // Used to keep track of the last position in the receive
        // stream for error checking
        //
        rDataPoint = (rDataPoint + 1);

        //
        // Clear interrupt flag
        //
        I2C_clearInterruptStatus(myI2C1_BASE, I2C_INT_RXFF);
    }
}
// 
// Non FIFO ISR not used in loopback example
//
 void INT_myI2C0_ISR(void)
{
    //
    // Clear interrupt flag
    //
    I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_STOP_CONDITION);
}

// 
// Non FIFO ISR not used in loopback example
//
 void INT_myI2C1_ISR(void)
{
    //
    // Clear interrupt flag
    //
    I2C_clearInterruptStatus(myI2C1_BASE, I2C_INT_STOP_CONDITION);
}

void I2CB_init(){
	I2C_disableModule(myI2C1_BASE);
	I2C_initController(myI2C1_BASE, DEVICE_SYSCLK_FREQ, myI2C0_BITRATE, I2C_DUTYCYCLE_50);
	I2C_setConfig(myI2C1_BASE, I2C_TARGET_RECEIVE_MODE);
	I2C_disableLoopback(myI2C1_BASE);
	I2C_setOwnAddress(myI2C1_BASE, myI2C1_OWN_ADDRESS);
	I2C_setTargetAddress(myI2C1_BASE, myI2C1_TARGET_ADDRESS);
	I2C_setBitCount(myI2C1_BASE, I2C_BITCOUNT_8);
	I2C_setDataCount(myI2C1_BASE, 2);
	I2C_setAddressMode(myI2C1_BASE, I2C_ADDR_MODE_7BITS);
	I2C_disableExtendedAutomaticClkStretchingMode(myI2C1_BASE);
	I2C_enableFIFO(myI2C1_BASE);
	I2C_clearInterruptStatus(myI2C1_BASE, I2C_INT_STOP_CONDITION | I2C_INT_RXFF);
	I2C_setFIFOInterruptLevel(myI2C1_BASE, I2C_FIFO_TX2, I2C_FIFO_RX2);
	I2C_enableInterrupt(myI2C1_BASE, I2C_INT_STOP_CONDITION | I2C_INT_RXFF);
	I2C_setEmulationMode(myI2C1_BASE, I2C_EMULATION_FREE_RUN);
	I2C_enableModule(myI2C1_BASE);
}
//
// End of File
//

