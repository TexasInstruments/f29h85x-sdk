////###########################################################################
////
//// FILE:   ex3_cpubrom_utils.c
////
//// TITLE:  Common Macros Used and Helper APIs
////
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//###########################################################################

#include <ex3_cpubrom_utils.h>

//
//  CPU_BROM_getCycleCount
//
uint64_t CPU_BROM_getCycleCount(void)
{
    volatile uint32_t ipcCounterL;
    volatile uint32_t ipcCounterH;
    //
    //  Always read IPCCOUNTERL followed by IPCCOUNTERH register
    //  ->  IPCCOUNTER register provides free running pll sysclk count
    //
    ipcCounterL = HWREG(IPCCOUNTER_BASE + IPC_O_COUNTERL);
    ipcCounterH = HWREG(IPCCOUNTER_BASE + IPC_O_COUNTERH);

    return ((((uint64_t)ipcCounterH << 32U) | ipcCounterL));
}

//
/**
*Function to insert delay based on cycles.
*
*Arguments:
*@param cycles                : Number of cycles .
*
* Design: \ref did_delay_algo
*
*/
void CPU_BROM_delay_cycles(uint32_t cycles)
{
    uint64_t startCnt;
    uint32_t cnt;
    //
    //  Wait for required cycles
    //
    startCnt = CPU_BROM_getCycleCount();
    for(cnt = 0U;cnt < cycles;cnt++)
    {
        if((CPU_BROM_getCycleCount() - startCnt) >= (uint64_t)cycles)
        {
            break;
        }
    }
}

//
//  CPU_BROM_memset
//
void CPU_BROM_memset(uint8_t *address, uint8_t val, uint32_t size)
{
    uint32_t cnt;

    for(cnt = 0U;cnt < size;cnt++)
    {
        address[cnt] = val;
    }
}

//
//  CPU_BROM_memcpy
//
void CPU_BROM_memcpy(uint8_t *dst, uint8_t *src, uint32_t size)
{
    uint32_t cnt;

    for(cnt = 0U;cnt < size;cnt++)
    {
        if(dst > src)
        {
            //
            //  Copy in reverse order
            //
            dst[(size - 1U) - cnt] = src[(size - 1U) - cnt];
        }
        else
        {
            dst[cnt] = src[cnt];
        }
    }
}
