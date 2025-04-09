//###########################################################################
//
// FILE:    hwbf_pipe.h
//
// TITLE:   Definitions for the PIPE registers.
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

#ifndef HWBF_PIPE_H
#define HWBF_PIPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// PIPE Individual Register Bit Definitions:

struct PIPE_RTINT_THRESHOLD_BITS {      // bits description
    uint16_t INT_RTINT_THRESHOLD:8;     // 7:0 Interrupt threshold value
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_RTINT_THRESHOLD_REG {
    uint32_t  all;
    struct  PIPE_RTINT_THRESHOLD_BITS  bit;
};

struct PIPE_INT_GRP_MASK_BITS {         // bits description
    uint16_t INT_GRP_MASK:8;            // 7:0 Interrupt group mask
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_INT_GRP_MASK_REG {
    uint32_t  all;
    struct  PIPE_INT_GRP_MASK_BITS  bit;
};

struct PIPE_GLOBAL_EN_BITS {            // bits description
    uint16_t ENABLE:2;                  // 1:0 Global enable
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_GLOBAL_EN_REG {
    uint32_t  all;
    struct  PIPE_GLOBAL_EN_BITS  bit;
};

struct PIPE_REVISION_BITS {             // bits description
    uint16_t MINREV:8;                  // 7:0 Minor Revision Number
    uint16_t MAJREV:8;                  // 15:8 Major Revision Number
    uint16_t rsvd1:8;                   // 23:16 Reserved
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union PIPE_REVISION_REG {
    uint32_t  all;
    struct  PIPE_REVISION_BITS  bit;
};

struct PIPE_CPU_INT_STS_BITS {          // bits description
    uint16_t LAST_INTSTS:2;             // 1:0 Type of last interrupt in-service between INT and  RTINT
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t LAST_INT_PRIOLVL:8;        // 15:8 Priority level of last INT interrupt  in-service
    uint16_t LAST_RTINT_PRIOLVL:8;      // 23:16 Priority level of last RTINT interrupt  in-service
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union PIPE_CPU_INT_STS_REG {
    uint32_t  all;
    struct  PIPE_CPU_INT_STS_BITS  bit;
};

struct PIPE_RST_LINK_OWNER_BITS {       // bits description
    uint16_t LINK_OWNER:4;              // 3:0 Reset vector link owner
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_RST_LINK_OWNER_REG {
    uint32_t  all;
    struct  PIPE_RST_LINK_OWNER_BITS  bit;
};

struct PIPE_NMI_STS_BITS {              // bits description
    uint16_t NMI_FLAG:1;                // 0 Interrupt active
    uint16_t NMI_CLR:1;                 // 1 NMI SW clear bit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_NMI_STS_REG {
    uint32_t  all;
    struct  PIPE_NMI_STS_BITS  bit;
};

struct PIPE_NMI_LINK_OWNER_BITS {       // bits description
    uint16_t LINK_OWNER:4;              // 3:0 NMI vector link owner
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_NMI_LINK_OWNER_REG {
    uint32_t  all;
    struct  PIPE_NMI_LINK_OWNER_BITS  bit;
};

struct PIPE_MEM_ECC_DIAG_BITS {         // bits description
    uint16_t ECC_VIEW:1;                // 0 ECC memory map enable register
    uint16_t MEM_SIC_DIAG_EN:1;         // 1 Memory safe interconnect diagnostics enable
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_MEM_ECC_DIAG_REG {
    uint32_t  all;
    struct  PIPE_MEM_ECC_DIAG_BITS  bit;
};

struct PIPE_MEM_INIT_BITS {             // bits description
    uint16_t INIT:2;                    // 1:0 Memory initialization start
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_MEM_INIT_REG {
    uint32_t  all;
    struct  PIPE_MEM_INIT_BITS  bit;
};

struct PIPE_MEM_INIT_STS_BITS {         // bits description
    uint16_t INIT_STS:2;                // 1:0 Memory initialization status
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_MEM_INIT_STS_REG {
    uint32_t  all;
    struct  PIPE_MEM_INIT_STS_BITS  bit;
};

struct PIPE_INT_SEC_STS_BITS {          // bits description
    uint16_t SEC_FAIL_FLAG:1;           // 0 VBUSP access security error
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_INT_SEC_STS_REG {
    uint32_t  all;
    struct  PIPE_INT_SEC_STS_BITS  bit;
};

struct PIPE_INT_SEC_CLR_BITS {          // bits description
    uint16_t SEC_FAIL_FLAG_CLR:1;       // 0 SEC_FAIL_FLAG bit clear field
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_INT_SEC_CLR_REG {
    uint32_t  all;
    struct  PIPE_INT_SEC_CLR_BITS  bit;
};

struct PIPE_RTINT_SP_L_BITS {           // bits description
    uint16_t RTISP:5;                   // 4:0 Real Time Interrupt Stack Pointer
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint16_t MAXRTISP:5;                // 12:8 Maximum Real Time Interrupt Stack Pointer
    uint16_t rsvd2:3;                   // 15:13 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union PIPE_RTINT_SP_L_REG {
    uint32_t  all;
    struct  PIPE_RTINT_SP_L_BITS  bit;
};

struct PIPE_RTINT_SP_H_BITS {           // bits description
    uint16_t WARNRTISP:5;               // 4:0 Warning Real Time Interrupt Stack Pointer
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint16_t WARNRTISP_PRIO_LEVEL:8;    // 15:8 RTINT Stack Pointer warning priority level
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_RTINT_SP_H_REG {
    uint32_t  all;
    struct  PIPE_RTINT_SP_H_BITS  bit;
};

struct PIPE_RTISP_STS_BITS {            // bits description
    uint16_t WARNRTISP_STS:1;           // 0 RTINT Stack Pointer warning status
    uint16_t MAXRTISP_STS:1;            // 1 RTINT Stack Pointer max breach status
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_RTISP_STS_REG {
    uint32_t  all;
    struct  PIPE_RTISP_STS_BITS  bit;
};

struct PIPE_INTSP_BITS {                // bits description
    uint16_t INTSP:4;                   // 3:0 Interrupt Stack Pointer
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_INTSP_REG {
    uint32_t  all;
    struct  PIPE_INTSP_BITS  bit;
};

struct PIPE_LOCK_BITS {                 // bits description
    uint16_t LINK_LOCK:1;               // 0 Lock bit for link owner field
    uint16_t CONFIG_LOCK:1;             // 1 Lock bit for interrupt priority field
    uint16_t GLOBAL_LOCK:1;             // 2 Lock bit for common config regs
    uint16_t VECT_LOCK:1;               // 3 Lock bit for Vector memory
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_LOCK_REG {
    uint32_t  all;
    struct  PIPE_LOCK_BITS  bit;
};

struct PIPE_COMMIT_BITS {               // bits description
    uint16_t LINK_COMMIT:1;             // 0 Commit bit for link fields
    uint16_t CONFIG_COMMIT:1;           // 1 Commit bit for interrupt priority field
    uint16_t GLOBAL_COMMIT:1;           // 2 Commit bit for common config regs
    uint16_t VECT_COMMIT:1;             // 3 Commit bit for vector memory
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_COMMIT_REG {
    uint32_t  all;
    struct  PIPE_COMMIT_BITS  bit;
};

struct PIPE_TASK_CTRL_BITS {            // bits description
    uint16_t ACTIVE_CONTEXT_ID:2;       // 1:0 Active context ID for PIPE arbitration.
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t SUP_IGN_INTE_EN:1;         // 8 Supervisor Interrupt Enable
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_TASK_CTRL_REG {
    uint32_t  all;
    struct  PIPE_TASK_CTRL_BITS  bit;
};

struct PIPE_BOOT_LINK_CTRL_BITS {       // bits description
    uint16_t BOOT_LINK_LOCK:1;          // 0 Locks the Boot Link updates to configuration registers.
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_BOOT_LINK_CTRL_REG {
    uint32_t  all;
    struct  PIPE_BOOT_LINK_CTRL_BITS  bit;
};

struct PIPE_INT_VECT_MAPPING_BITS {     // bits description
    uint16_t LFU_INT_VECT_MAPPING:2;    // 1:0 Interrupt vector mapping to PPB for LFU support
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_INT_VECT_MAPPING_REG {
    uint32_t  all;
    struct  PIPE_INT_VECT_MAPPING_BITS  bit;
};

struct PIPE_MMR_CLR_BITS {              // bits description
    uint16_t MMR_CLR:2;                 // 1:0 PIPE MMR clear control
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_MMR_CLR_REG {
    uint32_t  all;
    struct  PIPE_MMR_CLR_BITS  bit;
};

struct PIPE_ALL_FLAG_CLR_BITS {         // bits description
    uint16_t ALL_FLAG_CLR:2;            // 1:0 Clears the Flags for all the interrupt lines.
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_ALL_FLAG_CLR_REG {
    uint32_t  all;
    struct  PIPE_ALL_FLAG_CLR_BITS  bit;
};

struct PIPE_REG_PARITY_DIAG_PARITY_BITS {// bits description
    uint16_t DIAG_PARITY_DATA:4;        // 3:0 Diagnostics parity data
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_REG_PARITY_DIAG_PARITY_REG {
    uint32_t  all;
    struct  PIPE_REG_PARITY_DIAG_PARITY_BITS  bit;
};

struct PIPE_REG_PARITY_DIAG_ASSERT_BITS {// bits description
    uint16_t DIAG_ASSERT:1;             // 0 Diagnostics assert
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_REG_PARITY_DIAG_ASSERT_REG {
    uint32_t  all;
    struct  PIPE_REG_PARITY_DIAG_ASSERT_BITS  bit;
};

struct PIPE_REG_PARITY_CHECK_BITS {     // bits description
    uint16_t MODE:4;                    // 3:0 Parity check mode
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_REG_PARITY_CHECK_REG {
    uint32_t  all;
    struct  PIPE_REG_PARITY_CHECK_BITS  bit;
};

struct PIPE_REG_PARITY_READ_BITS {      // bits description
    uint16_t PARITY_READ_EN:4;          // 3:0 Parity read enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t KEY:16;                    // 31:16 Key to enable write to lower [15:0] bit fields
};

union PIPE_REG_PARITY_READ_REG {
    uint32_t  all;
    struct  PIPE_REG_PARITY_READ_BITS  bit;
};

struct PIPE_INT_CTL_L_BITS {            // bits description
    uint16_t EN:1;                      // 0 INT enable
    uint16_t FLAG:1;                    // 1 INT FLAG status
    uint16_t OVERFLOW_FLAG:1;           // 2 INT_OVERFLOW_FLAG status
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_INT_CTL_L_REG {
    uint32_t  all;
    struct  PIPE_INT_CTL_L_BITS  bit;
};

struct PIPE_INT_CTL_H_BITS {            // bits description
    uint16_t FLAG_FRC:1;                // 0 INT SW set bit
    uint16_t FLAG_CLR:1;                // 1 INT_FLAG clear bit
    uint16_t OVERFLOW_FLAG_CLR:1;       // 2 INT_OVERFLOW_FLAG clear bit
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_INT_CTL_H_REG {
    uint32_t  all;
    struct  PIPE_INT_CTL_H_BITS  bit;
};

struct PIPE_INT_CONFIG_BITS {           // bits description
    uint16_t PRI_LEVEL:8;               // 7:0 Priority level
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t CONTEXT_ID:2;              // 17:16 Interrupt Context-ID
    uint16_t rsvd2:14;                  // 31:18 Reserved
};

union PIPE_INT_CONFIG_REG {
    uint32_t  all;
    struct  PIPE_INT_CONFIG_BITS  bit;
};

struct PIPE_INT_LINK_OWNER_BITS {       // bits description
    uint16_t OWNER_LINK:4;              // 3:0 Link owner for INT
    uint16_t API_LINK:4;                // 7:4 Access protection inheritance link for INT
    uint16_t API_LINK_EN:1;             // 8 Access protection inheritance link enable for INT
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_INT_LINK_OWNER_REG {
    uint32_t  all;
    struct  PIPE_INT_LINK_OWNER_BITS  bit;
};

struct PIPE_INT_LINK_OWNER_LFU_BITS {   // bits description
    uint16_t OWNER_LINK:4;              // 3:0 Link owner for INT for LFU
    uint16_t API_LINK:4;                // 7:4 Access protection inheritance link for INT for LFU
    uint16_t API_LINK_EN:1;             // 8 Access protection inheritance link enable for INT for LFU
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_INT_LINK_OWNER_LFU_REG {
    uint32_t  all;
    struct  PIPE_INT_LINK_OWNER_LFU_BITS  bit;
};

struct PIPE_SELFTEST_DIAG_DATA1_BITS {  // bits description
    uint32_t SELFTEST_DIAG_DATA1:20;    // 19:0 Self test Diagnostics data 1
    uint16_t rsvd1:12;                  // 31:20 Reserved
};

union PIPE_SELFTEST_DIAG_DATA1_REG {
    uint32_t  all;
    struct  PIPE_SELFTEST_DIAG_DATA1_BITS  bit;
};

struct PIPE_SELFTEST_DIAG_ECC_BITS {    // bits description
    uint16_t SELFTEST_DIAG_ECC:7;       // 6:0 Self test Diagnostics ECC
    uint16_t rsvd1:9;                   // 15:7 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PIPE_SELFTEST_DIAG_ECC_REG {
    uint32_t  all;
    struct  PIPE_SELFTEST_DIAG_ECC_BITS  bit;
};

struct PIPE_SELFTEST_DIAG_CONTROL_BITS {// bits description
    uint16_t DIAG_TEST_EN:4;            // 3:0 Diagnostic test enable
    uint16_t rsvd1:8;                   // 11:4 Reserved
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t DIAG_ECC_WIDTH:4;          // 19:16 Diagnostic ECC width
    uint16_t rsvd3:4;                   // 23:20 Reserved
    uint16_t DIAG_DATA_WIDTH:8;         // 31:24 Diagnostic Data width
};

union PIPE_SELFTEST_DIAG_CONTROL_REG {
    uint32_t  all;
    struct  PIPE_SELFTEST_DIAG_CONTROL_BITS  bit;
};

struct PIPE_SELFTEST_DIAG_STATUS_BITS { // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t DIAG_TEST_DONE:1;          // 1 Done self test
    uint16_t DIAG_TEST_FAIL:1;          // 2 Test failed
    uint16_t DIAG_FAIL_C_ERROR:1;       // 3 Diagnostic correctable error
    uint16_t DIAG_FAIL_UC_ERROR:1;      // 4 Diagnostic uncorrectable error
    uint16_t DIAG_FAIL_CHECK_TYPE:2;    // 6:5 Failed diagnostic check type
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t DIAG_FAIL_BIT_INDEX:8;     // 15:8 Error bit position
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union PIPE_SELFTEST_DIAG_STATUS_REG {
    uint32_t  all;
    struct  PIPE_SELFTEST_DIAG_STATUS_BITS  bit;
};

struct PIPE_SELFTEST_DIAG_STATUS_CLR_BITS {// bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t DIAG_TEST_DONE:1;          // 1 Clear self test done status flag
    uint16_t DIAG_TEST_FAIL:1;          // 2 Clear test failed status flags
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union PIPE_SELFTEST_DIAG_STATUS_CLR_REG {
    uint32_t  all;
    struct  PIPE_SELFTEST_DIAG_STATUS_CLR_BITS  bit;
};

struct PIPE_REGS {
    union   PIPE_RTINT_THRESHOLD_REG         RTINT_THRESHOLD;              // Interrupt threshold register
    union   PIPE_INT_GRP_MASK_REG            INT_GRP_MASK;                 // Interrupt group mask register
    union   PIPE_GLOBAL_EN_REG               GLOBAL_EN;                    // Global enable for INT and RTINT
    union   PIPE_REVISION_REG                REVISION;                     // Reserved
    uint8_t                                  rsvd1[16];                    // Reserved
    union   PIPE_CPU_INT_STS_REG             CPU_INT_STS;                  // CPU interrupt status
    uint32_t                                 RST_VECT;                     // Reset vector register
    union   PIPE_RST_LINK_OWNER_REG          RST_LINK_OWNER;               // Reset link owner register
    union   PIPE_NMI_STS_REG                 NMI_STS;                      // Non Maskable Interrupt status register
    uint32_t                                 NMI_VECT;                     // Non Maskable Interrupt vector register
    union   PIPE_NMI_LINK_OWNER_REG          NMI_LINK_OWNER;               // Non Maskable Interrupt link owner register
    uint8_t                                  rsvd2[8];                     // Reserved
    union   PIPE_MEM_ECC_DIAG_REG            MEM_ECC_DIAG;                 // ECC diagnostics register
    union   PIPE_MEM_INIT_REG                MEM_INIT;                     // PIPE vector memory initialization register
    union   PIPE_MEM_INIT_STS_REG            MEM_INIT_STS;                 // PIPE memory initialization status register
    union   PIPE_INT_SEC_STS_REG             INT_SEC_STS;                  // Interrupt security status register
    union   PIPE_INT_SEC_CLR_REG             INT_SEC_CLR;                  // Interrupt security clear register
    uint8_t                                  rsvd3[12];                    // Reserved
    union   PIPE_RTINT_SP_L_REG              RTINT_SP_L;                   // RTINT stack limit register
    union   PIPE_RTINT_SP_H_REG              RTINT_SP_H;                   // RTINT stack limit register
    union   PIPE_RTISP_STS_REG               RTISP_STS;                    // RTINT Stack pointer violation status register
    union   PIPE_INTSP_REG                   INTSP;                        // INT stack pointer
    uint8_t                                  rsvd4[16];                    // Reserved
    union   PIPE_LOCK_REG                    LOCK;                         // PIPE lock register
    union   PIPE_COMMIT_REG                  COMMIT;                       // PIPE commit register
    uint8_t                                  rsvd5[8];                     // Reserved
    union   PIPE_TASK_CTRL_REG               TASK_CTRL;                    // Task control register
    union   PIPE_BOOT_LINK_CTRL_REG          BOOT_LINK_CTRL;               // Boot Link control to lock out BOOT_LINK
    union   PIPE_INT_VECT_MAPPING_REG        INT_VECT_MAPPING;             // Interrupt vector mapping for LFU, FOTA, and INT vector swapping support
    uint8_t                                  rsvd6[4];                     // Reserved
    union   PIPE_MMR_CLR_REG                 MMR_CLR;                      // PIPE MMR clear register
    union   PIPE_ALL_FLAG_CLR_REG            ALL_FLAG_CLR;                 // PIPE flag clear register
    uint8_t                                  rsvd7[8];                     // Reserved
    uint32_t                                 REG_PARITY_DIAG_DATA;         // Register parity Diagnostic data
    uint8_t                                  rsvd8[4];                     // Reserved
    union   PIPE_REG_PARITY_DIAG_PARITY_REG  REG_PARITY_DIAG_PARITY;       // Register parity Diagnostic Parity
    uint8_t                                  rsvd9[4];                     // Reserved
    union   PIPE_REG_PARITY_DIAG_ASSERT_REG  REG_PARITY_DIAG_ASSERT;       // Register parity Assert diagnostic
    uint8_t                                  rsvd10[4];                    // Reserved
    union   PIPE_REG_PARITY_CHECK_REG        REG_PARITY_CHECK;             // Enabling the Parity check
    union   PIPE_REG_PARITY_READ_REG         REG_PARITY_READ;              // Enabling the Parity read
    uint8_t                                  rsvd11[3888];                 // Reserved
    union   PIPE_INT_CTL_L_REG               INT_CTL_L[256];               // Interrupt low flag and status control register
    uint8_t                                  rsvd12[3072];                 // Reserved
    union   PIPE_INT_CTL_H_REG               INT_CTL_H[256];               // Interrupt high flag and status control register
    uint8_t                                  rsvd13[3072];                 // Reserved
    union   PIPE_INT_CONFIG_REG              INT_CONFIG[256];              // Interrupt configuration register
    uint8_t                                  rsvd14[3072];                 // Reserved
    union   PIPE_INT_LINK_OWNER_REG          INT_LINK_OWNER[256];          // Interrupt link ownership config register
    uint8_t                                  rsvd15[3072];                 // Reserved
    uint32_t                                 INT_VECT_ADDR[256];           // Interrupt vector address
    uint8_t                                  rsvd16[3072];                 // Reserved
    union   PIPE_INT_LINK_OWNER_LFU_REG      INT_LINK_OWNER_LFU[256];      // Interrupt link ownership config register
    uint8_t                                  rsvd17[3072];                 // Reserved
    uint32_t                                 INT_VECT_ADDR_LFU[256];       // Interrupt vector address
    uint8_t                                  rsvd18[3072];                 // Reserved
    uint32_t                                 SELFTEST_DIAG_DATA0;          // Diagnostics data register 0
    union   PIPE_SELFTEST_DIAG_DATA1_REG     SELFTEST_DIAG_DATA1;          // Diagnostics data register 1
    uint8_t                                  rsvd19[24];                   // Reserved
    union   PIPE_SELFTEST_DIAG_ECC_REG       SELFTEST_DIAG_ECC;            // Diagnostics ECC
    uint8_t                                  rsvd20[4];                    // Reserved
    union   PIPE_SELFTEST_DIAG_CONTROL_REG   SELFTEST_DIAG_CONTROL;        // Diagnostic test enable.
    union   PIPE_SELFTEST_DIAG_STATUS_REG    SELFTEST_DIAG_STATUS;         // Diagnostic status register
    union   PIPE_SELFTEST_DIAG_STATUS_CLR_REG SELFTEST_DIAG_STATUS_CLR;    // Diagnostic status clear register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
