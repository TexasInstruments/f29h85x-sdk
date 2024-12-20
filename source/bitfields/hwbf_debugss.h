//###########################################################################
//
// FILE:    hwbf_debugss.h
//
// TITLE:   Definitions for the DEBUGSS registers.
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

#ifndef HWBF_DEBUGSS_H
#define HWBF_DEBUGSS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// DEBUGSS Individual Register Bit Definitions:

struct DEBUGSS_PASSWORD_ID_BITS {       // bits description
    uint16_t ID:4;                      // 3:0 Password ID
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DEBUGSS_PASSWORD_ID_REG {
    uint32_t  all;
    struct  DEBUGSS_PASSWORD_ID_BITS  bit;
};

struct DEBUGSS_DEBUG_ENABLE_STATUS_BITS {// bits description
    uint16_t JTAG_DBGEN:1;              // 0 JTAG Full Debug enable
    uint16_t ZONE0_DBGEN:1;             // 1 Zone1 Full Debug enable
    uint16_t ZONE1_DBGEN:1;             // 2 Zone2 Full Debug enable
    uint16_t ZONE2_DBGEN:1;             // 3 Zone3 Full Debug enable
    uint16_t ZONE3_DBGEN:1;             // 4 Zone4 Full Debug enable
    uint16_t rsvd1:3;                   // 7:5 Reserved
    uint16_t PARTIAL_ZONE1_DBGEN:1;     // 8 Partial Zone1 Debug enable
    uint16_t PARTIAL_ZONE2_DBGEN:1;     // 9 Partial Zone2 Debug enable
    uint16_t PARTIAL_ZONE3_DBGEN:1;     // 10 Partial Zone3 Debug enable
    uint16_t rsvd2:4;                   // 14:11 Reserved
    uint16_t ZONEX_DBGEN:1;             // 15 ZoneX Debug enable
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union DEBUGSS_DEBUG_ENABLE_STATUS_REG {
    uint32_t  all;
    struct  DEBUGSS_DEBUG_ENABLE_STATUS_BITS  bit;
};

struct DEBUGSS_DBG2CPU1_INT_FLG_BITS {  // bits description
    uint16_t INT:1;                     // 0 Debugger to CPU Interrupt flag
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DEBUGSS_DBG2CPU1_INT_FLG_REG {
    uint32_t  all;
    struct  DEBUGSS_DBG2CPU1_INT_FLG_BITS  bit;
};

struct DEBUGSS_DBG2CPU1_INT_FLG_SET_BITS {// bits description
    uint16_t INT:1;                     // 0 Debugger to CPU Interrupt set
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DEBUGSS_DBG2CPU1_INT_FLG_SET_REG {
    uint32_t  all;
    struct  DEBUGSS_DBG2CPU1_INT_FLG_SET_BITS  bit;
};

struct DEBUGSS_DBG2CPU1_INT_FLG_CLR_BITS {// bits description
    uint16_t INT:1;                     // 0 Debugger to CPU Interrupt flag clear
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union DEBUGSS_DBG2CPU1_INT_FLG_CLR_REG {
    uint32_t  all;
    struct  DEBUGSS_DBG2CPU1_INT_FLG_CLR_BITS  bit;
};

struct DEBUGSS_C29_DBG_RX_ADDR_BITS {   // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint32_t ADDRESS:31;                // 31:1 Rx Bus Address register
};

union DEBUGSS_C29_DBG_RX_ADDR_REG {
    uint32_t  all;
    struct  DEBUGSS_C29_DBG_RX_ADDR_BITS  bit;
};

struct SECAP_HANDLER_REGS {
    union   DEBUGSS_PASSWORD_ID_REG          PASSWORD_ID;                  // Password ID
    uint32_t                                 PASSWORD1;                    // Password1 Register
    uint32_t                                 PASSWORD2;                    // Password2 Register
    uint32_t                                 PASSWORD3;                    // Password3 Register
    uint32_t                                 PASSWORD4;                    // Password4 Register
    union   DEBUGSS_DEBUG_ENABLE_STATUS_REG  DEBUG_ENABLE_STATUS;          // Debug status register
    uint8_t                                  rsvd1[104];                   // Reserved
    uint32_t                                 TEST_PASSWORD1;               // Test Password1 Register
    uint32_t                                 TEST_PASSWORD2;               // Test Password2 Register
    uint32_t                                 TEST_PASSWORD3;               // Test Password3 Register
    uint32_t                                 TEST_PASSWORD4;               // Test Password4 Register
    uint8_t                                  rsvd2[112];                   // Reserved
    uint32_t                                 DBG2CPU1_CHR;                 // Debugger to CPU1/SSU challenge response
    uint32_t                                 CPU12DBG_CHR;                 // CPU1/SSU to Debugger challenge response
    uint32_t                                 DBG2CPU1_HS;                  // Debugger to CPU1/SSU Handshake
    uint32_t                                 CPU12DBG_HS;                  // CPU1/SSU to Debugger Handshake
    union   DEBUGSS_DBG2CPU1_INT_FLG_REG     DBG2CPU1_INT_FLG;             // Debugger to CPU1 interrupt flag
    union   DEBUGSS_DBG2CPU1_INT_FLG_SET_REG DBG2CPU1_INT_FLG_SET;         // Debugger to CPU1 interrupt set
    union   DEBUGSS_DBG2CPU1_INT_FLG_CLR_REG DBG2CPU1_INT_FLG_CLR;         // Debugger to CPU1 interrupt clear
    uint8_t                                  rsvd3[232];                   // Reserved
    uint32_t                                 SSU_DBG_STATUS;               // Read only SSU DBG Status
    uint32_t                                 HSM_DBG_STATUS;               // Read only HSM DBG Status
    uint32_t                                 CTL_DBG_STATUS;               // Read only CTL DBG Status
    uint32_t                                 GEN_DBG_STATUS0;              // Read only GEN DBG Status0
    uint32_t                                 GEN_DBG_STATUS1;              // Read only GEN DBG Status1
    uint32_t                                 GEN_DBG_STATUS2;              // Read only GEN DBG Status2
    uint32_t                                 GEN_DBG_STATUS3;              // Read only GEN DBG Status3
    uint32_t                                 GEN_DBG_STICKY_STATUS0;       // Read only GEN DBG_STICKY Status0
    uint32_t                                 GEN_DBG_STICKY_STATUS1;       // Read only GEN DBG_STICKY Status1
    uint32_t                                 GEN_DBG_STICKY_STATUS2;       // Read only GEN DBG_STICKY Status2
    uint32_t                                 GEN_DBG_STICKY_STATUS3;       // Read only GEN DBG_STICKY Status3
    uint32_t                                 GEN_DBG_STICKY_CLR0;          // Write only GEN_DBG_STICKY clear register0
    uint32_t                                 GEN_DBG_STICKY_CLR1;          // Write only GEN_DBG_STICKY clear register1
    uint32_t                                 GEN_DBG_STICKY_CLR2;          // Write only GEN_DBG_STICKY clear register2
    uint32_t                                 GEN_DBG_STICKY_CLR3;          // Write only GEN_DBG_STICKY clear register3
    union   DEBUGSS_C29_DBG_RX_ADDR_REG      C29_DBG_RX_ADDR;              // RX Data Write Address
    uint32_t                                 JTAG_GEN;                     // jtag general purpose register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
