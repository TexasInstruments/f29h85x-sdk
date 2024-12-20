//###########################################################################
//
// FILE:    hwbf_epwm.h
//
// TITLE:   Definitions for the EPWM registers.
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

#ifndef HWBF_EPWM_H
#define HWBF_EPWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// EPWM Individual Register Bit Definitions:

struct EPWM_XCMPCTL1_BITS {             // bits description
    uint16_t XCMPEN:1;                  // 0 XCMP Compare Register Operation Enable
    uint16_t XCMPSPLIT:1;               // 1 XCMP Register Allocation Options
    uint16_t rsvd1:2;                   // 3:2 Reserved
    uint16_t XCMPA_ALLOC:4;             // 7:4 XCMPn register allocation for CMPA
    uint16_t XCMPB_ALLOC:4;             // 11:8 XCMPn register allocation for CMPB
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union EPWM_XCMPCTL1_REG {
    uint32_t  all;
    struct  EPWM_XCMPCTL1_BITS  bit;
};

struct EPWM_XLOADCTL_BITS {             // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t LOADMODE:1;                // 2 Load mode selection for Shadow registers
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t SHDWLEVEL:2;               // 5:4 Shadow Register Level Allocation Options
    uint16_t rsvd3:2;                   // 7:6 Reserved
    uint16_t SHDWBUFPTR_LOADONCE:2;     // 9:8 Register Load event count
    uint16_t SHDWBUFPTR_LOADMULTIPLE:2; // 11:10 Register Load event count
    uint16_t rsvd4:4;                   // 15:12 Reserved
    uint16_t RPTBUF2PRD:3;              // 18:16 Repeat Count Shadow Buffer 2
    uint16_t rsvd5:1;                   // 19 Reserved
    uint16_t RPTBUF2CNT:3;              // 22:20 Repeat Count Status Shadow Buffer 2
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t RPTBUF3PRD:3;              // 26:24 Repeat Count Shadow Buffer 3
    uint16_t rsvd7:1;                   // 27 Reserved
    uint16_t RPTBUF3CNT:3;              // 30:28 Repeat Count Status Shadow Buffer 3
    uint16_t rsvd8:1;                   // 31 Reserved
};

union EPWM_XLOADCTL_REG {
    uint32_t  all;
    struct  EPWM_XLOADCTL_BITS  bit;
};

struct EPWM_XLOAD_BITS {                // bits description
    uint16_t STARTLD:1;                 // 0 Enable register loading of shadow buffers
    uint16_t FRCLD:1;                   // 1 Force register loading of shadow buffers
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_XLOAD_REG {
    uint32_t  all;
    struct  EPWM_XLOAD_BITS  bit;
};

struct EPWM_EPWMXLINKXLOAD_BITS {       // bits description
    uint16_t XLOADLINK:5;               // 4:0 XLOAD  Link Register
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_EPWMXLINKXLOAD_REG {
    uint32_t  all;
    struct  EPWM_EPWMXLINKXLOAD_BITS  bit;
};

struct EPWM_XREGSHDW1STS_BITS {         // bits description
    uint16_t XCMP1_SHDW1FULL:1;         // 0 XCMP1_SHDW1 register full Status flag
    uint16_t XCMP2_SHDW1FULL:1;         // 1 XCMP2_SHDW1 register full Status flag
    uint16_t XCMP3_SHDW1FULL:1;         // 2 XCMP3_SHDW1 register full Status flag
    uint16_t XCMP4_SHDW1FULL:1;         // 3 XCMP4_SHDW1 register full Status flag
    uint16_t XCMP5_SHDW1FULL:1;         // 4 XCMP5_SHDW1 register full Status flag
    uint16_t XCMP6_SHDW1FULL:1;         // 5 XCMP6_SHDW1 register full Status flag
    uint16_t XCMP7_SHDW1FULL:1;         // 6 XCMP7_SHDW1 register full Status flag
    uint16_t XCMP8_SHDW1FULL:1;         // 7 XCMP8_SHDW1 register full Status flag
    uint16_t XTBPRD_SHDW1FULL:1;        // 8 XTBPRD_SHDW1 register full Status flag:
    uint16_t CMPC_SHDW1FULL:1;          // 9 CMPC_SHDW1 register full Status flag:
    uint16_t CMPD_SHDW1FULL:1;          // 10 CMPD_SHDW1 register full Status flag:
    uint16_t XAQCTLA_SHDW1FULL:1;       // 11 XAQCTLA_SHDW1 register full Status flag:
    uint16_t XAQCTLB_SHDW1FULL:1;       // 12 XAQCTLB_SHDW1 register full Status flag:
    uint16_t XMAX_SHDW1FULL:1;          // 13 XMINMAX_SHDW1 register full Status flag:MAX field update
    uint16_t XMIN_SHDW1FULL:1;          // 14 XMINMAX_SHDW1 register full Status flag: MIN field update
    uint16_t rsvd1:1;                   // 15 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_XREGSHDW1STS_REG {
    uint32_t  all;
    struct  EPWM_XREGSHDW1STS_BITS  bit;
};

struct EPWM_XREGSHDW2STS_BITS {         // bits description
    uint16_t XCMP1_SHDW2FULL:1;         // 0 XCMP1_SHDW2 register full Status flag
    uint16_t XCMP2_SHDW2FULL:1;         // 1 XCMP2_SHDW2 register full Status flag
    uint16_t XCMP3_SHDW2FULL:1;         // 2 XCMP3_SHDW2 register full Status flag
    uint16_t XCMP4_SHDW2FULL:1;         // 3 XCMP4_SHDW2 register full Status flag
    uint16_t XCMP5_SHDW2FULL:1;         // 4 XCMP5_SHDW2 register full Status flag
    uint16_t XCMP6_SHDW2FULL:1;         // 5 XCMP6_SHDW2 register full Status flag
    uint16_t XCMP7_SHDW2FULL:1;         // 6 XCMP7_SHDW2 register full Status flag
    uint16_t XCMP8_SHDW2FULL:1;         // 7 XCMP8_SHDW2 register full Status flag
    uint16_t XTBPRD_SHDW2FULL:1;        // 8 XTBPRD_SHDW2 register full Status flag:
    uint16_t CMPC_SHDW2FULL:1;          // 9 CMPC_SHDW2 register full Status flag:
    uint16_t CMPD_SHDW2FULL:1;          // 10 CMPD_SHDW2 register full Status flag:
    uint16_t XAQCTLA_SHDW2FULL:1;       // 11 XAQCTLA_SHDW2 register full Status flag:
    uint16_t XAQCTLB_SHDW2FULL:1;       // 12 XAQCTLB_SHDW2 register full Status flag:
    uint16_t XMAX_SHDW2FULL:1;          // 13 XMINMAX_SHDW2 register full Status flag:MAX field update
    uint16_t XMIN_SHDW2FULL:1;          // 14 XMINMAX_SHDW2 register full Status flag: MIN field update
    uint16_t rsvd1:1;                   // 15 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_XREGSHDW2STS_REG {
    uint32_t  all;
    struct  EPWM_XREGSHDW2STS_BITS  bit;
};

struct EPWM_XREGSHDW3STS_BITS {         // bits description
    uint16_t XCMP1_SHDW3FULL:1;         // 0 XCMP1_SHDW3 register full Status flag
    uint16_t XCMP2_SHDW3FULL:1;         // 1 XCMP2_SHDW3 register full Status flag
    uint16_t XCMP3_SHDW3FULL:1;         // 2 XCMP3_SHDW3 register full Status flag
    uint16_t XCMP4_SHDW3FULL:1;         // 3 XCMP4_SHDW3 register full Status flag
    uint16_t XCMP5_SHDW3FULL:1;         // 4 XCMP5_SHDW3 register full Status flag
    uint16_t XCMP6_SHDW3FULL:1;         // 5 XCMP6_SHDW3 register full Status flag
    uint16_t XCMP7_SHDW3FULL:1;         // 6 XCMP7_SHDW3 register full Status flag
    uint16_t XCMP8_SHDW3FULL:1;         // 7 XCMP8_SHDW3 register full Status flag
    uint16_t XTBPRD_SHDW3FULL:1;        // 8 XTBPRD_SHDW3 register full Status flag:
    uint16_t CMPC_SHDW3FULL:1;          // 9 CMPC_SHDW3 register full Status flag:
    uint16_t CMPD_SHDW3FULL:1;          // 10 CMPD_SHDW3 register full Status flag:
    uint16_t XAQCTLA_SHDW3FULL:1;       // 11 XAQCTLA_SHDW3 register full Status flag:
    uint16_t XAQCTLB_SHDW3FULL:1;       // 12 XAQCTLB_SHDW3 register full Status flag:
    uint16_t XMAX_SHDW3FULL:1;          // 13 XMINMAX_SHDW3 register full Status flag:MAX field update
    uint16_t XMIN_SHDW3FULL:1;          // 14 XMINMAX_SHDW3 register full Status flag: MIN field update
    uint16_t rsvd1:1;                   // 15 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_XREGSHDW3STS_REG {
    uint32_t  all;
    struct  EPWM_XREGSHDW3STS_BITS  bit;
};

struct EPWM_XCMP1_ACTIVE_BITS {         // bits description
    uint16_t XCMP1HR_ACTIVE:16;         // 15:0 Additional Compare 1 Active HR Register
    uint16_t XCMP1_ACTIVE:16;           // 31:16 Additional Compare 1 Active Register
};

union EPWM_XCMP1_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XCMP1_ACTIVE_BITS  bit;
};

struct EPWM_XCMP2_ACTIVE_BITS {         // bits description
    uint16_t XCMP2HR_ACTIVE:16;         // 15:0 Additional Compare 2 Active HR Register
    uint16_t XCMP2_ACTIVE:16;           // 31:16 Additional Compare 2 Active Register
};

union EPWM_XCMP2_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XCMP2_ACTIVE_BITS  bit;
};

struct EPWM_XCMP3_ACTIVE_BITS {         // bits description
    uint16_t XCMP3HR_ACTIVE:16;         // 15:0 Additional Compare 3 Active HR Register
    uint16_t XCMP3_ACTIVE:16;           // 31:16 Additional Compare 3 Active Register
};

union EPWM_XCMP3_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XCMP3_ACTIVE_BITS  bit;
};

struct EPWM_XCMP4_ACTIVE_BITS {         // bits description
    uint16_t XCMP4HR_ACTIVE:16;         // 15:0 Additional Compare 4 Active HR Register
    uint16_t XCMP4_ACTIVE:16;           // 31:16 Additional Compare 4 Active Register
};

union EPWM_XCMP4_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XCMP4_ACTIVE_BITS  bit;
};

struct EPWM_XCMP5_ACTIVE_BITS {         // bits description
    uint16_t XCMP5HR_ACTIVE:16;         // 15:0 Additional Compare 5 Active HR Register
    uint16_t XCMP5_ACTIVE:16;           // 31:16 Additional Compare 5 Active Register
};

union EPWM_XCMP5_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XCMP5_ACTIVE_BITS  bit;
};

struct EPWM_XCMP6_ACTIVE_BITS {         // bits description
    uint16_t XCMP6HR_ACTIVE:16;         // 15:0 Additional Compare 6 Active HR Register
    uint16_t XCMP6_ACTIVE:16;           // 31:16 Additional Compare 6 Active Register
};

union EPWM_XCMP6_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XCMP6_ACTIVE_BITS  bit;
};

struct EPWM_XCMP7_ACTIVE_BITS {         // bits description
    uint16_t XCMP7HR_ACTIVE:16;         // 15:0 Additional Compare 7 Active HR Register
    uint16_t XCMP7_ACTIVE:16;           // 31:16 Additional Compare 7 Active Register
};

union EPWM_XCMP7_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XCMP7_ACTIVE_BITS  bit;
};

struct EPWM_XCMP8_ACTIVE_BITS {         // bits description
    uint16_t XCMP8HR_ACTIVE:16;         // 15:0 Additional Compare 8 Active HR Register
    uint16_t XCMP8_ACTIVE:16;           // 31:16 Additional Compare 8 Active Register
};

union EPWM_XCMP8_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XCMP8_ACTIVE_BITS  bit;
};

struct EPWM_XTBPRD_ACTIVE_BITS {        // bits description
    uint16_t XTBPRDHR_ACTIVE:16;        // 15:0 Additional Time Base Period Active HR Register
    uint16_t XTBPRD_ACTIVE:16;          // 31:16 Additional Time Base Period Active Register
};

union EPWM_XTBPRD_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XTBPRD_ACTIVE_BITS  bit;
};

struct EPWM_XAQCTLA_ACTIVE_BITS {       // bits description
    uint16_t XCMP1:2;                   // 1:0 XCMP1 Action
    uint16_t XCMP2:2;                   // 3:2 XCMP2 Action
    uint16_t XCMP3:2;                   // 5:4 XCMP3 Action
    uint16_t XCMP4:2;                   // 7:6 XCMP4 Action
    uint16_t XCMP5:2;                   // 9:8 XCMP5 Action
    uint16_t XCMP6:2;                   // 11:10 XCMP6 Action
    uint16_t XCMP7:2;                   // 13:12 XCMP7 Action
    uint16_t XCMP8:2;                   // 15:14 XCMP8 Action
};

union EPWM_XAQCTLA_ACTIVE_REG {
    uint16_t  all;
    struct  EPWM_XAQCTLA_ACTIVE_BITS  bit;
};

struct EPWM_XAQCTLB_ACTIVE_BITS {       // bits description
    uint16_t rsvd1:8;                   // 7:0 Reserved
    uint16_t XCMP5:2;                   // 9:8 XCMP5 Action
    uint16_t XCMP6:2;                   // 11:10 XCMP6 Action
    uint16_t XCMP7:2;                   // 13:12 XCMP7 Action
    uint16_t XCMP8:2;                   // 15:14 XCMP8 Action
};

union EPWM_XAQCTLB_ACTIVE_REG {
    uint16_t  all;
    struct  EPWM_XAQCTLB_ACTIVE_BITS  bit;
};

struct EPWM_XMINMAX_ACTIVE_BITS {       // bits description
    uint16_t XMAX_ACTIVE:16;            // 15:0 Maximum Valude  for Capture Counter Active Register
    uint16_t XMIN_ACTIVE:16;            // 31:16 Minimum Valude  for Capture Counter Active Register
};

union EPWM_XMINMAX_ACTIVE_REG {
    uint32_t  all;
    struct  EPWM_XMINMAX_ACTIVE_BITS  bit;
};

struct EPWM_XCMP1_SHDW1_BITS {          // bits description
    uint16_t XCMP1HR_SHDW1:16;          // 15:0 Additional Compare 1 Shadow 1 HR Register
    uint16_t XCMP1_SHDW1:16;            // 31:16 Additional Compare 1 Shadow 1 Register
};

union EPWM_XCMP1_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XCMP1_SHDW1_BITS  bit;
};

struct EPWM_XCMP2_SHDW1_BITS {          // bits description
    uint16_t XCMP2HR_SHDW1:16;          // 15:0 Additional Compare 2 Shadow 1 HR Register
    uint16_t XCMP2_SHDW1:16;            // 31:16 Additional Compare 2 Shadow 1 Register
};

union EPWM_XCMP2_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XCMP2_SHDW1_BITS  bit;
};

struct EPWM_XCMP3_SHDW1_BITS {          // bits description
    uint16_t XCMP3HR_SHDW1:16;          // 15:0 Additional Compare 3 Shadow 1 HR Register
    uint16_t XCMP3_SHDW1:16;            // 31:16 Additional Compare 3 Shadow 1 Register
};

union EPWM_XCMP3_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XCMP3_SHDW1_BITS  bit;
};

struct EPWM_XCMP4_SHDW1_BITS {          // bits description
    uint16_t XCMP4HR_SHDW1:16;          // 15:0 Additional Compare 4 Shadow 1 HR Register
    uint16_t XCMP4_SHDW1:16;            // 31:16 Additional Compare 4 Shadow 1 Register
};

union EPWM_XCMP4_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XCMP4_SHDW1_BITS  bit;
};

struct EPWM_XCMP5_SHDW1_BITS {          // bits description
    uint16_t XCMP5HR_SHDW1:16;          // 15:0 Additional Compare 5 Shadow 1 HR Register
    uint16_t XCMP5_SHDW1:16;            // 31:16 Additional Compare 5 Shadow 1 Register
};

union EPWM_XCMP5_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XCMP5_SHDW1_BITS  bit;
};

struct EPWM_XCMP6_SHDW1_BITS {          // bits description
    uint16_t XCMP6HR_SHDW1:16;          // 15:0 Additional Compare 6 Shadow 1 HR Register
    uint16_t XCMP6_SHDW1:16;            // 31:16 Additional Compare 6 Shadow 1 Register
};

union EPWM_XCMP6_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XCMP6_SHDW1_BITS  bit;
};

struct EPWM_XCMP7_SHDW1_BITS {          // bits description
    uint16_t XCMP7HR_SHDW1:16;          // 15:0 Additional Compare 7 Shadow 1 HR Register
    uint16_t XCMP7_SHDW1:16;            // 31:16 Additional Compare 7 Shadow 1 Register
};

union EPWM_XCMP7_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XCMP7_SHDW1_BITS  bit;
};

struct EPWM_XCMP8_SHDW1_BITS {          // bits description
    uint16_t XCMP8HR_SHDW1:16;          // 15:0 Additional Compare 8 Shadow 1 HR Register
    uint16_t XCMP8_SHDW1:16;            // 31:16 Additional Compare 8 Shadow 1 Register
};

union EPWM_XCMP8_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XCMP8_SHDW1_BITS  bit;
};

struct EPWM_XTBPRD_SHDW1_BITS {         // bits description
    uint16_t XTBPRDHR_SHDW1:16;         // 15:0 Additional Time Base Period Shadow 1 HR Register
    uint16_t XTBPRD_SHDW1:16;           // 31:16 Additional Time Base Period Shadow 1 Register
};

union EPWM_XTBPRD_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XTBPRD_SHDW1_BITS  bit;
};

struct EPWM_XAQCTLA_SHDW1_BITS {        // bits description
    uint16_t XCMP1:2;                   // 1:0 XCMP1 Action
    uint16_t XCMP2:2;                   // 3:2 XCMP2 Action
    uint16_t XCMP3:2;                   // 5:4 XCMP3 Action
    uint16_t XCMP4:2;                   // 7:6 XCMP4 Action
    uint16_t XCMP5:2;                   // 9:8 XCMP5 Action
    uint16_t XCMP6:2;                   // 11:10 XCMP6 Action
    uint16_t XCMP7:2;                   // 13:12 XCMP7 Action
    uint16_t XCMP8:2;                   // 15:14 XCMP8 Action
};

union EPWM_XAQCTLA_SHDW1_REG {
    uint16_t  all;
    struct  EPWM_XAQCTLA_SHDW1_BITS  bit;
};

struct EPWM_XAQCTLB_SHDW1_BITS {        // bits description
    uint16_t rsvd1:8;                   // 7:0 Reserved
    uint16_t XCMP5:2;                   // 9:8 XCMP5 Action
    uint16_t XCMP6:2;                   // 11:10 XCMP6 Action
    uint16_t XCMP7:2;                   // 13:12 XCMP7 Action
    uint16_t XCMP8:2;                   // 15:14 XCMP8 Action
};

union EPWM_XAQCTLB_SHDW1_REG {
    uint16_t  all;
    struct  EPWM_XAQCTLB_SHDW1_BITS  bit;
};

struct EPWM_XMINMAX_SHDW1_BITS {        // bits description
    uint16_t XMAX_SHDW1:16;             // 15:0 Maximum Valude  for Capture Counter Active Register
    uint16_t XMIN_SHDW1:16;             // 31:16 Minimum Valude  for Capture Counter Active Register
};

union EPWM_XMINMAX_SHDW1_REG {
    uint32_t  all;
    struct  EPWM_XMINMAX_SHDW1_BITS  bit;
};

struct EPWM_XCMP1_SHDW2_BITS {          // bits description
    uint16_t XCMP1HR_SHDW2:16;          // 15:0 Additional Compare 1 Shadow 2 HR Register
    uint16_t XCMP1_SHDW2:16;            // 31:16 Additional Compare 1 Shadow 2 Register
};

union EPWM_XCMP1_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XCMP1_SHDW2_BITS  bit;
};

struct EPWM_XCMP2_SHDW2_BITS {          // bits description
    uint16_t XCMP2HR_SHDW2:16;          // 15:0 Additional Compare 2 Shadow 2 HR Register
    uint16_t XCMP2_SHDW2:16;            // 31:16 Additional Compare 2 Shadow 2 Register
};

union EPWM_XCMP2_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XCMP2_SHDW2_BITS  bit;
};

struct EPWM_XCMP3_SHDW2_BITS {          // bits description
    uint16_t XCMP3HR_SHDW2:16;          // 15:0 Additional Compare 3 Shadow 2 HR Register
    uint16_t XCMP3_SHDW2:16;            // 31:16 Additional Compare 3 Shadow 2 Register
};

union EPWM_XCMP3_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XCMP3_SHDW2_BITS  bit;
};

struct EPWM_XCMP4_SHDW2_BITS {          // bits description
    uint16_t XCMP4HR_SHDW2:16;          // 15:0 Additional Compare 4 Shadow 2 HR Register
    uint16_t XCMP4_SHDW2:16;            // 31:16 Additional Compare 4 Shadow 2 Register
};

union EPWM_XCMP4_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XCMP4_SHDW2_BITS  bit;
};

struct EPWM_XCMP5_SHDW2_BITS {          // bits description
    uint16_t XCMP5HR_SHDW2:16;          // 15:0 Additional Compare 5 Shadow 2 HR Register
    uint16_t XCMP5_SHDW2:16;            // 31:16 Additional Compare 5 Shadow 2 Register
};

union EPWM_XCMP5_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XCMP5_SHDW2_BITS  bit;
};

struct EPWM_XCMP6_SHDW2_BITS {          // bits description
    uint16_t XCMP6HR_SHDW2:16;          // 15:0 Additional Compare 6 Shadow 2 HR Register
    uint16_t XCMP6_SHDW2:16;            // 31:16 Additional Compare 6 Shadow 2 Register
};

union EPWM_XCMP6_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XCMP6_SHDW2_BITS  bit;
};

struct EPWM_XCMP7_SHDW2_BITS {          // bits description
    uint16_t XCMP7HR_SHDW2:16;          // 15:0 Additional Compare 7 Shadow 2 HR Register
    uint16_t XCMP7_SHDW2:16;            // 31:16 Additional Compare 7 Shadow 2 Register
};

union EPWM_XCMP7_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XCMP7_SHDW2_BITS  bit;
};

struct EPWM_XCMP8_SHDW2_BITS {          // bits description
    uint16_t XCMP8HR_SHDW2:16;          // 15:0 Additional Compare 8 Shadow 2 HR Register
    uint16_t XCMP8_SHDW2:16;            // 31:16 Additional Compare 8 Shadow 2 Register
};

union EPWM_XCMP8_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XCMP8_SHDW2_BITS  bit;
};

struct EPWM_XTBPRD_SHDW2_BITS {         // bits description
    uint16_t XTBPRDHR_SHDW2:16;         // 15:0 Additional Time Base Period Shadow 1 HR Register
    uint16_t XTBPRD_SHDW2:16;           // 31:16 Additional Time Base Period Shadow 1 Register
};

union EPWM_XTBPRD_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XTBPRD_SHDW2_BITS  bit;
};

struct EPWM_XAQCTLA_SHDW2_BITS {        // bits description
    uint16_t XCMP1:2;                   // 1:0 XCMP1 Action
    uint16_t XCMP2:2;                   // 3:2 XCMP2 Action
    uint16_t XCMP3:2;                   // 5:4 XCMP3 Action
    uint16_t XCMP4:2;                   // 7:6 XCMP4 Action
    uint16_t XCMP5:2;                   // 9:8 XCMP5 Action
    uint16_t XCMP6:2;                   // 11:10 XCMP6 Action
    uint16_t XCMP7:2;                   // 13:12 XCMP7 Action
    uint16_t XCMP8:2;                   // 15:14 XCMP8 Action
};

union EPWM_XAQCTLA_SHDW2_REG {
    uint16_t  all;
    struct  EPWM_XAQCTLA_SHDW2_BITS  bit;
};

struct EPWM_XAQCTLB_SHDW2_BITS {        // bits description
    uint16_t rsvd1:8;                   // 7:0 Reserved
    uint16_t XCMP5:2;                   // 9:8 XCMP5 Action
    uint16_t XCMP6:2;                   // 11:10 XCMP6 Action
    uint16_t XCMP7:2;                   // 13:12 XCMP7 Action
    uint16_t XCMP8:2;                   // 15:14 XCMP8 Action
};

union EPWM_XAQCTLB_SHDW2_REG {
    uint16_t  all;
    struct  EPWM_XAQCTLB_SHDW2_BITS  bit;
};

struct EPWM_XMINMAX_SHDW2_BITS {        // bits description
    uint16_t XMAX_SHDW2:16;             // 15:0 Maximum Valude  for Capture Counter Active Register
    uint16_t XMIN_SHDW2:16;             // 31:16 Minimum Valude  for Capture Counter Active Register
};

union EPWM_XMINMAX_SHDW2_REG {
    uint32_t  all;
    struct  EPWM_XMINMAX_SHDW2_BITS  bit;
};

struct EPWM_XCMP1_SHDW3_BITS {          // bits description
    uint16_t XCMP1HR_SHDW3:16;          // 15:0 Additional Compare 1 Shadow 3 HR Register
    uint16_t XCMP1_SHDW3:16;            // 31:16 Additional Compare 1 Shadow 3 Register
};

union EPWM_XCMP1_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XCMP1_SHDW3_BITS  bit;
};

struct EPWM_XCMP2_SHDW3_BITS {          // bits description
    uint16_t XCMP2HR_SHDW3:16;          // 15:0 Additional Compare 2 Shadow 3 HR Register
    uint16_t XCMP2_SHDW3:16;            // 31:16 Additional Compare 2 Shadow 3 Register
};

union EPWM_XCMP2_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XCMP2_SHDW3_BITS  bit;
};

struct EPWM_XCMP3_SHDW3_BITS {          // bits description
    uint16_t XCMP3HR_SHDW3:16;          // 15:0 Additional Compare 3 Shadow 3 HR Register
    uint16_t XCMP3_SHDW3:16;            // 31:16 Additional Compare 3 Shadow 3 Register
};

union EPWM_XCMP3_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XCMP3_SHDW3_BITS  bit;
};

struct EPWM_XCMP4_SHDW3_BITS {          // bits description
    uint16_t XCMP4HR_SHDW3:16;          // 15:0 Additional Compare 4 Shadow 3 HR Register
    uint16_t XCMP4_SHDW3:16;            // 31:16 Additional Compare 4 Shadow 3 Register
};

union EPWM_XCMP4_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XCMP4_SHDW3_BITS  bit;
};

struct EPWM_XCMP5_SHDW3_BITS {          // bits description
    uint16_t XCMP5HR_SHDW3:16;          // 15:0 Additional Compare 5 Shadow 3 HR Register
    uint16_t XCMP5_SHDW3:16;            // 31:16 Additional Compare 5 Shadow 3 Register
};

union EPWM_XCMP5_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XCMP5_SHDW3_BITS  bit;
};

struct EPWM_XCMP6_SHDW3_BITS {          // bits description
    uint16_t XCMP6HR_SHDW3:16;          // 15:0 Additional Compare 6 Shadow 3 HR Register
    uint16_t XCMP6_SHDW3:16;            // 31:16 Additional Compare 6 Shadow 3 Register
};

union EPWM_XCMP6_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XCMP6_SHDW3_BITS  bit;
};

struct EPWM_XCMP7_SHDW3_BITS {          // bits description
    uint16_t XCMP7HR_SHDW3:16;          // 15:0 Additional Compare 7 Shadow 3 HR Register
    uint16_t XCMP7_SHDW3:16;            // 31:16 Additional Compare 7 Shadow 3 Register
};

union EPWM_XCMP7_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XCMP7_SHDW3_BITS  bit;
};

struct EPWM_XCMP8_SHDW3_BITS {          // bits description
    uint16_t XCMP8HR_SHDW3:16;          // 15:0 Additional Compare 8 Shadow 3 HR Register
    uint16_t XCMP8_SHDW3:16;            // 31:16 Additional Compare 8 Shadow 3 Register
};

union EPWM_XCMP8_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XCMP8_SHDW3_BITS  bit;
};

struct EPWM_XTBPRD_SHDW3_BITS {         // bits description
    uint16_t XTBPRDHR_SHDW3:16;         // 15:0 Additional Time Base Period Shadow 1 HR Register
    uint16_t XTBPRD_SHDW3:16;           // 31:16 Additional Time Base Period Shadow 1 Register
};

union EPWM_XTBPRD_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XTBPRD_SHDW3_BITS  bit;
};

struct EPWM_XAQCTLA_SHDW3_BITS {        // bits description
    uint16_t XCMP1:2;                   // 1:0 XCMP1 Action
    uint16_t XCMP2:2;                   // 3:2 XCMP2 Action
    uint16_t XCMP3:2;                   // 5:4 XCMP3 Action
    uint16_t XCMP4:2;                   // 7:6 XCMP4 Action
    uint16_t XCMP5:2;                   // 9:8 XCMP5 Action
    uint16_t XCMP6:2;                   // 11:10 XCMP6 Action
    uint16_t XCMP7:2;                   // 13:12 XCMP7 Action
    uint16_t XCMP8:2;                   // 15:14 XCMP8 Action
};

union EPWM_XAQCTLA_SHDW3_REG {
    uint16_t  all;
    struct  EPWM_XAQCTLA_SHDW3_BITS  bit;
};

struct EPWM_XAQCTLB_SHDW3_BITS {        // bits description
    uint16_t rsvd1:8;                   // 7:0 Reserved
    uint16_t XCMP5:2;                   // 9:8 XCMP5 Action
    uint16_t XCMP6:2;                   // 11:10 XCMP6 Action
    uint16_t XCMP7:2;                   // 13:12 XCMP7 Action
    uint16_t XCMP8:2;                   // 15:14 XCMP8 Action
};

union EPWM_XAQCTLB_SHDW3_REG {
    uint16_t  all;
    struct  EPWM_XAQCTLB_SHDW3_BITS  bit;
};

struct EPWM_XMINMAX_SHDW3_BITS {        // bits description
    uint16_t XMAX_SHDW3:16;             // 15:0 Maximum Valude  for Capture Counter Active Register
    uint16_t XMIN_SHDW3:16;             // 31:16 Minimum Valude  for Capture Counter Active Register
};

union EPWM_XMINMAX_SHDW3_REG {
    uint32_t  all;
    struct  EPWM_XMINMAX_SHDW3_BITS  bit;
};

struct EPWM_XCMP_REGS {
    union   EPWM_XCMPCTL1_REG                XCMPCTL1;                     // XCMP Mode Control Register
    uint8_t                                  rsvd1[12];                    // Reserved
    union   EPWM_XLOADCTL_REG                XLOADCTL;                     // XCMP Mode Load Control Register
    uint8_t                                  rsvd2[4];                     // Reserved
    union   EPWM_XLOAD_REG                   XLOAD;                        // XCMP Mode Load Enable Register
    union   EPWM_EPWMXLINKXLOAD_REG          EPWMXLINKXLOAD;               // Link register across PWM modules
    union   EPWM_XREGSHDW1STS_REG            XREGSHDW1STS;                 // Shadow Buffer 1 Update Status Register
    uint8_t                                  rsvd3[4];                     // Reserved
    union   EPWM_XREGSHDW2STS_REG            XREGSHDW2STS;                 // Shadow Buffer 2 Update Status Register
    uint8_t                                  rsvd4[4];                     // Reserved
    union   EPWM_XREGSHDW3STS_REG            XREGSHDW3STS;                 // Shadow Buffer 3 Update Status Register
    uint8_t                                  rsvd5[460];                   // Reserved
    union   EPWM_XCMP1_ACTIVE_REG            XCMP1_ACTIVE;                 // Additional Compare 1 Active Register
    union   EPWM_XCMP2_ACTIVE_REG            XCMP2_ACTIVE;                 // Additional Compare 2 Active Register
    union   EPWM_XCMP3_ACTIVE_REG            XCMP3_ACTIVE;                 // Additional Compare 3 Active Register
    union   EPWM_XCMP4_ACTIVE_REG            XCMP4_ACTIVE;                 // Additional Compare 4 Active Register
    union   EPWM_XCMP5_ACTIVE_REG            XCMP5_ACTIVE;                 // Additional Compare 5 Active Register
    union   EPWM_XCMP6_ACTIVE_REG            XCMP6_ACTIVE;                 // Additional Compare 6 Active Register
    union   EPWM_XCMP7_ACTIVE_REG            XCMP7_ACTIVE;                 // Additional Compare 7 Active Register
    union   EPWM_XCMP8_ACTIVE_REG            XCMP8_ACTIVE;                 // Additional Compare 8 Active Register
    union   EPWM_XTBPRD_ACTIVE_REG           XTBPRD_ACTIVE;                // Additional Time Base Period Active Register
    uint8_t                                  rsvd6[12];                    // Reserved
    union   EPWM_XAQCTLA_ACTIVE_REG          XAQCTLA_ACTIVE;               // AQCTLA Active Register
    union   EPWM_XAQCTLB_ACTIVE_REG          XAQCTLB_ACTIVE;               // AQCTLB Active Register
    uint8_t                                  rsvd7[16];                    // Reserved
    union   EPWM_XMINMAX_ACTIVE_REG          XMINMAX_ACTIVE;               // XMINMAX Active Register
    uint8_t                                  rsvd8[56];                    // Reserved
    union   EPWM_XCMP1_SHDW1_REG             XCMP1_SHDW1;                  // Additional Compare 1 Shadow 1 Register
    union   EPWM_XCMP2_SHDW1_REG             XCMP2_SHDW1;                  // Additional Compare 2 Shadow 1 Register
    union   EPWM_XCMP3_SHDW1_REG             XCMP3_SHDW1;                  // Additional Compare 3 Shadow 1 Register
    union   EPWM_XCMP4_SHDW1_REG             XCMP4_SHDW1;                  // Additional Compare 4 Shadow 1 Register
    union   EPWM_XCMP5_SHDW1_REG             XCMP5_SHDW1;                  // Additional Compare 5 Shadow 1 Register
    union   EPWM_XCMP6_SHDW1_REG             XCMP6_SHDW1;                  // Additional Compare 6 Shadow 1 Register
    union   EPWM_XCMP7_SHDW1_REG             XCMP7_SHDW1;                  // Additional Compare 7 Shadow 1 Register
    union   EPWM_XCMP8_SHDW1_REG             XCMP8_SHDW1;                  // Additional Compare 8 Shadow 1 Register
    union   EPWM_XTBPRD_SHDW1_REG            XTBPRD_SHDW1;                 // Additional Time Base Period Shadow 1 Register
    uint8_t                                  rsvd9[12];                    // Reserved
    union   EPWM_XAQCTLA_SHDW1_REG           XAQCTLA_SHDW1;                // XAQCTLA Shadow 1 Register
    union   EPWM_XAQCTLB_SHDW1_REG           XAQCTLB_SHDW1;                // XAQCTLB Shadow 1 Register
    uint8_t                                  rsvd10[6];                    // Reserved
    uint16_t                                 CMPC_SHDW1;                   // CMPC Shadow 1 Register
    uint8_t                                  rsvd11[2];                    // Reserved
    uint16_t                                 CMPD_SHDW1;                   // CMPD Shadow 1 Register
    uint8_t                                  rsvd12[4];                    // Reserved
    union   EPWM_XMINMAX_SHDW1_REG           XMINMAX_SHDW1;                // XMINMAX Shadow 1 Register
    uint8_t                                  rsvd13[56];                   // Reserved
    union   EPWM_XCMP1_SHDW2_REG             XCMP1_SHDW2;                  // Additional Compare 1 Shadow 2 Register
    union   EPWM_XCMP2_SHDW2_REG             XCMP2_SHDW2;                  // Additional Compare 2 Shadow 2 Register
    union   EPWM_XCMP3_SHDW2_REG             XCMP3_SHDW2;                  // Additional Compare 3 Shadow 2 Register
    union   EPWM_XCMP4_SHDW2_REG             XCMP4_SHDW2;                  // Additional Compare 4 Shadow 2 Register
    union   EPWM_XCMP5_SHDW2_REG             XCMP5_SHDW2;                  // Additional Compare 5 Shadow 2 Register
    union   EPWM_XCMP6_SHDW2_REG             XCMP6_SHDW2;                  // Additional Compare 6 Shadow 2 Register
    union   EPWM_XCMP7_SHDW2_REG             XCMP7_SHDW2;                  // Additional Compare 7 Shadow 2 Register
    union   EPWM_XCMP8_SHDW2_REG             XCMP8_SHDW2;                  // Additional Compare 8 Shadow 2 Register
    union   EPWM_XTBPRD_SHDW2_REG            XTBPRD_SHDW2;                 // Additional Time Base Period Shadow 2 Register
    uint8_t                                  rsvd14[12];                   // Reserved
    union   EPWM_XAQCTLA_SHDW2_REG           XAQCTLA_SHDW2;                // XAQCTLA Shadow 2 Register
    union   EPWM_XAQCTLB_SHDW2_REG           XAQCTLB_SHDW2;                // XAQCTLB Shadow 2 Register
    uint8_t                                  rsvd15[6];                    // Reserved
    uint16_t                                 CMPC_SHDW2;                   // CMPC Shadow 2 Register
    uint8_t                                  rsvd16[2];                    // Reserved
    uint16_t                                 CMPD_SHDW2;                   // CMPD Shadow 2 Register
    uint8_t                                  rsvd17[4];                    // Reserved
    union   EPWM_XMINMAX_SHDW2_REG           XMINMAX_SHDW2;                // XMINMAX Shadow 2 Register
    uint8_t                                  rsvd18[56];                   // Reserved
    union   EPWM_XCMP1_SHDW3_REG             XCMP1_SHDW3;                  // Additional Compare 1 Shadow 3 Register
    union   EPWM_XCMP2_SHDW3_REG             XCMP2_SHDW3;                  // Additional Compare 2 Shadow 3 Register
    union   EPWM_XCMP3_SHDW3_REG             XCMP3_SHDW3;                  // Additional Compare 3 Shadow 3 Register
    union   EPWM_XCMP4_SHDW3_REG             XCMP4_SHDW3;                  // Additional Compare 4 Shadow 3 Register
    union   EPWM_XCMP5_SHDW3_REG             XCMP5_SHDW3;                  // Additional Compare 5 Shadow 3 Register
    union   EPWM_XCMP6_SHDW3_REG             XCMP6_SHDW3;                  // Additional Compare 6 Shadow 3 Register
    union   EPWM_XCMP7_SHDW3_REG             XCMP7_SHDW3;                  // Additional Compare 7 Shadow 3 Register
    union   EPWM_XCMP8_SHDW3_REG             XCMP8_SHDW3;                  // Additional Compare 8 Shadow 3 Register
    union   EPWM_XTBPRD_SHDW3_REG            XTBPRD_SHDW3;                 // Additional Time Base Period Shadow 3 Register
    uint8_t                                  rsvd19[12];                   // Reserved
    union   EPWM_XAQCTLA_SHDW3_REG           XAQCTLA_SHDW3;                // XAQCTLA Shadow 3 Register
    union   EPWM_XAQCTLB_SHDW3_REG           XAQCTLB_SHDW3;                // XAQCTLB Shadow 3 Register
    uint8_t                                  rsvd20[6];                    // Reserved
    uint16_t                                 CMPC_SHDW3;                   // CMPC Shadow 3 Register
    uint8_t                                  rsvd21[2];                    // Reserved
    uint16_t                                 CMPD_SHDW3;                   // CMPD Shadow 3 Register
    uint8_t                                  rsvd22[4];                    // Reserved
    union   EPWM_XMINMAX_SHDW3_REG           XMINMAX_SHDW3;                // XMINMAX Shadow 3 Register
};

struct EPWM_TBCTL_BITS {                // bits description
    uint16_t CTRMODE:2;                 // 1:0 Counter Mode
    uint16_t PHSEN:1;                   // 2 Phase Load Enable
    uint16_t PRDLD:1;                   // 3 Active Period Load
    uint16_t rsvd1:2;                   // 5:4 Reserved
    uint16_t SWFSYNC:1;                 // 6 Software Force Sync Pulse
    uint16_t HSPCLKDIV:3;               // 9:7 High Speed TBCLK Pre-scaler
    uint16_t CLKDIV:3;                  // 12:10 Time Base Clock Pre-scaler
    uint16_t PHSDIR:1;                  // 13 Phase Direction Bit
    uint16_t FREE_SOFT:2;               // 15:14 Emulation Mode Bits
};

union EPWM_TBCTL_REG {
    uint16_t  all;
    struct  EPWM_TBCTL_BITS  bit;
};

struct EPWM_TBCTL2_BITS {               // bits description
    uint16_t rsvd1:5;                   // 4:0 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t OSHTSYNCMODE:1;            // 6 One shot sync mode
    uint16_t OSHTSYNC:1;                // 7 One shot sync
    uint16_t rsvd3:4;                   // 11:8 Reserved
    uint16_t rsvd4:2;                   // 13:12 Reserved
    uint16_t PRDLDSYNC:2;               // 15:14 PRD Shadow to Active Load on SYNC Event
};

union EPWM_TBCTL2_REG {
    uint16_t  all;
    struct  EPWM_TBCTL2_BITS  bit;
};

struct EPWM_EPWMSYNCINSEL_BITS {        // bits description
    uint16_t SEL:7;                     // 6:0 EPWMxSYNCI source select
    uint16_t rsvd1:9;                   // 15:7 Reserved
};

union EPWM_EPWMSYNCINSEL_REG {
    uint16_t  all;
    struct  EPWM_EPWMSYNCINSEL_BITS  bit;
};

struct EPWM_TBSTS_BITS {                // bits description
    uint16_t CTRDIR:1;                  // 0 Counter Direction Status
    uint16_t SYNCI:1;                   // 1 External Input Sync Status
    uint16_t CTRMAX:1;                  // 2 Counter Max Latched Status
    uint16_t rsvd1:13;                  // 15:3 Reserved
};

union EPWM_TBSTS_REG {
    uint16_t  all;
    struct  EPWM_TBSTS_BITS  bit;
};

struct EPWM_EPWMSYNCOUTEN_BITS {        // bits description
    uint16_t SWEN:1;                    // 0 EPWMxSYNCO Software Force Enable
    uint16_t ZEROEN:1;                  // 1 EPWMxSYNCO Zero Count Event Enable
    uint16_t CMPBEN:1;                  // 2 EPWMxSYNCO Compare B Event Enable
    uint16_t CMPCEN:1;                  // 3 EPWMxSYNCO Compare C Event Enable
    uint16_t CMPDEN:1;                  // 4 EPWMxSYNCO Compare D Event Enable
    uint16_t DCAEVT1EN:1;               // 5 EPWMxSYNCO Digital Compare A Event 1 Sync Enable
    uint16_t DCBEVT1EN:1;               // 6 EPWMxSYNCO Digital Compare B Event 1 Sync Enable
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t rsvd2:8;                   // 15:8 Reserved
};

union EPWM_EPWMSYNCOUTEN_REG {
    uint16_t  all;
    struct  EPWM_EPWMSYNCOUTEN_BITS  bit;
};

struct EPWM_TBCTL3_BITS {               // bits description
    uint16_t OSSFRCEN:1;                // 0 One Shot Sync Force Enable
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union EPWM_TBCTL3_REG {
    uint16_t  all;
    struct  EPWM_TBCTL3_BITS  bit;
};

struct EPWM_CMPCTL_BITS {               // bits description
    uint16_t LOADAMODE:2;               // 1:0 Active Compare A Load
    uint16_t LOADBMODE:2;               // 3:2 Active Compare B Load
    uint16_t SHDWAMODE:1;               // 4 Compare A Register Block Operating Mode
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t SHDWBMODE:1;               // 6 Compare B Register Block Operating Mode
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t SHDWAFULL:1;               // 8 Compare A Shadow Register Full Status
    uint16_t SHDWBFULL:1;               // 9 Compare B Shadow Register Full Status
    uint16_t LOADASYNC:2;               // 11:10 Active Compare A Load on SYNC
    uint16_t LOADBSYNC:2;               // 13:12 Active Compare B Load on SYNC
    uint16_t rsvd3:1;                   // 14 Reserved
    uint16_t LINKDUTYHR:1;              // 15 Enable same values on CMPAHR/CMPBHR
};

union EPWM_CMPCTL_REG {
    uint16_t  all;
    struct  EPWM_CMPCTL_BITS  bit;
};

struct EPWM_CMPCTL2_BITS {              // bits description
    uint16_t LOADCMODE:2;               // 1:0 Active Compare C Load
    uint16_t LOADDMODE:2;               // 3:2 Active Compare D load
    uint16_t SHDWCMODE:1;               // 4 Compare C Block Operating Mode
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t SHDWDMODE:1;               // 6 Compare D Block Operating Mode
    uint16_t rsvd2:3;                   // 9:7 Reserved
    uint16_t LOADCSYNC:2;               // 11:10 Active Compare C Load on SYNC
    uint16_t LOADDSYNC:2;               // 13:12 Active Compare D Load on SYNC
    uint16_t rsvd3:2;                   // 15:14 Reserved
};

union EPWM_CMPCTL2_REG {
    uint16_t  all;
    struct  EPWM_CMPCTL2_BITS  bit;
};

struct EPWM_DBCTL_BITS {                // bits description
    uint16_t OUT_MODE:2;                // 1:0 Dead Band Output Mode Control
    uint16_t POLSEL:2;                  // 3:2 Polarity Select Control
    uint16_t IN_MODE:2;                 // 5:4 Dead Band Input Select Mode Control
    uint16_t LOADREDMODE:2;             // 7:6 Active DBRED Load Mode
    uint16_t LOADFEDMODE:2;             // 9:8 Active DBFED Load Mode
    uint16_t SHDWDBREDMODE:1;           // 10 DBRED Block Operating Mode
    uint16_t SHDWDBFEDMODE:1;           // 11 DBFED Block Operating Mode
    uint16_t OUTSWAP:2;                 // 13:12 Dead Band Output Swap Control
    uint16_t DEDB_MODE:1;               // 14 Dead Band Dual-Edge B Mode Control
    uint16_t HALFCYCLE:1;               // 15 Half Cycle Clocking Enable
};

union EPWM_DBCTL_REG {
    uint16_t  all;
    struct  EPWM_DBCTL_BITS  bit;
};

struct EPWM_DBCTL2_BITS {               // bits description
    uint16_t LOADDBCTLMODE:2;           // 1:0 DBCTL Load from Shadow Mode Select
    uint16_t SHDWDBCTLMODE:1;           // 2 DBCTL Load mode Select
    uint16_t rsvd1:13;                  // 15:3 Reserved
};

union EPWM_DBCTL2_REG {
    uint16_t  all;
    struct  EPWM_DBCTL2_BITS  bit;
};

struct EPWM_AQCTL_BITS {                // bits description
    uint16_t LDAQAMODE:2;               // 1:0 Action Qualifier A Load Select
    uint16_t LDAQBMODE:2;               // 3:2 Action Qualifier B Load Select
    uint16_t SHDWAQAMODE:1;             // 4 Action Qualifer A Operating Mode
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t SHDWAQBMODE:1;             // 6 Action Qualifier B Operating Mode
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t LDAQASYNC:2;               // 9:8 AQCTLA Register Load on SYNC
    uint16_t LDAQBSYNC:2;               // 11:10 AQCTLB Register Load on SYNC
    uint16_t rsvd3:4;                   // 15:12 Reserved
};

union EPWM_AQCTL_REG {
    uint16_t  all;
    struct  EPWM_AQCTL_BITS  bit;
};

struct EPWM_AQTSRCSEL_BITS {            // bits description
    uint16_t T1SEL:4;                   // 3:0 T1 Event Source Select Bits
    uint16_t T2SEL:4;                   // 7:4 T2 Event Source Select Bits
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union EPWM_AQTSRCSEL_REG {
    uint16_t  all;
    struct  EPWM_AQTSRCSEL_BITS  bit;
};

struct EPWM_PCCTL_BITS {                // bits description
    uint16_t CHPEN:1;                   // 0 PWM chopping enable
    uint16_t OSHTWTH:4;                 // 4:1 One-shot pulse width
    uint16_t CHPFREQ:3;                 // 7:5 Chopping clock frequency
    uint16_t CHPDUTY:3;                 // 10:8 Chopping clock Duty cycle
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union EPWM_PCCTL_REG {
    uint16_t  all;
    struct  EPWM_PCCTL_BITS  bit;
};

struct EPWM_VCAPCTL_BITS {              // bits description
    uint16_t VCAPE:1;                   // 0 Valley  Capture mode
    uint16_t VCAPSTART:1;               // 1 Valley  Capture Start
    uint16_t TRIGSEL:3;                 // 4:2 Capture Trigger Select
    uint16_t rsvd1:2;                   // 6:5 Reserved
    uint16_t VDELAYDIV:3;               // 9:7 Valley Delay Mode Divide Enable
    uint16_t EDGEFILTDLYSEL:1;          // 10 Valley Switching Mode Delay Select
    uint16_t rsvd2:5;                   // 15:11 Reserved
};

union EPWM_VCAPCTL_REG {
    uint16_t  all;
    struct  EPWM_VCAPCTL_BITS  bit;
};

struct EPWM_VCNTCFG_BITS {              // bits description
    uint16_t STARTEDGE:4;               // 3:0 Counter Start Edge Selection
    uint16_t rsvd1:3;                   // 6:4 Reserved
    uint16_t STARTEDGESTS:1;            // 7 Start Edge Status Bit
    uint16_t STOPEDGE:4;                // 11:8 Counter Start Edge Selection
    uint16_t rsvd2:3;                   // 14:12 Reserved
    uint16_t STOPEDGESTS:1;             // 15 Stop Edge Status Bit
};

union EPWM_VCNTCFG_REG {
    uint16_t  all;
    struct  EPWM_VCNTCFG_BITS  bit;
};

struct EPWM_HRCNFG_BITS {               // bits description
    uint16_t EDGMODE:2;                 // 1:0 ePWMxA Edge Mode Select Bits
    uint16_t CTLMODE:1;                 // 2 ePWMxA Control Mode Select Bits
    uint16_t HRLOAD:2;                  // 4:3 ePWMxA Shadow Mode Select Bits
    uint16_t SELOUTB:1;                 // 5 EPWMB Output Selection Bit
    uint16_t AUTOCONV:1;                // 6 Autoconversion Bit
    uint16_t SWAPAB:1;                  // 7 Swap EPWMA and EPWMB Outputs Bit
    uint16_t EDGMODEB:2;                // 9:8 ePWMxB Edge Mode Select Bits
    uint16_t CTLMODEB:1;                // 10 ePWMxB Control Mode Select Bits
    uint16_t HRLOADB:2;                 // 12:11 ePWMxB Shadow Mode Select Bits
    uint16_t rsvd1:1;                   // 13 Reserved
    uint16_t rsvd2:2;                   // 15:14 Reserved
};

union EPWM_HRCNFG_REG {
    uint16_t  all;
    struct  EPWM_HRCNFG_BITS  bit;
};

struct EPWM_HRCNFG2_BITS {              // bits description
    uint16_t EDGMODEDB:2;               // 1:0 Dead-Band Edge-Mode Select Bits
    uint16_t CTLMODEDBRED:2;            // 3:2 DBRED Control Mode Select Bits
    uint16_t CTLMODEDBFED:2;            // 5:4 DBFED Control Mode Select Bits
    uint16_t rsvd1:8;                   // 13:6 Reserved
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t rsvd3:1;                   // 15 Reserved
};

union EPWM_HRCNFG2_REG {
    uint16_t  all;
    struct  EPWM_HRCNFG2_BITS  bit;
};

struct EPWM_HRPCTL_BITS {               // bits description
    uint16_t HRPE:1;                    // 0 High Resolution Period Enable
    uint16_t PWMSYNCSEL:1;              // 1 EPWMSYNCPER Source Select
    uint16_t TBPHSHRLOADE:1;            // 2 TBPHSHR Load Enable
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t PWMSYNCSELX:3;             // 6:4 EPWMSYNCPER Extended Source Select Bit:
    uint16_t rsvd2:9;                   // 15:7 Reserved
};

union EPWM_HRPCTL_REG {
    uint16_t  all;
    struct  EPWM_HRPCTL_BITS  bit;
};

struct EPWM_TRREM_BITS {                // bits description
    uint16_t TRREM:11;                  // 10:0 HRPWM Remainder Bits
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union EPWM_TRREM_REG {
    uint16_t  all;
    struct  EPWM_TRREM_BITS  bit;
};

struct EPWM_GLDCTL_BITS {               // bits description
    uint16_t GLD:1;                     // 0 Global Shadow to Active load event control
    uint16_t GLDMODE:4;                 // 4:1 Shadow to Active Global Load Pulse Selection
    uint16_t OSHTMODE:1;                // 5 One Shot Load mode control bit
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GLDPRD:3;                  // 9:7 Global Load Strobe Period Select Register
    uint16_t GLDCNT:3;                  // 12:10 Global Load Strobe Counter Register
    uint16_t rsvd2:3;                   // 15:13 Reserved
};

union EPWM_GLDCTL_REG {
    uint16_t  all;
    struct  EPWM_GLDCTL_BITS  bit;
};

struct EPWM_GLDCFG_BITS {               // bits description
    uint16_t TBPRD_TBPRDHR:1;           // 0 Global load event configuration for TBPRD:TBPRDHR
    uint16_t CMPA_CMPAHR:1;             // 1 Global load event configuration for CMPA:CMPAHR
    uint16_t CMPB_CMPBHR:1;             // 2 Global load event configuration for CMPB:CMPBHR
    uint16_t CMPC:1;                    // 3 Global load event configuration for CMPC
    uint16_t CMPD:1;                    // 4 Global load event configuration for CMPD
    uint16_t DBRED_DBREDHR:1;           // 5 Global load event configuration for DBRED:DBREDHR
    uint16_t DBFED_DBFEDHR:1;           // 6 Global load event configuration for DBFED:DBFEDHR
    uint16_t DBCTL:1;                   // 7 Global load event configuration for DBCTL
    uint16_t AQCTLA_AQCTLA2:1;          // 8 Global load event configuration for AQCTLA/A2
    uint16_t AQCTLB_AQCTLB2:1;          // 9 Global load event configuration for AQCTLB/B2
    uint16_t AQCSFRC:1;                 // 10 Global load event configuration for AQCSFRC
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union EPWM_GLDCFG_REG {
    uint16_t  all;
    struct  EPWM_GLDCFG_BITS  bit;
};

struct EPWM_AQCTLA_BITS {               // bits description
    uint16_t ZRO:2;                     // 1:0 Action Counter = Zero
    uint16_t PRD:2;                     // 3:2 Action Counter = Period
    uint16_t CAU:2;                     // 5:4 Action Counter = Compare A Up
    uint16_t CAD:2;                     // 7:6 Action Counter = Compare A Down
    uint16_t CBU:2;                     // 9:8 Action Counter = Compare B Up
    uint16_t CBD:2;                     // 11:10 Action Counter = Compare B Down
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union EPWM_AQCTLA_REG {
    uint16_t  all;
    struct  EPWM_AQCTLA_BITS  bit;
};

struct EPWM_AQCTLA2_BITS {              // bits description
    uint16_t T1U:2;                     // 1:0 Action when event occurs on T1 in UP-Count
    uint16_t T1D:2;                     // 3:2 Action when event occurs on T1 in DOWN-Count
    uint16_t T2U:2;                     // 5:4 Action when event occurs on T2 in UP-Count
    uint16_t T2D:2;                     // 7:6 Action when event occurs on T2 in DOWN-Count
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union EPWM_AQCTLA2_REG {
    uint16_t  all;
    struct  EPWM_AQCTLA2_BITS  bit;
};

struct EPWM_AQCTLB_BITS {               // bits description
    uint16_t ZRO:2;                     // 1:0 Action Counter = Zero
    uint16_t PRD:2;                     // 3:2 Action Counter = Period
    uint16_t CAU:2;                     // 5:4 Action Counter = Compare A Up
    uint16_t CAD:2;                     // 7:6 Action Counter = Compare A Down
    uint16_t CBU:2;                     // 9:8 Action Counter = Compare B Up
    uint16_t CBD:2;                     // 11:10 Action Counter = Compare B Down
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union EPWM_AQCTLB_REG {
    uint16_t  all;
    struct  EPWM_AQCTLB_BITS  bit;
};

struct EPWM_AQCTLB2_BITS {              // bits description
    uint16_t T1U:2;                     // 1:0 Action when event occurs on T1 in UP-Count
    uint16_t T1D:2;                     // 3:2 Action when event occurs on T1 in DOWN-Count
    uint16_t T2U:2;                     // 5:4 Action when event occurs on T2 in UP-Count
    uint16_t T2D:2;                     // 7:6 Action when event occurs on T2 in DOWN-Count
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union EPWM_AQCTLB2_REG {
    uint16_t  all;
    struct  EPWM_AQCTLB2_BITS  bit;
};

struct EPWM_AQSFRC_BITS {               // bits description
    uint16_t ACTSFA:2;                  // 1:0 Action when One-time SW Force A Invoked
    uint16_t OTSFA:1;                   // 2 One-time SW Force A Output
    uint16_t ACTSFB:2;                  // 4:3 Action when One-time SW Force B Invoked
    uint16_t OTSFB:1;                   // 5 One-time SW Force A Output
    uint16_t RLDCSF:2;                  // 7:6 Reload from Shadow Options
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union EPWM_AQSFRC_REG {
    uint16_t  all;
    struct  EPWM_AQSFRC_BITS  bit;
};

struct EPWM_AQCSFRC_BITS {              // bits description
    uint16_t CSFA:2;                    // 1:0 Continuous Software Force on output A
    uint16_t CSFB:2;                    // 3:2 Continuous Software Force on output B
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union EPWM_AQCSFRC_REG {
    uint16_t  all;
    struct  EPWM_AQCSFRC_BITS  bit;
};

struct EPWM_DBREDHR_BITS {              // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:7;                   // 7:1 Reserved
    uint16_t rsvd3:1;                   // 8 Reserved
    uint16_t DBREDHR:7;                 // 15:9 DBREDHR High Resolution Bits
};

union EPWM_DBREDHR_REG {
    uint16_t  all;
    struct  EPWM_DBREDHR_BITS  bit;
};

struct EPWM_DBRED_BITS {                // bits description
    uint16_t DBRED:14;                  // 13:0 Rising edge delay value
    uint16_t rsvd1:2;                   // 15:14 Reserved
};

union EPWM_DBRED_REG {
    uint16_t  all;
    struct  EPWM_DBRED_BITS  bit;
};

struct EPWM_DBFEDHR_BITS {              // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:7;                   // 7:1 Reserved
    uint16_t rsvd3:1;                   // 8 Reserved
    uint16_t DBFEDHR:7;                 // 15:9 DBFEDHR High Resolution Bits
};

union EPWM_DBFEDHR_REG {
    uint16_t  all;
    struct  EPWM_DBFEDHR_BITS  bit;
};

struct EPWM_DBFED_BITS {                // bits description
    uint16_t DBFED:14;                  // 13:0 Falling edge delay value
    uint16_t rsvd1:2;                   // 15:14 Reserved
};

union EPWM_DBFED_REG {
    uint16_t  all;
    struct  EPWM_DBFED_BITS  bit;
};

struct EPWM_TBPHS_BITS {                // bits description
    uint16_t TBPHSHR:16;                // 15:0 Extension Register for HRPWM Phase (8-bits)
    uint16_t TBPHS:16;                  // 31:16 Phase Offset Register
};

union EPWM_TBPHS_REG {
    uint32_t  all;
    struct  EPWM_TBPHS_BITS  bit;
};

struct EPWM_CMPA_BITS {                 // bits description
    uint16_t CMPAHR:16;                 // 15:0 Compare A HRPWM Extension Register
    uint16_t CMPA:16;                   // 31:16 Compare A Register
};

union EPWM_CMPA_REG {
    uint32_t  all;
    struct  EPWM_CMPA_BITS  bit;
};

struct EPWM_CMPB_BITS {                 // bits description
    uint16_t CMPBHR:16;                 // 15:0 Compare B High Resolution Bits
    uint16_t CMPB:16;                   // 31:16 Compare B Register
};

union EPWM_CMPB_REG {
    uint32_t  all;
    struct  EPWM_CMPB_BITS  bit;
};

struct EPWM_GLDCTL2_BITS {              // bits description
    uint16_t OSHTLD:1;                  // 0 Enable reload event in one shot mode
    uint16_t GFRCLD:1;                  // 1 Force reload event in one shot mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
};

union EPWM_GLDCTL2_REG {
    uint16_t  all;
    struct  EPWM_GLDCTL2_BITS  bit;
};

struct EPWM_TZSEL_BITS {                // bits description
    uint16_t CBC1:1;                    // 0 TZ1 CBC select
    uint16_t CBC2:1;                    // 1 TZ2 CBC select
    uint16_t CBC3:1;                    // 2 TZ3 CBC select
    uint16_t CBC4:1;                    // 3 TZ4 CBC select
    uint16_t CBC5:1;                    // 4 TZ5 CBC select
    uint16_t CBC6:1;                    // 5 TZ6 CBC select
    uint16_t DCAEVT2:1;                 // 6 DCAEVT2 CBC select
    uint16_t DCBEVT2:1;                 // 7 DCBEVT2 CBC select
    uint16_t OSHT1:1;                   // 8 One-shot TZ1 select
    uint16_t OSHT2:1;                   // 9 One-shot TZ2 select
    uint16_t OSHT3:1;                   // 10 One-shot TZ3 select
    uint16_t OSHT4:1;                   // 11 One-shot TZ4 select
    uint16_t OSHT5:1;                   // 12 One-shot TZ5 select
    uint16_t OSHT6:1;                   // 13 One-shot TZ6 select
    uint16_t DCAEVT1:1;                 // 14 One-shot DCAEVT1 select
    uint16_t DCBEVT1:1;                 // 15 One-shot DCBEVT1 select
};

union EPWM_TZSEL_REG {
    uint16_t  all;
    struct  EPWM_TZSEL_BITS  bit;
};

struct EPWM_TZSEL2_BITS {               // bits description
    uint16_t CAPEVTCBC:1;               // 0 CAPEVT CBC select
    uint16_t rsvd1:7;                   // 7:1 Reserved
    uint16_t CAPEVTOST:1;               // 8 CAPEVT One-shot select
    uint16_t rsvd2:7;                   // 15:9 Reserved
};

union EPWM_TZSEL2_REG {
    uint16_t  all;
    struct  EPWM_TZSEL2_BITS  bit;
};

struct EPWM_TZDCSEL_BITS {              // bits description
    uint16_t DCAEVT1:3;                 // 2:0 Digital Compare Output A Event 1
    uint16_t DCAEVT2:3;                 // 5:3 Digital Compare Output A Event 2
    uint16_t DCBEVT1:3;                 // 8:6 Digital Compare Output B Event 1
    uint16_t DCBEVT2:3;                 // 11:9 Digital Compare Output B Event 2
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union EPWM_TZDCSEL_REG {
    uint16_t  all;
    struct  EPWM_TZDCSEL_BITS  bit;
};

struct EPWM_TZCTL_BITS {                // bits description
    uint16_t TZA:2;                     // 1:0 TZ1 to TZ6 Trip Action On EPWMxA
    uint16_t TZB:2;                     // 3:2 TZ1 to TZ6 Trip Action On EPWMxB
    uint16_t DCAEVT1:2;                 // 5:4 EPWMxA action on DCAEVT1
    uint16_t DCAEVT2:2;                 // 7:6 EPWMxA action on DCAEVT2
    uint16_t DCBEVT1:2;                 // 9:8 EPWMxB action on DCBEVT1
    uint16_t DCBEVT2:2;                 // 11:10 EPWMxB action on DCBEVT2
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union EPWM_TZCTL_REG {
    uint16_t  all;
    struct  EPWM_TZCTL_BITS  bit;
};

struct EPWM_TZCTL2_BITS {               // bits description
    uint16_t TZAU:3;                    // 2:0 Trip Action On EPWMxA while Count direction is UP
    uint16_t TZAD:3;                    // 5:3 Trip Action On EPWMxA while Count direction is DOWN
    uint16_t TZBU:3;                    // 8:6 Trip Action On EPWMxB while Count direction is UP
    uint16_t TZBD:3;                    // 11:9 Trip Action On EPWMxB while Count direction is DOWN
    uint16_t rsvd1:3;                   // 14:12 Reserved
    uint16_t ETZE:1;                    // 15 TZCTL2 Enable
};

union EPWM_TZCTL2_REG {
    uint16_t  all;
    struct  EPWM_TZCTL2_BITS  bit;
};

struct EPWM_TZCTLDCA_BITS {             // bits description
    uint16_t DCAEVT1U:3;                // 2:0 DCAEVT1 Action On EPWMxA while Count direction is UP
    uint16_t DCAEVT1D:3;                // 5:3 DCAEVT1 Action On EPWMxA while Count direction is DOWN
    uint16_t DCAEVT2U:3;                // 8:6 DCAEVT2 Action On EPWMxA while Count direction is UP
    uint16_t DCAEVT2D:3;                // 11:9 DCAEVT2 Action On EPWMxA while Count direction is DOWN
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union EPWM_TZCTLDCA_REG {
    uint16_t  all;
    struct  EPWM_TZCTLDCA_BITS  bit;
};

struct EPWM_TZCTLDCB_BITS {             // bits description
    uint16_t DCBEVT1U:3;                // 2:0 DCBEVT1 Action On EPWMxA while Count direction is UP
    uint16_t DCBEVT1D:3;                // 5:3 DCBEVT1 Action On EPWMxA while Count direction is DOWN
    uint16_t DCBEVT2U:3;                // 8:6 DCBEVT2 Action On EPWMxA while Count direction is UP
    uint16_t DCBEVT2D:3;                // 11:9 DCBEVT2 Action On EPWMxA while Count direction is DOWN
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union EPWM_TZCTLDCB_REG {
    uint16_t  all;
    struct  EPWM_TZCTLDCB_BITS  bit;
};

struct EPWM_TZEINT_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CBC:1;                     // 1 Trip Zones Cycle By Cycle Int Enable
    uint16_t OST:1;                     // 2 Trip Zones One Shot Int Enable
    uint16_t DCAEVT1:1;                 // 3 Digital Compare A Event 1 Int Enable
    uint16_t DCAEVT2:1;                 // 4 Digital Compare A Event 2 Int Enable
    uint16_t DCBEVT1:1;                 // 5 Digital Compare B Event 1 Int Enable
    uint16_t DCBEVT2:1;                 // 6 Digital Compare B Event 2 Int Enable
    uint16_t CAPEVT:1;                  // 7 Capture Eveent Interrupt Enable
    uint16_t rsvd2:8;                   // 15:8 Reserved
};

union EPWM_TZEINT_REG {
    uint16_t  all;
    struct  EPWM_TZEINT_BITS  bit;
};

struct EPWM_TZFLG_BITS {                // bits description
    uint16_t INT:1;                     // 0 Global Int Status Flag
    uint16_t CBC:1;                     // 1 Trip Zones Cycle By Cycle Flag
    uint16_t OST:1;                     // 2 Trip Zones One Shot Flag
    uint16_t DCAEVT1:1;                 // 3 Digital Compare A Event 1 Flag
    uint16_t DCAEVT2:1;                 // 4 Digital Compare A Event 2 Flag
    uint16_t DCBEVT1:1;                 // 5 Digital Compare B Event 1 Flag
    uint16_t DCBEVT2:1;                 // 6 Digital Compare B Event 2 Flag
    uint16_t CAPEVT:1;                  // 7 Capture Event Flag
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union EPWM_TZFLG_REG {
    uint16_t  all;
    struct  EPWM_TZFLG_BITS  bit;
};

struct EPWM_TZCBCFLG_BITS {             // bits description
    uint16_t CBC1:1;                    // 0 Latched Status Flag for CBC1 Trip Latch
    uint16_t CBC2:1;                    // 1 Latched Status Flag for CBC2 Trip Latch
    uint16_t CBC3:1;                    // 2 Latched Status Flag for CBC3 Trip Latch
    uint16_t CBC4:1;                    // 3 Latched Status Flag for CBC4 Trip Latch
    uint16_t CBC5:1;                    // 4 Latched Status Flag for CBC5 Trip Latch
    uint16_t CBC6:1;                    // 5 Latched Status Flag for CBC6 Trip Latch
    uint16_t DCAEVT2:1;                 // 6 Latched Status Flag for Digital Compare Output A Event 2
    uint16_t DCBEVT2:1;                 // 7 Latched Status Flag for Digital Compare Output B Event 2
    uint16_t CAPEVT:1;                  // 8 Capture Event Flag
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union EPWM_TZCBCFLG_REG {
    uint16_t  all;
    struct  EPWM_TZCBCFLG_BITS  bit;
};

struct EPWM_TZOSTFLG_BITS {             // bits description
    uint16_t OST1:1;                    // 0 Latched Status Flag for OST1 Trip Latch
    uint16_t OST2:1;                    // 1 Latched Status Flag for OST2 Trip Latch
    uint16_t OST3:1;                    // 2 Latched Status Flag for OST3 Trip Latch
    uint16_t OST4:1;                    // 3 Latched Status Flag for OST4 Trip Latch
    uint16_t OST5:1;                    // 4 Latched Status Flag for OST5 Trip Latch
    uint16_t OST6:1;                    // 5 Latched Status Flag for OST6 Trip Latch
    uint16_t DCAEVT1:1;                 // 6 Latched Status Flag for Digital Compare Output A Event 1
    uint16_t DCBEVT1:1;                 // 7 Latched Status Flag for Digital Compare Output B Event 1
    uint16_t CAPEVT:1;                  // 8 Capture Event Flag
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union EPWM_TZOSTFLG_REG {
    uint16_t  all;
    struct  EPWM_TZOSTFLG_BITS  bit;
};

struct EPWM_TZCLR_BITS {                // bits description
    uint16_t INT:1;                     // 0 Global Interrupt Clear Flag
    uint16_t CBC:1;                     // 1 Cycle-By-Cycle Flag Clear
    uint16_t OST:1;                     // 2 One-Shot Flag Clear
    uint16_t DCAEVT1:1;                 // 3 DCAVET1 Flag Clear
    uint16_t DCAEVT2:1;                 // 4 DCAEVT2 Flag Clear
    uint16_t DCBEVT1:1;                 // 5 DCBEVT1 Flag Clear
    uint16_t DCBEVT2:1;                 // 6 DCBEVT2 Flag Clear
    uint16_t CAPEVT:1;                  // 7 Capture Event Clear
    uint16_t rsvd1:6;                   // 13:8 Reserved
    uint16_t CBCPULSE:2;                // 15:14 Clear Pulse for CBC Trip Latch
};

union EPWM_TZCLR_REG {
    uint16_t  all;
    struct  EPWM_TZCLR_BITS  bit;
};

struct EPWM_TZCBCCLR_BITS {             // bits description
    uint16_t CBC1:1;                    // 0 Clear Flag for Cycle-By-Cycle (CBC1) Trip Latch
    uint16_t CBC2:1;                    // 1 Clear Flag for Cycle-By-Cycle (CBC2) Trip Latch
    uint16_t CBC3:1;                    // 2 Clear Flag for Cycle-By-Cycle (CBC3) Trip Latch
    uint16_t CBC4:1;                    // 3 Clear Flag for Cycle-By-Cycle (CBC4) Trip Latch
    uint16_t CBC5:1;                    // 4 Clear Flag for Cycle-By-Cycle (CBC5) Trip Latch
    uint16_t CBC6:1;                    // 5 Clear Flag for Cycle-By-Cycle (CBC6) Trip Latch
    uint16_t DCAEVT2:1;                 // 6 Clear Flag forDCAEVT2 selected for CBC
    uint16_t DCBEVT2:1;                 // 7 Clear Flag for DCBEVT2 selected for CBC
    uint16_t CAPEVT:1;                  // 8 Clear Flag for CAPEVT selected for CBC
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union EPWM_TZCBCCLR_REG {
    uint16_t  all;
    struct  EPWM_TZCBCCLR_BITS  bit;
};

struct EPWM_TZOSTCLR_BITS {             // bits description
    uint16_t OST1:1;                    // 0 Clear Flag for Oneshot (OST1) Trip Latch
    uint16_t OST2:1;                    // 1 Clear Flag for Oneshot (OST2) Trip Latch
    uint16_t OST3:1;                    // 2 Clear Flag for Oneshot (OST3) Trip Latch
    uint16_t OST4:1;                    // 3 Clear Flag for Oneshot (OST4) Trip Latch
    uint16_t OST5:1;                    // 4 Clear Flag for Oneshot (OST5) Trip Latch
    uint16_t OST6:1;                    // 5 Clear Flag for Oneshot (OST6) Trip Latch
    uint16_t DCAEVT1:1;                 // 6 Clear Flag for DCAEVT1 selected for OST
    uint16_t DCBEVT1:1;                 // 7 Clear Flag for DCBEVT1 selected for OST
    uint16_t CAPEVT:1;                  // 8 Clear Flag for CAPEVT selected for OST
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union EPWM_TZOSTCLR_REG {
    uint16_t  all;
    struct  EPWM_TZOSTCLR_BITS  bit;
};

struct EPWM_TZFRC_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CBC:1;                     // 1 Force Trip Zones Cycle By Cycle Event
    uint16_t OST:1;                     // 2 Force Trip Zones One Shot Event
    uint16_t DCAEVT1:1;                 // 3 Force Digital Compare A Event 1
    uint16_t DCAEVT2:1;                 // 4 Force Digital Compare A Event 2
    uint16_t DCBEVT1:1;                 // 5 Force Digital Compare B Event 1
    uint16_t DCBEVT2:1;                 // 6 Force Digital Compare B Event 2
    uint16_t CAPEVT:1;                  // 7 Force Capture Event
    uint16_t rsvd2:8;                   // 15:8 Reserved
};

union EPWM_TZFRC_REG {
    uint16_t  all;
    struct  EPWM_TZFRC_BITS  bit;
};

struct EPWM_TZTRIPOUTSEL_BITS {         // bits description
    uint16_t OST:1;                     // 0 OST TRIPOUT select
    uint16_t CBC:1;                     // 1 CBC TRIPOUT select
    uint16_t TZ1:1;                     // 2 TZ1 TRIPOUT select
    uint16_t TZ2:1;                     // 3 TZ2 TRIPOUT select
    uint16_t TZ3:1;                     // 4 TZ3 TRIPOUT select
    uint16_t TZ4:1;                     // 5 TZ4 TRIPOUT select
    uint16_t TZ5:1;                     // 6 TZ5 TRIPOUT select
    uint16_t TZ6:1;                     // 7 TZ6 TRIPOUT select
    uint16_t DCAEVT1:1;                 // 8 DCAEVT1.force TRIPOUT select
    uint16_t DCAEVT2:1;                 // 9 DCAEVT2.force TRIPOUT select
    uint16_t DCBEVT1:1;                 // 10 DCBEVT1.force TRIPOUT select
    uint16_t DCBEVT2:1;                 // 11 DCBEVT2.force TRIPOUT select
    uint16_t CAPEVT:1;                  // 12 CAPEVT TRIPOUT select
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union EPWM_TZTRIPOUTSEL_REG {
    uint16_t  all;
    struct  EPWM_TZTRIPOUTSEL_BITS  bit;
};

struct EPWM_ETSEL_BITS {                // bits description
    uint16_t INTSEL:3;                  // 2:0 EPWMxINTn Select
    uint16_t INTEN:1;                   // 3 EPWMxINTn Enable
    uint16_t SOCASELCMP:1;              // 4 EPWMxSOCA Compare Select
    uint16_t SOCBSELCMP:1;              // 5 EPWMxSOCB Compare Select
    uint16_t INTSELCMP:1;               // 6 EPWMxINT Compare Select
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t SOCASEL:3;                 // 10:8 Start of Conversion A Select
    uint16_t SOCAEN:1;                  // 11 Start of Conversion A Enable
    uint16_t SOCBSEL:3;                 // 14:12 Start of Conversion B Select
    uint16_t SOCBEN:1;                  // 15 Start of Conversion B Enable
};

union EPWM_ETSEL_REG {
    uint16_t  all;
    struct  EPWM_ETSEL_BITS  bit;
};

struct EPWM_ETPS_BITS {                 // bits description
    uint16_t INTPRD:2;                  // 1:0 EPWMxINTn Period Select
    uint16_t INTCNT:2;                  // 3:2 EPWMxINTn Counter Register
    uint16_t INTPSSEL:1;                // 4 EPWMxINTn Pre-Scale Selection Bits
    uint16_t SOCPSSEL:1;                // 5 EPWMxSOC A/B  Pre-Scale Selection Bits
    uint16_t rsvd1:2;                   // 7:6 Reserved
    uint16_t SOCAPRD:2;                 // 9:8 EPWMxSOCA Period Select
    uint16_t SOCACNT:2;                 // 11:10 EPWMxSOCA Counter Register
    uint16_t SOCBPRD:2;                 // 13:12 EPWMxSOCB Period Select
    uint16_t SOCBCNT:2;                 // 15:14 EPWMxSOCB Counter
};

union EPWM_ETPS_REG {
    uint16_t  all;
    struct  EPWM_ETPS_BITS  bit;
};

struct EPWM_ETFLG_BITS {                // bits description
    uint16_t INT:1;                     // 0 EPWMxINTn Flag
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t SOCA:1;                    // 2 EPWMxSOCA Flag
    uint16_t SOCB:1;                    // 3 EPWMxSOCB Flag
    uint16_t rsvd2:12;                  // 15:4 Reserved
};

union EPWM_ETFLG_REG {
    uint16_t  all;
    struct  EPWM_ETFLG_BITS  bit;
};

struct EPWM_ETCLR_BITS {                // bits description
    uint16_t INT:1;                     // 0 EPWMxINTn Clear
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t SOCA:1;                    // 2 EPWMxSOCA Clear
    uint16_t SOCB:1;                    // 3 EPWMxSOCB Clear
    uint16_t rsvd2:12;                  // 15:4 Reserved
};

union EPWM_ETCLR_REG {
    uint16_t  all;
    struct  EPWM_ETCLR_BITS  bit;
};

struct EPWM_ETFRC_BITS {                // bits description
    uint16_t INT:1;                     // 0 EPWMxINTn Force
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t SOCA:1;                    // 2 EPWMxSOCA Force
    uint16_t SOCB:1;                    // 3 EPWMxSOCB Force
    uint16_t rsvd2:12;                  // 15:4 Reserved
};

union EPWM_ETFRC_REG {
    uint16_t  all;
    struct  EPWM_ETFRC_BITS  bit;
};

struct EPWM_ETINTPS_BITS {              // bits description
    uint16_t INTPRD2:4;                 // 3:0 EPWMxINTn Period Select
    uint16_t INTCNT2:4;                 // 7:4 EPWMxINTn Counter Register
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union EPWM_ETINTPS_REG {
    uint16_t  all;
    struct  EPWM_ETINTPS_BITS  bit;
};

struct EPWM_ETSOCPS_BITS {              // bits description
    uint16_t SOCAPRD2:4;                // 3:0 EPWMxSOCA Period Select
    uint16_t SOCACNT2:4;                // 7:4 EPWMxSOCA Counter Register
    uint16_t SOCBPRD2:4;                // 11:8 EPWMxSOCB Period Select
    uint16_t SOCBCNT2:4;                // 15:12 EPWMxSOCB Counter Register
};

union EPWM_ETSOCPS_REG {
    uint16_t  all;
    struct  EPWM_ETSOCPS_BITS  bit;
};

struct EPWM_ETCNTINITCTL_BITS {         // bits description
    uint16_t rsvd1:10;                  // 9:0 Reserved
    uint16_t INTINITFRC:1;              // 10 EPWMxINT Counter Initialization Force
    uint16_t SOCAINITFRC:1;             // 11 EPWMxSOCA Counter Initialization Force
    uint16_t SOCBINITFRC:1;             // 12 EPWMxSOCB Counter Initialization Force
    uint16_t INTINITEN:1;               // 13 EPWMxINT Counter Initialization Enable
    uint16_t SOCAINITEN:1;              // 14 EPWMxSOCA Counter Initialization Enable
    uint16_t SOCBINITEN:1;              // 15 EPWMxSOCB Counter Initialization Enable
};

union EPWM_ETCNTINITCTL_REG {
    uint16_t  all;
    struct  EPWM_ETCNTINITCTL_BITS  bit;
};

struct EPWM_ETCNTINIT_BITS {            // bits description
    uint16_t INTINIT:4;                 // 3:0 EPWMxINT Counter Initialization Bits
    uint16_t SOCAINIT:4;                // 7:4 EPWMxSOCA Counter Initialization Bits
    uint16_t SOCBINIT:4;                // 11:8 EPWMxSOCB Counter Initialization Bits
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union EPWM_ETCNTINIT_REG {
    uint16_t  all;
    struct  EPWM_ETCNTINIT_BITS  bit;
};

struct EPWM_ETINTMIXEN_BITS {           // bits description
    uint16_t ZRO:1;                     // 0 Zero match enable to ETINTMIX
    uint16_t PRD:1;                     // 1 Period match enable to ETINTMIX
    uint16_t CAU:1;                     // 2 CMPA up-count match enable to ETINTMIX
    uint16_t CAD:1;                     // 3 CMPA down-count match enable to ETINTMIX
    uint16_t CBU:1;                     // 4 CMPB up-count match enable to ETINTMIX
    uint16_t CBD:1;                     // 5 CMPB down-count match enable to ETINTMIX
    uint16_t CCU:1;                     // 6 CMPC up-count match enable to ETINTMIX
    uint16_t CCD:1;                     // 7 CMPC down-count match enable to ETINTMIX
    uint16_t CDU:1;                     // 8 CMPD up-count match enable to ETINTMIX
    uint16_t CDD:1;                     // 9 CMPD down-count match enable to ETINTMIX
    uint16_t DCAEVT1:1;                 // 10 DCAEVT1.inter enable to ETINTMIX
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union EPWM_ETINTMIXEN_REG {
    uint16_t  all;
    struct  EPWM_ETINTMIXEN_BITS  bit;
};

struct EPWM_ETSOCAMIXEN_BITS {          // bits description
    uint16_t ZRO:1;                     // 0 Zero match enable to ETSOCAMIX
    uint16_t PRD:1;                     // 1 Period match enable to ETSOCAMIX
    uint16_t CAU:1;                     // 2 CMPA up-count match enable to ETSOCAMIX
    uint16_t CAD:1;                     // 3 CMPA down-count match enable to ETSOCAMIX
    uint16_t CBU:1;                     // 4 CMPB up-count match enable to ETSOCAMIX
    uint16_t CBD:1;                     // 5 CMPB down-count match enable to ETSOCAMIX
    uint16_t CCU:1;                     // 6 CMPC up-count match enable to ETSOCAMIX
    uint16_t CCD:1;                     // 7 CMPC down-count match enable to ETSOCAMIX
    uint16_t CDU:1;                     // 8 CMPD up-count match enable to ETSOCAMIX
    uint16_t CDD:1;                     // 9 CMPD down-count match enable to ETSOCAMIX
    uint16_t DCAEVT1:1;                 // 10 DCAEVT1.inter enable to ETSOCAMIX
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union EPWM_ETSOCAMIXEN_REG {
    uint16_t  all;
    struct  EPWM_ETSOCAMIXEN_BITS  bit;
};

struct EPWM_ETSOCBMIXEN_BITS {          // bits description
    uint16_t ZRO:1;                     // 0 Zero match enable to ETSOCBMIX
    uint16_t PRD:1;                     // 1 Period match enable to ETSOCBMIX
    uint16_t CAU:1;                     // 2 CMPA up-count match enable to ETSOCBMIX
    uint16_t CAD:1;                     // 3 CMPA down-count match enable to ETSOCBMIX
    uint16_t CBU:1;                     // 4 CMPB up-count match enable to ETSOCBMIX
    uint16_t CBD:1;                     // 5 CMPB down-count match enable to ETSOCBMIX
    uint16_t CCU:1;                     // 6 CMPC up-count match enable to ETSOCBMIX
    uint16_t CCD:1;                     // 7 CMPC down-count match enable to ETSOCBMIX
    uint16_t CDU:1;                     // 8 CMPD up-count match enable to ETSOCBMIX
    uint16_t CDD:1;                     // 9 CMPD down-count match enable to ETSOCBMIX
    uint16_t DCBEVT1:1;                 // 10 DCBEVT1.inter enable to ETSOCBMIX
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union EPWM_ETSOCBMIXEN_REG {
    uint16_t  all;
    struct  EPWM_ETSOCBMIXEN_BITS  bit;
};

struct EPWM_DCTRIPSEL_BITS {            // bits description
    uint16_t DCAHCOMPSEL:4;             // 3:0 Digital Compare A High COMP Input Select
    uint16_t DCALCOMPSEL:4;             // 7:4 Digital Compare A Low COMP Input Select
    uint16_t DCBHCOMPSEL:4;             // 11:8 Digital Compare B High COMP Input Select
    uint16_t DCBLCOMPSEL:4;             // 15:12 Digital Compare B Low COMP Input Select
};

union EPWM_DCTRIPSEL_REG {
    uint16_t  all;
    struct  EPWM_DCTRIPSEL_BITS  bit;
};

struct EPWM_DCACTL_BITS {               // bits description
    uint16_t EVT1SRCSEL:1;              // 0 DCAEVT1 Source Signal
    uint16_t EVT1FRCSYNCSEL:1;          // 1 DCAEVT1 Force Sync Signal
    uint16_t EVT1SOCE:1;                // 2 DCAEVT1 SOC Enable
    uint16_t EVT1SYNCE:1;               // 3 DCAEVT1 SYNC Enable
    uint16_t EVT1LATSEL:1;              // 4 DCAEVT1 Latched signal select
    uint16_t EVT1LATCLRSEL:2;           // 6:5 DCAEVT1 Latched clear source select
    uint16_t EVT1LAT:1;                 // 7 Indicates the status of DCAEVT1LAT signal.
    uint16_t EVT2SRCSEL:1;              // 8 DCAEVT2 Source Signal
    uint16_t EVT2FRCSYNCSEL:1;          // 9 DCAEVT2 Force Sync Signal
    uint16_t rsvd1:2;                   // 11:10 Reserved
    uint16_t EVT2LATSEL:1;              // 12 DCAEVT2 Latched signal select
    uint16_t EVT2LATCLRSEL:2;           // 14:13 DCAEVT2 Latched clear source select
    uint16_t EVT2LAT:1;                 // 15 Indicates the status of DCAEVT2LAT signal.
};

union EPWM_DCACTL_REG {
    uint16_t  all;
    struct  EPWM_DCACTL_BITS  bit;
};

struct EPWM_DCBCTL_BITS {               // bits description
    uint16_t EVT1SRCSEL:1;              // 0 DCBEVT1 Source Signal
    uint16_t EVT1FRCSYNCSEL:1;          // 1 DCBEVT1 Force Sync Signal
    uint16_t EVT1SOCE:1;                // 2 DCBEVT1 SOC Enable
    uint16_t EVT1SYNCE:1;               // 3 DCBEVT1 SYNC Enable
    uint16_t EVT1LATSEL:1;              // 4 DCBEVT1 Latched signal select
    uint16_t EVT1LATCLRSEL:2;           // 6:5 DCBEVT1 Latched clear source select
    uint16_t EVT1LAT:1;                 // 7 Indicates the status of DCBEVT1LAT signal.
    uint16_t EVT2SRCSEL:1;              // 8 DCBEVT2 Source Signal
    uint16_t EVT2FRCSYNCSEL:1;          // 9 DCBEVT2 Force Sync Signal
    uint16_t rsvd1:2;                   // 11:10 Reserved
    uint16_t EVT2LATSEL:1;              // 12 DCBEVT2 Latched signal select
    uint16_t EVT2LATCLRSEL:2;           // 14:13 DCBEVT2 Latched clear source select
    uint16_t EVT2LAT:1;                 // 15 Indicates the status of DCBEVT2LAT signal.
};

union EPWM_DCBCTL_REG {
    uint16_t  all;
    struct  EPWM_DCBCTL_BITS  bit;
};

struct EPWM_DCFCTL_BITS {               // bits description
    uint16_t SRCSEL:2;                  // 1:0 Filter Block Signal Source Select
    uint16_t BLANKE:1;                  // 2 Blanking Enable/Disable
    uint16_t BLANKINV:1;                // 3 Blanking Window Inversion
    uint16_t PULSESEL:2;                // 5:4 Pulse Select for Blanking & Capture Alignment
    uint16_t EDGEFILTSEL:1;             // 6 Edge Filter Select
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t EDGEMODE:2;                // 9:8 Edge Mode
    uint16_t EDGECOUNT:3;               // 12:10 Edge Count
    uint16_t EDGESTATUS:3;              // 15:13 Edge Status
};

union EPWM_DCFCTL_REG {
    uint16_t  all;
    struct  EPWM_DCFCTL_BITS  bit;
};

struct EPWM_DCCAPCTL_BITS {             // bits description
    uint16_t CAPE:1;                    // 0 Counter Capture Enable
    uint16_t SHDWMODE:1;                // 1 Counter Capture Mode
    uint16_t rsvd1:11;                  // 12:2 Reserved
    uint16_t CAPSTS:1;                  // 13 Latched Status Flag for Capture Event
    uint16_t CAPCLR:1;                  // 14 DC Capture Latched Status Clear Flag
    uint16_t CAPMODE:1;                 // 15 Counter Capture Mode
};

union EPWM_DCCAPCTL_REG {
    uint16_t  all;
    struct  EPWM_DCCAPCTL_BITS  bit;
};

struct EPWM_BLANKPULSEMIXSEL_BITS {     // bits description
    uint16_t ZRO:1;                     // 0 Zero match enable to BLANKPULSEMIX
    uint16_t PRD:1;                     // 1 Period match enable to BLANKPULSEMIX
    uint16_t CAU:1;                     // 2 CMPA up-count match enable to BLANKPULSEMIX
    uint16_t CAD:1;                     // 3 CMPA down-count match enable to BLANKPULSEMIX
    uint16_t CBU:1;                     // 4 CMPB up-count match enable to BLANKPULSEMIX
    uint16_t CBD:1;                     // 5 CMPB down-count match enable to BLANKPULSEMIX
    uint16_t CCU:1;                     // 6 CMPC up-count match enable to BLANKPULSEMIX
    uint16_t CCD:1;                     // 7 CMPC down-count match enable to BLANKPULSEMIX
    uint16_t CDU:1;                     // 8 CMPD up-count match enable to BLANKPULSEMIX
    uint16_t CDD:1;                     // 9 CMPD down-count match enable to BLANKPULSEMIX
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union EPWM_BLANKPULSEMIXSEL_REG {
    uint16_t  all;
    struct  EPWM_BLANKPULSEMIXSEL_BITS  bit;
};

struct EPWM_DCCAPMIXSEL_BITS {          // bits description
    uint16_t ZRO:1;                     // 0 Zero match enable to DCCAPMIX
    uint16_t PRD:1;                     // 1 Period match enable to DCCAPMIX
    uint16_t CAU:1;                     // 2 CMPA up-count match enable to DCCAPMIX
    uint16_t CAD:1;                     // 3 CMPA down-count match enable to DCCAPMIX
    uint16_t CBU:1;                     // 4 CMPB up-count match enable to DCCAPMIX
    uint16_t CBD:1;                     // 5 CMPB down-count match enable to DCCAPMIX
    uint16_t CCU:1;                     // 6 CMPC up-count match enable to DCCAPMIX
    uint16_t CCD:1;                     // 7 CMPC down-count match enable to DCCAPMIX
    uint16_t CDU:1;                     // 8 CMPD up-count match enable to DCCAPMIX
    uint16_t CDD:1;                     // 9 CMPD down-count match enable to DCCAPMIX
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union EPWM_DCCAPMIXSEL_REG {
    uint16_t  all;
    struct  EPWM_DCCAPMIXSEL_BITS  bit;
};

struct EPWM_DCAHTRIPSEL_BITS {          // bits description
    uint16_t TRIPINPUT1:1;              // 0 Trip Input 1 Select to DCAH Mux
    uint16_t TRIPINPUT2:1;              // 1 Trip Input 2 Select to DCAH Mux
    uint16_t TRIPINPUT3:1;              // 2 Trip Input 3 Select to DCAH Mux
    uint16_t TRIPINPUT4:1;              // 3 Trip Input 4 Select to DCAH Mux
    uint16_t TRIPINPUT5:1;              // 4 Trip Input 5 Select to DCAH Mux
    uint16_t TRIPINPUT6:1;              // 5 Trip Input 6 Select to DCAH Mux
    uint16_t TRIPINPUT7:1;              // 6 Trip Input 7 Select to DCAH Mux
    uint16_t TRIPINPUT8:1;              // 7 Trip Input 8 Select to DCAH Mux
    uint16_t TRIPINPUT9:1;              // 8 Trip Input 9 Select to DCAH Mux
    uint16_t TRIPINPUT10:1;             // 9 Trip Input 10 Select to DCAH Mux
    uint16_t TRIPINPUT11:1;             // 10 Trip Input 11 Select to DCAH Mux
    uint16_t TRIPINPUT12:1;             // 11 Trip Input 12 Select to DCAH Mux
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t TRIPINPUT14:1;             // 13 Trip Input 14 Select to DCAH Mux
    uint16_t TRIPINPUT15:1;             // 14 Trip Input 15 Select to DCAH Mux
    uint16_t rsvd2:1;                   // 15 Reserved
};

union EPWM_DCAHTRIPSEL_REG {
    uint16_t  all;
    struct  EPWM_DCAHTRIPSEL_BITS  bit;
};

struct EPWM_DCALTRIPSEL_BITS {          // bits description
    uint16_t TRIPINPUT1:1;              // 0 Trip Input 1 Select to DCAL Mux
    uint16_t TRIPINPUT2:1;              // 1 Trip Input 2 Select to DCAL Mux
    uint16_t TRIPINPUT3:1;              // 2 Trip Input 3 Select to DCAL Mux
    uint16_t TRIPINPUT4:1;              // 3 Trip Input 4 Select to DCAL Mux
    uint16_t TRIPINPUT5:1;              // 4 Trip Input 5 Select to DCAL Mux
    uint16_t TRIPINPUT6:1;              // 5 Trip Input 6 Select to DCAL Mux
    uint16_t TRIPINPUT7:1;              // 6 Trip Input 7 Select to DCAL Mux
    uint16_t TRIPINPUT8:1;              // 7 Trip Input 8 Select to DCAL Mux
    uint16_t TRIPINPUT9:1;              // 8 Trip Input 9 Select to DCAL Mux
    uint16_t TRIPINPUT10:1;             // 9 Trip Input 10 Select to DCAL Mux
    uint16_t TRIPINPUT11:1;             // 10 Trip Input 11 Select to DCAL Mux
    uint16_t TRIPINPUT12:1;             // 11 Trip Input 12 Select to DCAL Mux
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t TRIPINPUT14:1;             // 13 Trip Input 14 Select to DCAL Mux
    uint16_t TRIPINPUT15:1;             // 14 Trip Input 15 Select to DCAL Mux
    uint16_t rsvd2:1;                   // 15 Reserved
};

union EPWM_DCALTRIPSEL_REG {
    uint16_t  all;
    struct  EPWM_DCALTRIPSEL_BITS  bit;
};

struct EPWM_DCBHTRIPSEL_BITS {          // bits description
    uint16_t TRIPINPUT1:1;              // 0 Trip Input 1 Select to DCBH Mux
    uint16_t TRIPINPUT2:1;              // 1 Trip Input 2 Select to DCBH Mux
    uint16_t TRIPINPUT3:1;              // 2 Trip Input 3 Select to DCBH Mux
    uint16_t TRIPINPUT4:1;              // 3 Trip Input 4 Select to DCBH Mux
    uint16_t TRIPINPUT5:1;              // 4 Trip Input 5 Select to DCBH Mux
    uint16_t TRIPINPUT6:1;              // 5 Trip Input 6 Select to DCBH Mux
    uint16_t TRIPINPUT7:1;              // 6 Trip Input 7 Select to DCBH Mux
    uint16_t TRIPINPUT8:1;              // 7 Trip Input 8 Select to DCBH Mux
    uint16_t TRIPINPUT9:1;              // 8 Trip Input 9 Select to DCBH Mux
    uint16_t TRIPINPUT10:1;             // 9 Trip Input 10 Select to DCBH Mux
    uint16_t TRIPINPUT11:1;             // 10 Trip Input 11 Select to DCBH Mux
    uint16_t TRIPINPUT12:1;             // 11 Trip Input 12 Select to DCBH Mux
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t TRIPINPUT14:1;             // 13 Trip Input 14 Select to DCBH Mux
    uint16_t TRIPINPUT15:1;             // 14 Trip Input 15 Select to DCBH Mux
    uint16_t rsvd2:1;                   // 15 Reserved
};

union EPWM_DCBHTRIPSEL_REG {
    uint16_t  all;
    struct  EPWM_DCBHTRIPSEL_BITS  bit;
};

struct EPWM_DCBLTRIPSEL_BITS {          // bits description
    uint16_t TRIPINPUT1:1;              // 0 Trip Input 1 Select to DCBL Mux
    uint16_t TRIPINPUT2:1;              // 1 Trip Input 2 Select to DCBL Mux
    uint16_t TRIPINPUT3:1;              // 2 Trip Input 3 Select to DCBL Mux
    uint16_t TRIPINPUT4:1;              // 3 Trip Input 4 Select to DCBL Mux
    uint16_t TRIPINPUT5:1;              // 4 Trip Input 5 Select to DCBL Mux
    uint16_t TRIPINPUT6:1;              // 5 Trip Input 6 Select to DCBL Mux
    uint16_t TRIPINPUT7:1;              // 6 Trip Input 7 Select to DCBL Mux
    uint16_t TRIPINPUT8:1;              // 7 Trip Input 8 Select to DCBL Mux
    uint16_t TRIPINPUT9:1;              // 8 Trip Input 9 Select to DCBL Mux
    uint16_t TRIPINPUT10:1;             // 9 Trip Input 10 Select to DCBL Mux
    uint16_t TRIPINPUT11:1;             // 10 Trip Input 11 Select to DCBL Mux
    uint16_t TRIPINPUT12:1;             // 11 Trip Input 12 Select to DCBL Mux
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t TRIPINPUT14:1;             // 13 Trip Input 14 Select to DCBL Mux
    uint16_t TRIPINPUT15:1;             // 14 Trip Input 15 Select to DCBL Mux
    uint16_t rsvd2:1;                   // 15 Reserved
};

union EPWM_DCBLTRIPSEL_REG {
    uint16_t  all;
    struct  EPWM_DCBLTRIPSEL_BITS  bit;
};

struct EPWM_CAPCTL_BITS {               // bits description
    uint16_t SRCSEL:1;                  // 0 Capture Logic Input Selection
    uint16_t CAPGATEPOL:2;              // 2:1 Polarity selection for Capture Gate input
    uint16_t CAPINPOL:1;                // 3 Polarity selection for Capture input
    uint16_t PULSECTL:1;                // 4 Polarity selection for Capture input
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint16_t FRCLOAD:1;                 // 8 Capture event force load
    uint16_t rsvd2:7;                   // 15:9 Reserved
};

union EPWM_CAPCTL_REG {
    uint16_t  all;
    struct  EPWM_CAPCTL_BITS  bit;
};

struct EPWM_CAPGATETRIPSEL_BITS {       // bits description
    uint16_t TRIPINPUT1:1;              // 0 Trip Input 1 Select to CAPGATE Mux
    uint16_t TRIPINPUT2:1;              // 1 Trip Input 2 Select to CAPGATE Mux
    uint16_t TRIPINPUT3:1;              // 2 Trip Input 3 Select to CAPGATE Mux
    uint16_t TRIPINPUT4:1;              // 3 Trip Input 4 Select to CAPGATE Mux
    uint16_t TRIPINPUT5:1;              // 4 Trip Input 5 Select to CAPGATE Mux
    uint16_t TRIPINPUT6:1;              // 5 Trip Input 6 Select to CAPGATE Mux
    uint16_t TRIPINPUT7:1;              // 6 Trip Input 7 Select to CAPGATE Mux
    uint16_t TRIPINPUT8:1;              // 7 Trip Input 8 Select to CAPGATE Mux
    uint16_t TRIPINPUT9:1;              // 8 Trip Input 9 Select to CAPGATE Mux
    uint16_t TRIPINPUT10:1;             // 9 Trip Input 10 Select to CAPGATE Mux
    uint16_t TRIPINPUT11:1;             // 10 Trip Input 11 Select to CAPGATE Mux
    uint16_t TRIPINPUT12:1;             // 11 Trip Input 12 Select to CAPGATE Mux
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t TRIPINPUT14:1;             // 13 Trip Input 14 Select to CAPGATE Mux
    uint16_t TRIPINPUT15:1;             // 14 Trip Input 15 Select to CAPGATE Mux
    uint16_t rsvd2:1;                   // 15 Reserved
};

union EPWM_CAPGATETRIPSEL_REG {
    uint16_t  all;
    struct  EPWM_CAPGATETRIPSEL_BITS  bit;
};

struct EPWM_CAPINTRIPSEL_BITS {         // bits description
    uint16_t TRIPINPUT1:1;              // 0 Trip Input 1 Select to CAPIN Mux
    uint16_t TRIPINPUT2:1;              // 1 Trip Input 2 Select to CAPIN Mux
    uint16_t TRIPINPUT3:1;              // 2 Trip Input 3 Select to CAPIN Mux
    uint16_t TRIPINPUT4:1;              // 3 Trip Input 4 Select to CAPIN Mux
    uint16_t TRIPINPUT5:1;              // 4 Trip Input 5 Select to CAPIN Mux
    uint16_t TRIPINPUT6:1;              // 5 Trip Input 6 Select to CAPIN Mux
    uint16_t TRIPINPUT7:1;              // 6 Trip Input 7 Select to CAPIN Mux
    uint16_t TRIPINPUT8:1;              // 7 Trip Input 8 Select to CAPIN Mux
    uint16_t TRIPINPUT9:1;              // 8 Trip Input 9 Select to CAPIN Mux
    uint16_t TRIPINPUT10:1;             // 9 Trip Input 10 Select to CAPIN Mux
    uint16_t TRIPINPUT11:1;             // 10 Trip Input 11 Select to CAPIN Mux
    uint16_t TRIPINPUT12:1;             // 11 Trip Input 12 Select to CAPIN Mux
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t TRIPINPUT14:1;             // 13 Trip Input 14 Select to CAPIN Mux
    uint16_t TRIPINPUT15:1;             // 14 Trip Input 15 Select to CAPIN Mux
    uint16_t rsvd2:1;                   // 15 Reserved
};

union EPWM_CAPINTRIPSEL_REG {
    uint16_t  all;
    struct  EPWM_CAPINTRIPSEL_BITS  bit;
};

struct EPWM_CAPTRIPSEL_BITS {           // bits description
    uint16_t CAPINCOMPSEL:4;            // 3:0 CAPIN Comparator Input Select
    uint16_t CAPGATECOMPSEL:4;          // 7:4 CAPGATE Comparator COMP Input Select
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union EPWM_CAPTRIPSEL_REG {
    uint16_t  all;
    struct  EPWM_CAPTRIPSEL_BITS  bit;
};

struct EPWM_EPWMLOCK_BITS {             // bits description
    uint16_t HRLOCK:1;                  // 0 HRPWM Register Set Lock
    uint16_t GLLOCK:1;                  // 1 Global Load Register Set Lock
    uint16_t TZCFGLOCK:1;               // 2 TripZone Register Set Lock
    uint16_t TZCLRLOCK:1;               // 3 TripZone Clear Register Set Lock
    uint16_t DCLOCK:1;                  // 4 Digital Compare Register Set Lock
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t KEY:16;                    // 31:16 Key to write to this register
};

union EPWM_EPWMLOCK_REG {
    uint32_t  all;
    struct  EPWM_EPWMLOCK_BITS  bit;
};

struct EPWM_REGS {
    union   EPWM_TBCTL_REG                   TBCTL;                        // Time Base Control Register
    union   EPWM_TBCTL2_REG                  TBCTL2;                       // Time Base Control Register 2
    uint8_t                                  rsvd1[2];                     // Reserved
    union   EPWM_EPWMSYNCINSEL_REG           EPWMSYNCINSEL;                // EPWMxSYNCIN Source Select Register
    uint16_t                                 TBCTR;                        // Time Base Counter Register
    union   EPWM_TBSTS_REG                   TBSTS;                        // Time Base Status Register
    union   EPWM_EPWMSYNCOUTEN_REG           EPWMSYNCOUTEN;                // EPWMxSYNCOUT Source Enable Register
    union   EPWM_TBCTL3_REG                  TBCTL3;                       // Time Base Control Register 3
    union   EPWM_CMPCTL_REG                  CMPCTL;                       // Counter Compare Control Register
    union   EPWM_CMPCTL2_REG                 CMPCTL2;                      // Counter Compare Control Register 2
    uint8_t                                  rsvd2[4];                     // Reserved
    union   EPWM_DBCTL_REG                   DBCTL;                        // Dead-Band Generator Control Register
    union   EPWM_DBCTL2_REG                  DBCTL2;                       // Dead-Band Generator Control Register 2
    uint8_t                                  rsvd3[4];                     // Reserved
    union   EPWM_AQCTL_REG                   AQCTL;                        // Action Qualifier Control Register
    union   EPWM_AQTSRCSEL_REG               AQTSRCSEL;                    // Action Qualifier Trigger Event Source Select Register
    uint8_t                                  rsvd4[4];                     // Reserved
    union   EPWM_PCCTL_REG                   PCCTL;                        // PWM Chopper Control Register
    uint8_t                                  rsvd5[6];                     // Reserved
    union   EPWM_VCAPCTL_REG                 VCAPCTL;                      // Valley Capture Control Register
    union   EPWM_VCNTCFG_REG                 VCNTCFG;                      // Valley Counter Config Register
    uint8_t                                  rsvd6[12];                    // Reserved
    union   EPWM_HRCNFG_REG                  HRCNFG;                       // HRPWM Configuration Register
    uint8_t                                  rsvd7[12];                    // Reserved
    union   EPWM_HRCNFG2_REG                 HRCNFG2;                      // HRPWM Configuration 2 Register
    uint8_t                                  rsvd8[10];                    // Reserved
    union   EPWM_HRPCTL_REG                  HRPCTL;                       // High Resolution Period Control Register
    union   EPWM_TRREM_REG                   TRREM;                        // HRPWM High Resolution Remainder Register
    uint8_t                                  rsvd9[10];                    // Reserved
    union   EPWM_GLDCTL_REG                  GLDCTL;                       // Global PWM Load Control Register
    union   EPWM_GLDCFG_REG                  GLDCFG;                       // Global PWM Load Config Register
    uint8_t                                  rsvd10[20];                   // Reserved
    union   EPWM_AQCTLA_REG                  AQCTLA;                       // Action Qualifier Control Register For Output A
    union   EPWM_AQCTLA2_REG                 AQCTLA2;                      // Additional Action Qualifier Control Register For Output A
    union   EPWM_AQCTLB_REG                  AQCTLB;                       // Action Qualifier Control Register For Output B
    union   EPWM_AQCTLB2_REG                 AQCTLB2;                      // Additional Action Qualifier Control Register For Output B
    uint8_t                                  rsvd11[6];                    // Reserved
    union   EPWM_AQSFRC_REG                  AQSFRC;                       // Action Qualifier Software Force Register
    uint8_t                                  rsvd12[2];                    // Reserved
    union   EPWM_AQCSFRC_REG                 AQCSFRC;                      // Action Qualifier Continuous S/W Force Register
    uint8_t                                  rsvd13[12];                   // Reserved
    union   EPWM_DBREDHR_REG                 DBREDHR;                      // Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    union   EPWM_DBRED_REG                   DBRED;                        // Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    union   EPWM_DBFEDHR_REG                 DBFEDHR;                      // Dead-Band Generator Falling Edge Delay High Resolution Register
    union   EPWM_DBFED_REG                   DBFED;                        // Dead-Band Generator Falling Edge Delay Count Register
    uint8_t                                  rsvd14[24];                   // Reserved
    union   EPWM_TBPHS_REG                   TBPHS;                        // Time Base Phase High
    uint16_t                                 TBPRDHR;                      // Time Base Period High Resolution Register
    uint16_t                                 TBPRD;                        // Time Base Period Register
    uint8_t                                  rsvd15[12];                   // Reserved
    union   EPWM_CMPA_REG                    CMPA;                         // Counter Compare A Register
    union   EPWM_CMPB_REG                    CMPB;                         // Compare B Register
    uint8_t                                  rsvd16[2];                    // Reserved
    uint16_t                                 CMPC;                         // Counter Compare C Register
    uint8_t                                  rsvd17[2];                    // Reserved
    uint16_t                                 CMPD;                         // Counter Compare D Register
    uint8_t                                  rsvd18[4];                    // Reserved
    union   EPWM_GLDCTL2_REG                 GLDCTL2;                      // Global PWM Load Control Register 2
    uint8_t                                  rsvd19[4];                    // Reserved
    uint16_t                                 SWVDELVAL;                    // Software Valley Mode Delay Register
    uint8_t                                  rsvd20[16];                   // Reserved
    union   EPWM_TZSEL_REG                   TZSEL;                        // Trip Zone Select Register
    union   EPWM_TZSEL2_REG                  TZSEL2;                       // Trip Zone Select Register 2
    union   EPWM_TZDCSEL_REG                 TZDCSEL;                      // Trip Zone Digital Comparator Select Register
    uint8_t                                  rsvd21[2];                    // Reserved
    union   EPWM_TZCTL_REG                   TZCTL;                        // Trip Zone Control Register
    union   EPWM_TZCTL2_REG                  TZCTL2;                       // Additional Trip Zone Control Register
    union   EPWM_TZCTLDCA_REG                TZCTLDCA;                     // Trip Zone Control Register Digital Compare A
    union   EPWM_TZCTLDCB_REG                TZCTLDCB;                     // Trip Zone Control Register Digital Compare B
    uint8_t                                  rsvd22[10];                   // Reserved
    union   EPWM_TZEINT_REG                  TZEINT;                       // Trip Zone Enable Interrupt Register
    uint8_t                                  rsvd23[10];                   // Reserved
    union   EPWM_TZFLG_REG                   TZFLG;                        // Trip Zone Flag Register
    union   EPWM_TZCBCFLG_REG                TZCBCFLG;                     // Trip Zone CBC Flag Register
    union   EPWM_TZOSTFLG_REG                TZOSTFLG;                     // Trip Zone OST Flag Register
    uint8_t                                  rsvd24[2];                    // Reserved
    union   EPWM_TZCLR_REG                   TZCLR;                        // Trip Zone Clear Register
    union   EPWM_TZCBCCLR_REG                TZCBCCLR;                     // Trip Zone CBC Clear Register
    union   EPWM_TZOSTCLR_REG                TZOSTCLR;                     // Trip Zone OST Clear Register
    uint8_t                                  rsvd25[2];                    // Reserved
    union   EPWM_TZFRC_REG                   TZFRC;                        // Trip Zone Force Register
    uint8_t                                  rsvd26[2];                    // Reserved
    union   EPWM_TZTRIPOUTSEL_REG            TZTRIPOUTSEL;                 // Trip Zone Force Register
    uint8_t                                  rsvd27[12];                   // Reserved
    union   EPWM_ETSEL_REG                   ETSEL;                        // Event Trigger Selection Register
    uint8_t                                  rsvd28[2];                    // Reserved
    union   EPWM_ETPS_REG                    ETPS;                         // Event Trigger Pre-Scale Register
    uint8_t                                  rsvd29[2];                    // Reserved
    union   EPWM_ETFLG_REG                   ETFLG;                        // Event Trigger Flag Register
    uint8_t                                  rsvd30[2];                    // Reserved
    union   EPWM_ETCLR_REG                   ETCLR;                        // Event Trigger Clear Register
    uint8_t                                  rsvd31[2];                    // Reserved
    union   EPWM_ETFRC_REG                   ETFRC;                        // Event Trigger Force Register
    uint8_t                                  rsvd32[2];                    // Reserved
    union   EPWM_ETINTPS_REG                 ETINTPS;                      // Event-Trigger Interrupt Pre-Scale Register
    uint8_t                                  rsvd33[2];                    // Reserved
    union   EPWM_ETSOCPS_REG                 ETSOCPS;                      // Event-Trigger SOC Pre-Scale Register
    uint8_t                                  rsvd34[2];                    // Reserved
    union   EPWM_ETCNTINITCTL_REG            ETCNTINITCTL;                 // Event-Trigger Counter Initialization Control Register
    uint8_t                                  rsvd35[2];                    // Reserved
    union   EPWM_ETCNTINIT_REG               ETCNTINIT;                    // Event-Trigger Counter Initialization Register
    uint8_t                                  rsvd36[2];                    // Reserved
    union   EPWM_ETINTMIXEN_REG              ETINTMIXEN;                   // Event-Trigger Mixed INT Selection
    uint8_t                                  rsvd37[2];                    // Reserved
    union   EPWM_ETSOCAMIXEN_REG             ETSOCAMIXEN;                  // Event-Trigger Mixed SOCA Selection
    uint8_t                                  rsvd38[2];                    // Reserved
    union   EPWM_ETSOCBMIXEN_REG             ETSOCBMIXEN;                  // Event-Trigger Mixed SOCB Selection
    uint8_t                                  rsvd39[10];                   // Reserved
    union   EPWM_DCTRIPSEL_REG               DCTRIPSEL;                    // Digital Compare Trip Select Register
    uint8_t                                  rsvd40[4];                    // Reserved
    union   EPWM_DCACTL_REG                  DCACTL;                       // Digital Compare A Control Register
    union   EPWM_DCBCTL_REG                  DCBCTL;                       // Digital Compare B Control Register
    uint8_t                                  rsvd41[4];                    // Reserved
    union   EPWM_DCFCTL_REG                  DCFCTL;                       // Digital Compare Filter Control Register
    union   EPWM_DCCAPCTL_REG                DCCAPCTL;                     // Digital Compare Capture Control Register
    uint16_t                                 DCFOFFSET;                    // Digital Compare Filter Offset Register
    uint16_t                                 DCFOFFSETCNT;                 // Digital Compare Filter Offset Counter Register
    uint16_t                                 DCFWINDOW;                    // Digital Compare Filter Window Register
    uint16_t                                 DCFWINDOWCNT;                 // Digital Compare Filter Window Counter Register
    union   EPWM_BLANKPULSEMIXSEL_REG        BLANKPULSEMIXSEL;             // Blanking window trigger pulse select register
    union   EPWM_DCCAPMIXSEL_REG             DCCAPMIXSEL;                  // Capture Event pulse select register
    uint16_t                                 DCCAP;                        // Digital Compare Counter Capture Register
    uint8_t                                  rsvd42[4];                    // Reserved
    union   EPWM_DCAHTRIPSEL_REG             DCAHTRIPSEL;                  // Digital Compare AH Trip Select
    union   EPWM_DCALTRIPSEL_REG             DCALTRIPSEL;                  // Digital Compare AL Trip Select
    union   EPWM_DCBHTRIPSEL_REG             DCBHTRIPSEL;                  // Digital Compare BH Trip Select
    union   EPWM_DCBLTRIPSEL_REG             DCBLTRIPSEL;                  // Digital Compare BL Trip Select
    union   EPWM_CAPCTL_REG                  CAPCTL;                       // Event Capture Control Register
    union   EPWM_CAPGATETRIPSEL_REG          CAPGATETRIPSEL;               // Event Capture Gate Trip input select
    union   EPWM_CAPINTRIPSEL_REG            CAPINTRIPSEL;                 // Event Capture Trip input select
    union   EPWM_CAPTRIPSEL_REG              CAPTRIPSEL;                   // Event Capture Signal Select
    uint8_t                                  rsvd43[64];                   // Reserved
    union   EPWM_EPWMLOCK_REG                EPWMLOCK;                     // EPWM Lock Register
    uint8_t                                  rsvd44[2];                    // Reserved
    uint16_t                                 HWVDELVAL;                    // Hardware Valley Mode Delay Register
    uint16_t                                 VCNTVAL;                      // Hardware Valley Counter Register
};

struct EPWM_DECTL_BITS {                // bits description
    uint16_t ENABLE:1;                  // 0 DE function enable.
    uint16_t MODE:1;                    // 1 DE Mode
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t REENTRYDLY:8;              // 15:8 Re-entry delay value
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_DECTL_REG {
    uint32_t  all;
    struct  EPWM_DECTL_BITS  bit;
};

struct EPWM_DECOMPSEL_BITS {            // bits description
    uint16_t TRIPL:6;                   // 5:0 Comparator TRIPL source select.
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t TRIPH:6;                   // 21:16 Comparator TRIPH source select.
    uint16_t rsvd2:10;                  // 31:22 Reserved
};

union EPWM_DECOMPSEL_REG {
    uint32_t  all;
    struct  EPWM_DECOMPSEL_BITS  bit;
};

struct EPWM_DEACTCTL_BITS {             // bits description
    uint16_t PWMA:2;                    // 1:0 Comparator source select.
    uint16_t TRIPSELA:1;                // 2 Trip source select on PWMA output
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t PWMB:2;                    // 5:4 Comparator source select.
    uint16_t TRIPSELB:1;                // 6 Trip source select on PWMB output
    uint16_t rsvd2:9;                   // 15:7 Reserved
    uint16_t TRIPENABLE:1;              // 16 Enables PWMTRIP condition to bypassDiode emulation logic.
    uint16_t rsvd3:15;                  // 31:17 Reserved
};

union EPWM_DEACTCTL_REG {
    uint32_t  all;
    struct  EPWM_DEACTCTL_BITS  bit;
};

struct EPWM_DESTS_BITS {                // bits description
    uint16_t DEACTIVE:1;                // 0 Diode Emulation mode active flag.
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_DESTS_REG {
    uint32_t  all;
    struct  EPWM_DESTS_BITS  bit;
};

struct EPWM_DEFRC_BITS {                // bits description
    uint16_t DEACTIVE:1;                // 0 Diode Emulation mode active flag force.
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_DEFRC_REG {
    uint32_t  all;
    struct  EPWM_DEFRC_BITS  bit;
};

struct EPWM_DECLR_BITS {                // bits description
    uint16_t DEACTIVE:1;                // 0 Diode Emulation mode active flag clear.
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_DECLR_REG {
    uint32_t  all;
    struct  EPWM_DECLR_BITS  bit;
};

struct EPWM_DEMONCNT_BITS {             // bits description
    uint16_t CNT:16;                    // 15:0 DEACTIVE monitor counter
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union EPWM_DEMONCNT_REG {
    uint32_t  all;
    struct  EPWM_DEMONCNT_BITS  bit;
};

struct EPWM_DEMONCTL_BITS {             // bits description
    uint16_t ENABLE:1;                  // 0 DEACTIVE monitor counter
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPWM_DEMONCTL_REG {
    uint32_t  all;
    struct  EPWM_DEMONCTL_BITS  bit;
};

struct EPWM_DEMONSTEP_BITS {            // bits description
    uint16_t INCSTEP:8;                 // 7:0 DE monitor counter increment step.
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t DECSTEP:8;                 // 23:16 DE monitor counter decrement step.
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union EPWM_DEMONSTEP_REG {
    uint32_t  all;
    struct  EPWM_DEMONSTEP_BITS  bit;
};

struct EPWM_DEMONTHRES_BITS {           // bits description
    uint16_t THRESHOLD:16;              // 15:0 DE monitor counter compare threshold.
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union EPWM_DEMONTHRES_REG {
    uint32_t  all;
    struct  EPWM_DEMONTHRES_BITS  bit;
};

struct DE_REGS {
    union   EPWM_DECTL_REG                   DECTL;                        // DE control register
    union   EPWM_DECOMPSEL_REG               DECOMPSEL;                    // DE comparator source select register
    union   EPWM_DEACTCTL_REG                DEACTCTL;                     // DE Action Control
    union   EPWM_DESTS_REG                   DESTS;                        // DE Status register
    union   EPWM_DEFRC_REG                   DEFRC;                        // DE Status force register
    union   EPWM_DECLR_REG                   DECLR;                        // DE Status clear register
    uint8_t                                  rsvd1[8];                     // Reserved
    union   EPWM_DEMONCNT_REG                DEMONCNT;                     // DE trip monitor counter
    union   EPWM_DEMONCTL_REG                DEMONCTL;                     // DE monitor mode control
    union   EPWM_DEMONSTEP_REG               DEMONSTEP;                    // DE monitor counter step
    union   EPWM_DEMONTHRES_REG              DEMONTHRES;                   // DE monitor counter threshold
};

struct EPWM_MINDBCFG_BITS {             // bits description
    uint16_t ENABLEA:1;                 // 0 Minimum dead band logic enable on PWMA
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t INVERTA:1;                 // 2 Invert the selected reference signal on PWMA
    uint16_t SELBLOCKA:1;               // 3 BLOCK signal source select on PWMA
    uint16_t SELA:4;                    // 7:4 Reference source select on PWMA min dead band logic.
    uint16_t POLSELA:1;                 // 8 Select signal for the AND OR logic of PWMA
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t ENABLEB:1;                 // 16 Minimum dead band logic enable on PWMB
    uint16_t rsvd3:1;                   // 17 Reserved
    uint16_t INVERTB:1;                 // 18 Invert the selected reference signal on PWMB
    uint16_t SELBLOCKB:1;               // 19 BLOCK signal source select on PWMB
    uint16_t SELB:4;                    // 23:20 Reference source select on PWMB min dead band logic.
    uint16_t POLSELB:1;                 // 24 Select signal for the AND OR logic of PWMB
    uint16_t rsvd4:7;                   // 31:25 Reserved
};

union EPWM_MINDBCFG_REG {
    uint32_t  all;
    struct  EPWM_MINDBCFG_BITS  bit;
};

struct EPWM_MINDBDLY_BITS {             // bits description
    uint16_t DELAYA:16;                 // 15:0 Minimum dead band delay on PWMA
    uint16_t DELAYB:16;                 // 31:16 Minimum dead band delay on PWMB
};

union EPWM_MINDBDLY_REG {
    uint32_t  all;
    struct  EPWM_MINDBDLY_BITS  bit;
};

struct EPWM_LUTCTLA_BITS {              // bits description
    uint16_t BYPASS:1;                  // 0 Bypass LUTA
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t SELXBAR:4;                 // 7:4 ICSS XBAR select
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t LUTDEC0:1;                 // 16 LUT output PWMA value on decoding 0
    uint16_t LUTDEC1:1;                 // 17 LUT output PWMA value on decoding 1
    uint16_t LUTDEC2:1;                 // 18 LUT output PWMA value on decoding 2
    uint16_t LUTDEC3:1;                 // 19 LUT output PWMA value on decoding 3
    uint16_t LUTDEC4:1;                 // 20 LUT output PWMA value on decoding 4
    uint16_t LUTDEC5:1;                 // 21 LUT output PWMA value on decoding 5
    uint16_t LUTDEC6:1;                 // 22 LUT output PWMA value on decoding 6
    uint16_t LUTDEC7:1;                 // 23 LUT output PWMA value on decoding 7
    uint16_t rsvd3:8;                   // 31:24 Reserved
};

union EPWM_LUTCTLA_REG {
    uint32_t  all;
    struct  EPWM_LUTCTLA_BITS  bit;
};

struct EPWM_LUTCTLB_BITS {              // bits description
    uint16_t BYPASS:1;                  // 0 Bypass LUTB
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t SELXBAR:4;                 // 7:4 ICSS XBAR select
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t LUTDEC0:1;                 // 16 LUT output PWMB value on decoding 0
    uint16_t LUTDEC1:1;                 // 17 LUT output PWMB value on decoding 1
    uint16_t LUTDEC2:1;                 // 18 LUT output PWMB value on decoding 2
    uint16_t LUTDEC3:1;                 // 19 LUT output PWMB value on decoding 3
    uint16_t LUTDEC4:1;                 // 20 LUT output PWMB value on decoding 4
    uint16_t LUTDEC5:1;                 // 21 LUT output PWMB value on decoding 5
    uint16_t LUTDEC6:1;                 // 22 LUT output PWMB value on decoding 6
    uint16_t LUTDEC7:1;                 // 23 LUT output PWMB value on decoding 7
    uint16_t rsvd3:8;                   // 31:24 Reserved
};

union EPWM_LUTCTLB_REG {
    uint32_t  all;
    struct  EPWM_LUTCTLB_BITS  bit;
};

struct MINDB_LUT_REGS {
    union   EPWM_MINDBCFG_REG                MINDBCFG;                     // Minimum dead band configuration register.
    union   EPWM_MINDBDLY_REG                MINDBDLY;                     // Minimum dead band delay register
    uint8_t                                  rsvd1[24];                    // Reserved
    union   EPWM_LUTCTLA_REG                 LUTCTLA;                      // LUT control register on PWMA
    union   EPWM_LUTCTLB_REG                 LUTCTLB;                      // LUT control register on PWMB
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
