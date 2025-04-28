//#############################################################################
//
// FILE:   aci_fe_const.h
//
// TITLE:  ACI Motor Control Flux Estimator(FE) Constants.
//
//#############################################################################

#ifndef _ACI_FE_CONST_H
#define _ACI_FE_CONST_H

//
// Included Files
//
#include "parameter.h"

//
// Data structure for maintaining Flux estimator parameters
//
typedef struct
{ 
    float  Rs; 				//!< Input: Stator resistance (ohm) 
    float  Rr;				//!< Input: Rotor resistance (ohm) 
    float  Ls;				//!< Input: Stator inductance (H) 	  			      
    float  Lr;				//!< Input: Rotor inductance (H) 			
    float  Lm;				//!< Input: Magnetizing inductance (H) 
    float  Ib; 				//!< Input: Base phase current (amp) 
    float  Vb;				//!< Input: Base phase voltage (volt) 
    float  Ts;				//!< Input: Sampling period in sec   
    float  K1;				//!< Output: constant using in rotor flux calculation  
    float  K2;				//!< Output: constant using in rotor flux calculation  
    float  K3;				//!< Output: constant using in rotor flux calculation  
    float  K4;				//!< Output: constant using in stator current calculation  
    float  K5;				//!< Output: constant using in stator current calculation  
    float  K6;				//!< Output: constant using in stator current calculation  
    float  K7;				//!< Output: constant using in stator current calculation  
    float  K8;				//!< Output: constant using in torque calculation
} ACIFE_Const;
																																																																																																																																																																																																								

//
// Default initializer for the ACIFE_CONST object.
// These ACI parameters are based on WEG 1-hp induction motor
//
#define ACIFE_CONST_DEFAULTS {RS_VALUE, RR_VALUE, LS_VALUE, LR_VALUE, LM_VALUE, \
                             BASE_CURRENT, BASE_VOLTAGE, \
                             SAMPLING_PERIOD, \
 		          	         0,0,0,0,0,0,0,0, }

//
// Function Prototypes
//
void ACIFE_Const_calc(ACIFE_Const *);

#endif //_ACI_FE_CONST_H
