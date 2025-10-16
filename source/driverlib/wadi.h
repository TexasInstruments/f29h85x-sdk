//#############################################################################
//
// FILE:   wadi.h
//
// TITLE:   C29x WADI driver
//
//#############################################################################
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

//#############################################################################

#ifndef WADI_H
#define WADI_H

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
//! \addtogroup wadi_api WADI
//! \brief This module is used for WADI configurations
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_wadi.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
//! Debug options in WADI
//
//*****************************************************************************
#define WADI_DEBUG_SIGNAL1              0x0U        // Signal 1 debug
#define WADI_DEBUG_SIGNAL2              0x1U        // Signal 2 debug
#define WADI_DEBUG_SIGNAL_TO_SIGNAL     0x2U        // Signal to signal debug

//*****************************************************************************
//
//! Signals to a WADI block.
//
//*****************************************************************************
typedef enum
{
    WADI_SIGNAL1 = 0,                       // Signal 1
    WADI_SIGNAL2 = 1                        // Signal 2
} WADI_Signal;

//*****************************************************************************
//
//! Values that can be passed to the WADI_configSignalAndTrigger as the
//! \e signal1 and \e signal2 parameter.
//
//*****************************************************************************
typedef enum
{
    WADI_INPUT_SIGNAL_PWMXBAR1,
    WADI_INPUT_SIGNAL_PWMXBAR2,
    WADI_INPUT_SIGNAL_PWMXBAR3,
    WADI_INPUT_SIGNAL_PWMXBAR4,
    WADI_INPUT_SIGNAL_PWMXBAR5,
    WADI_INPUT_SIGNAL_PWMXBAR6,
    WADI_INPUT_SIGNAL_PWMXBAR7,
    WADI_INPUT_SIGNAL_PWMXBAR8,
    WADI_INPUT_SIGNAL_PWMXBAR9,
    WADI_INPUT_SIGNAL_PWMXBAR10,
    WADI_INPUT_SIGNAL_PWMXBAR11,
    WADI_INPUT_SIGNAL_PWMXBAR12,
    WADI_INPUT_SIGNAL_PWMXBAR13,
    WADI_INPUT_SIGNAL_PWMXBAR14,
    WADI_INPUT_SIGNAL_PWMXBAR15,
    WADI_INPUT_SIGNAL_PWMXBAR16,
    WADI_INPUT_SIGNAL_INPUTXBAR33,
    WADI_INPUT_SIGNAL_INPUTXBAR34,
    WADI_INPUT_SIGNAL_INPUTXBAR35,
    WADI_INPUT_SIGNAL_INPUTXBAR36,
    WADI_INPUT_SIGNAL_INPUTXBAR37,
    WADI_INPUT_SIGNAL_INPUTXBAR38,
    WADI_INPUT_SIGNAL_INPUTXBAR39,
    WADI_INPUT_SIGNAL_INPUTXBAR40,
    WADI_INPUT_SIGNAL_INPUTXBAR41,
    WADI_INPUT_SIGNAL_INPUTXBAR42,
    WADI_INPUT_SIGNAL_INPUTXBAR43,
    WADI_INPUT_SIGNAL_INPUTXBAR44,
    WADI_INPUT_SIGNAL_INPUTXBAR45,
    WADI_INPUT_SIGNAL_INPUTXBAR46,
    WADI_INPUT_SIGNAL_INPUTXBAR47,
    WADI_INPUT_SIGNAL_INPUTXBAR48,
    WADI_INPUT_SIGNAL_INPUTXBAR49 = WADI_INPUT_SIGNAL_INPUTXBAR33,
    WADI_INPUT_SIGNAL_INPUTXBAR50,
    WADI_INPUT_SIGNAL_INPUTXBAR51,
    WADI_INPUT_SIGNAL_INPUTXBAR52,
    WADI_INPUT_SIGNAL_INPUTXBAR53,
    WADI_INPUT_SIGNAL_INPUTXBAR54,
    WADI_INPUT_SIGNAL_INPUTXBAR55,
    WADI_INPUT_SIGNAL_INPUTXBAR56,
    WADI_INPUT_SIGNAL_INPUTXBAR57,
    WADI_INPUT_SIGNAL_INPUTXBAR58,
    WADI_INPUT_SIGNAL_INPUTXBAR59,
    WADI_INPUT_SIGNAL_INPUTXBAR60,
    WADI_INPUT_SIGNAL_INPUTXBAR61,
    WADI_INPUT_SIGNAL_INPUTXBAR62,
    WADI_INPUT_SIGNAL_INPUTXBAR63,
    WADI_INPUT_SIGNAL_INPUTXBAR64,
} WADI_InputSignal;

//*****************************************************************************
//
//! Values that can be passed to the WADI_configSignalAndTrigger as the
//! \e trigger1 parameter.
//
//*****************************************************************************
typedef enum
{
    WADI_WADI1_TRIGGER1_PWMXBAR9 = 0x10U,
    WADI_WADI1_TRIGGER1_PWMXBAR10 = 0x11U,
    WADI_WADI1_TRIGGER1_PWMXBAR11 = 0x12U,
    WADI_WADI1_TRIGGER1_PWMXBAR12 = 0x13U,
    WADI_WADI1_TRIGGER1_PWMXBAR13 = 0x14U,
    WADI_WADI1_TRIGGER1_PWMXBAR14 = 0x15U,
    WADI_WADI1_TRIGGER1_PWMXBAR15 = 0x16U,
    WADI_WADI1_TRIGGER1_PWMXBAR16 = 0x17U,
    WADI_WADI1_TRIGGER1_INPUTXBAR41 = 0x18U,
    WADI_WADI1_TRIGGER1_INPUTXBAR42 = 0x19U,
    WADI_WADI1_TRIGGER1_INPUTXBAR43 = 0x1AU,
    WADI_WADI1_TRIGGER1_INPUTXBAR44 = 0x1BU,
    WADI_WADI1_TRIGGER1_INPUTXBAR45 = 0x1CU,
    WADI_WADI1_TRIGGER1_INPUTXBAR46 = 0x1DU,
    WADI_WADI1_TRIGGER1_INPUTXBAR47 = 0x1EU,
    WADI_WADI1_TRIGGER1_INPUTXBAR48 = 0x1FU,
    WADI_WADI2_TRIGGER1_PWMXBAR9 = 0x20U,
    WADI_WADI2_TRIGGER1_PWMXBAR10 = 0x21U,
    WADI_WADI2_TRIGGER1_PWMXBAR11 = 0x22U,
    WADI_WADI2_TRIGGER1_PWMXBAR12 = 0x23U,
    WADI_WADI2_TRIGGER1_PWMXBAR13 = 0x24U,
    WADI_WADI2_TRIGGER1_PWMXBAR14 = 0x25U,
    WADI_WADI2_TRIGGER1_PWMXBAR15 = 0x26U,
    WADI_WADI2_TRIGGER1_PWMXBAR16 = 0x27U,
    WADI_WADI2_TRIGGER1_INPUTXBAR57 = 0x28U,
    WADI_WADI2_TRIGGER1_INPUTXBAR58 = 0x29U,
    WADI_WADI2_TRIGGER1_INPUTXBAR59 = 0x2AU,
    WADI_WADI2_TRIGGER1_INPUTXBAR60 = 0x2BU,
    WADI_WADI2_TRIGGER1_INPUTXBAR61 = 0x2CU,
    WADI_WADI2_TRIGGER1_INPUTXBAR62 = 0x2DU,
    WADI_WADI2_TRIGGER1_INPUTXBAR63 = 0x2EU,
    WADI_WADI2_TRIGGER1_INPUTXBAR64 = 0x2FU,
}WADI_Trigger1;

//*****************************************************************************
//
//! Values that can be passed to the WADI_configSignalAndTrigger as the
//! \e trigger2 parameter.
//
//*****************************************************************************
typedef enum
{
    WADI_WADI1_TRIGGER2_PWMXBAR1 = 0x10U,
    WADI_WADI1_TRIGGER2_PWMXBAR2 = 0x11U,
    WADI_WADI1_TRIGGER2_PWMXBAR3 = 0x12U,
    WADI_WADI1_TRIGGER2_PWMXBAR4 = 0x13U,
    WADI_WADI1_TRIGGER2_PWMXBAR5 = 0x14U,
    WADI_WADI1_TRIGGER2_PWMXBAR6 = 0x15U,
    WADI_WADI1_TRIGGER2_PWMXBAR7 = 0x16U,
    WADI_WADI1_TRIGGER2_PWMXBAR8 = 0x17U,
    WADI_WADI1_TRIGGER2_INPUTXBAR33 = 0x18U,
    WADI_WADI1_TRIGGER2_INPUTXBAR34 = 0x19U,
    WADI_WADI1_TRIGGER2_INPUTXBAR35 = 0x1AU,
    WADI_WADI1_TRIGGER2_INPUTXBAR36 = 0x1BU,
    WADI_WADI1_TRIGGER2_INPUTXBAR37 = 0x1CU,
    WADI_WADI1_TRIGGER2_INPUTXBAR38 = 0x1DU,
    WADI_WADI1_TRIGGER2_INPUTXBAR39 = 0x1EU,
    WADI_WADI1_TRIGGER2_INPUTXBAR40 = 0x1FU,
    WADI_WADI2_TRIGGER2_PWMXBAR1 = 0x20U,
    WADI_WADI2_TRIGGER2_PWMXBAR2 = 0x21U,
    WADI_WADI2_TRIGGER2_PWMXBAR3 = 0x22U,
    WADI_WADI2_TRIGGER2_PWMXBAR4 = 0x23U,
    WADI_WADI2_TRIGGER2_PWMXBAR5 = 0x24U,
    WADI_WADI2_TRIGGER2_PWMXBAR6 = 0x25U,
    WADI_WADI2_TRIGGER2_PWMXBAR7 = 0x26U,
    WADI_WADI2_TRIGGER2_PWMXBAR8 = 0x27U,
    WADI_WADI2_TRIGGER2_INPUTXBAR49 = 0x28U,
    WADI_WADI2_TRIGGER2_INPUTXBAR50 = 0x29U,
    WADI_WADI2_TRIGGER2_INPUTXBAR51 = 0x2AU,
    WADI_WADI2_TRIGGER2_INPUTXBAR52 = 0x2BU,
    WADI_WADI2_TRIGGER2_INPUTXBAR53 = 0x2CU,
    WADI_WADI2_TRIGGER2_INPUTXBAR54 = 0x2DU,
    WADI_WADI2_TRIGGER2_INPUTXBAR55 = 0x2EU,
    WADI_WADI2_TRIGGER2_INPUTXBAR56 = 0x2FU,
}WADI_Trigger2;

//*****************************************************************************
//
//! Trigger Modes for a signal
//
//*****************************************************************************
typedef enum
{
    //! No Trigger
    WADI_TRIGGER_MODE_NO_TRIGGER            = 0x0U,
    //! Hardware trigger
    WADI_TRIGGER_MODE_HARDWARE_TRIGGER      = 0x1U,
    //! Software trigger
    WADI_TRIGGER_MODE_SOFTWARE_TRIGGER      = 0x2U,
    //! Either of hardware or software trigger
    WADI_TRIGGER_MODE_EITHER_TRIGGER        = 0x3U,
    //! Synchronized trigger
    WADI_TRIGGER_MODE_SYNCHRONIZED_TRIGGER  = 0x4U
} WADI_TriggerMode;

//*****************************************************************************
//
//! Polarity of the signals
//
//*****************************************************************************
typedef enum
{
    //! Rising edge to be considered
    WADI_SIGNAL_POLARITY_RISING_EDGE = 1U,
    //! Falling edge to be considered
    WADI_SIGNAL_POLARITY_FALLING_EDGE = 2U,
    //! Either rising edge or falling edge to be considered
    WADI_SIGNAL_POLARITY_EITHER_EDGE = 3U
} WADI_SignalPolarity;

//*****************************************************************************
//
//! Permissible aggregation modes for measurement
//
//*****************************************************************************
typedef enum
{
    //! Aggregation Mode
    WADI_AGGR_MODE_AGGREGATION              = 0U,
    //! Aggregation and peak mode
    WADI_AGGR_MODE_AGGREGATION_PEAK         = 1U,
    //! Aggregation and average mode
    WADI_AGGR_MODE_AGGREGATION_AVERAGE      = 2U,
    //! Aggregation and Peak and Average mode
    WADI_AGGR_MODE_AGGREGATION_PEAK_AVERAGE = 3U
} WADI_AggregationMode;

//*****************************************************************************
//
//! Permissible aggregation sizes for measurement
//
//*****************************************************************************
typedef enum
{
    //! Aggregation is disabled, each measurements are independently compared.
    WADI_AGGREGATION_SIZE0 = 0x0U,
    //! Aggregation of 2 measurements
    WADI_AGGREGATION_SIZE2 = 0x1U,
    //! Aggregation of 4 measurements
    WADI_AGGREGATION_SIZE4 = 0x2U,
    //! Aggregation of 8 measurements
    WADI_AGGREGATION_SIZE8 = 0x3U,
    //! Aggregation of 16 measurements
    WADI_AGGREGATION_SIZE16 = 0x4U,
    //! Aggregation of 32 measurements
    WADI_AGGREGATION_SIZE32 = 0x5U,
    //! Aggregation of 64 measurements
    WADI_AGGREGATION_SIZE64 = 0x6U
} WADI_NumberOfAggregation;

//*****************************************************************************
//
//! Permissible edgespan values for measurement
//
//*****************************************************************************
typedef enum
{
    //! No measurement
    WADI_EDGESPAN0 = 0x0U,
    //! Smallest pulse on signal
    WADI_EDGESPAN1 = 0x1U,
    //! Smallest period on signal
    WADI_EDGESPAN2 = 0x2U,
    //! Period to 3rd edge from start edge after trigger condition
    WADI_EDGESPAN3 = 0x3U,
    //! Period to 4th edge from start edge after trigger condition
    WADI_EDGESPAN4 = 0x4U,
    //! Period to 5th edge from start edge after trigger condition
    WADI_EDGESPAN5 = 0x5U,
    //! Period to 6th edge from start edge after trigger condition
    WADI_EDGESPAN6 = 0x6U,
    //! Period to 7th edge from start edge after trigger condition
    WADI_EDGESPAN7 = 0x7U,
    //! Period to 8th edge from start edge after trigger condition
    WADI_EDGESPAN8 = 0x8U,
    //! Period to 9th edge from start edge after trigger condition
    WADI_EDGESPAN9 = 0x9U,
    //! Period to 10th edge from start edge after trigger condition
    WADI_EDGESPAN10 = 0xAU,
    //! Period to 11th edge from start edge after trigger condition
    WADI_EDGESPAN11 = 0xBU,
    //! Period to 12th edge from start edge after trigger condition
    WADI_EDGESPAN12 = 0xCU,
    //! Period to 13th edge from start edge after trigger condition
    WADI_EDGESPAN13 = 0xDU,
    //! Period to 14th edge from start edge after trigger condition
    WADI_EDGESPAN14 = 0xEU,
    //! Period to 15th edge from start edge after trigger condition
    WADI_EDGESPAN15 = 0xFU
} WADI_EdgeSpan;

//*****************************************************************************
//
//! Possible values for moving count in case of Moving Window Frequency Mode
//
//*****************************************************************************
typedef enum
{
    //! Only one snapshot for window count. No moving window measurements.
    WADI_MOVING_COUNT0 = 0U,
    //! Two snapshots in one window.
    WADI_MOVING_COUNT1 = 1U,
    //! Three snapshots in one window.
    WADI_MOVING_COUNT2 = 2U,
    //! Four snapshots in one window.
    WADI_MOVING_COUNT3 = 3U
} WADI_MovingCount;

//*****************************************************************************
//
//! Frequency Compare Modes
//
//*****************************************************************************
typedef enum
{
    //! Frequency compare in fixed window mode
    WADI_COMPARE_FREQ_MODE_FIXED_WINDOW = 0U,
    //! Frequency compare in moving window mode
    WADI_COMPARE_FREQ_MODE_MOVING_WINDOW = 1U
} WADI_CompareFreqMode;

//*****************************************************************************
//
//! Deadband and Phase Overlap compare types
//
//*****************************************************************************
typedef enum
{
    //! Configured edge compare
    WADI_COMPARE_CONFIGURED = 0U,
    //! Configured as well as complementary edge compare
    WADI_COMPARE_CONFIGURED_AND_COMPLEMENTARY = 1U
} WADI_CompareType;

//*****************************************************************************
//
//! Different interrupt sources
//
//*****************************************************************************
typedef enum
{
    //! Block 1 is the interrupt source
    WADI_INTERRUPT_SOURCE_BLOCK1 = 0x1U,
    //! Block 2 is the interrupt source
    WADI_INTERRUPT_SOURCE_BLOCK2 = 0x2U,
    //! Block 3 is the interrupt source
    WADI_INTERRUPT_SOURCE_BLOCK3 = 0x4U,
    //! Block 4 is the interrupt source
    WADI_INTERRUPT_SOURCE_BLOCK4 = 0x8U,
    //! Interrupt is generated due to any signal anomaly
    WADI_INTERRUPT_SOURCE_SIG = 0x40000000U,
    //! Interrupt is generated due to mismatch between signals
    WADI_INTERRUPT_SOURCE_SIGTOSIG = 0x80000000U
} WADI_InterruptSource;

//*****************************************************************************
//
//! Different types of error that can occur
//
//*****************************************************************************
typedef enum
{
    //! Compare A error of signal 1
    WADI_ERROR_TYPES_SIG1CMPAERR  = 0x1U,
    //! Peak error of signal 1
    WADI_ERROR_TYPES_SIG1PKERR  = 0x2U,
    //! Average error of signal 1
    WADI_ERROR_TYPES_SIG1AVGERR  = 0x4U,
    //! Compare B error of signal 1
    WADI_ERROR_TYPES_SIG1CMPBERR  = 0x8U,
    //! Compare error in signal to signal analysis
    WADI_ERROR_TYPES_SIGTOSIG_CMPERR  = 0x100U,
    //! Peak error in signal to signal analysis
    WADI_ERROR_TYPES_SIGTOSIG_PKERR  = 0x200U,
    //! Average error in signal to signal analysis
    WADI_ERROR_TYPES_SIGTOSIG_AVGERR  = 0x400U,
    //! Deadband compare A error
    WADI_ERROR_TYPES_SIGTOSIG_DBCMPAERR  = 0x800U,
    //! Phase Overlap compare A error
    WADI_ERROR_TYPES_SIGTOSIG_OLAPCMPAERR  = 0x1000U,
    //! Deadband compare B error
    WADI_ERROR_TYPES_SIGTOSIG_DBCMPBERR  = 0x2000U,
    //! Phase Overlap compare B error
    WADI_ERROR_TYPES_SIGTOSIG_OLAPCMPBERR  = 0x4000U,
    //! Compare A error in signal 2
    WADI_ERROR_TYPES_SIG2CMPAERR  = 0x10000U,
    //! Peak error in signal 2
    WADI_ERROR_TYPES_SIG2PKERR  = 0x20000U,
    //! Average error in signal 2
    WADI_ERROR_TYPES_SIG2AVGERR  = 0x40000U,
    //! Compare B error in signal 2
    WADI_ERROR_TYPES_SIG2CMPBERR  = 0x80000U
} WADI_ErrorTypes;

//*****************************************************************************
//
//! WADI events
//
//*****************************************************************************
typedef enum
{
    WADI_EVENT1 = 0x1U,
    WADI_EVENT2 = 0x2U,
    WADI_EVENT3 = 0x4U,
    WADI_EVENT4 = 0x8U,
    WADI_EVENT5 = 0x10U,
    WADI_EVENT6 = 0x20U,
    WADI_EVENT7 = 0x40U,
    WADI_EVENT8 = 0x80U
} WADI_Event;

//*****************************************************************************
//
//! WADI output events
//
//*****************************************************************************
typedef enum
{
    WADI_OUTPUT_EVENT1 = 0x1U,
    WADI_OUTPUT_EVENT2 = 0x2U,
    WADI_OUTPUT_EVENT3 = 0x4U,
    WADI_OUTPUT_EVENT4 = 0x8U,
    WADI_OUTPUT_EVENT5 = 0x10U,
    WADI_OUTPUT_EVENT6 = 0x20U,
    WADI_OUTPUT_EVENT7 = 0x40U,
    WADI_OUTPUT_EVENT8 = 0x80U,
} WADI_OutputEvent;

//*****************************************************************************
//
//! Errors of Blocks
//
//*****************************************************************************
typedef enum
{
    //! SIG1 & SIGTOSIG event aggregation of block1
    WADI_EVENT_ERROR_SIG1_SIGTOSIG_BLOCK1 = 0x1U,
    //! SIG2 event aggregation of block1
    WADI_EVENT_ERROR_SIG2_BLOCK1 = 0x2U,
    //! SIG1 & SIGTOSIG event aggregation of block2
    WADI_EVENT_ERROR_SIG1_SIGTOSIG_BLOCK2 = 0x4U,
    //! SIG2 event aggregation of block2
    WADI_EVENT_ERROR_SIG2_BLOCK2 = 0x8U,
    //! SIG1 & SIGTOSIG event aggregation of block3
    WADI_EVENT_ERROR_SIG1_SIGTOSIG_BLOCK3 = 0x10U,
    //! SIG2 event aggregation of block3
    WADI_EVENT_ERROR_SIG2_BLOCK3 = 0x20U,
    //! SIG1 & SIGTOSIG event aggregation of block4
    WADI_EVENT_ERROR_SIG1_SIGTOSIG_BLOCK4 = 0x40U,
    //! SIG2 event aggregation of block4
    WADI_EVENT_ERROR_SIG2_BLOCK4 = 0x80U
} WADI_EventError;

//*****************************************************************************
//
//! Actions that a output event can perform
//
//*****************************************************************************
typedef enum
{
    WADI_SSS_OUTPUT_ACTION_LOW = 0x0U,
    //! SIG1 output override of block1
    WADI_SSS_OUTPUT_ACTION_BLOCK1_SIG1_HIGH = 0x1U,
    //! SIG2 output override of block1
    WADI_SSS_OUTPUT_ACTION_BLOCK1_SIG2_HIGH = 0x2U,
    //! SIG1 output override of block2
    WADI_SSS_OUTPUT_ACTION_BLOCK2_SIG1_HIGH = 0x4U,
    //! SIG2 output override of block2
    WADI_SSS_OUTPUT_ACTION_BLOCK2_SIG2_HIGH = 0x8U,
    //! SIG1 output override of block3
    WADI_SSS_OUTPUT_ACTION_BLOCK3_SIG1_HIGH = 0x10U,
    //! SIG2 output override of block3
    WADI_SSS_OUTPUT_ACTION_BLOCK3_SIG2_HIGH = 0x20U,
    //! SIG1 output override of block4
    WADI_SSS_OUTPUT_ACTION_BLOCK4_SIG1_HIGH = 0x40U,
    //! SIG2 output override of block4
    WADI_SSS_OUTPUT_ACTION_BLOCK4_SIG2_HIGH = 0x80U
} WADI_SSSOutputAction;

//*****************************************************************************
//
//! Signals that a output event of the SSS can control
//
//*****************************************************************************
typedef enum
{
    //! Block 1 signal 1
    WADI_OUTPUT_SIGNAL_BLOCK1_SIG1 = 0U,
    //! Block 1 signal 2
    WADI_OUTPUT_SIGNAL_BLOCK1_SIG2 = 1U,
    //! Block 2 signal 1
    WADI_OUTPUT_SIGNAL_BLOCK2_SIG1 = 2U,
    //! Block 2 signal 2
    WADI_OUTPUT_SIGNAL_BLOCK2_SIG2 = 3U,
    //! Block 3 signal 1
    WADI_OUTPUT_SIGNAL_BLOCK3_SIG1 = 4U,
    //! Block 3 signal 2
    WADI_OUTPUT_SIGNAL_BLOCK3_SIG2 = 5U,
    //! Block 4 signal 1
    WADI_OUTPUT_SIGNAL_BLOCK4_SIG1 = 6U,
    //! Block 4 signal 2
    WADI_OUTPUT_SIGNAL_BLOCK4_SIG2 = 7U
}WADI_OutputSignal;

//*****************************************************************************
//
//! Different modes to override a signal
//
//*****************************************************************************
typedef enum
{
    WADI_SIG_OVERRIDE_NO_ACTION = 0x0U,
    WADI_SIG_OVERRIDE_LOW = 0x2U,
    WADI_SIG_OVERRIDE_HIGH = 0x3U,
}WADI_SigOverride;

//*****************************************************************************
//
//! Different modes to override both the signals
//
//*****************************************************************************
typedef enum
{
    WADI_SIGTOSIG_OVERRIDE_NO_ACTION = 0x0U,
    WADI_SIGTOSIG_OVERRIDE_LOW_LOW = 0x4U,
    WADI_SIGTOSIG_OVERRIDE_LOW_HIGH = 0x5U,
    WADI_SIGTOSIG_OVERRIDE_HIGH_LOW = 0x6U,
    WADI_SIGTOSIG_OVERRIDE_HIGH_HIGH = 0x7U
}WADI_SigToSigOverride;

//*****************************************************************************
//
//! Different Sources that can access DMA
//
//*****************************************************************************
typedef enum
{
    //! Block 1
    WADI_DMA_REQ_SOURCES_BLOCK1 = 0x1U,
    //! Block 2
    WADI_DMA_REQ_SOURCES_BLOCK2 = 0x2U,
    //! Block 3
    WADI_DMA_REQ_SOURCES_BLOCK3 = 0x4U,
    //! Block 4
    WADI_DMA_REQ_SOURCES_BLOCK4 = 0x8U,
    //! SSS event 1
    WADI_DMA_REQ_SOURCES_SSS_EVENT1 = 0x10000U,
    //! SSS event 2
    WADI_DMA_REQ_SOURCES_SSS_EVENT2 = 0x20000U,
    //! SSS event 3
    WADI_DMA_REQ_SOURCES_SSS_EVENT3 = 0x40000U,
    //! SSS event 4
    WADI_DMA_REQ_SOURCES_SSS_EVENT4 = 0x80000U,
    //! SSS event 5
    WADI_DMA_REQ_SOURCES_SSS_EVENT5 = 0x100000U,
    //! SSS event 6
    WADI_DMA_REQ_SOURCES_SSS_EVENT6 = 0x200000U,
    //! SSS event 7
    WADI_DMA_REQ_SOURCES_SSS_EVENT7 = 0x400000U,
    //! SSS event 8
    WADI_DMA_REQ_SOURCES_SSS_EVENT8 = 0x800000U,
    //! SSS output event 1
    WADI_DMA_REQ_SOURCES_SSS_OUTPUT_EVENT1 = 0x1000000U,
    //! SSS output event 2
    WADI_DMA_REQ_SOURCES_SSS_OUTPUT_EVENT2 = 0x2000000U,
    //! SSS output event 3
    WADI_DMA_REQ_SOURCES_SSS_OUTPUT_EVENT3 = 0x4000000U,
    //! SSS output event 4
    WADI_DMA_REQ_SOURCES_SSS_OUTPUT_EVENT4 = 0x8000000U,
    //! SSS output event 5
    WADI_DMA_REQ_SOURCES_SSS_OUTPUT_EVENT5 = 0x10000000U,
    //! SSS output event 6
    WADI_DMA_REQ_SOURCES_SSS_OUTPUT_EVENT6 = 0x20000000U,
    //! SSS output event 7
    WADI_DMA_REQ_SOURCES_SSS_OUTPUT_EVENT7 = 0x40000000U,
    //! SSS output event 8
    WADI_DMA_REQ_SOURCES_SSS_OUTPUT_EVENT8 = 0x80000000U
}WADI_DMAReqSources;

//*****************************************************************************
//
//! Structure containing the parameters to configure a particular signal
//
//*****************************************************************************
typedef struct
{
    WADI_Signal                 signal;
    WADI_TriggerMode            triggerMode;
} WADI_SigConfig;

//*****************************************************************************
//
//! Values that can be passed to the WADI_measurePulseWidth() function in the
//! \e configParams parameter to configure a particular signal
//
//*****************************************************************************
typedef struct
{
    //! Edgespan for measurement
    WADI_EdgeSpan               edgeSpan;
    //! Number of measurements to be aggregated
    WADI_NumberOfAggregation    numAggr;
    //! Mode of measurement
    WADI_AggregationMode        aggrMode;
    //! Polarity of the configured edge of the signal
    WADI_SignalPolarity         polarity;
} WADI_PulseWidthConfigParams;

//*****************************************************************************
//
//! Values that can be passed to the WADI_measurePulseWidth() function in the
//! \e configCompare parameter
//
//*****************************************************************************
typedef struct
{
    uint32_t cmpAVal;               //!< Compare A value
    uint8_t cmpAMargin;             //!< Compare A margin
    uint32_t cmpBVal;               //!< Compare B value
    uint8_t cmpBMargin;             //!< Compare B margin
    uint32_t cmpAvgVal;             //!< Compare value for average mode
    uint8_t cmpAvgMargin;           //!< Compare margin for average mode
    uint32_t cmpPkVal;              //!< Compare value for peak mode
    uint8_t cmpPkMargin;            //!< Compare margin for peak mode
} WADI_PulseWidthConfigCompare;

//*****************************************************************************
//
//! Values that can be passed to the WADI_measureFrequency function
//! in the \e configParams parameter
//
//*****************************************************************************
typedef struct
{
    //! Frequency Mode - can be either fixed window or moving window mode
    WADI_CompareFreqMode        freqMode;
    //! Polarity of the configured edge of the signal
    WADI_SignalPolarity         polarity;
    //! Mode of measurement
    WADI_AggregationMode        aggrMode;
    //! Number of measurements to be aggregated
    WADI_NumberOfAggregation    numaggr;
    //! Time window in case of fixed window frequency
    uint32_t                    timeWindow;
    //! Moving window time in case of moving window frequency mode
    uint32_t                    mvwtime;
    //! Moving window count in case of moving window frequency mode
    WADI_MovingCount            movingCount;
}WADI_FreqConfigParams;

//*****************************************************************************
//
//! Values that can be passed to the WADI_measureFrequency function
//! in the \e configCompare parameter
//
//*****************************************************************************
typedef struct
{
    uint32_t cmpAVal;               //!< Compare A value
    uint8_t cmpAMargin;             //!< Compare A margin
    uint32_t cmpBVal;               //!< Compare B value
    uint8_t cmpBMargin;             //!< Compare B margin
    uint32_t cmpAvgVal;             //!< Compare value for average mode
    uint8_t cmpAvgMargin;           //!< Compare margin for average mode
    uint32_t cmpPkVal;              //!< Compare value for peak mode
    uint8_t cmpPkMargin;            //!< Compare margin for peak mode
} WADI_FreqConfigCompare;

//*****************************************************************************
//
//! Structure containing the necessary parameters to configure both the
//! signals
//
//*****************************************************************************
typedef struct
{
    WADI_TriggerMode    triggerMode1;   //!< Trigger mode of signal 1
    WADI_TriggerMode    triggerMode2;   //!< Trigger mode of signal 2
} WADI_SigToSigConfig;

//*****************************************************************************
//
//! Values that can be passed to the WADI_compareSigToSigPulseWidth() as the
//! \e configParams parameter
//
//*****************************************************************************
typedef struct
{
    WADI_AggregationMode        aggrMode;
    WADI_NumberOfAggregation    numAggr;
    WADI_EdgeSpan               edgeSpan;
    WADI_SignalPolarity         polarity;
} WADI_SigToSigPWConfigParams;

//*****************************************************************************
//
//! Values that can be passed to the WADI_compareSigToSigPulseWidth() as the
//! \e configCompare parameter
//
//*****************************************************************************
typedef struct
{
    uint32_t cmpVal;                //!< Compare value
    uint8_t cmpMargin;              //!< Compare margin
    uint32_t cmpAvgVal;             //!< Compare value for average mode
    uint8_t cmpAvgMargin;           //!< Compare margin for average mode
    uint32_t cmpPkVal;              //!< Compare value for peak mode
    uint8_t cmpPkMargin;            //!< Compare margin for peak mode
} WADI_SigToSigPWConfigCompare;

//*****************************************************************************
//
//! Values that can be passed to the WADI_compareSigToSigFrequency()
//! as the \e configParams parameter
//
//*****************************************************************************
typedef struct
{
    //! Frequency Mode - can be either fixed window or moving window mode
    WADI_CompareFreqMode        freqMode;
    //! Polarity of the configured edge of the signals
    WADI_SignalPolarity         polarity;
    //! Mode of measurement
    WADI_AggregationMode        aggrMode;
    //! number of measurements to be aggregated
    WADI_NumberOfAggregation    numaggr;
    //! Time window in case of fixed window frequency mode
    uint32_t timeWindow;
    //! Moving window count in case of moving window frequency mode
    WADI_MovingCount        movingCount;
    //! Moving window time in case of moving window frequency mode
    uint32_t  mvwtime;
}WADI_SigToSigFreqConfigParams;

//*****************************************************************************
//
//! Values that can be passed to the WADI_compareSigToSigFrequency()
//! as the \e configCompare parameter
//
//*****************************************************************************
typedef struct
{
    uint32_t cmpVal;                //!< Compare value
    uint8_t cmpMargin;              //!< Compare margin
    uint32_t cmpAvgVal;             //!< Compare value for average mode
    uint8_t cmpAvgMargin;           //!< Compare margin for average mode
    uint32_t cmpPkVal;              //!< Compare value for peak mode
    uint8_t cmpPkMargin;            //!< Compare margin for peak mode
} WADI_SigToSigFreqConfigCompare;

//*****************************************************************************
//
//! Values that can be passed to the WADI_compareSigToSigDeadBandMode()
//! as the \e configParams parameter
//
//*****************************************************************************
typedef struct
{

    WADI_CompareType  compareType;          //!< Mode of compare
    WADI_SignalPolarity polarity1;          //!< Configured edge type of
                                            //!< signal 1
    WADI_SignalPolarity polarity2;          //!< Configured edge type of
                                            //!< signal 2
    uint8_t compareA;                       //!< Compare A value
    uint8_t compareB;                       //!< Compare B value
}WADI_SigToSigDeadbandConfigParams;

//*****************************************************************************
//
//! Values that can be passed to the WADI_compareSigToSigPhaseOverlapMode()
//! as the \e configParams parameter
//
//*****************************************************************************
typedef struct
{
    WADI_CompareType  compareType;          //!< Mode of compare
    WADI_SignalPolarity polarity1;          //!< Configured edge type of
                                            //!< signal 1
    WADI_SignalPolarity polarity2;          //!< Configured edge type of
                                            //!< signal 2
    uint16_t compareA;                      //!< Compare A value
    uint8_t compareAMargin;                 //!< Compare A margin
    uint16_t compareB;                      //!< Compare B value
    uint8_t compareBMargin;                 //!< Compare B margin
}WADI_SigToSigPhaseOverlapCompareParams;

//*****************************************************************************
//
// Prototypes for the API.
//
//*****************************************************************************

//*****************************************************************************
//
//! \internal
//! Checks WADI base address.
//!
//! \param base specifies the WADI block base address.
//!
//! This function determines if an WADI block base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
WADI_isBaseValid(uint32_t base)
{
        return(
           ((base & BASE_ADDR_MASK) == WADI1BLK1CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI1BLK2CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI1BLK3CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI1BLK4CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI2BLK1CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI2BLK2CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI2BLK3CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI2BLK4CONFIG_BASE_FRAME(0U))
          );
}
#endif


//*****************************************************************************
//
//! \internal
//! Checks SSS base address.
//!
//! \param base specifies the SSS base address.
//!
//! This function determines if the SSS base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
WADI_isSSSBaseValid(uint32_t base)
{
        return(
           ((base & BASE_ADDR_MASK) == WADI1OPERSSS_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI2OPERSSS_BASE_FRAME(0U))
          );
}
#endif


//*****************************************************************************
//
//! \internal
//! Checks if the base address is that of WADI1.
//!
//! \param base specifies the base address
//!
//! This function determines if the given base address is that of WADI1
//!
//! \return Returns \b true if the base address is that of WADI1
//!  and \b false otherwise.
//
//*****************************************************************************
static inline bool
WADI_isWadi1(uint32_t base)
{
        return(
           ((base & BASE_ADDR_MASK) == WADI1BLK1CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI1BLK2CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI1BLK3CONFIG_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == WADI1BLK4CONFIG_BASE_FRAME(0U))
          );
}

//*****************************************************************************
//
//! Enables the clock
//!
//! \param base is the base address of the WADI block.
//!
//! This function enables the WADI clock.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_enableClock(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Write to the BLKCFG register
    //
    HWREGB(base + WADI_O_BLKCFG) = (uint8_t)WADI_BLKCFG_CLKEN;

}

//*****************************************************************************
//
//! Disables the clock
//!
//! \param base is the base address of the WADI block.
//!
//! This function disables the WADI clock.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_disableClock(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Write to the BLKCFG register
    //
    HWREGB(base + WADI_O_BLKCFG) &= (uint8_t)~WADI_BLKCFG_CLKEN;
}

//*****************************************************************************
//
//! Software trigger
//!
//! \param base is the base address of the WADI block.
//! \param signal is the signal for whom the trigger is to be issued
//!
//! This function acts as the software trigger for the signal and enables
//! measurement for the following signal.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_enableSoftwareTrigger(uint32_t base, WADI_Signal signal)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Enable the software trigger for the signal
    //
    if(signal == WADI_SIGNAL1)
    {
        HWREG(base + WADI_O_BLKTRIGCFG) |= WADI_BLKTRIGCFG_TRIG1SWEN;
    }
    else
    {
        HWREG(base + WADI_O_BLKTRIGCFG) |= WADI_BLKTRIGCFG_TRIG2SWEN;
    }
}

//*****************************************************************************
//
//! Set the Trigger mode
//!
//! \param base is the base address of the WADI block.
//! \param signal is the signal for whom the trigger mode is to be set.
//! \param triggerMode is the trigger mode which is to be set for the signal.
//!
//! This function sets the trigger mode for the particular signal.
//! If the trigger mode is set to be \b WADI_TRIGGER_MODE_SOFTWARE_TRIGGER
//! or \b WADI_TRIGGER_MODE_EITHER_TRIGGER , make sure to enable the software
//! trigger after the clock is enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_setTriggerMode(uint32_t base, WADI_Signal signal,
                    WADI_TriggerMode triggerMode)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    if(signal == WADI_SIGNAL1)  //! signal 1
    {
        HWREGB(base + WADI_O_BLKTRIGCFG)
            |= (uint8_t)(((uint32_t)triggerMode << WADI_BLKTRIGCFG_TRIG1TYPE_S));
    }
    else                        //! signal 2
    {
        HWREG(base + WADI_O_BLKTRIGCFG)
            |= ((uint32_t)triggerMode << WADI_BLKTRIGCFG_TRIG2TYPE_S);
    }
}

//*****************************************************************************
//
//! Enables the base timer
//!
//! \param base is the base address of the SSS
//!
//! This function enables the base timer of all the WADI blocks
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_enableBaseTimer(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Enabling the base timer.
    //
    HWREG(base + WADI_O_BASETIMERHIGH) |= WADI_BASETIMERHIGH_ENBASETIMER;
}

//*****************************************************************************
//
//! Disables the base timer
//!
//! \param base is the base address of the SSS.
//!
//! Disabling the base timer.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_disableBaseTimer(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Clearing the ENBASETIMER bit in the BASETIMERHIGH register
    //
    HWREG(base + WADI_O_BASETIMERHIGH) &= ~WADI_BASETIMERHIGH_ENBASETIMER;
}

//*****************************************************************************
//
//! Enable interrupt
//!
//! \param base is the base address of the SSS
//! \param source is the logical OR of the contents of the enum
//! WADI_InterruptSource
//
//! This function enables the interrupt in case of a block error,
//! signal error or signal to signal error.
//
//! \return None.
//
//*****************************************************************************
static inline void
WADI_enableInterrupt(uint32_t base, uint32_t source)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Enable interrupt for the specific source
    //
    HWREG(base + WADI_O_INTSTSMASK) |= source;
}

//*****************************************************************************
//
//! Disable interrupt
//!
//! \param base is the base address of the SSS
//! \param source is the logical OR of the contents of the enum
//! WADI_InterruptSource
//
//! This function disables the interrupt in case of a block error,
//! signal error or signal to signal error.
//
//! \return None.
//
//*****************************************************************************
static inline void
WADI_disableInterrupt(uint32_t base, uint32_t source)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Disable interrupt for the specific source
    //
    HWREG(base + WADI_O_INTSTSMASK) &= ~source;
}

//*****************************************************************************
//
//! Setting the error mask.
//!
//! \param base is the base address of the WADI block.
//! \param error denotes the different errors that will be allowed to
//! aggregate in the SSS Trigger word.
//!
//! This function selects the errors that will be aggregated in the SSS event
//! trigger word.
//!
//! The \e error parameter is the logical OR of the components of the enum
//! WADI_ErrorTypes.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_setSSSTriggerWord(uint32_t base, uint32_t error)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Write in the SSS_EVTMASK register
    //
    HWREG(base + WADI_O_SSS_EVTMASK)|= error;
}

//*****************************************************************************
//
//! Configuring the events.
//!
//! \param base is the base address of the SSS.
//! \param event is the event whom to configure.
//! \param blockError is the logical OR of the contents of enum
//! \b WADI_EventError.
//!
//! This function configures the eight configurable events.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_configSSSEvent(uint32_t base, WADI_Event event, uint32_t blockError)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Convert bitmask to event index (0 to 7)
    //
    uint32_t index = 0, temp;
    temp = (uint32_t)event >> 1;
    while (temp != 0U)
    {
        index++;
        temp >>= 1;
    }

    //
    // Calculate register offset
    //

    uint32_t offset;
    if(index < 4)
    {
        offset = WADI_O_SSS_EVT1CFG + (index * 4U);
    }
    else
    {
        offset = WADI_O_SSS_EVT5CFG + ((index % 4U) * 4U);
    }

    HWREG(base + offset) |= blockError;
}


//*****************************************************************************
//
//! Writing the Trigger Sequence
//!
//! \param base is the base address of the SSS
//! \param startEvent is the starting event of the sequence
//! \param endEvent is the ending event of the sequence
//!
//! This function sets the trigger sequence required to trigger the SSS
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_configSSSTriggerSequence(uint32_t base,
                                WADI_Event startEvent,
                                WADI_Event endEvent)
{
    uint32_t i = 0U;

    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Converting the bitmask to event index
    //
    uint32_t temp;
    uint32_t indexStartEvent = 0;
    temp = (uint32_t)startEvent >> 1;
    while (temp != 0U)
    {
        indexStartEvent++;
        temp >>= 1;
    }

    uint32_t indexEndEvent = 0;
    temp = (uint32_t)endEvent >> 1;
    while (temp != 0U)
    {
        indexEndEvent++;
        temp >>= 1;
    }

    ASSERT(indexStartEvent <= indexEndEvent);

    //
    // Set trigger types for the events
    //
    uint8_t trigType[8] = {0};
    for (i = 0; i <= 7U; i++)
    {
        if((i < indexStartEvent) || (i > indexEndEvent))
        {
            trigType[i] = 0x0U; //!< not used
        }
        else if(i == indexEndEvent)
        {
            trigType[i] = 0x1U; //!< start with immediate
        }
        else
        {
            trigType[i] = 0x9U; //!< in sequence
        }
    }

    uint32_t reg1 = 0;
    uint32_t reg2 = 0;

    //
    // The complement must be written before the actual value
    //
    for (i = 0; i < 4U; i++)
    {
        uint8_t val = trigType[i] & 0xFU;
        uint8_t byte = ((~val & 0xFU) << 4U) | val;
        reg1 |= ((uint32_t)byte << ((i % 4U) * 8U));
    }

    if(indexEndEvent >= 4U)
    {
        for (i = 4U; i < 8U; i++)
        {
            uint8_t val = trigType[i] & 0xFU;
            uint8_t byte = ((~val & 0xFU) << 4U) | val;
            reg2 |= ((uint32_t)byte << ((i % 4U) * 8U));
        }
    }
    HWREG(base + WADI_O_SSS_TRIGEVT1_4CFG) |= reg1;
    HWREG(base + WADI_O_SSS_TRIGEVT5_8CFG) |= reg2;
}

//*****************************************************************************
//
//! Configuring the event trigger for the SSS output events
//!
//! \param base is the base address of the SSS.
//! \param outputEvent is the the particular output event whose event
//! trigger is to be configured.
//! \param eventTrig denotes which all events can trigger this
//!  particular event.
//!
//! This function configures the triggers for the different output events
//! of the SSS. One output event can be triggered by multiple events.
//!
//! The \e eventTrig parameter is the logical OR of the different events which
//! can trigger the particular output event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_configSSSOutputEventTrigger(uint32_t base,
                                WADI_OutputEvent outputEvent,
                                uint32_t eventTrig)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Convert bitmask to output event index (0 to 7)
    //
    uint32_t outputEventIndex = 0, temp;
    temp = (uint32_t)outputEvent >> 1;
    while (temp != 0U)
    {
        outputEventIndex++;
        temp >>= 1;
    }

    //
    // Configuring which events will trigger the particular output event
    //
    if(outputEventIndex < 4)
    {
        HWREGB(base + WADI_O_SSS_OUTEVT1TRIGCFG + (outputEventIndex * 4U))
                                                        |= (uint8_t)eventTrig;
    }
    else
    {
        HWREGB(base + WADI_O_SSS_OUTEVT5TRIGCFG +
                ((outputEventIndex % 4) * 4U)) |= (uint8_t)eventTrig;
    }
}

//*****************************************************************************
//
//! Configuring the SSS output events parameters with link.
//!
//! \param base is the base address of the SSS.
//! \param outputEvent is the the particular output event to be configured.
//! \param outputAction denotes the action that the output event will perform.
//! \param duration denotes the time for which the output event
//! will be active. For driving fixed value safe state input, the
//! duration needs to be configured to \b 0xFFFFFF.
//! \param linkOutputEvent denotes which output events needs to be linked
//! after the particular output event.
//!
//! This function configures the different output events of the SSS which
//! are linked to other output events. One output event can be triggered
//! by multiple events.
//!
//! The \e outputAction is the logical OR of the different actions the
//! particular output event will perform. It is the logical OR of the
//! contents of the enum WADI_SSSOutputAction.
//!
//! The \e linkOutputEvent is the logical OR of the different output events
//! the particular output event will be linked to. It is the logical OR
//! of the contents of the enum WADI_OutputEvent.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_configSSSOutputEventParamsWithLink(uint32_t base,
                        WADI_OutputEvent outputEvent,
                        uint32_t outputAction,
                        uint32_t duration,
                        uint32_t linkOutputEvent)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Convert bitmask to output event index (0 to 7)
    //
    uint32_t outputEventIndex = 0, temp;
    temp = (uint32_t)outputEvent >> 1;
    while (temp != 0U)
    {
        outputEventIndex++;
        temp >>= 1;
    }

    //
    // Writing the signals that this output event can override
    //
    if(outputEventIndex < 4U)
    {
        HWREGB(base + WADI_O_SSS_BLKSOUTEVT1CFG + (outputEventIndex * 4U))
                                                |= (uint8_t)(outputAction);
    }
    else
    {
        HWREGB(base + WADI_O_SSS_BLKSOUTEVT5CFG +
                ((outputEventIndex % 4U) * 4U)) |= (uint8_t)(outputAction);
    }

    //
    // Setting the duration of the Output event
    //
    if(outputEventIndex < 4U)
    {
        HWREG(base + WADI_O_SSS_OUTEVT1DUR + (outputEventIndex * 4U))
                                                            |= (duration);
    }
    else
    {
        HWREG(base + WADI_O_SSS_OUTEVT5DUR + ((outputEventIndex % 4U) * 4U))
                                                            |= (duration);
    }

    //
    // Linking the output event to the other output events if needed
    //
    HWREG(base + WADI_O_SSS_OUTEVT1LINKCFG + (outputEventIndex * 4U))
                                                |= linkOutputEvent;
}

//*****************************************************************************
//
//! Configuring the SSS output events parameters without link.
//!
//! \param base is the base address of the SSS.
//! \param outputEvent is the the particular output event to be configured.
//! \param outputAction denotes the action that the output event will perform.
//! \param duration denotes the time for which the output event
//! will be active. For driving fixed value safe state input, the
//! duration needs to be configured to \b 0xFFFFFF.
//!
//! This function configures the different output events of the SSS which
//! are not linked to other output events. One output event can be triggered
//! by multiple events.
//!
//! The \e outputAction is the logical OR of the different actions the
//! particular output event will perform. It is the logical OR of the
//! contents of the enum WADI_SSSOutputAction.
//!
//! The \e linkOutputEvent is the logical OR of the different output events
//! the particular output event will be linked to. It is the logical OR
//! of the contents of the enum WADI_OutputEvent.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_configSSSOutputEventParamsWithoutLink(uint32_t base,
                        WADI_OutputEvent outputEvent,
                        uint32_t outputAction,
                        uint32_t duration)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Convert bitmask to output event index (0 to 7)
    //
    uint32_t outputEventIndex = 0, temp;
    temp = (uint32_t)outputEvent >> 1;
    while (temp != 0U)
    {
        outputEventIndex++;
        temp >>= 1;
    }

    //
    // Writing the signals that this output event can override
    //
    if(outputEventIndex < 4U)
    {
        HWREGB(base + WADI_O_SSS_BLKSOUTEVT1CFG + (outputEventIndex * 4U))
                                                |= (uint8_t)(outputAction);
    }
    else
    {
        HWREGB(base + WADI_O_SSS_BLKSOUTEVT5CFG +
               ((outputEventIndex % 4U) * 4U)) |= (uint8_t)(outputAction);
    }

    //
    // Setting the duration of the Output event
    //
    if(outputEventIndex < 4U)
    {
        HWREG(base + WADI_O_SSS_OUTEVT1DUR + (outputEventIndex * 4U))
                                                            |= (duration);
    }
    else
    {
        HWREG(base + WADI_O_SSS_OUTEVT5DUR + ((outputEventIndex % 4U) * 4U))
                                                            |= (duration);
    }
}

//*****************************************************************************
//
//! Selecting the output events.
//!
//! \param base is the base address of the SSS.
//! \param outputSignal denotes an output signal of WADI.
//! \param outputEventSSS denotes the output events of the SSS, that will
//! be mapped to the particular output signal of WADI.
//!
//! This function selects the output events of the SSS that will be mapped
//! to a particular output signal of the WADI.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_selectSSSOutputEvent(uint32_t base,
                        WADI_OutputSignal outputSignal,
                        uint32_t outputEventSSS)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Selecting the output events to be muxed to the corresponding
    // output signal
    //
    if(outputSignal < 4U)
    {
        HWREG(base + WADI_O_SSS_BLK1_2OUTSEL)
            |= (outputEventSSS << (outputSignal * 8U));
    }
    else
    {
        HWREG(base + WADI_O_SSS_BLK3_4OUTSEL)
            |= (outputEventSSS << ((outputSignal % 4U) * 8U));
    }
}

//*****************************************************************************
//
//! Signal override in case there is no SSS
//!
//! \param base is the base address of the WADI block
//! \param signal is the signal which is to be overridden
//! \param mode is the mode of override
//!
//! This function overrides the signal to some predefined safe state in
//! in the case of an error
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_overrideSig (uint32_t base,
                WADI_Signal signal,
                WADI_SigOverride mode)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Write to the BLKERRCFG register
    //
    if(signal == WADI_SIGNAL1)  //!< signal 1
    {
        HWREG(base + WADI_O_BLKERRCFG)
            |= (mode << WADI_BLKERRCFG_OVERIDESIG1_S);
    }
    else                        //!< signal 2
    {
         HWREG(base + WADI_O_BLKERRCFG)
            |= (mode << WADI_BLKERRCFG_OVERIDESIG2_S);
    }
}

//*****************************************************************************
//
//! Signals override in case there is no SSS
//!
//! \param base is the base address of the WADI block
//! \param mode is the mode of override for both the signals
//!
//! This function overrides the signal to some predefined safe state in
//! in the case of an error n the signl to signal mode
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_overrideSigToSig (uint32_t base,
                WADI_SigToSigOverride mode)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Write to the BLKERRCFG register
    //
    HWREG(base + WADI_O_BLKERRCFG)
        |= (mode << WADI_BLKERRCFG_OVERIDESIGTOSIG_S);
}

//*****************************************************************************
//
//! Enable the DMA trigger
//!
//! \param base is the base address of the SSS
//! \param dmaSources is the source whose DMA trigger is to be enabled.
//!
//! This function enables the DMA trigger for a particular block,
//! event or output event.
//!
//! The \e dmaSources is the logical OR of the  different sources for which
//! the DMA trigger is to be enabled. It is basically the logical OR of the
//! contents of the enum WADI_DMAReqSources.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_enableDmaTrigger(uint32_t base, uint32_t dmaSources)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Enable the DMA trigger for that particular source
    //
    HWREG(base + WADI_O_DMATRIGEN) |= dmaSources;
}

//*****************************************************************************
//
//! Diasble the DMA trigger
//!
//! \param base is the base address of the SSS
//! \param dmaSources is the source whose DMA trigger is to be disabled.
//!
//! This function disables the DMA trigger for a particular block,
//! event or output event.
//!
//! The \e dmaSources is the logical OR of the  different sources for
//! which the DMA trigger is to be disabled. It is basically the logical OR
//! of the contents of the enum WADI_DMAReqSources.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_disableDmaTrigger(uint32_t base, uint32_t dmaSources)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Clear the DMA trigger for that particular source
    //
    HWREG(base + WADI_O_DMATRIGEN) &= ~dmaSources;
}

//*****************************************************************************
//
//! Enable filtered writes
//!
//! \param base is the base address of the SSS
//! \param dmaSources is the source for which filtered write is to be enabled.
//!
//! This function enables the filtered write for a particular block,
//! event or output event
//!
//! The \e dmaSources is the logical OR of the  different sources for
//! which filtered write is to be enabled. It is basically the logical OR
//! of the contents of the enum WADI_DMAReqSources.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_enableFilteredWrite(uint32_t base, uint32_t dmaSources)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Enable filtered write for that particular source
    //
    HWREG(base + WADI_O_DMAFILTWRCFG) |= dmaSources;
}

//*****************************************************************************
//
//! Disable filtered writes
//!
//! \param base is the base address of the SSS
//! \param dmaSources is the source for which filtered write is to be disabled.
//!
//! This function disables the filtered write for a particular block,
//! event or output event.
//!
//! The \e dmaSources is the logical OR of the  different sources for
//! which filtered write is to be disabled. It is basically the logical OR
//! of the contents of the enum WADI_DMAReqSources.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_disableFilteredWrite(uint32_t base, uint32_t dmaSources)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Disable filtered write for that particular source
    //
    HWREG(base + WADI_O_DMAFILTWRCFG) &= ~dmaSources;
}

//*****************************************************************************
//
//! Clear the DMA status
//!
//! \param base is the base address of the SSS
//! \param dmaSources is the source whose DMA status is to be cleared
//!
//! This function clears the DMA status of a particular block,
//! event or output event.
//!
//! The \e dmaSources is the logical OR of the  different sources whose
//! DMA status is to be cleared. It is basically the logical OR
//! of the contents of the enum WADI_DMAReqSources.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_clearDmaStatus(uint32_t base, uint32_t dmaSources)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Clear that DMA status for the particular source
    //
    HWREG(base + WADI_O_DMASTSUPDATE) &= ~dmaSources;
}

//*****************************************************************************
//
//! Lock the WADI configuration registers
//!
//! \param base is the base address of the SSS
//!
//! This function locks all the WADI configuration registers that is
//! writes to those registers will have no effect on them.
//! This bit can only be modified if CONFIG_REG_COMMIT.COMMIT is cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_lockConfigReg(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Lock WADI configuration registers
    //
    HWREG(base + WADI_O_CFGREGLOCK) = WADI_CFGREGLOCK_LOCK;
}

//*****************************************************************************
//
//! Unlock the WADI configuration registers
//!
//! \param base is the base address of the SSS
//!
//! This function unlocks all the WADI configuration registers that is
//! they can be modified and writes to those registers are enabled.
//! This bit can only be modified if CONFIG_REG_COMMIT.COMMIT is cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_unlockConfigReg(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Unlock WADI configuration registers
    //
    HWREG(base + WADI_O_CFGREGLOCK) = 0U;
}

//*****************************************************************************
//
//! Commits the WADI configuration registers
//!
//! \param base is the base address of the SSS
//!
//! This function commits the lock on the DMA configuration registers.
//! Once committed, this bit can not be cleared, except by reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_commitConfigReg(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Commits the lock on the WADI configuration registers
    //
    HWREG(base + WADI_O_CFGREGCOMMIT) = WADI_CFGREGCOMMIT_COMMIT;
}

//*****************************************************************************
//
//! Lock the WADI operational registers
//!
//! \param base is the base address of the SSS
//!
//! This function locks all the WADI operational registers that is
//! writes to those registers will have no effect on them.
//! This bit can only be modified if OPER_REG_COMMIT.COMMIT is cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_lockOperationalReg(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Lock WADI opeational registers
    //
    HWREG(base + WADI_O_OPERREGLOCK) = WADI_OPERREGLOCK_LOCK;
}

//*****************************************************************************
//
//! Unlock the WADI operational registers
//!
//! \param base is the base address of the SSS
//!
//! This function unlocks all the WADI operational registers that is
//! they can be modified and writes to those registers are enabled.
//! This bit can only be modified if OPER_REG_COMMIT.COMMIT is cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_unlockOperationalReg(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Unlock WADI configuration registers
    //
    HWREG(base + WADI_O_OPERREGLOCK) = 0U;
}

//*****************************************************************************
//
//! Commits the WADI operational registers
//!
//! \param base is the base address of the SSS
//!
//! This function commits the lock on the DMA operational registers.
//! Once committed, this bit can not be cleared, except by reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
WADI_commitOperationalReg(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isSSSBaseValid(base));

    //
    // Commits the lock on the WADI operational registers
    //
    HWREG(base + WADI_O_OPERREGCOMMIT) = WADI_OPERREGCOMMIT_COMMIT;
}

//*****************************************************************************
//
//! Configuration of the Input signal and trigger signals
//!
//! \param base is the base address of the WADI instance.
//! \param signal1 is the signal source for input Signal1.
//! \param signal is the trigger source for Trigger1.
//! \param trigger1 is the signal source for input Signal2.
//! \param trigger2 is the trigger source for Trigger2.
//!
//! This function configures the input signal and trigger signal
//! configurations of a WADI block. It will not configure the trigger
//! mode of the two signals.
//!
//! \return None.
//
//*****************************************************************************
extern void
WADI_configSignalAndTrigger(uint32_t base,
                        WADI_InputSignal signal1,
                        WADI_InputSignal signal2,
                        WADI_Trigger1 trigger1,
                        WADI_Trigger2 trigger2);


//*****************************************************************************
//
//! Pulse width mode
//!
//! \param base is the base address of the WADI block.
//! \param configSignal is the desired signal configuration parameters
//!                                 Refer struct #WADI_SigConfig
//! \param configParams is the desired mode parameters
//!                                 Refer struct #WADI_PulseWidthConfigParams
//! \param configCompare is the desired compare parameters
//!                                 Refer struct #WADI_PulseWidthConfigCompare
//!
//! This function configures the WADI block in the pulse width mode for one
//! signal of the block
//!
//! \return None.
//
//*****************************************************************************
extern void
WADI_measurePulseWidth(uint32_t base,
                const WADI_SigConfig *configSignal,
                const WADI_PulseWidthConfigParams *configParams,
                const WADI_PulseWidthConfigCompare *configCompare);

//*****************************************************************************
//
//! Frequency Mode
//!
//! \param base is the base address of the WADI block.
//! \param configSignal is the desired signal configuration parameters
//!                                 Refer struct #WADI_SigConfig
//! \param configParams is the structure containing the required mode
//! configuration paramters
//!                                 Refer struct #WADI_FreqConfigParams
//! \param configCompare is the desired compare parameters
//!                                 Refer struct #WADI_FreqConfigCompare
//!
//! This function configures the WADI block for measurng in frequency mode
//! of a particular signal of the block.
//!
//! \return None.
//
//*****************************************************************************
extern void
WADI_measureFrequency(uint32_t base,
                    const WADI_SigConfig *configSignal,
                    const WADI_FreqConfigParams *configParams,
                    const WADI_FreqConfigCompare *configCompare);

//*****************************************************************************
//
//! Compare Pulse width between two signals
//!
//! \param base is the base address of the WADI block.
//! \param configSignals is the configuration parameters for both the signals
//!                                 Refer struct #WADI_SigToSigConfig
//! \param configParams is the desired mode parameters
//!                                 Refer struct #WADI_SigToSigPWConfigParams
//! \param configCompare is the desired compare parameters
//!                                 Refer struct #WADI_SigToSigPWConfigCompare
//!
//! This function configures the WADI block to compare pulse width
//! between two signals of the WADI block.
//!
//! \return None.
//
//*****************************************************************************
extern void
WADI_compareSigToSigPulseWidth(uint32_t base,
                const WADI_SigToSigConfig *configSignals,
                const WADI_SigToSigPWConfigParams *configParams,
                const WADI_SigToSigPWConfigCompare *configCompare);

//*****************************************************************************
//
//! Compare Frequency between two signals
//!
//! \param base is the base address of the WADI block.
//! \param configSignals is the configuration parameters for both the signals
//!                             Refer struct #WADI_SigToSigConfig
//! \param configParams is the different mode configuration parameters
//!                             Refer struct #WADI_SigToSigFreqConfigParams
//! \param configCompare is the desired compare parameters
//!                             Refer struct #WADI_SigToSigFreqConfigCompare
//!
//! This function configures the WADI block to compare frequency
//! between the two signals of the WADI block.
//!
//! \return None.
//
//*****************************************************************************
extern void
WADI_compareSigToSigFrequency(uint32_t base,
                const WADI_SigToSigConfig *configSignals,
                const WADI_SigToSigFreqConfigParams *configParams,
                const WADI_SigToSigFreqConfigCompare *configCompare);

//*****************************************************************************
//
//! Compare Deadband between two signals
//!
//! \param base is the base address of the WADI block.
//! \param configSignals is the configuration parameters for both the signals
//!                                 Refer struct #WADI_SigToSigConfig
//! \param configParams is the desired compare parameters
//!                           Refer struct #WADI_SigToSigDeadbandConfigParams
//!
//! This functions configure the WADI block to compare the deadband between
//! the two signals of the WADI block.
//!
//! \return None.
//
//*****************************************************************************
extern void
WADI_compareSigToSigDeadBandMode(uint32_t base,
                    const WADI_SigToSigConfig *configSignals,
                    const WADI_SigToSigDeadbandConfigParams *configParams);

//*****************************************************************************
//
//! Compare Phase Overlap between two signals
//!
//! \param base is the base address of the WADI block.
//! \param configSignals is the configuration parameters for both the signals
//!                                 Refer struct #WADI_SigToSigConfig
//! \param configParams is the desired compare parameters
//!                      Refer struct #WADI_SigToSigPhaseOverlapCompareParams
//!
//! This functions configure the WADI block to compare the phase overlap
//! between the two signals of the WADI block
//!
//! \return None.
//
//*****************************************************************************
extern void
WADI_compareSigToSigPhaseOverlapMode(uint32_t base,
                    const WADI_SigToSigConfig *configSignals,
                    const WADI_SigToSigPhaseOverlapCompareParams *configParams);


#ifdef __cplusplus
}
#endif

#endif // WADI_H
