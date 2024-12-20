//#############################################################################
//
// FILE:   uart_ex1_loopback.c
//
// TITLE:  UART Loopback
//
//! \addtogroup driver_example_list
//! <h1>UART Loopback</h1>
//!
//! Simple UART internal loopback example
//!
//! The sent data looks like this: \n
//!  00 01 02 03 .... FE FF 00
//!
//! This pattern is repeated forever.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b sData - Data to send
//!  - \b rData - Received data
//!
//! Note: Avoid keeping the memory browser open while the execution
//! is in progress.
//
//#############################################################################

//
// Included Files
//
#include "board.h"


uint8_t sData = 1;
int32_t rData = 0;

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


    // Loop forever echoing data through the UART.
    //
    while(1)
    {

        // Transmit data
        UART_writeChar(myUART0_BASE, sData);

        // Block until data is received and then return it
        rData = UART_readChar(myUART0_BASE);

        // Check received data against sent data
        if(rData != sData)
        {
            // Something went wrong. rData doesn't contain expected data.
            ESTOP0;
        }

        sData++;
    }
}

//
// End of File
//