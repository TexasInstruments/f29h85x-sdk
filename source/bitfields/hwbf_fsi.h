//###########################################################################
//
// FILE:    hwbf_fsi.h
//
// TITLE:   Definitions for the FSI registers.
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

#ifndef HWBF_FSI_H
#define HWBF_FSI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// FSI Individual Register Bit Definitions:

struct FSI_TX_MAIN_CTRL_BITS {          // bits description
    uint16_t CORE_RST:1;                // 0 Transmitter Main Core Reset
    uint16_t FLUSH:1;                   // 1 Flush Operation Start
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t KEY:8;                     // 15:8 Write Key
};

union FSI_TX_MAIN_CTRL_REG {
    uint16_t  all;
    struct  FSI_TX_MAIN_CTRL_BITS  bit;
};

struct FSI_TX_CLK_CTRL_BITS {           // bits description
    uint16_t CLK_RST:1;                 // 0 Soft Reset for the Clock Divider
    uint16_t CLK_EN:1;                  // 1 Clock Divider Enable
    uint16_t PRESCALE_VAL:8;            // 9:2 Prescale value
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union FSI_TX_CLK_CTRL_REG {
    uint16_t  all;
    struct  FSI_TX_CLK_CTRL_BITS  bit;
};

struct FSI_TX_OPER_CTRL_LO_BITS {       // bits description
    uint16_t DATA_WIDTH:2;              // 1:0 Transmit Data width
    uint16_t SPI_MODE:1;                // 2 SPI Mode Select
    uint16_t START_MODE:3;              // 5:3 Transmission Start Mode Select
    uint16_t SW_CRC:1;                  // 6 CRC Source Select
    uint16_t PING_TO_MODE:1;            // 7 Ping Counter Reset Mode Select
    uint16_t SEL_PLLCLK:1;              // 8 Input Clock Select
    uint16_t TDM_ENABLE:1;              // 9 Transmit TDM Mode Enable
    uint16_t SEL_TDM_IN:1;              // 10 Input TDM Port Select
    uint16_t rsvd1:5;                   // 15:11 Reserved
};

union FSI_TX_OPER_CTRL_LO_REG {
    uint16_t  all;
    struct  FSI_TX_OPER_CTRL_LO_BITS  bit;
};

struct FSI_TX_OPER_CTRL_HI_BITS {       // bits description
    uint16_t rsvd1:5;                   // 4:0 Reserved
    uint16_t FORCE_ERR:1;               // 5 Error Frame Force
    uint16_t ECC_SEL:1;                 // 6 ECC Data Width Select
    uint16_t EXT_TRIG_SEL:7;            // 13:7 External Trigger Select
    uint16_t rsvd2:2;                   // 15:14 Reserved
};

union FSI_TX_OPER_CTRL_HI_REG {
    uint16_t  all;
    struct  FSI_TX_OPER_CTRL_HI_BITS  bit;
};

struct FSI_TX_FRAME_CTRL_BITS {         // bits description
    uint16_t FRAME_TYPE:4;              // 3:0 Transmit Frame Type
    uint16_t N_WORDS:4;                 // 7:4 Number of Words to be Transmitted
    uint16_t rsvd1:7;                   // 14:8 Reserved
    uint16_t START:1;                   // 15 Start Transmission
};

union FSI_TX_FRAME_CTRL_REG {
    uint16_t  all;
    struct  FSI_TX_FRAME_CTRL_BITS  bit;
};

struct FSI_TX_FRAME_TAG_UDATA_BITS {    // bits description
    uint16_t FRAME_TAG:4;               // 3:0 Frame Tag
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t USER_DATA:8;               // 15:8 User Data
};

union FSI_TX_FRAME_TAG_UDATA_REG {
    uint16_t  all;
    struct  FSI_TX_FRAME_TAG_UDATA_BITS  bit;
};

struct FSI_TX_BUF_PTR_LOAD_BITS {       // bits description
    uint16_t BUF_PTR_LOAD:4;            // 3:0 Buffer Pointer Force Load
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union FSI_TX_BUF_PTR_LOAD_REG {
    uint16_t  all;
    struct  FSI_TX_BUF_PTR_LOAD_BITS  bit;
};

struct FSI_TX_BUF_PTR_STS_BITS {        // bits description
    uint16_t CURR_BUF_PTR:4;            // 3:0 Current Buffer Pointer Index
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t CURR_WORD_CNT:5;           // 12:8 Remaining Words in Buffer
    uint16_t rsvd2:3;                   // 15:13 Reserved
};

union FSI_TX_BUF_PTR_STS_REG {
    uint16_t  all;
    struct  FSI_TX_BUF_PTR_STS_BITS  bit;
};

struct FSI_TX_PING_CTRL_BITS {          // bits description
    uint16_t CNT_RST:1;                 // 0 Ping Counter Reset
    uint16_t TIMER_EN:1;                // 1 Ping Counter Enable
    uint16_t EXT_TRIG_EN:1;             // 2 External Trigger Enable
    uint16_t EXT_TRIG_SEL:7;            // 9:3 External Trigger Select
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union FSI_TX_PING_CTRL_REG {
    uint16_t  all;
    struct  FSI_TX_PING_CTRL_BITS  bit;
};

struct FSI_TX_PING_TAG_BITS {           // bits description
    uint16_t TAG:4;                     // 3:0 Ping Frame Tag
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union FSI_TX_PING_TAG_REG {
    uint16_t  all;
    struct  FSI_TX_PING_TAG_BITS  bit;
};

struct FSI_TX_INT_CTRL_BITS {           // bits description
    uint16_t INT1_EN_FRAME_DONE:1;      // 0 Enable Frame Done Interrupt to INT1
    uint16_t INT1_EN_BUF_UNDERRUN:1;    // 1 Enable Buffer Underrun Interrupt to INT1
    uint16_t INT1_EN_BUF_OVERRUN:1;     // 2 Enable Buffer Overrun Interrupt to INT1
    uint16_t INT1_EN_PING_TO:1;         // 3 Enable Ping Timer Interrupt to INT1
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t INT2_EN_FRAME_DONE:1;      // 8 Enable Frame Done Interrupt to INT2
    uint16_t INT2_EN_BUF_UNDERRUN:1;    // 9 Enable Buffer Underrun Interrupt to INT2
    uint16_t INT2_EN_BUF_OVERRUN:1;     // 10 Enable Buffer Overrun Interrupt to INT2
    uint16_t INT2_EN_PING_TO:1;         // 11 Enable Ping Timer Interrupt to INT2
    uint16_t rsvd2:4;                   // 15:12 Reserved
};

union FSI_TX_INT_CTRL_REG {
    uint16_t  all;
    struct  FSI_TX_INT_CTRL_BITS  bit;
};

struct FSI_TX_DMA_CTRL_BITS {           // bits description
    uint16_t DMA_EVT_EN:1;              // 0 DMA Event Enable
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union FSI_TX_DMA_CTRL_REG {
    uint16_t  all;
    struct  FSI_TX_DMA_CTRL_BITS  bit;
};

struct FSI_TX_LOCK_CTRL_BITS {          // bits description
    uint16_t LOCK:1;                    // 0 Control Register Lock Enable
    uint16_t rsvd1:7;                   // 7:1 Reserved
    uint16_t KEY:8;                     // 15:8 Write Key
};

union FSI_TX_LOCK_CTRL_REG {
    uint16_t  all;
    struct  FSI_TX_LOCK_CTRL_BITS  bit;
};

struct FSI_TX_EVT_STS_BITS {            // bits description
    uint16_t FRAME_DONE:1;              // 0 Frame Done Flag
    uint16_t BUF_UNDERRUN:1;            // 1 Buffer Underrun Flag
    uint16_t BUF_OVERRUN:1;             // 2 Buffer Overrun Flag
    uint16_t PING_TRIGGERED:1;          // 3 Ping Frame Triggered Flag
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union FSI_TX_EVT_STS_REG {
    uint16_t  all;
    struct  FSI_TX_EVT_STS_BITS  bit;
};

struct FSI_TX_EVT_CLR_BITS {            // bits description
    uint16_t FRAME_DONE:1;              // 0 Frame Done Flag Clear
    uint16_t BUF_UNDERRUN:1;            // 1 Buffer Underrun Flag Clear
    uint16_t BUF_OVERRUN:1;             // 2 Buffer Overrun Flag Clear
    uint16_t PING_TRIGGERED:1;          // 3 Ping Frame Triggered Flag Clear
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union FSI_TX_EVT_CLR_REG {
    uint16_t  all;
    struct  FSI_TX_EVT_CLR_BITS  bit;
};

struct FSI_TX_EVT_FRC_BITS {            // bits description
    uint16_t FRAME_DONE:1;              // 0 Frame Done Flag Force
    uint16_t BUF_UNDERRUN:1;            // 1 Buffer Underrun Flag Force
    uint16_t BUF_OVERRUN:1;             // 2 Buffer Overrun Flag Force
    uint16_t PING_TRIGGERED:1;          // 3 Ping Frame Triggered Flag Force
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union FSI_TX_EVT_FRC_REG {
    uint16_t  all;
    struct  FSI_TX_EVT_FRC_BITS  bit;
};

struct FSI_TX_USER_CRC_BITS {           // bits description
    uint16_t USER_CRC:8;                // 7:0 User-defined CRC
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union FSI_TX_USER_CRC_REG {
    uint16_t  all;
    struct  FSI_TX_USER_CRC_BITS  bit;
};

struct FSI_TX_ECC_DATA_BITS {           // bits description
    uint16_t DATA_LOW:16;               // 15:0 ECC Data Lower 16 Bits
    uint16_t DATA_HIGH:16;              // 31:16 ECC Data Upper 16 Bits
};

union FSI_TX_ECC_DATA_REG {
    uint32_t  all;
    struct  FSI_TX_ECC_DATA_BITS  bit;
};

struct FSI_TX_ECC_VAL_BITS {            // bits description
    uint16_t ECC_VAL:7;                 // 6:0 Computed ECC Value
    uint16_t rsvd1:9;                   // 15:7 Reserved
};

union FSI_TX_ECC_VAL_REG {
    uint16_t  all;
    struct  FSI_TX_ECC_VAL_BITS  bit;
};

struct FSI_TX_DLYLINE_CTRL_BITS {       // bits description
    uint16_t TXCLK_DLY:5;               // 4:0 Delay Line Tap Select for TXCLK
    uint16_t TXD0_DLY:5;                // 9:5 Delay Line Tap Select for TXD0
    uint16_t TXD1_DLY:5;                // 14:10 Delay Line Tap Select for TXD1
    uint16_t rsvd1:1;                   // 15 Reserved
};

union FSI_TX_DLYLINE_CTRL_REG {
    uint16_t  all;
    struct  FSI_TX_DLYLINE_CTRL_BITS  bit;
};

struct FSI_TX_REGS {
    union   FSI_TX_MAIN_CTRL_REG             TX_MAIN_CTRL;                 // Transmit main control register
    uint8_t                                  rsvd1[2];                     // Reserved
    union   FSI_TX_CLK_CTRL_REG              TX_CLK_CTRL;                  // Transmit clock control register
    uint8_t                                  rsvd2[2];                     // Reserved
    union   FSI_TX_OPER_CTRL_LO_REG          TX_OPER_CTRL_LO;              // Transmit operation control register low
    union   FSI_TX_OPER_CTRL_HI_REG          TX_OPER_CTRL_HI;              // Transmit operation control register high
    union   FSI_TX_FRAME_CTRL_REG            TX_FRAME_CTRL;                // Transmit frame control register
    union   FSI_TX_FRAME_TAG_UDATA_REG       TX_FRAME_TAG_UDATA;           // Transmit frame tag and user data register
    union   FSI_TX_BUF_PTR_LOAD_REG          TX_BUF_PTR_LOAD;              // Transmit buffer pointer control load register
    union   FSI_TX_BUF_PTR_STS_REG           TX_BUF_PTR_STS;               // Transmit buffer pointer control status register
    union   FSI_TX_PING_CTRL_REG             TX_PING_CTRL;                 // Transmit ping control register
    union   FSI_TX_PING_TAG_REG              TX_PING_TAG;                  // Transmit ping tag register
    uint32_t                                 TX_PING_TO_REF;               // Transmit ping timeout counter reference
    uint32_t                                 TX_PING_TO_CNT;               // Transmit ping timeout current count
    union   FSI_TX_INT_CTRL_REG              TX_INT_CTRL;                  // Transmit interrupt event control register
    union   FSI_TX_DMA_CTRL_REG              TX_DMA_CTRL;                  // Transmit DMA event control register
    union   FSI_TX_LOCK_CTRL_REG             TX_LOCK_CTRL;                 // Transmit lock control register
    uint8_t                                  rsvd3[2];                     // Reserved
    union   FSI_TX_EVT_STS_REG               TX_EVT_STS;                   // Transmit event and error status flag register
    uint8_t                                  rsvd4[2];                     // Reserved
    union   FSI_TX_EVT_CLR_REG               TX_EVT_CLR;                   // Transmit event and error clear register
    union   FSI_TX_EVT_FRC_REG               TX_EVT_FRC;                   // Transmit event and error flag force register
    union   FSI_TX_USER_CRC_REG              TX_USER_CRC;                  // Transmit user-defined CRC register
    uint8_t                                  rsvd5[14];                    // Reserved
    union   FSI_TX_ECC_DATA_REG              TX_ECC_DATA;                  // Transmit ECC data register
    union   FSI_TX_ECC_VAL_REG               TX_ECC_VAL;                   // Transmit ECC value register
    uint8_t                                  rsvd6[2];                     // Reserved
    union   FSI_TX_DLYLINE_CTRL_REG          TX_DLYLINE_CTRL;              // Transmit delay Line control register
    uint8_t                                  rsvd7[54];                    // Reserved
    uint16_t                                 TX_BUF_BASE[16];              // Base address for transmit buffer
};

struct FSI_RX_MAIN_CTRL_BITS {          // bits description
    uint16_t CORE_RST:1;                // 0 Receiver Main Core Reset
    uint16_t INT_LOOPBACK:1;            // 1 Internal Loopback Enable
    uint16_t SPI_PAIRING:1;             // 2 Clock Pairing for SPI-like Behaviour
    uint16_t INPUT_ISOLATE:1;           // 3 ISOLATE Input signals
    uint16_t DATA_FILTER_EN:1;          // 4 Data Filter Enable
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint16_t KEY:8;                     // 15:8 Write Key
};

union FSI_RX_MAIN_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_MAIN_CTRL_BITS  bit;
};

struct FSI_RX_OPER_CTRL_BITS {          // bits description
    uint16_t DATA_WIDTH:2;              // 1:0 Receive Data Width Select
    uint16_t SPI_MODE:1;                // 2 SPI Mode Enable
    uint16_t N_WORDS:4;                 // 6:3 Number of Words to be Received
    uint16_t ECC_SEL:1;                 // 7 ECC Data Width Select
    uint16_t PING_WD_RST_MODE:1;        // 8 Ping Watchdog Timeout Mode Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union FSI_RX_OPER_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_OPER_CTRL_BITS  bit;
};

struct FSI_RX_FRAME_INFO_BITS {         // bits description
    uint16_t FRAME_TYPE:4;              // 3:0 Received Frame Type
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union FSI_RX_FRAME_INFO_REG {
    uint16_t  all;
    struct  FSI_RX_FRAME_INFO_BITS  bit;
};

struct FSI_RX_FRAME_TAG_UDATA_BITS {    // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t FRAME_TAG:4;               // 4:1 Received Frame Tag
    uint16_t rsvd2:3;                   // 7:5 Reserved
    uint16_t USER_DATA:8;               // 15:8 Received User Data
};

union FSI_RX_FRAME_TAG_UDATA_REG {
    uint16_t  all;
    struct  FSI_RX_FRAME_TAG_UDATA_BITS  bit;
};

struct FSI_RX_DMA_CTRL_BITS {           // bits description
    uint16_t DMA_EVT_EN:1;              // 0 DMA Event Enable
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union FSI_RX_DMA_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_DMA_CTRL_BITS  bit;
};

struct FSI_RX_EVT_STS_BITS {            // bits description
    uint16_t PING_WD_TO:1;              // 0 Ping Watchdog Timeout Flag
    uint16_t FRAME_WD_TO:1;             // 1 Frame Watchdog Timeout Flag.
    uint16_t CRC_ERR:1;                 // 2 CRC Error Flag
    uint16_t TYPE_ERR:1;                // 3 Frame Type Error Flag
    uint16_t EOF_ERR:1;                 // 4 End-of-Frame Error Flag
    uint16_t BUF_OVERRUN:1;             // 5 Receive Buffer Overrun Flag
    uint16_t FRAME_DONE:1;              // 6 Frame Done Flag
    uint16_t BUF_UNDERRUN:1;            // 7 Receive Buffer Underrun Flag
    uint16_t ERR_FRAME:1;               // 8 Error Frame Received Flag
    uint16_t PING_FRAME:1;              // 9 Ping Frame Received Flag
    uint16_t FRAME_OVERRUN:1;           // 10 Frame Overrun Flag
    uint16_t DATA_FRAME:1;              // 11 Data Frame Received Flag
    uint16_t PING_TAG_MATCH:1;          // 12 Ping Tag Match Flag
    uint16_t DATA_TAG_MATCH:1;          // 13 Data Tag Match Flag
    uint16_t ERROR_TAG_MATCH:1;         // 14 Error Tag Match Flag
    uint16_t rsvd1:1;                   // 15 Reserved
};

union FSI_RX_EVT_STS_REG {
    uint16_t  all;
    struct  FSI_RX_EVT_STS_BITS  bit;
};

struct FSI_RX_CRC_INFO_BITS {           // bits description
    uint16_t RX_CRC:8;                  // 7:0 Received CRC Value
    uint16_t CALC_CRC:8;                // 15:8 Hardware Calculated CRC
};

union FSI_RX_CRC_INFO_REG {
    uint16_t  all;
    struct  FSI_RX_CRC_INFO_BITS  bit;
};

struct FSI_RX_EVT_CLR_BITS {            // bits description
    uint16_t PING_WD_TO:1;              // 0 Ping Watchdog Timeout Flag Clear
    uint16_t FRAME_WD_TO:1;             // 1 Frame Watchdog Timeout Flag Clear
    uint16_t CRC_ERR:1;                 // 2 CRC Error Flag Clear
    uint16_t TYPE_ERR:1;                // 3 Frame Type Error Flag Clear
    uint16_t EOF_ERR:1;                 // 4 End-of-Frame Error Flag Clear
    uint16_t BUF_OVERRUN:1;             // 5 Receive Buffer Overrun Flag Clear
    uint16_t FRAME_DONE:1;              // 6 Frame Done Flag Clear
    uint16_t BUF_UNDERRUN:1;            // 7 Receive Buffer Underrun Flag Clear
    uint16_t ERR_FRAME:1;               // 8 Error Frame Received Flag Clear
    uint16_t PING_FRAME:1;              // 9 PING Frame Received Flag Clear
    uint16_t FRAME_OVERRUN:1;           // 10 Frame Overrun Flag Clear
    uint16_t DATA_FRAME:1;              // 11 Data Frame Received Flag Clear
    uint16_t PING_TAG_MATCH:1;          // 12 Ping Tag Match Flag Clear
    uint16_t DATA_TAG_MATCH:1;          // 13 Data Tag Match Flag Clear
    uint16_t ERROR_TAG_MATCH:1;         // 14 Error Tag Match Flag Clear
    uint16_t rsvd1:1;                   // 15 Reserved
};

union FSI_RX_EVT_CLR_REG {
    uint16_t  all;
    struct  FSI_RX_EVT_CLR_BITS  bit;
};

struct FSI_RX_EVT_FRC_BITS {            // bits description
    uint16_t PING_WD_TO:1;              // 0 Ping Watchdog Timeout Flag Force
    uint16_t FRAME_WD_TO:1;             // 1 Frame Watchdog Timeout Flag Force
    uint16_t CRC_ERR:1;                 // 2 CRC Error Flag Force
    uint16_t TYPE_ERR:1;                // 3 Frame Type Error Flag Force
    uint16_t EOF_ERR:1;                 // 4 End-of-Frame Error Flag Force
    uint16_t BUF_OVERRUN:1;             // 5 Receive Buffer Overrun Flag Force
    uint16_t FRAME_DONE:1;              // 6 Frame Done Flag Force
    uint16_t BUF_UNDERRUN:1;            // 7 Receive Buffer Underrun Flag Force
    uint16_t ERR_FRAME:1;               // 8 Error Frame Received Flag Force
    uint16_t PING_FRAME:1;              // 9 Ping Frame Received Flag Force
    uint16_t FRAME_OVERRUN:1;           // 10 Frame Overrun Flag Force
    uint16_t DATA_FRAME:1;              // 11 Data Frame Received Flag Force
    uint16_t PING_TAG_MATCH:1;          // 12 Ping Tag Match Flag Force
    uint16_t DATA_TAG_MATCH:1;          // 13 Data Tag Match Flag Force
    uint16_t ERROR_TAG_MATCH:1;         // 14 Error Tag Match Flag Force
    uint16_t rsvd1:1;                   // 15 Reserved
};

union FSI_RX_EVT_FRC_REG {
    uint16_t  all;
    struct  FSI_RX_EVT_FRC_BITS  bit;
};

struct FSI_RX_BUF_PTR_LOAD_BITS {       // bits description
    uint16_t BUF_PTR_LOAD:4;            // 3:0 Load value for receive buffer pointer
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union FSI_RX_BUF_PTR_LOAD_REG {
    uint16_t  all;
    struct  FSI_RX_BUF_PTR_LOAD_BITS  bit;
};

struct FSI_RX_BUF_PTR_STS_BITS {        // bits description
    uint16_t CURR_BUF_PTR:4;            // 3:0 Current Buffer Pointer Index
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t CURR_WORD_CNT:5;           // 12:8 Available Words in Buffer
    uint16_t rsvd2:3;                   // 15:13 Reserved
};

union FSI_RX_BUF_PTR_STS_REG {
    uint16_t  all;
    struct  FSI_RX_BUF_PTR_STS_BITS  bit;
};

struct FSI_RX_FRAME_WD_CTRL_BITS {      // bits description
    uint16_t FRAME_WD_CNT_RST:1;        // 0 Frame Watchdog Counter Reset
    uint16_t FRAME_WD_EN:1;             // 1 Frame Watchdog Counter Enable
    uint16_t rsvd1:14;                  // 15:2 Reserved
};

union FSI_RX_FRAME_WD_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_FRAME_WD_CTRL_BITS  bit;
};

struct FSI_RX_PING_WD_CTRL_BITS {       // bits description
    uint16_t PING_WD_RST:1;             // 0 Ping Watchdog Counter Reset
    uint16_t PING_WD_EN:1;              // 1 Ping Watchdog Counter Enable
    uint16_t rsvd1:14;                  // 15:2 Reserved
};

union FSI_RX_PING_WD_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_PING_WD_CTRL_BITS  bit;
};

struct FSI_RX_PING_TAG_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t PING_TAG:4;                // 4:1 Ping Frame Tag
    uint16_t rsvd2:11;                  // 15:5 Reserved
};

union FSI_RX_PING_TAG_REG {
    uint16_t  all;
    struct  FSI_RX_PING_TAG_BITS  bit;
};

struct FSI_RX_INT1_CTRL_BITS {          // bits description
    uint16_t INT1_EN_PING_WD_TO:1;      // 0 Enable Ping Watchdog Timeout Interrupt to INT1
    uint16_t INT1_EN_FRAME_WD_TO:1;     // 1 Enable Frame Watchdog Timeout Interrupt to INT1
    uint16_t INT1_EN_CRC_ERR:1;         // 2 Enable CRC Error Interrupt to INT1
    uint16_t INT1_EN_TYPE_ERR:1;        // 3 Enable Frame Type Error Interrupt to INT1
    uint16_t INT1_EN_EOF_ERR:1;         // 4 Enable End-of-Frame Error Interrupt to INT1
    uint16_t INT1_EN_OVERRUN:1;         // 5 Enable Receive Buffer Overrun Interrupt to INT1
    uint16_t INT1_EN_FRAME_DONE:1;      // 6 Enable Frame Done Interrupt to INT1
    uint16_t INT1_EN_UNDERRUN:1;        // 7 Enable Buffer Underrun Interrupt to INT1
    uint16_t INT1_EN_ERR_FRAME:1;       // 8 Enable Error Frame Received Interrupt to INT1
    uint16_t INT1_EN_PING_FRAME:1;      // 9 Enable Ping Frame Received Interrupt to INT1
    uint16_t INT1_EN_FRAME_OVERRUN:1;   // 10 Enable Frame Overrun Interrupt to INT1
    uint16_t INT1_EN_DATA_FRAME:1;      // 11 Enable Data Frame Received Interrupt to INT1
    uint16_t INT1_EN_PING_TAG_MATCH:1;  // 12 Enable Ping Frame Tag Matched Interrupt to INT1
    uint16_t INT1_EN_DATA_TAG_MATCH:1;  // 13 Enable Data Frame Tag Matched Interrupt to INT1
    uint16_t INT1_EN_ERROR_TAG_MATCH:1; // 14 Enable Error Frame Tag Matched Interrupt to INT1
    uint16_t rsvd1:1;                   // 15 Reserved
};

union FSI_RX_INT1_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_INT1_CTRL_BITS  bit;
};

struct FSI_RX_INT2_CTRL_BITS {          // bits description
    uint16_t INT2_EN_PING_WD_TO:1;      // 0 Enable Ping Watchdog Timeout Interrupt to INT2
    uint16_t INT2_EN_FRAME_WD_TO:1;     // 1 Enable Frame Watchdog Timeout Interrupt to INT2
    uint16_t INT2_EN_CRC_ERR:1;         // 2 Enable CRC Errror Interrupt to INT2
    uint16_t INT2_EN_TYPE_ERR:1;        // 3 Enable Frame Type Error Interrupt to INT2
    uint16_t INT2_EN_EOF_ERR:1;         // 4 Enable End-of-Frame Error Interrupt to INT2
    uint16_t INT2_EN_OVERRUN:1;         // 5 Enable Buffer Overrun Interrupt to INT2
    uint16_t INT2_EN_FRAME_DONE:1;      // 6 Enable Frame Done Interrupt to INT2
    uint16_t INT2_EN_UNDERRUN:1;        // 7 Enable Buffer Underrun Interrupt to INT2
    uint16_t INT2_EN_ERR_FRAME:1;       // 8 Enable Error Frame Received Interrupt to INT2
    uint16_t INT2_EN_PING_FRAME:1;      // 9 Enable Ping Frame Received Interrupt to INT2
    uint16_t INT2_EN_FRAME_OVERRUN:1;   // 10 Enable Frame Overrun Interrupt to INT2
    uint16_t INT2_EN_DATA_FRAME:1;      // 11 Enable Data Frame Received Interrupt to INT2
    uint16_t INT2_EN_PING_TAG_MATCH:1;  // 12 Enable Ping Frame Tag Matched Interrupt to INT2
    uint16_t INT2_EN_DATA_TAG_MATCH:1;  // 13 Enable Data Frame Tag Matched Interrupt to INT2
    uint16_t INT2_EN_ERROR_TAG_MATCH:1; // 14 Enable Error Frame Tag Matched Interrupt to INT2
    uint16_t rsvd1:1;                   // 15 Reserved
};

union FSI_RX_INT2_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_INT2_CTRL_BITS  bit;
};

struct FSI_RX_LOCK_CTRL_BITS {          // bits description
    uint16_t LOCK:1;                    // 0 Control Register Lock Enable
    uint16_t rsvd1:7;                   // 7:1 Reserved
    uint16_t KEY:8;                     // 15:8 Write Key
};

union FSI_RX_LOCK_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_LOCK_CTRL_BITS  bit;
};

struct FSI_RX_ECC_DATA_BITS {           // bits description
    uint16_t DATA_LOW:16;               // 15:0 ECC Data Lower 16 Bits
    uint16_t DATA_HIGH:16;              // 31:16 ECC Data Upper 16 Bits
};

union FSI_RX_ECC_DATA_REG {
    uint32_t  all;
    struct  FSI_RX_ECC_DATA_BITS  bit;
};

struct FSI_RX_ECC_VAL_BITS {            // bits description
    uint16_t ECC_VAL:7;                 // 6:0 Computed ECC Value
    uint16_t rsvd1:9;                   // 15:7 Reserved
};

union FSI_RX_ECC_VAL_REG {
    uint16_t  all;
    struct  FSI_RX_ECC_VAL_BITS  bit;
};

struct FSI_RX_ECC_LOG_BITS {            // bits description
    uint16_t SBE:1;                     // 0 Single Bit Error Detected
    uint16_t MBE:1;                     // 1 Multiple Bit Errors Detected
    uint16_t rsvd1:14;                  // 15:2 Reserved
};

union FSI_RX_ECC_LOG_REG {
    uint16_t  all;
    struct  FSI_RX_ECC_LOG_BITS  bit;
};

struct FSI_RX_FRAME_TAG_CMP_BITS {      // bits description
    uint16_t TAG_REF:4;                 // 3:0 Frame Tag Reference
    uint16_t TAG_MASK:4;                // 7:4 Frame Tag Mask
    uint16_t CMP_EN:1;                  // 8 Frame Tag Compare Enable
    uint16_t BROADCAST_EN:1;            // 9 Broadcast Enable
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union FSI_RX_FRAME_TAG_CMP_REG {
    uint16_t  all;
    struct  FSI_RX_FRAME_TAG_CMP_BITS  bit;
};

struct FSI_RX_PING_TAG_CMP_BITS {       // bits description
    uint16_t TAG_REF:4;                 // 3:0 Ping Tag Reference
    uint16_t TAG_MASK:4;                // 7:4 Ping Tag Mask
    uint16_t CMP_EN:1;                  // 8 Ping Tag Compare Enable
    uint16_t BROADCAST_EN:1;            // 9 Broadcast Enable
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union FSI_RX_PING_TAG_CMP_REG {
    uint16_t  all;
    struct  FSI_RX_PING_TAG_CMP_BITS  bit;
};

struct FSI_RX_TRIG_CTRL_0_BITS {        // bits description
    uint16_t TRIG_EN:1;                 // 0 Enable Trigger Function
    uint16_t TRIG_SEL:4;                // 4:1 Input Select for Trigger
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint32_t RX_TRIG_DLY:24;            // 31:8 Delay for Trigger generation
};

union FSI_RX_TRIG_CTRL_0_REG {
    uint32_t  all;
    struct  FSI_RX_TRIG_CTRL_0_BITS  bit;
};

struct FSI_RX_TRIG_WIDTH_0_BITS {       // bits description
    uint16_t RX_TRIG_WIDTH:16;          // 15:0 Output Pulse Width
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union FSI_RX_TRIG_WIDTH_0_REG {
    uint32_t  all;
    struct  FSI_RX_TRIG_WIDTH_0_BITS  bit;
};

struct FSI_RX_DLYLINE_CTRL_BITS {       // bits description
    uint16_t RXCLK_DLY:5;               // 4:0 Delay Line Tap Select for RXCLK
    uint16_t RXD0_DLY:5;                // 9:5 Delay Line Tap Select for RXD0
    uint16_t RXD1_DLY:5;                // 14:10 Delay Line Tap Select for RXD1
    uint16_t rsvd1:1;                   // 15 Reserved
};

union FSI_RX_DLYLINE_CTRL_REG {
    uint16_t  all;
    struct  FSI_RX_DLYLINE_CTRL_BITS  bit;
};

struct FSI_RX_TRIG_CTRL_1_BITS {        // bits description
    uint16_t TRIG_EN:1;                 // 0 Enable Trigger Function
    uint16_t TRIG_SEL:4;                // 4:1 Input Select for Trigger
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint32_t RX_TRIG_DLY:24;            // 31:8 Delay for Trigger generation
};

union FSI_RX_TRIG_CTRL_1_REG {
    uint32_t  all;
    struct  FSI_RX_TRIG_CTRL_1_BITS  bit;
};

struct FSI_RX_TRIG_CTRL_2_BITS {        // bits description
    uint16_t TRIG_EN:1;                 // 0 Enable Trigger Function
    uint16_t TRIG_SEL:4;                // 4:1 Input Select for Trigger
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint32_t RX_TRIG_DLY:24;            // 31:8 Delay for Trigger generation
};

union FSI_RX_TRIG_CTRL_2_REG {
    uint32_t  all;
    struct  FSI_RX_TRIG_CTRL_2_BITS  bit;
};

struct FSI_RX_TRIG_CTRL_3_BITS {        // bits description
    uint16_t TRIG_EN:1;                 // 0 Enable Trigger Function
    uint16_t TRIG_SEL:4;                // 4:1 Input Select for Trigger
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint32_t RX_TRIG_DLY:24;            // 31:8 Delay for Trigger generation
};

union FSI_RX_TRIG_CTRL_3_REG {
    uint32_t  all;
    struct  FSI_RX_TRIG_CTRL_3_BITS  bit;
};

struct FSI_RX_VIS_1_BITS {              // bits description
    uint16_t rsvd1:3;                   // 2:0 Reserved
    uint16_t RX_CORE_STS:1;             // 3 Receiver Core Status
    uint16_t rsvd2:12;                  // 15:4 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union FSI_RX_VIS_1_REG {
    uint32_t  all;
    struct  FSI_RX_VIS_1_BITS  bit;
};

struct FSI_RX_UDATA_FILTER_BITS {       // bits description
    uint16_t UDATA_REF:8;               // 7:0 UserData reference value
    uint16_t UDATA_MASK:8;              // 15:8 UserData mask  value
};

union FSI_RX_UDATA_FILTER_REG {
    uint16_t  all;
    struct  FSI_RX_UDATA_FILTER_BITS  bit;
};

struct FSI_RX_REGS {
    union   FSI_RX_MAIN_CTRL_REG             RX_MAIN_CTRL;                 // Receive main control register
    uint8_t                                  rsvd1[6];                     // Reserved
    union   FSI_RX_OPER_CTRL_REG             RX_OPER_CTRL;                 // Receive operation control register
    uint8_t                                  rsvd2[2];                     // Reserved
    union   FSI_RX_FRAME_INFO_REG            RX_FRAME_INFO;                // Receive frame control register
    union   FSI_RX_FRAME_TAG_UDATA_REG       RX_FRAME_TAG_UDATA;           // Receive frame tag and user data register
    union   FSI_RX_DMA_CTRL_REG              RX_DMA_CTRL;                  // Receive DMA event control register
    uint8_t                                  rsvd3[2];                     // Reserved
    union   FSI_RX_EVT_STS_REG               RX_EVT_STS;                   // Receive event and error status flag register
    union   FSI_RX_CRC_INFO_REG              RX_CRC_INFO;                  // Receive CRC info of received and computed CRC
    union   FSI_RX_EVT_CLR_REG               RX_EVT_CLR;                   // Receive event and error clear register
    union   FSI_RX_EVT_FRC_REG               RX_EVT_FRC;                   // Receive event and error flag force register
    union   FSI_RX_BUF_PTR_LOAD_REG          RX_BUF_PTR_LOAD;              // Receive buffer pointer load register
    union   FSI_RX_BUF_PTR_STS_REG           RX_BUF_PTR_STS;               // Receive buffer pointer status register
    union   FSI_RX_FRAME_WD_CTRL_REG         RX_FRAME_WD_CTRL;             // Receive frame watchdog control register
    uint8_t                                  rsvd4[2];                     // Reserved
    uint32_t                                 RX_FRAME_WD_REF;              // Receive frame watchdog counter reference
    uint32_t                                 RX_FRAME_WD_CNT;              // Receive frame watchdog current count
    union   FSI_RX_PING_WD_CTRL_REG          RX_PING_WD_CTRL;              // Receive ping watchdog control register
    union   FSI_RX_PING_TAG_REG              RX_PING_TAG;                  // Receive ping tag register
    uint32_t                                 RX_PING_WD_REF;               // Receive ping watchdog counter reference
    uint32_t                                 RX_PING_WD_CNT;               // Receive pingwatchdog current count
    union   FSI_RX_INT1_CTRL_REG             RX_INT1_CTRL;                 // Receive interrupt control register for RX_INT1
    union   FSI_RX_INT2_CTRL_REG             RX_INT2_CTRL;                 // Receive interrupt control register for RX_INT2
    union   FSI_RX_LOCK_CTRL_REG             RX_LOCK_CTRL;                 // Receive lock control register
    uint8_t                                  rsvd5[2];                     // Reserved
    union   FSI_RX_ECC_DATA_REG              RX_ECC_DATA;                  // Receive ECC data register
    union   FSI_RX_ECC_VAL_REG               RX_ECC_VAL;                   // Receive ECC value register
    uint8_t                                  rsvd6[2];                     // Reserved
    uint32_t                                 RX_ECC_SEC_DATA;              // Receive ECC corrected data register
    union   FSI_RX_ECC_LOG_REG               RX_ECC_LOG;                   // Receive ECC log and status register
    uint8_t                                  rsvd7[2];                     // Reserved
    union   FSI_RX_FRAME_TAG_CMP_REG         RX_FRAME_TAG_CMP;             // Receive frame tag compare register
    union   FSI_RX_PING_TAG_CMP_REG          RX_PING_TAG_CMP;              // Receive ping tag compare register
    uint8_t                                  rsvd8[4];                     // Reserved
    union   FSI_RX_TRIG_CTRL_0_REG           RX_TRIG_CTRL_0;               // Receive Trigger Control register 0
    union   FSI_RX_TRIG_WIDTH_0_REG          RX_TRIG_WIDTH_0;              // Receive Trigger Wdith register 0
    union   FSI_RX_DLYLINE_CTRL_REG          RX_DLYLINE_CTRL;              // Receive delay line control register
    uint8_t                                  rsvd9[2];                     // Reserved
    union   FSI_RX_TRIG_CTRL_1_REG           RX_TRIG_CTRL_1;               // Receive Trigger Control register 1
    union   FSI_RX_TRIG_CTRL_2_REG           RX_TRIG_CTRL_2;               // Receive Trigger Control register 2
    union   FSI_RX_TRIG_CTRL_3_REG           RX_TRIG_CTRL_3;               // Receive Trigger Control register 3
    union   FSI_RX_VIS_1_REG                 RX_VIS_1;                     // Receive debug visibility register 1
    union   FSI_RX_UDATA_FILTER_REG          RX_UDATA_FILTER;              // Receive User Data Filter Control register
    uint8_t                                  rsvd10[10];                   // Reserved
    uint16_t                                 RX_BUF_BASE[16];              // Base address for receive data buffer
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
