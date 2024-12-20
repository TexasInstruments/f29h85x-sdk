//###########################################################################
//
// FILE:    hwbf_i2c.h
//
// TITLE:   Definitions for the I2C registers.
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

#ifndef HWBF_I2C_H
#define HWBF_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// I2C Individual Register Bit Definitions:

struct I2C_I2COAR_BITS {                // bits description
    uint16_t OAR:10;                    // 9:0 I2C Own address
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union I2C_I2COAR_REG {
    uint16_t  all;
    struct  I2C_I2COAR_BITS  bit;
};

struct I2C_I2CIER_BITS {                // bits description
    uint16_t ARBL:1;                    // 0 Arbitration-lost interrupt enable
    uint16_t NACK:1;                    // 1 No-acknowledgment interrupt enable
    uint16_t ARDY:1;                    // 2 Register-access-ready interrupt enable
    uint16_t RRDY:1;                    // 3 Receive-data-ready interrupt enable
    uint16_t XRDY:1;                    // 4 Transmit-data-ready interrupt enable
    uint16_t SCD:1;                     // 5 Stop condition detected interrupt enable
    uint16_t AAT:1;                     // 6 Addressed as TARGET interrupt enable
    uint16_t rsvd1:8;                   // 14:7 Reserved
    uint16_t SCL_ECS:1;                 // 15 SCL Extended Automatic Clock Stretch interrupt enable
};

union I2C_I2CIER_REG {
    uint16_t  all;
    struct  I2C_I2CIER_BITS  bit;
};

struct I2C_I2CSTR_BITS {                // bits description
    uint16_t ARBL:1;                    // 0 Arbitration-lost interrupt flag bit
    uint16_t NACK:1;                    // 1 No-acknowledgment interrupt flag bit.
    uint16_t ARDY:1;                    // 2 Register-access-ready interrupt flag bit
    uint16_t RRDY:1;                    // 3 Receive-data-ready interrupt flag bit.
    uint16_t XRDY:1;                    // 4 Transmit-data-ready interrupt flag bit.
    uint16_t SCD:1;                     // 5 Stop condition detected bit.
    uint16_t BYTESENT:1;                // 6 Byte transmit over indication
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t AD0:1;                     // 8 Address 0 bits
    uint16_t AAT:1;                     // 9 Addressed-as-TARGET bit
    uint16_t XSMT:1;                    // 10 Transmit shift register empty bit.
    uint16_t RSFULL:1;                  // 11 Receive shift register full bit.
    uint16_t BB:1;                      // 12 Bus busy bit.
    uint16_t NACKSNT:1;                 // 13 NACK sent bit.
    uint16_t TDIR:1;                    // 14 TARGET direction bit
    uint16_t SCL_ECS:1;                 // 15 SCL Extended Automatic Clock Stretch Status
};

union I2C_I2CSTR_REG {
    uint16_t  all;
    struct  I2C_I2CSTR_BITS  bit;
};

struct I2C_I2CDRR_BITS {                // bits description
    uint16_t DATA:8;                    // 7:0 Receive data
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union I2C_I2CDRR_REG {
    uint16_t  all;
    struct  I2C_I2CDRR_BITS  bit;
};

struct I2C_I2CTAR_BITS {                // bits description
    uint16_t TAR:10;                    // 9:0 TARGET Address
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union I2C_I2CTAR_REG {
    uint16_t  all;
    struct  I2C_I2CTAR_BITS  bit;
};

struct I2C_I2CDXR_BITS {                // bits description
    uint16_t DATA:8;                    // 7:0 Transmit data
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union I2C_I2CDXR_REG {
    uint16_t  all;
    struct  I2C_I2CDXR_BITS  bit;
};

struct I2C_I2CMDR_BITS {                // bits description
    uint16_t BC:3;                      // 2:0 Bit count bits.
    uint16_t FDF:1;                     // 3 Free Data Format
    uint16_t STB:1;                     // 4 START Byte Mode
    uint16_t IRS:1;                     // 5 I2C Module Reset
    uint16_t DLB:1;                     // 6 Digital Loopback Mode
    uint16_t RM:1;                      // 7 Repeat Mode
    uint16_t XA:1;                      // 8 Expanded Address Mode
    uint16_t TRX:1;                     // 9 Transmitter Mode
    uint16_t CNT:1;                     // 10 CONTROLLER Mode
    uint16_t STP:1;                     // 11 STOP Condition
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t STT:1;                     // 13 START condition bit
    uint16_t FREE:1;                    // 14 Debug Action
    uint16_t NACKMOD:1;                 // 15 NACK mode bit
};

union I2C_I2CMDR_REG {
    uint16_t  all;
    struct  I2C_I2CMDR_BITS  bit;
};

struct I2C_I2CISRC_BITS {               // bits description
    uint16_t INTCODE:4;                 // 3:0 Interrupt code bits.
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t WRITE_ZEROS:4;             // 11:8 Always write all 0s to this field
    uint16_t rsvd2:4;                   // 15:12 Reserved
};

union I2C_I2CISRC_REG {
    uint16_t  all;
    struct  I2C_I2CISRC_BITS  bit;
};

struct I2C_I2CEMDR_BITS {               // bits description
    uint16_t BC:1;                      // 0 Backwards compatibility mode
    uint16_t FCM:1;                     // 1 Forward Compatibility for Tx behav in Type1
    uint16_t ECS:1;                     // 2 Extended Automatic Clock Stretching mode
    uint16_t MCS:1;                     // 3 Manual Clock Stretching mode (Clock Override)
    uint16_t SCLKEY:4;                  // 7:4 Key to enable SCL (Clock Override)
    uint16_t NACK_CM:1;                 // 8 NACK Compatibility mode
    uint16_t rsvd1:6;                   // 14:9 Reserved
    uint16_t rsvd2:1;                   // 15 Reserved
};

union I2C_I2CEMDR_REG {
    uint16_t  all;
    struct  I2C_I2CEMDR_BITS  bit;
};

struct I2C_I2CPSC_BITS {                // bits description
    uint16_t IPSC:8;                    // 7:0 I2C Prescaler Divide Down
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union I2C_I2CPSC_REG {
    uint16_t  all;
    struct  I2C_I2CPSC_BITS  bit;
};

struct I2C_I2CFFTX_BITS {               // bits description
    uint16_t TXFFIL:5;                  // 4:0 Transmit FIFO Interrupt Level
    uint16_t TXFFIENA:1;                // 5 Transmit FIFO Interrupt Enable
    uint16_t TXFFINTCLR:1;              // 6 Transmit FIFO Interrupt Flag Clear
    uint16_t TXFFINT:1;                 // 7 Transmit FIFO Interrupt Flag
    uint16_t TXFFST:5;                  // 12:8 Transmit FIFO Status
    uint16_t TXFFRST:1;                 // 13 Transmit FIFO Reset
    uint16_t I2CFFEN:1;                 // 14 Transmit FIFO Enable
    uint16_t rsvd1:1;                   // 15 Reserved
};

union I2C_I2CFFTX_REG {
    uint16_t  all;
    struct  I2C_I2CFFTX_BITS  bit;
};

struct I2C_I2CFFRX_BITS {               // bits description
    uint16_t RXFFIL:5;                  // 4:0 Receive FIFO Interrupt Level
    uint16_t RXFFIENA:1;                // 5 Receive FIFO Interrupt Enable
    uint16_t RXFFINTCLR:1;              // 6 Receive FIFO Interrupt Flag Clear
    uint16_t RXFFINT:1;                 // 7 Receive FIFO Interrupt Flag
    uint16_t RXFFST:5;                  // 12:8 Receive FIFO Status
    uint16_t RXFFRST:1;                 // 13 Receive FIFO Reset
    uint16_t rsvd1:2;                   // 15:14 Reserved
};

union I2C_I2CFFRX_REG {
    uint16_t  all;
    struct  I2C_I2CFFRX_BITS  bit;
};

struct I2C_REGS {
    union   I2C_I2COAR_REG                   I2COAR;                       // I2C Own address
    union   I2C_I2CIER_REG                   I2CIER;                       // I2C Interrupt Enable
    union   I2C_I2CSTR_REG                   I2CSTR;                       // I2C Status
    uint16_t                                 I2CCLKL;                      // I2C Clock low-time divider
    uint16_t                                 I2CCLKH;                      // I2C Clock high-time divider
    uint16_t                                 I2CCNT;                       // I2C Data count
    union   I2C_I2CDRR_REG                   I2CDRR;                       // I2C Data receive
    union   I2C_I2CTAR_REG                   I2CTAR;                       // I2C TARGET address
    union   I2C_I2CDXR_REG                   I2CDXR;                       // I2C Data Transmit
    union   I2C_I2CMDR_REG                   I2CMDR;                       // I2C Mode
    union   I2C_I2CISRC_REG                  I2CISRC;                      // I2C Interrupt Source
    union   I2C_I2CEMDR_REG                  I2CEMDR;                      // I2C Extended Mode
    union   I2C_I2CPSC_REG                   I2CPSC;                       // I2C Prescaler
    uint8_t                                  rsvd1[38];                    // Reserved
    union   I2C_I2CFFTX_REG                  I2CFFTX;                      // I2C FIFO Transmit
    union   I2C_I2CFFRX_REG                  I2CFFRX;                      // I2C FIFO Receive
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
