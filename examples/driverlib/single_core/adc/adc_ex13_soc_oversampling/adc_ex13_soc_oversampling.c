//#############################################################################
//
// FILE:   adc_ex13_soc_oversampling.c
//
// TITLE:  ADC Oversampling Using Multiple SOCs
//
//! \addtogroup driver_example_list
//! <h1>ADC SOC Oversampling </h1>
//!
//! This example sets up ePWM1 to periodically trigger a set of conversions on
//! ADCA including multiple SOCs that all convert A2 to achieve oversampling on
//! A2. 
//!
//! ADCA Interrupt ISRs are used to read results of ADCA.
//!
//! \b External \b Connections \n
//!  - A0, A1, A2 should be connected to signals to be converted.
//!
//! \b Watch \b Variables \n
//! - \b adcAResult0 - Digital representation of the voltage on pin A0
//! - \b adcAResult1 - Digital representation of the voltage on pin A1
//! - \b adcAResult2 - Digital representation of the voltage on pin A2
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
uint16_t adcAResult0; 
uint16_t adcAResult1;
uint16_t adcAResult2;

//
// Function Prototypes
//
void initEPWM();
__attribute__((interrupt("INT"))) void adcA1ISR(void);

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
    // Set up ADCs:
    // Signal Mode           : single-ended
    // Conversion Resolution : 12-bit;
    //
    // Configure SOC0-1 in round robin mode to sample A0 and A1 channel
    // respectively and SOC2-SOC5 oversamples channel A2 on EPWM1SOCA
    // trigger.
    //
    // Register and enable the interrupts:
    // SOC0 and SOC1 results are read after each PWM trigger for
    // channel 0 and 1 outputs while SOC2-SOC5 results will be
    // averaged together for oversampled channel A2 result
    //
    Board_init();

    //
    // Initialize PWM
    //
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
    // Store results for A0 and A1
    //
    adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);

    //
    // Average the 4 oversampled A2 results together
    //
    adcAResult2 = 
        (ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER5)) >> 2;

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }
}

//
// End of file
//
