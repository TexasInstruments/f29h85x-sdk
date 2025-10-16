/*
 *  Copyright (C) 2023-24 Texas Instruments Incorporated
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

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inc/stw_types.h>
#include <inc/hw_types.h>
#include <i2c.h>
#include <pmic_tps65036xx.h>
#include <SemaphoreP.h>
#include <pmic_core.h>
#include <pmic_power.h>
#include <pmic_irq.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

SemaphoreP_Object gPmicCoreObj;

uint32_t g_isFirstI2cComm = 1U;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t PMIC_regRead(const Pmic_CoreHandle_t *pmicHandle, uint8_t regAddr, uint8_t bufLen, uint8_t *rxbuf);
int32_t PMIC_regWrite(const Pmic_CoreHandle_t *pmicHandle, uint8_t regAddr, uint8_t bufLen, const uint8_t *txBuf);

void PMIC_criticalSectionStartFn(void);
void PMIC_criticalSectionStopFn(void);
PMIC_Handle PMIC_getHandle(uint32_t index);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

PMIC_Fxns gPmicFxns_tps65036xx =
{
    .openFxn        = PMIC_tps65036xxOpen,
    .configureFxn   = PMIC_tps65036xxConfigure,
    .closeFxn       = PMIC_tps65036xxClose,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */



/**
 * @brief Initialize PMIC communication interface and resources.
 * This function initializes the PMIC communication interface and resources
 * based on the provided configuration and parameters.
 *
 * @param config Pointer to the PMIC configuration structure.
 * @param params Pointer to the PMIC parameters structure.
 * @return status Status of the operation (SystemP_SUCCESS if successful,
 * SystemP_FAILURE otherwise).
 */
int32_t PMIC_tps65036xxOpen(PMIC_Config *config, const PMIC_Params *params)
{
    int32_t         status = SystemP_SUCCESS;
    PMIC_Object     *object;
    Pmic_CoreCfg_t pmicConfigData = {0U};
    Pmic_CoreHandle_t *coreHandle = NULL;

    if((NULL == config) || (NULL == params))
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        object = (PMIC_Object *) config->object;
        status += SemaphoreP_constructMutex(&gPmicCoreObj);

        /* Allocate memory for PMIC core Handle */
        coreHandle = (Pmic_CoreHandle_t *)malloc(sizeof(Pmic_CoreHandle_t));
        if (NULL != coreHandle)
        {
            memset(coreHandle, 0, sizeof(Pmic_CoreHandle_t));
            object->pmicCoreHandle = coreHandle;
        }

        /* Fill parameters to pmicConfigData */
        pmicConfigData.i2cAddr      = params->i2cAddr;
        pmicConfigData.commHandle   = params->commHandle;
        pmicConfigData.ioRead       = PMIC_regRead;
        pmicConfigData.ioWrite      = PMIC_regWrite;
        pmicConfigData.critSecStart = PMIC_criticalSectionStartFn;
        pmicConfigData.critSecStop  = PMIC_criticalSectionStopFn;

        status += Pmic_init(&pmicConfigData, coreHandle);

    }

    if(SystemP_SUCCESS == status)
    {
        object->isOpen = 1;
        object->handle = (PMIC_Handle)config;
        g_isFirstI2cComm = 1U;
    }
    else
    {
        PMIC_tps65036xxClose(config);
    }

   return status;
}


/**
 * @brief  Configure the PMIC instance
 * This function performs a LDO configurations and set the LDO's to respective voltage
 *
 * @param PMIC_Config  Pointer to the PMIC config.
 * @return  Status of the register read operation.
 *          - #SystemP_SUCCESS if the read operation is successful.
 *          - #SystemP_FAILURE if the read operation fails.
 */
int32_t PMIC_tps65036xxConfigure(PMIC_Config *config)
{

    int32_t status = SystemP_SUCCESS;
    PMIC_Object *object;
    bool wdgEnabled = (bool)false;
    bool crcIntMask = (bool)TRUE;

    if ((NULL == config))
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        object = (PMIC_Object *)config->object;
        Pmic_CoreHandle_t *pmicCoreHandle = object->pmicCoreHandle;

        // Unlock PMIC registers
        status = Pmic_unlockRegs(pmicCoreHandle);

        /* Any time a setting is changed so that it is different from what is stored
         * in the PMIC’s OTP memory, the device will have a reset.
         * The workaround for this is to mask the CONFIG_CRC interrupt.
         */
        status = Pmic_irqSetMask(pmicCoreHandle, PMIC_CONFIG_CRC_INT, crcIntMask);

        // Disable WD if its enabled
        status = Pmic_wdgGetEnable(pmicCoreHandle, &wdgEnabled);
        if (wdgEnabled == true)
        {
            // Disable WDG
            status = Pmic_wdgDisable(pmicCoreHandle);
        }
    }

    return status;

}

/**
 * @brief Deinitialize PMIC communication interface and resources.
 * This function deinitializes the PMIC communication interface and resources.
 *
 * @param config Pointer to the PMIC configuration structure.
 * @return void No return value.
 */
void PMIC_tps65036xxClose(PMIC_Config *config)
{
    int32_t         status = SystemP_SUCCESS;
    PMIC_Object     *object;

    if(NULL == config)
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        object = (PMIC_Object *) config->object;
        object-> isOpen = 0;
        status = Pmic_deinit(object->pmicCoreHandle);
        free(object->pmicCoreHandle);
        SemaphoreP_destruct(&gPmicCoreObj);
        g_isFirstI2cComm = 0U;
    }

    return;
}

/**
 * @brief  Get the Pmic_CoreHandle_t driver handle
 * This function gets the PMIC driver handle for the specified index
 *
 * @param index  [in] Index within `PMIC_Config gPmicConfig[]`
 * @return  Handle to pmic driver
 */
Pmic_CoreHandle_t* PMIC_getCoreHandle(uint32_t index)
{
    Pmic_CoreHandle_t* handle = NULL;
    /* Check index */
    if(index < gPmicConfigNum)
    {
        PMIC_Object *obj;
        obj = (PMIC_Object *)gPmicConfig[index].object;

        if(obj && (TRUE == obj->isOpen))
        {
            /* valid handle */
            handle = obj->pmicCoreHandle;
        }
    }
    return handle;
}


/**
 * @brief  Reads a register from the PMIC device.
 * This function performs a read operation on a specified register of
 * the PMIC device using the configured SPI communication. It utilizes
 * the I2C driver to execute the read transaction and updates the
 * received data in the provided buffer.
 *
 * @param pmicCorehandle  Pointer to the PMIC core handle.
 * @param regAddr         Register address to read.
 * @param pBuf            Pointer to the buffer to store the read data.
 * @param bufLen          Length of the buffer.
 * @return  Status of the register read operation.
 *          - #SystemP_SUCCESS if the read operation is successful.
 *          - #SystemP_FAILURE if the read operation fails.
 */
int32_t PMIC_regRead(const Pmic_CoreHandle_t *pmicHandle, uint8_t regAddr, uint8_t bufLen, uint8_t *rxBuf)
{
    int32_t         status      = PMIC_ST_SUCCESS;
    I2c_handle      *pI2cHandle = NULL;
    uint32_t        readCnt     = 0U;
    uint32_t        cnt         = 0U;
    uint32_t        i2cCnt      = 0U;
    I2C_RxFIFOLevel rxFifoSts   = I2C_FIFO_RXEMPTY;

    // Parameter check
    if ((pmicHandle == NULL) || (rxBuf == NULL))
    {
        status = PMIC_ST_ERR_NULL_PARAM;
    }
    if ((status == PMIC_ST_SUCCESS) && (bufLen == 0U))
    {
        status = PMIC_ST_ERR_INV_PARAM;
    }

    if (status == PMIC_ST_SUCCESS)
    {
        pI2cHandle = (I2c_handle*)pmicHandle->commHandle;

        if(NULL != pI2cHandle)
        {
            if(1U == g_isFirstI2cComm)
            {
                i2cCnt              = 2U;
                g_isFirstI2cComm    = 0U;
            }
            else
            {
                i2cCnt = 1U;
            }

            for(readCnt = 0U;readCnt < i2cCnt;readCnt++)
            {
                /* Check STOP bit and busy status */
                if((FALSE == I2C_getStopConditionStatus(pI2cHandle->i2cBaseAddr)) &&
                   (FALSE == I2C_isBusBusy(pI2cHandle->i2cBaseAddr)))
                {
                    /* Set target (PMIC) address */
                    I2C_setTargetAddress(pI2cHandle->i2cBaseAddr, pmicHandle->i2cAddr);

                    /* Set data count for sending address = 1 */
                    I2C_setDataCount(pI2cHandle->i2cBaseAddr, 1U);

                    /* Configure I2C controller in SEND mode */
                    I2C_setConfig(pI2cHandle->i2cBaseAddr, I2C_CONTROLLER_SEND_MODE);

                    /* Send register address */
                    I2C_putData(pI2cHandle->i2cBaseAddr, regAddr);

                    /* Send START condition */
                    I2C_sendStartCondition(pI2cHandle->i2cBaseAddr);

                    /* Wait for ARDY */
                    while (0U == (I2C_getStatus(pI2cHandle->i2cBaseAddr) & I2C_STR_ARDY))
                    {
                        ;
                    }

                    /* Set data count to read */
                    I2C_setDataCount(pI2cHandle->i2cBaseAddr, bufLen);

                    /* Configure I2C controller in RECEIVE mode */
                    I2C_setConfig(pI2cHandle->i2cBaseAddr, I2C_CONTROLLER_RECEIVE_MODE);

                    /* Send START (REPEATED) condition */
                    I2C_sendStartCondition(pI2cHandle->i2cBaseAddr);

                    /* Send STOP condition, generates STOP condition when all data is received */
                    I2C_sendStopCondition(pI2cHandle->i2cBaseAddr);

                    /* Wait until STOP condition */
                    while(0U == (I2C_getStatus(pI2cHandle->i2cBaseAddr) & I2C_STS_STOP_CONDITION))
                    {
                        ;
                    }

                    /* Clear SCD and NACKSNT */
                    I2C_clearStatus(pI2cHandle->i2cBaseAddr, (I2C_STS_STOP_CONDITION | I2C_STS_NACK_SENT | I2C_STS_BYTE_SENT));

                    /* Wait until STP bit is cleared */
                    while(TRUE == I2C_getStopConditionStatus(pI2cHandle->i2cBaseAddr))
                    {
                        ;
                    }

                    /* Read the data bytes */
                    rxFifoSts = I2C_getRxFIFOStatus(pI2cHandle->i2cBaseAddr);
                    for(cnt = 0U;cnt < rxFifoSts;cnt++)
                    {
                        rxBuf[cnt] = I2C_getData(pI2cHandle->i2cBaseAddr);
                    }
                }
                else
                {
                    status = PMIC_ST_ERR_I2C_COMM_FAIL;
                }
            }
        }
        else
        {
            status = PMIC_ST_ERR_NULL_PARAM;
        }
    }

    return status;
}

/**
 * @brief  Writes data to a register of the PMIC device.
 * This function performs a write operation to a specified register of the
 * PMIC device using the configured SPI communication. It utilizes the
 * I2C driver to execute the write transaction with the provided data.
 *
 * @param pmicCorehandle Pointer to the PMIC core handle.
 * @param regAddr        Register address to write.
 * @param pBuf           Pointer to the buffer containing the data to write.
 * @param bufLen         Length of the buffer.
 * @return  Status of the register write operation.
 *          - #SystemP_SUCCESS if the write operation is successful.
 *          - #SystemP_FAILURE if the write operation fails.
 */
int32_t PMIC_regWrite(const Pmic_CoreHandle_t *pmicHandle, uint8_t regAddr, uint8_t bufLen, const uint8_t *txBuf)
{
    int32_t     status          = PMIC_ST_SUCCESS;
    uint8_t     writeBuf[3U]    = {0U};
    I2c_handle  *pI2cHandle     = NULL;
    uint32_t    writeCnt        = 0U;
    uint32_t    cnt             = 0U;
    uint32_t    i2cCnt          = 0U;

    // Parameter check
    if ((pmicHandle == NULL) || (txBuf == NULL))
    {
        status = PMIC_ST_ERR_NULL_PARAM;
    }
    if ((status == PMIC_ST_SUCCESS) && ((bufLen == 0U) || (bufLen > 2U)))
    {
        status = PMIC_ST_ERR_INV_PARAM;
    }

    if (status == PMIC_ST_SUCCESS)
    {
        pI2cHandle = (I2c_handle*)pmicHandle->commHandle;

        if(NULL != pI2cHandle)
        {
            if(1U == g_isFirstI2cComm)
            {
                i2cCnt              = 2U;
                g_isFirstI2cComm    = 0U;
            }
            else
            {
                i2cCnt = 1U;
            }

            for(writeCnt = 0U;writeCnt < i2cCnt;writeCnt++)
            {
                /* Check STOP bit and busy status */
                if((FALSE == I2C_getStopConditionStatus(pI2cHandle->i2cBaseAddr)) &&
                   (FALSE == I2C_isBusBusy(pI2cHandle->i2cBaseAddr)))
                {
                    /* Set target (PMIC) address */
                    I2C_setTargetAddress(pI2cHandle->i2cBaseAddr, pmicHandle->i2cAddr);

                    /* Set data count including register address byte */
                    I2C_setDataCount(pI2cHandle->i2cBaseAddr, (bufLen + 1U));

                    /* Configure I2C controller in SEND mode */
                    I2C_setConfig(pI2cHandle->i2cBaseAddr, I2C_CONTROLLER_SEND_MODE);

                    /* Send register address */
                    I2C_putData(pI2cHandle->i2cBaseAddr, regAddr);

                    /* Send data array */
                    for(cnt = 0U;cnt < bufLen;cnt++)
                    {
                        I2C_putData(pI2cHandle->i2cBaseAddr, txBuf[cnt]);
                    }

                    /* Send START condition */
                    I2C_sendStartCondition(pI2cHandle->i2cBaseAddr);

                    /* Send STOP condition, generates STOP condition when all data is transmitted */
                    I2C_sendStopCondition(pI2cHandle->i2cBaseAddr);

                    /* Wait until STOP condition */
                    while(0U == (I2C_getStatus(pI2cHandle->i2cBaseAddr) & I2C_STS_STOP_CONDITION))
                    {
                        ;
                    }

                    /* Clear SCD */
                    I2C_clearStatus(pI2cHandle->i2cBaseAddr, (I2C_STS_STOP_CONDITION | I2C_STS_BYTE_SENT));

                    /* Wait until STP bit is cleared */
                    while(TRUE == I2C_getStopConditionStatus(pI2cHandle->i2cBaseAddr))
                    {
                        ;
                    }
                }
                else
                {
                    status = PMIC_ST_ERR_I2C_COMM_FAIL;
                }
            }
        }
        else
        {
            status = PMIC_ST_ERR_NULL_PARAM;
        }
    }

    return status;
}

/**
 * @brief  Initiates the start of a critical section for PMIC operations.
 * This function attempts to acquire a semaphore, which is typically
 * used to ensure exclusive access to resources during PMIC operations.
 * If the semaphore acquisition fails, an error message is logged.
 *
 * @param   void
 * @return  NULL
 */
void PMIC_criticalSectionStartFn(void)
{
    SemaphoreP_pend(&gPmicCoreObj, SystemP_WAIT_FOREVER);
}

/**
 * @brief  Concludes a critical section for PMIC operations.
 * This function releases the semaphore, signifying
 * the end of a critical section initiated by a
 * corresponding "start" function.
 *
 * @param   void
 * @return  NULL
 */
void PMIC_criticalSectionStopFn(void)
{
    SemaphoreP_post(&gPmicCoreObj);
}

