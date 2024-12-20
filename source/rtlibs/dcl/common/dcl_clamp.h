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
#ifndef _DCL_CLAMP_H_
#define _DCL_CLAMP_H_     

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *
 *  \file       dcl_clamp.h
 *  \brief      Defines both single, double precision clamp function for saturation
 */
        
//--- Controller clamping functions ------------------------------------

//! \brief          Saturates a control variable and returns true if either limit is exceeded
//!
//! \param[in] data The address of the data variable
//! \param[in] Umax The upper limit
//! \param[in] Umin The lower limit
//! \return         Returns 'false' if (Umin < data < Umax), else 'true'
//!
_DCL_CODE_ACCESS
bool DCL_runClamp(float32_t *data, float32_t Umax, float32_t Umin)
{   
    float32_t orig = *(data);
    *(data) = (*(data) > Umax) ? Umax : *(data);
    *(data) = (*(data) < Umin) ? Umin : *(data);
    return(((orig < Umax) && (orig > Umin)) ? false : true);
}

//! \brief          Saturates a control variable and returns true if either limit is exceeded 
//!
//! \param[in] data The address of the data variable
//! \param[in] Umax The upper limit
//! \param[in] Umin The lower limit
//! \return         Returns 'false' if (Umin < data < Umax), else 'true'
//!
_DCL_CODE_ACCESS
bool DCL_runClampF64(float64_t *data, float64_t Umax, float64_t Umin)
{
    float64_t orig = *(data);
    *(data) = (*(data) > Umax) ? Umax : *(data);
    *(data) = (*(data) < Umin) ? Umin : *(data);
    return(((orig < Umax) && (orig > Umin)) ? false : true);
}

//! \brief          Macro to saturate a control variable but does not change the data itself unlike runClamp() 
//!
//! \param[in] data The data value
//! \param[in] Umax The upper limit
//! \param[in] Umin The lower limit
//! \return         Returns unchanged data value is not saturated, else either Umax or Umin
#define DCL_runSat(data,Umax,Umin) (data > Umax) ? Umax : (data < Umin) ? Umin : data

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_CLAMP_H_
