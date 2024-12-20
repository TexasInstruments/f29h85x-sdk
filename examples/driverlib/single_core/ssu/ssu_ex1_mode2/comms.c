
//
// Included Files
//
#include "app.h"

void commTask(void) __attribute__((c29_protected_call))
{
    volatile int i;
    GPIO_togglePin(myGPIOOutput0);
    for (i = 63; i; i--);
}
