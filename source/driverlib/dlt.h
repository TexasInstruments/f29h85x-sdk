//###########################################################################
//
// FILE:   dlt.h
//
// TITLE:  C29x Data Logger and Trace (DLT) driver.
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

#ifndef DLT_H
#define DLT_H

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
//! \addtogroup dlt_api DLT
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_dlt.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "ssu.h"


//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define DLT_CONTROL_CAP_MODE_S  3U

//*****************************************************************************
//
//! Values that can be passed to DLT_enableInterrupt(), DLT_disableInterrupt(),
//! DLT_forceEvent(), DLT_clearEvent() functions as \e events parameter.
//
//*****************************************************************************
#define DLT_INT_INT          0x1U    // Global Interrupt
#define DLT_INT_TIMER1_OVF   0x2U    // TIMER1 overflow
#define DLT_INT_TIMER2_OVF   0x4U    // TIMER2 overflow
#define DLT_INT_FIFO_OVF     0x8U    // FIFO overflow
#define DLT_INT_FIFO_UF      0x10U   // FIFO underflow
#define DLT_INT_FIFO_TRIG    0x20U   // FIFO reached Trigger level

//*****************************************************************************
//
//! Values that can be passed to DLT_configERADFilter() as part of the
//! \e startEvents and \e endEvents parameter.
//
//*****************************************************************************
typedef enum
{
    DLT_EVENT_CPUx_ERAD_EBC_EVT1   = 0x000000001U,  //!CPUx ERAD EBC EVT1
    DLT_EVENT_CPUx_ERAD_EBC_EVT2   = 0x000000002U,  //!CPUx ERAD EBC EVT2
    DLT_EVENT_CPUx_ERAD_EBC_EVT3   = 0x000000004U,  //!CPUx ERAD EBC EVT3
    DLT_EVENT_CPUx_ERAD_EBC_EVT4   = 0x000000008U,  //!CPUx ERAD EBC EVT4
    DLT_EVENT_CPUx_ERAD_EBC_EVT5   = 0x000000010U,  //!CPUx ERAD EBC EVT5
    DLT_EVENT_CPUx_ERAD_EBC_EVT6   = 0x000000020U,  //!CPUx ERAD EBC EVT6
    DLT_EVENT_CPUx_ERAD_EBC_EVT7   = 0x000000040U,  //!CPUx ERAD EBC EVT7
    DLT_EVENT_CPUx_ERAD_EBC_EVT8   = 0x000000080U,  //!CPUx ERAD EBC EVT8
    DLT_EVENT_CPUx_ERAD_SEC_EVT1   = 0x000010000U,  //!CPUx ERAD SEC EVT1
    DLT_EVENT_CPUx_ERAD_SEC_EVT2   = 0x000020000U,  //!CPUx ERAD SEC EVT2
    DLT_EVENT_CPUx_ERAD_SEC_EVT3   = 0x000040000U,  //!CPUx ERAD SEC EVT3
    DLT_EVENT_CPUx_ERAD_SEC_EVT4   = 0x000080000U,  //!CPUx ERAD SEC EVT4
    DLT_EVENT_CPUx_ERAD_AND_MASK1  = 0x001000000U,  //!CPUx ERAD AND MASK1
    DLT_EVENT_CPUx_ERAD_AND_MASK2  = 0x002000000U,  //!CPUx ERAD AND MASK2
    DLT_EVENT_CPUx_ERAD_AND_MASK3  = 0x004000000U,  //!CPUx ERAD AND MASK3
    DLT_EVENT_CPUx_ERAD_AND_MASK4  = 0x008000000U,  //!CPUx ERAD AND MASK4
    DLT_EVENT_CPUx_ERAD_OR_MASK1   = 0x100000000U,  //!CPUx ERAD OR MASK1
    DLT_EVENT_CPUx_ERAD_OR_MASK2   = 0x200000000U,  //!CPUx ERAD OR MASK2
    DLT_EVENT_CPUx_ERAD_OR_MASK3   = 0x400000000U,  //!CPUx ERAD OR MASK3
    DLT_EVENT_CPUx_ERAD_OR_MASK4   = 0x800000000U   //!CPUx ERAD OR MASK4
} DLT_EventSelect;

//*****************************************************************************
//
//! Values that can be passed to DLT_setCaptureMode() as \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    DLT_CAPTURE_TIME      = 0x0U,  //!< With each entry, Timestamp is captured
    DLT_CAPTURE_PC_SOURCE = 0x1U   //!< With each entry, PC Source is captured
} DLT_CaptureMode;

//*****************************************************************************
//
//! Values that can be passed to DLT_configTagFilter() as the configure
//! parameter.
//
//*****************************************************************************
typedef struct
{
    uint16_t startMask;         // Tag Filtering Start Mask
    uint16_t startReference;    // Tag Filtering Start Reference
    uint16_t endMask;           // Tag Filtering End Mask
    uint16_t endReference;      // Tag Filtering End Reference
} DLT_ConfigTagFilterParams;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an DLT FIFO base address.
//!
//! \param base specifies the CPU specific DLT FIFO base address.
//!
//! This function determines if a CPU DLT FIFO base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
__attribute__((always_inline))
static inline bool
DLT_isFIFOBaseValid(uint32_t base)
{
    //
    // Check if the base address of the DLT FIFO is valid
    //
    return(
           ((base & BASE_ADDR_MASK) == CPU1DLTFIFO_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == CPU2DLTFIFO_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == CPU3DLTFIFO_BASE_FRAME(0U))
          );
}
#endif

//*****************************************************************************
//
//! Enable Link permissions.
//!
//! \param link is the SSU_LINK for which the permissions are enabled to record
//! DLT entries in the FIFO.
//!
//! The LINKs corresponding to the bits set are allowed to record DLT entries
//! in the FIFO.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_enableLinkPermission(SSU_Link link)
{
    HWREG(CPUDLT_BASE + DLT_O_LINK_EN) |= 1U << (uint32_t)link;
}

//*****************************************************************************
//
//! Disable Link permissions.
//!
//! \param link is the SSU_LINK for which the permissions are disabled to
//! record DLT entries in the FIFO.
//!
//! This function disables the permission of the corresponding link to record
//! entries to the DLT FIFO.
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_disableLinkPermission(SSU_Link link)
{
    HWREG(CPUDLT_BASE + DLT_O_LINK_EN) &= ~(1U << (uint32_t)link);
}

//*****************************************************************************
//
//! Enable DLT Recording and triggers.
//!
//! This function does a global enable of DLT module. The DLT recording and
//! triggers are enabled.
//!
//! \note The 16 bit key (DLT_CONTROL_KEY) act as a key to enable writes to
//! lower 16 bits of DLT_CONTROL register. The only time lower 16 bits can be
//! updated is by a single 32-bit write where bits 31:16 equal 0x5a5a. All
//! other writes are ignored including separate 16-bit writes.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_enableModule(void)
{
    HWREG(CPUDLT_BASE + DLT_O_CONTROL) |= (DLT_CONTROL_KEY |
                                           DLT_CONTROL_DLT_EN);
}

//*****************************************************************************
//
//! Disable Logging.
//!
//! This function disables all components of the DLT module.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_disableModule(void)
{
    HWREG(CPUDLT_BASE + DLT_O_CONTROL) = DLT_CONTROL_KEY |
        (HWREG(CPUDLT_BASE + DLT_O_CONTROL) & (~(uint32_t)DLT_CONTROL_DLT_EN));
}

//*****************************************************************************
//
//! Enable ERAD Filtering.
//!
//! This function enables ERAD event based START-END filtering.
//! Note: Filter enables are not expected to change dynamically in the middle
//! of data logging, and take effect after a few cycles.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_enableERADFilter(void)
{
    HWREG(CPUDLT_BASE + DLT_O_CONTROL) |= (DLT_CONTROL_KEY |
                                           DLT_CONTROL_ERAD_FILTER_EN);
}

//*****************************************************************************
//
//! Disable ERAD Filtering.
//!
//! This function disables the ERAD event based START-END filtering.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_disableERADFilter(void)
{
    HWREG(CPUDLT_BASE + DLT_O_CONTROL) = DLT_CONTROL_KEY |
                                   (HWREG(CPUDLT_BASE + DLT_O_CONTROL) &
                                    (~(uint32_t)DLT_CONTROL_ERAD_FILTER_EN));
}

//*****************************************************************************
//
//! Enable Tag Filtering.
//!
//! This function enables the TAG based START-END filtering.
//!
//! \note TAGs should be at the beginning of every function call or ISR
//! function, followed by any registers being data logged.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_enableTagFilter(void)
{
    HWREG(CPUDLT_BASE + DLT_O_CONTROL) |= (DLT_CONTROL_KEY |
                                           DLT_CONTROL_TAG_FILTER_EN);
}

//*****************************************************************************
//
//! Disable Tag Filtering.
//!
//! This function disables TAG based START-END filtering.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_disableTagFilter(void)
{
    HWREG(CPUDLT_BASE + DLT_O_CONTROL) = DLT_CONTROL_KEY |
                                   (HWREG(CPUDLT_BASE + DLT_O_CONTROL) &
                                    (~(uint32_t)DLT_CONTROL_TAG_FILTER_EN));
}

//*****************************************************************************
//
//! Set the DLT Capture Mode.
//!
//! \param mode is the capture mode to be selected. Refer DLT_CaptureMode enum
//! for the possible modes.
//!
//! This function sets the Capture mode.
//!     mode = 0: With each entry, the timestamp is captured.
//!     mode = 1: With each entry, PC source is captured.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_setCaptureMode(DLT_CaptureMode mode)
{
    HWREG(CPUDLT_BASE + DLT_O_CONTROL) = DLT_CONTROL_KEY |
                                         (HWREG(CPUDLT_BASE + DLT_O_CONTROL) &
                                          (~(uint32_t)DLT_CONTROL_CAP_MODE)) |
                                    ((uint32_t)mode << DLT_CONTROL_CAP_MODE_S);
}

//*****************************************************************************
//
//! Reset Filtering Unit.
//!
//! This function resets the filtering unit. It clears the previous status
//! derived from START and STOP events.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_resetFilter(void)
{
    HWREG(CPUDLT_BASE + DLT_O_CONTROL) |= (DLT_CONTROL_KEY |
                                           DLT_CONTROL_FILTER_RST);
}

//*****************************************************************************
//
//! Enable DMA.
//!
//! This function enables DMA request to be generated when FIFO reaches
//! FIFO_TRIG_LEVEL.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_enableDMA(void)
{
    HWREG(CPUDLT_BASE + DLT_O_FIFO_CONTROL) =
                            (HWREG(CPUDLT_BASE + DLT_O_FIFO_CONTROL) &
                            (~(uint32_t)DLT_FIFO_CONTROL_DMA_EN)) |
                            DLT_FIFO_CONTROL_DMA_EN;
}

//*****************************************************************************
//
//! Disable DMA.
//!
//! This function disables DMA request from being generated when FIFO reaches
//! FIFO_TRIG_LEVEL.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_disableDMA(void)
{
    HWREG(CPUDLT_BASE + DLT_O_FIFO_CONTROL) =
                            HWREG(CPUDLT_BASE + DLT_O_FIFO_CONTROL) &
                            (~(uint32_t)DLT_FIFO_CONTROL_DMA_EN);
}

//*****************************************************************************
//
//! Reset FIFO.
//!
//! This function initializes write and read pointers (FIFO_PTR), number of
//! words (FIFO_STS.WORD_CTR), Write counter of FIFO (FIFO_STS.WR_CTR) to 0.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_resetFIFO(void)
{
    HWREG(CPUDLT_BASE + DLT_O_FIFO_CONTROL) |= DLT_FIFO_CONTROL_FIFO_RST;
}

//*****************************************************************************
//
//! Set FIFO Trigger Level.
//!
//! \param triggerLevel is the FIFO trigger level to be set.
//!
//! This function sets the level of FIFO writes required to trigger INT/DMA.
//! When \e triggerLevel new writes are received in FIFO after the last
//! trigger, INT/DMA trigger is generated if enabled.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_setFIFOTriggerLevel(uint32_t triggerLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(triggerLevel <= 0xFFU);

    HWREG(CPUDLT_BASE + DLT_O_FIFO_CONTROL) =
                        (HWREG(CPUDLT_BASE + DLT_O_FIFO_CONTROL) &
                        (~(uint32_t)DLT_FIFO_CONTROL_WR_CTR_TRIG_LEVEL_M)) |
                ((triggerLevel - 1U) << DLT_FIFO_CONTROL_WR_CTR_TRIG_LEVEL_S);
}

//*****************************************************************************
//
//! Reset TIMER.
//!
//! TIMER2 is reset to 0, stopped and restarted.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_resetTimer(void)
{
    HWREGH(CPUDLT_BASE + DLT_O_TIMER_CONTROL) = DLT_TIMER_CONTROL_TIMER2_RST;
    HWREGH(CPUDLT_BASE + DLT_O_TIMER_CONTROL) = 0U;
}

//*****************************************************************************
//
//! Get FIFO Word Status.
//!
//! This function gets the number of 64-bit words to be read in the FIFO
//! (current level of FIFO that is filled).
//!
//! \return Returns the number of 64-bit words to be read in the FIFO.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
DLT_getFIFOWordStatus(void)
{
    return(HWREG(CPUDLT_BASE + DLT_O_FIFO_STS) & DLT_FIFO_STS_WORD_CTR_M);
}

//*****************************************************************************
//
//! Get FIFO Write Status.
//!
//! This function gets the number of 64-bit words written to the FIFO after
//! the last trigger.
//! This WR_CTR gets reset every time the WR_CTR = FIFO_TRIG_LEVEL.
//!
//! \return Returns the number of 64-bit words written to the FIFO after the
//! last trigger.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
DLT_getFIFOWriteStatus(void)
{
    return((HWREG(CPUDLT_BASE + DLT_O_FIFO_STS) & DLT_FIFO_STS_WR_CTR_M)
                                               >> DLT_FIFO_STS_WR_CTR_S);
}

//*****************************************************************************
//
//! Get FIFO Read Pointer.
//!
//! This function returns the read pointer location of FIFO.
//!
//! \return Returns the read pointer location of FIFO.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
DLT_getFIFOReadPointer(void)
{
    return(HWREG(CPUDLT_BASE + DLT_O_FIFO_PTR) & DLT_FIFO_PTR_RD_PTR_M);
}

//*****************************************************************************
//
//! Get FIFO Write Pointer.
//!
//! This function returns the write pointer location of FIFO.
//!
//! \return Returns the write pointer location of FIFO.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
DLT_getFIFOWritePointer(void)
{
    return((HWREG(CPUDLT_BASE + DLT_O_FIFO_PTR) & DLT_FIFO_PTR_WR_PTR_M)
                                               >> DLT_FIFO_PTR_WR_PTR_S);
}

//*****************************************************************************
//
//! Get TIMER Count.
//!
//! This function returns the current value of TIMER2. TIMER2 is an internal
//! counter and is exported with REGS. It indicates the time difference from
//! the last reported TAG value.
//!
//! \return Returns the current value of TIMER2.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
DLT_getTimerCount(void)
{
    return(HWREG(CPUDLT_BASE + DLT_O_TIMER2_COUNT));
}

//*****************************************************************************
//
//! Global Interrupt Status.
//!
//! This function returns the status of the Global interrupt flag. Reading a
//! 1 on this flag indicates that an interrupt was generated from one of the
//! following events.
//!    - TIMER1 overflow
//!    - TIMER2 overflow
//!    - FIFO overflow
//!    - FIFO underflow
//!    - FIFO reached Trigger level
//!
//! \return Returns \b true if the Global Interrupt Status Flag is set.
//! Returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
DLT_getGlobalInterruptStatus(void)
{
    return(HWREGH(CPUDLT_BASE + DLT_O_INT_FLG) & DLT_INT_FLG_INT);
}

//*****************************************************************************
//
//! TIMER1 Overflow Status.
//!
//! This function returns the overflow status of TIMER1. TIMER1 is exported
//! with TAGS and is a 45 bit timer. TIMER1's value is derived from the 64-bit
//! IPC timer outside DLT.
//!
//! \return Returns \b true if the TIMER1 Overflow Status Flag is set.
//! Returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
DLT_getTimer1OverflowStatus(void)
{
    return(HWREGH(CPUDLT_BASE + DLT_O_INT_FLG) & DLT_INT_FLG_TIMER1_OVF);
}

//*****************************************************************************
//
//! TIMER2 Overflow Status.
//!
//! This function returns the overflow status of TIMER2. The TIMER2 is
//! exported with REGS.
//!
//! \return Returns \b true if the TIMER2 Overflow Status Flag is set.
//! Returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
DLT_getTimer2OverflowStatus(void)
{
    return(HWREGH(CPUDLT_BASE + DLT_O_INT_FLG) & DLT_INT_FLG_TIMER2_OVF);
}

//*****************************************************************************
//
//! FIFO Overflow Status.
//!
//! This function returns the status of FIFO overflow flag. The FIFO overflow
//! flag is set when the FIFO is full and a write is attempted.
//!
//! \return Returns \b true if the FIFO Overflow Status Flag is set.
//! Returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
DLT_getFIFOOverflowStatus(void)
{
    return(HWREGH(CPUDLT_BASE + DLT_O_INT_FLG) & DLT_INT_FLG_FIFO_OVF);
}

//*****************************************************************************
//
//! FIFO Underflow Status.
//!
//! This function returns the status of FIFO underflow flag. The FIFO underflow
//! flag is set when a read is attempted with no data in the FIFO.
//!
//! \return Returns \b true if the FIFO Underflow Status Flag is set.
//! Returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
DLT_getFIFOUnderflowStatus(void)
{
    return(HWREGH(CPUDLT_BASE + DLT_O_INT_FLG) & DLT_INT_FLG_FIFO_UF);
}

//*****************************************************************************
//
//! FIFO reached Trigger level status.
//!
//! This function gets the status of the FIFO whether it has recahed the
//! Trigger level or not. The flag is set when the number of writes in the
//! FIFO reaches the configured trigger level.
//!
//! \return Returns \b true if the FIFO Trigger level Status Flag is set.
//! Returns \b false otherwise.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
DLT_getFIFOTriggerLevelStatus(void)
{
    return(HWREGH(CPUDLT_BASE + DLT_O_INT_FLG) & DLT_INT_FLG_FIFO_TRIG);
}

//*****************************************************************************
//
//! Enable Interrupt.
//!
//! \param events can be a bitwise OR of the following events:
//!      - DLT_INT_TIMER1_OVF
//!      - DLT_INT_TIMER2_OVF
//!      - DLT_INT_FIFO_OVF
//!      - DLT_INT_FIFO_UF
//!      - DLT_INT_FIFO_TRIG
//!
//! The corresponding events are enabled to generate an interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_enableInterrupt(uint16_t events)
{
    HWREGH(CPUDLT_BASE + DLT_O_INT_EN) |= (uint16_t)events;
}

//*****************************************************************************
//
//! Disable Interrupt.
//!
//! \param events can be a bitwise OR of the following events:
//!      - DLT_INT_TIMER1_OVF
//!      - DLT_INT_TIMER2_OVF
//!      - DLT_INT_FIFO_OVF
//!      - DLT_INT_FIFO_UF
//!      - DLT_INT_FIFO_TRIG
//!
//! The corresponding events are disabled to generate an interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_disableInterrupt(uint16_t events)
{
    HWREGH(CPUDLT_BASE + DLT_O_INT_EN) &= ~(uint16_t)events;
}

//*****************************************************************************
//
//! Force event.
//!
//! \param events can be a bitwise OR of the following events:
//!      - DLT_INT_TIMER1_OVF
//!      - DLT_INT_TIMER2_OVF
//!      - DLT_INT_FIFO_OVF
//!      - DLT_INT_FIFO_UF
//!      - DLT_INT_FIFO_TRIG
//!
//! This function forces the corresponding events.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_forceEvent(uint16_t events)
{
    HWREGH(CPUDLT_BASE + DLT_O_INT_FRC) = (uint16_t)events;
}

//*****************************************************************************
//
//! Clear Event.
//!
//! \param events can be a bitwise OR of the following events:
//!      - DLT_INT_INT
//!      - DLT_INT_TIMER1_OVF
//!      - DLT_INT_TIMER2_OVF
//!      - DLT_INT_FIFO_OVF
//!      - DLT_INT_FIFO_UF
//!      - DLT_INT_FIFO_TRIG
//!
//! This function clears the corresponding events.
//! Clearing the INT flag will enable further interrupts to be generated if
//! any of the event flags are set to 1.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DLT_clearEvent(uint16_t events)
{
    HWREGH(CPUDLT_BASE + DLT_O_INT_CLR) = (uint16_t)events;
}

//*****************************************************************************
//
//! Configure Tag Filtering.
//!
//! \param *configParams configuration parameter
//!                      Refer struct DLT_ConfigTagFilterParams
//!
//! This function configures Tag filtering.
//! Recording in FIFO is started if incoming TAG when masked with startMask
//! matches the startReference.
//! Recording in FIFO is stopped if incoming TAG when masked with endMask
//! matches the endReference.
//!
//! \return None.
//
//*****************************************************************************
extern void
DLT_configTagFilter(const DLT_ConfigTagFilterParams *configParams);

//*****************************************************************************
//
//! Configure ERAD Filtering.
//!
//! \param startEvents is the ERAD start Mask. It can be an OR of the
//! enumerated ERAD events from DLT_EventSelect.
//! \param endEvents is the ERAD end Mask. It can be an OR of the
//! enumerated ERAD events from DLT_EventSelect.
//!
//! This function configures ERAD events based filtering.
//! When the ERAD start mask is set, it generates a START DLT event, after
//! which entries are recorded in the FIFO.
//! When the ERAD end mask is set, it generates a END DLT event, after which
//! entries are no longer recorded in the FIFO.
//!
//! \return None.
//
//*****************************************************************************
extern void
DLT_configERADFilter(uint64_t startEvents, uint64_t endEvents);


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

#endif // DLT_H
