/* ###########################################################################
 *
 * FILE:  sdl_sic.c
 *
 * TITLE: Diagnostic Library SIC software module source
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

#include "sdl_sic.h"
#include "sdlr_sic.h"

#define SDL_SIC_DELAY __asm(" NOP #5")
#define SDL_SIC_ERRAGGR_CPU_OFFSET                                            \
    (SDL_ERR_AGGR_CPU2_PR_HIGHPRIO_ERRADDR - SDL_ERR_AGGR_CPU1_PR_HIGHPRIO_ERRADDR)

static volatile uint32_t SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
static uint32_t SDL_SIC_errType;

void SDL_SIC_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg)
{
    uint32_t errVal;
    uint32_t errAggrBase = (uint32_t)callbackArg;
    uint8_t cpuIDOffset = (uint8_t)((HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUID) - 1U) *
                          SDL_SIC_ERRAGGR_CPU_OFFSET);

    /*
    * Check if the error was triggered by RTDMA1(DR) emualte fault.
    * If so, clear the error aggregator status and the corresponding ESM interrupt statuses.
    */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, SDL_ERR_AGGR_SRC_RTDMA1_DR, &errVal);
    if((errVal & SDL_SIC_errType) == SDL_SIC_errType)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, SDL_ERR_AGGR_SRC_RTDMA1_DR, errVal);
    }

    /*
     * Similarly, handle error from RTDMA2(DR).
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, SDL_ERR_AGGR_SRC_RTDMA2_DR, &errVal);
    if((errVal & SDL_SIC_errType) == SDL_SIC_errType)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, SDL_ERR_AGGR_SRC_RTDMA2_DR, errVal);
    }

    /*
     * Similarly, handle error from RTDMA1(DW).
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, SDL_ERR_AGGR_SRC_RTDMA1_DW, &errVal);
    if((errVal & SDL_SIC_errType) == SDL_SIC_errType)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, SDL_ERR_AGGR_SRC_RTDMA1_DW, errVal);
    }

    /*
     * Similarly, handle error from RTDMA2(DW).
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, SDL_ERR_AGGR_SRC_RTDMA2_DW, &errVal);
    if((errVal & SDL_SIC_errType) == SDL_SIC_errType)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, SDL_ERR_AGGR_SRC_RTDMA2_DW, errVal);
    }

    /*
     * Handle errors coming from CPU DR1 emulate fault.
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DR1 + cpuIDOffset), &errVal);
    if((errVal & SDL_SIC_errType) == SDL_SIC_errType)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DR1 + cpuIDOffset), errVal);
    }

    /*
     * Handle errors coming from CPU DR2 emulate fault.
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DR2 + cpuIDOffset), &errVal);
    if((errVal & SDL_SIC_errType) == SDL_SIC_errType)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DR2 + cpuIDOffset), errVal);
    }

    /*
     * Handle errors coming from CPU DW emulate fault.
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DW + cpuIDOffset), &errVal);
    if((errVal & SDL_SIC_errType) == SDL_SIC_errType)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DW + cpuIDOffset), errVal);
    }

    /*
     * Handle errors coming from CPU PR emulate fault.
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_PR + cpuIDOffset), &errVal);
    if((errVal & SDL_SIC_errType) == SDL_SIC_errType)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_PR + cpuIDOffset), errVal);
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG) = SDL_SIC_FLTDIS;
    }

    /*
     * Handle errors coming from PIPE emulate fault.
     */
    (void)SDL_ERR_AGGR_getErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_INT + cpuIDOffset), &errVal);
    if((errVal & SDL_ERR_AGGR_INT_TYPE_VEC_UNCERR_MASK) == SDL_ERR_AGGR_INT_TYPE_VEC_UNCERR_MASK)
    {
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_INT + cpuIDOffset), errVal);
    }

    /* Setting the ISR flag */
    SDL_SIC_isrFlag = SDL_SIC_INTERRUPT;
}

SDL_MEMSS_RAM SDL_SIC_getRAMBlock(uint32_t memAddr)
{

    SDL_MEMSS_RAM ramLocation;

    if((memAddr >=SDL_LDA7_RAM_BASE) && (memAddr < SDL_LDA6_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LDA7;
    }

    else if((memAddr >=SDL_LDA6_RAM_BASE) && (memAddr < SDL_LDA5_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LDA6;
    }

    else if((memAddr >=SDL_LDA5_RAM_BASE) && (memAddr < SDL_LDA4_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LDA5;
    }

    else if((memAddr >=SDL_LDA4_RAM_BASE) && (memAddr < SDL_LDA3_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LDA4;
    }

    else if((memAddr >=SDL_LDA3_RAM_BASE) && (memAddr < SDL_LDA2_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LDA3;
    }

    else if((memAddr >=SDL_LDA2_RAM_BASE) && (memAddr < SDL_LDA1_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LDA2;
    }

    else if((memAddr >=SDL_LDA1_RAM_BASE) && (memAddr < SDL_LDA0_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LDA1;
    }

    else if((memAddr >=SDL_LDA0_RAM_BASE) && (memAddr < SDL_LPA0_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LDA0;
    }

    else if((memAddr >=SDL_LPA0_RAM_BASE) && (memAddr < SDL_LPA1_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LPA0;
    }

    else if((memAddr >=SDL_LPA1_RAM_BASE) && (memAddr < SDL_CPA0_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_LPA1;
    }

    else if((memAddr >=SDL_CPA0_RAM_BASE) && (memAddr < SDL_CPA1_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CPA0;
    }

    else if((memAddr >=SDL_CPA1_RAM_BASE) && (memAddr < SDL_CDA0_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CPA1;
    }

    else if((memAddr >=SDL_CDA0_RAM_BASE) && (memAddr < SDL_CDA1_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA0;
    }

    else if((memAddr >=SDL_CDA1_RAM_BASE) && (memAddr < SDL_CDA2_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA1;
    }

    else if((memAddr >=SDL_CDA2_RAM_BASE) && (memAddr < SDL_CDA3_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA2;
    }

    else if((memAddr >=SDL_CDA3_RAM_BASE) && (memAddr < SDL_CDA4_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA3;
    }

    else if((memAddr >=SDL_CDA4_RAM_BASE) && (memAddr < SDL_CDA5_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA4;
    }

    else if((memAddr >=SDL_CDA5_RAM_BASE) && (memAddr < SDL_CDA6_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA5;
    }

    else if((memAddr >=SDL_CDA6_RAM_BASE) && (memAddr < SDL_CDA7_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA6;
    }

    else if((memAddr >=SDL_CDA7_RAM_BASE) && (memAddr < SDL_CDA8_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA7;
    }

    else if((memAddr >=SDL_CDA8_RAM_BASE) && (memAddr < SDL_CDA9_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA8;
    }

    else if((memAddr >=SDL_CDA9_RAM_BASE) && (memAddr < SDL_CDA10_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA9;
    }

    else if((memAddr >=SDL_CDA10_RAM_BASE) && (memAddr < SDL_CDA11_RAM_BASE))
    {
        ramLocation = SDL_MEMSS_RAM_CDA10;
    }

    else if((memAddr >=SDL_CDA11_RAM_BASE) && (memAddr <= SDL_CDA11_RAM_END))
    {
        ramLocation = SDL_MEMSS_RAM_CDA11;
    }

    else 
    {
        ramLocation = SDL_MEMSS_RAM_INVALID;
    }

    return ramLocation;
} 

__attribute__((section(".text.link2.SDL_RTDMA_init")))
static void SDL_RTDMA_init(uint32_t dmaBase, uint32_t dmaChBase,
                           const void *destAddr, const void *srcAddr)
{
    HWREGB(dmaBase + SDL_RTDMA_O_DMACTRL) = 0x1U;
    SDL_SIC_DELAY;

    /* Set up SOURCE address */
    HWREG(dmaChBase + SDL_RTDMA_O_SRC_BEG_ADDR_SHADOW) = (uint32_t)srcAddr;
    HWREG(dmaChBase + SDL_RTDMA_O_SRC_ADDR_SHADOW)     = (uint32_t)srcAddr;

    /* Set up DESTINATION address */
    HWREG(dmaChBase + SDL_RTDMA_O_DST_BEG_ADDR_SHADOW) = (uint32_t)destAddr;
    HWREG(dmaChBase + SDL_RTDMA_O_DST_ADDR_SHADOW)     = (uint32_t)destAddr;

    /* Set up BURST registers */
    HWREGH(dmaChBase + SDL_RTDMA_O_BURST_SIZE)     = 0;
    HWREGH(dmaChBase + SDL_RTDMA_O_SRC_BURST_STEP) = 0;
    HWREGH(dmaChBase + SDL_RTDMA_O_DST_BURST_STEP) = 0;

    /*Set up TRANSFER registers */
    HWREGH(dmaChBase + SDL_RTDMA_O_TRANSFER_SIZE)     = 0;
    HWREGH(dmaChBase + SDL_RTDMA_O_SRC_TRANSFER_STEP) = 0;
    HWREGH(dmaChBase + SDL_RTDMA_O_DST_TRANSFER_STEP) = 0;

    /*Set up WRAP registers*/
    HWREGH(dmaChBase + SDL_RTDMA_O_SRC_WRAP_SIZE) = (uint16_t)(65535U - 1U);
    HWREGH(dmaChBase + SDL_RTDMA_O_SRC_WRAP_STEP) = 0;
    HWREGH(dmaChBase + SDL_RTDMA_O_DST_WRAP_SIZE) = (uint16_t)(65535U - 1U);
    HWREGH(dmaChBase + SDL_RTDMA_O_DST_WRAP_STEP) = 0;

    /*Configure the Burst mode operation*/
    HWREGB(dmaChBase + SDL_RTDMA_O_BURST_INTF_CTRL) = 0;

    /*Set the peripheral interrupt trigger enable bit*/
    HWREGH(dmaChBase + SDL_RTDMA_O_MODE) |= SDL_SIC_RTDMA_PERINTE;

    /*Set the halt bit*/
    HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = SDL_SIC_RTDMA_HALT;
}

int32_t SDL_SIC_enableSafety(void)
{
    int32_t status = SDL_EFAIL;
    uint32_t sicStatus;

    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_SICCONFIG) |= SDL_SIC_ENABLE;
    sicStatus = HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_SICCONFIG) & SDL_SIC_ENABLE;

    if(sicStatus == SDL_SIC_ENABLE)
    {
        status = SDL_PASS;
    }

    return status;
}

int32_t SDL_SIC_disableSafety(void)
{
    int32_t status = SDL_EFAIL;
    uint32_t sicStatus;

    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_SICCONFIG) &= ~(uint32_t)SDL_SIC_ENABLE;
    sicStatus = HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_SICCONFIG) & SDL_SIC_ENABLE;

    if(sicStatus == 0x0U)
    {
        status = SDL_PASS;
    }

    return status;
}

int32_t SDL_SIC_setTimeout(uint16_t timeOut)
{
    int32_t status = SDL_EFAIL;
    uint32_t sicStatus;
    uint32_t extendedTimeout;

    extendedTimeout = ((uint32_t)timeOut) << SDL_SYSCTL_SICCONFIG_TIMEOUT_S;
    HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_SICCONFIG) = (extendedTimeout | (HWREG(SDL_DEVCFG_BASE
                                                    + SDL_SYSCTL_O_SICCONFIG) & 0x0000FFFFU));

    sicStatus = HWREG(SDL_DEVCFG_BASE + SDL_SYSCTL_O_SICCONFIG) & SDL_SYSCTL_SICCONFIG_TIMEOUT_M;

    if(sicStatus == extendedTimeout)
    {
        status = SDL_PASS;
    }

    return(status);
}

int32_t SDL_SIC_PIPE_emulateFault(uint32_t errAggrBase, uint32_t intNum)
{
    int32_t status = SDL_EFAIL, retVal;
    volatile uint32_t tempRead;
    uint32_t saveVector, loopCounter;
    uint32_t bitIndex, startValue;
    uint32_t errCount = 0U, errVal;
    volatile uint32_t errFlagTimeout = 120U;
    SDL_ERR_AGGR_ErrSource errSrcType = ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_INT +
                                         ((HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUID) - 1U) *
                                          SDL_SIC_ERRAGGR_CPU_OFFSET));

    SDL_ESM_setSelfTestCallback(&SDL_SIC_handleESMIntr, (void *)errAggrBase);

    if((intNum > 255U) || ((errAggrBase & SDL_BASE_ADDR_MASK) != SDL_ERRORAGGREGATOR_BASE_FRAME(0U)))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        /* Back up interrupt vector */
        saveVector = HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum));

        /*
         * looping to inject errors for both the cases: when the vector is in reset state(all zeros)
         * and when the vector is in set state(all ones).
         */
        for(loopCounter = 0U; loopCounter < 2U; loopCounter++)
        {

            if(loopCounter == 0U)
            {
                startValue = SDL_SIC_RESET_VECTOR;
            }
            else
            {
                startValue = SDL_SIC_SET_VECTOR;
            }

            HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum)) = startValue;

            /* looping for single bit error*/
            for(bitIndex = 0U; bitIndex < 32U; bitIndex++)
            {
                /* Enable diag writes to memory and inject a single bit error. */
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_MEM_ECC_DIAG) = SDL_PIPE_MEM_ECC_DIAG_MEM_SIC_DIAG_EN |
                                                                 SDL_SIC_WRITE_KEY;
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum)) ^= (((uint32_t)1U) << bitIndex);
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_MEM_ECC_DIAG) = SDL_SIC_WRITE_KEY;   /* MEM_SIC_DIAG_EN = 0 */
                tempRead = HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum));

                retVal = SDL_ERR_AGGR_getErrorType(errAggrBase, errSrcType, &errVal);
                if((errVal & SDL_ERR_AGGR_INT_TYPE_VEC_CERR_MASK) == 0U)
                {
                    errCount++;
                }

                retVal = SDL_ERR_AGGR_clearErrorType(errAggrBase, errSrcType,
                                                     SDL_ERR_AGGR_INT_TYPE_VEC_CERR_MASK);

                SDL_SIC_DELAY;

                /* Resetting/Setting the vector for the next iteration */
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_MEM_ECC_DIAG) = SDL_PIPE_MEM_ECC_DIAG_MEM_SIC_DIAG_EN |
                                                                 SDL_SIC_WRITE_KEY;
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum)) = startValue;
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_MEM_ECC_DIAG) = SDL_SIC_WRITE_KEY;   /* MEM_SIC_DIAG_EN = 0 */

            }

            /* looping for 2 bits error*/
            for(bitIndex = 0U; bitIndex < 31U; bitIndex += 2U)
            {
                SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
                SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

                /* Enable diag writes to memory and inject a two bits error. */
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_MEM_ECC_DIAG) = SDL_PIPE_MEM_ECC_DIAG_MEM_SIC_DIAG_EN |
                                                                 SDL_SIC_WRITE_KEY;
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum)) ^= ((((uint32_t)3U) << bitIndex));
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_MEM_ECC_DIAG) = SDL_SIC_WRITE_KEY;   /* MEM_SIC_DIAG_EN = 0 */

                SDL_SIC_DELAY;

                tempRead = HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum));

                while((errFlagTimeout != 0U) && (SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT))
                {
                    errFlagTimeout -= 1U;
                }

                SDL_SIC_DELAY;

                /* Resetting/Setting the vector for the next iteration */
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_MEM_ECC_DIAG) = SDL_PIPE_MEM_ECC_DIAG_MEM_SIC_DIAG_EN |
                                                                 SDL_SIC_WRITE_KEY;
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum)) = startValue;
                HWREG(SDL_PIPE_BASE + SDL_PIPE_O_MEM_ECC_DIAG) = SDL_SIC_WRITE_KEY;   /* MEM_SIC_DIAG_EN = 0 */
            }
        }

        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        /* Restoring interrupt vector */
        HWREG(SDL_PIPE_BASE + SDL_PIPE_O_INT_VECT_ADDR(intNum)) = saveVector;

        if((errFlagTimeout != 0U) && (errCount == 0U) && (retVal == SDL_PASS))
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

int32_t SDL_SIC_CPU_DR1_emulateFault(uint32_t errAggrBase, uint32_t *memAddr)
{
    int32_t status,retVal;
    uint32_t saveVector, errVal;
    volatile uint32_t tempRead, errFlagTimeout = 5U;
    SDL_ERR_AGGR_ErrSource errSrcType = ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DR1 +
                                         ((HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUID) - 1U) *
                                          SDL_SIC_ERRAGGR_CPU_OFFSET));

    if((memAddr == NULL) || ((errAggrBase & SDL_BASE_ADDR_MASK) != SDL_ERRORAGGREGATOR_BASE_FRAME(0U)))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        SDL_ESM_setSelfTestCallback(&SDL_SIC_handleESMIntr, (void *)errAggrBase);

        /*
         * DR1 control group, ACK error
         */
        SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
        SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_ACK_MASK;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DR1CTL;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;    /* FLTEMU enable */
        SDL_SIC_DELAY;

        tempRead = *memAddr;

        while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout -= 1U;
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * DR1 control group, READY timeout error
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_TIMEOUT_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DR1CTL;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_READY_ERROR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;     /* FLTEMU enable */
            SDL_SIC_DELAY;

            tempRead = *memAddr;

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * UNC error on DR1 data group, data bit 0/1
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_UNCERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DR1DATA;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU_UNC; /* FLTEMU enable */
            SDL_SIC_DELAY;

            tempRead = *memAddr;

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * CORR error on DR1 data group, data bit 0
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_CERR_MASK;

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL)  = SDL_SIC_CPU_DR1DATA;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)     = SDL_SIC_CLEAR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)       = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)     = SDL_SIC_FLTEMU;    /* FLTEMU enable */
            SDL_SIC_DELAY;

            tempRead = *memAddr;


            do
            {
                retVal = SDL_ERR_AGGR_getErrorType(errAggrBase, errSrcType, &errVal);
                errFlagTimeout -= 1U;

            } while(((errVal & SDL_ERR_AGGR_TYPE_CERR_MASK) == 0U) && (errFlagTimeout != 0U));

            retVal = SDL_ERR_AGGR_clearErrorType(errAggrBase, errSrcType,
                                             SDL_ERR_AGGR_TYPE_CERR_MASK);
        }

        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        /*disabling the fault emulation mode*/
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG) = SDL_SIC_FLTDIS;

        if((errFlagTimeout != 0U) && (retVal == SDL_PASS))
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

int32_t SDL_SIC_CPU_DR2_emulateFault(uint32_t errAggrBase, uint32_t *memAddr)
{

    int32_t status,retVal;
    uint32_t saveVector, errVal;
    volatile uint32_t errFlagTimeout = 5U;
    SDL_ERR_AGGR_ErrSource errSrcType = ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DR2 +
                                         ((HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUID) - 1U) *
                                          SDL_SIC_ERRAGGR_CPU_OFFSET));

    if((memAddr == NULL) || ((errAggrBase & SDL_BASE_ADDR_MASK) != SDL_ERRORAGGREGATOR_BASE_FRAME(0U)))
    {
        status = SDL_EBADARGS;
    }

    else
    {
        SDL_ESM_setSelfTestCallback(&SDL_SIC_handleESMIntr, (void *)errAggrBase);

        /*
         * DR2 control group, ACK error
         */
        SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
        SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_ACK_MASK;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DR2CTL;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)(memAddr);
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;    /* FLTEMU enable */

        SDL_SIC_dr2Read((uint32_t)memAddr);

        while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout -= 1U;
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * DR2 control group, READY timeout error
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_TIMEOUT_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DR2CTL;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_READY_ERROR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;     /* FLTEMU enable */

            SDL_SIC_dr2Read((uint32_t)memAddr);

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * UNC error on DR2 data group, data bit 0/1
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_UNCERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DR2DATA;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU_UNC; /* FLTEMU enable */

            SDL_SIC_dr2Read((uint32_t)memAddr);

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * CORR error on DR2 data group, data bit 0
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_CERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL)  = SDL_SIC_CPU_DR2DATA;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)     = SDL_SIC_CLEAR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)       = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)     = SDL_SIC_FLTEMU;    /* FLTEMU enable */

            SDL_SIC_dr2Read((uint32_t)memAddr);

            do
            {
                retVal = SDL_ERR_AGGR_getErrorType(errAggrBase, errSrcType, &errVal);
                errFlagTimeout -= 1U;

            } while(((errVal & SDL_ERR_AGGR_TYPE_CERR_MASK) == 0U) && (errFlagTimeout != 0U));

            retVal = SDL_ERR_AGGR_clearErrorType(errAggrBase, errSrcType,
                                             SDL_ERR_AGGR_TYPE_CERR_MASK);
        }

        /*disabling the fault emulation mode*/
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG) = SDL_SIC_FLTDIS;

        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        if((errFlagTimeout != 0U) && (retVal == SDL_PASS))
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

int32_t SDL_SIC_CPU_DW_emulateFault(uint32_t errAggrBase, uint32_t *memAddr)
{
    int32_t status,retVal;
    uint32_t saveVector, errVal;
    volatile uint32_t tempWrite = 0x0000FFFFU, errFlagTimeout = 10U;
    SDL_ERR_AGGR_ErrSource errSrcType = ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DW +
                                         ((HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUID) - 1U) *
                                          SDL_SIC_ERRAGGR_CPU_OFFSET));

    if((memAddr == NULL) || ((errAggrBase & SDL_BASE_ADDR_MASK) != SDL_ERRORAGGREGATOR_BASE_FRAME(0U)))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        /* Back up data */
        saveVector = *memAddr;

        SDL_ESM_setSelfTestCallback(&SDL_SIC_handleESMIntr, (void *)errAggrBase);

        /*
         * DW control group, ACK error
         */
        SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
        SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_ACK_MASK;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DWCTL;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;    /* FLTEMU enable */
        SDL_SIC_DELAY;

        *memAddr = tempWrite;

        while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout -= 1U;
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * DW control group, READY timeout error
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_TIMEOUT_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DWCTL;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_READY_ERROR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;     /* FLTEMU enable */
            SDL_SIC_DELAY;

            *memAddr = tempWrite;

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * UNC error on DW data group, data bit 0/1
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_UNCERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_DWDATA;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU; /* FLTEMU enable */
            SDL_SIC_DELAY;

            *memAddr = tempWrite;

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * CORR error on DW data group, data bit 0
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_CERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL)  = SDL_SIC_CPU_DWDATA;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)     = SDL_SIC_CLEAR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)       = (uint32_t)memAddr + (uint32_t)2U;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)     = SDL_SIC_FLTEMU;    /* FLTEMU enable */
            SDL_SIC_DELAY;

            *((uint16_t *)memAddr) = (uint16_t)tempWrite;

            do
            {
                retVal = SDL_ERR_AGGR_getErrorType(errAggrBase, errSrcType, &errVal);
                errFlagTimeout -= 1U;

            } while(((errVal & SDL_ERR_AGGR_TYPE_CERR_MASK) == 0U) && (errFlagTimeout != 0U));

            retVal = SDL_ERR_AGGR_clearErrorType(errAggrBase, errSrcType, SDL_ERR_AGGR_TYPE_CERR_MASK);
        }

        /* Restoring data */
        *memAddr = saveVector;

        /*disabling the fault emulation mode*/
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG) = SDL_SIC_FLTDIS;

        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        if((errFlagTimeout != 0U) && (retVal == SDL_PASS))
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

int32_t SDL_SIC_CPU_PR_emulateFault(uint32_t errAggrBase, uint32_t *memAddr)
{

    int32_t status,retVal;
    uint32_t saveVector, errVal;
    volatile uint32_t errFlagTimeout = 5U;
    SDL_ERR_AGGR_ErrSource errSrcType = ((uint32_t)SDL_ERR_AGGR_SRC_CPU1_PR +
                                         ((HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUID) - 1U) *
                                          SDL_SIC_ERRAGGR_CPU_OFFSET));

    if((memAddr == NULL) || ((errAggrBase & SDL_BASE_ADDR_MASK) != SDL_ERRORAGGREGATOR_BASE_FRAME(0U)))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        /* Back up data */
        saveVector = *memAddr;

        SDL_ESM_setSelfTestCallback(&SDL_SIC_handleESMIntr, (void *)errAggrBase);

        /*
         * PR control group, ACK error
         */
        SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
        SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_ACK_MASK;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_PRCTL;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;    /* FLTEMU enable */

        SDL_SIC_exec((uint32_t)memAddr);

        while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout -= 1U;
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * UNC error on PR data group, data bit 0/1
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_UNCERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_CPU_PRDATA;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU_UNC; /* FLTEMU enable */

            SDL_SIC_exec((uint32_t)memAddr);

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * CORR error on PR data group, data bit 0
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_CERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ACCGRPSEL)  = SDL_SIC_CPU_PRDATA;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_BITSEL)     = SDL_SIC_CLEAR;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_ADDR)       = (uint32_t)memAddr;
            HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG)     = SDL_SIC_FLTEMU;    /* FLTEMU enable */

            SDL_SIC_exec((uint32_t)memAddr);

            do
            {
                retVal = SDL_ERR_AGGR_getErrorType(errAggrBase, errSrcType, &errVal);
                errFlagTimeout -= 1U;

            } while(((errVal & SDL_ERR_AGGR_TYPE_CERR_MASK) == 0U) && (errFlagTimeout != 0U));

            retVal = SDL_ERR_AGGR_clearErrorType(errAggrBase, errSrcType, SDL_ERR_AGGR_TYPE_CERR_MASK);
        }

        /* Restoring data */
        *memAddr = saveVector;

        /*disabling the fault emulation mode*/
        HWREG(SDL_C29CPUDIAG_BASE + SDL_SIC_FLTEMU_CONFIG) = SDL_SIC_FLTDIS;

        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        if((errFlagTimeout != 0U) && (retVal == SDL_PASS))
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

int32_t SDL_SIC_RTDMA_DR_emulateFault(uint32_t errAggrBase, uint32_t dmaBase, uint32_t dmaChBase,
                                      const void *destAddr, const void *srcAddr)
{
    int32_t status,retVal;
    volatile uint32_t errFlagTimeout = 25U;
    uint32_t sicDiagBase, errVal;
    int32_t result;
    SDL_ERR_AGGR_ErrSource sicErrType;

    if(((errAggrBase & SDL_BASE_ADDR_MASK) != SDL_ERRORAGGREGATOR_BASE_FRAME(0U)) || (destAddr == NULL) || (srcAddr ==NULL))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        /*Initialising RTDMA*/
        SDL_RTDMA_init(dmaBase, dmaChBase, destAddr, srcAddr);

        /* Getting other base addresses */
        if(dmaBase == SDL_RTDMA1_BASE)
        {
            sicDiagBase = SDL_RTDMA1_DIAG_BASE;
            sicErrType  = SDL_ERR_AGGR_SRC_RTDMA1_DR;
        }
        else
        {
            sicDiagBase = SDL_RTDMA2_DIAG_BASE;
            sicErrType  = SDL_ERR_AGGR_SRC_RTDMA2_DR;
        }

        SDL_ESM_setSelfTestCallback(&SDL_SIC_handleESMIntr, (void *)errAggrBase);

        /*
         * DR control group, ACK error
         */
        SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
        SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_ACK_MASK;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        HWREG(sicDiagBase + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_RTDMA_DRCTL;
        HWREG(sicDiagBase + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
        HWREG(sicDiagBase + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)(srcAddr);
        HWREG(sicDiagBase + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;    /* FLTEMU enable */

        /* Start DMA channel */
        HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x1U;
        HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x8U;

        while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout -= 1U;
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * DR1 control group, READY timeout error
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_TIMEOUT_MASK | SDL_ERR_AGGR_TYPE_ACC_ACK_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_RTDMA_DRCTL;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_READY_ERROR;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)(srcAddr);
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;     /* FLTEMU enable */

            /* Start DMA channel */
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x1U;
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x8U;

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * UNC error on DR data group, data bit 0/1
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_UNCERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_RTDMA_DRDATA;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)(srcAddr);
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU_UNC; /* FLTEMU enable */

            /* Start DMA channel */
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x1U;
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x8U;

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * CORR error on DR data group, data bit 0
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_CERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_RTDMA_DRDATA;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)(srcAddr);
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;    /* FLTEMU enable */

            /* Start DMA channel */
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x1U;
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x8U;

            do
            {
                retVal = SDL_ERR_AGGR_getErrorType(errAggrBase, sicErrType, &errVal);
                errFlagTimeout -= 1U;

            } while(((errVal & SDL_ERR_AGGR_TYPE_CERR_MASK) == 0U) && (errFlagTimeout != 0U));

            retVal = SDL_ERR_AGGR_clearErrorType(errAggrBase, sicErrType, SDL_ERR_AGGR_TYPE_CERR_MASK);
        }

        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        if((errFlagTimeout != 0U) && (retVal == SDL_PASS))
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

int32_t SDL_SIC_RTDMA_DW_emulateFault(uint32_t errAggrBase, uint32_t dmaBase, uint32_t dmaChBase,
                                      const void *destAddr, const void *srcAddr)
{
    int32_t status, retVal;
    volatile uint32_t errFlagTimeout = 25U;
    volatile SDL_MEMSS_RAM ramLocation;
    uint32_t sicDiagBase, errVal;
    int32_t result;
    SDL_ERR_AGGR_ErrSource sicErrType;

    if(((errAggrBase & SDL_BASE_ADDR_MASK) != SDL_ERRORAGGREGATOR_BASE_FRAME(0U)) || (destAddr == NULL) || (srcAddr == NULL))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        /*Initialising RTDMA*/
        SDL_RTDMA_init(dmaBase, dmaChBase, destAddr, srcAddr);

        /* Getting other base addresses */
        if(dmaBase == SDL_RTDMA1_BASE)
        {
            sicDiagBase = SDL_RTDMA1_DIAG_BASE;
            sicErrType  = SDL_ERR_AGGR_SRC_RTDMA1_DW;
        }
        else
        {
            sicDiagBase = SDL_RTDMA2_DIAG_BASE;
            sicErrType  = SDL_ERR_AGGR_SRC_RTDMA2_DW;
        }

        SDL_ESM_setSelfTestCallback(&SDL_SIC_handleESMIntr, (void *)errAggrBase);

        /*
         * DW control group, ACK error
         */
        SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
        SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_ACK_MASK;
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        HWREG(sicDiagBase + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_RTDMA_DWCTL;
        HWREG(sicDiagBase + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
        HWREG(sicDiagBase + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)(destAddr);
        HWREG(sicDiagBase + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;    /* FLTEMU enable */

        /* Start DMA channel */
        HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x1U;
        HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x8U;

        while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout -= 1U;
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * DW control group, READY timeout error
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_ACC_TIMEOUT_MASK | SDL_ERR_AGGR_TYPE_ACC_ACK_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_RTDMA_DWCTL;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_READY_ERROR;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)(destAddr);
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU;     /* FLTEMU enable */

            /* Start DMA channel */
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x1U;
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x8U;

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * UNC error on DW data group, data bit 0/1
             */
            SDL_SIC_isrFlag = SDL_SIC_NO_INTERRUPT;
            SDL_SIC_errType = SDL_ERR_AGGR_TYPE_UNCERR_MASK;
            SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ACCGRPSEL) = SDL_SIC_RTDMA_DWDATA;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_BITSEL)    = SDL_SIC_CLEAR;
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_ADDR)      = (uint32_t)(destAddr);
            HWREG(sicDiagBase + SDL_SIC_FLTEMU_CONFIG)    = SDL_SIC_FLTEMU; /* FLTEMU enable */

            /* Start DMA channel */
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x1U;
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x8U;

            while((SDL_SIC_isrFlag == SDL_SIC_NO_INTERRUPT) && (errFlagTimeout != 0U))
            {
                errFlagTimeout -= 1U;
            }
        }

        if(errFlagTimeout != 0U)
        {

            /*
             * CORR error on DW data group, data bit 0
             */

            /* Get the Memory location of destination address*/
            ramLocation = SDL_SIC_getRAMBlock((uint32_t)destAddr);

            /*configure the memory in the test mode*/
            SDL_MEMSS_configTestMode(ramLocation, SDL_MEMSS_TESTMODE_DATA_ONLY);  /* MODE_dma1 1  data will be modified but not ecc */
            HWREGB((uint32_t)destAddr) = (HWREGB((uint32_t)destAddr)^0x1U);   /* flipping the dest bit. */
            SDL_MEMSS_configTestMode(ramLocation, SDL_MEMSS_TESTMODE_NORMAL);     /* MODE_dma1 1  data will be modified but not ecc */

            /*configuring the RTDMA for 16 bit write operation*/
            HWREG(dmaChBase + SDL_RTDMA_O_DST_BEG_ADDR_SHADOW) = ((uint32_t)(destAddr))+2U;
            HWREG(dmaChBase + SDL_RTDMA_O_DST_ADDR_SHADOW) = ((uint32_t)(destAddr))+2U;

            /* Start DMA channel */
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x1U;
            HWREGB(dmaChBase + SDL_RTDMA_O_CONTROL) = 0x8U;
            SDL_SIC_DELAY;

            do
            {
                retVal = SDL_ERR_AGGR_getErrorType(errAggrBase, sicErrType, &errVal);
                errFlagTimeout -= 1U;

            } while(((errVal & SDL_ERR_AGGR_TYPE_CERR_MASK) == 0U) && (errFlagTimeout != 0U));

            retVal = SDL_ERR_AGGR_clearErrorType(errAggrBase, sicErrType, SDL_ERR_AGGR_TYPE_CERR_MASK);
        }
        
        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        if((errFlagTimeout != 0U) && (retVal == SDL_PASS))
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