/*
 * Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
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
