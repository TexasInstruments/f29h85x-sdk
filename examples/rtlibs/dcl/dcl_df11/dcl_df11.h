//#############################################################################
//
//
// $Copyright:
//#############################################################################

#ifndef DF11_TEST_H
#define DF11_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "board.h"
#include "ti_dpl_config.h"
#include "dcl.h"

//
//  User configurable values
//
#define DF11_TESTCASE   1     //!< Defines testcase, tests 1-3 is provided   
#define DATA_LENGTH     1601  //!< Size of total data inputs
#define NUM_ELEMENTS    1000   //!< The number of samples ran, cannot exceed DATA_LENGTH

#if NUM_ELEMENTS > DATA_LENGTH
#error "Sample size must be smaller than the size of the data"
#endif

int DF11_runTest(DCL_DF11 *ctrl_handle);

//
//  Controller initialization
// 
DCL_DF11 *df11_controller = &(DCL_DF11)
{
    .a1 = -0.5170939860f,
    .b0 = 1.3436620732f,
    .b1 = -0.3488624959f,
    DF11_INT_DEFAULTS  // macro for default values of internal attributes
};

//
//  Macros for selecting testvector based on DF11_TESTCASE 
//
#define _LSTR(x) #x
#define __LSTR(x) _LSTR(x)
#define DF11_IN_DATA(x)  __LSTR(data/DF11_in-x.dat) 
#define DF11_CTL_DATA(x) __LSTR(data/DF11_ctl-x.dat) 

//
// Allocate data sections and initialize test vector
//
const float32_t __attribute__((weak)) in_buffer[DATA_LENGTH] =
{
#include DF11_IN_DATA(DF11_TESTCASE)
};

const float32_t __attribute__((weak)) ctl_buffer[DATA_LENGTH] =
{
#include DF11_CTL_DATA(DF11_TESTCASE)
};

static float32_t out_buffer[DATA_LENGTH];

#ifdef __cplusplus
}
#endif // extern "C"

#endif
