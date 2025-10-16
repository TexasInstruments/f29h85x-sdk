/* ###########################################################################
 *
 * FILE:  sdl_sic_example.c
 *
 * TITLE: Example file for the demonstration of the sic library.
 *
 *
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

########################################################################### */


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "board.h"
#include <stdio.h>

#include <kernel/dpl/DebugP.h>
#include <sdl_esm.h>
#include <sdl_sic.h>


/* RTDMA supporting declarations/definitions*/
static uint32_t TxData __attribute__((aligned(8))) = 0xA5A55A5AU;  /* Send data buffer */
static uint32_t RxData __attribute__((aligned(8))) = 0x12345678U;  /* Receive data buffer */
static uint32_t ramAddr __attribute__((aligned(16)));


SDL_ESM_Config SIC_esmInitConfig =
{
    .enableBitmap =   {0x00000000U,     /* Group 0 is enabled by default */
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       SDL_ESM_EVENT_ErrorAggregator_RTDMA1_HPERR_MASK |
                       SDL_ESM_EVENT_ErrorAggregator_RTDMA2_HPERR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
    .priorityBitmap = {0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       SDL_ESM_EVENT_ErrorAggregator_RTDMA1_HPERR_MASK |
                       SDL_ESM_EVENT_ErrorAggregator_RTDMA2_HPERR_MASK,
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

__attribute__((interrupt("INT")))
void SDL_ESMLowPriIntrISR(void)
{
    SDL_ESM_IntrStatus intrStatus;

    do
    {
        /* Get ESM interrupt status and try to clear event */
        SDL_ESM_loInterruptHandler(SDL_ESMCPU1_BASE, &intrStatus);

        /*
         * This example only uses high priority interrupts. If you hit this
         * breakpoint, something unexpected has happened.
         */
        ESTOP0;

    }while(intrStatus.nextPendPulseEvent != SDL_ESM_NO_EVENT_VALUE);

    SDL_ESM_writeEOI(SDL_ESMCPU1_BASE, SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR);
}

__attribute__((interrupt("RTINT")))
void nmiISR(void)
{
    SDL_ESM_IntrStatus intrStatus;

    do
    {
        /* Get ESM interrupt status and try to clear event */
        SDL_ESM_hiInterruptHandler(SDL_ESMCPU1_BASE, &intrStatus);

        if(intrStatus.selfTestStatus != SDL_ESM_SELF_TEST_ACTIVE)
        {
            /* Unexpected ESM event */
            ESTOP0;
        }

    }while(intrStatus.nextPendPulseEvent != SDL_ESM_NO_EVENT_VALUE);

    SDL_ESM_writeEOI(SDL_ESMCPU1_BASE, SDL_ESM_INTR_TYPE_HIGH_PRIO_ERROR);
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

    Interrupt_configNMI(&nmiISR, SSU_LINK2);
}

void test_sdl_sic_test_app (void)
{
    /* Declarations of variables */
    int32_t retVal;
    int32_t result;
    uint32_t status;
    const void *destAddr = (const void *)&RxData;
    const void *srcAddr = (const void *)&TxData;
    uint32_t *memAddr = &ramAddr;

    printf("\n SIC Example Test Application\r\n");

    result = SDL_ESM_init(SDL_ESMCPU1_BASE, &SIC_esmInitConfig);

    /* Register the SDL_ESM interrupt handler */
    SDL_registerESMISR();

    if (result != SDL_PASS)
    {
        /* print error and quit */
        DebugP_log("Error initializing ESM: result = %d\n", result);
        return;
    }
    else
    {
        DebugP_log("\nInit ESM complete \n");
    }

    retVal = SDL_SIC_enableSafety();

    if(retVal == SDL_PASS)
    {
        printf("\n Enabled the SIC module");
    }
    else
    {
        printf("\n Enable SIC module test got failed \r\n");
        return;
    }

    retVal = SDL_SIC_setTimeout(0x007F);

    if(retVal == SDL_PASS)
    {
        printf("\n Timeout: Set Timeout test passed");
    }
    else
    {
        printf("\n Timeout: Set Timeout test got failed \r\n");
        return;
    }

    retVal = SDL_SIC_PIPE_emulateFault(SDL_ERRORAGGREGATOR_BASE, INT_ADCA3);

    if(retVal == SDL_PASS)
    {
        printf("\n PIPE: fault emulation test passed");
    }
    else
    {
        printf("\n PIPE: fault emulation test got failed \r\n");
        return;
    }

    retVal = SDL_SIC_CPU_DR1_emulateFault(SDL_ERRORAGGREGATOR_BASE, memAddr);

    if(retVal == SDL_PASS)
    {
        printf("\n CPU DR1: fault emulation test passed");
    }
    else
    {
        printf("\n CPU DR1: fault emulation test got failed \r\n");
        return;
    }

    retVal = SDL_SIC_CPU_DR2_emulateFault(SDL_ERRORAGGREGATOR_BASE, memAddr);

    if(retVal == SDL_PASS)
    {
        printf("\n CPU DR2: fault emulation test passed");
    }
    else
    {
        printf("\n CPU DR2: fault emulation test got failed \r\n");
        return;
    }

    retVal = SDL_SIC_CPU_DW_emulateFault(SDL_ERRORAGGREGATOR_BASE, memAddr);

    if(retVal == SDL_PASS)
    {
        printf("\n CPU DW: fault emulation test passed");
    }
    else
    {
        printf("\n CPU DW: fault emulation test got failed \r\n");
        return;
    }

    retVal = SDL_SIC_CPU_PR_emulateFault(SDL_ERRORAGGREGATOR_BASE, memAddr);

    if(retVal == SDL_PASS)
    {
        printf("\n CPU PR: fault emulation test passed");
    }
    else
    {
        printf("\n CPU PR: fault emulation test got failed \r\n");
        return;
    }

    DMA_disableMPU(RTDMA1_MPU_BASE);
    retVal = SDL_SIC_RTDMA_DR_emulateFault(SDL_ERRORAGGREGATOR_BASE,
                                           SDL_RTDMA1_BASE, SDL_RTDMA1CH1_BASE,
                                           destAddr, srcAddr);

    if(retVal == SDL_PASS)
    {
        printf("\n RTDMA DR: fault emulation test passed");
    }
    else
    {
        printf("\n RTDMA DR: fault emulation test got failed \r\n");
        return;
    }

    retVal = SDL_SIC_RTDMA_DW_emulateFault(SDL_ERRORAGGREGATOR_BASE,
                                           SDL_RTDMA1_BASE, SDL_RTDMA1CH1_BASE,
                                           destAddr, srcAddr);

    if(retVal == SDL_PASS)
    {
        printf("\n RTDMA DW: fault emulation test passed");
    }
    else
    {
        printf("\n RTDMA DW: fault emulation test got failed \r\n");
        return;
    }

    if (retVal == SDL_PASS)
    {
        printf("\n All tests have passed.\r\n");
    }
    else
    {
        printf("\n Few/all tests Failed \r\n");
    }
}

/*
 * Main
 */
int main(void)
{
    /*
     * Initialize device clock, peripheral clocks and interrupts
     */
    Device_init();

    /*
     * Board Initialization
     */
    Board_init();

    /*
     * Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
     */
    ENINT;
    Interrupt_enableGlobal();

    test_sdl_sic_test_app();

    while(1);
}