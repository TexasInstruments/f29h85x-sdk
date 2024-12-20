//#############################################################################
//
// FILE:   rtdma_ex2_mem_transfer_mpu.c
//
// TITLE:  RTDMA Example
//
//! \addtogroup driver_example_list
//! <h1> RTDMA Transfer with MPU </h1>
//!
//!  This example uses one RTDMA channel to transfer data from a buffer to 
//!  another buffer in RAM. The example triggers the DMA channel repeatedly
//!  until the transfer of 16 bursts (where each burst is 4 8-bit words)
//!  has been completed. When the whole transfer is complete it will trigger
//!  the DMA interrupt. 
//!
//!  The RTDMA1 MPU is enabled in this example to configure a predefined region
//!  that dictates read and write access to the transmit buffer and
//!  receive buffer. When a DMA channel attempts to access data at an illegal 
//!  address, MPU outputs a security violation. Any faults in the interface are
//!  communicated to the Error Aggregator module which are sent to the Error 
//!  Signaling Module (ESM) where the errors are latched and RTDMA access is blocked.
//!
//!  Configured Address Ranges:
//!  MPU Region Start Address - 0x200E0000
//!  MPU Region End Address   - 0x200E0FFF
//!  TxData Start Address     - 0x200E0100
//!  TxData End Address       - 0x200E013F	
//!  RxData Start Address     - 0x200E0FDC
//!  RxData End Address       - 0x200E101B	
//!
//!  
//!  \b Watch \b Variables \n
//!  - \b TxData            - Data to send
//!  - \b RxData            - Received data
//!  - \b status            - When set to 0, transfer is not done. When set to 1, transfer successful. When set to 2, transfer is not successful (error).
//!  - \b error_location_WR - Address where write error occurs
//!  - \b error_location_RD - Address where read error occurs
//!
//
//#############################################################################

//
// Included Files
//
#include "board.h"
#include "bitfield_structs.h"
#include "inc/hw_error_aggregator.h"

//
// Globals
//
__attribute__((location(0x200E0100))) volatile uint32_t TxData[16]; // Transmit data buffer
__attribute__((location(0x200E0FDC))) volatile uint32_t RxData[16]; // Receive data buffer

volatile uint16_t status;
volatile uint32_t error_location_WR, error_location_RD;

const void *srcAddr = (const void *)TxData;
const void *destAddr = (const void *)RxData;

//
// Function Prototypes
//
void error();

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
    // Board Initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // User specific code
    // Initialize the data buffers
    //
    for(i = 0; i < 16; i++)
    {
        TxData[i] = i;
        RxData[i] = 0;
    }

    // Start DMA channel
    DMA_startChannel(myRTDMA1Ch0_BASE);

    status = 0;           // Test is not done yet

    while(!status)        // Wait until the DMA transfer is complete
    {
        DMA_forceTrigger(myRTDMA1Ch0_BASE);
        SysCtl_delay(10);
        if (status == 2) // Check for data integrity at the end of the transfer. When data is not received correctly, the error function is called.
        {
            error(); 
        }
    }

    //
    // When the DMA transfer is complete the program will stop here. Code will never reach this line due to NMI error.
    //
    ESTOP0;
}

//
// error - Error Function which will halt the debugger
//
void error(void)
{
    ESTOP0;  // Test failed (as expected)!! Stop!
    for (;;);
}

//
// DMA Channel ISR
//
void INT_myRTDMA1Ch0_ISR(void)
{
    uint16_t i;

    DMA_stopChannel(myRTDMA1Ch0_BASE);

    for(i = 0; i < 16; i++)
    {
        //
        // check for data integrity
        //
        if (RxData[i] != i)
        {
            status = 2; // Test resulted in an error. Refer to the Error Aggregator for specific RTDMA error source. 
            return; // Exit DMA ISR 
        }
    }

    status = 1; // Test done. Code will never reach this line due to NMI error.
    return;
}

// NMI ISR
void myNMI_ISR(void) 
{
    //
    // Service the highest priority active RTDMA error event that caused the interrupt. 
    //
    if(ESM_getInterruptStatus(ESMCPU1_BASE,ESM_EVENT_ErrorAggregator_RTDMA1_HPERR))
    {

        //
        // Determine and store the specific address where the high priority error occurs and on which RTDMA interface port. It is also 
        // possible to get the low priority address and error type, if needed, using the ErrorAggregator_getRtdmaErrorInfo() function.
        //
        error_location_WR = ErrorAggregatorRegs.RTDMA1_DW_HIGHPRIO_ERROR_ADDRESS;
        error_location_RD = ErrorAggregatorRegs.RTDMA1_DR_HIGHPRIO_ERROR_ADDRESS;
        
        //
        // Clear the peripheral error flag
        //
        DMA_clearErrorFlag(myRTDMA1Ch0_BASE);

        //
        // Clear Error Aggregator error type flags on both RTDMA buses to allow further high priority errors
        //
        ErrorAggregator_clearRtdmaError(ERRORAGGREGATOR_BASE, EA_SRC_RTDMA1);

        //
        // Clear the raw status and deassert the level interrupt.
        //
        ESM_clearRawInterruptStatus(ESMCPU1_BASE,ESM_EVENT_ErrorAggregator_RTDMA1_HPERR);
        
        //
        // Acknowledge the High priority interrupt (NMI).
        // In case there are enabled error events pending then a new pulse is 
        // generated and level interrupt remains asserted, else no new pulse is 
        // generated.
        //
        ESM_ackInterrupt(ESMCPU1_BASE, ESM_HIGH_PRIORITY_ERROR_INTERRUPT);
    }

}

