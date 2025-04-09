//#############################################################################
//
//
// $Copyright:
//#############################################################################
#ifndef _BINARY_LUT_SEARCH_H_
#define _BINARY_LUT_SEARCH_H_
//#############################################################################
//
// FILE:   binary_lut_search.h
//
// TITLE:  Binary LUT search prototypes
//
//
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>
#include "math.h"
//!
//! \defgroup BINARY_LUT_SEARCH BIN_LUT

//!
//! \addtogroup BINARY_LUT_SEARCH
// @{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************


//*****************************************************************************
// typedefs
//*****************************************************************************

extern void binary_lut_search_closest_match(int32_t search_val, uint32_t size, int32_t lut[], uint32_t *piLeft, uint32_t *piRght);
extern int32_t binary_lut_search_exact_match(int32_t search_val, uint32_t size, int32_t lut[]);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _BINARY_LUT_SEARCH_H_

// End of File
