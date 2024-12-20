//#############################################################################
//
// FILE:   spi_ex4_external_loopback_fifo_interrupt.c
//
// TITLE:  SPI Digital Loopback with FIFO Interrupts
//
//! \addtogroup driver_example_list
//! <h1>SPI Digital External Loopback with FIFO Interrupts</h1>
//!
//! This program uses the external loopback between two SPI modules. Both
//! the SPI FIFOs are used. SPI-A is configured as a peripheral and receives
//! data from SPI-B which is configured as a controller. SPI-A RX interrupt
//! is used.
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
//!  -GPIO16 and GPIO63 - SPIPICO
//!  -GPIO17 and GPIO25 - SPIPOCI
//!  -GPIO34 and GPIO26 - SPICLK
//!  -GPIO61 and GPIO27 - SPISTE
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
volatile uint16_t sData[2];                 // Send data buffer
volatile uint16_t rData[2];                 // Receive data buffer
volatile uint16_t rDataPoint = 0;           // To keep track of where we are in the
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
            SPI_writeDataNonBlocking(SPIB_BASE, sData[i]);
            sData[i] = sData[i] + 1;
        }

        DEVICE_DELAY_US(20);
    }
}

//
// SPI A Receive FIFO ISR
//
void spiaRxFIFOISR(void)
{
    uint8_t i;

    //
    // Read data
    //
    for(i = 0; i < 2; i++)
    {
        rData[i] = SPI_readDataNonBlocking(SPIA_BASE);
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
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
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