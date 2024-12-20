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

#define ENCODER_SLOTS   1000U           // LVSERVOMTR is a 1000-line encoder
#define UNIT_PERIOD     10000U          // Unit period in microseconds
//
// Globals
//
uint32_t oldCount = 0;                  // stores the previous position counter value
uint32_t newCount = 0;                  // stores the new position counter value for frequency calculation
uint32_t currentEncoderPosition = 0;    // stores the current encoder position
int32_t frequency = 0;                  // measured quadrature signal frequency of motor using eQEP
float32_t speed = 0.0f;                 // measured speed of motor in rpm
int32_t direction = 0;                  // direction of rotation of motor

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
        //
        // myGPIOIndex pulses high for every 1000 encoder cycles (400us (2.5kHz) * 1000 = 400,000 us)
        //
        DEVICE_DELAY_US(400000L);
        GPIO_writePin(myGPIOIndex, 1);
        DEVICE_DELAY_US(200L);
        GPIO_writePin(myGPIOIndex, 0);
    }
}

//
// eqep11 ISR- interrupts once per ePWM period
//
void INT_myEQEP1_ISR(void)
{

    //
    // Save current encoder position value for monitoring
    //
    currentEncoderPosition = EQEP_getPosition(myEQEP1_BASE);
    //
    // Get position counter value latched on unit time-out event
    //
    newCount = EQEP_getPositionLatch(myEQEP1_BASE);
    //
    // Gets rotation direction of motor
    //
    direction = EQEP_getDirection(myEQEP1_BASE);
    //
    // Calculates the number of position in unit time based on direction
    //
    if (direction > 0 ){
        if (newCount >= oldCount)
            newCount = newCount - oldCount;
        else
            newCount = ((4 * ENCODER_SLOTS - 1) - oldCount) + newCount;
        }
    else {
        if (newCount <= oldCount)
            newCount = oldCount - newCount;
        else
            newCount = ((4 * ENCODER_SLOTS - 1) - newCount) + oldCount;
        }
    //
    // Stores the current position count value to oldCount variable
    //
    oldCount = currentEncoderPosition;
    //
    // Calculate frequency and speed values
    // frequency found by counting external input pulses for UNIT PERIOD
    // speed derived from encoder frequency and encoder resolution
    //
    frequency = (newCount * (uint32_t)1000000U) / ((uint32_t)UNIT_PERIOD);
    speed = (frequency * 60) / ((float)(4 * ENCODER_SLOTS));
    //
    // Clear interrupt flag and issue ACK
    //
    EQEP_clearInterruptStatus(myEQEP1_BASE,EQEP_INT_UNIT_TIME_OUT|EQEP_INT_GLOBAL);
}

//
// End of File
//

