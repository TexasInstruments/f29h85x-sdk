//#############################################################################
//
// FILE:   epwm_ex1_trip_zone.c
//
// TITLE:  ePWM Using Trip-Zone Submodule.
//
//! \addtogroup driver_example_list
//! <h1>ePWM Trip Zone</h1>
//!
//! This example configures ePWM1 and ePWM2 as follows
//!  - ePWM1 has TZ1 as one shot trip source
//!  - ePWM2 has TZ1 as cycle by cycle trip source
//!
//! Initially tie TZ1 high. During the test, monitor ePWM1 or ePWM2
//! outputs on a scope. Pull TZ1 low to see the effect.
//!
//!  \b External \b Connections \n
//!  - ePWM1A is on GPIO0
//!  - ePWM2A is on GPIO2
//!  - TZ1 is on GPIO12
//!
//! This example also makes use of the Input X-BAR. GPIO12 (the external
//! trigger) is routed to the input X-BAR, from which it is routed to TZ1.
//!
//! The TZ-Event is defined such that ePWM1A will undergo a One-Shot Trip
//! and ePWM2A will undergo a Cycle-By-Cycle Trip.
//!
//              _____________             __________________
//              |           |             |                |
//  GPIO12 -----| I/P X-BAR |-----TZ1-----| ePWM TZ Module |-----TZ-Event
//              |___________|             |________________|
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

//
// Globals
//
uint32_t  epwm1TZIntCount;
uint32_t  epwm2TZIntCount;

//
// Function Prototypes
//
__attribute__((interrupt("INT"))) void epwm1TZISR(void);
__attribute__((interrupt("INT"))) void epwm2TZISR(void);

int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Initialize global variables
    //
    epwm1TZIntCount = 0U;
    epwm2TZIntCount = 0U;


    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // Configure ePWM1, ePWM2, and TZ GPIOs/Modules
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

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
        __asm(" NOP #1");
    }
}

//
// epwm1TZISR - ePWM1 TZ ISR
//
void epwm1TZISR(void)
{
    epwm1TZIntCount++;

    //
    // To re-enable the OST Interrupt, uncomment the below code:
    //
    // EPWM_clearTripZoneFlag(EPWM1_BASE,
    //                        (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));
}

//
// epwm2TZISR - ePWM2 TZ ISR
//
void epwm2TZISR(void)
{
    epwm2TZIntCount++;

    //
    // Toggle GPIO to notify when TZ is entered
    //
    GPIO_togglePin(myGPIO11);

    //
    // Clear the flags - we will continue to take this interrupt until the TZ
    // pin goes high.
    //
    EPWM_clearTripZoneFlag(myEPWM2_BASE, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_CBC));
}

