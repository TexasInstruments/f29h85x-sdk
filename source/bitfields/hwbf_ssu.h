//###########################################################################
//
// FILE:    hwbf_ssu.h
//
// TITLE:   Definitions for the SSU registers.
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

#ifndef HWBF_SSU_H
#define HWBF_SSU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// SSU Individual Register Bit Definitions:

struct SSU_REVISION_BITS {              // bits description
    uint16_t MINREV:8;                  // 7:0 Minor Revision Number
    uint16_t MAJREV:8;                  // 15:8 Major Revision Number
    uint16_t rsvd1:8;                   // 23:16 Reserved
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union SSU_REVISION_REG {
    uint32_t  all;
    struct  SSU_REVISION_BITS  bit;
};

struct SSU_UPP_REVISION_BITS {          // bits description
    uint16_t REV:16;                    // 15:0 User Protection Policy Revision
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union SSU_UPP_REVISION_REG {
    uint32_t  all;
    struct  SSU_UPP_REVISION_BITS  bit;
};

struct SSU_SSUMODE_BITS {               // bits description
    uint16_t OPMODE:6;                  // 5:0 SSU Operational Mode
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_SSUMODE_REG {
    uint32_t  all;
    struct  SSU_SSUMODE_BITS  bit;
};

struct SSU_LINK2_AP_OVERRIDE_BITS {     // bits description
    uint16_t CPU1:1;                    // 0 CPU1 LINK2 Access Protection Override Bit
    uint16_t CPU2:1;                    // 1 CPU2 LINK2 Access Protection Override Bit
    uint16_t CPU3:1;                    // 2 CPU3 LINK2 Access Protection Override Bit
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK2_AP_OVERRIDE_REG {
    uint32_t  all;
    struct  SSU_LINK2_AP_OVERRIDE_BITS  bit;
};

struct SSU_BOOTMODE_STAT_BITS {         // bits description
    uint16_t PIN_STAT:3;                // 2:0 Boot Mode Pin Status
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_BOOTMODE_STAT_REG {
    uint32_t  all;
    struct  SSU_BOOTMODE_STAT_BITS  bit;
};

struct SSU_EMU_BOOTPIN_CONFIG_BITS {    // bits description
    uint16_t BMSP0:8;                   // 7:0 Boot Mode Select Pin 0
    uint16_t BMSP1:8;                   // 15:8 Boot Mode Select Pin 1
    uint16_t BMSP2:8;                   // 23:16 Boot Mode Select Pin 2
    uint16_t KEY:8;                     // 31:24 Register Valid Key
};

union SSU_EMU_BOOTPIN_CONFIG_REG {
    uint32_t  all;
    struct  SSU_EMU_BOOTPIN_CONFIG_BITS  bit;
};

struct SSU_EMU_BOOT_DIAG_BITS {         // bits description
    uint16_t LPOST_EN:2;                // 1:0 LPOST Enable
    uint16_t LPOST_COVER:2;             // 3:2 LPOST Coverage
    uint16_t MPOST_EN:2;                // 5:4 MPOST Enable
    uint16_t rsvd1:10;                  // 15:6 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_EMU_BOOT_DIAG_REG {
    uint32_t  all;
    struct  SSU_EMU_BOOT_DIAG_BITS  bit;
};

struct SSU_EMU_BOOT_CLKCFG_BITS {       // bits description
    uint16_t IMULT:8;                   // 7:0 Secure Boot PLL IMULT
    uint16_t ODIV:5;                    // 12:8 Secure Boot PLL ODIV
    uint16_t rsvd1:3;                   // 15:13 Reserved
    uint16_t REFDIV:5;                  // 20:16 Secure Boot PLL REFDIV
    uint16_t rsvd2:7;                   // 27:21 Reserved
    uint16_t PLLEN:4;                   // 31:28 Secure Boot PLL Enable
};

union SSU_EMU_BOOT_CLKCFG_REG {
    uint32_t  all;
    struct  SSU_EMU_BOOT_CLKCFG_BITS  bit;
};

struct SSU_EMU_BOOTEN_BITS {            // bits description
    uint16_t ENABLE:1;                  // 0 Emulation Boot Enable
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_EMU_BOOTEN_REG {
    uint32_t  all;
    struct  SSU_EMU_BOOTEN_BITS  bit;
};

struct SSU_RAMOPEN_LOCK_BITS {          // bits description
    uint16_t LOCK:8;                    // 7:0 RAMOPEN Lock
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_RAMOPEN_LOCK_REG {
    uint32_t  all;
    struct  SSU_RAMOPEN_LOCK_BITS  bit;
};

struct SSU_RAMOPEN_COMMIT_BITS {        // bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_RAMOPEN_COMMIT_REG {
    uint32_t  all;
    struct  SSU_RAMOPEN_COMMIT_BITS  bit;
};

struct SSU_CPUID_BITS {                 // bits description
    uint16_t CPUID:3;                   // 2:0 CPUID Value
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t DBGREAD:1;                 // 4 Debug Read Status
    uint16_t rsvd2:11;                  // 15:5 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SSU_CPUID_REG {
    uint32_t  all;
    struct  SSU_CPUID_BITS  bit;
};

struct SSU_BANKMAP_BITS {               // bits description
    uint16_t CPU1SWAP:8;                // 7:0 CPU1 Bank Swap
    uint16_t CPU3SWAP:8;                // 15:8 CPU3 Bank Swap
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union SSU_BANKMAP_REG {
    uint32_t  all;
    struct  SSU_BANKMAP_BITS  bit;
};

struct SSU_BANKMAP_LOCK_BITS {          // bits description
    uint16_t LOCK1:1;                   // 0 CPU1 Bank Swap Lock
    uint16_t LOCK2:1;                   // 1 CPU3 Bank Swap Lock
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_BANKMAP_LOCK_REG {
    uint32_t  all;
    struct  SSU_BANKMAP_LOCK_BITS  bit;
};

struct SSU_BANKMAP_COMMIT_BITS {        // bits description
    uint16_t COMMIT1:1;                 // 0 CPU1 Bank Swap Commit
    uint16_t COMMIT2:1;                 // 1 CPU3 Bank Swap Commit
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_BANKMAP_COMMIT_REG {
    uint32_t  all;
    struct  SSU_BANKMAP_COMMIT_BITS  bit;
};

struct SSU_BANKMODE_BITS {              // bits description
    uint16_t MODE:4;                    // 3:0 Device Flash Configuration Mode
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_BANKMODE_REG {
    uint32_t  all;
    struct  SSU_BANKMODE_BITS  bit;
};

struct SSU_BANKMODE_LOCK_BITS {         // bits description
    uint16_t LOCK:1;                    // 0 Bank Mode Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_BANKMODE_LOCK_REG {
    uint32_t  all;
    struct  SSU_BANKMODE_LOCK_BITS  bit;
};

struct SSU_BANKMODE_COMMIT_BITS {       // bits description
    uint16_t COMMIT:1;                  // 0 Bank Mode Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_BANKMODE_COMMIT_REG {
    uint32_t  all;
    struct  SSU_BANKMODE_COMMIT_BITS  bit;
};

struct SSU_SECCFG_UPDATE_CFG_BITS {     // bits description
    uint16_t LINK_OWNER:4;              // 3:0 SECCFG Update Owner LINK
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t CPU_OWNER:3;               // 10:8 SECCFG Update Owner CPU
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t UPDATE_EN:4;               // 15:12 SECCFG Update Enable
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SSU_SECCFG_UPDATE_CFG_REG {
    uint32_t  all;
    struct  SSU_SECCFG_UPDATE_CFG_BITS  bit;
};

struct SSU_PROG_BANKMODE_BITS {         // bits description
    uint16_t MODE:2;                    // 1:0 Device Flash Configuration Mode
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_PROG_BANKMODE_REG {
    uint32_t  all;
    struct  SSU_PROG_BANKMODE_BITS  bit;
};

struct SSU_SECVALID_BITS {              // bits description
    uint16_t CPU1:8;                    // 7:0 Valid CPU1/CPU2 SECCFG Sector
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t CPU3:8;                    // 23:16 Valid CPU3 SECCFG Sector
    uint16_t rsvd2:8;                   // 31:24 Reserved
};

union SSU_SECVALID_REG {
    uint32_t  all;
    struct  SSU_SECVALID_BITS  bit;
};

struct SSU_SECVALID_LOCK_BITS {         // bits description
    uint16_t LOCK:1;                    // 0 SECVALID LOCK
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_SECVALID_LOCK_REG {
    uint32_t  all;
    struct  SSU_SECVALID_LOCK_BITS  bit;
};

struct SSU_SECVALID_COMMIT_BITS {       // bits description
    uint16_t COMMIT:1;                  // 0 Security Sectors Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_SECVALID_COMMIT_REG {
    uint32_t  all;
    struct  SSU_SECVALID_COMMIT_BITS  bit;
};

struct SSU_ZONE1_CFG_BITS {             // bits description
    uint16_t FWU_LINK:4;                // 3:0 Firmware Update Owner LINK
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t FWU_CPU:3;                 // 10:8 Firmware Update Owner CPU
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t UPDATE_EN:4;               // 15:12 ZONE1 Update Enable
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SSU_ZONE1_CFG_REG {
    uint32_t  all;
    struct  SSU_ZONE1_CFG_BITS  bit;
};

struct SSU_ZONE2_CFG_BITS {             // bits description
    uint16_t FWU_LINK:4;                // 3:0 Firmware Update Owner LINK
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t FWU_CPU:3;                 // 10:8 Firmware Update Owner CPU
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t UPDATE_EN:4;               // 15:12 ZONE2 Update Enable
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SSU_ZONE2_CFG_REG {
    uint32_t  all;
    struct  SSU_ZONE2_CFG_BITS  bit;
};

struct SSU_ZONE3_CFG_BITS {             // bits description
    uint16_t FWU_LINK:4;                // 3:0 Firmware Update Owner LINK
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t FWU_CPU:3;                 // 10:8 Firmware Update Owner CPU
    uint16_t rsvd2:1;                   // 11 Reserved
    uint16_t UPDATE_EN:4;               // 15:12 ZONE3 Update Enable
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SSU_ZONE3_CFG_REG {
    uint32_t  all;
    struct  SSU_ZONE3_CFG_BITS  bit;
};

struct SSU_DEBUG_CFG_BITS {             // bits description
    uint16_t C29DBGEN_CFG:3;            // 2:0 C29DBGEN Enable Configuration
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t ZONE1:3;                   // 6:4 ZONE1 Debug Enable Configuration
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t ZONE2:3;                   // 10:8 ZONE2 Debug Enable Configuration
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t ZONE3:3;                   // 14:12 ZONE3 Debug Enable Configuration
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t rsvd5:16;                  // 31:16 Reserved
};

union SSU_DEBUG_CFG_REG {
    uint32_t  all;
    struct  SSU_DEBUG_CFG_BITS  bit;
};

struct SSU_DEBUG_CFG_LOCK_BITS {        // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_DEBUG_CFG_LOCK_REG {
    uint32_t  all;
    struct  SSU_DEBUG_CFG_LOCK_BITS  bit;
};

struct SSU_DEBUG_CFG_COMMIT_BITS {      // bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_DEBUG_CFG_COMMIT_REG {
    uint32_t  all;
    struct  SSU_DEBUG_CFG_COMMIT_BITS  bit;
};

struct SSU_DEBUG_STAT_BITS {            // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t ZONE1:2;                   // 3:2 ZONE1 Debug State
    uint16_t ZONE2:2;                   // 5:4 ZONE2 Debug State
    uint16_t ZONE3:2;                   // 7:6 ZONE3 Debug State
    uint16_t rsvd2:8;                   // 15:8 Reserved
    uint16_t rsvd3:13;                  // 28:16 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t C29DBGS:1;                 // 31 C29 Debug Status
};

union SSU_DEBUG_STAT_REG {
    uint32_t  all;
    struct  SSU_DEBUG_STAT_BITS  bit;
};

struct SSU_C29DBGEN_BITS {              // bits description
    uint16_t ENA:4;                     // 3:0 C29 Debug Enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_C29DBGEN_REG {
    uint32_t  all;
    struct  SSU_C29DBGEN_BITS  bit;
};

struct SSU_ZONE_DBGEN_BITS {            // bits description
    uint16_t ZONE1:6;                   // 5:0 ZONE1 Debug Enable
    uint16_t rsvd1:2;                   // 7:6 Reserved
    uint16_t ZONE2:6;                   // 13:8 ZONE2 Debug Enable
    uint16_t rsvd2:2;                   // 15:14 Reserved
    uint16_t ZONE3:6;                   // 21:16 ZONE3 Debug Enable
    uint16_t rsvd3:10;                  // 31:22 Reserved
};

union SSU_ZONE_DBGEN_REG {
    uint32_t  all;
    struct  SSU_ZONE_DBGEN_BITS  bit;
};

struct SSU_BEPROT_BANK_BITS {           // bits description
    uint16_t BANKID:3;                  // 2:0 Bank Erase Bank
    uint16_t FLCID:2;                   // 4:3 Bank Erase Bank
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_BEPROT_BANK_REG {
    uint32_t  all;
    struct  SSU_BEPROT_BANK_BITS  bit;
};

struct SSU_BEPROT_STAT_BITS {           // bits description
    uint16_t READY:1;                   // 0 Bank Erase State Machine Ready
    uint16_t ACTIVE:1;                  // 1 Bank Erase State Machine Initializing
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_BEPROT_STAT_REG {
    uint32_t  all;
    struct  SSU_BEPROT_STAT_BITS  bit;
};

struct SSU_BEPROTA_BITS {               // bits description
    uint16_t SECT0:1;                   // 0 Sector 0 Bank Erase Protection
    uint16_t SECT1:1;                   // 1 Sector 1 Bank Erase Protection
    uint16_t SECT2:1;                   // 2 Sector 2 Bank Erase Protection
    uint16_t SECT3:1;                   // 3 Sector 3 Bank Erase Protection
    uint16_t SECT4:1;                   // 4 Sector 4 Bank Erase Protection
    uint16_t SECT5:1;                   // 5 Sector 5 Bank Erase Protection
    uint16_t SECT6:1;                   // 6 Sector 6 Bank Erase Protection
    uint16_t SECT7:1;                   // 7 Sector 7 Bank Erase Protection
    uint16_t SECT8:1;                   // 8 Sector 8 Bank Erase Protection
    uint16_t SECT9:1;                   // 9 Sector 9 Bank Erase Protection
    uint16_t SECT10:1;                  // 10 Sector 10 Bank Erase Protection
    uint16_t SECT11:1;                  // 11 Sector 11 Bank Erase Protection
    uint16_t SECT12:1;                  // 12 Sector 12 Bank Erase Protection
    uint16_t SECT13:1;                  // 13 Sector 13 Bank Erase Protection
    uint16_t SECT14:1;                  // 14 Sector 14 Bank Erase Protection
    uint16_t SECT15:1;                  // 15 Sector 15 Bank Erase Protection
    uint16_t SECT16:1;                  // 16 Sector 16 Bank Erase Protection
    uint16_t SECT17:1;                  // 17 Sector 17 Bank Erase Protection
    uint16_t SECT18:1;                  // 18 Sector 18 Bank Erase Protection
    uint16_t SECT19:1;                  // 19 Sector 19 Bank Erase Protection
    uint16_t SECT20:1;                  // 20 Sector 20 Bank Erase Protection
    uint16_t SECT21:1;                  // 21 Sector 21 Bank Erase Protection
    uint16_t SECT22:1;                  // 22 Sector 22 Bank Erase Protection
    uint16_t SECT23:1;                  // 23 Sector 23 Bank Erase Protection
    uint16_t SECT24:1;                  // 24 Sector 24 Bank Erase Protection
    uint16_t SECT25:1;                  // 25 Sector 25 Bank Erase Protection
    uint16_t SECT26:1;                  // 26 Sector 26 Bank Erase Protection
    uint16_t SECT27:1;                  // 27 Sector 27 Bank Erase Protection
    uint16_t SECT28:1;                  // 28 Sector 28 Bank Erase Protection
    uint16_t SECT29:1;                  // 29 Sector 29 Bank Erase Protection
    uint16_t SECT30:1;                  // 30 Sector 30 Bank Erase Protection
    uint16_t SECT31:1;                  // 31 Sector 31 Bank Erase Protection
};

union SSU_BEPROTA_REG {
    uint32_t  all;
    struct  SSU_BEPROTA_BITS  bit;
};

struct SSU_BEPROTB_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t SECT39_22:1;               // 4 Sectors 39 - 22 Bank Erase Protection
    uint16_t SECT47_40:1;               // 5 Sectors 47 - 40 Bank Erase Protection
    uint16_t SECT55_48:1;               // 6 Sectors 55 - 48 Bank Erase Protection
    uint16_t SECT63_56:1;               // 7 Sectors 63 - 56 Bank Erase Protection
    uint16_t SECT71_64:1;               // 8 Sectors 71 - 64 Bank Erase Protection
    uint16_t SECT79_72:1;               // 9 Sectors 79 - 72 Bank Erase Protection
    uint16_t SECT87_80:1;               // 10 Sectors 87 - 80 Bank Erase Protection
    uint16_t SECT95_88:1;               // 11 Sectors 95 - 88 Bank Erase Protection
    uint16_t SECT103_96:1;              // 12 Sectors 103 - 96 Bank Erase Protection
    uint16_t SECT111_104:1;             // 13 Sectors 111 - 104 Bank Erase Protection
    uint16_t SECT119_112:1;             // 14 Sectors 119 - 112 Bank Erase Protection
    uint16_t SECT127_120:1;             // 15 Sectors 127 - 120 Bank Erase Protection
    uint16_t SECT135_128:1;             // 16 Sectors 135 - 128 Bank Erase Protection
    uint16_t SECT143_136:1;             // 17 Sectors 143 - 136 Bank Erase Protection
    uint16_t SECT151_144:1;             // 18 Sectors 151 - 144 Bank Erase Protection
    uint16_t SECT159_152:1;             // 19 Sectors 159 - 152 Bank Erase Protection
    uint16_t SECT167_160:1;             // 20 Sectors 167 - 160 Bank Erase Protection
    uint16_t SECT175_168:1;             // 21 Sectors 175 - 168 Bank Erase Protection
    uint16_t SECT183_176:1;             // 22 Sectors 183 - 176 Bank Erase Protection
    uint16_t SECT191_184:1;             // 23 Sectors 191 - 184 Bank Erase Protection
    uint16_t SECT199_192:1;             // 24 Sectors 199 - 192 Bank Erase Protection
    uint16_t SECT207_200:1;             // 25 Sectors 207 - 200 Bank Erase Protection
    uint16_t SECT215_208:1;             // 26 Sectors 215 - 208 Bank Erase Protection
    uint16_t SECT223_216:1;             // 27 Sectors 223 - 216 Bank Erase Protection
    uint16_t SECT231_224:1;             // 28 Sectors 231 - 224 Bank Erase Protection
    uint16_t SECT239_232:1;             // 29 Sectors 239 - 232 Bank Erase Protection
    uint16_t SECT247_240:1;             // 30 Sectors 247 - 240 Bank Erase Protection
    uint16_t SECT255_248:1;             // 31 Sectors 255 - 248 Bank Erase Protection
};

union SSU_BEPROTB_REG {
    uint32_t  all;
    struct  SSU_BEPROTB_BITS  bit;
};

struct SSU_FLSEMSTAT_BITS {             // bits description
    uint16_t LINK:4;                    // 3:0 Semaphore LINK Owner
    uint16_t rsvd1:4;                   // 7:4 Reserved
    uint16_t ZONE:2;                    // 9:8 Semaphore ZONE Owner
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t CPU:3;                     // 14:12 Semaphore CPU Owner
    uint16_t rsvd3:1;                   // 15 Reserved
    uint16_t rsvd4:14;                  // 29:16 Reserved
    uint16_t MATCH:1;                   // 30 Match Status Bit
    uint16_t ASSIGNED:1;                // 31 Assigned Flag
};

union SSU_FLSEMSTAT_REG {
    uint32_t  all;
    struct  SSU_FLSEMSTAT_BITS  bit;
};

struct SSU_FLSEMREQ_BITS {              // bits description
    uint16_t REQ:1;                     // 0 Request Semaphore Ownership
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_FLSEMREQ_REG {
    uint32_t  all;
    struct  SSU_FLSEMREQ_BITS  bit;
};

struct SSU_FLSEMCLR_BITS {              // bits description
    uint16_t CLR:1;                     // 0 Release Semaphore Ownership
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_FLSEMCLR_REG {
    uint32_t  all;
    struct  SSU_FLSEMCLR_BITS  bit;
};

struct SSU_WEPROT_CODE_BANKS_BITS {     // bits description
    uint16_t PROT:1;                    // 0 Global Code Banks WEPROT
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_CODE_BANKS_REG {
    uint32_t  all;
    struct  SSU_WEPROT_CODE_BANKS_BITS  bit;
};

struct SSU_WEPROT_CODE_BANKS_LOCK_BITS {// bits description
    uint16_t LOCK:1;                    // 0 System Access Protection Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_CODE_BANKS_LOCK_REG {
    uint32_t  all;
    struct  SSU_WEPROT_CODE_BANKS_LOCK_BITS  bit;
};

struct SSU_WEPROT_CODE_BANKS_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 System Access Protection Register Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_CODE_BANKS_COMMIT_REG {
    uint32_t  all;
    struct  SSU_WEPROT_CODE_BANKS_COMMIT_BITS  bit;
};

struct SSU_WEPROT_DATA_BANKS_BITS {     // bits description
    uint16_t PROT:1;                    // 0 Global Data Banks WEPROT
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_DATA_BANKS_REG {
    uint32_t  all;
    struct  SSU_WEPROT_DATA_BANKS_BITS  bit;
};

struct SSU_WEPROT_DATA_BANKS_LOCK_BITS {// bits description
    uint16_t LOCK:1;                    // 0 System Access Protection Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_DATA_BANKS_LOCK_REG {
    uint32_t  all;
    struct  SSU_WEPROT_DATA_BANKS_LOCK_BITS  bit;
};

struct SSU_WEPROT_DATA_BANKS_COMMIT_BITS {// bits description
    uint16_t COMMIT:1;                  // 0 System Access Protection Register Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_DATA_BANKS_COMMIT_REG {
    uint32_t  all;
    struct  SSU_WEPROT_DATA_BANKS_COMMIT_BITS  bit;
};

struct SSU_WEPROT_FLC1_B0_A_BITS {      // bits description
    uint16_t SECT0:1;                   // 0 Sector 0 Write Erase Protection
    uint16_t SECT1:1;                   // 1 Sector 1 Write Erase Protection
    uint16_t SECT2:1;                   // 2 Sector 2 Write Erase Protection
    uint16_t SECT3:1;                   // 3 Sector 3 Write Erase Protection
    uint16_t SECT4:1;                   // 4 Sector 4 Write Erase Protection
    uint16_t SECT5:1;                   // 5 Sector 5 Write Erase Protection
    uint16_t SECT6:1;                   // 6 Sector 6 Write Erase Protection
    uint16_t SECT7:1;                   // 7 Sector 7 Write Erase Protection
    uint16_t SECT8:1;                   // 8 Sector 8 Write Erase Protection
    uint16_t SECT9:1;                   // 9 Sector 9 Write Erase Protection
    uint16_t SECT10:1;                  // 10 Sector 10 Write Erase Protection
    uint16_t SECT11:1;                  // 11 Sector 11 Write Erase Protection
    uint16_t SECT12:1;                  // 12 Sector 12 Write Erase Protection
    uint16_t SECT13:1;                  // 13 Sector 13 Write Erase Protection
    uint16_t SECT14:1;                  // 14 Sector 14 Write Erase Protection
    uint16_t SECT15:1;                  // 15 Sector 15 Write Erase Protection
    uint16_t SECT16:1;                  // 16 Sector 16 Write Erase Protection
    uint16_t SECT17:1;                  // 17 Sector 17 Write Erase Protection
    uint16_t SECT18:1;                  // 18 Sector 18 Write Erase Protection
    uint16_t SECT19:1;                  // 19 Sector 19 Write Erase Protection
    uint16_t SECT20:1;                  // 20 Sector 20 Write Erase Protection
    uint16_t SECT21:1;                  // 21 Sector 21 Write Erase Protection
    uint16_t SECT22:1;                  // 22 Sector 22 Write Erase Protection
    uint16_t SECT23:1;                  // 23 Sector 23 Write Erase Protection
    uint16_t SECT24:1;                  // 24 Sector 24 Write Erase Protection
    uint16_t SECT25:1;                  // 25 Sector 25 Write Erase Protection
    uint16_t SECT26:1;                  // 26 Sector 26 Write Erase Protection
    uint16_t SECT27:1;                  // 27 Sector 27 Write Erase Protection
    uint16_t SECT28:1;                  // 28 Sector 28 Write Erase Protection
    uint16_t SECT29:1;                  // 29 Sector 29 Write Erase Protection
    uint16_t SECT30:1;                  // 30 Sector 30 Write Erase Protection
    uint16_t SECT31:1;                  // 31 Sector 31 Write Erase Protection
};

union SSU_WEPROT_FLC1_B0_A_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC1_B0_A_BITS  bit;
};

struct SSU_WEPROT_FLC1_B0_B_BITS {      // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t SECT39_22:1;               // 4 Sectors 39 - 22 Write Erase Protection
    uint16_t SECT47_40:1;               // 5 Sectors 47 - 40 Write Erase Protection
    uint16_t SECT55_48:1;               // 6 Sectors 55 - 48 Write Erase Protection
    uint16_t SECT63_56:1;               // 7 Sectors 63 - 56 Write Erase Protection
    uint16_t SECT71_64:1;               // 8 Sectors 71 - 64 Write Erase Protection
    uint16_t SECT79_72:1;               // 9 Sectors 79 - 72 Write Erase Protection
    uint16_t SECT87_80:1;               // 10 Sectors 87 - 80 Write Erase Protection
    uint16_t SECT95_88:1;               // 11 Sectors 95 - 88 Write Erase Protection
    uint16_t SECT103_96:1;              // 12 Sectors 103 - 96 Write Erase Protection
    uint16_t SECT111_104:1;             // 13 Sectors 111 - 104 Write Erase Protection
    uint16_t SECT119_112:1;             // 14 Sectors 119 - 112 Write Erase Protection
    uint16_t SECT127_120:1;             // 15 Sectors 127 - 120 Write Erase Protection
    uint16_t SECT135_128:1;             // 16 Sectors 135 - 128 Write Erase Protection
    uint16_t SECT143_136:1;             // 17 Sectors 143 - 136 Write Erase Protection
    uint16_t SECT151_144:1;             // 18 Sectors 151 - 144 Write Erase Protection
    uint16_t SECT159_152:1;             // 19 Sectors 159 - 152 Write Erase Protection
    uint16_t SECT167_160:1;             // 20 Sectors 167 - 160 Write Erase Protection
    uint16_t SECT175_168:1;             // 21 Sectors 175 - 168 Write Erase Protection
    uint16_t SECT183_176:1;             // 22 Sectors 183 - 176 Write Erase Protection
    uint16_t SECT191_184:1;             // 23 Sectors 191 - 184 Write Erase Protection
    uint16_t SECT199_192:1;             // 24 Sectors 199 - 192 Write Erase Protection
    uint16_t SECT207_200:1;             // 25 Sectors 207 - 200 Write Erase Protection
    uint16_t SECT215_208:1;             // 26 Sectors 215 - 208 Write Erase Protection
    uint16_t SECT223_216:1;             // 27 Sectors 223 - 216 Write Erase Protection
    uint16_t SECT231_224:1;             // 28 Sectors 231 - 224 Write Erase Protection
    uint16_t SECT239_232:1;             // 29 Sectors 239 - 232 Write Erase Protection
    uint16_t SECT247_240:1;             // 30 Sectors 247 - 240 Write Erase Protection
    uint16_t SECT255_248:1;             // 31 Sectors 255 - 248 Write Erase Protection
};

union SSU_WEPROT_FLC1_B0_B_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC1_B0_B_BITS  bit;
};

struct SSU_WEPROT_FLC1_B0_LOCK_BITS {   // bits description
    uint16_t LOCK:1;                    // 0 System Access Protection Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_FLC1_B0_LOCK_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC1_B0_LOCK_BITS  bit;
};

struct SSU_WEPROT_FLC1_B0_COMMIT_BITS { // bits description
    uint16_t COMMIT:1;                  // 0 System Access Protection Register Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_FLC1_B0_COMMIT_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC1_B0_COMMIT_BITS  bit;
};

struct SSU_WEPROT_FLC1_B2_A_BITS {      // bits description
    uint16_t SECT0:1;                   // 0 Sector 0 Write Erase Protection
    uint16_t SECT1:1;                   // 1 Sector 1 Write Erase Protection
    uint16_t SECT2:1;                   // 2 Sector 2 Write Erase Protection
    uint16_t SECT3:1;                   // 3 Sector 3 Write Erase Protection
    uint16_t SECT4:1;                   // 4 Sector 4 Write Erase Protection
    uint16_t SECT5:1;                   // 5 Sector 5 Write Erase Protection
    uint16_t SECT6:1;                   // 6 Sector 6 Write Erase Protection
    uint16_t SECT7:1;                   // 7 Sector 7 Write Erase Protection
    uint16_t SECT8:1;                   // 8 Sector 8 Write Erase Protection
    uint16_t SECT9:1;                   // 9 Sector 9 Write Erase Protection
    uint16_t SECT10:1;                  // 10 Sector 10 Write Erase Protection
    uint16_t SECT11:1;                  // 11 Sector 11 Write Erase Protection
    uint16_t SECT12:1;                  // 12 Sector 12 Write Erase Protection
    uint16_t SECT13:1;                  // 13 Sector 13 Write Erase Protection
    uint16_t SECT14:1;                  // 14 Sector 14 Write Erase Protection
    uint16_t SECT15:1;                  // 15 Sector 15 Write Erase Protection
    uint16_t SECT16:1;                  // 16 Sector 16 Write Erase Protection
    uint16_t SECT17:1;                  // 17 Sector 17 Write Erase Protection
    uint16_t SECT18:1;                  // 18 Sector 18 Write Erase Protection
    uint16_t SECT19:1;                  // 19 Sector 19 Write Erase Protection
    uint16_t SECT20:1;                  // 20 Sector 20 Write Erase Protection
    uint16_t SECT21:1;                  // 21 Sector 21 Write Erase Protection
    uint16_t SECT22:1;                  // 22 Sector 22 Write Erase Protection
    uint16_t SECT23:1;                  // 23 Sector 23 Write Erase Protection
    uint16_t SECT24:1;                  // 24 Sector 24 Write Erase Protection
    uint16_t SECT25:1;                  // 25 Sector 25 Write Erase Protection
    uint16_t SECT26:1;                  // 26 Sector 26 Write Erase Protection
    uint16_t SECT27:1;                  // 27 Sector 27 Write Erase Protection
    uint16_t SECT28:1;                  // 28 Sector 28 Write Erase Protection
    uint16_t SECT29:1;                  // 29 Sector 29 Write Erase Protection
    uint16_t SECT30:1;                  // 30 Sector 30 Write Erase Protection
    uint16_t SECT31:1;                  // 31 Sector 31 Write Erase Protection
};

union SSU_WEPROT_FLC1_B2_A_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC1_B2_A_BITS  bit;
};

struct SSU_WEPROT_FLC1_B2_B_BITS {      // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t SECT39_22:1;               // 4 Sectors 39 - 22 Write Erase Protection
    uint16_t SECT47_40:1;               // 5 Sectors 47 - 40 Write Erase Protection
    uint16_t SECT55_48:1;               // 6 Sectors 55 - 48 Write Erase Protection
    uint16_t SECT63_56:1;               // 7 Sectors 63 - 56 Write Erase Protection
    uint16_t SECT71_64:1;               // 8 Sectors 71 - 64 Write Erase Protection
    uint16_t SECT79_72:1;               // 9 Sectors 79 - 72 Write Erase Protection
    uint16_t SECT87_80:1;               // 10 Sectors 87 - 80 Write Erase Protection
    uint16_t SECT95_88:1;               // 11 Sectors 95 - 88 Write Erase Protection
    uint16_t SECT103_96:1;              // 12 Sectors 103 - 96 Write Erase Protection
    uint16_t SECT111_104:1;             // 13 Sectors 111 - 104 Write Erase Protection
    uint16_t SECT119_112:1;             // 14 Sectors 119 - 112 Write Erase Protection
    uint16_t SECT127_120:1;             // 15 Sectors 127 - 120 Write Erase Protection
    uint16_t SECT135_128:1;             // 16 Sectors 135 - 128 Write Erase Protection
    uint16_t SECT143_136:1;             // 17 Sectors 143 - 136 Write Erase Protection
    uint16_t SECT151_144:1;             // 18 Sectors 151 - 144 Write Erase Protection
    uint16_t SECT159_152:1;             // 19 Sectors 159 - 152 Write Erase Protection
    uint16_t SECT167_160:1;             // 20 Sectors 167 - 160 Write Erase Protection
    uint16_t SECT175_168:1;             // 21 Sectors 175 - 168 Write Erase Protection
    uint16_t SECT183_176:1;             // 22 Sectors 183 - 176 Write Erase Protection
    uint16_t SECT191_184:1;             // 23 Sectors 191 - 184 Write Erase Protection
    uint16_t SECT199_192:1;             // 24 Sectors 199 - 192 Write Erase Protection
    uint16_t SECT207_200:1;             // 25 Sectors 207 - 200 Write Erase Protection
    uint16_t SECT215_208:1;             // 26 Sectors 215 - 208 Write Erase Protection
    uint16_t SECT223_216:1;             // 27 Sectors 223 - 216 Write Erase Protection
    uint16_t SECT231_224:1;             // 28 Sectors 231 - 224 Write Erase Protection
    uint16_t SECT239_232:1;             // 29 Sectors 239 - 232 Write Erase Protection
    uint16_t SECT247_240:1;             // 30 Sectors 247 - 240 Write Erase Protection
    uint16_t SECT255_248:1;             // 31 Sectors 255 - 248 Write Erase Protection
};

union SSU_WEPROT_FLC1_B2_B_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC1_B2_B_BITS  bit;
};

struct SSU_WEPROT_FLC1_B2_LOCK_BITS {   // bits description
    uint16_t LOCK:1;                    // 0 System Access Protection Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_FLC1_B2_LOCK_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC1_B2_LOCK_BITS  bit;
};

struct SSU_WEPROT_FLC1_B2_COMMIT_BITS { // bits description
    uint16_t COMMIT:1;                  // 0 System Access Protection Register Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_FLC1_B2_COMMIT_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC1_B2_COMMIT_BITS  bit;
};

struct SSU_WEPROT_FLC2_B0_A_BITS {      // bits description
    uint16_t SECT0:1;                   // 0 Sector 0 Write Erase Protection
    uint16_t SECT1:1;                   // 1 Sector 1 Write Erase Protection
    uint16_t SECT2:1;                   // 2 Sector 2 Write Erase Protection
    uint16_t SECT3:1;                   // 3 Sector 3 Write Erase Protection
    uint16_t SECT4:1;                   // 4 Sector 4 Write Erase Protection
    uint16_t SECT5:1;                   // 5 Sector 5 Write Erase Protection
    uint16_t SECT6:1;                   // 6 Sector 6 Write Erase Protection
    uint16_t SECT7:1;                   // 7 Sector 7 Write Erase Protection
    uint16_t SECT8:1;                   // 8 Sector 8 Write Erase Protection
    uint16_t SECT9:1;                   // 9 Sector 9 Write Erase Protection
    uint16_t SECT10:1;                  // 10 Sector 10 Write Erase Protection
    uint16_t SECT11:1;                  // 11 Sector 11 Write Erase Protection
    uint16_t SECT12:1;                  // 12 Sector 12 Write Erase Protection
    uint16_t SECT13:1;                  // 13 Sector 13 Write Erase Protection
    uint16_t SECT14:1;                  // 14 Sector 14 Write Erase Protection
    uint16_t SECT15:1;                  // 15 Sector 15 Write Erase Protection
    uint16_t SECT16:1;                  // 16 Sector 16 Write Erase Protection
    uint16_t SECT17:1;                  // 17 Sector 17 Write Erase Protection
    uint16_t SECT18:1;                  // 18 Sector 18 Write Erase Protection
    uint16_t SECT19:1;                  // 19 Sector 19 Write Erase Protection
    uint16_t SECT20:1;                  // 20 Sector 20 Write Erase Protection
    uint16_t SECT21:1;                  // 21 Sector 21 Write Erase Protection
    uint16_t SECT22:1;                  // 22 Sector 22 Write Erase Protection
    uint16_t SECT23:1;                  // 23 Sector 23 Write Erase Protection
    uint16_t SECT24:1;                  // 24 Sector 24 Write Erase Protection
    uint16_t SECT25:1;                  // 25 Sector 25 Write Erase Protection
    uint16_t SECT26:1;                  // 26 Sector 26 Write Erase Protection
    uint16_t SECT27:1;                  // 27 Sector 27 Write Erase Protection
    uint16_t SECT28:1;                  // 28 Sector 28 Write Erase Protection
    uint16_t SECT29:1;                  // 29 Sector 29 Write Erase Protection
    uint16_t SECT30:1;                  // 30 Sector 30 Write Erase Protection
    uint16_t SECT31:1;                  // 31 Sector 31 Write Erase Protection
};

union SSU_WEPROT_FLC2_B0_A_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC2_B0_A_BITS  bit;
};

struct SSU_WEPROT_FLC2_B0_B_BITS {      // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t SECT39_22:1;               // 4 Sectors 39 - 22 Write Erase Protection
    uint16_t SECT47_40:1;               // 5 Sectors 47 - 40 Write Erase Protection
    uint16_t SECT55_48:1;               // 6 Sectors 55 - 48 Write Erase Protection
    uint16_t SECT63_56:1;               // 7 Sectors 63 - 56 Write Erase Protection
    uint16_t SECT71_64:1;               // 8 Sectors 71 - 64 Write Erase Protection
    uint16_t SECT79_72:1;               // 9 Sectors 79 - 72 Write Erase Protection
    uint16_t SECT87_80:1;               // 10 Sectors 87 - 80 Write Erase Protection
    uint16_t SECT95_88:1;               // 11 Sectors 95 - 88 Write Erase Protection
    uint16_t SECT103_96:1;              // 12 Sectors 103 - 96 Write Erase Protection
    uint16_t SECT111_104:1;             // 13 Sectors 111 - 104 Write Erase Protection
    uint16_t SECT119_112:1;             // 14 Sectors 119 - 112 Write Erase Protection
    uint16_t SECT127_120:1;             // 15 Sectors 127 - 120 Write Erase Protection
    uint16_t SECT135_128:1;             // 16 Sectors 135 - 128 Write Erase Protection
    uint16_t SECT143_136:1;             // 17 Sectors 143 - 136 Write Erase Protection
    uint16_t SECT151_144:1;             // 18 Sectors 151 - 144 Write Erase Protection
    uint16_t SECT159_152:1;             // 19 Sectors 159 - 152 Write Erase Protection
    uint16_t SECT167_160:1;             // 20 Sectors 167 - 160 Write Erase Protection
    uint16_t SECT175_168:1;             // 21 Sectors 175 - 168 Write Erase Protection
    uint16_t SECT183_176:1;             // 22 Sectors 183 - 176 Write Erase Protection
    uint16_t SECT191_184:1;             // 23 Sectors 191 - 184 Write Erase Protection
    uint16_t SECT199_192:1;             // 24 Sectors 199 - 192 Write Erase Protection
    uint16_t SECT207_200:1;             // 25 Sectors 207 - 200 Write Erase Protection
    uint16_t SECT215_208:1;             // 26 Sectors 215 - 208 Write Erase Protection
    uint16_t SECT223_216:1;             // 27 Sectors 223 - 216 Write Erase Protection
    uint16_t SECT231_224:1;             // 28 Sectors 231 - 224 Write Erase Protection
    uint16_t SECT239_232:1;             // 29 Sectors 239 - 232 Write Erase Protection
    uint16_t SECT247_240:1;             // 30 Sectors 247 - 240 Write Erase Protection
    uint16_t SECT255_248:1;             // 31 Sectors 255 - 248 Write Erase Protection
};

union SSU_WEPROT_FLC2_B0_B_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC2_B0_B_BITS  bit;
};

struct SSU_WEPROT_FLC2_B0_LOCK_BITS {   // bits description
    uint16_t LOCK:1;                    // 0 System Access Protection Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_FLC2_B0_LOCK_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC2_B0_LOCK_BITS  bit;
};

struct SSU_WEPROT_FLC2_B0_COMMIT_BITS { // bits description
    uint16_t COMMIT:1;                  // 0 System Access Protection Register Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_FLC2_B0_COMMIT_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC2_B0_COMMIT_BITS  bit;
};

struct SSU_WEPROT_FLC2_B2_A_BITS {      // bits description
    uint16_t SECT0:1;                   // 0 Sector 0 Write Erase Protection
    uint16_t SECT1:1;                   // 1 Sector 1 Write Erase Protection
    uint16_t SECT2:1;                   // 2 Sector 2 Write Erase Protection
    uint16_t SECT3:1;                   // 3 Sector 3 Write Erase Protection
    uint16_t SECT4:1;                   // 4 Sector 4 Write Erase Protection
    uint16_t SECT5:1;                   // 5 Sector 5 Write Erase Protection
    uint16_t SECT6:1;                   // 6 Sector 6 Write Erase Protection
    uint16_t SECT7:1;                   // 7 Sector 7 Write Erase Protection
    uint16_t SECT8:1;                   // 8 Sector 8 Write Erase Protection
    uint16_t SECT9:1;                   // 9 Sector 9 Write Erase Protection
    uint16_t SECT10:1;                  // 10 Sector 10 Write Erase Protection
    uint16_t SECT11:1;                  // 11 Sector 11 Write Erase Protection
    uint16_t SECT12:1;                  // 12 Sector 12 Write Erase Protection
    uint16_t SECT13:1;                  // 13 Sector 13 Write Erase Protection
    uint16_t SECT14:1;                  // 14 Sector 14 Write Erase Protection
    uint16_t SECT15:1;                  // 15 Sector 15 Write Erase Protection
    uint16_t SECT16:1;                  // 16 Sector 16 Write Erase Protection
    uint16_t SECT17:1;                  // 17 Sector 17 Write Erase Protection
    uint16_t SECT18:1;                  // 18 Sector 18 Write Erase Protection
    uint16_t SECT19:1;                  // 19 Sector 19 Write Erase Protection
    uint16_t SECT20:1;                  // 20 Sector 20 Write Erase Protection
    uint16_t SECT21:1;                  // 21 Sector 21 Write Erase Protection
    uint16_t SECT22:1;                  // 22 Sector 22 Write Erase Protection
    uint16_t SECT23:1;                  // 23 Sector 23 Write Erase Protection
    uint16_t SECT24:1;                  // 24 Sector 24 Write Erase Protection
    uint16_t SECT25:1;                  // 25 Sector 25 Write Erase Protection
    uint16_t SECT26:1;                  // 26 Sector 26 Write Erase Protection
    uint16_t SECT27:1;                  // 27 Sector 27 Write Erase Protection
    uint16_t SECT28:1;                  // 28 Sector 28 Write Erase Protection
    uint16_t SECT29:1;                  // 29 Sector 29 Write Erase Protection
    uint16_t SECT30:1;                  // 30 Sector 30 Write Erase Protection
    uint16_t SECT31:1;                  // 31 Sector 31 Write Erase Protection
};

union SSU_WEPROT_FLC2_B2_A_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC2_B2_A_BITS  bit;
};

struct SSU_WEPROT_FLC2_B2_B_BITS {      // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t SECT39_22:1;               // 4 Sectors 39 - 22 Write Erase Protection
    uint16_t SECT47_40:1;               // 5 Sectors 47 - 40 Write Erase Protection
    uint16_t SECT55_48:1;               // 6 Sectors 55 - 48 Write Erase Protection
    uint16_t SECT63_56:1;               // 7 Sectors 63 - 56 Write Erase Protection
    uint16_t SECT71_64:1;               // 8 Sectors 71 - 64 Write Erase Protection
    uint16_t SECT79_72:1;               // 9 Sectors 79 - 72 Write Erase Protection
    uint16_t SECT87_80:1;               // 10 Sectors 87 - 80 Write Erase Protection
    uint16_t SECT95_88:1;               // 11 Sectors 95 - 88 Write Erase Protection
    uint16_t SECT103_96:1;              // 12 Sectors 103 - 96 Write Erase Protection
    uint16_t SECT111_104:1;             // 13 Sectors 111 - 104 Write Erase Protection
    uint16_t SECT119_112:1;             // 14 Sectors 119 - 112 Write Erase Protection
    uint16_t SECT127_120:1;             // 15 Sectors 127 - 120 Write Erase Protection
    uint16_t SECT135_128:1;             // 16 Sectors 135 - 128 Write Erase Protection
    uint16_t SECT143_136:1;             // 17 Sectors 143 - 136 Write Erase Protection
    uint16_t SECT151_144:1;             // 18 Sectors 151 - 144 Write Erase Protection
    uint16_t SECT159_152:1;             // 19 Sectors 159 - 152 Write Erase Protection
    uint16_t SECT167_160:1;             // 20 Sectors 167 - 160 Write Erase Protection
    uint16_t SECT175_168:1;             // 21 Sectors 175 - 168 Write Erase Protection
    uint16_t SECT183_176:1;             // 22 Sectors 183 - 176 Write Erase Protection
    uint16_t SECT191_184:1;             // 23 Sectors 191 - 184 Write Erase Protection
    uint16_t SECT199_192:1;             // 24 Sectors 199 - 192 Write Erase Protection
    uint16_t SECT207_200:1;             // 25 Sectors 207 - 200 Write Erase Protection
    uint16_t SECT215_208:1;             // 26 Sectors 215 - 208 Write Erase Protection
    uint16_t SECT223_216:1;             // 27 Sectors 223 - 216 Write Erase Protection
    uint16_t SECT231_224:1;             // 28 Sectors 231 - 224 Write Erase Protection
    uint16_t SECT239_232:1;             // 29 Sectors 239 - 232 Write Erase Protection
    uint16_t SECT247_240:1;             // 30 Sectors 247 - 240 Write Erase Protection
    uint16_t SECT255_248:1;             // 31 Sectors 255 - 248 Write Erase Protection
};

union SSU_WEPROT_FLC2_B2_B_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC2_B2_B_BITS  bit;
};

struct SSU_WEPROT_FLC2_B2_LOCK_BITS {   // bits description
    uint16_t LOCK:1;                    // 0 System Access Protection Register Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_FLC2_B2_LOCK_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC2_B2_LOCK_BITS  bit;
};

struct SSU_WEPROT_FLC2_B2_COMMIT_BITS { // bits description
    uint16_t COMMIT:1;                  // 0 System Access Protection Register Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_WEPROT_FLC2_B2_COMMIT_REG {
    uint32_t  all;
    struct  SSU_WEPROT_FLC2_B2_COMMIT_BITS  bit;
};

struct SSU_GEN_REGS {
    union   SSU_REVISION_REG                 REVISION;                     // Module Revision Register
    union   SSU_UPP_REVISION_REG             UPP_REVISION;                 // User Protection Policy Revision
    union   SSU_SSUMODE_REG                  SSUMODE;                      // Safety and Security Operational Mode
    union   SSU_LINK2_AP_OVERRIDE_REG        LINK2_AP_OVERRIDE;            // LINK2 Access Protection Override Register
    uint8_t                                  rsvd1[28];                    // Reserved
    union   SSU_BOOTMODE_STAT_REG            BOOTMODE_STAT;                // User Boot Mode Status Register
    union   SSU_EMU_BOOTPIN_CONFIG_REG       EMU_BOOTPIN_CONFIG;           // User Emulation Boot Pin Configuration
    union   SSU_EMU_BOOT_DIAG_REG            EMU_BOOT_DIAG;                // User Emulation Boot Options
    union   SSU_EMU_BOOT_CLKCFG_REG          EMU_BOOT_CLKCFG;              // User Emulation Boot Clock Configuration Register
    union   SSU_EMU_BOOTEN_REG               EMU_BOOTEN;                   // User Emulation Boot Enable
    union   SSU_RAMOPEN_LOCK_REG             RAMOPEN_LOCK;                 // RAMOPEN Feature Lock Register
    union   SSU_RAMOPEN_COMMIT_REG           RAMOPEN_COMMIT;               // RAMOPEN Feature Commit Register
    uint8_t                                  rsvd2[4];                     // Reserved
    union   SSU_CPUID_REG                    CPUID;                        // CPUID Register
    union   SSU_BANKMAP_REG                  BANKMAP;                      // Valid Banks
    union   SSU_BANKMAP_LOCK_REG             BANKMAP_LOCK;                 // Bank Map Lock Register
    union   SSU_BANKMAP_COMMIT_REG           BANKMAP_COMMIT;               // Bank Map Commit Register
    union   SSU_BANKMODE_REG                 BANKMODE;                     // Bank Mode Configuration Register
    union   SSU_BANKMODE_LOCK_REG            BANKMODE_LOCK;                // Bank Mode Lock Register
    union   SSU_BANKMODE_COMMIT_REG          BANKMODE_COMMIT;              // Bank Mode Commit Register
    union   SSU_SECCFG_UPDATE_CFG_REG        SECCFG_UPDATE_CFG;            // SECCFG Flash Update Configuration Register
    uint8_t                                  rsvd3[4];                     // Reserved
    union   SSU_PROG_BANKMODE_REG            PROG_BANKMODE;                // Programming BANKMODE Register
    union   SSU_SECVALID_REG                 SECVALID;                     // Valid SECCFG Sector
    union   SSU_SECVALID_LOCK_REG            SECVALID_LOCK;                // Valid SECCFG Sector Lock Register
    union   SSU_SECVALID_COMMIT_REG          SECVALID_COMMIT;              // Valid SECCFG Sector Commit Register
    union   SSU_ZONE1_CFG_REG                ZONE1_CFG;                    // ZONE1 Configuration
    union   SSU_ZONE2_CFG_REG                ZONE2_CFG;                    // ZONE2 Configuration
    union   SSU_ZONE3_CFG_REG                ZONE3_CFG;                    // ZONE3 Configuration
    uint8_t                                  rsvd4[4];                     // Reserved
    union   SSU_DEBUG_CFG_REG                DEBUG_CFG;                    // Debug Configuration
    union   SSU_DEBUG_CFG_LOCK_REG           DEBUG_CFG_LOCK;               // Debug Configuration Lock Register
    union   SSU_DEBUG_CFG_COMMIT_REG         DEBUG_CFG_COMMIT;             // Debug Configuration Commit Register
    uint8_t                                  rsvd5[4];                     // Reserved
    union   SSU_DEBUG_STAT_REG               DEBUG_STAT;                   // Debug Status Register
    union   SSU_C29DBGEN_REG                 C29DBGEN;                     // C29 Debug Enable Register
    union   SSU_ZONE_DBGEN_REG               ZONE_DBGEN;                   // ZONE Debug Enable Register
    uint8_t                                  rsvd6[340];                   // Reserved
    union   SSU_BEPROT_BANK_REG              BEPROT_BANK;                  // Bank Erase Protection Bank Register
    union   SSU_BEPROT_STAT_REG              BEPROT_STAT;                  // Bank Erase Status Register
    union   SSU_BEPROTA_REG                  BEPROTA;                      // Bank Erase Protection Register A
    union   SSU_BEPROTB_REG                  BEPROTB;                      // Bank Erase Protection Register B
    uint8_t                                  rsvd7[16];                    // Reserved
    union   SSU_FLSEMSTAT_REG                FLSEMSTAT;                    // Flash Controller Semaphore Status Register
    union   SSU_FLSEMREQ_REG                 FLSEMREQ;                     // Flash Controller Semaphore Request Register
    union   SSU_FLSEMCLR_REG                 FLSEMCLR;                     // Flash Controller Semaphore Clear Register
    uint8_t                                  rsvd8[4];                     // Reserved
    union   SSU_WEPROT_CODE_BANKS_REG        WEPROT_CODE_BANKS;            // Global Code Banks Write Erase
    union   SSU_WEPROT_CODE_BANKS_LOCK_REG   WEPROT_CODE_BANKS_LOCK;       // Global Code Banks Write Erase Lock
    union   SSU_WEPROT_CODE_BANKS_COMMIT_REG WEPROT_CODE_BANKS_COMMIT;     // Global Code Banks Write Erase Commit
    uint8_t                                  rsvd9[4];                     // Reserved
    union   SSU_WEPROT_DATA_BANKS_REG        WEPROT_DATA_BANKS;            // Global Data Banks Write Erase
    union   SSU_WEPROT_DATA_BANKS_LOCK_REG   WEPROT_DATA_BANKS_LOCK;       // Global Data Banks Write Erase Lock
    union   SSU_WEPROT_DATA_BANKS_COMMIT_REG WEPROT_DATA_BANKS_COMMIT;     // Global Data Banks Write Erase Commit
    uint8_t                                  rsvd10[180];                  // Reserved
    union   SSU_WEPROT_FLC1_B0_A_REG         WEPROT_FLC1_B0_A;             // Flash Controller 1 B0 Write Erase Protection A
    union   SSU_WEPROT_FLC1_B0_B_REG         WEPROT_FLC1_B0_B;             // Flash Controller 1 B0 Write Erase Protection B
    uint8_t                                  rsvd11[8];                    // Reserved
    union   SSU_WEPROT_FLC1_B0_LOCK_REG      WEPROT_FLC1_B0_LOCK;          // Flash Controller 1 B0 WEPROTA Lock
    union   SSU_WEPROT_FLC1_B0_COMMIT_REG    WEPROT_FLC1_B0_COMMIT;        // Flash Controller 1 B0 WEPROTA Commit
    uint8_t                                  rsvd12[40];                   // Reserved
    union   SSU_WEPROT_FLC1_B2_A_REG         WEPROT_FLC1_B2_A;             // Flash Controller 1 B2 Write Erase Protection A
    union   SSU_WEPROT_FLC1_B2_B_REG         WEPROT_FLC1_B2_B;             // Flash Controller 1 B2 Write Erase Protection B
    uint8_t                                  rsvd13[8];                    // Reserved
    union   SSU_WEPROT_FLC1_B2_LOCK_REG      WEPROT_FLC1_B2_LOCK;          // Flash Controller 1 B2 WEPROTA Lock
    union   SSU_WEPROT_FLC1_B2_COMMIT_REG    WEPROT_FLC1_B2_COMMIT;        // Flash Controller 1 B2 WEPROTA Commit
    uint8_t                                  rsvd14[72];                   // Reserved
    union   SSU_WEPROT_FLC2_B0_A_REG         WEPROT_FLC2_B0_A;             // Flash Controller 2 B0 Write Erase Protection A
    union   SSU_WEPROT_FLC2_B0_B_REG         WEPROT_FLC2_B0_B;             // Flash Controller 2 B0 Write Erase Protection B
    uint8_t                                  rsvd15[8];                    // Reserved
    union   SSU_WEPROT_FLC2_B0_LOCK_REG      WEPROT_FLC2_B0_LOCK;          // Flash Controller 2 B0 WEPROTA Lock
    union   SSU_WEPROT_FLC2_B0_COMMIT_REG    WEPROT_FLC2_B0_COMMIT;        // Flash Controller 2 B0 WEPROTA Commit
    uint8_t                                  rsvd16[40];                   // Reserved
    union   SSU_WEPROT_FLC2_B2_A_REG         WEPROT_FLC2_B2_A;             // Flash Controller 2 B2 Write Erase Protection A
    union   SSU_WEPROT_FLC2_B2_B_REG         WEPROT_FLC2_B2_B;             // Flash Controller 2 B2 Write Erase Protection B
    uint8_t                                  rsvd17[8];                    // Reserved
    union   SSU_WEPROT_FLC2_B2_LOCK_REG      WEPROT_FLC2_B2_LOCK;          // Flash Controller 2 B2 WEPROTA Lock
    union   SSU_WEPROT_FLC2_B2_COMMIT_REG    WEPROT_FLC2_B2_COMMIT;        // Flash Controller 2 B2 WEPROTA Commit
};

struct SSU_EMU_BOOTDEF_LOW_BITS {       // bits description
    uint16_t BOOT_DEF0:8;               // 7:0 Boot Definitions 0
    uint16_t BOOT_DEF1:8;               // 15:8 Boot Definitions 1
    uint16_t BOOT_DEF2:8;               // 23:16 Boot Definitions 2
    uint16_t BOOT_DEF3:8;               // 31:24 Boot Definitions 3
};

union SSU_EMU_BOOTDEF_LOW_REG {
    uint32_t  all;
    struct  SSU_EMU_BOOTDEF_LOW_BITS  bit;
};

struct SSU_EMU_BOOTDEF_HIGH_BITS {      // bits description
    uint16_t BOOT_DEF4:8;               // 7:0 Boot Definitions 4
    uint16_t BOOT_DEF5:8;               // 15:8 Boot Definitions 5
    uint16_t BOOT_DEF6:8;               // 23:16 Boot Definitions 6
    uint16_t BOOT_DEF7:8;               // 31:24 Boot Definitions 7
};

union SSU_EMU_BOOTDEF_HIGH_REG {
    uint32_t  all;
    struct  SSU_EMU_BOOTDEF_HIGH_BITS  bit;
};

struct SSU_LINK3_CFG_BITS {             // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK3_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK3_CFG_BITS  bit;
};

struct SSU_LINK4_CFG_BITS {             // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK4_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK4_CFG_BITS  bit;
};

struct SSU_LINK5_CFG_BITS {             // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK5_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK5_CFG_BITS  bit;
};

struct SSU_LINK6_CFG_BITS {             // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK6_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK6_CFG_BITS  bit;
};

struct SSU_LINK7_CFG_BITS {             // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK7_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK7_CFG_BITS  bit;
};

struct SSU_LINK8_CFG_BITS {             // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK8_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK8_CFG_BITS  bit;
};

struct SSU_LINK9_CFG_BITS {             // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK9_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK9_CFG_BITS  bit;
};

struct SSU_LINK10_CFG_BITS {            // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK10_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK10_CFG_BITS  bit;
};

struct SSU_LINK11_CFG_BITS {            // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK11_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK11_CFG_BITS  bit;
};

struct SSU_LINK12_CFG_BITS {            // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK12_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK12_CFG_BITS  bit;
};

struct SSU_LINK13_CFG_BITS {            // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK13_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK13_CFG_BITS  bit;
};

struct SSU_LINK14_CFG_BITS {            // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK14_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK14_CFG_BITS  bit;
};

struct SSU_LINK15_CFG_BITS {            // bits description
    uint16_t STACK:3;                   // 2:0 STACK Association
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_LINK15_CFG_REG {
    uint32_t  all;
    struct  SSU_LINK15_CFG_BITS  bit;
};

struct SSU_STACK3_CFG_BITS {            // bits description
    uint16_t ZONE:2;                    // 1:0 ZONE Association
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_STACK3_CFG_REG {
    uint32_t  all;
    struct  SSU_STACK3_CFG_BITS  bit;
};

struct SSU_STACK4_CFG_BITS {            // bits description
    uint16_t ZONE:2;                    // 1:0 ZONE Association
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_STACK4_CFG_REG {
    uint32_t  all;
    struct  SSU_STACK4_CFG_BITS  bit;
};

struct SSU_STACK5_CFG_BITS {            // bits description
    uint16_t ZONE:2;                    // 1:0 ZONE Association
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_STACK5_CFG_REG {
    uint32_t  all;
    struct  SSU_STACK5_CFG_BITS  bit;
};

struct SSU_STACK6_CFG_BITS {            // bits description
    uint16_t ZONE:2;                    // 1:0 ZONE Association
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_STACK6_CFG_REG {
    uint32_t  all;
    struct  SSU_STACK6_CFG_BITS  bit;
};

struct SSU_STACK7_CFG_BITS {            // bits description
    uint16_t ZONE:2;                    // 1:0 ZONE Association
    uint16_t rsvd1:14;                  // 15:2 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_STACK7_CFG_REG {
    uint32_t  all;
    struct  SSU_STACK7_CFG_BITS  bit;
};

struct SSU_RAMOPENSTAT_BITS {           // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t LINK1_RAMOPENS:1;          // 1 LINK1 RAM Open Status Bit
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SSU_RAMOPENSTAT_REG {
    uint32_t  all;
    struct  SSU_RAMOPENSTAT_BITS  bit;
};

struct SSU_RAMOPENFRC_BITS {            // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:3;                   // 3:1 Reserved
    uint16_t rsvd3:1;                   // 4 Reserved
    uint16_t rsvd4:3;                   // 7:5 Reserved
    uint16_t SET_LINK1:1;               // 8 Set LINK1 RAM Open Request
    uint16_t rsvd5:3;                   // 11:9 Reserved
    uint16_t WIPE_ON_LINK1_CLR:1;       // 12 Wipe LINK1 RAM on Clear Request
    uint16_t rsvd6:3;                   // 15:13 Reserved
    uint16_t rsvd7:16;                  // 31:16 Reserved
};

union SSU_RAMOPENFRC_REG {
    uint32_t  all;
    struct  SSU_RAMOPENFRC_BITS  bit;
};

struct SSU_RAMOPENCLR_BITS {            // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t CLEAR_LINK1:1;             // 1 Clear LINK1 RAM Open Request
    uint16_t rsvd2:14;                  // 15:2 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union SSU_RAMOPENCLR_REG {
    uint32_t  all;
    struct  SSU_RAMOPENCLR_BITS  bit;
};

struct SSU_DECODER_ADDR_IN_BITS {       // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDR_L:4;                  // 15:12 Address Bits 15:12
    uint16_t ADDR_H:16;                 // 31:16 Address Bits 31:16
};

union SSU_DECODER_ADDR_IN_REG {
    uint32_t  all;
    struct  SSU_DECODER_ADDR_IN_BITS  bit;
};

struct SSU_DECODER_OUT_BITS {           // bits description
    uint16_t LINK:4;                    // 3:0 Decoded LINK
    uint16_t STACK:3;                   // 6:4 Decoded STACK
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t ZONE:2;                    // 9:8 Decoded ZONE
    uint16_t rsvd2:6;                   // 15:10 Reserved
    uint16_t APR:7;                     // 22:16 Access Protection Region
    uint16_t rsvd3:8;                   // 30:23 Reserved
    uint16_t INVALID:1;                 // 31 Decoder Output Invalid
};

union SSU_DECODER_OUT_REG {
    uint32_t  all;
    struct  SSU_DECODER_OUT_BITS  bit;
};

struct SSU_EMU_DECODER_ADDR_IN_BITS {   // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDR_L:4;                  // 15:12 Address Bits 15:12
    uint16_t ADDR_H:16;                 // 31:16 Address Bits 31:16
};

union SSU_EMU_DECODER_ADDR_IN_REG {
    uint32_t  all;
    struct  SSU_EMU_DECODER_ADDR_IN_BITS  bit;
};

struct SSU_EMU_DECODER_OUT_BITS {       // bits description
    uint16_t LINK:4;                    // 3:0 Decoded LINK
    uint16_t STACK:3;                   // 6:4 Decoded STACK
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t ZONE:2;                    // 9:8 Decoded ZONE
    uint16_t rsvd2:6;                   // 15:10 Reserved
    uint16_t APR:7;                     // 22:16 Access Protection Region
    uint16_t rsvd3:8;                   // 30:23 Reserved
    uint16_t INVALID:1;                 // 31 Decoder Output Invalid
};

union SSU_EMU_DECODER_OUT_REG {
    uint32_t  all;
    struct  SSU_EMU_DECODER_OUT_BITS  bit;
};

struct SSU_CPU1_CFG_REGS {
    uint8_t                                  rsvd1[40];                    // Reserved
    union   SSU_EMU_BOOTDEF_LOW_REG          EMU_BOOTDEF_LOW;              // User Emulation Boot Definition Low Register
    union   SSU_EMU_BOOTDEF_HIGH_REG         EMU_BOOTDEF_HIGH;             // User Emulation Boot Definition High Register
    uint8_t                                  rsvd2[12];                    // Reserved
    union   SSU_LINK3_CFG_REG                LINK3_CFG;                    // LINK3 Configuration
    union   SSU_LINK4_CFG_REG                LINK4_CFG;                    // LINK4 Configuration
    union   SSU_LINK5_CFG_REG                LINK5_CFG;                    // LINK5 Configuration
    union   SSU_LINK6_CFG_REG                LINK6_CFG;                    // LINK6 Configuration
    union   SSU_LINK7_CFG_REG                LINK7_CFG;                    // LINK7 Configuration
    union   SSU_LINK8_CFG_REG                LINK8_CFG;                    // LINK8 Configuration
    union   SSU_LINK9_CFG_REG                LINK9_CFG;                    // LINK9 Configuration
    union   SSU_LINK10_CFG_REG               LINK10_CFG;                   // LINK10 Configuration
    union   SSU_LINK11_CFG_REG               LINK11_CFG;                   // LINK11 Configuration
    union   SSU_LINK12_CFG_REG               LINK12_CFG;                   // LINK12 Configuration
    union   SSU_LINK13_CFG_REG               LINK13_CFG;                   // LINK13 Configuration
    union   SSU_LINK14_CFG_REG               LINK14_CFG;                   // LINK14 Configuration
    union   SSU_LINK15_CFG_REG               LINK15_CFG;                   // LINK15 Configuration
    uint8_t                                  rsvd3[12];                    // Reserved
    union   SSU_STACK3_CFG_REG               STACK3_CFG;                   // STACK3 Configuration
    union   SSU_STACK4_CFG_REG               STACK4_CFG;                   // STACK4 Configuration
    union   SSU_STACK5_CFG_REG               STACK5_CFG;                   // STACK5 Configuration
    union   SSU_STACK6_CFG_REG               STACK6_CFG;                   // STACK6 Configuration
    union   SSU_STACK7_CFG_REG               STACK7_CFG;                   // STACK7 Configuration
    union   SSU_RAMOPENSTAT_REG              RAMOPENSTAT;                  // RAMOPEN Feature Status Register
    union   SSU_RAMOPENFRC_REG               RAMOPENFRC;                   // RAMOPEN Feature Force Register
    union   SSU_RAMOPENCLR_REG               RAMOPENCLR;                   // RAMOPEN Feature Clear Register
    uint8_t                                  rsvd4[4];                     // Reserved
    union   SSU_DECODER_ADDR_IN_REG          DECODER_ADDR_IN;              // SW ZONE Decoder Address Input
    union   SSU_DECODER_OUT_REG              DECODER_OUT;                  // SW ZONE Decoder Output
    union   SSU_EMU_DECODER_ADDR_IN_REG      EMU_DECODER_ADDR_IN;          // SW ZONE Decoder Address Input
    union   SSU_EMU_DECODER_OUT_REG          EMU_DECODER_OUT;              // SW ZONE Decoder Output
};

struct SSU_AP_CFG_BITS {                // bits description
    uint16_t LINKID:4;                  // 3:0 LINK ID Value
    uint16_t rsvd1:2;                   // 5:4 Reserved
    uint16_t APD:1;                     // 6 Access Protection Disable
    uint16_t XE:1;                      // 7 Execute Enable
    uint16_t APILINK:4;                 // 11:8 Access Protection Inheritance LINK
    uint16_t rsvd2:2;                   // 13:12 Reserved
    uint16_t APILINKE:1;                // 14 Access Protection Inheritance LINK Enable
    uint16_t rsvd3:1;                   // 15 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union SSU_AP_CFG_REG {
    uint32_t  all;
    struct  SSU_AP_CFG_BITS  bit;
};

struct SSU_AP_START_BITS {              // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower Start Address
    uint16_t ADDRH:8;                   // 23:16 Upper Start Address
    uint16_t rsvd2:4;                   // 27:24 Reserved
    uint16_t MEMTYPE:3;                 // 30:28 Start Address Memory Type
    uint16_t rsvd3:1;                   // 31 Reserved
};

union SSU_AP_START_REG {
    uint32_t  all;
    struct  SSU_AP_START_BITS  bit;
};

struct SSU_AP_END_BITS {                // bits description
    uint16_t rsvd1:12;                  // 11:0 Reserved
    uint16_t ADDRL:4;                   // 15:12 Lower End Address
    uint16_t ADDRH:8;                   // 23:16 Upper End Address
    uint16_t rsvd2:4;                   // 27:24 Reserved
    uint16_t MEMTYPE:3;                 // 30:28 Start Address Memory Type
    uint16_t rsvd3:1;                   // 31 Reserved
};

union SSU_AP_END_REG {
    uint32_t  all;
    struct  SSU_AP_END_BITS  bit;
};

struct SSU_AP_LOCK_BITS {               // bits description
    uint16_t LOCK:1;                    // 0 Temporary Lock
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_AP_LOCK_REG {
    uint32_t  all;
    struct  SSU_AP_LOCK_BITS  bit;
};

struct SSU_AP_COMMIT_BITS {             // bits description
    uint16_t COMMIT:1;                  // 0 Permanent Commit
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_AP_COMMIT_REG {
    uint32_t  all;
    struct  SSU_AP_COMMIT_BITS  bit;
};

struct SSU_AP_ACCESS_BITS {             // bits description
    uint16_t LINK0:2;                   // 1:0 LINK0 Access Permissions
    uint16_t LINK1:2;                   // 3:2 LINK1 Access Permissions
    uint16_t LINK2:2;                   // 5:4 LINK2 Access Permissions
    uint16_t LINK3:2;                   // 7:6 LINK3 Access Permissions
    uint16_t LINK4:2;                   // 9:8 LINK4 Access Permissions
    uint16_t LINK5:2;                   // 11:10 LINK5 Access Permissions
    uint16_t LINK6:2;                   // 13:12 LINK6 Access Permissions
    uint16_t LINK7:2;                   // 15:14 LINK7 Access Permissions
    uint16_t LINK8:2;                   // 17:16 LINK8 Access Permissions
    uint16_t LINK9:2;                   // 19:18 LINK9 Access Permissions
    uint16_t LINK10:2;                  // 21:20 LINK10 Access Permissions
    uint16_t LINK11:2;                  // 23:22 LINK11 Access Permissions
    uint16_t LINK12:2;                  // 25:24 LINK12 Access Permissions
    uint16_t LINK13:2;                  // 27:26 LINK13 Access Permissions
    uint16_t LINK14:2;                  // 29:28 LINK14 Access Permissions
    uint16_t LINK15:2;                  // 31:30 LINK15 Access Permissions
};

union SSU_AP_ACCESS_REG {
    uint32_t  all;
    struct  SSU_AP_ACCESS_BITS  bit;
};

struct CPU1_AP_REGS {
    union   SSU_AP_CFG_REG                   AP_CFG;                       // Access Protection  Configuration
    union   SSU_AP_START_REG                 AP_START;                     // Access Protection  Start Address
    union   SSU_AP_END_REG                   AP_END;                       // Access Protection  End Address
    union   SSU_AP_LOCK_REG                  AP_LOCK;                      // Access Protection  Temporary Lock
    union   SSU_AP_COMMIT_REG                AP_COMMIT;                    // Access Protection  Permanent Commit
    union   SSU_AP_ACCESS_REG                AP_ACCESS;                    // Access Protection  R/W Access Permissions
    uint8_t                                  rsvd1[8];                     // Reserved
};

struct SSU_CPU1_AP_REGS {
    struct CPU1_AP_REGS                      CPU1_AP[64];                  // 
};

struct SSU_RST_LINK_BITS {              // bits description
    uint16_t LINK:4;                    // 3:0 Reset LINK Value
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_RST_LINK_REG {
    uint32_t  all;
    struct  SSU_RST_LINK_BITS  bit;
};

struct SSU_CPU_RST_CTRL_BITS {          // bits description
    uint16_t SW_SYSRSN:8;               // 7:0 System CPU Reset
    uint16_t rsvd1:8;                   // 15:8 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_CPU_RST_CTRL_REG {
    uint32_t  all;
    struct  SSU_CPU_RST_CTRL_BITS  bit;
};

struct SSU_DEF_NMI_LINK_BITS {          // bits description
    uint16_t LINK:4;                    // 3:0 Default NMI LINK Value
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union SSU_DEF_NMI_LINK_REG {
    uint32_t  all;
    struct  SSU_DEF_NMI_LINK_BITS  bit;
};

struct SSU_CPU2_CFG_REGS {
    uint32_t                                 RST_VECT;                     // CPU Reset Vector
    union   SSU_RST_LINK_REG                 RST_LINK;                     // CPU Reset LINK
    union   SSU_CPU_RST_CTRL_REG             CPU_RST_CTRL;                 // CPU Reset Control
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 DEF_NMI_VECT;                 // Default CPU NMI Vector
    union   SSU_DEF_NMI_LINK_REG             DEF_NMI_LINK;                 // Default CPU NMI LINK
    uint8_t                                  rsvd2[16];                    // Reserved
    union   SSU_EMU_BOOTDEF_LOW_REG          EMU_BOOTDEF_LOW;              // User Emulation Boot Definition Low Register
    union   SSU_EMU_BOOTDEF_HIGH_REG         EMU_BOOTDEF_HIGH;             // User Emulation Boot Definition High Register
    uint8_t                                  rsvd3[12];                    // Reserved
    union   SSU_LINK3_CFG_REG                LINK3_CFG;                    // LINK3 Configuration
    union   SSU_LINK4_CFG_REG                LINK4_CFG;                    // LINK4 Configuration
    union   SSU_LINK5_CFG_REG                LINK5_CFG;                    // LINK5 Configuration
    union   SSU_LINK6_CFG_REG                LINK6_CFG;                    // LINK6 Configuration
    union   SSU_LINK7_CFG_REG                LINK7_CFG;                    // LINK7 Configuration
    union   SSU_LINK8_CFG_REG                LINK8_CFG;                    // LINK8 Configuration
    union   SSU_LINK9_CFG_REG                LINK9_CFG;                    // LINK9 Configuration
    union   SSU_LINK10_CFG_REG               LINK10_CFG;                   // LINK10 Configuration
    union   SSU_LINK11_CFG_REG               LINK11_CFG;                   // LINK11 Configuration
    union   SSU_LINK12_CFG_REG               LINK12_CFG;                   // LINK12 Configuration
    union   SSU_LINK13_CFG_REG               LINK13_CFG;                   // LINK13 Configuration
    union   SSU_LINK14_CFG_REG               LINK14_CFG;                   // LINK14 Configuration
    union   SSU_LINK15_CFG_REG               LINK15_CFG;                   // LINK15 Configuration
    uint8_t                                  rsvd4[12];                    // Reserved
    union   SSU_STACK3_CFG_REG               STACK3_CFG;                   // STACK3 Configuration
    union   SSU_STACK4_CFG_REG               STACK4_CFG;                   // STACK4 Configuration
    union   SSU_STACK5_CFG_REG               STACK5_CFG;                   // STACK5 Configuration
    union   SSU_STACK6_CFG_REG               STACK6_CFG;                   // STACK6 Configuration
    union   SSU_STACK7_CFG_REG               STACK7_CFG;                   // STACK7 Configuration
    union   SSU_RAMOPENSTAT_REG              RAMOPENSTAT;                  // RAMOPEN Feature Status Register
    union   SSU_RAMOPENFRC_REG               RAMOPENFRC;                   // RAMOPEN Feature Force Register
    union   SSU_RAMOPENCLR_REG               RAMOPENCLR;                   // RAMOPEN Feature Clear Register
    uint8_t                                  rsvd5[4];                     // Reserved
    union   SSU_DECODER_ADDR_IN_REG          DECODER_ADDR_IN;              // SW ZONE Decoder Address Input
    union   SSU_DECODER_OUT_REG              DECODER_OUT;                  // SW ZONE Decoder Output
    union   SSU_EMU_DECODER_ADDR_IN_REG      EMU_DECODER_ADDR_IN;          // SW ZONE Decoder Address Input
    union   SSU_EMU_DECODER_OUT_REG          EMU_DECODER_OUT;              // SW ZONE Decoder Output
};

struct CPU2_AP_REGS {
    union   SSU_AP_CFG_REG                   AP_CFG;                       // Access Protection  Configuration
    union   SSU_AP_START_REG                 AP_START;                     // Access Protection  Start Address
    union   SSU_AP_END_REG                   AP_END;                       // Access Protection  End Address
    union   SSU_AP_LOCK_REG                  AP_LOCK;                      // Access Protection  Temporary Lock
    union   SSU_AP_COMMIT_REG                AP_COMMIT;                    // Access Protection  Permanent Commit
    union   SSU_AP_ACCESS_REG                AP_ACCESS;                    // Access Protection  R/W Access Permissions
    uint8_t                                  rsvd1[8];                     // Reserved
};

struct SSU_CPU2_AP_REGS {
    struct CPU2_AP_REGS                      CPU2_AP[64];               // 
};

struct SSU_CPU3_CFG_REGS {
    uint32_t                                 RST_VECT;                     // CPU Reset Vector
    union   SSU_RST_LINK_REG                 RST_LINK;                     // CPU Reset LINK
    union   SSU_CPU_RST_CTRL_REG             CPU_RST_CTRL;                 // CPU Reset Control
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 DEF_NMI_VECT;                 // Default CPU NMI Vector
    union   SSU_DEF_NMI_LINK_REG             DEF_NMI_LINK;                 // Default CPU NMI LINK
    uint8_t                                  rsvd2[16];                    // Reserved
    union   SSU_EMU_BOOTDEF_LOW_REG          EMU_BOOTDEF_LOW;              // User Emulation Boot Definition Low Register
    union   SSU_EMU_BOOTDEF_HIGH_REG         EMU_BOOTDEF_HIGH;             // User Emulation Boot Definition High Register
    uint8_t                                  rsvd3[12];                    // Reserved
    union   SSU_LINK3_CFG_REG                LINK3_CFG;                    // LINK3 Configuration
    union   SSU_LINK4_CFG_REG                LINK4_CFG;                    // LINK4 Configuration
    union   SSU_LINK5_CFG_REG                LINK5_CFG;                    // LINK5 Configuration
    union   SSU_LINK6_CFG_REG                LINK6_CFG;                    // LINK6 Configuration
    union   SSU_LINK7_CFG_REG                LINK7_CFG;                    // LINK7 Configuration
    union   SSU_LINK8_CFG_REG                LINK8_CFG;                    // LINK8 Configuration
    union   SSU_LINK9_CFG_REG                LINK9_CFG;                    // LINK9 Configuration
    union   SSU_LINK10_CFG_REG               LINK10_CFG;                   // LINK10 Configuration
    union   SSU_LINK11_CFG_REG               LINK11_CFG;                   // LINK11 Configuration
    union   SSU_LINK12_CFG_REG               LINK12_CFG;                   // LINK12 Configuration
    union   SSU_LINK13_CFG_REG               LINK13_CFG;                   // LINK13 Configuration
    union   SSU_LINK14_CFG_REG               LINK14_CFG;                   // LINK14 Configuration
    union   SSU_LINK15_CFG_REG               LINK15_CFG;                   // LINK15 Configuration
    uint8_t                                  rsvd4[12];                    // Reserved
    union   SSU_STACK3_CFG_REG               STACK3_CFG;                   // STACK3 Configuration
    union   SSU_STACK4_CFG_REG               STACK4_CFG;                   // STACK4 Configuration
    union   SSU_STACK5_CFG_REG               STACK5_CFG;                   // STACK5 Configuration
    union   SSU_STACK6_CFG_REG               STACK6_CFG;                   // STACK6 Configuration
    union   SSU_STACK7_CFG_REG               STACK7_CFG;                   // STACK7 Configuration
    union   SSU_RAMOPENSTAT_REG              RAMOPENSTAT;                  // RAMOPEN Feature Status Register
    union   SSU_RAMOPENFRC_REG               RAMOPENFRC;                   // RAMOPEN Feature Force Register
    union   SSU_RAMOPENCLR_REG               RAMOPENCLR;                   // RAMOPEN Feature Clear Register
    uint8_t                                  rsvd5[4];                     // Reserved
    union   SSU_DECODER_ADDR_IN_REG          DECODER_ADDR_IN;              // SW ZONE Decoder Address Input
    union   SSU_DECODER_OUT_REG              DECODER_OUT;                  // SW ZONE Decoder Output
    union   SSU_EMU_DECODER_ADDR_IN_REG      EMU_DECODER_ADDR_IN;          // SW ZONE Decoder Address Input
    union   SSU_EMU_DECODER_OUT_REG          EMU_DECODER_OUT;              // SW ZONE Decoder Output
};

struct CPU3_AP_REGS {
    union   SSU_AP_CFG_REG                   AP_CFG;                       // Access Protection  Configuration
    union   SSU_AP_START_REG                 AP_START;                     // Access Protection  Start Address
    union   SSU_AP_END_REG                   AP_END;                       // Access Protection  End Address
    union   SSU_AP_LOCK_REG                  AP_LOCK;                      // Access Protection  Temporary Lock
    union   SSU_AP_COMMIT_REG                AP_COMMIT;                    // Access Protection  Permanent Commit
    union   SSU_AP_ACCESS_REG                AP_ACCESS;                    // Access Protection  R/W Access Permissions
    uint8_t                                  rsvd1[8];                     // Reserved
};

struct SSU_CPU3_AP_REGS {
    struct CPU3_AP_REGS                      CPU3_AP[64];                  // 
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
