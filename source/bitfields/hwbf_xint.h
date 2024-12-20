//###########################################################################
//
// FILE:    hwbf_xint.h
//
// TITLE:   Definitions for the XINT registers.
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

#ifndef HWBF_XINT_H
#define HWBF_XINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// XINT Individual Register Bit Definitions:

struct XINT_XINT1CR_BITS {              // bits description
    uint16_t ENABLE:1;                  // 0 XINT1 Enable
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t POLARITY:2;                // 3:2 XINT1 Polarity
    uint16_t rsvd2:12;                  // 15:4 Reserved
};

union XINT_XINT1CR_REG {
    uint16_t  all;
    struct  XINT_XINT1CR_BITS  bit;
};

struct XINT_XINT2CR_BITS {              // bits description
    uint16_t ENABLE:1;                  // 0 XINT2 Enable
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t POLARITY:2;                // 3:2 XINT2 Polarity
    uint16_t rsvd2:12;                  // 15:4 Reserved
};

union XINT_XINT2CR_REG {
    uint16_t  all;
    struct  XINT_XINT2CR_BITS  bit;
};

struct XINT_XINT3CR_BITS {              // bits description
    uint16_t ENABLE:1;                  // 0 XINT3 Enable
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t POLARITY:2;                // 3:2 XINT3 Polarity
    uint16_t rsvd2:12;                  // 15:4 Reserved
};

union XINT_XINT3CR_REG {
    uint16_t  all;
    struct  XINT_XINT3CR_BITS  bit;
};

struct XINT_XINT4CR_BITS {              // bits description
    uint16_t ENABLE:1;                  // 0 XINT4 Enable
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t POLARITY:2;                // 3:2 XINT4 Polarity
    uint16_t rsvd2:12;                  // 15:4 Reserved
};

union XINT_XINT4CR_REG {
    uint16_t  all;
    struct  XINT_XINT4CR_BITS  bit;
};

struct XINT_XINT5CR_BITS {              // bits description
    uint16_t ENABLE:1;                  // 0 XINT5 Enable
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t POLARITY:2;                // 3:2 XINT5 Polarity
    uint16_t rsvd2:12;                  // 15:4 Reserved
};

union XINT_XINT5CR_REG {
    uint16_t  all;
    struct  XINT_XINT5CR_BITS  bit;
};

struct XINT_REGS {
    union   XINT_XINT1CR_REG                 XINT1CR;                      // XINT1 configuration register
    union   XINT_XINT2CR_REG                 XINT2CR;                      // XINT2 configuration register
    union   XINT_XINT3CR_REG                 XINT3CR;                      // XINT3 configuration register
    union   XINT_XINT4CR_REG                 XINT4CR;                      // XINT4 configuration register
    union   XINT_XINT5CR_REG                 XINT5CR;                      // XINT5 configuration register
    uint8_t                                  rsvd1[6];                     // Reserved
    uint16_t                                 XINT1CTR;                     // XINT1 counter register
    uint16_t                                 XINT2CTR;                     // XINT2 counter register
    uint16_t                                 XINT3CTR;                     // XINT3 counter register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
