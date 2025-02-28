//#############################################################################
//
// FILE:  ssuIpc_ex1_basic_cpu1_cpu3_multi_starter_c29x1.c
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
//!  CPU1 SSU Configurations:
//!  APRs   - ipc_shared, APR_RESERVED_sign_CPU1 (CERT), APR_FlashLoad_CPU1, LINK2_codeAPR_Flash, 
//!           LINK2_codeAPR_RAM, LINK2_dataAPR_RW, LINK2_dataAPR_RO, STACK1_stackmem_apr, STACK2_stackmem_apr
//!  LINKs  - LINK1, LINK2
//!  STACKs - STACK1, STACK2
//!
//! Refer to linker.cmd files and Memory Allocation tool (View > Memory Allocation) for more insight on memory usage.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - pass - Indicates if the test was successful.
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
#include "ssu_config.h"

//
// Defines
//
#ifdef _FLASH
    #define CPU3_RESET_VECTOR   0x10400000U
    #define CPU3_NMI_VECTOR     0x10400040U
#else
    #define CPU3_RESET_VECTOR   0x20110000U
    #define CPU3_NMI_VECTOR     0x20110040U
#endif
#define IPC_CMD_READ_MEM        0x1001
#define TEST_PASS               0x5555
#define TEST_FAIL               0xAAAA
#define DATA_COUNT              64

//
//  Globals
//
uint32_t pass;

//
// Main
//
int main(void)
{
    uint32_t cnt;
    //
    // Enable LINK2 AP override
    //
    SSU_enableLink2APOverride(SSU_CPU1);

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Disable LINK2 AP override
    //
    SSU_disableLink2APOverride(SSU_CPU1);

    //
    // Defines the address at which CPU3 Boots
    //
    SSU_configBootAddress(SSU_CPU3, (uint32_t)CPU3_RESET_VECTOR, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU3, CPU3_NMI_VECTOR, SSU_LINK2);

    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU3, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU3Reset() == 0x1U);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // CPU3 is out of reset now. Connect to CPU3 and load the symbols.
    //
    ESTOP0;

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
