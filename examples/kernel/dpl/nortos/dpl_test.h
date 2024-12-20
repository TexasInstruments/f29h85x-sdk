//#############################################################################
//
//   FILE:  dpl.h
//
//   TITLE:
//
//#############################################################################
//  $ Copyright: $
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
