//#############################################################################
//
// FILE:   adc_ex15_trigger_repeater_oversampling.c
//
// TITLE:  ADC Trigger Repeater Oversampling
//
//! \addtogroup driver_example_list
//! <h1>ADC Trigger Repeater Oversampling</h1>
//!
//! This example configures ADC for oversampling using trigger repeater block.
//! The ePWM1 is configured to periodically trigger the ADC SOC and the trigger
//! repeater module is configured to generate 4 repeated pulses. Post-processing
//! block will take the repeated pulses, accumulates them and stores the results
//! in ppb sum register.
//!
//! \b External \b Connections \n
//!  - A0 should be connected to signals to convert.
//!
//! \b Watch \b Variables \n
//! - \b myADC0Result - Digital representation of the voltage on pin A0
//! - \b myPPB0Result - Digital representation of the voltage of the 4 repeated
//!      pulses on pin A0
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
uint16_t myADC0Result;
uint16_t myPPB0Result;

//
// Function Prototypes
//
void initEPWM(void);

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
    // Board Initialization
    // - Set up the ADC and initialize the SOC
    // - Enable ADC interrupt and trigger repeater
    // - Signal Mode           : single-ended
    // - Conversion Resolution : 12-bit;
    //
    Board_init();

    // Set up the ePWM
    initEPWM();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start ePWM1, enabling SOCA and putting the counter in up-count mode
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Wait while ePWM causes ADC conversions.
        // ADCA1 ISR processes each new set of conversions. 
        //
    }
    while(1);

}

//
// Function to configure ePWM1 to generate the SOC.
//
void initEPWM(void)
{
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //
    // Set the compare A value to 1000 and the period to 1999
    // Assuming ePWM clock is 100MHz, this would give 50kHz sampling
    // 50MHz ePWM clock would give 25kHz sampling, etc. 
    // The sample rate can also be modulated by changing the ePWM period
    // directly (ensure that the compare A value is less than the period). 
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 1000);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 1999);

    //
    // Set the local ePWM module clock divider to /1
    //
    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Freeze the counter
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// adcA1ISR - ADC A Interrupt 1 ISR
//
__attribute__((interrupt("INT"))) void adcA1ISR(void)
{
    //
    // Store the results for A0
    //
    myADC0Result = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    
    //
    // Store the 4 oversampled A0 results together
    //
    myPPB0Result = ADC_readPPBSum(ADCARESULT_BASE, ADC_PPB_NUMBER1);

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    }

}