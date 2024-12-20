//###########################################################################
//
// FILE:    hwbf_erad.h
//
// TITLE:   Definitions for the ERAD registers.
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

#ifndef HWBF_ERAD_H
#define HWBF_ERAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// ERAD Individual Register Bit Definitions:

struct ERAD_EBC_OWNER_BITS {            // bits description
    uint16_t OWNER:2;                   // 1:0 Ownership ID
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t ZONE:4;                    // 11:8 Zone ID
    uint16_t SROOT:1;                   // 12 SROOT LINK ownership
    uint16_t rsvd2:3;                   // 15:13 Reserved
    uint16_t SEM:1;                     // 16 Semaphore
    uint16_t CONFIG:2;                  // 18:17 Configuration
    uint16_t rsvd3:13;                  // 31:19 Reserved
};

union ERAD_EBC_OWNER_REG {
    uint32_t  all;
    struct  ERAD_EBC_OWNER_BITS  bit;
};

struct ERAD_EBC_CNTL_BITS {             // bits description
    uint16_t EN:1;                      // 0 Enable
    uint16_t BUS_SEL:5;                 // 5:1 Bus select bits
    uint16_t HALT:1;                    // 6 CPU Halt
    uint16_t INTERRUPT:1;               // 7 Interrupt enable
    uint16_t NMI_EN:1;                  // 8 NMI enable
    uint16_t COMP_MODE:3;               // 11:9 Compare mode
    uint16_t STACK_QUAL:1;              // 12 Stack access qualifier
    uint16_t SPSEL_MATCH_EN:1;          // 13 SPSEL match enable
    uint32_t SPSEL:4;                   // 17:14 SPSEL
    uint16_t rsvd1:14;                  // 31:18 Reserved
};

union ERAD_EBC_CNTL_REG {
    uint32_t  all;
    struct  ERAD_EBC_CNTL_BITS  bit;
};

struct ERAD_EBC_STATUS_BITS {           // bits description
    uint16_t EVENT_FIRED:1;             // 0 EBC Event Fired bits
    uint16_t rsvd1:7;                   // 7:1 Reserved
    uint16_t STATUS:2;                  // 9:8 Status bits
    uint16_t rsvd2:6;                   // 15:10 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ERAD_EBC_STATUS_REG {
    uint32_t  all;
    struct  ERAD_EBC_STATUS_BITS  bit;
};

struct ERAD_EBC_STATUSCLEAR_BITS {      // bits description
    uint16_t EVENT_FIRED:1;             // 0 Event Clear register
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ERAD_EBC_STATUSCLEAR_REG {
    uint32_t  all;
    struct  ERAD_EBC_STATUSCLEAR_BITS  bit;
};

struct ERAD_EBC_REGS {
    union   ERAD_EBC_OWNER_REG               EBC_OWNER;                    // EBC Owner Register
    union   ERAD_EBC_CNTL_REG                EBC_CNTL;                     // EBC Control Register
    union   ERAD_EBC_STATUS_REG              EBC_STATUS;                   // EBC Status Register
    union   ERAD_EBC_STATUSCLEAR_REG         EBC_STATUSCLEAR;              // EBC Clear Register
    uint32_t                                 EBC_REFL;                     // EBC Reference Low Register
    uint32_t                                 EBC_REFH;                     // EBC Reference High Register
    uint32_t                                 EBC_MASKL;                    // EBC Mask Low Register
    uint32_t                                 EBC_MASKH;                    // EBC Mask High Register
    uint32_t                                 EBC_WP_PC;                    // EBC Watchpoint PC Register
    uint8_t                                  rsvd1[28];                    // Reserved
};

struct ERAD_SEC_OWNER_BITS {            // bits description
    uint16_t OWNER:2;                   // 1:0 Ownership ID
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t ZONE:4;                    // 11:8 Zone ID
    uint16_t SROOT:1;                   // 12 SROOT LINK ownership
    uint16_t rsvd2:3;                   // 15:13 Reserved
    uint16_t SEM:1;                     // 16 Semaphore
    uint16_t CONFIG:2;                  // 18:17 Configuration
    uint16_t rsvd3:13;                  // 31:19 Reserved
};

union ERAD_SEC_OWNER_REG {
    uint32_t  all;
    struct  ERAD_SEC_OWNER_BITS  bit;
};

struct ERAD_SEC_CNTL_BITS {             // bits description
    uint16_t EN:1;                      // 0 Enable
    uint16_t EDGE_LEVEL:1;              // 1 Event mode bit
    uint16_t START_STOP_MODE:1;         // 2 Start_stop mode bit
    uint16_t START_STOP_CUMULATIVE:1;   // 3 Start stop cumulative bit
    uint16_t RST_ON_MATCH:1;            // 4 Reset_on_match bit
    uint16_t HALT:1;                    // 5 CPU Halt
    uint16_t INTERRUPT:1;               // 6 Interrupt enable
    uint16_t NMI_EN:1;                  // 7 NMI enable
    uint16_t CNT_INP_SEL_EN:1;          // 8 Counter input select enable
    uint16_t RST_INP_SEL_EN:1;          // 9 Counter reset input select enable
    uint16_t FREE_RUN:1;                // 10 counter behaviour on CPU Halt
    uint16_t rsvd1:5;                   // 15:11 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ERAD_SEC_CNTL_REG {
    uint32_t  all;
    struct  ERAD_SEC_CNTL_BITS  bit;
};

struct ERAD_SEC_STATUS_BITS {           // bits description
    uint16_t EVENT_FIRED:1;             // 0 Counter Event Fired bits
    uint16_t OVERFLOW:1;                // 1 Counter Overflowed
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t STATUS:2;                  // 9:8 Status bits
    uint16_t rsvd2:6;                   // 15:10 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ERAD_SEC_STATUS_REG {
    uint32_t  all;
    struct  ERAD_SEC_STATUS_BITS  bit;
};

struct ERAD_SEC_STATUSCLEAR_BITS {      // bits description
    uint16_t EVENT_FIRED:1;             // 0 Clear EVENT_FIRED
    uint16_t OVERFLOW:1;                // 1 Clear OVERFLOW
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ERAD_SEC_STATUSCLEAR_REG {
    uint32_t  all;
    struct  ERAD_SEC_STATUSCLEAR_BITS  bit;
};

struct ERAD_SEC_INPUT_SEL1_BITS {       // bits description
    uint16_t CNT_INP_SEL:8;             // 7:0 Counter Input Select
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t RST_INP_SEL:8;             // 23:16 Counter Reset input Select
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union ERAD_SEC_INPUT_SEL1_REG {
    uint32_t  all;
    struct  ERAD_SEC_INPUT_SEL1_BITS  bit;
};

struct ERAD_SEC_INPUT_SEL2_BITS {       // bits description
    uint16_t STA_INP_SEL:8;             // 7:0 Counter Sart Input Select
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t STO_INP_SEL:8;             // 23:16 Counter Stop Input Select
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union ERAD_SEC_INPUT_SEL2_REG {
    uint32_t  all;
    struct  ERAD_SEC_INPUT_SEL2_BITS  bit;
};

struct ERAD_SEC_INPUT_COND_BITS {       // bits description
    uint16_t SEC_INP_INV:1;             // 0 Counter Input Invert
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:2;                   // 3:2 Reserved
    uint16_t STA_INP_INV:1;             // 4 Start input Invert
    uint16_t rsvd3:1;                   // 5 Reserved
    uint16_t rsvd4:2;                   // 7:6 Reserved
    uint16_t STO_INP_INV:1;             // 8 Stop input Invert
    uint16_t rsvd5:1;                   // 9 Reserved
    uint16_t rsvd6:2;                   // 11:10 Reserved
    uint16_t RST_INP_INV:1;             // 12 Reset input Invert
    uint16_t rsvd7:1;                   // 13 Reserved
    uint16_t rsvd8:2;                   // 15:14 Reserved
    uint16_t rsvd9:16;                  // 31:16 Reserved
};

union ERAD_SEC_INPUT_COND_REG {
    uint32_t  all;
    struct  ERAD_SEC_INPUT_COND_BITS  bit;
};

struct ERAD_SEC_REGS {
    union   ERAD_SEC_OWNER_REG               SEC_OWNER;                    // SEC Owner Register
    union   ERAD_SEC_CNTL_REG                SEC_CNTL;                     // SEC Control Register
    union   ERAD_SEC_STATUS_REG              SEC_STATUS;                   // SEC Status Register
    union   ERAD_SEC_STATUSCLEAR_REG         SEC_STATUSCLEAR;              // SEC Clear Register
    uint32_t                                 SEC_REF;                      // SEC Reference Register
    union   ERAD_SEC_INPUT_SEL1_REG          SEC_INPUT_SEL1;               // SEC Input Select Register1
    union   ERAD_SEC_INPUT_SEL2_REG          SEC_INPUT_SEL2;               // SEC Input Select Register2
    union   ERAD_SEC_INPUT_COND_REG          SEC_INPUT_COND;               // SEC Input Conditioning Register
    uint32_t                                 SEC_COUNT;                    // SEC Counter Register
    uint32_t                                 SEC_MAX_COUNT;                // SEC Max Count Register
    uint32_t                                 SEC_MIN_COUNT;                // SEC Min Count Register
    uint8_t                                  rsvd1[20];                    // Reserved
};

struct ERAD_AND_MASK_OWNER_BITS {       // bits description
    uint16_t OWNER:2;                   // 1:0 Ownership ID
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t ZONE:4;                    // 11:8 Zone ID
    uint16_t SROOT:1;                   // 12 SROOT LINK ownership
    uint16_t rsvd2:3;                   // 15:13 Reserved
    uint16_t SEM:1;                     // 16 Semaphore
    uint16_t rsvd3:15;                  // 31:17 Reserved
};

union ERAD_AND_MASK_OWNER_REG {
    uint32_t  all;
    struct  ERAD_AND_MASK_OWNER_BITS  bit;
};

struct ERAD_AND_MASK_CTL_BITS {         // bits description
    uint16_t HALT:1;                    // 0 CPU Halt
    uint16_t INTERRUPT:1;               // 1 Interrupt enable
    uint16_t NMI_EN:1;                  // 2 NMI enable
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ERAD_AND_MASK_CTL_REG {
    uint32_t  all;
    struct  ERAD_AND_MASK_CTL_BITS  bit;
};

struct ERAD_EVENT_AND_MASK_BITS {       // bits description
    uint32_t MASK_EBC:24;               // 23:0 EBC, SEC AND Event Mask
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ERAD_EVENT_AND_MASK_REG {
    uint32_t  all;
    struct  ERAD_EVENT_AND_MASK_BITS  bit;
};

struct ERAD_AND_REGS {
    union   ERAD_AND_MASK_OWNER_REG          AND_MASK_OWNER;               // AND Owner Register
    union   ERAD_AND_MASK_CTL_REG            AND_MASK_CTL;                 // AND Control Register
    union   ERAD_EVENT_AND_MASK_REG          EVENT_AND_MASK;               // AND Event Selection Register
    uint8_t                                  rsvd1[20];                    // Reserved
};

struct ERAD_OR_MASK_OWNER_BITS {        // bits description
    uint16_t OWNER:2;                   // 1:0 Ownership ID
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t ZONE:4;                    // 11:8 Zone ID
    uint16_t SROOT:1;                   // 12 SROOT LINK ownership
    uint16_t rsvd2:3;                   // 15:13 Reserved
    uint16_t SEM:1;                     // 16 Semaphore
    uint16_t rsvd3:15;                  // 31:17 Reserved
};

union ERAD_OR_MASK_OWNER_REG {
    uint32_t  all;
    struct  ERAD_OR_MASK_OWNER_BITS  bit;
};

struct ERAD_OR_MASK_CTL_BITS {          // bits description
    uint16_t HALT:1;                    // 0 CPU Halt
    uint16_t INTERRUPT:1;               // 1 Interrupt enable
    uint16_t NMI_EN:1;                  // 2 NMI enable
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ERAD_OR_MASK_CTL_REG {
    uint32_t  all;
    struct  ERAD_OR_MASK_CTL_BITS  bit;
};

struct ERAD_EVENT_OR_MASK_BITS {        // bits description
    uint32_t MASK_EBC:24;               // 23:0 EBC, SEC OR Event Mask
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ERAD_EVENT_OR_MASK_REG {
    uint32_t  all;
    struct  ERAD_EVENT_OR_MASK_BITS  bit;
};

struct ERAD_OR_REGS {
    union   ERAD_OR_MASK_OWNER_REG           OR_MASK_OWNER;                // OR Owner Register
    union   ERAD_OR_MASK_CTL_REG             OR_MASK_CTL;                  // OR Control Register
    union   ERAD_EVENT_OR_MASK_REG           EVENT_OR_MASK;                // OR Event Selection Register
    uint8_t                                  rsvd1[20];                    // Reserved
};

struct ERAD_GLBL_ERAD_ID_BITS {         // bits description
    uint16_t MINOR:6;                   // 5:0 Minor
    uint16_t CUSTOM:2;                  // 7:6 Custom
    uint16_t MAJOR:3;                   // 10:8 Major
    uint16_t rsvd1:5;                   // 15:11 Reserved
    uint16_t FUNC:12;                   // 27:16 Func
    uint16_t rsvd2:2;                   // 29:28 Reserved
    uint16_t rsvd3:2;                   // 31:30 Reserved
};

union ERAD_GLBL_ERAD_ID_REG {
    uint32_t  all;
    struct  ERAD_GLBL_ERAD_ID_BITS  bit;
};

struct ERAD_GLBL_EVENT_STAT_BITS {      // bits description
    uint16_t EBC:16;                    // 15:0 EBC Module Event Status
    uint16_t SEC:16;                    // 31:16 SEC Module Event Status
};

union ERAD_GLBL_EVENT_STAT_REG {
    uint32_t  all;
    struct  ERAD_GLBL_EVENT_STAT_BITS  bit;
};

struct ERAD_PCTRACE_OWNER_BITS {        // bits description
    uint16_t OWNER:2;                   // 1:0 Ownership ID
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t ZONE:4;                    // 11:8 Zone ID
    uint16_t SROOT:1;                   // 12 SROOT LINK ownership
    uint16_t rsvd2:3;                   // 15:13 Reserved
    uint16_t SEM:1;                     // 16 Semaphore
    uint16_t rsvd3:15;                  // 31:17 Reserved
};

union ERAD_PCTRACE_OWNER_REG {
    uint32_t  all;
    struct  ERAD_PCTRACE_OWNER_BITS  bit;
};

struct ERAD_PCTRACE_GLOBAL_BITS {       // bits description
    uint16_t EN:1;                      // 0 Enable PC  trace
    uint16_t rsvd1:7;                   // 7:1 Reserved
    uint16_t INIT:1;                    // 8 Initialize the PC Trace and buffer pointer
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t BUFFER_SIZE:2;             // 17:16 Trace buffer size
    uint16_t rsvd3:14;                  // 31:18 Reserved
};

union ERAD_PCTRACE_GLOBAL_REG {
    uint32_t  all;
    struct  ERAD_PCTRACE_GLOBAL_BITS  bit;
};

struct ERAD_PCTRACE_BUFFER_BITS {       // bits description
    uint16_t PTR:16;                    // 15:0 Trace Buffer Pointer
    uint16_t BUFFER_FULL:1;             // 16 Trace Buffer Full
    uint16_t rsvd1:15;                  // 31:17 Reserved
};

union ERAD_PCTRACE_BUFFER_REG {
    uint32_t  all;
    struct  ERAD_PCTRACE_BUFFER_BITS  bit;
};

struct ERAD_PCTRACE_QUAL1_BITS {        // bits description
    uint16_t WINDOWED_INP_SEL:8;        // 7:0 Windowed trace qualifier
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t TRACE_MODE:2;              // 17:16 Trace qualifier mode
    uint16_t WINDOWED_INP_INV:1;        // 18 Windowed trace Input Invert
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t START_INP_INV:1;           // 20 Start input Invert
    uint16_t rsvd3:1;                   // 21 Reserved
    uint16_t STOP_INP_INV:1;            // 22 Stop input Invert
    uint16_t rsvd4:1;                   // 23 Reserved
    uint16_t rsvd5:8;                   // 31:24 Reserved
};

union ERAD_PCTRACE_QUAL1_REG {
    uint32_t  all;
    struct  ERAD_PCTRACE_QUAL1_BITS  bit;
};

struct ERAD_PCTRACE_QUAL2_BITS {        // bits description
    uint16_t START_INP_SEL:8;           // 7:0 Trace Start event select
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t STOP_INP_SEL:8;            // 23:16 Trace Stop event select
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union ERAD_PCTRACE_QUAL2_REG {
    uint32_t  all;
    struct  ERAD_PCTRACE_QUAL2_BITS  bit;
};

struct ERAD_PCTRACE_BUFFER_BASE_BITS {  // bits description
    uint16_t BLOCKED:1;                 // 0 Access blocked due to security
    uint32_t PROGRAM_COUNTER:31;        // 31:1 Program Counter
};

union ERAD_PCTRACE_BUFFER_BASE_REG {
    uint32_t  all;
    struct  ERAD_PCTRACE_BUFFER_BASE_BITS  bit;
};

struct ERAD_REGS {
    union   ERAD_GLBL_ERAD_ID_REG            GLBL_ERAD_ID;                 // Debug Peripheral ID
    union   ERAD_GLBL_EVENT_STAT_REG         GLBL_EVENT_STAT;              // Global Event Status Register
    uint8_t                                  rsvd1[56];                    // Reserved
    struct ERAD_EBC_REGS                     ERAD_EBC[8];                  // 
    uint8_t                                  rsvd2[512];                   // Reserved
    struct ERAD_SEC_REGS                     ERAD_SEC[4];                  // 
    uint8_t                                  rsvd3[256];                   // Reserved
    struct ERAD_AND_REGS                     ERAD_AND[4];                  // 
    uint8_t                                  rsvd4[128];                   // Reserved
    struct ERAD_OR_REGS                      ERAD_OR[4];                   // 
    uint8_t                                  rsvd5[128];                   // Reserved
    union   ERAD_PCTRACE_OWNER_REG           PCTRACE_OWNER;                // Owner Register
    union   ERAD_PCTRACE_GLOBAL_REG          PCTRACE_GLOBAL;               // Global Control Register
    union   ERAD_PCTRACE_BUFFER_REG          PCTRACE_BUFFER;               // Trace Buffer pointer register
    union   ERAD_PCTRACE_QUAL1_REG           PCTRACE_QUAL1;                // Trace Qualifier register 1
    union   ERAD_PCTRACE_QUAL2_REG           PCTRACE_QUAL2;                // Trace Qualifier register 2
    uint32_t                                 PCTRACE_LOGPC_SOFTENABLE;     // PC when PC Trace was last enabled by software
    uint32_t                                 PCTRACE_LOGPC_SOFTDISABLE;    // PC when PC Trace was last disabled by software
    uint8_t                                  rsvd6[1956];                  // Reserved
    union   ERAD_PCTRACE_BUFFER_BASE_REG     PCTRACE_BUFFER_BASE[256];     // Trace Buffer Base address
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
