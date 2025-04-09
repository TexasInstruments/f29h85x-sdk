//#############################################################################
//
// FILE:   fir_f32_example.h
//
// TITLE:  
//
//
//#############################################################################

//*****************************************************************************
// defines
//*****************************************************************************
#define USE_C    0  
#define INPUT_SIZE (512U)
// IMPORTANT: The asm implementation requires filt coeff size to be a multiple of 8
// Therefore, 0 pad the filt coeff array as needed
// Also, the asm implementation requires the top and bottom half of filt coeffs
// to be interleaved
#define COEFF_SIZE (64)
