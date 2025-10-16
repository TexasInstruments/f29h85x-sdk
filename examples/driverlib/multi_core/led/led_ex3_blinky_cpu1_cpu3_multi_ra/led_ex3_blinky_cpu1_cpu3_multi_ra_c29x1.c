//#############################################################################
//
// FILE:  led_ex3_blinky_cpu1_cpu3_multi_ra_c29x1.c
//
// TITLE: LED Blinky Example
//
//! \addtogroup driver_multicore_example_list
//! <h1> LED Blinky Example</h1>
//!
//! This example demonstrates how to blink a LED using CPU1 and blink another
//! LED using CPU3 (led_ex3_blinky_cpu1_cpu3_multi_ra_c29x3.c).
//!
//! The Resources i.e. GPIOs are assigned to CPU1 and CPU3 in the
//! led_ex3_blinky_cpu1_cpu3_multi_ra.syscfg file. This generates a
//! resourceAllocation.json file at led_ex3_blinky_cpu1_cpu3_multi_ra/RA/syscfg
//! folder. The individual CPU specific syscfg file further configures its
//! pre-allocated GPIO.
//! The individual CPU projects can be built independent of each other.
//!
//! When using CCS for debugging this Multi-core example, after launching the
//! debug session,
//!     - Connect to CPU1 and load the c29x3.out first. (In case of FLASH
//!     configuration, this might not halt at main, ignore this)
//!     - Load c29x1.out next.
//!     - After the program is loaded, run CPU1.
//!     - Once c29x1 releases CPU3 out of reset, the program stops.
//!     - Connect to CPU3 target now. c29x3.out would have started execution
//!     as soon as it is released from reset.
//!     - In case of RAM configuration, load the symbols for CPU3.
//!     - In case of FLASH, do a Power-on-Reset, connect to CPU1/ CPU3 and load
//!     the respective symbols.
//!
//! \note When importing the Project in CCS 20.3.0, do verify if the
//! Resource allocation specific flags are set. If not, update the Project
//! Properties -> Build -> Tools -> SysConfig -> Miscellaneous -> Other flags
//! to include the appropriate flag.
//! For projects having the .syscfg file in "Define Resource Allocations" mode,
//! add the following flag:
//!      --enableResourceAllocationSetup
//! For CPUx projects having .syscfg files in "Configure using Predefined
//! Resource Allocations" mode, add the following flag:
//!      --resourceAllocation <path to resourceAllocation.json file>
//!   for example,
//!      --resourceAllocation ..\..\led_ex3_blinky_cpu1_cpu3_multi_ra\RA\syscfg\resourceAllocation.json
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

#ifdef _FLASH
    #define CPU3_RESET_VECTOR   0x10401000U
    #define CPU3_NMI_VECTOR     0x10401040U
#else
    #define CPU3_RESET_VECTOR   0x20110000U
    #define CPU3_NMI_VECTOR     0x20110040U
#endif

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
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Defines the address and link to which CPU3 Boots
    //
    SSU_configBootAddress(SSU_CPU3, CPU3_RESET_VECTOR, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU3, CPU3_NMI_VECTOR, SSU_LINK2);

    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU3, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU3Reset() == 0x1U);

    //
    // CPU3 is out of reset now. Connect to CPU3 and load the .out
    //
    ESTOP0;

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG31);

    //
    // Loop Forever
    //
    while(1)
    {
        //
        // Turn on LED
        //
        GPIO_writePin(CPU1_LED_GPIO, 0);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(1000000);

        //
        // Turn off LED
        //
        GPIO_writePin(CPU1_LED_GPIO, 1);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(1000000);
    }
}


//
// End of File
//