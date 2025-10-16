/*
 * FILE:  sdl_lcm.c
 *
 * TITLE: Diagnostic Library LCM software module source
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
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <sdl_esm.h>
#include "sdl_lcm.h"

static volatile uint32_t SDL_LCM_isrFlag = SDL_LCM_NO_INTERRUPT;

void SDL_LCM_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg)
{
    SDL_LCM_isrFlag = SDL_LCM_INTERRUPT;
}

/******************************************************************************
 *
 * SDL_LCM_checkRegisterParity(uint32_t lcmBase)
 *
 *****************************************************************************/

int32_t SDL_LCM_checkRegisterParity(uint32_t lcmBase)
{
    int32_t status = SDL_EFAIL;
    volatile uint32_t errFlagTimeout = SDL_LCM_PARITY_TIMEOUT;
    SDL_LCM_isrFlag = SDL_LCM_NO_INTERRUPT;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        SDL_ESM_setSelfTestCallback(&SDL_LCM_handleESMIntr, NULL);
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        /*
         * Turn on MMR parity test mode.
         */
        HWREG(lcmBase + SDL_LCM_PARITY_TEST) = SDL_LCM_PARITY_TEST_KEY;

        /*
         * Check that an error is detected when a parity error is injected in each
         * of the parity-protected registers. Each time we'll inject an error,
         * wait for the error flags to be set by ESM, clear the error flags, and move to
         * the next bit.
         *
         * CONTROL - Byte 0
         */
        HWREGB(lcmBase + SDL_LCM_CONTROL) = 1U;

        while((SDL_LCM_isrFlag == SDL_LCM_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout-=1U;
        }

        SDL_LCM_isrFlag = SDL_LCM_NO_INTERRUPT;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        /*
         * STATUS - Byte 1
         */
        HWREGB(lcmBase + SDL_LCM_STATUS + 1U) = 1U;

        while((SDL_LCM_isrFlag == SDL_LCM_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout-=1U;
        }

        SDL_LCM_isrFlag = SDL_LCM_NO_INTERRUPT;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        /*
         * LOCK - Byte 0
         */
        HWREGB(lcmBase + SDL_LCM_LOCK) = 1U;

        while((SDL_LCM_isrFlag == SDL_LCM_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout-=1U;
        }

        SDL_LCM_isrFlag = SDL_LCM_NO_INTERRUPT;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        /*
         * COMMIT - Byte 1
         */
        HWREGB(lcmBase + SDL_LCM_COMMIT + 1U) = 1U;

        while((SDL_LCM_isrFlag == SDL_LCM_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout-=1U;
        }

        /*
         * Turn off MMR parity test mode.
         */
        HWREG(lcmBase + SDL_LCM_PARITY_TEST) = 0U;
        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        /*
         * If any of the checks failed to produce a REGPARITY_ERR_FLG in the
         * expected time frame, return SDL_FAIL. Otherwise, return PASS.
         */
        if(errFlagTimeout != 0U)
        {
            status = SDL_PASS;
        }
        else
        {
            status = SDL_EFAIL;
        }
    }

    return(status);
}

/********************************************************************************
 *
 * SDL_LCM_enableLockstep(void)
 *
 *******************************************************************************/

int32_t SDL_LCM_enableLockstep(void)
{
    int32_t status = SDL_EFAIL;
    uint32_t lcmStatus;

    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_LSEN) = SDL_SYSCTL_LSEN_ENABLE;
    lcmStatus = HWREG(SDL_LCM_CPU_BASE + SDL_LCM_STATUS) & SDL_LCM_STATUS_LSEN;

    if(lcmStatus == 1U)
    {
        status = SDL_PASS;
    }

    return status;
}

/********************************************************************************
 *
 * SDL_LCM_disableLockstep(uint32_t lcmBase)
 *
 *******************************************************************************/

int32_t SDL_LCM_disableLockstep(uint32_t lcmBase)
{
    int32_t status = SDL_EFAIL;
    uint32_t lcmStatus;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }

    else
    {

        HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_LSEN) = SDL_SYSCTL_LSEN_DISABLE;
        lcmStatus = HWREG(lcmBase + SDL_LCM_STATUS) & SDL_LCM_STATUS_LSEN;

        if(lcmStatus == 0U)
        {
            status = SDL_PASS;
        }
    }

    return status;
}

/********************************************************************************
 *
 * SDL_LCM_enableLockstep(uint32_t lcmBase)
 *
 *******************************************************************************/

int32_t SDL_LCM_enableComparator(uint32_t lcmBase)
{
    int32_t status = SDL_EFAIL;
    uint32_t lcmStatus;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }

    else
    {

        HWREG(lcmBase + SDL_LCM_CONTROL) = 1U;
        lcmStatus = HWREG(lcmBase + SDL_LCM_CONTROL) & SDL_LCM_CONTROL_CMPEN;

        if(lcmStatus == 1U)
        {
            status = SDL_PASS;
        }
    }

    return status;
}

/********************************************************************************
 *
 * SDL_LCM_disableComparator(uint32_t lcmBase)
 *
 *******************************************************************************/

int32_t SDL_LCM_disableComparator(uint32_t lcmBase)
{
    int32_t status = SDL_EFAIL;
    uint32_t lcmStatus;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }

    else
    {

        HWREG(lcmBase + SDL_LCM_CONTROL) = 0U;
        lcmStatus = HWREG(lcmBase + SDL_LCM_CONTROL) & SDL_LCM_CONTROL_CMPEN;

        if(lcmStatus == 0U)
        {
            status = SDL_PASS;
        }
    }

    return status;
}

/********************************************************************************
 *
 * SDL_LCM_runSelfTest(uint32_t lcmBase)
 *
 *******************************************************************************/

int32_t SDL_LCM_runSelfTest(uint32_t lcmBase)
{
    uint32_t lcmStatus;
    uint32_t errorCount = 0U;
    int32_t status = SDL_EFAIL;
    volatile uint32_t stTimeout = SDL_LCM_SELF_TEST_TIMEOUT;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        HWREG(lcmBase + SDL_LCM_STATUS_CLEAR) = (SDL_LCM_STATUS_CLEAR_STPASS |
                                                 SDL_LCM_STATUS_CLEAR_STDONE);

        /*
         * Enable the self-test.
         */
        HWREG(lcmBase + SDL_LCM_CONTROL) = SDL_LCM_CONTROL_STEN;

        /*
         * We'll mask out the "debugger connected" bit throughout this test to
         * allow it to work both with and without a debug connection.
         */
        lcmStatus = HWREG(lcmBase + SDL_LCM_STATUS) & ~(uint32_t)SDL_LCM_STATUS_DBGCON;

        /*
         * Wait until the self-test finishes, checking and decrementing a software
         * timeout variable to make sure it doesn't get stuck.
         */
        while(((lcmStatus & SDL_LCM_STATUS_STDONE) == 0U) && (0U != stTimeout))
        {
            if(lcmStatus != (SDL_LCM_STATUS_STACTIVE | SDL_LCM_STATUS_LSEN))
            {
                errorCount++;
            }

            lcmStatus = HWREG(lcmBase + SDL_LCM_STATUS) &
                        ~(uint32_t)SDL_LCM_STATUS_DBGCON;
            stTimeout-=1U;
        }

        /*
         * LCM status should show that LCM is done and passed.
         */
        if(lcmStatus != (SDL_LCM_STATUS_STDONE | SDL_LCM_STATUS_STPASS | SDL_LCM_STATUS_LSEN))
        {
            errorCount++;
        }

        /*
         * Negative check of status clear register.
         */
        HWREG(lcmBase + SDL_LCM_STATUS_CLEAR) = 0U;
        HWREG(lcmBase + SDL_LCM_STATUS_CLEAR) = ~(SDL_LCM_STATUS_CLEAR_STPASS |
                                                SDL_LCM_STATUS_CLEAR_STDONE);

        lcmStatus = HWREG(lcmBase + SDL_LCM_STATUS) & ~(uint32_t)SDL_LCM_STATUS_DBGCON;
        if(lcmStatus != (SDL_LCM_STATUS_STDONE | SDL_LCM_STATUS_STPASS | SDL_LCM_STATUS_LSEN))
        {
            errorCount++;
        }

        /*
         * Clear pass bit.
         */
        HWREG(lcmBase + SDL_LCM_STATUS_CLEAR) = SDL_LCM_STATUS_CLEAR_STPASS;

        lcmStatus = HWREG(lcmBase + SDL_LCM_STATUS) & ~(uint32_t)SDL_LCM_STATUS_DBGCON;
        if(lcmStatus != (SDL_LCM_STATUS_STDONE | SDL_LCM_STATUS_LSEN))
        {
            errorCount++;
        }

        /*
         * Clear done bit.
         */
        HWREG(lcmBase + SDL_LCM_STATUS_CLEAR) = SDL_LCM_STATUS_CLEAR_STDONE;

        lcmStatus = HWREG(lcmBase + SDL_LCM_STATUS) & ~(uint32_t)SDL_LCM_STATUS_DBGCON;
        if(lcmStatus != SDL_LCM_STATUS_LSEN)
        {
            errorCount++;
        }

        if(errorCount == 0U)
        {
            status = SDL_PASS;
        }
        else
        {
            status = SDL_EFAIL;
        }
    }

    return(status);
}

/********************************************************************************
 *
 * SDL_LCM_checkCompareError(uint32_t lcmBase)
 *
 *******************************************************************************/

int32_t SDL_LCM_checkCompareError(uint32_t lcmBase)
{
    uint32_t errorCount = 0U;
    int32_t status = SDL_EFAIL;
    volatile uint32_t cmp1Timeout = SDL_LCM_ERROR_FORCE_TIMEOUT;
    volatile uint32_t cmp2Timeout = SDL_LCM_ERROR_FORCE_TIMEOUT;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        /*
         * Test CMP1 error force
         */
        SDL_ESM_setSelfTestCallback(&SDL_LCM_handleESMIntr, NULL);
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        HWREG(lcmBase + SDL_LCM_CONTROL) = SDL_LCM_CONTROL_CMP1_ERR_FORCE |
                                            SDL_LCM_CONTROL_CMPEN;

        /*
         * Wait for the force to complete.
         */
        while(((HWREG(lcmBase + SDL_LCM_STATUS) &
                SDL_LCM_STATUS_CMP1_ERR_FORCE_DONE) == 0U) && (cmp1Timeout != 0U))
        {
            cmp1Timeout-=1U;
        }

        /*
         * Check that the expected LCM-level flags are set and then clear them.
         */
        if(HWREG(lcmBase + SDL_LCM_STATUS) != (SDL_LCM_STATUS_CMP1_ERR_FORCE_DONE |
                                                SDL_LCM_STATUS_CMP1_ERR_FORCE_PASS |
                                                SDL_LCM_STATUS_LSEN))
        {
            errorCount++;
        }

        HWREG(lcmBase + SDL_LCM_STATUS_CLEAR) =
                SDL_LCM_STATUS_CMP1_ERR_FORCE_DONE | SDL_LCM_STATUS_CMP1_ERR_FORCE_PASS;

        /*
         * Test CMP2 error force
         */
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);
        HWREG(lcmBase + SDL_LCM_CONTROL) = SDL_LCM_CONTROL_CMP2_ERR_FORCE |
                                            SDL_LCM_CONTROL_CMPEN;

        /*
         * Wait for the force to complete.
         */
        while(((HWREG(lcmBase + SDL_LCM_STATUS) &
                SDL_LCM_STATUS_CMP2_ERR_FORCE_DONE) == 0U) && (cmp2Timeout != 0U))
        {
            cmp2Timeout-=1U;
        }

        /*
         * Check that the expected LCM-level flags are set and then clear them.
         */
        if(HWREG(lcmBase + SDL_LCM_STATUS) != (SDL_LCM_STATUS_CMP2_ERR_FORCE_DONE |
                                                SDL_LCM_STATUS_CMP2_ERR_FORCE_PASS |
                                                SDL_LCM_STATUS_LSEN))
        {
            errorCount++;
        }

        HWREG(lcmBase + SDL_LCM_STATUS_CLEAR) =
                SDL_LCM_STATUS_CMP2_ERR_FORCE_DONE | SDL_LCM_STATUS_CMP2_ERR_FORCE_PASS;

        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        if(errorCount == 0U)
        {
            status = SDL_PASS;
        }
        else
        {
            status = SDL_EFAIL;
        }
    }

    return(status);
}

/********************************************************************************
 *
 * SDL_LCM_getStatus(uint32_t lcmBase,uint32_t *pStatus)
 *
 *******************************************************************************/

int32_t SDL_LCM_getStatus(uint32_t lcmBase,uint32_t *pStatus)
{

    int32_t status = SDL_EFAIL;

    if(((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE)) || (pStatus == NULL))
    {
        status = SDL_EBADARGS;
    }

    else
    {

        *pStatus = HWREG(lcmBase + SDL_LCM_STATUS);
         status = SDL_PASS;
    }

    return status;
}

/********************************************************************************
 *
 * SDL_LCM_clearStatus(uint32_t lcmBase, uint32_t clearStatus)
 *
 *******************************************************************************/

int32_t SDL_LCM_clearStatus(uint32_t lcmBase, uint32_t clearStatus)
{
    int32_t status = SDL_EFAIL;
    uint32_t lcmStatus;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }

    else
    {

        HWREG(lcmBase + SDL_LCM_STATUS_CLEAR) = clearStatus;
        lcmStatus = HWREG(lcmBase + SDL_LCM_STATUS) & clearStatus;

        if(lcmStatus == 0U)
        {
            status = SDL_PASS;
        }
    }

    return status;

}

/********************************************************************************
 *
 * SDL_LCM_lockRegister(uint32_t lcmBase, uint32_t lcmRegs)
 *
 *******************************************************************************/

int32_t SDL_LCM_lockRegister(uint32_t lcmBase, uint32_t lcmRegs)
{
    int32_t status = SDL_EFAIL;
    uint32_t lcmStatus;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }

    else
    {

        HWREG(lcmBase + SDL_LCM_LOCK) |= lcmRegs;
        lcmStatus = HWREG(lcmBase + SDL_LCM_LOCK) & lcmRegs;

        if(lcmStatus == lcmRegs)
        {
            status = SDL_PASS;
        }
    }

    return status;
}

/********************************************************************************
 *
 * SDL_LCM_unlockRegister(uint32_t lcmBase, uint32_t lcmRegs)
 *
 *******************************************************************************/

int32_t SDL_LCM_unlockRegister(uint32_t lcmBase, uint32_t lcmRegs)
{
    int32_t status = SDL_EFAIL;
    uint32_t lcmStatus;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }

    else
    {

        HWREG(lcmBase + SDL_LCM_LOCK) &= ~lcmRegs;
        lcmStatus = HWREG(lcmBase + SDL_LCM_LOCK) & lcmRegs;

        if(lcmStatus == 0U)
        {
            status = SDL_PASS;
        }
    }

    return status;
}

/********************************************************************************
 *
 * SDL_LCM_commitRegister(uint32_t lcmBase, uint32_t lcmRegs)
 *
 *******************************************************************************/

int32_t SDL_LCM_commitRegister(uint32_t lcmBase, uint32_t lcmRegs)
{
    int32_t status = SDL_EFAIL;
    uint32_t lcmStatus;

    if((lcmBase != SDL_LCM_CPU_BASE) && (lcmBase != SDL_LCM_DMA_BASE))
    {
        status = SDL_EBADARGS;
    }

    else
    {

        HWREG(lcmBase + SDL_LCM_COMMIT) |= lcmRegs;
        lcmStatus = HWREG(lcmBase + SDL_LCM_COMMIT) & lcmRegs;

        if(lcmStatus == lcmRegs)
        {
            status = SDL_PASS;
        }
    }

    return status;
}

/*
 * End of File
 */