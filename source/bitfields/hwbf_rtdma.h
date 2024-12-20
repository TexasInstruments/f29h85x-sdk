//###########################################################################
//
// FILE:    hwbf_rtdma.h
//
// TITLE:   Definitions for the RTDMA registers.
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

#ifndef HWBF_RTDMA_H
#define HWBF_RTDMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// RTDMA Individual Register Bit Definitions:

struct RTDMA_DMACTRL_BITS {             // bits description
    uint16_t HARDRESET:1;               // 0 Hard Reset Bit
    uint16_t PRIORITYRESET:1;           // 1 Priority Reset Bit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t PRIORITYSEL:1;             // 16 The priority select bit
    uint16_t rsvd2:15;                  // 31:17 Reserved
};

union RTDMA_DMACTRL_REG {
    uint32_t  all;
    struct  RTDMA_DMACTRL_BITS  bit;
};

struct RTDMA_DEBUGCTRL_BITS {           // bits description
    uint16_t rsvd1:15;                  // 14:0 Reserved
    uint16_t FREE:1;                    // 15 Debug Mode Bit
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_DEBUGCTRL_REG {
    uint32_t  all;
    struct  RTDMA_DEBUGCTRL_BITS  bit;
};

struct RTDMA_REVISION_BITS {            // bits description
    uint16_t TYPE:8;                    // 7:0 RTDMA Type
    uint16_t REV:8;                     // 15:8 RTDMA Revision
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_REVISION_REG {
    uint32_t  all;
    struct  RTDMA_REVISION_BITS  bit;
};

struct RTDMA_SWPRI1_BITS {              // bits description
    uint16_t CH1PRIORITY:4;             // 3:0 Ch1 Priority Configuration
    uint16_t CH2PRIORITY:4;             // 7:4 Ch2 Priority Configuration
    uint16_t CH3PRIORITY:4;             // 11:8 Ch3 Priority Configuration
    uint16_t CH4PRIORITY:4;             // 15:12 Ch4 Priority Configuration
    uint16_t CH5PRIORITY:4;             // 19:16 Ch5 Priority Configuration
    uint16_t CH6PRIORITY:4;             // 23:20 Ch6 Priority Configuration
    uint16_t CH7PRIORITY:4;             // 27:24 Ch7 Priority Configuration
    uint16_t CH8PRIORITY:4;             // 31:28 Ch8 Priority Configuration
};

union RTDMA_SWPRI1_REG {
    uint32_t  all;
    struct  RTDMA_SWPRI1_BITS  bit;
};

struct RTDMA_SWPRI2_BITS {              // bits description
    uint16_t CH9PRIORITY:4;             // 3:0 Ch9 Priority Configuration
    uint16_t CH10PRIORITY:4;            // 7:4 Ch10 Priority Configuration
    uint16_t rsvd1:4;                   // 11:8 Reserved
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t rsvd3:4;                   // 19:16 Reserved
    uint16_t rsvd4:4;                   // 23:20 Reserved
    uint16_t rsvd5:4;                   // 27:24 Reserved
    uint16_t rsvd6:4;                   // 31:28 Reserved
};

union RTDMA_SWPRI2_REG {
    uint32_t  all;
    struct  RTDMA_SWPRI2_BITS  bit;
};

struct RTDMA_PRIORITYSTAT_BITS {        // bits description
    uint16_t ACTIVESTS:5;               // 4:0 Active Channel Status Bits
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint16_t ACTIVESTS_SHADOW:5;        // 12:8 Active Channel Status Shadow Bits
    uint16_t rsvd2:3;                   // 15:13 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union RTDMA_PRIORITYSTAT_REG {
    uint32_t  all;
    struct  RTDMA_PRIORITYSTAT_BITS  bit;
};

struct RTDMA_DMACFG_LOCK_BITS {         // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_DMACFG_LOCK_REG {
    uint32_t  all;
    struct  RTDMA_DMACFG_LOCK_BITS  bit;
};

struct RTDMA_DMACFG_COMMIT_BITS {       // bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_DMACFG_COMMIT_REG {
    uint32_t  all;
    struct  RTDMA_DMACFG_COMMIT_BITS  bit;
};

struct RTDMA_REGS {
    union   RTDMA_DMACTRL_REG                DMACTRL;                      // DMA Control Register
    union   RTDMA_DEBUGCTRL_REG              DEBUGCTRL;                    // Debug Control Register
    union   RTDMA_REVISION_REG               REVISION;                     // RTDMA Revision Control Register
    uint8_t                                  rsvd1[8];                     // Reserved
    union   RTDMA_SWPRI1_REG                 SWPRI1;                       // Software Priority Configuration Register 1
    union   RTDMA_SWPRI2_REG                 SWPRI2;                       // Software Priority Configuration Register 2
    union   RTDMA_PRIORITYSTAT_REG           PRIORITYSTAT;                 // Priority Status Register
    uint8_t                                  rsvd2[32];                    // Reserved
    union   RTDMA_DMACFG_LOCK_REG            DMACFG_LOCK;                  // Channel Configuration Temporary Lock
    union   RTDMA_DMACFG_COMMIT_REG          DMACFG_COMMIT;                // Channel Configuration Permanent Commit
};

struct RTDMA_MPUR_CHMASK_BITS {         // bits description
    uint16_t CH1MASK:1;                 // 0 MPU region channel mask Channel 1
    uint16_t CH2MASK:1;                 // 1 MPU region channel mask Channel 2
    uint16_t CH3MASK:1;                 // 2 MPU region channel mask Channel 3
    uint16_t CH4MASK:1;                 // 3 MPU region channel mask Channel 4
    uint16_t CH5MASK:1;                 // 4 MPU region channel mask Channel 5
    uint16_t CH6MASK:1;                 // 5 MPU region channel mask Channel 6
    uint16_t CH7MASK:1;                 // 6 MPU region channel mask Channel 7
    uint16_t CH8MASK:1;                 // 7 MPU region channel mask Channel 8
    uint16_t CH9MASK:1;                 // 8 MPU region channel mask Channel 9
    uint16_t CH10MASK:1;                // 9 MPU region channel mask Channel 10
    uint16_t rsvd1:1;                   // 10 Reserved
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t rsvd3:1;                   // 12 Reserved
    uint16_t rsvd4:1;                   // 13 Reserved
    uint16_t rsvd5:1;                   // 14 Reserved
    uint16_t rsvd6:1;                   // 15 Reserved
    uint16_t rsvd7:16;                  // 31:16 Reserved
};

union RTDMA_MPUR_CHMASK_REG {
    uint32_t  all;
    struct  RTDMA_MPUR_CHMASK_BITS  bit;
};

struct RTDMA_MPUR_START_BITS {          // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:16;                  // 31:16 Upper Start Address
};

union RTDMA_MPUR_START_REG {
    uint32_t  all;
    struct  RTDMA_MPUR_START_BITS  bit;
};

struct RTDMA_MPUR_END_BITS {            // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:16;                  // 31:16 Upper End Address
};

union RTDMA_MPUR_END_REG {
    uint32_t  all;
    struct  RTDMA_MPUR_END_BITS  bit;
};

struct RTDMA_MPUR_LOCK_BITS {           // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_MPUR_LOCK_REG {
    uint32_t  all;
    struct  RTDMA_MPUR_LOCK_BITS  bit;
};

struct RTDMA_MPUR_COMMIT_BITS {         // bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_MPUR_COMMIT_REG {
    uint32_t  all;
    struct  RTDMA_MPUR_COMMIT_BITS  bit;
};

struct RTDMA_MPUR_ACCESS_BITS {         // bits description
    uint16_t ACCESS:2;                  // 1:0 Region Access Permissions
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_MPUR_ACCESS_REG {
    uint32_t  all;
    struct  RTDMA_MPUR_ACCESS_BITS  bit;
};

struct RTDMA_MPU_REGS_RegisterFile0_REGS {
    union   RTDMA_MPUR_CHMASK_REG            MPUR_CHMASK;                  // MPU Region Configuration
    union   RTDMA_MPUR_START_REG             MPUR_START;                   // MPU Region Start Address
    union   RTDMA_MPUR_END_REG               MPUR_END;                     // MPU Region End Address
    union   RTDMA_MPUR_LOCK_REG              MPUR_LOCK;                    // MPU Temporary Lock
    union   RTDMA_MPUR_COMMIT_REG            MPUR_COMMIT;                  // MPU Permanent Commit
    union   RTDMA_MPUR_ACCESS_REG            MPUR_ACCESS;                  // MPU Region R/W Access Permissions
    uint8_t                                  rsvd1[8];                     // Reserved
};

struct RTDMA_MPUCTRL_BITS {             // bits description
    uint16_t MPUEN:1;                   // 0 Enable MPU function
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_MPUCTRL_REG {
    uint32_t  all;
    struct  RTDMA_MPUCTRL_BITS  bit;
};

struct RTDMA_MPUCFG_LOCK_BITS {         // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_MPUCFG_LOCK_REG {
    uint32_t  all;
    struct  RTDMA_MPUCFG_LOCK_BITS  bit;
};

struct RTDMA_MPUCFG_COMMIT_BITS {       // bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_MPUCFG_COMMIT_REG {
    uint32_t  all;
    struct  RTDMA_MPUCFG_COMMIT_BITS  bit;
};

struct RTDMA_MPU_REGS {
    struct RTDMA_MPU_REGS_RegisterFile0_REGS RTDMA_MPU_RegisterFile0[16];  // 
    uint8_t                                  rsvd1[1536];                  // Reserved
    union   RTDMA_MPUCTRL_REG                MPUCTRL;                      // MPU Control Register
    uint8_t                                  rsvd2[28];                    // Reserved
    union   RTDMA_MPUCFG_LOCK_REG            MPUCFG_LOCK;                  // Channel Configuration Temporary Lock
    union   RTDMA_MPUCFG_COMMIT_REG          MPUCFG_COMMIT;                // Channel Configuration Permanent Commit
};

struct RTDMA_MODE_BITS {                // bits description
    uint16_t PERINTSEL:8;               // 7:0 Peripheral Interrupt and Sync Select
    uint16_t rsvd1:2;                   // 9:8 Reserved
    uint16_t OVRINTE:1;                 // 10 Overflow Interrupt Enable
    uint16_t PERINTE:1;                 // 11 Peripheral Interrupt Enable
    uint16_t CHINTMODE:1;               // 12 Channel Interrupt Mode
    uint16_t ONESHOT:1;                 // 13 One Shot Mode Bit
    uint16_t CONTINUOUS:1;              // 14 Continuous Mode Bit
    uint16_t rsvd2:1;                   // 15 Reserved
    uint16_t rsvd3:1;                   // 16 Reserved
    uint16_t DATASIZE:2;                // 18:17 Data Size Mode Bit
    uint16_t CHINTE:1;                  // 19 Channel Interrupt Enable Bit
    uint16_t WRT_DATASIZE:2;            // 21:20 Write Data Size Mode Bit
    uint16_t rsvd4:10;                  // 31:22 Reserved
};

union RTDMA_MODE_REG {
    uint32_t  all;
    struct  RTDMA_MODE_BITS  bit;
};

struct RTDMA_CONTROL_BITS {             // bits description
    uint16_t RUN:1;                     // 0 Run Bit
    uint16_t HALT:1;                    // 1 Halt Bit
    uint16_t SOFTRESET:1;               // 2 Soft Reset Bit
    uint16_t PERINTFRC:1;               // 3 Interrupt Force Bit
    uint16_t PERINTCLR:1;               // 4 Interrupt Clear Bit
    uint16_t rsvd1:1;                   // 5 Reserved
    uint16_t rsvd2:1;                   // 6 Reserved
    uint16_t ERRCLR:1;                  // 7 Error Clear Bit
    uint16_t PERINTFLG:1;               // 8 Interrupt Flag Bit
    uint16_t rsvd3:1;                   // 9 Reserved
    uint16_t rsvd4:1;                   // 10 Reserved
    uint16_t TRANSFERSTS:1;             // 11 Transfer Status Bit
    uint16_t BURSTSTS:1;                // 12 Burst Status Bit
    uint16_t RUNSTS:1;                  // 13 Run Status Bit
    uint16_t OVRFLG:1;                  // 14 Overflow Flag Bit
    uint16_t rsvd5:1;                   // 15 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union RTDMA_CONTROL_REG {
    uint32_t  all;
    struct  RTDMA_CONTROL_BITS  bit;
};

struct RTDMA_BURST_SIZE_BITS {          // bits description
    uint16_t BURSTSIZE:8;               // 7:0 Burst Transfer Size
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_BURST_SIZE_REG {
    uint32_t  all;
    struct  RTDMA_BURST_SIZE_BITS  bit;
};

struct RTDMA_BURST_COUNT_BITS {         // bits description
    uint16_t BURSTCOUNT:8;              // 7:0 Burst Transfer Size
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_BURST_COUNT_REG {
    uint32_t  all;
    struct  RTDMA_BURST_COUNT_BITS  bit;
};

struct RTDMA_SRC_BURST_STEP_BITS {      // bits description
    uint16_t SRCBURSTSTEP:16;           // 15:0 Source post-increment/decrement step size of a burst
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_SRC_BURST_STEP_REG {
    uint32_t  all;
    struct  RTDMA_SRC_BURST_STEP_BITS  bit;
};

struct RTDMA_DST_BURST_STEP_BITS {      // bits description
    uint16_t DSTBURSTSTEP:16;           // 15:0 Destination post-increment/decrement step size of a burst
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_DST_BURST_STEP_REG {
    uint32_t  all;
    struct  RTDMA_DST_BURST_STEP_BITS  bit;
};

struct RTDMA_TRANSFER_SIZE_BITS {       // bits description
    uint16_t TRANSFERSIZE:16;           // 15:0 These bits specify the number of bursts to transfer:
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_TRANSFER_SIZE_REG {
    uint32_t  all;
    struct  RTDMA_TRANSFER_SIZE_BITS  bit;
};

struct RTDMA_TRANSFER_COUNT_BITS {      // bits description
    uint16_t TRANSFERCOUNT:16;          // 15:0 These bits specify the current transfer counter value:
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_TRANSFER_COUNT_REG {
    uint32_t  all;
    struct  RTDMA_TRANSFER_COUNT_BITS  bit;
};

struct RTDMA_SRC_TRANSFER_STEP_BITS {   // bits description
    uint16_t SRCTRANSFERSTEP:16;        // 15:0 Source post-increment/decrement step size of a transfer
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_SRC_TRANSFER_STEP_REG {
    uint32_t  all;
    struct  RTDMA_SRC_TRANSFER_STEP_BITS  bit;
};

struct RTDMA_DST_TRANSFER_STEP_BITS {   // bits description
    uint16_t DSTTRANSFERSTEP:16;        // 15:0 Destination post-increment/decrement step size of a transfer
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_DST_TRANSFER_STEP_REG {
    uint32_t  all;
    struct  RTDMA_DST_TRANSFER_STEP_BITS  bit;
};

struct RTDMA_SRC_WRAP_SIZE_BITS {       // bits description
    uint16_t WRAPSIZE:16;               // 15:0 Number of bursts to transfer before wrapping
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_SRC_WRAP_SIZE_REG {
    uint32_t  all;
    struct  RTDMA_SRC_WRAP_SIZE_BITS  bit;
};

struct RTDMA_SRC_WRAP_COUNT_BITS {      // bits description
    uint16_t WRAPSIZE:16;               // 15:0 These bits indicate the current wrap counter value:
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_SRC_WRAP_COUNT_REG {
    uint32_t  all;
    struct  RTDMA_SRC_WRAP_COUNT_BITS  bit;
};

struct RTDMA_SRC_WRAP_STEP_BITS {       // bits description
    uint16_t WRAPSTEP:16;               // 15:0 Source post-increment/decrement step size for a wrap
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_SRC_WRAP_STEP_REG {
    uint32_t  all;
    struct  RTDMA_SRC_WRAP_STEP_BITS  bit;
};

struct RTDMA_DST_WRAP_SIZE_BITS {       // bits description
    uint16_t WRAPSIZE:16;               // 15:0 Number of bursts to transfer before wrapping
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_DST_WRAP_SIZE_REG {
    uint32_t  all;
    struct  RTDMA_DST_WRAP_SIZE_BITS  bit;
};

struct RTDMA_DST_WRAP_COUNT_BITS {      // bits description
    uint16_t WRAPSIZE:16;               // 15:0 These bits indicate the current wrap counter value:
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_DST_WRAP_COUNT_REG {
    uint32_t  all;
    struct  RTDMA_DST_WRAP_COUNT_BITS  bit;
};

struct RTDMA_DST_WRAP_STEP_BITS {       // bits description
    uint16_t WRAPSTEP:16;               // 15:0 Destination post-increment/decrement step size for a wrap
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_DST_WRAP_STEP_REG {
    uint32_t  all;
    struct  RTDMA_DST_WRAP_STEP_BITS  bit;
};

struct RTDMA_CHSECLAT1_BITS {           // bits description
    uint16_t ZONE:4;                    // 3:0 Channel owner zone
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t LINK:4;                    // 11:8 Channel owner Link
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t APILINK:4;                 // 19:16 Channel owner Clink
    uint16_t rsvd3:4;                   // 23:20 Reserved
    uint16_t STACK:4;                   // 27:24 Channel owner Stack
    uint16_t rsvd4:4;                   // 31:28 Reserved
};

union RTDMA_CHSECLAT1_REG {
    uint32_t  all;
    struct  RTDMA_CHSECLAT1_BITS  bit;
};

struct RTDMA_CHSECLAT2_BITS {           // bits description
    uint16_t SECURE:1;                  // 0 Channel SECURE Information
    uint16_t rsvd1:7;                   // 7:1 Reserved
    uint16_t PRIV:2;                    // 9:8 Channel PRIV information
    uint16_t rsvd2:6;                   // 15:10 Reserved
    uint16_t PRIVID:8;                  // 23:16 Channel PRIVID information
    uint16_t rsvd3:8;                   // 31:24 Reserved
};

union RTDMA_CHSECLAT2_REG {
    uint32_t  all;
    struct  RTDMA_CHSECLAT2_BITS  bit;
};

struct RTDMA_BURST_INTF_CTRL_BITS {     // bits description
    uint16_t BURSTCTRL:2;               // 1:0 Control Burst Interface operation
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_BURST_INTF_CTRL_REG {
    uint32_t  all;
    struct  RTDMA_BURST_INTF_CTRL_BITS  bit;
};

struct RTDMA_CHCFG_LOCK_BITS {          // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_CHCFG_LOCK_REG {
    uint32_t  all;
    struct  RTDMA_CHCFG_LOCK_BITS  bit;
};

struct RTDMA_CHCFG_COMMIT_BITS {        // bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_CHCFG_COMMIT_REG {
    uint32_t  all;
    struct  RTDMA_CHCFG_COMMIT_BITS  bit;
};

struct RTDMA_CH_REGS {
    union   RTDMA_MODE_REG                   MODE;                         // Mode Register
    union   RTDMA_CONTROL_REG                CONTROL;                      // Control Register
    union   RTDMA_BURST_SIZE_REG             BURST_SIZE;                   // Burst Size Register
    union   RTDMA_BURST_COUNT_REG            BURST_COUNT;                  // Burst Count Register
    union   RTDMA_SRC_BURST_STEP_REG         SRC_BURST_STEP;               // Source Burst Step Register
    union   RTDMA_DST_BURST_STEP_REG         DST_BURST_STEP;               // Destination Burst Step Register
    union   RTDMA_TRANSFER_SIZE_REG          TRANSFER_SIZE;                // Transfer Size Register
    union   RTDMA_TRANSFER_COUNT_REG         TRANSFER_COUNT;               // Transfer Count Register
    union   RTDMA_SRC_TRANSFER_STEP_REG      SRC_TRANSFER_STEP;            // Source Transfer Step Register
    union   RTDMA_DST_TRANSFER_STEP_REG      DST_TRANSFER_STEP;            // Destination Transfer Step Register
    union   RTDMA_SRC_WRAP_SIZE_REG          SRC_WRAP_SIZE;                // Source Wrap Size Register
    union   RTDMA_SRC_WRAP_COUNT_REG         SRC_WRAP_COUNT;               // Source Wrap Count Register
    union   RTDMA_SRC_WRAP_STEP_REG          SRC_WRAP_STEP;                // Source Wrap Step Register
    union   RTDMA_DST_WRAP_SIZE_REG          DST_WRAP_SIZE;                // Destination Wrap Size Register
    union   RTDMA_DST_WRAP_COUNT_REG         DST_WRAP_COUNT;               // Destination Wrap Count Register
    union   RTDMA_DST_WRAP_STEP_REG          DST_WRAP_STEP;                // Destination Wrap Step Register
    uint32_t                                 SRC_BEG_ADDR_SHADOW;          // Source Begin Address Shadow Register
    uint32_t                                 SRC_ADDR_SHADOW;              // Source Address Shadow Register
    uint32_t                                 SRC_BEG_ADDR_ACTIVE;          // Source Begin Address Active Register
    uint32_t                                 SRC_ADDR_ACTIVE;              // Source Address Active Register
    uint32_t                                 DST_BEG_ADDR_SHADOW;          // Destination Begin Address Shadow Register
    uint32_t                                 DST_ADDR_SHADOW;              // Destination Address Shadow Register
    uint32_t                                 DST_BEG_ADDR_ACTIVE;          // Destination Begin Address Active Register
    uint32_t                                 DST_ADDR_ACTIVE;              // Destination Address Active Register
    uint8_t                                  rsvd1[32];                    // Reserved
    union   RTDMA_CHSECLAT1_REG              CHSECLAT1;                    // Channel Security Details Latch Register
    union   RTDMA_CHSECLAT2_REG              CHSECLAT2;                    // Channel Security Details Latch Register
    uint8_t                                  rsvd2[24];                    // Reserved
    union   RTDMA_BURST_INTF_CTRL_REG        BURST_INTF_CTRL;              // Burst Interface Control Register
    uint8_t                                  rsvd3[92];                    // Reserved
    union   RTDMA_CHCFG_LOCK_REG             CHCFG_LOCK;                   // Channel Configuration Temporary Lock
    union   RTDMA_CHCFG_COMMIT_REG           CHCFG_COMMIT;                 // Channel Configuration Permanent Commit
};

struct RTDMA_FLTEMU_CONFIG_BITS {       // bits description
    uint16_t ENABLE:1;                  // 0 Fault emulation enable
    uint16_t DBL_BIT_INJ_EN:1;          // 1 Double bit injection enable
    uint16_t rsvd1:6;                   // 7:2 Reserved
    uint16_t KEY:8;                     // 15:8 Write Key
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_FLTEMU_CONFIG_REG {
    uint32_t  all;
    struct  RTDMA_FLTEMU_CONFIG_BITS  bit;
};

struct RTDMA_FLTEMU_ACCGRPSEL_BITS {    // bits description
    uint16_t CTRL_GROUP_SEL:8;          // 7:0 CTRL group selection
    uint16_t DATA_GROUP_SEL:8;          // 15:8 DATA READ1 control information bus selection
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union RTDMA_FLTEMU_ACCGRPSEL_REG {
    uint32_t  all;
    struct  RTDMA_FLTEMU_ACCGRPSEL_BITS  bit;
};

struct RTDMA_FLTEMU_BITSEL_BITS {       // bits description
    uint16_t BITSEL:7;                  // 6:0 Fault emulation bit selection
    uint16_t rsvd1:9;                   // 15:7 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_FLTEMU_BITSEL_REG {
    uint32_t  all;
    struct  RTDMA_FLTEMU_BITSEL_BITS  bit;
};

struct RTDMA_DIAG_REGS {
    union   RTDMA_FLTEMU_CONFIG_REG          FLTEMU_CONFIG;                // Fault emulation configuration registerr
    union   RTDMA_FLTEMU_ACCGRPSEL_REG       FLTEMU_ACCGRPSEL;             // Fault emulation access information group selection register
    union   RTDMA_FLTEMU_BITSEL_REG          FLTEMU_BITSEL;                // Fault emulation bitsel
    uint32_t                                 FLTEMU_ADDR;                  // Fault emulation access address register
};

struct RTDMA_SELFTEST_DIAG_DATA2_BITS { // bits description
    uint32_t SELFTEST_DIAG_DATA2:17;    // 16:0 Self test Diagnostics data 2
    uint16_t rsvd1:15;                  // 31:17 Reserved
};

union RTDMA_SELFTEST_DIAG_DATA2_REG {
    uint32_t  all;
    struct  RTDMA_SELFTEST_DIAG_DATA2_BITS  bit;
};

struct RTDMA_SELFTEST_DIAG_ECC_BITS {   // bits description
    uint16_t SELFTEST_DIAG_ECC:8;       // 7:0 Self test Diagnostics ECC
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union RTDMA_SELFTEST_DIAG_ECC_REG {
    uint32_t  all;
    struct  RTDMA_SELFTEST_DIAG_ECC_BITS  bit;
};

struct RTDMA_SELFTEST_DIAG_CONTROL_BITS {// bits description
    uint16_t DIAG_TEST_EN:4;            // 3:0 Diagnostic test enable
    uint16_t rsvd1:2;                   // 5:4 Reserved
    uint16_t DIAG_SAFETY_SEL:1;         // 6 Diagnostic safety selection
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t DIAG_CHECKER_SEL:2;        // 9:8 ECC checker selection
    uint16_t rsvd3:6;                   // 15:10 Reserved
    uint16_t DIAG_ECC_WIDTH:4;          // 19:16 Diagnostic ECC width
    uint16_t rsvd4:4;                   // 23:20 Reserved
    uint16_t DIAG_DATA_WIDTH:8;         // 31:24 Diagnostic Data width
};

union RTDMA_SELFTEST_DIAG_CONTROL_REG {
    uint32_t  all;
    struct  RTDMA_SELFTEST_DIAG_CONTROL_BITS  bit;
};

struct RTDMA_SELFTEST_DIAG_STATUS_BITS {// bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t DIAG_TEST_DONE:1;          // 1 Done self test
    uint16_t DIAG_TEST_FAIL:1;          // 2 Test failed
    uint16_t DIAG_FAIL_C_ERROR:1;       // 3 Diagnostic correctable error
    uint16_t DIAG_FAIL_UC_ERROR:1;      // 4 Diagnostic uncorrectable error
    uint16_t DIAG_FAIL_CHECK_TYPE:2;    // 6:5 Failed diagnostic check type
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t DIAG_FAIL_BIT_INDEX:8;     // 15:8 Error bit position
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union RTDMA_SELFTEST_DIAG_STATUS_REG {
    uint32_t  all;
    struct  RTDMA_SELFTEST_DIAG_STATUS_BITS  bit;
};

struct RTDMA_SELFTEST_DIAG_STATUS_CLR_BITS {// bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t DIAG_TEST_DONE:1;          // 1 Clear self test done status flag
    uint16_t DIAG_TEST_FAIL:1;          // 2 Clear test failed status flags
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union RTDMA_SELFTEST_DIAG_STATUS_CLR_REG {
    uint32_t  all;
    struct  RTDMA_SELFTEST_DIAG_STATUS_CLR_BITS  bit;
};

struct RTDMA_SELFTEST_REGS {
    uint32_t                                 SELFTEST_DIAG_DATA0;          // Diagnostics data register 0
    uint32_t                                 SELFTEST_DIAG_DATA1;          // Diagnostics data register 1
    union   RTDMA_SELFTEST_DIAG_DATA2_REG    SELFTEST_DIAG_DATA2;          // Diagnostics data register 2
    uint8_t                                  rsvd1[20];                    // Reserved
    union   RTDMA_SELFTEST_DIAG_ECC_REG      SELFTEST_DIAG_ECC;            // Diagnostics ECC
    uint8_t                                  rsvd2[4];                     // Reserved
    union   RTDMA_SELFTEST_DIAG_CONTROL_REG  SELFTEST_DIAG_CONTROL;        // Diagnostic test enable
    union   RTDMA_SELFTEST_DIAG_STATUS_REG   SELFTEST_DIAG_STATUS;         // Diagnostic status register
    union   RTDMA_SELFTEST_DIAG_STATUS_CLR_REG SELFTEST_DIAG_STATUS_CLR;   // Diagnostic status clear register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
