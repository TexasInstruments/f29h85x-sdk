//#############################################################################
//
// FILE:  led_blinky_cpu1.c
//
// TITLE: FOTA LED Blinky Example
//
//#############################################################################
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

//
// Included Files
//
#include "board.h"
#include "f29h85x_kernel_commands_cpu1.h"
#include "uart.h"

//
// Defines
//
#define CPU3_RESET_VECTOR   0x10401000U
#define CPU3_NMI_VECTOR     0x10401040U


//
// Entry point to FOTA functions in SBL
//
#define CPU1_FOTA_ENTRY_POINT 0x1001F000
#define CPU3_FOTA_ENTRY_POINT 0x1001F200
#define CPU1_SECURE_FOTA_ENTRY_POINT 0x1001F400
#define CPU3_SECURE_FOTA_ENTRY_POINT 0x1001F600
#define HSM_SECURE_FOTA_ENTRY_POINT 0x1001F800
#define SECCFG_PROGRAM_ENTRY_POINT 0x1001FA00

//
// Function definitions
//
uint16_t uartGetPacket(uint16_t* length, uint16_t* data);
uint16_t uartGetOnlyWordData(void);
void sendACK(void);
void sendNAK(void);
void uartaFlush(void);
uint32_t CPU_jumpToAddr(uint32_t jumpAddr);

//
// Globals
//
uint16_t command;
uint16_t length;
uint16_t data[10];
uint8_t ledBit = 0;
FlashStatusCode statusCode;
uint16_t CHECKSUM;

//
// Main
//

int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop Forever
    //
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
        // Reset the statusCode.
        //
        statusCode.status = NO_COMMAND_ERROR;

        //
        // DFU_CPU1
        //
        if(command == DFU_CPU1)
        {
            // 
            // Jump to CPU 1 FOTA function
            //
            [[clang::noinline]] CPU_jumpToAddr(CPU1_FOTA_ENTRY_POINT); 

            command = 0; 

        }
        else if(command == DFU_CPU3)
        {
            // 
            // Jump to CPU 3 FOTA function
            //
            [[clang::noinline]] CPU_jumpToAddr(CPU3_FOTA_ENTRY_POINT); 

            command = 0; 

        } else if (command == HSM_CP_FLASH_IMAGE)
        {
            // 
            // Jump to HSM Secure FOTA function
            //
            [[clang::noinline]] CPU_jumpToAddr(HSM_SECURE_FOTA_ENTRY_POINT); 

            command = 0; 
            
        }  else if (command == CPU1_CP_FLASH_IMAGE)
        {
            // 
            // Jump to CPU1 Secure FOTA function
            //
            [[clang::noinline]] CPU_jumpToAddr(CPU1_SECURE_FOTA_ENTRY_POINT); 

            command = 0; 
            
        }  else if (command == CPU3_CP_FLASH_IMAGE)
        {
            // 
            // Jump to CPU3 Secure FOTA function
            //
            [[clang::noinline]] CPU_jumpToAddr(CPU3_SECURE_FOTA_ENTRY_POINT); 

            command = 0; 
            
        } 
        
        else if (command == SEC_CFG_IMAGE)
        {
            // 
            // Jump to SECCFG Programming function
            //
            [[clang::noinline]] CPU_jumpToAddr(SECCFG_PROGRAM_ENTRY_POINT); 
            // UART_clearInterruptStatus(UARTA_BASE, UART_GLB_INT_CLR_INT_FLG_CLR);

            command = 0; 
            
        } 
    }
}

//
// This ISR will catch cmd packets from the host
//
void INT_myUART0_ISR(void) 
{
    //
    // Get the interrupt status.
    //
    uint32_t ui32Status;
    ui32Status = UART_getInterruptStatus(myUART0_BASE, UART_RAW_INT);

    //
    // Clear the asserted interrupts.
    //
    UART_clearInterruptStatus(myUART0_BASE, ui32Status);
    command = uartGetPacket(&length, data);
    // Clear UART global interrupt flag
    UART_clearGlobalInterruptFlag(myUART0_BASE);
    
}

//
// ISR to blink LED
//
void INT_myCPUTIMER1_ISR(void)
{
    ledBit = ledBit ^ 1;
    GPIO_writePin(CPU1_LED, ledBit);
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
// Function used to branch to an address
//
uint32_t CPU_jumpToAddr(uint32_t jumpAddr)
{
    uint32_t test = jumpAddr;
    asm(" MV A7, D0");
    asm(" LB A7");
    return test;

}

//
// End of File
//