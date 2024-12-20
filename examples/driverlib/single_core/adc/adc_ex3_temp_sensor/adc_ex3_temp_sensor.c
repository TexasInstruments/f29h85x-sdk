//#############################################################################
//
// FILE:   adc_ex3_temp_sensor.c
//
// TITLE:  Sample temperature sensor and convert to temperature
//
//! \addtogroup driver_example_list
//! <h1>ADC Temperature Sensor Conversion</h1>
//!
//! This example sets up the ePWM to periodically trigger the ADC.  The
//! ADC converts the internal connection to the temperature sensor,
//! which is then interpreted as a temperature by calling the
//! ADC_getTemperatureC() function.
//!
//! \b Watch \b Variables \n
//! - \b sensorSample - The raw reading from the temperature sensor
//! - \b sensorTemp   - The interpretation of the sensor sample as a temperature
//!                     in degrees Celsius.
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
uint16_t sensorSample;
int16_t sensorTemp;

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
    //  - Configure and power up ADCA.
    //  - Configure ADC's SOC0 to be triggered by ePWM1.
    //  - Enable the temperature sensor and give it 500 us to power up
    //  - Enable ADC interrupt
    //  - Signal Mode           : single-ended
    //  - Conversion Resolution : 12-bit;
    //
    Board_init();

    //
    // Set up the ePWM
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
    // Loop indefinitely
    //
    while(1)
    {
        ;
    }
}

//
// initEPWM - Function to configure ePWM1 to generate the SOC.
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
    // Read the raw result
    //
    sensorSample = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    //
    // Convert the result to a temperature in degrees C
    //
    sensorTemp = ADC_getTemperatureC(sensorSample, ADC_REFERENCE_INTERNAL, 3.3f);

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

