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
#ifndef _IQNTABLES_H_
#define _IQNTABLES_H_

#include <stdint.h>
#include "support.h"
/* LOG lookup and coefficient tables. */
#define _IQ30log_order  14
extern const uint_fast32_t _IQNlog_min[5];
extern const uint_fast32_t _IQ30log_coeffs[15];

/* asin and acos coefficient table. */
extern const int_fast32_t _IQ29Asin_coeffs[17][5];

/* sin and cos lookup tables. */
extern const int_fast32_t _IQ31CosLookup[52];
extern const int_fast32_t _IQ31SinLookup[52];

/* atan coefficient table. */
extern const int_fast32_t _IQ32atan_coeffs[132];

/* Tables for exp function. Min/Max and integer lookup for each q type */
#define _IQ30exp_order  10
extern const uint_fast32_t _IQNexp_min[30];
extern const uint_fast32_t _IQNexp_max[30];
extern const uint_fast16_t _IQNexp_offset[30];
extern const uint_fast32_t _IQNexp_lookup1[22];
extern const uint_fast32_t _IQNexp_lookup2[22];
extern const uint_fast32_t _IQNexp_lookup3[22];
extern const uint_fast32_t _IQNexp_lookup4[22];
extern const uint_fast32_t _IQNexp_lookup5[22];
extern const uint_fast32_t _IQNexp_lookup6[22];
extern const uint_fast32_t _IQNexp_lookup7[22];
extern const uint_fast32_t _IQNexp_lookup8[22];
extern const uint_fast32_t _IQNexp_lookup9[22];
extern const uint_fast32_t _IQNexp_lookup10[22];
extern const uint_fast32_t _IQNexp_lookup11[22];
extern const uint_fast32_t _IQNexp_lookup12[22];
extern const uint_fast32_t _IQNexp_lookup13[22];
extern const uint_fast32_t _IQNexp_lookup14[22];
extern const uint_fast32_t _IQNexp_lookup15[22];
extern const uint_fast32_t _IQNexp_lookup16[22];
extern const uint_fast32_t _IQNexp_lookup17[22];
extern const uint_fast32_t _IQNexp_lookup18[22];
extern const uint_fast32_t _IQNexp_lookup19[22];
extern const uint_fast32_t _IQNexp_lookup20[22];
extern const uint_fast32_t _IQNexp_lookup21[22];
extern const uint_fast32_t _IQNexp_lookup22[22];
extern const uint_fast32_t _IQNexp_lookup23[22];
extern const uint_fast32_t _IQNexp_lookup24[22];
extern const uint_fast32_t _IQNexp_lookup25[22];
extern const uint_fast32_t _IQNexp_lookup26[22];
extern const uint_fast32_t _IQNexp_lookup27[22];
extern const uint_fast32_t _IQNexp_lookup28[22];
extern const uint_fast32_t _IQNexp_lookup29[22];
extern const uint_fast32_t _IQNexp_lookup30[22];
extern const uint_fast32_t _IQ30exp_coeffs[11];

/* 
 *  Q0.15 lookup table for 1/2x best guess. 
 */
extern const uint8_t _IQ6div_lookup[65];

/* 
 *  Q0.15 lookup table for 1/(2*sqrt(x)) best guess. 
 *  96 entries gives us enough accuracy to only need 2 iterations.
 */
extern const uint_fast16_t _IQ14sqrt_lookup[96];

/* 
 * Lookup table for shifting using the multiplier.
 * Right: Index is the shift count, result is high 32 bits.
 * Left: Index is 32 - count, result is low (and high) 32 bits.
 */
extern const uint_fast32_t _IQNshift32[32];

#endif
