// ###########################################################################
//
//  FILE:    sbl_command_flow.h
//
//  TITLE:   SBL's top-level command execution flow
//  <h1> CPU SBL's top-level command execution flow</h1>
//
// ###########################################################################
//  $TI Release:  $
//  $Release Date:  $
//  //
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

// ###########################################################################

#include "sbl_command_flow.h"

extern HsmClient_t gHSMClient;

/* Cache Aligned Objects which will be passed to and from HSM & C29 (Even though M4 does not do any cacheline alignment) */
/* This struct needs to be placed in a hsm_accessible region as it will be passed to the hsm to fill out version info */
HsmVer_t hsmVer __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT),section("hsm_accessible")));

//
// Function that firmware will branch to when DFU CPU1 command received from firmware
// Note: DFU vs FOTA, DFU programs to the active banks directly (No A/B swapping) whereas FOTA programs dormant banks (w A/B swapping)
//
void cpu1DFUFlow(void)
{
    //
    // Initialize locals
    //
    uint8_t  bankMode;
    uint8_t  deviceState;
    CommandResponsePkt_t cmdResponse;
    MessagePkt_t msgPkt;

    //
    // Get device state and bank mode
    //
    deviceState = getDeviceState();
    bankMode = getBankMode();

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = COMMAND_DFU_CPU1,
        .expectsData = true, 
        .timeDelay_ms = 0U,                 // Time delay for flash api & ssu init
        .maxPayloadSize = MAX_PAYLOAD_SIZE, // Pre-allocated fixed data buffer
        .expectsEOTpacket = true,           // sbl will send packet at EOT
        .reserved = 0U
    };
    sblSendPacket(1, &cmdResponse);
    
    //
    // DFU is not compatible with HS-KP/HS-SE Devices 
    //
    if (deviceState != HS_FS) 
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1004,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = (uint32_t*)&deviceState                      
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        return ;
    } 
    
    sblStartDataMode();
    
    //
    // loads application into CPU1 FLASH
    //
    programDFU(1, bankMode);

    // Must end data mode first before preceding
    sblEndDataMode();

    char ch[] = "CPU1 image has been written to flash, please proceed to Run CPU1 or Reset CPU1(in flash boot mode) to start the new firmware.";
    msgPkt = (MessagePkt_t)
    {
        .payloadType = (PayloadType)Message,
        .length = sizeof(ch),
        .msgAddr = ch
    };

    //
    // send the packet with flash status and message at EOT
    //
    sblSendPacket(1, &msgPkt);
}

//
// Function that firmware will branch to when DFU CPU3 command received from firmware
// Note: DFU vs FOTA, DFU programs to the active banks directly (No A/B swapping) whereas FOTA programs dormant banks (w A/B swapping)
//
void cpu3DFUFlow(void)
{
    //
    // Initialize locals
    //
    uint8_t  bankMode;
    uint8_t  deviceState;
    CommandResponsePkt_t cmdResponse;
    MessagePkt_t msgPkt;

    //
    // Get device state and bank mode
    //
    deviceState = getDeviceState();
    bankMode = getBankMode();

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = COMMAND_DFU_CPU3,
        .expectsData = true, 
        .timeDelay_ms = 0U,               // Time delay for flash api & ssu init
        .maxPayloadSize = MAX_PAYLOAD_SIZE, // Pre-allocated fixed data buffer
        .expectsEOTpacket = true,           // sbl will send packet at EOT
        .reserved = 0U
    };
    sblSendPacket(1, &cmdResponse);
    
    //
    // DFU is not compatible with HS-KP/SE Devices 
    //
    if (deviceState != HS_FS) 
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1004,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = (uint32_t*)&deviceState                      
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        return ;
    }

    //
    // cannot upgrade CPU3 firmware in Bank Mode 0/1
    //
    if (bankMode != FLASH_BANK_MODE_2 && bankMode != FLASH_BANK_MODE_3)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x2001,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = (uint32_t*)&deviceState                      
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        return ;
    }

    sblStartDataMode();

    //
    // loads application into CPU1 FLASH
    //
    programDFU(3, bankMode);

    // Must end data mode first before preceding
    sblEndDataMode();

    char ch[] = "CPU3 image has been written to flash. In order to start the new CPU3 firmware, please proceed to Run CPU3 or Reset CPU1(in flash mode) and have CPU1 flash application boot CPU3 (For an reference routine, see RUN_CPU3 implementation of uartGetFunction() in the flash sbl).";
    msgPkt = (MessagePkt_t)
    {
        .payloadType = (PayloadType)Message,
        .length = sizeof(ch),
        .msgAddr = ch
    };

    //
    // send the packet with flash status and message at EOT
    //
    sblSendPacket(1, &msgPkt);
}

//
// Function that firmware will branch to load Keys (Key-provision)
//
void loadKeyFlow()
{
    //
    // Initialize locals
    //
    CommandResponsePkt_t cmdResponse;
    MessagePkt_t msgPkt;

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = COMMAND_HSM_KEYS,
        .expectsData = true, 
        .timeDelay_ms = 0U,
        .maxPayloadSize = MAX_PAYLOAD_SIZE, // Pre-allocated fixed data buffer
        .expectsEOTpacket = true,           // sbl will send packet at EOT
        .reserved = 0U
    };
    sblSendPacket(1, &cmdResponse);

    sblStartDataMode();

    if (0U != provisionKeys(LDA1_RAM_BASE))
    {
        // Error occurred to send message twice.
    }
    
    // Must end data mode first before preceding
    sblEndDataMode();

    msgPkt = (MessagePkt_t)
    {
        .payloadType = (PayloadType)Message,
        .length = MAX_KP_LOG_SIZE,
        .msgAddr = (char*)KP_LOG_ADDR
    };
    //
    // send the packet with flash status and message at EOT
    //
    sblSendPacket(1, &msgPkt);
}

void loadRamHSMRtFlow()
{
    //
    // Initialize locals
    //
    CommandResponsePkt_t cmdResponse;
    MessagePkt_t msgPkt;

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = COMMAND_HSM_RT_IMAGE,
        .expectsData = true, 
        .timeDelay_ms = 0U,
        .maxPayloadSize = MAX_PAYLOAD_SIZE, // Pre-allocated fixed data buffer
        .expectsEOTpacket = true,           // sbl will send packet at EOT
        .reserved = 0U
    };
    sblSendPacket(1, &cmdResponse);

    uint32_t bootNotifyStatus = HWREG(READ_BOOT_NOTIFY_REG);
    if (bootNotifyStatus == BOOT_NOTIFY_DONE_STATUS)
    {
        char ch[] = "HSM Runtime has already been loaded, please proceed with subsequent steps or perform a PORSn reset to load a different HSM RT image";
        msgPkt = (MessagePkt_t)
        {
            .payloadType = (PayloadType)Message,
            .length = sizeof(ch),
            .msgAddr = ch
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &msgPkt);
        return ;
    }

    sblStartDataMode();
    
    if (loadHSMRT(LDA7_RAM_BASE) != SystemP_SUCCESS)
    {
        char ch[] = "HSM Run Time failed to authenticate.";
        msgPkt = (MessagePkt_t)
        {
            .payloadType = (PayloadType)Message,
            .length = sizeof(ch),
            .msgAddr = ch
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &msgPkt);
        return ;
    }

    // Must end data mode first before preceding
    sblEndDataMode();

    KernelSystem_init();

    char parsedVer[PARSED_VERSION_SIZE];
    memset(parsedVer, '\0', PARSED_VERSION_SIZE);
    
    if (!HsmClient_getVersion(&gHSMClient, &hsmVer, ClockP_usecToTicks(1000U)))
    {
        if (!HsmClient_parseVersion(&hsmVer, parsedVer))
        {
            msgPkt = (MessagePkt_t)
            {
                .payloadType = (PayloadType)Message,
                .length = PARSED_VERSION_SIZE,
                .msgAddr = (char*)parsedVer
            };
            // Sends EOT packet
            sblSendPacket(1, &msgPkt);
        }
    }
    else
    {
        char ch[] = "!! FAILED INSTALLATION OF KW !!";
        msgPkt = (MessagePkt_t)
        {
            .payloadType = (PayloadType)Message,
            .length = sizeof(ch),
            .msgAddr = ch
        };
        // Sends EOT packet
        sblSendPacket(1, &msgPkt);
    }
}

//
// Function that firmware will branch to when CP command received
//
void secureCodeProvisionFlow(uint16_t command) 
{
    //
    // Initialize locals
    //
    uint8_t  bankMode;
    uint8_t  deviceState;
    CommandResponsePkt_t cmdResponse;
    MessagePkt_t msgPkt;

    //
    // Get device state and bank mode
    //
    deviceState = getDeviceState();
    bankMode = getBankMode();

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = command,
        .expectsData = true, 
        .timeDelay_ms = 0U,
        .maxPayloadSize = MAX_PAYLOAD_SIZE, // Pre-allocated fixed data buffer
        .expectsEOTpacket = true,           // SBL will send packet at EOT
        .reserved = 0U
    };
    sblSendPacket(1, &cmdResponse);

    //
    // Set error if CP command is sent for HS-FS device
    //
    if (deviceState == HS_FS) 
    {   
        const ErrorStatusPkt_t errPkt = 
        {
        .payloadType = (PayloadType)ErrorStatus,
        .errorMsgCode = 0x1101,              // error message decoded in comm_packet_protocol.h
        .recoveryStatus = RS_NormalOperation,  
        .hasSprintfArgs = true,             
        .numArgs = 1U,                       
        .pArgsVal = (uint32_t*)&deviceState                      
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        return;
    }

    //
    // Set error if invalid bank mode and CPU target are selected
    //
    if (command == COMMAND_CPU3_CP_FLASH_IMAGE && (command == FLASH_BANK_MODE_0 || command == FLASH_BANK_MODE_1))
    {   
        const ErrorStatusPkt_t errPkt = 
        {
        .payloadType = (PayloadType)ErrorStatus,
        .errorMsgCode = 0x1102,                   // error message decoded in comm_packet_protocol.h
        .recoveryStatus = RS_NormalOperation,  
        .hasSprintfArgs = true,             
        .numArgs = 1U,                       
        .pArgsVal = (uint32_t*)&bankMode                      
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        return;
    }
    //
    // Set error message inquiry if HSM runtime has not been loaded.
    //
    uint32_t bootNotifyStatus = HWREG(READ_BOOT_NOTIFY_REG);
    if (BOOT_NOTIFY_DONE_STATUS != bootNotifyStatus)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1107,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        return;
    }

    // Start data transfer
    sblStartDataMode();

    provisionApplicationImg(LDA1_RAM_BASE);

    // Must end data mode first before preceding
    sblEndDataMode();

    char hsm_msg[] = "HSM Flash Loading is successful.";
    char cpu_msg[] = "CPU APP Loading is successful.";
    if (command == COMMAND_HSM_CP_FLASH_IMAGE)
    {
        msgPkt = (MessagePkt_t)
        {
            .payloadType = (PayloadType)Message,
            .length = sizeof(hsm_msg),
            .msgAddr = hsm_msg
        };
    }
    else
    {
        msgPkt = (MessagePkt_t)
        {
            .payloadType = (PayloadType)Message,
            .length = sizeof(cpu_msg),
            .msgAddr = cpu_msg
        };
    }

    // send the packet with flash status and message at EOT
    sblSendPacket(1, &msgPkt);
}

//
// Function that firmware will branch to when SECCFG command received
//
void programSecCfgFlow()
{
    //
    // Initialize locals
    //
    uint8_t  deviceState;
    CommandResponsePkt_t cmdResponse;
    MessagePkt_t msgPkt;

    //
    // Get device state
    //
    deviceState = getDeviceState();

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = COMMAND_SEC_CFG_IMAGE,
        .expectsData = true, 
        .timeDelay_ms = 0U,
        .maxPayloadSize = MAX_PAYLOAD_SIZE, // Pre-allocated fixed data buffer
        .expectsEOTpacket = true,           // sbl will send packet at EOT
        .reserved = 0U
    };
    sblSendPacket(1, &cmdResponse);

    //
    // Set error if CP command is sent for HS-FS device
    //
    if (deviceState == HS_FS) 
    {   
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1101,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = true,             
            .numArgs = 1U,                       
            .pArgsVal = (uint32_t*)&deviceState                      
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        return ;
    }

    //
    // Set message inquiry if HSM runtime has not been loaded.
    //
    uint32_t bootNotifyStatus = HWREG(READ_BOOT_NOTIFY_REG);
    if (BOOT_NOTIFY_DONE_STATUS != bootNotifyStatus)
    {
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x1107,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_NormalOperation,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet and break out of routine
        //
        sblSendPacket(1, &errPkt);
        return ;
    }

    sblStartDataMode();
    //
    // Sec Cfg Program Logic
    //
    if (provisionSecCfgImg(LDA1_RAM_BASE))
    {
        char ch[] = "Sec Cfg imagine failed to authenticate. Please re-try again.";
        msgPkt = (MessagePkt_t)
        {
            .payloadType = (PayloadType)Message,
            .length = sizeof(ch),
            .msgAddr = ch
        };
        sblSendPacket(1, &msgPkt);
        return ;
    }
    // Must end data mode first before preceding
    sblEndDataMode();

    char ch[] = "SecCfg Loading is successful. If this is an upgrade from HS-KP to HS-SE, please perform a device reset to show effect (viewable via SoC ID).";
    msgPkt = (MessagePkt_t)
    {
        .payloadType = (PayloadType)Message,
        .length = sizeof(ch),
        .msgAddr = ch
    };
    //
    // send the packet with flash status and message at EOT
    //
    sblSendPacket(1, &msgPkt);
}

//
// Function to run CPU3
//
void runCPU3(void)
{
    CommandResponsePkt_t cmdResponse;

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = COMMAND_RUN_CPU3,
        .expectsData = false,
        .timeDelay_ms = 0U,                 // Irrelvant
        .maxPayloadSize = 0U,               // Irrelvant
        .expectsEOTpacket = false,          // sbl will not send packet at EOT
        .reserved = 0U
    };
    sblSendPacket(1, &cmdResponse);

    //
    // Defines the CPU3 RESET & NMI Vector to which CPU3 Boots
    //
    SSU_configBootAddress(SSU_CPU3, (uint32_t)CPU3_RESET_VECTOR, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU3, (uint32_t)CPU3_NMI_VECTOR, SSU_LINK2);

    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU3, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU3Reset() == 0x1U);
}


//
// Function to send SoCID
//
void sendSOCIDFlow(void)
{
    CommandResponsePkt_t cmdResponse;
    // Host side to override default commandPkt behavior
    CommandPkt_t socidPkt; 

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = COMMAND_GET_SOCID,
        .expectsData = false,
        .timeDelay_ms = 0U,                 // Irrelvant
        .maxPayloadSize = 0U,               // Irrelvant
        .expectsEOTpacket =  false,         // sbl will not send packet at EOT
        .reserved = 0U
    };
    
    socidPkt = (CommandPkt_t)
    {
        .payloadType = (PayloadType)Command,
        .command = 0U,
        .addlContentLength = sizeof(g_socId),
        .addlContentAddr = (void*)&g_socId
    };
    sblSendPacket(2, &cmdResponse, &socidPkt);
}

//
// Function to send BromStatus
//
void sendBromStatusFlow(void)
{
    CommandResponsePkt_t cmdResponse;
    // Host side to override default commandPkt behavior
    CommandPkt_t bromStsPkt; 

    cmdResponse = (CommandResponsePkt_t)
    {
        .payloadType = (PayloadType)CommandResponse,
        .echoCommand = COMMAND_GET_BROMSTATUS,
        .expectsData = false,
        .timeDelay_ms = 0U,                 // Irrelvant
        .maxPayloadSize = 0U,               // Irrelvant
        .expectsEOTpacket =  false,         // sbl will not send packet at EOT
        .reserved = 0U
    };

    // g_bootromStatus memory layout has some prohibited access region. Therefore use a local struct to access all atttributes.
    brom_status bromStat;
    
    bromStat.link0StartCycleCount = g_bootromStatus.link0StartCycleCount;
    bromStat.link0EndCycleCount = g_bootromStatus.link0EndCycleCount;
    bromStat.resetCnt = g_bootromStatus.resetCnt;
    bromStat.resetCause = g_bootromStatus.resetCause;
    bromStat.sysclk = g_bootromStatus.sysclk;
    //bromStat.eccErrAddrDR1 = g_bootromStatus.eccErrAddrDR1;
    //bromStat.eccErrAddrDR2 = g_bootromStatus.eccErrAddrDR2;
    bromStat.eccErrAddrDR1 = HWREG(ERRORAGGREGATOR_BASE + ERROR_AGGREGATOR_O_CPU1_DR1_HIGHPRIO_ERROR_ADDRESS);
    bromStat.eccErrAddrDR2 = HWREG(ERRORAGGREGATOR_BASE + ERROR_AGGREGATOR_O_CPU1_DR2_HIGHPRIO_ERROR_ADDRESS);
    bromStat.bootMode = g_bootromStatus.bootMode;
    bromStat.bootLoaderLock = g_bootromStatus.bootLoaderLock;
    bromStat.deviceLifeCycleState = g_bootromStatus.deviceLifeCycleState;
    bromStat.link0ErrId = g_bootromStatus.link0ErrId;
    bromStat.bromStatus = g_bootromStatus.bromStatus;
    bromStat.ssuStatus = g_bootromStatus.ssuStatus;
    bromStat.nmiStatus = g_bootromStatus.nmiStatus;

    bromStsPkt = (CommandPkt_t)
    {
        .payloadType = (PayloadType)Command,
        .command = 0U,
        .addlContentLength = sizeof(bromStat),
        .addlContentAddr = (void*)&bromStat
    };
    sblSendPacket(2, &cmdResponse, &bromStsPkt);
}

void programBankmodeFlow(uint16_t command)
{
    uint8_t  deviceState;
    uint8_t curBankMode, targetBankMode;
    uint32_t u32UserFlashConfig;
    CommandResponsePkt_t cmdResponse;
    MessagePkt_t msgPkt;
    char modeNum;
    
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

    deviceState = getDeviceState();
    curBankMode = getBankMode();

    //
    // Set error if device is not HS_FS (Fapi not applicable)
    //
    if (deviceState != HS_FS) 
    {   
        char ch[] = "Currently bank mode changes is only supported in HS-FS. Skipping.";
        msgPkt = (MessagePkt_t)
        {
            .payloadType = (PayloadType)Message,
            .length = sizeof(ch),
            .msgAddr = ch
        };
        sblSendPacket(1, &msgPkt);
        return ;
    }


    switch (command)
    {
        case COMMAND_BANK_MODE_0:
            targetBankMode = FLASH_BANK_MODE_0;
            modeNum = '0';
            break;
        case COMMAND_BANK_MODE_1:
            targetBankMode = FLASH_BANK_MODE_1;
            modeNum = '1';
            break;
        case COMMAND_BANK_MODE_2:
            targetBankMode = FLASH_BANK_MODE_2;
            modeNum = '2';
            break;
        case COMMAND_BANK_MODE_3:
        default:
            targetBankMode = FLASH_BANK_MODE_3;
            modeNum = '3';
            break;
    }

    if (targetBankMode == curBankMode)
    {
        char ch[] = "The current bank mode is already mode x.";
        ch[sizeof("The current bank mode is already mode ") - 1] = modeNum;
        msgPkt = (MessagePkt_t)
        {
            .payloadType = (PayloadType)Message,
            .length = sizeof(ch),
            .msgAddr = ch
        };
        //
        // send the packet with flash status and message at EOT
        //
        sblSendPacket(1, &msgPkt);
        return;
    }

    SSU_claimFlashSemaphore();

    // Set current bank mode to PROG_BANKMODE
    Fapi_SetFlashCPUConfiguration(curBankMode);

    switch (curBankMode)
    {
        // Current Bankmode 1 or 3
        case FLASH_BANK_MODE_1:
        case FLASH_BANK_MODE_3:
            u32UserFlashConfig = Fapi_getUserConfiguration((Fapi_FlashBankType)C29Bank, 
                                                            (Fapi_FOTAStatus)FOTA_Image);
            
            break;
        // Current Bankmode 0 or 2 or in-case if invalid, treat it as if mode 0
        case FLASH_BANK_MODE_INVALID:
        default:
            // Treat as if mode 0
            Fapi_SetFlashCPUConfiguration(Mode0);
        case FLASH_BANK_MODE_0:
        case FLASH_BANK_MODE_2:
            u32UserFlashConfig = Fapi_getUserConfiguration((Fapi_FlashBankType)C29Bank, 
                                                            (Fapi_FOTAStatus)Active_Bank);
            break;
    }

    // Bankmode only exists in CPU1 bank management (not in CPU3 bank management)
    ProgramInactiveBankManagement(0x1, targetBankMode, u32UserFlashConfig);

    SSU_releaseFlashSemaphore();

    // Device must be resetted for bootROM to remap the flash banks
    char ch[] = "Bankmode x has been successfully set, device now must reset (XRSn/PORSn) to take effect and prior to any subsequent programming operations. Note: Data integrity is not perserved when changing bank modes.";
    ch[sizeof("Bankmode ") - 1] = modeNum;
    msgPkt = (MessagePkt_t)
    {
        .payloadType = (PayloadType)Message,
        .length = sizeof(ch),
        .msgAddr = ch
    };
    //
    // send the packet with flash status and message at EOT
    //
    sblSendPacket(1, &msgPkt);

}