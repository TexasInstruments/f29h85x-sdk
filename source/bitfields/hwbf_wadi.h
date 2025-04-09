//###########################################################################
//
// FILE:    hwbf_wadi.h
//
// TITLE:   Definitions for the WADI registers.
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

#ifndef HWBF_WADI_H
#define HWBF_WADI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// WADI Individual Register Bit Definitions:

struct WADI_BLKCFG_BITS {               // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t CLKEN:1;                   // 4 Enables clock for WADI block
    uint16_t rsvd3:3;                   // 7:5 Reserved
    uint16_t SIG1IN:5;                  // 12:8 Selects the input signal for the SIG1 input of WADI block
    uint16_t rsvd4:3;                   // 15:13 Reserved
    uint16_t SIG2IN:5;                  // 20:16 Selects the input signal for the SIG2 input of WADI block
    uint16_t rsvd5:3;                   // 23:21 Reserved
    uint16_t TRIG1IN:4;                 // 27:24 Selects trigger input signal for SIG1 analysis
    uint16_t TRIG2IN:4;                 // 31:28 Selects  trigger input signal for SIG2 analysis
};

union WADI_BLKCFG_REG {
    uint32_t  all;
    struct  WADI_BLKCFG_BITS  bit;
};

struct WADI_SIGTOSIGCFG_BITS {          // bits description
    uint16_t CMP:16;                    // 15:0 Compare value for difference of width/sum measurement
    uint16_t CMPMARGIN:4;               // 19:16 Margin of error for difference of width/sum measurement
    uint16_t rsvd1:4;                   // 23:20 Reserved
    uint16_t SIGTOSIG_CMPEN:1;          // 24 Enables the signal to signal compare
    uint16_t rsvd2:1;                   // 25 Reserved
    uint16_t SIGTOSIG_DBCMPEN:1;        // 26 Enables the deadband check between two signals
    uint16_t SIGTOSIG_OLAPCMPEN:1;      // 27 Enables the overlap check between two signals
    uint16_t DBCMPTYPE:1;               // 28 Selects the check type for deadband control
    uint16_t OLAPCMPTYPE:1;             // 29 Selects the check type for overlap control
    uint16_t rsvd3:2;                   // 31:30 Reserved
};

union WADI_SIGTOSIGCFG_REG {
    uint32_t  all;
    struct  WADI_SIGTOSIGCFG_BITS  bit;
};

struct WADI_SIGTOSIG_PKCFG_BITS {       // bits description
    uint32_t PKCMP:24;                  // 23:0 Compare value for difference of peak measurement
    uint16_t PKCMPMARGIN:8;             // 31:24 Margin of error for difference of peak measurement
};

union WADI_SIGTOSIG_PKCFG_REG {
    uint32_t  all;
    struct  WADI_SIGTOSIG_PKCFG_BITS  bit;
};

struct WADI_SIGTOSIG_AVGCFG_BITS {      // bits description
    uint32_t AVGCMP:24;                 // 23:0 Compare difference for measurements average of both signals
    uint16_t AVGCMPMARGIN:8;            // 31:24 Margin for difference of average of both signals
};

union WADI_SIGTOSIG_AVGCFG_REG {
    uint32_t  all;
    struct  WADI_SIGTOSIG_AVGCFG_BITS  bit;
};

struct WADI_SIGTOSIG_DBOLAPA_BITS {     // bits description
    uint16_t DBCMPA:8;                  // 7:0 Compare value for dead-band between both signals
    uint32_t OLAPCMPA:16;               // 23:8 Compare value for Overlap between both signal levels
    uint16_t OLAPCMPAMARGIN:6;          // 29:24 Margin of variation of overlap between both signals
    uint16_t rsvd1:2;                   // 31:30 Reserved
};

union WADI_SIGTOSIG_DBOLAPA_REG {
    uint32_t  all;
    struct  WADI_SIGTOSIG_DBOLAPA_BITS  bit;
};

struct WADI_SIGTOSIG_DBOLAPB_BITS {     // bits description
    uint16_t DBCMPB:8;                  // 7:0 Compare value for dead-band between both signals
    uint32_t OLAPCMPB:16;               // 23:8 Compare value for Overlap between both signal levels
    uint16_t OLAPCMPBMARGIN:6;          // 29:24 Margin of variation of overlap between both signals
    uint16_t rsvd1:2;                   // 31:30 Reserved
};

union WADI_SIGTOSIG_DBOLAPB_REG {
    uint32_t  all;
    struct  WADI_SIGTOSIG_DBOLAPB_BITS  bit;
};

struct WADI_BLKTRIGCFG_BITS {           // bits description
    uint16_t TRIG1TYPE:3;               // 2:0 The trigger type for SIG1 signal input.
    uint16_t rsvd1:5;                   // 7:3 Reserved
    uint16_t TRIG1SWEN:1;               // 8 Software trigger for the SIG1
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t TRIG2TYPE:3;               // 18:16 The trigger type for SIG2 signal input.
    uint16_t rsvd3:5;                   // 23:19 Reserved
    uint16_t TRIG2SWEN:1;               // 24 Software trigger for the SIG2
    uint16_t rsvd4:7;                   // 31:25 Reserved
};

union WADI_BLKTRIGCFG_REG {
    uint32_t  all;
    struct  WADI_BLKTRIGCFG_BITS  bit;
};

struct WADI_SIG1CFG_BITS {              // bits description
    uint16_t SIGPOL:2;                  // 1:0 Starting edge select as rise, fall or either
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t EDGESPAN:4;                // 11:8 Defines span of edges of given type to measure the width.
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t NUMAGGR:3;                 // 18:16 Defines number of measurements to be aggregated
    uint16_t rsvd3:5;                   // 23:19 Reserved
    uint16_t AGGRMODE:2;                // 25:24 Whether peak or average or both measurements to compute
    uint16_t rsvd4:6;                   // 31:26 Reserved
};

union WADI_SIG1CFG_REG {
    uint32_t  all;
    struct  WADI_SIG1CFG_BITS  bit;
};

struct WADI_SIG1CMPA_BITS {             // bits description
    uint32_t CMPA:24;                   // 23:0 Compare A value for measured count of the SIG1
    uint16_t CMPAMARGIN:8;              // 31:24 +/- Margin for compare-1 around SIG1CMPA[CMPA]
};

union WADI_SIG1CMPA_REG {
    uint32_t  all;
    struct  WADI_SIG1CMPA_BITS  bit;
};

struct WADI_SIG1CMPB_BITS {             // bits description
    uint32_t CMPB:24;                   // 23:0 Compare B value for measured count of the SIG1
    uint16_t CMPBMARGIN:8;              // 31:24 +/- Margin for compare B around SIG1CMPB[CMPB]
};

union WADI_SIG1CMPB_REG {
    uint32_t  all;
    struct  WADI_SIG1CMPB_BITS  bit;
};

struct WADI_SIG1PKCFG_BITS {            // bits description
    uint32_t CMP:24;                    // 23:0 Compare value for peak measurements of SIG1
    uint16_t CMPMARGIN:8;               // 31:24 Margin of variation for peak measurements of SIG1
};

union WADI_SIG1PKCFG_REG {
    uint32_t  all;
    struct  WADI_SIG1PKCFG_BITS  bit;
};

struct WADI_SIG1AVGCFG_BITS {           // bits description
    uint32_t CMP:24;                    // 23:0 Compare value for average of measurements of SIG1
    uint16_t CMPMARGIN:8;               // 31:24 Margin for average of measurements of SIG1
};

union WADI_SIG1AVGCFG_REG {
    uint32_t  all;
    struct  WADI_SIG1AVGCFG_BITS  bit;
};

struct WADI_SIG1EDGECFG_BITS {          // bits description
    uint32_t TIMEWNDOW:28;              // 27:0 Time window to count edges of SIG1
    uint16_t rsvd1:3;                   // 30:28 Reserved
    uint16_t CNTEN:1;                   // 31 SIG1 Edge count mode enable
};

union WADI_SIG1EDGECFG_REG {
    uint32_t  all;
    struct  WADI_SIG1EDGECFG_BITS  bit;
};

struct WADI_SIG1EDGEMVWCFG_BITS {       // bits description
    uint32_t MVWTIME:26;                // 25:0 Moving Window time
    uint16_t rsvd1:2;                   // 27:26 Reserved
    uint16_t MVWCNT:2;                  // 29:28 Moving window count:number of MWVTIME windows to accumulate
    uint16_t rsvd2:1;                   // 30 Reserved
    uint16_t MVWEN:1;                   // 31 Moving window operation enable
};

union WADI_SIG1EDGEMVWCFG_REG {
    uint32_t  all;
    struct  WADI_SIG1EDGEMVWCFG_BITS  bit;
};

struct WADI_SIG2CFG_BITS {              // bits description
    uint16_t SIGPOL:2;                  // 1:0 Starting edge select as rise, fall or either
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t EDGESPAN:4;                // 11:8 Defines span of edges of given type to measure the width.
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t NUMAGGR:3;                 // 18:16 Defines number of measurements to be aggregated
    uint16_t rsvd3:5;                   // 23:19 Reserved
    uint16_t AGGRMODE:2;                // 25:24 Whether peak or average or both measurements to compute
    uint16_t rsvd4:6;                   // 31:26 Reserved
};

union WADI_SIG2CFG_REG {
    uint32_t  all;
    struct  WADI_SIG2CFG_BITS  bit;
};

struct WADI_SIG2CMPA_BITS {             // bits description
    uint32_t CMPA:24;                   // 23:0 Compare A value for measured count of the SIG2
    uint16_t CMPAMARGIN:8;              // 31:24 +/- Margin for compare-1 around SIG2CMPA[CMPA]
};

union WADI_SIG2CMPA_REG {
    uint32_t  all;
    struct  WADI_SIG2CMPA_BITS  bit;
};

struct WADI_SIG2CMPB_BITS {             // bits description
    uint32_t CMPB:24;                   // 23:0 Compare B value for measured count of the SIG2
    uint16_t CMPBMARGIN:8;              // 31:24 +/- Margin for compare B around SIG2CMPB[CMPB]
};

union WADI_SIG2CMPB_REG {
    uint32_t  all;
    struct  WADI_SIG2CMPB_BITS  bit;
};

struct WADI_SIG2PKCFG_BITS {            // bits description
    uint32_t CMP:24;                    // 23:0 Compare value for peak measurements of SIG2
    uint16_t CMPMARGIN:8;               // 31:24 Margin of variation for peak measurements of SIG2
};

union WADI_SIG2PKCFG_REG {
    uint32_t  all;
    struct  WADI_SIG2PKCFG_BITS  bit;
};

struct WADI_SIG2AVGCFG_BITS {           // bits description
    uint32_t CMP:24;                    // 23:0 Compare value for average of measurements of SIG2
    uint16_t CMPMARGIN:8;               // 31:24 Margin for average of measurements of SIG2
};

union WADI_SIG2AVGCFG_REG {
    uint32_t  all;
    struct  WADI_SIG2AVGCFG_BITS  bit;
};

struct WADI_SIG2EDGECFG_BITS {          // bits description
    uint32_t TIMEWNDOW:28;              // 27:0 Time window to count edges of SIG2
    uint16_t rsvd1:3;                   // 30:28 Reserved
    uint16_t CNTEN:1;                   // 31 SIG2 Edge count mode enable
};

union WADI_SIG2EDGECFG_REG {
    uint32_t  all;
    struct  WADI_SIG2EDGECFG_BITS  bit;
};

struct WADI_SIG2EDGEMVWCFG_BITS {       // bits description
    uint32_t MVWTIME:26;                // 25:0 Moving Window time
    uint16_t rsvd1:2;                   // 27:26 Reserved
    uint16_t MVWCNT:2;                  // 29:28 Moving window count:number of MWVTIME windows to accumulate
    uint16_t rsvd2:1;                   // 30 Reserved
    uint16_t MVWEN:1;                   // 31 Moving window operation enable
};

union WADI_SIG2EDGEMVWCFG_REG {
    uint32_t  all;
    struct  WADI_SIG2EDGEMVWCFG_BITS  bit;
};

struct WADI_BLKERRSTS_BITS {            // bits description
    uint16_t SIG1CMPAERR:2;             // 1:0 Compare A margin error for the SIG1 measurements
    uint16_t SIG1PKERR:2;               // 3:2 Error of SIG1 peak measurements
    uint16_t SIG1AVGERR:2;              // 5:4 Average of aggregation error for the SIG1 measurements
    uint16_t SIG1CMPBERR:2;             // 7:6 Compare B margin error for the SIG1 measurements
    uint16_t SIG2CMPAERR:2;             // 9:8 Compare A margin error for the SIG2 measurements
    uint16_t SIG2PKERR:2;               // 11:10 Error of SIG2 peak measurements
    uint16_t SIG2AVGERR:2;              // 13:12 Average of aggregation error for the SIG2 measurements
    uint16_t SIG2CMPBERR:2;             // 15:14 Compare B margin error for the SIG2 measurements
    uint16_t SIGTOSIG_CMPERR:2;         // 17:16 Compare error for the SIGTOSIG measurements difference
    uint16_t SIGTOSIG_PKERR:2;          // 19:18 Error of SIGTOSIG peak measurements difference
    uint16_t SIGTOSIG_AVGERR:2;         // 21:20 Average error for the SIGTOSIG measurements difference
    uint16_t SIGTOSIG_DBCMPAERR:1;      // 22 Deadband Compare A error for the SIGTOSIG measurements
    uint16_t SIGTOSIG_DBCMPBERR:1;      // 23 Deadband Compare B Error for the SIGTOSIG measurements
    uint16_t SIGTOSIG_OLAPCMPAERR:2;    // 25:24 Overlap check Compare A error of SIGTOSIG measurements
    uint16_t SIGTOSIG_OLAPCMPBERR:2;    // 27:26 Overlap check Compare B error of SIGTOSIG measurements
    uint16_t rsvd1:2;                   // 29:28 Reserved
    uint16_t SIG_ERR:1;                 // 30 Measurement error of unexpected waveform anomaly
    uint16_t SIGTOSIG_ERR:1;            // 31 Mismatch in number of readings between signals
};

union WADI_BLKERRSTS_REG {
    uint32_t  all;
    struct  WADI_BLKERRSTS_BITS  bit;
};

struct WADI_BLKERRINFO_BITS {           // bits description
    uint32_t ERRCNT:25;                 // 24:0 First failed count of SIGx multiplexed  to this register
    uint16_t rsvd1:3;                   // 27:25 Reserved
    uint16_t ERRTYPE:3;                 // 30:28 Type of error of the registered count
    uint16_t rsvd2:1;                   // 31 Reserved
};

union WADI_BLKERRINFO_REG {
    uint32_t  all;
    struct  WADI_BLKERRINFO_BITS  bit;
};

struct WADI_BLKERRCFG_BITS {            // bits description
    uint16_t ERRCNTSEL:2;               // 1:0 Selects the count to be multiplexed for debug
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t OVERIDESIG1:4;             // 11:8 Drives the signal correction for outputting the SIG1
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t OVERIDESIG2:4;             // 19:16 Drives the signal correction for outputting the SIG2
    uint16_t rsvd3:4;                   // 23:20 Reserved
    uint16_t OVERIDESIGTOSIG:4;         // 27:24 Drives the correction to both signals if SIGTOSIG error
    uint16_t rsvd4:4;                   // 31:28 Reserved
};

union WADI_BLKERRCFG_REG {
    uint32_t  all;
    struct  WADI_BLKERRCFG_BITS  bit;
};

struct WADI_SSS_EVTMASK_BITS {          // bits description
    uint16_t SIG1MASK:15;               // 14:0 Mask for specific WADI events to SSS event word or not
    uint16_t rsvd1:1;                   // 15 Reserved
    uint16_t SIG2MASK:4;                // 19:16 Mask for specific WADI events to SSS event word or not
    uint16_t rsvd2:12;                  // 31:20 Reserved
};

union WADI_SSS_EVTMASK_REG {
    uint32_t  all;
    struct  WADI_SSS_EVTMASK_BITS  bit;
};

struct WADI_PARTEST_BITS {              // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity test enable configuration
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_PARTEST_REG {
    uint32_t  all;
    struct  WADI_PARTEST_BITS  bit;
};

struct WADI_CONFIG_REGS {
    union   WADI_BLKCFG_REG                  BLKCFG;                       // WADI Block Clock Divider
    union   WADI_SIGTOSIGCFG_REG             SIGTOSIGCFG;                  // Configuration for SIG1 to SIG2 comparison for WADI Block
    union   WADI_SIGTOSIG_PKCFG_REG          SIGTOSIG_PKCFG;               // Signal1 to Signal2 peak comparison value and margin for WADI Block
    union   WADI_SIGTOSIG_AVGCFG_REG         SIGTOSIG_AVGCFG;              // Signal1 to Signal2 average comparison value and margin for WADI Block
    union   WADI_SIGTOSIG_DBOLAPA_REG        SIGTOSIG_DBOLAPA;             // Signal1 to Signal2 dead-band comparison difference and margin for WADI Block
    union   WADI_SIGTOSIG_DBOLAPB_REG        SIGTOSIG_DBOLAPB;             // Signal1 to Signal2 dead-band and Overlap compare values for WADI Block
    union   WADI_BLKTRIGCFG_REG              BLKTRIGCFG;                   // The trigger configuration for SIG1 and SIG2 of the WADI Block
    uint8_t                                  rsvd1[36];                    // Reserved
    union   WADI_SIG1CFG_REG                 SIG1CFG;                      // Measurement configuration for SIG1 of WADI Block
    union   WADI_SIG1CMPA_REG                SIG1CMPA;                     // Envelope-1 compare value and margin for SIG1 for WADI Block
    union   WADI_SIG1CMPB_REG                SIG1CMPB;                     // Envelope-2 compare value and margin for SIG1 for WADI Block
    union   WADI_SIG1PKCFG_REG               SIG1PKCFG;                    // Peak of the aggregation compare configuration for  SIG1 of WADI Block
    union   WADI_SIG1AVGCFG_REG              SIG1AVGCFG;                   // Average of the aggregation comparison configuration for SIG1 of WADI Block
    union   WADI_SIG1EDGECFG_REG             SIG1EDGECFG;                  // Frequency measurement  configuration for SIG1 of WADI Block
    union   WADI_SIG1EDGEMVWCFG_REG          SIG1EDGEMVWCFG;               // Moving Window Configuration for SIG1 of WADI Block
    uint8_t                                  rsvd2[36];                    // Reserved
    union   WADI_SIG2CFG_REG                 SIG2CFG;                      // Measurement configuration for SIG2 of WADI Block
    union   WADI_SIG2CMPA_REG                SIG2CMPA;                     // Compare value A and +/- margin for SIG2 for WADI Block
    union   WADI_SIG2CMPB_REG                SIG2CMPB;                     // Compare value B and +/- margin for SIG2 for WADI Block
    union   WADI_SIG2PKCFG_REG               SIG2PKCFG;                    // Peak of the aggregation compare configuration for  SIG2 of WADI Block
    union   WADI_SIG2AVGCFG_REG              SIG2AVGCFG;                   // Average of the aggregation comparison configuration for SIG2 of WADI Block
    union   WADI_SIG2EDGECFG_REG             SIG2EDGECFG;                  // Frequency measurement  configuration for SIG2 of WADI Block
    union   WADI_SIG2EDGEMVWCFG_REG          SIG2EDGEMVWCFG;               // Moving Window Configuration for SIG2 of WADI Block
    uint8_t                                  rsvd3[36];                    // Reserved
    union   WADI_BLKERRSTS_REG               BLKERRSTS;                    // Block status register
    union   WADI_BLKERRINFO_REG              BLKERRINFO;                   // Block count value of failed register
    union   WADI_BLKERRCFG_REG               BLKERRCFG;                    // Block Debug additional info.
    union   WADI_SSS_EVTMASK_REG             SSS_EVTMASK;                  // Mask to combine Block errors for trigger of SSS in event word Output by WADI block
    uint8_t                                  rsvd4[24];                    // Reserved
    union   WADI_PARTEST_REG                 PARTEST;                      // Enables parity test
};

struct WADI_BASETIMERHIGH_BITS {        // bits description
    uint32_t HIGHWORD:28;               // 27:0 Upper word of the base timer
    uint16_t rsvd1:3;                   // 30:28 Reserved
    uint16_t ENBASETIMER:1;             // 31 Start base timer trigger
};

union WADI_BASETIMERHIGH_REG {
    uint32_t  all;
    struct  WADI_BASETIMERHIGH_BITS  bit;
};

struct WADI_INTSTS_BITS {               // bits description
    uint16_t BLK1INT:1;                 // 0 Interrupt status by ORing all WADI block errors
    uint16_t BLK2INT:1;                 // 1 Interrupt status by ORing all WADI block errors
    uint16_t BLK3INT:1;                 // 2 Interrupt status by ORing all WADI block errors
    uint16_t BLK4INT:1;                 // 3 Interrupt status by ORing all WADI block errors
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t rsvd13:14;                 // 29:16 Reserved
    uint16_t SIGBLKSINT:1;              // 30 ORed int status of measurement error for all WADI blocks
    uint16_t SIGTOSIG_BLKSINT:1;        // 31 ORed int status of mismatch error for all WADI blocks
};

union WADI_INTSTS_REG {
    uint32_t  all;
    struct  WADI_INTSTS_BITS  bit;
};

struct WADI_INTSTSMASK_BITS {           // bits description
    uint16_t BLKSMASK:16;               // 15:0 Line wise mask to propagate interrupt or not
    uint16_t rsvd1:14;                  // 29:16 Reserved
    uint16_t SIGBLKSMASK:1;             // 30 Line wise mask to propagate interrupt or not
    uint16_t SIGTOSIG_BLKSMASK:1;       // 31 Line wise mask to propagate interrupt or not
};

union WADI_INTSTSMASK_REG {
    uint32_t  all;
    struct  WADI_INTSTSMASK_BITS  bit;
};

struct WADI_BLKSMASKSTS_BITS {          // bits description
    uint16_t BLKSMASK:16;               // 15:0 This is AND of INTSTS and INTSTSMASK
    uint16_t rsvd1:14;                  // 29:16 Reserved
    uint16_t SIGBLKS:1;                 // 30 This is AND of INTSTS and INTSTSMASK
    uint16_t SIGTOSIGBLKS:1;            // 31 This is AND of INTSTS and INTSTSMASK
};

union WADI_BLKSMASKSTS_REG {
    uint32_t  all;
    struct  WADI_BLKSMASKSTS_BITS  bit;
};

struct WADI_INTSTSCLR_BITS {            // bits description
    uint16_t BLK1INT:1;                 // 0 Clears the status of the INTSTS of Block 1
    uint16_t BLK2INT:1;                 // 1 Clears the status of the INTSTS of Block 2
    uint16_t BLK3INT:1;                 // 2 Clears the status of the INTSTS of Block 3
    uint16_t BLK4INT:1;                 // 3 Clears the status of the INTSTS of Block 4
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t rsvd13:14;                 // 29:16 Reserved
    uint16_t SIGBLKSINT:1;              // 30 Clears the status of all block's INTSTS[SIGBLKSINT]
    uint16_t SIGTOSIG_BLKSINT:1;        // 31 Clears the status of all block's INTSTS[SIGTOSIG_BLKSINT]
};

union WADI_INTSTSCLR_REG {
    uint32_t  all;
    struct  WADI_INTSTSCLR_BITS  bit;
};

struct WADI_INTSTSFRC_BITS {            // bits description
    uint16_t BLK1INT:1;                 // 0 Allows software force of WADI Block interrupt
    uint16_t BLK2INT:1;                 // 1 Allows software force of WADI Block interrupt
    uint16_t BLK3INT:1;                 // 2 Allows software force of WADI Block interrupt
    uint16_t BLK4INT:1;                 // 3 Allows software force of WADI Block interrupt
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t rsvd13:14;                 // 29:16 Reserved
    uint16_t SIGBLKSINT:1;              // 30 Allows software force of WADI Block interrupt
    uint16_t SIGTOSIG_BLKSINT:1;        // 31 Allows software force of WADI Block interrupt
};

union WADI_INTSTSFRC_REG {
    uint32_t  all;
    struct  WADI_INTSTSFRC_BITS  bit;
};

struct WADI_SIGSYNCFILTCFG_BITS {       // bits description
    uint16_t BLKS_SIGS_SYNCFILT:8;      // 7:0 Selects SIG is synchronised and filtered or not
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SIGSYNCFILTCFG_REG {
    uint32_t  all;
    struct  WADI_SIGSYNCFILTCFG_BITS  bit;
};

struct WADI_TRIGSYNCFILTCFG_BITS {      // bits description
    uint16_t BLKS_TRIG_SYNCFILT:8;      // 7:0 Selects Trigger input is synchronised and filtered or not
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_TRIGSYNCFILTCFG_REG {
    uint32_t  all;
    struct  WADI_TRIGSYNCFILTCFG_BITS  bit;
};

struct WADI_REVISION_BITS {             // bits description
    uint16_t MINOR:6;                   // 5:0 Minor Revision Number
    uint16_t CUSTOM:2;                  // 7:6 Custom Module Number
    uint16_t MAJOR:3;                   // 10:8 Major Revision Number
    uint16_t RTL:5;                     // 15:11 Design Release Number
    uint16_t FUNC:12;                   // 27:16 Functional Release Number
    uint16_t rsvd1:2;                   // 29:28 Reserved
    uint16_t SCHEME:2;                  // 31:30 Defines Scheme for Module
};

union WADI_REVISION_REG {
    uint32_t  all;
    struct  WADI_REVISION_BITS  bit;
};

struct WADI_DMATRIGSTS_BITS {           // bits description
    uint16_t BLK1_DMAEVT:1;             // 0 Indicates the WADI Block event for DMA trigger
    uint16_t BLK2_DMAEVT:1;             // 1 Indicates the WADI Block event for DMA trigger
    uint16_t BLK3_DMAEVT:1;             // 2 Indicates the WADI Block event for DMA trigger
    uint16_t BLK4_DMAEVT:1;             // 3 Indicates the WADI Block event for DMA trigger
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t SSS_EVT1:1;                // 16 Indicates the SSS Event event for DMA trigger
    uint16_t SSS_EVT2:1;                // 17 Indicates the SSS Event for DMA trigger
    uint16_t SSS_EVT3:1;                // 18 Indicates the SSS Event for DMA trigger
    uint16_t SSS_EVT4:1;                // 19 Indicates the SSS Event for DMA trigger
    uint16_t SSS_EVT5:1;                // 20 Indicates the SSS Event for DMA trigger
    uint16_t SSS_EVT6:1;                // 21 Indicates the SSS Event for DMA trigger
    uint16_t SSS_EVT7:1;                // 22 Indicates the SSS Event for DMA trigger
    uint16_t SSS_EVT8:1;                // 23 Indicates the SSS Event for DMA trigger
    uint16_t SSS_OUTEVT1:1;             // 24 Indicates the SSS output event for DMA trigger
    uint16_t SSS_OUTEVT2:1;             // 25 Indicates the SSS output event for DMA trigger
    uint16_t SSS_OUTEVT3:1;             // 26 Indicates the SSS output event for DMA trigger
    uint16_t SSS_OUTEVT4:1;             // 27 Indicates the SSS output event for DMA trigger
    uint16_t SSS_OUTEVT5:1;             // 28 Indicates the SSS output event for DMA trigger
    uint16_t SSS_OUTEVT6:1;             // 29 Indicates the SSS output event for DMA trigger
    uint16_t SSS_OUTEVT7:1;             // 30 Indicates the SSS output event for DMA trigger
    uint16_t SSS_OUTEVT8:1;             // 31 Indicates the SSS output event for DMA trigger
};

union WADI_DMATRIGSTS_REG {
    uint32_t  all;
    struct  WADI_DMATRIGSTS_BITS  bit;
};

struct WADI_DMATRIGEN_BITS {            // bits description
    uint16_t BLKSDMAEVT:16;             // 15:0 WADI Block event enables for DMA request trigger
    uint16_t SSS_EVT1_4DMA:4;           // 19:16 SSS Event word Set-1 enables for DMA request Trigger
    uint16_t SSS_EVT5_8DMA:4;           // 23:20 SSS Event word Set-2 enables for DMA request Trigger
    uint16_t SSS_OUTEVT1_4DMA:4;        // 27:24 SSS output event 1 to 4 enables for DMA request Trigger
    uint16_t SSS_OUTEVT5_8DMA:4;        // 31:28 SSS output event 5 to 8 enables for DMA request Trigger
};

union WADI_DMATRIGEN_REG {
    uint32_t  all;
    struct  WADI_DMATRIGEN_BITS  bit;
};

struct WADI_DMASTSUPDATE_BITS {         // bits description
    uint16_t WRSTSBLK1:1;               // 0 Status of DMA update for register set of WADI Block
    uint16_t WRSTSBLK2:1;               // 1 Status of DMA update for register set of WADI Block
    uint16_t WRSTSBLK3:1;               // 2 Status of DMA update for register set of WADI Block
    uint16_t WRSTSBLK4:1;               // 3 Status of DMA update for register set of WADI Block
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t WRSTSEVT1:1;               // 16 DMA MMR write status of  SSS Event word
    uint16_t WRSTSEVT2:1;               // 17 DMA MMR write status of  SSS Event word
    uint16_t WRSTSEVT3:1;               // 18 DMA MMR write status of  SSS Event word
    uint16_t WRSTSEVT4:1;               // 19 DMA MMR write status of  SSS Event word
    uint16_t WRSTSEVT5:1;               // 20 DMA MMR write status of  SSS Event word
    uint16_t WRSTSEVT6:1;               // 21 DMA MMR write status of  SSS Event word
    uint16_t WRSTSEVT7:1;               // 22 DMA MMR write status of  SSS Event word
    uint16_t WRSTSEVT8:1;               // 23 DMA MMR write status of  SSS Event word
    uint16_t WRSTSOUT1:1;               // 24 DMA MMR write status of  SSS OUTEVT1
    uint16_t WRSTSOUT2:1;               // 25 DMA MMR write status of  SSS OUTEVT2
    uint16_t WRSTSOUT3:1;               // 26 DMA MMR write status of  SSS OUTEVT3
    uint16_t WRSTSOUT4:1;               // 27 DMA MMR write status of  SSS OUTEVT4
    uint16_t WRSTSOUT5:1;               // 28 DMA MMR write status of  SSS OUTEVT5
    uint16_t WRSTSOUT6:1;               // 29 DMA MMR write status of  SSS OUTEVT6
    uint16_t WRSTSOUT7:1;               // 30 DMA MMR write status of  SSS OUTEVT7
    uint16_t WRSTSOUT8:1;               // 31 DMA MMR write status of  SSS OUTEVT8
};

union WADI_DMASTSUPDATE_REG {
    uint32_t  all;
    struct  WADI_DMASTSUPDATE_BITS  bit;
};

struct WADI_DMAFILTWRCFG_BITS {         // bits description
    uint16_t BLKSWREN:16;               // 15:0 Enable for filtered DMA write for WADI Block
    uint16_t EVT1_4WREN:4;              // 19:16 Enable for filtered DMA write for SSS Event 1 to 4
    uint16_t EVT5_8WREN:4;              // 23:20 Enable for filtered DMA write for SSS Event 5 to 8
    uint16_t OUTEVT1_4WREN:4;           // 27:24 Enable for filtered DMA write for SSS output Events 1-4
    uint16_t OUTEVT5_8WREN:4;           // 31:28 Enable for filtered DMA write for SSS output Events 5-8
};

union WADI_DMAFILTWRCFG_REG {
    uint32_t  all;
    struct  WADI_DMAFILTWRCFG_BITS  bit;
};

struct WADI_CFGREGLOCK_BITS {           // bits description
    uint16_t LOCK:1;                    // 0 Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_CFGREGLOCK_REG {
    uint32_t  all;
    struct  WADI_CFGREGLOCK_BITS  bit;
};

struct WADI_CFGREGCOMMIT_BITS {         // bits description
    uint16_t COMMIT:1;                  // 0 CONFIG_REG_LOCK Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_CFGREGCOMMIT_REG {
    uint32_t  all;
    struct  WADI_CFGREGCOMMIT_BITS  bit;
};

struct WADI_OPERREGLOCK_BITS {          // bits description
    uint16_t LOCK:1;                    // 0 Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_OPERREGLOCK_REG {
    uint32_t  all;
    struct  WADI_OPERREGLOCK_BITS  bit;
};

struct WADI_OPERREGCOMMIT_BITS {        // bits description
    uint16_t COMMIT:1;                  // 0 OPER_REG_LOCK Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_OPERREGCOMMIT_REG {
    uint32_t  all;
    struct  WADI_OPERREGCOMMIT_BITS  bit;
};

struct WADI_SSS_EVTTRIG_BITS {          // bits description
    uint16_t EVTTRIG:8;                 // 7:0 SSS start if event trigger matches one of defined EVT1-8
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_EVTTRIG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVTTRIG_BITS  bit;
};

struct WADI_SSS_OUTEVTSTS_BITS {        // bits description
    uint16_t OUTEVT1_4:4;               // 3:0 Active seq word status for first set
    uint16_t OUTEVT5_8:4;               // 7:4 Active seq word status for Second set
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVTSTS_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVTSTS_BITS  bit;
};

struct WADI_SSS_BLK1_2OUTSEL_BITS {     // bits description
    uint16_t BLK1SIG1:8;                // 7:0 Maps the  OUTEVTn associated with BLK0:SIG1
    uint16_t BLK1SIG2:8;                // 15:8 Maps the OUTEVTn associated with BLK0:SIG2
    uint16_t BLK2SIG1:8;                // 23:16 Maps the OUTEVTn associated with BLK1:SIG1
    uint16_t BLK2SIG2:8;                // 31:24 Maps the OUTEVTn associated with BLK1:SIG2
};

union WADI_SSS_BLK1_2OUTSEL_REG {
    uint32_t  all;
    struct  WADI_SSS_BLK1_2OUTSEL_BITS  bit;
};

struct WADI_SSS_BLK3_4OUTSEL_BITS {     // bits description
    uint16_t BLK3SIG1:8;                // 7:0 Maps the  OUTEVTn associated with BLK2:SIG1
    uint16_t BLK3SIG2:8;                // 15:8 Maps the OUTEVTn associated with BLK2:SIG2
    uint16_t BLK4SIG1:8;                // 23:16 Maps the OUTEVTn associated with BLK3:SIG1
    uint16_t BLK4SIG2:8;                // 31:24 Maps the OUTEVTn associated with BLK3:SIG2
};

union WADI_SSS_BLK3_4OUTSEL_REG {
    uint32_t  all;
    struct  WADI_SSS_BLK3_4OUTSEL_BITS  bit;
};

struct WADI_SSS_OUTEVT1LINKCFG_BITS {   // bits description
    uint16_t OUTEVT1LINK:8;             // 7:0 Links output events (OUTEVTs) as per one hot encoding
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT1LINKCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT1LINKCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT2LINKCFG_BITS {   // bits description
    uint16_t OUTEVT2LINK:8;             // 7:0 Links output events (OUTEVTs) as per one hot encoding
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT2LINKCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT2LINKCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT3LINKCFG_BITS {   // bits description
    uint16_t OUTEVT3LINK:8;             // 7:0 Links output events (OUTEVTs) as per one hot encoding
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT3LINKCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT3LINKCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT4LINKCFG_BITS {   // bits description
    uint16_t OUTEVT4LINK:8;             // 7:0 Links output events (OUTEVTs) as per one hot encoding
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT4LINKCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT4LINKCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT5LINKCFG_BITS {   // bits description
    uint16_t OUTEVT5LINK:8;             // 7:0 Links output events (OUTEVTs) as per one hot encoding
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT5LINKCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT5LINKCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT6LINKCFG_BITS {   // bits description
    uint16_t OUTEVT6LINK:8;             // 7:0 Links output events (OUTEVTs) as per one hot encoding
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT6LINKCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT6LINKCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT7LINKCFG_BITS {   // bits description
    uint16_t OUTEVT7LINK:8;             // 7:0 Links output events (OUTEVTs) as per one hot encoding
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT7LINKCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT7LINKCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT8LINKCFG_BITS {   // bits description
    uint16_t OUT8LINK:8;                // 7:0 Links output events (OUTEVTs) as per one hot encoding
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT8LINKCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT8LINKCFG_BITS  bit;
};

struct WADI_SSS_EVT1CFG_BITS {          // bits description
    uint16_t EVT1:8;                    // 7:0 First event compare configuration
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_EVT1CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVT1CFG_BITS  bit;
};

struct WADI_SSS_EVT2CFG_BITS {          // bits description
    uint16_t EVT2:8;                    // 7:0 Second word compare value configuration
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_EVT2CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVT2CFG_BITS  bit;
};

struct WADI_SSS_EVT3CFG_BITS {          // bits description
    uint16_t EVT3:8;                    // 7:0 Third word compare value configuration
    uint32_t EVT3_BLK5_TO_16:24;        // 31:8 Third word compare value configuration
};

union WADI_SSS_EVT3CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVT3CFG_BITS  bit;
};

struct WADI_SSS_EVT4CFG_BITS {          // bits description
    uint16_t EVT4:8;                    // 7:0 Fourth word compare value configuration
    uint32_t EVT4_BLK5_TO_16:24;        // 31:8 Fourth word compare value configuration
};

union WADI_SSS_EVT4CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVT4CFG_BITS  bit;
};

struct WADI_SSS_TRIGEVT1_4CFG_BITS {    // bits description
    uint16_t TRIG_EVT1CFG:4;            // 3:0 Selects action associated with event 1
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t TRIG_EVT2CFG:4;            // 11:8 Selects action associated with event 2
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t TRIG_EVT3CFG:4;            // 19:16 Selects action associated with event 3
    uint16_t rsvd3:4;                   // 23:20 Reserved
    uint16_t TRIG_EVT4CFG:4;            // 27:24 Selects action associated with event 4
    uint16_t rsvd4:4;                   // 31:28 Reserved
};

union WADI_SSS_TRIGEVT1_4CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_TRIGEVT1_4CFG_BITS  bit;
};

struct WADI_SSS_BLKSOUTEVT1CFG_BITS {   // bits description
    uint16_t OUTEVT1:8;                 // 7:0 Output configuration on event 1
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_BLKSOUTEVT1CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_BLKSOUTEVT1CFG_BITS  bit;
};

struct WADI_SSS_BLKSOUTEVT2CFG_BITS {   // bits description
    uint16_t OUTEVT2:8;                 // 7:0 Output configuration on event 2
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_BLKSOUTEVT2CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_BLKSOUTEVT2CFG_BITS  bit;
};

struct WADI_SSS_BLKSOUTEVT3CFG_BITS {   // bits description
    uint16_t OUTEVT3:8;                 // 7:0 Output configuration on event 3
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_BLKSOUTEVT3CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_BLKSOUTEVT3CFG_BITS  bit;
};

struct WADI_SSS_BLKSOUTEVT4CFG_BITS {   // bits description
    uint16_t OUTEVT4:8;                 // 7:0 Output configuration on event 4
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_BLKSOUTEVT4CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_BLKSOUTEVT4CFG_BITS  bit;
};

struct WADI_SSS_OUTEVT1TRIGCFG_BITS {   // bits description
    uint16_t EVT1TRIG:1;                // 0 Sets OUTEVT1 based on Event 1 Trigger
    uint16_t EVT2TRIG:1;                // 1 Sets OUTEVT1 based on Event 2 Trigger
    uint16_t EVT3TRIG:1;                // 2 Sets OUTEVT1 based on Event 3 Trigger
    uint16_t EVT4TRIG:1;                // 3 Sets OUTEVT1 based on Event 4 Trigger
    uint16_t EVT5TRIG:1;                // 4 Sets OUTEVT1 based on Event 5 Trigger
    uint16_t EVT6TRIG:1;                // 5 Sets OUTEVT1 based on Event 6 Trigger
    uint16_t EVT7TRIG:1;                // 6 Sets OUTEVT1 based on Event 7 Trigger
    uint16_t EVT8TRIG:1;                // 7 Sets OUTEVT1 based on Event 8 Trigger
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT1TRIGCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT1TRIGCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT2TRIGCFG_BITS {   // bits description
    uint16_t EVT1TRIG:1;                // 0 Sets OUTEVT2 based on Event 1 Trigger
    uint16_t EVT2TRIG:1;                // 1 Sets OUTEVT2 based on Event 2 Trigger
    uint16_t EVT3TRIG:1;                // 2 Sets OUTEVT2 based on Event 3 Trigger
    uint16_t EVT4TRIG:1;                // 3 Sets OUTEVT2 based on Event 4 Trigger
    uint16_t EVT5TRIG:1;                // 4 Sets OUTEVT2 based on Event 5 Trigger
    uint16_t EVT6TRIG:1;                // 5 Sets OUTEVT2 based on Event 6 Trigger
    uint16_t EVT7TRIG:1;                // 6 Sets OUTEVT2 based on Event 7 Trigger
    uint16_t EVT8TRIG:1;                // 7 Sets OUTEVT2 based on Event 8 Trigger
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT2TRIGCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT2TRIGCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT3TRIGCFG_BITS {   // bits description
    uint16_t EVT1TRIG:1;                // 0 Sets OUTEVT3 based on Event 1 Trigger
    uint16_t EVT2TRIG:1;                // 1 Sets OUTEVT3 based on Event 2 Trigger
    uint16_t EVT3TRIG:1;                // 2 Sets OUTEVT3 based on Event 3 Trigger
    uint16_t EVT4TRIG:1;                // 3 Sets OUTEVT3 based on Event 4 Trigger
    uint16_t EVT5TRIG:1;                // 4 Sets OUTEVT3 based on Event 5 Trigger
    uint16_t EVT6TRIG:1;                // 5 Sets OUTEVT3 based on Event 6 Trigger
    uint16_t EVT7TRIG:1;                // 6 Sets OUTEVT3 based on Event 7 Trigger
    uint16_t EVT8TRIG:1;                // 7 Sets OUTEVT3 based on Event 8 Trigger
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT3TRIGCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT3TRIGCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT4TRIGCFG_BITS {   // bits description
    uint16_t EVT1TRIG:1;                // 0 Sets OUTEVT4 based on Event 1 Trigger
    uint16_t EVT2TRIG:1;                // 1 Sets OUTEVT4 based on Event 2 Trigger
    uint16_t EVT3TRIG:1;                // 2 Sets OUTEVT4 based on Event 3 Trigger
    uint16_t EVT4TRIG:1;                // 3 Sets OUTEVT4 based on Event 4 Trigger
    uint16_t EVT5TRIG:1;                // 4 Sets OUTEVT4 based on Event 5 Trigger
    uint16_t EVT6TRIG:1;                // 5 Sets OUTEVT4 based on Event 6 Trigger
    uint16_t EVT7TRIG:1;                // 6 Sets OUTEVT4 based on Event 7 Trigger
    uint16_t EVT8TRIG:1;                // 7 Sets OUTEVT4 based on Event 8 Trigger
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT4TRIGCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT4TRIGCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT1DUR_BITS {       // bits description
    uint32_t TIME:24;                   // 23:0 Duration time for application of OUTEVT1
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union WADI_SSS_OUTEVT1DUR_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT1DUR_BITS  bit;
};

struct WADI_SSS_OUTEVT2DUR_BITS {       // bits description
    uint32_t TIME:24;                   // 23:0 Duration time for application of OUTEVT2
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union WADI_SSS_OUTEVT2DUR_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT2DUR_BITS  bit;
};

struct WADI_SSS_OUTEVT3DUR_BITS {       // bits description
    uint32_t TIME:24;                   // 23:0 Duration time for application of OUTEVT3
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union WADI_SSS_OUTEVT3DUR_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT3DUR_BITS  bit;
};

struct WADI_SSS_OUTEVT4DUR_BITS {       // bits description
    uint32_t TIME:24;                   // 23:0 Duration time for application of OUTEVT4
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union WADI_SSS_OUTEVT4DUR_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT4DUR_BITS  bit;
};

struct WADI_SSS_EVT5CFG_BITS {          // bits description
    uint16_t EVT5:8;                    // 7:0 Fifth word compare value configuration
    uint32_t EVT5_BLK5_TO_16:24;        // 31:8 Fifth word compare value configuration
};

union WADI_SSS_EVT5CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVT5CFG_BITS  bit;
};

struct WADI_SSS_EVT6CFG_BITS {          // bits description
    uint16_t EVT6:8;                    // 7:0 Sixth word compare value configuration
    uint32_t EVT6_BLK5_TO_16:24;        // 31:8 Sixth word compare value configuration
};

union WADI_SSS_EVT6CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVT6CFG_BITS  bit;
};

struct WADI_SSS_EVT7CFG_BITS {          // bits description
    uint16_t EVT7:8;                    // 7:0 Seventh word compare value configuration
    uint32_t EVT7_BLK5_TO_16:24;        // 31:8 Seventh word compare value configuration
};

union WADI_SSS_EVT7CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVT7CFG_BITS  bit;
};

struct WADI_SSS_EVT8CFG_BITS {          // bits description
    uint16_t EVT8:8;                    // 7:0 Eighth word compare value configuration
    uint32_t EVT8_BLK5_TO_16:24;        // 31:8 Eighth word compare value configuration
};

union WADI_SSS_EVT8CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_EVT8CFG_BITS  bit;
};

struct WADI_SSS_TRIGEVT5_8CFG_BITS {    // bits description
    uint16_t TRIG_EVT5CFG:4;            // 3:0 Selects action associated with event 5
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t TRIG_EVT6CFG:4;            // 11:8 Selects action associated with event 6
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t TRIG_EVT7CFG:4;            // 19:16 Selects action associated with event 7
    uint16_t rsvd3:4;                   // 23:20 Reserved
    uint16_t TRIG_EVT8CFG:4;            // 27:24 Selects action associated with event 8
    uint16_t rsvd4:4;                   // 31:28 Reserved
};

union WADI_SSS_TRIGEVT5_8CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_TRIGEVT5_8CFG_BITS  bit;
};

struct WADI_SSS_BLKSOUTEVT5CFG_BITS {   // bits description
    uint16_t OUTEVT5:8;                 // 7:0 Output configuration on event 5
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_BLKSOUTEVT5CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_BLKSOUTEVT5CFG_BITS  bit;
};

struct WADI_SSS_BLKSOUTEVT6CFG_BITS {   // bits description
    uint16_t OUTEVT6:8;                 // 7:0 Output configuration on event 6
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_BLKSOUTEVT6CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_BLKSOUTEVT6CFG_BITS  bit;
};

struct WADI_SSS_BLKSOUTEVT7CFG_BITS {   // bits description
    uint16_t OUTEVT7:8;                 // 7:0 Output configuration on event 7
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_BLKSOUTEVT7CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_BLKSOUTEVT7CFG_BITS  bit;
};

struct WADI_SSS_BLKSOUTEVT8CFG_BITS {   // bits description
    uint16_t OUTEVT8:8;                 // 7:0 Output configuration on event 8
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_BLKSOUTEVT8CFG_REG {
    uint32_t  all;
    struct  WADI_SSS_BLKSOUTEVT8CFG_BITS  bit;
};

struct WADI_SSS_OUTEVT5TRIGCFG_BITS {   // bits description
    uint16_t EVT1TRIG:1;                // 0 Sets OUTEVT5 based on Event 1 Trigger
    uint16_t EVT2TRIG:1;                // 1 Sets OUTEVT5 based on Event 2 Trigger
    uint16_t EVT3TRIG:1;                // 2 Sets OUTEVT5 based on Event 3 Trigger
    uint16_t EVT4TRIG:1;                // 3 Sets OUTEVT5 based on Event 4 Trigger
    uint16_t EVT5TRIG:1;                // 4 Sets OUTEVT5 based on Event 5 Trigger
    uint16_t EVT6TRIG:1;                // 5 Sets OUTEVT5 based on Event 6 Trigger
    uint16_t EVT7TRIG:1;                // 6 Sets OUTEVT5 based on Event 7 Trigger
    uint16_t EVT8TRIG:1;                // 7 Sets OUTEVT5 based on Event 8 Trigger
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT5TRIGCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT5TRIGCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT6TRIGCFG_BITS {   // bits description
    uint16_t EVT1TRIG:1;                // 0 Sets OUTEVT6 based on Event 1 Trigger
    uint16_t EVT2TRIG:1;                // 1 Sets OUTEVT6 based on Event 2 Trigger
    uint16_t EVT3TRIG:1;                // 2 Sets OUTEVT6 based on Event 3 Trigger
    uint16_t EVT4TRIG:1;                // 3 Sets OUTEVT6 based on Event 4 Trigger
    uint16_t EVT5TRIG:1;                // 4 Sets OUTEVT6 based on Event 5 Trigger
    uint16_t EVT6TRIG:1;                // 5 Sets OUTEVT6 based on Event 6 Trigger
    uint16_t EVT7TRIG:1;                // 6 Sets OUTEVT6 based on Event 7 Trigger
    uint16_t EVT8TRIG:1;                // 7 Sets OUTEVT6 based on Event 8 Trigger
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT6TRIGCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT6TRIGCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT7TRIGCFG_BITS {   // bits description
    uint16_t EVT1TRIG:1;                // 0 Sets OUTEVT7 based on Event 1 Trigger
    uint16_t EVT2TRIG:1;                // 1 Sets OUTEVT7 based on Event 2 Trigger
    uint16_t EVT3TRIG:1;                // 2 Sets OUTEVT7 based on Event 3 Trigger
    uint16_t EVT4TRIG:1;                // 3 Sets OUTEVT7 based on Event 4 Trigger
    uint16_t EVT5TRIG:1;                // 4 Sets OUTEVT7 based on Event 5 Trigger
    uint16_t EVT6TRIG:1;                // 5 Sets OUTEVT7 based on Event 6 Trigger
    uint16_t EVT7TRIG:1;                // 6 Sets OUTEVT7 based on Event 7 Trigger
    uint16_t EVT8TRIG:1;                // 7 Sets OUTEVT7 based on Event 8 Trigger
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT7TRIGCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT7TRIGCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT8TRIGCFG_BITS {   // bits description
    uint16_t EVT1TRIG:1;                // 0 Sets OUTEVT8 based on Event 1 Trigger
    uint16_t EVT2TRIG:1;                // 1 Sets OUTEVT8 based on Event 2 Trigger
    uint16_t EVT3TRIG:1;                // 2 Sets OUTEVT8 based on Event 3 Trigger
    uint16_t EVT4TRIG:1;                // 3 Sets OUTEVT8 based on Event 4 Trigger
    uint16_t EVT5TRIG:1;                // 4 Sets OUTEVT8 based on Event 5 Trigger
    uint16_t EVT6TRIG:1;                // 5 Sets OUTEVT8 based on Event 6 Trigger
    uint16_t EVT7TRIG:1;                // 6 Sets OUTEVT8 based on Event 7 Trigger
    uint16_t EVT8TRIG:1;                // 7 Sets OUTEVT8 based on Event 8 Trigger
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union WADI_SSS_OUTEVT8TRIGCFG_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT8TRIGCFG_BITS  bit;
};

struct WADI_SSS_OUTEVT5DUR_BITS {       // bits description
    uint32_t TIME:24;                   // 23:0 Duration time for application of OUTEVT5
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union WADI_SSS_OUTEVT5DUR_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT5DUR_BITS  bit;
};

struct WADI_SSS_OUTEVT6DUR_BITS {       // bits description
    uint32_t TIME:24;                   // 23:0 Duration time for application of OUTEVT6
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union WADI_SSS_OUTEVT6DUR_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT6DUR_BITS  bit;
};

struct WADI_SSS_OUTEVT7DUR_BITS {       // bits description
    uint32_t TIME:24;                   // 23:0 Duration time for application of OUTEVT7
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union WADI_SSS_OUTEVT7DUR_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT7DUR_BITS  bit;
};

struct WADI_SSS_OUTEVT8DUR_BITS {       // bits description
    uint32_t TIME:24;                   // 23:0 Duration time for application of OUTEVT8
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union WADI_SSS_OUTEVT8DUR_REG {
    uint32_t  all;
    struct  WADI_SSS_OUTEVT8DUR_BITS  bit;
};

struct WADI_OPER_SSS_REGS {
    uint32_t                                 BASETIMERLOW;                 // Read only value for lower word of the base timer.
    union   WADI_BASETIMERHIGH_REG           BASETIMERHIGH;                // Upper word of the base timer and trigger to start the timer.
    union   WADI_INTSTS_REG                  INTSTS;                       // Gives the block wise aggregated raw error status that shall trigger the interrupt.
    union   WADI_INTSTSMASK_REG              INTSTSMASK;                   // Provides mask for application to suppress or allow a particular block related errors to cause interrupt or not
    union   WADI_BLKSMASKSTS_REG             BLKSMASKSTS;                  // This is AND combination of active high indication of block-wise status asserting an interrupt.
    union   WADI_INTSTSCLR_REG               INTSTSCLR;                    // Provides way for application to clear the interrupt status.
    union   WADI_INTSTSFRC_REG               INTSTSFRC;                    // Allows emulation of the RIS to raise interrupt in software
    union   WADI_SIGSYNCFILTCFG_REG          SIGSYNCFILTCFG;               // Each input SIG to be connected through synchroniser or not
    union   WADI_TRIGSYNCFILTCFG_REG         TRIGSYNCFILTCFG;              // Each trigger to be connected through synchroniser or not
    uint8_t                                  rsvd1[24];                    // Reserved
    union   WADI_REVISION_REG                REVISION;                     // IP Revision
    union   WADI_DMATRIGSTS_REG              DMATRIGSTS;                   // Status of the DMA triggers active
    union   WADI_DMATRIGEN_REG               DMATRIGEN;                    // Mask to enable individual trigger cause
    union   WADI_DMASTSUPDATE_REG            DMASTSUPDATE;                 // Indicates the register set updated post DMA write
    union   WADI_DMAFILTWRCFG_REG            DMAFILTWRCFG;                 // DMA writes Filter enable for each of WADI & SSS blocks
    uint8_t                                  rsvd2[84];                    // Reserved
    union   WADI_CFGREGLOCK_REG              CFGREGLOCK;                   // Configuration Register Lock
    union   WADI_CFGREGCOMMIT_REG            CFGREGCOMMIT;                 // Configuration Register Commit
    union   WADI_OPERREGLOCK_REG             OPERREGLOCK;                  // Operating Register Lock
    union   WADI_OPERREGCOMMIT_REG           OPERREGCOMMIT;                // Operating Register Commit
    uint8_t                                  rsvd3[4];                     // Reserved
    union   WADI_SSS_EVTTRIG_REG             SSS_EVTTRIG;                  // Event trigger word output by WADI instance for SSS
    union   WADI_SSS_OUTEVTSTS_REG           SSS_OUTEVTSTS;                // Status of the active event
    union   WADI_SSS_BLK1_2OUTSEL_REG        SSS_BLK1_2OUTSEL;             // Mux select word for outputs 0-3
    union   WADI_SSS_BLK3_4OUTSEL_REG        SSS_BLK3_4OUTSEL;             // Mux select word for outputs 4-7
    uint8_t                                  rsvd4[24];                    // Reserved
    union   WADI_SSS_OUTEVT1LINKCFG_REG      SSS_OUTEVT1LINKCFG;           // Output event1 Link configuration
    union   WADI_SSS_OUTEVT2LINKCFG_REG      SSS_OUTEVT2LINKCFG;           // Output event2 link configuration
    union   WADI_SSS_OUTEVT3LINKCFG_REG      SSS_OUTEVT3LINKCFG;           // Output event3 link configuration
    union   WADI_SSS_OUTEVT4LINKCFG_REG      SSS_OUTEVT4LINKCFG;           // Output event4 link configuration
    union   WADI_SSS_OUTEVT5LINKCFG_REG      SSS_OUTEVT5LINKCFG;           // Output event5 link configuration
    union   WADI_SSS_OUTEVT6LINKCFG_REG      SSS_OUTEVT6LINKCFG;           // Output event6 link configuration
    union   WADI_SSS_OUTEVT7LINKCFG_REG      SSS_OUTEVT7LINKCFG;           // Output event7 link configuration
    union   WADI_SSS_OUTEVT8LINKCFG_REG      SSS_OUTEVT8LINKCFG;           // Output event8 link configuration
    union   WADI_SSS_EVT1CFG_REG             SSS_EVT1CFG;                  // Event1 that compares to trigger word SSS_EVTTRIG
    union   WADI_SSS_EVT2CFG_REG             SSS_EVT2CFG;                  // Event2 that compares to trigger word SSS_EVTTRIG
    union   WADI_SSS_EVT3CFG_REG             SSS_EVT3CFG;                  // Event3 that compares to trigger word SSS_EVTTRIG
    union   WADI_SSS_EVT4CFG_REG             SSS_EVT4CFG;                  // Event4 that compares to trigger word SSS_EVTTRIG
    union   WADI_SSS_TRIGEVT1_4CFG_REG       SSS_TRIGEVT1_4CFG;            // Configuration for using trigger word in specific manner
    uint8_t                                  rsvd5[108];                   // Reserved
    union   WADI_SSS_BLKSOUTEVT1CFG_REG      SSS_BLKSOUTEVT1CFG;           // Output event1 to be applied for output
    union   WADI_SSS_BLKSOUTEVT2CFG_REG      SSS_BLKSOUTEVT2CFG;           // Output event2 to be applied for output
    union   WADI_SSS_BLKSOUTEVT3CFG_REG      SSS_BLKSOUTEVT3CFG;           // Output event3 to be applied for output
    union   WADI_SSS_BLKSOUTEVT4CFG_REG      SSS_BLKSOUTEVT4CFG;           // Output event4 to be applied for output
    union   WADI_SSS_OUTEVT1TRIGCFG_REG      SSS_OUTEVT1TRIGCFG;           // Output event1 configuration for triggers, link
    union   WADI_SSS_OUTEVT2TRIGCFG_REG      SSS_OUTEVT2TRIGCFG;           // Output event2 configuration for triggers, link
    union   WADI_SSS_OUTEVT3TRIGCFG_REG      SSS_OUTEVT3TRIGCFG;           // Output event3 configuration for triggers, link
    union   WADI_SSS_OUTEVT4TRIGCFG_REG      SSS_OUTEVT4TRIGCFG;           // Output event4 configuration for triggers, link
    union   WADI_SSS_OUTEVT1DUR_REG          SSS_OUTEVT1DUR;               // Output event1 configuration of delays
    union   WADI_SSS_OUTEVT2DUR_REG          SSS_OUTEVT2DUR;               // Output event2 configuration of delays
    union   WADI_SSS_OUTEVT3DUR_REG          SSS_OUTEVT3DUR;               // Output event3 configuration of delays
    union   WADI_SSS_OUTEVT4DUR_REG          SSS_OUTEVT4DUR;               // Output event4 configuration of delays
    uint8_t                                  rsvd6[80];                    // Reserved
    union   WADI_SSS_EVT5CFG_REG             SSS_EVT5CFG;                  // Event5 that compares to trigger word SSS_EVTTRIG
    union   WADI_SSS_EVT6CFG_REG             SSS_EVT6CFG;                  // Event6 that compares to trigger word SSS_EVTTRIG
    union   WADI_SSS_EVT7CFG_REG             SSS_EVT7CFG;                  // Event7 that compares to trigger word SSS_EVTTRIG
    union   WADI_SSS_EVT8CFG_REG             SSS_EVT8CFG;                  // Event8 that compares to trigger word SSS_EVTTRIG
    union   WADI_SSS_TRIGEVT5_8CFG_REG       SSS_TRIGEVT5_8CFG;            // Configuration for using trigger word in specific manner
    uint8_t                                  rsvd7[108];                   // Reserved
    union   WADI_SSS_BLKSOUTEVT5CFG_REG      SSS_BLKSOUTEVT5CFG;           // Output event5 to be applied for output
    union   WADI_SSS_BLKSOUTEVT6CFG_REG      SSS_BLKSOUTEVT6CFG;           // Output event6 to be applied for output
    union   WADI_SSS_BLKSOUTEVT7CFG_REG      SSS_BLKSOUTEVT7CFG;           // Output event7 to be applied for output
    union   WADI_SSS_BLKSOUTEVT8CFG_REG      SSS_BLKSOUTEVT8CFG;           // Output event8 to be applied for output
    union   WADI_SSS_OUTEVT5TRIGCFG_REG      SSS_OUTEVT5TRIGCFG;           // Output event5 configuration for triggers, link
    union   WADI_SSS_OUTEVT6TRIGCFG_REG      SSS_OUTEVT6TRIGCFG;           // Output event6 configuration for triggers, link
    union   WADI_SSS_OUTEVT7TRIGCFG_REG      SSS_OUTEVT7TRIGCFG;           // Output event7 configuration for triggers, link
    union   WADI_SSS_OUTEVT8TRIGCFG_REG      SSS_OUTEVT8TRIGCFG;           // Output event8 configuration for triggers, link
    union   WADI_SSS_OUTEVT5DUR_REG          SSS_OUTEVT5DUR;               // Output event5 configuration of delays
    union   WADI_SSS_OUTEVT6DUR_REG          SSS_OUTEVT6DUR;               // Output event6 configuration of delays
    union   WADI_SSS_OUTEVT7DUR_REG          SSS_OUTEVT7DUR;               // Output event7 configuration of delays
    union   WADI_SSS_OUTEVT8DUR_REG          SSS_OUTEVT8DUR;               // Output event8 configuration of delays
    uint8_t                                  rsvd8[24];                    // Reserved
    union   WADI_PARTEST_REG                 PARTEST;                      // Enables parity test
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
