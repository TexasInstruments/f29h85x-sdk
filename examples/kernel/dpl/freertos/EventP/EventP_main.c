//#############################################################################
//
// FILE:   EventP_main.c
//
// TITLE:  DPL freertos EventP example
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
#define HWI_PRI                 (20U)
//
//  Events
//
#define EVENT_BIT_2             (0x4U)
#define EVENT_BIT_4             (0x10U)
#define EVENT_BIT_6             (0x40U)

//
//  Globals
//
//
//  Task stack
//
uint8_t gTask1Stack[TASK_STACK_SIZE] __attribute__((aligned(32)));
uint8_t gTask2Stack[TASK_STACK_SIZE] __attribute__((aligned(32)));
//
//  Objects
//
TaskP_Object    gTask1Obj;
TaskP_Object    gTask2Obj;
EventP_Object   gEventObj;
HwiP_Object     gHwiObj;
uint32_t        gEventCreated = 0U;

//
//  task2Main
//
void task2Main(void *args)
{
    int32_t  status;
    uint32_t eventBits;

    DebugP_log("Entered Task 2 ...\n");

    for(;;)
    {
        //
        //  Wait for event bit 2
        //
        status = EventP_waitBits(
                        &gEventObj,
                        EVENT_BIT_2,            // bitsToWaitFor
                        1U,                     // clearOnExit
                        0U,                     // waitForAll
                        SystemP_WAIT_FOREVER,   // timeToWaitInTicks
                        &eventBits);            // eventBits
        DebugP_assert(status == SystemP_SUCCESS);

        DebugP_log("Task2 Event = 0x%X\n", eventBits);

        //
        //  Wait for event bit 4
        //
        status = EventP_waitBits(
                        &gEventObj,
                        EVENT_BIT_4,            // bitsToWaitFor
                        1U,                     // clearOnExit
                        0U,                     // waitForAll
                        SystemP_WAIT_FOREVER,   // timeToWaitInTicks
                        &eventBits);            // eventBits
        DebugP_assert(status == SystemP_SUCCESS);

        DebugP_log("Task2 Event = 0x%X\n", eventBits);

        //
        //  Set event bit 6
        //
        status = EventP_setBits(&gEventObj, EVENT_BIT_6);
        DebugP_assert(status == SystemP_SUCCESS);
    }
}

//
//  Software interrupt handler
//
void swiHandler(void)
{
    int32_t status;

    if(1U == gEventCreated)
    {
        //
        //  Event set bit 4
        //
        status = EventP_setBits(&gEventObj, EVENT_BIT_4);
        DebugP_assert(status == SystemP_SUCCESS);
    }
}

//
//  task1Main
//
void task1Main(void *args)
{
    int32_t         status;
    uint32_t        cnt;
    uint32_t        eventBits;
    TaskP_Params    taskParams;

    DebugP_log("Entered Task 1 ...\n");

    //
    //  Main loop for the example
    //
    for(;;)
    {
        //
        //  Construct an event
        //
        status = EventP_construct(&gEventObj);
        DebugP_assert(status == SystemP_SUCCESS);
        gEventCreated = 1U;

        //
        //  Construct task 2
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

        for(cnt = 0U;cnt < 10U;cnt++)
        {
            //
            //  Set event bit 2
            //
            status = EventP_setBits(&gEventObj, EVENT_BIT_2);
            DebugP_assert(status == SystemP_SUCCESS);

            //
            //  Force software interrupt
            //
            HwiP_post(INT_SW12);

            //
            //  Wait for event bit 6
            //
            status = EventP_waitBits(
                            &gEventObj,
                            EVENT_BIT_6,            // bitsToWaitFor
                            1U,                     // clearOnExit
                            0U,                     // waitForAll
                            SystemP_WAIT_FOREVER,   // timeToWaitInTicks
                            &eventBits);            // eventBits
            DebugP_assert(status == SystemP_SUCCESS);

            DebugP_log("Task1 Event = 0x%X\n", eventBits);
        }

        //
        //  Destruct task 2
        //
        TaskP_destruct(&gTask2Obj);

        //
        //  Destruct event
        //
        gEventCreated = 0U;
        EventP_destruct(&gEventObj);
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
    //  Create task1
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

