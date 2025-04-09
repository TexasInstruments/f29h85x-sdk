//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   CommandLine.cpp
//! 
//! \brief  Command line prints, error checks and parameter parsing functions
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

#include "../include/CommandLine.h"

#include <unordered_map>
#include <functional>

// Needed by exitApp()
#if defined(_WIN32)
#include <conio.h>
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#include <termios.h>
#include <unistd.h>
#endif 



//*****************************************************************************
//
// \brief	Display the welcome banner when the program is started.
//
//*****************************************************************************
void printWelcome(void)
{
	std::cout << "\nF29x UART Firmware Programmer\n";
	std::cout << "Copyright (c) 2024 Texas Instruments Incorporated.\n\n";
}

//*****************************************************************************
//
// \brief	Show help on the application command line parameters.
//
//*****************************************************************************
void showHelp(void)
{
	//
	// Only print help if help has not been shown before.
	//
	if (g_bShownHelp)
	{
		return;
	}

	std::cout << ("\nF29x UART Firmware Programmer\n");
	std::cout << ("Supported parameters are:\n\n");
	std::cout << ("-d,  --device <device>     - The device family of the target device:\n");
	std::cout << ("                             (f29h85x)\n");
	std::cout << ("-p,  --port   <port>       - Serial COM/tty port used for UART communication.\n");
	std::cout << ("                             (port format: COM<num>, /dev/ttyUSB<num>, /dev/ttyACM<num>)\n");
	std::cout << ("-k,  --kernel    <file>    - File path for uart flash kernel\n");
	std::cout << ("-a1, --appcpu1   <file>    - File path for Flash-based C29 CPU1 application image (HS-FS Only)\n");
	std::cout << ("-a3, --appcpu3   <file>    - File path for Flash-based C29 CPU3 application image (HS-FS Only)\n");
	std::cout << ("-sr, --hsmrt     <file>    - File path for RAM-based HSM runtime (HSMRt) image    (Prerequisite for KP & CP)\n");
	std::cout << ("-sk, --hsmkeys   <file>    - File path for HSM keys image                         (HS-KP key provision)\n");
	std::cout << ("-s1, --cpappcpu1 <file>    - File path for Flash-based C29 CPU1 application image (HS-SE code provision)\n");
	std::cout << ("-s3, --cpappcpu3 <file>    - File path for Flash-based C29 CPU3 application image (HS-SE code provision)\n");
	std::cout << ("-sh, --cpapphsm  <file>    - File path for Flash-based HSM application image      (HS-SE code provision)\n");
	std::cout << ("-sc, --cpseccfg  <file>    - File path for Sec Cfg program image                  (HS-SE code provision)\n");
	std::cout << ("-e1, --entryaddr <hex_num> - (optional) Override entry address of the C29 CPU1 application \n");

	std::cout << ("\nNote: -d, -p, -k are mandatory parameters.\n");
	std::cout << ("Note: Images must be in the binary format and includes an X.509 certificate.\n\n");

	std::cout << ("-h, --help       - Show this help.\n");
	std::cout << ("-q, --quiet      - Quiet mode. Suppress all non-essential printouts\n");
	std::cout << ("-l, --log <file> - Log mode. Redirect all non-essential printouts to the specified file, will override -q mode\n");
	std::cout << ("-w               - Wait on keypress before exiting\n");
	//std::cout << ("-v           - Enable verbose output\n");
	std::cout << ("\nSyntax: -d f29h85x -p COM41 -k ex3_uart_flash_kernel.bin --appcpu1 c29_cpu1_application.bin --entryaddr 10001000 --hsmrt HSM_runtimeImage.bin --hsmkeys HSM_customKeyCert.bin --cpseccfg sec_cfg_cert.bin --cpappcpu1 c29_cpu1_application.bin -cpapphsm hsm_application.bin -l output.log\n");

	std::cout << std::endl;

	g_bShownHelp = true;
}

//*****************************************************************************
//
// \brief	Parse the command line, extracting all parameters.
//
// On failure, calls ExitApp(-1).
//
//*****************************************************************************
void parseCommandLine(int argc, char* argv[])
{
	//
	// Lambda functions for each parameter action
	//
	auto setQuietMode = [](){
		// Don't override if output stream is already an instance of FileStream
		if (!dynamic_cast<FileStream*>(g_pOutputStream.get()))
		{
			NullStream* nullStream = new NullStream();
			g_pOutputStream.reset(nullStream);
		}
		std::cout << "Quiet mode specified, all non-essential outputs will be suppressed.\n";
	};

	auto setLogMode = [](char* file) {
		g_pszLogFile = file;
		FileStream* fileStream = new FileStream(g_pszLogFile);
		g_pOutputStream.reset(fileStream);
		std::cout << "Log mode specified, all non-essential outputs will be redirected to " << g_pszLogFile << ".\n";
	};

	auto setWaitOnExitMode = []() { g_bWaitOnExit = true; };

	auto setPortName      = [](char* port) { g_pszComPort = port; };
	auto setKernelFile    = [](char* file) { g_pszKernelFile = file; };
	auto setAppCpu1File   = [](char* file) { g_pszAppFile = file; };
	auto setAppCpu3File   = [](char* file) { g_pszAppFile2 = file; };
	auto setHSMRtFile     = [](char* file) { g_pszHSMRunTimeFile = file; };
	auto setHSMKeysFile   = [](char* file) { g_pszHSMKeysFile = file; };
	auto setCPAppCpu1File = [](char* file) { g_pszCPU1FlashCodeProvisionFile = file; };
	auto setCPAppCpu3File = [](char* file) { g_pszCPU3FlashCodeProvisionFile = file; };
	auto setCPAppHSMFile  = [](char* file) { g_pszHSMFlashCodeProvisionFile = file; };
	auto setCPSecCfgFile  = [](char* file) { g_pszSecCfgProgramFile = file; };
	auto setEntryAddress  = [](char* addr) { g_pszAppEntryAddress = addr; };

	std::unordered_map<std::string, std::function<void()>> noArgActions = {
		{"-h",		showHelp},
		{"--help",	showHelp},
		{"-q",		setQuietMode},
		{"--quiet",	setQuietMode},
		{"-w",		setWaitOnExitMode},
	};

	std::unordered_map<std::string, std::function<void(char*)>> wArgActions = {
		{"-d",		   setDeviceName},
		{"--device",   setDeviceName},
		{"-p",		   setPortName},
		{"--port",	   setPortName},
		{"-k",		   setKernelFile},
		{"--kernel",   setKernelFile},
		{"-a1",		   setAppCpu1File},
		{"--appcpu1",  setAppCpu1File},
		{"-a3",		   setAppCpu3File},
		{"--appcpu3",  setAppCpu3File},
		{"-sr",		 setHSMRtFile},
		{"--hsmrt",	 setHSMRtFile},
		{"-sk",		 setHSMKeysFile},
		{"--hsmkeys",   setHSMKeysFile},
		{"-s1",			setCPAppCpu1File},
		{"--cpappcpu1", setCPAppCpu1File},
		{"-s3",			setCPAppCpu3File},
		{"--cpappcpu3", setCPAppCpu3File},
		{"-sh",			setCPAppHSMFile},
		{"--cpapphsm",  setCPAppHSMFile},
		{"-sc",			setCPSecCfgFile},
		{"--cpseccfg",  setCPSecCfgFile},
		{"-e1",			setEntryAddress},
		{"--entryaddr", setEntryAddress},
		{"-l",		     setLogMode},
		{"--log",	     setLogMode},
	};

	//
	// Walk through each of the parameters in the arr, skipping the first one
	// which is the executable name itself.
	//
	for (int iParm = 1; iParm < argc; iParm++)
	{
		auto exitErrorMsg = [](const std::ostringstream& message)
		{
			showHelp();
			std::cout << message.str() << std::endl;
			exitApp(-1);
		};

		std::ostringstream message;
		std::string param = argv[iParm];
		
		//
		// Check if any key matches with a value
		//
		auto noArgKey = noArgActions.find(param);
		auto wArgKey = wArgActions.find(param);
		if (noArgKey != noArgActions.end())
		{
			//
			// Run the value func
			//
			noArgKey->second();
		}
		else if (wArgKey != wArgActions.end())
		{
			//
			// Check flag input parameter for validity 
			// (if flag input parameter exceeds number of input or is an input flag itself)
			//
			char* nextParam = argv[++iParm];
			if (iParm >= argc || noArgActions.find(nextParam) != noArgActions.end() || wArgActions.find(nextParam) != wArgActions.end())
			{
				message << "Missing an input to parameter: " << argv[--iParm] << "\n";
				exitErrorMsg(message);
			}
			wArgKey->second(nextParam);
		}
		else
		{
			message << "Unrecognized argument: " << argv[iParm] << "\n";
			exitErrorMsg(message);
		}
	}

	checkErrors();

	printWelcome();
}

//*****************************************************************************
//
// \brief	Exit the application, optionally pausing for a key press first.
//
//*****************************************************************************
void exitApp(int iRetcode)
{

	//
	// Has the caller asked us to pause before exiting?
	//
	if (g_bWaitOnExit)
	{
		//
		// Wait for a key press.
		//
#if defined(_WIN32)
		printf("\nPress any key to exit...\n");
		while (!_kbhit()) {}
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
		printf("\nPress enter or ctrl+c to exit...\n");
		char c;
		read(STDIN_FILENO, &c, 1);
#endif
	}

	exit(iRetcode);
}

//*****************************************************************************
//
// \brief	Parse device name strings and assign corresponding variables
//
//*****************************************************************************
void setDeviceName(char* deviceName)
{
	if (deviceName == nullptr)
	{
		std::cout << "ERROR: No device family specified. Please use -d to provide the target device.\n";
		exitApp(-1);
	}

	//
	// if not a proper input device name
	// 0 == false, !false = !0 = true. strncmp && wcsncmp returns !0 = true if different.
	//
	if (!strncmp(deviceName, "f29h85x", 7))
	{
		g_bf29h85x = true;
	}
	else
	{
		std::cout << "ERROR: Device name is not recognized. Please see -h for the list of recognized device family.\n";
		exitApp(-1);
	}

	g_pszDeviceName = deviceName;

	return;
}

//*****************************************************************************
//
// \brief	Checks for mandatory parameters to ensure necessary input exists
//
//*****************************************************************************
void checkErrors(void)
{
	bool hasError = false;

	//
	// Catch if no Com/tty port inputs.
	//
	if (!g_pszComPort)
	{
		showHelp();
		std::cout << "ERROR: No COM/tty port number was specified. Please use -p to provide a serial port.\n";
		hasError = true;
	}
	//
	// Catch if no target device inputs.
	//
	if (!g_pszDeviceName)
	{
		showHelp();
		std::cout << "ERROR: No device family specified. Please use -d to provide the target device.\n";
		hasError = true;
	}

#ifdef kernel
	//
	// Catch if no flash kernel image inputs.
	//
	if (!g_pszKernelFile)
	{
		showHelp();
		std::cout << "ERROR: No flash kernel image specified. Please use -k to provide a kernel image.\n";
		hasError = true;
	}
#endif 

	if (hasError)
	{
		std::cout << "Not all mandatory parameters are specified, exiting the application...\n";
		exitApp(-1);
	}

}

/** @} */