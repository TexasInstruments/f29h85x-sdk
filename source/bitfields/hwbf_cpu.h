//###########################################################################
//
// FILE:    hwbf_cpu.h
//
// TITLE:   Definitions for the CPU registers.
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

#ifndef HWBF_CPU_H
#define HWBF_CPU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// CPU Individual Register Bit Definitions:

struct CPU_RTINT_STACK_ECC0_BITS {      // bits description
    uint16_t RTINT_STACK_ECC0:8;        // 7:0 RTINT_STACK_ECC0
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_RTINT_STACK_ECC0_REG {
    uint32_t  all;
    struct  CPU_RTINT_STACK_ECC0_BITS  bit;
};

struct CPU_RTINT_STACK_ECC1_BITS {      // bits description
    uint16_t RTINT_STACK_ECC1:8;        // 7:0 RTINT_STACK_ECC1
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_RTINT_STACK_ECC1_REG {
    uint32_t  all;
    struct  CPU_RTINT_STACK_ECC1_BITS  bit;
};

struct CPU_RTINT_STACK_ECC2_BITS {      // bits description
    uint16_t RTINT_STACK_ECC2:8;        // 7:0 RTINT_STACK_ECC2
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_RTINT_STACK_ECC2_REG {
    uint32_t  all;
    struct  CPU_RTINT_STACK_ECC2_BITS  bit;
};

struct CPU_RTINT_STACK_ECC3_BITS {      // bits description
    uint16_t RTINT_STACK_ECC3:8;        // 7:0 RTINT_STACK_ECC3
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_RTINT_STACK_ECC3_REG {
    uint32_t  all;
    struct  CPU_RTINT_STACK_ECC3_BITS  bit;
};

struct C29_RTINT_STACK_RegisterFile0_REGS {
    uint32_t                                 RTINT_STACK_DATA0;            // RTINT stack Data0
    uint32_t                                 RTINT_STACK_DATA1;            // RTINT stack Data1
    uint32_t                                 RTINT_STACK_DATA2;            // RTINT stack Data2
    uint32_t                                 RTINT_STACK_DATA3;            // RTINT stack Data3
    uint32_t                                 RTINT_STACK_DATA4;            // RTINT stack Data4
    uint32_t                                 RTINT_STACK_DATA5;            // RTINT stack Data5
    uint32_t                                 RTINT_STACK_DATA6;            // RTINT stack Data6
    uint32_t                                 RTINT_STACK_DATA7;            // RTINT stack Data7
    uint32_t                                 RTINT_STACK_DATA8;            // RTINT stack Data8
    union   CPU_RTINT_STACK_ECC0_REG         RTINT_STACK_ECC0;             // RTINT stack ECC0
    union   CPU_RTINT_STACK_ECC1_REG         RTINT_STACK_ECC1;             // RTINT stack ECC1
    union   CPU_RTINT_STACK_ECC2_REG         RTINT_STACK_ECC2;             // RTINT stack ECC2
    union   CPU_RTINT_STACK_ECC3_REG         RTINT_STACK_ECC3;             // RTINT stack ECC3
    uint8_t                                  rsvd1[12];                    // Reserved
};

struct C29_RTINT_STACK {
    struct C29_RTINT_STACK_RegisterFile0_REGS C29_RTINT_STACK_RegisterFile0[128]; // 
};

struct CPU_SECCALL_STACK_DATA2_BITS {   // bits description
    uint16_t SECCALL_STACK_DATA2:4;     // 3:0 Secure call stack Data2
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_SECCALL_STACK_DATA2_REG {
    uint32_t  all;
    struct  CPU_SECCALL_STACK_DATA2_BITS  bit;
};

struct C29_SECCALL_STACK_RegisterFile0_REGS {
    uint32_t                                 SECCALL_STACK_DATA0;          // SECCALL stack Data0
    uint32_t                                 SECCALL_STACK_DATA1;          // SECCALL stack Data1
    union   CPU_SECCALL_STACK_DATA2_REG      SECCALL_STACK_DATA2;          // SECCALL stack Data2
    uint8_t                                  rsvd1[4];                     // Reserved
};

struct C29_SECCALL_STACK {
    struct C29_SECCALL_STACK_RegisterFile0_REGS C29_SECCALL_STACK_RegisterFile0[17]; // 
};

struct CPU_PSP_BITS {                   // bits description
    uint16_t PSP:12;                    // 11:0 Protected call stack pointer
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_PSP_REG {
    uint32_t  all;
    struct  CPU_PSP_BITS  bit;
};

struct CPU_WARNPSP_BITS {               // bits description
    uint16_t WARNPSP:12;                // 11:0 Warning level for protected call stack pointer
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_WARNPSP_REG {
    uint32_t  all;
    struct  CPU_WARNPSP_BITS  bit;
};

struct CPU_MAXPSP_BITS {                // bits description
    uint16_t MAXPSP:12;                 // 11:0 Maximum levels of protected calls supported by the HW
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_MAXPSP_REG {
    uint32_t  all;
    struct  CPU_MAXPSP_BITS  bit;
};

struct CPU_REVISION_BITS {              // bits description
    uint16_t MINREV:8;                  // 7:0 Minor Revision Number
    uint16_t MAJREV_Revision:3;         // 10:8 Major Revision Number
    uint16_t MAJREV_FPU64_PRESENT:1;    // 11 FPU64 Present
    uint16_t MAJREV_TMU64_PRESENT:1;    // 12 TMU64 Present
    uint16_t MAJREV_CPUCONFIG:3;        // 15:13 CPU configuration
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union CPU_REVISION_REG {
    uint32_t  all;
    struct  CPU_REVISION_BITS  bit;
};

struct CPU_C29_REGS_LOCK_BITS {         // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t C29_RTINT_STACK:1;         // 1 C29 RTINT stack registers Lock
    uint16_t C29_SECCALL_STACK:1;       // 2 C29 SECCALL stack registers Lock
    uint16_t C29_SECURE_REGS:1;         // 3 C29 SECURE registers Lock
    uint16_t C29_DIAG_REGS:1;           // 4 C29 DIAG registers Lock
    uint16_t C29_SELFTEST_REGS:1;       // 5 C29 Selftest registers Lock
    uint16_t rsvd2:10;                  // 15:6 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union CPU_C29_REGS_LOCK_REG {
    uint32_t  all;
    struct  CPU_C29_REGS_LOCK_BITS  bit;
};

struct CPU_C29_REGS_COMMIT_BITS {       // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t C29_RTINT_STACK:1;         // 1 C29 RTINT stack registers Commit
    uint16_t C29_SECCALL_STACK:1;       // 2 C29 SECCALL stack registers Commit
    uint16_t C29_SECURE_REGS:1;         // 3 C29 SECURE registers Commit
    uint16_t C29_DIAG_REGS:1;           // 4 C29 DIAG registers Commit
    uint16_t C29_SELFTEST_REGS:1;       // 5 C29 Selftest registers Commit
    uint16_t rsvd2:10;                  // 15:6 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union CPU_C29_REGS_COMMIT_REG {
    uint32_t  all;
    struct  CPU_C29_REGS_COMMIT_BITS  bit;
};

struct C29_SECURE_REGS {
    uint32_t                                 SECSP0;                       // Secure Stackpointer 0
    uint32_t                                 SECSP1;                       // Secure Stackpointer 1
    uint32_t                                 SECSP2;                       // Secure Stackpointer 2
    uint32_t                                 SECSP3;                       // Secure Stackpointer 3
    uint32_t                                 SECSP4;                       // Secure Stackpointer 4
    uint32_t                                 SECSP5;                       // Secure Stackpointer 5
    uint32_t                                 SECSP6;                       // Secure Stackpointer 6
    uint32_t                                 SECSP7;                       // Secure Stackpointer 7
    uint8_t                                  rsvd1[96];                    // Reserved
    union   CPU_PSP_REG                      PSP;                          // Protected call stack pointer
    union   CPU_WARNPSP_REG                  WARNPSP;                      // Warning level register for protected call stack pointer
    union   CPU_MAXPSP_REG                   MAXPSP;                       // Maximum levels of protected calls supported by the HW
    union   CPU_REVISION_REG                 REVISION;                     // IP revision id register
    union   CPU_C29_REGS_LOCK_REG            C29_REGS_LOCK;                // Lock register
    union   CPU_C29_REGS_COMMIT_REG          C29_REGS_COMMIT;              // Commit register
};

struct CPU_FLTEMU_CONFIG_BITS {         // bits description
    uint16_t ENABLE:1;                  // 0 Fault emulation enable
    uint16_t DBL_BIT_INJ_EN:1;          // 1 Double bit injection enable
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t KEY:8;                     // 15:8 Write Key
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_FLTEMU_CONFIG_REG {
    uint32_t  all;
    struct  CPU_FLTEMU_CONFIG_BITS  bit;
};

struct CPU_FLTEMU_ACCGRPSEL_BITS {      // bits description
    uint16_t CTRL_GROUP_SEL:8;          // 7:0 CTRL group selection
    uint16_t DATA_GROUP_SEL:8;          // 15:8 DATA READ1 control information bus selection
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union CPU_FLTEMU_ACCGRPSEL_REG {
    uint32_t  all;
    struct  CPU_FLTEMU_ACCGRPSEL_BITS  bit;
};

struct CPU_FLTEMU_BITSEL_BITS {         // bits description
    uint16_t BITSEL:7;                  // 6:0 Fault emulation bitselection
    uint16_t rsvd1:9;                   // 15:7 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_FLTEMU_BITSEL_REG {
    uint32_t  all;
    struct  CPU_FLTEMU_BITSEL_BITS  bit;
};

struct CPU_TMU_ROM_PAR_FORCE_BITS {     // bits description
    uint16_t TMU_ROM_PAR_FORCE:1;       // 0 Fault emulation enable
    uint16_t rsvd1:7;                   // 7:1 Reserved
    uint16_t KEY:8;                     // 15:8 Write Key
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_TMU_ROM_PAR_FORCE_REG {
    uint32_t  all;
    struct  CPU_TMU_ROM_PAR_FORCE_BITS  bit;
};

struct C29_DIAG_REGS {
    union   CPU_FLTEMU_CONFIG_REG            FLTEMU_CONFIG;                // Fault emulation configuration registerr
    union   CPU_FLTEMU_ACCGRPSEL_REG         FLTEMU_ACCGRPSEL;             // Fault emulation access information group selection register
    union   CPU_FLTEMU_BITSEL_REG            FLTEMU_BITSEL;                // Fault emulation bitsel
    uint32_t                                 FLTEMU_ADDR;                  // Fault emulation access address register
    union   CPU_TMU_ROM_PAR_FORCE_REG        TMU_ROM_PAR_FORCE;            // Force TMU ROM Parity error
};

struct CPU_SELFTEST_DIAG_ECC_BITS {     // bits description
    uint16_t SELFTEST_DIAG_ECC:8;       // 7:0 Self test Diagnostics ECC
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_SELFTEST_DIAG_ECC_REG {
    uint32_t  all;
    struct  CPU_SELFTEST_DIAG_ECC_BITS  bit;
};

struct CPU_SELFTEST_DIAG_CONTROL_BITS { // bits description
    uint16_t DIAG_TEST_EN:4;            // 3:0 Diagnostic test enable
    uint16_t DIAG_MICRO_STEP_MODE:1;    // 4 Diagnostic micro step mode
    uint16_t DIAG_ADDITIONAL_PIPELINE_EN:1; // 5 Additional pipeline enable
    uint16_t DIAG_SAFETY_SEL:1;         // 6 Diagnostic safetly selection
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t DIAG_CHECKER_SEL:4;        // 11:8 ECC checker selection
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t DIAG_ECC_WIDTH:4;          // 19:16 Diagnostic ECC width
    uint16_t rsvd3:4;                   // 23:20 Reserved
    uint16_t DIAG_DATA_WIDTH:8;         // 31:24 Diagnostic Data width
};

union CPU_SELFTEST_DIAG_CONTROL_REG {
    uint32_t  all;
    struct  CPU_SELFTEST_DIAG_CONTROL_BITS  bit;
};

struct CPU_SELFTEST_DIAG_STATUS_BITS {  // bits description
    uint16_t DIAG_MICROSTEP_DONE:1;     // 0 Done Micro step
    uint16_t DIAG_TEST_DONE:1;          // 1 Done self test
    uint16_t DIAG_TEST_FAIL:1;          // 2 Test failed
    uint16_t DIAG_FAIL_C_ERROR:1;       // 3 Diagnostic correctable error
    uint16_t DIAG_FAIL_UC_ERROR:1;      // 4 Diagnostic uncorrectable error
    uint16_t DIAG_FAIL_CHECK_TYPE:2;    // 6:5 Failed diagnostic check type
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t DIAG_FAIL_BIT_INDEX:8;     // 15:8 Error bit position
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_SELFTEST_DIAG_STATUS_REG {
    uint32_t  all;
    struct  CPU_SELFTEST_DIAG_STATUS_BITS  bit;
};

struct CPU_SELFTEST_DIAG_STATUS_CLR_BITS {// bits description
    uint16_t DIAG_MICROSTEP_DONE:1;     // 0 Clear micro step done status flag
    uint16_t DIAG_TEST_DONE:1;          // 1 Clear selftest done status flag
    uint16_t DIAG_TEST_FAIL:1;          // 2 Clear test failed status flags
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union CPU_SELFTEST_DIAG_STATUS_CLR_REG {
    uint32_t  all;
    struct  CPU_SELFTEST_DIAG_STATUS_CLR_BITS  bit;
};

struct C29_SELFTEST_REGS {
    uint32_t                                 SELFTEST_DIAG_DATA0;          // Diagnostics data register 0
    uint32_t                                 SELFTEST_DIAG_DATA1;          // Diagnostics data register 1
    uint32_t                                 SELFTEST_DIAG_DATA2;          // Diagnostics data register 2
    uint8_t                                  rsvd1[20];                    // Reserved
    union   CPU_SELFTEST_DIAG_ECC_REG        SELFTEST_DIAG_ECC;            // Diagnostics ECC
    uint8_t                                  rsvd2[4];                     // Reserved
    union   CPU_SELFTEST_DIAG_CONTROL_REG    SELFTEST_DIAG_CONTROL;        // Diagnostic test enable
    union   CPU_SELFTEST_DIAG_STATUS_REG     SELFTEST_DIAG_STATUS;         // Diagnostic status register
    union   CPU_SELFTEST_DIAG_STATUS_CLR_REG SELFTEST_DIAG_STATUS_CLR;     // Diagnostic status clear register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
