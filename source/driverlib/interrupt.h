//###########################################################################
//
// FILE:   interrupt.h
//
// TITLE:  C29x Interrupt (PIPE) driver.
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

#ifndef INTERRUPT_H
#define INTERRUPT_H

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
//! \addtogroup interrupt_api Interrupt
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_pipe.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "ssu.h"
#include "esm.h"
#include "erroraggregator.h"

//*****************************************************************************
//
//! Total number of interrupts available in the device
//
//*****************************************************************************
#define INTERRUPT_NO_OF_CHANNELS    256U

//*****************************************************************************
//
//! Values that can be passed to Interrupt_lockRegister(),
//! Interrupt_unlockRegister(), Interrupt_commitRegister() as the \e registers
//! parameter.
//
//*****************************************************************************
#define INTERRUPT_LINK_REGS    PIPE_LOCK_LINK_LOCK
#define INTERRUPT_CONFIG_REGS  PIPE_LOCK_CONFIG_LOCK
#define INTERRUPT_GLOBAL_REGS  PIPE_LOCK_GLOBAL_LOCK
#define INTERRUPT_VECTOR_REG   PIPE_LOCK_VECT_LOCK

//*****************************************************************************
//
//! Values that can be passed to Interrupt_configChannel() as contextID
//! parameter.
//
//*****************************************************************************
typedef enum
{
    INTERRUPT_CONTEXTID_0,
    INTERRUPT_CONTEXTID_1,
    INTERRUPT_CONTEXTID_2,
    INTERRUPT_CONTEXT_AGNOSTIC
}Interrupt_Context;


//*****************************************************************************
//
//! Struct used as parameter to Interrupt_configChannel() for registering an
//! interrupt in PIPE.
//
//*****************************************************************************
typedef struct
{
    bool              enable;     // true : enable, false : disable
    void              (*handler)(void); // pointer to the ISR
    uint8_t           priority;   // Priority level 0-255
    SSU_Link          linkOwner;  // Use enum SSU_LINK0-15
    Interrupt_Context contextID;  // Use enum INTERRUPT_CONTEXT_XXX
    SSU_APILink       apiLinkID;  // Use enum SSU_LINK0-15
} Interrupt_Config;

//*****************************************************************************
//
//! Struct used as parameter to Interrupt_configChannel() for registering an
//! interrupt in PIPE.
//
//*****************************************************************************
typedef struct
{
    uint32_t                        cpu1EsmSts[ESM_NUM_GROUPS]; // CPU1 ESM status for all groups
    ErrorAggregator_CpuErrorInfo    cpu1EaSts;                  // CPU1 EA status
    ErrorAggregator_CpuErrorInfo    cpu2EaSts;                  // CPU2 EA status
    ErrorAggregator_CpuErrorInfo    cpu3EaSts;                  // CPU3 EA status
    ErrorAggregator_RtdmaErrorInfo  rtdma1EaSts;                // RTDMA1 EA status
    ErrorAggregator_RtdmaErrorInfo  rtdma2EaSts;                // RTDMA2 EA status
    ErrorAggregator_ErrorInfo       ssuEaSts;                   // SSU EA status
    ErrorAggregator_ErrorInfo       ethercatEaSts;              // Ethercat EA status
} Interrupt_NmiStatus;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \internal
//! The default interrupt handler.
//!
//! This is the default interrupt handler.  The Interrupt_initVectorTable()
//! function sets all vectors to this function.  Also, when an interrupt is
//! unregistered using the Interrupt_unregister() function, this handler takes
//! its place.  This should never be called during normal operation.
//!
//! The ESTOP0 statement is for debug purposes only. Remove and replace with an
//! appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_defaultHandler(void);

//*****************************************************************************
//
//! \internal
//! The default non-maskable interrupt handler.
//!
//! This is the default interrupt handler for a non-maskable interrupt (NMI).
//! The Interrupt_initVectorTable() function sets the appropriate vector to
//! this function.  This should never be called during normal operation.
//!
//! The ESTOP0 statement is for debug purposes only. Remove and replace with an
//! appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_defaultNMIHandler(void);

//*****************************************************************************
//
//! \internal
//! Function to clear the ESM and EA error flags.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_clearEsmEaFlags(void);

//*****************************************************************************
//
//! Global enable for INT and RTINT.
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_enableGlobal(void)
{
    HWREG(PIPE_BASE + PIPE_O_GLOBAL_EN) = 0x3U | PIPE_GLOBAL_EN_KEY;
}

//*****************************************************************************
//
//! Global disable for INT and RTINT.
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_disableGlobal(void)
{
    HWREG(PIPE_BASE + PIPE_O_GLOBAL_EN) = PIPE_GLOBAL_EN_KEY;
}

//*****************************************************************************
//
//! Enables an interrupt.
//!
//! \param intNum specifies the interrupt to be enabled.
//!
//! The specified interrupt is enabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! The available \e intNum values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_enable(uint32_t intNum)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);
    HWREGB(PIPE_BASE + PIPE_O_INT_CTL_L(intNum)) = PIPE_INT_CTL_L_EN;
}

//*****************************************************************************
//
//! Disables an interrupt.
//!
//! \param intNum specifies the interrupt to be disabled.
//!
//! The specified interrupt is disabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! The available \e intNum values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_disable(uint32_t intNum)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);
    HWREGB(PIPE_BASE + PIPE_O_INT_CTL_L(intNum)) = 0U;
}

//*****************************************************************************
//
//! Force an interrupt
//!
//! \param intNum specifies the interrupt to be forced.
//!
//! The available \e intNum values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_force(uint32_t intNum)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);
    HWREGB(PIPE_BASE + PIPE_O_INT_CTL_H(intNum)) = PIPE_INT_CTL_H_FLAG_FRC;
}

//*****************************************************************************
//
//! Clear the interrupt flag
//!
//! \param intNum specifies the interrupt flag to be cleared.
//!
//! The available \e intNum values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_clearFlag(uint32_t intNum)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);
    HWREGB(PIPE_BASE + PIPE_O_INT_CTL_H(intNum)) = PIPE_INT_CTL_H_FLAG_CLR;
}

//*****************************************************************************
//
//! Clear the interrupt overflow flag
//!
//! \param intNum specifies the interrupt flag to be cleared.
//!
//! The available \e intNum values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_clearOverflowFlag(uint32_t intNum)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);
    HWREGB(PIPE_BASE + PIPE_O_INT_CTL_H(intNum)) =
                                            PIPE_INT_CTL_H_OVERFLOW_FLAG_CLR;
}


//*****************************************************************************
//
//! Registers a function to be called when an interrupt occurs.
//!
//! \param intNum specifies the interrupt in question.
//! \param handler is a pointer to the function to be called.
//!
//! This function is used to specify the handler function to be called when the
//! given interrupt is asserted to the processor.  When the interrupt occurs,
//! if it is enabled (via Interrupt_enable()), the handler function will be
//! called in interrupt context.  Since the handler function can preempt other
//! code, care must be taken to protect memory or peripherals that are accessed
//! by the handler and other non-handler code.
//!
//! The available \e intNum values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_register(uint32_t intNum, void (*handler)(void))
{
    //
    //  INT_NMI used as an id and has no numeric significance
    //
    ASSERT((intNum < INTERRUPT_NO_OF_CHANNELS) || (intNum == INT_NMI));

    if(intNum == INT_NMI)
    {
        HWREG(PIPE_BASE + PIPE_O_NMI_VECT) = (uint32_t)handler;
    }
    else
    {
        HWREG(PIPE_BASE + PIPE_O_INT_VECT_ADDR(intNum)) = (uint32_t)handler;
    }
}


//*****************************************************************************
//
//! Unregisters the function to be called when an interrupt occurs.
//!
//! \param intNum specifies the interrupt in question.
//!
//! This function is used to indicate that a default handler
//! Interrupt_defaultHandler() should be called when the given interrupt is
//! asserted to the processor.  Call Interrupt_disable() to disable
//! the interrupt before calling this function.
//!
//! The available \e intNum values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_unregister(uint32_t intNum)
{
    //
    //  INT_NMI used as an id and has no numeric significance
    //
    ASSERT((intNum < INTERRUPT_NO_OF_CHANNELS) || (intNum == INT_NMI));

    if(intNum == INT_NMI)
    {
        HWREG(PIPE_BASE + PIPE_O_NMI_VECT) =
                                (uint32_t)Interrupt_defaultHandler;
    }
    else
    {
        HWREG(PIPE_BASE + PIPE_O_INT_VECT_ADDR(intNum)) =
                                (uint32_t)Interrupt_defaultHandler;
    }
}

//*****************************************************************************
//
//! Set the Threshold for RTINT
//!
//! \param threshold Threshold value (0-255)
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setThreshold(uint8_t threshold)
{
    HWREGB(PIPE_BASE + PIPE_O_RTINT_THRESHOLD) = threshold;
}

//*****************************************************************************
//
//! Set the Interrupt Group Mask
//!
//! \param groupMask Group mask (0-0xFF)
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setGroupMask(uint8_t groupMask)
{
    HWREGB(PIPE_BASE + PIPE_O_INT_GRP_MASK) = groupMask;
}

//*****************************************************************************
//
//! Set the Interrupt Priority Level
//!
//! \param intNum specifies the interrupt in question.
//! \param priority Priority level (0-255)
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setPriority(uint32_t intNum, uint8_t priority)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);

    HWREGB(PIPE_BASE + PIPE_O_INT_CONFIG(intNum)) = priority;
}

//*****************************************************************************
//
//! Set the Interrupt Context ID
//!
//! \param intNum specifies the interrupt in question.
//! \param contextID Context ID to be set for the interrupt
//!                  - INTERRUPT_CONTEXTID_0
//!                  - INTERRUPT_CONTEXTID_1
//!                  - INTERRUPT_CONTEXTID_2
//!                  - INTERRUPT_CONTEXT_AGNOSTIC
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setContextID(uint32_t intNum, Interrupt_Context contextID)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);

    HWREGB(PIPE_BASE + PIPE_O_INT_CONFIG(intNum) + 2U) = (uint8_t)contextID;
}

//*****************************************************************************
//
//! Set the Interrupt Link Owner
//!
//! \param intNum specifies the interrupt in question.
//! \param linkOwner LinkOwner to be set for the interrupt (SSU_LINK0..15)
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setLinkOwner(uint32_t intNum, SSU_Link linkOwner)
{
    //
    //  INT_NMI used as an id and has no numeric significance
    //
    ASSERT((intNum < INTERRUPT_NO_OF_CHANNELS) || (intNum == INT_NMI));

    if(intNum == INT_NMI)
    {
        HWREGB(PIPE_BASE + PIPE_O_NMI_LINK_OWNER) = (uint8_t)linkOwner;
    }
    else
    {
        HWREGB(PIPE_BASE + PIPE_O_INT_LINK_OWNER(intNum)) =
            (HWREGB(PIPE_BASE + PIPE_O_INT_LINK_OWNER(intNum)) & 0xF0U) |
            (uint8_t)linkOwner;
    }
}

//*****************************************************************************
//
//! Set the Access protection inheritance link
//!
//! \param intNum specifies the interrupt in question.
//! \param apiLinkID Access protection inheritance link for the interrupt
//!                 (Use SSU_API_LINK1..15, or SSU_API_DISABLE to disable)
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setAPILink(uint32_t intNum, SSU_APILink apiLinkID)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);

    if(apiLinkID == SSU_API_DISABLE)
    {
        HWREGH(PIPE_BASE + PIPE_O_INT_LINK_OWNER(intNum)) &= 0xFU;
    }
    else
    {
        HWREGH(PIPE_BASE + PIPE_O_INT_LINK_OWNER(intNum)) =
            (HWREGB(PIPE_BASE + PIPE_O_INT_LINK_OWNER(intNum)) & 0x0FU) |
            PIPE_INT_LINK_OWNER_API_LINK_EN |
            ((uint16_t)apiLinkID << PIPE_INT_LINK_OWNER_API_LINK_S);
    }
}

//*****************************************************************************
//
//! Set the current Context ID
//!
//! \param contextID can be one of the following :
//!               - INTERRUPT_CONTEXTID_0
//!               - INTERRUPT_CONTEXTID_1
//!               - INTERRUPT_CONTEXTID_2
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setActiveContextID(Interrupt_Context contextID)
{
    ASSERT(contextID != INTERRUPT_CONTEXT_AGNOSTIC);
    HWREG(PIPE_BASE + PIPE_O_TASK_CTRL) =
                    (HWREG(PIPE_BASE + PIPE_O_TASK_CTRL) &
                     ~PIPE_TASK_CTRL_ACTIVE_CONTEXT_ID_M) |
                    (uint32_t)contextID | PIPE_TASK_CTRL_KEY;
}

//*****************************************************************************
//
//! Enable Supervisor ignore INTE control
//!
//! \param None
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_enableSupervisorIgnoreINTE(void)
{
    HWREG(PIPE_BASE + PIPE_O_TASK_CTRL) =
                    (HWREG(PIPE_BASE + PIPE_O_TASK_CTRL) |
                     PIPE_TASK_CTRL_SUP_IGN_INTE_EN) |
                    PIPE_TASK_CTRL_KEY;
}

//*****************************************************************************
//
//! Disable Supervisor ignore INTE control
//!
//! \param None
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_disableSupervisorIgnoreINTE(void)
{
    HWREG(PIPE_BASE + PIPE_O_TASK_CTRL) =
                    (HWREG(PIPE_BASE + PIPE_O_TASK_CTRL) &
                     ~PIPE_TASK_CTRL_SUP_IGN_INTE_EN) |
                    PIPE_TASK_CTRL_KEY;
}

//*****************************************************************************
//
//! RTINT Stack Warning
//!
//! \param level Level for the RTISP to trigger the warning (0-15)
//! \param priority priority level for which interrupts will be disabled
//!
//! Once RTISP >= level the RTINT assertions are only for interrupts higher
//! in priority than the configured priority
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setRTINTSPWarning(uint8_t level, uint8_t priority)
{
    ASSERT(level <= 15U);

    HWREG(PIPE_BASE + PIPE_O_RTINT_SP_H) =
                ((uint32_t)level << PIPE_RTINT_SP_H_WARNRTISP_S) |
                ((uint32_t)priority << PIPE_RTINT_SP_H_WARNRTISP_PRIO_LEVEL_S);
}

//*****************************************************************************
//
//! Sets the INT Stack Pointer
//!
//! \param stack is the INT stack.
//!
//! CPU will acknowledge the INT only when its current execution stack matched
//! with INTSP
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_setINTSP(SSU_Stack stack)
{
    HWREGB(PIPE_BASE + PIPE_O_INTSP) = stack;
}

//*****************************************************************************
//
//! Lock the Boot link updates to config registers
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_lockBootLinkUpdates(void)
{
    HWREG(PIPE_BASE + PIPE_O_BOOT_LINK_CTRL) =
                PIPE_BOOT_LINK_CTRL_BOOT_LINK_LOCK |
                PIPE_BOOT_LINK_CTRL_KEY;
}

//*****************************************************************************
//
//! Lock PIPE registers
//!
//! \param registers Registers to be locked. Can be OR of the following -
//!                     - INTERRUPT_LINK_REGS
//!                     - INTERRUPT_CONFIG_REGS
//!                     - INTERRUPT_GLOBAL_REGS
//!                     - INTERRUPT_VECTOR_REG
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_lockRegister(uint32_t registers)
{
    HWREG(PIPE_BASE + PIPE_O_LOCK) =
                    (HWREG(PIPE_BASE + PIPE_O_LOCK) | registers) |
                    PIPE_LOCK_KEY;
}

//*****************************************************************************
//
//! Unlock PIPE registers
//!
//! \param registers Registers to be unlocked. Can be OR of the following -
//!                     - INTERRUPT_LINK_REGS
//!                     - INTERRUPT_CONFIG_REGS
//!                     - INTERRUPT_GLOBAL_REGS
//!                     - INTERRUPT_VECTOR_REG
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_unlockRegister(uint32_t registers)
{
    HWREG(PIPE_BASE + PIPE_O_LOCK) =
                    (HWREG(PIPE_BASE + PIPE_O_LOCK) & ~registers) |
                    PIPE_LOCK_KEY;
}

//*****************************************************************************
//
//! Unlock PIPE registers
//!
//! \param registers Registers to be unlocked. Can be OR of the following -
//!                     - INTERRUPT_LINK_REGS
//!                     - INTERRUPT_CONFIG_REGS
//!                     - INTERRUPT_GLOBAL_REGS
//!                     - INTERRUPT_VECTOR_REG
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_commitRegister(uint32_t registers)
{
    HWREG(PIPE_BASE + PIPE_O_COMMIT) =
                    (HWREG(PIPE_BASE + PIPE_O_COMMIT) | registers) |
                    PIPE_COMMIT_KEY;
}

//*****************************************************************************
//
//! Initializes the PIPE control registers by setting them to a known state.
//!
//! This function initializes the PIPE control registers. After globally
//! disabling interrupts and enabling the PIPE, it clears all of the PIPE
//! interrupt enable bits and interrupt flags.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_initModule(void);

//*****************************************************************************
//
//! Initializes the PIPE vector table by setting all vectors to a default
//! handler function.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_initVectorTable(void);

//*****************************************************************************
//
//! Configures the interrupt channel
//!
//! \param intNum specifies the interrupt in question.
//! \param config Configuration parameters. Refer to the struct
//! Interrupt_Config
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_configChannel(uint32_t intNum, Interrupt_Config config);

//*****************************************************************************
//
//! Configures the NMI
//!
//! \param handler is a pointer to the function to be called.
//! \param linkOwner is the linkOwner (INTERRUPT_LINKOWNER_0-15)
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_configNMI(void (*handler)(void), SSU_Link linkOwner);

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

#endif // INTERRUPT_H
