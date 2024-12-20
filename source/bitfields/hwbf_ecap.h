//###########################################################################
//
// FILE:    hwbf_ecap.h
//
// TITLE:   Definitions for the ECAP registers.
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

#ifndef HWBF_ECAP_H
#define HWBF_ECAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// ECAP Individual Register Bit Definitions:

struct ECAP_ECCTL0_BITS {               // bits description
    uint16_t INPUTSEL:8;                // 7:0 INPUT source select
    uint16_t rsvd1:4;                   // 11:8 Reserved
    uint16_t QUALPRD:4;                 // 15:12 Reserved
    uint16_t SOCEVTSEL:2;               // 17:16 Reserved
    uint16_t rsvd2:14;                  // 31:18 Reserved
};

union ECAP_ECCTL0_REG {
    uint32_t  all;
    struct  ECAP_ECCTL0_BITS  bit;
};

struct ECAP_ECCTL1_BITS {               // bits description
    uint16_t CAP1POL:1;                 // 0 Capture Event 1 Polarity select
    uint16_t CTRRST1:1;                 // 1 Counter Reset on Capture Event 1
    uint16_t CAP2POL:1;                 // 2 Capture Event 2 Polarity select
    uint16_t CTRRST2:1;                 // 3 Counter Reset on Capture Event 2
    uint16_t CAP3POL:1;                 // 4 Capture Event 3 Polarity select
    uint16_t CTRRST3:1;                 // 5 Counter Reset on Capture Event 3
    uint16_t CAP4POL:1;                 // 6 Capture Event 4 Polarity select
    uint16_t CTRRST4:1;                 // 7 Counter Reset on Capture Event 4
    uint16_t CAPLDEN:1;                 // 8 Enable Loading CAP1-4 regs on a Cap Event
    uint16_t PRESCALE:5;                // 13:9 Event Filter prescale select
    uint16_t FREE_SOFT:2;               // 15:14 Emulation mode
};

union ECAP_ECCTL1_REG {
    uint16_t  all;
    struct  ECAP_ECCTL1_BITS  bit;
};

struct ECAP_ECCTL2_BITS {               // bits description
    uint16_t CONT_ONESHT:1;             // 0 Continuous or one-shot
    uint16_t STOP_WRAP:2;               // 2:1 Stop value for one-shot, Wrap for continuous
    uint16_t REARM:1;                   // 3 One-shot re-arm
    uint16_t TSCTRSTOP:1;               // 4 TSCNT counter stop
    uint16_t SYNCI_EN:1;                // 5 Counter sync-in select
    uint16_t SYNCO_SEL:2;               // 7:6 Sync-out mode
    uint16_t SWSYNC:1;                  // 8 SW forced counter sync
    uint16_t CAP_APWM:1;                // 9 CAP/APWM operating mode select
    uint16_t APWMPOL:1;                 // 10  APWM output polarity select
    uint16_t CTRFILTRESET:1;            // 11 Reset event filter, modulus counter, and interrupt flags.
    uint16_t DMAEVTSEL:2;               // 13:12 DMA event select
    uint16_t MODCNTRSTS:2;              // 15:14 modulo counter status
};

union ECAP_ECCTL2_REG {
    uint16_t  all;
    struct  ECAP_ECCTL2_BITS  bit;
};

struct ECAP_ECEINT_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CEVT1:1;                   // 1 Capture Event 1 Interrupt Enable
    uint16_t CEVT2:1;                   // 2 Capture Event 2 Interrupt Enable
    uint16_t CEVT3:1;                   // 3 Capture Event 3 Interrupt Enable
    uint16_t CEVT4:1;                   // 4 Capture Event 4 Interrupt Enable
    uint16_t CTROVF:1;                  // 5 Counter Overflow Interrupt Enable
    uint16_t CTR_EQ_PRD:1;              // 6 Period Equal Interrupt Enable
    uint16_t CTR_EQ_CMP:1;              // 7 Compare Equal Interrupt Enable
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t MUNIT_1_ERROR_EVT1:1;      // 9 Monitoring unit 1 error event-1 interrupt enable
    uint16_t MUNIT_1_ERROR_EVT2:1;      // 10 Monitoring unit 1 error event-2 interrupt enable
    uint16_t MUNIT_2_ERROR_EVT1:1;      // 11 Monitoring unit 2 error event-1 interrupt enable
    uint16_t MUNIT_2_ERROR_EVT2:1;      // 12 Monitoring unit 2 error event-2 interrupt enable
    uint16_t rsvd3:3;                   // 15:13 Reserved
};

union ECAP_ECEINT_REG {
    uint16_t  all;
    struct  ECAP_ECEINT_BITS  bit;
};

struct ECAP_ECFLG_BITS {                // bits description
    uint16_t INT:1;                     // 0 Global Flag
    uint16_t CEVT1:1;                   // 1 Capture Event 1 Interrupt Flag
    uint16_t CEVT2:1;                   // 2 Capture Event 2 Interrupt Flag
    uint16_t CEVT3:1;                   // 3 Capture Event 3 Interrupt Flag
    uint16_t CEVT4:1;                   // 4 Capture Event 4 Interrupt Flag
    uint16_t CTROVF:1;                  // 5 Counter Overflow Interrupt Flag
    uint16_t CTR_PRD:1;                 // 6 Period Equal Interrupt Flag
    uint16_t CTR_CMP:1;                 // 7 Compare Equal Interrupt Flag
    uint16_t rsvd1:1;                   // 8 Reserved
    uint16_t MUNIT_1_ERROR_EVT1:1;      // 9 Error event 2 Interrupt Flag from monitoring unit 1
    uint16_t MUNIT_1_ERROR_EVT2:1;      // 10 Error event 2 Interrupt Flag from monitoring unit 1
    uint16_t MUNIT_2_ERROR_EVT1:1;      // 11 Error event 2 Interrupt Flag from monitoring unit 2
    uint16_t MUNIT_2_ERROR_EVT2:1;      // 12 Error event 2 Interrupt Flag from monitoring unit 2
    uint16_t rsvd2:3;                   // 15:13 Reserved
};

union ECAP_ECFLG_REG {
    uint16_t  all;
    struct  ECAP_ECFLG_BITS  bit;
};

struct ECAP_ECCLR_BITS {                // bits description
    uint16_t INT:1;                     // 0 ECAP Global Interrupt Status Clear
    uint16_t CEVT1:1;                   // 1 Capture Event 1 Status Clear
    uint16_t CEVT2:1;                   // 2 Capture Event 2 Status Clear
    uint16_t CEVT3:1;                   // 3 Capture Event 3 Status Clear
    uint16_t CEVT4:1;                   // 4 Capture Event 4 Status Clear
    uint16_t CTROVF:1;                  // 5 Counter Overflow Status Clear
    uint16_t CTR_PRD:1;                 // 6 Period Equal Status Clear
    uint16_t CTR_CMP:1;                 // 7 Compare Equal Status Clear
    uint16_t rsvd1:1;                   // 8 Reserved
    uint16_t MUNIT_1_ERROR_EVT1:1;      // 9 MUNIT_1_ERROR_EVT1 interrupt flag Clear
    uint16_t MUNIT_1_ERROR_EVT2:1;      // 10 MUNIT_1_ERROR_EVT2 interrupt flag Clear
    uint16_t MUNIT_2_ERROR_EVT1:1;      // 11 MUNIT_2_ERROR_EVT1 interrupt flag Clear
    uint16_t MUNIT_2_ERROR_EVT2:1;      // 12 MUNIT_2_ERROR_EVT2 interrupt flag Clear
    uint16_t rsvd2:3;                   // 15:13 Reserved
};

union ECAP_ECCLR_REG {
    uint16_t  all;
    struct  ECAP_ECCLR_BITS  bit;
};

struct ECAP_ECFRC_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CEVT1:1;                   // 1 Capture Event 1 Force Interrupt
    uint16_t CEVT2:1;                   // 2 Capture Event 2 Force Interrupt
    uint16_t CEVT3:1;                   // 3 Capture Event 3 Force Interrupt
    uint16_t CEVT4:1;                   // 4 Capture Event 4 Force Interrupt
    uint16_t CTROVF:1;                  // 5 Counter Overflow Force Interrupt
    uint16_t CTR_PRD:1;                 // 6 Period Equal Force Interrupt
    uint16_t CTR_CMP:1;                 // 7 Compare Equal Force Interrupt
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t MUNIT_1_ERROR_EVT1:1;      // 9 MUNIT_1_ERROR_EVT1 interrupt flag Set
    uint16_t MUNIT_1_ERROR_EVT2:1;      // 10 MUNIT_1_ERROR_EVT2 interrupt flag Set
    uint16_t MUNIT_2_ERROR_EVT1:1;      // 11 MUNIT_2_ERROR_EVT1 interrupt flag Set
    uint16_t MUNIT_2_ERROR_EVT2:1;      // 12 MUNIT_2_ERROR_EVT2 interrupt flag Set
    uint16_t rsvd3:3;                   // 15:13 Reserved
};

union ECAP_ECFRC_REG {
    uint16_t  all;
    struct  ECAP_ECFRC_BITS  bit;
};

struct ECAP_ECAPSYNCINSEL_BITS {        // bits description
    uint16_t SEL:7;                     // 6:0 SYNCIN source select
    uint16_t rsvd1:9;                   // 15:7 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAP_ECAPSYNCINSEL_REG {
    uint32_t  all;
    struct  ECAP_ECAPSYNCINSEL_BITS  bit;
};

struct ECAP_REGS {
    uint32_t                                 TSCTR;                        // Time-Stamp Counter
    uint32_t                                 CTRPHS;                       // Counter Phase Offset Value Register
    uint32_t                                 CAP1;                         // Capture 1 Register
    uint32_t                                 CAP2;                         // Capture 2 Register
    uint32_t                                 CAP3;                         // Capture 3 Register
    uint32_t                                 CAP4;                         // Capture 4 Register
    uint8_t                                  rsvd1[12];                    // Reserved
    union   ECAP_ECCTL0_REG                  ECCTL0;                       // Capture Control Register 0
    union   ECAP_ECCTL1_REG                  ECCTL1;                       // Capture Control Register 1
    union   ECAP_ECCTL2_REG                  ECCTL2;                       // Capture Control Register 2
    union   ECAP_ECEINT_REG                  ECEINT;                       // Capture Interrupt Enable Register
    union   ECAP_ECFLG_REG                   ECFLG;                        // Capture Interrupt Flag Register
    union   ECAP_ECCLR_REG                   ECCLR;                        // Capture Interrupt Clear Register
    union   ECAP_ECFRC_REG                   ECFRC;                        // Capture Interrupt Force Register
    uint8_t                                  rsvd2[8];                     // Reserved
    union   ECAP_ECAPSYNCINSEL_REG           ECAPSYNCINSEL;                // SYNC source select register
};

struct ECAP_HRCTL_BITS {                // bits description
    uint16_t HRE:1;                     // 0 High Resolution Enable
    uint16_t HRCLKE:1;                  // 1 High Resolution Clock Enable
    uint16_t PRDSEL:1;                  // 2 Calibration Period Match
    uint16_t CALIBSTART:1;              // 3 Calibration start
    uint16_t CALIBSTS:1;                // 4 Calibration status
    uint16_t CALIBCONT:1;               // 5 Continuous mode Calibration Select
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAP_HRCTL_REG {
    uint32_t  all;
    struct  ECAP_HRCTL_BITS  bit;
};

struct ECAP_HRINTEN_BITS {              // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CALIBDONE:1;               // 1 Calibration doe interrupt enable
    uint16_t CALPRDCHKSTS:1;            // 2 Calibration period check status enable
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ECAP_HRINTEN_REG {
    uint32_t  all;
    struct  ECAP_HRINTEN_BITS  bit;
};

struct ECAP_HRFLG_BITS {                // bits description
    uint16_t CALIBINT:1;                // 0 Global calibration Interrupt Status Flag
    uint16_t CALIBDONE:1;               // 1 Calibration Done Interrupt Flag Bit
    uint16_t CALPRDCHKSTS:1;            // 2 Calibration period check status Flag Bi
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAP_HRFLG_REG {
    uint32_t  all;
    struct  ECAP_HRFLG_BITS  bit;
};

struct ECAP_HRCLR_BITS {                // bits description
    uint16_t CALIBINT:1;                // 0 Clear Global calibration Interrupt Flag
    uint16_t CALIBDONE:1;               // 1 Clear Calibration Done Interrupt Flag Bit
    uint16_t CALPRDCHKSTS:1;            // 2 Clear Calibration period check status Flag Bit
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAP_HRCLR_REG {
    uint32_t  all;
    struct  ECAP_HRCLR_BITS  bit;
};

struct ECAP_HRFRC_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CALIBDONE:1;               // 1 Force Calibration Done Interrupt Flag Bit
    uint16_t CALPRDCHKSTS:1;            // 2 Force Calibration period check status Flag Bit
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ECAP_HRFRC_REG {
    uint32_t  all;
    struct  ECAP_HRFRC_BITS  bit;
};

struct HRCAP_REGS {
    union   ECAP_HRCTL_REG                   HRCTL;                        // High-Res Control Register
    uint8_t                                  rsvd1[4];                     // Reserved
    union   ECAP_HRINTEN_REG                 HRINTEN;                      // High-Res Calibration Interrupt Enable Register
    union   ECAP_HRFLG_REG                   HRFLG;                        // High-Res Calibration Interrupt Flag Register
    union   ECAP_HRCLR_REG                   HRCLR;                        // High-Res Calibration Interrupt Clear Register
    union   ECAP_HRFRC_REG                   HRFRC;                        // High-Res Calibration Interrupt Force Register
    uint32_t                                 HRCALPRD;                     // High-Res Calibration Period Register
    uint32_t                                 HRSYSCLKCTR;                  // High-Res Calibration SYSCLK Counter Register
    uint32_t                                 HRSYSCLKCAP;                  // High-Res Calibration SYSCLK Capture Register
    uint32_t                                 HRCLKCTR;                     // High-Res Calibration HRCLK Counter Register
    uint32_t                                 HRCLKCAP;                     // High-Res Calibration HRCLK Capture Register
};

struct ECAP_MUNIT_COMMON_CTL_BITS {     // bits description
    uint16_t TRIPSEL:7;                 // 6:0 Trip signal select
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t GLDSTRBSEL:7;              // 14:8 Global Load strobe select
    uint16_t rsvd2:1;                   // 15 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ECAP_MUNIT_COMMON_CTL_REG {
    uint32_t  all;
    struct  ECAP_MUNIT_COMMON_CTL_BITS  bit;
};

struct ECAP_MUNIT_1_CTL_BITS {          // bits description
    uint16_t EN:1;                      // 0 Enable bit
    uint16_t DEBUG_RANGE_EN:1;          // 1 Debug enable to aquire the range of check being done
    uint16_t DISABLE_EARLY_MAX_ERR:1;   // 2 Disable early max error check
    uint16_t rsvd1:5;                   // 7:3 Reserved
    uint16_t MON_SEL:4;                 // 11:8 Selects type of monitoring
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ECAP_MUNIT_1_CTL_REG {
    uint32_t  all;
    struct  ECAP_MUNIT_1_CTL_BITS  bit;
};

struct ECAP_MUNIT_1_SHADOW_CTL_BITS {   // bits description
    uint16_t SYNCI_EN:1;                // 0 Enable for shadowing on Min and Max Registers
    uint16_t SWSYNC:1;                  // 1 SW sync to copy shadow to active Min and Max registers
    uint16_t LOADMODE:1;                // 2 Load mode
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAP_MUNIT_1_SHADOW_CTL_REG {
    uint32_t  all;
    struct  ECAP_MUNIT_1_SHADOW_CTL_BITS  bit;
};

struct ECAP_MUNIT_2_CTL_BITS {          // bits description
    uint16_t EN:1;                      // 0 Enable bit
    uint16_t DEBUG_RANGE_EN:1;          // 1 Debug enable to aquire the range of check being done
    uint16_t DISABLE_EARLY_MAX_ERR:1;   // 2 Disable early max error check
    uint16_t rsvd1:5;                   // 7:3 Reserved
    uint16_t MON_SEL:4;                 // 11:8 Selects type of monitoring
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ECAP_MUNIT_2_CTL_REG {
    uint32_t  all;
    struct  ECAP_MUNIT_2_CTL_BITS  bit;
};

struct ECAP_MUNIT_2_SHADOW_CTL_BITS {   // bits description
    uint16_t SYNCI_EN:1;                // 0 Enable for shadowing on Min and Max Registers
    uint16_t SWSYNC:1;                  // 1 SW sync to copy shadow to active Min and Max registers
    uint16_t LOADMODE:1;                // 2 Load mode
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAP_MUNIT_2_SHADOW_CTL_REG {
    uint32_t  all;
    struct  ECAP_MUNIT_2_SHADOW_CTL_BITS  bit;
};

struct ECAP_SIGNAL_MONITORING {
    union   ECAP_MUNIT_COMMON_CTL_REG        MUNIT_COMMON_CTL;             // Control registers for monitoring unit {#}
    uint8_t                                  rsvd1[60];                    // Reserved
    union   ECAP_MUNIT_1_CTL_REG             MUNIT_1_CTL;                  // Control registers for monitoring unit 1
    union   ECAP_MUNIT_1_SHADOW_CTL_REG      MUNIT_1_SHADOW_CTL;           // Shadow control registers for monitoring unit 1
    uint8_t                                  rsvd2[8];                     // Reserved
    uint32_t                                 MUNIT_1_MIN;                  // Min value for monitoring unit 1
    uint32_t                                 MUNIT_1_MAX;                  // Max value for monitoring unit 1
    uint32_t                                 MUNIT_1_MIN_SHADOW;           // Shadow register for Min value of monitoring unit 1
    uint32_t                                 MUNIT_1_MAX_SHADOW;           // Shadow register for Max value of monitoring unit 1
    uint32_t                                 MUNIT_1_DEBUG_RANGE_MIN;      // Observed Min value of check being enabled on minotoring unit 1
    uint32_t                                 MUNIT_1_DEBUG_RANGE_MAX;      // Observed Max value of check being enabled on minotoring unit 1
    uint8_t                                  rsvd3[24];                    // Reserved
    union   ECAP_MUNIT_2_CTL_REG             MUNIT_2_CTL;                  // Control registers for monitoring unit 2
    union   ECAP_MUNIT_2_SHADOW_CTL_REG      MUNIT_2_SHADOW_CTL;           // Shadow control registers for monitoring unit 2
    uint8_t                                  rsvd4[8];                     // Reserved
    uint32_t                                 MUNIT_2_MIN;                  // Min value for monitoring unit 2
    uint32_t                                 MUNIT_2_MAX;                  // Max value for monitoring unit 2
    uint32_t                                 MUNIT_2_MIN_SHADOW;           // Shadow register for Min value of monitoring unit 2
    uint32_t                                 MUNIT_2_MAX_SHADOW;           // Shadow register for Max value of monitoring unit 2
    uint32_t                                 MUNIT_2_DEBUG_RANGE_MIN;      // Observed Min value of check being enabled on minotoring unit 2
    uint32_t                                 MUNIT_2_DEBUG_RANGE_MAX;      // Observed Max value of check being enabled on minotoring unit 2
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
