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

//###########################################################################

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
