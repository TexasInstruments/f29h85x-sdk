//#############################################################################
//
//
// $Copyright:
//#############################################################################

#ifndef DF22_TEST_H
#define DF22_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "board.h"
#include "dcl.h"

//
//  User configurable values
//
#define DF22_TESTCASE   1     //!< Defines testcase, tests 1-3 is provided   
#define DATA_LENGTH     1601  //!< Size of total data inputs
#define NUM_ELEMENTS    1000   //!< The number of samples ran, cannot exceed DATA_LENGTH

#if NUM_ELEMENTS > DATA_LENGTH
#error "Sample size must be smaller than the size of the data"
#endif

int DF22_runTest(DCL_DF22 *ctrl_handle);

//
//  Controller initialization
// 
DCL_DF22 *df22_controller = &(DCL_DF22)
{
    .b0 = 9.8549f,
    .b1 = -19.4165f,
    .b2 = 9.5636f,
    .a1 = -1.9417f,
    .a2 = 0.9417f,
    DF22_INT_DEFAULTS  // macro for default values of internal attributes
};

//
//  Macros for selecting testvector based on DF22_TESTCASE 
//
#define _LSTR(x) #x
#define __LSTR(x) _LSTR(x)
#define DF22_IN_DATA(x)  __LSTR(data/DF22_in-x.dat) 
#define DF22_CTL_DATA(x) __LSTR(data/DF22_ctl-x.dat) 

//
// Allocate data sections and initialize test vector
//
const float32_t __attribute__((weak)) in_buffer[DATA_LENGTH] =
{
#include DF22_IN_DATA(DF22_TESTCASE)
};

const float32_t __attribute__((weak)) ctl_buffer[DATA_LENGTH] =
{
#include DF22_CTL_DATA(DF22_TESTCASE)
};

static float32_t out_buffer[DATA_LENGTH];

#ifdef __cplusplus
}
#endif // extern "C"

#endif
