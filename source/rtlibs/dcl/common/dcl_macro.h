//#############################################################################
//
//
// $Copyright:
//#############################################################################
#ifndef _DCL_MACRO_H_
#define _DCL_MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif     

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *  
 *  \file       dcl_macro.h
 *  \brief      Defines all the auxiliary macros for DCL
 */

#ifndef NULL
#define NULL    0
#endif

//! \brief          Local definitions of the mathematical constant pi
//!
#define CONST_PI        3.14159265358979323846f
#define CONST_2PI       2.0f * CONST_PI
#define CONST_PI_F64    3.1415926535897932384626433832795028841971693993751058209749445923078164062L
#define CONST_2PI_F64   2.0L * CONST_PI_F64

//! \brief          Define the acceptable FPU numerical tolerances
//!
#define DCL_FPU32_TOL       1.0e-06f
#define DCL_FPU64_TOL       1.0e-10L

//! \brief          Define the default control period in seconds
//!
#define DCL_DEFAULT_PERIOD_S    100.0e-06f
#define DCL_DEFAULT_PERIODF64_S 100.0e-06L

//! \brief          Determines numerical proximity to specified value
//!
#define DCL_isValue(x,y)        ((float32_t) fabsf(x - y) < DCL_FPU32_TOL ? 1U : 0U)
#define DCL_isValueF64(x,y)     ((float64_t) fabs(x - y) < DCL_FPU64_TOL ? 1U : 0U)

//! \brief          Determines floating point numerical proximity to zero
//!
#define DCL_isZero(x)           DCL_isValue(x,0.0f)
#define DCL_isZeroF64(x)        DCL_isValueF64(x,0.0L)

//! \brief          Returns a random floating point result between -1.0 and +1.0
//!                 where 'a' is the multiplier in single or double precision. 
//!                 Useful for initialization of arrays and matrices during test.
//!
//! \code
//!                 float32_t s = DCL_rand(1.0f);
//! \endcode
#define DCL_rand(a)         (a * ((float32_t) rand() / (float32_t) (RAND_MAX >> 1) - 1.0f))
#define DCL_randF64(a)      (a * ((float64_t) rand() / (float64_t) (RAND_MAX >> 1) - 1.0L))

//! \brief          Defines the lower limit on derivative filter coefficient c2
//!                 in order for fc to lie below the Nyquist frequency
//!
#define DCL_c2Limit         ((2.0f - CONST_PI) / (2.0f + CONST_PI))
#define DCL_c2LimitF64      ((2.0L - CONST_PI_F64) / (2.0L + CONST_PI_F64))

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_MACRO_H_
