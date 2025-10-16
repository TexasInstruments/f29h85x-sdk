// ###########################################################################
//
//  FILE:    sbl_code_provisioning.c
//
//  TITLE:   Bootloader HS-SE code provisioning functions
//
// <h1> Bootloader HS-SE code provisioning </h1>
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

#include <ti_drivers_config.h>
#include <ti_dpl_config.h>
#include "sbl_code_provisioning.h"
#include "sbl_packet_interface.h"

/* Global variable declare in auto-gen file */
extern HsmClient_t gHSMClient;

//
// provisionApplicationImg
//
int32_t provisionApplicationImg(uint32_t BaseAddress)
{
    bootLoadCtx_t blCtx;
    uint32_t status = BROM_STATUS_OK;
    uint32_t loop;
    uint32_t ImageSize = 0;
    int32_t authStatus = SystemP_SUCCESS;

    blCtx.certAddr = BaseAddress;
    blCtx.imageAddr = BaseAddress + MAX_CERT_SIZE;
    blCtx.maxImageSize = getMaxFlashImageSize();
    blCtx.readDataCb = &insertUartData;
    blCtx.certType = CERT_TYPE_CP_APP_IMAGE;

    FirmwareUpdateReq_t firmwareUpdate;

    //
    // Boot Loader Init
    //
    status = bootloadInit();

    //
    // Boot loader Process, returns image size
    //
    ImageSize = bootloadProcessWithChecks(&blCtx);

    //
    // Boot load is successful, now exit LINK1 and copy the image to Flash memory
    //
    AuthenticateImageviaHSMRT(ImageSize, BaseAddress);

    //
    // Boot Load Deinit
    //
    bootloadDeInit();

    return (authStatus);
}

//
// provisionSecCfgImg
//
int32_t provisionSecCfgImg(uint32_t BaseAddress)
{
    FirmwareUpdateReq_t firmwareUpdate;
    uint32_t status = BROM_STATUS_OK;
    uint32_t ImageSize = 0;
    int32_t authStatus = SystemP_SUCCESS;

    //
    // Boot Loader Init
    //
    status = bootloadInit();
    
    //
    // Get Sec Cfg data to LDAx ram
    //
    sblGetDataArray((void*)BaseAddress, SEC_CFG_IMG_SIZE);

    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
    firmwareUpdate.dataLength = SEC_CFG_MAX_CHUNK_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CertProcess(&gHSMClient, &firmwareUpdate);

    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1201,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress + SEC_CFG_MAX_CHUNK_SIZE;
    firmwareUpdate.dataLength = SEC_CFG_MAX_CHUNK_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);

    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1202,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    firmwareUpdate.pStartAddress = (uint8_t *)NULL;
    firmwareUpdate.dataLength = 0;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CodeVerify(&gHSMClient, &firmwareUpdate);
    
    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1203,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress + (2*SEC_CFG_MAX_CHUNK_SIZE);
    firmwareUpdate.dataLength = SEC_CFG_MAX_CHUNK_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CertProcess(&gHSMClient, &firmwareUpdate);

    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1201,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress + (3*SEC_CFG_MAX_CHUNK_SIZE);
    firmwareUpdate.dataLength = SEC_CFG_MAX_CHUNK_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);

    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1202,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    firmwareUpdate.pStartAddress = (uint8_t *)NULL;
    firmwareUpdate.dataLength = 0;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CodeVerify(&gHSMClient, &firmwareUpdate);
    
    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1203,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress + (4*SEC_CFG_MAX_CHUNK_SIZE);
    firmwareUpdate.dataLength = SEC_CFG_MAX_CHUNK_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CertProcess(&gHSMClient, &firmwareUpdate);

    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1201,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress + (5*SEC_CFG_MAX_CHUNK_SIZE);
    firmwareUpdate.dataLength = SEC_CFG_MAX_CHUNK_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);

    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1202,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    firmwareUpdate.pStartAddress = (uint8_t *)NULL;
    firmwareUpdate.dataLength = 0;
    firmwareUpdate.bankMode = 0; // TBD

    // Wait for HSM IPC message that says keys are validated in LDAx RAM
    authStatus = HsmClient_firmwareUpdate_CodeVerify(&gHSMClient, &firmwareUpdate);
    
    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1203,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
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
int32_t AuthenticateImageviaHSMRT(uint32_t ImageSize, uint32_t BaseAddress)
{
    // Declare/initialize locals
    uint32_t bytesRemain = ImageSize;
    int32_t authStatus = SystemP_SUCCESS;
    FirmwareUpdateReq_t firmwareUpdate;

    // Populate parameters for certificate processing
    // Cert content has already been loaded to LDAx ram here
    firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
    firmwareUpdate.dataLength = MAX_CERT_SIZE;
    firmwareUpdate.bankMode = 0; // TBD

    // Process certificate to verify the authenticity of the incoming firmware
    authStatus = HsmClient_firmwareUpdate_CertProcess(&gHSMClient, &firmwareUpdate);

    if (authStatus != SystemP_SUCCESS)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1201,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    // Disable SSU Flash WEPROT
    //storeAndDisableFlashWEPROT();

    while (bytesRemain)
    {
        uint32_t allowableSize, programSize;
        allowableSize = (bytesRemain >= CP_CHUNK_SIZE) ? CP_CHUNK_SIZE : bytesRemain;

        // Receive the chunk post certificate from the host
        sblGetDataArray((void*)BaseAddress, allowableSize);

        // Add trailing padding to make sure it's 16byte aligned
        if (bytesRemain < CP_CHUNK_SIZE)
        {
            uint16_t numPadding = (allowableSize % 16U) ? 16U - (allowableSize % 16U) : 0U;
            memset((void*)(BaseAddress + allowableSize), 0xff, numPadding);
            programSize = allowableSize + numPadding;
        }
        else
        {
            programSize = allowableSize;
        }

        // Populate parameters to program the first receive chunk in flash
        firmwareUpdate.pStartAddress = (uint8_t *)BaseAddress;
        firmwareUpdate.dataLength = programSize;
        firmwareUpdate.bankMode = 0; // TBD

        // Program the first received chunk in flash
        authStatus = HsmClient_firmwareUpdate_CodeProgram(&gHSMClient, &firmwareUpdate);
        bytesRemain -= allowableSize;

        if (authStatus != SystemP_SUCCESS)
        {
            //restoreFlashWEPROT();
            const ErrorStatusPkt_t errPkt = 
            {
                .payloadType = (PayloadType)ErrorStatus,
                .errorMsgCode = 0x1202,              // error message decoded in comm_packet_protocol.h
                .recoveryStatus = RS_Unrecoverable,  
                .hasSprintfArgs = false,             
                .numArgs = 0U,                       
                .pArgsVal = NULL                     
            };
            //
            // send EOT packet and break out of routine
            //
            sblSendPacket(1, &errPkt);
            Example_Error();
        }
    }

    // Populate parameters to verify the programmed firmware in flash
    firmwareUpdate.pStartAddress = (uint8_t *)NULL;
    firmwareUpdate.dataLength = 0;
    firmwareUpdate.bankMode = 0; // TBD

    // Verify the programmed firmware and program the certificate in flash
    authStatus = HsmClient_firmwareUpdate_CodeVerify(&gHSMClient, &firmwareUpdate);

    if (authStatus != SystemP_SUCCESS)
    {
        //restoreFlashWEPROT();
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1203,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        Example_Error();
    }

    // Restore SSU Flash WEPROT
    //restoreFlashWEPROT();

    return (authStatus);
}

////
//// End of file
////