//###########################################################################
//
// FILE:    hwbf_esm_safety_aggregator.h
//
// TITLE:   Definitions for the ESM_SAFETY_AGGREGATOR registers.
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

#ifndef HWBF_ESM_SAFETY_AGGREGATOR_H
#define HWBF_ESM_SAFETY_AGGREGATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hwbf_edc.h"

//---------------------------------------------------------------------------
// ESM_SAFETY_AGGREGATOR Individual Register Bit Definitions:

struct ESM_SAFETY_AGGREGATOR_aggr_revision_BITS {// bits description
    uint16_t revmin:6;                  // 5:0
    uint16_t custom:2;                  // 7:6
    uint16_t revmaj:3;                  // 10:8
    uint16_t revrtl:5;                  // 15:11
    uint16_t module_id:12;              // 27:16
    uint16_t bu:2;                      // 29:28
    uint16_t scheme:2;                  // 31:30
};

union ESM_SAFETY_AGGREGATOR_aggr_revision_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_aggr_revision_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_ecc_vector_BITS {// bits description
    uint16_t ecc_vector:11;             // 10:0
    uint16_t rsvd1:4;                   // 14:11
    uint16_t rd_svbus:1;                // 15
    uint16_t rd_svbus_address:8;        // 23:16
    uint16_t rd_svbus_done:1;           // 24
};

union ESM_SAFETY_AGGREGATOR_ecc_vector_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_ecc_vector_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_misc_status_BITS {// bits description
    uint16_t num_rams:11;               // 10:0
};

union ESM_SAFETY_AGGREGATOR_misc_status_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_misc_status_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_ded_eoi_reg_BITS {// bits description
    uint16_t eoi_wr:1;                  // 0
};

union ESM_SAFETY_AGGREGATOR_ded_eoi_reg_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_ded_eoi_reg_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_ded_status_reg0_BITS {// bits description
    uint16_t esmss_sys_esm_edc_ctrl_busecc_pend:1; // 0
    uint16_t esmss_esm0_edc_ctrl_busecc_pend:1; // 1
    uint16_t esmss_esm1_edc_ctrl_busecc_pend:1; // 2
    uint16_t esmss_esm2_edc_ctrl_busecc_pend:1; // 3
};

union ESM_SAFETY_AGGREGATOR_ded_status_reg0_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_ded_status_reg0_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_ded_enable_set_reg0_BITS {// bits description
    uint16_t esmss_sys_esm_edc_ctrl_busecc_enable_set:1; // 0
    uint16_t esmss_esm0_edc_ctrl_busecc_enable_set:1; // 1
    uint16_t esmss_esm1_edc_ctrl_busecc_enable_set:1; // 2
    uint16_t esmss_esm2_edc_ctrl_busecc_enable_set:1; // 3
};

union ESM_SAFETY_AGGREGATOR_ded_enable_set_reg0_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_ded_enable_set_reg0_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_ded_enable_clr_reg0_BITS {// bits description
    uint16_t esmss_sys_esm_edc_ctrl_busecc_enable_clr:1; // 0
    uint16_t esmss_esm0_edc_ctrl_busecc_enable_clr:1; // 1
    uint16_t esmss_esm1_edc_ctrl_busecc_enable_clr:1; // 2
    uint16_t esmss_esm2_edc_ctrl_busecc_enable_clr:1; // 3
};

union ESM_SAFETY_AGGREGATOR_ded_enable_clr_reg0_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_ded_enable_clr_reg0_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_aggr_enable_set_BITS {// bits description
    uint16_t parity:1;                  // 0
    uint16_t timeout:1;                 // 1
};

union ESM_SAFETY_AGGREGATOR_aggr_enable_set_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_aggr_enable_set_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_aggr_enable_clr_BITS {// bits description
    uint16_t parity:1;                  // 0
    uint16_t timeout:1;                 // 1
};

union ESM_SAFETY_AGGREGATOR_aggr_enable_clr_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_aggr_enable_clr_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_aggr_status_set_BITS {// bits description
    uint16_t parity:2;                  // 1:0
    uint16_t timeout:2;                 // 3:2
};

union ESM_SAFETY_AGGREGATOR_aggr_status_set_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_aggr_status_set_BITS  bit;
};

struct ESM_SAFETY_AGGREGATOR_aggr_status_clr_BITS {// bits description
    uint16_t parity:2;                  // 1:0
    uint16_t timeout:2;                 // 3:2
};

union ESM_SAFETY_AGGREGATOR_aggr_status_clr_REG {
    uint32_t  all;
    struct  ESM_SAFETY_AGGREGATOR_aggr_status_clr_BITS  bit;
};

struct ESM_SAFETYAGG_REGS {
    union   ESM_SAFETY_AGGREGATOR_aggr_revision_REG aggr_revision;         // Aggregator Revision Register
    uint8_t                                  rsvd1[4];                     // Reserved
    union   ESM_SAFETY_AGGREGATOR_ecc_vector_REG ecc_vector;               // ECC Vector Register
    union   ESM_SAFETY_AGGREGATOR_misc_status_REG misc_status;             // Misc Status
    struct  EDC_REGS                         EDC_Regs;                     // EDC Registers
    uint8_t                                  rsvd2[8];                     // Reserved
    uint8_t                                  rsvd3[252];                   // Reserved
    union   ESM_SAFETY_AGGREGATOR_ded_eoi_reg_REG ded_eoi_reg;             // EOI Register
    union   ESM_SAFETY_AGGREGATOR_ded_status_reg0_REG ded_status_reg0;     // Interrupt Status Register 0
    uint8_t                                  rsvd4[60];                    // Reserved
    union   ESM_SAFETY_AGGREGATOR_ded_enable_set_reg0_REG ded_enable_set_reg0; // Interrupt Enable Set Register 0
    uint8_t                                  rsvd5[60];                    // Reserved
    union   ESM_SAFETY_AGGREGATOR_ded_enable_clr_reg0_REG ded_enable_clr_reg0; // Interrupt Enable Clear Register 0
    uint8_t                                  rsvd6[60];                    // Reserved
    union   ESM_SAFETY_AGGREGATOR_aggr_enable_set_REG aggr_enable_set;     // AGGR interrupt enable set Register
    union   ESM_SAFETY_AGGREGATOR_aggr_enable_clr_REG aggr_enable_clr;     // AGGR interrupt enable clear Register
    union   ESM_SAFETY_AGGREGATOR_aggr_status_set_REG aggr_status_set;     // AGGR interrupt status set Register
    union   ESM_SAFETY_AGGREGATOR_aggr_status_clr_REG aggr_status_clr;     // AGGR interrupt status clear Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
