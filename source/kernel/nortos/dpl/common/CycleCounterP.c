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


#include <kernel/dpl/CycleCounterP.h>
#include "driverlib.h"

uint64_t g_cycleCounterSeed = 0ULL;
uint32_t g_cycleCounterCpuFreqHz;

void CycleCounterP_init(const uint64_t cpuFreqHz)
{
    g_cycleCounterCpuFreqHz = cpuFreqHz;
    g_cycleCounterSeed      = IPC_getCounter();
}

uint32_t CycleCounterP_getCount32(void)
{
    return ((uint32_t)((IPC_getCounter() - g_cycleCounterSeed) & 0xFFFFFFFFU));
}

void CycleCounterP_reset(void)
{
    g_cycleCounterSeed = IPC_getCounter();
}

uint64_t CycleCounterP_getCount64(void)
{
    return (IPC_getCounter() - g_cycleCounterSeed);
}

uint64_t CycleCounterP_nsToTicks(const uint64_t nanosecs)
{
    return ((nanosecs * (g_cycleCounterCpuFreqHz/1000000U))/1000U);
}





