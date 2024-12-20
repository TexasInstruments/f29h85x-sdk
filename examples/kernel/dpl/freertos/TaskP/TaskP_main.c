//#############################################################################
//
// FILE:   TaskP_main.c
//
// TITLE:  DPL freertos TimerP example
//
//! \addtogroup driver_example_list
//! <h1> CPU Timers </h1>
//!
//! This example creates 2 independent tasks using DPL
//!
//! Syscfg configures DPL and freeRTOS
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - gTask1Count
//! - gTask2Count
//!
//
//#############################################################################

//
// Included Files
//
#include "board.h"
#include "ti_dpl_config.h"
#include "dpl_test.h"
#include "FreeRTOS.h"
#include "task.h"

//
//  Defines
//
#define TASK_STACK_SIZE         (2048U)
#define TASK_PRI_1              (3U)
#define TASK_PRI_2              (3U)

//
//  Globals
//
uint8_t gTask1Stack[TASK_STACK_SIZE] __attribute__((aligned(32)));
uint8_t gTask2Stack[TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gTask1Obj;
TaskP_Object gTask2Obj;
uint32_t gTask1Count = 0U;
uint32_t gTask2Count = 0U;

//
//  task2Main
//
void task2Main(void *args)
{
    TaskP_Load taskLoad;

    DebugP_log("Entered Task 2 ...\n");

    for(;;)
    {
        gTask2Count++;
        ClockP_sleep(1U);
        //
        //  Get task load
        //
        if(8U == gTask2Count)
        {
            TaskP_loadGet(&gTask2Obj, &taskLoad);
            DebugP_log("Task %s load = %d\n", taskLoad.name, taskLoad.cpuLoad);
        }
    }
}

//
//  task1Main
//
void task1Main(void *args)
{
    int32_t         status;
    TaskP_Params    taskParams;
    TaskP_Load      taskLoad;

    DebugP_log("Entered Task 1 ...\n");

    //
    //  Main loop for the example
    //
    for(;;)
    {
        //
        //  Construct Task2
        //
        gTask2Count = 0U;

        TaskP_Params_init(&taskParams);
        taskParams.name         = "Task2";
        taskParams.stackSize    = TASK_STACK_SIZE;
        taskParams.stack        = gTask2Stack;
        taskParams.priority     = TASK_PRI_2;
        taskParams.args         = NULL;
        taskParams.taskMain     = task2Main;
        status = TaskP_construct(&gTask2Obj, &taskParams);
        DebugP_assert(status == SystemP_SUCCESS);

        //
        //  Delay of 10 sec
        //
        ClockP_sleep(10U);

        //
        //  Destruct the Task2
        //
        TaskP_destruct(&gTask2Obj);
    }
}

//
// Main
//
int main(void)
{
    int32_t         status;
    TaskP_Params    taskParams;
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();

    //
    //  DPL init
    //
    Dpl_init();

    //
    //  Construct task1
    //
    TaskP_Params_init(&taskParams);
    taskParams.name         = "Task1";
    taskParams.stackSize    = TASK_STACK_SIZE;
    taskParams.stack        = gTask1Stack;
    taskParams.priority     = TASK_PRI_1;
    taskParams.args         = NULL;
    taskParams.taskMain     = task1Main;
    status = TaskP_construct(&gTask1Obj, &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);

    //
    //  Start freeRTOS scheduler
    //
    vTaskStartScheduler();
}

//
// End of File
//

