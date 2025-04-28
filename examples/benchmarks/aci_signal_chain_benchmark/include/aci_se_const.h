//#############################################################################
//
// FILE:   aci_se_const.h
//
// TITLE:  ACI Motor Control Speed Estimator(SE) Constants.
//
//#############################################################################

#ifndef _ACI_SE_CONST_H
#define _ACI_SE_CONST_H

//
// Included Files
//
#include "parameter.h"

//
// Data structure for maintaining Speed estimator parameters
//
typedef struct 	{ 
	float  Rr;		  //!< Input: Rotor resistance (ohm) 
	float  Lr;		  //!< Input: Rotor inductance (H) 
	float  fb;        //!< Input: Base electrical frequency (Hz) 
	float  fc;        //!< Input: Cut-off frequency of lowpass filter (Hz) 
	float  Ts;		  //!< Input: Sampling period in sec  
	float  K1;		  //!< Output: constant using in rotor flux calculation  
	float  K2;		  //!< Output: constant using in rotor flux calculation  
	float  K3;		  //!< Output: constant using in rotor flux calculation  
	float  K4;		  //!< Output: constant using in stator current calculation
} ACISE_Const;
																																																																																																																																																																																																								
//
// Default initializer for the ACISE_CONST object
// These ACI parameters are based on WEG 1-hp induction motor
//
#define ACISE_CONST_DEFAULTS {RR_VALUE, LR_VALUE, \
                             BASE_FREQ, 200, SAMPLING_PERIOD, \
 		          	         0,0,0,0, }

//
// Function prototypes
//
void ACISE_Const_calc(ACISE_Const *);

#endif //_ACI_SE_CONT_H
