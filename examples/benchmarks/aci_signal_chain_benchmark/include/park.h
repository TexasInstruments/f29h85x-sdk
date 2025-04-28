//#############################################################################
//
// FILE:   park.h
//
// TITLE:  Park Transform.
//
//#############################################################################

#ifndef _PARK_H
#define _PARK_H

#if defined (CLA_CPU)
#include "IQmathLib_cla.h"
#else
#include "math.h"
#include "IQmathLib.h"
#endif

#if USE_FAST_TRIG_LIB == 1
#include "FastFPUTrigLib.h"
#endif

#include "device.h"

//
// Park Transformation Parameters
//
typedef struct
{
	_iq  ds;  		    //!< Input: stationary d-axis stator variable */
	_iq  qs;		    //!< Input: stationary q-axis stator variable */
	_iq  ang;			//!< Input: rotating angle (pu) */
	_iq  de;			//!< Output: rotating d-axis stator variable */
	_iq  qe;			//!< Output: rotating q-axis stator variable */
} PARK;	            


//
// Default initalizer for the PARK object.
//
#define PARK_DEFAULTS {   0.0F, \
                          0.0F, \
                          0.0F, \
                          0.0F, \
                          0.0F, \
                      }

//
// Constants
//
#define TWO_PI    _IQ(6.28318530717959F)

//
// Park transform calculation
//

static inline void PARK_calc(PARK* v)
{	
    #if USE_FAST_TRIG_LIB == 1
    sincos_t sin_cos_ang;
    #else // Use TMU
    _iq cos_ang, sin_ang;
    #endif
    
    #if USE_FAST_TRIG_LIB == 1
    FASTPUSinCos(&sin_cos_ang,v->ang);

    v->de = (v->ds * sin_cos_ang.c) + (v->qs * sin_cos_ang.s);
    v->qe = (v->qs * sin_cos_ang.c) - (v->ds * sin_cos_ang.s);
    #else // Use TMU

    sin_ang = __builtin_c29_i32_pusinf32_m(v->ang);
    cos_ang = __builtin_c29_i32_pucosf32_m(v->ang);

    v->de = _IQmpy(v->ds,cos_ang) + _IQmpy(v->qs,sin_ang);
    v->qe = _IQmpy(v->qs,cos_ang) - _IQmpy(v->ds,sin_ang);
    #endif
}


#endif //_PARK_H
