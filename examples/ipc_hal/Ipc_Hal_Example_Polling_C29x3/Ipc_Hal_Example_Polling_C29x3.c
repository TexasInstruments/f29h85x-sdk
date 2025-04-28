//#############################################################################
//
// FILE: Ipc_Hal_Example_Polling_C29x3.c
//
// TITLE: MCAL-SDK IPC HAL example with polling
//
//! IPC HAL basic message passing example with polling
//!
//! This example demonstrates how to configure IPC and pass information between
//! C29x1 running MCAL to C29x3 running SDK core. C29x1 running MCAL transmits a message "hello" and 
//! C29x3 running SDK receives the message, appends the string " CPU1" to it, and send it back the C29x1.
//! This example should be ran on C29x3 with MCAL example: Cdd_Ipc_Example_Polling_C29x1 running on C29x1.
//!
//! When using CCS for debugging this Multi-core example, after launching the
//! debug session,
//!     - Connect to CPU1 and load only the C29x1_merged.out.
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
#include "ipc_hal.h"

//
// Main
//
int main(void)
{
    //
    // Interrupt initialization
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
    IPC_HAL_sync(Ipc_Cpu1);
    
    //
    // Loop forever. Wait for IPC message
    //
    while(true)
    {
        IPC_HAL_pollInstances();
    }
}

void Ipc_Hal_exampleUserCallbackFunction(const IPC_InfoType ipcData)
{
    uint8_t cpu1String[] = " CPU1";
    uint8_t cpu1StringLength = sizeof(cpu1String) - 1;
    uint8_t newData[IPC_HAL_MAX_SIZE];
    uint8_t dataLength = ipcData.Length;
    uint8_t dataindex;
    uint8_t cpu3dataindex;
     
    // Copy the received data
    for (dataindex = 0; dataindex < dataLength; dataindex++)
    {
        newData[dataindex] = ipcData.DataPtr[dataindex];
    }

    // Append the CPU1 string
    cpu1StringLength = sizeof(cpu1String) - 1; // exclude null terminator
    for (cpu3dataindex = 0; cpu3dataindex < cpu1StringLength; cpu3dataindex++,dataindex++)
    {
        if (dataindex < IPC_HAL_MAX_SIZE) {
            newData[dataindex] = cpu1String[cpu3dataindex];
        }
    }
    

    // Transmit the new data
    IPC_InfoType newIpcData = {newData, dataindex};
    IPC_HAL_transmit(IPC_HAL_TX_CH1, &newIpcData);

}

//
// End of File
//
