// #############################################################################
//
//  FILE:   i2c_ex7_clock_stretching_target_rx.c
//
//  TITLE:  I2C Extended Clock Stretching Target RX
//
//! \addtogroup driver_example_list
//! <h1>I2C Extended Clock Stretching Target RX</h1>
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
#define CLOCK_STRETCHING_MASK (0x8000)
#define NUM_I2C_DATA (4)

//
// Globals
//
uint16_t txData = 0, rxData = 0, count = 0, aas_count = 0;
uint16_t rx_data_rdy_count = 0, eacs_count = 0, scd = 0, error = 0;
uint16_t pui32DataTx[NUM_I2C_DATA];
uint16_t pui32DataRx[NUM_I2C_DATA];
uint16_t ui32Index;
uint16_t status_check = 0x0000;
uint16_t clk_status_check = 0x0000;
volatile uint16_t int_isrc = 0x0000;
uint16_t intSeq[11];

volatile uint16_t waitForInt = 11;
uint16_t ui32Index_1 = 0, ui32Index_12 = 0;
volatile uint16_t I2C_Int = 1;
unsigned int status1 = 0, ecs_hit = 0, arb_lost_count = 0, no_ack_hit = 0, int_none = 0;

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

    for (ui32Index = 0; ui32Index < NUM_I2C_DATA; ui32Index++)
    {
        pui32DataTx[ui32Index] = ui32Index + 1;
    }
    //
    // Board initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    while (I2C_Int)
    {
        if (waitForInt == 0)
        {
            I2C_Int = 0;
        }
    }
    for (ui32Index_1 = 0; ui32Index_1 < NUM_I2C_DATA; ui32Index_1++)
    {
        if (pui32DataRx[ui32Index_1] != pui32DataTx[ui32Index_1])
        {
            error++;
        }
    }
    if (error == 0 && aas_count == 1 && rx_data_rdy_count == 4 && scd == 1 && (HWREGH(I2CB_BASE + I2C_O_ISRC)) == 0)
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
    count++;
    waitForInt = waitForInt - 1;
    int_isrc = I2C_getInterruptSource(I2CB_BASE); // Checking source of interrupt
    switch (int_isrc)
    {
    case I2C_INTSRC_ADDR_TARGET:
        aas_count++;
        // To check sequence of interrupt
        if (rx_data_rdy_count != 0 && eacs_count != 0)
        {
            error++;
        }
        break;
    case I2C_INTSRC_RX_DATA_RDY:
        rx_data_rdy_count++;

        // To check sequence of interrupt
        if (rx_data_rdy_count != eacs_count)
        {
            error++;
        }

        rxData = HWREGH(I2CB_BASE + I2C_O_DRR);
        pui32DataRx[ui32Index_12] = rxData;
        ui32Index_12++;

        break;
    case I2C_INTSRC_SCL_ECS:
        ecs_hit++;
        clk_status_check = HWREGH(I2CB_BASE + I2C_O_STR) & I2C_STS_SCL_ECS;
        if (clk_status_check == CLOCK_STRETCHING_MASK)
        {
            eacs_count++;

            HWREGH(I2CB_BASE + I2C_O_STR) |= CLOCK_STRETCHING_MASK;
        }
        else
        {
            error++;
        }
        break;
    case I2C_INTSRC_ARB_LOST:
        arb_lost_count++;
        error++;
        break;
    case I2C_INTSRC_NO_ACK:
        no_ack_hit++;
        error++;
        break;
    case I2C_INTSRC_STOP_CONDITION:
        scd++;
        break;
    case I2C_INTSRC_NONE:
        int_none++;
        error++;
        break;
    }
    Interrupt_disable(INT_I2CB);
    Interrupt_enable(INT_I2CB);
}

void INT_myI2C0_FIFO_ISR(void) 
{
    ESTOP0;
}

//
// End of File
//
