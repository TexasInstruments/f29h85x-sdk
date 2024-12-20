//#############################################################################
//
// FILE:   clb_ex1_combinatorial_logic.c
//
// TITLE:  CLB Combinational Logic.
//
//! \addtogroup driver_example_list
//! <h1>CLB Combinational Logic</h1>
//!
//!
//! The objective of this example is to prevent simultaneous high or low outputs 
//! on a PWM pair. PWM modules 1 and 2 are configured to generate identical 
//! waveforms based on a fixed frequency up-count mode.
//!
//
//
//#############################################################################
// $TI Release: $
// $Release Date: $
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

#include "clb_config.h"
#include "board.h"

void initCLB1(void);

uint32_t mode = 0;


int main(void)
{
    Device_init();

	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);

    Board_init();

    initTILE1(myTILE1_BASE);

    CLB_setGPREG(myTILE1_BASE, mode);

    CLB_setOutputMask(myTILE1_BASE, 0x5, true);

    Interrupt_enable(INT_EPWM1);
    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    while(1)
    {
        __asm(" NOP #1");
    }
}


__attribute__((interrupt("INT"))) void INT_myEPWM1_ISR(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);
    CLB_setGPREG(myTILE1_BASE, mode & 3UL);
    __asm(" NOP #1");
}
