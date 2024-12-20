//#############################################################################
//
// FILE:   watchdog_ex1_service.c
//
// TITLE:  Servicing Watchdog Example
//
//! \addtogroup driver_example_list
//! <h1> Watchdog </h1>
//!
//! This example shows how to service the watchdog or generate a watchdog
//! interrupt using the watchdog. By default the example will generate a
//! watchdog interrupt. To service the watchdog and not generate the interrupt,
//! uncomment the SysCtl_serviceWatchdog() line in the main for loop.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - ISRCount - The number of times entered into the watchdog ISR
//!  - loopCount - The number of loops performed while not in ISR
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
// Globals
//
uint32_t ISRCount;
uint32_t loopCount;


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
    // Board Initialization
    //
    Board_init();

    //
    // Clear the counters
    //
    ISRCount = 0;
    loopCount = 0;

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop Forever
    //
    for(;;)
    {
        loopCount++;

        //
        // Uncomment SysCtl_serviceWatchdog to just loop here.
        // Comment SysCtl_serviceWatchdog to have watchdog timeout and trigger
        // an interrupt signal to execute the wakeupISR
        //
        // SysCtl_serviceWatchdog();
    }
}

//
// watchdogISR ISR - The interrupt service routine called when the watchdog
//                   triggers the wake interrupt signal
//
void watchdogISR(void)
{
    ISRCount++;
}

//
// End of File
//