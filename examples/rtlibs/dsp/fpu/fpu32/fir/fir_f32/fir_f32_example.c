//#############################################################################
//
// FILE:   fir_f32_example.c
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
#include <fir_f32_example.h>
#include <fir_f32.h>

//*****************************************************************************
//  defines
//*****************************************************************************

  

//*****************************************************************************
//  globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float32_t tolerance = 3.0e-6;

// profiling variables
uint32_t differenceCounter=0;
uint32_t startCounter=0;
uint32_t endCounter=0;
uint32_t overheadCounter=0;

// FIR_f32 object
FIR_f32 fir;
// Handle to the FIR_f32 object
FIR_f32_Handle hnd_fir = &fir;

// Input buffer to filter
extern float32_t test_input[];

// Expected output buffer
extern float32_t test_golden[];

// Filter coefficient buffer
extern float32_t filt_coeffs[];

// Delay line buffer
__attribute__((location(0x200FC000))) float32_t delayLine[COEFF_SIZE];

float32_t test_output[INPUT_SIZE];
float32_t test_error[INPUT_SIZE];
//*****************************************************************************
//  function definitions
//*****************************************************************************
int32_t main(void)
{
    // Locals
    uint16_t i;
    float32u_t in, out, gold, err;
        
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
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    overheadCounter = startCounter - endCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);


    // Configure the object
    FIR_f32_setCoefficientsPtr(hnd_fir, filt_coeffs);
    FIR_f32_setDelayLinePtr(hnd_fir, delayLine);
    FIR_f32_setOrder(hnd_fir, COEFF_SIZE);
    FIR_f32_setInitFunction(hnd_fir, (v_pfn_v)FIR_f32_init);

    // Run the initialization function
    hnd_fir->init(hnd_fir);

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    // Call the calculation routine
    // fir_f32_c and fir_f32_asm run on the complete input block
    // they replace FIR_f32_calc which runs per sample
    #if USE_C
        fir_f32_c(hnd_fir,test_output,test_input,INPUT_SIZE);
    #else
        fir_f32_casm(hnd_fir,test_output,test_input,INPUT_SIZE);
    #endif
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    for(i = 0U; i < INPUT_SIZE; i++)
    {
        err.f32 = fabsf(test_output[i] - test_golden[i]);

        if(err.f32 < tolerance)
        {
            pass++;
        }
        else
        {
            fail++;
        }
        test_error[i] = err.f32;
    }
    printf("FIR Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("FIR Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);
    while(1)
    {}
}

// End of File
