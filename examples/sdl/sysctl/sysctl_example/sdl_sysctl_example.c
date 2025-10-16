/* ###########################################################################
 *
 * FILE:  sdl_sysctl_example.c
 *
 * TITLE: Example file for the demonstration of the sysctl library.
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
#include <sdl_sysctl.h>

SDL_ESM_Config SYSCTL_esmInitConfig =
{
    .enableBitmap =   {0x00000000U,     /* Group 0 is enabled by default */
                       SDL_ESM_EVENT_CLOCKFAIL_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       SDL_ESM_EVENT_SYSCTL_REG_PAR_ERR_MASK},
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
void SDL_ESM_WDISR(void)
{
    SDL_SYSCTL_handleWDIntr();
}

__attribute__((interrupt("INT")))
void SDL_ESMLowPriIntrISR(void)
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

void test_sdl_sysctl_test_app (void)
{
    /* Declarations of variables */
    int32_t retval;
    int32_t result;
    uint32_t status;

    printf("\n SYSCTL Example Test Application\r\n");

    Interrupt_register(INT_ESM_LOWPRI, &SDL_ESMLowPriIntrISR);
    Interrupt_enable(INT_ESM_LOWPRI);

    Interrupt_register(INT_WD, &SDL_ESM_WDISR);
    Interrupt_enable(INT_WD);

    result = SDL_ESM_init(SDL_ESMCPU1_BASE, &SYSCTL_esmInitConfig);

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

    retval = SDL_SYSCTL_checkDEVCFGParity();

    if(retval == SDL_PASS)
    {
        printf("\n DEVCFG: Parity Test Passed");
    }
    else
    {
        printf("\n DEVCFG: Parity Test got failed \r\n");
        return;
    }

    retval = SDL_SYSCTL_checkCPUSYSParity();

    if(retval == SDL_PASS)
    {
        printf("\n CPUSYS: Parity Test Passed");
    }
    else
    {
        printf("\n CPUSYS: Parity Test got Failed \r\n");
        return;
    }

    retval = SDL_SYSCTL_checkCPUPERCFGParity();

    if(retval == SDL_PASS)
    {
        printf("\n CPUPERCFG: Parity Test Passed");
    }
    else
    {
        printf("\n CPUPERCFG: Parity Test got Failed \r\n");
        return;
    }

    retval = SDL_SYSCTL_checkMCD();

    if(retval == SDL_PASS)
    {
        printf("\n MCD: Missing Clock Detection Passed");
    }
    else
    {
        printf("\n MCD: Missing Clock Detection Failed\r\n");
        return;
    }

    /* After an MCD event, the system clock needs to be reconfigured. */
    CLOCK_init();

    retval = SDL_SYSCTL_checkWDTimeout();

    if(retval == SDL_PASS)
    {
        printf("\n checkWDTimeout: Watchdog timeout test started");
    }
    else
    {
        printf("\n checkWDTimeout: Watchdog timeout did not start\r\n");
        return;
    }

    /*
    * Fail to reset the watchdog in time by delaying until it overflows. The
    * minimum delay was determined by considering the watchdog is an 8-bit
    * timer running off of INTOSC1 (10MHz) with a default pre-divider of /512.
    */
    DEVICE_DELAY_US(13800U);

    retval = SDL_SYSCTL_checkWDResult();
    if(retval == SDL_PASS)
    {
        printf("\n checkWDResults: test Watchdog timeout PASSED");
    }
    else
    {
        printf("\n checkWDResults: test Watchdog timeout FAILED\r\n");
        return;
    }

    retval = SDL_SYSCTL_checkWDWindow();
    DEVICE_DELAY_US(30U);
    if(retval == SDL_PASS)
    {
        printf("\n checkWDResults: Watchdog window test started");
    }
    else
    {
        printf("\n checkWDResults: Watchdog window did not start\r\n");
        return;
    }

    retval = SDL_SYSCTL_checkWDResult();
    if(retval == SDL_PASS)
    {
        printf("\n checkWDResults: test Watchdog window check PASSED");
    }
    else
    {
        printf("\n checkWDResults: test Watchdog window check FAILED\r\n");
        return;
    }

    if (retval == SDL_PASS)
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

    test_sdl_sysctl_test_app();

    while(1);
}