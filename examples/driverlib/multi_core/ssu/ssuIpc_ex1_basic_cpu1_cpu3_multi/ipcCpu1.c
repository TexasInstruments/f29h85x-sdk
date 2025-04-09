//#############################################################################
//
// FILE:  ipcCpu1.c
//
// TITLE: SysConfig IPC example with interrupt
//
//! \addtogroup driver_dual_example_list
//! <h1> IPC basic message passing example with interrupt </h1>
//!
//! This example demonstrates how to configure IPC and pass information from
//! C29x1 to C29x3 core without message queues.
//!
//! When using CCS for debugging this Multi-core example, after launching the
//! debug session,
//!     - Connect to CPU1 and load only the c29x1.out.
//!     - After the program is loaded, run CPU1.
//!     - Once c29x1 configures and releases CPU3 out of reset, the program
//!     stops.
//!     - Connect to CPU3 target now. c29x3.out would have started execution
//!     as soon as it is released from reset.
//!     - In case of RAM configuration, restart the CPU3 target and load the
//!     symbols.
//!
//! \note For FLASH configuration, this example is run in FLASH BANKMODE2,
//! where CPU3 has access to FLASH (FRI-2). Refer to the Flash Plugin
//! documentation to know about changing FLASH BANKMODEs and more.
//! Additionally, the CPAx and CDAx RAMs are used for allocating various
//! RAM sections.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - pass
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
#include "ssu_config.h"

//
// Defines
//
#define IPC_CMD_READ_MEM    0x1001
#define TEST_PASS           0x5555
#define TEST_FAIL           0xAAAA
#define DATA_COUNT          64

//
//  Globals
//
uint32_t pass;

void ipcCpu1(void) __attribute__((c29_protected_call))
{
    uint32_t cnt;
    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG31);

    //
    // Fill in the data to be sent
    //
    for(cnt = 0; cnt < DATA_COUNT; cnt++)
    {
        HWREGB(ipc_shared_START_ADDR + cnt) = cnt; 
    }

    //
    // Send a message without message queue
    // Length of the data to be read is passed as data.
    //
    IPC_sendCommand(
                IPC_CPU1_L_CPU3_R_CH0,
                IPC_FLAG0,
                IPC_CMD_READ_MEM,
                (uint32_t)ipc_shared_START_ADDR,
                DATA_COUNT);

    //
    // Wait for acknowledgment
    //
    IPC_waitForAck(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG0);

    //
    // Read response
    //
    if(IPC_getResponse(IPC_CPU1_L_CPU3_R_CH0) == TEST_PASS)
    {
        pass = 1;
    }
    else
    {
        pass = 0;
    }

    //
    // End of example. Loop forever
    //
    while(1);
}

//
// End of File
//