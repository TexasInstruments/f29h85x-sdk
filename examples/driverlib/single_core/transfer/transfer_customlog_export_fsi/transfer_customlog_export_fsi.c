//#############################################################################
//
// FILE:   transfer_customlog_export_fsi.c
//
// TITLE:  Transfer: Custom Logger Solution
//
//! \addtogroup driver_example_list
//! <h1> GUI based solution for data logging (one direction) </h1>
//!
//! This example demonstrates how to use SysConfig to enable datalogging
//! on our C29x devices. To enable this example, make sure to go to
//! Build -> Variables and set GUI_SUPPORT to value of 1.
//! This will create the GUI in CCS which can be opened under 
//! View -> Plugins -> transfer_customlog_export_fsi
//! If there are no plugins after buliding, 
//! please reload the window by doing Help -> Reload Window
//! Please select the correct COM port in the GUI by clicking "Options"
//! then "Serial Port Settings"
//! In this example, we are using fsi to export data out of the device.
//! If you're using a launchpad, you can enable board components to select
//! the correct fsi base.
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
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "export/export_log.h"


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
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Logging Inits
    //
    EXPORT_init();
    EXPORTLOG_init();

    while(1)
    {
        DEVICE_DELAY_US(1000000);

        EXPORTLOG_log("Logging entry 1");
        EXPORTLOG_log("Next log entry 2");
        EXPORTLOG_log("last entry 3");
    }
}


//
// End of File
//
