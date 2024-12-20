//###########################################################################
//
// FILE:    hwbf_esm_cpu.h
//
// TITLE:   Definitions for the ESM_CPU registers.
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

#ifndef HWBF_ESM_CPU_H
#define HWBF_ESM_CPU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// ESM_CPU Individual Register Bit Definitions:

struct ESM_CPU_ERR_GRP_REGS {
    uint32_t                                 RAW;                          // Error Group N Event Raw Status/Set Register
    uint32_t                                 STS;                          // Error Group N Interrupt Enable Status/Clear Register
    uint32_t                                 INTR_EN_SET;                  // Error Group N Interrupt Enable Set Register
    uint32_t                                 INTR_EN_CLR;                  // Error Group N Interrupt Enabled Clear Register
    uint32_t                                 INT_PRIO;                     // Error Group N Interrupt Priority Register
    uint32_t                                 PIN_EN_SET;                   // Error Group N Error Pin Influence Set Register
    uint32_t                                 PIN_EN_CLR;                   // Error Group N Error Pin Influence Clear Register
    uint32_t                                 rsvd;
};

struct ESM_CPU_ERR_EXT_GRP_REGS {
    uint32_t                                 CRIT_EN_SET;                  // Error Group N Critical Priority Interrupt Influence Set Register
    uint32_t                                 CRIT_EN_CLR;                  // Error Group N Critical Priority Interrupt Influence Clear Register
    uint32_t                                 rsvd1;
    uint32_t                                 rsvd2;
    uint32_t                                 rsvd3;
    uint32_t                                 rsvd4;
    uint32_t                                 rsvd5;
    uint32_t                                 rsvd6;
};

struct ESM_CPU_PID_BITS {               // bits description
    uint16_t minor:6;                   // 5:0
    uint16_t custom:2;                  // 7:6
    uint16_t major:3;                   // 10:8
    uint16_t rtl:5;                     // 15:11
    uint16_t func:12;                   // 27:16
    uint16_t bu:2;                      // 29:28
    uint16_t scheme:2;                  // 31:30
};

union ESM_CPU_PID_REG {
    uint32_t  all;
    struct  ESM_CPU_PID_BITS  bit;
};

struct ESM_CPU_INFO_BITS {              // bits description
    uint16_t groups:8;                  // 7:0
    uint16_t pulse_groups:8;            // 15:8
    uint16_t crit_intr:1;               // 30
    uint16_t last_reset:1;              // 31
};

union ESM_CPU_INFO_REG {
    uint32_t  all;
    struct  ESM_CPU_INFO_BITS  bit;
};

struct ESM_CPU_EN_BITS {                // bits description
    uint16_t key:4;                     // 3:0
};

union ESM_CPU_EN_REG {
    uint32_t  all;
    struct  ESM_CPU_EN_BITS  bit;
};

struct ESM_CPU_SFT_RST_BITS {           // bits description
    uint16_t key:4;                     // 3:0
};

union ESM_CPU_SFT_RST_REG {
    uint32_t  all;
    struct  ESM_CPU_SFT_RST_BITS  bit;
};

struct ESM_CPU_LOW_PRI_BITS {           // bits description
    uint16_t lvl:16;                    // 15:0
    uint16_t pls:16;                    // 31:16
};

union ESM_CPU_LOW_PRI_REG {
    uint32_t  all;
    struct  ESM_CPU_LOW_PRI_BITS  bit;
};

struct ESM_CPU_HI_PRI_BITS {            // bits description
    uint16_t lvl:16;                    // 15:0
    uint16_t pls:16;                    // 31:16
};

union ESM_CPU_HI_PRI_REG {
    uint32_t  all;
    struct  ESM_CPU_HI_PRI_BITS  bit;
};

struct ESM_CPU_EOI_BITS {               // bits description
    uint16_t key:11;                    // 10:0
};

union ESM_CPU_EOI_REG {
    uint32_t  all;
    struct  ESM_CPU_EOI_BITS  bit;
};

struct ESM_CPU_PIN_CTRL_BITS {          // bits description
    uint16_t key:4;                     // 3:0
    uint16_t pwm_en:4;                  // 7:4
    uint16_t polarity:4;                // 11:8
};

union ESM_CPU_PIN_CTRL_REG {
    uint32_t  all;
    struct  ESM_CPU_PIN_CTRL_BITS  bit;
};

struct ESM_CPU_PIN_STS_BITS {           // bits description
    uint16_t val:1;                     // 0
};

union ESM_CPU_PIN_STS_REG {
    uint32_t  all;
    struct  ESM_CPU_PIN_STS_BITS  bit;
};

struct ESM_CPU_PIN_CNTR_BITS {          // bits description
    uint32_t count:24;                  // 23:0
};

union ESM_CPU_PIN_CNTR_REG {
    uint32_t  all;
    struct  ESM_CPU_PIN_CNTR_BITS  bit;
};

struct ESM_CPU_PIN_CNTR_PRE_BITS {      // bits description
    uint32_t count:24;                  // 23:0
};

union ESM_CPU_PIN_CNTR_PRE_REG {
    uint32_t  all;
    struct  ESM_CPU_PIN_CNTR_PRE_BITS  bit;
};

struct ESM_CPU_PWMH_PIN_CNTR_BITS {     // bits description
    uint32_t count:24;                  // 23:0
};

union ESM_CPU_PWMH_PIN_CNTR_REG {
    uint32_t  all;
    struct  ESM_CPU_PWMH_PIN_CNTR_BITS  bit;
};

struct ESM_CPU_PWMH_PIN_CNTR_PRE_BITS { // bits description
    uint32_t count:24;                  // 23:0
};

union ESM_CPU_PWMH_PIN_CNTR_PRE_REG {
    uint32_t  all;
    struct  ESM_CPU_PWMH_PIN_CNTR_PRE_BITS  bit;
};

struct ESM_CPU_PWML_PIN_CNTR_BITS {     // bits description
    uint32_t count:24;                  // 23:0
};

union ESM_CPU_PWML_PIN_CNTR_REG {
    uint32_t  all;
    struct  ESM_CPU_PWML_PIN_CNTR_BITS  bit;
};

struct ESM_CPU_PWML_PIN_CNTR_PRE_BITS { // bits description
    uint32_t count:24;                  // 23:0
};

union ESM_CPU_PWML_PIN_CNTR_PRE_REG {
    uint32_t  all;
    struct  ESM_CPU_PWML_PIN_CNTR_PRE_BITS  bit;
};

struct ESM_CPU_HI_PRI_WD_CFG_BITS {     // bits description
    uint16_t wd_en:4;                   // 3:0
    uint16_t rsvd1:4;    
    uint16_t emu_free:4;                // 11:8
};

union ESM_CPU_HI_PRI_WD_CFG_REG {
    uint32_t  all;
    struct  ESM_CPU_HI_PRI_WD_CFG_BITS  bit;
};

struct ESM_CPU_HI_PRI_WD_INTR_SET_BITS {// bits description
    uint16_t val:1;                     // 0
};

union ESM_CPU_HI_PRI_WD_INTR_SET_REG {
    uint32_t  all;
    struct  ESM_CPU_HI_PRI_WD_INTR_SET_BITS  bit;
};

struct ESM_CPU_HI_PRI_WD_INTR_CLR_BITS {// bits description
    uint16_t val:1;                     // 0
};

union ESM_CPU_HI_PRI_WD_INTR_CLR_REG {
    uint32_t  all;
    struct  ESM_CPU_HI_PRI_WD_INTR_CLR_BITS  bit;
};

struct ESM_CPU_MMR_CONFIG_LOCK_BITS {   // bits description
    uint16_t hi_pri_wd_lock:1;          // 0
    uint16_t errpin_mon_lock:1;         // 1
    uint16_t errpin_lock:1;             // 2
    uint16_t rsvd1:2;                   
    uint16_t global_soft_rst_lock:1;    // 5
    uint16_t rsvd2:2;                   
    uint16_t globel_en_lock:1;          // 8
};

union ESM_CPU_MMR_CONFIG_LOCK_REG {
    uint32_t  all;
    struct  ESM_CPU_MMR_CONFIG_LOCK_BITS  bit;
};

struct ESM_CPU_MMR_CONFIG_COMMIT_BITS { // bits description
    uint16_t hi_pri_wd_commit:1;          // 0
    uint16_t errpin_mon_commit:1;         // 1
    uint16_t errpin_commit:1;             // 2
    uint16_t rsvd1:2;                   
    uint16_t global_soft_rst_commit:1;    // 5
    uint16_t rsvd2:2;                   
    uint16_t globel_en_commit:1;          // 8
};

union ESM_CPU_MMR_CONFIG_COMMIT_REG {
    uint32_t  all;
    struct  ESM_CPU_MMR_CONFIG_COMMIT_BITS  bit;
};

struct ESM_CPU_REGS {
    union   ESM_CPU_PID_REG                  PID;                          // Revision Register
    union   ESM_CPU_INFO_REG                 INFO;                         // Info Register
    union   ESM_CPU_EN_REG                   EN;                           // Global Enable Register
    union   ESM_CPU_SFT_RST_REG              SFT_RST;                      // Global Soft Reset Register
    uint8_t                                  rsvd1[16];                    // Reserved
    union   ESM_CPU_LOW_PRI_REG              LOW_PRI;                      // Low Priority Prioritized Register
    union   ESM_CPU_HI_PRI_REG               HI_PRI;                       // High Priority Prioritized Register
    uint32_t                                 LOW;                          // Low Priority Interrupt Status Register
    uint32_t                                 HI;                           // High Priority Interrupt Status Register
    union   ESM_CPU_EOI_REG                  EOI;                          // EOI Interrupt Register
    uint8_t                                  rsvd2[12];                    // Reserved
    union   ESM_CPU_PIN_CTRL_REG             PIN_CTRL;                     // Error Pin Control Register
    union   ESM_CPU_PIN_STS_REG              PIN_STS;                      // Error Pin Status Register
    union   ESM_CPU_PIN_CNTR_REG             PIN_CNTR;                     // Error Counter Value Register
    union   ESM_CPU_PIN_CNTR_PRE_REG         PIN_CNTR_PRE;                 // Error Counter Value Pre-Load Register
    union   ESM_CPU_PWMH_PIN_CNTR_REG        PWMH_PIN_CNTR;                // Error PWM High Counter Value Register
    union   ESM_CPU_PWMH_PIN_CNTR_PRE_REG    PWMH_PIN_CNTR_PRE;            // Error PWM High Counter Value Pre-Load Register
    union   ESM_CPU_PWML_PIN_CNTR_REG        PWML_PIN_CNTR;                // Error PWM Low Counter Value Register
    union   ESM_CPU_PWML_PIN_CNTR_PRE_REG    PWML_PIN_CNTR_PRE;            // Error PWM Low Counter Value Pre-Load Register
    uint8_t                                  rsvd3[32];                    // Reserved
    union   ESM_CPU_HI_PRI_WD_CFG_REG        HI_PRI_WD_CFG;                // High Priority Watchdog Config Register
    uint32_t                                 HI_PRI_WD_CNTR;               // High Priority Watchdog Counter Value Register
    uint32_t                                 HI_PRI_WD_CNTR_PRE;           // High Priority Watchdog Pre-Load Register
    union   ESM_CPU_HI_PRI_WD_INTR_SET_REG   HI_PRI_WD_INTR_SET;           // High Priority Watchdog Interrupt Status/Set Register
    union   ESM_CPU_HI_PRI_WD_INTR_CLR_REG   HI_PRI_WD_INTR_CLR;           // High Priority Watchdog Interrupt Status/Clear Register
    uint8_t                                  rsvd4[108];                   // Reserved
    uint32_t                                 GROUP_N_LOCK;                 // Group N Interrupt Lock Register
    uint32_t                                 GROUP_N_COMMIT;               // Group N Interrupt Commit Register
    uint8_t                                  rsvd5[8];                     // Reserved
    uint32_t                                 ERR_PIN_INFLUENCE_LOCK;       // Error Pin Influence Lock Register
    uint32_t                                 ERR_PIN_INFLUENCE_COMMIT;     // Error Pin Influence Commit Register
    uint32_t                                 CRI_PRI_INFLUENCE_LOCK;       // Critical Prioirty Interrupt Influence Lock Register
    uint32_t                                 CRI_PRI_INFLUENCE_COMMIT;     // Critical Priority Interrupt Influence Lock Register
    union   ESM_CPU_MMR_CONFIG_LOCK_REG      MMR_CONFIG_LOCK;              // MMR Config Lock Register
    union   ESM_CPU_MMR_CONFIG_COMMIT_REG    MMR_CONFIG_COMMIT;            // MMR Config Commit Register
    uint8_t                                  rsvd6[728];                   // Reserved
    struct ESM_CPU_ERR_GRP_REGS              ERR_GRP[8];                   // 
    uint8_t                                  rsvd7[768];                   // Reserved
    struct ESM_CPU_ERR_EXT_GRP_REGS          ERR_EXT_GRP[8];               // 
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
