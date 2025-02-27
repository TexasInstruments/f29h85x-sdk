
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

