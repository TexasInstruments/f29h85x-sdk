//###########################################################################
//
// FILE:    ex4_uart_sbl.c
//
// TITLE:   CPU kernel main function
// <h1> CPU kernel main function </h1>
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

// #include "FlashTech.h"
#include "board.h"
#include "cputimer.h"
#include "drivers/hsmclient/hsmclient.h"
#include "ex4_cpubrom.h"
#include "f29h85x_kernel_commands_cpu1.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "ssu.h"
#include "watchdog.h"
#include <ex4_uart_sbl.h>
#include <ti_drivers_config.h>
#include <ti_dpl_config.h>

uint8_t BankNum;
uint8_t deviceState;
FlashStatusCode statusCode;
uint32_t ENTRY_ADDR;
uint32_t LOAD_ADDR;
uint32_t IMAGE_SIZE;
uint16_t CHECKSUM;
uint8_t cpuTimer0IntCount = 0;
uint8_t bootFlag = 0;
uint8_t validCmdFlag = 0;
uint8_t ledBit = 0;
extern HsmClient_t gHSMClient;

#define HSM_FLASH_START_ADDRESS 0x10001140U

#ifdef BANKMODE1
#define BANKMODE Mode1
#elif BANKMODE3
#define BANKMODE Mode3
#endif


__attribute__((retain, section("firmware"))) const uint8_t firmwaredata[27000] = {0U};


/**
 * main.c
 */
int main(void)
{
    //
    // Local variables
    //
    uint16_t command;
    uint16_t data[10];
    uint16_t length;
    uint32_t selected_bank;
    Fapi_StatusType oReturnCheck;
    int32_t status = 0;

    uint8_t bank_mode = getBankMode();

    // Initialize the device and GPIOs (driverlib)
    Device_init();
    Device_initGPIO();

    //
    // First, need to determine if device is HS-FS or HS-SE
    //
    deviceState = getDeviceState();

    //
    // Verify the HSMRt is running on the HSM
    //
    if (deviceState == HS_SE) 
    {
        /* Initialize Clocks and Interrupts */
        Dpl_init();
        status = Hsmclient_loadHSMRtFirmware(&gHSMClient, (uint8_t*) HSM_FLASH_START_ADDRESS);
        DebugP_assert(SystemP_SUCCESS == status);
        //
        // Synchornization mechanism to prevent C29 CPU requests before HSMRt begins
        //
        if (SystemP_SUCCESS == status)
        {
            status = HsmClient_waitForBootNotify(NULL, 0);
            Dpl_deinit();
        }
        System_init();
    } else {
        ENINT;
        Interrupt_enableGlobal();
    }
    //
    // Initialize syscfg peripherals
    //
    Board_init();
        
    // By default, flash image is expected to be one full bank pair
    IMAGE_SIZE = (0x100000);

    //
    // Set default value for load address
    //
    LOAD_ADDR = C29FlashBankFR1RP0StartAddress;

    //
    // If bank mode doesn't match, need to wait for firmware. Cannot boot to existing firmware
    // 0xFFFF is an exception because that means Boot Manager + firmware has been loaded for the first time
    //
    if (getPreviousBankMode() != 0xFFFF) 
    {
        if (getBankMode() != getPreviousBankMode()) 
        {
            CPUTimer_disableInterrupt(CPUTIMER0_BASE);
        }
    }  

    //
    // Flush UART-A
    //
    uartaFlush();
    
    //
    // get user command through console.
    //
    command = uartGetPacket(&length, data);
    while(1)
    {
        //
        // Reset the statusCode.
        //
        statusCode.status = NO_COMMAND_ERROR;

        //
        // Reset data packet flag
        //
        bool sendDataPacket = false;

        //
        // If Timeout has been reached with valid application in flash,
        // boot to existing firmware
        //
        if (bootFlag) 
        {
            BootExistingFirmware(deviceState);
        }

        //
        // DFU_CPU1
        //
        if(command == DFU_CPU1)
        {
            //
            // Acknowledge that valid cmd was received
            //
            validCmdFlag = 1;

            //
            // DFU is not compatible with HS-SE Devices
            //
            if (deviceState == HS_SE) 
            {
                statusCode.status = COMMAND_ERROR;
            } else 
            {
                //
                // loads application into CPU1 FLASH
                //
                uartDFU(1, bank_mode, UART_BOOT_ALT2, C29FlashBankFR1RP0StartAddress, IMAGE_SIZE, deviceState);
            }

            //
            // send the flash status packet and if NAK send again.
            //
            while(uartSendFlashStatusPacket(command, &statusCode)){}

            //
            // reply back with a message
            //
            char ch[] = "CPU1 image has been written to flash, please proceed to Run CPU1 or Reset CPU1(in flash boot mode) to start the new firmware.";
            uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t*)ch, sizeof(ch));
        }
        else if(command == DFU_CPU3)
        {
            //
            // Acknowledge that valid cmd was received
            //
            validCmdFlag = 1;

            //
            // DFU is not compatible with HS-SE Devices and
            // cannot upgrade CPU3 firmware in Bank Mode 1
            //
            if ((deviceState == HS_SE) || (bank_mode == Mode1)) 
            {
                statusCode.status = COMMAND_ERROR;
            } else 
            {
                //
                // loads application into CPU1 FLASH
                //
                uartDFU(3, bank_mode, UART_BOOT_ALT2, C29FlashBankFR2RP0StartAddress, IMAGE_SIZE, deviceState);
            }

            //
            // send the flash status packet and if NAK send again.
            //
            while(uartSendFlashStatusPacket(command, &statusCode)){}

            //
            // reply back with a message
            //
            char ch[] = "CPU3 image has been written to flash, please proceed to Run CPU3 or Reset CPU3(in flash boot mode) to start the new firmware.";
            uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t*)ch, sizeof(ch));
        }
        else if ((command == HSM_CP_FLASH_IMAGE) || (command == CPU1_CP_FLASH_IMAGE) || (command == CPU3_CP_FLASH_IMAGE)) 
        {

            validCmdFlag = 1;

            //
            // Set error if CP command  is sent for HS-FS or if invalid bmode and CPU target are selected
            //
            if ((deviceState == HS_FS) || ((bank_mode == Mode1) && (command == CPU3_CP_FLASH_IMAGE))) 
            {
                statusCode.status = COMMAND_ERROR;

            } else if (provisionApplicationImgToHSM(LDA1_RAM_BASE, bank_mode))
            {
                statusCode.status = AUTHENTICATION_ERROR;
            }

            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }

            if (command == HSM_CP_FLASH_IMAGE)
            {
                char testString[] = "HSM Run Time Loading is successful.";
                uint16_t testSize = sizeof(testString) / sizeof(*testString);
                uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);
            }
            else
            {
                char testString[] = "APP Loading is successful.";
                uint16_t testSize = sizeof(testString) / sizeof(*testString);
                uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);

                // while(uartSendFlashStatusPacket(command, &statusCode)){}
            }
        }
        //
        // Load SEC CFG Program Image
        //
        else if (command == SEC_CFG_IMAGE)
        {

            //
            // Sec Cfg Program Logic
            //
            if (provisionSecCfgImg(LDA1_RAM_BASE))
            {
                statusCode.status = AUTHENTICATION_ERROR;
            }

            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }

            char testString[] = "SecCfg Loading is successful.";
            uint16_t testSize = sizeof(testString) / sizeof(*testString);
            uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);
        }
        //
        // SYNC STATUS
        //
        else if (command == SYNC_STATUS)
        {
            char testString[] = "!!! SBL LIVE !!!";
            uint16_t testSize = sizeof(testString) / sizeof(*testString);
            uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);

            //
            // send the flash status packet
            //
            while(uartSendFlashStatusPacket(command, &statusCode)){}
        }
        //
        // CPU reset
        //
        else if (command == RESET_CPU1)
        {
            //
            // break out of infinite loop to reset
            //
            break;
        }
        //
        // COMMAND_ERROR
        //
        else
        {
            statusCode.status = COMMAND_ERROR;

            while(uartSendFlashStatusPacket(command, &statusCode)){}
        }

        command = uartGetPacket(&length, data); //get next packet
    }

    // Enable WD and let it reset device
    SysCtl_enableWatchdog();

    while(1) 
    {

    }
	return(ENTRY_ADDR);
}


//
// Function that firmware will branch to when DFU CPU1 command received from firmware
//
__attribute__((__used__))
__attribute__((section("CPU1_FOTA_ENTRY")))
void cpu1FOTA(void) 
{

    //
    // Initialize locals
    //
    uint16_t command;
    uint16_t data[10];
    uint16_t length;

    initializeFlash();
    
    // By default, flash image is expected to be one full bank pair
    IMAGE_SIZE = (0x100000);

    //
    // Set default value for load address
    //
    LOAD_ADDR = C29FlashBankFR1RP0StartAddress;

    //
    // First, need to determine if device is HS-FS or HS-SE
    //
    deviceState = getDeviceState();

    command = DFU_CPU1;
    statusCode.status = NO_COMMAND_ERROR;

    //
    // DFU is not compatible with HS-SE Devices
    //
    if (deviceState == HS_SE) 
    {
        statusCode.status = COMMAND_ERROR;
    } else 
    {
        //
        // loads application into CPU1 FLASH
        //
        uartDFU(1, BANKMODE, UART_BOOT_ALT2, C29FlashBankFR1RP0StartAddress, IMAGE_SIZE, deviceState);
    }

    //
    // send the flash status packet and if NAK send again.
    //
    while(uartSendFlashStatusPacket(command, &statusCode)){}

    //
    // reply back with a message
    //
    char ch[] = "CPU1 image has been written to flash, please proceed to Run CPU1 or Reset CPU1(in flash boot mode) to start the new firmware.";
    uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t*)ch, sizeof(ch));

}

//
// Function that firmware will branch to when DFU CPU3 command received from firmware
//
__attribute__((__used__))
__attribute__((section("CPU3_FOTA_ENTRY")))
void cpu3FOTA(void) 
{
    //
    // Initialize locals
    //
    uint16_t command;
    uint16_t data[10];
    uint16_t length;

    initializeFlash();

    // By default, flash image is expected to be one full bank pair
    IMAGE_SIZE = (0x100000);

    //
    // Set default value for load address
    //
    LOAD_ADDR = C29FlashBankFR1RP0StartAddress;

    //
    // First, need to determine if device is HS-FS or HS-SE
    //
    deviceState = getDeviceState();

    command = DFU_CPU3;
    statusCode.status = NO_COMMAND_ERROR;

    //
    // DFU is not compatible with HS-SE Devices and
    // cannot upgrade CPU3 firmware in Bank Mode 1
    //
    if ((deviceState == HS_SE) || (BANKMODE == Mode1)) 
    {
        statusCode.status = COMMAND_ERROR;
    } else 
    {
        //
        // loads application into CPU1 FLASH
        //
        uartDFU(3, BANKMODE, UART_BOOT_ALT2, C29FlashBankFR2RP0StartAddress, IMAGE_SIZE, deviceState);
    }

    //
    // send the flash status packet and if NAK send again.
    //
    while(uartSendFlashStatusPacket(command, &statusCode)){}

    //
    // reply back with a message
    //
    char ch[] = "CPU3 image has been written to flash, please proceed to Run CPU3 or Reset CPU3(in flash boot mode) to start the new firmware.";
    uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t*)ch, sizeof(ch));

}

//
// Function that firmware will branch to when CP command received
//
__attribute__((__used__))
__attribute__((section("CPU1_SECURE_FOTA_ENTRY")))
void cpu1SecureFOTA(void) 
{
    //
    // Initialize locals
    //
    uint16_t command;
    uint16_t data[10];
    uint16_t length;

    //
    // First, need to determine if device is HS-FS or HS-SE
    //
    deviceState = getDeviceState();

    command = CPU1_CP_FLASH_IMAGE;
    statusCode.status = NO_COMMAND_ERROR;

    //
    // Set error if CP command  is sent for HS-FS or if invalid bmode and CPU target are selected
    //
    if (deviceState == HS_FS) 
    {
        statusCode.status = COMMAND_ERROR;

    } else if (provisionApplicationImgToHSM(LDA1_RAM_BASE, getBankMode()))
    {
        statusCode.status = AUTHENTICATION_ERROR;
    }

    while (uartSendFlashStatusPacket(command, &statusCode))
    {
    }

    char testString[] = "APP Loading is successful.";
    uint16_t testSize = sizeof(testString) / sizeof(*testString);
    uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);

}

//
// Function that firmware will branch to when CP command received
//
__attribute__((__used__))
__attribute__((section("CPU3_SECURE_FOTA_ENTRY")))
void cpu3SecureFOTA(void) 
{
    //
    // Initialize locals
    //
    uint16_t command;
    uint16_t data[10];
    uint16_t length;

    //
    // First, need to determine if device is HS-FS or HS-SE
    //
    deviceState = getDeviceState();

    command = CPU3_CP_FLASH_IMAGE;
    statusCode.status = NO_COMMAND_ERROR;

    //
    // Set error if CP command  is sent for HS-FS or if invalid bmode and CPU target are selected
    //
    if ((deviceState == HS_FS) || ((BANKMODE == Mode1) && (command == CPU3_CP_FLASH_IMAGE))) 
    {
        statusCode.status = COMMAND_ERROR;

    } else if (provisionApplicationImgToHSM(LDA1_RAM_BASE, getBankMode()))
    {
        statusCode.status = AUTHENTICATION_ERROR;
    }

    while (uartSendFlashStatusPacket(command, &statusCode))
    {
    }

    char testString[] = "APP Loading is successful.";
    uint16_t testSize = sizeof(testString) / sizeof(*testString);
    uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);

}

//
// Function that firmware will branch to when CP command received
//
__attribute__((__used__))
__attribute__((section("HSM_SECURE_FOTA_ENTRY")))
void hsmSecureFOTA(void) 
{
    //
    // Initialize locals
    //
    uint16_t command;
    uint16_t data[10];
    uint16_t length;

    //
    // First, need to determine if device is HS-FS or HS-SE
    //
    deviceState = getDeviceState();

    command = HSM_CP_FLASH_IMAGE;
    statusCode.status = NO_COMMAND_ERROR;

    //
    // Set error if CP command  is sent for HS-FS or if invalid bmode and CPU target are selected
    //
    if (deviceState == HS_FS) 
    {
        statusCode.status = COMMAND_ERROR;

    } else if (provisionApplicationImgToHSM(LDA1_RAM_BASE, getBankMode()))
    {
        statusCode.status = AUTHENTICATION_ERROR;
    }

    while (uartSendFlashStatusPacket(command, &statusCode))
    {
    }

    char testString[] = "HSM Loading is successful.";
    uint16_t testSize = sizeof(testString) / sizeof(*testString);
    uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);

}

//
// Function that firmware will branch to when SECCFG CP command received
//
__attribute__((__used__))
__attribute__((section("SECCFG_PROGRAM_ENTRY")))
void seccfgProgram(void) 
{
    //
    // Initialize locals
    //
    uint16_t command;
    uint16_t data[10];
    uint16_t length;

    command = SEC_CFG_IMAGE;
    statusCode.status = NO_COMMAND_ERROR;

    //
    // Sec Cfg Program Logic
    //
    if (provisionSecCfgImg(LDA1_RAM_BASE))
    {
        statusCode.status = AUTHENTICATION_ERROR;
    }

    while (uartSendFlashStatusPacket(command, &statusCode))
    {
    }

    char testString[] = "SecCfg Loading is successful.";
    uint16_t testSize = sizeof(testString) / sizeof(*testString);
    uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);

}

//
// Initialize flash driverlib, flash API, and get flash semaphore for CPU1
//
void initializeFlash() 
{

    Fapi_StatusType  oReturnCheck;
    
    //
    // At 200MHz, execution wait-states for external oscillator is 3. Modify the
    // wait-states when the system clock frequency is changed.
    //
    Flash_initModule(3);

    // Initialize the Flash API by providing the Flash register base address
    // and operating frequency(in MHz).
    // This function is required to initialize the Flash API based on System
    // frequency before any other Flash API operation can be performed.
    // This function must also be called whenever System frequency or RWAIT is
    // changed.
    //
    oReturnCheck = Fapi_initializeAPI((Fapi_FmcRegistersType*)FLASHCONTROLLER1_BASE, 200);
    
    if(oReturnCheck != Fapi_Status_Success)
    {
        //
        // Check Flash API documentation for possible errors
        //
        Example_Error();
    }


}

//
// ISRs for the timer interrupts
//
void cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;
    if (cpuTimer0IntCount == 8) 
    {
        CPUTimer_disableInterrupt(CPUTIMER0_BASE);
        if (validCmdFlag == 0) 
        {
            bootFlag = 1;
            BootExistingFirmware(deviceState);
        }
        
    }
}


//
// Jump to this function when SBL times out
//
void BootExistingFirmware(uint8_t currentState)
{

    [[clang::noinline]] CPU_jumpToAddr(APP_ENTRY_POINT);

}

//
// Returns device state (HS-FS or HS-SE)
//
uint8_t getDeviceState() 
{
    //
    // Read DEVCFG_BASE.DEVLIFECYCLE.HSSUBTYPE to determine device state
    //
    return ((HWREG((DEVCFG_BASE + 0x3D4)) & 0xF00) >> 8);
}

//
// Returns CPU1 Bank Mode
//
uint8_t getBankMode()
{
    return((HWREG(SSUGEN_BASE + 0x5C)));
}

//
// Returns bank mode programmed in data flash after successful firmware update
//
uint32_t getPreviousBankMode() 
{
    uint32_t prevBankMode = C29FlashBankFR4RP0StartAddress;
    return (HWREG(prevBankMode));
}

//
// Function used to branch to an address
//
uint32_t CPU_jumpToAddr(uint32_t jumpAddr)
{
    asm(" MV A7, D0");
    asm(" LB A7");
    return jumpAddr;
}

uint16_t uartSendDataPacket(uint16_t command, uint8_t *data, uint16_t length)
{
    int i;

    uartaFlush();
    DEVICE_DELAY_US(100000);
    uartSendWord(FULL_PACKET_HEADER);
    uartSendWord(length);

    CHECKSUM = 0;
    uartSendWord(command);

    for (i = 0; i < length; i++)
    {
        uartSendByte(*(data + i));
    }

    uartSendChecksum();
    uartSendWord(FULL_PACKET_FOOTER);

    //
    // Receive an ACK or NAK
    //
    return uartaGetACK();
}

//
// uartSendByte - Sends a byte.
//
void uartSendByte(uint8_t byte)
{
    //
    // send LSB of word, driverlib.
    //
    UART_writeChar(UARTA_BASE, byte);
    CHECKSUM += byte;
    uartaFlush();
}

//
// uartGetPacket -  This routine receives the packet, returns the
//                 command and puts the data length in Uin16* length
//                 and data in uint16_t* data
//
uint16_t uartGetPacket(uint16_t* length, uint16_t* data)
{
    
    if(uartGetOnlyWordData() != 0x1BE4)
    {
        sendNAK();

        //
        // start packet error
        //
        return(100);
    }

    *length = uartGetOnlyWordData();

    //
    // checksum of command and data
    //
    CHECKSUM = 0;
    uint16_t command = uartGetOnlyWordData();

    int i = 0;
    for(i = 0; i < (*length)/2; i++)
    {
        *(data+i) = uartGetOnlyWordData();
    }

    uint16_t dataChecksum = CHECKSUM;
    if(dataChecksum != uartGetOnlyWordData())
    {
        sendNAK();

        //
        // checksum error
        //
        return(101);
    }
    if(uartGetOnlyWordData() != 0xE41B)
    {
        sendNAK();

        //
        // end packet error
        //
        return(102);
    }

    sendACK();
    return(command);
}

//
//
// uartSendPacket -  Sends a Packet to the host which contains
//                  status in the data and address.  It sends the
//                  statusCode global variable contents.  It then waits
//                  for an ACK or NAK from the host.
//
uint16_t uartSendFlashStatusPacket(uint16_t command, FlashStatusCode* statusCode)
{
    int i;
    uint16_t packetSize = 12;
    uint16_t status = statusCode->status;
    uint16_t flashError = statusCode->flashAPIError;
    uint16_t* address = (uint16_t*)&(statusCode->address);
    uint16_t* fsmStatus = (uint16_t*)&(statusCode->flashAPIFsmStatus);

    uartaFlush();
    DEVICE_DELAY_US(100000);

    uartSendWord(0x1BE4);
    uartSendWord(packetSize);

    CHECKSUM = 0;
    uartSendWord(command);
    uartSendWord(status);

    for(i = 0; i < 2; i++)
    {
        uartSendWord(*(address + i));
    }

    uartSendWord(flashError);

    for(i = 0; i < 2; i++){
        uartSendWord(*(fsmStatus + i));
    }

    uartSendChecksum();
    uartSendWord(0xE41B);

    //
    // Receive an ACK or NAK
    //
    return uartaGetACK();
}


//
// uartaFlush - This routine flushes UARTA.
//
void uartaFlush(void)
{
    //
    // wait while TX is busy.
    //
    while(UART_isBusy(UARTA_BASE))
    {
    }
}


//
// uartaGetData   -   This routine fetches one byte from the UART-A
//                    port and echoes it back if checksum is enabled.
//
uint16_t uartGetData(void)
{
   //uint16_t wordData;
   uint16_t byteData;

   //wordData = 0x0000;
   byteData = 0x0000;

   //
   // Fetch the LSB and verify back to the host
   //
   byteData = UART_readChar(UARTA_BASE); // wait until RX is rdy then read.

#if checksum_enable

   //
   // wait until TX is rdy then write.
   //
   UART_writeChar(UARTA_BASE, byteData);

#endif

//
// form checksum.
//
#if checksum_enable
    CHECKSUM += byteData;
#endif

   return byteData;
}

//
// uartGetOnlyWordData -  This routine fetches two bytes from the SCI-A
//                        port and puts them together to form a single
//                        16-bit value.  It is assumed that the host is
//                        sending the data in the order LSB followed by MSB.
//
uint16_t uartGetOnlyWordData(void)
{
   uint16_t wordData;
   uint16_t byteData;

   wordData = 0x0000;
   byteData = 0x0000;

   //
   // Fetch the LSB and verify back to the host
   //
   wordData = UART_readChar(UARTA_BASE);

   //
   // Fetch the MSB and verify back to the host
   //
   byteData = UART_readChar(UARTA_BASE);

   // compute checksum.
   CHECKSUM += wordData + byteData;

   //
   // form the wordData from the MSB:LSB
   //
   wordData |= (byteData << 8);

   return wordData;
}

//
// uartSendWord - Sends a uint16_t word.
//
void uartSendWord(uint16_t word)
{
    //
    // send LSB of word, driverlib.
    //
    UART_writeChar(UARTA_BASE, (word & 0xFF));

    CHECKSUM += word & 0xFF;

    uartaFlush();
    //uartaGetACK();

    //
    // send MSB of word, driverlib.
    //
    UART_writeChar(UARTA_BASE, ((word>>8) & 0xFF));

    CHECKSUM += word>>8 & 0xFF;

    uartaFlush();
    //uartaGetACK();
}

//
// uartSendChecksum - Sends the Global checksum value
//
void uartSendChecksum()
{
    //
    // wait for SCIA_TX to be free and write LSB of checksum to it.
    //
    UART_writeChar(UARTA_BASE, (CHECKSUM & 0xFF));

    uartaFlush();
    //uartaGetACK();

    //
    // wait for SCIA_TX to be free and write MSB of checksum to it.
    //
    UART_writeChar(UARTA_BASE, ((CHECKSUM >> 8) & 0xFF));

    uartaFlush();
    //uartaGetACK();
}

//
// sendNAK - This routine transmits NAK.
//
void sendNAK(void)
{
    //
    // write NotAcKowledged.
    //
    UART_writeChar(UARTA_BASE, NAK);

    uartaFlush();
}

//
// sendACK - This routine transmits ACK.
//
void sendACK(void)
{
    //
    // write ACKowledged.
    //
    UART_writeChar(UARTA_BASE, ACK);

    uartaFlush();
}


//
// uartaGetACK - Gets 1-byte ACK from the host.
//
uint16_t uartaGetACK()
{
    uint16_t wordData;

    //
    // wait for and read a char blocking nonFIFO, driverlib.
    //
    wordData = UART_readChar(UARTA_BASE);

    if(wordData != ACK)
    {
        return(1);
    }

    return(0);
}
