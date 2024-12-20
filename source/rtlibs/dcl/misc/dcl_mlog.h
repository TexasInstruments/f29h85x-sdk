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
#ifndef _DCL_MLOG_H_
#define _DCL_MLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *  
 *  \file       dcl_mlog.h
 *  \brief      Defines the interface to Multi-channel data logger (mlog) 
 */

#include "dcl_fdlog.h"
#include "../dcl_common.h"

//! \brief          Defines the number of MLOG channels
//!
#define MLOG_CHANS   4

//! \brief          Enumerated MLOG operating modes
//!
typedef enum dcl_mlog_states
{
    MLOG_INVALID  =  0,   //!< Buffer pointers not initialised
    MLOG_IDLE     =  1,   //!< Memory initialised but module not armed
    MLOG_ARMED    =  2,   //!< Armed: capturing monitor frame data and waiting for trigger
    MLOG_CAPTURE  =  3,   //!< Triggered: logging data into capture frame
    MLOG_COMPLETE =  4,   //!< Full data frame captured and available for read-out
} DCL_mlog_states;

//! \brief          Defines the MLOG structure
//!
typedef _DCL_VOLATILE struct dcl_mlog 
{
    DCL_FDLOG captFrame[MLOG_CHANS]; //!< Capture data frames
    float32_t *data[MLOG_CHANS];     //!< Data channel pointers
    float32_t trigMax;               //!< Upper trigger threshold
    float32_t trigMin;               //!< Lower trigger threshold
    uint32_t  tScale;                //!< Number of samples per log write
    uint32_t  sCount;                //!< Sample counter
    uint32_t  mode;                  //!< Operating mode
} DCL_MLOG;

//! \brief          Defines default values to initialise the MLOG structure
//!                 Note: modify to match number of channels
//!
#define MLOG_DEFAULTS { { FDLOG_DEFAULTS, FDLOG_DEFAULTS, FDLOG_DEFAULTS, FDLOG_DEFAULTS }, \
                        { 0x0, 0x0, 0x0, 0x0 }, \
                          0.1, -0.1, 1, 1, MLOG_invalid }

//! \brief          Initializes the MLOG module
//!
//! \param[in] q    The MLOG structure
//! \param[in] addr The start address of the memory block (must be a continous memory block size of MLOG_CHANS * size * 32bit)
//! \param[in] size The size of each memory block in 32-bit words
//! \param[in] tmin The upper trigger threshold
//! \param[in] tmax The lower trigger threshold
//! \param[in] div  The divider count, for example, 2 means capture frames everything second occurance of running DCL_runMLOG. 
//!
_DCL_CODE_ACCESS
void DCL_initMLOG(DCL_MLOG *q, float32_t *addr, uint32_t size, float32_t tmax, float32_t tmin, uint32_t div)
{
    int i;
    for (i = 0; i < MLOG_CHANS; i++)
    {
        // assign and clear capture frame, and initialize index to end of lead frame
        DCL_initLog(&(q->captFrame[i]), (addr + i*size), size);
        DCL_clearLog(&(q->captFrame[i]));
    }

    q->trigMax = tmax;
    q->trigMin = tmin;
    q->tScale = div;
    q->sCount = div;
    q->mode = MLOG_IDLE;
}

//! \brief          Resets the MLOG module: clears all frame buffers and sets idle mode
//!
//! \param[in] q    The MLOG structure
//!
_DCL_CODE_ACCESS
void DCL_resetMLOG(DCL_MLOG *q)
{
    int i;
    for (i = 0; i < MLOG_CHANS; i++)
    {
        DCL_clearLog(&(q->captFrame[i]));
    }

    q->mode = MLOG_IDLE;
}

//! \brief          Changes the MLOG mode to "MLOG_ARMED".  Only valid if current operating mode is "MLOG_IDLE"
//!
//! \param[in] q    The MLOG structure
//! \return         The operating mode
//!
_DCL_CODE_ACCESS
uint16_t DCL_armMLOG(DCL_MLOG *q)
{
    q->mode = (q->mode == MLOG_IDLE) ? MLOG_ARMED : MLOG_IDLE;
    return(q->mode);
}

//! \brief          Runs the MLOG module
//!
//! \param[in] q    The MLOG structure
//! \return         The operating mode
//!
_DCL_CODE_ACCESS
uint16_t DCL_runMLOG(DCL_MLOG *q)
{
    // skip sample unless counter reaches zero
    if (--(q->sCount) != 0)
    {
        return(q->mode);
    }

    int i;
    switch(q->mode)
    {
        // MLOG not initialised
        case MLOG_INVALID:
        // idle: do nothing
        case MLOG_IDLE:
        // complete: do nothing - results available in capture buffer
        case MLOG_COMPLETE:
        default:
            break;

        // armed: ready to begin capturing when either trigger threshold is crossed
        case MLOG_ARMED:
            // check for trigger condition
            if ((*(q->data[0]) > q->trigMax) || (*(q->data[0]) < q->trigMin))
            {
                for (i = 0; i < MLOG_CHANS; i++)
                {
                    DCL_writeLog(&(q->captFrame[i]), *(q->data[i]));
                }
                q->mode = MLOG_CAPTURE;
            }
            break;

        // capture mode: acquiring data
        case MLOG_CAPTURE:
            // check for full capture frame
            if (q->captFrame[0].dptr == q->captFrame[0].fptr)
            {
                q->mode = MLOG_COMPLETE;
            }
            else
            {
                // log data channels
                for (i = 0; i < MLOG_CHANS; i++)
                {
                    DCL_writeLog(&(q->captFrame[i]), *(q->data[i]));
                }
            }
            break;
    }
    q->sCount = q->tScale;
    return(q->mode);
}

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_MLOG_H_
