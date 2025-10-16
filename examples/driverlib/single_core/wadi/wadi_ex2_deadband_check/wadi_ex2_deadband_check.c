//#############################################################################
//
// FILE:   wadi_ex2_deadband_check.c
//
// TITLE:  WADI deadband mode check
//
//! \addtogroup driver_example_list
//! <h1>WADI deadband mode check</h1>
//!
//! This example configures WADI1 Block 1 and Block 2 as follows
//!  - WADI1 Block 1 has two inputs from the input crossbar and deadband check
//!    is enabled between them.
//!  - GPIO0 and GPIO1 are routed to the input X-BAR, from which it is routed to
//!    wadi block1 signal1 and signal2 respectively.
//!  - Hardware trigger and synchronized trigger are enabled for trigger1 and trigger2.
//!  - Signal to signal deadband is configured by using compare parameters,comparetype and
//!    signal polarity.
//!  - SIGTOSIG_DBCMPAERR and SIGTOSIG_DBCMPBERR flags are raised under BLKERRSTS register.
//!
//! The WADI block has error status register that can be used to
//! monitor if any erroneous signals occur. (BLKERRSTS)
//!
//! This example also makes use of the Input X-BAR. GPIO0 (ePWM1A
//! output) is routed to the input X-BAR, from which it is routed to
//! WADI1 inputs
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
void deadbandConfig();

volatile uint32_t error1;

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

    deadbandConfig();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    WADI_enableClock(WADI1BLK1CONFIG_BASE_FRAME(0U));

    GpioDataRegs.GPASET.bit.GPIO5 = 1;
    GpioDataRegs.GPASET.bit.GPIO6 = 1;

    // should read the value 20 for db mode
    error1 = (HWREG(WADI1BLK1CONFIG_BASE_FRAME(0U) + WADI_O_BLKERRINFO) & WADI_BLKERRINFO_ERRCNT_M);

    WADI_disableClock(WADI1BLK1CONFIG_BASE_FRAME(0U));

    GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;

    HWREG(WADI1BLK1CONFIG_BASE_FRAME(0U) + WADI_O_BLKERRCFG) = 0x2U; // for signal to signal debug count

    WADI_enableClock(WADI1BLK1CONFIG_BASE_FRAME(0U));
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
    WADI_configSignalAndTrigger(WADI1BLK1CONFIG_BASE_FRAME(0U), WADI_INPUT_SIGNAL_INPUTXBAR33, WADI_INPUT_SIGNAL_INPUTXBAR34,
                                    WADI_WADI1_TRIGGER1_INPUTXBAR44 , WADI_WADI1_TRIGGER2_INPUTXBAR38);
}


void deadbandConfig()
{
    WADI_SigToSigConfig configSignals = {
        .triggerMode1 = WADI_TRIGGER_MODE_HARDWARE_TRIGGER,
        .triggerMode2 = WADI_TRIGGER_MODE_SYNCHRONIZED_TRIGGER
    };

    WADI_SigToSigDeadbandConfigParams configCompare = {
        .compareA = 100,
        .compareB = 200,
        .compareType = WADI_COMPARE_CONFIGURED,
        .polarity1 = WADI_SIGNAL_POLARITY_RISING_EDGE,
        .polarity2 = WADI_SIGNAL_POLARITY_FALLING_EDGE
    };

    WADI_compareSigToSigDeadBandMode(WADI1BLK1CONFIG_BASE_FRAME(0U),
                            &configSignals,
                            &configCompare);
}
