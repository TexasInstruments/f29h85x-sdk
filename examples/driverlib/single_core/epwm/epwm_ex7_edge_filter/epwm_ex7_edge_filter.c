//#############################################################################
//
// FILE:   epwm_ex7_edge_filter.c
//
// TITLE:  ePWM Using Digital Compare Submodule with
//         Edge Filter.
//
//! \addtogroup driver_example_list
//! <h1>ePWM Digital Compare Edge Filter</h1>
//!
//! This example configures ePWM1 as follows
//!  - ePWM1 with DCBEVT2 forcing the ePWM output LOW as a CBC source
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCBEVT2
//!  - GPIO25 is set to output and toggled in the main loop to trip the PWM
//!  - The DCBEVT2 is the source for DCFILT
//!  - The DCFILT will count edges of the DCBEVT2 and generate a signal to
//!    to trip the ePWM on the 4th edge of DCBEVT2
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
    // Delay to let ePWM do complete uninterrupted cycles
    // This allows the user to see the PWM waveform uninterrupted
    // on the scope.
    //
    SysCtl_delay(600000U);

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        //
        // Toggle the GPIO multiple times, the trip occurs
        // on the 4th edge
        //
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 4000);
        GPIO_writePin(myGPIO25, 0);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 5000);
        GPIO_writePin(myGPIO25, 1);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 6000);
        GPIO_writePin(myGPIO25, 0);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 7000);
        GPIO_writePin(myGPIO25, 1);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 8000);
        GPIO_writePin(myGPIO25, 0);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 9000);
        GPIO_writePin(myGPIO25, 1);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 10000);
        GPIO_writePin(myGPIO25, 0);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 11000);
        GPIO_writePin(myGPIO25, 1);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) > 3000);
        GPIO_writePin(myGPIO25, 1);
        NOP;
    }
}

void epwm1ISR(void)
{
    EPWM_clearTripZoneFlag(myEPWM1_BASE, EPWM_TZ_FLAG_CBC | EPWM_TZ_FLAG_DCBEVT2 | EPWM_TZ_INTERRUPT);
    EPWM_clearCycleByCycleTripZoneFlag(myEPWM1_BASE, EPWM_TZ_CBC_FLAG_DCBEVT2);

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

}

