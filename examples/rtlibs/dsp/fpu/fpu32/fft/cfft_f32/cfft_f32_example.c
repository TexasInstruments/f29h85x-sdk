//#############################################################################
//
// FILE:   cfft_f32_example.c
//
// TITLE:  Complex FFT, specify the implementation type (Optimized C 
// or Optimized Assembly) and the number of stages/size in 
// cfft_f32_example.h, build and run the example
// It will print statements as it executes the example, along with
// Pass/Fail information
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
#include <cfft_f32_example.h>
#include <cfft_f32.h>

//*****************************************************************************
// defines
//*****************************************************************************
 
//*****************************************************************************
// globals
//*****************************************************************************
// The global pass, fail values
int16_t pass = 0U, fail = 0U;
// Error tolerance for FFT outputs
float32_t tolerance = 0.005F;
// Error tolerance for magnitude and phase
float32_t tolerance_mag_phase = 0.03F;

// profiling variables
uint32_t differenceCounter=0;
uint32_t startCounter=0;
uint32_t endCounter=0;
uint32_t overheadCounter=0;

// CFFT object
CFFT_F32_STRUCT cfft;
// Handle to the object
CFFT_F32_STRUCT_Handle hnd_cfft = &cfft;

// test input, output, golden (expected output) arrays
// input, output size is twice FFT_SIZE because array is complex (real, imag)
// golden size is four times FFT_SIZE because it contains the complex FFT output (twice FFT_SIZE) plus magnitude (FFT_SIZE) plus phase (FFT_SIZE)
extern float32_t test_input[];
extern float32_t test_golden[];

__attribute__((location(0x200E0000))) float32_t test_output[FFT_SIZE << 1];

// test error, magnitude, phase arrays
float32_t test_error[FFT_SIZE << 1];
// size is FFT_SIZE because one mag and phase value per FFT bin
float32_t test_magnitude[FFT_SIZE];
float32_t test_phase[FFT_SIZE];

// size is twice FFT_SIZE because cos and sin twiddle per bin
// allocate test_input, test_output, and twiddleFactors in different RAM blocks so there are no stalls on parallel loads
__attribute__((aligned(8))) __attribute__((location(0x20140000))) float32_t twiddleFactors[FFT_SIZE << 1];

//*****************************************************************************
// function definitions
//*****************************************************************************
int32_t main(void)
{
    // Locals
    int16_t i, j;
    float32u_t out, gold, err;
    float32_t *p_temp;
    
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

    // Configure the FFT object
    printf("Configuring FFT object...\n");
    CFFT_f32_setInputPtr(hnd_cfft, test_input);
    CFFT_f32_setOutputPtr(hnd_cfft, test_output);
    CFFT_f32_setStages(hnd_cfft, FFT_STAGES);
    CFFT_f32_setFFTSize(hnd_cfft, FFT_SIZE);
    
    printf("Computing Twiddles...\n");
    //Twiddle factor table
#ifdef USE_TABLES
    CFFT_f32_setTwiddlesPtr(hnd_cfft, CFFT_f32_twiddleFactors);
#else
    CFFT_f32_setTwiddlesPtr(hnd_cfft, twiddleFactors);
    CFFT_f32_computeTwiddle(hnd_cfft);   
#endif //USE_TABLES

    printf("Bitreversing input...\n");
    // Bit reverse the inputs - the function bit reverses the input array and returns it in the same array
    CFFT_f32_bitrev((complex_T *)(test_input), (complex_T *)(test_output), FFT_SIZE);
    // Run the calculation function

    printf("Computing CFFT...\n");
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
#ifdef USE_TABLES
    CFFT_f32t(hnd_cfft);                   // Calculate FFT
#else
    #if USE_C
        CFFT_f32_c(hnd_cfft);                // Optimized C CFFT
    #else
        CFFT_f32_asm(hnd_cfft);                // Optimized assembly CFFT
    #endif
#endif //USE_TABLES
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    // Check the output
    #if USE_C
    // OptC implementation is In-place, so output is always at the input ptr
        p_temp = CFFT_f32_getInputPtr(hnd_cfft);
    #else
    // Asm implementation is out of place, so output is at the input ptr if number of FFT stages is odd..
    // ..output is in the output ptr if FFT stages is even
    // we have designed getCurrInputPtr to return the correct ptr representing the FFT output
        p_temp = CFFT_f32_getCurrInputPtr(hnd_cfft);
    #endif
    
    printf("Performing FFT error checking..\n");
    for(i = 0U; i < (FFT_SIZE << 1); i++)
    {
        out.f32  = p_temp[i];
        gold.f32 = test_golden[i];
        err.f32  = fabsf(out.f32 - gold.f32);
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
    printf("CFFT Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("CFFT Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);

    // Zero out the error array
    memset(test_error, 0U, sizeof(float32_t)*(FFT_SIZE << 1));
    
    // Set CurrInPtr = input to Magnitude calculation = FFT output
    printf("Computing Magnitude...\n");
    #if USE_C
    // If C, FFT output is at test_input
        CFFT_f32_setCurrInputPtr(hnd_cfft, test_input);
    #else
    // If asm, we have designed getCurrInputPtr to return the correct ptr representing the FFT output
        p_temp = CFFT_f32_getCurrInputPtr(hnd_cfft);
    // now Set CurrInPtr = input to Magnitude calculation = FFT output
        CFFT_f32_setCurrInputPtr(hnd_cfft, p_temp);
    #endif    
    // Set output for magnitude calc
    CFFT_f32_setCurrOutputPtr(hnd_cfft, test_magnitude);
    // Calculate Magnitude:    
    CFFT_f32_mag(hnd_cfft);          

    // below step is the same as p_temp = test_magnitude
    p_temp      = CFFT_f32_getCurrOutputPtr(hnd_cfft);
    printf("Performing FFT magnitude error checking..\n");
    for(i = (FFT_SIZE << 1), j=0U; i < (3U*FFT_SIZE); i++, j++)
    {
    	out.f32     = p_temp[j];
        gold.f32    = test_golden[i];
        err.f32     = fabsf(out.f32 - gold.f32);
        if(err.f32 < tolerance_mag_phase)
        {
            pass++;
        }
        else
        {
            fail++;
        }
        test_error[j] = err.f32;
    }
    printf("FFT Pass_count = %d, Fail_count = %d \n", pass, fail);
    // Zero out the error array
    memset(test_error, 0U, sizeof(float32_t)*(FFT_SIZE << 1));
    
    // Set CurrInPtr = input to Phase calculation = FFT output
    printf("Computing Phase...\n");
    #if USE_C
    // If C, FFT output is at test_input
        CFFT_f32_setCurrInputPtr(hnd_cfft, test_input);
    #else
    // If asm, we have designed getCurrInputPtr to return the correct ptr representing the FFT output
        p_temp = CFFT_f32_getCurrInputPtr(hnd_cfft);
    // now Set CurrInPtr = input to Phase calculation = FFT output 
        CFFT_f32_setCurrInputPtr(hnd_cfft, p_temp);
    #endif    
    // Set output for phase calc
    CFFT_f32_setCurrOutputPtr(hnd_cfft, test_phase);
    // Calculate phase:    
    CFFT_f32_phase(hnd_cfft);          

    // below step is the same as p_temp = test_phase
    p_temp      = CFFT_f32_getCurrOutputPtr(hnd_cfft);
    printf("Performing FFT phase error checking..\n");
    for(i = 3U*FFT_SIZE, j=0U; i < (FFT_SIZE << 2); i++, j++)
    {
    	out.f32     = p_temp[j];
        gold.f32    = test_golden[i];
        err.f32     = fabsf(out.f32 - gold.f32);
        if(err.f32 < tolerance_mag_phase)
        {
            pass++;
        }
        else
        {
            fail++;
        }
        test_error[j] = err.f32;
    }
    printf("Completed %d-pt CFFT Pass_count = %d, Fail_count = %d \n", FFT_SIZE, pass, fail);
}

// End of File
