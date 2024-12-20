//#############################################################################
//
// FILE:   lin_ex5_sci_dma_single_buffer.c
//
// TITLE:  LIN SCI MODE (SIngle Buffer) Internal Loopback with DMA
//
//! \addtogroup driver_example_list
//! <h1> LIN SCI MODE (Single Buffer) Internal Loopback with DMA </h1>
//!
//! This example configures the LIN module in SCI mode for internal loopback
//! with the use of the DMA. The LIN module performs as SCI with a set
//! character and frame length in single-buffer compatibility mode. When the
//! transmit buffer i.e. the SCITD register is free, the DMA will transfer
//! data from global variable sData into this register. Once the received
//! buffer, i.e. the SCIRD register contains data, the DMA will transfer the
//! data into the global variable rdata.
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
volatile uint8_t sData[128];
volatile uint8_t rData[128];
volatile uint16_t done = 0;         // Flag to set when all data transfered

const void *myLIN0_RX_DMA_ADDRESS = ((uint8_t *)(myLIN0_BASE + LIN_O_SCIRD));
const void *myLIN0_TX_DMA_ADDRESS = ((uint8_t *)(myLIN0_BASE + LIN_O_SCITD));

const void *destAddr = (const void *)rData;
const void *srcAddr = (const void *)sData;

//
// Main
//
int main(void)
{
    uint16_t i;

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
    for(i = 0; i < 128; i++)
    {
       sData[i]= i+1;
       rData[i]= 0;
    }

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Wait for the SCI receiver to be idle
    //
    while(!LIN_isSCIReceiverIdle(myLIN0_BASE));

    //
    // Wait until space is available in the transmit buffer.
    //
    while(!LIN_isSCISpaceAvailable(myLIN0_BASE)){
        ;
    }

    //
    // Start the DMA channels
    //
    DMA_startChannel(myLIN0_TX_DMA_BASE);
    DMA_startChannel(myLIN0_RX_DMA_BASE);

    //
    // Initiate transfer by forcing a TX DMA trigger.
    //
    DMA_forceTrigger(myLIN0_TX_DMA_BASE);


    //
    // Wait until the DMA transfer is complete
    //
    while(!done){
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
void dmaTxIsr(void)
{
    DMA_stopChannel(myLIN0_TX_DMA_BASE);
    return;
}

//
// DMA Channel 6 ISR
//
void dmaRxIsr(void)
{
    uint16_t i;
    DMA_stopChannel(myLIN0_RX_DMA_BASE);

    //
    //Check for data integrity
    //
    for(i=0; i<128; i++)
    {
        if(rData[i] != i+1)
        {
           //Something went wrong, rdata doesn't contain expected data.
           ESTOP0;
        }
    }

    done = 1;
    return;
}

//
// End of File
//