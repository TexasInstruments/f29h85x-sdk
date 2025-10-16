/*
 * SDL ESM
 *
 * Software Diagnostics Reference module for Error Signaling Module
 *
 *  Copyright (c) Texas Instruments Incorporated 2025
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
 *  \file     sdl_esm_priv.c
 *
 *  \brief    This file contains the private ESM APIs.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sdlr_esm.h"
#include "sdl_esm_priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Register information for the ERAD Counter 3 STATUSCLEAR register needed for
 * processing back-to-back CPU fault errata workaround  */
#define SDL_ERAD_STATUSCLEAR_CNTR3          (0x50CU)
#define SDL_ERAD_STATUSCLEAR_EVENT_FIRED    (1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * Design: C2000DL-791
 */

static SDL_ESM_Instance_t SDL_ESM_CPU_instance;
static SDL_ESM_Instance_t SDL_ESM_SYSTEM_instance;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void SDL_ESM_processInterruptSource(uint32_t esmBase, uint32_t intSrc);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *
 * \brief   Process Interrupt source and call callback function
 *
 * \return  None
 */
static void SDL_ESM_processInterruptSource(uint32_t esmBase,
                                           uint32_t intSrc)
{
    SDL_ESM_Instance_t *SDL_ESM_instance = &SDL_ESM_CPU_instance;
    uint32_t groupNumber, bitIndex;

    if (intSrc != SDL_ESM_NO_EVENT_VALUE)
    {
        if (intSrc < (SDL_ESM_EVENTS_PER_GROUP * SDL_ESM_NUM_EVENT_GROUPS))
        {
            /* Check if this is due to self test */
            if (SDL_ESM_instance->selfTestStatus == SDL_ESM_SELF_TEST_ACTIVE)
            {
                SDL_ESM_instance->selfTestCallback(esmBase, intSrc,
                                                   SDL_ESM_instance->callbackArg);

                /* Set self-test to inactive */
                SDL_ESM_setSelfTestStatus(SDL_ESM_SELF_TEST_NONE);
            }

            (void)SDL_ESM_clearIntrStatus(esmBase, intSrc);
        }
    }

    return;
}

void SDL_ESM_clearNMIFetchErrataWorkaround(uint32_t esmBase)
{
    SDL_ESM_IntrStatus eventStatus;

    /* Get the group 0 high priority event that was the origin */
    (void)SDL_ESM_getGroupIntrStatus(SDL_ESMSYSTEM_BASE,
                                     SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR,
                                     &eventStatus);

    /* Clear original event and workaround related flags */
    (void)SDL_ESM_clearIntrStatus(SDL_ESMSYSTEM_BASE, eventStatus.highestPendPulseEvent);
    (void)SDL_ESM_clearIntrStatus(SDL_ESMSYSTEM_BASE, SDL_ESM_EVENT_CPU1_ERAD_NMI);
    (void)SDL_ESM_clearIntrStatus(SDL_ESMSYSTEM_BASE, SDL_ESM_EVENT_EPWMXBAR1);

    (void)SDL_ESM_clearIntrStatus(esmBase, eventStatus.highestPendPulseEvent);
    (void)SDL_ESM_clearIntrStatus(esmBase, SDL_ESM_EVENT_EPWMXBAR1);

    /* Clear ERAD counter event flag */
    HW_WR_REG8(SDL_ERAD_BASE + SDL_ERAD_STATUSCLEAR_CNTR3, SDL_ERAD_STATUSCLEAR_EVENT_FIRED);

    (void)SDL_ESM_writeEOI(SDL_ESMSYSTEM_BASE, SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR);
}

/*
 * Design: C2000DL-790
 */
void SDL_ESM_interruptHandler(uint32_t esmBase,
                              SDL_ESM_IntrType esmIntrPriorityLvlType,
                              SDL_ESM_IntrStatus *intrStatus)
{
    SDL_ESM_IntrStatus nextIntrStatus;

    /* Check the next pending event if there is one */
    (void)SDL_ESM_getGroupIntrStatus(esmBase, esmIntrPriorityLvlType,
                                     intrStatus);

    /* Handle the interrupt */
    SDL_ESM_processInterruptSource(esmBase, intrStatus->highestPendPulseEvent);
    SDL_ESM_processInterruptSource(esmBase, intrStatus->highestPendLevelEvent);

    /* Check the next pending event if there is one */
    (void)SDL_ESM_getGroupIntrStatus(esmBase, esmIntrPriorityLvlType,
                                     &nextIntrStatus);

    intrStatus->nextPendLevelEvent = nextIntrStatus.highestPendLevelEvent;
    intrStatus->nextPendPulseEvent = nextIntrStatus.highestPendPulseEvent;

    return;
}

bool SDL_ESM_selectESMInst(const uint32_t esmBase,
                           SDL_ESM_Instance_t **pEsmInstancePtr)
{
    bool instValid = true;
    uint32_t maskedBase;

    maskedBase = esmBase & SDL_BASE_ADDR_MASK;

    switch(maskedBase)
    {
        case SDL_ESMCPU1_BASE_FRAME(0U):
            *pEsmInstancePtr = (SDL_ESM_Instance_t *)(&SDL_ESM_CPU_instance);
            break;

        case SDL_ESMCPU2_BASE_FRAME(0U):
            *pEsmInstancePtr = (SDL_ESM_Instance_t *)(&SDL_ESM_CPU_instance);
            break;

        case SDL_ESMCPU3_BASE_FRAME(0U):
            *pEsmInstancePtr = (SDL_ESM_Instance_t *)(&SDL_ESM_CPU_instance);
            break;

        case SDL_ESMSYSTEM_BASE_FRAME(0U):
            *pEsmInstancePtr = (SDL_ESM_Instance_t *)(&SDL_ESM_SYSTEM_instance);
            break;

        default:
            /* Invalid instance input parameter */
            instValid = false;
            break;
    }

    return instValid;
}
