//#############################################################################
//
// FILE:   lab_main.c
//
// TITLE:  CLB eCAP Example
//
//! <h1> CLB eCAP Example Lab </h1>
//!
//! This example configures an EPWM to be measured by the CLB which will act 
//! as a basic eCAP.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - frequency
//! - period
//! - duty
//!
//
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Macros and Global Variables
//
volatile float32_t frequency = 0.0;
volatile float32_t period = 0.0;
volatile float32_t duty = 0.0;
volatile float32_t timesHLH[3];
volatile uint32_t regPush[4];
volatile uint32_t firstHigh  = 0;
volatile uint32_t firstLow   = 0;
volatile uint32_t secondHigh = 0;
volatile uint16_t ledCount = 0;
volatile uint16_t  gpioStatus = 0;

//
// Functions
//
__attribute__((interrupt("INT"))) void INT_myCLB0_ISR(void);

//
// Main
//
int main(void)
{
	//
    // CPU Initialization
    //
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();

    Interrupt_enable(INT_CLB1);
    Interrupt_register(INT_CLB1, &INT_myCLB0_ISR);
    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Local variables
    //
    uint32_t clockFreq = DEVICE_SYSCLK_FREQ;
    uint32_t firstHighCLB = 0;
    uint32_t firstLowCLB = 0;
    uint32_t secondHighCLB = 0;

	while(1)
	{
	    //
	    // Frequency, period, duty, and other timing calculations
	    // NOTE: 1 is added to each count because of zero-indexing counter
	    //
	    firstHighCLB = regPush[0] + 1;
        firstLowCLB = regPush[1] + 1;
        secondHighCLB = regPush[2] + 1;
	    frequency = (float32_t)(clockFreq) / ((float32_t)(firstHighCLB + firstLowCLB));
	    period = 1 / frequency;
        timesHLH[0] = (float32_t)(firstHighCLB) / (float32_t)(clockFreq);
        timesHLH[1] = (float32_t)(firstLowCLB) / (float32_t)(clockFreq);
        timesHLH[2] = (float32_t)(secondHighCLB) / (float32_t)(clockFreq);
        duty = timesHLH[0] * frequency * 100;
	}
}

__attribute__((interrupt("INT"))) void INT_myCLB0_ISR(void)
{
    CLB_readFIFOs(myCLB0_BASE, (uint32_t *)regPush);

    //
    // Toggle the GPIO pins; increase from 1000 to slow down the toggle
    //
    ledCount = (ledCount + 1) % (1000);

    if(ledCount == 0)
    {
        if(gpioStatus)
        {
           gpioStatus = 0;
        }
        else
        {
           gpioStatus = 1;
        }
        GPIO_writePin(myBoardLED1_GPIO, gpioStatus);
    }

    CLB_clearInterruptTag(myCLB0_BASE);
}

//
// End of File
//
