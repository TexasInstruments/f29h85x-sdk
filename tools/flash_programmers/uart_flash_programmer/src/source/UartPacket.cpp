//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   UartPacket.cpp
//! 
//! \brief  Includes High-level UART packet flow implementation
//!
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

#include "../include/UartPacket.h"

namespace FlashProgrammer
{
	//*****************************************************************************
	//!
	//! \brief  Send the packet to the kernel running in the device. 
	//!	        The flash kernel is expected to respond to the packet by sending an acknowledgement 
	//!
	//! \param size		   Size of the packet, in bytes
	//! 
	//! \return            0 upon success, -1 if error occurs 
	//!
	//*****************************************************************************
	int UartPacketExecutor::sendPacket(const std::size_t size)
	{
		std::size_t bytesRead;
		uint8_t result, footer;
		uint8_t* packetContent = _buffer.data();

		// Flush input/output buffer
		_uart.clearPort(true, true);

		//
		// Send packet header and proceed until acknowledgement (handshake)
		// 
		// UART RX-interrupt requires at least two bytes to trigger, therefore send header twice
		_uart.sendByte(PACKET_HEADER);
		_uart.sendByte(PACKET_HEADER);
		// Add a tiny delay for OS to respond 
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		while (!(_uart.isDataAvailable() && (result = _uart.readByte()) == PACKET_ACK))
		{
			// Wait for 50ms (>line delay)
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			if (!_uart.isDataAvailable())
			{
				_uart.sendByte(PACKET_HEADER);
			}
		}
		 
		// Send end of handshake and proceed with payloads
		_uart.sendByte(PACKET_END_HANDSHAKE);
		while (_uart.readByte() != PACKET_END_HANDSHAKE) {;}

		bytesRead = _uart.sendBytes(packetContent, size);

		if (bytesRead)
		{
		
			uint8_t byte = _uart.readByte();
			if (byte != PACKET_ACK)
			{
				*g_pOutputStream << std::hex << std::showbase << "sendPacket ERROR with incorrect ack value from the target, recvd " << static_cast<std::size_t>(byte) << ", but expecting " << PACKET_ACK << " (" << STRING_LITERAL(PACKET_ACK) << ")" << std::endl;
				return -1;
			}
		}

		*g_pOutputStream << ("sendPacket success") << std::endl;

		return 0;
	}

	//*****************************************************************************
	//!
	//! \brief  This function receives the packet from the kernel running in the device. 
	//!			And sends ack/nak upon verifing the integrity of the packet content.
	//! 
	//! (Full packet - valid for initial packet response, end-of-transmission (EOT) packet. If sent outside of the two, it'll be treated as a NAK packet)
	//! Packet Format: | Header | Payload Size |   Payload(s)   | Payload Checksum | Footer | 
	//! Size (bytes)   |   1    |       2      |   (oPkt_t(s))  |         2        |   1    |
	//!
	//! (Data Frame NAK status Packet - only valid during data tranmission)
	//! Packet Format: | NAK | Payload Size |   Payload(s)   | Payload Checksum | Footer | 
	//! Size (bytes)   |  1  |       2      |   (oPkt_t(s))  |         2        |   1    |
	//!
	//! (Data Frame ACK Packet - only valid during data tranmission)
	//! Packet Format: | ACK | Data Size | Data Checksum |
	//! Size (bytes)   |  1  |     2     |       2       |
	//! 
	//! \param uartHandle  Handle to an instance of UART interface
	//! \param dataSize	   Pointer to return size of the payload, in bytes
	//! 
	//! \return            0 upon success, -1 if error occurs 
	//!
	//*****************************************************************************
	int UartPacketExecutor::getPacket(uint16_t* size)
	{
		int retVal = 0;
		uint8_t header, footer;
		uint16_t rcvdChecksum, checkSum = 0;
		uint8_t* dataArr;

		// If received isn't a header, keep sending NAK until received (handshake)
		// No sleep needed as readByte is a blocking function
		header = _uart.readByte();
		while (!(header == PACKET_HEADER || header == PACKET_NAK))
		{
			*g_pOutputStream << std::hex << std::showbase << "getPacket header ERROR, recvd " << (unsigned int)header << ", but expecting " << PACKET_HEADER << " (" << STRING_LITERAL(PACKET_HEADER) << ")" << std::endl;
			_uart.sendByte(PACKET_NAK);
			header = _uart.readByte();
		}

		// Now handshake is received, send ACK till sender sends end of handshake
		_uart.sendByte(PACKET_ACK);
		while (_uart.readByte() != PACKET_END_HANDSHAKE)
		{
			_uart.sendByte(PACKET_ACK);
		}

		// Send end of handshake and proceed with payloads
		_uart.sendByte(PACKET_END_HANDSHAKE);

		*size = _uart.readWord();
	
		//
		// Reserve enough packet storage to store data
		//
		if (_buffer.capacity() < *size)
		{
			_buffer.reserve(*size);
		}
		dataArr = _buffer.data();

		_uart.readBytes(dataArr, *size);

		rcvdChecksum = _uart.readWord();

	#if ENABLE_CHECKSUM_VALIDATION
		for (int i = 0; i < *size; i++)
		{
			checkSum += dataArr[i];
		}
	
		if (checkSum != rcvdChecksum)
		{
			*g_pOutputStream << std::hex << std::showbase << "getPacket checksum ERROR, recvd " << checkSum << ", but expecting " << rcvdChecksum << std::endl;
			retVal = -1;
		}
	#endif /* enable_checksum_validation */

		footer = _uart.readByte();
		if (footer != PACKET_FOOTER)
		{
			*g_pOutputStream << std::hex << std::showbase << "getPacket footer ERROR, recvd " << (unsigned int)header << ", but expecting " << PACKET_FOOTER << " (" << STRING_LITERAL(PACKET_HEADER) << ")" << std::endl;
			retVal = -1;
		}

		// Ack/Nak the packet 
		if (retVal)
		{
			_uart.sendByte(PACKET_NAK);
			*g_pOutputStream << "getPacket FAILURE" << std::endl;
		}
		else
		{
			_uart.sendByte(PACKET_ACK);
			*g_pOutputStream << "getPacket success" << std::endl;
		}

		if (header == PACKET_NAK)
		{
			*g_pOutputStream << "FAILURE: NAK packet received, an error has occurred on the device and prevented operation from completion." << std::endl;
			retVal = -1;
		}

		return retVal;
	}

	//*****************************************************************************
	//!
	//! \brief  This function runs the packet protocol flow with an inputted command packet, for the UART interface
	//! 
	//! \param cmdPkt	   The input command packet to be sent to the target
	//! \param file	  	   The file to be sent to the target, if applicable
	//! 
	//! \details This function sends the command packet to the target, and waits for a command response packet to act accordingly.
	//!			If the target expects data, it will send the file to the target.
	//!			If the target sends a NAK packet in the process, it will return an error.
	//! 
	//! \return            0 upon success, -1 if error occurs 
	//!
	//*****************************************************************************
	int UartPacketExecutor::initiatePacketFlow(CommandPkt_t& cmdPkt, const char* file)
	{
		int retVal = 0;
		size_t packetSize;  // Shouldn't exceed payloadsize (uint16_t max, 65535) + packet metadata (8 byte)
		uint16_t payloadSize;
		bool expectsNakPacket = false;


		// Send handshake packet with command payload
		packetSize = constructCommandPacket(cmdPkt);
		retVal |= sendPacket(packetSize);

		// Receive the packet with command response
		retVal |= getPacket(&payloadSize);
		if (retVal)
		{
			*g_pOutputStream << "initiatePacketFlow ERROR: failure in getting properly formatted packet, exiting...\n";
			return -1;
		}

		// Process the packet
		retVal |= _pktContent->run(_buffer, payloadSize, &cmdPkt);

		if (!_pktContent->is_crPktAvail)
		{
			*g_pOutputStream << "initiatePacketFlow ERROR: Host did not receive any command response regarding host inquiry, please double check target behavior\n";
			return -1;
		}

		CommandResponsePkt_t& rcvdResponse = _pktContent->_crPkt;

		// Target calls for for data transmission
		if (rcvdResponse.expectsData)
		{
			if (file == nullptr)
			{
				*g_pOutputStream << "initiatePacketFlow ERROR: Target requests for data transmission but host did not implement which file to use, please adjust the implementation parameters accordingly\n";
				return -1;
			}

			// Target requests for time delay (only applicable if expected to receive data)
			if (rcvdResponse.timeDelay_ms)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(rcvdResponse.timeDelay_ms));
			}

			// Send the application image
			if (downloadApplication(_uart, file, rcvdResponse.maxPayloadSize) == -1)
			{
				// host now expects NAK packet
				expectsNakPacket = true;
				retVal = -1;
			}
		}

		// Target signals for NAK status packet which indicates target error occurred and EOT.
		if (expectsNakPacket)
		{
			retVal |= getPacket(&payloadSize);
			retVal |= _pktContent->run(_buffer, payloadSize);
			*g_pOutputStream << "An error has occurred and the operation did not complete\n";
		}
		// Target signals for EOT packet
		else if (rcvdResponse.expectsEOTpacket)
		{
			retVal |= getPacket(&payloadSize);
			retVal |= _pktContent->run(_buffer, payloadSize);
		}

		return retVal;
	}

}

/** @} */