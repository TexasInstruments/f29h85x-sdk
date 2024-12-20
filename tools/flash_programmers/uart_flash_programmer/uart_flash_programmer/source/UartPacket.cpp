//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   UartPacket.cpp
//! 
//! \brief  UART messaging protocol in term of command packets
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

//*****************************************************************************
//!
//! \brief  This function constructs the packet to be send to the device
//! 		  
//! Packet Format: | Header | Length | Command | Data | Checksum | Footer | 
//! Size (bytes)   |   2    |   2    |    2    |Length|    2     |   2    |
//!
//! \param packet   The byte vector that stores the content of the outputted packet
//! \param command  The command field of the packet, must be 2 bytes
//! \param dataSize The size of the input data, in bytes
//! \param data	    Pointer to the content of input data
//! 
//! \return         Length of the packet, in bytes
//!
//*****************************************************************************
std::size_t constructPacket(std::vector<uint8_t>&packet, const uint16_t command, const uint16_t dataSize, const uint8_t* data)
{
	std::size_t fullPacketSize = dataSize + 10;

	if (packet.capacity() < fullPacketSize)
	{
		packet.reserve(fullPacketSize);
	}

	uint8_t* dataArr = packet.data();
	uint16_t checksum = 0; //checksum of the Command and the Data

	dataArr[0] = PACKET_HEADER_LSB; //start LSB
	dataArr[1] = PACKET_HEADER_MSB; //start MSB
	dataArr[2] = (uint8_t)(dataSize & 0xFF); //length LSB
	dataArr[3] = (uint8_t)((dataSize & 0xFF00) >> 8); //length MSB
	dataArr[4] = (uint8_t)(command & 0xFF); checksum += (command & 0xFF); //command LSB
	dataArr[5] = (uint8_t)((command & 0xFF00) >> 8); checksum += ((command & 0xFF00) >> 8); //command MSB

	std::size_t index = 6;
	for (std::size_t i = 0; i < dataSize; i++)
	{
		checksum += data[i];
		dataArr[index++] = data[i];
	}

#if checksum_enable
	dataArr[index++] = (uint8_t)(checksum & 0xFF); //checksum LSB
	dataArr[index++] = (uint8_t)((checksum & 0xFF00) >> 8); //checksum MSB
#else 
	dataArr[index++] = 0;
	dataArr[index++] = 0;
#endif /* checksum_enable */

	dataArr[index++] = PACKET_FOOTER_LSB; //end LSB
	dataArr[index++] = PACKET_FOOTER_MSB; //end MSB

	//index is one larger than last index of array so equals the length.
	return(index);
}

//*****************************************************************************
//!
//! \brief  Send the command packet to the kernel running in the device. 
//!	        The flash kernel is expected to respond to the packet by sending an acknowledgement 
//!
//! \param uartHandle  Handle to an instance of UART interface
//! \param packet	   The byte vector which contains the content of the packet
//! \param size		   Size of the packet, in bytes
//! 
//! \return            0 upon success, -1 if error occurs 
//!
//*****************************************************************************
int sendPacket(FlashProgrammer::UartHandler& uartHandle, std::vector<uint8_t>& packet, const std::size_t size)
{
	std::size_t bytesRead;
	uint8_t* packetContent = packet.data();

	bytesRead = uartHandle.sendBytes(packetContent, size);

	if (bytesRead)
	{
		uint8_t byte = uartHandle.readByte();
		if (byte != ACK)
		{
			*g_pOutputStream << std::hex << std::showbase << "Packet nack ERROR with the returned ack value, recvd " << static_cast<std::size_t>(byte) << ", but expecting " << ACK << std::endl;
			return -1;
		}
	}

	*g_pOutputStream << ("Finished sending Packet...") << std::endl;

	return 0;
}

//*****************************************************************************
//!
//! \brief  This function receives the packet from the kernel running in the device. 
//!			And sends ack/nak upon verifing the integrity of the packet content.
//!
//! \param uartHandle  Handle to an instance of UART interface
//! \param packet	   The byte vector that stores the content of the outputted packet
//! \param dataSize	   Pointer to return size of the packet, in bytes
//! 
//! \return            The echoed previous command that triggers the kernel 
//!						to reply with the current packet. If recvd packet fails
//!						integrity check, then DECIPHER_PACKET_ERROR
//!
//*****************************************************************************
uint16_t getPacket(FlashProgrammer::UartHandler& uartHandle, std::vector<uint8_t>& packet, uint16_t* dataSize)
{
	size_t fail = 0;
	uint16_t header, command, size;
	uint16_t checkSum = 0, recievedChecksum = 0;
	uint8_t* dataArr;
	

	header = uartHandle.readWord();
	if (header != FULL_PACKET_HEADER)
	{
		*g_pOutputStream << std::hex << std::showbase << "Packet header ERROR, recvd " << header << ", but expecting " << FULL_PACKET_HEADER << std::endl;
		fail++;
	}
	
	size = uartHandle.readWord();
	
	//
	// Reserve enough packet storage to store data
	//
	if (packet.capacity() < size)
	{
		packet.reserve(size);
	}

	dataArr = packet.data();

#if checksum_enable
	command = uartHandle.readWord(&checkSum);
#else 
	command = uartHandle.readWord();
#endif /* checksum_enable */

	uartHandle.readBytes(dataArr, size);

#if checksum_enable
	for (int i = 0; i < size; i++)
	{
		checkSum += dataArr[i];
	}
	
	recievedChecksum = uartHandle.readWord();
	if (checkSum != recievedChecksum)
	{
		*g_pOutputStream << std::hex << std::showbase << "Packet checksum ERROR, recvd " << checkSum << ", but expecting " << recievedChecksum  << std::endl;
		fail++;
	}
#endif /* checksum_enable */

	header = uartHandle.readWord();
	if (header != FULL_PACKET_FOOTER)
	{
		*g_pOutputStream << std::hex << std::showbase << "Packet footer ERROR, recvd " << header << ", but expecting " << FULL_PACKET_FOOTER << std::endl;
		fail++;
	}

	if (fail)
	{
		uartHandle.sendByte(NAK);
		command = DECIPHER_PACKET_ERROR;
		*g_pOutputStream << "Command packet FAILURE" << std::endl;
	}
	else
	{
		uartHandle.sendByte(ACK);
		*g_pOutputStream << "Command packet SUCCESS" << std::endl;
	}

	*dataSize = size;

	return command;
}

//*****************************************************************************
//!
//! \brief  This function parses the received flash status packet
//!
//! \param packet	   The byte vector that stores the content of the receivied packet
//! \param flashStatus Output pointer to the flash status strcture
//! 
//! \return            0 upon success, -1 if error occurs 
//!
//*****************************************************************************
int parseFlashStatus(std::vector<uint8_t>& packet, FlashStatusCode* flashStatus)
{
	constexpr std::size_t packedSize = sizeof(flashStatus->status) + sizeof(flashStatus->address) + sizeof(flashStatus->flashAPIError) + sizeof(flashStatus->flashAPIFsmStatus);

	//
	// Only catches Seg fault, does not gurantee actual memory content
	//
	if (packet.capacity() < packedSize)
	{
		*g_pOutputStream << "decipherFlashPacket ERROR: recvd packet doesn't contain enough content to decipher" << std::endl;
		return -1;
	}

	uint8_t* packetData = packet.data();
	int offset = 0;

	//
	// Assumes system to be little-endian...
	//
	std::memcpy(&flashStatus->status, &packetData[offset], sizeof(flashStatus->status));
	offset += sizeof(flashStatus->status);

	std::memcpy(&flashStatus->address, &packetData[offset], sizeof(flashStatus->address));
	offset += sizeof(flashStatus->address);

	std::memcpy(&flashStatus->flashAPIError, &packetData[offset], sizeof(flashStatus->flashAPIError));
	offset += sizeof(flashStatus->flashAPIError);

	std::memcpy(&flashStatus->flashAPIFsmStatus, &packetData[offset], sizeof(flashStatus->flashAPIFsmStatus));
	offset += sizeof(flashStatus->flashAPIFsmStatus);

	return 0;
}

//*****************************************************************************
//!
//! \brief  This function interprets the error status and returns error dialogue
//!
//! \param status	   The status attribute of the command packet
//!
//*****************************************************************************
void printErrorStatus(uint16_t status)
{
	switch (status)
	{
	case BLANK_ERROR:
		*g_pOutputStream << "ERROR Status: BLANK_ERROR" << std::endl;
		break;
	case VERIFY_ERROR:
		*g_pOutputStream << "ERROR Status: VERIFY_ERROR" << std::endl;
		break;
	case PROGRAM_ERROR:
		*g_pOutputStream << "ERROR Status: PROGRAM_ERROR" << std::endl;
		break;
	case COMMAND_ERROR:
		*g_pOutputStream << "ERROR Status: COMMAND_ERROR" << std::endl;
		break;
	case UNLOCK_ERROR:
		*g_pOutputStream << "ERROR Status: UNLOCK_ERROR" << std::endl;
		break;
	case AUTHENTICATION_ERROR:
		*g_pOutputStream << "ERROR Status: AUTHENTICATION_ERROR" << std::endl;
		break;
	case INCORRECT_DATA_BUFFER_LENGTH:
		*g_pOutputStream << "Flash API Error: Incorrect Data Buffer Length" << std::endl;
		break;
	case DATA_ECC_BUFFER_LENGTH_MISMATCH:
		*g_pOutputStream << "Flash API Error: Data ECC Buffer Length Mismatch" << std::endl;
		break;
	case FLASH_REGS_NOT_WRITABLE:
		*g_pOutputStream << "Flash API Error: Flash Registers not Writable" << std::endl;
		break;
	case FEATURE_NOT_AVAILABLE:
		*g_pOutputStream << "Flash API Error: Feature not Available" << std::endl;
		break;
	case INVALID_ADDRESS:
		*g_pOutputStream << "Flash API Error: Invalid Address" << std::endl;
		break;
	case INVALID_CPUID:
		*g_pOutputStream << "Flash API Error: Invalid CPUID" << std::endl;
		break;
	case FAILURE:
		*g_pOutputStream << "Flash API Error: Failure" << std::endl;
		break;
	default:
		*g_pOutputStream << "ERROR Status: Not Recognized Error" << std::endl;
		break;
	}
}

/** @} */