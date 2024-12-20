//###########################################################################
//
// FILE:    hwbf_lcm.h
//
// TITLE:   Definitions for the LCM registers.
//
//###########################################################################
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//###########################################################################

#ifndef HWBF_LCM_H
#define HWBF_LCM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// LCM Individual Register Bit Definitions:

struct LCM_REVISION_BITS {              // bits description
    uint16_t MINOR:6;                   // 5:0 Minor Revision Number
    uint16_t CUSTOM:2;                  // 7:6 Custom Module Number
    uint16_t MAJOR:3;                   // 10:8 Major Revision Number
    uint16_t rsvd1:5;                   // 15:11 Reserved
    uint16_t FUNC:12;                   // 27:16 Functional Release Number
    uint16_t rsvd2:2;                   // 29:28 Reserved
    uint16_t SCHEME:2;                  // 31:30 Defines Scheme for Module
};

union LCM_REVISION_REG {
    uint32_t  all;
    struct  LCM_REVISION_BITS  bit;
};

struct LCM_LCM_CONTROL_BITS {           // bits description
    uint16_t CMPEN:1;                   // 0 Enable/disable configuration for lockstep compare.
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t STEN:1;                    // 16 Self-test enable
    uint16_t rsvd2:2;                   // 18:17 Reserved
    uint16_t CMP1_ERR_FORCE:1;          // 19 Force error on comparator-1 lockstep compare error output
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t CMP2_ERR_FORCE:1;          // 21 Force error on comparator-2 lockstep compare error output
    uint16_t rsvd4:10;                  // 31:22 Reserved
};

union LCM_LCM_CONTROL_REG {
    uint32_t  all;
    struct  LCM_LCM_CONTROL_BITS  bit;
};

struct LCM_LCM_STATUS_BITS {            // bits description
    uint16_t LSEN:1;                    // 0 Lockstep configuration status
    uint16_t CMP_FAIL:1;                // 1 Pass/fail status of lockstep compare
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t DBGCON:1;                  // 8 debugger connected status information
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t STPASS:1;                  // 16 self-test pass/fail status
    uint16_t STDONE:1;                  // 17 self-test completion status
    uint16_t STACTIVE:1;                // 18 self-test active status indication
    uint16_t CMP1_ERR_FORCE_PASS:1;     // 19 fail status of comparator1 func error forcing
    uint16_t CMP1_ERR_FORCE_DONE:1;     // 20 completion status of comparator1 func error forcing
    uint16_t CMP2_ERR_FORCE_PASS:1;     // 21 fail status of comparator2 func error forcing
    uint16_t CMP2_ERR_FORCE_DONE:1;     // 22 completion status of comparator2 func error forcing
    uint16_t rsvd3:9;                   // 31:23 Reserved
};

union LCM_LCM_STATUS_REG {
    uint32_t  all;
    struct  LCM_LCM_STATUS_BITS  bit;
};

struct LCM_LCM_STATUS_CLEAR_BITS {      // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CMP_FAIL:1;                // 1 Clear lockstep compare fail status
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t STPASS:1;                  // 16 clear Self-test_fail_status
    uint16_t STDONE:1;                  // 17 clear Self-test_done_status
    uint16_t rsvd3:1;                   // 18 Reserved
    uint16_t CMP1_ERR_FORCE_PASS:1;     // 19 clear cmp1_func_error_force_fail_status
    uint16_t CMP1_ERR_FORCE_DONE:1;     // 20 clear cmp1_func_error_force_done_status
    uint16_t CMP2_ERR_FORCE_PASS:1;     // 21 clear cmp2_func_error_force_fail_status
    uint16_t CMP2_ERR_FORCE_DONE:1;     // 22 clear cmp2_func_error_force_done_status
    uint16_t rsvd4:9;                   // 31:23 Reserved
};

union LCM_LCM_STATUS_CLEAR_REG {
    uint32_t  all;
    struct  LCM_LCM_STATUS_CLEAR_BITS  bit;
};

struct LCM_PARITY_TEST_BITS {           // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity test enable configuration
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LCM_PARITY_TEST_REG {
    uint32_t  all;
    struct  LCM_PARITY_TEST_BITS  bit;
};

struct LCM_LCM_LOCK_BITS {              // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t LCM_CONTROL:1;             // 2 Register lock configuration
    uint16_t rsvd3:1;                   // 3 Reserved
    uint16_t rsvd4:1;                   // 4 Reserved
    uint16_t rsvd5:1;                   // 5 Reserved
    uint16_t rsvd6:1;                   // 6 Reserved
    uint16_t rsvd7:1;                   // 7 Reserved
    uint16_t rsvd8:1;                   // 8 Reserved
    uint16_t rsvd9:1;                   // 9 Reserved
    uint16_t LCM_STATUS_CLEAR:1;        // 10 Register lock configuration
    uint16_t rsvd10:1;                  // 11 Reserved
    uint16_t rsvd11:1;                  // 12 Reserved
    uint16_t rsvd12:1;                  // 13 Reserved
    uint16_t rsvd13:1;                  // 14 Reserved
    uint16_t rsvd14:1;                  // 15 Reserved
    uint16_t rsvd15:1;                  // 16 Reserved
    uint16_t rsvd16:1;                  // 17 Reserved
    uint16_t rsvd17:1;                  // 18 Reserved
    uint16_t rsvd18:1;                  // 19 Reserved
    uint16_t rsvd19:1;                  // 20 Reserved
    uint16_t rsvd20:1;                  // 21 Reserved
    uint16_t rsvd21:1;                  // 22 Reserved
    uint16_t rsvd22:1;                  // 23 Reserved
    uint16_t rsvd23:1;                  // 24 Reserved
    uint16_t rsvd24:1;                  // 25 Reserved
    uint16_t PARITY_TEST:1;             // 26 Register lock configuration
    uint16_t rsvd25:1;                  // 27 Reserved
    uint16_t rsvd26:1;                  // 28 Reserved
    uint16_t rsvd27:1;                  // 29 Reserved
    uint16_t rsvd28:1;                  // 30 Reserved
    uint16_t rsvd29:1;                  // 31 Reserved
};

union LCM_LCM_LOCK_REG {
    uint32_t  all;
    struct  LCM_LCM_LOCK_BITS  bit;
};

struct LCM_LCM_COMMIT_BITS {            // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t LCM_CONTROL:1;             // 2 Register commit configuration
    uint16_t rsvd3:1;                   // 3 Reserved
    uint16_t rsvd4:1;                   // 4 Reserved
    uint16_t rsvd5:1;                   // 5 Reserved
    uint16_t rsvd6:1;                   // 6 Reserved
    uint16_t rsvd7:1;                   // 7 Reserved
    uint16_t rsvd8:1;                   // 8 Reserved
    uint16_t rsvd9:1;                   // 9 Reserved
    uint16_t LCM_STATUS_CLEAR:1;        // 10 Register commit configuration
    uint16_t rsvd10:1;                  // 11 Reserved
    uint16_t rsvd11:1;                  // 12 Reserved
    uint16_t rsvd12:1;                  // 13 Reserved
    uint16_t rsvd13:1;                  // 14 Reserved
    uint16_t rsvd14:1;                  // 15 Reserved
    uint16_t rsvd15:1;                  // 16 Reserved
    uint16_t rsvd16:1;                  // 17 Reserved
    uint16_t rsvd17:1;                  // 18 Reserved
    uint16_t rsvd18:1;                  // 19 Reserved
    uint16_t rsvd19:1;                  // 20 Reserved
    uint16_t rsvd20:1;                  // 21 Reserved
    uint16_t rsvd21:1;                  // 22 Reserved
    uint16_t rsvd22:1;                  // 23 Reserved
    uint16_t rsvd23:1;                  // 24 Reserved
    uint16_t rsvd24:1;                  // 25 Reserved
    uint16_t PARITY_TEST:1;             // 26 Register commit configuration
    uint16_t rsvd25:1;                  // 27 Reserved
    uint16_t rsvd26:1;                  // 28 Reserved
    uint16_t rsvd27:1;                  // 29 Reserved
    uint16_t rsvd28:1;                  // 30 Reserved
    uint16_t rsvd29:1;                  // 31 Reserved
};

union LCM_LCM_COMMIT_REG {
    uint32_t  all;
    struct  LCM_LCM_COMMIT_BITS  bit;
};

struct LCM_REGS {
    union   LCM_REVISION_REG                 REVISION;                     // IP Revision tie-off value
    uint8_t                                  rsvd1[4];                     // Reserved
    union   LCM_LCM_CONTROL_REG              LCM_CONTROL;                  // LCM Control configuration
    uint8_t                                  rsvd2[20];                    // Reserved
    union   LCM_LCM_STATUS_REG               LCM_STATUS;                   // LCM status register
    uint8_t                                  rsvd3[4];                     // Reserved
    union   LCM_LCM_STATUS_CLEAR_REG         LCM_STATUS_CLEAR;             // LCM Status clear register
    uint8_t                                  rsvd4[60];                    // Reserved
    union   LCM_PARITY_TEST_REG              PARITY_TEST;                  // Enabling the parity test feature
    uint8_t                                  rsvd5[4];                     // Reserved
    union   LCM_LCM_LOCK_REG                 LCM_LOCK;                     // LCM lock configuration
    uint8_t                                  rsvd6[4];                     // Reserved
    union   LCM_LCM_COMMIT_REG               LCM_COMMIT;                   // LCM commit configuration
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
