//#############################################################################
//
// FILE:   clarke.h
//
// TITLE:  Clarke Transform.
//
//#############################################################################

#ifndef _CLARKE_H
#define _CLARKE_H

//
// Included Files
//
#if defined (CLA_CPU)
#include "IQmathLib_cla.h"
#else
#include "math.h"
#include "IQmathLib.h"
#endif

//
// Clarke Transform Parameters for 3 phase stator current
//
typedef struct
{  
    _iq  As;          //!< Input: phase-a stator variable
    _iq  Bs;          //!< Input: phase-b stator variable
    _iq  Cs;          //!< Input: phase-c stator variable
    _iq  Alpha;       //!< Output: stationary d-axis stator variable
    _iq  Beta;        //!< Output: stationary q-axis stator variable
} CLARKE;

//
// Default initalizer for the CLARKE object.
//
#define CLARKE_DEFAULTS { 0.0F, \
                          0.0F, \
                          0.0F, \
                          0.0F, \
                          0.0F  }

//
// Constant
//

//
// 1/sqrt(3) = 0.57735026918963
//
#define INVSQRT3 _IQ(0.57735026918963F)

//
// Clarke transformation calculation
//
static inline void Clarke_calc(CLARKE* v)
{
    v->Alpha = v->As;
    v->Beta = _IQmpy((v->As +_IQmpy2(v->Bs)),_IQ(INVSQRT3));
}

#endif // _CLARKE_H
