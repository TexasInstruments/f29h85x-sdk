//###########################################################################
//
// FILE:    ex3_uart_flash_kernel_cpu1.h
//
// TITLE:   CPU kernel get function header
// <h1> CPU kernel get function </h1>
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

#ifndef UART_GET_FUNCTION_CPU1_H
#define UART_GET_FUNCTION_CPU1_H


//
// Included Files
//
#include "device.h"
#include "stdint.h"


#include "ex3_cpubrom.h"
#include "ex3_cpubrom_uartBoot.h"
#include "ex3_cpubrom_utils.h"
#include "ex3_uart_flash_kernel_cpu1.h"
#include "f29h85x_kernel_commands_cpu1.h"
#include "inc/hw_ssu.h"
#include "inc/hw_memmap.h"

//
// Globals
//
uint32_t EntryAddr;
uint32_t LoadAddr;
uint32_t ImageSize;

FlashStatusCode statusCode;

uint16_t checksum;

//
//  UART
//
#define UART_BOOT                                   (0x01U)
#define UART_BOOT_ALT1                              (0x21U)
#define UART_BOOT_ALT2                              (0x41U)
#define UART_BOOT_ALT3                              (0x61U)
#define UART_BOOT_ALT4                              (0x81U)


uint32_t UART_AutoBaud(void);
extern void uartBoot(uint32_t bootMode, uint32_t LoadAddr, uint32_t ImageSize);
uint32_t uartBootInit(uint32_t bootMode);
uint16_t uartGetPacket(uint16_t* length, uint16_t* data);
uint16_t uartaGetACK();
void uartSendChecksum();
void uartSendByte(uint8_t byte);
void uartSendWord(uint16_t word);
uint16_t uartGetOnlyWordData(void);
void uartaFlush(void);
uint16_t uartSendFlashStatusPacket(uint16_t command, FlashStatusCode* statusCode);
uint16_t uartSendDataPacket(uint16_t command, uint8_t* data, uint16_t length);
void CPU_BROM_waitBoot(void);
void sendACK(void);
void sendNAK(void);
static void uartConfigureGPIO(uint32_t bootMode);
static void uartInitGPIO(void);
void transmitByte(uint8_t byte);
uint8_t getHexAscii(uint8_t data);
uint8_t copyImageToRAM(uint32_t bootMode, uint32_t BaseAddress);
uint8_t copyKeysToRAM(uint32_t bootMode, uint32_t BaseAddress);
uint8_t provisionApplicationImgToHSM(uint32_t bootMode, uint32_t BaseAddress);
uint8_t copyC29ImageToFlash(uint32_t bootMode, uint32_t BaseAddress);
uint8_t provisionSecCfgImg(uint32_t bootMode, uint32_t BaseAddress);

#endif