//###########################################################################
//
// FILE:   dcc.h
//
// TITLE:  C29x DCC driver.
//
//###########################################################################
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//###########################################################################

#ifndef DCC_H
#define DCC_H

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
//! \addtogroup dcc_api DCC
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_dcc.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//
// Minimum and maximum values of valid seed value
//
#define DCC_VALIDSEED_MIN 4U
#define DCC_VALIDSEED_MAX 0xFFFFU

//
// Minimum and maximum values of counter0/1 seed value
//
#define DCC_COUNTSEED_MIN 1U
#define DCC_COUNTSEED_MAX 0xFFFFFU

//
// The reset value required to start or enable specific DCC operations
//
#define DCC_ENABLE_VALUE     (0xAU)

//
// The reset value required to stop or disable specific DCC operations
//
#define DCC_DISABLE_VALUE    (0x5U)

//
// A 16-bit register mask
//
#define DCC_REG_WORD_MASK    (0xFFFFU)

//
// A 7-bit register mask
//
#define DCC_REG_BYTE_MASK    (0x7FU)

//
// A mask for the DCC counter seed registers
//
#define DCC_SEED_REG_MASK    (0xFFF0U)

//
// A mask for the DCC counter seed value
//
#define DCC_SEED_CNT_MASK    (0xF0000U)


//*****************************************************************************
//
//! The following are defines for the source parameter of the
//! DCC_setCounter1ClkSource() function.
//
//*****************************************************************************
typedef enum
{
    DCC_COUNT1SRC_PLL                 = 0x0U,  //!< Direct output of SYSPLL
                                               //!< CLKOUT
    DCC_COUNT1SRC_FLC1_FCLK           = 0x1U,  //!< FCLK (divided clock) output
                                               //!< from Flash Controller 1
    DCC_COUNT1SRC_INTOSC1             = 0x2U,  //!< Internal Oscillator1 Output
                                               //!< Clock
    DCC_COUNT1SRC_INTOSC2             = 0x3U,  //!< Internal Oscillator2 Output
                                               //!< Clock
    DCC_COUNT1SRC_ECATPHYCLK          = 0x5U,  //!< Ethercat PHY Clock
    DCC_COUNT1SRC_CPU1_CLOCK          = 0x6U,  //!< CPU1 Clock
    DCC_COUNT1SRC_CPU2_CLOCK          = 0x7U,  //!< CPU2 Clock
    DCC_COUNT1SRC_RTDMA_CLOCK         = 0x8U,  //!< RTDMA Clock
    DCC_COUNT1SRC_INPUTXBAR1_INPUT15  = 0x9U,  //!< Input 15 of INPUTXBAR1
    DCC_COUNT1SRC_AUXCLKIN            = 0xAU,  //!< Auxiliary Clock input
    DCC_COUNT1SRC_EPWMCLK             = 0xBU,  //!< Clock input to EPWM module
    DCC_COUNT1SRC_ADCCLK              = 0xDU,  //!< ADC conversion clock
    DCC_COUNT1SRC_WDCLK               = 0xEU,  //!< Watchdog clock after dividers
    DCC_COUNT1SRC_FLC2_FCLK           = 0xFU,  //!< FCLK (divided clock) output
                                               //!< from Flash Controller 2
    DCC_COUNT1SRC_CPU3_CLOCK          = 0x15U, //!< CPU3 Clock
    DCC_COUNT1SRC_INPUTXBAR1_INPUT11  = 0x18U, //!< Input 11 of INPUTXBAR
    DCC_COUNT1SRC_INPUTXBAR1_INPUT12  = 0x19U, //!< Input 12 of INPUTXBAR
    DCC_COUNT1SRC_MCANA               = 0x1AU, //!< MCANA Bit Clock
    DCC_COUNT1SRC_MCANB               = 0x1BU, //!< MCANB Bit Clock
    DCC_COUNT1SRC_MCANC               = 0x1CU, //!< MCANC Bit Clock
    DCC_COUNT1SRC_MCAND               = 0x1DU, //!< MCAND Bit Clock
    DCC_COUNT1SRC_MCANE               = 0x1EU, //!< MCANE Bit Clock
    DCC_COUNT1SRC_MCANF               = 0x1FU, //!< MCANF Bit Clock
    DCC_COUNT1SRC_ESMCLK              = 0x20U, //!< ESM Clock
} DCC_Count1ClockSource;

//*****************************************************************************
//
//! The following are defines for the source parameter of the
//! DCC_setCounter0ClkSource() function.
//
//*****************************************************************************
typedef enum
{
    DCC_COUNT0SRC_XTAL               = 0x0U,  //!< Crystal Oscillator output
    DCC_COUNT0SRC_INTOSC1            = 0x1U,  //!< Internal Oscillator1 output
    DCC_COUNT0SRC_INTOSC2            = 0x2U,  //!< Internal Oscillator2 output
    DCC_COUNT0SRC_TCK                = 0x4U,  //!< TCK pin input
    DCC_COUNT0SRC_CPU1_CLOCK         = 0x5U,  //!< CPU1 Clock
    DCC_COUNT0SRC_AUXCLKIN           = 0x8U,  //!< Auxiliary Clock input
    DCC_COUNT0SRC_INPUTXBAR1_INPUT16 = 0xCU,  //!< Input 16 of INPUTXBAR
} DCC_Count0ClockSource;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks DCC base address.
//!
//! \param base specifies the DCC module base address.
//!
//! This function determines if an DCC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
__attribute__((always_inline))
static inline bool
DCC_isBaseValid(uint32_t base)
{
    return(
           ((base & BASE_ADDR_MASK) == DCC1_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == DCC2_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == DCC3_BASE_FRAME(0U))
          );
}
#endif

//*****************************************************************************
//
//! Enables the DCC module.
//!
//! \param base is the DCC module base address
//!
//! This function starts the DCC counter operation.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Set DCC enable bit field.
    //
    HWREGH(base + DCC_O_GCTRL) =
                (HWREGH(base + DCC_O_GCTRL) & ~(DCC_GCTRL_DCCENA_M)) |
                ((uint16_t)DCC_ENABLE_VALUE << DCC_GCTRL_DCCENA_S);
}

//*****************************************************************************
//
//! Disable the DCC module.
//!
//! \param base is the DCC module base address
//!
//! This function stops the DCC counter operation.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Reset DCC enable bit field.
    //
    HWREGH(base + DCC_O_GCTRL) =
                (HWREGH(base + DCC_O_GCTRL) & ~(DCC_GCTRL_DCCENA_M)) |
                ((uint16_t)DCC_DISABLE_VALUE << DCC_GCTRL_DCCENA_S);
}

//*****************************************************************************
//
//! Enable DCC Error Signal
//!
//! \param base is the DCC module base address
//!
//! This function enables the error signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_enableErrorSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Enable the error signal
    //
    HWREGH(base + DCC_O_GCTRL) =
                (HWREGH(base + DCC_O_GCTRL) & ~(DCC_GCTRL_ERRENA_M)) |
                ((uint16_t)DCC_ENABLE_VALUE << DCC_GCTRL_ERRENA_S);
}

//*****************************************************************************
//
//! Enable DCC Done Signal
//!
//! \param base is the DCC module base address
//!
//! This function enables the done signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_enableDoneSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Enable the done interrupt signal
    //
    HWREGH(base + DCC_O_GCTRL) =
                (HWREGH(base + DCC_O_GCTRL) & ~(DCC_GCTRL_DONEENA_M)) |
                ((uint16_t)DCC_ENABLE_VALUE << DCC_GCTRL_DONEENA_S);
}

//*****************************************************************************
//
//! Disable DCC Error Signal
//!
//! \param base is the DCC module base address
//!
//! This function disables the error signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_disableErrorSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Disable the error signal
    //
    HWREGH(base + DCC_O_GCTRL) =
                (HWREGH(base + DCC_O_GCTRL) & ~(DCC_GCTRL_ERRENA_M)) |
                ((uint16_t)DCC_DISABLE_VALUE << DCC_GCTRL_ERRENA_S);
}

//*****************************************************************************
//
//! Disable DCC Done Signal
//!
//! \param base is the DCC module base address
//!
//! This function disables the done signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_disableDoneSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Disable the done interrupt signal
    //
    HWREGH(base + DCC_O_GCTRL) =
                (HWREGH(base + DCC_O_GCTRL) & ~(DCC_GCTRL_DONEENA_M)) |
                ((uint16_t)DCC_DISABLE_VALUE << DCC_GCTRL_DONEENA_S);
}

//*****************************************************************************
//
//! Enable DCC Single-Shot Mode
//!
//! \param base is the DCC module base address
//!
//! This function enables the single-shot mode and sets the operation mode.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_enableSingleShotMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Enable Single-Shot mode
    //
    HWREGH(base + DCC_O_GCTRL) =
                (HWREGH(base + DCC_O_GCTRL) & ~(DCC_GCTRL_SINGLESHOT_M)) |
                ((uint16_t)DCC_ENABLE_VALUE << DCC_GCTRL_SINGLESHOT_S);
}

//*****************************************************************************
//
//! Disable DCC Single-Shot Mode
//!
//! \param base is the DCC module base address
//!
//! This function disables the DCC Single-Shot operation mode
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_disableSingleShotMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Disable Single-Shot mode
    //
    HWREGH(base + DCC_O_GCTRL) =
                (HWREGH(base + DCC_O_GCTRL) & ~(DCC_GCTRL_SINGLESHOT_M)) |
                ((uint16_t)DCC_DISABLE_VALUE << DCC_GCTRL_SINGLESHOT_S);
}

//*****************************************************************************
//
//! Get Error Flag Status
//!
//! \param base is the DCC module base address
//!
//! This function gets the error flag status.
//!
//! \return Returns \b true if an error has occurred, \b false if no errors
//! have occurred.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
DCC_getErrorStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the error flag
    //
    return((HWREGB(base + DCC_O_STATUS) & DCC_STATUS_ERR) == DCC_STATUS_ERR);
}

//*****************************************************************************
//
//! Get Single-Shot Done Flag Status
//!
//! \param base is the DCC module base address
//!
//! This function gets the single-shot done flag status.
//!
//! \return Returns \b true if single-shot mode has completed, \b false if
//! single-shot mode has not completed.
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
DCC_getSingleShotStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Read the done flag
    //
    return((HWREGB(base + DCC_O_STATUS) & DCC_STATUS_DONE) == DCC_STATUS_DONE);
}

//*****************************************************************************
//
//! Clear Error Status Flag
//!
//! \param base is the DCC module base address
//!
//! This function clears the DCC error status flag.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_clearErrorFlag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Clear error status flag
    //
    HWREGB(base + DCC_O_STATUS) |= DCC_STATUS_ERR;
}

//*****************************************************************************
//
//! Clear Single-Shot Done Status Flag
//!
//! \param base is the DCC module base address
//!
//! This function clears the DCC single-shot done status flag.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_clearDoneFlag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Clear done status flag
    //
    HWREGB(base + DCC_O_STATUS) |= DCC_STATUS_DONE;
}

//*****************************************************************************
//
//! Get Current Value of Counter 0
//!
//! \param base is the DCC module base address
//!
//! This function gets current value of counter 0.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of counter 0.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
DCC_getCounter0Value(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the current counter 0 value
    //
    return(HWREG(base + DCC_O_CNT0));
}

//*****************************************************************************
//
//! Get Current Value of the Valid Duration Counter for Counter 0
//!
//! \param base is the DCC module base address
//!
//! This function gets current value of the valid duration counter for
//! counter 0.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of the valid duration counter.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint16_t
DCC_getValidCounter0Value(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the current valid duration counter value
    //
    return(HWREGH(base + DCC_O_VALID0));
}

//*****************************************************************************
//
//! Get Current Value of Counter 1
//!
//! \param base is the DCC module base address
//!
//! This function gets current value of counter 1.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of counter 1.
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint32_t
DCC_getCounter1Value(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the current counter 1 value
    //
    return(HWREG(base + DCC_O_CNT1));
}

//*****************************************************************************
//
//! Set Counter 1 Clock Source
//!
//! \param base is the DCC module base address
//! \param source is the selected clock source for counter 1
//!
//! This function sets the counter 1 clock source.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_setCounter1ClkSource(uint32_t base, DCC_Count1ClockSource source)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Set the specified clock source
    //  DCC Clk source is of 5bits DCCCLKSRC1[4:0]
    //
    HWREGH(base + DCC_O_CLKSRC1) = (HWREGH(base + DCC_O_CLKSRC1) &
                                   (DCC_CLKSRC1_CLKSRC1_M << 6U)) |
                                   (((uint16_t)DCC_ENABLE_VALUE <<
                                   DCC_CLKSRC1_KEY_S) | (uint16_t)source);
}

//*****************************************************************************
//
//! Set Counter 0 Clock Source
//!
//! \param base is the DCC module base address
//! \param source is the selected clock source for counter 0
//!
//! This function sets the counter 0 clock source.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_setCounter0ClkSource(uint32_t base, DCC_Count0ClockSource source)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Set the specified clock source
    //  DCC Clk source is of 4bits DCCCLKSRC0[3:0]
    //
    HWREGH(base + DCC_O_CLKSRC0) = (HWREGH(base + DCC_O_CLKSRC0) &
                                   (DCC_REG_BYTE_MASK << 5U)) |
                                   (((uint16_t)DCC_ENABLE_VALUE <<
                                   DCC_CLKSRC0_KEY_S) | (uint16_t)source);
}

//*****************************************************************************
//
//! Get Counter 1 Clock Source
//!
//! \param base is the DCC module base address
//!
//! This function gets the counter 1 clock source.
//!
//! \return Returns Counter 1 clock source from the enum DCC_Count1ClockSource
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint16_t
DCC_getCounter1ClkSource(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Get the specified clock source
    //
    return(HWREGH(base + DCC_O_CLKSRC1) & DCC_CLKSRC1_CLKSRC1_M);
}

//*****************************************************************************
//
//! Get Counter 0 Clock Source
//!
//! \param base is the DCC module base address
//!
//! This function gets the counter 0 clock source.
//!
//! \return Returns Counter 0 clock source from the enum DCC_Count0ClockSource
//
//*****************************************************************************
__attribute__((always_inline))
static inline uint16_t
DCC_getCounter0ClkSource(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Get the specified clock source
    //
    return(HWREGH(base + DCC_O_CLKSRC0) & DCC_CLKSRC0_CLKSRC0_M);
}

//*****************************************************************************
//
//! Set the seed values
//!
//! \param base is the DCC module base address
//! \param counter0 sets the seed value that gets loaded into Counter 0
//! \param validCounter0 sets the seed value that gets loaded into the valid
//!  duration counter for Counter 0
//! \param counter1 sets the seed value that gets loaded into Counter 1
//!
//! This function sets the seed values for Counter 0, Valid Duration Counter 0,
//! and Counter 1.
//!
//! \note
//! -# Operating DCC with '0' set as the seed value for Counter 0, Valid
//! Duration Counter 0, and/or Counter 1 will result in undefined operation.
//! -# The Valid Duration Counter 0 is designed to be at least four cycles
//! wide and shouldn't be programmed with a value less than '4'.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
DCC_setCounterSeeds(uint32_t base, uint32_t counter0, uint32_t validCounter0,
                    uint32_t counter1)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));
    ASSERT(validCounter0 >= DCC_VALIDSEED_MIN);
    ASSERT(counter0 >= DCC_COUNTSEED_MIN);
    ASSERT(counter1 >= DCC_COUNTSEED_MIN);
    ASSERT(validCounter0 <= DCC_VALIDSEED_MAX);
    ASSERT(counter0 <= DCC_COUNTSEED_MAX);
    ASSERT(counter1 <= DCC_COUNTSEED_MAX);

    //
    // Set Counter 0 Seed
    //
    HWREG(base + DCC_O_CNTSEED0) = counter0;

    //
    // Set Valid Duration Counter 0 Seed
    //
    HWREG(base + DCC_O_VALIDSEED0) = validCounter0;

    //
    // Set Counter 1 Seed
    //
    HWREG(base + DCC_O_CNTSEED1) = counter1;

}

//*****************************************************************************
//
//! Verify the frequency of a clock source using a reference clock
//!
//! \param base is the DCC module base address
//! \param clock1 is the clock source to be verified
//! \param freq1 is the frequency of the clock source to be verified
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCC error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function verifies the frequency of the specified clock using a
//! reference clock.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \return Returns \b true if the actual frequency of clock1 is matching
//! freq1, \b false otherwise
//
//*****************************************************************************
extern bool
DCC_verifyClockFrequency(uint32_t base,
                         DCC_Count1ClockSource clock1,
                         float32_t freq1,
                         DCC_Count0ClockSource clock0,
                         float32_t freq0,
                         float32_t tolerance,
                         float32_t freqerr,
                         float32_t freq_sysclk);

//*****************************************************************************
//
//! Measure the frequency of a clock source using a reference clock
//!
//! \param base is the DCC module base address
//! \param clock1 is the clock source to be measured
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCC error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function measures the frequency of the specified clock using a
//! reference clock.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \return Measured clock frequency
//
//*****************************************************************************
extern float32_t
DCC_measureClockFrequency(uint32_t base,
                          DCC_Count1ClockSource clock1,
                          DCC_Count0ClockSource clock0,
                          float32_t freq0,
                          float32_t tolerance,
                          float32_t freqerr,
                          float32_t freq_sysclk);

//*****************************************************************************
//
//! Continuously monitor the frequency of a clock source using a reference
//! clock
//!
//! \param base is the DCC module base address
//! \param clock1 is the clock source to be verified
//! \param freq1 is the frequency of the clock source to be verified
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCC error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function continuously monitors the frequency of the specified clock
//! using a reference clock. An error signal is generated if the frequency
//! ratio is altered.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \note This function does not enable the DCC interrupt. The user application
//! must enable it to trigger an intetrupt when an error is detected.
//!
//! \return Returns None
//
//*****************************************************************************
extern void
DCC_continuousMonitor(uint32_t base,
                      DCC_Count1ClockSource clock1,
                      float32_t freq1,
                      DCC_Count0ClockSource clock0,
                      float32_t freq0,
                      float32_t tolerance,
                      float32_t freqerr,
                      float32_t freq_sysclk);
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // DCC_H
