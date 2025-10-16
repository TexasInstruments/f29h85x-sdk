/********************************************************************
 * Copyright (C) 2025 Texas Instruments Incorporated.
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
 *  \file     sdl_err_aggr.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of Aggregator.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sdl_err_aggr.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t SDL_ERR_AGGR_getHighPrioErrorAddr(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t *errAddr)
{
    int32_t retVal = SDL_PASS;

    if ((baseAddr & SDL_BASE_ADDR_MASK) == SDL_ERRORAGGREGATOR_BASE_FRAME(0U))
    {
        *errAddr = HW_RD_FIELD32((baseAddr + ((uint32_t)source + SDL_ERR_AGGR_O_HIGHPRIO_ERRADDR)),
                                 SDL_ERR_AGGR_TYPE_HIGHPRIO_ERRADDR);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ERR_AGGR_getLowPrioErrorAddr(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t *errAddr)
{
    int32_t retVal = SDL_PASS;
    if ((baseAddr & SDL_BASE_ADDR_MASK) == SDL_ERRORAGGREGATOR_BASE_FRAME(0U))
    {
        *errAddr = HW_RD_FIELD32((baseAddr + ((uint32_t)source + SDL_ERR_AGGR_O_LOWPRIO_ERRADDR)),
                                 SDL_ERR_AGGR_TYPE_LOWPRIO_ERRADDR);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ERR_AGGR_getErrorType(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t *errTypeVal)
{
    int32_t retVal = SDL_PASS;

    if ((baseAddr & SDL_BASE_ADDR_MASK) == SDL_ERRORAGGREGATOR_BASE_FRAME(0U))
    {
        *errTypeVal = HW_RD_FIELD32((baseAddr + ((uint32_t)source + SDL_ERR_AGGR_O_ERRTYPE)),
                                   SDL_ERR_AGGR_TYPE);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ERR_AGGR_setErrorType(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t errTypeMask)
{
    int32_t retVal = SDL_PASS;

    if ((baseAddr & SDL_BASE_ADDR_MASK) == SDL_ERRORAGGREGATOR_BASE_FRAME(0U))
    {
        HW_WR_REG32((baseAddr + ((uint32_t)source + SDL_ERR_AGGR_O_ERRTYPE_FRC)),
                    errTypeMask);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ERR_AGGR_clearErrorType(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t errTypeMask)
{
    int32_t retVal = SDL_PASS;

    if ((baseAddr & SDL_BASE_ADDR_MASK) == SDL_ERRORAGGREGATOR_BASE_FRAME(0U))
    {
        HW_WR_REG32((baseAddr + ((uint32_t)source + SDL_ERR_AGGR_O_ERRTYPE_CLR)),
                    errTypeMask);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ERR_AGGR_getStoredPCValue(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t *pcVal)
{
    int32_t retVal = SDL_PASS;
    if ((baseAddr & SDL_BASE_ADDR_MASK) == SDL_ERRORAGGREGATOR_BASE_FRAME(0U))
    {
        *pcVal = HW_RD_FIELD32((baseAddr + ((uint32_t)source + SDL_ERR_AGGR_O_PC)),
                                 SDL_ERR_AGGR_TYPE);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

void SDL_ESM_getBootErrorStatus(SDL_ESM_CPU1BootErrorStatus *pBootAddr)
{
    SDL_ESM_CPU1BootErrorStatus *bootAddr = (SDL_ESM_CPU1BootErrorStatus*)(SDL_BOOTROM_ESM_RAW_STATUS_ADDR);

    if (pBootAddr != ((void *) 0))
    {
        pBootAddr->ESM_RAW_STATUS               = bootAddr->ESM_RAW_STATUS;
        pBootAddr->PR_EA_HI_PRIO_ERROR_ADDR     = bootAddr->PR_EA_HI_PRIO_ERROR_ADDR;
        pBootAddr->PR_EA_LOW_PRIO_ERROR_ADDR    = bootAddr->PR_EA_LOW_PRIO_ERROR_ADDR;
        pBootAddr->PR_EA_ERROR_TYPE             = bootAddr->PR_EA_ERROR_TYPE;
        pBootAddr->PR_EA_PC_VALUE               = bootAddr->PR_EA_PC_VALUE;
        pBootAddr->DR1_EA_HI_PRIO_ERROR_ADDR    = bootAddr->DR1_EA_HI_PRIO_ERROR_ADDR;
        pBootAddr->DR1_EA_LOW_PRIO_ERROR_ADDR   = bootAddr->DR1_EA_LOW_PRIO_ERROR_ADDR;
        pBootAddr->DR1_EA_ERROR_TYPE            = bootAddr->DR1_EA_ERROR_TYPE;
        pBootAddr->DR1_EA_PC_VALUE              = bootAddr->DR1_EA_PC_VALUE;
        pBootAddr->DR2_EA_HI_PRIO_ERROR_ADDR    = bootAddr->DR2_EA_HI_PRIO_ERROR_ADDR;
        pBootAddr->DR2_EA_LOW_PRIO_ERROR_ADDR   = bootAddr->DR2_EA_LOW_PRIO_ERROR_ADDR;
        pBootAddr->DR2_EA_ERROR_TYPE            = bootAddr->DR2_EA_ERROR_TYPE;
        pBootAddr->DR2_EA_PC_VALUE              = bootAddr->DR2_EA_PC_VALUE;
        pBootAddr->DW_EA_HI_PRIO_ERROR_ADDR     = bootAddr->DW_EA_HI_PRIO_ERROR_ADDR;
        pBootAddr->DW_EA_LOW_PRIO_ERROR_ADDR    = bootAddr->DW_EA_LOW_PRIO_ERROR_ADDR;
        pBootAddr->DW_EA_ERROR_TYPE             = bootAddr->DW_EA_ERROR_TYPE;
        pBootAddr->DW_EA_PC_VALUE               = bootAddr->DW_EA_PC_VALUE;
        pBootAddr->INT_EA_HI_PRIO_ERROR_ADDR    = bootAddr->INT_EA_HI_PRIO_ERROR_ADDR;
        pBootAddr->INT_EA_LOW_PRIO_ERROR_ADDR   = bootAddr->INT_EA_LOW_PRIO_ERROR_ADDR;
        pBootAddr->INT_EA_ERROR_TYPE            = bootAddr->INT_EA_ERROR_TYPE;
        pBootAddr->INT_EA_PC_VALUE              = bootAddr->INT_EA_PC_VALUE;
    }
}