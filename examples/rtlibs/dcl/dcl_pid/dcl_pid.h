//#############################################################################
//
//
// $Copyright:
//#############################################################################
 
#ifndef PID_TEST_H
#define PID_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "board.h"
#include "dcl.h"

//
//  User configurable values
//
#define PID_TESTCASE     1    //!< Defines testcase, tests 1-3 is provided               
#define DATA_LENGTH     1601  //!< Size of total data inputs
#define NUM_ELEMENTS    800   //!< The number of samples ran, cannot exceed DATA_LENGTH

#if NUM_ELEMENTS > DATA_LENGTH
#error "Sample size must be smaller than the size of the data"
#endif

typedef float32_t (*DCL_PID_FUNC)(DCL_PID *p, float32_t rk, float32_t yk, float32_t lk);
int PID_runTest(DCL_PID *ctrl_handle, DCL_PID_FUNC dcl_pid_func);
bool PID_updateParams(DCL_PID *pid_ptr, uint32_t testCase);

//
//  Controller initialization
// 
DCL_PID *pid_controller = &(DCL_PID) PID_DEFAULTS;

//
//  Macros for selecting testvector based on PID_TESTCASE 
//
#define _LSTR(x) #x
#define __LSTR(x) _LSTR(x)
#define PID_RK_DATA(x)  __LSTR(data/PID_rk-x.dat) 
#define PID_YK_DATA(x)  __LSTR(data/PID_yk-x.dat) 
#define PID_LK_DATA(x)  __LSTR(data/PID_lk-x.dat) 
#define PID_CTL_DATA(x) __LSTR(data/PID_ctl-x.dat) 

//
// Allocate data sections and initialize data
//
const float32_t __attribute__((weak)) rk_buffer[DATA_LENGTH] =
{
#include PID_RK_DATA(PID_TESTCASE)
};

const float32_t __attribute__((weak)) yk_buffer[DATA_LENGTH] =
{
#include PID_YK_DATA(PID_TESTCASE)
};

const float32_t __attribute__((weak)) lk_buffer[DATA_LENGTH] =
{
#include PID_LK_DATA(PID_TESTCASE)
};

const float32_t __attribute__((weak)) ctl_buffer[DATA_LENGTH] =
{
#include PID_CTL_DATA(PID_TESTCASE)
};

static float32_t out_buffer[DATA_LENGTH];

#ifdef __cplusplus
}
#endif // extern "C"

#endif
