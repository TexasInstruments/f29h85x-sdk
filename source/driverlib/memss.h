//###########################################################################
//
// FILE:   memss.h
//
// TITLE:  C29x MemSS driver.
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

#ifndef MEMSS_H
#define MEMSS_H

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
//! \addtogroup memss_api Memss
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_memss.h"

//*****************************************************************************
//
// Useful defines used within the driver functions to access the registers.
// Not intended for use by application code.
//
//*****************************************************************************
#define MEMSS_INIT          MEMSS_LPA0_MEM_CONFIG_INIT
#define MEMSS_INIT_STS      MEMSS_LPA0_MEM_CONFIG_INIT_STS
#define MEMSS_TESTMODE_M    MEMSS_LPA0_MEM_CONFIG_TESTMODE_M
#define MEMSS_TESTMODE_S    MEMSS_LPA0_MEM_CONFIG_TESTMODE_S


//*****************************************************************************
//
//! The following are values that can be passed to all the functions as \e ram
//! or \e mem parameter.
//
//*****************************************************************************
typedef enum
{
    MEMSS_RAM_LPA0 = MEMSSLCFG_BASE + 0x0U,
    MEMSS_RAM_LPA1 = MEMSSLCFG_BASE + 0x10U,
    MEMSS_RAM_LDA0 = MEMSSLCFG_BASE + 0x20U,
    MEMSS_RAM_LDA1 = MEMSSLCFG_BASE + 0x30U,
    MEMSS_RAM_LDA2 = MEMSSLCFG_BASE + 0x40U,
    MEMSS_RAM_LDA3 = MEMSSLCFG_BASE + 0x50U,
    MEMSS_RAM_LDA4 = MEMSSLCFG_BASE + 0x60U,
    MEMSS_RAM_LDA5 = MEMSSLCFG_BASE + 0x70U,
    MEMSS_RAM_LDA6 = MEMSSLCFG_BASE + 0x80U,
    MEMSS_RAM_LDA7 = MEMSSLCFG_BASE + 0x90U,
    MEMSS_RAM_CPA0 = MEMSSCCFG_BASE + 0x0U,
    MEMSS_RAM_CPA1 = MEMSSCCFG_BASE + 0x10U,
    MEMSS_RAM_CDA0 = MEMSSCCFG_BASE + 0x20U,
    MEMSS_RAM_CDA1 = MEMSSCCFG_BASE + 0x30U,
    MEMSS_RAM_CDA2 = MEMSSCCFG_BASE + 0x40U,
    MEMSS_RAM_CDA3 = MEMSSCCFG_BASE + 0x50U,
    MEMSS_RAM_CDA4 = MEMSSCCFG_BASE + 0x60U,
    MEMSS_RAM_CDA5 = MEMSSCCFG_BASE + 0x70U,
    MEMSS_RAM_CDA6 = MEMSSCCFG_BASE + 0x80U,
    MEMSS_RAM_CDA7 = MEMSSCCFG_BASE + 0x90U,
    MEMSS_RAM_CDA8 = MEMSSCCFG_BASE + 0xA0U,
    MEMSS_RAM_CDA9 = MEMSSCCFG_BASE + 0xB0U,
    MEMSS_RAM_CDA10 = MEMSSCCFG_BASE + 0xC0U,
    MEMSS_RAM_CDA11 = MEMSSCCFG_BASE + 0xD0U,
    MEMSS_RAM_M0 = MEMSSMCFG_BASE + 0x0U
} Memss_RAM;


//*****************************************************************************
//
//! The following are values that can be passed to Memss_setTestMode() function
//! as \e testMode parameter.
//
//*****************************************************************************
typedef enum
{
    MEMSS_RAM_TEST_NORMAL     = 0, //! Normal mode of operation
    MEMSS_RAM_TEST_WRITE_DATA = 1, //! Write to ECC bits is disabled. ECC check
                                   //! on Read Data is disabled.
    MEMSS_RAM_TEST_WRITE_ECC  = 2, //! Write to Data bits is disabled. ECC check
                                   //! on Read Data is disabled. Read Returns
                                   //! ECC bits
} Memss_RAMTestMode;

//*****************************************************************************
//
//! The following are values that can be passed to Memss_enableDlb() and
//! Memss_disableDlb() function as \e cpuId parameter.
//
//*****************************************************************************
typedef enum
{
    MEMSS_CPU_ID_1  = 0U,    //! ID for CPU1
    MEMSS_CPU_ID_2  = 1U,    //! ID for CPU2
    MEMSS_CPU_ID_3  = 2U     //! ID for CPU3
} Memss_CpuId;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Triggers memory initialization
//!
//! \param ram is the RAM block to be initialized.
//!
//! This function triggers memory initialization for the specified block. Use
//! the function Memss_getInitStatus() for reading the init status.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_initMemory")))
__attribute__((always_inline))
static inline void
Memss_initMemory(Memss_RAM ram)
{
    HWREG((uint32_t)ram) |= MEMSS_INIT;
}

//*****************************************************************************
//
//! Returns the status of the RAM init
//!
//! \param ram is the RAM block to be checked.
//!
//! This function returns the status if RAM initialization for the specified
//! block.
//!
//! \return true if initialization is complete, false if not
//
//*****************************************************************************
__attribute__((always_inline))
static inline bool
Memss_getInitStatus(Memss_RAM ram)
{
    return((HWREG((uint32_t)ram) & MEMSS_INIT_STS) != 0U);
}

//*****************************************************************************
//
//! Sets the RAM test mode
//!
//! \param ram is the RAM block
//! \param testMode Test Mode to be set
//!
//! This function sets the test mode for the specified block.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_setRAMTestMode")))
__attribute__((always_inline))
static inline void
Memss_setRAMTestMode(Memss_RAM ram, Memss_RAMTestMode testMode)
{
    HWREG((uint32_t)ram) =
                 (HWREG((uint32_t)ram) & ~(uint32_t)MEMSS_TESTMODE_M) |
                 ((uint32_t)testMode << MEMSS_TESTMODE_S);
}

//*****************************************************************************
//
//! Locks the config register
//!
//! \param mem is the RAM/ROM config register to be locked. Use the enum
//!            Memss_RAM.
//!
//! This function locks the CONFIG register of selected RAM block.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_lockConfig")))
__attribute__((always_inline))
static inline void
Memss_lockConfig(uint32_t mem)
{
    HWREG(mem + 4U) = 1U;
}

//*****************************************************************************
//
//! Unlocks the config register
//!
//! \param mem is the RAM/ROM config register to be unlocked. Use the enum
//!            Memss_RAM.
//!
//! This function unlocks the CONFIG register of selected RAM block.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_unlockConfig")))
__attribute__((always_inline))
static inline void
Memss_unlockConfig(uint32_t mem)
{
    HWREG(mem + 4U) = 0U;
}

//*****************************************************************************
//
//! Commit the config register
//!
//! \param mem is the RAM/ROM config register to be commited. Use the enum
//!            Memss_RAM.
//!
//! This function commits the CONFIG register of selected RAM block.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_commitConfig")))
__attribute__((always_inline))
static inline void
Memss_commitConfig(uint32_t mem)
{
    HWREG(mem + 8U) = 1U;
}

//*****************************************************************************
//
//! Enable DLB for CPU ID
//!
//! \param cpuId is CPU ID for which DLB is enabled
//!
//! This function enables Data Line Buffer for CPU ID.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_enableDlb")))
__attribute__((always_inline))
static inline void
Memss_enableDlb(Memss_CpuId cpuId)
{
    HWREG(MEMSSMISCI_BASE + MEMSS_O_MEM_DLB_CONFIG) |= \
                            ((uint32_t)1U << (uint32_t)cpuId);
}

//*****************************************************************************
//
//! Disable DLB for CPU ID
//!
//! \param cpuId is CPU ID for which DLB is disabled
//!
//! This function disables Data Line Buffer for CPU ID.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_disableDlb")))
__attribute__((always_inline))
static inline void
Memss_disableDlb(Memss_CpuId cpuId)
{
    HWREG(MEMSSMISCI_BASE + MEMSS_O_MEM_DLB_CONFIG) &= \
                            ~(((uint32_t)1U << (uint32_t)cpuId));
}

//*****************************************************************************
//
//! Locks all the config registers.
//!
//! This function locks all the RAM and ROM CONFIG registers.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_lockAllRegisters")))
extern void
Memss_lockAllRegisters(void);

//*****************************************************************************
//
//! Unlocks all the config registers.
//!
//! This function unlocks all the RAM and ROM CONFIG registers.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_unlockAllRegisters")))
extern void
Memss_unlockAllRegisters(void);

//*****************************************************************************
//
//! Commits all the config registers.
//!
//! This function commits all the RAM and ROM CONFIG registers.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.Memss_commitAllRegisters")))
extern void
Memss_commitAllRegisters(void);


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // MEMSS_H
