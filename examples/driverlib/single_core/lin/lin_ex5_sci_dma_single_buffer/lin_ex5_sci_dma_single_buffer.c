//#############################################################################
//
// FILE:   lin_ex5_sci_dma_single_buffer.c
//
// TITLE:  LIN SCI MODE (SIngle Buffer) Internal Loopback with DMA
//
//! \addtogroup driver_example_list
//! <h1> LIN SCI MODE (Single Buffer) Internal Loopback with DMA </h1>
//!
//! This example configures the LIN module in SCI mode for internal loopback
//! with the use of the DMA. The LIN module performs as SCI with a set
//! character and frame length in single-buffer compatibility mode. When the
//! transmit buffer i.e. the SCITD register is free, the DMA will transfer
//! data from global variable sData into this register. Once the received
//! buffer, i.e. the SCIRD register contains data, the DMA will transfer the
//! data into the global variable rdata.
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
volatile uint8_t sData[128];
volatile uint8_t rData[128];
volatile uint16_t done = 0;         // Flag to set when all data transfered

const void *myLIN0_RX_DMA_ADDRESS = ((uint8_t *)(myLIN0_BASE + LIN_O_SCIRD));
const void *myLIN0_TX_DMA_ADDRESS = ((uint8_t *)(myLIN0_BASE + LIN_O_SCITD));

const void *destAddr = (const void *)rData;
const void *srcAddr = (const void *)sData;

//
// Main
//
int main(void)
{
    uint16_t i;

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
       sData[i]= i+1;
       rData[i]= 0;
    }

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Wait for the SCI receiver to be idle
    //
    while(!LIN_isSCIReceiverIdle(myLIN0_BASE));

    //
    // Wait until space is available in the transmit buffer.
    //
    while(!LIN_isSCISpaceAvailable(myLIN0_BASE)){
        ;
    }

    //
    // Start the DMA channels
    //
    DMA_startChannel(myLIN0_TX_DMA_BASE);
    DMA_startChannel(myLIN0_RX_DMA_BASE);

    //
    // Initiate transfer by forcing a TX DMA trigger.
    //
    DMA_forceTrigger(myLIN0_TX_DMA_BASE);


    //
    // Wait until the DMA transfer is complete
    //
    while(!done){
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
void dmaTxIsr(void)
{
    DMA_stopChannel(myLIN0_TX_DMA_BASE);
    return;
}

//
// DMA Channel 6 ISR
//
void dmaRxIsr(void)
{
    uint16_t i;
    DMA_stopChannel(myLIN0_RX_DMA_BASE);

    //
    //Check for data integrity
    //
    for(i=0; i<128; i++)
    {
        if(rData[i] != i+1)
        {
           //Something went wrong, rdata doesn't contain expected data.
           ESTOP0;
        }
    }

    done = 1;
    return;
}

//
// End of File
//