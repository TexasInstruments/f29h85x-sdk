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
#ifndef _DCL_MACRO_H_
#define _DCL_MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif     

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *  
 *  \file       dcl_macro.h
 *  \brief      Defines all the auxiliary macros for DCL
 */

#ifndef NULL
#define NULL    0
#endif

//! \brief          Local definitions of the mathematical constant pi
//!
#define CONST_PI        3.14159265358979323846f
#define CONST_2PI       2.0f * CONST_PI
#define CONST_PI_F64    3.1415926535897932384626433832795028841971693993751058209749445923078164062L
#define CONST_2PI_F64   2.0L * CONST_PI_F64

//! \brief          Define the acceptable FPU numerical tolerances
//!
#define DCL_FPU32_TOL       1.0e-06f
#define DCL_FPU64_TOL       1.0e-10L

//! \brief          Define the default control period in seconds
//!
#define DCL_DEFAULT_PERIOD_S    100.0e-06f
#define DCL_DEFAULT_PERIODF64_S 100.0e-06L

//! \brief          Determines numerical proximity to specified value
//!
#define DCL_isValue(x,y)        ((float32_t) fabsf(x - y) < DCL_FPU32_TOL ? 1U : 0U)
#define DCL_isValueF64(x,y)     ((float64_t) fabs(x - y) < DCL_FPU64_TOL ? 1U : 0U)

//! \brief          Determines floating point numerical proximity to zero
//!
#define DCL_isZero(x)           DCL_isValue(x,0.0f)
#define DCL_isZeroF64(x)        DCL_isValueF64(x,0.0L)

//! \brief          Returns a random floating point result between -1.0 and +1.0
//!                 where 'a' is the multiplier in single or double precision. 
//!                 Useful for initialization of arrays and matrices during test.
//!
//! \code
//!                 float32_t s = DCL_rand(1.0f);
//! \endcode
#define DCL_rand(a)         (a * ((float32_t) rand() / (float32_t) (RAND_MAX >> 1) - 1.0f))
#define DCL_randF64(a)      (a * ((float64_t) rand() / (float64_t) (RAND_MAX >> 1) - 1.0L))

//! \brief          Defines the lower limit on derivative filter coefficient c2
//!                 in order for fc to lie below the Nyquist frequency
//!
#define DCL_c2Limit         ((2.0f - CONST_PI) / (2.0f + CONST_PI))
#define DCL_c2LimitF64      ((2.0L - CONST_PI_F64) / (2.0L + CONST_PI_F64))

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_MACRO_H_
