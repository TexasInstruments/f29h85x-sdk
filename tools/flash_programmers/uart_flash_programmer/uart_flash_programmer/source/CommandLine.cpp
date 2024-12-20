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

	std::cout << ("This application may be used to download images to a Texas Instruments\n");
	std::cout << ("F29x microcontroller in UART boot mode.\n\n");
	std::cout << ("Supported parameters are:\n\n");
	std::cout << ("-d <device>   - The device family of the target device:\n");
	std::cout << ("                (f29h85x)\n");
	std::cout << ("-p <port>     - Serial COM/tty port used for UART communication.\n");
	std::cout << ("                (port format: COM<num>, /dev/ttyUSB<num>, /dev/ttyACM<num>)\n");
	std::cout << ("-k <file>     - File path for uart flash kernel\n");
	std::cout << ("-a <file>     - File path for Flash-based C29 CPU1 application image (HS-FS Only)\n");
	std::cout << ("-j <file>     - File path for RAM-based HSM runtime (HSMRt) image    (Prerequisite for KP & CP)\n");
	std::cout << ("-f <file>     - File path for HSM keys image                         (HS-KP key provision)\n");
	std::cout << ("-t <file>     - File path for Flash-based C29 CPU1 application image (HS-SE code provision)\n");
	std::cout << ("-g <file>     - File path for Flash-based HSM application image      (HS-SE code provision)\n");
	std::cout << ("-c <file>     - File path for Sec Cfg program image                  (HS-SE code provision)\n");
	std::cout << ("-e <hex_num>  - Override entry address of the C29 CPU1 application, optional\n");
	std::cout << ("\nNote: -d, -k, -p are mandatory parameters.\n");
	std::cout << ("Note: Images must be in the binary format and includes an X.509 certificate.\n\n");

	std::cout << ("-? or -h      - Show this help.\n");
	std::cout << ("-q            - Quiet mode. Suppress all non-essential printouts\n");
	std::cout << ("-l <file>     - Log mode. Redirect all non-essential printouts to the specified file, will override -q mode\n");
	std::cout << ("-w		     - Wait on keypress before exiting\n");
	//std::cout << ("-v            - Enable verbose output\n");
	std::cout << ("\nSyntax: -d f29h85x -p COM41 -k ex3_uart_flash_kernel.bin -a c29_cpu1_application.bin -e 10001000 -j HSM_runtimeImage.bin -f HSM_customKeyCert.bin -c sec_cfg_cert.bin -t c29_cpu1_application.bin -g hsm_application.bin -l output.log\n");

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
	int iParm;
	char* pcOptArg = nullptr;

	//
	// By default, don't show the help screen.
	//
	g_bShownHelp = false;

	//
	// Walk through each of the parameters in the list, skipping the first one
	// which is the executable name itself.
	//
	for (iParm = 1; iParm < argc; iParm++)
	{

		if (!argv || ((argv[iParm][0] != '-') && (argv[iParm][0] != '/')) ||
			(argv[iParm][1] == '\0'))
		{
			//
			// We found something on the command line that didn't look like a
			// switch so ExitApp.
			//
			std::cout << "Unrecognized or invalid argument: " << argv[iParm] << "\n";
			exitApp(-1);
		}
		else
		{
			//
			// Get a pointer to the next argument since it may be used
			// as a parameter for the case statements 
			//
			pcOptArg = ((iParm + 1) < argc) ? argv[iParm + 1] : NULL;
		}

		switch (argv[iParm][1])
		{
		case 'a':
			g_pszAppFile = pcOptArg;
			iParm++;
			break;

		case 'c':
			g_pszSecCfgProgramFile = pcOptArg;
			iParm++;
			break;

		case 'd':
			g_pszDeviceName = pcOptArg;
			iParm++;
			setDeviceName();
			break;

		case 'e':
			g_pszAppEntryAddress = pcOptArg;
			iParm++;
			break;

		case 'f':
			g_pszHSMKeysFile = pcOptArg;
			iParm++;
			break;

		case 'g':
			g_pszHSMFlashCodeProvisionFile = pcOptArg;
			iParm++;
			break;

		case 'j':
			g_pszHSMRunTimeFile = pcOptArg;
			iParm++;
			break;

		case 't':
			g_pszCPU1FlashCodeProvisionFile = pcOptArg;
			iParm++;
			break;

		case 'k':
			g_pszKernelFile = pcOptArg;
			iParm++;
			break;

		case 'l':
			{
			g_pszLogFile = pcOptArg;
			FileStream* fileStream = new FileStream(g_pszLogFile);
			g_pOutputStream.reset(fileStream);
			iParm++;
			}
			break;

		case 'm':
			g_pszKernelFile2 = pcOptArg;
			iParm++;
			break;

		case 'n':
			g_pszAppFile2 = pcOptArg;
			iParm++;
			break;

		case 'p':
			g_pszComPort = pcOptArg;
			iParm++;
			break;

		case 'q':
			{
			//
			// Don't override if output stream is already an instance of FileStream
			//
			if (!dynamic_cast<FileStream*>(g_pOutputStream.get()))
			{
				NullStream* nullStream = new NullStream();
				g_pOutputStream.reset(nullStream);
			}
			iParm++;
			}
			break;

		case 'v':
			g_bVerbose = true;
			break;

		case 'w':
			g_bWaitOnExit = true;
			break;

		case '?':
		case 'h':
			showHelp();
			exitApp(0);
			break;

		default:
			std::cout << "Unrecognized argument: " << argv[iParm] << "\n\n";
			showHelp();
			exitApp(-1);

		}
	}

	printWelcome();

	checkErrors();
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
void setDeviceName(void)
{
	if (g_pszDeviceName == nullptr)
	{
		std::cout << "ERROR: No device family specified. Please use -d to provide the target device.\n";
		exitApp(-1);
	}

	//
	// if not a proper input device name
	// 0 == false, !false = !0 = true. strncmp && wcsncmp returns !0 = true if different.
	//
	if (!strncmp(g_pszDeviceName, "f29h85x", 7))
	{
		g_bf29h85x = true;
	}
	else
	{
		std::cout << "ERROR: Device name is not recognized. Please see -h for the list of recognized device family.\n";
		exitApp(-1);
	}
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