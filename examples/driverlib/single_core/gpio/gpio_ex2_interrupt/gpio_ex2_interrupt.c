//#############################################################################
//
// FILE:   gpio_ex2_interrupt.c
//
// TITLE:  XINT/XBAR Example
//
//! \addtogroup driver_example_list
//! <h1> XINT/XBAR example </h1>
//!
//! This example demonstrates the XINT feature in SysConfig by using it in 
//! conjunction with the input and output XBARs. The GPIO is toggled and
//! connected to the input XBAR, while simultaneously triggering an 
//! external interrupt. The interrupt increments a counter which can be observed 
//! in the watch window. In addition to triggering an interrupt, the input 
//! signal is routed from the input XBAR to the output XBAR so that the output 
//! can be observed via oscilloscope or logic analyzer on a separate pin.
//!
//!  \b Watch \b Variables \n
//!  - \b counter - Number of interrupts generated
//!  
//#############################################################################
//
// $Release Date: $
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
//Global Variables
//
int counter = 0;

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

    while(1)
    {
        GPIO_writePin(myINPUTXBARINPUT0_SOURCE, 1);
        DEVICE_DELAY_US(1000000);
        GPIO_writePin(myINPUTXBARINPUT0_SOURCE, 0);
        DEVICE_DELAY_US(1000000);
    }
}

void INT_myGPIO0_XINT_ISR(void){
    counter++;
}

//
// End of File
//
