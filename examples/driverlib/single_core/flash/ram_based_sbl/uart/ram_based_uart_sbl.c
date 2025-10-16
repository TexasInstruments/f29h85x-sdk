//###########################################################################
//
// FILE:    ram_based_uart_sbl.c
//
// TITLE:   RAM-based UART SBL (formerly UART flash kernel) main function
// <h1> RAM-based UART SBL (formerly UART flash kernel) main function </h1>
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

#include "ram_based_uart_sbl.h"

//
// Globals
//
extern COPY_TABLE fapiCopyTable;

uint32_t LoadAddr; // Not used by host & sbl, reserved for future impl
uint32_t EntryAddr = CPU1_FLASH_ENTRY_POINT;
uint32_t currBaudRate = SBL_COMA_BAUDRATE;
uint32_t bootCPU1Flag = 0;

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
    // Board initialization
    //
    Board_init();

    //
    // If in peripherial boot and RAMOPEN mode enabled, set Link and Stack of interrupts to 1
    // RAMOPEN is only applicable to HS-FS via peripherial boot
    //
    if (SSU_getRAMOPENStatus())
    {
        Interrupt_setLinkOwner(INT_UARTA, DPL_RAMOPEN_LINK);
        Interrupt_setLinkOwner(SBL_dataMode_DMA_INT, DPL_RAMOPEN_LINK);
        Interrupt_configNMI(&kernelInterrupt_NMIHandler, DPL_RAMOPEN_LINK);
        Interrupt_setINTSP(DPL_RAMOPEN_STACK);
    }
    else 
    {
        // Everything else defaults to Link and Stack 2
        Interrupt_configNMI(&kernelInterrupt_NMIHandler, DPL_NORMAL_LINK);
        Interrupt_setINTSP(DPL_NORMAL_STACK);
    }

#ifdef SECURE_CP // CP: HS_KP -> HS_SE
    // Check if device is in HS-KP state
    if(HS_KP == getDeviceState())
    {
        //
        // Disable flash erase and write protection to enable 
        // code provisioning for C29 CPU in HS-KP state.
        // C29 CPU does not have flash read/write access in HS-KP state,
        // hence the SSU registers are held in reset value during this 
        // lifecycle as C29 ROM is unable to configure these registers
        //
        enableFlashEraseAndWrite();
    }
#endif /* SECURE_CP */

#ifdef NONSECURE_DFU // HS-FS only
    //
    // Configure flash settings to improve flash execution performance
    // 
    Flash_initModule(DEVICE_FLASH_WAITSTATES);

    //
    // Load Flash API libraries at code start
    // (Using copy table with LZSS compression to save memory space)
    copy_in(&fapiCopyTable);
#endif /* NONSECURE_DFU */

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Run main sbl routine
    //
    sblRoutine();
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
            
            //
            // Branch to application entrypoint
            //
            ((void (*)(void)) EntryAddr)();
        } 
    }

}

//
// Command parser function that enacts user command
//
void commandJumpTable(void)
{   
    //
    // local variables
    //
    uint16_t command, length;
    char    addlData[20];  // Set higher buffer if CommandPkt_t.addlContentLength is larger than 20
    CommandPkt_t cmdPkt = 
    {
        .payloadType = Command,
        .command = 0U,
        .addlContentLength = 0U, 
        .addlContentAddr = addlData 
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
#ifdef NONSECURE_DFU 
        case COMMAND_DFU_CPU1:
            cpu1DFUFlow();
            break;
        case COMMAND_DFU_CPU3:
            cpu3DFUFlow();
            break;
#endif /* NONSECURE_DFU */

// HS-FS -> HS-KP
#ifdef SECURE_KP 
        case COMMAND_HSM_KEYS:
            loadKeyFlow();
            break;
#endif /* SECURE_KP */

// HS-KP -> HS-SE
#ifdef SECURE_CP 
        case COMMAND_SEC_CFG_IMAGE:
            programSecCfgFlow();
            break;
        // Load CPU1/3/HSM Code Provisioning Flash Image
        case COMMAND_HSM_CP_FLASH_IMAGE: 
        case COMMAND_CPU1_CP_FLASH_IMAGE:
        case COMMAND_CPU3_CP_FLASH_IMAGE:
            secureCodeProvisionFlow(command);
            break;
#endif /* SECURE_CP */

#if defined(SECURE_KP) || defined(SECURE_CP)
        // Load Ram-based HSMRt image
        case COMMAND_HSM_RT_IMAGE: 
            loadRamHSMRtFlow();
            break;
#endif /* defined (SECURE_KP) || defined (SECURE_CP) */
        case COMMAND_SYNC_STATUS: 
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
                sblSendPacket(1, &cmdResponse);

                char ch[] = "RAM-based UART SBL is live!";
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
                    .expectsEOTpacket =  false,         // sbl will not send packet at EOT
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
        // Run C29 CPU1 Flash Application
        case COMMAND_RUN_CPU1: 
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
                    .expectsEOTpacket = false,          // sbl will not send packet at EOT
                    .reserved = 0U
                };
                
                // In RAMOPEN Mode, bootloader can't execute in Flash (RAM-only)
                if (SSU_getRAMOPENStatus())
                {
                    char ch[] = "Skipped. RAMOPEN is enforced and restricts bootloader to run from flash. Do Reset CPU1 in flash boot mode instead.";
                    
                    // Send message along with cmdresponse and don't do anything
                    msgPkt = (MessagePkt_t)
                    {
                        .payloadType = (PayloadType)Message,
                        .length = sizeof(ch),
                        .msgAddr = ch
                    };
                    sblSendPacket(2, &cmdResponse, &msgPkt);
                }
                else
                {
                    sblSendPacket(1, &cmdResponse);

                    // Enable branch to entry point once exit
                    bootCPU1Flag = 1;
                }
            }
            break;
        // Run C29 CPU3 Flash Application
        case COMMAND_RUN_CPU3: 
            runCPU3();
            break;
        // Set C29 alternate Flash Application Entry Address
        case COMMAND_SET_APP_ENTRY_ADDRESS: 
            {
                CommandResponsePkt_t cmdResponse;

                cmdResponse = (CommandResponsePkt_t)
                {
                    .payloadType = (PayloadType)CommandResponse,
                    .echoCommand = command,
                    .expectsData = false,
                    .timeDelay_ms = 0U,                 // Irrelvant
                    .maxPayloadSize = 0U,               // Irrelvant
                    .expectsEOTpacket = false,          // sbl will not send packet at EOT
                    .reserved = 0U
                };
                sblSendPacket(1, &cmdResponse);

                //
                // Selects which bank the CPU chooses to erase
                //
                EntryAddr = BYTES_TO_UINT32(addlData);
            }
            break;
        // Set C29 alternate Flash Application Load Address
        case COMMAND_SET_APP_LOAD_ADDRESS: 
            {
                CommandResponsePkt_t cmdResponse;

                cmdResponse = (CommandResponsePkt_t)
                {
                    .payloadType = (PayloadType)CommandResponse,
                    .echoCommand = command,
                    .expectsData = false,
                    .timeDelay_ms = 0U,                 // Irrelvant
                    .maxPayloadSize = 0U,               // Irrelvant
                    .expectsEOTpacket =  false,          // sbl will not send packet at EOT
                    .reserved = 0U
                };
                sblSendPacket(1, &cmdResponse);

                LoadAddr = BYTES_TO_UINT32(addlData);
            }
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
                    uint32_t hostProposedBaud = BYTES_TO_UINT32(addlData);
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
        
                if (currBaud != sendBuf[0])
                {
                    currBaudRate = sendBuf[0];
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
#if defined(NONSECURE_DFU) || defined(SECURE_KP) // Only available to HS-FS atm
            // For KP, Fapi needs to be first loaded manually 
            // Since Fapi is sharing the same LDA1 space as KP scratchpad
            copy_in(&fapiCopyTable);
            Fapi_initializeAPI((Fapi_FmcRegistersType*)FLASHCONTROLLER1_BASE,
                                DEVICE_SYSCLK_FREQ / 1000000U);
            programBankmodeFlow(command);
            break;
#endif /* ifndef NONSECURE_DFU */
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