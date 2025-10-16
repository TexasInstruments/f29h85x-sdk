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
 *  \file     sdl_esm_safety_aggr.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of ESM Safety Aggregator.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sdl_esm_safety_aggr.h"

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

int32_t SDL_ESM_SAFETYAGGR_getRevision(uint32_t safetyAggrBase, SDL_ESM_SAFETYAGGR_Rev *revReg)
{
    uint32_t regVal;
    int32_t  retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        regVal  = HW_RD_REG32(safetyAggrBase + SDL_ESM_SAFETYAGGR_REVISION);

        revReg->scheme     = HW_GET_FIELD(regVal, SDL_ESM_SAFETYAGGR_REV_SCHEME);
        revReg->bu         = HW_GET_FIELD(regVal, SDL_ESM_SAFETYAGGR_REV_BU);
        revReg->moduleID   = HW_GET_FIELD(regVal, SDL_ESM_SAFETYAGGR_REV_MODULE_ID);
        revReg->rtlVer     = HW_GET_FIELD(regVal, SDL_ESM_SAFETYAGGR_REV_RTLVER);
        revReg->majorVer   = HW_GET_FIELD(regVal, SDL_ESM_SAFETYAGGR_REV_MAJORVER);
        revReg->customVer  = HW_GET_FIELD(regVal, SDL_ESM_SAFETYAGGR_REV_CUSTOMVER);
        revReg->minorVer   = HW_GET_FIELD(regVal, SDL_ESM_SAFETYAGGR_REV_MINORVER);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }
    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_clearSvBusStatus(uint32_t safetyAggrBase)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                    SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_DONE_MASK);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_getSvBusStatus(uint32_t safetyAggrBase, uint32_t *readStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *readStatus = HW_RD_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                                     SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_DONE);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_SvBusAddrtoRead(uint32_t safetyAggrBase, uint32_t busAddr)
{
    int32_t retVal = SDL_PASS;
    uint32_t regVal;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        regVal = HW_RD_REG32(safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR);
        HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                      ((busAddr << SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_ADDR_SHIFT) | regVal));
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_getSvBusAddr(uint32_t safetyAggrBase, uint32_t *busAddr)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *busAddr = HW_RD_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                                 SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_ADDR);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_triggerSvBusRead(uint32_t safetyAggrBase)
{
    int32_t retVal = SDL_PASS;
    uint32_t regVal;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        regVal = HW_RD_REG32(safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR);
        HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                    (regVal | SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_MASK));
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_configECCVectESMInst(uint32_t safetyAggrBase, SDL_ESM_Inst esmInst)
{
    int32_t retVal = SDL_PASS;
    uint32_t regVal, vecVal;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        regVal = HW_RD_REG32(safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR);
        vecVal = (regVal & (~SDL_ESM_SAFETYAGGR_ECC_VECTOR_MASK));
        switch(esmInst)
        {
            case SDL_ESM_CPU1_INST_ESM:
                /* Selecting ESM CPU1 for Control */
                HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                            (vecVal | SDL_ESM_SAFETYAGGR_ECC_VECTOR_ESM_CPU1));
                break;

            case SDL_ESM_CPU2_INST_ESM:
                /* Selecting ESM CPU2 for Control */
                HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                            (vecVal | SDL_ESM_SAFETYAGGR_ECC_VECTOR_ESM_CPU2));
                break;

            case SDL_ESM_CPU3_INST_ESM:
                /* Selecting ESM CPU3 for Control */
                HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                            (vecVal | SDL_ESM_SAFETYAGGR_ECC_VECTOR_ESM_CPU3));
                break;

            case SDL_ESM_SYSTEM_INST_ESM:
                /* Selecting ESM SYS for Control */
                HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ECC_VECTOR),
                            (vecVal | SDL_ESM_SAFETYAGGR_ECC_VECTOR_ESM_SYS));
                break;

            default:
                retVal = SDL_EBADARGS;
                break;
        }
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_getESMInstCntStatus(uint32_t safetyAggrBase, uint32_t *numInst)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *numInst = HW_RD_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_MISC_STATUS),
                                 SDL_ESM_SAFETYAGGR_MISC_STATUS);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_setDEDEOIReg(uint32_t safetyAggrBase)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_DED_EOI_REG),
                     SDL_ESM_SAFETYAGGR_DED_EOI_REG_MASK);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_getDEDEOIReg(uint32_t safetyAggrBase, uint32_t *regVal)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *regVal = HW_RD_REG32(safetyAggrBase + SDL_ESM_SAFETYAGGR_DED_EOI_REG);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_getPendingIntrStatus(uint32_t safetyAggrBase, uint32_t *pStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *pStatus = HW_RD_REG32(safetyAggrBase + SDL_ESM_SAFETYAGGR_DED_STATUS_REG0);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_enableEDCIntr(uint32_t safetyAggrBase, SDL_ESM_Inst enableIntrESM)
{
    int32_t retVal = SDL_PASS;
    uint32_t regVal, enVal = ((uint32_t)(0x1U) << ((uint32_t)enableIntrESM - 0x1U));

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        regVal = HW_RD_REG32(safetyAggrBase + SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0);
        HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0),
                                 (regVal | enVal));
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_disableEDCIntr(uint32_t safetyAggrBase, SDL_ESM_Inst disIntrESM)
{
    int32_t retVal = SDL_PASS;
    uint32_t disVal = ((uint32_t)(0x1U) << ((uint32_t)disIntrESM - 0x1U));

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        HW_WR_REG32((safetyAggrBase + SDL_ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0), disVal);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_enableAggrIntrErr(uint32_t safetyAggrBase, uint32_t intrEnable)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        if (intrEnable == SDL_ESM_SAFETYAGGR_INTR_PARITYERR_EN)
        {
            HW_WR_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ENABLE_SET),
                          SDL_ESM_SAFETYAGGR_ENABLE_SET_PARITY, 0x1U);
        }
        else if (intrEnable == SDL_ESM_SAFETYAGGR_INTR_TIMEOUTERR_EN)
        {
            HW_WR_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ENABLE_SET),
                          SDL_ESM_SAFETYAGGR_ENABLE_SET_TIMEOUT, 0x1U);
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

int32_t SDL_ESM_SAFETYAGGR_disableAggrIntrErr(uint32_t safetyAggrBase, uint32_t intrDisable)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        if (intrDisable == SDL_ESM_SAFETYAGGR_INTR_PARITYERR_DIS)
        {
            HW_WR_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ENABLE_CLR),
                          SDL_ESM_SAFETYAGGR_ENABLE_CLR_PARITY, 0x1U);
        }
        else if (intrDisable == SDL_ESM_SAFETYAGGR_INTR_TIMEOUTERR_DIS)
        {
            HW_WR_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_ENABLE_CLR),
                          SDL_ESM_SAFETYAGGR_ENABLE_CLR_TIMEOUT, 0x1U);
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

int32_t SDL_ESM_SAFETYAGGR_setAggrParityErr(uint32_t safetyAggrBase, uint32_t parityErr)
{
    int32_t retVal = SDL_PASS;

    if (((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U)) &&
        (parityErr <= SDL_ESM_SAFETYAGGR_INTR_MAX_COUNT))
    {
        HW_WR_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_STATUS_SET),
                      SDL_ESM_SAFETYAGGR_STATUS_SET_PARITY,
                      parityErr);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_setAggrTimeoutErr(uint32_t safetyAggrBase, uint32_t timeoutErr)
{
    int32_t retVal = SDL_PASS;

    if (((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U)) &&
        (timeoutErr <= SDL_ESM_SAFETYAGGR_INTR_MAX_COUNT))
    {
        HW_WR_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_STATUS_SET),
                      SDL_ESM_SAFETYAGGR_STATUS_SET_TIMEOUT,
                      timeoutErr);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_getAggrParityErrStatus(uint32_t safetyAggrBase, uint32_t *pErrStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *pErrStatus = HW_RD_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_STATUS_SET),
                                    SDL_ESM_SAFETYAGGR_STATUS_SET_PARITY);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_getAggrTimeoutErrStatus(uint32_t safetyAggrBase, uint32_t *tErrStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *tErrStatus = HW_RD_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_STATUS_SET),
                                    SDL_ESM_SAFETYAGGR_STATUS_SET_TIMEOUT);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_getAggrClearStatus(uint32_t safetyAggrBase, uint32_t *clearStatus)
{
    int32_t retVal = SDL_PASS;

    if ((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U))
    {
        *clearStatus = HW_RD_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_STATUS_CLR),
                                      SDL_ESM_SAFETYAGGR_STATUS_CLR);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_clearAggrParityErr(uint32_t safetyAggrBase, uint32_t parityErr)
{
    int32_t retVal = SDL_PASS;

    if (((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U)) &&
        (parityErr <= SDL_ESM_SAFETYAGGR_INTR_MAX_COUNT))
    {
        HW_WR_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_STATUS_CLR),
                      SDL_ESM_SAFETYAGGR_STATUS_CLR_PARITY,
                      parityErr);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_SAFETYAGGR_clearAggrTimeoutErr(uint32_t safetyAggrBase, uint32_t timeoutErr)
{
    int32_t retVal = SDL_PASS;
    uint32_t regVal;

    if (((safetyAggrBase & SDL_BASE_ADDR_MASK) == SDL_ESMSAFETYAGG_BASE_FRAME(0U)) &&
        (timeoutErr <= SDL_ESM_SAFETYAGGR_INTR_MAX_COUNT))
    {
        HW_WR_FIELD32((safetyAggrBase + SDL_ESM_SAFETYAGGR_STATUS_CLR),
                      SDL_ESM_SAFETYAGGR_STATUS_CLR_TIMEOUT,
                      timeoutErr);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}