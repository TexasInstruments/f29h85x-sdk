//#############################################################################
//
// FILE:   aci_const.c
//
// TITLE:  ACI Motor Control Model Output Constants.
//
//#############################################################################

//
// Included Files
//
#include "math.h"
#include "aci_const.h"

//
// Calculate the ACI motor output constants
//
void ACI_Const_calc(ACI_Const *v)
{	
	float sigma,gamma,alpha,beta;
	
	sigma = 1 - (v->Lm*v->Lm)/(v->Ls*v->Lr);
	gamma = (v->Lm*v->Lm*v->Rr + v->Lr*v->Lr*v->Rs)/(sigma*v->Ls*v->Lr*v->Lr);
	alpha = v->Rr/v->Lr;
	beta = v->Lm/(sigma*v->Ls*v->Lr);
	
    v->K1 = v->Ts*alpha;
    v->K2 = v->Ts*v->Wb;
    v->K3 = v->Ts*alpha*v->Lm*(v->Ib/v->Lb);  
    v->K4 = v->Ts*alpha*beta*(v->Lb/v->Ib);
    v->K5 = v->Ts*beta*(v->Lb*v->Wb/v->Ib);
    v->K6 = v->Ts*gamma;  
    v->K7 = v->Ts*(1/(sigma*v->Ls))*(v->Vb/v->Ib);
    v->K8 = 1.5F*(v->p/2)*(v->Lm/v->Lr)*(v->Lb*v->Ib/v->Tb);
    v->K9 = v->Ts*(v->B/v->J);  
    v->K10 = v->Ts*(v->p/2)*(1/v->J)*(v->Tb/v->Wb);   
}

//
// End of File
//
