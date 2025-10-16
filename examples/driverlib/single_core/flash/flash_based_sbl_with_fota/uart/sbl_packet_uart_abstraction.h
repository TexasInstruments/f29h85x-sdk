//###########################################################################
//
// FILE:    sbl_packet_uart_abstraction.h
//
// TITLE:   Internal Low-level abstraction of UART periperial implementation used by the packet interface
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

#ifndef SBL_PACKET_UART_ABSTRACTION_H
#define SBL_PACKET_UART_ABSTRACTION_H

//
// Included Files
//
#include "uart.h"
#include "sbl_packet_interface.h"

extern packetInterface_t gPktIntf;

//
// Utility function:
// Reset communication interface, clear receive buffer and send write buffer, check for data avilabilities (only for handshake)
//
#define comReset() {;}                 // No dedicated UART interface
static inline void comFlushRead(void);  
#define comFlushWrite() {;}            // UART transmission is not buffered, therefore no need to flush
#define comIsDataAvailable()  UART_isDataAvailable(gPktIntf.commBase)

//
// Base UART calls (enableCs must be passed in as raw boolean)
//
static inline uint8_t comReadByte(bool enableCs);
static inline void    comWriteByte(uint8_t byte, bool enableCs);
static inline void    comReadArray(void* const array, size_t length);

//
// Derived funcs from the base function
//
static inline uint16_t  comReadWord(bool enableCs);
static inline void      comWriteWord(uint16_t word, bool enableCs);
static inline void      comWriteDWord(uint32_t dword, bool enableCs);

/* Function implementations */

//
// comFlushRead - This routine flushes recvd read port.
//
static inline void comFlushRead(void)
{
    //
    // flush until all read buffer is empty.
    //
    while (UART_isDataAvailable(gPktIntf.commBase))
    {
        UART_readCharNonBlocking(gPktIntf.commBase);
    }
}        

//
// comReadByte -  This routine fetches one bytes from the gPktIntf.commBase
//                        port and optionally calculate its checksum
//
static inline uint8_t comReadByte(bool enableCs)
{
    uint8_t byte;

    byte = UART_readChar(gPktIntf.commBase);

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
    UART_writeChar(gPktIntf.commBase, byte);

#if ENABLE_CHECKSUM_VALIDATION
    if (enableCs) { gPktIntf.dInfo.checksum += byte; }
#endif /* ENABLE_CHECKSUM_VALIDATION */
}

//
// comReadArray - reads variable length of bytes and output them in the inputted array address
// Note: assumes every read array (data read) requires checksum calculation
//
static inline __attribute__((nonnull))
void comReadArray(void* const array, size_t length)
{
    uint8_t* addr = array;
    
    /* UART_readCharArray() implementation */
    for (int i = 0; i < length; i++)
    {
        //
        // Wait until a char is available.
        //
        while((HWREG(gPktIntf.commBase + UART_O_FR) & UART_FR_RXFE) == UART_FR_RXFE) {;}

        //
        // Read the char.
        //
        addr[i] = (int32_t)(HWREG(gPktIntf.commBase + UART_O_DR));
#if ENABLE_CHECKSUM_VALIDATION
        gPktIntf.dInfo.checksum += addr[i];
#endif /* ENABLE_CHECKSUM_VALIDATION */   
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
    if (enableCs) { gPktIntf.dInfo.checksum += wordData + byteData; }
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
    if (enableCs) { gPktIntf.dInfo.checksum += lsb + msb; }
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

#endif /* SBL_PACKET_UART_ABSTRACTION_H */