#include "board.h"
#include "c2000_freertos.h"

volatile uint32_t Task1_count=0, Task2_count=0;

//-------------------------------------------------------------------------------------------------

void Task1(void * pvParameters)
{
    for(;;)
    {
        Task1_count++;
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

//-------------------------------------------------------------------------------------------------

void Task2(void * pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake( binarySemaphore0Handle, portMAX_DELAY ) == pdTRUE)
        {
            Task2_count++;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void timer1_ISR( void )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR( binarySemaphore0Handle, &xHigherPriorityTaskWoken );

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

//-------------------------------------------------------------------------------------------------

int main(void)
{
    Device_init();
    Board_init();
    Interrupt_enableGlobal();
    FreeRTOS_init();

    return(0);
}
