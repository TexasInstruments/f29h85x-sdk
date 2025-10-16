//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{ 
//! 
//! \file   CommandLine.h
//! 
//! \brief  Includes the command line utility functions to parse all command parameters
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

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "Common.h"
#include "OutputStream.h"

//
// Global parameter input variable
//
extern char* g_pszAppLoadAddress;
extern char* g_pszAppEntryAddress;
extern char* g_pszKernelFile;
extern char* g_pszCPU1AppFile;
extern char* g_pszCPU3AppFile;
extern char* g_pszSecCfgProgramFile;
extern char* g_pszHSMFlashCodeProvisionFile;
extern char* g_pszCPU1FlashCodeProvisionFile;
extern char* g_pszCPU3FlashCodeProvisionFile;
extern char* g_pszHSMRunTimeFile;
extern char* g_pszHSMKeysFile;
extern char* g_pszAltTargetBaudRate;
extern char* g_pszAltHostBaudRate;
extern char* g_pszComPort;
extern char* g_pszDeviceName;
extern char* g_pszLogFile;

extern bool g_bShownHelp;
extern bool g_bWaitOnExit;
extern bool g_bUsrCommand;
extern bool g_bBootOnly;

extern std::queue<size_t> g_usrInputOptions;

void parseCommandLine(int argc, char* argv[]);
void exitApp(int iRetcode);

#endif /* COMMANDLINE_H */
/** @} */

