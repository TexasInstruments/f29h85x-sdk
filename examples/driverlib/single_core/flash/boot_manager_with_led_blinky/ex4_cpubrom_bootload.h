//###########################################################################
//
// FILE:   ex3_cpubrom_bootload.h
//
// TITLE:  BootROM Definitions.
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

#ifndef C_BOOTROM_BOOTLOAD_H_
#define C_BOOTROM_BOOTLOAD_H_
#include "bootrom.h"
//
//  Defines
//
#define MAX_CERT_SIZE               (4U * 1024U)

#define CERT_TYPE_DFU_CPU1                (0x00000001U)
#define CERT_TYPE_KP_HSMFW_IMAGE          (0x00010001U)
#define CERT_TYPE_KP_KEYCERT              (0x00010002U)
#define CERT_TYPE_CP_HSMFW_IMAGE          (0x00020001U)
#define CERT_TYPE_CP_APP_IMAGE            (0x00020002U)
#define CERT_TYPE_CP_C29_IMAGE            (0x00020003U)

//
//  ENUM
//


//
//  Structures
//
/**
 * @brief
 *  Bootload Context
 *
 * @details
 *  This is a Bootload Context Structure
 */
typedef uint32_t (*readDataCb_t)(uint32_t addr, uint32_t size);
typedef struct
{
    /**
     * @brief   Certificate Address
     */
    uint32_t      certAddr;

    /**
     * @brief   Certificate Type
     */
    uint32_t      certType;

    /**
     * @brief   Image Address
     */
    uint32_t      imageAddr;

    /**
     * @brief   Chunk Size
     */
    uint32_t      chunkSize;

    /**
     * @brief   Maximum Image Size
     */
    uint32_t      maxImageSize;


    /**
     * @brief   Callback function to read data from the peripheral
     */
    readDataCb_t  readDataCb;
} bootLoadCtx_t;

/**
 * @brief
 *  Bootload Status
 *
 * @details
 *  This is a Bootload runtime status Structure
 */
typedef struct
{
    /**
     * @brief   Flow status for Init function
     */
    status_t   init:2U;

    /**
     * @brief   Flow status for HELLO message
     */
    status_t   helloMsg:2U;

    /**
     * @brief   Flow status for Certificate Read
     */
    status_t   readCert:2U;

    /**
     * @brief   Flow status for CERT message
     */
    status_t   certMsg:2U;

    /**
     * @brief   Flow status for Get Image Size from Certificate
     */
    status_t   getImageSize:2U;

    /**
     * @brief   Flow status for Read Image block Error
     */
    status_t   readBlockErr:2U;

    /**
     * @brief   Flow status for ACK receive for CANCEL message Error
     */
    status_t   ackRcvErr:2U;

    /**
     * @brief   Flow status for CANCEL message Error
     */
    status_t   cancelMsgErr:2U;

    /**
     * @brief   Flow status for Timeout Error in sending IMAGE message
     */
    status_t   sendBlockSkipErr:2U;

    /**
     * @brief   Flow status for receiving RESULT message
     */
    status_t   resMsg:2U;

    /**
     * @brief   Flow status for Sending RESULT ACK message
     */
    status_t   resAck:2U;

    /**
     * @brief   Flow status for DeInit function
     */
    status_t   deInit:2U;

    /**
     * @brief   Total number of blocks in the image that are sent to HSM
     */
    uint32_t   numBlk;

    /**
     * @brief   Current block number sebt to HSM
     */
    uint32_t   blkCnt;

    /**
     * @brief   Size of the certificate
     */
    uint32_t   certSize;

    /**
     * @brief   Size of the Image
     */
    uint32_t   imageSize;

    /**
     * @brief   The current count of the IMAGE message skip
     */
    uint32_t   sendBlockSkip;


} bootLoadStatus_t;

//
//  Functions
//
extern uint32_t bootloadProcess(bootLoadCtx_t *blCtx);
extern void ClearFSMStatus(uint32_t u32StartAddress, uint32_t u32UserFlashConfig);
extern void EraseBanks(uint32_t u32StartAddress, uint32_t FlashConfig);
extern void sendCancelMsg(void);

#endif //C_BOOTROM_BOOTLOAD_H_