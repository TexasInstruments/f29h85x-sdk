//#############################################################################
//
// FILE:   clarke.h
//
// TITLE:  Inverse Clarke Transform.
//
//#############################################################################

#ifndef _ICLARKE_H
#define _ICLARKE_H

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
    _iq  Alpha;       //!< Input: stationary d-axis stator variable
    _iq  Beta;        //!< Input: stationary q-axis stator variable
    _iq  As;          //!< Output: phase-a stator variable
    _iq  Bs;          //!< Output: phase-b stator variable
    _iq  Cs;          //!< Output: phase-c stator variable
} ICLARKE;

//
//    Default initalizer for the CLARKE object.
//
#define ICLARKE_DEFAULTS { 0.0F, \
                          0.0F, \
                          0.0F, \
                          0.0F, \
                          0.0F }

//
// Constant
//
#define SQRT3 _IQ(1.732050808F)

//
// Inverse Clarke transformation calculation
//
static inline void IClarke_calc(ICLARKE* v)
{
    v->As = v->Alpha;
    v->Bs = _IQmpy((-v->Alpha + _IQmpy(v->Beta, SQRT3)), 0.5F);
    v->Cs = _IQmpy((-v->Alpha - _IQmpy(v->Beta, SQRT3)), 0.5F);
}


#endif // _ICLARKE_H
