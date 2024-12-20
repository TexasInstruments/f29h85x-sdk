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
#ifndef _DCL_STABILITY_H_
#define _DCL_STABILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *  
 *  \file       dcl_stability.h
 *  \brief      Defines polynomial stability functions
 */

//--- Polynomial stability functions -----------------------------------------

//! \brief          Determines stability of a first order real polynomial
//!                 P(z) = z + a1
//!
//! \param[in] a1   Coefficient a1
//! \return         'true' if the root has magnitude less than 1, 'false' otherwise
//!
_DCL_CODE_ACCESS
bool DCL_isStablePn1(float32_t a1)
{
    return ((a1 * a1) < 1.0f);
}

//! \brief          Determines stability of a second order polynomial with real coefficients
//!                 P(z) = a0 z^2 + a1 z + a2
//!
//! \param[in] a0   Second order coefficient a1
//! \param[in] a1   First order coefficient a1
//! \param[in] a2   Coefficient a2
//! \return         'true' if both roots have magnitude less than 1, 'false' otherwise
//!
_DCL_CODE_ACCESS
bool DCL_isStablePn2(float32_t a0, float32_t a1, float32_t a2)
{
    float32_t b0, b1, c0;

    b0 = a0 - a2 * a2 / a0;
    b1 = a1 - a1 * a2 / a0;
    c0 = b0 - b1 * b1 / b0;

    return ((a0 > 0.0f) && (b0 > 0.0f) && (c0 > 0.0f));
}

//! \brief          Determines stability of a third order polynomial with real coefficients
//!                 P(z) = a0 z^3 + a1 z^2 + a2 z + a3
//!
//! \param[in] a0   Third order coefficient a1
//! \param[in] a1   Second order coefficient a1
//! \param[in] a2   First order coefficient a2
//! \param[in] a3   Coefficient a3
//! \return         'true' if all roots have magnitude less than 1, 'false' otherwise
//!
_DCL_CODE_ACCESS
bool DCL_isStablePn3(float32_t a0, float32_t a1, float32_t a2, float32_t a3)
{
    float32_t b0, b1, b2, c0, c1, d0;

    b0 = a0 - a3 * a3 / a0;
    b1 = a1 - a2 * a3 / a0;
    b2 = a2 - a1 * a3 / a0;
    c0 = b0 - b2 * b2 / b0;
    c1 = b1 - b1 * b2 / b0;
    d0 = c0 - c1 * c1 / c0;

    return ((a0 > 0.0f) && (b0 > 0.0f) && (c0 > 0.0f) && (d0 > 0.0f));
}

/*
//! \brief         Determines stability of a ZPK3 representation by checking pole magnitude
//!                Located in common/dcl_zpk3.h
extern bool DCL_isStableZpk3(DCL_ZPK3 *q);
*/

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_STABILITY_H_
