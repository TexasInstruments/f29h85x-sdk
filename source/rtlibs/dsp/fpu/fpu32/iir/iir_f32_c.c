/*
 *	Copyright (C) Texas Instruments Incorporated
 *
 *	All rights reserved not granted herein.
 *	Limited License.

 *	Texas Instruments Incorporated grants a world-wide, royalty-free,
 *	non-exclusive license under copyrights and patents it now or hereafter
 *	owns or controls to make, have made, use, import, offer to sell and sell ("Utilize")
 *	this software subject to the terms herein.  With respect to the foregoing patent
 *	license, such license is granted  solely to the extent that any such patent is necessary
 *	to Utilize the software alone.  The patent license shall not apply to any combinations which
 *	include this software, other than combinations with devices manufactured by or for TI ("TI Devices").
 *	No hardware patent is licensed hereunder.

 *	Redistributions must preserve existing copyright notices and reproduce this license (including the
 *	above copyright notice and the disclaimer and (if applicable) source code license limitations below)
 *	in the documentation and/or other materials provided with the distribution

 *	Redistribution and use in binary form, without modification, are permitted provided that the following
 *	conditions are met:

 *	  - No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any
 *		 software provided in binary form.
 *	  - Any redistribution and use are licensed by TI for use only with TI Devices.
 *	  - Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.

 *	If software source code is provided to you, modification and redistribution of the source code are permitted
 *	provided that the following conditions are met:
 *
 *	  - any redistribution and use of the source code, including any resulting derivative works, are licensed by
 *		TI for use only with TI Devices.
 *	  - any redistribution and use of any object code compiled from the source code and any resulting derivative
 *		works, are licensed by TI for use only with TI Devices.
 *
 *	Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or
 *	promote products derived from this software without specific prior written permission.

 *	DISCLAIMER.
 *
 *	THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 *	BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *	IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 *	OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE.
*/

#include "iir_f32.h"
#include <string.h>

//
// Function: iir_f32_sample
// Filter an input sample with an IIR biquad filter (1 SOS)
// Transposed Direct Form 2 Structure
__attribute__((section("kernel_opt")))
void iir_f32_sample(IIR_f32_Handle hndIIR_f32)
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

*out = (*in * filt[0]) + hist[0];
hist[0]= (*in * filt[1]) + hist[1] - (*out * filt[4]);
hist[1] = (*in * filt[2]) - (*out * filt[5]);
	
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
