//#############################################################################
//
// FILE:   lpm_ex4_standbywake_watchdog.c
//
// TITLE:  Standby entry and Exit example.
//
//! \addtogroup driver_example_list
//! <h1>Low Power Modes: Device Standby Mode and Wakeup using Watchdog</h1>
//!
//!  This example puts the device into STANDBY mode. If the lowest
//!  possible current consumption in STANDBY mode is desired, the
//!  JTAG connector must be removed from the device board while
//!  the device is in STANDBY mode.
//!
//!  This example puts the device into STANDBY mode then wakes up
//!  the device from STANDBY using watchdog timer.
//!
//!  The device wakes up from the STANDBY mode when the watchdog timer overflows
//!  triggering an interrupt. In the ISR, the GPIO1 is pulled low.
//!  the GPIO1 is toggled to indicate the device is out of STANDBY mode.
//!  A pre scalar is set for the watchdog timer to change the counter overflow
//!  time.
//!
//!  GPIO1 is pulled high before entering the STANDBY mode and is pulled low
//!  when in the wakeup ISR.
//!
//! \b External \b Connections \n
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
    // Enter standby mode.
    //
    SysCtl_enterStandbyMode();

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

        //
        // Service watchdog
        //
        SysCtl_serviceWatchdog();
    }
}



//
// watchdogISR - The interrupt service routine called when the watchdog
//               triggers the wake interrupt signal
//
__attribute((section(".TI.ramfunc")))
void watchdogISR(void)
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