// ###########################################################################
//
//  FILE:    ex3_uart_flash_kernel_cpu1.c
//
//  TITLE:   CPU kernel get function
//  <h1> CPU kernel get function </h1>
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

#include <ex3_uart_get_function_cpu1.h>
#include <ti_drivers_config.h>

#define PARSED_VERSION_BUFFER_LENGTH (0x96U)
#define MAX_SIZE_KP_LOG (0x2000U)

/* Global variable declare in auto-gen file */
extern HsmClient_t gHSMClient;

//
// uartGetFunction - This function first initializes UART-A and
//                   contains a while loop waiting on
//                   commands from the host.  It processes each
//                   command and sends a response except for Run and
//                   Reset commands.  On Run the kernel exits and branches
//                   to the Entry Point.  On Reset, the kernel exits the
//                   while loop and does a WatchDog Time-out.
//
uint32_t uartGetFunction(uint32_t BootMode)
{
    uint16_t command;
    uint16_t data[10];
    uint16_t length;
    uint32_t selected_bank;
    uint8_t bankMode;
    uint8_t deviceState;

#ifdef DFU_CPU1_APP
    Fapi_StatusType oReturnCheck;
#endif

    // By default, flash image is expected to be the full size of flash (4MB)
    ImageSize = 0x400000;

    // By default, entry address is expected to be CPU1 default address.
    EntryAddr = CPU1_FLASH_ENTRY_POINT;

    //
    // Get device state and bank mode
    //
    deviceState = getDeviceState();
    bankMode = getBankMode();

    //
    // get user command through console.
    //
    command = uartGetPacket(&length, data);

    while (1)
    {
        //
        // Reset the statusCode.
        //
        statusCode.status = NO_COMMAND_ERROR;

#ifdef DFU_CPU1_APP
        //
        // DFU_CPU1
        //
        if (command == DFU_CPU1)
        {
            if (deviceState == HS_SE) 
            {
                statusCode.status = COMMAND_ERROR;
            } else 
            {
                //
                // loads application into CPU1 FLASH
                //
                uartBoot(1, bankMode, BootMode, CPU1_FLASH_ENTRY_POINT, ImageSize);
            }


            //
            // send the flash status packet and if NAK send again.
            //
            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }

            //
            // reply back with a message
            //
            char ch[] = "CPU1 image has been written to flash, please proceed to Run CPU1 or Reset CPU1(in flash boot mode) to start the new firmware.";
            uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t*)ch, sizeof(ch));
        }
        //
        // DFU_CPU3
        //
        else if (command == DFU_CPU3)
        {

            //
            // DFU is not compatible with HS-SE Devices and
            // cannot upgrade CPU3 firmware in Bank Mode 1
            //
            if ((deviceState == HS_SE) || (bankMode == Mode1)) 
            {
                statusCode.status = COMMAND_ERROR;
            } else 
            {
                //
                // loads application into CPU1 FLASH
                //
                uartBoot(3, bankMode, BootMode, CPU1_FLASH_ENTRY_POINT, ImageSize);
            }

            //
            // send the flash status packet and if NAK send again.
            //
            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }

            //
            // reply back with a message
            //
            char ch[] = "CPU3 image has been written to flash, please proceed to Run CPU1 or Reset CPU1(in flash boot mode) to start the new firmware.";
            uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t*)ch, sizeof(ch));
        }
        //
        // Run C29 CPU1 Flash Application
        //
        else if (command == RUN_CPU1)
        {
            return (EntryAddr);
        }
        //
        // Set C29 Flash Application Entry Address
        //
        else if (command == SET_APP_ENTRY_ADDRESS)
        {
            //
            // Selects which bank the CPU chooses to erase
            //
            EntryAddr = (uint32_t)(((uint32_t)data[1] << 16) | ((uint32_t)data[0]));

            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }
        }
        //
        // Set C29 Flash Application Load Address
        //
        else if (command == SET_APP_LOAD_ADDRESS)
        {

            LoadAddr = (uint32_t)(((uint32_t)data[1] << 16) | ((uint32_t)data[0]));

            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }
        }
        //
        // Set C29 Flash Application Size
        //
        else if (command == SET_APP_SIZE)
        {

            ImageSize = (uint32_t)(((uint32_t)data[1] << 16) | ((uint32_t)data[0]));

            if ((ImageSize > 0x400000) || (ImageSize == 0))
            {
                statusCode.status = INVALID_APP_SIZE;
            }

            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }
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
#endif /* defined(DFU_CPU1_APP) */

#ifdef KP_APP
        //
        // Load HSM_KEYS
        //
        if (command == HSM_KEYS)
        {
            if (0U != copyKeysToRAM(BootMode, LDA1_RAM_BASE))
            {
                statusCode.status = AUTHENTICATION_ERROR;
            }

            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }

            uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)0x200FA000U, MAX_SIZE_KP_LOG);
        }
#endif /* defined(KP_APP) */
#ifdef CP_APP
        //
        // Load SEC CFG Program Image
        //
        if (command == SEC_CFG_IMAGE)
        {

            //
            // Sec Cfg Program Logic
            //
            if (provisionSecCfgImg(BootMode, LDA1_RAM_BASE))
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
        // Load HSM Code Provisioning Flash Image
        //
        else if ((command == HSM_CP_FLASH_IMAGE) || (command == CPU1_CP_FLASH_IMAGE) || (command == CPU3_CP_FLASH_IMAGE))
        {

            //
            // Set error if CP command  is sent for HS-FS or if invalid bmode and CPU target are selected
            //
            if ((deviceState == HS_FS) || ((bankMode == Mode0) && (command == CPU3_CP_FLASH_IMAGE))) 
            {
                statusCode.status = COMMAND_ERROR;

            } else if (provisionApplicationImgToHSM(BootMode, LDA1_RAM_BASE))
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
            }
        }
#endif /* defined(CP_APP) */
#if defined(KP_APP) || defined(CP_APP)
        //
        // Load Ram-based HSMRt image
        //
        else if (command == HSM_RT_IMAGE)
        {
            if (0U != copyImageToRAM(BootMode, LDA7_RAM_BASE))
            {
                statusCode.status = AUTHENTICATION_ERROR;
            }

            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }

            System_init();

            char parsedVer[PARSED_VERSION_BUFFER_LENGTH];
            int32_t status = SystemP_SUCCESS;
            /* Cache Aligned Objects which will be passed to and from HSM & R5 */
            HsmVer_t hsmVer __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));

            memset(parsedVer, '\0', PARSED_VERSION_BUFFER_LENGTH);
            if (!HsmClient_getVersion(&gHSMClient, &hsmVer, SystemP_WAIT_FOREVER))
            {
                if (!HsmClient_parseVersion(&hsmVer, parsedVer))
                {
                    uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)parsedVer, PARSED_VERSION_BUFFER_LENGTH);
                }
            }
            else
            {
                char ch[] = "!! FAILED INSTALLATION OF KW !!";
                uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)ch, sizeof(ch));
            }
        }
#endif /* defined (KP_APP) || defined (CP_APP) */

        //
        // SYNC STATUS
        //
        else if (command == SYNC_STATUS)
        {
            char testString[] = "!!! UART FLASH KERNEL LIVE !!!";
            uint16_t testSize = sizeof(testString) / sizeof(*testString);
            uartSendDataPacket(GENERIC_DATA_PACKET, (uint8_t *)testString, testSize);

            //
            // send the flash status packet
            //
            while(uartSendFlashStatusPacket(command, &statusCode)){}
        }
        //
        // COMMAND_ERROR
        //
        else
        {
            statusCode.status = COMMAND_ERROR;

            while (uartSendFlashStatusPacket(command, &statusCode))
            {
            }
        }

        command = uartGetPacket(&length, data); // get next packet
    }

    //
    // Reset with WatchDog Timeout
    //

    //
    // driverlib, Watchdog reset enable = WDENINT->0 and WDOVERRIDE->0
    //
    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_RESET);

    //
    // enable the Watchdog
    //
    SysCtl_enableWatchdog();

    while (1)
    {
    }
}

uint32_t uartBootInit(uint32_t bootMode)
{
    uint32_t status = BROM_STATUS_OK;

    //
    // Enable Sysclk and wait for 20U cycles
    //
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_UART_A);
    CPU_BROM_delay_cycles(20U);

    //
    // UART Configurstion
    //
    UART_disableModule(UARTA_BASE); // Put UART to reset before configuring
    UART_setConfig(UARTA_BASE, DEVICE_SYSCLK_FREQ, UART_BOOT_BAUDRATE, UART_BOOT_CONFIG);

    UART_enableModule(UARTA_BASE);

    UART_enableFIFO(UARTA_BASE);

    uartConfigureGPIO(bootMode);

    return (status);
}

//
// uartGetPacket -  This routine receives the packet, returns the
//                 command and puts the data length in Uin16* length
//                 and data in uint16_t* data
//
uint16_t uartGetPacket(uint16_t *length, uint16_t *data)
{
    if (uartGetOnlyWordData() != FULL_PACKET_HEADER)
    {
        sendNAK();

        //
        // start packet error
        //
        return (100);
    }

    *length = uartGetOnlyWordData();

    //
    // checksum of command and data
    //
    checksum = 0;
    uint16_t command = uartGetOnlyWordData();

    int i = 0;
    for (i = 0; i < (*length) / 2; i++)
    {
        *(data + i) = uartGetOnlyWordData();
    }

#if checksum_enable
    uint16_t dataChecksum = checksum;
    if (dataChecksum != uartGetOnlyWordData())
    {
        sendNAK();

        //
        // checksum error
        //
        return (101);
    }
#endif /* checksum_enable */

    if (uartGetOnlyWordData() != FULL_PACKET_FOOTER)
    {
        sendNAK();

        //
        // end packet error
        //
        return (102);
    }

    sendACK();
    return (command);
}

//
//
// uartSendPacket -  Sends a Packet to the host which contains
//                  status in the data and address.  It sends the
//                  statusCode global variable contents.  It then waits
//                  for an ACK or NAK from the host.
//
uint16_t uartSendFlashStatusPacket(uint16_t command, FlashStatusCode *statusCode)
{
    int i;
    uint16_t packetSize = 12;
    uint16_t status = statusCode->status;
    uint16_t flashError = statusCode->flashAPIError;
    uint16_t *address = (uint16_t *)&(statusCode->address);
    uint16_t *fsmStatus = (uint16_t *)&(statusCode->flashAPIFsmStatus);

    uartaFlush();
    DEVICE_DELAY_US(100000);

    uartSendWord(FULL_PACKET_HEADER);
    uartSendWord(packetSize);

    checksum = 0;
    uartSendWord(command);
    uartSendWord(status);

    for (i = 0; i < 2; i++)
    {
        uartSendWord(*(address + i));
    }

    uartSendWord(flashError);

    for (i = 0; i < 2; i++)
    {
        uartSendWord(*(fsmStatus + i));
    }

    uartSendChecksum();
    uartSendWord(FULL_PACKET_FOOTER);

    //
    // Receive an ACK or NAK
    //
    return uartaGetACK();
}

uint16_t uartSendDataPacket(uint16_t command, uint8_t *data, uint16_t length)
{
    int i;

    uartaFlush();
    DEVICE_DELAY_US(100000);
    uartSendWord(FULL_PACKET_HEADER);
    uartSendWord(length);

    checksum = 0;
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
// uartaFlush - This routine flushes UARTA.
//
void uartaFlush(void)
{
    //
    // wait while TX is busy.
    //
    while (UART_isBusy(UARTA_BASE))
    {
    }
}

//
// uartaGetData   -   This routine fetches one byte from the UART-A
//                    port and echoes it back if checksum is enabled.
//
uint16_t uartGetData(void)
{
    // uint16_t wordData;
    uint16_t byteData;

    // wordData = 0x0000;
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
    checksum += byteData;
#endif

    return byteData;
}
//
// uartaGetData   -   This routine fetches one byte from the UART-A
//                    port and echoes it back if checksum is enabled.
//
uint8_t uartGetCPData(void)
{
    // uint16_t wordData;
    uint8_t byteData;

    // wordData = 0x0000;
    byteData = 0x00;

    //
    // Fetch the LSB and verify back to the host
    //
    byteData = UART_readChar(UARTA_BASE); // wait until RX is rdy then read.

    return byteData;
}

void uartSendCPData(uint8_t byteData)
{
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
    checksum += byteData;
#endif
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
    checksum += wordData + byteData;

    //
    // form the wordData from the MSB:LSB
    //
    wordData |= (byteData << 8);

    return wordData;
}

//
// uartSendByte - Sends a uint16_t byte.
//
void uartSendByte(uint8_t byte)
{
    //
    // send LSB of word, driverlib.
    //
    UART_writeChar(UARTA_BASE, byte);
    checksum += byte;
    uartaFlush();
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

    checksum += word & 0xFF;

    uartaFlush();

    //
    // send MSB of word, driverlib.
    //
    UART_writeChar(UARTA_BASE, ((word >> 8) & 0xFF));

    checksum += word >> 8 & 0xFF;

    uartaFlush();
}

//
// uartSendChecksum - Sends the Global checksum value
//
void uartSendChecksum()
{
    //
    // wait for SCIA_TX to be free and write LSB of checksum to it.
    //
    UART_writeChar(UARTA_BASE, (checksum & 0xFF));

    uartaFlush();

    //
    // wait for SCIA_TX to be free and write MSB of checksum to it.
    //
    UART_writeChar(UARTA_BASE, ((checksum >> 8) & 0xFF));

    uartaFlush();
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

    if (wordData != ACK)
    {
        return (1);
    }

    return (0);
}

//
// Unlock the GPIO configuration registers
//
static void uartInitGPIO(void)
{
    GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFFUL);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFFUL);
    GPIO_unlockPortConfig(GPIO_PORT_C, 0xFFFFFFFFUL);
}

//
// Configure GPIO Pins for SCL and SDA
//
static void uartConfigureGPIO(uint32_t bootMode)
{
    uint16_t gpioTXA;
    uint16_t gpioRXA;
    uint32_t gpioUARTTXPinConfig;
    uint32_t gpioUARTRXPinConfig;

    //
    // Disable pin locks and enable internal pullups
    //
    uartInitGPIO();

    switch (bootMode)
    {
    case UART_BOOT_ALT1:
        //
        // GPIO38 = UARTA_TX
        // GPIO39 = UARTA_RX
        //
        gpioTXA = 38U;
        gpioRXA = 39U;
        gpioUARTTXPinConfig = GPIO_38_UARTA_TX;
        gpioUARTRXPinConfig = GPIO_39_UARTA_RX;
        break;

    case UART_BOOT:
        //
        // GPI42 = UARTA_TX
        // GPI43 = UARTA_RX
        //
        gpioTXA = 42U;
        gpioRXA = 43U;
        gpioUARTTXPinConfig = GPIO_42_UARTA_TX;
        gpioUARTRXPinConfig = GPIO_43_UARTA_RX;
        break;

    case UART_BOOT_ALT3:
        //
        // GPIO38 = UARTA_TX
        // GPI03 = UARTA_RX
        //
        gpioTXA = 38;
        gpioRXA = 3;
        gpioUARTTXPinConfig = GPIO_38_UARTA_TX;
        gpioUARTRXPinConfig = GPIO_3_UARTA_RX;
        break;

    case UART_BOOT_ALT4:
        //
        // GPIO84 = UARTA_TX
        // GPI085 = UARTA_RX
        //
        gpioTXA = 84;
        gpioRXA = 85;
        gpioUARTTXPinConfig = GPIO_84_UARTA_TX;
        gpioUARTRXPinConfig = GPIO_85_UARTA_RX;
        break;

    case UART_BOOT_ALT2:
        //
        // GPIO2 = UARTA_TX
        // GPIO3 = UARTA_RX
        //
        gpioTXA = 2U;
        gpioRXA = 3U;
        gpioUARTTXPinConfig = GPIO_2_UARTA_TX;
        gpioUARTRXPinConfig = GPIO_3_UARTA_RX;
        break;
    }

    //
    // Set GPIO configuration for UART
    //
    GPIO_setPinConfig(gpioUARTTXPinConfig);
    GPIO_setPinConfig(gpioUARTRXPinConfig);

    //
    // Configure GPIOs as async pins
    //
    GPIO_setQualificationMode(gpioTXA, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(gpioRXA, GPIO_QUAL_ASYNC);
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