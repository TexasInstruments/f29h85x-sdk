//###########################################################################
//
// FILE:   erroraggregator.h
//
// TITLE:  C29x Error Aggregator driver.
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

#ifndef ERRORAGGREGATOR_H
#define ERRORAGGREGATOR_H

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
#include "inc/hw_error_aggregator.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Values that are used in ErrorAggregator_getCpuErrorInfo() and
// ErrorAggregator_clearCpuError()
//
//*****************************************************************************
#define ERROR_AGGREGATOR_CPU_REG_OFFSET     (ERROR_AGGREGATOR_O_CPU2_PR_HIGHPRIO_ERROR_ADDRESS - ERROR_AGGREGATOR_O_CPU1_PR_HIGHPRIO_ERROR_ADDRESS)

//*****************************************************************************
//
// Values that are used in ErrorAggregator_getRtdmaErrorInfo() and
// ErrorAggregator_clearRtdmaError()
//
//*****************************************************************************
#define ERROR_AGGREGATOR_RTDMA_REG_OFFSET   (ERROR_AGGREGATOR_O_RTDMA2_DR_HIGHPRIO_ERROR_ADDRESS - ERROR_AGGREGATOR_O_RTDMA1_DR_HIGHPRIO_ERROR_ADDRESS)

//*****************************************************************************
//
//! Error Aggregator CPU error source.
//
//*****************************************************************************
typedef enum
{
    EA_SRC_CPU1 = 0x0U,     //! Error source is CPU1
    EA_SRC_CPU2 = 0x1U,     //! Error source is CPU2
    EA_SRC_CPU3 = 0x2U      //! Error source is CPU3
}ErrorAggregator_SourceCpu;

//*****************************************************************************
//
//! Error Aggregator RTDMA error source.
//
//*****************************************************************************
typedef enum
{
    EA_SRC_RTDMA1 = 0x0U,   //! Error source is RTDMA1
    EA_SRC_RTDMA2 = 0x1U    //! Error source is RTDMA2
}ErrorAggregator_SourceRtdma;

//*****************************************************************************
//
//! Error Aggregator error information structure.
//
//*****************************************************************************
typedef struct
{
    //! High priority error address.
    uint32_t    highPriErrAddr;
    //! Low priority error address.
    uint32_t    lowPriErrAddr;
    //! Error Type.
    uint32_t    errorType;
    //! PC address.
    uint32_t    pcAddr;
}ErrorAggregator_ErrorInfo;

//*****************************************************************************
//
//! Error Aggregator error information structure for CPU source.
//
//*****************************************************************************
typedef struct
{
    //! PR error info.
    ErrorAggregator_ErrorInfo    pr;
    //! DR1 error info.
    ErrorAggregator_ErrorInfo    dr1;
    //! DR2 error info.
    ErrorAggregator_ErrorInfo    dr2;
    //! DW error info.
    ErrorAggregator_ErrorInfo    dw;
    //! INT error info.
    ErrorAggregator_ErrorInfo    interrupt;
}ErrorAggregator_CpuErrorInfo;

//*****************************************************************************
//
//! Error Aggregator error information structure for RTDMA source.
//
//*****************************************************************************
typedef struct
{
    //! DR error info.
    ErrorAggregator_ErrorInfo    dr;
    //! DW error info.
    ErrorAggregator_ErrorInfo    dw;
}ErrorAggregator_RtdmaErrorInfo;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an ErrorAggregator module base address.
//!
//! \param base specifies the ErrorAggregator base address.
//!
//! This function determines if a ErrorAggregator address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
__attribute__((always_inline))
static inline bool
ErrorAggregator_isBaseValid(uint32_t base)
{
    return((base & BASE_ADDR_MASK) == ERRORAGGREGATOR_BASE_FRAME(0U));
}
#endif


//*****************************************************************************
//
//! Get CPU error information
//!
//! \param base is the base address of the Error Aggregator instance.
//! \param cpuId is the CPU id.
//! \param cpuErrorInfo is the pointer to the CPU error info structure
//!
//! This function fetces the CPU error information
//!
//! \return None.
//
//*****************************************************************************
extern void
ErrorAggregator_getCpuErrorInfo(
                            uint32_t base,
                            ErrorAggregator_SourceCpu cpuId,
                            ErrorAggregator_CpuErrorInfo *cpuErrorInfo);

//*****************************************************************************
//
//! Get RTDMA error information
//!
//! \param base is the base address of the Error Aggregator instance.
//! \param cpuId is the RTDMA id.
//! \param rtdmaErrorInfo is the pointer to the RTDMA error info structure
//!
//! This function fetces the RTDMA error information
//!
//! \return None.
//
//*****************************************************************************
extern void
ErrorAggregator_getRtdmaErrorInfo(
                            uint32_t base,
                            ErrorAggregator_SourceRtdma rtdmaId,
                            ErrorAggregator_RtdmaErrorInfo *rtdmaErrorInfo);

//*****************************************************************************
//
//! Get SSU error information
//!
//! \param base is the base address of the Error Aggregator instance.
//! \param ssuErrorInfo is the pointer to the SSU error info structure
//!
//! This function fetces the SSU error information
//!
//! \return None.
//
//*****************************************************************************
extern void
ErrorAggregator_getSsuErrorInfo(
                            uint32_t base,
                            ErrorAggregator_ErrorInfo *ssuErrorInfo);

//*****************************************************************************
//
//! Get Ethercat error information
//!
//! \param base is the base address of the Error Aggregator instance.
//! \param ethercatErrorInfo is the pointer to the Ethercat error info structure
//!
//! This function fetces the Ethercat error information
//!
//! \return None.
//
//*****************************************************************************
extern void
ErrorAggregator_getEthercatErrorInfo(
                            uint32_t base,
                            ErrorAggregator_ErrorInfo *ethercatErrorInfo);

//*****************************************************************************
//
//! Clear CPU error information
//!
//! \param base is the base address of the Error Aggregator instance.
//! \param cpuId is the CPU id for which errors are cleared
//!
//! This function clears CPU errors
//!
//! \return None.
//
//*****************************************************************************
extern void
ErrorAggregator_clearCpuError(uint32_t base, ErrorAggregator_SourceCpu cpuId);

//*****************************************************************************
//
//! Clear RTDMA error information
//!
//! \param base is the base address of the Error Aggregator instance.
//! \param rtdmaId is the RTDMA id for which errors are cleared
//!
//! This function clears RTDMA errors
//!
//! \return None.
//
//*****************************************************************************
extern void
ErrorAggregator_clearRtdmaError(uint32_t base, ErrorAggregator_SourceRtdma rtdmaId);

//*****************************************************************************
//
//! Clear SSU error information
//!
//! \param base is the base address of the Error Aggregator instance.
//!
//! This function clears SSU errors
//!
//! \return None.
//
//*****************************************************************************
extern void
ErrorAggregator_clearSsuError(uint32_t base);

//*****************************************************************************
//
//! Clear Ethercat error information
//!
//! \param base is the base address of the Error Aggregator instance.
//!
//! This function clears Ethercat errors
//!
//! \return None.
//
//*****************************************************************************
extern void
ErrorAggregator_clearEthercatError(uint32_t base);


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

#endif // ERRORAGGREGATOR_H