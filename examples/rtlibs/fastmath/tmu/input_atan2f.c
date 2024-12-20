//#############################################################################
//
// FILE:   input_atan2f.c
//
// TITLE:  
//
//
//#############################################################################

#include <stdint.h>
#include "atan2f_example.h"

// atanf input
__attribute__((location(0x20120000))) volatile float32_t test_input= 0.6f; 

// atan2f inputs
volatile float32_t x_input= -3.0f;
volatile float32_t y_input= 1.0f;

// End of File
