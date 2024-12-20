//###########################################################################
//
// FILE:    hwbf_lin.h
//
// TITLE:   Definitions for the LIN registers.
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

#ifndef HWBF_LIN_H
#define HWBF_LIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// LIN Individual Register Bit Definitions:

struct LIN_SCIGCR0_BITS {               // bits description
    uint16_t RESET:1;                   // 0 LIN Module reset bit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_SCIGCR0_REG {
    uint32_t  all;
    struct  LIN_SCIGCR0_BITS  bit;
};

struct LIN_SCIGCR1_BITS {               // bits description
    uint16_t COMMMODE:1;                // 0 SCI/LIN communications mode bit
    uint16_t TIMINGMODE:1;              // 1 SCI timing mode bit. Should be set to 1 for SCI mode.
    uint16_t PARITYENA:1;               // 2 Parity enable
    uint16_t PARITY:1;                  // 3 SCI parity odd/even selection
    uint16_t STOP:1;                    // 4 SCI number of stop bits
    uint16_t CLK_COMMANDER:1;           // 5 LIN Commander/Responder selection and SCI clock enable
    uint16_t LINMODE:1;                 // 6 LIN Mode enable/disable
    uint16_t SWnRST:1;                  // 7 Software reset
    uint16_t SLEEP:1;                   // 8 SCI sleep (SCI compatibility mode)
    uint16_t ADAPT:1;                   // 9 Automatic baudrate adjustment control(LIN mode)
    uint16_t MBUFMODE:1;                // 10 Multi-buffer mode
    uint16_t CTYPE:1;                   // 11 Checksum type (LIN mode)
    uint16_t HGENCTRL:1;                // 12 Mask filtering comparison control (LIN mode)
    uint16_t STOPEXTFRAME:1;            // 13 Stop extended frame communication (LIN mode)
    uint16_t rsvd1:2;                   // 15:14 Reserved
    uint16_t LOOPBACK:1;                // 16 Digital loopback mode
    uint16_t CONT:1;                    // 17 Continue on suspend
    uint16_t rsvd2:6;                   // 23:18 Reserved
    uint16_t RXENA:1;                   // 24 Receive enable
    uint16_t TXENA:1;                   // 25 Transmit enable
    uint16_t rsvd3:6;                   // 31:26 Reserved
};

union LIN_SCIGCR1_REG {
    uint32_t  all;
    struct  LIN_SCIGCR1_BITS  bit;
};

struct LIN_SCIGCR2_BITS {               // bits description
    uint16_t POWERDOWN:1;               // 0 Low-power mode PowerDown bit
    uint16_t rsvd1:7;                   // 7:1 Reserved
    uint16_t GENWU:1;                   // 8 Generate Wakeup
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t SC:1;                      // 16 Send Checksum (LIN mode)
    uint16_t CC:1;                      // 17 Compare Checksum (LIN mode)
    uint16_t rsvd3:14;                  // 31:18 Reserved
};

union LIN_SCIGCR2_REG {
    uint32_t  all;
    struct  LIN_SCIGCR2_BITS  bit;
};

struct LIN_SCISETINT_BITS {             // bits description
    uint16_t SETBRKDTINT:1;             // 0 Set Break-detect Interrupt (SCI compatible mode)
    uint16_t SETWAKEUPINT:1;            // 1 Set Wake-up Interrupt
    uint16_t rsvd1:2;                   // 3:2 Reserved
    uint16_t SETTIMEOUTINT:1;           // 4 Set Timeout Interrupt (LIN only)
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t SETTOAWUSINT:1;            // 6 Set Timeout After Wakeup Signal Interrupt (LIN only)
    uint16_t SETTOA3WUSINT:1;           // 7 Set Timeout After 3 Wakeup Signals Interrupt (LIN only)
    uint16_t SETTXINT:1;                // 8 Set Transmitter Interrupt
    uint16_t SETRXINT:1;                // 9 Se Receiver Interrupt
    uint16_t rsvd3:3;                   // 12:10 Reserved
    uint16_t SETIDINT:1;                // 13 Set Identifier Interrupt (LIN only)
    uint16_t rsvd4:2;                   // 15:14 Reserved
    uint16_t SET_TX_DMA:1;              // 16 Set transmit DMA
    uint16_t SET_RX_DMA:1;              // 17 Set receiver DMA
    uint16_t SET_RX_DMA_ALL:1;          // 18 Set receiver DMA for Address & Data frames
    uint16_t rsvd5:5;                   // 23:19 Reserved
    uint16_t SETPEINT:1;                // 24 Set Parity Interrupt
    uint16_t SETOEINT:1;                // 25 Set Overrun-Error Interrupt
    uint16_t SETFEINT:1;                // 26 Set Framing-Error Interrupt
    uint16_t SETNREINT:1;               // 27 Set No-Response-Error Interrupt (LIN only)
    uint16_t SETISFEINT:1;              // 28 Set Inconsistent-Sync-Field-Error Interrupt (LIN only)
    uint16_t SETCEINT:1;                // 29 Set Checksum-error Interrupt (LIN only)
    uint16_t SETPBEINT:1;               // 30 Set Physical Bus Error Interrupt (LIN only)
    uint16_t SETBEINT:1;                // 31 Set Bit Error Interrupt (LIN only)
};

union LIN_SCISETINT_REG {
    uint32_t  all;
    struct  LIN_SCISETINT_BITS  bit;
};

struct LIN_SCICLEARINT_BITS {           // bits description
    uint16_t CLRBRKDTINT:1;             // 0 Clear Break-detect Interrupt (SCI compatible mode
    uint16_t CLRWAKEUPINT:1;            // 1 Clear Wake-up Interrupt
    uint16_t rsvd1:2;                   // 3:2 Reserved
    uint16_t CLRTIMEOUTINT:1;           // 4 Clear Timeout Interrupt (LIN only)
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t CLRTOAWUSINT:1;            // 6 Clear Timeout After Wakeup Signal Interrupt (LIN only)
    uint16_t CLRTOA3WUSINT:1;           // 7 Clear Timeout After 3 Wakeup Signals Interrupt (LIN only)
    uint16_t CLRTXINT:1;                // 8 Clear Transmitter Interrupt
    uint16_t CLRRXINT:1;                // 9 Clear Receiver Interrupt
    uint16_t rsvd3:3;                   // 12:10 Reserved
    uint16_t CLRIDINT:1;                // 13 Clear Identifier Interrupt (LIN only)
    uint16_t rsvd4:2;                   // 15:14 Reserved
    uint16_t CLRTXDMA:1;                // 16 Clear transmit DMA
    uint16_t CLRRXDMA:1;                // 17 Clear receiver DMA
    uint16_t rsvd5:1;                   // 18 Reserved
    uint16_t rsvd6:5;                   // 23:19 Reserved
    uint16_t CLRPEINT:1;                // 24 Clear Parity Interrupt
    uint16_t CLROEINT:1;                // 25 Clear Overrun-Error Interrupt
    uint16_t CLRFEINT:1;                // 26 Clear Framing-Error Interrupt
    uint16_t CLRNREINT:1;               // 27 Clear No-Response-Error Interrupt (LIN only)
    uint16_t CLRISFEINT:1;              // 28 Clear Inconsistent-Sync-Field-Error Interrupt (LIN only)
    uint16_t CLRCEINT:1;                // 29 Clear Checksum-error Interrupt (LIN only)
    uint16_t CLRPBEINT:1;               // 30 Clear Physical Bus Error Interrupt (LIN only)
    uint16_t CLRBEINT:1;                // 31 Clear Bit Error Interrupt (LIN only)
};

union LIN_SCICLEARINT_REG {
    uint32_t  all;
    struct  LIN_SCICLEARINT_BITS  bit;
};

struct LIN_SCISETINTLVL_BITS {          // bits description
    uint16_t SETBRKDTINTLVL:1;          // 0 Set Break-detect Interrupt Level (SCI compatible mode)
    uint16_t SETWAKEUPINTLVL:1;         // 1 Set Wake-up Interrupt Level
    uint16_t rsvd1:2;                   // 3:2 Reserved
    uint16_t SETTIMEOUTINTLVL:1;        // 4 Set Timeout Interrupt Level (LIN only)
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t SETTOAWUSINTLVL:1;         // 6 Set Timeout After Wakeup Signal Interrupt Level (LIN only)
    uint16_t SETTOA3WUSINTLVL:1;        // 7 Set Timeout After 3 Wakeup Signals Interrupt Level
    uint16_t SETTXINTLVL:1;             // 8 Set Transmitter Interrupt Level
    uint16_t SETRXINTOVO:1;             // 9 Receiver Interrupt Enable Level
    uint16_t rsvd3:3;                   // 12:10 Reserved
    uint16_t SETIDINTLVL:1;             // 13 Set Identifier Interrupt Level (LIN only)
    uint16_t rsvd4:2;                   // 15:14 Reserved
    uint16_t rsvd5:2;                   // 17:16 Reserved
    uint16_t rsvd6:1;                   // 18 Reserved
    uint16_t rsvd7:5;                   // 23:19 Reserved
    uint16_t SETPEINTLVL:1;             // 24 Set Parity Interrupt Level
    uint16_t SETOEINTLVL:1;             // 25 Set Overrun-Error Interrupt Level
    uint16_t SETFEINTLVL:1;             // 26 Set Framing-Error Interrupt Level
    uint16_t SETNREINTLVL:1;            // 27 Set No-Response-Error Interrupt Level (LIN only)
    uint16_t SETISFEINTLVL:1;           // 28 Set Inconsistent-Sync-Field-Error Interrupt Level
    uint16_t SETCEINTLVL:1;             // 29 Set Checksum-error Interrupt Level (LIN only)
    uint16_t SETPBEINTLVL:1;            // 30 Set Physical Bus Error Interrupt Level (LIN only)
    uint16_t SETBEINTLVL:1;             // 31 Set Bit Error Interrupt Level (LIN only)
};

union LIN_SCISETINTLVL_REG {
    uint32_t  all;
    struct  LIN_SCISETINTLVL_BITS  bit;
};

struct LIN_SCICLEARINTLVL_BITS {        // bits description
    uint16_t CLRBRKDTINTLVL:1;          // 0 Clear Break-detect Interrupt Level (SCI compatible mode)
    uint16_t CLRWAKEUPINTLVL:1;         // 1 Clear Wake-up Interrupt Level
    uint16_t rsvd1:2;                   // 3:2 Reserved
    uint16_t CLRTIMEOUTINTLVL:1;        // 4  Clear Timeout Interrupt Level (LIN only)
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t CLRTOAWUSINTLVL:1;         // 6 Clear Timeout After Wakeup Signal Interrupt Level (LIN only)
    uint16_t CLRTOA3WUSINTLVL:1;        // 7 Clear Timeout After 3 Wakeup Signals
    uint16_t CLRTXINTLVL:1;             // 8 Clear Transmitter Interrupt Level
    uint16_t CLRRXINTLVL:1;             // 9 Clear Receiver interrupt Level.
    uint16_t rsvd3:3;                   // 12:10 Reserved
    uint16_t CLRIDINTLVL:1;             // 13 Clear Identifier Interrupt Level (LIN only)
    uint16_t rsvd4:2;                   // 15:14 Reserved
    uint16_t rsvd5:2;                   // 17:16 Reserved
    uint16_t rsvd6:1;                   // 18 Reserved
    uint16_t rsvd7:5;                   // 23:19 Reserved
    uint16_t CLRPEINTLVL:1;             // 24 Clear Parity Interrupt Level
    uint16_t CLROEINTLVL:1;             // 25 Clear Overrun-Error Interrupt Level
    uint16_t CLRFEINTLVL:1;             // 26 Clear Framing-Error Interrupt Level
    uint16_t CLRNREINTLVL:1;            // 27 Clear No-Response-Error Interrupt Level (LIN only)
    uint16_t CLRISFEINTLVL:1;           // 28 Clear Inconsistent-Sync-Field-Error
    uint16_t CLRCEINTLVL:1;             // 29 Clear Checksum-error Interrupt Level (LIN only)
    uint16_t CLRPBEINTLVL:1;            // 30 Clear Physical Bus Error Interrupt Level (LIN only)
    uint16_t CLRBEINTLVL:1;             // 31 Clear Bit Error Interrupt Level (LIN only)
};

union LIN_SCICLEARINTLVL_REG {
    uint32_t  all;
    struct  LIN_SCICLEARINTLVL_BITS  bit;
};

struct LIN_SCIFLR_BITS {                // bits description
    uint16_t BRKDT:1;                   // 0 Break-detect Flag (SCI compatible mode)
    uint16_t WAKEUP:1;                  // 1 Wake-up Flag
    uint16_t IDLE:1;                    // 2 SCI receiver in idle state (SCI compatible mode)
    uint16_t BUSY:1;                    // 3 Busy Flag
    uint16_t TIMEOUT:1;                 // 4 LIN Bus IDLE timeout Flag (LIN only)
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t TOAWUS:1;                  // 6 Timeout After Wakeup Signal Flag (LIN only)
    uint16_t TOA3WUS:1;                 // 7 Timeout After 3 Wakeup Signals Flag (LIN only)
    uint16_t TXRDY:1;                   // 8 Transmitter Buffer Ready Flag
    uint16_t RXRDY:1;                   // 9 Receiver Buffer Ready Flag
    uint16_t TXWAKE:1;                  // 10 SCI Transmitter Wakeup Method Select
    uint16_t TXEMPTY:1;                 // 11 Transmitter Empty Flag
    uint16_t RXWAKE:1;                  // 12 Receiver Wakeup Detect Flag
    uint16_t IDTXFLAG:1;                // 13 Identifier On Transmit Flag (LIN only)
    uint16_t IDRXFLAG:1;                // 14 Identifier on Receive Flag
    uint16_t rsvd2:1;                   // 15 Reserved
    uint16_t rsvd3:8;                   // 23:16 Reserved
    uint16_t PE:1;                      // 24 Parity Error Flag
    uint16_t OE:1;                      // 25 Overrun Error Flag
    uint16_t FE:1;                      // 26 Framing Error Flag
    uint16_t NRE:1;                     // 27 No-Response Error Flag (LIN only)
    uint16_t ISFE:1;                    // 28 Inconsistent Sync Field Error Flag (LIN only)
    uint16_t CE:1;                      // 29 Checksum Error Flag (LIN only)
    uint16_t PBE:1;                     // 30 Physical Bus Error Flag (LIN only)
    uint16_t BE:1;                      // 31 Bit Error Flag (LIN only)
};

union LIN_SCIFLR_REG {
    uint32_t  all;
    struct  LIN_SCIFLR_BITS  bit;
};

struct LIN_SCIINTVECT0_BITS {           // bits description
    uint16_t INTVECT0:5;                // 4:0 LIN Module reset bit
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_SCIINTVECT0_REG {
    uint32_t  all;
    struct  LIN_SCIINTVECT0_BITS  bit;
};

struct LIN_SCIINTVECT1_BITS {           // bits description
    uint16_t INTVECT1:5;                // 4:0 LIN Module reset bit
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_SCIINTVECT1_REG {
    uint32_t  all;
    struct  LIN_SCIINTVECT1_BITS  bit;
};

struct LIN_SCIFORMAT_BITS {             // bits description
    uint16_t CHAR:3;                    // 2:0 Character Length Control Bits
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t LENGTH:3;                  // 18:16 Frame Length Control Bits
    uint16_t rsvd2:13;                  // 31:19 Reserved
};

union LIN_SCIFORMAT_REG {
    uint32_t  all;
    struct  LIN_SCIFORMAT_BITS  bit;
};

struct LIN_BRSR_BITS {                  // bits description
    uint16_t SCI_LIN_PSL:16;            // 15:0 24-Bit Integer Prescaler Select (Low Bits)
    uint16_t SCI_LIN_PSH:8;             // 23:16 24-Bit Integer Prescaler Select (High Bits)
    uint16_t M:4;                       // 27:24 M 4-bit Fractional Divider selection
    uint16_t U:3;                       // 30:28 U Superfractional divider Selection
    uint16_t rsvd1:1;                   // 31 Reserved
};

union LIN_BRSR_REG {
    uint32_t  all;
    struct  LIN_BRSR_BITS  bit;
};

struct LIN_SCIED_BITS {                 // bits description
    uint16_t ED:8;                      // 7:0 Receiver Emulation Data.
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_SCIED_REG {
    uint32_t  all;
    struct  LIN_SCIED_BITS  bit;
};

struct LIN_SCIRD_BITS {                 // bits description
    uint16_t RD:8;                      // 7:0 Received Data.
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_SCIRD_REG {
    uint32_t  all;
    struct  LIN_SCIRD_BITS  bit;
};

struct LIN_SCITD_BITS {                 // bits description
    uint16_t TD:8;                      // 7:0 Transmit data
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_SCITD_REG {
    uint32_t  all;
    struct  LIN_SCITD_BITS  bit;
};

struct LIN_SCIPIO0_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t RXFUNC:1;                  // 1 LINRX pin function
    uint16_t TXFUNC:1;                  // 2 LINTX pin function
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union LIN_SCIPIO0_REG {
    uint32_t  all;
    struct  LIN_SCIPIO0_BITS  bit;
};

struct LIN_SCIPIO2_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t RXIN:1;                    // 1 SCIRX pin value
    uint16_t TXIN:1;                    // 2 SCITX pin value
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union LIN_SCIPIO2_REG {
    uint32_t  all;
    struct  LIN_SCIPIO2_BITS  bit;
};

struct LIN_LINCOMP_BITS {               // bits description
    uint16_t SBREAK:3;                  // 2:0 Sync Break Extend
    uint16_t rsvd1:5;                   // 7:3 Reserved
    uint16_t SDEL:2;                    // 9:8 Sync Delimiter Compare
    uint16_t rsvd2:6;                   // 15:10 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union LIN_LINCOMP_REG {
    uint32_t  all;
    struct  LIN_LINCOMP_BITS  bit;
};

struct LIN_LINRD0_BITS {                // bits description
    uint16_t RD3:8;                     // 7:0 Receive Buffer 3
    uint16_t RD2:8;                     // 15:8 Receive Buffer 2
    uint16_t RD1:8;                     // 23:16 Receive Buffer 1
    uint16_t RD0:8;                     // 31:24 Receive Buffer 0
};

union LIN_LINRD0_REG {
    uint32_t  all;
    struct  LIN_LINRD0_BITS  bit;
};

struct LIN_LINRD1_BITS {                // bits description
    uint16_t RD7:8;                     // 7:0 Receive Buffer 3
    uint16_t RD6:8;                     // 15:8 Receive Buffer 2
    uint16_t RD5:8;                     // 23:16 Receive Buffer 1
    uint16_t RD4:8;                     // 31:24 Receive Buffer 0
};

union LIN_LINRD1_REG {
    uint32_t  all;
    struct  LIN_LINRD1_BITS  bit;
};

struct LIN_LINMASK_BITS {               // bits description
    uint16_t TXIDMASK:8;                // 7:0 TX ID Mask bits (LIN only)
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t RXIDMASK:8;                // 23:16 RX ID Mask bits (LIN only)
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union LIN_LINMASK_REG {
    uint32_t  all;
    struct  LIN_LINMASK_BITS  bit;
};

struct LIN_LINID_BITS {                 // bits description
    uint16_t IDBYTE:8;                  // 7:0 LIN message ID (LIN only)
    uint16_t IDRESPONDERTASKBYTE:8;     // 15:8 ID  Responder Task byte (LIN only)
    uint16_t RECEIVEDID:8;              // 23:16 Current Message ID (LIN only)
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union LIN_LINID_REG {
    uint32_t  all;
    struct  LIN_LINID_BITS  bit;
};

struct LIN_LINTD0_BITS {                // bits description
    uint16_t TD3:8;                     // 7:0 TRANSMIT Buffer 3
    uint16_t TD2:8;                     // 15:8 TRANSMIT Buffer 2
    uint16_t TD1:8;                     // 23:16 TRANSMIT Buffer 1
    uint16_t TD0:8;                     // 31:24 TRANSMIT Buffer 0
};

union LIN_LINTD0_REG {
    uint32_t  all;
    struct  LIN_LINTD0_BITS  bit;
};

struct LIN_LINTD1_BITS {                // bits description
    uint16_t TD7:8;                     // 7:0 TRANSMIT Buffer 7
    uint16_t TD6:8;                     // 15:8 TRANSMIT Buffer 6
    uint16_t TD5:8;                     // 23:16 TRANSMIT Buffer 5
    uint16_t TD4:8;                     // 31:24 TRANSMIT Buffer 4
};

union LIN_LINTD1_REG {
    uint32_t  all;
    struct  LIN_LINTD1_BITS  bit;
};

struct LIN_MBRSR_BITS {                 // bits description
    uint16_t MBR:13;                    // 12:0 Received Data.
    uint16_t rsvd1:3;                   // 15:13 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_MBRSR_REG {
    uint32_t  all;
    struct  LIN_MBRSR_BITS  bit;
};

struct LIN_IODFTCTRL_BITS {             // bits description
    uint16_t RXPENA:1;                  // 0 Analog Loopback Via Receive Pin Enable
    uint16_t LPBENA:1;                  // 1 Module Loopback Enable
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t IODFTENA:4;                // 11:8 IO DFT Enable Key
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t TXSHIFT:3;                 // 18:16 Transmit Delay Shift
    uint16_t PINSAMPLEMASK:2;           // 20:19 TX Pin Sample Mask
    uint16_t rsvd3:3;                   // 23:21 Reserved
    uint16_t BRKDTERRENA:1;             // 24 Break Detect Error Enable (SCI compatibility mode)
    uint16_t PERRENA:1;                 // 25 Parity Error Enable (SCI compatibility mode)
    uint16_t FERRENA:1;                 // 26 Frame Error Enable (SCI compatibility mode)
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t ISFERRENA:1;               // 28 Inconsistent Sync Field Error Enable (LIN mode)
    uint16_t CERRENA:1;                 // 29 Checksum Error Enable(LIN mode)
    uint16_t PBERRENA:1;                // 30 Physical Bus Error Enable (LIN mode)
    uint16_t BERRENA:1;                 // 31 Bit Error Enable (LIN mode)
};

union LIN_IODFTCTRL_REG {
    uint32_t  all;
    struct  LIN_IODFTCTRL_BITS  bit;
};

struct LIN_LIN_GLB_INT_EN_BITS {        // bits description
    uint16_t GLBINT0_EN:1;              // 0 Global Interrupt Enable for LIN INT0
    uint16_t GLBINT1_EN:1;              // 1 Global Interrupt Enable for LIN INT1
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_LIN_GLB_INT_EN_REG {
    uint32_t  all;
    struct  LIN_LIN_GLB_INT_EN_BITS  bit;
};

struct LIN_LIN_GLB_INT_FLG_BITS {       // bits description
    uint16_t INT0_FLG:1;                // 0 Global Interrupt Flag for LIN INT0
    uint16_t INT1_FLG:1;                // 1 Global Interrupt Flag for LIN INT1
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_LIN_GLB_INT_FLG_REG {
    uint32_t  all;
    struct  LIN_LIN_GLB_INT_FLG_BITS  bit;
};

struct LIN_LIN_GLB_INT_CLR_BITS {       // bits description
    uint16_t INT0_FLG_CLR:1;            // 0 Global Interrupt flag clear for LIN INT0
    uint16_t INT1_FLG_CLR:1;            // 1 Global Interrupt flag  clear for LIN INT1
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LIN_LIN_GLB_INT_CLR_REG {
    uint32_t  all;
    struct  LIN_LIN_GLB_INT_CLR_BITS  bit;
};

struct LIN_REGS {
    union   LIN_SCIGCR0_REG                  SCIGCR0;                      // Global Control Register 0
    union   LIN_SCIGCR1_REG                  SCIGCR1;                      // Global Control Register 1
    union   LIN_SCIGCR2_REG                  SCIGCR2;                      // Global Control Register 2
    union   LIN_SCISETINT_REG                SCISETINT;                    // Interrupt Enable Register
    union   LIN_SCICLEARINT_REG              SCICLEARINT;                  // Interrupt Disable Register
    union   LIN_SCISETINTLVL_REG             SCISETINTLVL;                 // Set Interrupt Level Register
    union   LIN_SCICLEARINTLVL_REG           SCICLEARINTLVL;               // Clear Interrupt Level Register
    union   LIN_SCIFLR_REG                   SCIFLR;                       // Flag Register
    union   LIN_SCIINTVECT0_REG              SCIINTVECT0;                  // Interrupt Vector Offset Register 0
    union   LIN_SCIINTVECT1_REG              SCIINTVECT1;                  // Interrupt Vector Offset Register 1
    union   LIN_SCIFORMAT_REG                SCIFORMAT;                    // Length Control Register
    union   LIN_BRSR_REG                     BRSR;                         // Baud Rate Selection Register
    union   LIN_SCIED_REG                    SCIED;                        // Emulation buffer Register
    union   LIN_SCIRD_REG                    SCIRD;                        // Receiver data buffer Register
    union   LIN_SCITD_REG                    SCITD;                        // Transmit data buffer Register
    union   LIN_SCIPIO0_REG                  SCIPIO0;                      // Pin control Register 0
    uint8_t                                  rsvd1[4];                     // Reserved
    union   LIN_SCIPIO2_REG                  SCIPIO2;                      // Pin control Register 2
    uint8_t                                  rsvd2[24];                    // Reserved
    union   LIN_LINCOMP_REG                  LINCOMP;                      // Compare register
    union   LIN_LINRD0_REG                   LINRD0;                       // Receive data register 0
    union   LIN_LINRD1_REG                   LINRD1;                       // Receive data register 1
    union   LIN_LINMASK_REG                  LINMASK;                      // Acceptance mask register
    union   LIN_LINID_REG                    LINID;                        // LIN ID Register
    union   LIN_LINTD0_REG                   LINTD0;                       // Transmit Data Register 0
    union   LIN_LINTD1_REG                   LINTD1;                       // Transmit Data Register 1
    union   LIN_MBRSR_REG                    MBRSR;                        // Maximum Baud Rate Selection Register
    uint8_t                                  rsvd3[16];                    // Reserved
    union   LIN_IODFTCTRL_REG                IODFTCTRL;                    // IODFT for LIN
    uint8_t                                  rsvd4[76];                    // Reserved
    union   LIN_LIN_GLB_INT_EN_REG           LIN_GLB_INT_EN;               // LIN Global Interrupt Enable Register
    union   LIN_LIN_GLB_INT_FLG_REG          LIN_GLB_INT_FLG;              // LIN Global Interrupt Flag Register
    union   LIN_LIN_GLB_INT_CLR_REG          LIN_GLB_INT_CLR;              // LIN Global Interrupt Clear Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
