//#############################################################################
//
//   FILE:  HwiP_int_main.c
//
//   TITLE: HwiP Examples
//
//
//! \addtogroup dpl_example_list
//! <h1> HwiP INT Example </h1>
//!
//! This example configures CPU Timer0, 1, and 2
//! through the DPL Hardware Interrupt API. A peripheral-specific
//! count is incremented each time the peripheral's ISR executes.
//!
//! The interrupt priorities are configured such that all
//! 3 interrupts are INT
//!
//! Sysconfig is used to configure the device and CPU timers. The
//! interrupts are configured using the DPL HwiP API.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - cpuTimer0IntCount - will count up to CPU_TIMER0_MAX
//! - cpuTimer1IntCount - will count up to CPU_TIMER1_MAX
//! - cpuTimer2IntCount - will count up to CPU_TIMER2_MAX
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
// This needs to be defined before #include dpl_test.h
//
#define QUIET 0

//
// Included Files
//
#include "board.h"
#include "ti_dpl_config.h"
#include "dpl_test.h"

//
// Prototypes for the interrupt callback functions
//
void cpuTimer0Callback(void);
void cpuTimer1Callback(void);
void cpuTimer2Callback(void);

//
// Globals modified in the ISRs
//
volatile uint32_t cpuTimer0IntCount;
volatile uint32_t cpuTimer1IntCount;
volatile uint32_t cpuTimer2IntCount;
volatile uint32_t errorFlag;
volatile uint8_t cpuTimer0Priority;
volatile uint8_t cpuTimer1Priority;
volatile uint8_t cpuTimer2Priority;

#define CPU_TIMER0_MAX 20UL
#define CPU_TIMER1_MAX (CPU_TIMER0_MAX * 2UL)
#define CPU_TIMER2_MAX (CPU_TIMER0_MAX * 3UL)

//
// For this example RTINT_THRESHOLD should be
// a number less than than the priority level of
// all 3 CPU timers
//
#define RTINT_THRESHOLD     ((uint8_t)5)
#define CPU_TIMER0_PRIORITY ((uint8_t)10)
#define CPU_TIMER1_PRIORITY ((uint8_t)20)
#define CPU_TIMER2_PRIORITY ((uint8_t)30)

//
// Defines to compare to the return value of HwiP_inISR
//
#define CPU_TIMER0_IN_ISR   HWIP_IN_ISR_INT
#define CPU_TIMER1_IN_ISR   HWIP_IN_ISR_INT
#define CPU_TIMER2_IN_ISR   HWIP_IN_ISR_INT

//
// Main
//
int main(void)
{
    HwiP_Object cpuTimer0HwiObject;
    HwiP_Object cpuTimer1HwiObject;
    HwiP_Object cpuTimer2HwiObject;

    uint32_t intStatus;
    uint32_t intCount;
    uint8_t inISR;
    uint8_t cpuID;

    DebugP_log("\r\n\r\n----------------- Starting %s test ----------------- \r\n",__FILE__);
    cpuID = CpuIdP_c29GetCpuID();
    DebugP_logInfo("Running on CPU %d. \r\n", cpuID);
    DebugP_logInfo("Checking HwiP priorities. All 3 interrupts should be INT. \r\n");
    testCheck(RTINT_THRESHOLD, "<", CPU_TIMER0_PRIORITY, "TIMER0");
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

    HwiP_Params HwiParams;
    HwiP_Params_init(&HwiParams);

    //
    // setup normal interrupts (INT)
    // rtintHandler is NULL since the generic HwiP INT handler will be used.
    //
    HwiParams.isRTINT = 0;
    HwiParams.rtintHandler = NULL;

    DebugP_logInfo("HwiP_construct() INT Interrupts:\r\n");

    HwiParams.intNum = INT_TIMER0;
    HwiParams.priority = CPU_TIMER0_PRIORITY;
    HwiParams.callback = &cpuTimer0Callback;
    errorFlag = SystemP_FAILURE;
    errorFlag = HwiP_construct(&cpuTimer0HwiObject, &HwiParams);
    testCheck(errorFlag, "==", SystemP_SUCCESS, "INT_TIMER0");

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

    HwiP_post(INT_TIMER0);
    HwiP_post(INT_TIMER1);
    HwiP_post(INT_TIMER2);
    while(cpuTimer2IntCount == 0U) { }

    HwiP_post(INT_TIMER1);
    HwiP_post(INT_TIMER2);
    while(cpuTimer2IntCount == 1U) { }

    HwiP_post(INT_TIMER2);
    while(cpuTimer2IntCount == 2U) { }
    testCheck(cpuTimer0IntCount, "==", 1U, "Force TIMER0");
    testCheck(cpuTimer1IntCount, "==", 2U, "Force TIMER1");
    testCheck(cpuTimer2IntCount, "==", 3U, "Force TIMER2");

    errorFlag = SystemP_SUCCESS;
    //
    // This should return a failure since the code is not in
    // an INT service routine
    //
    if(HwiP_getIntPriority((uint8_t*)&cpuTimer2Priority)                  \
            == SystemP_FAILURE)
    {
        errorFlag = SystemP_FAILURE;
    }
    testCheck(errorFlag, "==", SystemP_FAILURE, "errorFlag"  );

    DebugP_logInfo("Starting the timers to test HwiP_disableInt and HwiP_inISR. \r\n");
    DebugP_logInfo("Testing disableInt(): When max count is reached, the ISR will disable the interrupt for the timer.\r\n");
    DebugP_logInfo("Waiting....\r\n");
    //
    // Start the timers and wait until cpuTimer2IntCount is at its
    // expected max value
    //
    // As configured once cpuTimer2IntCount is at its maximum,
    // the other two counts should also be at their maximum
    //
    errorFlag = SystemP_SUCCESS;
    CPUTimer_startTimer(myCPUTIMER0_BASE);
    CPUTimer_startTimer(myCPUTIMER1_BASE);
    CPUTimer_startTimer(myCPUTIMER2_BASE);
    while(cpuTimer2IntCount < CPU_TIMER2_MAX){}
    DebugP_logInfo("Checking the CPU timers' interrupt count, error flag and logged priority:\r\n");
    testCheck(cpuTimer0IntCount, "==", CPU_TIMER0_MAX, "TIMER0");
    testCheck(cpuTimer1IntCount, "==", CPU_TIMER1_MAX, "TIMER1");
    testCheck(cpuTimer2IntCount, "==", CPU_TIMER2_MAX, "TIMER2");
    testCheck(errorFlag, "==", SystemP_SUCCESS, "errorFlag"  );
    testCheck(cpuTimer0Priority, "==", CPU_TIMER0_PRIORITY, "TIMER0 Priority");
    testCheck(cpuTimer1Priority, "==", CPU_TIMER1_PRIORITY, "TIMER1 Priority");
    testCheck(cpuTimer2Priority, "==", CPU_TIMER2_PRIORITY, "TIMER2 Priority");

    cpuTimer2IntCount = 0;
    DebugP_logInfo("Testing HwiP_disableInt and HwiP_restoreInt():\r\n");
    //
    // CPU TIMER2 interrupt is currently disabled
    // Check return value from disableInt
    //
    intStatus = HwiP_disableInt(INT_TIMER2);
    testCheck(intStatus, "==", 0U, "oldStatus disabled");

    //
    // Test restoreInt - force "old status" to be enabled
    //
    HwiP_restoreInt(INT_TIMER2, 1U);

    //
    // Keep this value very low (much lower than CPU_TIMER2_MAX)
    //
    while(cpuTimer2IntCount < 2U) { }
    intStatus = HwiP_disableInt(INT_TIMER2);
    testCheck(intStatus, "==", 1U, "oldStatus enabled");

    HwiP_restoreInt(INT_TIMER2, intStatus);
    while(cpuTimer2IntCount < intCount + 10U) { }
    intStatus = HwiP_disableInt(INT_TIMER2);
    testCheck(intStatus, "==", 1U, "oldStatus enabled");

    intStatus = HwiP_disableInt(INT_TIMER2);
    testCheck(intStatus, "==", 0U, "oldStatus disabled");

    DebugP_log("\r\n\r\n-----------------       All done!        ----------------- \r\n");
    __asm("  EMUSTOP0");
}

//
//
//

void cpuTimer0Callback(void)
{
    if(HwiP_inISR() == CPU_TIMER0_IN_ISR)
    {
        cpuTimer0IntCount++;
    }
    if(cpuTimer0IntCount == CPU_TIMER0_MAX)
    {
        if(HwiP_getIntPriority((uint8_t*)&cpuTimer0Priority)                  \
                == SystemP_FAILURE)
        {
            errorFlag = SystemP_FAILURE;
        }
        HwiP_disableInt(INT_TIMER0);
    }
}

void cpuTimer1Callback(void)
{
    if(HwiP_inISR() == CPU_TIMER1_IN_ISR)
    {
        cpuTimer1IntCount++;
    }
    if(cpuTimer1IntCount == CPU_TIMER1_MAX)
    {
        if(HwiP_getIntPriority((uint8_t*)&cpuTimer1Priority)                  \
                == SystemP_FAILURE)
        {
            errorFlag = SystemP_FAILURE;
        }
        HwiP_disableInt(INT_TIMER1);
    }
}

void cpuTimer2Callback(void)
{
    if(HwiP_inISR() == CPU_TIMER2_IN_ISR)
    {
        cpuTimer2IntCount++;
    }
    if(cpuTimer2IntCount == CPU_TIMER2_MAX)
    {
        if(HwiP_getIntPriority((uint8_t*)&cpuTimer2Priority)                  \
                == SystemP_FAILURE)
        {
            errorFlag = SystemP_FAILURE;
        }
        HwiP_disableInt(INT_TIMER2);
    }
}


//
// End of File
//
