//###########################################################################
//
// FILE:   adc_ex8_ppb_limits.c
//
// TITLE:  ADC limits check using post-processing block.
//
//! \addtogroup driver_example_list
//! <h1> ADC PPB Limits (adc_ppb_limits)</h1>
//!
//! This example sets up the ePWM to periodically trigger the ADC. If the
//! results are outside of the defined range, the post-processing block
//! will generate an interrupt.
//!
//! The default limits are 1000LSBs and 3000LSBs.  With VREFHI set to 3.3V, the
//! PPB will generate an interrupt if the input voltage goes above about
//! 2.4V or below about 0.8V.
//!
//! \b External \b Connections \n
//!  - A0 should be connected to a signal to convert
//!
//! \b Watch \b Variables \n
//!  - None
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
uint32_t intStatus;
//
// Functional Prototypes
//
void configureEPWM(uint32_t epwmBase);
__attribute__((interrupt("INT"))) void adcAEvtISR(void);

int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Board Initialization
    // - Configure the ADC and power it up
    // - Setup the ADC for ePWM triggered conversions on channel 0
    // - Configure ADC post-processing limits
    //      SOC0 will generate an interrupt if conversion is above or below limits
    // - Signal Mode           : single-ended
    // - Conversion Resolution : 12-bit;
    // 
    Board_init();

    //
    // Configure the ePWM
    //
    configureEPWM(EPWM1_BASE);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start ePWM:
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable SOCA trigger
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Unfreeze epwm counter to count-up
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Wait while ePWM causes ADC conversions.
        // If the ADC conversions exceed the PPB limits, then an interrupt
        // will be generated. User can read ADC results either in idle loop
        // or ADCINT ISR as per application requirement.
        //
    }
    while(1);
}

//
// configureEPWM - Setup SOC and compare values for EPWM
//
void configureEPWM(uint32_t epwmBase)
{
    //
    // Disable SOCA trigger
    //
    EPWM_disableADCTrigger(epwmBase, EPWM_SOC_A);

    //
    // Trigger SOCA on CMPA up-count
    //
    EPWM_setADCTriggerSource(epwmBase, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);

    //
    // Generate pulse on 1st event
    //
    EPWM_setADCTriggerEventPrescale(epwmBase, EPWM_SOC_A, 1U);

    //
    // Set compare A value to 2048 counts
    //
    EPWM_setCounterCompareValue(epwmBase, EPWM_COUNTER_COMPARE_A, 2048U);

    //
    // Set period to 4096 counts
    //
    EPWM_setTimeBasePeriod(epwmBase, 4096U);

    //
    // Freeze counter
    //
    EPWM_setTimeBaseCounterMode(epwmBase, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// adcAEvtISR - ISR for ADCA PPB
//
void adcAEvtISR(void)
{
    //
    // Warning, you are outside of PPB limits
    //
    intStatus = ADC_getPPBEventStatus(myADC0_BASE, ADC_PPB_NUMBER1);
    if((intStatus & ADC_EVT_TRIPHI) != 0U)
    {
        //
        // Voltage exceeded high limit
        //
        ESTOP0;

        //
        // Clear the trip flag and continue
        //
        ADC_clearPPBEventStatus(myADC0_BASE, ADC_PPB_NUMBER1, ADC_EVT_TRIPHI);
    }
    if((intStatus & ADC_EVT_TRIPLO) != 0U)
    {
        //
        // Voltage exceeded low limit
        //
        ESTOP0;

        //
        // Clear the trip flag and continue
        //
        ADC_clearPPBEventStatus(myADC0_BASE, ADC_PPB_NUMBER1, ADC_EVT_TRIPLO);
    }
}

//
// End of file
//
