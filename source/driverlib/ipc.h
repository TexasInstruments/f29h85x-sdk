//###########################################################################
//
// FILE:   ipc.h
//
// TITLE:  C29x IPC driver.
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

#ifndef IPC_H
#define IPC_H

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
//! \addtogroup ipc_api IPC
//! \brief This module is used for inter-processor communications.
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "debug.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ipc.h"
#include "inc/hw_ints.h"
#include "interrupt.h"
#include "sysctl.h"

//*****************************************************************************
//
// Defines for the APIs
//
//*****************************************************************************


//*****************************************************************************
//
// Values that can be passed as parameter flags in all the IPC API functions.
//
//*****************************************************************************
#define IPC_NO_FLAG     0x00000000U  //!< NO FLAG
#define IPC_FLAG0       0x00000001U  //!< IPC FLAG 0
#define IPC_FLAG1       0x00000002U  //!< IPC FLAG 1
#define IPC_FLAG2       0x00000004U  //!< IPC FLAG 2
#define IPC_FLAG3       0x00000008U  //!< IPC FLAG 3
#define IPC_FLAG4       0x00000010U  //!< IPC FLAG 4
#define IPC_FLAG5       0x00000020U  //!< IPC FLAG 5
#define IPC_FLAG6       0x00000040U  //!< IPC FLAG 6
#define IPC_FLAG7       0x00000080U  //!< IPC FLAG 7
#define IPC_FLAG8       0x00000100U  //!< IPC FLAG 8
#define IPC_FLAG9       0x00000200U  //!< IPC FLAG 9
#define IPC_FLAG10      0x00000400U  //!< IPC FLAG 10
#define IPC_FLAG11      0x00000800U  //!< IPC FLAG 11
#define IPC_FLAG12      0x00001000U  //!< IPC FLAG 12
#define IPC_FLAG13      0x00002000U  //!< IPC FLAG 13
#define IPC_FLAG14      0x00004000U  //!< IPC FLAG 14
#define IPC_FLAG15      0x00008000U  //!< IPC FLAG 15
#define IPC_FLAG16      0x00010000U  //!< IPC FLAG 16
#define IPC_FLAG17      0x00020000U  //!< IPC FLAG 17
#define IPC_FLAG18      0x00040000U  //!< IPC FLAG 18
#define IPC_FLAG19      0x00080000U  //!< IPC FLAG 19
#define IPC_FLAG20      0x00100000U  //!< IPC FLAG 20
#define IPC_FLAG21      0x00200000U  //!< IPC FLAG 21
#define IPC_FLAG22      0x00400000U  //!< IPC FLAG 22
#define IPC_FLAG23      0x00800000U  //!< IPC FLAG 23
#define IPC_FLAG24      0x01000000U  //!< IPC FLAG 24
#define IPC_FLAG25      0x02000000U  //!< IPC FLAG 25
#define IPC_FLAG26      0x04000000U  //!< IPC FLAG 26
#define IPC_FLAG27      0x08000000U  //!< IPC FLAG 27
#define IPC_FLAG28      0x10000000U  //!< IPC FLAG 28
#define IPC_FLAG29      0x20000000U  //!< IPC FLAG 29
#define IPC_FLAG30      0x40000000U  //!< IPC FLAG 30
#define IPC_FLAG31      0x80000000U  //!< IPC FLAG 31
#define IPC_FLAG_ALL    0xFFFFFFFFU  //!< All IPC flags


//
// Useful defines used in APIs
//
#define IPC_SEND_TO_RCV_STEP (CPU1IPCRCV_BASE - CPU1IPCSEND_BASE)
#define IPC_REG_SET(x)         ((uint32_t)(x) + 0x0U)
#define IPC_REG_CLR(x)         ((uint32_t)(x) + 0x4U)
#define IPC_REG_FLG(x)         ((uint32_t)(x) + 0x8U)
#define IPC_REG_SENDCOM(x)     ((uint32_t)(x) + 0x10U)
#define IPC_REG_SENDADDR(x)    ((uint32_t)(x) + 0x14U)
#define IPC_REG_SENDDATA(x)    ((uint32_t)(x) + 0x18U)
#define IPC_REG_REMOTEREPLY(x) ((uint32_t)(x) + 0x1CU)
#define IPC_REG_STS(x)         ((uint32_t)(x) + IPC_SEND_TO_RCV_STEP + 0U)
#define IPC_REG_ACK(x)         ((uint32_t)(x) + IPC_SEND_TO_RCV_STEP + 0x4U)
#define IPC_REG_RECVCOM(x)     ((uint32_t)(x) + IPC_SEND_TO_RCV_STEP + 0x10U)
#define IPC_REG_RECVADDR(x)    ((uint32_t)(x) + IPC_SEND_TO_RCV_STEP + 0x14U)
#define IPC_REG_RECVDATA(x)    ((uint32_t)(x) + IPC_SEND_TO_RCV_STEP + 0x18U)
#define IPC_REG_LOCALREPLY(x)  ((uint32_t)(x) + IPC_SEND_TO_RCV_STEP + 0x1CU)

//*****************************************************************************
//
// Enums for the APIs
//
//*****************************************************************************

//*****************************************************************************
//
//! Values that can be passed as parameter \e ipcChannel in all the driver
//! functions
//
//*****************************************************************************
typedef enum
{
    //
    // CPU1 - Local core, CPU2 - Remote core,
    //
    IPC_CPU1_L_CPU2_R_CH0 = CPU1IPCSEND_BASE + IPC_O_CPU1TOCPU2INTIPCSET(0U),
    IPC_CPU1_L_CPU2_R_CH1 = CPU1IPCSEND_BASE + IPC_O_CPU1TOCPU2INTIPCSET(1U),
    IPC_CPU1_L_CPU2_R_CH2 = CPU1IPCSEND_BASE + IPC_O_CPU1TOCPU2INTIPCSET(2U),
    IPC_CPU1_L_CPU2_R_CH3 = CPU1IPCSEND_BASE + IPC_O_CPU1TOCPU2INTIPCSET(3U),

    //
    // CPU1 - Local core, CPU3 - Remote core,
    //
    IPC_CPU1_L_CPU3_R_CH0 = CPU1IPCSEND_BASE + IPC_O_CPU1TOCPU3INTIPCSET(0U),
    IPC_CPU1_L_CPU3_R_CH1 = CPU1IPCSEND_BASE + IPC_O_CPU1TOCPU3INTIPCSET(1U),
    IPC_CPU1_L_CPU3_R_CH2 = CPU1IPCSEND_BASE + IPC_O_CPU1TOCPU3INTIPCSET(2U),
    IPC_CPU1_L_CPU3_R_CH3 = CPU1IPCSEND_BASE + IPC_O_CPU1TOCPU3INTIPCSET(3U),

    //
    // CPU2 - Local core, CPU1 - Remote core,
    //
    IPC_CPU2_L_CPU1_R_CH0 = CPU2IPCSEND_BASE + IPC_O_CPU2TOCPU1INTIPCSET(0U),
    IPC_CPU2_L_CPU1_R_CH1 = CPU2IPCSEND_BASE + IPC_O_CPU2TOCPU1INTIPCSET(1U),
    IPC_CPU2_L_CPU1_R_CH2 = CPU2IPCSEND_BASE + IPC_O_CPU2TOCPU1INTIPCSET(2U),
    IPC_CPU2_L_CPU1_R_CH3 = CPU2IPCSEND_BASE + IPC_O_CPU2TOCPU1INTIPCSET(3U),

    //
    // CPU2 - Local core, CPU3 - Remote core,
    //
    IPC_CPU2_L_CPU3_R_CH0 = CPU2IPCSEND_BASE + IPC_O_CPU2TOCPU3INTIPCSET(0U),
    IPC_CPU2_L_CPU3_R_CH1 = CPU2IPCSEND_BASE + IPC_O_CPU2TOCPU3INTIPCSET(1U),
    IPC_CPU2_L_CPU3_R_CH2 = CPU2IPCSEND_BASE + IPC_O_CPU2TOCPU3INTIPCSET(2U),
    IPC_CPU2_L_CPU3_R_CH3 = CPU2IPCSEND_BASE + IPC_O_CPU2TOCPU3INTIPCSET(3U),

    //
    // CPU3 - Local core, CPU1 - Remote core,
    //
    IPC_CPU3_L_CPU1_R_CH0 = CPU3IPCSEND_BASE + IPC_O_CPU3TOCPU1INTIPCSET(0U),
    IPC_CPU3_L_CPU1_R_CH1 = CPU3IPCSEND_BASE + IPC_O_CPU3TOCPU1INTIPCSET(1U),
    IPC_CPU3_L_CPU1_R_CH2 = CPU3IPCSEND_BASE + IPC_O_CPU3TOCPU1INTIPCSET(2U),
    IPC_CPU3_L_CPU1_R_CH3 = CPU3IPCSEND_BASE + IPC_O_CPU3TOCPU1INTIPCSET(3U),

    //
    // CPU3 - Local core, CPU2 - Remote core,
    //
    IPC_CPU3_L_CPU2_R_CH0 = CPU3IPCSEND_BASE + IPC_O_CPU3TOCPU2INTIPCSET(0U),
    IPC_CPU3_L_CPU2_R_CH1 = CPU3IPCSEND_BASE + IPC_O_CPU3TOCPU2INTIPCSET(1U),
    IPC_CPU3_L_CPU2_R_CH2 = CPU3IPCSEND_BASE + IPC_O_CPU3TOCPU2INTIPCSET(2U),
    IPC_CPU3_L_CPU2_R_CH3 = CPU3IPCSEND_BASE + IPC_O_CPU3TOCPU2INTIPCSET(3U),

}IPC_Channel_t;


//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************


//*****************************************************************************
//
//! Local core sets Local to Remote IPC Flag
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flags is the IPC flag mask for the flags being set
//!
//! This function will allow the Local core system to set the designated IPC
//! flags to send to the Remote core system. The \e flags parameter can be any
//! of the IPC flag values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! Note that the IPC interrupt can only be triggered by IPC flag 0.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_setFlagLtoR(IPC_Channel_t ipcChannel, uint32_t flags)
{
    HWREG(IPC_REG_SET(ipcChannel)) = flags;
}

//*****************************************************************************
//
//! Local core clears Local to Remote IPC Flag
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flags is the IPC flag mask for the flags being cleared
//!
//! This function will allow the Local core system to clear the designated IPC
//! flags sent to the Remote core system. The \e flags parameter can be any
//! of the IPC flag values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_clearFlagLtoR(IPC_Channel_t ipcChannel, uint32_t flags)
{
    HWREG(IPC_REG_CLR(ipcChannel)) = flags;
}

//*****************************************************************************
//
//! Local core triggers Interrupt to Remote
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//!
//! This function will allow the Local core system to set the IPC_FLAG0 event
//! flag for the Remote core system. This will trigger interrupt in the
//! receiving CPU via the PIPE.
//!
//! Note that the IPC interrupt can only be triggered by IPC flag 0.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_triggerInterrupt(IPC_Channel_t ipcChannel)
{
    HWREG(IPC_REG_SET(ipcChannel)) = (uint32_t)IPC_FLAG0;
}

//*****************************************************************************
//
//! Local core acknowledges Remote to Local IPC Flag.
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flags is the IPC flag mask for the flags being acknowledged.
//!
//! This function will allow the Local core system to acknowledge/clear the IPC
//! flag set by the Remote core system. The \e flags parameter can be any of
//! the IPC flag values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_ackFlagRtoL(IPC_Channel_t ipcChannel, uint32_t flags)
{
    HWREG(IPC_REG_ACK(ipcChannel)) = flags;
}

//*****************************************************************************
//
//! Determines whether the given IPC flags are busy or not.
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flags is the Local to Remote IPC flag masks to check the status of
//!
//! Allows the caller to determine whether the designated Local to Remote
//! IPC flags are pending. The \e flags parameter can be any of the IPC flag
//! values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return Returns \b true if the any of the designated IPC flags are busy
//! or \b false if all the designated IPC flags are free.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
IPC_isFlagBusyLtoR(IPC_Channel_t ipcChannel, uint32_t flags)
{
    return((HWREG(IPC_REG_FLG(ipcChannel)) & flags) != 0U);
}

//*****************************************************************************
//
//! Determines whether the given Remote to Local IPC flags are busy or not.
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flags is the Remote to Local IPC Flag masks to check the status of
//!
//! Allows the caller to determine whether the designated Remote to Local
//! IPC flags are pending. The \e flags parameter can be any of the IPC flag
//! values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return Returns \b true if the any of the designated IPC flags are busy
//! or \b false if all the designated IPC flags are free.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
IPC_isFlagBusyRtoL(IPC_Channel_t ipcChannel, uint32_t flags)
{
    return((HWREG(IPC_REG_STS(ipcChannel)) & flags) != 0U);
}

//*****************************************************************************
//
//! Wait for the remote core to send a flag
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flag is the Remote to Local IPC flag mask to wait for
//!
//! Allows the caller to wait for the Remote to Local flag to be send by
//! the remote core. The \e flags parameter can be any of the IPC flag
//! values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_waitForFlag(IPC_Channel_t ipcChannel, uint32_t flag)
{
    while((HWREG(IPC_REG_STS(ipcChannel)) & flag) == 0U)
    {
    }
}

//*****************************************************************************
//
//! Wait for the IPC flag to be acknowledged
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flag is the IPC flag mask for which ack is pending
//!
//! Allows the caller to wait for the IPC flag to be acknowledged by the
//! remote core. The \e flagsparameter can be any of the IPC flag values:
//! \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_waitForAck(IPC_Channel_t ipcChannel, uint32_t flag)
{
    while((HWREG(IPC_REG_FLG(ipcChannel)) & flag) != 0U)
    {
    }
}

//*****************************************************************************
//
//! Synchronises the two cores
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flag is the IPC flag mask with which synchronisation is done
//!
//! Allows the local and remote cores to synchronise. Neither core will return
//! from this function call before the other core enters it.
//!
//! \note Must be called with same flag mask on both the cores
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_sync(IPC_Channel_t ipcChannel, uint32_t flag)
{
    IPC_setFlagLtoR(ipcChannel, flag);
    IPC_waitForFlag(ipcChannel, flag);
    IPC_ackFlagRtoL(ipcChannel, flag);
    IPC_waitForAck(ipcChannel, flag);
}

//*****************************************************************************
//
//! Initialize IPC
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//
//! This function initializes IPC by clearing all the flags
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_init(IPC_Channel_t ipcChannel)
{
    IPC_clearFlagLtoR(ipcChannel, IPC_FLAG_ALL);
}

//*****************************************************************************
//
//! Sends a command to the Remote core
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flags is the IPC flag mask for the flags to be set
//! \param command is the 32-bit command value
//! \param addr is the 32-bit address to be sent as part of command
//! \param data is the 32-bit data to be sent as part of command
//!
//! Allows the caller to send a command to the remote core. A command consists
//! of a unique command value, a 32-bit address and a 32-bit data. The function
//! also sends the designated flags to the remote core.
//!
//! The \e flags parameter can be any of the IPC flag values: \b IPC_FLAG0 -
//! \b IPC_FLAG31.
//!
//! The application shall use the function IPC_getResponse to read the response
//! sent by the remote core.
//!
//! \note The application is expected to wait until the response is
//! received before sending another command using the same channel.
//!
//! \return Returns \b true if the command is sent properly and \b false if
//! the designated flags were busy and hence command was not sent.
//
//*****************************************************************************
extern bool
IPC_sendCommand(IPC_Channel_t ipcChannel, uint32_t flags,
                uint32_t command, uint32_t addr, uint32_t data);

//*****************************************************************************
//
//! Reads a command sent by the Remote core
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param flags is the IPC flag mask for the flags sent by the remote core
//! \param command is the 32-bit pointer at which the command value is read to
//! \param addr is the 32-bit pointer at which address value is read to
//! \param data is the 32-bit pointer at which the data is read to
//!
//! Allows the caller to read a command sent by the remote core. A command
//! consists of a unique command value, a 32-bit address and a 32-bit data.
//!
//! The \e flags parameter can be any of the IPC flag values: \b IPC_FLAG0 -
//! \b IPC_FLAG31.
//!
//! \note The application is expected to acknowledge the flag and send a
//! response (if needed) after reading the command.
//!
//! \return Returns \b true if the command is read properly and \b false if
//!  the designated flags were empty and hence command was not read.
//
//*****************************************************************************
extern bool
IPC_readCommand(IPC_Channel_t ipcChannel, uint32_t flags,
                uint32_t *command, uint32_t *addr, uint32_t *data);

//*****************************************************************************
//
//! Sends the response to the command sent by remote core.
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//! \param data is the 32-bit value of the response to be sent
//!
//! Allows the caller to send a response to the command previously sent by the
//! remote core
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
IPC_sendResponse(IPC_Channel_t ipcChannel, uint32_t data)
{
    HWREG(IPC_REG_LOCALREPLY(ipcChannel)) = data;
}

//*****************************************************************************
//
//! Reads the response from the remote core.
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//!
//! Allows the caller to read the response sent by the remote core to the
//! command previously sent by the local core
//!
//! \return the 32-bit value of the response.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
IPC_getResponse(IPC_Channel_t ipcChannel)
{
    return(HWREG(IPC_REG_REMOTEREPLY(ipcChannel)));
}

//*****************************************************************************
//
//! Reads the timestamp counter value.
//!
//! \param ipcChannel is the enum corresponding to the IPC instance used
//!
//! Allows the caller to read the IPC timestamp counter value.
//!
//! \return 64-bit counter value.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint64_t
IPC_getCounter(void)
{
    //
    // Get the Counter High and Low values. Read to the Counter low register
    // saves the value of Counter High register.
    //
    uint32_t ctrL = HWREG(IPCCOUNTERREGS_BASE + IPC_O_COUNTERL);
    uint32_t ctrH = HWREG(IPCCOUNTERREGS_BASE + IPC_O_COUNTERH);

    //
    // Return the 64-bit value of the counter
    //
    return(((uint64_t)ctrH << 32U) | ((uint64_t)ctrL));
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

#endif // IPC_H
