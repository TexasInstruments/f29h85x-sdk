//###########################################################################
//! 
//! \defgroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//!
//! \file	uart_flash_programmer.cpp
//! 
//! \brief	Host-side Flash Programmer cli for firmware upgrades and other uility options via UART
//!
//! \note	This is a demonstration cli in tandem with the Texas Instruments UART Flash Kernel.
//!			It takes parameter input to send binary applications, images, and 
//!			other operations to the mcu via UART (COM/tty port). 
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

#include "include/CommandLine.h"
#include "include/OutputStream.h"
#include "include/UartDownload.h"
#include "include/UartPacket.h"
#include "include/UartInterface.h"
#include <filesystem>

//*****************************************************************************
//
// Globals whose values are set or overridden via command line parameters.
//
//*****************************************************************************
bool g_bVerbose = false;
bool g_bShownHelp = false;
bool g_bWaitOnExit = false;
bool g_bDualCore = false;
bool g_bCpu1Status = true;
bool g_bCpu3Status = true;
// Output stream defaults to an reference of std::cout with custom deleter (do nothing)
std::unique_ptr<std::ostream, std::remove_reference<void(*)(std::ostream*)>::type> g_pOutputStream(&std::cout, [](std::ostream*){});

//
// Parameter input variable
//
char* g_pszAppFile = nullptr;
char* g_pszAppFile2 = nullptr;
char* g_pszAppLoadAddress = nullptr;
char* g_pszAppEntryAddress = nullptr;
char* g_pszKernelFile = nullptr;
char* g_pszKernelFile2 = nullptr;
char* g_pszSecCfgProgramFile = nullptr;
char* g_pszHSMFlashCodeProvisionFile = nullptr;
char* g_pszCPU1FlashCodeProvisionFile = nullptr;
char* g_pszCPU3FlashCodeProvisionFile = nullptr;
char* g_pszHSMRunTimeFile = nullptr;
char* g_pszHSMKeysFile = nullptr;
char* g_pszComPort = nullptr;
char* g_pszDeviceName = nullptr;
char* g_pszLogFile = nullptr;

uint32_t CERT_SIZE = 4096;
uint32_t CP_CHUNK_SIZE = 14336;

//
// Device name
//
bool g_bf29h85x = false;

//*****************************************************************************
//
// The main entry point of the DFU programmer example application.
//
//*****************************************************************************
int main(int argc, char* argv[])
{
	std::ios_base::sync_with_stdio(false);

	int iExitCode = 0;

	//
	// Parse the command line parameters, print the welcome banner and
	// tell the user about any errors they made.
	//
	parseCommandLine(argc, argv);
	if (g_pszKernelFile2 && g_pszAppFile2) {
		g_bDualCore = true;
	}

	//
	// configure and open UART COM/tty port
	//
	FlashProgrammer::UartHandler uartHandle;
	try
	{
		std::cout << g_pszComPort << std::endl;
		uartHandle.configComPort(g_pszComPort);
	}
	catch (const std::exception& eptr)
	{
		const char* badMsg = eptr.what();
		std::cout << "Error occurred during initialization of UART settings: \n" << badMsg << std::endl;
		exitApp(-1);
	}

	//
	// Download the Kernel
	//
#ifdef kernel
	if (!g_pszKernelFile)
	{
		*g_pOutputStream << "ERROR: No flash kernel specified for CPU1 download kernel!" << std::endl;
		exitApp(-1);
	}

	std::cout <<  "\ncalling DownloadKernel CPU1 Kernel\n" << std::endl;
	downloadKernel(uartHandle, g_pszKernelFile);

	// added for delay 
	std::this_thread::sleep_for(std::chrono::milliseconds(6));
#endif


	bool done = false;
	std::vector<uint8_t> packet;
	uint32_t packetLength;
	uint16_t commandType;
	uint16_t tempLength;
	uint32_t entryAddr;
	uint32_t loadAddr;
	FlashStatusCode flashErrorCode;
	FlashStatusCode* flashStatus = &flashErrorCode;


	while (!done)
	{
		// Display user input options
		std::cout << ("\nWhat operation do you want to perform?\n");
		std::cout << ("\t 1-DFU CPU1             (HS-FS only)\n");
		std::cout << ("\t 2-DFU CPU3             (HS-FS only)\n");
		std::cout << ("\t 3-Load HSMRt Image     (Prerequisite for KP & CP)\n");
		std::cout << ("\t 4-Load HSM Keys        (HS-KP Key Provision)\n");
		std::cout << ("\t 5-Program Sec Cfg      (HS-SE Code Provision)\n");
		std::cout << ("\t 6-Load HSM Image       (HS-SE Code Provision)\n");
		std::cout << ("\t 7-Load C29 CPU1 Image  (HS-SE Code Provision)\n");
		std::cout << ("\t 8-Load C29 CPU3 Image  (HS-SE Code Provision)\n");
		std::cout << ("\t 9-Run CPU1\n");
		std::cout << ("\t 10-Run CPU3\n");
		std::cout << ("\t 11-Sync (Verify kernel or Boot Manager is running)\n");
		std::cout << ("\t 12-Reset CPU1\n");
		std::cout << ("\t 0-Done\n");

		size_t responseOption;
		std::cin >> std::dec >> responseOption;

		switch (responseOption)
		{
			
			//------------------------------------DFU_CPU1------------------------------//
		case 1: {
			if (!g_pszAppFile)
			{
				*g_pOutputStream << "ERROR: No flash application specified for CPU1 Flash Programming!" << std::endl;
				exitApp(-1);
			}

			// Construct packet to send DFU command
			packetLength = constructPacket(packet, DFU_CPU1, 0, nullptr);
			*g_pOutputStream << ("\nSending device firmware update command packet\n");
			sendPacket(uartHandle, packet, packetLength);

			// Allow time for flash to be erased
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			// Send the application image
			downloadImage(uartHandle, g_pszAppFile);
			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != DFU_CPU1)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}

			// Retrieve data logging messages
			*g_pOutputStream << ("\nWaiting for logging messages...\n");
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			break;
		}

			  //------------------------------------DFU_CPU3------------------------------//
		case 2: {
			if (!g_pszAppFile2)
			{
				*g_pOutputStream << "ERROR: No flash application specified for CPU3 Flash Programming!" << std::endl;
				exitApp(-1);
			}

			// Construct packet to send DFU command
			packetLength = constructPacket(packet, DFU_CPU3, 0, nullptr);
			*g_pOutputStream << ("\nSending device firmware update command packet\n");
			sendPacket(uartHandle, packet, packetLength);

			// Allow time for flash to be erased
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			// Send the application image
			downloadImage(uartHandle, g_pszAppFile2);
			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != DFU_CPU3)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}

			// Retrieve data logging messages
			*g_pOutputStream << ("\nWaiting for logging messages...\n");
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			break;
		}

			//------------------------------------HSMRt------------------------------//
		case 3:
			if (!g_pszHSMRunTimeFile)
			{
				*g_pOutputStream << "ERROR: No HSMRt Image specified for programming!" << std::endl;
				exitApp(-1);
			}

			// Construct packet to send HSM runtime image command
			packetLength = constructPacket(packet, HSM_RT_IMAGE, 0, nullptr);

			// Send packet with HSM runtime image command
			*g_pOutputStream << "\nSending HSM key provisioning command packet\n";
			sendPacket(uartHandle, packet, packetLength);

			// Send the HSM runtime image
			downloadImage(uartHandle, g_pszHSMRunTimeFile);
			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != HSM_RT_IMAGE)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}

			// Retrieve data logging messages
			*g_pOutputStream << "\nWaiting for logging messages...\n";
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			break;

			//------------------------------------HSM_KEYS------------------------------//
		case 4:
			if (!g_pszHSMKeysFile)
			{
				*g_pOutputStream << "ERROR: No HSM Keys specified for programming!" << std::endl;
				exitApp(-1);
			}

			// Construct packet to send HSM Keys command
			packetLength = constructPacket(packet, HSM_KEYS, 0, nullptr);

			// Send packet with HSM Keys command
			*g_pOutputStream << "\nSending HSM keys command packet\n";
			sendPacket(uartHandle, packet, packetLength);

			// Send the application image
			downloadImage(uartHandle, g_pszHSMKeysFile);
			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != HSM_KEYS)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}

			// Retrieve data logging messages
			*g_pOutputStream << ("\nWaiting for logging messages...\n");
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			break;

		case 5:
			//------------------------------------SEC_CFG_PROGRAM------------------------------//
			if (!g_pszSecCfgProgramFile)
			{
				*g_pOutputStream << "ERROR: No Sec Cfg File specified for programming!" << std::endl;
				exitApp(-1);
			}

			// Construct packet to send Sec Cfg Program Command
			packetLength = constructPacket(packet, SEC_CFG_IMAGE, 0, nullptr);

			// Send packet with SEC CFG command
			*g_pOutputStream << "\nSending SEC_CFG program command packet\n";
			sendPacket(uartHandle, packet, packetLength);

			// Send the application image
			downloadImage(uartHandle, g_pszSecCfgProgramFile);
			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != SEC_CFG_IMAGE)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}

			// Retrieve data logging messages
			*g_pOutputStream << ("\nWaiting for logging messages...\n");
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			break;

			//------------------------------------HSM_CP_LOAD------------------------------//
		case 6:
		{
			if (!g_pszHSMFlashCodeProvisionFile)
			{
				*g_pOutputStream << "ERROR: No HSM Flash Code Provisioning File specified for programming!" << std::endl;
				exitApp(-1);
			}

			std::size_t fileSize = std::filesystem::file_size(g_pszHSMFlashCodeProvisionFile);

			// Calculate the number of breakpoints

			uint32_t numBps = (fileSize - CERT_SIZE) / CP_CHUNK_SIZE;

			std::vector<uint32_t> hardCodedBps;

			// First breakpoint occurs after certificate
			hardCodedBps.push_back(CERT_SIZE);

			// Add breakpoints after each chunk
			// Note that there is a break point after the first 512 bits of the image as well
			for (uint32_t i = (CERT_SIZE + 512); i < fileSize; i += CP_CHUNK_SIZE)
			{
				hardCodedBps.push_back(i);
			}

			// Add another break point if there is data that won't fill a whole chunk or 512 bits
			uint32_t lastChunkSize = (fileSize - CERT_SIZE - 512) % CP_CHUNK_SIZE;
			lastChunkSize = lastChunkSize % 512;
			hardCodedBps.push_back((fileSize - lastChunkSize));

			// Calculate number of breakpoints
			std::size_t sizeBps = hardCodedBps.size();

			// Construct packet to send HSM Code Provisioning Flash Image command
			packetLength = constructPacket(packet, HSM_CP_FLASH_IMAGE, 0, nullptr);

			// Send packet with HSM_CP_FLASH_IMAGE command
			*g_pOutputStream << ("\nSending HSM code provisioning flash image command packet\n");
			sendPacket(uartHandle, packet, packetLength);

			// Send the application image
			downloadImage(uartHandle, g_pszHSMFlashCodeProvisionFile, &hardCodedBps[0], sizeBps);
			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != HSM_CP_FLASH_IMAGE)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}
			// Retrieve data logging messages
			*g_pOutputStream << "\nWaiting for logging messages...\n";
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			break;
		}

			//------------------------------------C29_CPU1_CP_LOAD------------------------------//
		case 7:
		{
			if (!g_pszCPU1FlashCodeProvisionFile)
			{
				*g_pOutputStream << "ERROR: No CPU1 Flash Code Provisioning File specified for programming!" << std::endl;
				exitApp(-1);
			}

			std::size_t fileSize = std::filesystem::file_size(g_pszCPU1FlashCodeProvisionFile);

			// Calculate the number of breakpoints

			uint32_t numBps = (fileSize - CERT_SIZE) / CP_CHUNK_SIZE;

			std::vector<uint32_t> hardCodedBps;

			// First breakpoint occurs after certificate
			hardCodedBps.push_back(CERT_SIZE);

			// Add breakpoints after each chunk
			// Note that there is a break point after the first 512 bits of the image as well
			for (uint32_t i = (CERT_SIZE + 512); i < fileSize; i += CP_CHUNK_SIZE)
			{
				hardCodedBps.push_back(i);
			}

			// Add another break point if there is data that won't fill a whole chunk or 512 bits
			uint32_t lastChunkSize = (fileSize - CERT_SIZE - 512) % CP_CHUNK_SIZE;
			lastChunkSize = lastChunkSize % 512;
			hardCodedBps.push_back((fileSize - lastChunkSize));

			// Calculate number of breakpoints
			std::size_t sizeBps = hardCodedBps.size();

			// Construct packet to send CPU1_CP_FLASH_IMAGE command
			packetLength = constructPacket(packet, CPU1_CP_FLASH_IMAGE, 0, nullptr);

			// Send packet with CPU1_CP_FLASH_IMAGE command
			*g_pOutputStream << ("\nSending CPU1 code provisioning flash image command packet\n");
			sendPacket(uartHandle, packet, packetLength);

			// Send the application image
			downloadImage(uartHandle, g_pszCPU1FlashCodeProvisionFile, (void*) &hardCodedBps[0], sizeBps);
			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != CPU1_CP_FLASH_IMAGE)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}

			// Retrieve data logging messages
			*g_pOutputStream << ("\nWaiting for logging messages...\n");
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			break;
		}

		//------------------------------------C29_CPU3_CP_LOAD------------------------------//
		case 8:
		{
			if (!g_pszCPU3FlashCodeProvisionFile)
			{
				*g_pOutputStream << "ERROR: No CPU3 Flash Code Provisioning File specified for programming!" << std::endl;
				exitApp(-1);
			}

			std::size_t fileSize = std::filesystem::file_size(g_pszCPU3FlashCodeProvisionFile);

			// Calculate the number of breakpoints

			uint32_t numBps = (fileSize - CERT_SIZE) / CP_CHUNK_SIZE;

			std::vector<uint32_t> hardCodedBps;

			// First breakpoint occurs after certificate
			hardCodedBps.push_back(CERT_SIZE);

			// Add breakpoints after each chunk
			// Note that there is a break point after the first 512 bits of the image as well
			for (uint32_t i = (CERT_SIZE + 512); i < fileSize; i += CP_CHUNK_SIZE)
			{
				hardCodedBps.push_back(i);
			}

			// Add another break point if there is data that won't fill a whole chunk or 512 bits
			uint32_t lastChunkSize = (fileSize - CERT_SIZE - 512) % CP_CHUNK_SIZE;
			lastChunkSize = lastChunkSize % 512;
			hardCodedBps.push_back((fileSize - lastChunkSize));

			// Calculate number of breakpoints
			std::size_t sizeBps = hardCodedBps.size();

			// Construct packet to send CPU3_CP_FLASH_IMAGE command
			packetLength = constructPacket(packet, CPU3_CP_FLASH_IMAGE, 0, nullptr);

			// Send packet with CPU3_CP_FLASH_IMAGE command
			*g_pOutputStream << ("\nSending CPU3 code provisioning flash image command packet\n");
			sendPacket(uartHandle, packet, packetLength);

			// Send the application image
			downloadImage(uartHandle, g_pszCPU3FlashCodeProvisionFile, (void*)&hardCodedBps[0], sizeBps);
			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != CPU3_CP_FLASH_IMAGE)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}

			// Retrieve data logging messages
			*g_pOutputStream << ("\nWaiting for logging messages...\n");
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			break;
		}

			//------------------------------------RUN_CPU1----------------------------------//
		case 9:
			if (g_bCpu1Status == false)
			{
				*g_pOutputStream << "ERROR: Cannot perform operations on CPU1 after CPU3 is booted and given control of UART!" << std::endl;
				break;
			}

			//
			// Optional Entry Address override
			//
			if (g_pszAppEntryAddress)
			{
				// Convert entry address to uint32_t
				entryAddr = strtoul(g_pszAppEntryAddress, nullptr, 16);

				// Construct packet with app entry address selection
				packetLength = constructPacket(packet, SET_APP_ENTRY_ADDRESS, sizeof(entryAddr), (uint8_t*)&entryAddr);

				// Send packet with app entry address selection
				*g_pOutputStream << ("\nSending entry address command packet\n");
				sendPacket(uartHandle, packet, packetLength);
				commandType = getPacket(uartHandle, packet, &tempLength);
				if (commandType != SET_APP_ENTRY_ADDRESS)
				{
					*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
				}
				parseFlashStatus(packet, flashStatus);
				if (flashStatus->status != NO_COMMAND_ERROR)
				{
					printErrorStatus(flashStatus->status);
					*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
					printErrorStatus(flashStatus->flashAPIError);
					*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
				}
			}

			// Construct packet with run cpu1 command
			packetLength = constructPacket(packet, RUN_CPU1, 0, nullptr);

			// Send packet with run cpu1 command
			*g_pOutputStream << "\nSending run CPU1 command packet\n";
			sendPacket(uartHandle, packet, packetLength);

			break;

			//------------------------------------RUN_CPU3----------------------------------//
		case 10:
			if (g_bCpu1Status == false)
			{
				*g_pOutputStream << "ERROR: Cannot perform operations on CPU1 after CPU3 is booted and given control of UART!" << std::endl;
				break;
			}

			//
			// Optional Entry Address override
			//
			if (g_pszAppEntryAddress)
			{
				// Convert entry address to uint32_t
				entryAddr = strtoul(g_pszAppEntryAddress, nullptr, 16);

				// Construct packet with app entry address selection
				packetLength = constructPacket(packet, SET_APP_ENTRY_ADDRESS, sizeof(entryAddr), (uint8_t*)&entryAddr);

				// Send packet with app entry address selection
				*g_pOutputStream << ("\nSending entry address command packet\n");
				sendPacket(uartHandle, packet, packetLength);
				commandType = getPacket(uartHandle, packet, &tempLength);
				if (commandType != SET_APP_ENTRY_ADDRESS)
				{
					*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
				}
				parseFlashStatus(packet, flashStatus);
				if (flashStatus->status != NO_COMMAND_ERROR)
				{
					printErrorStatus(flashStatus->status);
					*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
					printErrorStatus(flashStatus->flashAPIError);
					*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
				}
			}

			// Construct packet with run cpu1 command
			packetLength = constructPacket(packet, RUN_CPU3, 0, nullptr);

			// Send packet with run cpu1 command
			*g_pOutputStream << "\nSending run CPU3 command packet\n";
			sendPacket(uartHandle, packet, packetLength);

			break;

			//------------------------------------SYNC_STATUS---------------------------------//
		case 11:

			// Construct packet with reset cpu1 command
			packetLength = constructPacket(packet, SYNC_STATUS, 0, nullptr);

			// Send packet with reset cpu1 command
			*g_pOutputStream << "\nSending reset CPU1 command packet\n";
			sendPacket(uartHandle, packet, packetLength);

			// Retrieve data logging messages
			*g_pOutputStream << "\nWaiting for logging messages...\n";
			getPacket(uartHandle, packet, &tempLength);
			*g_pOutputStream << ("Received message:\n");
			(*g_pOutputStream).write((char*)packet.data(), tempLength) << std::endl;

			commandType = getPacket(uartHandle, packet, &tempLength);
			if (commandType != SYNC_STATUS)
			{
				*g_pOutputStream << "validation ERROR with returned command!" << std::endl;
			}
			parseFlashStatus(packet, flashStatus);
			if (flashStatus->status != NO_COMMAND_ERROR)
			{
				printErrorStatus(flashStatus->status);
				*g_pOutputStream << std::hex << std::showbase << "ERROR Flashing Address: " << flashStatus->address << std::endl;
				printErrorStatus(flashStatus->flashAPIError);
				*g_pOutputStream << std::hex << std::showbase << "FMSTAT Register contents: " << flashStatus->flashAPIFsmStatus << std::endl;
			}

			break;

			//------------------------------------RESET_CPU1---------------------------------//
		case 12:
			if (g_bCpu1Status == false)
			{
				*g_pOutputStream << "ERROR: Cannot perform operations on CPU1 after CPU3 is booted and given control of UART!" << std::endl;
				break;
			}

			// Construct packet with reset cpu1 command
			packetLength = constructPacket(packet, RESET_CPU1, 0, nullptr);

			// Send packet with reset cpu1 command
			*g_pOutputStream << "\nSending reset CPU1 command packet\n";
			sendPacket(uartHandle, packet, packetLength);

			break;

			//------------------------------------DONE-----------------------------------------//
		case 0:
			done = true;
			iExitCode = 0;
			std::cout << "Exiting the Application." << std::endl;
			break;

			//------------------------------------DEFAULT-------------------------------------//
		default:
			std::cout << "Command not recognized, please try again" << std::endl;
			break;
		}
	}

	/***********************************************************************/

	exitApp(iExitCode);
}
/** @} */