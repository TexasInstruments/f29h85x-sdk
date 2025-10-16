//#############################################################################
//
//
// $Copyright:
//#############################################################################
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
#ifndef MLOG_CHANS
#define MLOG_CHANS   4
#endif

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
