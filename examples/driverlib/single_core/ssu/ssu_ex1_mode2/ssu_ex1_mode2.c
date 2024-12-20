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
//! After loading the example.out power cycle EVM to run and debug the example
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