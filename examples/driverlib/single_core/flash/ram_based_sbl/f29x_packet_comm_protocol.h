//###########################################################################
//
// FILE:    packet_comm_protocol.h
//
// TITLE:   Packet communication protocol
//
// Defines packet properties and protocols used in communication across flash kernel and host programmer
// 
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

#ifndef PACKET_COMM_PROTOCOL_H
#define PACKET_COMM_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#define COMM_PACKET_PROTOCOL_VERSION    1.0.0

#define SIZE_O(oPkt_t, attr)     sizeof(((oPkt_t*)0)->attr)
#define SIZE_O_VAL(pPkt_t, attr) sizeof(*(((pPkt_t*)0)->attr))
#define BYTES_TO_UINT16(p) (((uint16_t)((const uint8_t*)(p))[1] << 8) | ((const uint8_t*)(p))[0]) // p needs to be type uint8_t*
#define BYTES_TO_UINT32(p) (((uint32_t)((const uint8_t*)(p))[3] << 24) | ((uint32_t)((const uint8_t*)(p))[2] << 16) | ((uint32_t)((const uint8_t*)(p))[1] << 8) | (uint32_t)((const uint8_t*)(p))[0])
#define STRING_LITERAL(x) #x
#define EVAL_STRING_LITERAL(x) STRING_LITERAL(x)

    typedef enum PayloadType_ /* : uint8_t // Can not be negative and exceeds 255 in value*/
    {
        // Do not set value for 0 to prohibit default initalized variable from compilation
        Command = 1,
        CommandResponse = 2,
        FlashStatus = 3,
        Message = 4,
        ErrorStatus = 5,
    } PayloadType;

    //
    // Packet payload struct to encapsulate the attributes in order
    //
    /* Command contents that host sends to SBL as part of handshake, and in some cases, SBL also sends this payload with addintional information back to the host along with command response */
    typedef struct CommandPkt_t_
    {
        uint8_t      payloadType;               // Must be enum PayloadType_ Command
        uint16_t     command;
        uint16_t     addlContentLength;
        char* addlContentAddr;
    } CommandPkt_t;
#define COMMAND_PACKET_SIZE(pCommandPkt) (SIZE_O(CommandPkt_t,payloadType) + SIZE_O(CommandPkt_t,command) + SIZE_O(CommandPkt_t, addlContentLength) + (pCommandPkt)->addlContentLength)

    /* SBL response content to the host command */
    typedef struct CommandResponsePkt_t_
    {
        uint8_t      payloadType;             // Must be enum PacketType_ CommandResponse
        uint16_t     echoCommand;             // Reply with the same command if recognized, if unrecognized, use COMMAND_NOT_RECOGNIZED   
        uint8_t      expectsData;             // Does SBL expects further data for this command, 0 for false or otherwise true (boolean value)
        uint16_t     timeDelay_ms;            // Host time delay before subsequent data transmition, in ms, irrelevant if "expectsData" is false.
        uint16_t     maxPayloadSize;          // Maximum size of data SBL can parse at once, irrelvant if "expectsData" is false, 0 will use host default setting
        uint8_t      expectsEOTpacket;        // Would SBL sends out an addintional packet at end-of-transmission to the host, 0 for false or otherwise true (boolean value)
        uint8_t      reserved;                // Reserved field for future impl. Defaults to 0 for future compatibility.
    } CommandResponsePkt_t;
#define COMMAND_RESPONSE_PACKET_SIZE (SIZE_O(CommandResponsePkt_t,payloadType) + SIZE_O(CommandResponsePkt_t,echoCommand) + SIZE_O(CommandResponsePkt_t,timeDelay_ms) + SIZE_O(CommandResponsePkt_t,expectsData) + SIZE_O(CommandResponsePkt_t,maxPayloadSize) + SIZE_O(CommandResponsePkt_t,expectsEOTpacket) + SIZE_O(CommandResponsePkt_t,reserved))

    typedef struct FlashStatusPkt_t_
    {
        uint8_t      payloadType;                     // Must be enum PacketType_ FlashStatus
        uint16_t     status;
        uint32_t     address;
        uint16_t     flashAPIError;
        uint32_t     flashAPIFsmStatus;               // Flash FSMSTAT/STATCMD status register value
    } FlashStatusPkt_t;
#define FLASH_PACKET_SIZE (SIZE_O(FlashStatusPkt_t,payloadType) + SIZE_O(FlashStatusPkt_t,status) + SIZE_O(FlashStatusPkt_t,address) + SIZE_O(FlashStatusPkt_t,flashAPIError) + SIZE_O(FlashStatusPkt_t,flashAPIFsmStatus))

    typedef struct MessagePkt_t_
    {
        uint8_t     payloadType;                     // Must be enum PacketType_ Message
        uint16_t    length;
        char* msgAddr;
    } MessagePkt_t;
#define MESSAGE_PACKET_SIZE(pMsgPkt) (SIZE_O(MessagePkt_t,payloadType) + SIZE_O(MessagePkt_t,length) + (pMsgPkt)->length)

    typedef enum recoveryStatus_ /* : uint8_t */
    {
        RS_IgnoreStatus = 0,                 // Ignore device status (host won't interpret recoveryStatus)
        RS_Unrecoverable = 1,                // Device stuck in fault state
        RS_NormalOperation = 2,              // Device back in normal operation (fail-safe)
    } recoveryStatus;

    typedef struct ErrorStatusPkt_t_
    {
        uint8_t          payloadType;         // Must be enum PacketType_ ErrorStatus
        uint32_t         errorMsgCode;
        uint8_t          recoveryStatus;      // status of device after error recovery
        uint8_t          hasSprintfArgs;      // If the error Msg code is of a sprintf parsable
        uint8_t          numArgs;             // # of varadic arguments, 0 if "hasSprintfArgs" is false
        uint32_t* pArgsVal;             // address of input varadic arugments (assumes 4bytes for each argument)
    } ErrorStatusPkt_t;
#define ERROR_PACKET_SIZE(pErrPkt)          (((ErrorStatusPkt_t*)pErrPkt)->hasSprintfArgs ? ERROR_PACKET_SIZE_W_ARGS(pErrPkt) : ERROR_PACKET_SIZE_NO_ARGS(pErrPkt)) // In case if user has conflicting hasSprintfArgs and numArgs
#define ERROR_PACKET_SIZE_W_ARGS(pErrPkt)   (SIZE_O(ErrorStatusPkt_t,payloadType) + SIZE_O(ErrorStatusPkt_t,errorMsgCode) + SIZE_O(ErrorStatusPkt_t,recoveryStatus) + SIZE_O(ErrorStatusPkt_t,hasSprintfArgs) + SIZE_O(ErrorStatusPkt_t,numArgs) + (pErrPkt)->numArgs * SIZE_O_VAL(ErrorStatusPkt_t,pArgsVal))
#define ERROR_PACKET_SIZE_NO_ARGS(pErrPkt)  (SIZE_O(ErrorStatusPkt_t,payloadType) + SIZE_O(ErrorStatusPkt_t,errorMsgCode) + SIZE_O(ErrorStatusPkt_t,recoveryStatus) + SIZE_O(ErrorStatusPkt_t,hasSprintfArgs) + SIZE_O(ErrorStatusPkt_t,numArgs))

#ifdef __cplusplus
}

// Error Status Message hash map used by the host
#include <unordered_map>
inline const std::unordered_map<uint32_t, std::string> ErrorStatusPkt_errorMsgCode =
{
    {0x0000, "This is the default error message code 0x0000 and no return message should have this value"},
    {0x0001, "An NMI Error has occured and the device is unable to return to its normal function. Suggest to connect the device via JTAG (w/ debug port open) in CCS and use Error_Agg_Check_Status gel script (in Scripts->Error Handling->Error Aggregator) to see the error status"},

    /* 1xxx reserved for general programming flow */
    {0x1001, "SBL (CPU1) is unable to claim flash semaphore, it might have been claimed by other cores or was never released from the previous fault state. If latter, please perform a device reset such as XRSn reset to release the semaphore." },
    {0x1002, "Unable to verify image size that is a part of the certificate metadata, please make sure to follow the correct post-build steps to generate a complete binary of application image with X.509 certificate. (Note: this is also applicable for non-secure programming as well to obtain the metadata info)"},
    {0x1003, "Image size indicated by the certificate is %d, which is larger than the size of flash supported (%d)"},
    {0x1004, "Command error, this device is in %x(0x0A is HS-FS, 0x03 is HS-KP, 0x00 and others is HS-SE), please make sure the device is in HS-FS for non-secure DFU."},
    {0x1005, "Error erasing flash via Fapi_issueBankEraseCommand(), please first make sure your SSU_Gen_Reg.bankmode is 0x03(mode 0) or 0x09(mode 2) and refer to fapi user's guide for the returned status."},
    {0x1006, "Flash state machine error encountered in Fapi_getFsmStatus(), refer to fapi user's guide for the returned status."},
    {0x1007, "Error during blank check, Fapi_doBlankCheck() failed"},
    {0x1008, "Error in setting flash api configs, Fapi_SetFlashCPUConfiguration() returned value of %d"},
    {0x1009, "Error programming flash, Fapi_issueAutoEcc512ProgrammingCommand() failed "},
    {0x100A, "Error in verify programmed value, Fapi_doVerify() failed "},
    {0x100B, "Bytes written (%d) in CopyApplication mismatches with the image size (%d) and something has gone wrong."},
    {0x100C, "Unable to clear flash state machine status, Fapi_issueAsyncCommand() failed"},
    {0x100D, "Error in initializing flash api, Fapi_initializeAPI() returned value of %d."},
    {0x100E, "Error in Bank Mode setting, Current bank mode is invalid."},

    {0x1101, "Command error, this device is in %x(0x0A is HS-FS, 0x00 is HS-SE), please make sure the device is in HS-KP or HS-SE for secure code provisioning."},
    {0x1102, "Command error, Invalid bankmode configuration for the selected CPU target, current bankmode is %x, please make sure your SSU_Gen_Reg.bankmode is in 0x09(mode2) for CPU3."},
    {0x1103, "Error in Sec Cfg image validation, the image size certificate metadata mismatches with the expected size of a sec cfg image."},
    {0x1104, "Load HSM runtime error, HsmClient_loadHSMRtFirmware() returned an error. If HSM runtime has already been loaded, please perform a PORSn power-on reset." },
    {0x1105, "Load HSM runtime error, HsmClient_waitForBootNotify() returned an error. Please double check X.509 certificate of the incoming HSMRt firmware and make sure it has the correct private key." },
    {0x1106, "HSM Key Writer error, HsmClient_keyWriter() returned an error. Please check the DebugP_log on what error messages the key writer produces." },
    {0x1107, "HSM Runtime has yet to be loaded, please load a HSM RT image first before proceeding with this step. If a custom runtime image is used, please make sure READ_BOOT_NOTIFY_REG gets correctly populated to indiciate a successful HSMRt load."},

    {0x1201, "Code Provisioning error, HsmClient_firmwareUpdate_CertProcess() returned an error and is unable to verify the certificate. Please double check X.509 certificate of the incoming firmware and make sure it has the correct private key." },
    {0x1202, "Code Provisioning error, HsmClient_firmwareUpdate_CodeProgram() returned an error." },
    {0x1203, "Code Provisioning error, HsmClient_firmwareUpdate_CodeVerify() returned an error. Final verification and integrity checks has failed for the incoming firmware." },
    {0x1204, "SEC CFG image check failed, the incoming image size does not match the expected size. Please double check your SEC CFG generation. Image size: %d, expected size: %d."},

    /* 2xxx reserved for ram-based uart sbl */
    {0x2001, "Command error, Invalid bankmode configuration for the selected CPU target, current bankmode is %x, Ram-based SBL DFU CPU3 only supports SSU_Gen_Reg.bankmode in mode 2. (0x03-mode 0, 0x06-mode 1, 0x09-mode 2, 0x0C-mode3)" },
    {0x2002, "Error, UART Channel overfilled error, please make sure no breakpoints or interruptions in receiving the data."},

    /* 3xxx reserved for flash-based sbl */
    {0x3001, "Command error, Invalid bankmode configuration for the selected CPU target, current bankmode is %x, please make sure your SSU_Gen_Reg.bankmode is in 0x07/0x0c(mode1/3) for CPU1."},
    {0x3002, "Command error, Invalid bankmode configuration for the selected CPU target, current bankmode is %x, please make sure your SSU_Gen_Reg.bankmode is in 0x0c(mode3) for CPU3."},
};

extern "C" {
#endif /* __cplusplus */

    //
    // Enables validation on the packet checksum field
    //
#define ENABLE_CHECKSUM_VALIDATION      1

//
// Packet metadata definitions
// 
#define PACKET_ACK                             0x2D
#define PACKET_NAK                             0xA5
#define PACKET_END_HANDSHAKE                   0x00
#define PACKET_HEADER				           0x1B
#define PACKET_FOOTER				           0xB1
#define PACKET_HEADER_BYTE                     1U
#define PACKET_PLSIZE_BYTE                     2U
#define PACKET_CHECKSUM_BYTE                   2U
#define PACKET_FOOTER_BYTE                     1U

//
// CommandResponsePkt_t Command Options
// (Do not use 0x0000)
// 
/* Non-secure HS-FS commands */
#define COMMAND_DFU_CPU1                    0x1001
#define COMMAND_DFU_CPU3                    0x1002
#define COMMAND_LFU_CPU1                    0x1003
/* Secure HS-KP & HS-SE commands */
#define COMMAND_HSM_RT_IMAGE                0x2001
#define COMMAND_HSM_KEYS                    0x2002
#define COMMAND_SEC_CFG_IMAGE               0x2003
#define COMMAND_HSM_CP_FLASH_IMAGE          0x2004
#define COMMAND_CPU1_CP_FLASH_IMAGE         0x2005
#define COMMAND_CPU3_CP_FLASH_IMAGE         0x2006
/* Utility commands */
#define COMMAND_SYNC_STATUS					0x3001
#define COMMAND_RUN_CPU1                    0x3002
#define COMMAND_RUN_CPU3                    0x3003
#define COMMAND_RESET_CPU1                  0x3004
/* Bank management commands */
#define COMMAND_BANK_MODE_0                 0x4000
#define COMMAND_BANK_MODE_1                 0x4001
#define COMMAND_BANK_MODE_2                 0x4002
#define COMMAND_BANK_MODE_3                 0x4003
/* Erase commands */
#define COMMAND_ERASE_MAIN_CPU1             0x5001
#define COMMAND_ERASE_MAIN_CPU3             0x5002
#define COMMAND_ERASE_BANKMGMT_CPU1         0x5003
#define COMMAND_ERASE_BANKMGMT_CPU3         0x5004
#define COMMAND_ERASE_SECCFG_CPU1           0x5005
#define COMMAND_ERASE_SECCFG_CPU3           0x5006
/* Set commands */
#define COMMAND_SET_APP_LOAD_ADDRESS        0x6001
#define COMMAND_SET_APP_ENTRY_ADDRESS       0x6002
#define COMMAND_SET_APP_SIZE                0x6003
/* Get commands */
#define COMMAND_GET_SOCID                   0x7001
#define COMMAND_GET_BROMSTATUS              0x7002
#define COMMAND_GET_ALT_UART_BAUD           0x7010

#define COMMAND_NOT_RECOGNIZED              0xFFFF

//
// FlashStatusPkt_t flashAPIError options
//
#define FLASH_NO_ERROR					           0x1000
#define FLASH_BLANK_ERROR					       0x2000
#define FLASH_VERIFY_ERROR						   0x3000
#define FLASH_PROGRAM_ERROR						   0x4000
#define FLASH_COMMAND_ERROR						   0x5000
#define FLASH_UNLOCK_ERROR						   0x6000
#define FLASH_AUTHENTICATION_ERROR                 0x7000
#define FLASH_ERASE_ERROR                          0x8000

#ifdef __cplusplus
}
#endif

#endif /* PACKET_COMM_PROTOCOL_H */