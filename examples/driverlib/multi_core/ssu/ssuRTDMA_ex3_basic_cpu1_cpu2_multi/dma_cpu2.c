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
#include "app_cpu2.h"

//
// Globals
//
__attribute__((location(0x20145000))) volatile uint32_t RxData[16]; // Receive data buffer

volatile uint16_t done;

const void *destAddr = (const void *)RxData;
const void *srcAddr = (const void *)0x20144000;

__attribute__((location(0x20143000))) volatile uint32_t TxData2[16]; // Transmit data buffer

const void *srcAddr2 = (const void *)TxData2;


//
// Function Prototypes
//
void error();

//
// Main
//
void dmaTask_cpu2(void) __attribute__((c29_protected_call))
{
    int i;

    //
    // Initialize the data buffers
    //
    for(i = 0; i < 16; i++)
    {
        TxData2[i] = i;
    }

    DMA_startChannel(myRTDMA2Ch0_BASE);

    while(!done)
    {
        DMA_forceTrigger(myRTDMA2Ch0_BASE);
        SysCtl_delay(10);
    }

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
void INT_myRTDMA2Ch0_ISR(void)
{
    uint16_t i;

    DMA_stopChannel(myRTDMA2Ch0_BASE);

    for(i = 0; i < 16; i++)
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