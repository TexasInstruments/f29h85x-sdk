//#############################################################################
//
// FILE:   aci_se_const.c
//
// TITLE:  ACI Motor Control Speed Estimator(SE) Constants.
//
//#############################################################################

//
// Included Files
//
#include "math.h"
#include "aci_se_const.h"

#define PI 3.14159265358979

//
// Calculate Speed Estimator(FE) output constants
//
void ACISE_Const_calc(ACISE_Const *v)
{	
   float Wb, Tr, tc;
   
   //
   // Rotor time constant (sec)
   //
   Tr = v->Lr/v->Rr;

   //
   // Lowpass filter time constant (sec)
   //
   tc = 1/(2*PI*v->fc);
   Wb = 2*PI*v->fb;
   
   v->K1 = 1/(Wb*Tr); 
   v->K2 = 1/(v->fb*v->Ts);  
   v->K3 = tc/(tc+v->Ts);
   v->K4 = v->Ts/(tc+v->Ts);   

}


