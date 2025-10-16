//###########################################################################
//
//  FILE:    sbl_packet_interface.h
//
//  TITLE:   Packet communication interface that interacts with the host
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

#ifndef SBL_PACKET_INTERFACE_H
#define SBL_PACKET_INTERFACE_H

//
// Included Files
//
#include <board.h>
#include "f29x_packet_comm_protocol.h"

#define MAX_PAYLOAD_SIZE     UINT16_MAX // Use this macro for the maximum value of CommandResponsePkt_t.maxPayloadSize

typedef struct packetInterface_t_
{
    /**
     * @brief   Base Address of the communication periperial module
     */
    const uint32_t commBase;

    /**
     * @brief   The current data transmition status
     */
    bool           isInDataMode;    

    struct commDataStruct_
    {
        /**
        * @brief   pointer to the data buffer to store peripheral data, must be the size of bufferSize
        */
        uint8_t* const  dataPtr;
        
        /**
        * @brief    size of the data buffer (DATA_BUFFER_SIZE)
        */
        const uint16_t  bufferSize;

        /**
        * @brief   The current read index pointer
        */
        uint16_t        readIdx;

        /**
        * @brief   The current data capacity 
        */
        uint16_t        readSize;

        /**
        * @brief   Checksum of data content (sum of all data, in 2 bytes)
        */
        uint16_t        checksum;

    } dInfo;    

#if ENABLE_SHADOW_BUFFER
    struct commShadowStruct_
    {
        bool        isRxDmaActive;
        bool        isShadowEnabled;

        uint16_t    shadowReadIdx;
        uint16_t    shadowDataSize;
    } sInfo;
#endif /* ENABLE_SHADOW_BUFFER */

} packetInterface_t;

//
// FSM function
//
void sblResetInterface(void);
void sblStartDataMode(void);
void sblEndDataMode(void);

//
// Funcs to obtain and send packets
//
int sblGetCommandPacket(CommandPkt_t* cmdPkt);
int sblSendPacket(int n, ...);

//
// Functions to obtain data during data transfer
//
uint8_t sblGetData(void);
void sblGetDataArray(uint8_t* const array, size_t length);


#endif /* SBL_PACKET_INTERFACE_H */