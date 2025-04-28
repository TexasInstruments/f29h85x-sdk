//#############################################################################
//
// FILE:   erad_ex7_free_running_counter_syscfg.c
//
// TITLE:  ERAD Free Running Counter using System Event Counter.
//
//! \addtogroup driver_example_list
//! <h1>ERAD Free Running Counter using System Event Counter with Sysconfig</h1>
//!
//!  This example uses SEC2 to implement a free running counter. The SEC is
//!  set to count up based on CPU cycles and generate an interrupt to
//!  CPU when counter reaches 0X0BEBC200 (1 sec at 200 MHz SYSCLK). In the ISR counter reference
//!  is re-programmed with new counter value to get the next interrupt after 1 second.
//!
//!  Note: The System Event Counter (SEC) module instance SEC2 is used in this example. This is because, in
//!  CCS will use SEC0 as the default System Event Counter.for profiling and SEC3 is used by SDK for errata.
//!
//!  \b Watch \b Variables \n
//!  - triggerCounts - the number of times the ISR was entered.
//!
//! \b External \b Connections \n
//!  None
//
//#############################################################################

//
//Included Files
//
#include "board.h"

//
// Global Variables
//
volatile uint32_t triggerCounts = 0U;

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
    // Board initialization
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
// ISR increments triggerCounts, User can add it to watch expressions to monitor number of interrupts triggered.
// Counter reference is re-programmed with new counter value to get the next interrupt after 1 second.
// Counter event is cleared to get the next interrupt.
//
__attribute__((interrupt("INT"))) void INT_myERAD_ISR(void)
{
    ERAD_CounterInstance instance = myERAD_COUNTER0;
    uint32_t currCount = HWREG(ERAD_BASE + ERAD_O_SEC_REF((uint32_t)instance));
    
    triggerCounts++;

    //
    // Write into registers to configure the counter
    //
    HWREG(ERAD_BASE + ERAD_O_SEC_REF((uint32_t)instance)) = currCount + 0x0BEBC200;

    ERAD_clearCounterEvent(instance);

}

//
// End of File
//
