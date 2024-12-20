//###########################################################################
//
// FILE:    hwbf_dac.h
//
// TITLE:   Definitions for the DAC registers.
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

#ifndef HWBF_DAC_H
#define HWBF_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// DAC Individual Register Bit Definitions:

struct DAC_DACREV_BITS {                // bits description
    uint16_t REV:8;                     // 7:0 DAC Revision Register
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union DAC_DACREV_REG {
    uint16_t  all;
    struct  DAC_DACREV_BITS  bit;
};

struct DAC_DACCTL_BITS {                // bits description
    uint16_t DACREFSEL:1;               // 0 DAC Reference Select
    uint16_t MODE:1;                    // 1 DAC Mode Select
    uint16_t LOADMODE:1;                // 2 DACVALA Load Mode
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t SYNCSEL:5;                 // 8:4 DAC EPWMSYNCPER Select
    uint16_t rsvd2:7;                   // 15:9 Reserved
};

union DAC_DACCTL_REG {
    uint16_t  all;
    struct  DAC_DACCTL_BITS  bit;
};

struct DAC_DACVALA_BITS {               // bits description
    uint16_t DACVALA:12;                // 11:0 DAC Active Output Code
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union DAC_DACVALA_REG {
    uint16_t  all;
    struct  DAC_DACVALA_BITS  bit;
};

struct DAC_DACVALS_BITS {               // bits description
    uint16_t DACVALS:12;                // 11:0 DAC Shadow Output Code
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union DAC_DACVALS_REG {
    uint16_t  all;
    struct  DAC_DACVALS_BITS  bit;
};

struct DAC_DACOUTEN_BITS {              // bits description
    uint16_t DACOUTEN:1;                // 0 DAC Output Code
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union DAC_DACOUTEN_REG {
    uint16_t  all;
    struct  DAC_DACOUTEN_BITS  bit;
};

struct DAC_DACLOCK_BITS {               // bits description
    uint16_t DACCTL:1;                  // 0 DAC Control Register Lock
    uint16_t DACVAL:1;                  // 1 DAC Value Register Lock
    uint16_t DACOUTEN:1;                // 2 DAC Output Enable Register Lock
    uint16_t rsvd1:9;                   // 11:3 Reserved
    uint16_t KEY:4;                     // 15:12 DAC Register Lock Key
};

union DAC_DACLOCK_REG {
    uint16_t  all;
    struct  DAC_DACLOCK_BITS  bit;
};

struct DAC_DACTRIM_BITS {               // bits description
    uint16_t OFFSET_TRIM:8;             // 7:0 DAC Offset Trim
    uint16_t rsvd1:4;                   // 11:8 Reserved
    uint16_t rsvd2:4;                   // 15:12 Reserved
};

union DAC_DACTRIM_REG {
    uint16_t  all;
    struct  DAC_DACTRIM_BITS  bit;
};

struct DAC_REGS {
    union   DAC_DACREV_REG                   DACREV;                       // DAC Revision Register
    union   DAC_DACCTL_REG                   DACCTL;                       // DAC Control Register
    union   DAC_DACVALA_REG                  DACVALA;                      // DAC Value Register - Active
    union   DAC_DACVALS_REG                  DACVALS;                      // DAC Value Register - Shadow
    union   DAC_DACOUTEN_REG                 DACOUTEN;                     // DAC Output Enable Register
    union   DAC_DACLOCK_REG                  DACLOCK;                      // DAC Lock Register
    union   DAC_DACTRIM_REG                  DACTRIM;                      // DAC Trim Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
