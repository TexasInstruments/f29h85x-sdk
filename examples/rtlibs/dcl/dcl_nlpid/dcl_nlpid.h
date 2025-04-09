//#############################################################################
//
//
// $Copyright:
//#############################################################################
 
#ifndef NLPID_TEST_H
#define NLPID_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "board.h"
#include "dcl.h"

//
//  User configurable values
//
#define NLPID_TESTCASE     1   //!< Defines testcase        
#define DATA_LENGTH     1601   //!< Size of total data inputs
#define NUM_ELEMENTS    1000   //!< The number of samples ran, cannot exceed DATA_LENGTH

#if NUM_ELEMENTS > DATA_LENGTH
#error "Sample size must be smaller than the size of the data"
#endif

int NLPID_runTest(DCL_NLPID *nlpid_ptr);
bool NLPID_updateParams(DCL_NLPID *nlpid_ptr);

//
//  Controller initialization
// 
DCL_NLPID *nlpid_controller = &(DCL_NLPID) NLPID_DEFAULTS;

//
//  Macros for selecting testvector based on NLPID_TESTCASE 
//
#define _LSTR(x) #x
#define __LSTR(x) _LSTR(x)
#define NLPID_RK_DATA(x)  __LSTR(data/NLPID_rk-x.dat) 
#define NLPID_YK_DATA(x)  __LSTR(data/NLPID_yk-x.dat) 
#define NLPID_LK_DATA(x)  __LSTR(data/NLPID_lk-x.dat) 
#define NLPID_CTL_DATA(x) __LSTR(data/NLPID_ctl-x.dat) 

//
// Allocate data sections and initialize data
//
const float32_t __attribute__((weak)) rk_buffer[DATA_LENGTH] =
{
#include NLPID_RK_DATA(NLPID_TESTCASE)
};

const float32_t __attribute__((weak)) yk_buffer[DATA_LENGTH] =
{
#include NLPID_YK_DATA(NLPID_TESTCASE)
};

const float32_t __attribute__((weak)) lk_buffer[DATA_LENGTH] =
{
#include NLPID_LK_DATA(NLPID_TESTCASE)
};

const float32_t __attribute__((weak)) ctl_buffer[DATA_LENGTH] =
{
#include NLPID_CTL_DATA(NLPID_TESTCASE)
};

static float32_t out_buffer[DATA_LENGTH];

#ifdef __cplusplus
}
#endif // extern "C"

#endif
