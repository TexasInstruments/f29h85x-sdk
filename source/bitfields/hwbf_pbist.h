//###########################################################################
//
// FILE:    hwbf_pbist.h
//
// TITLE:   Definitions for the PBIST registers.
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

#ifndef HWBF_PBIST_H
#define HWBF_PBIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// PBIST Individual Register Bit Definitions:

struct PBIST_RAMT_BITS {                // bits description
    uint16_t rsvd1:16;                  // 15:0 Reserved
    uint16_t RDS:8;                     // 23:16 Return Data Select
    uint16_t RGS:8;                     // 31:24 RAM Group Select
};

union PBIST_RAMT_REG {
    uint32_t  all;
    struct  PBIST_RAMT_BITS  bit;
};

struct PBIST_DLRT_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t ROM_TEST:1;                // 2 ROM-based testing
    uint16_t TCK_GATED:1;               // 3 TCK gated
    uint16_t CONFIG_ACC:1;              // 4 Config Access
    uint16_t rsvd3:1;                   // 5 Reserved
    uint16_t rsvd4:1;                   // 6 Reserved
    uint16_t rsvd5:1;                   // 7 Reserved
    uint16_t rsvd6:1;                   // 8 Reserved
    uint16_t GO_NOGO_TEST:1;            // 9 GO/ NO-GO Testing
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:5;                   // 15:11 Reserved
    uint16_t rsvd9:16;                  // 31:16 Reserved
};

union PBIST_DLRT_REG {
    uint32_t  all;
    struct  PBIST_DLRT_BITS  bit;
};

struct PBIST_STR_BITS {                 // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t RESUME:1;                  // 1 Resume / Emulation Read
    uint16_t STOP:1;                    // 2 Stops PBIST testing
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:2;                   // 6:5 Reserved
    uint16_t rsvd5:1;                   // 7 Reserved
    uint16_t rsvd6:1;                   // 8 Reserved
    uint16_t rsvd7:7;                   // 15:9 Reserved
    uint16_t rsvd8:16;                  // 31:16 Reserved
};

union PBIST_STR_REG {
    uint32_t  all;
    struct  PBIST_STR_BITS  bit;
};

struct PBIST_PACT_BITS {                // bits description
    uint16_t ENABLE:1;                  // 0 Enable clocks to PBIST
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PBIST_PACT_REG {
    uint32_t  all;
    struct  PBIST_PACT_BITS  bit;
};

struct PBIST_OVERRIDE_BITS {            // bits description
    uint16_t RINFO_MEM_OVER:1;          // 0 ROM Memory Information Override
    uint16_t rsvd1:2;                   // 2:1 Reserved
    uint16_t ALGO_OVER:1;               // 3 ROM Algorithm Override
    uint16_t rsvd2:12;                  // 15:4 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union PBIST_OVERRIDE_REG {
    uint32_t  all;
    struct  PBIST_OVERRIDE_BITS  bit;
};

struct PBIST_REGS {
    uint8_t                                  rsvd1[352];                   // Reserved
    union   PBIST_RAMT_REG                   RAMT;                         // RAM Configuration Register
    union   PBIST_DLRT_REG                   DLRT;                         // PBIST Data Logger Register
    uint8_t                                  rsvd2[4];                     // Reserved
    union   PBIST_STR_REG                    STR;                          // Program Control Register
    uint8_t                                  rsvd3[16];                    // Reserved
    union   PBIST_PACT_REG                   PACT;                         // PBIST Activate Register
    uint8_t                                  rsvd4[4];                     // Reserved
    union   PBIST_OVERRIDE_REG               OVERRIDE;                     // PBIST Override Register
    uint8_t                                  rsvd5[4];                     // Reserved
    uint32_t                                 FSRF0;                        // Fail Status - Port 0
    uint32_t                                 FSRF1;                        // Fail Status - Port 1
    uint32_t                                 FSRC0;                        // Fail Status Count - Port 0
    uint32_t                                 FSRC1;                        // Fail Status Count - Port 1
    uint8_t                                  rsvd6[36];                    // Reserved
    uint32_t                                 ALGO;                         // PBIST Algorithm
    uint32_t                                 RINFOL;                       // RAM Info Mask Register Lower
    uint32_t                                 RINFOU;                       // RAM Info Mask Register Higher
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
