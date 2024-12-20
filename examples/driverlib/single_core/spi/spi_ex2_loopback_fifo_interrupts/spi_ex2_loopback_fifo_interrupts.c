//#############################################################################
//
// FILE:   spi_ex2_loopback_fifo_interrupt.c
//
// TITLE:  SPI Digital Loopback with FIFO Interrupts
//
//! \addtogroup driver_example_list
//! <h1>SPI Digital Loopback with FIFO Interrupts</h1>
//!
//! This program uses the internal loopback test mode of the SPI module. Both
//! the SPI FIFOs are used, and SPI RX interrupt is used.
//!
//! A stream of data is sent and then compared to the received stream.
//! The sent data looks like this: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  FFFE FFFF \n
//!  FFFF 0000 \n
//!  etc.. \n
//! This pattern is repeated forever.
//!
//! Note : The SPI peripheral generates level interrupts, which should be
//! cleared in ISR to avoid generating false pending interrupt on clear edge,
//! followed by some wait cycles
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b sData - Data to send
//!  - \b rData - Received data
//!  - \b rDataPoint - Used to keep track of the last position in the receive
//!    stream for error checking
//!
//
//#############################################################################

//
// Included Files
//
#include "board.h"

//
// Globals
//
uint16_t sData[2];                  // Send data buffer
uint16_t rData[2];                  // Receive data buffer
uint16_t rDataPoint = 0;            // To keep track of where we are in the
                                    // data stream to check received data

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
    // Initialize the data buffers
    //
    for(i = 0; i < 2; i++)
    {
        sData[i] = i;
        rData[i]= 0;
    }

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop forever
    //
    while(1)
    {
        //
        // Send data & increment for next cycle
        //
        for(i = 0; i < 2; i++)
        {
            SPI_writeDataNonBlocking(mySPI0_BASE, sData[i]);
            sData[i] = sData[i] + 1;
        }

        DEVICE_DELAY_US(20);
    }
}

//
// SPI A Receive FIFO ISR
//
void spiRxFIFOISR(void)
{
    uint8_t i;

    //
    // Read data
    //
    for(i = 0; i < 2; i++)
    {
        rData[i] = SPI_readDataNonBlocking(mySPI0_BASE);
    }

    //
    // Check received data
    //
    for(i = 0; i < 2; i++)
    {
        if(rData[i] != ((uint16_t)(rDataPoint + i)))
        {
            // Something went wrong. rData doesn't contain expected data.
            ESTOP0;
        }
    }

    rDataPoint++;

    //
    // Clear interrupt flag
    //
    SPI_clearInterruptStatus(mySPI0_BASE, SPI_INT_RXFF);
    __asm(" NOP #7");

    //
    // Clear PIPE interrupt flag
    //
    Interrupt_clearFlag(INT_SPIA_RX);
    __asm(" NOP #7"); 
}

//
// End of File
//