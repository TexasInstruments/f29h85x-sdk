//#############################################################################
//
// FILE:  dcc_ex2_single_shot_measurement.c
//
// TITLE: DCC Single shot Clock measurement
//
//! \addtogroup driver_example_list
//! <h1>DCC Single shot Clock measurement</h1>
//!
//! This program demonstrates Single Shot measurement of the INTOSC1
//! clock post trim using INTOSC2 as the reference clock.
//!
//! The Dual-Clock Comparator Module 1 is used for the clock measurement.
//! The clocksource0 is the reference clock (Fclk0 = 10Mhz) and the
//! clocksource1 is the clock that needs to be measured (Fclk1 = 10Mhz).
//! Since the frequency of clock1 needs to be measured, an initial seed is
//! set to the max value of the counter.
//!
//! Please refer to the TRM for details on counter seed values to be set.
//!
//! \b External \b Connections \n
//!   - None
//!
//! \b Watch \b Variables \n
//!  - \b result - Status if the INTOSC1 clock measurement completed
//!       successfully.
//!  - \b meas_freq1 - measured clock frequency, in this case for INTOSC1.
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
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define PASS 0
#define FAIL 1

//
// Globals
//
volatile uint32_t result = FAIL;
volatile float32_t meas_freq1 = 0.0F;

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
    // Measure the frequency of INTOSC1 using INTOSC2 as reference clock
    // Clk1 = INTOSC1
    // CLk2 = INTOSC2 (Frequency = 10MHz)
    // Tolerance = 1%
    // Allowable Frequency Tolerance = 0% (update as per the error in the frequency)
    // SysClk Freq = 200MHz
    //
    meas_freq1 = DCC_measureClockFrequency(DCC1_BASE,
                                          DCC_COUNT1SRC_INTOSC1,
                                          DCC_COUNT0SRC_INTOSC2, 10.0F,
                                          1.0F, 0.0F, 200.0F);

    //
    // Measured clock frequency of INTOSC1.
    // Value of INTOSC1 freq can be checked in the device datasheet
    //
    if ((meas_freq1 >= 9.7F) && (meas_freq1 <= 10.3F))
    {
        result = PASS;
    }
    else
    {
        result = FAIL;
    }

    ESTOP0;
}
