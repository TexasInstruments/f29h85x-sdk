//#############################################################################
//
// FILE:   hrpwm.h
//
// TITLE:   C29x HRPWM Driver
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

#ifndef HRPWM_H
#define HRPWM_H

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
//! \addtogroup hrpwm_api HRPWM
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_epwm.h"
#include "inc/hw_hrpwmcal.h"
#include "cpu.h"
#include "debug.h"
#include "epwm.h"

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setMEPEdgeSelect(),
//! HRPWM_setMEPControlMode(), HRPWM_setCounterCompareShadowLoadEvent()
//! as the \e channel parameter.
//
//*****************************************************************************
typedef enum
{
    HRPWM_CHANNEL_A = 0, //!< HRPWM A
    HRPWM_CHANNEL_B = 8  //!< HRPWM B
} HRPWM_Channel;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setMEPEdgeSelect() as the \e mepEdgeMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! HRPWM is disabled
    HRPWM_MEP_CTRL_DISABLE = 0,
    //! MEP controls rising edge
    HRPWM_MEP_CTRL_RISING_EDGE = 1,
    //! MEP controls falling edge
    HRPWM_MEP_CTRL_FALLING_EDGE = 2,
    //! MEP controls both rising and falling edge
    HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE = 3
} HRPWM_MEPEdgeMode;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setHRMEPCtrlMode() as the \e
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! CMPAHR/CMPBHR or TBPRDHR controls MEP edge
    HRPWM_MEP_DUTY_PERIOD_CTRL = 0,
    //! TBPHSHR controls MEP edge
    HRPWM_MEP_PHASE_CTRL = 1
} HRPWM_MEPCtrlMode;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setCounterCompareShadowLoadEvent(),
//! HRPWM_setRisingEdgeDelayLoadMode() and HRPWM_setFallingEdgeDelayLoadMode
//! as the \e loadEvent parameter.
//
//*****************************************************************************
typedef enum
{
    //! load when counter equals zero
    HRPWM_LOAD_ON_CNTR_ZERO = 0,
    //! load when counter equals period
    HRPWM_LOAD_ON_CNTR_PERIOD = 1,
    //! load when counter equals zero or period
    HRPWM_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! load on translator event CMPA/B-3
    HRPWM_LOAD_ON_CMPx_EQ = 3,
} HRPWM_LoadMode;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setChannelBOutputPath() as the \e
//! outputOnB parameter.
//
//*****************************************************************************
typedef enum
{
    HRPWM_OUTPUT_ON_B_NORMAL = 0, //!< ePWMxB output is normal.
    HRPWM_OUTPUT_ON_B_INV_A  = 1  //!< ePWMxB output is inverted
                                  //!< version of ePWMxA signal
} HRPWM_ChannelBOutput;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setSyncPulseSource() as the \e
//! syncPulseSource parameter.
//
//*****************************************************************************
typedef enum
{
    //! Counter equals Period
    HRPWM_PWMSYNC_SOURCE_PERIOD = 0,
    //! Counter equals zero
    HRPWM_PWMSYNC_SOURCE_ZERO = 1,
    //! Counter equals COMPC when counting up
    HRPWM_PWMSYNC_SOURCE_COMPC_UP = 4,
    //! Counter equals COMPC when counting down
    HRPWM_PWMSYNC_SOURCE_COMPC_DOWN = 5,
    //! Counter equals COMPD when counting up
    HRPWM_PWMSYNC_SOURCE_COMPD_UP = 6,
    //! Counter equals COMPD when counting down
    HRPWM_PWMSYNC_SOURCE_COMPD_DOWN = 7
} HRPWM_SyncPulseSource;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setCounterCompareValue() as the \e
//! compModule parameter.
//
//*****************************************************************************
typedef enum
{
    HRPWM_COUNTER_COMPARE_A = 0, //!< counter compare A
    HRPWM_COUNTER_COMPARE_B = 4  //!< counter compare B
} HRPWM_CounterCompareModule;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setDeadbandMEPEdgeSelect() as the \e
//! mepDBEdge.
//
//*****************************************************************************
typedef enum
{
    //! HRPWM is disabled
    HRPWM_DB_MEP_CTRL_DISABLE = 0,
    //! MEP controls Rising Edge Delay
    HRPWM_DB_MEP_CTRL_RED = 1,
    //! MEP controls Falling Edge Delay
    HRPWM_DB_MEP_CTRL_FED = 2,
    //! MEP controls both Falling and Rising edge delay
    HRPWM_DB_MEP_CTRL_RED_FED = 3
} HRPWM_MEPDeadBandEdgeMode;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_lockRegisters() as the \e registerGroup
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HRPWM_REGISTER_GROUP_HRPWM = 0x1,           //!< HRPWM register group
    HRPWM_REGISTER_GROUP_GLOBAL_LOAD = 0x2,     //!< Global load register group
    HRPWM_REGISTER_GROUP_TRIP_ZONE = 0x4,       //!< Trip zone register group
    HRPWM_REGISTER_GROUP_TRIP_ZONE_CLEAR = 0x8, //!< Trip zone clear group
    HRPWM_REGISTER_GROUP_DIGITAL_COMPARE = 0x10 //!< Digital compare group
} HRPWM_LockRegisterGroup;

//*****************************************************************************
//
// Functions APIs shared with ePWM module
//
//*****************************************************************************

//
// Time Base Sub Module related APIs
//
#define HRPWM_setTimeBaseCounter                 EPWM_setTimeBaseCounter
#define HRPWM_setCountModeAfterSync              EPWM_setCountModeAfterSync
#define HRPWM_setClockPrescaler                  EPWM_setClockPrescaler
#define HRPWM_swForceSyncPulse                   EPWM_forceSyncPulse
#define HRPWM_setSyncOutPulseMode                EPWM_setSyncOutPulseMode
#define HRPWM_setPeriodLoadMode                  EPWM_setPeriodLoadMode
#define HRPWM_setTimeBaseCounterMode             EPWM_setTimeBaseCounterMode
#define HRPWM_selectPeriodLoadEvent              EPWM_selectPeriodLoadEvent
#define HRPWM_enableOneShotSync                  EPWM_enableOneShotSync
#define HRPWM_disableOneShotSync                 EPWM_disableOneShotSync
#define HRPWM_startOneShotSync                   EPWM_startOneShotSync
#define HRPWM_getTimeBaseCounterOverflowStatus                                \
                                          EPWM_getTimeBaseCounterOverflowStatus
#define HRPWM_clearTimeBaseCounterOverflowEvent                               \
                                         EPWM_clearTimeBaseCounterOverflowEvent
#define HRPWM_getSyncStatus                      EPWM_getSyncStatus
#define HRPWM_clearSyncEvent                     EPWM_clearSyncEvent
#define HRPWM_getTimeBaseCounterDirection     EPWM_getTimeBaseCounterDirection
#define HRPWM_setupEPWMLinks                     EPWM_setupEPWMLinks
#define HRPWM_setCounterCompareShadowLoadMode                                 \
                                           EPWM_setCounterCompareShadowLoadMode
#define HRPWM_disableCounterCompareShadowLoadMode                             \
                                       EPWM_disableCounterCompareShadowLoadMode
#define HRPWM_getCounterCompareShadowStatus                                   \
                                            EPWM_getCounterCompareShadowStatus

//
// Action Qualifier module related APIs
//
#define HRPWM_setActionQualifierShadowLoadMode                                \
                                       EPWM_setActionQualifierShadowLoadMode
#define HRPWM_disableActionQualifierShadowLoadMode                            \
                                      EPWM_disableActionQualifierShadowLoadMode
#define HRPWM_setActionQualifierT1TriggerSource                               \
                                        EPWM_setActionQualifierT1TriggerSource
#define HRPWM_setActionQualifierT2TriggerSource                               \
                                        EPWM_setActionQualifierT2TriggerSource
#define HRPWM_setActionQualifierAction           EPWM_setActionQualifierAction
#define HRPWM_setActionQualifierContSWForceShadowMode                         \
                                  EPWM_setActionQualifierContSWForceShadowMode
#define HRPWM_setActionQualifierContSWForceAction                             \
                                  EPWM_setActionQualifierContSWForceAction
/* HRPWM_setActionQualifierSwAction is kept for compatibility,
use HRPWM_setActionQualifierSWAction*/
#define HRPWM_setActionQualifierSwAction        EPWM_setActionQualifierSwAction
#define HRPWM_setActionQualifierSWAction        EPWM_setActionQualifierSWAction
/* HRPWM_forceActionQualifierSwAction  is kept for compatibility,
use HRPWM_forceActionQualifierSWAction*/
#define HRPWM_forceActionQualifierSwAction    EPWM_forceActionQualifierSwAction
#define HRPWM_forceActionQualifierSWAction    EPWM_forceActionQualifierSWAction
//
// Dead Band Module related APIs
//
#define HRPWM_setDeadBandOutputSwapMode          EPWM_setDeadBandOutputSwapMode
#define HRPWM_setDeadBandDelayMode               EPWM_setDeadBandDelayMode
#define HRPWM_setDeadBandDelayPolarity           EPWM_setDeadBandDelayPolarity
#define HRPWM_setRisingEdgeDeadBandDelayInput                                 \
                                         EPWM_setRisingEdgeDeadBandDelayInput
#define HRPWM_setFallingEdgeDeadBandDelayInput                                \
                                         EPWM_setFallingEdgeDeadBandDelayInput
#define HRPWM_setDeadBandControlShadowLoadMode                                \
                                         EPWM_setDeadBandControlShadowLoadMode
#define HRPWM_disableDeadBandControlShadowLoadMode                            \
                                      EPWM_disableDeadBandControlShadowLoadMode
#define HRPWM_setRisingEdgeDelayCountShadowLoadMode                           \
                                   EPWM_setRisingEdgeDelayCountShadowLoadMode
#define HRPWM_disableRisingEdgeDelayCountShadowLoadMode                       \
                                 EPWM_disableRisingEdgeDelayCountShadowLoadMode
#define HRPWM_setFallingEdgeDelayCountShadowLoadMode                          \
                                   EPWM_setFallingEdgeDelayCountShadowLoadMode
#define HRPWM_disableFallingEdgeDelayCountShadowLoadMode                      \
                                EPWM_disableFallingEdgeDelayCountShadowLoadMode
#define HRPWM_setDeadBandCounterClock            EPWM_setDeadBandCounterClock
#define HRPWM_setRisingEdgeDelayCount            EPWM_setRisingEdgeDelayCount
#define HRPWM_setFallingEdgeDelayCount           EPWM_setFallingEdgeDelayCount

//
// Chopper module related APIs
//
#define HRPWM_enableChopper                      EPWM_enableChopper
#define HRPWM_disableChopper                     EPWM_disableChopper
#define HRPWM_setChopperDutyCycle                EPWM_setChopperDutyCycle
#define HRPWM_setChopperFreq                     EPWM_setChopperFreq
#define HRPWM_setChopperFirstPulseWidt           EPWM_setChopperFirstPulseWidth

//
// Trip Zone module related APIs
//
#define HRPWM_enableTripZoneSignals              EPWM_enableTripZoneSignals
#define HRPWM_disableTripZoneSignals             EPWM_disableTripZoneSignals
#define HRPWM_setTripZoneDigitalCompareEventCondition                         \
                                   EPWM_setTripZoneDigitalCompareEventCondition
#define HRPWM_enableTripZoneAdvAction             EPWM_enableTripZoneAdvAction
#define HRPWM_disableTripZoneAdvAction            EPWM_disableTripZoneAdvAction
#define HRPWM_setTripZoneAction                   EPWM_setTripZoneAction
#define HRPWM_setTripZoneAdvAction                EPWM_setTripZoneAdvAction
#define HRPWM_setTripZoneAdvDigitalCompareActionA                             \
                                   EPWM_setTripZoneAdvDigitalCompareActionA
#define HRPWM_setTripZoneAdvDigitalCompareActionB                             \
                                   EPWM_setTripZoneAdvDigitalCompareActionB
#define HRPWM_enableTripZoneInterrupt           EPWM_enableTripZoneInterrupt
#define HRPWM_disableTripZoneInterrupt          EPWM_disableTripZoneInterrupt

//
// HRPWM_getTripZoneInterruptStatus API define is obsolete please use
// HRPWM_getTripZoneFlagStatus going forward.
//
#define HRPWM_getTripZoneInterruptStatus        EPWM_getTripZoneFlagStatus
#define HRPWM_getTripZoneFlagStatus             EPWM_getTripZoneFlagStatus

//
// HRPWM_getCycleByCycleTripZoneInterruptStatus API define is obsolete
// please use HRPWM_getCycleByCycleTripZoneFlagStatus going forward.
//
#define HRPWM_getCycleByCycleTripZoneInterruptStatus                          \
                                   HRPWM_getCycleByCycleTripZoneFlagStatus
#define HRPWM_getCycleByCycleTripZoneFlagStatus                               \
                                   EPWM_getCycleByCycleTripZoneFlagStatus

//
// HRPWM_getOneShotTripZoneInterruptStatus is obsolete please use
// HRPWM_getOneShotTripZoneFlagStatus going forward.
//
#define HRPWM_getOneShotTripZoneInterruptStatus                               \
                                   HRPWM_getOneShotTripZoneFlagStatus
#define HRPWM_getOneShotTripZoneFlagStatus                                    \
                                   EPWM_getOneShotTripZoneFlagStatus
#define HRPWM_selectCycleByCycleTripZoneClearEvent                            \
                                   EPWM_selectCycleByCycleTripZoneClearEvent

//
// HRPWM_clearTripZoneInterruptFlag is obsolete please use
// HRPWM_clearTripZoneFlag going forward.
//
#define HRPWM_clearTripZoneInterruptFlag        HRPWM_clearTripZoneFlag
#define HRPWM_clearTripZoneFlag                 EPWM_clearTripZoneFlag

//
// HRPWM_clearCycleByCycleTripZoneInterruptFlag is obsolete please use
// HRPWM_clearCycleByCycleTripZoneFlag going forward.
//
#define HRPWM_clearCycleByCycleTripZoneInterruptFlag                          \
                                   HRPWM_clearCycleByCycleTripZoneFlag
#define HRPWM_clearCycleByCycleTripZoneFlag                                   \
                                   EPWM_clearCycleByCycleTripZoneFlag

//
// HRPWM_clearOneShotTripZoneInterruptFlag is obsolete please use
// HRPWM_clearOneShotTripZoneFlag going forward.
//
#define HRPWM_clearOneShotTripZoneInterruptFlag                               \
                                   HRPWM_clearOneShotTripZoneFlag
#define HRPWM_clearOneShotTripZoneFlag                                        \
                                   EPWM_clearOneShotTripZoneFlag
#define HRPWM_forceTripZoneEvent                  EPWM_forceTripZoneEvent

//
// Event Trigger related APIs
//
#define HRPWM_enableInterrupt                     EPWM_enableInterrupt
#define HRPWM_disableInterrupt                    EPWM_disableInterrupt
#define HRPWM_setInterruptSource                  EPWM_setInterruptSource
#define HRPWM_setInterruptEventCount              EPWM_setInterruptEventCount
#define HRPWM_getEventTriggerInterruptStatus                                  \
                                           EPWM_getEventTriggerInterruptStatus
#define HRPWM_clearEventTriggerInterruptFlag                                  \
                                           EPWM_clearEventTriggerInterruptFlag
#define HRPWM_enableInterruptEventCountInit                                   \
                                           EPWM_enableInterruptEventCountInit
#define HRPWM_disableInterruptEventCountInit                                  \
                                            EPWM_disableInterruptEventCountInit
#define HRPWM_forceInterruptEventCountInit                                    \
                                              EPWM_forceInterruptEventCountInit
#define HRPWM_setInterruptEventCountInitValue                                 \
                                           EPWM_setInterruptEventCountInitValue
#define HRPWM_getInterruptEventCount            EPWM_getInterruptEventCount
#define HRPWM_forceEventTriggerInterrupt        EPWM_forceEventTriggerInterrupt

//
// ADC SOC configuration related APIs
//
#define HRPWM_enableADCTrigger                  EPWM_enableADCTrigger
#define HRPWM_disableADCTrigger                 EPWM_disableADCTrigger
#define HRPWM_setADCTriggerSource               EPWM_setADCTriggerSource
#define HRPWM_setADCTriggerEventPrescale        EPWM_setADCTriggerEventPrescale
#define HRPWM_getADCTriggerFlagStatus           EPWM_getADCTriggerFlagStatus
#define HRPWM_clearADCTriggerFlag               EPWM_clearADCTriggerFlag
#define HRPWM_enableADCTriggerEventCountInit                                  \
                                          EPWM_enableADCTriggerEventCountInit
#define HRPWM_disableADCTriggerEventCountInit                                 \
                                          EPWM_disableADCTriggerEventCountInit
#define HRPWM_forceADCTriggerEventCountInit                                   \
                                          EPWM_forceADCTriggerEventCountInit
#define HRPWM_setADCTriggerEventCountInitValue                                \
                                         EPWM_setADCTriggerEventCountInitValue
#define HRPWM_getADCTriggerEventCount             EPWM_getADCTriggerEventCount
#define HRPWM_forceADCTrigger                     EPWM_forceADCTrigger

//
// Digital Compare Module related APIs
//
#define HRPWM_selectDigitalCompareTripInput                                   \
                                            EPWM_selectDigitalCompareTripInput
#define HRPWM_enableDigitalCompareBlankingWindow                              \
                                   EPWM_enableDigitalCompareBlankingWindow
#define HRPWM_disableDigitalCompareBlankingWindow                             \
                                   EPWM_disableDigitalCompareBlankingWindow
#define HRPWM_enableDigitalCompareWindowInverseMode                           \
                                   EPWM_enableDigitalCompareWindowInverseMode
#define HRPWM_disableDigitalCompareWindowInverseMode                          \
                                   EPWM_disableDigitalCompareWindowInverseMode
#define HRPWM_setDigitalCompareBlankingEvent                                  \
                                        EPWM_setDigitalCompareBlankingEvent
#define HRPWM_setDigitalCompareFilterInput                                    \
                                        EPWM_setDigitalCompareFilterInput
#define HRPWM_setDigitalCompareWindowOffset                                   \
                                        EPWM_setDigitalCompareWindowOffset
#define HRPWM_setDigitalCompareWindowLength                                   \
                                         EPWM_setDigitalCompareWindowLength
#define HRPWM_getDigitalCompareBlankingWindowOffsetCount                      \
                               EPWM_getDigitalCompareBlankingWindowOffsetCount
#define HRPWM_getDigitalCompareBlankingWindowLengthCount                      \
                               EPWM_getDigitalCompareBlankingWindowLengthCount
#define HRPWM_setDigitalCompareEventSource                                    \
                                            EPWM_setDigitalCompareEventSource
#define HRPWM_setDigitalCompareEventSyncMode                                  \
                                           EPWM_setDigitalCompareEventSyncMode
#define HRPWM_enableDigitalCompareADCTrigger                                  \
                                           EPWM_enableDigitalCompareADCTrigger
#define HRPWM_disableDigitalCompareADCTrigger                                 \
                                          EPWM_disableDigitalCompareADCTrigger
#define HRPWM_enableDigitalCompareSyncEvent                                   \
                                            EPWM_enableDigitalCompareSyncEvent
#define HRPWM_disableDigitalCompareSyncEvent                                  \
                                           EPWM_disableDigitalCompareSyncEvent
#define HRPWM_enableDigitalCompareCounterCapture                              \
                                EPWM_enableDigitalCompareCounterCapture
#define HRPWM_disableDigitalCompareCounterCapture                             \
                                EPWM_disableDigitalCompareCounterCapture
#define HRPWM_setDigitalCompareCounterShadowMode                              \
                                EPWM_setDigitalCompareCounterShadowMode
#define HRPWM_getDigitalCompareCaptureStatus                                  \
                                 EPWM_getDigitalCompareCaptureStatus
#define HRPWM_getDigitalCompareCaptureCount                                   \
                                 EPWM_getDigitalCompareCaptureCount
#define HRPWM_enableDigitalCompareTripCombinationInput                        \
                                EPWM_enableDigitalCompareTripCombinationInput
#define HRPWM_disableDigitalCompareTripCombinationInput                       \
                                EPWM_disableDigitalCompareTripCombinationInput

//
// Valley switching related APIs
//
#define HRPWM_enableValleyCapture             EPWM_enableValleyCapture
#define HRPWM_disableValleyCapture            EPWM_disableValleyCapture
#define HRPWM_startValleyCapture              EPWM_startValleyCapture
#define HRPWM_setValleyTriggerSource          EPWM_setValleyTriggerSource
#define HRPWM_setValleyTriggerEdgeCounts      EPWM_setValleyTriggerEdgeCounts
#define HRPWM_enableValleyHWDelay             EPWM_enableValleyHWDelay
#define HRPWM_disableValleyHWDelay            EPWM_disableValleyHWDelay
#define HRPWM_setValleySWDelayValue           EPWM_setValleySWDelayValue
#define HRPWM_setValleyDelayDivider           EPWM_setValleyDelayDivider
#define HRPWM_getValleyEdgeStatus             EPWM_getValleyEdgeStatus
#define HRPWM_getValleyCount                  EPWM_getValleyCount
#define HRPWM_getValleyHWDelay                EPWM_getValleyHWDelay

//
// Global Load feature related APIs
//
#define HRPWM_enableGlobalLoad                EPWM_enableGlobalLoad
#define HRPWM_disableGlobalLoad               EPWM_disableGlobalLoad
#define HRPWM_setGlobalLoadTrigger            EPWM_setGlobalLoadTrigger
#define HRPWM_setGlobalLoadEventPrescale      EPWM_setGlobalLoadEventPrescale
#define HRPWM_getGlobalLoadEventCount         EPWM_getGlobalLoadEventCount
#define HRPWM_disableGlobalLoadOneShotMode    EPWM_disableGlobalLoadOneShotMode
#define HRPWM_enableGlobalLoadOneShotMode     EPWM_enableGlobalLoadOneShotMode
#define HRPWM_setGlobalLoadOneShotLatch       EPWM_setGlobalLoadOneShotLatch
#define HRPWM_forceGlobalLoadOneShotEvent     EPWM_forceGlobalLoadOneShotEvent
#define HRPWM_enableGlobalLoadRegisters       EPWM_enableGlobalLoadRegisters
#define HRPWM_disableGlobalLoadRegisters      EPWM_disableGlobalLoadRegisters
#define HRPWM_setEmulationMode                EPWM_setEmulationMode

//*****************************************************************************
//
// Prototypes for the API.
//
//*****************************************************************************

//*****************************************************************************
//
//! \internal
//! Checks HRPWM base address.
//!
//! \param base specifies the HRPWM module base address.
//!
//! This function determines if an HRPWM module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
__attribute__((always_inline))
static inline bool HRPWM_isBaseValid(uint32_t base)
{
    return(
           ((base & BASE_ADDR_MASK) == EPWM1_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM2_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM3_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM4_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM5_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM6_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM7_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM8_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM9_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM10_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM11_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM12_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM13_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM14_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM15_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM16_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM17_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == EPWM18_BASE_FRAME(0U))
          );
}
//*****************************************************************************
//
//! \internal
//! Checks HRPWMCAL base address.
//!
//! \param base specifies the HRPWMCAL module base address.
//!
//! This function determines if an HRPWMCAL module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool HRPWMCAL_isBaseValid(uint32_t base)
{
    return(
           ((base & BASE_ADDR_MASK) == HRPWMCAL1_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == HRPWMCAL2_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == HRPWMCAL3_BASE_FRAME(0U))
          );
}
#endif
//*****************************************************************************
//
//! Sets the consolidated phase shift value in high resolution mode.
//!
//! \param base is the base address of the EPWM module.
//! \param phaseCount is the consolidated phase shift count value.
//!
//! This function sets the consolidated phase shift value, that is, both TBPHS
//! and TBPHSHR values are configured together.
//!
//! Call EPWM_enablePhaseShiftLoad & HRPWM_enableHRPhaseShiftLoad() functions
//! to enable loading of the phaseCount in high resolution mode.
//!
//! \b Note: phaseCount is a 24-bit value.
//! \b Note: For configuring TBPHS = 0x3C, TBPHSHR = 0x2;
//!          phaseCount = 0x3C02
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setPhaseShift(uint32_t base, uint32_t phaseCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(phaseCount < 0x1000000U);

    //
    // Write to TBPHS:TBPHSHR bits
    //
    HWREG(base +  EPWM_O_TBPHS) = phaseCount << 8U;
}

//*****************************************************************************
//
//! Sets only the high resolution phase shift value.
//!
//! \param base is the base address of the EPWM module.
//! \param hrPhaseCount is the high resolution phase shift count value.
//!
//! This function sets only the high resolution phase shift(TBPHSHR) value.
//! Call the HRPWM_enableHRPhaseShiftLoad() function to enable loading of
//! the hrPhaseCount.
//!
//! \b Note: hrPhaseCount is an 8-bit value.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setHiResPhaseShiftOnly(uint32_t base, uint16_t hrPhaseCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrPhaseCount < 256U);

    //
    // Write to TBPHSHR bits
    //
    HWREGH(base + EPWM_O_TBPHS) = hrPhaseCount << 8U;
}

//*****************************************************************************
//
//! Sets the consolidated period of time base counter used in HR mode.
//!
//! \param base is the base address of the EPWM module.
//! \param periodCount is the consolidated period count value.
//!
//! This function sets the consolidated period of time base counter value
//! (TBPRD:TBPRDHR) required in high resolution mode.
//!
//! User should map the desired period or frequency of the waveform into
//! the correct periodCount.
//!
//! \b Note: periodCount is a 24 bit value.
//! \b Note: For configuring TBPRD = 0x3C, TBPRDHR = 0xA;
//!          periodCount = 0x3C0A
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setTimeBasePeriod(uint32_t base, uint32_t periodCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(periodCount < 0x1000000U);

    //
    // Write to TBPRD:TBPRDHR bits
    //
    HWREG(base + EPWM_O_TBPRDHR) = periodCount << 8U;
}

//*****************************************************************************
//
//! Sets only the high resolution time base counter.
//!
//! \param base is the base address of the EPWM module.
//! \param hrPeriodCount is the high resolution period count value.
//!
//! This function sets only the high resolution time base counter(TBPRDHR)
//! value.
//!
//! User should map the desired period or frequency of the waveform into
//! the correct hrPeriodCount.
//!
//! \b Note: hrPeriodCount is an 8-bit value.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setHiResTimeBasePeriodOnly(uint32_t base, uint16_t hrPeriodCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrPeriodCount < 256U);

    //
    // Write to TBPRDHR bits
    //
    HWREGH(base + EPWM_O_TBPRDHR) = hrPeriodCount << 8U;
}

//*****************************************************************************
//
//! Gets the consolidated time base period count used in HR mode
//!
//! \param base is the base address of the EPWM module.
//!
//! This function gets the consolidated time base period(TBPRD:TBPRDHR) value
//! used in high resolution mode.
//!
//! \return The consolidated time base period count value.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
HRPWM_getTimeBasePeriod(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Read from TBPRD:TBPRDHR bit
    //
    return(HWREG(base + EPWM_O_TBPRDHR) >> 8U);
}

//*****************************************************************************
//
//! Gets the only the high resolution time base period count.
//!
//! \param base is the base address of the EPWM module.
//!
//! This function gets only the high resolution time base period(TBPRDHR) value.
//!
//! \return The high resolution time base period count value.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint16_t
HRPWM_getHiResTimeBasePeriodOnly(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Read from TBPRDHR bit
    //
    return(HWREGH(base + EPWM_O_TBPRDHR) >> 8U);
}

//*****************************************************************************
//
//! Sets the high resolution edge controlled by MEP (Micro Edge Positioner).
//!
//! \param base is the base address of the EPWM module.
//! \param channel is high resolution period module.
//! \param mepEdgeMode edge of the PWM that is controlled by MEP (Micro Edge
//!        Positioner).
//!
//! This function sets the edge of the PWM that is controlled by MEP (Micro
//! Edge Positioner). Valid values for the parameters are:
//!  - channel
//!      - HRPWM_CHANNEL_A  - HRPWM A
//!      - HRPWM_CHANNEL_B  - HRPWM B
//!  - mepEdgeMode
//!      - HRPWM_MEP_CTRL_DISABLE                 - HRPWM is disabled
//!      - HRPWM_MEP_CTRL_RISING_EDGE             - MEP (Micro Edge Positioner)
//!                                                 controls rising edge.
//!      - HRPWM_MEP_CTRL_FALLING_EDGE            - MEP (Micro Edge Positioner)
//!                                                 controls falling edge.
//!      - HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE - MEP (Micro Edge Positioner)
//!                                                 controls both edges.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setMEPEdgeSelect(uint32_t base, HRPWM_Channel channel,
                       HRPWM_MEPEdgeMode mepEdgeMode)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the edge mode
    //

    HWREGH(base + EPWM_O_HRCNFG) =
             ((HWREGH(base + EPWM_O_HRCNFG) & ~(0x3U << (uint16_t)channel )) |
              ((uint16_t)mepEdgeMode << (uint16_t)channel));

}

//*****************************************************************************
//
//! Sets the MEP (Micro Edge Positioner) control mode.
//!
//! \param base is the base address of the EPWM module.
//! \param channel is high resolution period module.
//! \param mepCtrlMode is the MEP (Micro Edge Positioner) control mode.
//!
//! This function sets the mode (register type) the MEP (Micro Edge Positioner)
//! will control. Valid values for the parameters are:
//!  - channel
//!      - HRPWM_CHANNEL_A  - HRPWM A
//!      - HRPWM_CHANNEL_B  - HRPWM B
//!  - mepCtrlMode
//!      - HRPWM_MEP_DUTY_PERIOD_CTRL      - MEP (Micro Edge Positioner) is
//!                                          controlled by value of CMPAHR/
//!                                          CMPBHR(depending on the value of
//!                                          channel) or TBPRDHR.
//!      - HRPWM_MEP_PHASE_CTRL            - MEP (Micro Edge Positioner) is
//!                                          controlled by TBPHSHR.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setMEPControlMode(uint32_t base, HRPWM_Channel channel,
                        HRPWM_MEPCtrlMode mepCtrlMode)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the MEP control
    //

    HWREGH(base + EPWM_O_HRCNFG) =
       ((HWREGH(base + EPWM_O_HRCNFG) & ~(0x1U << ((uint16_t)channel + 2U))) |
         ((uint16_t)mepCtrlMode << ((uint16_t)channel + 2U)));

}

//*****************************************************************************
//
//! Sets the high resolution comparator load mode.
//!
//! \param base is the base address of the EPWM module.
//! \param channel is high resolution period module.
//! \param loadEvent is the MEP (Micro Edge Positioner) control mode.
//!
//! This function sets the shadow load mode of the high resolution comparator.
//! The function sets the COMPA or COMPB register depending on the channel
//! variable.
//! Valid values for the parameters are:
//!  - channel
//!      - HRPWM_CHANNEL_A  - HRPWM A
//!      - HRPWM_CHANNEL_B  - HRPWM B
//!  - loadEvent
//!      - HRPWM_LOAD_ON_CNTR_ZERO         - load when counter equals zero
//!      - HRPWM_LOAD_ON_CNTR_PERIOD       - load when counter equals period
//!      - HRPWM_LOAD_ON_CNTR_ZERO_PERIOD  - load when counter equals zero or
//!                                          period
//!      - HRPWM_LOAD_ON_CMPx_EQ           - load on translator event CMPA/B-3
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setCounterCompareShadowLoadEvent(uint32_t base, HRPWM_Channel channel,
                                       HRPWM_LoadMode loadEvent)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the CMPAHR or CMPBHR load mode
    //

    HWREGH(base + EPWM_O_HRCNFG) =
       ((HWREGH(base + EPWM_O_HRCNFG) & ~(0x3U << ((uint16_t)channel + 3U))) |
         ((uint16_t)loadEvent << ((uint16_t)channel + 3U)));

}

//*****************************************************************************
//
//! Sets the high resolution output swap mode.
//!
//! \param base is the base address of the EPWM module.
//! \param enableOutputSwap is the output swap flag.
//!
//! This function sets the HRPWM output swap mode. If enableOutputSwap is true,
//! ePWMxA signal appears on ePWMxB output and ePWMxB signal appears on ePWMxA
//! output. If it is false ePWMxA and ePWMxB outputs are unchanged.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setOutputSwapMode(uint32_t base, bool enableOutputSwap)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set output swap mode
    //

    if(enableOutputSwap)
    {
        HWREGH(base + EPWM_O_HRCNFG) |= EPWM_HRCNFG_SWAPAB;
    }
    else
    {
        HWREGH(base + EPWM_O_HRCNFG) &= ~EPWM_HRCNFG_SWAPAB;
    }

}

//*****************************************************************************
//
//! Sets the high resolution output on ePWMxB
//!
//! \param base is the base address of the EPWM module.
//! \param outputOnB is the output signal on ePWMxB.
//!
//! This function sets the HRPWM output signal on ePWMxB. If outputOnB is
//! HRPWM_OUTPUT_ON_B_INV_A, ePWMxB output is an inverted version of
//! ePWMxA. If outputOnB is HRPWM_OUTPUT_ON_B_NORMAL, ePWMxB output is
//! ePWMxB.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setChannelBOutputPath(uint32_t base, HRPWM_ChannelBOutput outputOnB)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the output on ePWM B
    //

    HWREGH(base + EPWM_O_HRCNFG) =
            ((HWREGH(base + EPWM_O_HRCNFG) & ~(EPWM_HRCNFG_SELOUTB)) |
             ((uint16_t)outputOnB << 5U));

}

//*****************************************************************************
//
//! Enables MEP (Micro Edge Positioner) automatic scale mode.
//!
//! \param base is the base address of the EPWM module.
//!
//! This function enables the MEP (Micro Edge Positioner) to automatically
//! scale HRMSTEP.
//!
//! The SFO library will calculate required MEP steps per coarse steps and
//! feed it to HRMSTEP register. The MEP calibration module will use the value
//! in HRMSTEP to determine appropriate number of MEP steps represented by
//! fractional duty cycle.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_enableAutoConversion(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Enable MEP automatic scale
    //

    HWREGH(base + EPWM_O_HRCNFG) |= EPWM_HRCNFG_AUTOCONV;

}

//*****************************************************************************
//
//! Disables MEP automatic scale mode.
//!
//! \param base is the base address of the EPWM module.
//!
//! This function disables the MEP (Micro Edge Positioner) from automatically
//! scaling HRMSTEP.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_disableAutoConversion(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Disable MEP automatic scale
    //

    HWREGH(base + EPWM_O_HRCNFG) &= ~EPWM_HRCNFG_AUTOCONV;

}

//*****************************************************************************
//
//! Enable high resolution period feature.
//!
//! \param base is the base address of the EPWM module.
//!
//! This function enables the high resolution period feature.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_enablePeriodControl(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set HRPE bit
    //

    HWREGH(base + EPWM_O_HRPCTL) |= EPWM_HRPCTL_HRPE;

}

//*****************************************************************************
//
//! Disable high resolution period feature.
//!
//! \param base is the base address of the EPWM module.
//!
//! This function disables the high resolution period feature.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_disablePeriodControl(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Clear HRPE bit
    //

    HWREGH(base + EPWM_O_HRPCTL) &= ~EPWM_HRPCTL_HRPE;

}

//*****************************************************************************
//
//! Enable high resolution phase load
//!
//! \param base is the base address of the EPWM module.
//!
//! This function enables loading of high resolution phase shift value which is
//! set by the function HRPWM_setPhaseShift().
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_enablePhaseShiftLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set TBPHSHRLOADE bit
    //

    HWREGH(base + EPWM_O_HRPCTL) |= EPWM_HRPCTL_TBPHSHRLOADE;

}

//*****************************************************************************
//
//! Disable high resolution phase load
//!
//! \param base is the base address of the EPWM module.
//!
//! This function disables loading of high resolution phase shift value.
//!
//! \return
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_disablePhaseShiftLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Clear TBPHSHRLOADE bit
    //

    HWREGH(base + EPWM_O_HRPCTL) &= ~EPWM_HRPCTL_TBPHSHRLOADE;

}

//*****************************************************************************
//
//! Set high resolution PWMSYNC source.
//!
//! \param base is the base address of the EPWM module.
//! \param syncPulseSource is the PWMSYNC source.
//!
//! This function sets the high resolution PWMSYNC pulse source.
//! Valid values for syncPulseSource are:
//!  - HRPWM_PWMSYNC_SOURCE_PERIOD      - Counter equals Period.
//!  - HRPWM_PWMSYNC_SOURCE_ZERO        - Counter equals zero.
//!  - HRPWM_PWMSYNC_SOURCE_COMPC_UP    - Counter equals COMPC when
//!                                       counting up.
//!  - HRPWM_PWMSYNC_SOURCE_COMPC_DOWN  - Counter equals COMPC when
//!                                       counting down.
//!  - HRPWM_PWMSYNC_SOURCE_COMPD_UP    - Counter equals COMPD when
//!                                       counting up.
//!  - HRPWM_PWMSYNC_SOURCE_COMPD_DOWN  - Counter equals COMPD when
//!                                       counting down.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setSyncPulseSource(uint32_t base, HRPWM_SyncPulseSource syncPulseSource)
{
    //
    // Set the PWMSYNC source
    //


    //
    // Configuration for sync pulse source equal to HRPWM_PWMSYNC_SOURCE_PERIOD
    // or HRPWM_PWMSYNC_SOURCE_ZERO
    //
    if(syncPulseSource < HRPWM_PWMSYNC_SOURCE_COMPC_UP)
    {
        HWREGH(base + EPWM_O_HRPCTL) =
          ((HWREGH(base + EPWM_O_HRPCTL) &
          ~(EPWM_HRPCTL_PWMSYNCSELX_M | EPWM_HRPCTL_PWMSYNCSEL)) |
           ((uint16_t)syncPulseSource << 1U));
    }
    else
    {
        HWREGH(base + EPWM_O_HRPCTL) =
          ((HWREGH(base + EPWM_O_HRPCTL) & ~EPWM_HRPCTL_PWMSYNCSELX_M) |
           ((uint16_t)syncPulseSource << EPWM_HRPCTL_PWMSYNCSELX_S));
    }

}

//*****************************************************************************
//
//! Sets the Translator Remainder value.
//!
//! \param base is the base address of the EPWM module.
//! \param trremVal is the translator remainder value.
//!
//! This function sets the Translator Remainder value.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setTranslatorRemainder(uint32_t base, uint16_t trremVal)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(trremVal < 2048U);

    //
    // Set Translator Remainder value
    //

    HWREGH(base + EPWM_O_TRREM) = (trremVal & EPWM_TRREM_TRREM_M);

}

//*****************************************************************************
//
//! Sets the consolidated counter compare values in HR mode.
//!
//! \param base is the base address of the EPWM module.
//! \param compModule is the Counter Compare module.
//! \param compCount is the consolidated counter compare count value.
//!
//! This function sets the consolidated counter compare(CMPx:CMPxHR) value
//! required in high resolution mode for counter compare registers.
//! Valid values for compModule are:
//!  - HRPWM_COUNTER_COMPARE_A - counter compare A.
//!  - HRPWM_COUNTER_COMPARE_B - counter compare B.
//!
//! \b Note: compCount is a 24 bit value.
//! \b Note: For configuring CMPA = 0xB4, CMPAHR = 0x64; value of
//!          compCount = 0xB464
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setCounterCompareValue(uint32_t base,
                             HRPWM_CounterCompareModule compModule,
                             uint32_t compCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(compCount < 0x1000000U);

    //
    // Write to counter compare registers
    //
    if(compModule == HRPWM_COUNTER_COMPARE_A)
    {
        //
        // Write to CMPA:CMPAHR
        //
        HWREG(base + EPWM_O_CMPA) = compCount << 8U;
    }
    else
    {
        //
        // Write to CMPB:CMPBHR
        //
        HWREG(base + EPWM_O_CMPB) = compCount << 8U;
    }
}

//*****************************************************************************
//
//! Sets only the high resolution counter compare value.
//!
//! \param base is the base address of the EPWM module.
//! \param compModule is the Counter Compare module.
//! \param hrCompCount is the high resolution counter compare count value.
//!
//! This function sets the high resolution counter compare value(CMPxHR) for
//! counter compare registers.
//! Valid values for compModule are:
//!  - HRPWM_COUNTER_COMPARE_A - counter compare A.
//!  - HRPWM_COUNTER_COMPARE_B - counter compare B.
//!
//! \b Note: hrCompCount is an 8-bit value.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setHiResCounterCompareValueOnly(uint32_t base,
                                      HRPWM_CounterCompareModule compModule,
                                      uint16_t hrCompCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrCompCount < 256U);

    //
    // Write to the high resolution counter compare registers
    //
    if(compModule == HRPWM_COUNTER_COMPARE_A)
    {
        //
        // Write to CMPAHR
        //
        HWREGH(base + EPWM_O_CMPA) = hrCompCount << 8U;
    }
    else
    {
        //
        // Write to CMPBHR
        //
        HWREGH(base + EPWM_O_CMPB) = hrCompCount << 8U;
    }
}

//*****************************************************************************
//
//! Gets the consolidated counter compare values.
//!
//! \param base is the base address of the EPWM module.
//! \param compModule is the Counter Compare module value.
//!
//! This function gets the consolidated counter compare(CMPx:CMPxHR) value
//! used in high resolution for the counter compare module specified.
//! Valid values for compModule are:
//!  - HRPWM_COUNTER_COMPARE_A - counter compare A.
//!  - HRPWM_COUNTER_COMPARE_B - counter compare B.
//!
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
HRPWM_getCounterCompareValue(uint32_t base,
                             HRPWM_CounterCompareModule compModule)
{
    uint32_t compCount;

    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Get counter compare value for selected module
    //
    if(compModule == HRPWM_COUNTER_COMPARE_A)
    {
        //
        // Read from CMPAHR
        //
        compCount = HWREG(base + EPWM_O_CMPA) >> 8U;
    }
    else
    {
        //
        // Read from CMPBHR
        //
        compCount = HWREG(base + EPWM_O_CMPB) >> 8U;
    }
    return(compCount);
}

//*****************************************************************************
//
//! Gets only the high resolution counter compare values.
//!
//! \param base is the base address of the EPWM module.
//! \param compModule is the Counter Compare module value.
//!
//! This function gets only the high resolution counter compare(CMPxHR) value
//! for the counter compare module specified.
//! Valid values for compModule are:
//!  - HRPWM_COUNTER_COMPARE_A - counter compare A.
//!  - HRPWM_COUNTER_COMPARE_B - counter compare B.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint16_t
HRPWM_getHiResCounterCompareValueOnly(uint32_t base,
                                      HRPWM_CounterCompareModule compModule)
{
    uint16_t hrCompCount;

    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Get counter compare value for selected module
    //
    if(compModule == HRPWM_COUNTER_COMPARE_A)
    {
        //
        // Read from CMPAHR
        //
        hrCompCount = HWREGH(base + EPWM_O_CMPA) >> 8U;
    }
    else
    {
        //
        // Read from CMPBHR
        //
        hrCompCount = HWREGH(base + EPWM_O_CMPB) >> 8U;
    }
    return(hrCompCount);
}

//*****************************************************************************
//
//! Sets the consolidated RED count in high resolution mode.
//!
//! \param base is the base address of the EPWM module.
//! \param redCount is the high resolution RED count.
//!
//! This function sets the consolidated RED (Rising Edge Delay) count
//! (DBRED:DBREDHR) value used in high resolution mode. The value of
//! redCount should be less than 0x200000.
//!
//! \b Note: redCount is a 21 bit value.
//! \b Note: For configuring DBRED = 0x4, DBREDHR = 0x1; value of
//!          redCount = ((0x4 << 7) | 0x1) = 0x201
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setRisingEdgeDelay(uint32_t base, uint32_t redCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(redCount < 0x200000U);

    //
    // Set the consolidated RED (Rising Edge Delay) count
    //
    HWREG(base + EPWM_O_DBREDHR) = redCount << 9U;
}

//*****************************************************************************
//
//! Sets the high resolution RED count only.
//!
//! \param base is the base address of the EPWM module.
//! \param hrRedCount is the high resolution RED count.
//!
//! This function sets only the high resolution RED (Rising Edge Delay)
//! count(DBREDHR) value.
//! The value of hrRedCount should be less than 128.
//!
//! \b Note: hrRedCount is a 7-bit value.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setHiResRisingEdgeDelayOnly(uint32_t base, uint16_t hrRedCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrRedCount < 128U);

    //
    // Set the High Resolution RED (Rising Edge Delay) count only
    //
    HWREGH(base + EPWM_O_DBREDHR) = hrRedCount << 9U;
}

//*****************************************************************************
//
//! Sets the consolidated FED value in high resolution mode.
//!
//! \param base is the base address of the EPWM module.
//! \param fedCount is the high resolution FED count.
//!
//! This function sets the consolidated FED (Falling Edge Delay) count
//! (DBFED: DBFEDHR) value used in high resolution mode. The value of fedCount
//! should be less than 0x200000.
//!
//! \b Note: fedCount is a 21 bit value.
//! \b Note: For configuring DBFED = 0x4, DBFEDHR = 0x1; value of
//!          fedCount = ((0x4 << 7) | 0x1) = 0x201
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setFallingEdgeDelay(uint32_t base, uint32_t fedCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(fedCount < 0x200000U);

    //
    // Set the High Resolution FED (Falling Edge Delay) count
    //
    HWREG(base + EPWM_O_DBFEDHR) = fedCount << 9U;
}

//*****************************************************************************
//
//! Sets high resolution FED count only.
//!
//! \param base is the base address of the EPWM module.
//! \param hrFedCount is the high resolution FED count.
//!
//! This function sets only the high resolution FED (Falling Edge Delay) count
//! (DBFEDHR)value. The value of hrFedCount should be less than 128.
//!
//! \b Note: hrFedCount is a 7-bit value.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setHiResFallingEdgeDelayOnly(uint32_t base, uint16_t hrFedCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrFedCount < 128U);

    //
    // Set the high resolution FED (Falling Edge Delay) count
    //
    HWREGH(base + EPWM_O_DBFEDHR) = hrFedCount << 9U;
}

//*****************************************************************************
//
//! Set high resolution MEP (Micro Edge Positioner) step.
//!
//! \param base is the base address of the EPWM module.
//! \param mepCount is the high resolution MEP (Micro Edge Positioner) step
//!        count.
//!
//! This function sets the high resolution MEP (Micro Edge Positioner) step
//! count. The maximum value for the MEP count step is 255.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setMEPStep(uint32_t base, uint16_t mepCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWMCAL_isBaseValid(base));
    ASSERT(mepCount < 256U);

    //
    // Set HRPWM MEP count
    //

    HWREGH(base + HRPWMCAL_O_HRMSTEP) =
             ((HWREGH(base + HRPWMCAL_O_HRMSTEP) & ~HRPWMCAL_HRMSTEP_HRMSTEP_M) |
               mepCount);

}

//*****************************************************************************
//
//! Set high resolution Dead Band MEP (Micro Edge Positioner) control.
//!
//! \param base is the base address of the EPWM module.
//! \param mepDBEdge is the high resolution MEP (Micro Edge Positioner) control
//!        edge.
//!
//! This function sets the high resolution Dead Band edge that the MEP (Micro
//! Edge Positioner) controls Valid values for mepDBEdge are:
//!   - HRPWM_DB_MEP_CTRL_DISABLE  - HRPWM is disabled
//!   - HRPWM_DB_MEP_CTRL_RED      - MEP (Micro Edge Positioner) controls
//!                                  Rising Edge Delay
//!   - HRPWM_DB_MEP_CTRL_FED      - MEP (Micro Edge Positioner) controls
//!                                  Falling Edge Delay
//!   - HRPWM_DB_MEP_CTRL_RED_FED  - MEP (Micro Edge Positioner) controls both
//!                                  Falling and Rising edge delays
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setDeadbandMEPEdgeSelect(uint32_t base,
                               HRPWM_MEPDeadBandEdgeMode mepDBEdge)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the HRPWM DB edge mode
    //

    HWREGH(base + EPWM_O_HRCNFG2) =
       ((HWREGH(base + EPWM_O_HRCNFG2) & ~EPWM_HRCNFG2_EDGMODEDB_M) |
         ((uint16_t)mepDBEdge));

}

//*****************************************************************************
//
//! Set the high resolution Dead Band RED load mode.
//!
//! \param base is the base address of the EPWM module.
//! \param loadEvent is the shadow to active load event.
//!
//! This function sets the high resolution Rising Edge Delay(RED)Dead Band
//! count load mode.
//! Valid values for loadEvent are:
//!   - HRPWM_LOAD_ON_CNTR_ZERO        - load when counter equals zero.
//!   - HRPWM_LOAD_ON_CNTR_PERIOD      - load when counter equals period
//!   - HRPWM_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero
//!                                             or period.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setRisingEdgeDelayLoadMode(uint32_t base,
                                 HRPWM_LoadMode loadEvent)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the HRPWM RED load mode
    //

    HWREGH(base + EPWM_O_HRCNFG2) =
      ((HWREGH(base + EPWM_O_HRCNFG2) & ~EPWM_HRCNFG2_CTLMODEDBRED_M) |
       ((uint16_t)loadEvent << EPWM_HRCNFG2_CTLMODEDBRED_S));

}

//*****************************************************************************
//
//! Set the high resolution Dead Band FED load mode.
//!
//! \param base is the base address of the EPWM module.
//! \param loadEvent is the shadow to active load event.
//!
//! This function sets the high resolution Falling Edge Delay(FED) Dead Band
//! count load mode.
//! Valid values for loadEvent are:
//!   - HRPWM_LOAD_ON_CNTR_ZERO        - load when counter equals zero.
//!   - HRPWM_LOAD_ON_CNTR_PERIOD      - load when counter equals period
//!   - HRPWM_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero
//!                                             or period.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setFallingEdgeDelayLoadMode(uint32_t base, HRPWM_LoadMode loadEvent)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the HRPWM FED load mode
    //

    HWREGH(base + EPWM_O_HRCNFG2) =
       ((HWREGH(base + EPWM_O_HRCNFG2) & ~EPWM_HRCNFG2_CTLMODEDBFED_M) |
        ((uint16_t)loadEvent << EPWM_HRCNFG2_CTLMODEDBFED_S));

}

//*****************************************************************************
//
//!
//! \param base is the base address of the EPWM module.
//!
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_lockRegisters(uint32_t base, HRPWM_LockRegisterGroup registerGroup)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Write the Key to EPWMLOCK register
    //
    HWREG(base + EPWM_O_LOCK) =
                           (0xA5A50000UL | ((uint32_t)registerGroup));
}

//*****************************************************************************
//
//! Sets the consolidated XCMP values in HR mode.
//!
//! \param base is the base address of the EPWM module
//! \param xcmpReg is the XCMP register offset
//! \param xcmpValue is the consolidated value to be written to XCMP registers
//!
//! This function sets the consolidated counter compare(XCMPx:XCMPxHR) value
//! required in high resolution mode for XCMP registers.
//! Valid values for xcmpReg are:
//!    EPWM_XCMP[1-8]_[ACTIVE/SHADOW1/SHADOW2/SHADOW3]
//!                          -XCMP[1-8]_[ACTIVE/SHADOW1/SHADOW2/SHADOW3]
//!    EPWM_XTBPRD_ACTIVE                               -XTBPRD_ACTIVE
//!    EPWM_XTBPRD_SHADOW1                              -XTBPRD_SHADOW1
//!    EPWM_XTBPRD_SHADOW2                              -XTBPRD_SHADOW2
//!    EPWM_XTBPRD_SHADOW3                              -XTBPRD_SHADOW3
//!
//! \b Note: For configuring XCMPx = 0x3E8, XCMPxHR = 0x64; value of
//!          xcmpValue = 0x03E80064
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setXCMPRegValue(uint32_t base, EPWM_XCMPReg xcmpReg,
                      uint32_t xcmpValue)
{
    //
    // Check the arguments
    //
    ASSERT(EPWM_isBaseValid(base));
    uint32_t registerOffset;
    registerOffset = base + EPWM_O_XCMP +
                     EPWM_O_XCMP1_ACTIVE + (uint32_t)xcmpReg*2U;

    //
    // Write to the XCMP registers.
    //
    HWREG(registerOffset) = xcmpValue;
}

//*****************************************************************************
//
//! Sets only the high resolution XCMP value.
//!
//! \param base is the base address of the EPWM module
//! \param xcmpReg is the XCMP register offset
//! \param hrXcmpValue is the HR value to be written to XCMP registers
//!
//! This function sets the high resolution counter compare value(XCMPx_HR) for
//! XCMP registers.
//! Valid values for xcmpReg are:
//!    EPWM_XCMP[1-8]_[ACTIVE/SHADOW1/SHADOW2/SHADOW3]
//!                          -XCMP[1-8]_[ACTIVE/SHADOW1/SHADOW2/SHADOW3]
//!    EPWM_XTBPRD_ACTIVE                               -XTBPRD_ACTIVE
//!    EPWM_XTBPRD_SHADOW1                              -XTBPRD_SHADOW1
//!    EPWM_XTBPRD_SHADOW2                              -XTBPRD_SHADOW2
//!    EPWM_XTBPRD_SHADOW3                              -XTBPRD_SHADOW3
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
HRPWM_setHiResXCMPRegValueOnly(uint32_t base, EPWM_XCMPReg xcmpReg,
                               uint32_t hrXcmpValue)
{
    //
    // Check the arguments
    //
    ASSERT(EPWM_isBaseValid(base));
    uint32_t registerOffset;
    registerOffset = base + EPWM_O_XCMP +
                     EPWM_O_XCMP1_ACTIVE + (uint32_t)xcmpReg*2U;

    //
    // Write to the XCMP registers.
    //
    HWREGH(registerOffset) = hrXcmpValue;
}
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

#endif // HRPWM_H
