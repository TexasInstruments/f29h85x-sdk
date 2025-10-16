//###########################################################################
//
// FILE:    sbl_key_provisioning.c
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


#include "sbl_key_provisioning.h"
#include <ti_drivers_config.h>
#include <ti_dpl_config.h>
#include <kernel/nortos/dpl/common/printf.h>

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
// CopyApplicationToRAM - This function will copy application to LDAx RAM
//
static inline void CopyApplicationToRAM(uint32_t ImageSize, uint32_t BaseAddress)
{
    sblGetDataArray((void *)BaseAddress, ImageSize);
}

//
// Copy and load RAM-based HSMRt Image to LDAx RAM 
//
int32_t loadHSMRT(uint32_t BaseAddress)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t loop;
    uint32_t ImageSize = 0;
    int32_t  hsmStatus = SystemP_SUCCESS;

    blCtx.certAddr      = BaseAddress;
    blCtx.certType      = CERT_TYPE_KP_HSMFW_IMAGE;
    blCtx.imageAddr     = BaseAddress + MAX_CERT_SIZE;
    blCtx.maxImageSize  = MAX_KP_IMAGE_SIZE;
    blCtx.readDataCb    = &insertUartData;

    //
    // Boot Loader Init
    //
    status = bootloadInit();

    //
    // Boot loader Process, returns image size
    //
    ImageSize = bootloadProcessWithChecks(&blCtx);

    //
    // Boot load is successful, now exit LINK1 and load the image to the destinated address
    //
    CopyApplicationToRAM(ImageSize, BaseAddress + MAX_CERT_SIZE);

    //
    // Enable the interrupts for HSMROM x FLASH KERNEL Communication
    //
    KernelDpl_init();

    // Loads HSM runtime firmware
    hsmStatus = Hsmclient_loadHSMRtFirmware(&gHSMClient, (uint8_t *)(BaseAddress));

    if(hsmStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1104,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation, 
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL 
        };
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    // Wait for HSM IPC message that says HSMRt is validated and
    // running in LDAx RAM
    hsmStatus = HsmClient_waitForBootNotify(NULL, 0);
    
    if(hsmStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1105,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation, 
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL 
        };
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    //
    // DeInit as System Init is yet to be called.
    //
    KernelDpl_deinit();
    
    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return(hsmStatus);
}

KeyWriterCertHeader_t certHeader __attribute__((section("hsm_accessible"))); // variable is noinit

//
// Copy customer keys to LDA0 RAM
//
int32_t provisionKeys(uint32_t BaseAddress)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t ImageSize = 0;
    int32_t authStatus = SystemP_SUCCESS;

    extern KeyWriterCertHeader_t certHeader;

    uint64_t startCycleCount, endCycleCount;
    const uint32_t cpuMHz = (gClockConfig.timerInputClkHz) / 1000000U;

    CycleCounterP_reset();

    certHeader.certAddress = (uint8_t *)SOC_virtToPhy((uint8_t *)BaseAddress);
    certHeader.debugResponse = DEBUG_RESPONSE_SUCCESS;

    /*
        !!!IMPORTANT!!!
        The default mode is DRYRUN_MODE. **No conversion** occurs in this mode.
        To convert a device change the certHeader.reserved field below to KEYWRITER_MODE .
    */
    certHeader.reserved = DRYRUN_MODE;
    //certHeader.reserved = KEYWRITER_MODE;

    blCtx.certAddr      = BaseAddress;
    blCtx.certType      = CERT_TYPE_KP_KEYCERT;
    blCtx.imageAddr     = BaseAddress + MAX_CERT_SIZE;
    blCtx.maxImageSize  = MAX_KEY_SIZE;
    blCtx.readDataCb    = &insertUartData;

    //
    // Boot Loader Init
    //
    status = bootloadInit();

    //
    // Boot loader Process, returns image size
    //
    ImageSize = bootloadProcessWithChecks(&blCtx);

    certHeader.certSize = g_bootLoadStatus.certSize + ImageSize;

    //
    // Receive and copy the application to LDA0 RAM
    //
    CopyApplicationToRAM(ImageSize, BaseAddress + g_bootLoadStatus.certSize);

    startCycleCount = CycleCounterP_getCount64();
    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_keyWriter(&gHSMClient, (KeyWriterCertHeader_t *)(&certHeader), ClockP_usecToTicks(7000000U)); // 7sec timeout, alternatively can use SystemP_WAIT_FOREVER
    endCycleCount = CycleCounterP_getCount64();

    if(authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt =
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1106,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation, 
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL 
        };
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    // TODO: embed prints into message strings
    char buffer[2048U], buffer1[128U];
    snprintf(buffer1, sizeof(buffer1), "\r\n\r\n[HSM CLIENT_PROFILE] Time taken to Process Key Certificate %uus\r\n", ((endCycleCount - startCycleCount) / cpuMHz));
    strcat(buffer, buffer1);
    snprintf(buffer1, sizeof(buffer1), "[HSM CLIENT] OTP-KW Error Status\n\n\r");
    strcat(buffer, buffer1);
    snprintf(buffer1, sizeof(buffer1), "[HSM CLIENT] OTP-KW debugResponse = 0x%08x\r\n", certHeader.debugResponse);
    strcat(buffer, buffer1);
    snprintf(buffer1, sizeof(buffer1), "[HSM CLIENT] OTP-KW Error phase = 0x%01x\r\n", (certHeader.debugResponse & DBGRSP_ERROR_PHASE_MASK));
    strcat(buffer, buffer1);
    snprintf(buffer1, sizeof(buffer1), "[HSM CLIENT] OTP-KW Error module = 0x%02x\r\n", (certHeader.debugResponse & DBGRSP_ERROR_MODULE_MASK) >> DBGRSP_ERROR_MODULE_SHIFT);
    strcat(buffer, buffer1);
    snprintf(buffer1, sizeof(buffer1), "[HSM CLIENT] OTP-KW Error stage = 0x%02x\r\n", (certHeader.debugResponse & DBGRSP_ERROR_STAGE_MASK) >> DBGRSP_ERROR_STAGE_SHIFT);
    strcat(buffer, buffer1);
    snprintf(buffer1, sizeof(buffer1), "[HSM CLIENT] OTP-KW Error customer key extension = 0x%01x\n\n\r", (certHeader.debugResponse & DBGRSP_ERROR_CUSTKEYEXTENSION_MASK) >> DBGRSP_ERROR_CUSTKEYEXTENSION_SHIFT);
    strcat(buffer, buffer1);

    // Temporary store to the trailing end of reserved buffer (LDA1 RAM).
    // So it appends to the key provision logs when getting outputted to the host.
    // (LDA1 RAM needs to be reserved as a scatchpad)
    strcpy((void *)((KP_LOG_ADDR + MAX_KP_LOG_SIZE) - 512U), (buffer));
    
    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return(authStatus);

}

//
// End of file
//