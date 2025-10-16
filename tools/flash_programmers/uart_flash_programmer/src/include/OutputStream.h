//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{ 
//! 
//! \file   OutputStream.h
//! 
//! \brief  Includes output stream abstract class based on std::ostream
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

#ifndef OUTPUTSTEAM_H
#define OUTPUTSTEAM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <chrono>
#include <iomanip>

//
// Cout Stream with a static custom deleter
//
class CoutStream : public std::ostream
{
public:
	explicit CoutStream(std::ostream& stream) : std::ostream(stream.rdbuf()) {}
	static void deleter(std::ostream*) {}; // Do nothing, required for smart pointer allocation
};

//
// NullStream that directs output buffer into a nullptr
//
class NullStream : public std::ostream
{
public:
	NullStream() : std::ostream(nullptr), _buffer()
	{
		rdbuf(&_buffer);
	}

private:
	class NullBuffer : public std::streambuf
	{
	protected: 
		int overflow(int c) override { return c; }
	} _buffer;
};

//
// FileStream to implement custom operator overload function
// equivalent to std::ofstream Foo("test.log", std::ios::out);
//
class FileStream : public std::ostream
{
public:
	explicit FileStream(const std::string& fileName) : std::ostream(nullptr), _streamBuf(nullptr), _fileStream(fileName, std::ios::out)
	{
		if (!_fileStream.is_open())
		{
			std::string message = "ERROR: failed to open log file: " + fileName;
			throw std::runtime_error(message);
		}
		_streamBuf = _fileStream.rdbuf();
		rdbuf(_streamBuf);
	}

	template <typename T>
	FileStream& operator<<(const T& data)
	{
		std::ostream::operator<< (getTimeStamp().c_str());
		std::ostream::operator<< (data);
		return *this;
	}

	FileStream& operator<<(std::ostream& (*manip)(std::ostream&))
	{

		std::ostream::operator<< (getTimeStamp().c_str());
		manip(*this);

		return *this;
	}

	~FileStream() 
	{
		if (_fileStream.is_open())
		{
			_fileStream.close();
		}
	}

private:
	std::ofstream _fileStream;
	std::streambuf* _streamBuf;

	std::string getTimeStamp()
	{
		std::ostringstream timeStamp;

		auto timeNow = std::chrono::system_clock::now();
		auto timeNow_t = std::chrono::system_clock::to_time_t(timeNow);
		auto timeNow_tm = *std::localtime(&timeNow_t);
		
		timeStamp << "[" << std::put_time(&timeNow_tm, "%H:%M:%S") << "] ";

		return timeStamp.str();
	}
};

#endif /* OUTPUTSTEAM_H */
/** @} */