//#############################################################################
//
// FILE:   ipark.h
//
// TITLE:  Inverse Park Transform.
//
//#############################################################################

#ifndef _IPARK_H
#define _IPARK_H

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
// Inverse Park Transformation Parameters
//
typedef struct
{  
	_iq  ds; 	 	 //!<Output: stationary d-axis stator variable
	_iq  qs;		 //!<Output: stationary q-axis stator variable
	_iq  ang;		 //!<Input: rotating angle (pu)
	_iq  de;		 //!<Input: rotating d-axis stator variable
	_iq  qe;		 //!<Input: rotating q-axis stator variable
} IPARK;	            

//
// Default initalizer for the IPARK object.
//
#define IPARK_DEFAULTS {  0.0F, \
                          0.0F, \
                          0.0F, \
                          0.0F, \
                          0.0F, \
					   }

//
// Constants
//
#define TWO_PI _IQ(6.28318530717959F)

//
// Inverse Park transform calculation
//

static inline void IPARK_calc(IPARK *v)
{	
    #if USE_FAST_TRIG_LIB == 1
    sincos_t sin_cos_ang;
    #else // Use TMU
    _iq cos_ang, sin_ang;
    #endif    
   
    #if USE_FAST_TRIG_LIB == 1
    FASTPUSinCos(&sin_cos_ang,v->ang);

    v->ds = (v->de * sin_cos_ang.c) - (v->qe * sin_cos_ang.s);
    v->qs = (v->qe * sin_cos_ang.c) + (v->de * sin_cos_ang.s);
    #else  // Use TMU
    //sin_ang = __sinpuf32(v->ang);
    //cos_ang = __cospuf32(v->ang);

    sin_ang = __builtin_c29_i32_pusinf32_m(v->ang);
    cos_ang = __builtin_c29_i32_pucosf32_m(v->ang);

    v->ds = _IQmpy(v->de,cos_ang) - _IQmpy(v->qe,sin_ang);
    v->qs = _IQmpy(v->qe,cos_ang) + _IQmpy(v->de,sin_ang);  
    #endif
}


#endif //_IPARK_H
