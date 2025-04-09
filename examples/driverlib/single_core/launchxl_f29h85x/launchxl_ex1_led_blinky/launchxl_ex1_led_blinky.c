//#############################################################################
//
// FILE:    launchxl_ex1_led_blinky.c
//
// TITLE:   LED Blinky example for LaunchPad
//
//! \addtogroup driver_example_list
//! <h1> LED Blinky example </h1>
//!
//! This example demonstrates how to blink the LaunchPad LEDs. The device GPIOs
//! are configured through the SysConfig file. The initial values of GPIOs
//! connected to LED0 and LED1 are set HIGH and LOW respectively. The GPIO pins
//! are toggled in an infinite loop, making the LEDs blink alternatively.
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
#include "board.h"

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
    // Loop.
    //
    for(;;)
    {
        //
        // Toggle both LEDs
        //
        GPIO_togglePin(myBoardLED0_GPIO);
        GPIO_togglePin(myBoardLED1_GPIO);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(1000000);
    }
}


//
// End of File
//

