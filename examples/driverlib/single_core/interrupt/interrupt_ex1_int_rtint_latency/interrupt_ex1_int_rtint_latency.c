//#############################################################################
//
// FILE:   interrupt_ex1_int_rtint_latency.c
//
// TITLE:  RTINT vs INT Latency example
//
//! \addtogroup driver_example_list
//! <h1> RTINT vs INT Latency example </h1>
//!
//! This example demonstrates the interrupt latencies of INT and RTINT.
//! This configures 2 CPU timer interrupts with following priorities.
//!   - RTINT Threshold = 15
//!   - Timer 0 Interrupt priority = 10 -> RTINT
//!   - Timer 1 Interrupt priority = 20 -> INT
//!
//! User can set the macro ENABLE_FUNCTION_CALL_IN_ISR to 1 to configure both
//! the ISRs to invoke a function call, hence multiple core registers needs to
//! be saved and restored. If the macro is set to 0, both ISRs just updates a
//! counter variable, hence requires only 1 register to be saved and restored.
//! In case of RTINT, register saves and restores are done by the hardware.
//! In case of INT, register saves and restores are done by the software.
//!
//! The ERAD module is configured to measure the cycles taken between the timer
//! interrupt event to the first instruction in the ISR.
//!
//! Note : Run the example for some duration to get the min and max values. The
//! watch variables are arrays with min and max values [Min, Max]
//!
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - timer0_intEvent_to_isr : Min and Max cycles count between the timer event
//!                            to the ISR entry
//! - timer0_isr_to_data     : Min and Max cycle count between the ISR entry to
//!                            the first C instruction (data access to
//!                            cpuTimer0IntCount variable)
//! - timer1_intEvent_to_isr : Min and Max cycles count between the timer event
//!                            to the ISR entry
//! - timer1_isr_to_data     : Min and Max cycle count between the ISR entry to
//!                            the first C instruction (data access to
//!                            cpuTimer1IntCount variable)
//!
//! \b Expected \b results : (With opt level = 1)
//!-------------------------------------------------------------------
//!                  |   RTINT   |   RTINT   |    INT    |    INT    |
//!                  |  w/o func | with func |  w/o func | with func |
//!-------------------------------------------------------------------
//!  intEvent_to_isr |   23-29   |   23-29   |   21-27   |   21-27   |
//!  isr_to_data     |     1     |     1     |     2     |   25-26   |
//!-------------------------------------------------------------------
//!
//
//#############################################################################
// //
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

//###########################################################################

//
// Included Files
//
#include "board.h"
#include "driverlib.h"

//
// Set this to 1 to profile the ISRs with function calls within it.
// Set this to 0 to profile the ISRs with just data access, and no function calls
#define ENABLE_FUNCTION_CALL_IN_ISR     0

//
// Globals
//
volatile uint16_t cpuTimer0IntCount = 0;
volatile uint16_t cpuTimer1IntCount = 0;

volatile uint32_t timer0_intEvent_to_isr[2];
volatile uint32_t timer1_intEvent_to_isr[2];
volatile uint32_t timer0_isr_to_data[2];
volatile uint32_t timer1_isr_to_data[2];

void configureERAD();

//
// Main
//
int main(void)
{
    Device_init();
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_CPUTIMER);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_CPUX_ERAD);

    Board_init();
    configureERAD();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Add some delay between the timer start, to avoid nesting
    //
    CPUTimer_startTimer(myCPUTIMER0_BASE);
    SysCtl_delay(20);
    CPUTimer_startTimer(myCPUTIMER1_BASE);

    //
    // Clear the max count after the first tick
    //
    while(cpuTimer1IntCount < 1U);
    ERAD_setMaxCount(ERAD_COUNTER0, 0);
    ERAD_setMaxCount(ERAD_COUNTER1, 0);
    ERAD_setMaxCount(ERAD_COUNTER2, 0);
    ERAD_setMaxCount(ERAD_COUNTER3, 0);

    //
    // IDLE loop. Read the ERAD results
    //
    while(1)
    {
        timer0_intEvent_to_isr[0] = ERAD_getMinCount(ERAD_COUNTER0);
        timer0_intEvent_to_isr[1] = ERAD_getMaxCount(ERAD_COUNTER0);

        timer0_isr_to_data[0]     = ERAD_getMinCount(ERAD_COUNTER1);
        timer0_isr_to_data[1]     = ERAD_getMaxCount(ERAD_COUNTER1);

        timer1_intEvent_to_isr[0] = ERAD_getMinCount(ERAD_COUNTER2);
        timer1_intEvent_to_isr[1] = ERAD_getMaxCount(ERAD_COUNTER2);

        timer1_isr_to_data[0]     = ERAD_getMinCount(ERAD_COUNTER3);
        timer1_isr_to_data[1]     = ERAD_getMaxCount(ERAD_COUNTER3);

        SysCtl_delay(100);
    }
}

//
// ISRs for the timer interrupts
//
__attribute__((interrupt("RTINT")))
void cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;

    #if ENABLE_FUNCTION_CALL_IN_ISR==1
    SysCtl_delay(1);
    #endif
}

__attribute__((interrupt("INT")))
void cpuTimer1ISR(void)
{
    cpuTimer1IntCount++;

    #if ENABLE_FUNCTION_CALL_IN_ISR==1
    SysCtl_delay(1);
    #endif
}

void configureERAD()
{
    //
    // Bus Comparator initialization
    //
    ERAD_BusComp_Config buscomp_params;
    buscomp_params.enable_stack_qual=false;
    buscomp_params.enable_spsel_match = false;
    buscomp_params.spsel = 0x0U;
    buscomp_params.mask = 0x0U;
    buscomp_params.enable_stop = false;
    buscomp_params.enable_int = false;
    buscomp_params.enable_nmi = false;
    buscomp_params.comp_mode = ERAD_BUSCOMP_COMPMODE_EQ;


    //
    // ERAD_BUSCOMP4 = cpuTimer0ISR (W aligned)
    //
    ERAD_setBusCompOwnership(ERAD_BUSCOMP4, ERAD_OWNER_APPLICATION);
    ERAD_disableBusCompModule(ERAD_BUSCOMP4);
    buscomp_params.bus_sel = ERAD_BUSCOMP_BUS_VPC_W_ALIGNED;
    buscomp_params.reference = (uint64_t)&cpuTimer0ISR;
    ERAD_configBusComp(ERAD_BUSCOMP4, &buscomp_params);

    //
    // ERAD_BUSCOMP5 = cpuTimer1ISR (W aligned)
    //
    ERAD_setBusCompOwnership(ERAD_BUSCOMP5, ERAD_OWNER_APPLICATION);
    ERAD_disableBusCompModule(ERAD_BUSCOMP5);
    buscomp_params.bus_sel = ERAD_BUSCOMP_BUS_VPC_W_ALIGNED;
	buscomp_params.reference = (uint64_t)&cpuTimer1ISR;
    ERAD_configBusComp(ERAD_BUSCOMP5, &buscomp_params);

    //
    // ERAD_BUSCOMP6 = cpuTimer0IntCount (DR, W Aligned)
    //
    ERAD_setBusCompOwnership(ERAD_BUSCOMP6, ERAD_OWNER_APPLICATION);
    ERAD_disableBusCompModule(ERAD_BUSCOMP6);
    buscomp_params.bus_sel = ERAD_BUSCOMP_BUS_DRAB_W;
	buscomp_params.reference = (uint64_t)&cpuTimer0IntCount;
    ERAD_configBusComp(ERAD_BUSCOMP6, &buscomp_params);

    //
    // ERAD_BUSCOMP7 = cpuTimer1IntCount (DR, W Aligned)
    //
    ERAD_setBusCompOwnership(ERAD_BUSCOMP7, ERAD_OWNER_APPLICATION);
    ERAD_disableBusCompModule(ERAD_BUSCOMP7);
    buscomp_params.bus_sel = ERAD_BUSCOMP_BUS_DRAB_W;
	buscomp_params.reference = (uint64_t)&cpuTimer1IntCount;
    ERAD_configBusComp(ERAD_BUSCOMP7, &buscomp_params);


    //
    // Counter initialization
    //
    ERAD_Counter_Config counter_params;
    counter_params.event = ERAD_EVENT_NO_EVENT;
    counter_params.event_mode = ERAD_COUNTER_MODE_ACTIVE;
    counter_params.reference = 0xFFFFFFFF;
    counter_params.rst_on_match = false;
    counter_params.enable_stop = false;
    counter_params.enable_int = false;
    counter_params.enable_nmi = false;


    //
    // ERAD_COUNTER0 = TINT0 - ERAD_BUSCOMP4 (cpuTimer0ISR)
    //
    ERAD_setCounterOwnership(ERAD_COUNTER0, ERAD_OWNER_APPLICATION);
    ERAD_disableCounterModule(ERAD_COUNTER0);
    ERAD_configCounterInStartStopMode(ERAD_COUNTER0, &counter_params, ERAD_EVENT_CPU1_TIMER0_INT, ERAD_EVENT_EBC4);
    ERAD_setCounterInputConditioning(ERAD_COUNTER0, ERAD_COUNTER_START_INPUT, ERAD_INPUT_INVERT_ENABLE);

    //
    // ERAD_COUNTER1 = ERAD_BUSCOMP4 (cpuTimer0ISR) - ERAD_BUSCOMP6 (cpuTimer0IntCount)
    //
    ERAD_setCounterOwnership(ERAD_COUNTER1, ERAD_OWNER_APPLICATION);
    ERAD_disableCounterModule(ERAD_COUNTER1);
    ERAD_configCounterInStartStopMode(ERAD_COUNTER1, &counter_params, ERAD_EVENT_EBC4, ERAD_EVENT_EBC6);

    //
    // ERAD_COUNTER2 = TINT1 - ERAD_BUSCOMP5 (cpuTimer1ISR)
    //
    ERAD_setCounterOwnership(ERAD_COUNTER2, ERAD_OWNER_APPLICATION);
    ERAD_disableCounterModule(ERAD_COUNTER2);
    ERAD_configCounterInStartStopMode(ERAD_COUNTER2, &counter_params, ERAD_EVENT_CPU1_TIMER1_INT, ERAD_EVENT_EBC5);
    ERAD_setCounterInputConditioning(ERAD_COUNTER2, ERAD_COUNTER_START_INPUT, ERAD_INPUT_INVERT_ENABLE);

    //
    // ERAD_COUNTER3 = ERAD_BUSCOMP5 (cpuTimer1ISR) - ERAD_BUSCOMP7 (cpuTimer1IntCount)
    //
    ERAD_setCounterOwnership(ERAD_COUNTER3, ERAD_OWNER_APPLICATION);
    ERAD_disableCounterModule(ERAD_COUNTER3);
    ERAD_configCounterInStartStopMode(ERAD_COUNTER3, &counter_params, ERAD_EVENT_EBC5, ERAD_EVENT_EBC7);

    ERAD_enableModules(ERAD_INST_BUSCOMP4 | ERAD_INST_BUSCOMP5 | ERAD_INST_BUSCOMP6 | ERAD_INST_BUSCOMP7  |
                       ERAD_INST_COUNTER0 | ERAD_INST_COUNTER1 | ERAD_INST_COUNTER2 | ERAD_INST_COUNTER3 );
}

//
// End of File
//
