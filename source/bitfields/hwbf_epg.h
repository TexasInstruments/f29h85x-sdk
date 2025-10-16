//###########################################################################
//
// FILE:    hwbf_epg.h
//
// TITLE:   Definitions for the EPG registers.
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

#ifndef HWBF_EPG_H
#define HWBF_EPG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// EPG Individual Register Bit Definitions:

struct EPG_GCTL0_BITS {                 // bits description
    uint16_t EN:1;                      // 0 Enable EPG
    uint16_t SIGGEN0_EN:1;              // 1 Signal generator enable
    uint16_t SIGGEN1_EN:1;              // 2 Signal generator enable
    uint16_t rsvd1:5;                   // 7:3 Reserved
    uint16_t EPGOUT13SEL:1;             // 8 EPG output 13 Clock/signal select
    uint16_t EPGOUT15SEL:1;             // 9 EPG output 15 Clock/signal select
    uint16_t EPGOUT16SEL:1;             // 10 EPG output 16 Clock/signal select
    uint16_t EPGOUT17SEL:1;             // 11 EPG output 17 Clock/signal select
    uint16_t EPGOUT20SEL:1;             // 12 EPG output 20 Clock/signal select
    uint16_t EPGOUT21SEL:1;             // 13 EPG output 21 Clock/signal select
    uint16_t EPGOUT22SEL:1;             // 14 EPG output 22 Clock/signal select
    uint16_t EPGOUT23SEL:1;             // 15 EPG output 23 Clock/signal select
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPG_GCTL0_REG {
    uint32_t  all;
    struct  EPG_GCTL0_BITS  bit;
};

struct EPG_GCTL1_BITS {                 // bits description
    uint16_t SIGGEN0_CLKSEL:3;          // 2:0 Clock source select of SIGGEN0
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t SIGGEN1_CLKSEL:3;          // 6:4 Clock source select of SIGGEN1
    uint16_t rsvd2:9;                   // 15:7 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union EPG_GCTL1_REG {
    uint32_t  all;
    struct  EPG_GCTL1_BITS  bit;
};

struct EPG_GCTL2_BITS {                 // bits description
    uint16_t EPGOUT0_CLKOUTSEL:3;       // 2:0 Selects the clock signal source of EPG output 0.
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t EPGOUT1_CLKOUTSEL:3;       // 6:4 Selects the clock signal source of EPG output 1.
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t EPGOUT2_CLKOUTSEL:3;       // 10:8 Selects the clock signal source of EPG output 2.
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t EPGOUT3_CLKOUTSEL:3;       // 14:12 Selects the clock signal source of EPG output 3.
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t EPGOUT4_CLKOUTSEL:3;       // 18:16 Selects the clock signal source of EPG output 4.
    uint16_t rsvd5:1;                   // 19 Reserved
    uint16_t EPGOUT5_CLKOUTSEL:3;       // 22:20 Selects the clock signal source of EPG output 5.
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t EPGOUT6_CLKOUTSEL:3;       // 26:24 Selects the clock signal source of EPG output 6.
    uint16_t rsvd7:1;                   // 27 Reserved
    uint16_t EPGOUT7_CLKOUTSEL:3;       // 30:28 Selects the clock signal source of EPG output 7.
    uint16_t rsvd8:1;                   // 31 Reserved
};

union EPG_GCTL2_REG {
    uint32_t  all;
    struct  EPG_GCTL2_BITS  bit;
};

struct EPG_GCTL3_BITS {                 // bits description
    uint16_t EPGOUT0_SIGOUTSEL:4;       // 3:0 Selects the signal source of EPG output 0.
    uint16_t EPGOUT1_SIGOUTSEL:4;       // 7:4 Selects the signal source of EPG output 1.
    uint16_t EPGOUT2_SIGOUTSEL:4;       // 11:8 Selects the signal source of EPG output 2.
    uint16_t EPGOUT3_SIGOUTSEL:4;       // 15:12 Selects the signal source of EPG output 3.
    uint16_t EPGOUT4_SIGOUTSEL:4;       // 19:16 Selects the signal source of EPG output 4.
    uint16_t EPGOUT5_SIGOUTSEL:4;       // 23:20 Selects the signal source of EPG output 5.
    uint16_t EPGOUT6_SIGOUTSEL:4;       // 27:24 Selects the signal source of EPG output 6.
    uint16_t EPGOUT7_SIGOUTSEL:4;       // 31:28 Selects the signal source of EPG output 7.
};

union EPG_GCTL3_REG {
    uint32_t  all;
    struct  EPG_GCTL3_BITS  bit;
};

struct EPG_EPGLOCK_BITS {               // bits description
    uint16_t GCTL0:1;                   // 0 GCTL0 Lock bit
    uint16_t GCTL1:1;                   // 1 GCTL1 Lock bit
    uint16_t GCTL2:1;                   // 2 GCTL2 Lock bit
    uint16_t GCTL3:1;                   // 3 GCTL3 Lock bit
    uint16_t CLKDIV0_CTL0:1;            // 4 CLKDIV0_CTL0 Lock bit
    uint16_t CLKDIV1_CTL0:1;            // 5 CLKDIV1_CTL0 Lock bit
    uint16_t SIGGEN0_CTL0:1;            // 6 SIGGEN0_CTL0 Lock bit
    uint16_t SIGGEN0_CTL1:1;            // 7 SIGGEN0_CTL1 Lock bit
    uint16_t SIGGEN1_CTL0:1;            // 8 SIGGEN1_CTL0 Lock bit
    uint16_t SIGGEN1_CTL1:1;            // 9 SIGGEN1_CTL1 Lock bit
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPG_EPGLOCK_REG {
    uint32_t  all;
    struct  EPG_EPGLOCK_BITS  bit;
};

struct EPG_EPGCOMMIT_BITS {             // bits description
    uint16_t GCTL0:1;                   // 0 GCTL0 Commit bit
    uint16_t GCTL1:1;                   // 1 GCTL1 Commit bit
    uint16_t GCTL2:1;                   // 2 GCTL2 Commit bit
    uint16_t GCTL3:1;                   // 3 GCTL3 Commit bit
    uint16_t CLKDIV0_CTL0:1;            // 4 CLKDIV0_CTL0 Commit bit
    uint16_t CLKDIV1_CTL0:1;            // 5 CLKDIV1_CTL0 Commit bit
    uint16_t SIGGEN0_CTL0:1;            // 6 SIGGEN0_CTL0 Commit bit
    uint16_t SIGGEN0_CTL1:1;            // 7 SIGGEN0_CTL1 Commit bit
    uint16_t SIGGEN1_CTL0:1;            // 8 SIGGEN1_CTL0 Commit bit
    uint16_t SIGGEN1_CTL1:1;            // 9 SIGGEN1_CTL1 Commit bit
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPG_EPGCOMMIT_REG {
    uint32_t  all;
    struct  EPG_EPGCOMMIT_BITS  bit;
};

struct EPG_GINTSTS_BITS {               // bits description
    uint16_t INT:1;                     // 0 Global interrupt flag register
    uint16_t SIGGEN0_DONE:1;            // 1 SIGGEN0 operation done status
    uint16_t SIGGEN0_FILL:1;            // 2 SIGGEN0 data fill status
    uint16_t SIGGEN1_DONE:1;            // 3 SIGGEN1 operation done status
    uint16_t SIGGEN1_FILL:1;            // 4 SIGGEN1 data fill status
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPG_GINTSTS_REG {
    uint32_t  all;
    struct  EPG_GINTSTS_BITS  bit;
};

struct EPG_GINTEN_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t SIGGEN0_DONE:1;            // 1 SIGGEN0 operation done interrupt enable
    uint16_t SIGGEN0_FILL:1;            // 2 SIGGEN0 data fill interrupt enable
    uint16_t SIGGEN1_DONE:1;            // 3 SIGGEN1 operation done interrupt enable
    uint16_t SIGGEN1_FILL:1;            // 4 SIGGEN1 data fill interrupt enable
    uint16_t rsvd2:11;                  // 15:5 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union EPG_GINTEN_REG {
    uint32_t  all;
    struct  EPG_GINTEN_BITS  bit;
};

struct EPG_GINTCLR_BITS {               // bits description
    uint16_t INT:1;                     // 0 Global interrupt flag clear
    uint16_t SIGGEN0_DONE:1;            // 1 SIGGEN0 operation done interrupt flag clear
    uint16_t SIGGEN0_FILL:1;            // 2 SIGGEN0 data fill interrupt flag clear
    uint16_t SIGGEN1_DONE:1;            // 3 SIGGEN0 data fill interrupt flag clear
    uint16_t SIGGEN1_FILL:1;            // 4 SIGGEN1 data fill interrupt flag clear
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPG_GINTCLR_REG {
    uint32_t  all;
    struct  EPG_GINTCLR_BITS  bit;
};

struct EPG_GINTFRC_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t SIGGEN0_DONE:1;            // 1 SIGGEN0 operation done interrupt flag set
    uint16_t SIGGEN0_FILL:1;            // 2 SIGGEN0 data fill interrupt flag set
    uint16_t SIGGEN1_DONE:1;            // 3 SIGGEN1 operation done interrupt flag set
    uint16_t SIGGEN1_FILL:1;            // 4 SIGGEN1 data fill interrupt flag set
    uint16_t rsvd2:11;                  // 15:5 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union EPG_GINTFRC_REG {
    uint32_t  all;
    struct  EPG_GINTFRC_BITS  bit;
};

struct EPG_CLKDIV0_CTL0_BITS {          // bits description
    uint16_t PRD:16;                    // 15:0 Clock divider value
    uint16_t CLKSTOP:3;                 // 18:16 Clock Stop Configuration
    uint16_t rsvd1:13;                  // 31:19 Reserved
};

union EPG_CLKDIV0_CTL0_REG {
    uint32_t  all;
    struct  EPG_CLKDIV0_CTL0_BITS  bit;
};

struct EPG_CLKDIV0_CLKOFFSET_BITS {     // bits description
    uint16_t CLK0OFFSET:8;              // 7:0 Clock output 0 offset delay value.
    uint16_t CLK1OFFSET:8;              // 15:8 Clock output 0 offset delay value.
    uint16_t CLK2OFFSET:8;              // 23:16 Clock output 0 offset delay value.
    uint16_t CLK3OFFSET:8;              // 31:24 Clock output 0 offset delay value.
};

union EPG_CLKDIV0_CLKOFFSET_REG {
    uint32_t  all;
    struct  EPG_CLKDIV0_CLKOFFSET_BITS  bit;
};

struct EPG_CLKDIV1_CTL0_BITS {          // bits description
    uint16_t PRD:16;                    // 15:0 Clock divider value
    uint16_t CLKSTOP:3;                 // 18:16 Clock Stop Configuration
    uint16_t rsvd1:13;                  // 31:19 Reserved
};

union EPG_CLKDIV1_CTL0_REG {
    uint32_t  all;
    struct  EPG_CLKDIV1_CTL0_BITS  bit;
};

struct EPG_CLKDIV1_CLKOFFSET_BITS {     // bits description
    uint16_t CLK0OFFSET:8;              // 7:0 Clock output 0 offset delay value.
    uint16_t CLK1OFFSET:8;              // 15:8 Clock output 0 offset delay value.
    uint16_t CLK2OFFSET:8;              // 23:16 Clock output 0 offset delay value.
    uint16_t CLK3OFFSET:8;              // 31:24 Clock output 0 offset delay value.
};

union EPG_CLKDIV1_CLKOFFSET_REG {
    uint32_t  all;
    struct  EPG_CLKDIV1_CLKOFFSET_BITS  bit;
};

struct EPG_SIGGEN0_CTL0_BITS {          // bits description
    uint16_t MODE:4;                    // 3:0 Signal generator modes
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t BRIN:1;                    // 5 Reverse bits before transform
    uint16_t BROUT:1;                   // 6 Reverse bits after transform
    uint16_t rsvd2:9;                   // 15:7 Reserved
    uint16_t BITLENGTH:8;               // 23:16 Length of bit stream
    uint16_t rsvd3:8;                   // 31:24 Reserved
};

union EPG_SIGGEN0_CTL0_REG {
    uint32_t  all;
    struct  EPG_SIGGEN0_CTL0_BITS  bit;
};

struct EPG_SIGGEN0_CTL1_BITS {          // bits description
    uint16_t DATA0_INSEL:4;             // 3:0 Select the source of DATA[0] bit.
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:12;                  // 27:16 Reserved
    uint16_t DATA63_INSEL:4;            // 31:28 Select the source of DATA[63] bit.
};

union EPG_SIGGEN0_CTL1_REG {
    uint32_t  all;
    struct  EPG_SIGGEN0_CTL1_BITS  bit;
};

struct EPG_SIGGEN1_CTL0_BITS {          // bits description
    uint16_t MODE:4;                    // 3:0 Signal generator modes
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t BRIN:1;                    // 5 Reverse bits before transform
    uint16_t BROUT:1;                   // 6 Reverse bits after transform
    uint16_t rsvd2:9;                   // 15:7 Reserved
    uint16_t BITLENGTH:8;               // 23:16 Length of bit stream
    uint16_t rsvd3:8;                   // 31:24 Reserved
};

union EPG_SIGGEN1_CTL0_REG {
    uint32_t  all;
    struct  EPG_SIGGEN1_CTL0_BITS  bit;
};

struct EPG_SIGGEN1_CTL1_BITS {          // bits description
    uint16_t DATA0_INSEL:4;             // 3:0 Select the source of DATA[0] bit.
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:12;                  // 27:16 Reserved
    uint16_t DATA63_INSEL:4;            // 31:28 Select the source of DATA[63] bit.
};

union EPG_SIGGEN1_CTL1_REG {
    uint32_t  all;
    struct  EPG_SIGGEN1_CTL1_BITS  bit;
};

struct EPG_REVISION_BITS {              // bits description
    uint16_t MINOR:6;                   // 5:0 Minor Revision Number
    uint16_t CUSTOM:2;                  // 7:6 Custom Module Number
    uint16_t MAJOR:3;                   // 10:8 Major Revision Number
    uint16_t rsvd1:5;                   // 15:11 Reserved
    uint16_t FUNC:12;                   // 27:16 Functional Release Number
    uint16_t rsvd2:2;                   // 29:28 Reserved
    uint16_t SCHEME:2;                  // 31:30 Defines Scheme for Module
};

union EPG_REVISION_REG {
    uint32_t  all;
    struct  EPG_REVISION_BITS  bit;
};

struct EPG_REGS {
    union   EPG_GCTL0_REG                    GCTL0;                        // EPG Global control register 0
    union   EPG_GCTL1_REG                    GCTL1;                        // EPG Global control register 1
    union   EPG_GCTL2_REG                    GCTL2;                        // EPG Global control register 2
    union   EPG_GCTL3_REG                    GCTL3;                        // EPG Global control register 3
    union   EPG_EPGLOCK_REG                  EPGLOCK;                      // EPG LOCK Register
    union   EPG_EPGCOMMIT_REG                EPGCOMMIT;                    // EPG COMMIT register
    union   EPG_GINTSTS_REG                  GINTSTS;                      // EPG Global interrupt status register.
    union   EPG_GINTEN_REG                   GINTEN;                       // EPG Global interrupt enable register.
    union   EPG_GINTCLR_REG                  GINTCLR;                      // EPG Global interrupt clear register.
    union   EPG_GINTFRC_REG                  GINTFRC;                      // EPG Global interrupt force register.
    uint8_t                                  rsvd1[8];                     // Reserved
    union   EPG_CLKDIV0_CTL0_REG             CLKDIV0_CTL0;                 // Clock divider 0's control register 0
    uint8_t                                  rsvd2[8];                     // Reserved
    union   EPG_CLKDIV0_CLKOFFSET_REG        CLKDIV0_CLKOFFSET;            // Clock divider 0's clock offset value
    uint8_t                                  rsvd3[8];                     // Reserved
    union   EPG_CLKDIV1_CTL0_REG             CLKDIV1_CTL0;                 // Clock divider 1's control register 0
    uint8_t                                  rsvd4[8];                     // Reserved
    union   EPG_CLKDIV1_CLKOFFSET_REG        CLKDIV1_CLKOFFSET;            // Clock divider 1's clock offset value
    uint8_t                                  rsvd5[8];                     // Reserved
    union   EPG_SIGGEN0_CTL0_REG             SIGGEN0_CTL0;                 // Signal generator 0's control register 0
    union   EPG_SIGGEN0_CTL1_REG             SIGGEN0_CTL1;                 // Signal generator 0's control register 1
    uint8_t                                  rsvd6[8];                     // Reserved
    uint32_t                                 SIGGEN0_DATA0;                // Signal generator 0's data register 0
    uint32_t                                 SIGGEN0_DATA1;                // Signal generator 0's data register 1
    uint32_t                                 SIGGEN0_DATA0_ACTIVE;         // Signal generator 0's data active register 0
    uint32_t                                 SIGGEN0_DATA1_ACTIVE;         // Signal generator 0's data active register 1
    union   EPG_SIGGEN1_CTL0_REG             SIGGEN1_CTL0;                 // Signal generator 1's control register 0
    union   EPG_SIGGEN1_CTL1_REG             SIGGEN1_CTL1;                 // Signal generator 1's control register 1
    uint8_t                                  rsvd7[8];                     // Reserved
    uint32_t                                 SIGGEN1_DATA0;                // Signal generator 1's data register 0
    uint32_t                                 SIGGEN1_DATA1;                // Signal generator 1's data register 1
    uint32_t                                 SIGGEN1_DATA0_ACTIVE;         // Signal generator 1's data active register 0
    uint32_t                                 SIGGEN1_DATA1_ACTIVE;         // Signal generator 1's data active register 1
    union   EPG_REVISION_REG                 REVISION;                     // IP Revision tie-off value
};

struct EPG_EPGMXSEL0_BITS {             // bits description
    uint16_t SEL0:1;                    // 0 DATAOUT[0] mux select.
    uint16_t SEL1:1;                    // 1 DATAOUT[1] mux select.
    uint16_t SEL2:1;                    // 2 DATAOUT[2] mux select.
    uint16_t SEL3:1;                    // 3 DATAOUT[3] mux select.
    uint16_t SEL4:1;                    // 4 DATAOUT[4] mux select.
    uint16_t SEL5:1;                    // 5 DATAOUT[5] mux select.
    uint16_t SEL6:1;                    // 6 DATAOUT[6] mux select.
    uint16_t SEL7:1;                    // 7 DATAOUT[7] mux select.
    uint16_t SEL8:1;                    // 8 DATAOUT[8] mux select.
    uint16_t SEL9:1;                    // 9 DATAOUT[9] mux select.
    uint16_t SEL10:1;                   // 10 DATAOUT[10] mux select.
    uint16_t SEL11:1;                   // 11 DATAOUT[11] mux select.
    uint16_t SEL12:1;                   // 12 DATAOUT[12] mux select.
    uint16_t SEL13:1;                   // 13 DATAOUT[13] mux select.
    uint16_t SEL14:1;                   // 14 DATAOUT[14] mux select.
    uint16_t SEL15:1;                   // 15 DATAOUT[15] mux select.
    uint16_t SEL16:1;                   // 16 DATAOUT[16] mux select.
    uint16_t SEL17:1;                   // 17 DATAOUT[17] mux select.
    uint16_t SEL18:1;                   // 18 DATAOUT[18] mux select.
    uint16_t SEL19:1;                   // 19 DATAOUT[19] mux select.
    uint16_t SEL20:1;                   // 20 DATAOUT[20] mux select.
    uint16_t SEL21:1;                   // 21 DATAOUT[21] mux select.
    uint16_t SEL22:1;                   // 22 DATAOUT[22] mux select.
    uint16_t SEL23:1;                   // 23 DATAOUT[23] mux select.
    uint16_t SEL24:1;                   // 24 DATAOUT[24] mux select.
    uint16_t SEL25:1;                   // 25 DATAOUT[25] mux select.
    uint16_t SEL26:1;                   // 26 DATAOUT[26] mux select.
    uint16_t SEL27:1;                   // 27 DATAOUT[27] mux select.
    uint16_t SEL28:1;                   // 28 DATAOUT[28] mux select.
    uint16_t SEL29:1;                   // 29 DATAOUT[29] mux select.
    uint16_t SEL30:1;                   // 30 DATAOUT[30] mux select.
    uint16_t SEL31:1;                   // 31 DATAOUT[31] mux select.
};

union EPG_EPGMXSEL0_REG {
    uint32_t  all;
    struct  EPG_EPGMXSEL0_BITS  bit;
};

struct EPG_EPGMXSEL1_BITS {             // bits description
    uint16_t SEL32:1;                   // 0 DATAOUT[32] mux select.
    uint16_t SEL33:1;                   // 1 DATAOUT[33] mux select.
    uint16_t SEL34:1;                   // 2 DATAOUT[34] mux select.
    uint16_t SEL35:1;                   // 3 DATAOUT[35] mux select.
    uint16_t SEL36:1;                   // 4 DATAOUT[36] mux select.
    uint16_t SEL37:1;                   // 5 DATAOUT[37] mux select.
    uint16_t SEL38:1;                   // 6 DATAOUT[38] mux select.
    uint16_t SEL39:1;                   // 7 DATAOUT[39] mux select.
    uint16_t SEL40:1;                   // 8 DATAOUT[40] mux select.
    uint16_t SEL41:1;                   // 9 DATAOUT[41] mux select.
    uint16_t SEL42:1;                   // 10 DATAOUT[42] mux select.
    uint16_t SEL43:1;                   // 11 DATAOUT[43] mux select.
    uint16_t SEL44:1;                   // 12 DATAOUT[44] mux select.
    uint16_t SEL45:1;                   // 13 DATAOUT[45] mux select.
    uint16_t SEL46:1;                   // 14 DATAOUT[46] mux select.
    uint16_t SEL47:1;                   // 15 DATAOUT[47] mux select.
    uint16_t SEL48:1;                   // 16 DATAOUT[48] mux select.
    uint16_t SEL49:1;                   // 17 DATAOUT[49] mux select.
    uint16_t SEL50:1;                   // 18 DATAOUT[50] mux select.
    uint16_t SEL51:1;                   // 19 DATAOUT[51] mux select.
    uint16_t SEL52:1;                   // 20 DATAOUT[52] mux select.
    uint16_t SEL53:1;                   // 21 DATAOUT[53] mux select.
    uint16_t SEL54:1;                   // 22 DATAOUT[54] mux select.
    uint16_t SEL55:1;                   // 23 DATAOUT[55] mux select.
    uint16_t SEL56:1;                   // 24 DATAOUT[56] mux select.
    uint16_t SEL57:1;                   // 25 DATAOUT[57] mux select.
    uint16_t SEL58:1;                   // 26 DATAOUT[58] mux select.
    uint16_t SEL59:1;                   // 27 DATAOUT[59] mux select.
    uint16_t SEL60:1;                   // 28 DATAOUT[60] mux select.
    uint16_t SEL61:1;                   // 29 DATAOUT[61] mux select.
    uint16_t SEL62:1;                   // 30 DATAOUT[62] mux select.
    uint16_t SEL63:1;                   // 31 DATAOUT[63] mux select.
};

union EPG_EPGMXSEL1_REG {
    uint32_t  all;
    struct  EPG_EPGMXSEL1_BITS  bit;
};

struct EPG_EPGMXSELLOCK_BITS {          // bits description
    uint16_t EPGMXSEL0:1;               // 0 EPGMXSEL0 lock bit
    uint16_t EPGMXSEL1:1;               // 1 EPGMXSEL1 lock bit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPG_EPGMXSELLOCK_REG {
    uint32_t  all;
    struct  EPG_EPGMXSELLOCK_BITS  bit;
};

struct EPG_EPGMXSELCOMMIT_BITS {        // bits description
    uint16_t EPGMXSEL0:1;               // 0 EPGMXSEL0 commit bit
    uint16_t EPGMXSEL1:1;               // 1 EPGMXSEL1 commit bit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union EPG_EPGMXSELCOMMIT_REG {
    uint32_t  all;
    struct  EPG_EPGMXSELCOMMIT_BITS  bit;
};

struct EPG_MUX_REGS {
    union   EPG_EPGMXSEL0_REG                EPGMXSEL0;                    // EPG Mux select register 0
    union   EPG_EPGMXSEL1_REG                EPGMXSEL1;                    // EPG Mux select register 1
    uint8_t                                  rsvd1[16];                    // Reserved
    union   EPG_EPGMXSELLOCK_REG             EPGMXSELLOCK;                 // EPG Mux select register lock
    union   EPG_EPGMXSELCOMMIT_REG           EPGMXSELCOMMIT;               // EPG Mux select register commit
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
