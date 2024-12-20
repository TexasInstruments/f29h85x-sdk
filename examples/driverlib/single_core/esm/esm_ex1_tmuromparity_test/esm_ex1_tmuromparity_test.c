//#############################################################################
//
// FILE:   esm_ex1_tmuromparity_test.c
//
// TITLE:  TMU ROM Parity Error Test Example
//
//! \addtogroup driver_example_list
//! <h1> ESM </h1>
//!
//! Example shows how to generate and check the error response configuration
//! during development phase of software. It highlights the capability to
//! self test the error propogation path providing test for diagnostic (TMU ROM
//! Parity logic) 
//! Note - TMU ROM parity error puts CPU in fault state and only NMI can take
//! CPU out of the fault state.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - error_generated - check if the proper error is generated
//!
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
#include "board.h"

//
// Globals
//
uint32_t loopCount;

bool error_generated ;
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

    loopCount = 0;

    //
    // Forcing the TMU ROM Parity Error
    //
    CPU_forceTMUROMParityError();

   
    // Execute CPU Instruction's that does a read access to TMU ROM for triggering the Parity Error
    // Since the bits are already flipped by forcing the parity error, executing the PUSINF instruction will immediately trigger CPU1 TMU ROM Parity error
    // Refer to C29 CPU User guide for more information on PUSINF instruction
    asm("PUSINF M2,M1");
    
    // Loop Forever
    //
    for(;;)
    {
        loopCount++;
    }
}

// ISR
void myNMI_ISR(void) 
{
    //
    // Check if the correct error event is Active/Pending and Enabled using the status register
    // if error_generated is true CPU1_TMUROM_PAR_ERR is active and enabled because that is the error forced
    //
    error_generated = ESM_getInterruptStatus(ESMCPU1_BASE,ESM_EVENT_CPU1_TMUROM_PAR_ERR);
    
    //
    // Disable the TMU parity force
    //
    CPU_clearTMUROMParityError();
    
    //
    // Clear the raw status and deassert the interrupt.
    //
    ESM_clearRawInterruptStatus(ESMCPU1_BASE,ESM_EVENT_CPU1_TMUROM_PAR_ERR);
    ESM_clearRawInterruptStatus(ESMCPU1_BASE,ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT);
    
    //
    // Write the end of interrupt vector to the EOI Interrupt Register. In
    // case there are enabled error events pending then a new pulse is 
    // generated and level interrupt remains asserted, else no new pulse is 
    // generated.
    //
    ESM_writeEOIVector(ESMCPU1_BASE, ESM_EOI_HIGH_PRIORITY_ERROR_INTERRUPT);
}

//
// End of File
//
