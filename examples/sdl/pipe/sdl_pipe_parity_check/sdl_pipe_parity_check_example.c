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
 *  \file     sdl_pipe_parity_check_example.c
 *
 *  \brief    This file contains parity check using PIPE.
 *
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/
#include "device.h"
#include "board.h"
#include <stdio.h>
#include <kernel/dpl/DebugP.h>
#include <sdl_esm.h>
#include <pipe/sdl_pipe.h>
#include <pipe/sdlr_pipe.h>
#include <include/sdl_types.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

#define SDL_PIPE_START_DATA_ONE    (0xFFFFFFFFU)
#define SDL_PIPE_START_DATA_ZERO   (0x00000000U)

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/
SDL_ESM_Config Parity_esmInitConfig =
{
    .enableBitmap =   {0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_LPERR_MASK |
                       SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_LPERR_MASK |
                       SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_LPERR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
    .priorityBitmap = {0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
    .errorPinBitmap = {0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U}
};

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

__attribute__((interrupt("INT"))) void SDL_ESMLowPriIntrISR(void)
{
    SDL_ESM_IntrStatus intrStatus;

    do
    {
        /* Get ESM interrupt status and try to clear event */
        SDL_ESM_loInterruptHandler(SDL_ESMCPU1_BASE, &intrStatus);

        if(intrStatus.selfTestStatus != SDL_ESM_SELF_TEST_ACTIVE)
        {
            /* Unexpected ESM event */
            ESTOP0;
        }

    }while(intrStatus.nextPendPulseEvent != SDL_ESM_NO_EVENT_VALUE);

    SDL_ESM_writeEOI(SDL_ESMCPU1_BASE, SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR);
}

static void SDL_registerESMISR(void)
{
    Interrupt_Config intrParams;

    intrParams.enable      = true;
    intrParams.handler     = &SDL_ESMLowPriIntrISR;
    intrParams.priority    = 10;
    intrParams.linkOwner   = SSU_LINK2;
    intrParams.contextID   = INTERRUPT_CONTEXT_AGNOSTIC;
    intrParams.apiLinkID   = SSU_API_DISABLE;

    Interrupt_configChannel(INT_ESM_LOWPRI, intrParams);

}

void sdl_parity_check(void)
{
    /* Declarations of variables */
    int32_t result;
    uint32_t data,bitIndex;
    uint8_t parity;

    DebugP_log(" Parity Check Example Application\r\n");

    result = SDL_ESM_init(SDL_ESMCPU1_BASE, &Parity_esmInitConfig);

    /* Register the SDL_ESM interrupt handler */
    SDL_registerESMISR();

    if (result != SDL_PASS)
    {
        /* print error and quit */
        DebugP_log(" Error initializing ESM: result = %d\n", result);
        return;
    }
    else
    {
        DebugP_log(" Init ESM complete \n");
    }

    /* Set parity as 0x0*/
    parity = 0x0U;
    /* Start the parity check test with data 0xFFFFFFFF*/
    data = SDL_PIPE_START_DATA_ONE;
    for(bitIndex = 0; bitIndex < 32; bitIndex++)
    {
        data = data ^ (1U << bitIndex);
        result = SDL_PIPE_checkRegisterParity(SDL_ERRORAGGREGATOR_BASE, data, parity);
        data = SDL_PIPE_START_DATA_ONE;
        if(result==SDL_EFAIL)
        {
            break;
        }
    }

    if(result == SDL_PASS)
    {
        /* Start the parity check test with data 0x00000000*/
        data = SDL_PIPE_START_DATA_ZERO;
        for(bitIndex = 0; bitIndex < 32; bitIndex++)
        {
            data = data ^ (1U << bitIndex);
            result = SDL_PIPE_checkRegisterParity(SDL_ERRORAGGREGATOR_BASE, data, parity);
            data = SDL_PIPE_START_DATA_ZERO;
            if(result==SDL_EFAIL)
            {
                break;
            }
        }
    }
    
    if(result == SDL_PASS)
    {
        DebugP_log(" Parity check example successful \n");
    }
    else
    {
        DebugP_log(" Parity check example failed \n");
    }

}
int main(void)
{
    /* Initializes device clock and peripherals */
    Device_init();

    /* Board Initialization */
    Board_init();

    /*
     * Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
     */
    ENINT;

    Interrupt_enableGlobal();

    sdl_parity_check();

    while(1)
    {

    }

}
