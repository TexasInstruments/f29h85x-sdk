//#############################################################################
//
// FILE:   dlt_ex1_datalog_erad.c
//
// TITLE:  Basic variable data log using ERAD and read from FIFO
//
//! \addtogroup driver_example_list
//! <h1>DLT ERAD filter example</h1>
//!
//! This example configures DLT and datalogs four variables MultVar, 
//! Current, Speed, Voltage throughout code execution.
//! The DLT contents are read from the DLTFIFO via CPU and transferred
//! to internal memory.
//!  - DLT configured for Time capture mode, ERAD filter enabled
//!  - In order to use the ERAD filter, ERAD is configured in SysCfg:
//!           
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
#include "bitfield_structs.h"

//
// Globals: Variables to be datalogged
//
uint32_t MultVar = 1;
uint32_t Current = 0;
uint32_t Speed = 0;
uint32_t Voltage = 0;
uint32_t InternalBuffer[18];

//
// Start and end address of the function delayFunction.
// This value comes from the linker command file.
//
extern uint32_t func1Start, func1End, 
                func2Start, func2End,
                func3Start, func3End;

void *addr_func1Start = (void *)&func1Start;
void *addr_func1End   = (void *)((uint32_t)&func1End - 2);
void *addr_func2Start = (void *)&func2Start;
void *addr_func2End   = (void *)((uint32_t)&func2End - 2);
void *addr_func3Start = (void *)&func3Start;
void *addr_func3End   = (void *)((uint32_t)&func3End - 2);

//
// Function Prototypes
//
__attribute__ ((section(".func1"), noinline)) void func1(void);
__attribute__ ((section(".func2"), noinline)) void func2(void);
__attribute__ ((section(".func3"), noinline)) void func3(void);
void DLT_enableLinks(void);

int main(void)
{
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Initialize global variables
    //
    for(int i = 0; i < 18; i++){
        InternalBuffer[i] = 0;
    }

    //
    // Configure ePWM1, ePWM2, and TZ GPIOs/Modules
    //
    Board_init();

    // Enable All Links
    DLT_enableLinks();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        int index = 0;
        func1();
        func2();
        func3();
        while(DLT_getFIFOWordStatus())
        {
            InternalBuffer[index] = CPU1DLTFifoRegs.FIFO_BUF_L;
            index++;
            InternalBuffer[index] = CPU1DLTFifoRegs.FIFO_BUF_H;
            index++;
        }
    }
}

//
// func1 starts DLT 
//
void func1(void)
{
    // Start address of func1 starts DLT.
    // Content is enabled for writing to DLT FIFO
    uint16_t i=0;
    for (; i<50; i++)
    {
        NOP;
        NOP;
        NOP;
        NOP;
    }

}

void func2(void) 
{
    __builtin_c29_datalog_tag(0x05);
    MultVar *= 2;
    Current += 100;
    // DLREG instrinsic used to 
    // record contents in variables
    __builtin_c29_datalog_write(MultVar);
    __builtin_c29_datalog_write(Current);
}

//
// end address of func3 stops DLT 
//

void func3(void) 
{
    // Tag to denote start of new function
    __builtin_c29_datalog_tag(0x04);
    Speed += 40;
    Voltage++;
    // DLREG instrinsic used to 
    // record contents in variables
    __builtin_c29_datalog_write(Speed);
    __builtin_c29_datalog_write(Voltage);
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