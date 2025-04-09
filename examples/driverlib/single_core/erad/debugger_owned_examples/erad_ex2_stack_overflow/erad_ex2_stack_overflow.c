//#############################################################################
//
// FILE:   erad_ex2_stack_overflow.c
//
// TITLE:  ERAD Stack Overflow Example
//
//! \addtogroup driver_example_list
//! <h1> ERAD Stack Overflow </h1>
//!
//! This example uses BUSCOMP6 to monitor the stack. The Bus comparator is
//! set to monitor the data write access bus and generate an interrupt to
//! CPU when a write is detected to end of the STACK within a threshold.
//! A recursive function call is intentionally made to allow the stack
//! to overflow. The example is built with optimization=O0 and might not
//! function as intended with higher optimizations.
//! The included JavaScript file, erad_ex2_stack_overflow.js, programs 
//! ERAD registers in order to detect the stack overflow and halt the CPU
//! once the pointer reaches the threshold at the end of stack.
//!
//! To run the ERAD script, use the following command in the scripting console:
//! - require("<proj_workspace_path>\\erad_ex2_stack_overflow\\erad_ex2_stack_overflow.js")
//!
//! Note that the script must be run after loading the .out on the C29x core. 
//!
//! This JavaScript file uses CCS Scripting features. For information on
//! using the CCS scripting, please visit:
//! https://software-dl.ti.com/ccs/esd/documents/users_guide_ccs_20.0.0/index_debug-scripting.html
//!
//! This example uses 1 HW watchpoint :
//!  - BUSCOMP6 : Data Write Address Bus = Stack end address - 0x10U
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Profiling \b Script \b Output
//!  - "STACK OVERFLOW detected. Halting CPU." will be printed in the scripting
//!    console when a stack overflow occurs (that is, when the watchpoint is hit)
//
//#############################################################################
//
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
#include "driverlib.h"
#include "device.h"


//
// Globals
//
extern uint32_t __TI_STACK_END;
volatile uint32_t functionCallCount = 0;

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
    // Initializes device clock and peripherals
    //
    Device_init();

    recursiveFunction(1);

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {

    }
}

//
// recursive function to fill the stack
//
void recursiveFunction(uint32_t delay)
{
    functionCallCount++;

    //
    // Recursive function
    //
    recursiveFunction(delay + 1UL);
}


//
// End of File
//