//###########################################################################
//
// FILE:    flash_mode3_512_program_cpu1_cpu3x3.c
//
// TITLE:   Flash Bank Mode 3 512-bit programming Example for CPU3
//! <h1> Flash Bank Mode 3 512-bit programming Example for CPU3 </h1>
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

//
// Included Files
//
#include "board.h"

//
// Include Flash API include file
//
#include "FlashTech_F29H85x_C29x.h"

//
// Include Flash API example header file
//
#include "flash_programming_F29H85x_C29.h"

//
// Defines
//

//
// Length (in bytes) of data buffer used for program
//
#define  WORDS_IN_FLASH_BUFFER    0x200

//
// Globals
//

//
// Data Buffers used for program operation using the flash API program function
//
uint8_t   Buffer[WORDS_IN_FLASH_BUFFER];
uint32_t *Buffer32;

//
// Flash API configuration variables
//
Fapi_FlashBankType  BankType = C29Bank;
Fapi_FOTAStatus  FOTAStatus = FOTA_Image;
uint32_t u32UserFlashConfig = 0;

//
// Prototypes
//

//
// Termination States
//
void Example_Error(Fapi_StatusType status);
void Example_Done(void);
void FMSTAT_Fail(void);
void ECC_Fail(void);

//
// Example Functions
//
void Example_CallFlashAPI(void);
void Example_EraseBanks(void);
void Example_EraseSector(void);
void Example_ProgramUsingC29AutoECC512bit(void);
void Example_ProgramUsingC29DataAndECC512bit(void);
void Example_ProgramUsingC29DataOnlyECCOnly512bit(void);
void Example_ProgramDataFlashUsingC29AutoECC512Bit(void);
void ClearFSMStatus(uint32_t u32StartAddress, uint32_t u32UserFlashConfig);
void ConstructInterleavedData1024Bits(uint8_t* sequential1024BitsArrPtr);

//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Sync with CPU1 so that user has time to connect to CPU3 and set breakpoints
    //
    IPC_sync(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG31);

    //
    // Request semaphore for CPU3
    //
    if (!SSU_claimFlashSemaphore())
    {
        //
        // Stop execution if unable to claim the semaphore
        //
        Example_Error(0);
    }

    Fapi_StatusType oReturnCheck;

    //
    // Get the current FOTA configuration. This variable is passed to
    // as a parameter to most functions and if in Mode 1 or 3, determines
    // whether or not the update region will be written to
    //
    u32UserFlashConfig = Fapi_getUserConfiguration(BankType, FOTAStatus);

    //
    // Set Flash API Bank Mode configuration. These address mappings
    // will be used for program and erase operations. Outside of specific
    // use cases, this should match the device's currently programmed bank mode
    //
    oReturnCheck = Fapi_SetFlashCPUConfiguration(Mode3);
    
    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error(oReturnCheck);
    }

    //
    // Flash API functions should not be executed from the same bank on which
    // erase/program operations are in progress.
    // Also, note that there should not be any access to the Flash bank on
    // which erase/program operations are in progress.
    //
    Example_CallFlashAPI();

    //
    // Release the flash semaphore
    //
    if (!SSU_releaseFlashSemaphore())
    {
        //
        // Stop execution if unable to release the flash semaphore
        //
        Example_Error(0);
    }

    //
    // Example is done here
    //
    Example_Done();
}

//*****************************************************************************
//  Example_CallFlashAPI
//
//  This function will interface to the flash API.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
void Example_CallFlashAPI(void)
{
    //
    // In this example we only program the update region (FOTA_Image u32FlashConfig setting),
    // as the only flash available in the active region is used to
    // store this program (when using the FLASH build configuration).
    // To program to the active region, call Fapi_getUserConfiguration() and Fapi_setFlashCPUConfiguration()
    // using Active_Bank instead of FOTA_Image
    //

    //
    // Also note that even though we are programming to the update region,
    // the active bank addresses are still used -- the address translation is
    // handled internally by the Flash API.
    //

    //
    // Fill a buffer with data to program into the flash.
    //
    for(uint32_t i = 0; i < WORDS_IN_FLASH_BUFFER; i++)
    {
        Buffer[i] = i;
    }

    //
    // Assign 32-indexed buffer for ECC computation
    //
    Buffer32 = (uint32_t*) Buffer;
    
    //
    // Reformat the buffer so that it is written to flash
    // in the same order
    //
    for (uint32_t i = 0; i < 4; i++)
    {
        ConstructInterleavedData1024Bits(Buffer + (i*128));
    }

    //
    // Erase banks before programming
    //
    Example_EraseBanks();

    //
    // Program first 0x200 bytes of FR3RP1 (at 0x10700000) using 512-bit AutoECC option
    //
    Example_ProgramUsingC29AutoECC512bit();

    //
    // Erase the sector
    //
    Example_EraseSector();

    //
    // Program first 0x200 bytes of FR3RP1 (at 0x10700000) using 512-bit DataAndECC option
    //
    Example_ProgramUsingC29DataAndECC512bit();

    //
    // Erase the sector
    //
    Example_EraseSector();

    //
    // Program first 0x200 bytes of FR3RP1 (at 0x10700000) using 512-bit DataOnly and EccOnly options
    //
    Example_ProgramUsingC29DataOnlyECCOnly512bit();

    //
    // Erase the sector
    //
    Example_EraseSector();

    //
    // Reset data buffer for programming to non-interleaved data bank
    //
    for (uint32_t i = 0 ; i < WORDS_IN_FLASH_BUFFER; i++)
    {
        Buffer[i] = i;
    }
    
    //
    // Program first 0x200 bytes of FR4RP0 (at 0x10C00000) using 512-bit AutoECC option
    //
    Example_ProgramDataFlashUsingC29AutoECC512Bit();

    //
    // Erase all banks for a clean exit
    //
    Example_EraseBanks();
}

//*****************************************************************************
//  Example_ProgramUsingC29AutoECC512bit
//
//  Example function to Program data in Flash using "AutoEccGeneration" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
void Example_ProgramUsingC29AutoECC512bit(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    
    //
    // Issue program command
    //
    for(uint32_t u32CurrentAddress = C29FlashBankFR2RP0StartAddress;
        u32CurrentAddress < C29FlashBankFR2RP0EndAddressPlus1;
        u32CurrentAddress += FlashC29BankOffset)
    {
        //
        // Program 0x200 words to given bank
        //
        for(uint32_t i = 0, u32Index = u32CurrentAddress;
            u32Index < (u32CurrentAddress + WORDS_IN_FLASH_BUFFER);
            i += 128, u32Index += 128)
        {
            for(uint8_t u8Iterator = 1; u8Iterator <= 2; u8Iterator++)
            {
                ClearFSMStatus(u32Index, u32UserFlashConfig);

                //
                // Set program/erase protection
                //
                Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                            FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
                Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                            FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

                oReturnCheck = Fapi_issueAutoEcc512ProgrammingCommand((uint32_t *) u32Index, Buffer+i,
                                                                      64, u32UserFlashConfig,
                                                                      u8Iterator);

                //
                // Wait until the Flash program operation is over
                //
                while(Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

                if(oReturnCheck != Fapi_Status_Success)
                {
                    //
                    // Check Flash API documentation for possible errors
                    //
                    Example_Error(oReturnCheck);
                }

                //
                // Read FMSTAT register contents to know the status of FSM after
                // program command to see if there are any program operation related
                // errors
                //
                oFlashStatus = Fapi_getFsmStatus(u32Index, u32UserFlashConfig);
                if(oFlashStatus != 3)
                {
                    //
                    // Check FMSTAT and debug accordingly
                    //
                    FMSTAT_Fail();
                }

                //
                // Verify the programmed values.  Check for any ECC errors.
                //
                oReturnCheck = Fapi_doVerify((uint32_t *) u32Index,
                                             16, (uint32_t *) (Buffer + i),
                                             &oFlashStatusWord, u8Iterator, u32UserFlashConfig);

                if(oReturnCheck != Fapi_Status_Success)
                {
                    //
                    // Check Flash API documentation for possible errors
                    //
                    Example_Error(oReturnCheck);
                }
            }
        }
    }
}

//*****************************************************************************
//  Example_ProgramUsingC29DataAndECC512bit
//
//  Example function to Program data in Flash using "DataAndEcc" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************

void Example_ProgramUsingC29DataAndECC512bit(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Issue program command
    //
    for(uint32_t u32CurrentAddress = C29FlashBankFR2RP0StartAddress;
        u32CurrentAddress < C29FlashBankFR2RP0EndAddressPlus1;
        u32CurrentAddress += FlashC29BankOffset)
    {
        //
        // Program 0x200 words to given bank
        //
        for(uint32_t i = 0, u32Index = u32CurrentAddress;
            u32Index < (u32CurrentAddress + WORDS_IN_FLASH_BUFFER);
            i += 128, u32Index += 128)
        {
            uint8_t u8Iterator;
            for(u8Iterator = 1; u8Iterator <= 2; u8Iterator++)
            {
                ClearFSMStatus(u32Index, u32UserFlashConfig);

                //
                // Set program/erase protection
                //
                Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                            FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
                Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                            FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

                uint8_t  u8ECC_array[8];
                uint32_t u32ECC_array[4];
                for(uint8_t j = 0; j < 8; j += 2)
                {
                    //
                    // Point LData to the lower 64 bit data
                    // and   HData to the higher 64 bit data
                    //
                    uint64_t *LData = (uint64_t *) (Buffer + i/4 + j*8);
                    uint64_t *HData = (uint64_t *) (Buffer + i/4 + j*8 + 8);

                    //
                    // Calculate ECC for lower 64 bit and higher 64 bit data
                    //
                    uint32_t ECC_LB = u8ECC_array[j]   = Fapi_calculateEcc((uint32_t *) (u32Index + j*16), LData, u8Iterator);
                    uint32_t ECC_HB = u8ECC_array[j+1] = Fapi_calculateEcc((uint32_t *) (u32Index + j*16 + 8), HData, u8Iterator);
                    u32ECC_array[j/2] = (uint32_t) ((ECC_HB<<8) | ECC_LB);

                }

                oReturnCheck = Fapi_issueDataAndEcc512ProgrammingCommand((uint32_t *) u32Index, Buffer+i, 64,
                                                                         u8ECC_array, 8, u32UserFlashConfig, u8Iterator);

                //
                // Wait until the Flash program operation is over
                //
                while(Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

                if(oReturnCheck != Fapi_Status_Success)
                {
                    //
                    // Check Flash API documentation for possible errors
                    //
                    Example_Error(oReturnCheck);
                }

                //
                // Read FMSTAT register contents to know the status of FSM after
                // program command to see if there are any program operation related
                // errors
                //
                oFlashStatus = Fapi_getFsmStatus(u32Index, u32UserFlashConfig);
                if(oFlashStatus != 3)
                {
                    //
                    // Check FMSTAT and debug accordingly
                    //
                    FMSTAT_Fail();
                }

                //
                // Verify the programmed values.  Check for any ECC errors.
                //
                oReturnCheck = Fapi_doVerify((uint32_t *) u32Index,
                                            16, (uint32_t *) (Buffer + i),
                                            &oFlashStatusWord, u8Iterator, u32UserFlashConfig);

                if(oReturnCheck != Fapi_Status_Success)
                {
                    //
                    // Check Flash API documentation for possible errors
                    //
                    Example_Error(oReturnCheck);
                }
            }
        }
    }
}

//*****************************************************************************
//  Example_ProgramUsingC29DataOnlyECCOnly512bit
//
//  Example function to Program data in Flash using "DataAndEcc" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************

void Example_ProgramUsingC29DataOnlyECCOnly512bit(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    
    //
    // Issue program command
    //
    for(uint32_t u32CurrentAddress = C29FlashBankFR2RP0StartAddress;
        u32CurrentAddress < C29FlashBankFR2RP0EndAddressPlus1;
        u32CurrentAddress += FlashC29BankOffset)
    {

        //
        // Program 0x200 words to given bank
        //
        for(uint32_t i = 0, u32Index = u32CurrentAddress;
            u32Index < (u32CurrentAddress + WORDS_IN_FLASH_BUFFER);
            i += 128, u32Index += 128)
        {
            for(uint8_t u8Iterator = 1; u8Iterator <= 2; u8Iterator++)
            {
                ClearFSMStatus(u32Index, u32UserFlashConfig);

                //
                // Set program/erase protection
                //
                Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                            FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
                Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                            FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

                uint8_t  u8ECC_array[8];
                uint32_t u32ECC_array[4];
                for(uint8_t j = 0; j < 8; j += 2)
                {
                    //
                    // Point LData to the lower 64 bit data
                    // and   HData to the higher 64 bit data
                    //
                    uint64_t *LData = (uint64_t *) (Buffer + i/4 + j*8);
                    uint64_t *HData = (uint64_t *) (Buffer + i/4 + j*8 + 8);

                    //
                    // Calculate ECC for lower 64 bit and higher 64 bit data
                    //
                    uint32_t ECC_LB = u8ECC_array[j] =   Fapi_calculateEcc((uint32_t *) (u32Index + j*16),LData, u8Iterator);
                    uint32_t ECC_HB = u8ECC_array[j+1] = Fapi_calculateEcc((uint32_t *) (u32Index+ j*16 + 8) ,HData, u8Iterator);
                    u32ECC_array[j/2] = (uint32_t) ((ECC_HB<<8) | ECC_LB);
                }

                oReturnCheck = Fapi_issueDataOnly512ProgrammingCommand((uint32_t *) u32Index, Buffer+i,
                                                                        64, u32UserFlashConfig, u8Iterator);

                //
                // Wait until the Flash program operation is over
                //
                while(Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

                if(oReturnCheck != Fapi_Status_Success)
                {
                    //
                    // Check Flash API documentation for possible errors
                    //
                    Example_Error(oReturnCheck);
                }

                //
                // Read FMSTAT register contents to know the status of FSM after
                // program command to see if there are any program operation related
                // errors
                //
                oFlashStatus = Fapi_getFsmStatus(u32Index, u32UserFlashConfig);
                if(oFlashStatus != 3)
                {
                    //
                    // Check FMSTAT and debug accordingly
                    //
                    FMSTAT_Fail();
                }


                ClearFSMStatus(u32Index, u32UserFlashConfig);

                //
                // Enable program/erase protection for select sectors where this example is
                // located CMDWEPROTA, CMDWEPROTB
                //
                Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                            FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
                Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                            FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);


                oReturnCheck = Fapi_issueEccOnly64ProgrammingCommand((uint32_t *) u32Index, &(u8ECC_array[0]), 8,
                                                                     u32UserFlashConfig, u8Iterator);

                //
                // Wait until the Flash program operation is over
                //
                while(Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

                if(oReturnCheck != Fapi_Status_Success)
                {
                    //
                    // Check Flash API documentation for possible errors
                    //
                    Example_Error(oReturnCheck);
                }

                //
                // Read FMSTAT register contents to know the status of FSM after
                // program command to see if there are any program operation related
                // errors
                //
                oFlashStatus = Fapi_getFsmStatus(u32Index, u32UserFlashConfig);
                if(oFlashStatus != 3)
                {
                    //
                    // Check FMSTAT and debug accordingly
                    //
                    FMSTAT_Fail();
                }

                //
                // Verify the programmed values.  Check for any ECC errors.
                //
                oReturnCheck = Fapi_doVerify((uint32_t *) u32Index, 16, (uint32_t *) (Buffer + i),
                                             &oFlashStatusWord, u8Iterator, u32UserFlashConfig);

                if(oReturnCheck != Fapi_Status_Success)
                {
                    //
                    // Check Flash API documentation for possible errors
                    //
                    Example_Error(oReturnCheck);
                }
            }
        }
    }
}

//*****************************************************************************
//  Example_ProgramDataFlashUsingC29AutoECC
//
//  Example function to Program data in Flash using "AutoEccGeneration" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************

void Example_ProgramDataFlashUsingC29AutoECC512Bit(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Issue program command
    //
    for(uint32_t u32CurrentAddress = C29FlashBankFR4RP0StartAddress;
        u32CurrentAddress < C29FlashBankFR4RP0EndAddressPlus1;
        u32CurrentAddress += FlashC29BankOffset)
    {

        //
        // Program 0x200 words to given bank
        //
        for(uint32_t i = 0, u32Index = u32CurrentAddress;
            u32Index < (u32CurrentAddress + WORDS_IN_FLASH_BUFFER); 
            i += 64, u32Index += 64)
        {
            ClearFSMStatus(u32Index, u32UserFlashConfig);

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

            oReturnCheck = Fapi_issueAutoEcc512ProgrammingCommand((uint32_t *) u32Index, Buffer + i,
                                                                64, u32UserFlashConfig, 0);

            //
            // Wait until the Flash program operation is over
            //
            while(Fapi_checkFsmForReady(u32Index,  u32UserFlashConfig) == Fapi_Status_FsmBusy);

            if(oReturnCheck != Fapi_Status_Success)
            {
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error(oReturnCheck);
            }

            //
            // Read FMSTAT register contents to know the status of FSM after
            // program command to see if there are any program operation related
            // errors
            //
            oFlashStatus = Fapi_getFsmStatus(u32Index,  u32UserFlashConfig);
            if(oFlashStatus != 3)
            {
                //
                // Check FMSTAT and debug accordingly
                //
                FMSTAT_Fail();
            }

            //
            // Verify the programmed values.  Check for any ECC errors.
            //
            oReturnCheck = Fapi_doVerifyByByte((uint8_t *) u32Index,
                                                64, (uint8_t *) (Buffer + i),
                                                &oFlashStatusWord, 0, u32UserFlashConfig);

            if(oReturnCheck != Fapi_Status_Success)
            {
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error(oReturnCheck);
            }
        }
    }
}

//*****************************************************************************
//  Example_EraseBanks
//
//  Example function to Erase data of a sector in Flash.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************

void Example_EraseBanks(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    
    //
    // Issue bank erase command
    //
    for(uint32_t u32CurrentAddress = C29FlashBankFR2RP0StartAddress;
        u32CurrentAddress < C29FlashBankFR2RP0EndAddressPlus1;
        u32CurrentAddress += FlashC29BankOffset)
    {
        //
        // Loop for erasing 1 interleaved bank
        //
        for(uint8_t u8Iterator = 1; u8Iterator <= 2; u8Iterator++)
        {
            ClearFSMStatus(u32CurrentAddress, u32UserFlashConfig);

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *) (u32CurrentAddress), u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t *) (u32CurrentAddress), u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

            //
            // Issue bank erase command
            //
            oReturnCheck = Fapi_issueBankEraseCommand((uint32_t *) (u32CurrentAddress), u8Iterator , u32UserFlashConfig);

            //
            // Wait until FSM is done with erase operation
            //
            while (Fapi_checkFsmForReady(u32CurrentAddress, u32UserFlashConfig) != Fapi_Status_FsmReady){}

            if(oReturnCheck != Fapi_Status_Success)
            {
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error(oReturnCheck);
            }

            //
            // Read FMSTAT register contents to know the status of FSM after
            // erase command to see if there are any erase operation related errors
            //
            oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, u32UserFlashConfig);
            if(oFlashStatus != 3)
            {
                //
                // Check Flash API documentation for FMSTAT and debug accordingly
                // Fapi_getFsmStatus() function gives the FMSTAT register contents.
                // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
                // VOLTSTAT bit is set (Refer to API documentation for more details).
                //
                FMSTAT_Fail();
            }
        }

        //
        // Do blank check
        // Blank check is performed on all the sectors that are not protected
        // during Bank erase
        // Verify that Bank 0 is erased.
        // The Erase command itself does a verify as it goes.
        // Hence erase verify by CPU reads (Fapi_doBlankCheck()) is optional.
        //
        Fapi_FlashStatusType oReturnCheck = Fapi_doBlankCheck((uint32_t *) u32CurrentAddress,
                                                              (128*Sector2KB_u32length),
                                                              &oFlashStatusWord, 0 , u32UserFlashConfig);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for error info
            //
            Example_Error(oReturnCheck);
        }
    }

    //
    // Issue Bank erase command for Data Flash
    // No for loops here because data flash is not interleaved
    //
    ClearFSMStatus(C29FlashBankFR4RP0StartAddress, u32UserFlashConfig);

    //
    // Set program/erase protection
    //
    Fapi_setupBankSectorEnable((uint32_t *) (C29FlashBankFR4RP0StartAddress), u32UserFlashConfig,
                                FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
    Fapi_setupBankSectorEnable((uint32_t *) (C29FlashBankFR4RP0StartAddress), u32UserFlashConfig,
                                FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);


    //
    // Issue bank erase command
    //
    oReturnCheck = Fapi_issueBankEraseCommand((uint32_t *) (C29FlashBankFR4RP0StartAddress), 0, u32UserFlashConfig);

    //
    // Wait until FSM is done with erase operation
    //
    while (Fapi_checkFsmForReady(C29FlashBankFR4RP0StartAddress, u32UserFlashConfig) != Fapi_Status_FsmReady){}

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error(oReturnCheck);
    }

    //
    // Read FMSTAT register contents to know the status of FSM after
    // erase command to see if there are any erase operation related errors
    //
    oFlashStatus = Fapi_getFsmStatus(C29FlashBankFR4RP0StartAddress, u32UserFlashConfig);
    if(oFlashStatus != 3)
    {
        //
        // Check Flash API documentation for FMSTAT and debug accordingly
        // Fapi_getFsmStatus() function gives the FMSTAT register contents.
        // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
        // VOLTSTAT bit is set (Refer to API documentation for more details).
        //
       FMSTAT_Fail();
    }

    //
    // Do blank check
    // Blank check is performed on all the sectors that are not protected
    // during Bank erase
    // Verify that Bank 0 is erased.
    // The Erase command itself does a verify as it goes.
    // Hence erase verify by CPU reads (Fapi_doBlankCheck()) is optional.
    //
    oReturnCheck = Fapi_doBlankCheck((uint32_t *) C29FlashBankFR4RP0StartAddress,
                                     (128*Sector2KB_u32length),
                                     &oFlashStatusWord, 0 , u32UserFlashConfig);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for error info
        //
        Example_Error(oReturnCheck);
    }
}

//*****************************************************************************
//  Example_EraseSector
//
//  Example function to Erase data of a sector in Flash.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
void Example_EraseSector(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Issue sector erase command
    //
    for(uint32_t u32CurrentAddress = C29FlashBankFR2RP0StartAddress;
        u32CurrentAddress < C29FlashBankFR2RP0EndAddressPlus1;
        u32CurrentAddress +=FlashC29BankOffset)
    {
        for(uint8_t u8Iterator=1; u8Iterator<=2; u8Iterator++)
        {
            ClearFSMStatus(u32CurrentAddress, u32UserFlashConfig);

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *) (u32CurrentAddress), u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t *) (u32CurrentAddress), u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

            //
            // Erase Sector
            //
            oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                                                             (uint32_t *) (u32CurrentAddress),
                                                             u8Iterator, u32UserFlashConfig);

            //
            // Wait until FSM is done with erase sector operation
            //
            while(Fapi_checkFsmForReady(u32CurrentAddress, u32UserFlashConfig) == Fapi_Status_FsmBusy);

            if(oReturnCheck != Fapi_Status_Success)
            {
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error(oReturnCheck);
            }

            //
            // Read FMSTAT register contents to know the status of FSM after
            // erase command to see if there are any erase operation related errors
            //
            oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, u32UserFlashConfig);
            if(oFlashStatus != 3)
            {
                //
                // Check Flash API documentation for FMSTAT and debug accordingly
                // Fapi_getFsmStatus() function gives the FMSTAT register contents.
                // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
                // VOLTSTAT bit is set (Refer to API documentation for more details).
                //
                FMSTAT_Fail();
            }
        }

        //
        // Verify the sector is erased
        //
        oReturnCheck = Fapi_doBlankCheck((uint32_t *) (u32CurrentAddress),
                                         Sector2KB_u32length,
                                         &oFlashStatusWord, 0, u32UserFlashConfig);
        if(oReturnCheck != Fapi_Status_Success)
        {
           //
           // Check Flash API documentation for error info
           //
           Example_Error(oReturnCheck);
        }
    }
}

//*****************************************************************************
//  ConstructInterleavedData1024Bits
//
//  Example function to reformat a 1024-bit data buffer so that it reads back correctly
//  when written to flash
//*****************************************************************************
void ConstructInterleavedData1024Bits(uint8_t* sequential1024BitsArrPtr)
{
    uint8_t* srcBuffer = sequential1024BitsArrPtr;
    uint8_t tmpBuffer[64];

    //
    // Even(first) interleaved region: 0-15, 32-47, 64-79, 96-111 Byte
    // Note: First even region (0-15) doesn't need to be re-copied, starting from 32 
    //
    int evenIdx = 32;  
    // Odd(second) interleaved region: 16-31, 48-63, 80-95, 112-127 Byte
    int oddIdx = 16; 
    
    //
    // Preparing temp buffer to store the 2nd half of 1024bit data composed of odd(second) interleaved 512bit data
    //
    for (int idx = 0; idx < 64; idx += 16)
    {
       memcpy(&tmpBuffer[idx], &srcBuffer[oddIdx], 16);
       oddIdx += 32;
    }

    //
    // Preparing src buffer to store the 1st half of 1024bit data composed of even(first) interleaved 512bit data
    // Skipping first even region (0-15)
    //
    for (int idx = 16; idx < 64; idx += 16)
    {
       memcpy(&srcBuffer[idx], &srcBuffer[evenIdx], 16);
       evenIdx += 32;
    }

    //
    // Copying the 2nd half of 1024bit back to the bottom half of the original buffer
    //
    memcpy(&srcBuffer[64], tmpBuffer, 64);
}

//**************************************************************************************
//  ClearFSMStatus
//
//  This function clears the status (STATCMD, similar to FMSTAT of the previous
//  devices) of the previous flash operation.
//  This function and the flash API functions used in this function are
//  executed from RAM in this example.
//**************************************************************************************
void ClearFSMStatus(uint32_t u32StartAddress, uint32_t u32UserFlashConfig) {
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_StatusType  oReturnCheck;

    //
    // Wait until FSM is done with the previous flash operation
    //
    while (Fapi_checkFsmForReady(u32StartAddress, u32UserFlashConfig) != Fapi_Status_FsmReady);
    
    oFlashStatus = Fapi_getFsmStatus(u32StartAddress, u32UserFlashConfig);

    //
    // If the status register is nonzero, then clear it
    //
    if (oFlashStatus != 0)
    {
        //
        // Clear the status register
        //
        oReturnCheck = Fapi_issueAsyncCommand(u32StartAddress, u32UserFlashConfig, Fapi_ClearStatus);

        //
        // Wait until status is cleared
        //
        while (Fapi_getFsmStatus(u32StartAddress, u32UserFlashConfig) != 0) {}

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error(oReturnCheck);
        }
    }
}

//******************************************************************************
// For this example, just stop here if an API error is found
//******************************************************************************
void Example_Error(Fapi_StatusType status)
{
    //
    //  Error code will be in the status parameter
    //
    asm(" EMUSTOP0");
    for (;;);
}

//******************************************************************************
//  For this example, once we are done just stop here
//******************************************************************************
void Example_Done(void)
{
    asm(" EMUSTOP0");
    for (;;);
}

//******************************************************************************
// For this example, just stop here if FMSTAT fail occurs
//******************************************************************************
void FMSTAT_Fail(void)
{
    asm(" EMUSTOP0");
    for (;;);
}

//******************************************************************************
// For this example, just stop here if ECC fail occurs
//******************************************************************************
void ECC_Fail(void)
{
    asm(" EMUSTOP0");
    for (;;);
}

//
// End of File
//
