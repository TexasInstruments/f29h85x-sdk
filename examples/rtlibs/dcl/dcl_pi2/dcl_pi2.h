//#############################################################################
//
//
// $Copyright:
//#############################################################################
 
#ifndef PI2_TEST_H
#define PI2_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "board.h"
#include "dcl.h"

//
//  User configurable values
//
#define PI2_TESTCASE     1     //!< Defines testcase, tests 1-3 is provided            
#define DATA_LENGTH     1601   //!< Size of total data inputs
#define NUM_ELEMENTS    1000   //!< The number of samples ran, cannot exceed DATA_LENGTH

#if NUM_ELEMENTS > DATA_LENGTH
#error "Sample size must be smaller than the size of the data"
#endif

typedef float32_t (*DCL_PI_FUNC)(DCL_PI *p, float32_t rk, float32_t yk);
int PI2_runTest(DCL_PI2 *ctrl_handle);


//
//  Controller initialization
// 
DCL_PI2 *pi2_controller = &(DCL_PI2)
{
    .Kp  = 0.6753591151f,
    .Ki  = 0.1915683544f,
    .Umax = 100.00000f,
    .Umin = -100.00000f,
    PI2_INT_DEFAULTS // macro for default values of internal attributes
};

//
//  Macros for selecting testvector based on PI2_TESTCASE 
//
#define _LSTR(x) #x
#define __LSTR(x) _LSTR(x)
#define PI2_RK_DATA(x)  __LSTR(data/PI2_rk-x.dat) 
#define PI2_YK_DATA(x)  __LSTR(data/PI2_yk-x.dat) 
#define PI2_CTL_DATA(x) __LSTR(data/PI2_ctl-x.dat) 

//
// Allocate data sections and initialize data
//
const float32_t __attribute__((weak)) rk_buffer[DATA_LENGTH] =
{
#include PI2_RK_DATA(PI2_TESTCASE)
};

const float32_t __attribute__((weak)) yk_buffer[DATA_LENGTH] =
{
#include PI2_YK_DATA(PI2_TESTCASE)
};

const float32_t __attribute__((weak)) ctl_buffer[DATA_LENGTH] =
{
#include PI2_CTL_DATA(PI2_TESTCASE)
};

static float32_t out_buffer[DATA_LENGTH];

#ifdef __cplusplus
}
#endif // extern "C"

#endif
