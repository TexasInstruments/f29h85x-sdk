//###########################################################################
//
// FILE:    uart_boot_cpu1.c
//
// TITLE:   UART Boot mode functions
//! <h1> UART Boot mode functions </h1>
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

#include "sbl_flash_programming.h"

//
// program DFU image to active flash banks - supports all Bankmodes (0,1,2,3)
// Note: DFU vs FOTA, DFU programs directly to the active banks (no A/B swap), whereas FOTA programs to dormant banks (w A/B swap) and mode 1&3 only.
//
void programDFU(uint8_t targetCPU, uint8_t bankMode)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t imageSize;

    blCtx.maxImageSize  = getMaxFlashImageSize();
    blCtx.readDataCb    = &insertUartData;
    blCtx.certAddr      = LDA1_RAM_BASE;

    //
    // FAPI parameters
    //
    Fapi_FlashBankType BankType = C29Bank;
    Fapi_FOTAStatus FOTAStatus = Active_Bank;
    Fapi_StatusType oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    uint32_t u32UserFlashConfig = 0;
    bool flashSemaphore;

    // Set configuration as per user request
    u32UserFlashConfig = Fapi_getUserConfiguration(BankType,
                                                   FOTAStatus);
    oReturnCheck = Fapi_SetFlashCPUConfiguration(bankMode);

/*
    if(oReturnCheck != Fapi_Status_Success)
    {
        uint32_t tmpVal = oReturnCheck;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1008,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                     
        };
        sblSendPacket(1, &errPkt);
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }
*/

    // Request semaphore for CPU1
    flashSemaphore = SSU_claimFlashSemaphore();

    if (!flashSemaphore) 
    {
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1001,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  // Semaphore reset requires a XRSn if unresettable by CPU1
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                      
        };
        sblSendPacket(1, &errPkt);

        Example_Error();
    }

    // Initialize the Flash API by providing the Flash register base address
    // and operating frequency(in MHz).
    // This function is required to initialize the Flash API based on System
    // frequency before any other Flash API operation can be performed.
    // This function must also be called whenever System frequency or RWAIT is
    // changed.
    //
    oReturnCheck = Fapi_initializeAPI((Fapi_FmcRegistersType *)FLASHCONTROLLER1_BASE,
                                      DEVICE_SYSCLK_FREQ / 1000000U); // 200 (Mhz)

    if (oReturnCheck != Fapi_Status_Success) 
    {
        uint32_t tmpVal = oReturnCheck;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x100D,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                      
        };
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    //
    // If Bank Mode 0, erase all of flash.
    // Else, only erase the target CPU flash
    //
    if (bankMode == FLASH_BANK_MODE_0) 
    {

        blCtx.imageAddr     = 0x10000000 + MAX_CERT_SIZE;
        EraseBanks(C29FlashBankFR1RP0StartAddress, u32UserFlashConfig);
        EraseBanks(C29FlashBankFR1RP1StartAddress, u32UserFlashConfig);
        EraseBanks(C29FlashBankFR1RP2StartAddress, u32UserFlashConfig);
        EraseBanks(C29FlashBankFR1RP3StartAddress, u32UserFlashConfig);
        
    }
    else if (bankMode == FLASH_BANK_MODE_1)
    {
        blCtx.imageAddr     = 0x10000000 + MAX_CERT_SIZE;
        EraseBanks(C29FlashBankFR1RP0StartAddress, u32UserFlashConfig);
        EraseBanks(C29FlashBankFR1RP1StartAddress, u32UserFlashConfig);
    } 
    else if (bankMode == FLASH_BANK_MODE_2) 
    {
        if (targetCPU == 3) 
        {
            blCtx.imageAddr = 0x10400000 + MAX_CERT_SIZE;
            EraseBanks(C29FlashBankFR2RP0StartAddress, u32UserFlashConfig);
            EraseBanks(C29FlashBankFR2RP1StartAddress, u32UserFlashConfig);

        } 
        else // targetCPU == 1
        {
            blCtx.imageAddr = 0x10000000 + MAX_CERT_SIZE;
            EraseBanks(C29FlashBankFR1RP0StartAddress, u32UserFlashConfig);
            EraseBanks(C29FlashBankFR1RP1StartAddress, u32UserFlashConfig);
        }
    }
    else if (bankMode == FLASH_BANK_MODE_3)
    {
        if (targetCPU == 3) 
        {
            blCtx.imageAddr     = 0x10400000 + MAX_CERT_SIZE;
            EraseBanks(C29FlashBankFR2RP0StartAddress, u32UserFlashConfig);
        } 
        else // targetCPU == 1 
        {
            blCtx.imageAddr     = 0x10000000 + MAX_CERT_SIZE;
            EraseBanks(C29FlashBankFR1RP0StartAddress, u32UserFlashConfig);
        }
    }
    else
    {
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x100E,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                      
        };
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    //
    // Boot Loader Init
    //
    bootloadInit();

    //
    // Boot loader Process, returns image size
    //
    imageSize = bootloadProcessWithChecks(&blCtx);
    
    //
    // Copy the image to Flash memory
    //
    CopyApplication(blCtx.imageAddr, imageSize, bankMode);


    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    //
    // Now program cert to flash
    //
    uint32_t i, j;
    uint8_t certBuffer[16] = {0};
    uint32_t certOffset = 0;
    uint8_t * certPointer;
    uint32_t certProgramAddr;

    //
    // Set target address based on target CPU
    //
    if (targetCPU == 3) 
    {
        certProgramAddr = C29FlashBankFR2RP0StartAddress;
    }
    else // targetCPU == 1
    {
        certProgramAddr = C29FlashBankFR1RP0StartAddress;
    }

    for (i = 0; i < (MAX_CERT_SIZE / 16U); i++) 
    {
        //
        // Read cert into buffer
        //
        for (j = 0; j < 16; j++) 
        {
            certPointer = (uint8_t*) (blCtx.certAddr + certOffset + j);
            certBuffer[j] = *certPointer;
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
            uint32_t tmpVal = oReturnCheck;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = &tmpVal                    
            };
            sblSendPacket(1, &errPkt);
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

        if(oFlashStatus != 0b11)
        {
            uint32_t tmpVal = oFlashStatus;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = &tmpVal                  
            };
            sblSendPacket(1, &errPkt);
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
            uint32_t tmpVal = oReturnCheck;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x100A,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = &tmpVal                
            };
            sblSendPacket(1, &errPkt);
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        } 

        certOffset += 16U;
    }

    //
    // Program the current bankMode
    //
    ProgramBankModeToDataFlash(bankMode, u32UserFlashConfig);

    SSU_releaseFlashSemaphore();

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
        uint32_t tmpVal = oReturnCheck;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                 
        };
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    oFlashStatus = Fapi_getFsmStatus((uint32_t) u32CurrentAddress, u32UserFlashConfig);

    if (oFlashStatus != 0b11)
    {
        uint32_t tmpVal = oFlashStatus;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                 
        };
        sblSendPacket(1, &errPkt);
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
        uint32_t tmpVal = oReturnCheck;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                    
        };
        sblSendPacket(1, &errPkt);
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

    if(oFlashStatus != 0b11)
    {
        uint32_t tmpVal = oFlashStatus;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                     
        };
        sblSendPacket(1, &errPkt);
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
        uint32_t tmpVal = oReturnCheck;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x100A,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                   
        };
        sblSendPacket(1, &errPkt);
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }

}

//
// Read Callback Function.
//
uint32_t insertUartData(uint32_t addr, uint32_t size)
{
    uint32_t status = BROM_STATUS_OK;

    sblGetDataArray((void *)addr, size);
    return (status);
}

//
// CopyApplication - This function will copy application from LDAx RAM to the Flash entry address
//
void CopyApplication(uint32_t LoadAddr, uint32_t ImageSize, uint8_t bankMode)
{

    // Declare/initialize locals
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    uint32_t i, j;
    uint32_t currentAddr = LoadAddr;
    uint32_t bytesWritten = 0;
    uint8_t Buffer[FLASH_BUFFER_SIZE] = {0};

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
    Fapi_FOTAStatus  FOTAStatus = Active_Bank;
    uint32_t u32UserFlashConfig = 0;
    oReturnCheck = Fapi_Status_Success;
    oFlashStatus = 3;

    // Set configuration as per user request
    u32UserFlashConfig = Fapi_getUserConfiguration(BankType,
                                                   FOTAStatus);
    oReturnCheck = Fapi_SetFlashCPUConfiguration(bankMode);
/*
    // Fapi_SetFlashCPUConfiguration is not working as intended.
    if(oReturnCheck != Fapi_Status_Success)
    {
        uint32_t tmpVal = oReturnCheck;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1008,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                     
        };
        sblSendPacket(1, &errPkt);
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }
    */

    // Write 512 bits of application to flash until the end of the image is reached.
    // Make sure that the remaining data will fill up the buffer
    for (i = 0; i < numBuffers; i++)
    {

        // Load up the buffer with 1024 bits (128 Byte) of the application
        sblGetDataArray(Buffer, FLASH_BUFFER_SIZE);

        // Create interleaved data buffers to prepare for programming
        ConstructInterleavedData1024Bits(Buffer);

        ClearFSMStatus(currentAddr, u32UserFlashConfig);

        // Enable program/erase protection for select sectors where this example is
        // located CMDWEPROTA, CMDWEPROTB
        Fapi_setupBankSectorEnable((uint32_t*)currentAddr, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
        Fapi_setupBankSectorEnable((uint32_t*)currentAddr, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);


        oReturnCheck = Fapi_issueAutoEcc512ProgrammingCommand((uint32_t*)currentAddr, Buffer,
                                          64, u32UserFlashConfig, 1);


        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady(currentAddr, u32UserFlashConfig) == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            uint32_t tmpVal = oReturnCheck;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = &tmpVal                   
            };
            sblSendPacket(1, &errPkt);
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
        if(oFlashStatus != 0b11)
        {
            uint32_t tmpVal = oFlashStatus;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = (uint32_t*)&oFlashStatus                      
            };
            sblSendPacket(1, &errPkt);
            //
            //Check FMSTAT and debug accordingly
            //
            Example_Error();
        }

        //
        // Verify the programmed values.  Check for any ECC errors.
        //
        oReturnCheck = Fapi_doVerify((uint32_t*)currentAddr,
                                     16, (uint32_t*)(Buffer),
                                     &oFlashStatusWord, 1, u32UserFlashConfig);

        if(oReturnCheck != Fapi_Status_Success)
        {
            uint32_t tmpVal = oReturnCheck;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x100A,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = &tmpVal                    
            };
            sblSendPacket(1, &errPkt);
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }

        ClearFSMStatus(currentAddr, u32UserFlashConfig);

        // Enable program/erase protection for select sectors where this example is
        // located CMDWEPROTA, CMDWEPROTB
        Fapi_setupBankSectorEnable((uint32_t*)currentAddr, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, 0x00000000);
        Fapi_setupBankSectorEnable((uint32_t*)currentAddr, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, 0x00000000);


        oReturnCheck = Fapi_issueAutoEcc512ProgrammingCommand((uint32_t*)currentAddr, Buffer,
                                          64, u32UserFlashConfig, 2);


        //
        // Wait until the Flash program operation is over
        //
        while(Fapi_checkFsmForReady(currentAddr, u32UserFlashConfig) == Fapi_Status_FsmBusy);

        if(oReturnCheck != Fapi_Status_Success)
        {
            uint32_t tmpVal = oReturnCheck;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = &tmpVal                 
            };
            sblSendPacket(1, &errPkt);
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
        if(oFlashStatus != 0b11)
        {
            uint32_t tmpVal = oFlashStatus;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = &tmpVal                    
            };
            sblSendPacket(1, &errPkt);
            //
            //Check FMSTAT and debug accordingly
            //
            Example_Error();
        }

        oReturnCheck = Fapi_doVerify((uint32_t*)currentAddr,
                                     16, (uint32_t*)(Buffer),
                                     &oFlashStatusWord, 2, u32UserFlashConfig);


        if(oReturnCheck != Fapi_Status_Success)
        {
            uint32_t tmpVal = oReturnCheck;
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x100A,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 1U,                       
                .pArgsVal = &tmpVal                    
            };
            sblSendPacket(1, &errPkt);
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

            if (bytesRemaining > 16)
            {
                // Load up the buffer with 128 bits of the application
                sblGetDataArray(Buffer, 16);
            } 
            else
            {
                // Load up the buffer with remaining bits of the application
                sblGetDataArray(Buffer, bytesRemaining);

                // Fill remaining buffer with 1s
                for (i = bytesRemaining; i < FLASH_BUFFER_SIZE; i++)
                {
                    Buffer[i] = 0xFF;
                }
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
                uint32_t tmpVal = oReturnCheck;
                const ErrorStatusPkt_t errPkt =
                {
                    .payloadType = (PayloadType)ErrorStatus,
                    .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
                    .recoveryStatus = RS_Unrecoverable, 
                    .hasSprintfArgs = true,             
                    .numArgs = 1U,                       
                    .pArgsVal = &tmpVal                   
                };
                sblSendPacket(1, &errPkt);
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
            if(oFlashStatus != 0b11)
            {
                uint32_t tmpVal = oFlashStatus;
                const ErrorStatusPkt_t errPkt =
                {
                    .payloadType = (PayloadType)ErrorStatus,
                    .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
                    .recoveryStatus = RS_Unrecoverable, 
                    .hasSprintfArgs = true,             
                    .numArgs = 1U,                       
                    .pArgsVal = &tmpVal                      
                };
                sblSendPacket(1, &errPkt);
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
                uint32_t tmpVal = oReturnCheck;
                const ErrorStatusPkt_t errPkt =
                {
                    .payloadType = (PayloadType)ErrorStatus,
                    .errorMsgCode = 0x100A,              // error message decoded in comm_packet_protocol.h
                    .recoveryStatus = RS_Unrecoverable, 
                    .hasSprintfArgs = true,             
                    .numArgs = 1U,                       
                    .pArgsVal = &tmpVal               
                };
                sblSendPacket(1, &errPkt);
                //
                // Check Flash API documentation for possible errors
                //
                Example_Error();
            }

            // Increment the current address and number of bytes written
            if (bytesRemaining > 16)
            {
                currentAddr += 16;
                bytesWritten += 16;
                bytesRemaining -= 16;
            } else
            {
                currentAddr += bytesRemaining;
                bytesWritten += bytesRemaining;
            }

        }

    }

    // If there is a discrepancy between the number of bytes written and the
    // size of the image, something has gone wrong
    if (bytesWritten != ImageSize)
    {
        uint32_t argsValArr[2] = { bytesWritten, ImageSize };
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x100B,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 2U,                       
            .pArgsVal = argsValArr                    
        };
        sblSendPacket(1, &errPkt);

        Example_Error();
    }

}

//*****************************************************************************
//
//  This function clears the status (STATCMD, similar to FMSTAT of the previous
//  devices) of the previous flash operation.
//
//*****************************************************************************
void ClearFSMStatus(uint32_t u32StartAddress, uint32_t u32UserFlashConfig)
{
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
    while (Fapi_checkFsmForReady(u32StartAddress, u32UserFlashConfig) != Fapi_Status_FsmReady) {;}
    oFlashStatus = Fapi_getFsmStatus(u32StartAddress, u32UserFlashConfig);

    /* Clear the Status register */
    oReturnCheck = Fapi_issueAsyncCommand(u32StartAddress, u32UserFlashConfig, Fapi_ClearStatus);
    //
    // Wait until status is cleared
    //
    while (Fapi_getFsmStatus(u32StartAddress, u32UserFlashConfig) != 0) {}

    if(oReturnCheck != Fapi_Status_Success)
    {
        uint32_t tmpVal = oReturnCheck;
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x100C,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                    
        };
        sblSendPacket(1, &errPkt);
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
            uint32_t tmpVal = oReturnCheck;
            const ErrorStatusPkt_t errPkt =
            {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1005,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  // 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                      
            };
            
            sblSendPacket(1, &errPkt);
            // Check Flash API documentation for possible errors
            Example_Error();
        }

        // Read FMSTAT register contents to know the status of FSM after
        // erase command to see if there are any erase operation related errors
        oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, FlashConfig);
        if(oFlashStatus != 0b11)
        {   
            uint32_t tmpVal = oFlashStatus;
            const ErrorStatusPkt_t errPkt =
            {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  // 
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = &tmpVal                   
            };
            
            sblSendPacket(1, &errPkt);
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
        uint32_t tmpVal = u32CurrentAddress;
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1007,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  // 
            .hasSprintfArgs = true,             
            .numArgs = 1U, 
            .pArgsVal = &tmpVal
        };
        sblSendPacket(1, &errPkt);

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
    uint32_t u32CurrentAddress;
    uint8_t  u8Iterator = 0;


    if ((bankMode == Mode3) && (targetCPU == 3)) 
    {
        u32CurrentAddress = FlashFR2_Mode3RP0BankmgmtStartAddress;
    }
    else // targetCPU == 1
    {
        u32CurrentAddress = FlashFR1_Mode1RP0BankmgmtStartAddress;
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

        // Issue bank erase command
        // oReturnCheck = Fapi_issueBankEraseCommand((uint32_t *)(u32CurrentAddress), u8Iterator , flashConfig);
        oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector, (uint32_t *)(u32CurrentAddress), u8Iterator, flashConfig);
        
        // Wait until FSM is done with erase operation
        while (Fapi_checkFsmForReady(u32CurrentAddress, flashConfig) != Fapi_Status_FsmReady){}

        // Read FMSTAT register contents to know the status of FSM after
        // erase command to see if there are any erase operation related errors
        oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, flashConfig);

        if(oReturnCheck != Fapi_Status_Success)
        {
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = false,             
                .numArgs = 0U,                       
                .pArgsVal = NULL                    
            };
            const FlashStatusPkt_t flashPkt = 
            {
                .payloadType = (PayloadType)FlashStatus,
                .status = oReturnCheck,
                .address = u32CurrentAddress,
                .flashAPIError = FLASH_ERASE_ERROR,
                .flashAPIFsmStatus = oFlashStatus
            };
            sblSendPacket(2, &flashPkt, &errPkt);
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }
        
        if(oFlashStatus != 0b11)
        {
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = false,             
                .numArgs = 0U,                       
                .pArgsVal = NULL                    
            };
            const FlashStatusPkt_t flashPkt = 
            {
                .payloadType = (PayloadType)FlashStatus,
                .status = oReturnCheck,
                .address = u32CurrentAddress,
                .flashAPIError = FLASH_ERASE_ERROR,
                .flashAPIFsmStatus = oFlashStatus
            };
            sblSendPacket(2, &flashPkt, &errPkt);
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
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1007,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = false,             
            .numArgs = 0U, 
            .pArgsVal = NULL
        };
        const FlashStatusPkt_t flashPkt = 
        {
            .payloadType = (PayloadType)FlashStatus,
            .status = oReturnCheck,
            .address = u32CurrentAddress,
            .flashAPIError = FLASH_BLANK_ERROR,
            .flashAPIFsmStatus = oFlashStatus
        };
        sblSendPacket(2, &flashPkt, &errPkt);

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

        //
        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related
        // errors
        //
        oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, flashConfig);
        
        if(oReturnCheck != Fapi_Status_Success)
        {
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = true,             
                .numArgs = 0U,                       
                .pArgsVal = NULL                    
            };
            const FlashStatusPkt_t flashPkt = 
            {
                .payloadType = (PayloadType)FlashStatus,
                .status = oReturnCheck,
                .address = u32CurrentAddress,
                .flashAPIError = FLASH_PROGRAM_ERROR,
                .flashAPIFsmStatus = oFlashStatus
            };
            sblSendPacket(2, &flashPkt, &errPkt);
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }
        
        if(oFlashStatus != 0b11)
        {
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = false,             
                .numArgs = 0U,                       
                .pArgsVal = NULL                    
            };
            const FlashStatusPkt_t flashPkt = 
            {
                .payloadType = (PayloadType)FlashStatus,
                .status = oReturnCheck,
                .address = u32CurrentAddress,
                .flashAPIError = FLASH_PROGRAM_ERROR,
                .flashAPIFsmStatus = oFlashStatus
            };
            sblSendPacket(2, &flashPkt, &errPkt);
            Example_Error();
        }

        //
        // Verify the programmed values.  Check for any ECC errors.
        //
        oReturnCheck = Fapi_doVerify((uint32_t*)u32CurrentAddress,
                                        2, (uint32_t*)(Buffer),
                                        &oFlashStatusWord, 0, flashConfig);

        if(oReturnCheck != Fapi_Status_Success)
        {
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x100A,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = false,             
                .numArgs = 0U,                       
                .pArgsVal = NULL                   
            };
            const FlashStatusPkt_t flashPkt = 
            {
                .payloadType = (PayloadType)FlashStatus,
                .status = oReturnCheck,
                .address = u32CurrentAddress,
                .flashAPIError = FLASH_VERIFY_ERROR,
                .flashAPIFsmStatus = oFlashStatus
            };
            sblSendPacket(2, &flashPkt, &errPkt);
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

    //
    // Read FMSTAT register contents to know the status of FSM after
    // program command to see if there are any program operation related
    // errors
    //
    oFlashStatus = Fapi_getFsmStatus(u32CurrentAddress, flashConfig);

        if(oReturnCheck != Fapi_Status_Success)
        {
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1009,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = false,             
                .numArgs = 0U,                       
                .pArgsVal = NULL                    
            };
            const FlashStatusPkt_t flashPkt = 
            {
                .payloadType = (PayloadType)FlashStatus,
                .status = oReturnCheck,
                .address = u32CurrentAddress,
                .flashAPIError = FLASH_PROGRAM_ERROR,
                .flashAPIFsmStatus = oFlashStatus
            };
            sblSendPacket(2, &flashPkt, &errPkt);
            //
            // Check Flash API documentation for possible errors
            //
            Example_Error();
        }
        
        if(oFlashStatus != 0b11)
        {
            const ErrorStatusPkt_t errPkt =
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1006,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable, 
                .hasSprintfArgs = false,             
                .numArgs = 0U,                       
                .pArgsVal = NULL                    
            };
            const FlashStatusPkt_t flashPkt = 
            {
                .payloadType = (PayloadType)FlashStatus,
                .status = oReturnCheck,
                .address = u32CurrentAddress,
                .flashAPIError = FLASH_PROGRAM_ERROR,
                .flashAPIFsmStatus = oFlashStatus
            };
            sblSendPacket(2, &flashPkt, &errPkt);
            Example_Error();
        }

    //
    // Verify the programmed values.  Check for any ECC errors.
    //
    oReturnCheck = Fapi_doVerify((uint32_t*)u32CurrentAddress,
                                    4, (uint32_t*)(Buffer),
                                    &oFlashStatusWord, 0, flashConfig);

    if(oReturnCheck != Fapi_Status_Success)
    {
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x100A,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable, 
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                   
        };
        const FlashStatusPkt_t flashPkt = 
        {
            .payloadType = (PayloadType)FlashStatus,
            .status = oReturnCheck,
            .address = u32CurrentAddress,
            .flashAPIError = FLASH_VERIFY_ERROR,
            .flashAPIFsmStatus = oFlashStatus
        };
        sblSendPacket(2, &flashPkt, &errPkt);
        Example_Error();
    }
}

//! \brief     Transform 1024bit sequential data into interleaved data of 2*512bit chuncks for 512bit interleaved flash programming
//! \param[in] sequential1024BitsArrPtr	pointer to the head of 1024bit sequential data array
//!
//! i.e, The final interleaved data will be in the format of:
//!         0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
//!         32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
//!         64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
//!         96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,
//!         16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
//!         48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
//!         80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
//!         112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127
//! (0...127 represents the nth byte index of the original sequential data)
void ConstructInterleavedData1024Bits(uint8_t* sequential1024BitsArrPtr)
{
    uint8_t* srcBuffer = sequential1024BitsArrPtr;
    uint8_t tmpBuffer[64];

    // Even(first) interleaved region: 0-15, 32-47, 64-79, 96-111 Byte
    // Note: First even region (0-15) doesn't need to be re-copied, starting from 32 
    int evenIdx = 32;  
    // Odd(second) interleaved region: 16-31, 48-63, 80-95, 112-127 Byte
    int oddIdx = 16; 
    

    // Preparing temp buffer to store the 2nd half of 1024bit data composed of odd(second) interleaved 512bit data
    for (int idx = 0; idx < 64; idx += 16)
    {
       memcpy(&tmpBuffer[idx], &srcBuffer[oddIdx], 16);
       oddIdx += 32;
    }

    // Preparing src buffer to store the 1st half of 1024bit data composed of even(first) interleaved 512bit data
    // Skipping first even region (0-15)
    for (int idx = 16; idx < 64; idx += 16)
    {
       memcpy(&srcBuffer[idx], &srcBuffer[evenIdx], 16);
       evenIdx += 32;
    }

    // Copying the 2nd half of 1024bit back to the bottom half of the original buffer
    memcpy(&srcBuffer[64], tmpBuffer, 64);
}

uint32_t bootloadProcessWithChecks(bootLoadCtx_t *blCtx)
{
    uint32_t ImageSize;

    //
    // Boot loader Process, returns image size
    //
    ImageSize = bootloadProcess(blCtx);

    if (ImageSize == 0)
    {
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1002,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation, 
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                      
        };
        sblSendPacket(1, &errPkt);
        Example_Error();
    }
    else if(ImageSize > blCtx->maxImageSize)
    {
        uint32_t argsValArr[2] = {ImageSize, blCtx->maxImageSize};
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1003,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation, 
            .hasSprintfArgs = true,             
            .numArgs = 2U,                       
            .pArgsVal = argsValArr 
        };
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    return ImageSize;
}

//
// End of file
//