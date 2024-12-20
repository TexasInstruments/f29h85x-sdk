//#############################################################################
// FILE:  dcc_ex3_continuous_monitoring_of_clock.c
//
// TITLE:  DCC Continuous clock monitoring with sysconfig
//
//! \addtogroup driver_example_list
//! <h1>DCC Continuous clock monitoring</h1>
//!
//! This program demonstrates continuous monitoring of PLL Clock in the
//! system using INTOSC1 as the reference clock. This would trigger an
//! error signal on any error, causing the decrement/ reload of counters to
//! stop.
//! The Dual-Clock Comparator Module 1 is used for the clock monitoring.
//! The clocksource0 is the reference clock (Fclk0 = 10Mhz) and the
//! clocksource1 is the clock that needs to be monitored (Fclk1 = 200Mhz).
//! The clock0 and clock1 seed are set automatically by the error tolerances
//! defined in the sysconfig file included in this project.
//! For the sake of demo an un-realistic tolerance is assumed to generate an
//! error on continuous monitoring.
//!
//! Please refer to the TRM for details on counter seed values to be set.
//! Note : When running in flash configuration it is good to do a reset
//! & restart after loading the example to remove any stale flags/states.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b result - Status of the PLLRAW clock monitoring
//!  - \b cnt0 - Counter0 Value measure when error is generated
//!  - \b cnt1 - Counter1 Value measure when error is generated
//!  - \b valid - Valid0 Value measure when error is generated
//!  - \b esm0IntCount - Indication that ESM Low Priority Int ISR is entered
//!  - \b highestIntr - ESM Global event number of the highest priority
//!       outstanding low priority interrupt that is pending - corresponds to
//!       DCCx_ERR for this example
//!
//
//#############################################################################
// $TI Release: $
// $Release Date: $
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
// SysConfig Contains the assumptions for the DCC error tolerances
// This example uses the internal oscillator1 clock source (Fclk0) to measure 
// the accuracy of the PLL clock (Fclk1)
//
// Calculating Counter0 & Valid Seed Value with +/-1% tolerance.
// INTOSC1 has  frequency variance of +/-3%
//
// If Fclk1>Fclk0, Async. Error (In Clock0 cycles) = 2 + 2*(Fsysclk/Fclk0) = 42
// Digitization error (In Clock0 cycles) = 8
// DCC Error = Async. Error + Digitization error = 50
//
// Window (in Cycles) = (DCC Error) / (0.01 * Tolerance)
// Window = 50 / (0.01 * 1) = 5000
//
// Frequency Error Allowed (In Clock0 Cycles)
//                       = Window * (Allowable Frequency Tolerance (in %) / 100)
//                       = 5000 * (3/100) = 150
//
// Total Error = DCC Error + Frequency Error Allowed = 50 + 150 = 200
//
// Counter0 = Window - Total Error   = 5000 - 200      = 4800
// Valid0   = 2 * Total Error        = 2 * 200         = 400
// Counter1 = Window x (Fclk1/Fclk0) = 5000 * (200/10)  = 100000
//
// To simulate an error, we are configuring count1 seed value as 110000.
//
// Note : Update the values if you are using a different PLL frequency
//

//
// Globals
//
uint32_t result = FAIL, pass_base = myDCC0_BASE , isr_enter_dcc = 0;
uint32_t cnt0 = 0, cnt1 = 0, valid = 0;
uint16_t esm0IntCount = 0;
uint32_t highestIntr;

int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Invoking Sysconfig controlled settings
    //
    Board_init();

    //
    // To simulate an error, we are configuring count1 seed value as 101000.
    //
	DCC_setCounterSeeds(myDCC0_BASE, 4800, 400, 110000);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start the DCC timers
    //
    DCC_enableModule(myDCC0_BASE);

    //
    // Allow time for the dcc module to complete
    //
    DEVICE_DELAY_US(10000);

    //
    // Status of the INTOSC1 clock measurement
    //
    if (!isr_enter_dcc)
    {
        result = FAIL;
    }
    else
    {
        result = PASS;
    }

    ESTOP0;
}

//
// ESM Low priority ISR triggered on a DCC error
//
void INT_myESM_LOWPRI_ISR()
{
    esm0IntCount++;
    
    //
    // Service the highest priority event that caused the interrupt.
    //
    highestIntr = ESM_getHighestLowPriorityInterrupt(ESMCPU1_BASE);

    if (highestIntr == ESM_EVENT_DCC1_ERR)
    {
        uint32_t base;

        //
        // Pass the DCC base address to the ISR
        //
        base = pass_base;

        //
        // Shows that the ISR was called
        //
        isr_enter_dcc = 1;

        if (DCC_getErrorStatus(base) == 1U)
        {
            //
            // Dump the DCC counters into RAM
            //
            cnt0 = DCC_getCounter0Value(base);
            cnt1 = DCC_getCounter1Value(base);
            valid = DCC_getValidCounter0Value(base);

            //
            // Clear the Error flag
            //
            DCC_clearErrorFlag(base);

            //
            // Clear the raw status and deassert the level interrupt.
            //
            ESM_clearRawInterruptStatus(ESMCPU1_BASE, ESM_EVENT_DCC1_ERR);

            //
            // Acknowledge the low priority interrupt.
            // In case there are enabled error events pending then a new pulse is 
            // generated and level interrupt remains asserted, else no new pulse is 
            // generated.
            //
            ESM_ackInterrupt(ESMCPU1_BASE, ESM_LOW_PRIORITY_ERROR_INTERRUPT);
        }
    }
}