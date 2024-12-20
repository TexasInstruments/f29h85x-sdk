//#############################################################################
//
// FILE:    rtdma_academy_lab.c
//
// TITLE:   RTDMA Academy Lab 
//
//! \addtogroup rtdma_example_list
//! <h1> RTDMA Academy Lab </h1>
//!
//! This example demonstrates how to use the RTDMA to service the ADC in a
//! real-time processing application. The ePWM and ADC modules generate and sample
//! a PWM waveform. The DMA is used to store the ADC samples in a ping pong buffer,
//! so sample groups can be simultaneously processed by the CPU in an ISR.
//!
//! \b External \b Connections \n
//! - ADCINA0 (AIO160) to EPWM1_A (GPIO0)
//!
//! \b Watch \b Variables \n
//! - \b PingPongState - Ping-pong buffer state.
//! - \b LedCtr - Counter to slow LED toggling.
//! - \b TaskDelayUs - Delay to simulate data processing task.
//! - \b OverCnt - Counter to store DMA overwrites.
//! - \b TimDiff - To measure the DMA ISR time.
//! - \b AdcBufRaw - Ping-pong buffer.
//!
//
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "inc/hw_memmap.h"

#define ADC_BUF_LEN 50              // Buffer length.

__attribute__((location(LDA0_RAM_BASE))) volatile uint32_t AdcBufRaw[2*ADC_BUF_LEN]; // Place ping-pong buffer in memory.

volatile uint16_t AdcBuf[ADC_BUF_LEN];       // Buffer for CCS plotting.
volatile uint16_t PingPongState = 0;         // Ping-pong buffer state.
volatile uint16_t LedCtr = 0;                // Counter to slow LED toggling.
volatile uint16_t TaskDelayUs = 0;           // Delay to simulate data processing task.
volatile uint16_t OverCnt = 0;               // Counter to store DMA overwrites.
volatile uint32_t TimDiff;                   // Variable to measure the DMA ISR time.

const void *AdcAddr = (void*)(ADCARESULT_BASE + ADC_O_RESULT0);
const void *AdcRawBufAddr = (void*)AdcBufRaw;

void dma1_Ch1ISR(void)
{
    // Start and reload the timer.
    CPUTimer_startTimer(myCPUTIMER0_BASE);

    volatile uint16_t *AdcBufPtr = AdcBuf;
    volatile uint32_t *AdcBufRawPtr;
    uint16_t i;

    // Blink LED at about 1Hz. ISR is occurring every 1ms.
    if (LedCtr++ >= 1000) {
        GPIO_togglePin(myBoardLED1_GPIO);
        LedCtr = 0;
    }

    if (PingPongState == 0) {
        // Set DMA address to start at ping buffer.
        DMA_configAddresses(myRTDMA0_BASE,
                            (const void *)AdcBufRaw,
                            (const void *)(ADCARESULT_BASE + ADC_O_RESULT0));

        // Fill AdcBuf with contents of the pong buffer.
        AdcBufRawPtr = AdcBufRaw + ADC_BUF_LEN;
        for (i = 0; i < ADC_BUF_LEN; i++) {
            *(AdcBufPtr++) = *(AdcBufRawPtr++);
        }
    } else {
        // Set DMA address to start at pong buffer.
        DMA_configAddresses(myRTDMA0_BASE,
                            (const void *)(AdcBufRaw + ADC_BUF_LEN),
                            (const void *)(ADCARESULT_BASE + ADC_O_RESULT0));

        // Fill AdcBuf with contents on the ping buffer.
        AdcBufRawPtr = AdcBufRaw;
        for (i = 0; i < ADC_BUF_LEN; i++) {
            *(AdcBufPtr++) = *(AdcBufRawPtr++);
        }
    }

    // Toggle PingPongState.
    PingPongState ^= 1;

    // Delay to simulate more data processing.
    for (i = 0; i < TaskDelayUs; i++) {
        DEVICE_DELAY_US(1);
    }

    // Get the time stamp and check to see if interrupt completed within the
    // required time frame of 1ms. Don't worry about overflows.
    CPUTimer_stopTimer(myCPUTIMER0_BASE);
    TimDiff = 0xFFFFFFFF - CPUTimer_getTimerCount(myCPUTIMER0_BASE);
    if (TimDiff >= ((uint32_t)(0.001*DEVICE_SYSCLK_FREQ))) {
        OverCnt++;
    }
}

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
    // Loop.
    //

    for(;;) {
        // Do nothing.
        NOP;
    }
}

//
// End of File
//