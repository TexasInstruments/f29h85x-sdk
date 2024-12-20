//#############################################################################
//
// FILE:   SemaphoreP_mutex_binary_main.c
//
// TITLE:  DPL freertos SemaphoreP_mutex_binary example
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
#define TASK_PRI_2              (5U)
#define TASK_PRI_3              (5U)
#define HWI_PRI                 (20U)

//
//  Globals
//
//
//  Task stack
//
uint8_t gTask1Stack[TASK_STACK_SIZE] __attribute__((aligned(32)));
uint8_t gTask2Stack[TASK_STACK_SIZE] __attribute__((aligned(32)));
uint8_t gTask3Stack[TASK_STACK_SIZE] __attribute__((aligned(32)));
//
//  Objects
//
TaskP_Object        gTask1Obj;
TaskP_Object        gTask2Obj;
TaskP_Object        gTask3Obj;
SemaphoreP_Object   gSemMutexObj;
SemaphoreP_Object   gSemBinaryObj;
SemaphoreP_Object   gSemBinaryIsrObj;
HwiP_Object         gHwiObj;
uint32_t            gSemCreated = 0U;

//
//  task3Main
//
void task3Main(void *args)
{
    int32_t  status;
    uint32_t startCount;
    uint32_t endCount;

    DebugP_log("Entered Task 3 ...\n");

    for(;;)
    {
        //
        //  Get start cycle count
        //
        startCount = CycleCounterP_getCount32();

        //
        //  Lock the mutex
        //
        status = SemaphoreP_pend(&gSemMutexObj, SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);

        //
        //  Delay of 1 sec
        //
        ClockP_sleep(1U);

        //
        //  Unlock mutex
        //
        SemaphoreP_post(&gSemMutexObj);

        //
        //  Get end cycle count
        //
        endCount = CycleCounterP_getCount32();

        DebugP_log("Task 3 delay = %d cycles\n", (endCount - startCount));

        //
        //  Pend on binary Semaphore from ISR
        //
        status = SemaphoreP_pend(&gSemBinaryIsrObj, SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);
    }
}

//
//  task2Main
//
void task2Main(void *args)
{
    int32_t  status;
    uint32_t startCount;
    uint32_t endCount;

    DebugP_log("Entered Task 2 ...\n");

    for(;;)
    {
        //
        //  Get start cycle count
        //
        startCount = CycleCounterP_getCount32();

        //
        //  Lock the mutex
        //
        status = SemaphoreP_pend(&gSemMutexObj, SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);

        //
        //  Delay of 1 sec
        //
        ClockP_sleep(1U);

        //
        //  Unlock mutex
        //
        SemaphoreP_post(&gSemMutexObj);

        //
        //  Get end cycle count
        //
        endCount = CycleCounterP_getCount32();

        DebugP_log("Task 2 delay = %d cycles\n", (endCount - startCount));

        //
        //  Pend on binary Semaphore
        //
        status = SemaphoreP_pend(&gSemBinaryObj, SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);
    }
}

//
//  swiHandler
//
void swiHandler(void)
{
    if(1U == gSemCreated)
    {
        //
        //  Post binary Semaphore from ISR
        //
        SemaphoreP_post(&gSemBinaryIsrObj);
    }
}

//
//  task1Main
//
void task1Main(void *args)
{
    int32_t         status;
    uint32_t        cnt;
    TaskP_Params    taskParams;

    DebugP_log("Entered Task 1 ...\n");

    //
    //  Main loop for the example
    //
    for(;;)
    {
        //
        //  Construct mutex
        //
        status = SemaphoreP_constructMutex(&gSemMutexObj);
        DebugP_assert(status == SystemP_SUCCESS);

        //
        //  Construct binary semaphores
        //
        status = SemaphoreP_constructBinary(&gSemBinaryObj, 0U);
        DebugP_assert(status == SystemP_SUCCESS);

        status = SemaphoreP_constructBinary(&gSemBinaryIsrObj, 0U);
        DebugP_assert(status == SystemP_SUCCESS);
        gSemCreated = 1U;

        //
        //  Construct task2
        //
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
        //  Construct task3
        //
        TaskP_Params_init(&taskParams);
        taskParams.name         = "Task3";
        taskParams.stackSize    = TASK_STACK_SIZE;
        taskParams.stack        = gTask3Stack;
        taskParams.priority     = TASK_PRI_3;
        taskParams.args         = NULL;
        taskParams.taskMain     = task3Main;
        status = TaskP_construct(&gTask3Obj, &taskParams);
        DebugP_assert(status == SystemP_SUCCESS);

        for(cnt = 0U;cnt < 10U;cnt++)
        {
            //
            //  Delay for tasks to complete mutual exclusion
            //
            ClockP_sleep(5U);

            //
            //  Force software interrupt
            //
            HwiP_post(INT_SW12);

            //
            //  Post binary semaphore
            //
            SemaphoreP_post(&gSemBinaryObj);
        }

        //
        //  Destruct tasks
        //
        TaskP_destruct(&gTask2Obj);
        TaskP_destruct(&gTask3Obj);

        //
        //  Destruct mutex and binary Semaphore
        //
        SemaphoreP_destruct(&gSemMutexObj);
        SemaphoreP_destruct(&gSemBinaryObj);
        gSemCreated = 0U;
        SemaphoreP_destruct(&gSemBinaryIsrObj);
    }
}

//
// Main
//
int main(void)
{
    int32_t         status;
    TaskP_Params    taskParams;
    HwiP_Params     hwiParams;

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
    //  Construct software interrupt
    //
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum    = INT_SW12;
    hwiParams.callback  = &swiHandler;
    hwiParams.priority  = HWI_PRI;
    status = HwiP_construct(&gHwiObj, &hwiParams);
    DebugP_assert(status == SystemP_SUCCESS);

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

