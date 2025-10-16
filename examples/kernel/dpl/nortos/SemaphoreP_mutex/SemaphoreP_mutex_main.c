//#############################################################################
//
//   FILE:  SemaphoreP_mutex.c
//
//   TITLE: SemaphoreP Examples
//
//
//! \addtogroup dpl_example_list
//! <h1> SemaphoreP Mutex Example </h1>
//!
//!
//!
//!
//!
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
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
// Prototypes for the interrupt callback functions for INT
//
void cpuTimer1Callback(void);

//
// Globals
//
volatile uint32_t cpuTimer1IntCount;
HwiP_Object cpuTimer1HwiObject;
SemaphoreP_Object cpuTimer1MutexSemObject;

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
__attribute__((retain)) SemaphoreP_Struct *cpuTimer1MutexSem;

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

    DebugP_logInfo("Create mutex Semaphore:\r\n");
    status = SemaphoreP_constructMutex(&cpuTimer1MutexSemObject);
    testCheck(SystemP_SUCCESS, "==", status, "Mutex");
    cpuTimer1MutexSem = (SemaphoreP_Struct *)&cpuTimer1MutexSemObject;

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

    #define PEND_NUM 4U
    uint32_t i;
    DebugP_logInfo("Pend %d times. Check nestCount. \r\n", PEND_NUM);
    for(i = 1; i <= PEND_NUM; i++ )
    {
        status = SemaphoreP_pend(&cpuTimer1MutexSemObject, SystemP_WAIT_FOREVER);
        testCheck(status, "==", SystemP_SUCCESS, "pend");
    }

    testCheck(cpuTimer1MutexSem->nestCount, "==", PEND_NUM, "nestCount0");
    testCheck(cpuTimer1MutexSem->count, "==", 0U, "count0");

    DebugP_logInfo("Enable interrupt. ISR will post at INT_COUNT1, INT_COUNT2, INT_COUNT3 and INT_COUNT4 \r\n");
    CPUTimer_startTimer(myCPUTIMER1_BASE);

    while(cpuTimer1MutexSem->nestCount == PEND_NUM){}
    testCheck(cpuTimer1IntCount, "==", INT_COUNT1, "INT_COUNT1");

    while(cpuTimer1MutexSem->nestCount == PEND_NUM-1U){}
    testCheck(cpuTimer1IntCount, "==", INT_COUNT2, "INT_COUNT2");

    while(cpuTimer1MutexSem->nestCount == PEND_NUM-2U){}
    testCheck(cpuTimer1IntCount, "==", INT_COUNT3, "INT_COUNT3");

    while(cpuTimer1MutexSem->nestCount == PEND_NUM-3U){}
    testCheck(cpuTimer1IntCount, "==", INT_COUNT4, "INT_COUNT4");

    testCheck(cpuTimer1MutexSem->nestCount, "==", 0U, "nestCount0");
    testCheck(cpuTimer1MutexSem->count, "==", 1U, "count1");

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
            SemaphoreP_post(&cpuTimer1MutexSemObject);
        }
        else if(cpuTimer1IntCount == INT_COUNT2)
        {
            SemaphoreP_post(&cpuTimer1MutexSemObject);
        }
        else if(cpuTimer1IntCount == INT_COUNT3)
        {
            SemaphoreP_post(&cpuTimer1MutexSemObject);
        }
        else if(cpuTimer1IntCount == INT_COUNT4)
        {
            SemaphoreP_post(&cpuTimer1MutexSemObject);
        }
    }
}



//
// End of File
//
