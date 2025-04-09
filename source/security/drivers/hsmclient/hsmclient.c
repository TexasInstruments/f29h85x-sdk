/*
 *  Copyright (C) 2022-24 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <security/drivers/secure_ipc_notify/sipc_notify.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/CacheP.h>
#include <security/drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/HwiP.h>
#include <security/drivers/hsmclient/hsmclient.h>
#include <security/drivers/hsmclient/hsmclient_msg.h>
#include <drivers/soc.h>
#include <string.h>
#include <kernel/dpl/DebugP.h>

void Hsmclient_updateBootNotificationRegister(void);

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * @brief
 *        Macro calculates the cache-aligned size for a given buffer or data structure
 */
#define GET_CACHE_ALIGNED_SIZE(x) ((x + CacheP_CACHELINE_ALIGNMENT) & ~(CacheP_CACHELINE_ALIGNMENT - 1))

/**
 * @brief
 *        Maximum size of the HSM client message queue
 *        For Streaming Secure Boot, the break up is as follows,
 *        1 start message (includes the certificate) +
 *        1 finish message +
 *        1 ELF Header Buffer update message + 1 PHT Buffer update message
 *        1024 ELF segment update messages (including the two note segments)
 *          - PT note for boot sequence info
 *          - PT note containing Random string for decryption verification
 */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* This variable indicates HSM Runtime load status */
volatile uint32_t gHsmrtLoadStatus = HSMRT_LOAD_NOT_REQUESTED;

/* This variable indicates Secure Boot status */
static volatile int32_t gSecureBootStatus = SystemP_SUCCESS;

/* This variable indicates whether Boot notification is received or not */
static volatile int32_t gBootNotificationReceived = SystemP_FAILURE;

static int32_t gLastSentIndex = -1;
static int32_t gLastEnqueuedIndex = -1;
static int32_t gNum_HsmRequestSent = 0;
static volatile int32_t gNum_HsmResponseReceived = 0;
static uint32_t hsm_client_msg_queue_size = 64U;

/* Queue used to store HSM client messages that need to be dispatched via SIPC */
extern HsmMsg_t gHsmClientMsgQueue[];

/*==========================================================================
 *                        Static Function Declarations
 *==========================================================================*/

/**
 * @brief
 *        Calculate crc16_ccit for a given data.
 * @param data data pointer
 * @param length data length
 * @return 16 bit crc calculated from given data.
 */
static uint16_t crc16_ccit(uint8_t *data, uint16_t length);

/**
 * @brief
 *      Generic send and receive message api
 * @param HsmClient client type
 * @param timeout time to wait for interrupt from HSM before throwing timeout
 *                exception.
 * @return SystemP_SUCCESS if transaction is successful else SystemP_FAILURE.
 */
static int32_t HsmClient_SendAndRecv(HsmClient_t *HsmClient, uint32_t timeout);

/**
 * @brief
 *      Generic send message api which enqueus the message in HSM client message
 *      queue and tries to send the message via SIPC.
 *      This API is non blocking in nature.
 * @param message message that needs to be sent to the HSM core.
 * @return SystemP_SUCCESS if transaction is successful else SystemP_FAILURE.
 */
static int32_t HsmClient_EnqueueAndSendMsg(HsmMsg_t message);

/**
 * @brief
 *      Generic send message api which enqueus the message in HSM client message
 *      queue and ensures all the messages present in the queue are sent via SIPC.
 *      This API is blocking in nature.
 * @param message message that needs to be sent to the HSM core
 * @return SystemP_SUCCESS if transaction is successful else SystemP_FAILURE.
 */
static int32_t HsmClient_EnqueueAndSendMsgBlocking(HsmMsg_t message);

/**
 * @brief
 *      Generic api which waits for all responses to be received
 * @return SystemP_SUCCESS if all responses are successful else SystemP_FAILURE.
 */
static int32_t HsmClient_waitForAllResponses();

/*==============================================================================*
 *                          Static Functions definition.
 *==============================================================================*/

/* CRC 16 CCIT soft implementation */
static uint16_t crc16_ccit(uint8_t *data, uint16_t length)
{
    uint8_t x;
    uint16_t crc = 0xFFFF;

    while (length--)
    {
        x = crc >> 8 ^ *data++;
        x ^= x >> 4;
        crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x << 5)) ^ ((uint16_t)x);
    }
    return crc;
}

static int32_t HsmClient_EnqueueAndSendMsg(HsmMsg_t message)
{
    int32_t status = SystemP_FAILURE;
    uint8_t localClientId = message.srcClientId;
    uint8_t remoteClientId = message.destClientId;

    message.crcMsg = crc16_ccit((uint8_t *)&message, (sizeof(HsmMsg_t) - 2));

	if (gLastEnqueuedIndex < (int32_t)(hsm_client_msg_queue_size - 1))
	{
		gHsmClientMsgQueue[++gLastEnqueuedIndex] = message;

        /* Till the boot notify is not received, simply enqueue the message */
        if (gBootNotificationReceived == SystemP_SUCCESS)
        {
            while ((gSecureBootStatus == SystemP_SUCCESS) && (gLastSentIndex < gLastEnqueuedIndex))
            {
                /*
                    Do not wait in case the SIPC software Queue is full and simply abort with error.
                    This is done in order to make this call non blocking.
                */
                status = SIPC_sendMsg(CORE_INDEX_HSM, remoteClientId, localClientId,
                                      (uint8_t *)&gHsmClientMsgQueue[gLastSentIndex + 1], ABORT_ON_FIFO_FULL);

                /* Successfully able to send the message via SIPC */
                if (status == SystemP_SUCCESS)
                {
                    gNum_HsmRequestSent++;
                    gLastSentIndex++;
                }
                /*
                    Failed to send the message because the SIPC Software FIFO is full.
                    Retry in the next call to this function or in the finish call.
                */
                else if (status == SystemP_FAILURE)
                {
                    status = SystemP_SUCCESS;
                    break;
                }
                else
                {
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }
        else
        {
            status = SystemP_SUCCESS;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t HsmClient_EnqueueAndSendMsgBlocking(HsmMsg_t message)
{
    int32_t status = SystemP_FAILURE;
    uint8_t localClientId = message.srcClientId;
    uint8_t remoteClientId = message.destClientId;

    message.crcMsg = crc16_ccit((uint8_t *)&message, (sizeof(HsmMsg_t) - 2));

	if (gLastEnqueuedIndex < (int32_t)(hsm_client_msg_queue_size - 1))
	{
		gHsmClientMsgQueue[++gLastEnqueuedIndex] = message;

        /*
            If the boot notification is not received, we wait for it indefinitely
            and once it arrives we begin sending our request packets.
        */
        status = HsmClient_checkAndWaitForBootNotification();

        if (status == SystemP_SUCCESS)
        {
            while ((gSecureBootStatus == SystemP_SUCCESS) && (gLastSentIndex < gLastEnqueuedIndex))
            {
                /*
                    In this call, we want to wait in case the SIPC software Queue is full
                    and we simply abort with error. This is done in order to make sure that
                    all the requests to HSM are sent in order.
                */
                status = SIPC_sendMsg(CORE_INDEX_HSM, remoteClientId, localClientId,
                                      (uint8_t *)&gHsmClientMsgQueue[gLastSentIndex + 1], WAIT_IF_FIFO_FULL);

                if (status == SystemP_SUCCESS)
                {
                    gNum_HsmRequestSent++;
                    gLastSentIndex++;
                }
                else
                {
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t HsmClient_waitForAllResponses()
{
    while ((gSecureBootStatus == SystemP_SUCCESS) && (gNum_HsmResponseReceived < gNum_HsmRequestSent))
    {
    }

    return gSecureBootStatus;
}

static int32_t HsmClient_SendAndRecv(HsmClient_t *HsmClient, uint32_t timeout)
{
    uint8_t localClientId;
    uint8_t remoteClientId;
    int32_t status;
    uint16_t crcMsg;

    localClientId = HsmClient->ReqMsg.srcClientId;
    remoteClientId = HsmClient->ReqMsg.destClientId;

    /* Add message crc. Exclude crcMsg argument of HsmMsg_t from crc calculations*/
    HsmClient->ReqMsg.crcMsg = crc16_ccit((uint8_t *)&HsmClient->ReqMsg, (sizeof(HsmMsg_t) - 2));
    SemaphoreP_constructBinary(&HsmClient->Semaphore, 0);

    status = SIPC_sendMsg(CORE_INDEX_HSM, remoteClientId, localClientId,
                          (uint8_t *)&HsmClient->ReqMsg, WAIT_IF_FIFO_FULL);
    if (status == SystemP_SUCCESS)
    {
        status = SemaphoreP_pend(&HsmClient->Semaphore, timeout);
        if (status == SystemP_FAILURE)
        {
            return SystemP_FAILURE;
        }
        else if (status == SystemP_TIMEOUT)
        {
            DebugP_log("\r\n [HSM_CLIENT] Timeout exception \r\n");
            return SystemP_TIMEOUT;
        }
        else
        {
            crcMsg = crc16_ccit((uint8_t *)&HsmClient->RespMsg, SIPC_MSG_SIZE - 2);
            /* if the message is okay then send whatever the flag receive */
            if (crcMsg == HsmClient->RespMsg.crcMsg)
            {
                HsmClient->RespFlag = HsmClient->RespMsg.flags;
                status = SystemP_SUCCESS;
            }
            /* corrupted message received */
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] Corrupted message received \r\n");
                HsmClient->RespFlag = HSM_FLAG_NACK;
                status = SystemP_FAILURE;
            }
            return status;
        }
    }
    else
    {
        return status;
    }
}

/*==============================================================================*
 *                          Public Function definition.
 *==============================================================================*/

void HsmClient_isr(uint8_t remoteCoreId, uint8_t localClientId,
                   uint8_t remoteClientId, uint8_t *msgValue, void *args)
{
    HsmClient_t *HsmClient = (HsmClient_t *)args;

    /* here we will just post the semaphore */
    /* copy message to client response variable */
    /* As this ISR is blocking, quickly copy the message and exit ISR */
    memcpy(&HsmClient->RespMsg, msgValue, SIPC_MSG_SIZE);
    SemaphoreP_post(&HsmClient->Semaphore);

    /*
        Analyze the received response packet.
    */
    if (HsmClient->RespMsg.serType == HSM_MSG_BOOT_NOTIFY)
    {
        gBootNotificationReceived = SystemP_SUCCESS;
        gSecureBootStatus = SystemP_SUCCESS;

        Hsmclient_updateBootNotificationRegister();
    }
    else
    {
        if (gSecureBootStatus == SystemP_SUCCESS)
        {
            gNum_HsmResponseReceived++;
            if (HsmClient->RespMsg.flags == HSM_FLAG_NACK)
            {
                gSecureBootStatus = SystemP_FAILURE;
            }
            else if (HsmClient->RespMsg.flags == HSM_FLAG_ACK)
            {
                gSecureBootStatus = SystemP_SUCCESS;
            }
            else
            {
                gSecureBootStatus = SystemP_FAILURE;
            }
        }
        else
        {
            gSecureBootStatus = SystemP_FAILURE;
        }
    }
}

int32_t HsmClient_checkAndWaitForBootNotification(void)
{
    int32_t status = SystemP_FAILURE;

    if (gHsmrtLoadStatus == HSMRT_LOAD_NOT_REQUESTED)
    {
        /*
           If HSM Runtime load is not requested up till now,
           just return Success.
       */
        status = SystemP_SUCCESS;
    }
    else if (gHsmrtLoadStatus == HSMRT_LOAD_REQUESTED)
    {
        /* Only wait if HSM Runtime load is requested up till now. */
        while (gHsmrtLoadStatus == HSMRT_LOAD_REQUESTED)
        {
        }

        if (gHsmrtLoadStatus == HSMRT_LOAD_SUCCEEDED)
        {
            /* Only wait for Boot notification HSM Runtime load is successful */
            while (gBootNotificationReceived == SystemP_FAILURE)
            {
            }
            status = SystemP_SUCCESS;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    else if (gHsmrtLoadStatus == HSMRT_LOAD_FAILED)
    {
        status = SystemP_FAILURE;
    }
    else if (gHsmrtLoadStatus == HSMRT_LOAD_SUCCEEDED)
    {
        /* Only wait for Boot notification HSM Runtime load is successful */
        while (gBootNotificationReceived == SystemP_FAILURE)
        {
        }
        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

/* return SystemP_FAILURE if clientId is greater the max or
 * A callback has been registered. already */
int32_t HsmClient_register(HsmClient_t *HsmClient, uint8_t clientId)
{
    uint8_t status;

    if (HsmClient == NULL)
    {
        DebugP_log(" \r\n [HSM_CLIENT] HsmCliet_t type error. \r\n");
        return SystemP_FAILURE;
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    HsmClient->ClientId = clientId;

    /* register HSM_Isr and pass the pointer as args */
    status = SIPC_registerClient(clientId, HsmClient_isr, (void *)HsmClient);
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("\r\n [HSM_CLIENT] New Client Registered with Client Id = %d\r\n ", clientId);
    }
    else
    {
        DebugP_log(" \r\n [HSM_CLIENT] Client already registered or Invalid ClientId\r\n");
    }
    return status;
}

int32_t HsmClient_init(SIPC_Params *params)
{
    /* get the params and do SIPC init */
    int32_t status;
    uint32_t selfCoreId;
    status = SIPC_init(params);
    /* TODO: keyrings initialization */
    if (status == SystemP_FAILURE)
    {
        selfCoreId = SIPC_getSelfCoreId();
        DebugP_log("[HSM_CLIENT] Secure Host initialization failed for R5F%d \r\n", selfCoreId);
    }
    return status;
}

void HsmClient_SecureBootQueueInit(uint32_t configured_hsm_client_msg_queue_size){
    /* Customize the size of the HSM client message queue*/
    hsm_client_msg_queue_size = configured_hsm_client_msg_queue_size; 
}

/* do sipc deinit */
void HsmClient_deinit(void)
{
    SIPC_deInit();
}

void HsmClient_unregister(HsmClient_t *HsmClient, uint8_t clientId)
{
    /* unregister a client */
    SIPC_unregisterClient(clientId);
}

int32_t HsmClient_getVersion(HsmClient_t *HsmClient,
                             HsmVer_t *hsmVer, uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_VERSION;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)hsmVer, sizeof(HsmVer_t));

    /* Change the Arguments Address in Physical Address */
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(hsmVer);

    /*
       Write back the HsmVer struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(hsmVer, GET_CACHE_ALIGNED_SIZE(sizeof(HsmVer_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);

    if (status == SystemP_SUCCESS)
    {
        /* the hsmVer has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Get version request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), sizeof(HsmVer_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for getversion response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getUID(HsmClient_t *HsmClient,
                         uint8_t *uid, uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_UID;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)uid, HSM_UID_SIZE);

    /* Change the Arguments Address in Physical Address */
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(uid);

    /*
       Write back the uid and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(uid, GET_CACHE_ALIGNED_SIZE(sizeof(uid)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the getUID has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Get UID request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, HSM_UID_SIZE);
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for getUID response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_openDbgFirewall(HsmClient_t *HsmClient,
                                  uint8_t *cert,
                                  uint32_t cert_size,
                                  uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_OPEN_DBG_FIREWALLS;
    HsmClient->ReqMsg.args = (void *)cert;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)cert, cert_size);

    /* Change the Arguments Address in Physical Address */
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(cert);

    /*
       Write back the debug cert and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(cert, GET_CACHE_ALIGNED_SIZE(cert_size), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] OpenDbgFirewall request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0U);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for openDbgFirewall response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_importKeyring(HsmClient_t *HsmClient,
                                uint8_t *cert,
                                uint32_t cert_size,
                                uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_KEYRING_IMPORT;
    HsmClient->ReqMsg.args = (void *)cert;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)cert, cert_size);

    /* Change the Arguments Address in Physical Address */
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(cert);

    /*
       Write back the keyring cert and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(cert, GET_CACHE_ALIGNED_SIZE(cert_size), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Import Keyring request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0U);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for Import Keyring response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_readOTPRow(HsmClient_t *HsmClient,
                             EfuseRead_t *readRow)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_READ_OTP_ROW;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(readRow);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)readRow, sizeof(EfuseRead_t));

    /*
       Write back the EfuseRead struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(readRow, GET_CACHE_ALIGNED_SIZE(sizeof(EfuseRead_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Read OTP row request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {

            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(EfuseRead_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for read OTP Row response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_writeOTPRow(HsmClient_t *HsmClient,
                              EfuseRowWrite_t *writeRow)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_WRITE_OTP_ROW;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(writeRow);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)writeRow, sizeof(EfuseRowWrite_t));

    /*
       Write back the EfuseRowWrite struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(writeRow, GET_CACHE_ALIGNED_SIZE(sizeof(EfuseRowWrite_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the extended otp row has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Write OTP row request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(EfuseRowWrite_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for Write OTP row response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_lockOTPRow(HsmClient_t *HsmClient,
                             EfuseRowProt_t *protRow)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_PROT_OTP_ROW;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(protRow);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)protRow, sizeof(EfuseRowProt_t));

    /*
       Write back the EfuseRowProt struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(protRow, GET_CACHE_ALIGNED_SIZE(sizeof(EfuseRowProt_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the row is locked by HSM server if this
         * request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Extended OTP row protection request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(EfuseRowProt_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for extended OTP row protection response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getOTPRowCount(HsmClient_t *HsmClient,
                                 EfuseRowCount_t *rowCount)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_OTP_ROW_COUNT;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(rowCount);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)rowCount, sizeof(EfuseRowCount_t));

    /*
       Write back the EfuseRowCount struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(rowCount, GET_CACHE_ALIGNED_SIZE(sizeof(EfuseRowCount_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the rowCount has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Get OTP row count request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(EfuseRowCount_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for get OTP Row count response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getOTPRowProtection(HsmClient_t *HsmClient,
                                      EfuseRowProt_t *rowProt)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_OTP_ROW_PROT;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(rowProt);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)rowProt, sizeof(EfuseRowProt_t));

    /*
       Write back the EfuseRowProt struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(rowProt, GET_CACHE_ALIGNED_SIZE(sizeof(EfuseRowProt_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the rowProt has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Get OTP row protection request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(EfuseRowProt_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for get OTP Row protection response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_procAuthBoot(HsmClient_t *HsmClient,
                               uint8_t *cert,
                               uint32_t cert_size,
                               uint32_t timeout)
{
    /* make the message */
    int32_t status = SystemP_FAILURE;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_PROC_AUTH_BOOT;
    HsmClient->ReqMsg.args = (void *)cert;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)cert, cert_size);

    /* Change the Arguments Address in Physical Address */
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(cert);

    /*
        Write back the cert and
        invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(cert, GET_CACHE_ALIGNED_SIZE(cert_size), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Proc_Auth_Boot request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0U);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for Proc_Auth_Boot response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_procAuthBootStart(HsmClient_t *HsmClient,
                                    SecureBoot_Stream_t *secureBootInfo)
{
    int32_t status = SystemP_FAILURE;
    /* Create the message object */
    HsmMsg_t startMsg;

    /*populate the send message structure */
    startMsg.destClientId = HSM_CLIENT_ID_1;
    startMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    startMsg.flags = HSM_FLAG_AOP;
    startMsg.serType = HSM_MSG_PROC_AUTH_BOOT_START;
    startMsg.args = (void *)secureBootInfo;

    /* Add arg crc */
    startMsg.crcArgs = crc16_ccit((uint8_t *)secureBootInfo, sizeof(SecureBoot_Stream_t));

    /* Change the Arguments Address in Physical Address */
    startMsg.args = (void *)(uintptr_t)SOC_virtToPhy(secureBootInfo);

    /*
       Write back secure boot info object  and the data it contains
       to Shared memory invalidate the caches before passing it to HSM
    */
    CacheP_wbInv(secureBootInfo->dataIn, GET_CACHE_ALIGNED_SIZE(secureBootInfo->dataLen), CacheP_TYPE_ALLD);
    CacheP_wbInv(secureBootInfo, GET_CACHE_ALIGNED_SIZE(sizeof(SecureBoot_Stream_t)), CacheP_TYPE_ALLD);

    status = HsmClient_EnqueueAndSendMsg(startMsg);

    return status;
}

int32_t HsmClient_procAuthBootUpdate(HsmClient_t *HsmClient,
                                     SecureBoot_Stream_t *secureBootInfo)
{

    int32_t status = SystemP_FAILURE;
    /* Create the message object */
    HsmMsg_t updateMsg;

    /*populate the send message structure */
    updateMsg.destClientId = HSM_CLIENT_ID_1;
    updateMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    updateMsg.flags = HSM_FLAG_AOP;
    updateMsg.serType = HSM_MSG_PROC_AUTH_BOOT_UPDATE;
    updateMsg.args = (void *)secureBootInfo;

    /* Add arg crc */
    updateMsg.crcArgs = crc16_ccit((uint8_t *)secureBootInfo, sizeof(SecureBoot_Stream_t));

    /* Change the Arguments Address in Physical Address */
    updateMsg.args = (void *)(uintptr_t)SOC_virtToPhy(secureBootInfo);

    /*
       Write back secure boot info object to Shared memory
       invalidate the caches before passing it to HSM
    */
    CacheP_wbInv(secureBootInfo, GET_CACHE_ALIGNED_SIZE(sizeof(SecureBoot_Stream_t)), CacheP_TYPE_ALLD);

    status = HsmClient_EnqueueAndSendMsg(updateMsg);

    return status;
}

int32_t HsmClient_procAuthBootFinish(HsmClient_t *HsmClient,
                                     SecureBoot_Stream_t *secureBootInfo)
{

    int32_t status = SystemP_FAILURE;
    /* Create the message object */
    HsmMsg_t finishMsg;

    /*populate the send message structure */
    finishMsg.destClientId = HSM_CLIENT_ID_1;
    finishMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    finishMsg.flags = HSM_FLAG_AOP;
    finishMsg.serType = HSM_MSG_PROC_AUTH_BOOT_FINISH;
    finishMsg.args = (void *)secureBootInfo;

    /* Add arg crc */
    finishMsg.crcArgs = crc16_ccit((uint8_t *)secureBootInfo, sizeof(SecureBoot_Stream_t));

    /* Change the Arguments Address in Physical Address */
    finishMsg.args = (void *)(uintptr_t)SOC_virtToPhy(secureBootInfo);

    /*
       Write back secure boot info object to Shared memory
       invalidate the caches before passing it to HSM
    */
    CacheP_wbInv(secureBootInfo, GET_CACHE_ALIGNED_SIZE(sizeof(SecureBoot_Stream_t)), CacheP_TYPE_ALLD);

    status = HsmClient_EnqueueAndSendMsgBlocking(finishMsg);

    if (status == SystemP_SUCCESS)
    {
        status = HsmClient_waitForAllResponses();
    }

    return status;
}

int32_t HsmClient_setFirewall(HsmClient_t *HsmClient,
                              FirewallReq_t *FirewallReqObj,
                              uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint16_t crcFirewallRegionArr;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_SET_FIREWALL;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(FirewallReqObj);

    /* Calculates CRC of the array containing firewall regions to be configured */
    crcFirewallRegionArr = crc16_ccit((uint8_t *)FirewallReqObj->FirewallRegionArr, ((FirewallReqObj->regionCount) * sizeof(FirewallRegionReq_t)));
    FirewallReqObj->crcArr = crcFirewallRegionArr;
    FirewallReqObj->FirewallRegionArr = (FirewallRegionReq_t *)(uintptr_t)SOC_virtToPhy(FirewallReqObj->FirewallRegionArr);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)FirewallReqObj, sizeof(FirewallReq_t));

    /*
       Write back the FirewallReqObj and FirewallRegionArr
    */
    CacheP_wbInv((void *)FirewallReqObj, GET_CACHE_ALIGNED_SIZE(sizeof(FirewallReq_t)), CacheP_TYPE_ALL);
    CacheP_wbInv((void *)FirewallReqObj->FirewallRegionArr, GET_CACHE_ALIGNED_SIZE(((FirewallReqObj->regionCount) * sizeof(FirewallRegionReq_t))), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the firewall regions has been configured by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Set firewall request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            CacheP_inv((void *)HsmClient->RespMsg.args, GET_CACHE_ALIGNED_SIZE(sizeof(FirewallReq_t)), CacheP_TYPE_ALL);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(FirewallReq_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for set firewall response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_FirewallIntr(HsmClient_t *HsmClient,
                               FirewallIntrReq_t *FirewallIntrReqObj,
                               uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_SET_FIREWALL_INTR;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(FirewallIntrReqObj);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)FirewallIntrReqObj, sizeof(FirewallIntrReq_t));

    /*
       Write back the FirewallIntrReq_t struct
    */
    CacheP_wbInv((void *)FirewallIntrReqObj, GET_CACHE_ALIGNED_SIZE(sizeof(FirewallIntrReq_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the firewall interrupt request has been honored by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] firewall interrupt request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            CacheP_inv((void *)HsmClient->RespMsg.args, GET_CACHE_ALIGNED_SIZE(sizeof(FirewallIntrReq_t)), CacheP_TYPE_ALL);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(FirewallIntrReq_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for firewall interrupt response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getDKEK(HsmClient_t *HsmClient,
                          DKEK_t *getDKEK,
                          uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_DKEK;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(getDKEK);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)getDKEK, sizeof(DKEK_t));

    /*
       Write back the DKEK_t struct
    */
    CacheP_wbInv((void *)getDKEK, GET_CACHE_ALIGNED_SIZE(sizeof(getDKEK)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Get DKEK request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {

            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(DKEK_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for get DKEK response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_keyWriter(HsmClient_t *HsmClient, KeyWriterCertHeader_t *certHeader, uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_KEYWRITER_SEND_CUST_KEY_CERT;
    HsmClient->ReqMsg.args = (void *)certHeader;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)certHeader, sizeof(KeyWriterCertHeader_t));

    /* Change the Arguments Address in Physical Address */
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(certHeader);

    /*
       Write back the KwrCertHeader struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(certHeader, GET_CACHE_ALIGNED_SIZE(sizeof(KeyWriterCertHeader_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);

    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] KeyWriter customer key certificate send request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(KeyWriterCertHeader_t));

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for KeyWriter customer key certificate send response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_readSWRev(HsmClient_t *HsmClient,
                            SWRev_t *readSWRev)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_READ_SWREV;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(readSWRev);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)readSWRev, sizeof(SWRev_t));

    /*
       Write back the SWRev_t struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(readSWRev, GET_CACHE_ALIGNED_SIZE(sizeof(SWRev_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Read SWRev request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {

            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(SWRev_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for read SWRev response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_writeSWRev(HsmClient_t *HsmClient,
                             SWRev_t *writeSWRev)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_WRITE_SWREV;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(writeSWRev);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)writeSWRev, sizeof(SWRev_t));

    /*
       Write back the SWRev_t struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(writeSWRev, GET_CACHE_ALIGNED_SIZE(sizeof(SWRev_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Write SWRev request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {

            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(SWRev_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for write SWRev response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getRandomNum(HsmClient_t *HsmClient,
                               RNGReq_t *getRandomNum)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_RAND;
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(getRandomNum);

    getRandomNum->resultPtr = (uint8_t *)(uintptr_t)SOC_virtToPhy(getRandomNum->resultPtr);
    getRandomNum->resultLengthPtr = (uint32_t *)(uintptr_t)SOC_virtToPhy(getRandomNum->resultLengthPtr);
    getRandomNum->seedValue = (uint32_t *)(uintptr_t)SOC_virtToPhy(getRandomNum->seedValue);

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)getRandomNum, sizeof(RNGReq_t));

    /*
       Write back the RNGReq_t struct and
       invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(getRandomNum, GET_CACHE_ALIGNED_SIZE(sizeof(RNGReq_t)), CacheP_TYPE_ALL);
    CacheP_wbInv(getRandomNum->seedValue, GET_CACHE_ALIGNED_SIZE((getRandomNum->seedSizeInDWords) * 4), CacheP_TYPE_ALL);
    CacheP_wbInv(getRandomNum->resultLengthPtr, GET_CACHE_ALIGNED_SIZE(sizeof(uint32_t)), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] Get Random Number request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {

            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);
            CacheP_inv((void *)HsmClient->RespMsg.args, GET_CACHE_ALIGNED_SIZE(sizeof(RNGReq_t)), CacheP_TYPE_ALL);
            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(RNGReq_t));

            ((RNGReq_t *)HsmClient->RespMsg.args)->resultPtr = (uint8_t *)SOC_phyToVirt((uint64_t)(((RNGReq_t *)HsmClient->RespMsg.args)->resultPtr));
            ((RNGReq_t *)HsmClient->RespMsg.args)->resultLengthPtr = (uint32_t *)SOC_phyToVirt((uint64_t)(((RNGReq_t *)HsmClient->RespMsg.args)->resultLengthPtr));
            ((RNGReq_t *)HsmClient->RespMsg.args)->seedValue = (uint32_t *)SOC_phyToVirt((uint64_t)(((RNGReq_t *)HsmClient->RespMsg.args)->seedValue));
            CacheP_inv((void *)((RNGReq_t *)HsmClient->RespMsg.args)->resultPtr, GET_CACHE_ALIGNED_SIZE(((uint32_t)*(((RNGReq_t *)HsmClient->RespMsg.args)->resultPtr))), CacheP_TYPE_ALL);
            CacheP_inv((void *)((RNGReq_t *)HsmClient->RespMsg.args)->resultLengthPtr, GET_CACHE_ALIGNED_SIZE(((uint32_t)*(((RNGReq_t *)HsmClient->RespMsg.args)->resultLengthPtr))), CacheP_TYPE_ALL);
            CacheP_inv((void *)((RNGReq_t *)HsmClient->RespMsg.args)->seedValue, GET_CACHE_ALIGNED_SIZE(((uint32_t)*(((RNGReq_t *)HsmClient->RespMsg.args)->seedValue))), CacheP_TYPE_ALL);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for Get RandomNumber response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_firmwareUpdate_CertProcess(HsmClient_t *HsmClient,
                                             FirmwareUpdateReq_t *pFirmwareUpdateObject)
{
    int32_t status = SystemP_SUCCESS;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /* Proceed only if no previous firmware update API calls have been made, or HsmClient_firmwareUpdate_CodeVerify API is called */
    if (SystemP_SUCCESS == status)
    {

        /*populate the send message structure */
        HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
        HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

        /* Always expect acknowledgement from HSM server */
        HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
        HsmClient->ReqMsg.serType = HSM_MSG_FW_UPDATE_CERT_PROCESS;
    }
    else
    {
        /* Do nothing */
    }

    /* Proceed only if address and size check falls within bounds */
    if (SystemP_SUCCESS == status)
    {
        /* Change the certificate start address to HSM address space */
        pFirmwareUpdateObject->pStartAddress = (uint8_t *)(uintptr_t)SOC_virtToPhy(pFirmwareUpdateObject->pStartAddress);
        /* Add arg crc */
        HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)pFirmwareUpdateObject, sizeof(FirmwareUpdateReq_t));
        /* Change the Arguments Address in Physical Address */
        HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(pFirmwareUpdateObject);

        /*
        Write back the HsmVer struct and
        invalidate the cache before passing it to HSM
        */
        CacheP_wbInv(pFirmwareUpdateObject, GET_CACHE_ALIGNED_SIZE(sizeof(FirmwareUpdateReq_t)), CacheP_TYPE_ALL);
        status = HsmClient_SendAndRecv(HsmClient, timeout);

        if (status == SystemP_SUCCESS)
        {
            /* the FW update cert process request has been completed by HSM server
             * if this request has been processed correctly */
            if (HsmClient->RespFlag == HSM_FLAG_NACK)
            {
                DebugP_log("\r\n [HSM_CLIENT] Firmware update certificate processing request NACKed by HSM server\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                /* Change the Arguments Address in Physical Address */
                HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);
                /* check the integrity of args */
                crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), 0);
                if (crcArgs == HsmClient->RespMsg.crcArgs)
                {
                    status = SystemP_SUCCESS;
                }
                else
                {
                    DebugP_log("\r\n [HSM_CLIENT] CRC check for firmware update certificate process response failed \r\n");
                    status = SystemP_FAILURE;
                }
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return status;
}

int32_t HsmClient_firmwareUpdate_CodeProgram(HsmClient_t *HsmClient,
                                             FirmwareUpdateReq_t *pFirmwareUpdateObject)
{
    int32_t status = SystemP_SUCCESS;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /* Proceed only if HsmClient_firmwareUpdate_CertProcess API call has been made */
    if (SystemP_SUCCESS == status)
    {
        /*populate the send message structure */
        HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
        HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

        /* Always expect acknowledgement from HSM server */
        HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
        HsmClient->ReqMsg.serType = HSM_MSG_FW_UPDATE_CODE_PROGRAM;
    }
    else
    {
        /* Do nothing */
    }

    /* Proceed only if address and size check falls within bounds */
    if (SystemP_SUCCESS == status)
    {
        /* Change the certificate start address to HSM address space */
        pFirmwareUpdateObject->pStartAddress = (uint8_t *)(uintptr_t)SOC_virtToPhy(pFirmwareUpdateObject->pStartAddress);
        /* Add arg crc */
        HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)pFirmwareUpdateObject, sizeof(FirmwareUpdateReq_t));
        /* Change the Arguments Address in Physical Address */
        HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(pFirmwareUpdateObject);

        /*
        Write back the HsmVer struct and
        invalidate the cache before passing it to HSM
        */
        CacheP_wbInv(pFirmwareUpdateObject, GET_CACHE_ALIGNED_SIZE(sizeof(FirmwareUpdateReq_t)), CacheP_TYPE_ALL);
        status = HsmClient_SendAndRecv(HsmClient, timeout);

        if (status == SystemP_SUCCESS)
        {
            /* the FW update cert process request has been completed by HSM server
             * if this request has been processed correctly */
            if (HsmClient->RespFlag == HSM_FLAG_NACK)
            {
                DebugP_log("\r\n [HSM_CLIENT] Firmware update code programming request NACKed by HSM server\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                /* Change the Arguments Address in Physical Address */
                HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);
                /* check the integrity of args */
                crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), 0);
                if (crcArgs == HsmClient->RespMsg.crcArgs)
                {
                    status = SystemP_SUCCESS;
                }
                else
                {
                    DebugP_log("\r\n [HSM_CLIENT] CRC check for firmware update code programming response failed \r\n");
                    status = SystemP_FAILURE;
                }
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return status;
}

int32_t HsmClient_firmwareUpdate_CodeVerify(HsmClient_t *HsmClient,
                                            FirmwareUpdateReq_t *pFirmwareUpdateObject)
{
    int32_t status = SystemP_SUCCESS;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /* Proceed only if HsmClient_firmwareUpdate_CodeProgram API call has been made */
    if (SystemP_SUCCESS == status)
    {
        /*populate the send message structure */
        HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
        HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

        /* Always expect acknowledgement from HSM server */
        HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
        HsmClient->ReqMsg.serType = HSM_MSG_FW_UPDATE_CODE_VERIFY;

        /* Address and size check */
        if ((pFirmwareUpdateObject->pStartAddress == NULL) && (pFirmwareUpdateObject->dataLength == 0))
        {
            status = SystemP_SUCCESS;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }

    /* Proceed only if address and size check falls within bounds */
    if (SystemP_SUCCESS == status)
    {
        /* Add arg crc */
        HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)pFirmwareUpdateObject, 0);
        /* Change the Arguments Address in Physical Address */
        HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(pFirmwareUpdateObject);

        /*
        Write back the HsmVer struct and
        invalidate the cache before passing it to HSM
        */
        CacheP_wbInv(pFirmwareUpdateObject, GET_CACHE_ALIGNED_SIZE(sizeof(FirmwareUpdateReq_t)), CacheP_TYPE_ALL);
        status = HsmClient_SendAndRecv(HsmClient, timeout);

        if (SystemP_SUCCESS == status)
        {
            /* the FW update cert process request has been completed by HSM server
             * if this request has been processed correctly */
            if (HSM_FLAG_NACK == HsmClient->RespFlag)
            {
                DebugP_log("\r\n [HSM_CLIENT] Firmware update certificate programming request NACKed by HSM server\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                /* Change the Arguments Address in Physical Address */
                HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);
                /* check the integrity of args */
                crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), 0);
                if (crcArgs == HsmClient->RespMsg.crcArgs)
                {
                    status = SystemP_SUCCESS;
                }
                else
                {
                    DebugP_log("\r\n [HSM_CLIENT] CRC check for firmware update certificate programming response failed \r\n");
                    status = SystemP_FAILURE;
                }
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return status;
}
int32_t HsmClient_VerifyROTSwitchingCertificate(HsmClient_t *HsmClient,
                                                uint8_t *cert,
                                                uint32_t cert_size,
                                                uint32_t timeout)
{
    /* make the message */
    int32_t status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_VERIFY_ROT_CERT;
    HsmClient->ReqMsg.args = (void *)cert;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)cert, cert_size);

    /* Change the Arguments Address in Physical Address */
    HsmClient->ReqMsg.args = (void *)(uintptr_t)SOC_virtToPhy(cert);

    /*
    Write back the debug cert and
    invalidate the cache before passing it to HSM
    */
    CacheP_wbInv(cert, GET_CACHE_ALIGNED_SIZE(cert_size), CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the RoT Switch has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == HSM_FLAG_NACK)
        {
            DebugP_log("\r\n [HSM_CLIENT] RoT Switching Certificate Verification request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            HsmClient->RespMsg.args = (void *)SOC_phyToVirt((uint64_t)HsmClient->RespMsg.args);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0U);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                DebugP_log("\r\n [HSM_CLIENT] CRC check for RoT Switching Certificate Verification response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}
