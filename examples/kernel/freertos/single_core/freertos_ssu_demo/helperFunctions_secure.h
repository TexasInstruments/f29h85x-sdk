#include "board.h"
#include "c2000_freertos.h"
//
// Function prototypes
//
__attribute__((noinline)) 
void helper_portYieldFromISR(BaseType_t xHigherPriorityTaskWoken);

__attribute__((noinline)) 
void helper_forceInterrupt(uint32_t intNum);

__attribute__((noinline)) 
void helper_clearInterruptFlag(uint32_t intNum);