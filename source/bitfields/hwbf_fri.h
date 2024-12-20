//###########################################################################
//
// FILE:    hwbf_fri.h
//
// TITLE:   Definitions for the FRI registers.
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

#ifndef HWBF_FRI_H
#define HWBF_FRI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// FRI Individual Register Bit Definitions:

struct FRI_REVISION_BITS {              // bits description
    uint16_t MINREV:8;                  // 7:0 Minor Revision Number
    uint16_t MAJREV:8;                  // 15:8 Major Revision Number
    uint16_t rsvd1:8;                   // 23:16 Reserved
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union FRI_REVISION_REG {
    uint32_t  all;
    struct  FRI_REVISION_BITS  bit;
};

struct FRI_FRDCNTL_BITS {               // bits description
    uint16_t rsvd1:8;                   // 7:0 Reserved
    uint16_t RWAIT:4;                   // 11:8 Read Waitstate
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t rsvd3:8;                   // 23:16 Reserved
    uint16_t TRIMENGRRWAIT:4;           // 27:24 Read Waitstate of Trim and ENGR sectors
    uint16_t rsvd4:4;                   // 31:28 Reserved
};

union FRI_FRDCNTL_REG {
    uint32_t  all;
    struct  FRI_FRDCNTL_BITS  bit;
};

struct FRI_FRDCNTL_LOCK_BITS {          // bits description
    uint16_t LOCK:1;                    // 0 Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRDCNTL_LOCK_REG {
    uint32_t  all;
    struct  FRI_FRDCNTL_LOCK_BITS  bit;
};

struct FRI_FRDCNTL_COMMIT_BITS {        // bits description
    uint16_t COMMIT:1;                  // 0 FRDCNTL_LOCK Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRDCNTL_COMMIT_REG {
    uint32_t  all;
    struct  FRI_FRDCNTL_COMMIT_BITS  bit;
};

struct FRI_FRI1_INTF_CTRL_BITS {        // bits description
    uint16_t PREFETCH_EN:1;             // 0 Prefetch Enable
    uint16_t DATA_CACHE_EN:1;           // 1 Data Line Buffer Enable
    uint16_t CODE_CACHE_EN:1;           // 2 Code Cache Enable
    uint16_t DATA_PREREAD_EN:1;         // 3 Sequential Data Preread Mode Enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI1_INTF_CTRL_REG {
    uint32_t  all;
    struct  FRI_FRI1_INTF_CTRL_BITS  bit;
};

struct FRI_FRI1_INTF_CTRL_LOCK_BITS {   // bits description
    uint16_t LOCK:1;                    // 0 Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI1_INTF_CTRL_LOCK_REG {
    uint32_t  all;
    struct  FRI_FRI1_INTF_CTRL_LOCK_BITS  bit;
};

struct FRI_FRI1_INTF_CTRL_COMMIT_BITS { // bits description
    uint16_t COMMIT:1;                  // 0 FRD_INTF_CTRL_LOCK Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI1_INTF_CTRL_COMMIT_REG {
    uint32_t  all;
    struct  FRI_FRI1_INTF_CTRL_COMMIT_BITS  bit;
};

struct FRI_FRI1_INTF_CLR_BITS {         // bits description
    uint16_t PREFETCH_CLR:1;            // 0 Prefetch Clear
    uint16_t DATA_CACHE_CLR:1;          // 1 Data Line Buffer Clear
    uint16_t CODE_CACHE_CLR:1;          // 2 Code Cache Clear
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI1_INTF_CLR_REG {
    uint32_t  all;
    struct  FRI_FRI1_INTF_CLR_BITS  bit;
};

struct FRI_FRI2_INTF_CTRL_BITS {        // bits description
    uint16_t PREFETCH_EN:1;             // 0 Prefetch Enable
    uint16_t DATA_CACHE_EN:1;           // 1 Data Line Buffer Enable
    uint16_t CODE_CACHE_EN:1;           // 2 Code Cache Enable
    uint16_t DATA_PREREAD_EN:1;         // 3 Sequential Data Preread Mode Enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI2_INTF_CTRL_REG {
    uint32_t  all;
    struct  FRI_FRI2_INTF_CTRL_BITS  bit;
};

struct FRI_FRI2_INTF_CTRL_LOCK_BITS {   // bits description
    uint16_t LOCK:1;                    // 0 Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI2_INTF_CTRL_LOCK_REG {
    uint32_t  all;
    struct  FRI_FRI2_INTF_CTRL_LOCK_BITS  bit;
};

struct FRI_FRI2_INTF_CTRL_COMMIT_BITS { // bits description
    uint16_t COMMIT:1;                  // 0 FRD_INTF_CTRL_LOCK Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI2_INTF_CTRL_COMMIT_REG {
    uint32_t  all;
    struct  FRI_FRI2_INTF_CTRL_COMMIT_BITS  bit;
};

struct FRI_FRI2_INTF_CLR_BITS {         // bits description
    uint16_t PREFETCH_CLR:1;            // 0 Prefetch Clear
    uint16_t DATA_CACHE_CLR:1;          // 1 Data Line Buffer Clear
    uint16_t CODE_CACHE_CLR:1;          // 2 Code Cache Clear
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI2_INTF_CLR_REG {
    uint32_t  all;
    struct  FRI_FRI2_INTF_CLR_BITS  bit;
};

struct FRI_FRI3_INTF_CTRL_BITS {        // bits description
    uint16_t PREFETCH_EN:1;             // 0 Prefetch Enable
    uint16_t DATA_CACHE_EN:1;           // 1 Data Line Buffer Enable
    uint16_t CODE_CACHE_EN:1;           // 2 Code Cache Enable
    uint16_t DATA_PREREAD_EN:1;         // 3 Sequential Data Preread Mode Enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI3_INTF_CTRL_REG {
    uint32_t  all;
    struct  FRI_FRI3_INTF_CTRL_BITS  bit;
};

struct FRI_FRI3_INTF_CTRL_LOCK_BITS {   // bits description
    uint16_t LOCK:1;                    // 0 Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI3_INTF_CTRL_LOCK_REG {
    uint32_t  all;
    struct  FRI_FRI3_INTF_CTRL_LOCK_BITS  bit;
};

struct FRI_FRI3_INTF_CTRL_COMMIT_BITS { // bits description
    uint16_t COMMIT:1;                  // 0 FRD_INTF_CTRL_LOCK Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI3_INTF_CTRL_COMMIT_REG {
    uint32_t  all;
    struct  FRI_FRI3_INTF_CTRL_COMMIT_BITS  bit;
};

struct FRI_FRI3_INTF_CLR_BITS {         // bits description
    uint16_t PREFETCH_CLR:1;            // 0 Prefetch Clear
    uint16_t DATA_CACHE_CLR:1;          // 1 Data Line Buffer Clear
    uint16_t CODE_CACHE_CLR:1;          // 2 Code Cache Clear
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI3_INTF_CLR_REG {
    uint32_t  all;
    struct  FRI_FRI3_INTF_CLR_BITS  bit;
};

struct FRI_FRI4_INTF_CTRL_BITS {        // bits description
    uint16_t PREFETCH_EN:1;             // 0 Prefetch Enable
    uint16_t DATA_CACHE_EN:1;           // 1 Data Line Buffer Enable
    uint16_t CODE_CACHE_EN:1;           // 2 Code Cache Enable
    uint16_t DATA_PREREAD_EN:1;         // 3 Sequential Data Preread Mode Enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI4_INTF_CTRL_REG {
    uint32_t  all;
    struct  FRI_FRI4_INTF_CTRL_BITS  bit;
};

struct FRI_FRI4_INTF_CTRL_LOCK_BITS {   // bits description
    uint16_t LOCK:1;                    // 0 Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI4_INTF_CTRL_LOCK_REG {
    uint32_t  all;
    struct  FRI_FRI4_INTF_CTRL_LOCK_BITS  bit;
};

struct FRI_FRI4_INTF_CTRL_COMMIT_BITS { // bits description
    uint16_t COMMIT:1;                  // 0 FRD_INTF_CTRL_LOCK Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI4_INTF_CTRL_COMMIT_REG {
    uint32_t  all;
    struct  FRI_FRI4_INTF_CTRL_COMMIT_BITS  bit;
};

struct FRI_FRI4_INTF_CLR_BITS {         // bits description
    uint16_t PREFETCH_CLR:1;            // 0 Prefetch Clear
    uint16_t DATA_CACHE_CLR:1;          // 1 Data Line Buffer Clear
    uint16_t CODE_CACHE_CLR:1;          // 2 Code Cache Clear
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_FRI4_INTF_CLR_REG {
    uint32_t  all;
    struct  FRI_FRI4_INTF_CLR_BITS  bit;
};

struct FRI_PARITY_TEST_BITS {           // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity Test Enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_PARITY_TEST_REG {
    uint32_t  all;
    struct  FRI_PARITY_TEST_BITS  bit;
};

struct FRI_PARITY_TEST_LOCK_BITS {      // bits description
    uint16_t LOCK:1;                    // 0 Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_PARITY_TEST_LOCK_REG {
    uint32_t  all;
    struct  FRI_PARITY_TEST_LOCK_BITS  bit;
};

struct FRI_PARITY_TEST_COMMIT_BITS {    // bits description
    uint16_t COMMIT:1;                  // 0 PARITY_TEST_LOCK Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union FRI_PARITY_TEST_COMMIT_REG {
    uint32_t  all;
    struct  FRI_PARITY_TEST_COMMIT_BITS  bit;
};

struct FRI_CTRL_REGS {
    union   FRI_REVISION_REG                 REVISION;                     // IP Revision Register
    uint8_t                                  rsvd1[12];                    // Reserved
    union   FRI_FRDCNTL_REG                  FRDCNTL;                      // Flash Read Control Register
    union   FRI_FRDCNTL_LOCK_REG             FRDCNTL_LOCK;                 // Flash Read Control Lock Register
    union   FRI_FRDCNTL_COMMIT_REG           FRDCNTL_COMMIT;               // Flash Read Control Commit Register
    uint8_t                                  rsvd2[20];                    // Reserved
    union   FRI_FRI1_INTF_CTRL_REG           FRI1_INTF_CTRL;               // Flash Read Interface 1 Control Register
    union   FRI_FRI1_INTF_CTRL_LOCK_REG      FRI1_INTF_CTRL_LOCK;          // Flash Read Interface 1 Control Lock Register
    union   FRI_FRI1_INTF_CTRL_COMMIT_REG    FRI1_INTF_CTRL_COMMIT;        // Flash Read Interface 1 Control Commit Register
    union   FRI_FRI1_INTF_CLR_REG            FRI1_INTF_CLR;                // Flash Read Interface 1 Clear Register
    union   FRI_FRI2_INTF_CTRL_REG           FRI2_INTF_CTRL;               // Flash Read Interface 2 Control Register
    union   FRI_FRI2_INTF_CTRL_LOCK_REG      FRI2_INTF_CTRL_LOCK;          // Flash Read Interface 2 Control Lock Register
    union   FRI_FRI2_INTF_CTRL_COMMIT_REG    FRI2_INTF_CTRL_COMMIT;        // Flash Read Interface 2 Control Commit Register
    union   FRI_FRI2_INTF_CLR_REG            FRI2_INTF_CLR;                // Flash Read Interface 2 Clear Register
    union   FRI_FRI3_INTF_CTRL_REG           FRI3_INTF_CTRL;               // Flash Read Interface 3 Control Register
    union   FRI_FRI3_INTF_CTRL_LOCK_REG      FRI3_INTF_CTRL_LOCK;          // Flash Read Interface 3 Control Lock Register
    union   FRI_FRI3_INTF_CTRL_COMMIT_REG    FRI3_INTF_CTRL_COMMIT;        // Flash Read Interface 3 Control Commit Register
    union   FRI_FRI3_INTF_CLR_REG            FRI3_INTF_CLR;                // Flash Read Interface 3 Clear Register
    union   FRI_FRI4_INTF_CTRL_REG           FRI4_INTF_CTRL;               // Flash Read Interface 4 Control Register
    union   FRI_FRI4_INTF_CTRL_LOCK_REG      FRI4_INTF_CTRL_LOCK;          // Flash Read Interface 4 Control Lock Register
    union   FRI_FRI4_INTF_CTRL_COMMIT_REG    FRI4_INTF_CTRL_COMMIT;        // Flash Read Interface 4 Control Commit Register
    union   FRI_FRI4_INTF_CLR_REG            FRI4_INTF_CLR;                // Flash Read Interface 4 Clear Register
    union   FRI_PARITY_TEST_REG              PARITY_TEST;                  // Parity Test Enable
    union   FRI_PARITY_TEST_LOCK_REG         PARITY_TEST_LOCK;             // Parity Test Lock Register
    union   FRI_PARITY_TEST_COMMIT_REG       PARITY_TEST_COMMIT;           // Parity Test Commit Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
