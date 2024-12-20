/*
 *  Copyright (C) 2018-2023 Texas Instruments Incorporated
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

#include <kernel/dpl/TimerP.h>
#include "driverlib.h"

#define ONE_MHZ             (1000000U)
#define ONE_KHZ             (1000U)

void TimerP_Params_init(TimerP_Params *params)
{
    params->inputPreScaler      = 1U;
    params->inputClkHz          = 200U * ONE_MHZ;
    params->periodInUsec        = 1000U;
    params->periodInNsec        = 0U;
    params->oneshotMode         = 0U;
    params->enableOverflowInt   = 1U;
    params->enableDmaTrigger    = 0U;
}

void TimerP_setup(uint32_t baseAddr, TimerP_Params *params)
{
    uint32_t period;

    /* Parameter validation */
    DebugP_assert(0U != baseAddr);
    DebugP_assert(0U != params->inputPreScaler);
    DebugP_assert(5U >= params->inputPreScaler);
    DebugP_assert(0U != params->inputClkHz);
    DebugP_assert((0U != params->periodInUsec) || (0U != params->periodInNsec));
    DebugP_assert(0U == (params->inputClkHz % params->inputPreScaler));

    /* Stop timer */
    CPUTimer_stopTimer(baseAddr);

    /* Set the prescale */
    CPUTimer_setPreScaler(baseAddr, (uint16_t)((params->inputPreScaler - 1U) & 0xFFFFU));

    /* Set the timer period */
    if(0U != params->periodInNsec)
    {
        /* Period is in nsec */
        period = ((params->periodInNsec * (params->inputClkHz/ONE_MHZ))/ONE_KHZ)/params->inputPreScaler;
    }
    else
    {
        /* Period is in usec */
        period = (params->periodInUsec * (params->inputClkHz/ONE_MHZ))/params->inputPreScaler;
    }
    CPUTimer_setPeriod(baseAddr, period);

    /* Reload counters */
    CPUTimer_reloadTimerCounter(baseAddr);

    /* Set emulation mode */
    CPUTimer_setEmulationMode(baseAddr, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);

    /* Enable/disble interrupt */
    if(1U == params->enableOverflowInt)
    {
        CPUTimer_enableInterrupt(baseAddr);
    }
    else
    {
        CPUTimer_disableInterrupt(baseAddr);
    }
}

void TimerP_start(uint32_t baseAddr)
{
    CPUTimer_startTimer(baseAddr);
}

void TimerP_stop(uint32_t baseAddr)
{
    CPUTimer_stopTimer(baseAddr);
}

uint32_t TimerP_getCount(uint32_t baseAddr)
{
    //
    //  Current timer count = (Max 32 bit count - current down count)
    //
    return (MAX_TIMER_COUNT_VALUE - CPUTimer_getTimerCount(baseAddr));
}

uint32_t TimerP_getReloadCount(uint32_t baseAddr)
{
    //
    //  Reload timer count = (Max 32 bit count - reload count)
    //
    return (MAX_TIMER_COUNT_VALUE - HWREG(baseAddr + CPUTIMER_O_PRD));
}

void TimerP_clearOverflowInt(uint32_t baseAddr)
{
    CPUTimer_clearOverflowFlag(baseAddr);
}

uint32_t TimerP_isOverflowed(uint32_t baseAddr)
{
    return ((uint32_t)CPUTimer_getTimerOverflowStatus(baseAddr));
}
