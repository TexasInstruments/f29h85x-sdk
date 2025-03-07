//###########################################################################
//
// FILE:   adc_ex14_ppb_pwm_trip.c
//
// TITLE:  ADC limits check and PWM trip in case of out of bound input.
//
//! \addtogroup driver_example_list
//! <h1> ADC PPB PWM trip (adc_ppb_pwm_trip)</h1>
//!
//! This example demonstrates EPWM tripping through ADC limit detection PPB
//! block. ADCAINT1 is configured to periodically trigger the ADCA channel 2
//! post initial software forced trigger. The limit detection post-processing
//! block(PPB) is configured and if the ADC results are outside of the
//! defined range, the post-processing block will generate an ADCxEVTy event.
//! This event is configured as EPWM trip source through configuring EPWM
//! XBAR and corresponding EPWM's trip zone and digital compare sub-modules.
//! The example showcases 
//!  - one-shot
//!  - cycle-by-cycle
//!  - and direct tripping of PWMs
//! through ADCAEVT1 source via Digital compare submodule.
//!
//! The default limits are 0LSBs and 3600LSBs. With VREFHI set to 3.3V, the
//! PPB will generate a trip event if the input voltage goes above about
//! 2.9V.
//!
//! \b External \b Connections \n
//!  - A2 should be connected to a signal to convert
//!  - Observe the following signals on an oscilloscope
//!    - ePWM1(GPIO0 - GPIO1)
//!    - ePWM2(GPIO2 - GPIO3)
//!    - ePWM3(GPIO4 - GPIO5)
//!  - 
//!
//! \b Watch \b Variables \n
//!  - adcA2Results - digital representation of the voltage on pin A2
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
// Defines
//

// Uncomment to enable profiling
//#define ENABLE_PROFILING
#define RESULTS_BUFFER_SIZE     512U
#define EX_ADC_RESOLUTION       12
// 12 for 12-bit conversion resolution, which supports single-ended signaling
// Or 16 for 16-bit conversion resolution, which supports single-ended or
// differential signaling
#define EX_ADC_SIGNALMODE       "SINGLE-ENDED"
//"SINGLE-ENDED" for ADC_MODE_SINGLE_ENDED:
// Sample on single pin (VREFLO is the low reference)
// Or "Differential" for ADC_MODE_DIFFERENTIAL:
// Sample on pair of pins (difference between pins is converted, subject to
// common mode voltage requirements; see the device data manual)


//
// Globals
//
volatile uint16_t indexA = 0;                // Index into result buffer
volatile uint16_t bufferFull;                // Flag to indicate buffer is full
uint16_t adcA2Results[RESULTS_BUFFER_SIZE];  // ADC result buffer

//
// Characteristics of PWMs to be tripped
// EPWM1 - frequency -> 10kHz, dutyA -> 50%, dutyB -> 50%, ePWM1B - inverted
// EPWM2 - frequency -> 2.5kHz, dutyA -> 20%, dutyB -> 50%, ePWM2B - inverted
// EPWM3 - frequency -> 5kHz, dutyA -> 70%, dutyB -> 50%, ePWM3B - inverted
//
EPWM_SignalParams pwmSignal1 =
            {10000, 0.5f, 0.5f, true, DEVICE_SYSCLK_FREQ, SYSCTL_EPWMCLK_DIV_2,
            EPWM_COUNTER_MODE_UP_DOWN, EPWM_CLOCK_DIVIDER_1,
            EPWM_HSCLOCK_DIVIDER_1};

EPWM_SignalParams pwmSignal2 =
            {25000, 0.2f, 0.5f, true, DEVICE_SYSCLK_FREQ, SYSCTL_EPWMCLK_DIV_2,
            EPWM_COUNTER_MODE_UP_DOWN, EPWM_CLOCK_DIVIDER_1,
            EPWM_HSCLOCK_DIVIDER_1};

EPWM_SignalParams pwmSignal3 =
            {5000, 0.7f, 0.5f, true, DEVICE_SYSCLK_FREQ, SYSCTL_EPWMCLK_DIV_2,
            EPWM_COUNTER_MODE_UP_DOWN, EPWM_CLOCK_DIVIDER_1,
            EPWM_HSCLOCK_DIVIDER_1};

//
// Functional Prototypes
//

//
// ADC configuration related APIs
//
void configureADC(uint32_t adcBase);
void configureADCSOC(uint32_t adcBase, uint16_t channel);
void configureLimitDetectionPPB(uint16_t soc, uint16_t limitHigh,
                                uint16_t limitLow);

//
// EPWM configuration related APIs
//
void initEPWMGPIO(void);
void configureOSHTripSignal(uint32_t epwmBase);
void configureCBCTripSignal(uint32_t epwmBase);
void configureDirectTripSignal(uint32_t epwmBase);

#ifdef ENABLE_PROFILING
void setupProfileGpio(void);
#endif

//
// ISRs
//
__attribute__((interrupt("INT"))) void adcA1ISR(void);

int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_ADCA1, &adcA1ISR);

#ifdef ENABLE_PROFILING
    //
    // Setup profiling GPIO
    //
    setupProfileGpio();
#endif

    //
    // For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
    //
    initEPWMGPIO();

    //
    // Enable internal reference on ADCs
    //
    ASysCtl_setVREF(ASYSCTL_VREFHIAB, ASYSCTL_VREF_INTERNAL_3_3_V);

    //
    // Configure the ADC and power it up
    //
    configureADC(ADCA_BASE);

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configuring ePWM modules for desired frequency and duty
    //
    EPWM_configureSignal(EPWM1_BASE, &pwmSignal1);
    EPWM_configureSignal(EPWM2_BASE, &pwmSignal2);
    EPWM_configureSignal(EPWM3_BASE, &pwmSignal3);

    //
    // Configure ADCEVTx as one-shot trip signal for ePWM1
    //
    configureOSHTripSignal(EPWM1_BASE);

    //
    // Configure ADCEVTx as cycle-by-cycle trip signal for ePWM2
    //
    configureCBCTripSignal(EPWM2_BASE);

    //
    // Configure ADCEVTx as direct trip signal for ePWM3
    //
    configureDirectTripSignal(EPWM3_BASE);
    //
    // Setup the ADC for ADCAINT1 triggered conversions on channel 2
    //
    configureADCSOC(ADCA_BASE, 2U);

    //
    // Configure ADC post-processing limits
    // SOC0 will generate an interrupt if conversion is above or below limits
    //
    configureLimitDetectionPPB(0U, 3600U, 0U);

    //
    // Enable ADC interrupt
    //
    Interrupt_enable(INT_ADCA1);

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
    // Trigger ADC once through software
    //
    ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    do
    {
    }
    while(1);
}

//
// configureOSHTripSignal - Configure ADCAEVT1 as one-shot trip signal for
//                          desired PWM instance
//
void configureOSHTripSignal(uint32_t epwmBase)
{
    //
    // Configure trip 7 input to be triggered by ADCAEVT1
    //
    XBAR_selectEpwmXbarInputSource(XBAR_TRIP7, XBAR_EPWM_ADCAEVT1);

    //
    // Select Trip 7 input as input to DC module
    //
    EPWM_selectDigitalCompareTripInput(epwmBase, EPWM_DC_TRIP_TRIPIN7,
                                       EPWM_DC_TYPE_DCAH);

    //
    // DCAEVT1 is generated when DCAH is high.
    //
    EPWM_setTripZoneDigitalCompareEventCondition(epwmBase,EPWM_TZ_DC_OUTPUT_A1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);

    //
    // DCAEVT1 uses the unfiltered version of DCAEVT1
    //
    EPWM_setDigitalCompareEventSource(epwmBase, EPWM_DC_MODULE_A,
                            EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // DCAEVT1 is asynchronous
    //
    EPWM_setDigitalCompareEventSyncMode( epwmBase, EPWM_DC_MODULE_A,
                              EPWM_DC_EVENT_1,EPWM_DC_EVENT_INPUT_NOT_SYNCED);

    //
    // Enable Trip zone signals
    //
    EPWM_enableTripZoneSignals(epwmBase, EPWM_TZ_SIGNAL_DCAEVT1);

    //
    // Action on DCAEVT1
    // Force the EPWMxA LOW and EPWMxB HIGH
    //
    EPWM_setTripZoneAction(epwmBase,
                           EPWM_TZ_ACTION_EVENT_TZA,
                           EPWM_TZ_ACTION_LOW);

    EPWM_setTripZoneAction(epwmBase,
                           EPWM_TZ_ACTION_EVENT_TZB,
                           EPWM_TZ_ACTION_HIGH);

    //
    // Clear any spurious trip zone flags before enabling the interrupt
    //
    EPWM_clearTripZoneFlag(epwmBase, EPWM_TZ_FLAG_DCAEVT1);

    EPWM_clearOneShotTripZoneFlag(epwmBase, EPWM_TZ_OST_FLAG_DCAEVT1);

    //
    // Enable TZ interrupt
    //
    EPWM_enableTripZoneInterrupt(epwmBase, EPWM_TZ_INTERRUPT_OST);
}

//
// configureCBCTripSignal - Configure ADCAEVT1 as cycle-by-cycle trip signal
//                          for desired PWM instance
//
void configureCBCTripSignal(uint32_t epwmBase)
{
    //
    // Configure trip 8 input to be triggered by ADCAEVT1
    //
    XBAR_selectEpwmXbarInputSource(XBAR_TRIP8, XBAR_EPWM_ADCAEVT1);

    //
    // Select Trip 8 input as input to DC module
    //
    EPWM_selectDigitalCompareTripInput(epwmBase, EPWM_DC_TRIP_TRIPIN8,
                                       EPWM_DC_TYPE_DCAH);

    //
    // DCAEVT2 is generated when DCAH is high.
    //
    EPWM_setTripZoneDigitalCompareEventCondition(epwmBase, EPWM_TZ_DC_OUTPUT_A2,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);

    //
    // DCAEVT2 uses the unfiltered version of DCAEVT2
    //
    EPWM_setDigitalCompareEventSource(epwmBase, EPWM_DC_MODULE_A,
                            EPWM_DC_EVENT_2, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // DCAEVT2 is asynchronous
    //
    EPWM_setDigitalCompareEventSyncMode(epwmBase, EPWM_DC_MODULE_A,
                              EPWM_DC_EVENT_2, EPWM_DC_EVENT_INPUT_NOT_SYNCED);

    //
    // Enable Trip zone signals
    //
    EPWM_enableTripZoneSignals(epwmBase, EPWM_TZ_SIGNAL_DCAEVT2);

    //
    // Configure CBC clear event
    //
    EPWM_selectCycleByCycleTripZoneClearEvent(epwmBase,
                                       EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD);

    //
    // Action on DCAEVT2
    // Force the EPWMxA/EPWMxB LOW
    //
    EPWM_setTripZoneAction(epwmBase, EPWM_TZ_ACTION_EVENT_TZA,
                           EPWM_TZ_ACTION_LOW);

    EPWM_setTripZoneAction(epwmBase, EPWM_TZ_ACTION_EVENT_TZB,
                           EPWM_TZ_ACTION_HIGH);

    //
    // Clear any spurious trip zone flags before enabling the interrupt
    //
    EPWM_clearTripZoneFlag(epwmBase, EPWM_TZ_FLAG_DCAEVT2);

    EPWM_clearCycleByCycleTripZoneFlag(epwmBase, EPWM_TZ_CBC_FLAG_DCAEVT2);

    //
    // Enable TZ interrupt
    //
    EPWM_enableTripZoneInterrupt(epwmBase, EPWM_TZ_INTERRUPT_CBC);
}

//
// configureDirectTripSignal - Configure ADCAEVT1 as direct trip signal for
//                             desired PWM instance
//
void configureDirectTripSignal(uint32_t epwmBase)
{
    //
    // Configure trip 9 input to be triggered by ADCAEVT1
    //
    XBAR_selectEpwmXbarInputSource(XBAR_TRIP9, XBAR_EPWM_ADCAEVT1);

    //
    // Select Trip 9 input as input to DC module
    //
    EPWM_selectDigitalCompareTripInput(epwmBase, EPWM_DC_TRIP_TRIPIN9,
                                       EPWM_DC_TYPE_DCAH);
    EPWM_selectDigitalCompareTripInput(epwmBase, EPWM_DC_TRIP_TRIPIN9,
                                       EPWM_DC_TYPE_DCBH);

    //
    // DCAEVT1 is generated when DCAH is high. DCBEVT2 is generated when DCBH
    // is high
    //
    EPWM_setTripZoneDigitalCompareEventCondition(epwmBase, EPWM_TZ_DC_OUTPUT_A1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);
    EPWM_setTripZoneDigitalCompareEventCondition(epwmBase, EPWM_TZ_DC_OUTPUT_B2,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);

    //
    // DCAEVT1/DCBEVT2 uses the unfiltered version of DCAEVT1/DCBEVT2
    //
    EPWM_setDigitalCompareEventSource(epwmBase, EPWM_DC_MODULE_A,
                            EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);
    EPWM_setDigitalCompareEventSource(epwmBase, EPWM_DC_MODULE_B,
                            EPWM_DC_EVENT_2, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // DCAEVT1/ DCBEVT2 is asynchronous
    //
    EPWM_setDigitalCompareEventSyncMode(epwmBase, EPWM_DC_MODULE_A,
                              EPWM_DC_EVENT_1, EPWM_DC_EVENT_INPUT_NOT_SYNCED);
    EPWM_setDigitalCompareEventSyncMode(epwmBase, EPWM_DC_MODULE_B,
                              EPWM_DC_EVENT_2, EPWM_DC_EVENT_INPUT_NOT_SYNCED);

    //
    // Action on TZA/TZB
    // Force the EPWMxA LOW and EPWMxB HIGH
    //
    EPWM_setTripZoneAction(epwmBase,
                           EPWM_TZ_ACTION_EVENT_DCAEVT1,
                           EPWM_TZ_ACTION_LOW);

    EPWM_setTripZoneAction(epwmBase,
                           EPWM_TZ_ACTION_EVENT_DCBEVT2,
                           EPWM_TZ_ACTION_HIGH);

    //
    // Clear any spurious trip zone flags before enabling the interrupt
    //
    EPWM_clearTripZoneFlag(epwmBase, (EPWM_TZ_INTERRUPT_DCAEVT1 |
                                      EPWM_TZ_INTERRUPT_DCBEVT2));

    //
    // Enable TZ interrupt
    //
    EPWM_enableTripZoneInterrupt(epwmBase, (EPWM_TZ_INTERRUPT_DCAEVT1 |
                                            EPWM_TZ_INTERRUPT_DCBEVT2));
}

//
// configureADC - Write ADC configurations and power up the ADC for both
//                ADC A and ADC B
//
void configureADC(uint32_t adcBase)
{
    //
    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(adcBase, ADC_CLK_DIV_4_0);

    //
    // Set resolution and signal mode (see #defines above) and load
    // corresponding trims.
    //
#if(EX_ADC_RESOLUTION == 12)
    ADC_setMode(adcBase, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
#elif(EX_ADC_RESOLUTION == 16)
    #if(EX_ADC_SIGNALMODE == "SINGLE-ENDED")
    ADC_setMode(adcBase, ADC_RESOLUTION_16BIT, ADC_MODE_SINGLE_ENDED);
    #elif(EX_ADC_SIGNALMODE == "DIFFERENTIAL")
    ADC_setMode(adcBase, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);
    #endif
#endif

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(adcBase, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADCs and then delay for 1 ms
    //
    ADC_enableConverter(adcBase);

    //
    // Delay for 1ms to allow ADC time to power up
    //
    DEVICE_DELAY_US(1000);
}

//
// configureLimitDetectionPPB - Configure high and low limits for ADCPPB
//
void configureLimitDetectionPPB(uint16_t soc, uint16_t limitHigh,
                                uint16_t limitLow)
{
    //
    // Associate PPB1 with soc
    //
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER1, (ADC_SOCNumber)soc);

    //
    // Set high and low limits
    //
    ADC_setPPBTripLimits(ADCA_BASE, ADC_PPB_NUMBER1, limitHigh, limitLow);

    //
    // Enable high and low limit PPB events
    //
    ADC_enablePPBEvent(ADCA_BASE, ADC_PPB_NUMBER1, (ADC_EVT_TRIPHI |
                                                    ADC_EVT_TRIPLO));

    //
    // Configure CBCEN
    //
    HWREGH(ADCA_BASE + ADC_O_PPB1CONFIG) |= ADC_PPB2CONFIG_CBCEN;
}

//
// configureADCSOC - Setup ADC EPWM channel and trigger settings
//
void configureADCSOC(uint32_t adcBase, uint16_t channel)
{
    uint16_t acqps;

    //
    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    //
    if(EX_ADC_RESOLUTION == 12)
    {
        acqps = 14; // 75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; // 320ns
    }
    //
    // - NOTE: A longer sampling window will be required if the ADC driving
    //   source is less than ideal (an ideal source would be a high bandwidth
    //   op-amp with a small series resistance). See TI application report
    //   SPRACT6 for guidance on ADC driver design.
    //

    //
    // Select the channels to convert and end of conversion flag
    // ADCA
    //
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);

    //
    // Configure ADCINT1 as SOC0 trigger
    //
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER0,
                               ADC_INT_SOC_TRIGGER_ADCINT1);

    //
    // Enable continuous mode
    //
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Configure source as EOC1, clear & enable the interrupt
    //
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER1, ADC_INT_TRIGGER_EOC0);
    ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER1);
    ADC_enableInterrupt(adcBase, ADC_INT_NUMBER1);
}

//
// ADC A Interrupt 1 ISR
//
__attribute__((interrupt("INT"))) void adcA1ISR(void)
{
#ifdef ENABLE_PROFILING
    //
    // Setting Profiling GPIO12 : Takes 3 cycles
    //
    HWREG(GPIODATA_BASE  + GPIO_O_GPASET) = 0x1000;
#endif

    //
    // Add the latest result to the buffer
    //
    adcA2Results[indexA++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    //
    // Set the bufferFull flag if the buffer is full
    //
    if(RESULTS_BUFFER_SIZE <= indexA)
    {
        indexA = 0;
    }

#ifdef ENABLE_PROFILING
    //
    // Resetting Profiling GPIO12
    //
    HWREG(GPIODATA_BASE  + GPIO_O_GPACLEAR) = 0x1000;
#endif
}

//
// initEPWMGPIO - Configure ePWM1-ePWM3 GPIO
//
void initEPWMGPIO(void)
{
    //
    // Disable pull up on GPIO0-5 and configure them as PWMs
    //
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1_A);

    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1_B);

    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_2_EPWM2_A);

    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_3_EPWM2_B);

    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_EPWM3_A);

    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_EPWM3_B);
}

#ifdef ENABLE_PROFILING
void setupProfileGpio(void)
{
    GPIO_setDirectionMode(12,GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(12,GPIO_QUAL_SYNC);
    GPIO_setPinConfig(GPIO_12_GPIO12);
    GPIO_writePin(12,0);
}

#endif
//
// End of file
//
