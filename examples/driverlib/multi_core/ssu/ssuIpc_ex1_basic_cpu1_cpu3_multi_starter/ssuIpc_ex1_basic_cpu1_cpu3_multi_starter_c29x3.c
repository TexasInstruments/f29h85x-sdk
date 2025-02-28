//#############################################################################
//
// FILE:  ssuIpc_ex1_basic_cpu1_cpu3_multi_starter_c29x3.c
//
// TITLE: Starter SysConfig IPC example with interrupt
//
//! \addtogroup driver_dual_example_list
//! <h1> Simple IPC messaging between two CPUs (with interrupts) configured with minimum SSU settings </h1>
//!
//! This example demonstrates how to configure IPC and pass information from
//! C29x1 to C29x3 core without using message queues and configure the SSU. This example
//! should be used to get started with the SSU as it uses the minimum APR/LINK/STACK configuration.
//!
//! Follow these steps to use CCS to debug this multi-core example. After 
//! launching the debug session:
//!     1. Connect to CPU1.
//!     2. Using the Flash Plug-In, 
//!         - In 'User Config Settings', Program FLASH BANKMODE to BANKMODE 2, if not already done.
//!         - In 'Download Settings', Unselect ‘Verify Flash after Program (SSU Mode 1 Usage Only)’, if not already done.
//!         - In 'Download Settings', Unselect ‘Perform Blank Check before loading data to Flash memory (SSU Mode 1 Usage Only)’, if not already done.
//!         - In 'NonMain Erase Settings', Select 'Allow NonMain Flash erase before loading data to Flash memory' (click checkbox), if not already done. 
//!          Refer to Flash Plug-In documentation for further instructions.
//!     4. Load only the CPU1.out.
//!     5. After the program is loaded, disconnect from target and power cycle the EVM. 
//!        Connect to CPU1 and load symbols. 
//!     6. At this point, CPU1 configures and releases CPU3 out of reset. CPU3 program
//!     has started execution. Connect to CPU3 and load the symbols. 
//!
//! \note For FLASH configuration, this example is run in FLASH BANKMODE2,
//! where CPU3 has access to FLASH (FRI-2). Refer to the Flash Plugin
//! documentation to know about changing FLASH BANKMODEs and more.
//! Additionally, the CPAx and CDAx RAMs are used for allocating various
//! RAM sections.
//!
//!  CPU3 SSU Configurations:
//!  APRs   - APR_FlashLoad_CPU3, LINK2_codeAPR_Flash, LINK2_codeAPR_RAM, 
//!           LINK2_dataAPR_RW, LINK2_dataAPR_RO, STACK1_stackmem_apr, STACK2_stackmem_apr
//!  LINKs  - LINK1, LINK2
//!  STACKs - STACK1, STACK2
//!
//! Refer to linker.cmd files and Memory Allocation tool (View > Memory Allocation) for more insight on memory usage.
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
#define IPC_CMD_READ_MEM    0x1001
#define TEST_PASS           0x5555
#define TEST_FAIL           0xAAAA

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
    SSU_enableLink2APOverride(SSU_CPU3);

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
    SSU_disableLink2APOverride(SSU_CPU3);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG31);

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
    IPC_readCommand(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG0, &command, &addr, &data);

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
        IPC_sendResponse(IPC_CPU3_L_CPU1_R_CH0, TEST_PASS);
    }
    else
    {
        IPC_sendResponse(IPC_CPU3_L_CPU1_R_CH0, TEST_FAIL);
    }

    //
    // Acknowledge the flag
    //
    IPC_ackFlagRtoL(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG0);
}

//
// End of File
//
