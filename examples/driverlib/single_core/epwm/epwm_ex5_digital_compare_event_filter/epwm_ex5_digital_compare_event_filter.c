//#############################################################################
//
// FILE:   epwm_ex5_digital_compare_event_filter.c
//
// TITLE:  ePWM Using Digital Compare Submodule with
//         Event Filter (Blanking Window).
//
//! \addtogroup driver_example_list
//! <h1>ePWM Digital Compare Event Filter Blanking Window</h1>
//!
//! This example configures ePWM1 as follows
//!  - ePWM1 with DCAEVT1 forcing the ePWM output LOW
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO25's PULL-UP resistor is enabled, in order to test the trip, PULL
//!    this pin to GND
//!
//!  - ePWM1 with DCBEVT1 forcing the ePWM output LOW
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO25's PULL-UP resistor is enabled, in order to test the trip, PULL
//!    this pin to GND
//!  - DCBEVT1 uses the filtered version of DCBEVT1
//!  - The DCFILT signal uses the blanking window to ignore the DCBEVT1
//!    for the duration of DC Blanking window
//!
//! \b External \b Connections \n
//! - GPIO0 EPWM1A
//! - GPIO1 EPWM1B
//! - GPIO25 TRIPIN1, pull this pin low to trip the ePWM
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
    // To re-enable the Interrupts
    //
    EPWM_clearTripZoneFlag(EPWM1_BASE,
                           EPWM_TZ_FLAG_DCAEVT1 | EPWM_TZ_FLAG_DCBEVT1 | EPWM_TZ_INTERRUPT);

}

