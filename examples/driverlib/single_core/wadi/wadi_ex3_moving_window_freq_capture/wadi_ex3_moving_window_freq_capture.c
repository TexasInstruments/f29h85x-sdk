//#############################################################################
//
// FILE:   wadi_ex3_moving_window_freq_capture.c
//
// TITLE:  WADI frequency check (main and moving window)

//! \addtogroup driver_example_list
//! <h1>WADI signal frequency configuration</h1>
//!
//! This example configures WADI1 Block 1 and Block 2 as follows
//!  - WADI1 Block 1 has two inputs from the input crossbar and
//!    frequency check is enabled on one of the signals.
//!  - GPIO0 and GPIO1 are routed to the input X-BAR from which 
//!    it is routed to WADI block 1 signal 1 and signal 2 respectively.
//!  - Hardware trigger is enabled as trigger1 for signal1.
//!  - Here frequency check is enabled in moving window average mode
//!    and error flags are raised based on the compare values along with the margins.
//!
//! The WADI block has error status register that can be used to
//! monitor if any erroneous signals occur. (BLKERRSTS)
//!
//! This example also makes use of the Input X-BAR. GPIO0 (ePWM1A
//! output) is routed to the input X-BAR, from which it is routed to
//! WADI1 inputs.
//!
//!
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


void signaltriggerconfig();
void sigfreqconfig();
void Wadi_start();

uint32_t error1;

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
    // Configure ePWM1, ePWM2, and TZ GPIOs/Modules
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    signaltriggerconfig();

    sigfreqconfig();

    // sigtosigfreqconfig();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Wadi_start();
    GpioDataRegs.GPASET.bit.GPIO5 = 1;
    GpioDataRegs.GPASET.bit.GPIO6 = 1;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {

    }
}

void signaltriggerconfig()
{
    WADI_configSignalAndTrigger(WADI1BLK1CONFIG_BASE_FRAME(0U),
                            WADI_INPUT_SIGNAL_INPUTXBAR33,
                            WADI_INPUT_SIGNAL_INPUTXBAR34,
                            WADI_WADI1_TRIGGER1_INPUTXBAR44,
                            WADI_WADI1_TRIGGER2_INPUTXBAR38);
}

void sigfreqconfig()
{

    WADI_SigConfig configSignal = {
        .signal = WADI_SIGNAL1,
        .triggerMode = WADI_TRIGGER_MODE_HARDWARE_TRIGGER
    };
    WADI_FreqConfigParams configParams = {
        .freqMode = WADI_COMPARE_FREQ_MODE_MOVING_WINDOW,   //moving window mode
        .polarity = WADI_SIGNAL_POLARITY_RISING_EDGE,
        .aggrMode = WADI_AGGR_MODE_AGGREGATION_AVERAGE,     //Average mode is activated
        .numaggr = WADI_AGGREGATION_SIZE4,
        .movingCount = WADI_MOVING_COUNT2,
        .mvwtime = 1000,
        .timeWindow = 0
    };

    WADI_FreqConfigCompare configCompare = {
        .cmpAVal = 4, .cmpAMargin = 3,
        .cmpBVal = 25, .cmpBMargin = 5,
        .cmpPkVal = 16, .cmpPkMargin = 3,
        .cmpAvgVal = 12, .cmpAvgMargin = 2
    };

    WADI_measureFrequency(WADI1BLK1CONFIG_BASE_FRAME(0U),
                        &configSignal,
                        &configParams,
                        &configCompare);
}

void Wadi_start()
{
    WADI_enableClock(WADI1BLK1CONFIG_BASE_FRAME(0U));
    WADI_enableBaseTimer(WADI1OPERSSS_BASE);
}
