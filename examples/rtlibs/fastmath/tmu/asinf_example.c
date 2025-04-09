//#############################################################################
//
// FILE:   asinf_example.c
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
#include <asinf_example.h>

//*****************************************************************************
// defines
//*****************************************************************************
#define TWOPI 6.28318531f
 
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

extern const float32_t test_golden_asinf;

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


    // asinf
    #ifdef FASTMATH
        CPUTimer_startTimer(CPUTIMER0_BASE);
        startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);        
        // test_output is in per-unit, need to multiply by TWOPI to get radians
        test_output = asinf_opt(test_input);

        endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
        differenceCounter = startCounter - endCounter - overheadCounter;
        CPUTimer_stopTimer(CPUTIMER0_BASE);

        printf("asinf() computed with builtin/intrinsic TMU instructions...\n");
        printf("%.7f, %.7f,Error = %.7f\n",(test_output*TWOPI),test_golden_asinf,((test_output*TWOPI)-test_golden_asinf));
        if(fabsf((test_output*TWOPI)-test_golden_asinf)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #else
        CPUTimer_startTimer(CPUTIMER0_BASE);
        startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

        test_output = asinf(test_input);
        
        endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
        differenceCounter = startCounter - endCounter - overheadCounter;
        CPUTimer_stopTimer(CPUTIMER0_BASE);

        printf("asinf() computed with RTS library call...\n");
        printf("%.7f, %.7f,Error = %.7f\n",test_output,test_golden_asinf,(test_output-test_golden_asinf));
        if(fabsf(test_output-test_golden_asinf)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #endif

    printf("Completed atanf, asinf test Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("asinf Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);
}

// End of File
