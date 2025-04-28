//#############################################################################
//
// FILE:   clb_ex2_gpio_input_filter.c
//
// TITLE:  CLB GPIO Input Filter.
//
//! \addtogroup driver_example_list
//! <h1>CLB GPIO Input Filter</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! This example demonstrates use of finite state machines (FSMs) and counters 
//! to implement a simple glitch filter which might, for example, be applied 
//! to an incoming GPIO signal to remove unwanted short duration pulses.
//!
//
//
//#############################################################################


#include "clb_config.h"
#include "board.h"

#define EPWM1_TIMER_TBPRD   0xFFFF
#define EPWM1_CMPA          0x0003
#define EPWM1_CMPB          0xFFFC
#define MODE_CHG_COUNT      10000U

void initEPWM1(void);
void initCLB1(void);

uint32_t ccount = 0UL;
uint16_t cglitch = 3U;


int main(void)
{
    Device_init();

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initEPWM1();
    
    Board_init();

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initTILE1(myTILE1_BASE);
    
    CLB_setOutputMask(myTILE1_BASE, 0x1, true);

    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);

    while(1)
    {
        if (ccount++ > MODE_CHG_COUNT)
        {
            EPWM_setCounterCompareValue (myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, cglitch);
            EPWM_setCounterCompareValue (myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, cglitch);
            ccount = 0;
        }
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
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
}

