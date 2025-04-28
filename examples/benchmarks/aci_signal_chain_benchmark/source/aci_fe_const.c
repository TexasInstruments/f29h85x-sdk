//#############################################################################
//
// FILE:   aci_fe_const.c
//
// TITLE:  ACI Motor Control Flux Estimator(FE) Constants.
//
//#############################################################################

//
// Included Files
//
#include "math.h"
#include "aci_fe_const.h"

//
// Calculate Flux Estimator(FE) output constants
//
void ACIFE_Const_calc(ACIFE_Const *v)
{	
   float Tr;
   
   //
   // Rotor time constant (sec)
   //
   Tr = v->Lr/v->Rr;

   v->K1 = Tr/(Tr+v->Ts); 
   v->K2 = v->Ts/(Tr+v->Ts); 
   v->K3 = v->Lm/v->Lr;
   v->K4 = (v->Ls*v->Lr-v->Lm*v->Lm)/(v->Lr*v->Lm);   
   v->K5 = v->Ib*v->Rs/v->Vb; 
   v->K6 = v->Vb*v->Ts/(v->Lm*v->Ib); 
   v->K7 = v->Lr/v->Lm;   
   v->K8 = (v->Ls*v->Lr-v->Lm*v->Lm)/(v->Lm*v->Lm);
   
}
