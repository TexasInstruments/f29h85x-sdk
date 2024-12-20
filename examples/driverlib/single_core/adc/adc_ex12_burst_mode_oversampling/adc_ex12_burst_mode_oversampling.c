//#############################################################################
//
// FILE:   adc_ex13_burst_mode_oversampling.c
//
// TITLE:  ADC burst mode oversampling example
//
//! \addtogroup driver_example_list
//! <h1>ADC Burst Mode Oversampling</h1>
//!
//! This example is an ADC oversampling example implemented with software. The
//! ADC SOCs are configured in burst mode, triggered by the ePWM SOC A event
//! trigger.
//!
//! \b External \b Connection \n
//!  - A2
//!
//! \b Watch \b Variables \n
//! - \b lv_results - Array of digital values measured on pin A2 (oversampling
//!                 is configured by Oversampling_Amount)
//!
//
//#############################################################################
//
//
// $Copyright:
//#############################################################################

//
// Included Files
//
#include "board.h"

//
// Macros and Enumerations
//
#define DO_TOGGLE 0
typedef enum
{
    Baseline = 0,           //!< No oversampling
    X2_Oversampling = 1,    //!< 2X oversampling
    X4_Oversampling = 2,    //!< 4X oversampling
    X8_Oversampling = 3,    //!< 8X oversampling
    X16_Oversampling = 4,   //!< 16X oversampling
    X32_Oversampling = 5,   //!< 32X oversampling
} Oversampling_Amount;

//
// Global Variables
//
uint32_t acc;
uint16_t numBins = 8192;
volatile uint16_t nloops = 0;
volatile uint32_t lv_results[256];
Oversampling_Amount ovrsmplAmt = Baseline;

//
// Functions
//
__attribute__((interrupt("INT"))) void INT_myADC0_1_ISR(void);

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
    // Burst mode configuration:
    // 1 burst of 16 conversions (SOC0 - SOC15) with equal priority
    //
    // Burst mode trigger is EPWM1 SOCA. Select the channels to be
    // converted and configure the S+H duration
    //
    Board_init();

    //
    // Debug Timing of ePWM and SOC conversions
    //
#if(DO_TOGGLE == 1)
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOC_SRC_PWM1SOCA);     			//Routes ePWM SOCA trigger to external pin
    GPIO_setPinConfig(GPIO_8_ADCSOCAO);
    GPIO_setPadConfig(7, GPIO_PIN_TYPE_STD/*GPIO_PIN_TYPE_PULLUP*/);
    GPIO_setPinConfig(GPIO_7_GPIO7);
    GPIO_setDirectionMode(7, GPIO_DIR_MODE_OUT);
    GPIO_writePin(0,0);
#endif

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    while(1);
}

//
// INT_myADC0_1_ISR - ADC A Interrupt Burst Mode ISR
// Interrupt performs oversampling calculation based on oversampling factor
//
void INT_myADC0_1_ISR(void)
{
    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

    //
    // Debug Timing of ePWM and SOC conversions
    //
#if(DO_TOGGLE == 1)
    GPIO_togglePin(myGPIO0);
#endif

    //
    // Accumulate SOC results (store only 1 value per burst)
    //
    if(ovrsmplAmt == Baseline)
    {
        //
        // 1X Oversampling
        //
        lv_results[nloops++] = ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0);
    }
    else if(ovrsmplAmt == X2_Oversampling)
    {
        //
        // 2X Oversampling
        //
        lv_results[nloops++] = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1));
    }
    else if(ovrsmplAmt == X4_Oversampling)
    {
        //
        // 4X Oversampling
        //
        lv_results[nloops++] = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3));
    }
    else if(ovrsmplAmt == X8_Oversampling)
    {
        //
        // 8X Oversampling
        //
        lv_results[nloops++] = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER4) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER5) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER6) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER7));
    }
    else if(ovrsmplAmt == X16_Oversampling)
    {
        //
        // 16X Oversampling
        //
        acc = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER4) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER5) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER6) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER7) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER8) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER9) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER10) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER11) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER12) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER13) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER14) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER15));
        lv_results[nloops] = acc;
        nloops++;
    }
    else if(ovrsmplAmt == X32_Oversampling){
        //
        // 32X Oversampling
        //
        acc = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER4) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER5) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER6) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER7) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER8) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER9) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER10) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER11) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER12) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER13) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER14) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER15) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER16) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER17) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER18) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER19) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER20) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER21) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER22) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER23) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER24) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER25) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER26) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER27) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER28) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER29) +
                ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER30) + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER31));

        lv_results[nloops] = acc;
        nloops++;

    }

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    }

    //
    // Check if all results are stored
    //
    if(nloops >= numBins)
    {
        //
        // Disable ADC interrupt
        //
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
        ESTOP0;
    }

    //
    // Debug Timing of ePWM and SOC conversions
    //
#if(DO_TOGGLE == 1)
    GPIO_togglePin(myGPIO0);
#endif

}

//
// End of file
//
