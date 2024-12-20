//###########################################################################
//
// FILE:   erroraggregator.c
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


#include "erroraggregator.h"

//*****************************************************************************
//
// ErrorAggregator_getCpuErrorInfo
//
//*****************************************************************************
void ErrorAggregator_getCpuErrorInfo(
                            uint32_t base,
                            ErrorAggregator_SourceCpu cpuId,
                            ErrorAggregator_CpuErrorInfo *cpuErrorInfo)
{
    uint32_t cpuBaseAddr;
    //
    // Check the arguments
    //
    ASSERT(ErrorAggregator_isBaseValid(base));
    ASSERT((EA_SRC_CPU1 == cpuId) || (EA_SRC_CPU2 == cpuId) || (EA_SRC_CPU3 == cpuId));
    ASSERT(NULL != cpuErrorInfo);

    //
    //  Populate the CPUx error info
    //
    cpuBaseAddr = base + (cpuId * ERROR_AGGREGATOR_CPU_REG_OFFSET);
    //
    //  PR
    //
    cpuErrorInfo->pr.highPriErrAddr         = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_PR_HIGHPRIO_ERROR_ADDRESS);
    cpuErrorInfo->pr.lowPriErrAddr          = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_PR_LOWPRIO_ERROR_ADDRESS);
    cpuErrorInfo->pr.errorType              = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_PR_ERROR_TYPE);
    cpuErrorInfo->pr.pcAddr                 = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_PR_PC);
    //
    //  DR1
    //
    cpuErrorInfo->dr1.highPriErrAddr        = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR1_HIGHPRIO_ERROR_ADDRESS);
    cpuErrorInfo->dr1.lowPriErrAddr         = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR1_LOWPRIO_ERROR_ADDRESS);
    cpuErrorInfo->dr1.errorType             = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR1_ERROR_TYPE);
    cpuErrorInfo->dr1.pcAddr                = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR1_PC);
    //
    //  DR2
    //
    cpuErrorInfo->dr2.highPriErrAddr        = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR2_HIGHPRIO_ERROR_ADDRESS);
    cpuErrorInfo->dr2.lowPriErrAddr         = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR2_LOWPRIO_ERROR_ADDRESS);
    cpuErrorInfo->dr2.errorType             = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR2_ERROR_TYPE);
    cpuErrorInfo->dr2.pcAddr                = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR2_PC);
    //
    //  DW
    //
    cpuErrorInfo->dw.highPriErrAddr         = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DW_HIGHPRIO_ERROR_ADDRESS);
    cpuErrorInfo->dw.lowPriErrAddr          = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DW_LOWPRIO_ERROR_ADDRESS);
    cpuErrorInfo->dw.errorType              = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DW_ERROR_TYPE);
    cpuErrorInfo->dw.pcAddr                 = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DW_PC);
    //
    //  INT
    //
    cpuErrorInfo->interrupt.highPriErrAddr  = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_INT_HIGHPRIO_ERROR_ADDRESS);
    cpuErrorInfo->interrupt.lowPriErrAddr   = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_INT_LOWPRIO_ERROR_ADDRESS);
    cpuErrorInfo->interrupt.errorType       = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_INT_ERROR_TYPE);
    cpuErrorInfo->interrupt.pcAddr          = HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_INT_PC);
}

//*****************************************************************************
//
// ErrorAggregator_getRtdmaErrorInfo
//
//*****************************************************************************
void ErrorAggregator_getRtdmaErrorInfo(
                            uint32_t base,
                            ErrorAggregator_SourceRtdma rtdmaId,
                            ErrorAggregator_RtdmaErrorInfo *rtdmaErrorInfo)
{
    uint32_t rtdmaBaseAddr;
    //
    // Check the arguments
    //
    ASSERT(ErrorAggregator_isBaseValid(base));
    ASSERT((EA_SRC_RTDMA1 == rtdmaId) || (EA_SRC_RTDMA2 == rtdmaId));
    ASSERT(NULL != rtdmaErrorInfo);

    //
    //  Populate the RTDMAx error info
    //
    rtdmaBaseAddr = base + (rtdmaId * ERROR_AGGREGATOR_RTDMA_REG_OFFSET);
    //
    //  DR
    //
    rtdmaErrorInfo->dr.highPriErrAddr       = HWREG(rtdmaBaseAddr + ERROR_AGGREGATOR_O_RTDMA1_DR_HIGHPRIO_ERROR_ADDRESS);
    rtdmaErrorInfo->dr.lowPriErrAddr        = HWREG(rtdmaBaseAddr + ERROR_AGGREGATOR_O_RTDMA1_DR_LOWPRIO_ERROR_ADDRESS);
    rtdmaErrorInfo->dr.errorType            = HWREG(rtdmaBaseAddr + ERROR_AGGREGATOR_O_RTDMA1_DR_ERROR_TYPE);
    rtdmaErrorInfo->dr.pcAddr               = 0x00000000U;
    //
    //  DW
    //
    rtdmaErrorInfo->dw.highPriErrAddr       = HWREG(rtdmaBaseAddr + ERROR_AGGREGATOR_O_RTDMA1_DW_HIGHPRIO_ERROR_ADDRESS);
    rtdmaErrorInfo->dw.lowPriErrAddr        = HWREG(rtdmaBaseAddr + ERROR_AGGREGATOR_O_RTDMA1_DW_LOWPRIO_ERROR_ADDRESS);
    rtdmaErrorInfo->dw.errorType            = HWREG(rtdmaBaseAddr + ERROR_AGGREGATOR_O_RTDMA1_DW_ERROR_TYPE);
    rtdmaErrorInfo->dw.pcAddr               = 0x00000000U;
}

//*****************************************************************************
//
// ErrorAggregator_getSsuErrorInfo
//
//*****************************************************************************
void ErrorAggregator_getSsuErrorInfo(
                            uint32_t base,
                            ErrorAggregator_ErrorInfo *ssuErrorInfo)
{
    //
    // Check the arguments
    //
    ASSERT(ErrorAggregator_isBaseValid(base));
    ASSERT(NULL != ssuErrorInfo);

    //
    //  Populate the SSU error info
    //
    ssuErrorInfo->highPriErrAddr            = HWREG(base + ERROR_AGGREGATOR_O_SSU_HIGHPRIO_ERROR_ADDRESS);
    ssuErrorInfo->lowPriErrAddr             = 0x00000000U;
    ssuErrorInfo->errorType                 = HWREG(base + ERROR_AGGREGATOR_O_SSU_ERROR_TYPE);
    ssuErrorInfo->pcAddr                    = 0x00000000U;
}

//*****************************************************************************
//
// ErrorAggregator_getEthercatErrorInfo
//
//*****************************************************************************
void ErrorAggregator_getEthercatErrorInfo(
                            uint32_t base,
                            ErrorAggregator_ErrorInfo *ethercatErrorInfo)
{
    //
    // Check the arguments
    //
    ASSERT(ErrorAggregator_isBaseValid(base));
    ASSERT(NULL != ethercatErrorInfo);

    //
    //  Populate the Ethercat error info
    //
    ethercatErrorInfo->highPriErrAddr       = HWREG(base + ERROR_AGGREGATOR_O_ETHERCAT_HIGHPRIO_ERROR_ADDRESS);
    ethercatErrorInfo->lowPriErrAddr        = 0x00000000U;
    ethercatErrorInfo->errorType            = HWREG(base + ERROR_AGGREGATOR_O_ETHERCAT_ERROR_TYPE);
    ethercatErrorInfo->pcAddr               = 0x00000000U;
}

//*****************************************************************************
//
// ErrorAggregator_clearCpuError
//
//*****************************************************************************
void ErrorAggregator_clearCpuError(uint32_t base, ErrorAggregator_SourceCpu cpuId)
{
    uint32_t cpuBaseAddr;
    //
    // Check the arguments
    //
    ASSERT(ErrorAggregator_isBaseValid(base));
    ASSERT((EA_SRC_CPU1 == cpuId) || (EA_SRC_CPU2 == cpuId) || (EA_SRC_CPU3 == cpuId));

    //
    //  Clear the CPUx errors
    //
    cpuBaseAddr = base + (cpuId * ERROR_AGGREGATOR_CPU_REG_OFFSET);
    //
    //  PR
    //
    HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_PR_ERROR_TYPE_CLR)  = 0xFFFFFFFFU;
    //
    //  DR1
    //
    HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR1_ERROR_TYPE_CLR) = 0xFFFFFFFFU;
    //
    //  DR2
    //
    HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DR2_ERROR_TYPE_CLR) = 0xFFFFFFFFU;
    //
    //  DW
    //
    HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_DW_ERROR_TYPE_CLR)  = 0xFFFFFFFFU;
    //
    //  INT
    //
    HWREG(cpuBaseAddr + ERROR_AGGREGATOR_O_CPU1_INT_ERROR_TYPE_CLR) = 0xFFFFFFFFU;
}

//*****************************************************************************
//
// ErrorAggregator_clearRtdmaError
//
//*****************************************************************************
void ErrorAggregator_clearRtdmaError(uint32_t base, ErrorAggregator_SourceRtdma rtdmaId)
{
    uint32_t rtdmaBaseAddr;
    //
    // Check the arguments
    //
    ASSERT(ErrorAggregator_isBaseValid(base));
    ASSERT((EA_SRC_RTDMA1 == rtdmaId) || (EA_SRC_RTDMA2 == rtdmaId));

    //
    //  Clear RTDMAx errors
    //
    rtdmaBaseAddr = base + (rtdmaId * ERROR_AGGREGATOR_RTDMA_REG_OFFSET);
    //
    //  DR
    //
    HWREG(rtdmaBaseAddr + ERROR_AGGREGATOR_O_RTDMA1_DR_ERROR_TYPE_CLR)  = 0xFFFFFFFFU;
    //
    //  DW
    //
    HWREG(rtdmaBaseAddr + ERROR_AGGREGATOR_O_RTDMA1_DW_ERROR_TYPE_CLR)  = 0xFFFFFFFFU;
}

//*****************************************************************************
//
// ErrorAggregator_clearSsuError
//
//*****************************************************************************
void ErrorAggregator_clearSsuError(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(ErrorAggregator_isBaseValid(base));

    //
    //  Clear SSU errors
    //
    HWREG(base + ERROR_AGGREGATOR_O_SSU_ERROR_TYPE_CLR) = 0xFFFFFFFFU;
}

//*****************************************************************************
//
// ErrorAggregator_clearSsuError
//
//*****************************************************************************
void ErrorAggregator_clearEthercatError(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(ErrorAggregator_isBaseValid(base));

    //
    //  Clear Ethercat errors
    //
    HWREG(base + ERROR_AGGREGATOR_O_ETHERCAT_ERROR_TYPE_CLR)    = 0xFFFFFFFFU;
}