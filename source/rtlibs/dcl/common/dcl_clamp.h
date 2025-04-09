//#############################################################################
//
//
// $Copyright:
//#############################################################################
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
#if defined (__C29__)
    #define DCL_runSat(data,Umax,Umin) __builtin_c29_i32_minmaxf32_m(data,Umax,Umin)
#else
    #define DCL_runSat(data,Umax,Umin) (data > Umax) ? Umax : (data < Umin) ? Umin : data
#endif

//! \brief          Macro to saturate a control variable but does not change the data itself unlike runClamp() 
//!
//! \param[in] data The data value
//! \param[in] Umax The upper limit
//! \param[in] Umin The lower limit
//! \return         Returns unchanged data value is not saturated, else either Umax or Umin
#if defined (__C29_OPTF64__)
    #define DCL_runSatF64(data,Umax,Umin) __builtin_c29_i32_minmaxf64_xm(data,Umax,Umin)
#else
    #define DCL_runSatF64(data,Umax,Umin) (data > Umax) ? Umax : (data < Umin) ? Umin : data
#endif


/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_CLAMP_H_
