//#############################################################################
//
// FILE:   spi_ex1_loopback.c
//
// TITLE:  SPI Digital Loopback
//
//! \addtogroup driver_example_list
//! <h1>SPI Digital Loopback</h1>
//!
//! This program uses the internal loopback test mode of the SPI module. This
//! is a very basic loopback that does not use the FIFOs or interrupts. A
//! stream of data is sent and then compared to the received stream.
//! The pinmux and SPI modules are configured through the sysconfig file.
//!
//! The sent data looks like this: \n
//!  0000 0001 0002 0003 0004 0005 0006 0007 .... FFFE FFFF 0000
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
//
//#############################################################################

//
// Included Files
//
#include "board.h"

//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    uint16_t sData = 0;                  // Send data
    uint16_t rData = 0;                  // Receive data

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
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    while(1)
    {
        // Transmit data
        SPI_writeDataNonBlocking(mySPI0_BASE, sData);

        // Block until data is received and then return it
        rData = SPI_readDataBlockingNonFIFO(mySPI0_BASE);

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