//###########################################################################
//
// FILE:   ipc_hal.c
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
#include "ipc_hal.h"

static const Ipc_Hal_Instance_t Ipc_syncInstances[3][3] = {
                                            {0, IPC_CPU1_L_CPU2_R_CH0, IPC_CPU1_L_CPU3_R_CH0},
                                            {IPC_CPU2_L_CPU1_R_CH0, 0, IPC_CPU2_L_CPU3_R_CH0},
                                            {IPC_CPU3_L_CPU1_R_CH0, IPC_CPU3_L_CPU2_R_CH0, 0}
                                          };
//*****************************************************************************
//
// Local Function prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! Waits for a flag to be set in the IPC_REG_STS register of the given ipcInstance.
//!
//! \param ipcInstance The IPC instance to wait for the flag.
//! \param flag The flag to wait for.
//! \return Returns \b true if the flag is set within the timeout and 
//! \b false if the flag is not set within the timeout.
//
//*****************************************************************************
static bool IPC_HAL_waitForFlagTimeout(Ipc_Hal_Instance_t ipcInstance, uint32_t flag);

//*****************************************************************************
//
//! Waits for a flag to be acknowledged by the remote core.
//!
//! \param ipcInstance is the IPC instance to wait for the acknowledgement.
//! \param flag is the flag to wait for.
//! \return Returns \b true if the flag is acknowledged within the timeout and 
//! \b false if the flag is not acknowledged within the timeout.
//
//*****************************************************************************
static bool IPC_HAL_waitForAckTimeout(Ipc_Hal_Instance_t ipcInstance, uint32_t flag);

//*****************************************************************************
//
//! Finds the Rx instance index and Rx channel index for the given channel
//!
//! \param globalChannelId is the numeric id of the configured channel
//! \param instanceIndex is the pointer to the instance index in configuration structure
//! \param channelIndex is the pointer to the channel index in configuration structure
//! \return Returns \b true if the Rx instance and channel index is found and 
//! \b false if the Rx instance and channel index is not found
//
//*****************************************************************************
static bool IPC_HAL_getTxIdxPriv(Ipc_GlobalChannelId_t globalChannelId, uint8_t* instanceIndex, uint8_t* channelIndex);

//*****************************************************************************
//
//! Checks the status of an instance
//!
//! \param ipcInstance is the Tx instance for which the status is checked
//! \return Returns \b true if the Tx instance is free and 
//! \b false if the Tx instance is busy
//
//*****************************************************************************
static bool IPC_HAL_isInstanceFree(Ipc_Hal_Instance_t ipcInstance);

//*****************************************************************************
//
//! Returns the Rx polling status of the instance
//!
//! \param instanceIndex is the instance index in configuration structure
//! \param channelIndex is the pointer to the channel index in configuration structure
//! \return Returns \b true if the message is received on an Rx instance and channel and 
//! \b false if the messages are not received on the Rx instance
//
//*****************************************************************************
static bool IPC_HAL_getChannelPollingStatus(uint8_t instanceIndex, uint8_t* channelIndex);

//*****************************************************************************
//
//! Copies the data to be transmitted to the Ipc registers
//!
//! \param instanceIndex is the instance index in configuration structure
//! \param channelIndex is the channel index in configuration structure
//! \param ipcData is the pointer to a struct of type IPC_InfoType
//! \return None
//
//*****************************************************************************
static void IPC_HAL_writeChannelPriv(uint8_t instanceIndex, uint8_t channelIndex, IPC_InfoType *ipcData);

//*****************************************************************************
//
//! Copies the received data to the ipcData
//!
//! \param instanceIndex is the instance index in configuration structure
//! \param ipcData is the pointer to a struct of type IPC_InfoType where data is copied
//! \return None
//
//*****************************************************************************
static void IPC_HAL_readChannelPriv(uint8_t instanceIndex, IPC_InfoType *ipcData);

//*****************************************************************************
//
//! Acknowledges the reception of a message
//!
//! \param instanceIndex is the instance index in configuration structure
//! \return None
//
//*****************************************************************************
static void IPC_HAL_acknowledge(Ipc_Hal_Instance_t ipcInstance);

//*****************************************************************************
//
//! Finds the Rx instance index and Rx channel index for the given instance
//!
//! \param ipcInstance is the the IPC instance
//! \param instanceIndex is the pointer to the instance index in configuration structure
//! \param channelIndex is the pointer to the channel index in configuration structure
//! \return Returns \b true if Rx instance index and Rx channel index is found and 
//! \b false if Rx instance index and Rx channel index is not found
//
//*****************************************************************************
static bool IPC_HAL_GetRxIdxPriv(Ipc_Hal_Instance_t ipcInstance, uint8_t* instanceIndex, uint8_t* channelIndex);

//*****************************************************************************
//
//! Finds the Rx channel index
//!
//! \param ipcInstance is the the IPC instance
//! \param instanceIndex is the the instance index in configuration structure
//! \param channelIndex is the pointer to the channel index in configuration structure
//! \return Returns \b true if Rx channel index is found and 
//! \b false if and Rx channel index is not found
//
//*****************************************************************************
static bool IPC_HAL_GetRxChIdx(Ipc_Hal_Instance_t ipcInstance, uint8_t instanceIndex, uint8_t* channelIndex);


//*****************************************************************************
//
// Ipc_Hal_sync
//
//*****************************************************************************
bool IPC_HAL_sync(Ipc_Core_t remotecore)
{ 
    bool retVal = false;
    if((remotecore != Ipc_configuration.localCore) && (remotecore < IPC_HAL_CORE_COUNT))
    {
        Ipc_Hal_Instance_t ipcInstance = Ipc_syncInstances[Ipc_configuration.localCore][remotecore];
        uint32_t flag = IPC_HAL_SYNC_FLAG; 

        IPC_setFlagLtoR(ipcInstance, flag);
        retVal = IPC_HAL_waitForFlagTimeout(ipcInstance, flag);
        if(true == retVal)
        {
            IPC_ackFlagRtoL(ipcInstance, flag);
            retVal = IPC_HAL_waitForAckTimeout(ipcInstance, flag);
        }  

    }
    return retVal;
}

//*****************************************************************************
//
// Ipc_Hal_transmit
//
//*****************************************************************************
bool IPC_HAL_transmit(Ipc_GlobalChannelId_t globalChannelId, IPC_InfoType *ipcData) 
{
    uint8_t instanceIndex = 0U;
    uint8_t channelIndex = 0U;
    bool retVal = false;

    if(true == IPC_HAL_getTxIdxPriv(globalChannelId, &instanceIndex, &channelIndex)) 
    {
        if(true == IPC_HAL_isInstanceFree(Ipc_configuration.txInstanceConfig[instanceIndex].txInstance))
        {
            IPC_HAL_writeChannelPriv(instanceIndex, channelIndex, ipcData);
            retVal = true;
        }
    }
    return(retVal);
}

//*****************************************************************************
//
// IPC_HAL_pollInstances
//
//*****************************************************************************
void IPC_HAL_pollInstances(void)
{
    uint8_t instanceIndex;
    uint8_t channelIndex;
    IPC_InfoType ipcData;
    uint8_t dataBuffer[IPC_HAL_MAX_SIZE] = {0};
    ipcData.DataPtr = dataBuffer;

    for (uint8_t instanceIndex = 0U; instanceIndex < IPC_HAL_RX_INSTANCE_COUNT; instanceIndex++)
    {
        if(true == IPC_HAL_getChannelPollingStatus(instanceIndex, &channelIndex))
        {
            IPC_HAL_readChannelPriv(instanceIndex, &ipcData);
            IPC_HAL_acknowledge(Ipc_configuration.rxInstanceConfig[instanceIndex].rxInstance);
            if(Ipc_configuration.rxInstanceConfig[instanceIndex].rxChannelConfig[channelIndex].userCallbackFunction != NULL_PTR)
            {
                Ipc_configuration.rxInstanceConfig[instanceIndex].rxChannelConfig[channelIndex].userCallbackFunction(ipcData);
            } 
        }
    }

}

//*****************************************************************************
//
// IPC_HAL_processIsr
//
//*****************************************************************************
void IPC_HAL_processIsr(Ipc_Hal_Instance_t Instance)
{
    uint8_t channelIndex = 0U;
    uint8_t instanceIndex = 0U;
    bool status = false;
    IPC_InfoType ipcData;
    uint8_t dataBuffer[IPC_HAL_MAX_SIZE] = {0};
    ipcData.DataPtr = dataBuffer;

    if((HWREG(IPC_REG_STS(Instance)) & IPC_HAL_SYNC_FLAG) != IPC_HAL_SYNC_FLAG)
    {
        status = IPC_HAL_GetRxIdxPriv(Instance, &instanceIndex, &channelIndex);

        if(true == status)
        {
            IPC_HAL_readChannelPriv(instanceIndex, &ipcData);
            IPC_HAL_acknowledge(Instance);
            if(Ipc_configuration.rxInstanceConfig[instanceIndex].rxChannelConfig[channelIndex].userCallbackFunction != NULL_PTR)
            {
                (void)Ipc_configuration.rxInstanceConfig[instanceIndex].rxChannelConfig[channelIndex].userCallbackFunction(ipcData);
            } 
        }
    }
}

//*****************************************************************************
//
// ISR handlers
//
//*****************************************************************************
#ifdef IPC_HAL_CPU1_L_CPU2_R_INT1_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU1_L_CPU2_R_INT1_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU1_L_CPU2_R_CH0);
}
#endif

#ifdef IPC_HAL_CPU1_L_CPU2_R_INT2_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU1_L_CPU2_R_INT2_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU1_L_CPU2_R_CH1);
}
#endif

#ifdef IPC_HAL_CPU1_L_CPU2_R_INT3_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU1_L_CPU2_R_INT3_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU1_L_CPU2_R_CH2);
}
#endif

#ifdef IPC_HAL_CPU1_L_CPU2_R_INT4_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU1_L_CPU2_R_INT4_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU1_L_CPU2_R_CH3);
}
#endif

#ifdef IPC_HAL_CPU1_L_CPU3_R_INT1_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU1_L_CPU3_R_INT1_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU1_L_CPU3_R_CH0);
}
#endif

#ifdef IPC_HAL_CPU1_L_CPU3_R_INT2_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU1_L_CPU3_R_INT2_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU1_L_CPU3_R_CH1);
}
#endif

#ifdef IPC_HAL_CPU1_L_CPU3_R_INT3_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU1_L_CPU3_R_INT3_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU1_L_CPU3_R_CH2);
}
#endif

#ifdef IPC_HAL_CPU1_L_CPU3_R_INT4_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU1_L_CPU3_R_INT4_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU1_L_CPU3_R_CH3);
}
#endif

#ifdef IPC_HAL_CPU2_L_CPU1_R_INT1_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU2_L_CPU1_R_INT1_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU2_L_CPU1_R_CH0);
}
#endif

#ifdef IPC_HAL_CPU2_L_CPU1_R_INT2_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU2_L_CPU1_R_INT2_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU2_L_CPU1_R_CH1);
}
#endif

#ifdef IPC_HAL_CPU2_L_CPU1_R_INT3_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU2_L_CPU1_R_INT3_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU2_L_CPU1_R_CH2);
}
#endif

#ifdef IPC_HAL_CPU2_L_CPU1_R_INT4_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU2_L_CPU1_R_INT4_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU2_L_CPU1_R_CH3);
}
#endif

#ifdef IPC_HAL_CPU2_L_CPU3_R_INT1_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU2_L_CPU3_R_INT1_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU2_L_CPU3_R_CH0);
}
#endif

#ifdef IPC_HAL_CPU2_L_CPU3_R_INT2_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU2_L_CPU3_R_INT2_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU2_L_CPU3_R_CH1);
}
#endif

#ifdef IPC_HAL_CPU2_L_CPU3_R_INT3_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU2_L_CPU3_R_INT3_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU2_L_CPU3_R_CH2);
}
#endif

#ifdef IPC_HAL_CPU2_L_CPU3_R_INT4_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU2_L_CPU3_R_INT4_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU2_L_CPU3_R_CH3);
}
#endif

#ifdef IPC_HAL_CPU3_L_CPU1_R_INT1_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU3_L_CPU1_R_INT1_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU3_L_CPU1_R_CH0);
}
#endif

#ifdef IPC_HAL_CPU3_L_CPU1_R_INT2_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU3_L_CPU1_R_INT2_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU3_L_CPU1_R_CH1);
}
#endif

#ifdef IPC_HAL_CPU3_L_CPU1_R_INT3_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU3_L_CPU1_R_INT3_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU3_L_CPU1_R_CH2);
}
#endif

#ifdef IPC_HAL_CPU3_L_CPU1_R_INT4_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU3_L_CPU1_R_INT4_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU3_L_CPU1_R_CH3);
}
#endif

#ifdef IPC_HAL_CPU3_L_CPU2_R_INT1_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU3_L_CPU2_R_INT1_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU3_L_CPU2_R_CH0);
}
#endif

#ifdef IPC_HAL_CPU3_L_CPU2_R_INT2_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU3_L_CPU2_R_INT2_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU3_L_CPU2_R_CH1);
}
#endif

#ifdef IPC_HAL_CPU3_L_CPU2_R_INT3_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU3_L_CPU2_R_INT3_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU3_L_CPU2_R_CH2);
}
#endif

#ifdef IPC_HAL_CPU3_L_CPU2_R_INT4_ISR_ENABLE
__attribute__((interrupt("INT"))) void IPC_HAL_CPU3_L_CPU2_R_INT4_ISR(void)
{
    IPC_HAL_processIsr(IPC_CPU3_L_CPU2_R_CH3);
}
#endif

//*****************************************************************************
//
// Local Function definitions
//
//*****************************************************************************

static bool IPC_HAL_waitForFlagTimeout(Ipc_Hal_Instance_t ipcInstance, uint32_t flag)
{
    bool retVal = true;
    uint64_t elapsedCount;
    uint64_t startCount = IPC_getCounter();
    while((HWREG(IPC_REG_STS(ipcInstance)) & flag) == 0U) 
    {
        elapsedCount = IPC_getCounter() - startCount;
        if(IPC_HAL_CFG_TIMEOUT_CLOCK_CYCLES <= elapsedCount)
        {
            retVal = false;
            break;
        }
    }
    return retVal;
}

static bool IPC_HAL_waitForAckTimeout(Ipc_Hal_Instance_t ipcInstance, uint32_t flag)
{
    bool retVal = true;
    uint64_t elapsedCount;
    uint64_t startCount = IPC_getCounter();
    while((HWREG(IPC_REG_FLG(ipcInstance)) & flag) != 0U)
    {
        elapsedCount = IPC_getCounter() - startCount;
        if(IPC_HAL_CFG_TIMEOUT_CLOCK_CYCLES <= elapsedCount)
        {
            retVal = false;
            break;
        }
    }
    return retVal;
}

static bool IPC_HAL_isInstanceFree(Ipc_Hal_Instance_t ipcInstance)
{
    if(HWREG(IPC_REG_FLG(ipcInstance)) != 0U)
    {
        return false;
    }
    else
    {
        return true;
    }
}

static bool IPC_HAL_getTxIdxPriv(Ipc_GlobalChannelId_t globalChannelId, uint8_t* instanceIndex, uint8_t* channelIndex)
{
    bool retVal = false;
    uint8_t instanceIdx = 0U;
    uint8_t channelIdx = 0U;

    for (instanceIdx = 0U; instanceIdx < IPC_HAL_TX_INSTANCE_COUNT; instanceIdx++)
    {
       for(channelIdx = 0U;
           channelIdx < Ipc_configuration.txInstanceConfig[instanceIdx].txChannelCount; 
           channelIdx++)
        {
            if(globalChannelId == 
                Ipc_configuration.txInstanceConfig[instanceIdx].txChannelConfig[channelIdx]
                .globalChannelIdentifier)
            {
                *instanceIndex = instanceIdx;
                *channelIndex = channelIdx;
                retVal = true;
                break;
            }
        }
        if(true == retVal)
        {
            break;       
        }
    } 

    return retVal;

}

static bool IPC_HAL_getChannelPollingStatus(uint8_t instanceIndex, uint8_t* channelIndex)
{
    bool retVal = false;
    uint8_t channel = 0U;
    uint32_t status = HWREG(IPC_REG_STS(Ipc_configuration.rxInstanceConfig[instanceIndex].rxInstance));
    uint8_t channelIdx = 0U;

    if(((status & IPC_HAL_POLL_FLAG) == IPC_HAL_POLL_FLAG) && (((status & (IPC_HAL_SYNC_FLAG | IPC_HAL_INTR_FLAG)) == 0U)))
    {
        channel = (status >> IPC_HAL_CHANNELINDEX) & BIT_MASK_EIGHT;

        for(channelIdx = 0U; 
            channelIdx < Ipc_configuration.rxInstanceConfig[instanceIndex].rxChannelCount; 
            channelIdx++)
        {
            if(channel == Ipc_configuration.rxInstanceConfig[instanceIndex].rxChannelConfig[channelIdx].channelId)
            {
                *channelIndex = channelIdx;
                retVal = true;
                break;
            }
        }
        if(false == retVal)
        {
            IPC_HAL_acknowledge(Ipc_configuration.rxInstanceConfig[instanceIndex].rxInstance);
        }
    }

    return(retVal);

}

static void IPC_HAL_writeChannelPriv(uint8_t instanceIndex, uint8_t channelIndex, IPC_InfoType *ipcData)
{
    uint8_t byteCnt = 0U;
    uint32_t flags = 0U;
    uint32_t command = 0U;
    uint32_t addr = 0U;
    uint32_t data = 0U;

    for(byteCnt = 0U; (byteCnt < (uint8_t)ipcData->Length) && (byteCnt < IPC_HAL_MAX_SIZE); byteCnt++)
    {
        if(byteCnt < IPC_HAL_COMMBYTE)
        {
            // Calculate the command value
            command |= (ipcData->DataPtr[byteCnt] << (8 * (byteCnt % IPC_HAL_COMMANDSIZE)));
        }
        else if((byteCnt >= IPC_HAL_COMMBYTE) && (byteCnt < IPC_HAL_ADDRBYTE))
        {
            // Calculate the address value
            addr |= (ipcData->DataPtr[byteCnt] << (8 * ((byteCnt - IPC_HAL_COMMBYTE) % IPC_HAL_COMMANDSIZE)));
        }
        else
        {
            // Calculate the data value
            data |= (ipcData->DataPtr[byteCnt] << (8 * ((byteCnt - IPC_HAL_ADDRBYTE) % IPC_HAL_COMMANDSIZE)));
        }
    }

    HWREG(IPC_REG_SENDCOM(Ipc_configuration.txInstanceConfig[instanceIndex].txInstance)) = command;
    HWREG(IPC_REG_SENDADDR(Ipc_configuration.txInstanceConfig[instanceIndex].txInstance)) = addr;
    HWREG(IPC_REG_SENDDATA(Ipc_configuration.txInstanceConfig[instanceIndex].txInstance)) = data;


    // Flags to indicate the Tx processing type
    if (Ipc_configuration.txInstanceConfig[instanceIndex].txChannelConfig[channelIndex].txProcessing == IPC_INTERRUPT) 
    { 
        flags = flags | IPC_HAL_INTR_FLAG;
    }
    else 
    { 
        flags = flags | IPC_HAL_POLL_FLAG;
    }

    // Flags to indicate the Channel ID
    flags = flags | ((Ipc_configuration.txInstanceConfig[instanceIndex].txChannelConfig[channelIndex].channelId) << IPC_HAL_CHANNELINDEX);

    // Flags to indicate the length
    flags = flags | ((uint32_t)(ipcData->Length) << IPC_HAL_LENGTHINDEX);

    HWREG(Ipc_configuration.txInstanceConfig[instanceIndex].txInstance) = flags;

}

static void IPC_HAL_readChannelPriv(uint8_t instanceIndex, IPC_InfoType *ipcData)
{
    uint32_t flags = (uint32_t)0U;
    uint8_t length = (uint8_t)0U;
    uint8_t byteCnt = (uint8_t)0U;
    uint32_t commandValue = 0U;
    uint32_t addrValue = 0U;
    uint32_t dataValue = 0U;

    flags = HWREG(IPC_REG_STS(Ipc_configuration.rxInstanceConfig[instanceIndex].rxInstance));
    length = (flags >> IPC_HAL_LENGTHINDEX) & BIT_MASK_FOUR;
    ipcData->Length = (length > IPC_HAL_MAX_SIZE) ? IPC_HAL_MAX_SIZE : length;

    commandValue = HWREG(IPC_REG_RECVCOM(Ipc_configuration.rxInstanceConfig[instanceIndex].rxInstance));
    addrValue = HWREG(IPC_REG_RECVADDR(Ipc_configuration.rxInstanceConfig[instanceIndex].rxInstance));
    dataValue = HWREG(IPC_REG_RECVDATA(Ipc_configuration.rxInstanceConfig[instanceIndex].rxInstance));

    for(byteCnt = 0U; (byteCnt < ipcData->Length); byteCnt++)
    {
        if(byteCnt < IPC_HAL_COMMBYTE)
        {
           ipcData->DataPtr[byteCnt] = (uint8_t)((commandValue >> (8U * (byteCnt % IPC_HAL_COMMANDSIZE))) & 0xFFU);
        }
        else if((byteCnt >= IPC_HAL_COMMBYTE) && (byteCnt < IPC_HAL_ADDRBYTE))
        {
            ipcData->DataPtr[byteCnt] = (uint8_t)((addrValue >> (8U * ((byteCnt - IPC_HAL_COMMBYTE) % IPC_HAL_COMMANDSIZE))) & 0xFFU);
        }
        else
        {
            ipcData->DataPtr[byteCnt] = (uint8_t)((dataValue >> (8U * ((byteCnt - IPC_HAL_ADDRBYTE) % IPC_HAL_COMMANDSIZE))) & 0xFFU);
        }
     }

}

static void IPC_HAL_acknowledge(Ipc_Hal_Instance_t ipcInstance)
{
    uint32_t status = HWREG(IPC_REG_STS(ipcInstance));
    HWREG(IPC_REG_ACK(ipcInstance)) = status;
}

static bool IPC_HAL_GetRxIdxPriv(Ipc_Hal_Instance_t ipcInstance, uint8_t* instanceIndex, uint8_t* channelIndex)
{
    bool retVal = false;
    uint8_t instanceIdx = 0U;

    for (instanceIdx = 0U; instanceIdx < IPC_HAL_RX_INSTANCE_COUNT; instanceIdx++)
    {
        if(ipcInstance == Ipc_configuration.rxInstanceConfig[instanceIdx].rxInstance)
        {
            retVal = IPC_HAL_GetRxChIdx(ipcInstance, instanceIdx, channelIndex);
            if(true == retVal)
            {
                *instanceIndex = instanceIdx;
                break;       
            }
        }
    }
    if(false == retVal)
    {
        IPC_HAL_acknowledge(ipcInstance);
    }  

    return retVal;
}

static bool IPC_HAL_GetRxChIdx(Ipc_Hal_Instance_t ipcInstance, uint8_t instanceIndex, uint8_t* channelIndex)
{
    bool retVal = false;
    uint8_t channelIdx = 0U;
    uint8_t channel = ((HWREG(IPC_REG_STS(ipcInstance))) >> IPC_HAL_CHANNELINDEX) & BIT_MASK_EIGHT;

    for(channelIdx = 0; 
        channelIdx < Ipc_configuration.rxInstanceConfig[instanceIndex].rxChannelCount; 
        channelIdx++)
    {
        if(channel == Ipc_configuration.rxInstanceConfig[instanceIndex]
            .rxChannelConfig[channelIdx].channelId)
        {
            *channelIndex = channelIdx;
            retVal = true;
            break;
        }
    }

    return retVal;
}