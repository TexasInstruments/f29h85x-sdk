//#############################################################################
//
// FILE:   clb_ex4_pwm_protection.c
//
// TITLE:  CLB PWM Protection.
//
//! \addtogroup driver_example_list
//! <h1>CLB PWM Protection</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! This example extends the features of example 1 to ensure an active high 
//! complementary pair PWM configuration always operates with a minimum value 
//! of dead-band irrespective of how the generating PWM module is configured. 
//! The example illustrates the configuration of four separate PWM tiles to 
//! implement PWM protection on four PWM modules. The outputs of PWM modules 
//! 1 to 4 are operated on by CLB tiles 1 to 4, respectively.
//!
//
//
//#############################################################################

#include "clb_config.h"
#include "board.h"

#define EPWM1_TIMER_TBPRD   2000U
#define EPWM1_CMPA           933U
#define EPWM1_CMPB           933U

#define EPWM2_TIMER_TBPRD   2000U
#define EPWM2_CMPA           933U
#define EPWM2_CMPB           933U

#define EPWM3_TIMER_TBPRD   2000U
#define EPWM3_CMPA           933U
#define EPWM3_CMPB           933U

#define EPWM4_TIMER_TBPRD   2000U
#define EPWM4_CMPA           933U
#define EPWM4_CMPB           933U


void initEPWM1(void);
void initEPWM2(void);
void initEPWM3(void);
void initEPWM4(void);
__attribute__((interrupt("INT"))) void epwm1ISR(void);

uint32_t mode = 0;


int main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_register(INT_EPWM1, &epwm1ISR);

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB2);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB3);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB4);

    Board_init();

    initTILE1(myTILE1_BASE);
    initTILE2(myTILE2_BASE);
    initTILE3(myTILE3_BASE);
    initTILE4(myTILE4_BASE);

    initEPWM1();
    initEPWM2();
    initEPWM3();
    initEPWM4();

    // start PWMs
    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(myEPWM2_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(myEPWM3_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(myEPWM4_BASE, EPWM_COUNTER_MODE_UP);

    Interrupt_enable(INT_EPWM1);
    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    while(1)
    {
        __asm(" NOP #1");
    }
}


void initEPWM1()
{
    EPWM_setTimeBasePeriod(myEPWM1_BASE, EPWM1_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0U);

    EPWM_enableSyncOutPulseSource(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);

    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM1_CMPA);
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM1_CMPB);

    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setInterruptSource(myEPWM1_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(myEPWM1_BASE);
    EPWM_setInterruptEventCount(myEPWM1_BASE, 3U);
}


void initEPWM2()
{
    EPWM_setTimeBasePeriod(myEPWM2_BASE, EPWM2_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM2_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM2_BASE, 0U);

    EPWM_enablePhaseShiftLoad(myEPWM2_BASE);
    EPWM_setPhaseShift(myEPWM2_BASE, 0U);

    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM2_CMPA);
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM2_CMPB);

    EPWM_setClockPrescaler(myEPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
}


void initEPWM3()
{
    EPWM_setTimeBasePeriod(myEPWM3_BASE, EPWM3_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM3_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM3_BASE, 0U);

    EPWM_enablePhaseShiftLoad(myEPWM3_BASE);
    EPWM_setPhaseShift(myEPWM3_BASE, 0U);

    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM3_CMPA);
    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM3_CMPB);

    EPWM_setClockPrescaler(myEPWM3_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
}


void initEPWM4()
{
    EPWM_setTimeBasePeriod(myEPWM4_BASE, EPWM4_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM4_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM4_BASE, 0U);

    EPWM_enablePhaseShiftLoad(myEPWM4_BASE);
    EPWM_setPhaseShift(myEPWM4_BASE, 0U);

    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM4_CMPA);
    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM4_CMPB);

    EPWM_setClockPrescaler(myEPWM4_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
}


__attribute__((interrupt("INT"))) void epwm1ISR(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

    if (mode == 0)
    {
        CLB_setOutputMask(myTILE1_BASE, 0x5, false);
        CLB_setOutputMask(myTILE2_BASE, 0x5, false);
        CLB_setOutputMask(myTILE3_BASE, 0x5, false);
        CLB_setOutputMask(myTILE4_BASE, 0x5, false);
    }
    else
    {
        CLB_setOutputMask(myTILE1_BASE, 0x5, true);
        CLB_setOutputMask(myTILE2_BASE, 0x5, true);
        CLB_setOutputMask(myTILE3_BASE, 0x5, true);
        CLB_setOutputMask(myTILE4_BASE, 0x5, true);
    }
    __asm(" NOP #1");
}

/* end of file */
