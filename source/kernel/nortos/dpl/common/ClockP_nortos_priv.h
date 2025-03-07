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

#ifndef CLOCKP_NORTOS_H
#define CLOCKP_NORTOS_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TimerP.h>

#if !defined(__C29__)
#include "kernel/am263_compatibility/csl_types.h"
#endif

#if defined(__C29__)
//
// Added to pickup the inline function HwiP_disable
//
#include "kernel/nortos/dpl/c29/HwiP_c29_pipe.h"
#endif

typedef struct ClockP_Struct_
{
    ClockP_FxnCallback callback;
    void *args;
    uint32_t startTimeout;  /* timeout passed to ClockP_construct() */
    uint32_t timeout;
    uint32_t period;
    struct ClockP_Struct_ *next;
} ClockP_Struct;

typedef struct ClockP_Control_
{
    uint64_t ticks;
    ClockP_Struct *list;
    uint32_t usecPerTick;
    HwiP_Object timerHwiObj;
    uint32_t timerBaseAddr;
    uint32_t timerReloadCount;
} ClockP_Control;

extern ClockP_Control gClockCtrl;
extern ClockP_Config gClockConfig;

void ClockP_timerClearOverflowInt(uint32_t timerBaseAddr);
uint32_t ClockP_getTimerCount(uint32_t timerBaseAddr);
void ClockP_timerTickIsr(void *args);


#ifdef __cplusplus
}
#endif

#endif /* CLOCKP_NORTOS_H */
