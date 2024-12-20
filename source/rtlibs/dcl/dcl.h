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

#ifndef _DCL_H_
#define _DCL_H_

#ifdef __cplusplus
extern "C" {
#endif

 /**
 * \defgroup RTLIBS_API APIs for Real Time Libraries
 *
 * This module contains APIs for real time libraries in this SDK.
 */

/**
 *  \defgroup DCL_API_MODULE APIs for Digital Control Library
 *  \ingroup  RTLIBS_API
 *  
 *  Here is the list of APIs used for Digital Control Library
 *  @{
 *
 *  \file     dcl.h
 *  \brief    Top level header that contains all collections of Digital Controller Library functions
 *  
 *  \details  To use this library, simply use
 *  \code     #include "dcl.h" \endcode
 *            while making sure the path to this file is added as a compiler include path
 */

//! \brief          Library version number formatted for numerical comparison
//!                 v4.02.00.00
#define DCL_VERSION 4020000

//! \brief          Enable voltaile flag for dcl strcutures
//!                 Disabled by default
//#define DCL_VOLATILE_ENABLED

//! \brief          Build the library with error handling enabled
//!                 Performs error checks on various update and
//!                 stability functions
//!                 Disabled by default
//#define DCL_ERROR_HANDLING_ENABLED

//! \brief          Build the library with test points enabled
//!                 during arthmetic operations
//!                 Disabled by default
//#define DCL_TESTPOINTS_ENABLED

/* Includes legacy API */
#ifndef DCL_NO_LEGACY_API
#include "misc/dcl_c28_compatibility.h"
#endif

/* utilities */
#include "misc/dcl_error.h"
#include "misc/dcl_fdlog.h"
#include "misc/dcl_gsm.h"
#include "misc/dcl_mlog.h"
#include "misc/dcl_refgen.h"
#include "misc/dcl_tcm.h"

/* 32bit arithmetic */
#include "pi/dcl_pi.h"
#include "pi/dcl_pi2.h"
#include "pid/dcl_pid.h"
#include "pid/dcl_nlpid.h"

#include "df/dcl_df11.h"
#include "df/dcl_df12.h"
#include "df/dcl_df13.h"
#include "df/dcl_df22.h"
#include "df/dcl_df23.h"

/* 64bit arithmetic */
#include "pid/dcl_pidf64.h"

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_H_
