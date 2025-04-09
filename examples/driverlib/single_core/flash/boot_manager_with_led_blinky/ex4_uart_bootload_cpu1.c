//###########################################################################
//
// FILE:    ex3_uart_bootload_cpu1.c
//
// TITLE:   CPU1 System Boot
//
// CPU1 System Initialization and associated functions
//
//###########################################################################
// $TI Release: $
// $Release Date:   $
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

#include "ex4_uart_bootload_cpu1.h"


//
//  readCert
//
static uint32_t readCert(bootLoadCtx_t *blCtx)
{
    uint32_t      status     = BROM_STATUS_OK;
    uint32_t      certLength = 0U;
    Cert_Return_t certRet    = CERT_RETURN_SUCCESS;
    //
    //  Read first 4 bytes
    //
    status = blCtx->readDataCb(blCtx->certAddr, CONFIG_CERT_SIZE);
    if(BROM_STATUS_OK == status)
    {

        certRet = Cert_getLength((uint8_t*)blCtx->certAddr, CONFIG_CERT_SIZE, &certLength);

        //
        // Set certLength to 0x1000 (as shown in linker cmd file)
        //
        certLength = 0x1000;

        if((CERT_RETURN_SUCCESS == certRet) && (certLength <= MAX_CERT_SIZE))
        {

            //
            //  Read remaining certificate
            //
            status = blCtx->readDataCb(
                                blCtx->certAddr + CONFIG_CERT_SIZE,
                                (certLength - CONFIG_CERT_SIZE));
            if(BROM_STATUS_OK != status)
            {
                certLength = 0U;
            }
        }
        else
        {
            certLength = 0U;
        }
    }

    return (certLength);
}
//
//  resetBootLoadStatus
//
static void resetBootLoadStatus(void)
{
    //
    //  Init Boot Load Status execpt for init and HELLO message
    //
    g_bootLoadStatus.readCert         = STATUS_NA;
    g_bootLoadStatus.certMsg          = STATUS_NA;
    g_bootLoadStatus.getImageSize     = STATUS_NA;
    g_bootLoadStatus.readBlockErr     = STATUS_NA;
    g_bootLoadStatus.ackRcvErr        = STATUS_NA;
    g_bootLoadStatus.cancelMsgErr     = STATUS_NA;
    g_bootLoadStatus.sendBlockSkipErr = STATUS_NA;
    g_bootLoadStatus.resMsg           = STATUS_NA;
    g_bootLoadStatus.resAck           = STATUS_NA;
    g_bootLoadStatus.deInit           = STATUS_NA;
    g_bootLoadStatus.numBlk           = 0U;
    g_bootLoadStatus.blkCnt           = 0U;
    g_bootLoadStatus.certSize         = 0U;
    g_bootLoadStatus.imageSize        = 0U;
    g_bootLoadStatus.sendBlockSkip    = 0U;
}


//
//  bootloadProcess
//
uint32_t bootloadProcess(bootLoadCtx_t *blCtx)
{
    Cert_Return_t  certRet      = CERT_RETURN_SUCCESS;
    uint64_t       startCnt;
    uint32_t       status       = BROM_STATUS_OK;
    uint32_t       blStatus     = BROM_STATUS_FAIL;
    uint32_t       certLength   = 0U;
    uint32_t       curReadAddr  = BROM_INVALID_ADDR;
    uint32_t       curMsgAddr   = BROM_INVALID_ADDR;
    uint32_t       imageSize = 0;

        //
        //  Reset the boot load status
        //
        resetBootLoadStatus();
        //
        //  Get Certificate from the bootloader
        //
        certLength = readCert(blCtx);
        if(0U != certLength)
        {
            g_bootLoadStatus.readCert = STATUS_PASS;
            g_bootLoadStatus.certSize = certLength;

            if(BROM_STATUS_OK == status)
            {
                g_bootLoadStatus.certMsg = STATUS_PASS;
                //
                //  Get image size
                //
                certRet = Cert_getImageSize(&imageSize);

                return (imageSize);

            }
            else
            {
                g_bootLoadStatus.certMsg = STATUS_FAIL;
            }
        }
        else
        {
            //
            //  Cert read failed
            //
            status = BROM_STATUS_FAIL;
            g_bootLoadStatus.readCert = STATUS_FAIL;
        }

    return (imageSize);
}

