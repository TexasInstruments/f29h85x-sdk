//#############################################################################
//
// FILE:   sinf_example.c
//
// TITLE:  
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
#include <sinf_example.h>

//*****************************************************************************
// defines
//*****************************************************************************
 
//*****************************************************************************
// globals
//*****************************************************************************
// The global pass, fail values
int16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float32_t tolerance = 1.0e-5;

// profiling variables
uint32_t differenceCounter=0;
uint32_t startCounter=0;
uint32_t endCounter=0;
uint32_t overheadCounter=0;

// test input, output, golden (expected output)
extern volatile float32_t test_input;
extern const float32_t test_golden;

__attribute__((location(0x200E0000))) float32_t test_output;

//*****************************************************************************
// function definitions
//*****************************************************************************
int32_t main(void)
{
    // Locals
    float32_t temp;
    temp = test_input;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    // Timer configuration for profiling (Period set to 10s)
    CPUTimer_setPeriod(CPUTIMER0_BASE, 200 * 10000000);
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    overheadCounter = startCounter - endCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    test_output = sinf(temp);

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    #ifdef FASTMATH

        printf("sinf() computed with -ffast-math compiler option, resulting in TMU instruction...\n");
        printf("%.7f, %.7f,Error = %.7f\n",test_output,test_golden,(test_output-test_golden));
        if(fabsf(test_output-test_golden)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #else
        printf("sinf() computed without -ffast-math compiler options, resulting in RTS library call...\n");
        printf("%.7f, %.7f,Error = %.7f\n",test_output,test_golden,(test_output-test_golden));
        if(fabsf(test_output-test_golden)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #endif

    printf("Completed sinf test Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("sinf Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);
}

// End of File
