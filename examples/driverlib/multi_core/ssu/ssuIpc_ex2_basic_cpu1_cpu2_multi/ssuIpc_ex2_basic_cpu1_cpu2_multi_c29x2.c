//#############################################################################
//
// FILE:  ssuIpc_ex1_basic_cpu1_cpu3_multi_c29x3.c
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
//!  - None.
//!
//
//#############################################################################
// $Copyright: $
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
