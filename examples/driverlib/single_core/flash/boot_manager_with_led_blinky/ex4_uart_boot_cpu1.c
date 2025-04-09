//###########################################################################
//
// FILE:    ex4_uart_boot_cpu1.c
//
// TITLE:   UART Boot mode functions
//! <h1> UART Boot mode functions </h1>
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################
// #include "FlashTech.h"
// #include "Types.h"
#include "bootrom.h"
#include "ex4_cpubrom.h"
#include "ex4_cpubrom_bootload.h"
#include "flash_programming_F29H85x_C29.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "ssu.h"
#include <string.h>
#include <ex4_uart_boot_cpu1.h>



//
// UART Main Boot
//
void uartDFU(uint8_t targetCPU, Fapi_BankMode bankMode, uint32_t bootMode, uint32_t LoadAddr, uint32_t ImageSize, uint8_t currentState)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t loop;
    uint32_t Available_Flash = 0;
    uint32_t Size_Check = 0;
    bool flashSemaphore;
    //
    // FAPI parameters
    //
    Fapi_FlashBankType BankType = C29Bank;
    Fapi_FOTAStatus FOTAStatus = FOTA_Image;
    uint32_t u32UserFlashConfig = 0;
    Fapi_StatusType oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    oReturnCheck = Fapi_Status_Success;
    oFlashStatus = 3;
    Fapi_BankMode fapi_bankmode;
    
    //
    // Set bank mode enum
    //
    if (bankMode == 0x6) 
    {

        fapi_bankmode = Mode1;

    } else if (bankMode == 0xC) 
    {

        fapi_bankmode = Mode3;
        
    }

    // Set configuration as per user request
    u32UserFlashConfig = Fapi_getUserConfiguration(BankType, FOTAStatus);

    Fapi_SetFlashCPUConfiguration(fapi_bankmode);

    // Release flash semaphore
    SSU_releaseFlashSemaphore();

    // Request semaphore for CPU1
    flashSemaphore = SSU_claimFlashSemaphore();

    if (!flashSemaphore) 
    {
        Example_Error();
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

    //
    // Set image size, uart read callback function, and address of certificate
    //
    blCtx.maxImageSize  = FLASH_IMAGE_SIZE;
    blCtx.readDataCb    = &uartRead;
    blCtx.certAddr      = LDA7_RAM_BASE;

#ifdef BANKMODE1
    blCtx.imageAddr     = 0x10000000 + MAX_CERT_SIZE;
    EraseBanks(C29FlashBankFR1RP0StartAddress, u32UserFlashConfig);
    EraseBanks(C29FlashBankFR1RP1StartAddress, u32UserFlashConfig);
#else
    if (targetCPU ==3) 
    {
        blCtx.imageAddr     = 0x10400000 + MAX_CERT_SIZE;
        EraseBanks(C29FlashBankFR2RP0StartAddress, u32UserFlashConfig);
    } else 
    {
        blCtx.imageAddr     = 0x10000000 + MAX_CERT_SIZE;
        EraseBanks(C29FlashBankFR1RP0StartAddress, u32UserFlashConfig);
    }
#endif
   
    //
    // Enable Sysclk and wait for 20U cycles
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
    CPU_BROM_delay_cycles(20U);

    //
    // Boot Loader Init
    //
    status = bootloadInit();

    if (status == BROM_STATUS_OK)
    {
        for (loop = 0U; loop < UART_MAX_BOOT_RETRY; ++loop)
        {


            if (status == BROM_STATUS_OK)
            {
                uint32_t test;
                //
                // Boot loader Process, returns image size
                //
                ImageSize = bootloadProcess(&blCtx);

                if ((ImageSize != 0) && (ImageSize < FLASH_IMAGE_SIZE))
                {

                    //
                    // If HS_FS, program the incoming application
                    //
                    if (currentState == HS_FS) 
                    {
                        //
                        // Boot load is successful, now exit LINK1 and copy the image to Flash memory
                        //
                        CopyApplication(bankMode, blCtx.imageAddr, ImageSize);
                    }

                } else
                {
                    Example_Error();
                }
            }
        }

    } else
    {
        Example_Error();
    }
    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    if (g_bootLoadStatus.deInit != STATUS_PASS)
    {
        Example_Error();
    }

    //
    // Now that application is programmed to flash, need to call PROC_AUTH_BOOT to authenticate the firmware
    // ONLY CALL THIS IF IN HS-SE STATE
    //
    if (currentState == HS_SE) 
    {
        uint8_t authStatus = 0;
        if (authStatus) 
        {
            Example_Error();
        } 
    }


    //
    // Now program cert to flash
    //
    uint32_t i, j;
    uint8_t certBuffer[16] = {0};
    uint32_t certOffset = 0;
    uint8_t * certPointer;
    uint32_t certProgramAddr = C29FlashBankFR1RP0StartAddress; 

    //
    // FAPI parameters
    //
    oReturnCheck = Fapi_Status_Success;
    oFlashStatus = 3;

    //
    // Set target address based on target CPU
    //
    if (targetCPU == 3) 
    {

        certProgramAddr = C29FlashBankFR2RP0StartAddress;
        
    }
    

    for (i = 0; i < (MAX_CERT_SIZE / 16); i++) 
    {
        //
        // Read cert into buffer
        //
        for (j = 0; j < 16; j++) 
        {
            certPointer = (uint8_t*) (blCtx.certAddr + certOffset + j);
            certBuffer[j] = *certPointer;
        }



        // Set configuration as per user request
        u32UserFlashConfig = Fapi_getUserConfiguration(BankType,
                                                    FOTAStatus);


        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }

        ClearFSMStatus(certProgramAddr + certOffset, u32UserFlashConfig);

        // Enable program/erase protection for select sectors where this example is
        // located CMDWEPROTA, CMDWEPROTB
        Fapi_setupBankSectorEnable((uint32_t*)(certProgramAddr + certOffset), u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
        Fapi_setupBankSectorEnable((uint32_t*)(certProgramAddr + certOffset), u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);


        oReturnCheck = Fapi_issueProgrammingCommand((uint32_t*)(certProgramAddr + certOffset), certBuffer,
                                        16, 0, 0, Fapi_AutoEccGeneration, u32UserFlashConfig);


        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady(certProgramAddr + certOffset, u32UserFlashConfig) == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related
        // errors
        //
        oFlashStatus = Fapi_getFsmStatus(certProgramAddr + certOffset, u32UserFlashConfig);
        if(oFlashStatus != 3)
        {
            //
            //Check FMSTAT and debug accordingly
            //
            Example_Error();
        }

        //
        // Verify the programmed values.  Check for any ECC errors.
        //
        oReturnCheck = Fapi_doVerify((uint32_t*)(certProgramAddr + certOffset), 4, (uint32_t*)(certBuffer), &oFlashStatusWord, 0, u32UserFlashConfig);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        } {
            certOffset += 16;
        }
    
    }
    
    //
    // New firmware has been successfully loaded, now we need to swap banks and reset
    //
    ProgramInactiveBankManagement(targetCPU, bankMode, u32UserFlashConfig);

    //
    // Program the current bankMode
    //
    ProgramBankModeToDataFlash(bankMode, u32UserFlashConfig);

    flashSemaphore = SSU_releaseFlashSemaphore();

    if (!flashSemaphore) 
    {
        Example_Error();
    }


    // Let WD timer run out and trigger a reset
    //SysCtl_enableWatchdog();
}

void ProgramBankModeToDataFlash(uint8_t bankMode, uint32_t u32UserFlashConfig) 
{

    Fapi_StatusType oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType oFlashStatusWord;
    uint32_t u32CurrentAddress = C29FlashBankFR4RP0StartAddress;

    uint8_t bankModeBuffer[16] = {bankMode};

    //
    // Enable program/erase protection for select sectors
    //
    Fapi_setupBankSectorEnable((uint32_t*) u32CurrentAddress, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, 0);
    Fapi_setupBankSectorEnable((uint32_t*) u32CurrentAddress, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, 0);

    //
    // Erase the flash bank
    //
    oReturnCheck = Fapi_issueBankEraseCommand((uint32_t*) u32CurrentAddress, 0, u32UserFlashConfig);

    //
    // Wait for completion and check for any programming errors
    //
    while(Fapi_checkFsmForReady((uint32_t) u32CurrentAddress, u32UserFlashConfig) == Fapi_Status_FsmBusy);

    if (oReturnCheck != Fapi_Status_Success) 
    {
        Example_Error();
    }

    oFlashStatus = Fapi_getFsmStatus((uint32_t) u32CurrentAddress, u32UserFlashConfig);

    if (oFlashStatus != 3)
    {
        Example_Error();
    }


    //
    // Clear the status of the previous Flash operation
    //
    ClearFSMStatus(u32CurrentAddress, u32UserFlashConfig);

    //
    // Enable program/erase protection for select sectors
    //
    Fapi_setupBankSectorEnable((uint32_t*) u32CurrentAddress, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, 0);
    Fapi_setupBankSectorEnable((uint32_t*) u32CurrentAddress, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, 0);


    oReturnCheck = Fapi_issueProgrammingCommand((uint32_t*)u32CurrentAddress, bankModeBuffer,
                                        16, 0, 0, Fapi_AutoEccGeneration, u32UserFlashConfig);

    //
    // Wait until the Flash program operation is over
    //
    while(Fapi_checkFsmForReady(u32CurrentAddress, u32UserFlashConfig) == Fapi_Status_FsmBusy);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }

    //
    // Read FMSTAT register contents to know the status of FSM after
    // program command to see if there are any program operation related
    // errors
    //
    oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, u32UserFlashConfig);
    if(oFlashStatus != 3)
    {
        //
        //Check FMSTAT and debug accordingly
        //
        Example_Error();
    }


    //
    // Verify the programmed values.  Check for any ECC errors.
    //
    oReturnCheck = Fapi_doVerify((uint32_t*)u32CurrentAddress,
                                    4, (uint32_t*)(uint32_t)(bankModeBuffer),
                                    &oFlashStatusWord, 0, u32UserFlashConfig);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }

}


//
//  bootloadInit
//
uint32_t bootloadInit()
{

    uint32_t       status = BROM_STATUS_OK;

    //
    //  Cert init
    //
    (void)Cert_init();
    //
    //  Init status
    //
    g_bootLoadStatus.init = STATUS_PASS;

    if(BROM_STATUS_OK == status)
    {
        g_bootLoadStatus.helloMsg = STATUS_PASS;
    }
    else
    {
        g_bootLoadStatus.helloMsg = STATUS_FAIL;
    }

    return status;
}

//
//  bootloadDeInit
//
void bootloadDeInit(void)
{
    (void)Cert_close();

    g_bootLoadStatus.deInit = STATUS_PASS;
}

//
// Read Callback Function.
//
uint32_t uartRead(uint32_t addr, uint32_t size)
{
    uint32_t cnt;
    uint32_t rData;
    uint32_t status = BROM_STATUS_OK;

    for (cnt = 0U; cnt < size; cnt++)
    {
        //
        //  Read UART data
        //
        rData = UART_readChar(UARTA_BASE);
        //
        //  Write UART data to unblock the next send
        //
        UART_writeCharNonBlocking(UARTA_BASE, rData);
        //
        // Write data to the destination address
        //
        HWREGB(addr + cnt) = (uint8_t)((rData) & 0xFFU);
    }
    return (status);
}

//
// CopyApplication - This function will copy application from LDAx RAM to the Flash entry address
//
void CopyApplication(uint8_t targetCPU, uint32_t LoadAddr, uint32_t ImageSize)
{

    // Declare/initialize locals
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    uint16_t wordData;
    uint32_t i, j;
    uint32_t currentAddr = LoadAddr;
    uint32_t bytesWritten = 0;
    uint8_t Buffer[FLASH_BUFFER_SIZE] = {0};
    uint32_t InactiveBank;

#ifdef BANKMODE1
    InactiveBank     = 0x10000000;
#else
    if (targetCPU == 3) 
    {
        InactiveBank     = 0x10400000;
    } else 
    {
        InactiveBank     = 0x10000000;
    }
#endif

//
    // Calculate the loop limits and if image size is even multiple
    // of buffer size
    //
    uint16_t bytesRemaining = ImageSize % FLASH_BUFFER_SIZE;
    uint32_t numBuffers = ImageSize / FLASH_BUFFER_SIZE;


    //
    // FAPI parameters
    //
    Fapi_FlashBankType BankType = C29Bank;
    Fapi_FOTAStatus  FOTAStatus = FOTA_Image;
    uint32_t u32UserFlashConfig = 0;
    oReturnCheck = Fapi_Status_Success;
    oFlashStatus = 3;

    // Set configuration as per user request
    u32UserFlashConfig = Fapi_getUserConfiguration(BankType,
                                                   FOTAStatus);

    // Set CPU Flash configuration based on user inputs
    Fapi_SetFlashCPUConfiguration(u32UserFlashConfig);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }

    // Write 128 bits of application to flash until the end of the image is reached.
    // Make sure that the remaining data will fill up the buffer
    for (i = 0; i < numBuffers; i++)
    {

        // Load up the buffer with 128 bits of the application
        for (j = 0; j < FLASH_BUFFER_SIZE; j++)
        {
            wordData = uartGetData();
            Buffer[j] = wordData;

        }

        ClearFSMStatus(currentAddr, u32UserFlashConfig);

        // Enable program/erase protection for select sectors where this example is
        // located CMDWEPROTA, CMDWEPROTB
        Fapi_setupBankSectorEnable((uint32_t*)currentAddr, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
        Fapi_setupBankSectorEnable((uint32_t*)currentAddr, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);

        oReturnCheck = Fapi_issueProgrammingCommand((uint32_t *)currentAddr,Buffer,
                                        16, 0, 0, Fapi_AutoEccGeneration, u32UserFlashConfig);


        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady(currentAddr, u32UserFlashConfig) == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related
        // errors
        //
        oFlashStatus = Fapi_getFsmStatus(currentAddr, u32UserFlashConfig);
        if(oFlashStatus != 3)
        {
            //
            //Check FMSTAT and debug accordingly
            //
            Example_Error();
        }

        //
        // Verify the programmed values.  Check for any ECC errors.
        //
        oReturnCheck = Fapi_doVerify((uint32_t*)currentAddr,
                                     4, (uint32_t*)(Buffer),
                                     &oFlashStatusWord, 1, u32UserFlashConfig);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }

        // Increment the current address and number of bytes written
        currentAddr += FLASH_BUFFER_SIZE;
        bytesWritten += FLASH_BUFFER_SIZE;

    }

    // Once there is less than one full buffer left in the image, we need to
    // fill up the buffer with the remaining data and then fill with 0xFF
    // Will use 128 bit programming for this
    if (bytesRemaining)
    {
        while (bytesWritten < ImageSize)
        {

            //
            // Load up the buffer with remaining bits of the application
            //
            for (i = 0; i < bytesRemaining; i++)
            {
                wordData = uartGetData();
                Buffer[i] = wordData;
            }

            //
            // Fill remaining buffer with 1s
            //
            for (i = bytesRemaining; i < FLASH_BUFFER_SIZE; i++)
            {
                Buffer[i] = 0xFF;
            }
            

            ClearFSMStatus(currentAddr, u32UserFlashConfig);

            // Enable program/erase protection for select sectors where this example is
            // located CMDWEPROTA, CMDWEPROTB
            Fapi_setupBankSectorEnable((uint32_t*)currentAddr, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
            Fapi_setupBankSectorEnable((uint32_t*)currentAddr, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);


            oReturnCheck = Fapi_issueProgrammingCommand((uint32_t*)currentAddr, Buffer,
                                              16, 0, 0, Fapi_AutoEccGeneration, u32UserFlashConfig);

            //
            // Wait until the Flash program operation is over
            //
            while(Fapi_checkFsmForReady(currentAddr, u32UserFlashConfig) == Fapi_Status_FsmBusy);

            if(oReturnCheck != Fapi_Status_Success)
            {
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error();
            }

            //
            // Read FMSTAT register contents to know the status of FSM after
            // program command to see if there are any program operation related
            // errors
            //
            oFlashStatus = Fapi_getFsmStatus(currentAddr, u32UserFlashConfig);
            if(oFlashStatus != 3)
            {
                //
                //Check FMSTAT and debug accordingly
                //
                Example_Error();
            }


            //
            // Verify the programmed values.  Check for any ECC errors.
            //
            oReturnCheck = Fapi_doVerify((uint32_t*)currentAddr,
                                         4, (uint32_t*)(uint32_t)(Buffer),
                                         &oFlashStatusWord, 0, u32UserFlashConfig);

            if(oReturnCheck != Fapi_Status_Success)
            {
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error();
            }

            currentAddr += bytesRemaining;
            bytesWritten += bytesRemaining;

        }

    }

    // If there is a discrepancy between the number of bytes written and the
    // size of the image, something has gone wrong
    if (bytesWritten != ImageSize)
    {
        Example_Error();
    }

}

//******************************************************************************
// For this example, just stop here if an error is found
//******************************************************************************
void Example_Error()
{
    //
    //  Error code will be in the status parameter
    //
    asm(" EMUSTOP0");
    for (;;);
}

//**************************************************************************************
//  ClearFSMStatus
//
//  This function clears the status (STATCMD, similar to FMSTAT of the previous
//  devices) of the previous flash operation.
//  This function and the flash API functions used in this function are
//  executed from RAM in this example.
//**************************************************************************************
__attribute__((section(".TI.ramfunc")))
void ClearFSMStatus(uint32_t u32StartAddress, uint32_t u32UserFlashConfig){
    //
    // FAPI parameters
    //
    Fapi_FlashBankType BankType = C29Bank;
    Fapi_FOTAStatus  FOTAStatus = FOTA_Image;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_StatusType  oReturnCheck;

    //
    // Wait until FSM is done with the previous flash operation
    //
    while (Fapi_checkFsmForReady(u32StartAddress, u32UserFlashConfig) != Fapi_Status_FsmReady){}
    oFlashStatus = Fapi_getFsmStatus(u32StartAddress, u32UserFlashConfig);


    /* Clear the Status register */
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
        Example_Error();
    }

}

//*****************************************************************************
//  EraseBanks
//
//  Erase data of banks in flash.
//  Flash API functions used in this function are executed from RAM
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc")))
void EraseBanks(uint32_t u32StartAddress, uint32_t FlashConfig)
{

    //
    // FAPI parameters
    //
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    uint32_t u32CurrentAddress = u32StartAddress;
    uint8_t  u8Iterator = 0;
        
    //loop for erasing 1 interleaved bank
    for(u8Iterator = 1; u8Iterator <= 2; u8Iterator++)
    {
        ClearFSMStatus(u32CurrentAddress, FlashConfig);

        // Enable program/erase protection for select sectors where this example is
        // located  CMDWEPROTA, CMDWEPROTB
        Fapi_setupBankSectorEnable((uint32_t *)(u32CurrentAddress), FlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
        Fapi_setupBankSectorEnable((uint32_t *)(u32CurrentAddress), FlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);


        //Issue bank erase command
        oReturnCheck = Fapi_issueBankEraseCommand((uint32_t *)(u32CurrentAddress), u8Iterator , FlashConfig);


        // Wait until FSM is done with erase operation
        while (Fapi_checkFsmForReady(u32CurrentAddress, FlashConfig) != Fapi_Status_FsmReady){}

        if(oReturnCheck != Fapi_Status_Success)
        {
            // Check Flash API documentation for possible errors
            Example_Error();
        }

        // Read FMSTAT register contents to know the status of FSM after
        // erase command to see if there are any erase operation related errors
        oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, FlashConfig);
        if(oFlashStatus != 3)
        {
            // Check Flash API documentation for FMSTAT and debug accordingly
            // Fapi_getFsmStatus() function gives the FMSTAT register contents.
            // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
            // VOLTSTAT bit is set (Refer to API documentation for more details).
            Example_Error();
        }

    }

    // Do blank check
    // Blank check is performed on all the sectors that are not protected
    // during Bank erase
    // Verify that Bank 0 is erased.
    // The Erase command itself does a verify as it goes.
    // Hence erase verify by CPU reads (Fapi_doBlankCheck()) is optional.
    oReturnCheck = Fapi_doBlankCheck((uint32_t *)u32CurrentAddress,
                (128*Sector2KB_u32length),
                    &oFlashStatusWord, 0 , FlashConfig);


    if(oReturnCheck != Fapi_Status_Success)
    {
        // Check Flash API documentation for error info
        Example_Error();
    }

}

//
// This function programs the inactive regions bank management with a specific bank mode.
// After programming bank mode 1 or 3 to the inactive region, bank swapping will be enabled after reset.
//
void ProgramInactiveBankManagement(uint8_t targetCPU, uint8_t bankMode, uint32_t flashConfig)
{
    //
    // FAPI parameters
    //
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    uint32_t u32CurrentAddress = FlashFR1_Mode1RP0BankmgmtStartAddress;
    uint8_t  u8Iterator = 0;


    if ((bankMode == Mode3) && (targetCPU == 3)) 
    {
        u32CurrentAddress = FlashFR2_Mode3RP0BankmgmtStartAddress;
    }
    //
    // loop for erasing the existing bankmgmt values
    //
    for(u8Iterator = 1; u8Iterator <= 2; u8Iterator++)
    {
        ClearFSMStatus(u32CurrentAddress, flashConfig);

        // Enable program/erase protection for select sectors where this example is
        // located  CMDWEPROTA, CMDWEPROTB
        Fapi_setupBankSectorEnable((uint32_t *)(u32CurrentAddress), flashConfig, FLASH_NOWRAPPER_O_CMDWEPROTNM, 0x00000000);

        //Issue bank erase command
        // oReturnCheck = Fapi_issueBankEraseCommand((uint32_t *)(u32CurrentAddress), u8Iterator , flashConfig);
        oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector, (uint32_t *)(u32CurrentAddress), u8Iterator, flashConfig);

        //
        // Add short delay so there are no SSU errors
        //
        DEVICE_DELAY_US(100000);
        
        // Wait until FSM is done with erase operation
        while (Fapi_checkFsmForReady(u32CurrentAddress, flashConfig) != Fapi_Status_FsmReady){}

        if(oReturnCheck != Fapi_Status_Success)
        {
            // Check Flash API documentation for possible errors
            Example_Error();
        }

        // Read FMSTAT register contents to know the status of FSM after
        // erase command to see if there are any erase operation related errors
        oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, flashConfig);
        if(oFlashStatus != 3)
        {
            // Check Flash API documentation for FMSTAT and debug accordingly
            // Fapi_getFsmStatus() function gives the FMSTAT register contents.
            // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
            // VOLTSTAT bit is set (Refer to API documentation for more details).
            Example_Error();
        }

    }

    // Do blank check
    // Blank check is performed on all the sectors that are not protected
    // during Bank erase
    // Verify that Bank 0 is erased.
    // The Erase command itself does a verify as it goes.
    // Hence erase verify by CPU reads (Fapi_doBlankCheck()) is optional.
    oReturnCheck = Fapi_doBlankCheck((uint32_t *)u32CurrentAddress,
                (2*Sector2KB_u32length), &oFlashStatusWord, 0 , flashConfig);


    if(oReturnCheck != Fapi_Status_Success)
    {
        // Check Flash API documentation for error info
        Example_Error();
    }

    //
    // Create buffer for data
    //
    uint8_t Buffer[16] = {0};
    uint8_t i;

    //
    // Only need to program bank mode for CPU1
    //
    if (targetCPU == 0x1U) 
    {
        //
        // Bank mode is offset by 0x10
        //
        u32CurrentAddress += 0x10;

        //
        // Fill first 64 bits of buffer with BANKMODE
        //
        Buffer[0] = bankMode;
        Buffer[1] = 0;
        Buffer[2] = 0;
        Buffer[3] = 0;
        Buffer[4] = 0;
        Buffer[5] = 0;
        Buffer[6] = 0;
        Buffer[7] = 0;

        //
        // Program BANKMODE
        //
        ClearFSMStatus(u32CurrentAddress, flashConfig);

        //
        // Disable W/E protection
        //
        Fapi_setupBankSectorEnable((uint32_t *)(u32CurrentAddress), flashConfig, FLASH_NOWRAPPER_O_CMDWEPROTNM, 0x00000000);


        oReturnCheck = Fapi_issueProgrammingCommand((uint32_t*)u32CurrentAddress, Buffer,
                                            8, 0, 0, Fapi_AutoEccGeneration, flashConfig);

        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady(u32CurrentAddress, flashConfig) == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related
        // errors
        //
        oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, flashConfig);
        if(oFlashStatus != 3)
        {
            //
            //Check FMSTAT and debug accordingly
            //
            Example_Error();
        }


        //
        // Verify the programmed values.  Check for any ECC errors.
        //
        oReturnCheck = Fapi_doVerify((uint32_t*)u32CurrentAddress,
                                        2, (uint32_t*)(uint32_t)(Buffer),
                                        &oFlashStatusWord, 0, flashConfig);

        if(oReturnCheck != Fapi_Status_Success)
        {
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }

        //
        // Move current address back to beginning of BANKMGMT regions
        //
        u32CurrentAddress -= 0x10;

    }

    //
    // Fill first 64 bits of buffer with BANK_STATUS
    //
    for (i = 0; i < 8; i++) 
    {
        Buffer[i] = 0x55;
    }
    //
    // Fill last 64 bits of buffer with 0 (FAPI will decrement bank update ctr)
    //
    for (i = 8; i < 16; i++) 
    {
        Buffer[i] = 0x0;
    }

    //
    // Program BANK_STATUS and BANK_UPDATE_CTR to bankmgmt region
    //
    ClearFSMStatus(u32CurrentAddress, flashConfig);

    //
    // Disable W/E protection
    //
    Fapi_setupBankSectorEnable((uint32_t *)(u32CurrentAddress), flashConfig, FLASH_NOWRAPPER_O_CMDWEPROTNM, 0x00000000);

    oReturnCheck = Fapi_issueProgrammingCommand((uint32_t*)u32CurrentAddress, Buffer,
                                        16, 0, 0, Fapi_AutoEccGeneration, flashConfig);

    //
    // Wait until the Flash program operation is over
    //
    while(Fapi_checkFsmForReady(u32CurrentAddress, flashConfig) == Fapi_Status_FsmBusy);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }

    //
    // Read FMSTAT register contents to know the status of FSM after
    // program command to see if there are any program operation related
    // errors
    //
    oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, flashConfig);
    if(oFlashStatus != 3)
    {
        //
        //Check FMSTAT and debug accordingly
        //
        Example_Error();
    }


    //
    // Verify the programmed values.  Check for any ECC errors.
    //
    oReturnCheck = Fapi_doVerify((uint32_t*)u32CurrentAddress,
                                    4, (uint32_t*)(uint32_t)(Buffer),
                                    &oFlashStatusWord, 0, flashConfig);

    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }



}


//
// End of file
//
