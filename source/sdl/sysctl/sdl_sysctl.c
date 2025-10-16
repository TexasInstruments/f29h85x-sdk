/* ###########################################################################
 *
 * FILE:  sdl_sysctl.c
 *
 * TITLE: Diagnostic Library SYSCTL software module source
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

#include <sdl_esm.h>
#include "sdl_sysctl.h"

#define SDL_SYSCTL_DELAY __asm(" NOP #7")

static volatile uint32_t SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
static volatile bool SDL_SYSCTL_mcdDetect = FALSE;

void SDL_SYSCTL_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg)
{
    if(intSrc == SDL_ESM_EVENT_CLOCKFAIL)
    {
        SDL_SYSCTL_isrFlag = SDL_SYSCTL_INTERRUPT;

        /* If the Interrupt caused by MCD*/
        SDL_SYSCTL_mcdDetect = ((HWREGH(SDL_DEVCFG_BASE + SDL_SYSCTL_O_MCDCR) & SDL_SYSCTL_MCDCR_MCLKSTS) != 0U);

        /*Re-connect missing clock detection to clock source to stop simulating
        clock failure.*/
        HWREGH(SDL_DEVCFG_BASE + SDL_SYSCTL_O_MCDCR) &= (uint16_t)(~SDL_SYSCTL_MCDCR_OSCOFF);

        /*Reset the missing clock detection logic after clock failure.*/
        HWREGH(SDL_DEVCFG_BASE + SDL_SYSCTL_O_MCDCR) |= SDL_SYSCTL_MCDCR_MCLKCLR;
    }
    else if(intSrc == SDL_ESM_EVENT_SYSCTL_REG_PAR_ERR)
    {
        SDL_SYSCTL_isrFlag = SDL_SYSCTL_INTERRUPT;
    }
    else
    {
        /* Do nothing. Unexpected event type. */
    }
}

void SDL_SYSCTL_handleWDIntr(void)
{
    SDL_SYSCTL_isrFlag = SDL_SYSCTL_INTERRUPT;
}

int32_t SDL_SYSCTL_checkDEVCFGParity(void)
{
    int32_t status = SDL_EFAIL;
    volatile uint32_t errFlagTimeout = 10U;

    /*
      Turn on MMR parity test mode.
    */
    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_PARITY_TEST) = SDL_SYSCTL_PARITY_TEST_KEY;

    /*
      Check that an error is detected when a parity error is injected in each
      of the parity-protected registers. Each time we'll inject an error,
      wait for the error flags to be set by ESM, clear the error flags, and move to
      the next bit.
    */
    SDL_ESM_setSelfTestCallback(&SDL_SYSCTL_handleESMIntr, NULL);
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /*DEVCFGL - BYTE-0*/
    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_DEVCFGLOCK1) = 1U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*PARTIDL - BYTE-1*/
    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_PARTIDL) = 0x100U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*CLKSRCCTL - BYTE-2*/
    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_CLKSRCCTL2) = 0x10000U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*SYNCSELCT - BYTE-3*/
    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_SYNCSELECT) = 0x1000000U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /*
      Turn off MMR parity test mode.
    */
    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_PARITY_TEST) = 0U;

    /* Deassert self-test */
    SDL_ESM_clearSelfTestCallback();
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

    /*
      If any of the checks failed to produce a REGPARITY_ERR_FLG in the
      expected time frame, return SDL_FAIL. Otherwise, return PASS.
    */

    if(errFlagTimeout != 0U)
    {
        status = SDL_PASS;
    }
    else
    {
        status = SDL_EFAIL;
    }

    return(status);
}

int32_t SDL_SYSCTL_checkCPUSYSParity(void)
{
    int32_t status = SDL_EFAIL;
    volatile uint32_t errFlagTimeout = 10U;

    /*
      Turn on MMR parity test mode.
    */
    HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_PARITY_TEST_ALT2) = SDL_SYSCTL_PARITY_TEST_KEY;

    /*
      Check that an error is detected when a parity error is injected in each
      of the parity-protected registers. Each time we'll inject an error,
      wait for the error flags to be set by ESM, clear the error flags, and move to
      the next bit.
    */
    SDL_ESM_setSelfTestCallback(&SDL_SYSCTL_handleESMIntr, NULL);
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /*LPCMR - BYTE-0*/
    HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_LPMCR) = 1U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*GPIO0 - BYTE-1*/
    HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_GPIOLPMSEL0) = 0x100U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*GPIO1 - BYTE-2*/
    HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_GPIOLPMSEL1) = 0x10000U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*CPUSYSLOCK1 - BYTE-3*/
    HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUPERCFGLOCK1) = 0x1000000U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /*
      Turn off MMR parity test mode.
    */
    HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_PARITY_TEST_ALT2) = 0U;

    /* Deassert self-test */
    SDL_ESM_clearSelfTestCallback();
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

    /*
      If any of the checks failed to produce a REGPARITY_ERR_FLG in the
      expected time frame, return SDL_FAIL. Otherwise, return PASS.
    */

    if(errFlagTimeout != 0U)
    {
        status = SDL_PASS;
    }
    else
    {
        status = SDL_EFAIL;
    }

    return(status);
}

int32_t SDL_SYSCTL_checkCPUPERCFGParity(void)
{
    int32_t status = SDL_EFAIL;
    volatile uint32_t errFlagTimeout = 10U;

    /*
      Turn on MMR parity test mode.
    */
    HWREG(SDL_CPUPERCFG_BASE + SDL_SYSCTL_O_PARITY_TEST_ALT1) = SDL_SYSCTL_PARITY_TEST_KEY;

    /*
      Check that an error is detected when a parity error is injected in each
      of the parity-protected registers. Each time we'll inject an error,
      wait for the error flags to be set by ESM, clear the error flags, and move to
      the next bit.
    */
    SDL_ESM_setSelfTestCallback(&SDL_SYSCTL_handleESMIntr, NULL);
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /*PCLKCR1 - BYTE-0*/
    HWREG(SDL_CPUPERCFG_BASE + SDL_SYSCTL_O_PCLKCR1) = 1U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*PCLKCR10 - BYTE-1*/
    HWREG(SDL_CPUPERCFG_BASE + SDL_SYSCTL_O_PCLKCR10) = 0x100U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*SOFTPRES2 - BYTE-2*/
    HWREG(SDL_CPUPERCFG_BASE + SDL_SYSCTL_O_SOFTPRES2) = 0x10000U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /*SOFTPRES0 - BYTE-3*/
    HWREG(SDL_CPUPERCFG_BASE + SDL_SYSCTL_O_SOFTPRES0) = 0x1000000U;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /*
      Turn off MMR parity test mode.
    */
    HWREG(SDL_CPUPERCFG_BASE + SDL_SYSCTL_O_PARITY_TEST_ALT1) = 0U;

    /* Deassert self-test */
    SDL_ESM_clearSelfTestCallback();
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

    /*
      If any of the checks failed to produce a REGPARITY_ERR_FLG in the
      expected time frame, return SDL_FAIL. Otherwise, return PASS.
    */
    if(errFlagTimeout != 0U)
    {
        status = SDL_PASS;
    }
    else
    {
        status = SDL_EFAIL;
    }

    return(status);
}

int32_t SDL_SYSCTL_checkMCD(void)
{
    int32_t status = SDL_EFAIL;
    volatile uint32_t errFlagTimeout = 10000U;
    uint32_t errCount = 0, timeoutCnt = 0U, busyStatus = 1U;

    /* Register self-test */
    SDL_ESM_setSelfTestCallback(&SDL_SYSCTL_handleESMIntr, NULL);
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /*Turn on MCD mode*/
    HWREGH(SDL_DEVCFG_BASE + SDL_SYSCTL_O_MCDCR) &= (uint16_t)(~SDL_SYSCTL_MCDCR_MCLKOFF);

    /* Simulate a missing clock.*/
    HWREGH(SDL_DEVCFG_BASE + SDL_SYSCTL_O_MCDCR) |= SDL_SYSCTL_MCDCR_OSCOFF;

    while((SDL_SYSCTL_isrFlag == SDL_SYSCTL_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout-=1U;
    }

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /* A missing clock was detected.*/
    if(SDL_SYSCTL_mcdDetect != true)
    {
        errCount++;
    }

    /*  Wait for BUSY bit to clear */
    while((HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_SYNCBUSY) & SDL_SYSCTL_SYNCBUSY_CLKSRCCTL1) ==
                                                            SDL_SYSCTL_SYNCBUSY_CLKSRCCTL1)
    {
        if(timeoutCnt >= SDL_SYSCTL_SYNCBUSY_TIMEOUT_CYCLES)
        {
            busyStatus = 0U;
            break;
        }

        timeoutCnt++;
    }

    /* Deassert self-test */
    SDL_ESM_clearSelfTestCallback();
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

    if(errCount != 0U)
    {
        status = SDL_EFAIL;
    }
    else
    {
        status = SDL_PASS;
    }

    return(status);
}

int32_t SDL_SYSCTL_checkWDTimeout(void)
{
    int32_t status = SDL_EFAIL;
    volatile uint16_t errCount = 0;
    uint32_t timeoutCnt = 0U, busyStatus = 1U;

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /* Set the watchdog to generate an interrupt signal instead of a reset signal.*/
    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_SCSR) =
                (uint16_t)((HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_SCSR) & ~SDL_SYSCTL_SCSR_WDOVERRIDE) |
                SDL_SYSCTL_SCSR_WDENINT);

    /* Enable the counter to be reset */
    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDKEY) = SDL_SYSCTL_WD_ENRSTKEY;

    /* Reset the watchdog counter*/
    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDKEY) = SDL_SYSCTL_WD_RSTKEY;

    /* Set lower boundary of the watchdog window.*/
    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDWCR) &= (uint16_t)(~SDL_SYSCTL_WDWCR_MIN_M);

    /* Set the windowed value*/
    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDWCR) |= (SDL_SYSCTL_WD_WINDOW & SDL_SYSCTL_WDWCR_MIN_M);

    /* Enable the watchdog.*/
    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDCR) = (uint16_t)((HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDCR) &
                                       ~SDL_SYSCTL_WDCR_WDDIS) | SDL_SYSCTL_WD_CHKBITS);

    /*  Wait for BUSY bit to clear */
    while((HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_SYNCBUSYWD) & SDL_SYSCTL_SYNCBUSYWD_WDCR) == SDL_SYSCTL_SYNCBUSYWD_WDCR)
    {
        if(timeoutCnt >= SDL_SYSCTL_SYNCBUSY_TIMEOUT_CYCLES)
        {
            busyStatus = 0U;
            break;
        }

        timeoutCnt++;
    }

    if(busyStatus != 1U)
    {
        status = SDL_EFAIL;
    }
    else
    {
        status = SDL_PASS;
    }

    return (status);

}

int32_t SDL_SYSCTL_checkWDWindow(void)
{
    int32_t status = SDL_PASS;
    volatile uint16_t errCount = 0;

    SDL_SYSCTL_isrFlag = SDL_SYSCTL_NO_INTERRUPT;

    /* Test the windowing feature by resetting the watchdog before it has a
       chance to reach the window threshold.*/

    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDKEY) = SDL_SYSCTL_WD_ENRSTKEY;
    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDKEY) = SDL_SYSCTL_WD_RSTKEY;

    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDKEY) = SDL_SYSCTL_WD_ENRSTKEY;
    HWREGH(SDL_WD_BASE + SDL_SYSCTL_O_WDKEY) = SDL_SYSCTL_WD_RSTKEY;

    return (status);
}

int32_t SDL_SYSCTL_checkWDResult(void)
{
    int32_t status = SDL_EFAIL;

    if(SDL_SYSCTL_isrFlag == SDL_SYSCTL_INTERRUPT)
    {
        status = SDL_PASS;
    }

    return (status);
}
