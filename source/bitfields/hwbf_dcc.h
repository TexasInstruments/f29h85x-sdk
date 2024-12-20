//###########################################################################
//
// FILE:    hwbf_dcc.h
//
// TITLE:   Definitions for the DCC registers.
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

#ifndef HWBF_DCC_H
#define HWBF_DCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// DCC Individual Register Bit Definitions:

struct DCC_DCCGCTRL_BITS {              // bits description
    uint16_t DCCENA:4;                  // 3:0 DCC Enable
    uint16_t ERRENA:4;                  // 7:4 Error Enable
    uint16_t SINGLESHOT:4;              // 11:8 Single-Shot Enable
    uint16_t DONEENA:4;                 // 15:12 DONE Enable
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union DCC_DCCGCTRL_REG {
    uint32_t  all;
    struct  DCC_DCCGCTRL_BITS  bit;
};

struct DCC_DCCCNTSEED0_BITS {           // bits description
    uint32_t COUNTSEED0:20;             // 19:0 Seed Value for Counter 0
    uint16_t rsvd1:12;                  // 31:20 Reserved
};

union DCC_DCCCNTSEED0_REG {
    uint32_t  all;
    struct  DCC_DCCCNTSEED0_BITS  bit;
};

struct DCC_DCCVALIDSEED0_BITS {         // bits description
    uint16_t VALIDSEED:16;              // 15:0 Seed Value for Valid Duration Counter 0
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union DCC_DCCVALIDSEED0_REG {
    uint32_t  all;
    struct  DCC_DCCVALIDSEED0_BITS  bit;
};

struct DCC_DCCCNTSEED1_BITS {           // bits description
    uint32_t COUNTSEED1:20;             // 19:0 Seed Value for Counter 1
    uint16_t rsvd1:12;                  // 31:20 Reserved
};

union DCC_DCCCNTSEED1_REG {
    uint32_t  all;
    struct  DCC_DCCCNTSEED1_BITS  bit;
};

struct DCC_DCCSTATUS_BITS {             // bits description
    uint16_t ERR:1;                     // 0 Error Flag
    uint16_t DONE:1;                    // 1 Single-Shot Done Flag
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DCC_DCCSTATUS_REG {
    uint32_t  all;
    struct  DCC_DCCSTATUS_BITS  bit;
};

struct DCC_DCCCNT0_BITS {               // bits description
    uint32_t COUNT0:20;                 // 19:0 Current Value of Counter 0
    uint16_t rsvd1:12;                  // 31:20 Reserved
};

union DCC_DCCCNT0_REG {
    uint32_t  all;
    struct  DCC_DCCCNT0_BITS  bit;
};

struct DCC_DCCVALID0_BITS {             // bits description
    uint16_t VALID0:16;                 // 15:0 Current Value of Valid 0
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union DCC_DCCVALID0_REG {
    uint32_t  all;
    struct  DCC_DCCVALID0_BITS  bit;
};

struct DCC_DCCCNT1_BITS {               // bits description
    uint32_t COUNT1:20;                 // 19:0 Current Value of Counter 1
    uint16_t rsvd1:12;                  // 31:20 Reserved
};

union DCC_DCCCNT1_REG {
    uint32_t  all;
    struct  DCC_DCCCNT1_BITS  bit;
};

struct DCC_DCCCLKSRC1_BITS {            // bits description
    uint16_t CLKSRC1:6;                 // 5:0 Clock Source Select for Counter 1
    uint16_t rsvd1:6;                   // 11:6 Reserved
    uint16_t KEY:4;                     // 15:12 Enables or Disables Clock Source Selection for COUNT1
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DCC_DCCCLKSRC1_REG {
    uint32_t  all;
    struct  DCC_DCCCLKSRC1_BITS  bit;
};

struct DCC_DCCCLKSRC0_BITS {            // bits description
    uint16_t CLKSRC0:5;                 // 4:0 Clock Source Select for Counter 0
    uint16_t rsvd1:7;                   // 11:5 Reserved
    uint16_t KEY:4;                     // 15:12 Enables or Disables Clock Source Selection for COUNT0
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DCC_DCCCLKSRC0_REG {
    uint32_t  all;
    struct  DCC_DCCCLKSRC0_BITS  bit;
};

struct DCC_REGS {
    union   DCC_DCCGCTRL_REG                 DCCGCTRL;                     // Starts / stops the counters. Clears the error signal.
    uint8_t                                  rsvd1[4];                     // Reserved
    union   DCC_DCCCNTSEED0_REG              DCCCNTSEED0;                  // Seed value for the counter attached to Clock Source 0.
    union   DCC_DCCVALIDSEED0_REG            DCCVALIDSEED0;                // Seed value for the timeout counter attached to Clock Source 0.
    union   DCC_DCCCNTSEED1_REG              DCCCNTSEED1;                  // Seed value for the counter attached to Clock Source 1.
    union   DCC_DCCSTATUS_REG                DCCSTATUS;                    // Specifies the status of the DCC Module.
    union   DCC_DCCCNT0_REG                  DCCCNT0;                      // Value of the counter attached to Clock Source 0.
    union   DCC_DCCVALID0_REG                DCCVALID0;                    // Value of the valid counter attached to Clock Source 0.
    union   DCC_DCCCNT1_REG                  DCCCNT1;                      // Value of the counter attached to Clock Source 1.
    union   DCC_DCCCLKSRC1_REG               DCCCLKSRC1;                   // Selects the clock source for Counter 1.
    union   DCC_DCCCLKSRC0_REG               DCCCLKSRC0;                   // Selects the clock source for Counter 0.
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
