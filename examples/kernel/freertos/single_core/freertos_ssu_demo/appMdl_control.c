//
// All the code in this file executes from LINK5 - Control LINK
//

#include "appMdl_control.h"
#include "helperFunctions_secure.h"

//
// Globals
//
volatile uint16_t task_control_count = 0, timer_int_count = 0;

//
// Secure task placed in LINK2
// Waits on Medium Priority SW interrupt to release a semaphore
// Transmits multiple counts to Comms task
//
void task_ctrl(void * pvParameters){
    for(;;)
    {
        task_control_count++;

        // Some processing
        SysCtl_delay(10);

        vTaskDelay(50);
    }
}

//
// TIMER0 Interrupt
// Triggers a Medium Priority SW interrupt
//
void INT_CPUTimer0_ISR(void){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    timer_int_count++;

    // Some processing
    SysCtl_delay(10);

    // 
    // Force Med priority SWINT
    // Done using helper function since only LINK2 and OWNER_LINK
    // are allowed to write to this bit in the PIPE registers
    //
    helper_forceInterrupt(med_prio_swint);
}
