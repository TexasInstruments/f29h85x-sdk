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