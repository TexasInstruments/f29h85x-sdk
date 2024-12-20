//#############################################################################
//
// FILE:   uart_ex2_loopback_fifo_interrupts.c
//
// TITLE:  UART Loopback with Interrupt
//
//! \addtogroup driver_example_list
//! <h1>UART Loopback with Interrupt</h1>
//!
//! UART internal loopback w/ interrupt example
//! Receive interrupt with FIFO is used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The sent data looks like this: \n
//!  00 01 \n
//!  01 02 \n
//!  02 03 \n
//!  .... \n
//!  FE FF \n
//!  FF 00 \n
//!  etc.. \n
//!  The pattern is repeated forever.
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

//
// Globals
//
uint8_t sData[2];                  // Send data buffer
int32_t rData[2];                  // Receive data buffer


//
// Main
//
int main(void)
{
    uint8_t i;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Initialize receive data buffer
    //
    for(i = 0; i < 2; i++)
    {
        rData[i]= 0;
    }

    //
    // Initialize sent data buffer
    // Put a character to show start of example.
    //
    for(i = 0; i < 2; i++)
    {
        sData[i] = i;
        UART_writeChar(myUART0_BASE, sData[i]);
    }

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    while(1)
    {
        ;
    }
}

//
// UART Receive FIFO ISR
//
void INT_myUART0_ISR(void){

    uint32_t ui32Status;
    uint16_t i = 0;

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
        rData[i++] = UART_readCharNonBlocking(myUART0_BASE);
    }

    //
    // Check received data
    //
    for(i = 0; i < 2; i++)
    {
        if(rData[i] != sData[i])
        {
            // Something went wrong. rData doesn't contain expected data.
            ESTOP0;
        }
    }

    //
    // Increment & send data for next cycle
    //
    for(i = 0; i < 2; i++)
    {
        sData[i] = (sData[i] + 1);
        UART_writeCharNonBlocking(myUART0_BASE, sData[i]);
    }


    // Clear UART global interrupt flag
    UART_clearGlobalInterruptFlag(myUART0_BASE);

}

//
// End of File
//