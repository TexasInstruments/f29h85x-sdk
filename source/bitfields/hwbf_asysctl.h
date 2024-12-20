//###########################################################################
//
// FILE:    hwbf_asysctl.h
//
// TITLE:   Definitions for the ASYSCTL registers.
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

#ifndef HWBF_ASYSCTL_H
#define HWBF_ASYSCTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// ASYSCTL Individual Register Bit Definitions:

struct ASYSCTL_PMMVREGTRIM_BITS {       // bits description
    uint16_t VREGTRIM:8;                // 7:0 Core VDD Voltage Regulator Trim
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_PMMVREGTRIM_REG {
    uint32_t  all;
    struct  ASYSCTL_PMMVREGTRIM_BITS  bit;
};

struct ASYSCTL_CTLTRIMSTS_BITS {        // bits description
    uint16_t CTLSTS:1;                  // 0 TRIM Load Complete
    uint16_t rsvd1:6;                   // 6:1 Reserved
    uint16_t SBERR:1;                   // 7 Single-bit error detected while reading from Flash
    uint16_t SCANERR:1;                 // 8 Wrong scan chain signature
    uint16_t rsvd2:1;                   // 9 Reserved
    uint16_t TWOBERR:1;                 // 10 Two-bit error detected
    uint16_t TIMEOUT:1;                 // 11 Timeout Error
    uint16_t rsvd3:4;                   // 15:12 Reserved
    uint16_t INVKEY1:1;                 // 16 Invalid key read during TLC1
    uint16_t INVKEY2:1;                 // 17 Invalid key read during TLC2
    uint16_t INVKEY3:1;                 // 18 Invalid key read during TLC3
    uint16_t rsvd4:1;                   // 19 Reserved
    uint16_t rsvd5:4;                   // 23:20 Reserved
    uint16_t rsvd6:8;                   // 31:24 Reserved
};

union ASYSCTL_CTLTRIMSTS_REG {
    uint32_t  all;
    struct  ASYSCTL_CTLTRIMSTS_BITS  bit;
};

struct ASYSCTL_REFBUFCONFIGCDE_BITS {   // bits description
    uint16_t ADCC_LSB_RES_DAMP:2;       // 1:0 ADCC LSB damp res prog
    uint16_t ADCC_MSB_RES_DAMP:2;       // 3:2 ADCC MSB damp res prog
    uint16_t ADCC_CHSEL_SOC_DEL_PROG:1; // 4 CHSEL rise to ADCCSOC rise delay program
    uint16_t ADCD_LSB_RES_DAMP:2;       // 6:5 ADCD LSB damp res prog
    uint16_t ADCD_MSB_RES_DAMP:2;       // 8:7 ADCD MSB damp res prog
    uint16_t ADCD_CHSEL_SOC_DEL_PROG:1; // 9 CHSEL rise to ADCDSOC rise delay program
    uint16_t ADCE_LSB_RES_DAMP:2;       // 11:10 ADCE LSB damp res prog
    uint16_t ADCE_MSB_RES_DAMP:2;       // 13:12 ADCE MSB damp res prog
    uint16_t ADCE_CHSEL_SOC_DEL_PROG:1; // 14 CHSEL rise to ADCESOC rise delay program
    uint16_t ADCC_TM_ENZ_DUTY_CYCLE:1;  // 15 Disable Pulse Stretch testmode to have effect in ADC_CLK
    uint16_t DIS_ADCC_SP_SLEWBOOST:1;   // 16 ADC sp slew boost disbale
    uint16_t ADCDTM_ENZ_DUTY_CYCLE:1;   // 17 Disable Pulse Stretch testmode to have effect in ADC_CLK
    uint16_t DIS_ADCD_SP_SLEWBOOST:1;   // 18 ADC sp slew boost disbale
    uint16_t ADCE_TM_ENZ_DUTY_CYCLE:1;  // 19 Disable Pulse Stretch testmode to have effect in ADC_CLK
    uint16_t DIS_ADCE_SP_SLEWBOOST:1;   // 20 ADC sp slew boost disbale
    uint16_t Spare1:11;                 // 31:21 Spare1 bits
};

union ASYSCTL_REFBUFCONFIGCDE_REG {
    uint32_t  all;
    struct  ASYSCTL_REFBUFCONFIGCDE_BITS  bit;
};

struct ASYSCTL_INTERNALTESTCTL_BITS {   // bits description
    uint16_t TESTSEL:6;                 // 5:0 Test Select
    uint16_t rsvd1:3;                   // 8:6 Reserved
    uint16_t rsvd2:3;                   // 11:9 Reserved
    uint16_t rsvd3:4;                   // 15:12 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union ASYSCTL_INTERNALTESTCTL_REG {
    uint32_t  all;
    struct  ASYSCTL_INTERNALTESTCTL_BITS  bit;
};

struct ASYSCTL_CONFIGLOCK_BITS {        // bits description
    uint16_t LOCKBIT:1;                 // 0 Locks analog subsystem config
    uint16_t AGPIOFILTER:1;             // 1 Locks AGPIOFILTER Register
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t AGPIOCTRL:1;               // 3 Locks all AGPIOCTRL Register
    uint16_t rsvd2:1;                   // 4 Reserved
    uint16_t rsvd3:1;                   // 5 Reserved
    uint16_t rsvd4:1;                   // 6 Reserved
    uint16_t rsvd5:9;                   // 15:7 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union ASYSCTL_CONFIGLOCK_REG {
    uint32_t  all;
    struct  ASYSCTL_CONFIGLOCK_BITS  bit;
};

struct ASYSCTL_TSNSCTL_BITS {           // bits description
    uint16_t ENABLE:1;                  // 0 Temperature Sensor Enable
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_TSNSCTL_REG {
    uint32_t  all;
    struct  ASYSCTL_TSNSCTL_BITS  bit;
};

struct ASYSCTL_ANAREFCTL_BITS {         // bits description
    uint16_t ANAREFABSEL:1;             // 0 Analog Reference ADC-A/B Select
    uint16_t ANAREFCDESEL:1;            // 1 Analog Reference ADC-C/D/E Select
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:3;                   // 7:5 Reserved
    uint16_t ANAREFAB_2P5SEL:1;         // 8 Analog Reference Select
    uint16_t ANAREFCDE_2P5SEL:1;        // 9 Analog Reference B Select
    uint16_t rsvd5:1;                   // 10 Reserved
    uint16_t rsvd6:3;                   // 13:11 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:16;                  // 31:16 Reserved
};

union ASYSCTL_ANAREFCTL_REG {
    uint32_t  all;
    struct  ASYSCTL_ANAREFCTL_BITS  bit;
};

struct ASYSCTL_VREGCTL_BITS {           // bits description
    uint16_t PWRDNVREG:1;               // 0 Power down internal voltage regulator
    uint16_t rsvd1:14;                  // 14:1 Reserved
    uint16_t ENMASK:1;                  // 15 Enable VMON function mask on a TRIM load
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_VREGCTL_REG {
    uint32_t  all;
    struct  ASYSCTL_VREGCTL_BITS  bit;
};

struct ASYSCTL_VMONCTL_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:6;                   // 7:2 Reserved
    uint16_t BORLVMONDIS:1;             // 8 Disable BORL(ow) feature on VDDIO
    uint16_t rsvd4:7;                   // 15:9 Reserved
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union ASYSCTL_VMONCTL_REG {
    uint32_t  all;
    struct  ASYSCTL_VMONCTL_BITS  bit;
};

struct ASYSCTL_CMPHPMXSEL_BITS {        // bits description
    uint16_t CMP1HPMXSEL:3;             // 2:0 CMP1HPMXSEL bits
    uint16_t CMP2HPMXSEL:3;             // 5:3 CMP2HPMXSEL bits
    uint16_t CMP3HPMXSEL:3;             // 8:6 CMP3HPMXSEL bits
    uint16_t CMP4HPMXSEL:3;             // 11:9 CMP4HPMXSEL bits
    uint16_t CMP5HPMXSEL:3;             // 14:12 CMP5HPMXSEL bits
    uint32_t CMP6HPMXSEL:3;             // 17:15 CMP6HPMXSEL bits
    uint16_t CMP7HPMXSEL:3;             // 20:18 CMP7HPMXSEL bits
    uint16_t CMP8HPMXSEL:3;             // 23:21 CMP8HPMXSEL bits
    uint16_t CMP9HPMXSEL:3;             // 26:24 CMP9HPMXSEL bits
    uint16_t CMP10HPMXSEL:3;            // 29:27 CMP10HPMXSEL bits
    uint16_t rsvd1:2;                   // 31:30 Reserved
};

union ASYSCTL_CMPHPMXSEL_REG {
    uint32_t  all;
    struct  ASYSCTL_CMPHPMXSEL_BITS  bit;
};

struct ASYSCTL_CMPHPMXSEL1_BITS {       // bits description
    uint16_t CMP11HPMXSEL:3;            // 2:0 CMP11HPMXSEL bits
    uint16_t CMP12HPMXSEL:3;            // 5:3 CMP12HPMXSEL bits
    uint16_t rsvd1:3;                   // 8:6 Reserved
    uint16_t rsvd2:3;                   // 11:9 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t rsvd5:2;                   // 17:16 Reserved
    uint16_t rsvd6:3;                   // 20:18 Reserved
    uint16_t rsvd7:3;                   // 23:21 Reserved
    uint16_t rsvd8:3;                   // 26:24 Reserved
    uint16_t rsvd9:3;                   // 29:27 Reserved
    uint16_t rsvd10:2;                  // 31:30 Reserved
};

union ASYSCTL_CMPHPMXSEL1_REG {
    uint32_t  all;
    struct  ASYSCTL_CMPHPMXSEL1_BITS  bit;
};

struct ASYSCTL_CMPLPMXSEL_BITS {        // bits description
    uint16_t CMP1LPMXSEL:3;             // 2:0 CMP1LPMXSEL bits
    uint16_t CMP2LPMXSEL:3;             // 5:3 CMP2LPMXSEL bits
    uint16_t CMP3LPMXSEL:3;             // 8:6 CMP3LPMXSEL bits
    uint16_t CMP4LPMXSEL:3;             // 11:9 CMP4LPMXSEL bits
    uint16_t CMP5LPMXSEL:3;             // 14:12 CMP5LPMXSEL bits
    uint32_t CMP6LPMXSEL:3;             // 17:15 CMP6LPMXSEL bits
    uint16_t CMP7LPMXSEL:3;             // 20:18 CMP7LPMXSEL bits
    uint16_t CMP8LPMXSEL:3;             // 23:21 CMP8LPMXSEL bits
    uint16_t CMP9LPMXSEL:3;             // 26:24 CMP9LPMXSEL bits
    uint16_t CMP10LPMXSEL:3;            // 29:27 CMP10LPMXSEL bits
    uint16_t rsvd1:2;                   // 31:30 Reserved
};

union ASYSCTL_CMPLPMXSEL_REG {
    uint32_t  all;
    struct  ASYSCTL_CMPLPMXSEL_BITS  bit;
};

struct ASYSCTL_CMPLPMXSEL1_BITS {       // bits description
    uint16_t CMP11LPMXSEL:3;            // 2:0 CMP11LPMXSEL bits
    uint16_t CMP12LPMXSEL:3;            // 5:3 CMP12LPMXSEL bits
    uint16_t rsvd1:3;                   // 8:6 Reserved
    uint16_t rsvd2:3;                   // 11:9 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t rsvd5:2;                   // 17:16 Reserved
    uint16_t rsvd6:3;                   // 20:18 Reserved
    uint16_t rsvd7:3;                   // 23:21 Reserved
    uint16_t rsvd8:3;                   // 26:24 Reserved
    uint16_t rsvd9:3;                   // 29:27 Reserved
    uint16_t rsvd10:2;                  // 31:30 Reserved
};

union ASYSCTL_CMPLPMXSEL1_REG {
    uint32_t  all;
    struct  ASYSCTL_CMPLPMXSEL1_BITS  bit;
};

struct ASYSCTL_CMPHNMXSEL_BITS {        // bits description
    uint16_t CMP1HNMXSEL:1;             // 0 CMP1HNMXSEL bits
    uint16_t CMP2HNMXSEL:1;             // 1 CMP2HNMXSEL bits
    uint16_t CMP3HNMXSEL:1;             // 2 CMP3HNMXSEL bits
    uint16_t CMP4HNMXSEL:1;             // 3 CMP4HNMXSEL bits
    uint16_t CMP5HNMXSEL:1;             // 4 CMP5HNMXSEL bits
    uint16_t CMP6HNMXSEL:1;             // 5 CMP6HNMXSEL bits
    uint16_t CMP7HNMXSEL:1;             // 6 CMP7HNMXSEL bits
    uint16_t CMP8HNMXSEL:1;             // 7 CMP8HNMXSEL bits
    uint16_t CMP9HNMXSEL:1;             // 8 CMP9HNMXSEL bits
    uint16_t CMP10HNMXSEL:1;            // 9 CMP10HNMXSEL bits
    uint16_t CMP11HNMXSEL:1;            // 10 CMP11HNMXSEL bits
    uint16_t CMP12HNMXSEL:1;            // 11 CMP12HNMXSEL bits
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_CMPHNMXSEL_REG {
    uint32_t  all;
    struct  ASYSCTL_CMPHNMXSEL_BITS  bit;
};

struct ASYSCTL_CMPLNMXSEL_BITS {        // bits description
    uint16_t CMP1LNMXSEL:1;             // 0 CMP1LNMXSEL bits
    uint16_t CMP2LNMXSEL:1;             // 1 CMP2LNMXSEL bits
    uint16_t CMP3LNMXSEL:1;             // 2 CMP3LNMXSEL bits
    uint16_t CMP4LNMXSEL:1;             // 3 CMP4LNMXSEL bits
    uint16_t CMP5LNMXSEL:1;             // 4 CMP5LNMXSEL bits
    uint16_t CMP6LNMXSEL:1;             // 5 CMP6LNMXSEL bits
    uint16_t CMP7LNMXSEL:1;             // 6 CMP7LNMXSEL bits
    uint16_t CMP8LNMXSEL:1;             // 7 CMP8LNMXSEL bits
    uint16_t CMP9LNMXSEL:1;             // 8 CMP9LNMXSEL bits
    uint16_t CMP10LNMXSEL:1;            // 9 CMP10LNMXSEL bits
    uint16_t CMP11LNMXSEL:1;            // 10 CMP11LNMXSEL bits
    uint16_t CMP12LNMXSEL:1;            // 11 CMP12LNMXSEL bits
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_CMPLNMXSEL_REG {
    uint32_t  all;
    struct  ASYSCTL_CMPLNMXSEL_BITS  bit;
};

struct ASYSCTL_LOCK_BITS {              // bits description
    uint16_t TSNSCTL:1;                 // 0 TSNSCTL Register lock bit
    uint16_t ANAREFCTL:1;               // 1 ANAREFCTL Register lock bit
    uint16_t VMONCTL:1;                 // 2 VMONCTL Register lock bit
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t rsvd2:1;                   // 4 Reserved
    uint16_t CMPHPMXSEL:1;              // 5 CMPHPMXSEL Register lock bit
    uint16_t CMPLPMXSEL:1;              // 6 CMPLPMXSEL Register lock bit
    uint16_t CMPHNMXSEL:1;              // 7 CMPHNMXSEL Register lock bit
    uint16_t CMPLNMXSEL:1;              // 8 CMPLNMXSEL Register lock bit
    uint16_t VREGCTL:1;                 // 9 VREGCTL Register lock bit
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t CMPHPMXSEL1:1;             // 11 CMPHPMXSEL1 Register lock bit
    uint16_t CMPLPMXSEL1:1;             // 12 CMPLPMXSEL1 Register lock bit
    uint16_t rsvd4:3;                   // 15:13 Reserved
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union ASYSCTL_LOCK_REG {
    uint32_t  all;
    struct  ASYSCTL_LOCK_BITS  bit;
};

struct ASYSCTL_IODRVSEL_BITS {          // bits description
    uint16_t GPIO10:1;                  // 0 Drive select for GPIO10
    uint16_t GPIO15:1;                  // 1 Drive select for GPIO15
    uint16_t GPIO18:1;                  // 2 Drive select for GPIO18
    uint16_t GPIO22:1;                  // 3 Drive select for GPIO22
    uint16_t GPIO23:1;                  // 4 Drive select for GPIO23
    uint16_t GPIO29:1;                  // 5 Drive select for GPIO29
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_IODRVSEL_REG {
    uint32_t  all;
    struct  ASYSCTL_IODRVSEL_BITS  bit;
};

struct ASYSCTL_IOMODESEL_BITS {         // bits description
    uint16_t GPIO10:1;                  // 0 Mode select for GPIO10
    uint16_t GPIO15:1;                  // 1 Mode select for GPIO15
    uint16_t GPIO18:1;                  // 2 Mode select for GPIO18
    uint16_t GPIO22:1;                  // 3 Mode select for GPIO22
    uint16_t GPIO23:1;                  // 4 Mode select for GPIO23
    uint16_t GPIO29:1;                  // 5 Mode select for GPIO29
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_IOMODESEL_REG {
    uint32_t  all;
    struct  ASYSCTL_IOMODESEL_BITS  bit;
};

struct ASYSCTL_AGPIOFILTER_BITS {       // bits description
    uint16_t FILTER:2;                  // 1:0 AGPIOFILTER Control for filter ALL AGPIO pins
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t rsvd2:2;                   // 9:8 Reserved
    uint16_t rsvd3:6;                   // 15:10 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union ASYSCTL_AGPIOFILTER_REG {
    uint32_t  all;
    struct  ASYSCTL_AGPIOFILTER_BITS  bit;
};

struct ASYSCTL_AGPIOCTRLH_BITS {        // bits description
    uint16_t GPIO224:1;                 // 0 AGPIOCTRL for GPIO224
    uint16_t GPIO225:1;                 // 1 AGPIOCTRL for GPIO225
    uint16_t GPIO226:1;                 // 2 AGPIOCTRL for GPIO226
    uint16_t GPIO227:1;                 // 3 AGPIOCTRL for GPIO227
    uint16_t GPIO228:1;                 // 4 AGPIOCTRL for GPIO228
    uint16_t GPIO229:1;                 // 5 AGPIOCTRL for GPIO229
    uint16_t GPIO230:1;                 // 6 AGPIOCTRL for GPIO230
    uint16_t GPIO231:1;                 // 7 AGPIOCTRL for GPIO231
    uint16_t GPIO232:1;                 // 8 AGPIOCTRL for GPIO232
    uint16_t GPIO233:1;                 // 9 AGPIOCTRL for GPIO233
    uint16_t GPIO234:1;                 // 10 AGPIOCTRL for GPIO234
    uint16_t GPIO235:1;                 // 11 AGPIOCTRL for GPIO235
    uint16_t GPIO236:1;                 // 12 AGPIOCTRL for GPIO236
    uint16_t GPIO237:1;                 // 13 AGPIOCTRL for GPIO237
    uint16_t GPIO238:1;                 // 14 AGPIOCTRL for GPIO238
    uint16_t GPIO239:1;                 // 15 AGPIOCTRL for GPIO239
    uint16_t GPIO240:1;                 // 16 AGPIOCTRL for GPIO240
    uint16_t GPIO241:1;                 // 17 AGPIOCTRL for GPIO241
    uint16_t GPIO242:1;                 // 18 AGPIOCTRL for GPIO242
    uint16_t GPIO243:1;                 // 19 AGPIOCTRL for GPIO243
    uint16_t GPIO244:1;                 // 20 AGPIOCTRL for GPIO244
    uint16_t GPIO245:1;                 // 21 AGPIOCTRL for GPIO245
    uint16_t GPIO246:1;                 // 22 AGPIOCTRL for GPIO246
    uint16_t GPIO247:1;                 // 23 AGPIOCTRL for GPIO247
    uint16_t GPIO248:1;                 // 24 AGPIOCTRL for GPIO248
    uint16_t GPIO249:1;                 // 25 AGPIOCTRL for GPIO249
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union ASYSCTL_AGPIOCTRLH_REG {
    uint32_t  all;
    struct  ASYSCTL_AGPIOCTRLH_BITS  bit;
};

struct ASYSCTL_PARITY_TEST_BITS {       // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity test enable configuration
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_PARITY_TEST_REG {
    uint32_t  all;
    struct  ASYSCTL_PARITY_TEST_BITS  bit;
};

struct ANALOG_SUBSYS_REGS {
    uint8_t                                  rsvd1[68];                    // Reserved
    union   ASYSCTL_PMMVREGTRIM_REG          PMMVREGTRIM;                  // Power Management Module VREG Trim Register
    uint8_t                                  rsvd2[40];                    // Reserved
    union   ASYSCTL_CTLTRIMSTS_REG           CTLTRIMSTS;                   // HWCTL TRIM Error Status register
    uint8_t                                  rsvd3[224];                   // Reserved
    union   ASYSCTL_REFBUFCONFIGCDE_REG      REFBUFCONFIGCDE;              // Config register for analog reference CDE
    uint8_t                                  rsvd4[80];                    // Reserved
    union   ASYSCTL_INTERNALTESTCTL_REG      INTERNALTESTCTL;              // INTERNALTEST Node Control Register
    uint8_t                                  rsvd5[60];                    // Reserved
    union   ASYSCTL_CONFIGLOCK_REG           CONFIGLOCK;                   // Lock Register for all the config registers.
    union   ASYSCTL_TSNSCTL_REG              TSNSCTL;                      // Temperature Sensor Control Register
    uint8_t                                  rsvd6[28];                    // Reserved
    union   ASYSCTL_ANAREFCTL_REG            ANAREFCTL;                    // Analog Reference Control Register.
    uint8_t                                  rsvd7[4];                     // Reserved
    union   ASYSCTL_VREGCTL_REG              VREGCTL;                      // Voltage Regulator Control Register
    uint8_t                                  rsvd8[20];                    // Reserved
    union   ASYSCTL_VMONCTL_REG              VMONCTL;                      // Voltage Monitor Control Register
    uint8_t                                  rsvd9[60];                    // Reserved
    union   ASYSCTL_CMPHPMXSEL_REG           CMPHPMXSEL;                   // Bits to select one of the many sources on CopmHP inputs. Refer to Pimux diagram for details.
    union   ASYSCTL_CMPHPMXSEL1_REG          CMPHPMXSEL1;                  // Bits to select one of the many sources on CopmHP inputs. Refer to Pimux diagram for details.
    union   ASYSCTL_CMPLPMXSEL_REG           CMPLPMXSEL;                   // Bits to select one of the many sources on CopmLP inputs. Refer to Pimux diagram for details.
    union   ASYSCTL_CMPLPMXSEL1_REG          CMPLPMXSEL1;                  // Bits to select one of the many sources on CopmLP inputs. Refer to Pimux diagram for details.
    union   ASYSCTL_CMPHNMXSEL_REG           CMPHNMXSEL;                   // Bits to select one of the many sources on CopmHN inputs. Refer to Pimux diagram for details.
    union   ASYSCTL_CMPLNMXSEL_REG           CMPLNMXSEL;                   // Bits to select one of the many sources on CopmLN inputs. Refer to Pimux diagram for details.
    uint8_t                                  rsvd10[16];                   // Reserved
    union   ASYSCTL_LOCK_REG                 LOCK;                         // Lock Register
    uint8_t                                  rsvd11[448];                  // Reserved
    union   ASYSCTL_IODRVSEL_REG             IODRVSEL;                     // 5V FS IO Drive strength select register
    union   ASYSCTL_IOMODESEL_REG            IOMODESEL;                    // PMBUS IO Mode select register
    uint8_t                                  rsvd12[4];                    // Reserved
    union   ASYSCTL_AGPIOFILTER_REG          AGPIOFILTER;                  // AGPIO Filter Control Register
    uint8_t                                  rsvd13[36];                   // Reserved
    union   ASYSCTL_AGPIOCTRLH_REG           AGPIOCTRLH;                   // AGPIO Control Register
    uint8_t                                  rsvd14[36];                   // Reserved
    union   ASYSCTL_PARITY_TEST_REG          PARITY_TEST;                  // Enables parity test
};

struct ASYSCTL_ADCSOCFRCGB_BITS {       // bits description
    uint16_t SOC0:1;                    // 0 Generate synchronous SW trigger for SOC0
    uint16_t SOC1:1;                    // 1 Generate synchronous SW trigger for SOC1
    uint16_t SOC2:1;                    // 2 Generate synchronous SW trigger for SOC2
    uint16_t SOC3:1;                    // 3 Generate synchronous SW trigger for SOC3
    uint16_t SOC4:1;                    // 4 Generate synchronous SW trigger for SOC4
    uint16_t SOC5:1;                    // 5 Generate synchronous SW trigger for SOC5
    uint16_t SOC6:1;                    // 6 Generate synchronous SW trigger for SOC6
    uint16_t SOC7:1;                    // 7 Generate synchronous SW trigger for SOC7
    uint16_t SOC8:1;                    // 8 Generate synchronous SW trigger for SOC8
    uint16_t SOC9:1;                    // 9 Generate synchronous SW trigger for SOC9
    uint16_t SOC10:1;                   // 10 Generate synchronous SW trigger for SOC10
    uint16_t SOC11:1;                   // 11 Generate synchronous SW trigger for SOC11
    uint16_t SOC12:1;                   // 12 Generate synchronous SW trigger for SOC12
    uint16_t SOC13:1;                   // 13 Generate synchronous SW trigger for SOC13
    uint16_t SOC14:1;                   // 14 Generate synchronous SW trigger for SOC14
    uint16_t SOC15:1;                   // 15 Generate synchronous SW trigger for SOC15
    uint16_t SOC16:1;                   // 16 Generate synchronous SW trigger for SOC16
    uint16_t SOC17:1;                   // 17 Generate synchronous SW trigger for SOC17
    uint16_t SOC18:1;                   // 18 Generate synchronous SW trigger for SOC18
    uint16_t SOC19:1;                   // 19 Generate synchronous SW trigger for SOC19
    uint16_t SOC20:1;                   // 20 Generate synchronous SW trigger for SOC20
    uint16_t SOC21:1;                   // 21 Generate synchronous SW trigger for SOC21
    uint16_t SOC22:1;                   // 22 Generate synchronous SW trigger for SOC22
    uint16_t SOC23:1;                   // 23 Generate synchronous SW trigger for SOC23
    uint16_t SOC24:1;                   // 24 Generate synchronous SW trigger for SOC24
    uint16_t SOC25:1;                   // 25 Generate synchronous SW trigger for SOC25
    uint16_t SOC26:1;                   // 26 Generate synchronous SW trigger for SOC26
    uint16_t SOC27:1;                   // 27 Generate synchronous SW trigger for SOC27
    uint16_t SOC28:1;                   // 28 Generate synchronous SW trigger for SOC28
    uint16_t SOC29:1;                   // 29 Generate synchronous SW trigger for SOC29
    uint16_t SOC30:1;                   // 30 Generate synchronous SW trigger for SOC30
    uint16_t SOC31:1;                   // 31 Generate synchronous SW trigger for SOC31
};

union ASYSCTL_ADCSOCFRCGB_REG {
    uint32_t  all;
    struct  ASYSCTL_ADCSOCFRCGB_BITS  bit;
};

struct ASYSCTL_ADCSOCFRCGBSEL_BITS {    // bits description
    uint16_t ADCA:1;                    // 0 Generate synchronous SW trigger for ADCA
    uint16_t ADCB:1;                    // 1 Generate synchronous SW trigger for ADCB
    uint16_t ADCC:1;                    // 2 Generate synchronous SW trigger for ADCC
    uint16_t ADCD:1;                    // 3 Generate synchronous SW trigger for ADCD
    uint16_t ADCE:1;                    // 4 Generate synchronous SW trigger for ADCE
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_ADCSOCFRCGBSEL_REG {
    uint32_t  all;
    struct  ASYSCTL_ADCSOCFRCGBSEL_BITS  bit;
};

struct ASYSCTL_PARITY_TEST_ALT1_BITS {  // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity test enable configuration
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ASYSCTL_PARITY_TEST_ALT1_REG {
    uint32_t  all;
    struct  ASYSCTL_PARITY_TEST_ALT1_BITS  bit;
};

struct ADC_GLOBAL_REGS {
    union   ASYSCTL_ADCSOCFRCGB_REG          ADCSOCFRCGB;                  // ADC Global SOC Force
    union   ASYSCTL_ADCSOCFRCGBSEL_REG       ADCSOCFRCGBSEL;               // ADC Global SOC Force Select
    union   ASYSCTL_PARITY_TEST_ALT1_REG     PARITY_TEST_ALT1;             // Enables parity test
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
