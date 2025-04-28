//###########################################################################
//
// FILE:    ex3_uart_boot_cpu1.h
//
// TITLE:   UART Boot mode functions
//! <h1> UART Boot mode functions </h1>
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


//
// Included Files
//
#include "device.h"

#include <cert.h>
#include <ex3_cpubrom.h>
#include <ex3_cpubrom_bootload.h>
#include <ex3_cpubrom_uartBoot.h>
#include <ex3_cpubrom_utils.h>
#include <ex3_uart_flash_kernel_cpu1.h>

//
// Globals
//
extern bootLoadStatus_t g_bootLoadStatus;

//
// Defines
//
#define FLASH_BUFFER_SIZE 0x80U
#ifdef BANKMODE0
#define FLASH_IMAGE_SIZE (0x200000U - MAX_CERT_SIZE)
#else
#define FLASH_IMAGE_SIZE (0x100000U - MAX_CERT_SIZE)
#endif

//
// Functions
//
void CopyApplication(uint32_t LoadAddr, uint32_t ImageSize);
void ConstructInterleavedData1024Bits(uint8_t* arrPtr_1024Bits);
extern void sendACK(void);
extern void sendNAK(void);
void ProgramBankModeToDataFlash(uint8_t bankMode, uint32_t u32UserFlashConfig);
