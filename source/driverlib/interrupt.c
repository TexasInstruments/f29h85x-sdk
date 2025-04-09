//###########################################################################
//
// FILE:   interrupt.c
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

#include "interrupt.h"

__attribute__((interrupt("INT")))
void Interrupt_defaultHandler(void)
{
    ESTOP0;
    for(;;)
    {
        ;
    }
}

//
//  This function does the following...
//  ->  Store CPU1 ESM raw status
//  ->  Store CPU1/2/3, RTDMA1/2 SSU and Ethercat Error Aggregator status
//  ->  Clear CPU1/2/3 ESM status
//  ->  Clear CPU1/2/3, RTDMA1/2 SSU and Ethercat Error Aggregator status
//
void Interrupt_clearEsmEaFlags(Interrupt_NmiStatus *nmiStatus)
{
    uint32_t grp;

    //
    //  Get ESM status for all CPUs
    //
    for(grp = 0U;grp < ESM_NUM_GROUPS;grp++)
    {
        nmiStatus->cpu1EsmSts[grp]  = ESM_getGroupRawIntStatus(ESMCPU1_BASE, grp);
    }

    //
    //  Get EA status for all sources
    //
    //
    //  CPU
    //
    ErrorAggregator_getCpuErrorInfo(ERRORAGGREGATOR_BASE, EA_SRC_CPU1, &nmiStatus->cpu1EaSts);
    ErrorAggregator_getCpuErrorInfo(ERRORAGGREGATOR_BASE, EA_SRC_CPU2, &nmiStatus->cpu2EaSts);
    ErrorAggregator_getCpuErrorInfo(ERRORAGGREGATOR_BASE, EA_SRC_CPU3, &nmiStatus->cpu3EaSts);
    //
    //  RTDMA
    //
    ErrorAggregator_getRtdmaErrorInfo(ERRORAGGREGATOR_BASE, EA_SRC_RTDMA1, &nmiStatus->rtdma1EaSts);
    ErrorAggregator_getRtdmaErrorInfo(ERRORAGGREGATOR_BASE, EA_SRC_RTDMA2, &nmiStatus->rtdma2EaSts);
    //
    //  SSU
    //
    ErrorAggregator_getSsuErrorInfo(ERRORAGGREGATOR_BASE, &nmiStatus->ssuEaSts);
    //
    //  Ethercat
    //
    ErrorAggregator_getEthercatErrorInfo(ERRORAGGREGATOR_BASE, &nmiStatus->ethercatEaSts);

    //
    //  Clear ESM status for all CPUs
    //  -> Write 1 to status register to clear
    //
    for(grp = 0U;grp < ESM_NUM_GROUPS;grp++)
    {
        ESM_clearGroupIntStatus(ESMCPU1_BASE, grp);
        ESM_clearGroupIntStatus(ESMCPU2_BASE, grp);
        ESM_clearGroupIntStatus(ESMCPU3_BASE, grp);
    }

    //
    //  Clear EA status
    //
    //
    //  CPU
    //
    ErrorAggregator_clearCpuError(ERRORAGGREGATOR_BASE, EA_SRC_CPU1);
    ErrorAggregator_clearCpuError(ERRORAGGREGATOR_BASE, EA_SRC_CPU2);
    ErrorAggregator_clearCpuError(ERRORAGGREGATOR_BASE, EA_SRC_CPU3);
    //
    //  RTDMA
    //
    ErrorAggregator_clearRtdmaError(ERRORAGGREGATOR_BASE, EA_SRC_RTDMA1);
    ErrorAggregator_clearRtdmaError(ERRORAGGREGATOR_BASE, EA_SRC_RTDMA2);
    //
    //  SSU
    //
    ErrorAggregator_clearSsuError(ERRORAGGREGATOR_BASE);
    //
    //  Ethercat
    //
    ErrorAggregator_clearEthercatError(ERRORAGGREGATOR_BASE);
}

__attribute__((interrupt("RTINT")))
void Interrupt_defaultNMIHandler(void)
{
    ESTOP0;  // Use Gel scripts to read ESM and Error Aggregator status

    Interrupt_NmiStatus nmiStatus;
    //
    //  Clear ESM and EA error flags
    //
    Interrupt_clearEsmEaFlags(&nmiStatus);

    //
    //  Spin forever
    //
    for(;;)
    {
        ;
    }
}

//*****************************************************************************
//
// Interrupt_initModule
//
//*****************************************************************************
void
Interrupt_initModule(void)
{
    uint16_t i;

    //
    // Initialize the MMR registers
    //
    HWREG(PIPE_BASE + PIPE_O_MMR_CLR) = 0x3U;

    //
    // Initialize the memory and wait for completion
    //
    HWREG(PIPE_BASE + PIPE_O_MEM_INIT) = PIPE_MEM_INIT_KEY | 0x3U;
    while(HWREG(PIPE_BASE + PIPE_O_MEM_INIT_STS) != 0x2U)
    {
    }

    //
    // Set all link owner of all interrupts to LINK2 and INTSP to STACK2
    //
    for(i = 0; i < INTERRUPT_NO_OF_CHANNELS; i++)
    {
        Interrupt_setLinkOwner(i, SSU_LINK2);
    }
    Interrupt_setLinkOwner(INT_NMI, SSU_LINK2);
    Interrupt_setINTSP(SSU_STACK2);
}

//*****************************************************************************
//
// Interrupt_initVectorTable
//
//*****************************************************************************
void
Interrupt_initVectorTable(void)
{
    uint16_t i;

    //
    //  Program the PIPE register for NMI vector only for CPU1
    //  For CPU2 and CPU3, CPU1 programs the SSU NMI vector and
    //  link settings
    //
    if(SSU_CPU1 == SSU_getCPUID())
    {
        HWREG(PIPE_BASE + PIPE_O_NMI_VECT) = (uint32_t)Interrupt_defaultNMIHandler;
    }

    for(i = 0U; i < INTERRUPT_NO_OF_CHANNELS; i++)
    {
        HWREG(PIPE_BASE + PIPE_O_INT_VECT_ADDR(i)) =
                                            (uint32_t)Interrupt_defaultHandler;
    }

}

//*****************************************************************************
//
// Interrupt_configChannel
//
//*****************************************************************************
void
Interrupt_configChannel(uint32_t intNum, Interrupt_Config config)
{
    ASSERT(intNum < INTERRUPT_NO_OF_CHANNELS);

    HWREG(PIPE_BASE + PIPE_O_INT_VECT_ADDR(intNum)) = (uint32_t)config.handler;

    HWREG(PIPE_BASE + PIPE_O_INT_CONFIG(intNum)) =
        ((uint32_t)config.priority << PIPE_INT_CONFIG_PRI_LEVEL_S)  |
        ((uint32_t)config.contextID << PIPE_INT_CONFIG_CONTEXT_ID_S);

    if(config.apiLinkID == SSU_API_DISABLE)
    {
         HWREGH(PIPE_BASE + PIPE_O_INT_LINK_OWNER(intNum)) =
        ((uint16_t)config.linkOwner << PIPE_INT_LINK_OWNER_OWNER_LINK_S);
    }
    else
    {
        HWREGH(PIPE_BASE + PIPE_O_INT_LINK_OWNER(intNum)) =
        ((uint16_t)config.linkOwner << PIPE_INT_LINK_OWNER_OWNER_LINK_S) |
        PIPE_INT_LINK_OWNER_API_LINK_EN |
        ((uint16_t)config.apiLinkID << PIPE_INT_LINK_OWNER_API_LINK_S);

    }

    HWREGB(PIPE_BASE + PIPE_O_INT_CTL_L(intNum)) = config.enable;
}

//*****************************************************************************
//
// Interrupt_configNMI
//
//*****************************************************************************
void
Interrupt_configNMI(void (*handler)(void), SSU_Link linkOwner)
{
    HWREG(PIPE_BASE + PIPE_O_NMI_VECT) = (uint32_t)handler;
    HWREGB(PIPE_BASE + PIPE_O_NMI_LINK_OWNER) = (uint8_t)linkOwner;
}