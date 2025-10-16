//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   UartInterface.h
//! 
//! \brief  Includes low-level abstraction interface function to UART serial port 
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

#ifndef UARTINTERFACE_H
#define UARTINTERFACE_H

#include <asio.hpp>
#include <asio/serial_port.hpp>

#include "Common.h"

namespace FlashProgrammer
{
	class UartInterface
	{
	public:
		std::string _uartPortStr;
		asio::io_context _io;
		asio::serial_port _uartPort;
		//
		// Maximum bytes uart can send in a packet, could be higher than target uart FIFO size depending on how fast the target is processing the data. 
		//
		std::size_t _maxPacketBytes;

		UartInterface() : _uartPort(_io), _maxPacketBytes(DEFAULT_PAYLOAD_SIZE),
			_curReadPtr(nullptr), _curWritePtr(nullptr), _unvalidatedBytes(0), _remainingBytesToWrite(0), _remainingBytesToRead(0), _readValidationEnabled(false)
		{
			_maxBytesToWrite = _maxPacketBytes;
			// ASIO.buffer uses size info rather than capcity info of the buffer,
			// therefore one must use resize rather than reserve
			_readBuffer.resize(_maxPacketBytes);
		}

		~UartInterface()
		{
			if (_uartPort.is_open())
			{
				_uartPort.close();
			}
		}

		void configComPort(const std::string& portName, const size_t baudRate = 115200)
		{
			try
			{
				_uartPortStr = portName;
				_uartPort.open(portName);
			}
			catch (const std::exception& e)
			{
				std::string updatedMessage = "ERROR: please double check COM/tty port, does it exist? \nSystem message: " + std::string(e.what());
				throw std::runtime_error(updatedMessage);
			}

			try
			{
				_uartPort.set_option(asio::serial_port::baud_rate(baudRate));
				_uartPort.set_option(asio::serial_port::character_size(8));
				_uartPort.set_option(asio::serial_port::stop_bits(asio::serial_port::stop_bits::one));
				_uartPort.set_option(asio::serial_port::flow_control(asio::serial_port::flow_control::none));
				_uartPort.set_option(asio::serial_port::parity(asio::serial_port::parity::none));
			}
			catch (const std::exception& e)
			{
				std::string updatedMessage = "ERROR: please double check uart configuration settings. \nSystem message: " + std::string(e.what());
				throw std::runtime_error(updatedMessage);
			}
		}

		void configBaudRate(const size_t baudRate)
		{
			try
			{
				_uartPort.set_option(asio::serial_port::baud_rate(baudRate));
			}
			catch (const std::exception& e)
			{
				std::string updatedMessage = "configBaudRate ERROR: configure "+ std::to_string(baudRate) + " baud rate failed. \nSystem message: " + std::string(e.what());
				throw std::runtime_error(updatedMessage);
			}
		}

		uint8_t readByte(void);
		uint8_t readByte(uint16_t* checkSum);
		uint16_t readWord(void);
		uint16_t readWord(uint16_t* checkSum);
		std::size_t readBytes(void* outPtr, const std::size_t size);

		std::size_t sendByte(const uint8_t data);
		std::size_t sendWord(const uint16_t word);
		std::size_t sendBytes(const void* dataPtr, const std::size_t size);
		int sendData(const void* dataPtr, const std::size_t size, bool enableReadValidation, bool enableBitRateMeasurement);
		int sendDataFrame(const void* dataPtr, const std::size_t size, bool enableBitRateMeasurement);

		int clearPort(void);
		int clearPort(bool clearInput, bool clearOutput);

		bool isDataAvailable(void);

	private:
		std::size_t _remainingBytesToWrite;
		std::size_t _remainingBytesToRead;
		std::size_t _unvalidatedBytes;
		std::size_t _maxBytesToWrite;
		const void* _curWritePtr;
		const void* _curReadPtr;
		std::vector<uint8_t> _readBuffer;
		bool _readValidationEnabled;

		void resetReadAttributes();
		void resetWriteAttributes();

		void readTaskScheduler();
		void readValidationCallback(const asio::error_code& error, std::size_t bytesTransferred);
		void writeTaskScheduler();

		/*
		int uartCommunicator::errorCodeHandler(const asio::error_code& error);
		void uartCommunicator::asyncWait();
		void uartCommunicator::asyncWait(std::function<void()> callback);
		*/
	};

}

#endif /* UARTINTERFACE_H */
/** @} */