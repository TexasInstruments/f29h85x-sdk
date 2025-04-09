//###########################################################################
//
// FILE:   ipc_hal.h
//
// TITLE:  C29x IPC Hardware Abstraction Layer.
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

#ifndef IPC_HAL_H
#define IPC_HAL_H

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

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ipc.h"
#include "ipc.h"
#include "ipc_hal_cfg.h"

//*****************************************************************************
//
// Defines for the APIs
//
//*****************************************************************************
typedef uint16_t Ipc_GlobalChannelId_t;

typedef IPC_Channel_t Ipc_Hal_Instance_t;

/** \brief IPC Tx processing */
typedef enum
{
    IPC_POLLING = 1U,              /*!< \brief  Polling mode*/
    IPC_INTERRUPT  = 2U            /*!< \brief  Interrupt mode*/
}Ipc_TxProcessingType;

typedef struct
{
   uint8_t *DataPtr; /* Payload.*/
   uint8_t Length; /* Length of data.*/

} IPC_InfoType;

/** \brief  Notification callback function pointer. */
typedef void (*Ipc_Notify_t)(IPC_InfoType ipcData);


/** \brief IPC Tx channel config type */
typedef struct
{
    /** \brief  Tx channel ID specific to the instance */
    uint8_t channelId;    
    /** \brief  Tx processing */
    Ipc_TxProcessingType txProcessing;  
    /** \brief Cdd Ipc Global Channel ID */
    Ipc_GlobalChannelId_t globalChannelIdentifier;
}IPC_TxChannelConfigType;

/** \brief IPC Tx instance config type */
typedef struct
{
    /** \brief  Tx instance */    
    Ipc_Hal_Instance_t txInstance;
    /** \brief  No. of channels configured in the instance */    
    uint8_t txChannelCount;
    /** \brief IPC Tx channel configurations */
    IPC_TxChannelConfigType txChannelConfig[IPC_HAL_TX_CHANNEL_COUNT];    
}IPC_TxInstanceConfigType;

/** \brief IPC Rx channel config type */
typedef struct Ipc_RxChannelConfigTag
{
    /** \brief  Rx channel ID specific to the instance */
    uint8_t channelId;    
    /** \brief User call back function */
    Ipc_Notify_t userCallbackFunction;
    /** \brief Cdd Ipc Global Channel ID */
    Ipc_GlobalChannelId_t globalChannelIdentifier;
}IPC_RxChannelConfigType;

/** \brief IPC Rx instance config type */
typedef struct Ipc_RxInstanceConfigTag
{
    /** \brief  Rx instance */    
    Ipc_Hal_Instance_t rxInstance;
    /** \brief  No. of channels configured in the instance */    
    uint8_t rxChannelCount;
    /** \brief IPC Rx channel configurations */
    IPC_RxChannelConfigType rxChannelConfig[IPC_HAL_RX_CHANNEL_COUNT];    
}IPC_RxInstanceConfigType;

/** \brief IPC config type */
typedef struct IPC_ConfigTag
{
    /** \brief  Local core in the IPC communication */    
    uint8_t localCore;
    /** \brief  Tx channel configurations */
    IPC_TxInstanceConfigType txInstanceConfig[IPC_HAL_TX_INSTANCE_COUNT];    
    /** \brief  Rx channel configurations */
    IPC_RxInstanceConfigType rxInstanceConfig[IPC_HAL_RX_INSTANCE_COUNT];  
}IPC_ConfigType;

typedef enum
{
    Ipc_Cpu1 = 0U,              /*!< \brief  CPU1 */
    Ipc_Cpu2 = 1U,              /*!< \brief  CPU2 */
    Ipc_Cpu3 = 2U,              /*!< \brief  CPU3*/
}Ipc_Core_t;

/** \brief Macro to define the index of channel ID in flag register */
#define IPC_HAL_CHANNELINDEX    16U
/** \brief Macro to define the index of length in flag register */
#define IPC_HAL_LENGTHINDEX     24U
/** \brief Bit mask for last 8 bits */
#define BIT_MASK_EIGHT      0xFFU
/** \brief Bit mask for last 4 bits */
#define BIT_MASK_FOUR       0x0FU
/** \brief Shift bits by 8 bits */
#define BIT_SHIFT_BY_8      8U
/** \brief Interrupt flag */
#define IPC_HAL_INTR_FLAG      IPC_FLAG0
/** \brief Polling flag */
#define IPC_HAL_POLL_FLAG      IPC_FLAG1
/** \brief Syncronization flag */
#define IPC_HAL_SYNC_FLAG      IPC_FLAG2
/** \brief Macro to define the max no of bytes that can be transmitted or received */
#define IPC_HAL_MAX_SIZE                          12U
/** \brief Macro to define the upper byte index that can be transmitted/received in command register */
#define IPC_HAL_COMMBYTE                          4U
/** \brief Macro to define the upper byte index that can be transmitted/received in address register */
#define IPC_HAL_ADDRBYTE                          8U
/** \brief Macro to define the upper byte index that can be transmitted/received in address register */
#define IPC_HAL_DATABYTE                          12U
/** \brief Macro to define the no of bytes that can be written to a command register */
#define IPC_HAL_COMMANDSIZE                       4U
/** \brief Macro to define the number of core */
#define IPC_HAL_CORE_COUNT                        3U

#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
//*****************************************************************************
//
//! Synchronises the local core with the remote core.
//!
//! \param remotecore is the enum corresponding to the IPC remote core that needs to be synchronized with
//!
//! \return Returns \b true if the synchronization is successful within the preconfigured timeout time and 
//! \b false if the synchronization is not successful within the preconfigured timeout time.
//
//*****************************************************************************
bool IPC_HAL_sync(Ipc_Core_t remotecore);

//*****************************************************************************
//
//! Transmits the data to the remote core in the given channel.
//!
//! \param globalChannelId is the numeric id of the configured channel in which data needs to be transmitted
//! \param ipcData is the pointer to a struct of type IPC_InfoType containing the complete data to be transmitted
//!
//! \return Returns \b true if the transmit request is accepted 
//! \b false if the transmit request is rejected
//
//*****************************************************************************
bool IPC_HAL_transmit(Ipc_GlobalChannelId_t globalChannelId, IPC_InfoType *ipcData);

//*****************************************************************************
//
//! Polls the configured Rx instances.
//!
//! \param None
//! \return None
//*****************************************************************************
void IPC_HAL_pollInstances(void);

//*****************************************************************************
//
//! Invoked by the respective IPC instance ISR
//!
//! \param Instance is the IPC instance
//! \return None
//*****************************************************************************
void IPC_HAL_processIsr(Ipc_Hal_Instance_t Instance);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // IPC_HAL_H
