//#############################################################################
//
// FILE:   svgen.h
//
// TITLE:  Space Vector Generation
//
//#############################################################################

#ifndef _SVGEN_H
#define _SVGEN_H

//
// Include files
//
#include "stdint.h"

#if defined(CLA_OFFLOAD) || defined (CLA_CPU)
#ifdef __TMS320C28XX_CLA__
#include "IQmathLib_cla.h"
#endif
#else
#include "math.h"
#include "IQmathLib.h"
#endif

//
// SVGen Parameters
//
typedef struct  { 
      _iq  Ualpha;          //!< Input: reference alpha-axis phase voltage
      _iq  Ubeta;           //!< Input: reference beta-axis phase voltage
      _iq  Ta;              //!< Output: reference phase-a switching function
      _iq  Tb;              //!< Output: reference phase-b switching function
      _iq  Tc;              //!< Output: reference phase-c switching function
      _iq  tmp1;            //!< Variable: temp variable
      _iq  tmp2;            //!< Variable: temp variable
      _iq  tmp3;            //!< Variable: temp variable
      uint16_t VecSector;   //!< Space vector sector
} SVGEN;


//
// Default initalizer for the SVGEN object.
//

#define SVGEN_DEFAULTS { 0,0, \
                         0,0,0, \
                         0,0,0, \
                         0, \
                       }

//
// Space Vector  Generator (SVGEN) calculation
//
static inline void SVGEN_calc(SVGEN* v)
{
    v->tmp1= v->Ubeta;                                           
    v->tmp2= _IQdiv2(v->Ubeta) + (_IQmpy(_IQ(0.866F),v->Ualpha)); 
    v->tmp3= v->tmp2 - v->tmp1;                                  
                                                                 
    v->VecSector=3;                                              
    v->VecSector=(v->tmp2> 0)?( v->VecSector-1):v->VecSector;    
    v->VecSector=(v->tmp3> 0)?( v->VecSector-1):v->VecSector;    
    v->VecSector=(v->tmp1< 0)?(7-v->VecSector) :v->VecSector;    
                                                                 
    if(v->VecSector==1 || v->VecSector==4)                       
    {                                                            
        v->Ta= v->tmp2;                                          
        v->Tb= v->tmp1-v->tmp3;                                  
        v->Tc=-v->tmp2;                                          
    }                                                            
    else if(v->VecSector==2 || v->VecSector==5)                  
    {                                                            
        v->Ta= v->tmp3+v->tmp2;                                  
        v->Tb= v->tmp1;                                          
        v->Tc=-v->tmp1;                                          
    }                                                            
    else                                                         
    {                                                            
        v->Ta= v->tmp3;                                          
        v->Tb=-v->tmp3;
        v->Tc=-(v->tmp1+v->tmp2);                                
    }                                                            
}

/*static inline void SVGEN_calc(SVGEN* v)
{
    float Ubeta = v->Ubeta;
    float Ualpha = v->Ualpha;
    float ScaledUbeta = Ubeta * 0.5f;
    float ScaledUalpha = Ualpha * 0.866f;
    v->tmp1 = Ubeta;
    v->tmp2 = ScaledUbeta + ScaledUalpha;
    v->tmp3 = v->tmp2 - v->tmp1;

    unsigned int index;
    (void)__builtin_c29_quadf32(&index, &ScaledUbeta, &ScaledUalpha);

    float Ta, Tb, Tc;
    int VecSector;
    switch(index) {
      default:
        __builtin_unreachable();
        return;

      case 0:
      case 1:
      case 8:
      case 9:
        Ta = v->tmp2;
        Tb = v->tmp1 - v->tmp3;
        Tc = -v->tmp2;
        VecSector = (index < 8 ? 1 : 4);
        break;

      case 2:
      case 3:
      case 4:
      case 5:
      case 10:
      case 11:
      case 12:
      case 13:
        Ta = v->tmp3 + v->tmp2;
        Tb = v->tmp1;
        Tc = -v->tmp1;
        VecSector = (index < 8 ? 2 : 5);
        break;

      case 6:
      case 7:
      case 14:
      case 15:
        Ta = v->tmp3;
        Tb = -v->tmp3;
        Tc = -(v->tmp1 + v->tmp2);
        VecSector = (index < 8 ? 3 : 6);
        break;
    }
    v->Ta = Ta;
    v->Tb = Tb;
    v->Tc = Tc;
    v->VecSector = VecSector; 
}*/

#endif // _SVGEN_H
