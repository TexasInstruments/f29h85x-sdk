//###########################################################################
//
// FILE:    hwbf_uart.h
//
// TITLE:   Definitions for the UART registers.
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

#ifndef HWBF_UART_H
#define HWBF_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// UART Individual Register Bit Definitions:

struct UART_UARTDR_BITS {               // bits description
    uint16_t DATA:8;                    // 7:0 Data Transmitted or Received
    uint16_t FE:1;                      // 8 UART Framing Error
    uint16_t PE:1;                      // 9 UART Parity Error
    uint16_t BE:1;                      // 10 UART Break Error
    uint16_t OE:1;                      // 11 UART Overrun Error
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTDR_REG {
    uint32_t  all;
    struct  UART_UARTDR_BITS  bit;
};

struct UART_UARTRSR_BITS {              // bits description
    uint16_t FE:1;                      // 0 UART Framing Error
    uint16_t PE:1;                      // 1 UART Parity Error
    uint16_t BE:1;                      // 2 UART Break Error
    uint16_t OE:1;                      // 3 UART Overrun Error
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTRSR_REG {
    uint32_t  all;
    struct  UART_UARTRSR_BITS  bit;
};

struct UART_UARTFR_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t BUSY:1;                    // 3 UART Busy
    uint16_t RXFE:1;                    // 4 UART Receive FIFO Empty
    uint16_t TXFF:1;                    // 5 UART Transmit FIFO Full
    uint16_t RXFF:1;                    // 6 UART Receive FIFO Full
    uint16_t TXFE:1;                    // 7 UART Transmit FIFO Empty
    uint16_t rsvd4:1;                   // 8 Reserved
    uint16_t rsvd5:7;                   // 15:9 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union UART_UARTFR_REG {
    uint32_t  all;
    struct  UART_UARTFR_BITS  bit;
};

struct UART_UARTILPR_BITS {             // bits description
    uint16_t ILPDVSR:8;                 // 7:0 IrDA Low-Power Divisor
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTILPR_REG {
    uint32_t  all;
    struct  UART_UARTILPR_BITS  bit;
};

struct UART_UARTIBRD_BITS {             // bits description
    uint16_t DIVINT:16;                 // 15:0 Integer Baud-Rate Divisor
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union UART_UARTIBRD_REG {
    uint32_t  all;
    struct  UART_UARTIBRD_BITS  bit;
};

struct UART_UARTFBRD_BITS {             // bits description
    uint16_t DIVFRAC:6;                 // 5:0 Fractional Baud-Rate Divisor
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTFBRD_REG {
    uint32_t  all;
    struct  UART_UARTFBRD_BITS  bit;
};

struct UART_UARTLCRH_BITS {             // bits description
    uint16_t BRK:1;                     // 0 UART Send Break
    uint16_t PEN:1;                     // 1 UART Parity Enable
    uint16_t EPS:1;                     // 2 UART Even Parity Select
    uint16_t STP2:1;                    // 3 UART Two Stop Bits Select
    uint16_t FEN:1;                     // 4 UART Enable FIFOs
    uint16_t WLEN:2;                    // 6:5 UART Word Length
    uint16_t SPS:1;                     // 7 UART Stick Parity Select
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTLCRH_REG {
    uint32_t  all;
    struct  UART_UARTLCRH_BITS  bit;
};

struct UART_UARTCTL_BITS {              // bits description
    uint16_t UARTEN:1;                  // 0 UART Enable
    uint16_t SIREN:1;                   // 1 UART SIR Enable
    uint16_t SIRLP:1;                   // 2 UART SIR Low-Power Mode
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t EOT:1;                     // 4 End of Transmission
    uint16_t HSE:1;                     // 5 High-Speed Enable
    uint16_t rsvd2:1;                   // 6 Reserved
    uint16_t LBE:1;                     // 7 UART Loop Back Enable
    uint16_t TXE:1;                     // 8 UART Transmit Enable
    uint16_t RXE:1;                     // 9 UART Receive Enable
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:2;                   // 13:12 Reserved
    uint16_t rsvd6:1;                   // 14 Reserved
    uint16_t rsvd7:1;                   // 15 Reserved
    uint16_t rsvd8:16;                  // 31:16 Reserved
};

union UART_UARTCTL_REG {
    uint32_t  all;
    struct  UART_UARTCTL_BITS  bit;
};

struct UART_UARTIFLS_BITS {             // bits description
    uint16_t TXIFLSEL:3;                // 2:0 UART Transmit Interrupt FIFO Level Select
    uint16_t RXIFLSEL:3;                // 5:3 UART Receive Interrupt FIFO Level Select
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTIFLS_REG {
    uint32_t  all;
    struct  UART_UARTIFLS_BITS  bit;
};

struct UART_UARTIM_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t RXIM:1;                    // 4 UART Receive Interrupt Mask
    uint16_t TXIM:1;                    // 5 UART Transmit Interrupt Mask
    uint16_t RTIM:1;                    // 6 UART Receive Time-Out Interrupt Mask
    uint16_t FEIM:1;                    // 7 UART Framing Error Interrupt Mask
    uint16_t PEIM:1;                    // 8 UART Parity Error Interrupt Mask
    uint16_t BEIM:1;                    // 9 UART Break Error Interrupt Mask
    uint16_t OEIM:1;                    // 10 UART Overrun Error Interrupt Mask
    uint16_t rsvd5:1;                   // 11 Reserved
    uint16_t _9BITIM:1;                 // 12 9-Bit Mode Interrupt Mask
    uint16_t rsvd6:3;                   // 15:13 Reserved
    uint16_t DMARXIM:1;                 // 16 Receive DMA Interrupt Mask
    uint16_t DMATXIM:1;                 // 17 Transmit DMA Interrupt Mask
    uint16_t rsvd7:14;                  // 31:18 Reserved
};

union UART_UARTIM_REG {
    uint32_t  all;
    struct  UART_UARTIM_BITS  bit;
};

struct UART_UARTRIS_BITS {              // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t RXRIS:1;                   // 4 UART Receive Raw Interrupt Status
    uint16_t TXRIS:1;                   // 5 UART Transmit Raw Interrupt Status
    uint16_t RTRIS:1;                   // 6 UART Receive Time-Out Raw Interrupt Status
    uint16_t FERIS:1;                   // 7 UART Framing Error Raw Interrupt Status
    uint16_t PERIS:1;                   // 8 UART Parity Error Raw Interrupt Status
    uint16_t BERIS:1;                   // 9 UART Break Error Raw Interrupt Status
    uint16_t OERIS:1;                   // 10 UART Overrun Error Raw Interrupt Status
    uint16_t rsvd5:1;                   // 11 Reserved
    uint16_t _9BITRIS:1;                // 12 9-Bit Mode Raw Interrupt Status
    uint16_t rsvd6:3;                   // 15:13 Reserved
    uint16_t DMARXRIS:1;                // 16 Receive DMA Raw Interrupt Status
    uint16_t DMATXRIS:1;                // 17 Transmit DMA Raw Interrupt Status
    uint16_t rsvd7:14;                  // 31:18 Reserved
};

union UART_UARTRIS_REG {
    uint32_t  all;
    struct  UART_UARTRIS_BITS  bit;
};

struct UART_UARTMIS_BITS {              // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t RXMIS:1;                   // 4 UART Receive Masked Interrupt Status
    uint16_t TXMIS:1;                   // 5 UART Transmit Masked Interrupt Status
    uint16_t RTMIS:1;                   // 6 UART Receive Time-Out Masked Interrupt Status
    uint16_t FEMIS:1;                   // 7 UART Framing Error Masked Interrupt Status
    uint16_t PEMIS:1;                   // 8 UART Parity Error Masked Interrupt Status
    uint16_t BEMIS:1;                   // 9 UART Break Error Masked Interrupt Status
    uint16_t OEMIS:1;                   // 10 UART Overrun Error Masked Interrupt Status
    uint16_t rsvd5:1;                   // 11 Reserved
    uint16_t _9BITMIS:1;                // 12 9-Bit Mode Masked Interrupt Status
    uint16_t rsvd6:3;                   // 15:13 Reserved
    uint16_t DMARXMIS:1;                // 16 Receive DMA Masked Interrupt Status
    uint16_t DMATXMIS:1;                // 17 Transmit DMA Masked Interrupt Status
    uint16_t rsvd7:14;                  // 31:18 Reserved
};

union UART_UARTMIS_REG {
    uint32_t  all;
    struct  UART_UARTMIS_BITS  bit;
};

struct UART_UARTICR_BITS {              // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t RXIC:1;                    // 4 Receive Interrupt Clear
    uint16_t TXIC:1;                    // 5 Transmit Interrupt Clear
    uint16_t RTIC:1;                    // 6 Receive Time-Out Interrupt Clear
    uint16_t FEIC:1;                    // 7 Framing Error Interrupt Clear
    uint16_t PEIC:1;                    // 8 Parity Error Interrupt Clear
    uint16_t BEIC:1;                    // 9 Break Error Interrupt Clear
    uint16_t OEIC:1;                    // 10 Overrun Error Interrupt Clear
    uint16_t EOTIC:1;                   // 11 End of Transmission Interrupt Clear
    uint16_t _9BITIC:1;                 // 12 9-Bit Mode Interrupt Clear
    uint16_t rsvd5:3;                   // 15:13 Reserved
    uint16_t DMARXIC:1;                 // 16 Receive DMA Interrupt Clear
    uint16_t DMATXIC:1;                 // 17 Transmit DMA Interrupt Clear
    uint16_t rsvd6:14;                  // 31:18 Reserved
};

union UART_UARTICR_REG {
    uint32_t  all;
    struct  UART_UARTICR_BITS  bit;
};

struct UART_UARTDMACTL_BITS {           // bits description
    uint16_t RXDMAE:1;                  // 0 Receive DMA Enable
    uint16_t TXDMAE:1;                  // 1 Transmit DMA Enable
    uint16_t DMAERR:1;                  // 2 DMA on Error
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTDMACTL_REG {
    uint32_t  all;
    struct  UART_UARTDMACTL_BITS  bit;
};

struct UART_UART_GLB_INT_FLG_BITS {     // bits description
    uint16_t INT_FLG:1;                 // 0 Global Interrupt Flag for UART Interrupt
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UART_GLB_INT_FLG_REG {
    uint32_t  all;
    struct  UART_UART_GLB_INT_FLG_BITS  bit;
};

struct UART_UART_GLB_INT_CLR_BITS {     // bits description
    uint16_t INT_FLG_CLR:1;             // 0 Global Interrupt flag clear for UART Interrupt
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UART_GLB_INT_CLR_REG {
    uint32_t  all;
    struct  UART_UART_GLB_INT_CLR_BITS  bit;
};

struct UART_UART9BITADDR_BITS {         // bits description
    uint16_t ADDR:8;                    // 7:0 Self Address for 9-Bit Mode
    uint16_t rsvd1:7;                   // 14:8 Reserved
    uint16_t _9BITEN:1;                 // 15 Enable 9-Bit Mode
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UART9BITADDR_REG {
    uint32_t  all;
    struct  UART_UART9BITADDR_BITS  bit;
};

struct UART_UART9BITAMASK_BITS {        // bits description
    uint16_t MASK:8;                    // 7:0 Self Address Mask for 9-Bit Mode
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UART9BITAMASK_REG {
    uint32_t  all;
    struct  UART_UART9BITAMASK_BITS  bit;
};

struct UART_UARTPP_BITS {               // bits description
    uint16_t SC:1;                      // 0 Smart Card Support
    uint16_t NB:1;                      // 1 9-Bit Support
    uint16_t MS:1;                      // 2 Modem Support
    uint16_t MSE:1;                     // 3 Modem Support Extended
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPP_REG {
    uint32_t  all;
    struct  UART_UARTPP_BITS  bit;
};

struct UART_UARTPeriphID4_BITS {        // bits description
    uint16_t PID4:8;                    // 7:0 UART Peripheral ID Register [7:0]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPeriphID4_REG {
    uint32_t  all;
    struct  UART_UARTPeriphID4_BITS  bit;
};

struct UART_UARTPeriphID5_BITS {        // bits description
    uint16_t PID5:8;                    // 7:0 UART Peripheral ID Register [15:8]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPeriphID5_REG {
    uint32_t  all;
    struct  UART_UARTPeriphID5_BITS  bit;
};

struct UART_UARTPeriphID6_BITS {        // bits description
    uint16_t PID6:8;                    // 7:0 UART Peripheral ID Register [23:16]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPeriphID6_REG {
    uint32_t  all;
    struct  UART_UARTPeriphID6_BITS  bit;
};

struct UART_UARTPeriphID7_BITS {        // bits description
    uint16_t PID7:8;                    // 7:0 UART Peripheral ID Register [31:24]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPeriphID7_REG {
    uint32_t  all;
    struct  UART_UARTPeriphID7_BITS  bit;
};

struct UART_UARTPeriphID0_BITS {        // bits description
    uint16_t PID0:8;                    // 7:0 UART Peripheral ID Register [7:0]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPeriphID0_REG {
    uint32_t  all;
    struct  UART_UARTPeriphID0_BITS  bit;
};

struct UART_UARTPeriphID1_BITS {        // bits description
    uint16_t PID1:8;                    // 7:0 UART Peripheral ID Register [15:8]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPeriphID1_REG {
    uint32_t  all;
    struct  UART_UARTPeriphID1_BITS  bit;
};

struct UART_UARTPeriphID2_BITS {        // bits description
    uint16_t PID2:8;                    // 7:0 UART Peripheral ID Register [23:16]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPeriphID2_REG {
    uint32_t  all;
    struct  UART_UARTPeriphID2_BITS  bit;
};

struct UART_UARTPeriphID3_BITS {        // bits description
    uint16_t PID3:8;                    // 7:0 UART Peripheral ID Register [31:24]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPeriphID3_REG {
    uint32_t  all;
    struct  UART_UARTPeriphID3_BITS  bit;
};

struct UART_UARTPCellID0_BITS {         // bits description
    uint16_t CID0:8;                    // 7:0 UART PrimeCell ID Register [7:0]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPCellID0_REG {
    uint32_t  all;
    struct  UART_UARTPCellID0_BITS  bit;
};

struct UART_UARTPCellID1_BITS {         // bits description
    uint16_t CID1:8;                    // 7:0 UART PrimeCell ID Register [15:8]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPCellID1_REG {
    uint32_t  all;
    struct  UART_UARTPCellID1_BITS  bit;
};

struct UART_UARTPCellID2_BITS {         // bits description
    uint16_t CID2:8;                    // 7:0 UART PrimeCell ID Register [23:16]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPCellID2_REG {
    uint32_t  all;
    struct  UART_UARTPCellID2_BITS  bit;
};

struct UART_UARTPCellID3_BITS {         // bits description
    uint16_t CID3:8;                    // 7:0 UART PrimeCell ID Register [31:24]
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTPCellID3_REG {
    uint32_t  all;
    struct  UART_UARTPCellID3_BITS  bit;
};

struct UART_REGS {
    union   UART_UARTDR_REG                  UARTDR;                       // UART Data
    union   UART_UARTRSR_REG                 UARTRSR;                      // UART Receive Status/Error Clear
    uint8_t                                  rsvd1[16];                    // Reserved
    union   UART_UARTFR_REG                  UARTFR;                       // UART Flag
    uint8_t                                  rsvd2[4];                     // Reserved
    union   UART_UARTILPR_REG                UARTILPR;                     // UART IrDA Low-Power Register
    union   UART_UARTIBRD_REG                UARTIBRD;                     // UART Integer Baud-Rate Divisor
    union   UART_UARTFBRD_REG                UARTFBRD;                     // UART Fractional Baud-Rate Divisor
    union   UART_UARTLCRH_REG                UARTLCRH;                     // UART Line Control
    union   UART_UARTCTL_REG                 UARTCTL;                      // UART Control
    union   UART_UARTIFLS_REG                UARTIFLS;                     // UART Interrupt FIFO Level Select
    union   UART_UARTIM_REG                  UARTIM;                       // UART Interrupt Mask
    union   UART_UARTRIS_REG                 UARTRIS;                      // UART Raw Interrupt Status
    union   UART_UARTMIS_REG                 UARTMIS;                      // UART Masked Interrupt Status
    union   UART_UARTICR_REG                 UARTICR;                      // UART Interrupt Clear
    union   UART_UARTDMACTL_REG              UARTDMACTL;                   // UART DMA Control
    uint8_t                                  rsvd3[56];                    // Reserved
    union   UART_UART_GLB_INT_FLG_REG        UART_GLB_INT_FLG;             // UART Global Interrupt Flag Register
    union   UART_UART_GLB_INT_CLR_REG        UART_GLB_INT_CLR;             // UART Global Interrupt Clear Register
    uint8_t                                  rsvd4[24];                    // Reserved
    union   UART_UART9BITADDR_REG            UART9BITADDR;                 // UART 9-Bit Self Address
    union   UART_UART9BITAMASK_REG           UART9BITAMASK;                // UART 9-Bit Self Address Mask
    uint8_t                                  rsvd5[3860];                  // Reserved
    union   UART_UARTPP_REG                  UARTPP;                       // UART Peripheral Properties
    uint8_t                                  rsvd6[12];                    // Reserved
    union   UART_UARTPeriphID4_REG           UARTPeriphID4;                // UART Peripheral Identification 4
    union   UART_UARTPeriphID5_REG           UARTPeriphID5;                // UART Peripheral Identification 5
    union   UART_UARTPeriphID6_REG           UARTPeriphID6;                // UART Peripheral Identification 6
    union   UART_UARTPeriphID7_REG           UARTPeriphID7;                // UART Peripheral Identification 7
    union   UART_UARTPeriphID0_REG           UARTPeriphID0;                // UART Peripheral Identification 0
    union   UART_UARTPeriphID1_REG           UARTPeriphID1;                // UART Peripheral Identification 1
    union   UART_UARTPeriphID2_REG           UARTPeriphID2;                // UART Peripheral Identification 2
    union   UART_UARTPeriphID3_REG           UARTPeriphID3;                // UART Peripheral Identification 3
    union   UART_UARTPCellID0_REG            UARTPCellID0;                 // UART PrimeCell Identification 0
    union   UART_UARTPCellID1_REG            UARTPCellID1;                 // UART PrimeCell Identification 1
    union   UART_UARTPCellID2_REG            UARTPCellID2;                 // UART PrimeCell Identification 2
    union   UART_UARTPCellID3_REG            UARTPCellID3;                 // UART PrimeCell Identification 3
};

struct UART_UARTECR_BITS {              // bits description
    uint16_t DATA:8;                    // 7:0 Error Clear
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union UART_UARTECR_REG {
    uint32_t  all;
    struct  UART_UARTECR_BITS  bit;
};

struct UART_REGS_WRITE {
    uint8_t                                  rsvd1[4];                     // Reserved
    union   UART_UARTECR_REG                 UARTECR;                      // UART Error Clear
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
