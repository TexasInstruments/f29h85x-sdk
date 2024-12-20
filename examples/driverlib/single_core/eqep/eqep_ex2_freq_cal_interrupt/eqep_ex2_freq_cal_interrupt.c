//#############################################################################
//
// FILE:   eqep_ex4_freq_cal_interrupt.c
//
// TITLE:  Frequency Measurement Using eQEP via unit timeout interrupt
//
//! \addtogroup driver_example_list
//! <h1>Frequency Measurement Using eQEP via unit timeout interrupt</h1>
//!
//! This example will calculate the frequency of an input signal using the
//! eQEP module.  ePWM1A is configured to generate this input signal with a
//! frequency of 5 kHz. EQEP unit timeout is set which will generate
//! an interrupt every \b UNIT_PERIOD microseconds and frequency calculation
//! occurs continuously
//!
//! The configuration for this example is as follows
//! - PWM frequency is specified as 5000Hz
//! - UNIT_PERIOD is specified as 10000 us
//! - Min frequency is (1/(2*10ms)) i.e 50Hz
//! - Highest frequency can be (2^32)/ ((2*10ms))
//! - Resolution of frequency measurement is 50hz
//!
//! \b freq : Frequency Measurement is obtained by counting the
//! external input pulses for UNIT_PERIOD (unit timer set to 10 ms).
//!
//! \b External \b Connections \n
//! - Connect GPIO20/eQEP1A to GPIO0/ePWM1A
//!
//! \b Watch \b Variables \n
//! - \b freq - Frequency measurement using position counter/unit
//!   time out
//! - \b pass - If measured frequency matches with PWM frequency
//!             then pass = 1 else 0
//!
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
#define TB_CLK    DEVICE_SYSCLK_FREQ / 2        // ePWM Time base clock is SYSCLK/2
#define PWM_CLK   5000U                      // PWM frequency as 5 kHz
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Calculate value period value
                                            // for up-down count mode
#define UNIT_PERIOD  10000U // Specify the unit timeout period in
                            // microseconds
//
// Globals
//
uint32_t oldcount = 0;  // stores the previous position counter value
int32_t freq = 0;      // measured frequency using eQEP
uint32_t count = 0;     // just to make sure measured frequency gets saturated
uint32_t pass = 0, fail = 0; // test pass or fail indicator

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
    // Board Initialization
    // - Setup eQEP1, configuring the unit timer and quadrature capture units
    // - Initialize GPIOs for EQEP1A
    // - Interrupts that are used in this example are re-mapped to ISR functions
    //   found within this file.
    // - Enable interrupts required for this example
    //

    //
    // Setup ePWM1 to generate a 5 kHz signal to be an input to the eQEP
    //

    //
    // Disable the ePWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Board_init();

    //
    // Sync the ePWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop indefinitely
    //
    while(1)
    {
        ;
    }
}

//
// eqep11 ISR- interrupts once per ePWM period
//
__attribute__((interrupt("INT")))
void INT_myEQEP0_ISR(void)
{

    uint32_t temp =0, newcount = 0 ;
    
    count++;  // increment count value so to wait for frequency saturation

    newcount = EQEP_getPositionLatch(myEQEP0_BASE); // new position counter value
    temp = newcount;

    //
    // Calculates the number of position counts in unit time
    //
    if (newcount >= oldcount)
        newcount = newcount - oldcount;
    else
        newcount = (0xFFFFFFFF - oldcount) + newcount;

    //
    // Stores the current position count value to oldcount variable
    //
    oldcount = temp;

    //
    // Frequency calculation equation i.e
    // freq = ((position counts) * 1000000 )/ (2 * Unit_time (in microseconds))
    //
    freq = (newcount * (uint32_t)1000000U)/(2 * (uint32_t)UNIT_PERIOD);

    //
    // Compares the measured frequency with input frequency
    //
    if (count >= 2){
        if (((freq - PWM_CLK) < 50) && ((freq - PWM_CLK) > -50)){
            pass = 1; fail = 0;
        }
        else {
            fail = 1; pass = 0;
        }
    }

    //
    // Clears the interrupt flag
    //
    EQEP_clearInterruptStatus(myEQEP0_BASE,EQEP_INT_UNIT_TIME_OUT|EQEP_INT_GLOBAL);
}

//
// End of File
//

