//#############################################################################
//
// FILE:   iir_f32_example.c
//
// TITLE:  
//
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
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
#include <iir_f32_example.h>
#include <iir_f32.h>

//*****************************************************************************
//  defines
//*****************************************************************************

  

//*****************************************************************************
//  globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float32_t tolerance = 1.0e-6;

// profiling variables
uint32_t differenceCounter=0;
uint32_t startCounter=0;
uint32_t endCounter=0;
uint32_t overheadCounter=0;

// IIR_f32 object
IIR_f32 iir;
// Handle to the IIR_f32 object
IIR_f32_Handle hnd_iir = &iir;

// Input buffer to filter
extern float32_t test_input[];

// Expected output buffer
extern float32_t test_golden[];

// Filter coefficient buffer
extern float32_t filt_coeffs[];

// Delay line buffer
__attribute__((location(0x200FC000))) float32_t delayLine[NUM_SOS*2];

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

    // reduce rounding error by rounding to nearest even instead of rounding towards 0
    ROUND_TO_NEAREST_EVEN;

    // Configure the object
    IIR_f32_setCoefficientsBPtr(hnd_iir, &filt_coeffs[0]);
    //IIR_f32_setCoefficientsAPtr(hnd_iir, &filt[3]);
    IIR_f32_setDelayLinePtr(hnd_iir, delayLine);
    IIR_f32_setInputPtr(hnd_iir, test_input);
    IIR_f32_setOutputPtr(hnd_iir, test_output);
    //IIR_f32_setScalePtr(hnd_iir, scaleFactors);
    IIR_f32_setOrder(hnd_iir, FILTER_ORDER);
    IIR_f32_setInitFunction(hnd_iir, (v_pfn_v)IIR_f32_init);
    
    // Run the initialization function
    hnd_iir->init(hnd_iir);

    // Call the calculation routine
    // iir_f32_sample runs on 1 input sample and iir_f32_loop run on the complete input block
    // iir_f32_sample replaces IIR_f32_calc, both of which run per sample
    
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    iir_f32_loop(hnd_iir,INPUT_SIZE);
    
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
    printf("IIR loop Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("IIR loop Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);

    // Run the initialization function again
    hnd_iir->init(hnd_iir);    

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    iir_f32_sample(hnd_iir);
    
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    pass=0;
    fail=0;
    err.f32 = fabsf(test_output[0] - test_golden[0]);

    if(err.f32 < tolerance)
    {
        pass++;
    }
    else
    {
        fail++;
    }
    test_error[0] = err.f32;
    printf("IIR sample Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("IIR sample Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);

}

// End of File
