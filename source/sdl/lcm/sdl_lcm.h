/********************************************************************
 * Copyright (C) 2025 Texas Instruments Incorporated.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
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
 *
 */

#ifndef SDL_LCM_H
#define SDL_LCM_H

/*****************************************************************************
 *
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 *
 *****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Includes
 */

#include "sdlr_lcm.h"
#include <include/hw_types.h>
#include <include/sdlr_baseaddress.h>
#include <include/sdl_types.h>
#include <include/sdlr_sysctl.h>

/**
 *
 * \addtogroup sdl_lcm_group
 *
 * @{
 *
 */

/*
 * Defines
 */

#define SDL_LCM_NO_INTERRUPT (0U)
#define SDL_LCM_INTERRUPT (1U)

/*
 * Prototypes
 */

/**
 *
 * \brief Checks the LCM register parity logic.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 *
 * This function performs a test of the MMR parity logic, using the parity
 * error test functionality in LCM. An error is injected into a byte in each
 * parity-protected LCM register and the function confirms that ESM will
 * raise an interrupt if there is any error.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_checkRegisterParity(uint32_t lcmBase);

/**
 *
 * \brief Runs the LCM self-test.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 *
 * This function performs a self-test of the LCM using the built-in self-test
 * capability. The self-test is kicked off and the function waits for it to
 * complete. If the self-test times out or the LCM_STATUS registers indicate
 * that the self-test did not complete and pass, the test fails.
 *
 * This test can be run either before or after LCM_CONTROL.CMPEN is set.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_runSelfTest(uint32_t lcmBase);

/**
 *
 * \brief Checks LCM compare error force.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 *
 * This function performs a test of the error signaling path between the LCM
 * and the error aggregation logic. For each of the LCM comparators (referred
 * to as CMP1 and CMP2) an error is forced and the function confirms that ESM
 * will raise and handle the interrupt.
 *
 * If not already set by the software, this test sets LCM_CONTROL.CMPEN.
 *
 * \note This function will generate an error if there are any disparity and
 * ESM will handle the error by raising an interrupt.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_checkCompareError(uint32_t lcmBase);

/**
 *
 * \brief Enables the Lockstep module.
 *
 * This function Enables the lockstep functionality of LCM if it got disabled
 * by any software function.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL
 *
 */
int32_t SDL_LCM_enableLockstep(void);

/**
 *
 * \brief Disables the Lockstep module.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 *
 * This function Disables the lockstep functionality of LCM for the systems that
 * do not require the redundant module output for comparison in functional safety
 * requirements, the LCM redundant module can be used for functional output.
 *
 * To change the LCM comparators configuration upon device startup or after reset,
 * this function must be called at the beginning of the user application code
 *
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_disableLockstep(uint32_t lcmBase);

/**
 *
 * \brief Enables the LCM comparators.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 *
 * This function Enables the LCM comparators which are disabled by default or
 * any software function.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_enableComparator(uint32_t lcmBase);

/**
 *
 * \brief disables the LCM comparators.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 *
 * This function Disables the LCM comparators which are enabled by default or
 * by any software function.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_disableComparator(uint32_t lcmBase);

/**
 *
 * \brief Fetches the status register.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 * \param pStatus is the buffer to store the LCM status register's contents.
 *
 * This function fetches or copies the LCM status register's contents.
 *
 * User program can use this data to get the status of any particular
 * field of the status register.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_getStatus(uint32_t lcmBase, uint32_t *pStatus);

/**
 *
 * \brief Clears the status of a field in the status register.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 * \param clearStatus is the particular bit in register.
 *
 * This function clears or reset a particular bit in the status register.
 *
 * User program can pass the particular bit to this API to clear the status.
 *
 * It uses the LCM status clear register for it. If hardware is trying to set
 * the flag and software is trying to clear the same flag in the same cycle,
 * software clear is given higher priority
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_clearStatus(uint32_t lcmBase, uint32_t clearStatus);

/**
 *
 * \brief Locks a particular register's configuration.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 * \param lcmRegs is the particular bit in register.
 *
 * This function locks or set a particular register's configurations by setting
 * the appropriate bit in the lock register.
 *
 * User program can pass the particular bit to this API to lock the status or
 * configurations of the register.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_lockRegister(uint32_t lcmBase, uint32_t lcmRegs);

/**
 *
 * \brief Unlocks a particular register's configuration.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 * \param lcmRegs is the particular bit in register.
 *
 * This function unlocks or resets a particular register's configurations by
 * resetting the appropriate bit in the lock register.
 *
 * User program can pass the particular bit to this API to unlock the status or
 * configurations of the register.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid.
 *
 */
int32_t SDL_LCM_unlockRegister(uint32_t lcmBase, uint32_t lcmRegs);

/**
 *
 * \brief Commits register lock configurations in the commit register.
 *
 * \param lcmBase is the particular baseaddress(CPU/DMA) of the LCM module.
 * \param lcmRegs is the particular bit in register.
 *
 * This function Commits or set a particular bit for a particular Register lock
 * configuration in the commit register.
 *
 * Once configuration is committed, only reset can change the configuration.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the baseaddress
 * is invalid
 *
 */
int32_t SDL_LCM_commitRegister(uint32_t lcmBase, uint32_t lcmRegs);

/**
 *
 * \brief Handles ESM interrupts.
 * 
 * This function handles ESM interrupts triggered by LCM tests.
 * When an interrupt occurs, the ESM triggers the ISR, which in turn calls this 
 * function to safely and appropriately handle the interrupt.
 *
 */
void SDL_LCM_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg);

/** @} */

/*****************************************************************************
 *
 * Mark the end of the C bindings section for C++ compilers.
 *
 *****************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* STL_LCM_H */

