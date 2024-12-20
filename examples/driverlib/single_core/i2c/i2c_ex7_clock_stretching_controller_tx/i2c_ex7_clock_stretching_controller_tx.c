// #############################################################################
//
//  FILE:   i2c_ex7_clock_stretching_controller_tx.c
//
//  TITLE:  I2C Extended Clock Stretching Controller TX
//
//! \addtogroup driver_example_list
//! <h1>I2C Extended Clock Stretching Controller TX</h1>
//!
//! This program uses the extended clock stretching mode of the I2C module. Both
//! the TX and RX I2C Non-FIFOs and their interrupts are used.
//!
//! A stream of data is sent and then compared to the received stream.
//!
// #############################################################################
//
//
//  //
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

// #############################################################################

//
// Included Files
//
#include "board.h"

//
// Defines
//
#define NUM_I2C_DATA (4)

//
// Globals
//
uint16_t txData = 0, rxData = 0;
uint16_t pui32DataTx[NUM_I2C_DATA], pui32DataRx[NUM_I2C_DATA];
volatile uint16_t waitForInt = 4;
uint16_t ui32Index = 0, ui32Index_1 = 0, error = 0;
volatile uint16_t I2C_Int = 1;
int status1 = 0;

//
// Function Prototypes
//
void INT_myI2C0_ISR(void);
void INT_myI2C0_FIFO_ISR(void);

//
// Main
//
void main(void)
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

    I2C_sendStartCondition(I2CA_BASE);
    while (I2C_Int)
    {
        if (waitForInt == 0)
        {
            I2C_Int = 0;
        }
    }
    I2C_sendStopCondition(I2CA_BASE);
    if (error == 0)
    {
        status1 = 1;
    }
    else
    {
        status1 = 0;
    }
}

//
// I2C A Transmit & Receive ISR.
//

void INT_myI2C0_ISR(void)
{
    waitForInt = waitForInt - 1;
    txData = ui32Index;
    I2C_putData(I2CA_BASE, txData + 1);
    pui32DataTx[ui32Index] = txData + 1;
    ui32Index++;

    INTERRUPT_init();
}

void INT_myI2C0_FIFO_ISR(void)
{
    ESTOP0;
}
//
// End of File
//
