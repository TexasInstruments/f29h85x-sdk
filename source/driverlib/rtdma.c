//###########################################################################
//
// FILE:   rtdma.c
//
// TITLE:  C29x RTDMA driver.
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


#include "rtdma.h"

//*****************************************************************************
//
// RTDMA_configAddresses
//
//*****************************************************************************
void DMA_configAddresses(uint32_t base, const void *destAddr,
                         const void *srcAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_CH_isBaseValid(base));

    //
    // Set up SOURCE address.
    //
    HWREG(base + RTDMA_O_SRC_BEG_ADDR_SHADOW) = (uint32_t)srcAddr;
    HWREG(base + RTDMA_O_SRC_ADDR_SHADOW)     = (uint32_t)srcAddr;

    //
    // Set up DESTINATION address.
    //
    HWREG(base + RTDMA_O_DST_BEG_ADDR_SHADOW) = (uint32_t)destAddr;
    HWREG(base + RTDMA_O_DST_ADDR_SHADOW)     = (uint32_t)destAddr;
}

//*****************************************************************************
//
// DMA_configBurst
//
//*****************************************************************************
void DMA_configBurst(uint32_t base, uint16_t size, int16_t srcStep,
                     int16_t destStep)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_CH_isBaseValid(base));
    ASSERT((size >= 1U) && (size <= 256U));

    //
    // Set up BURST registers.
    //
    HWREGH(base + RTDMA_O_BURST_SIZE)     = size - 1U;
    HWREGH(base + RTDMA_O_SRC_BURST_STEP) = srcStep;
    HWREGH(base + RTDMA_O_DST_BURST_STEP) = destStep;
}


//*****************************************************************************
//
// DMA_configTransfer
//
//*****************************************************************************
void DMA_configTransfer(uint32_t base, uint32_t transferSize, int16_t srcStep,
                        int16_t destStep)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_CH_isBaseValid(base));
    ASSERT(transferSize <= 0x10000U);

    //
    // Set up TRANSFER registers.
    //
    HWREGH(base + RTDMA_O_TRANSFER_SIZE)     = (uint16_t)(transferSize - 1U);
    HWREGH(base + RTDMA_O_SRC_TRANSFER_STEP) = srcStep;
    HWREGH(base + RTDMA_O_DST_TRANSFER_STEP) = destStep;
}


//*****************************************************************************
//
// DMA_configWrap
//
//*****************************************************************************
void DMA_configWrap(uint32_t base, uint32_t srcWrapSize, int16_t srcStep,
                    uint32_t destWrapSize, int16_t destStep)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_CH_isBaseValid(base));
    ASSERT((srcWrapSize <= 0x10000U) || (destWrapSize <= 0x10000U));

    //
    // Set up WRAP registers.
    //
    HWREGH(base + RTDMA_O_SRC_WRAP_SIZE) = (uint16_t)(srcWrapSize - 1U);
    HWREGH(base + RTDMA_O_SRC_WRAP_STEP) = srcStep;

    HWREGH(base + RTDMA_O_DST_WRAP_SIZE) = (uint16_t)(destWrapSize - 1U);
    HWREGH(base + RTDMA_O_DST_WRAP_STEP) = destStep;
}


//*****************************************************************************
//
// DMA_configMode
//
//*****************************************************************************
void DMA_configMode(uint32_t base, DMA_Trigger trigger, uint32_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_CH_isBaseValid(base));

    //
    // Configure the peripheral trigger source of the channel and other
    // configurations to the mode register.
    //
    HWREG(base + RTDMA_O_MODE) = (HWREG(base + RTDMA_O_MODE) &
                                ( ~(RTDMA_MODE_PERINTSEL_M |
                                    RTDMA_MODE_DATASIZE_M |
                                    RTDMA_MODE_WRT_DATASIZE_M |
                                    RTDMA_MODE_CONTINUOUS |
                                    RTDMA_MODE_ONESHOT))) |
                                    (uint32_t) trigger | config;
}


//*****************************************************************************
//
// DMA_configChannel
//
//*****************************************************************************
void DMA_configChannel(uint32_t base, const DMA_ConfigParams *configParams)
{
    //
    // Check the arguments.
    //
    ASSERT(DMA_CH_isBaseValid(base));

    //
    // Configure DMA Channel
    //
    DMA_configAddresses(base, (const void *)configParams->destAddr,
                        (const void *)configParams->srcAddr);

    //
    // Configure the size of each burst and the address step size
    //
    DMA_configBurst(base, configParams->burstSize, configParams->srcBurstStep,
                    configParams->destBurstStep);

    //
    // Configure the transfer size and the address step that is
    // made after each burst.
    //
    DMA_configTransfer(base, configParams->transferSize,
                       configParams->srcTransferStep,
                       configParams->destTransferStep);

    //
    // Configure the DMA channel's wrap settings
    //
    DMA_configWrap(base, configParams->srcWrapSize, configParams->srcWrapStep,
                   configParams->destWrapSize, configParams->destWrapStep);

    //
    // Configure the DMA channel's trigger and mode
    //
    DMA_configMode(base, configParams->transferTrigger,
                   configParams->transferMode | configParams->reinitMode |
                   configParams->configSize | configParams->wrtDatasize);

    //
    // Enable the selected peripheral trigger to start a DMA transfer
    //
    DMA_enableTrigger(base);

    //
    // Configure interrupt
    //
    if(configParams->enableInterrupt)
    {
        //
        // Set the channel interrupt mode
        //
        DMA_setInterruptMode(base, configParams->interruptMode);

        //
        // Enable the indicated DMA channel interrupt source
        //
        DMA_enableInterrupt(base);
    }
    else
    {
        //
        // Disable the indicated DMA channel interrupt source
        //
        DMA_disableInterrupt(base);
    }
}


//*****************************************************************************
//
// DMA_configMPURegion
//
//*****************************************************************************
void DMA_configMPURegion(uint32_t base, DMA_MPURegion MPURegion,
                      const DMA_MPUConfigParams *configParams)
{
    //
    // Check the arguments
    //
    ASSERT(DMA_MPU_isBaseValid(base));
    //
    // Check the 4KB granularity
    //
    ASSERT(((configParams->startAddr & 0xFFFU) == 0U) &&
           ((configParams->endAddr   & 0xFFFU) == 0xFFFU));

    //
    // Configure the start and end addresses of the MPU region
    //
    HWREG(base + RTDMA_O_MPUR_START((uint32_t)MPURegion)) =
                                                configParams->startAddr;
    HWREG(base + RTDMA_O_MPUR_END((uint32_t)MPURegion))  =
                                                configParams->endAddr;

    //
    // Configure specific channel accesses for the MPU region
    //
    HWREGH(base + RTDMA_O_MPUR_CHMASK((uint32_t)MPURegion)) =
                                                configParams->channelMask;

    //
    // Configure the type of accesses allowed in the MPU region
    //
    HWREGB(base + RTDMA_O_MPUR_ACCESS((uint32_t)MPURegion)) =
                                    (uint8_t)configParams->accessPermission;
}

