//#############################################################################
//
// FILE:   empty_driverlib_project_secure.c
//
//! \addtogroup driver_example_list
//! <h1>Empty Project Example with Security configurations</h1>
//!
//! This example is an empty project setup for Driverlib development with
//! Security configurations
//! The following Security Settings can be mofified in syscfg:
//!     ->  SSU Mode
//!     ->  Boot Settings
//!         ->  Error Status Pin (Default is GPIO219)
//!         ->  Boot pin configuraton
//!     ->  Flash Update Owner
//!     ->  Flash Write/Erase Protections
//!     ->  SSU Setup
//! After making changes to the security settings follow the below steps
//!     ->  Save syscfg
//!     ->  Rebuild example project
//!     ->  Make sure the current BANKMODE is 0
//!     ->  Load the example.out
//!     ->  Power cycle EVM or issue XRSn
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
// Main
//
int main(void)
{
    //
    // Enable LINK2 AP override
    //
    SSU_enableLink2APOverride(SSU_CPU1);

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();

    //
    // Disable LINK2 AP override
    //
    SSU_disableLink2APOverride(SSU_CPU1);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();


    while(1)
    {

    }
}

//
// End of File
//
