//#############################################################################
//
// FILE:   uart_ex4_echoback.c
//
// TITLE:  UART echoback example.
//
//! \addtogroup driver_example_list
//! <h1>UART Echoback</h1>
//!
//!  This test receives and echo-backs data through the UART A port.
//!
//!  A terminal such as 'putty' can be used to view the data from
//!  the UART and to send information to the UART. Characters
//!  received by the UART port are sent back to the host.
//!
//!  \b Running \b the \b Application
//!  Open a COM port with the following settings using a terminal:
//!  -  Find correct COM port
//!  -  Bits per second = 115200
//!  -  Data Bits = 8
//!  -  Parity = None
//!  -  Stop Bits = 1
//!  -  Hardware Control = None
//!
//!  The program will print out a greeting and then ask you to
//!  enter a character which it will echo back to the terminal.
//!
//!  \b Watch \b Variables \n
//!  - None
//!
//! \b External \b Connections \n
//!  Connect the UARTA port to a PC via a transceiver and cable.
//!  - GPIO43 is UARTA RX
//!  - GPIO42 is UARTA TX
//!
//! Note: Avoid keeping the memory browser open while the execution
//! is in progress.
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

//
// Globals
//
uint8_t promptMsg[22] = "\nEnter a character : ";

//
// Function Prototypes
//
void UART_RX_IntHandler(void);

//
// Main
//
int main(void){

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Display typing prompt
    //
    UART_writeCharArray(myUART0_BASE, promptMsg, 21);

    // Loop forever echoing data through the UART.
    //
    while(1)
    {
        ;
    }
}


void UART_RX_IntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrupt status.
    //
    ui32Status = UART_getInterruptStatus(myUART0_BASE, UART_RAW_INT);

    //
    // Clear the asserted interrupts.
    //
    UART_clearInterruptStatus(myUART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(UART_isDataAvailable(myUART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        UART_writeCharNonBlocking(myUART0_BASE,
                                  UART_readCharNonBlocking(myUART0_BASE));
    }

    UART_writeCharArray(myUART0_BASE, promptMsg, 21);

    //
    // Clear UART global interrupt flag
    //
    UART_clearGlobalInterruptFlag(myUART0_BASE);

}

//
// End of File
//