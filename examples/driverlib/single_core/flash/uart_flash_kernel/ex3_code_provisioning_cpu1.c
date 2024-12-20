// ###########################################################################
//
//  FILE:    ex3_code_provisioning.c
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

#include <ex3_code_provisioning_cpu1.h>
#include <ti_drivers_config.h>
#include <ti_dpl_config.h>

/* Global variable declare in auto-gen file */
extern HsmClient_t gHSMClient;

//
// provisionApplicationImgToHSM
//
uint8_t provisionApplicationImgToHSM(uint32_t bootMode, uint32_t BaseAddress)
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
    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return (authStatus);
}

//
// provisionSecCfgImg
//
uint8_t provisionSecCfgImg(uint32_t bootMode, uint32_t BaseAddress)
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

    // Receive the first chunk post certificate from the SCI tool
    for (j = 0; j < CHUNK_SIZE; j++)
    {
        wordData = uartGetCPData();
        HWREGB(BaseAddress + MAX_CERT_SIZE + j) = wordData;
    }

    // Populate parameters for certificate processing
    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
    firmwareUpdate.dataLength = MAX_CERT_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Process certificate to verify the authenticity of the incoming firmware
    authStatus = HsmClient_firmwareUpdate_CertProcess(&gHSMClient, &firmwareUpdate);

    // Populate parameters to program the first receive chunk in flash
    firmwareUpdate.pStartAddress = (uint8_t *)(BaseAddress + MAX_CERT_SIZE);
    firmwareUpdate.dataLength = 512;
    firmwareUpdate.bankMode = 0; // TBD

    // Program the first received chunk in flash
    authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
    bytesWritten += CHUNK_SIZE;

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
            for (i = 0; i < 28; i++)
            {
                for (j = 0; j < CHUNK_SIZE; j++)
                {
                    currentAddress = ((BaseAddress + j) + 15 * (2 * CHUNK_SIZE));
                    wordData = *(uint8_t *)(currentAddress);
                    uartSendCPData(wordData);
                    wordData = uartGetCPData();
                    HWREGB(BaseAddress + (i * CHUNK_SIZE) + j) = wordData;
                }
                numChunks--;
                // Copy the last received chunk to the end of LDAx bank 
                memcpy((void *)(BaseAddress + (15 * (2 * CHUNK_SIZE))), (void *)(BaseAddress + (i * CHUNK_SIZE)), CHUNK_SIZE);
            }
            // Populate parameters to program the chunk in flash
            firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
            firmwareUpdate.dataLength = 14 * (2 * CHUNK_SIZE);
            firmwareUpdate.bankMode = 0; // TBD

            // Program the received chunk in flash
            authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
            bytesWritten += 14 * (2 * CHUNK_SIZE);
        }
        // If number of chunks pending is less than 28 (size < 14 KB), receive remaining number of chunks and program it
        else if ((numChunks < 28) && (numChunks > 0))
        {
            temp = numChunks;
            for (i = 0; i < temp; i++)
            {
                for (j = 0; j < CHUNK_SIZE; j++)
                {
                    currentAddress = ((BaseAddress + j) + 15 * (2 * CHUNK_SIZE));
                    wordData = *(uint8_t *)(currentAddress);
                    uartSendCPData(wordData);
                    wordData = uartGetCPData();
                    HWREGB(BaseAddress + (i * CHUNK_SIZE) + j) = wordData;
                }
                numChunks--;
                // Copy the last received chunk to the end of LDAx bank 
                memcpy((void *)(BaseAddress + (15 * (2 * CHUNK_SIZE))), (void *)(BaseAddress + (i * CHUNK_SIZE)), CHUNK_SIZE);
            }
            // Populate parameters to program the chunk in flash
            firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
            firmwareUpdate.dataLength = i * CHUNK_SIZE;
            firmwareUpdate.bankMode = 0; // TBD

            // Program the received chunk in flash
            authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
            bytesWritten += (i * CHUNK_SIZE);
        }
        // If number of bytes pending is less than the chunk size and not zero, program the remaining number of bytes
        else if ((0 == numChunks) && (0 != lastDataStreamSize))
        {
            for (i = 0; i < CHUNK_SIZE; i++)
            {
                // Send the last received chunk back
                currentAddress = ((BaseAddress + i) + 15 * (2 * CHUNK_SIZE));
                wordData = *(uint8_t *)(currentAddress);
                uartSendCPData(wordData);
                // Receive only the remaining bytes
                if (i < lastDataStreamSize)
                {
                    wordData = uartGetCPData();
                    HWREGB(BaseAddress + i) = wordData;
                    // Store the last received data stream contents in the pre-defined padded array
                    lastStream[i] = wordData;
                }
            }
            // Copy the last received chunk to the end of LDAx bank
            memcpy((void *)(BaseAddress + (15 * (2 * CHUNK_SIZE))), (void *)(BaseAddress), lastDataStreamSize);
            
            // Populate parameters to program the chunk in flash
            firmwareUpdate.pStartAddress = (uint8_t *)&lastStream[0];
            firmwareUpdate.dataLength = CHUNK_SIZE;
            firmwareUpdate.bankMode = 0; // TBD

            // Program the last data stream along with padded array in flash
            authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
            bytesWritten += lastDataStreamSize;

            // Send the last received data stream back to the SCI tool
            for (i = 0; i < lastDataStreamSize; i++)
            {
                currentAddress = ((BaseAddress + i) + 15 * (2 * CHUNK_SIZE));
                wordData = *(uint8_t *)(currentAddress);
                uartSendCPData(wordData);
            }
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
// CopyApplicationWithAuthentication() - NOT FINALIZED
//
void CopyApplicationWithAuthentication(uint32_t ImageSize, uint32_t BaseAddress)
{
}

////
//// End of file
////