//###########################################################################
//
//  FILE:    sbl_packet_config.h
//
//  TITLE:   Packet Interface Configuration Settings for each specific communication 
//           peripheral and memory interfaces - Flash-based CAN in this case
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

#ifndef SBL_PACKET_CONFIG_H
#define SBL_PACKET_CONFIG_H

/* Flash-based CAN peripheral configuration */

//
// Packet Interface Configuration Settings
//
/* Buffer size to store read data, therefore should be DATA_BUFFER_SIZE <= MAX_PAYLOAD_SIZE. */
#define DATA_BUFFER_SIZE      32768U                         // Flash-based SBL: reserved 0x8000 for sbl_packet_scratchpad (twice the size of maximum read - 0x4000 for CP)

/* Exchange handshake prior to sending full packet, recommended for communication interfaces with no build-in handshakes (UART, I2C, SPI...) in making sure host/target receives the request regardless of delays (timings) */
#define ENABLE_PACKET_HANDSHAKE 0                             // Disabled since CAN has arbitration at the protocol level, elinmate the need for handshakes

/* Flag to enable (1/0) shadow buffer, which uses DMA transfer rather than direct cpu reads. */
#define ENABLE_SHADOW_BUFFER    0                             // Disabled DMA since CAN is not a DMA trigger

/* The available buffer threshold to trigger a shadow read, only applicable when shadow buffer is enabled */
#define SHADOW_THRESHOLD (uint16_t) DATA_BUFFER_SIZE * 0.25f  // irrelevant


#define OPT_ATTR                                              // No function attributes needed

//
// CAN abstraction layer
//
#include "sbl_packet_can_abstraction.h"

#if DATA_BUFFER_SIZE > UINT16_MAX || MAX_PAYLOAD_SIZE > UINT16_MAX
#error "SBL packet interface's data buffer cannot exceed 16 bits, as the "Request Datasize" field is only a 2 byte attribute."
#endif

#endif /* SBL_PACKET_CONFIG_H */