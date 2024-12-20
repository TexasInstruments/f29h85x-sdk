//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   UartInterface.cpp
//! 
//! \brief  Low-level abstraction interface to UART serial port read and write
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

#include "../include/UartInterface.h"

#include <asio/thread_pool.hpp>
#include <asio/write.hpp>
#include <asio/read.hpp>
#include <asio/post.hpp>

thread_local std::size_t prevTime;
thread_local std::size_t currTime;
thread_local std::size_t timeElapsed;

auto getTickCount_ms = []() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); };
auto benchmarkTime_ms = []() { currTime = getTickCount_ms(); timeElapsed = currTime - prevTime; prevTime = currTime; };

namespace FlashProgrammer
{	

	//*****************************************************************************
	//!
	//! \brief   Clears the input/output buffer of the UART serial port. 
	//!
	//! \param clearInput		True to clear input buffer
	//! \param clearOutput		True to clear output buffer
	//! 
	//! \return					1 upon success, 0/-1 if error occurs (Windows)
	//!							0 upon success, -1 if error occurs (POSIX-compliant system)
	//!
	//*****************************************************************************
	int UartHandler::clearPort(bool clearInput, bool clearOutput)
	{
		if (!clearInput && !clearOutput) { return -1; }

		#if defined(_WIN32)
			#include <windows.h>
			HANDLE ioHandle = _uartPort.native_handle();
			size_t clearFlags = 0;
			clearFlags |= (clearInput) ? PURGE_RXCLEAR : 0;
			clearFlags |= (clearOutput) ? PURGE_TXCLEAR : 0;
			return PurgeComm(ioHandle, clearFlags);
		#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
			#include <termios.h>
			int ioHandle = _uartPort.native_handle();
			size_t clearFlags;
			clearFlags = (clearInput && clearOutput) ? TCIOFLUSH : (clearInput) ? TCIFLUSH : TCOFLUSH;
			return tcflush(ioHandle, clearFlags);
		#else
			#error "No viable implementation available to clear UART port, please implement one or comment this line out in UartInterface.cpp"
			return -1;
		#endif
	}

	int UartHandler::clearPort(void)
	{
		return this->clearPort(true, true);
	}

	//*****************************************************************************
	//!
	//! \brief  Sends data via UART by opening up concurrent Read/Write threads (if applicable)
	//!			Recommended to use this func for large data transmission
	//!
	//! \param dataPtr					Pointer to the input data
	//! \param size						Size of the data, in bytes
	//! \param enableReadValidation		Enables read port for validating echoed back data
	//! \param enableBitRateMeasurement	Enables bandwidth measurement
	//! 
	//! \return						    0 upon success, -1 if error occurs 
	//!								
	//*****************************************************************************
	int UartHandler::sendData(const void* dataPtr, const std::size_t size, bool enableReadValidation = true, bool enableBitRateMeasurement = false)
	{
		std::size_t timeBefore, timeAfter;

		if (size <= 0) { return -1; }

		this->clearPort();
		asio::thread_pool taskPool(2);

		*g_pOutputStream << "Initiate sending " << size <<" bytes of data...\n";

		if (enableBitRateMeasurement)
		{
			timeBefore = getTickCount_ms();
		}

		_maxBytesToWrite = _maxPacketBytes;
		_readValidationEnabled = enableReadValidation;

		_curWritePtr = dataPtr;
		_remainingBytesToWrite = size;
		_unvalidatedBytes = 0;
		asio::post(taskPool, [this]() { writeTaskScheduler(); });

		if (_readValidationEnabled)
		{
			_curReadPtr = dataPtr;
			_remainingBytesToRead = size;
			asio::post(taskPool, [this]() { readTaskScheduler(); });
		}

		taskPool.join();

		if (enableBitRateMeasurement)
		{
			timeAfter = getTickCount_ms();
			double bandwidth_bps = (double)size * 8 / (double)(timeAfter - timeBefore) * 1000;
			*g_pOutputStream << std::fixed << std::setprecision(3) << "\nData bandwidth is " << bandwidth_bps << " bits per second (bps)\n";
		}

		return 0;
	}

	//*****************************************************************************
	//!
	//! \brief		    Sends one byte via UART
	//!
	//! \param data		Data in one byte
	//! 
	//! \return			number of transferred bytes
	//!								
	//*****************************************************************************
	std::size_t UartHandler::sendByte(const uint8_t data)
	{
		const uint8_t byteBuf = data;
		std::size_t bytesTransferred = 0;

		while (!bytesTransferred)
		{
			bytesTransferred = asio::write(_uartPort, asio::buffer(&byteBuf, 1));
		}

		return bytesTransferred;
	}

	//*****************************************************************************
	//!
	//! \brief		    Sends multiple bytes via UART
	//!
	//! \param dataPtr	Pointer to the output data
	//! \param size		Size of the data, in bytes
	//! 
	//! \return			number of transferred bytes
	//!								
	//*****************************************************************************
	std::size_t UartHandler::sendBytes(const void* dataPtr, const std::size_t size)
	{
		if (size <= 0) { return 0; }

		this->clearPort(false, true);

		_maxBytesToWrite = _maxPacketBytes;
		_curWritePtr = static_cast<const uint8_t*>(dataPtr);
		_remainingBytesToWrite = size;

		writeTaskScheduler();

		return size;
	}

	//*****************************************************************************
	//!
	//! \brief	Read one byte via UART
	//!
	//! \param  checksum (Optional) Pointer to the accumlating checksum
	//! 
	//! \return	The read byte
	//!								
	//*****************************************************************************
	uint8_t UartHandler::readByte(uint16_t* checksum)
	{
		uint8_t result;
		result = this->readByte();
		*checksum += result;

		return result;
	}

	uint8_t UartHandler::readByte(void)
	{
		std::size_t bytesTransferred = 0;
		uint8_t byte;

		while (!bytesTransferred)
		{
			bytesTransferred = asio::read(_uartPort, asio::buffer(&byte, 1));
		}
		return byte;
	}

	//*****************************************************************************
	//!
	//! \brief		    Read multiple bytes via UART
	//!
	//! \param dataPtr	Pointer to the input data buffer
	//! \param size		Size of data to read, in bytes
	//! 
	//! \return			number of read bytes
	//!								
	//*****************************************************************************
	std::size_t UartHandler::readBytes(void* dataPtr, const std::size_t size)
	{
		std::size_t bytesTransferred = 0;
		uint8_t* curPtr = static_cast<uint8_t*>(dataPtr);

		while (bytesTransferred < size)
		{
			bytesTransferred += asio::read(_uartPort, asio::buffer(curPtr, size - bytesTransferred));
			curPtr += bytesTransferred;
		}

		return bytesTransferred;
	}

	//*****************************************************************************
	//!
	//! \brief	Read word (16bit) via UART
	//!
	//! \param	checksum (Optional) Pointer to the accumlating checksum
	//! 
	//! \return	The read word
	//!								
	//*****************************************************************************
	uint16_t UartHandler::readWord(uint16_t* checksum)
	{
		uint16_t wordData;
		uint16_t byteData;

		wordData = 0x0000;
		byteData = 0x0000;

		wordData = this->readByte() & 0xff;
		byteData = this->readByte() & 0xff;

		*checksum += wordData + byteData;
		wordData |= (byteData << 8);

		return wordData;
	}

	uint16_t UartHandler::readWord(void)
	{
		uint16_t discard;
		return this->readWord(&discard);
	}

	//*****************************************************************************
	//!
	//!  \brief	 Hook to invoke asynchronous read tasks via UART/Serial port.
	//!								
	//*****************************************************************************
	void UartHandler::readTaskScheduler(void)
	{
		asio::error_code err;

		prevTime = getTickCount_ms();
		readValidationCallback(err, 0);

		if (_io.stopped()) _io.reset();
		_io.run();
	}

	//*****************************************************************************
	//!
	//! \brief Read task recursive calls to invoke async read
	//!
	//! \param error				ASIO error status code
	//! \param bytesTransferred		Bytes read in the previous call
	//!								
	//*****************************************************************************
	void UartHandler::readValidationCallback(const asio::error_code& error, std::size_t bytesTransferred)
	{
		std::size_t allowableSize;
		const uint8_t* curPtr = static_cast<const uint8_t*>(_curReadPtr);

		if (error)
		{
			*g_pOutputStream << "Read uart ERROR: " << error.message() << std::endl;
		}

		if (bytesTransferred > 0)
		{
			benchmarkTime_ms();

			for (std::size_t i = 0; i < bytesTransferred; i++)
			{

				if (_readBuffer[i] != curPtr[i])
				{
					*g_pOutputStream << std::hex << std::showbase << "Data transmission ERROR, recvd " << static_cast<std::size_t>(_readBuffer[i]) << ", but expecting " << static_cast<std::size_t>(curPtr[i]) << "\n";
					//exitApp(-1);
				}
			}
			_unvalidatedBytes -= bytesTransferred;
			_remainingBytesToRead -= bytesTransferred;
			curPtr += bytesTransferred;
			_curReadPtr = curPtr;

			std::string readStatus = "Recvd " + std::to_string(bytesTransferred) + " bytes, port elasped for " + std::to_string(timeElapsed) + " ms, " +
									 std::to_string(_unvalidatedBytes) + " left to validate, " + std::to_string(_remainingBytesToRead) + " bytes remain\n";
			*g_pOutputStream << readStatus;
		}


		if (_remainingBytesToRead > 0)
		{
			allowableSize = std::min(_unvalidatedBytes, _remainingBytesToRead);
			_uartPort.async_read_some(asio::buffer(_readBuffer, allowableSize),
				std::bind(&UartHandler::readValidationCallback, this,
					asio::placeholders::error,
					asio::placeholders::bytes_transferred));
			//asio::transfer_exactly(allowableSize), [this](const asio::error_code& error, std::size_t bytes_transferred) {this->readPortListener(error, bytes_transferred); });
			//asio::post(_taskPool, [this]() {_io.run();} );
		}
	}

	//*****************************************************************************
	//!
	//!  \brief Recursive write task calls 
	//! 
	//!	 \note  if needed, attribute "_maxBytesToWrite" can be adjusted to implement congestion control
	//!								
	//*****************************************************************************
	void UartHandler::writeTaskScheduler(void)
	{
		std::size_t allowableSize;
		std::size_t bytesTransferred;
		std::size_t timeoutCntr = 0;
		const uint8_t* curPtr = static_cast<const uint8_t*>(_curWritePtr);

		while (_remainingBytesToWrite > 0)
		{
			if (_maxBytesToWrite <= _unvalidatedBytes) // If transmission rate is capped
			{
				allowableSize = 0;
			}
			else
			{
				allowableSize = std::min(_maxBytesToWrite - _unvalidatedBytes, _remainingBytesToWrite);
			}

			if (allowableSize == 0)
			{
				timeoutCntr++;
				std::this_thread::sleep_for(std::chrono::microseconds(2));
				continue;
			}
			prevTime = getTickCount_ms();

			bytesTransferred = asio::write(_uartPort, asio::buffer(curPtr, allowableSize));
			benchmarkTime_ms();

			if (_readValidationEnabled)
			{
				_unvalidatedBytes += bytesTransferred;
			}
			_remainingBytesToWrite -= bytesTransferred;
			curPtr += bytesTransferred;
			_curWritePtr = curPtr;

			std::string writeStatus = "Wrote " + std::to_string(bytesTransferred) + " bytes, port elasped for " + std::to_string(timeElapsed) + " ms, " +
				std::to_string(_unvalidatedBytes) + " left to validate, " + std::to_string(_remainingBytesToWrite) + " bytes remain\n";
			*g_pOutputStream << writeStatus;
		}
	}

}
/** @} */