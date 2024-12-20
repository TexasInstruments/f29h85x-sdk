//###########################################################################
//
// FILE:    hwbf_lpost.h
//
// TITLE:   Definitions for the LPOST registers.
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

#ifndef HWBF_LPOST_H
#define HWBF_LPOST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// LPOST Individual Register Bit Definitions:

struct LPOST_REVISION_BITS {            // bits description
    uint16_t MINOR:6;                   // 5:0 Minor Revision Number
    uint16_t CUSTOM:2;                  // 7:6 Custom Module Number
    uint16_t MAJOR:3;                   // 10:8 Major Revision Number
    uint16_t rsvd1:5;                   // 15:11 Reserved
    uint16_t FUNC:12;                   // 27:16 Functional Release Number
    uint16_t rsvd2:2;                   // 29:28 Reserved
    uint16_t SCHEME:2;                  // 31:30 Defines Scheme for Module
};

union LPOST_REVISION_REG {
    uint32_t  all;
    struct  LPOST_REVISION_BITS  bit;
};

struct LPOST_LPOST_CONTROL_BITS {       // bits description
    uint16_t GO:4;                      // 3:0 Start the self-test operation
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LPOST_LPOST_CONTROL_REG {
    uint32_t  all;
    struct  LPOST_LPOST_CONTROL_BITS  bit;
};

struct LPOST_LPOST_CONFIG_BITS {        // bits description
    uint16_t COVERAGE:4;                // 3:0 Coverage configuration for the power on self-test
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union LPOST_LPOST_CONFIG_REG {
    uint32_t  all;
    struct  LPOST_LPOST_CONFIG_BITS  bit;
};

struct LPOST_LPOST_STATUS_BITS {        // bits description
    uint16_t DONE:1;                    // 0 LPOST completion status.
    uint16_t PASS:1;                    // 1 LPOST test pass/fail status
    uint16_t TIMEOUT:1;                 // 2 LPOST test timeout status
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t SANITY_TEST_PASS:1;        // 16 LPOST sanity test status
    uint16_t SANITY_TIMEOUT_PASS:1;     // 17 LPOST timeout test status
    uint16_t rsvd2:13;                  // 30:18 Reserved
    uint16_t RAW_PORESETn_STATUS:1;     // 31 The bit will indicate RAW PORESETn Status
};

union LPOST_LPOST_STATUS_REG {
    uint32_t  all;
    struct  LPOST_LPOST_STATUS_BITS  bit;
};

struct LPOST_LPOST_STATUS_CLEAR_BITS {  // bits description
    uint16_t DONE:1;                    // 0 DONE status clear
    uint16_t PASS:1;                    // 1 PASS status clear
    uint16_t TIMEOUT:1;                 // 2 TIMEOUT status clear
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t SANITY_TEST_PASS:1;        // 16 SANITY_TEST_PASS status clear
    uint16_t SANITY_TIMEOUT_PASS:1;     // 17 SANITY_TIMEOUT_PASS status clear
    uint16_t rsvd2:13;                  // 30:18 Reserved
    uint16_t RAW_PORESETn_STATUS:1;     // 31 Clear bit for RAW_PORESETn_STATUS
};

union LPOST_LPOST_STATUS_CLEAR_REG {
    uint32_t  all;
    struct  LPOST_LPOST_STATUS_CLEAR_BITS  bit;
};

struct LPOST_LPOST_LOCK_BITS {          // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t LPOST_CONTROL:1;           // 2 Register lock configuration
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t LPOST_CONFIG:1;            // 4 Register lock configuration
    uint16_t rsvd3:11;                  // 15:5 Reserved
    uint16_t rsvd4:2;                   // 17:16 Reserved
    uint16_t LPOST_STATUS_CLEAR:1;      // 18 Register lock configuration
    uint16_t rsvd5:7;                   // 25:19 Reserved
    uint16_t PARITY_TEST:1;             // 26 Register lock configuration
    uint16_t rsvd6:5;                   // 31:27 Reserved
};

union LPOST_LPOST_LOCK_REG {
    uint32_t  all;
    struct  LPOST_LPOST_LOCK_BITS  bit;
};

struct LPOST_LPOST_COMMIT_BITS {        // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t LPOST_CONTROL:1;           // 2 Register commit configuration
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t LPOST_CONFIG:1;            // 4 Register commit configuration
    uint16_t rsvd3:11;                  // 15:5 Reserved
    uint16_t rsvd4:2;                   // 17:16 Reserved
    uint16_t LPOST_STATUS_CLEAR:1;      // 18 Register lock configuration
    uint16_t rsvd5:7;                   // 25:19 Reserved
    uint16_t PARITY_TEST:1;             // 26 Register commit configuration
    uint16_t rsvd6:5;                   // 31:27 Reserved
};

union LPOST_LPOST_COMMIT_REG {
    uint32_t  all;
    struct  LPOST_LPOST_COMMIT_BITS  bit;
};

struct LPOST_REGS {
    union   LPOST_REVISION_REG               REVISION;                     // IP Revision tie-off value
    uint8_t                                  rsvd1[4];                     // Reserved
    union   LPOST_LPOST_CONTROL_REG          LPOST_CONTROL;                // Register to start the power-on self-test operation.
    uint8_t                                  rsvd2[4];                     // Reserved
    union   LPOST_LPOST_CONFIG_REG           LPOST_CONFIG;                 // Register to configure the coverage for the power-on self-test operation.
    uint8_t                                  rsvd3[44];                    // Reserved
    union   LPOST_LPOST_STATUS_REG           LPOST_STATUS;                 // Register indicating the status of power-on self-test operation.
    uint8_t                                  rsvd4[4];                     // Reserved
    union   LPOST_LPOST_STATUS_CLEAR_REG     LPOST_STATUS_CLEAR;           // Register to clear the LPOST Status
    uint8_t                                  rsvd5[36];                    // Reserved
    union   LPOST_LPOST_LOCK_REG             LPOST_LOCK;                   // Register to lock the LPOST register configurations
    uint8_t                                  rsvd6[4];                     // Reserved
    union   LPOST_LPOST_COMMIT_REG           LPOST_COMMIT;                 // Register to commit the LPOST register configuration
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
