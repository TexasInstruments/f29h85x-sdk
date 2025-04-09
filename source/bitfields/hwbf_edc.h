//###########################################################################
//
// FILE:    hwbf_edc.h
//
// TITLE:   Definitions for the EDC registers.
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

#ifndef HWBF_EDC_H
#define HWBF_EDC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// EDC Individual Register Bit Definitions:

struct EDC_REVISION_BITS {              // bits description
    uint16_t MINOR:6;                   // 5:0 Minor revision of module
    uint16_t CUSTOM:2;                  // 7:6 Special version
    uint16_t MAJOR:3;                   // 10:8 Major revision of module
    uint16_t RTL:5;                     // 15:11 RTL version of the module
    uint16_t FUNC:12;                   // 27:16 Assigned func id
    uint16_t rsvd1:2;                   // 29:28 Reserved
    uint16_t SCHEME:2;                  // 31:30 Reserved
};

union EDC_REVISION_REG {
    uint32_t  all;
    struct  EDC_REVISION_BITS  bit;
};

struct EDC_CONTROL_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t ECCCHECK:1;                // 1 Enable ECC Checkers
    uint16_t rsvd2:1;                   // 2 Reserved
    uint16_t FORCE_SE:1;                // 3 Inject Single bit error
    uint16_t FORCE_DE:1;                // 4 Inject Double bit error
    uint16_t FORCE_N_BIT:1;             // 5 Incremental Injection
    uint16_t rsvd3:2;                   // 7:6 Reserved
    uint16_t ECC_PATTERN:4;             // 11:8 Data Pattern
    uint16_t rsvd4:4;                   // 15:12 Reserved
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union EDC_CONTROL_REG {
    uint32_t  all;
    struct  EDC_CONTROL_BITS  bit;
};

struct EDC_ERROR1_BITS {                // bits description
    uint16_t ECCGRP:16;                 // 15:0 Group of Checker to inject
    uint16_t ECCBIT1:9;                 // 24:16 ECC BIT1
    uint16_t rsvd1:7;                   // 31:25 Reserved
};

union EDC_ERROR1_REG {
    uint32_t  all;
    struct  EDC_ERROR1_BITS  bit;
};

struct EDC_ERROR2_BITS {                // bits description
    uint16_t ECCBIT2:9;                 // 8:0 ECC BIT2
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EDC_ERROR2_REG {
    uint32_t  all;
    struct  EDC_ERROR2_BITS  bit;
};

struct EDC_ERRORSTATUS1_BITS {          // bits description
    uint16_t COR_PEND:2;                // 1:0 Correctable Pending
    uint16_t UNCOR_PEND:2;              // 3:2 Uncorrectable Pending
    uint16_t INJ_COR_PEND:2;            // 5:4 Injected correctable pending interrupts
    uint16_t INJ_UNCOR_PEND:2;          // 7:6 Injected uncorrectable pending interrupts
    uint16_t COR_PEND_CLR:2;            // 9:8 Correctable pending interrupts
    uint16_t UNCOR_PEND_CLR:2;          // 11:10 Correctable pending interrupts
    uint16_t INJ_COR_PEND_CLR:2;        // 13:12 Injected correctable pending interrupts
    uint16_t INJ_UNCOR_PEND_CLR:2;      // 15:14 Injected uncorrectable pending interrupts
    uint16_t ERR_GROUP:16;              // 31:16 Specify Checker that reported Error
};

union EDC_ERRORSTATUS1_REG {
    uint32_t  all;
    struct  EDC_ERRORSTATUS1_BITS  bit;
};

struct EDC_ERRORSTATUS2_BITS {          // bits description
    uint16_t ERR_BIT:16;                // 15:0 error bit
    uint16_t ERROR_TYPE:16;             // 31:16 ERROR Type
};

union EDC_ERRORSTATUS2_REG {
    uint32_t  all;
    struct  EDC_ERRORSTATUS2_BITS  bit;
};

struct EDC_REGS {
    uint8_t                                  rsvd1[16];                    // Reserved
    union   EDC_REVISION_REG                 REVISION;                     // Revision Register
    union   EDC_CONTROL_REG                  CONTROL;                      // Control Register
    union   EDC_ERROR1_REG                   ERROR1;                       // Error 1 Register
    union   EDC_ERROR2_REG                   ERROR2;                       // Error 2 Register
    union   EDC_ERRORSTATUS1_REG             ERRORSTATUS1;                 // Error Status 1 Register
    union   EDC_ERRORSTATUS2_REG             ERRORSTATUS2;                 // Error Status 2 Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
