/*
 *  Copyright (c) 2025 Texas Instruments Incorporated
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
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON AN2
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*==========================================================================
 *                             Include Files
 *==========================================================================*/
#include <drivers/hsmclient/hsmclient.h>
#include <inc/hw_types.h>
#include <kernel/dpl/HwiP.h>

/*==========================================================================
 *                           Macros
 *==========================================================================*/
/**
 * @brief
 *  This is the version number for the IPC Export Interface. The version number
 *  should be the same between the HSM Boot ROM and the C29 SBL. In the case of a
 *  mismatch the HSM Boot ROM will generate an error.
 */
#define HSMCLIENT_IPC_EXPORT_VERSION          (0x1U)

#define HSM_MAILBOX_BASE_ADDR_TX              (0x302C0800U)
#define HSM_MAILBOX_BASE_ADDR_RX              (0x302C1000U)

/*==========================================================================
 *                       Section-1 structure Declarations
 *==========================================================================*/
/**
 * @brief
 *       hsmclient IPC  Message Type for HSMRt load function.
 *
 * @details
 *  The enumeration describes the messages which are supported by the
 *  IPC Module executing in the HSM Runtime state.
 */
typedef enum Hsmclient_ipcExportMsgType_e
{
    /**
     * @brief   Load the HSM Runtime
     *      R5 SBL -> HSM
     *  Payload = ipcLoadHSM
     */
    Hsmclient_ipcExportMsgType_LOAD_HSM = 0x9980A1D4U,
    /**
     * @brief   HSM Runtime Load Status
     *      HSM -> R5 SBL
     *  Payload = ipcLoadHSMResult
     */
    Hsmclient_ipcExportMsgType_LOAD_HSM_RESULT = 0xA70915DEU

} Hsmclient_ipcExportMsgType;

/**
 * @brief  IPC Load HSM Runtime
 *
 * @details
 *  This is the format of the message which is sent to load the
 *  HSM runtime. The R5 SBL will populate this message and will send
 *  to the HSM Boot ROM.
 */
typedef struct Hsmclient_ipcExportHeader_t
{
    /**
     * @brief   Version of the IPC Exported Interface.
     * \ref HSMCLIENT_IPC_EXPORT_VERSION
     */
    uint32_t version;
    /**
     * @brief   IPC Message Type which is being sent.
     */
    Hsmclient_ipcExportMsgType msgType;
    /**
     * @brief   This is the 16bit checksum which will need to be added
     * to ensure correctness of the data being passed. The checksum
     * is computed on the header + payload.
     */
    uint16_t checksum;
} Hsmclient_ipcExportHeader;

/**
 * @brief
 *  IPC Load HSM Runtime
 *
 * @details
 *  This is the format of the message which is sent to load the
 *  HSM runtime. The R5 SBL will populate this message and will send
 *  to the HSM Boot ROM.
 */
typedef struct Hsmclient_ipcLoadHSM_t
{
    /**
     * @brief   This is header which is added to all the messages
     */
    Hsmclient_ipcExportHeader header;
    /**
     * @brief   This is the load address where the HSM runtime image
     * is located. The image should always have the X509 certificate
     * followed by the actual HSM runtime binary.
     */
    uint32_t imgLoadAddress;
} Hsmclient_ipcLoadHSM;

/**
 * @brief
 *  IPC Load HSM Status
 *
 * @details
 *  The enumeration describes the status of the HSM Runtime loading
 *  status. This is sent back to the R5 SBL
 */
typedef enum Hsmclient_ipcLoadHSMStatus_e
{
    /**
     * @brief   HSM Runtime was loaded successfully
     */
    Hsmclient_ipcLoadHSMStatus_SUCCESS = 0x4A43AB6CU,

    /**
     * @brief   HSM Runtime could not be loaded
     */
    Hsmclient_ipcLoadHSMStatus_FAILURE = 0x7021AE4BU
} Hsmclient_ipcLoadHSMStatus;

/**
 * @brief  IPC Load HSM Result
 *
 * @details
 *  This is the format of the message which is sent from the HSM Boot ROM
 *  to the R5 SBL to indicate the result of the loading request.
 */
typedef struct Hsmclient_ipcLoadHSMResult_t
{
    /**
     * @brief   This is header which is added to all the messages
     */
    Hsmclient_ipcExportHeader header;
    /**
     * @brief   Status of the HSM Boot ROM Loading status
     */
    Hsmclient_ipcLoadHSMStatus status;
} Hsmclient_ipcLoadHSMResult;

/*==========================================================================
 *                          Section-1 Global Variables
 *==========================================================================*/
/* Flag for IPC write done ack */
volatile uint8_t gHsmRtDownloadComplete = 0;

/*==========================================================================
 *                          static Function Declarations
 *==========================================================================*/
/**
 *  @brief   This is a utility function which is used to compute the checksum
 *           on the provided buffer.
 *
 *  @param   ptrBuffer Buffer pointer.
 *
 *  @param   sizeMsg   message size in bytes.
 *
 *  @return  Computed checksum
 */
static uint16_t Hsmclient_computeIPCChecksum(uint8_t *ptrBuffer, uint32_t sizeMsg);

/**
 *  @brief   mailbox Rx ISR, copies HSM ROM response to passed argument
 *
 *  @param   args loadHSMResult passing as arument
 *
 */
void Hsmclient_mboxWdoneISR(void *args);

/**
 *  @brief   mailbox read request ACK ISR, clears the read request interrupt generated 
 *           by HSM ROM 
 *
 *  @param   args NULL
 *
 */
void Hsmclient_mboxReadAckISR(void *args);

/*==========================================================================
 *                      static Function Definitions
 *==========================================================================*/
static uint16_t Hsmclient_computeIPCChecksum(uint8_t *ptrBuffer, uint32_t sizeMsg)
{
    uint8_t *ptrData;
    uint32_t index = 0U;
    uint32_t checksum = 0U;

    /* Checksum includes the header */
    ptrData = (uint8_t *)ptrBuffer;

    /* Cycle through the entire message */
    while (index < sizeMsg)
    {
        checksum = checksum + ptrData[index];
        index = index + 1U;
    }
    checksum = (checksum & 0xFFFFU) + (checksum >> 16U);
    checksum = (checksum & 0xFFFFU) + (checksum >> 16U);
    checksum = ~checksum;

    return (uint16_t)checksum;
}


/*==============================================================================*
 *                          public Function definition.
 *==============================================================================*/

void Hsmclient_updateBootNotificationRegister(void)
{
    
}

int32_t Hsmclient_loadHSMRtFirmware(HsmClient_t *NotifyClient, const uint8_t *pHSMRt_firmware)
{
    int32_t  status   = SystemP_SUCCESS;
    Hsmclient_ipcLoadHSM         loadHSMImage;
    Hsmclient_ipcLoadHSMResult   loadHSMResult = {{0}};
    uint16_t            orgChecksum;
    HwiP_Params hwiParams;
    HwiP_Object hwiObjReadDone, hwiObjWriteDone;
    uint8_t *ptrMessage = (uint8_t *) HSM_MAILBOX_BASE_ADDR_TX;
    uint8_t i = 0;

    if (pHSMRt_firmware != NULL)
    {
        if(SSU_RAMOPENSTAT_LINK1_RAMOPENS == (HWREG(SSUCPU1CFG_BASE + SSU_O_RAMOPENSTAT) & SSU_RAMOPENSTAT_LINK1_RAMOPENS))
        {
            Interrupt_setINTSP(1);
        }
        /* clear any pending Interrupt */
        HWREG(CPU1IPCSEND_BASE + IPC_O_CPU1TOHSMINTIPCCLR(0U)) = IPC_CPU1TOHSMINTIPCCLR_IPC0;
        HWREG(CPU1IPCSEND_BASE + IPC_O_CPU1TOHSMINTIPCCLR(1U)) = IPC_CPU1TOHSMINTIPCCLR_IPC0;

        /* register interrupt for Rx Mailbox */
        HwiP_Params_init(&hwiParams);
        hwiParams.intNum = INT_IPC_HSM_RACK;
        hwiParams.callback = Hsmclient_mboxReadAckISR;
        hwiParams.args = NULL;
        hwiParams.priority = 10;
        if(SSU_RAMOPENSTAT_LINK1_RAMOPENS == (HWREG(SSUCPU1CFG_BASE + SSU_O_RAMOPENSTAT) & SSU_RAMOPENSTAT_LINK1_RAMOPENS))
        {
            hwiParams.linkOwner = 1;
        }

        status |= HwiP_construct(
            &hwiObjReadDone,
            &hwiParams);

        /* register interrupt for Rx Mailbox */
        HwiP_Params_init(&hwiParams);
        hwiParams.intNum = INT_IPC_HSM_WDONE;
        hwiParams.callback = Hsmclient_mboxWdoneISR;
        hwiParams.args = &loadHSMResult;
        hwiParams.priority = 9;
        if(SSU_RAMOPENSTAT_LINK1_RAMOPENS == (HWREG(SSUCPU1CFG_BASE + SSU_O_RAMOPENSTAT) & SSU_RAMOPENSTAT_LINK1_RAMOPENS))
        {
            hwiParams.linkOwner = 1;
        }

        status |= HwiP_construct(
            &hwiObjWriteDone,
            &hwiParams);

        /* Populate the ipcExportMsgType_LOAD_HSM message header: */
        loadHSMImage.header.version  = HSMCLIENT_IPC_EXPORT_VERSION;
        loadHSMImage.header.msgType  = Hsmclient_ipcExportMsgType_LOAD_HSM;
        loadHSMImage.header.checksum = 0U;
        loadHSMImage.imgLoadAddress  = (uint32_t)((uint8_t *)pHSMRt_firmware);
        /* Compute the checksum: */
        loadHSMImage.header.checksum = Hsmclient_computeIPCChecksum ((uint8_t*)&loadHSMImage, sizeof(loadHSMImage));

        /* Copy the message: */
        memcpy ((void *)ptrMessage, (void *)&loadHSMImage, sizeof(Hsmclient_ipcLoadHSM));

        /* raise interrupt to the processor */
        HWREG(CPU1IPCSEND_BASE + IPC_O_CPU1TOHSMINTIPCSET(0U)) = IPC_CPU1TOHSMINTIPCSET_IPC0;

        /* Wait until hsmRt firmware download completes */
        while(gHsmRtDownloadComplete != 1)
        {
            
        }

        /* Reset the variable status to 0 */
        gHsmRtDownloadComplete = 0;

        orgChecksum = loadHSMResult.header.checksum;
        loadHSMResult.header.checksum = 0U;
        /* Compute the checksum: */
        loadHSMResult.header.checksum = Hsmclient_computeIPCChecksum ((uint8_t*)&loadHSMResult, sizeof(loadHSMResult));
        /* Check for checksum match and firmware load status signature */
        if ((loadHSMResult.header.checksum != orgChecksum) || (loadHSMResult.status != Hsmclient_ipcLoadHSMStatus_SUCCESS))
        {
            /* Error: Invalid checksum */
            status = SystemP_FAILURE;
        }
        HwiP_destruct(&hwiObjReadDone);
        HwiP_destruct(&hwiObjWriteDone);
    }
    else
    {
        /* Error: Invalid load address */
        status = SystemP_FAILURE;
    }
    return status;
}

void Hsmclient_mboxReadAckISR(void *args)
{
    /*  Clear the 'R-REQ' interrupt */
    HWREG(CPU1IPCSEND_BASE + IPC_O_CPU1TOHSMINTIPCCLR(0U)) = IPC_CPU1TOHSMINTIPCCLR_IPC0;
}

void Hsmclient_mboxWdoneISR(void *args)
{
    Hsmclient_ipcLoadHSMResult *ploadHSMResult = (Hsmclient_ipcLoadHSMResult *) args;
    
    /* clear Read done */
    HWREG(CPU1IPCSEND_BASE + IPC_O_CPU1TOHSMINTIPCCLR(1U)) = IPC_CPU1TOHSMINTIPCCLR_IPC0;

    /* Copy the HSM Result */
    memcpy ((void*)ploadHSMResult, (void*)HSM_MAILBOX_BASE_ADDR_RX, sizeof(Hsmclient_ipcLoadHSMResult));

    /*HSMRT down load completed*/
    gHsmRtDownloadComplete = 1;
}