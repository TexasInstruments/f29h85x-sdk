//#############################################################################
//
// FILE:  empty_project_dummy_cert_multi_c29x1.c
//
// TITLE: Empty Multi-core Example with Dummy Certificate (CPU1|CPU2|CPU3)-CPU1
//
//! \addtogroup driver_multicore_example_list
//! <h1> Empty Multi-core Example with Dummy Certificate (CPU1|CPU2|CPU3) </h1>
//!
//! This is an empty project that can be used to develop a multi-core
//! application. It does the required init configurations in each of the CPUs.
//!
//! CPU1 disables lockstep to use CPU2, releases CPU2 & CPU3 out of reset to
//! the reset vectors set in empty_project_dummy_cert_multi_c29x1.c file. CPU2
//! and CPU3 application code are part of empty_project_dummy_cert_multi_c29x2
//! and empty_project_dummy_cert_multi_c29x3 projects respectively.
//!
//! This example demonstrates the usage of dummy certificate
//! ->  A pre defined dummy certificate is available for CPU1 and CPU3 FLASH
//!     build configurations
//! ->  The dummy certificate is updated with the size of the respective binary
//!     during post build step
//! ->  The updated dummy certificate is then included into the example program
//!
//! The application on all the CPU cores are then combined into a single .out
//! file - empty_project_dummy_cert_multi_c29x1.out
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

#define CPU2_RESET_VECTOR       0x20108000U
#define CPU2_NMI_VECTOR         0x20108040U

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
    // Boot CPU2
    //
    SSU_configBootAddress(SSU_CPU2, CPU2_RESET_VECTOR, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU2, CPU2_NMI_VECTOR, SSU_LINK2);
    //
    // Bring CPU2 out of reset. Wait for CPU2 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU2, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU2Reset() == 0x1U);

    //
    // Boot CPU3
    //
    SSU_configBootAddress(SSU_CPU3, CPU3_RESET_VECTOR, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU3, CPU3_NMI_VECTOR, SSU_LINK2);
    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU3, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU3Reset() == 0x1U);

    //
    // CPU2 and CPU3 are out of reset now.
    //
    ESTOP0;

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Synchronize the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU2_R_CH0, IPC_FLAG31);
    IPC_sync(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG31);

    //
    // Loop Forever
    //
    while(1)
    {

    }
}


//
// End of File
//