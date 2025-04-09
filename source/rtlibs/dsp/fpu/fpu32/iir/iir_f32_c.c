//#############################################################################
//
//
// $Copyright:
//#############################################################################

#include "iir_f32.h"
#include <string.h>

__attribute__((section("kernel_opt")))
void iir_f32_sample_inner(float32_t * restrict out, float32_t * restrict in,
             const float32_t * restrict filt, float32_t * restrict hist)
{	

*out = (*in * filt[0]) + hist[0];
hist[0]= (*in * filt[1]) + hist[1] - (*out * filt[4]);
hist[1] = (*in * filt[2]) - (*out * filt[5]);
	
}

//
// Function: iir_f32_sample
// Filter an input sample with an IIR biquad filter (1 SOS)
// Transposed Direct Form 2 Structure
__attribute__((section("kernel_opt")))
void iir_f32_sample(IIR_f32_Handle hndIIR_f32)
{	
	iir_f32_sample_inner(hndIIR_f32->p_output,hndIIR_f32->p_input,hndIIR_f32->p_coeff_B,hndIIR_f32->p_dbuffer);
}

__attribute__((section("kernel_opt")))
void iir_f32_loop_inner(uint32_t N, float * restrict out, float * restrict in,
             const float * restrict filt, float * restrict hist)
{	
uint32_t i;
float b0 = filt[0];
float b1 = filt[1];
float b2 = filt[2];
float a1 = filt[4];
float a2 = filt[5];

for(i=0;i<N;i++){
	out[i] = (in[i] * b0) + hist[0];
	hist[0]= (in[i] * b1) + hist[1] - (out[i] * a1);
	hist[1] = (in[i] * b2) - (out[i] * a2);
}
}

// Function: iir_f32_sample
// Filter an input buffer with an IIR biquad filter (1 SOS)
// Transposed Direct Form 2 Structure
__attribute__((section("kernel_opt")))
void iir_f32_loop(IIR_f32_Handle hndIIR_f32, uint32_t N)
{
float32_t *out;
float32_t *in;
float32_t *filt;
float32_t *hist;

// map the F28x handle to the F29x function arguments
out = hndIIR_f32->p_output;
in = hndIIR_f32->p_input;
filt = hndIIR_f32->p_coeff_B;
hist = hndIIR_f32->p_dbuffer;

// then call the function that implements the IIR loop
iir_f32_loop_inner(N,out,in,filt,hist);

}

void IIR_f32_init(IIR_f32_Handle hndIIR_f32)
{
    memset(hndIIR_f32->p_dbuffer,0U,sizeof(float32_t)*(hndIIR_f32->order));
}
