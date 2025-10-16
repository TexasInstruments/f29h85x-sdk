//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   PacketParser.cpp
//! 
//! \brief  Includes the general function and strcture used in packet communication protocol
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

#include "../include/PacketParser.h"

namespace FlashProgrammer
{
	//*****************************************************************************
	//!
	//! \brief  This function constructs the (full) packet to be send to the device
	//! 		  
	//! Packet Format: | Header | Payload Size |   Payload(s)   | Payload Checksum | Footer | 
	//! Size (bytes)   |   1    |       2      |   (oPkt_t(s))  |         2        |   1    |
	//!
	//! \param cPkt		An instance of payload struct CommandPkt_t, with all of its attributes properly populated
	//! 
	//! \return         Length of the packet, in bytes
	//!
	//*****************************************************************************
	std::size_t PacketExecutor::constructCommandPacket(CommandPkt_t& cPkt)
	{
		uint16_t dataSize = COMMAND_PACKET_SIZE(&cPkt);
		std::size_t fullPacketSize = COMMAND_PACKET_SIZE(&cPkt) + 
			PACKET_PLSIZE_BYTE + PACKET_CHECKSUM_BYTE + PACKET_FOOTER_BYTE; // Excluding HEADER

		if (_buffer.capacity() < fullPacketSize)
		{
			_buffer.reserve(fullPacketSize);
		}

		uint8_t* dataArr = _buffer.data();
		std::size_t index = 0;

		// Not including HEADER in the payload since the host & target uses handshake to exchange and ack HEADER
		//dataArr[index++] = PACKET_HEADER;
		dataArr[index++] = (uint8_t)(dataSize & 0xFF);			// Data size LSB
		dataArr[index++] = (uint8_t)((dataSize & 0xFF00) >> 8);	// Data size MSB

		uint16_t checksum = 0; //checksum is only calculated on the data/payload itself

		// CommandPkt_t data 
		dataArr[index++] = (uint8_t)(PayloadType::Command & 0xFF);		checksum += (uint8_t)(PayloadType::Command & 0xFF);	// .type
		dataArr[index++] = (uint8_t)(cPkt.command & 0xFF);				checksum += (uint8_t)(cPkt.command & 0xFF);			// .command LSB
		dataArr[index++] = (uint8_t)((cPkt.command & 0xFF00) >> 8);		checksum += (uint8_t)((cPkt.command & 0xFF00) >> 8);// .command MSB
		dataArr[index++] = (uint8_t)(cPkt.addlContentLength & 0xFF);			checksum += (uint8_t)(cPkt.addlContentLength & 0xFF);	      // .addlContentLength LSB
		dataArr[index++] = (uint8_t)((cPkt.addlContentLength & 0xFF00) >> 8);	checksum += (uint8_t)((cPkt.addlContentLength & 0xFF00) >> 8);// .addlContentLength MSB
		for (std::size_t i = 0; i < cPkt.addlContentLength; i++)
		{
			dataArr[index++] = (uint8_t)cPkt.addlContentAddr[i];
			checksum += (uint8_t)cPkt.addlContentAddr[i];
		}

#if ENABLE_CHECKSUM_VALIDATION
		dataArr[index++] = (uint8_t)(checksum & 0xFF);			//checksum LSB
		dataArr[index++] = (uint8_t)((checksum & 0xFF00) >> 8); //checksum MSB
#else
		dataArr[index++] = 0;
		dataArr[index++] = 0;
#endif /* enable_checksum_validation */

		dataArr[index++] = PACKET_FOOTER;

		//index is one larger than last index of array so equals the length.
		if (index != fullPacketSize)
		{
			throw std::runtime_error("constructCommandPacket ERROR: mismatch packet content size, please double check CommandPkt_t input and CommandPkt_t size calculation ");
		}

		return(fullPacketSize);
	}

	//*****************************************************************************
	//!
	//! \brief  High-level function to run the (generic) payload handler, feel free to extend the 
	//!			class and make alternative workflow for any host command.
	//! 
	//! \param payload	   The byte vector that stores the content of payload
	//! \param dataSize	   Size of the payload
	//! \param pCmdPkt	   Optional arugment of CommandPkt_t*, pass in to handle CommandResponsePkt_t
	//! 
	//! \return            0 upon success, -1 if error occurs 
	//!
	//*****************************************************************************
	int PayloadProcessor::run(std::vector<uint8_t>& payload, const std::size_t size, CommandPkt_t* pCmdPkt)
	{
		int retVal = 0;

		if (parsePayload(payload, size))
		{
			*g_pOutputStream << "PayloadHandler::run ERROR: Parse payload failed, therefore payload content will not be interpreted.\n";
			return -1;
		}

		*g_pOutputStream << "\n";

		if (is_crPktAvail)
		{
			retVal |= crPktHandler(pCmdPkt);
		}

		if (is_fsPktAvail)
		{
			retVal |= fsPktHandler();
		}

		if (is_msgPktAvail)
		{
			retVal |= msgPktHandler();
		}

		if (is_cmdPktAvail)
		{
			retVal |= cmdPktHandler();
		}

		if (is_errPktAvail)
		{
			retVal |= errPktHandler();

		}

		return retVal;
	}

	//*****************************************************************************
	//!
	//! \brief  This function parse the received raw packet content and convert them 
	//!			into the corresponding payload strcture
	//! 
	//! \param payload	   The byte vector that stores the content of payload
	//! \param dataSize	   Size of the payload
	//! 
	//! \return            0 upon success, -1 if error occurs 
	//!
	//*****************************************************************************
	int PayloadProcessor::parsePayload(std::vector<uint8_t>& payload, const size_t size)
	{
		uint8_t* dataArr = payload.data();
		uint8_t* endArr = dataArr + size;

		this->reset();

		while (dataArr != endArr)
		{
			size_t offset = 0;
			switch ((PayloadType)*dataArr)
			{
			case Command:
				offset = parseCommandPkt(dataArr);
				break;
			case CommandResponse:
				offset = parseCommandResponsePkt(dataArr);
				break;
			case FlashStatus:
				offset = parseFlashStatusPkt(dataArr);
				break;
			case Message:
				offset = parseMessagePkt(dataArr);
				break;
			case ErrorStatus:
				offset = parseErrorStatusPkt(dataArr);
				break;
			default:
				*g_pOutputStream << "parsePayload ERROR, rcvd PayloadType: " + std::to_string((unsigned int)*dataArr) + " is unrecognized by the host. Please double check target packet content." << std::endl;
				return -1;
			}

			dataArr += offset;
			if (dataArr > endArr)
			{
				*g_pOutputStream << "parsePayload ERROR, mismatch payload size, packet metadata indicates size of " << size << " but actual content size is " << (size_t)(dataArr - endArr) << std::endl;
				return -1;
			}
		}

		return 0;
	}

	//*****************************************************************************
	//!
	//! \brief  This function parses the received command response content
	//!
	//! \param data		   The data array that stores the content of the receivied packet
	//! 
	//! \return            size of the content
	//!
	//*****************************************************************************
	uint16_t PayloadProcessor::parseCommandPkt(uint8_t* data)
	{
		uint16_t packedSize;
		int offset = 0;
		uint8_t* dataArr;

		//
		// Assumes system to be little-endian...
		//
		_cmdPkt.payloadType = (PayloadType)data[offset++];

		std::memcpy(&_cmdPkt.command, &data[offset], sizeof(_cmdPkt.command));
		offset += sizeof(_cmdPkt.command);

		std::memcpy(&_cmdPkt.addlContentLength, &data[offset], sizeof(_cmdPkt.addlContentLength));
		offset += sizeof(_cmdPkt.addlContentLength);

		if (_cmdPktBuf.capacity() < _cmdPkt.addlContentLength)
		{
			_cmdPktBuf.reserve(_cmdPkt.addlContentLength);
		}
		dataArr = _cmdPktBuf.data();
		std::memcpy(dataArr, &data[offset], _cmdPkt.addlContentLength);
		_cmdPkt.addlContentAddr = (char*)dataArr;
		offset += _cmdPkt.addlContentLength;

		is_cmdPktAvail = true;

		//offset is one larger than last index so equals the length.
		packedSize = COMMAND_PACKET_SIZE(&_cmdPkt);
		if (offset != packedSize)
		{
			*g_pOutputStream << "_parseCommandPkt ERROR: mismatch rcvd packet content size, please double check CommandPkt_t input and CommandPkt_t size calculation" << std::endl;
			is_cmdPktAvail = false;
		}

		return packedSize;
	}


	//*****************************************************************************
	//!
	//! \brief  This function parses the received command response content
	//!
	//! \param data		   The data array that stores the content of the receivied packet
	//! 
	//! \return            size of the content
	//!
	//*****************************************************************************
	uint16_t PayloadProcessor::parseCommandResponsePkt(uint8_t* data)
	{
		constexpr std::size_t packedSize = COMMAND_RESPONSE_PACKET_SIZE;
		int offset = 0;

		//
		// Assumes system to be little-endian...
		//
		_crPkt.payloadType = (PayloadType)data[offset++];

		std::memcpy(&_crPkt.echoCommand, &data[offset], sizeof(_crPkt.echoCommand));
		offset += sizeof(_crPkt.echoCommand);

		_crPkt.expectsData = (uint8_t)data[offset++];

		std::memcpy(&_crPkt.timeDelay_ms, &data[offset], sizeof(_crPkt.timeDelay_ms));
		offset += sizeof(_crPkt.timeDelay_ms);

		std::memcpy(&_crPkt.maxPayloadSize, &data[offset], sizeof(_crPkt.maxPayloadSize));
		offset += sizeof(_crPkt.maxPayloadSize);

		_crPkt.expectsEOTpacket = (uint8_t)data[offset++];

		_crPkt.reserved = (uint8_t)data[offset++];

		is_crPktAvail = true;

		//offset is one larger than last index so equals the length.
		if (offset != packedSize)
		{
			*g_pOutputStream << "_parseCommandResponsePkt ERROR: mismatch rcvd packet content size, please double check CommandResponsePkt_t input and CommandResponsePkt_t size calculation" << std::endl;
			is_crPktAvail = false;
		}

		return packedSize;
	}

	//*****************************************************************************
	//!
	//! \brief  This function parses the received flash status content
	//!
	//! \param data		   The data array that stores the content of the receivied packet
	//! 
	//! \return            size of the content
	//!
	//*****************************************************************************
	uint16_t PayloadProcessor::parseFlashStatusPkt(uint8_t* data)
	{
		constexpr std::size_t packedSize = FLASH_PACKET_SIZE;
		int offset = 0;

		//
		// Assumes system to be little-endian...
		//
		_fsPkt.payloadType = (PayloadType)data[offset++];

		std::memcpy(&_fsPkt.status, &data[offset], sizeof(_fsPkt.status));
		offset += sizeof(_fsPkt.status);

		std::memcpy(&_fsPkt.address, &data[offset], sizeof(_fsPkt.address));
		offset += sizeof(_fsPkt.address);

		std::memcpy(&_fsPkt.flashAPIError, &data[offset], sizeof(_fsPkt.flashAPIError));
		offset += sizeof(_fsPkt.flashAPIError);

		std::memcpy(&_fsPkt.flashAPIFsmStatus, &data[offset], sizeof(_fsPkt.flashAPIFsmStatus));
		offset += sizeof(_fsPkt.flashAPIFsmStatus);

		is_fsPktAvail = true;

		//offset is one larger than last index so equals the length.
		if (offset != packedSize)
		{
			*g_pOutputStream << "_parseFlashStatusPkt ERROR: mismatch rcvd packet content size, please double check FlashStatusPkt_t input and FlashStatusPkt_t size calculation" << std::endl;
			is_fsPktAvail = false;
		}


		return packedSize;
	}

	//*****************************************************************************
	//!
	//! \brief  This function parses the received command response content
	//!
	//! \param data		   The data array that stores the content of the receivied packet
	//! 
	//! \return            size of the content
	//!
	//*****************************************************************************
	uint16_t PayloadProcessor::parseMessagePkt(uint8_t* data)
	{
		uint16_t packedSize;
		int offset = 0;
		uint8_t* dataArr;

		//
		// Assumes system to be little-endian...
		//
		_msgPkt.payloadType = (PayloadType)data[offset++];

		std::memcpy(&_msgPkt.length, &data[offset], sizeof(_msgPkt.length));
		offset += sizeof(_msgPkt.length);

		if (_msgPktBuf.capacity() < _msgPkt.length)
		{
			_msgPktBuf.reserve(_msgPkt.length);
		}
		dataArr = _msgPktBuf.data();
		std::memcpy(dataArr, &data[offset], _msgPkt.length);
		_msgPkt.msgAddr = (char*)dataArr;
		offset += _msgPkt.length;

		is_msgPktAvail = true;

		//offset is one larger than last index so equals the length.
		packedSize = MESSAGE_PACKET_SIZE(&_msgPkt);
		if (offset != packedSize)
		{
			*g_pOutputStream << "_parseMessagePkt ERROR: mismatch rcvd packet content size, please double check MessagePkt_t input and MessagePkt_t size calculation" << std::endl;
			is_msgPktAvail = false;
		}

		return packedSize;
	}

	//*****************************************************************************
	//!
	//! \brief  This function parses the received command response content
	//!
	//! \param data		   The data array that stores the content of the receivied packet
	//! 
	//! \return            size of the content
	//!
	//*****************************************************************************
	uint16_t PayloadProcessor::parseErrorStatusPkt(uint8_t* data)
	{
		uint16_t packedSize;
		int offset = 0;
		uint8_t* dataArr;

		//
		// Assumes system to be little-endian...
		//
		_errPkt.payloadType = (PayloadType)data[offset++];

		std::memcpy(&_errPkt.errorMsgCode, &data[offset], sizeof(_errPkt.errorMsgCode));
		offset += sizeof(_errPkt.errorMsgCode);

		_errPkt.recoveryStatus = (PayloadType)data[offset++];
		_errPkt.hasSprintfArgs = (PayloadType)data[offset++];
		_errPkt.numArgs = (PayloadType)data[offset++];

		if (_errPktBuf.capacity() < _errPkt.numArgs)
		{
			_errPktBuf.reserve(_errPkt.numArgs * SIZE_O_VAL(ErrorStatusPkt_t, pArgsVal));
		}
		dataArr = _errPktBuf.data();
		_errPkt.pArgsVal = (uint32_t*)dataArr;

		for (int i = 0; i < _errPkt.numArgs; i++)
		{
			std::memcpy(dataArr, &data[offset], SIZE_O_VAL(ErrorStatusPkt_t, pArgsVal));
			offset += SIZE_O_VAL(ErrorStatusPkt_t, pArgsVal);
			dataArr += SIZE_O_VAL(ErrorStatusPkt_t, pArgsVal);
		}

		is_errPktAvail = true;

		//offset is one larger than last index so equals the length.
		packedSize = ERROR_PACKET_SIZE(&_errPkt);
		if (offset != packedSize)
		{
			*g_pOutputStream << "_parseErrorStatusPkt ERROR: mismatch rcvd packet content size, please double check ErrorStatusPkt_t input and ErrorStatusPkt_t size calculation." << std::endl;
			is_errPktAvail = false;
		}

		return packedSize;
	}
	
	//*****************************************************************************
	//!
	//! \brief  The default handler used to parse command payload
	//! 
	//! \return            return status
	//!
	//*****************************************************************************
	int PayloadProcessor::cmdPktHandler(void)
	{
		// The default command payload handler is not implemented, it is upon each individual operations to overload the function and make use of the content;
		*g_pOutputStream << "Received command content from the target.\n";
		*g_pOutputStream << "cmdPktHandler warning: the default cmdPktHandler is called but only serves as a placeholder. Please use an overload function instead tailored to the specific operation." << std::endl;
		return 0;
	}

	//*****************************************************************************
	//!
	//! \brief  The default handler used to parse command response payload
	//! 
	//! \param pCmdPkt	   The sent command payload packet
	//! 
	//! \return            return status
	//!
	//*****************************************************************************
	int PayloadProcessor::crPktHandler(CommandPkt_t* pCmdPkt)
	{
		int retVal = 0;
		std::string cmdName;

		if (_crPkt.echoCommand == COMMAND_NOT_RECOGNIZED)
		{
			*g_pOutputStream << "crPktHandler warning: target does not recognize the received command." << std::endl;
			cmdName = STRING_LITERAL(COMMAND_NOT_RECOGNIZED);
			cmdName = " (" + cmdName + ")";
			retVal = -1;
		}
		else if (pCmdPkt != nullptr && _crPkt.echoCommand != pCmdPkt->command)
		{
			*g_pOutputStream << "crPktHandler ERROR: validation error with echo command from target, should be " << std::hex << std::showbase << pCmdPkt->command << " ,but received " << _crPkt.echoCommand << std::endl;
			retVal = -1;
		}

		*g_pOutputStream << "Device configuration:\n";
		*g_pOutputStream << "\tCommand code: " << std::hex << std::showbase << _crPkt.echoCommand << cmdName << "\n";

		*g_pOutputStream << "\tExpects incoming data: " << std::boolalpha << (bool)_crPkt.expectsData << "\n";

		// If not expecting data, hide the Time delay and payload size field
		if (_crPkt.expectsData)
		{
			if (_crPkt.timeDelay_ms)
			{
				*g_pOutputStream << "\tTime delay: " << std::dec << _crPkt.timeDelay_ms << "ms\n";
			}

			*g_pOutputStream << "\tMax payload size: " << std::dec << _crPkt.maxPayloadSize << "bytes\n";
		}

		*g_pOutputStream << "\tExpects end-of-transmission packet: " << std::boolalpha << (bool)_crPkt.expectsEOTpacket << std::endl;

		return retVal;
	}

	//*****************************************************************************
	//!
	//! \brief  The default handler used to parse flash status payload
	//! 
	//! \return            return status
	//!
	//*****************************************************************************
	int PayloadProcessor::fsPktHandler(void)
	{
		if (_fsPkt.flashAPIError != FLASH_NO_ERROR)
		{
			// Use utility func to print flash status since implmentation is too large
			printFlashStatus(*g_pOutputStream, _fsPkt);
		}
		else
		{
			*g_pOutputStream << "\tFlash status in good standing.\n";
		}
		return 0;
	}

	//*****************************************************************************
	//!
	//! \brief  The default handler used to parse message payload
	//! 
	//! \return            return status
	//!
	//*****************************************************************************
	int PayloadProcessor::msgPktHandler(void)
	{
		*g_pOutputStream << ("Received message:\n");
		(*g_pOutputStream).write((char*)_msgPkt.msgAddr, _msgPkt.length) << std::endl;

		return 0;
	}

	//*****************************************************************************
	//!
	//! \brief  The default handler used to parse error payload
	//! 
	//! \return            return status
	//!
	//*****************************************************************************
	int PayloadProcessor::errPktHandler(void)
	{
		auto match = ErrorStatusPkt_errorMsgCode.find(_errPkt.errorMsgCode);
		std::string deviceStatus;

		*g_pOutputStream << "Device error status:\n";

		switch ((recoveryStatus)_errPkt.recoveryStatus)
		{
		case RS_IgnoreStatus:
			deviceStatus = "";
			break;
		case RS_Unrecoverable:
			deviceStatus = "\tDevice Status: Unrecoverable\n";
			break;
		case RS_NormalOperation:
			deviceStatus = "\tDevice Status: Good standing\n";
			break;
		default:
			deviceStatus = "\tDevice Status: Unknown (Value = " + std::to_string(_errPkt.recoveryStatus) + ")\n";
			break;
		}
		*g_pOutputStream << deviceStatus;

		*g_pOutputStream << std::hex << std::showbase << "\tMessage Code : " << _errPkt.errorMsgCode << "\n";

		if (match != ErrorStatusPkt_errorMsgCode.end())
		{
			std::string errorMsg = match->second;
			*g_pOutputStream << "\tError Message: " << errorMsg << std::endl;
			int idx = 0;
			for (int argc = _errPkt.numArgs; argc; argc--)
			{
				*g_pOutputStream << _errPkt.pArgsVal[idx] << std::endl;
				idx++;
			}
		}
		else
		{
			*g_pOutputStream << "The received errorMsgCode does not match any known error code, please make sure the programmer has the up-to-date packet protocol (packet_comm_protocol.h, current version: " << EVAL_STRING_LITERAL(COMM_PACKET_PROTOCOL_VERSION) << ")\n";
		}
		return 0;
	}

}

/** @} */