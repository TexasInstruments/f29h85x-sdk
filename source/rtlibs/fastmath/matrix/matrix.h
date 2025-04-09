//#############################################################################
//
//
// $Copyright:
//#############################################################################
#ifndef _MATRIX_H_
#define _MATRIX_H_
//#############################################################################
//
// FILE:   matrix.h
//
// TITLE:  Matrix functions
//
//
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>
#include "math.h"
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************


//*****************************************************************************
// typedefs
//*****************************************************************************
typedef float float32_t;

//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//

// Function: matrix_mpy_f32_4by4
// Description: 4x4 matrix multiply in C, single-precision floating-pt
extern void matrix_mpy_f32_4by4(float32_t Ma_f32[][4], float32_t Mb_f32[][4], float32_t Mc_f32[][4]);

// Function: matrix_mpy_f64_4by4
// Description: 4x4 matrix multiply in C, double-precision floating-pt
extern void matrix_mpy_f64_4by4(double Ma_f64[][4], double Mb_f64[][4], double Mc_f64[][4]);

// Function: matrix_determinant_f32_4by4
// Description: Determinant of 4x4 matrix in C, single-precision floating-pt
extern float32_t matrix_determinant_f32_4by4(float32_t Ma_f32[][4]);

// Function: matrix_invert_f32_4by4
// Description: Inverse of 4x4 matrix in C, single-precision floating-pt
extern void matrix_invert_f32_4by4(float32_t Ma_f32[][4], float32_t Mb_f32[][4], float32_t Det);

// Function: matrix_invert_determinant_f32_4by4
// Description: Inverse and determinant of 4x4 matrix in C, single-precision floating-pt
extern float32_t matrix_invert_determinant_f32_4by4(float32_t Ma_f32[][4], float32_t Mb_f32[][4]);

// Function: matrix_mpy_f32_4by4_casm
// Description: 4x4 matrix multiply in Asm, single-precision floating-pt
extern void matrix_mpy_f32_4by4_casm(float Ma_f32[][4], float Mb_f32[][4], float Mc_f32[][4]);

// Function: matrix_mpy_f32_4by1_casm
// Description: 4x1 matrix multiply in Asm, single-precision floating-pt
extern void matrix_mpy_f32_4by1_casm(float Ma_f32[][4], float Mb_f32[], float Mc_f32[]);

// Function: matrix_mpy_f32_6by6_casm
// Description: 6x6 matrix multiply in Asm, single-precision floating-pt
extern void matrix_mpy_f32_6by6_casm(float Ma_f32[][6], float Mb_f32[][6], float Mc_f32[][6]);

// Function: matrix_mpy_f64_4by4_casm
// Description: 4x4 matrix multiply in Asm, double-precision floating-pt
void    matrix_mpy_f64_4by4_casm(double Ma_f64[][4], double Mb_f64[][4], double Mc_f64[][4]);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_FILTER_H_

// End of File
