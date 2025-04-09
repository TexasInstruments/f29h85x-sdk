//###########################################################################
//
// FILE:    F29H85x_EEPROM_PingPong_Example.c
//
// TITLE:   EEPROM_PingPong main file
//! <h1> EEPROM_PingPong main file </h1>
//
//###########################################################################
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

#include <F29H85x_EEPROM_PingPong_Config.h>

//
// Set the flash configuration
//
extern uint32_t Flash_CPUScaleFactor;

Fapi_FlashBankType  BankType = C29Bank;
Fapi_FOTAStatus  FOTAStatus = FOTA_Image;
uint32_t u32UserFlashConfig = 0;

#ifdef _64_BIT_MODE
//
// Initialize 64-bit read and write buffers
//
uint32_t write_buffer_len = WRITE_SIZE_BYTES;
uint8_t Write_Buffer[WRITE_SIZE_BYTES] = {[0 ... WRITE_SIZE_BYTES - 1] = 0xFF};
uint8_t Read_Buffer[WRITE_SIZE_BYTES] = {0};
#else

uint32_t write_buffer_len = EEPROM_PAGE_DATA_SIZE;

//
// Initialize page-size read and write buffers.
// Read_Buffer uses DATA_SIZE because the read data doesn't need
// to be padded for alignment.
//
uint8_t Write_Buffer[EEPROM_PAGE_DATA_SIZE] = {[0 ... EEPROM_PAGE_DATA_SIZE-1] = 0xFF};
uint8_t Read_Buffer[DATA_SIZE] = {0};
#endif

int main(void)
{
    //
    // Setup the device and initialize flash
    //
    Configure_Device();

    //
    // Ensure EEPROM configuration is valid for this device
    //
    int EEPROMConfigCheck = EEPROM_Config_Check();
    if (EEPROMConfigCheck == 0xFFFF || EEPROMConfigCheck == 0xEEEE || EEPROMConfigCheck == 0xCCCC)
    {
        Sample_Error();
    }

    //
    // Precompute and cache the length passed to the blank check function
    //
    BLANK_CHECK_LEN = (FLASH_SECTOR_SIZE * (FIRST_AND_LAST_SECTOR[EEPROM_ACTIVE_UNIT][1] - FIRST_AND_LAST_SECTOR[EEPROM_ACTIVE_UNIT][0] + 1)) / 4;
    
    //
    // Erase any pre-existing data before starting emulation
    //
    EEPROM_Erase_All();

    uint32_t Loop_Limit;
    uint32_t i;

#ifdef _64_BIT_MODE
    //
    // Write an increasing series of integers as our EEPROM data.
    // We will fill the EEPROM, erase, and fill it again to demostrate full functionality
    //
    Loop_Limit = (NUM_EEPROM_SECTORS * FLASH_SECTOR_SIZE * 2) / WRITE_SIZE_BYTES + 1;
    for (i = 0; i < Loop_Limit; i++)
    {
        Fill_Buffer(Write_Buffer, write_buffer_len, i % 256);
        EEPROM_Write_64_Bits(WRITE_SIZE_BYTES, Write_Buffer);
        EEPROM_Read(Read_Buffer);
    }

#else
    //
    // Fill the write buffer with an increasing series of integers
    //
    for(i=0; i<DATA_SIZE; i++)
    {
        Write_Buffer[i] = i;
    }

    //
    // We will fill the EEPROM, erase, and fill it again to demostrate full functionality
    //
    Loop_Limit = (NUM_EEPROM_BANKS * NUM_EEPROM_PAGES * 2) + 1;

    for (i = 0; i < Loop_Limit; i++)
    {
        EEPROM_Write_Page(Write_Buffer);
        EEPROM_Read(Read_Buffer);
    }
#endif

    //
    // Release semaphore
    //
    while (!SSU_releaseFlashSemaphore());

    Example_Done();

    return 0;
}

void Configure_Device() {
    //
    // Initialize device clock and peripherals
    // Copy the Flash initialization code from Flash to RAM
    // Copy the Flash API from Flash to RAM
    // Configure Flash wait-states, fall back power mode, performance features
    // and ECC
    //
    Device_init();
    Flash_initModule(3);
    
    //
    // Initialize GPIO
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();
    
    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    __asm(" ENINT");

    Fapi_StatusType  oReturnCheck;

    //
    // Request semaphore for CPU1
    //
    while (!SSU_claimFlashSemaphore());

    //
    // Set configuration as per user request
    //
    u32UserFlashConfig = Fapi_getUserConfiguration(BankType, FOTAStatus);
    oReturnCheck = Fapi_SetFlashCPUConfiguration(Mode0);
    
    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Sample_Error();
    }
    
    //
    // Initialize the Flash API by providing the Flash register base address
    // and operating frequency(in MHz).
    // This function is required to initialize the Flash API based on System
    // frequency before any other Flash API operation can be performed.
    // This function must also be called whenever System frequency or RWAIT is
    // changed.
    //

    oReturnCheck = Fapi_initializeAPI((Fapi_FmcRegistersType*) FLASHCONTROLLER1_BASE, 200);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Sample_Error();
    }
}
