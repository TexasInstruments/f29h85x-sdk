//#############################################################################
//
//
// $Copyright:
//#############################################################################

#ifndef _DCL_DF11_H_
#define _DCL_DF11_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *
 *  \file       dcl_df11.h
 *  \brief      Contains direct form 1 1st order DF11 compensator
 *              with its related structures and functions
 */                 

#include "../dcl_common.h"

//--- Direct Form 1 - 1st order ----------------------------------------------

//! \brief          Defines DCL_DF11 shadow parameter set
//!                 used for updating compensator parameter
//!
typedef struct dcl_df11_sps
{
    float32_t b0;   //!< pos. coefficient to e(k)
    float32_t b1;   //!< pos. coefficient to e(k-1)
    float32_t a1;   //!< neg. coefficient to u(k-1)
} DCL_DF11_SPS;

#define DF11_SPS_DEFAULTS { 0.5f, 0.5f, 1.0f }

//! \brief          DCL_DF11 object for storing df11 specific parameters
//!
typedef _DCL_VOLATILE struct dcl_df11
{
    /* compensator parameter */
    float32_t b0;   //!< pos. coefficient to e(k)
    float32_t b1;   //!< pos. coefficient to e(k-1)
    float32_t a1;   //!< neg. coefficient to u(k-1)

    /* internal storage */
    float32_t d1;   //!< e(k-1)
    float32_t d2;   //!< u(k-1)

    /* miscellaneous */
    DCL_DF11_SPS *sps; //!< Pointer to the shadow parameter set
    DCL_CSS *css;      //!< Pointer to the common support structure
} DCL_DF11;

//! \brief          Defines default values to initialize DCL_DF11
//!
#define DF11_DEFAULTS { 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, \
        &(DCL_DF11_SPS)DF11_SPS_DEFAULTS, &(DCL_CSS)DCL_CSS_DEFAULTS }

//! \brief          Macro for internal default values to initialize DCL_DF11
//!                 Example: DCL_DF11 df11_ctrl = { 
//!                                             .b0 = 0.5f,
//!                                             .b1 = 0.5f,
//!                                             .a1 = 1.0f,
//!                                             DF11_INT_DEFAULTS
//!                                           };
#define DF11_INT_DEFAULTS .d1=0.0f, .d2=0.0f, .sps=&(DCL_DF11_SPS)DF11_SPS_DEFAULTS, .css=&(DCL_CSS)DCL_CSS_DEFAULTS 

//! \brief          Initialize DCL_DF11 struct with default parameters
//!                 Example: DCL_DF11* df11_ctrl = DCL_initDF11();
//!
//! \return         A DCL_DF11* pointer
//!
#define DCL_initDF11() &(DCL_DF11)DF11_DEFAULTS

//! \brief          Initialize DCL_DF11 struct with input compensator parameters
//!                 Example: DCL_DF11* DF11_ctrl = DCL_initDF11asParam(0.5f,0.5f,1.0f);
//! \note           Note: input parameter needs to be in the same order as listed in DF11_SPS struct
//!
//! \return         A DCL_DF11* pointer
//!
#define DCL_initDF11asParam(_b0,_b1,_a1) &(DCL_DF11){ .b0=_b0, .b1=_b1, .a1=_a1, \
                                DF11_INT_DEFAULTS }

//! \brief                  Initialize DCL_DF11 struct with sps parameters
//!                         Example: DCL_DF11_SPS df_sps = { .b0 = , .b1 = , ...}; //initial parameter
//!                                  DCL_DF11 df_ctrl;
//!                                  DCL_initDF11asSPS(&df_ctrl,&df_sps);
//!
//! \param[in] df_ptr       DCL_DF11* pointer that needs to be initialized
//! \param[in] sps_ptr      DCL_DF11_SPS* pointer with assigned parameters
//! \return    DCL_DF11*    Returns DCL_DF11* with set sps parameters, default parameter will be used
//!                         if sps_ptr is not specified   
//!
#define DCL_initDF11asSPS(df_ptr,sps_ptr)                                          \
({                                                                                 \
    DCL_DF11* new_df = (df_ptr) ? df_ptr : DCL_initDF11();                         \
    DCL_DF11_SPS* new_sps = (sps_ptr) ? sps_ptr : &(DCL_DF11_SPS)DF11_SPS_DEFAULTS;\
    if(sps_ptr)                                                                    \
    {                                                                              \
        *new_df = (DCL_DF11){ (new_sps)->b0, (new_sps)->b1, (new_sps)->a1,         \
        0.0f, 0.0f, (DCL_DF11_SPS*)new_sps, &(DCL_CSS)DCL_CSS_DEFAULTS };          \
    }                                                                              \
    new_df;                                                                        \
})

//! \brief           Resets DF11 internal storage data with interrupt protection
//!
//! \param[in] df    Pointer to the DCL_DF11 structure
//!
_DCL_CODE_ACCESS
void DCL_resetDF11(DCL_DF11 *df)
{
    dcl_interrupt_t ints;

    ints = DCL_disableInts();
    df->d1 = df->d2 = 0.0f;
    DCL_restoreInts(ints);
}

//! \brief           Loads DF11 tuning parameter from its SPS parameter without interrupt protection
//!
//! \param[in] df    Pointer to the active DCL_DF11 controller structure
//!
_DCL_CODE_ACCESS
void DCL_forceUpdateDF11(DCL_DF11 *df)
{
    df->b0 = df->sps->b0;
    df->b1 = df->sps->b1;
    df->a1 = df->sps->a1;
}

//! \brief           Loads DF11 tuning parameter from its SPS parameter with interrupt protection
//!
//! \param[in] df    Pointer to the DCL_DF11 controller structure
//!
_DCL_CODE_ACCESS
void DCL_updateDF11NoCheck(DCL_DF11 *df)
{
    dcl_interrupt_t ints;
    
    ints = DCL_disableInts();
    DCL_forceUpdateDF11(df);
    DCL_restoreInts(ints);
}

//! \brief           A conditional update based on the update flag.
//!                  If the update status is set, the function will update DF11
//!                  parameter from its SPS parameter and clear the status flag on completion.
//! \note            Note: Use DCL_setUpdateStatus(df) to set the update status.
//!     
//! \param[in] df    Pointer to the DCL_DF11 controller structure
//! \return          'true' if an update is applied, otherwise 'false'
//!
_DCL_CODE_ACCESS
bool DCL_updateDF11(DCL_DF11 *df)
{
    if (DCL_getUpdateStatus(df))
    {
        DCL_updateDF11NoCheck(df);
        DCL_clearUpdateStatus(df);
        return true;
    }
    return false;
}

//! \brief           Determines stability of the shadow DF11 compensator
//!
//! \param[in] df    Pointer to the DCL_DF11 controller structure
//! \return         'true' if the pole has magnitude less than 1, 'false' otherwise
//!
_DCL_CODE_ACCESS
bool DCL_isStableDF11(DCL_DF11 *df)
{
    return(DCL_isStablePn1(df->sps->a1));
}

//! \brief            Loads the DF11 shadow coefficients from a ZPK3 description
//! \note             Note: Sampling period df->css->T are used in the calculation.
//!                   New settings take effect after DCL_updateDF11().
//!                   Only real z1 & p1 considered, all other roots ignored.
//!
//! \param[in] df     Pointer to the DCL_DF11 controller structure
//! \param[in] zpk    Pointer to the ZPK3 structure
//!
_DCL_CODE_ACCESS
void DCL_loadDF11asZPK(DCL_DF11 *df, DCL_ZPK3 *zpk)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    uint32_t err_code = dcl_none;
    err_code |= DCL_isZero(cimagf(zpk->z1)) ? dcl_none : dcl_param_warn_err;
    err_code |= DCL_isZero(cimagf(zpk->p1)) ? dcl_none : dcl_param_warn_err;
    if (err_code)
    {
        DCL_setError(df,err_code);
        DCL_getErrorInfo(df);
        DCL_runErrorHandler(df);
    }
#endif

    float32_t T = df->css->T;
    float32_t a0p = 2.0f - (float32_t) crealf(zpk->p1) * T;
    df->sps->b0 = zpk->K * (2.0f - (float32_t) crealf(zpk->z1) * T) / a0p;
    df->sps->b1 = zpk->K * (-2.0f - (float32_t) crealf(zpk->z1) * T) / a0p;
    df->sps->a1 = (-2.0f - (float32_t) crealf(zpk->p1) * T) / a0p;
}

//! \brief           Loads compensator coefficients to emulate series form PI
//! \note            Note: Sampling period df->css->T are used in the calculation.
//!                  New settings take effect after DCL_updateDF11().
//!
//! \param[in] df    Pointer to the DCL_DF11 controller structure
//! \param[in] Kp    Proportional gain
//! \param[in] Ki    Integral gain
//!
_DCL_CODE_ACCESS
void DCL_loadDF11asPI(DCL_DF11 *df, float32_t Kp, float32_t Ki)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    uint32_t err_code = dcl_none;
    err_code |= (Kp < 0.0f) ? dcl_param_invalid_err : dcl_none;
    err_code |= (Ki < 0.0f) ? dcl_param_invalid_err : dcl_none;
    if (err_code)
    {
        DCL_setError(df,err_code);
        DCL_getErrorInfo(df);
        DCL_runErrorHandler(df);
    }
#endif

    float32_t T = df->css->T;
    df->sps->b0 = Kp * ((Ki * T) + 2.0f) / 2.0f;
    df->sps->b1 = Kp * ((Ki * T) - 2.0f) / 2.0f;
    df->sps->a1 = -1.0f;
}

//! \brief           Executes a 1st order Direct Form 1 controller
//!                  
//! \param[in] df    Pointer to the DCL_DF11 controller structure
//! \param[in] ek    The servo error
//! \return    uk    The control effort
//!
_DCL_CRIT_ACCESS 
float32_t DCL_runDF11(DCL_DF11 *df, float32_t ek)
{
    df->d2 = (ek * df->b0) + (df->d1 * df->b1) - (df->d2 * df->a1);
    df->d1 = ek;

    return(df->d2);
}

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_DF11_H_
