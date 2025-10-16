//###########################################################################
//
// FILE:   ram_sbl_dpl_config.c
//
// TITLE:  SBL DPL configuration that is based on ti_dpl_config.c
//         The only difference is the hard coded SSU LINK & STACK config depending on the device state
//         HS-FS: LINK1 & STACK1, HS-KP/SE: LINK2 & STACK2
//
//###########################################################################
// $TI Release:  $
// $Release Date:   $
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
//  Includes
//
#include "ram_sbl_dpl_config.h"

extern ClockP_Config gClockConfig;
extern void HsmClient_config(void);

//
// Same implementation as System_init, except for calls to KernelDpl_init() insstead.
//
void KernelSystem_init(void)
{
    /* DPL init sets up address transalation unit, on some CPUs this is needed
     * to access SCICLIENT services, hence this needs to happen first
     */
    KernelDpl_init();

    /* finally we initialize all peripheral drivers */
    HsmClient_config();
}

//
// Same implementation as Dpl_init, except for LINK & STACK selection
//
void KernelDpl_init(void)
{
    uint32_t ssuLink, ssuStack, deviceState;

    deviceState = getDeviceState();

    if (deviceState == HS_FS)
    {
        ssuLink = DPL_RAMOPEN_LINK;
        ssuStack = DPL_RAMOPEN_STACK;
    }
    else // HS-KP/HS-SE
    {
        ssuLink = DPL_NORMAL_LINK;
        ssuStack = DPL_NORMAL_STACK;
    }

    gClockConfig.timerHwiLinkOwner = ssuLink;

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
