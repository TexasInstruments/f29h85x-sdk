//###########################################################################
//
//  FILE:    sbl_code_provisioning.c
//
//  TITLE:   Bootloader HS-SE code provisioning functions
//  <h1> Bootloader HS-SE code provisioning </h1>
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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

#ifndef SBL_CODE_PROVISIONING_H
#define SBL_CODE_PROVISIONING_H

//
// Included Files
//
#include <device.h>
#include "cert.h"
#include "cpubrom.h"
#include "sbl_flash_programming.h"

//
// Defines
//
#define SEC_CFG_IMG_SIZE        (0x3000U)
#define SEC_CFG_MAX_CHUNK_SIZE  (0x800U)  // Size of each CPU certificate and Sec Cfg content

#define CP_CHUNK_SIZE           0x4000U

#if (CP_CHUNK_SIZE % 16U)
#error "CP Chuncks size must be 16 bytes aligned (128bit is the most atomic CP flash programming call supported)"
#endif
#if CP_CHUNK_SIZE > 0x4000U
#error "CP Chunck size (data to be validated by HSM at once) cannot exceed 0x4000 bytes, since only LDA1/0 RAM is available to the application space (non-HSMRT) and only LDA1 in this software is reserved as a scratchpad for authentication."
#endif

//
// Functions
//
int32_t AuthenticateImageviaHSMRT(uint32_t ImageSize, uint32_t BaseAddress);
int32_t provisionApplicationImg(uint32_t BaseAddress);
int32_t provisionSecCfgImg(uint32_t BaseAddress);

#endif //SBL_CODE_PROVISIONING_H