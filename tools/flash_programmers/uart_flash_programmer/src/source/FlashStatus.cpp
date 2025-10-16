//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   FlashStatus.cpp
//! 
//! \brief  Utility file to interpret Flash Status Packet Info (FlashStatusPkt_t)
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

#include "../include/FlashStatus.h"

//
// Internal Functions
//
int _printFMSTAT_f29h85x(std::ostream& console, FlashStatusPkt_t& flashPkt);


//*****************************************************************************
//!
//! \brief   Prints the Flash Status Packet Info (FlashStatusPkt_t) to the console
//!
//! \param console      The output stream to print the Flash Status Packet Info
//! \param flashPkt		 The Flash Status Packet Info to be printed
//! 
//! \return             0 upon success, -1 if error occurs
//! 
//*****************************************************************************
int printFlashStatus(std::ostream& console, FlashStatusPkt_t& flashPkt)
{
	int retVal;

	if (g_bf29h85x || g_bf29p58x || g_bf29p32x)
	{
		retVal = _printFMSTAT_f29h85x(console, flashPkt);
	}
	else
	{
		console << "printFlashStatus warning: no implementation is available for the inputted device, using default F29H85x printFlashStatus parser..." << std::endl;
		retVal = _printFMSTAT_f29h85x(console, flashPkt);
	}

	return retVal;
}

int _printFMSTAT_f29h85x(std::ostream& console, FlashStatusPkt_t& flashPkt)
{
	/* F29H85x Flash tech enum */
	typedef enum
	{
		Fapi_Status_Success = 0,         /* Function completed successfully */
		Fapi_Status_FsmBusy,             /* FSM is Busy */
		Fapi_Status_FsmReady,            /* FSM is Ready */
		Fapi_Status_AsyncBusy,           /* Async function operation is Busy */
		Fapi_Status_AsyncComplete,       /* Async function operation is Complete */
		Fapi_Error_Fail = 500,           /* Generic Function Fail code */
		Fapi_Error_StateMachineTimeout,  /* State machine polling never returned ready and timed out */
		Fapi_Error_OtpChecksumMismatch,  /* Returned if OTP checksum does not match expected value */
		Fapi_Error_InvalidDelayValue,    /* Returned if the Calculated RWAIT value exceeds 15  - Legacy Error */
		Fapi_Error_InvalidHclkValue,     /* Returned if FClk is above max FClk value - FClk is a calculated from HClk and RWAIT/EWAIT */
		Fapi_Error_InvalidCpu,           /* Returned if the specified Cpu does not exist */
		Fapi_Error_InvalidBank,          /* Returned if the specified bank does not exist */
		Fapi_Error_InvalidAddress,       /* Returned if the specified Address does not exist in Flash or OTP */
		Fapi_Error_InvalidReadMode,      /* Returned if the specified read mode does not exist */
		Fapi_Error_AsyncIncorrectDataBufferLength,
		Fapi_Error_AsyncIncorrectEccBufferLength,
		Fapi_Error_AsyncDataEccBufferLengthMismatch,
		Fapi_Error_FeatureNotAvailable,  /* FMC feature is not available on this device */
		Fapi_Error_FlashRegsNotWritable, /* Returned if Flash registers are not writable due to security */
		Fapi_Error_InvalidCPUID,          /* Returned if OTP has an invalid CPUID */
		Fapi_Error_InvalidBankMode       /* Returned if BankMode provided is invalid */
	}  Fapi_StatusType;

	//
	// If good standing, print and exit
	//
	if (flashPkt.flashAPIError == FLASH_NO_ERROR)
	{
		console << "\tFlash status in good standing.\n";
		return 0;
	}

	std::string status_str, apiError_str, statCmd_str;

	// Convert to strings
	switch (flashPkt.status)
	{
	case Fapi_StatusType::Fapi_Status_Success:
		status_str = STRING_LITERAL(Fapi_Status_Success);
		break;
	case Fapi_StatusType::Fapi_Status_FsmBusy:
		status_str = STRING_LITERAL(Fapi_Status_FsmBusy);
		break;
	case Fapi_StatusType::Fapi_Status_FsmReady:
		status_str = STRING_LITERAL(Fapi_Status_FsmReady);
		break;
	case Fapi_StatusType::Fapi_Status_AsyncBusy:
		status_str = STRING_LITERAL(Fapi_Status_AsyncBusy);
		break;
	case Fapi_StatusType::Fapi_Status_AsyncComplete:
		status_str = STRING_LITERAL(Fapi_Status_AsyncComplete);
		break;
	case Fapi_StatusType::Fapi_Error_Fail:
		status_str = STRING_LITERAL(Fapi_Error_Fail);
		break;
	case Fapi_StatusType::Fapi_Error_StateMachineTimeout:
		status_str = STRING_LITERAL(Fapi_Error_StateMachineTimeout);
		break;
	case Fapi_StatusType::Fapi_Error_OtpChecksumMismatch:
		status_str = STRING_LITERAL(Fapi_Error_OtpChecksumMismatch);
		break;
	case Fapi_StatusType::Fapi_Error_InvalidDelayValue:
		status_str = STRING_LITERAL(Fapi_Error_InvalidDelayValue);
		break;
	case Fapi_StatusType::Fapi_Error_InvalidHclkValue:
		status_str = STRING_LITERAL(Fapi_Error_InvalidHclkValue);
		break;
	case Fapi_StatusType::Fapi_Error_InvalidCpu:
		status_str = STRING_LITERAL(Fapi_Error_InvalidCpu);
		break;
	case Fapi_StatusType::Fapi_Error_InvalidBank:
		status_str = STRING_LITERAL(Fapi_Error_InvalidBank);
		break;
	case Fapi_StatusType::Fapi_Error_InvalidAddress:
		status_str = STRING_LITERAL(Fapi_Error_InvalidAddress);
		break;
	case Fapi_StatusType::Fapi_Error_InvalidReadMode:
		status_str = STRING_LITERAL(Fapi_Error_InvalidReadMode);
		break;
	case Fapi_StatusType::Fapi_Error_AsyncIncorrectDataBufferLength:
		status_str = STRING_LITERAL(Fapi_Error_AsyncIncorrectDataBufferLength);
		break;
	case Fapi_StatusType::Fapi_Error_AsyncIncorrectEccBufferLength:
		status_str = STRING_LITERAL(Fapi_Error_AsyncIncorrectEccBufferLength);
		break;
	case Fapi_StatusType::Fapi_Error_AsyncDataEccBufferLengthMismatch:
		status_str = STRING_LITERAL(Fapi_Error_AsyncDataEccBufferLengthMismatch);
		break;
	case Fapi_StatusType::Fapi_Error_FeatureNotAvailable:
		status_str = STRING_LITERAL(Fapi_Error_FeatureNotAvailable);
		break;
	case Fapi_StatusType::Fapi_Error_FlashRegsNotWritable:
		status_str = STRING_LITERAL(Fapi_Error_FlashRegsNotWritable);
		break;
	case Fapi_StatusType::Fapi_Error_InvalidCPUID:
		status_str = STRING_LITERAL(Fapi_Error_InvalidCPUID);
		break;
	case Fapi_StatusType::Fapi_Error_InvalidBankMode:
		status_str = STRING_LITERAL(Fapi_Error_InvalidBankMode);
		break;
	default:
		status_str = "Unknown";
		break;
	}
	status_str += " (value = " + std::to_string(flashPkt.status) + ")";

	switch (flashPkt.flashAPIError)
	{
	case FLASH_BLANK_ERROR:
		apiError_str = "Blank check error";
		break;
	case FLASH_VERIFY_ERROR:
		apiError_str = "Verify error";
		break;
	case FLASH_PROGRAM_ERROR:
		apiError_str = "Program error";
		break;
	case FLASH_COMMAND_ERROR:
		apiError_str = "Command error";
		break;
	case FLASH_UNLOCK_ERROR:
		apiError_str = "Unlock error";
		break;
	case FLASH_AUTHENTICATION_ERROR:
		apiError_str = "Authentication error";
		break;
	case FLASH_ERASE_ERROR:
		apiError_str = "Erase error";
		break;
	case FLASH_NO_ERROR:
		apiError_str = "No error";
		break;
	default:
		apiError_str = "Unknown (value = " + std::to_string(flashPkt.flashAPIError) + ")";
		break;
	}

	// Convert registers to print strings
	auto check_bit = [](uint32_t reg, uint32_t n)
	{
		return (reg & (1U << n)) ? true : false;
	};

	auto convertStatusCmdStr = [&](uint32_t statCmd)
		{
			std::string retStr;
			std::ostringstream oss;
			if (check_bit(statCmd, 0)) { oss << "\n\t( Command Done "; }
			else { oss << "\n\t( Command NOT Done "; }
			if (check_bit(statCmd, 1)) { oss << "\n\t  Command Passed "; }
			else { oss << "\n\t  Command FAILED "; }
			if (check_bit(statCmd, 2)) { oss << "\n\t  Command is In Progress (Not Completed)"; }
			if (check_bit(statCmd, 4)) { oss << "\n\t  Command FAILED due to Write/Erase Protect Sector violation."; }
			if (check_bit(statCmd, 5)) { oss << "\n\t  Command FAILED due to Verify error."; }
			if (check_bit(statCmd, 6)) { oss << "\n\t  Command FAILED due to the use of an Illegal Address."; }
			if (check_bit(statCmd, 8)) { oss << "\n\t  Command FAILED because an attempt was made to program a stored 0 value to a 1."; }
			if (check_bit(statCmd, 12)) { oss << "\n\t  Command FAILED due to error other than write/erase protect violation or verify error."; }

			if (!oss.str().empty())
			{
				retStr = oss.str() + " )";
			}
			return retStr;
		};

	statCmd_str = convertStatusCmdStr(flashPkt.flashAPIFsmStatus);

	console << "Device flash status:\n";
	console << "\tFlash API Return : " << status_str << "\n";
	console << "\tFlash Error Addr : " << std::hex << std::showbase << flashPkt.address << "\n";
	console << "\tFlash Error Type : " << apiError_str << "\n";
	console << "\tFMSTAT/STATCMD value: " << std::hex << std::showbase << flashPkt.flashAPIFsmStatus;
	console << statCmd_str << "\n";

	return 0;
}

/** @} */