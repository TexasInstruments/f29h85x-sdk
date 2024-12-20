//###########################################################################
//
// FILE:    hwbf_debug_controller.h
//
// TITLE:   Definitions for the DEBUG_CONTROLLER registers.
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

#ifndef HWBF_DEBUG_CONTROLLER_H
#define HWBF_DEBUG_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// DEBUG_CONTROLLER Individual Register Bit Definitions:

struct DEBUG_CONTROLLER_DBG_CAP_BITS {  // bits description
    uint16_t REV_MIN:4;                 // 3:0 Minor Revision
    uint16_t REV_MAX:4;                 // 7:4 Major Revision
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:4;                   // 19:16 Reserved
    uint16_t TRIG_CHNS:2;               // 21:20 Number of Trigger Channels
    uint16_t TRIG_INPUT:1;              // 22 Number of Input Triggers
    uint16_t TRIG_OUTPUT:1;             // 23 Number of Output Triggers
    uint16_t SYS_EXE_REQ:1;             // 24 IDLE control
    uint16_t DBG_RESET_SUP:1;           // 25 CPU Reset support
    uint16_t rsvd3:6;                   // 31:26 Reserved
};

union DEBUG_CONTROLLER_DBG_CAP_REG {
    uint32_t  all;
    struct  DEBUG_CONTROLLER_DBG_CAP_BITS  bit;
};

struct DEBUG_CONTROLLER_DBG_PID_BITS {  // bits description
    uint16_t MINOR:6;                   // 5:0 Minor Revision
    uint16_t CUSTOM:2;                  // 7:6 Custom Field
    uint16_t MAJOR:3;                   // 10:8 Major Revision
    uint16_t RTL:5;                     // 15:11 RTL Revision
    uint16_t FUNC:12;                   // 27:16 Functional Group
    uint16_t BUSINESS_UNIT:2;           // 29:28 Business Unit
    uint16_t SCHEME:2;                  // 31:30 Scheme Version
};

union DEBUG_CONTROLLER_DBG_PID_REG {
    uint32_t  all;
    struct  DEBUG_CONTROLLER_DBG_PID_BITS  bit;
};

struct DEBUG_CONTROLLER_DBG_CONNECT_BITS {// bits description
    uint16_t CONNECTED:2;               // 1:0 Debug Connected
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t CONNECT_PATTERN:16;        // 31:16 Write Key pattern
};

union DEBUG_CONTROLLER_DBG_CONNECT_REG {
    uint32_t  all;
    struct  DEBUG_CONTROLLER_DBG_CONNECT_BITS  bit;
};

struct DEBUG_CONTROLLER_DBG_CNTL0_BITS {// bits description
    uint16_t EXE_CMD:3;                 // 2:0 Execution Command
    uint16_t EXE_CMD_LD:1;              // 3 Load Enable for Execution Command
    uint16_t EXE_MODE:2;                // 5:4 Execution Mode
    uint16_t EXE_IGNORE_HPI:1;          // 6 Ignore HPI
    uint16_t EXE_IGNORE_DBGM:1;         // 7 Ignore DBGM
    uint16_t EXE_SWBP_EN:1;             // 8 Enable Softaware Breakpoints
    uint16_t EXE_HWBP_EN:1;             // 9 Enable Hardware Breakpoints
    uint16_t EXT_DBG_EN:1;              // 10 Enable External Triggers
    uint16_t EXT_HALT_EN:1;             // 11 Enable External Trigger  HALTs
    uint16_t EXT_RUN_EN:1;              // 12 Enable Synchronous RUN
    uint16_t EXE_D_INT:1;               // 13 Debug Interrupts
    uint16_t EXE_D_NMI:1;               // 14 Debug NMI
    uint16_t GUI_PC_MOD_RESTART:1;      // 15 Debugger Restart PC modification
    uint16_t DBG_IDLE_WAKEUP:1;         // 16 IDLE wakeup request
    uint16_t rsvd1:15;                  // 31:17 Reserved
};

union DEBUG_CONTROLLER_DBG_CNTL0_REG {
    uint32_t  all;
    struct  DEBUG_CONTROLLER_DBG_CNTL0_BITS  bit;
};

struct DEBUG_CONTROLLER_DBG_CNTL1_BITS {// bits description
    uint16_t FORCE_CPU_RESET:1;         // 0 Force CPU Reset
    uint16_t CPU_RST_LD:1;              // 1 Load Enable for FORCE_CPU_RESET
    uint16_t FORCE_READY:1;             // 2 Force CPU pipeline ready
    uint16_t FORCE_READY_LD:1;          // 3 Load Enable for FORCE_READY
    uint16_t CPU_BLOCK_PIN_RESET:1;     // 4 Block CPU Pin Reset
    uint16_t CPU_BLOCK_RST_LD:1;        // 5 Load enable for CPU_BLOCK_PIN_RESET
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DEBUG_CONTROLLER_DBG_CNTL1_REG {
    uint32_t  all;
    struct  DEBUG_CONTROLLER_DBG_CNTL1_BITS  bit;
};

struct DEBUG_CONTROLLER_DBG_STAT_BITS { // bits description
    uint16_t EXE_STAT:2;                // 1:0 Execution Status
    uint16_t RESTART:1;                 // 2 Execution Resumed Status bit
    uint16_t rsvd1:3;                   // 5:3 Reserved
    uint16_t HALT_IN_E7:1;              // 6 HALT condition seen in E7 pipeline phase
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t HALT_SWBP:1;               // 8 HALTed due to Software breakpoint
    uint16_t HALT_HWBP:1;               // 9 HALTed due to Hardware breakpoint
    uint16_t HALT_CPU_RESET:1;          // 10 Reserved
    uint16_t HALT_STEP:1;               // 11 HALTed due to Single Step operation
    uint16_t HALT_USER:1;               // 12 HALTed due to user request
    uint16_t HALT_EXT_HALT:1;           // 13 HALTed due to external trigger
    uint16_t HALT_WP:1;                 // 14 HALTed due to a Watchpoint
    uint16_t HALT_IN_IDS:1;             // 15 Reserved
    uint16_t STAT_PRIV_DBGM:1;          // 16 DBGM status
    uint16_t STAT_PRIV_HPI:1;           // 17 HPI status
    uint16_t STAT_EXT_RUN_SEEN:1;       // 18 External RUN request seen
    uint16_t STAT_EXT_HALT_SEEN:1;      // 19 External HALT request seen
    uint16_t STAT_PIPE_READY:1;         // 20 CPU Pipeline advancement status
    uint16_t STAT_CLK_SEEN:1;           // 21 CPU has seen a Clock
    uint16_t RESET_OCC:1;               // 22 CPU has seen a Reset
    uint16_t RESET_ACT:1;               // 23 CPU reset active
    uint16_t FAULT_SEEN:1;              // 24 CPU entered a FAULT state
    uint16_t IDLE_IN_R1:1;              // 25 IDLE instruction in R1 pipeline phase
    uint16_t IDLE_IN_E7:1;              // 26 IDLE instruction in E7 pipeline phase
    uint16_t rsvd3:5;                   // 31:27 Reserved
};

union DEBUG_CONTROLLER_DBG_STAT_REG {
    uint32_t  all;
    struct  DEBUG_CONTROLLER_DBG_STAT_BITS  bit;
};

struct DEBUG_CONTROLLER_DBG_MEM_CNTL_BITS {// bits description
    uint16_t MEM_RW:1;                  // 0 Read Write Select
    uint16_t MEM_ADDR_INC:1;            // 1 Address Increment mode
    uint16_t MEM_IGNORE_DBGM:1;         // 2 Ignore DBGM for memory access
    uint16_t MEM_IGNORE_HPI:1;          // 3 Ignore HPI for memory access
    uint16_t ACC_TYPE:3;                // 6:4 Debug Access Type
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t MEM_ACC_SIZE:3;            // 10:8 Debug access size
    uint16_t DBG_ACCESS_EN:1;           // 11 Enable Debug Access
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t rsvd3:2;                   // 17:16 Reserved
    uint16_t LOAD_MEMACC_FIELDS:1;      // 18 Load enable Debug Access fields
    uint16_t CLR_MEM_STATUS:1;          // 19 Clear Debug access fault status bits
    uint16_t MEM_ACC_STATUS:4;          // 23:20 Debug access status
    uint16_t MEM_ACC_BUS_ERROR:1;       // 24 Transaction fault on access
    uint16_t MEM_ACC_SEC_ERROR:1;       // 25 Security violation on access
    uint16_t MEM_ACC_SEQUENCE_ERROR:1;  // 26 Access Sequence violation during bulk access
    uint16_t rsvd4:5;                   // 31:27 Reserved
};

union DEBUG_CONTROLLER_DBG_MEM_CNTL_REG {
    uint32_t  all;
    struct  DEBUG_CONTROLLER_DBG_MEM_CNTL_BITS  bit;
};

struct DEBUG_CONTROLLER_DBG_VIS_READ_P0_BITS {// bits description
    uint16_t D2_FSM:6;                  // 5:0 D2 FSM states
    uint16_t DELAY_DISC_REQ:1;          // 6 Delay discontinuity request
    uint16_t EXE_FAULT:1;               // 7 Fault from exe unit
    uint16_t FETCH_FSM:3;               // 10:8 Fetch FSM states
    uint16_t D2_ZONE:2;                 // 12:11 D2 Zone ID
    uint16_t D2_STACK:3;                // 15:13 D2 Stack ID
    uint16_t D2_LINK:4;                 // 19:16 D2 Link ID
    uint16_t D2_READY:1;                // 20 D2 ready
    uint16_t R1_READY:1;                // 21 R1 ready
    uint16_t MEMRD1_MPROT_BUFF_ACC:1;   // 22 Memread1 memory protection buffer access
    uint16_t MEMRD2_MPROT_BUFF_ACC:1;   // 23 Memread2 memory protection buffer access
    uint16_t VIS_PORT0:8;               // 31:24 Debug Visibility Port0
};

union DEBUG_CONTROLLER_DBG_VIS_READ_P0_REG {
    uint32_t  all;
    struct  DEBUG_CONTROLLER_DBG_VIS_READ_P0_BITS  bit;
};

struct C29_DEBUG_CNTL_REGS {
    union   DEBUG_CONTROLLER_DBG_CAP_REG     DBG_CAP;                      // Debug Capability
    union   DEBUG_CONTROLLER_DBG_PID_REG     DBG_PID;                      // Debug Part ID
    union   DEBUG_CONTROLLER_DBG_CONNECT_REG DBG_CONNECT;                  // Debug Connect
    union   DEBUG_CONTROLLER_DBG_CNTL0_REG   DBG_CNTL0;                    // Debug Execution Control 0
    union   DEBUG_CONTROLLER_DBG_CNTL1_REG   DBG_CNTL1;                    // Debug Execution Control 1
    union   DEBUG_CONTROLLER_DBG_STAT_REG    DBG_STAT;                     // Debug Status
    union   DEBUG_CONTROLLER_DBG_MEM_CNTL_REG DBG_MEM_CNTL;                // Debug  Access control
    uint8_t                                  rsvd1[36];                    // Reserved
    uint32_t                                 DBG_MEM_ADDR0;                // Debyg Acess Address
    uint8_t                                  rsvd2[4];                     // Reserved
    uint32_t                                 DBG_MEM_DATA0;                // Debug Access Data 0
    uint32_t                                 DBG_MEM_DATA1;                // Debug Access Data 1
    union   DEBUG_CONTROLLER_DBG_VIS_READ_P0_REG DBG_VIS_READ_P0;          // Debug Visibility Read Port 0
    uint32_t                                 DBG_VIS_READ_P1;              // Debug Visibility Read Port 1
    uint32_t                                 DBG_VIS_CLR_P1;               // Debug Visibility Port 1 Clear
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
