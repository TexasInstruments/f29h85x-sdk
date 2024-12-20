// ###########################################################################
//
//  FILE:   ex3_cpubrom_uartBoot.h
//
//  TITLE:  BootROM Definitions.
//
// ###########################################################################
//  $TI Release:  $
//  $Release Date:  $
//  //
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

#ifndef C_BOOTROM_UARTBOOT_H
#define C_BOOTROM_UARTBOOT_H

//
// Includes
//
#include "device.h"

//
// Defines
//
#define UART_BOOT_CERT_ADDR             (LDA7_RAM_BASE)
#define UART_BOOT_LOAD_ADDR             (UART_BOOT_CERT_ADDR + MAX_CERT_SIZE)
#define UART_MAX_BOOT_RETRY             (1U)
#define UART_BOOT_RUN_ADDR              (LPA0_RAM_BASE)
#define UART_BOOT_CHUNK_SIZE            (16U * 1024U)
#define UART_BOOT_MAX_IMAGE_SIZE        (96U * 1024U)

#define TARGET_ADDRESS                  (0x0050U)

#define UART_BOOT_BAUDRATE              (115200UL)
#define UART_BOOT_CONFIG                (UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE | UART_CONFIG_WLEN_8) // 1 stop bit, No Parity, 8-bit character


typedef uint16_t (*uint16fptr)();

//
//  Functions
//
uint16_t uartGetData(void);
uint32_t uartRead(uint32_t addr, uint32_t size);//
uint8_t uartGetCPData(void);
void uartSendCPData(uint8_t byteData);


#endif /*C_BOOTROM_UARTBOOT_H*/