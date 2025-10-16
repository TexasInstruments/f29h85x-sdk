//#############################################################################
//
// FILE:  led_blinky_cpu1.c
//
// TITLE: FOTA LED Blinky Example
//
//###########################################################################
// $TI Release:  $
// $Release Date:   $
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
#include <board.h>
#include "ti_dpl_config.h"

//
// Globals
//
void blinkyLedCb(ClockP_Object *hClk, void *arg);

// Entry point to the command jump table in the SBL, specified in linker
extern const uint32_t cmdTableEntryAddr;
void (*commandJumpTable)() __attribute__((c29_protected_call));

bool    rcvdCommandInput = false;
uint8_t ledBit = 1U;
ClockP_Object  gblinkyLedClk;

//
// Main
//
int main(void)
{
    //
    // Initialize SysConfig Settings
    //
    PinMux_init();
	PERCONFIG_init();
	GPIO_init();
	CPUTIMER_init();
	UART_init();

    // Interrupt Settings for SBL_COMA_INT -> INT_UARTA
	Interrupt_register(SBL_COMA_INT, &SBL_uartNotifyISR);
	Interrupt_enable(SBL_COMA_INT);
	Interrupt_setPriority(SBL_COMA_INT, 255);
	Interrupt_setContextID(SBL_COMA_INT, INTERRUPT_CONTEXTID_0);

    //
    // Initialize CPUTIMER interrupt to blink LED
    //
    Interrupt_register(myCPUTIMER0_INT, &INT_myCPUTIMER0_ISR);
	Interrupt_enable(myCPUTIMER0_INT);
	Interrupt_setPriority(myCPUTIMER0_INT, 255);
	Interrupt_setContextID(myCPUTIMER0_INT, INTERRUPT_CONTEXTID_0);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Assign entry address to function call
    //
    commandJumpTable = (__attribute__((c29_protected_call)) void(*)())&cmdTableEntryAddr;

    //
    // Loop Forever
    //
    while(1)
    {
        if (rcvdCommandInput)
        {
            rcvdCommandInput = false;

            // Call commandJumpTable located in the SBL
            commandJumpTable();

            // Re-enable Rx source trigger
            UART_enableInterrupt(SBL_COMA_BASE, UART_INT_RX);
        }
    }
}

//
// UARTA ISR
// This ISR will catch incoming command packets (UART fifo level to two bytes)
//
__attribute__((interrupt("INT")))
void SBL_uartNotifyISR(void) 
{
    uint32_t ui32Status;

    //
    // Get the interrupt status.
    //
    ui32Status = UART_getInterruptStatus(SBL_COMA_BASE, UART_RAW_INT);

    if (UART_isDataAvailable(SBL_COMA_BASE))
    {
        // Flag semaphore and wait for the main loop to handle the command
        rcvdCommandInput = true;

        // Disable trigger source until main code processes the command
        UART_disableInterrupt(SBL_COMA_BASE, UART_INT_RX);
    }
    
    //
    // Clear the asserted interrupts.
    //
    UART_clearInterruptStatus(SBL_COMA_BASE, ui32Status);

    //
    // Clear UART global interrupt flag
    //
    UART_clearGlobalInterruptFlag(SBL_COMA_BASE);
    
    return ;
}


void INT_myCPUTIMER0_ISR()
{
    GPIO_writePin(CPU1_SOM_LED3, ledBit);
    GPIO_writePin(CPU1_LP_LED4, ledBit);

    ledBit = ledBit ^ 1;
    
    // Set alternating LEDs
    GPIO_writePin(CPU1_SOM_LED4, ledBit);
    GPIO_writePin(CPU1_LP_LED5, ledBit);
    
    return;
}

//
// End of File
//