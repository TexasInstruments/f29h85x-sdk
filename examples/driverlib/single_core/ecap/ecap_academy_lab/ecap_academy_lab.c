//#############################################################################
//
// FILE:    ecap_academy_lab.c
//
// TITLE:   eCAP and ePWM Lab.
//
//! \addtogroup driver_example_list
//! <h1>eCAP APWM Phase-shift Example</h1>
//!
//! This lab sets up the eCAP1 to capture ePWM1's GPIO0 output. ePWM1 is 
//! configured to output a certain waveform. ePWM2 is configured to generate
//! a SOCA to sample the GPIO0 signal. ADCA is used to sample the output and
//! stores the samples to AdcBuf. 
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
#include "bitfield_structs.h"
//
// Globals
//
uint32_t ePwm_TimeBase;
uint32_t ePwm_MinDuty;
uint32_t ePwm_MaxDuty;
uint32_t ePwm_curDuty;
uint16_t AdcBuf[50];            // Buffer to store ADC samples.
uint16_t *AdcBufPtr = AdcBuf;   // Pointer to ADC buffer samples.
uint16_t LedCtr = 0;            // Counter to slow down LED toggle in ADC ISR.
uint16_t DutyModOn = 0;         // Flag to turn on/off duty cycle modulation.
uint16_t DutyModDir = 0;        // Flag to control duty mod direction up/down.
uint16_t DutyModCtr = 0;        // Counter to slow down rate of modulation.
int32_t eCapPwmDuty;            // Percent = (eCapPwmDuty/eCapPwmPeriod)*100.
int32_t eCapPwmPeriod;          // Frequency = DEVICE_SYSCLK_FREQ/eCapPwmPeriod.

//
// Function Prototypes
//
void error(void);

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
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Board initialization
    // Configure InputXbar7 as eCAP input
    // Enable interrupts required for this example
    //

    Board_init();

    //
    // Configure the SOCA MIXEN
    //
    EPwm2Regs.ETSOCAMIXEN.bit.PRD = 0x01;
    EPwm2Regs.ETSOCAMIXEN.bit.ZRO = 0x01;

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Record time base, duty
    //
    ePwm_TimeBase = EPWM_getTimeBasePeriod(myEPWM0_BASE);
    ePwm_MinDuty = (uint32_t)(0.95f * (float)ePwm_TimeBase);
    ePwm_MaxDuty = (uint32_t)(0.05f * (float)ePwm_TimeBase);
    ePwm_curDuty = EPWM_getCounterCompareValue(myEPWM0_BASE, EPWM_COUNTER_COMPARE_A);

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
// error - Error function
//
void error()
{
    ESTOP0;
}
void INT_myADC0_1_ISR(void)
{
    //
    // Clear interrupt flags.
    //
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    //
    // Write contents of the ADC register to a circular buffer.
    //
    *AdcBufPtr = ADC_readResult(myADC0_RESULT_BASE, myADC0_SOC0);
    if (AdcBufPtr == (AdcBuf + 49))
    {
        //
        // Force buffer to wrap around.
        //
        AdcBufPtr = AdcBuf;
    } else {
        AdcBufPtr += 1;
    }
    if (LedCtr >= 49999) {
        //
        // Divide 50kHz sample rate by 50e3 to toggle LED at a rate of 1Hz.
        //
        GPIO_togglePin(myBoardLED0_GPIO);
        LedCtr = 0;
    } else {
        LedCtr += 1;
    }
    if (DutyModOn) {
        //
        // Divide 50kHz sample rate by 16 to slow down duty modulation.
        //
        if (DutyModCtr >= 15) {
            if (DutyModDir == 0) {
                //
                // Increment State => Decrease Duty Cycle.
                //
                if (ePwm_curDuty >= ePwm_MinDuty) {
                    DutyModDir = 1;
                } else {
                    ePwm_curDuty += 1;
                }
            } else {
                //
                // Decrement State => Increase Duty Cycle.
                //
                if (ePwm_curDuty <= ePwm_MaxDuty) {
                    DutyModDir = 0;
                } else {
                    ePwm_curDuty -= 1;
                }
            }
            DutyModCtr = 0;
        } else {
            DutyModCtr += 1;
        }
    }
    //
    // Set the counter compare value.
    //
    EPWM_setCounterCompareValue(myEPWM0_BASE, EPWM_COUNTER_COMPARE_A, ePwm_curDuty);
}

void INT_myECAP0_ISR(void)
{
    ECAP_clearGlobalInterrupt(myECAP0_BASE);
    ECAP_clearInterrupt(myECAP0_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_3);
    //
    // Calculate duty and period using eCAP reading
    // Divide both values by 2, since eCAP runs at 200Mhz 
    // ePWM runs at 100Mhz
    eCapPwmDuty = (int32_t)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2) -
                  (int32_t)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1);
    eCapPwmDuty = eCapPwmDuty >> 1;
    eCapPwmPeriod = (int32_t)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) -
                    (int32_t)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1);
    eCapPwmPeriod = eCapPwmPeriod >> 1;
}   