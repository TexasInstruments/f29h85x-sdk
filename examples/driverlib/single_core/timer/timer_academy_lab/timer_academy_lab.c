//#############################################################################
//
// FILE:    timer_academy_lab.c
//
// TITLE:   Timer Academy Lab 
//
//! \addtogroup driver_example_list
//! <h1> Timer Academy Lab </h1>
//!
//! This example demonstrates how to use a CPU Timer to blink two LEDs. 
//! The timer and the LED GPIOs are each configured wthin the SysConfig file. 
//! The LED GPIO pins are toggled in the CPU Timer interrupt service routine. 
//! A global variable is incremented at the end of each timer interrupt.
//!
//! \b External \b Connections \n
//! - None.
//!
//! \b Watch \b Variables \n
//! - \b cpuTimer0IntCount - CPU Timer interrupt counts.
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


//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts.
    //
    Device_init();

    //
    // Board Initialization.
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // IDLE loop. Just sit and loop forever.
    //
    while(1)
    {
    }
}

//
// ISR for the timer interrupt.
//
void INT_myCPUTIMER0_ISR(void)
{
    //
    // Toggle both LED GPIOs on/off.
    //
    GPIO_togglePin(myBoardLED0_GPIO);
    GPIO_togglePin(myBoardLED1_GPIO);

    //
    // Increment the interrupt counter variable.
    //
    cpuTimer0IntCount++;
}

//
// End of File
//