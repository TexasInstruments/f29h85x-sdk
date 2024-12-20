//###########################################################################
//
// FILE:    hwbf_cmpss.h
//
// TITLE:   Definitions for the CMPSS registers.
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

#ifndef HWBF_CMPSS_H
#define HWBF_CMPSS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// CMPSS Individual Register Bit Definitions:

struct CMPSS_COMPCTL_BITS {             // bits description
    uint16_t COMPHSOURCE:1;             // 0 High Comparator Source Select
    uint16_t COMPHINV:1;                // 1 High Comparator Invert Select
    uint16_t CTRIPHSEL:2;               // 3:2 High Comparator Trip Select
    uint16_t CTRIPOUTHSEL:2;            // 5:4 High Comparator Trip Output Select
    uint16_t ASYNCHEN:1;                // 6 High Comparator Asynchronous Path Enable
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t COMPLSOURCE:1;             // 8 Low Comparator Source Select
    uint16_t COMPLINV:1;                // 9 Low Comparator Invert Select
    uint16_t CTRIPLSEL:2;               // 11:10 Low Comparator Trip Select
    uint16_t CTRIPOUTLSEL:2;            // 13:12 Low Comparator Trip Output Select
    uint16_t ASYNCLEN:1;                // 14 Low Comparator Asynchronous Path Enable
    uint16_t COMPDACE:1;                // 15 Comparator/DAC Enable
};

union CMPSS_COMPCTL_REG {
    uint16_t  all;
    struct  CMPSS_COMPCTL_BITS  bit;
};

struct CMPSS_COMPHYSCTL_BITS {          // bits description
    uint16_t COMPHYS:4;                 // 3:0 Comparator Hysteresis Trim
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union CMPSS_COMPHYSCTL_REG {
    uint16_t  all;
    struct  CMPSS_COMPHYSCTL_BITS  bit;
};

struct CMPSS_COMPSTS_BITS {             // bits description
    uint16_t COMPHSTS:1;                // 0 High Comparator Status
    uint16_t COMPHLATCH:1;              // 1 High Comparator Latched Status
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t COMPLSTS:1;                // 8 Low Comparator Status
    uint16_t COMPLLATCH:1;              // 9 Low Comparator Latched Status
    uint16_t rsvd2:6;                   // 15:10 Reserved
};

union CMPSS_COMPSTS_REG {
    uint16_t  all;
    struct  CMPSS_COMPSTS_BITS  bit;
};

struct CMPSS_COMPSTSCLR_BITS {          // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t HLATCHCLR:1;               // 1 High Comparator Latched Status Clear
    uint16_t HSYNCCLREN:1;              // 2 High Comparator EPWMSYNCPER Clear Enable
    uint16_t rsvd2:6;                   // 8:3 Reserved
    uint16_t LLATCHCLR:1;               // 9 Low Comparator Latched Status Clear
    uint16_t LSYNCCLREN:1;              // 10 Low Comparator EPWMSYNCPER Clear Enable
    uint16_t rsvd3:5;                   // 15:11 Reserved
};

union CMPSS_COMPSTSCLR_REG {
    uint16_t  all;
    struct  CMPSS_COMPSTSCLR_BITS  bit;
};

struct CMPSS_COMPDACHCTL_BITS {         // bits description
    uint16_t DACSOURCE:1;               // 0 DAC Source Control
    uint16_t RAMPSOURCE:4;              // 4:1 Ramp Generator Source Control
    uint16_t SELREF:1;                  // 5 DAC Reference Select
    uint16_t RAMPLOADSEL:1;             // 6 Ramp Load Select
    uint16_t SWLOADSEL:1;               // 7 Software Load Select
    uint16_t BLANKSOURCE:4;             // 11:8 EPWMBLANK Source Select
    uint16_t BLANKEN:1;                 // 12 EPWMBLANK Enable
    uint16_t RAMPDIR:1;                 // 13 Ramp Generator Direction
    uint16_t FREESOFT:2;                // 15:14 Free/Soft Emulation Bits
};

union CMPSS_COMPDACHCTL_REG {
    uint16_t  all;
    struct  CMPSS_COMPDACHCTL_BITS  bit;
};

struct CMPSS_COMPDACHCTL2_BITS {        // bits description
    uint16_t DEENABLE:1;                // 0 Diode Emulation mode enable
    uint16_t DEACTIVESEL:5;             // 5:1 DEACTIVE source select
    uint16_t rsvd1:2;                   // 7:6 Reserved
    uint16_t BLANKSOURCEUSEL:1;         // 8 BLANK source upper group select
    uint16_t rsvd2:1;                   // 9 Reserved
    uint16_t RAMPSOURCEUSEL:1;          // 10 RAMP source upper group select
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t XTRIGCFG:2;                // 13:12 Ramp Generator Cross Trigger Configuration
    uint16_t rsvd4:2;                   // 15:14 Reserved
};

union CMPSS_COMPDACHCTL2_REG {
    uint16_t  all;
    struct  CMPSS_COMPDACHCTL2_BITS  bit;
};

struct CMPSS_DACHVALS_BITS {            // bits description
    uint16_t DACVAL:12;                 // 11:0 DAC Value Control
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union CMPSS_DACHVALS_REG {
    uint16_t  all;
    struct  CMPSS_DACHVALS_BITS  bit;
};

struct CMPSS_DACHVALA_BITS {            // bits description
    uint16_t DACVAL:12;                 // 11:0 DAC Value Control
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union CMPSS_DACHVALA_REG {
    uint16_t  all;
    struct  CMPSS_DACHVALA_BITS  bit;
};

struct CMPSS_RAMPHCTLA_BITS {           // bits description
    uint16_t RAMPCLKDIV:4;              // 3:0 Ramp Clock Divider Active Value
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union CMPSS_RAMPHCTLA_REG {
    uint16_t  all;
    struct  CMPSS_RAMPHCTLA_BITS  bit;
};

struct CMPSS_RAMPHCTLS_BITS {           // bits description
    uint16_t RAMPCLKDIV:4;              // 3:0 Ramp Clock Divider Shadow Value
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union CMPSS_RAMPHCTLS_REG {
    uint16_t  all;
    struct  CMPSS_RAMPHCTLS_BITS  bit;
};

struct CMPSS_DACLVALS_BITS {            // bits description
    uint16_t DACVAL:12;                 // 11:0 DAC Value Control
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union CMPSS_DACLVALS_REG {
    uint16_t  all;
    struct  CMPSS_DACLVALS_BITS  bit;
};

struct CMPSS_DACLVALA_BITS {            // bits description
    uint16_t DACVAL:12;                 // 11:0 DAC Value Control
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union CMPSS_DACLVALA_REG {
    uint16_t  all;
    struct  CMPSS_DACLVALA_BITS  bit;
};

struct CMPSS_RAMPHDLYA_BITS {           // bits description
    uint16_t DELAY:13;                  // 12:0 High Ramp Delay Value Active
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union CMPSS_RAMPHDLYA_REG {
    uint16_t  all;
    struct  CMPSS_RAMPHDLYA_BITS  bit;
};

struct CMPSS_RAMPHDLYS_BITS {           // bits description
    uint16_t DELAY:13;                  // 12:0 High Ramp Delay Value Shadow
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union CMPSS_RAMPHDLYS_REG {
    uint16_t  all;
    struct  CMPSS_RAMPHDLYS_BITS  bit;
};

struct CMPSS_CTRIPLFILCTL_BITS {        // bits description
    uint16_t FILTINSEL:3;               // 2:0 Filter Input Select
    uint16_t SAMPWIN:6;                 // 8:3 Sample Window
    uint16_t THRESH:6;                  // 14:9 Majority Voting Threshold
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union CMPSS_CTRIPLFILCTL_REG {
    uint16_t  all;
    struct  CMPSS_CTRIPLFILCTL_BITS  bit;
};

struct CMPSS_CTRIPHFILCTL_BITS {        // bits description
    uint16_t FILTINSEL:3;               // 2:0 Filter Input Select
    uint16_t SAMPWIN:6;                 // 8:3 Sample Window
    uint16_t THRESH:6;                  // 14:9 Majority Voting Threshold
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union CMPSS_CTRIPHFILCTL_REG {
    uint16_t  all;
    struct  CMPSS_CTRIPHFILCTL_BITS  bit;
};

struct CMPSS_COMPLOCK_BITS {            // bits description
    uint16_t COMPCTL:1;                 // 0 COMPCTL Lock
    uint16_t COMPHYSCTL:1;              // 1 COMPHYSCTL Lock
    uint16_t DACCTL:1;                  // 2 DACCTL Lock
    uint16_t CTRIP:1;                   // 3 CTRIP Lock
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:11;                  // 15:5 Reserved
};

union CMPSS_COMPLOCK_REG {
    uint16_t  all;
    struct  CMPSS_COMPLOCK_BITS  bit;
};

struct CMPSS_DACHVALS2_BITS {           // bits description
    uint16_t DACVAL:12;                 // 11:0 DAC Value Control
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union CMPSS_DACHVALS2_REG {
    uint16_t  all;
    struct  CMPSS_DACHVALS2_BITS  bit;
};

struct CMPSS_DACLVALS2_BITS {           // bits description
    uint16_t DACVAL:12;                 // 11:0 DAC Value Control
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union CMPSS_DACLVALS2_REG {
    uint16_t  all;
    struct  CMPSS_DACLVALS2_BITS  bit;
};

struct CMPSS_COMPDACLCTL_BITS {         // bits description
    uint16_t DACSOURCE:1;               // 0 DAC Source Control
    uint16_t RAMPSOURCE:4;              // 4:1 Ramp Generator Source Control
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t RAMPLOADSEL:1;             // 6 Ramp Load Select
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t BLANKSOURCE:4;             // 11:8 EPWMBLANK Source Select
    uint16_t BLANKEN:1;                 // 12 EPWMBLANK Enable
    uint16_t RAMPDIR:1;                 // 13 Ramp Generator Direction
    uint16_t rsvd3:2;                   // 15:14 Reserved
};

union CMPSS_COMPDACLCTL_REG {
    uint16_t  all;
    struct  CMPSS_COMPDACLCTL_BITS  bit;
};

struct CMPSS_COMPDACLCTL2_BITS {        // bits description
    uint16_t rsvd1:8;                   // 7:0 Reserved
    uint16_t BLANKSOURCEUSEL:1;         // 8 BLANK source upper group select
    uint16_t rsvd2:1;                   // 9 Reserved
    uint16_t RAMPSOURCEUSEL:1;          // 10 RAMP source upper group select
    uint16_t rsvd3:5;                   // 15:11 Reserved
};

union CMPSS_COMPDACLCTL2_REG {
    uint16_t  all;
    struct  CMPSS_COMPDACLCTL2_BITS  bit;
};

struct CMPSS_RAMPLCTLA_BITS {           // bits description
    uint16_t RAMPCLKDIV:4;              // 3:0 Ramp Clock Divider Active Value
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union CMPSS_RAMPLCTLA_REG {
    uint16_t  all;
    struct  CMPSS_RAMPLCTLA_BITS  bit;
};

struct CMPSS_RAMPLCTLS_BITS {           // bits description
    uint16_t RAMPCLKDIV:4;              // 3:0 Ramp Clock Divider Shadow Value
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union CMPSS_RAMPLCTLS_REG {
    uint16_t  all;
    struct  CMPSS_RAMPLCTLS_BITS  bit;
};

struct CMPSS_RAMPLDLYA_BITS {           // bits description
    uint16_t DELAY:13;                  // 12:0 Low Ramp Delay Value Active
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union CMPSS_RAMPLDLYA_REG {
    uint16_t  all;
    struct  CMPSS_RAMPLDLYA_BITS  bit;
};

struct CMPSS_RAMPLDLYS_BITS {           // bits description
    uint16_t DELAY:13;                  // 12:0 Low Ramp Delay Value Shadow
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union CMPSS_RAMPLDLYS_REG {
    uint16_t  all;
    struct  CMPSS_RAMPLDLYS_BITS  bit;
};

struct CMPSS_CTRIPLFILCLKCTL2_BITS {    // bits description
    uint16_t CLKPRESCALEU:8;            // 7:0 Sample Clock Prescale Upper Bits
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union CMPSS_CTRIPLFILCLKCTL2_REG {
    uint16_t  all;
    struct  CMPSS_CTRIPLFILCLKCTL2_BITS  bit;
};

struct CMPSS_CTRIPHFILCLKCTL2_BITS {    // bits description
    uint16_t CLKPRESCALEU:8;            // 7:0 Sample Clock Prescale Upper Bits
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union CMPSS_CTRIPHFILCLKCTL2_REG {
    uint16_t  all;
    struct  CMPSS_CTRIPHFILCLKCTL2_BITS  bit;
};

struct CMPSS_REGS {
    union   CMPSS_COMPCTL_REG                COMPCTL;                      // CMPSS Comparator Control Register
    union   CMPSS_COMPHYSCTL_REG             COMPHYSCTL;                   // CMPSS Comparator Hysteresis Control Register
    union   CMPSS_COMPSTS_REG                COMPSTS;                      // CMPSS Comparator Status Register
    union   CMPSS_COMPSTSCLR_REG             COMPSTSCLR;                   // CMPSS Comparator Status Clear Register
    union   CMPSS_COMPDACHCTL_REG            COMPDACHCTL;                  // CMPSS High DAC Control Register
    union   CMPSS_COMPDACHCTL2_REG           COMPDACHCTL2;                 // CMPSS High DAC Control Register 2
    union   CMPSS_DACHVALS_REG               DACHVALS;                     // CMPSS High DAC Value Shadow Register
    union   CMPSS_DACHVALA_REG               DACHVALA;                     // CMPSS High DAC Value Active Register
    uint16_t                                 RAMPHREFA;                    // CMPSS High Ramp Reference Active Register
    uint8_t                                  rsvd1[2];                     // Reserved
    uint16_t                                 RAMPHREFS;                    // CMPSS High Ramp Reference Shadow Register
    uint8_t                                  rsvd2[2];                     // Reserved
    uint16_t                                 RAMPHSTEPVALA;                // CMPSS High Ramp Step Value Active Register
    union   CMPSS_RAMPHCTLA_REG              RAMPHCTLA;                    // CMPSS High Ramp Control Active Register
    uint16_t                                 RAMPHSTEPVALS;                // CMPSS High Ramp Step Value Shadow Register
    union   CMPSS_RAMPHCTLS_REG              RAMPHCTLS;                    // CMPSS High Ramp Control Shadow Register
    uint16_t                                 RAMPHSTS;                     // CMPSS High Ramp Status Register
    uint8_t                                  rsvd3[2];                     // Reserved
    union   CMPSS_DACLVALS_REG               DACLVALS;                     // CMPSS Low DAC Value Shadow Register
    union   CMPSS_DACLVALA_REG               DACLVALA;                     // CMPSS Low DAC Value Active Register
    union   CMPSS_RAMPHDLYA_REG              RAMPHDLYA;                    // CMPSS High Ramp Delay Active Register
    union   CMPSS_RAMPHDLYS_REG              RAMPHDLYS;                    // CMPSS High Ramp Delay Shadow Register
    union   CMPSS_CTRIPLFILCTL_REG           CTRIPLFILCTL;                 // CTRIPL Filter Control Register
    uint16_t                                 CTRIPLFILCLKCTL;              // CTRIPL Filter Clock Control Register
    union   CMPSS_CTRIPHFILCTL_REG           CTRIPHFILCTL;                 // CTRIPH Filter Control Register
    uint16_t                                 CTRIPHFILCLKCTL;              // CTRIPH Filter Clock Control Register
    union   CMPSS_COMPLOCK_REG               COMPLOCK;                     // CMPSS Lock Register
    uint8_t                                  rsvd4[2];                     // Reserved
    union   CMPSS_DACHVALS2_REG              DACHVALS2;                    // CMPSS High DAC Value Shadow Register 2
    union   CMPSS_DACLVALS2_REG              DACLVALS2;                    // CMPSS Low DAC Value Shadow Register 2
    uint8_t                                  rsvd5[12];                    // Reserved
    union   CMPSS_COMPDACLCTL_REG            COMPDACLCTL;                  // CMPSS Low DAC Control Register
    union   CMPSS_COMPDACLCTL2_REG           COMPDACLCTL2;                 // CMPSS Low DAC Control Register 2
    uint8_t                                  rsvd6[4];                     // Reserved
    uint16_t                                 RAMPLREFA;                    // CMPSS Low Ramp Reference Active Register
    uint8_t                                  rsvd7[2];                     // Reserved
    uint16_t                                 RAMPLREFS;                    // CMPSS Low Ramp Reference Shadow Register
    uint8_t                                  rsvd8[2];                     // Reserved
    uint16_t                                 RAMPLSTEPVALA;                // CMPSS Low Ramp Step Value Active Register
    union   CMPSS_RAMPLCTLA_REG              RAMPLCTLA;                    // CMPSS Low Ramp Control Active Register
    uint16_t                                 RAMPLSTEPVALS;                // CMPSS Low Ramp Step Value Shadow Register
    union   CMPSS_RAMPLCTLS_REG              RAMPLCTLS;                    // CMPSS Low Ramp Control Shadow Register
    uint16_t                                 RAMPLSTS;                     // CMPSS Low Ramp Status Register
    uint8_t                                  rsvd9[6];                     // Reserved
    union   CMPSS_RAMPLDLYA_REG              RAMPLDLYA;                    // CMPSS Low Ramp Delay Active Register
    union   CMPSS_RAMPLDLYS_REG              RAMPLDLYS;                    // CMPSS Low Ramp Delay Shadow Register
    uint8_t                                  rsvd10[2];                    // Reserved
    union   CMPSS_CTRIPLFILCLKCTL2_REG       CTRIPLFILCLKCTL2;             // CTRIPL Filter Clock Control Register 2
    uint8_t                                  rsvd11[2];                    // Reserved
    union   CMPSS_CTRIPHFILCLKCTL2_REG       CTRIPHFILCLKCTL2;             // CTRIPH Filter Clock Control Register 2
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
