//###########################################################################
//
// FILE:    hwbf_aes.h
//
// TITLE:   Definitions for the AES registers.
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

#ifndef HWBF_AES_H
#define HWBF_AES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// AES Individual Register Bit Definitions:

struct AES_AES_CTRL_BITS {              // bits description
    uint16_t OUTPUT_READY:1;            // 0 Output Ready Status
    uint16_t INPUT_READY:1;             // 1 Input Ready Status
    uint16_t DIRECTION:1;               // 2 Encryption/Decryption Selection
    uint16_t KEY_SIZE:2;                // 4:3 Key Size
    uint16_t MODE:1;                    // 5 ECB/CBC Mode
    uint16_t CTR:1;                     // 6 Counter Mode
    uint16_t CTR_WIDTH:2;               // 8:7 AES-CTR Mode Counter Width
    uint16_t ICM:1;                     // 9 AES Integer Counter Mode (ICM) Enable
    uint16_t CFB:1;                     // 10 Full block AES cipher feedback mode (CFB128) Enable
    uint16_t XTS:2;                     // 12:11 AES-XTS Operation Enable
    uint16_t F8:1;                      // 13 AES f8 Mode Enable
    uint16_t F9:1;                      // 14 AES f9 Mode Enable
    uint16_t CBCMAC:1;                  // 15 AES-CBC MAC Enable
    uint16_t GCM:2;                     // 17:16 AES-GCM Mode Enable
    uint16_t CCM:1;                     // 18 AES-CCM Mode Enable
    uint16_t CCM_L:3;                   // 21:19 Width of the length field for CCM operations
    uint16_t CCM_M:3;                   // 24:22 Length of the authentication field for CCM operations
    uint16_t rsvd1:4;                   // 28:25 Reserved
    uint16_t SAVE_CONTEXT:1;            // 29 TAG or Result IV Save
    uint16_t SVCTXTRDY:1;               // 30 AES TAG/IV Block(s) Ready
    uint16_t CTXTRDY:1;                 // 31 Context Data Registers Ready
};

union AES_AES_CTRL_REG {
    uint32_t  all;
    struct  AES_AES_CTRL_BITS  bit;
};

struct AES_AES_SYSCONFIG_BITS {         // bits description
    uint16_t AUTOIDLE:1;                // 0 autoidle
    uint16_t SOFTRESET:1;               // 1 Soft Reset
    uint16_t SIDLE:2;                   // 3:2 Slave Idle Mode
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t DMA_REQ_DATA_IN_EN:1;      // 5 DMA Request Data In Enable
    uint16_t DMA_REQ_DATA_OUT_EN:1;     // 6 DMA Request Data Out Enable
    uint16_t DMA_REQ_CONTEXT_IN_EN:1;   // 7 DMA Request Context In Enable
    uint16_t DMA_REQ_CONTEXT_OUT_EN:1;  // 8 DMA Request Context Out Enable
    uint16_t MAP_CONTEXT_OUT_ON_DATA_OUT:1; // 9 Map Context Out on Data Out Enable
    uint16_t rsvd2:1;                   // 10 Reserved
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t rsvd4:1;                   // 12 Reserved
    uint16_t rsvd5:3;                   // 15:13 Reserved
    uint16_t rsvd6:16;                  // 31:16 Reserved
};

union AES_AES_SYSCONFIG_REG {
    uint32_t  all;
    struct  AES_AES_SYSCONFIG_BITS  bit;
};

struct AES_AES_SYSSTATUS_BITS {         // bits description
    uint16_t RESETDONE:1;               // 0 Reset Done
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union AES_AES_SYSSTATUS_REG {
    uint32_t  all;
    struct  AES_AES_SYSSTATUS_BITS  bit;
};

struct AES_AES_IRQSTATUS_BITS {         // bits description
    uint16_t CONTEXT_IN:1;              // 0 Context In Interrupt Status
    uint16_t DATA_IN:1;                 // 1 Data In Interrupt Status
    uint16_t DATA_OUT:1;                // 2 Data Out Interrupt Status
    uint16_t CONTEXT_OUT:1;             // 3 Context Output Interrupt Status
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union AES_AES_IRQSTATUS_REG {
    uint32_t  all;
    struct  AES_AES_IRQSTATUS_BITS  bit;
};

struct AES_AES_IRQENABLE_BITS {         // bits description
    uint16_t CONTEXT_IN:1;              // 0 Context In Interrupt Enable
    uint16_t DATA_IN:1;                 // 1 Data In Interrupt Enable
    uint16_t DATA_OUT:1;                // 2 Data Out Interrupt Enable
    uint16_t CONTEXT_OUT:1;             // 3 Context Out Interrupt Enable
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union AES_AES_IRQENABLE_REG {
    uint32_t  all;
    struct  AES_AES_IRQENABLE_BITS  bit;
};

struct AES_AES_DIRTY_BITS_BITS {        // bits description
    uint16_t S_ACCESS:1;                // 0 AES Access Bit
    uint16_t S_DIRTY:1;                 // 1 AES Dirty Bit
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t rsvd2:1;                   // 3 Reserved
    uint16_t rsvd3:12;                  // 15:4 Reserved
    uint16_t rsvd4:16;                  // 31:16 Reserved
};

union AES_AES_DIRTY_BITS_REG {
    uint32_t  all;
    struct  AES_AES_DIRTY_BITS_BITS  bit;
};

struct AES_REGS {
    uint32_t                                 AES_KEY2_6;                   // XTS Second Key or CBC-MAC Third Key
    uint32_t                                 AES_KEY2_7;                   // XTS Second Key or CBC-MAC Third Key
    uint32_t                                 AES_KEY2_4;                   // XTS/CCM Second Key or CBC-MAC Third Key
    uint32_t                                 AES_KEY2_5;                   // XTS Second Key or CBC-MAC Third Key
    uint32_t                                 AES_KEY2_2;                   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
    uint32_t                                 AES_KEY2_3;                   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
    uint32_t                                 AES_KEY2_0;                   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
    uint32_t                                 AES_KEY2_1;                   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
    uint32_t                                 AES_KEY1_6;                   // Key
    uint32_t                                 AES_KEY1_7;                   // Key
    uint32_t                                 AES_KEY1_4;                   // Key
    uint32_t                                 AES_KEY1_5;                   // Key
    uint32_t                                 AES_KEY1_2;                   // Key
    uint32_t                                 AES_KEY1_3;                   // Key
    uint32_t                                 AES_KEY1_0;                   // Key
    uint32_t                                 AES_KEY1_1;                   // Key
    uint32_t                                 AES_IV_IN_OUT_0;              // Initialization Vector 0
    uint32_t                                 AES_IV_IN_OUT_1;              // Initialization Vector 1
    uint32_t                                 AES_IV_IN_OUT_2;              // Initialization Vector 2
    uint32_t                                 AES_IV_IN_OUT_3;              // Initialization Vector 3
    union   AES_AES_CTRL_REG                 AES_CTRL;                     // Input/Output Buffer Control and Mode Selection
    uint32_t                                 AES_C_LENGTH_0;               // Crypto Data Length 0
    uint32_t                                 AES_C_LENGTH_1;               // Crypto Data Length 1
    uint32_t                                 AES_AUTH_LENGTH;              // AAD Data Length
    uint32_t                                 AES_DATA_IN_OUT_0;            // Data Word 0
    uint32_t                                 AES_DATA_IN_OUT_1;            // Data Word 1
    uint32_t                                 AES_DATA_IN_OUT_2;            // Data Word 2
    uint32_t                                 AES_DATA_IN_OUT_3;            // Data Word 3
    uint32_t                                 AES_TAG_OUT_0;                // Hash Result 0
    uint32_t                                 AES_TAG_OUT_1;                // Hash Result 1
    uint32_t                                 AES_TAG_OUT_2;                // Hash Result 2
    uint32_t                                 AES_TAG_OUT_3;                // Hash Result 3
    uint32_t                                 AES_REV;                      // Module Revision Number
    union   AES_AES_SYSCONFIG_REG            AES_SYSCONFIG;                // System Configuration
    union   AES_AES_SYSSTATUS_REG            AES_SYSSTATUS;                // Reset Status
    union   AES_AES_IRQSTATUS_REG            AES_IRQSTATUS;                // Interrupt Status
    union   AES_AES_IRQENABLE_REG            AES_IRQENABLE;                // Interrupt Enable
    union   AES_AES_DIRTY_BITS_REG           AES_DIRTY_BITS;               // Accessed / Dirty Bits
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
