//#############################################################################
//
// FILE:   atan2f_example.c
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
#include <atan2f_example.h>

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
extern volatile float32_t x_input;
extern volatile float32_t y_input;

extern const float32_t test_golden_atan;
extern const float32_t test_golden_atan2;

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

    // atanf
    #ifdef FASTMATH                
        // test_output is in per-unit, need to multiply by TWOPI to get radians
        test_output = __builtin_c29_i32_puatanf32_m(temp);    

        printf("atanf() computed with builtin/intrinsic TMU instruction...\n");
        printf("%.7f, %.7f,Error = %.7f\n",(test_output*TWOPI),test_golden_atan,((test_output*TWOPI)-test_golden_atan));
        if(fabsf((test_output*TWOPI)-test_golden_atan)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #else

        test_output = atanf(temp);
    
        printf("atanf() computed with RTS library call...\n");
        printf("%.7f, %.7f,Error = %.7f\n",test_output,test_golden_atan,(test_output-test_golden_atan));
        if(fabsf(test_output-test_golden_atan)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #endif

    // atan2f
    #ifdef FASTMATH
        CPUTimer_startTimer(CPUTIMER0_BASE);
        startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);        
        // test_output is in per-unit, need to multiply by TWOPI to get radians
        test_output = puatan2f32(y_input,x_input);

        endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
        differenceCounter = startCounter - endCounter - overheadCounter;
        CPUTimer_stopTimer(CPUTIMER0_BASE);

        printf("atan2f() computed with builtin/intrinsic TMU instructions...\n");
        printf("%.7f, %.7f,Error = %.7f\n",(test_output*TWOPI),test_golden_atan2,((test_output*TWOPI)-test_golden_atan2));
        if(fabsf((test_output*TWOPI)-test_golden_atan2)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #else
        CPUTimer_startTimer(CPUTIMER0_BASE);
        startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

        test_output = atan2f(y_input,x_input);
        
        endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
        differenceCounter = startCounter - endCounter - overheadCounter;
        CPUTimer_stopTimer(CPUTIMER0_BASE);

        printf("atan2f() computed with RTS library call...\n");
        printf("%.7f, %.7f,Error = %.7f\n",test_output,test_golden_atan2,(test_output-test_golden_atan2));
        if(fabsf(test_output-test_golden_atan2)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #endif

    printf("Completed atanf, atan2f test Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("atan2f Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);
}

// End of File
