//###########################################################################
//
// FILE:    hwbf_sysctl.h
//
// TITLE:   Definitions for the SYSCTL registers.
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

#ifndef HWBF_SYSCTL_H
#define HWBF_SYSCTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// SYSCTL Individual Register Bit Definitions:

struct SYSCTL_DEVCFGLOCK1_BITS {        // bits description
    uint16_t PER0SYSCONFIG:1;           // 0 Lock bit for PER0SYSCONFIG register
    uint16_t PER1SYSCONFIG:1;           // 1 Lock bit for PER1SYSCONFIG register
    uint16_t PER2SYSCONFIG:1;           // 2 Lock bit for PER2SYSCONFIG register
    uint16_t PER3SYSCONFIG:1;           // 3 Lock bit for PER3SYSCONFIG register
    uint16_t PER4SYSCONFIG:1;           // 4 Lock bit for PER4SYSCONFIG register
    uint16_t PER5SYSCONFIG:1;           // 5 Lock bit for PER5SYSCONFIG register
    uint16_t PER6SYSCONFIG:1;           // 6 Lock bit for PER6SYSCONFIG register
    uint16_t PER7SYSCONFIG:1;           // 7 Lock bit for PER7SYSCONFIG register
    uint16_t PER8SYSCONFIG:1;           // 8 Lock bit for PER8SYSCONFIG register
    uint16_t PER9SYSCONFIG:1;           // 9 Lock bit for PER9SYSCONFIG register
    uint16_t PER10SYSCONFIG:1;          // 10 Lock bit for PER10SYSCONFIG register
    uint16_t PER11SYSCONFIG:1;          // 11 Lock bit for PER11SYSCONFIG register
    uint16_t PER12SYSCONFIG:1;          // 12 Lock bit for PER12SYSCONFIG register
    uint16_t PER13SYSCONFIG:1;          // 13 Lock bit for PER13SYSCONFIG register
    uint16_t PER14SYSCONFIG:1;          // 14 Lock bit for PER14SYSCONFIG register
    uint16_t PER15SYSCONFIG:1;          // 15 Lock bit for PER15SYSCONFIG register
    uint16_t PER16SYSCONFIG:1;          // 16 Lock bit for PER16SYSCONFIG register
    uint16_t PER17SYSCONFIG:1;          // 17 Lock bit for PER17SYSCONFIG register
    uint16_t PER18SYSCONFIG:1;          // 18 Lock bit for PER18SYSCONFIG register
    uint16_t PER19SYSCONFIG:1;          // 19 Lock bit for PER19SYSCONFIG register
    uint16_t PER20SYSCONFIG:1;          // 20 Lock bit for PER20SYSCONFIG register
    uint16_t PER21SYSCONFIG:1;          // 21 Lock bit for PER21SYSCONFIG register
    uint16_t PER22SYSCONFIG:1;          // 22 Lock bit for PER22SYSCONFIG register
    uint16_t PER23SYSCONFIG:1;          // 23 Lock bit for PER23SYSCONFIG register
    uint16_t PER24SYSCONFIG:1;          // 24 Lock bit for PER24SYSCONFIG register
    uint16_t PER25SYSCONFIG:1;          // 25 Lock bit for PER25SYSCONFIG register
    uint16_t PER26SYSCONFIG:1;          // 26 Lock bit for PER26SYSCONFIG register
    uint16_t PER27SYSCONFIG:1;          // 27 Lock bit for PER27SYSCONFIG register
    uint16_t PER28SYSCONFIG:1;          // 28 Lock bit for PER28SYSCONFIG register
    uint16_t PER29SYSCONFIG:1;          // 29 Lock bit for PER29SYSCONFIG register
    uint16_t PER30SYSCONFIG:1;          // 30 Lock bit for PER30SYSCONFIG register
    uint16_t PER31SYSCONFIG:1;          // 31 Lock bit for PER31SYSCONFIG register
};

union SYSCTL_DEVCFGLOCK1_REG {
    uint32_t  all;
    struct  SYSCTL_DEVCFGLOCK1_BITS  bit;
};

struct SYSCTL_DEVCFGLOCK2_BITS {        // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t SICCONFIG:1;               // 3 Lock for SICCONFIG
    uint16_t LSEN:1;                    // 4 Lock for LSEN
    uint16_t rsvd4:1;                   // 5 Reserved
    uint16_t ETHERCATCTL:1;             // 6 Lock for ETHERCATCTL
    uint16_t PCLKCR22:1;                // 7 Lock for PCLKCR22
    uint16_t rsvd5:8;                   // 15:8 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_DEVCFGLOCK2_REG {
    uint32_t  all;
    struct  SYSCTL_DEVCFGLOCK2_BITS  bit;
};

struct SYSCTL_DEVCFGLOCK3_BITS {        // bits description
    uint16_t PER32SYSCONFIG:1;          // 0 Lock bit for PER32SYSCONFIG register
    uint16_t PER33SYSCONFIG:1;          // 1 Lock bit for PER33SYSCONFIG register
    uint16_t PER34SYSCONFIG:1;          // 2 Lock bit for PER34SYSCONFIG register
    uint16_t PER35SYSCONFIG:1;          // 3 Lock bit for PER35SYSCONFIG register
    uint16_t PER36SYSCONFIG:1;          // 4 Lock bit for PER36SYSCONFIG register
    uint16_t PER37SYSCONFIG:1;          // 5 Lock bit for PER37SYSCONFIG register
    uint16_t PER38SYSCONFIG:1;          // 6 Lock bit for PER38SYSCONFIG register
    uint16_t PER39SYSCONFIG:1;          // 7 Lock bit for PER39SYSCONFIG register
    uint16_t PER40SYSCONFIG:1;          // 8 Lock bit for PER40SYSCONFIG register
    uint16_t PER41SYSCONFIG:1;          // 9 Lock bit for PER41SYSCONFIG register
    uint16_t PER42SYSCONFIG:1;          // 10 Lock bit for PER42SYSCONFIG register
    uint16_t PER43SYSCONFIG:1;          // 11 Lock bit for PER43SYSCONFIG register
    uint16_t PER44SYSCONFIG:1;          // 12 Lock bit for PER44SYSCONFIG register
    uint16_t PER45SYSCONFIG:1;          // 13 Lock bit for PER45SYSCONFIG register
    uint16_t PER46SYSCONFIG:1;          // 14 Lock bit for PER46SYSCONFIG register
    uint16_t PER47SYSCONFIG:1;          // 15 Lock bit for PER47SYSCONFIG register
    uint16_t PER48SYSCONFIG:1;          // 16 Lock bit for PER48SYSCONFIG register
    uint16_t PER49SYSCONFIG:1;          // 17 Lock bit for PER49SYSCONFIG register
    uint16_t PER50SYSCONFIG:1;          // 18 Lock bit for PER50SYSCONFIG register
    uint16_t PER51SYSCONFIG:1;          // 19 Lock bit for PER51SYSCONFIG register
    uint16_t PER52SYSCONFIG:1;          // 20 Lock bit for PER52SYSCONFIG register
    uint16_t PER53SYSCONFIG:1;          // 21 Lock bit for PER53SYSCONFIG register
    uint16_t PER54SYSCONFIG:1;          // 22 Lock bit for PER54SYSCONFIG register
    uint16_t PER55SYSCONFIG:1;          // 23 Lock bit for PER55SYSCONFIG register
    uint16_t PER56SYSCONFIG:1;          // 24 Lock bit for PER56SYSCONFIG register
    uint16_t PER57SYSCONFIG:1;          // 25 Lock bit for PER57SYSCONFIG register
    uint16_t PER58SYSCONFIG:1;          // 26 Lock bit for PER58SYSCONFIG register
    uint16_t PER59SYSCONFIG:1;          // 27 Lock bit for PER59SYSCONFIG register
    uint16_t PER60SYSCONFIG:1;          // 28 Lock bit for PER60SYSCONFIG register
    uint16_t PER61SYSCONFIG:1;          // 29 Lock bit for PER61SYSCONFIG register
    uint16_t PER62SYSCONFIG:1;          // 30 Lock bit for PER62SYSCONFIG register
    uint16_t PER63SYSCONFIG:1;          // 31 Lock bit for PER63SYSCONFIG register
};

union SYSCTL_DEVCFGLOCK3_REG {
    uint32_t  all;
    struct  SYSCTL_DEVCFGLOCK3_BITS  bit;
};

struct SYSCTL_DEVCFGLOCK4_BITS {        // bits description
    uint16_t PER64SYSCONFIG:1;          // 0 Lock bit for PER64SYSCONFIG register
    uint16_t PER65SYSCONFIG:1;          // 1 Lock bit for PER65SYSCONFIG register
    uint16_t PER66SYSCONFIG:1;          // 2 Lock bit for PER66SYSCONFIG register
    uint16_t PER67SYSCONFIG:1;          // 3 Lock bit for PER67SYSCONFIG register
    uint16_t PER68SYSCONFIG:1;          // 4 Lock bit for PER68SYSCONFIG register
    uint16_t PER69SYSCONFIG:1;          // 5 Lock bit for PER69SYSCONFIG register
    uint16_t PER70SYSCONFIG:1;          // 6 Lock bit for PER70SYSCONFIG register
    uint16_t PER71SYSCONFIG:1;          // 7 Lock bit for PER71SYSCONFIG register
    uint16_t PER72SYSCONFIG:1;          // 8 Lock bit for PER72SYSCONFIG register
    uint16_t PER73SYSCONFIG:1;          // 9 Lock bit for PER73SYSCONFIG register
    uint16_t PER74SYSCONFIG:1;          // 10 Lock bit for PER74SYSCONFIG register
    uint16_t PER75SYSCONFIG:1;          // 11 Lock bit for PER75SYSCONFIG register
    uint16_t PER76SYSCONFIG:1;          // 12 Lock bit for PER76SYSCONFIG register
    uint16_t PER77SYSCONFIG:1;          // 13 Lock bit for PER77SYSCONFIG register
    uint16_t PER78SYSCONFIG:1;          // 14 Lock bit for PER78SYSCONFIG register
    uint16_t PER79SYSCONFIG:1;          // 15 Lock bit for PER79SYSCONFIG register
    uint16_t PER80SYSCONFIG:1;          // 16 Lock bit for PER80SYSCONFIG register
    uint16_t PER81SYSCONFIG:1;          // 17 Lock bit for PER81SYSCONFIG register
    uint16_t PER82SYSCONFIG:1;          // 18 Lock bit for PER82SYSCONFIG register
    uint16_t PER83SYSCONFIG:1;          // 19 Lock bit for PER83SYSCONFIG register
    uint16_t PER84SYSCONFIG:1;          // 20 Lock bit for PER84SYSCONFIG register
    uint16_t PER85SYSCONFIG:1;          // 21 Lock bit for PER85SYSCONFIG register
    uint16_t PER86SYSCONFIG:1;          // 22 Lock bit for PER86SYSCONFIG register
    uint16_t PER87SYSCONFIG:1;          // 23 Lock bit for PER87SYSCONFIG register
    uint16_t PER88SYSCONFIG:1;          // 24 Lock bit for PER88SYSCONFIG register
    uint16_t PER89SYSCONFIG:1;          // 25 Lock bit for PER89SYSCONFIG register
    uint16_t PER90SYSCONFIG:1;          // 26 Lock bit for PER90SYSCONFIG register
    uint16_t PER91SYSCONFIG:1;          // 27 Lock bit for PER91SYSCONFIG register
    uint16_t PER92SYSCONFIG:1;          // 28 Lock bit for PER92SYSCONFIG register
    uint16_t PER93SYSCONFIG:1;          // 29 Lock bit for PER93SYSCONFIG register
    uint16_t PER94SYSCONFIG:1;          // 30 Lock bit for PER94SYSCONFIG register
    uint16_t PER95SYSCONFIG:1;          // 31 Lock bit for PER95SYSCONFIG register
};

union SYSCTL_DEVCFGLOCK4_REG {
    uint32_t  all;
    struct  SYSCTL_DEVCFGLOCK4_BITS  bit;
};

struct SYSCTL_DEVCFGLOCK5_BITS {        // bits description
    uint16_t PER96SYSCONFIG:1;          // 0 Lock bit for PER96SYSCONFIG register
    uint16_t PER97SYSCONFIG:1;          // 1 Lock bit for PER97SYSCONFIG register
    uint16_t PER98SYSCONFIG:1;          // 2 Lock bit for PER98SYSCONFIG register
    uint16_t PER99SYSCONFIG:1;          // 3 Lock bit for PER99SYSCONFIG register
    uint16_t PER100SYSCONFIG:1;         // 4 Lock bit for PER100SYSCONFIG register
    uint16_t PER101SYSCONFIG:1;         // 5 Lock bit for PER101SYSCONFIG register
    uint16_t PER102SYSCONFIG:1;         // 6 Lock bit for PER102SYSCONFIG register
    uint16_t PER103SYSCONFIG:1;         // 7 Lock bit for PER103SYSCONFIG register
    uint16_t PER104SYSCONFIG:1;         // 8 Lock bit for PER104SYSCONFIG register
    uint16_t PER105SYSCONFIG:1;         // 9 Lock bit for PER105SYSCONFIG register
    uint16_t PER106SYSCONFIG:1;         // 10 Lock bit for PER106SYSCONFIG register
    uint16_t PER107SYSCONFIG:1;         // 11 Lock bit for PER107SYSCONFIG register
    uint16_t PER108SYSCONFIG:1;         // 12 Lock bit for PER108SYSCONFIG register
    uint16_t PER109SYSCONFIG:1;         // 13 Lock bit for PER109SYSCONFIG register
    uint16_t PER110SYSCONFIG:1;         // 14 Lock bit for PER110SYSCONFIG register
    uint16_t PER111SYSCONFIG:1;         // 15 Lock bit for PER111SYSCONFIG register
    uint16_t PER112SYSCONFIG:1;         // 16 Lock bit for PER112SYSCONFIG register
    uint16_t PER113SYSCONFIG:1;         // 17 Lock bit for PER113SYSCONFIG register
    uint16_t PER114SYSCONFIG:1;         // 18 Lock bit for PER114SYSCONFIG register
    uint16_t PER115SYSCONFIG:1;         // 19 Lock bit for PER115SYSCONFIG register
    uint16_t PER116SYSCONFIG:1;         // 20 Lock bit for PER116SYSCONFIG register
    uint16_t PER117SYSCONFIG:1;         // 21 Lock bit for PER117SYSCONFIG register
    uint16_t PER118SYSCONFIG:1;         // 22 Lock bit for PER118SYSCONFIG register
    uint16_t PER119SYSCONFIG:1;         // 23 Lock bit for PER119SYSCONFIG register
    uint16_t PER120SYSCONFIG:1;         // 24 Lock bit for PER120SYSCONFIG register
    uint16_t rsvd1:1;                   // 25 Reserved
    uint16_t rsvd2:1;                   // 26 Reserved
    uint16_t rsvd3:1;                   // 27 Reserved
    uint16_t rsvd4:1;                   // 28 Reserved
    uint16_t rsvd5:1;                   // 29 Reserved
    uint16_t rsvd6:1;                   // 30 Reserved
    uint16_t rsvd7:1;                   // 31 Reserved
};

union SYSCTL_DEVCFGLOCK5_REG {
    uint32_t  all;
    struct  SYSCTL_DEVCFGLOCK5_BITS  bit;
};

struct SYSCTL_PARTIDL_BITS {            // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint16_t rsvd2:2;                   // 4:3 Reserved
    uint16_t rsvd3:1;                   // 5 Reserved
    uint16_t QUAL:2;                    // 7:6 Qualification Status
    uint16_t PIN_COUNT:3;               // 10:8 Device Pin Count
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:2;                   // 14:13 Reserved
    uint16_t rsvd7:1;                   // 15 Reserved
    uint16_t FLASH_SIZE:8;              // 23:16 FLASH_SIZE
    uint16_t rsvd8:4;                   // 27:24 Reserved
    uint16_t PARTID_FORMAT_REV:4;       // 31:28 PARTID_FORMAT_REV
};

union SYSCTL_PARTIDL_REG {
    uint32_t  all;
    struct  SYSCTL_PARTIDL_BITS  bit;
};

struct SYSCTL_PARTIDH_BITS {            // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t rsvd2:4;                   // 7:4 Reserved
    uint16_t FAMILY:8;                  // 15:8 Device family
    uint16_t PARTNO:8;                  // 23:16 Device part number
    uint16_t DEVICE_CLASS_ID:8;         // 31:24 Device class ID
};

union SYSCTL_PARTIDH_REG {
    uint32_t  all;
    struct  SYSCTL_PARTIDH_BITS  bit;
};

struct SYSCTL_REVID_BITS {              // bits description
    uint16_t REVID:16;                  // 15:0 Device Revision ID. This is specific to the Device
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union SYSCTL_REVID_REG {
    uint32_t  all;
    struct  SYSCTL_REVID_BITS  bit;
};

struct SYSCTL_MCUCNF1_BITS {            // bits description
    uint16_t EMIF1:1;                   // 0 EMIF1 Present
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF1_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF1_BITS  bit;
};

struct SYSCTL_MCUCNF2_BITS {            // bits description
    uint16_t EPWM1:1;                   // 0 EPWM1 Present
    uint16_t EPWM2:1;                   // 1 EPWM2 Present
    uint16_t EPWM3:1;                   // 2 EPWM3 Present
    uint16_t EPWM4:1;                   // 3 EPWM4 Present
    uint16_t EPWM5:1;                   // 4 EPWM5 Present
    uint16_t EPWM6:1;                   // 5 EPWM6 Present
    uint16_t EPWM7:1;                   // 6 EPWM7 Present
    uint16_t EPWM8:1;                   // 7 EPWM8 Present
    uint16_t EPWM9:1;                   // 8 EPWM9 Present
    uint16_t EPWM10:1;                  // 9 EPWM10 Present
    uint16_t EPWM11:1;                  // 10 EPWM11 Present
    uint16_t EPWM12:1;                  // 11 EPWM12 Present
    uint16_t EPWM13:1;                  // 12 EPWM13 Present
    uint16_t EPWM14:1;                  // 13 EPWM14 Present
    uint16_t EPWM15:1;                  // 14 EPWM15 Present
    uint16_t EPWM16:1;                  // 15 EPWM16 Present
    uint16_t EPWM17:1;                  // 16 EPWM17 Present
    uint16_t EPWM18:1;                  // 17 EPWM18 Present
    uint16_t rsvd1:14;                  // 31:18 Reserved
};

union SYSCTL_MCUCNF2_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF2_BITS  bit;
};

struct SYSCTL_MCUCNF4_BITS {            // bits description
    uint16_t EQEP1:1;                   // 0 EQEP1 Present
    uint16_t EQEP2:1;                   // 1 EQEP2 Present
    uint16_t EQEP3:1;                   // 2 EQEP3 Present
    uint16_t EQEP4:1;                   // 3 EQEP4 Present
    uint16_t EQEP5:1;                   // 4 EQEP5 Present
    uint16_t EQEP6:1;                   // 5 EQEP6 Present
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF4_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF4_BITS  bit;
};

struct SYSCTL_MCUCNF7_BITS {            // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:12;                  // 15:4 Reserved
    uint16_t UART_A:1;                  // 16 UART_A Present
    uint16_t UART_B:1;                  // 17 UART_B Present
    uint16_t UART_C:1;                  // 18 UART_C Present
    uint16_t UART_D:1;                  // 19 UART_D Present
    uint16_t UART_E:1;                  // 20 UART_E Present
    uint16_t UART_F:1;                  // 21 UART_F Present
    uint16_t rsvd6:10;                  // 31:22 Reserved
};

union SYSCTL_MCUCNF7_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF7_BITS  bit;
};

struct SYSCTL_MCUCNF10_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t MCAN_A:1;                  // 4 MCAN_A Present
    uint16_t MCAN_B:1;                  // 5 MCAN_B Present
    uint16_t MCAN_C:1;                  // 6 MCAN_C Present
    uint16_t MCAN_D:1;                  // 7 MCAN_D Present
    uint16_t MCAN_E:1;                  // 8 MCAN_E Present
    uint16_t MCAN_F:1;                  // 9 MCAN_F Present
    uint16_t rsvd5:6;                   // 15:10 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF10_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF10_BITS  bit;
};

struct SYSCTL_MCUCNF13_BITS {           // bits description
    uint16_t ADC_A:1;                   // 0 ADC_A Present
    uint16_t ADC_B:1;                   // 1 ADC_B Present
    uint16_t ADC_C:1;                   // 2 ADC_C Present
    uint16_t ADC_D:1;                   // 3 ADC_D Present
    uint16_t ADC_E:1;                   // 4 ADC_E Present
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t rsvd2:10;                  // 15:6 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF13_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF13_BITS  bit;
};

struct SYSCTL_MCUCNF14_BITS {           // bits description
    uint16_t CMPSS1:1;                  // 0 CMPSS1 Present
    uint16_t CMPSS2:1;                  // 1 CMPSS2 Present
    uint16_t CMPSS3:1;                  // 2 CMPSS3 Present
    uint16_t CMPSS4:1;                  // 3 CMPSS4 Present
    uint16_t CMPSS5:1;                  // 4 CMPSS5 Present
    uint16_t CMPSS6:1;                  // 5 CMPSS6 Present
    uint16_t CMPSS7:1;                  // 6 CMPSS7 Present
    uint16_t CMPSS8:1;                  // 7 CMPSS8 Present
    uint16_t CMPSS9:1;                  // 8 CMPSS9 Present
    uint16_t CMPSS10:1;                 // 9 CMPSS10 Present
    uint16_t CMPSS11:1;                 // 10 CMPSS11 Present
    uint16_t CMPSS12:1;                 // 11 CMPSS12 Present
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF14_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF14_BITS  bit;
};

struct SYSCTL_MCUCNF16_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:12;                  // 15:4 Reserved
    uint16_t DAC_A:1;                   // 16 DAC_A Present
    uint16_t DAC_B:1;                   // 17 DAC_B Present
    uint16_t rsvd6:1;                   // 18 Reserved
    uint16_t rsvd7:1;                   // 19 Reserved
    uint16_t rsvd8:12;                  // 31:20 Reserved
};

union SYSCTL_MCUCNF16_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF16_BITS  bit;
};

struct SYSCTL_MCUCNF17_BITS {           // bits description
    uint16_t CLB1:1;                    // 0 CLB1 Present
    uint16_t CLB2:1;                    // 1 CLB2 Present
    uint16_t CLB3:1;                    // 2 CLB3 Present
    uint16_t CLB4:1;                    // 3 CLB4 Present
    uint16_t CLB5:1;                    // 4 CLB5 Present
    uint16_t CLB6:1;                    // 5 CLB6 Present
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF17_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF17_BITS  bit;
};

struct SYSCTL_MCUCNF18_BITS {           // bits description
    uint16_t FSITX_A:1;                 // 0 FSITX_A  Present
    uint16_t FSITX_B:1;                 // 1 FSITX_B  Present
    uint16_t FSITX_C:1;                 // 2 FSITX_C  Present
    uint16_t FSITX_D:1;                 // 3 FSITX_D  Present
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t FSIRX_A:1;                 // 16 FSIRX_A  Present
    uint16_t FSIRX_B:1;                 // 17 FSIRX_B  Present
    uint16_t FSIRX_C:1;                 // 18 FSIRX_C  Present
    uint16_t FSIRX_D:1;                 // 19 FSIRX_D  Present
    uint16_t rsvd2:12;                  // 31:20 Reserved
};

union SYSCTL_MCUCNF18_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF18_BITS  bit;
};

struct SYSCTL_MCUCNF19_BITS {           // bits description
    uint16_t LIN_A:1;                   // 0 LIN_A Present
    uint16_t LIN_B:1;                   // 1 LIN_B Present
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:12;                  // 15:4 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF19_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF19_BITS  bit;
};

struct SYSCTL_MCUCNF23_BITS {           // bits description
    uint16_t ETHERCAT:1;                // 0 ETHERCAT
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF23_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF23_BITS  bit;
};

struct SYSCTL_MCUCNF26_BITS {           // bits description
    uint16_t AES:6;                     // 5:0 AES Present
    uint16_t SHA:6;                     // 11:6 SHA Present
    uint32_t PKA:6;                     // 17:12 PKA Present
    uint16_t TRNG:6;                    // 23:18 TRNG Present
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union SYSCTL_MCUCNF26_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF26_BITS  bit;
};

struct SYSCTL_MCUCNF31_BITS {           // bits description
    uint16_t SM2:6;                     // 5:0 SM2 Present
    uint16_t SM3:6;                     // 11:6 SM3 Present
    uint32_t SM4:6;                     // 17:12 SM4 Present
    uint16_t rsvd1:14;                  // 31:18 Reserved
};

union SYSCTL_MCUCNF31_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF31_BITS  bit;
};

struct SYSCTL_MCUCNF64_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t CPU2:1;                    // 3 CPU2SS Present on this device
    uint16_t CPU3:1;                    // 4 CPU3SS Present on this device
    uint16_t rsvd4:1;                   // 5 Reserved
    uint16_t rsvd5:1;                   // 6 Reserved
    uint16_t rsvd6:1;                   // 7 Reserved
    uint16_t rsvd7:1;                   // 8 Reserved
    uint16_t rsvd8:1;                   // 9 Reserved
    uint16_t rsvd9:1;                   // 10 Reserved
    uint16_t rsvd10:5;                  // 15:11 Reserved
    uint16_t rsvd11:16;                 // 31:16 Reserved
};

union SYSCTL_MCUCNF64_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF64_BITS  bit;
};

struct SYSCTL_MCUCNF65_BITS {           // bits description
    uint16_t CPA0:1;                    // 0 CPA0 Memory Present
    uint16_t CPA1:1;                    // 1 CPA1 Memory Present
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t LPA0:1;                    // 4 LPA0 Memory Present
    uint16_t LPA1:1;                    // 5 LPA1 Memory Present
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t LDA0:1;                    // 8 LDA0 Memory Present
    uint16_t LDA1:1;                    // 9 LDA1 Memory Present
    uint16_t LDA2:1;                    // 10 LDA2 Memory Present
    uint16_t LDA3:1;                    // 11 LDA3 Memory Present
    uint16_t LDA4:1;                    // 12 LDA4 Memory Present
    uint16_t LDA5:1;                    // 13 LDA5 Memory Present
    uint16_t LDA6:1;                    // 14 LDA6 Memory Present
    uint16_t LDA7:1;                    // 15 LDA7 Memory Present
    uint16_t CDA0:1;                    // 16 CDA0 Memory Present
    uint16_t CDA1:1;                    // 17 CDA1 Memory Present
    uint16_t CDA2:1;                    // 18 CDA2 Memory Present
    uint16_t CDA3:1;                    // 19 CDA3 Memory Present
    uint16_t CDA4:1;                    // 20 CDA4 Memory Present
    uint16_t CDA5:1;                    // 21 CDA5 Memory Present
    uint16_t CDA6:1;                    // 22 CDA6 Memory Present
    uint16_t CDA7:1;                    // 23 CDA7 Memory Present
    uint16_t CDA8:1;                    // 24 CDA8 Memory Present
    uint16_t CDA9:1;                    // 25 CDA9 Memory Present
    uint16_t CDA10:1;                   // 26 CDA10 Memory Present
    uint16_t CDA11:1;                   // 27 CDA11 Memory Present
    uint16_t rsvd5:1;                   // 28 Reserved
    uint16_t rsvd6:1;                   // 29 Reserved
    uint16_t rsvd7:1;                   // 30 Reserved
    uint16_t rsvd8:1;                   // 31 Reserved
};

union SYSCTL_MCUCNF65_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF65_BITS  bit;
};

struct SYSCTL_MCUCNF74_BITS {           // bits description
    uint16_t SECT15_0:1;                // 0 Flash sectors 15_0 present
    uint16_t SECT31_16:1;               // 1 Flash sectors 31_16 present
    uint16_t SECT47_32:1;               // 2 Flash sectors 47_32 present
    uint16_t SECT63_48:1;               // 3 Flash sectors 63_48 present
    uint16_t SECT79_64:1;               // 4 Flash sectors 79_64 present
    uint16_t SECT95_80:1;               // 5 Flash sectors 95_80 present
    uint16_t SECT111_96:1;              // 6 Flash sectors 111_96 present
    uint16_t SECT127_112:1;             // 7 Flash sectors 127_112 present
    uint16_t SECT143_128:1;             // 8 Flash sectors 143_128 present
    uint16_t SECT159_144:1;             // 9 Flash sectors 159_144 present
    uint16_t SECT175_160:1;             // 10 Flash sectors 175_160 present
    uint16_t SECT191_176:1;             // 11 Flash sectors 191_176 present
    uint16_t SECT207_192:1;             // 12 Flash sectors 207_192 present
    uint16_t SECT223_208:1;             // 13 Flash sectors 223_208 present
    uint16_t SECT239_224:1;             // 14 Flash sectors 239_224 present
    uint16_t SECT255_240:1;             // 15 Flash sectors 255_240 present
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF74_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF74_BITS  bit;
};

struct SYSCTL_MCUCNF76_BITS {           // bits description
    uint16_t SECT15_0:1;                // 0 Flash sectors 15_0 present
    uint16_t SECT31_16:1;               // 1 Flash sectors 31_16 present
    uint16_t SECT47_32:1;               // 2 Flash sectors 47_32 present
    uint16_t SECT63_48:1;               // 3 Flash sectors 63_48 present
    uint16_t SECT79_64:1;               // 4 Flash sectors 79_64 present
    uint16_t SECT95_80:1;               // 5 Flash sectors 95_80 present
    uint16_t SECT111_96:1;              // 6 Flash sectors 111_96 present
    uint16_t SECT127_112:1;             // 7 Flash sectors 127_112 present
    uint16_t SECT143_128:1;             // 8 Flash sectors 143_128 present
    uint16_t SECT159_144:1;             // 9 Flash sectors 159_144 present
    uint16_t SECT175_160:1;             // 10 Flash sectors 175_160 present
    uint16_t SECT191_176:1;             // 11 Flash sectors 191_176 present
    uint16_t SECT207_192:1;             // 12 Flash sectors 207_192 present
    uint16_t SECT223_208:1;             // 13 Flash sectors 223_208 present
    uint16_t SECT239_224:1;             // 14 Flash sectors 239_224 present
    uint16_t SECT255_240:1;             // 15 Flash sectors 255_240 present
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF76_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF76_BITS  bit;
};

struct SYSCTL_MCUCNF78_BITS {           // bits description
    uint16_t SECT15_0:1;                // 0 Flash sectors 15_0 present
    uint16_t SECT31_16:1;               // 1 Flash sectors 31_16 present
    uint16_t SECT47_32:1;               // 2 Flash sectors 47_32 present
    uint16_t SECT63_48:1;               // 3 Flash sectors 63_48 present
    uint16_t SECT79_64:1;               // 4 Flash sectors 79_64 present
    uint16_t SECT95_80:1;               // 5 Flash sectors 95_80 present
    uint16_t SECT111_96:1;              // 6 Flash sectors 111_96 present
    uint16_t SECT127_112:1;             // 7 Flash sectors 127_112 present
    uint16_t rsvd1:1;                   // 8 Reserved
    uint16_t rsvd2:1;                   // 9 Reserved
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF78_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF78_BITS  bit;
};

struct SYSCTL_MCUCNF79_BITS {           // bits description
    uint16_t SECT15_0:1;                // 0 Flash sectors 15_0 present
    uint16_t SECT31_16:1;               // 1 Flash sectors 31_16 present
    uint16_t SECT47_32:1;               // 2 Flash sectors 47_32 present
    uint16_t SECT63_48:1;               // 3 Flash sectors 63_48 present
    uint16_t SECT79_64:1;               // 4 Flash sectors 79_64 present
    uint16_t SECT95_80:1;               // 5 Flash sectors 95_80 present
    uint16_t SECT111_96:1;              // 6 Flash sectors 111_96 present
    uint16_t SECT127_112:1;             // 7 Flash sectors 127_112 present
    uint16_t SECT143_128:1;             // 8 Flash sectors 143_128 present
    uint16_t SECT159_144:1;             // 9 Flash sectors 159_144 present
    uint16_t SECT175_160:1;             // 10 Flash sectors 175_160 present
    uint16_t SECT191_176:1;             // 11 Flash sectors 191_176 present
    uint16_t SECT207_192:1;             // 12 Flash sectors 207_192 present
    uint16_t SECT223_208:1;             // 13 Flash sectors 223_208 present
    uint16_t SECT239_224:1;             // 14 Flash sectors 239_224 present
    uint16_t SECT255_240:1;             // 15 Flash sectors 255_240 present
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF79_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF79_BITS  bit;
};

struct SYSCTL_MCUCNF81_BITS {           // bits description
    uint16_t SECT15_0:1;                // 0 Flash sectors 15_0 present
    uint16_t SECT31_16:1;               // 1 Flash sectors 31_16 present
    uint16_t SECT47_32:1;               // 2 Flash sectors 47_32 present
    uint16_t SECT63_48:1;               // 3 Flash sectors 63_48 present
    uint16_t SECT79_64:1;               // 4 Flash sectors 79_64 present
    uint16_t SECT95_80:1;               // 5 Flash sectors 95_80 present
    uint16_t SECT111_96:1;              // 6 Flash sectors 111_96 present
    uint16_t SECT127_112:1;             // 7 Flash sectors 127_112 present
    uint16_t SECT143_128:1;             // 8 Flash sectors 143_128 present
    uint16_t SECT159_144:1;             // 9 Flash sectors 159_144 present
    uint16_t SECT175_160:1;             // 10 Flash sectors 175_160 present
    uint16_t SECT191_176:1;             // 11 Flash sectors 191_176 present
    uint16_t SECT207_192:1;             // 12 Flash sectors 207_192 present
    uint16_t SECT223_208:1;             // 13 Flash sectors 223_208 present
    uint16_t SECT239_224:1;             // 14 Flash sectors 239_224 present
    uint16_t SECT255_240:1;             // 15 Flash sectors 255_240 present
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union SYSCTL_MCUCNF81_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNF81_BITS  bit;
};

struct SYSCTL_MCUCNFLOCK1_BITS {        // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t MCUCNF1:1;                 // 1 Lock bit for MCUCNF1 register
    uint16_t MCUCNF2:1;                 // 2 Lock bit for MCUCNF2 register
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t MCUCNF4:1;                 // 4 Lock bit for MCUCNF4 register
    uint16_t rsvd3:5;                   // 9:5 Reserved
    uint16_t MCUCNF10:1;                // 10 Lock bit for MCUCNF10 register
    uint16_t rsvd4:5;                   // 15:11 Reserved
    uint16_t rsvd5:1;                   // 16 Reserved
    uint16_t MCUCNF17:1;                // 17 Lock bit for MCUCNF17 register
    uint16_t MCUCNF18:1;                // 18 Lock bit for MCUCNF18 register
    uint16_t MCUCNF19:1;                // 19 Lock bit for MCUCNF19 register
    uint16_t rsvd6:3;                   // 22:20 Reserved
    uint16_t MCUCNF23:1;                // 23 Lock bit for MCUCNF23 register
    uint16_t rsvd7:2;                   // 25:24 Reserved
    uint16_t MCUCNF26:1;                // 26 Lock bit for MCUCNF26 register
    uint16_t rsvd8:4;                   // 30:27 Reserved
    uint16_t MCUCNF31:1;                // 31 Lock bit for MCUCNF31 register
};

union SYSCTL_MCUCNFLOCK1_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNFLOCK1_BITS  bit;
};

struct SYSCTL_MCUCNFLOCK3_BITS {        // bits description
    uint16_t MCUCNF64:1;                // 0 Lock bit for MCUCNF64 register
    uint16_t MCUCNF65:1;                // 1 Lock bit for MCUCNF65 register
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t rsvd3:1;                   // 9 Reserved
    uint16_t MCUCNF74:1;                // 10 Lock bit for MCUCNF74 register
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t MCUCNF76:1;                // 12 Lock bit for MCUCNF76 register
    uint16_t rsvd5:1;                   // 13 Reserved
    uint16_t MCUCNF78:1;                // 14 Lock bit for MCUCNF78 register
    uint16_t MCUCNF79:1;                // 15 Lock bit for MCUCNF79 register
    uint16_t rsvd6:1;                   // 16 Reserved
    uint16_t MCUCNF81:1;                // 17 Lock bit for MCUCNF81 register
    uint16_t rsvd7:12;                  // 29:18 Reserved
    uint16_t MCUCNF95:1;                // 30 Lock bit for MCUCNF95 register
    uint16_t rsvd8:1;                   // 31 Reserved
};

union SYSCTL_MCUCNFLOCK3_REG {
    uint32_t  all;
    struct  SYSCTL_MCUCNFLOCK3_BITS  bit;
};

struct SYSCTL_LSEN_BITS {               // bits description
    uint16_t Enable:1;                  // 0 Lockstep Enable
    uint32_t Rserved:31;                // 31:1 Reserved
};

union SYSCTL_LSEN_REG {
    uint32_t  all;
    struct  SYSCTL_LSEN_BITS  bit;
};

struct SYSCTL_EPWMXLINKCFG_BITS {       // bits description
    uint16_t EPWM1:1;                   // 0 Enable EPWM1 instance for the XLINK feature
    uint16_t EPWM2:1;                   // 1 Enable EPWM2 instance for the XLINK feature
    uint16_t EPWM3:1;                   // 2 Enable EPWM3 instance for the XLINK feature
    uint16_t EPWM4:1;                   // 3 Enable EPWM4 instance for the XLINK feature
    uint16_t EPWM5:1;                   // 4 Enable EPWM5 instance for the XLINK feature
    uint16_t EPWM6:1;                   // 5 Enable EPWM6 instance for the XLINK feature
    uint16_t EPWM7:1;                   // 6 Enable EPWM7 instance for the XLINK feature
    uint16_t EPWM8:1;                   // 7 Enable EPWM8 instance for the XLINK feature
    uint16_t EPWM9:1;                   // 8 Enable EPWM9 instance for the XLINK feature
    uint16_t EPWM10:1;                  // 9 Enable EPWM10 instance for the XLINK feature
    uint16_t EPWM11:1;                  // 10 Enable EPWM11 instance for the XLINK feature
    uint16_t EPWM12:1;                  // 11 Enable EPWM12 instance for the XLINK feature
    uint16_t EPWM13:1;                  // 12 Enable EPWM13 instance for the XLINK feature
    uint16_t EPWM14:1;                  // 13 Enable EPWM14 instance for the XLINK feature
    uint16_t EPWM15:1;                  // 14 Enable EPWM15 instance for the XLINK feature
    uint16_t EPWM16:1;                  // 15 Enable EPWM16 instance for the XLINK feature
    uint16_t EPWM17:1;                  // 16 Enable EPWM17 instance for the XLINK feature
    uint16_t EPWM18:1;                  // 17 Enable EPWM18 instance for the XLINK feature
    uint16_t rsvd1:14;                  // 31:18 Reserved
};

union SYSCTL_EPWMXLINKCFG_REG {
    uint32_t  all;
    struct  SYSCTL_EPWMXLINKCFG_BITS  bit;
};

struct SYSCTL_SICCONFIG_BITS {          // bits description
    uint16_t Enable:1;                  // 0 Safety Interconnect Enable
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t TIMEOUT:16;                // 31:16 Safety Interconnect (SIC) READY TUMEOUT
};

union SYSCTL_SICCONFIG_REG {
    uint32_t  all;
    struct  SYSCTL_SICCONFIG_BITS  bit;
};

struct SYSCTL_RSTSTAT_BITS {            // bits description
    uint16_t CPU2:1;                    // 0 CPU2 Reset Status bit
    uint16_t CPU3:1;                    // 1 CPU3 Reset Status bit
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:1;                   // 5 Reserved
    uint16_t rsvd5:1;                   // 6 Reserved
    uint16_t rsvd6:1;                   // 7 Reserved
    uint16_t rsvd7:1;                   // 8 Reserved
    uint16_t rsvd8:1;                   // 9 Reserved
    uint16_t rsvd9:2;                   // 11:10 Reserved
    uint16_t rsvd10:4;                  // 15:12 Reserved
    uint16_t rsvd11:16;                 // 31:16 Reserved
};

union SYSCTL_RSTSTAT_REG {
    uint32_t  all;
    struct  SYSCTL_RSTSTAT_BITS  bit;
};

struct SYSCTL_LPMSTAT_BITS {            // bits description
    uint16_t CPU2:2;                    // 1:0 CPU2 LPM Status
    uint16_t CPU3:2;                    // 3:2 CPU3 LPM Status
    uint16_t rsvd1:2;                   // 5:4 Reserved
    uint16_t rsvd2:2;                   // 7:6 Reserved
    uint16_t rsvd3:2;                   // 9:8 Reserved
    uint16_t rsvd4:6;                   // 15:10 Reserved
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union SYSCTL_LPMSTAT_REG {
    uint32_t  all;
    struct  SYSCTL_LPMSTAT_BITS  bit;
};

struct SYSCTL_TAP_STATUS_BITS {         // bits description
    uint16_t TAP_STATE:16;              // 15:0 Present TAP State
    uint16_t rsvd1:15;                  // 30:16 Reserved
    uint16_t DCON:1;                    // 31 Debugger Connect Indication
};

union SYSCTL_TAP_STATUS_REG {
    uint32_t  all;
    struct  SYSCTL_TAP_STATUS_BITS  bit;
};

struct SYSCTL_TAP_CONTROL_BITS {        // bits description
    uint16_t BSCAN_DIS:1;               // 0 Disable BSCAN TAP control
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t KEY:16;                    // 31:16 Key value to enable write
};

union SYSCTL_TAP_CONTROL_REG {
    uint32_t  all;
    struct  SYSCTL_TAP_CONTROL_BITS  bit;
};

struct SYSCTL_DEVLIFECYCLE_BITS {       // bits description
    uint16_t DEVTYPE:4;                 // 3:0 These bits reflect the state from HSM DEVICE_TYPE
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t HSSUBTYPE:4;               // 11:8 These bits reflect the state from the HSM HS_SUBTYPE
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t OVRFLASH:1;                // 16 Status of Override mode with access to Flash
    uint16_t OVRNOFLASH:1;              // 17 Status of Override mode with no access to Flash
    uint16_t rsvd3:14;                  // 31:18 Reserved
};

union SYSCTL_DEVLIFECYCLE_REG {
    uint32_t  all;
    struct  SYSCTL_DEVLIFECYCLE_BITS  bit;
};

struct SYSCTL_SDFMTYPE_BITS {           // bits description
    uint16_t TYPE:2;                    // 1:0 Configure SDFM type
    uint16_t rsvd1:13;                  // 14:2 Reserved
    uint16_t LOCK:1;                    // 15 Lock bit
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SDFMTYPE_REG {
    uint32_t  all;
    struct  SYSCTL_SDFMTYPE_BITS  bit;
};

struct SYSCTL_SYNCSELECT_BITS {         // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint16_t rsvd2:3;                   // 5:3 Reserved
    uint16_t rsvd3:3;                   // 8:6 Reserved
    uint16_t rsvd4:3;                   // 11:9 Reserved
    uint16_t rsvd5:3;                   // 14:12 Reserved
    uint16_t rsvd6:1;                   // 15 Reserved
    uint16_t rsvd7:2;                   // 17:16 Reserved
    uint16_t rsvd8:6;                   // 23:18 Reserved
    uint16_t SYNCOUT:5;                 // 28:24 Select Syncout Source
    uint16_t rsvd9:3;                   // 31:29 Reserved
};

union SYSCTL_SYNCSELECT_REG {
    uint32_t  all;
    struct  SYSCTL_SYNCSELECT_BITS  bit;
};

struct SYSCTL_ADCSOCOUTSELECT_BITS {    // bits description
    uint16_t PWM1SOCAEN:1;              // 0 PWM1SOCAEN Enable for ADCSOCAOn
    uint16_t PWM2SOCAEN:1;              // 1 PWM2SOCAEN Enable for ADCSOCAOn
    uint16_t PWM3SOCAEN:1;              // 2 PWM3SOCAEN Enable for ADCSOCAOn
    uint16_t PWM4SOCAEN:1;              // 3 PWM4SOCAEN Enable for ADCSOCAOn
    uint16_t PWM5SOCAEN:1;              // 4 PWM5SOCAEN Enable for ADCSOCAOn
    uint16_t PWM6SOCAEN:1;              // 5 PWM6SOCAEN Enable for ADCSOCAOn
    uint16_t PWM7SOCAEN:1;              // 6 PWM7SOCAEN Enable for ADCSOCAOn
    uint16_t PWM8SOCAEN:1;              // 7 PWM8SOCAEN Enable for ADCSOCAOn
    uint16_t PWM9SOCAEN:1;              // 8 PWM9SOCAEN Enable for ADCSOCAOn
    uint16_t PWM10SOCAEN:1;             // 9 PWM10SOCAEN Enable for ADCSOCAOn
    uint16_t PWM11SOCAEN:1;             // 10 PWM11SOCAEN Enable for ADCSOCAOn
    uint16_t PWM12SOCAEN:1;             // 11 PWM12SOCAEN Enable for ADCSOCAOn
    uint16_t PWM13SOCAEN:1;             // 12 PWM13SOCAEN Enable for ADCSOCAOn
    uint16_t PWM14SOCAEN:1;             // 13 PWM14SOCAEN Enable for ADCSOCAOn
    uint16_t PWM15SOCAEN:1;             // 14 PWM15SOCAEN Enable for ADCSOCAOn
    uint16_t PWM16SOCAEN:1;             // 15 PWM16SOCAEN Enable for ADCSOCAOn
    uint16_t PWM1SOCBEN:1;              // 16 PWM1SOCBEN Enable for ADCSOCBOn
    uint16_t PWM2SOCBEN:1;              // 17 PWM2SOCBEN Enable for ADCSOCBOn
    uint16_t PWM3SOCBEN:1;              // 18 PWM3SOCBEN Enable for ADCSOCBOn
    uint16_t PWM4SOCBEN:1;              // 19 PWM4SOCBEN Enable for ADCSOCBOn
    uint16_t PWM5SOCBEN:1;              // 20 PWM5SOCBEN Enable for ADCSOCBOn
    uint16_t PWM6SOCBEN:1;              // 21 PWM6SOCBEN Enable for ADCSOCBOn
    uint16_t PWM7SOCBEN:1;              // 22 PWM7SOCBEN Enable for ADCSOCBOn
    uint16_t PWM8SOCBEN:1;              // 23 PWM8SOCBEN Enable for ADCSOCBOn
    uint16_t PWM9SOCBEN:1;              // 24 PWM9SOCBEN Enable for ADCSOCBOn
    uint16_t PWM10SOBAEN:1;             // 25 PWM10SOBAEN Enable for ADCSOCBOn
    uint16_t PWM11SOBAEN:1;             // 26 PWM11SOBAEN Enable for ADCSOCBOn
    uint16_t PWM12SOBAEN:1;             // 27 PWM12SOBAEN Enable for ADCSOCBOn
    uint16_t PWM13SOCBEN:1;             // 28 PWM13SOCBEN Enable for ADCSOCBOn
    uint16_t PWM14SOBAEN:1;             // 29 PWM14SOBAEN Enable for ADCSOCBOn
    uint16_t PWM15SOBAEN:1;             // 30 PWM15SOBAEN Enable for ADCSOCBOn
    uint16_t PWM16SOBAEN:1;             // 31 PWM16SOBAEN Enable for ADCSOCBOn
};

union SYSCTL_ADCSOCOUTSELECT_REG {
    uint32_t  all;
    struct  SYSCTL_ADCSOCOUTSELECT_BITS  bit;
};

struct SYSCTL_ADCSOCOUTSELECT1_BITS {   // bits description
    uint16_t PWM17SOCAEN:1;             // 0 PWM17SOCAEN Enable for ADCSOCAOn
    uint16_t PWM18SOCAEN:1;             // 1 PWM18SOCAEN Enable for ADCSOCAOn
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t PWM17SOCBEN:1;             // 16 PWM17SOCBEN Enable for ADCSOCBOn
    uint16_t PWM18SOCBEN:1;             // 17 PWM18SOCBEN Enable for ADCSOCBOn
    uint16_t rsvd2:14;                  // 31:18 Reserved
};

union SYSCTL_ADCSOCOUTSELECT1_REG {
    uint32_t  all;
    struct  SYSCTL_ADCSOCOUTSELECT1_BITS  bit;
};

struct SYSCTL_SYNCSOCLOCK_BITS {        // bits description
    uint16_t SYNCSELECT:1;              // 0 SYNCSEL Register Lock bit
    uint16_t ADCSOCOUTSELECT:1;         // 1 ADCSOCOUTSELECT Register Lock bit
    uint16_t ADCSOCOUTSELECT1:1;        // 2 ADCSOCOUTSELECT1 Register Lock bit
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SYNCSOCLOCK_REG {
    uint32_t  all;
    struct  SYSCTL_SYNCSOCLOCK_BITS  bit;
};

struct SYSCTL_HSMTOCPU_STS1_BITS {      // bits description
    uint16_t SRAM_BANK0:1;              // 0 HSM to CPU USURP Communication Signal for SRAM_BANK0
    uint16_t SRAM_BANK1:1;              // 1 HSM to CPU USURP Communication Signal for SRAM_BANK1
    uint16_t SRAM_BANK2:1;              // 2 HSM to CPU USURP Communication Signal for SRAM_BANK2
    uint16_t SRAM_BANK3:1;              // 3 HSM to CPU USURP Communication Signal for SRAM_BANK3
    uint16_t SRAM_BANK4:1;              // 4 HSM to CPU USURP Communication Signal for SRAM_BANK4
    uint16_t SRAM_BANK5:1;              // 5 HSM to CPU USURP Communication Signal for SRAM_BANK5
    uint16_t SRAM_BANK6:1;              // 6 HSM to CPU USURP Communication Signal for SRAM_BANK6
    uint16_t SRAM_BANK7:1;              // 7 HSM to CPU USURP Communication Signal for SRAM_BANK7
    uint16_t FLC1:1;                    // 8 HSM to CPU USURP Communication Signal for FLC1
    uint16_t FLC2:1;                    // 9 HSM to CPU USURP Communication Signal for FLC2
    uint16_t LPOST:1;                   // 10 HSM to CPU USURP Communication Signal for LPOST
    uint16_t MPOST:1;                   // 11 HSM to CPU USURP Communication Signal for MPOST
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t SOC_GENR_1:8;              // 23:16 HSM to CPU USURP Communication Signal for SOC_GENR_1
    uint16_t SOC_GENR_2:8;              // 31:24 HSM to CPU USURP Communication Signal for SOC_GENR_2
};

union SYSCTL_HSMTOCPU_STS1_REG {
    uint32_t  all;
    struct  SYSCTL_HSMTOCPU_STS1_BITS  bit;
};

struct SYSCTL_HSMTOCPU_STS2_BITS {      // bits description
    uint16_t FLC1_BANK0:1;              // 0 HSM to CPU USURP Communication Signal for FLC1_BANK0
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t FLC2_BANK0:1;              // 4 HSM to CPU USURP Communication Signal for FLC2_BANK0
    uint16_t FLC1_BANK1:1;              // 5 HSM to CPU USURP Communication Signal for FLC1_BANK1
    uint16_t rsvd2:3;                   // 8:6 Reserved
    uint16_t FLC2_BANK1:1;              // 9 HSM to CPU USURP Communication Signal for FLC2_BANK1
    uint16_t FLC1_BANK2:1;              // 10 HSM to CPU USURP Communication Signal for FLC1_BANK2
    uint16_t rsvd3:3;                   // 13:11 Reserved
    uint16_t FLC2_BANK2:1;              // 14 HSM to CPU USURP Communication Signal for FLC2_BANK2
    uint16_t FLC1_BANK3:1;              // 15 HSM to CPU USURP Communication Signal for FLC1_BANK3
    uint16_t rsvd4:3;                   // 18:16 Reserved
    uint16_t FLC2_BANK3:1;              // 19 HSM to CPU USURP Communication Signal for FLC2_BANK3
    uint16_t FLC1_BANK4:1;              // 20 HSM to CPU USURP Communication Signal for FLC1_BANK4
    uint16_t rsvd5:3;                   // 23:21 Reserved
    uint16_t FLC2_BANK4:1;              // 24 HSM to CPU USURP Communication Signal for FLC2_BANK4
    uint16_t rsvd6:7;                   // 31:25 Reserved
};

union SYSCTL_HSMTOCPU_STS2_REG {
    uint32_t  all;
    struct  SYSCTL_HSMTOCPU_STS2_BITS  bit;
};

struct SYSCTL_CLKCFGLOCK1_BITS {        // bits description
    uint16_t CLKSRCCTL1:1;              // 0 Lock bit for CLKSRCCTL1 register
    uint16_t CLKSRCCTL2:1;              // 1 Lock bit for CLKSRCCTL2 register
    uint16_t CLKSRCCTL3:1;              // 2 Lock bit for CLKSRCCTL3 register
    uint16_t SYSPLLCTL1:1;              // 3 Lock bit for SYSPLLCTL1 register
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t SYSPLLMULT:1;              // 6 Lock bit for SYSPLLMULT register
    uint16_t rsvd3:1;                   // 7 Reserved
    uint16_t rsvd4:1;                   // 8 Reserved
    uint16_t rsvd5:1;                   // 9 Reserved
    uint16_t rsvd6:1;                   // 10 Reserved
    uint16_t SYSCLKDIVSEL:1;            // 11 Lock bit for SYSCLKDIVSEL register
    uint16_t rsvd7:1;                   // 12 Reserved
    uint16_t PERCLKDIVSEL:1;            // 13 Lock bit for PERCLKDIVSEL register
    uint16_t CLBCLKCTL:1;               // 14 Lock bit for CLBCLKCTL register
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t XTALCR:1;                  // 16 Lock bit for XTALCR  & XTALCR2 register
    uint16_t EXTRFLTDET:1;              // 17 Lockbit for EXTRFLTDET register
    uint16_t ETHERCATCLKCTL:1;          // 18 Lockbit for ETHERCATCLKCTL register
    uint16_t HSMCLKDIVSEL:1;            // 19 Lock bit for HSMCLKDIVSEL register
    uint16_t MCANCLKDIVSEL:1;           // 20 Lock bit for MCANCLKDIVSEL register
    uint16_t XCLKOUTDIVSEL:1;           // 21 Lock bit for XCLKOUTDIVSEL register
    uint16_t rsvd9:10;                  // 31:22 Reserved
};

union SYSCTL_CLKCFGLOCK1_REG {
    uint32_t  all;
    struct  SYSCTL_CLKCFGLOCK1_BITS  bit;
};

struct SYSCTL_CLKSRCCTL1_BITS {         // bits description
    uint16_t OSCCLKSRCSEL:2;            // 1:0 OSCCLK Source Select Bit
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:1;                   // 5 Reserved
    uint16_t rsvd5:1;                   // 6 Reserved
    uint16_t rsvd6:1;                   // 7 Reserved
    uint16_t rsvd7:1;                   // 8 Reserved
    uint16_t rsvd8:7;                   // 15:9 Reserved
    uint16_t rsvd9:16;                  // 31:16 Reserved
};

union SYSCTL_CLKSRCCTL1_REG {
    uint32_t  all;
    struct  SYSCTL_CLKSRCCTL1_BITS  bit;
};

struct SYSCTL_CLKSRCCTL2_BITS {         // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t rsvd2:2;                   // 3:2 Reserved
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:2;                   // 7:6 Reserved
    uint16_t rsvd5:2;                   // 9:8 Reserved
    uint16_t MCANABCLKSEL:2;            // 11:10 MCANA Bit Clock Source Select Bit
    uint16_t MCANBBCLKSEL:2;            // 13:12 MCANB Bit Clock Source Select Bit
    uint16_t MCANCBCLKSEL:2;            // 15:14 MCANC Bit Clock Source Select Bit
    uint16_t MCANDBCLKSEL:2;            // 17:16 MCAND Bit Clock Source Select Bit
    uint16_t MCANEBCLKSEL:2;            // 19:18 MCANE Bit Clock Source Select Bit
    uint16_t MCANFBCLKSEL:2;            // 21:20 MCANF Bit Clock Source Select Bit
    uint16_t rsvd6:10;                  // 31:22 Reserved
};

union SYSCTL_CLKSRCCTL2_REG {
    uint32_t  all;
    struct  SYSCTL_CLKSRCCTL2_BITS  bit;
};

struct SYSCTL_CLKSRCCTL3_BITS {         // bits description
    uint16_t XCLKOUTSEL:5;              // 4:0 XCLKOUT Source Select Bit
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CLKSRCCTL3_REG {
    uint32_t  all;
    struct  SYSCTL_CLKSRCCTL3_BITS  bit;
};

struct SYSCTL_SYSPLLCTL1_BITS {         // bits description
    uint16_t PLLEN:1;                   // 0 SYSPLL enable/disable bit
    uint16_t PLLCLKEN:1;                // 1 SYSPLL bypassed or included in the PLLSYSCLK path
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:1;                   // 5 Reserved
    uint16_t rsvd5:10;                  // 15:6 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_SYSPLLCTL1_REG {
    uint32_t  all;
    struct  SYSCTL_SYSPLLCTL1_BITS  bit;
};

struct SYSCTL_SYSPLLMULT_BITS {         // bits description
    uint16_t IMULT:8;                   // 7:0 SYSPLL Integer Multiplier
    uint16_t rsvd1:2;                   // 9:8 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:2;                   // 13:12 Reserved
    uint16_t rsvd4:2;                   // 15:14 Reserved
    uint16_t ODIV:5;                    // 20:16 Output Clock Divider
    uint16_t rsvd5:3;                   // 23:21 Reserved
    uint16_t REFDIV:5;                  // 28:24 Reference Clock Divider
    uint16_t rsvd6:3;                   // 31:29 Reserved
};

union SYSCTL_SYSPLLMULT_REG {
    uint32_t  all;
    struct  SYSCTL_SYSPLLMULT_BITS  bit;
};

struct SYSCTL_SYSPLLSTS_BITS {          // bits description
    uint16_t LOCKS:1;                   // 0 SYSPLL Lock Status Bit
    uint16_t SLIPS_NOTSUPPORTED:1;      // 1 SYSPLL Slip Status Bit
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:1;                   // 5 Reserved
    uint16_t rsvd5:10;                  // 15:6 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_SYSPLLSTS_REG {
    uint32_t  all;
    struct  SYSCTL_SYSPLLSTS_BITS  bit;
};

struct SYSCTL_SYSCLKDIVSEL_BITS {       // bits description
    uint16_t PLLSYSCLKDIV:6;            // 5:0 PLLSYSCLK Divide Select
    uint16_t rsvd1:2;                   // 7:6 Reserved
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t rsvd3:7;                   // 15:9 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union SYSCTL_SYSCLKDIVSEL_REG {
    uint32_t  all;
    struct  SYSCTL_SYSCLKDIVSEL_BITS  bit;
};

struct SYSCTL_PERCLKDIVSEL_BITS {       // bits description
    uint16_t EPWMCLKDIV:2;              // 1:0 EPWM Clock Divide Select
    uint16_t rsvd1:2;                   // 3:2 Reserved
    uint16_t EMIF1CLKDIV:2;             // 5:4 EMIF1  Clock Divide Select
    uint16_t rsvd2:1;                   // 6 Reserved
    uint16_t rsvd3:1;                   // 7 Reserved
    uint16_t LINACLKDIV:2;              // 9:8 LINA Clock Divide Select
    uint16_t rsvd4:1;                   // 10 Reserved
    uint16_t LINBCLKDIV:2;              // 12:11 LINB Clock Divide Select
    uint16_t rsvd5:3;                   // 15:13 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_PERCLKDIVSEL_REG {
    uint32_t  all;
    struct  SYSCTL_PERCLKDIVSEL_BITS  bit;
};

struct SYSCTL_XCLKOUTDIVSEL_BITS {      // bits description
    uint16_t XCLKOUTDIV:2;              // 1:0 XCLKOUT Divide Select
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_XCLKOUTDIVSEL_REG {
    uint32_t  all;
    struct  SYSCTL_XCLKOUTDIVSEL_BITS  bit;
};

struct SYSCTL_HSMCLKDIVSEL_BITS {       // bits description
    uint16_t HSMCLKDIV:5;               // 4:0 Divider value for HSMSYSCLK clock input to HSM
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_HSMCLKDIVSEL_REG {
    uint32_t  all;
    struct  SYSCTL_HSMCLKDIVSEL_BITS  bit;
};

struct SYSCTL_MCANCLKDIVSEL_BITS {      // bits description
    uint16_t MCANACLKDIV:5;             // 4:0 Divider CANFD Bit CLK for MCANA
    uint16_t MCANBCLKDIV:5;             // 9:5 Divider CANFD Bit CLK for MCANB
    uint16_t MCANCCLKDIV:5;             // 14:10 Divider CANFD Bit CLK for MCANC
    uint32_t MCANDCLKDIV:5;             // 19:15 Divider CANFD Bit CLK for MCAND
    uint16_t MCANECLKDIV:5;             // 24:20 Divider CANFD Bit CLK for MCANE
    uint16_t MCANFCLKDIV:5;             // 29:25 Divider CANFD Bit CLK for MCANF
    uint16_t rsvd1:2;                   // 31:30 Reserved
};

union SYSCTL_MCANCLKDIVSEL_REG {
    uint32_t  all;
    struct  SYSCTL_MCANCLKDIVSEL_BITS  bit;
};

struct SYSCTL_CLBCLKCTL_BITS {          // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:11;                  // 15:5 Reserved
    uint16_t CLKMODECLB1:1;             // 16 Clock mode of CLB1
    uint16_t CLKMODECLB2:1;             // 17 Clock mode of CLB2
    uint16_t CLKMODECLB3:1;             // 18 Clock mode of CLB3
    uint16_t CLKMODECLB4:1;             // 19 Clock mode of CLB4
    uint16_t CLKMODECLB5:1;             // 20 Clock mode of CLB5
    uint16_t CLKMODECLB6:1;             // 21 Clock mode of CLB6
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t rsvd7:8;                   // 31:24 Reserved
};

union SYSCTL_CLBCLKCTL_REG {
    uint32_t  all;
    struct  SYSCTL_CLBCLKCTL_BITS  bit;
};

struct SYSCTL_MCDCR_BITS {              // bits description
    uint16_t MCLKSTS:1;                 // 0 Missing Clock Status Bit
    uint16_t MCLKCLR:1;                 // 1 Missing Clock Clear Bit
    uint16_t MCLKOFF:1;                 // 2 Missing Clock Detect Off Bit
    uint16_t OSCOFF:1;                  // 3 Oscillator Clock Off Bit
    uint16_t SYSREF_LOSTS:1;            // 4 SYSPLL "Reference  Lost" Status Bit
    uint16_t SYSREF_LOSTSCLR:1;         // 5 Clear for Ref clock lost status
    uint16_t SYSREF_LOST_MCD_EN:1;      // 6 Enable for PLL REF_CLK_LOST as MCD cause
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t rsvd3:1;                   // 9 Reserved
    uint16_t EXTR_FAULTS:1;             // 10 External Resistor fault indication
    uint16_t EXTR_FAULTSCLR:1;          // 11 External Resistor fault status clear
    uint16_t EXTR_FAULT_MCD_EN:1;       // 12 Configuration to enable EXTR_FAULTS as MCD cause
    uint16_t rsvd4:1;                   // 13 Reserved
    uint16_t rsvd5:1;                   // 14 Reserved
    uint16_t rsvd6:1;                   // 15 Reserved
    uint16_t rsvd7:16;                  // 31:16 Reserved
};

union SYSCTL_MCDCR_REG {
    uint32_t  all;
    struct  SYSCTL_MCDCR_BITS  bit;
};

struct SYSCTL_X1CNT_BITS {              // bits description
    uint16_t X1CNT:11;                  // 10:0 X1 Counter
    uint16_t rsvd1:5;                   // 15:11 Reserved
    uint16_t CLR:1;                     // 16 X1 Counter Clear
    uint16_t rsvd2:15;                  // 31:17 Reserved
};

union SYSCTL_X1CNT_REG {
    uint32_t  all;
    struct  SYSCTL_X1CNT_BITS  bit;
};

struct SYSCTL_XTALCR_BITS {             // bits description
    uint16_t OSCOFF:1;                  // 0 XTAL Oscillator powered-down
    uint16_t SE:1;                      // 1 XTAL Oscilator in Single-Ended mode
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SYSCTL_XTALCR_REG {
    uint32_t  all;
    struct  SYSCTL_XTALCR_BITS  bit;
};

struct SYSCTL_XTALCR2_BITS {            // bits description
    uint16_t XIF:1;                     // 0 XI Initial value deposited before XOSC start
    uint16_t XOF:1;                     // 1 XO Initial value deposited before XOSC start
    uint16_t FEN:1;                     // 2 XOSC pads initialisation enable
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_XTALCR2_REG {
    uint32_t  all;
    struct  SYSCTL_XTALCR2_BITS  bit;
};

struct SYSCTL_ETHERCATCLKCTL_BITS {     // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t ECATDIV:3;                 // 3:1 etherCAT clock divider configuration.
    uint16_t rsvd2:4;                   // 7:4 Reserved
    uint16_t PHYCLKEN:1;                // 8 etherCAT PHY clock enable
    uint16_t rsvd3:7;                   // 15:9 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union SYSCTL_ETHERCATCLKCTL_REG {
    uint32_t  all;
    struct  SYSCTL_ETHERCATCLKCTL_BITS  bit;
};

struct SYSCTL_ETHERCATCTL_BITS {        // bits description
    uint16_t I2CLOOPBACK:1;             // 0 Loopback I2C port of etherCAT IP to I2C_A.
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ETHERCATCTL_REG {
    uint32_t  all;
    struct  SYSCTL_ETHERCATCTL_BITS  bit;
};

struct SYSCTL_SYNCBUSY_BITS {           // bits description
    uint16_t BUSY:1;                    // 0 Status bit indicating synchronization in progress
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t MCANCLKDIVSEL:1;           // 16 BUSY status bit for MCANCLKDIVSEL
    uint16_t rsvd2:1;                   // 17 Reserved
    uint16_t CLBCLKCTL:1;               // 18 BUSY status bit for CLBCLKCTL
    uint16_t ETHERCATCLKCTL:1;          // 19 BUSY status bit for ETHERCATCLKCTL
    uint16_t PERCLKDIVSEL:1;            // 20 BUSY status bit for PERCLKDIVSEL
    uint16_t SYSCLKDIVSEL:1;            // 21 BUSY status bit for SYSCLKDIVSEL
    uint16_t SYSPLLCTL1:1;              // 22 BUSY status bit for SYSPLLCTL1
    uint16_t SYSPLLMULT:1;              // 23 BUSY status bit for SYSPLLMULT
    uint16_t XCLKOUTDIVSEL:1;           // 24 BUSY status bit for XCLKOUTDIVSEL
    uint16_t XTALCR:1;                  // 25 BUSY status bit for XTALCR
    uint16_t CLKSRCCTL1:1;              // 26 BUSY status bit for CLKSRCCTL1
    uint16_t CLKSRCCTL2:1;              // 27 BUSY status bit for CLKSRCCTL2
    uint16_t CLKSRCCTL3:1;              // 28 BUSY status bit for CLKSRCCTL3
    uint16_t CPU3TMR2CTL:1;             // 29 BUSY status bit for CPU3TMR2CTL
    uint16_t CPU1TMR2CTL:1;             // 30 BUSY status bit for CPU1TMR2CTL
    uint16_t CPU2TMR2CTL:1;             // 31 BUSY status bit for CPU2TMR2CTL
};

union SYSCTL_SYNCBUSY_REG {
    uint32_t  all;
    struct  SYSCTL_SYNCBUSY_BITS  bit;
};

struct SYSCTL_ESMXRSNCTL_BITS {         // bits description
    uint16_t ESMCPU1CRITICAL:1;         // 0 Enable ESMCPU1CRITICAL to cause XRSn
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t ESMCPU2CRITICAL:1;         // 2 Enable ESMCPU2CRITICAL to cause XRSn
    uint16_t ESMCPU2HIPRIWD:1;          // 3 Enable ESMCPU2HIPRIWD to cause XRSn
    uint16_t ESMCPU3CRITICAL:1;         // 4 Enable ESMCPU3CRITICAL to cause XRSn
    uint16_t ESMCPU3HIPRIWD:1;          // 5 Enable ESMCPU3HIPRIWD to cause XRSn
    uint16_t rsvd2:10;                  // 15:6 Reserved
    uint16_t ESMRESET:1;                // 16 Enable ESMRESET to cause XRSn
    uint16_t rsvd3:15;                  // 31:17 Reserved
};

union SYSCTL_ESMXRSNCTL_REG {
    uint32_t  all;
    struct  SYSCTL_ESMXRSNCTL_BITS  bit;
};

struct SYSCTL_EPWM1_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM1_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM1_BITS  bit;
};

struct SYSCTL_EPWM2_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM2_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM2_BITS  bit;
};

struct SYSCTL_EPWM3_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM3_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM3_BITS  bit;
};

struct SYSCTL_EPWM4_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM4_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM4_BITS  bit;
};

struct SYSCTL_EPWM5_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM5_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM5_BITS  bit;
};

struct SYSCTL_EPWM6_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM6_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM6_BITS  bit;
};

struct SYSCTL_EPWM7_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM7_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM7_BITS  bit;
};

struct SYSCTL_EPWM8_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM8_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM8_BITS  bit;
};

struct SYSCTL_EPWM9_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM9_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM9_BITS  bit;
};

struct SYSCTL_EPWM10_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM10_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM10_BITS  bit;
};

struct SYSCTL_EPWM11_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM11_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM11_BITS  bit;
};

struct SYSCTL_EPWM12_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM12_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM12_BITS  bit;
};

struct SYSCTL_EPWM13_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM13_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM13_BITS  bit;
};

struct SYSCTL_EPWM14_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM14_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM14_BITS  bit;
};

struct SYSCTL_EPWM15_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM15_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM15_BITS  bit;
};

struct SYSCTL_EPWM16_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM16_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM16_BITS  bit;
};

struct SYSCTL_EPWM17_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM17_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM17_BITS  bit;
};

struct SYSCTL_EPWM18_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPWM18_REG {
    uint32_t  all;
    struct  SYSCTL_EPWM18_BITS  bit;
};

struct SYSCTL_HRCAL0_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_HRCAL0_REG {
    uint32_t  all;
    struct  SYSCTL_HRCAL0_BITS  bit;
};

struct SYSCTL_HRCAL1_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_HRCAL1_REG {
    uint32_t  all;
    struct  SYSCTL_HRCAL1_BITS  bit;
};

struct SYSCTL_HRCAL2_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_HRCAL2_REG {
    uint32_t  all;
    struct  SYSCTL_HRCAL2_BITS  bit;
};

struct SYSCTL_ECAP1_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ECAP1_REG {
    uint32_t  all;
    struct  SYSCTL_ECAP1_BITS  bit;
};

struct SYSCTL_ECAP2_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ECAP2_REG {
    uint32_t  all;
    struct  SYSCTL_ECAP2_BITS  bit;
};

struct SYSCTL_ECAP3_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ECAP3_REG {
    uint32_t  all;
    struct  SYSCTL_ECAP3_BITS  bit;
};

struct SYSCTL_ECAP4_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ECAP4_REG {
    uint32_t  all;
    struct  SYSCTL_ECAP4_BITS  bit;
};

struct SYSCTL_ECAP5_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ECAP5_REG {
    uint32_t  all;
    struct  SYSCTL_ECAP5_BITS  bit;
};

struct SYSCTL_ECAP6_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ECAP6_REG {
    uint32_t  all;
    struct  SYSCTL_ECAP6_BITS  bit;
};

struct SYSCTL_EQEP1_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EQEP1_REG {
    uint32_t  all;
    struct  SYSCTL_EQEP1_BITS  bit;
};

struct SYSCTL_EQEP2_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EQEP2_REG {
    uint32_t  all;
    struct  SYSCTL_EQEP2_BITS  bit;
};

struct SYSCTL_EQEP3_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EQEP3_REG {
    uint32_t  all;
    struct  SYSCTL_EQEP3_BITS  bit;
};

struct SYSCTL_EQEP4_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EQEP4_REG {
    uint32_t  all;
    struct  SYSCTL_EQEP4_BITS  bit;
};

struct SYSCTL_EQEP5_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EQEP5_REG {
    uint32_t  all;
    struct  SYSCTL_EQEP5_BITS  bit;
};

struct SYSCTL_EQEP6_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EQEP6_REG {
    uint32_t  all;
    struct  SYSCTL_EQEP6_BITS  bit;
};

struct SYSCTL_SDFM1_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SDFM1_REG {
    uint32_t  all;
    struct  SYSCTL_SDFM1_BITS  bit;
};

struct SYSCTL_SDFM2_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SDFM2_REG {
    uint32_t  all;
    struct  SYSCTL_SDFM2_BITS  bit;
};

struct SYSCTL_SDFM3_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SDFM3_REG {
    uint32_t  all;
    struct  SYSCTL_SDFM3_BITS  bit;
};

struct SYSCTL_SDFM4_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SDFM4_REG {
    uint32_t  all;
    struct  SYSCTL_SDFM4_BITS  bit;
};

struct SYSCTL_UARTA_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_UARTA_REG {
    uint32_t  all;
    struct  SYSCTL_UARTA_BITS  bit;
};

struct SYSCTL_UARTB_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_UARTB_REG {
    uint32_t  all;
    struct  SYSCTL_UARTB_BITS  bit;
};

struct SYSCTL_UARTC_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_UARTC_REG {
    uint32_t  all;
    struct  SYSCTL_UARTC_BITS  bit;
};

struct SYSCTL_UARTD_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_UARTD_REG {
    uint32_t  all;
    struct  SYSCTL_UARTD_BITS  bit;
};

struct SYSCTL_UARTE_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_UARTE_REG {
    uint32_t  all;
    struct  SYSCTL_UARTE_BITS  bit;
};

struct SYSCTL_UARTF_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_UARTF_REG {
    uint32_t  all;
    struct  SYSCTL_UARTF_BITS  bit;
};

struct SYSCTL_SPIA_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SPIA_REG {
    uint32_t  all;
    struct  SYSCTL_SPIA_BITS  bit;
};

struct SYSCTL_SPIB_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SPIB_REG {
    uint32_t  all;
    struct  SYSCTL_SPIB_BITS  bit;
};

struct SYSCTL_SPIC_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SPIC_REG {
    uint32_t  all;
    struct  SYSCTL_SPIC_BITS  bit;
};

struct SYSCTL_SPID_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SPID_REG {
    uint32_t  all;
    struct  SYSCTL_SPID_BITS  bit;
};

struct SYSCTL_SPIE_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SPIE_REG {
    uint32_t  all;
    struct  SYSCTL_SPIE_BITS  bit;
};

struct SYSCTL_I2CA_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_I2CA_REG {
    uint32_t  all;
    struct  SYSCTL_I2CA_BITS  bit;
};

struct SYSCTL_I2CB_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_I2CB_REG {
    uint32_t  all;
    struct  SYSCTL_I2CB_BITS  bit;
};

struct SYSCTL_PMBUSA_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PMBUSA_REG {
    uint32_t  all;
    struct  SYSCTL_PMBUSA_BITS  bit;
};

struct SYSCTL_LINA_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_LINA_REG {
    uint32_t  all;
    struct  SYSCTL_LINA_BITS  bit;
};

struct SYSCTL_LINB_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_LINB_REG {
    uint32_t  all;
    struct  SYSCTL_LINB_BITS  bit;
};

struct SYSCTL_MCANA_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCANA_REG {
    uint32_t  all;
    struct  SYSCTL_MCANA_BITS  bit;
};

struct SYSCTL_MCANB_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCANB_REG {
    uint32_t  all;
    struct  SYSCTL_MCANB_BITS  bit;
};

struct SYSCTL_MCANC_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCANC_REG {
    uint32_t  all;
    struct  SYSCTL_MCANC_BITS  bit;
};

struct SYSCTL_MCAND_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCAND_REG {
    uint32_t  all;
    struct  SYSCTL_MCAND_BITS  bit;
};

struct SYSCTL_MCANE_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCANE_REG {
    uint32_t  all;
    struct  SYSCTL_MCANE_BITS  bit;
};

struct SYSCTL_MCANF_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCANF_REG {
    uint32_t  all;
    struct  SYSCTL_MCANF_BITS  bit;
};

struct SYSCTL_ADCA_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCA_REG {
    uint32_t  all;
    struct  SYSCTL_ADCA_BITS  bit;
};

struct SYSCTL_ADCB_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCB_REG {
    uint32_t  all;
    struct  SYSCTL_ADCB_BITS  bit;
};

struct SYSCTL_ADCC_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCC_REG {
    uint32_t  all;
    struct  SYSCTL_ADCC_BITS  bit;
};

struct SYSCTL_ADCD_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCD_REG {
    uint32_t  all;
    struct  SYSCTL_ADCD_BITS  bit;
};

struct SYSCTL_ADCE_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCE_REG {
    uint32_t  all;
    struct  SYSCTL_ADCE_BITS  bit;
};

struct SYSCTL_CMPSS1_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS1_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS1_BITS  bit;
};

struct SYSCTL_CMPSS2_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS2_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS2_BITS  bit;
};

struct SYSCTL_CMPSS3_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS3_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS3_BITS  bit;
};

struct SYSCTL_CMPSS4_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS4_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS4_BITS  bit;
};

struct SYSCTL_CMPSS5_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS5_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS5_BITS  bit;
};

struct SYSCTL_CMPSS6_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS6_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS6_BITS  bit;
};

struct SYSCTL_CMPSS7_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS7_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS7_BITS  bit;
};

struct SYSCTL_CMPSS8_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS8_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS8_BITS  bit;
};

struct SYSCTL_CMPSS9_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS9_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS9_BITS  bit;
};

struct SYSCTL_CMPSS10_BITS {            // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS10_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS10_BITS  bit;
};

struct SYSCTL_CMPSS11_BITS {            // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS11_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS11_BITS  bit;
};

struct SYSCTL_CMPSS12_BITS {            // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CMPSS12_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSS12_BITS  bit;
};

struct SYSCTL_DACA_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_DACA_REG {
    uint32_t  all;
    struct  SYSCTL_DACA_BITS  bit;
};

struct SYSCTL_DACB_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_DACB_REG {
    uint32_t  all;
    struct  SYSCTL_DACB_BITS  bit;
};

struct SYSCTL_CLB1_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CLB1_REG {
    uint32_t  all;
    struct  SYSCTL_CLB1_BITS  bit;
};

struct SYSCTL_CLB2_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CLB2_REG {
    uint32_t  all;
    struct  SYSCTL_CLB2_BITS  bit;
};

struct SYSCTL_CLB3_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CLB3_REG {
    uint32_t  all;
    struct  SYSCTL_CLB3_BITS  bit;
};

struct SYSCTL_CLB4_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CLB4_REG {
    uint32_t  all;
    struct  SYSCTL_CLB4_BITS  bit;
};

struct SYSCTL_CLB5_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CLB5_REG {
    uint32_t  all;
    struct  SYSCTL_CLB5_BITS  bit;
};

struct SYSCTL_CLB6_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CLB6_REG {
    uint32_t  all;
    struct  SYSCTL_CLB6_BITS  bit;
};

struct SYSCTL_FSITXA_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_FSITXA_REG {
    uint32_t  all;
    struct  SYSCTL_FSITXA_BITS  bit;
};

struct SYSCTL_FSITXB_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_FSITXB_REG {
    uint32_t  all;
    struct  SYSCTL_FSITXB_BITS  bit;
};

struct SYSCTL_FSITXC_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_FSITXC_REG {
    uint32_t  all;
    struct  SYSCTL_FSITXC_BITS  bit;
};

struct SYSCTL_FSITXD_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_FSITXD_REG {
    uint32_t  all;
    struct  SYSCTL_FSITXD_BITS  bit;
};

struct SYSCTL_FSIRXA_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_FSIRXA_REG {
    uint32_t  all;
    struct  SYSCTL_FSIRXA_BITS  bit;
};

struct SYSCTL_FSIRXB_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_FSIRXB_REG {
    uint32_t  all;
    struct  SYSCTL_FSIRXB_BITS  bit;
};

struct SYSCTL_FSIRXC_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_FSIRXC_REG {
    uint32_t  all;
    struct  SYSCTL_FSIRXC_BITS  bit;
};

struct SYSCTL_FSIRXD_BITS {             // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_FSIRXD_REG {
    uint32_t  all;
    struct  SYSCTL_FSIRXD_BITS  bit;
};

struct SYSCTL_DCC1_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_DCC1_REG {
    uint32_t  all;
    struct  SYSCTL_DCC1_BITS  bit;
};

struct SYSCTL_DCC2_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_DCC2_REG {
    uint32_t  all;
    struct  SYSCTL_DCC2_BITS  bit;
};

struct SYSCTL_DCC3_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_DCC3_REG {
    uint32_t  all;
    struct  SYSCTL_DCC3_BITS  bit;
};

struct SYSCTL_ETHERCATA_BITS {          // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ETHERCATA_REG {
    uint32_t  all;
    struct  SYSCTL_ETHERCATA_BITS  bit;
};

struct SYSCTL_EPG1_BITS {               // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_EPG1_REG {
    uint32_t  all;
    struct  SYSCTL_EPG1_BITS  bit;
};

struct SYSCTL_SENT1_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SENT1_REG {
    uint32_t  all;
    struct  SYSCTL_SENT1_BITS  bit;
};

struct SYSCTL_SENT2_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SENT2_REG {
    uint32_t  all;
    struct  SYSCTL_SENT2_BITS  bit;
};

struct SYSCTL_SENT3_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SENT3_REG {
    uint32_t  all;
    struct  SYSCTL_SENT3_BITS  bit;
};

struct SYSCTL_SENT4_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SENT4_REG {
    uint32_t  all;
    struct  SYSCTL_SENT4_BITS  bit;
};

struct SYSCTL_SENT5_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SENT5_REG {
    uint32_t  all;
    struct  SYSCTL_SENT5_BITS  bit;
};

struct SYSCTL_SENT6_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SENT6_REG {
    uint32_t  all;
    struct  SYSCTL_SENT6_BITS  bit;
};

struct SYSCTL_ADCCHECKER1_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER1_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER1_BITS  bit;
};

struct SYSCTL_ADCCHECKER2_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER2_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER2_BITS  bit;
};

struct SYSCTL_ADCCHECKER3_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER3_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER3_BITS  bit;
};

struct SYSCTL_ADCCHECKER4_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER4_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER4_BITS  bit;
};

struct SYSCTL_ADCCHECKER5_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER5_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER5_BITS  bit;
};

struct SYSCTL_ADCCHECKER6_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER6_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER6_BITS  bit;
};

struct SYSCTL_ADCCHECKER7_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER7_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER7_BITS  bit;
};

struct SYSCTL_ADCCHECKER8_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER8_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER8_BITS  bit;
};

struct SYSCTL_ADCCHECKER9_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER9_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER9_BITS  bit;
};

struct SYSCTL_ADCCHECKER10_BITS {       // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCCHECKER10_REG {
    uint32_t  all;
    struct  SYSCTL_ADCCHECKER10_BITS  bit;
};

struct SYSCTL_ADCSEAGGRCPU1_BITS {      // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCSEAGGRCPU1_REG {
    uint32_t  all;
    struct  SYSCTL_ADCSEAGGRCPU1_BITS  bit;
};

struct SYSCTL_ADCSEAGGRCPU2_BITS {      // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCSEAGGRCPU2_REG {
    uint32_t  all;
    struct  SYSCTL_ADCSEAGGRCPU2_BITS  bit;
};

struct SYSCTL_ADCSEAGGRCPU3_BITS {      // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADCSEAGGRCPU3_REG {
    uint32_t  all;
    struct  SYSCTL_ADCSEAGGRCPU3_BITS  bit;
};

struct SYSCTL_RTDMA1CH_BITS {           // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_RTDMA1CH_REG {
    uint32_t  all;
    struct  SYSCTL_RTDMA1CH_BITS  bit;
};

struct SYSCTL_RTDMA2CH_BITS {           // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_RTDMA2CH_REG {
    uint32_t  all;
    struct  SYSCTL_RTDMA2CH_BITS  bit;
};

struct SYSCTL_WADI1_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_WADI1_REG {
    uint32_t  all;
    struct  SYSCTL_WADI1_BITS  bit;
};

struct SYSCTL_WADI2_BITS {              // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_WADI2_REG {
    uint32_t  all;
    struct  SYSCTL_WADI2_BITS  bit;
};

struct SYSCTL_INPUTXBARFLAGS_BITS {     // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_INPUTXBARFLAGS_REG {
    uint32_t  all;
    struct  SYSCTL_INPUTXBARFLAGS_BITS  bit;
};

struct SYSCTL_OUTPUTXBARFLAGS_BITS {    // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_OUTPUTXBARFLAGS_REG {
    uint32_t  all;
    struct  SYSCTL_OUTPUTXBARFLAGS_BITS  bit;
};

struct SYSCTL_DLTFIFOREGS_BITS {        // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_DLTFIFOREGS_REG {
    uint32_t  all;
    struct  SYSCTL_DLTFIFOREGS_BITS  bit;
};

struct SYSCTL_ADC_GLOBAL_REGS_BITS {    // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ADC_GLOBAL_REGS_REG {
    uint32_t  all;
    struct  SYSCTL_ADC_GLOBAL_REGS_BITS  bit;
};

struct SYSCTL_ERROR_AGGREGATOR_BITS {   // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ERROR_AGGREGATOR_REG {
    uint32_t  all;
    struct  SYSCTL_ERROR_AGGREGATOR_BITS  bit;
};

struct SYSCTL_ESM_BITS {                // bits description
    uint16_t FRAMESEL:3;                // 2:0 FRAMESEL Selection for Peripheral Instance
    uint16_t CPUSEL:3;                  // 5:3 CPUSEL Selection for Peripheral Instance
    uint16_t STANDBYEN:1;               // 6 STANDBYEN to enable peripheral clock gating based on CPUx
    uint16_t DBGHALTEN:1;               // 7 DBGHALTEN to enable peripheral clock gating based on CPUx
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_ESM_REG {
    uint32_t  all;
    struct  SYSCTL_ESM_BITS  bit;
};

struct SYSCTL_PARITY_TEST_BITS {        // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity test enable configuration
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PARITY_TEST_REG {
    uint32_t  all;
    struct  SYSCTL_PARITY_TEST_BITS  bit;
};

struct DEV_CFG_REGS {
    union   SYSCTL_DEVCFGLOCK1_REG           DEVCFGLOCK1;                  // Lock bit for PERxSYSCONFIG0-31 registers
    union   SYSCTL_DEVCFGLOCK2_REG           DEVCFGLOCK2;                  // Lock bit for DEVCFG registers
    union   SYSCTL_DEVCFGLOCK3_REG           DEVCFGLOCK3;                  // Lock bit for PERxSYSCONFIG32-63 registers
    union   SYSCTL_DEVCFGLOCK4_REG           DEVCFGLOCK4;                  // Lock bit for PERxSYSCONFIG64-95 registers
    union   SYSCTL_DEVCFGLOCK5_REG           DEVCFGLOCK5;                  // Lock bit for PERxSYSCONFIG96-127 registers
    uint8_t                                  rsvd1[12];                    // Reserved
    union   SYSCTL_PARTIDL_REG               PARTIDL;                      // Lower 32-bit of Device PART Identification Number
    union   SYSCTL_PARTIDH_REG               PARTIDH;                      // Upper 32-bit of Device PART Identification Number
    union   SYSCTL_REVID_REG                 REVID;                        // Device Revision Number
    uint8_t                                  rsvd2[404];                   // Reserved
    union   SYSCTL_MCUCNF1_REG               MCUCNF1;                      // MCUCNF Capability: EMIF Customization
    union   SYSCTL_MCUCNF2_REG               MCUCNF2;                      // MCUCNF Capability: EPWM
    uint8_t                                  rsvd3[4];                     // Reserved
    union   SYSCTL_MCUCNF4_REG               MCUCNF4;                      // MCUCNF Capability: EQEP
    uint8_t                                  rsvd4[8];                     // Reserved
    union   SYSCTL_MCUCNF7_REG               MCUCNF7;                      // MCUCNF Capability: UART
    uint8_t                                  rsvd5[8];                     // Reserved
    union   SYSCTL_MCUCNF10_REG              MCUCNF10;                     // MCUCNF Capability: CAN, MCAN
    uint8_t                                  rsvd6[8];                     // Reserved
    union   SYSCTL_MCUCNF13_REG              MCUCNF13;                     // MCUCNF Capability: AMCUCNF
    union   SYSCTL_MCUCNF14_REG              MCUCNF14;                     // MCUCNF Capability: CMPSS
    uint8_t                                  rsvd7[4];                     // Reserved
    union   SYSCTL_MCUCNF16_REG              MCUCNF16;                     // MCUCNF Capability: DAC
    union   SYSCTL_MCUCNF17_REG              MCUCNF17;                     // MCUCNF Capability: CLB
    union   SYSCTL_MCUCNF18_REG              MCUCNF18;                     // MCUCNF Capability: FSI
    union   SYSCTL_MCUCNF19_REG              MCUCNF19;                     // MCUCNF Capability: LIN
    uint8_t                                  rsvd8[12];                    // Reserved
    union   SYSCTL_MCUCNF23_REG              MCUCNF23;                     // MCUCNF Capability: EtherCAT
    uint8_t                                  rsvd9[8];                     // Reserved
    union   SYSCTL_MCUCNF26_REG              MCUCNF26;                     // Device Capability: HSM-Crypto Engines AES, SHA, PKA, TRNG
    uint8_t                                  rsvd10[16];                   // Reserved
    union   SYSCTL_MCUCNF31_REG              MCUCNF31;                     // Device Capability: HSM-Crypto Engines SM2, SM3, SM4
    uint8_t                                  rsvd11[128];                  // Reserved
    union   SYSCTL_MCUCNF64_REG              MCUCNF64;                     // MCUCNF Capability: MCUCNF level, Processing Block, RTDMA Customization
    union   SYSCTL_MCUCNF65_REG              MCUCNF65;                     // MCUCNF Capability: On-chip SRAM Customization
    uint8_t                                  rsvd12[32];                   // Reserved
    union   SYSCTL_MCUCNF74_REG              MCUCNF74;                     // MCUCNF Capability: FLC1.B0/B1
    uint8_t                                  rsvd13[4];                    // Reserved
    union   SYSCTL_MCUCNF76_REG              MCUCNF76;                     // MCUCNF Capability: FLC1.B2/B3
    uint8_t                                  rsvd14[4];                    // Reserved
    union   SYSCTL_MCUCNF78_REG              MCUCNF78;                     // MCUCNF Capability: FLC1.B4 256KB Data Flash
    union   SYSCTL_MCUCNF79_REG              MCUCNF79;                     // MCUCNF Capability: FLC2.B0/B1
    uint8_t                                  rsvd15[4];                    // Reserved
    union   SYSCTL_MCUCNF81_REG              MCUCNF81;                     // MCUCNF Capability: FLC2.B2/B3
    uint8_t                                  rsvd16[56];                   // Reserved
    union   SYSCTL_MCUCNFLOCK1_REG           MCUCNFLOCK1;                  // Lock bit for MCUCNFx registers
    uint8_t                                  rsvd17[4];                    // Reserved
    union   SYSCTL_MCUCNFLOCK3_REG           MCUCNFLOCK3;                  // Lock bit for MCUCNFx registers
    union   SYSCTL_LSEN_REG                  LSEN;                         // Lockstep enable configuration
    uint8_t                                  rsvd18[48];                   // Reserved
    union   SYSCTL_EPWMXLINKCFG_REG          EPWMXLINKCFG;                 // Configure which EPWM module instaces are linked in the XLINK scheme
    uint8_t                                  rsvd19[4];                    // Reserved
    union   SYSCTL_SICCONFIG_REG             SICCONFIG;                    // Safety Interconnect(SIC) Configuration - Enable and READY TIMEOUT value
    uint8_t                                  rsvd20[40];                   // Reserved
    union   SYSCTL_RSTSTAT_REG               RSTSTAT;                      // Reset Status register for secondary CPUs
    union   SYSCTL_LPMSTAT_REG               LPMSTAT;                      // LPM Status Register for secondary CPUs
    uint8_t                                  rsvd21[20];                   // Reserved
    union   SYSCTL_TAP_STATUS_REG            TAP_STATUS;                   // Status of JTAG State machine & Debugger Connect
    union   SYSCTL_TAP_CONTROL_REG           TAP_CONTROL;                  // Disable TAP control
    union   SYSCTL_DEVLIFECYCLE_REG          DEVLIFECYCLE;                 // Reflect the state of the Device Life Cycle signals reported from the HSM
    uint8_t                                  rsvd22[164];                  // Reserved
    union   SYSCTL_SDFMTYPE_REG              SDFMTYPE;                     // Configures SDFM Type for the device
    uint8_t                                  rsvd23[44];                   // Reserved
    union   SYSCTL_SYNCSELECT_REG            SYNCSELECT;                   // Sync Input and Output Select Register
    union   SYSCTL_ADCSOCOUTSELECT_REG       ADCSOCOUTSELECT;              // External ADCSOC Select Register (PWM1-16)
    union   SYSCTL_ADCSOCOUTSELECT1_REG      ADCSOCOUTSELECT1;             // External ADCSOC Select Register (PWM17-32)
    union   SYSCTL_SYNCSOCLOCK_REG           SYNCSOCLOCK;                  // SYNCSEL and ADCSOC Select Lock register
    uint8_t                                  rsvd24[32];                   // Reserved
    union   SYSCTL_HSMTOCPU_STS1_REG         HSMTOCPU_STS1;                // HSM to C29x Signal Status1
    union   SYSCTL_HSMTOCPU_STS2_REG         HSMTOCPU_STS2;                // HSM to C29x Signal Status2
    uint32_t                                 HSM_SECURE_BOOT_INFO_REG0;    // Status information of the secure boot process HSM to CPU1
    uint32_t                                 HSM_SECURE_BOOT_INFO_REG1;    // Status information of the secure boot process HSM to CPU1
    uint32_t                                 HSM_SECURE_BOOT_INFO_REG2;    // Status information of the secure boot process HSM to CPU1
    uint32_t                                 HSM_SECURE_BOOT_INFO_REG3;    // Status information of the secure boot process HSM to CPU1
    uint32_t                                 HSM_SECURE_BOOT_INFO_REG4;    // Status information of the secure boot process HSM to CPU1
    uint32_t                                 HSM_SECURE_BOOT_INFO_REG5;    // Status information of the secure boot process HSM to CPU1
    uint32_t                                 HSM_SECURE_BOOT_INFO_REG6;    // Status information of the secure boot process HSM to CPU1
    uint32_t                                 HSM_SECURE_BOOT_INFO_REG7;    // Status information of the secure boot process HSM to CPU1
    uint32_t                                 SOC_SECURE_BOOT_INFO_REG0;    // Status information of the secure boot process CPU1 to HSM
    uint32_t                                 SOC_SECURE_BOOT_INFO_REG1;    // Status information of the secure boot process CPU1 to HSM
    uint32_t                                 SOC_SECURE_BOOT_INFO_REG2;    // Status information of the secure boot process CPU1 to HSM
    uint32_t                                 SOC_SECURE_BOOT_INFO_REG3;    // Status information of the secure boot process CPU1 to HSM
    uint32_t                                 SOC_SECURE_BOOT_INFO_REG4;    // Status information of the secure boot process CPU1 to HSM
    uint32_t                                 SOC_SECURE_BOOT_INFO_REG5;    // Status information of the secure boot process CPU1 to HSM
    uint32_t                                 SOC_SECURE_BOOT_INFO_REG6;    // Status information of the secure boot process CPU1 to HSM
    uint32_t                                 SOC_SECURE_BOOT_INFO_REG7;    // Status information of the secure boot process CPU1 to HSM
    union   SYSCTL_CLKCFGLOCK1_REG           CLKCFGLOCK1;                  // Lock bit for CLKCFG registers
    uint8_t                                  rsvd25[8];                    // Reserved
    union   SYSCTL_CLKSRCCTL1_REG            CLKSRCCTL1;                   // Clock Source Control register-1
    union   SYSCTL_CLKSRCCTL2_REG            CLKSRCCTL2;                   // Clock Source Control register-2
    union   SYSCTL_CLKSRCCTL3_REG            CLKSRCCTL3;                   // Clock Source Control register-3
    union   SYSCTL_SYSPLLCTL1_REG            SYSPLLCTL1;                   // SYSPLL Control register-1
    uint8_t                                  rsvd26[8];                    // Reserved
    union   SYSCTL_SYSPLLMULT_REG            SYSPLLMULT;                   // SYSPLL Multiplier register
    union   SYSCTL_SYSPLLSTS_REG             SYSPLLSTS;                    // SYSPLL Status register
    uint8_t                                  rsvd27[20];                   // Reserved
    union   SYSCTL_SYSCLKDIVSEL_REG          SYSCLKDIVSEL;                 // System Clock Divider Select register
    uint8_t                                  rsvd28[4];                    // Reserved
    union   SYSCTL_PERCLKDIVSEL_REG          PERCLKDIVSEL;                 // Peripheral Clock Divider Select register
    union   SYSCTL_XCLKOUTDIVSEL_REG         XCLKOUTDIVSEL;                // XCLKOUT Divider Select register
    union   SYSCTL_HSMCLKDIVSEL_REG          HSMCLKDIVSEL;                 // HSM SYSCLK Divider Select register
    union   SYSCTL_MCANCLKDIVSEL_REG         MCANCLKDIVSEL;                // MCAN Bit Clock Divider Select register
    union   SYSCTL_CLBCLKCTL_REG             CLBCLKCTL;                    // CLB Clocking Control Register
    uint8_t                                  rsvd29[4];                    // Reserved
    union   SYSCTL_MCDCR_REG                 MCDCR;                        // Missing Clock Detect Control Register
    union   SYSCTL_X1CNT_REG                 X1CNT;                        // 10-bit Counter on X1 Clock
    union   SYSCTL_XTALCR_REG                XTALCR;                       // XTAL Control Register
    uint8_t                                  rsvd30[12];                   // Reserved
    union   SYSCTL_XTALCR2_REG               XTALCR2;                      // XTAL Control Register for pad init
    uint8_t                                  rsvd31[8];                    // Reserved
    union   SYSCTL_ETHERCATCLKCTL_REG        ETHERCATCLKCTL;               // EtherCAT Clock Control
    union   SYSCTL_ETHERCATCTL_REG           ETHERCATCTL;                  // ETHERCAT control register.
    union   SYSCTL_SYNCBUSY_REG              SYNCBUSY;                     // Pulse Transfer Sync Busy Status register
    uint8_t                                  rsvd32[12];                   // Reserved
    union   SYSCTL_ESMXRSNCTL_REG            ESMXRSNCTL;                   // Enable ESM reset outputs for XRSn
    uint8_t                                  rsvd33[4];                    // Reserved
    union   SYSCTL_EPWM1_REG                 EPWM1;                        // PER2SYSCONFIG -  Peripheral System Configuration for EPWM1
    union   SYSCTL_EPWM2_REG                 EPWM2;                        // PER3SYSCONFIG -  Peripheral System Configuration for EPWM2
    union   SYSCTL_EPWM3_REG                 EPWM3;                        // PER4SYSCONFIG -  Peripheral System Configuration for EPWM3
    union   SYSCTL_EPWM4_REG                 EPWM4;                        // PER5SYSCONFIG -  Peripheral System Configuration for EPWM4
    union   SYSCTL_EPWM5_REG                 EPWM5;                        // PER6SYSCONFIG -  Peripheral System Configuration for EPWM5
    union   SYSCTL_EPWM6_REG                 EPWM6;                        // PER7SYSCONFIG -  Peripheral System Configuration for EPWM6
    union   SYSCTL_EPWM7_REG                 EPWM7;                        // PER8SYSCONFIG -  Peripheral System Configuration for EPWM7
    union   SYSCTL_EPWM8_REG                 EPWM8;                        // PER9SYSCONFIG -  Peripheral System Configuration for EPWM8
    union   SYSCTL_EPWM9_REG                 EPWM9;                        // PER10SYSCONFIG -  Peripheral System Configuration for EPWM9
    union   SYSCTL_EPWM10_REG                EPWM10;                       // PER11SYSCONFIG -  Peripheral System Configuration for EPWM10
    union   SYSCTL_EPWM11_REG                EPWM11;                       // PER12SYSCONFIG -  Peripheral System Configuration for EPWM11
    union   SYSCTL_EPWM12_REG                EPWM12;                       // PER13SYSCONFIG -  Peripheral System Configuration for EPWM12
    union   SYSCTL_EPWM13_REG                EPWM13;                       // PER14SYSCONFIG -  Peripheral System Configuration for EPWM13
    union   SYSCTL_EPWM14_REG                EPWM14;                       // PER15SYSCONFIG -  Peripheral System Configuration for EPWM14
    union   SYSCTL_EPWM15_REG                EPWM15;                       // PER16SYSCONFIG -  Peripheral System Configuration for EPWM15
    union   SYSCTL_EPWM16_REG                EPWM16;                       // PER17SYSCONFIG -  Peripheral System Configuration for EPWM16
    union   SYSCTL_EPWM17_REG                EPWM17;                       // PER18SYSCONFIG -  Peripheral System Configuration for EPWM17
    union   SYSCTL_EPWM18_REG                EPWM18;                       // PER19SYSCONFIG -  Peripheral System Configuration for EPWM18
    uint8_t                                  rsvd34[4];                    // Reserved
    union   SYSCTL_HRCAL0_REG                HRCAL0;                       // PER21SYSCONFIG -  Peripheral System Configuration for HRCAL0
    union   SYSCTL_HRCAL1_REG                HRCAL1;                       // PER22SYSCONFIG -  Peripheral System Configuration for HRCAL1
    union   SYSCTL_HRCAL2_REG                HRCAL2;                       // PER23SYSCONFIG -  Peripheral System Configuration for HRCAL2
    union   SYSCTL_ECAP1_REG                 ECAP1;                        // PER24SYSCONFIG -  Peripheral System Configuration for ECAP1
    union   SYSCTL_ECAP2_REG                 ECAP2;                        // PER25SYSCONFIG -  Peripheral System Configuration for ECAP2
    union   SYSCTL_ECAP3_REG                 ECAP3;                        // PER26SYSCONFIG -  Peripheral System Configuration for ECAP3
    union   SYSCTL_ECAP4_REG                 ECAP4;                        // PER27SYSCONFIG -  Peripheral System Configuration for ECAP4
    union   SYSCTL_ECAP5_REG                 ECAP5;                        // PER28SYSCONFIG -  Peripheral System Configuration for ECAP5
    union   SYSCTL_ECAP6_REG                 ECAP6;                        // PER29SYSCONFIG -  Peripheral System Configuration for ECAP6
    union   SYSCTL_EQEP1_REG                 EQEP1;                        // PER30SYSCONFIG -  Peripheral System Configuration for EQEP1
    union   SYSCTL_EQEP2_REG                 EQEP2;                        // PER31SYSCONFIG -  Peripheral System Configuration for EQEP2
    union   SYSCTL_EQEP3_REG                 EQEP3;                        // PER32SYSCONFIG -  Peripheral System Configuration for EQEP3
    union   SYSCTL_EQEP4_REG                 EQEP4;                        // PER33SYSCONFIG -  Peripheral System Configuration for EQEP4
    union   SYSCTL_EQEP5_REG                 EQEP5;                        // PER34SYSCONFIG -  Peripheral System Configuration for EQEP5
    union   SYSCTL_EQEP6_REG                 EQEP6;                        // PER35SYSCONFIG -  Peripheral System Configuration for EQEP6
    union   SYSCTL_SDFM1_REG                 SDFM1;                        // PER36SYSCONFIG -  Peripheral System Configuration for SDFM1
    union   SYSCTL_SDFM2_REG                 SDFM2;                        // PER37SYSCONFIG -  Peripheral System Configuration for SDFM2
    union   SYSCTL_SDFM3_REG                 SDFM3;                        // PER38SYSCONFIG -  Peripheral System Configuration for SDFM3
    union   SYSCTL_SDFM4_REG                 SDFM4;                        // PER39SYSCONFIG -  Peripheral System Configuration for SDFM4
    union   SYSCTL_UARTA_REG                 UARTA;                        // PER40SYSCONFIG -  Peripheral System Configuration for UARTA
    union   SYSCTL_UARTB_REG                 UARTB;                        // PER41SYSCONFIG -  Peripheral System Configuration for UARTB
    union   SYSCTL_UARTC_REG                 UARTC;                        // PER42SYSCONFIG -  Peripheral System Configuration for UARTC
    union   SYSCTL_UARTD_REG                 UARTD;                        // PER43SYSCONFIG -  Peripheral System Configuration for UARTD
    union   SYSCTL_UARTE_REG                 UARTE;                        // PER44SYSCONFIG -  Peripheral System Configuration for UARTE
    union   SYSCTL_UARTF_REG                 UARTF;                        // PER45SYSCONFIG -  Peripheral System Configuration for UARTF
    union   SYSCTL_SPIA_REG                  SPIA;                         // PER46SYSCONFIG -  Peripheral System Configuration for SPIA
    union   SYSCTL_SPIB_REG                  SPIB;                         // PER47SYSCONFIG -  Peripheral System Configuration for SPIB
    union   SYSCTL_SPIC_REG                  SPIC;                         // PER48SYSCONFIG -  Peripheral System Configuration for SPIC
    union   SYSCTL_SPID_REG                  SPID;                         // PER49SYSCONFIG -  Peripheral System Configuration for SPID
    union   SYSCTL_SPIE_REG                  SPIE;                         // PER50SYSCONFIG -  Peripheral System Configuration for SPIE
    union   SYSCTL_I2CA_REG                  I2CA;                         // PER51SYSCONFIG -  Peripheral System Configuration for I2CA
    union   SYSCTL_I2CB_REG                  I2CB;                         // PER52SYSCONFIG -  Peripheral System Configuration for I2CB
    union   SYSCTL_PMBUSA_REG                PMBUSA;                       // PER53SYSCONFIG -  Peripheral System Configuration for PMBUSA
    union   SYSCTL_LINA_REG                  LINA;                         // PER54SYSCONFIG -  Peripheral System Configuration for LINA
    union   SYSCTL_LINB_REG                  LINB;                         // PER55SYSCONFIG -  Peripheral System Configuration for LINB
    union   SYSCTL_MCANA_REG                 MCANA;                        // PER56SYSCONFIG -  Peripheral System Configuration for MCANA
    union   SYSCTL_MCANB_REG                 MCANB;                        // PER57SYSCONFIG -  Peripheral System Configuration for MCANB
    union   SYSCTL_MCANC_REG                 MCANC;                        // PER58SYSCONFIG -  Peripheral System Configuration for MCANC
    union   SYSCTL_MCAND_REG                 MCAND;                        // PER59SYSCONFIG -  Peripheral System Configuration for MCAND
    union   SYSCTL_MCANE_REG                 MCANE;                        // PER60SYSCONFIG -  Peripheral System Configuration for MCANE
    union   SYSCTL_MCANF_REG                 MCANF;                        // PER61SYSCONFIG -  Peripheral System Configuration for MCANF
    union   SYSCTL_ADCA_REG                  ADCA;                         // PER62SYSCONFIG -  Peripheral System Configuration for ADCA
    union   SYSCTL_ADCB_REG                  ADCB;                         // PER63SYSCONFIG -  Peripheral System Configuration for ADCB
    union   SYSCTL_ADCC_REG                  ADCC;                         // PER64SYSCONFIG -  Peripheral System Configuration for ADCC
    union   SYSCTL_ADCD_REG                  ADCD;                         // PER65SYSCONFIG -  Peripheral System Configuration for ADCD
    union   SYSCTL_ADCE_REG                  ADCE;                         // PER66SYSCONFIG -  Peripheral System Configuration for ADCE
    union   SYSCTL_CMPSS1_REG                CMPSS1;                       // PER67SYSCONFIG -  Peripheral System Configuration for CMPSS1
    union   SYSCTL_CMPSS2_REG                CMPSS2;                       // PER68SYSCONFIG -  Peripheral System Configuration for CMPSS2
    union   SYSCTL_CMPSS3_REG                CMPSS3;                       // PER69SYSCONFIG -  Peripheral System Configuration for CMPSS3
    union   SYSCTL_CMPSS4_REG                CMPSS4;                       // PER70SYSCONFIG -  Peripheral System Configuration for CMPSS4
    union   SYSCTL_CMPSS5_REG                CMPSS5;                       // PER71SYSCONFIG -  Peripheral System Configuration for CMPSS5
    union   SYSCTL_CMPSS6_REG                CMPSS6;                       // PER72SYSCONFIG -  Peripheral System Configuration for CMPSS6
    union   SYSCTL_CMPSS7_REG                CMPSS7;                       // PER73SYSCONFIG -  Peripheral System Configuration for CMPSS7
    union   SYSCTL_CMPSS8_REG                CMPSS8;                       // PER74SYSCONFIG -  Peripheral System Configuration for CMPSS8
    union   SYSCTL_CMPSS9_REG                CMPSS9;                       // PER75SYSCONFIG -  Peripheral System Configuration for CMPSS9
    union   SYSCTL_CMPSS10_REG               CMPSS10;                      // PER76SYSCONFIG -  Peripheral System Configuration for CMPSS10
    union   SYSCTL_CMPSS11_REG               CMPSS11;                      // PER77SYSCONFIG -  Peripheral System Configuration for CMPSS11
    union   SYSCTL_CMPSS12_REG               CMPSS12;                      // PER78SYSCONFIG -  Peripheral System Configuration for CMPSS12
    union   SYSCTL_DACA_REG                  DACA;                         // PER79SYSCONFIG -  Peripheral System Configuration for DACA
    union   SYSCTL_DACB_REG                  DACB;                         // PER80SYSCONFIG -  Peripheral System Configuration for DACB
    union   SYSCTL_CLB1_REG                  CLB1;                         // PER81SYSCONFIG -  Peripheral System Configuration for CLB1
    union   SYSCTL_CLB2_REG                  CLB2;                         // PER82SYSCONFIG -  Peripheral System Configuration for CLB2
    union   SYSCTL_CLB3_REG                  CLB3;                         // PER83SYSCONFIG -  Peripheral System Configuration for CLB3
    union   SYSCTL_CLB4_REG                  CLB4;                         // PER84SYSCONFIG -  Peripheral System Configuration for CLB4
    union   SYSCTL_CLB5_REG                  CLB5;                         // PER85SYSCONFIG -  Peripheral System Configuration for CLB5
    union   SYSCTL_CLB6_REG                  CLB6;                         // PER86SYSCONFIG -  Peripheral System Configuration for CLB6
    union   SYSCTL_FSITXA_REG                FSITXA;                       // PER87SYSCONFIG -  Peripheral System Configuration for FSITXA
    union   SYSCTL_FSITXB_REG                FSITXB;                       // PER88SYSCONFIG -  Peripheral System Configuration for FSITXB
    union   SYSCTL_FSITXC_REG                FSITXC;                       // PER89SYSCONFIG -  Peripheral System Configuration for FSITXC
    union   SYSCTL_FSITXD_REG                FSITXD;                       // PER90SYSCONFIG -  Peripheral System Configuration for FSITXD
    union   SYSCTL_FSIRXA_REG                FSIRXA;                       // PER91SYSCONFIG -  Peripheral System Configuration for FSIRXA
    union   SYSCTL_FSIRXB_REG                FSIRXB;                       // PER92SYSCONFIG -  Peripheral System Configuration for FSIRXB
    union   SYSCTL_FSIRXC_REG                FSIRXC;                       // PER93SYSCONFIG -  Peripheral System Configuration for FSIRXC
    union   SYSCTL_FSIRXD_REG                FSIRXD;                       // PER94SYSCONFIG -  Peripheral System Configuration for FSIRXD
    union   SYSCTL_DCC1_REG                  DCC1;                         // PER95SYSCONFIG -  Peripheral System Configuration for DCC1
    union   SYSCTL_DCC2_REG                  DCC2;                         // PER96SYSCONFIG -  Peripheral System Configuration for DCC2
    union   SYSCTL_DCC3_REG                  DCC3;                         // PER97SYSCONFIG -  Peripheral System Configuration for DCC3
    union   SYSCTL_ETHERCATA_REG             ETHERCATA;                    // PER98SYSCONFIG -  Peripheral System Configuration for ETHERCATA
    union   SYSCTL_EPG1_REG                  EPG1;                         // PER99SYSCONFIG -  Peripheral System Configuration for EPG1
    union   SYSCTL_SENT1_REG                 SENT1;                        // PER100SYSCONFIG -  Peripheral System Configuration for SENT1
    union   SYSCTL_SENT2_REG                 SENT2;                        // PER101SYSCONFIG -  Peripheral System Configuration for SENT2
    union   SYSCTL_SENT3_REG                 SENT3;                        // PER102SYSCONFIG -  Peripheral System Configuration for SENT3
    union   SYSCTL_SENT4_REG                 SENT4;                        // PER103SYSCONFIG -  Peripheral System Configuration for SENT4
    union   SYSCTL_SENT5_REG                 SENT5;                        // PER104SYSCONFIG -  Peripheral System Configuration for SENT5
    union   SYSCTL_SENT6_REG                 SENT6;                        // PER105SYSCONFIG -  Peripheral System Configuration for SENT6
    union   SYSCTL_ADCCHECKER1_REG           ADCCHECKER1;                  // PER106SYSCONFIG -  Peripheral System Configuration for ADCCHECKER1
    union   SYSCTL_ADCCHECKER2_REG           ADCCHECKER2;                  // PER107SYSCONFIG -  Peripheral System Configuration for ADCCHECKER2
    union   SYSCTL_ADCCHECKER3_REG           ADCCHECKER3;                  // PER108SYSCONFIG -  Peripheral System Configuration for ADCCHECKER3
    union   SYSCTL_ADCCHECKER4_REG           ADCCHECKER4;                  // PER109SYSCONFIG -  Peripheral System Configuration for ADCCHECKER4
    union   SYSCTL_ADCCHECKER5_REG           ADCCHECKER5;                  // PER110SYSCONFIG -  Peripheral System Configuration for ADCCHECKER5
    union   SYSCTL_ADCCHECKER6_REG           ADCCHECKER6;                  // PER111SYSCONFIG -  Peripheral System Configuration for ADCCHECKER6
    union   SYSCTL_ADCCHECKER7_REG           ADCCHECKER7;                  // PER112SYSCONFIG -  Peripheral System Configuration for ADCCHECKER7
    union   SYSCTL_ADCCHECKER8_REG           ADCCHECKER8;                  // PER113SYSCONFIG -  Peripheral System Configuration for ADCCHECKER8
    union   SYSCTL_ADCCHECKER9_REG           ADCCHECKER9;                  // PER114SYSCONFIG -  Peripheral System Configuration for ADCCHECKER9
    union   SYSCTL_ADCCHECKER10_REG          ADCCHECKER10;                 // PER115SYSCONFIG -  Peripheral System Configuration for ADCCHECKER10
    union   SYSCTL_ADCSEAGGRCPU1_REG         ADCSEAGGRCPU1;                // PER116SYSCONFIG -  Peripheral System Configuration for ADCSEAGGRCPU1
    union   SYSCTL_ADCSEAGGRCPU2_REG         ADCSEAGGRCPU2;                // PER117SYSCONFIG -  Peripheral System Configuration for ADCSEAGGRCPU2
    union   SYSCTL_ADCSEAGGRCPU3_REG         ADCSEAGGRCPU3;                // PER118SYSCONFIG -  Peripheral System Configuration for ADCSEAGGRCPU3
    uint8_t                                  rsvd35[12];                   // Reserved
    union   SYSCTL_RTDMA1CH_REG              RTDMA1CH;                     // PER122SYSCONFIG -  Peripheral System Configuration for RTDMA1CH
    union   SYSCTL_RTDMA2CH_REG              RTDMA2CH;                     // PER123SYSCONFIG -  Peripheral System Configuration for RTDMA2CH
    union   SYSCTL_WADI1_REG                 WADI1;                        // PER124SYSCONFIG -  Peripheral System Configuration for WADI1
    union   SYSCTL_WADI2_REG                 WADI2;                        // PER125SYSCONFIG -  Peripheral System Configuration for WADI2
    union   SYSCTL_INPUTXBARFLAGS_REG        INPUTXBARFLAGS;               // PER126SYSCONFIG -  Peripheral System Configuration for INPUTXBARFlags
    union   SYSCTL_OUTPUTXBARFLAGS_REG       OUTPUTXBARFLAGS;              // PER127SYSCONFIG -  Peripheral System Configuration for OUTPUTXBARFlags
    union   SYSCTL_DLTFIFOREGS_REG           DLTFIFOREGS;                  // PER128SYSCONFIG -  Peripheral System Configuration for DLTFIFORegs
    union   SYSCTL_ADC_GLOBAL_REGS_REG       ADC_GLOBAL_REGS;              // PER129SYSCONFIG -  Peripheral System Configuration for ADC_GLOBAL_REGS
    union   SYSCTL_ERROR_AGGREGATOR_REG      ERROR_AGGREGATOR;             // PER130SYSCONFIG -  Peripheral System Configuration for Error_Aggregator
    union   SYSCTL_ESM_REG                   ESM;                          // PER131SYSCONFIG -  Peripheral System Configuration for ESM ESMCPU1/2/3 and ESMSYS
    uint8_t                                  rsvd36[20];                   // Reserved
    union   SYSCTL_PARITY_TEST_REG           PARITY_TEST;                  // Enables parity test
};

struct SYSCTL_CPUPERCFGLOCK1_BITS {     // bits description
    uint16_t PCLKCR0:1;                 // 0 Lock bit for PCLKCR0 Register
    uint16_t PCLKCR1:1;                 // 1 Lock bit for PCLKCR1 Register
    uint16_t PCLKCR2:1;                 // 2 Lock bit for PCLKCR2 Register
    uint16_t PCLKCR3:1;                 // 3 Lock bit for PCLKCR3 Register
    uint16_t PCLKCR4:1;                 // 4 Lock bit for PCLKCR4 Register
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t PCLKCR6:1;                 // 6 Lock bit for PCLKCR6 Register
    uint16_t PCLKCR7:1;                 // 7 Lock bit for PCLKCR7 Register
    uint16_t PCLKCR8:1;                 // 8 Lock bit for PCLKCR8 Register
    uint16_t PCLKCR9:1;                 // 9 Lock bit for PCLKCR9 Register
    uint16_t PCLKCR10:1;                // 10 Lock bit for PCLKCR10 Register
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t rsvd3:1;                   // 12 Reserved
    uint16_t PCLKCR13:1;                // 13 Lock bit for PCLKCR13 Register
    uint16_t PCLKCR14:1;                // 14 Lock bit for PCLKCR14 Register
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t PCLKCR16:1;                // 16 Lock bit for PCLKCR16 Register
    uint16_t PCLKCR17:1;                // 17 Lock bit for PCLKCR17 Register
    uint16_t PCLKCR18:1;                // 18 Lock bit for PCLKCR18 Register
    uint16_t PCLKCR19:1;                // 19 Lock bit for PCLKCR19 Register
    uint16_t PCLKCR20:1;                // 20 Lock bit for PCLKCR20 Register
    uint16_t PCLKCR21:1;                // 21 Lock bit for PCLKCR21 Register
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t PCLKCR23:1;                // 23 Lock bit for PCLKCR23 Register
    uint16_t rsvd6:1;                   // 24 Reserved
    uint16_t PCLKCR25:1;                // 25 Lock bit for PCLKCR25 Register
    uint16_t rsvd7:1;                   // 26 Reserved
    uint16_t PCLKCR27:1;                // 27 Lock bit for PCLKCR27 Register
    uint16_t PCLKCR28:1;                // 28 Lock bit for PCLKCR28 Register
    uint16_t rsvd8:1;                   // 29 Reserved
    uint16_t PCLKCR30:1;                // 30 Lock bit for PCLKCR30 Register
    uint16_t rsvd9:1;                   // 31 Reserved
};

union SYSCTL_CPUPERCFGLOCK1_REG {
    uint32_t  all;
    struct  SYSCTL_CPUPERCFGLOCK1_BITS  bit;
};

struct SYSCTL_CPUPERCFGLOCK2_BITS {     // bits description
    uint16_t PCLKCR32:1;                // 0 Lock bit for PCLKCR32 Register
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CPUPERCFGLOCK2_REG {
    uint32_t  all;
    struct  SYSCTL_CPUPERCFGLOCK2_BITS  bit;
};

struct SYSCTL_PCLKCR0_BITS {            // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t RTDMA1:1;                  // 2 RTDMA1 Clock Enable Bit
    uint16_t RTDMA2:1;                  // 3 RTDMA2 Clock Enable Bit
    uint16_t CPUTIMER0:1;               // 4 CPUTIMER0 Clock Enable Bit
    uint16_t CPUTIMER1:1;               // 5 CPUTIMER1 Clock Enable Bit
    uint16_t CPUTIMER2:1;               // 6 CPUTIMER2 Clock Enable Bit
    uint16_t rsvd3:9;                   // 15:7 Reserved
    uint16_t rsvd4:3;                   // 18:16 Reserved
    uint16_t TBCLKSYNC:1;               // 19 TBCLKSYNC Clock Enable Bit
    uint16_t GTBCLKSYNC:1;              // 20 GTBCLKSYNC Clock Enable Bit
    uint16_t rsvd5:3;                   // 23:21 Reserved
    uint16_t CPUx_ERAD:1;               // 24 CPUx_ERAD Clock Enable Bit
    uint16_t CPUx_DLT:1;                // 25 CPUx_DLT Clock Enable Bit
    uint16_t rsvd6:6;                   // 31:26 Reserved
};

union SYSCTL_PCLKCR0_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR0_BITS  bit;
};

struct SYSCTL_PCLKCR1_BITS {            // bits description
    uint16_t EMIF1:1;                   // 0 EMIF1 Clock Enable bit
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR1_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR1_BITS  bit;
};

struct SYSCTL_PCLKCR2_BITS {            // bits description
    uint16_t EPWM1:1;                   // 0 EPWM1 Clock Enable bit
    uint16_t EPWM2:1;                   // 1 EPWM2 Clock Enable bit
    uint16_t EPWM3:1;                   // 2 EPWM3 Clock Enable bit
    uint16_t EPWM4:1;                   // 3 EPWM4 Clock Enable bit
    uint16_t EPWM5:1;                   // 4 EPWM5 Clock Enable bit
    uint16_t EPWM6:1;                   // 5 EPWM6 Clock Enable bit
    uint16_t EPWM7:1;                   // 6 EPWM7 Clock Enable bit
    uint16_t EPWM8:1;                   // 7 EPWM8 Clock Enable bit
    uint16_t EPWM9:1;                   // 8 EPWM9 Clock Enable bit
    uint16_t EPWM10:1;                  // 9 EPWM10 Clock Enable bit
    uint16_t EPWM11:1;                  // 10 EPWM11 Clock Enable bit
    uint16_t EPWM12:1;                  // 11 EPWM12 Clock Enable bit
    uint16_t EPWM13:1;                  // 12 EPWM13 Clock Enable bit
    uint16_t EPWM14:1;                  // 13 EPWM14 Clock Enable bit
    uint16_t EPWM15:1;                  // 14 EPWM15 Clock Enable bit
    uint16_t EPWM16:1;                  // 15 EPWM16 Clock Enable bit
    uint16_t EPWM17:1;                  // 16 EPWM17 Clock Enable bit
    uint16_t EPWM18:1;                  // 17 EPWM18 Clock Enable bit
    uint16_t rsvd1:14;                  // 31:18 Reserved
};

union SYSCTL_PCLKCR2_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR2_BITS  bit;
};

struct SYSCTL_PCLKCR3_BITS {            // bits description
    uint16_t ECAP1:1;                   // 0 ECAP1 Clock Enable bit
    uint16_t ECAP2:1;                   // 1 ECAP2 Clock Enable bit
    uint16_t ECAP3:1;                   // 2 ECAP3 Clock Enable bit
    uint16_t ECAP4:1;                   // 3 ECAP4 Clock Enable bit
    uint16_t ECAP5:1;                   // 4 ECAP5 Clock Enable bit
    uint16_t ECAP6:1;                   // 5 ECAP6 Clock Enable bit
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t rsvd3:8;                   // 15:8 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR3_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR3_BITS  bit;
};

struct SYSCTL_PCLKCR4_BITS {            // bits description
    uint16_t EQEP1:1;                   // 0 EQEP1 Clock Enable bit
    uint16_t EQEP2:1;                   // 1 EQEP2 Clock Enable bit
    uint16_t EQEP3:1;                   // 2 EQEP3 Clock Enable bit
    uint16_t EQEP4:1;                   // 3 EQEP4 Clock Enable bit
    uint16_t EQEP5:1;                   // 4 EQEP5 Clock Enable bit
    uint16_t EQEP6:1;                   // 5 EQEP6 Clock Enable bit
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR4_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR4_BITS  bit;
};

struct SYSCTL_PCLKCR6_BITS {            // bits description
    uint16_t SD1:1;                     // 0 SD1 Clock Enable bit
    uint16_t SD2:1;                     // 1 SD2 Clock Enable bit
    uint16_t SD3:1;                     // 2 SD3 Clock Enable bit
    uint16_t SD4:1;                     // 3 SD4 Clock Enable bit
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:8;                   // 15:8 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR6_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR6_BITS  bit;
};

struct SYSCTL_PCLKCR7_BITS {            // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:12;                  // 15:4 Reserved
    uint16_t UART_A:1;                  // 16 UART_A Clock Enable bit
    uint16_t UART_B:1;                  // 17 UART_B Clock Enable bit
    uint16_t UART_C:1;                  // 18 UART_C Clock Enable bit
    uint16_t UART_D:1;                  // 19 UART_D Clock Enable bit
    uint16_t UART_E:1;                  // 20 UART_E Clock Enable bit
    uint16_t UART_F:1;                  // 21 UART_F Clock Enable bit
    uint16_t rsvd6:10;                  // 31:22 Reserved
};

union SYSCTL_PCLKCR7_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR7_BITS  bit;
};

struct SYSCTL_PCLKCR8_BITS {            // bits description
    uint16_t SPI_A:1;                   // 0 SPI_A Clock Enable bit
    uint16_t SPI_B:1;                   // 1 SPI_B Clock Enable bit
    uint16_t SPI_C:1;                   // 2 SPI_C Clock Enable bit
    uint16_t SPI_D:1;                   // 3 SPI_D Clock Enable bit
    uint16_t SPI_E:1;                   // 4 SPI_E Clock Enable bit
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:1;                   // 16 Reserved
    uint16_t rsvd3:1;                   // 17 Reserved
    uint16_t rsvd4:14;                  // 31:18 Reserved
};

union SYSCTL_PCLKCR8_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR8_BITS  bit;
};

struct SYSCTL_PCLKCR9_BITS {            // bits description
    uint16_t I2C_A:1;                   // 0 I2C_A Clock Enable bit
    uint16_t I2C_B:1;                   // 1 I2C_B Clock Enable bit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR9_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR9_BITS  bit;
};

struct SYSCTL_PCLKCR10_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t MCAN_A:1;                  // 4 MCAN_A Clock Enable bit
    uint16_t MCAN_B:1;                  // 5 MCAN_B Clock Enable bit
    uint16_t MCAN_C:1;                  // 6 MCAN_C Clock Enable bit
    uint16_t MCAN_D:1;                  // 7 MCAN_D Clock Enable bit
    uint16_t MCAN_E:1;                  // 8 MCAN_E Clock Enable bit
    uint16_t MCAN_F:1;                  // 9 MCAN_F Clock Enable bit
    uint16_t rsvd5:6;                   // 15:10 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR10_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR10_BITS  bit;
};

struct SYSCTL_PCLKCR13_BITS {           // bits description
    uint16_t ADC_A:1;                   // 0 ADC_A Clock Enable bit
    uint16_t ADC_B:1;                   // 1 ADC_B Clock Enable bit
    uint16_t ADC_C:1;                   // 2 ADC_C Clock Enable bit
    uint16_t ADC_D:1;                   // 3 ADC_D Clock Enable bit
    uint16_t ADC_E:1;                   // 4 ADC_E Clock Enable bit
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR13_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR13_BITS  bit;
};

struct SYSCTL_PCLKCR14_BITS {           // bits description
    uint16_t CMPSS1:1;                  // 0 CMPSS1 Clock Enable bit
    uint16_t CMPSS2:1;                  // 1 CMPSS2 Clock Enable bit
    uint16_t CMPSS3:1;                  // 2 CMPSS3 Clock Enable bit
    uint16_t CMPSS4:1;                  // 3 CMPSS4 Clock Enable bit
    uint16_t CMPSS5:1;                  // 4 CMPSS5 Clock Enable bit
    uint16_t CMPSS6:1;                  // 5 CMPSS6 Clock Enable bit
    uint16_t CMPSS7:1;                  // 6 CMPSS7 Clock Enable bit
    uint16_t CMPSS8:1;                  // 7 CMPSS8 Clock Enable bit
    uint16_t CMPSS9:1;                  // 8 CMPSS9 Clock Enable bit
    uint16_t CMPSS10:1;                 // 9 CMPSS10 Clock Enable bit
    uint16_t CMPSS11:1;                 // 10 CMPSS11 Clock Enable bit
    uint16_t CMPSS12:1;                 // 11 CMPSS12 Clock Enable bit
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR14_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR14_BITS  bit;
};

struct SYSCTL_PCLKCR16_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:12;                  // 15:4 Reserved
    uint16_t DAC_A:1;                   // 16 DAC_A Clock Enable bit
    uint16_t DAC_B:1;                   // 17 DAC_B Clock Enable bit
    uint16_t rsvd6:1;                   // 18 Reserved
    uint16_t rsvd7:1;                   // 19 Reserved
    uint16_t rsvd8:12;                  // 31:20 Reserved
};

union SYSCTL_PCLKCR16_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR16_BITS  bit;
};

struct SYSCTL_PCLKCR17_BITS {           // bits description
    uint16_t CLB1:1;                    // 0 CLB1 Clock Enable bit
    uint16_t CLB2:1;                    // 1 CLB2 Clock Enable bit
    uint16_t CLB3:1;                    // 2 CLB3 Clock Enable bit
    uint16_t CLB4:1;                    // 3 CLB4 Clock Enable bit
    uint16_t CLB5:1;                    // 4 CLB5 Clock Enable bit
    uint16_t CLB6:1;                    // 5 CLB6 Clock Enable bit
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR17_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR17_BITS  bit;
};

struct SYSCTL_PCLKCR18_BITS {           // bits description
    uint16_t FSITX_A:1;                 // 0 FSITX_A Clock Enable bit
    uint16_t FSITX_B:1;                 // 1 FSITX_B Clock Enable bit
    uint16_t FSITX_C:1;                 // 2 FSITX_C Clock Enable bit
    uint16_t FSITX_D:1;                 // 3 FSITX_D Clock Enable bit
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t FSIRX_A:1;                 // 16 FSIRX_A Clock Enable bit
    uint16_t FSIRX_B:1;                 // 17 FSIRX_B Clock Enable bit
    uint16_t FSIRX_C:1;                 // 18 FSIRX_C Clock Enable bit
    uint16_t FSIRX_D:1;                 // 19 FSIRX_D Clock Enable bit
    uint16_t rsvd2:12;                  // 31:20 Reserved
};

union SYSCTL_PCLKCR18_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR18_BITS  bit;
};

struct SYSCTL_PCLKCR19_BITS {           // bits description
    uint16_t LIN_A:1;                   // 0 LIN_A Clock Enable bit
    uint16_t LIN_B:1;                   // 1 LIN_B Clock Enable bit
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:12;                  // 15:4 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR19_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR19_BITS  bit;
};

struct SYSCTL_PCLKCR20_BITS {           // bits description
    uint16_t PMBUS_A:1;                 // 0 PMBUS_A Clock Enable bit
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR20_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR20_BITS  bit;
};

struct SYSCTL_PCLKCR21_BITS {           // bits description
    uint16_t DCC1:1;                    // 0 DCC1 Clock Enable Bit
    uint16_t DCC2:1;                    // 1 DCC2 Clock Enable Bit
    uint16_t DCC3:1;                    // 2 DCC3 Clock Enable Bit
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR21_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR21_BITS  bit;
};

struct SYSCTL_PCLKCR23_BITS {           // bits description
    uint16_t ETHERCAT:1;                // 0 ETHERCAT Clock Enable Bit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR23_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR23_BITS  bit;
};

struct SYSCTL_PCLKCR25_BITS {           // bits description
    uint16_t HRCAL0:1;                  // 0 HRCAL0 Clock Enable Bit
    uint16_t HRCAL1:1;                  // 1 HRCAL1 Clock Enable Bit
    uint16_t HRCAL2:1;                  // 2 HRCAL2 Clock Enable Bit
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR25_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR25_BITS  bit;
};

struct SYSCTL_PCLKCR27_BITS {           // bits description
    uint16_t EPG1:1;                    // 0 EPG1 Clock Enable Bit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR27_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR27_BITS  bit;
};

struct SYSCTL_PCLKCR28_BITS {           // bits description
    uint16_t ADCCHECKER1:1;             // 0 ADCCHECKER1 Clock Enable bit
    uint16_t ADCCHECKER2:1;             // 1 ADCCHECKER2 Clock Enable bit
    uint16_t ADCCHECKER3:1;             // 2 ADCCHECKER3 Clock Enable bit
    uint16_t ADCCHECKER4:1;             // 3 ADCCHECKER4 Clock Enable bit
    uint16_t ADCCHECKER5:1;             // 4 ADCCHECKER5 Clock Enable bit
    uint16_t ADCCHECKER6:1;             // 5 ADCCHECKER6 Clock Enable bit
    uint16_t ADCCHECKER7:1;             // 6 ADCCHECKER7 Clock Enable bit
    uint16_t ADCCHECKER8:1;             // 7 ADCCHECKER8 Clock Enable bit
    uint16_t ADCCHECKER9:1;             // 8 ADCCHECKER9 Clock Enable bit
    uint16_t ADCCHECKER10:1;            // 9 ADCCHECKER10 Clock Enable bit
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t ADCSEAGGRCPU1:1;           // 16 ADCSEAGGRCPU1 Clock Enable bit
    uint16_t ADCSEAGGRCPU2:1;           // 17 ADCSEAGGRCPU2 Clock Enable bit
    uint16_t ADCSEAGGRCPU3:1;           // 18 ADCSEAGGRCPU3 Clock Enable bit
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t rsvd4:1;                   // 21 Reserved
    uint16_t rsvd5:10;                  // 31:22 Reserved
};

union SYSCTL_PCLKCR28_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR28_BITS  bit;
};

struct SYSCTL_PCLKCR30_BITS {           // bits description
    uint16_t SENT1:1;                   // 0 SENT1 Clock Enable bit
    uint16_t SENT2:1;                   // 1 SENT2 Clock Enable bit
    uint16_t SENT3:1;                   // 2 SENT3 Clock Enable bit
    uint16_t SENT4:1;                   // 3 SENT4 Clock Enable bit
    uint16_t SENT5:1;                   // 4 SENT5 Clock Enable bit
    uint16_t SENT6:1;                   // 5 SENT6 Clock Enable bit
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR30_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR30_BITS  bit;
};

struct SYSCTL_PCLKCR32_BITS {           // bits description
    uint16_t WADI1:1;                   // 0 WADI1 Clock Enable bit
    uint16_t WADI2:1;                   // 1 WADI2 Clock Enable bit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PCLKCR32_REG {
    uint32_t  all;
    struct  SYSCTL_PCLKCR32_BITS  bit;
};

struct SYSCTL_SOFTPRES0_BITS {          // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t CPUTIMER:1;                // 4 Reset bit for modules CPUTIMER0, COUTIMER1 and CPUTIMER2
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:9;                   // 15:7 Reserved
    uint16_t rsvd5:8;                   // 23:16 Reserved
    uint16_t CPUx_ERAD:1;               // 24 CPUx_ERAD Module reset bit
    uint16_t CPUx_DLT:1;                // 25 CPUx_DLT Module reset bit
    uint16_t rsvd6:6;                   // 31:26 Reserved
};

union SYSCTL_SOFTPRES0_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES0_BITS  bit;
};

struct SYSCTL_SOFTPRES1_BITS {          // bits description
    uint16_t EMIF1:1;                   // 0 EMIF1 software reset bit
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES1_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES1_BITS  bit;
};

struct SYSCTL_SOFTPRES2_BITS {          // bits description
    uint16_t EPWM1:1;                   // 0 EPWM1 software reset bit
    uint16_t EPWM2:1;                   // 1 EPWM2 software reset bit
    uint16_t EPWM3:1;                   // 2 EPWM3 software reset bit
    uint16_t EPWM4:1;                   // 3 EPWM4 software reset bit
    uint16_t EPWM5:1;                   // 4 EPWM5 software reset bit
    uint16_t EPWM6:1;                   // 5 EPWM6 software reset bit
    uint16_t EPWM7:1;                   // 6 EPWM7 software reset bit
    uint16_t EPWM8:1;                   // 7 EPWM8 software reset bit
    uint16_t EPWM9:1;                   // 8 EPWM9 software reset bit
    uint16_t EPWM10:1;                  // 9 EPWM10 software reset bit
    uint16_t EPWM11:1;                  // 10 EPWM11 software reset bit
    uint16_t EPWM12:1;                  // 11 EPWM12 software reset bit
    uint16_t EPWM13:1;                  // 12 EPWM13 software reset bit
    uint16_t EPWM14:1;                  // 13 EPWM14 software reset bit
    uint16_t EPWM15:1;                  // 14 EPWM15 software reset bit
    uint16_t EPWM16:1;                  // 15 EPWM16 software reset bit
    uint16_t EPWM17:1;                  // 16 EPWM17 software reset bit
    uint16_t EPWM18:1;                  // 17 EPWM18 software reset bit
    uint16_t rsvd1:14;                  // 31:18 Reserved
};

union SYSCTL_SOFTPRES2_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES2_BITS  bit;
};

struct SYSCTL_SOFTPRES3_BITS {          // bits description
    uint16_t ECAP1:1;                   // 0 ECAP1 software reset bit
    uint16_t ECAP2:1;                   // 1 ECAP2 software reset bit
    uint16_t ECAP3:1;                   // 2 ECAP3 software reset bit
    uint16_t ECAP4:1;                   // 3 ECAP4 software reset bit
    uint16_t ECAP5:1;                   // 4 ECAP5 software reset bit
    uint16_t ECAP6:1;                   // 5 ECAP6 software reset bit
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t rsvd3:8;                   // 15:8 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES3_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES3_BITS  bit;
};

struct SYSCTL_SOFTPRES4_BITS {          // bits description
    uint16_t EQEP1:1;                   // 0 EQEP1 software reset bit
    uint16_t EQEP2:1;                   // 1 EQEP2 software reset bit
    uint16_t EQEP3:1;                   // 2 EQEP3 software reset bit
    uint16_t EQEP4:1;                   // 3 EQEP4 software reset bit
    uint16_t EQEP5:1;                   // 4 EQEP5 software reset bit
    uint16_t EQEP6:1;                   // 5 EQEP6 software reset bit
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES4_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES4_BITS  bit;
};

struct SYSCTL_SOFTPRES6_BITS {          // bits description
    uint16_t SD1:1;                     // 0 SD1 software reset bit
    uint16_t SD2:1;                     // 1 SD2 software reset bit
    uint16_t SD3:1;                     // 2 SD3 software reset bit
    uint16_t SD4:1;                     // 3 SD4 software reset bit
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:8;                   // 15:8 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES6_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES6_BITS  bit;
};

struct SYSCTL_SOFTPRES7_BITS {          // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:12;                  // 15:4 Reserved
    uint16_t UART_A:1;                  // 16 UART_A software reset bit
    uint16_t UART_B:1;                  // 17 UART_B software reset bit
    uint16_t UART_C:1;                  // 18 UART_C software reset bit
    uint16_t UART_D:1;                  // 19 UART_D software reset bit
    uint16_t UART_E:1;                  // 20 UART_E software reset bit
    uint16_t UART_F:1;                  // 21 UART_F software reset bit
    uint16_t rsvd6:10;                  // 31:22 Reserved
};

union SYSCTL_SOFTPRES7_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES7_BITS  bit;
};

struct SYSCTL_SOFTPRES8_BITS {          // bits description
    uint16_t SPI_A:1;                   // 0 SPI_A software reset bit
    uint16_t SPI_B:1;                   // 1 SPI_B software reset bit
    uint16_t SPI_C:1;                   // 2 SPI_C software reset bit
    uint16_t SPI_D:1;                   // 3 SPI_D software reset bit
    uint16_t SPI_E:1;                   // 4 SPI_E software reset bit
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:1;                   // 16 Reserved
    uint16_t rsvd3:1;                   // 17 Reserved
    uint16_t rsvd4:14;                  // 31:18 Reserved
};

union SYSCTL_SOFTPRES8_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES8_BITS  bit;
};

struct SYSCTL_SOFTPRES9_BITS {          // bits description
    uint16_t I2C_A:1;                   // 0 I2C_A software reset bit
    uint16_t I2C_B:1;                   // 1 I2C_B software reset bit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES9_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES9_BITS  bit;
};

struct SYSCTL_SOFTPRES10_BITS {         // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t MCAN_A:1;                  // 4 MCAN_A software reset bit
    uint16_t MCAN_B:1;                  // 5 MCAN_B software reset bit
    uint16_t MCAN_C:1;                  // 6 MCAN_C software reset bit
    uint16_t MCAN_D:1;                  // 7 MCAN_D software reset bit
    uint16_t MCAN_E:1;                  // 8 MCAN_E software reset bit
    uint16_t MCAN_F:1;                  // 9 MCAN_F software reset bit
    uint16_t rsvd5:6;                   // 15:10 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES10_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES10_BITS  bit;
};

struct SYSCTL_SOFTPRES13_BITS {         // bits description
    uint16_t ADC_A:1;                   // 0 ADC_A software reset bit
    uint16_t ADC_B:1;                   // 1 ADC_B software reset bit
    uint16_t ADC_C:1;                   // 2 ADC_C software reset bit
    uint16_t ADC_D:1;                   // 3 ADC_D software reset bit
    uint16_t ADC_E:1;                   // 4 ADC_E software reset bit
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t rsvd2:10;                  // 15:6 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES13_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES13_BITS  bit;
};

struct SYSCTL_SOFTPRES14_BITS {         // bits description
    uint16_t CMPSS1:1;                  // 0 CMPSS1 software reset bit
    uint16_t CMPSS2:1;                  // 1 CMPSS2 software reset bit
    uint16_t CMPSS3:1;                  // 2 CMPSS3 software reset bit
    uint16_t CMPSS4:1;                  // 3 CMPSS4 software reset bit
    uint16_t CMPSS5:1;                  // 4 CMPSS5 software reset bit
    uint16_t CMPSS6:1;                  // 5 CMPSS6 software reset bit
    uint16_t CMPSS7:1;                  // 6 CMPSS7 software reset bit
    uint16_t CMPSS8:1;                  // 7 CMPSS8 software reset bit
    uint16_t CMPSS9:1;                  // 8 CMPSS9 software reset bit
    uint16_t CMPSS10:1;                 // 9 CMPSS10 software reset bit
    uint16_t CMPSS11:1;                 // 10 CMPSS11 software reset bit
    uint16_t CMPSS12:1;                 // 11 CMPSS12 software reset bit
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES14_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES14_BITS  bit;
};

struct SYSCTL_SOFTPRES16_BITS {         // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:12;                  // 15:4 Reserved
    uint16_t DAC_A:1;                   // 16 DAC_A software reset bit
    uint16_t DAC_B:1;                   // 17 DAC_B software reset bit
    uint16_t rsvd6:1;                   // 18 Reserved
    uint16_t rsvd7:1;                   // 19 Reserved
    uint16_t rsvd8:12;                  // 31:20 Reserved
};

union SYSCTL_SOFTPRES16_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES16_BITS  bit;
};

struct SYSCTL_SOFTPRES17_BITS {         // bits description
    uint16_t CLB1:1;                    // 0 CLB1 software reset bit
    uint16_t CLB2:1;                    // 1 CLB2 software reset bit
    uint16_t CLB3:1;                    // 2 CLB3 software reset bit
    uint16_t CLB4:1;                    // 3 CLB4 software reset bit
    uint16_t CLB5:1;                    // 4 CLB5 software reset bit
    uint16_t CLB6:1;                    // 5 CLB6 software reset bit
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES17_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES17_BITS  bit;
};

struct SYSCTL_SOFTPRES18_BITS {         // bits description
    uint16_t FSITX_A:1;                 // 0 FSITX_A software reset bit
    uint16_t FSITX_B:1;                 // 1 FSITX_B software reset bit
    uint16_t FSITX_C:1;                 // 2 FSITX_C software reset bit
    uint16_t FSITX_D:1;                 // 3 FSITX_D software reset bit
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t FSIRX_A:1;                 // 16 FSIRX_A software reset bit
    uint16_t FSIRX_B:1;                 // 17 FSIRX_B software reset bit
    uint16_t FSIRX_C:1;                 // 18 FSIRX_C software reset bit
    uint16_t FSIRX_D:1;                 // 19 FSIRX_D software reset bit
    uint16_t rsvd2:12;                  // 31:20 Reserved
};

union SYSCTL_SOFTPRES18_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES18_BITS  bit;
};

struct SYSCTL_SOFTPRES19_BITS {         // bits description
    uint16_t LIN_A:1;                   // 0 LIN_A software reset bit
    uint16_t LIN_B:1;                   // 1 LIN_B software reset bit
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:12;                  // 15:4 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES19_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES19_BITS  bit;
};

struct SYSCTL_SOFTPRES20_BITS {         // bits description
    uint16_t PMBUS_A:1;                 // 0 PMBUS_A software reset bit
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES20_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES20_BITS  bit;
};

struct SYSCTL_SOFTPRES21_BITS {         // bits description
    uint16_t DCC1:1;                    // 0 DCC Module reset bit
    uint16_t DCC2:1;                    // 1 DCC Module reset bit
    uint16_t DCC3:1;                    // 2 DCC Module reset bit
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES21_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES21_BITS  bit;
};

struct SYSCTL_SOFTPRES23_BITS {         // bits description
    uint16_t ETHERCAT:1;                // 0 ETHERCAT Module reset bit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES23_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES23_BITS  bit;
};

struct SYSCTL_SOFTPRES25_BITS {         // bits description
    uint16_t HRCAL0:1;                  // 0 HRCAL0 Module reset bit
    uint16_t HRCAL1:1;                  // 1 HRCAL1 Module reset bit
    uint16_t HRCAL2:1;                  // 2 HRCAL2 Module reset bit
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES25_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES25_BITS  bit;
};

struct SYSCTL_SOFTPRES27_BITS {         // bits description
    uint16_t EPG1:1;                    // 0 EPG Module Reset Bit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES27_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES27_BITS  bit;
};

struct SYSCTL_SOFTPRES28_BITS {         // bits description
    uint16_t ADCCHECKER1:1;             // 0 ADCCHECKER1 software reset bit
    uint16_t ADCCHECKER2:1;             // 1 ADCCHECKER2 software reset bit
    uint16_t ADCCHECKER3:1;             // 2 ADCCHECKER3 software reset bit
    uint16_t ADCCHECKER4:1;             // 3 ADCCHECKER4 software reset bit
    uint16_t ADCCHECKER5:1;             // 4 ADCCHECKER5 software reset bit
    uint16_t ADCCHECKER6:1;             // 5 ADCCHECKER6 software reset bit
    uint16_t ADCCHECKER7:1;             // 6 ADCCHECKER7 software reset bit
    uint16_t ADCCHECKER8:1;             // 7 ADCCHECKER8 software reset bit
    uint16_t ADCCHECKER9:1;             // 8 ADCCHECKER9 software reset bit
    uint16_t ADCCHECKER10:1;            // 9 ADCCHECKER10 software reset bit
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t ADCSEAGGRCPU1:1;           // 16 ADCSEAGGRCPU1 software reset bit
    uint16_t ADCSEAGGRCPU2:1;           // 17 ADCSEAGGRCPU2 software reset bit
    uint16_t ADCSEAGGRCPU3:1;           // 18 ADCSEAGGRCPU3 software reset bit
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t rsvd4:1;                   // 21 Reserved
    uint16_t rsvd5:10;                  // 31:22 Reserved
};

union SYSCTL_SOFTPRES28_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES28_BITS  bit;
};

struct SYSCTL_SOFTPRES30_BITS {         // bits description
    uint16_t SENT1:1;                   // 0 SENT1 software reset bit
    uint16_t SENT2:1;                   // 1 SENT2 software reset bit
    uint16_t SENT3:1;                   // 2 SENT3 software reset bit
    uint16_t SENT4:1;                   // 3 SENT4 software reset bit
    uint16_t SENT5:1;                   // 4 SENT5 software reset bit
    uint16_t SENT6:1;                   // 5 SENT6 software reset bit
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES30_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES30_BITS  bit;
};

struct SYSCTL_SOFTPRES32_BITS {         // bits description
    uint16_t WADI1:1;                   // 0 WADI1 software reset bit
    uint16_t WADI2:1;                   // 1 WADI2 software reset bit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_SOFTPRES32_REG {
    uint32_t  all;
    struct  SYSCTL_SOFTPRES32_BITS  bit;
};

struct SYSCTL_PARITY_TEST_ALT1_BITS {   // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity test enable configuration
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PARITY_TEST_ALT1_REG {
    uint32_t  all;
    struct  SYSCTL_PARITY_TEST_ALT1_BITS  bit;
};

struct CPU_PER_CFG_REGS {
    union   SYSCTL_CPUPERCFGLOCK1_REG        CPUPERCFGLOCK1;               // Lock bit for CPUx_PER_CFG registers
    union   SYSCTL_CPUPERCFGLOCK2_REG        CPUPERCFGLOCK2;               // Lock bit for CPUx_PER_CFG registers
    uint8_t                                  rsvd1[8];                     // Reserved
    union   SYSCTL_PCLKCR0_REG               PCLKCR0;                      // Peripheral Clock Gating Registers
    union   SYSCTL_PCLKCR1_REG               PCLKCR1;                      // Peripheral Clock Gating Register - EMIF
    union   SYSCTL_PCLKCR2_REG               PCLKCR2;                      // Peripheral Clock Gating Register - EPWM
    union   SYSCTL_PCLKCR3_REG               PCLKCR3;                      // Peripheral Clock Gating Register - ECAP
    union   SYSCTL_PCLKCR4_REG               PCLKCR4;                      // Peripheral Clock Gating Register - EQEP
    uint8_t                                  rsvd2[4];                     // Reserved
    union   SYSCTL_PCLKCR6_REG               PCLKCR6;                      // Peripheral Clock Gating Register - SDFM
    union   SYSCTL_PCLKCR7_REG               PCLKCR7;                      // Peripheral Clock Gating Register - SCI, UART
    union   SYSCTL_PCLKCR8_REG               PCLKCR8;                      // Peripheral Clock Gating Register - SPI
    union   SYSCTL_PCLKCR9_REG               PCLKCR9;                      // Peripheral Clock Gating Register - I2C
    union   SYSCTL_PCLKCR10_REG              PCLKCR10;                     // Peripheral Clock Gating Register - CAN
    uint8_t                                  rsvd3[8];                     // Reserved
    union   SYSCTL_PCLKCR13_REG              PCLKCR13;                     // Peripheral Clock Gating Register - ADC
    union   SYSCTL_PCLKCR14_REG              PCLKCR14;                     // Peripheral Clock Gating Register - CMPSS
    uint8_t                                  rsvd4[4];                     // Reserved
    union   SYSCTL_PCLKCR16_REG              PCLKCR16;                     // Peripheral Clock Gating Register Buf_DAC
    union   SYSCTL_PCLKCR17_REG              PCLKCR17;                     // Peripheral Clock Gating Register - CLB
    union   SYSCTL_PCLKCR18_REG              PCLKCR18;                     // Peripheral Clock Gating Register - FSI
    union   SYSCTL_PCLKCR19_REG              PCLKCR19;                     // Peripheral Clock Gating Register - LIN
    union   SYSCTL_PCLKCR20_REG              PCLKCR20;                     // Peripheral Clock Gating Register - PMBUS
    union   SYSCTL_PCLKCR21_REG              PCLKCR21;                     // Peripheral Clock Gating Register - DCC
    uint8_t                                  rsvd5[4];                     // Reserved
    union   SYSCTL_PCLKCR23_REG              PCLKCR23;                     // Peripheral Clock Gating Register - EtherCAT
    uint8_t                                  rsvd6[4];                     // Reserved
    union   SYSCTL_PCLKCR25_REG              PCLKCR25;                     // Peripheral Clock Gating Register - HRCAL0,1,2
    uint8_t                                  rsvd7[4];                     // Reserved
    union   SYSCTL_PCLKCR27_REG              PCLKCR27;                     // Peripheral Clock Gating Register - EPG
    union   SYSCTL_PCLKCR28_REG              PCLKCR28;                     // Peripheral Clock Gating Register - ADCCHECKER
    uint8_t                                  rsvd8[4];                     // Reserved
    union   SYSCTL_PCLKCR30_REG              PCLKCR30;                     // Peripheral Clock Gating Register - SENT
    uint8_t                                  rsvd9[4];                     // Reserved
    union   SYSCTL_PCLKCR32_REG              PCLKCR32;                     // Peripheral Clock Gating Register - WADI
    uint8_t                                  rsvd10[124];                  // Reserved
    union   SYSCTL_SOFTPRES0_REG             SOFTPRES0;                    // Processing Block Software Reset register
    union   SYSCTL_SOFTPRES1_REG             SOFTPRES1;                    // EMIF Software Reset register
    union   SYSCTL_SOFTPRES2_REG             SOFTPRES2;                    // EPWM Software Reset register
    union   SYSCTL_SOFTPRES3_REG             SOFTPRES3;                    // ECAP Software Reset register
    union   SYSCTL_SOFTPRES4_REG             SOFTPRES4;                    // EQEP Software Reset register
    uint8_t                                  rsvd11[4];                    // Reserved
    union   SYSCTL_SOFTPRES6_REG             SOFTPRES6;                    // Sigma Delta Software Reset register
    union   SYSCTL_SOFTPRES7_REG             SOFTPRES7;                    // SCI, UART Software Reset register
    union   SYSCTL_SOFTPRES8_REG             SOFTPRES8;                    // SPI Software Reset register
    union   SYSCTL_SOFTPRES9_REG             SOFTPRES9;                    // I2C Software Reset register
    union   SYSCTL_SOFTPRES10_REG            SOFTPRES10;                   // CAN Software Reset register
    uint8_t                                  rsvd12[8];                    // Reserved
    union   SYSCTL_SOFTPRES13_REG            SOFTPRES13;                   // ADC Software Reset register
    union   SYSCTL_SOFTPRES14_REG            SOFTPRES14;                   // CMPSS Software Reset register
    uint8_t                                  rsvd13[4];                    // Reserved
    union   SYSCTL_SOFTPRES16_REG            SOFTPRES16;                   // DAC Software Reset register
    union   SYSCTL_SOFTPRES17_REG            SOFTPRES17;                   // CLB Software Reset register
    union   SYSCTL_SOFTPRES18_REG            SOFTPRES18;                   // FSI Software Reset register
    union   SYSCTL_SOFTPRES19_REG            SOFTPRES19;                   // LIN Software Reset register
    union   SYSCTL_SOFTPRES20_REG            SOFTPRES20;                   // PMBUS Software Reset register
    union   SYSCTL_SOFTPRES21_REG            SOFTPRES21;                   // DCC Software Reset register
    uint8_t                                  rsvd14[4];                    // Reserved
    union   SYSCTL_SOFTPRES23_REG            SOFTPRES23;                   // ETHERCAT Software Reset register
    uint8_t                                  rsvd15[4];                    // Reserved
    union   SYSCTL_SOFTPRES25_REG            SOFTPRES25;                   // HRCAL0,1,2 Software Reset register
    uint8_t                                  rsvd16[4];                    // Reserved
    union   SYSCTL_SOFTPRES27_REG            SOFTPRES27;                   // EPG Software Reset register
    union   SYSCTL_SOFTPRES28_REG            SOFTPRES28;                   // ADCCHECKER Software Reset register
    uint8_t                                  rsvd17[4];                    // Reserved
    union   SYSCTL_SOFTPRES30_REG            SOFTPRES30;                   // SENT Software Reset register
    uint8_t                                  rsvd18[4];                    // Reserved
    union   SYSCTL_SOFTPRES32_REG            SOFTPRES32;                   // WADI Software Reset register
    uint8_t                                  rsvd19[36];                   // Reserved
    union   SYSCTL_PARITY_TEST_ALT1_REG      PARITY_TEST_ALT1;             // Enables parity test
};

struct SYSCTL_CPUSYSLOCK1_BITS {        // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t LPMCR:1;                   // 1 Lock bit for LPMCR Register
    uint16_t GPIOLPMSEL0:1;             // 2 Lock bit for GPIOLPMSEL0 Register
    uint16_t GPIOLPMSEL1:1;             // 3 Lock bit for GPIOLPMSEL1 Register
    uint16_t rsvd2:1;                   // 4 Reserved
    uint16_t CMPSSLPMSEL:1;             // 5 Lock bit for CMPSSLPMSEL register
    uint16_t rsvd3:10;                  // 15:6 Reserved
    uint16_t rsvd4:8;                   // 23:16 Reserved
    uint16_t USER_REG1_SYSRSn:1;        // 24 Lock bit for USER_REG1_SYSRSn
    uint16_t USER_REG2_SYSRSn:1;        // 25 Lock bit for USER_REG2_SYSRSn
    uint16_t USER_REG1_XRSn:1;          // 26 Lock bit for USER_REG1_XRSn
    uint16_t USER_REG2_XRSn:1;          // 27 Lock bit for USER_REG2_XRSn
    uint16_t USER_REG1_PORESETn:1;      // 28 Lock bit for USER_REG1_PORESETn
    uint16_t USER_REG2_PORESETn:1;      // 29 Lock bit for USER_REG2_PORESETn
    uint16_t USER_REG3_PORESETn:1;      // 30 Lock bit for USER_REG3_PORESETn
    uint16_t USER_REG4_PORESETn:1;      // 31 Lock bit for USER_REG4_PORESETn
};

union SYSCTL_CPUSYSLOCK1_REG {
    uint32_t  all;
    struct  SYSCTL_CPUSYSLOCK1_BITS  bit;
};

struct SYSCTL_CPUID_BITS {              // bits description
    uint16_t CPUID:2;                   // 1:0 Indicates CPU1, CPU2, CPU3, CPU4, CPU5 or CPU6
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_CPUID_REG {
    uint32_t  all;
    struct  SYSCTL_CPUID_BITS  bit;
};

struct SYSCTL_LPMCR_BITS {              // bits description
    uint16_t LPM:2;                     // 1:0 Low Power Mode setting
    uint16_t QUALSTDBY:6;               // 7:2 STANDBY Wakeup Pin Qualification Setting
    uint16_t rsvd1:7;                   // 14:8 Reserved
    uint16_t WDINTE:1;                  // 15 Enable for WDINT wakeup from STANDBY
    uint16_t rsvd2:2;                   // 17:16 Reserved
    uint16_t rsvd3:13;                  // 30:18 Reserved
    uint16_t rsvd4:1;                   // 31 Reserved
};

union SYSCTL_LPMCR_REG {
    uint32_t  all;
    struct  SYSCTL_LPMCR_BITS  bit;
};

struct SYSCTL_CMPSSLPMSEL_BITS {        // bits description
    uint16_t CMPSS1H:1;                 // 0 CMPSS1H Enable for LPM Wakeup
    uint16_t CMPSS1L:1;                 // 1 CMPSS1L Enable for LPM Wakeup
    uint16_t CMPSS2H:1;                 // 2 CMPSS2H Enable for LPM Wakeup
    uint16_t CMPSS2L:1;                 // 3 CMPSS2L Enable for LPM Wakeup
    uint16_t CMPSS3H:1;                 // 4 CMPSS3H Enable for LPM Wakeup
    uint16_t CMPSS3L:1;                 // 5 CMPSS3L Enable for LPM Wakeup
    uint16_t CMPSS4H:1;                 // 6 CMPSS4H Enable for LPM Wakeup
    uint16_t CMPSS4L:1;                 // 7 CMPSS4L Enable for LPM Wakeup
    uint16_t CMPSS5H:1;                 // 8 CMPSS5H Enable for LPM Wakeup
    uint16_t CMPSS5L:1;                 // 9 CMPSS5L Enable for LPM Wakeup
    uint16_t CMPSS6H:1;                 // 10 CMPSS6H Enable for LPM Wakeup
    uint16_t CMPSS6L:1;                 // 11 CMPSS6L Enable for LPM Wakeup
    uint16_t CMPSS7H:1;                 // 12 CMPSS7H Enable for LPM Wakeup
    uint16_t CMPSS7L:1;                 // 13 CMPSS7L Enable for LPM Wakeup
    uint16_t CMPSS8H:1;                 // 14 CMPSS8H Enable for LPM Wakeup
    uint16_t CMPSS8L:1;                 // 15 CMPSS8L Enable for LPM Wakeup
    uint16_t CMPSS9H:1;                 // 16 CMPSS9H Enable for LPM Wakeup
    uint16_t CMPSS9L:1;                 // 17 CMPSS9L Enable for LPM Wakeup
    uint16_t CMPSS10H:1;                // 18 CMPSS10H Enable for LPM Wakeup
    uint16_t CMPSS10L:1;                // 19 CMPSS10L Enable for LPM Wakeup
    uint16_t CMPSS11H:1;                // 20 CMPSS11H Enable for LPM Wakeup
    uint16_t CMPSS11L:1;                // 21 CMPSS11L Enable for LPM Wakeup
    uint16_t CMPSS12H:1;                // 22 CMPSS12H Enable for LPM Wakeup
    uint16_t CMPSS12L:1;                // 23 CMPSS12L Enable for LPM Wakeup
    uint16_t rsvd1:1;                   // 24 Reserved
    uint16_t rsvd2:1;                   // 25 Reserved
    uint16_t rsvd3:1;                   // 26 Reserved
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t rsvd5:1;                   // 28 Reserved
    uint16_t rsvd6:1;                   // 29 Reserved
    uint16_t rsvd7:1;                   // 30 Reserved
    uint16_t rsvd8:1;                   // 31 Reserved
};

union SYSCTL_CMPSSLPMSEL_REG {
    uint32_t  all;
    struct  SYSCTL_CMPSSLPMSEL_BITS  bit;
};

struct SYSCTL_GPIOLPMSEL0_BITS {        // bits description
    uint16_t GPIO0:1;                   // 0 GPIO0 Enable for LPM Wakeup
    uint16_t GPIO1:1;                   // 1 GPIO1 Enable for LPM Wakeup
    uint16_t GPIO2:1;                   // 2 GPIO2 Enable for LPM Wakeup
    uint16_t GPIO3:1;                   // 3 GPIO3 Enable for LPM Wakeup
    uint16_t GPIO4:1;                   // 4 GPIO4 Enable for LPM Wakeup
    uint16_t GPIO5:1;                   // 5 GPIO5 Enable for LPM Wakeup
    uint16_t GPIO6:1;                   // 6 GPIO6 Enable for LPM Wakeup
    uint16_t GPIO7:1;                   // 7 GPIO7 Enable for LPM Wakeup
    uint16_t GPIO8:1;                   // 8 GPIO8 Enable for LPM Wakeup
    uint16_t GPIO9:1;                   // 9 GPIO9 Enable for LPM Wakeup
    uint16_t GPIO10:1;                  // 10 GPIO10 Enable for LPM Wakeup
    uint16_t GPIO11:1;                  // 11 GPIO11 Enable for LPM Wakeup
    uint16_t GPIO12:1;                  // 12 GPIO12 Enable for LPM Wakeup
    uint16_t GPIO13:1;                  // 13 GPIO13 Enable for LPM Wakeup
    uint16_t GPIO14:1;                  // 14 GPIO14 Enable for LPM Wakeup
    uint16_t GPIO15:1;                  // 15 GPIO15 Enable for LPM Wakeup
    uint16_t GPIO16:1;                  // 16 GPIO16 Enable for LPM Wakeup
    uint16_t GPIO17:1;                  // 17 GPIO17 Enable for LPM Wakeup
    uint16_t GPIO18:1;                  // 18 GPIO18 Enable for LPM Wakeup
    uint16_t GPIO19:1;                  // 19 GPIO19 Enable for LPM Wakeup
    uint16_t GPIO20:1;                  // 20 GPIO20 Enable for LPM Wakeup
    uint16_t GPIO21:1;                  // 21 GPIO21 Enable for LPM Wakeup
    uint16_t GPIO22:1;                  // 22 GPIO22 Enable for LPM Wakeup
    uint16_t GPIO23:1;                  // 23 GPIO23 Enable for LPM Wakeup
    uint16_t GPIO24:1;                  // 24 GPIO24 Enable for LPM Wakeup
    uint16_t GPIO25:1;                  // 25 GPIO25 Enable for LPM Wakeup
    uint16_t GPIO26:1;                  // 26 GPIO26 Enable for LPM Wakeup
    uint16_t GPIO27:1;                  // 27 GPIO27 Enable for LPM Wakeup
    uint16_t GPIO28:1;                  // 28 GPIO28 Enable for LPM Wakeup
    uint16_t GPIO29:1;                  // 29 GPIO29 Enable for LPM Wakeup
    uint16_t GPIO30:1;                  // 30 GPIO30 Enable for LPM Wakeup
    uint16_t GPIO31:1;                  // 31 GPIO31 Enable for LPM Wakeup
};

union SYSCTL_GPIOLPMSEL0_REG {
    uint32_t  all;
    struct  SYSCTL_GPIOLPMSEL0_BITS  bit;
};

struct SYSCTL_GPIOLPMSEL1_BITS {        // bits description
    uint16_t GPIO32:1;                  // 0 GPIO32 Enable for LPM Wakeup
    uint16_t GPIO33:1;                  // 1 GPIO33 Enable for LPM Wakeup
    uint16_t GPIO34:1;                  // 2 GPIO34 Enable for LPM Wakeup
    uint16_t GPIO35:1;                  // 3 GPIO35 Enable for LPM Wakeup
    uint16_t GPIO36:1;                  // 4 GPIO36 Enable for LPM Wakeup
    uint16_t GPIO37:1;                  // 5 GPIO37 Enable for LPM Wakeup
    uint16_t GPIO38:1;                  // 6 GPIO38 Enable for LPM Wakeup
    uint16_t GPIO39:1;                  // 7 GPIO39 Enable for LPM Wakeup
    uint16_t GPIO40:1;                  // 8 GPIO40 Enable for LPM Wakeup
    uint16_t GPIO41:1;                  // 9 GPIO41 Enable for LPM Wakeup
    uint16_t GPIO42:1;                  // 10 GPIO42 Enable for LPM Wakeup
    uint16_t GPIO43:1;                  // 11 GPIO43 Enable for LPM Wakeup
    uint16_t GPIO44:1;                  // 12 GPIO44 Enable for LPM Wakeup
    uint16_t GPIO45:1;                  // 13 GPIO45 Enable for LPM Wakeup
    uint16_t GPIO46:1;                  // 14 GPIO46 Enable for LPM Wakeup
    uint16_t GPIO47:1;                  // 15 GPIO47 Enable for LPM Wakeup
    uint16_t GPIO48:1;                  // 16 GPIO48 Enable for LPM Wakeup
    uint16_t GPIO49:1;                  // 17 GPIO49 Enable for LPM Wakeup
    uint16_t GPIO50:1;                  // 18 GPIO50 Enable for LPM Wakeup
    uint16_t GPIO51:1;                  // 19 GPIO51 Enable for LPM Wakeup
    uint16_t GPIO52:1;                  // 20 GPIO52 Enable for LPM Wakeup
    uint16_t GPIO53:1;                  // 21 GPIO53 Enable for LPM Wakeup
    uint16_t GPIO54:1;                  // 22 GPIO54 Enable for LPM Wakeup
    uint16_t GPIO55:1;                  // 23 GPIO55 Enable for LPM Wakeup
    uint16_t GPIO56:1;                  // 24 GPIO56 Enable for LPM Wakeup
    uint16_t GPIO57:1;                  // 25 GPIO57 Enable for LPM Wakeup
    uint16_t GPIO58:1;                  // 26 GPIO58 Enable for LPM Wakeup
    uint16_t GPIO59:1;                  // 27 GPIO59 Enable for LPM Wakeup
    uint16_t GPIO60:1;                  // 28 GPIO60 Enable for LPM Wakeup
    uint16_t GPIO61:1;                  // 29 GPIO61 Enable for LPM Wakeup
    uint16_t GPIO62:1;                  // 30 GPIO62 Enable for LPM Wakeup
    uint16_t GPIO63:1;                  // 31 GPIO63 Enable for LPM Wakeup
};

union SYSCTL_GPIOLPMSEL1_REG {
    uint32_t  all;
    struct  SYSCTL_GPIOLPMSEL1_BITS  bit;
};

struct SYSCTL_TMR2CLKCTL_BITS {         // bits description
    uint16_t TMR2CLKSRCSEL:3;           // 2:0 CPU Timer 2 Clock Source Select Bit
    uint16_t TMR2CLKPRESCALE:3;         // 5:3 CPU Timer 2 Clock Pre-Scale Value
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_TMR2CLKCTL_REG {
    uint32_t  all;
    struct  SYSCTL_TMR2CLKCTL_BITS  bit;
};

struct SYSCTL_RESCCLR_BITS {            // bits description
    uint16_t POR:1;                     // 0 POR POR Reset Cause Clear Bit
    uint16_t XRSn:1;                    // 1 XRSn POR Reset Cause Clear Bit
    uint16_t WDRSn:1;                   // 2 WDRSn POR Reset Cause Clear Bit
    uint16_t NMIWDRSn:1;                // 3 NMIWDRSn POR Reset Cause Clear Bit
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t ECAT_RESET_OUT:1;          // 9 ECAT_RESET_OUT POR Reset Cause Clear Bit
    uint16_t rsvd6:1;                   // 10 Reserved
    uint16_t SIMRESET_XRSn:1;           // 11 SIMRESET_XRSn POR Reset Cause Clear Bit
    uint16_t ESMXRSn:1;                 // 12 ESMXRSn Reset Cause Clear Bit
    uint16_t rsvd7:3;                   // 15:13 Reserved
    uint16_t rsvd8:16;                  // 31:16 Reserved
};

union SYSCTL_RESCCLR_REG {
    uint32_t  all;
    struct  SYSCTL_RESCCLR_BITS  bit;
};

struct SYSCTL_RESC_BITS {               // bits description
    uint16_t POR:1;                     // 0 POR Reset Cause Indication Bit
    uint16_t XRSn:1;                    // 1 XRSn Reset Cause Indication Bit
    uint16_t WDRSn:1;                   // 2 WDRSn Reset Cause Indication Bit
    uint16_t NMIWDRSn:1;                // 3 NMIWDRSn Reset Cause Indication Bit
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t ECAT_RESET_OUT:1;          // 9 ECAT_RESET_OUT Reset Cause Indication Bit
    uint16_t rsvd6:1;                   // 10 Reserved
    uint16_t SIMRESET_XRSn:1;           // 11 SIMRESET_XRSn Reset Cause Indication Bit
    uint16_t ESMRESET:1;                // 12 ESMRESET Reset Cause Indication Bit
    uint16_t rsvd7:3;                   // 15:13 Reserved
    uint16_t rsvd8:14;                  // 29:16 Reserved
    uint16_t XRSn_pin_status:1;         // 30 XRSN Pin Status
    uint16_t DCON:1;                    // 31 Debugger connection status to C29x CPU
};

union SYSCTL_RESC_REG {
    uint32_t  all;
    struct  SYSCTL_RESC_BITS  bit;
};

struct SYSCTL_MCANWAKESTATUS_BITS {     // bits description
    uint16_t WAKE_MCANA:1;              // 0 WAKE_MCANA Wake Status
    uint16_t WAKE_MCANB:1;              // 1 WAKE_MCANB Wake Status
    uint16_t WAKE_MCANC:1;              // 2 WAKE_MCANC Wake Status
    uint16_t WAKE_MCAND:1;              // 3 WAKE_MCAND Wake Status
    uint16_t WAKE_MCANE:1;              // 4 WAKE_MCANE Wake Status
    uint16_t WAKE_MCANF:1;              // 5 WAKE_MCANF Wake Status
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCANWAKESTATUS_REG {
    uint32_t  all;
    struct  SYSCTL_MCANWAKESTATUS_BITS  bit;
};

struct SYSCTL_MCANWAKESTATUSCLR_BITS {  // bits description
    uint16_t WAKE_MCANA:1;              // 0 Cear bit for MCANWAKESTATUS.WAKE_MCANA bit
    uint16_t WAKE_MCANB:1;              // 1 Cear bit for MCANWAKESTATUS.WAKE_MCANB bit
    uint16_t WAKE_MCANC:1;              // 2 Cear bit for MCANWAKESTATUS.WAKE_MCANC bit
    uint16_t WAKE_MCAND:1;              // 3 Cear bit for MCANWAKESTATUS.WAKE_MCAND bit
    uint16_t WAKE_MCANE:1;              // 4 Cear bit for MCANWAKESTATUS.WAKE_MCANE bit
    uint16_t WAKE_MCANF:1;              // 5 Cear bit for MCANWAKESTATUS.WAKE_MCANF bit
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_MCANWAKESTATUSCLR_REG {
    uint32_t  all;
    struct  SYSCTL_MCANWAKESTATUSCLR_BITS  bit;
};

struct SYSCTL_CLKSTOPREQ_BITS {         // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:1;                   // 4 Reserved
    uint16_t rsvd6:1;                   // 5 Reserved
    uint16_t rsvd7:2;                   // 7:6 Reserved
    uint16_t MCAN_A:1;                  // 8 MCAN_A Clock Stop Request Bit
    uint16_t MCAN_B:1;                  // 9 MCAN_B Clock Stop Request Bit
    uint16_t MCAN_C:1;                  // 10 MCAN_C Clock Stop Request Bit
    uint16_t MCAN_D:1;                  // 11 MCAN_D Clock Stop Request Bit
    uint16_t MCAN_E:1;                  // 12 MCAN_E Clock Stop Request Bit
    uint16_t MCAN_F:1;                  // 13 MCAN_F Clock Stop Request Bit
    uint16_t rsvd8:2;                   // 15:14 Reserved
    uint16_t KEY:16;                    // 31:16 Key for register write
};

union SYSCTL_CLKSTOPREQ_REG {
    uint32_t  all;
    struct  SYSCTL_CLKSTOPREQ_BITS  bit;
};

struct SYSCTL_CLKSTOPACK_BITS {         // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:1;                   // 4 Reserved
    uint16_t rsvd6:1;                   // 5 Reserved
    uint16_t rsvd7:2;                   // 7:6 Reserved
    uint16_t MCAN_A:1;                  // 8 MCAN_A Clock Stop Ack Bit
    uint16_t MCAN_B:1;                  // 9 MCAN_B Clock Stop Ack Bit
    uint16_t MCAN_C:1;                  // 10 MCAN_C Clock Stop Ack Bit
    uint16_t MCAN_D:1;                  // 11 MCAN_D Clock Stop Ack Bit
    uint16_t MCAN_E:1;                  // 12 MCAN_E Clock Stop Ack Bit
    uint16_t MCAN_F:1;                  // 13 MCAN_F Clock Stop Ack Bit
    uint16_t rsvd8:2;                   // 15:14 Reserved
    uint16_t rsvd9:16;                  // 31:16 Reserved
};

union SYSCTL_CLKSTOPACK_REG {
    uint32_t  all;
    struct  SYSCTL_CLKSTOPACK_BITS  bit;
};

struct SYSCTL_SIMRESET_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t XRSn:1;                    // 1 Generates a simulated XRSn
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t KEY:16;                    // 31:16 Key value to enable write
};

union SYSCTL_SIMRESET_REG {
    uint32_t  all;
    struct  SYSCTL_SIMRESET_BITS  bit;
};

struct SYSCTL_PARITY_TEST_ALT2_BITS {   // bits description
    uint16_t TESTEN:4;                  // 3:0 Parity test enable configuration
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SYSCTL_PARITY_TEST_ALT2_REG {
    uint32_t  all;
    struct  SYSCTL_PARITY_TEST_ALT2_BITS  bit;
};

struct CPU_SYS_REGS {
    union   SYSCTL_CPUSYSLOCK1_REG           CPUSYSLOCK1;                  // Lock bit for CPUSYS registers
    uint8_t                                  rsvd1[8];                     // Reserved
    union   SYSCTL_CPUID_REG                 CPUID;                        // Indicates CPU1, CPU2.. CPU6
    uint8_t                                  rsvd2[24];                    // Reserved
    union   SYSCTL_LPMCR_REG                 LPMCR;                        // LPM Control Register
    union   SYSCTL_CMPSSLPMSEL_REG           CMPSSLPMSEL;                  // CMPSS LPM Wakeup select registers
    union   SYSCTL_GPIOLPMSEL0_REG           GPIOLPMSEL0;                  // GPIO LPM Wakeup select registers
    union   SYSCTL_GPIOLPMSEL1_REG           GPIOLPMSEL1;                  // GPIO LPM Wakeup select registers
    union   SYSCTL_TMR2CLKCTL_REG            TMR2CLKCTL;                   // Timer2 Clock Measurement functionality control register
    union   SYSCTL_RESCCLR_REG               RESCCLR;                      // Reset Cause Clear Register
    union   SYSCTL_RESC_REG                  RESC;                         // Reset Cause register
    uint8_t                                  rsvd3[44];                    // Reserved
    union   SYSCTL_MCANWAKESTATUS_REG        MCANWAKESTATUS;               // MCAN Wake Status Register
    union   SYSCTL_MCANWAKESTATUSCLR_REG     MCANWAKESTATUSCLR;            // MCAN Wake Status Clear Register
    union   SYSCTL_CLKSTOPREQ_REG            CLKSTOPREQ;                   // Peripheral Clock Stop Request Register
    union   SYSCTL_CLKSTOPACK_REG            CLKSTOPACK;                   // Peripheral Clock Stop Ackonwledge Register
    uint32_t                                 USER_REG1_SYSRSn;             // Software Configurable registers reset by SYSRSn
    uint32_t                                 USER_REG2_SYSRSn;             // Software Configurable registers reset by SYSRSn
    uint32_t                                 USER_REG1_XRSn;               // Software Configurable registers reset by XRSn
    uint32_t                                 USER_REG2_XRSn;               // Software Configurable registers reset by XRSn
    uint32_t                                 USER_REG1_PORESETn;           // Software Configurable registers reset by PORESETn
    uint32_t                                 USER_REG2_PORESETn;           // Software Configurable registers reset by PORESETn
    uint32_t                                 USER_REG3_PORESETn;           // Software Configurable registers reset by PORESETn
    uint32_t                                 USER_REG4_PORESETn;           // Software Configurable registers reset by PORESETn
    uint8_t                                  rsvd4[4];                     // Reserved
    union   SYSCTL_SIMRESET_REG              SIMRESET;                     // Simulated Reset Register
    union   SYSCTL_PARITY_TEST_ALT2_REG      PARITY_TEST_ALT2;             // Enables parity test
};

struct SYSCTL_SCSR_BITS {               // bits description
    uint16_t WDOVERRIDE:1;              // 0 WD Override for WDDIS bit
    uint16_t WDENINT:1;                 // 1 WD Interrupt Enable
    uint16_t WDINTS:1;                  // 2 WD Interrupt Status
    uint16_t rsvd1:13;                  // 15:3 Reserved
};

union SYSCTL_SCSR_REG {
    uint16_t  all;
    struct  SYSCTL_SCSR_BITS  bit;
};

struct SYSCTL_WDCNTR_BITS {             // bits description
    uint16_t WDCNTR:8;                  // 7:0 WD Counter
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union SYSCTL_WDCNTR_REG {
    uint16_t  all;
    struct  SYSCTL_WDCNTR_BITS  bit;
};

struct SYSCTL_WDKEY_BITS {              // bits description
    uint16_t WDKEY:8;                   // 7:0 Key to pet the watchdog timer.
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union SYSCTL_WDKEY_REG {
    uint16_t  all;
    struct  SYSCTL_WDKEY_BITS  bit;
};

struct SYSCTL_SYNCBUSYWD_BITS {         // bits description
    uint16_t BUSY:1;                    // 0 Status bit indicating synchronization in progress
    uint16_t WDCR:1;                    // 1 BUSY status bit for WDCR
    uint16_t rsvd1:14;                  // 15:2 Reserved
};

union SYSCTL_SYNCBUSYWD_REG {
    uint16_t  all;
    struct  SYSCTL_SYNCBUSYWD_BITS  bit;
};

struct SYSCTL_WDCR_BITS {               // bits description
    uint16_t WDPS:3;                    // 2:0 WD Clock Prescalar
    uint16_t WDCHK:3;                   // 5:3 WD Check Bits
    uint16_t WDDIS:1;                   // 6 WD Disable
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t WDPRECLKDIV:4;             // 11:8 WD Pre Clock Divider
    uint16_t rsvd2:4;                   // 15:12 Reserved
};

union SYSCTL_WDCR_REG {
    uint16_t  all;
    struct  SYSCTL_WDCR_BITS  bit;
};

struct SYSCTL_WDWCR_BITS {              // bits description
    uint16_t MIN:8;                     // 7:0 WD Min Threshold setting for Windowed Watchdog functionality
    uint16_t rsvd1:1;                   // 8 Reserved
    uint16_t rsvd2:7;                   // 15:9 Reserved
};

union SYSCTL_WDWCR_REG {
    uint16_t  all;
    struct  SYSCTL_WDWCR_BITS  bit;
};

struct WD_REGS {
    uint8_t                                  rsvd1[68];                    // Reserved
    union   SYSCTL_SCSR_REG                  SCSR;                         // System Control & Status Register
    union   SYSCTL_WDCNTR_REG                WDCNTR;                       // Watchdog Counter Register
    uint8_t                                  rsvd2[2];                     // Reserved
    union   SYSCTL_WDKEY_REG                 WDKEY;                        // Watchdog Reset Key Register
    uint8_t                                  rsvd3[4];                     // Reserved
    union   SYSCTL_SYNCBUSYWD_REG            SYNCBUSYWD;                   // SYNCBUSY status for Watchdog Register
    union   SYSCTL_WDCR_REG                  WDCR;                         // Watchdog Control Register
    union   SYSCTL_WDWCR_REG                 WDWCR;                        // Watchdog Windowed Control Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
