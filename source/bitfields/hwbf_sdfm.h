//###########################################################################
//
// FILE:    hwbf_sdfm.h
//
// TITLE:   Definitions for the SDFM registers.
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

#ifndef HWBF_SDFM_H
#define HWBF_SDFM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// SDFM Individual Register Bit Definitions:

struct SDFM_SDIFLG_BITS {               // bits description
    uint16_t FLT1_FLG_CEVT1:1;          // 0 High-level Interrupt flag for Ch1
    uint16_t FLT1_FLG_CEVT2:1;          // 1 Low-level Interrupt flag for Ch1
    uint16_t FLT2_FLG_CEVT1:1;          // 2 High-level Interrupt flag for Ch2
    uint16_t FLT2_FLG_CEVT2:1;          // 3 Low-level Interrupt flag for Ch2
    uint16_t FLT3_FLG_CEVT1:1;          // 4 High-level Interrupt flag for Ch3
    uint16_t FLT3_FLG_CEVT2:1;          // 5 Low-level Interrupt flag for Ch3
    uint16_t FLT4_FLG_CEVT1:1;          // 6 High-level Interrupt flag for Ch4
    uint16_t FLT4_FLG_CEVT2:1;          // 7 Low-level Interrupt flag for Ch4
    uint16_t MF1:1;                     // 8 Modulator Failure for Filter 1
    uint16_t MF2:1;                     // 9 Modulator Failure for Filter 2
    uint16_t MF3:1;                     // 10 Modulator Failure for Filter 3
    uint16_t MF4:1;                     // 11 Modulator Failure for Filter 4
    uint16_t AF1:1;                     // 12 Acknowledge flag for Filter 1
    uint16_t AF2:1;                     // 13 Acknowledge flag for Filter 2
    uint16_t AF3:1;                     // 14 Acknowledge flag for Filter 3
    uint16_t AF4:1;                     // 15 Acknowledge flag for Filter 4
    uint16_t SDFFOVF1:1;                // 16 FIFO Overflow Flag for Ch1.
    uint16_t SDFFOVF2:1;                // 17 FIFO Overflow Flag for Ch2
    uint16_t SDFFOVF3:1;                // 18 FIFO Overflow Flag for Ch3
    uint16_t SDFFOVF4:1;                // 19 FIFO Overflow Flag for Ch4
    uint16_t SDFFINT1:1;                // 20 SDFIFO interrupt for Ch1
    uint16_t SDFFINT2:1;                // 21 SDFIFO interrupt for Ch2
    uint16_t SDFFINT3:1;                // 22 SDFIFO interrupt for Ch3
    uint16_t SDFFINT4:1;                // 23 SDFIFO interrupt for Ch4
    uint16_t rsvd1:7;                   // 30:24 Reserved
    uint16_t MIF:1;                     // 31 Master Interrupt Flag
};

union SDFM_SDIFLG_REG {
    uint32_t  all;
    struct  SDFM_SDIFLG_BITS  bit;
};

struct SDFM_SDIFLGCLR_BITS {            // bits description
    uint16_t FLT1_FLG_CEVT1:1;          // 0 High-level Interrupt flag for Ch1
    uint16_t FLT1_FLG_CEVT2:1;          // 1 Low-level Interrupt flag for Ch1
    uint16_t FLT2_FLG_CEVT1:1;          // 2 High-level Interrupt flag for Ch2
    uint16_t FLT2_FLG_CEVT2:1;          // 3 Low-level Interrupt flag for Ch2
    uint16_t FLT3_FLG_CEVT1:1;          // 4 High-level Interrupt flag for Ch3
    uint16_t FLT3_FLG_CEVT2:1;          // 5 Low-level Interrupt flag for Ch3
    uint16_t FLT4_FLG_CEVT1:1;          // 6 High-level Interrupt flag for Ch4
    uint16_t FLT4_FLG_CEVT2:1;          // 7 Low-level Interrupt flag for Ch4
    uint16_t MF1:1;                     // 8 Modulator Failure for Filter 1
    uint16_t MF2:1;                     // 9 Modulator Failure for Filter 2
    uint16_t MF3:1;                     // 10 Modulator Failure for Filter 3
    uint16_t MF4:1;                     // 11 Modulator Failure for Filter 4
    uint16_t AF1:1;                     // 12 Acknowledge flag for Filter 1
    uint16_t AF2:1;                     // 13 Acknowledge flag for Filter 2
    uint16_t AF3:1;                     // 14 Acknowledge flag for Filter 3
    uint16_t AF4:1;                     // 15 Acknowledge flag for Filter 4
    uint16_t SDFFOVF1:1;                // 16 SDFIFO overflow clear Ch1
    uint16_t SDFFOVF2:1;                // 17 SDFIFO overflow clear Ch2
    uint16_t SDFFOVF3:1;                // 18 SDFIFO overflow clear Ch3
    uint16_t SDFFOVF4:1;                // 19 SDFIFO overflow clear Ch4
    uint16_t SDFFINT1:1;                // 20 SDFIFO Interrupt flag-clear bit for Ch1
    uint16_t SDFFINT2:1;                // 21 SDFIFO Interrupt flag-clear bit for Ch2
    uint16_t SDFFINT3:1;                // 22 SDFIFO Interrupt flag-clear bit for Ch3
    uint16_t SDFFINT4:1;                // 23 SDFIFO Interrupt flag-clear bit for Ch4
    uint16_t rsvd1:7;                   // 30:24 Reserved
    uint16_t MIF:1;                     // 31 Master Interrupt Flag
};

union SDFM_SDIFLGCLR_REG {
    uint32_t  all;
    struct  SDFM_SDIFLGCLR_BITS  bit;
};

struct SDFM_SDCTL_BITS {                // bits description
    uint16_t HZ1:1;                     // 0 High-level Threshold crossing (Z) flag Ch1
    uint16_t HZ2:1;                     // 1 High-level Threshold crossing (Z) flag Ch2
    uint16_t HZ3:1;                     // 2 High-level Threshold crossing (Z) flag Ch3
    uint16_t HZ4:1;                     // 3 High-level Threshold crossing (Z) flag Ch4
    uint16_t rsvd1:9;                   // 12:4 Reserved
    uint16_t MIE:1;                     // 13 Master SDy_ERR Interrupt enable
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t rsvd3:1;                   // 15 Reserved
};

union SDFM_SDCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCTL_BITS  bit;
};

struct SDFM_SDMFILEN_BITS {             // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t rsvd2:3;                   // 6:4 Reserved
    uint16_t rsvd3:2;                   // 8:7 Reserved
    uint16_t rsvd4:1;                   // 9 Reserved
    uint16_t rsvd5:1;                   // 10 Reserved
    uint16_t MFE:1;                     // 11 Master Filter Enable.
    uint16_t rsvd6:1;                   // 12 Reserved
    uint16_t rsvd7:3;                   // 15:13 Reserved
};

union SDFM_SDMFILEN_REG {
    uint16_t  all;
    struct  SDFM_SDMFILEN_BITS  bit;
};

struct SDFM_SDSTATUS_BITS {             // bits description
    uint16_t HZ1:1;                     // 0 High-level Threshold crossing (Z) flag Ch1
    uint16_t HZ2:1;                     // 1 High-level Threshold crossing (Z) flag Ch2
    uint16_t HZ3:1;                     // 2 High-level Threshold crossing (Z) flag Ch3
    uint16_t HZ4:1;                     // 3 High-level Threshold crossing (Z) flag Ch4
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t rsvd3:1;                   // 9 Reserved
    uint16_t rsvd4:1;                   // 10 Reserved
    uint16_t rsvd5:1;                   // 11 Reserved
    uint16_t rsvd6:1;                   // 12 Reserved
    uint16_t rsvd7:1;                   // 13 Reserved
    uint16_t rsvd8:1;                   // 14 Reserved
    uint16_t rsvd9:1;                   // 15 Reserved
};

union SDFM_SDSTATUS_REG {
    uint16_t  all;
    struct  SDFM_SDSTATUS_BITS  bit;
};

struct SDFM_SDINTMODE_BITS {            // bits description
    uint16_t SDINTMODESEL:1;            // 0 CompxH/L events interrupt mode select
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union SDFM_SDINTMODE_REG {
    uint16_t  all;
    struct  SDFM_SDINTMODE_BITS  bit;
};

struct SDFM_SDCTLPARM1_BITS {           // bits description
    uint16_t MOD:2;                     // 1:0 Modulator clocking modes
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t SDCLKSEL:1;                // 3 SD1 Clock source select.
    uint16_t SDCLKSYNC:1;               // 4 Enable Synchronizer on SD clock
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t SDDATASYNC:1;              // 6 Enable Synchronizer on SD data
    uint16_t rsvd3:1;                   // 7 Reserved
    uint16_t rsvd4:8;                   // 15:8 Reserved
};

union SDFM_SDCTLPARM1_REG {
    uint16_t  all;
    struct  SDFM_SDCTLPARM1_BITS  bit;
};

struct SDFM_SDDFPARM1_BITS {            // bits description
    uint16_t DOSR:8;                    // 7:0 Data Filter Oversample Ratio= DOSR+1
    uint16_t FEN:1;                     // 8 Filter Enable
    uint16_t AE:1;                      // 9 Ack Enable
    uint16_t SST:2;                     // 11:10 Data filter Structure (SincFast/1/2/3)
    uint16_t SDSYNCEN:1;                // 12 Data Filter Reset Enable
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union SDFM_SDDFPARM1_REG {
    uint16_t  all;
    struct  SDFM_SDDFPARM1_BITS  bit;
};

struct SDFM_SDDPARM1_BITS {             // bits description
    uint16_t rsvd1:10;                  // 9:0 Reserved
    uint16_t DR:1;                      // 10 Data Representation (0/1 = 16/32b 2's complement)
    uint16_t SH:5;                      // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDFM_SDDPARM1_REG {
    uint16_t  all;
    struct  SDFM_SDDPARM1_BITS  bit;
};

struct SDFM_SDFLT1CMPH1_BITS {          // bits description
    uint16_t HLT:15;                    // 14:0 High-level threshold for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT1CMPH1_REG {
    uint16_t  all;
    struct  SDFM_SDFLT1CMPH1_BITS  bit;
};

struct SDFM_SDFLT1CMPL1_BITS {          // bits description
    uint16_t LLT:15;                    // 14:0 Low-level threshold for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT1CMPL1_REG {
    uint16_t  all;
    struct  SDFM_SDFLT1CMPL1_BITS  bit;
};

struct SDFM_SDCPARM1_BITS {             // bits description
    uint16_t COSR:5;                    // 4:0 Comparator Oversample Ratio. Actual rate COSR+1
    uint16_t EN_CEVT1:1;                // 5 CEVT1 Interrupt enable.
    uint16_t EN_CEVT2:1;                // 6 CEVT2 Interrupt enable.
    uint16_t CS1_CS0:2;                 // 8:7 Comparator Filter Structure (SincFast/1/2/3)
    uint16_t MFIE:1;                    // 9 Modulator Failure Interrupt enable
    uint16_t HZEN:1;                    // 10 High level (Z) Threshold crossing output enable
    uint16_t CEVT1SEL:2;                // 12:11 Comparator Event1 select
    uint16_t CEN:1;                     // 13 Comparator Enable
    uint16_t CEVT2SEL:2;                // 15:14 Comparator Event2 select
};

union SDFM_SDCPARM1_REG {
    uint16_t  all;
    struct  SDFM_SDCPARM1_BITS  bit;
};

struct SDFM_SDDATA1_BITS {              // bits description
    uint16_t DATA16:16;                 // 15:0 Lo-order 16b in 32b mode
    uint16_t DATA32HI:16;               // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDFM_SDDATA1_REG {
    uint32_t  all;
    struct  SDFM_SDDATA1_BITS  bit;
};

struct SDFM_SDDATFIFO1_BITS {           // bits description
    uint16_t DATA16:16;                 // 15:0 Lo-order 16b in 32b mode
    uint16_t DATA32HI:16;               // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDFM_SDDATFIFO1_REG {
    uint32_t  all;
    struct  SDFM_SDDATFIFO1_BITS  bit;
};

struct SDFM_SDFLT1CMPH2_BITS {          // bits description
    uint16_t HLT2:15;                   // 14:0 Second High level threshold.
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT1CMPH2_REG {
    uint16_t  all;
    struct  SDFM_SDFLT1CMPH2_BITS  bit;
};

struct SDFM_SDFLT1CMPHZ_BITS {          // bits description
    uint16_t HLTZ:15;                   // 14:0 High-level threshold (Z) for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT1CMPHZ_REG {
    uint16_t  all;
    struct  SDFM_SDFLT1CMPHZ_BITS  bit;
};

struct SDFM_SDFIFOCTL1_BITS {           // bits description
    uint16_t SDFFIL:5;                  // 4:0 SDFIFO Interrupt Level
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t SDFFST:5;                  // 10:6 SDFIFO Status
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t FFIEN:1;                   // 12 SDFIFO data ready Interrupt Enable
    uint16_t FFEN:1;                    // 13 SDFIFO Enable
    uint16_t DRINTSEL:1;                // 14 Data-Ready Interrupt Source Select
    uint16_t OVFIEN:1;                  // 15 SDFIFO Overflow interrupt enable
};

union SDFM_SDFIFOCTL1_REG {
    uint16_t  all;
    struct  SDFM_SDFIFOCTL1_BITS  bit;
};

struct SDFM_SDSYNC1_BITS {              // bits description
    uint16_t SYNCSEL:6;                 // 5:0 SDSYNC Source Select
    uint16_t WTSYNCEN:1;                // 6 Wait-for-Sync Enable
    uint16_t WTSYNFLG:1;                // 7 Wait-for-Sync Flag
    uint16_t WTSYNCLR:1;                // 8 Wait-for-Sync Flag Clear
    uint16_t FFSYNCCLREN:1;             // 9 FIFO Clear-on-SDSYNC Enable
    uint16_t WTSCLREN:1;                // 10 WTSYNFLG Clear-on-FIFOINT Enable
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union SDFM_SDSYNC1_REG {
    uint16_t  all;
    struct  SDFM_SDSYNC1_BITS  bit;
};

struct SDFM_SDFLT1CMPL2_BITS {          // bits description
    uint16_t LLT2:15;                   // 14:0 Second low-level threshold for the comparator filter output.
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT1CMPL2_REG {
    uint16_t  all;
    struct  SDFM_SDFLT1CMPL2_BITS  bit;
};

struct SDFM_SDCTLPARM2_BITS {           // bits description
    uint16_t MOD:2;                     // 1:0 Modulator clocking modes
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t SDCLKSEL:1;                // 3 SD2 Clock source select.
    uint16_t SDCLKSYNC:1;               // 4 Enable Synchronizer on SD clock
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t SDDATASYNC:1;              // 6 Enable Synchronizer on SD data
    uint16_t rsvd3:1;                   // 7 Reserved
    uint16_t rsvd4:8;                   // 15:8 Reserved
};

union SDFM_SDCTLPARM2_REG {
    uint16_t  all;
    struct  SDFM_SDCTLPARM2_BITS  bit;
};

struct SDFM_SDDFPARM2_BITS {            // bits description
    uint16_t DOSR:8;                    // 7:0 Data Filter Oversample Ratio= DOSR+1
    uint16_t FEN:1;                     // 8 Filter Enable
    uint16_t AE:1;                      // 9 Ack Enable
    uint16_t SST:2;                     // 11:10 Data filter Structure (SincFast/1/2/3)
    uint16_t SDSYNCEN:1;                // 12 Data Filter Reset Enable
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union SDFM_SDDFPARM2_REG {
    uint16_t  all;
    struct  SDFM_SDDFPARM2_BITS  bit;
};

struct SDFM_SDDPARM2_BITS {             // bits description
    uint16_t rsvd1:10;                  // 9:0 Reserved
    uint16_t DR:1;                      // 10 Data Representation (0/1 = 16/32b 2's complement)
    uint16_t SH:5;                      // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDFM_SDDPARM2_REG {
    uint16_t  all;
    struct  SDFM_SDDPARM2_BITS  bit;
};

struct SDFM_SDFLT2CMPH1_BITS {          // bits description
    uint16_t HLT:15;                    // 14:0 High-level threshold for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT2CMPH1_REG {
    uint16_t  all;
    struct  SDFM_SDFLT2CMPH1_BITS  bit;
};

struct SDFM_SDFLT2CMPL1_BITS {          // bits description
    uint16_t LLT:15;                    // 14:0 Low-level threshold for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT2CMPL1_REG {
    uint16_t  all;
    struct  SDFM_SDFLT2CMPL1_BITS  bit;
};

struct SDFM_SDCPARM2_BITS {             // bits description
    uint16_t COSR:5;                    // 4:0 Comparator Oversample Ratio. Actual rate COSR+1
    uint16_t EN_CEVT1:1;                // 5 CEVT1 Interrupt enable.
    uint16_t EN_CEVT2:1;                // 6 CEVT2 Interrupt enable.
    uint16_t CS1_CS0:2;                 // 8:7 Comparator Filter Structure (SincFast/1/2/3)
    uint16_t MFIE:1;                    // 9 Modulator Failure Interrupt enable
    uint16_t HZEN:1;                    // 10 High level (Z) Threshold crossing output enable
    uint16_t CEVT1SEL:2;                // 12:11 Comparator Event1 select
    uint16_t CEN:1;                     // 13 Comparator Enable
    uint16_t CEVT2SEL:2;                // 15:14 Comparator Event2 select
};

union SDFM_SDCPARM2_REG {
    uint16_t  all;
    struct  SDFM_SDCPARM2_BITS  bit;
};

struct SDFM_SDDATA2_BITS {              // bits description
    uint16_t DATA16:16;                 // 15:0 Lo-order 16b in 32b mode
    uint16_t DATA32HI:16;               // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDFM_SDDATA2_REG {
    uint32_t  all;
    struct  SDFM_SDDATA2_BITS  bit;
};

struct SDFM_SDDATFIFO2_BITS {           // bits description
    uint16_t DATA16:16;                 // 15:0 Lo-order 16b in 32b mode
    uint16_t DATA32HI:16;               // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDFM_SDDATFIFO2_REG {
    uint32_t  all;
    struct  SDFM_SDDATFIFO2_BITS  bit;
};

struct SDFM_SDFLT2CMPH2_BITS {          // bits description
    uint16_t HLT2:15;                   // 14:0 Second High level threshold.
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT2CMPH2_REG {
    uint16_t  all;
    struct  SDFM_SDFLT2CMPH2_BITS  bit;
};

struct SDFM_SDFLT2CMPHZ_BITS {          // bits description
    uint16_t HLTZ:15;                   // 14:0 High-level threshold (Z) for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT2CMPHZ_REG {
    uint16_t  all;
    struct  SDFM_SDFLT2CMPHZ_BITS  bit;
};

struct SDFM_SDFIFOCTL2_BITS {           // bits description
    uint16_t SDFFIL:5;                  // 4:0 SDFIFO Interrupt Level
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t SDFFST:5;                  // 10:6 SDFIFO Status
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t FFIEN:1;                   // 12 SDFIFO data ready Interrupt Enable
    uint16_t FFEN:1;                    // 13 SDFIFO Enable
    uint16_t DRINTSEL:1;                // 14 Data-Ready Interrupt Source Select
    uint16_t OVFIEN:1;                  // 15 SDFIFO Overflow interrupt enable
};

union SDFM_SDFIFOCTL2_REG {
    uint16_t  all;
    struct  SDFM_SDFIFOCTL2_BITS  bit;
};

struct SDFM_SDSYNC2_BITS {              // bits description
    uint16_t SYNCSEL:6;                 // 5:0 SDSYNC Source Select
    uint16_t WTSYNCEN:1;                // 6 Wait-for-Sync Enable
    uint16_t WTSYNFLG:1;                // 7 Wait-for-Sync Flag
    uint16_t WTSYNCLR:1;                // 8 Wait-for-Sync Flag Clear
    uint16_t FFSYNCCLREN:1;             // 9 FIFO Clear-on-SDSYNC Enable
    uint16_t WTSCLREN:1;                // 10 WTSYNFLG Clear-on-FIFOINT Enable
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union SDFM_SDSYNC2_REG {
    uint16_t  all;
    struct  SDFM_SDSYNC2_BITS  bit;
};

struct SDFM_SDFLT2CMPL2_BITS {          // bits description
    uint16_t LLT2:15;                   // 14:0 Second low-level threshold for the comparator filter output.
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT2CMPL2_REG {
    uint16_t  all;
    struct  SDFM_SDFLT2CMPL2_BITS  bit;
};

struct SDFM_SDCTLPARM3_BITS {           // bits description
    uint16_t MOD:2;                     // 1:0 Modulator clocking modes
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t SDCLKSEL:1;                // 3 SD3 Clock source select.
    uint16_t SDCLKSYNC:1;               // 4 Enable Synchronizer on SD clock
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t SDDATASYNC:1;              // 6 Enable Synchronizer on SD data
    uint16_t rsvd3:1;                   // 7 Reserved
    uint16_t rsvd4:8;                   // 15:8 Reserved
};

union SDFM_SDCTLPARM3_REG {
    uint16_t  all;
    struct  SDFM_SDCTLPARM3_BITS  bit;
};

struct SDFM_SDDFPARM3_BITS {            // bits description
    uint16_t DOSR:8;                    // 7:0 Data Filter Oversample Ratio= DOSR+1
    uint16_t FEN:1;                     // 8 Filter Enable
    uint16_t AE:1;                      // 9 Ack Enable
    uint16_t SST:2;                     // 11:10 Data filter Structure (SincFast/1/2/3)
    uint16_t SDSYNCEN:1;                // 12 Data Filter Reset Enable
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union SDFM_SDDFPARM3_REG {
    uint16_t  all;
    struct  SDFM_SDDFPARM3_BITS  bit;
};

struct SDFM_SDDPARM3_BITS {             // bits description
    uint16_t rsvd1:10;                  // 9:0 Reserved
    uint16_t DR:1;                      // 10 Data Representation (0/1 = 16/32b 2's complement)
    uint16_t SH:5;                      // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDFM_SDDPARM3_REG {
    uint16_t  all;
    struct  SDFM_SDDPARM3_BITS  bit;
};

struct SDFM_SDFLT3CMPH1_BITS {          // bits description
    uint16_t HLT:15;                    // 14:0 High-level threshold for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT3CMPH1_REG {
    uint16_t  all;
    struct  SDFM_SDFLT3CMPH1_BITS  bit;
};

struct SDFM_SDFLT3CMPL1_BITS {          // bits description
    uint16_t LLT:15;                    // 14:0 Low-level threshold for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT3CMPL1_REG {
    uint16_t  all;
    struct  SDFM_SDFLT3CMPL1_BITS  bit;
};

struct SDFM_SDCPARM3_BITS {             // bits description
    uint16_t COSR:5;                    // 4:0 Comparator Oversample Ratio. Actual rate COSR+1
    uint16_t EN_CEVT1:1;                // 5 CEVT1 Interrupt enable.
    uint16_t EN_CEVT2:1;                // 6 CEVT2 Interrupt enable.
    uint16_t CS1_CS0:2;                 // 8:7 Comparator Filter Structure (SincFast/1/2/3)
    uint16_t MFIE:1;                    // 9 Modulator Failure Interrupt enable
    uint16_t HZEN:1;                    // 10 High level (Z) Threshold crossing output enable
    uint16_t CEVT1SEL:2;                // 12:11 Comparator Event1 select
    uint16_t CEN:1;                     // 13 Comparator Enable
    uint16_t CEVT2SEL:2;                // 15:14 Comparator Event2 select
};

union SDFM_SDCPARM3_REG {
    uint16_t  all;
    struct  SDFM_SDCPARM3_BITS  bit;
};

struct SDFM_SDDATA3_BITS {              // bits description
    uint16_t DATA16:16;                 // 15:0 Lo-order 16b in 32b mode
    uint16_t DATA32HI:16;               // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDFM_SDDATA3_REG {
    uint32_t  all;
    struct  SDFM_SDDATA3_BITS  bit;
};

struct SDFM_SDDATFIFO3_BITS {           // bits description
    uint16_t DATA16:16;                 // 15:0 Lo-order 16b in 32b mode
    uint16_t DATA32HI:16;               // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDFM_SDDATFIFO3_REG {
    uint32_t  all;
    struct  SDFM_SDDATFIFO3_BITS  bit;
};

struct SDFM_SDFLT3CMPH2_BITS {          // bits description
    uint16_t HLT2:15;                   // 14:0 Second High level threshold.
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT3CMPH2_REG {
    uint16_t  all;
    struct  SDFM_SDFLT3CMPH2_BITS  bit;
};

struct SDFM_SDFLT3CMPHZ_BITS {          // bits description
    uint16_t HLTZ:15;                   // 14:0 High-level threshold (Z) for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT3CMPHZ_REG {
    uint16_t  all;
    struct  SDFM_SDFLT3CMPHZ_BITS  bit;
};

struct SDFM_SDFIFOCTL3_BITS {           // bits description
    uint16_t SDFFIL:5;                  // 4:0 SDFIFO Interrupt Level
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t SDFFST:5;                  // 10:6 SDFIFO Status
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t FFIEN:1;                   // 12 SDFIFO data ready Interrupt Enable
    uint16_t FFEN:1;                    // 13 SDFIFO Enable
    uint16_t DRINTSEL:1;                // 14 Data-Ready Interrupt Source Select
    uint16_t OVFIEN:1;                  // 15 SDFIFO Overflow interrupt enable
};

union SDFM_SDFIFOCTL3_REG {
    uint16_t  all;
    struct  SDFM_SDFIFOCTL3_BITS  bit;
};

struct SDFM_SDSYNC3_BITS {              // bits description
    uint16_t SYNCSEL:6;                 // 5:0 SDSYNC Source Select
    uint16_t WTSYNCEN:1;                // 6 Wait-for-Sync Enable
    uint16_t WTSYNFLG:1;                // 7 Wait-for-Sync Flag
    uint16_t WTSYNCLR:1;                // 8 Wait-for-Sync Flag Clear
    uint16_t FFSYNCCLREN:1;             // 9 FIFO Clear-on-SDSYNC Enable
    uint16_t WTSCLREN:1;                // 10 WTSYNFLG Clear-on-FIFOINT Enable
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union SDFM_SDSYNC3_REG {
    uint16_t  all;
    struct  SDFM_SDSYNC3_BITS  bit;
};

struct SDFM_SDFLT3CMPL2_BITS {          // bits description
    uint16_t LLT2:15;                   // 14:0 Second low-level threshold for the comparator filter output.
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT3CMPL2_REG {
    uint16_t  all;
    struct  SDFM_SDFLT3CMPL2_BITS  bit;
};

struct SDFM_SDCTLPARM4_BITS {           // bits description
    uint16_t MOD:2;                     // 1:0 Modulator clocking modes
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t SDCLKSEL:1;                // 3 SD4 Clock source select.
    uint16_t SDCLKSYNC:1;               // 4 Enable Synchronizer on SD clock
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t SDDATASYNC:1;              // 6 Enable Synchronizer on SD data
    uint16_t rsvd3:1;                   // 7 Reserved
    uint16_t rsvd4:8;                   // 15:8 Reserved
};

union SDFM_SDCTLPARM4_REG {
    uint16_t  all;
    struct  SDFM_SDCTLPARM4_BITS  bit;
};

struct SDFM_SDDFPARM4_BITS {            // bits description
    uint16_t DOSR:8;                    // 7:0 Data Filter Oversample Ratio= DOSR+1
    uint16_t FEN:1;                     // 8 Filter Enable
    uint16_t AE:1;                      // 9 Ack Enable
    uint16_t SST:2;                     // 11:10 Data filter Structure (SincFast/1/2/3)
    uint16_t SDSYNCEN:1;                // 12 Data Filter Reset Enable
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union SDFM_SDDFPARM4_REG {
    uint16_t  all;
    struct  SDFM_SDDFPARM4_BITS  bit;
};

struct SDFM_SDDPARM4_BITS {             // bits description
    uint16_t rsvd1:10;                  // 9:0 Reserved
    uint16_t DR:1;                      // 10 Data Representation (0/1 = 16/32b 2's complement)
    uint16_t SH:5;                      // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDFM_SDDPARM4_REG {
    uint16_t  all;
    struct  SDFM_SDDPARM4_BITS  bit;
};

struct SDFM_SDFLT4CMPH1_BITS {          // bits description
    uint16_t HLT:15;                    // 14:0 High-level threshold for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT4CMPH1_REG {
    uint16_t  all;
    struct  SDFM_SDFLT4CMPH1_BITS  bit;
};

struct SDFM_SDFLT4CMPL1_BITS {          // bits description
    uint16_t LLT:15;                    // 14:0 Low-level threshold for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT4CMPL1_REG {
    uint16_t  all;
    struct  SDFM_SDFLT4CMPL1_BITS  bit;
};

struct SDFM_SDCPARM4_BITS {             // bits description
    uint16_t COSR:5;                    // 4:0 Comparator Oversample Ratio. Actual rate COSR+1
    uint16_t EN_CEVT1:1;                // 5 CEVT1 Interrupt enable.
    uint16_t EN_CEVT2:1;                // 6 CEVT2 Interrupt enable.
    uint16_t CS1_CS0:2;                 // 8:7 Comparator Filter Structure (SincFast/1/2/3)
    uint16_t MFIE:1;                    // 9 Modulator Failure Interrupt enable
    uint16_t HZEN:1;                    // 10 High level (Z) Threshold crossing output enable
    uint16_t CEVT1SEL:2;                // 12:11 Comparator Event1 select
    uint16_t CEN:1;                     // 13 Comparator Enable
    uint16_t CEVT2SEL:2;                // 15:14 Comparator Event2 select
};

union SDFM_SDCPARM4_REG {
    uint16_t  all;
    struct  SDFM_SDCPARM4_BITS  bit;
};

struct SDFM_SDDATA4_BITS {              // bits description
    uint16_t DATA16:16;                 // 15:0 Lo-order 16b in 32b mode
    uint16_t DATA32HI:16;               // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDFM_SDDATA4_REG {
    uint32_t  all;
    struct  SDFM_SDDATA4_BITS  bit;
};

struct SDFM_SDDATFIFO4_BITS {           // bits description
    uint16_t DATA16:16;                 // 15:0 Lo-order 16b in 32b mode
    uint16_t DATA32HI:16;               // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDFM_SDDATFIFO4_REG {
    uint32_t  all;
    struct  SDFM_SDDATFIFO4_BITS  bit;
};

struct SDFM_SDFLT4CMPH2_BITS {          // bits description
    uint16_t HLT2:15;                   // 14:0 Second High level threshold.
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT4CMPH2_REG {
    uint16_t  all;
    struct  SDFM_SDFLT4CMPH2_BITS  bit;
};

struct SDFM_SDFLT4CMPHZ_BITS {          // bits description
    uint16_t HLTZ:15;                   // 14:0 High-level threshold (Z) for the comparator filter output
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT4CMPHZ_REG {
    uint16_t  all;
    struct  SDFM_SDFLT4CMPHZ_BITS  bit;
};

struct SDFM_SDFIFOCTL4_BITS {           // bits description
    uint16_t SDFFIL:5;                  // 4:0 SDFIFO Interrupt Level
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t SDFFST:5;                  // 10:6 SDFIFO Status
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t FFIEN:1;                   // 12 SDFIFO data ready Interrupt Enable
    uint16_t FFEN:1;                    // 13 SDFIFO Enable
    uint16_t DRINTSEL:1;                // 14 Data-Ready Interrupt Source Select
    uint16_t OVFIEN:1;                  // 15 SDFIFO Overflow interrupt enable
};

union SDFM_SDFIFOCTL4_REG {
    uint16_t  all;
    struct  SDFM_SDFIFOCTL4_BITS  bit;
};

struct SDFM_SDSYNC4_BITS {              // bits description
    uint16_t SYNCSEL:6;                 // 5:0 SDSYNC Source Select
    uint16_t WTSYNCEN:1;                // 6 Wait-for-Sync Enable
    uint16_t WTSYNFLG:1;                // 7 Wait-for-Sync Flag
    uint16_t WTSYNCLR:1;                // 8 Wait-for-Sync Flag Clear
    uint16_t FFSYNCCLREN:1;             // 9 FIFO Clear-on-SDSYNC Enable
    uint16_t WTSCLREN:1;                // 10 WTSYNFLG Clear-on-FIFOINT Enable
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union SDFM_SDSYNC4_REG {
    uint16_t  all;
    struct  SDFM_SDSYNC4_BITS  bit;
};

struct SDFM_SDFLT4CMPL2_BITS {          // bits description
    uint16_t LLT2:15;                   // 14:0 Second low-level threshold for the comparator filter output.
    uint16_t rsvd1:1;                   // 15 Reserved
};

union SDFM_SDFLT4CMPL2_REG {
    uint16_t  all;
    struct  SDFM_SDFLT4CMPL2_BITS  bit;
};

struct SDFM_SDCOMP1CTL_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t CEVT1DIGFILTSEL:2;         // 3:2 High Comparator Trip Select
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:1;                   // 6 Reserved
    uint16_t rsvd5:1;                   // 7 Reserved
    uint16_t rsvd6:1;                   // 8 Reserved
    uint16_t rsvd7:1;                   // 9 Reserved
    uint16_t CEVT2DIGFILTSEL:2;         // 11:10 Low Comparator Trip Select
    uint16_t rsvd8:2;                   // 13:12 Reserved
    uint16_t rsvd9:1;                   // 14 Reserved
    uint16_t rsvd10:1;                  // 15 Reserved
};

union SDFM_SDCOMP1CTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP1CTL_BITS  bit;
};

struct SDFM_SDCOMP1EVT2FLTCTL_BITS {    // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t SAMPWIN:5;                 // 8:4 Sample Window
    uint16_t THRESH:5;                  // 13:9 Majority Voting Threshold
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union SDFM_SDCOMP1EVT2FLTCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP1EVT2FLTCTL_BITS  bit;
};

struct SDFM_SDCOMP1EVT2FLTCLKCTL_BITS { // bits description
    uint16_t CLKPRESCALE:10;            // 9:0 Sample Clock Prescale
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union SDFM_SDCOMP1EVT2FLTCLKCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP1EVT2FLTCLKCTL_BITS  bit;
};

struct SDFM_SDCOMP1EVT1FLTCTL_BITS {    // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t SAMPWIN:5;                 // 8:4 Sample Window
    uint16_t THRESH:5;                  // 13:9 Majority Voting Threshold
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union SDFM_SDCOMP1EVT1FLTCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP1EVT1FLTCTL_BITS  bit;
};

struct SDFM_SDCOMP1EVT1FLTCLKCTL_BITS { // bits description
    uint16_t CLKPRESCALE:10;            // 9:0 Sample Clock Prescale
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union SDFM_SDCOMP1EVT1FLTCLKCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP1EVT1FLTCLKCTL_BITS  bit;
};

struct SDFM_SDCOMP1LOCK_BITS {          // bits description
    uint16_t SDCOMP1CTL:1;              // 0 COMPCTL Lock
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:1;                   // 2 Reserved
    uint16_t COMP:1;                    // 3 COMPevent filter registers Lock
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:11;                  // 15:5 Reserved
};

union SDFM_SDCOMP1LOCK_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP1LOCK_BITS  bit;
};

struct SDFM_SDCOMP2CTL_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t CEVT1DIGFILTSEL:2;         // 3:2 High Comparator Trip Select
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:1;                   // 6 Reserved
    uint16_t rsvd5:1;                   // 7 Reserved
    uint16_t rsvd6:1;                   // 8 Reserved
    uint16_t rsvd7:1;                   // 9 Reserved
    uint16_t CEVT2DIGFILTSEL:2;         // 11:10 Low Comparator Trip Select
    uint16_t rsvd8:2;                   // 13:12 Reserved
    uint16_t rsvd9:1;                   // 14 Reserved
    uint16_t rsvd10:1;                  // 15 Reserved
};

union SDFM_SDCOMP2CTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP2CTL_BITS  bit;
};

struct SDFM_SDCOMP2EVT2FLTCTL_BITS {    // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t SAMPWIN:5;                 // 8:4 Sample Window
    uint16_t THRESH:5;                  // 13:9 Majority Voting Threshold
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union SDFM_SDCOMP2EVT2FLTCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP2EVT2FLTCTL_BITS  bit;
};

struct SDFM_SDCOMP2EVT2FLTCLKCTL_BITS { // bits description
    uint16_t CLKPRESCALE:10;            // 9:0 Sample Clock Prescale
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union SDFM_SDCOMP2EVT2FLTCLKCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP2EVT2FLTCLKCTL_BITS  bit;
};

struct SDFM_SDCOMP2EVT1FLTCTL_BITS {    // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t SAMPWIN:5;                 // 8:4 Sample Window
    uint16_t THRESH:5;                  // 13:9 Majority Voting Threshold
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union SDFM_SDCOMP2EVT1FLTCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP2EVT1FLTCTL_BITS  bit;
};

struct SDFM_SDCOMP2EVT1FLTCLKCTL_BITS { // bits description
    uint16_t CLKPRESCALE:10;            // 9:0 Sample Clock Prescale
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union SDFM_SDCOMP2EVT1FLTCLKCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP2EVT1FLTCLKCTL_BITS  bit;
};

struct SDFM_SDCOMP2LOCK_BITS {          // bits description
    uint16_t SDCOMP2CTL:1;              // 0 COMPCTL Lock
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:1;                   // 2 Reserved
    uint16_t COMP:1;                    // 3 COMPevent filter registers Lock
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:11;                  // 15:5 Reserved
};

union SDFM_SDCOMP2LOCK_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP2LOCK_BITS  bit;
};

struct SDFM_SDCOMP3CTL_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t CEVT1DIGFILTSEL:2;         // 3:2 High Comparator Trip Select
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:1;                   // 6 Reserved
    uint16_t rsvd5:1;                   // 7 Reserved
    uint16_t rsvd6:1;                   // 8 Reserved
    uint16_t rsvd7:1;                   // 9 Reserved
    uint16_t CEVT2DIGFILTSEL:2;         // 11:10 Low Comparator Trip Select
    uint16_t rsvd8:2;                   // 13:12 Reserved
    uint16_t rsvd9:1;                   // 14 Reserved
    uint16_t rsvd10:1;                  // 15 Reserved
};

union SDFM_SDCOMP3CTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP3CTL_BITS  bit;
};

struct SDFM_SDCOMP3EVT2FLTCTL_BITS {    // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t SAMPWIN:5;                 // 8:4 Sample Window
    uint16_t THRESH:5;                  // 13:9 Majority Voting Threshold
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union SDFM_SDCOMP3EVT2FLTCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP3EVT2FLTCTL_BITS  bit;
};

struct SDFM_SDCOMP3EVT2FLTCLKCTL_BITS { // bits description
    uint16_t CLKPRESCALE:10;            // 9:0 Sample Clock Prescale
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union SDFM_SDCOMP3EVT2FLTCLKCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP3EVT2FLTCLKCTL_BITS  bit;
};

struct SDFM_SDCOMP3EVT1FLTCTL_BITS {    // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t SAMPWIN:5;                 // 8:4 Sample Window
    uint16_t THRESH:5;                  // 13:9 Majority Voting Threshold
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union SDFM_SDCOMP3EVT1FLTCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP3EVT1FLTCTL_BITS  bit;
};

struct SDFM_SDCOMP3EVT1FLTCLKCTL_BITS { // bits description
    uint16_t CLKPRESCALE:10;            // 9:0 Sample Clock Prescale
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union SDFM_SDCOMP3EVT1FLTCLKCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP3EVT1FLTCLKCTL_BITS  bit;
};

struct SDFM_SDCOMP3LOCK_BITS {          // bits description
    uint16_t SDCOMP3CTL:1;              // 0 COMPCTL Lock
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:1;                   // 2 Reserved
    uint16_t COMP:1;                    // 3 COMPevent filter registers Lock
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:11;                  // 15:5 Reserved
};

union SDFM_SDCOMP3LOCK_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP3LOCK_BITS  bit;
};

struct SDFM_SDCOMP4CTL_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t CEVT1DIGFILTSEL:2;         // 3:2 High Comparator Trip Select
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:1;                   // 6 Reserved
    uint16_t rsvd5:1;                   // 7 Reserved
    uint16_t rsvd6:1;                   // 8 Reserved
    uint16_t rsvd7:1;                   // 9 Reserved
    uint16_t CEVT2DIGFILTSEL:2;         // 11:10 Low Comparator Trip Select
    uint16_t rsvd8:2;                   // 13:12 Reserved
    uint16_t rsvd9:1;                   // 14 Reserved
    uint16_t rsvd10:1;                  // 15 Reserved
};

union SDFM_SDCOMP4CTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP4CTL_BITS  bit;
};

struct SDFM_SDCOMP4EVT2FLTCTL_BITS {    // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t SAMPWIN:5;                 // 8:4 Sample Window
    uint16_t THRESH:5;                  // 13:9 Majority Voting Threshold
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union SDFM_SDCOMP4EVT2FLTCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP4EVT2FLTCTL_BITS  bit;
};

struct SDFM_SDCOMP4EVT2FLTCLKCTL_BITS { // bits description
    uint16_t CLKPRESCALE:10;            // 9:0 Sample Clock Prescale
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union SDFM_SDCOMP4EVT2FLTCLKCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP4EVT2FLTCLKCTL_BITS  bit;
};

struct SDFM_SDCOMP4EVT1FLTCTL_BITS {    // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t SAMPWIN:5;                 // 8:4 Sample Window
    uint16_t THRESH:5;                  // 13:9 Majority Voting Threshold
    uint16_t rsvd2:1;                   // 14 Reserved
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union SDFM_SDCOMP4EVT1FLTCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP4EVT1FLTCTL_BITS  bit;
};

struct SDFM_SDCOMP4EVT1FLTCLKCTL_BITS { // bits description
    uint16_t CLKPRESCALE:10;            // 9:0 Sample Clock Prescale
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union SDFM_SDCOMP4EVT1FLTCLKCTL_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP4EVT1FLTCLKCTL_BITS  bit;
};

struct SDFM_SDCOMP4LOCK_BITS {          // bits description
    uint16_t SDCOMP4CTL:1;              // 0 COMPCTL Lock
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:1;                   // 2 Reserved
    uint16_t COMP:1;                    // 3 COMPevent filter registers Lock
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:11;                  // 15:5 Reserved
};

union SDFM_SDCOMP4LOCK_REG {
    uint16_t  all;
    struct  SDFM_SDCOMP4LOCK_BITS  bit;
};

struct SDFM_REGS {
    union   SDFM_SDIFLG_REG                  SDIFLG;                       // SD Interrupt Flag Register
    union   SDFM_SDIFLGCLR_REG               SDIFLGCLR;                    // SD Interrupt Flag Clear Register
    union   SDFM_SDCTL_REG                   SDCTL;                        // SD Control Register
    uint8_t                                  rsvd1[2];                     // Reserved
    union   SDFM_SDMFILEN_REG                SDMFILEN;                     // SD Master Filter Enable
    union   SDFM_SDSTATUS_REG                SDSTATUS;                     // SD Status Register
    union   SDFM_SDINTMODE_REG               SDINTMODE;                    // SD Interrupt Mode register
    uint8_t                                  rsvd2[14];                    // Reserved
    union   SDFM_SDCTLPARM1_REG              SDCTLPARM1;                   // Control Parameter Register for Ch1
    union   SDFM_SDDFPARM1_REG               SDDFPARM1;                    // Data Filter Parameter Register for Ch1
    union   SDFM_SDDPARM1_REG                SDDPARM1;                     // Data Parameter Register for Ch1
    union   SDFM_SDFLT1CMPH1_REG             SDFLT1CMPH1;                  // High-level Threshold Register for Ch1
    union   SDFM_SDFLT1CMPL1_REG             SDFLT1CMPL1;                  // Low-level Threshold Register for Ch1
    union   SDFM_SDCPARM1_REG                SDCPARM1;                     // Comparator Filter Parameter Register for Ch1
    union   SDFM_SDDATA1_REG                 SDDATA1;                      // Data Filter Data Register (16 or 32bit) for Ch1
    union   SDFM_SDDATFIFO1_REG              SDDATFIFO1;                   // Filter Data FIFO Output(32b) for Ch1
    uint16_t                                 SDCDATA1;                     // Comparator Filter Data Register (16b) for Ch1
    union   SDFM_SDFLT1CMPH2_REG             SDFLT1CMPH2;                  // Second high level threhold  for CH1
    union   SDFM_SDFLT1CMPHZ_REG             SDFLT1CMPHZ;                  // High-level (Z) Threshold Register for Ch1
    union   SDFM_SDFIFOCTL1_REG              SDFIFOCTL1;                   // FIFO Control Register for Ch1
    union   SDFM_SDSYNC1_REG                 SDSYNC1;                      // SD Filter Sync control for Ch1
    union   SDFM_SDFLT1CMPL2_REG             SDFLT1CMPL2;                  // Second low level threhold  for CH1
    union   SDFM_SDCTLPARM2_REG              SDCTLPARM2;                   // Control Parameter Register for Ch2
    union   SDFM_SDDFPARM2_REG               SDDFPARM2;                    // Data Filter Parameter Register for Ch2
    union   SDFM_SDDPARM2_REG                SDDPARM2;                     // Data Parameter Register for Ch2
    union   SDFM_SDFLT2CMPH1_REG             SDFLT2CMPH1;                  // High-level Threshold Register for Ch2
    union   SDFM_SDFLT2CMPL1_REG             SDFLT2CMPL1;                  // Low-level Threshold Register for Ch2
    union   SDFM_SDCPARM2_REG                SDCPARM2;                     // Comparator Filter Parameter Register for Ch2
    union   SDFM_SDDATA2_REG                 SDDATA2;                      // Data Filter Data Register (16 or 32bit) for Ch2
    union   SDFM_SDDATFIFO2_REG              SDDATFIFO2;                   // Filter Data FIFO Output(32b) for Ch2
    uint16_t                                 SDCDATA2;                     // Comparator Filter Data Register (16b) for Ch2
    union   SDFM_SDFLT2CMPH2_REG             SDFLT2CMPH2;                  // Second high level threhold  for CH2
    union   SDFM_SDFLT2CMPHZ_REG             SDFLT2CMPHZ;                  // High-level (Z) Threshold Register for Ch2
    union   SDFM_SDFIFOCTL2_REG              SDFIFOCTL2;                   // FIFO Control Register for Ch2
    union   SDFM_SDSYNC2_REG                 SDSYNC2;                      // SD Filter Sync control for Ch2
    union   SDFM_SDFLT2CMPL2_REG             SDFLT2CMPL2;                  // Second low level threhold  for CH2
    union   SDFM_SDCTLPARM3_REG              SDCTLPARM3;                   // Control Parameter Register for Ch3
    union   SDFM_SDDFPARM3_REG               SDDFPARM3;                    // Data Filter Parameter Register for Ch3
    union   SDFM_SDDPARM3_REG                SDDPARM3;                     // Data Parameter Register for Ch3
    union   SDFM_SDFLT3CMPH1_REG             SDFLT3CMPH1;                  // High-level Threshold Register for Ch3
    union   SDFM_SDFLT3CMPL1_REG             SDFLT3CMPL1;                  // Low-level Threshold Register for Ch3
    union   SDFM_SDCPARM3_REG                SDCPARM3;                     // Comparator Filter Parameter Register for Ch3
    union   SDFM_SDDATA3_REG                 SDDATA3;                      // Data Filter Data Register (16 or 32bit) for Ch3
    union   SDFM_SDDATFIFO3_REG              SDDATFIFO3;                   // Filter Data FIFO Output(32b) for Ch3
    uint16_t                                 SDCDATA3;                     // Comparator Filter Data Register (16b) for Ch3
    union   SDFM_SDFLT3CMPH2_REG             SDFLT3CMPH2;                  // Second high level threhold  for CH3
    union   SDFM_SDFLT3CMPHZ_REG             SDFLT3CMPHZ;                  // High-level (Z) Threshold Register for Ch3
    union   SDFM_SDFIFOCTL3_REG              SDFIFOCTL3;                   // FIFO Control Register for Ch3
    union   SDFM_SDSYNC3_REG                 SDSYNC3;                      // SD Filter Sync control for Ch3
    union   SDFM_SDFLT3CMPL2_REG             SDFLT3CMPL2;                  // Second low level threhold  for CH3
    union   SDFM_SDCTLPARM4_REG              SDCTLPARM4;                   // Control Parameter Register for Ch4
    union   SDFM_SDDFPARM4_REG               SDDFPARM4;                    // Data Filter Parameter Register for Ch4
    union   SDFM_SDDPARM4_REG                SDDPARM4;                     // Data Parameter Register for Ch4
    union   SDFM_SDFLT4CMPH1_REG             SDFLT4CMPH1;                  // High-level Threshold Register for Ch4
    union   SDFM_SDFLT4CMPL1_REG             SDFLT4CMPL1;                  // Low-level Threshold Register for Ch4
    union   SDFM_SDCPARM4_REG                SDCPARM4;                     // Comparator Filter Parameter Register for Ch4
    union   SDFM_SDDATA4_REG                 SDDATA4;                      // Data Filter Data Register (16 or 32bit) for Ch4
    union   SDFM_SDDATFIFO4_REG              SDDATFIFO4;                   // Filter Data FIFO Output(32b) for Ch4
    uint16_t                                 SDCDATA4;                     // Comparator Filter Data Register (16b) for Ch4
    union   SDFM_SDFLT4CMPH2_REG             SDFLT4CMPH2;                  // Second high level threhold  for CH4
    union   SDFM_SDFLT4CMPHZ_REG             SDFLT4CMPHZ;                  // High-level (Z) Threshold Register for Ch4
    union   SDFM_SDFIFOCTL4_REG              SDFIFOCTL4;                   // FIFO Control Register for Ch4
    union   SDFM_SDSYNC4_REG                 SDSYNC4;                      // SD Filter Sync control for Ch4
    union   SDFM_SDFLT4CMPL2_REG             SDFLT4CMPL2;                  // Second low level threhold  for CH4
    uint8_t                                  rsvd3[32];                    // Reserved
    union   SDFM_SDCOMP1CTL_REG              SDCOMP1CTL;                   // SD Comparator event filter1 Control Register
    union   SDFM_SDCOMP1EVT2FLTCTL_REG       SDCOMP1EVT2FLTCTL;            // COMPL/CEVT2 Digital filter1 Control Register
    union   SDFM_SDCOMP1EVT2FLTCLKCTL_REG    SDCOMP1EVT2FLTCLKCTL;         // COMPL/CEVT2 Digital filter1 Clock Control Register
    union   SDFM_SDCOMP1EVT1FLTCTL_REG       SDCOMP1EVT1FLTCTL;            // COMPH/CEVT1 Digital filter1 Control Register
    union   SDFM_SDCOMP1EVT1FLTCLKCTL_REG    SDCOMP1EVT1FLTCLKCTL;         // COMPH/CEVT1 Digital filter1 Clock Control Register
    uint8_t                                  rsvd4[4];                     // Reserved
    union   SDFM_SDCOMP1LOCK_REG             SDCOMP1LOCK;                  // SD  compartor event filter1 Lock Register
    union   SDFM_SDCOMP2CTL_REG              SDCOMP2CTL;                   // SD Comparator event filter2 Control Register
    union   SDFM_SDCOMP2EVT2FLTCTL_REG       SDCOMP2EVT2FLTCTL;            // COMPL/CEVT2 Digital filter2 Control Register
    union   SDFM_SDCOMP2EVT2FLTCLKCTL_REG    SDCOMP2EVT2FLTCLKCTL;         // COMPL/CEVT2 Digital filter2 Clock Control Register
    union   SDFM_SDCOMP2EVT1FLTCTL_REG       SDCOMP2EVT1FLTCTL;            // COMPH/CEVT1 Digital filter2 Control Register
    union   SDFM_SDCOMP2EVT1FLTCLKCTL_REG    SDCOMP2EVT1FLTCLKCTL;         // COMPH/CEVT1 Digital filter2 Clock Control Register
    uint8_t                                  rsvd5[4];                     // Reserved
    union   SDFM_SDCOMP2LOCK_REG             SDCOMP2LOCK;                  // SD  compartor event filter2 Lock Register
    union   SDFM_SDCOMP3CTL_REG              SDCOMP3CTL;                   // SD Comparator event filter3 Control Register
    union   SDFM_SDCOMP3EVT2FLTCTL_REG       SDCOMP3EVT2FLTCTL;            // COMPL/CEVT2 Digital filter3 Control Register
    union   SDFM_SDCOMP3EVT2FLTCLKCTL_REG    SDCOMP3EVT2FLTCLKCTL;         // COMPL/CEVT2 Digital filter3 Clock Control Register
    union   SDFM_SDCOMP3EVT1FLTCTL_REG       SDCOMP3EVT1FLTCTL;            // COMPH/CEVT1 Digital filter3 Control Register
    union   SDFM_SDCOMP3EVT1FLTCLKCTL_REG    SDCOMP3EVT1FLTCLKCTL;         // COMPH/CEVT1 Digital filter3 Clock Control Register
    uint8_t                                  rsvd6[4];                     // Reserved
    union   SDFM_SDCOMP3LOCK_REG             SDCOMP3LOCK;                  // SD  compartor event filter3 Lock Register
    union   SDFM_SDCOMP4CTL_REG              SDCOMP4CTL;                   // SD Comparator event filter4 Control Register
    union   SDFM_SDCOMP4EVT2FLTCTL_REG       SDCOMP4EVT2FLTCTL;            // COMPL/CEVT2 Digital filter4 Control Register
    union   SDFM_SDCOMP4EVT2FLTCLKCTL_REG    SDCOMP4EVT2FLTCLKCTL;         // COMPL/CEVT2 Digital filter4 Clock Control Register
    union   SDFM_SDCOMP4EVT1FLTCTL_REG       SDCOMP4EVT1FLTCTL;            // COMPH/CEVT1 Digital filter4 Control Register
    union   SDFM_SDCOMP4EVT1FLTCLKCTL_REG    SDCOMP4EVT1FLTCLKCTL;         // COMPH/CEVT1 Digital filter4 Clock Control Register
    uint8_t                                  rsvd7[4];                     // Reserved
    union   SDFM_SDCOMP4LOCK_REG             SDCOMP4LOCK;                  // SD  compartor event filter4 Lock Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
