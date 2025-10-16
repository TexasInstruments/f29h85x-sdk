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

#include "sdl_esm.h"
#include "sdlr_esm.h"
#include "sdl_esm_priv.h"
#include <include/hw_types.h>
#include <include/sdlr_sysctl.h>

static void SDL_ESM_defaultCallback(uint32_t esmBase, uint32_t intSrc,
                                    void *callbackArg)
{
    /* Do nothing */
}

/*
 * Design: C2000DL-789
 */
int32_t SDL_ESM_hiInterruptHandler(uint32_t esmBase, SDL_ESM_IntrStatus *intrStatus)
{
    int32_t retVal;

    /* Check the baseAddr */
    if((SDL_ESM_isBaseValid(esmBase) == true) && (intrStatus != NULL))
    {
        /* Call common Interrupt handler */
        SDL_ESM_interruptHandler(esmBase, SDL_ESM_INTR_TYPE_HIGH_PRIO_ERROR, intrStatus);

        /*
         * If REVID is Rev 0 or Rev A, address CPU fault workaround. This is only
         * applicable to the group 0 events.
         */
        if((HW_RD_REG16(SDL_DEVCFG_BASE + SDL_SYSCTL_O_REVID) <= SDL_SYSCTL_REVID_REVA) &&
           (intrStatus->highestPendPulseEvent <= SDL_ESM_EVENT_CPU1_ERAD_NMI))
        {
            SDL_ESM_clearNMIFetchErrataWorkaround(esmBase);
        }

        retVal = SDL_PASS;
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return(retVal);
}

/*
 * Design: C2000DL-789
 */
int32_t SDL_ESM_loInterruptHandler(uint32_t esmBase, SDL_ESM_IntrStatus *intrStatus)
{
    int32_t retVal;

    /* Check the baseAddr */
    if((SDL_ESM_isBaseValid(esmBase) == true) && (intrStatus != NULL))
    {
        /* Call common Interrupt handler */
        SDL_ESM_interruptHandler(esmBase, SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR, intrStatus);

        retVal = SDL_PASS;
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return(retVal);
}

void SDL_ESM_setSelfTestStatus(SDL_ESM_SelfTestStatus selfTestStatus)
{
    SDL_ESM_Instance_t *SDL_ESM_instance;

    /*
     * The instance object is the same regardless of CPU, so we can use the
     * the CPU1 ESM instance for this purpose even if this code is executing
     * on another CPU.
     */
    SDL_ESM_selectESMInst(SDL_ESMCPU1_BASE, &SDL_ESM_instance);

    SDL_ESM_instance->selfTestStatus = selfTestStatus;
}

SDL_ESM_SelfTestStatus SDL_ESM_getSelfTestStatus(void)
{
    SDL_ESM_Instance_t *SDL_ESM_instance;

    /*
     * The instance object is the same regardless of CPU, so we can use the
     * the CPU1 ESM instance for this purpose even if this code is executing
     * on another CPU. This parameter isn't applicable to the SYSTEM instance.
     */
    SDL_ESM_selectESMInst(SDL_ESMCPU1_BASE, &SDL_ESM_instance);
        
    return (SDL_ESM_instance->selfTestStatus);
}

void SDL_ESM_setSelfTestCallback(SDL_ESM_SelfTestCallback callback,
                                 void *callbackArg)
{
    SDL_ESM_Instance_t *SDL_ESM_instance;

    /*
     * The instance object is the same regardless of CPU, so we can use the
     * the CPU1 ESM instance for this purpose even if this code is executing
     * on another CPU. This parameter isn't applicable to the SYSTEM instance.
     */
    SDL_ESM_selectESMInst(SDL_ESMCPU1_BASE, &SDL_ESM_instance);

    SDL_ESM_instance->selfTestCallback = callback;
    SDL_ESM_instance->callbackArg = callbackArg;
}

void SDL_ESM_clearSelfTestCallback(void)
{
    SDL_ESM_Instance_t *SDL_ESM_instance;

    /*
     * The instance object is the same regardless of CPU, so we can use the
     * the CPU1 ESM instance for this purpose even if this code is executing
     * on another CPU.
     */
    SDL_ESM_selectESMInst(SDL_ESMCPU1_BASE, &SDL_ESM_instance);

    SDL_ESM_instance->selfTestCallback = &SDL_ESM_defaultCallback;
}

int32_t SDL_ESM_getNErrorStatus(uint32_t esmBase, uint32_t *pStatus)
{
    int32_t  retVal = SDL_EBADARGS;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        retVal = SDL_ESM_getErrPinStatus(esmBase, pStatus);
    }

    return retVal;
}

/* Read back the static config API implementation
 * Returns the static register configuration for the ESM module for the specified instance.
 * This API can be used by the application to read back the static config. */

int32_t SDL_ESM_getStaticRegisters(uint32_t esmBase, SDL_ESM_StaticRegs *pStaticRegs)
{
    int32_t  retVal = SDL_EBADARGS;
    uint32_t groupIndex;

    if (SDL_ESM_isBaseValid(esmBase) == true)
    {
        /*Base address will assign to the Structure variable and Each structure variable 32bit wide*/
        SDL_esmRegs *esmRegs = (SDL_esmRegs *)(uintptr_t)esmBase;

        if (pStaticRegs != ((void *) 0))
        {
            pStaticRegs->PID                        = esmRegs->PID;
            pStaticRegs->INFO                       = esmRegs->INFO;
            pStaticRegs->EN                         = esmRegs->EN;
            pStaticRegs->LOW_PRI                    = esmRegs->LOW_PRI;
            pStaticRegs->HI_PRI                     = esmRegs->HI_PRI;
            pStaticRegs->LOW                        = esmRegs->LOW;
            pStaticRegs->HI                         = esmRegs->HI;
            pStaticRegs->EOI                        = esmRegs->EOI;
            pStaticRegs->GROUP_N_LOCK               = esmRegs->GROUP_N_LOCK;
            pStaticRegs->GROUP_N_COMMIT             = esmRegs->GROUP_N_COMMIT;
            pStaticRegs->CRI_PRI_INFLUENCE_LOCK     = esmRegs->CRI_PRI_INFLUENCE_LOCK;
            pStaticRegs->CRI_PRI_INFLUENCE_COMMIT   = esmRegs->CRI_PRI_INFLUENCE_COMMIT;
            pStaticRegs->MMR_CONFIG_LOCK            = esmRegs->MMR_CONFIG_LOCK;
            pStaticRegs->MMR_CONFIG_COMMIT          = esmRegs->MMR_CONFIG_COMMIT;
            if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
            {
                pStaticRegs->PIN_CTRL                   = esmRegs->PIN_CTRL;
                pStaticRegs->PIN_STS                    = esmRegs->PIN_STS;
                pStaticRegs->PIN_CNTR_PRE               = esmRegs->PIN_CNTR_PRE;
                pStaticRegs->PWMH_PIN_CNTR_PRE          = esmRegs->PWMH_PIN_CNTR_PRE;
                pStaticRegs->PWML_PIN_CNTR_PRE          = esmRegs->PWML_PIN_CNTR_PRE;
            }
            else
            {
                pStaticRegs->HI_PRI_WD_CFG              = esmRegs->HI_PRI_WD_CFG;
                pStaticRegs->HI_PRI_WD_CNTR_PRE         = esmRegs->HI_PRI_WD_CNTR_PRE;
                pStaticRegs->HI_PRI_WD_INTR_SET         = esmRegs->HI_PRI_WD_INTR_SET;
            }

        /*It reads Error group Register of ESM instances*/

            for (groupIndex = 0U; groupIndex < SDL_ESM_NUM_EVENT_GROUPS; groupIndex++)
            {
                pStaticRegs->ERR_GRP[groupIndex].RAW          = esmRegs->ERR_GRP[groupIndex].RAW;
                pStaticRegs->ERR_GRP[groupIndex].STATUS       = esmRegs->ERR_GRP[groupIndex].STS;
                pStaticRegs->ERR_GRP[groupIndex].INTR_EN_SET  = esmRegs->ERR_GRP[groupIndex].INTR_EN_SET;
                pStaticRegs->ERR_GRP[groupIndex].INTR_EN_CLR  = esmRegs->ERR_GRP[groupIndex].INTR_EN_CLR;
                pStaticRegs->ERR_GRP[groupIndex].INT_PRIO     = esmRegs->ERR_GRP[groupIndex].INT_PRIO;
                pStaticRegs->ERR_GRP[groupIndex].CRIT_EN_SET   = esmRegs->ERR_EXT_GRP[groupIndex].CRIT_EN_SET;
                pStaticRegs->ERR_GRP[groupIndex].CRIT_EN_CLR   = esmRegs->ERR_EXT_GRP[groupIndex].CRIT_EN_CLR;
                if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
                {
                    pStaticRegs->ERR_GRP[groupIndex].PIN_EN_SET   = esmRegs->ERR_GRP[groupIndex].PIN_EN_SET;
                    pStaticRegs->ERR_GRP[groupIndex].PIN_EN_CLR   = esmRegs->ERR_GRP[groupIndex].PIN_EN_CLR;
                }
            }
            retVal = SDL_PASS;
        }
    }
    return retVal;
}

/* Verifies the written config against the provided configuration */
int32_t SDL_ESM_verifyConfig(uint32_t esmBase, const SDL_ESM_Config *pConfig)
{
    uint32_t intStatus;
    uint32_t groupIndex, bitIndex;
    SDL_ESM_IntrType intrPriorityLvlRd;
    SDL_ESM_IntrType intrPriorityLvlWr;
    uint32_t influence;
    int32_t result = SDL_EBADARGS;
    uint32_t intNum;
    int32_t sdlRet = SDL_PASS;
    uint32_t enableRd;
    uint32_t enableWr;

    /* Check for valid pConfig and ESM register base address */
    if ((SDL_ESM_isBaseValid(esmBase) == false) || (pConfig == NULL))
    {
        result = SDL_EBADARGS;
    }
    else
    {
        /* ESM reset and configure */
        for (groupIndex = 0U; groupIndex < (SDL_ESM_MAX_NUM_EVENTS/SDL_ESM_EVENTS_PER_GROUP); groupIndex++)
        {
            uint32_t remainingBits = SDL_ESM_MAX_NUM_EVENTS - (groupIndex * SDL_ESM_EVENTS_PER_GROUP);

            if (remainingBits > SDL_ESM_EVENTS_PER_GROUP)
            {
                remainingBits = SDL_ESM_EVENTS_PER_GROUP;
            }

            for (bitIndex = 0U; bitIndex < remainingBits; bitIndex++)
            {
                intNum = (groupIndex * SDL_ESM_EVENTS_PER_GROUP) + bitIndex;

                sdlRet = SDL_ESM_isEnableIntr(esmBase, intNum, &intStatus);

                enableWr = ((pConfig->enableBitmap[groupIndex] & (SDL_ESM_MASK_BIT << bitIndex)) != 0U)? 1U:0U;

                if (intStatus == enableWr)
                {
                    intrPriorityLvlWr = ((pConfig->priorityBitmap[groupIndex]
                                         & (((uint32_t)1U)<<bitIndex)) != 0U)?1U:0U;
                    (void)SDL_ESM_getIntrPriorityLvl(esmBase,
                                                     intNum,
                                                     &intrPriorityLvlRd);

                    if (intrPriorityLvlWr != intrPriorityLvlRd)
                    {
                        sdlRet = SDL_EFAIL;
                    }
                }
                else
                {
                    sdlRet = SDL_EFAIL;
                }

                if ((sdlRet == SDL_PASS) && (esmBase == SDL_ESMSYSTEM_BASE))
                {
                    enableWr = ((pConfig->errorPinBitmap[groupIndex]
                                 & (SDL_ESM_MASK_BIT << bitIndex)) != 0U)? 1U:0U;
                    sdlRet = SDL_ESM_getInfluenceOnErrPin(esmBase,
                                                          intNum,
                                                          &influence);
                    if (sdlRet == SDL_PASS)
                    {
                        enableRd = (influence != 0U)? 1U:0U;
                        if (enableWr != enableRd)
                        {
                            sdlRet = SDL_EFAIL;
                        }
                    }
                }
                if (sdlRet != SDL_PASS)
                {
                    break;
                }
            }
            if (sdlRet != SDL_PASS)
            {
                break;
            }
        }
        result = sdlRet;
    }

    return result;
}

/* Function used to clear the nERROR pin */
int32_t SDL_ESM_clearNError(uint32_t esmBase)
{
    int32_t  retVal = SDL_PASS;
    uint32_t status;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        if (SDL_ESM_resetErrPin(esmBase) == SDL_PASS)
        {
            (void)SDL_ESM_getErrPinStatus(esmBase, &status);
            if (status != SDL_ESM_SYS_PIN_STS_VAL_MAX)
            {
                retVal = SDL_EFAIL;
            }
        }
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

int32_t SDL_ESM_setNError(uint32_t esmBase)
{
    int32_t retVal;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        /* Set Force Error output */
        retVal = SDL_ESM_setPinControlMode(esmBase, SDL_ESM_OPERATION_MODE_ERROR_FORCE);
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return retVal;
}

/**
 * Design: C2000DL-810
 */
int32_t SDL_ESM_setPinOutSignalMode(uint32_t esmBase, SDL_ESM_ErrPinOutSignal pinOutSignal)
{
    int32_t    retVal = SDL_EBADARGS;
    int32_t    sdlRet;
    uint32_t   intStatus;
    uint32_t   pinOutVal;

    if ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
    {
        /* In SDL_ESM_init API, global interrupt are enabled so here
           it should get disabled before change outPut mode.
        */
        /* Disable global interrupt */
        sdlRet = SDL_ESM_disableGlobalIntr(esmBase);

        if (sdlRet == SDL_PASS)
        {
            if (pinOutSignal == SDL_ESM_PWM_PINOUT)
            {
                /* Enable PWM error Ouptput */
                HW_WR_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_PWM_EN, SDL_ESM_PWM_PINOUT);
                /* Verify PWM error Ouptput */
                pinOutVal = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_PWM_EN);

                if (pinOutVal == SDL_ESM_PWM_PINOUT)
                {
                    retVal = SDL_PASS;
                }
            }
            else if (pinOutSignal == SDL_ESM_LVL_PINOUT)
            {
                /* Enable LVL error Ouptput */
                HW_WR_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_PWM_EN, SDL_ESM_LVL_PINOUT);
                /* Verify PWM error Ouptput */
                pinOutVal = HW_RD_FIELD32(esmBase + SDL_ESM_SYS_PIN_CTRL, SDL_ESM_SYS_PIN_CTRL_PWM_EN);

                if (pinOutVal == SDL_ESM_LVL_PINOUT)
                {
                    retVal = SDL_PASS;
                }
            }
            else
            {
                /* For MISRA C Compliance */
            }

            /* global interrupt are disabled, enable again global interrupt */
            sdlRet = SDL_ESM_enableGlobalIntr(esmBase);

            if (sdlRet == SDL_PASS)
            {
                sdlRet = SDL_ESM_getGlobalIntrEnabledStatus(esmBase, &intStatus);
            }
            if (sdlRet == SDL_PASS)
            {
                if (intStatus != SDL_ESM_EN_KEY_ENABLE)
                {
                    sdlRet = SDL_EFAIL;
                }
            }
            if (sdlRet != SDL_PASS)
            {
                retVal = SDL_EFAIL;
            }
        }
        else
        {
            retVal = SDL_EFAIL;
        }
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return (retVal);
}

/**
 * Design: C2000DL-809
 */
int32_t SDL_ESM_init(const uint32_t esmBase, const SDL_ESM_Config *pConfig)
{
    int32_t result = SDL_PASS;
    int32_t sdlRet = SDL_PASS;
    uint32_t intNum;
    uint32_t groupIndex, bitIndex;
    uint32_t intStatus;
    SDL_ESM_IntrType intrPriorityLvlWr, intrPriorityLvlRd;
    bool enableWr, enableRd;
    uint32_t influence;
    SDL_ESM_Instance_t *SDL_ESM_instance;

    /* Check for valid pConfig and ESM register base address then get the corresponding
       SDM_ESM_instance for SW instance structure. */
    if ((SDL_ESM_isBaseValid(esmBase) == false) || (pConfig == NULL))
    {
        result = SDL_EBADARGS;
    }
    else
    {
        SDL_ESM_selectESMInst(esmBase, &SDL_ESM_instance);

        /* Record init config in instance */
        for (groupIndex = 0U; groupIndex < SDL_ESM_NUM_EVENT_GROUPS; groupIndex++)
        {
            SDL_ESM_instance->esmInitConfig.enableBitmap[groupIndex]   = pConfig->enableBitmap[groupIndex];
            SDL_ESM_instance->esmInitConfig.priorityBitmap[groupIndex] = pConfig->priorityBitmap[groupIndex];
            SDL_ESM_instance->esmInitConfig.errorPinBitmap[groupIndex] = pConfig->errorPinBitmap[groupIndex];
        }

        SDL_ESM_instance->selfTestCallback = &SDL_ESM_defaultCallback;
        SDL_ESM_instance->selfTestStatus = SDL_ESM_NO_EVENT_VALUE;

        /* Enable interrupt for all events from init configuration*/
        for (groupIndex = 0U; groupIndex <= (SDL_ESM_MAX_NUM_EVENTS/SDL_ESM_EVENTS_PER_GROUP); groupIndex++)
        {
            uint32_t remainingBits = SDL_ESM_MAX_NUM_EVENTS - (groupIndex * SDL_ESM_EVENTS_PER_GROUP);

            if (remainingBits > SDL_ESM_EVENTS_PER_GROUP)
            {
                remainingBits = SDL_ESM_EVENTS_PER_GROUP;
            }

            for (bitIndex = 0U; bitIndex < remainingBits; bitIndex++)
            {
                intNum = (groupIndex * SDL_ESM_EVENTS_PER_GROUP) + bitIndex;

                /* Clear interrupt status, so that we start with clean state */
                (void)SDL_ESM_clearIntrStatus(esmBase, intNum);

                (void)SDL_ESM_getIntrStatus(esmBase, intNum, &intStatus);


                /* Depending on the bitmap configuration enable interrupt and set priority level */
                if (((pConfig->enableBitmap[groupIndex]) & (SDL_ESM_MASK_BIT << bitIndex)) != 0U)
                {
                    /* Enable interrupt and verify if interrupt status is enabled */
                    (void)SDL_ESM_enableIntr(esmBase, intNum);

                    sdlRet = SDL_ESM_isEnableIntr(esmBase, intNum, &intStatus);

                    if (intStatus != SDL_ESM_INTRSTATUS_EN)
                    {
                        sdlRet = SDL_EFAIL;
                    }

                    /* Set interrupt priority level and verify if priority level is set */
                    if (sdlRet == SDL_PASS)
                    {
                        intrPriorityLvlWr = ((pConfig->priorityBitmap[groupIndex]
                                            & (SDL_ESM_MASK_BIT << bitIndex)) != 0U)?1U:0U;
                        sdlRet = SDL_ESM_setIntrPriorityLvl(esmBase,
                                                            intNum,
                                                            intrPriorityLvlWr);
                    }
                    if (sdlRet == SDL_PASS)
                    {
                        sdlRet = SDL_ESM_getIntrPriorityLvl(esmBase,
                                                            intNum,
                                                            &intrPriorityLvlRd);
                    }
                    if (sdlRet == SDL_PASS)
                    {
                        if (intrPriorityLvlWr != intrPriorityLvlRd)
                        {
                            sdlRet = SDL_EFAIL;
                        }
                    }

                    /*
                     * Depending on the bitmap configuration set error output
                     * and verify if error output is set */
                    if ((sdlRet == SDL_PASS) && (esmBase == SDL_ESMSYSTEM_BASE))
                    {
                        enableWr = ((pConfig->errorPinBitmap[groupIndex]
                                     & (SDL_ESM_MASK_BIT << bitIndex)) != 0U)? true : false;
                        sdlRet = SDL_ESM_setInfluenceOnErrPin(esmBase,
                                                              intNum,
                                                              enableWr);

                        if (sdlRet == SDL_PASS)
                        {
                            sdlRet = SDL_ESM_getInfluenceOnErrPin(esmBase,
                                                                  intNum,
                                                                  &influence);
                            if (sdlRet == SDL_PASS)
                            {
                                enableRd = (influence != 0U)? true : false;
                                if (enableWr != enableRd)
                                {
                                    sdlRet = SDL_EFAIL;
                                }
                            }
                        }
                    }
                }

                if (sdlRet != SDL_PASS)
                {
                    break;
                }
            }
        }

        /* Enable Global interrupt and verify if global interrupt is enabled for ESM */
        if (sdlRet == SDL_PASS)
        {
            if (SDL_ESM_enableGlobalIntr(esmBase) == SDL_PASS)
            {
                if (SDL_ESM_getGlobalIntrEnabledStatus(esmBase, &intStatus) == SDL_PASS)
                {
                    if (intStatus != SDL_ESM_EN_KEY_ENABLE)
                    {
                        sdlRet = SDL_EFAIL;
                    }
                }
            }
        }
        if (sdlRet != SDL_PASS)
        {
            result = SDL_EFAIL;
        }
    }

    return result;
}
