//###########################################################################
//
// FILE:   flash.h
//
// TITLE:  C29x Flash driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef FLASH_H
#define FLASH_H

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
//! \addtogroup flash_api Flash
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_fri.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_asysctl.h"
#include "cpu.h"
#include "debug.h"


//
// Internal macros used for committing trim registers.
// Not intended for application use.
//
#define ASYSCTL_O_FLASHTRIMCOMMIT                     0x90U
#define ASYSCTL_FLASHTRIMCOMMIT_FLC0TRIMCOMMITREAD    0x1U
#define ASYSCTL_FLASHTRIMCOMMIT_FLC0TRIMCOMMITOTHER   0x2U
#define ASYSCTL_FLASHTRIMCOMMIT_FLC1TRIMCOMMITREAD    0x4U
#define ASYSCTL_FLASHTRIMCOMMIT_FLC1TRIMCOMMITOTHER   0x8U
#define ASYSCTL_FLASHTRIMCOMMIT_FLC2TRIMCOMMITREAD    0x10
#define ASYSCTL_FLASHTRIMCOMMIT_FLC2TRIMCOMMITOTHER   0x20

//*****************************************************************************
//
//! Enumeration of FRI register addresses for use with Flash_configFRI()
//
//*****************************************************************************
typedef enum {
    FLASH_FRI1 = 0,
    FLASH_FRI2 = 1,
    FLASH_FRI3 = 2,
    FLASH_FRI4 = 3
} Flash_FRI;

//*****************************************************************************
//
//! Macros for FRI options to use with the Flash_configFRI() function.
//! Includes macros for enabling and disabling prefetch, data cache, code cache
//! and data preread.
//
//*****************************************************************************
#define    FLASH_PREFETCH_ENABLE        0x1U
#define    FLASH_PREFETCH_DISABLE       0x0U
#define    FLASH_DATACACHE_ENABLE       0x2U
#define    FLASH_DATACACHE_DISABLE      0x0U
#define    FLASH_CODECACHE_ENABLE       0x4U
#define    FLASH_CODECACHE_DISABLE      0x0U
#define    FLASH_DATAPREREAD_ENABLE     0x8U
#define    FLASH_DATAPREREAD_DISABLE    0x0U


//*****************************************************************************
//
//! Macro to define the offset between options for different FRIs.
//! For example, FRI_O_2_INTF_CTRL - FRI_O_1_INTF_CTRL = 0x10U.
//
//*****************************************************************************
#define     FRI_REG_STEP                0x10U

//*****************************************************************************
//
//! Macros for FRI options to use with the Flash_lockFRI() function.
//
//*****************************************************************************
#define    FLASH_INTF_CTRL_LOCK         0x1U

//*****************************************************************************
//
//! Macros for FRI options to use with the Flash_commitFRI() function.
//
//*****************************************************************************
#define    FLASH_INTF_CTRL_COMMIT       0x1U

//*****************************************************************************
//
//! Macros for FRI options to use with the Flash_clearFRI() function.
//
//*****************************************************************************
#define    FLASH_PREFETCH_CLEAR         0x1U
#define    FLASH_DATACACHE_CLEAR        0x2U
#define    FLASH_CODECACHE_CLEAR        0x4U

//*****************************************************************************
//
// Delay instruction that allows for register configuration to complete.
//
//*****************************************************************************

#define    FLASH_DELAY_CONFIG   __asm(" NOP #8"); __asm(" NOP #8"); __asm(" NOP #4");

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************


//*****************************************************************************
//
//! Sets the random read wait state amount.
//!
//!
//! \param waitstates is the wait-state value.
//!
//! This function sets the number of wait states for a flash read access. The
//! \e waitstates parameter is a number between 1 and 15. It is \b important
//! to look at your device's datasheet for information about what the required
//! minimum flash wait-state is for your selected SYSCLK frequency.
//!
//! By default the wait state amount is configured to the maximum 15.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_setWaitstates(uint16_t waitstates)
{

    //
    // waitstates is 4 bits wide.
    //
    ASSERT(waitstates <= 0xFU);
    ASSERT(waitstates >= 0x1U);

    //
    // Write flash read wait-state amount to appropriate register.
    //
    HWREG(FRI1_BASE + FRI_O_FRDCNTL) =
        (HWREG(FRI1_BASE + FRI_O_FRDCNTL) &
         ~(uint32_t)FRI_FRDCNTL_RWAIT_M) |
         ((uint32_t)waitstates << FRI_FRDCNTL_RWAIT_S);
}

//*****************************************************************************
//
//! Locks the wait states set in the FRDCNTL register.
//!
//!
//!
//! This function locks the number of wait states for a flash read access.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_lockWaitstates()
{

    //
    // Set the FRI FRDCNTL Lock bit
    //
    HWREG(FRI1_BASE + FRI_O_FRDCNTL_LOCK) |= FRI_FRDCNTL_LOCK_LOCK;

}

//*****************************************************************************
//
//! Commitss the wait states.
//!
//!
//!
//! This function commits the number of wait states for a flash read access.
//! Once set, the lock cannot be written to until device is reset.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_commitWaitstates()
{

    //
    // Set the FRI FRDCNTL Lock bit
    //
    HWREG(FRI1_BASE + FRI_O_FRDCNTL_COMMIT) |= FRI_FRDCNTL_COMMIT_COMMIT;

}


//*****************************************************************************
//
//! Configures FRI
//!
//! \param friID is the Flash_FRI enum associated with the FRI desired for
//! for configuration
//!
//! \param configFlags is the value to be written and should be built with values
//! from the FRI option macros
//!
//!
//! This function allows the user to configure FRI prefetch, data cache,
//! code cache, and data preread flags.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_configFRI(Flash_FRI friID, uint32_t configFlags)
{

    //
    // Set the FRI options.
    //
    HWREG(FRI1_BASE + FRI_O_1_INTF_CTRL + (friID * FRI_REG_STEP)) = configFlags;

}

//*****************************************************************************
//
//! Locks FRI Interface Control register.
//!
//! \param friLockID is the FRI that will be locked. Should be value
//! from Flash_FRI_Lock enumeration.
//!
//! This function locks the FRI Interface control register specified by
//! friLockID.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_lockFRI(Flash_FRI friID)
{

    //
    // Set the FRI lock bit.
    //
    HWREG(FRI1_BASE + FRI_O_1_INTF_CTRL_LOCK + (friID * FRI_REG_STEP)) |= FLASH_INTF_CTRL_LOCK;

}

//*****************************************************************************
//
//! Commits FRI Interface Control register.
//!
//! \param friCommitID is the FRI that will be comitted. Should be value
//! from Flash_FRI_Commit enumeration.
//!
//! This function commits the FRI Interface control register specified by
//! friCommitID.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_commitFRI(Flash_FRI friID)
{

    //
    // Set the FRI lock bit.
    //
    HWREG(FRI1_BASE + FRI_O_1_INTF_CTRL_COMMIT + (friID * FRI_REG_STEP)) |= FLASH_INTF_CTRL_COMMIT;

}

//*****************************************************************************
//
//! Clears FRI options (code cache, data cache, and prefetch).
//!
//! \param friID is the Flash_FRI_Clear enum associated with the FRI desired for
//! for configuration
//!
//! \param clearFlags is the value to be written and should be built with values
//! from the FRI Clear macros
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_clearFRI(Flash_FRI friID, uint32_t clearFlags)
{

    //
    // Set the FRI INTF CLR bits
    //
    HWREG(FRI1_BASE + FRI_O_1_INTF_CLR + (friID * FRI_REG_STEP)) = clearFlags;

}

//*****************************************************************************
//
//! Enables parity test mechanism.
//!
//!
//! \param testEnable is the value to be written to the TESTEN field
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_enableParityTest(uint16_t testEnable)
{

    //
    // testEnable is 4 bits wide.
    //
    ASSERT(testEnable <= 0xFU);

    //
    // Set the test enable field
    //
    HWREG(FRI1_BASE + FRI_O_PARITY_TEST) =
        (HWREG(FRI1_BASE + FRI_O_PARITY_TEST) &
         ~(uint32_t)FRI_PARITY_TEST_TESTEN_M) |
         ((uint32_t)testEnable);

}

//*****************************************************************************
//
//! Disables parity test mechanism.
//!
//!
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_disableParityTest()
{

    //
    // Clear the test enable field
    //
    HWREG(FRI1_BASE + FRI_O_PARITY_TEST) &= ~(uint32_t)FRI_PARITY_TEST_TESTEN_M;

}

//*****************************************************************************
//
//! Locks Parity Test register.
//!
//!
//!
//! This function locks the Parity Test register.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_lockParityTest()
{

    //
    // Set the PARITY TEST LOCK bit
    //
    HWREG(FRI1_BASE + FRI_O_PARITY_TEST_LOCK) |= FRI_PARITY_TEST_LOCK_LOCK;

}

//*****************************************************************************
//
//! Commits Parity Test register.
//!
//!
//!
//! This function commits the Parity Test register. The PARITY TEST LOCK register
//! cannot be written to without a reset.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".TI.ramfunc.link2")))
__attribute__((always_inline))
static inline void
Flash_commitParityTest()
{

    //
    // Set the PARITY TEST COMMIT bit
    //
    HWREG(FRI1_BASE + FRI_O_PARITY_TEST_COMMIT) |= FRI_PARITY_TEST_COMMIT_COMMIT;

}

//*****************************************************************************
//
//! Initializes the flash config 1 trim registers.
//!
//! \return None.
//!
//!
//*****************************************************************************
__attribute__((always_inline))
static inline void
Flash_writeTrims(uint32_t reg_offset, uint32_t mask,
                 uint32_t shift, uint32_t value)
{
    //
    // Set the requested bits to the value.
    //
    HWREG(ANALOGSUBSYS_BASE + reg_offset) &= ~(uint32_t)mask;

    HWREG(ANALOGSUBSYS_BASE + reg_offset) |= ((uint32_t)value << shift);

}

//*****************************************************************************
//
//! Initializes the flash control registers.
//!
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param waitstates is the wait-state value.
//!
//! This function initializes the flash control registers. At reset banks and
//! pumps are in sleep.  A flash access will power up the bank and pump
//! automatically. This function will power up Flash banks and pumps and set the
//! fallback mode of flash and pumps as active.
//!
//! This function also sets the number of wait-states for a flash access
//! (see Flash_setWaitstates() for more details), and enables cache, the
//! prefetch mechanism, and ECC.
//!
//! \return None.
//
//*****************************************************************************
extern void
Flash_initModule(uint16_t waitstates);

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

#endif
