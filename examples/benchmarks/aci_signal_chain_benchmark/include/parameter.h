
//#############################################################################
//
// FILE:   parameter.h
//
// TITLE:  Parameters
//
//#############################################################################

#ifndef _PARAMETER_H
#define _PARAMETER_H

/**
 * @brief Define the samping period for simulation (sec) 
 * 
 */
#define SAMPLING_PERIOD 0.0005

/**
 * @brief Define the Induction motor parameters 
 * 
 */
#define RS_VALUE 	1.723               //!< Stator resistance (ohm)
#define RR_VALUE   	2.011               //!< Rotor resistance (ohm)
#define LS_VALUE   	0.166619     		//!< Stator inductance (H)
#define LR_VALUE   	0.168964			//!< Rotor inductance (H)
#define LM_VALUE   	0.159232			//!< Rotor inductance (H)
#define P_VALUE    	4					//!< Number of poles

/**
 * @brief Define the mechanical parameters 
 * 
 */
#define BB_VALUE	0.0001     			//!< Damping coefficient (N.m.sec/rad)
#define JJ_VALUE	0.001				//!< Moment of inertia of rotor mass (kg.m^2)
#define TL_VALUE    0    				//!< Load torque (N.m)

/**
 * @brief Define the base quantites 
 * 
 */
#define BASE_VOLTAGE    184.752       //!< Base peak phase voltage (volt)
#define BASE_CURRENT    5             //!< Base peak phase current (amp)
#define BASE_TORQUE     7.35105194    //!< Base torque (N.m)
#define BASE_FLUX       0.79616       //!< Base flux linkage (volt.sec/rad)
#define BASE_FREQ      	60            //!< Base electrical frequency (Hz)


extern void aci_ctrlLoop(void);

#endif  // _PARAMETER.H
