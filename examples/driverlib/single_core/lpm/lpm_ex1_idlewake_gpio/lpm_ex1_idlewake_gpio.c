//#############################################################################
//
// FILE:   lpm_ex1_idlewake_gpio.c
//
// TITLE:  Idle entry and Exit example.
//
//! \addtogroup driver_example_list
//! <h1>Low Power Modes: Device Idle Mode and Wakeup using GPIO</h1>
//!
//!  This example puts the device into IDLE mode and then wakes up the device
//!  from IDLE using XINT1 which triggers on a falling edge of GPIO0.
//!
//!  The GPIO0 pin must be pulled from high to low by an external agent for
//!  wakeup. GPIO0 is configured as an XINT1 pin to trigger an XINT1 interrupt
//!  upon detection of a falling edge.
//!
//!  Initially, pull GPIO0 high externally. To wake device from IDLE mode by
//!  triggering an XINT1 interrupt, pull GPIO0 low (falling edge). The wakeup
//!  process begins as soon as GPIO0 is held low for the time indicated in the
//!  device datasheet.
//!
//!  GPIO1 is pulled high before entering the IDLE mode and is pulled low when
//!  in the external interrupt ISR.
//!
//! \b External \b Connections \n
//!  - GPIO0 needs to be pulled low to wake up the device.
//!  - On device wakeup, the GPIO1 will be low and LED1 will start blinking
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

    //
    // Set GPIO1 high.
    //
    GPIO_writePin(myGPIO1, 1);

    //
    // Enter idle mode.
    //
    SysCtl_enterIdleMode();

    while(1)
    {
        //
        // Toggle LED1
        //
        GPIO_togglePin(myGPIO2);

        //
        // 500ms delay
        //
        DEVICE_DELAY_US(500000);
    }
}


//
// XINT1_ISR - External interrupt when GPIO0 is pulled from high to low.
//
__attribute((section(".TI.ramfunc")))
void XINT1_ISR(void)
{
    //
    // Wake the flash from low power mode.
    //
    // Flash_wakeFromLPM(FLASH0CTRL_BASE);

    //
    // Set GPIO1 low.
    //
    GPIO_writePin(myGPIO1, 0);
}

//
// End of File
//
