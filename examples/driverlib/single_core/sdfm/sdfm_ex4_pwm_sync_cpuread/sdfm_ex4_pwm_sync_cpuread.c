//###########################################################################
//
// FILE:   sdfm_ex4_pwm_sync_cpuread.c
//
// TITLE:  SDFM PWM Sync Example
//
//! \addtogroup driver_example_list
//! <h1> SDFM PWM Sync </h1>
//!
//! In this example, SDFM filter data is read by CPU in SDFM ISR routine. The
//! SDFM configuration is shown below:
//!     - SDFM1 is used in this example. For using SDFM2, few modifications
//!       would be needed in the example.
//!     - MODE0 Input control mode selected
//!     - Comparator settings
//!         - Sinc3 filter selected
//!         - OSR = 32
//!         - hlt = 0x7FFF (Higher threshold setting)
//!         - llt  = 0x0000(Lower threshold setting)
//!  -  Data filter settings
//!      - All the 4 filter modules enabled
//!      - Sinc3 filter selected
//!      - OSR = 256
//!      - All the 4 filters are synchronized by using PWM
//!       (Master Filter enable bit)
//!      - Filter output represented in 16 bit format
//!      - In order to convert 25 bit Data filter
//!        into 16 bit format user needs to right shift by 10 bits for
//!        Sinc3 filter with OSR = 256
//!  - Interrupt module settings for SDFM filter
//!      - All the 4 higher threshold comparator interrupts disabled
//!      - All the 4 lower threshold comparator interrupts disabled
//!      - All the 4 modulator failure interrupts disabled
//!      - All the 4 filter will generate interrupt when a new filter data
//!        is available
//!
//! \b External \b Connections \n
//!   - SDFM_PIN_MUX_OPTION1 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO16-GPIO55
//!   - SDFM_PIN_MUX_OPTION2 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO48-GPIO75
//!   - SDFM_PIN_MUX_OPTION3 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO69-GPIO98
//!
//! \b Watch \b Variables \n
//! -  \b filter1Result - Output of filter 1
//! -  \b filter2Result - Output of filter 2
//! -  \b filter3Result - Output of filter 3
//! -  \b filter4Result - Output of filter 4
//!
//
//###########################################################################

//
// Included Files
//
#include "board.h"
#include <stdio.h>

//
// Defines
//
#define MAX_SAMPLES               1024
#define SDFM_PIN_MUX_OPTION1      1
#define SDFM_PIN_MUX_OPTION2      2
#define SDFM_PIN_MUX_OPTION3      3
#define EPWM_TIMER_TBPRD          65535  // ePWM Period register
#define SDFM_INT_MASK             0x8000F000U

//
// Macro to read the SDFM filter data in 16-bit format
//
#define READ_16BIT_FILTER_DATA(base, offset)                                  \
                                   (*((volatile int16_t *)(base + offset + 2)))

#define READ_32BIT_FILTER_DATA(base, offset)                                  \
                                   (*((volatile int32_t *)(base + offset)))

//
// Globals
//
uint32_t sdfmInstance;
uint32_t pwmInstance = EPWM11_BASE; // ePWM 11 for synchronizing SDFM1 filters
int16_t  filter1Result[MAX_SAMPLES];
int16_t  filter2Result[MAX_SAMPLES];
int16_t  filter3Result[MAX_SAMPLES];
int16_t  filter4Result[MAX_SAMPLES];

//
// Function Prototypes
//
void configureSDFMPins(uint16_t sdfmPinOption);
void setPinConfig1(void);
void setPinConfig2(void);
void setPinConfig3(void);
void initEPWM(uint32_t epwmInstance);
__attribute__((interrupt("INT"))) void sdfm1ISR(void);
__attribute__((interrupt("INT"))) void sdfm2ISR(void);

//
// Main
//
int main(void)
{
   uint16_t  pinMuxOption;
   uint16_t  hlt, llt;

   //
   // Initialize device clock and peripherals
   //
   Device_init();

   //
   // Interrupts that are used in this example are re-mapped to
   // ISR functions found within this file.
   //
   Interrupt_register(INT_SD1_ERR, sdfm1ISR);
   Interrupt_register(INT_SD2_ERR, sdfm2ISR);

   //
   // Enable SDFM1 amd SDFM2 interrupts
   //
   Interrupt_enable(INT_SD1_ERR);
   Interrupt_enable(INT_SD2_ERR);

#ifdef CPU1
   pinMuxOption = SDFM_PIN_MUX_OPTION1;

   //
   // Configure GPIO pins as SDFM pins
   //
   configureSDFMPins(pinMuxOption);
#endif

    //
    // Select SDFM1
    //
    sdfmInstance = SDFM1_BASE;

    //
    // Input Control Module:
    // Configure Modulator Clock rate = Modulator data rate
    //
    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_1,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_2,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_3,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_4,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    //
    // Comparator Module
    //
    hlt = 0x7FFF;    //Over value threshold settings
    llt = 0x0000;    //Under value threshold settings

    //
    // Configure Comparator module's comparator filter type and comparator's OSR
    // value, higher threshold, lower threshold
    //
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_3 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_4 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)), 0);

    //
    // Data filter Module
    //
    // Configure Data filter modules filter type, OSR value and
    // enable / disable data filter
    //
    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_3 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_4 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    //
    // Enable Master filter bit: Unless this bit is set none of the filter modules
    // can be enabled. All the filter modules are synchronized when master filter
    // bit is enabled after individual filter modules are enabled.
    //
    SDFM_enableMainFilter(sdfmInstance);


    //
    // PWM11.CMPC, PWM11.CMPD signals can synchronize SDFM1 filters and
    // PWM12.CMPC and PWM12.CMPD signals can synchronize SDFM2 filters. This
    // option is being used in this example for SDFM1.
    //
    SDFM_enableExternalReset(sdfmInstance, SDFM_FILTER_1);
    SDFM_enableExternalReset(sdfmInstance, SDFM_FILTER_2);
    SDFM_enableExternalReset(sdfmInstance, SDFM_FILTER_3);
    SDFM_enableExternalReset(sdfmInstance, SDFM_FILTER_4);

    //
    // Init EPWMs
    //
    initEPWM(pwmInstance);

    //
    // Enable interrupts
    //
    // Following SDFM interrupts can be enabled / disabled using this function.
    //  Enable / disable comparator high threshold
    //  Enable / disable comparator low threshold
    //  Enable / disable modulator clock failure
    //  Enable / disable filter acknowledge
    //
    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_1,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_2,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_3,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_4,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_1,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_2,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_3,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_4,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    while((HWREGH(pwmInstance + EPWM_O_TBCTR)) < 550);

    //
    // Enable master interrupt so that any of the filter interrupts can trigger
    // by SDFM interrupt to CPU
    //
    SDFM_enableMainInterrupt(sdfmInstance);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    while(1);
}

//
// sdfm1ISR - SDFM 1 ISR
//
void sdfm1ISR(void)
{
    static uint16_t loopCounter1 = 0;

    //
    // Wait for result from all the filters (SDIFLG)
    //
    while((HWREG(SDFM1_BASE + SDFM_O_SDIFLG) & SDFM_INT_MASK) != SDFM_INT_MASK);

    //
    // Reset the loop counter
    //
    if(loopCounter1 >= MAX_SAMPLES)
    {
        loopCounter1 = 0;
    }

    //
    // Read each SDFM filter output and store it in respective filter
    // result array
    //
    filter1Result[loopCounter1]   =
                        READ_16BIT_FILTER_DATA(SDFM1_BASE, SDFM_O_SDDATA1);
    filter2Result[loopCounter1]   =
                        READ_16BIT_FILTER_DATA(SDFM1_BASE, SDFM_O_SDDATA2);
    filter3Result[loopCounter1]   =
                        READ_16BIT_FILTER_DATA(SDFM1_BASE, SDFM_O_SDDATA3);
    filter4Result[loopCounter1++] =
                        READ_16BIT_FILTER_DATA(SDFM1_BASE, SDFM_O_SDDATA4);

    //
    // Clear SDFM flag register
    //
    SDFM_clearInterruptFlag(SDFM1_BASE, SDFM_INT_MASK);
}

//
// sdfm2ISR - SDFM 2 ISR
//
void sdfm2ISR(void)
{
    static uint16_t loopCounter2 = 0;

    //
    // Wait for result from all the filters (SDIFLG)
    //
    while((HWREG(SDFM2_BASE + SDFM_O_SDIFLG) & SDFM_INT_MASK) != SDFM_INT_MASK);

    //
    // Reset the loop counter
    //
    if(loopCounter2 >= MAX_SAMPLES)
    {
        loopCounter2 = 0;
    }

    //
    // Read each SDFM filter output and store it in respective filter
    // result array
    //
    filter1Result[loopCounter2]   =
                        READ_16BIT_FILTER_DATA(SDFM2_BASE, SDFM_O_SDDATA1);
    filter2Result[loopCounter2]   =
                        READ_16BIT_FILTER_DATA(SDFM2_BASE, SDFM_O_SDDATA1);
    filter3Result[loopCounter2]   =
                        READ_16BIT_FILTER_DATA(SDFM2_BASE, SDFM_O_SDDATA1);
    filter4Result[loopCounter2++] =
                        READ_16BIT_FILTER_DATA(SDFM2_BASE, SDFM_O_SDDATA1);

    //
    // Clear SDFM flag register
    //
    SDFM_clearInterruptFlag(SDFM2_BASE, SDFM_INT_MASK);
}

//
// configureSDFMPins - Configure SDFM GPIOs
//
void configureSDFMPins(uint16_t sdfmPinOption)
{
    uint16_t pin;

    switch (sdfmPinOption)
    {
        case SDFM_PIN_MUX_OPTION1:
            for(pin = 16; pin <= 31; pin++)
            {
                if(pin == 18 || pin == 22 || pin ==23 || pin == 29)
                {
                    continue;
                }
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setControllerCore(pin, GPIO_CORE_CPU1);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            GPIO_setDirectionMode(37, GPIO_DIR_MODE_IN);
            GPIO_setControllerCore(37, GPIO_CORE_CPU1);
            GPIO_setPadConfig(37, GPIO_PIN_TYPE_STD);
            GPIO_setQualificationMode(37, GPIO_QUAL_ASYNC);

            GPIO_setDirectionMode(39, GPIO_DIR_MODE_IN);
            GPIO_setControllerCore(39, GPIO_CORE_CPU1);
            GPIO_setPadConfig(39, GPIO_PIN_TYPE_STD);
            GPIO_setQualificationMode(39, GPIO_QUAL_ASYNC);

            GPIO_setDirectionMode(55, GPIO_DIR_MODE_IN);
            GPIO_setControllerCore(55, GPIO_CORE_CPU1);
            GPIO_setPadConfig(55, GPIO_PIN_TYPE_STD);
            GPIO_setQualificationMode(55, GPIO_QUAL_ASYNC);

            GPIO_setDirectionMode(59, GPIO_DIR_MODE_IN);
            GPIO_setControllerCore(59, GPIO_CORE_CPU1);
            GPIO_setPadConfig(59, GPIO_PIN_TYPE_STD);
            GPIO_setQualificationMode(59, GPIO_QUAL_ASYNC);

            setPinConfig1();
            break;

        case SDFM_PIN_MUX_OPTION2:
            for(pin = 48; pin <= 63; pin++)
            {
                if(pin == 60)
                {
                    continue;
                }
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setControllerCore(pin, GPIO_CORE_CPU1);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            GPIO_setDirectionMode(75, GPIO_DIR_MODE_IN);
            GPIO_setControllerCore(75, GPIO_CORE_CPU1);
            GPIO_setPadConfig(75, GPIO_PIN_TYPE_STD);
            GPIO_setQualificationMode(75, GPIO_QUAL_ASYNC);

            setPinConfig2();
            break;

        case SDFM_PIN_MUX_OPTION3:
            for(pin = 69; pin <= 80; pin++)
            {
                if(pin == 71 || pin == 72)
                {
                    continue;
                }
                GPIO_setControllerCore(pin, GPIO_CORE_CPU1);
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            for(pin = 89; pin <= 98; ++pin)
            {
                if(pin == 91 || pin == 92 || pin == 93 || pin == 94)
                {
                    continue;
                }
                GPIO_setControllerCore(pin, GPIO_CORE_CPU1);
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig3();
            break;
    }
}

//
// done - Function to halt debugger and stop application
//
void done(void)
{
    ESTOP0;
    for(;;);
}

//
// setPinConfig1 - sets the pin configuration for pins 16-55
//
void setPinConfig1()
{
    GPIO_setPinConfig(GPIO_16_SD1_D1);
    GPIO_setPinConfig(GPIO_17_SD1_C1);
    GPIO_setPinConfig(GPIO_37_SD1_D2);
    GPIO_setPinConfig(GPIO_19_SD1_C2);
    GPIO_setPinConfig(GPIO_20_SD1_D3);
    GPIO_setPinConfig(GPIO_21_SD1_C3);
    GPIO_setPinConfig(GPIO_39_SD1_D4);
    GPIO_setPinConfig(GPIO_55_SD1_C4);
    GPIO_setPinConfig(GPIO_24_SD2_D1);
    GPIO_setPinConfig(GPIO_25_SD2_C1);
    GPIO_setPinConfig(GPIO_26_SD2_D2);
    GPIO_setPinConfig(GPIO_27_SD2_C2);
    GPIO_setPinConfig(GPIO_28_SD2_D3);
    GPIO_setPinConfig(GPIO_59_SD2_C3);
    GPIO_setPinConfig(GPIO_30_SD2_D4);
    GPIO_setPinConfig(GPIO_31_SD2_C4);
}

//
// setPinConfig2 - sets the pin configuration for
// pins 48-75(Some pins are not in order)
//
void setPinConfig2()
{
    GPIO_setPinConfig(GPIO_48_SD1_D1);
    GPIO_setPinConfig(GPIO_49_SD1_C1);
    GPIO_setPinConfig(GPIO_50_SD1_D2);
    GPIO_setPinConfig(GPIO_51_SD1_C2);
    GPIO_setPinConfig(GPIO_52_SD1_D3);
    GPIO_setPinConfig(GPIO_53_SD1_C3);
    GPIO_setPinConfig(GPIO_54_SD1_D4);
    GPIO_setPinConfig(GPIO_55_SD1_C4);
    GPIO_setPinConfig(GPIO_56_SD2_D1);
    GPIO_setPinConfig(GPIO_57_SD2_C1);
    GPIO_setPinConfig(GPIO_58_SD2_D2);
    GPIO_setPinConfig(GPIO_59_SD2_C2);
    GPIO_setPinConfig(GPIO_75_SD2_D3);
    GPIO_setPinConfig(GPIO_61_SD2_C3);
    GPIO_setPinConfig(GPIO_62_SD2_D4);
    GPIO_setPinConfig(GPIO_63_SD2_C4);
}

//
// setPinConfig3 - sets the pin configuration for pins 69-98(Some pins are not in order)
//
void setPinConfig3()
{
    GPIO_setPinConfig(GPIO_95_SD1_D1);
    GPIO_setPinConfig(GPIO_96_SD1_C1);
    GPIO_setPinConfig(GPIO_97_SD1_D2);
    GPIO_setPinConfig(GPIO_98_SD1_C2);
    GPIO_setPinConfig(GPIO_89_SD1_D3);
    GPIO_setPinConfig(GPIO_90_SD1_C3);
    GPIO_setPinConfig(GPIO_69_SD1_D4);
    GPIO_setPinConfig(GPIO_70_SD1_C4);
    GPIO_setPinConfig(GPIO_79_SD2_D1);
    GPIO_setPinConfig(GPIO_80_SD2_C1);
    GPIO_setPinConfig(GPIO_73_SD2_D2);
    GPIO_setPinConfig(GPIO_74_SD2_C2);
    GPIO_setPinConfig(GPIO_75_SD2_D3);
    GPIO_setPinConfig(GPIO_76_SD2_C3);
    GPIO_setPinConfig(GPIO_77_SD2_D4);
    GPIO_setPinConfig(GPIO_78_SD2_C4);
}

//
// initEPWM - Initialize specified EPWM settings
//
void initEPWM(uint32_t epwmInstance)
{
    uint16_t compCVal,compDVal;

    compCVal = 200;
    compDVal = 200;

#ifdef CPU1
    GPIO_setDirectionMode(4, GPIO_DIR_MODE_OUT);
    GPIO_setPinConfig(GPIO_4_GPIO4);
#endif

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Setup TBCLK: Configure timer period = 801 TBCLKs, phase = 0 &
    // clear counter
    //
    EPWM_setTimeBasePeriod(epwmInstance, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(epwmInstance, 0U);
    EPWM_setTimeBaseCounter(epwmInstance, 0U);

    //
    // Set CMPA, CMPB, CMPC & CMPD values
    //
    EPWM_setCounterCompareValue(epwmInstance, EPWM_COUNTER_COMPARE_C, compCVal);
    EPWM_setCounterCompareValue(epwmInstance, EPWM_COUNTER_COMPARE_D, compDVal);
    EPWM_setCounterCompareValue(epwmInstance, EPWM_COUNTER_COMPARE_A, compCVal);
    EPWM_setCounterCompareValue(epwmInstance, EPWM_COUNTER_COMPARE_B, compDVal);

    //
    // Setup counter mode
    //
    EPWM_setTimeBaseCounterMode(epwmInstance, EPWM_COUNTER_MODE_UP);
    EPWM_setClockPrescaler(epwmInstance,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set actions:
    // Toggle PWMxA on event A, up-count
    // Toggle PWMxB on event A, up-count
    //
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_TOGGLE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_TOGGLE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// End of file
//