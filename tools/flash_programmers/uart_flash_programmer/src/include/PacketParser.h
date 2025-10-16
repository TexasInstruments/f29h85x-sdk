//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{ 
//! 
//! \file   PacketParser.h
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

#ifndef PACKETPARSER_H
#define PACKETPARSER_H

#include "Common.h"
#include "FlashStatus.h"

namespace FlashProgrammer
{
	const CommandPkt_t defaultCmdPkt = {.payloadType = PayloadType::Command, .command = COMMAND_NOT_RECOGNIZED, .addlContentLength = 0U, .addlContentAddr = nullptr };
	const CommandResponsePkt_t defaultCrPkt = { .payloadType = PayloadType::CommandResponse, .echoCommand = COMMAND_NOT_RECOGNIZED, .expectsData = true, .timeDelay_ms = 0U, .maxPayloadSize = DEFAULT_PAYLOAD_SIZE, .expectsEOTpacket = false, .reserved = 0U };
	const FlashStatusPkt_t defaultFsPkt = { .payloadType = PayloadType::FlashStatus, .status = 0, .address = 0x0, .flashAPIError = FLASH_NO_ERROR, .flashAPIFsmStatus = 0x3 };
	const MessagePkt_t defaultMsgPkt = { .payloadType = PayloadType::Message, .length = 0, .msgAddr = nullptr };
	const ErrorStatusPkt_t defaultErrPkt = { .payloadType = PayloadType::ErrorStatus, .errorMsgCode = 0x0000, .recoveryStatus = recoveryStatus::RS_IgnoreStatus, .hasSprintfArgs = false, .numArgs = 0U, .pArgsVal = nullptr };

	class PayloadProcessor
	{
	public:
		bool is_cmdPktAvail;
		bool is_crPktAvail;
		bool is_fsPktAvail;
		bool is_msgPktAvail;
		bool is_errPktAvail;
		CommandPkt_t _cmdPkt;
		CommandResponsePkt_t _crPkt;
		FlashStatusPkt_t _fsPkt;
		MessagePkt_t _msgPkt;
		ErrorStatusPkt_t _errPkt;
		//std::queue<ErrorStatusPkt_t> _errPktQueue;

		PayloadProcessor() : is_cmdPktAvail(false), is_crPktAvail(false), is_fsPktAvail(false), is_msgPktAvail(false),
		_cmdPkt(defaultCmdPkt), _crPkt(defaultCrPkt), _fsPkt(defaultFsPkt), _msgPkt(defaultMsgPkt), _errPkt(defaultErrPkt)
		//_errPktQueue(), _errPktBufQueue()
		{
			_cmdPktBuf.reserve(DEFAULT_PAYLOAD_SIZE);
			_msgPktBuf.reserve(DEFAULT_PAYLOAD_SIZE);
		}

		void reset()
		{
			is_cmdPktAvail = false;
			is_crPktAvail = false;
			is_fsPktAvail = false;
			is_msgPktAvail = false;
			is_errPktAvail = false;
			//_errPktQueue = {};
			//_errPktBufQueue = {};
		}

		virtual int run(std::vector<uint8_t>& payload, const std::size_t size, CommandPkt_t* pCmdPkt = nullptr);
		int parsePayload(std::vector<uint8_t>& payload, const std::size_t size);

	protected:
		std::vector<uint8_t> _cmdPktBuf;
		std::vector<uint8_t> _msgPktBuf;
		std::vector <uint8_t> _errPktBuf;
		//std::queue<std::vector<uint8_t>> _errPktBufQueue;

		uint16_t parseCommandPkt(uint8_t* data);
		uint16_t parseCommandResponsePkt(uint8_t* data);
		uint16_t parseFlashStatusPkt(uint8_t* data);
		uint16_t parseMessagePkt(uint8_t* data);
		uint16_t parseErrorStatusPkt(uint8_t* data);
		virtual int cmdPktHandler(void);
		virtual int crPktHandler(CommandPkt_t* pCmdPkt);
		virtual int fsPktHandler(void);
		virtual int msgPktHandler(void);
		virtual int errPktHandler(void);
	};

	class PacketExecutor
	{
	public:
		PayloadProcessor* _pktContent;

		PacketExecutor() : _pktContent(nullptr), _buffer(DEFAULT_PAYLOAD_SIZE) { ; }

		void reset(PayloadProcessor& plHandler)
		{
			_pktContent = &plHandler;
		}

		std::size_t constructCommandPacket(CommandPkt_t& cPkt);

	protected:
		std::vector<uint8_t> _buffer;
	};

}

#endif /* PACKETPARSER_H */
/** @} */
