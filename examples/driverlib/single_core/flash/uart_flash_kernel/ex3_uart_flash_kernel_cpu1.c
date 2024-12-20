//###########################################################################
//
// FILE:    ex3_uart_flash_kernel_cpu1.c
//
// TITLE:   CPU kernel main function
// <h1> CPU kernel main function </h1>
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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

#include <ex3_uart_flash_kernel_cpu1.h>
#include "board.h"

extern uint32_t __LDAX_END;
extern uint32_t __LDAX_START;
extern uint32_t __CPAX_START;

/**
 * main.c
 */
int main(void)
{

    // Initialize the device and GPIOs (driverlib)
    Device_init();
    Device_initGPIO();

    // Initialize interrupts and vector table (driverlib)
    Interrupt_initModule();
    Interrupt_initVectorTable();

    // Copy the code from CPAX (Non Executable) to LDAX (Executable)
    memcpy((void*)&__LDAX_START,(void*)&__CPAX_START,((uintptr_t)&__LDAX_END - (uintptr_t)&__LDAX_START));

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;

    Board_init();

    #ifdef DFU_CPU1_APP
    //
    // At 200MHz, execution wait-states for external oscillator is 3. Modify the
    // wait-states when the system clock frequency is changed.
    //
    Flash_initModule(3);
    #endif /* DFU_CPU1_APP */

    uint32_t EntryAddr;

    // Use GPIOs 2 and 3 as UART TX and RX
    EntryAddr = uartGetFunction(UART_BOOT_ALT2);

    //
    // Branch to application entrypoint
    //
    CPU_jumpToAddr(EntryAddr);

	return(EntryAddr);
}

void CPU_jumpToAddr(uint32_t jumpAddr)
{
    asm(" MV A7, D0");
    asm(" LB A7");
}