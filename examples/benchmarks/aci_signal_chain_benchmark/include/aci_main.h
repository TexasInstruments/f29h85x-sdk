//#############################################################################
//
// FILE:   aci_main.h
//
// TITLE:  ACI Motor Control Benchmark Application
//
//#############################################################################

#ifndef _ACI_MAIN_H
#define _ACI_MAIN_H

#define MATH_TYPE FLOAT_MATH

//
// Include files
//
#include "aci.h"        	//!< Include header for the ACI object
#include "aci_const.h"      //!< Include header for the ACI_CONST object
#include "aci_fe.h"        	//!< Include header for the ACIFE object
#include "aci_fe_const.h"   //!< Include header for the ACIFE_Const object
#include "aci_se.h"        	//!< Include header for the ACISE object
#include "aci_se_const.h"   //!< Include header for the ACISE_Const object
#include "park.h"       	//!< Include header for the PARK object
#include "ipark.h"       	//!< Include header for the IPARK object
#include "pid_reg3.h"       //!< Include header for the PIDREG3 object
#include "clarke.h"         //!< Include header for the CLARKE object
#include "iclarke.h"        //!< Include header for the ICLARKE object
#include "svgen.h"          //!< Include header for the SVGEN object

#include "bitfield_structs.h"

//
// Defines
//

//#ifdef CLA_CPU
//
// CLA can only access LS and Message RAMs.
// Reducing the number of log samples saved to be able to fit application
// in CLA accessible memory.
//
//#define DLOG_NUMBER_SAMPLES  800
//#else
//
//
#define DLOG_NUMBER_SAMPLES  1024
//#endif

#define Ia_ADJUST_FACTOR 1000
#define Ia_ADJUST_BASELINE 2700
//#define Ia_ADJUST_FACTOR 250
//#define Ia_ADJUST_BASELINE 520

#define ADJUST_Ia_OUTPUT(x) ( ((x) * Ia_ADJUST_FACTOR) + Ia_ADJUST_BASELINE )
#define ADJUST_Ia_INPUT(x)  ( (x - Ia_ADJUST_BASELINE) / Ia_ADJUST_FACTOR )

#define Ib_ADJUST_FACTOR 500
#define Ib_ADJUST_BASELINE 1500
//#define Ib_ADJUST_FACTOR 125
//#define Ib_ADJUST_BASELINE 250

#define ADJUST_Ib_OUTPUT(x) ( ((x) * Ib_ADJUST_FACTOR) + Ib_ADJUST_BASELINE )
#define ADJUST_Ib_INPUT(x)  ( (x - Ib_ADJUST_BASELINE) / Ib_ADJUST_FACTOR )

#define ADC_SAMPLE_PERIOD (DEVICE_SYSCLK_FREQ * SAMPLING_PERIOD)

#define ADC_SAMPLE_CYCLE_COUNT (15+1)

uint32_t PWM_PERIOD_MAX = ADC_SAMPLE_PERIOD/2;

uint32_t PWM_HALF_MAX = ADC_SAMPLE_PERIOD/4;




//
// Bitfield datastructure definition
//
struct ADC_RESULT_REGS AdcaResult;

//*****************************************************************************
//
// ADC functions
//
//*****************************************************************************

//
// ADC read functions
//
__attribute__((always_inline)) inline uint16_t ADC_getIa()
{
    return AdcaResult.ADCRESULT0;
}


__attribute__((always_inline)) inline uint16_t ADC_getIb()
{
    return AdcaResult.ADCRESULT1;
}

//*****************************************************************************
//
// PWM functions
//
//*****************************************************************************
__attribute__((always_inline)) inline void PWM_setUa(uint16_t Ua)
{
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, Ua);
}

__attribute__((always_inline)) inline void PWM_setUb(uint16_t Ub)
{
    EPWM_setCounterCompareValue(EPWM2_BASE, EPWM_COUNTER_COMPARE_A, Ub);
}

__attribute__((always_inline)) inline void PWM_setUc(uint16_t Uc)
{
    EPWM_setCounterCompareValue(EPWM3_BASE, EPWM_COUNTER_COMPARE_A, Uc);
}

//*****************************************************************************
//
// DAC functions
//
//*****************************************************************************
__attribute__((always_inline)) inline void DAC_setIa(uint16_t value)
{
    DAC_setShadowValue(DACA_BASE, value);
}

__attribute__((always_inline)) inline void DAC_setIb(uint16_t value)
{
    DAC_setShadowValue(DACB_BASE, value);
}

#endif   //_ACI_MAIN_H
