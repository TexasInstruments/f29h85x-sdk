//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   UartDownload.cpp
//! 
//! \brief  High-level UART workflow (download host image to target)
//!
//! \note   For all downloads, the flash programmer sends the application the same
//!		    way it does the kernel.  In both instances, the flash programmer
//!		    send one byte and the device echos back that same byte.
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

#include "../include/UartDownload.h"

//
// Internal Functions
//
int _UartBoot(FlashProgrammer::UartInterface& uartHandle, FILE* fptr);
int _PktDataMode(FlashProgrammer::UartInterface& uartHandle, FILE* fptr);

//*****************************************************************************
//!
//! \brief   Loads the program to device by sending the file to BootROM/flash kernel
//!			 via the boot ROM method (byte-by-byte send with byte-by-byte acknowledgement)
//!		     Note: This is the default behavior from BootROM for uart boot
//!
//! \param uartHandle   Handle to an instance of UART interface
//! \param fptr		    File handler pointer
//! 
//! \return             0 upon success, -1 if error occurs
//! 
//*****************************************************************************
int _UartBoot(FlashProgrammer::UartInterface& uartHandle, FILE* fptr)
{
	std::size_t dataSize = 0;

	fseek(fptr, 0, SEEK_END);
	dataSize = ftell(fptr);
	rewind(fptr);
	
	auto rawData = std::make_unique<char[]>(dataSize);
	char* rawPtr = rawData.get();

	fread(rawPtr, sizeof(*rawPtr), dataSize, fptr);

	return uartHandle.sendData(rawPtr, dataSize, true, true);

}

//*****************************************************************************
//!
//! \brief   Loads the program to device by sending the file to BootROM/flash kernel
//!  		 via the buffered method (frame-by-frame send with frame acknowledgement)
//!		     Note: This flow has error-detection and error-handling support and therefore
//!		           recommended for all kernel applications
//!
//! \param uartHandle   Handle to an instance of UART interface
//! \param fptr		    File handler pointer
//! 
//! \return             0 upon success, -1 if error occurs
//!
//*****************************************************************************
int _PktDataMode(FlashProgrammer::UartInterface& uartHandle, FILE* fptr)
{
	std::size_t dataSize = 0;

	fseek(fptr, 0, SEEK_END);
	dataSize = ftell(fptr);
	rewind(fptr);

	auto rawData = std::make_unique<char[]>(dataSize);
	char* rawPtr = rawData.get();

	fread(rawPtr, sizeof(*rawPtr), dataSize, fptr);

	return uartHandle.sendDataFrame(rawPtr, dataSize, true);

}

//*****************************************************************************
//!
//! \brief   Download a (SBL) kernel to the device via BootROM. 
//!
//! \param uartHandle   Handle to an instance of UART interface
//! \param kernelFile   The name of the kernel file 
//! 
//! \return             0 upon success, -1 if error occurs 
//!
//*****************************************************************************
int downloadBootloader(FlashProgrammer::UartInterface& uartHandle, const char* kernelFile)
{
	FILE* Kfh;
	int retVal;

	uartHandle.clearPort();

	*g_pOutputStream << "\nDownloading " << kernelFile << " to device..." << std::endl;

	// Opens the Flash Kernel File
	Kfh = fopen(kernelFile, "rb");
	if (!Kfh)
	{
		*g_pOutputStream << "Unable to open kernel file " << kernelFile << ", Does it exist?" << std::endl;
		return(-1);
	}

	retVal = _UartBoot(uartHandle, Kfh);

	if (retVal == 0)
	{
		*g_pOutputStream << "SBL kernel successfully sent!" << std::endl;
	}
	
	fclose(Kfh);

	return(retVal);
}

//*****************************************************************************
//!
//! \brief	 Download an application image with certificate to the device. 
//!
//! \param uartHandle		Handle to an instance of UART interface
//! \param applicationFile  The name of the application image 
//! \param maxPacketSize	Optional packet size input to limit to maximum size of allowable bytes
//! 
//! \return					0 upon success, -1 if error occurs 
//!
//*****************************************************************************
int downloadApplication(FlashProgrammer::UartInterface& uartHandle, const char* applicationFile, const size_t maxPacketSize)
{
	FILE *Afh;
	size_t prevPacketSize = uartHandle._maxPacketBytes;
	int retVal;

	uartHandle.clearPort(false, true);

	*g_pOutputStream << "\nDownloading " << applicationFile << " to device..." << std::endl;

    //Opens the application file 
	Afh = fopen(applicationFile, "rb");
	if (!Afh)
	{
		*g_pOutputStream << "Unable to open application file " << applicationFile << ", Does it exist?" << std::endl;
		return(-1);
	}

	// Set packet size (for buffered flow packet is the payload itself during data transfer)
	if (maxPacketSize != 0)
	{
		uartHandle._maxPacketBytes = maxPacketSize;
	}

	retVal = _PktDataMode(uartHandle, Afh);
	
	// Restore previously recorded size
	uartHandle._maxPacketBytes = prevPacketSize;

	if (retVal == 0)
	{
		*g_pOutputStream << "Application successfully sent!\n" << std::endl;
	}

	fclose(Afh);

	return(retVal);
}

/** @} */