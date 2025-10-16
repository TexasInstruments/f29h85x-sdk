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
 *  \file     sdl_ip_esm.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of ESM.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sdlr_esm.h"
#include "sdl_esm.h"
#include "sdl_ip_esm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SDL_ESM_PIN_CTRL_KEY_RESET_VAL     (0x0U)

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

/**
 *  Design: C2000DL-746
 */
int32_t SDL_ESM_getRevisionId(uint32_t esmBase, SDL_ESM_RevisionID_t *revId)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        regVal  = HW_RD_REG32(esmBase + SDL_ESM_PID);
        revId->scheme = HW_GET_FIELD(regVal, SDL_ESM_PID_SCHEME);
        revId->bu     = HW_GET_FIELD(regVal, SDL_ESM_PID_BU);
        revId->func   = HW_GET_FIELD(regVal, SDL_ESM_PID_FUNC);
        revId->rtlRev = HW_GET_FIELD(regVal, SDL_ESM_PID_RTL);
        revId->major  = HW_GET_FIELD(regVal, SDL_ESM_PID_MAJOR);
        revId->custom = HW_GET_FIELD(regVal, SDL_ESM_PID_CUSTOM);
        revId->minor  = HW_GET_FIELD(regVal, SDL_ESM_PID_MINOR);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-747
 */
int32_t SDL_ESM_getInfo(uint32_t esmBase, SDL_ESM_Info_t *info)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        regVal  = HW_RD_REG32(esmBase + SDL_ESM_INFO);
        info->lastRstType = HW_GET_FIELD(regVal, SDL_ESM_INFO_LAST_RESET);
        info->critIntr    = HW_GET_FIELD(regVal, SDL_ESM_INFO_CRIT_INTR);
        info->plsGrpNum   = HW_GET_FIELD(regVal, SDL_ESM_INFO_PULSE_GROUPS);
        info->lvlGrpNum   = (HW_GET_FIELD(regVal, SDL_ESM_INFO_GROUPS) -
                             HW_GET_FIELD(regVal, SDL_ESM_INFO_PULSE_GROUPS));
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-748
 */
int32_t SDL_ESM_enableGlobalIntr(uint32_t esmBase)
{
    int32_t retVal = SDL_EBADARGS;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        HW_WR_FIELD32(esmBase +SDL_ESM_EN,
                      SDL_ESM_EN_KEY,
                      SDL_ESM_EN_KEY_ENABLE);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-748
 */
int32_t SDL_ESM_disableGlobalIntr(uint32_t esmBase)
{
    int32_t retVal = SDL_EBADARGS;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_EN,
                      SDL_ESM_EN_KEY,
                      SDL_ESM_EN_KEY_DISABLE);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-749
 */
int32_t SDL_ESM_getGlobalIntrEnabledStatus(uint32_t esmBase, uint32_t *pStatus)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ( (SDL_ESM_isBaseValid(esmBase) == true) &&
         (pStatus  != ((void *) 0)) )
    {
        regVal = HW_RD_FIELD32(esmBase + SDL_ESM_EN,
                      SDL_ESM_EN_KEY);

       *pStatus = regVal & SDL_ESM_EN_KEY_MASK;
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-750
 */
int32_t SDL_ESM_reset(uint32_t esmBase)
{
    int32_t retVal = SDL_EBADARGS;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_SFT_RST,
                      SDL_ESM_SFT_RST_KEY,
                      SDL_ESM_GLOBAL_SFT_RST_VAL);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-751
 */
int32_t SDL_ESM_getGroupIntrStatus(uint32_t esmBase, SDL_ESM_IntrType intrPrioType,
                                   SDL_ESM_IntrStatus *intrStatus)
{
    int32_t retVal = SDL_EBADARGS;

    if ((SDL_ESM_isBaseValid(esmBase) == true) &&
        (intrStatus != ((void *) 0)))
    {
        if (intrPrioType == (SDL_ESM_IntrType)SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR)
        {
            intrStatus->highestPendPulseEvent = HW_RD_FIELD32(
                        esmBase + SDL_ESM_LOW_PRI, SDL_ESM_LOW_PRI_PLS);
            intrStatus->highestPendLevelEvent = HW_RD_FIELD32(
                        esmBase + SDL_ESM_LOW_PRI, SDL_ESM_LOW_PRI_LVL);
            intrStatus->grpIntrStatus = HW_RD_REG32(esmBase + SDL_ESM_LOW);
        }
        else
        {
            intrStatus->highestPendPulseEvent = HW_RD_FIELD32(
                        esmBase + SDL_ESM_HI_PRI, SDL_ESM_HI_PRI_PLS);
            intrStatus->highestPendLevelEvent = HW_RD_FIELD32(
                        esmBase + SDL_ESM_HI_PRI, SDL_ESM_HI_PRI_LVL);
            intrStatus->grpIntrStatus = HW_RD_REG32(esmBase + SDL_ESM_HI);
        }

        intrStatus->selfTestStatus = SDL_ESM_getSelfTestStatus();
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-752
 */
int32_t SDL_ESM_writeEOI(uint32_t esmBase, SDL_ESM_IntrType intrType)
{
    int32_t retVal = SDL_EBADARGS;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_EOI, SDL_ESM_EOI_KEY,
                      ((uint32_t)0x1 << intrType));
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-753
 */
int32_t SDL_ESM_setPinControlMode(uint32_t esmBase, SDL_ESM_OperationMode mode)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    /* Map the mode passed to supported values */
    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (mode == SDL_ESM_OPERATION_MODE_NORMAL)
        {
            regVal = SDL_ESM_OPERATION_MODE_NORMAL;
        }
        else if (mode == SDL_ESM_OPERATION_MODE_CLEAR_EVENT)
        {
            regVal = SDL_ESM_OPERATION_MODE_CLEAR_EVENT;
        }
        else
        {
            regVal = SDL_ESM_OPERATION_MODE_ERROR_FORCE;
        }
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_KEY, regVal);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-754
 */
int32_t SDL_ESM_getPinControlMode(uint32_t esmBase, SDL_ESM_OperationMode *pMode)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pMode != NULL)
        {
            regVal = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_KEY);
            *pMode = regVal;
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-755
 */
int32_t SDL_ESM_getErrPinOutSignal(uint32_t esmBase, SDL_ESM_ErrPinOutSignal *pSignal)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pSignal != NULL)
        {
            *pSignal = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_PWM_EN);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-855
 */
int32_t SDL_ESM_setErrPinOutPolarity(uint32_t esmBase, SDL_ESM_PolarityType pType)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        HW_WR_FIELD32((esmBase + SDL_ESM_SYS_PIN_CTRL), 
                      SDL_ESM_SYS_PIN_CTRL_POLARITY, (uint32_t)pType);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-855
 */
int32_t SDL_ESM_getErrPinOutPolarity(uint32_t esmBase, SDL_ESM_PolarityType *pType)
{
    int32_t  retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pType != NULL)
        {
            *pType = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_POLARITY);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-777
 */
int32_t SDL_ESM_resetErrPin(uint32_t esmBase)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_KEY,
                      SDL_ESM_PIN_CTRL_KEY_RESET_VAL);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-756
 */
int32_t SDL_ESM_getErrPinStatus(uint32_t esmBase, uint32_t *pStatus)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pStatus != ((void *) 0))
        {
            *pStatus = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PIN_STS, SDL_ESM_SYS_PIN_STS_VAL);
            retVal =  SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-757
 */
int32_t SDL_ESM_getCurrErrPinLowTimeCnt(uint32_t esmBase, uint32_t *pPinCntrPre)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pPinCntrPre != ((void *) 0))
        {
            *pPinCntrPre = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PIN_CNTR, SDL_ESM_SYS_PIN_CNTR_COUNT);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-758
 */
int32_t SDL_ESM_setErrPinLowTimePreload(uint32_t esmBase, uint32_t lowTime)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (SDL_ESM_SYS_PIN_CNTR_PRE_COUNT_MAX >= lowTime)
        {
            HW_WR_FIELD32(esmBase + SDL_ESM_SYS_PIN_CNTR_PRE,
                          SDL_ESM_SYS_PIN_CNTR_PRE_COUNT,
                          lowTime);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-759
 */
int32_t SDL_ESM_getErrPinLowTimePreload(uint32_t esmBase, uint32_t *pLowTime)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pLowTime != ((void *) 0))
        {
            *pLowTime = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PIN_CNTR_PRE,
                          SDL_ESM_SYS_PIN_CNTR_PRE_COUNT);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 * Design: C2000DL-760
 */
int32_t SDL_ESM_PWMH_getCurrErrPinHighTimeCnt(uint32_t esmBase, uint32_t *pHighPWMHTime)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pHighPWMHTime != ((void *) 0))
        {
            *pHighPWMHTime = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PWMH_PIN_CNTR,
                                           SDL_ESM_SYS_PIN_CNTR_COUNT);
            retVal =SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-761
 */
int32_t SDL_ESM_PWMH_setErrPinHighTimePreload(uint32_t esmBase, uint32_t highTime)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (SDL_ESM_SYS_PIN_CNTR_PRE_COUNT_MAX >= highTime)
        {
            HW_WR_FIELD32(esmBase + SDL_ESM_SYS_PWMH_PIN_CNTR_PRE,
                          SDL_ESM_SYS_PIN_CNTR_PRE_COUNT,
                          highTime);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-762
 */
int32_t SDL_ESM_PWMH_getErrPinHighTimePreload(uint32_t esmBase, uint32_t *pPinPWMHCntrPre)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pPinPWMHCntrPre != ((void *) 0))
        {
            *pPinPWMHCntrPre = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PWMH_PIN_CNTR_PRE,
                                             SDL_ESM_SYS_PIN_CNTR_PRE_COUNT);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 * Design: C2000DL-763
 */
int32_t SDL_ESM_PWML_getCurrErrPinLowTimeCnt(uint32_t esmBase, uint32_t *pLowPWMLTime)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pLowPWMLTime != ((void *) 0))
        {
            *pLowPWMLTime = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PWML_PIN_CNTR,
                                          SDL_ESM_SYS_PIN_CNTR_COUNT);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-764
 */
int32_t SDL_ESM_PWML_setErrPinLowTimePreload(uint32_t esmBase, uint32_t lowTime)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (SDL_ESM_SYS_PIN_CNTR_PRE_COUNT_MAX >= lowTime)
        {
            HW_WR_FIELD32(esmBase + SDL_ESM_SYS_PWML_PIN_CNTR_PRE,
                          SDL_ESM_SYS_PIN_CNTR_PRE_COUNT,
                          lowTime);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-765
 */
int32_t SDL_ESM_PWML_getErrPinLowTimePreload(uint32_t esmBase, uint32_t *pPinPWMLCntrPre)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (pPinPWMLCntrPre!= ((void *) 0))
        {
            *pPinPWMLCntrPre = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PWML_PIN_CNTR_PRE,
                                             SDL_ESM_SYS_PIN_CNTR_PRE_COUNT);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-766
 */
int32_t SDL_ESM_setIntrStatusRAW(uint32_t esmBase, uint32_t intrSrc)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase) == true) &&
        (intrSrc  < SDL_ESM_MAX_NUM_EVENTS))
    {
        regVal  = HW_RD_REG32(esmBase +
                    SDL_ESM_ERR_GRP_RAW(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        regVal |= ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        HW_WR_REG32(esmBase +
                    SDL_ESM_ERR_GRP_RAW(intrSrc / SDL_ESM_EVENTS_PER_GROUP),
                    regVal);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-767
 */
int32_t SDL_ESM_getIntrStatusRAW(uint32_t esmBase, uint32_t intrSrc, uint32_t *pStatus)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase) == true) &&
        (intrSrc  < SDL_ESM_MAX_NUM_EVENTS)  &&
        (pStatus != ((void *) 0)))
    {
        regVal  = HW_RD_REG32(esmBase +
                    SDL_ESM_ERR_GRP_RAW(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        regVal &= ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        *pStatus  = (regVal >> (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-768
 */
int32_t SDL_ESM_getIntrStatus(uint32_t esmBase, uint32_t intrSrc, uint32_t *pStatus)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ( (SDL_ESM_isBaseValid(esmBase) == true) &&
         (intrSrc  < SDL_ESM_MAX_NUM_EVENTS) &&
         (pStatus != NULL) )
    {
        regVal  = HW_RD_REG32(esmBase +
                    SDL_ESM_ERR_GRP_STS(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        regVal &= ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        if (pStatus != ((void *) 0))
        {
            *pStatus  = (regVal >> (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-769
 */
int32_t SDL_ESM_clearIntrStatus(uint32_t esmBase, uint32_t intrSrc)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ( (SDL_ESM_isBaseValid(esmBase) == true) &&
         (intrSrc  < SDL_ESM_MAX_NUM_EVENTS))
    {
        regVal = ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        HW_WR_REG32(esmBase +
                SDL_ESM_ERR_GRP_STS(intrSrc / SDL_ESM_EVENTS_PER_GROUP), regVal);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-770
 */
int32_t SDL_ESM_isEnableIntr(uint32_t esmBase, uint32_t intrSrc, uint32_t *pEnStatus)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal, mask;

    if ( (SDL_ESM_isBaseValid(esmBase) == false) ||
         (intrSrc >= SDL_ESM_MAX_NUM_EVENTS) ||
         (pEnStatus == ((void *) 0)) )
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal  = HW_RD_REG32(esmBase +
                SDL_ESM_ERR_GRP_INTR_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        mask  = ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        regVal &= mask;

        if (regVal == ((uint32_t) (0U)))
        {
           *pEnStatus = SDL_ESM_INTRSTATUS_DIS;
        }
        else
        {
           *pEnStatus = SDL_ESM_INTRSTATUS_EN;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-771
 */
int32_t SDL_ESM_enableIntr(uint32_t esmBase, uint32_t intrSrc)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ( (SDL_ESM_isBaseValid(esmBase) == false) ||
         (intrSrc >= SDL_ESM_MAX_NUM_EVENTS) )
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal  = HW_RD_REG32(esmBase +
                SDL_ESM_ERR_GRP_INTR_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        regVal |= ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        HW_WR_REG32(esmBase +
                SDL_ESM_ERR_GRP_INTR_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP),
                regVal);
    }

    return retVal;
}

/**
 *  Design: C2000DL-772
 */
int32_t SDL_ESM_disableIntr(uint32_t esmBase, uint32_t intrSrc)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ( (SDL_ESM_isBaseValid(esmBase) == false) ||
         (intrSrc >= SDL_ESM_MAX_NUM_EVENTS) )
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        HW_WR_REG32(esmBase +
            SDL_ESM_ERR_GRP_INTR_EN_CLR(intrSrc / SDL_ESM_EVENTS_PER_GROUP),
            regVal);
    }

    return retVal;
}

/**
 *  Design: C2000DL-773
 */
int32_t SDL_ESM_setIntrPriorityLvl(uint32_t esmBase, uint32_t intrSrc,
                                   SDL_ESM_IntrType intrPriorityLvl)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ( (SDL_ESM_isBaseValid(esmBase) == true) &&
         (intrSrc  < SDL_ESM_MAX_NUM_EVENTS) )
    {
        regVal = HW_RD_REG32(esmBase +
                 SDL_ESM_ERR_GRP_INT_PRIO(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        if (intrPriorityLvl == (SDL_ESM_IntrType)SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR)
        {
            regVal &= ~((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        }
        else
        {
            regVal |= ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        }
        HW_WR_REG32(esmBase +
                    SDL_ESM_ERR_GRP_INT_PRIO(intrSrc / SDL_ESM_EVENTS_PER_GROUP),
                    regVal);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-774
 */
int32_t SDL_ESM_getIntrPriorityLvl(uint32_t esmBase, uint32_t intrSrc,
                                   SDL_ESM_IntrType *pIntrPriorityLvl)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal, mask;

    if ( (SDL_ESM_isBaseValid(esmBase) == true) &&
         (intrSrc  < SDL_ESM_MAX_NUM_EVENTS)  &&
         (pIntrPriorityLvl != ((void *) 0)) )
    {
        regVal = HW_RD_REG32(esmBase +
                 SDL_ESM_ERR_GRP_INT_PRIO(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        mask = ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        regVal &= mask;
        if (regVal == ((uint32_t) (0U)))
        {
           *pIntrPriorityLvl = SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR;
        }
        else
        {
            *pIntrPriorityLvl = SDL_ESM_INTR_TYPE_HIGH_PRIO_ERROR;
        }
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-775
 */
int32_t SDL_ESM_setInfluenceOnErrPin(uint32_t esmBase, uint32_t intrSrc, bool enable)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if (((esmBase & SDL_BASE_ADDR_MASK) != SDL_ESMSYSTEM_BASE_FRAME(0U)) ||
        (intrSrc >= SDL_ESM_MAX_NUM_EVENTS))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase +
                 SDL_ESM_SYS_ERR_GRP_PIN_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        if (true == enable)
        {
            regVal |= ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
            HW_WR_REG32(esmBase +
                SDL_ESM_SYS_ERR_GRP_PIN_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP),
                regVal);
        }
        else
        {
            regVal |= ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
            HW_WR_REG32(esmBase +
                SDL_ESM_SYS_ERR_GRP_PIN_EN_CLR(intrSrc / SDL_ESM_EVENTS_PER_GROUP),
                regVal);
        }
    }

    return(retVal);
}

/**
 *  Design: C2000DL-776
 */
int32_t SDL_ESM_getInfluenceOnErrPin(uint32_t esmBase, uint32_t intrSrc,
                                     uint32_t *pInfluence)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal, mask;

    if ( (SDL_ESM_isBaseValid(esmBase) == false) ||
         (intrSrc >= SDL_ESM_MAX_NUM_EVENTS)     ||
         (pInfluence == ((void *) 0)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal  = HW_RD_REG32(esmBase +
               SDL_ESM_SYS_ERR_GRP_PIN_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        mask   = ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        regVal &= mask;

        if (regVal == 0x0U)
        {
           *pInfluence = 0x0U;
        }
        else
        {
           *pInfluence = 0x1U;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-779
 */
int32_t SDL_ESM_isEnableCriticalIntr(uint32_t esmBase, uint32_t intrSrc, uint32_t *pEnStatus)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal, mask;

    if ( (SDL_ESM_isBaseValid(esmBase) == false) ||
         (intrSrc >= SDL_ESM_MAX_NUM_EVENTS) ||
         (pEnStatus == ((void *) 0)) )
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase +
                 SDL_ESM_ERR_GRP_CRIT_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        mask = ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        regVal &= mask;

        if (regVal == ((uint32_t) (0U)))
        {
           *pEnStatus = SDL_ESM_INTRSTATUS_DIS;
        }
        else
        {
           *pEnStatus = SDL_ESM_INTRSTATUS_EN;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-778
 */
int32_t SDL_ESM_enableCriticalIntr(uint32_t esmBase, uint32_t intrSrc)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ( (SDL_ESM_isBaseValid(esmBase) == false) ||
         (intrSrc >= SDL_ESM_MAX_NUM_EVENTS) )
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal  = HW_RD_REG32(esmBase +
                SDL_ESM_ERR_GRP_CRIT_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP));
        regVal |= ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        HW_WR_REG32(esmBase +
                SDL_ESM_ERR_GRP_CRIT_EN_SET(intrSrc / SDL_ESM_EVENTS_PER_GROUP),
                regVal);
    }

    return retVal;
}

/**
 *  Design: C2000DL-780
 */
int32_t SDL_ESM_disableCriticalIntr(uint32_t esmBase, uint32_t intrSrc)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ( (SDL_ESM_isBaseValid(esmBase) == false) ||
         (intrSrc >= SDL_ESM_MAX_NUM_EVENTS) )
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = ((uint32_t) 0x1U << (intrSrc % SDL_ESM_EVENTS_PER_GROUP));
        HW_WR_REG32(esmBase +
            SDL_ESM_ERR_GRP_CRIT_EN_CLR(intrSrc / SDL_ESM_EVENTS_PER_GROUP),
            regVal);
    }

    return retVal;
}

/**
 *  Design: C2000DL-846
 */
int32_t SDL_ESM_enableHiPriWDConfig(uint32_t esmBase)
{
    int32_t retVal = SDL_PASS;

    if ((SDL_ESM_isBaseValid(esmBase) == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_CPU_HI_PRI_WD_CFG,
                      SDL_ESM_CPU_HI_PRI_WD_CFG_EN,
                      SDL_ESM_CPU_HI_PRI_WATCHDOG_ENABLE);
    }

    return retVal;
}

/**
 *  Design: C2000DL-846
 */
int32_t SDL_ESM_disableHiPriWDConfig(uint32_t esmBase)
{
    int32_t retVal = SDL_PASS;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_CPU_HI_PRI_WD_CFG,
                      SDL_ESM_CPU_HI_PRI_WD_CFG_EN,
                      SDL_ESM_CPU_HI_PRI_WATCHDOG_DISABLE);
    }

    return retVal;
}

/**
 *  Design: C2000DL-781
 */
int32_t SDL_ESM_enableHiPriWDFreerun(uint32_t esmBase)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal  = HW_RD_REG32(esmBase + SDL_ESM_CPU_HI_PRI_WD_CFG);
        HW_WR_REG32(esmBase + SDL_ESM_CPU_HI_PRI_WD_CFG,
                  (regVal & SDL_ESM_CPU_HI_PRI_WD_CFG_MAX));
    }

    return retVal;
}

/**
 *  Design: C2000DL-781
 */
int32_t SDL_ESM_disableHiPriWDFreerun(uint32_t esmBase)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal  = HW_RD_REG32(esmBase + SDL_ESM_CPU_HI_PRI_WD_CFG);
        HW_WR_REG32((esmBase + SDL_ESM_CPU_HI_PRI_WD_CFG),
                    (regVal & SDL_ESM_CPU_HI_PRI_WD_CFG_EN_MAX));
    }

    return retVal;
}

/**
 * Design: C2000DL-792
 */
int32_t SDL_ESM_getHiPriWDCounter(uint32_t esmBase, uint32_t *pWDCntrVal)
{
    int32_t retVal = SDL_PASS;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)) ||
        (pWDCntrVal == ((void *) 0)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        *pWDCntrVal = HW_RD_FIELD32(esmBase + SDL_ESM_CPU_HI_PRI_WD_CNTR,
                                    SDL_ESM_CPU_HI_PRI_WD_CNTR_COUNT);
    }

    return retVal;
}

/**
 *  Design: C2000DL-797
 */
int32_t SDL_ESM_setHiPriWDCntrPreload(uint32_t esmBase, uint32_t preloadValue)
{
    int32_t retVal;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        if (preloadValue <= SDL_ESM_CPU_HI_PRI_WD_PRE_COUNT_MAX)
        {
            HW_WR_FIELD32(esmBase + SDL_ESM_CPU_HI_PRI_WD_CNTR_PRE,
                          SDL_ESM_CPU_HI_PRI_WD_PRE_COUNT,
                          preloadValue);
            retVal = SDL_PASS;
        }
        else
        {
            retVal = SDL_EBADARGS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-798
 */
int32_t SDL_ESM_getHiPriWDCntrPreload(uint32_t esmBase, uint32_t *pPreLoadVal)
{
    int32_t retVal = SDL_EBADARGS;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        if (pPreLoadVal != ((void *) 0))
        {
            *pPreLoadVal = HW_RD_FIELD32(esmBase + SDL_ESM_CPU_HI_PRI_WD_CNTR_PRE,
                                         SDL_ESM_CPU_HI_PRI_WD_PRE_COUNT);
            retVal = SDL_PASS;
        }
    }

    return retVal;
}

/**
 *  Design: C2000DL-800
 */
int32_t SDL_ESM_getHiPriWDIntrStatus(uint32_t esmBase, uint32_t *pWDStatus)
{
    int32_t retVal = SDL_PASS;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)) ||
        (pWDStatus == ((void *) 0)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        *pWDStatus = HW_RD_FIELD32(esmBase + SDL_ESM_CPU_HI_PRI_WD_INTR_SET,
                                   SDL_ESM_CPU_CLR_HI_PRI_WD_INTR);
    }

    return retVal;
}

/**
 *  Design: C2000DL-799
 */
int32_t SDL_ESM_setHiPriWDIntrOutput(uint32_t esmBase)
{
    int32_t retVal = SDL_PASS;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_CPU_HI_PRI_WD_INTR_SET,
                      SDL_ESM_CPU_SET_HI_PRI_WD_INTR,
                      SDL_ESM_CPU_SET_HI_PRI_WD_INTR_MAX);
    }

    return retVal;
}

/**
 *  Design: C2000DL-799
 */
int32_t SDL_ESM_clearHiPriWDIntrOutput(uint32_t esmBase)
{
    int32_t retVal = SDL_PASS;

    if ((SDL_ESM_isBaseValid(esmBase)   == false) ||
        ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_CPU_HI_PRI_WD_INTR_CLR,
                      SDL_ESM_CPU_CLR_HI_PRI_WD_INTR,
                      SDL_ESM_CPU_CLR_HI_PRI_WD_INTR_MAX);
    }

    return retVal;
}

/**
 *  Design: C2000DL-801
 */
int32_t SDL_ESM_enableErrPinMonConfig(uint32_t esmBase)
{
    int32_t retVal = SDL_EBADARGS;

    if (((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERRPIN_MON_CFG,
                      SDL_ESM_SYS_CFG_ERRPIN_MON,
                      SDL_ESM_SYS_CFG_ERRPIN_MON_EN_KEY);
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_disableErrPinMonConfig(uint32_t esmBase)
{
    int32_t retVal = SDL_EBADARGS;

    if (((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)))
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERRPIN_MON_CFG,
                      SDL_ESM_SYS_CFG_ERRPIN_MON,
                      SDL_ESM_SYS_CFG_ERRPIN_MON_DIS_KEY);
        retVal = SDL_PASS;
    }

    return retVal;
}

/**
 *  Design: C2000DL-802
 */
int32_t SDL_ESM_getErrPinMonConfigStatus(uint32_t esmBase, uint32_t *pStatus)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        *pStatus = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_ERRPIN_MON_CFG,
                                 SDL_ESM_SYS_CFG_ERRPIN_MON);
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_setErrPinMonitorIntr(uint32_t esmBase)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERRPIN_MON_INTR_SET,
                      SDL_ESM_SYS_SET_ERRPIN_MON_INTR,
                      SDL_ESM_SYS_SET_ERRPIN_MON_INTR_MAX);
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_clearErrPinMonitorIntr(uint32_t esmBase)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERRPIN_MON_INTR_CLR,
                      SDL_ESM_SYS_CLR_ERRPIN_MON_INTR,
                      SDL_ESM_SYS_CLR_ERRPIN_MON_INTR_MAX);
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_lockErrPinInfluenceConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK,
                      SDL_ESM_SYS_LOCK_ERRPIN_INFLUENCE,
                      (regVal | groupNum));
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_unlockErrPinInfluenceConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK,
                      SDL_ESM_SYS_LOCK_ERRPIN_INFLUENCE,
                      (regVal & (~(groupNum))));
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_commitErrPinInfluenceConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

   if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT);
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT,
                      SDL_ESM_SYS_COMMIT_ERRPIN_INFLUENCE,
                      (regVal | groupNum));
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_lockErrorGroupIntrConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase) == false) || (groupNum > SDL_ESM_NUM_EVENT_GROUPS))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_GROUP_N_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_GROUP_N_LOCK,
                      SDL_ESM_GROUP_LOCK,
                      (regVal | ((uint32_t)0x1U << groupNum)));
    }

    return retVal;
}

int32_t SDL_ESM_getIntrLockReg(uint32_t esmBase, uint32_t *groupNum)
{
    int32_t retVal = SDL_EBADARGS;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        *groupNum = HW_RD_REG32(esmBase + SDL_ESM_GROUP_N_LOCK);
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_unlockErrorGroupIntrConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase) == false) || (groupNum > SDL_ESM_NUM_EVENT_GROUPS))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_GROUP_N_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_GROUP_N_LOCK,
                      SDL_ESM_GROUP_LOCK,
                      (regVal & (~(groupNum))));
    }

    return retVal;
}

int32_t SDL_ESM_commitErrorGroupIntrConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase) == false) || (groupNum > SDL_ESM_NUM_EVENT_GROUPS))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_GROUP_N_COMMIT);
        HW_WR_FIELD32(esmBase + SDL_ESM_GROUP_N_COMMIT,
                      SDL_ESM_GROUP_COMMIT,
                      regVal | groupNum);
    }

    return retVal;
}

/**
 *  Design: C2000DL-
 */
int32_t SDL_ESM_setErrPinInfluenceLock(uint32_t esmBase, uint32_t groupNumber)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal;

    if (((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U)) &&
        (groupNumber < SDL_ESM_NUM_EVENT_GROUPS))
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK,
                      SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK,
                      (regVal | groupNumber));
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_getErrPinInfluenceLock(uint32_t esmBase, uint32_t *errorPinlockSTS)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        *errorPinlockSTS = HW_RD_REG32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK);
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_setErrPinInfluenceCommit(uint32_t esmBase)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t regVal, lockSTS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        (void)SDL_ESM_getErrPinInfluenceLock(esmBase, &lockSTS);
        regVal = HW_RD_REG32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT);
        HW_WR_FIELD32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT,
                      SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT,
                      (regVal | lockSTS));
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_getErrPinInfluenceCommit(uint32_t esmBase, uint32_t *errorPinCommitSTS)
{
    int32_t retVal = SDL_EBADARGS;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        *errorPinCommitSTS = HW_RD_REG32(esmBase + SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT);
        retVal = SDL_PASS;
    }

    return retVal;
}

int32_t SDL_ESM_lockCriticalPriIntrInfluenceConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase) == false) || (groupNum > SDL_ESM_NUM_EVENT_GROUPS))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_CRI_PRI_INFLUENCE_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_CRI_PRI_INFLUENCE_LOCK,
                      SDL_ESM_LOCK_CRI_PRI_INFLUENCE,
                      regVal | groupNum);
    }

    return retVal;
}

int32_t SDL_ESM_unlockCriticalPriIntrInfluenceConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase) == false) || (groupNum > SDL_ESM_NUM_EVENT_GROUPS))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_CRI_PRI_INFLUENCE_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_CRI_PRI_INFLUENCE_LOCK,
                      SDL_ESM_LOCK_CRI_PRI_INFLUENCE,
                      (regVal & (~(groupNum))));
    }

    return retVal;
}

int32_t SDL_ESM_commitCriticalPriIntrInfluenceConfig(uint32_t esmBase, uint32_t groupNum)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if ((SDL_ESM_isBaseValid(esmBase) == false) || (groupNum > SDL_ESM_NUM_EVENT_GROUPS))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_CRI_PRI_INFLUENCE_COMMIT);
        HW_WR_FIELD32(esmBase + SDL_ESM_CRI_PRI_INFLUENCE_COMMIT,
                      SDL_ESM_COMMIT_CRI_PRI_INFLUENCE,
                      (regVal | groupNum));
    }

    return retVal;
}

int32_t SDL_ESM_lockMMRConfig(uint32_t esmBase, SDL_ESM_MMRConfig configMMR)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if (SDL_ESM_isBaseValid(esmBase) == false)
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_MMR_CONFIG_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_MMR_CONFIG_LOCK,
                      SDL_ESM_MMR_CONFIG_LOCK,
                      regVal | configMMR);
    }

    return retVal;
}

int32_t SDL_ESM_unlockMMRConfig(uint32_t esmBase, SDL_ESM_MMRConfig configMMR)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if (SDL_ESM_isBaseValid(esmBase) == false)
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_MMR_CONFIG_LOCK);
        HW_WR_FIELD32(esmBase + SDL_ESM_MMR_CONFIG_LOCK,
                      SDL_ESM_MMR_CONFIG_LOCK,
                      (regVal & (~configMMR)));
    }

    return retVal;
}

int32_t SDL_ESM_commitMMRConfig(uint32_t esmBase, SDL_ESM_MMRConfig configMMR)
{
    int32_t  retVal = SDL_PASS;
    uint32_t regVal;

    if (SDL_ESM_isBaseValid(esmBase) == false)
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        regVal = HW_RD_REG32(esmBase + SDL_ESM_MMR_CONFIG_COMMIT);
        HW_WR_FIELD32(esmBase + SDL_ESM_MMR_CONFIG_COMMIT,
                      SDL_ESM_MMR_CONFIG_COMMIT,
                      (regVal | configMMR));
    }

    return retVal;
}