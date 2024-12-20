//#############################################################################
//
// FILE:  dcc_ex1_single_shot_verification.c
//
// TITLE:  DCC Single shot Clock verification
//
//! \addtogroup driver_example_list
//! <h1>DCC Single shot Clock verification</h1>
//!
//! This program uses the Internal oscillator 2 as a reference clock to verify
//! the frequency of the PLL.
//!
//! The Dual-Clock Comparator Module 1 is used for the clock verification.
//! The clocksource0 is the reference clock (Fclk0 = 10Mhz) and the
//! clocksource1 is the clock that needs to be verified (Fclk1 = 200Mhz).
//! Seed is the value that gets loaded into the Counter.
//!
//! Please refer to the TRM for details on counter seed values to be set.
//!
//! \b External \b Connections \n
//!   - None
//!
//! \b Watch \b Variables \n
//!  - \b result - Status of the clock verification
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
#define PASS 0
#define FAIL 1

//
// Globals
//
volatile uint32_t result = FAIL;

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
    // Verify the frequency of PLL clock using the INTOSC2 as reference clock
    // FClk1 = PLL frequency = 200 MHz
    // FClk0 = INTOSC2 frequency = 25 MHz
    // Tolerance = 1%
    // Allowable Frequency Tolerance = 0% (update as per the error in frequency)
    // SysClk Freq = 200MHz
    //

    //
    // Configure the DCC module to verify the clock frequency
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start the DCC
    //
	DCC_enableModule(myDCC0_BASE);

    //
    // Wait until Error or Done Flag is generated
    //
    while(!(DCC_getSingleShotStatus(myDCC0_BASE) || DCC_getErrorStatus(myDCC0_BASE)))
    {
    }

    //
    // Result of clock verification if DCC completes without error
    //
    if(DCC_getSingleShotStatus(myDCC0_BASE))
    {
        result = PASS;
    }
    else
    {
        result = FAIL;
    }

    ESTOP0;
}
