//#############################################################################
//
// FILE:   erad_ex6_stack_overflow_detect_syscfg.c
//
// TITLE:  ERAD Bus Comparator Stack Overflow Detection.
//
//! \addtogroup driver_example_list
//! <h1>ERAD Bus Comparator Stack Overflow Detection with Sysconfig</h1>
//!
//!  This example uses BUSCOMP7 to monitor the stack. The Bus comparator is
//!  set to monitor the data write access bus and generate an interrupt to
//!  CPU when a write is detected beyond the dedicated STACK.
//!  The example is built with optimization=O0 and might not function as
//!  intended with higher optimizations.
//!
//!  Note: The Enhanced Bus Comparator (EBC) modules are used in the
//!  decreasing order of their instances in this example. This is because, in
//!  FLASH configuration/ when hardware breakpoints are used while debugging,
//!  the first few ERAD EBCs are owned by the Debugger and are blocked for the
//!  application to use.
//!
//!  \b Watch \b Variables \n
//!  - functionCallCount - the number of times the recursive function
//!    overflowing the STACK is called.
//!  - x indicates that the ISR has been entered
//!
//! \b External \b Connections \n
//!  None
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
// Global Variables
//

volatile uint32_t functionCallCount = 0;
uint32_t x = 0;
volatile uint32_t dummyValue = 0;

//
// Function Prototypes
//
void recursiveFunction(uint32_t delay);

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

    recursiveFunction(1);

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {

    }
}

//
// Recursive function to fill the stack
//
void recursiveFunction(uint32_t delay)
{
    //
    // Reserves space on stack
    //
    uint32_t    buffer[100];
    uint32_t    clobber = delay;

    functionCallCount++;

    // The following lines are here just to give a meaning to
    // local variables, so that they aren't considered unused;
    // buffer[1] ... buffer[99] are untouched
    buffer[0] = functionCallCount + 1;
    dummyValue = clobber + buffer[0];

    //
    // Recursive function
    //
    recursiveFunction(delay + 1UL);
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
    x++;
    ESTOP0;
}

//
// End of File
//
