//#############################################################################
//
//   FILE:  dpl.h
//
//   TITLE:
//
//#############################################################################
//  //
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

//#############################################################################

#ifndef DPL_H
#define DPL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include "kernel/dpl/ClockP.h"
#include "kernel/dpl/CpuIdP.h"
#include "kernel/dpl/DebugP.h"
#include "kernel/dpl/HwiP.h"
#include "kernel/dpl/SemaphoreP.h"
#include "kernel/dpl/TimerP.h"
#include "kernel/nortos/dpl/c29/HwiP_c29_pipe.h"
#include "kernel/nortos/dpl/common/printf.h"

//
// This setup is done by SysConfig for AM263
// TODO: only CCS logging has been tested
//
#define DPL_ENABLE_CCS_LOG 1

//
// Todo: These are defined in Semaphore_nortos.c but not defined in the header file?
//
/**
 * \brief Semaphore type
 */
typedef enum SemaphoreP_Type_ {
    SemaphoreP_TYPE_BINARY, /**< Binary semaphore */
    SemaphoreP_TYPE_COUNTING, /**< Counting semaphore */
    SemaphoreP_TYPE_MUTEX /**< Mutual exclusion semaphore */
} SemaphoreP_Type;

/**
 * \brief Parameters passed during \ref SemaphoreP_construct
 */
typedef struct SemaphoreP_Params_ {

    uint32_t type; /**< see \ref SemaphoreP_Type */
    uint32_t initCount; /**< initial value of the semaphore. \n
        Only valid for \ref SemaphoreP_TYPE_COUNTING and \ref SemaphoreP_TYPE_BINARY. \n
        MUST be 0 or 1 for \ref SemaphoreP_TYPE_BINARY \n
        Ignored for \ref SemaphoreP_TYPE_MUTEX */
    uint32_t maxCount; /**< max value the semaphore can take. \n
        Only valid for \ref SemaphoreP_TYPE_COUNTING. \n
        MUST be >= SemaphoreP_Params.initCount \n
        Ignored for \ref SemaphoreP_TYPE_MUTEX and \ref SemaphoreP_TYPE_BINARY
        */

} SemaphoreP_Params;

typedef struct SemaphoreP_Struct_ {
    uint32_t type;
    uint32_t maxCount;
    volatile uint32_t count;
    volatile uint32_t nestCount;
} SemaphoreP_Struct;

extern void SemaphoreP_Params_init(SemaphoreP_Params *params);
extern int32_t SemaphoreP_construct(SemaphoreP_Object *obj,SemaphoreP_Params *params);

//
//
//
void testCheck(const uint32_t testVariable, const char *testComparison, const uint32_t expectedValue, const char *testMessage)
{
#if (QUIET != 1)
    if(0 == strcmp(testComparison,"=="))
    {
        if(testVariable == expectedValue ) DebugP_log("  - %s: test passed \r\n", testMessage);
        else DebugP_logError("   - test failed! \r\n");
        DebugP_assert(testVariable == expectedValue);
    }
    else if(0 == strcmp(testComparison,"<"))
    {
        if(testVariable < expectedValue ) DebugP_log("  - %s: test passed \r\n", testMessage);
        else DebugP_logError("   - test failed! \r\n");
        DebugP_assert(testVariable < expectedValue);
    }
    else if(0 == strcmp(testComparison,">"))
    {
        if(testVariable > expectedValue ) DebugP_log("  - %s: test passed \r\n", testMessage);
        else DebugP_logError("   - test failed! \r\n");
        DebugP_assert(testVariable > expectedValue);
    }
    else
    {
        DebugP_assert(0);
    }
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* DPL_H */
