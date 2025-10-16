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
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//###########################################################################

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


