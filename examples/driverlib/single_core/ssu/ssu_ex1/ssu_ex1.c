//#############################################################################
//
// FILE:   ssu_ex1.c
//
// TITLE:  SSU Example
//
//! \addtogroup driver_example_list
//! <h1> SSU </h1>
//!
//! This example configures CPU Timer0, 1, and 2 and increments
//! a counter each time the timer asserts an interrupt.
//!
//! The interrupt priorities are configured as follows :
//!   - RTINT Threshold = 15
//!   - Timer 0 Interrupt priority = 10 -> RTINT
//!   - Timer 1 Interrupt priority = 20 -> INT
//!   - Timer 2 Interrupt priority = 30 -> INT
//!
//! Sysconfig inserts the required attributes to the ISR functions to inform
//! the compiler that the function is an interrupt / realtime interrupt.
//!
//! Follow these steps to use CCS to debug this multi-core example. After
//! launching the debug session:
//!     1. Connect to CPU1.
//!     2. Using the Flash Plug-In,
//!         - In 'User Config Settings', Program FLASH BANKMODE to BANKMODE0, if not already done.
//!         - In 'Download Settings', Unselect 'Verify Flash after Program (SSU Mode 1 Usage Only)', if not already done.
//!         - In 'Download Settings', Unselect 'Perform Blank Check before loading data to Flash memory (SSU Mode 1 Usage Only)', if not already done.
//!         - In 'NonMain Erase Settings', Select 'Allow NonMain Flash erase before loading data to Flash memory' (click checkbox), if not already done.
//!          Refer to Flash Plug-In documentation for further instructions.
//!     3. Issue an XRSN to the device.
//!     4. Load the CPU1.out.
//!     5. After the program is loaded, issue an XRSN to the device.
//!        Connect to CPU1 and load symbols.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - cpuTimer0IntCount
//! - cpuTimer1IntCount
//! - cpuTimer2IntCount
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
#include "app.h"

void systemInit(void);

//
// Main
//
__attribute__((section(".text.main")))
int main(void)
{
    //
    // Initialize system configuration
    //
    systemInit();

    //
    // Loop.
    //
    for(;;)
    {
    }
}