//###########################################################################
//
// FILE:   SFO_V8.H
//
// TITLE:  Scale Factor Optimizer Library V8 Interface Header
//         This header provides the function call interface for the scale
//         factor optimizer
//
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated
//#############################################################################

#ifndef _SFO_V8_H
#define _SFO_V8_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//
#define SFO_INCOMPLETE      0
#define SFO_COMPLETE        1
#define SFO_ERROR           2

#define PWM_CH_MAX 18  // Equals # of HRPWM modules in the device

//
// Function Prototypes
//
int SFO(void);     // SFO V8  Calibration Function

#endif // End: Multiple include Guard

#ifdef __cplusplus
}
#endif /* extern "C" */

//
// End of file
//
