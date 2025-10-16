//###########################################################################
//
// FILE:    sbl_flash_programming.h
//
// TITLE:   SBL unsecure FOTA functions
//! <h1> SBL unsecure FOTA functions </h1>
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

#ifndef SBL_FLASH_PROGRAMMING_H
#define SBL_FLASH_PROGRAMMING_H

//
// Included Files
//
#include <device.h>
#include "cert.h"
#include "cpubrom.h"
#include "bootload_cpu1.h"
#include "sbl_packet_interface.h"
#include "sbl_device_utils.h"

//
// Include Flash API include file
//
#include "FlashTech_F29H85x_C29x.h"

//
// Include Flash API example header file
//
#include "flash_programming_F29H85x_C29.h"

//
// Globals
//
extern bootLoadStatus_t g_bootLoadStatus;

//
// Defines
//
/* For 1024bit interleaved (2x512bit) programming */
#define FLASH_BUFFER_SIZE 128U

//
// Functions
//
void CopyApplication(uint32_t LoadAddr, uint32_t ImageSize, uint8_t bankMode);
void ConstructInterleavedData1024Bits(uint8_t* arrPtr_1024Bits);
void ProgramInactiveBankManagement(uint8_t targetCPU, uint8_t bankMode, uint32_t flashConfig);
void ProgramBankModeToDataFlash(uint8_t bankMode, uint32_t u32UserFlashConfig);
void EraseInactiveBankManagement(uint8_t targetCPU, uint8_t bankMode, uint32_t flashConfig);
void EraseBanks(uint32_t u32StartAddress, uint32_t FlashConfig);
void ClearFSMStatus(uint32_t u32StartAddress, uint32_t u32UserFlashConfig);
void ConstructInterleavedData1024Bits(uint8_t* sequential1024BitsArrPtr);

void programFOTA(uint8_t targetCPU, uint8_t bankMode);

uint32_t insertUartData(uint32_t addr, uint32_t size);
uint32_t bootloadProcessWithChecks(bootLoadCtx_t *blCtx);

//
// Returns bank mode programmed in data flash after successful firmware update
// Note: ProgramBankModeToDataFlash must be called prior
//
static inline uint32_t getPreviousBankMode() 
{
    uint32_t prevBankModeAddr = C29FlashBankFR4RP0StartAddress;
    return (HWREG(prevBankModeAddr));
}

#endif /* SBL_FLASH_PROGRAMMING_H */