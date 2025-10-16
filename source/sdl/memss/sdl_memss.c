/* ###########################################################################
 *
 *  \file     sdl_memss.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of MEMSS.
 *            This also contains some related macros.
 *
 *
 *  Copyright (C) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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

#include "sdlr_memss.h"
#include "sdl_memss.h"
#include <stdint.h>

#include <sdl_esm.h>
#include <sdl_err_aggr.h>

#include <include/sdlr_sysctl.h>

#define SDL_MEMSS_ERRAGGR_CPU_OFFSET                                            \
    (SDL_ERR_AGGR_CPU2_PR_HIGHPRIO_ERRADDR - SDL_ERR_AGGR_CPU1_PR_HIGHPRIO_ERRADDR)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static volatile uint32_t SDL_MEMSS_isrFlag = SDL_MEMSS_NO_INTERRUPT;

void SDL_MEMSS_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg)
{
    uint32_t errAggrBase = (uint32_t)callbackArg;
    uint32_t cpuId = HWREG(SDL_CPUSYS_BASE + SDL_SYSCTL_O_CPUID);
    SDL_ERR_AGGR_ErrSource errSrcType =(SDL_ERR_AGGR_ErrSource)((uint32_t)SDL_ERR_AGGR_SRC_CPU1_DR1 +
                                       ((cpuId - 1U) * SDL_MEMSS_ERRAGGR_CPU_OFFSET));

    if(intSrc == SDL_ESM_EVENT_ErrorAggregator_CPU1_LPERR)
    {
        SDL_MEMSS_isrFlag = SDL_MEMSS_INTERRUPT;
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, errSrcType, SDL_ERR_AGGR_TYPE_CERR_MASK);
    }
    else if(intSrc == SDL_ESM_EVENT_CPU1_ERAD_NMI)
    {
        SDL_MEMSS_isrFlag = SDL_MEMSS_INTERRUPT;
        (void)SDL_ERR_AGGR_clearErrorType(errAggrBase, errSrcType, SDL_ERR_AGGR_TYPE_UNCERR_MASK);
    }
    else if (intSrc == SDL_ESM_EVENT_MEMSS_REG_PAR_ERR)
    {
        SDL_MEMSS_isrFlag = SDL_MEMSS_INTERRUPT;
    }
    else
    {
        /* Do nothing. Unexpected event type. */
    }
}

/* API for TestMode MEMSS module */
void SDL_MEMSS_configTestMode(SDL_MEMSS_RAM memory, SDL_MEMSS_TestMode mode)
{
   HW_WR_FIELD32((uint32_t)memory, SDL_MEMSS_MEM_CONFIG_TESTMODE, (uint32_t)mode);
}

/* Lock Mechanism for Control Registers */
/* API for memconfigLock Register the MEMSS module */
void SDL_MEMSS_lockConfig(SDL_MEMSS_RAM memory)
{
    HW_WR_FIELD32((uint32_t)memory + SDL_MEMSS_MEM_CONFIG_LOCK_OFFSET,
                  SDL_MEMSS_MEM_CONFIG_LOCK,
                  SDL_MEMSS_MEM_CONFIG_LOCK_ENABLE);
}

/* API for memconfigUnLock Register the MEMSS module */

void SDL_MEMSS_unlockConfig(SDL_MEMSS_RAM memory)
{
    HW_WR_FIELD32((uint32_t)memory + SDL_MEMSS_MEM_CONFIG_LOCK_OFFSET,
                  SDL_MEMSS_MEM_CONFIG_LOCK,
                  SDL_MEMSS_MEM_CONFIG_LOCK_DISABLE);
}

/* API for memcommitconfig Register the MEMSS module */
void SDL_MEMSS_commitConfig(SDL_MEMSS_RAM memory)
{
    HW_WR_FIELD32((uint32_t)memory + SDL_MEMSS_MEM_CONFIG_COMMIT_OFFSET,
                  SDL_MEMSS_MEM_CONFIG_COMMIT,
                  SDL_MEMSS_MEM_CONFIG_COMMIT_MEM_CONFIG_LOCK);
}

/* API for Peri Mem TestControl Register the MEMSS module */
void SDL_MEMSS_forceEtherCATParityError(void)
{
    HW_WR_FIELD32(SDL_MEMSSMISCI_BASE + SDL_MEMSS_PERI_MEM_TEST_CONTROL,
                  SDL_MEMSS_PERI_MEM_TEST_CONTROL_ETHERCAT_MEM_FORCE_ERROR,
                  SDL_MEMSS_PERI_MEM_TEST_CONTROL_ETHERCAT_MEM_FORCE_INTRODUCE_ERROR);
}

/* API for Peri MemLockControl Register the MEMSS module */
void SDL_MEMSS_lockPeriphMemTestRegister(void)
{
    HW_WR_FIELD32(SDL_MEMSSMISCI_BASE + SDL_MEMSS_PERI_MEM_TEST_LOCK,
                  SDL_MEMSS_PERI_MEM_TEST_LOCK,
                  SDL_MEMSS_PERI_MEM_TEST_LOCK_ALLOWED);
}

void SDL_MEMSS_unlockPeriphMemTestRegister(void)
{
    HW_WR_FIELD32(SDL_MEMSSMISCI_BASE + SDL_MEMSS_PERI_MEM_TEST_LOCK,
                  SDL_MEMSS_PERI_MEM_TEST_LOCK,
                  SDL_MEMSS_PERI_MEM_TEST_LOCK_BLOCKED);
}

/* API for Parity Test Register the MEMSS module */
/* Enable parity test mode */
void SDL_MEMSS_enableCheckRegisterParity(void)
{
     HW_WR_FIELD32(SDL_MEMSSMISCI_BASE + SDL_MEMSS_PARITY_TEST,
                  SDL_MEMSS_PARITY_TEST_TESTEN,
                  SDL_MEMSS_PARITY_TEST_ENABLE);
}

/* Disable parity test mode */
void SDL_MEMSS_disableCheckRegisterParity(void)
{
    HW_WR_FIELD32(SDL_MEMSSMISCI_BASE + SDL_MEMSS_PARITY_TEST,
                  SDL_MEMSS_PARITY_TEST_TESTEN,
                  SDL_MEMSS_PARITY_TEST_DISABLE);
}

/* API for Parity Test Register the MEMSS module */
/* Enable parity test mode */
int32_t SDL_MEMSS_checkRegisterParity(void)
{
    int32_t status = SDL_EFAIL;
    volatile uint32_t errFlagTimeout = SDL_MEMSS_PARITY_TIMEOUT;
    SDL_MEMSS_isrFlag = SDL_MEMSS_NO_INTERRUPT;

    SDL_ESM_setSelfTestCallback(&SDL_MEMSS_handleESMIntr, NULL);
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

    /* Enable parity test mode */
    SDL_MEMSS_enableCheckRegisterParity();

    SDL_MEMSS_configTestMode(SDL_MEMSS_RAM_CPA0, SDL_MEMSS_TESTMODE_DATA_ONLY);

    /* Wait for ISR flag set by ESM */
    while ((SDL_MEMSS_isrFlag == SDL_MEMSS_NO_INTERRUPT) && (errFlagTimeout != 0U))
    {
        errFlagTimeout -= 1U;
    }

    /* Disable parity test mode */
    SDL_MEMSS_disableCheckRegisterParity();

    SDL_ESM_clearSelfTestCallback();
    SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

    /* Evaluate timeout and set result */
    if (errFlagTimeout != 0U)
    {
        status = SDL_PASS;
    }
    else
    {
        status = SDL_EFAIL;
    }

    return status;
}

/* API for TestECCInjection Register the MEMSS module */
int32_t SDL_MEMSS_testECCInjection(uint32_t errAggrBase, SDL_MEMSS_RAM memory,
                                   uint32_t *testAddr, SDL_MEMSS_TestMode testMode,
                                   uint32_t xorMask)
{
    uint32_t originalValue;
    int32_t status;
    volatile uint32_t *pAddr = (volatile uint32_t *)testAddr;
    volatile uint32_t errFlagTimeout = SDL_MEMSS_PARITY_TIMEOUT;

    if (((errAggrBase & SDL_BASE_ADDR_MASK) == SDL_ERRORAGGREGATOR_BASE_FRAME(0U)) &&
        (testAddr != NULL))
    {
        /* Clear ISR flag */
        SDL_MEMSS_isrFlag = SDL_MEMSS_NO_INTERRUPT;
        SDL_ESM_setSelfTestCallback(&SDL_MEMSS_handleESMIntr, (void *)errAggrBase);
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_ACTIVE);

        /* Step 1: Set RAM to ECC test mode */
        SDL_MEMSS_configTestMode(memory, testMode);

        /* Step 2: Save original value and inject error */
        originalValue = *pAddr;
        *pAddr = originalValue ^ xorMask;  /* Flip lowest bit to inject 1-bit error */

        /* Step 3: Return to normal mode */
        SDL_MEMSS_configTestMode(memory, SDL_MEMSS_TESTMODE_NORMAL);

        /* Small delay for writes to latch */
        __asm("NOP #5");

        /* Read back to trigger ECC/parity detection */
        (void)*pAddr;

       /* Step 4: Wait for ESM interrupt flag */
        while ((SDL_MEMSS_isrFlag == SDL_MEMSS_NO_INTERRUPT) && (errFlagTimeout != 0U))
        {
            errFlagTimeout -= 1U;
        }

        SDL_ESM_clearSelfTestCallback();
        SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);

        /* Restore original value to clear ECC/parity error */
        *pAddr = originalValue;

        /* Step 5: Evaluate result */
        if (errFlagTimeout != 0U)
        {
            status = SDL_PASS;
        }
        else
        {
            status = SDL_EFAIL;
        }
    }
    else
    {
        status = SDL_EBADARGS;
    }

    return status;
}