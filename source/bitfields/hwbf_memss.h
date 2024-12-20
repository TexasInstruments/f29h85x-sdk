//###########################################################################
//
// FILE:    hwbf_memss.h
//
// TITLE:   Definitions for the MEMSS registers.
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

#ifndef HWBF_MEMSS_H
#define HWBF_MEMSS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// MEMSS Individual Register Bit Definitions:

struct MEMSS_LPA0_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LPA0 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LPA0 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LPA0_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LPA0_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LPA0_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LPA0_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LPA0_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LPA0_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LPA0_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LPA0_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LPA0_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LPA0_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LPA1_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LPA1 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LPA1 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LPA1_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LPA1_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LPA1_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LPA1_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LPA1_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LPA1_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LPA1_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LPA1_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LPA1_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LPA1_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LDA0_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA0 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LDA0 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LDA0_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LDA0_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LDA0_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LDA0_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA0_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LDA0_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LDA0_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LDA0_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA0_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LDA0_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LDA1_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA1 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LDA1 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LDA1_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LDA1_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LDA1_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LDA1_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA1_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LDA1_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LDA1_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LDA1_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA1_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LDA1_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LDA2_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA2 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LDA2 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LDA2_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LDA2_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LDA2_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LDA2_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA2_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LDA2_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LDA2_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LDA2_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA2_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LDA2_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LDA3_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA3 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LDA3 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LDA3_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LDA3_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LDA3_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LDA3_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA3_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LDA3_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LDA3_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LDA3_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA3_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LDA3_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LDA4_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA4 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LDA4 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LDA4_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LDA4_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LDA4_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LDA4_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA4_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LDA4_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LDA4_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LDA4_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA4_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LDA4_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LDA5_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA5 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LDA5 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LDA5_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LDA5_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LDA5_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LDA5_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA5_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LDA5_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LDA5_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LDA5_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA5_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LDA5_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LDA6_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA6 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LDA6 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LDA6_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LDA6_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LDA6_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LDA6_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA6_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LDA6_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LDA6_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LDA6_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA6_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LDA6_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_LDA7_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA7 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 LDA7 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_LDA7_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_LDA7_MEM_CONFIG_BITS  bit;
};

struct MEMSS_LDA7_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t LDA7_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA7_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_LDA7_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_LDA7_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t LDA7_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_LDA7_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_LDA7_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_L_CONFIG_REGS {
    union   MEMSS_LPA0_MEM_CONFIG_REG        LPA0_MEM_CONFIG;              // LPA0 Memory Configuration Register
    union   MEMSS_LPA0_MEM_CONFIG_LOCK_REG   LPA0_MEM_CONFIG_LOCK;         // Temporary Lock for LPA0 Memory Configuration Register
    union   MEMSS_LPA0_MEM_CONFIG_COMMIT_REG LPA0_MEM_CONFIG_COMMIT;       // Permament Lock for LPA0 Memory Configuration Register
    uint8_t                                  rsvd1[4];                     // Reserved
    union   MEMSS_LPA1_MEM_CONFIG_REG        LPA1_MEM_CONFIG;              // LPA1 Memory Configuration Register
    union   MEMSS_LPA1_MEM_CONFIG_LOCK_REG   LPA1_MEM_CONFIG_LOCK;         // Temporary Lock for LPA1 Memory Configuration Register
    union   MEMSS_LPA1_MEM_CONFIG_COMMIT_REG LPA1_MEM_CONFIG_COMMIT;       // Permament Lock for LPA1 Memory Configuration Register
    uint8_t                                  rsvd2[4];                     // Reserved
    union   MEMSS_LDA0_MEM_CONFIG_REG        LDA0_MEM_CONFIG;              // LDA0 Memory Configuration Register
    union   MEMSS_LDA0_MEM_CONFIG_LOCK_REG   LDA0_MEM_CONFIG_LOCK;         // Temporary Lock for LDA0 Memory Configuration Register
    union   MEMSS_LDA0_MEM_CONFIG_COMMIT_REG LDA0_MEM_CONFIG_COMMIT;       // Permament Lock for LDA0 Memory Configuration Register
    uint8_t                                  rsvd3[4];                     // Reserved
    union   MEMSS_LDA1_MEM_CONFIG_REG        LDA1_MEM_CONFIG;              // LDA1 Memory Configuration Register
    union   MEMSS_LDA1_MEM_CONFIG_LOCK_REG   LDA1_MEM_CONFIG_LOCK;         // Temporary Lock for LDA1 Memory Configuration Register
    union   MEMSS_LDA1_MEM_CONFIG_COMMIT_REG LDA1_MEM_CONFIG_COMMIT;       // Permament Lock for LDA1 Memory Configuration Register
    uint8_t                                  rsvd4[4];                     // Reserved
    union   MEMSS_LDA2_MEM_CONFIG_REG        LDA2_MEM_CONFIG;              // LDA2 Memory Configuration Register
    union   MEMSS_LDA2_MEM_CONFIG_LOCK_REG   LDA2_MEM_CONFIG_LOCK;         // Temporary Lock for LDA2 Memory Configuration Register
    union   MEMSS_LDA2_MEM_CONFIG_COMMIT_REG LDA2_MEM_CONFIG_COMMIT;       // Permament Lock for LDA2 Memory Configuration Register
    uint8_t                                  rsvd5[4];                     // Reserved
    union   MEMSS_LDA3_MEM_CONFIG_REG        LDA3_MEM_CONFIG;              // LDA3 Memory Configuration Register
    union   MEMSS_LDA3_MEM_CONFIG_LOCK_REG   LDA3_MEM_CONFIG_LOCK;         // Temporary Lock for LDA3 Memory Configuration Register
    union   MEMSS_LDA3_MEM_CONFIG_COMMIT_REG LDA3_MEM_CONFIG_COMMIT;       // Permament Lock for LDA3 Memory Configuration Register
    uint8_t                                  rsvd6[4];                     // Reserved
    union   MEMSS_LDA4_MEM_CONFIG_REG        LDA4_MEM_CONFIG;              // LDA4 Memory Configuration Register
    union   MEMSS_LDA4_MEM_CONFIG_LOCK_REG   LDA4_MEM_CONFIG_LOCK;         // Temporary Lock for LDA4 Memory Configuration Register
    union   MEMSS_LDA4_MEM_CONFIG_COMMIT_REG LDA4_MEM_CONFIG_COMMIT;       // Permament Lock for LDA4 Memory Configuration Register
    uint8_t                                  rsvd7[4];                     // Reserved
    union   MEMSS_LDA5_MEM_CONFIG_REG        LDA5_MEM_CONFIG;              // LDA5 Memory Configuration Register
    union   MEMSS_LDA5_MEM_CONFIG_LOCK_REG   LDA5_MEM_CONFIG_LOCK;         // Temporary Lock for LDA5 Memory Configuration Register
    union   MEMSS_LDA5_MEM_CONFIG_COMMIT_REG LDA5_MEM_CONFIG_COMMIT;       // Permament Lock for LDA5 Memory Configuration Register
    uint8_t                                  rsvd8[4];                     // Reserved
    union   MEMSS_LDA6_MEM_CONFIG_REG        LDA6_MEM_CONFIG;              // LDA6 Memory Configuration Register
    union   MEMSS_LDA6_MEM_CONFIG_LOCK_REG   LDA6_MEM_CONFIG_LOCK;         // Temporary Lock for LDA6 Memory Configuration Register
    union   MEMSS_LDA6_MEM_CONFIG_COMMIT_REG LDA6_MEM_CONFIG_COMMIT;       // Permament Lock for LDA6 Memory Configuration Register
    uint8_t                                  rsvd9[4];                     // Reserved
    union   MEMSS_LDA7_MEM_CONFIG_REG        LDA7_MEM_CONFIG;              // LDA7 Memory Configuration Register
    union   MEMSS_LDA7_MEM_CONFIG_LOCK_REG   LDA7_MEM_CONFIG_LOCK;         // Temporary Lock for LDA7 Memory Configuration Register
    union   MEMSS_LDA7_MEM_CONFIG_COMMIT_REG LDA7_MEM_CONFIG_COMMIT;       // Permament Lock for LDA7 Memory Configuration Register
};

struct MEMSS_CPA0_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LPA0 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CPA0 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CPA0_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CPA0_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CPA0_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CPA0_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPA0_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CPA0_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CPA0_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CPA0_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPA0_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CPA0_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CPA1_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LPA1 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CPA1 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CPA1_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CPA1_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CPA1_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CPA1_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPA1_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CPA1_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CPA1_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CPA1_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPA1_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CPA1_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA0_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA0 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA0 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA0_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA0_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA0_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA0_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA0_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA0_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA0_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA0_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA0_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA0_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA1_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA1 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA1 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA1_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA1_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA1_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA1_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA1_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA1_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA1_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA1_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA1_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA1_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA2_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA2 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA2 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA2_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA2_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA2_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA2_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA2_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA2_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA2_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA2_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA2_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA2_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA3_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA3 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA3 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA3_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA3_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA3_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA3_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA3_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA3_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA3_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA3_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA3_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA3_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA4_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA4 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA4 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA4_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA4_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA4_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA4_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA4_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA4_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA4_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA4_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA4_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA4_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA5_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA5 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA5 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA5_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA5_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA5_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA5_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA5_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA5_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA5_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA5_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA5_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA5_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA6_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA6 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA6 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA6_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA6_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA6_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA6_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA6_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA6_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA6_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA6_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA6_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA6_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA7_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA7 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA7 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA7_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA7_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA7_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA7_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA7_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA7_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA7_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA7_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA7_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA7_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA8_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA8 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA8 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA8_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA8_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA8_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA8_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA8_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA8_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA8_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA8_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA8_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA8_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA9_MEM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA9 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA9 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA9_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA9_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA9_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA9_MEM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA9_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA9_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA9_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA9_MEM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA9_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA9_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA10_MEM_CONFIG_BITS {    // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA10 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA10 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA10_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA10_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA10_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA10_MEM_CONFIG:1;        // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA10_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA10_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA10_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA10_MEM_CONFIG_LOCK:1;   // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA10_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA10_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CDA11_MEM_CONFIG_BITS {    // bits description
    uint16_t TESTMODE:2;                // 1:0 LDA11 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 CDA11 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_CDA11_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CDA11_MEM_CONFIG_BITS  bit;
};

struct MEMSS_CDA11_MEM_CONFIG_LOCK_BITS {// bits description
    uint16_t CDA11_MEM_CONFIG:1;        // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA11_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CDA11_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CDA11_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CDA11_MEM_CONFIG_LOCK:1;   // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CDA11_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CDA11_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_C_CONFIG_REGS {
    union   MEMSS_CPA0_MEM_CONFIG_REG        CPA0_MEM_CONFIG;              // CPA0 Memory Configuration Register
    union   MEMSS_CPA0_MEM_CONFIG_LOCK_REG   CPA0_MEM_CONFIG_LOCK;         // Temporary Lock for CPA0 Memory Configuration Register
    union   MEMSS_CPA0_MEM_CONFIG_COMMIT_REG CPA0_MEM_CONFIG_COMMIT;       // Permament Lock for CPA0 Memory Configuration Register
    uint8_t                                  rsvd1[4];                     // Reserved
    union   MEMSS_CPA1_MEM_CONFIG_REG        CPA1_MEM_CONFIG;              // CPA1 Memory Configuration Register
    union   MEMSS_CPA1_MEM_CONFIG_LOCK_REG   CPA1_MEM_CONFIG_LOCK;         // Temporary Lock for CPA1 Memory Configuration Register
    union   MEMSS_CPA1_MEM_CONFIG_COMMIT_REG CPA1_MEM_CONFIG_COMMIT;       // Permament Lock for CPA1 Memory Configuration Register
    uint8_t                                  rsvd2[4];                     // Reserved
    union   MEMSS_CDA0_MEM_CONFIG_REG        CDA0_MEM_CONFIG;              // CDA0 Memory Configuration Register
    union   MEMSS_CDA0_MEM_CONFIG_LOCK_REG   CDA0_MEM_CONFIG_LOCK;         // Temporary Lock for CDA0 Memory Configuration Register
    union   MEMSS_CDA0_MEM_CONFIG_COMMIT_REG CDA0_MEM_CONFIG_COMMIT;       // Permament Lock for CDA0 Memory Configuration Register
    uint8_t                                  rsvd3[4];                     // Reserved
    union   MEMSS_CDA1_MEM_CONFIG_REG        CDA1_MEM_CONFIG;              // CDA1 Memory Configuration Register
    union   MEMSS_CDA1_MEM_CONFIG_LOCK_REG   CDA1_MEM_CONFIG_LOCK;         // Temporary Lock for CDA1 Memory Configuration Register
    union   MEMSS_CDA1_MEM_CONFIG_COMMIT_REG CDA1_MEM_CONFIG_COMMIT;       // Permament Lock for CDA1 Memory Configuration Register
    uint8_t                                  rsvd4[4];                     // Reserved
    union   MEMSS_CDA2_MEM_CONFIG_REG        CDA2_MEM_CONFIG;              // CDA2 Memory Configuration Register
    union   MEMSS_CDA2_MEM_CONFIG_LOCK_REG   CDA2_MEM_CONFIG_LOCK;         // Temporary Lock for CDA2 Memory Configuration Register
    union   MEMSS_CDA2_MEM_CONFIG_COMMIT_REG CDA2_MEM_CONFIG_COMMIT;       // Permament Lock for CDA2 Memory Configuration Register
    uint8_t                                  rsvd5[4];                     // Reserved
    union   MEMSS_CDA3_MEM_CONFIG_REG        CDA3_MEM_CONFIG;              // CDA3 Memory Configuration Register
    union   MEMSS_CDA3_MEM_CONFIG_LOCK_REG   CDA3_MEM_CONFIG_LOCK;         // Temporary Lock for CDA3 Memory Configuration Register
    union   MEMSS_CDA3_MEM_CONFIG_COMMIT_REG CDA3_MEM_CONFIG_COMMIT;       // Permament Lock for CDA3 Memory Configuration Register
    uint8_t                                  rsvd6[4];                     // Reserved
    union   MEMSS_CDA4_MEM_CONFIG_REG        CDA4_MEM_CONFIG;              // CDA4 Memory Configuration Register
    union   MEMSS_CDA4_MEM_CONFIG_LOCK_REG   CDA4_MEM_CONFIG_LOCK;         // Temporary Lock for CDA4 Memory Configuration Register
    union   MEMSS_CDA4_MEM_CONFIG_COMMIT_REG CDA4_MEM_CONFIG_COMMIT;       // Permament Lock for CDA4 Memory Configuration Register
    uint8_t                                  rsvd7[4];                     // Reserved
    union   MEMSS_CDA5_MEM_CONFIG_REG        CDA5_MEM_CONFIG;              // CDA5 Memory Configuration Register
    union   MEMSS_CDA5_MEM_CONFIG_LOCK_REG   CDA5_MEM_CONFIG_LOCK;         // Temporary Lock for CDA5 Memory Configuration Register
    union   MEMSS_CDA5_MEM_CONFIG_COMMIT_REG CDA5_MEM_CONFIG_COMMIT;       // Permament Lock for CDA5 Memory Configuration Register
    uint8_t                                  rsvd8[4];                     // Reserved
    union   MEMSS_CDA6_MEM_CONFIG_REG        CDA6_MEM_CONFIG;              // CDA6 Memory Configuration Register
    union   MEMSS_CDA6_MEM_CONFIG_LOCK_REG   CDA6_MEM_CONFIG_LOCK;         // Temporary Lock for CDA6 Memory Configuration Register
    union   MEMSS_CDA6_MEM_CONFIG_COMMIT_REG CDA6_MEM_CONFIG_COMMIT;       // Permament Lock for CDA6 Memory Configuration Register
    uint8_t                                  rsvd9[4];                     // Reserved
    union   MEMSS_CDA7_MEM_CONFIG_REG        CDA7_MEM_CONFIG;              // CDA7 Memory Configuration Register
    union   MEMSS_CDA7_MEM_CONFIG_LOCK_REG   CDA7_MEM_CONFIG_LOCK;         // Temporary Lock for CDA7 Memory Configuration Register
    union   MEMSS_CDA7_MEM_CONFIG_COMMIT_REG CDA7_MEM_CONFIG_COMMIT;       // Permament Lock for CDA7 Memory Configuration Register
    uint8_t                                  rsvd10[4];                    // Reserved
    union   MEMSS_CDA8_MEM_CONFIG_REG        CDA8_MEM_CONFIG;              // CDA8 Memory Configuration Register
    union   MEMSS_CDA8_MEM_CONFIG_LOCK_REG   CDA8_MEM_CONFIG_LOCK;         // Temporary Lock for CDA8 Memory Configuration Register
    union   MEMSS_CDA8_MEM_CONFIG_COMMIT_REG CDA8_MEM_CONFIG_COMMIT;       // Permament Lock for CDA8 Memory Configuration Register
    uint8_t                                  rsvd11[4];                    // Reserved
    union   MEMSS_CDA9_MEM_CONFIG_REG        CDA9_MEM_CONFIG;              // CDA9 Memory Configuration Register
    union   MEMSS_CDA9_MEM_CONFIG_LOCK_REG   CDA9_MEM_CONFIG_LOCK;         // Temporary Lock for CDA9 Memory Configuration Register
    union   MEMSS_CDA9_MEM_CONFIG_COMMIT_REG CDA9_MEM_CONFIG_COMMIT;       // Permament Lock for CDA9 Memory Configuration Register
    uint8_t                                  rsvd12[4];                    // Reserved
    union   MEMSS_CDA10_MEM_CONFIG_REG       CDA10_MEM_CONFIG;             // CDA10 Memory Configuration Register
    union   MEMSS_CDA10_MEM_CONFIG_LOCK_REG  CDA10_MEM_CONFIG_LOCK;        // Temporary Lock for CDA10 Memory Configuration Register
    union   MEMSS_CDA10_MEM_CONFIG_COMMIT_REG CDA10_MEM_CONFIG_COMMIT;     // Permament Lock for CDA10 Memory Configuration Register
    uint8_t                                  rsvd13[4];                    // Reserved
    union   MEMSS_CDA11_MEM_CONFIG_REG       CDA11_MEM_CONFIG;             // CDA11 Memory Configuration Register
    union   MEMSS_CDA11_MEM_CONFIG_LOCK_REG  CDA11_MEM_CONFIG_LOCK;        // Temporary Lock for CDA11 Memory Configuration Register
    union   MEMSS_CDA11_MEM_CONFIG_COMMIT_REG CDA11_MEM_CONFIG_COMMIT;     // Permament Lock for CDA11 Memory Configuration Register
};

struct MEMSS_M0_MEM_CONFIG_BITS {       // bits description
    uint16_t TESTMODE:2;                // 1:0 M0 Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t INIT:1;                    // 16 Triggers memory Initilization
    uint16_t rsvd2:7;                   // 23:17 Reserved
    uint16_t INIT_STS:1;                // 24 M0 INIT status
    uint16_t rsvd3:7;                   // 31:25 Reserved
};

union MEMSS_M0_MEM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_M0_MEM_CONFIG_BITS  bit;
};

struct MEMSS_M0_MEM_CONFIG_LOCK_BITS {  // bits description
    uint16_t M0_MEM_CONFIG:1;           // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_M0_MEM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_M0_MEM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_M0_MEM_CONFIG_COMMIT_BITS {// bits description
    uint16_t M0_MEM_CONFIG_LOCK:1;      // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_M0_MEM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_M0_MEM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_M_CONFIG_REGS {
    union   MEMSS_M0_MEM_CONFIG_REG          M0_MEM_CONFIG;                // M0 Memory Configuration Register
    union   MEMSS_M0_MEM_CONFIG_LOCK_REG     M0_MEM_CONFIG_LOCK;           // Temporary Lock for M0 Memory Configuration Register
    union   MEMSS_M0_MEM_CONFIG_COMMIT_REG   M0_MEM_CONFIG_COMMIT;         // Permament Lock for M0 Memory Configuration Register
};

struct MEMSS_CPU1_ROM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 CPU1_ROM Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:1;                   // 16 Reserved
    uint16_t rsvd3:7;                   // 23:17 Reserved
    uint16_t rsvd4:2;                   // 25:24 Reserved
    uint16_t rsvd5:6;                   // 31:26 Reserved
};

union MEMSS_CPU1_ROM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_ROM_CONFIG_BITS  bit;
};

struct MEMSS_CPU1_ROM_CONFIG_LOCK_BITS {// bits description
    uint16_t CPU1_ROM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_ROM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_ROM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CPU1_ROM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CPU1_ROM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_ROM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_ROM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CPU2_ROM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 CPU1_ROM Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:1;                   // 16 Reserved
    uint16_t rsvd3:7;                   // 23:17 Reserved
    uint16_t rsvd4:2;                   // 25:24 Reserved
    uint16_t rsvd5:6;                   // 31:26 Reserved
};

union MEMSS_CPU2_ROM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CPU2_ROM_CONFIG_BITS  bit;
};

struct MEMSS_CPU2_ROM_CONFIG_LOCK_BITS {// bits description
    uint16_t CPU2_ROM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU2_ROM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CPU2_ROM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CPU2_ROM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CPU2_ROM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU2_ROM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CPU2_ROM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_CPU3_ROM_CONFIG_BITS {     // bits description
    uint16_t TESTMODE:2;                // 1:0 CPU1_ROM Test Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:1;                   // 16 Reserved
    uint16_t rsvd3:7;                   // 23:17 Reserved
    uint16_t rsvd4:2;                   // 25:24 Reserved
    uint16_t rsvd5:6;                   // 31:26 Reserved
};

union MEMSS_CPU3_ROM_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_CPU3_ROM_CONFIG_BITS  bit;
};

struct MEMSS_CPU3_ROM_CONFIG_LOCK_BITS {// bits description
    uint16_t CPU3_ROM_CONFIG:1;         // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU3_ROM_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CPU3_ROM_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_CPU3_ROM_CONFIG_COMMIT_BITS {// bits description
    uint16_t CPU3_ROM_CONFIG_LOCK:1;    // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU3_ROM_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CPU3_ROM_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_ROM_CONFIG_REGS {
    union   MEMSS_CPU1_ROM_CONFIG_REG        CPU1_ROM_CONFIG;              // CPU1 ROM Configuration Register
    union   MEMSS_CPU1_ROM_CONFIG_LOCK_REG   CPU1_ROM_CONFIG_LOCK;         // Temporary Lock for CPU1 ROM Memory Configuration Register
    union   MEMSS_CPU1_ROM_CONFIG_COMMIT_REG CPU1_ROM_CONFIG_COMMIT;       // Permament Lock for CPU1 ROM Memory Configuration Register
    uint8_t                                  rsvd1[4];                     // Reserved
    union   MEMSS_CPU2_ROM_CONFIG_REG        CPU2_ROM_CONFIG;              // CPU2 ROM Configuration Register
    union   MEMSS_CPU2_ROM_CONFIG_LOCK_REG   CPU2_ROM_CONFIG_LOCK;         // Temporary Lock for CPU2 ROM Memory Configuration Register
    union   MEMSS_CPU2_ROM_CONFIG_COMMIT_REG CPU2_ROM_CONFIG_COMMIT;       // Permament Lock for CPU2 ROM Memory Configuration Register
    uint8_t                                  rsvd2[4];                     // Reserved
    union   MEMSS_CPU3_ROM_CONFIG_REG        CPU3_ROM_CONFIG;              // CPU3 ROM Configuration Register
    union   MEMSS_CPU3_ROM_CONFIG_LOCK_REG   CPU3_ROM_CONFIG_LOCK;         // Temporary Lock for CPU3 ROM Memory Configuration Register
    union   MEMSS_CPU3_ROM_CONFIG_COMMIT_REG CPU3_ROM_CONFIG_COMMIT;       // Permament Lock for CPU3 ROM Memory Configuration Register
};

struct MEMSS_MEM_DLB_CONFIG_BITS {      // bits description
    uint16_t CPU1_DLB_EN:1;             // 0 CPU1 Data line buffer Enable
    uint16_t CPU2_DLB_EN:1;             // 1 CPU2 Data line buffer Enable
    uint16_t CPU3_DLB_EN:1;             // 2 CPU3 Data line buffer Enable
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t rsvd2:1;                   // 4 Reserved
    uint16_t rsvd3:1;                   // 5 Reserved
    uint16_t SYNCBRIDGE_DLB_EN:1;       // 6 Sync Bridge Dataline buffer Enable
    uint16_t rsvd4:9;                   // 15:7 Reserved
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union MEMSS_MEM_DLB_CONFIG_REG {
    uint32_t  all;
    struct  MEMSS_MEM_DLB_CONFIG_BITS  bit;
};

struct MEMSS_MEM_DLB_CONFIG_LOCK_BITS { // bits description
    uint16_t MEM_DLB_CONFIG:1;          // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_MEM_DLB_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_MEM_DLB_CONFIG_LOCK_BITS  bit;
};

struct MEMSS_MEM_DLB_CONFIG_COMMIT_BITS {// bits description
    uint16_t MEM_DLB_CONFIG_LOCK:1;     // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_MEM_DLB_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_MEM_DLB_CONFIG_COMMIT_BITS  bit;
};

struct MEMSS_PERI_MEM_TEST_LOCK_BITS {  // bits description
    uint16_t PERI_MEM_TEST_CONTROL:1;   // 0 PERI_MEM_TEST_CONTROL Lock bit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_PERI_MEM_TEST_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_PERI_MEM_TEST_LOCK_BITS  bit;
};

struct MEMSS_PERI_MEM_TEST_CONTROL_BITS {// bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:1;                   // 4 Reserved
    uint16_t EtherCAT_MEM_FORCE_ERROR:1; // 5 Force Parity Error on EtherCAT RAM
    uint16_t rsvd6:10;                  // 15:6 Reserved
    uint16_t rsvd7:16;                  // 31:16 Reserved
};

union MEMSS_PERI_MEM_TEST_CONTROL_REG {
    uint32_t  all;
    struct  MEMSS_PERI_MEM_TEST_CONTROL_BITS  bit;
};

struct MEMSS_PARITY_TEST_BITS {         // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity test enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_PARITY_TEST_REG {
    uint32_t  all;
    struct  MEMSS_PARITY_TEST_BITS  bit;
};

struct MEMSS_MISCI_REGS {
    union   MEMSS_MEM_DLB_CONFIG_REG         MEM_DLB_CONFIG;               // Dataline buffer enable
    union   MEMSS_MEM_DLB_CONFIG_LOCK_REG    MEM_DLB_CONFIG_LOCK;          // Temporary Lock for DLB Configuration Register
    union   MEMSS_MEM_DLB_CONFIG_COMMIT_REG  MEM_DLB_CONFIG_COMMIT;        // Permament Lock for DLB Configuration Register
    uint8_t                                  rsvd1[4];                     // Reserved
    union   MEMSS_PERI_MEM_TEST_LOCK_REG     PERI_MEM_TEST_LOCK;           // Peripheral Memory Test Lock Register
    union   MEMSS_PERI_MEM_TEST_CONTROL_REG  PERI_MEM_TEST_CONTROL;        // Peripheral Memory Test control Register
    uint8_t                                  rsvd2[484];                   // Reserved
    union   MEMSS_PARITY_TEST_REG            PARITY_TEST;                  // Enabling the parity test feature
};

struct MEMSS_CPU1_ROM_PATCH_REG_LOCK_BITS {// bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_ROM_PATCH_REG_LOCK_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_ROM_PATCH_REG_LOCK_BITS  bit;
};

struct MEMSS_CPU1_ROM_PATCH_REG_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_ROM_PATCH_REG_COMMIT_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_ROM_PATCH_REG_COMMIT_BITS  bit;
};

struct MEMSS_CPU1_0_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_0_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_0_ADDR_BITS  bit;
};

struct MEMSS_CPU1_0_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_0_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_0_ECC_BITS  bit;
};

struct MEMSS_CPU1_1_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_1_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_1_ADDR_BITS  bit;
};

struct MEMSS_CPU1_1_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_1_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_1_ECC_BITS  bit;
};

struct MEMSS_CPU1_2_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_2_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_2_ADDR_BITS  bit;
};

struct MEMSS_CPU1_2_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_2_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_2_ECC_BITS  bit;
};

struct MEMSS_CPU1_3_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_3_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_3_ADDR_BITS  bit;
};

struct MEMSS_CPU1_3_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_3_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_3_ECC_BITS  bit;
};

struct MEMSS_CPU1_4_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_4_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_4_ADDR_BITS  bit;
};

struct MEMSS_CPU1_4_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_4_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_4_ECC_BITS  bit;
};

struct MEMSS_CPU1_5_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_5_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_5_ADDR_BITS  bit;
};

struct MEMSS_CPU1_5_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_5_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_5_ECC_BITS  bit;
};

struct MEMSS_CPU1_6_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_6_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_6_ADDR_BITS  bit;
};

struct MEMSS_CPU1_6_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_6_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_6_ECC_BITS  bit;
};

struct MEMSS_CPU1_7_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_7_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_7_ADDR_BITS  bit;
};

struct MEMSS_CPU1_7_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_7_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_7_ECC_BITS  bit;
};

struct MEMSS_CPU1_8_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_8_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_8_ADDR_BITS  bit;
};

struct MEMSS_CPU1_8_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_8_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_8_ECC_BITS  bit;
};

struct MEMSS_CPU1_9_ADDR_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_9_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_9_ADDR_BITS  bit;
};

struct MEMSS_CPU1_9_ECC_BITS {          // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_9_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_9_ECC_BITS  bit;
};

struct MEMSS_CPU1_10_ADDR_BITS {        // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_10_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_10_ADDR_BITS  bit;
};

struct MEMSS_CPU1_10_ECC_BITS {         // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_10_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_10_ECC_BITS  bit;
};

struct MEMSS_CPU1_11_ADDR_BITS {        // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_11_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_11_ADDR_BITS  bit;
};

struct MEMSS_CPU1_11_ECC_BITS {         // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_11_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_11_ECC_BITS  bit;
};

struct MEMSS_CPU1_12_ADDR_BITS {        // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_12_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_12_ADDR_BITS  bit;
};

struct MEMSS_CPU1_12_ECC_BITS {         // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_12_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_12_ECC_BITS  bit;
};

struct MEMSS_CPU1_13_ADDR_BITS {        // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_13_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_13_ADDR_BITS  bit;
};

struct MEMSS_CPU1_13_ECC_BITS {         // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_13_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_13_ECC_BITS  bit;
};

struct MEMSS_CPU1_14_ADDR_BITS {        // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_14_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_14_ADDR_BITS  bit;
};

struct MEMSS_CPU1_14_ECC_BITS {         // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_14_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_14_ECC_BITS  bit;
};

struct MEMSS_CPU1_15_ADDR_BITS {        // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint32_t ADDR_64B_ALIGNED:29;       // 31:3 Address to be patched
};

union MEMSS_CPU1_15_ADDR_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_15_ADDR_BITS  bit;
};

struct MEMSS_CPU1_15_ECC_BITS {         // bits description
    uint16_t ECC:8;                     // 7:0 ECC of 64 bits to be patched
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union MEMSS_CPU1_15_ECC_REG {
    uint32_t  all;
    struct  MEMSS_CPU1_15_ECC_BITS  bit;
};

struct MEMSS_CPU1_ROM_PATCH_REGS {
    union   MEMSS_CPU1_ROM_PATCH_REG_LOCK_REG CPU1_ROM_PATCH_REG_LOCK;     // Temporary Lock for CPU1 ROM PATCH ADDR, ECC and DATA registers
    union   MEMSS_CPU1_ROM_PATCH_REG_COMMIT_REG CPU1_ROM_PATCH_REG_COMMIT; // Permament  Lock for CPU1 ROM PATCH ADDR, ECC and DATA registers
    uint8_t                                  rsvd1[8];                     // Reserved
    union   MEMSS_CPU1_0_ADDR_REG            CPU1_0_ADDR;                  // Address-0 of ROM to be patched
    union   MEMSS_CPU1_0_ECC_REG             CPU1_0_ECC;                   // ECC bits for Address-0 of ROM
    uint32_t                                 CPU1_0_DATA64_L;              // Data[31:0] for Address-0
    uint32_t                                 CPU1_0_DATA64_H;              // Data[63:32] for Address-0
    union   MEMSS_CPU1_1_ADDR_REG            CPU1_1_ADDR;                  // Address-1 of ROM to be patched
    union   MEMSS_CPU1_1_ECC_REG             CPU1_1_ECC;                   // ECC bits for Address-1 of ROM
    uint32_t                                 CPU1_1_DATA64_L;              // Data[31:0] for Address-1
    uint32_t                                 CPU1_1_DATA64_H;              // Data[63:32] for Address-1
    union   MEMSS_CPU1_2_ADDR_REG            CPU1_2_ADDR;                  // Address-2 of ROM to be patched
    union   MEMSS_CPU1_2_ECC_REG             CPU1_2_ECC;                   // ECC bits for Address-2 of ROM
    uint32_t                                 CPU1_2_DATA64_L;              // Data[31:0] for Address-2
    uint32_t                                 CPU1_2_DATA64_H;              // Data[63:32] for Address-2
    union   MEMSS_CPU1_3_ADDR_REG            CPU1_3_ADDR;                  // Address-3 of ROM to be patched
    union   MEMSS_CPU1_3_ECC_REG             CPU1_3_ECC;                   // ECC bits for Address-3 of ROM
    uint32_t                                 CPU1_3_DATA64_L;              // Data[31:0] for Address-3
    uint32_t                                 CPU1_3_DATA64_H;              // Data[63:32] for Address-3
    union   MEMSS_CPU1_4_ADDR_REG            CPU1_4_ADDR;                  // Address-4 of ROM to be patched
    union   MEMSS_CPU1_4_ECC_REG             CPU1_4_ECC;                   // ECC bits for Address-4 of ROM
    uint32_t                                 CPU1_4_DATA64_L;              // Data[31:0] for Address-4
    uint32_t                                 CPU1_4_DATA64_H;              // Data[63:32] for Address-4
    union   MEMSS_CPU1_5_ADDR_REG            CPU1_5_ADDR;                  // Address-5 of ROM to be patched
    union   MEMSS_CPU1_5_ECC_REG             CPU1_5_ECC;                   // ECC bits for Address-5 of ROM
    uint32_t                                 CPU1_5_DATA64_L;              // Data[31:0] for Address-5
    uint32_t                                 CPU1_5_DATA64_H;              // Data[63:32] for Address-5
    union   MEMSS_CPU1_6_ADDR_REG            CPU1_6_ADDR;                  // Address-6 of ROM to be patched
    union   MEMSS_CPU1_6_ECC_REG             CPU1_6_ECC;                   // ECC bits for Address-6 of ROM
    uint32_t                                 CPU1_6_DATA64_L;              // Data[31:0] for Address-6
    uint32_t                                 CPU1_6_DATA64_H;              // Data[63:32] for Address-6
    union   MEMSS_CPU1_7_ADDR_REG            CPU1_7_ADDR;                  // Address-7 of ROM to be patched
    union   MEMSS_CPU1_7_ECC_REG             CPU1_7_ECC;                   // ECC bits for Address-7 of ROM
    uint32_t                                 CPU1_7_DATA64_L;              // Data[31:0] for Address-7
    uint32_t                                 CPU1_7_DATA64_H;              // Data[63:32] for Address-7
    union   MEMSS_CPU1_8_ADDR_REG            CPU1_8_ADDR;                  // Address-8 of ROM to be patched
    union   MEMSS_CPU1_8_ECC_REG             CPU1_8_ECC;                   // ECC bits for Address-8 of ROM
    uint32_t                                 CPU1_8_DATA64_L;              // Data[31:0] for Address-8
    uint32_t                                 CPU1_8_DATA64_H;              // Data[63:32] for Address-8
    union   MEMSS_CPU1_9_ADDR_REG            CPU1_9_ADDR;                  // Address-9 of ROM to be patched
    union   MEMSS_CPU1_9_ECC_REG             CPU1_9_ECC;                   // ECC bits for Address-9 of ROM
    uint32_t                                 CPU1_9_DATA64_L;              // Data[31:0] for Address-9
    uint32_t                                 CPU1_9_DATA64_H;              // Data[63:32] for Address-9
    union   MEMSS_CPU1_10_ADDR_REG           CPU1_10_ADDR;                 // Address-10 of ROM to be patched
    union   MEMSS_CPU1_10_ECC_REG            CPU1_10_ECC;                  // ECC bits for Address-10 of ROM
    uint32_t                                 CPU1_10_DATA64_L;             // Data[31:0] for Address-10
    uint32_t                                 CPU1_10_DATA64_H;             // Data[63:32] for Address-10
    union   MEMSS_CPU1_11_ADDR_REG           CPU1_11_ADDR;                 // Address-11 of ROM to be patched
    union   MEMSS_CPU1_11_ECC_REG            CPU1_11_ECC;                  // ECC bits for Address-11 of ROM
    uint32_t                                 CPU1_11_DATA64_L;             // Data[31:0] for Address-11
    uint32_t                                 CPU1_11_DATA64_H;             // Data[63:32] for Address-11
    union   MEMSS_CPU1_12_ADDR_REG           CPU1_12_ADDR;                 // Address-12 of ROM to be patched
    union   MEMSS_CPU1_12_ECC_REG            CPU1_12_ECC;                  // ECC bits for Address-12 of ROM
    uint32_t                                 CPU1_12_DATA64_L;             // Data[31:0] for Address-12
    uint32_t                                 CPU1_12_DATA64_H;             // Data[63:32] for Address-12
    union   MEMSS_CPU1_13_ADDR_REG           CPU1_13_ADDR;                 // Address-13 of ROM to be patched
    union   MEMSS_CPU1_13_ECC_REG            CPU1_13_ECC;                  // ECC bits for Address-13 of ROM
    uint32_t                                 CPU1_13_DATA64_L;             // Data[31:0] for Address-13
    uint32_t                                 CPU1_13_DATA64_H;             // Data[63:32] for Address-13
    union   MEMSS_CPU1_14_ADDR_REG           CPU1_14_ADDR;                 // Address-14 of ROM to be patched
    union   MEMSS_CPU1_14_ECC_REG            CPU1_14_ECC;                  // ECC bits for Address-14 of ROM
    uint32_t                                 CPU1_14_DATA64_L;             // Data[31:0] for Address-14
    uint32_t                                 CPU1_14_DATA64_H;             // Data[63:32] for Address-14
    union   MEMSS_CPU1_15_ADDR_REG           CPU1_15_ADDR;                 // Address-15 of ROM to be patched
    union   MEMSS_CPU1_15_ECC_REG            CPU1_15_ECC;                  // ECC bits for Address-15 of ROM
    uint32_t                                 CPU1_15_DATA64_L;             // Data[31:0] for Address-15
    uint32_t                                 CPU1_15_DATA64_H;             // Data[63:32] for Address-15
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
