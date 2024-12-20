//#############################################################################
//
// FILE:   adc_ex11_burst_mode_epwm.c
//
// TITLE:  ADC burst mode example
//
//! \addtogroup driver_example_list
//! <h1>ADC Burst Mode</h1>
//!
//! This example sets up ePWM1 to periodically trigger ADCA using burst mode.
//! This allows for different channels to be sampled with each burst.
//!
//! Each burst triggers 3 conversions.  A0 and A1 are part of every burst while
//! the third conversion rotates between A2, A3, and A4.  This allows high
//! importance signals to be sampled at high speed while lower priority signals
//! can be sampled at a lower rate.
//!
//! ADCA Interrupt ISRs are used to read results for ADCA.
//!
//! \b External \b Connections \n
//!  - A0, A1, A2, A3, A4
//!
//! \b Watch \b Variables \n
//! - \b adcAResult0 - Digital representation of the voltage on pin A0
//! - \b adcAResult1 - Digital representation of the voltage on pin A1
//! - \b adcAResult2 - Digital representation of the voltage on pin A2
//! - \b adcAResult3 - Digital representation of the voltage on pin A3
//! - \b adcAResult4 - Digital representation of the voltage on pin A4
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
uint16_t adcAResult3;
uint16_t adcAResult4;

//
// Function Prototypes
//
void initEPWM();
__attribute__((interrupt("INT"))) void adcABurstISR(void);

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
    // Enable burst mode for SOC23-31 with burst size of 3 with
    // burst mode trigger as EPWM1 SOCA. Select the channels to be
    // converted and configure the S+H duration
    // Burst1: SOC23  (A0) + SOC24  (A1) + SOC25  (A2)
    // Burst2: SOC26 (A0) + SOC27 (A1) + SOC28 (A3)
    // Burst3: SOC29 (A0) + SOC30 (A1) + SOC31 (A4)
    //
    // Register and enable the interrupts:
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file. Each of the 3 interrupts will occur at the end
    // of the 3 different bursts, but all 3 will map to the same ADC result
    // handling ISR
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
        // ADCA Burst ISR processes each new set of conversions.
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
// ADC A Interrupt Burst Mode ISR
//
void adcABurstISR(void)
{
    uint16_t rrPointer;
    ADC_IntNumber burstIntSource;

    //
    //Read the round-robin pointer to determine which burst just completed
    //
    rrPointer = (HWREGH(ADCA_BASE + ADC_O_SOCPRICTL) & 0xFC0) >> 6;
    switch(rrPointer){
        //
        // Burst 1
        //
        case 25:
            adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER23);
            adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER24);
            adcAResult2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER25);
            burstIntSource = ADC_INT_NUMBER1;
        break;

        //
        // Burst 2
        //
        case 28:
            adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER26);
            adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER27);
            adcAResult3 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER28);
            burstIntSource = ADC_INT_NUMBER2;
        break;

        //
        // Burst 3
        //
        case 31:
            adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER29);
            adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER30);
            adcAResult4 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER31);
            burstIntSource = ADC_INT_NUMBER3;
        break;

        default:
            ESTOP0; //handle error for unexpected RR pointer value
    }

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, burstIntSource);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, burstIntSource))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, burstIntSource);
        ADC_clearInterruptStatus(ADCA_BASE, burstIntSource);
    }
}

//
// End of file
//
