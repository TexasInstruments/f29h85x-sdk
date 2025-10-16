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
#include <inc/stw_types.h>
#include <inc/hw_types.h>
#include <gpio.h>
#include <spi.h>
#include <SemaphoreP.h>
#include <pmic_tps653860xx.h>
#include <pmic_core.h>
#include <pmic_power.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Enable error register dump */
#define PMIC_ERROR_DEBUG

/* Sub address command as per tps653860xx datasheet */
#define CMD_SHIFT 			(8U)
#define DAT_SHIFT 			(8U)
#define CMD_RD_EN 			(0x10U)
#define CMD_WR_EN 			(0x00U)
#define DUMP_ERR_STATUS_REG (0xFFU)

SemaphoreP_Object gPmicCoreObj;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t PMIC_regRead(Pmic_CoreHandle_t  *pmicCorehandle,
                          uint8_t       instType,
                          uint16_t      regAddr,
                          uint8_t       *pBuf,
                          uint8_t       bufLen);
int32_t PMIC_regWrite(Pmic_CoreHandle_t *pmicCorehandle,
                           uint8_t      instType,
                           uint16_t     regAddr,
                           uint8_t      *pBuf,
                           uint8_t      bufLen);

void PMIC_criticalSectionStartFn(void);
void PMIC_criticalSectionStopFn(void);
PMIC_Handle PMIC_getHandle(uint32_t index);
void ClockP_usleep(uint32_t usec);

/* Private Functions */
uint8_t PMIC_calcCRC8(uint8_t cmd, uint8_t rdwr, uint8_t dat);
int32_t PMIC_spiRead(Spi_handle  *pSpiHandle, uint8_t addr, uint8_t *pData);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

PMIC_Fxns gPmicFxns_tps653860xx =
{
    .openFxn        = PMIC_tps653860xxOpen,
    .configureFxn   = PMIC_tps653860xxConfigure,
    .closeFxn       = PMIC_tps653860xxClose,
};

/* Error status register address */
uint8_t g_errReg[PMIC_NUM_ERR_REG] =
{
    0x09U,      // REG_STAT
    0x0BU,      // RDBK_ERR_STAT
    0x0FU,      // OFF_STATE_STAT1
    0x10U,      // OFF_STATE_STAT2
    0x46U,      // WD_ERR_STAT
    0x51U,      // ESM_ERR_STAT
    0x5AU,      // DCDC_STAT
    0x5BU,      // VMON_DEV_STAT
    0x5CU,      // VMON_LDO_STAT
    0x5EU,      // VMON_PLDO_STAT
    0x5FU,      // EXT_VMON_STAT
    0x63U,      // THERMAL_STAT1
    0x64U,      // THERMAL_STAT2
    0x65U,      // BIST_STAT
    0x67U,      // SPI_ERR_STAT
    0x77U,      // CM_STAT1
    0x78U       // CM_STAT2
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
int32_t PMIC_tps653860xxOpen(PMIC_Config *config, const PMIC_Params *params)
{
    int32_t             status          = SystemP_SUCCESS;
    PMIC_Object         *object;
    Pmic_CoreCfg_t      pmicConfigData  = {0U};
    Pmic_CoreHandle_t   *coreHandle     = NULL;

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
        pmicConfigData.pmicDeviceType       = params->deviceType;
        pmicConfigData.commMode             = params->commMode;
        pmicConfigData.instType             = params->instType;
        pmicConfigData.pCommHandle          = params->commHandle;
        pmicConfigData.pFnPmicCommIoRead    = PMIC_regRead;
        pmicConfigData.pFnPmicCommIoWrite   = PMIC_regWrite;
        pmicConfigData.pFnPmicCritSecStart  = PMIC_criticalSectionStartFn;
        pmicConfigData.pFnPmicCritSecStop   = PMIC_criticalSectionStopFn;

        pmicConfigData.validParams |= (PMIC_CFG_DEVICE_TYPE_VALID_SHIFT | PMIC_CFG_COMM_MODE_VALID_SHIFT |
                                        PMIC_CFG_COMM_IO_RD_VALID_SHIFT | PMIC_CFG_COMM_IO_WR_VALID_SHIFT |
                                        PMIC_CFG_CRITSEC_START_VALID_SHIFT | PMIC_CFG_CRITSEC_STOP_VALID_SHIFT |
                                        PMIC_CFG_COMM_HANDLE_VALID_SHIFT);

        status += Pmic_init(&pmicConfigData, coreHandle);

    }

    if(SystemP_SUCCESS == status)
    {
        object->isOpen = 1;
        object->handle = (PMIC_Handle)config;
    }
    else
    {
        PMIC_tps653860xxClose(config);
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
int32_t PMIC_tps653860xxConfigure(PMIC_Config *config)
{
    int32_t             status          = SystemP_SUCCESS;
    PMIC_Object         *object;
    Pmic_CoreHandle_t   *pmicCoreHandle = NULL;
    int32_t             pmicStatus      = PMIC_ST_SUCCESS;

    if ((NULL == config))
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        object = (PMIC_Object *)config->object;
        pmicCoreHandle = object->pmicCoreHandle;

        Pmic_setRegLockState(pmicCoreHandle, PMIC_LOCK_DISABLE);

        Pmic_PwrLdoCfg_t ldocfg_exp = {
            .validParams = PMIC_PWR_CFG_LDO_MODE_VALID_SHIFT | PMIC_PWR_CFG_LDO_LVL_VALID_SHIFT |
                           PMIC_PWR_CFG_LDO_ILIM_LVL_VALID_SHIFT | PMIC_PWR_CFG_LDO_RAMP_TIME_VALID_SHIFT,
            .ldo = PMIC_PWR_LDO2,
            .mode = PMIC_PWR_LDO_EN_AS_LDO_IN_OPER,
            .lvl = PMIC_PWR_LDO_LVL_3P3V,
            .ilimLvl = PMIC_PWR_LDO_ILIM_LVL_OPTION_0,
            .rampTime = PMIC_PWR_RT_LONGER,
        };
        pmicStatus += Pmic_pwrSetLdoCfg(pmicCoreHandle, &ldocfg_exp);

        ldocfg_exp.ldo = PMIC_PWR_LDO3;
        ldocfg_exp.lvl = PMIC_PWR_LDO_LVL_5V;
        pmicStatus += Pmic_pwrSetLdoCfg(pmicCoreHandle, &ldocfg_exp);

        ldocfg_exp.ldo = PMIC_PWR_LDO4;
        ldocfg_exp.lvl = PMIC_PWR_LDO_LVL_1P8V;
        pmicStatus += Pmic_pwrSetLdoCfg(pmicCoreHandle, &ldocfg_exp);

        if (PMIC_ST_SUCCESS != pmicStatus)
        {
            status += SystemP_FAILURE;
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
void PMIC_tps653860xxClose(PMIC_Config *config)
{
    int32_t     status  = SystemP_SUCCESS;
    PMIC_Object *object;

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
 * the MCSPI driver to execute the read transaction and updates the
 * received data in the provided buffer.
 *
 * @param pmicCorehandle  Pointer to the PMIC core handle.
 * @param instType        PMIC instance type.
 * @param regAddr         Register address to read.
 * @param pBuf            Pointer to the buffer to store the read data.
 * @param bufLen          Length of the buffer.
 * @return  Status of the register read operation.
 *          - #SystemP_SUCCESS if the read operation is successful.
 *          - #SystemP_FAILURE if the read operation fails.
 */
int32_t PMIC_regRead(Pmic_CoreHandle_t  *pmicCorehandle,
                          uint8_t       instType,
                          uint16_t      regAddr,
                          uint8_t       *pBuf,
                          uint8_t       bufLen)
{
    int32_t     status      = SystemP_SUCCESS;
    Spi_handle  *pSpiHandle = NULL;
    uint32_t    cnt         = 0U;

    if(NULL != pmicCorehandle)
    {
        pSpiHandle = (Spi_handle*)pmicCorehandle->pCommHandle;

        if(NULL != pSpiHandle)
        {
            /* SPI read */
            status = PMIC_spiRead(
                            pSpiHandle,                 // SPI handle
                            pBuf[0U],                   // Register address
                            &pBuf[2U]);                 // Read data
            /* If read fails, read the error registers */
            if(DUMP_ERR_STATUS_REG == status)
            {
#ifdef PMIC_ERROR_DEBUG
                for(cnt = 0U;cnt < PMIC_NUM_ERR_REG;cnt++)
                {
                    (void)PMIC_spiRead(
                            pSpiHandle,                 // SPI handle
                            g_errReg[cnt],              // Register address
                            &pSpiHandle->errReg[cnt]);  // Read data
                }
#endif
                status = SystemP_SUCCESS;
            }
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

/**
 * @brief  Writes data to a register of the PMIC device.
 * This function performs a write operation to a specified register of the
 * PMIC device using the configured SPI communication. It utilizes the
 * MCSPI driver to execute the write transaction with the provided data.
 *
 * @param pmicCorehandle Pointer to the PMIC core handle.
 * @param instType       PMIC instance type.
 * @param regAddr        Register address to write.
 * @param pBuf           Pointer to the buffer containing the data to write.
 * @param bufLen         Length of the buffer.
 * @return  Status of the register write operation.
 *          - #SystemP_SUCCESS if the write operation is successful.
 *          - #SystemP_FAILURE if the write operation fails.
 */
int32_t PMIC_regWrite(Pmic_CoreHandle_t *pmicCorehandle,
                           uint8_t      instType,
                           uint16_t     regAddr,
                           uint8_t      *pBuf,
                           uint8_t      bufLen)
{
    int32_t     status          = SystemP_SUCCESS;
    Spi_handle  *pSpiHandle     = NULL;
    uint8_t     crc             = 0U;
    uint8_t     readCrc         = 0U;
    uint32_t    cnt             = 0U;
    uint16_t    txData[2U]      = {0U, 0U};
    uint16_t    statusData[2U]  = {0U, 0U};

    if(NULL != pmicCorehandle)
    {
        pSpiHandle = (Spi_handle*)pmicCorehandle->pCommHandle;

        if(NULL != pSpiHandle)
        {
            /* Clear status data */
            statusData[0U] = 0U;
            statusData[1U] = 0U;

            /* Compute CRC */
            crc = PMIC_calcCRC8(pBuf[0U], CMD_WR_EN, pBuf[2U]);

            /* TX data */
            txData[0U]  = (pBuf[0U] << CMD_SHIFT)   | CMD_WR_EN;
            txData[1U]  = (pBuf[2U] << DAT_SHIFT)   | crc;

            /* Drive CS pin low */
            if(PMIC_TPS653860XX_INVALID_CS != pSpiHandle->csPin)
            {
                GPIO_writePin(pSpiHandle->csPin, 0U);

                /* Minimum 250 ns between falling edge of CS and rising edge of CLK */
                ClockP_usleep(1U);
            }

            /* Write 2 words of 16 bits each */
            SPI_writeDataNonBlocking(pSpiHandle->spiBaseAddr, txData[0U]);
            SPI_writeDataNonBlocking(pSpiHandle->spiBaseAddr, txData[1U]);

            /* Read status */
            statusData[0U] = SPI_readDataBlockingFIFO(pSpiHandle->spiBaseAddr);
            statusData[1U] = SPI_readDataBlockingFIFO(pSpiHandle->spiBaseAddr);

            /* Drive CS pin high */
            if(PMIC_TPS653860XX_INVALID_CS != pSpiHandle->csPin)
            {
                /* Minimum 45 ns between last falling edge of CLK and rising edge of CS */
                ClockP_usleep(1U);

                GPIO_writePin(pSpiHandle->csPin, 1U);
            }

            /* Minimum 500 ns between 2 SPI frames */
            ClockP_usleep(1U);

            /* Compute CRC on read data */
            readCrc = PMIC_calcCRC8(
                                (uint8_t)((statusData[0U] >> 8U) & 0xFFU),
                                (uint8_t)(statusData[0U] & 0xFFU),
                                (uint8_t)((statusData[1U] >> 8U) & 0xFFU));

            /* Check CRC */
            if(readCrc != (uint8_t)(statusData[1U] & 0xFFU))
            {
                /* Error status bit is set */
                status = SystemP_FAILURE;
            }
            else if(1U == (statusData[0U] & 1U))
            {
#ifdef PMIC_ERROR_DEBUG
                /* Read error registers */
                for(cnt = 0U;cnt < PMIC_NUM_ERR_REG;cnt++)
                {
                    (void)PMIC_spiRead(
                                pSpiHandle,                 // SPI handle
                                g_errReg[cnt],              // Register address
                                &pSpiHandle->errReg[cnt]);  // Read data
                }
#endif
            }
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    else
    {
        status = SystemP_FAILURE;
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

/**
 * @brief Calculate CRC-8 checksum for PMIC SPI communication.
 * This function calculates the CRC-8 checksum based on the command, read/write
 * flag, and data provided for communication between the MCU and the
 * TPS653850A-Q1 device.
 *
 * @param cmd Command byte for communication.
 * @param rdwr Read/Write flag for communication (CMD_RD_EN or CMD_WR_EN).
 * @param dat Data byte for communication.
 * @return crc Calculated CRC-8 checksum value.
 */
uint8_t PMIC_calcCRC8(uint8_t cmd, uint8_t rdwr, uint8_t dat) {
    int8_t i = 0;
    uint32_t crc;
    uint32_t tmp;

    tmp = ((uint32_t) cmd << 16) | ((uint32_t) rdwr << 8) | (uint32_t) dat;
    crc = (uint32_t) 0xFF;

    /* Standard CRC-8 polynomial ,X8 + X2 + X1 + 1.,is used to calculate the
     * checksum value based on the command and data which the MCU transmits
     * to the TPS653850A-Q1 device.
     */

    for (i = 0; i < 24; i++) {
        uint64_t D;
        D = (uint64_t)((uint64_t) tmp & (uint64_t) 0x800000) / (uint64_t) 8388608;
        tmp = (tmp & (uint32_t) 0x7FFFFF) * (uint32_t) 2;
        D = D ^ ((uint64_t)((uint64_t) crc & (uint64_t) 0x80) / (uint64_t) 128);
        crc = (crc & 0x7FU) * 2U;
        D = D * (uint64_t) 7;
        crc = crc ^ (uint32_t) D;
    }

    /* Return the PMIC SPI MCRC value */
    return (uint8_t) crc;
}

/**
 * @brief Read PMIC register.
 * This function reads the PMIC register using SPI
 *
 * @param pSpiHandle    SPI handle.
 * @param addr          Address of the register to read.
 * @param pData         Pointer to the read register.
 */
int32_t PMIC_spiRead(Spi_handle  *pSpiHandle, uint8_t addr, uint8_t *pData)
{
    int32_t     status          = SystemP_SUCCESS;
    uint8_t     crc             = 0U;
    uint8_t     readCrc         = 0U;
    uint16_t    txData[2U]      = {0U, 0U};
    uint16_t    statusData[2U]  = {0U, 0U};

    /* Clear status data */
    statusData[0U]  = 0U;
    statusData[1U]  = 0U;

    /* Compute CRC */
    crc = PMIC_calcCRC8(addr, CMD_RD_EN, 0U);

    /* TX data */
    txData[0U]  = (addr << CMD_SHIFT)   | CMD_RD_EN;
    txData[1U]  = (0U   << DAT_SHIFT)   | crc;

    /* Drive CS pin low */
    if(PMIC_TPS653860XX_INVALID_CS != pSpiHandle->csPin)
    {
        GPIO_writePin(pSpiHandle->csPin, 0U);

        /* Minimum 250 ns between falling edge of CS and rising edge of CLK */
        ClockP_usleep(1U);
    }

    /* Write 2 words of 16 bits each */
    SPI_writeDataNonBlocking(pSpiHandle->spiBaseAddr, txData[0U]);
    SPI_writeDataNonBlocking(pSpiHandle->spiBaseAddr, txData[1U]);

    /* Read status */
    statusData[0U] = SPI_readDataBlockingFIFO(pSpiHandle->spiBaseAddr);
    statusData[1U] = SPI_readDataBlockingFIFO(pSpiHandle->spiBaseAddr);

    /* Drive CS pin high */
    if(PMIC_TPS653860XX_INVALID_CS != pSpiHandle->csPin)
    {
        /* Minimum 45 ns between last falling edge of CLK and rising edge of CS */
        ClockP_usleep(1U);

        GPIO_writePin(pSpiHandle->csPin, 1U);
    }

    /* Minimum 500 ns between 2 SPI frames */
    ClockP_usleep(1U);

    /* Read SPI data */
    *(pData) = (uint8_t)((statusData[1U] >> 8U) & 0xFFU);

    /* Compute CRC on read data */
    readCrc = PMIC_calcCRC8(
                        (uint8_t)((statusData[0U] >> 8U) & 0xFFU),
                        (uint8_t)(statusData[0U] & 0xFFU),
                        (uint8_t)((statusData[1U] >> 8U) & 0xFFU));

    /* Check CRC */
    if(readCrc != (uint8_t)(statusData[1U] & 0xFFU))
    {
        /* CRC mismatch or Error status bit is set */
        status = SystemP_FAILURE;
    }
    else if(1U == (statusData[0U] & 1U))
    {
        status = DUMP_ERR_STATUS_REG;
    }

    return status;
}