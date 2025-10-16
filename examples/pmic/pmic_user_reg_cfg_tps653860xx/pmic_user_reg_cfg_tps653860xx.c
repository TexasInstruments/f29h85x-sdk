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
*  \file pmic_user_reg_cfg_tps653860xx.c
*
*  \brief This is a PMIC User register config example will set gpio, IRQ, Timer, vmon and Power configurations.
          Set/Get/clear IRQ mask and flag. Use Pmic_io(Rx/Tx)Byte Api to direct access of register
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "board.h"
#include "inc/stw_types.h"
#include "DebugP.h"
#include "pmic_tps653860xx.h"
#include "ClockP.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CUSTOMER_SCRATCH1       (0x68U)
#define PMIC_REG_STATE_LOCK     (1U)
#define CONFIG_PMIC0            (0U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void PMICApp_setPldoLdoCfg(Pmic_CoreHandle_t *coreHandle);
static void PMICApp_setGpioConf(Pmic_CoreHandle_t *coreHandle);
static void PMICAPP_irqSetGetMaskCfg_WD(Pmic_CoreHandle_t *coreHandle);
static void PMICAPP_irqClrFlags(Pmic_CoreHandle_t *coreHandle);
static void PMICApp_setTimerCfg(Pmic_CoreHandle_t *coreHandle);
static void PMICApp_ioWriteRead(Pmic_CoreHandle_t *coreHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void pmic_user_reg_cfg_main(void *args)
{
    Pmic_CoreHandle_t* handle;
    uint8_t val = (uint8_t)0;

    /* PMIC interface handle initialized by PMIC_open */
    handle = PMIC_getCoreHandle(CONFIG_PMIC0);
    DebugP_assert(NULL != handle);

    /* Unlock the PMIC registers if locked */
    Pmic_getRegLockState(handle, &val);
    if(val == PMIC_REG_STATE_LOCK)
    {
        Pmic_setRegLockState(handle,PMIC_LOCK_DISABLE);
    }

    DebugP_log("\r\n");
    DebugP_log("Starting PMIC user space register configuration example !!\r\n");

    PMICApp_setPldoLdoCfg(handle);
    PMICApp_setGpioConf(handle);
    PMICAPP_irqSetGetMaskCfg_WD(handle);
    PMICAPP_irqClrFlags(handle);
    PMICApp_setTimerCfg(handle);
    PMICApp_ioWriteRead(handle);

    DebugP_log("PMIC user space register configuration example is successful !!\r\n");
    DebugP_log("All tests have passed!!\r\n");

    return;
}

static void PMICApp_setPldoLdoCfg(Pmic_CoreHandle_t *coreHandle)
{
    uint32_t status = PMIC_ST_SUCCESS;
    /*Setting PLDO1 Configuration*/
    Pmic_PwrPldoCfg_t expPldoCfg = {
        .validParams = PMIC_PWR_CFG_PLDO_MODE_VALID_SHIFT | PMIC_PWR_CFG_PLDO_TRACKING_MODE_VALID_SHIFT |
                       PMIC_PWR_CFG_PLDO_LVL_VALID_SHIFT | PMIC_PWR_CFG_PLDO_ILIM_LVL_VALID_SHIFT |
                       PMIC_PWR_CFG_PLDO_ILIM_DGL_VALID_SHIFT | PMIC_PWR_CFG_PLDO_VMON_THR_VALID_SHIFT |
                       PMIC_PWR_CFG_PLDO_VMON_DGL_VALID_SHIFT,
        .pldo = PMIC_PWR_PLDO1,
        .mode = PMIC_PWR_PLDO_EN_AS_LDO_IN_OPER,
        .trackingMode = (bool)FALSE,
        .lvl = PMIC_PWR_LDO_LVL_1P3V,
        .ilimLvl = PMIC_PWR_LDO_ILIM_LVL_OPTION_0,
        .ilimDgl = PMIC_PWR_LDO_ILIM_DEGLITCH_1_MS,
        .vmonThr = PMIC_PWR_PLDO_VMON_THR_MAX,
        .vmonDgl = PMIC_PWR_RSRC_VMON_DGL_MAX,
    };

    Pmic_PwrPldoCfg_t acpPldoCfg = {
        .validParams = PMIC_PWR_CFG_PLDO_MODE_VALID_SHIFT | PMIC_PWR_CFG_PLDO_TRACKING_MODE_VALID_SHIFT |
                       PMIC_PWR_CFG_PLDO_LVL_VALID_SHIFT | PMIC_PWR_CFG_PLDO_ILIM_LVL_VALID_SHIFT |
                       PMIC_PWR_CFG_PLDO_ILIM_DGL_VALID_SHIFT | PMIC_PWR_CFG_PLDO_VMON_THR_VALID_SHIFT |
                       PMIC_PWR_CFG_PLDO_VMON_DGL_VALID_SHIFT,
        .pldo = PMIC_PWR_PLDO1,
    };

    Pmic_PwrRsrcStat_t PldoStatus = {
        .validParams = PMIC_PWR_RSRC_STAT_OV_ERR_VALID | PMIC_PWR_RSRC_STAT_UV_ERR_VALID |
                       PMIC_PWR_RSRC_STAT_ILIM_ERR_VALID | PMIC_PWR_RSRC_STAT_TSD_ERR_VALID |
                       PMIC_PWR_RSRC_STAT_TSD_WARN_VALID,
        .pwrRsrc = PMIC_PWR_PLDO1,
    };

    DebugP_log("\r\n");
    DebugP_log("Setting PLDO1 config...\r\n");
    status = Pmic_pwrSetPldoCfg(coreHandle, &expPldoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    status = Pmic_pwrGetPldoCfg(coreHandle, &acpPldoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("Validating PLDO1 configurations...\r\n");
    DebugP_assert(expPldoCfg.mode == acpPldoCfg.mode);
    DebugP_assert(expPldoCfg.trackingMode == acpPldoCfg.trackingMode);
    DebugP_assert(expPldoCfg.lvl == acpPldoCfg.lvl);
    DebugP_assert(expPldoCfg.ilimLvl == acpPldoCfg.ilimLvl);
    DebugP_assert(expPldoCfg.ilimDgl == acpPldoCfg.ilimDgl);
    DebugP_assert(expPldoCfg.vmonThr == acpPldoCfg.vmonThr);
    DebugP_assert(expPldoCfg.vmonDgl == acpPldoCfg.vmonDgl);
    DebugP_log("PLDO1 configurations have been successfully validated\r\n");

    status = Pmic_pwrGetRsrcStat(coreHandle, &PldoStatus);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("PLDO voltage, thermal and current limit status\r\n");
    DebugP_log("PLDO1 over voltage error status: %s\r\n", ((PldoStatus.ovErr == (bool)true) ? "set" : "cleared"));
    DebugP_log("PLDO1 under voltage error status: %s\r\n", ((PldoStatus.uvErr == (bool)true) ? "set" : "cleared"));
    DebugP_log("PLDO1 current limit error status: %s\r\n", ((PldoStatus.ilimErr == (bool)true) ? "set" : "cleared"));
    DebugP_log("PLDO1 Thermal shutdown warning status: %s\r\n", ((PldoStatus.tsdErr == (bool)true) ? "set" : "cleared"));
    DebugP_log("PLDO1 Thermal shutdown error status: %s\r\n", ((PldoStatus.tsdWarn == (bool)true) ? "set" : "cleared"));

    /*Setting LDO2 Configuration*/
    Pmic_PwrLdoCfg_t expLdoCfg = {
        .validParams = PMIC_PWR_CFG_LDO_MODE_VALID_SHIFT | PMIC_PWR_CFG_LDO_ILIM_LVL_VALID_SHIFT |
                       PMIC_PWR_CFG_LDO_ILIM_DGL_VALID_SHIFT | PMIC_PWR_CFG_LDO_VMON_THR_VALID_SHIFT |
                       PMIC_PWR_CFG_LDO_VMON_DGL_VALID_SHIFT,
        .ldo = PMIC_PWR_LDO2,
        .mode = PMIC_PWR_LDO_EN_AS_LDO_IN_OPER,
        .ilimLvl = PMIC_PWR_LDO_ILIM_LVL_OPTION_0,
        .ilimDgl = PMIC_PWR_LDO_ILIM_DEGLITCH_1_MS,
        .vmonThr = PMIC_PWR_PLDO_VMON_THR_MAX,
        .vmonDgl = PMIC_PWR_RSRC_VMON_DGL_MAX,
    };

    Pmic_PwrLdoCfg_t acpLdoCfg = {
        .validParams = PMIC_PWR_CFG_LDO_MODE_VALID_SHIFT | PMIC_PWR_CFG_LDO_ILIM_LVL_VALID_SHIFT |
                       PMIC_PWR_CFG_LDO_ILIM_DGL_VALID_SHIFT | PMIC_PWR_CFG_LDO_VMON_THR_VALID_SHIFT |
                       PMIC_PWR_CFG_LDO_VMON_DGL_VALID_SHIFT,
        .ldo = PMIC_PWR_LDO2,
    };

    Pmic_PwrRsrcStat_t ldoStatus = {
        .validParams = PMIC_PWR_RSRC_STAT_OV_ERR_VALID_SHIFT | PMIC_PWR_RSRC_STAT_UV_ERR_VALID_SHIFT |
                       PMIC_PWR_RSRC_STAT_ILIM_ERR_VALID_SHIFT | PMIC_PWR_RSRC_STAT_TSD_ERR_VALID_SHIFT |
                       PMIC_PWR_RSRC_STAT_TSD_WARN_VALID_SHIFT,
        .pwrRsrc = PMIC_PWR_LDO2,
    };

    DebugP_log("\r\n");
    DebugP_log("Setting LDO2 config...\r\n");
    status = Pmic_pwrSetLdoCfg(coreHandle, &expLdoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    status = Pmic_pwrGetLdoCfg(coreHandle, &acpLdoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("Validating LDO2 configurations...\r\n");
    DebugP_assert(expLdoCfg.mode == acpLdoCfg.mode);
    DebugP_assert(expLdoCfg.ilimLvl == acpLdoCfg.ilimLvl);
    DebugP_assert(expLdoCfg.ilimDgl == acpLdoCfg.ilimDgl);
    DebugP_assert(expLdoCfg.vmonThr == acpLdoCfg.vmonThr);
    DebugP_assert(expLdoCfg.vmonDgl == acpLdoCfg.vmonDgl);
    DebugP_log("LDO2 configurations have been successfully validated\r\n");

    status = Pmic_pwrGetRsrcStat(coreHandle, &ldoStatus);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("LDO voltage, thermal and current limit status\r\n");
    DebugP_log("LDO2 over voltage error status: %s\r\n", ((ldoStatus.ovErr == (bool)true) ? "set" : "cleared"));
    DebugP_log("LDO2 under voltage error status: %s\r\n", ((ldoStatus.uvErr == (bool)true) ? "set" : "cleared"));
    DebugP_log("LDO2 current limit error status: %s\r\n", ((ldoStatus.ilimErr == (bool)true) ? "set" : "cleared"));
    DebugP_log("LDO2 Thermal shutdown warning status: %s\r\n", ((ldoStatus.tsdErr == (bool)true) ? "set" : "cleared"));
    DebugP_log("LDO2 Thermal shutdown error status: %s\r\n", ((ldoStatus.tsdWarn == (bool)true) ? "set" : "cleared"));

    /* Success */
    DebugP_log("PMIC PLDO and LDO configuration and status report complete\r\n");
}

static void PMICApp_setGpioConf(Pmic_CoreHandle_t *coreHandle)
{
    int32_t status = PMIC_ST_SUCCESS;
    bool pinStatus;
    Pmic_GpioCfg_t expGpoCfg = {
        .validParams = PMIC_CFG_GPO1_VALID_SHIFT,
        .gpo1 = PMIC_GPO1_HIGH_LVL,
    };
    // Actual thermal configurations
    Pmic_GpioCfg_t actGPOCfg = {
        .validParams = PMIC_CFG_GPO1_VALID_SHIFT
    };

    DebugP_log("\r\n");
    DebugP_log("Setting GPO1 output state as High...\r\n");
    status = Pmic_gpioSetCfg(coreHandle, &expGpoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    DebugP_log("Getting actual GPIO configurations...\r\n");
    status = Pmic_gpioGetCfg(coreHandle, &actGPOCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("GPIO configurations have been obtained...\r\n");

    DebugP_log("Validating GPIO configurations, pin state: High...\r\n");
    DebugP_assert(expGpoCfg.gpo1 == actGPOCfg.gpo1);
    DebugP_log("GPIO configurations have been successfully validated\r\n");

    status = Pmic_gpioGetOutputVal(coreHandle, PMIC_GPO1, &pinStatus);
    DebugP_log("GPIO Pin status: %s\r\n",((pinStatus == (bool)true) ? "High" : "Low"));

    expGpoCfg.gpo1 = PMIC_GPO1_LOW_LVL;

    DebugP_log("Setting GPO1 output state as LOW...\r\n");
    status = Pmic_gpioSetCfg(coreHandle, &expGpoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    DebugP_log("Getting actual GPIO configurations...\r\n");
    status = Pmic_gpioGetCfg(coreHandle, &actGPOCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("GPIO configurations have been obtained...\r\n");

    DebugP_log("Validating GPIO configurations, pin state: Low...\r\n");
    DebugP_assert(expGpoCfg.gpo1 == actGPOCfg.gpo1);
    DebugP_log("GPIO configurations have been successfully validated\r\n");

    status = Pmic_gpioGetOutputVal(coreHandle, PMIC_GPO1, &pinStatus);
    DebugP_log("GPIO Pin status: %s\r\n",((pinStatus == (bool)true) ? "High" : "Low"));

    expGpoCfg.gpo1 = PMIC_GPO1_LOW_LVL;
    DebugP_log("Setting GPO1 as NINT...\r\n");
    status = Pmic_gpioSetCfg(coreHandle, &expGpoCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    DebugP_log("Getting actual GPIO configurations...\r\n");
    status = Pmic_gpioGetCfg(coreHandle, &actGPOCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("GPIO configurations have been obtained...\r\n");

    DebugP_log("Validating GPIO configurations, pin state: NINT...\r\n");
    DebugP_assert(expGpoCfg.gpo1 == actGPOCfg.gpo1);
    DebugP_log("GPIO configurations have been successfully validated\r\n");
}

static void PMICAPP_irqSetGetMaskCfg_WD(Pmic_CoreHandle_t *coreHandle)
{
    int32_t status = PMIC_ST_SUCCESS;
    Pmic_IrqCfg_t expIrqMasks[] = {
        {
            .validParams = PMIC_IRQ_CFG_ALL_VALID_SHIFT,
            .irqNum = PMIC_WD_TH1_ERR_INT,
            .config = PMIC_IRQ_CONFIG0_INT_SET,
        },
        {
            .validParams = PMIC_IRQ_CFG_ALL_VALID_SHIFT,
            .irqNum = PMIC_WD_TH2_ERR_INT,
            .config = PMIC_IRQ_CONFIG0_INT_SET,
        },
    };
    Pmic_IrqCfg_t actIrqMasks[] = {
        {
            .validParams = PMIC_IRQ_CFG_ALL_VALID_SHIFT,
            .irqNum = PMIC_WD_TH1_ERR_INT,
            .config = PMIC_IRQ_CONFIG0_INT_SET,
        },
        {
            .validParams = PMIC_IRQ_CFG_ALL_VALID_SHIFT,
            .irqNum = PMIC_WD_TH2_ERR_INT,
            .config = PMIC_IRQ_CONFIG0_INT_SET,
        },
    };

    // Mask interrupts
    expIrqMasks[0U].mask = (bool)TRUE;
    expIrqMasks[1U].mask = (bool)TRUE;

    DebugP_log("\r\n");
    DebugP_log("Setting multiple IRQ mask and configs...\r\n");
    status = Pmic_irqSetCfgs(coreHandle, 2U, expIrqMasks);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    // Get actual mask configurations and compare expected vs. actual values
    DebugP_log("Validating IRQ mask status...\r\n");
    status = Pmic_irqGetCfgs(coreHandle, 2U, actIrqMasks);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_assert(expIrqMasks[0U].mask == actIrqMasks[0U].mask);
    DebugP_assert(expIrqMasks[1U].mask == actIrqMasks[1U].mask);
    DebugP_log("IRQ mask have been successfully validated\r\n");

    // Unmask interrupts
    expIrqMasks[0U].mask = (bool)FALSE;
    expIrqMasks[1U].mask = (bool)FALSE;
    status = Pmic_irqSetCfgs(coreHandle, 2U, expIrqMasks);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    // Get actual mask configurations and compare expected vs. actual values
    status = Pmic_irqGetCfgs(coreHandle, 2U, actIrqMasks);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_assert(expIrqMasks[0U].mask == actIrqMasks[0U].mask);
    DebugP_assert(expIrqMasks[1U].mask == actIrqMasks[1U].mask);
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


static void PMICApp_setTimerCfg(Pmic_CoreHandle_t *coreHandle)
{
    uint32_t count;
    int32_t status = PMIC_ST_SUCCESS;
    Pmic_timerCfg_t exptimerCfg = {
        .validParams = PMIC_CFG_TMR_PRESCALE_VALID_SHIFT | PMIC_CFG_TMR_MODE_VALID_SHIFT,
        .prescale = PMIC_TMR_PRESCALE_1049_MS,
        .mode = PMIC_TMR_MODE_OPER_SEQ,
    };

    Pmic_timerCfg_t acptimerCfg = {
        .validParams = PMIC_CFG_TMR_PRESCALE_VALID_SHIFT | PMIC_CFG_TMR_MODE_VALID_SHIFT,
    };

    DebugP_log("\r\n");
    DebugP_log("Setting PMIC timer configurations...\r\n");
    status = Pmic_timerSetCfg(coreHandle, &exptimerCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    // Get actual timer configurations and compare expected vs. actual values
    DebugP_log("Validating Timer configurations...\r\n");
    status = Pmic_timerGetCfg(coreHandle, &acptimerCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    //set timer count
    status = Pmic_timerSetCnt(coreHandle, PMIC_TMR_CNT_MAX);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_assert(exptimerCfg.prescale == acptimerCfg.prescale);
    DebugP_assert(exptimerCfg.mode == acptimerCfg.mode);
    DebugP_log("Timer configurations have been successfully validated\r\n");

    //Add 3 sec delay to increment timer count
    DebugP_log("Adding delay of 3 sec to increment the timer count\r\n");
    ClockP_sleep(3);

    //Get the timer count
    Pmic_timerGetCnt(coreHandle, &count);
    DebugP_assert(status == PMIC_ST_SUCCESS);
    DebugP_log("Pmic Timer count value : %d\r\n",count);

    //clear the timer count
    status = Pmic_timerClr(coreHandle);
    DebugP_assert(status == PMIC_ST_SUCCESS);

    //stop the timer
    exptimerCfg.mode = PMIC_TMR_MODE_STOPPED;
    status = Pmic_timerSetCfg(coreHandle, &exptimerCfg);
    DebugP_assert(status == PMIC_ST_SUCCESS);
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
