//#############################################################################
//
// FILE:  ssuIpc_ex2_basic_cpu1_cpu2_multi_c29x2.c
//
// TITLE: SysConfig IPC example with interrupt
//
//! \addtogroup driver_dual_example_list
//! <h1> IPC basic message passing example with interrupt </h1>
//!
//! This example demonstrates how to configure IPC and pass information from
//! C29x1 to C29x2 core without message queues.
//!
//! Follow these steps to use CCS to debug this multi-core example. After 
//! launching the debug session:
//!     1. Connect to CPU1.
//!     2. Using the Flash Plug-In, 
//!         - In 'User Config Settings', Program FLASH BANKMODE to BANKMODE2, if not already done.
//!         - In 'Download Settings', Unselect ‘Verify Flash after Program (SSU Mode 1 Usage Only)’, if not already done.
//!         - In 'Download Settings', Unselect ‘Perform Blank Check before loading data to Flash memory (SSU Mode 1 Usage Only)’, if not already done.
//!         - In 'NonMain Erase Settings', Select 'Allow NonMain Flash erase before loading data to Flash memory' (click checkbox), if not already done. 
//!          Refer to Flash Plug-In documentation for further instructions.
//!     3. Issue an XRSN to the device.
//!     4. Load only the CPU1.out.
//!     5. After the program is loaded, issue an XRSN to the device. 
//!        Connect to CPU1 and load symbols. 
//!     6. At this point, CPU1 configures and releases CPU2 out of reset. CPU2 program
//!     has started execution. To further debug, connect to CPU2 and load the symbols. 
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
#include "inc/hw_types.h"

//
//  Defines
//
#define IPC_CMD_READ_MEM        0x1001
#define TEST_PASS               0x5555
#define TEST_FAIL               0xAAAA

//
//  IPC isr
//
__attribute__((interrupt("RTINT"))) void INT_IPC_1_1_ISR();

//
// Main
//
int main(void)
{
    //
    // Enable LINK2 AP override
    //
    SSU_enableLink2APOverride(SSU_CPU2);

    //
    // Interrupt initialization
    //
    Device_init();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Disable LINK2 AP override
    //
    SSU_disableLink2APOverride(SSU_CPU2);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU2_L_CPU1_R_CH0, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU2_L_CPU1_R_CH0, IPC_FLAG31);

    //
    // Loop forever. Wait for IPC interrupt
    //
    while(1);
}

//
// IPC ISR for Flag 0.
// C29x core sends data using Flag 0
//
void INT_IPC_1_1_ISR()
{
    uint32_t    cnt;
    uint32_t    command;
    uint32_t    addr;
    uint32_t    data;
    bool        status = false;

    //
    // Read the command
    //
    IPC_readCommand(IPC_CPU2_L_CPU1_R_CH0, IPC_FLAG0, &command, &addr, &data);

    if(command == IPC_CMD_READ_MEM)
    {
        status = true;

        //
        //  Read and compare data
        //
        for(cnt = 0U;cnt < data;cnt++)
        {
            if(HWREGB(addr + cnt) != cnt)
            {
                status = false;
            }
        }
    }

    //
    // Send response to C29x core
    //
    if(status)
    {
        IPC_sendResponse(IPC_CPU2_L_CPU1_R_CH0, TEST_PASS);
    }
    else
    {
        IPC_sendResponse(IPC_CPU2_L_CPU1_R_CH0, TEST_FAIL);
    }

    //
    // Acknowledge the flag
    //
    IPC_ackFlagRtoL(IPC_CPU2_L_CPU1_R_CH0, IPC_FLAG0);
}

//
// End of File
//
