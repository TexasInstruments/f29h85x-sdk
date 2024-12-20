//###########################################################################
//
// FILE:    hwbf_dlt.h
//
// TITLE:   Definitions for the DLT registers.
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

#ifndef HWBF_DLT_H
#define HWBF_DLT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// DLT Individual Register Bit Definitions:

struct DLT_TAG_FILTER_START_REF_BITS {  // bits description
    uint16_t START_REF:16;              // 15:0 Reference for TAG start comparison
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union DLT_TAG_FILTER_START_REF_REG {
    uint32_t  all;
    struct  DLT_TAG_FILTER_START_REF_BITS  bit;
};

struct DLT_TAG_FILTER_START_MASK_BITS { // bits description
    uint16_t START_MASK:16;             // 15:0 MASK for TAG start comparison
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union DLT_TAG_FILTER_START_MASK_REG {
    uint32_t  all;
    struct  DLT_TAG_FILTER_START_MASK_BITS  bit;
};

struct DLT_TAG_FILTER_END_REF_BITS {    // bits description
    uint16_t END_REF:16;                // 15:0 Reference for TAG end comparison
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union DLT_TAG_FILTER_END_REF_REG {
    uint32_t  all;
    struct  DLT_TAG_FILTER_END_REF_BITS  bit;
};

struct DLT_TAG_FILTER_END_MASK_BITS {   // bits description
    uint16_t END_MASK:16;               // 15:0 MASK for TAG end comparison
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union DLT_TAG_FILTER_END_MASK_REG {
    uint32_t  all;
    struct  DLT_TAG_FILTER_END_MASK_BITS  bit;
};

struct DLT_LINK_EN_BITS {               // bits description
    uint16_t LINK0_EN:1;                // 0 LINK permissions to write to FIFO
    uint16_t LINK1_EN:1;                // 1 LINK permissions to write to FIFO
    uint16_t LINK2_EN:1;                // 2 LINK permissions to write to FIFO
    uint16_t LINK3_EN:1;                // 3 LINK permissions to write to FIFO
    uint16_t LINK4_EN:1;                // 4 LINK permissions to write to FIFO
    uint16_t LINK5_EN:1;                // 5 LINK permissions to write to FIFO
    uint16_t LINK6_EN:1;                // 6 LINK permissions to write to FIFO
    uint16_t LINK7_EN:1;                // 7 LINK permissions to write to FIFO
    uint16_t LINK8_EN:1;                // 8 LINK permissions to write to FIFO
    uint16_t LINK9_EN:1;                // 9 LINK permissions to write to FIFO
    uint16_t LINK10_EN:1;               // 10 LINK permissions to write to FIFO
    uint16_t LINK11_EN:1;               // 11 LINK permissions to write to FIFO
    uint16_t LINK12_EN:1;               // 12 LINK permissions to write to FIFO
    uint16_t LINK13_EN:1;               // 13 LINK permissions to write to FIFO
    uint16_t LINK14_EN:1;               // 14 LINK permissions to write to FIFO
    uint16_t LINK15_EN:1;               // 15 LINK permissions to write to FIFO
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union DLT_LINK_EN_REG {
    uint32_t  all;
    struct  DLT_LINK_EN_BITS  bit;
};

struct DLT_DLT_CONTROL_BITS {           // bits description
    uint16_t DLT_EN:1;                  // 0 DLTAG Enable
    uint16_t ERAD_FILTER_EN:1;          // 1 ERAD Filter Enable
    uint16_t TAG_FILTER_EN:1;           // 2 TAG Filter Enable
    uint16_t CAP_MODE:1;                // 3 Capture mode
    uint16_t FILTER_RST:1;              // 4 Filter Reset
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t KEY:16;                    // 31:16 key to enable write to lower [15:0] bit fileds
};

union DLT_DLT_CONTROL_REG {
    uint32_t  all;
    struct  DLT_DLT_CONTROL_BITS  bit;
};

struct DLT_FIFO_CONTROL_BITS {          // bits description
    uint16_t DMA_EN:1;                  // 0 Trigger DMA on FIFO level
    uint16_t FIFO_RST:1;                // 1 Initialize pointers of FIFO to 0
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint32_t WR_CTR_TRIG_LEVEL:10;      // 17:8 Level of FIFO writes required to trigger INT/DMA
    uint16_t rsvd2:14;                  // 31:18 Reserved
};

union DLT_FIFO_CONTROL_REG {
    uint32_t  all;
    struct  DLT_FIFO_CONTROL_BITS  bit;
};

struct DLT_TIMER_CONTROL_BITS {         // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t TIMER2_RST:1;              // 1 Timer 2 is reset
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union DLT_TIMER_CONTROL_REG {
    uint32_t  all;
    struct  DLT_TIMER_CONTROL_BITS  bit;
};

struct DLT_FIFO_STS_BITS {              // bits description
    uint16_t WORD_CTR:10;               // 9:0 Number of 64-bit words to be read in the FIFO
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t WR_CTR:10;                 // 25:16 Write counter of FIFO after last trigger
    uint16_t rsvd2:6;                   // 31:26 Reserved
};

union DLT_FIFO_STS_REG {
    uint32_t  all;
    struct  DLT_FIFO_STS_BITS  bit;
};

struct DLT_FIFO_PTR_BITS {              // bits description
    uint16_t RD_PTR:10;                 // 9:0 Read pointer location of FIFO
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t WR_PTR:10;                 // 25:16 Write pointer location of FIFO
    uint16_t rsvd2:6;                   // 31:26 Reserved
};

union DLT_FIFO_PTR_REG {
    uint32_t  all;
    struct  DLT_FIFO_PTR_BITS  bit;
};

struct DLT_TIMER2_COUNT_BITS {          // bits description
    uint32_t COUNT:29;                  // 28:0 Current value of TIMER2
    uint16_t rsvd1:3;                   // 31:29 Reserved
};

union DLT_TIMER2_COUNT_REG {
    uint32_t  all;
    struct  DLT_TIMER2_COUNT_BITS  bit;
};

struct DLT_INT_FLG_BITS {               // bits description
    uint16_t INT:1;                     // 0 Global Interrupt Status
    uint16_t TIMER1_OVF:1;              // 1 TIMER1 overflow status
    uint16_t TIMER2_OVF:1;              // 2 TIMER2 overflow status
    uint16_t FIFO_OVF:1;                // 3 FIFO overflow status
    uint16_t FIFO_UF:1;                 // 4 FIFO underflow status
    uint16_t FIFO_TRIG:1;               // 5 FIFO reached Trigger level status
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DLT_INT_FLG_REG {
    uint32_t  all;
    struct  DLT_INT_FLG_BITS  bit;
};

struct DLT_INT_EN_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t TIMER1_OVF:1;              // 1 TIMER1 overflow enable
    uint16_t TIMER2_OVF:1;              // 2 TIMER2 overflow enable
    uint16_t FIFO_OVF:1;                // 3 FIFO overflow enable
    uint16_t FIFO_UF:1;                 // 4 FIFO underflow enable
    uint16_t FIFO_TRIG:1;               // 5 FIFO reached Trigger level enable
    uint16_t rsvd2:10;                  // 15:6 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union DLT_INT_EN_REG {
    uint32_t  all;
    struct  DLT_INT_EN_BITS  bit;
};

struct DLT_INT_FRC_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t TIMER1_OVF:1;              // 1 TIMER1 overflow force
    uint16_t TIMER2_OVF:1;              // 2 TIMER2 overflow force
    uint16_t FIFO_OVF:1;                // 3 FIFO overflow force
    uint16_t FIFO_UF:1;                 // 4 FIFO underflow force
    uint16_t FIFO_TRIG:1;               // 5 FIFO reached Trigger level force
    uint16_t rsvd2:10;                  // 15:6 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union DLT_INT_FRC_REG {
    uint32_t  all;
    struct  DLT_INT_FRC_BITS  bit;
};

struct DLT_INT_CLR_BITS {               // bits description
    uint16_t INT:1;                     // 0 Global Interrupt clear
    uint16_t TIMER1_OVF:1;              // 1 TIMER1 overflow clear
    uint16_t TIMER2_OVF:1;              // 2 TIMER2 overflow clear
    uint16_t FIFO_OVF:1;                // 3 FIFO overflow clear
    uint16_t FIFO_UF:1;                 // 4 FIFO underflow clear
    uint16_t FIFO_TRIG:1;               // 5 FIFO reached Trigger level clear
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DLT_INT_CLR_REG {
    uint32_t  all;
    struct  DLT_INT_CLR_BITS  bit;
};

struct DLT_CORE_REGS {
    uint32_t                                 ERAD_START_MASK_L;            // ERAD Start Mask for Lower 32 lines
    uint32_t                                 ERAD_START_MASK_H;            // ERAD Start Mask for Higher 32 lines
    uint32_t                                 ERAD_END_MASK_L;              // ERAD End Mask for Lower 32 lines
    uint32_t                                 ERAD_END_MASK_H;              // ERAD End Mask for Higher 32 lines
    union   DLT_TAG_FILTER_START_REF_REG     TAG_FILTER_START_REF;         // Tag Filer Start Reference
    union   DLT_TAG_FILTER_START_MASK_REG    TAG_FILTER_START_MASK;        // Tag Filer Start Mask
    union   DLT_TAG_FILTER_END_REF_REG       TAG_FILTER_END_REF;           // Tag Filer End Reference
    union   DLT_TAG_FILTER_END_MASK_REG      TAG_FILTER_END_MASK;          // Tag Filer End Mask
    union   DLT_LINK_EN_REG                  LINK_EN;                      // Link Enable
    union   DLT_DLT_CONTROL_REG              DLT_CONTROL;                  // DLT Control Register
    union   DLT_FIFO_CONTROL_REG             FIFO_CONTROL;                 // FIFO Control Register
    union   DLT_TIMER_CONTROL_REG            TIMER_CONTROL;                // Timer Control Register
    union   DLT_FIFO_STS_REG                 FIFO_STS;                     // Number of entries in FIFO
    union   DLT_FIFO_PTR_REG                 FIFO_PTR;                     // Pointer locations in FIFO
    union   DLT_TIMER2_COUNT_REG             TIMER2_COUNT;                 // Timer2 Status
    union   DLT_INT_FLG_REG                  INT_FLG;                      // Interrupt Flag
    union   DLT_INT_EN_REG                   INT_EN;                       // Interrupt Enable
    union   DLT_INT_FRC_REG                  INT_FRC;                      // Interrupt Force
    union   DLT_INT_CLR_REG                  INT_CLR;                      // Interrupt Clear
};

struct DLT_FIFO_REGS {
    uint32_t                                 FIFO_BUF_L;                   // FIFO Content Register
    uint32_t                                 FIFO_BUF_H;                   // FIFO Content Register
    uint8_t                                  rsvd1[4088];                  // Reserved
    uint32_t                                 FIFO_MEM[512];                // FIFO access in Memory mode
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
