//#############################################################################
//
// FILE:   wadi_ex6_pw_with_dma_trigger.c
//
// TITLE:  WADI pulse width check with dma trigger
//
//! \addtogroup driver_example_list
//! <h1>WADI Pulse Wdith Check with DMA trigger</h1>
//!
//! This example configures WADI1 Block 1 as follows
//!  - WADI1 Block 1 has an input from the input Xbar and pulse width check is
//!    enabled in that block for signal 1
//!  - Signal1 is taken from GPIO2 which is connected to the EPWMA.
//!  - RTDMA trigger is enabled for the block.
//!  - Filtered Write is enabled for the block.
//!  - Errors will occur in compare A and compare B register values 
//!    so that filtered writes will update SIG1CMPA and SIG1CMPB register according
//!    for which register values errors are occured.
//!    
//!
//! The WADI block has error status register that can be used to
//! monitor if any erroneous signals occur. (BLKERRSTS)
//!
//! This example also makes use of the Input X-BAR. GPIO0 (ePWM1A
//! output) is routed to the input X-BAR, from which it is routed to
//! WADI SIG1 input and also RTDMA
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
void pulsewidthconfig();
// void frequencyconfig();

// Prototypes that provide parameter values to update
uint32_t compare_Param1[2];

// Define source and destination addresses for comapre parameters
const void *srcAddr1= (const void *)compare_Param1;
const void *destAddr1= (const void *)(WADI1BLK1CONFIG_BASE_FRAME(0U) + WADI_O_SIG1CMPA);

uint32_t compare_Param2[2];

const void *srcAddr2= (const void *)compare_Param2;
const void *destAddr2= (const void *)(WADI1BLK1CONFIG_BASE_FRAME(0U) + WADI_O_SIG1CMPB);


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

    signaltriggerconfig();          //configuring both input and trigger signals
    pulsewidthconfig();             //pulse width checking for signal 1

    // We will try to update SIG1CMPA and SIG1CMPB register with this below values:
    compare_Param1[0] = 0x10000A0U;
    compare_Param1[1] = 0x1000020U;

    compare_Param2[0] = 0x100AAA0U;
    compare_Param2[1] = 0x1000222U;

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    WADI_enableDmaTrigger(WADI1OPERSSS_BASE, WADI_DMA_REQ_SOURCES_BLOCK1);     // Enabling the RTDMA Trigger
    WADI_enableFilteredWrite(WADI1OPERSSS_BASE, WADI_DMA_REQ_SOURCES_BLOCK1); // enabling the filtered write for block 1

    WADI_enableBaseTimer(WADI1OPERSSS_BASE_FRAME(0U));
    WADI_enableClock(WADI1BLK1CONFIG_BASE_FRAME(0U));
    WADI_enableSoftwareTrigger(WADI1BLK1CONFIG_BASE_FRAME(0U), WADI_SIGNAL1);

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
                            WADI_INPUT_SIGNAL_INPUTXBAR36,
                            WADI_INPUT_SIGNAL_INPUTXBAR34,
                            WADI_WADI1_TRIGGER1_INPUTXBAR44,
                            WADI_WADI1_TRIGGER2_INPUTXBAR38);
}



void pulsewidthconfig()
{
    WADI_SigConfig configSignals = {
        .signal = 0,  // signal 1
        .triggerMode = WADI_TRIGGER_MODE_SOFTWARE_TRIGGER // It's an software trigger
    };

    WADI_PulseWidthConfigParams configParams = {
        .aggrMode = WADI_AGGR_MODE_AGGREGATION,
        .numAggr = WADI_AGGREGATION_SIZE0,      //aggregation is disabled so each measurements are independently compared.
        .edgeSpan = WADI_EDGESPAN1,
        .polarity = WADI_SIGNAL_POLARITY_RISING_EDGE
    };


    // The actual value of the pulse width is 0x7AA (1962)

    
    // Error will occur for compare values of both compare A and compare B registers,
    // so filtered writes will update both CMPA and CMPB register
    // SIG1CMPA = 0x10000A0 and SIG1CMPB = 0x100AAA0
    /**Uncomment this section to get errors in both Compare A and Compare B register**/

    // WADI_PulseWidthConfigCompare configCompare = {
    // .cmpAVal = 1000, .cmpAMargin = 50,
    // .cmpBVal = 1000, .cmpBMargin = 50,
    // .cmpAvgVal = 150, .cmpAvgMargin = 5,
    // .cmpPkVal = 250, .cmpPkMargin = 20
    // };

    /*********************************************************************************/

    // Error will occur for compare values of only compare A register,
    // so filtered writes will update only CMPA register
    // SIG1CMPA = 0x10000A0 only

    /*Uncomment this section to get errors in only Compare A register*/

      WADI_PulseWidthConfigCompare configCompare = {
    .cmpAVal = 1000, .cmpAMargin = 50,
    .cmpBVal = 2000, .cmpBMargin = 50,
    .cmpAvgVal = 150, .cmpAvgMargin = 5,
    .cmpPkVal = 250, .cmpPkMargin = 20
    };

    /*************************************************************** */


    // Error will occur for compare values of only compare B register,
    // so filtered writes will update only CMPB register
    // SIG1CMPB = 0x100AAA0 only

    /*Uncomment this section to get errors only  Compare B register*/

    /*  WADI_PulseWidthConfigCompare configCompare = {
    .cmpAVal = 2000, .cmpAMargin = 50,
    .cmpBVal = 1000, .cmpBMargin = 50,
    .cmpAvgVal = 150, .cmpAvgMargin = 5,
    .cmpPkVal = 250, .cmpPkMargin = 20
    };  */
    
    /*********************************************************************** */

    WADI_measurePulseWidth(WADI1BLK1CONFIG_BASE_FRAME(0U),
                            &configSignals,
                            &configParams,
                            &configCompare);
}




