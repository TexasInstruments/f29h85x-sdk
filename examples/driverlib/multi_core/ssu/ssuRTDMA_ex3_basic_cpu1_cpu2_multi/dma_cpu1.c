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
#include "app_cpu1.h"

//
// Globals
//
__attribute__((location(0x20144000))) volatile uint32_t TxData[16]; // Transmit data buffer

const void *srcAddr = (const void *)TxData;

__attribute__((location(0x20146000))) volatile uint32_t RxData2[16]; // Receive data buffer

volatile uint16_t done2;

const void *destAddr2 = (const void *)RxData2;
const void *srcAddr2 = (const void *)0x20143000;

//
// Function Prototypes
//
void error();

//
// Main
//
void dmaTask_cpu1(void) __attribute__((c29_protected_call))
{
    int i;

    //
    // Initialize the data buffers
    //
    for(i = 0; i < 16; i++)
    {
        TxData[i] = i;
    }

    DMA_startChannel(myRTDMA1Ch0_BASE);

    while(!done2)
    {
        DMA_forceTrigger(myRTDMA1Ch0_BASE);
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
void INT_myRTDMA1Ch0_ISR(void)
{
    uint16_t i;

    DMA_stopChannel(myRTDMA1Ch0_BASE);

    for(i = 0; i < 16; i++)
    {
        //
        // check for data integrity
        //
        if (RxData2[i] != i)
        {
            error();
        }
    }

    done2 = 1; // Test done.
    return;
}