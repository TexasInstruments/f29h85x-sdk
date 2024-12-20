//#############################################################################
//
// FILE:   lab_main.c
//
// TITLE:  Lab - CLB Lab
//
//! \addtogroup academy_lab_list
//! <h1> CLB Example Lab</h1>
//!
//!
//!
//! \b External \b Connections \n
//!  - GPIO6 is a GPIO input used to enable / disable the EPWM output
//!  - GPIO0 is the EPWM output which should be probed by an oscilloscope
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "clb_config.h"
#include "clb.h"

//
// Global variables and definitions
//
#define     SENSOR_HIGH_INT_TAG 1
#define     SENSOR_LOW_INT_TAG  2
uint16_t    tag;

__attribute__((interrupt("INT"))) void INT_myCLB1_ISR(void);

int main(void)
{
    // CPU Initialization
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();

    // Configure the GPIOs/XBARs/PWM/CLB/LEDs through
    // SysConfig-generated function found within board.c
    Board_init();
    Interrupt_register(INT_CLB1, &INT_myCLB1_ISR);
    Interrupt_enable(INT_CLB1);
    // Initialize and enable the CLB1 tile
    initTILE1(myCLB1_BASE);
    CLB_enableCLB(myCLB1_BASE);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    // Main Loop
    for(;;)
    {

        __asm(" NOP #1");
    }
}

__attribute__((interrupt("INT"))) void INT_myCLB1_ISR(void)
{
    // Get interrupt tag upon HLC interrupt
    tag = CLB_getInterruptTag(myCLB1_BASE);

    // Turn off EPWM LED and turn on SENSOR LED
    if (tag == SENSOR_HIGH_INT_TAG)
    {
        GPIO_writePin(LED_EPWM_GPIO, 1);
        GPIO_writePin(LED_SENSOR_GPIO, 0);
    }

    // Turn on EPWM LED and turn off SENSOR LED
    if (tag == SENSOR_LOW_INT_TAG)
    {
        GPIO_writePin(LED_EPWM_GPIO, 0);
        GPIO_writePin(LED_SENSOR_GPIO, 1);
    }

    CLB_clearInterruptTag(myCLB1_BASE);
}

