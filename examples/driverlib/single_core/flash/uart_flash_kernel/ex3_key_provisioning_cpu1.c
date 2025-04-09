//###########################################################################
//
// FILE:    ex3_key_provisioning_cpu1.c
//
// TITLE:   Functions associated with the key provisioning flow
//! <h1> Functions associated with the key provisioning flow </h1>
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


#include <ex3_key_provisioning_cpu1.h>
#include <ti_drivers_config.h>
#include <ti_dpl_config.h>

/*
    KEYWRITER_MODE - converts the device from HS-FS to HS-SE
    DRYRUN_MODE    - executes the keywriter without blowing the Efuses
*/
#define KEYWRITER_MODE                          (0x00000000U)
#define DRYRUN_MODE                             (0xF0000000U)

/* Initial value of debug response. This is compared with the response from HSM side. */
#define DEBUG_RESPONSE_SUCCESS                  (0x00000000U)

#define DBGRSP_ERROR_PHASE_MASK                 (0x0000000FU)
#define DBGRSP_ERROR_MODULE_MASK                (0x00000FF0U)
#define DBGRSP_ERROR_STAGE_MASK                 (0x000FF000U)
#define DBGRSP_ERROR_CUSTKEYEXTENSION_MASK      (0x00F00000U)

#define DBGRSP_ERROR_MODULE_SHIFT               (4U)
#define DBGRSP_ERROR_STAGE_SHIFT                (12U)
#define DBGRSP_ERROR_CUSTKEYEXTENSION_SHIFT     (20U)

/* Global variable declare in auto-gen file */
extern HsmClient_t gHSMClient;
extern ClockP_Config gClockConfig;

//
// Copy a RAM-based HSMRt Image to LDAx RAM
//
uint8_t copyImageToRAM(uint32_t bootMode, uint32_t BaseAddress)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t loop;
    uint32_t ImageSize = 0;
    uint8_t authStatus = 0;
    int32_t  hsmStatus   = 0;

    blCtx.certAddr      = BaseAddress;
    blCtx.certType      = CERT_TYPE_KP_HSMFW_IMAGE;
    blCtx.imageAddr     = BaseAddress + MAX_CERT_SIZE;
    blCtx.maxImageSize  = UART_BOOT_MAX_IMAGE_SIZE;
    blCtx.readDataCb    = &uartRead;

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

                    if ((ImageSize != 0) && (ImageSize <= MAX_KP_IMAGE_SIZE))
                    {
                        //
                        // Boot load is successful, now exit LINK1 and copy the image to Flash memory
                        //
                        CopyApplicationToRAM(ImageSize, BaseAddress + MAX_CERT_SIZE);

                        //
                        // Enable the interrupts for HSMROM x FLASH KERNEL Communication
                        //
                        Dpl_init();

                        authStatus = 0xFF;

                        // Wait for HSM IPC message that says HSMRt is validated and
                        // running in LDAx RAM
                        hsmStatus  = Hsmclient_loadHSMRtFirmware(&gHSMClient, (uint8_t *)(BaseAddress));
                        hsmStatus = HsmClient_waitForBootNotify(NULL, 0);
                        if(hsmStatus == SystemP_SUCCESS)
                        {
                            authStatus = 0;
                        }

                        //
                        // DeInit as System Init is yet to be called.
                        //
                        Dpl_deinit();
                    } else
                    {
                        Example_Error();
                    }
                }
            }
    }
    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return(authStatus);

}

//
// Copy customer keys to LDA0 RAM
//
uint8_t copyKeysToRAM(uint32_t bootMode, uint32_t BaseAddress)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t loop;
    uint32_t ImageSize = 0;
    uint8_t authStatus = 0;

    KeyWriterCertHeader_t certHeader;

    uint32_t startCycleCount, endCycleCount;
    const uint32_t cpuMHz = (gClockConfig.timerInputClkHz)/1000000;

    CycleCounterP_reset();

    certHeader.certAddress = (uint8_t *)SOC_virtToPhy((uint8_t *)BaseAddress);
    certHeader.debugResponse = DEBUG_RESPONSE_SUCCESS;

    /*
        The default mode is DRYRUN_MODE . No conversion occurs in this mode.
        To convert a device change the certHeader.reserved field below to KEYWRITER_MODE .
    */
    certHeader.reserved = DRYRUN_MODE;

    blCtx.certAddr      = BaseAddress;
    blCtx.certType      = CERT_TYPE_KP_KEYCERT;
    blCtx.imageAddr     = BaseAddress + MAX_CERT_SIZE;
    blCtx.maxImageSize  = MAX_KEY_SIZE;
    blCtx.readDataCb    = &uartRead;

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

                    //
                    // Check for valid image size. Must be non-zero and less than 8KB
                    //
                    if ((ImageSize != 0) && (ImageSize <= MAX_KEY_SIZE))
                    {
                        certHeader.certSize = g_bootLoadStatus.certSize + ImageSize;
                        //
                        // Receive and copy the application to LDA0 RAM
                        //
                        CopyApplicationToRAM(ImageSize, BaseAddress + g_bootLoadStatus.certSize);

                        startCycleCount = CycleCounterP_getCount64();
                        // Wait for HSM IPC message that says keys are validated in LDAx RAM
                        authStatus = HsmClient_keyWriter(&gHSMClient, (KeyWriterCertHeader_t *)(&certHeader), SystemP_WAIT_FOREVER);
                        endCycleCount = CycleCounterP_getCount64();
                        char buffer[2048U], buffer1[128U];
                        sprintf(buffer1, "\r\n\r\n[HSM CLIENT_PROFILE] Time taken to Process Key Certificate %uus\r\n", ((endCycleCount - startCycleCount) / cpuMHz));
                        strcat(buffer, buffer1);
                        sprintf(buffer1, "[HSM CLIENT] OTP-KW Error encountered in OTP Keywriter\n\n\r");
                        strcat(buffer, buffer1);
                        sprintf(buffer1, "[HSM CLIENT] OTP-KW debugResponse = 0x%08x\r\n", certHeader.debugResponse);
                        strcat(buffer, buffer1);
                        sprintf(buffer1, "[HSM CLIENT] OTP-KW Error phase = 0x%01x\r\n", (certHeader.debugResponse & DBGRSP_ERROR_PHASE_MASK));
                        strcat(buffer, buffer1);
                        sprintf(buffer1, "[HSM CLIENT] OTP-KW Error module = 0x%02x\r\n", (certHeader.debugResponse & DBGRSP_ERROR_MODULE_MASK) >> DBGRSP_ERROR_MODULE_SHIFT);
                        strcat(buffer, buffer1);
                        sprintf(buffer1, "[HSM CLIENT] OTP-KW Error stage = 0x%02x\r\n", (certHeader.debugResponse & DBGRSP_ERROR_STAGE_MASK) >> DBGRSP_ERROR_STAGE_SHIFT);
                        strcat(buffer, buffer1);
                        sprintf(buffer1, "[HSM CLIENT] OTP-KW Error customer key extension = 0x%01x\n\n\r", (certHeader.debugResponse & DBGRSP_ERROR_CUSTKEYEXTENSION_MASK) >> DBGRSP_ERROR_CUSTKEYEXTENSION_SHIFT);
                        strcat(buffer, buffer1);

                        strcpy((void *)((0x200FA000U + 0x2000U)- 512U), (buffer));
                    }
                    else
                    {
                        Example_Error();
                    }
                }
            }
    }
    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return(authStatus);

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