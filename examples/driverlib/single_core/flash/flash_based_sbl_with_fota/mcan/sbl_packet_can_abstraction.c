//###########################################################################
//
// FILE:    sbl_packet_can_abstraction.h
//
// TITLE:   Internal Low-level abstraction of CAN periperial implementation used by the packet interface
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

//
// Included Files
//
#include "sbl_packet_can_abstraction.h"

mcanInterface_t mcanIntf = 
{
    .commBase = SBL_COMA_BASE,            // Sysconfig defined variable
    .maxDataSize = MCAN_MAX_PAYLOAD_BYTES // Sends CAN-FD message
};

void mcanSendFrame(uint32_t size);
void mcanRecvFrame();

//
// Internal functions
//
void _mcanSendFrame(uint32_t dlc);
void _mcanSendMultiFrame(uint32_t size);

//
// Reset internal mcanIntf
//
void comReset()
{
    //
    // Initialize transmit message properties 
    // Adjust these configurations will affect all messages sent to host 
    //
    mcanIntf.txMsg.id       = ((uint32_t)(0x4)) << 18U; // Identifier Value. 0x4 in extended frame format
    mcanIntf.txMsg.rtr      = 0U; // Transmit data frame.
    mcanIntf.txMsg.xtd      = 0U; // 11-bit standard identifier.
    mcanIntf.txMsg.esi      = 0U; // ESI bit in CAN FD format depends only on error
                                  // passive flag.
    mcanIntf.txMsg.brs      = 1U; // CAN FD frames transmitted with bit rate
                                  // switching.
    mcanIntf.txMsg.fdf      = 1U; // Frame transmitted in CAN FD format.
    mcanIntf.txMsg.efc      = 1U; // Store Tx events.
    mcanIntf.txMsg.mm       = 0xAAU; // Message Marker.
    // txMsg.dlc is determined when frames are sent

    mcanIntf.rxIdx = 0;
    mcanIntf.txIdx = 0;
    mcanIntf.rxSize = 0;
}

//
// mcanSendFrame - sends a frame with mcanIntf.txMsg settings
// Note: assumes that data has already been copied into the mcanIntf.txMsg.data buffer
//
void mcanSendFrame(uint32_t size)
{
    ASSERT(size <= 64U);

    switch (size) 
    {
        case 64U:
            _mcanSendFrame(15U);
            break;
        case 48U:
            _mcanSendFrame(14U);
            break;
        case 32U:
            _mcanSendFrame(13U);
            break;
        case 24U:
            _mcanSendFrame(12U);
            break;
        case 20U:
            _mcanSendFrame(11U);
            break;
        case 16U:
            _mcanSendFrame(10U);
            break;
        case 12U:
            _mcanSendFrame(9U);
            break;
        default:
            if (size <= 8U)
            {
                _mcanSendFrame(size);
            }
            else
            {
                // Unable to send in one frame, opt for multiple frames
                _mcanSendMultiFrame(size);
            }   
            break;
    }
    mcanIntf.txIdx = 0;
}

//
// _mcanSendMultiFrame - sends multiple frames if a CAN-FD message can't be send in one frame (data paddings can't be used in packet protocol)
// Note: assumes that data has already been copied into the mcanIntf.txMsg.data buffer
//
void _mcanSendMultiFrame(uint32_t size)
{
    uint32_t bytesRemain = size;

    while (bytesRemain)
    {
        uint32_t dlc;
        uint32_t sendSize;
        
        if (bytesRemain == 64U)
        {
            dlc = 15U;
            sendSize = 64U;
            bytesRemain -= sendSize;
        }
        else if (bytesRemain >= 48U)
        {
            dlc = 14U;
            sendSize = 48U;
            bytesRemain -= sendSize;
        }
        else if (bytesRemain >= 32U)
        {
            dlc = 13U;
            sendSize = 32U;
            bytesRemain -= sendSize;
        }
        else if (bytesRemain >= 24U)
        {
            dlc = 12U;
            sendSize = 24U;
            bytesRemain -= sendSize;
        }
        else if (bytesRemain >= 20U)
        {
            dlc = 11U;
            sendSize = 20U;
            bytesRemain -= sendSize;
        }
        else if (bytesRemain >= 16U)
        {
            dlc = 10U;
            sendSize = 16U;
            bytesRemain -= sendSize;
        }
        else if (bytesRemain >= 12U)
        {
            dlc = 9U;
            sendSize = 12U;
            bytesRemain -= sendSize;
        }
        else if (bytesRemain >= 8U)
        {
            dlc = 8U;
            sendSize = 8U;
            bytesRemain -= sendSize;
        }
        else
        {
            dlc = bytesRemain;
            sendSize = 0;
            bytesRemain = 0;
        }

        // Send mcan frame with dlc attribute
        _mcanSendFrame(dlc);

        // Copy remaining datas to the beginning (skip initial copy - since data has already been populated in the txMsg buffer)
        memcpy(mcanIntf.txMsg.data, &mcanIntf.txMsg.data[sendSize], sizeof(*mcanIntf.txMsg.data) * bytesRemain);
    }
}

//
// _mcanSendFrame - sends message using TX FIFO in blocking fashion.
// Note: assumes that data has already been copied into the mcanIntf.txMsg.data buffer
//
void _mcanSendFrame(uint32_t dlc)
{
    MCAN_TxFIFOStatus txFifoStatus;
    uint32_t putIdx;

    mcanIntf.txMsg.dlc = dlc;

    //
    // Wait until Tx Fifo is available
    //
    do
    {
        MCAN_getTxFIFOQueStatus(mcanIntf.commBase, &txFifoStatus);
    } while (txFifoStatus.fifoFull);

    // Get the index for next free slot
    putIdx = txFifoStatus.putIdx;

    //
    // Write Tx Message to the Message RAM (Tx FIFO).
    //
    MCAN_writeMsgRam(mcanIntf.commBase, MCAN_MEM_TYPE_FIFO, 0U, &mcanIntf.txMsg);

    //
    // Mark written slot (putIdx) as active and let MCAN to send when available
    //
    MCAN_txBufAddReq(mcanIntf.commBase, putIdx);
}

//
// mcanRecvFrame - receive can frame in RX FIFO0
//
void mcanRecvFrame()
{
    MCAN_RxFIFOStatus fifo0Status;
    uint32_t getIdx;

    //
    // Setting to recv from Rx FIFO0
    //
    fifo0Status.num = MCAN_RX_FIFO_NUM_0;
    
    //
    // Wait until a message is recvd in Rx FIFO0
    //
    do
    {
        MCAN_getRxFIFOStatus(mcanIntf.commBase, &fifo0Status);
    } while (fifo0Status.fillLvl == 0U);

    //
    // Fifo in blocking mode and no message should get lost or FIFO filled up
    //
    ASSERT(!fifo0Status.msgLost && !fifo0Status.fifoFull);

    // Get the next sequential slot for read
    getIdx = fifo0Status.getIdx;

    //
    // Read Message RAM. (From Rx FIFO0)
    //
    MCAN_readMsgRam(mcanIntf.commBase, MCAN_MEM_TYPE_FIFO, 0U, MCAN_RX_FIFO_NUM_0,
                    &mcanIntf.rxMsg);

    //
    // Acknowledge the message and free up the read slot (getIdx) 
    //
    MCAN_writeRxFIFOAck(mcanIntf.commBase, MCAN_RX_FIFO_NUM_0, getIdx);

    const uint8_t DLCToSize[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

    if (mcanIntf.rxMsg.dlc < sizeof(DLCToSize)/sizeof(*DLCToSize))
    {
        mcanIntf.rxSize = DLCToSize[mcanIntf.rxMsg.dlc];
    }
    else
    {
        // Unrecognized DLC coding, setting to 0
        mcanIntf.rxSize = 0;
    }
    mcanIntf.rxIdx = 0;
}
