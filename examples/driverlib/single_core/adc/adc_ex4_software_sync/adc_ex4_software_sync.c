//###########################################################################
//
// FILE:   adc_ex4_soc_software_sync.c
//
// TITLE:  ADC synchronous software triggering
//
//! \addtogroup driver_example_list
//! <h1> ADC Synchronous SOC Software Force (adc_soc_software_sync)</h1>
//!
//! This example converts some voltages on ADCA and ADCC using input 5 of the
//! input X-BAR as a software force. Input 5 is triggered by toggling GPIO0,
//! but any spare GPIO could be used. This method will ensure that both ADCs
//! start converting at exactly the same time.
//!
//! \b External \b Connections \n
//!  - A0, A1, C0, C1 pins should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//! - \b myADC0Result0 \b: a digital representation of the voltage on pin A0\n
//! - \b myADC0Result1 \b: a digital representation of the voltage on pin A1\n
//! - \b myADC1Result0 \b: a digital representation of the voltage on pin C0\n
//! - \b myADC1Result1 \b: a digital representation of the voltage on pin C1\n
//!
//
//#############################################################################
//
//
// $Copyright:
//#############################################################################
//

//
// Included Files
//
#include "board.h"

//
// Globals
//
uint16_t myADC0Result0;
uint16_t myADC0Result1;
uint16_t myADC1Result0;
uint16_t myADC1Result1;

int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Board Initialization
    // - Write ADC configurations and power up the ADC for both ADC A and ADC C
    // - Setup GPIO 0 to trigger input XBAR line 5.  GPIO0 is used
    //   as an example, but any spare GPIO could be used. The
    //   physical GPIO pin should be allowed to float, since the
    //   code configures it as an output and changes the value.
    // - Setup ADC acquisition window and compare values
    //  - Signal Mode           : single-ended
    //  - Conversion Resolution : 12-bit;
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Convert, wait for completion, and store results
        //

        //
        // Toggle GPIO0 in software.  This will cause a trigger to
        // both ADCs via input XBAR, line 5.
        //
        GPIO_writePin(0U, 1U); // Set pin
        GPIO_writePin(0U, 0U); // Clear pin

        //
        // Wait for ADCA to complete, then acknowledge the flag.
        // Since both ADCs are running synchronously, it isn't necessary
        // to wait for completion notification from both ADCs
        //
        while(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1) == 0U);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        myADC0Result0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        myADC0Result1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
        myADC1Result0 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);
        myADC1Result1 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1);

        //
        // At this point, conversion results are stored in
        // myADC0Result0, myADC0Result1, myADC1Result0, and myADC1Result1
        //

        //
        // Software breakpoint, hit run again to get updated conversions
        //
        ESTOP0;

    }
    while(1);
}

//
// End of file
//
