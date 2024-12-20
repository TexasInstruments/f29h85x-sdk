//#############################################################################
//
// FILE:   hrcap_ex1_capture.h
//
// TITLE:  HRCAP Calibration Header
//
//#############################################################################
//
//
// $Copyright:
//#############################################################################

//
// Included Files
//
#include "hrcap.h"

//
// Defines
//
#define HRCALCAL_STATUS_DONE_ISR    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT )

#define HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR                               \
                                    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT |      \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCALCAL_CALIBRATION_FLAGS  (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCAPCAL_OVERFLOW           4294967295.0f
#define HRCAPCAL_INV_OVERFLOW       (float32_t)(1.0f / HRCAPCAL_OVERFLOW)

//
// Typedefs
//
typedef struct
{
    uint32_t hrclkCount;    // High resolution clock count
    uint32_t sysclkcount;   // System clock count
    float32_t scaleFactor;  // Scale factor
    bool calDone;           // Calibration done flag
} HRCAPCAL_CalResultObj;
