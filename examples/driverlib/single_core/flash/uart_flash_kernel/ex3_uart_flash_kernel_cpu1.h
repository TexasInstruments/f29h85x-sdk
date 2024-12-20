//###########################################################################
//
// FILE:   ex3_uart_flash_kernel.h
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


//
// Included Files
//
#include "device.h"
#include "flash.h"

#include "ex3_cpubrom_uartBoot.h"

//
// Include Flash API include file
//
#include "FlashTech_F29H85x_C29x.h"

//
// Include Flash API example header file
//
#include "flash_programming_F29H85x_C29.h"

//
//  UART
//
#define UART_BOOT                                   (0x01U)
#define UART_BOOT_ALT1                              (0x21U)
#define UART_BOOT_ALT2                              (0x41U)
#define UART_BOOT_ALT3                              (0x61U)
#define UART_BOOT_ALT4                              (0x81U)

//
// CPU1 default address
//
#define CPU1_FLASH_ENTRY_POINT                      (0x10001000U)    


extern uint32_t uartGetFunction(uint32_t  BootMode);
void CPU_jumpToAddr(uint32_t jumpAddr);
