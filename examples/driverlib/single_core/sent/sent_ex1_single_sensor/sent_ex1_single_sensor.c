//#############################################################################
//
// FILE:   sent_ex1_single_sensor.c
//
// TITLE:  SENT Single Sensor
//
//! \addtogroup driver_example_list
//! <h1> SENT Single Sensor </h1>
//!
//! This program will receive sensor data from a magnetic angle sensor using
//! the SENT communication protocol. This data can be further utilized
//! to convert and get the sensed information.
//!
//! The sensor sends out a signal that is made up of a string of pulses with
//! data encoded as falling to falling edge periods. It happens independently
//! of any receiver module activity, which occurs without the receiver module
//! sending a sync signal. The modulated signal with a constant amplitude
//! voltage and an evaluation of the time interval between two falling edges
//! (a single edge) is delivered in units of 4 bits (1 nibble), which can
//! represent values ranging from 0 to 15.
//!
//! This example configures SENT module to receive 6 Data-nibble per frame
//! for fast channel.
//!
//! \b External \b Connections \n
//!     - Connect GPIO58 to sensor's SENT channel 1 pin
//!
//! \b Watch \b Variables \n
//!  - \b SENT_Frame[] - Frame received from the Sensor
//!  - \b timestamp[] - Time stamp of the data nibble received
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

volatile uint32_t IntCount = 0;
uint32_t SENT_Frame[20];
uint32_t timestamp[20];

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
    // - Setup SENT1, configuring the Tick time, data nibbles
    // - Initialize GPIOs for SENT1
    // - Enable interrupts for Sensor 1 fast channel for this example
    Board_init();
    SENT_enableSENTReceiver(mySENT1_BASE);
    SENT_clearInterruptFlag(mySENT1_BASE, SENT_INT_RFAST_S1DV | SENT_INT_GLOBAL);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();


    //receiver wait for data frame
    while(1);

}

__attribute__((interrupt("INT"))) void sent1ISR(void)
{
    if(IntCount<20)
    {
        //
        // Last 12 bit of the received SENT frame represents data nibbles 1,2 and 3
        //
        SENT_Frame[IntCount] = SENT_getFrameData(mySENT1_BASE, 1);
        timestamp[IntCount]  = SENT_getFrameData(mySENT1_BASE, 0);

        SENT_clearInterruptFlag(mySENT1_BASE, SENT_INT_RFAST_S1DV | SENT_INT_GLOBAL);
        IntCount++;
    }
    else
    {
        SENT_disableInterrupt(mySENT1_BASE, SENT_INT_RFAST_S1DV);
    }

}
