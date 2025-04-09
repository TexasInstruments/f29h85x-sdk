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

//*****************************************************************************
//!
//! \brief   Loads the program to device by sending the file to BootROM/flash kernel
//!
//! \param uartHandle   Handle to an instance of UART interface
//! \param fptr		    File handler pointer
//!
//*****************************************************************************
void loadProgram(FlashProgrammer::UartHandler& uartHandle, FILE* fptr)
{
	std::size_t dataSize = 0;

	fseek(fptr, 0, SEEK_END);
	dataSize = ftell(fptr);
	rewind(fptr);
	
	auto rawData = std::make_unique<char[]>(dataSize);
	char* rawPtr = rawData.get();

	fread(rawPtr, sizeof(*rawPtr), dataSize, fptr);

	uartHandle.sendData(rawPtr, dataSize, true, true);

}

//*****************************************************************************
//!
//! \brief   Loads the program to device by sending the file to flash kernel with specified breakpoints
//!
//! \param uartHandle   Handle to an instance of UART interface
//! \param fptr		    File handler pointer
//! \param breakpointPtr	The pointer to an array of breakpoints, needs to be uint32_t
//! \param bpSize			The size of the breakpoint array
//!
//*****************************************************************************
void loadProgram(FlashProgrammer::UartHandler& uartHandle, FILE* fptr, const void* breakpointPtr, const std::size_t bpSize)
{
	std::size_t dataSize = 0;

	fseek(fptr, 0, SEEK_END);
	dataSize = ftell(fptr);
	rewind(fptr);

	auto rawData = std::make_unique<char[]>(dataSize);
	char* rawPtr = rawData.get();

	fread(rawPtr, sizeof(*rawPtr), dataSize, fptr);

	uartHandle.sendData(rawPtr, dataSize, breakpointPtr, bpSize, true);

}

//*****************************************************************************
//!
//! \brief   Download a kernel to the device. 
//!
//! \param uartHandle   Handle to an instance of UART interface
//! \param kernelFile   The name of the kernel file 
//! 
//! \return             0 upon success, -1 if error occurs 
//!
//*****************************************************************************
int downloadKernel(FlashProgrammer::UartHandler& uartHandle, const char* kernelFile)
{
	FILE* Kfh;

	*g_pOutputStream << "\nDownloading " << kernelFile << " to device..." << std::endl;

	// Opens the Flash Kernel File
	Kfh = fopen(kernelFile, "rb");
	if (!Kfh)
	{
		*g_pOutputStream << "Unable to open kernel file " << kernelFile << ", Does it exist?" << std::endl;
		return(-1);
	}

	loadProgram(uartHandle, Kfh);

	*g_pOutputStream << "Kernel successfully sent!" << std::endl;

	fclose(Kfh);

	uartHandle.clearPort();

	return(0);
}

//*****************************************************************************
//!
//! \brief	 Download an application image with certificate to the device. 
//!
//! \param uartHandle		Handle to an instance of UART interface
//! \param applicationFile  The name of the application image 
//! 
//! \return					0 upon success, -1 if error occurs 
//!
//*****************************************************************************
int downloadImage(FlashProgrammer::UartHandler& uartHandle, const char* applicationFile)
{
	FILE *Afh;

	*g_pOutputStream << "\nDownloading " << applicationFile << " to device..." << std::endl;

    //Opens the application file 
	Afh = fopen(applicationFile, "rb");
	if (!Afh)
	{
		*g_pOutputStream << "Unable to open application file " << applicationFile << ", Does it exist?" << std::endl;
		return(-1);
	}

	loadProgram(uartHandle, Afh);

	*g_pOutputStream << "Application successfully sent!\n" << std::endl;

	fclose(Afh);

	uartHandle.clearPort(false, true);

	return(0);
}

//*****************************************************************************
//!
//! \brief	 Download an application image with specified breakpoints 
//!
//! \param uartHandle		Handle to an instance of UART interface
//! \param applicationFile  The name of the application image 
//! \param breakpointPtr	The pointer to an array of breakpoints, needs to be uint32_t
//! \param bpSize			The size of the breakpoint array
//! 
//! \return					0 upon success, -1 if error occurs 
//!
//*****************************************************************************
int downloadImage(FlashProgrammer::UartHandler& uartHandle, const char* applicationFile, const void* breakpointPtr, const std::size_t bpSize)
{
	FILE* Afh;

	*g_pOutputStream << "\nDownloading " << applicationFile << " to device..." << std::endl;

	//Opens the application file 
	Afh = fopen(applicationFile, "rb");
	if (!Afh)
	{
		*g_pOutputStream << "Unable to open application file " << applicationFile << ", Does it exist?" << std::endl;
		return(-1);
	}

	loadProgram(uartHandle, Afh, breakpointPtr, bpSize);

	*g_pOutputStream << "Application successfully sent!\n" << std::endl;

	fclose(Afh);

	uartHandle.clearPort(true, true);

	return(0);
}
/** @} */