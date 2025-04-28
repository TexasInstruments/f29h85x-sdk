//###########################################################################
//
// FILE:   ex4_uart_sbl.h
//
// TITLE:  F29H85x UART flash kernel functions
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

#ifndef UART_SBL_H
#define UART_SBL_H

//
// Included Files
//
// #include "Types.h"
#include "device.h"
#include "flash.h"

//#include "ex4_cpubrom_uartBoot.h"

//
// Include Flash API include file
//
#include "FlashTech_F29H85x_C29x.h"

//
// Include Flash API example header file
//
#include "flash_programming_F29H85x_C29.h"
#include "f29h85x_kernel_commands_cpu1.h"
#include "ex4_cpubrom.h"
#include "ex4_cpubrom_uartBoot.h"
#include "ex4_cpubrom_utils.h"
#include "inc/hw_ssu.h"

//
//  UART
//
#define UART_BOOT                                   (0x01U)
#define UART_BOOT_ALT1                              (0x21U)
#define UART_BOOT_ALT2                              (0x41U)
#define UART_BOOT_ALT3                              (0x61U)
#define UART_BOOT_ALT4                              (0x81U)

#define HS_FS                                       (0x0AU)
#define HS_SE                                       (0x00U)

#define APP_ENTRY_POINT 0x10020000U

//
// Globals
//
extern FlashStatusCode statusCode;
extern uint32_t ENTRY_ADDR;
extern uint32_t LOAD_ADDR;
extern uint32_t IMAGE_SIZE;
extern uint16_t CHECKSUM;

//
// Function declarations
//
extern uint32_t uartGetFunction(uint32_t  BootMode, uint8_t BankNum);
uint32_t CPU_jumpToAddr(uint32_t jumpAddr);

uint32_t UART_AutoBaud(void);
extern void uartDFU(uint8_t targetCPU, Fapi_BankMode bankMode, uint32_t bootMode, uint32_t LoadAddr, uint32_t ImageSize, uint8_t currentState);
uint32_t uartBootInit(uint32_t bootMode);
uint16_t uartGetPacket(uint16_t* length, uint16_t* data);
uint16_t uartaGetACK();
void uartSendChecksum();
void uartSendWord(uint16_t word);
void uartSendByte(uint8_t byte);
uint16_t uartGetOnlyWordData(void);
void uartaFlush(void);
uint16_t uartSendPacket(uint16_t command, uint16_t status, uint16_t length,
                       uint16_t* data1, uint16_t flashAPIError, uint16_t* data2);
uint16_t uartSendDataPacket(uint16_t command, uint8_t* data, uint16_t length);
void CPU_BROM_waitBoot(void);
void sendACK(void);
void sendNAK(void);
static void uartConfigureGPIO(uint32_t bootMode);
static void uartInitGPIO(void);
void transmitByte(uint8_t byte);
uint8_t getHexAscii(uint8_t data);
uint8_t copyKPImageToRAM(uint32_t bootMode, uint32_t BaseAddress);
uint8_t copyKeysToRAM(uint32_t bootMode, uint32_t BaseAddress);
uint8_t copyApplicationToHSM(uint32_t bootMode, uint32_t BaseAddress);
uint8_t copyCPImageToRAM(uint32_t bootMode, uint32_t BaseAddress);
uint8_t copyC29ImageToFlash(uint32_t bootMode, uint32_t BaseAddress);
void initializeFlash();
void BootExistingFirmware(uint8_t currentState);
uint8_t getDeviceState();
uint16_t uartSendFlashStatusPacket(uint16_t command, FlashStatusCode* statusCode);
void sampleApplication();
uint8_t provisionApplicationImgToHSM(uint32_t BaseAddress, uint8_t bankMode);
uint8_t provisionSecCfgImg(uint32_t BaseAddress);
void CopyApplicationToRAM(uint32_t ImageSize, uint32_t BaseAddress);
uint8_t getBankMode();
uint32_t getPreviousBankMode();
void cpu1FOTA(void);
void cpu3FOTA(void);
void seccfgProgram(void);
void cpu1SecureFOTA(void);
void cpu3SecureFOTA(void);
void hsmSecureFOTA(void);


#endif
