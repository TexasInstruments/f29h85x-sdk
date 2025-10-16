/* ###########################################################################
 *
 * FILE:  sdl_memss_example.c
 *
 * ############################################################################
 *
 *  TITLE: Example file for the demonstration of the memss library.
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
#include <sdl_esm.h>
#include <sdl_memss.h>
#include <kernel/dpl/DebugP.h>
#include <sdl_err_aggr.h>


SDL_ESM_Config MEMSS_esmInitConfig =
{
    .enableBitmap   = {0x00000000U, /* Group 0 will be enabled via NMI errata workaround */
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       SDL_ESM_EVENT_ErrorAggregator_CPU1_LPERR_MASK,
                       0x00000000U,
                       0x00000000U,
                       SDL_ESM_EVENT_MEMSS_REG_PAR_ERR_MASK},
    .priorityBitmap = {0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U}
};

__attribute__((interrupt("INT")))
void esmLowPriIntrISR(void)
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

void test_sdl_memss_test_app(void)
{
    int32_t result;

    DebugP_log("\n MEMSS UNIT Test Application\r\n");

    result = SDL_ESM_init(SDL_ESMCPU1_BASE, &MEMSS_esmInitConfig);

    /* Register the ESM interrupt handlers */
    Interrupt_register(INT_ESM_LOWPRI, &esmLowPriIntrISR);
    Interrupt_enable(INT_ESM_LOWPRI);

    Interrupt_configNMI(&nmiISR, SSU_LINK2);

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

    result = SDL_MEMSS_checkRegisterParity();

    if (result == SDL_PASS)
{
    DebugP_log("checkRegisterParity Pass\n");
}
else
{
    DebugP_log("checkRegisterParity Fail, result = %d\n", result);
}

    result = SDL_MEMSS_testECCInjection(SDL_ERRORAGGREGATOR_BASE, SDL_MEMSS_RAM_CDA0,
                                        (uint32_t *)0x20120000, SDL_MEMSS_TESTMODE_DATA_ONLY,
                                        0x00000001U);

    if (result == SDL_PASS)
    {
        DebugP_log("testECCInjection (correctable, data bits) Pass\n");
    }
    else
    {
        DebugP_log("testECCInjection Fail, result = %d\n", result);
    }

    result = SDL_MEMSS_testECCInjection(SDL_ERRORAGGREGATOR_BASE, SDL_MEMSS_RAM_CDA1,
                                        (uint32_t *)0x20124000, SDL_MEMSS_TESTMODE_DATA_ONLY,
                                        0x00030000U);

    if (result == SDL_PASS)
    {
        DebugP_log("testECCInjection (uncorrectable, data bits) Pass\n");
    }
    else
    {
        DebugP_log("testECCInjection Fail, result = %d\n", result);
    }


    result = SDL_MEMSS_testECCInjection(SDL_ERRORAGGREGATOR_BASE, SDL_MEMSS_RAM_CDA1,
                                        (uint32_t *)0x20124000, SDL_MEMSS_TESTMODE_ECC_ONLY,
                                        0x00000001U);

    if (result == SDL_PASS)
    {
        DebugP_log("testECCInjection (correctable, ECC bits) Pass\n");
    }
    else
    {
        DebugP_log("testECCInjection Fail, result = %d\n", result);
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

    test_sdl_memss_test_app();

    while(1);
}