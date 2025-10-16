//###########################################################################
//
// FILE:  hrcap.h
//
// TITLE: C29x HRCAP Driver.
//
//#############################################################################
// $Copyright:
//#############################################################################

#ifndef HRCAP_H
#define HRCAP_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup hrcap_api HRCAP
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ecap.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Values that can be passed to HRCAP_enableCalibrationInterrupt(),
// HRCAP_disableCalibrationInterrupt() as the intFlags parameter and
// HRCAP_clearCalibrationFlags() and HRCAP_forceCalibrationFlags() as the flags
// parameter and returned by HRCAP_getCalibrationFlags().
//
//*****************************************************************************
//! Global calibration interrupt flag
//!
#define HRCAP_GLOBAL_CALIBRATION_INTERRUPT 0x1U
//! Calibration done flag
//!
#define HRCAP_CALIBRATION_DONE  0x2U
//! Calibration period overflow flag
//!
#define HRCAP_CALIBRATION_PERIOD_OVERFLOW  0x4U

//*****************************************************************************
//
//! Values that can be passed to HRCAP_getCalibrationClockPeriod() as the
//! \e clockSource parameter.
//
//*****************************************************************************
typedef enum
{
    HRCAP_CALIBRATION_CLOCK_SYSCLK = 0x0, //!< Use SYSCLK for period match.
    HRCAP_CALIBRATION_CLOCK_HRCLK  = 0x4  //!< Use HRCLK for period match.
}HRCAP_CalibrationClockSource;

//*****************************************************************************
//
//! Values that can be passed to HRCAP_setCalibrationMode(),
//! as the \e continuousMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Continuous calibration disabled.
    HRCAP_CONTINUOUS_CALIBRATION_DISABLED = 0x00,
    //! Continuous calibration enabled.
    HRCAP_CONTINUOUS_CALIBRATION_ENABLED =  0x20
}HRCAP_ContinuousCalibrationMode;

//*****************************************************************************
//
//! \internal
//! Checks HRCAP base address.
//!
//! \param base specifies the HRCAP module base address.
//!
//! This function determines if an HRCAP module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
HRCAP_isBaseValid(uint32_t base)
{
    return(
           ((base & BASE_ADDR_MASK) == HRCAP5_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == HRCAP6_BASE_FRAME(0U))
          );
}
#endif

//*****************************************************************************
//
//! enables HRCAP.
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function enables High Resolution Capture module.
//!
//! \note High resolution clock must be enabled before High Resolution Module
//!       is enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_enableHighResolution(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    //
    // Set HRE bit.
    //
    HWREGH(base + ECAP_O_HRCTL) |= ECAP_HRCTL_HRE;
}

//*****************************************************************************
//
//! Disables HRCAP.
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function disable High Resolution Capture module.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_disableHighResolution(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    //
    // Set HRE bit.
    //
    HWREGH(base + ECAP_O_HRCTL) &= ~ECAP_HRCTL_HRE;
}

//*****************************************************************************
//
//! Enables high resolution clock.
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function enables High Resolution clock.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_enableHighResolutionClock(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    //
    // Set HRCLKE bit.
    //
    HWREGH(base + ECAP_O_HRCTL) |= ECAP_HRCTL_HRCLKE;
}

//*****************************************************************************
//
//! Disables High resolution clock.
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function disables High Resolution clock.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_disbleHighResolutionClock(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));


    //
    // Clear HRCLKE bit.
    //
    HWREGH(base + ECAP_O_HRCTL) &= ECAP_HRCTL_HRCLKE;
}

//*****************************************************************************
//
//! Starts calibration.
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function starts calibration.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_startCalibration(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    //
    // Set CALIBSTART bit.
    //
    HWREGH(base + ECAP_O_HRCTL) |= ECAP_HRCTL_CALIBSTART;
}

//*****************************************************************************
//
//! Sets the calibration mode.
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function sets the the calibration mode by turning on continuous
//! calibration.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_setCalibrationMode(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));


    //
    // Write to CALIBSTS and CALIBCONT bits.
    //
    HWREGH(base + ECAP_O_HRCTL) |= ECAP_HRCTL_CALIBCONT;
}

//*****************************************************************************
//
//! Enables calibration interrupt.
//!
//! \param base is the base address of the HRCAP module.
//! \param intFlags is the calibration interrupt flags to be enabled.
//!
//! This function enables HRCAP calibration interrupt flags.
//! Valid values for intFlags are:
//!     - HRCAP_CALIBRATION_DONE   - Calibration done interrupt.
//!     - HRCAP_CALIBRATION_PERIOD_OVERFLOW - Calibration period overflow
//!                                                check interrupt.
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_enableCalibrationInterrupt(uint32_t base, uint16_t intFlags)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((intFlags & ~(HRCAP_CALIBRATION_DONE |
                       HRCAP_CALIBRATION_PERIOD_OVERFLOW)) == 0U);


    //
    // Set CALIBDONE or CALPRDCHKSTS.
    //
    HWREGH(base + ECAP_O_HRINTEN) |= intFlags;
}

//*****************************************************************************
//
//! Disables calibration interrupt source.
//!
//! \param base is the base address of the HRCAP module.
//! \param intFlags is the calibration interrupt flags to be disabled.
//!
//! This function disables HRCAP calibration interrupt flags.
//! Valid values for intFlags are:
//!     - HRCAP_CALIBRATION_DONE   - Calibration done interrupt.
//!     - HRCAP_CALIBRATION_PERIOD_OVERFLOW - Calibration period check
//!                                                   interrupt.
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_disableCalibrationInterrupt(uint32_t base, uint16_t intFlags)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((intFlags & ~(HRCAP_CALIBRATION_DONE |
                       HRCAP_CALIBRATION_PERIOD_OVERFLOW)) == 0U);


    //
    // Clear CALIBDONE or CALPRDCHKSTS.
    //
    HWREGH(base + ECAP_O_HRINTEN) &= ~intFlags;
}

//*****************************************************************************
//
//! Returns the calibration interrupt source.
//!
//! \param base is the base address of the HRCAP module.
//!
//! This function returns the HRCAP calibration interrupt source.
//!
//! \return Returns the HRCAP interrupt that has occurred. The following are
//!         valid return values.
//!          - HRCAP_GLOBAL_CALIBRATION_INTERRUPT - Global calibration
//!                                                 interrupt.
//!          - HRCAP_CALIBRATION_DONE   - Calibration done interrupt.
//!          - HRCAP_CALIBRATION_PERIOD_OVERFLOW - Calibration period overflow
//!                                                interrupt.
//!
//! \note - User can check if a combination of the interrupts have occurred
//!         by ORing the above return values.
//
//*****************************************************************************
static inline uint16_t
HRCAP_getCalibrationFlags(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    //
    // Return contents of HRFLG register.
    //
    return((uint16_t)(HWREGH(base + ECAP_O_HRFLG) & 0x7U));
}

//*****************************************************************************
//
//! Clears calibration flags.
//!
//! \param base is the base address of the HRCAP module.
//! \param flags is the calibration flags to be cleared.
//!
//! This function clears HRCAP calibration flags.
//! The following are valid values for flags.
//!     - HRCAP_GLOBAL_CALIBRATION_INTERRUPT - Global calibration interrupt.
//!     - HRCAP_CALIBRATION_DONE   - Calibration done flag.
//!     - HRCAP_CALIBRATION_PERIOD_OVERFLOW - Calibration period overflow flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_clearCalibrationFlags(uint32_t base, uint16_t flags)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((flags == (HRCAP_CALIBRATION_DONE |
                      HRCAP_GLOBAL_CALIBRATION_INTERRUPT)) ||
           (flags == (HRCAP_CALIBRATION_PERIOD_OVERFLOW |
                      HRCAP_GLOBAL_CALIBRATION_INTERRUPT)) ||
           (flags == (HRCAP_CALIBRATION_DONE |
                      HRCAP_GLOBAL_CALIBRATION_INTERRUPT |
                      HRCAP_CALIBRATION_PERIOD_OVERFLOW)));

    //
    // Write to HRCLR register.
    //
    HWREGH(base + ECAP_O_HRCLR) = flags;
}

//*****************************************************************************
//
//! Return the Calibration status
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function returns the calibration status.
//!
//! \return This functions returns true if the calibration is in process,false
//!         if there is no active calibration.
//
//*****************************************************************************
static inline bool
HRCAP_isCalibrationBusy(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    //
    // Read CALIBSTS bit.
    //
    return((HWREGH(base + ECAP_O_HRCTL) & ECAP_HRCTL_CALIBSTS) ==
             ECAP_HRCTL_CALIBSTS);
}

//*****************************************************************************
//
//! Force a software based calibration
//!
//! \param base is the base address of the HRCAP instance used.
//! \param flag is the calibration flag source.
//!
//! This function forces a software based calibration done flag.
//! The following are valid values for flag.
//!     - HRCAP_CALIBRATION_DONE - Calibration done flag.
//!     - HRCAP_CALIBRATION_PERIOD_OVERFLOW - Calibration period overflow flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_forceCalibrationFlags(uint32_t base, uint16_t flag)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((flag & ~(HRCAP_CALIBRATION_DONE |
                    HRCAP_CALIBRATION_PERIOD_OVERFLOW)) == 0U);


    //
    // Write to CALIBDONE or CALPRDCHKSTS bit.
    //
    HWREGH(base + ECAP_O_HRFRC) = flag;
}

//*****************************************************************************
//
//! Sets the calibration period count
//!
//! \param base is the base address of the HRCAP instance used.
//! \param sysclkHz is the rate of the SYSCLK in Hz.
//!
//! This function sets the calibration period count value to achieve a period
//! of 1.6 milliseconds given the SYSCLK frequency in Hz (the \e sysclkHz
//! parameter).
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_setCalibrationPeriod(uint32_t base, uint32_t sysclkHz)
{
    ASSERT(HRCAP_isBaseValid(base));

    HWREG(base + ECAP_O_HRCALPRD) = (sysclkHz * 16U) / 10000U;
}

//*****************************************************************************
//
//! Sets the calibration period count at a user configurable value.
//!
//! \param base is the base address of the HRCAP instance used.
//! \param sysclkHz is the rate of the SYSCLK in Hz.
//! \param periodInMs is the calibration period to be configured.
//!
//! This function sets the calibration period count value to the provided
//! period in milliseconds given the SYSCLK frequency in Hz (the \e sysclkHz
//! parameter).
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRCAP_configCalibrationPeriod(uint32_t base, uint32_t sysclkHz,
                                                     float periodInMs)
{
    ASSERT(HRCAP_isBaseValid(base));

    HWREG(base + ECAP_O_HRCALPRD) =
                    (uint32_t)((float32_t)sysclkHz * periodInMs / 1000.0F);
}

//*****************************************************************************
//
//! Returns the calibration clock period
//!
//! \param base is the base address of the HRCAP instance used.
//! \param clockSource is the calibration clock source
//! (\b HRCAP_CALIBRATION_CLOCK_SYSCLK or \b HRCAP_CALIBRATION_CLOCK_HRCLK).
//!
//! This function returns the period match value of the calibration clock. The
//! return value has a valid count when a period match occurs.
//!
//! \return This function returns the captured value of the clock counter
//!         specified by clockSource.
//
//*****************************************************************************
static inline uint32_t
HRCAP_getCalibrationClockPeriod(uint32_t base,
                                HRCAP_CalibrationClockSource clockSource)
{
    ASSERT(HRCAP_isBaseValid(base));

    //
    // Return ECAP_O_HRSYSCLKCAP or ECAP_O_HRCLKCAP.
    //
     return(HWREG(base + ECAP_O_HRSYSCLKCAP + ((uint32_t)clockSource*2UL)));
}

//*****************************************************************************
//
//! Calculates the scale factor
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function reads the SYSCLK and HRCLK calibration periods and then
//! uses them to calculate the scale factor.
//!
//! \return This function returns the calculated scale factor.
//
//*****************************************************************************
static inline float32_t
HRCAP_getScaleFactor(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    //
    // Calculate and return the scale factor.
    //
    return((float32_t)HRCAP_getCalibrationClockPeriod(base,
                                            HRCAP_CALIBRATION_CLOCK_SYSCLK) /
           (float32_t)HRCAP_getCalibrationClockPeriod(base,
                                            HRCAP_CALIBRATION_CLOCK_HRCLK));
}

//*****************************************************************************
//
//! Returns event time stamp in nanoseconds
//!
//! \param timeStamp is a raw time stamp count returned by
//! ECAP_getEventTimeStamp().
//! \param scaleFactor is the calculated scale factor returned by
//! HRCAP_getScaleFactor().
//!
//! This function converts a raw CAP time stamp (the \e timeStamp parameter) to
//! nanoseconds using the provided scale factor (the \e scaleFactor parameter).
//!
//! \return Returns the converted time stamp in nanoseconds.
//
//*****************************************************************************
static inline float32_t
HRCAP_convertEventTimeStampNanoseconds(uint32_t timeStamp,
                                       float32_t scaleFactor)
{
    //
    // Convert the raw count value to nanoseconds using the given scale factor.
    //
    return((float32_t)timeStamp * scaleFactor * ((float32_t)5.0 /
                                                 (float32_t)128.0));
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // HRCAP_H
