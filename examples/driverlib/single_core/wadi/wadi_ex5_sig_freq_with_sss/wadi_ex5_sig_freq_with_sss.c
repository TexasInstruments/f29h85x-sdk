//#############################################################################
//
// FILE:   wadi_ex5_sig_freq_with_sss.c
//
// TITLE:  WADI signal frequency check and configuring events with SSS
//
//! \addtogroup driver_example_list
//! <h1>WADI FREQUENCY CHECK ALONGWITH SSS</h1>
//!
//! This example configures WADI1 Block 1 as follows
//!  - WADI1 Block 1 has two inputs from the input crossbar and
//!    pulse width check and freq check is also enabled for both the
//!    signals of the block
//!  - The SSS is also configured to override the signal 1 block 1.
//!  - 2 Events are configured using SSS.
//!    Event1 keep tracks of the errors for signal1 of block1 and 
//!    Event2 keep tracks of the errors for signal2 of block1.
//!  - Trigger sequence is 1->2 and then 2 triggers the SSS that means
//!    output event1 is triggered by event2.
//!  - Output event 1 overrides both signal1 and signa2 of block 1
//!  - Output event 2 is used  to override the value to low
//!  - Output is routed to output X-BAR which is connected to GPIO14 and GPIO3.
//!
//!
//! The WADI block has error status register that can be used to
//! monitor if any erroneous signals occur. (BLKERRSTS)
//! override values can be seen in SSSOUTEVT1DUR and SSSOUTEVT2DUR registers.
//!
//! This example also makes use of the Input X-BAR,Output X-BAR. GPIO0 (ePWM1A
//! output) is routed to the input X-BAR, from which it is routed to
//! WADI1 inputs and configuring output events based on the errors events using SSS
//! output is routed to Output X-Bar.
//! 
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
void sssconfig();
void sigfreqconfig1();
void sigfreqconfig2();
void Wadi_start();
void Wadi_stop();


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
    // ENINT;
    Interrupt_enableGlobal();


    signaltriggerconfig();      //configure both input and trigger signals
    sigfreqconfig1();           //configuring frequency of signal1
    sigfreqconfig2();           //configuring frequency of signal2

    sssconfig();                //configuring SSS for output events

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Wadi_start();
    GpioDataRegs.GPASET.bit.GPIO5 = 1;
    GpioDataRegs.GPASET.bit.GPIO6 = 1;

    // IDLE loop. Just sit and loop forever (optional):
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


void sssconfig()
{
    // Masking for aggregating the errors in SSS
    WADI_setSSSTriggerWord(WADI1BLK1CONFIG_BASE_FRAME(0U),
                        WADI_ERROR_TYPES_SIG1CMPAERR | WADI_ERROR_TYPES_SIG1CMPBERR |
                        WADI_ERROR_TYPES_SIG2CMPAERR | WADI_ERROR_TYPES_SIG2CMPBERR);

    // // configuring the events

    // event 1 keeps track of the errors in signal 1 of block 1
    WADI_configSSSEvent(WADI1OPERSSS_BASE_FRAME(0U), WADI_EVENT1,
                        WADI_EVENT_ERROR_SIG1_SIGTOSIG_BLOCK1);

    // event 2 keeps track of the errors in signal 2 of block 1
    WADI_configSSSEvent(WADI1OPERSSS_BASE_FRAME(0U), WADI_EVENT2,
                WADI_EVENT_ERROR_SIG1_SIGTOSIG_BLOCK1 | WADI_EVENT_ERROR_SIG2_BLOCK1 );

    // trigger seq is 1->2 and 2 triggers the SSS
    WADI_configSSSTriggerSequence(WADI1OPERSSS_BASE_FRAME(0U),
                                WADI_EVENT1,
                                WADI_EVENT2);

    // output event 1 is triggered by event 2
    WADI_configSSSOutputEventTrigger(WADI1OPERSSS_BASE_FRAME(0U),
                WADI_OUTPUT_EVENT1, WADI_EVENT2);

    // params of output event 1, it overrides both sig1 and sig2 of block 1
    WADI_configSSSOutputEventParamsWithLink(WADI1OPERSSS_BASE_FRAME(0U),
                WADI_OUTPUT_EVENT1,
                WADI_SSS_OUTPUT_ACTION_BLOCK1_SIG1_HIGH | WADI_SSS_OUTPUT_ACTION_BLOCK1_SIG2_HIGH,
                0x1FFF, // THE FREQ OF THE CLOCK USED HERE IS 200MHz
                WADI_OUTPUT_EVENT2);

    // params of output event 2, it is used to override the value to low
    WADI_configSSSOutputEventParamsWithLink(WADI1OPERSSS_BASE_FRAME(0U),
                WADI_OUTPUT_EVENT2,
                WADI_SSS_OUTPUT_ACTION_LOW,
                0xF00,
                WADI_OUTPUT_EVENT1);

    // selects that block 1 sig 1 can be overriden by output event 1 and output event 2
    WADI_selectSSSOutputEvent(WADI1OPERSSS_BASE_FRAME(0U),
                WADI_OUTPUT_SIGNAL_BLOCK1_SIG1,
                WADI_OUTPUT_EVENT1 | WADI_OUTPUT_EVENT2);
}


void sigfreqconfig1()
{
    WADI_SigConfig configSignal = {
        .signal = WADI_SIGNAL1,
        .triggerMode = WADI_TRIGGER_MODE_HARDWARE_TRIGGER
    };

    WADI_FreqConfigParams configParams = {
        .freqMode = WADI_COMPARE_FREQ_MODE_FIXED_WINDOW,
        .polarity = WADI_SIGNAL_POLARITY_RISING_EDGE,
        .aggrMode = WADI_AGGR_MODE_AGGREGATION,
        .numaggr = WADI_AGGREGATION_SIZE0,
        .movingCount = 0,
        .mvwtime = 0,
        .timeWindow = 10000
    };

    WADI_FreqConfigCompare configCompare = {
        .cmpAVal = 10,
        .cmpAMargin = 4,
        .cmpBVal = 50,
        .cmpBMargin = 5,
        .cmpPkVal = 16,
        .cmpPkMargin = 3,
        .cmpAvgVal = 12,
        .cmpAvgMargin = 2
    };

    WADI_measureFrequency(WADI1BLK1CONFIG_BASE_FRAME(0U),
                        &configSignal,
                        &configParams,
                        &configCompare);
}

void sigfreqconfig2()
{
    WADI_SigConfig configSignal = {
        .signal = WADI_SIGNAL2,
        .triggerMode = WADI_TRIGGER_MODE_HARDWARE_TRIGGER
    };

    WADI_FreqConfigParams configParams = {
        .freqMode = WADI_COMPARE_FREQ_MODE_FIXED_WINDOW,
        .polarity = WADI_SIGNAL_POLARITY_RISING_EDGE,
        .aggrMode = WADI_AGGR_MODE_AGGREGATION,
        .numaggr = WADI_AGGREGATION_SIZE0,
        .movingCount = 0,
        .mvwtime = 0,
        .timeWindow = 10000
    };

    WADI_FreqConfigCompare configCompare = {
        .cmpAVal = 10,
        .cmpAMargin = 4,
        .cmpBVal = 50,
        .cmpBMargin = 5,
        .cmpPkVal = 16,
        .cmpPkMargin = 3,
        .cmpAvgVal = 12,
        .cmpAvgMargin = 2
    };

    WADI_measureFrequency(WADI1BLK1CONFIG_BASE_FRAME(0U),
                        &configSignal,
                        &configParams,
                        &configCompare);
}

void Wadi_start()
{
    WADI_enableClock(WADI1BLK1CONFIG_BASE_FRAME(0U));
    WADI_enableBaseTimer((WADI1OPERSSS_BASE_FRAME(0U)));
}

void Wadi_stop()
{
    WADI_disableClock(WADI1BLK1CONFIG_BASE_FRAME(0U));
    WADI_disableBaseTimer((WADI1OPERSSS_BASE_FRAME(0U)));
}


