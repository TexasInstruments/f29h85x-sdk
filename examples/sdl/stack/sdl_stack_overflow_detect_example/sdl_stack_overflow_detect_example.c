/* Copyright (c) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

 /**
 *  \file     sdl_stack_overflow_detect_example.c
 *
 *  \brief    This file contains stack overflow detection.
 *
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/
#include "device.h"
#include "board.h"
#include <stdio.h>
#include <kernel/dpl/DebugP.h>
#include <stack/sdl_stack.h>
#include <stack/sdlr_erad.h>
#include <include/sdl_types.h>

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/

volatile uint32_t functionCallCount = 0;
uint32_t intCount = 0;
/* The stack start address */
extern uint32_t __stack;
/* The stack end address */
extern uint32_t __TI_STACK_END;

/*===========================================================================*/
/*                   Internal & External function declarations               */
/*===========================================================================*/
/* ISR to be executed on interrupt generation
 * Program will halt at this ESTOP0 
 */
void Stack_interrupt_ISR(void);
/* Recursive function to fill the stack */
void Stack_recursiveFunction(uint32_t delay);
void Stack_enableInterrupt_StackOverflow(SDL_Stack_BusCompInstance instance);

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

int main(void)
{
    /* Initializes device clock and peripherals */
    Device_init();

    /* Board Initialization */
    Board_init();

    DebugP_log(" Stack overflow example started \n");

    Interrupt_Config cfg ={
        .enable        = true,
        .priority      = 40,
        .linkOwner     = SSU_LINK2,
        .contextID     = INTERRUPT_CONTEXT_AGNOSTIC,
        .apiLinkID     = SSU_API_DISABLE
    };

    cfg.handler = &Stack_interrupt_ISR;
    Interrupt_configChannel(INT_ERAD, cfg);

    /* Set the threshold for RTINT. The ERAD interrupt is configured as normal interrupt */
    Interrupt_setThreshold(20);

    /* Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU. */
    ENINT;

    DebugP_log(" Configure the module for stack overflow detection\n");

    /* Configure the ERAD module for stack overflow detection */
    Stack_enableInterrupt_StackOverflow(SDL_STACK_BUSCOMP7);


    Interrupt_enableGlobal();

    DebugP_log(" execute recursive function to fill the stack \n");
    Stack_recursiveFunction(1);

    while(1)
    {

    }

}

void Stack_enableInterrupt_StackOverflow(SDL_Stack_BusCompInstance instance)
{
    SDL_Stack_Config busCompParams;
    int32_t status = SDL_EBADARGS;

    /* Disable CPU halt and enable Interrupt */
    busCompParams.enableStop = FALSE;
    busCompParams.enableInt  = TRUE;
    busCompParams.enableNMI  = FALSE;

    /* reference address is set to stack end address 
     * mask is set to zero 
     */
    busCompParams.reference = (uint32_t)&__TI_STACK_END;
    busCompParams.mask  = 0x0U;

    /* Configure the Stack pointer select */
    busCompParams.enableSpselMatch = FALSE;
    busCompParams.spsel = 0x0U;

    /* Configure the bus comparator */
    status = SDL_Stack_configBusComp(instance, &busCompParams);

    if(status==SDL_PASS)
    {
        DebugP_log(" Configuration of the module completed \n");
    }
    else
    {
        DebugP_log(" Configuration of the module failed \n");
    }

}

void Stack_recursiveFunction(uint32_t delay)
{
    uint32_t  buffer[20];
    
    functionCallCount++;

    if((uint32_t)buffer > (uint32_t)(&__stack))
    {
        /* Recursive function to fill the stack */
        Stack_recursiveFunction(delay + 1UL);
    }
}

void Stack_interrupt_ISR(void)
{
    printf(" a write is detected beyond the dedicated STACK \n");
    printf(" Executed the ISR\n");
    printf(" All tests have passed. \n");
    intCount++;
    ESTOP0;
}