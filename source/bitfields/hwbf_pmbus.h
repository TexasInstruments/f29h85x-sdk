//###########################################################################
//
// FILE:    hwbf_pmbus.h
//
// TITLE:   Definitions for the PMBUS registers.
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

#ifndef HWBF_PMBUS_H
#define HWBF_PMBUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// PMBUS Individual Register Bit Definitions:

struct PMBUS_PMBCCR_BITS {              // bits description
    uint16_t RW:1;                      // 0 RnW bit of the Message
    uint16_t TARGET_ADDR:7;             // 7:1 TARGET Address
    uint16_t BYTE_COUNT:8;              // 15:8 Number of Bytes Transmitted
    uint16_t CMD_ENA:1;                 // 16 CONTROLLER Command Code Enable
    uint16_t EXT_CMD:1;                 // 17 CONTROLLER Extended Command Code Enable
    uint16_t PEC_ENA:1;                 // 18 CONTROLLER PEC Processing Enable
    uint16_t GRP_CMD:1;                 // 19 CONTROLLER Group Command Message Enable
    uint16_t PRC_CALL:1;                // 20 CONTROLLER Process Call Message Enable
    uint16_t rsvd1:11;                  // 31:21 Reserved
};

union PMBUS_PMBCCR_REG {
    uint32_t  all;
    struct  PMBUS_PMBCCR_BITS  bit;
};

struct PMBUS_PMBACK_BITS {              // bits description
    uint16_t ACK:1;                     // 0 Allows firmware to ack/nack received data
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PMBUS_PMBACK_REG {
    uint32_t  all;
    struct  PMBUS_PMBACK_BITS  bit;
};

struct PMBUS_PMBSTS_BITS {              // bits description
    uint16_t RD_BYTE_COUNT:3;           // 2:0 Number of Data Bytes available in Receive Data Register
    uint16_t DATA_READY:1;              // 3 Data Ready Flag
    uint16_t DATA_REQUEST:1;            // 4 Data Request Flag
    uint16_t EOM:1;                     // 5 End of Message Indicator
    uint16_t NACK:1;                    // 6 Not Acknowledge Flag Status
    uint16_t PEC_VALID:1;               // 7 PEC Valid Indicator
    uint16_t CLK_LOW_TIMEOUT:1;         // 8 Clock Low Timeout Status
    uint16_t CLK_HIGH_DETECTED:1;       // 9 Clock High Detection Status
    uint16_t TARGET_ADDR_READY:1;       // 10 TARGET Address Ready
    uint16_t RPT_START:1;               // 11 Repeated Start Flag
    uint16_t UNIT_BUSY:1;               // 12 PMBus Busy Indicator
    uint16_t BUS_FREE:1;                // 13 PMBus Free Indicator
    uint16_t LOST_ARB:1;                // 14 Lost Arbitration Flag
    uint16_t CONTROLLER:1;              // 15 CONTROLLER Indicator
    uint16_t ALERT_EDGE:1;              // 16 Alert Edge Detection Status
    uint16_t CONTROL_EDGE:1;            // 17 Control Edge Detection Status
    uint16_t ALERT_RAW:1;               // 18 Alert Pin Real Time Status
    uint16_t CONTROL_RAW:1;             // 19 Control Pin Real Time Status
    uint16_t SDA_RAW:1;                 // 20 PMBus Data Pin Real Time Status
    uint16_t SCL_RAW:1;                 // 21 PMBus Clock Pin Real Time Status
    uint16_t rsvd1:10;                  // 31:22 Reserved
};

union PMBUS_PMBSTS_REG {
    uint32_t  all;
    struct  PMBUS_PMBSTS_BITS  bit;
};

struct PMBUS_PMBINTM_BITS {             // bits description
    uint16_t BUS_FREE:1;                // 0 Bus Free Interrupt Mask
    uint16_t BUS_LOW_TIMEOUT:1;         // 1 Clock Low Timeout Interrupt Mask
    uint16_t DATA_READY:1;              // 2 Data Ready Interrupt Mask
    uint16_t DATA_REQUEST:1;            // 3 Data Request Interrupt Mask
    uint16_t TARGET_ADDR_READY:1;       // 4 TARGET Address Ready Interrupt Mask
    uint16_t EOM:1;                     // 5 End of Message Interrupt Mask
    uint16_t ALERT:1;                   // 6 Alert Detection Interrupt Mask
    uint16_t CONTROL:1;                 // 7 Control Detection Interrupt Mask
    uint16_t LOST_ARB:1;                // 8 Lost Arbitration Interrupt Mask
    uint16_t CLK_HIGH_DETECT:1;         // 9 Clock High Detection Interrupt Mask
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PMBUS_PMBINTM_REG {
    uint32_t  all;
    struct  PMBUS_PMBINTM_BITS  bit;
};

struct PMBUS_PMBTCR_BITS {              // bits description
    uint16_t TARGET_ADDR:7;             // 6:0 Configures the current device address of the TARGET.
    uint16_t MAN_TARGET_ACK:1;          // 7 Manual TARGET Address Acknowledgement Mode
    uint16_t TARGET_MASK:7;             // 14:8 TARGET address mask
    uint16_t PEC_ENA:1;                 // 15 PEC Processing Enable
    uint16_t TX_COUNT:3;                // 18:16 Number of valid bytes in Transmit Data Register
    uint16_t TX_PEC:1;                  // 19 send a PEC byte at end of message
    uint16_t MAN_CMD:1;                 // 20 Manual Command Acknowledgement Mode
    uint16_t RX_BYTE_ACK_CNT:2;         // 22:21 Number of data bytes to automatically acknowledge
    uint16_t rsvd1:9;                   // 31:23 Reserved
};

union PMBUS_PMBTCR_REG {
    uint32_t  all;
    struct  PMBUS_PMBTCR_BITS  bit;
};

struct PMBUS_PMBHTA_BITS {              // bits description
    uint16_t TARGET_RW:1;               // 0 Stored R/W bit
    uint16_t TARGET_ADDR:7;             // 7:1 Stored device address
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PMBUS_PMBHTA_REG {
    uint32_t  all;
    struct  PMBUS_PMBHTA_BITS  bit;
};

struct PMBUS_PMBCTRL_BITS {             // bits description
    uint16_t RESET:1;                   // 0 PMBus Interface Synchronous Reset
    uint16_t ALERT_EN:1;                // 1 TARGET Alert Enable
    uint16_t BUS_LO_INT_EDGE:1;         // 2 Clock Low Timeout Interrupt Edge Select
    uint16_t FAST_MODE:1;               // 3 Fast Mode Enable
    uint16_t FAST_MODE_PLUS:1;          // 4 Fast Mode Plus Enable
    uint16_t CNTL_INT_EDGE:1;           // 5 Control Interrupt Edge Select
    uint16_t ALERT_MODE:1;              // 6 Configures mode of Alert pin
    uint16_t ALERT_VALUE:1;             // 7 Configures output value of Alert pin in GPIO Mode
    uint16_t ALERT_DIR:1;               // 8 Configures direction of Alert pin in GPIO mode
    uint16_t CNTL_MODE:1;               // 9 Configures mode of Control pin
    uint16_t CNTL_VALUE:1;              // 10 Configures output value of Control pin in GPIO Mode
    uint16_t CNTL_DIR:1;                // 11 Configures direction of Control pin in GPIO mode
    uint16_t SDA_MODE:1;                // 12 Configures mode of PMBus Data pin
    uint16_t SDA_VALUE:1;               // 13 Configures output value of PMBus data pin in GPIO Mode
    uint16_t SDA_DIR:1;                 // 14 Configures direction of PMBus data pin in GPIO mode
    uint16_t rsvd1:1;                   // 15 Reserved
    uint16_t rsvd2:1;                   // 16 Reserved
    uint16_t rsvd3:1;                   // 17 Reserved
    uint16_t rsvd4:1;                   // 18 Reserved
    uint16_t rsvd5:1;                   // 19 Reserved
    uint16_t CLK_LO_DIS:1;              // 20 Clock Low Timeout Disable
    uint16_t TARGET_EN:1;               // 21 PMBus TARGET Enable
    uint16_t CONTROLLER_EN:1;           // 22 PMBus CONTROLLER Enable
    uint16_t CLKDIV:5;                  // 27:23 PMBUS Clock Divide Value
    uint16_t rsvd6:2;                   // 29:28 Reserved
    uint16_t ZH_EN:1;                   // 30 Zero data hold enable
    uint16_t I2CMODE:1;                 // 31 Bit to enable I2C mode
};

union PMBUS_PMBCTRL_REG {
    uint32_t  all;
    struct  PMBUS_PMBCTRL_BITS  bit;
};

struct PMBUS_PMBTIMCTL_BITS {           // bits description
    uint16_t TIM_OVERRIDE:1;            // 0 Overide the default settings of the timing parameters.
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PMBUS_PMBTIMCTL_REG {
    uint32_t  all;
    struct  PMBUS_PMBTIMCTL_BITS  bit;
};

struct PMBUS_PMBTIMCLK_BITS {           // bits description
    uint16_t CLK_HIGH_LIMIT:8;          // 7:0 Determines the PMBUS CONTROLLER clock high pulse width.
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t CLK_FREQ:8;                // 23:16 Determines the PMBUS CONTROLLER clock frequency.
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union PMBUS_PMBTIMCLK_REG {
    uint32_t  all;
    struct  PMBUS_PMBTIMCLK_BITS  bit;
};

struct PMBUS_PMBTIMSTSETUP_BITS {       // bits description
    uint16_t TSU_STA:8;                 // 7:0 Setup time, rise edge of CONTROLLER clock to start edge.
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PMBUS_PMBTIMSTSETUP_REG {
    uint32_t  all;
    struct  PMBUS_PMBTIMSTSETUP_BITS  bit;
};

struct PMBUS_PMBTIMBIDLE_BITS {         // bits description
    uint16_t BUSIDLE:10;                // 9:0 Determines the Bus Idle Limit
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PMBUS_PMBTIMBIDLE_REG {
    uint32_t  all;
    struct  PMBUS_PMBTIMBIDLE_BITS  bit;
};

struct PMBUS_PMBTIMLOWTIMOUT_BITS {     // bits description
    uint32_t CLKLOWTIMOUT:20;           // 19:0 Determines the clock low timeout value
    uint16_t rsvd1:12;                  // 31:20 Reserved
};

union PMBUS_PMBTIMLOWTIMOUT_REG {
    uint32_t  all;
    struct  PMBUS_PMBTIMLOWTIMOUT_BITS  bit;
};

struct PMBUS_PMBTIMHIGHTIMOUT_BITS {    // bits description
    uint16_t CLKHIGHTIMOUT:10;          // 9:0 Determines the clock high timeout value
    uint16_t rsvd1:6;                   // 15:10 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union PMBUS_PMBTIMHIGHTIMOUT_REG {
    uint32_t  all;
    struct  PMBUS_PMBTIMHIGHTIMOUT_BITS  bit;
};

struct PMBUS_REGS {
    union   PMBUS_PMBCCR_REG                 PMBCCR;                       // PMBUS CONTROLLER Mode Control Register
    uint32_t                                 PMBTXBUF;                     // PMBUS Transmit Buffer
    uint32_t                                 PMBRXBUF;                     // PMBUS Receive buffer
    union   PMBUS_PMBACK_REG                 PMBACK;                       // PMBUS Acknowledge Register
    union   PMBUS_PMBSTS_REG                 PMBSTS;                       // PMBUS Status Register
    union   PMBUS_PMBINTM_REG                PMBINTM;                      // PMBUS Interrupt Mask Register
    union   PMBUS_PMBTCR_REG                 PMBTCR;                       // PMBUS TARGET Mode Configuration Register
    union   PMBUS_PMBHTA_REG                 PMBHTA;                       // PMBUS Hold TARGET Address Register
    union   PMBUS_PMBCTRL_REG                PMBCTRL;                      // PMBUS Control Register
    union   PMBUS_PMBTIMCTL_REG              PMBTIMCTL;                    // PMBUS Timing Control Register
    union   PMBUS_PMBTIMCLK_REG              PMBTIMCLK;                    // PMBUS Clock Timing Register
    union   PMBUS_PMBTIMSTSETUP_REG          PMBTIMSTSETUP;                // PMBUS Start Setup Time Register
    union   PMBUS_PMBTIMBIDLE_REG            PMBTIMBIDLE;                  // PMBUS Bus Idle Time Register
    union   PMBUS_PMBTIMLOWTIMOUT_REG        PMBTIMLOWTIMOUT;              // PMBUS Clock Low Timeout Value Register
    union   PMBUS_PMBTIMHIGHTIMOUT_REG       PMBTIMHIGHTIMOUT;             // PMBUS Clock High Timeout Value Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
