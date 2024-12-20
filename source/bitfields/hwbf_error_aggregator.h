//###########################################################################
//
// FILE:    hwbf_error_aggregator.h
//
// TITLE:   Definitions for the ERROR_AGGREGATOR registers.
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

#ifndef HWBF_ERROR_AGGREGATOR_H
#define HWBF_ERROR_AGGREGATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// ERROR_AGGREGATOR Individual Register Bit Definitions:

struct ERROR_AGGREGATOR_HSM_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t rsvd2:6;                   // 13:8 Reserved
    uint16_t ACC_TYPE_READ:1;           // 14 Access type Read
    uint16_t ACC_TYPE_WRITE:1;          // 15 Access type write
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 High Priority error set by software
};

union ERROR_AGGREGATOR_HSM_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_HSM_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_HSM_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t rsvd2:6;                   // 13:8 Reserved
    uint16_t ACC_TYPE_READ:1;           // 14 Access type Read force
    uint16_t ACC_TYPE_WRITE:1;          // 15 Access type write force
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 Force high priority software error
};

union ERROR_AGGREGATOR_HSM_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_HSM_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_HSM_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t rsvd2:6;                   // 13:8 Reserved
    uint16_t ACC_TYPE_READ:1;           // 14 Access type Read clear
    uint16_t ACC_TYPE_WRITE:1;          // 15 Access type write clear
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_HSM_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_HSM_ERROR_TYPE_CLR_BITS  bit;
};

struct HSM_ERROR_AGGREGATOR_CONFIG_REGS {
    uint32_t                                 HSM_HIGHPRIO_ERROR_ADDRESS;   // High Priority Error address register
    uint32_t                                 HSM_LOWPRIO_ERROR_ADDRESS;    // Low Priority Error address register
    union   ERROR_AGGREGATOR_HSM_ERROR_TYPE_REG HSM_ERROR_TYPE;            // Error Type Register
    union   ERROR_AGGREGATOR_HSM_ERROR_TYPE_FRC_REG HSM_ERROR_TYPE_FRC;    // Error Type Force Register
    union   ERROR_AGGREGATOR_HSM_ERROR_TYPE_CLR_REG HSM_ERROR_TYPE_CLR;    // Error Type Clear Register
};

struct ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6  Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation force.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error force.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error force
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error force
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6  Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error force
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error force
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error force
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error force
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 Force high priority software error
};

union ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation clear.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error clear.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error clear
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error clear
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6  Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error clear
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error clear
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error clear
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error clear
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error
    uint16_t WARNISP:1;                 // 24 warnisp
    uint16_t MAXISP:1;                  // 25 maxisp
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock/key error
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error force
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error force
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error force
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error force
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error force
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error force
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error force
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error force
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error force
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error force
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error force
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error force
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error force
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error force
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error force
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error force
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error force
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error force
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error force
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error force
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error force
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error force
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error force
    uint16_t WARNISP:1;                 // 24 warnisp force
    uint16_t MAXISP:1;                  // 25 maxisp force
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation force
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error force
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error force
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock key error force
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error clear
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error clear
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error clear
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error clear
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error clear
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error clear
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error clear
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error clear
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error clear
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error clear
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error clear
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error clear
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error clear
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error clear
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error clear
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error clear
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error clear
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error clear
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error clear
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error clear
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error clear
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error clear
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error clear
    uint16_t WARNISP:1;                 // 24 warnisp clear
    uint16_t MAXISP:1;                  // 25 maxisp clear
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation clear
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error clear
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error clear
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock key error clear
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6  Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation force.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error force.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error force
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error force
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6  Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error force
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error force
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error force
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error force
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 Force high priority software error
};

union ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation clear.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error clear.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error clear
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error clear
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6  Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error clear
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error clear
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error clear
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error clear
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error
    uint16_t WARNISP:1;                 // 24 warnisp
    uint16_t MAXISP:1;                  // 25 maxisp
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock/key error
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error force
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error force
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error force
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error force
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error force
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error force
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error force
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error force
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error force
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error force
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error force
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error force
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error force
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error force
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error force
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error force
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error force
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error force
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error force
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error force
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error force
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error force
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error force
    uint16_t WARNISP:1;                 // 24 warnisp force
    uint16_t MAXISP:1;                  // 25 maxisp force
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation force
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error force
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error force
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock key error force
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error clear
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error clear
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error clear
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error clear
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error clear
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error clear
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error clear
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error clear
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error clear
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error clear
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error clear
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error clear
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error clear
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error clear
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error clear
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error clear
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error clear
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error clear
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error clear
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error clear
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error clear
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error clear
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error clear
    uint16_t WARNISP:1;                 // 24 warnisp clear
    uint16_t MAXISP:1;                  // 25 maxisp clear
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation clear
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error clear
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error clear
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock key error clear
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6  Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation force.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error force.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error force
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error force
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6  Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error force
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error force
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error force
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error force
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 Force high priority software error
};

union ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t INSTR_SECURITY_VIO:1;      // 0 Instruction packet security violation clear.
    uint16_t SEC_ENTRY_VIO:1;           // 1 Secure entry and linear code crossing error clear.
    uint16_t SEC_EXIT_VIO:1;            // 2 Secure exit error clear
    uint16_t MAX_PSP_ERR:1;             // 3  MAX PSP error clear
    uint16_t ACC_TIMEOUT_ERR:1;         // 4  Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6  Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t WARN_PSP_ERR:1;            // 8 Warn PSP error clear
    uint16_t SW_BREAKPOINT_ERR:1;       // 9 Software brakepoint error clear
    uint16_t ILLEGAL_INSTRUCTION:1;     // 10 Illegal instruction error clear
    uint16_t INSTRUCTION_TIMEOUT:1;     // 11 Instruction timeout error clear
    uint16_t rsvd1:4;                   // 15:12 Reserved
    uint16_t rsvd2:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error force
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t UNALIGNED_ADDR_ERR:1;      // 8 Unaligned address error clear
    uint16_t rsvd2:7;                   // 15:9 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error
    uint16_t WARNISP:1;                 // 24 warnisp
    uint16_t MAXISP:1;                  // 25 maxisp
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock/key error
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error force
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error force
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error force
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error force
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error force
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error force
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error force
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error force
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error force
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error force
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error force
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error force
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error force
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error force
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error force
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error force
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error force
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error force
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error force
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error force
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error force
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error force
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error force
    uint16_t WARNISP:1;                 // 24 warnisp force
    uint16_t MAXISP:1;                  // 25 maxisp force
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation force
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error force
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error force
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock key error force
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t MAIN_ISR_ENTRY_ERR:1;      // 0 Main ISR entry error clear
    uint16_t MAIN_VECT_CERR:1;          // 1 Main Correctable vector error clear
    uint16_t MAIN_VECT_UNCERR:1;        // 2 Main Uncorrectable vector error clear
    uint16_t MAIN_INTERRUPT_RETURN_ERR:1; // 3 Main Interrupt return error clear
    uint16_t INT_ISR_ENTRY_ERR:1;       // 4 INT ISR entry error clear
    uint16_t INT_VECT_CERR:1;           // 5 INT Correctable vector error clear
    uint16_t INT_VECT_UNCERR:1;         // 6 INT Uncorrectable vector error clear
    uint16_t INT_INTERRUPT_RETURN_ERR:1; // 7 INT INTerrupt return error clear
    uint16_t RTINT_ISR_ENTRY_ERR:1;     // 8 RTINT ISR entry error clear
    uint16_t RTINT_VECT_CERR:1;         // 9 RTINT Correctable vector error clear
    uint16_t RTINT_VECT_UNCERR:1;       // 10 RTINT Uncorrectable vector error clear
    uint16_t RTINT_INTERRUPT_RETURN_ERR:1; // 11 RTINT Interrupt return error clear
    uint16_t RTINT_CONTEXT_RESTORE_VECT_CERR:1; // 12 RTINT Context restore Correctable vector error clear
    uint16_t RTINT_CONTEXT_RESTORE_VECT_UNCERR:1; // 13 RTINT Context restore Uncorrectable vector error clear
    uint16_t rsvd1:1;                   // 14 Reserved
    uint16_t NMI_MAXISP_ERR:1;          // 15 NMI MAXISP error clear
    uint16_t NMI_ISR_ENTRY_ERR:1;       // 16 NMI ISR entry error clear
    uint16_t NMI_VECT_CERR:1;           // 17 NMI Correctable vector error clear
    uint16_t NMI_VECT_UNCERR:1;         // 18 NMI Uncorrectable vector error clear
    uint16_t NMI_INTERRUPT_RETURN_ERR:1; // 19 NMI Interrupt return error clear
    uint16_t NMI_CONTEXT_RESTORE_VECT_CERR:1; // 20 NMI Context restore Correctable vector error clear
    uint16_t NMI_CONTEXT_RESTORE_VECT_UNCERR:1; // 21 NMI Context restore Uncorrectable vector error clear
    uint16_t VECT_CERR:1;               // 22 Vector Correctable error clear
    uint16_t VECT_UNCERR:1;             // 23 Vector Uncorrectable error clear
    uint16_t WARNISP:1;                 // 24 warnisp clear
    uint16_t MAXISP:1;                  // 25 maxisp clear
    uint16_t PIPE_SECURITY_VIO:1;       // 26 PIPE security violation clear
    uint16_t REG_PARITY_ERR:1;          // 27 PIPE Reg parity error clear
    uint16_t REG_PARITY_DIAG_ERR:1;     // 28 PIPE Register parity diag error clear
    uint16_t PIPE_LOCK_KEY_ERR:1;       // 29 PIPE Lock key error clear
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t CERR:1;                    // 7 Correctable error
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Low Priority error set by software
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation force
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error force
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error force
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t CERR:1;                    // 7 Correctable error force
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 Force low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t SECURITY_VIO:1;            // 0 Security violation clear
    uint16_t rsvd1:3;                   // 3:1 Reserved
    uint16_t ACC_TIMEOUT_ERR:1;         // 4 Access timeout error clear
    uint16_t ACC_ACK_ERR:1;             // 5 Access ACK error clear
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t CERR:1;                    // 7 Correctable error clear
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t LP_SOFTWARE_ERR:1;         // 30 clear low priority software error
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_SSU_ERROR_TYPE_BITS {// bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CPU1_SSU_MMR_ACCESS_ERROR:1; // 1 CPU1_SSU_MMR_ACCESS_ERROR
    uint16_t CPU2_SSU_MMR_ACCESS_ERROR:1; // 2 CPU2_SSU_MMR_ACCESS_ERROR
    uint16_t CPU3_SSU_MMR_ACCESS_ERROR:1; // 3 CPU3_SSU_MMR_ACCESS_ERROR
    uint16_t rsvd2:3;                   // 6:4 Reserved
    uint16_t MODE_INVALID:1;            // 7 BANKMAP, SECVALID, BANKMODE, SSUMODE invalid
    uint16_t FLC1_ERROR_STS:1;          // 8 FLC1_ERROR_STS
    uint16_t FLC1_ERROR_TYPE:3;         // 11:9 FLC1_ERROR_TYPE
    uint16_t FLC1_MMR_ACCESS_ERROR:1;   // 12 FLC1_MMR_ACCESS_ERROR
    uint16_t FLC2_ERROR_STS:1;          // 13 FLC2_ ERROR_STS
    uint32_t FLC2_ERROR_TYPE:3;         // 16:14 FLC2_ERROR_TYPE
    uint16_t FLC2_MMR_ACCESS_ERROR:1;   // 17 FLC2_MMR_ACCESS_ERROR
    uint16_t rsvd3:12;                  // 29:18 Reserved
    uint16_t rsvd4:1;                   // 30 Reserved
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_SSU_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_SSU_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_SSU_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CPU1_SSU_MMR_ACCESS_ERROR:1; // 1 CPU1_SSU_MMR_ACCESS_ERROR force
    uint16_t CPU2_SSU_MMR_ACCESS_ERROR:1; // 2 CPU2_SSU_MMR_ACCESS_ERROR force
    uint16_t CPU3_SSU_MMR_ACCESS_ERROR:1; // 3 CPU3_SSU_MMR_ACCESS_ERROR force
    uint16_t rsvd2:3;                   // 6:4 Reserved
    uint16_t MODE_INVALID:1;            // 7 BANKMAP, SECVALID, BANKMODE, SSUMODE invalid  force
    uint16_t FLC1_ERROR_STS:1;          // 8 FLC1_ERROR_STS  force
    uint16_t FLC1_ERROR_TYPE:3;         // 11:9 FLC1_ERROR_TYPE force
    uint16_t FLC1_MMR_ACCESS_ERROR:1;   // 12 FLC1_MMR_ACCESS_ERROR force
    uint16_t FLC2_ERROR_STS:1;          // 13 FLC2_ ERROR_STS force
    uint32_t FLC2_ERROR_TYPE:3;         // 16:14 FLC2_ERROR_TYPE force
    uint16_t FLC2_MMR_ACCESS_ERROR:1;   // 17 FLC2_MMR_ACCESS_ERROR force
    uint16_t rsvd3:12;                  // 29:18 Reserved
    uint16_t rsvd4:1;                   // 30 Reserved
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_SSU_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_SSU_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_SSU_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CPU1_SSU_MMR_ACCESS_ERROR:1; // 1 CPU1_SSU_MMR_ACCESS_ERROR Clear
    uint16_t CPU2_SSU_MMR_ACCESS_ERROR:1; // 2 CPU2_SSU_MMR_ACCESS_ERROR Clear
    uint16_t CPU3_SSU_MMR_ACCESS_ERROR:1; // 3 CPU3_SSU_MMR_ACCESS_ERROR Clear
    uint16_t rsvd2:3;                   // 6:4 Reserved
    uint16_t MODE_INVALID:1;            // 7 BANKMAP, SECVALID, BANKMODE, SSUMODE invalid  Clear
    uint16_t FLC1_ERROR_STS:1;          // 8 FLC1_ERROR_STS  Clear
    uint16_t FLC1_ERROR_TYPE:3;         // 11:9 FLC1_ERROR_TYPE Clear
    uint16_t FLC1_MMR_ACCESS_ERROR:1;   // 12 FLC1_MMR_ACCESS_ERROR Clear
    uint16_t FLC2_ERROR_STS:1;          // 13 FLC2_ ERROR_STS Clear
    uint32_t FLC2_ERROR_TYPE:3;         // 16:14 FLC2_ERROR_TYPE Clear
    uint16_t FLC2_MMR_ACCESS_ERROR:1;   // 17 FLC2_MMR_ACCESS_ERROR Clear
    uint16_t rsvd3:12;                  // 29:18 Reserved
    uint16_t rsvd4:1;                   // 30 Reserved
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_SSU_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_SSU_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_BITS {// bits description
    uint16_t rsvd1:6;                   // 5:0 Reserved
    uint16_t UNCERR:1;                  // 6 Uncorrectable error
    uint16_t rsvd2:9;                   // 15:7 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t rsvd4:1;                   // 30 Reserved
    uint16_t HP_SOFTWARE_ERR:1;         // 31 high priority error set by software
};

union ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_BITS  bit;
};

struct ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_FRC_BITS {// bits description
    uint16_t rsvd1:6;                   // 5:0 Reserved
    uint16_t UNCERR:1;                  // 6 Uncorrectable error force
    uint16_t rsvd2:9;                   // 15:7 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t rsvd4:1;                   // 30 Reserved
    uint16_t HP_SOFTWARE_ERR:1;         // 31 force high priority software error
};

union ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_FRC_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_FRC_BITS  bit;
};

struct ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_CLR_BITS {// bits description
    uint16_t rsvd1:6;                   // 5:0 Reserved
    uint16_t UNCERR:1;                  // 6 Uncorrectable error clear
    uint16_t rsvd2:9;                   // 15:7 Reserved
    uint16_t rsvd3:14;                  // 29:16 Reserved
    uint16_t rsvd4:1;                   // 30 Reserved
    uint16_t HP_SOFTWARE_ERR:1;         // 31 clear high priority software error
};

union ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_CLR_REG {
    uint32_t  all;
    struct  ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_CLR_BITS  bit;
};

struct ERROR_AGGREGATOR_CONFIG_REGS {
    uint32_t                                 CPU1_PR_HIGHPRIO_ERROR_ADDRESS; // CPU1 PR Error aggregator High Priority Error address register
    uint32_t                                 CPU1_PR_LOWPRIO_ERROR_ADDRESS; // CPU1 PR Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_REG CPU1_PR_ERROR_TYPE;    // CPU1 PR Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_FRC_REG CPU1_PR_ERROR_TYPE_FRC; // CPU1 PR Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU1_PR_ERROR_TYPE_CLR_REG CPU1_PR_ERROR_TYPE_CLR; // CPU1 PR Error aggregator Error Type Clear Register
    uint32_t                                 CPU1_PR_PC;                   // CPU1 PR Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd1[40];                    // Reserved
    uint32_t                                 CPU1_DR1_HIGHPRIO_ERROR_ADDRESS; // CPU1 DR1 Error aggregator High Priority Error address register
    uint32_t                                 CPU1_DR1_LOWPRIO_ERROR_ADDRESS; // CPU1 DR1 Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_REG CPU1_DR1_ERROR_TYPE;  // CPU1 DR1 Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_FRC_REG CPU1_DR1_ERROR_TYPE_FRC; // CPU1 DR1 Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU1_DR1_ERROR_TYPE_CLR_REG CPU1_DR1_ERROR_TYPE_CLR; // CPU1 DR1 Error aggregator Error Type Clear Register
    uint32_t                                 CPU1_DR1_PC;                  // CPU1 DR1 Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd2[40];                    // Reserved
    uint32_t                                 CPU1_DR2_HIGHPRIO_ERROR_ADDRESS; // CPU1 DR2 Error aggregator High Priority Error address register
    uint32_t                                 CPU1_DR2_LOWPRIO_ERROR_ADDRESS; // CPU1 DR2 Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_REG CPU1_DR2_ERROR_TYPE;  // CPU1 DR2 Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_FRC_REG CPU1_DR2_ERROR_TYPE_FRC; // CPU1 DR2 Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU1_DR2_ERROR_TYPE_CLR_REG CPU1_DR2_ERROR_TYPE_CLR; // CPU1 DR2 Error aggregator Error Type Clear Register
    uint32_t                                 CPU1_DR2_PC;                  // CPU1 DR2 Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd3[40];                    // Reserved
    uint32_t                                 CPU1_DW_HIGHPRIO_ERROR_ADDRESS; // CPU1 DW Error aggregator High Priority Error address register
    uint32_t                                 CPU1_DW_LOWPRIO_ERROR_ADDRESS; // CPU1 DW Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_REG CPU1_DW_ERROR_TYPE;    // CPU1 DW Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_FRC_REG CPU1_DW_ERROR_TYPE_FRC; // CPU1 DW Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU1_DW_ERROR_TYPE_CLR_REG CPU1_DW_ERROR_TYPE_CLR; // CPU1 DW Error aggregator Error Type Clear Register
    uint32_t                                 CPU1_DW_PC;                   // CPU1 DW Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd4[40];                    // Reserved
    uint32_t                                 CPU1_INT_HIGHPRIO_ERROR_ADDRESS; // CPU1 INT Error aggregator High Priority Error address register
    uint32_t                                 CPU1_INT_LOWPRIO_ERROR_ADDRESS; // CPU1 INT Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_REG CPU1_INT_ERROR_TYPE;  // CPU1 INT Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_FRC_REG CPU1_INT_ERROR_TYPE_FRC; // CPU1 INT Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU1_INT_ERROR_TYPE_CLR_REG CPU1_INT_ERROR_TYPE_CLR; // CPU1 INT Error aggregator Error Type Clear Register
    uint32_t                                 CPU1_INT_PC;                  // CPU1 INT Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd5[40];                    // Reserved
    uint32_t                                 CPU2_PR_HIGHPRIO_ERROR_ADDRESS; // CPU2 PR Error aggregator High Priority Error address register
    uint32_t                                 CPU2_PR_LOWPRIO_ERROR_ADDRESS; // CPU2 PR Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_REG CPU2_PR_ERROR_TYPE;    // CPU2 PR Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_FRC_REG CPU2_PR_ERROR_TYPE_FRC; // CPU2 PR Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU2_PR_ERROR_TYPE_CLR_REG CPU2_PR_ERROR_TYPE_CLR; // CPU2 PR Error aggregator Error Type Clear Register
    uint32_t                                 CPU2_PR_PC;                   // CPU2 PR Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd6[40];                    // Reserved
    uint32_t                                 CPU2_DR1_HIGHPRIO_ERROR_ADDRESS; // CPU2 DR1 Error aggregator High Priority Error address register
    uint32_t                                 CPU2_DR1_LOWPRIO_ERROR_ADDRESS; // CPU2 DR1 Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_REG CPU2_DR1_ERROR_TYPE;  // CPU2 DR1 Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_FRC_REG CPU2_DR1_ERROR_TYPE_FRC; // CPU2 DR1 Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU2_DR1_ERROR_TYPE_CLR_REG CPU2_DR1_ERROR_TYPE_CLR; // CPU2 DR1 Error aggregator Error Type Clear Register
    uint32_t                                 CPU2_DR1_PC;                  // CPU2 DR1 Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd7[40];                    // Reserved
    uint32_t                                 CPU2_DR2_HIGHPRIO_ERROR_ADDRESS; // CPU2 DR2 Error aggregator High Priority Error address register
    uint32_t                                 CPU2_DR2_LOWPRIO_ERROR_ADDRESS; // CPU2 DR2 Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_REG CPU2_DR2_ERROR_TYPE;  // CPU2 DR2 Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_FRC_REG CPU2_DR2_ERROR_TYPE_FRC; // CPU2 DR2 Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU2_DR2_ERROR_TYPE_CLR_REG CPU2_DR2_ERROR_TYPE_CLR; // CPU2 DR2 Error aggregator Error Type Clear Register
    uint32_t                                 CPU2_DR2_PC;                  // CPU2 DR2 Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd8[40];                    // Reserved
    uint32_t                                 CPU2_DW_HIGHPRIO_ERROR_ADDRESS; // CPU2 DW Error aggregator High Priority Error address register
    uint32_t                                 CPU2_DW_LOWPRIO_ERROR_ADDRESS; // CPU2 DW Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_REG CPU2_DW_ERROR_TYPE;    // CPU2 DW Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_FRC_REG CPU2_DW_ERROR_TYPE_FRC; // CPU2 DW Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU2_DW_ERROR_TYPE_CLR_REG CPU2_DW_ERROR_TYPE_CLR; // CPU2 DW Error aggregator Error Type Clear Register
    uint32_t                                 CPU2_DW_PC;                   // CPU2 DW Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd9[40];                    // Reserved
    uint32_t                                 CPU2_INT_HIGHPRIO_ERROR_ADDRESS; // CPU2 INT Error aggregator High Priority Error address register
    uint32_t                                 CPU2_INT_LOWPRIO_ERROR_ADDRESS; // CPU2 INT Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_REG CPU2_INT_ERROR_TYPE;  // CPU2 INT Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_FRC_REG CPU2_INT_ERROR_TYPE_FRC; // CPU2 INT Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU2_INT_ERROR_TYPE_CLR_REG CPU2_INT_ERROR_TYPE_CLR; // CPU2 INT Error aggregator Error Type Clear Register
    uint32_t                                 CPU2_INT_PC;                  // CPU2 INT Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd10[40];                   // Reserved
    uint32_t                                 CPU3_PR_HIGHPRIO_ERROR_ADDRESS; // CPU3 PR Error aggregator High Priority Error address register
    uint32_t                                 CPU3_PR_LOWPRIO_ERROR_ADDRESS; // CPU3 PR Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_REG CPU3_PR_ERROR_TYPE;    // CPU3 PR Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_FRC_REG CPU3_PR_ERROR_TYPE_FRC; // CPU3 PR Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU3_PR_ERROR_TYPE_CLR_REG CPU3_PR_ERROR_TYPE_CLR; // CPU3 PR Error aggregator Error Type Clear Register
    uint32_t                                 CPU3_PR_PC;                   // CPU3 PR Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd11[40];                   // Reserved
    uint32_t                                 CPU3_DR1_HIGHPRIO_ERROR_ADDRESS; // CPU3 DR1 Error aggregator High Priority Error address register
    uint32_t                                 CPU3_DR1_LOWPRIO_ERROR_ADDRESS; // CPU3 DR1 Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_REG CPU3_DR1_ERROR_TYPE;  // CPU3 DR1 Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_FRC_REG CPU3_DR1_ERROR_TYPE_FRC; // CPU3 DR1 Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU3_DR1_ERROR_TYPE_CLR_REG CPU3_DR1_ERROR_TYPE_CLR; // CPU3 DR1 Error aggregator Error Type Clear Register
    uint32_t                                 CPU3_DR1_PC;                  // CPU3 DR1 Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd12[40];                   // Reserved
    uint32_t                                 CPU3_DR2_HIGHPRIO_ERROR_ADDRESS; // CPU3 DR2 Error aggregator High Priority Error address register
    uint32_t                                 CPU3_DR2_LOWPRIO_ERROR_ADDRESS; // CPU3 DR2 Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_REG CPU3_DR2_ERROR_TYPE;  // CPU3 DR2 Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_FRC_REG CPU3_DR2_ERROR_TYPE_FRC; // CPU3 DR2 Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU3_DR2_ERROR_TYPE_CLR_REG CPU3_DR2_ERROR_TYPE_CLR; // CPU3 DR2 Error aggregator Error Type Clear Register
    uint32_t                                 CPU3_DR2_PC;                  // CPU3 DR2 Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd13[40];                   // Reserved
    uint32_t                                 CPU3_DW_HIGHPRIO_ERROR_ADDRESS; // CPU3 DW Error aggregator High Priority Error address register
    uint32_t                                 CPU3_DW_LOWPRIO_ERROR_ADDRESS; // CPU3 DW Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_REG CPU3_DW_ERROR_TYPE;    // CPU3 DW Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_FRC_REG CPU3_DW_ERROR_TYPE_FRC; // CPU3 DW Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU3_DW_ERROR_TYPE_CLR_REG CPU3_DW_ERROR_TYPE_CLR; // CPU3 DW Error aggregator Error Type Clear Register
    uint32_t                                 CPU3_DW_PC;                   // CPU3 DW Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd14[40];                   // Reserved
    uint32_t                                 CPU3_INT_HIGHPRIO_ERROR_ADDRESS; // CPU3 INT Error aggregator High Priority Error address register
    uint32_t                                 CPU3_INT_LOWPRIO_ERROR_ADDRESS; // CPU3 INT Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_REG CPU3_INT_ERROR_TYPE;  // CPU3 INT Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_FRC_REG CPU3_INT_ERROR_TYPE_FRC; // CPU3 INT Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_CPU3_INT_ERROR_TYPE_CLR_REG CPU3_INT_ERROR_TYPE_CLR; // CPU3 INT Error aggregator Error Type Clear Register
    uint32_t                                 CPU3_INT_PC;                  // CPU3 INT Error aggregator Register to store PC value at the first High priority error event
    uint8_t                                  rsvd15[1000];                 // Reserved
    uint32_t                                 RTDMA1_DR_HIGHPRIO_ERROR_ADDRESS; // RTDMA1 DR Error aggregator High Priority Error address register
    uint32_t                                 RTDMA1_DR_LOWPRIO_ERROR_ADDRESS; // RTDMA1 DR Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_REG RTDMA1_DR_ERROR_TYPE; // RTDMA1 DR Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_FRC_REG RTDMA1_DR_ERROR_TYPE_FRC; // RTDMA1 DR Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_RTDMA1_DR_ERROR_TYPE_CLR_REG RTDMA1_DR_ERROR_TYPE_CLR; // RTDMA1 DR Error aggregator Error Type Clear Register
    uint8_t                                  rsvd16[44];                   // Reserved
    uint32_t                                 RTDMA1_DW_HIGHPRIO_ERROR_ADDRESS; // RTDMA1 DW Error aggregator High Priority Error address register
    uint32_t                                 RTDMA1_DW_LOWPRIO_ERROR_ADDRESS; // RTDMA1 DW Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_REG RTDMA1_DW_ERROR_TYPE; // RTDMA1 DW Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_FRC_REG RTDMA1_DW_ERROR_TYPE_FRC; // RTDMA1 DW Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_RTDMA1_DW_ERROR_TYPE_CLR_REG RTDMA1_DW_ERROR_TYPE_CLR; // RTDMA1 DW Error aggregator Error Type Clear Register
    uint8_t                                  rsvd17[44];                   // Reserved
    uint32_t                                 RTDMA2_DR_HIGHPRIO_ERROR_ADDRESS; // RTDMA2 DR Error aggregator High Priority Error address register
    uint32_t                                 RTDMA2_DR_LOWPRIO_ERROR_ADDRESS; // RTDMA2 DR Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_REG RTDMA2_DR_ERROR_TYPE; // RTDMA2 DR Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_FRC_REG RTDMA2_DR_ERROR_TYPE_FRC; // RTDMA2 DR Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_RTDMA2_DR_ERROR_TYPE_CLR_REG RTDMA2_DR_ERROR_TYPE_CLR; // RTDMA2 DR Error aggregator Error Type Clear Register
    uint8_t                                  rsvd18[44];                   // Reserved
    uint32_t                                 RTDMA2_DW_HIGHPRIO_ERROR_ADDRESS; // RTDMA2 DW Error aggregator High Priority Error address register
    uint32_t                                 RTDMA2_DW_LOWPRIO_ERROR_ADDRESS; // RTDMA2 DW Error aggregator Low Priority Error address register
    union   ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_REG RTDMA2_DW_ERROR_TYPE; // RTDMA2 DW Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_FRC_REG RTDMA2_DW_ERROR_TYPE_FRC; // RTDMA2 DW Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_RTDMA2_DW_ERROR_TYPE_CLR_REG RTDMA2_DW_ERROR_TYPE_CLR; // RTDMA2 DW Error aggregator Error Type Clear Register
    uint8_t                                  rsvd19[44];                   // Reserved
    uint32_t                                 SSU_HIGHPRIO_ERROR_ADDRESS;   // SSU Error aggregator High Priority Error address register
    uint8_t                                  rsvd20[4];                    // Reserved
    union   ERROR_AGGREGATOR_SSU_ERROR_TYPE_REG SSU_ERROR_TYPE;            // SSU Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_SSU_ERROR_TYPE_FRC_REG SSU_ERROR_TYPE_FRC;    // SSU Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_SSU_ERROR_TYPE_CLR_REG SSU_ERROR_TYPE_CLR;    // SSU Error aggregator Error Type Clear Register
    uint8_t                                  rsvd21[44];                   // Reserved
    uint32_t                                 ETHERCAT_HIGHPRIO_ERROR_ADDRESS; // ETHERCAT Error aggregator High Priority Error address register
    uint8_t                                  rsvd22[4];                    // Reserved
    union   ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_REG ETHERCAT_ERROR_TYPE;  // ETHERCAT Error aggregator Error Type Register
    union   ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_FRC_REG ETHERCAT_ERROR_TYPE_FRC; // ETHERCAT Error aggregator Error Type Force Register
    union   ERROR_AGGREGATOR_ETHERCAT_ERROR_TYPE_CLR_REG ETHERCAT_ERROR_TYPE_CLR; // ETHERCAT Error aggregator Error Type Clear Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
