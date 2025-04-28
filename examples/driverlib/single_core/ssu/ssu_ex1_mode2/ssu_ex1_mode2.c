//#############################################################################
//
// FILE:   ssu_ex1_mode2.c
//
// TITLE:  SSU MODE2 Example
//
//! \addtogroup driver_example_list
//! <h1> SSU </h1>
//!
//! This example configures CPU Timer0, 1, and 2 and increments
//! a counter each time the timer asserts an interrupt.
//!
//! The interrupt priorities are configured as follows :
//!   - RTINT Threshold = 15
//!   - Timer 0 Interrupt priority = 10 -> RTINT
//!   - Timer 1 Interrupt priority = 20 -> INT
//!   - Timer 2 Interrupt priority = 30 -> INT
//!
//! Sysconfig inserts the required attributes to the ISR functions to inform
//! the compiler that the function is an interrupt / realtime interrupt.
//!
//! Follow these steps to use CCS to debug this multi-core example. After
//! launching the debug session:
//!     1. Connect to CPU1.
//!     2. Using the Flash Plug-In,
//!         - In 'User Config Settings', Program FLASH BANKMODE to BANKMODE0, if not already done.
//!         - In 'Download Settings', Unselect 'Verify Flash after Program (SSU Mode 1 Usage Only)', if not already done.
//!         - In 'Download Settings', Unselect 'Perform Blank Check before loading data to Flash memory (SSU Mode 1 Usage Only)', if not already done.
//!         - In 'NonMain Erase Settings', Select 'Allow NonMain Flash erase before loading data to Flash memory' (click checkbox), if not already done.
//!          Refer to Flash Plug-In documentation for further instructions.
//!     3. Issue an XRSN to the device.
//!     4. Load the CPU1.out.
//!     5. After the program is loaded, issue an XRSN to the device.
//!        Connect to CPU1 and load symbols.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - cpuTimer0IntCount
//! - cpuTimer1IntCount
//! - cpuTimer2IntCount
//!
//
//#############################################################################

//
// Included Files
//
#include "app.h"

void systemInit(void);

//
// Main
//
__attribute__((section(".text.main")))
int main(void)
{
    //
    // Initialize system configuration
    //
    systemInit();

    //
    // Loop.
    //
    for(;;)
    {
    }
}