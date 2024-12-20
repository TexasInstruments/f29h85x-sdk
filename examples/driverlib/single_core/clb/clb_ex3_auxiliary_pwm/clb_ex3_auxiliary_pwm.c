//#############################################################################
//
// FILE:   clb_ex3_auxiliary_pwm.c
//
// TITLE:  CLB Auxilary PWM.
//
//! \addtogroup driver_example_list
//! <h1>CLB Auxilary PWM</h1>
//!
//! This example configures a CLB tile as an auxiliary PWM generator. The 
//! example uses combinatorial logic (LUTs), state machines (FSMs), counters, 
//! and the high level controller (HLC) to demonstrate the PWM output generation 
//! capabilities using CLB.
//!
//
//
//#############################################################################



#include "clb_config.h"
#include "board.h"

__attribute__((interrupt("INT"))) void clb1ISR(void);

#define ENABLE_AUX_PWM      1
volatile uint16_t dutyValue = 200;

int main(void)
{
    Device_init();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Interrupt_register(INT_CLB1, &clb1ISR);
    Interrupt_enable(INT_CLB1);

	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);

    Board_init();

    initTILE1(myTILE1_BASE);

    CLB_setGPREG(myTILE1_BASE, ENABLE_AUX_PWM);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    CLB_clearInterruptTag(myTILE1_BASE);


    while(1)
    {
        __asm(" NOP #1");
    }
}

__attribute__((interrupt("INT"))) void clb1ISR(void)
{
    GPIO_togglePin(myGPIO0);      // Debug: Used to determine if interrupt is being set

    //
    // Change duty cycle of PWM signal at the end of a period
    //
    if (dutyValue == 150)
    {
        dutyValue = 100U;
    }
    else
    {
        dutyValue = 150U;
    }

    //
    // Load new duty cycle value in HLC Registers
    //
    CLB_setHLCRegisters(myTILE1_BASE, dutyValue, 0, 0, 0);

    CLB_clearInterruptTag(myTILE1_BASE);
}

