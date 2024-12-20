//###########################################################################
//
// FILE:    hwbf_emif.h
//
// TITLE:   Definitions for the EMIF registers.
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

#ifndef HWBF_EMIF_H
#define HWBF_EMIF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// EMIF Individual Register Bit Definitions:

struct EMIF_RCSR_BITS {                 // bits description
    uint16_t MINOR_REVISION:8;          // 7:0 Minor Revision.
    uint16_t MAJOR_REVISION:8;          // 15:8 Major Revision.
    uint16_t MODULE_ID:14;              // 29:16 EMIF module ID.
    uint16_t FR:1;                      // 30 EMIF is running in full rate or half rate.
    uint16_t BE:1;                      // 31 EMIF endian mode.
};

union EMIF_RCSR_REG {
    uint32_t  all;
    struct  EMIF_RCSR_BITS  bit;
};

struct EMIF_ASYNC_WCCR_BITS {           // bits description
    uint16_t MAX_EXT_WAIT:8;            // 7:0 Maximum Extended Wait cycles.
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:2;                   // 17:16 Reserved
    uint16_t rsvd3:2;                   // 19:18 Reserved
    uint16_t rsvd4:2;                   // 21:20 Reserved
    uint16_t rsvd5:2;                   // 23:22 Reserved
    uint16_t rsvd6:4;                   // 27:24 Reserved
    uint16_t WP0:1;                     // 28  Polarity for EMxWAIT.
    uint16_t rsvd7:1;                   // 29 Reserved
    uint16_t rsvd8:1;                   // 30 Reserved
    uint16_t rsvd9:1;                   // 31 Reserved
};

union EMIF_ASYNC_WCCR_REG {
    uint32_t  all;
    struct  EMIF_ASYNC_WCCR_BITS  bit;
};

struct EMIF_SDRAM_CR_BITS {             // bits description
    uint16_t PAGESIGE:3;                // 2:0 Page Size.
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t IBANK:3;                   // 6:4 Internal Bank setup of SDRAM devices.
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t BIT_11_9_LOCK:1;           // 8 Bits 11 to 9 are writable only if this bit is set.
    uint16_t CL:3;                      // 11:9 CAS Latency.
    uint16_t rsvd3:1;                   // 12 Reserved
    uint16_t rsvd4:1;                   // 13 Reserved
    uint16_t NM:1;                      // 14 Narrow Mode.
    uint16_t rsvd5:1;                   // 15 Reserved
    uint16_t rsvd6:1;                   // 16 Reserved
    uint16_t rsvd7:2;                   // 18:17 Reserved
    uint16_t rsvd8:1;                   // 19 Reserved
    uint16_t rsvd9:3;                   // 22:20 Reserved
    uint16_t rsvd10:3;                  // 25:23 Reserved
    uint16_t rsvd11:3;                  // 28:26 Reserved
    uint16_t PDWR:1;                    // 29 Perform refreshes during Power Down.
    uint16_t PD:1;                      // 30 Power Down.
    uint16_t SR:1;                      // 31 Self Refresh.
};

union EMIF_SDRAM_CR_REG {
    uint32_t  all;
    struct  EMIF_SDRAM_CR_BITS  bit;
};

struct EMIF_SDRAM_RCR_BITS {            // bits description
    uint16_t REFRESH_RATE:13;           // 12:0 Refresh Rate.
    uint16_t rsvd1:3;                   // 15:13 Reserved
    uint16_t rsvd2:3;                   // 18:16 Reserved
    uint16_t rsvd3:13;                  // 31:19 Reserved
};

union EMIF_SDRAM_RCR_REG {
    uint32_t  all;
    struct  EMIF_SDRAM_RCR_BITS  bit;
};

struct EMIF_ASYNC_CS2_CR_BITS {         // bits description
    uint16_t ASIZE:2;                   // 1:0 Asynchronous Memory Size.
    uint16_t TA:2;                      // 3:2 Turn Around cycles.
    uint16_t R_HOLD:3;                  // 6:4 Read Strobe Hold cycles.
    uint16_t R_STROBE:6;                // 12:7 Read Strobe Duration cycles.
    uint32_t R_SETUP:4;                 // 16:13 Read Strobe Setup cycles.
    uint16_t W_HOLD:3;                  // 19:17 Write Strobe Hold cycles.
    uint16_t W_STROBE:6;                // 25:20 Write Strobe Duration cycles.
    uint16_t W_SETUP:4;                 // 29:26 Write Strobe Setup cycles.
    uint16_t EW:1;                      // 30 Extend Wait mode.
    uint16_t SS:1;                      // 31 Select Strobe mode.
};

union EMIF_ASYNC_CS2_CR_REG {
    uint32_t  all;
    struct  EMIF_ASYNC_CS2_CR_BITS  bit;
};

struct EMIF_ASYNC_CS3_CR_BITS {         // bits description
    uint16_t ASIZE:2;                   // 1:0 Asynchronous Memory Size.
    uint16_t TA:2;                      // 3:2 Turn Around cycles.
    uint16_t R_HOLD:3;                  // 6:4 Read Strobe Hold cycles.
    uint16_t R_STROBE:6;                // 12:7 Read Strobe Duration cycles.
    uint32_t R_SETUP:4;                 // 16:13 Read Strobe Setup cycles.
    uint16_t W_HOLD:3;                  // 19:17 Write Strobe Hold cycles.
    uint16_t W_STROBE:6;                // 25:20 Write Strobe Duration cycles.
    uint16_t W_SETUP:4;                 // 29:26 Write Strobe Setup cycles.
    uint16_t EW:1;                      // 30 Extend Wait mode.
    uint16_t SS:1;                      // 31 Select Strobe mode.
};

union EMIF_ASYNC_CS3_CR_REG {
    uint32_t  all;
    struct  EMIF_ASYNC_CS3_CR_BITS  bit;
};

struct EMIF_ASYNC_CS4_CR_BITS {         // bits description
    uint16_t ASIZE:2;                   // 1:0 Asynchronous Memory Size.
    uint16_t TA:2;                      // 3:2 Turn Around cycles.
    uint16_t R_HOLD:3;                  // 6:4 Read Strobe Hold cycles.
    uint16_t R_STROBE:6;                // 12:7 Read Strobe Duration cycles.
    uint32_t R_SETUP:4;                 // 16:13 Read Strobe Setup cycles.
    uint16_t W_HOLD:3;                  // 19:17 Write Strobe Hold cycles.
    uint16_t W_STROBE:6;                // 25:20 Write Strobe Duration cycles.
    uint16_t W_SETUP:4;                 // 29:26 Write Strobe Setup cycles.
    uint16_t EW:1;                      // 30 Extend Wait mode.
    uint16_t SS:1;                      // 31 Select Strobe mode.
};

union EMIF_ASYNC_CS4_CR_REG {
    uint32_t  all;
    struct  EMIF_ASYNC_CS4_CR_BITS  bit;
};

struct EMIF_SDRAM_TR_BITS {             // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t T_RRD:3;                   // 6:4 Activate to Activate timing for different bank.
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t T_RC:4;                    // 11:8 Activate to Activate timing .
    uint16_t T_RAS:4;                   // 15:12 Activate to Precharge timing.
    uint16_t T_WR:3;                    // 18:16 Last Write to Precharge timing.
    uint16_t rsvd3:1;                   // 19 Reserved
    uint16_t T_RCD:3;                   // 22:20 Activate to Read/Write timing.
    uint16_t rsvd4:1;                   // 23 Reserved
    uint16_t T_RP:3;                    // 26:24 Precharge to Activate/Refresh timing.
    uint16_t T_RFC:5;                   // 31:27 Refresh/Load Mode to Refresh/Activate timing
};

union EMIF_SDRAM_TR_REG {
    uint32_t  all;
    struct  EMIF_SDRAM_TR_BITS  bit;
};

struct EMIF_SDR_EXT_TMNG_BITS {         // bits description
    uint16_t T_XS:5;                    // 4:0 Self Refresh exit to new command timing.
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EMIF_SDR_EXT_TMNG_REG {
    uint32_t  all;
    struct  EMIF_SDR_EXT_TMNG_BITS  bit;
};

struct EMIF_INT_RAW_BITS {              // bits description
    uint16_t AT:1;                      // 0 Asynchronous Timeout.
    uint16_t LT:1;                      // 1 Line Trap.
    uint16_t WR:4;                      // 5:2 Wait Rise.
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EMIF_INT_RAW_REG {
    uint32_t  all;
    struct  EMIF_INT_RAW_BITS  bit;
};

struct EMIF_INT_MSK_BITS {              // bits description
    uint16_t AT_MASKED:1;               // 0 Asynchronous Timeout.
    uint16_t LT_MASKED:1;               // 1 Line Trap.
    uint16_t WR_MASKED:4;               // 5:2 Wait Rise.
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EMIF_INT_MSK_REG {
    uint32_t  all;
    struct  EMIF_INT_MSK_BITS  bit;
};

struct EMIF_INT_MSK_SET_BITS {          // bits description
    uint16_t AT_MASK_SET:1;             // 0 Asynchronous Timeout.
    uint16_t LT_MASK_SET:1;             // 1 Line Trap.
    uint16_t WR_MASK_SET:4;             // 5:2 Wait Rise.
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EMIF_INT_MSK_SET_REG {
    uint32_t  all;
    struct  EMIF_INT_MSK_SET_BITS  bit;
};

struct EMIF_INT_MSK_CLR_BITS {          // bits description
    uint16_t AT_MASK_CLR:1;             // 0 Asynchronous Timeout.
    uint16_t LT_MASK_CLR:1;             // 1 Line Trap.
    uint16_t WR_MASK_CLR:4;             // 5:2 Wait Rise.
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EMIF_INT_MSK_CLR_REG {
    uint32_t  all;
    struct  EMIF_INT_MSK_CLR_BITS  bit;
};

struct EMIF_REGS {
    union   EMIF_RCSR_REG                    RCSR;                         // Revision Code and Status Register
    union   EMIF_ASYNC_WCCR_REG              ASYNC_WCCR;                   // Async Wait Cycle Config Register
    union   EMIF_SDRAM_CR_REG                SDRAM_CR;                     // SDRAM (EMxCS0n) Config Register
    union   EMIF_SDRAM_RCR_REG               SDRAM_RCR;                    // SDRAM Refresh Control Register
    union   EMIF_ASYNC_CS2_CR_REG            ASYNC_CS2_CR;                 // Async 1 (EMxCS2n) Config Register
    union   EMIF_ASYNC_CS3_CR_REG            ASYNC_CS3_CR;                 // Async 2 (EMxCS3n) Config Register
    union   EMIF_ASYNC_CS4_CR_REG            ASYNC_CS4_CR;                 // Async 3 (EMxCS4n) Config Register
    uint8_t                                  rsvd1[4];                     // Reserved
    union   EMIF_SDRAM_TR_REG                SDRAM_TR;                     // SDRAM Timing Register
    uint8_t                                  rsvd2[12];                    // Reserved
    uint32_t                                 TOTAL_SDRAM_AR;               // Total SDRAM Accesses Register
    uint32_t                                 TOTAL_SDRAM_ACTR;             // Total SDRAM Activate Register
    uint8_t                                  rsvd3[4];                     // Reserved
    union   EMIF_SDR_EXT_TMNG_REG            SDR_EXT_TMNG;                 // SDRAM SR/PD Exit Timing Register
    union   EMIF_INT_RAW_REG                 INT_RAW;                      // Interrupt Raw Register
    union   EMIF_INT_MSK_REG                 INT_MSK;                      // Interrupt Masked Register
    union   EMIF_INT_MSK_SET_REG             INT_MSK_SET;                  // Interrupt Mask Set Register
    union   EMIF_INT_MSK_CLR_REG             INT_MSK_CLR;                  // Interrupt Mask Clear Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
