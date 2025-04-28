//###########################################################################
//
// FILE:    ex4_uart_boot_cpu1.h
//
// TITLE:   UART Boot mode functions
//! <h1> UART Boot mode functions </h1>
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef UART_BOOT_CPU1_H
#define UART_BOOT_CPU1_H

//
// Included Files
//
#include "device.h"

#include <cert.h>
#include <ex4_cpubrom_bootload.h>
#include <ex4_uart_sbl.h>

//
// Globals
//
extern bootLoadStatus_t g_bootLoadStatus;

//
// Defines
//
#define FLASH_BUFFER_SIZE 0x10U

#ifdef BANKMODE1
#define FLASH_IMAGE_SIZE (0x200000U - MAX_CERT_SIZE)
#else
#define FLASH_IMAGE_SIZE (0x100000U - MAX_CERT_SIZE)
#endif

// //
// // Globals
// //
// FlashStatusCode statusCode;
// uint32_t ENTRY_ADDR;
// uint32_t LOAD_ADDR;
// uint32_t IMAGE_SIZE;
// uint16_t CHECKSUM;

//
// Functions
//
void CopyApplication(uint8_t targetCPU, uint32_t LoadAddr, uint32_t ImageSize);
void ConstructInterleavedData1024Bits(uint8_t* arrPtr_1024Bits);
void ProgramInactiveBankManagement(uint8_t targetCPU, uint8_t bankMode, uint32_t flashConfig);
extern void sendACK(void);
extern void sendNAK(void);
void ProgramBankModeToDataFlash(uint8_t bankMode, uint32_t u32UserFlashConfig);
void eraseInactiveBankManagement(uint8_t targetCPU, uint8_t bankMode, uint32_t flashConfig);
#endif