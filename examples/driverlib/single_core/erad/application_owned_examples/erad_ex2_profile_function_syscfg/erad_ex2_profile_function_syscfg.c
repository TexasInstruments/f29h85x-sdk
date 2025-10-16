//#############################################################################
//
// FILE:   erad_ex2_profile_function_syscfg.c
//
// TITLE:  ERAD Profile Function.
//
//! \addtogroup driver_example_list
//! <h1>ERAD Profile Function</h1>
//!
//!  This example uses BUSCOMP7, BUSCOMP6 and COUNTER0 of the ERAD module to
//!  profile a function (delayFunction). It calculates the CPU cycles taken
//!  between the the start address of the function to the end address of the
//!  function
//!
//!  Two dummy variable are written to inside the function - startCount and
//!  endCount. BUSCOMP5, BUSCOMP4 and COUNTER1 are used to profile the time
//!  taken between the access to startCount variable till the access to
//!  endCount variable.
//!
//!  Both the counters are setup to operate in START-STOP mode and count the
//!  number of CPU cycles spend between the respective bus comparator events.
//!
//!  Note: The Enhanced Bus Comparator (EBC) modules are used in the
//!  decreasing order of their instances in this example. This is because, in
//!  FLASH configuration/ when hardware breakpoints are used while debugging,
//!  the first few ERAD EBCs are owned by the Debugger and are blocked for the
//!  application to use.
//!
//!  \b Watch \b Variables \n
//!   - cycles_Function_Max - the maximum number of cycles between the start
//!                           of function to the end of function
//!   - cycles_Function_Min - the minimum number of cycles between the start
//!                           of function to the end of function
//!   - cycles_Data_Max     - the maximum number of cycles taken between
//!                           accessing startCount variable to endCount
//!                           variable
//!   - cycles_Data_Min     - the minimum number of cycles taken between
//!                           accessing startCount variable to endCount
//!                           variable
//!
//! \b External \b Connections \n
//!  None
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

//
// Global Variables
//

//
// Start and end address of the function delayFunction.
// This value comes from the linker command file.
//
extern uint32_t delayFuncStart, delayFuncEnd;
void *addr_delayFuncStart = (void *)&delayFuncStart;
void *addr_delayFuncEnd   = (void *)((uint32_t)&delayFuncEnd - 2);

//
// The variables used in the function which are monitored by bus comparators
// 3 and 4.
//
volatile uint32_t startCount = 0;
volatile uint32_t endCount = 0;
void *addr_startCount = (void *)&startCount;
void *addr_endCount   = (void *)&endCount;

//
// Watch variables with the number of CPU cycles elapsed.
//
volatile uint32_t cycles_Function_Max = 0;
volatile uint32_t cycles_Function_Min = 0xFFFFFFFF;
volatile uint32_t cycles_Data_Max = 0;
volatile uint32_t cycles_Data_Min = 0xFFFFFFFF;

//
// Function Prototypes
//
__attribute__ ((section(".delayFunc"), noinline))
void delayFunction(uint16_t);

//
// Main
//
int main(void)
{
    int i;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Loop to call the delay function repeatedly with different delays
    //
    for(i = 0; i < 10; i++)
    {
        delayFunction(i % 5);

        //
        // View these variables in CCS view
        // Note that calling the function ERAD_getCurrentValue here will
        // return 0 since the stop events have already been occurred.
        //
        cycles_Function_Max = ERAD_getMaxCount(ERAD_COUNTER0);
        cycles_Data_Max     = ERAD_getMaxCount(ERAD_COUNTER1);

        cycles_Function_Min = ERAD_getMinCount(ERAD_COUNTER0);
        cycles_Data_Min     = ERAD_getMinCount(ERAD_COUNTER1);

        ESTOP0;

        //
        // Uncomment the code below to clear the maximum and minimum count
        //
        // ERAD_setMaxCount(ERAD_COUNTER0, 0);
        // ERAD_setMaxCount(ERAD_COUNTER1, 0);
        // ERAD_setMinCount(ERAD_COUNTER0, 0xFFFFFFFF);
        // ERAD_setMinCount(ERAD_COUNTER1, 0xFFFFFFFF);
    }

    ESTOP0;
    while(1);
}

//
// delay function
//
void delayFunction(uint16_t delay)
{
    startCount++;

    uint16_t i=0;
    for (; i<delay; i++)
    {
        NOP;
        NOP;
        NOP;
        NOP;
    }

    endCount++;
}

//
// End of File
//
