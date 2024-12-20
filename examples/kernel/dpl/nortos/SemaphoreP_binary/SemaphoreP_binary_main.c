//#############################################################################
//
//   FILE:  SemaphoreP_binary.c
//
//   TITLE: SemaphoreP Examples
//
//
//! \addtogroup dpl_example_list
//! <h1> SemaphoreP Binary Example </h1>
//!
//! Sysconfig is used to configure the device and CPU timer1. The
//! timer 1 interrupt is configured using the DPL HwiP API.
//! SemaphoreP is used to create a binary semaphore. The semaphore is posted
//! in the ISR when the count is INT_COUNT1, INT_COUNT2, INT_COUNT3, and INT_COUNT4
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - cpuTimer1IntCount
//
//
//#############################################################################
//  $ Copyright: $
//#############################################################################



//
// Define as 1 to turn off some of the debugP logging messages
// in favor of execution speed. Asserts will still be checked.
// This needs to be before #include dpl_test.h
//
#define QUIET 0


//
// Included Files
//
#include "board.h"
#include "ti_dpl_config.h"
#include "dpl_test.h"

//
// Prototypes for the interrupt callback functions for INT
//
void cpuTimer1Callback(void);

//
// Globals
//
volatile uint32_t cpuTimer1IntCount;
HwiP_Object cpuTimer1HwiObject;
SemaphoreP_Object cpuTimer1BinarySemObject;

//
// For this example RTINT_THRESHOLD should be
// a number greater lower than the priority level of
// CPU Timer 1
//
#define RTINT_THRESHOLD     ((uint8_t)15)
#define CPU_TIMER1_PRIORITY ((uint8_t)20)

//
// Defines to compare to the return value of HwiP_inISR
//
#define CPU_TIMER1_IN_ISR   HWIP_IN_ISR_INT

__attribute__((retain)) uint32_t status;
__attribute__((retain)) uint32_t intCount;
__attribute__((retain)) uint32_t errorFlag;
__attribute__((retain)) uint8_t inISR;
__attribute__((retain)) uint8_t cpuID;
__attribute__((retain)) SemaphoreP_Struct *cpuTimer1BinarySem;

//
// cpuTimer1IntCount when the "resource" is made available
// That is the binary semaphore is posted
//
#define INT_COUNT1 10U
#define INT_COUNT2 22U
#define INT_COUNT3 39U
#define INT_COUNT4 52U


//
// Main
//
int main(void)
{
    DebugP_log("\r\n\r\n----------------- Starting %s test ----------------- \r\n",__FILE__);
    cpuID = CpuIdP_c29GetCpuID();
    DebugP_logInfo("Running on CPU %d. \r\n", cpuID);
    DebugP_logInfo("Checking HwiP priorities. Timer 1 is INT. \r\n");
    testCheck(RTINT_THRESHOLD, "<", CPU_TIMER1_PRIORITY, "TIMER1");

    DebugP_logInfo("Configure CPU Timer1 and device. Leave timer halted.\r\n");
    Device_init();
    Board_init();
    Dpl_init();

    HwiP_enable();
    __builtin_c29_enable_INT();

    DebugP_logInfo("Check HwiP_inISR while in main:\r\n");
    inISR = HwiP_inISR();
    testCheck(inISR, "==", HWIP_IN_ISR_MAIN, "IN_ISR");

    SemaphoreP_Params SemParams;
    SemaphoreP_Params_init(&SemParams);

    DebugP_logInfo("Create binary Semaphore:\r\n");
    status = SemaphoreP_constructBinary(&cpuTimer1BinarySemObject, 0);
    testCheck(SystemP_SUCCESS, "==", status, "Binary");
    cpuTimer1BinarySem = (SemaphoreP_Struct *)&cpuTimer1BinarySemObject;

    HwiP_Params HwiParams;
    HwiP_Params_init(&HwiParams);

    //
    // setup normal interrupts (INT)
    //
    DebugP_logInfo("HwiP_construct() INT Interrupts:\r\n");
    HwiParams.isRTINT = 0;
    HwiParams.rtintHandler = NULL;

    HwiParams.intNum = INT_TIMER1;
    HwiParams.priority = CPU_TIMER1_PRIORITY;
    HwiParams.callback = &cpuTimer1Callback;
    errorFlag = SystemP_FAILURE;
    errorFlag = HwiP_construct(&cpuTimer1HwiObject, &HwiParams);
    testCheck(errorFlag, "==", SystemP_SUCCESS, "INT_TIMER1");

    DebugP_logInfo("Set RTINT threshold and enable interrupts.\r\n");
    HwiP_setRTINTThreshold(RTINT_THRESHOLD);

    //
    // CPU timer level, PIPE level and CPU level
    //
    CPUTimer_enableInterrupt(myCPUTIMER1_BASE);
    HwiP_enableInt(INT_TIMER1);


    CPUTimer_startTimer(myCPUTIMER1_BASE);

    DebugP_logInfo("Wait forever for resource.... \r\n");
    DebugP_logInfo("Resource will be made available in INT_COUNT1, INT_COUNT2, INT_COUNT3 and INT_COUNT4 of CPU Timer 1 ISR: \r\n");
    SemaphoreP_pend(&cpuTimer1BinarySemObject, SystemP_WAIT_FOREVER);
    testCheck(cpuTimer1IntCount, "==", INT_COUNT1, "INT_COUNT1");

    SemaphoreP_pend(&cpuTimer1BinarySemObject, SystemP_WAIT_FOREVER);
    testCheck(cpuTimer1IntCount, "==", INT_COUNT2, "INT_COUNT2");

    SemaphoreP_pend(&cpuTimer1BinarySemObject, SystemP_WAIT_FOREVER);
    testCheck(cpuTimer1IntCount, "==", INT_COUNT3, "INT_COUNT3");

    SemaphoreP_pend(&cpuTimer1BinarySemObject, SystemP_WAIT_FOREVER);
    testCheck(cpuTimer1IntCount, "==", INT_COUNT4, "INT_COUNT4");

    DebugP_log("\r\n\r\n-----------------       All done!        ----------------- \r\n");
    __asm("  EMUSTOP0");
}

//
//
//

void cpuTimer1Callback(void)
{
    uint8_t temp;
    temp = HwiP_inISR();
    if(temp == CPU_TIMER1_IN_ISR)
    {
        cpuTimer1IntCount++;
        if(cpuTimer1IntCount == INT_COUNT1)
        {
            SemaphoreP_post(&cpuTimer1BinarySemObject);
        }
        else if(cpuTimer1IntCount == INT_COUNT2)
        {
            SemaphoreP_post(&cpuTimer1BinarySemObject);
        }
        else if(cpuTimer1IntCount == INT_COUNT3)
        {
            SemaphoreP_post(&cpuTimer1BinarySemObject);
        }
        else if(cpuTimer1IntCount == INT_COUNT4)
        {
            SemaphoreP_post(&cpuTimer1BinarySemObject);
        }
    }
}



//
// End of File
//
