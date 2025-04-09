//###########################################################################
//
// FILE:    flash_mode2_128_program_cpu1_cpu3x1.c
//
// TITLE:   Flash Bank Mode 2 128-bit programming Example for CPU1
//! <h1> Flash Bank Mode 2 128-bit programming Example for CPU1 </h1>
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
Fapi_FOTAStatus  FOTAStatus = Active_Bank;
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
void Example_ProgramUsingC29AutoECC(void);
void Example_ProgramUsingDataAndECC(void);
void Example_ProgramUsingDataOnlyECCOnly(void);
void Example_ProgramDataFlashUsingC29AutoECC(void);
void ClearFSMStatus(uint32_t u32StartAddress, uint32_t u32UserFlashConfig);

//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();
    Flash_initModule(3);

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
    // Request semaphore for CPU1
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
    oReturnCheck = Fapi_SetFlashCPUConfiguration(Mode2);
    
    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error(oReturnCheck);
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
    // Bring CPU3 out of reset
    //

    //
    // Defines the address and link to which CPU3 Boots
    //
    #ifdef _FLASH
    SSU_configBootAddress(SSU_CPU3, (uint32_t)0x10401000, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU3, (uint32_t)0x10401040, SSU_LINK2);
    #else
    SSU_configBootAddress(SSU_CPU3, (uint32_t)0x20110000, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU3, (uint32_t)0x20110040, SSU_LINK2);
    #endif
    
    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU3, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU3Reset() == 0x1U);

    //
    // CPU3 is out of reset now. Connect to CPU3
    //

    ESTOP0;

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

    IPC_sync(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG31);

    //
    // Finish the program on CPU1
    //
    Example_Done();
}

void Example_CallFlashAPI(void)
{
    //
    // Fill the flash buffer with a series of increasing integers
    //
    for (uint32_t i = 0 ; i < WORDS_IN_FLASH_BUFFER; i++)
    {
        Buffer[i] = i;
    }
    
    //
    // Assign 32-indexed buffer for ECC computation
    //
    Buffer32 = (uint32_t*) Buffer;
    
    //
    // Erase flash banks before we start
    //
    Example_EraseBanks();

    //
    // Program first 0x200 bytes of FR1RP1 (at 0x10100000) using AutoECC option
    //
    Example_ProgramUsingC29AutoECC();

    //
    // Erase sector
    //
    Example_EraseSector();

    //
    // Program first 0x200 bytes of FR1RP1 (at 0x10100000) using DataAndEcc option
    //
    Example_ProgramUsingDataAndECC();

    //
    // Erase sector
    //
    Example_EraseSector();

    //
    // Program first 0x200 bytes of FR1RP1 (at 0x10100000) using DataOnly and EccOnly options
    //
    Example_ProgramUsingDataOnlyECCOnly();

    //
    // Program first 0x200 bytes of FR4RP0 (at 0x10C00000) using AutoECC option
    //
    Example_ProgramDataFlashUsingC29AutoECC();

    //
    // Erase flash for clean exit
    //
    Example_EraseBanks();
}

//*****************************************************************************
//  Example_ProgramUsingC29AutoECC
//
//  Example function to Program data in Flash using "AutoEccGeneration" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
void Example_ProgramUsingC29AutoECC(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Issue program command for Mode 2 main array data bank FR1RP1
    //
    for (uint32_t u32CurrentAddress = C29FlashBankFR1RP1StartAddress;
         u32CurrentAddress < C29FlashBankFR1RP1EndAddressPlus1;
         u32CurrentAddress += FlashC29BankOffset)
    {

        //
        // Program 0x200 words to given bank
        //
        for (uint32_t i = 0, u32Index = u32CurrentAddress;
             u32Index < (u32CurrentAddress + WORDS_IN_FLASH_BUFFER);
             i += 16, u32Index += 16)
        {

            ClearFSMStatus(u32Index, u32UserFlashConfig);

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *)u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);  
            Fapi_setupBankSectorEnable((uint32_t *)u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);


            oReturnCheck = Fapi_issueProgrammingCommand((uint32_t *) u32Index, Buffer + i,
                                                        16, 0, 0, Fapi_AutoEccGeneration,
                                                        u32UserFlashConfig);

            //
            // Wait until the Flash program operation is over
            //
            while (Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

            if (oReturnCheck != Fapi_Status_Success)
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
            if (oFlashStatus != 3)
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
                                         4, (uint32_t *) (Buffer + i),
                                         &oFlashStatusWord, 0, u32UserFlashConfig);

            if (oReturnCheck != Fapi_Status_Success)
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
//  Example_ProgramUsingDataAndECC
//
//  Example function to Program data in Flash using "DataAndEcc" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
void Example_ProgramUsingDataAndECC(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Issue program command for Mode 2 main array data bank FR1RP1
    //
    for (uint32_t u32CurrentAddress = C29FlashBankFR1RP1StartAddress;
         u32CurrentAddress < C29FlashBankFR1RP1EndAddressPlus1;
         u32CurrentAddress += FlashC29BankOffset)
    {
        //
        // Program 0x200 words to given bank
        //
        for (uint32_t i = 0, u32Index = u32CurrentAddress;
             u32Index < (u32CurrentAddress + WORDS_IN_FLASH_BUFFER);
             i += 16, u32Index += 16)
        {
            ClearFSMStatus(u32Index, u32UserFlashConfig);

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

            //
            // Point LData to the lower 64 bit data
            // and   HData to the higher 64 bit data
            //
            uint64_t *LData = (uint64_t *) (Buffer32 + i/4);
            uint64_t *HData = (uint64_t *) (Buffer32 + i/4 + 2);

            //
            // Calculate ECC for lower 64 bit and higher 64 bit data
            //
            uint32_t ECC_LB = Fapi_calculateEcc((uint32_t *)u32Index, LData, 0);
            uint32_t ECC_HB = Fapi_calculateEcc((uint32_t *)(u32Index+8), HData, 0);
            uint32_t ECC_B = ((ECC_HB<<8) | ECC_LB);

            oReturnCheck = Fapi_issueProgrammingCommand((uint32_t *) u32Index, Buffer + i,
                                                        16, (uint8_t *) &ECC_B, 2, Fapi_DataAndEcc,
                                                        u32UserFlashConfig);

            //
            // Wait until the Flash program operation is over
            //
            while (Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

            if (oReturnCheck != Fapi_Status_Success)
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
            if (oFlashStatus != 3)
            {
                //
                // Check FMSTAT and debug accordingly
                //
                FMSTAT_Fail();
            }

            //
            // Verify the programmed values.  Check for any ECC errors.
            //
            oReturnCheck = Fapi_doVerify((uint32_t *) u32Index, 4, (uint32_t *) (Buffer + i),
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
//  Example_ProgramUsingDataOnlyECCOnly
//
//  Example function to Program data in Flash using "DataOnly" option and ECC
//  using "EccOnly" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
void Example_ProgramUsingDataOnlyECCOnly(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Issue program command for Mode 2 main array data bank FR1RP1
    //
    for (uint32_t u32CurrentAddress = C29FlashBankFR1RP1StartAddress;
         u32CurrentAddress < C29FlashBankFR1RP1EndAddressPlus1;
         u32CurrentAddress += FlashC29BankOffset)
    {
        //
        // Program 0x200 words to given bank
        //
        for (uint32_t i = 0, u32Index = u32CurrentAddress;
             u32Index < (u32CurrentAddress + WORDS_IN_FLASH_BUFFER);
             i += 16, u32Index += 16)
        {
            ClearFSMStatus(u32Index, u32UserFlashConfig);

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

            //
            // Point LData to the lower 64 bit data
            // and   HData to the higher 64 bit data
            //
            uint64_t *LData = (uint64_t *) (Buffer32 + i/4);
            uint64_t *HData = (uint64_t *) (Buffer32 + i/4 + 2);

            //
            // Calculate ECC for lower 64 bit and higher 64 bit data
            //
            uint32_t ECC_LB = Fapi_calculateEcc((uint32_t *) u32Index, LData, 0);
            uint32_t ECC_HB = Fapi_calculateEcc((uint32_t *) (u32Index+8), HData, 0);
            uint32_t ECC_B = ((ECC_HB<<8) | ECC_LB);

            oReturnCheck = Fapi_issueProgrammingCommand((uint32_t *) u32Index, Buffer + i,
                                                        16, 0, 0, Fapi_DataOnly, u32UserFlashConfig);

            //
            // Wait until the Flash program operation is over
            //
            while (Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

            if (oReturnCheck != Fapi_Status_Success)
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
            if (oFlashStatus != 3)
            {
                //
                // Check FMSTAT and debug accordingly
                //
                FMSTAT_Fail();
            }

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

            oReturnCheck = Fapi_issueProgrammingCommand((uint32_t *) u32Index, 0, 0,
                                                        (uint8_t *) &ECC_B, 2, Fapi_EccOnly, u32UserFlashConfig);

            //
            // Wait until the Flash program operation is over
            //
            while (Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

            if (oReturnCheck != Fapi_Status_Success)
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
            if (oFlashStatus != 3)
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
                                         4, (uint32_t *) (Buffer + i),
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
//  Example_ProgramDataFlashUsingC29AutoECC
//
//  Example function to Program data in Flash using "AutoEccGeneration" option.
//  Flash API functions used in this function are executed from RAM in this
//  example.
//*****************************************************************************
void Example_ProgramDataFlashUsingC29AutoECC(void)
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;

    //
    // Issue program command for Mode 2 main array data bank FR4RP0
    //
    for (uint32_t u32CurrentAddress = C29FlashBankFR4RP0StartAddress;
         u32CurrentAddress < C29FlashBankFR4RP0EndAddressPlus1;
         u32CurrentAddress += FlashC29BankOffset)
    {

        //
        // Program 0x200 words to given bank
        //
        for (uint32_t i = 0, u32Index = u32CurrentAddress;
             u32Index < (u32CurrentAddress + WORDS_IN_FLASH_BUFFER);
             i += 16, u32Index += 16)
        {

            ClearFSMStatus(u32Index, u32UserFlashConfig);

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t *) u32Index, u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

            oReturnCheck = Fapi_issueProgrammingCommand((uint32_t *)u32Index,Buffer+i,
                                                        16, 0, 0, Fapi_AutoEccGeneration,
                                                        u32UserFlashConfig);

            //
            // Wait until the Flash program operation is over
            //
            while (Fapi_checkFsmForReady(u32Index, u32UserFlashConfig) == Fapi_Status_FsmBusy);

            if (oReturnCheck != Fapi_Status_Success)
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
            if (oFlashStatus != 3)
            {
                //
                // Check FMSTAT and debug accordingly
                //
                FMSTAT_Fail();
            }

            //
            // Verify the programmed values. Check for any ECC errors.
            //
            oReturnCheck = Fapi_doVerify((uint32_t *)u32Index,
                                         4, (uint32_t *) (Buffer + i),
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
    // Issue Bank erase command
    //
    for (uint32_t u32CurrentAddress = C29FlashBankFR1RP1StartAddress;
         u32CurrentAddress < C29FlashBankFR1RP1EndAddressPlus1;
         u32CurrentAddress +=FlashC29BankOffset)
    {
        //
        // Loop for erasing 1 interleaved bank
        //
        for (uint32_t u8Iterator = 1; u8Iterator <= 2; u8Iterator++)
        {
            ClearFSMStatus(u32CurrentAddress, u32UserFlashConfig);

            //
            // Set program/erase protection
            //
            Fapi_setupBankSectorEnable((uint32_t *)(u32CurrentAddress), u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t *)(u32CurrentAddress), u32UserFlashConfig,
                                        FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

            //
            // Set program/erase protection
            //
            oReturnCheck = Fapi_issueBankEraseCommand((uint32_t *)(u32CurrentAddress), u8Iterator, u32UserFlashConfig);

            //
            // Wait until FSM is done with erase operation
            //
            while (Fapi_checkFsmForReady(u32CurrentAddress, u32UserFlashConfig) != Fapi_Status_FsmReady) {}

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
        // Perform a blank check to ensure all sectors are erased
        //
        oReturnCheck = Fapi_doBlankCheck((uint32_t *)u32CurrentAddress,
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
    Fapi_setupBankSectorEnable((uint32_t *)(C29FlashBankFR4RP0StartAddress), u32UserFlashConfig,
                                FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
    Fapi_setupBankSectorEnable((uint32_t *)(C29FlashBankFR4RP0StartAddress), u32UserFlashConfig,
                                FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

    //
    // Issue bank erase command
    //
    oReturnCheck = Fapi_issueBankEraseCommand((uint32_t *)(C29FlashBankFR4RP0StartAddress),
                                              0, u32UserFlashConfig);

    //
    // Wait until FSM is done with erase operation
    //
    while (Fapi_checkFsmForReady(C29FlashBankFR4RP0StartAddress, u32UserFlashConfig) != Fapi_Status_FsmReady) {}

    if (oReturnCheck != Fapi_Status_Success)
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
    // Perform a blank check to ensure all sectors are erased
    //
    oReturnCheck = Fapi_doBlankCheck((uint32_t *)C29FlashBankFR4RP0StartAddress,
                                     (128*Sector2KB_u32length),
                                     &oFlashStatusWord, 0, u32UserFlashConfig);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for error info
        //
        Example_Error(oReturnCheck);
    }
}

//**************************************************************************************
//  ClearFSMStatus
//
//  This function clears the status (STATCMD, similar to FMSTAT of the previous
//  devices) of the previous flash operation.
//  This function and the flash API functions used in this function are
//  executed from RAM in this example.
//  Note: this function is applicable for only F280013X, F280015X and F28P65X devices
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
    for(uint32_t u32CurrentAddress = C29FlashBankFR1RP1StartAddress;
        u32CurrentAddress < C29FlashBankFR1RP1EndAddressPlus1;
        u32CurrentAddress += FlashC29BankOffset)
    {
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
            // Erase sector
            //
            oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                                                             (uint32_t *) (u32CurrentAddress), u8Iterator, 
                                                             u32UserFlashConfig);

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

void Example_Done(void)
{
    asm(" EMUSTOP0");
    for (;;);
}

void Example_Error(Fapi_StatusType status)
{
    //
    //  Error code will be in the status parameter
    //
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
