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

#include "fir_f32.h"
#include <string.h>

#if defined __has_builtin
#  if __has_builtin(__builtin_c29_inccirc)
#    define INCCIRC(x, y) __builtin_c29_inccirc((x), (y))
#  else
#    define INCCIRC(x, y) inccirc((x), (y))
#  endif
#else
#  define INCCIRC(x, y) inccirc((x), (y))
#endif

#if defined __has_builtin
#  if __has_builtin(__builtin_c29_deccirc)
#    define DECCIRC(x, y) __builtin_c29_deccirc((x), (y))
#  else
#    define DECCIRC(x, y) deccirc((x), (y))
#  endif
#else
#  define DECCIRC(x, y) deccirc((x), (y))
#endif

__attribute__((section("kernel_opt")))
void fir_f32_c(FIR_f32_Handle hndFIR_f32,float32_t *restrict out, float32_t *restrict in, uint32_t input_size)
{
    uint32_t filt_size;
    float32_t *filt;
    float32_t *hist;

    // map the F28x handle to the F29x function arguments
    filt_size = hndFIR_f32->order;
    filt = hndFIR_f32->coeff_ptr;
    hist = hndFIR_f32->dbuffer_ptr;

    //
    // the FIR filter function
    //
    float32_t acc;
    static int circular_buff_index = 0;
    int n;
    int j;
    
    //
    // apply the filter to each input sample
    //
    for ( n = 0; n < input_size; n++ ) 
    {
        hist[circular_buff_index] = in[n];
        
        //
        // calculate output n
        //
        acc = 0;
        filt = hndFIR_f32->coeff_ptr;
        for ( j = 0; j < filt_size; j++ ) {
            acc += (*filt++) * hist[circular_buff_index];
            circular_buff_index = DECCIRC(circular_buff_index, (filt_size - 1));
        }
        out[n] = acc;
        
        circular_buff_index = INCCIRC(circular_buff_index,(filt_size - 1));
    }
}

__attribute__((section("kernel_asm")))
void fir_f32_casm(FIR_f32_Handle hndFIR_f32,float32_t *restrict out, float32_t *restrict in, uint32_t input_size)
{
    uint32_t filt_size;
    float32_t *filt;
    float32_t *hist;

    // map the F28x handle to the F29x function arguments
    filt_size = hndFIR_f32->order;
    filt = hndFIR_f32->coeff_ptr;
    hist = hndFIR_f32->dbuffer_ptr;
    
    fir_f32_asm(input_size, filt_size, out, in, filt, hist);

}

void FIR_f32_init(FIR_f32_Handle hndFIR_f32)
{
    memset(hndFIR_f32->dbuffer_ptr,0U,sizeof(float32_t)*(hndFIR_f32->order));
}
