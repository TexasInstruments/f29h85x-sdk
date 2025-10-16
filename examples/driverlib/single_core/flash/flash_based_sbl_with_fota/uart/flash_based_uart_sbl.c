//###########################################################################
//
// FILE:    flash_based_uart_sbl.c
//
// TITLE:   CPU SBL main function
// <h1> CPU SBL main function </h1>
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

#include "flash_based_uart_sbl.h"
#include "ti_drivers_config.h"
//
// Globals
//
extern HsmClient_t gHSMClient;
extern COPY_TABLE fapiCopyTable;
extern const uint32_t app1EntryAddr; // Cpu1 application firmware entry address specfied by linker

__attribute__((retain, section("cpu1app")))
const uint8_t cpu1appData[] = 
{
    //
    // ONLY for obtaining the size of cpu1app in the program header of the generated .out
    // actual content will be inserted in post-build step
    //
    #embed "../../cpu1_firmware.bin" 
};

uint32_t AltBaudRate = SBL_COMA_BAUDRATE;
uint32_t bootCPU1Flag = 0;
bool isApp1Loaded = false;

/**
 * main.c
 */
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // DPL driver init
    //
    Dpl_init();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    ENINT;
    Interrupt_enableGlobal();

    //
    // Local variables
    //
    uint8_t  deviceState;
    uint32_t status;

#ifdef SECURE_CP
    //
    // First, need to determine if device is HS-FS or HS-SE
    //
    deviceState = getDeviceState();

    //
    // Verify the HSMRt is running on the HSM
    //
    if (deviceState == HS_SE) 
    {
        status = Hsmclient_loadHSMRtFirmware(&gHSMClient, (uint8_t*) HSM_FLASH_START_ADDRESS);
        DebugP_assert(SystemP_SUCCESS == status);
        
        //
        // Synchornization mechanism to prevent C29 CPU requests before HSMRt begins
        //
        if (SystemP_SUCCESS == status)
        {
            status = HsmClient_waitForBootNotify(NULL, 0U);
            Dpl_deinit();
        }
        
        //
        // Initialize DPL, SIPC interrupts, and HSM Client
        //
        KernelSystem_init();
    }
#endif /* SECURE_CP */

#ifdef NONSECURE
    //
    // Load Flash API libraries at code start
    // (Using copy table with LZSS compression to save memory space)
    copy_in(&fapiCopyTable);
#endif /* NONSECURE */

#ifdef NONSECURE
    //
    // Invalid firmware if bank mode doesn't match, with an exception of when previousBankMode data is uninitalized indicating SBL + firmware is loaded for the first time
    // Implemented for HS-FS only at the moment
    //
    bool isInvalidFirmware = (getPreviousBankMode() != 0xFFFFFFFF && getBankMode() != getPreviousBankMode()) ? true : false;

    //
    // Unless the need to wait for firmware indefinitely, boot the firmware
    //
    if (!isInvalidFirmware) 
    {
        bootCPU1Firmware();
    }
#else
    bootCPU1Firmware();
#endif /* NONSECURE */

    sblRoutine();

	return(0);
}

//
// sblRoutine that serves as an entry point for both normal operation and fail-safe (example_error)
//
void sblRoutine()
{
    while(1)
    {
        //
        // enact user command via jump table
        //
        commandJumpTable();

        //
        // If recvd run CPU1 command, boot the CPU1 firmware.
        //
        if (bootCPU1Flag) 
        {
            bootCPU1Flag = 0;
            bootCPU1Firmware();
        } 
    }
}

//
// Command parser function that serves as an entry point into this SBL from the application.
//
__attribute__((retain,c29_protected_call,section("command_table")))
void commandJumpTable(void) 
{   
    //
    // local variables
    //
    uint16_t command, length;
    char data[20];  // Set higher buffer if CommandPkt_t.addlContentLength is larger than 20
    CommandPkt_t cmdPkt = 
    {
        .payloadType = Command,
        .command = 0U,
        .addlContentLength = 0U, 
        .addlContentAddr = data 
    };

    //
    // Reset Uart packet interface FSM
    //
    sblResetInterface();

    //
    // get user command through console.
    //
    sblGetCommandPacket(&cmdPkt);

    command = cmdPkt.command;
    length = cmdPkt.addlContentLength;

    switch (command) 
    {
// HS-FS only
#ifdef NONSECURE
        case COMMAND_DFU_CPU1:
            cpu1FOTAFlow();
            break;
        case COMMAND_DFU_CPU3:
            cpu3FOTAFlow();
            break;
#endif /* NONSECURE */

// HS-SE only
#ifdef SECURE_CP
        case COMMAND_HSM_CP_FLASH_IMAGE:
        case COMMAND_CPU1_CP_FLASH_IMAGE:
        case COMMAND_CPU3_CP_FLASH_IMAGE:
            secureCodeProvisionFlow(command);
            break;
        case COMMAND_SEC_CFG_IMAGE:
            programSecCfgFlow();
            break;
#endif /* SECURE_CP */
        case COMMAND_SYNC_STATUS:
            {
                CommandResponsePkt_t cmdResponse;
                MessagePkt_t msgPkt;
                int strlen;

                cmdResponse = (CommandResponsePkt_t)
                {
                    .payloadType = (PayloadType)CommandResponse,
                    .echoCommand = command,
                    .expectsData = false,
                    .timeDelay_ms = 0U,                 // Irrelvant
                    .maxPayloadSize = 0U,               // Irrelvant
                    .expectsEOTpacket = true,           // SBL will send packet at EOT
                    .reserved = 0U
                };
                sblSendPacket(1, &cmdResponse);
                
                char ch[] = "Flash-based UART SBL is live and CPU1 firmware is loaded!";
                if (isApp1Loaded)
                {
                    strlen = sizeof(ch);
                }
                else
                {
                    strlen = sizeof("Flash-based UART SBL is live");
                }

                msgPkt = (MessagePkt_t)
                {
                    .payloadType = (PayloadType)Message,
                    .length = strlen,
                    .msgAddr = ch
                };

                // Send EOT packet
                sblSendPacket(1, &msgPkt);
            }
            break;
        case COMMAND_RESET_CPU1:
            {
                CommandResponsePkt_t cmdResponse;

                cmdResponse = (CommandResponsePkt_t)
                {
                    .payloadType = (PayloadType)CommandResponse,
                    .echoCommand = command,
                    .expectsData = false,
                    .timeDelay_ms = 0U,                 // Irrelvant
                    .maxPayloadSize = 0U,               // Irrelvant
                    .expectsEOTpacket =  false,         // SBL will not send packet at EOT
                    .reserved = 0U
                };
                sblSendPacket(1, &cmdResponse);
                
                //
                // Enable WD and let it reset device
                //
                SysCtl_setWatchdogMode(SYSCTL_WD_MODE_RESET);
                SysCtl_enableWatchdog();
            }
            
            break;
        case COMMAND_RUN_CPU1:
            {
                CommandResponsePkt_t cmdResponse;

                cmdResponse = (CommandResponsePkt_t)
                {
                    .payloadType = (PayloadType)CommandResponse,
                    .echoCommand = command,
                    .expectsData = false,
                    .timeDelay_ms = 0U,                 // Irrelvant
                    .maxPayloadSize = 0U,               // Irrelvant
                    .expectsEOTpacket = false,          // SBL will not send packet at EOT
                    .reserved = 0U
                };
                sblSendPacket(1, &cmdResponse);
                
                // Set boot flag to boot CPU1 firmware once exit
                bootCPU1Flag = 1;
            }
            break;
        case COMMAND_RUN_CPU3:
            runCPU3();
            break;
        case COMMAND_GET_SOCID:
            sendSOCIDFlow();
            break;
        case COMMAND_GET_BROMSTATUS:
            sendBromStatusFlow();
            break;
        case COMMAND_GET_ALT_UART_BAUD:
            {   
                CommandResponsePkt_t cmdResponse;
                MessagePkt_t msgPkt;

                cmdResponse = (CommandResponsePkt_t)
                {
                    .payloadType = (PayloadType)CommandResponse,
                    .echoCommand = command,
                    .expectsData = false,
                    .timeDelay_ms = 0U,                 // Irrelvant
                    .maxPayloadSize = 0U,               // Irrelvant
                    .expectsEOTpacket = true,           // sbl will send packet at EOT
                    .reserved = 0U
                };
                // F29H85x supports up to 12M baud, but bottlenecks after ~2-3M baud
                const uint32_t maxDeviceSupportBaud = 12000000U;
                const uint32_t altDefaultBaudRate = 2304000U; 

                uint32_t sendBuf[2] = {altDefaultBaudRate, maxDeviceSupportBaud}; // Current proposed baud rate, max supported baud rate

                // If host send a suggestive baud rate, try to comply with the proposed rate
                if (length != 0)
                {
                    uint32_t hostProposedBaud = BYTES_TO_UINT32(data);
                    // Cap at the max supported baudrate of the device
                    if (hostProposedBaud != 0 && hostProposedBaud <= maxDeviceSupportBaud)
                    {
                        sendBuf[0] = hostProposedBaud;
                    }
                    else
                    {   
                        sendBuf[0] = maxDeviceSupportBaud;
                    }
                }
                AltBaudRate = sendBuf[0];

                CommandPkt_t baudRatePkt = 
                {
                    .payloadType = (PayloadType)Command,
                    .command = 0U,
                    .addlContentLength = sizeof(sendBuf),
                    .addlContentAddr = (void*)&sendBuf
                };
                sblSendPacket(2, &cmdResponse, &baudRatePkt);

                uint32_t currBaud, uartConfig;
                UART_getConfig(SBL_COMA_BASE, DEVICE_SYSCLK_FREQ, &currBaud, &uartConfig);
        
                if (currBaud != AltBaudRate)
                {
                    UART_setConfig(
                    SBL_COMA_BASE,              // Sysconfig defined variable
                    DEVICE_SYSCLK_FREQ,      // UART source clock
                    sendBuf[0],                 // new baud rate
                    uartConfig                // word length + stop bits + parity bit config
                    );
                
                    // Wait for a few just in case
                    DEVICE_DELAY_US(100U);
                }

                char ch[] = "UART SBL has changed baudrate!";
                msgPkt = (MessagePkt_t)
                {
                    .payloadType = (PayloadType)Message,
                    .length = sizeof(ch),
                    .msgAddr = ch
                };
                //
                // Send EOT packet
                //
                sblSendPacket(1, &msgPkt);
            }
            break;
        case COMMAND_BANK_MODE_0:
        case COMMAND_BANK_MODE_1:
        case COMMAND_BANK_MODE_2:
        case COMMAND_BANK_MODE_3:
#ifdef NONSECURE
            Fapi_initializeAPI((Fapi_FmcRegistersType*)FLASHCONTROLLER1_BASE,
                                DEVICE_SYSCLK_FREQ / 1000000U);
            // bankmode should be set first before any programming as bank modes changes won't gurantee data integrity on the existing banks.
            // bankmode options is only included in flash sbl for development purpose, it should be REMOVED for production.
            programBankmodeFlow(command);
            break;
#endif /* ifdef NONSECURE */
        case COMMAND_NOT_RECOGNIZED:
        default:
            {
                CommandResponsePkt_t cmdResponse;

                cmdResponse = (CommandResponsePkt_t)
                {
                    .payloadType = (PayloadType)CommandResponse,
                    .echoCommand = COMMAND_NOT_RECOGNIZED, // Unrecognized command
                    .expectsData = false,
                    .timeDelay_ms = 0U,                 // Irrelvant
                    .maxPayloadSize = 0U,               // Irrelvant
                    .expectsEOTpacket = false,          // SBL will not send packet at EOT
                    .reserved = 0U
                };
                sblSendPacket(1, &cmdResponse);
            }
            break;
    }

    return;
}

//
// Call CPU1 entry address
//
void bootCPU1Firmware()
{
    isApp1Loaded = true;

    // Similar to long branch asm("LB @(app1EntryAddr)");
    ((void (*)(void)) &app1EntryAddr)();
}


