//#############################################################################
//
// FILE:   wadi_ex4_sig_to_sig_freq_capture.c
//
// TITLE:  WADI signal to signal frequency check in fixed window average mode
//
//! \addtogroup driver_example_list
//! <h1>WADI sig to sig freq check </h1>
//!
//! This example configures WADI1 Block 1 as follows
//!  - WADI1 Block 1 has two inputs from the input crossbar and
//!    freq check is also enabled for both the signals of the block.
//!  - Hardware trigger and synchronized trigger signals are configured.
//!  - Here, signal to signal frequency check is done through fixed
//!    window (movingtime = 0).
//!  - Aggregate mode and average mode is activated(checks ERRTYPE in BLKERRINFO register).
//!  - Signal 1 is taken through GPIO0 from epwm0 and signal 2 is taken through GPIO2 from epwm1.
//!
//! The WADI block has error status register that can be used to
//! monitor if any erroneous signals occur. (BLKERRSTS)
//! Here in BLKERRSTS register SIGTOSIG_AVGERR and SIGTOSIG_CMPERR , these errors will be flagged
//! along with individual signal errors.
//!
//! This example also makes use of the Input X-BAR, Output X-BAR. GPIO0 (ePWM1A
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
void sigtosigfreqconfig();
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


    //input signals and hardware and synchronized triggers are enabled through Input X-BAR.
    signaltriggerconfig();

    //signal to signal frequency check in fixed window average mode
    sigtosigfreqconfig();

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
                            WADI_INPUT_SIGNAL_INPUTXBAR34,
                            WADI_INPUT_SIGNAL_INPUTXBAR36,
                            WADI_WADI1_TRIGGER1_INPUTXBAR44,
                            WADI_WADI1_TRIGGER2_INPUTXBAR38);
}



void sigtosigfreqconfig()
{
    WADI_SigToSigConfig configSignals = {
        .triggerMode1 = WADI_TRIGGER_MODE_HARDWARE_TRIGGER,         //hardware trigger and synchronized trigger are enabled.
        .triggerMode2 = WADI_TRIGGER_MODE_SYNCHRONIZED_TRIGGER
    };

    WADI_SigToSigFreqConfigParams configParams = {
        .freqMode = WADI_COMPARE_FREQ_MODE_FIXED_WINDOW,
        .polarity = WADI_SIGNAL_POLARITY_RISING_EDGE,
        .aggrMode = WADI_AGGR_MODE_AGGREGATION_AVERAGE,     // Activate the average mode
        .numaggr = WADI_AGGREGATION_SIZE4,
        .movingCount = WADI_MOVING_COUNT0,                  // moving count should be 0 for main mode
        .mvwtime = 0,                                       // moving time should be 0 for fixed window mode
        .timeWindow = 10000
    };

    WADI_SigToSigFreqConfigCompare configCompare = {
        .cmpVal = 10, .cmpMargin = 2,
        .cmpAvgVal = 7, .cmpAvgMargin = 1,
        .cmpPkVal = 20, .cmpPkMargin = 3
    };

    WADI_compareSigToSigFrequency(WADI1BLK1CONFIG_BASE_FRAME(0U),
                        &configSignals,
                        &configParams,
                        &configCompare);

}

void Wadi_start()
{
    WADI_enableClock(WADI1BLK1CONFIG_BASE_FRAME(0U));
    HWREG (WADI1OPERSSS_BASE_FRAME(0U) + WADI_O_BASETIMERHIGH) |= WADI_BASETIMERHIGH_ENBASETIMER;
}


