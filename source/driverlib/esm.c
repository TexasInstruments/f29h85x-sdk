//###########################################################################
//
// FILE:   esm.c
//
// TITLE:  C29x Error Signalling Module (ESM) driver.
//
//###########################################################################
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


#include "esm.h"

//*****************************************************************************
//
// ESM_configErrorEvent
//
//*****************************************************************************
void ESM_configErrorEvent(uint32_t base, const ESM_ConfigParams *configParams)
{
    //
    // Check the arguments
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = configParams->event / 32U;
    uint32_t eventNum = configParams->event % 32U;

    //
    // Set the Interrupt enable bit.
    //
    if(configParams->enableInterrupt == true)
    {
        HWREG(base + ESM_CPU_O_INTR_EN_SET(groupNum)) = (uint32_t)1U << eventNum;
    }

    //
    // Set the interrupt priority level.
    //
    if(configParams->interruptPriorityLevel ==
                                        ESM_INTERRUPT_PRIORITY_LEVEL_HIGH)
    {
        HWREG(base + ESM_CPU_O_INT_PRIO(groupNum)) |= 1U << eventNum;
    }
    else
    {
        HWREG(base + ESM_CPU_O_INT_PRIO(groupNum)) &= ~(1U << eventNum);
    }

    //
    // Set the influence on the Error pin.
    //
    if(configParams->enableInfluenceOnErrorPin == true)
    {
        HWREG(base + ESM_CPU_O_PIN_EN_SET(groupNum)) = (uint32_t)1U << eventNum;
    }
    else
    {
        HWREG(base + ESM_CPU_O_PIN_EN_CLR(groupNum)) = (uint32_t)1U << eventNum;
    }

    //
    // Set the influemce on the Critical priority interrupt.
    //
    if(configParams->enableCriticalPriorityInterruptInfluence == true)
    {
        HWREG(base + ESM_CPU_O_CRIT_EN_SET(groupNum)) = (uint32_t)1U << eventNum;
    }
    else
    {
        HWREG(base + ESM_CPU_O_CRIT_EN_CLR(groupNum)) = (uint32_t)1U << eventNum;
    }
}

//*****************************************************************************
//
// ESM_setErrorPinCounterPreload
//
//*****************************************************************************
void ESM_setErrorPinCounterPreload(uint32_t value)
{
    //
    // Set the preload value.
    //
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CNTR_PRE) = value;
}

//*****************************************************************************
//
// ESM_setWatchdogCounterPreload
//
//*****************************************************************************
void ESM_setWatchdogCounterPreload(uint32_t base, uint32_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base) && (base != ESMSYSTEM_BASE));

    //
    // Set the preload value.
    //
    HWREG(base + ESM_CPU_O_HI_PRI_WD_CNTR_PRE) = value;
}

//*****************************************************************************
//
// ESM_setPWMCounterPreload
//
//*****************************************************************************
void ESM_setPWMCounterPreload(uint32_t highValue, uint32_t lowValue)
{
    //
    // Check the arguments.
    //
    ASSERT(highValue <= ESM_SYS_PWMH_PIN_CNTR_PRE_COUNT_M);
    ASSERT(lowValue <= ESM_SYS_PWML_PIN_CNTR_PRE_COUNT_M);

    //
    // Set the PWM period value
    //
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PWMH_PIN_CNTR_PRE) = highValue;
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PWML_PIN_CNTR_PRE) = lowValue;
}

//*****************************************************************************
//
// ESM_configErrorPin
//
//*****************************************************************************
void ESM_configErrorPin(const ESM_ErrorPinConfigParams *configParams)
{
    //
    // Configure the operation mode.
    //
    HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) =
                       (HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) &
                        ~(ESM_SYS_PIN_CTRL_KEY_M)) |
                       ((uint8_t)configParams->mode << ESM_SYS_PIN_CTRL_KEY_S);

    //
    // Configure the ESM error output pin mode
    //
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) =
                (HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) &
                ~(ESM_SYS_PIN_CTRL_PWM_EN_M)) |
                ((uint32_t)configParams->pinMode << ESM_SYS_PIN_CTRL_PWM_EN_S);

    //
    // Set the polarity of the Level mode
    //
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) =
            (HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) &
            ~(ESM_SYS_PIN_CTRL_POLARITY_M)) |
            ((uint32_t)configParams->polarity << ESM_SYS_PIN_CTRL_POLARITY_S);

    if(configParams->enableErrorPinMonitor)
    {
        //
        // Enable the Error pin monitor.
        //
        HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_ERRPIN_MON_CFG) =
                                                ESM_ERROR_PIN_MONITOR_ENABLE;
    }
    else
    {
        //
        // Disable the Error pin monitor.
        //
        HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_ERRPIN_MON_CFG) =
                                            ESM_ERROR_PIN_MONITOR_DISABLE;
    }
}

//*****************************************************************************
//
// ESM_config
//
//*****************************************************************************
void ESM_config(uint32_t base, ESM_EventMap event, ESM_ConfigType configType)
{
    //
    // Check the arguments
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = (uint32_t)event / 32U;
    uint32_t eventNum = (uint32_t)event % 32U;

    //
    // Set the Interrupt enable bit
    //
    HWREG(base + ESM_CPU_O_INTR_EN_SET(groupNum)) = (uint32_t)1U << eventNum;

    switch(configType)
    {
        case ESM_CONFIG_LOW_PRIORITY_INTERRUPT:
            //
            // Configure Low priority interrupt
            //
            HWREG(base + ESM_CPU_O_INT_PRIO(groupNum)) &= ~(1U << eventNum);
            break;

        case ESM_CONFIG_NMI:
            //
            // Configure NMI
            //
            ASSERT(!(base == ESMSYSTEM_BASE));
            HWREG(base + ESM_CPU_O_INT_PRIO(groupNum)) |= 1U << eventNum;
            break;

        case ESM_CONFIG_CRITICAL_PRIORITY_INTERRUPT:
            //
            // Configure Critical priority interrupt
            //
            HWREG(base + ESM_CPU_O_CRIT_EN_SET(groupNum)) = (uint32_t)1U << eventNum;
            break;

        case ESM_CONFIG_ERROR_PIN:
            //
            // Configure influence on Error Pin
            //
            ASSERT(base == ESMSYSTEM_BASE);
            HWREG(base + ESM_CPU_O_PIN_EN_SET(groupNum)) = (uint32_t)1U << eventNum;
            break;

        default:
            ASSERT((bool)false);
            break;
    }
}