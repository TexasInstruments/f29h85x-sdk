//#############################################################################
//
// FILE:   ceilf_example.c
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
#include <ceilf_example.h>

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
extern volatile float32_t test_input_1;
extern volatile float32_t test_input_2;
extern volatile float32_t test_input_3;
extern volatile float32_t test_input_4;
extern volatile float32_t test_input_5;
extern volatile float32_t test_input_6;
extern volatile float32_t test_input_7;
extern volatile float32_t test_input_8;


extern const float32_t test_golden_1;
extern const float32_t test_golden_2;
extern const float32_t test_golden_3;
extern const float32_t test_golden_4;
extern const float32_t test_golden_5;
extern const float32_t test_golden_6;
extern const float32_t test_golden_7;
extern const float32_t test_golden_8;

__attribute__((location(0x200E0000))) float32_t test_output;

//*****************************************************************************
// function definitions
//*****************************************************************************
int32_t main(void)
{
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

    #ifdef FASTMATH
        printf("ceilf computed with FRACF builtin/intrinsic...\n");
        
        CPUTimer_startTimer(CPUTIMER0_BASE);
        startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
        
        test_output = ceilf_opt(test_input_1);

        endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
        differenceCounter = startCounter - endCounter - overheadCounter;
        CPUTimer_stopTimer(CPUTIMER0_BASE);

        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_1,(test_output-test_golden_1));
        if(fabsf(test_output-test_golden_1)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf_opt(test_input_2);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_2,(test_output-test_golden_2));
        if(fabsf(test_output-test_golden_2)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf_opt(test_input_3);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_3,(test_output-test_golden_3));
        if(fabsf(test_output-test_golden_3)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf_opt(test_input_4);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_4,(test_output-test_golden_4));
        if(fabsf(test_output-test_golden_4)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf_opt(test_input_5);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_5,(test_output-test_golden_5));
        if(fabsf(test_output-test_golden_5)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf_opt(test_input_6);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_6,(test_output-test_golden_6));
        if(fabsf(test_output-test_golden_6)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf_opt(test_input_7);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_7,(test_output-test_golden_7));
        if(fabsf(test_output-test_golden_7)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf_opt(test_input_8);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_8,(test_output-test_golden_8));
        if(fabsf(test_output-test_golden_8)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #else
        printf("ceilf computed with RTS library call...\n");

        CPUTimer_startTimer(CPUTIMER0_BASE);
        startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

        test_output = ceilf(test_input_1);

        endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
        differenceCounter = startCounter - endCounter - overheadCounter;
        CPUTimer_stopTimer(CPUTIMER0_BASE);

        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_1,(test_output-test_golden_1));
        if(fabsf(test_output-test_golden_1)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf(test_input_2);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_2,(test_output-test_golden_2));
        if(fabsf(test_output-test_golden_2)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf(test_input_3);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_3,(test_output-test_golden_3));
        if(fabsf(test_output-test_golden_3)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf(test_input_4);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_4,(test_output-test_golden_4));
        if(fabsf(test_output-test_golden_4)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf(test_input_5);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_5,(test_output-test_golden_5));
        if(fabsf(test_output-test_golden_5)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf(test_input_6);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_6,(test_output-test_golden_6));
        if(fabsf(test_output-test_golden_6)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf(test_input_7);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_7,(test_output-test_golden_7));
        if(fabsf(test_output-test_golden_7)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }

        test_output = ceilf(test_input_8);        
        printf("%4.6f, %4.6f,Error = %.7f\n",test_output,test_golden_8,(test_output-test_golden_8));
        if(fabsf(test_output-test_golden_8)<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    
    #endif

    printf("Completed ceilf test Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("ceilf Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);
}

// End of File
