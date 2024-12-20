//###########################################################################
//
// FILE:    hwbf_eqep.h
//
// TITLE:   Definitions for the EQEP registers.
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

#ifndef HWBF_EQEP_H
#define HWBF_EQEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// EQEP Individual Register Bit Definitions:

struct EQEP_QDECCTL_BITS {              // bits description
    uint16_t QIDIRE:1;                  // 0 Qep Index Direction Enhancement enable
    uint16_t rsvd1:4;                   // 4:1 Reserved
    uint16_t QSP:1;                     // 5 QEPS input polarity
    uint16_t QIP:1;                     // 6 QEPI input polarity
    uint16_t QBP:1;                     // 7 QEPB input polarity
    uint16_t QAP:1;                     // 8 QEPA input polarity
    uint16_t IGATE:1;                   // 9 Index pulse gating option
    uint16_t SWAP:1;                    // 10 CLK/DIR Signal Source for Position Counter
    uint16_t XCR:1;                     // 11 External Clock Rate
    uint16_t SPSEL:1;                   // 12 Sync output pin selection
    uint16_t SOEN:1;                    // 13 Sync output-enable
    uint16_t QSRC:2;                    // 15:14 Position-counter source selection
};

union EQEP_QDECCTL_REG {
    uint16_t  all;
    struct  EQEP_QDECCTL_BITS  bit;
};

struct EQEP_QEPCTL_BITS {               // bits description
    uint16_t WDE:1;                     // 0 QEP watchdog enable
    uint16_t UTE:1;                     // 1 QEP unit timer enable
    uint16_t QCLM:1;                    // 2 QEP capture latch mode
    uint16_t QPEN:1;                    // 3 Quadrature postotion counter enable
    uint16_t IEL:2;                     // 5:4 Index event latch
    uint16_t SEL:1;                     // 6 Strobe event latch
    uint16_t SWI:1;                     // 7 Software init position counter
    uint16_t IEI:2;                     // 9:8 Index event init of position count
    uint16_t SEI:2;                     // 11:10 Strobe event init
    uint16_t PCRM:2;                    // 13:12 Postion counter reset
    uint16_t FREE_SOFT:2;               // 15:14 Emulation mode
};

union EQEP_QEPCTL_REG {
    uint16_t  all;
    struct  EQEP_QEPCTL_BITS  bit;
};

struct EQEP_QCAPCTL_BITS {              // bits description
    uint16_t UPPS:4;                    // 3:0 Unit position event prescaler
    uint16_t CCPS:3;                    // 6:4 eQEP capture timer clock prescaler
    uint16_t rsvd1:8;                   // 14:7 Reserved
    uint16_t CEN:1;                     // 15 Enable eQEP capture
};

union EQEP_QCAPCTL_REG {
    uint16_t  all;
    struct  EQEP_QCAPCTL_BITS  bit;
};

struct EQEP_QPOSCTL_BITS {              // bits description
    uint16_t PCSPW:12;                  // 11:0 Position compare sync pulse width
    uint16_t PCE:1;                     // 12 Position compare enable/disable
    uint16_t PCPOL:1;                   // 13 Polarity of sync output
    uint16_t PCLOAD:1;                  // 14 Position compare of shadow load
    uint16_t PCSHDW:1;                  // 15 Position compare of shadow enable
};

union EQEP_QPOSCTL_REG {
    uint16_t  all;
    struct  EQEP_QPOSCTL_BITS  bit;
};

struct EQEP_QEINT_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t PCE:1;                     // 1 Position counter error interrupt enable
    uint16_t QPE:1;                     // 2 Quadrature phase error interrupt enable
    uint16_t QDC:1;                     // 3 Quadrature direction change interrupt enable
    uint16_t WTO:1;                     // 4 Watchdog time out interrupt enable
    uint16_t PCU:1;                     // 5 Position counter underflow interrupt enable
    uint16_t PCO:1;                     // 6 Position counter overflow interrupt enable
    uint16_t PCR:1;                     // 7 Position-compare ready interrupt enable
    uint16_t PCM:1;                     // 8 Position-compare match interrupt enable
    uint16_t SEL:1;                     // 9 Strobe event latch interrupt enable
    uint16_t IEL:1;                     // 10 Index event latch interrupt enable
    uint16_t UTO:1;                     // 11 Unit time out interrupt enable
    uint16_t QMAE:1;                    // 12 QMA error interrupt enable
    uint16_t rsvd2:3;                   // 15:13 Reserved
};

union EQEP_QEINT_REG {
    uint16_t  all;
    struct  EQEP_QEINT_BITS  bit;
};

struct EQEP_QFLG_BITS {                 // bits description
    uint16_t INT:1;                     // 0 Global interrupt status flag
    uint16_t PCE:1;                     // 1 Position counter error interrupt flag
    uint16_t PHE:1;                     // 2 Quadrature phase error interrupt flag
    uint16_t QDC:1;                     // 3 Quadrature direction change interrupt flag
    uint16_t WTO:1;                     // 4 Watchdog timeout interrupt flag
    uint16_t PCU:1;                     // 5 Position counter underflow interrupt flag
    uint16_t PCO:1;                     // 6 Position counter overflow interrupt flag
    uint16_t PCR:1;                     // 7 Position-compare ready interrupt flag
    uint16_t PCM:1;                     // 8 eQEP compare match event interrupt flag
    uint16_t SEL:1;                     // 9 Strobe event latch interrupt flag
    uint16_t IEL:1;                     // 10 Index event latch interrupt flag
    uint16_t UTO:1;                     // 11 Unit time out interrupt flag
    uint16_t QMAE:1;                    // 12 QMA error interrupt flag
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union EQEP_QFLG_REG {
    uint16_t  all;
    struct  EQEP_QFLG_BITS  bit;
};

struct EQEP_QCLR_BITS {                 // bits description
    uint16_t INT:1;                     // 0 Global interrupt clear flag
    uint16_t PCE:1;                     // 1 Clear position counter error interrupt flag
    uint16_t PHE:1;                     // 2 Clear quadrature phase error interrupt flag
    uint16_t QDC:1;                     // 3 Clear quadrature direction change interrupt flag
    uint16_t WTO:1;                     // 4 Clear watchdog timeout interrupt flag
    uint16_t PCU:1;                     // 5 Clear position counter underflow interrupt flag
    uint16_t PCO:1;                     // 6 Clear position counter overflow interrupt flag
    uint16_t PCR:1;                     // 7 Clear position-compare ready interrupt flag
    uint16_t PCM:1;                     // 8 Clear eQEP compare match event interrupt flag
    uint16_t SEL:1;                     // 9 Clear strobe event latch interrupt flag
    uint16_t IEL:1;                     // 10 Clear index event latch interrupt flag
    uint16_t UTO:1;                     // 11 Clear unit time out interrupt flag
    uint16_t QMAE:1;                    // 12 Clear QMA error interrupt flag
    uint16_t rsvd1:3;                   // 15:13 Reserved
};

union EQEP_QCLR_REG {
    uint16_t  all;
    struct  EQEP_QCLR_BITS  bit;
};

struct EQEP_QFRC_BITS {                 // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t PCE:1;                     // 1 Force position counter error interrupt
    uint16_t PHE:1;                     // 2 Force quadrature phase error interrupt
    uint16_t QDC:1;                     // 3 Force quadrature direction change interrupt
    uint16_t WTO:1;                     // 4 Force watchdog time out interrupt
    uint16_t PCU:1;                     // 5 Force position counter underflow interrupt
    uint16_t PCO:1;                     // 6 Force position counter overflow interrupt
    uint16_t PCR:1;                     // 7 Force position-compare ready interrupt
    uint16_t PCM:1;                     // 8 Force position-compare match interrupt
    uint16_t SEL:1;                     // 9 Force strobe event latch interrupt
    uint16_t IEL:1;                     // 10 Force index event latch interrupt
    uint16_t UTO:1;                     // 11 Force unit time out interrupt
    uint16_t QMAE:1;                    // 12 Force QMA error interrupt
    uint16_t rsvd2:3;                   // 15:13 Reserved
};

union EQEP_QFRC_REG {
    uint16_t  all;
    struct  EQEP_QFRC_BITS  bit;
};

struct EQEP_QEPSTS_BITS {               // bits description
    uint16_t PCEF:1;                    // 0 Position counter error flag.
    uint16_t FIMF:1;                    // 1 First index marker flag
    uint16_t CDEF:1;                    // 2 Capture direction error flag
    uint16_t COEF:1;                    // 3 Capture overflow error flag
    uint16_t QDLF:1;                    // 4 eQEP direction latch flag
    uint16_t QDF:1;                     // 5 Quadrature direction flag
    uint16_t FIDF:1;                    // 6 The first index marker
    uint16_t UPEVNT:1;                  // 7 Unit position event flag
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union EQEP_QEPSTS_REG {
    uint16_t  all;
    struct  EQEP_QEPSTS_BITS  bit;
};

struct EQEP_REV_BITS {                  // bits description
    uint16_t MAJOR:3;                   // 2:0 Major Revision Number
    uint16_t MINOR:3;                   // 5:3 Minor Revision Number
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EQEP_REV_REG {
    uint32_t  all;
    struct  EQEP_REV_BITS  bit;
};

struct EQEP_QEPSTROBESEL_BITS {         // bits description
    uint16_t STROBESEL:2;               // 1:0 QMA Mode Select
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EQEP_QEPSTROBESEL_REG {
    uint32_t  all;
    struct  EQEP_QEPSTROBESEL_BITS  bit;
};

struct EQEP_QMACTRL_BITS {              // bits description
    uint16_t MODE:3;                    // 2:0 QMA Mode Select
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EQEP_QMACTRL_REG {
    uint32_t  all;
    struct  EQEP_QMACTRL_BITS  bit;
};

struct EQEP_QEPSRCSEL_BITS {            // bits description
    uint16_t QEPASEL:4;                 // 3:0 QEPA Source select
    uint16_t QEPBSEL:4;                 // 7:4 QEPB Source select
    uint16_t QEPISEL:4;                 // 11:8 QEPI Source select
    uint16_t QEPSSEL:4;                 // 15:12 QEPS Source select
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union EQEP_QEPSRCSEL_REG {
    uint32_t  all;
    struct  EQEP_QEPSRCSEL_BITS  bit;
};

struct EQEP_REGS {
    uint32_t                                 QPOSCNT;                      // Position Counter
    uint32_t                                 QPOSINIT;                     // Position Counter Init
    uint32_t                                 QPOSMAX;                      // Maximum Position Count
    uint32_t                                 QPOSCMP;                      // Position Compare
    uint32_t                                 QPOSILAT;                     // Index Position Latch
    uint32_t                                 QPOSSLAT;                     // Strobe Position Latch
    uint32_t                                 QPOSLAT;                      // Position Latch
    uint32_t                                 QUTMR;                        // QEP Unit Timer
    uint32_t                                 QUPRD;                        // QEP Unit Period
    uint16_t                                 QWDTMR;                       // QEP Watchdog Timer
    uint16_t                                 QWDPRD;                       // QEP Watchdog Period
    union   EQEP_QDECCTL_REG                 QDECCTL;                      // Quadrature Decoder Control
    union   EQEP_QEPCTL_REG                  QEPCTL;                       // QEP Control
    union   EQEP_QCAPCTL_REG                 QCAPCTL;                      // Qaudrature Capture Control
    union   EQEP_QPOSCTL_REG                 QPOSCTL;                      // Position Compare Control
    union   EQEP_QEINT_REG                   QEINT;                        // QEP Interrupt Control
    union   EQEP_QFLG_REG                    QFLG;                         // QEP Interrupt Flag
    union   EQEP_QCLR_REG                    QCLR;                         // QEP Interrupt Clear
    union   EQEP_QFRC_REG                    QFRC;                         // QEP Interrupt Force
    union   EQEP_QEPSTS_REG                  QEPSTS;                       // QEP Status
    uint16_t                                 QCTMR;                        // QEP Capture Timer
    uint16_t                                 QCPRD;                        // QEP Capture Period
    uint16_t                                 QCTMRLAT;                     // QEP Capture Latch
    uint16_t                                 QCPRDLAT;                     // QEP Capture Period Latch
    uint8_t                                  rsvd1[30];                    // Reserved
    union   EQEP_REV_REG                     REV;                          // QEP Revision Number
    union   EQEP_QEPSTROBESEL_REG            QEPSTROBESEL;                 // QEP Strobe select register
    union   EQEP_QMACTRL_REG                 QMACTRL;                      // QMA Control register
    union   EQEP_QEPSRCSEL_REG               QEPSRCSEL;                    // QEP Source Select Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
