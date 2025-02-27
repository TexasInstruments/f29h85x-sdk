//###########################################################################
//
// FILE:   esm.h
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

#ifndef ESM_H
#define ESM_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup esm_api ESM
//! \brief This module is used for ESM configurations.
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_esm_cpu.h"
#include "inc/hw_esm_sys.h"
#include "inc/hw_esm_safety_aggregator.h"
#include "cpu.h"
#include "debug.h"


//*****************************************************************************
//
// Values that are used in ESM_enableGlobal() and ESM_disableGlobal()
//
//*****************************************************************************
#define ESM_GLOBAL_ENABLE        0xFU
#define ESM_GLOBAL_DISABLE       0x0U

//*****************************************************************************
//
// Values that are used in ESM_enableHighPriorityWatchdog()
//
//*****************************************************************************
#define ESM_WATCHDOG_ENABLE     0xAU
#define ESM_WATCHDOG_DISABLE    0x0U

//*****************************************************************************
//
// Values that are used in ESM_enableErrorPinMonitor()
//
//*****************************************************************************
#define ESM_ERROR_PIN_MONITOR_ENABLE     0xAU
#define ESM_ERROR_PIN_MONITOR_DISABLE    0x0U

//*****************************************************************************
//
//! Values that are used in ESM_lockMMRConfig(), ESM_unlockMMRConfig() and
//! ESM_commitMMRConfig()
//
//*****************************************************************************
#define ESM_GLOBAL_EN_REG              ESM_CPU_MMR_CONFIG_LOCK_GLOBEL_EN_LOCK
#define ESM_GLOBAL_SOFT_RESET_REG ESM_CPU_MMR_CONFIG_LOCK_GLOBAL_SOFT_RST_LOCK
#define ESM_ERROR_PIN_REG              ESM_CPU_MMR_CONFIG_LOCK_ERRPIN_LOCK
#define ESM_ERROR_PIN_MONITOR_REG      ESM_CPU_MMR_CONFIG_LOCK_ERRPIN_MON_LOCK
#define ESM_HIGH_PRIORITY_WATCHDOG_REG ESM_CPU_MMR_CONFIG_LOCK_HI_PRI_WD_LOCK

//*****************************************************************************
//
//! The number of groups in ESM
//
//*****************************************************************************
#define ESM_NUM_GROUPS                  8U

//*****************************************************************************
//
//! Values that can be used to specify the ESM error event.
//
//*****************************************************************************
typedef enum
{
	ESM_EVENT_ErrorAggregator_CPU1_HPERR           = 0,
	ESM_EVENT_ErrorAggregator_CPU2_HPERR           = 1,
	ESM_EVENT_ErrorAggregator_CPU3_HPERR           = 2,
	ESM_EVENT_ErrorAggregator_CPU1_INT_HPERR       = 3,
	ESM_EVENT_ErrorAggregator_CPU2_INT_HPERR       = 4,
	ESM_EVENT_ErrorAggregator_CPU3_INT_HPERR       = 5,
	ESM_EVENT_CLOCKFAIL                            = 32,
	ESM_EVENT_DCC1_ERR                             = 33,
	ESM_EVENT_DCC2_ERR                             = 34,
	ESM_EVENT_DCC3_ERR                             = 35,
	ESM_EVENT_SYS_PLL_SLIP                         = 36,
	ESM_EVENT_CPU1RSn                              = 37,
	ESM_EVENT_CPU1WD                               = 38,
	ESM_EVENT_CPU1_ERAD_INT                        = 39,
	ESM_EVENT_CPU1_ERAD_NMI                        = 40,
	ESM_EVENT_ESM_CPU1_LOW_PRIORITY_INT            = 41,
	ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT           = 42,
	ESM_EVENT_LCM_CPU1SS_LCMPERR                   = 43,
	ESM_EVENT_CPU2RSn                              = 44,
	ESM_EVENT_CPU2WD                               = 45,
	ESM_EVENT_CPU2_ERAD_INT                        = 46,
	ESM_EVENT_CPU2_ERAD_NMI                        = 47,
	ESM_EVENT_ESM_CPU2_LOW_PRIORITY_INT            = 48,
	ESM_EVENT_ESM_CPU2_HIGH_PRIORITY_INT           = 49,
	ESM_EVENT_CPU3RSn                              = 50,
	ESM_EVENT_CPU3WD                               = 51,
	ESM_EVENT_CPU3_ERAD_INT                        = 52,
	ESM_EVENT_CPU3_ERAD_NMI                        = 53,
	ESM_EVENT_ESM_CPU3_LOW_PRIORITY_INT            = 54,
	ESM_EVENT_ESM_CPU3_HIGH_PRIORITY_INT           = 55,
	ESM_EVENT_RTDMA_LCM_CMP_ERR                    = 56,
	ESM_EVENT_ESM_ERRPIN_MON_EVT                   = 58,
	ESM_EVENT_ESM_PARITY_ERROR                     = 59,
	ESM_EVENT_HSM_HEA_INT_LO                       = 63,
	ESM_EVENT_HSM_HEA_INT_HI                       = 64,
	ESM_EVENT_INPUTXBAR63                          = 65,
	ESM_EVENT_INPUTXBAR64                          = 66,
	ESM_EVENT_EPWMXBAR1                            = 67,
	ESM_EVENT_EPWMXBAR2                            = 68,
	ESM_EVENT_EPWMXBAR3                            = 69,
	ESM_EVENT_EPWMXBAR4                            = 70,
	ESM_EVENT_EPWMXBAR5                            = 71,
	ESM_EVENT_EPWMXBAR6                            = 72,
	ESM_EVENT_EPWMXBAR7                            = 73,
	ESM_EVENT_EPWMXBAR8                            = 74,
	ESM_EVENT_EPWMXBAR9                            = 75,
	ESM_EVENT_EPWMXBAR10                           = 76,
	ESM_EVENT_EPWMXBAR11                           = 77,
	ESM_EVENT_EPWMXBAR12                           = 78,
	ESM_EVENT_EPWMXBAR13                           = 79,
	ESM_EVENT_EPWMXBAR14                           = 80,
	ESM_EVENT_EPWMXBAR15                           = 81,
	ESM_EVENT_EPWMXBAR16                           = 82,
	ESM_EVENT_OUTPUTXBAR1                          = 83,
	ESM_EVENT_OUTPUTXBAR2                          = 84,
	ESM_EVENT_OUTPUTXBAR3                          = 85,
	ESM_EVENT_OUTPUTXBAR4                          = 86,
	ESM_EVENT_OUTPUTXBAR5                          = 87,
	ESM_EVENT_OUTPUTXBAR6                          = 88,
	ESM_EVENT_OUTPUTXBAR7                          = 89,
	ESM_EVENT_OUTPUTXBAR8                          = 90,
	ESM_EVENT_OUTPUTXBAR9                          = 91,
	ESM_EVENT_OUTPUTXBAR10                         = 92,
	ESM_EVENT_OUTPUTXBAR11                         = 93,
	ESM_EVENT_OUTPUTXBAR12                         = 94,
	ESM_EVENT_OUTPUTXBAR13                         = 95,
	ESM_EVENT_OUTPUTXBAR14                         = 96,
	ESM_EVENT_OUTPUTXBAR15                         = 97,
	ESM_EVENT_OUTPUTXBAR16                         = 98,
	ESM_EVENT_WADI1_INTN_O                         = 99,
	ESM_EVENT_WADI2_INTN_O                         = 100,
	ESM_EVENT_CLB1_NMI                             = 102,
	ESM_EVENT_CLB2_NMI                             = 103,
	ESM_EVENT_CLB3_NMI                             = 104,
	ESM_EVENT_CLB4_NMI                             = 105,
	ESM_EVENT_CLB5_NMI                             = 106,
	ESM_EVENT_CLB6_NMI                             = 107,
	ESM_EVENT_EPG_INT                              = 108,
	ESM_EVENT_ECAT_NMIn                            = 109,
	ESM_EVENT_MCANA_ECC_CORR_PLS                   = 110,
	ESM_EVENT_MCANA_ECC_UNCORR_TS_PLS              = 111,
	ESM_EVENT_MCANB_ECC_CORR_PLS                   = 112,
	ESM_EVENT_MCANB_ECC_UNCORR_TS_PLS              = 113,
	ESM_EVENT_MCANC_ECC_CORR_PLS                   = 114,
	ESM_EVENT_MCANC_ECC_UNCORR_TS_PLS              = 115,
	ESM_EVENT_MCAND_ECC_CORR_PLS                   = 116,
	ESM_EVENT_MCAND_ECC_UNCORR_TS_PLS              = 117,
	ESM_EVENT_MCANE_ECC_CORR_PLS                   = 118,
	ESM_EVENT_MCANE_ECC_UNCORR_TS_PLS              = 119,
	ESM_EVENT_MCANF_ECC_CORR_PLS                   = 120,
	ESM_EVENT_MCANF_ECC_UNCORR_TS_PLS              = 121,
	ESM_EVENT_EMIF1_ERR                            = 122,
	ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU1            = 123,
	ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU2            = 124,
	ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU3            = 125,
	ESM_EVENT_ErrorAggregator_CPU1_LPERR           = 128,
	ESM_EVENT_ErrorAggregator_CPU2_LPERR           = 130,
	ESM_EVENT_ErrorAggregator_CPU3_LPERR           = 132,
	ESM_EVENT_ErrorAggregator_CPU1_INT_LPERR       = 134,
	ESM_EVENT_ErrorAggregator_CPU2_INT_LPERR       = 136,
	ESM_EVENT_ErrorAggregator_CPU3_INT_LPERR       = 138,
	ESM_EVENT_ErrorAggregator_RTDMA1_HPERR         = 139,
	ESM_EVENT_ErrorAggregator_RTDMA1_LPERR         = 140,
	ESM_EVENT_ErrorAggregator_RTDMA2_HPERR         = 141,
	ESM_EVENT_ErrorAggregator_RTDMA2_LPERR         = 142,
	ESM_EVENT_ErrorAggregator_SSU_HPERR            = 143,
	ESM_EVENT_ErrorAggregator_ECAT_MEM_HPERR       = 146,
	ESM_EVENT_ErrorAggregator_ECAT_MEM_LPERR       = 147,
	ESM_EVENT_MCANA_FEVT0                          = 162,
	ESM_EVENT_MCANA_FEVT1                          = 163,
	ESM_EVENT_MCANA_FEVT2                          = 164,
	ESM_EVENT_MCANB_FEVT0                          = 165,
	ESM_EVENT_MCANB_FEVT1                          = 166,
	ESM_EVENT_MCANB_FEVT2                          = 167,
	ESM_EVENT_MCANC_FEVT0                          = 168,
	ESM_EVENT_MCANC_FEVT1                          = 169,
	ESM_EVENT_MCANC_FEVT2                          = 170,
	ESM_EVENT_MCAND_FEVT0                          = 171,
	ESM_EVENT_MCAND_FEVT1                          = 172,
	ESM_EVENT_MCAND_FEVT2                          = 173,
	ESM_EVENT_MCANE_FEVT0                          = 174,
	ESM_EVENT_MCANE_FEVT1                          = 175,
	ESM_EVENT_MCANE_FEVT2                          = 176,
	ESM_EVENT_MCANF_FEVT0                          = 177,
	ESM_EVENT_MCANF_FEVT1                          = 178,
	ESM_EVENT_MCANF_FEVT2                          = 179,
	ESM_EVENT_WADI1_BLOCK1_SIG1ERROR_BUS_O_0       = 180,
	ESM_EVENT_WADI1_BLOCK1_SIG2ERROR_BUS_O_1       = 181,
	ESM_EVENT_WADI1_BLOCK1_SIG_TO_SIGERROR_BUS_O_2 = 182,
	ESM_EVENT_WADI1_BLOCK2_SIG1ERROR_BUS_O_0       = 183,
	ESM_EVENT_WADI1_BLOCK2_SIG2ERROR_BUS_O_1       = 184,
	ESM_EVENT_WADI1_BLOCK2_SIG_TO_SIGERROR_BUS_O_2 = 185,
	ESM_EVENT_WADI1_BLOCK3_SIG1ERROR_BUS_O_0       = 186,
	ESM_EVENT_WADI1_BLOCK3_SIG2ERROR_BUS_O_1       = 187,
	ESM_EVENT_WADI1_BLOCK3_SIG_TO_SIGERROR_BUS_O_2 = 188,
	ESM_EVENT_WADI1_BLOCK4_SIG1ERROR_BUS_O_0       = 189,
	ESM_EVENT_WADI1_BLOCK4_SIG2ERROR_BUS_O_1       = 190,
	ESM_EVENT_WADI1_BLOCK4_SIG_TO_SIGERROR_BUS_O_2 = 191,
	ESM_EVENT_WADI2_BLOCK1_SIG1ERROR_BUS_O_0       = 192,
	ESM_EVENT_WADI2_BLOCK1_SIG2ERROR_BUS_O_1       = 193,
	ESM_EVENT_WADI2_BLOCK1_SIG_TO_SIGERROR_BUS_O_2 = 194,
	ESM_EVENT_WADI2_BLOCK2_SIG1ERROR_BUS_O_0       = 195,
	ESM_EVENT_WADI2_BLOCK2_SIG2ERROR_BUS_O_1       = 196,
	ESM_EVENT_WADI2_BLOCK2_SIG_TO_SIGERROR_BUS_O_2 = 197,
	ESM_EVENT_WADI2_BLOCK3_SIG1ERROR_BUS_O_0       = 198,
	ESM_EVENT_WADI2_BLOCK3_SIG2ERROR_BUS_O_1       = 199,
	ESM_EVENT_WADI2_BLOCK3_SIG_TO_SIGERROR_BUS_O_2 = 200,
	ESM_EVENT_WADI2_BLOCK4_SIG1ERROR_BUS_O_0       = 201,
	ESM_EVENT_WADI2_BLOCK4_SIG2ERROR_BUS_O_1       = 202,
	ESM_EVENT_WADI2_BLOCK4_SIG_TO_SIGERROR_BUS_O_2 = 203,
	ESM_EVENT_EQEPERR                              = 233,
	ESM_EVENT_CPU1_OVFINT                          = 235,
	ESM_EVENT_CPU1_UVFINT                          = 236,
	ESM_EVENT_CPU1_DOVINT                          = 237,
	ESM_EVENT_CPU2_OVFINT                          = 238,
	ESM_EVENT_CPU2_UVFINT                          = 239,
	ESM_EVENT_CPU2_DOVINT                          = 240,
	ESM_EVENT_CPU3_OVFINT                          = 241,
	ESM_EVENT_CPU3_UVFINT                          = 242,
	ESM_EVENT_CPU3_DOVINT                          = 243,
	ESM_EVENT_MEMSS_REG_PAR_ERR                    = 244,
	ESM_EVENT_FRI_REG_PAR_ERR                      = 245,
	ESM_EVENT_SYSCTL_REG_PAR_ERR                   = 246,
	ESM_EVENT_LCM_CPU1SS_REG_PAR_ERR               = 247,
	ESM_EVENT_LCM_RTDMA_REG_PAR_ERR                = 248,
	ESM_EVENT_WADI_REG_PAR_ERR                     = 249,
	ESM_EVENT_CPU1_TMUROM_PAR_ERR                  = 250,
	ESM_EVENT_CPU2_TMUROM_PAR_ERR                  = 251,
	ESM_EVENT_CPU3_TMUROM_PAR_ERR                  = 252
} ESM_EventMap;


//*****************************************************************************
//
//! Values that can be returned by ESM_getLastResetSource as the reset source.
//
//*****************************************************************************
typedef enum
{
    ESM_RESET_SOURCE_POR        = 0x0U,  //! Last reset was a Power On Reset
    ESM_RESET_SOURCE_WARM_RESET = 0x1U,  //! Last reset was a Warm Reset
}ESM_ResetSource;

//*****************************************************************************
//
//! Values that can be passed to ESM_writeEOIVector() as the \e vector
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ESM_EOI_CONFIG_ERROR_INTERRUPT            = 0x0U,
    ESM_EOI_LOW_PRIORITY_ERROR_INTERRUPT      = 0x1U,
    ESM_EOI_HIGH_PRIORITY_ERROR_INTERRUPT     = 0x2U,
    ESM_EOI_HIGH_PRIORITY_WATCHDOG_INTERRUPT  = 0x4U,
    ESM_EOI_ERROR_PIN_MONITOR_INTERRUPT       = 0x5U,
}ESM_EOIVector;

//*****************************************************************************
//
//! Values that can be passed to ESM_ackInterrupt() as the \e vector
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ESM_CONFIG_ERROR_INTERRUPT            = 0x0U,
    ESM_LOW_PRIORITY_ERROR_INTERRUPT      = 0x1U,
    ESM_HIGH_PRIORITY_ERROR_INTERRUPT     = 0x2U,
    ESM_HIGH_PRIORITY_WATCHDOG_INTERRUPT  = 0x4U,
    ESM_ERROR_PIN_MONITOR_INTERRUPT       = 0x5U,
}ESM_InterruptType;

//*****************************************************************************
//
//! Values that can be passed to ESM_setOutputPinMode() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ESM_OUTPUT_LEVEL_MODE = 0x0U,  //! Level mode
    ESM_OUTPUT_PWM_MODE = 0xFU,    //! PWM mode
} ESM_OutputPinMode;

//*****************************************************************************
//
//! Values that can be passed to ESM_setErrorMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    //! ESM Normal mode of operation
    ESM_NORMAL_MODE = 0U,
    //! ESM Error force mode of operation
    ESM_ERROR_FORCE_MODE = 0xAU,
    //! Clear event (returns to Normal Mode (4’b0000) on the next cycle.)
    ESM_CLEAR_EVENT = 0x5U
} ESM_OperationMode;

//*****************************************************************************
//
//! Values that can be passed to ESM_setLevelModePolarity() as the \e polarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! The error output pin in level mode is active low (default).
    ESM_LEVEL_POLARITY_ACTIVE_LOW = 0x0U,
    //! The polarity of error output pin is active high.
    ESM_LEVEL_POLARITY_ACTIVE_HIGH = 0xFU
}ESM_LevelModePolarity;

//*****************************************************************************
//
//! Values that can be passed to ESM_setInterruptPriorityLevel() as the
//! \e priority parameter.
//
//*****************************************************************************
typedef enum
{
    //! Configure interrupt priority level to low priority
    ESM_INTERRUPT_PRIORITY_LEVEL_LOW = 0x0U,
    //! Configure interrupt priority level to high priority
    ESM_INTERRUPT_PRIORITY_LEVEL_HIGH = 0x1U
}ESM_InterruptPriorityLevel;

//*****************************************************************************
//
//! Values that can be passed to ESM_getLowPriorityInterruptStatus() and
//! ESM_getHighPriorityInterruptStatus() as the \e group parameter.
//
//*****************************************************************************
typedef enum
{
    ESM_EVENT_GROUP_1 = 0x1U,
    ESM_EVENT_GROUP_2 = 0x2U,
    ESM_EVENT_GROUP_3 = 0x4U,
    ESM_EVENT_GROUP_4 = 0x8U,
    ESM_EVENT_GROUP_5 = 0x10U,
    ESM_EVENT_GROUP_6 = 0x20U,
    ESM_EVENT_GROUP_7 = 0x40U,
    ESM_EVENT_GROUP_8 = 0x80U,
}ESM_EventGroup;

//*****************************************************************************
//
//! Values that can be pased to ESM_config().
//
//*****************************************************************************
typedef enum
{
    //! Configure low priority interrupt
    ESM_CONFIG_LOW_PRIORITY_INTERRUPT      = 0x0U,
    //! Configure NMI
    ESM_CONFIG_NMI                         = 0x1U,
    //! Configure Critical priority interrupt
    ESM_CONFIG_CRITICAL_PRIORITY_INTERRUPT = 0x2U,
    //! Configure Error Pin output
    ESM_CONFIG_ERROR_PIN                   = 0x3U
}ESM_ConfigType;

//*****************************************************************************
//
//! Values that can be passed to ESM_configErrorEvent() as the configure
//! parameter.
//
//*****************************************************************************
typedef struct
{
    //! Global event number of the error event.
    uint32_t                     event;
    //! Enable interrupt.
    bool                         enableInterrupt;
    //! Set the interrupt priority level to high or low.
    ESM_InterruptPriorityLevel   interruptPriorityLevel;
    //! Enable influence on critical priority interrupt.
    bool                         enableCriticalPriorityInterruptInfluence;
    //! Enable failure influence on ERROR pin.
    bool                         enableInfluenceOnErrorPin;
} ESM_ConfigParams;

//*****************************************************************************
//
//! Values that can be passed to ESM_configErrorPin() as the configure
//! parameter.
//
//*****************************************************************************
typedef struct
{
    //! Operation mode of Error Pin.
    ESM_OperationMode              mode;
    //! Error pin output mode.
    ESM_OutputPinMode              pinMode;
    //! Polarity of the error pin in Level mode.
    ESM_LevelModePolarity          polarity;
    //! Enable error pin monitor.
    bool                           enableErrorPinMonitor;
}ESM_ErrorPinConfigParams;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an ESM module base address.
//!
//! \param base specifies the ESM base address.
//!
//! This function determines if a ESM address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
__attribute__((always_inline))
static inline bool
ESM_isBaseValid(uint32_t base)
{
    return(
           ((base & BASE_ADDR_MASK) == ESMCPU1_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == ESMCPU2_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == ESMCPU3_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == ESMSYSTEM_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == ESMSAFETYAGG_BASE_FRAME(0U))
          );
}
#endif

//*****************************************************************************
//
//! ESM Global Soft Reset
//!
//! \param base is the base address of the ESM instance.
//!
//! This function does a Global Soft Reset to reset all enables and raw
//! status bits
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_triggerSoftReset(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Set the soft reset bits.
    //
    HWREGB(base + ESM_CPU_O_SFT_RST) = 0xFU;
}

//*****************************************************************************
//
//! Get last Reset source
//!
//! \param base is the base address of the ESM instance.
//!
//! This function returns the Source of the last Reset.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline ESM_ResetSource
ESM_getLastResetSource(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Set the soft reset bits.
    //
    return((ESM_ResetSource)((HWREG(base + ESM_CPU_O_INFO) &
                     ESM_CPU_INFO_LAST_RESET) == ESM_CPU_INFO_LAST_RESET));
}

//*****************************************************************************
//
//! Enable all interrupts (Global enable).
//!
//! \param base is the base address of the ESM module instance.
//!
//! The function enables all the interrupts.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_enableGlobal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Global enable.
    //
    HWREGB(base + ESM_CPU_O_EN) = ESM_GLOBAL_ENABLE;
}

//*****************************************************************************
//
//! Disables all the interrupts.
//!
//! \param base is the base address of the ESM instance.
//!
//! This function disables all the interrupts (Global disable)
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_disableGlobal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Disable all interrupts
    //
    HWREGB(base + ESM_CPU_O_EN) = ESM_GLOBAL_DISABLE;
}

//*****************************************************************************
//
//! Write the EOI vector to the EOI register.
//!
//! \param base is the base address of the ESM configuration registers.
//! \param vector is the corresponding vector for the interrupt.
//!             Refer ESM_EOIVector enum
//!
//! This function writes the corresponding EOI vector to the EOI register.
//! Writing the vector to this field will cause a re-evaluation of interrupts.
//! If, when the vector is written, there are still pending interrupts, a new
//! pulse will be generated.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_writeEOIVector(uint32_t base, ESM_EOIVector vector)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Write the vector to the EOI register.
    //
    HWREGH(base + ESM_CPU_O_EOI) = (uint16_t)vector;
}

//*****************************************************************************
//
//! Write the EOI vector to acknowledge the interrupt.
//!
//! \param base is the base address of the ESM configuration registers.
//! \param interruptType is the type of interrupt mapping the EOI vector.
//!             Refer ESM_InterruptType enum
//!
//! This function writes the corresponding EOI vector to the EOI register
//! based on the interrupt type passes.
//! Writing the vector to this field will cause a re-evaluation of interrupts.
//! If, when the vector is written, there are still pending interrupts, a new
//! pulse will be generated.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_ackInterrupt(uint32_t base, ESM_InterruptType interruptType)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Write the EOI vector to the EOI register based on the interrupt type.
    //
    HWREGH(base + ESM_CPU_O_EOI) = (uint16_t)interruptType;
}

//*****************************************************************************
//
//! Configure the operation mode of Error pin.
//!
//! \param mode is the Error pin mode to be configured.
//!             Refer ESM_OperationMode enum
//!
//! This function sets the mode of the Error pin of the ESM.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_setErrorMode(ESM_OperationMode mode)
{
    //
    // Configure the operation mode.
    //
    HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) =
                                (HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) &
                                ~(ESM_SYS_PIN_CTRL_KEY_M)) |
                                ((uint8_t)mode << ESM_SYS_PIN_CTRL_KEY_S);
}


//*****************************************************************************
//
//! Clears the Error pin
//!
//! The clear event mode from ESM_OperationMode enum is used.
//!
//! This function clears the Error pin. For the Error pin to de-assert,
//! 1.The Minimum Time Interval must expire
//! 2.The event that caused the Error Pin to assert must be cleared
//! 3.A CLEAR must be written to the Error Pin Control Register using this
//! function
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_clearErrorPin(void)
{
    //
    // Configure the operation mode.
    //
    HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) =
                         (HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) &
                         ~(ESM_SYS_PIN_CTRL_KEY_M)) |
                         ((uint8_t)ESM_CLEAR_EVENT << ESM_SYS_PIN_CTRL_KEY_S);
}

//*****************************************************************************
//
//! Sets the ESM error output pin mode
//!
//! \param mode indicates whether the output pin is level or PWM mode.
//!
//! This function configures the mode of the ESM error output pin. This
//! function should only be called when the ESM is disabled, from the Global
//! Enable register.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_setOutputPinMode(ESM_OutputPinMode mode)
{
    //
    // Configure the ESM error output pin mode
    //
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) =
                                (HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) &
                                ~(ESM_SYS_PIN_CTRL_PWM_EN_M)) |
                                ((uint32_t)mode << ESM_SYS_PIN_CTRL_PWM_EN_S);
}

//*****************************************************************************
//
//! Sets the polarity of the Error pin in Level mode.
//!
//! \param polarity indicates whether the polarity is active low or active high
//!
//! This function sets the Level mode polarity. When the error output pin is a
//! level, by default it is active low (drives the error pin low to indicate
//! an error). When 4’b1111 is written to this field, the polarity will be
//! active high instead.
//!
//! The polarity should only be modified when the ESM is disabled, from the
//! Global Enable register.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_setLevelModePolarity(ESM_LevelModePolarity polarity)
{
    //
    // Set the polarity of the Level mode
    //
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) =
                        (HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CTRL) &
                        ~(ESM_SYS_PIN_CTRL_POLARITY_M)) |
                        ((uint32_t)polarity << ESM_SYS_PIN_CTRL_POLARITY_S);
}

//*****************************************************************************
//
//! Get the current state of the Error pin output.
//!
//! This function returns the status of the Error Pin as looped back from the
//! I/O.
//!
//! \return Returns \b true if De-Asserted (pin is inactive, high).
//!         Returns \b false if Asserted (pin is active, low).
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
ESM_getErrorPinStatus(void)
{
    //
    // Return the status of the Error pin.
    //
    return(HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_PIN_STS) == ESM_SYS_PIN_STS_VAL);
}

//*****************************************************************************
//
//! Enables High priority Watchdog feature.
//!
//! \param base is the base address of the ESM CPU instance.
//!
//! This function enables the high priority Watchdog and its associated
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_enableHighPriorityWatchdog(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base) && (base != ESMSYSTEM_BASE));

    //
    // Enable the high priority watchdog
    //
    HWREGB(base + ESM_CPU_O_HI_PRI_WD_CFG) = ESM_WATCHDOG_ENABLE;
}

//*****************************************************************************
//
//! Disables the High priority Watchdog feature.
//!
//! \param base is the base address of the ESM CPU instance.
//!
//! This function disables the high priority Watchdog and its associated
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_disableHighPriorityWatchdog(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base) && (base != ESMSYSTEM_BASE));

    //
    // Disable the high priority watchdog
    //
    HWREGB(base + ESM_CPU_O_HI_PRI_WD_CFG) = ESM_WATCHDOG_DISABLE;
}

//*****************************************************************************
//
//! Enables High priority Watchdog's Free running mode.
//!
//! \param base is the base address of the ESM CPU instance.
//!
//! This function enables the high priority Watchdog free running mode. If it
//! is enabled, the Watchdog counter will continue to count down during debug.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_enableHighPriorityWatchdogFreerun(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base) && (base != ESMSYSTEM_BASE));

    //
    // Enable the high priority watchdog
    //
    HWREGH(base + ESM_CPU_O_HI_PRI_WD_CFG) =
                    (HWREGH(base + ESM_CPU_O_HI_PRI_WD_CFG) &
                    ~(ESM_CPU_HI_PRI_WD_CFG_EMU_FREE_M)) |
                    ((uint16_t)ESM_WATCHDOG_ENABLE <<
                    ESM_CPU_HI_PRI_WD_CFG_EMU_FREE_S);
}

//*****************************************************************************
//
//! Disables High priority Watchdog's Free running mode.
//!
//! \param base is the base address of the ESM CPU instance.
//!
//! This function disables the high priority Watchdog free running mode. The
//! watchdog counter will be frozen during debug and not resume counting down
//! until debug is suspended.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_disableHighPriorityWatchdogFreerun(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base) && (base != ESMSYSTEM_BASE));

    //
    // Enable the high priority watchdog
    //
    HWREGH(base + ESM_CPU_O_HI_PRI_WD_CFG) =
                    (HWREGH(base + ESM_CPU_O_HI_PRI_WD_CFG) &
                    ~(ESM_CPU_HI_PRI_WD_CFG_EMU_FREE_M)) |
                    ((uint16_t)ESM_WATCHDOG_DISABLE <<
                    ESM_CPU_HI_PRI_WD_CFG_EMU_FREE_S);
}

//*****************************************************************************
//
//! Enables the Error pin monitor.
//!
//! This function enables the Error Pin Monitor and its associated interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_enableErrorPinMonitor(void)
{
    //
    // Enable the Error pin monitor.
    //
    HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_ERRPIN_MON_CFG) =
                                                ESM_ERROR_PIN_MONITOR_ENABLE;
}

//*****************************************************************************
//
//! Disables the Error pin monitor.
//!
//! This function disables the Error Pin Monitor and its associated interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_disableErrorPinMonitor(void)
{
    //
    // Disable the Error pin monitor.
    //
    HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_ERRPIN_MON_CFG) =
                                            ESM_ERROR_PIN_MONITOR_DISABLE;
}

//*****************************************************************************
//
//! Set the Error pin monitor interrupt.
//!
//! This function allows software to set the Error pin monitor interrupt
//! output.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_setErrorPinMonitorInterrupt(void)
{
    //
    // Set the Error pin monitor interrupt.
    //
    HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_ERRPIN_MON_INTR_SET) =
                                            ESM_SYS_ERRPIN_MON_INTR_SET_VAL;
}

//*****************************************************************************
//
//! Clear the Error pin monitor interrupt.
//!
//! This function allows software to clear the Error pin monitor interrupt
//! output.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_clearErrorPinMonitorInterrupt(void)
{
    //
    // Clear the Error pin monitor interrupt.
    //
    HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_ERRPIN_MON_INTR_CLR) =
                                            ESM_SYS_ERRPIN_MON_INTR_CLR_VAL;
}

//*****************************************************************************
//
//! Get the Error pin monitor interrupt status.
//!
//! This function returns the status of the Error pin monitor interrupt
//!
//! \return Returns \b true if Inactive or Disabled
//!         Returns \b false if Active/Pending and Enabled
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
ESM_getErrorPinMonitorInterruptStatus(void)
{
    //
    // Get the Error pin monitor interrupt status
    //
    return(HWREGB(ESMSYSTEM_BASE + ESM_SYS_O_ERRPIN_MON_INTR_SET) != 0U);
}

//*****************************************************************************
//
//! Enable interrupt for an event
//!
//! \param base is the base address of the ESM module instance.
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//!
//! The function sets the interrupt enable bit for the specific error event.
//! If the corresponding bit and the global_enable are set, then then
//! interrupt is unmasked.
//! The enable field is only reset by a Power-On-Reset (not warm reset) or
//! global soft reset.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_enableInterrupt(uint32_t base, ESM_EventMap event)
{
    //
    // Check the arguments.
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
    HWREG(base + ESM_CPU_O_INTR_EN_SET(groupNum)) = 1U << eventNum;
}

//*****************************************************************************
//
//! Disable interrupt for an event
//!
//! \param base is the base address of the ESM module instance.
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//!
//! The function clears the interrupt enable bit for the specific error event.
//! (The interrupt is disabled.)
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_disableInterrupt(uint32_t base, ESM_EventMap event)
{
    //
    // Check the arguments.
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
    HWREG(base + ESM_CPU_O_INTR_EN_CLR(groupNum)) = 1U << eventNum;
}

//*****************************************************************************
//
//! Sets the Interrupt priority level.
//!
//! \param base is the base address of the ESM instance.
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//! \param priority indicates the priority level of the interrupt.
//!                 Refer enum ESM_InterruptPriorityLevel
//!
//! This function sets which interrupt (low or high prirority) should be
//! influenced for the events in group N.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_setInterruptPriorityLevel(uint32_t base, ESM_EventMap event,
                            ESM_InterruptPriorityLevel priority)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base) && (base != ESMSYSTEM_BASE));

    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = (uint32_t)event / 32U;
    uint32_t eventNum = (uint32_t)event % 32U;

    //
    // Set the interrupt priority level for the event
    //
    if(priority == ESM_INTERRUPT_PRIORITY_LEVEL_HIGH)
    {
        HWREG(base + ESM_CPU_O_INT_PRIO(groupNum)) |= 1U << eventNum;
    }
    else
    {
        HWREG(base + ESM_CPU_O_INT_PRIO(groupNum)) &= ~(1U << eventNum);
    }
}

//*****************************************************************************
//
//! Set the interrupt raw status of an event.
//!
//! \param base is the base address of the ESM instance.
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//!
//! This function sets the interrupt raw status for the corresponding error
//! event.
//!
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_setRawInterruptStatus(uint32_t base, ESM_EventMap event)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = (uint32_t)event / 32U;
    uint32_t eventNum = (uint32_t)event % 32U;

    //
    // Get the interrupt status of the corresponding event.
    //
    HWREG(base + ESM_CPU_O_RAW(groupNum)) = 1U << eventNum;
}

//*****************************************************************************
//
//! Get the interrupt raw status of an event.
//!
//! \param base is the base address of the ESM instance.
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//!
//! This function returns the raw status of the interrupt for the corresponding
//! error event.
//!
//! \return Returns \b false if Inactive
//!         Returns \b true if Active/Pending
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
ESM_getRawInterruptStatus(uint32_t base, ESM_EventMap event)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = (uint32_t)event / 32U;
    uint32_t eventNum = (uint32_t)event % 32U;

    //
    // Get the interrupt status of the corresponding event.
    //
    return(((HWREG(base + ESM_CPU_O_RAW(groupNum)) >> eventNum) & 1U) != 0U);
}

//*****************************************************************************
//
//! Get the interrupt status for an event.
//!
//! \param base is the base address of the ESM instance.
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//!
//! This function returns the status of the interrupt for the corresponding
//! error event.
//!
//! \return Returns \b false if Inactive or Disabled
//!         Returns \b true if Active/Pending and Enabled
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
ESM_getInterruptStatus(uint32_t base, ESM_EventMap event)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = (uint32_t)event / 32U;
    uint32_t eventNum = (uint32_t)event % 32U;

    //
    // Get the interrupt status of the corresponding event.
    //
    return(((HWREG(base + ESM_CPU_O_STS(groupNum)) >> eventNum) & 1U) != 0U);
}

//*****************************************************************************
//
//! Clear the interrupt raw status of an event.
//!
//! \param base is the base address of the ESM instance.
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//!
//! This function clears the interrupt raw status for the corresponding error
//! event.
//!
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_clearRawInterruptStatus(uint32_t base, ESM_EventMap event)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = (uint32_t)event / 32U;
    uint32_t eventNum = (uint32_t)event % 32U;

    //
    // Get the interrupt status of the corresponding event.
    //
    HWREG(base + ESM_CPU_O_STS(groupNum)) = 1U << eventNum;
}

//*****************************************************************************
//
//! Sets Critical priority interrupt influence for an event
//!
//! \param base is the base address of the ESM module instance.
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//! \param influence indicates if the event influences the critical priority
//! interrupt or not
//!
//! The function sets/clears the critical priority interrupt influence enable
//! bit for the specific error event. Corresponding event, when set, will
//! count as a pending event towards generating a critical priority interrupt.
//! It can only be reset by a Power-On-Reset (not warm reset) or global soft
//! reset. When cleared, the corresponding event will no longer count as a
//! pending event towards generating a critical priority interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_setCriticalPriorityInterruptInfluence(uint32_t base,
                                        ESM_EventMap event, bool influence)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = (uint32_t)event / 32U;
    uint32_t eventNum = (uint32_t)event % 32U;

    //
    // Set/clear the Critical Priority Interrupt Influence enable
    //
    if(influence == true)
    {
        HWREG(base + ESM_CPU_O_CRIT_EN_SET(groupNum)) = 1U << eventNum;
    }
    else
    {
        HWREG(base + ESM_CPU_O_CRIT_EN_CLR(groupNum)) = 1U << eventNum;
    }
}

//*****************************************************************************
//
//! Get Critical priority interrupt output status
//!
//! \param base is the base address of the ESM module instance.
//!
//! The function returns the status of the critical priority interrupt output.
//! The status is only reset via POR and the Global Soft Reset MMR.
//!
//! \return Returns \b true if the Critical Priority Interrupt output has
//! triggered, returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
ESM_getCriticalPriorityInterruptStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    return((HWREG(base + ESM_CPU_O_INFO) & ESM_CPU_INFO_CRIT_INTR) ==
                                                     ESM_CPU_INFO_CRIT_INTR);
}

//*****************************************************************************
//
//! Sets the influence of an event on the Error pin
//!
//! \param event is the error event.
//!      Refer ESM_EventMap for the list of error inputs to the ESM subsystem.
//! \param influence indicates if the event influences the error pin or not
//!
//! This function sets if the error event in group N can influence the Error
//! pin. Corresponding event, when set, will count as a pending error event
//! for the ESM state machine. If influence is cleared, the corresponding
//! events will no longer count as pending error events.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_setInfluenceOnErrorPin(ESM_EventMap event, bool influence)
{
    //
    // Calculate the group number & event number from the global event number.
    //
    uint32_t groupNum = (uint32_t)event / 32U;
    uint32_t eventNum = (uint32_t)event % 32U;

    if(influence == true)
    {
        HWREG(ESMSYSTEM_BASE + ESM_CPU_O_PIN_EN_SET(groupNum)) =
                                                            1U << eventNum;
    }
    else
    {
        HWREG(ESMSYSTEM_BASE + ESM_CPU_O_PIN_EN_CLR(groupNum)) =
                                                            1U << eventNum;
    }
}

//*****************************************************************************
//
//! Get the low priority interrupt status for an Event group.
//!
//! \param base is the base address of the ESM instance.
//! \param group is the event group.
//!     Refer ESM_EventGroup for the list of event groups in the ESM subsystem.
//!
//! This function returns the status of the low priority interrupt for the
//! corresponding error group.
//!
//! \return Returns \b true if the event Groups have one or more Low Priority
//! interrupts pending, returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
ESM_getLowPriorityInterruptStatus(uint32_t base, ESM_EventGroup group)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    return((HWREGH(base + ESM_CPU_O_LOW) & (uint16_t)group) ==
                                                            (uint16_t)group);
}

//*****************************************************************************
//
//! Get the high priority interrupt status for an Event group.
//!
//! \param base is the base address of the ESM instance.
//! \param group is the event group.
//!     Refer ESM_EventGroup for the list of event groups in the ESM subsystem.
//!
//! This function returns the status of the high priority interrupt for the
//! corresponding error group.
//!
//! \return Returns \b true if the event Groups have one or more High Priority
//! interrupts pending, returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
ESM_getHighPriorityInterruptStatus(uint32_t base, ESM_EventGroup group)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base) && (base != ESMSYSTEM_BASE));

    return((HWREGH(base + ESM_CPU_O_HI) & (uint16_t)group) == (uint16_t)group);
}

//*****************************************************************************
//
//! Get the highest priority outstanding low priority interrupt.
//!
//! \param base is the base address of the ESM instance.
//!
//! This function returns the global event number of the highest priority
//! outstanding low priority interrupt that is pending. The lowest event
//! number has the highest priority. A value of 0xFFFF indicates that there
//! are no low priority interrupts pending.
//!
//! \return Returns the global event number of the highest priority outstanding
//! low priority interrupt.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
ESM_getHighestLowPriorityInterrupt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    return((HWREG(base + ESM_CPU_O_LOW_PRI) & (ESM_CPU_LOW_PRI_PLS_M)) >>
                                                    ESM_CPU_LOW_PRI_PLS_S);
}

//*****************************************************************************
//
//! Get the highest priority outstanding high priority interrupt.
//!
//! \param base is the base address of the ESM instance.
//!
//! This function returns the global event number of the highest priority
//! outstanding high priority interrupt that is pending. The lowest event
//! number has the highest priority. A value of 0xFFFF indicates that there
//! are no high priority interrupts pending.
//!
//! \return Returns the global event number of the highest priority outstanding
//! high priority interrupt.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
ESM_getHighestHighPriorityInterrupt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base) && (base != ESMSYSTEM_BASE));

    return((HWREG(base + ESM_CPU_O_HI_PRI) & (ESM_CPU_HI_PRI_PLS_M)) >>
                                                    ESM_CPU_HI_PRI_PLS_S);
}

//*****************************************************************************
//
//! Get the Error pin counter value
//!
//! This function gets the current value of the Time Interval Counter. This
//! register is reloaded to the counter_preload value on entry to the ESM_ERROR
//! state from ESM_IDLE and counts down by one per clock cycle.  Once the
//! counter has reached 0, the Minimum Time Interval has expired.
//!
//! \return Returns the current Error pin counter value.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
ESM_getErrorPinCounterValue(void)
{
    return(HWREG(ESMSYSTEM_BASE + ESM_SYS_O_PIN_CNTR));
}

//*****************************************************************************
//
//! Lock the Error Group N Interrupt configuration Registers.
//!
//! \param base is the base address of the ESM instance.
//! \param groups Error groups whose configuration for the associated
//! Interrupt Enable Set/Clear Registers and Interrupt Priority Register are
//! to be locked. This parameter can be an OR of the groups in ESM_EventGroup
//! enum.
//!
//! This function locks the associated enable and priority bits for each Group
//! for Low and High Priority Interrupts.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_lockErrorGroupInterruptConfig(uint32_t base, uint32_t groups)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Set the lock bit for the specified groups.
    //
    HWREG(base + ESM_CPU_O_GROUP_N_LOCK) |= groups;
}

//*****************************************************************************
//
//! Unlock the Error Group N Interrupt configuration Registers.
//!
//! \param base is the base address of the ESM instance.
//! \param groups Error groups whose configuration for the associated
//! Interrupt Enable Set/Clear Registers and Interrupt Priority Register are to
//! be unlocked.
//!
//! This function unlocks the associated enable and priority bits for each
//! Group for Low and High Priority Interrupts.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_unlockErrorGroupInterruptConfig(uint32_t base, uint32_t groups)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Clear the lock bit for the specified groups to unlock.
    //
    HWREG(base + ESM_CPU_O_GROUP_N_LOCK) &= ~groups;
}

//*****************************************************************************
//
//! Commit the Error Group N Interrupt configuration Registers.
//!
//! \param base is the base address of the ESM instance.
//! \param groups Error groups whose lock on configuration for the associated
//! Interrupt Enable Set/Clear Registers and Interrupt Priority Register are to
//! be committed.
//!
//! This function locks the associated enable and priority bits for each Group
//! for Low and High Priority Interrupts.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_commitErrorGroupInterruptConfig(uint32_t base, uint32_t groups)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    //
    // Set the commit bit for the specified groups.
    //
    HWREG(base + ESM_CPU_O_GROUP_N_COMMIT) |= groups;
}

//*****************************************************************************
//
//! Lock Error Pin Influence registers
//!
//! \param groups Error groups whose Error Pin Influence Set and Clear
//! Registers are to be locked.
//!
//! This function locks the Error Pin Influence configuration for the
//! associated Error Groups.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_lockErrorPinInfluenceConfig(uint32_t groups)
{
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_ERR_PIN_INFLUENCE_LOCK) |= groups;
}

//*****************************************************************************
//
//! Unlock the Error Pin Influence registers
//!
//! \param groups Error groups whose Error Pin Influence Set and Clear
//! Registers are to be unlocked.
//!
//! This function unlocks the Error Pin Influence configuration for the
//! associated Error Groups, if the corresponding Commit bit is not set.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_unlockErrorPinInfluenceConfig(uint32_t groups)
{
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_ERR_PIN_INFLUENCE_LOCK) &= ~groups;
}

//*****************************************************************************
//
//! Commit the Error Pin Influence registers
//!
//! \param groups Error groups whose lock on Error Pin Influence Set and Clear
//! Registers are to be committed.
//!
//! This function commits the lock configuration for the Error Pin Influence
//! configuration for the associated Error Groups.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_commitErrorPinInfluenceConfig(uint32_t groups)
{
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_ERR_PIN_INFLUENCE_COMMIT) |= groups;
}

//*****************************************************************************
//
//! Lock the Critical Priority Interrupt Influence configuration.
//!
//! \param groups Error groups whose Error Pin Influence Set and Clear
//! Registers are to be locked.
//!
//! This function locks the Critical Priority Interrupt Influence configuration
//! for the associated Error Groups. Each bit lock[N] bit will lock the
//! associated masking MMRs associated with Group N.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_lockCriticalPriorityInterruptInfluenceConfig(uint32_t base,
                                                 uint32_t groups)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    HWREG(base + ESM_CPU_O_CRI_PRI_INFLUENCE_LOCK) |= groups;
}

//*****************************************************************************
//
//! Unlock the Critical Priority Interrupt Influence configuration.
//!
//! \param groups Error groups whose Error Pin Influence Set and Clear
//! Registers are to be unlocked.
//!
//! This function unlocks the Critical Priority Interrupt Influence
//! configuration for the associated Error Groups, if the corresponding Commit
//! bit is not set.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_unlockCriticalPriorityInterruptInfluenceConfig(uint32_t base,
                                                   uint32_t groups)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    HWREG(base + ESM_CPU_O_CRI_PRI_INFLUENCE_LOCK) &= ~groups;
}

//*****************************************************************************
//
//! Commit the Critical Priority Interrupt Influence configuration.
//!
//! \param groups Error groups whose lock on Error Pin Influence Set and Clear
//! Registers are to be committed.
//!
//! This function commits the lock configuration for the Critical Priority
//! Interrupt Influence configuration for the associated Error Groups. Each
//! bit commit[N] bit will commit the lock configuration for the corresponding
//! bit in the Critical Priority Interrupt Influence Lock Register.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_commitCriticalPriorityInterruptInfluenceConfig(uint32_t base,
                                                   uint32_t groups)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    HWREG(base + ESM_CPU_O_CRI_PRI_INFLUENCE_COMMIT) |= groups;
}

//*****************************************************************************
//
//! Lock MMR registers
//!
//! \param registers Registers to be locked. Can be OR of the following -
//!                     - ESM_GLOBAL_EN_REG
//!                     - ESM_GLOBAL_SOFT_RESET_REG
//!                     - ESM_ERROR_PIN_REG
//!                     - ESM_ERROR_PIN_MONITOR_REG
//!                     - ESM_HIGH_PRIORITY_WATCHDOG_REG
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_lockMMRConfig(uint32_t base, uint32_t registers)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    HWREG(base + ESM_CPU_O_MMR_CONFIG_LOCK) |= registers;
}

//*****************************************************************************
//
//! Unlock the Configuration MMR registers
//!
//! \param registers Registers to be unlocked. Can be OR of the following -
//!                     - ESM_GLOBAL_EN_REG
//!                     - ESM_GLOBAL_SOFT_RESET_REG
//!                     - ESM_ERROR_PIN_REG
//!                     - ESM_ERROR_PIN_MONITOR_REG
//!                     - ESM_HIGH_PRIORITY_WATCHDOG_REG
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_unlockMMRConfig(uint32_t base, uint32_t registers)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    HWREG(base + ESM_CPU_O_MMR_CONFIG_LOCK) &= ~registers;
}

//*****************************************************************************
//
//! Commit the configuration MMR registers
//!
//! \param registers Register locks to be committed. Can be OR of the following
//!                     - ESM_GLOBAL_EN_REG
//!                     - ESM_GLOBAL_SOFT_RESET_REG
//!                     - ESM_ERROR_PIN_REG
//!                     - ESM_ERROR_PIN_MONITOR_REG
//!                     - ESM_HIGH_PRIORITY_WATCHDOG_REG
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_commitMMRConfig(uint32_t base, uint32_t registers)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    HWREG(base + ESM_CPU_O_MMR_CONFIG_COMMIT) |= registers;
}

//*****************************************************************************
//
//! Get the ESM group interrupt status
//!
//! \param group The group id for which the interrupt status is returned
//!
//! \return Group interrupt status
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
ESM_getGroupRawIntStatus(uint32_t base, uint32_t group)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    return (HWREG(base + ESM_CPU_O_RAW(group)));
}

//*****************************************************************************
//
//! Clear the group interrupt status
//!
//! \param group Group for which the interrupt status is cleared
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
ESM_clearGroupIntStatus(uint32_t base, uint32_t group)
{
    //
    // Check the arguments.
    //
    ASSERT(ESM_isBaseValid(base));

    HWREG(base + ESM_CPU_O_STS(group)) = 0xFFFFFFFFU;
}

//*****************************************************************************
//
//! Configure the ESM action for a error event
//!
//! \param base is the base address of the ESM instance.
//! \param event is the ESM Error event which is configured.
//! \param configType is the configuration - low priority interrupt, NMI,
//! Critical priority interrupt or Error pin output.
//!
//! This function configures the settings for the specific error event
//! according to the configType specified.
//!
//! \return None.
//
//*****************************************************************************
extern void
ESM_config(uint32_t base, ESM_EventMap event, ESM_ConfigType configType);

//*****************************************************************************
//
//! Configure the ESM error event
//!
//! \param base is the base address of the ESM instance.
//! \param configparams is the configuration parameters used to configure the
//! error event.
//!
//! This function configures the settings for the specific error event. It sets
//! the priority level and configures the influence on the critical priority
//! event and error pin.
//!
//! \return None.
//
//*****************************************************************************
extern void
ESM_configErrorEvent(uint32_t base, const ESM_ConfigParams *configParams);

//*****************************************************************************
//
//! Set the High Priority Watchdog counter pre-load value
//!
//! \param base is the base address of the ESM instance.
//! \param value is the preload value for the watchdog counter.
//!
//! This function sets the pre-load register with the watchdog counter value.
//! This is the value that will be loaded in to the counter field of the High
//! Priority Watchdog Counter Register.
//!
//! \return None.
//
//*****************************************************************************
extern void
ESM_setWatchdogCounterPreload(uint32_t base, uint32_t value);

//*****************************************************************************
//
//! Set the Error pin counter pre-load value
//!
//! \param value is the preload value for the Error pin counter.
//!
//! This function sets the pre-load register with the Error pin counter. This
//! is the value that will be loaded in to the counter field of the Pin
//! Counter Value Register.
//!
//! \return None.
//
//*****************************************************************************
extern void
ESM_setErrorPinCounterPreload(uint32_t value);

//*****************************************************************************
//
//! Set the PWM high and low counter preload value.
//!
//! \param highValue is the PWM high counter preload value.
//! \param lowValue is the PWM low counter preload value.
//!
//! This functions sets the counter preload value. This value will be loaded
//! in to the counter field of the Error Pin PWM High Counter Value Register
//! and Low counter value register respectively, whenever the error output
//! pin toggles high.
//!
//! \return None.
//
//*****************************************************************************
extern void
ESM_setPWMCounterPreload(uint32_t highValue, uint32_t lowValue);

//*****************************************************************************
//
//! Configure the ESM Error Pin
//!
//! \param configparams is the configuration parameters used to configure the
//! error pin.
//!
//! This function configures the settings for the output Error pin.
//!
//! \return None.
//
//*****************************************************************************
extern void
ESM_configErrorPin(const ESM_ErrorPinConfigParams *configParams);



//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // ESM_H