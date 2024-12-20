//###########################################################################
//
// FILE:    hwbf_tmu.h
//
// TITLE:   Definitions for the TMU registers.
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

#ifndef HWBF_TMU_H
#define HWBF_TMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// TMU Individual Register Bit Definitions:

struct TMU_REVISION_BITS {              // bits description
    uint16_t MINOR:6;                   // 5:0 Minor Revision Number
    uint16_t CUSTOM:2;                  // 7:6 Custom Module Number
    uint16_t MAJOR:3;                   // 10:8 Major Revision Number
    uint16_t rsvd1:5;                   // 15:11 Reserved
    uint16_t FUNC:12;                   // 27:16 Functional Release Number
    uint16_t rsvd2:2;                   // 29:28 Reserved
    uint16_t SCHEME:2;                  // 31:30 Defines Scheme for Module
};

union TMU_REVISION_REG {
    uint32_t  all;
    struct  TMU_REVISION_BITS  bit;
};

struct TMU_CONTEXT_SAVE_BITS {          // bits description
    uint16_t SAVE:1;                    // 0 Initiates context save of result registers
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union TMU_CONTEXT_SAVE_REG {
    uint32_t  all;
    struct  TMU_CONTEXT_SAVE_BITS  bit;
};

struct TMU_CONTEXT_RESTORE_BITS {       // bits description
    uint16_t RESTORE:1;                 // 0 Initiates context restore of result registers
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union TMU_CONTEXT_RESTORE_REG {
    uint32_t  all;
    struct  TMU_CONTEXT_RESTORE_BITS  bit;
};

struct TMU_STF_BITS {                   // bits description
    uint16_t LVF:1;                     // 0 LVF  Status
    uint16_t LUF:1;                     // 1 LUF Status
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t LVF_WR_EN:1;               // 8 LVF  write enable
    uint16_t LUF_WR_EN:1;               // 9 LVF  write enable
    uint16_t rsvd2:6;                   // 15:10 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union TMU_STF_REG {
    uint32_t  all;
    struct  TMU_STF_BITS  bit;
};

struct TMU_PARITY_TEST_BITS {           // bits description
    uint16_t testen:4;                  // 3:0 Parity test enable configuration
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union TMU_PARITY_TEST_REG {
    uint32_t  all;
    struct  TMU_PARITY_TEST_BITS  bit;
};

struct TMU_LCM_LOCK_BITS {              // bits description
    uint16_t PARITY_TEST:1;             // 0 Register lock configuration
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union TMU_LCM_LOCK_REG {
    uint32_t  all;
    struct  TMU_LCM_LOCK_BITS  bit;
};

struct TMU_LCM_COMMIT_BITS {            // bits description
    uint16_t PARITY_TEST:1;             // 0 Register commit configuration
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union TMU_LCM_COMMIT_REG {
    uint32_t  all;
    struct  TMU_LCM_COMMIT_BITS  bit;
};

struct CLA_TMU_REGS {
    union   TMU_REVISION_REG                 REVISION;                     // IP revision id register
    uint8_t                                  rsvd1[28];                    // Reserved
    uint32_t                                 SINPUF32_R0;                  // Updates operand 1 for SINPUF32 operation
    uint32_t                                 SINPUF32_R1;                  // Updates operand 1 for SINPUF32 operation
    uint32_t                                 SINPUF32_R2;                  // Updates operand 1 for SINPUF32 operation
    uint32_t                                 SINPUF32_R3;                  // Updates operand 1 for SINPUF32 operation
    uint32_t                                 SINPUF32_R4;                  // Updates operand 1 for SINPUF32 operation
    uint32_t                                 SINPUF32_R5;                  // Updates operand 1 for SINPUF32 operation
    uint32_t                                 SINPUF32_R6;                  // Updates operand 1 for SINPUF32 operation
    uint32_t                                 SINPUF32_R7;                  // Updates operand 1 for SINPUF32 operation
    uint32_t                                 COSPUF32_R0;                  // Updates operand 1 for COSPUF32 operation
    uint32_t                                 COSPUF32_R1;                  // Updates operand 1 for COSPUF32 operation
    uint32_t                                 COSPUF32_R2;                  // Updates operand 1 for COSPUF32 operation
    uint32_t                                 COSPUF32_R3;                  // Updates operand 1 for COSPUF32 operation
    uint32_t                                 COSPUF32_R4;                  // Updates operand 1 for COSPUF32 operation
    uint32_t                                 COSPUF32_R5;                  // Updates operand 1 for COSPUF32 operation
    uint32_t                                 COSPUF32_R6;                  // Updates operand 1 for COSPUF32 operation
    uint32_t                                 COSPUF32_R7;                  // Updates operand 1 for COSPUF32 operation
    uint32_t                                 ATANPUF32_R0;                 // Updates operand 1 for ATANPUF32 operation
    uint32_t                                 ATANPUF32_R1;                 // Updates operand 1 for ATANPUF32 operation
    uint32_t                                 ATANPUF32_R2;                 // Updates operand 1 for ATANPUF32 operation
    uint32_t                                 ATANPUF32_R3;                 // Updates operand 1 for ATANPUF32 operation
    uint32_t                                 ATANPUF32_R4;                 // Updates operand 1 for ATANPUF32 operation
    uint32_t                                 ATANPUF32_R5;                 // Updates operand 1 for ATANPUF32 operation
    uint32_t                                 ATANPUF32_R6;                 // Updates operand 1 for ATANPUF32 operation
    uint32_t                                 ATANPUF32_R7;                 // Updates operand 1 for ATANPUF32 operation
    uint32_t                                 SQRTF32_R0;                   // Updates operand 1 for SQRTF32 operation
    uint32_t                                 SQRTF32_R1;                   // Updates operand 1 for SQRTF32 operation
    uint32_t                                 SQRTF32_R2;                   // Updates operand 1 for SQRTF32 operation
    uint32_t                                 SQRTF32_R3;                   // Updates operand 1 for SQRTF32 operation
    uint32_t                                 SQRTF32_R4;                   // Updates operand 1 for SQRTF32 operation
    uint32_t                                 SQRTF32_R5;                   // Updates operand 1 for SQRTF32 operation
    uint32_t                                 SQRTF32_R6;                   // Updates operand 1 for SQRTF32 operation
    uint32_t                                 SQRTF32_R7;                   // Updates operand 1 for SQRTF32 operation
    uint32_t                                 IEXP2F32_R0;                  // Updates operand 1 for IEXP2F32 operation
    uint32_t                                 IEXP2F32_R1;                  // Updates operand 1 for IEXP2F32 operation
    uint32_t                                 IEXP2F32_R2;                  // Updates operand 1 for IEXP2F32 operation
    uint32_t                                 IEXP2F32_R3;                  // Updates operand 1 for IEXP2F32 operation
    uint32_t                                 IEXP2F32_R4;                  // Updates operand 1 for IEXP2F32 operation
    uint32_t                                 IEXP2F32_R5;                  // Updates operand 1 for IEXP2F32 operation
    uint32_t                                 IEXP2F32_R6;                  // Updates operand 1 for IEXP2F32 operation
    uint32_t                                 IEXP2F32_R7;                  // Updates operand 1 for IEXP2F32 operation
    uint32_t                                 LOG2F32_R0;                   // Updates operand 1 for LOG2F32 operation
    uint32_t                                 LOG2F32_R1;                   // Updates operand 1 for LOG2F32 operation
    uint32_t                                 LOG2F32_R2;                   // Updates operand 1 for LOG2F32 operation
    uint32_t                                 LOG2F32_R3;                   // Updates operand 1 for LOG2F32 operation
    uint32_t                                 LOG2F32_R4;                   // Updates operand 1 for LOG2F32 operation
    uint32_t                                 LOG2F32_R5;                   // Updates operand 1 for LOG2F32 operation
    uint32_t                                 LOG2F32_R6;                   // Updates operand 1 for LOG2F32 operation
    uint32_t                                 LOG2F32_R7;                   // Updates operand 1 for LOG2F32 operation
    uint32_t                                 QUADF32_X_R0_R1;              // Updates operand 1 for QUADF32 operation
    uint32_t                                 QUADF32_X_R1_R2;              // Updates operand 1 for QUADF32 operation
    uint32_t                                 QUADF32_X_R2_R3;              // Updates operand 1 for QUADF32 operation
    uint32_t                                 QUADF32_X_R3_R4;              // Updates operand 1 for QUADF32 operation
    uint32_t                                 QUADF32_X_R4_R5;              // Updates operand 1 for QUADF32 operation
    uint32_t                                 QUADF32_X_R5_R6;              // Updates operand 1 for QUADF32 operation
    uint32_t                                 QUADF32_X_R6_R7;              // Updates operand 1 for QUADF32 operation
    uint8_t                                  rsvd2[4];                     // Reserved
    uint32_t                                 DIVF32_N_R0;                  // Updates operand 1 for DIVF32 operation
    uint32_t                                 DIVF32_N_R1;                  // Updates operand 1 for DIVF32 operation
    uint32_t                                 DIVF32_N_R2;                  // Updates operand 1 for DIVF32 operation
    uint32_t                                 DIVF32_N_R3;                  // Updates operand 1 for DIVF32 operation
    uint32_t                                 DIVF32_N_R4;                  // Updates operand 1 for DIVF32 operation
    uint32_t                                 DIVF32_N_R5;                  // Updates operand 1 for DIVF32 operation
    uint32_t                                 DIVF32_N_R6;                  // Updates operand 1 for DIVF32 operation
    uint32_t                                 DIVF32_N_R7;                  // Updates operand 1 for DIVF32 operation
    uint32_t                                 QUADF32_DIVF32_OP2;           // Updates operand 2 for QUADF32 and DIVF32 operation
    uint8_t                                  rsvd3[28];                    // Reserved
    uint32_t                                 RESULT_R0;                    // R0 result register
    uint32_t                                 RESULT_R1;                    // R1 result register
    uint32_t                                 RESULT_R2;                    // R2 result register
    uint32_t                                 RESULT_R3;                    // R3 result register
    uint32_t                                 RESULT_R4;                    // R4 result register
    uint32_t                                 RESULT_R5;                    // R5 result register
    uint32_t                                 RESULT_R6;                    // R6 result register
    uint32_t                                 RESULT_R7;                    // R7 result register
    uint32_t                                 CSAVE_R0;                     // Context save of R0 result register
    uint32_t                                 CSAVE_R1;                     // Context save of R1 result register
    uint32_t                                 CSAVE_R2;                     // Context save of R2 result register
    uint32_t                                 CSAVE_R3;                     // Context save of R3 result register
    uint32_t                                 CSAVE_R4;                     // Context save of R4 result register
    uint32_t                                 CSAVE_R5;                     // Context save of R5 result register
    uint32_t                                 CSAVE_R6;                     // Context save of R6 result register
    uint32_t                                 CSAVE_R7;                     // Context save of R7 result register
    uint32_t                                 CSAVE_OP2;                    // Context save of Operarand2 result register
    union   TMU_CONTEXT_SAVE_REG             CONTEXT_SAVE;                 // Register to initiate context save of result registers
    union   TMU_CONTEXT_RESTORE_REG          CONTEXT_RESTORE;              // Register to initiate context restore of result registers
    uint8_t                                  rsvd4[24];                    // Reserved
    union   TMU_STF_REG                      STF;                          // TMU status Register
    uint8_t                                  rsvd5[24];                    // Reserved
    union   TMU_PARITY_TEST_REG              PARITY_TEST;                  // Enabling the parity test feature
    uint8_t                                  rsvd6[4];                     // Reserved
    union   TMU_LCM_LOCK_REG                 LCM_LOCK;                     // LCM lock configuration
    uint8_t                                  rsvd7[4];                     // Reserved
    union   TMU_LCM_COMMIT_REG               LCM_COMMIT;                   // LCM commit configuration
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
