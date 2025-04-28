//###########################################################################
//
// FILE:    f29h85x_kernel_commands_cpu1.h
//
// TITLE:   User kernel commands
//
// The common command packet defintion file used across flash kernel and host programmer
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

#ifndef F29H85X_KERNEL_COMMANDS_CPU1_H_
#define F29H85X_KERNEL_COMMANDS_CPU1_H_

//
// Packet content struct
//
typedef struct
{
   uint16_t status;
   uint32_t address;
   uint16_t flashAPIError;
   uint32_t flashAPIFsmStatus;
}  FlashStatusCode;

//
// Enables packet checksum
//
#define checksum_enable             1

//
// Command Packet Command Options
//
#define DFU_CPU1                    0x0001
#define DFU_CPU3                    0x0002
#define ERASE_MAIN_CPU1             0x0003
#define ERASE_MAIN_CPU3             0x0004
#define ERASE_BANKMGMT_CPU1         0x0005
#define ERASE_BANKMGMT_CPU3         0x0006
#define ERASE_SECCFG_CPU1           0x0007
#define ERASE_SECCFG_CPU3           0x0008
#define RUN_CPU1                    0x0009
#define RESET_CPU1                  0x000A
#define HSM_RT_IMAGE                0x000B
#define SEC_CFG_IMAGE               0x000C
#define HSM_CP_FLASH_IMAGE          0x000D
#define HSM_KEYS                    0x000E
#define LFU_CPU1                    0x000F
#define CPU1_CP_FLASH_IMAGE         0x0010
#define CPU3_CP_FLASH_IMAGE         0x0011
#define GENERIC_DATA_PACKET         0x0012
#define RUN_CPU3                    0x0019
#define RESET_CPU3                  0x0020
#define BANK_SELECT                 0x00C0
#define BANK_MODE_SELECT            0x00D0
#define SET_APP_LOAD_ADDRESS        0x00E0
#define SET_APP_ENTRY_ADDRESS       0x00F0
#define SET_APP_SIZE                0x00F1
#define SYNC_STATUS                 0x00F2
#define DECIPHER_PACKET_ERROR		0x00A0

//
// Command Packet Return Error Status Options
//
#define NO_COMMAND_ERROR					 0x1000
#define BLANK_ERROR							 0x2000
#define VERIFY_ERROR						 0x3000
#define PROGRAM_ERROR						 0x4000
#define COMMAND_ERROR						 0x5000
#define UNLOCK_ERROR						 0x6000
#define AUTHENTICATION_ERROR			     0x7000
#define INCORRECT_DATA_BUFFER_LENGTH         0x8000
#define DATA_ECC_BUFFER_LENGTH_MISMATCH      0x9000
#define FLASH_REGS_NOT_WRITABLE              0xA000
#define FEATURE_NOT_AVAILABLE                0xB000
#define INVALID_ADDRESS                      0xC000
#define INVALID_CPUID                        0xD000
#define FAILURE                              0xE000
#define NOT_RECOGNIZED                       0xF000
#define INVALID_APP_SIZE                     0xF001

//
// Packet Handshake
// 
#define ACK                             0x2D
#define NAK                             0xA5
#define PACKET_HEADER_LSB				0xE4
#define PACKET_HEADER_MSB				0x1B
#define FULL_PACKET_HEADER				0x1BE4
#define PACKET_FOOTER_LSB				0x1B
#define PACKET_FOOTER_MSB				0xE4
#define FULL_PACKET_FOOTER				0xE41B

#endif /* F29H85X_KERNEL_COMMANDS_CPU1_H_ */