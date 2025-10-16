//###########################################################################
//
//  FILE:    sbl_packet_dma_interrupt.c
//
//  TITLE:   Internal packet interface extension to enable shadow buffers using rtdma
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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

#include "sbl_packet_config.h"
#include "sbl_packet_interface.h"

#if ENABLE_SHADOW_BUFFER

extern packetInterface_t gPktIntf;
extern void _ackAlternateDataFrame(uint16_t readSize);
extern void Example_Error();

uint8_t     dmaLengthBuffer[2];
uint16_t    reminderLength, isr2Length, isr3Length;
uint16_t    dmaStartIdx;
bool        isISR3Enabled;

unsigned int  rxDmaISRCounter = 0;

//
// Internal functions
//
static inline void uartSetupRxDmaISR1();
static inline void uartSetupRxDmaISR2();
static inline void uartSetupRxDmaISR3();
void uartRxDmaISR1();
void uartRxDmaISR2();
void uartRxDmaISR3();
void uartRxSendErrMsg();
void resetDataModeISR();

void enableDataModeISR()
{
    UART_enableDMA(gPktIntf.commBase, (UART_DMA_RX));
    UART_enableInterrupt(gPktIntf.commBase, (UART_INT_RX)); //(UART_INT_DMARX | UART_INT_RX | UART_INT_OE)
    DMA_enableInterrupt(SBL_dataMode_DMA_BASE);
    Interrupt_enable(SBL_dataMode_DMA_INT);

    resetDataModeISR();
}

void disableDataModeISR()
{
    UART_disableDMA(gPktIntf.commBase, (UART_DMA_RX));
    UART_disableInterrupt(gPktIntf.commBase, (UART_INT_RX));
    DMA_disableInterrupt(SBL_dataMode_DMA_BASE);
    Interrupt_disable(SBL_dataMode_DMA_INT);
}

void resetDataModeISR()
{
    UART_clearInterruptStatus(gPktIntf.commBase, 0xFFFF);
    UART_clearGlobalInterruptFlag(gPktIntf.commBase);
    DMA_clearTriggerFlag(SBL_dataMode_DMA_BASE);
    DMA_enableTrigger(SBL_dataMode_DMA_BASE);
    Interrupt_clearFlag(SBL_dataMode_DMA_INT);
}

void stopDataModeISR()
{
    DMA_stopChannel(SBL_dataMode_DMA_BASE); 
    DMA_triggerSoftReset(SBL_dataMode_DMA_BASE); 

    gPktIntf.sInfo.isRxDmaActive = false;
}

void startDataModeISR()
{   
    if (gPktIntf.sInfo.isRxDmaActive)
    {
        return;
    }
    
    uartSetupRxDmaISR1();
}

void uartRxSendErrMsg()
{
    const ErrorStatusPkt_t errPkt =
    {
        .payloadType = (PayloadType)ErrorStatus,
        .errorMsgCode = 0x2002,              // error message decoded in comm_packet_protocol.h
        .recoveryStatus = RS_NormalOperation,
        .hasSprintfArgs = false,             
        .numArgs = 0U,                       
        .pArgsVal = NULL                      
    };
    sblSendPacket(1, &errPkt);
    Example_Error();
}

// Setup and start ISR1
static inline __attribute__((always_inline))
void uartSetupRxDmaISR1()
{
    uint16_t dmaEndIdx;

    if (gPktIntf.sInfo.isShadowEnabled)
    {
        dmaStartIdx = gPktIntf.sInfo.shadowDataSize;
        dmaEndIdx = (gPktIntf.dInfo.readIdx >= gPktIntf.dInfo.readSize) ? DATA_BUFFER_SIZE - 1 : gPktIntf.dInfo.readIdx - 1;
        ASSERT(gPktIntf.dInfo.readIdx != 0);
    }
    else
    {
        dmaStartIdx = (gPktIntf.dInfo.readIdx >= gPktIntf.dInfo.readSize || gPktIntf.dInfo.readSize >= DATA_BUFFER_SIZE) ? 0 : gPktIntf.dInfo.readSize;
        dmaEndIdx = (gPktIntf.dInfo.readIdx >= gPktIntf.dInfo.readSize || gPktIntf.dInfo.readIdx == 0) ? DATA_BUFFER_SIZE - 1 : gPktIntf.dInfo.readIdx - 1;
    }
	
    if (dmaStartIdx == dmaEndIdx)
    {
        return;
    }

	// +1 denoting conversion from 0th index (inclusive) to 1st index. As size is 1st index
    // Subsequent ISR2/3 Indexes are calculated bassed on the commented relationship with respective to its length
	if (dmaStartIdx > dmaEndIdx)
	{
		isISR3Enabled = true;
		isr2Length = DATA_BUFFER_SIZE - dmaStartIdx;
		isr3Length = dmaEndIdx + 1;
        //isr2StartIdx = dmaStartIdx;
        //isr2EndIdx = DATA_BUFFER_SIZE - 1;
        //isr3StartIdx = 0;
        //isr3EndIdx = dmaEndIdx;
	}
	else
	{
		isISR3Enabled = false;
		isr2Length = dmaEndIdx - dmaStartIdx + 1;
        isr3Length = 0;
        //isr2StartIdx = dmaStartIdx;
        //isr2EndIdx = dmaEndIdx;
	}

    gPktIntf.sInfo.isRxDmaActive = true;

    // register ISR1
    Interrupt_register(SBL_dataMode_DMA_INT, &uartRxDmaISR1);

    // set destination addr
    DMA_configAddresses(SBL_dataMode_DMA_BASE, (const void*)dmaLengthBuffer, SBL_dataMode_DMA_ADDRESS);

    // set to read 2Bytes (the length metadata of the packet)
    // Change trigger source to 2 bytes (UART_FIFO_RX1_8)
    UART_setFIFOLevel(gPktIntf.commBase, UART_FIFO_TX4_8, UART_FIFO_RX1_8);
    DMA_configBurst(SBL_dataMode_DMA_BASE, 2U, 0, sizeof(uint8_t));
    DMA_configTransfer(SBL_dataMode_DMA_BASE, 1U, 0, sizeof(uint8_t));

    _ackAlternateDataFrame(isr2Length + isr3Length);
    DMA_startChannel(SBL_dataMode_DMA_BASE);
}

// End of DMA transfer
__attribute__((interrupt("RTINT")))
void uartRxDmaISR1()
{
    if (UART_getRxError(gPktIntf.commBase))
    {
        uartRxSendErrMsg();
        return;
    }
    uartSetupRxDmaISR2();
}

// Setup and start ISR2
static inline __attribute__((always_inline))
void uartSetupRxDmaISR2()
{

	uint16_t rcvdLength, length;
    uint16_t isr2StartIdx;

    isr2StartIdx = dmaStartIdx;
    
    // register ISR2
    Interrupt_register(SBL_dataMode_DMA_INT, &uartRxDmaISR2);

    // set destination addr
    DMA_configAddresses(SBL_dataMode_DMA_BASE, (const void*)&gPktIntf.dInfo.dataPtr[isr2StartIdx], SBL_dataMode_DMA_ADDRESS);

    rcvdLength = dmaLengthBuffer[0] | ((uint16_t)dmaLengthBuffer[1] << 8);

	if (rcvdLength <= isr2Length) 
	{
		length = rcvdLength;
		isISR3Enabled = false;
	}
	else
	{
		length = isr2Length;
		isr3Length = rcvdLength - isr2Length;
	}

    // Match UART RX FIFO interrupt size
    if (length % 8 == 0)
    {
        // 8 bytes per burst
        UART_setFIFOLevel(gPktIntf.commBase, UART_FIFO_TX4_8, UART_FIFO_RX4_8);
        DMA_configBurst(SBL_dataMode_DMA_BASE, 8U, 0, sizeof(uint8_t));
        DMA_configTransfer(SBL_dataMode_DMA_BASE, length / 8U, 0, sizeof(uint8_t));
        reminderLength = 0;
    }
    else
    {
        // 2 bytes per burst
        UART_setFIFOLevel(gPktIntf.commBase, UART_FIFO_TX4_8, UART_FIFO_RX1_8);
        DMA_configBurst(SBL_dataMode_DMA_BASE, 2U, 0, sizeof(uint8_t));
        DMA_configTransfer(SBL_dataMode_DMA_BASE, length / 2U, 0, sizeof(uint8_t));
        reminderLength = length % 2;
        if (reminderLength == length)
        {
            uartRxDmaISR2();
            return;
        }
    }

    DMA_startChannel(SBL_dataMode_DMA_BASE); 

}

// End of DMA transfer
__attribute__((interrupt("RTINT")))
void uartRxDmaISR2()
{
    uint16_t isr2StartIdx, isr2EndIdx;

    if (UART_getRxError(gPktIntf.commBase))
    {
        uartRxSendErrMsg();
        return;
    }
    
    isr2StartIdx = dmaStartIdx;
    isr2EndIdx = dmaStartIdx + isr2Length - 1;

    while (reminderLength)
    {
        gPktIntf.dInfo.dataPtr[isr2EndIdx - (reminderLength - 1)] = comReadByte(false);
        reminderLength--;
    }

	if (isISR3Enabled)
	{
		uartSetupRxDmaISR3();
		return;
	}

#if ENABLE_CHECKSUM_VALIDATION
    uint16_t checksum;
	uint8_t* dataPtr;
    checksum = 0;
	dataPtr = &gPktIntf.dInfo.dataPtr[isr2StartIdx];
    for (int i = 0; i < isr2Length; i++)
    {
        checksum += dataPtr[i];
    }
    gPktIntf.dInfo.checksum = checksum;
#endif 

    // If new data gets placed before current data or the whole data buffer is new, mark it as shadow to manually switch in code
	if (gPktIntf.dInfo.readSize >= isr2EndIdx + 1 || (isr2StartIdx == 0 & isr2EndIdx == DATA_BUFFER_SIZE - 1))
	{
		gPktIntf.sInfo.shadowReadIdx = 0;
		gPktIntf.sInfo.shadowDataSize = isr2EndIdx + 1;
		gPktIntf.sInfo.isShadowEnabled = true;
	}
    // new data is placed after the current data, simply extends the data range to include it
	else
	{
        gPktIntf.dInfo.readSize = isr2EndIdx + 1;
		gPktIntf.sInfo.isShadowEnabled = false;
	}
    gPktIntf.sInfo.isRxDmaActive = false;
    rxDmaISRCounter++;
}

// Setup and start optional ISR3 (wrap-around data acquisition)
static inline __attribute__((always_inline))
void uartSetupRxDmaISR3()
{

	uint16_t length;
    uint16_t isr3StartIdx;

    isr3StartIdx = 0;

    // register ISR2
    Interrupt_register(SBL_dataMode_DMA_INT, &uartRxDmaISR3);

    // set destination addr
    DMA_configAddresses(SBL_dataMode_DMA_BASE, (const void*)&gPktIntf.dInfo.dataPtr[isr3StartIdx], SBL_dataMode_DMA_ADDRESS);

    length = isr3Length;

    // Match UART RX FIFO interrupt size
    if (length % 8 == 0)
    {
        // 8 bytes per burst
        UART_setFIFOLevel(gPktIntf.commBase, UART_FIFO_TX4_8, UART_FIFO_RX4_8);
        DMA_configBurst(SBL_dataMode_DMA_BASE, 8U, 0, sizeof(uint8_t));
        DMA_configTransfer(SBL_dataMode_DMA_BASE, length / 8U, 0, sizeof(uint8_t));
        reminderLength = 0;
    }
    else
    {
        // 2 bytes per burst
        UART_setFIFOLevel(gPktIntf.commBase, UART_FIFO_TX4_8, UART_FIFO_RX1_8);
        DMA_configBurst(SBL_dataMode_DMA_BASE, 2U, 0, sizeof(uint8_t));
        DMA_configTransfer(SBL_dataMode_DMA_BASE, length / 2U, 0, sizeof(uint8_t));
        reminderLength = length % 2;
        if (reminderLength == length)
        {
            uartRxDmaISR3();
            return;
        }
    }

    DMA_startChannel(SBL_dataMode_DMA_BASE); 
}

// End of DMA transfer 
__attribute__((interrupt("RTINT")))
void uartRxDmaISR3()
{
    uint16_t isr2StartIdx, isr2EndIdx, isr3StartIdx, isr3EndIdx;

    if (UART_getRxError(gPktIntf.commBase))
    {
        uartRxSendErrMsg();
        return;
    }

    isr2StartIdx = dmaStartIdx;
    isr2EndIdx = DATA_BUFFER_SIZE - 1;
    isr3StartIdx = 0;
    isr3EndIdx = isr3Length - 1;

    while (reminderLength)
    {
        gPktIntf.dInfo.dataPtr[isr3EndIdx - (reminderLength - 1)] = comReadByte(false);
        reminderLength--;
    }

#if ENABLE_CHECKSUM_VALIDATION
    uint16_t checksum;
	uint8_t* dataPtr;
    checksum = 0;
    dataPtr = &gPktIntf.dInfo.dataPtr[isr3StartIdx];
    for (int i = 0; i < isr3Length; i++)
    {
        checksum += dataPtr[i];
    }
    dataPtr = &gPktIntf.dInfo.dataPtr[isr2StartIdx];
    for (int i = 0; i < isr2Length; i++)
    {
        checksum += dataPtr[i];
    }
    gPktIntf.dInfo.checksum = checksum;
#endif 

    // new data gets placed both before and after the existing data
    // therefore both extend current data range and mark the shadow buffer
    gPktIntf.dInfo.readSize = isr2EndIdx + 1;
	gPktIntf.sInfo.shadowReadIdx = isr3StartIdx;
	gPktIntf.sInfo.shadowDataSize = isr3EndIdx + 1;
	gPktIntf.sInfo.isShadowEnabled = true;
    gPktIntf.sInfo.isRxDmaActive = false;
    rxDmaISRCounter++;
}

#else

// Placeholder for sysconfig func
__attribute__((weak))
void uartRxDmaISR1() {;}

#endif /* ENABLE_SHADOW_BUFFER */