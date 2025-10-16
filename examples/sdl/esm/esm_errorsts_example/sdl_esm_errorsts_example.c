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
 *  \file     sdl_esm_errorsts_example.c
 *
 *  \brief    This file contains ESM Error Status Testcase .
 *
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include "device.h"
#include "board.h"
#include <kernel/dpl/DebugP.h>
#include <esm/sdl_esm.h>
#include <esm/sdlr_edc.h>
#include <esm/sdlr_esm_safety_aggr.h>

/*===========================================================================*/
/*                         Macros and Structures                             */
/*===========================================================================*/

#define ERRORSTS_PIN 79U

SDL_ESM_Config pConfig = 
{
    .enableBitmap =   {0x00000000U,
                       SDL_ESM_EVENT_DCC1_ERR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
    .priorityBitmap = {0x00000000U,
                       SDL_ESM_EVENT_DCC1_ERR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
    .errorPinBitmap = {0x00000000U,
                       SDL_ESM_EVENT_DCC1_ERR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
};

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/

volatile uint32_t pinVal = 0xFU, readVal;

/*===========================================================================*/
/*                   Internal & External function declarations               */
/*===========================================================================*/

static void SDL_clearESMStatus(void);

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

int main(void)
{
    int32_t result;
    uint32_t errFlagTimeout = 50U;
    uint32_t esmBaseAddr = SDL_ESMSYSTEM_BASE;
    Device_init();

    /* Board Initialization */
    Board_init();

    ENINT;
    Interrupt_enableGlobal();

    result = SDL_ESM_init(esmBaseAddr, &pConfig);

    if (result != SDL_PASS)
    {
        /* print error and quit */
        DebugP_log("Error initializing ESM: result = %d\n", result);
    }
    else
    {
        DebugP_log("\nInit ESM complete \n");
    }

    readVal = GPIO_readPin(ERRORSTS_PIN);
    pinVal = readVal;
    DebugP_log(" Error Status Pin value before forced error event = %d\n", readVal);

    /*set Error Pin Preload counter to lower value 0xFFF */
    SDL_ESM_setErrPinLowTimePreload(esmBaseAddr, 0xFFFU);

    /* force the error event interrupt */
    SDL_ESM_setIntrStatusRAW(SDL_ESMSYSTEM_BASE, SDL_ESM_EVENT_DCC1_ERR);

    while((pinVal == readVal) && (errFlagTimeout != 0U))
    {
        errFlagTimeout--;
        pinVal = GPIO_readPin(ERRORSTS_PIN);
    }

    if(pinVal != readVal)
    {
        DebugP_log(" Error Status Pin value after forced error event = %d\n"
                   " Error Status Example Passed \n", pinVal);
        SDL_clearESMStatus();
    }
    else
    {
        SDL_ESM_resetErrPin(SDL_ESMSYSTEM_BASE);
        DebugP_log(" Error Status Example Failed \n");
    }
    
    while(1)
    {
        /* End of the Example */
    }
}

static void SDL_clearESMStatus(void)
{
    SDL_ESM_clearIntrStatus(SDL_ESMSYSTEM_BASE, SDL_ESM_EVENT_DCC1_ERR);
    SDL_ESM_resetErrPin(SDL_ESMSYSTEM_BASE);
}