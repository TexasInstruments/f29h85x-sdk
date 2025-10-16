//#############################################################################
//
// FILE:   interrupt_ex2_int_rtint_nesting.c
//
// TITLE:  INT and RTINT Nesting example
//
//! \addtogroup driver_example_list
//! <h1> INT and RTINT Nesting Example </h1>
//!
//! This example showcases nesting of INTs and RTINTs in groups using software
//! interrupts and increments every time the software asserts an interrupt.
//! The watch variables and print statements can be used to determine
//! entry and exit points of ISR.
//!
//! The interrupt priorities / group mask are configured as follows :
//!   - RTINT Threshold = 20
//!   - Group Mask      = 0xFE
//!   - INT   1 Interrupt priority = 50 -> INT (Group 24)
//!   - INT   2 Interrupt priority = 51 -> INT (Group 24)
//!   - INT   3 Interrupt priority = 49 -> INT (Group 23)
//!   - RTINT 1 Interrupt priority = 10 -> RTINT (Group 4)
//!   - RTINT 2 Interrupt priority = 11 -> RTINT (Group 4)
//!   - RTINT 3 Interrupt priority = 9 -> RTINT (Group 3)
//!
//! Order of Interrupt Triggers:
//! INT1 -> INT2 -> INT3 -> RTINT1 -> RTINT2 -> RTINT3
//!
//! Order of Interrupt Execution:
//! INT1 -> INT3 -> RTINT1 -> RTINT3 -> RTINT1 -> RTINT2 -> INT3 -> INT1 -> INT2
//!
//! Sysconfig inserts the required attributes to the ISR functions to inform
//! the compiler that the function is an interrupt / realtime interrupt.
//!
//! \b External \b Connections \n
//!  - None
//!
//!  \b Watch \b Variables \n
//!  - \b SWINT1Count - INT1 count
//!  - \b SWINT2Count - INT2 count
//!  - \b SWINT3Count - INT3 count
//!  - \b SWINT4Count - RTINT1 count
//!  - \b SWINT5Count - RTINT2 count
//!  - \b SWINT6Count - RTINT3 count
//!
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
// Included Files
//
#include "board.h"
#include <stdio.h>

//
// Globals
//
volatile uint16_t SWINT1Count = 0; // INT1 count
volatile uint16_t SWINT2Count = 0; // INT2 count
volatile uint16_t SWINT3Count = 0; // INT3 count
volatile uint16_t SWINT4Count = 0; // RTINT1 count
volatile uint16_t SWINT5Count = 0; // RTINT2 count
volatile uint16_t SWINT6Count = 0; // RTINT3 count

volatile uint16_t done;

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

    done = 0;              // Test is not done yet

    printf("\nSW INT 1 is triggered.\n");
    Interrupt_force(INT1); // Trigger INT1

    while(!done)           // Wait until all interrupts have been serviced
    {

    }

    //
    // When the interrupts have been serviced, the program will stop here.
    //
    ESTOP0;

}

//
// INT1 ISR
//
void INT_SW1_ISR(void)
{
    printf(" -> Entering SW INT 1 ISR.\n");
    SWINT1Count++; // INT1 ISR is being serviced.
    ENINT; // Enable Nesting. This interrupt has the higher priority within its group, and it will not be preempted by any interrupts within its group. This interrupt will be preempted by an interrupt in another group with a higher priority.
    printf("   SW INT 2 is triggered.\n");
    Interrupt_force(INT2); // Trigger INT2
    printf("   SW INT 3 is triggered.\n");
    Interrupt_force(INT3); // Trigger INT3
    printf(" <- Exiting SW INT 1 ISR.\n");
}

//
// INT2 ISR
//
void INT_SW2_ISR(void)
{
    printf("   -> Entering SW INT 2 ISR.\n");
    SWINT2Count++; // INT2 ISR is being serviced.
    ENINT; // Enable Nesting. This interrupt has the lower priority within its group, and it will not be preempted by any interrupts within its group.
    done = 1; // Test done.
    printf("   <- Exiting SW INT 2 ISR.\n");
}

//
// INT3 ISR
//
void INT_SW3_ISR(void)
{
    printf("     -> Entering SW INT 3 ISR.\n");
    SWINT3Count++; // INT3 ISR is being serviced.
    ENINT; // Enable Nesting. This interrupt has the highest INT priority overall and is in its own group, so it will not be preempted by the other INTs.
    printf("       SW RTINT 1 is triggered.\n");
    Interrupt_force(RTINT1); // Trigger RTINT1
    printf("     <- Exiting SW INT 3 ISR.\n");
}

//
// RTINT1 ISR
//
void INT_SW4_ISR(void)
{
    printf("       -> Entering SW RTINT 1 ISR.\n");
    SWINT4Count++; // RTINT1 ISR is being serviced.
    printf("         SW RTINT 2 is triggered.\n");
    Interrupt_force(RTINT2); // Trigger RTINT2
    printf("         SW RTINT 3 is triggered.\n");
    Interrupt_force(RTINT3); // Trigger RTINT3
    printf("       <- Exiting SW RTINT 1 ISR.\n");
}

//
// RTINT2 ISR
//
void INT_SW5_ISR(void)
{
    printf("         -> Entering SW RTINT 2 ISR.\n");
    SWINT5Count++; // RTINT2 ISR is being serviced.
    printf("         <- Exiting SW RTINT 2 ISR.\n");
}

//
// RTINT3 ISR
//
void INT_SW6_ISR(void)
{
    printf("           -> Entering SW RTINT 3 ISR.\n");
    SWINT6Count++; // RTINT3 ISR is being serviced.
    printf("           <- Exiting SW RTINT 3 ISR.\n");
}

//
// End of File
//