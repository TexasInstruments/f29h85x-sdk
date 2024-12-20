
//
// Included Files
//
#include "app.h"

__attribute__((section(".text.rtos")))
void systemInit(void)
{
    //
    // Enable LINK2 AP override
    //
    SSU_enableLink2APOverride(SSU_CPU1);

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    //  Peripheral init
    //  ADC
    //  PWM
    //  Timers
    //
    Board_init();

    //
    // Disable LINK2 AP override
    //
    SSU_disableLink2APOverride(SSU_CPU1);

    //
    // Global interrupt enable
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Execute tasks
    //
    while (1)
    {
        commTask();
    }
}
