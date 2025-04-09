//#############################################################################
//
//
// $Copyright:
//#############################################################################
 
#ifndef PI_TEST_H
#define PI_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "board.h"
#include "dcl.h"

//
//  User configurable values
//
#define PI_TESTCASE     1     //!< Defines testcase, tests 1-3 is provided            
#define DATA_LENGTH     1601  //!< Size of total data inputs
#define NUM_ELEMENTS    400   //!< The number of samples ran, cannot exceed DATA_LENGTH

#if NUM_ELEMENTS > DATA_LENGTH
#error "Sample size must be smaller than the size of the data"
#endif

typedef float32_t (*DCL_PI_FUNC)(DCL_PI *p, float32_t rk, float32_t yk);
int PI_runTest(DCL_PI *ctrl_handle, DCL_PI_FUNC dcl_pi_func);


//
//  Controller initialization
// 
//! Method 1: 
//! Direct assignments
//!
DCL_PI *pi_controller = &(DCL_PI)
{
    .Kp  = 2.5f,
    .Ki  = 0.01f,
    .Umax = 2.0f,
    .Umin = -2.0f,
    .Imax = 1.0f,
    .Imin = -1.0f,
    PI_INT_DEFAULTS // macro for default values of internal attributes
};

//
//  Macros for selecting testvector based on PI_TESTCASE 
//
#define _LSTR(x) #x
#define __LSTR(x) _LSTR(x)
#define PI_RK_DATA(x)  __LSTR(data/PI_rk-x.dat) 
#define PI_YK_DATA(x)  __LSTR(data/PI_yk-x.dat) 
#define PI_CTL_DATA(x) __LSTR(data/PI_ctl-x.dat) 

//
// Allocate data sections and initialize data
//
const float32_t __attribute__((weak)) rk_buffer[DATA_LENGTH] =
{
#include PI_RK_DATA(PI_TESTCASE)
};

const float32_t __attribute__((weak)) yk_buffer[DATA_LENGTH] =
{
#include PI_YK_DATA(PI_TESTCASE)
};

const float32_t __attribute__((weak)) ctl_buffer[DATA_LENGTH] =
{
#include PI_CTL_DATA(PI_TESTCASE)
};

static float32_t out_buffer[DATA_LENGTH];

#ifdef __cplusplus
}
#endif // extern "C"

#endif
