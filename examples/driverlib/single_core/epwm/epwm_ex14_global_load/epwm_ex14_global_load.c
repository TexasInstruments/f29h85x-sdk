//###########################################################################
//
// FILE:   epwm_ex14_global_load.c
//
// TITLE:  Use Case Example Code for EPWM Developers Guide
//
//
// This example contains the solution for the use case described in the
// C2000 ePWM Developer's Guide (www.ti.com/lit/SPRAD12).
//
// The use case described in the application report is the following:
//
// Output frequency of 400 kHz for EPWM1/2/3
// Phase shift of 120 degrees for EPWM2 with respect to EPWM1
// Phase shift of 240 degrees for EPWM3 with respect to EPWM1
// Duty cycle of 45% for EPWM1/2/3
// Active high complementary signal pairs with 200 nsec of rising/falling edge delay for EPWM1/2/3
// Cycle-by-Cycle trip zone protection through comparator signal on EPWM2
// One-Shot trip protection through GPIO on EPWM3
// Interrupt generation everytime the time base counter equals zero on EPWM1
// Global loading to support asynchronous updates of action qualifier settings
// Link CMPA/CMPB of EPWM1 to EPWM2 and EPWM3
//
//###########################################################################
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

//###########################################################################

//
// Included Files
//
#include "board.h"

//
// Defines
//


//
// Globals
//
uint16_t  perform_one_shot_load=0;

//
//  Function Prototypes
//



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
    // Configure GPIO pins and EPWM Modules
    //
    Board_init();
    SysCtl_enableEPWMXLINK(SYSCTL_EPWM1_XLINK);
    SysCtl_enableEPWMXLINK(SYSCTL_EPWM2_XLINK);
    SysCtl_enableEPWMXLINK(SYSCTL_EPWM3_XLINK);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_EPWM1);
    Interrupt_enable(INT_EPWM2);
    Interrupt_enable(INT_EPWM3);

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
        if(perform_one_shot_load==1)
        {
            //
            // EPWM1, EPWM2, EPWM3 are linked so only EPWM1 needs to be updated
            //
            EPWM_setCounterCompareValue(EPWM1XLINK_BASE, EPWM_COUNTER_COMPARE_A, 100);
            EPWM_setCounterCompareValue(EPWM1XLINK_BASE, EPWM_COUNTER_COMPARE_B, 100);

            //
            // Change the Action Qualifier Settings for EPWM1, EPWM2, and EPWM3
            // using XLINKBASE
            EPWM_setActionQualifierAction(EPWM1XLINK_BASE,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_LOW,
                                            EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            EPWM_setActionQualifierAction(EPWM1XLINK_BASE,EPWM_AQ_OUTPUT_A,EPWM_AQ_OUTPUT_HIGH,
                                            EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
            // PWM outputs will not change until the global one shot latch is set
            // Using XLINKBASE will set the global one shot latch for ePWM1/2/3 (Similar to F28P65x or any devices with XLINK)
            ESTOP0;
            // EPWM1, EPWM2, EPWM3 are linked
            EPWM_setGlobalLoadOneShotLatch(EPWM1XLINK_BASE);

            // Clear the setting
            perform_one_shot_load = 0;
        }
    }
}


void INT_myEPWM1_ISR(void){
    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
}

void INT_myEPWM2_TZ_ISR(void){

     //
     // Clear the flags
     //
     EPWM_clearTripZoneFlag(myEPWM2_BASE, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_CBC));


}

void INT_myEPWM3_TZ_ISR(void){

    //
    // Re-enable the OST Interrupt
    //
     EPWM_clearTripZoneFlag(myEPWM3_BASE, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));
}

