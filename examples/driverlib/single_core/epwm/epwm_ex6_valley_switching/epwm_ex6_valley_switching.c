//#############################################################################
//
// FILE:   epwm_ex6_valley_switching.c
//
// TITLE:  ePWM Using Valley Switching
//
//! \addtogroup driver_example_list
//! <h1>ePWM Valley Switching</h1>
//!
//! This example configures ePWM1 as follows
//!  - ePWM1 with DCAEVT1 forcing the ePWM output LOW
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO25 is set to output and toggled in the main loop to trip the PWM
//!
//!  - ePWM1 with DCBEVT1 forcing the ePWM output LOW
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO25 is set to output and toggled in the main loop to trip the PWM
//!  - DCBEVT1 uses the filtered version of DCBEVT1
//!  - The DCFILT signal uses the valley switching module to delay the
//!  - DCFILT signal by a software defined DELAY value.
//!
//! \b External \b Connections \n
//! - GPIO0 EPWM1A
//! - GPIO1 EPWM1B
//! - GPIO25 TRIPIN1 (Output Pin, toggled through software)
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
// Function Prototypes
//
__attribute__((interrupt("INT"))) void epwm1ISR(void);

int main(void)
{

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
    GPIO_writePin(myGPIO25, 1);

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
    // Delay so the PWM runs for a some time to see the Waveform on
    // scope
    //

    SysCtl_delay(600000U);
    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        //
        // PULL Trip GPIO LOW from CTR=4000 to 11000
        // PULL Trip GPIO HIGH at CTR=11000
        //
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 4000);
        GPIO_writePin(myGPIO25, 0);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 11000);
        GPIO_writePin(myGPIO25, 1);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) > 3000);
        GPIO_writePin(myGPIO25, 1);
        NOP;
    }
}

void epwm1ISR(void){

    EPWM_clearTripZoneFlag(myEPWM1_BASE, EPWM_TZ_FLAG_OST | EPWM_TZ_FLAG_DCAEVT1 | EPWM_TZ_FLAG_DCBEVT1 | EPWM_TZ_INTERRUPT);
    EPWM_clearOneShotTripZoneFlag(myEPWM1_BASE, EPWM_TZ_OST_FLAG_DCBEVT1);

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);
}



