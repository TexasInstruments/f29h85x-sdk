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
 *  \file     sdl_edc.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of EDC.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sdl_edc.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t SDL_EDC_setControlReg(uint32_t safetyAggrBase, SDL_EDC_CtrlReg edcCtrlReg)
{
    int32_t retVal = SDL_EBADARGS;
    uint32_t ctrlRegVal;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        ctrlRegVal = (((uint32_t)edcCtrlReg.pattern) << SDL_EDC_CONTROL_ECC_PATTERN_SHIFT);
        ctrlRegVal |= (((uint32_t)edcCtrlReg.forceNBit) << SDL_EDC_CONTROL_FORCE_NBIT_SHIFT);
        ctrlRegVal |= (((uint32_t)edcCtrlReg.forceBitError) << SDL_EDC_CONTROL_FORCE_DE_SHIFT);
        ctrlRegVal |= ((edcCtrlReg.enableParityChecker) << SDL_EDC_CONTROL_ECCCHECK_SHIFT);
    
        HW_WR_REG32((safetyAggrBase + SDL_EDC_CONTROL), ctrlRegVal);
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_EDC_getParityCheckerStatus(uint32_t safetyAggrBase, uint32_t *pStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *pStatus = HW_RD_FIELD32((safetyAggrBase + SDL_EDC_CONTROL),
                                 SDL_EDC_CONTROL_ECCCHECK);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_EDC_getParityPattern(uint32_t safetyAggrBase, uint32_t *pStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *pStatus = HW_RD_FIELD32((safetyAggrBase + SDL_EDC_CONTROL),
                                 SDL_EDC_CONTROL_ECC_PATTERN);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_EDC_injectErr1GroupNum(uint32_t safetyAggrBase, uint32_t groupNum)
{
    int32_t retVal = SDL_PASS;
    uint32_t regVal;

    if (((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U)) &&
        (groupNum < SDL_ESM_NUM_EVENT_GROUPS))
    {
        regVal = HW_RD_FIELD32((SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERROR1),
                                SDL_EDC_ERROR1_ECCBIT1);
        HW_WR_REG32((SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERROR1),
                    (regVal | groupNum));
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_EDC_injectBitErr(uint32_t safetyAggrBase, uint32_t bitIndex)
{
    int32_t retVal = SDL_PASS;
    uint32_t regVal;

    if (((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U)) &&
        (bitIndex < SDL_ESM_EVENTS_PER_GROUP))
    {
        regVal = HW_RD_FIELD32((SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERROR1),
                                SDL_EDC_ERROR1_ECCGRP);
        HW_WR_REG32((SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERROR1),
                      (regVal | bitIndex));
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_EDC_injectDoubleBitErr(uint32_t safetyAggrBase, uint32_t bitIndex)
{
    int32_t retVal = SDL_PASS;
    uint32_t regVal;

    if (((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U)) &&
        (bitIndex < SDL_ESM_EVENTS_PER_GROUP))
    {
        regVal = HW_RD_REG32(SDL_ESMSAFETYAGG_BASE + SDL_EDC_CONTROL);
        if((regVal & SDL_EDC_CONTROL_FORCE_DE_MASK) == SDL_EDC_CONTROL_FORCE_DE_MASK)
        {
            HW_WR_FIELD32((SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERROR2),
                          SDL_EDC_ERROR2_ECCBIT2,
                          bitIndex);
        }
        else
        {
            retVal = SDL_EBADARGS;
        }
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_EDC_getErr1Status(uint32_t safetyAggrBase, uint32_t *errStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *errStatus = HW_RD_REG32(SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERRORSTATUS1);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_EDC_setErr1Status(uint32_t safetyAggrBase, uint32_t statusVal)
{
    uint32_t regVal;
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        regVal = HW_RD_REG32(SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERRORSTATUS1);
        HW_WR_REG32((SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERRORSTATUS1),
                    regVal | statusVal);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_EDC_getErr2Status(uint32_t safetyAggrBase, uint32_t *errStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *errStatus = HW_RD_REG32(SDL_ESMSAFETYAGG_BASE + SDL_EDC_ERRORSTATUS2);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}