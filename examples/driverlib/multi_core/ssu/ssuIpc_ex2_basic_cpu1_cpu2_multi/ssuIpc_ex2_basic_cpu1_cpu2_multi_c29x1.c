//#############################################################################
//
// FILE:  ssuIpc_ex1_basic_cpu1_cpu3_multi_c29x1.c
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
//!     -   If the current BANKMODE is not 2 then change it to 2, refer to Flash plug in
//!         documentation to change BANKMODE
//!     -   Load only the CPU1.out
//!     -   When the CPU1.out loading is completed power cycle the EVM
//!     -   Connect to CPU1 and or CPU3, load the sysmbols
//!     -   Debug the example
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - pass
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
#define CPU2_RESET_VECTOR       0x20100000U
#define CPU2_NMI_VECTOR         0x20100040U
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
    SSU_configBootAddress(SSU_CPU2, (uint32_t)CPU2_RESET_VECTOR, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU2, CPU2_NMI_VECTOR, SSU_LINK2);

    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU2, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU2Reset() == 0x1U);

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
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU2_R_CH0, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU2_R_CH0, IPC_FLAG31);

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
                IPC_CPU1_L_CPU2_R_CH0,
                IPC_FLAG0,
                IPC_CMD_READ_MEM,
                (uint32_t)ipc_shared_START_ADDR,
                DATA_COUNT);

    //
    // Wait for acknowledgment
    //
    IPC_waitForAck(IPC_CPU1_L_CPU2_R_CH0, IPC_FLAG0);

    //
    // Read response
    //
    if(IPC_getResponse(IPC_CPU1_L_CPU2_R_CH0) == TEST_PASS)
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