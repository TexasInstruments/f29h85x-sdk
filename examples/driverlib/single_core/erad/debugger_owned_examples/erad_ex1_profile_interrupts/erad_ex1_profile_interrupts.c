//#############################################################################
//
// FILE:    erad_ex1_profile_interrupts.c
//
// TITLE:   ERAD Profiling Interrupts Example
//
//! \addtogroup driver_example_list
//! <h1> ERAD Profiling Interrupts </h1>
//!
//! This example configures CPU Timer0, 1, and 2 to be profiled using the ERAD
//! module. Included is a JavaScript file, erad_ex1_profile_interrupts.js, which
//! is used with the scripting console to program ERAD registers and view
//! profiling data.
//!
//! To run the ERAD script, use the following command in the scripting console:
//! - require("<proj_workspace_path>\\erad_ex1_profile_interrupts\\erad_ex1_profile_interrupts.js")
//!
//! The included JavaScript file, erad_ex1_profile_interrupts.js, uses CCS
//! Scripting features. For information, please visit:
//! https://software-dl.ti.com/ccs/esd/documents/users_guide_ccs_20.0.0/index_debug-scripting.html
//!
//! Note that the script must be run after loading and running the .out on the
//! C29x core. Only CPU timer 2 ISR is profiled in this example.
//!
//! This example uses 2 Bus comparators (EBC) and 3 counters (SEC):
//!  - BUSCOMP4  : PC = start address of INT_myCPUTIMER2_ISR
//!  - BUSCOMP5  : PC = end address of INT_myCPUTIMER2_ISR
//!  - COUNTER2  : Used to count the INT_myCPUTIMER2_ISR execution cycles.
//!                Configured in start-stop mode with start event as BUSCOMP4
//!                and stop event as BUSCOMP5
//!  - COUNTER0  : Used to count the number of times the system event
//!                TIMER2_INT has occurred.
//!                Configured in rising-edge count mode with counting input as
//!                system event TIMER2_INT
//!  - COUNTER1  : Used to count the latency from the system event TIMER2_INT
//!                to INT_myCPUTIMER2_ISR entry.
//!                Configured in start-stop mode with start event as 
//!                TIMER2_INT and stop event as BUSCOMP4
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - cpuTimer0IntCount
//!  - cpuTimer1IntCount
//!  - cpuTimer2IntCount
//!
//! \b Profiling \b Script \b Output
//!  - Current ISR cycle count (COUNTER2)
//!  - Max ISR cycle count (maximum value of COUNTER2)
//!  - Interrupt occurrence count (COUNTER0)
//!  - ISR entry delay cycle count (maximum value of COUNTER1)
//!
//! Note that the large difference between Interrupt occurrence count
//! (COUNTER0) and ISR execution count (cpuTimer2IntCount) is because the ISR
//! takes more number of cycles than the actual interrupt period. ISR entry
//! delay cycle count will also be higher due to the same reason.
//
//#############################################################################
//
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

//#############################################################################

//
// Included Files
//
#include <stdint.h>
#include <float.h>
#include <math.h>
#include "board.h"

//
// Globals
//
uint64_t cpuTimer0IntCount;
uint64_t cpuTimer1IntCount;
uint64_t cpuTimer2IntCount;

//
// Pre-chosen Pseudo Random Generator constants
//
const uint16_t PseudoRand_multiplier = 31821;
const uint16_t PseudoRand_increment = 13849;
uint16_t PseudoRand_seed = 21845;

//
// Function Prototypes
//
uint16_t generatePseudoRand16(uint16_t *);

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
    // Reset interrupt counter
    //
    cpuTimer0IntCount = 0;
    cpuTimer1IntCount = 0;
    cpuTimer2IntCount = 0;

    //
    // Starts CPU-Timer 0, CPU-Timer 1, and CPU-Timer 2.
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);
    CPUTimer_startTimer(CPUTIMER1_BASE);
    CPUTimer_startTimer(CPUTIMER2_BASE);

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
void INT_myCPUTIMER0_ISR(void)
{
    cpuTimer0IntCount++;
}

void INT_myCPUTIMER1_ISR(void)
{
    cpuTimer1IntCount++;
}

__attribute__ ((section(".funcToProfile"), noinline))
void INT_myCPUTIMER2_ISR(void)
{
    //
    // Simulate storing data to a location. "volatile" keyword ensures this is
    // not optimized out by the compiler.
    //
    volatile uint32_t output;

    //
    // Generate a random number.
    //
    uint16_t count = generatePseudoRand16(&PseudoRand_seed);

    //
    // Simulate a task that can take some time to complete. Loop a "random"
    // number of times and store values to a location.
    //
    uint32_t i;
    for(i = 0; i < count; i++)
    {
        output = i;
    }

    //
    // The CPU acknowledges the interrupt.
    //
    cpuTimer2IntCount++;
}

//
// generatePseudoRand16 - Generate a pseudo random 16-bit number by passing a
// start value or "seed". This generator is a linear congruential pseudo random
// generator, which is very fast. The basic calculation is:
//
// randNum(n) = ((randNum(n-1) * multiplier) + increment) modulo M
//
uint16_t
generatePseudoRand16(uint16_t *seed)
{
    //
    // Perform calculation. Mask off bottom bits in lieu of modulus operation
    //
    *seed = ((uint32_t)*seed * PseudoRand_multiplier + PseudoRand_increment)
            & 0xFFFF;
    return(*seed);
}

//
// End of File
//