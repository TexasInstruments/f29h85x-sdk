//###########################################################################
//
// FILE:    hwbf_ecat_ss.h
//
// TITLE:   Definitions for the ECAT_SS registers.
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

#ifndef HWBF_ECAT_SS_H
#define HWBF_ECAT_SS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// ECAT_SS Individual Register Bit Definitions:

struct ECAT_SS_ESCSS_IPREVNUM_BITS {    // bits description
    uint16_t IP_REV_MINOR:4;            // 3:0 Minor IP Revision Number
    uint16_t IP_REV_MAJOR:4;            // 7:4 Major IP Revision Number
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_IPREVNUM_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_IPREVNUM_BITS  bit;
};

struct ECAT_SS_ESCSS_INTR_RIS_BITS {    // bits description
    uint16_t SYNC0_RIS:1;               // 0 SYNC0 feature RIS
    uint16_t SYNC1_RIS:1;               // 1 SYNC1 feature RIS
    uint16_t IRQ_RIS:1;                 // 2 EtherCATSS IRQ RIS
    uint16_t DMA_DONE_RIS:1;            // 3 DMA Done RIS
    uint16_t TIMEOUT_ERR_RIS:1;         // 4 PDI bus Timeout Error RIS
    uint16_t MASTER_RESET_RIS:1;        // 5 ECAT RESET RIS
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_INTR_RIS_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_INTR_RIS_BITS  bit;
};

struct ECAT_SS_ESCSS_INTR_MASK_BITS {   // bits description
    uint16_t SYNC0_MASK:1;              // 0 SYNC0 feature Mask
    uint16_t SYNC1_MASK:1;              // 1 SYNC1 feature Mask
    uint16_t IRQ_MASK:1;                // 2 EtherCATSS IRQ Mask
    uint16_t DMA_DONE_MASK:1;           // 3 DMA Done Mask
    uint16_t TIMEOUT_ERR_MASK:1;        // 4 PDI Access Timeout Error Mask
    uint16_t MASTER_RESET_MASK:1;       // 5 EtherCAT Master Reset Mask
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_INTR_MASK_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_INTR_MASK_BITS  bit;
};

struct ECAT_SS_ESCSS_INTR_MIS_BITS {    // bits description
    uint16_t SYNC0_MIS:1;               // 0 SYNC0 feature MIS
    uint16_t SYNC1_MIS:1;               // 1 SYNC1 feature MIS
    uint16_t IRQ_MIS:1;                 // 2 EtherCATSS IRQ MIS
    uint16_t DMA_DONE_MIS:1;            // 3 DMA Done MIS
    uint16_t TIMEOUT_ERR_MIS:1;         // 4 PDI bus Timeout Error MIS
    uint16_t MASTER_RESET_MIS:1;        // 5 EtherCAT Master Reset MIS
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_INTR_MIS_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_INTR_MIS_BITS  bit;
};

struct ECAT_SS_ESCSS_INTR_CLR_BITS {    // bits description
    uint16_t SYNC0_CLR:1;               // 0 SYNC0 feature Clear
    uint16_t SYNC1_CLR:1;               // 1 SYNC1 feature Clear
    uint16_t IRQ_CLR:1;                 // 2 EtherCATSS IRQ Clear
    uint16_t DMA_DONE_CLR:1;            // 3 DMA Done Clear
    uint16_t TIMEOUT_ERR_CLR:1;         // 4 PDI Access Timeout Error Clear
    uint16_t MASTER_RESET_CLR:1;        // 5 EtherCAT Master Reset Clear
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_INTR_CLR_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_INTR_CLR_BITS  bit;
};

struct ECAT_SS_ESCSS_INTR_SET_BITS {    // bits description
    uint16_t SYNC0_SET:1;               // 0 SYNC0 Set Emulate
    uint16_t SYNC1_SET:1;               // 1 SYNC1 Set Emulate
    uint16_t IRQ_SET:1;                 // 2 EtherCATSS IRQ Set Emulate
    uint16_t DMA_DONE_SET:1;            // 3 DMA Done Set Emulate
    uint16_t TIMEOUT_ERR_SET:1;         // 4 PDI Access Timeout Error Set Emulate
    uint16_t MASTER_RESET_SET:1;        // 5 EtherCAT Master Reset Emulate
    uint16_t rsvd1:2;                   // 7:6 Reserved
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_INTR_SET_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_INTR_SET_BITS  bit;
};

struct ECAT_SS_ESCSS_LATCH_SEL_BITS {   // bits description
    uint16_t LATCH0_SELECT:5;           // 4:0 LATCH0 Inputs mux select
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint16_t LATCH1_SELECT:5;           // 12:8 LATCH1 Inputs mux select
    uint16_t rsvd2:3;                   // 15:13 Reserved
    uint16_t rsvd3:1;                   // 16 Reserved
    uint16_t rsvd4:15;                  // 31:17 Reserved
};

union ECAT_SS_ESCSS_LATCH_SEL_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_LATCH_SEL_BITS  bit;
};

struct ECAT_SS_ESCSS_ACCESS_CTRL_BITS { // bits description
    uint16_t WAIT_STATES:7;             // 6:0 Minimum Wait States for VBUS Bridge
    uint16_t EN_TIMEOUT:1;              // 7 PDI Timeout enable
    uint16_t rsvd1:1;                   // 8 Reserved
    uint16_t ENABLE_DEBUG_ACCESS:1;     // 9 Debug access enable
    uint16_t ENABLE_PARALLEL_PORT_ACCESS:1; // 10 Parallel port access enable
    uint16_t rsvd2:5;                   // 15:11 Reserved
    uint16_t TIMEOUT_COUNT:12;          // 27:16 Max timecount programmed and count while enabled.
    uint16_t rsvd3:4;                   // 31:28 Reserved
};

union ECAT_SS_ESCSS_ACCESS_CTRL_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_ACCESS_CTRL_BITS  bit;
};

struct ECAT_SS_ESCSS_GPIN_GRP_CAP_SEL_BITS {// bits description
    uint16_t GPI_GRP_CAP_SEL0:3;        // 2:0 GPI7-0 capture trigger select
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t GPI_GRP_CAP_SEL1:3;        // 6:4 GPI15-8 capture trigger select
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t GPI_GRP_CAP_SEL2:3;        // 10:8 GPI23-16 capture trigger select
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t GPI_GRP_CAP_SEL3:3;        // 14:12 GPI31-24 capture trigger select
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_GPIN_GRP_CAP_SEL_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_GPIN_GRP_CAP_SEL_BITS  bit;
};

struct ECAT_SS_ESCSS_GPOUT_GRP_CAP_SEL_BITS {// bits description
    uint16_t GPO_GRP_CAP_SEL0:2;        // 1:0 GPO7-0 capture trigger select
    uint16_t rsvd1:2;                   // 3:2 Reserved
    uint16_t GPO_GRP_CAP_SEL1:2;        // 5:4 GPO15-8 capture trigger select
    uint16_t rsvd2:2;                   // 7:6 Reserved
    uint16_t GPO_GRP_CAP_SEL2:2;        // 9:8 GPO23-16 capture trigger select
    uint16_t rsvd3:2;                   // 11:10 Reserved
    uint16_t GPO_GRP_CAP_SEL3:2;        // 13:12 GPO31-24 capture trigger select
    uint16_t rsvd4:2;                   // 15:14 Reserved
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_GPOUT_GRP_CAP_SEL_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_GPOUT_GRP_CAP_SEL_BITS  bit;
};

struct ECAT_SS_ESCSS_MEM_TEST_BITS {    // bits description
    uint16_t INITIATE_MEM_INIT:1;       // 0 Initialize memory init
    uint16_t MEM_INIT_DONE:1;           // 1 Memory Init done status
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_MEM_TEST_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_MEM_TEST_BITS  bit;
};

struct ECAT_SS_ESCSS_RESET_DEST_CONFIG_BITS {// bits description
    uint16_t CPU_RESET_EN:1;            // 0 CPU reset enable for ResetOut
    uint16_t CPU_NMI_EN:1;              // 1 CPU NMI enable for ResetOut
    uint16_t CPU_INT_EN:1;              // 2 CPU Interrupt enable for ResetOut
    uint16_t rsvd1:4;                   // 6:3 Reserved
    uint16_t DEVICE_RESET_EN:1;         // 7 Enables RESET_OUT to impact the device reset
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_RESET_DEST_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_RESET_DEST_CONFIG_BITS  bit;
};

struct ECAT_SS_ESCSS_SYNC0_CONFIG_BITS {// bits description
    uint16_t CPUx_INT_EN:1;             // 0 Connects the SYNC0 to CPUx  Interrupt
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t DMAx_TRIG_EN:1;            // 2 Connects the SYNC0 to DMA Trigger
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:3;                   // 7:5 Reserved
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_SYNC0_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_SYNC0_CONFIG_BITS  bit;
};

struct ECAT_SS_ESCSS_SYNC1_CONFIG_BITS {// bits description
    uint16_t CPUx_INT_EN:1;             // 0 Connects the SYNC1 to CPUx Interrupt
    uint16_t rsvd1:1;                   // 1 Reserved
    uint16_t DMAx_TRIG_EN:1;            // 2 Connects the SYNC1 to CPUx DMA Trigger
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:3;                   // 7:5 Reserved
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_SYNC1_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_SYNC1_CONFIG_BITS  bit;
};

struct ESCSS_REGS {
    union   ECAT_SS_ESCSS_IPREVNUM_REG       ESCSS_IPREVNUM;               // IP Revision Number
    union   ECAT_SS_ESCSS_INTR_RIS_REG       ESCSS_INTR_RIS;               // EtherCATSS Interrupt Raw Status
    union   ECAT_SS_ESCSS_INTR_MASK_REG      ESCSS_INTR_MASK;              // EtherCATSS Interrupt Mask
    union   ECAT_SS_ESCSS_INTR_MIS_REG       ESCSS_INTR_MIS;               // EtherCATSS Masked Interrupt Status
    union   ECAT_SS_ESCSS_INTR_CLR_REG       ESCSS_INTR_CLR;               // EtherCATSS Interrupt Clear
    union   ECAT_SS_ESCSS_INTR_SET_REG       ESCSS_INTR_SET;               // EtherCATSS Interrupt Set to emulate
    union   ECAT_SS_ESCSS_LATCH_SEL_REG      ESCSS_LATCH_SEL;              // Select for Latch0/1 inputs and LATCHIN input
    union   ECAT_SS_ESCSS_ACCESS_CTRL_REG    ESCSS_ACCESS_CTRL;            // PDI interface access control config.
    uint32_t                                 ESCSS_GPIN_DAT;               // GPIN data capture for debug & override
    uint32_t                                 ESCSS_GPIN_PIPE;              // GPIN pipeline select
    union   ECAT_SS_ESCSS_GPIN_GRP_CAP_SEL_REG ESCSS_GPIN_GRP_CAP_SEL;     // GPIN pipe group capture trigger
    uint32_t                                 ESCSS_GPOUT_DAT;              // GPOUT data capture for debug & override
    uint32_t                                 ESCSS_GPOUT_PIPE;             // GPOUT pipeline select
    union   ECAT_SS_ESCSS_GPOUT_GRP_CAP_SEL_REG ESCSS_GPOUT_GRP_CAP_SEL;   // GPOUT pipe group capture trigger
    union   ECAT_SS_ESCSS_MEM_TEST_REG       ESCSS_MEM_TEST;               // Memory Test Control
    union   ECAT_SS_ESCSS_RESET_DEST_CONFIG_REG ESCSS_RESET_DEST_CONFIG;   // ResetOut impact or destination config
    union   ECAT_SS_ESCSS_SYNC0_CONFIG_REG   ESCSS_SYNC0_CONFIG;           // SYNC0 Configuration for various triggers
    union   ECAT_SS_ESCSS_SYNC1_CONFIG_REG   ESCSS_SYNC1_CONFIG;           // SYNC1 Configuration for various triggers
};

struct ECAT_SS_ESCSS_CONFIG_LOCK_BITS { // bits description
    uint16_t LOCK_ENABLE:1;             // 0 Locking writes to ECATSS
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t IO_CONFIG_ENABLE:1;        // 4 Locking the IO Configuration
    uint16_t rsvd2:3;                   // 7:5 Reserved
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_CONFIG_LOCK_BITS  bit;
};

struct ECAT_SS_ESCSS_MISC_IO_CONFIG_BITS {// bits description
    uint16_t RESETIN_GPIO_EN:1;         // 0 Enabled ResetIN from GPIO
    uint16_t EEPROM_I2C_IO_EN:1;        // 1 Enables the EEPROM I2C IOPAD connection
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_MISC_IO_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_MISC_IO_CONFIG_BITS  bit;
};

struct ECAT_SS_ESCSS_PHY_IO_CONFIG_BITS {// bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t PHY_PORT_CNT:2;            // 3:2 Number of PHY port counts
    uint16_t rsvd2:2;                   // 5:4 Reserved
    uint16_t TX_CLK_AUTO_COMP:1;        // 6 Selects TX_CLK IO to do Auto compensation
    uint16_t rsvd3:1;                   // 7 Reserved
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_PHY_IO_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_PHY_IO_CONFIG_BITS  bit;
};

struct ECAT_SS_ESCSS_SYNC_IO_CONFIG_BITS {// bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t rsvd2:1;                   // 2 Reserved
    uint16_t SYNC0_GPIO_EN:1;           // 3 SYNC0 connection to OUT pad enabled
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:1;                   // 6 Reserved
    uint16_t SYNC1_GPIO_EN:1;           // 7 SYNC1 connection to OUT pad enabled
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_SYNC_IO_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_SYNC_IO_CONFIG_BITS  bit;
};

struct ECAT_SS_ESCSS_LATCH_IO_CONFIG_BITS {// bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t rsvd2:1;                   // 2 Reserved
    uint16_t LATCH0_GPIO_EN:1;          // 3 LATCH0 connection to IN pad enabled
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:1;                   // 6 Reserved
    uint16_t LATCH1_GPIO_EN:1;          // 7 LATCH1 connection to IN pad enabled
    uint16_t WRITE_KEY:8;               // 15:8 Key to enable writing lock
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_LATCH_IO_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_LATCH_IO_CONFIG_BITS  bit;
};

struct ECAT_SS_ESCSS_LED_CONFIG_BITS {  // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t STATE:1;                   // 2 GPIO enable for STATE LED
    uint16_t ERR:1;                     // 3 GPIO enable for ERR LED
    uint16_t RUN:1;                     // 4 GPIO enable for RUN LED
    uint16_t rsvd3:1;                   // 5 Reserved
    uint16_t rsvd4:2;                   // 7:6 Reserved
    uint16_t rsvd5:2;                   // 9:8 Reserved
    uint16_t rsvd6:2;                   // 11:10 Reserved
    uint16_t rsvd7:2;                   // 13:12 Reserved
    uint16_t rsvd8:2;                   // 15:14 Reserved
    uint16_t rsvd9:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_LED_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_LED_CONFIG_BITS  bit;
};

struct ECAT_SS_ESCSS_MISC_CONFIG_BITS { // bits description
    uint16_t TX0_SHIFT_CONFIG:2;        // 1:0 TX Shift configuration for Port0
    uint16_t TX1_SHIFT_CONFIG:2;        // 3:2 TX Shift configuration for Port1
    uint16_t EEPROM_SIZE:1;             // 4 EEPROM Size bound select
    uint16_t PDI_EMULATION:1;           // 5 PDI Emulation enable
    uint16_t PHY_ADDR:5;                // 10:6 PHY Address Offset
    uint16_t rsvd1:5;                   // 15:11 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ECAT_SS_ESCSS_MISC_CONFIG_REG {
    uint32_t  all;
    struct  ECAT_SS_ESCSS_MISC_CONFIG_BITS  bit;
};

struct ESCSS_CONFIG_REGS {
    union   ECAT_SS_ESCSS_CONFIG_LOCK_REG    ESCSS_CONFIG_LOCK;            // EtherCATSS Configuration Lock
    union   ECAT_SS_ESCSS_MISC_IO_CONFIG_REG ESCSS_MISC_IO_CONFIG;         // RESET_IN, EEPROM IO connections select
    union   ECAT_SS_ESCSS_PHY_IO_CONFIG_REG  ESCSS_PHY_IO_CONFIG;          // Control Register of ESCSS
    union   ECAT_SS_ESCSS_SYNC_IO_CONFIG_REG ESCSS_SYNC_IO_CONFIG;         // SYNC Signals IO configurations
    union   ECAT_SS_ESCSS_LATCH_IO_CONFIG_REG ESCSS_LATCH_IO_CONFIG;       // LATCH inputs IO pad select
    uint32_t                                 ESCSS_GPIN_SEL;               // GPIN Select between IO PAD & tieoff
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 ESCSS_GPOUT_SEL;              // GPOUT IO pad connect select
    uint8_t                                  rsvd2[4];                     // Reserved
    union   ECAT_SS_ESCSS_LED_CONFIG_REG     ESCSS_LED_CONFIG;             // Selection of LED o/p connect to IO pad
    union   ECAT_SS_ESCSS_MISC_CONFIG_REG    ESCSS_MISC_CONFIG;            // Miscelleneous Configuration
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
