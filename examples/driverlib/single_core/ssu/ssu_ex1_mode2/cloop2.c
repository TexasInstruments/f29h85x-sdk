
//
// Included Files
//
#include "app.h"
#include <stdint.h>

//
// Globals
//
uint16_t cpuTimer0IntCount;
uint16_t cpuTimer1IntCount;
uint16_t cpuTimer2IntCount;

//
// Function Prototypes
//
__attribute__((interrupt("RTINT"))) void cpuTimer0ISR(void);
__attribute__((interrupt("RTINT"))) void cpuTimer1ISR(void);
__attribute__((interrupt("RTINT"))) void cpuTimer2ISR(void);

void initCPUTimers(void);
void configCPUTimer(uint32_t, float, float);

void timerSetup(void)
{
    //
    // Initialize timer peripherals
    //
    initCPUTimers();

    //
    // Setup CPU Timers to interrupt every 1, 2 and 4 seconds
    //
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 1000000);
    configCPUTimer(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ, 2000000);
    configCPUTimer(CPUTIMER2_BASE, DEVICE_SYSCLK_FREQ, 4000000);

    //
    // Interrupt enable
    //
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    CPUTimer_enableInterrupt(CPUTIMER1_BASE);
    CPUTimer_enableInterrupt(CPUTIMER2_BASE);
}

void initCPUTimers(void)
{
    //
    // Initialize prescalers to /1
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0);

    //
    // Make sure timers are stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_stopTimer(CPUTIMER2_BASE);

    //
    // Reload counters
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);

    //
    // Reset interrupt counters
    //
    cpuTimer0IntCount = 0;
    cpuTimer1IntCount = 0;
    cpuTimer2IntCount = 0;
}

void configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t perCount;

    //
    // Initialize period
    //
    perCount = (uint32_t)((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, perCount);

    //
    // Set prescale
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Setup timer control
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    //
    // Reset interrupt counters
    //
    if (cpuTimer == CPUTIMER0_BASE)
    {
        cpuTimer0IntCount = 0;
    }
    if (cpuTimer == CPUTIMER1_BASE)
    {
        cpuTimer1IntCount = 0;
    }
    if (cpuTimer == CPUTIMER2_BASE)
    {
        cpuTimer2IntCount = 0;
    }
}

//
// Timer ISRs
//
void cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;
}

void cpuTimer1ISR(void)
{
    cpuTimer1IntCount++;
}

void cpuTimer2ISR(void)
{
    cpuTimer2IntCount++;
}

