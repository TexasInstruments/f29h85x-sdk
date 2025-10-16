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

#ifndef SDL_SYSCTL_H
#define SDL_SYSCTL_H

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

#include <include/hw_types.h>
#include <include/sdlr_baseaddress.h>
#include <include/sdl_types.h>
#include <include/sdlr_sysctl.h>

/**
 *
 * \addtogroup sdl_sysctl_group
 *
 * @{
 *
 */

/*
 * Defines
 */

#define SDL_SYSCTL_NO_INTERRUPT (0U)
#define SDL_SYSCTL_INTERRUPT (1U)

/* SDL_SYSCTL_PARITY_TEST Bit Fields in SYSCTL_PARITY_TEST Register */
#define SDL_SYSCTL_PARITY_TEST_KEY          0xAU   /* Parity test enable */
#define SDL_SYSCTL_WD_WINDOW                0x20U
#define SDL_SYSCTL_WD_ENRSTKEY              0x0055U
#define SDL_SYSCTL_WD_RSTKEY                0x00AAU
#define SDL_SYSCTL_SYNCBUSY_TIMEOUT_CYCLES  10000U

/* Shifted pattern for WDCR register's WDCHK field.*/
#define SDL_SYSCTL_WD_CHKBITS       0x0028U

/*
 * Prototypes
 */

/**
 *
 * \brief Checks the DEVCFG register parity logic.
 *
 * This function performs a test of the parity test feature, using the parity
 * error test functionality in DEVCFG register. An error is injected into a byte in each
 * parity-protected DEVCFG register and the function confirms that ESM will
 * raise an interrupt if there is any error.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
int32_t SDL_SYSCTL_checkDEVCFGParity(void);

/**
 *
 * \brief Checks the CPUSYS register parity logic.
 *
 * This function performs a test of the parity test feature, using the parity
 * error test functionality in CPUSYS register. An error is injected into a byte in each
 * parity-protected CPUSYS register and the function confirms that ESM will
 * raise an interrupt if there is any error.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
int32_t SDL_SYSCTL_checkCPUSYSParity(void);

/**
 *
 * \brief Checks the CPUPERCFG register parity logic.
 *
 * This function performs a test of the parity test feature, using the parity
 * error test functionality in CPUPERCFG register. An error is injected into a byte in each
 * parity-protected CPUPERCFG register and the function confirms that ESM will
 * raise an interrupt if there is any error.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
int32_t SDL_SYSCTL_checkCPUPERCFGParity(void);

/**
 *
 * \brief Checks the Missing Clock Detection feature.
 *
 * This function performs test of MCD(Missing Clock Detection) features in SYSCTL by
 * Simulating a missing clock and makes sure it switches to the secondary clock.
 * The interrupt caused by MCD takes care of Re-connecting missing clock detection
 * to clock source to stop simulating clock failure.
 * User needs to initialise their clock after testing this feature.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
int32_t SDL_SYSCTL_checkMCD(void);

/**
 *
 * \brief Tests the WATCHDOG Timeout functionality.
 *
 * This function performs test of watchdog timeout feature by setting the watchdog to generate an
 * interrupt signal instead of a reset signal in the WATCHDOG. This function will change the states
 * of the Watchdog registers, it is advisable to save the contents of the registers before calling this
 * function and restore after testing the feature.
 * Note: This function is paired with \b SDL_SYSCTL_checkWDResult So, to check the result of this function
 * we need to call it.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
int32_t SDL_SYSCTL_checkWDTimeout(void);

/**
 *
 * \brief Checks the WATCHDOG Timeout result.
 *
 * This function checks if the ISR got called after the test of watchdog timeout feature,
 * basically it checks the wakeISRFlag if it got set or not.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
int32_t SDL_SYSCTL_checkWDResult(void);

/**
 *
 * \brief Tests the WATCHDOG Window functionality.
 *
 * This function performs test of watchdog window feature, it sets the lower boundary of
 * the watchdog window by resetting the watchdog before it has a chance to reach the window
 * threshold.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
int32_t SDL_SYSCTL_checkWDWindow(void);

/**
 *
 * \brief Handles ESM interrupts.
 *
 * This function handles ESM interrupts triggered by SYSCTL tests.
 * When an interrupt occurs, the ESM triggers the ISR, which in turn calls this
 * function to safely and appropriately handle the interrupt.
 *
 */
void SDL_SYSCTL_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg);

/**
 *
 * \brief Handles watchdog interrupt.
 *
 * This function should be called from the watchdog interrupt to handle the
 * interrupt.
 */
void SDL_SYSCTL_handleWDIntr(void);

/** @} */

/*****************************************************************************
 *
 * Mark the end of the C bindings section for C++ compilers.
 *
 *****************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* SDL_SYSCTL_H */
