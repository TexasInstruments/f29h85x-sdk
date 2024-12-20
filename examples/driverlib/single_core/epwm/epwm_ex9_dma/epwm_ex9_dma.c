//#############################################################################
//
// FILE:   epwm_ex9_dma.c
//
// TITLE:  ePWM Using DMA.
//
//! \addtogroup driver_example_list
//! <h1>ePWM DMA</h1>
//!
//! This example configures ePWM1 and DMA as follows:
//!  - ePWM1 is set up to generate PWM waveforms
//!  - DMA5 is set up to update the CMPAHR, CMPA, CMPBHR and CMPB every period
//!    with the next value in the configuration array. This allows the user to
//!    create a DMA enabled fifo for all the CMPx and CMPxHR registers to
//!    generate unconventional PWM waveforms.
//!  - DMA6 is set up to update the TBPHSHR, TBPHS, TBPRDHR and TBPRD every
//!    period with the next value in the configuration array.
//!  - Other registers such as AQCTL can be controlled through the DMA as well
//!    by following the same procedure. (Not used in this example)
//!
//! \b External \b Connections \n
//! - GPIO0 EPWM1A
//! - GPIO1 EPWM1B
//!
//! \b Watch \b Variables \n
//! - None.
//
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

#define EPWM_TIMER_TBPRD    20000UL

//
// Defines
//
#define BURST       8              // 4 words per transfer
#define TRANSFER    4              // 4 transfers (different configs)

//
// Globals
//

uint16_t phasePeriodConfigs[TRANSFER*BURST] = {
//  TBPHSHR ,   TBPHS   ,  TBPRDHR ,   TBPRD,
    9  << 8 ,    17U    ,  13 << 8 ,   2000U,
    10 << 8 ,    18U    ,  14 << 8 ,   4000U,
    11 << 8 ,    19U    ,  15 << 8 ,   6000U,
    12 << 8 ,    20U    ,  16 << 8 ,   8000U,
};

uint16_t compareConfigs[TRANSFER*BURST] = {
//  CMPAHR  ,   CMPA   ,   CMPBHR  ,   CMPB ,
    1 << 8  ,  1001U   ,   5 << 8  ,   1000U,
    2 << 8  ,  2001U   ,   6 << 8  ,   2000U,
    3 << 8  ,  3001U   ,   7 << 8  ,   3000U,
    4 << 8  ,  4001U   ,   8 << 8  ,   4000U,
};

//
// Function Prototypes
//
void initDMA(void);
void initEPWM(uint32_t base);

__attribute__((interrupt("INT")))  void dmaCh5ISR(void);
__attribute__((interrupt("INT")))  void dmaCh6ISR(void);
__attribute__((interrupt("INT")))  void epwm1ISR(void);

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
    // Assign the interrupt service routines to ePWM interrupts
    //
    Interrupt_register(INT_EPWM1, &epwm1ISR);
    Interrupt_register(INT_RTDMA1CH5, &dmaCh5ISR);
    Interrupt_register(INT_RTDMA1CH6, &dmaCh6ISR);

    //
    // Configure EPWM and Input X-BAR Pins
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initDMA();
    initEPWM(myEPWM1_BASE);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


    // Enable ePWM interrupts
    //
    Interrupt_enable(INT_EPWM1);
    Interrupt_enable(INT_RTDMA1CH5);
    Interrupt_enable(INT_RTDMA1CH6);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    DMA_startChannel(RTDMA1CH5_BASE);
    DMA_startChannel(RTDMA1CH6_BASE);

    //
    // IDLE loop. Just sit and loop forever (optional):
    //

    for(;;)
    {

    }
}


//
// DMA setup channels.
//
void initDMA()
{
    //
    // Initialize DMA
    //
    DMA_initController(RTDMA1_BASE);
    DMA_disableMPU(RTDMA1_MPU_BASE);

    //
    // DMA CH5
    //

    DMA_configAddresses(RTDMA1CH5_BASE, (uint16_t *)(myEPWM1_BASE + EPWM_O_CMPA),
                        compareConfigs);
    DMA_configBurst(RTDMA1CH5_BASE, BURST, 2, 2);
    DMA_configTransfer(RTDMA1CH5_BASE, TRANSFER, 2, (2-BURST));
    DMA_configMode(RTDMA1CH5_BASE, DMA_TRIGGER_EPWM1SOCA, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA Ch5 interrupts
    //
    DMA_setInterruptMode(RTDMA1CH5_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(RTDMA1CH5_BASE);
    DMA_enableTrigger(RTDMA1CH5_BASE);

    //
    // DMA CH6
    //
    DMA_configAddresses(RTDMA1CH6_BASE, (uint16_t *)(myEPWM1_BASE + EPWM_O_TBPHS),
                        phasePeriodConfigs);
    DMA_configBurst(RTDMA1CH6_BASE, BURST, 2, 2);
    DMA_configTransfer(RTDMA1CH6_BASE, TRANSFER, 2, (2-BURST));
    DMA_configMode(RTDMA1CH6_BASE, DMA_TRIGGER_EPWM1SOCA, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA Ch6 interrupts
    //
    DMA_setInterruptMode(RTDMA1CH6_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(RTDMA1CH6_BASE);
    DMA_enableTrigger(RTDMA1CH6_BASE);

}

//
// DMA Channel 5 ISR
//
__attribute__((interrupt("INT")))  void dmaCh5ISR(void)
{
    return;
}

//
// DMA Channel 6 ISR
//
__attribute__((interrupt("INT")))  void dmaCh6ISR(void)
{
    return;
}


//
// epwm1ISR - ePWM 1 ISR
//
__attribute__((interrupt("INT")))  void epwm1ISR(void)
{
    //
    // Un-comment below to check the status of each register after CTR=0
    //
    // ESTOP0;

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);
}


void initEPWM(uint32_t base)
{
    EPWM_setEmulationMode(base, EPWM_EMULATION_STOP_AFTER_FULL_CYCLE);

    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(base, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(base, 0U);
    EPWM_setTimeBaseCounter(base, 0U);

    //
    // Set Compare values
    //
    EPWM_setCounterCompareValue(base,
                                EPWM_COUNTER_COMPARE_A,
                                EPWM_TIMER_TBPRD/2);
    EPWM_setCounterCompareValue(base,
                                EPWM_COUNTER_COMPARE_B,
                                EPWM_TIMER_TBPRD/2);

    //
    // Set up counter mode
    //
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(base);
    EPWM_setClockPrescaler(base,
                           EPWM_CLOCK_DIVIDER_64,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    //

    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);


    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);


    //
    // Interrupt where we will change the Compare Values
    // Select INT on Time base counter zero event,
    // Enable INT, generate INT on 1st event
    //
    EPWM_setInterruptSource(base, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(base);
    EPWM_setInterruptEventCount(base, 1U);

    EPWM_enableADCTrigger(base, EPWM_SOC_A);
    EPWM_setADCTriggerSource(base,
                             EPWM_SOC_A,
                             EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(base,
                                    EPWM_SOC_A,
                                       1);
    EPWM_clearADCTriggerFlag(base,
                             EPWM_SOC_A);
}

