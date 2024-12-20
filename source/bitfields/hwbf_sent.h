//###########################################################################
//
// FILE:    hwbf_sent.h
//
// TITLE:   Definitions for the SENT registers.
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

#ifndef HWBF_SENT_H
#define HWBF_SENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// SENT Individual Register Bit Definitions:

struct SENT_RCFG_BITS {                 // bits description
    uint16_t RX_ENB:1;                  // 0
    uint16_t RX_CRCENB:1;               // 1
    uint16_t RSVD_0:1;                  // 2
    uint16_t RX_PPENB:1;                // 3
    uint16_t RX_DNIB:4;                 // 7:4
    uint16_t CRC_WIDTH:2;               // 9:8
    uint16_t RX_CRC_WITH_STATUS:1;      // 10
    uint16_t RX_CRCTYPE:1;              // 11
    uint16_t RSVD:4;                    // 15:12
    uint16_t TTCLK:16;                  // 31:16
};

union SENT_RCFG_REG {
    uint32_t  all;
    struct  SENT_RCFG_BITS  bit;
};

struct SENT_RSDATA_BITS {               // bits description
    uint16_t CRC:6;                     // 5:0
    uint16_t RSVD:1;                    // 6
    uint16_t C:1;                       // 7
    uint32_t DATA:16;                   // 23:8
    uint16_t MESSAGEID:8;               // 31:24
};

union SENT_RSDATA_REG {
    uint32_t  all;
    struct  SENT_RSDATA_BITS  bit;
};

struct SENT_RSTAT_BITS {                // bits description
    uint16_t RXNIB:4;                   // 3:0
    uint16_t PP:1;                      // 4
    uint16_t RSVD:3;                    // 7:5
    uint16_t RXSLOW_ST:5;               // 12:8
    uint16_t RXSLOW_ACT:1;              // 13
    uint16_t RXSLOW_DN:1;               // 14
    uint16_t RX_SYNC:1;                 // 15
    uint16_t RX_TTCLK:16;               // 31:16
};

union SENT_RSTAT_REG {
    uint32_t  all;
    struct  SENT_RSTAT_BITS  bit;
};

struct SENT_RCFG2_BITS {                // bits description
    uint16_t FIFO_MODE:1;               // 0
    uint16_t DMA_ENB:1;                 // 1
    uint16_t TSTAMP_DIS:1;              // 2
    uint16_t NOWR_ERRDATA:1;            // 3
    uint16_t GFILT:8;                   // 11:4
    uint16_t RFIFO_TRIGLEV:4;           // 19:16
    uint16_t RSVD:3;                    // 15:13
    uint16_t MTP_MODE:1;                // 12
    uint16_t RSVD_0:12;                 // 31:20
};

union SENT_RCFG2_REG {
    uint32_t  all;
    struct  SENT_RCFG2_BITS  bit;
};

struct SENT_RINTFLAG_BITS {             // bits description
    uint16_t GLBL:1;                    // 0
    uint16_t RFAST_S1DV:1;              // 1
    uint16_t RFAST_S2DV:1;              // 2
    uint16_t RFAST_S3DV:1;              // 3
    uint16_t RFAST_S4DV:1;              // 4
    uint16_t RSLOW_DV:1;                // 5
    uint16_t RSLOW_CRCERR:1;            // 6
    uint16_t RSLOW_FORMATERR:1;         // 7
    uint16_t RFAST_S1CRCE:1;            // 8
    uint16_t RFAST_S2CRCE:1;            // 9
    uint16_t RFAST_S3CRCE:1;            // 10
    uint16_t RFAST_S4CRCE:1;            // 11
    uint16_t RFAST_S1FRME:1;            // 12
    uint16_t RFAST_S2FRME:1;            // 13
    uint16_t RFAST_S3FRME:1;            // 14
    uint16_t RFAST_S4FRME:1;            // 15
    uint16_t RTIMEOUT_ERR:4;            // 19:16
    uint16_t RFAST_SYNCERR25:1;         // 20
    uint16_t RFAST_SYNCERR:1;           // 21
    uint16_t FREQDRIFT_ERR:1;           // 22
    uint16_t RFIFO_TRIGGER:1;           // 23
    uint16_t RFIFO_OVFERR:1;            // 24
    uint16_t RFIFO_UNDFERR:1;           // 25
    uint16_t OVFTRIG_ERR:5;             // 30:26
    uint16_t RSVD:1;                    // 31
};

union SENT_RINTFLAG_REG {
    uint32_t  all;
    struct  SENT_RINTFLAG_BITS  bit;
};

struct SENT_REINT_BITS {                // bits description
    uint16_t RSVD:1;                    // 0
    uint16_t RSVD_1:1;                  // 31
    uint16_t RFAST_S2DV_E:1;            // 2
    uint16_t RFAST_S3DV_E:1;            // 3
    uint16_t RFAST_S4DV_E:1;            // 4
    uint16_t RSLOW_DV_E:1;              // 5
    uint16_t RSLOW_CRCERR_E:1;          // 6
    uint16_t RSLOW_FORMATERR_E:1;       // 7
    uint16_t RFAST_S1CRCE_E:1;          // 8
    uint16_t RFAST_S2CRCE_E:1;          // 9
    uint16_t RFAST_S3CRCE_E:1;          // 10
    uint16_t RFAST_S4CRCE_E:1;          // 11
    uint16_t RFAST_S1FRME_E:1;          // 12
    uint16_t RFAST_S2FRME_E:1;          // 13
    uint16_t RFAST_S3FRME_E:1;          // 14
    uint16_t RFAST_S4FRME_E:1;          // 15
    uint16_t RTIMEOUT_ERR_E:4;          // 19:16
    uint16_t RFAST_SYNCERR25_E:1;       // 20
    uint16_t RFAST_SYNCERR_E:1;         // 21
    uint16_t FREQDRIFT_ERR_E:1;         // 22
    uint16_t RFIFO_TRIGGER_E:1;         // 23
    uint16_t RFIFO_OVFERR_E:1;          // 24
    uint16_t RFIFO_UNDFERR_E:1;         // 25
    uint16_t OVFTRIG_ERR_E:5;           // 30:26
    uint16_t RFAST_S1DV_E:1;            // 1
};

union SENT_REINT_REG {
    uint32_t  all;
    struct  SENT_REINT_BITS  bit;
};

struct SENT_RSETINT_BITS {              // bits description
    uint16_t RSVD_0:1;                  // 31
    uint16_t RFAST_S1DV_S:1;            // 1
    uint16_t RFAST_S2DV_S:1;            // 2
    uint16_t RFAST_S3DV_S:1;            // 3
    uint16_t RFAST_S4DV_S:1;            // 4
    uint16_t RSLOW_DV_S:1;              // 5
    uint16_t RSLOW_CRCERR_S:1;          // 6
    uint16_t RSLOW_FORMATERR_S:1;       // 7
    uint16_t RFAST_S1CRCE_S:1;          // 8
    uint16_t RFAST_S2CRCE_S:1;          // 9
    uint16_t RFAST_S3CRCE_S:1;          // 10
    uint16_t RFAST_S4CRCE_S:1;          // 11
    uint16_t RFAST_S1FRME_S:1;          // 12
    uint16_t RFAST_S2FRME_S:1;          // 13
    uint16_t RFAST_S3FRME_S:1;          // 14
    uint16_t RFAST_S4FRME_S:1;          // 15
    uint16_t RTIMEOUT_ERR_S:4;          // 19:16
    uint16_t RFAST_SYNCERR25_S:1;       // 20
    uint16_t RFAST_SYNCERR_S:1;         // 21
    uint16_t FREQDRIFT_ERR_S:1;         // 22
    uint16_t RFIFO_TRIGGER_S:1;         // 23
    uint16_t RFIFO_OVFERR_S:1;          // 24
    uint16_t RFIFO_UNDFERR_S:1;         // 25
    uint16_t OVFTRIG_ERR_S:5;           // 30:26
    uint16_t RSVD:1;                    // 0
};

union SENT_RSETINT_REG {
    uint32_t  all;
    struct  SENT_RSETINT_BITS  bit;
};

struct SENT_RCLRINT_BITS {              // bits description
    uint16_t GLBL_CLR:1;                // 0
    uint16_t RFAST_S1DV_CLR:1;          // 1
    uint16_t RFAST_S2DV_CLR:1;          // 2
    uint16_t RFAST_S3DV_CLR:1;          // 3
    uint16_t RFAST_S4DV_CLR:1;          // 4
    uint16_t RSLOW_DV_CLR:1;            // 5
    uint16_t RSLOW_CRCERR_CLR:1;        // 6
    uint16_t RSLOW_FORMATERR_CLR:1;     // 7
    uint16_t RFAST_S1CRCE_CLR:1;        // 8
    uint16_t RFAST_S2CRCE_CLR:1;        // 9
    uint16_t RFAST_S3CRCE_CLR:1;        // 10
    uint16_t RFAST_S4CRCE_CLR:1;        // 11
    uint16_t RFAST_S1FRME_CLR:1;        // 12
    uint16_t RFAST_S2FRME_CLR:1;        // 13
    uint16_t RFAST_S3FRME_CLR:1;        // 14
    uint16_t RFAST_S4FRME_CLR:1;        // 15
    uint16_t RTIMEOUT_ERR_CLR:4;        // 19:16
    uint16_t RFAST_SYNCERR25_CLR:1;     // 20
    uint16_t RFAST_SYNCERR_CLR:1;       // 21
    uint16_t FREQDRIFT_ERR_CLR:1;       // 22
    uint16_t RFIFO_TRIGGER_CLR:1;       // 23
    uint16_t RFIFO_OVFERR_CLR:1;        // 24
    uint16_t RFIFO_UNDFERR_CLR:1;       // 25
    uint16_t OVFTRIG_ERR_CLR:5;         // 30:26
    uint16_t RSVD:1;                    // 31
};

union SENT_RCLRINT_REG {
    uint32_t  all;
    struct  SENT_RCLRINT_BITS  bit;
};

struct SENT_CSENT_SWR_BITS {            // bits description
    uint16_t SWR:1;                     // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_CSENT_SWR_REG {
    uint32_t  all;
    struct  SENT_CSENT_SWR_BITS  bit;
};

struct SENT_DATA0_MAP_BITS {            // bits description
    uint16_t D0_NIB0:4;                 // 3:0
    uint16_t D0_NIB1:4;                 // 7:4
    uint16_t D0_NIB2:4;                 // 11:8
    uint16_t D0_NIB3:4;                 // 15:12
    uint16_t D0_NIB4:4;                 // 19:16
    uint16_t D0_NIB5:4;                 // 23:20
    uint16_t D0_NIB6:4;                 // 27:24
    uint16_t D0_NIB7:4;                 // 31:28
};

union SENT_DATA0_MAP_REG {
    uint32_t  all;
    struct  SENT_DATA0_MAP_BITS  bit;
};

struct SENT_DATA1_MAP_BITS {            // bits description
    uint16_t D1_NIB0:4;                 // 3:0
    uint16_t D1_NIB1:4;                 // 7:4
    uint16_t D1_NIB2:4;                 // 11:8
    uint16_t D1_NIB3:4;                 // 15:12
    uint16_t D1_NIB4:4;                 // 19:16
    uint16_t D1_NIB5:4;                 // 23:20
    uint16_t D1_NIB6:4;                 // 27:24
    uint16_t D1_NIB7:4;                 // 31:28
};

union SENT_DATA1_MAP_REG {
    uint32_t  all;
    struct  SENT_DATA1_MAP_BITS  bit;
};

struct SENT_CSENT_RXD_BITS {            // bits description
    uint16_t RXD_I_R:1;                 // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_CSENT_RXD_REG {
    uint32_t  all;
    struct  SENT_CSENT_RXD_BITS  bit;
};

struct SENT_RXVAL_CNT_BITS {            // bits description
    uint16_t RXVALID_CNT_R:8;           // 7:0
    uint32_t RSVD:24;                   // 31:8
};

union SENT_RXVAL_CNT_REG {
    uint32_t  all;
    struct  SENT_RXVAL_CNT_BITS  bit;
};

struct SENT_RXDEDGE_CNT_BITS {          // bits description
    uint16_t RXDEDGE_CNT_R:8;           // 7:0
    uint32_t RSVD:24;                   // 31:8
};

union SENT_RXDEDGE_CNT_REG {
    uint32_t  all;
    struct  SENT_RXDEDGE_CNT_BITS  bit;
};

struct SENT_SWR_RXVAL_CNT_BITS {        // bits description
    uint16_t SWR_RXVAL_CNT:1;           // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_SWR_RXVAL_CNT_REG {
    uint32_t  all;
    struct  SENT_SWR_RXVAL_CNT_BITS  bit;
};

struct SENT_SWR_RXDEDGE_CNT_BITS {      // bits description
    uint16_t SWR_RXDEDGE_CNT:1;         // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_SWR_RXDEDGE_CNT_REG {
    uint32_t  all;
    struct  SENT_SWR_RXDEDGE_CNT_BITS  bit;
};

struct SENT_CFG {
    uint8_t                                  rsvd1[32];                    // Reserved
    union   SENT_RCFG_REG                    RCFG;                         // 
    uint32_t                                 RFDATA;                       // 
    union   SENT_RSDATA_REG                  RSDATA;                       // 
    union   SENT_RSTAT_REG                   RSTAT;                        // 
    uint8_t                                  rsvd2[4];                     // Reserved
    union   SENT_RCFG2_REG                   RCFG2;                        // 
    uint8_t                                  rsvd3[8];                     // Reserved
    union   SENT_RINTFLAG_REG                RINTFLAG;                     // 
    union   SENT_REINT_REG                   REINT;                        // 
    union   SENT_RSETINT_REG                 RSETINT;                      // 
    union   SENT_RCLRINT_REG                 RCLRINT;                      // 
    union   SENT_CSENT_SWR_REG               CSENT_SWR;                    // 
    union   SENT_DATA0_MAP_REG               DATA0_MAP;                    // 
    union   SENT_DATA1_MAP_REG               DATA1_MAP;                    // 
    uint32_t                                 CSENT_TO;                     // 
    union   SENT_CSENT_RXD_REG               CSENT_RXD;                    // 
    union   SENT_RXVAL_CNT_REG               RXVAL_CNT;                    // 
    union   SENT_RXDEDGE_CNT_REG             RXDEDGE_CNT;                  // 
    union   SENT_SWR_RXVAL_CNT_REG           SWR_RXVAL_CNT;                // 
    union   SENT_SWR_RXDEDGE_CNT_REG         SWR_RXDEDGE_CNT;              // 
    uint8_t                                  rsvd4[8];                     // Reserved
    uint32_t                                 CSENT_VERSION;                // 
};

struct SENT_MEM {
    uint32_t                                 MDATA[16];                    // Data word 'N' in TPRAM memory. The SENT TPRAM contains fast channel SENT frames whether in FIFO or Direct Map mode. In Direct Map mode, the user must read the SENT frame data out from this memory (refer to the section regarding Receive Modes for more details)
};

struct SENT_BC_MTP_EN_BITS {            // bits description
    uint16_t MTP_EN:1;                  // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_BC_MTP_EN_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_EN_BITS  bit;
};

struct SENT_BC_MTP_CMP1_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP1_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP1_BITS  bit;
};

struct SENT_BC_MTP_CMP2_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP2_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP2_BITS  bit;
};

struct SENT_BC_MTP_CMP3_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP3_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP3_BITS  bit;
};

struct SENT_BC_MTP_CMP4_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP4_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP4_BITS  bit;
};

struct SENT_BC_MTP_CMP5_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP5_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP5_BITS  bit;
};

struct SENT_BC_MTP_CMP6_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP6_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP6_BITS  bit;
};

struct SENT_BC_MTP_CMP7_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP7_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP7_BITS  bit;
};

struct SENT_BC_MTP_CMP8_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP8_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP8_BITS  bit;
};

struct SENT_BC_MTP_CMP9_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_CMP9_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_CMP9_BITS  bit;
};

struct SENT_BC_MTP_PERIOD_BITS {        // bits description
    uint16_t PERIOD:11;                 // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_BC_MTP_PERIOD_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_PERIOD_BITS  bit;
};

struct SENT_BC_TRIGSEL_BITS {           // bits description
    uint16_t TRIGSEL:7;                 // 6:0
    uint32_t RSVD:25;                   // 31:7
};

union SENT_BC_TRIGSEL_REG {
    uint32_t  all;
    struct  SENT_BC_TRIGSEL_BITS  bit;
};

struct SENT_BC_MTP_SWTR_BITS {          // bits description
    uint16_t SWTR:1;                    // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_BC_MTP_SWTR_REG {
    uint32_t  all;
    struct  SENT_BC_MTP_SWTR_BITS  bit;
};

struct SENT_S1_MTP_EN_BITS {            // bits description
    uint16_t MTP_EN:1;                  // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_S1_MTP_EN_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_EN_BITS  bit;
};

struct SENT_S1_MTP_CMP1_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP1_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP1_BITS  bit;
};

struct SENT_S1_MTP_CMP2_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP2_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP2_BITS  bit;
};

struct SENT_S1_MTP_CMP3_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP3_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP3_BITS  bit;
};

struct SENT_S1_MTP_CMP4_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP4_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP4_BITS  bit;
};

struct SENT_S1_MTP_CMP5_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP5_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP5_BITS  bit;
};

struct SENT_S1_MTP_CMP6_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP6_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP6_BITS  bit;
};

struct SENT_S1_MTP_CMP7_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP7_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP7_BITS  bit;
};

struct SENT_S1_MTP_CMP8_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP8_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP8_BITS  bit;
};

struct SENT_S1_MTP_CMP9_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP9_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP9_BITS  bit;
};

struct SENT_S1_MTP_CMP10RE_BITS {       // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_CMP10RE_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_CMP10RE_BITS  bit;
};

struct SENT_S1_MTP_PERIOD_BITS {        // bits description
    uint16_t PERIOD:11;                 // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S1_MTP_PERIOD_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_PERIOD_BITS  bit;
};

struct SENT_S1_TRIGSEL_BITS {           // bits description
    uint16_t TRIGSEL:7;                 // 6:0
    uint32_t RSVD:25;                   // 31:7
};

union SENT_S1_TRIGSEL_REG {
    uint32_t  all;
    struct  SENT_S1_TRIGSEL_BITS  bit;
};

struct SENT_S1_MTP_SWTR_BITS {          // bits description
    uint16_t SWTR:1;                    // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_S1_MTP_SWTR_REG {
    uint32_t  all;
    struct  SENT_S1_MTP_SWTR_BITS  bit;
};

struct SENT_S2_MTP_EN_BITS {            // bits description
    uint16_t MTP_EN:1;                  // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_S2_MTP_EN_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_EN_BITS  bit;
};

struct SENT_S2_MTP_CMP1_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP1_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP1_BITS  bit;
};

struct SENT_S2_MTP_CMP2_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP2_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP2_BITS  bit;
};

struct SENT_S2_MTP_CMP3_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP3_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP3_BITS  bit;
};

struct SENT_S2_MTP_CMP4_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP4_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP4_BITS  bit;
};

struct SENT_S2_MTP_CMP5_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP5_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP5_BITS  bit;
};

struct SENT_S2_MTP_CMP6_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP6_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP6_BITS  bit;
};

struct SENT_S2_MTP_CMP7_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP7_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP7_BITS  bit;
};

struct SENT_S2_MTP_CMP8_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP8_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP8_BITS  bit;
};

struct SENT_S2_MTP_CMP9_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP9_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP9_BITS  bit;
};

struct SENT_S2_MTP_CMP10RE_BITS {       // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_CMP10RE_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_CMP10RE_BITS  bit;
};

struct SENT_S2_MTP_PERIOD_BITS {        // bits description
    uint16_t PERIOD:11;                 // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S2_MTP_PERIOD_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_PERIOD_BITS  bit;
};

struct SENT_S2_TRIGSEL_BITS {           // bits description
    uint16_t TRIGSEL:7;                 // 6:0
    uint32_t RSVD:25;                   // 31:7
};

union SENT_S2_TRIGSEL_REG {
    uint32_t  all;
    struct  SENT_S2_TRIGSEL_BITS  bit;
};

struct SENT_S2_MTP_SWTR_BITS {          // bits description
    uint16_t SWTR:1;                    // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_S2_MTP_SWTR_REG {
    uint32_t  all;
    struct  SENT_S2_MTP_SWTR_BITS  bit;
};

struct SENT_S3_MTP_EN_BITS {            // bits description
    uint16_t MTP_EN:1;                  // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_S3_MTP_EN_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_EN_BITS  bit;
};

struct SENT_S3_MTP_CMP1_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP1_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP1_BITS  bit;
};

struct SENT_S3_MTP_CMP2_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP2_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP2_BITS  bit;
};

struct SENT_S3_MTP_CMP3_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP3_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP3_BITS  bit;
};

struct SENT_S3_MTP_CMP4_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP4_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP4_BITS  bit;
};

struct SENT_S3_MTP_CMP5_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP5_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP5_BITS  bit;
};

struct SENT_S3_MTP_CMP6_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP6_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP6_BITS  bit;
};

struct SENT_S3_MTP_CMP7_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP7_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP7_BITS  bit;
};

struct SENT_S3_MTP_CMP8_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP8_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP8_BITS  bit;
};

struct SENT_S3_MTP_CMP9_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP9_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP9_BITS  bit;
};

struct SENT_S3_MTP_CMP10RE_BITS {       // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_CMP10RE_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_CMP10RE_BITS  bit;
};

struct SENT_S3_MTP_PERIOD_BITS {        // bits description
    uint16_t PERIOD:11;                 // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S3_MTP_PERIOD_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_PERIOD_BITS  bit;
};

struct SENT_S3_TRIGSEL_BITS {           // bits description
    uint16_t TRIGSEL:7;                 // 6:0
    uint32_t RSVD:25;                   // 31:7
};

union SENT_S3_TRIGSEL_REG {
    uint32_t  all;
    struct  SENT_S3_TRIGSEL_BITS  bit;
};

struct SENT_S3_MTP_SWTR_BITS {          // bits description
    uint16_t SWTR:1;                    // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_S3_MTP_SWTR_REG {
    uint32_t  all;
    struct  SENT_S3_MTP_SWTR_BITS  bit;
};

struct SENT_S4_MTP_EN_BITS {            // bits description
    uint16_t MTP_EN:1;                  // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_S4_MTP_EN_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_EN_BITS  bit;
};

struct SENT_S4_MTP_CMP1_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP1_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP1_BITS  bit;
};

struct SENT_S4_MTP_CMP2_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP2_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP2_BITS  bit;
};

struct SENT_S4_MTP_CMP3_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP3_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP3_BITS  bit;
};

struct SENT_S4_MTP_CMP4_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP4_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP4_BITS  bit;
};

struct SENT_S4_MTP_CMP5_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP5_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP5_BITS  bit;
};

struct SENT_S4_MTP_CMP6_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP6_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP6_BITS  bit;
};

struct SENT_S4_MTP_CMP7_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP7_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP7_BITS  bit;
};

struct SENT_S4_MTP_CMP8_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP8_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP8_BITS  bit;
};

struct SENT_S4_MTP_CMP9_BITS {          // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP9_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP9_BITS  bit;
};

struct SENT_S4_MTP_CMP10RE_BITS {       // bits description
    uint16_t TOGGLETIME:11;             // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_CMP10RE_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_CMP10RE_BITS  bit;
};

struct SENT_S4_MTP_PERIOD_BITS {        // bits description
    uint16_t PERIOD:11;                 // 10:0
    uint32_t RSVD:21;                   // 31:11
};

union SENT_S4_MTP_PERIOD_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_PERIOD_BITS  bit;
};

struct SENT_S4_TRIGSEL_BITS {           // bits description
    uint16_t TRIGSEL:7;                 // 6:0
    uint32_t RSVD:25;                   // 31:7
};

union SENT_S4_TRIGSEL_REG {
    uint32_t  all;
    struct  SENT_S4_TRIGSEL_BITS  bit;
};

struct SENT_S4_MTP_SWTR_BITS {          // bits description
    uint16_t SWTR:1;                    // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_S4_MTP_SWTR_REG {
    uint32_t  all;
    struct  SENT_S4_MTP_SWTR_BITS  bit;
};

struct SENT_WAITTIME_BITS {             // bits description
    uint16_t WAITTIME:16;               // 15:0
    uint16_t RSVD:16;                   // 31:16
};

union SENT_WAITTIME_REG {
    uint32_t  all;
    struct  SENT_WAITTIME_BITS  bit;
};

struct SENT_TPGENSTAT_BITS {            // bits description
    uint16_t ACTIVE_CH:5;               // 4:0
    uint16_t SWTSTAT:1;                 // 7
    uint16_t TRIG_REQ:5;                // 12:8
    uint16_t RSVD:2;                    // 6:5
    uint32_t RSVD_1:19;                 // 31:13
};

union SENT_TPGENSTAT_REG {
    uint32_t  all;
    struct  SENT_TPGENSTAT_BITS  bit;
};

struct SENT_MTP_SWR_BITS {              // bits description
    uint16_t SWR:1;                     // 0
    uint32_t RSVD:31;                   // 31:1
};

union SENT_MTP_SWR_REG {
    uint32_t  all;
    struct  SENT_MTP_SWR_BITS  bit;
};

struct SENT_MTPG {
    union   SENT_BC_MTP_EN_REG               BC_MTP_EN;                    // 
    union   SENT_BC_MTP_CMP1_REG             BC_MTP_CMP1;                  // 
    union   SENT_BC_MTP_CMP2_REG             BC_MTP_CMP2;                  // 
    union   SENT_BC_MTP_CMP3_REG             BC_MTP_CMP3;                  // 
    union   SENT_BC_MTP_CMP4_REG             BC_MTP_CMP4;                  // 
    union   SENT_BC_MTP_CMP5_REG             BC_MTP_CMP5;                  // 
    union   SENT_BC_MTP_CMP6_REG             BC_MTP_CMP6;                  // 
    union   SENT_BC_MTP_CMP7_REG             BC_MTP_CMP7;                  // 
    union   SENT_BC_MTP_CMP8_REG             BC_MTP_CMP8;                  // 
    union   SENT_BC_MTP_CMP9_REG             BC_MTP_CMP9;                  // 
    uint8_t                                  rsvd2[4];                     // Reserved
    union   SENT_BC_MTP_PERIOD_REG           BC_MTP_PERIOD;                // 
    uint8_t                                  rsvd3[4];                     // Reserved
    union   SENT_BC_TRIGSEL_REG              BC_TRIGSEL;                   // 
    union   SENT_BC_MTP_SWTR_REG             BC_MTP_SWTR;                  // 
    uint8_t                                  rsvd4[196];                   // Reserved
    union   SENT_S1_MTP_EN_REG               S1_MTP_EN;                    // 
    union   SENT_S1_MTP_CMP1_REG             S1_MTP_CMP1;                  // 
    union   SENT_S1_MTP_CMP2_REG             S1_MTP_CMP2;                  // 
    union   SENT_S1_MTP_CMP3_REG             S1_MTP_CMP3;                  // 
    union   SENT_S1_MTP_CMP4_REG             S1_MTP_CMP4;                  // 
    union   SENT_S1_MTP_CMP5_REG             S1_MTP_CMP5;                  // 
    union   SENT_S1_MTP_CMP6_REG             S1_MTP_CMP6;                  // 
    union   SENT_S1_MTP_CMP7_REG             S1_MTP_CMP7;                  // 
    union   SENT_S1_MTP_CMP8_REG             S1_MTP_CMP8;                  // 
    union   SENT_S1_MTP_CMP9_REG             S1_MTP_CMP9;                  // 
    union   SENT_S1_MTP_CMP10RE_REG          S1_MTP_CMP10RE;               // 
    union   SENT_S1_MTP_PERIOD_REG           S1_MTP_PERIOD;                // 
    uint32_t                                 S1_MTP_TO;                    // 
    union   SENT_S1_TRIGSEL_REG              S1_TRIGSEL;                   // 
    union   SENT_S1_MTP_SWTR_REG             S1_MTP_SWTR;                  // 
    uint8_t                                  rsvd5[196];                   // Reserved
    union   SENT_S2_MTP_EN_REG               S2_MTP_EN;                    // 
    union   SENT_S2_MTP_CMP1_REG             S2_MTP_CMP1;                  // 
    union   SENT_S2_MTP_CMP2_REG             S2_MTP_CMP2;                  // 
    union   SENT_S2_MTP_CMP3_REG             S2_MTP_CMP3;                  // 
    union   SENT_S2_MTP_CMP4_REG             S2_MTP_CMP4;                  // 
    union   SENT_S2_MTP_CMP5_REG             S2_MTP_CMP5;                  // 
    union   SENT_S2_MTP_CMP6_REG             S2_MTP_CMP6;                  // 
    union   SENT_S2_MTP_CMP7_REG             S2_MTP_CMP7;                  // 
    union   SENT_S2_MTP_CMP8_REG             S2_MTP_CMP8;                  // 
    union   SENT_S2_MTP_CMP9_REG             S2_MTP_CMP9;                  // 
    union   SENT_S2_MTP_CMP10RE_REG          S2_MTP_CMP10RE;               // 
    union   SENT_S2_MTP_PERIOD_REG           S2_MTP_PERIOD;                // 
    uint32_t                                 S2_MTP_TO;                    // 
    union   SENT_S2_TRIGSEL_REG              S2_TRIGSEL;                   // 
    union   SENT_S2_MTP_SWTR_REG             S2_MTP_SWTR;                  // 
    uint8_t                                  rsvd6[196];                   // Reserved
    union   SENT_S3_MTP_EN_REG               S3_MTP_EN;                    // 
    union   SENT_S3_MTP_CMP1_REG             S3_MTP_CMP1;                  // 
    union   SENT_S3_MTP_CMP2_REG             S3_MTP_CMP2;                  // 
    union   SENT_S3_MTP_CMP3_REG             S3_MTP_CMP3;                  // 
    union   SENT_S3_MTP_CMP4_REG             S3_MTP_CMP4;                  // 
    union   SENT_S3_MTP_CMP5_REG             S3_MTP_CMP5;                  // 
    union   SENT_S3_MTP_CMP6_REG             S3_MTP_CMP6;                  // 
    union   SENT_S3_MTP_CMP7_REG             S3_MTP_CMP7;                  // 
    union   SENT_S3_MTP_CMP8_REG             S3_MTP_CMP8;                  // 
    union   SENT_S3_MTP_CMP9_REG             S3_MTP_CMP9;                  // 
    union   SENT_S3_MTP_CMP10RE_REG          S3_MTP_CMP10RE;               // 
    union   SENT_S3_MTP_PERIOD_REG           S3_MTP_PERIOD;                // 
    uint32_t                                 S3_MTP_TO;                    // 
    union   SENT_S3_TRIGSEL_REG              S3_TRIGSEL;                   // 
    union   SENT_S3_MTP_SWTR_REG             S3_MTP_SWTR;                  // 
    uint8_t                                  rsvd7[196];                   // Reserved
    union   SENT_S4_MTP_EN_REG               S4_MTP_EN;                    // 
    union   SENT_S4_MTP_CMP1_REG             S4_MTP_CMP1;                  // 
    union   SENT_S4_MTP_CMP2_REG             S4_MTP_CMP2;                  // 
    union   SENT_S4_MTP_CMP3_REG             S4_MTP_CMP3;                  // 
    union   SENT_S4_MTP_CMP4_REG             S4_MTP_CMP4;                  // 
    union   SENT_S4_MTP_CMP5_REG             S4_MTP_CMP5;                  // 
    union   SENT_S4_MTP_CMP6_REG             S4_MTP_CMP6;                  // 
    union   SENT_S4_MTP_CMP7_REG             S4_MTP_CMP7;                  // 
    union   SENT_S4_MTP_CMP8_REG             S4_MTP_CMP8;                  // 
    union   SENT_S4_MTP_CMP9_REG             S4_MTP_CMP9;                  // 
    union   SENT_S4_MTP_CMP10RE_REG          S4_MTP_CMP10RE;               // 
    union   SENT_S4_MTP_PERIOD_REG           S4_MTP_PERIOD;                // 
    uint32_t                                 S4_MTP_TO;                    // 
    union   SENT_S4_TRIGSEL_REG              S4_TRIGSEL;                   // 
    union   SENT_S4_MTP_SWTR_REG             S4_MTP_SWTR;                  // 
    uint8_t                                  rsvd8[708];                   // Reserved
    union   SENT_WAITTIME_REG                WAITTIME;                     // 
    union   SENT_TPGENSTAT_REG               TPGENSTAT;                    // 
    uint8_t                                  rsvd9[40];                    // Reserved
    uint32_t                                 MTP_VERSION;                  // 
    uint8_t                                  rsvd10[8];                    // Reserved
    union   SENT_MTP_SWR_REG                 MTP_SWR;                      // 
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
