//#############################################################################
//
// FILE:    ecap_capture_pwm.c
//
// TITLE:   Capture ePWM3.
//
//! \addtogroup driver_example_list
//! <h1>eCAP Capture PWM Example</h1>
//!
//! This example configures ePWM3A for:
//! - Up count mode
//! - Period starts at 500 and goes up to 8000
//! - Toggle output on PRD
//!
//! eCAP1 is configured to capture the time between rising
//! and falling edge of the ePWM3A output.
//!
//! \b External \b Connections \n
//! - eCAP1 is on GPIO16
//! - ePWM1A is on GPIO4
//! - Connect GPIO4 to GPIO16.
//!
//! \b Watch \b Variables \n
//! - \b ecap1PassCount - Successful captures.
//! - \b ecap1IntCount - Interrupt counts.
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
// Defines
//
#define PWM3_TIMER_MIN     500U
#define PWM3_TIMER_MAX     8000U
#define EPWM_TIMER_UP      1U
#define EPWM_TIMER_DOWN    0U

//
// Globals
//
uint32_t ecap1IntCount;
uint32_t ecap1PassCount;
uint32_t epwm3TimerDirection;
volatile uint16_t cap2Count;
volatile uint16_t cap3Count;
volatile uint16_t cap4Count;
volatile uint16_t epwm3PeriodCount;

//
// Function Prototypes
//
void error(void);
void initECAP(void);
void initEPWM(void);
__attribute__((interrupt("INT"))) void INT_myECAP0_ISR(void);
//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    // Configure GPIO 16 as eCAP input
    // Enable interrupts required for this example
    //

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Board initialization
    // Configure GPIO 16 as eCAP input
    // Enable interrupts required for this example
    //
    
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    epwm3TimerDirection = EPWM_TIMER_UP;

    //
    // Initialize counters:
    //
    cap2Count = 0U;
    cap3Count = 0U;
    cap4Count = 0U;
    ecap1IntCount = 0U;
    ecap1PassCount = 0U;
    epwm3PeriodCount = 0U;

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    for(;;)
    {
        __asm(" NOP #1");
    }
}

//
// myECAP0 ISR
//
void INT_myECAP0_ISR(void)
{
    //
    // Get the capture counts. Each capture should be 4x the ePWM count
    // because of the ePWM clock divider.
    //
    cap2Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2);
    cap3Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3);
    cap4Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_4);

    //
    // Compare the period value with the captured count
    //
    epwm3PeriodCount = EPWM_getTimeBasePeriod(EPWM3_BASE);

    if(cap2Count > ((epwm3PeriodCount *4) + 4) ||
       cap2Count < ((epwm3PeriodCount *4) - 4))
    {
        error();
    }

    if(cap3Count > ((epwm3PeriodCount *4) + 4) ||
       cap3Count < ((epwm3PeriodCount *4) - 4))
    {
        error();
    }

    if(cap4Count > ((epwm3PeriodCount *4) + 4) ||
       cap4Count < ((epwm3PeriodCount *4) - 4))
    {
        error();
    }

    ecap1IntCount++;

    //
    // Keep track of the ePWM direction and adjust period accordingly to
    // generate a variable frequency PWM.
    //
    if(epwm3TimerDirection == EPWM_TIMER_UP)
    {
        if(epwm3PeriodCount < PWM3_TIMER_MAX)
        {
           EPWM_setTimeBasePeriod(EPWM3_BASE, ++epwm3PeriodCount);
        }
        else
        {
           epwm3TimerDirection = EPWM_TIMER_DOWN;
           EPWM_setTimeBasePeriod(EPWM3_BASE, ++epwm3PeriodCount);
        }
    }
    else
    {
        if(epwm3PeriodCount > PWM3_TIMER_MIN)
        {
            EPWM_setTimeBasePeriod(EPWM3_BASE, --epwm3PeriodCount);
        }
        else
        {
           epwm3TimerDirection = EPWM_TIMER_UP;
           EPWM_setTimeBasePeriod(EPWM3_BASE, ++epwm3PeriodCount);
        }
    }

    //
    // Count correct captures
    //
    ecap1PassCount++;

    //
    // Clear interrupt flags for more interrupts.
    //
    ECAP_clearInterrupt(myECAP0_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(myECAP0_BASE);

    //
    // Start eCAP
    //
    ECAP_reArm(myECAP0_BASE);

}

//
// error - Error function
//
void error()
{
    ESTOP0;
}
