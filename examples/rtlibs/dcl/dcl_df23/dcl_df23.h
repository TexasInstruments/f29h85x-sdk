//#############################################################################
//
//
// $Copyright:
//#############################################################################

#ifndef DF23_TEST_H
#define DF23_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "board.h"
#include "dcl.h"

//
//  User configurable values
//
#define DF23_TESTCASE   1     //!< Defines testcase, tests 1-3 is provided   
#define DATA_LENGTH     1601  //!< Size of total data inputs
#define NUM_ELEMENTS    1000   //!< The number of samples ran, cannot exceed DATA_LENGTH

#if NUM_ELEMENTS > DATA_LENGTH
#error "Sample size must be smaller than the size of the data"
#endif

int DF23_runTest(DCL_DF23 *ctrl_handle);

//
//  Controller initialization
// 
DCL_DF23 *df23_controller = &(DCL_DF23)
{
    .a1 = 0.0341879720f,
    .a2 = -0.7668017816f,
    .a3 = -0.2673861903f,
    .b0 = 1.3436620732f,
    .b1 = 0.3459370813f,
    .b2 = -0.7200660800f,
    .b3 = -0.2790608258f,
    DF23_INT_DEFAULTS  // macro for default values of internal attributes
};

//
//  Macros for selecting testvector based on DF23_TESTCASE 
//
#define _LSTR(x) #x
#define __LSTR(x) _LSTR(x)
#define DF23_IN_DATA(x)  __LSTR(data/DF23_in-x.dat) 
#define DF23_CTL_DATA(x) __LSTR(data/DF23_ctl-x.dat) 

//
// Allocate data sections and initialize test vector
//
const float32_t __attribute__((weak)) in_buffer[DATA_LENGTH] =
{
#include DF23_IN_DATA(DF23_TESTCASE)
};

const float32_t __attribute__((weak)) ctl_buffer[DATA_LENGTH] =
{
#include DF23_CTL_DATA(DF23_TESTCASE)
};

static float32_t out_buffer[DATA_LENGTH];

#ifdef __cplusplus
}
#endif // extern "C"

#endif
