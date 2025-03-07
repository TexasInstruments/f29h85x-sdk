//#############################################################################
//
// FILE:   spi_ex3_external_loopback.c
//
// TITLE:  SPI Digital Loopback without using FIFOs and Interrupts
//
//! \addtogroup driver_example_list
//! <h1>SPI Digital External Loopback without FIFO Interrupts</h1>
//!
//! This program uses the external loopback between two SPI modules. Both
//! the SPI FIFOs and interrupts are not used in this example. SPIA is
//! configured as a peripheral and SPI B is configured as controller. This example
//! demonstrates full duplex communication where both controller and peripheral transmits
//! and receives data simultaneously.
//!
//!
//! \b External \b Connections \n
//!  -GPIO16 and GPIO63 - SPIPICO
//!  -GPIO17 and GPIO25 - SPIPOCI
//!  -GPIO34 and GPIO26 - SPICLK
//!  -GPIO61 and GPIO27 - SPISTE
//!
//! \b Watch \b Variables \n
//!  - \b TxData_SPIA - Data send from SPIA (peripheral)
//!  - \b TxData_SPIB - Data send from SPIB (controller)
//!  - \b RxData_SPIA - Data received by SPIA (peripheral)
//!  - \b RxData_SPIB - Data received by SPIB (controller)
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

    uint8_t i;

    uint16_t TxData_SPIA[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    uint16_t RxData_SPIA[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint16_t TxData_SPIB[] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
    uint16_t RxData_SPIB[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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
    for(i = 0; i < 16; i++)
    {
        //
        // Set the peripheral TX buffer.
        //
        SPI_writeDataNonBlocking(SPIA_BASE, TxData_SPIA[i]);

        //
        // Set the controller TX buffer. This triggers the data transmission
        //
        SPI_writeDataNonBlocking(SPIB_BASE, TxData_SPIB[i]);

        //
        // Read the received data
        //
        RxData_SPIA[i] = SPI_readDataBlockingNonFIFO(SPIA_BASE);
        RxData_SPIB[i] = SPI_readDataBlockingNonFIFO(SPIB_BASE);

        //
        // Check the received data
        //
        if(RxData_SPIA[i] != TxData_SPIB[i])
        {
            ESTOP0;
        }
        if(RxData_SPIB[i] != TxData_SPIA[i])
        {
            ESTOP0;
        }
    }

    //
    // Loop forever
    //
    while(1){
        ;
    }
}

//
// End of File
//