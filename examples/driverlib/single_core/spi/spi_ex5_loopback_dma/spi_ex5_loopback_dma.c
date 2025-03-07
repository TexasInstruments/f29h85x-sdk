//#############################################################################
//
// FILE:   spi_ex5_loopback_dma.c
//
// TITLE:  SPI Digital Loopback with DMA
//
//! \addtogroup driver_example_list
//! <h1>SPI Digital Loopback with DMA</h1>
//!
//! This program uses the internal loopback test mode of the SPI module. Both
//! DMA interrupts and the SPI FIFOs are used. When the SPI transmit FIFO has
//! enough space (as indicated by its FIFO level interrupt signal), the DMA
//! will transfer data from global variable sData into the FIFO. This will be
//! transmitted to the receive FIFO via the internal loopback.
//!
//! When enough data has been placed in the receive FIFO (as indicated by its
//! FIFO level interrupt signal), the DMA will transfer the data from the FIFO
//! into global variable rData.
//!
//! When all data has been placed into rData, a check of the validity of the
//! data will be performed in one of the DMA channels' ISRs.
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
// Globals
//
volatile uint16_t sData[128];                // Send data buffer
volatile uint16_t rData[128];                // Receive data buffer

const void *destAddr = (const void *)rData;
const void *srcAddr = (const void *)sData;

volatile uint8_t done = 0;         // Flag to set when all data transferred

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
    // Board initialization from SysConfig
    //
    Board_init();


    //
    // Initialize the data buffers
    //
    for(i = 0; i < 128; i++)
    {
        sData[i] = i+1;
        rData[i]= 0;
    }

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start the DMA channels
    //
    DMA_startChannel(mySPI0_TX_DMA_BASE);
    DMA_startChannel(mySPI0_RX_DMA_BASE);

    //
    // Wait until the DMA transfer is complete
    //
    while(!done)
    {
        ;
    }

    //
    // When the DMA transfer is complete the program will stop here
    //
    ESTOP0;
}

//
// DMA Channel 5 ISR
//
void INT_mySPI0_TX_DMA_ISR(void)
{
    DMA_stopChannel(mySPI0_TX_DMA_BASE);
    return;
}

//
// DMA Channel 6 ISR
//
void INT_mySPI0_RX_DMA_ISR(void)
{
    uint8_t i;

    //
    //  Wait for SPI transmission to complete
    //
    while(SPI_isBusy(mySPI0_BASE)){
        ;
    }

    DMA_stopChannel(mySPI0_RX_DMA_BASE);

    //
    // Check for data integrity
    //
    for(i = 0; i < 128; i++)
    {
        if (rData[i] != i+1)
        {
            // Something went wrong. rData doesn't contain expected data.
            ESTOP0;
        }
    }

    done = 1;
    return;
}

//
// End of File
//