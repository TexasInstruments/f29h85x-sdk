//###########################################################################
//
// FILE:   dac.c
//
// TITLE:  C29x DAC driver.
//
//###########################################################################
// $Copyright:
//###########################################################################

#include "dac.h"

//*****************************************************************************
//
// DAC_tuneOffsetTrim()
//
//*****************************************************************************

void
DAC_tuneOffsetTrim(uint32_t base, float32_t referenceVoltage)
{
    uint16_t oldOffsetTrim;
    float32_t newOffsetTrim;

    //
    // Check the arguments.
    //
    ASSERT(DAC_isBaseValid(base));
    ASSERT(referenceVoltage > 0.0F);

    //
    // Get the sign-extended offset trim value
    //
    oldOffsetTrim = (HWREGH(base + DAC_O_TRIM) & DAC_TRIM_OFFSET_TRIM_M);
    oldOffsetTrim = ((oldOffsetTrim & DAC_REG_BYTE_MASK) ^
                    0x80U) - 0x80U;

    //
    // Calculate new offset trim value if DAC is operating at a reference
    // voltage other than 2.5v.
    //
    newOffsetTrim = ((2.5F / referenceVoltage) *
                     (int16_t)oldOffsetTrim);

    //
    // Check if the new offset trim value is valid
    //
    ASSERT((newOffsetTrim > -129.0F) && (newOffsetTrim < 128.0F));

    //
    // Set the new offset trim value
    //
    HWREGH(base + DAC_O_TRIM) = (HWREGH(base + DAC_O_TRIM) &
                                 ~DAC_TRIM_OFFSET_TRIM_M) |
                                 (int16_t)newOffsetTrim;

}

