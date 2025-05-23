//#############################################################################
//
//
// $Copyright:
//#############################################################################
#ifndef _DCL_ZPK3_H_
#define _DCL_ZPK3_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  
 *  @{
 *  \file       dcl_zpk3.h
 *  \brief      Defines ZPK3 strcture that represents 
 *              a third order transfer function of poles and zeros
 */              

#include <complex.h>

//--- ZPK3 structure ---------------------------------------------------------

//! \brief          Defines the DCL_ZPK3 structure.
//!
//! \details        Allows controllers to be defined in terms of complex pole
//!                 and zero frequencies.  The common structure consists of
//!                 three complex zeros, three complex poles, and a real gain.
//!                 All frequencies must be specified in radians/sec.
//!
typedef struct dcl_zpk3 
{
    float complex z1;   //!< Complex zeros 1
    float complex z2;   //!< Complex zeros 2
    float complex z3;   //!< Complex zeros 3
    float complex p1;   //!< Complex poles 1
    float complex p2;   //!< Complex poles 2
    float complex p3;   //!< Complex poles 3
    float32_t K;        //!< Real gain
} DCL_ZPK3;

//! \brief          Defines default values to initialize the DCL_ZPK3 structure
//!
#define ZPK3_DEFAULTS { 0.0f + 0.0f*I, 0.0f + 0.0f*I, 0.0f + 0.0f*I, \
                        0.0f + 0.0f*I, 0.0f + 0.0f*I, 0.0f + 0.0f*I, \
                        1.0f }

//! \brief          Defines the 64bit ZPK3 structure.
//!
typedef struct dcl_zpk3f64
{
    double complex z1;   //!< Complex zeros 1
    double complex z2;   //!< Complex zeros 2
    double complex z3;   //!< Complex zeros 3
    double complex p1;   //!< Complex poles 1
    double complex p2;   //!< Complex poles 2
    double complex p3;   //!< Complex poles 3
    float64_t K;         //!< Real gain
} DCL_ZPK3F64;

//! \brief          Defines default values to initialize the DCL_ZPK3F64 structure
//!
#define ZPK3F64_DEFAULTS { 0.0L + 0.0L*I, 0.0L + 0.0L*I, 0.0L + 0.0L*I, \
                        0.0L + 0.0L*I, 0.0L + 0.0L*I, 0.0L + 0.0L*I, \
                        1.0L }                        

//! \brief         Determines stability of a ZPK3 representation by checking pole magnitude
//!
_DCL_CODE_ACCESS
bool DCL_isStableZpk3(DCL_ZPK3 *q)
{
    return((cabsf(q->p1) < 1.0f) && (cabsf(q->p2) < 1.0f) && (cabsf(q->p3) < 1.0f));
}

//! \brief         Determines stability of a ZPK3F64 representation by checking pole magnitude
//!
_DCL_CODE_ACCESS
bool DCL_isStableZpk3F64(DCL_ZPK3 *q)
{
    return((cabs(q->p1) < 1.0L) && (cabs(q->p2) < 1.0L) && (cabs(q->p3) < 1.0L));
}

//  \brief          All ZPK functions exist in its respective controller conversion type
//                  All the ZPK conversion function prototypes are listed below
/*
//! \brief          Loads the DF11 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF11()
//!                 Only real z1 & p1 considered: all other roots ignored
//!                 Located in df/dcl_df11.h
extern void DCL_loadDF11asZPK(DCL_DF11 *p, DCL_ZPK3 *q);

//! \brief          Loads the DF12 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF12()
//!                 Only z1, z2, p1 & p2 considered: z3 & p3 ignored
//!                 Located in df/dcl_df12.h
extern void DCL_loadDF12asZPK(DCL_DF12 *p, DCL_ZPK3 *q);

//! \brief          Loads the DF13 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF13()
//!                 Located in df/dcl_df13.h
extern void DCL_loadDF13asZPK(DCL_DF13 *p, DCL_ZPK3 *q);

//! \brief          Loads the DF22 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF22()
//!                 Only z1, z2, p1 & p2 considered: z3 & p3 ignored
//!                 Located in df/dcl_df22.h
extern void DCL_loadDF22asZPK(DCL_DF22 *p, DCL_ZPK3 *q);

//! \brief          Loads the DF23 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF23()
//!                 Located in df/dcl_df23.h
extern void DCL_loadDF23asZPK(DCL_DF23 *p, DCL_ZPK3 *q);

//! \brief          Configures a series PI controller in "zero-pole-gain" form
//!                 Note: new settings take effect after DCL_updatePI()
//!                 Only z1 considered in DCL_ZPK3, other poles & zeros ignored
//!                 Zero frequency assumed to be in radians/sec.
//!                 Located in pi/dcl_pi.h
extern void DCL_loadSeriesPIasZPK(DCL_PI *p, DCL_ZPK3 *q);

//! \brief          Configures a parallel PI controller in "zero-pole-gain" form
//!                 Note: new settings take effect after DCL_updatePI()
//!                 Zero frequency assumed to be in radians/sec.
//!                 Located in pi/dcl_pi.h
extern void DCL_loadParallelPIasZPK(DCL_PI *p, DCL_ZPK3 *q);

//! \brief          Configures a series PID controller in ZPK form
//!                 Note: parameters take effect after call to DCL_updatePID()
//!                 Only z1, z2 & p2 considered.  p1 = 0 assumed.
//!                 Located in pid/dcl_pid.h
extern void DCL_loadSeriesPIDasZPK(DCL_PID *p, DCL_ZPK3 *q);

//! \brief          Configures a parallel PID controller in ZPK form
//!                 Note: parameters take effect after call to DCL_updatePID()
//!                 Only z1, z2 & p2 considered.  p1 = 0 assumed.
//!                 Located in pid/dcl_pid.h
extern void DCL_loadParallelPIDasZPK(DCL_PID *p, DCL_ZPK3 *q);

//! \brief          Configures a series PID controller in ZPK form
//!                 Note: parameters take effect after call to DCL_updatePIDF64()
//!                 Only z1, z2 & p2 considered.  p1 = 0 assumed.
//!                 Located in pid/dcl_pidf64.h
extern void DCL_loadSeriesPIDF64asZPK(DCL_PIDF64 *p, DCL_ZPK3 *q);

//! \brief          Configures a parallel PID controller in ZPK form
//!                 Note: parameters take effect after call to DCL_updatePIDF64()
//!                 Only z1, z2 & p2 considered.  p1 = 0 assumed.
//!                 Located in pid/dcl_pidf64.h
extern void DCL_loadParallelPIDF64asZPK(DCL_PIDF64 *p, DCL_ZPK3F64 *q);
*/

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_ZPK3_H_
