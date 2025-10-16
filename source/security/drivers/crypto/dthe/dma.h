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

/**
 *  \defgroup SECURITY_DMA_MODULE APIs for DMA
 *  \ingroup SECURITY_MODULE
 *
 *  This module contains APIs to program and use the DMA module
 *
 *  @{
 */

#ifndef DMA_H_
#define DMA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SystemP.h>
#include <security/drivers/crypto/dthe/dma/device_includes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Dma disable macro*/
#define DMA_DISABLE                                   (0U)
/** Dma enable macro*/
#define DMA_ENABLE                                    (1U)

/** Dma AES disable macro*/
#define DMA_AES_ENABLE                                (0)
/** Dma SHA enable macro*/
#define DMA_SHA_ENABLE                                (1)

/** \brief Handle to the DMA driver returned by #DMA_open() */
typedef void *DMA_Handle;
/** \brief Forward declaration of \ref DMA_Config_s */
typedef struct DMA_Config_s DMA_Config;
/** \brief Forward declaration of \ref DMA_Params_s */
typedef struct DMA_Params_s DMA_Params;

/**
 * \brief
 *  DMA Driver Error code
 *
 * \details
 *  The enumeration describes all the possible return and error codes which
 *  the DMA Driver can return
 */
typedef enum DMA_Return_e
{
    DMA_RETURN_SUCCESS                  = 0xF356898CU, /*!< Success/pass return code */
    DMA_RETURN_FAILURE                  = 0x2DA11252U, /*!< General or unspecified failure/error */
}DMA_Return_t;

/**
 * \name DMA driver implementation callbacks
 *
 * @{
 */
/**
 *  \brief This callback implemented to configure a Transmit DMA channel
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *  \param srcAddress [IN] Source address for DMA transfer.
 *  \param dstAddress [IN] Destination address for DMA transfer.
 *  \param numBlocks [IN] Number of block to transfer.
 *
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*config_TxChannel)(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks, uint16_t blockSize, int32_t operationType);

/**
 *  \brief This callback implemented to configure a Receive DMA channel
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *  \param srcAddress [IN] Source address for DMA transfer.
 *  \param dstAddress [IN] Destination address for DMA transfer.
 *  \param numBlocks [IN] Number of block to transfer.
 *
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*config_RxChannel)(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks);

/**
 *  \brief This callback implemented to configure a Transmit SHA DMA channel
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *  \param srcAddress [IN] Source address for DMA transfer.
 *  \param dstAddress [IN] Destination address for DMA transfer.
 *  \param numBlocks [IN] Number of block to transfer.
 *  \param blockSize [IN] block size for sha channel cfg.
 * 
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*config_TxShaChannel)(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks, uint16_t blockSize);

/**
 *  \brief This callback implemented to enable Tx transfer DMA region
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*enableTxTransferRegion)(DMA_Handle handle);

/**
 *  \brief This callback implemented to disable Tx transfer channel
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*disableTxCh)(DMA_Handle handle);

/**
 *  \brief This callback implemented to wait for Tx transfer
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*waitForTxTransfer)(DMA_Handle handle);

/**
 *  \brief This callback implemented to enable Rx transfer DMA region
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*enableRxTransferRegion)(DMA_Handle handle);

/**
 *  \brief This callback implemented to disable Rx transfer channel
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*disableRxCh)(DMA_Handle handle);

/**
 *  \brief This callback implemented to wait for Rx transfer
 *
 *  \param handle [IN] DMA handle to process DMA operations.
 *
 *  \return SystemP_SUCCESS on success or SystemP_FAILURE on Failure.
 */
typedef int32_t (*waitForRxTransfer)(DMA_Handle handle);

/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Driver implementation callbacks
 */
typedef struct DMA_Fxns_s
{
    config_TxChannel        cfgDmaTxChFxn;
    /**< DMA callback function for cofigure dma tx channel */
    enableTxTransferRegion  enableTxTransferRegionFxn;
    /**< DMA callback function for enable tx transfer region */
    waitForTxTransfer       waitForTxTranferFxn;
    /**< DMA callback function to wait for tx transfer */
    config_RxChannel        cfgDmaRxChFxn;
    /**< DMA callback function for cofigure dma rx channel */
    enableRxTransferRegion  enableRxTransferRegionFxn;
    /**< DMA callback function for enable rx transfer region */
    waitForRxTransfer       waitForRxTranferFxn;
    /**< DMA callback function to wait for rx transfer */
    config_TxShaChannel     cfgDmaTxShaChFxn;
    /**< DMA callback function for cofigure dma sha tx channel */
    disableTxCh             disableTxChFxn;
    /**< DMA callback function for disable tx transfer region */
    disableRxCh             disableRxChFxn;
    /**< DMA callback function for disable Rx transfer region */
} DMA_Fxns;

/** \brief DMA instance attributes - used during init time */
struct DMA_Params_s
{
 #if defined(SOC_AM263X) || defined(SOC_AM263PX) || defined(SOC_AM273X) || defined(SOC_AWR294X) || defined(SOC_AM261X)
    uint32_t                baseAddr;
    /**< Base Address */
    uint32_t                regionId;
    /**< Region Id */
    uint32_t                dmaCh;
    /**< Channel number */
    uint32_t                tcc;
    /**< Channel control */
    uint32_t                param;
    /**< params */
#endif /* defined(SOC_AM263X) || defined(SOC_AM263PX) || defined(SOC_AM273X) || defined(SOC_AM261X) */
};

/**
 *  \brief DMA driver configuration, these are filled by SysCfg based
 *  on the device that is selected.
 */
struct DMA_Config_s
{
    void             *dmaHandle;
    /**< Pointer to DMA driver handler */
    DMA_Fxns         *dmaFxns;
    /**< Pointer to DMA driver functions */
};

/** Global dma configuration */
extern DMA_Config gDmaConfig[];
/** Number of global dma configurations */
extern uint32_t gDmaConfigNum;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief This DMA wrapper implemented to open DMA driver.
 *
 *  \param instanceId [IN] instanceId for DMA driver open
 *  
 *  \return handle    DMA driver handle from \ref DMA_open
 */
DMA_Handle DMA_open(uint32_t instanceId);

/**
 *  \brief This DMA wrapper implemented to close DMA driver.
 *
 *  \param handle    [IN] DMA driver handle from \ref DMA_open
 *  
 *  \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_close(DMA_Handle handle);

/**
 *  \brief This DMA wrapper implemented to configure DMA config TX channel.
 *
 *  \param handle    [IN] DMA driver handle from \ref DMA_open
 *  \param srcAddress [IN] Source address for DMA transfer.
 *  \param dstAddress [IN] Destination address for DMA transfer.
 *  \param numBlocks [IN] Number of block to transfer.
 *  
 *  \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_Config_TxChannel(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks, uint16_t blockSize, int32_t operationType);

/**
 * \brief This DMA wrapper implemented to enable DMA TX transfer region.
 *
 * \param handle    [IN] DMA driver handle from \ref DMA_open
 *
 * \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_enableTxTransferRegion(DMA_Handle handle);

/**
 * \brief This DMA wrapper implemented to wait TX transfer.
 *
 * \param handle    [IN] DMA driver handle from \ref DMA_open
 * 
 * \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_WaitForTxTransfer(DMA_Handle handle);

/**
 * \brief This DMA wrapper implemented to disable DMA TX channel.
 *
 * \param handle    [IN] DMA driver handle from \ref DMA_open
 *
 * \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_disableTxCh(DMA_Handle handle);

/**
 *  \brief This DMA wrapper implemented to configure DMA config RX sha channel.
 *
 *  \param handle    [IN] DMA driver handle from \ref DMA_open
 *  \param srcAddress [IN] Source address for DMA transfer.
 *  \param dstAddress [IN] Destination address for DMA transfer.
 *  \param numBlocks [IN] Number of block to transfer.
 *
 *   \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_Config_RxChannel(DMA_Handle handle, uint32_t *srcAddress, uint32_t *dstAddress, uint16_t numBlocks);

/**
 * \brief This DMA wrapper implemented to enable Rx Transfer Region.
 *
 * \param handle    [IN] DMA driver handle from \ref DMA_open
 *
 * \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_enableRxTransferRegion(DMA_Handle handle);

/**
 * \brief This DMA wrapper implemented to wait RX transfer.
 *
 * \param handle    [IN] DMA driver handle from \ref DMA_open
 * 
 * \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_WaitForRxTransfer(DMA_Handle handle);

/**
 * \brief This DMA wrapper implemented to disable DMA RX channel.
 *
 * \param handle    [IN] DMA driver handle from \ref DMA_open
 *
 * \return DMA_RETURN_SUCCESS on success or DMA_RETURN_FAILURE on Failure.
 */
DMA_Return_t DMA_disableRxCh(DMA_Handle handle);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DMA_H_ */

/** @} */
