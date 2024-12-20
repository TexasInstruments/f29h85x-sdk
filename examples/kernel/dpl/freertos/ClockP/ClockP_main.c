//#############################################################################
//
// FILE:   ClockP_main.c
//
// TITLE:  DPL freertos ClockP example
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
#define TASK_STACK_SIZE                 (2048U)
#define TASK_PRI_1                      (3U)
#define CLOCK_PERIOD_ONESHOT_US         (1000000U)
#define CLOCK_PERIOD_FREE_RUNNING_US    (1000U)

//
//  Globals
//
//
//  Task stack
//
uint8_t gTask1Stack[TASK_STACK_SIZE] __attribute__((aligned(32)));

//
//  Objects
//
TaskP_Object        gTask1Obj;
SemaphoreP_Object   gSemBinaryObj;
ClockP_Object       gClockFreeRunning;
ClockP_Object       gClockOneShot;
uint32_t            gSemCreated             = 0U;
uint32_t            gFreeRunningClockCnout  = 0U;

//
//  One shot Clock callback function
//
void clockCbOneShot(ClockP_Object *hClk, void *arg)
{
    if(1U == gSemCreated)
    {
        //
        //  Post sempahore to wake up the task
        //
        SemaphoreP_post(&gSemBinaryObj);
    }
}

//
//  Free running clock callback function
//
void clockCbFreeRunning(ClockP_Object *hClk, void *arg)
{
    //
    //  Incremnt the clock expiry count
    //
    gFreeRunningClockCnout++;
    DebugP_log("Free running clock:count = %d, tick count = %d, timeout = %d\n",    \
                            gFreeRunningClockCnout,                                 \
                            ClockP_getTicks(),                                      \
                            ClockP_getTimeout(&gClockFreeRunning));
}

//
//  task1Main
//
void task1Main(void *args)
{
    int32_t         status;
    uint32_t        cnt;
    ClockP_Params   clkPrms;

    DebugP_log("Entered Task 1 ...\n");

    //
    //  Main loop for the example
    //
    for(;;)
    {
        //
        //  Construct one shot clock
        //  ->  period = 0
        //
        ClockP_Params_init(&clkPrms);
        clkPrms.start       = false;
        clkPrms.timeout     = ClockP_usecToTicks(CLOCK_PERIOD_ONESHOT_US);
        clkPrms.period      = 0;
        clkPrms.callback    = &clockCbOneShot;
        status = ClockP_construct(&gClockOneShot, &clkPrms);
        DebugP_assert(status == SystemP_SUCCESS);

        //
        //  Create binary semaphore
        //
        status = SemaphoreP_constructBinary(&gSemBinaryObj, 0U);
        DebugP_assert(status == SystemP_SUCCESS);
        gSemCreated = 1U;

        //
        //  Start one shot clock
        //
        ClockP_start(&gClockOneShot);

        //
        //  Wait for one shot clock expiry
        //
        status = SemaphoreP_pend(&gSemBinaryObj, SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);

        //
        //  Log the clock tick count
        //
        DebugP_log("One shot clock expired @ ticks = %d\n", ClockP_getTicks());

        //
        //  Stop one shot clock
        //
        ClockP_stop(&gClockOneShot);

        //
        //  Destruct one shot clock
        //
        ClockP_destruct(&gClockOneShot);

        //
        //  Destruct binary semaphore
        //
        gSemCreated = 0U;
        SemaphoreP_destruct(&gSemBinaryObj);
    }
}

//
// Main
//
int main(void)
{
    int32_t         status;
    TaskP_Params    taskParams;
    ClockP_Params   clkPrms;

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
    //  Create free running clock
    //  ->  period = timeout
    //
    ClockP_Params_init(&clkPrms);
    clkPrms.start       = false;
    clkPrms.timeout     = ClockP_usecToTicks(CLOCK_PERIOD_FREE_RUNNING_US);
    clkPrms.period      = ClockP_usecToTicks(CLOCK_PERIOD_FREE_RUNNING_US);
    clkPrms.callback    = &clockCbFreeRunning;
    status = ClockP_construct(&gClockFreeRunning, &clkPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    //
    //  Start free running clock
    //
    ClockP_start(&gClockFreeRunning);

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

