// ###########################################################################
//
//  FILE:    ex3_code_provisioning.c
//
//  TITLE:   UART HS-SE code provisioning functions
//! <h1> UART HS-SE code provisioning </h1>
//
// ###########################################################################
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

// ###########################################################################
#ifndef CODE_PROVISIONING_CPU1_H
#define CODE_PROVISIONING_CPU1_H

//
// Included Files
//
#include "device.h"

#include <cert.h>
#include <ex4_cpubrom.h>
#include <ex4_cpubrom_bootload.h>
#include <ex4_cpubrom_uartBoot.h>
#include <ex4_cpubrom_utils.h>
#include <ex4_uart_boot_cpu1.h>
#include <ex4_uart_boot_manager.h>

//
// Defines
//
#define BUFFER_SIZE             0x10
#define CHUNK_SIZE              (512U)
#define MAX_CP_RAM_IMAGE_SIZE   (1024U * 96U)
#define SEC_CFG_IMG_SIZE        (6144U)

//
// Functions
//
void AuthenticateImageviaHSMRT(uint32_t ImageSize, uint32_t BaseAddress);
void CopyApplicationWithAuthentication(uint32_t ImageSize, uint32_t BaseAddress);

#endif