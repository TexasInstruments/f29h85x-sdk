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
 
#ifndef _DCL_ERROR_H_
#define _DCL_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *  
 *  \file       dcl_error.h
 *  \brief      Defines all error handling strctures and macro
 */

#include "../dcl_common.h"

//--- Error handling ---------------------------------------------------------

//! \brief          Defines the library enumerated error codes.
//!                 These will be applied as bit masks in the error handler
//!
typedef enum dcl_error_codes
{
    dcl_none = 0U,                         //!< No error
    dcl_param_range_err =   (1U << 0),     //!< Parameter range exceeded
    dcl_param_invalid_err = (1U << 1),     //!< Parameter not valid
    dcl_param_warn_err =    (1U << 2),     //!< Parameter warning
    dcl_input_range_err =   (1U << 3),     //!< Input range exceeded
    dcl_overflow_err =      (1U << 4),     //!< Numerical overflow
    dcl_underflow_err =     (1U << 5),     //!< Numerical underflow  
    dcl_controller_err =    (1U << 6),     //!< Controller operation not completed
    dcl_timing_err =        (1U << 7),     //!< Timing error
    dcl_comp_err =          (1U << 8)      //!< Computation error
} DCL_error_codes;

//! \brief            Macro to clear stored error code in CSS
//!
//! \param[in] ptr    DCL controller object that contains css
//!
#define DCL_clearError(ptr)        ((ptr)->css->err = dcl_none)

//! \brief            Macro to set error code in CSS
//!
//! \param[in] ptr    DCL controller object that contains css
//! \param[in] code   enum dcl_error_codes
//!
#define DCL_setError(ptr,code)        ((ptr)->css->err |= code)

//! \brief            Macro to store line location of error in CSS
//!
//! \param[in] ptr    DCL controller object that contains css
//!
#define DCL_getErrorLine(ptr)        ((ptr)->css->err_line = ((ptr)->css->err) ? __LINE__ : 0)

//! \brief            Macro to store function location of error in CSS
//!
//! \param[in] ptr    DCL controller object that contains css
//!
#define DCL_getErrorFunc(ptr)        ((ptr)->css->err_func = ((ptr)->css->err) ? __FUNCTION__ : NULL)

//! \brief            Macro to store error info in CSS
//!
//! \param[in] ptr    DCL controller object that contains css
//!
#define DCL_getErrorInfo(ptr) \
{                             \
    DCL_getErrorLine(ptr);    \
    DCL_getErrorFunc(ptr);    \
}

//! \brief            Prototype for basic error handler
//!
//! \param[in] ptr    DCL controller object that contains css
//!
#define DCL_runErrorHandler(ptr) \
{                                \
    if(ptr->css->err != dcl_none)\
    {                            \
        DCL_setBreakPoint();     \
        DCL_clearError(ptr);     \
    }                            \
}

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_ERROR_H_
