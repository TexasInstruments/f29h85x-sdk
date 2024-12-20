//#############################################################################
//
// FILE:   adc_ex17_safety_checker.c
//
// TITLE:  ADC Safety Checker
//
//! \addtogroup driver_example_list
//! <h1>ADC Safety Checker</h1>
//!
//! This example compares the absolute value of the two ADC conversion results
//! with the set tolerance value.
//!
//! The ADCA is used with A0 and A1 to compare the two ADC conversions. If
//! the difference between two conversion results exceeds the value configured
//! as tolerance then the ADC result safety checker tile generates an interrupt
//! signal from out-of-tolerance.
//!
//! \b External \b Connections \n
//!  - A0 and A1 should be connected to signals to convert.
//!
//! \b Watch \b Variables \n
//! - \b myADC0Result0 - Digital representation of the voltage on pin A0
//! - \b myADC0Result1 - Digital representation of the voltage on pin A1
//! - \b tolerance - Set digital tolerance limit for ADC safety checker
//! - \b count - number of times the OOT flag is generated
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
uint32_t count;
uint32_t getsafecheckStatus;
volatile uint16_t tolerance = 100;

void myADCSafetyChecker0_init();

//
// Main
//
int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Set up ADCs, initializing the SOCs to be triggered by software
    // Signal Mode           : single-ended
    // Conversion Resolution : 12-bit;
    //
    myADCSafetyChecker0_init();
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Convert, wait for completion, and store results
        //
        ADC_forceMultipleSOC(myADC0_BASE, (ADC_FORCE_SOC0 | ADC_FORCE_SOC1));

        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1) == false)
        {
        }
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        myADC0Result0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        myADC0Result1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);

        //
        // Get the safety checker result and generate flag if the difference exceeds the tolerance value
        //
        getsafecheckStatus = ADC_getSafetyCheckStatus(ADCSAFETYCHECKINTEVT1_BASE, ADC_SAFETY_CHECKER1, ADC_SAFETY_CHECK_OOT_FLG);
        if(getsafecheckStatus)
        {
            //
            // Indicate that the OOT flag is generated
            //
            count++;

            //
            // Software breakpoint. At this point, conversion results (myADC0Result0, myADC0Result1)
            // are compared with each other, generated safety checker out-of-tolerance flag and incremented count
            //
            // Hit run again to get updated conversions.
            //
            ESTOP0;
        }
        ADC_clearSafetyCheckStatus(ADCSAFETYCHECKINTEVT1_BASE, ADC_SAFETY_CHECKER1, ADC_SAFETY_CHECK_OOT_FLG);
    }
}


void myADCSafetyChecker0_init(void){

    //
    // Enable the safety checker event.
    //
    ADC_enableSafetyCheckEvt(ADCSAFETYCHECKINTEVT1_BASE, ADC_SAFETY_CHECKER1, ADC_SAFETY_CHECK_EVENT1, ADC_SAFETY_CHECK_OOT);
    //
    // Configures the safety checker result for a selected SOC.
    //
    ADC_configSOCSafetyCheckerInput(myADC0_BASE,ADC_SOC_NUMBER0,ADC_SAFETY_CHECKER_INPUT_SOCx);

    //
    // Configures the safety checker module.
    //
    ADC_configureSafetyChecker(ADCSAFETYCHECK1_BASE, ADC_SAFETY_CHECK1,ADC_A,ADC_RESULT0);

    //
    // Configures the safety checker result for a selected SOC.
    //
    ADC_configSOCSafetyCheckerInput(myADC0_BASE,ADC_SOC_NUMBER1,ADC_SAFETY_CHECKER_INPUT_SOCx);
    
    //
    // Configures the safety checker module.
    //
    ADC_configureSafetyChecker(ADCSAFETYCHECK1_BASE, ADC_SAFETY_CHECK2,ADC_A,ADC_RESULT1);

    //
    // Configures the tolerance allowed between safety check results.
    //
    ADC_setSafetyCheckerTolerance(ADCSAFETYCHECK1_BASE,tolerance);

    //
    // Enables the ADC result safety checker module.
    //
    ADC_enableSafetyChecker(ADCSAFETYCHECK1_BASE);
}
