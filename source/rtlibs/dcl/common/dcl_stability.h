//#############################################################################
//
//
// $Copyright:
//############################################################################# 
#ifndef _DCL_STABILITY_H_
#define _DCL_STABILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \addtogroup DCL_API_MODULE APIs for Digital Control Library
 *  @{
 *  
 *  \file       dcl_stability.h
 *  \brief      Defines polynomial stability functions
 */

//--- Polynomial stability functions -----------------------------------------

//! \brief          Determines stability of a first order real polynomial
//!                 P(z) = z + a1
//!
//! \param[in] a1   Coefficient a1
//! \return         'true' if the root has magnitude less than 1, 'false' otherwise
//!
_DCL_CODE_ACCESS
bool DCL_isStablePn1(float32_t a1)
{
    return ((a1 * a1) < 1.0f);
}

//! \brief          Determines stability of a second order polynomial with real coefficients
//!                 P(z) = a0 z^2 + a1 z + a2
//!
//! \param[in] a0   Second order coefficient a1
//! \param[in] a1   First order coefficient a1
//! \param[in] a2   Coefficient a2
//! \return         'true' if both roots have magnitude less than 1, 'false' otherwise
//!
_DCL_CODE_ACCESS
bool DCL_isStablePn2(float32_t a0, float32_t a1, float32_t a2)
{
    float32_t b0, b1, c0;

    b0 = a0 - a2 * a2 / a0;
    b1 = a1 - a1 * a2 / a0;
    c0 = b0 - b1 * b1 / b0;

    return ((a0 > 0.0f) && (b0 > 0.0f) && (c0 > 0.0f));
}

//! \brief          Determines stability of a third order polynomial with real coefficients
//!                 P(z) = a0 z^3 + a1 z^2 + a2 z + a3
//!
//! \param[in] a0   Third order coefficient a1
//! \param[in] a1   Second order coefficient a1
//! \param[in] a2   First order coefficient a2
//! \param[in] a3   Coefficient a3
//! \return         'true' if all roots have magnitude less than 1, 'false' otherwise
//!
_DCL_CODE_ACCESS
bool DCL_isStablePn3(float32_t a0, float32_t a1, float32_t a2, float32_t a3)
{
    float32_t b0, b1, b2, c0, c1, d0;

    b0 = a0 - a3 * a3 / a0;
    b1 = a1 - a2 * a3 / a0;
    b2 = a2 - a1 * a3 / a0;
    c0 = b0 - b2 * b2 / b0;
    c1 = b1 - b1 * b2 / b0;
    d0 = c0 - c1 * c1 / c0;

    return ((a0 > 0.0f) && (b0 > 0.0f) && (c0 > 0.0f) && (d0 > 0.0f));
}

/*
//! \brief         Determines stability of a ZPK3 representation by checking pole magnitude
//!                Located in common/dcl_zpk3.h
extern bool DCL_isStableZpk3(DCL_ZPK3 *q);
*/

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_STABILITY_H_
