//#############################################################################
//
// FILE:   erad_ex8_gpio_trigger_nmi.c
//
// TITLE:  External GPIO triggering NMI
//
//! \addtogroup driver_example_list
//! <h1>ERAD - External GPIO triggering NMI</h1>
//!
//!  In this example, a GPIO is triggered externally. The ERAD Counter module
//!  is used to count the number of rising edges on the GPIO and an NMI is
//!  triggered on reaching the set reference count value.
//!
//!  \b Watch \b Variables \n
//!  - nmiCount - number of times the NMI is serviced.
//!
//! \b External \b Connections \n
//!  - GPIO0 - trigger source
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
volatile uint32_t nmiCount = 0U;

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

void myNMI_ISR(void)
{
    nmiCount++;

    //
    // Clear the raw status and deassert the interrupt.
    //
    ESM_clearRawInterruptStatus(ESMCPU1_BASE,ESM_EVENT_CPU1_ERAD_NMI);
    ESM_clearRawInterruptStatus(ESMCPU1_BASE,ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT);

    //
    // Write the end of interrupt vector to the EOI Interrupt Register. In
    // case there are enabled error events pending then a new pulse is
    // generated and level interrupt remains asserted, else no new pulse is
    // generated.
    //
    ESM_writeEOIVector(ESMCPU1_BASE, ESM_EOI_HIGH_PRIORITY_ERROR_INTERRUPT);

    ERAD_clearCounterEvent(ERAD_COUNTER0);
}

//
// End of File
//
