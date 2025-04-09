//
// All the code in this file executes from LINK4 - Comms LINK
//

#include "appMdl_comms.h"
#include "helperFunctions_secure.h"

//
// Globals
//
volatile uint16_t task_comms_count = 0, hp_swint_count = 0;
extern SemaphoreHandle_t  bsem_spiToUart_Handle;

volatile uint16_t rData[] = {0,0,0,0,0};
uint8_t runningMsg[80] = 
"\n--- Tasks running successfully!  \
Inspect countTracker to see execution counts\n";

struct listCounts {
    uint16_t Timer_Interrupt_Count;
    uint16_t Med_Priority_Interrupt_Count;
    uint16_t Hi_Priority_Interrupt_Count;
    uint16_t Secure_Task_Count;
    uint16_t Control_Task_Count;
    uint16_t Comms_Task_Count;
} countTracker;


void task_comms(void * pvParameters){

    uint32_t i;

    for(;;)
    {
        if(xSemaphoreTake( bsem_spiToUart_Handle, portMAX_DELAY ) == pdTRUE)
        {
            task_comms_count++;

            //
            // Parse SPI data & log
            //
            countTracker.Timer_Interrupt_Count = rData[0];
            countTracker.Med_Priority_Interrupt_Count = rData[1];
            countTracker.Hi_Priority_Interrupt_Count = rData[2];
            countTracker.Secure_Task_Count = rData[3];
            countTracker.Control_Task_Count = rData[4];
            countTracker.Comms_Task_Count = task_comms_count;

            UART_writeCharArray(myUART0_BASE, runningMsg, 80);
        }
    }
}

//
//  User ISR for Software Interrupt 12
//
void INT_Hi_Prio_SWINT_ISR(void){
    hp_swint_count++;

    //
    //  Halt here to check nesting level
    //
    SysCtl_delay(10);

}

//
//  User ISR for SPI FIFO Receive interrupt
//
void INT_SPI_Receive_ISR(void)
{
    uint8_t i;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    //
    // Read data
    //
    for(i = 0; i < 5; i++)
    {
        rData[i] = SPI_readDataNonBlocking(mySPI0_BASE);
    }

    //
    // Clear interrupt flag
    //
    SPI_clearInterruptStatus(mySPI0_BASE, SPI_INT_RXFF);
    __asm(" NOP #7");

    //
    // PIPE interrupt flag clear
    // Done using helper function since only LINK2 and OWNER_LINK
    // are allowed to write to this bit in the PIPE registers
    //
    helper_clearInterruptFlag(mySPI0_RX_INT);

    xSemaphoreGiveFromISR( bsem_spiToUart_Handle, &xHigherPriorityTaskWoken );
    helper_portYieldFromISR( xHigherPriorityTaskWoken );
}