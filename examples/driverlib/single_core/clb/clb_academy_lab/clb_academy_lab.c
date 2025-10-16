//#############################################################################
//
// FILE:   lab_main.c
//
// TITLE:  Lab - CLB Lab
//
//! \addtogroup academy_lab_list
//! <h1> CLB Example Lab</h1>
//!
//!
//!
//! \b External \b Connections \n
//!  - GPIO6 is a GPIO input used to enable / disable the EPWM output
//!  - GPIO0 is the EPWM output which should be probed by an oscilloscope
//!
//! \b Watch \b Variables \n
//!  - None.
//!
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
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "clb_config.h"
#include "clb.h"

//
// Global variables and definitions
//
#define     SENSOR_HIGH_INT_TAG 1
#define     SENSOR_LOW_INT_TAG  2
uint16_t    tag;

__attribute__((interrupt("INT"))) void INT_myCLB1_ISR(void);

int main(void)
{
    // CPU Initialization
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();

    // Configure the GPIOs/XBARs/PWM/CLB/LEDs through
    // SysConfig-generated function found within board.c
    Board_init();
    Interrupt_register(INT_CLB1, &INT_myCLB1_ISR);
    Interrupt_enable(INT_CLB1);
    // Initialize and enable the CLB1 tile
    initTILE1(myCLB1_BASE);
    CLB_enableCLB(myCLB1_BASE);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    // Main Loop
    for(;;)
    {

        __asm(" NOP #1");
    }
}

__attribute__((interrupt("INT"))) void INT_myCLB1_ISR(void)
{
    // Get interrupt tag upon HLC interrupt
    tag = CLB_getInterruptTag(myCLB1_BASE);

    // Turn off EPWM LED and turn on SENSOR LED
    if (tag == SENSOR_HIGH_INT_TAG)
    {
        GPIO_writePin(LED_EPWM_GPIO, 1);
        GPIO_writePin(LED_SENSOR_GPIO, 0);
    }

    // Turn on EPWM LED and turn off SENSOR LED
    if (tag == SENSOR_LOW_INT_TAG)
    {
        GPIO_writePin(LED_EPWM_GPIO, 0);
        GPIO_writePin(LED_SENSOR_GPIO, 1);
    }

    CLB_clearInterruptTag(myCLB1_BASE);
}

