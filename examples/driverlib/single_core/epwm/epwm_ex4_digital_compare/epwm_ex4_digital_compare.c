//#############################################################################
//
// FILE:   epwm_ex4_digital_compare.c
//
// TITLE:  ePWM Using Digital Compare Submodule.
//
//! \addtogroup driver_example_list
//! <h1>ePWM Digital Compare</h1>
//!
//! This example configures ePWM1 as follows
//!  - ePWM1 with DCAEVT1 forcing the ePWM output LOW
//!  - GPIO2 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO2's PULL-UP resistor is enabled, in order to test the trip, PULL
//!    this pin to GND
//!
//! \b External \b Connections \n
//! - GPIO0 EPWM1A
//! - GPIO1 EPWM1B
//! - GPIO2 TZ1, pull this pin low to trip the ePWM
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

//
// Globals
//
uint32_t  epwm1TZIntCount;

//
// Function Prototypes
//
__attribute__((interrupt("INT"))) void epwm1TZISR(void);

int main(void)
{
    //
    // Initialize global variables
    //
    epwm1TZIntCount = 0U;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure ePWM1, and TZ GPIOs
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        NOP;
    }
}

//
// epwm1TZISR - ePWM1 TZ ISR
//
void epwm1TZISR(void)
{
    epwm1TZIntCount++;

    //
    // Uncomment the below lines of code to re-enable the interrupts
    //
    //EPWM_clearTripZoneFlag(EPWM1_BASE, EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_DCAEVT1);

    //
    // Uncomment the below lines of code to re-enable
    // the interrupts and the ePWM output if using one-shot
    //
    //EPWM_clearTripZoneFlag(EPWM1_BASE, EPWM_TZ_FLAG_OST | EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_DCAEVT1);
}


