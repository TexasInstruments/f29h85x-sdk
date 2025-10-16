//#############################################################################
//
//   FILE:  SemaphoreP_count.c
//
//   TITLE: SemaphoreP Examples
//
//
//! \addtogroup dpl_example_list
//! <h1> SemaphoreP Count Example </h1>
//!
//! This example configures CPU Timer0, 1, and 2
//! through the DPL Hardware Interrupt API. A peripheral-specific
//! count is posted through SemaphoreP each time the peripheral's ISR
//! executes.
//!
//! The interrupt priorities are configured such that CPU Timer 0 is
//! RTINT and Timer 1 and 2 are INT.
//!
//! Sysconfig is used to configure the device and CPU timers. The
//! interrupts are configured using the DPL HwiP API.
//! SemaphoreP is used to count the interrupts. Note cpuTimer0IntCount,
//! cpuTimer0IntCount, and cpuTimer0IntCount are not controlled by the
//! semaphore and will continue to increment passed the semaphore
//! max count.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - cpuTimer0CountSem
//! - cpuTimer1CountSem
//! - cpuTimer2CountSem
//!
//
//
//#############################################################################
//  //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

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
// Prototypes for the interrupt ISR functions for RTINT
//
__attribute__((interrupt("RTINT"))) void cpuTimer0ISR(void);

//
// Prototypes for the interrupt callback functions for INT
//
void cpuTimer1Callback(void);
void cpuTimer2Callback(void);

//
// Globals
//
volatile uint32_t cpuTimer0IntCount;
volatile uint32_t cpuTimer1IntCount;
volatile uint32_t cpuTimer2IntCount;

HwiP_Object cpuTimer0HwiObject;
HwiP_Object cpuTimer1HwiObject;
HwiP_Object cpuTimer2HwiObject;

SemaphoreP_Object cpuTimer0CountSemObject;
SemaphoreP_Object cpuTimer1CountSemObject;
SemaphoreP_Object cpuTimer2CountSemObject;

#define CPU_TIMER0_MIN 0UL
#define CPU_TIMER1_MIN 0UL
#define CPU_TIMER2_MIN 0UL


#define CPU_TIMER0_MAX 20UL
#define CPU_TIMER1_MAX (CPU_TIMER0_MAX * 2UL)
#define CPU_TIMER2_MAX (CPU_TIMER0_MAX * 3UL)

//
// For this example RTINT_THRESHOLD should be
// a number greater than than the priority level of
// all CPU Timer 0 but lower than CPU Timer 1 and 2
//
#define RTINT_THRESHOLD     ((uint8_t)15)
#define CPU_TIMER0_PRIORITY ((uint8_t)10)
#define CPU_TIMER1_PRIORITY ((uint8_t)20)
#define CPU_TIMER2_PRIORITY ((uint8_t)30)

//
// Defines to compare to the return value of HwiP_inISR
//
#define CPU_TIMER0_IN_ISR   HWIP_IN_ISR_RTINT
#define CPU_TIMER1_IN_ISR   HWIP_IN_ISR_INT
#define CPU_TIMER2_IN_ISR   HWIP_IN_ISR_INT

__attribute__((retain)) uint32_t status;
__attribute__((retain)) uint32_t intCount;
__attribute__((retain)) uint32_t errorFlag;
__attribute__((retain)) uint8_t inISR;
__attribute__((retain)) uint8_t cpuID;
__attribute__((retain)) SemaphoreP_Struct *cpuTimer0CountSem;
__attribute__((retain)) SemaphoreP_Struct *cpuTimer1CountSem;
__attribute__((retain)) SemaphoreP_Struct *cpuTimer2CountSem;


//
// Main
//
int main(void)
{
    DebugP_log("\r\n\r\n----------------- Starting %s test ----------------- \r\n",__FILE__);
    cpuID = CpuIdP_c29GetCpuID();
    DebugP_logInfo("Running on CPU %d. \r\n", cpuID);
    DebugP_logInfo("Checking HwiP priorities. Timer 0 is RTINT, Timer 1 & 2 are INT. \r\n");
    testCheck(RTINT_THRESHOLD, ">", CPU_TIMER0_PRIORITY, "TIMER0");
    testCheck(RTINT_THRESHOLD, "<", CPU_TIMER1_PRIORITY, "TIMER1");
    testCheck(RTINT_THRESHOLD, "<", CPU_TIMER2_PRIORITY, "TIMER2");

    DebugP_logInfo("Configure CPU Timers and device. Leave timers halted for now.\r\n");
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

    DebugP_logInfo("Create counting Semaphores for the interrupt counts:\r\n");
    status = SemaphoreP_constructCounting(&cpuTimer0CountSemObject, CPU_TIMER0_MIN, CPU_TIMER0_MAX);
    testCheck(SystemP_SUCCESS, "==", status, "TIMER0 construct");
    cpuTimer0CountSem = (SemaphoreP_Struct *)&cpuTimer0CountSemObject;

    status = SemaphoreP_constructCounting(&cpuTimer1CountSemObject, CPU_TIMER1_MIN, CPU_TIMER1_MAX);
    testCheck(SystemP_SUCCESS, "==", status, "TIMER1 construct");
    cpuTimer1CountSem = (SemaphoreP_Struct *)&cpuTimer1CountSemObject;

    status = SemaphoreP_constructCounting(&cpuTimer2CountSemObject, CPU_TIMER2_MIN, CPU_TIMER2_MAX);
    testCheck(SystemP_SUCCESS, "==", status, "TIMER2 construct");
    cpuTimer2CountSem = (SemaphoreP_Struct *)&cpuTimer2CountSemObject;

    HwiP_Params HwiParams;
    HwiP_Params_init(&HwiParams);

    //
    // setup realtime interrupts (RTINT)
    //
    DebugP_logInfo("HwiP_construct() RTINT Interrupts:\r\n");
    HwiParams.isRTINT = 1;
    HwiParams.callback = NULL;
    HwiParams.intNum = INT_TIMER0;
    HwiParams.priority = CPU_TIMER0_PRIORITY;
    HwiParams.rtintHandler = &cpuTimer0ISR;
    errorFlag = SystemP_FAILURE;
    errorFlag = HwiP_construct(&cpuTimer0HwiObject, &HwiParams);
    testCheck(errorFlag, "==", SystemP_SUCCESS, "INT_TIMER0");

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

    HwiParams.intNum = INT_TIMER2;
    HwiParams.priority = CPU_TIMER2_PRIORITY;
    HwiParams.callback = &cpuTimer2Callback;
    errorFlag = SystemP_FAILURE;
    errorFlag = HwiP_construct(&cpuTimer2HwiObject, &HwiParams);
    testCheck(errorFlag, "==", SystemP_SUCCESS, "INT_TIMER2");

    DebugP_logInfo("Set RTINT threshold and enable interrupts.\r\n");
    HwiP_setRTINTThreshold(RTINT_THRESHOLD);

    //
    // CPU timer level, PIPE level and CPU level
    //
    CPUTimer_enableInterrupt(myCPUTIMER0_BASE);
    CPUTimer_enableInterrupt(myCPUTIMER1_BASE);
    CPUTimer_enableInterrupt(myCPUTIMER2_BASE);
    DebugP_logInfo("Testing HwiP_enableInt and HwiP_post:\r\n");
    HwiP_enableInt(INT_TIMER0);
    HwiP_enableInt(INT_TIMER1);
    HwiP_enableInt(INT_TIMER2);

    //
    // cpuTimer0CountSem->count = 0
    //
    DebugP_logInfo("Call pend on TIMER0 should timeout.\r\n");
    errorFlag = SemaphoreP_pend(&cpuTimer0CountSemObject, 0U);
    testCheck(errorFlag, "==", SystemP_TIMEOUT, "pend TIMER0");
    testCheck(cpuTimer0CountSem->count, "==", 0U, "pend TIMER0 count");

    //
    // cpuTimer0CountSem->count += 1 --> 1
    //
    DebugP_logInfo("Call post on TIMER0\r\n");
    SemaphoreP_post(&cpuTimer0CountSemObject);
    testCheck(cpuTimer0CountSem->count, "==", 1U, "post TIMER0 count");

    //
    // cpuTimer0CountSem->count += 1 --> 2
    // cpuTimer1CountSem->count += 1 --> 1
    // cpuTimer2CountSem->count += 1 --> 1
    //
    HwiP_post(INT_TIMER0);
    HwiP_post(INT_TIMER1);
    HwiP_post(INT_TIMER2);
    while(cpuTimer2CountSem->count == 0U) { }

    //
    // cpuTimer1CountSem->count -= 1 --> 0
    //
    DebugP_logInfo("Call pend on TIMER1.. should not timeout, will decrement count\r\n");
    errorFlag = SemaphoreP_pend(&cpuTimer1CountSemObject, 0U);
    testCheck(errorFlag, "==", SystemP_SUCCESS, "INT_TIMER1");

    //
    // cpuTimer2CountSem->count += 1 --> 2
    //
    HwiP_post(INT_TIMER2);
    while(cpuTimer2CountSem->count == 1U) { }

    //
    // cpuTimer2CountSem->count += 1 --> 3
    //
    HwiP_post(INT_TIMER2);
    while(cpuTimer2CountSem->count == 2U) { }

    testCheck(cpuTimer0CountSem->count, "==", 2U, "Force TIMER0");
    testCheck(cpuTimer1CountSem->count, "==", 0U, "Force TIMER1");
    testCheck(cpuTimer2CountSem->count, "==", 3U, "Force TIMER2");

    //
    // cpuTimer1CountSem->count -= 1 --> 1
    //
    DebugP_logInfo("Call pend on TIMER1.. should timeout\r\n");
    errorFlag = SemaphoreP_pend(&cpuTimer1CountSemObject, 0U);
    testCheck(errorFlag, "==", SystemP_TIMEOUT, "INT_TIMER1");
    testCheck(cpuTimer1CountSem->count, "==", 0U, "pend TIMER1");


    DebugP_logInfo("Starting the timers to test SemaphoreP_post. \r\n");
    DebugP_logInfo("Waiting....\r\n");
    //
    // Start the timers and wait until cpuTimer2IntCount is at its
    // expected max value
    //
    // As configured once cpuTimer2IntCount is at its maximum,
    // the other two counts should also be at their maximum
    //
    CPUTimer_startTimer(myCPUTIMER0_BASE);
    CPUTimer_startTimer(myCPUTIMER1_BASE);
    CPUTimer_startTimer(myCPUTIMER2_BASE);

    while(cpuTimer2CountSem->count < cpuTimer2CountSem->maxCount) { }
    testCheck(cpuTimer0CountSem->count, "==", cpuTimer0CountSem->maxCount, "TIMER0");
    testCheck(cpuTimer1CountSem->count, "==", cpuTimer1CountSem->maxCount, "TIMER1");
    testCheck(cpuTimer2CountSem->count, "==", cpuTimer2CountSem->maxCount, "TIMER2");

    DebugP_log("\r\n\r\n-----------------       All done!        ----------------- \r\n");
    __asm("  EMUSTOP0");
}

//
//
//

void cpuTimer0ISR(void)
{
    uint8_t temp;
    temp = HwiP_inISR();
    if(temp == CPU_TIMER0_IN_ISR)
    {
        SemaphoreP_post(&cpuTimer0CountSemObject);
        cpuTimer0IntCount++;
    }
}

void cpuTimer1Callback(void)
{
    uint8_t temp;
    temp = HwiP_inISR();
    if(temp == CPU_TIMER1_IN_ISR)
    {
        SemaphoreP_post(&cpuTimer1CountSemObject);
        cpuTimer1IntCount++;
    }
}

void cpuTimer2Callback(void)
{
    uint8_t temp;
    temp = HwiP_inISR();
    if(temp == CPU_TIMER2_IN_ISR)
    {
        SemaphoreP_post(&cpuTimer2CountSemObject);
        cpuTimer2IntCount++;
    }
}


//
// End of File
//
