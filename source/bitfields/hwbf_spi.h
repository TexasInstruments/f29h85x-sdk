//###########################################################################
//
// FILE:    hwbf_spi.h
//
// TITLE:   Definitions for the SPI registers.
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

#ifndef HWBF_SPI_H
#define HWBF_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// SPI Individual Register Bit Definitions:

struct SPI_SPICCR_BITS {                // bits description
    uint16_t SPICHAR:4;                 // 3:0 Character Length Control
    uint16_t SPILBK:1;                  // 4 SPI Loopback
    uint16_t HS_MODE:1;                 // 5 High Speed mode control
    uint16_t CLKPOLARITY:1;             // 6 Shift Clock Polarity
    uint16_t SPISWRESET:1;              // 7 SPI Software Reset
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union SPI_SPICCR_REG {
    uint16_t  all;
    struct  SPI_SPICCR_BITS  bit;
};

struct SPI_SPICTL_BITS {                // bits description
    uint16_t SPIINTENA:1;               // 0 SPI Interupt Enable
    uint16_t TALK:1;                    // 1 CONTROLLER/PERIPHERAL Transmit Enable
    uint16_t CONTROLLER_PERIPHERAL:1;   // 2 SPI Network Mode Control
    uint16_t CLK_PHASE:1;               // 3 SPI Clock Phase
    uint16_t OVERRUNINTENA:1;           // 4 Overrun Interrupt Enable
    uint16_t rsvd1:11;                  // 15:5 Reserved
};

union SPI_SPICTL_REG {
    uint16_t  all;
    struct  SPI_SPICTL_BITS  bit;
};

struct SPI_SPISTS_BITS {                // bits description
    uint16_t rsvd1:5;                   // 4:0 Reserved
    uint16_t BUFFULL_FLAG:1;            // 5 SPI Transmit Buffer Full Flag
    uint16_t INT_FLAG:1;                // 6 SPI Interrupt Flag
    uint16_t OVERRUN_FLAG:1;            // 7 SPI Receiver Overrun Flag
    uint16_t rsvd2:8;                   // 15:8 Reserved
};

union SPI_SPISTS_REG {
    uint16_t  all;
    struct  SPI_SPISTS_BITS  bit;
};

struct SPI_SPIBRR_BITS {                // bits description
    uint16_t SPI_BIT_RATE:7;            // 6:0 SPI Bit Rate Control
    uint16_t rsvd1:9;                   // 15:7 Reserved
};

union SPI_SPIBRR_REG {
    uint16_t  all;
    struct  SPI_SPIBRR_BITS  bit;
};

struct SPI_SPIFFTX_BITS {               // bits description
    uint16_t TXFFIL:5;                  // 4:0 TXFIFO Interrupt Level
    uint16_t TXFFIENA:1;                // 5 TXFIFO Interrupt Enable
    uint16_t TXFFINTCLR:1;              // 6 TXFIFO Interrupt Clear
    uint16_t TXFFINT:1;                 // 7 TXFIFO Interrupt Flag
    uint16_t TXFFST:5;                  // 12:8 Transmit FIFO Status
    uint16_t TXFIFO:1;                  // 13 TXFIFO Reset
    uint16_t SPIFFENA:1;                // 14 FIFO Enhancements Enable
    uint16_t SPIRST:1;                  // 15 SPI Reset
};

union SPI_SPIFFTX_REG {
    uint16_t  all;
    struct  SPI_SPIFFTX_BITS  bit;
};

struct SPI_SPIFFRX_BITS {               // bits description
    uint16_t RXFFIL:5;                  // 4:0 RXFIFO Interrupt Level
    uint16_t RXFFIENA:1;                // 5 RXFIFO Interrupt Enable
    uint16_t RXFFINTCLR:1;              // 6 RXFIFO Interupt Clear
    uint16_t RXFFINT:1;                 // 7 RXFIFO Interrupt Flag
    uint16_t RXFFST:5;                  // 12:8 Receive FIFO Status
    uint16_t RXFIFORESET:1;             // 13 RXFIFO Reset
    uint16_t RXFFOVFCLR:1;              // 14 Receive FIFO Overflow Clear
    uint16_t RXFFOVF:1;                 // 15 Receive FIFO Overflow Flag
};

union SPI_SPIFFRX_REG {
    uint16_t  all;
    struct  SPI_SPIFFRX_BITS  bit;
};

struct SPI_SPIFFCT_BITS {               // bits description
    uint16_t TXDLY:8;                   // 7:0 FIFO Transmit Delay Bits
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union SPI_SPIFFCT_REG {
    uint16_t  all;
    struct  SPI_SPIFFCT_BITS  bit;
};

struct SPI_SPIPRI_BITS {                // bits description
    uint16_t TRIWIRE:1;                 // 0 3-wire mode select bit
    uint16_t PTEINV:1;                  // 1 SPIPTE inversion bit
    uint16_t rsvd1:2;                   // 3:2 Reserved
    uint16_t FREE:1;                    // 4 Free emulation mode
    uint16_t SOFT:1;                    // 5 Soft emulation mode
    uint16_t rsvd2:1;                   // 6 Reserved
    uint16_t rsvd3:9;                   // 15:7 Reserved
};

union SPI_SPIPRI_REG {
    uint16_t  all;
    struct  SPI_SPIPRI_BITS  bit;
};

struct SPI_REGS {
    union   SPI_SPICCR_REG                   SPICCR;                       // SPI Configuration Control Register
    union   SPI_SPICTL_REG                   SPICTL;                       // SPI Operation Control Register
    union   SPI_SPISTS_REG                   SPISTS;                       // SPI Status Register
    uint8_t                                  rsvd1[2];                     // Reserved
    union   SPI_SPIBRR_REG                   SPIBRR;                       // SPI Baud Rate Register
    uint8_t                                  rsvd2[2];                     // Reserved
    uint16_t                                 SPIRXEMU;                     // SPI Emulation Buffer Register
    uint16_t                                 SPIRXBUF;                     // SPI Serial Input Buffer Register
    uint16_t                                 SPITXBUF;                     // SPI Serial Output Buffer Register
    uint16_t                                 SPIDAT;                       // SPI Serial Data Register
    union   SPI_SPIFFTX_REG                  SPIFFTX;                      // SPI FIFO Transmit Register
    union   SPI_SPIFFRX_REG                  SPIFFRX;                      // SPI FIFO Receive Register
    union   SPI_SPIFFCT_REG                  SPIFFCT;                      // SPI FIFO Control Register
    uint8_t                                  rsvd3[4];                     // Reserved
    union   SPI_SPIPRI_REG                   SPIPRI;                       // SPI Priority Control Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
