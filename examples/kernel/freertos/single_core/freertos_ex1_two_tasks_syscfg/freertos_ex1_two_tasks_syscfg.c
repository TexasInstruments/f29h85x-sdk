#include "board.h"
#include "c2000_freertos.h"

volatile uint32_t Task1_count, Task2_count;

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
        Task2_count++;
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
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
