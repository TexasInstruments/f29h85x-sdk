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
#include "include/SoCIDParser.h"

//*****************************************************************************
//
// Globals whose values are set or overridden via command line parameters.
//
//*****************************************************************************
bool g_bShownHelp  = false;
bool g_bWaitOnExit = false;
bool g_bUsrCommand = false;
bool g_bBootOnly   = false;

//
// Supported device bool
//
bool g_bf29h85x = false;
bool g_bf29p58x = false;
bool g_bf29p32x = false;

//
// Parameter input variable
//
char* g_pszAppLoadAddress				= nullptr;
char* g_pszAppEntryAddress				= nullptr;
char* g_pszKernelFile					= nullptr;
char* g_pszCPU1AppFile					= nullptr;
char* g_pszCPU3AppFile					= nullptr;
char* g_pszSecCfgProgramFile			= nullptr;
char* g_pszHSMFlashCodeProvisionFile	= nullptr;
char* g_pszCPU1FlashCodeProvisionFile	= nullptr;
char* g_pszCPU3FlashCodeProvisionFile	= nullptr;
char* g_pszHSMRunTimeFile				= nullptr;
char* g_pszHSMKeysFile					= nullptr;
char* g_pszAltTargetBaudRate			= nullptr;
char* g_pszAltHostBaudRate              = nullptr;
char* g_pszComPort						= nullptr;
char* g_pszDeviceName					= nullptr;
char* g_pszLogFile						= nullptr;

std::queue<size_t> g_usrInputOptions;

//
// Output stream defaults to an reference of std::cout with custom deleter (do nothing)
//
std::unique_ptr<std::ostream, std::remove_reference<void(*)(std::ostream*)>::type> g_pOutputStream(&std::cout, [](std::ostream*) {});

int main(int argc, char* argv[])
{
    //*****************************************************************************
    //
    //  Implementation of host programmer commands via lambda function
    //
    //*****************************************************************************
    auto DFU_CPU1 = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------DFU_CPU1------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        if (!g_pszCPU1AppFile)
        {
            *g_pOutputStream << "ERROR: No flash application specified for CPU1 Flash Programming!" << std::endl;
            exitApp(-1);
        }

        // Construct packet payload to send DFU command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_DFU_CPU1,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending CPU1 flash command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt, g_pszCPU1AppFile);
        return status;
    };

    auto DFU_CPU3 = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------DFU_CPU3------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        if (!g_pszCPU3AppFile)
        {
            *g_pOutputStream << "ERROR: No flash application specified for CPU3 Flash Programming!" << std::endl;
            exitApp(-1);
        }

        // Construct packet payload to send DFU command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_DFU_CPU3,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending CPU3 flash command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt, g_pszCPU3AppFile);
        return status;
    };

    auto LOAD_RAM_HSMRT = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------HSMRt------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        if (!g_pszHSMRunTimeFile)
        {
            *g_pOutputStream << "ERROR: No HSMRt Image specified for programming!" << std::endl;
            exitApp(-1);
        }

        // Construct packet payload to send HSM runtime image command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_HSM_RT_IMAGE,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending HSM key provisioning command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt, g_pszHSMRunTimeFile);
        return status;
    };

    auto LOAD_HSM_KEYS = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------HSM_KEYS------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        if (!g_pszHSMKeysFile)
        {
            *g_pOutputStream << "ERROR: No HSM Keys specified for programming!" << std::endl;
            exitApp(-1);
        }

        // Construct packet payload to send HSM Keys command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_HSM_KEYS,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending HSM keys command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt, g_pszHSMKeysFile);
        return status;
    };

    auto LOAD_SEC_CFG = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------SEC_CFG_PROGRAM------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        if (!g_pszSecCfgProgramFile)
        {
            *g_pOutputStream << "ERROR: No Sec Cfg File specified for programming!" << std::endl;
            exitApp(-1);
        }

        // Construct packet payload to send Sec Cfg Program Command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_SEC_CFG_IMAGE,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending SEC_CFG program command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt, g_pszSecCfgProgramFile);
        return status;
    };

    auto LOAD_FLASH_HSMRT = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------HSM_CP_LOAD------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        if (!g_pszHSMFlashCodeProvisionFile)
        {
            *g_pOutputStream << "ERROR: No HSM Flash Code Provisioning File specified for programming!" << std::endl;
            exitApp(-1);
        }

        // Construct packet payload to send HSM Code Provisioning Flash Image command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_HSM_CP_FLASH_IMAGE,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending HSM code provisioning flash image command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt, g_pszHSMFlashCodeProvisionFile);
        return status;
    };

    auto LOAD_CP_CPU1 = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------C29_CPU1_CP_LOAD------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        if (!g_pszCPU1FlashCodeProvisionFile)
        {
            *g_pOutputStream << "ERROR: No CPU1 Flash Code Provisioning File specified for programming!" << std::endl;
            exitApp(-1);
        }

        // Construct packet payload to send CPU1_CP_FLASH_IMAGE command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_CPU1_CP_FLASH_IMAGE,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending CPU1 code provisioning flash image command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt, g_pszCPU1FlashCodeProvisionFile);
        return status;
    };

    auto LOAD_CP_CPU3 = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------C29_CPU3_CP_LOAD------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        if (!g_pszCPU3FlashCodeProvisionFile)
        {
            *g_pOutputStream << "ERROR: No CPU3 Flash Code Provisioning File specified for programming!" << std::endl;
            exitApp(-1);
        }

        // Construct packet payload to send CPU1_CP_FLASH_IMAGE command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_CPU1_CP_FLASH_IMAGE,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending CPU3 code provisioning flash image command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt, g_pszCPU3FlashCodeProvisionFile);
        return status;
    };

    auto SYNC_STATUS = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------SYNC_STATUS---------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        // Construct packet payload with sync status command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_SYNC_STATUS,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending sync status command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt);
        return status;
    };

    auto GET_SOCID = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------GET_SOCID---------------------------------//
        class SocIDPayloadProcessor : public FlashProgrammer::PayloadProcessor
        {
        protected:
            int cmdPktHandler() override
            {
                *g_pOutputStream << "Received packet with SoC ID content, printing the info...\n\n";
                return printSocID(*g_pOutputStream, _cmdPkt.addlContentAddr, _cmdPkt.addlContentLength);
            }
        };

        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        SocIDPayloadProcessor socidPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        // Construct packet payload with GET_SOCID command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_GET_SOCID,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending sync status command packet\n";
        status |= packetExec.run(socidPlHandler, commandPkt);
        return status;
    };

    auto GET_BROM_STATUS = [&](FlashProgrammer::UartInterface& uartHandler)
        {
            //------------------------------------GET_BROM_STATUS---------------------------------//
            class BROMStsPayloadProcessor : public FlashProgrammer::PayloadProcessor
            {
            protected:
                int cmdPktHandler() override
                {
                    *g_pOutputStream << "Received packet with Boot ROM Status, printing the info...\n\n";
                    return printBromStatus(*g_pOutputStream, _cmdPkt.addlContentAddr, _cmdPkt.addlContentLength);
                }
            };

            FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
            BROMStsPayloadProcessor socidPlHandler;
            CommandPkt_t commandPkt;
            int status = 0;

            // Construct packet payload with GET_BROM_STATUS command
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_GET_BROMSTATUS,
                .addlContentLength = 0,
                .addlContentAddr = nullptr
            };

            *g_pOutputStream << "\nSending get boot ROM status command packet\n";
            status |= packetExec.run(socidPlHandler, commandPkt);
            return status;
        };

    auto SET_ALT_BAUDRATE = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------SET_ALT_BAUD_RATE---------------------------------//
        class BaudPayloadProcessor : public FlashProgrammer::PayloadProcessor
        {
        public:
            FlashProgrammer::UartInterface& _uart;
            BaudPayloadProcessor(FlashProgrammer::UartInterface& uartHandler) : _uart(uartHandler) {}
            bool proposeAltBaud = false;
            uint32_t altBaudRate = 0;

        protected:
            int cmdPktHandler() override
            {
                *g_pOutputStream << "Received packet with baud rate content...\n";
                if (_cmdPkt.addlContentLength < 8U)
                {
                    *g_pOutputStream << "BaudPayloadProcessor::cmdPktHandler ERROR: host expects to receive at least 8 bytes of baud rate content but only received " << _cmdPkt.addlContentLength << "\n";
                }

                uint32_t deviceBaudRate, deviceMaxSupport;
                std::memcpy(&deviceBaudRate, &_cmdPkt.addlContentAddr[0], sizeof(deviceBaudRate));
                std::memcpy(&deviceMaxSupport, &_cmdPkt.addlContentAddr[sizeof(deviceBaudRate)], sizeof(deviceMaxSupport));

                if (proposeAltBaud && altBaudRate > deviceBaudRate)
                {
                    *g_pOutputStream << std::dec << "Note: programmer proposed baud rate: " << altBaudRate << " exceeds maxmium supported baud rate of the device, using the target proposed baud rate instead." << "\n";
                }

                *g_pOutputStream << std::dec << "Target reconfigure baud rate: " << deviceBaudRate << "; Device max supported rate: " << deviceMaxSupport << "\n";

                _uart.configBaudRate(deviceBaudRate);
                *g_pOutputStream << "Baud rate configured to " << deviceBaudRate << ", waiting to recv target message...\n";
                return 0;
            }
        };

        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        BaudPayloadProcessor baudPlHandler(uartHandler);
        CommandPkt_t commandPkt;
        int status = 0;

        if (g_pszAltTargetBaudRate && std::string(g_pszAltTargetBaudRate) != "0")
        {
            // Convert decimal baud rate to uint32_t
            baudPlHandler.proposeAltBaud = true;
            baudPlHandler.altBaudRate = strtoul(g_pszAltTargetBaudRate, nullptr, 10);

            // Construct packet payload with GET_ALT_UART_BAUD command and proposed alternate baud rate
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_GET_ALT_UART_BAUD,
                .addlContentLength = sizeof(baudPlHandler.altBaudRate),
                .addlContentAddr = (char*)&baudPlHandler.altBaudRate
            };
        }
        else
        {
            baudPlHandler.proposeAltBaud = false;

            // Construct packet payload with GET_ALT_UART_BAUD command (target will determine the alternate baud rate)
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_GET_ALT_UART_BAUD,
                .addlContentLength = 0,
                .addlContentAddr = nullptr
            };
        }

        *g_pOutputStream << "\nSending configure baud rate command packet\n";
        status |= packetExec.run(baudPlHandler, commandPkt);
        return status;
    };

    auto RUN_CPU1 = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------RUN_CPU1----------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        //
        // Optional Entry Address override
        //
        if (g_pszAppEntryAddress)
        {
            // Convert hex entry address to uint32_t
            uint32_t entryAddr = strtoul(g_pszAppEntryAddress, nullptr, 16);

            // Construct packet payload with app entry address selection
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_SET_APP_ENTRY_ADDRESS,
                .addlContentLength = sizeof(entryAddr),
                .addlContentAddr = (char*)&entryAddr
            };
            *g_pOutputStream << "\nSending entry address command packet\n";
            status |= packetExec.run(defaultPlHandler, commandPkt);
        }

        // Construct packet payload with run cpu1 command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_RUN_CPU1,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending entry address command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt);
        return status;
    };

    auto RUN_CPU3 = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------RUN_CPU3----------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        //
        // Optional Entry Address override
        //
        if (g_pszAppEntryAddress)
        {
            // Convert entry address to uint32_t
            uint32_t entryAddr = strtoul(g_pszAppEntryAddress, nullptr, 16);

            // Construct packet payload with app entry address selection
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_SET_APP_ENTRY_ADDRESS,
                .addlContentLength = sizeof(entryAddr),
                .addlContentAddr = (char*)&entryAddr
            };
            *g_pOutputStream << "\nSending entry address command packet\n";
            status |= packetExec.run(defaultPlHandler, commandPkt);
        }

        // Construct packet payload with run cpu3 command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_RUN_CPU3,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending run cpu3 command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt);
        return status;
    };

    auto RESET_CPU1 = [&](FlashProgrammer::UartInterface& uartHandler)
    {
        //------------------------------------RESET_CPU1---------------------------------//
        FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
        FlashProgrammer::PayloadProcessor defaultPlHandler;
        CommandPkt_t commandPkt;
        int status = 0;

        // Construct packet payload with reset cpu1 command
        commandPkt = CommandPkt_t
        {
            .payloadType = PayloadType::Command,
            .command = COMMAND_RESET_CPU1,
            .addlContentLength = 0,
            .addlContentAddr = nullptr
        };

        *g_pOutputStream << "\nSending reset CPU1 command packet\n";
        status |= packetExec.run(defaultPlHandler, commandPkt);
        return status;
    };

    auto SET_BANKMODE0 = [&](FlashProgrammer::UartInterface& uartHandler)
        {
            //--------------------------------PROGRAM_BANKMODE_0---------------------------------//
            FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
            FlashProgrammer::PayloadProcessor defaultPlHandler;
            CommandPkt_t commandPkt;
            int status = 0;

            // Construct packet payload with reset cpu1 command
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_BANK_MODE_0,
                .addlContentLength = 0,
                .addlContentAddr = nullptr
            };

            *g_pOutputStream << "\nSending programming bank mode 0 packet\n";
            status |= packetExec.run(defaultPlHandler, commandPkt);
            return status;
        };

    auto SET_BANKMODE1 = [&](FlashProgrammer::UartInterface& uartHandler)
        {
            //--------------------------------PROGRAM_BANKMODE_1---------------------------------//
            FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
            FlashProgrammer::PayloadProcessor defaultPlHandler;
            CommandPkt_t commandPkt;
            int status = 0;

            // Construct packet payload with reset cpu1 command
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_BANK_MODE_1,
                .addlContentLength = 0,
                .addlContentAddr = nullptr
            };

            *g_pOutputStream << "\nSending programming bank mode 1 packet\n";
            status |= packetExec.run(defaultPlHandler, commandPkt);
            return status;
        };

    auto SET_BANKMODE2 = [&](FlashProgrammer::UartInterface& uartHandler)
        {
            //--------------------------------PROGRAM_BANKMODE_2---------------------------------//
            FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
            FlashProgrammer::PayloadProcessor defaultPlHandler;
            CommandPkt_t commandPkt;
            int status = 0;

            // Construct packet payload with reset cpu1 command
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_BANK_MODE_2,
                .addlContentLength = 0,
                .addlContentAddr = nullptr
            };

            *g_pOutputStream << "\nSending programming bank mode 2 packet\n";
            status |= packetExec.run(defaultPlHandler, commandPkt);
            return status;
        };

    auto SET_BANKMODE3 = [&](FlashProgrammer::UartInterface& uartHandler)
        {
            //--------------------------------PROGRAM_BANKMODE_3---------------------------------//
            FlashProgrammer::UartPacketExecutor	packetExec(uartHandler);
            FlashProgrammer::PayloadProcessor defaultPlHandler;
            CommandPkt_t commandPkt;
            int status = 0;

            // Construct packet payload with reset cpu1 command
            commandPkt = CommandPkt_t
            {
                .payloadType = PayloadType::Command,
                .command = COMMAND_BANK_MODE_3,
                .addlContentLength = 0,
                .addlContentAddr = nullptr
            };

            *g_pOutputStream << "\nSending programming bank mode 3 packet\n";
            status |= packetExec.run(defaultPlHandler, commandPkt);
            return status;
        };
    /* End of lambda functions */


    FlashProgrammer::UartInterface uartHandler;
	int iExitCode = 0;
	bool done = false;

	std::ios_base::sync_with_stdio(false);

	//
	// Parse the command line parameters, print the welcome banner and
	// tell the user about any errors they made.
	//
	parseCommandLine(argc, argv);

	//
	// configure and open UART COM/tty port
	//
	try
	{
        *g_pOutputStream << "Serial Port: " << g_pszComPort << "\n";

#ifdef ENABLE_PERIPHERAL_BOOT
        // Using the device ROM default baud rate setting.
		uartHandler.configComPort(g_pszComPort);
#else
        //
        // Optional host baud rate change (appIn version ONLY)
        //
        if (g_pszAltHostBaudRate)
        {
            size_t newHostBaud = strtoul(g_pszAltHostBaudRate, nullptr, 10);
            uartHandler.configComPort(g_pszComPort, newHostBaud);
        }
        else
        {
            // Using the device ROM default baud rate setting.
            uartHandler.configComPort(g_pszComPort); 
        }
#endif  /* ENABLE_PERIPHERAL_BOOT */
	}
	catch (const std::exception& eptr)
	{
		const char* badMsg = eptr.what();
		*g_pOutputStream << "Error occurred during initialization of UART settings: \n" << badMsg << std::endl;
		exitApp(-1);
	}

//
// Download the Kernel (non-appIn version ONLY)
//
#ifdef ENABLE_PERIPHERAL_BOOT
	if (!g_pszKernelFile)
	{
		*g_pOutputStream << "ERROR: No flash kernel specified for CPU1 download kernel!" << std::endl;
		exitApp(-1);
	}

	*g_pOutputStream << "\nDownloading SBL kernel to CPU1...";
	iExitCode |= downloadBootloader(uartHandler, g_pszKernelFile);

    if (g_bBootOnly)
    {
        *g_pOutputStream << "\nPeripheral UART boot success, exiting the application.";
        exitApp(iExitCode);
    }

    // Wait for device to initalize
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    //
    // Automatically set alterate baudrate
    //
    *g_pOutputStream << "\nConfiguring UART for an alternate baud rate than the ROM default of 115200...";
    iExitCode |= SET_ALT_BAUDRATE(uartHandler);
#endif /* ENABLE_PERIPHERAL_BOOT */

	while (!done)
	{
        size_t responseOption;

        if (g_bUsrCommand)
        {
            if (iExitCode)
            {
                *g_pOutputStream << "An error has occured in the previous command, exiting the Application." << std::endl;
                exitApp(iExitCode);
            }
            if (g_usrInputOptions.empty())
            {
                *g_pOutputStream << "Command all done, exiting the application." << std::endl;
                exitApp(iExitCode);
            }

            // Wait for device to wrap up previous command (not necessary but just in case)
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            responseOption = g_usrInputOptions.front();
            g_usrInputOptions.pop();
            *g_pOutputStream << std::dec << "Executing command option " << responseOption << std::endl;
        }
        else
        {
            // Display user input options
            std::cout << ("\nPlease select from the available operations below\n");
            std::cout << ("Programming operations:\n");
            std::cout << ("\t  1-CPU1 DFU/FOTA        (HS-FS only)\n");
            std::cout << ("\t  2-CPU3 DFU/FOTA        (HS-FS only)\n");
            std::cout << ("\t  3-Load HSM RAM Image   (Runtime Image for KP & CP)\n");
            std::cout << ("\t  4-Load HSM Key         (HS-KP Key Provision)\n");
            std::cout << ("\t  5-Load Sec Cfg         (HS-SE Code Provision)\n");
            std::cout << ("\t  6-Load HSM Flash Image (HS-SE Code Provision)\n");
            std::cout << ("\t  7-Load C29 CPU1 Image  (HS-SE Code Provision)\n");
            std::cout << ("\t  8-Load C29 CPU3 Image  (HS-SE Code Provision)\n");
            std::cout << ("Utility operations:\n");
            std::cout << ("\t 10-Sync Device Status\n");
            std::cout << ("\t 11-Get SoC ID Info\n");
            std::cout << ("\t 12-Get Boot ROM Status\n");
            std::cout << ("\t 13-Run CPU1\n");
            std::cout << ("\t 14-Run CPU3\n");
            std::cout << ("\t 15-Reset CPU1\n");
            std::cout << ("\t 19-Configure UART Baud Rate\n");
            std::cout << ("\t 20-Set Bankmode 0\n");
            std::cout << ("\t 21-Set Bankmode 1\n");
            std::cout << ("\t 22-Set Bankmode 2\n");
            std::cout << ("\t 23-Set Bankmode 3\n");
            std::cout << ("\t  0-Done\n");

            std::cin >> std::dec >> responseOption;

            // Ignore gibberish characters in the input buffer up to the newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (std::cin.fail()) 
            {
                std::cout << "Invalid input: Not a valid command. Please try again." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }

		switch (responseOption)
		{
            case 1: 
                iExitCode |= DFU_CPU1(uartHandler);
                break;
            case 2: 
                iExitCode |= DFU_CPU3(uartHandler);
                break;
            case 3:
                iExitCode |= LOAD_RAM_HSMRT(uartHandler);
                break;
            case 4:
                iExitCode |= LOAD_HSM_KEYS(uartHandler);
                break;
            case 5:
                iExitCode |= LOAD_SEC_CFG(uartHandler);
                break;
            case 6:
                iExitCode |= LOAD_FLASH_HSMRT(uartHandler);
                break;
            case 7:
                iExitCode |= LOAD_CP_CPU1(uartHandler);
                break;
            case 8:
                iExitCode |= LOAD_CP_CPU3(uartHandler);
                break;
            case 10:
                iExitCode |= SYNC_STATUS(uartHandler);
                break;
            case 11:
                iExitCode |= GET_SOCID(uartHandler);
                break;
            case 12:
                iExitCode |= GET_BROM_STATUS(uartHandler);
                break;
            case 13:
                iExitCode |= RUN_CPU1(uartHandler);
                break;
            case 14:
                iExitCode |= RUN_CPU3(uartHandler);
                break;
            case 15:
                iExitCode |= RESET_CPU1(uartHandler);
                break;
            case 19:
                iExitCode |= SET_ALT_BAUDRATE(uartHandler);
                break;
            case 20:
                iExitCode |= SET_BANKMODE0(uartHandler);
                break;
            case 21:
                iExitCode |= SET_BANKMODE1(uartHandler);
                break;
            case 22:
                iExitCode |= SET_BANKMODE2(uartHandler);
                break;
            case 23:
                iExitCode |= SET_BANKMODE3(uartHandler);
                break;
            case 0:
                //------------------------------------DONE-----------------------------------------//
                done = true;
                std::cout << "Exiting the application." << std::endl;
                break;
            default:
                //------------------------------------DEFAULT-------------------------------------//
                std::cout << "Invalid input: Not a valid command. Please try again." << std::endl;
                break;
		}
	}
	exitApp(iExitCode);
}

/** @} */