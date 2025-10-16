//###########################################################################
//
// FILE:    flash_based_sbl_dpl.c
//
// TITLE:   SBL DPL init
// <h1> Custom SBL DPL configuration based on ti_dpl_config.c but retains interrupt settings. </h1>
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
// Includes
//
#include "flash_based_sbl_dpl.h"

extern void HsmClient_config(void);

//
// Same implementation as System_Init, except calls KernelDpl_init() instead
//
void KernelSystem_init(void) 
{
    KernelDpl_init();

    //
    // Initialize HSMClient for proper SIPC communication and HSM interactions
    //
    HsmClient_config();

}

//
// Same implementation as Dpl_init, except for 
// retention if interrupts (INTERRUPT_init()).
//
void KernelDpl_init(void)
{
    uint32_t ssuLink, ssuStack;


    ssuLink = SSU_LINK2;
    ssuStack = SSU_LINK2;

    /* initialize Hwi but keep interrupts disabled */
    HwiP_init();

    INTERRUPT_init(); // Retain existing Interrupt settings

    /* initialize Clock */
    ClockP_init();

    /* Enable interrupt handling */
    HwiP_enable();

    /* Enable interrupts within CPU */
    __builtin_c29_enable_INT();

    /* Interrupt stack pointer */
    HwiP_setINTSP(ssuStack);

    /* Cycle counter init */
    CycleCounterP_init(DEVICE_SYSCLK_FREQ);

    /* CPU Timer2 clock source and divider configuration */
    SysCtl_setCputimer2Clock(SYSCTL_TIMER2CLK_SOURCE_SYSCLK, SYSCTL_TIMER2CLK_DIV_1);
}