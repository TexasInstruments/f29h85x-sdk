//#############################################################################
//
//   FILE:  TimerP_main.c
//
//   TITLE: TimerP Examples
//
//
//! \addtogroup dpl_example_list
//! <h1> TimerP Example </h1>
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

#define CPU_TIMER0_MAX          (20UL)
#define CPU_TIMER1_MAX          (CPU_TIMER0_MAX * 2UL)
#define CPU_TIMER2_MAX          (CPU_TIMER0_MAX * 3UL)

//
// For this example RTINT_THRESHOLD should be
// a number less than than the priority level of
// all 3 CPU timers
//
#define RTINT_THRESHOLD         ((uint8_t)5)
#define CPU_TIMER0_PRIORITY     ((uint8_t)10)
#define CPU_TIMER1_PRIORITY     ((uint8_t)20)
#define CPU_TIMER2_PRIORITY     ((uint8_t)30)

//
// Defines to compare to the return value of HwiP_inISR
//
#define CPU_TIMER0_IN_ISR       (HWIP_IN_ISR_INT)
#define CPU_TIMER1_IN_ISR       (HWIP_IN_ISR_INT)
#define CPU_TIMER2_IN_ISR       (HWIP_IN_ISR_INT)

//
// Main
//
int main(void)
{
    HwiP_Object     cpuTimer0HwiObject;
    HwiP_Object     cpuTimer1HwiObject;
    HwiP_Object     cpuTimer2HwiObject;
    TimerP_Params   timer0Object;
    TimerP_Params   timer1Object;
    TimerP_Params   timer2Object;
    uint32_t        intStatus;
    uint32_t        intCount;
    uint8_t         inISR;
    uint8_t         cpuID;
    uint32_t        timer0Cnt;
    uint32_t        timer1Cnt;
    uint32_t        timer2Cnt;
    uint32_t        timer0DbgCnt;
    uint32_t        timer1DbgCnt;
    uint32_t        timer2DbgCnt;

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

    HwiP_enable();
    __builtin_c29_enable_INT();

    DebugP_log("\r\n\r\n----------------- Starting %s test ----------------- \r\n",__FILE__);
    cpuID = CpuIdP_c29GetCpuID();
    DebugP_logInfo("Running on CPU %d. \r\n", cpuID);

    //
    //  TimerP init
    //
    DebugP_logInfo("\r\n");
    DebugP_logInfo("TimerP_Params_init():Initializing Timer params\r\n");

    TimerP_Params_init(&timer0Object);
    TimerP_Params_init(&timer1Object);
    TimerP_Params_init(&timer2Object);

    //
    //  TimerP setup
    //
    DebugP_logInfo("\r\n");
    DebugP_logInfo("TimerP_setup():Configuring timers with timeout 1000,2000 and 4000 usec\r\n");

    timer0Object.periodInUsec   = 1000U;
    TimerP_setup(CPUTIMER0_BASE, &timer0Object);

    timer1Object.periodInUsec   = 2000;
    timer1Object.inputPreScaler = 2U;
    TimerP_setup(CPUTIMER1_BASE, &timer1Object);

    timer2Object.periodInUsec   = 4000;
    timer2Object.inputPreScaler = 4U;
    TimerP_setup(CPUTIMER2_BASE, &timer2Object);

    DebugP_logInfo("Check HwiP_inISR while in main:\r\n");
    inISR = HwiP_inISR();
    testCheck(inISR, "==", HWIP_IN_ISR_MAIN, "IN_ISR");

    HwiP_Params HwiParams;
    HwiP_Params_init(&HwiParams);

    //
    // setup normal interrupts (INT)
    // rtintHandler is NULL since the generic HwiP INT handler will be used.
    //
    DebugP_logInfo("\r\n");
    DebugP_logInfo("Configuring Timer interrupts...\r\n");

    HwiParams.isRTINT = 0;
    HwiParams.rtintHandler = NULL;

    HwiParams.intNum    = INT_TIMER0;
    HwiParams.priority  = CPU_TIMER0_PRIORITY;
    HwiParams.callback  = &cpuTimer0Callback;
    errorFlag = SystemP_FAILURE;
    errorFlag = HwiP_construct(&cpuTimer0HwiObject, &HwiParams);
    testCheck(errorFlag, "==", SystemP_SUCCESS, "INT_TIMER0");

    HwiParams.intNum    = INT_TIMER1;
    HwiParams.priority  = CPU_TIMER1_PRIORITY;
    HwiParams.callback  = &cpuTimer1Callback;
    errorFlag = SystemP_FAILURE;
    errorFlag = HwiP_construct(&cpuTimer1HwiObject, &HwiParams);
    testCheck(errorFlag, "==", SystemP_SUCCESS, "INT_TIMER1");

    HwiParams.intNum    = INT_TIMER2;
    HwiParams.priority  = CPU_TIMER2_PRIORITY;
    HwiParams.callback  = &cpuTimer2Callback;
    errorFlag = SystemP_FAILURE;
    errorFlag = HwiP_construct(&cpuTimer2HwiObject, &HwiParams);
    testCheck(errorFlag, "==", SystemP_SUCCESS, "INT_TIMER2");

    //
    //  RTINT threshold
    //
    DebugP_logInfo("\r\n");
    DebugP_logInfo("Set RTINT threshold and enable interrupts.\r\n");

    HwiP_setRTINTThreshold(RTINT_THRESHOLD);

    //
    // CPU timer level, PIPE level and CPU level
    //
    HwiP_enableInt(INT_TIMER0);
    HwiP_enableInt(INT_TIMER1);
    HwiP_enableInt(INT_TIMER2);

    //
    // Start the timers and wait until cpuTimer2IntCount is at its
    // expected max value
    //
    // As configured once cpuTimer2IntCount is at its maximum,
    // the other two counts should also be at their maximum
    //
    errorFlag = SystemP_SUCCESS;

    //
    //  TimerP start
    //
    DebugP_logInfo("\r\n");
    DebugP_logInfo("TimerP_start():Starting the timers\r\n");

    TimerP_start(CPUTIMER0_BASE);
    TimerP_start(CPUTIMER1_BASE);
    TimerP_start(CPUTIMER2_BASE);

    timer0DbgCnt = TimerP_getReloadCount(CPUTIMER0_BASE)/2U;
    timer1DbgCnt = TimerP_getReloadCount(CPUTIMER1_BASE)/2U;
    timer2DbgCnt = TimerP_getReloadCount(CPUTIMER2_BASE)/2U;

    DebugP_logInfo("\r\n");
    DebugP_logInfo("Waiting for timers to stop ...\r\n");

    while(cpuTimer2IntCount < CPU_TIMER2_MAX)
    {
        //
        //  Get timet current count
        //
        timer0Cnt = TimerP_getCount(CPUTIMER0_BASE);
        timer1Cnt = TimerP_getCount(CPUTIMER1_BASE);
        timer2Cnt = TimerP_getCount(CPUTIMER2_BASE);

        if(timer0Cnt >= timer0DbgCnt)
        {
            DebugP_logInfo("Timer0:Count = %u, Reload Count = %u\r\n", timer0Cnt, TimerP_getReloadCount(CPUTIMER0_BASE));
            timer0DbgCnt = 0xFFFFFFFFU;
        }
        if(timer1Cnt >= timer1DbgCnt)
        {
            DebugP_logInfo("Timer1:Count = %u, Reload Count = %u\r\n", timer1Cnt, TimerP_getReloadCount(CPUTIMER1_BASE));
            timer1DbgCnt = 0xFFFFFFFFU;
        }
        if(timer2Cnt >= timer2DbgCnt)
        {
            DebugP_logInfo("Timer2:Count = %u, Reload Count = %u\r\n", timer2Cnt, TimerP_getReloadCount(CPUTIMER2_BASE));
            timer2DbgCnt = 0xFFFFFFFFU;
        }
    }

    //
    //  Check timer interrupt count
    //
    DebugP_logInfo("\r\n");
    DebugP_logInfo("Checking the CPU timers' interrupt count:\r\n");

    DebugP_logInfo("\r\n");
    DebugP_logInfo("cpuTimer0IntCount = %d\r\n", cpuTimer0IntCount);
    DebugP_logInfo("cpuTimer1IntCount = %d\r\n", cpuTimer1IntCount);
    DebugP_logInfo("cpuTimer2IntCount = %d\r\n", cpuTimer2IntCount);

    DebugP_log("\r\n\r\n-----------------       All done!        ----------------- \r\n");
    __asm("  EMUSTOP0");
}

//
//  Timer callback functions
//

void cpuTimer0Callback(void)
{
    if(HwiP_inISR() == CPU_TIMER0_IN_ISR)
    {
        cpuTimer0IntCount++;
    }
    if(cpuTimer0IntCount == CPU_TIMER0_MAX)
    {
        TimerP_stop(CPUTIMER0_BASE);
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
        TimerP_stop(CPUTIMER1_BASE);
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
        TimerP_stop(CPUTIMER2_BASE);
    }
}


//
// End of File
//
