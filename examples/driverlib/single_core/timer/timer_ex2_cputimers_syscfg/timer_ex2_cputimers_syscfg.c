//#############################################################################
//
// FILE:   timer_ex2_cputimers_syscfg.c
//
// TITLE:  CPU Timers Example
//
//! \addtogroup driver_example_list
//! <h1> CPU Timers </h1>
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
#include "board.h"

//
// Globals
//
uint16_t cpuTimer0IntCount;
uint16_t cpuTimer1IntCount;
uint16_t cpuTimer2IntCount;


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
    // Board Initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {
    }
}

//
// ISRs for the timer interrupts
//
void cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;
}

void cpuTimer1ISR(void)
{
    cpuTimer1IntCount++;
}

void cpuTimer2ISR(void)
{
    cpuTimer2IntCount++;
}


//
// End of File
//