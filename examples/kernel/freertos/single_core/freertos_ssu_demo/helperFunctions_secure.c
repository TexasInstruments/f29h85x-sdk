#include "helperFunctions_secure.h"

//
//  Helper function to call the Interrupt_force API from CommonCode
//  Required to force interrupts from LINK3+.
//
void helper_forceInterrupt(uint32_t intNum){
    Interrupt_force(intNum);
}

//
//  Helper function to call portYIELD_FROM_ISR via LINK2
//  Required since implementation calls Interrupt_force
//  internally
//
void helper_portYieldFromISR(BaseType_t xHigherPriorityTaskWoken){
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

//
//  Helper function to call the Interrupt_clearFlag API from CommonCode
//  Required to clear interrupts from LINK3+.
//
void helper_clearInterruptFlag(uint32_t intNum){
    Interrupt_clearFlag(intNum);
}
