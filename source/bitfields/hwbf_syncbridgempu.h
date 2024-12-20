//###########################################################################
//
// FILE:    hwbf_syncbridgempu.h
//
// TITLE:   Definitions for the SYNCBRIDGEMPU registers.
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

#ifndef HWBF_SYNCBRIDGEMPU_H
#define HWBF_SYNCBRIDGEMPU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// SYNCBRIDGEMPU Individual Register Bit Definitions:

struct SYNCBRIDGEMPU_MPUR1_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR1_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR1_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR1_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR1_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR1_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR1_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR1_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR1_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR1_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR1_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR1_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR1_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR1_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR1_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR2_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR2_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR2_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR2_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR2_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR2_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR2_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR2_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR2_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR2_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR2_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR2_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR2_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR2_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR2_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR3_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR3_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR3_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR3_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR3_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR3_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR3_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR3_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR3_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR3_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR3_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR3_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR3_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR3_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR3_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR4_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR4_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR4_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR4_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR4_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR4_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR4_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR4_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR4_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR4_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR4_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR4_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR4_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR4_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR4_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR5_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR5_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR5_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR5_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR5_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR5_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR5_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR5_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR5_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR5_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR5_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR5_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR5_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR5_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR5_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR6_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR6_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR6_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR6_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR6_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR6_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR6_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR6_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR6_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR6_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR6_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR6_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR6_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR6_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR6_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR7_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR7_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR7_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR7_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR7_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR7_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR7_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR7_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR7_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR7_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR7_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR7_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR7_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR7_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR7_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR8_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR8_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR8_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR8_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR8_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR8_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR8_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR8_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR8_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR8_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR8_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR8_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR8_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR8_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR8_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR9_START_BITS { // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR9_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR9_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR9_END_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR9_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR9_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR9_LOCK_BITS {  // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR9_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR9_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR9_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR9_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR9_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR9_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR9_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR9_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR10_START_BITS {// bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR10_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR10_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR10_END_BITS {  // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR10_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR10_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR10_LOCK_BITS { // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR10_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR10_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR10_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR10_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR10_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR10_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR10_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR10_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR11_START_BITS {// bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR11_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR11_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR11_END_BITS {  // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR11_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR11_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR11_LOCK_BITS { // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR11_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR11_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR11_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR11_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR11_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR11_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR11_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR11_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR12_START_BITS {// bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR12_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR12_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR12_END_BITS {  // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR12_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR12_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR12_LOCK_BITS { // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR12_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR12_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR12_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR12_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR12_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR12_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR12_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR12_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR13_START_BITS {// bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR13_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR13_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR13_END_BITS {  // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR13_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR13_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR13_LOCK_BITS { // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR13_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR13_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR13_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR13_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR13_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR13_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR13_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR13_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR14_START_BITS {// bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR14_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR14_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR14_END_BITS {  // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR14_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR14_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR14_LOCK_BITS { // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR14_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR14_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR14_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR14_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR14_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR14_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR14_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR14_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR15_START_BITS {// bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR15_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR15_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR15_END_BITS {  // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR15_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR15_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR15_LOCK_BITS { // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR15_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR15_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR15_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR15_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR15_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR15_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR15_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR15_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR16_START_BITS {// bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union SYNCBRIDGEMPU_MPUR16_START_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR16_START_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR16_END_BITS {  // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union SYNCBRIDGEMPU_MPUR16_END_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR16_END_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR16_LOCK_BITS { // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR16_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR16_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR16_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR16_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR16_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUR16_ACCESS_BITS {// bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUR16_ACCESS_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUR16_ACCESS_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUCTRL_BITS {     // bits description
    uint16_t MPUEN:1;                   // 0 Enable MPU function
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUCTRL_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUCTRL_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUCFG_LOCK_BITS { // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUCFG_LOCK_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUCFG_LOCK_BITS  bit;
};

struct SYNCBRIDGEMPU_MPUCFG_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYNCBRIDGEMPU_MPUCFG_COMMIT_REG {
    uint32_t  all;
    struct  SYNCBRIDGEMPU_MPUCFG_COMMIT_BITS  bit;
};

struct SYNCBRIDGEMPU_REGS {
    union   SYNCBRIDGEMPU_MPUR1_START_REG    MPUR1_START;                  // MPU Region 1 Start Address
    union   SYNCBRIDGEMPU_MPUR1_END_REG      MPUR1_END;                    // MPU Region 1 End Address
    union   SYNCBRIDGEMPU_MPUR1_LOCK_REG     MPUR1_LOCK;                   // MPU 1 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR1_COMMIT_REG   MPUR1_COMMIT;                 // MPU 1 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR1_ACCESS_REG   MPUR1_ACCESS;                 // MPU Region 1 R/W Access Permissions
    uint8_t                                  rsvd1[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR2_START_REG    MPUR2_START;                  // MPU Region 2 Start Address
    union   SYNCBRIDGEMPU_MPUR2_END_REG      MPUR2_END;                    // MPU Region 2 End Address
    union   SYNCBRIDGEMPU_MPUR2_LOCK_REG     MPUR2_LOCK;                   // MPU 2 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR2_COMMIT_REG   MPUR2_COMMIT;                 // MPU 2 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR2_ACCESS_REG   MPUR2_ACCESS;                 // MPU Region 2 R/W Access Permissions
    uint8_t                                  rsvd2[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR3_START_REG    MPUR3_START;                  // MPU Region 3 Start Address
    union   SYNCBRIDGEMPU_MPUR3_END_REG      MPUR3_END;                    // MPU Region 3 End Address
    union   SYNCBRIDGEMPU_MPUR3_LOCK_REG     MPUR3_LOCK;                   // MPU 3 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR3_COMMIT_REG   MPUR3_COMMIT;                 // MPU 3 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR3_ACCESS_REG   MPUR3_ACCESS;                 // MPU Region 3 R/W Access Permissions
    uint8_t                                  rsvd3[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR4_START_REG    MPUR4_START;                  // MPU Region 4 Start Address
    union   SYNCBRIDGEMPU_MPUR4_END_REG      MPUR4_END;                    // MPU Region 4 End Address
    union   SYNCBRIDGEMPU_MPUR4_LOCK_REG     MPUR4_LOCK;                   // MPU 4 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR4_COMMIT_REG   MPUR4_COMMIT;                 // MPU 4 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR4_ACCESS_REG   MPUR4_ACCESS;                 // MPU Region 4 R/W Access Permissions
    uint8_t                                  rsvd4[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR5_START_REG    MPUR5_START;                  // MPU Region 5 Start Address
    union   SYNCBRIDGEMPU_MPUR5_END_REG      MPUR5_END;                    // MPU Region 5 End Address
    union   SYNCBRIDGEMPU_MPUR5_LOCK_REG     MPUR5_LOCK;                   // MPU 5 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR5_COMMIT_REG   MPUR5_COMMIT;                 // MPU 5 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR5_ACCESS_REG   MPUR5_ACCESS;                 // MPU Region 5 R/W Access Permissions
    uint8_t                                  rsvd5[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR6_START_REG    MPUR6_START;                  // MPU Region 6 Start Address
    union   SYNCBRIDGEMPU_MPUR6_END_REG      MPUR6_END;                    // MPU Region 6 End Address
    union   SYNCBRIDGEMPU_MPUR6_LOCK_REG     MPUR6_LOCK;                   // MPU 6 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR6_COMMIT_REG   MPUR6_COMMIT;                 // MPU 6 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR6_ACCESS_REG   MPUR6_ACCESS;                 // MPU Region 6 R/W Access Permissions
    uint8_t                                  rsvd6[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR7_START_REG    MPUR7_START;                  // MPU Region 7 Start Address
    union   SYNCBRIDGEMPU_MPUR7_END_REG      MPUR7_END;                    // MPU Region 7 End Address
    union   SYNCBRIDGEMPU_MPUR7_LOCK_REG     MPUR7_LOCK;                   // MPU 7 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR7_COMMIT_REG   MPUR7_COMMIT;                 // MPU 7 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR7_ACCESS_REG   MPUR7_ACCESS;                 // MPU Region 7 R/W Access Permissions
    uint8_t                                  rsvd7[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR8_START_REG    MPUR8_START;                  // MPU Region 8 Start Address
    union   SYNCBRIDGEMPU_MPUR8_END_REG      MPUR8_END;                    // MPU Region 8 End Address
    union   SYNCBRIDGEMPU_MPUR8_LOCK_REG     MPUR8_LOCK;                   // MPU 8 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR8_COMMIT_REG   MPUR8_COMMIT;                 // MPU 8 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR8_ACCESS_REG   MPUR8_ACCESS;                 // MPU Region 8 R/W Access Permissions
    uint8_t                                  rsvd8[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR9_START_REG    MPUR9_START;                  // MPU Region 9 Start Address
    union   SYNCBRIDGEMPU_MPUR9_END_REG      MPUR9_END;                    // MPU Region 9 End Address
    union   SYNCBRIDGEMPU_MPUR9_LOCK_REG     MPUR9_LOCK;                   // MPU 9 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR9_COMMIT_REG   MPUR9_COMMIT;                 // MPU 9 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR9_ACCESS_REG   MPUR9_ACCESS;                 // MPU Region 9 R/W Access Permissions
    uint8_t                                  rsvd9[12];                    // Reserved
    union   SYNCBRIDGEMPU_MPUR10_START_REG   MPUR10_START;                 // MPU Region 10 Start Address
    union   SYNCBRIDGEMPU_MPUR10_END_REG     MPUR10_END;                   // MPU Region 10 End Address
    union   SYNCBRIDGEMPU_MPUR10_LOCK_REG    MPUR10_LOCK;                  // MPU 10 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR10_COMMIT_REG  MPUR10_COMMIT;                // MPU 10 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR10_ACCESS_REG  MPUR10_ACCESS;                // MPU Region 10 R/W Access Permissions
    uint8_t                                  rsvd10[12];                   // Reserved
    union   SYNCBRIDGEMPU_MPUR11_START_REG   MPUR11_START;                 // MPU Region 11 Start Address
    union   SYNCBRIDGEMPU_MPUR11_END_REG     MPUR11_END;                   // MPU Region 11 End Address
    union   SYNCBRIDGEMPU_MPUR11_LOCK_REG    MPUR11_LOCK;                  // MPU 11 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR11_COMMIT_REG  MPUR11_COMMIT;                // MPU 11 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR11_ACCESS_REG  MPUR11_ACCESS;                // MPU Region 11 R/W Access Permissions
    uint8_t                                  rsvd11[12];                   // Reserved
    union   SYNCBRIDGEMPU_MPUR12_START_REG   MPUR12_START;                 // MPU Region 12 Start Address
    union   SYNCBRIDGEMPU_MPUR12_END_REG     MPUR12_END;                   // MPU Region 12 End Address
    union   SYNCBRIDGEMPU_MPUR12_LOCK_REG    MPUR12_LOCK;                  // MPU 12 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR12_COMMIT_REG  MPUR12_COMMIT;                // MPU 12 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR12_ACCESS_REG  MPUR12_ACCESS;                // MPU Region 12 R/W Access Permissions
    uint8_t                                  rsvd12[12];                   // Reserved
    union   SYNCBRIDGEMPU_MPUR13_START_REG   MPUR13_START;                 // MPU Region 13 Start Address
    union   SYNCBRIDGEMPU_MPUR13_END_REG     MPUR13_END;                   // MPU Region 13 End Address
    union   SYNCBRIDGEMPU_MPUR13_LOCK_REG    MPUR13_LOCK;                  // MPU 13 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR13_COMMIT_REG  MPUR13_COMMIT;                // MPU 13 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR13_ACCESS_REG  MPUR13_ACCESS;                // MPU Region 13 R/W Access Permissions
    uint8_t                                  rsvd13[12];                   // Reserved
    union   SYNCBRIDGEMPU_MPUR14_START_REG   MPUR14_START;                 // MPU Region 14 Start Address
    union   SYNCBRIDGEMPU_MPUR14_END_REG     MPUR14_END;                   // MPU Region 14 End Address
    union   SYNCBRIDGEMPU_MPUR14_LOCK_REG    MPUR14_LOCK;                  // MPU 14 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR14_COMMIT_REG  MPUR14_COMMIT;                // MPU 14 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR14_ACCESS_REG  MPUR14_ACCESS;                // MPU Region 14 R/W Access Permissions
    uint8_t                                  rsvd14[12];                   // Reserved
    union   SYNCBRIDGEMPU_MPUR15_START_REG   MPUR15_START;                 // MPU Region 15 Start Address
    union   SYNCBRIDGEMPU_MPUR15_END_REG     MPUR15_END;                   // MPU Region 15 End Address
    union   SYNCBRIDGEMPU_MPUR15_LOCK_REG    MPUR15_LOCK;                  // MPU 15 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR15_COMMIT_REG  MPUR15_COMMIT;                // MPU 15 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR15_ACCESS_REG  MPUR15_ACCESS;                // MPU Region 15 R/W Access Permissions
    uint8_t                                  rsvd15[12];                   // Reserved
    union   SYNCBRIDGEMPU_MPUR16_START_REG   MPUR16_START;                 // MPU Region 16 Start Address
    union   SYNCBRIDGEMPU_MPUR16_END_REG     MPUR16_END;                   // MPU Region 16 End Address
    union   SYNCBRIDGEMPU_MPUR16_LOCK_REG    MPUR16_LOCK;                  // MPU 16 Temporary Lock
    union   SYNCBRIDGEMPU_MPUR16_COMMIT_REG  MPUR16_COMMIT;                // MPU 16 Permanent Commit
    union   SYNCBRIDGEMPU_MPUR16_ACCESS_REG  MPUR16_ACCESS;                // MPU Region 16 R/W Access Permissions
    uint8_t                                  rsvd16[1544];                 // Reserved
    union   SYNCBRIDGEMPU_MPUCTRL_REG        MPUCTRL;                      // MPU Control Register
    uint8_t                                  rsvd17[28];                   // Reserved
    union   SYNCBRIDGEMPU_MPUCFG_LOCK_REG    MPUCFG_LOCK;                  // Channel Configuration Temporary Lock
    union   SYNCBRIDGEMPU_MPUCFG_COMMIT_REG  MPUCFG_COMMIT;                // Channel Configuration Permanent Commit
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
