//#############################################################################
//
// FILE:   erad_ex4_bus_monitor_syscfg.c
//
// TITLE:  ERAD Monitoring instruction and data address buses.
//
//! \addtogroup driver_example_list
//! <h1>ERAD Bus Comparator Monitor Program Counter</h1>
//!
//!  In this example, the function delayFunction is called multiple times.
//!  The function does read and writes to the global variables startCount and
//!  endCount.
//!
//!  The BUSCOMP7 and COUNTER0 is used to count the number of times the function
//!  delayFunction was invoked. BUSCOMP6 is used to generate an interrupt when
//!  there is read access to the startCount variable and BUSCOMP5 is used to
//!  generate an interrupt when there is a write access to the endCount variable
//!
//!  Note: The Enhanced Bus Comparator (EBC) modules are used in the
//!  decreasing order of their instances in this example. This is because, in
//!  FLASH configuration/ when hardware breakpoints are used while debugging,
//!  the first few ERAD EBCs are owned by the Debugger and are blocked for the
//!  application to use.
//!
//!  \b Watch \b Variables \n
//!  - funcCount - number of times the function delayFunction was invoked
//!  - isrCount  - number of times the ISR was invoked
//!
//! \b External \b Connections \n
//!  - None
//
//#############################################################################

//
//Included Files
//
#include "board.h"

//
// Globals
//
uint32_t isrCount = 0;
uint32_t funcCount = 0;
volatile uint32_t startCount, endCount;

//
// Function prototypes
//
__attribute__((noinline)) void delayFunction();

//
// Addresses of the function and variables to be monitored
//
void *addr_startCount    = (void *)&startCount;
void *addr_endCount      = (void *)&endCount;
void *addr_delayFunction = (void *)&delayFunction;


//
// Main
//
int main(void)
{
    int i;

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
    // Loop to call the delay function multiple times
    //
    for(i = 0; i < 10; i++)
    {
        //
        // Call the delay function
        //
        delayFunction();

        //
        // Get the current count of COUNTER0 to get the number of times
        // function delayFunction was invoked
        //
        funcCount = ERAD_getCurrentCount(ERAD_COUNTER0);
    }

    ESTOP0;
    while(1);
}

//
// delay function
//
void delayFunction()
{
    uint32_t temp = startCount;
    startCount = temp + 1;

    uint16_t i=0;
    for (; i<100; i++)
    {
        NOP;
    }

    endCount = temp + 1;
}


//
// ISR to be executed on interrupt generation
// Program will halt at this ESTOP0
//
void INT_myERAD_ISR(void)
{
    //
    // Indicate that the ISR was executed
    //
    isrCount++;

    if(ERAD_getBusCompStatus(ERAD_BUSCOMP6) == ERAD_STATE_COMPLETED)
    {
        //
        // ISR was raised because of BUSCOMP6 - Read to startCount variable
        //
        ESTOP0;
       	ERAD_clearBusCompEvent(ERAD_BUSCOMP6);
    }
    if(ERAD_getBusCompStatus(ERAD_BUSCOMP5) == ERAD_STATE_COMPLETED)
    {
        //
        // ISR was raised because of BUSCOMP5 - Write to endCount variable
        //
        ESTOP0;
       	ERAD_clearBusCompEvent(ERAD_BUSCOMP5);
    }
}


