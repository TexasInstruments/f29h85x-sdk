//#############################################################################
//
// FILE:   matrix_example.c
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
#include "matrix.h"

#include "device.h"
#include <matrix_example.h>

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
extern float32_t Ma_f32[4][4],Mb_f32[4][4],Mc_f32[4][4];
extern const float32_t Mr_f32[4][4];


//*****************************************************************************
// function definitions
//*****************************************************************************
int32_t main(void)
{
    // Locals
    int32_t i;
    float32_t *ptr_c_f32;
    const float32_t *ptr_r_f32;
    float32_t tmp_error;
    

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
    
    printf("4x4 matrix multiply...\n");

    CPUTimer_startTimer(CPUTIMER0_BASE);
    __builtin_instrumentation_label("MatrixMpy_start");
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    #if USE_C
        matrix_mpy_f32_4by4(Ma_f32, Mb_f32, Mc_f32);
    #else
        matrix_mpy_f32_4by4_casm(Ma_f32, Mb_f32, Mc_f32);
    #endif

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    __builtin_instrumentation_label("MatrixMpy_stop");
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    // Error checking
    ptr_c_f32 = &Mc_f32[0][0];
    ptr_r_f32 = &Mr_f32[0][0];
    for(i=0;i<16;i++)
    {
        tmp_error = fabsf((*ptr_c_f32++) - (*ptr_r_f32++));
        if(tmp_error < tolerance) 
        {
            pass++;
        }else{
            fail++;
        }
    }
    #if USE_C
        printf("Completed 4x4 matrix multiply in C, Pass_count = %d, Fail_count = %d \n", pass, fail);
    #else
        printf("Completed 4x4 matrix multiply in Asm, Pass_count = %d, Fail_count = %d \n", pass, fail);
    #endif    
    printf("matrix Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);
    while(1)
    {}
}

// End of File
