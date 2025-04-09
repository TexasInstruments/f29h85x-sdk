//#############################################################################
//
// FILE:   input_matrix.c
//
// TITLE:  
//
//
//#############################################################################

#include <stdint.h>
#include "matrix_example.h"

// Force a 64-bit alignment and put Ma, Mb and Mc in three different memory blocks
// CDA9
__attribute__((location(0x20144000))) float32_t   Ma_f32[4][4] = {{1,2,3,4},
                        {5,6,7,8},
                        {9,10,11,12},
                        {13,14,15,16}};
/// CDA10
__attribute__((location(0x20148000))) float32_t   Mb_f32[4][4] = {{1,2,3,4},
                        {5,6,7,8},
                        {9,10,11,12},
                        {13,14,15,16}};
/// CDA11
__attribute__((location(0x2014c000))) float32_t   Mc_f32[4][4] = {{0,0,0,0},
                        {0,0,0,0},
                        {0,0,0,0},
                        {0,0,0,0}};
// End of File
