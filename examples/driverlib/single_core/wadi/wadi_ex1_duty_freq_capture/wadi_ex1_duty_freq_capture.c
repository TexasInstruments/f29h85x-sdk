//#############################################################################
//
// FILE:   wadi_ex1_duty_freq_capture.c
//
// TITLE:  WADI Duty and Frequency validation
//
//! \addtogroup driver_example_list
//! <h1>WADI Duty and Frequency check</h1>
//!
//! This example configures WADI1 Block 1 and Block 2 as follows
//!  - WADI1 Block 1 has an input from the PWM using INPUTXBAR
//!  - Pulse width checking is enabled with defined margin of error
//!  - WADI1 Block 2 has an input from the PWM using INPUTXBAR
//!  - Frequency checking is enabled with defined margin of error
//!
//! The WADI block has error status register that can be used to
//! monitor if any erroneous signals occur. (BLKERRSTS)
//!
//! This example also makes use of the Input X-BAR. GPIO0 (ePWM1A
//! output) is routed to the input X-BAR, from which it is routed to 
//! WADI SIG1 input.
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
#include "inc/hw_memmap.h"
#include "bitfield_structs.h"

//
// Globals
//
uint16_t wadi_error_count = 0;
uint32_t val1;
uint32_t val2;
uint32_t val3;
uint32_t val4;

//
// Function Prototypes
//
void WADI_DutyConfig();
void WADI_FreqConfig();
void WADI_Start();

//
// eCAP is used as another method to validate
// digital signal
//
void INT_myECAP0_ISR(void)
{
    val1 = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1);
    val2 = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2);
    val3 = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3);
    val4 = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_4);
    ECAP_clearInterrupt(myECAP0_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(myECAP0_BASE);
}

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

    WADI_DutyConfig();
    WADI_FreqConfig();
    
    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    WADI_Start();


    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        if ((Wadi1Blk1ConfigRegs.BLKERRSTS.bit.SIG1CMPAERR != 0x0) || 
        (Wadi1Blk2ConfigRegs.BLKERRSTS.bit.SIG1CMPAERR != 0x0))
        {
          wadi_error_count++;
        }
    }
}

void WADI_DutyConfig()
{
    //
    // Duty Check 
    //
    Wadi1Blk1ConfigRegs.BLKCFG.bit.SIG1IN = 0x10;
    Wadi1Blk1ConfigRegs.BLKCFG.bit.SIG2IN = 0x11;
    
    //
    // SIG1 Configuration
    //
    Wadi1Blk1ConfigRegs.SIG1CFG.bit.SIGPOL = 0x01;
    Wadi1Blk1ConfigRegs.SIG1CFG.bit.EDGESPAN = 0x01;
    Wadi1Blk1ConfigRegs.SIG1CMPA.bit.CMPA = 500;
    Wadi1Blk1ConfigRegs.SIG1CMPA.bit.CMPAMARGIN = 15;
    Wadi1Blk1ConfigRegs.SIG1CMPB.bit.CMPB = 500;
    Wadi1Blk1ConfigRegs.SIG1CMPB.bit.CMPBMARGIN = 15;
    
    //
    // Trigger configuration
    //
    Wadi1Blk1ConfigRegs.BLKTRIGCFG.bit.TRIG1TYPE = 0x02;
    Wadi1Blk1ConfigRegs.BLKTRIGCFG.bit.TRIG2TYPE = 0x04;

    // 
    // Select the signal to analyze for debug
    // SIG1 is selected
    //
    Wadi1Blk1ConfigRegs.BLKERRCFG.bit.ERRCNTSEL = 0x00;
    

}

void WADI_FreqConfig()
{
    //
    // Freq Check
    //
    Wadi1Blk2ConfigRegs.BLKCFG.bit.SIG1IN = 0x10;
    Wadi1Blk2ConfigRegs.BLKCFG.bit.SIG2IN = 0x11;
    
    //
    // SIG1 Configuration
    //
    Wadi1Blk2ConfigRegs.SIG1CFG.bit.SIGPOL = 0x01;
    Wadi1Blk2ConfigRegs.SIG1CFG.bit.EDGESPAN = 0x02;
    Wadi1Blk2ConfigRegs.SIG1CMPA.bit.CMPA = 1000;
    Wadi1Blk2ConfigRegs.SIG1CMPA.bit.CMPAMARGIN = 10;
    Wadi1Blk2ConfigRegs.SIG1CMPB.bit.CMPB = 1000;
    Wadi1Blk2ConfigRegs.SIG1CMPB.bit.CMPBMARGIN = 10;
    
    //
    // Trigger configuration
    //
    Wadi1Blk2ConfigRegs.BLKTRIGCFG.bit.TRIG1TYPE = 0x02;
    Wadi1Blk2ConfigRegs.BLKTRIGCFG.bit.TRIG2TYPE = 0x04;
    
    //
    // Select the signal to analyze for debug
    // SIG1 is selected
    //
    Wadi1Blk2ConfigRegs.BLKERRCFG.bit.ERRCNTSEL = 0x00;
}
void WADI_Start()
{
    // 
    // Enable WADI 1 Block 1
    //
    Wadi1Blk1ConfigRegs.BLKCFG.bit.CLKEN = 0x01;
    Wadi1Blk1ConfigRegs.BLKTRIGCFG.bit.TRIG1SWEN = 0x01;
    
    // 
    // Enable WADI 1 Block 2
    //
    Wadi1Blk2ConfigRegs.BLKCFG.bit.CLKEN = 0x01;
    Wadi1Blk2ConfigRegs.BLKTRIGCFG.bit.TRIG1SWEN = 0x01;
}
