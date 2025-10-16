//#############################################################################
//
// FILE:   binary_lut_search_example.c
//
// TITLE:  
//
//
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <math.h>

#include "device.h"
#include <binary_lut_search_example.h>
#include <binary_lut_search.h>

//*****************************************************************************
//  defines
//*****************************************************************************

  

//*****************************************************************************
//  globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass[2],fail[2];

// profiling variables
uint32_t differenceCounter=0;
uint32_t startCounter=0;
uint32_t endCounter=0;
uint32_t overheadCounter=0;

extern int32_t search_val_closest;
extern int32_t search_val_exact;

extern int32_t lut_input[LUT_SIZE];

extern uint32_t left_closest_golden;
extern uint32_t right_closest_golden;

extern int32_t index_exact_golden;

//*****************************************************************************
//  function definitions
//*****************************************************************************
int32_t main(void)
{
    // Locals
    uint32_t Left;
    uint32_t Right;
    int32_t index_exact;

    // reduce rounding error by rounding to nearest even instead of rounding towards 0
    ROUND_TO_NEAREST_EVEN;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    // Timer configuration for profiling (Period set to 10s)
    CPUTimer_setPeriod(CPUTIMER0_BASE, 200 * 10000000);
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    
    CPUTimer_startTimer(CPUTIMER0_BASE);
    __builtin_instrumentation_label("Timer_read_start");
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    __builtin_instrumentation_label("Timer_read_stop");
    overheadCounter = startCounter - endCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);


    CPUTimer_startTimer(CPUTIMER0_BASE);
    __builtin_instrumentation_label("bin_lut_search_closest_start");
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    binary_lut_search_closest_match(search_val_closest, LUT_SIZE, lut_input, &Left, &Right);

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    __builtin_instrumentation_label("bin_lut_search_closest_stop");

    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    pass[0]=0;
    fail[0]=0;
    if((Left==left_closest_golden)&&(Right==right_closest_golden))
    {
        pass[0]++;
    }
    else
    {
        fail[0]++;
    }
    printf("binary_lut_search closest match Pass_count = %d, Fail_count = %d \n", pass[0], fail[0]);
    printf("binary_lut_search closest match Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);

    CPUTimer_startTimer(CPUTIMER0_BASE);
    __builtin_instrumentation_label("bin_lut_search_exact_start");
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    index_exact = binary_lut_search_exact_match(search_val_exact, LUT_SIZE, lut_input);

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    __builtin_instrumentation_label("bin_lut_search_exact_stop");

    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    pass[1]=0;
    fail[1]=0;
    if(index_exact==index_exact_golden)
    {
        pass[1]++;
    }
    else
    {
        fail[1]++;
    }

    printf("binary_lut_search exact match Pass_count = %d, Fail_count = %d \n", pass[1], fail[1]);
    printf("binary_lut_search exact match Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);
    while(1)
    {}
    
}

// End of File
