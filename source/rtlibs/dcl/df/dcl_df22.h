//#############################################################################
//
//
// $Copyright:
//#############################################################################
 
#ifndef _DCL_DF22_H_
#define _DCL_DF22_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *  
 *  \file       dcl_df22.h
 *  \brief      Contains direct form 2 2nd order DF22 compensator
 *              with its related structures and functions
 */              

#include "../dcl_common.h"

//--- Direct Form 2 - 2nd order ----------------------------------------------

//! \brief          Defines DCL_DF22 shadow parameter set
//!                 used for updating compensator parameter
//!
typedef struct dcl_df22_sps
{
    float32_t b0;   //!< pos. coefficient to e(k)
    float32_t b1;   //!< pos. coefficient to e(k-1)
    float32_t b2;   //!< pos. coefficient to e(k-2)
    float32_t a1;   //!< neg. coefficient to u(k-1)
    float32_t a2;   //!< neg. coefficient to u(k-2)
} DCL_DF22_SPS;

#define DF22_SPS_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f }

//! \brief          DCL_DF22 object for storing df22 specific parameters
//!
typedef _DCL_VOLATILE struct dcl_df22
{
    /* compensator parameter */
    float32_t b0;   //!< pos. coefficient to e(k)
    float32_t b1;   //!< pos. coefficient to e(k-1)
    float32_t b2;   //!< pos. coefficient to e(k-2)
    float32_t a1;   //!< neg. coefficient to u(k-1)
    float32_t a2;   //!< neg. coefficient to u(k-2)

    /* internal storage */
    float32_t x1;   //!< x1 = b1*e(k-1) - a1*u(k-1) + x2
    float32_t x2;   //!< x2 = b2*e(k-2) - a2*u(k-2)

    /* miscellaneous */
    DCL_DF22_SPS *sps; //!< updates compensator parameter
    DCL_CSS *css;      //!< configuration & debugging
} DCL_DF22;

//! \brief          Defines default values to initialize DCL_DF22
//!
#define DF22_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, \
        &(DCL_DF22_SPS)DF22_SPS_DEFAULTS, &(DCL_CSS)DCL_CSS_DEFAULTS }

//! \brief          Macro for internal default values to initialize DCL_DF22
//!                 Example: DCL_DF22 df22_ctrl = { 
//!                                                 .b0 = 1.00f,
//!                                                 .b1 = 0.0f,
//!                                                 ...
//!                                                 .a2 = 0.0f,
//!                                                 DF22_INT_DEFAULTS
//!                                               };
#define DF22_INT_DEFAULTS .x1=0.0f, .x2=0.0f, .sps=&(DCL_DF22_SPS)DF22_SPS_DEFAULTS, \
                          .css=&(DCL_CSS)DCL_CSS_DEFAULTS 
                        
//! \brief          Initialize DCL_DF22 struct with default parameters
//!                 Example: DCL_DF22* df22_ctrl = DCL_initDF22();
//!
//! \return         A DCL_DF22* pointer
//!
#define DCL_initDF22() &(DCL_DF22)DF22_DEFAULTS

//! \brief          Initialize DCL_DF22 struct with input compensator parameters
//!                 Example: DCL_DF22 DF22_ctrl = DCL_initD22asParam(1.0f,0.0f,0.0f,0.0f,0.0f);
//! \note           Note: input parameter needs to be in the same order as listed in DF22_SPS struct.
//!
//! \return         A DCL_DF22* pointer
//!
#define DCL_initDF22asParam(_b0,_b1,_b2,_a1,_a2) &(DCL_DF22){ .b0=_b0, .b1=_b1, \
                        .b2=_b2, .a1=_a1, .a2=_a2, .a3=_a3, DF22_INT_DEFAULTS }

//! \brief                  Initialize DCL_DF22 struct using sps parameters
//!                         Example: DCL_DF22_SPS df_sps = { .b0 = , .b1 = , ...}; //initial parameter
//!                                  DCL_DF22 df_ctrl;
//!                                  DCL_initDF22asSPS(&df_ctrl,&df_sps);
//!
//! \param[in] df_ptr       DCL_DF22* pointer that needs to be initialized
//! \param[in] sps_ptr      DCL_DF22_SPS* pointer with assigned parameters
//! \return                 Returns DCL_DF22* with set sps parameters, default parameter will be used
//!                         if sps_ptr is not specified   
//!
#define DCL_initDF22asSPS(df_ptr,sps_ptr)                                                \
({                                                                                       \
    DCL_DF22* new_df = (df_ptr) ? df_ptr : DCL_initDF22();                               \
    DCL_DF22_SPS* new_sps = (sps_ptr) ? sps_ptr : &(DCL_DF22_SPS)DF22_SPS_DEFAULTS;      \
    if(sps_ptr)                                                                          \
    {                                                                                    \
        *new_df = (DCL_DF22){ (new_sps)->b0, (new_sps)->b1, (new_sps)->b2, (new_sps)->a1,\
        (new_sps)->a2, 0.0f, 0.0f, (DCL_DF22_SPS*)new_sps, &(DCL_CSS)DCL_CSS_DEFAULTS }; \
    }                                                                                    \
    new_df;                                                                              \
})                    

//! \brief           Resets DF22 internal storage data with interrupt protection
//!
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//!
_DCL_CODE_ACCESS
void DCL_resetDF22(DCL_DF22 *df)
{
    dcl_interrupt_t ints;

    ints = DCL_disableInts();
    df->x1 = df->x2 = 0.0f;
    DCL_restoreInts(ints);
}

//! \brief           Loads DF22 tuning parameter from its SPS parameter without interrupt protection
//!
//! \param[in] df    Pointer to the active DCL_DF22 controller structure
//!
_DCL_CODE_ACCESS
void DCL_forceUpdateDF22(DCL_DF22 *df)
{
    df->b0 = df->sps->b0;
    df->b1 = df->sps->b1;
    df->b2 = df->sps->b2;
    df->a1 = df->sps->a1;
    df->a2 = df->sps->a2;
}

//! \brief           Loads DF22 tuning parameter from its SPS parameter with interrupt protection
//!
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//!
_DCL_CODE_ACCESS
void DCL_updateDF22NoCheck(DCL_DF22 *df)
{
    dcl_interrupt_t ints;
    
    ints = DCL_disableInts();
    DCL_forceUpdateDF22(df);
    DCL_restoreInts(ints);
}

//! \brief           A conditional update based on the update flag.
//!                  If the update status is set, the function will update DF22
//!                  parameter from its SPS parameter and clear the status flag on completion.
//! \note            Note: Use DCL_setUpdateStatus(df) to set the update status.
//!     
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//! \return          'true' if an update is applied, otherwise 'false'
//!
_DCL_CODE_ACCESS
bool DCL_updateDF22(DCL_DF22 *df)
{
    if (DCL_setUpdateStatus(df))
    {
        DCL_updateDF22NoCheck(df);
        DCL_clearUpdateStatus(df);
        return true;
    }
    return false;
}

//! \brief           Determines stability of the shadow compensator
//!
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//! \return         'true' if both poles have magnitude less than 1, 'false' otherwise
//!
_DCL_CODE_ACCESS
bool DCL_isStableDF22(DCL_DF22 *df)
{
    return(DCL_isStablePn2(1.0f, df->sps->a1, df->sps->a2));
}

//! \brief            Loads the DF22 shadow coefficients from a ZPK3 description
//! \note             Note: Sampling period df->css->T are used in the calculation.
//!                   New settings take effect after DCL_updateDF22().
//!                   Only z1, z2, p1 & p2 are considered, z3 & p3 are ignored.
//!
//! \param[in] df     Pointer to the DCL_DF22 controller structure
//! \param[in] zpk    Pointer to the DCL_ZPK3 structure
//!
_DCL_CODE_ACCESS
void DCL_loadDF22asZPK(DCL_DF22 *df, DCL_ZPK3 *zpk)
{

#ifdef DCL_ERROR_HANDLING_ENABLED
    uint32_t err_code = dcl_none;
    err_code |= DCL_isZero(cimagf(zpk->z1) + cimagf(zpk->z2)) ? dcl_none : dcl_param_invalid_err;
    err_code |= DCL_isZero(cimagf(zpk->p1) + cimagf(zpk->p2)) ? dcl_none : dcl_param_invalid_err;
    if (err_code)
    {
        DCL_setError(df,err_code);
        DCL_getErrorInfo(df);
        DCL_runErrorHandler(df);
    }
#endif

    float32_t beta1 = -(float32_t) crealf(zpk->z1 + zpk->z2);
    float32_t beta0 = (float32_t) crealf(zpk->z1 * zpk->z2);
    float32_t alpha1 = -(float32_t) crealf(zpk->p1 + zpk->p2);
    float32_t alpha0 = (float32_t) crealf(zpk->p1 * zpk->p2);

    float32_t T = df->css->T;
    float32_t a0p = 4.0f + (alpha1 * 2.0f * T) + (alpha0 * T * T);

    df->sps->b0 = zpk->K * (4.0f + (beta1 * 2.0f * T) + (beta0 * T * T)) / a0p;
    df->sps->b1 = zpk->K * (-8.0f + (2.0f * beta0 * T * T)) / a0p;
    df->sps->b2 = zpk->K * (4.0f - (beta1 * 2.0f * T) + (beta0 * T * T)) / a0p;
    df->sps->a1 = (-8.0f + (2.0f * alpha0 * T * T)) / a0p;
    df->sps->a2 = (4.0f - (alpha1 * 2.0f * T) + (alpha0 * T * T)) / a0p;
}

//! \brief           Loads the DF22 shadow coefficients from damping ratio and un-damped
//!                  natural frequency using sample rate in CSS.
//! \note            Note: Sampling period df->css->T are used in the calculation.
//!                  New settings take effect after DCL_updateDF22().
//!
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//! \param[in] z     The damping ratio
//! \param[in] wn    The un-damped natural frequency in rad/s
//!
_DCL_CODE_ACCESS
void DCL_loadDF22asZwn(DCL_DF22 *df, float32_t z, float32_t wn)
{

#ifdef DCL_ERROR_HANDLING_ENABLED
    uint32_t err_code = dcl_none;
    err_code |= (z >= 0.0f) ? dcl_none : dcl_param_invalid_err;
    err_code |= (wn >= 0.0f) ? dcl_none : dcl_param_invalid_err;
    if (err_code)
    {
        DCL_setError(df,err_code);
        DCL_getErrorInfo(df);
        DCL_runErrorHandler(df);
    }
#endif

    float32_t T = df->css->T;
    float32_t v1 = wn * wn * T * T;
    float32_t a2p = 1.0f / (4.0f + (4.0f * z * wn * T) + v1);
    df->sps->b0 = v1 * a2p;
    df->sps->b1 = 2.0f * df->sps->b0;
    df->sps->b2 = df->sps->b0;
    df->sps->a1 = ((2.0f * v1) - 8.0f) * a2p;
    df->sps->a2 = (4.0f - (4.0f * z * wn * T) + v1) * a2p;
}

//! \brief           Loads the shadow DF22 compensator coefficients to emulate a series form PID.
//! \note            Note: Sampling period df->css->T are used in the calculation.
//!                  New settings take effect after DCL_updateDF22().
//!
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//! \param[in] Kp    Proportional gain
//! \param[in] Ki    Integral gain
//! \param[in] Kd    Derivative gain
//! \param[in] fc    Derivative path filter bandwidth in Hz
//!
_DCL_CODE_ACCESS
void DCL_loadDF22asSeriesPID(DCL_DF22 *df, float32_t Kp, float32_t Ki, float32_t Kd, float32_t fc)
{

#ifdef DCL_ERROR_HANDLING_ENABLED
    uint32_t err_code = dcl_none;
    err_code |= (Kp < 0.0f) ? dcl_param_range_err : dcl_none;
    err_code |= (Ki < 0.0f) ? dcl_param_range_err : dcl_none;
    err_code |= (Kd < 0.0f) ? dcl_param_range_err : dcl_none;
    err_code |= ((fc < 0.0f) || (fc > (1.0f / (2.0f * df->css->T)))) ? dcl_param_range_err : dcl_none;
    if (err_code)
    {
        DCL_setError(df,err_code);
        DCL_getErrorInfo(df);
        DCL_runErrorHandler(df);
    }
#endif

    float32_t T = df->css->T;
    float32_t tau = 1 / (2.0f * CONST_PI * fc);
    float32_t c1 = 2.0f / (T + (2.0f * tau));
    float32_t c2 = c1 * (T - (2.0f * tau)) / 2.0f;
    float32_t Kdp = Kd * c1;
    df->sps->b0 = Kp * (1 + Ki + Kdp);
    df->sps->b1 = Kp * (c2 - 1 + Ki*c2 - 2*Kdp);
    df->sps->b2 = Kp * (-c2 + Kdp);
    df->sps->a1 = c2 - 1;
    df->sps->a2 = -c2;
}

//! \brief           Loads the shadow DF22 compensator coefficients to emulate a parallel form PID.
//! \note            Note: Sampling period df->css->T are used in the calculation.
//!                  New settings take effect after DCL_updateDF22().
//!
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//! \param[in] Kp    Proportional gain
//! \param[in] Ki    Integral gain
//! \param[in] Kd    Derivative gain
//! \param[in] fc    Derivative path filter bandwidth in Hz
//!
_DCL_CODE_ACCESS
void DCL_loadDF22asParallelPID(DCL_DF22 *df, float32_t Kp, float32_t Ki, float32_t Kd, float32_t fc)
{

#ifdef DCL_ERROR_HANDLING_ENABLED
    uint32_t err_code = dcl_none;
    err_code |= (Kp < 0.0f) ? dcl_param_range_err : dcl_none;
    err_code |= (Ki < 0.0f) ? dcl_param_range_err : dcl_none;
    err_code |= (Kd < 0.0f) ? dcl_param_range_err : dcl_none;
    err_code |= (fc < 0.0f) ? dcl_param_range_err : dcl_none;
    err_code |= (fc > (1.0f / (2.0f * df->css->T))) ? dcl_param_warn_err : dcl_none;
    if (err_code)
    {
        DCL_setError(df,err_code);
        DCL_getErrorInfo(df);
        DCL_runErrorHandler(df);
    }
#endif

    float32_t T = df->css->T;
    float32_t tau = 1.0f / (2.0f * CONST_PI * fc);
    float32_t c1 = 2.0f / (T + (2.0f * tau));
    float32_t c2 = c1 * (T - (2.0f * tau)) / 2.0f;
    float32_t Kdp = Kd * c1;
    df->sps->b0 = Kp + Ki + Kdp;
    df->sps->b1 = (Kp * (c2 - 1)) + (Ki * c2) - (2.0f * Kdp);
    df->sps->b2 = (-c2 * Kp) + Kdp;
    df->sps->a1 = c2 - 1;
    df->sps->a2 = -c2;
}

//! \brief           Executes a 2nd order Direct Form 2 controller
//!                  
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//! \param[in] ek    The servo error
//! \return          The control effort
//!
_DCL_CRIT_ACCESS
float32_t DCL_runDF22(DCL_DF22 *df, float32_t ek)
{
    float32_t v7 = (ek * df->b0) + df->x1;
    df->x1 = (ek * df->b1) + df->x2 - (v7 * df->a1);
    df->x2 = (ek * df->b2) - (v7 * df->a2);

    return(v7);
}

//! \brief           Immediate computation to obtain DF22 servo error 
//!                  without updating the controller
//!
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//! \param[in] ek    The servo error
//! \return          The control effort
//!
_DCL_CRIT_ACCESS
float32_t DCL_runDF22PartialCompute(DCL_DF22 *df, float32_t ek)
{
    return((ek * df->b0) + df->x1);
}

//! \brief           Update DF22 controller based on pre-computed control effort
//!                  
//! \param[in] df    Pointer to the DCL_DF22 controller structure
//! \param[in] ek    The servo error
//! \param[in] uk    The controller output in the previous sample interval
//!
_DCL_CRIT_ACCESS
void DCL_runDF22PartialUpdate(DCL_DF22 *df, float32_t ek, float32_t uk)
{
    df->x1 = (ek * df->b1) + df->x2 - (uk * df->a1);
    df->x2 = (ek * df->b2) - (uk * df->a2);
}

//! \brief          Executes a 2nd order Direct Form 2 controller with clamp
//!                 
//! \param[in] df   Pointer to the DCL_DF22 controller structure
//! \param[in] ek   The servo error
//! \param[in] Umax Upper saturation limit
//! \param[in] Umin Lower saturation limit  
//! \return         The control effort
//!
_DCL_CRIT_ACCESS
float32_t DCL_runDF22Clamp(DCL_DF22 *df, float32_t ek, float32_t Umax, float32_t Umin)
{
    float32_t uk = DCL_runDF22PartialCompute(df, ek);
    bool is_clamped = DCL_runClamp(&uk, Umax, Umin);
    if(!is_clamped) DCL_runDF22PartialUpdate(df, ek, uk);
    return(uk);
}

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_DF22_H_
