//#############################################################################
//
// FILE:   expf_example.c
//
// TITLE:  
// The API is F28x compatible
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
#include <expf_example.h>

//*****************************************************************************
// defines
//*****************************************************************************
 
//*****************************************************************************
// globals
//*****************************************************************************
// The global pass, fail values
int16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float32_t tolerance = 2.0e-5;

// profiling variables
uint32_t differenceCounter_rts=0;
uint32_t differenceCounter_tmu=0;
uint32_t startCounter=0;
uint32_t endCounter=0;
uint32_t overheadCounter=0;

// test input, output, golden (expected output)
extern volatile float32_t num_input[];

extern const float32_t test_golden[];

float32_t test_output_expf_rts[INPUT_SIZE];
float32_t test_output_expf_tmu[INPUT_SIZE];

//*****************************************************************************
// function definitions
//*****************************************************************************
int32_t main(void)
{
    uint32_t i;
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

    
    printf("expf computed with RTS library call...\n");
    
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    for(i=0;i<INPUT_SIZE;i++)
    {
        test_output_expf_rts[i] = expf(num_input[i]);
    }
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter_rts = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    
    printf("expf computed with TMU...\n");
    
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    for(i=0;i<INPUT_SIZE;i++)
    {
        test_output_expf_tmu[i] = expf_opt(num_input[i]);
    }
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter_tmu = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    for(i=0;i<INPUT_SIZE;i++)
    {
        printf("Input=%.7f,RTS output=%.10f,Golden output=%.10f,RTS Error = %.10f\n",num_input[i],test_output_expf_rts[i],test_golden[i],(test_output_expf_rts[i]-test_golden[i]));
        if(fabsf(test_output_expf_rts[i]-test_golden[i])<tolerance)
        {
            pass++;
        } else {
            fail++;
        }    
        
        printf("Input=%.7f,TMU output=%.10f,Golden output=%.10f,TMU Error = %.10f\n",num_input[i],test_output_expf_tmu[i],test_golden[i],(test_output_expf_tmu[i]-test_golden[i]));
        if(fabsf(test_output_expf_tmu[i]-test_golden[i])<tolerance)
        {
            pass++;
        } else {
            fail++;
        }
    }
    
    printf("Completed expf test Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("expf with RTS Cycles = %d, Timer overhead = %d \n", differenceCounter_rts/INPUT_SIZE, overheadCounter);
    printf("expf with TMU Cycles = %d, Timer overhead = %d \n", differenceCounter_tmu/INPUT_SIZE, overheadCounter);
}

// End of File
