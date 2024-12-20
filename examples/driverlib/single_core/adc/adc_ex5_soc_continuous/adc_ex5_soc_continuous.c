//###########################################################################
//
// FILE:   adc_ex5_soc_continuous.c
//
// TITLE:  ADC continuous self-triggering.
//
//! \addtogroup driver_example_list
//! <h1> ADC Continuous Triggering (adc_soc_continuous)</h1>
//!
//! This example sets up the ADC to convert continuously, achieving maximum
//! sampling rate.\n
//!
//! \b External \b Connections \n
//!  - A0 pin should be connected to signal to convert
//!
//! \b Watch \b Variables \n
//! - \b adcAResults - A sequence of analog-to-digital conversion samples
//! from pin A0. The time between samples is the minimum possible based on the
//! ADC speed.
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
// Defines
//
#define RESULTS_BUFFER_SIZE     256 //buffer for storing conversion results
                                //(size must be multiple of 16)

//
// Globals
//
uint16_t adcAResults[RESULTS_BUFFER_SIZE];
uint16_t resultsIndex;

int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    // 
    // Board Initialization
    // - Configure the ADC and power it up
    // - Setup the ADC for continuous conversions on channel 0
    // - Signal Mode           : single-ended
    // - Conversion Resolution : 12-bit;
    // 
    Board_init();

    //
    // Initialize results buffer
    //
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
        adcAResults[resultsIndex] = 0;
    }
    resultsIndex = 0;

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
        // Enable ADC interrupts
        //
        ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER2);
        ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER3);
        ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER4);

        //
        // Clear all interrupts flags(INT1-4)
        //
        HWREGH(myADC0_BASE + ADC_O_INTFLGCLR) = 0x000F;

        //
        // Initialize results index
        //
        resultsIndex = 0;

        //
        // Software force start SOC0 to SOC15
        //
        HWREG(myADC0_BASE + ADC_O_SOCFRC1) = 0x0000FFFF;

        //
        // Keep taking samples until the results buffer is full
        //
        while(resultsIndex < RESULTS_BUFFER_SIZE)
        {
            //
            // Wait for first set of 16 conversions to complete
            //
            while(false == ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER3));

            //
            // Clear the interrupt flag
            //
            ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER3);

            //
            // Save results for first 8 conversions
            //
            // Note that during this time, the second 8 conversions have
            // already been triggered by EOC14->ADCIN1 and will be actively
            // converting while first 8 results are being saved
            //
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER0);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER1);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER2);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER3);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER4);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER5);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER6);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER7);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER8);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER9);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER10);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER11);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER12);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER13);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER14);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER15);
                                                         

            //
            // Wait for the second set of 16 conversions to complete
            //
            while(false == ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER4));

            //
            // Clear the interrupt flag
            //
            ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER4);

            //
            // Save results for second 8 conversions
            //
            // Note that during this time, the first 8 conversions have
            // already been triggered by EOC30->ADCIN2 and will be actively
            // converting while second 8 results are being saved
            //
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER16);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER17);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER18);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER19);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER20);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER21);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER22);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER23);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER24);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER25);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER26);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER27);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER28);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER29);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER30);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER31);
        }

        //
        // Disable all ADCINT flags to stop sampling
        //
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER2);
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER3);
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER4);

        //
        // At this point, adcAResults[] contains a sequence of conversions
        // from the selected channel
        //

        //
        // Software breakpoint, hit run again to get updated conversions
        //
        ESTOP0;
    }
    while(1); // Loop forever
}

//
// End of file
//
