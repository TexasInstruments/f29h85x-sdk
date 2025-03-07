//#############################################################################
//
// FILE:   sysctl_ex1_missing_clock_detection.c
//
// TITLE:  Missing clock detection
//
//! \addtogroup driver_example_list
//! <h1> Missing clock detection (MCD) </h1>
//!
//! This example demonstrates the missing clock detection functionality and
//! the way to handle it.
//! Once the MCD is simulated by disconnecting the OSCCLK to the MCD module
//! an NMI would be generated. This NMI determines that an MCD was generated
//! due to a clock failure which is handled in the ISR.
//!
//! Before an MCD the clock frequency would be as per device initialization (200Mhz).
//! Post MCD the frequency would move to 10Mhz or INTOSC1.
//!
//! The example also shows how we can lock the PLL after missing clock,
//! detection, by first explicitly switching the clock source to INTOSC1,
//! resetting the missing clock detect circuit and then re-locking the PLL.
//! Post a re-lock the clock frequency would be 200Mhz but using the INTOSC1 as
//! clock source.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b fail - Indicates that a missing clock was either not detected or was
//!       not handled correctly.
//!  - \b mcd_clkfail_isr - Indicates that the missing clock failure caused an
//!       NMI to be triggered and called an the ISR to handle it.
//!  - \b mcd_detect - Indicates that a missing clock was detected.
//!  - \b result - Status of a successful handling of missing clock detection
//!
//
//#############################################################################
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
// Globals
//
volatile uint32_t isr_count = 0;
volatile uint32_t fail = 0;

//
// Defines
//
#define PASS 0
#define FAIL 1

volatile uint32_t result = FAIL;


//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();


    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Check the PLL System clock before the Missing clock detection
    // is simulated. It should be same as that set by Device_init().
    //
    if(SysCtl_getClock(DEVICE_OSCSRC_FREQ) != DEVICE_SYSCLK_FREQ)
        fail++;

    //
    // Enable the missing clock detection (MCD) Logic as a precaution.
    // The is continuously active, unless the MCD was disabled previously
    //
    SysCtl_enableMCD();

    //
    // Simulate a missing clock detection
    //
    SysCtl_disconnectMCDClockSource();

    //
    // Wait till the NMI is fired on clock failure
    //
    while(isr_count == 0);

    //
    // Status of a successful handling of missing clock detection
    //
    if (fail)
    {
        result = FAIL;
    }
    else
    {
        result = PASS;

    }
    while(1);
}

//
// NMI ISR - The interrupt service routine called when the NMI
//           is generated on clock failure detection
//
void myNMI_ISR(void)
{
    isr_count++;

    //
    // Check the MCD status
    //
    if(SysCtl_isMCDClockFailureDetected() == false)
        fail++;

    //
    // Check the ESM status
    //
    if(ESM_getInterruptStatus(ESMCPU1_BASE, ESM_EVENT_CLOCKFAIL) == false)
        fail++;

    //
    // Check the PLL System clock after the Missing clock detection
    // is simulated. It should be equal to INTOSC1(10Mhz).
    //
    if(SysCtl_getClock(DEVICE_OSCSRC_FREQ) != SYSCTL_DEFAULT_OSC_FREQ)
        fail++;

    //
    // To lock the PLL after missing clock detection, we first explicitly
    // switch the clock source to INTOSC1, reset the missing clock detect
    // circuit and then re-lock the PLL.
    //
    // Configure oscillator source to INTOSC1
    //
    SysCtl_selectOscSource(SYSCTL_OSCSRC_OSC1);

    //
    // Re-connect missing clock detection clock source to stop simulating clock
    // failure
    //
    SysCtl_connectMCDClockSource();
    SysCtl_enableMCD();

    //
    // Reset the missing clock detection logic after clock failure
    //
    SysCtl_resetMCD();

    //
    // Set up PLL control and clock dividers using INTOSC1 as clock source
    //
	SysCtl_setClock(SYSCTL_OSCSRC_OSC1, SYSCTL_PLL_ENABLE, SYSCTL_REFDIV_1,
					SYSCTL_IMULT_40, SYSCTL_ODIV_2, SYSCTL_SYSDIV_1, DCC1_BASE);

    //
    // Check the PLL System clock after the Missing clock detection
    // is cleared and handled using INTOSC1 as clock source.
    //
    if(SysCtl_getClock(DEVICE_OSCSRC_FREQ) != DEVICE_SYSCLK_FREQ)
        fail++;

    //
    // Clear the ESM status
    //
    ESM_clearRawInterruptStatus(ESMCPU1_BASE, ESM_EVENT_CLOCKFAIL);
    ESM_writeEOIVector(ESMCPU1_BASE, ESM_EOI_HIGH_PRIORITY_ERROR_INTERRUPT);
}


//
// End of File
//
