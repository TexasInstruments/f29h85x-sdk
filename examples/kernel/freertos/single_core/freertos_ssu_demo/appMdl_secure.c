//
// All the code in this file executes from LINK2 - Secure LINK
//

//
// Included Files
//
#include "appMdl_secure.h"

//
// Globals
//
volatile uint16_t mp_swint_count = 0, task_secure_count = 0;
extern uint16_t task_control_count, hp_swint_count, timer_int_count;

//
// FreeRTOS semaphores
//
__attribute__((section(".bsem_secure")))        // Placed in LINK2
SemaphoreHandle_t  bsem_timer_Handle = NULL;
StaticSemaphore_t bsem_timer_Buffer;

__attribute__((section(".bsem_comms")))         // Placed in Comms LINK
SemaphoreHandle_t  bsem_spiToUart_Handle = NULL;
StaticSemaphore_t bsem_spiToUart_Buffer;

//
// Defines needed for interrupt stack switching
//

#define ISR_STACK_LENGTH 256                    // Size of common interrupt stack

__attribute__((section(".isrStackCommon")))     // Common interrupt stack
uint32_t isrStack[ISR_STACK_LENGTH];

uint32_t intNestingLevel = 0;                   // Global to track interrupt nesting
uint32_t lastTaskStackPtr;                      // Global pointing to the last running FreeRTOS task's stack

void (*isrArray[])(void) = {                    // Array of user ISR pointers         
    INT_CPUTimer0_ISR,                          // Index = 0
    INT_SPI_Receive_ISR,                        // Index = 1
    INT_Med_Prio_SWINT_ISR,                     // Index = 2
    INT_Hi_Prio_SWINT_ISR,                      // Index = 3
};


//
//  User ISR for Medium Priority SW interrupt
//  Triggers a High Priority SW interrupt and unblocks Secure task
//
void INT_Med_Prio_SWINT_ISR(void){

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    mp_swint_count++;

    //
    // Halt here to check nesting level
    //
    SysCtl_delay(10);
    
    // Force Hi priority SWINT
    helper_forceInterrupt(high_prio_swint);

    xSemaphoreGiveFromISR( bsem_timer_Handle, &xHigherPriorityTaskWoken );
    helper_portYieldFromISR( xHigherPriorityTaskWoken );
}

//
// Secure task placed in LINK2
// Waits on Medium Priority SW interrupt to release a semaphore
// Transmits multiple counts to Comms task
//
void Task_Secure(void * pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake( bsem_timer_Handle, portMAX_DELAY ) == pdTRUE)
        {
            task_secure_count++;

            //
            //  Transmit count to SPI
            //            
            SPI_writeDataNonBlocking(mySPI0_BASE, timer_int_count);
            SPI_writeDataNonBlocking(mySPI0_BASE, mp_swint_count);
            SPI_writeDataNonBlocking(mySPI0_BASE, hp_swint_count);
            SPI_writeDataNonBlocking(mySPI0_BASE, task_secure_count);
            SPI_writeDataNonBlocking(mySPI0_BASE, task_control_count);
        }
    }
}

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
    //  Board init
    //
    Board_init();

    //
    //  FreeRTOS Setup
    //
    bsem_timer_Handle =
    xSemaphoreCreateBinaryStatic(&bsem_timer_Buffer);
    bsem_spiToUart_Handle =
    xSemaphoreCreateBinaryStatic(&bsem_spiToUart_Buffer);

    FreeRTOS_init();

    //
    // Disable LINK2 AP override
    //
    SSU_disableLink2APOverride(SSU_CPU1);

    //
    // Global interrupt enable
    //
    ENINT;
    Interrupt_enableGlobal();

    ESTOP0;

    vTaskStartScheduler();
    
    //
    // Should not reach
    //
    for(;;)
    {
    }
}