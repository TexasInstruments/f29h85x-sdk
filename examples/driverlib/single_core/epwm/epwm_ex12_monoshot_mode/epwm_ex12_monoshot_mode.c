//#############################################################################
//
// FILE:   epwm_ex12_monoshot_mode.c
//
// TITLE:  Realization of Monoshot mode
//
//! \addtogroup driver_example_list
//! <h1>Realization of Monoshot mode</h1>
//!
//! This example showcases how to generate monoshot PWM output based on external
//! trigger i.e. generating just a single pulse output on receipt of an external
//! trigger. And the next pulse will be generated only when the next trigger
//! comes. The example utilizes external synchronization and T1 action qualifier
//! event features to achieve the desired output.
//!
//! ePWM1 is used to generate the monoshot output and ePWM2 is used an external
//! trigger for that. No external connections are required as ePWM2A is fed
//! as the trigger using Input X-BAR automatically.
//!
//! ePWM1 is configured to generated a single pulse of 0.5us when received
//! an external trigger. This is achieved by enabling the phase synchronization
//! feature and configuring EPWMxSYNCI as EXTSYNCIN1. And this EPWMxSYNCI
//! is also configured as T1 event of action qualifier to set output HIGH while
//! "CTR = PRD" action is used to set output LOW.
//!
//! ePWM2 is configured to generate a 100 KHz signal with a duty of 1% (to
//! simulate a rising edge trigger) which is routed to EXTSYNCIN1 using Input XBAR.
//!
//! Observe GPIO0 (EPWM1A : Monoshot Output) and GPIO2(EPWM2 : External Trigger)
//! on oscilloscope.
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


int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure ePWM1, ePWM2 GPIOs and Modules
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

