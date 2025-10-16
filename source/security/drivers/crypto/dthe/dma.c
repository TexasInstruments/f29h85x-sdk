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
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <security/drivers/crypto/dthe/dma.h>
#include <stdlib.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
DMA_Handle DMA_open(uint32_t instanceId)
{
    DMA_Config *dmaCfg = NULL;

    if (instanceId < gDmaConfigNum)
    {
        dmaCfg = &gDmaConfig[instanceId];
    }

    return (dmaCfg);
}

DMA_Return_t DMA_Config_TxChannel(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks, uint16_t blockSize, int32_t operationType)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;
    int32_t dmaModuleStatus = SystemP_FAILURE;

    if(handle != NULL)
    {
        DMA_Config  *config = (DMA_Config *) handle;
        if(config && config->dmaFxns && config->dmaFxns->cfgDmaTxChFxn)
        {

            dmaModuleStatus = config->dmaFxns->cfgDmaTxChFxn(config->dmaHandle, srcAddress, dstAddress, numBlocks, blockSize, operationType);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_enableTxTransferRegion(DMA_Handle handle)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;
    int32_t dmaModuleStatus = SystemP_FAILURE;

    if(handle != NULL)
    {
        DMA_Config *config = (DMA_Config *) handle;

        if(config && config->dmaFxns && config->dmaFxns->enableTxTransferRegionFxn)
        {

            dmaModuleStatus = config->dmaFxns->enableTxTransferRegionFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_WaitForTxTransfer(DMA_Handle handle)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;
    int32_t dmaModuleStatus = SystemP_FAILURE;

    if(handle != NULL)
    {
        DMA_Config *config = (DMA_Config *) handle;

        if(config && config->dmaFxns && config->dmaFxns->waitForTxTranferFxn)
        {
            dmaModuleStatus = config->dmaFxns->waitForTxTranferFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_disableTxCh(DMA_Handle handle)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;
    int32_t dmaModuleStatus = SystemP_FAILURE;

    if(handle != NULL)
    {
        DMA_Config *config = (DMA_Config *) handle;

        if(config && config->dmaFxns && config->dmaFxns->enableRxTransferRegionFxn)
        {

            dmaModuleStatus = config->dmaFxns->disableTxChFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_Config_RxChannel(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;
    int32_t dmaModuleStatus = SystemP_FAILURE;

    if(handle != NULL)
    {
        DMA_Config *config = (DMA_Config *) handle;
        if(config && config->dmaFxns && config->dmaFxns->cfgDmaRxChFxn)
        {
            dmaModuleStatus = config->dmaFxns->cfgDmaRxChFxn(config->dmaHandle, srcAddress, dstAddress, numBlocks);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_enableRxTransferRegion(DMA_Handle handle)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;
    int32_t dmaModuleStatus = SystemP_FAILURE;

    if(handle != NULL)
    {
        DMA_Config *config = (DMA_Config *) handle;

        if(config && config->dmaFxns && config->dmaFxns->enableRxTransferRegionFxn)
        {

            dmaModuleStatus = config->dmaFxns->enableRxTransferRegionFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_WaitForRxTransfer(DMA_Handle handle)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;
    int32_t dmaModuleStatus = SystemP_FAILURE;

    if(handle != NULL)
    {
        DMA_Config *config = (DMA_Config *) handle;
        
        if(config && config->dmaFxns && config->dmaFxns->waitForRxTranferFxn)
        {
            dmaModuleStatus = config->dmaFxns->waitForRxTranferFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_disableRxCh(DMA_Handle handle)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;
    int32_t dmaModuleStatus = SystemP_FAILURE;

    if(handle != NULL)
    {
        DMA_Config *config = (DMA_Config *) handle;

        if(config && config->dmaFxns && config->dmaFxns->enableRxTransferRegionFxn)
        {

            dmaModuleStatus = config->dmaFxns->disableRxChFxn(config->dmaHandle);
        }
    }

    if (dmaModuleStatus == SystemP_FAILURE)
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }
    else if (dmaModuleStatus == SystemP_SUCCESS)
    {
        dmaStatus = DMA_RETURN_SUCCESS;
    }
    else
    {
        dmaStatus = DMA_RETURN_FAILURE;
    }

    return (dmaStatus);
}

DMA_Return_t DMA_close(DMA_Handle handle)
{
    DMA_Return_t dmaStatus = DMA_RETURN_FAILURE;

    if(handle != NULL)
    {
        handle = NULL;
        dmaStatus  = DMA_RETURN_SUCCESS;
    }
    return (dmaStatus);
}
