//#############################################################################
//
// FILE:   rtdma_ex1_mem_transfer.c
//
// TITLE:  RTDMA example
//
//! \addtogroup driver_example_list
//! <h1> RTDMA Transfer </h1>
//!
//!  This example uses one RTDMA channel to transfer data from a buffer to
//!  another buffer in RAM. The example triggers the DMA channel repeatedly
//!  until the transfer of 16 bursts (where each burst is 4 8-bit words)
//!  has been completed. When the whole transfer is complete it will trigger
//!  the DMA interrupt. The RTDMA1 MPU is disabled in this example.
//!
//!  \b Watch \b Variables \n
//!  - \b TxData - Data to send
//!  - \b RxData - Received data
//!  - \b done - Transfer successful
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
uint32_t TxData[16];   // Send data buffer
uint32_t RxData[16];   // Receive data buffer
volatile uint16_t done;

const void *destAddr = (const void *)RxData;
const void *srcAddr = (const void *)TxData;

//
// Function Prototypes
//
void error();

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
    // Board Initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // User specific code
    // Initialize the data buffers
    //
    for(i = 0; i < 16; i++)
    {
        TxData[i] = i;
        RxData[i] = 0;
    }

    // Start DMA channel
    DMA_startChannel(myRTDMA1Ch0_BASE);

    done = 0;           // Test is not done yet

    while(!done)        // wait until the DMA transfer is complete
    {
        DMA_forceTrigger(myRTDMA1Ch0_BASE);
        SysCtl_delay(10);
    }

    //
    // When the DMA transfer is complete the program will stop here
    //
    ESTOP0;
}

//
// error - Error Function which will halt the debugger
//
void error(void)
{
    ESTOP0;  //Test failed!! Stop!
    for (;;);
}

//
// DMA Channel ISR
//
void INT_myRTDMA1Ch0_ISR(void)
{
    uint16_t i;

    DMA_stopChannel(myRTDMA1Ch0_BASE);

    for( i = 0; i < 16; i++ )
    {
        //
        // check for data integrity
        //
        if (RxData[i] != i)
        {
            error();
        }
    }

    done = 1; // Test done.
    return;
}
