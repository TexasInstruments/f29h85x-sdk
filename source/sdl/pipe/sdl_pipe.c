/*
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

#include <sdl_esm.h>
#include "sdl_pipe.h"
#include "sdlr_pipe.h"
#include <include/hw_types.h>
#include <include/sdlr_sysctl.h>

#define SDL_PIPE_ERRAGGR_CPU_OFFSET                                            \
    (SDL_ERR_AGGR_CPU2_INT_HIGHPRIO_ERRADDR - SDL_ERR_AGGR_CPU1_INT_HIGHPRIO_ERRADDR)

static volatile uint32_t SDL_PIPE_isrFlag = SDL_PIPE_NO_INTERRUPT;

void SDL_PIPE_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg)
{
    uint32_t errVal;
    uint32_t errAggrBase = (uint32_t)callbackArg;
    uint8_t cpuIDOffset = (uint8_t)((HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUID) - 1U) *
                          SDL_PIPE_ERRAGGR_CPU_OFFSET);

    /*
     * Handle errors coming from PIPE.
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_INT + cpuIDOffset), &errVal);
    if(((errVal & SDL_ERR_AGGR_INT_TYPE_PIPE_REGPAR_DIAG_MASK) == SDL_ERR_AGGR_INT_TYPE_PIPE_REGPAR_DIAG_MASK))
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_INT + cpuIDOffset), errVal);
    }

    /* Setting the ISR flag */
    SDL_PIPE_isrFlag = SDL_PIPE_INTERRUPT;
}

int32_t SDL_PIPE_checkRegisterParity(uint32_t errAggrBase, uint32_t data, uint8_t parity)
{
    int32_t status = SDL_EFAIL;
    volatile uint32_t errFlagTimeout = 120U;

    if((errAggrBase & SDL_BASE_ADDR_MASK) != SDL_ERRORAGGREGATOR_BASE_FRAME(0U))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        /* Sets the self-test callback function */
        SDL_ESM_setSelfTestCallback(&SDL_PIPE_handleESMIntr, (void *)errAggrBase);
        /* Set the self-test status to ACTIVE*/
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        /* Setting the ISR flag */
        SDL_PIPE_isrFlag = SDL_PIPE_NO_INTERRUPT;

        /* Write parity data */
        HW_WR_REG32((SDL_PIPE_BASE + SDL_PIPE_REG_PARITY_DIAG_DATA), data);

        /* Inject error */
        HW_WR_FIELD32((SDL_PIPE_BASE + SDL_PIPE_REG_PARITY_DIAG_PARITY),
                      SDL_PIPE_REG_PARITY_DIAG_DATA, parity);

        /* Enable one-shot parity check */
        HW_WR_REG32((SDL_PIPE_BASE + SDL_PIPE_REG_PARITY_CHECK), SDL_PIPE_PARITY_CHECK_KEY);

        /* Start parity check */
        HW_WR_REG32((SDL_PIPE_BASE + SDL_PIPE_REG_PARITY_DIAG_ASSERT),
                    SDL_PIPE_PARITY_ASSERT_KEY);

        /*
        * Wait for ISR flags to be set by ESM and clear the error flags
        *
        */

        while((SDL_PIPE_isrFlag == SDL_PIPE_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout--;
        }

        /* Clear the self-test callback function */
        SDL_ESM_clearSelfTestCallback();
        /* Set the self-test status to NONE*/
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        if((errFlagTimeout != 0U))
        {
            status = SDL_PASS;
        }

        else
        {
            status = SDL_EFAIL;
        }
    }

    return (status);

}