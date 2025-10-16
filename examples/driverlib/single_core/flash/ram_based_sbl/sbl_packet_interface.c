// ###########################################################################
//
//  FILE:    sbl_packet_interface.c
//
//  TITLE:   Packet communication interface that interacts with the host
//
// ###########################################################################
//  $TI Release:  $
//  $Release Date:  $
//  //
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

// ###########################################################################

#include "sbl_packet_config.h"
#include "sbl_packet_interface.h"
#include <stdarg.h>

//
// Global watch variables
//
__attribute__((retain, section("sbl_packet_scratchpad")))
uint8_t gPktData[DATA_BUFFER_SIZE];
packetInterface_t gPktIntf =
{
    .commBase = SBL_COMA_BASE, // Sysconfig defined variable
    .dInfo.dataPtr = gPktData,
    .dInfo.bufferSize = sizeof(gPktData)
};
size_t  waitForDmaDataCounter_ticks = 0;

//
// Internal Functions
//
void _ackDataFrame(void);
void _ackAlternateDataFrame(uint16_t readSize);
void _recvDataFrame(void);
uint16_t _recvRedirectDataFrame(void* const altAddr);
void _sendCommandContent(CommandPkt_t* pCmdpkt);
void _sendCommandResponseContent(CommandResponsePkt_t* pCRpkt);
void _sendFlashStatusContent(FlashStatusPkt_t* pFSpkt);
void _sendMessageContent(MessagePkt_t* pMpkt);
void _sendErrorStatusContent(ErrorStatusPkt_t* pEpkt);

OPT_ATTR void sblResetInterface(void)
{
    gPktIntf.isInDataMode = false;
    gPktIntf.dInfo.readIdx = 0;
    gPktIntf.dInfo.readSize = 0;
    gPktIntf.dInfo.checksum = 0;
    comReset();
#if ENABLE_SHADOW_BUFFER
    gPktIntf.sInfo.isRxDmaActive = false;
    gPktIntf.sInfo.isShadowEnabled = false;
#endif  /* ENABLE_SHADOW_BUFFER */
}

// sblSendPacket - This function is used to construct packet based on input payload
//                  Note: Any non-Data Frame ACK packet sent during data mode will be considered as a NAK packet signaling EOT status and sbl error has occured 
//
//! (Full packet - valid for initial packet response, end-of-transmission (EOT) packet. If sent outside of the two, it'll be treated as a NAK packet)
//! Packet Format: | Header | Payload Size |   Payload(s)   | Payload Checksum | Footer | 
//! Size (bytes)   |   1    |       2      |   (oPkt_t(s))  |         2        |   1    |
//!
//! (Data Frame NAK status Packet - only valid during data tranmission)
//! Packet Format: | NAK | Payload Size |   Payload(s)   | Payload Checksum | Footer | 
//! Size (bytes)   |  1  |       2      |   (oPkt_t(s))  |         2        |   1    |
//!
//! (Data Frame ACK Packet - only valid during data tranmission)
//! Packet Format: | ACK | Data Checksum |
//! Size (bytes)   |  1  |       2       |
__attribute__((nonnull))
OPT_ATTR int sblSendPacket(int n, ...)
{
    va_list va;
    void* p;
    uint16_t size = 0;
    int retVal = 0;
    MessagePkt_t errMsg = { .payloadType=(PayloadType)Message, .msgAddr=NULL };

    if (n <= 0)
    {
        return -1;
    }

#if ENABLE_SHADOW_BUFFER
    // If DMA is active, stop and disable (sending error packets)
    if (gPktIntf.sInfo.isRxDmaActive)
    {
        stopDataModeISR();
        disableDataModeISR();
    }
#endif /* ENABLE_SHADOW_BUFFER */

    // Flush input buffer
    comFlushRead();

    // Send packet header and proceed until acknowledgement (handshake)
    uint8_t header = (gPktIntf.isInDataMode) ? PACKET_NAK : PACKET_HEADER;

#if ENABLE_PACKET_HANDSHAKE 
    comWriteByte(header, false);
    while (!(comIsDataAvailable() && comReadByte(false) == PACKET_ACK))
    {
        // Wait for 50ms (>line delay)
        DEVICE_DELAY_US(50000U);
        if (!comIsDataAvailable())
        {
            comWriteByte(header, false);
        }
    }

    // Send end of handshake and proceed with payloads
    comWriteByte(PACKET_END_HANDSHAKE, false);
    while(!(comIsDataAvailable() && comReadByte(false) == PACKET_END_HANDSHAKE)) {;}
#else
    comWriteByte(header, false);
#endif /* ENABLE_PACKET_HANDSHAKE */

    // Calculate the size of content
    va_start(va, n);
    for (int i = 0; i < n; i++)
    {
        p = va_arg(va, void*);
        uint8_t* pType = (uint8_t*)p;
        switch ((PayloadType)*pType) 
        {
            case Command:
                size += COMMAND_PACKET_SIZE((CommandPkt_t*)p);
                break;
            case CommandResponse:
                size += COMMAND_RESPONSE_PACKET_SIZE;
                break;
            case FlashStatus:
                size += FLASH_PACKET_SIZE;
                break;
            case Message:
                size += MESSAGE_PACKET_SIZE((MessagePkt_t*)p);
                break;
            case ErrorStatus:
                size += ERROR_PACKET_SIZE((ErrorStatusPkt_t*)p);
                break;
            default: 
                // if uninterpretable send error message
                errMsg.length = sizeof("sblSendPacket(target) ERROR: passed in Pkt_t object does not have a known PayloadType, please double check your sbl implementation");
                size += MESSAGE_PACKET_SIZE(&errMsg);
                break;
        }
    }
    va_end(va);

    // Send payload size field
    comWriteWord(size, false);

    //
    // Reset checksum
    // Checksum is only calculated on the data/payload content itself
    //
    gPktIntf.dInfo.checksum = 0;

    // Send the actual content
    va_start(va, n);
    for (int i = 0; i < n; i++)
    {
        p = va_arg(va, void*);
        uint8_t* pType = (uint8_t*)p;
        switch ((PayloadType) *pType) 
        {  
            case Command:
                _sendCommandContent((CommandPkt_t*)p);
                break;
            case CommandResponse:
                _sendCommandResponseContent((CommandResponsePkt_t*)p);
                break;
            case FlashStatus:
                _sendFlashStatusContent((FlashStatusPkt_t*)p);
                break;
            case Message:
                _sendMessageContent((MessagePkt_t*)p);
                break;
            case ErrorStatus:
                _sendErrorStatusContent((ErrorStatusPkt_t*)p);
                break;
            default: 
            {
                // if uninterpretable send error message
                char ch[] = "sblSendPacket(target) ERROR: passed in Pkt_t object does not have a known PayloadType, please double check your sbl implementation";
                errMsg.msgAddr = ch;
                errMsg.length = sizeof(ch);
                _sendMessageContent(&errMsg);
                retVal = -1;
                break;
            }
                
        }
    }
    va_end(va);

    // Send payload checksum field
    comWriteWord(gPktIntf.dInfo.checksum, false);

    // Send footer
    comWriteByte(PACKET_FOOTER, false);

    // Flush send buffer
    comFlushWrite();

    // Receive host acknowledgement 
    uint8_t ackVal = comReadByte(false);
    if (ackVal != PACKET_ACK)
    {
        retVal = -1;
    }
    
    return retVal;
}

//
// sblStartDataMode - this function signals for uart interface to be in data mode.
//                    
OPT_ATTR void sblStartDataMode(void)
{
    gPktIntf.isInDataMode = true;
#if ENABLE_SHADOW_BUFFER
    enableDataModeISR();
    // shadow buffer not in use, invoke uart dma to occupy shadow buffer
    if (!gPktIntf.sInfo.isRxDmaActive)
    {
        startDataModeISR();
    }
#endif /* ENABLE_SHADOW_BUFFER */
}

//
// sblEndDataMode -  This routine acknowledges final data frame from data transmission
//                    and set the status out of data mode
//                    One must call this func before sending EOT packet if sblGetData() 
//                    or sblGetDataArray() has been called
//
//
OPT_ATTR void sblEndDataMode(void)
{   
    // If not in data mode then don't send data frame ack
    if (gPktIntf.dInfo.readSize != 0 && gPktIntf.isInDataMode == true)
    {
#if ENABLE_SHADOW_BUFFER
        if (gPktIntf.sInfo.isRxDmaActive)
        {
            stopDataModeISR();
            // _ackDataFrame is already called prior to starting DataModeISR
        }
        else
        {
            _ackDataFrame();
        }
        disableDataModeISR();
#else 
        _ackDataFrame();
#endif /* ENABLE_SHADOW_BUFFER */
    }

    gPktIntf.isInDataMode = false;
}

//
// sblGetCommandPacket -  This routine receives the handshake packet, returns the
//                 command and put the data length in uint16_t* length
//                 and data in uint8_t* data
//
//! Packet Format: | Header | Data Size |   Data(s)   | Data Checksum | Footer | 
//! Size (bytes)   |   1    |     2     | (oPkt_t(s)) |       2       |   1    |
//
//
OPT_ATTR int sblGetCommandPacket(CommandPkt_t* cmdPkt)
{
    uint16_t pktSize;
    uint16_t* command = &cmdPkt->command;
    uint16_t* readSize = &cmdPkt->addlContentLength;
    char* dataAddr = cmdPkt->addlContentAddr;

#if ENABLE_PACKET_HANDSHAKE 
    // If received isn't a header, keep sending PACKET_NAK until received (handshake)
    // No sleep needed as comReadByte is a blocking function
    while (comReadByte(false) != PACKET_HEADER)
    {
        comWriteByte(PACKET_NAK, false);
    }

    // Now handshake is received, send ACK till sender sends end of handshake
    // No sleep needed as comReadByte is a blocking function
    comWriteByte(PACKET_ACK, false);
    while(comReadByte(false) != PACKET_END_HANDSHAKE) 
    {
        comWriteByte(PACKET_ACK, false);
    }

    // Send end of handshake and proceed with payloads
    comWriteByte(PACKET_END_HANDSHAKE, false);
#else
    if (comReadByte(false) != PACKET_HEADER)
    {
        comWriteByte(PACKET_NAK, false);
        comFlushWrite();
        // packet header mismatch
        return (-1);
    }
#endif /* ENABLE_PACKET_HANDSHAKE */

    pktSize = comReadWord(false); 

    //
    // Reset checksum
    // Checksum is only calculated on the data/payload content itself
    //
    gPktIntf.dInfo.checksum = 0;

    if ((PayloadType)Command != comReadByte(true))
    {
        comWriteByte(PACKET_NAK, false);
        comFlushWrite();
        // packet payloadType error
        return (-1);        
    }
    cmdPkt->payloadType = (PayloadType)Command;

    *command = comReadWord(true);
    *readSize = comReadWord(true);
    for (int i = 0; i < *readSize; i++)
    {
        *(dataAddr + i) = comReadByte(true);
    }

    uint16_t packetChecksum = gPktIntf.dInfo.checksum;
    uint16_t recvdChecksum = comReadWord(true);

#if ENABLE_CHECKSUM_VALIDATION
    if (packetChecksum != recvdChecksum)
    {
        comWriteByte(PACKET_NAK, false);
        comFlushWrite();
        // checksum error
        return (-2);
    }
#endif /* ENABLE_CHECKSUM_VALIDATION */

    if (comReadByte(false) != PACKET_FOOTER)
    {
        comWriteByte(PACKET_NAK, false);
        comFlushWrite();
        // packet footer mismatch
        return (-3);
    }

    // All good, send ACK
    comWriteByte(PACKET_ACK, false);
    comFlushWrite();

    return (0);
}

//! \brief     This routine returns one byte of buffered data during data transmission stage.
//!            If no buffered data are left, it will acknnowledge the host, recv data packet and store the data into its buffer.
//!            Note: only applicable post handshake, i.e command packet has been recognized and is in data transmission.
//! \return    A byte of data
//!
__attribute__((optnone)) uint8_t sblGetData(void)
{
    uint8_t byteData;

#if ENABLE_SHADOW_BUFFER
    while (gPktIntf.dInfo.readIdx >= gPktIntf.dInfo.readSize)
    {
        // if next shadow buffer is ready, reset the buffer
        if (gPktIntf.sInfo.isShadowEnabled)
        {
            gPktIntf.dInfo.readIdx = gPktIntf.sInfo.shadowReadIdx;
            gPktIntf.dInfo.readSize = gPktIntf.sInfo.shadowDataSize;
            gPktIntf.sInfo.isShadowEnabled = false;
        }
        // if DMA active, do not do direct uart read and wait for DMA to finish
        else if (gPktIntf.sInfo.isRxDmaActive)
        {
            while(gPktIntf.sInfo.isRxDmaActive) {waitForDmaDataCounter_ticks++;}
        }
        else
        {
            _ackDataFrame();
            _recvDataFrame();
        }
    }
#else
    if( gPktIntf.dInfo.readIdx >= gPktIntf.dInfo.readSize )
    {
        _ackDataFrame();
        _recvDataFrame();
    }
#endif /* ENABLE_SHADOW_BUFFER */    

    byteData = gPktIntf.dInfo.dataPtr[gPktIntf.dInfo.readIdx];
    gPktIntf.dInfo.readIdx++;
    
    return byteData;
}

//! \brief     This routine copies the requested length of data into the array address during data transmission stage.
//!            If no buffered data are left, it will acknnowledge the host, recv data packet and store the data into its buffer.
//!            Note: only applicable post handshake, i.e command packet has been recognized and is in data transmission.
//!
//! \param[in] array    pointer to an array to store returned data
//!
//! \param[in] length   length of required data
//!
__attribute__((optnone)) void sblGetDataArray(uint8_t* const array, size_t length)
{
    size_t bytesRemain = length;
    uint8_t *curArrIdx = array;
    uint16_t unreadBufSize;
    
    ASSERT(array != NULL);
    ASSERT(gPktIntf.dInfo.readIdx <= gPktIntf.dInfo.readSize);
    
    while (bytesRemain)
    {
        unreadBufSize = gPktIntf.dInfo.readSize - gPktIntf.dInfo.readIdx;
        
        // If data has already been buffered, read from buffer first
        if(unreadBufSize)
        {            
            uint16_t allowableBytes = (bytesRemain > unreadBufSize) ? unreadBufSize : bytesRemain;
            memcpy(curArrIdx, &gPktIntf.dInfo.dataPtr[gPktIntf.dInfo.readIdx], allowableBytes);
            gPktIntf.dInfo.readIdx += allowableBytes;
            curArrIdx += allowableBytes;
            bytesRemain -= allowableBytes;
        }
#if ENABLE_SHADOW_BUFFER
        // if dma data has been prepared, activate the shadow buffer
        else if (gPktIntf.sInfo.isShadowEnabled)
        {
            gPktIntf.dInfo.readIdx = gPktIntf.sInfo.shadowReadIdx;
            gPktIntf.dInfo.readSize = gPktIntf.sInfo.shadowDataSize;
            gPktIntf.sInfo.isShadowEnabled = false;
        }
        // if DMA active, don't file cpu read and wait for DMA to finish
        else if (gPktIntf.sInfo.isRxDmaActive)
        {
            while(gPktIntf.sInfo.isRxDmaActive) 
            {
                waitForDmaDataCounter_ticks++;
            }
        }
#endif /* ENABLE_SHADOW_BUFFER */
        // If the remaining bytes are more than the maximum size of a single packet,
        // then do a direct copy from read port to the target address (rather than having to copy twice).
        else if (bytesRemain >= gPktIntf.dInfo.bufferSize) 
        {
            // bytes to recv should be up to the max payload the packet can support
            uint16_t recvBytes = (bytesRemain > MAX_PAYLOAD_SIZE) ? MAX_PAYLOAD_SIZE : bytesRemain;
            _ackAlternateDataFrame(recvBytes);
            recvBytes = _recvRedirectDataFrame(curArrIdx);
            curArrIdx += recvBytes;
            bytesRemain -= recvBytes;
        }
        // The remaining bytes are less than max size of one incoming packet, 
        // ack and store data normally and proceed to the next loop
        else 
        {
            _ackDataFrame();
            _recvDataFrame();
        }
    }

#if ENABLE_SHADOW_BUFFER
    // Check to enable activate shadow buffer
    if (gPktIntf.dInfo.readIdx >= gPktIntf.dInfo.readSize && gPktIntf.sInfo.isShadowEnabled)
    {
        gPktIntf.dInfo.readIdx = gPktIntf.sInfo.shadowReadIdx;
        gPktIntf.dInfo.readSize = gPktIntf.sInfo.shadowDataSize;
        gPktIntf.sInfo.isShadowEnabled = false;
    }

    unreadBufSize = gPktIntf.dInfo.readSize - gPktIntf.dInfo.readIdx;

    // shadow buffer not in use,  invoke dma transfer to occupy shadow buffer
    if (!gPktIntf.sInfo.isRxDmaActive && unreadBufSize <= SHADOW_THRESHOLD)
    {
        startDataModeISR();
    }
#endif /* ENABLE_SHADOW_BUFFER */
}

//! (Data Frame Ackownledgement Packet - only valid during data tranmission)
//! Packet Format: | ACK | Request Datasize | Data Checksum |
//! Size (bytes)   |  1  |        2         |       1       |
OPT_ATTR void _ackDataFrame(void)
{
    _ackAlternateDataFrame(gPktIntf.dInfo.bufferSize);
}

//! (Data Frame Ackownledgement Packet - only valid during data tranmission)
//! Packet Format: | ACK | Request Datasize | Data Checksum |
//! Size (bytes)   |  1  |        2         |       1      |
OPT_ATTR void _ackAlternateDataFrame(uint16_t readSize)
{
    // Set data mode flag if not already
    gPktIntf.isInDataMode = true;

    // Send packet status first (ACK)
    comWriteByte(PACKET_ACK, false);

    // Request max data size
    comWriteWord(readSize, false);

    // Follow by the checksum
    comWriteWord(gPktIntf.dInfo.checksum, false);

    // Flush send buffer
    comFlushWrite();
}

OPT_ATTR void _recvDataFrame(void)
{
    _recvRedirectDataFrame(gPktIntf.dInfo.dataPtr);
    // Mark readIdx to 0 to indicate fresh buffer
    gPktIntf.dInfo.readIdx = 0;
}

__attribute__((nonnull))
OPT_ATTR uint16_t _recvRedirectDataFrame(void* const altAddr)
{
    uint16_t length;
    uint8_t  *addr;

    ASSERT(altAddr != NULL);

    addr = altAddr;
    length = comReadWord(false);
    
    gPktIntf.dInfo.checksum = 0;
    comReadArray(altAddr, length);
    
    // Mark readIdx = readSize indicating full read (full written to an external addr)
    gPktIntf.dInfo.readSize = length;
    gPktIntf.dInfo.readIdx = length;

    return length;
}

__attribute__((nonnull))
OPT_ATTR void _sendCommandContent(CommandPkt_t* pCmdpkt)
{
    uint8_t payloadType;

    ASSERT(pCmdpkt != NULL);

    payloadType = (PayloadType)Command;
    
    comWriteByte(payloadType, true);
    comWriteWord(pCmdpkt->command, true);
    comWriteWord(pCmdpkt->addlContentLength, true);
    for (int i = 0; i < pCmdpkt->addlContentLength; i++)
    {
        comWriteByte(pCmdpkt->addlContentAddr[i], true);
    }    
}
__attribute__((nonnull))
OPT_ATTR void _sendCommandResponseContent(CommandResponsePkt_t* pCRpkt)
{
    uint8_t payloadType;

    ASSERT(pCRpkt != NULL);

    payloadType = (PayloadType)CommandResponse;

    if (pCRpkt->expectsData && pCRpkt->maxPayloadSize > MAX_PAYLOAD_SIZE)
    {
        // Cap payload size to the maximum preallocated buffer
        pCRpkt->maxPayloadSize = MAX_PAYLOAD_SIZE;
    }
    
    comWriteByte(payloadType, true);
    comWriteWord(pCRpkt->echoCommand, true);
    comWriteByte(pCRpkt->expectsData, true);
    comWriteWord(pCRpkt->timeDelay_ms, true);
    comWriteWord(pCRpkt->maxPayloadSize, true);
    comWriteByte(pCRpkt->expectsEOTpacket, true);
    comWriteByte(pCRpkt->reserved, true);
}

__attribute__((nonnull))
OPT_ATTR void _sendFlashStatusContent(FlashStatusPkt_t* pFSpkt)
{
    uint8_t payloadType, *pAddress, *pFsmStatus;

    ASSERT(pFSpkt != NULL);

    payloadType = (PayloadType)FlashStatus;

    comWriteByte(payloadType, true);
    comWriteWord(pFSpkt->status, true);
    comWriteDWord(pFSpkt->address, true);
    comWriteWord(pFSpkt->flashAPIError, true);
    comWriteDWord(pFSpkt->flashAPIFsmStatus, true);
}

__attribute__((nonnull))
OPT_ATTR void _sendMessageContent(MessagePkt_t* pMpkt)
{
    uint8_t payloadType;

    ASSERT(pMpkt != NULL);

    payloadType = (PayloadType)Message;
    
    comWriteByte(payloadType, true);
    comWriteWord(pMpkt->length, true);
    for (int i = 0; i < pMpkt->length; i++)
    {
        comWriteByte(pMpkt->msgAddr[i], true);
    }
}

__attribute__((nonnull))
OPT_ATTR void _sendErrorStatusContent(ErrorStatusPkt_t* pEpkt)
{
    uint8_t payloadType, *pMsgCode, *pArgv;

    ASSERT(pEpkt != NULL);

    payloadType = (PayloadType)ErrorStatus;
    pArgv = (uint8_t*)pEpkt->pArgsVal;
    
    if (!pEpkt->hasSprintfArgs)
    {
        // Set numArgs to zero so pArgsVal won't send
        pEpkt->numArgs = 0;
    }

    comWriteByte(payloadType, true);
    comWriteDWord(pEpkt->errorMsgCode, true);
    comWriteByte(pEpkt->recoveryStatus, true);
    comWriteByte(pEpkt->hasSprintfArgs, true);
    comWriteByte(pEpkt->numArgs, true);
    for (int i = 0; i < pEpkt->numArgs * SIZE_O_VAL(ErrorStatusPkt_t,pArgsVal); i++)
    {
        comWriteByte(*(pArgv + i), true);
    }
}