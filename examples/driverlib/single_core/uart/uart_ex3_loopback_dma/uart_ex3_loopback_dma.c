//#############################################################################
//
// FILE:   uart_ex3_loopback_dma.c
//
// TITLE:  UART DMA Example
//
//! \addtogroup driver_example_list
//! <h1>UART Loopback with DMA</h1>
//!
//! This program uses the internal loopback test mode of the UART module. Both
//! DMA interrupts and UART FIFOs are used. When the UART transmit FIFO has
//! enough space (as indicated by its FIFO level interrupt signal), the DMA
//! will transfer data from global variable sData into the FIFO. This will be
//! transmitted to the receive FIFO via the internal loopback.
//!
//! When enough data has been placed in the receive FIFO (as indicated by its
//! FIFO level interrupt signal), the DMA will transfer the data from the FIFO
//! into global variable rData.
//!
//! When all data has been placed into rData, a check of the validity of the
//! data will be performed in one of the DMA channels' ISRs.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b sData - Data to send
//!  - \b rData - Received data
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
// Globals
//
volatile uint8_t sData[128];                // Send data buffer
volatile uint8_t rData[128];                // Receive data buffer

const void *destAddr = (const void *)rData;
const void *srcAddr = (const void *)sData;

volatile uint8_t done = 0;         // Flag to set when all data transferred

int main(void)
{
    uint8_t i;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Initialize the data buffers
    //
    for(i = 0; i < 128; i++)
    {
        sData[i] = i+1;
        rData[i]= 0;
    }

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start the DMA channels
    //
    DMA_startChannel(myUART0_TX_DMA_BASE);
    DMA_startChannel(myUART0_RX_DMA_BASE);

    //
    // Wait until the DMA transfer is complete
    //
    while(!done)
    {
        ;
    }

    //
    // When the DMA transfer is complete the program will stop here
    //
    ESTOP0;

}


//
// DMA Channel 5 ISR
//
void INT_myUART0_TX_DMA_ISR(void)
{
    DMA_stopChannel(myUART0_TX_DMA_BASE);
    return;
}


//
// DMA Channel 6 ISR
//
void INT_myUART0_RX_DMA_ISR(void)
{
    uint8_t i;

    //
    //  Wait for UART transmission to complete
    //
    while(UART_isBusy(myUART0_BASE)){
        ;
    }

    DMA_stopChannel(myUART0_RX_DMA_BASE);

    //
    // Check for data integrity
    //
    for(i = 0; i < 128; i++)
    {
        if (rData[i] != i+1)
        {
            // Something went wrong. rData doesn't contain expected data.
            ESTOP0;
        }
    }

    done = 1;
    return;
}

//
// End of File
//