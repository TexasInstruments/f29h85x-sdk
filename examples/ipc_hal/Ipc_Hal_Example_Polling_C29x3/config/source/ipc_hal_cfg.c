//###########################################################################
//
// FILE:   ipc_hal_cfg.c
//
// TITLE:  C29x IPC Hardware Abstraction Layer Configurations.
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


extern void Ipc_Hal_exampleUserCallbackFunction(const IPC_InfoType ipcData);

//*****************************************************************************
// Configuration structure
//*****************************************************************************
/** \brief Ipc Configuration */
const struct IPC_ConfigTag Ipc_configuration =
{
    .localCore = Ipc_Cpu3,

    .txInstanceConfig = 
     {
        {
            .txInstance = IPC_CPU3_L_CPU1_R_CH1,
            .txChannelCount = 1U,
            .txChannelConfig = 
                {
                    {
                        .channelId = 2U,
                        .txProcessing = IPC_POLLING,
                        .globalChannelIdentifier = IPC_HAL_TX_CH1,
                    },
                }
        },
     },

    .rxInstanceConfig = 
    {
        {
            .rxInstance = IPC_CPU3_L_CPU1_R_CH0,
            .rxChannelCount = 1U,
            .rxChannelConfig = 
                 {
                    {
                        .channelId = 1U,
                        .userCallbackFunction = (Ipc_Notify_t)Ipc_Hal_exampleUserCallbackFunction,
                        .globalChannelIdentifier = IPC_HAL_RX_CH1,
                    },
                }
        },
    },
};
