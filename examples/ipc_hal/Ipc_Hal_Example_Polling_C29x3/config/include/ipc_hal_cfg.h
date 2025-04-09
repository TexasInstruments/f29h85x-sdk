//###########################################################################
//
// FILE:   ipc_hal_cfg.h
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

#ifndef IPC_HAL_CFG_H
#define IPC_HAL_CFG_H

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
// Exported Preprocessor #define Constants
//*****************************************************************************
/** \brief Macro to define the number of Tx instances configured */
#define IPC_HAL_TX_INSTANCE_COUNT                   (1U)

/** \brief Macro to define the number of Rx instances configured */
#define IPC_HAL_RX_INSTANCE_COUNT                   (1U)

 /** \brief Macro to define the maximum number of Tx channels configured per instance */
#define IPC_HAL_TX_CHANNEL_COUNT         1U

 /** \brief Macro to define the maximum number of Rx channels configured per instance */
#define IPC_HAL_RX_CHANNEL_COUNT         1U

/** \brief Cdd Ipc Sync timeout, units is clock cycles. */
#define IPC_HAL_CFG_TIMEOUT_CLOCK_CYCLES    ((2000000000U))

//*****************************************************************************
// Symbolic names for the Tx channels
//*****************************************************************************
#define IPC_HAL_TX_CH1    1

//*****************************************************************************
// Symbolic names for the Rx channels
//*****************************************************************************
#define IPC_HAL_RX_CH1    1

/*********************************************************************************************************************
 * Exported Object Declarations
 *********************************************************************************************************************/
/* Cdd Ipc Configuration struct extern declaration */
extern const struct IPC_ConfigTag Ipc_configuration;

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // IPC_HAL_CFG_H
