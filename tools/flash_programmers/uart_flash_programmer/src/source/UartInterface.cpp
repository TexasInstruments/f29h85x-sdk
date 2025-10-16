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
#include <unordered_set>

namespace FlashProgrammer
{
	thread_local std::size_t prevTime;
	thread_local std::size_t currTime;
	thread_local std::size_t timeElapsed;

	auto getTickCount_ms = []() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); };
	auto benchmarkTime_ms = []() { currTime = getTickCount_ms(); timeElapsed = currTime - prevTime; prevTime = currTime; };

	//*****************************************************************************
	//!
	//! \brief   Clears the input/output buffer of the UART serial port. 
	//!
	//! \param clearInput		True to clear input/read buffer
	//! \param clearOutput		True to clear output/write buffer
	//! 
	//! \return					1 upon success, 0/-1 if error occurs (Windows)
	//!							0 upon success, -1 if error occurs (POSIX-compliant system)
	//!
	//*****************************************************************************
	int UartInterface::clearPort(bool clearInput, bool clearOutput)
	{
		if (!clearInput && !clearOutput) { return -1; }

#if defined(_WIN32)
#include <windows.h>
		HANDLE ioHandle = _uartPort.native_handle();
		size_t clearFlags = 0;
		clearFlags |= (clearInput) ? PURGE_RXCLEAR : 0;
		clearFlags |= (clearOutput) ? PURGE_TXCLEAR : 0;
		return PurgeComm(ioHandle, clearFlags);
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__) // POSIX-compliant
#include <termios.h>
		int ioHandle = _uartPort.native_handle();
		size_t clearFlags;
		clearFlags = (clearInput && clearOutput) ? TCIOFLUSH : (clearInput) ? TCIFLUSH : TCOFLUSH;
		return tcflush(ioHandle, clearFlags);
#else
		#warning "No viable implementation available to clear UART port, please implement one or comment this line out in UartInterface.cpp"
		return -1;
#endif
	}

	int UartInterface::clearPort(void)
	{
		return this->clearPort(true, true);
	}

	//*****************************************************************************
	//!
	//! \brief	Checks to see if any (unread) data is available
	//! 
	//! \return	true is data is available, otherwise false
	//!								
	//*****************************************************************************
	bool UartInterface::isDataAvailable(void)
	{
#if defined(_WIN32)
#include <windows.h>
		HANDLE ioHandle = _uartPort.native_handle();
		COMSTAT flgSts;
		DWORD err;
		flgSts.cbInQue = 0;
		if (ClearCommError(ioHandle, &err, &flgSts) && flgSts.cbInQue)
		{
			return true;
		}
		return false;
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__) // POSIX-compliant
#include <sys/ioctl.h>
		int ioHandle = _uartPort.native_handle();
		int bytesAvail = 0;
		if (ioctl(ioHandle, FIONREAD, &bytesAvail) == 0 && bytesAvail)
		{
			return true;
		}
		return false;
#else
		// Assumes datas are available
		#warning "No viable implementation available to check UART available data, please implement one or comment this line out in UartInterface.cpp"
		return true;
#endif
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
	int UartInterface::sendData(const void* dataPtr, const std::size_t size, bool enableReadValidation = true, bool enableBitRateMeasurement = true)
	{
		if (size <= 0) { return -1; }

		std::size_t timeBefore, timeAfter;
		asio::thread_pool taskPool(2);

		this->clearPort(enableReadValidation, true);

		*g_pOutputStream << std::dec << "Initiate sending " << size << " bytes of data...\n";

		if (enableBitRateMeasurement)
		{
			timeBefore = getTickCount_ms();
		}

		resetWriteAttributes();
		_readValidationEnabled = enableReadValidation;
		_curWritePtr = dataPtr;
		_remainingBytesToWrite = size;
		asio::post(taskPool, [this]() { writeTaskScheduler(); });

		if (_readValidationEnabled)
		{
			resetReadAttributes();
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
	int UartInterface::sendDataFrame(const void* dataPtr, const std::size_t size, bool enableBitRateMeasurement = true)
	{
		if (size <= 0) { return -1; }

		std::size_t timeBefore, timeAfter;

		this->clearPort(true, true);

		*g_pOutputStream << std::dec << "Initiate sending " << size << " bytes of data...\n";
		*g_pOutputStream << "Waiting to receive target signal to start data transfer...\n";

		if (enableBitRateMeasurement)
		{
			timeBefore = getTickCount_ms();
		}

		resetWriteAttributes();
		_readValidationEnabled = true;
		_curWritePtr = dataPtr;
		_remainingBytesToWrite = size;
		resetReadAttributes();
		_curReadPtr = dataPtr;
		_remainingBytesToRead = size;

		bool isBeginning = true;
		std::size_t allowableSize, requestDataSize = 0;

		while (_remainingBytesToRead > 0)
		{
			uint8_t packetStatus;
			uint16_t rcvdChecksum, checksum = 0;
			allowableSize = std::min(_maxBytesToWrite, _remainingBytesToWrite);
			allowableSize = std::min(allowableSize, requestDataSize);

			if (!isBeginning)
			{
				sendWord((uint16_t)allowableSize);
				sendBytes(_curWritePtr, allowableSize);
				*g_pOutputStream << "send " << allowableSize << " bytes\n";

				_curWritePtr = (const uint8_t*)_curWritePtr + allowableSize;
				_remainingBytesToWrite -= allowableSize;
				//*g_pOutputStream << std::dec << _remainingBytesToRead << " bytes remain\n";

#if ENABLE_CHECKSUM_VALIDATION
				// Don't perform checksum checking in the first ACK
				for (std::size_t i = 0; i < allowableSize; i++)
				{
					checksum += static_cast<const uint8_t*>(_curReadPtr)[i] & 0xff;
				}
#endif
			}

			// Activate communication via target ACK/NAK
			packetStatus = readByte();
			if (packetStatus == PACKET_ACK)
			{
				requestDataSize = readWord();
				rcvdChecksum = readWord();
#if ENABLE_CHECKSUM_VALIDATION
				// Don't perform checksum checking in the first ACK
				if (!isBeginning)
				{
					if (rcvdChecksum != checksum)
					{
						*g_pOutputStream << std::hex << std::showbase << "Checksum validation ERROR, recvd " << rcvdChecksum << ", but expecting " << checksum << "\n";
					}
					_curReadPtr = (const uint8_t*)_curReadPtr + allowableSize;
					_remainingBytesToRead -= allowableSize;
				}
#endif 
			}
			else if (packetStatus == PACKET_NAK)
			{
				*g_pOutputStream << "\nNAK status packet detected during data transmission..." << std::endl;
				return -1;
			}
			else if (packetStatus == PACKET_HEADER)
			{
				*g_pOutputStream << "\nFull status packet detected during data transmission, treating it as a NAK status packet." << std::endl;
				return -1;
			}
			else
			{
				*g_pOutputStream << "\nERROR, unrecognized receive value, received " << std::hex << std::showbase << packetStatus << " but expecting " << EVAL_STRING_LITERAL(PACKET_ACK) << " (" << STRING_LITERAL(PACKET_ACK) << ")" << std::endl;
				return -1;
			}

			isBeginning = false;
		}

		if (enableBitRateMeasurement)
		{
			timeAfter = getTickCount_ms();
			double bandwidth_bps = (double)size * 8 / (double)(timeAfter - timeBefore) * 1000;
			*g_pOutputStream << std::fixed << std::setprecision(3) << "Data bandwidth is " << bandwidth_bps << " bits per second (bps)" << std::endl;
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
	std::size_t UartInterface::sendByte(const uint8_t data)
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
	std::size_t UartInterface::sendBytes(const void* dataPtr, const std::size_t size)
	{
		if (size <= 0) { return 0; }

		std::size_t bytesTransferred = 0;

		while (bytesTransferred < size)
		{
			bytesTransferred = asio::write(_uartPort, asio::buffer(dataPtr, size));
		}

		return bytesTransferred;
	}

	//*****************************************************************************
	//!
	//! \brief		    Sends one word via UART
	//!
	//! \param data		Data in one word
	//! 
	//! \return			number of transferred bytes
	//!								
	//*****************************************************************************
	std::size_t UartInterface::sendWord(const uint16_t word)
	{
		std::size_t bytesTransferred = 0;

		bytesTransferred += this->sendByte(word & (uint8_t)0xFF);
		bytesTransferred += this->sendByte(((word >> 8) & (uint8_t)0xFF));

		return bytesTransferred;
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
	uint8_t UartInterface::readByte(uint16_t* checksum)
	{
		uint8_t result;
		result = this->readByte();
		*checksum += result;

		return result;
	}

	uint8_t UartInterface::readByte(void)
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
	std::size_t UartInterface::readBytes(void* dataPtr, const std::size_t size)
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
	uint16_t UartInterface::readWord(uint16_t* checksum)
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

	uint16_t UartInterface::readWord(void)
	{
		uint16_t discard;
		return this->readWord(&discard);
	}

	//*****************************************************************************
	//!
	//!  \brief	 Reset internal read attributes
	//!								
	//*****************************************************************************
	void UartInterface::resetReadAttributes(void)
	{
		_remainingBytesToRead = 0;
		_unvalidatedBytes = 0;
		_curReadPtr = nullptr;

		if (_readBuffer.size() < _maxPacketBytes)
		{
			// ASIO.buffer uses size info rather than capcity info of the buffer,
			// therefore one must use resize rather than reserve
			_readBuffer.resize(_maxPacketBytes);
		}
	}

	//*****************************************************************************
	//!
	//!  \brief	 Reset internal write attributes
	//!								
	//*****************************************************************************
	void UartInterface::resetWriteAttributes(void)
	{
		_remainingBytesToRead = 0;
		_unvalidatedBytes = 0;
		_maxBytesToWrite = _maxPacketBytes;
		_curWritePtr = nullptr;
		_readValidationEnabled = false;
	}

	//*****************************************************************************
	//!
	//!  \brief	 Hook to invoke asynchronous read tasks via UART/Serial port.
	//!								
	//*****************************************************************************
	void UartInterface::readTaskScheduler(void)
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
	void UartInterface::readValidationCallback(const asio::error_code& error, std::size_t bytesTransferred)
	{
		std::size_t allowableSize;
		const uint8_t* curPtr = static_cast<const uint8_t*>(_curReadPtr);

		if (error)
		{
			*g_pOutputStream << "Read uart ERROR: " << error.message() << "\n";
		}

		if (bytesTransferred > 0)
		{
			benchmarkTime_ms();

			for (std::size_t i = 0; i < bytesTransferred; i++)
			{

				if (_readBuffer[i] != curPtr[i])
				{
					*g_pOutputStream << std::hex << std::showbase << "Data transmission ERROR, recvd " << static_cast<std::size_t>(_readBuffer[i]) << ", but expecting " << static_cast<std::size_t>(curPtr[i]) << std::endl;
					*g_pOutputStream << "Error detected, exiting the program now..." << std::endl;
					exitApp(-1);
				}
				//else // If needing to see what's being received
				//{
				//	*g_pOutputStream << std::hex << std::showbase << "Received " << static_cast<std::size_t>(_readBuffer[i]) << "\n";
				//}
			}
			_unvalidatedBytes -= bytesTransferred;
			_remainingBytesToRead -= bytesTransferred;
			curPtr += bytesTransferred;
			_curReadPtr = curPtr;

			// Debug print statements
			//std::string readStatus = "Recvd " + std::to_string(bytesTransferred) + " bytes, port elasped for " + std::to_string(timeElapsed) + " ms, " +
			//	std::to_string(_unvalidatedBytes) + " left to validate, " + std::to_string(_remainingBytesToRead) + " bytes remain\n";
			//*g_pOutputStream << readStatus;
		}


		if (_remainingBytesToRead > 0)
		{
			allowableSize = std::min(_unvalidatedBytes, _remainingBytesToRead);
			_uartPort.async_read_some(asio::buffer(_readBuffer, allowableSize),
				std::bind(&UartInterface::readValidationCallback, this,
					asio::placeholders::error,
					asio::placeholders::bytes_transferred));
		}
	}

	//*****************************************************************************
	//!
	//!  \brief Recursive write task calls 
	//! 
	//!	 \note  if needed, attribute "_maxBytesToWrite" can be adjusted to implement congestion control
	//!								
	//*****************************************************************************
	void UartInterface::writeTaskScheduler(void)
	{
		std::size_t allowableSize;
		std::size_t bytesTransferred;
		std::size_t timeoutCntr = 0;
		const uint8_t* curPtr = static_cast<const uint8_t*>(_curWritePtr);

		while (_remainingBytesToWrite > 0)
		{
			// If transmission rate is capped
			if (_maxBytesToWrite <= _unvalidatedBytes)
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

			*g_pOutputStream << "send " + std::to_string(bytesTransferred) + " bytes\n";

			// Debug print statements
			//std::string writeStatus = "Wrote " + std::to_string(bytesTransferred) + " bytes, port elasped for " + std::to_string(timeElapsed) + " ms, " +
			//	std::to_string(_unvalidatedBytes) + " left to validate, " + std::to_string(_remainingBytesToWrite) + " bytes remain\n";
			//*g_pOutputStream << writeStatus;
		}
	}

}

/** @} */