//#############################################################################
//
// FILE:   dlt_ex1_datalog_variables.c
//
// TITLE:  Basic variable data log and read from FIFO
//
//! \addtogroup driver_example_list
//! <h1>DLT TAG filter example</h1>
//!
//! This example, configures the DLT to data log a single variable 
//! within a CPU Timer ISR and export out the DLT contents via FSI. 
//! The DMA is used to transfer the contents.
//! When the FIFO reaches a level of 4, the DMA is triggered to transfer contents to FSI TX buffer.
//!
//! DLT is setup using TAG filter and REGs in order to data log.
//!  - DLT configured for Time capture mode, tag filter enabled
//!  - In order to use the tag filter, compiler intrinsics are used:
//!  - __builtin_c29_datalog_tag for tag
//!  - __builtin_c29_datalog_write for reg
//!           
// +------+           +--------+                      
// |      |           |        |                      
// | DLT  |    DMA    | FSITXA |                      
// | FIFO +---------->|        +-+                    
// |      |           |        | |                    
// +------+           +--------+ |                    
//                               |                    
// +----------+       +--------+ |                    
// |          |  DMA  |        | |                    
// | INTERNAL |<------+ FSIRX  |<+                    
// | MEMORY   |       |        |                      
// +----------+       +--------+                      
//   
//                               
//
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
#include "inc/hw_dlt.h"
#include "inc/hw_memmap.h"
#define EXPECTED_CPUTIMER_ISR_COUNT     25

//
// Globals
//
uint32_t DLT_RTDMA_CH_ISR_Count = 0;
uint32_t DLT_RTDMA_FSITX_CH_ISR_Count = 0;
uint32_t CPUTIMER_ISR_Count = 0;
uint32_t LogVar = 0;
uint32_t DLTLoggingBuffer[500];
const void *txBufAddr;
const void *DLTLoggingBufferAddr = &DLTLoggingBuffer[0];
const void *cpu1_dlt_addr = (void *) CPU1DLTFIFO_BASE;

//
// Forward Declarations
//
void LoopCode(void);
void DLT_enableLinks(void);

//
// Main
//
int main(void)
{

    Device_init();

    for(int index = 0; index < 100; index++){
        DLTLoggingBuffer[index] = 0;
    }
    txBufAddr = (void *)FSI_getTxBufferAddress(myFSITX0_BASE);
    Interrupt_initModule();
    Interrupt_initVectorTable();
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUXDLT);

    Board_init();
    
    //
    // Reset DLT & Enable links
    //
    DLT_resetFIFO();
    DLT_resetFilter();
    DLT_enableLinks();

    //
    // FSI Configuration for initial flushing
    //
    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, 1);
    SysCtl_delay(1000000);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, 1);
    SysCtl_delay(1000000);

    // 
    // Enable global interrupts
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start DMA channels
    //
    DMA_startChannel(DLT_TO_FSITX_BASE);
    DMA_startChannel(myFSIRX0_RX_DMA_DATA_BASE);

    //
    // Start CPU Timer
    //
    CPUTimer_startTimer(myCPUTIMER0_BASE);

    //
    // Loop till CPU timer finish
    //
    LoopCode();

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {       

    }
}


void LoopCode(void) {
    __builtin_c29_datalog_tag(5);
    __builtin_c29_i16_dlreg_d(LogVar);
    LogVar++;
    while(CPUTIMER_ISR_Count != EXPECTED_CPUTIMER_ISR_COUNT){}
    __builtin_c29_datalog_tag(2);
}

//
// Interrupts
//
void INT_DLT_TO_FSITX_ISR(void)
{
    DLT_RTDMA_FSITX_CH_ISR_Count++;
}

void INT_FSIRX_TO_BUFFER_ISR(void)
{
    DLT_RTDMA_CH_ISR_Count++;
    DMA_configDestAddress(RTDMA2CH1_BASE , &(DLTLoggingBuffer[8*DLT_RTDMA_CH_ISR_Count]));

}

void INT_myCPUTIMER0_ISR(void)
{
    if(CPUTIMER_ISR_Count == EXPECTED_CPUTIMER_ISR_COUNT){
        CPUTimer_stopTimer(myCPUTIMER0_BASE);
    }
    __builtin_c29_datalog_tag(3);
    __builtin_c29_i16_dlreg_d(LogVar);
    CPUTIMER_ISR_Count++; 
    LogVar++;
}

void INT_myFSIRX0_1_ISR(void)
{
    FSI_clearTxEvents(myFSITX0_BASE, (FSI_TX_EVT_CLR_BUF_UNDERRUN | FSI_TX_EVT_CLR_BUF_OVERRUN));
}

void INT_myFSITX0_1_ISR(void)
{
    FSI_clearRxEvents(myFSIRX0_BASE, (FSI_RX_EVT_CLR_BUF_UNDERRUN | FSI_RX_EVT_CLR_BUF_OVERRUN));

}

void DLT_enableLinks(void)
{
    DLT_enableLinkPermission(SSU_LINK0);
    DLT_enableLinkPermission(SSU_LINK1);
    DLT_enableLinkPermission(SSU_LINK2);
    DLT_enableLinkPermission(SSU_LINK3);
    DLT_enableLinkPermission(SSU_LINK4);
    DLT_enableLinkPermission(SSU_LINK5);
    DLT_enableLinkPermission(SSU_LINK6);
    DLT_enableLinkPermission(SSU_LINK7);
    DLT_enableLinkPermission(SSU_LINK8);
    DLT_enableLinkPermission(SSU_LINK9);
    DLT_enableLinkPermission(SSU_LINK10);
    DLT_enableLinkPermission(SSU_LINK11);
    DLT_enableLinkPermission(SSU_LINK12);
    DLT_enableLinkPermission(SSU_LINK13);
    DLT_enableLinkPermission(SSU_LINK14);
    DLT_enableLinkPermission(SSU_LINK15);
}