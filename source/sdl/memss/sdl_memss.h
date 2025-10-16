/* ###########################################################################
 *
 *  \file     sdl_memss.h
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of MEMSS.
 *            This also contains some related macros.
 *
 *
 *  Copyright (C) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

########################################################################### */

/**
 * \addtogroup sdl_memss_group
 *
 * @{
 */

#ifndef SDL_MEMSS_H
#define SDL_MEMSS_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stddef.h>
#include <include/sdlr_baseaddress.h>
#include <include/hw_types.h>
#include "sdlr_memss.h"

typedef enum
{
    SDL_MEMSS_RAM_LPA0  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LPA0_MEM_CONFIG,
    SDL_MEMSS_RAM_LPA1  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LPA1_MEM_CONFIG,
    SDL_MEMSS_RAM_LDA0  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LDA0_MEM_CONFIG,
    SDL_MEMSS_RAM_LDA1  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LDA1_MEM_CONFIG,
    SDL_MEMSS_RAM_LDA2  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LDA2_MEM_CONFIG,
    SDL_MEMSS_RAM_LDA3  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LDA3_MEM_CONFIG,
    SDL_MEMSS_RAM_LDA4  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LDA4_MEM_CONFIG,
    SDL_MEMSS_RAM_LDA5  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LDA5_MEM_CONFIG,
    SDL_MEMSS_RAM_LDA6  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LDA6_MEM_CONFIG,
    SDL_MEMSS_RAM_LDA7  = SDL_MEMSSLCFG_BASE + SDL_MEMSS_LDA7_MEM_CONFIG,
    SDL_MEMSS_RAM_CPA0  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CPA0_MEM_CONFIG,
    SDL_MEMSS_RAM_CPA1  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CPA1_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA0  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA0_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA1  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA1_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA2  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA2_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA3  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA3_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA4  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA4_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA5  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA5_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA6  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA6_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA7  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA7_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA8  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA8_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA9  = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA9_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA10 = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA10_MEM_CONFIG,
    SDL_MEMSS_RAM_CDA11 = SDL_MEMSSCCFG_BASE + SDL_MEMSS_CDA11_MEM_CONFIG,
    SDL_MEMSS_RAM_M0    = SDL_MEMSSMCFG_BASE + SDL_MEMSS_M0_MEM_CONFIG,
    SDL_MEMSS_RAM_INVALID = -1
} SDL_MEMSS_RAM;

/* Test modes */
typedef enum
{
   SDL_MEMSS_TESTMODE_NORMAL = 0x0U,
   SDL_MEMSS_TESTMODE_DATA_ONLY = 0x1U,
   SDL_MEMSS_TESTMODE_ECC_ONLY = 0x2U,
   SDL_MEMSS_TESTMODE_ECC_READ,
   SDL_MEMSS_TESTMODE_INVALID
}SDL_MEMSS_TestMode;

/* Lock Mechanism for Control Registers values */
#define SDL_MEMSS_MEM_CONFIG_LOCK_ENABLE                                    (0x1U)
#define SDL_MEMSS_MEM_CONFIG_LOCK_DISABLE                                   (0x0U)
#define SDL_MEMSS_MEM_CONFIG_COMMIT_MEM_CONFIG_LOCK                         (0x1U)

#define SDL_MEMSS_PERI_MEM_TEST_LOCK_ALLOWED                                (0x0U)
#define SDL_MEMSS_PERI_MEM_TEST_LOCK_BLOCKED                                (0x1U)
#define SDL_MEMSS_PERI_MEM_TEST_CONTROL_ETHERCAT_MEM_FORCE_INTRODUCE_ERROR  (0x1U)
#define SDL_MEMSS_PERI_MEM_TEST_CONTROL_NO_EFFECT                           (0x0U)

/* PARITY_TEST register TESTEN values */
#define SDL_MEMSS_PARITY_TEST_ENABLE                                        (0xAU) /* 1010: Enable parity test */
#define SDL_MEMSS_PARITY_TEST_DISABLE                                       (0x0U) /* Disable parity test */
#define SDL_MEMSS_PERI_MEM_TEST_CONTROL_ETHERCAT_MEM_FORCE_INJECTED_ERROR   (0x1U)
#define SDL_MEMSS_PARITY_TIMEOUT                                            (5U)
#define SDL_MEMSS_NO_INTERRUPT                                                 0U
#define SDL_MEMSS_INTERRUPT                                                    1U

#define SDL_MEMSS_MEM_CONFIG_TESTMODE_MASK       (0x3U)
#define SDL_MEMSS_MEM_CONFIG_TESTMODE_SHIFT      (0X0U)

#define SDL_APP_TEST_PASS          (0)
#define SDL_APP_TEST_FAIL          (-1)
#define SDL_MEMSS_ECC_INTERRUPT    (1)

#define SDL_CDA11_RAM_END 0x2014FFFFU

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * @brief Configure memory test mode.
 *
 * This function sets the test mode for memory to control behavior of ECC and data bit accesses.
 * It is typically used for validating ECC logic and performing controlled memory tests.
 *
 * @param testMode   Test mode selection:
 *        - SDL_MEMSS_TESTMODE_NORMAL: Normal operation
 *        - SDL_MEMSS_TESTMODE_ECC_ONLY: ECC write mode
 *             Only ECC bits are written. ECC check on read is disabled.
 *        - SDL_MEMSS_TESTMODE_DATA_ONLY: Data write mode
 *             Only data bits are written. ECC check on read is disabled; reads return ECC bits.
 *        - SDL_MEMSS_TESTMODE_ECC_READ: Normal operation (functionally same as 0).
 *
 * @note
 * - Reset value: 0 (Normal operation).
 * - Reset source: CPU1.SYSRst
 *
 * Example:
 * @code
 * SDL_MEMSS_configureTestMode(memory,SDL_MEMSS_TESTMODE_ECC_ONLY); // Configure Data Write Mode
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_configTestMode")))
void SDL_MEMSS_configTestMode(SDL_MEMSS_RAM memory, SDL_MEMSS_TestMode mode);

 /**
 * @brief Perform ECC injection test on memory using MEMSS test modes.
 *
 * This function implements a diagnostic routine to inject faults into the memory system,
 * validating the ECC error detection and correction mechanisms supported by the CPU.
 *
 * It follows a sequence using the memory test modes as described in the TRM (section 3.10.7):
 * - Mode 0: Normal mode (both data and ECC are written)
 * - Mode 1: Data-only write (only data bits are updated; ECC check disabled)
 * - Mode 2: ECC-only write/read (only ECC bits are updated/read; data bits unchanged; ECC check disabled)
 *
 * The typical test flow:
 * 1. Write known data in mode 0 to store both data and ECC
 * 2. Switch to mode 1 to corrupt data bits (simulate data error)
 *    or mode 2 to corrupt ECC bits (simulate ECC error)
 * 3. Return to mode 0
 * 4. Read from the memory address to trigger ECC error detection by the CPU
 *
 * The CPU handles the ECC error response using its internal diagnostics and fault emulation logic.
 *
 * @note
 * - ECC check is performed in the CPU, not in the MEMSS controller.
 * - This test function is local to CPU1 memory accesses and does not affect other initiators.
 * - Test mode must be set per memory controller; it is not a global configuration.
 * - Ensure dataline buffering is disabled to prevent test data from being buffered during diagnostics.
 *
 * @return SDL_PASS on successful injection and test sequence,
 *         SDL_EFAIL if the operation or validation fails.
 *
 * @see SDL_MEMSS_configureTestMode()
 */
__attribute__((section(".text.link2.SDL_MEMSS_testECCInjection")))
int32_t SDL_MEMSS_testECCInjection(uint32_t errAggrBase, SDL_MEMSS_RAM memory,
                                   uint32_t *testAddr, SDL_MEMSS_TestMode testMode,
                                   uint32_t xorMask);

/**
 * @brief Enable write access to the memory configuration register.
 *
 * This function controls whether the memory configuration register is writable.
 * It is typically used to prevent accidental changes to memory test settings after configuration.
 *
 * @param memory
 *   Pointer to the SDL_MEMSS_RAM to be configured.
 *
 *
 * @note
 * - This bit can be modified only when the COMMIT bit is cleared.
 * - Default/reset value is 0 (write access allowed).
 * - Reset source: CPU1.SYSRst
 *
 * Example:
 * @code
 * SDL_MEMSS_lockConfig(memory);  // Lock configuration (no further writes allowed).
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_lockConfig")))
void SDL_MEMSS_lockConfig(SDL_MEMSS_RAM memory);

/**
 * @brief Disable write access to the memory configuration register.
 *
 * This function controls whether the memory configuration register is writable.
 * It is typically used to prevent accidental changes to memory test settings after configuration.
 *
 * @param enableWriteAccess
 *        - 1: Write access is *disabled* (modifications not allowed).
 *
 * @note
 * - This bit can be modified only when the COMMIT bit is cleared.
 * - Default/reset value is 0 (write access allowed).
 * - Reset source: CPU1.SYSRst
 *
 * Example:
 * @code
 * SDL_MEMSS_lockConfig(memory);  // Unlock configuration (writes allowed).
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_unlockConfig")))
void SDL_MEMSS_unlockConfig(SDL_MEMSS_RAM memory);

/**
 * @brief Permanently commit the memory configuration.
 *
 * This function locks the memory configuration by setting the commit bit. Once set,
 * this bit disables further modification of the memory configuration lock register.
 * It is a write-once bit and can only be cleared by a system reset.
 *
 * @param none
 *
 * @note
 * - 0: Configuration is modifiable.
 * - 1: Configuration is committed permanently and cannot be changed until reset.
 * - This is a write-once field; it cannot be cleared by software.
 * - Reset type: CPU1.SYSRst
 *
 * Example:
 * @code
 * SDL_MEMSS_commitConfig(memory); // Permanently commit configuration
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_commitConfig")))
void SDL_MEMSS_commitConfig(SDL_MEMSS_RAM memory);

/**
 * @brief Lock peripheral memory test control register.
 *
 * This function sets or clears the lock for the peripheral memory test control register.
 * When locked, write access to the control register is blocked.
 *
 * @param none
 *
 * @note
 * - 0: Write access to PERI_MEM_TEST_CONTROL is allowed.
 * - 1: Write access is blocked.
 * - This bit can only be cleared by a system reset.
 * - Reset type: CPU1.SYSRSn
 *
 * Example:
 * @code
 * SDL_MEMSS_lockPeriphMemTestRegister(); // Locks PERI_MEM_TEST_CONTROL register
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_lockPeriphMemTestRegister")))
void SDL_MEMSS_lockPeriphMemTestRegister(void);

 /**
 * @brief Unlock peripheral memory test control register.
 *
 * This function clears the lock for the peripheral memory test control register,
 * allowing write access to the control register if permitted by the hardware.
 *
 * @warning
 * - Depending on the hardware design, this unlock may not be possible via software
 *   if the lock bit can only be cleared by a system reset.
 * - Refer to the TRM: "This bit can only be cleared by a system reset."
 *
 * @param none
 *
 * @note
 * - 0: Write access to PERI_MEM_TEST_CONTROL is allowed.
 * - 1: Write access is blocked.
 * - If lock is permanent until reset, this function may not have any effect.
 *
 * Example:
 * @code
 * SDL_MEMSS_unlockPeriphMemTestRegister(); // Attempts to unlock PERI_MEM_TEST_CONTROL register
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_unlockPeriphMemTestRegister")))
void SDL_MEMSS_unlockPeriphMemTestRegister(void);

/**
 * @brief Force a parity error in the EtherCAT memory test path.
 *
 * This function sets or clears the error force bit for the EtherCAT parity checker.
 * When enabled (set to 1), the parity bit going to the EtherCAT parity checker module
 * is inverted, thus introducing a deliberate parity error.
 *
 * @param enable_error
 *        - 0: No effect (normal operation)
 *        - 1: Inverts parity bit to simulate a parity error
 *
 * @note Used for testing the parity error detection logic in EtherCAT.
 *       The bit is R/W and resets to 0 on CPU1.SYSRSn.
 *
 * Example:
 * @code
 * SDL_MEMSS_forceEtherCATParityError(true);  // Force parity error
 * SDL_MEMSS_forceEtherCATParityError(false); // Clear force error
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_forceEtherCATParityError")))
void SDL_MEMSS_forceEtherCATParityError(void);

/**
 * @brief Enable or disable the parity test feature.
 *
 * This function controls the parity test functionality. When enabled, the actual registers are hidden,
 * and parity result data becomes accessible in their place. This mode allows for parity checking
 * and error injection for testing.
 *
 * @param testen_value A 4-bit value to be written to the TESTEN field.
 *                     - 0xA (1010b): Parity test feature is enabled.
 *                     - All other values: Parity test feature is disabled.
 *
 * @note
 * (1) While enabled:
 *     - Actual registers are hidden from memory map.
 *     - Parity values (XOR result of memory data) are accessible.
 *     - You can inject parity errors by writing a '1' to the parity bit.
 * (2) Recommended to leave TESTEN as 0x5 or 0x0 after testing is complete.
 *
 * Reset type: CPU1.SYSRSn
 *
 * Example:
 * @code
 * SDL_MEMSS_enableParityTest(0xA); // Enable parity test mode
 * SDL_MEMSS_enableParityTest(0x0); // Disable parity test mode
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_CheckRegisterParity")))
int32_t SDL_MEMSS_checkRegisterParity(void);

/**
 * @brief Enable the parity test feature.
 *
 * This function enables the parity test functionality by writing 0xA to the TESTEN field.
 * In this mode, actual memory-mapped registers are hidden, and parity result data
 * (e.g., XOR of memory data) becomes accessible. You can also inject parity errors.
 *
 * @note
 * - TESTEN = 0xA (1010b) enables parity test mode.
 * - While enabled:
 *     - Actual registers are hidden.
 *     - You can view XOR parity values and inject parity errors.
 * - Remember to disable test mode after completion.
 *
 * Reset type: CPU1.SYSRSn
 *
 * Example:
 * @code
 * SDL_MEMSS_enableCheckRegisterParity(); // Enables parity test mode
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_enableCheckRegisterParity")))
void SDL_MEMSS_enableCheckRegisterParity(void);

/**
 * @brief Disable the parity test feature.
 *
 * This function disables the parity test functionality by writing 0x0 (or 0x5) to the TESTEN field.
 * This restores normal access to actual memory-mapped registers and stops any further
 * parity injection or observation.
 *
 * @note
 * - TESTEN = 0x0 or 0x5 disables parity test mode.
 * - Recommended to leave TESTEN at 0x0 or 0x5 after testing is done.
 *
 * Reset type: CPU1.SYSRSn
 *
 * Example:
 * @code
 * SDL_MEMSS_disableCheckRegisterParity(); // Disables parity test mode
 * @endcode
 */
__attribute__((section(".text.link2.SDL_MEMSS_disableCheckRegisterParity")))
void SDL_MEMSS_disableCheckRegisterParity(void);

/**
 *
 * \brief Handles ESM interrupts.
 *
 * This function handles ESM interrupts triggered by MEMSS tests.
 * When an interrupt occurs, the ESM triggers the ISR, which in turn calls this
 * function to appropriately handle the interrupt.
 *
 * Typically the user should not need to call this function directly.
 */
void SDL_MEMSS_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg);

#endif /* SDL_MEMSS_H */

/** @} */