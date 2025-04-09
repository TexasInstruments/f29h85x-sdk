//###########################################################################
//
// FILE:   FlashTech.h
//
// TITLE:  F65 Flash API v21.00
//
//###########################################################################
// //
//  Copyright: Copyright (C) Texas Instruments Incorporated
//  All rights reserved not granted herein.
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
#ifndef F65_H_
#define F65_H_

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "Registers.h"
#include "hw_flash_command.h"
#include "Constants/F29H85x.h"
#include "Types.h"
#include "stdint.h"

#if !defined(F65)
   #define F65
#endif

/* Flash C API functions*/

/* Flash State Machine commands */
extern Fapi_FlashStatusType Fapi_getFsmStatus(uint32_t u32StartAddress, uint32_t u32UserFlashConfig);

extern Fapi_StatusType Fapi_checkFsmForReady(uint32_t u32StartAddress, uint32_t u32UserFlashConfig);

extern Fapi_StatusType Fapi_setActiveFlashBank(Fapi_FlashBankType oNewFlashBank);


extern void Fapi_flushPipeline(uint32_t u32UserFlashConfig);


extern Fapi_StatusType Fapi_setupBankSectorEnable(uint32_t *pu32StartAddress, uint32_t u32UserFlashConfig, uint32_t reg_address, uint32_t value);

extern Fapi_StatusType Fapi_issueProgBankMode(Fapi_BankMgmtAddress u32StartAddress, Fapi_BankMode u32BankMode, Fapi_FlashStatusWordType *poFlashStatusWord, uint32_t u32UserFlashConfig);

/* Device Family Dependent FSM commands */
extern uint32_t * Fapi_remapEccAddress(uint32_t u32EccAddress);

extern boolean Fapi_isAddressEcc(uint32_t u32Address);

/* Async Commands */
extern Fapi_StatusType Fapi_issueAsyncCommandWithAddress(
                                                        Fapi_FlashStateCommandsType oCommand,
                                                        uint32_t *pu32StartAddress,
                                                        uint8_t                       u8Iterator,
                                                        uint32_t  u32UserFlashConfig
                                                        );

extern Fapi_StatusType Fapi_issueAsyncCommand(uint32_t u32StartAddress, uint32_t  u32UserFlashConfig, Fapi_FlashStateCommandsType oCommand);

extern Fapi_StatusType Fapi_issueBankEraseCommand(uint32_t *pu32StartAddress,
                                                  uint8_t u8Iterator,
                                                  uint32_t  u32UserFlashConfig
                                                  );

/* Info Commands */
extern Fapi_LibraryInfoType Fapi_getLibraryInfo(void);

/* Init */
extern Fapi_StatusType Fapi_initializeAPI(
                                         Fapi_FmcRegistersType *poFlashControlRegister,
                                         uint32_t u32HclkFrequency
                                         );

/* Read commands */
extern Fapi_StatusType Fapi_doBlankCheck(
                                        uint32_t *pu32StartAddress,
                                        uint32_t u32Length,
                                        Fapi_FlashStatusWordType *poFlashStatusWord,
                                        uint8_t u8Iterator,
                                        uint32_t  u32UserFlashConfig
                                        );

extern Fapi_StatusType Fapi_doVerify(
                                    uint32_t *pu32StartAddress,
                                    uint32_t u32Length,
                                    uint32_t *pu32CheckValueBuffer,
                                    Fapi_FlashStatusWordType *poFlashStatusWord,
                                    uint8_t u8Iterator,
                                    uint32_t  u32UserFlashConfig
                                    );


extern Fapi_StatusType Fapi_doVerifyByByte(
                             uint8_t *pu8StartAddress,
                             uint32_t u32Length,
                             uint8_t *pu8CheckValueBuffer,
                             Fapi_FlashStatusWordType *poFlashStatusWord,
                             uint8_t u8Iterator,
                             uint32_t  u32UserFlashConfig
                             );

/* Programming Commands */
extern Fapi_StatusType Fapi_issueProgrammingCommand(
                            uint32_t *pu32StartAddress,
                            uint8_t  *pu8DataBuffer,
                            uint8_t  u8DataBufferSizeInBytes,
                            uint8_t  *pu8EccBuffer,
                            uint8_t  u8EccBufferSizeInBytes,
                            Fapi_FlashProgrammingCommandsType oMode,
                            uint32_t  u32UserFlashConfig
                            );

extern Fapi_StatusType Fapi_issueDataOnly512ProgrammingCommand(
                                uint32_t *pu32StartAddress,
                                uint8_t *pu8DataBuffer,
                                uint8_t  u8DataBufferSizeInBytes,
                                uint32_t u32UserFlashConfig,
                                uint8_t  u8Iterator
                            );
											
extern Fapi_StatusType Fapi_issueAutoEcc512ProgrammingCommand(
                                            uint32_t *pu32StartAddress,
                                            uint8_t  *pu8DataBuffer,
                                            uint8_t  u8DataBufferSizeInWords,
                                            uint32_t  u32UserFlashConfig,
                                            uint8_t  u8Iterator
                                            );											

extern Fapi_StatusType Fapi_issueDataAndEcc512ProgrammingCommand(
                                            uint32_t *pu32StartAddress,
                                            uint8_t  *pu8DataBuffer,
                                            uint8_t  u8DataBufferSizeInWords,
                                            uint8_t  *pu8EccBuffer,
                                            uint8_t  u8EccBufferSizeInBytes,
                                            uint32_t u32UserFlashConfig,
                                            uint8_t  u8Iterator
                                            );

extern Fapi_StatusType Fapi_issueEccOnly64ProgrammingCommand(
                                            uint32_t *pu32StartAddress,
                                            uint8_t *pu8EccBuffer,
                                            uint8_t  u8EccBufferSizeInBytes,
                                            uint32_t u32UserFlashConfig,
                                            uint8_t  u8Iterator
                                            );

extern Fapi_StatusType Fapi_issueProgrammingCommandForEccAddresses(
                                            uint32_t *pu32StartAddress,
                                            uint8_t *pu8EccBuffer,
                                            uint8_t u8EccBufferSizeInBytes
                                            );


/* Utility Commands */
extern uint8_t Fapi_calculateEcc(
                               uint32_t *pu32Address,
                               uint64_t *pu64Data,
                               uint8_t  u8Iterator
                               );

extern Fapi_StatusType Write_32bp(uint32_t reg_offset, uint32_t mask, uint32_t shift, uint32_t value);

extern Fapi_StatusType Write_32(uint32_t ctrlBase, uint32_t reg_offset, uint32_t mask, uint32_t shift, uint32_t value);

extern Fapi_StatusType Fapi_regReadback(uint32_t u32FLCid , uint32_t reg_offset, uint32_t readback_value);

extern uint32_t Fapi_getUserConfiguration(
                                        Fapi_FlashBankType    BankType,
                                        Fapi_FOTAStatus  FOTAStatus
                                        );

extern Fapi_StatusType Fapi_SetFlashCPUConfiguration(Fapi_BankMode u32BankModeValue);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /*F65_H_*/
