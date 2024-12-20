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
 
#ifndef _DCL_CSS_H_
#define _DCL_CSS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *  
 *  \file       dcl_css.h
 *  \brief      Defines Controller Common Support Structure (CSS) and related macros
 */               

//--- Controller Common Support Structure ------------------------------------

//! \brief          Defines the controller common support structure
//!
//! \details        The CSS is accessed via a pointer in most of the DCL
//!                 controller structs.  It contains data used for testing and
//!                 configuring the controller, as well as for error checking.
//!
typedef struct dcl_css {
    float32_t tpt;      //!< Test point
    float32_t T;    //!< Controller period in seconds
    volatile uint32_t sts;      //!< Status word
    uint32_t err_line;          //!< Error location line (errno)
    uint32_t err;               //!< Error status code
    const char* err_func;       //!< Error function name
} DCL_CSS;

//! \brief          Default values to initialize the CSS structure
//!
#define DCL_CSS_DEFAULTS { 0.0f, DCL_DEFAULT_PERIOD_S, 0U, 0U, 0U, NULL }

//! \brief          Defines the 64bit CSS structure 
//!
typedef struct dcl_css64 {
    float64_t tpt;      //!< Test point
    float64_t T;    //!< Controller period in seconds
    volatile uint32_t sts;      //!< Status word
    uint32_t err_line;          //!< Error location line (errno)
    uint32_t err;               //!< Error status code
    const char* err_func;       //!< Error function name
} DCL_CSSF64;

//! \brief          Default values to initialize the CSS 64bit structure
//!
#define DCL_CSSF64_DEFAULTS { 0.0L, DCL_DEFAULT_PERIODF64_S, 0U, 0U, 0U, NULL }

//! \brief          Loads the controller period in the CSS
//!                 CSS pointer must be configured first
//!
//! \param[in] p     Pointer to the controller structure
//! \param[in] t_sec Controller period in seconds
//! \return          None
//!
#define DCL_setControllerPeriod(p,t_sec)   ((p)->css->T = t_sec)

//--- Status word ------------------------------------------------------------

//! \brief          Defines the library enumerated status bits
//!
//! \details        To perform a safe parameter update, the user first loads new parameter into
//!                 the controller's SPS. Then either invoke DCL_update() for an one-time update,
//!                 or in the case of an ISR routine update, the user could use 
//!                 DCL_setPendingStatus() to indicate an pending update. In which the next call to
//!                 DCL_pendingUpdate() would update the controller parameter and clear the flag.
//!                 
//!                 Both DCL_update() and DCL_pendingUpdate() disables global interrupts to ensure a safe update. 
//!
typedef enum dcl_status_bits
{
    DCL_STS_NONE = 0U,                     //!< Status empty
    DCL_STS_PARAM_UPDATE =   (1U << 0),    //!< Parameter update-in-progress flag, high if ongoing parameter update
    DCL_STS_CTRL_RUNNING =   (1U << 1),    //!< Controller operation-in-progress flag, high if operation is in progress
} DCL_status_bits;

//! \brief          Macros to set and clear the update-in-progress flag
//!
#define DCL_setUpdateStatus(p)           ((p)->css->sts |= DCL_STS_PARAM_UPDATE)
#define DCL_clearUpdateStatus(p)         ((p)->css->sts &= ~DCL_STS_PARAM_UPDATE)

//! \brief          Determine whether a parameter update-in-progress flag is set 
//!
//! \return         'true' if update status is set, otherwise false
//!
#define DCL_getUpdateStatus(p)           (0U != ((p)->css->sts & DCL_STS_PARAM_UPDATE))

//! \brief          Macros placed at the beginning and end of the controller
//!                 so that other functions know a control operation is in
//!                 progress. Typically only used with complex controllers
//!                 which may not be atomic.
//!
#define DCL_setControllerStatus(p)       ((p)->css->sts |= DCL_STS_CTRL_RUNNING)
#define DCL_clearControllerStatus(p)     ((p)->css->sts &= ~DCL_STS_CTRL_RUNNING)

//! \brief          Determine whether a controller operation-in-progress flag is set
//!
//! \return         'true' if controller running flag is set, otherwise false
//!
#define DCL_getControllerStatus(p)       (0U != ((p)->css->sts & DCL_STS_CTRL_RUNNING))

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_CSS_H_
