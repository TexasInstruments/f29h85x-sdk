//#############################################################################
//
//
// $Copyright:
//#############################################################################
 
#ifndef GSM_TEST_H
#define GSM_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"
#include "dcl.h"

void GSM_Routine(void);
float32_t GSM_target_fn(float32_t x);

//
//  User configurable values
//
#define BUFFER_SIZE    400   //!< The size of the output buffer

static float32_t out_buffer[BUFFER_SIZE];

DCL_GSM gain_module = GSM_DEFAULTS;

#ifdef __cplusplus
}
#endif // extern "C"

#endif
