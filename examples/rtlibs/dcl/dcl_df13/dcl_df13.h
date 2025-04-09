//#############################################################################
//
//
// $Copyright:
//#############################################################################

#ifndef DF13_TEST_H
#define DF13_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "board.h"
#include "dcl.h"

//
//  User configurable values
//
#define DF13_TESTCASE   1     //!< Defines testcase, tests 1-3 is provided   
#define DATA_LENGTH     1601  //!< Size of total data inputs
#define NUM_ELEMENTS    1000   //!< The number of samples ran, cannot exceed DATA_LENGTH

#if NUM_ELEMENTS > DATA_LENGTH
#error "Sample size must be smaller than the size of the data"
#endif

int DF13_runTest(DCL_DF13 *ctrl_handle);

//
//  Controller initialization
// 
DCL_DF13 *df13_controller = &(DCL_DF13)
{
    .a1 = -1.0277396009f,
    .a2 = 0.8277396009f,
    .a3 = -0.24802563f,
    .b0 = 1.2500036172f,
    .b1 = 0.2153188876f,
    .b2 = -2.0346715071f,
    .b3 = -0.2490805258f,
    DF13_INT_DEFAULTS  // macro for default values of internal attributes
};

//
//  Macros for selecting testvector based on DF13_TESTCASE 
//
#define _LSTR(x) #x
#define __LSTR(x) _LSTR(x)
#define DF13_IN_DATA(x)  __LSTR(data/DF13_in-x.dat) 
#define DF13_CTL_DATA(x) __LSTR(data/DF13_ctl-x.dat) 

//
// Allocate data sections and initialize test vector
//
const float32_t __attribute__((weak)) in_buffer[DATA_LENGTH] =
{
#include DF13_IN_DATA(DF13_TESTCASE)
};

const float32_t __attribute__((weak)) ctl_buffer[DATA_LENGTH] =
{
#include DF13_CTL_DATA(DF13_TESTCASE)
};

static float32_t out_buffer[DATA_LENGTH];

#ifdef __cplusplus
}
#endif // extern "C"

#endif
