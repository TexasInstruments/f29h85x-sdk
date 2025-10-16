/*
*  Copyright (C) 2025 Texas Instruments Incorporated
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
*  \file pmic_user_reg_cfg_tps65036xx.c
*
*  \brief This is a PMIC User register config example will set thermal, vmon and gpio configurations.
*         Set/Get/clear IRQ mask and flag. Use Pmic_io(Rx/Tx)Byte Api to direct access of register.
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "board.h"
#include "inc/stw_types.h"
#include "DebugP.h"
#include "pmic_tps65036xx.h"
#include "ClockP.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CUSTOMER_SCRATCH1       (0x0AU)
#define CONFIG_PMIC0            (0U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void PMICApp_setVmonConf(const Pmic_CoreHandle_t *coreHandle);
static void PMICApp_setThermalConf(Pmic_CoreHandle_t *coreHandle);
static void PMICApp_setGpioConf(Pmic_CoreHandle_t *coreHandle);
static void PMICAPP_irqSetGetMask_esm(Pmic_CoreHandle_t *coreHandle);
static void PMICAPP_irqClrFlags(Pmic_CoreHandle_t *coreHandle);
static void PMICApp_ioWriteRead(Pmic_CoreHandle_t *coreHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void pmic_user_reg_cfg_main(void *args)
{
    Pmic_CoreHandle_t *handle;

    /* PMIC interface handle initialized by PMIC_open */
    handle = PMIC_getCoreHandle(CONFIG_PMIC0);
    DebugP_assert(NULL != handle);

    DebugP_log("\r\n");
    DebugP_log("Starting PMIC user space register configuration example !!\r\n");

    /* Unlock PMIC registers */
    Pmic_unlockRegs(handle);

    PMICApp_setVmonConf(handle);
    PMICApp_setThermalConf(handle);
    PMICApp_setGpioConf(handle);
    PMICAPP_irqClrFlags(handle);
    PMICAPP_irqSetGetMask_esm(handle);
    PMICApp_ioWriteRead(handle);

    DebugP_log("PMIC user space register configuration example is successful !!\r\n");
    DebugP_log("All tests have passed!!\r\n");

    return;
}

/* Enable voltage monitors and set threshold for BUCK3, LDO2, VMON 1,2 and VCC VMON */
static void PMICApp_setVmonConf(const Pmic_CoreHandle_t *coreHandle)
{
    int32_t status = PMIC_ST_SUCCESS;

    // Expected buck CFG
    Pmic_PwrBuckCfg_t expBuckCfg = {
        .validParams = (PMIC_BUCK_UV_THR_VALID | PMIC_BUCK_OV_THR_VALID |
                        PMIC_BUCK_ILIM_SEL_VALID | PMIC_BUCK_DEGLITCH_SEL_VALID | PMIC_BUCK_VMON_ONLY_VALID),
        .resource = PMIC_BUCK2,
        .uvThr = PMIC_BUCK_UV_THR_5P5_PCT,
        .ovThr = PMIC_BUCK_OV_THR_5P5_PCT,
        .ilimSel = PMIC_BUCK2_3_ILIM_3_A,
        .deglitchSel = PMIC_BUCK_DEGLITCH_SEL_50_US,
        .vmonOnly = (bool)FALSE,
    };
    // Actual Buck CFG
    Pmic_PwrBuckCfg_t actBuckCfg = {
        .validParams = (PMIC_BUCK_UV_THR_VALID | PMIC_BUCK_OV_THR_VALID |
                        PMIC_BUCK_ILIM_SEL_VALID | PMIC_BUCK_DEGLITCH_SEL_VALID | PMIC_BUCK_VMON_ONLY_VALID),
        .resource = PMIC_BUCK2
    };
    // Expected LDO CFG
    Pmic_PwrLdoCfg_t expLdoCfg = {
        .validParams = (PMIC_LDO_UV_THR_VALID | PMIC_LDO_OV_THR_VALID |
                        PMIC_LDO_ILIM_SEL_VALID | PMIC_LDO_DEGLITCH_SEL_VALID | PMIC_LDO_VMON_ONLY_VALID),
        .uvThr = PMIC_BUCK_UV_THR_5P5_PCT,
        .ovThr = PMIC_BUCK_OV_THR_5P5_PCT,
        .ilimSel = PMIC_BUCK2_3_ILIM_3_A,
        .deglitchSel = PMIC_BUCK_DEGLITCH_SEL_50_US,
        .vmonOnly = (bool)FALSE,
    };
    // Actual LDO CFG
    Pmic_PwrLdoCfg_t actLdoCfg = {
        .validParams = (PMIC_LDO_UV_THR_VALID | PMIC_LDO_OV_THR_VALID |
                        PMIC_LDO_ILIM_SEL_VALID | PMIC_LDO_DEGLITCH_SEL_VALID | PMIC_LDO_VMON_ONLY_VALID)
    };
    Pmic_PwrRsrcStat_t buck2Stat = {.resource = PMIC_BUCK2};
    Pmic_PwrRsrcStat_t LDOStat = {.resource = PMIC_LDO};

    DebugP_log("\r\n");
    DebugP_log("Setting BUCK2 configurations...\r\n");
    status = Pmic_pwrSetBuckCfg(coreHandle, &expBuckCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("BUCK2 configurations have been set\r\n");

    DebugP_log("Getting actual BUCK2 configurations...\r\n");
    status = Pmic_pwrGetBuckCfg(coreHandle, &actBuckCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("BUCK2 configurations have been obtained\r\n");

    DebugP_log("Validating BUCK2 configurations...\r\n");
    DebugP_assert(expBuckCfg.uvThr == actBuckCfg.uvThr);
    DebugP_assert(expBuckCfg.ovThr == actBuckCfg.ovThr);
    DebugP_assert(expBuckCfg.ilimSel == actBuckCfg.ilimSel);
    DebugP_assert(expBuckCfg.deglitchSel == actBuckCfg.deglitchSel);
    DebugP_assert(expBuckCfg.vmonOnly == actBuckCfg.vmonOnly);
    DebugP_log("BUCK2 configurations have been successfully validated\r\n");

    DebugP_log("Setting LDO configurations...\r\n");
    status = Pmic_pwrSetLdoCfg(coreHandle, &expLdoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("LDO configurations have been set\r\n");

    DebugP_log("Getting actual LDO configurations...\r\n");
    status = Pmic_pwrGetLdoCfg(coreHandle, &actLdoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("LDO configurations have been obtained\r\n");

    DebugP_log("Validating LDO configurations...\r\n");
    DebugP_assert(expLdoCfg.uvThr == actLdoCfg.uvThr);
    DebugP_assert(expLdoCfg.ovThr == actLdoCfg.ovThr);
    DebugP_assert(expLdoCfg.ilimSel == actLdoCfg.ilimSel);
    DebugP_assert(expLdoCfg.deglitchSel == actLdoCfg.deglitchSel);
    DebugP_assert(expLdoCfg.vmonOnly == actLdoCfg.vmonOnly);
    DebugP_log("LDO configurations have been successfully validated\r\n");

    /* Get BUCK2 status */
    status = Pmic_pwrGetRsrcStat(coreHandle, &buck2Stat);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    /* BUCK2 status report */
    DebugP_log("Voltage monitoring status:\r\n");
    DebugP_log("BUCK2 Active voltage status: %s\r\n", ((buck2Stat.active == (bool)true) ? "set" : "cleared"));
    DebugP_log("BUCK2 over voltage status: %s\r\n", ((buck2Stat.ov == (bool)true) ? "set" : "cleared"));
    DebugP_log("BUCK2 under voltage status: %s\r\n", ((buck2Stat.uv == (bool)true) ? "set" : "cleared"));
    DebugP_log("BUCK2 over voltage protection status: %s\r\n", ((buck2Stat.ovp == (bool)true) ? "set" : "cleared"));

    /* Get LDO status */
    status = Pmic_pwrGetRsrcStat(coreHandle, &LDOStat);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    /* LDO status report */
    DebugP_log("LDO Active voltage status: %s\r\n", ((LDOStat.active == (bool)true) ? "set" : "cleared"));
    DebugP_log("LDO over voltage status: %s\r\n", ((LDOStat.ov == (bool)true) ? "set" : "cleared"));
    DebugP_log("LDO under voltage status: %s\r\n", ((LDOStat.uv == (bool)true) ? "set" : "cleared"));
    DebugP_log("LDO over voltage protection status: %s\r\n", ((LDOStat.ovp == (bool)true) ? "set" : "cleared"));

    /* Success */
    DebugP_log("PMIC VMON and BUCK configuration and status report complete\r\n\n");
}

static void PMICApp_setGpioConf(Pmic_CoreHandle_t *coreHandle)
{
    int32_t status = PMIC_ST_SUCCESS;
    bool pinStatus;
    Pmic_GpioCfg_t expGpioCfg = {
        .validParams = (PMIC_FUNCTIONALITY_VALID | PMIC_POLARITY_VALID),
        .functionality = PMIC_GPIO_OUTPUT,
        .polarity = PMIC_NORMAL_POLARITY,
    };
    // Actual thermal configurations
    Pmic_GpioCfg_t actGPIOCfg = {
        .validParams = (PMIC_FUNCTIONALITY_VALID | PMIC_POLARITY_VALID)
    };


    DebugP_log("\r\n");
    DebugP_log("Setting GPIO output state as High...\r\n");
    status = Pmic_gpioSetCfg(coreHandle, PMIC_GPIO, &expGpioCfg);
    status = Pmic_gpioSetActivationState(coreHandle, (bool)TRUE);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    DebugP_log("Getting actual GPIO configurations...\r\n");
    status = Pmic_gpioGetCfg(coreHandle, PMIC_GPIO, &actGPIOCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("GPIO configurations have been obtained...\r\n");

    DebugP_log("Validating GPIO configurations, pin state: High...\r\n");
    DebugP_assert(expGpioCfg.functionality == actGPIOCfg.functionality);
    DebugP_assert(expGpioCfg.polarity == actGPIOCfg.polarity);
    DebugP_log("GPIO configurations have been successfully validated\r\n");

    status = Pmic_gpioGetActivationState(coreHandle, &pinStatus);
    DebugP_log("GPIO Pin status: %s\r\n",((pinStatus == (bool)true) ? "High" : "Low"));

    expGpioCfg.polarity = PMIC_NORMAL_POLARITY,

    DebugP_log("Setting GPO1 output state as LOW...\r\n");
    status = Pmic_gpioSetActivationState(coreHandle, (bool)FALSE);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    DebugP_log("Getting actual GPIO configurations...\r\n");
    status = Pmic_gpioGetCfg(coreHandle, PMIC_GPIO, &actGPIOCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("GPIO configurations have been obtained...\r\n");

    DebugP_log("Validating GPIO configurations, pin state: Low...\r\n");
    DebugP_assert(expGpioCfg.polarity == actGPIOCfg.polarity);
    DebugP_log("GPIO configurations have been successfully validated\r\n");

    status = Pmic_gpioGetActivationState(coreHandle, &pinStatus);
    DebugP_log("GPIO Pin status: %s\r\n",((pinStatus == (bool)true) ? "High" : "Low"));

    expGpioCfg.functionality = PMIC_GPIO_ESM_INPUT,
    DebugP_log("Setting GPO1 as ESM IN...\r\n");
    status = Pmic_gpioSetCfg(coreHandle, PMIC_GPIO, &expGpioCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    DebugP_log("Getting actual GPIO configurations...\r\n");
    status = Pmic_gpioGetCfg(coreHandle, PMIC_GPIO, &actGPIOCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("GPIO configurations have been obtained...\r\n");

    DebugP_log("Validating GPIO configurations, pin state: ESM IN...\r\n");
    DebugP_assert(expGpioCfg.functionality == actGPIOCfg.functionality);
    DebugP_log("GPIO configurations have been successfully validated\r\n");
}

static void PMICApp_setThermalConf(Pmic_CoreHandle_t *coreHandle)
{
    int32_t status = PMIC_ST_SUCCESS;
    bool val = (bool)FALSE;
    // Expected thermal configurations
    Pmic_PwrTsdCfg_t expThermalCfg = {
        .validParams = PMIC_TWARN_STAY_IN_SAFE_STATE_VALID | PMIC_TSD_IMM_LEVEL_VALID | PMIC_TWARN_LEVEL_VALID,
        .twarnStayInSafeState = (bool)true,
        .tsdImmLevel = PMIC_TSD_IMM_LEVEL_160C,
        .twarnLevel = PMIC_TWARN_LEVEL_130C,
    };
    // Actual thermal configurations
    Pmic_PwrTsdCfg_t actThermalCfg = {
        .validParams = PMIC_TWARN_STAY_IN_SAFE_STATE_VALID | PMIC_TSD_IMM_LEVEL_VALID | PMIC_TWARN_LEVEL_VALID
    };
    DebugP_log("\r\n");
    DebugP_log("Setting thermal shutdown configurations\r\n");
    status = Pmic_pwrSetTsdCfg(coreHandle, &expThermalCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("Thermal shutdown configurations have been set\r\n");

    DebugP_log("Getting actual thermal shutdown configurations...\r\n");
    status = Pmic_pwrGetTsdCfg(coreHandle, &actThermalCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("Thermal configurations have been obtained\r\n");

    DebugP_log("Validating thermal shutdown configurations...\r\n");
    DebugP_assert(expThermalCfg.twarnStayInSafeState == actThermalCfg.twarnStayInSafeState);
    DebugP_assert(expThermalCfg.tsdImmLevel == actThermalCfg.tsdImmLevel);
    DebugP_assert(expThermalCfg.twarnLevel == actThermalCfg.twarnLevel);
    DebugP_log("Thermal configurations have been successfully validated\r\n");

    /* Get the thermal statuses */
    status = Pmic_pwrGetTsdImmStat(coreHandle, &val);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    /* Status report */
    DebugP_log("Thermal monitoring status:\r\n");
    DebugP_log("Thermal immediate shutdown bit: %d\r\n", val);

    /* Success */
    DebugP_log("PMIC thermal monitoring configuration and get status complete\r\n\n");
}

static void PMICAPP_irqSetGetMask_esm(Pmic_CoreHandle_t *coreHandle)
{
    int32_t status = PMIC_ST_SUCCESS;
    Pmic_IrqMask_t actIrqMasks[] = {
        {.irqNum = PMIC_ESM_MCU_RST_INT},
    };

    DebugP_log("\r\n");
    DebugP_log("Setting IRQ mask...\r\n");
    status = Pmic_irqSetMask(coreHandle, PMIC_ESM_MCU_RST_INT, (bool)TRUE);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    // Get actual mask configurations and compare expected vs. actual values
    DebugP_log("Validating IRQ mask status...\r\n");
    status = Pmic_irqGetMask(coreHandle, 1U, actIrqMasks);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_assert(actIrqMasks[0U].mask == (bool)TRUE);
    DebugP_log("IRQ mask have been successfully validated\r\n");

    // Unmask interrupts
    status = Pmic_irqSetMask(coreHandle, PMIC_ESM_MCU_RST_INT, (bool)FALSE);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    // Get actual mask configurations and compare expected vs. actual values
    status = Pmic_irqGetMask(coreHandle, 1U, actIrqMasks);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_assert(actIrqMasks[0U].mask == (bool)FALSE);
}

void PMICAPP_irqClrFlags(Pmic_CoreHandle_t *coreHandle)
{
    int32_t status = PMIC_ST_SUCCESS;
    uint8_t irqNum = 0U, iter = 0U;
    bool flag = (bool)TRUE;
    Pmic_IrqStat_t irqStat;

    // Get status of all PMIC IRQs
    DebugP_log("\r\n");
    DebugP_log("Get status of all IRQ's...\r\n");
    status = Pmic_irqGetStat(coreHandle, &irqStat);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    // While there are still IRQ statuses remaining...
    DebugP_log("Clear next IRQ's if its flag set\r\n");
    while ((status != PMIC_ST_WARN_NO_IRQ_REMAINING) && (iter != UINT8_MAX))
    {
        // Get next IRQ
        status = Pmic_irqGetNextFlag(&irqStat, &irqNum);

        if (status == PMIC_ST_SUCCESS)
        {
            // Check whether IRQ is set
            status = Pmic_irqGetFlag(coreHandle, irqNum, &flag);
            DebugP_assert(status == PMIC_ST_SUCCESS);
            if (flag == (bool)TRUE)
            {
                // Clear IRQ
                status = Pmic_irqClrFlag(coreHandle, irqNum);
                DebugP_assert(status == PMIC_ST_SUCCESS);

                // Check whether IRQ is cleared
                status = Pmic_irqGetFlag(coreHandle, irqNum, &flag);
                DebugP_assert(status == PMIC_ST_SUCCESS);
                DebugP_assert(flag == (bool)FALSE);
            }
        }

        iter++;
    }
    DebugP_log("Cleared IRQ's whose flag were set\r\n");
}

static void PMICApp_ioWriteRead(Pmic_CoreHandle_t *coreHandle)
{
    int32_t status = PMIC_ST_SUCCESS;
    uint8_t initVal = 0U, expVal = 0U, actVal = 0U;

    // Get initial CUSTOMER_SCRATCH1 register value
    DebugP_log("\r\n");
    DebugP_log("Reading initial value of CUSTOMER_SCRATCH1...\r\n");
    status = Pmic_ioRxByte(coreHandle, CUSTOMER_SCRATCH1, &initVal);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("Initial value of CUSTOMER_SCRATCH1: %u\r\n", initVal);

    // Write expected CUSTOMER_SCRATCH1 register value
    expVal = ~initVal;
    DebugP_log("Writing expected value of %u to CUSTOMER_SCRATCH1...\r\n", expVal);
    status = Pmic_ioTxByte(coreHandle, CUSTOMER_SCRATCH1, expVal);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("Write complete\r\n");

    // Get actual CUSTOMER_SCRATCH1 register value
    DebugP_log("Reading actual value of CUSTOMER_SCRATCH1...\r\n");
    status = Pmic_ioRxByte(coreHandle, CUSTOMER_SCRATCH1, &actVal);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("Actual CUSTOMER_SCRATCH1 register value: %u\r\n", actVal);

    // Compare
    // DebugP_assert(actVal != initVal);
    DebugP_assert(actVal == expVal);
    DebugP_log("Direct register write and read successful\r\n", actVal);
}