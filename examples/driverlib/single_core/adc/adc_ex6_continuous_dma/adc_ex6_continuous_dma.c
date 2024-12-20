//###########################################################################
//
// FILE:   adc_ex6_soc_continuous_dma.c
//
// TITLE:  ADC continuous conversions read by DMA.
//
//! \addtogroup driver_example_list
//! <h1> ADC Continuous Conversions Read by DMA (adc_soc_continuous_dma)</h1>
//!
//! This example sets up two ADC channels to convert simultaneously. The
//! results will be transferred by the DMA into a buffer in RAM.
//!
//! \b External \b Connections \n
//!  - A3 & C3 pins should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//! - \b myADC0DataBuffer \b: a digital representation of the voltage on pin A3\n
//! - \b myADC1DataBuffer \b: a digital representation of the voltage on pin C3\n
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
// Function Prototypes
//
__attribute__((interrupt("INT"))) void dmach1ISR(void);

void configureEPWM(uint32_t epwmBase);
void initializeDMA(void);
void configureDMAChannels(void);

//
// Defines
//
#define RESULTS_BUFFER_SIZE     1024 //buffer for storing conversion results
                                //(size must be multiple of 16)

//
// Globals
//
uint16_t myADC0DataBuffer[RESULTS_BUFFER_SIZE];
uint16_t myADC1DataBuffer[RESULTS_BUFFER_SIZE];
volatile uint16_t done;

int main(void)
{
    uint16_t resultsIndex;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    // 
    // Board Initializatrion
    // - Configure the ADCA & ADCC and power it up
    // - Setup the ADC for continuous conversions on channels A3 and C3
    // - Set up ISR for ADCA INT1 - occurs after first conversion
    // - Enable specific PIPE & CPU interrupts: ADCA INT1 - Group 1, interrupt 1
    // - Signal Mode           : single-ended
    // - Conversion Resolution : 12-bit;
    // 
    Board_init();

    //
    // Set up ISRs used by this example
    // ISR for DMA ch1 - occurs when DMA transfer is complete
    //
    Interrupt_register(INT_RTDMA1CH1, &dmach1ISR);

    //
    // Enable specific PIPE interrupt
    //
    Interrupt_enable(INT_RTDMA1CH1);

    //
    // Stop the ePWM clock
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Call the set up function for ePWM 2
    //
    configureEPWM(EPWM2_BASE);

    //
    // Start the ePWM clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize the DMA & configure DMA channels 1 & 2
    //
    initializeDMA();
    configureDMAChannels();

    //
    // Initialize results buffer
    //
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
        myADC0DataBuffer[resultsIndex] = 0;
        myADC1DataBuffer[resultsIndex] = 0;
    }

    //
    // Clearing all pending interrupt flags
    //
    DMA_clearTriggerFlag(RTDMA1CH1_BASE);   // DMA channel 1
    DMA_clearTriggerFlag(RTDMA1CH2_BASE);   // DMA channel 2
    HWREGH(myADC0_BASE + ADC_O_INTFLGCLR) = 0x3U; // ADCA
    HWREGH(myADC1_BASE + ADC_O_INTFLGCLR) = 0x3U; // ADCC
    EPWM_forceADCTriggerEventCountInit(EPWM2_BASE, EPWM_SOC_A); // EPWM2 SOCA
    EPWM_clearADCTriggerFlag(EPWM2_BASE, EPWM_SOC_A);    // EPWM2 SOCA

    //
    // Enable continuous operation by setting the last SOC to re-trigger
    // the first
    //
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0,    // ADCA
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER0,    // ADCC
                               ADC_INT_SOC_TRIGGER_ADCINT2);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start DMA
    //
    done = 0;
    DMA_startChannel(RTDMA1CH1_BASE);
    DMA_startChannel(RTDMA1CH2_BASE);

    //
    // Finally, enable the SOCA trigger from ePWM. This will kick off
    // conversions at the next ePWM event.
    //
    EPWM_enableADCTrigger(EPWM2_BASE, EPWM_SOC_A);

    //
    // Loop until the ISR signals the transfer is complete
    //
    while(done == 0)
    {
        __asm(" NOP #1");
    }
    ESTOP0;
}

//
// adcA1ISR - This is called after the very first conversion and will disable
//                      the ePWM SOC to avoid re-triggering problems.
//

__attribute__((interrupt("INT"))) void adcA1ISR(void)
{
    //
    // Remove ePWM trigger
    //
    EPWM_disableADCTrigger(EPWM2_BASE, EPWM_SOC_A);

    //
    // Disable this interrupt from happening again
    //
    Interrupt_disable(INT_ADCA1);
}

//
// dmach1ISR - This is called at the end of the DMA transfer, the conversions
//              are stopped by removing the trigger of the first SOC from
//              the last.
//
__attribute__((interrupt("INT"))) void dmach1ISR(void)
{
    //
    // Stop the ADC by removing the trigger for SOC0
    //
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0,
                               ADC_INT_SOC_TRIGGER_NONE);
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER0,
                               ADC_INT_SOC_TRIGGER_NONE);
    done = 1;
}

//
// configureEPWM - Set up the ePWM2 module so that the A output has a period
//                 of 40us with a 50% duty. The SOCA signal is coincident with
//                 the rising edge of this.
//
void configureEPWM(uint32_t epwmBase)
{
    //
    // Make the timer count up with a period of 40us
    //
    HWREGH(epwmBase + EPWM_O_TBCTL) = 0x0000U;
    EPWM_setTimeBasePeriod(epwmBase, 4000U);

    //
    // Set the A output on zero and reset on CMPA
    //
    EPWM_setActionQualifierAction(epwmBase, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwmBase, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    //
    // Set CMPA to 20us to get a 50% duty
    //
    EPWM_setCounterCompareValue(epwmBase, EPWM_COUNTER_COMPARE_A, 2000U);

    //
    // Start ADC when timer equals zero (note: don't enable yet)
    //
    EPWM_setADCTriggerSource(epwmBase, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(epwmBase, EPWM_SOC_A, 1U);

    //
    // Enable initialization of the SOCA event counter. Since we are
    // disabling the ETSEL.SOCAEN bit, we need a way to reset the SOCACNT.
    // Hence, enable the counter initialize control.
    //
    EPWM_enableADCTriggerEventCountInit(epwmBase, EPWM_SOC_A);
}

//
// initializeDMA - Initialize DMA through hard reset
//
void initializeDMA(void)
{
    //
    // Perform a hard reset on DMA
    //
    DMA_initController(RTDMA1_BASE);

    //
    // Allow DMA to run free on emulation suspend
    //
    DMA_setEmulationMode(RTDMA1_BASE,DMA_EMULATION_FREE_RUN);
}

//
// configureDMAChannels - Initialize DMA ch 1 to transfer ADCA results
//                        and DMA ch 2 to transfer ADCC results
//
void configureDMAChannels(void)
{
    // Disabling MPU region
    DMA_disableMPU(RTDMA1_MPU_BASE);

    //
    // DMA channel 1 set up for ADCA
    //
    DMA_configAddresses(RTDMA1CH1_BASE, (uint16_t *)&myADC0DataBuffer,
                        (uint16_t *)ADCARESULT_BASE);

    //
    // Perform enough 32-word bursts to fill the results buffer. Data will be
    // transferred 32 bits at a time hence the address steps below.
    //
    DMA_configBurst(RTDMA1CH1_BASE, 64, 4, 4);
    DMA_configTransfer(RTDMA1CH1_BASE, 32, -60, 4);
    DMA_configMode(RTDMA1CH1_BASE, DMA_TRIGGER_ADCA2,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_32BIT));

    DMA_enableTrigger(RTDMA1CH1_BASE);
    DMA_disableOverrunInterrupt(RTDMA1CH1_BASE);
    DMA_setInterruptMode(RTDMA1CH1_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(RTDMA1CH1_BASE);

    //
    // DMA channel 2 set up for ADCC
    //
    DMA_configAddresses(RTDMA1CH2_BASE, (uint16_t *)&myADC1DataBuffer,
                        (uint16_t *)ADCCRESULT_BASE);

    //
    // Perform enough 32-word bursts to fill the results buffer. Data will be
    // transferred 32 bits at a time hence the address steps below.
    //
    DMA_configBurst(RTDMA1CH2_BASE, 64, 4, 4);
    DMA_configTransfer(RTDMA1CH2_BASE, 32, -60, 4);
    DMA_configMode(RTDMA1CH2_BASE, DMA_TRIGGER_ADCA2,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_32BIT));

    DMA_enableTrigger(RTDMA1CH2_BASE);
    DMA_disableOverrunInterrupt(RTDMA1CH2_BASE);
    DMA_setInterruptMode(RTDMA1CH2_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(RTDMA1CH2_BASE);
}

//
// End of file
//
