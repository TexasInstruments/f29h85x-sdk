// ###########################################################################
//
//  FILE:    ex4_code_provisioning.c
//
//  TITLE:   UART HS-SE code provisioning functions
//! <h1> UART HS-SE code provisioning </h1>
//
// ###########################################################################
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

// ###########################################################################

#include "ex4_uart_boot_cpu1.h"
#include <ex4_code_provisioning_cpu1.h>
#include <ti_drivers_config.h>
#include <ti_dpl_config.h>

/* Global variable declare in auto-gen file */
extern HsmClient_t gHSMClient;

//
// provisionApplicationImgToHSM
//
uint8_t provisionApplicationImgToHSM(uint32_t BaseAddress, uint8_t bankMode)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t loop;
    uint32_t ImageSize = 0;
    uint8_t authStatus = 0;

    blCtx.certAddr = BaseAddress;
    blCtx.imageAddr = BaseAddress + MAX_CERT_SIZE;
    blCtx.maxImageSize = FLASH_IMAGE_SIZE;
    blCtx.readDataCb = &uartRead;
    blCtx.certType = CERT_TYPE_CP_APP_IMAGE;

    FirmwareUpdateReq_t firmwareUpdate;

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

            // Send IPC Message to HSM
            // loadHSMRt

            if (status == BROM_STATUS_OK)
            {
                //
                // Boot loader Process, returns image size
                //
                ImageSize = bootloadProcess(&blCtx);

                if (ImageSize != 0)
                {

                    //
                    // Boot load is successful, now exit LINK1 and copy the image to Flash memory
                    //
                    AuthenticateImageviaHSMRT(ImageSize, BaseAddress);
                }
            }
        }
    }

    // Request semaphore for CPU1
    bool flashSemaphore;
    flashSemaphore = SSU_claimFlashSemaphore();

    //
    // Claim flash semaphore
    //
    if (!flashSemaphore) 
    {
        Example_Error();
    }

    //
    // Program the current bank mode to the data flash
    //
    ProgramBankModeToDataFlash(bankMode, 0);

    //
    // Release flash semaphore
    //
    flashSemaphore = SSU_releaseFlashSemaphore();

    if (!flashSemaphore) 
    {
        Example_Error();
    }

    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return (authStatus);
}

//
// provisionSecCfgImg
//
uint8_t provisionSecCfgImg(uint32_t BaseAddress)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t loop;
    uint32_t ImageSize = 0;
    uint8_t authStatus = 0;

    blCtx.certAddr = BaseAddress;
    blCtx.imageAddr = BaseAddress + MAX_CERT_SIZE;
    blCtx.maxImageSize = FLASH_IMAGE_SIZE;
    blCtx.readDataCb = &uartRead;
    blCtx.certType = CERT_TYPE_CP_APP_IMAGE;

    FirmwareUpdateReq_t firmwareUpdate;

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

            // Send IPC Message to HSM
            // loadHSMRt

            if (status == BROM_STATUS_OK)
            {
                //
                // Boot loader Process, returns image size
                //
                bootloadProcess(&blCtx);
                ImageSize = SEC_CFG_IMG_SIZE;

                if (ImageSize != 0)
                {
                    CopyApplicationToRAM(ImageSize, BaseAddress + MAX_CERT_SIZE);

                    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
                    firmwareUpdate.dataLength = MAX_CERT_SIZE;
                    firmwareUpdate.bankMode = 0; // TBD

                    // Wait for HSM IPC message that says keys are validated in LDAx RAM
                    authStatus = HsmClient_firmwareUpdate_CertProcess(&gHSMClient, &firmwareUpdate);

                    firmwareUpdate.pStartAddress = (uint8_t *)(BaseAddress + MAX_CERT_SIZE);
                    firmwareUpdate.dataLength = ImageSize;
                    firmwareUpdate.bankMode = 0; // TBD

                    // Wait for HSM IPC message that says keys are validated in LDAx RAM
                    authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);

                    firmwareUpdate.pStartAddress = (uint8_t *)NULL;
                    firmwareUpdate.dataLength = 0;
                    firmwareUpdate.bankMode = 0; // TBD

                    // Wait for HSM IPC message that says keys are validated in LDAx RAM
                    authStatus = HsmClient_firmwareUpdate_CodeVerify(&gHSMClient, &firmwareUpdate);
                }
            }
        }
    }
    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return (authStatus);
}

//
// copyC29ImageToFlash - NOT FINALIZED
//
uint8_t copyC29ImageToFlash(uint32_t bootMode, uint32_t BaseAddress)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t loop;
    uint32_t ImageSize = 0;
    uint8_t authStatus = 0;

    blCtx.certAddr = LDA1_RAM_BASE;
    blCtx.imageAddr = LDA1_RAM_BASE + MAX_CERT_SIZE;
    blCtx.maxImageSize = UART_BOOT_MAX_IMAGE_SIZE;
    blCtx.readDataCb = &uartRead;
    blCtx.certType = CERT_TYPE_CP_C29_IMAGE;

    FirmwareUpdateReq_t firmwareUpdate;

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

            // Send IPC Message to HSM
            // loadHSMRt

            if (status == BROM_STATUS_OK)
            {
                //
                // Boot loader Process, returns image size
                //
                ImageSize = bootloadProcess(&blCtx);

                firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
                firmwareUpdate.dataLength = MAX_CERT_SIZE;
                firmwareUpdate.bankMode = 0; // TBD

                // Wait for HSM IPC message that says keys are validated in LDAx RAM
                authStatus = HsmClient_firmwareUpdate_CertProcess(&gHSMClient, &firmwareUpdate);

                if (ImageSize != 0)
                {

                    //
                    // Boot load is successful, now copy the image to Flash memory
                    //
                    CopyApplicationWithAuthentication(FLASH_IMAGE_SIZE, BaseAddress);
                }
            }
        }
    }
    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return (authStatus);
}

//
// AuthenticateImageviaHSMRT()
//
void AuthenticateImageviaHSMRT(uint32_t ImageSize, uint32_t BaseAddress)
{
    // Declare/initialize locals
    uint8_t wordData;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t bytesWritten = 0;
    uint32_t numBytesRemaining = 0;
    uint32_t currentAddress = 0;
    uint32_t numChunks = 0;
    uint8_t authStatus = 0;
    FirmwareUpdateReq_t firmwareUpdate;
    uint32_t lastDataStreamSize = 0;
    uint8_t temp = 0;
    uint8_t lastStream[CHUNK_SIZE] = {0xFF};

    // Populate parameters for certificate processing
    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
    firmwareUpdate.dataLength = MAX_CERT_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Process certificate to verify the authenticity of the incoming firmware
    authStatus = HsmClient_firmwareUpdate_CertProcess(&gHSMClient, &firmwareUpdate);

    sendACK();

    // Receive the first chunk post certificate from the SCI tool
    for (j = 0; j < CHUNK_SIZE; j++)
    {
        wordData = uartGetData();
        HWREGB(BaseAddress + MAX_CERT_SIZE + j) = wordData;
    }

    // Populate parameters to program the first receive chunk in flash
    firmwareUpdate.pStartAddress = (uint8_t *)(BaseAddress + MAX_CERT_SIZE);
    firmwareUpdate.dataLength = 512;
    firmwareUpdate.bankMode = 0; // TBD

    // Program the first received chunk in flash
    authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
    bytesWritten += CHUNK_SIZE;

    sendACK();

    // Populate the array that will store the last data stream and pad it
    for (i = 0; i < CHUNK_SIZE; i++)
    {
        lastStream[i] = 0xFFU;
    }
    
    // Copy the last received chunk to the end of the LDAx bank
    memcpy((void *)(BaseAddress + (15 * (2 * CHUNK_SIZE))), (void *)(BaseAddress + MAX_CERT_SIZE), CHUNK_SIZE);

    // Calculate the number of bytes left to receive from the SCI tool
    numBytesRemaining = ImageSize - bytesWritten;

    // Find the number pending chunks to be received from tool and the last data stream size less than the chunk size
    if (0 == (numBytesRemaining % CHUNK_SIZE))
    {
        numChunks = numBytesRemaining / CHUNK_SIZE;
    }
    else
    {
        numChunks = (numBytesRemaining / CHUNK_SIZE);
        lastDataStreamSize = numBytesRemaining - (numChunks * CHUNK_SIZE);
    }

    while ((0 != numChunks) || (0 != lastDataStreamSize))
    {
        // If number of chunks pending is greater than 28 (size >= 14 KB), receive 14 KB of data and program it 
        if (numChunks >= 28)
        {
            // Read in 14KB and copy it to the first 14KB of LDA7 RAM
            for (i = 0; i < (14 * 2 * CHUNK_SIZE); i++) 
            {
                wordData = uartGetData();
                HWREGB(BaseAddress + i) = wordData;
            }

            // Subract 28 chunks (14 KB)
            numChunks -= 28;
            // Populate parameters to program the chunk in flash
            firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
            firmwareUpdate.dataLength = 14 * (2 * CHUNK_SIZE);
            firmwareUpdate.bankMode = 0; // TBD

            // Program the received chunk in flash
            authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
            bytesWritten += 14 * (2 * CHUNK_SIZE);

            sendACK();
        }
        // If number of chunks pending is less than 28 (size < 14 KB), receive remaining number of chunks and program it
        else if ((numChunks < 28) && (numChunks > 0))
        {
            temp = numChunks;

            // Read in the data less than 14KB
            for (i = 0; i < (numChunks * CHUNK_SIZE); i++) 
            {
                wordData = uartGetData();
                HWREGB(BaseAddress + i) = wordData;
            }

            // Decrement numChunks by the number of chunks we read
            numChunks -= temp;

            // Populate parameters to program the chunk in flash
            firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
            firmwareUpdate.dataLength = temp * CHUNK_SIZE;
            firmwareUpdate.bankMode = 0; // TBD

            // Program the received chunk in flash
            authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
            bytesWritten += (temp * CHUNK_SIZE);

            // Only send ack if more data is coming
            if (lastDataStreamSize) 
            {
                sendACK();
            }
        }
        // If number of bytes pending is less than the chunk size and not zero, program the remaining number of bytes
        else if ((0 == numChunks) && (0 != lastDataStreamSize))
        {
            // Read in last chunk
            for (i = 0; i < lastDataStreamSize; i++) 
            {
                wordData = uartGetData();
                HWREGB(BaseAddress + i) = wordData;
                lastStream[i] = wordData;
            }

            // Fill in empty chunk space with 0xFF
            for (i = lastDataStreamSize; i < CHUNK_SIZE; i++) 
            {
                HWREGB(BaseAddress + i) = 0xFF;
            }
            
            // Populate parameters to program the chunk in flash
            firmwareUpdate.pStartAddress = (uint8_t *)&lastStream[0];
            firmwareUpdate.dataLength = CHUNK_SIZE;
            firmwareUpdate.bankMode = 0; // TBD

            // Program the last data stream along with padded array in flash
            authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
            bytesWritten += lastDataStreamSize;
            lastDataStreamSize = 0;
        }
    }

    // Populate parameters to verify the programmed firmware in flash
    firmwareUpdate.pStartAddress = (uint8_t *)NULL;
    firmwareUpdate.dataLength = 0;
    firmwareUpdate.bankMode = 0; // TBD

    // Verify the programmed firmware and program the certificate in flash
    authStatus = HsmClient_firmwareUpdate_CodeVerify(&gHSMClient, &firmwareUpdate);

    if (authStatus)
    {
        Example_Error();
    }

    // If there is a discrepancy between the number of bytes written and the
    // size of the image, something has gone wrong
    if (bytesWritten != ImageSize)
    {
        Example_Error();
    }

}

//
// CopyApplicationToRAM - This function will copy application to LDAx RAM
//
void CopyApplicationToRAM(uint32_t ImageSize, uint32_t BaseAddress)
{

    // Declare/initialize locals
    uint16_t wordData;
    uint32_t i, j;
    uint32_t currentAddr = BaseAddress;
    uint32_t bytesWritten = 0;

    uint32_t bytesRemaining = ImageSize % BUFFER_SIZE;
    uint32_t numBuffers = ImageSize / BUFFER_SIZE;

    uint8_t Buffer[BUFFER_SIZE] = {0};


    // Write 128 bits of application to RAM until the end of the image is reached.
    // Make sure that the remaining data will fill up the buffer

    for (i = 0; i < numBuffers; i++)
    {
        // Load up the buffer with 128 bits of the application
        for (j = 0; j < 16; j++)
        {
            wordData = uartGetData();
            Buffer[j] = wordData;

        }


        // Write buffer to RAM
        for (j = 0; j < 16; j++)
        {
            HWREGB(currentAddr + j) = (uint8_t)(Buffer[j]);
        }

        // Increment the current address and number of bytes written by 16 (128 bits)
        currentAddr += 16;
        bytesWritten += 16;

    }


    // Once there is less than one full buffer left in the image, we need to
    // fill up the buffer with the remaining data and then fill with 0xFFFF
    if (bytesRemaining)
    {

        // Load up the buffer with 128 bits of the application
        for (i = 0; i < bytesRemaining; i++)
        {
            wordData = uartGetData();
            Buffer[i] = wordData;
        }

        // Write buffer to RAM
        for (i = 0; i < bytesRemaining; i++)
        {
            HWREGB(currentAddr + i) = (uint8_t)(Buffer[i]);
        }

        // Increment the current address and number of bytes written by 16 (128 bits)
        currentAddr += bytesRemaining;
        bytesWritten += bytesRemaining;

    }

    // If there is a discrepancy between the number of bytes written and the
    // size of the image, something has gone wrong
    if (bytesWritten != ImageSize)
    {
        Example_Error();
    }

}


////
//// End of file
////