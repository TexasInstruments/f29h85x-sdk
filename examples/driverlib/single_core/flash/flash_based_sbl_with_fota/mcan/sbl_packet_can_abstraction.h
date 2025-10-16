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

#ifndef SBL_PACKET_CAN_ABSTRACTION_H
#define SBL_PACKET_CAN_ABSTRACTION_H

//
// Included Files
//
#include <stdint.h>
#include "mcan.h"
#include "sbl_packet_interface.h"

typedef struct mcanInterface_t_
{
    const uint32_t          commBase;
    const uint32_t          maxDataSize;
    MCAN_TxBufElement       txMsg;
    MCAN_RxBufElement       rxMsg;
    uint32_t                txIdx;
    uint32_t                rxSize;
    uint32_t                rxIdx;
} mcanInterface_t;

extern packetInterface_t gPktIntf;
extern mcanInterface_t   mcanIntf;

//
// Utility function:
// Reset communication interface, clear receive buffer and send write buffer, check for data avilabilities (only for handshake)
//
void comReset(void);
static inline void comFlushRead(void);
static inline void comFlushWrite(void);
#define comIsDataAvailable {;} // Handshake disabled therefore not needed

//
// Base CAN-FD calls (enableCs must be passed in as raw boolean)
//
static inline uint8_t comReadByte(bool enableCs);
static inline void    comWriteByte(uint8_t byte, bool enableCs);
static inline void    comReadArray(void* const array, size_t length);

//
// Derived CAN-FD funcs from the base function
//
static inline uint16_t  comReadWord(bool enableCs);
static inline void      comWriteWord(uint16_t word, bool enableCs);
static inline void      comWriteDWord(uint32_t dword, bool enableCs);

//
// MCAN internal implementation
//
extern void mcanSendFrame(uint32_t size);
extern void mcanRecvFrame();

/* Function implementations */

//
// No receive buffer to flush other than resetting mcan interface
//
static inline void comFlushRead()
{
    mcanIntf.rxIdx = 0;
    mcanIntf.rxSize = 0;
}

//
// Send all existing data now
//
static inline void comFlushWrite()
{
    if (mcanIntf.txIdx != 0)
    {
        mcanSendFrame(mcanIntf.txIdx);
    }
    //mcanSendFrame will reset txIdx to 0

}

//
// comReadByte -  This routine fetches one bytes from the gPktIntf.commBase
//                        port and optionally calculate its checksum
//
static inline uint8_t comReadByte(bool enableCs)
{
    if(mcanIntf.rxIdx >= mcanIntf.rxSize)
    {
        mcanRecvFrame();
    }
    
    uint8_t byte;
    byte = (uint8_t)mcanIntf.rxMsg.data[mcanIntf.rxIdx++];

#if ENABLE_CHECKSUM_VALIDATION
    if (enableCs) { gPktIntf.dInfo.checksum += byte; }
#endif /* ENABLE_CHECKSUM_VALIDATION */

    return byte;
}

//
// comWriteByte - Sends a uint8_t byte and optionally calculate its checksum.
//
static inline void comWriteByte(uint8_t byte, bool enableCs)
{
    mcanIntf.txMsg.data[mcanIntf.txIdx++] = byte;

    if(mcanIntf.txIdx >= mcanIntf.maxDataSize)
    {
        mcanSendFrame(mcanIntf.txIdx);
    }

#if ENABLE_CHECKSUM_VALIDATION
    if (enableCs) { gPktIntf.dInfo.checksum += byte; }
#endif /* ENABLE_CHECKSUM_VALIDATION */
}

//
// comReadArray - reads variable length of bytes and output them in the inputted array address
// Note: assumes every read array (data read) requires checksum calculation
//
static inline __attribute__((nonnull))
void comReadArray(void* const array, uint32_t length)
{
    uint8_t* currAddr = array;
    uint32_t currLen = 0;

    while (currLen < length)
    {
        if (mcanIntf.rxIdx >= mcanIntf.rxSize)
        {
            mcanRecvFrame();
        }
        
        uint32_t bytesAvail, bytesToRead;
        // TODO: change this srcAddr pointer to the same type of rxMsg.data once data type changes
        uint16_t* srcAddr = &mcanIntf.rxMsg.data[mcanIntf.rxIdx];

        bytesAvail = mcanIntf.rxSize - mcanIntf.rxIdx;
        bytesToRead = (bytesAvail < (length - currLen)) ? bytesAvail : length - currLen;

        for (uint32_t i = 0; i < bytesToRead; i++)
        {
            currAddr[i] = (uint8_t)srcAddr[i];
#if ENABLE_CHECKSUM_VALIDATION
            gPktIntf.dInfo.checksum += currAddr[i];
#endif /* ENABLE_CHECKSUM_VALIDATION */  
        }

        mcanIntf.rxIdx += bytesToRead;
        currAddr += bytesToRead;
        currLen += bytesToRead;
    }
}

//#############################################################################
//
// Derived comm funcs
//
//#############################################################################

//
// comReadWord -  This routine fetches two bytes from the gPktIntf.commBase
//                        port and puts them together to form a single
//                        16-bit value.  It is assumed that the host is
//                        sending the data in the order LSB followed by MSB.
//
static inline uint16_t comReadWord(bool enableCs)
{
    uint16_t wordData;
    uint16_t byteData;

    //
    // Fetch the LSB and verify back to the host
    //
    wordData = comReadByte(false);

    //
    // Fetch the MSB and verify back to the host
    //
    byteData = comReadByte(false);

#if ENABLE_CHECKSUM_VALIDATION
    if (enableCs) { gPktIntf.dInfo.checksum += (wordData + byteData); }
#endif /* ENABLE_CHECKSUM_VALIDATION */

    //
    // form the wordData from the MSB:LSB
    //
    wordData |= (byteData << 8);

    return wordData;
}

//
// comWriteWord - Sends a uint16_t word.
//
static inline void comWriteWord(uint16_t word, bool enableCs)
{
    uint8_t lsb,msb;

    lsb = (word & 0xFF);
    msb = ((word >> 8) & 0xFF);

    //
    // send LSB of word, driverlib.
    //
    comWriteByte(lsb, false);

    //
    // send MSB of word, driverlib.
    //
    comWriteByte(msb, false);

#if ENABLE_CHECKSUM_VALIDATION
    if (enableCs) { gPktIntf.dInfo.checksum += (lsb + msb); }
#endif /* ENABLE_CHECKSUM_VALIDATION */
}

//
// comWriteWord - Sends a uint32_t dword.
//
static inline void comWriteDWord(uint32_t dword, bool enableCs)
{
    uint8_t const* ptr = (uint8_t const*) &dword;

    //
    // LSB to MSB
    //
    for (int i = 0; i < 4; i++)
    {
        comWriteByte(ptr[i], false);
#if ENABLE_CHECKSUM_VALIDATION
    if (enableCs) { gPktIntf.dInfo.checksum += ptr[i]; }
#endif /* ENABLE_CHECKSUM_VALIDATION */
    }
}

#endif /* SBL_PACKET_CAN_ABSTRACTION_H */