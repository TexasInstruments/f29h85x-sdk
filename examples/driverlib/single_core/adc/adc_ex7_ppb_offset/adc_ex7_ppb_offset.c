//###########################################################################
//
// FILE:   adc_ex7_ppb_offset.c
//
// TITLE:  ADC offset adjust using post-processing block
//
//! \addtogroup driver_example_list
//! <h1> ADC PPB Offset (adc_ppb_offset)</h1>
//!
//! This example software triggers the ADC.  Some SOCs have automatic offset
//! adjustment applied by the post-processing block. After the program runs,
//! the memory will contain ADC & post-processing block(PPB) results.
//!
//! \b External \b Connections \n
//!  - A0, C0 pins should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//!  - \b myADC0Result \b: a digital representation of the voltage on pin A0
//!  - \b myADC0PPBResult \b : a digital representation of the voltage
//!      on pin A0, minus 100 LSBs of automatically added offset
//!  - \b myADC1Result \b: a digital representation of the voltage on pin C0
//!  - \b myADC1PPBResult \b : a digital representation of the voltage
//!      on pin C0 plus 100 LSBs of automatically added offset
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
uint16_t myADC0Result;
uint16_t myADC0PPBResult;
uint16_t myADC1Result;
uint16_t myADC1PPBResult;

int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Board Initialization
    // - Configure the ADCs and power them up
    // - Setup the ADCs for software conversions
    // - Setup PPB offset correction.
    //      conversion on channel A will subtract 100.
    //      conversion on channel C will add 100.
    // - Signal Mode           : single-ended
    // - Conversion Resolution : 12-bit;
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
        // Convert, wait for completion, and store results.
        // Start conversions immediately via software, ADCA
        //
        ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER0);
        ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER1);

        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1) == false);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

        //
        // Start conversions immediately via software, ADCC
        //
        ADC_forceSOC(myADC1_BASE, ADC_SOC_NUMBER0);
        ADC_forceSOC(myADC1_BASE, ADC_SOC_NUMBER1);

        //
        // Wait for ADCC to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1) == false);
        ADC_clearInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        myADC0Result = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        myADC0PPBResult = ADC_readPPBResult(ADCARESULT_BASE, ADC_PPB_NUMBER1);
        myADC1Result = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);
        myADC1PPBResult = ADC_readPPBResult(ADCCRESULT_BASE, ADC_PPB_NUMBER1);

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
