//#############################################################################
//
//
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

//#############################################################################

#ifndef F29H85X_EEPROM_PINGPONG_CONFIG_H_
#define F29H85X_EEPROM_PINGPONG_CONFIG_H_

//
// Include Files
//
//#include "board.h"
#include "driverlib.h"
#include "device.h"

//
// Include the Flash API include file
//
#include "FlashTech_F29H85x_C29x.h"

//
// Include the Flash API example header file
//
#include "flash_programming_F29H85x_C29.h"

//
// Define whether we are using page mode or 64-bit mode
// One of these must be commented out, they are mutually exclusive
//
// #define _64_BIT_MODE 1
#define PAGE_MODE 1

//
// Define which flash bank the EEPROM will be using
//
#define FLASH_BANK_SELECT C29FlashBankFR4RP0StartAddress

//
// Define the device flash sector size and the number of flash sectors it has
//
#define NUM_FLASH_SECTORS 128
#define FLASH_SECTOR_SIZE 0x800

//
// Define the number of EEPROM banks and pages
//
#define NUM_EEPROM_BANKS 8
#define NUM_EEPROM_PAGES 3

// 
// Define the size of an EEPROM page in bytes
//
#define DATA_SIZE 64

//
// Define the number of bytes programmed to flash at a time
// Keep this at 8 for optimal space usage
//
#define WRITE_SIZE_BYTES 8

//
// Calculate the appropriate size of data in EEPROM Pages.
// When programming 64 bits with FlashAPI, ECC requires the data 
// to be aligned to a 64-bit address.
// The below macro rounds the user-specified DATA_SIZE to fit this requirement
//
#define EEPROM_PAGE_DATA_SIZE (DATA_SIZE + 7 - ((DATA_SIZE + 7) % 8))

//
// Define macros for resetting the bank and page pointers
//
#define RESET_BANK_POINTER Bank_Pointer = (uint8_t *) (FLASH_BANK_SELECT + \
        ((uint32_t) FIRST_AND_LAST_SECTOR[EEPROM_ACTIVE_UNIT][0] * FLASH_SECTOR_SIZE))

#define RESET_PAGE_POINTER Page_Pointer = (uint8_t *) (FLASH_BANK_SELECT + \
        ((uint32_t) FIRST_AND_LAST_SECTOR[EEPROM_ACTIVE_UNIT][0] * FLASH_SECTOR_SIZE)) + WRITE_SIZE_BYTES*2

//
// Define a macro for computing the end of the memory allocated for
// EEPROM emulation
//
#define END_OF_SECTOR (FLASH_BANK_SELECT + ((uint32_t)FIRST_AND_LAST_SECTOR[EEPROM_ACTIVE_UNIT][1] * FLASH_SECTOR_SIZE) + (FLASH_SECTOR_SIZE));

//
// Define status values for empty/current/used banks and pages
// The current value is reused in the second half of the status field
// to mark a bank or page as used
//
#define EMPTY_BANK   0xFF
#define CURRENT_BANK 0x5A
#define BLANK_PAGE   0xFF
#define CURRENT_PAGE 0xA5

// ==== Function Prototypes ==== //

//
// Initialization + Setup
//
void Configure_Device();
int EEPROM_Config_Check();
void EEPROM_Erase_All();

//
// Page Mode Functions
//
void EEPROM_UpdateBankStatus();
void EEPROM_UpdatePageStatus();
void EEPROM_Write_Page(uint8_t* Write_Buffer);
void EEPROM_GetValidBank(uint8_t ReadFlag);
void EEPROM_UpdatePageData(uint8_t* Write_Buffer);

//
// 64-bit Mode Functions
//
void EEPROM_Write_64_Bits(uint8_t Num_Words, uint8_t* Write_Buffer);
void EEPROM_64_Bit_Mode_Check_EOS();

//
// Functions for Both
//
void EEPROM_Write_Buffer(uint8_t* address, uint8_t* write_buffer);
void EEPROM_Read(uint8_t* Read_Buffer);
void EEPROM_Erase_Inactive_Unit();
void Erase_Bank();
void Set_Protection_Masks();
uint64_t Configure_Protection_Masks(uint32_t* Sector_Numbers, uint32_t Num_EEPROM_Sectors);

//
// Utility Functions
//
void Fill_Buffer(uint8_t* buffer, int buffer_len, uint8_t value);
void Sample_Error();
void FMSTAT_Fail(void);
void Example_Done();
void ClearFSMStatus(void);

// ==== Global Config + State Variables ==== //

//
// Page Mode-Only State
//
extern uint8_t Bank_Status[WRITE_SIZE_BYTES];
extern uint8_t Page_Status[WRITE_SIZE_BYTES];
extern uint8_t *Bank_Pointer;
extern uint8_t *Page_Pointer;
extern uint32_t Bank_Size;

//
// Both
//
extern uint8_t Read_Buffer[];
extern uint8_t Write_Buffer[];
extern uint8_t Erase_Inactive_Unit;
extern uint8_t EEPROM_ACTIVE_UNIT;

extern uint32_t write_buffer_len;
extern uint32_t BLANK_CHECK_LEN;
extern uint32_t WE_Protection_A_Mask;
extern uint32_t WE_Protection_B_Mask;
extern uint32_t FIRST_AND_LAST_SECTOR[2][2];
extern uint32_t NUM_EEPROM_SECTORS;
extern uint32_t u32UserFlashConfig;

//
// Sector length in number of 16bits
//
#define Sector2KB_u16length                 0x200U
#define Bank256KB_u16length                 0x20000U

//
// Sector length in number of 32bits
//
#define Sector2KB_u32length                 0x200U
#define Bank256KB_u32length                 0x10000U

#define FlashTech_CPU0_BASE_ADDRESS ((Fapi_FmcRegistersType *)FLASH_FAPI_FLASHNW_FC1_BASE)

#endif /* F29H85X_EEPROM_PINGPONG_CONFIG_H_ */
