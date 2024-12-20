//#############################################################################
//
// FILE:  led_ex2_blinky_cpu1_cpu2_cpu3_multi_c29x3.c
//
// TITLE: LED Blinky Example
//
//! \addtogroup driver_multicore_example_list
//! <h1> LED Blinky Example (CPU3) </h1>
//!
//! This example demonstrates how to configure LEDs using CPU1 and blink
//! two LEDs using CPU2 (led_ex2_blinky_cpu1_cpu2_cpu3_multi_c29x2.c)
//! and CPU3 (led_ex2_blinky_cpu1_cpu2_cpu3_multi_c29x3.c).
//!
//! When using CCS for debugging this Multi-core example, after launching the
//! debug session, 
//!     - Connect to CPU1 and load only the c29x1.out.
//!     - After the program is loaded, run CPU1.
//!     - Once c29x1 disables lockstep, configures and releases CPU2 & CPU3 out
//!     of reset, the program stops.
//!     - Connect to the CPU2 target now. c29x2.out would have started execution
//!     as soon as it is released from reset.
//!     - Connect to the CPU3 target now. c29x3.out would have started execution
//!     as soon as it is released from reset.
//!     - In case of RAM configuration, restart CPU2, CPU3 targets and load the
//!     symbols.
//!
//! Note: Since CPU2 does not have FLASH access, the CPU2 application code is
//! loaded to CPU1's FLASH, which is copied to CPU2 RAM by the CPU1 application.
//! The CPU3 application code is loaded to its Flash (FRI-2) in FLASH BANKMODE2.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
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

//###########################################################################

//
// Included Files
//
#include "board.h"

#define DEVICE_SYSCLK_FREQ		200000000

//
// Main
//
int main(void)
{
    //
    // Initialize peripheral clocks and interrupts
    //
    Device_init();
    
    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG31);

    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Turn on LED
        //
        GPIO_writePin(CPU3_LED, 1);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(500000);

        //
        // Turn off LED
        //
        GPIO_writePin(CPU3_LED, 0);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(500000);
    }
}


//
// End of File
//
