/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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
 */

/**
 * \addtogroup sdl_esm_group
 *
 * @{
 */

/**
 * \file  sdl_esm.h
 *
 * \brief
 *  Header file contains enumerations, structure definitions and function
 *  declarations for SDL Error Signaling Module interface.
 *
 *  The SDL ESM enumerations include:
 *      1. SDL ESM interrupt types
 *      2. SDL ESM interrupt sources
 *      3. SDL ESM Watchdog Timer IDs
 *
 *
 *  The SDL ESM data structures include:
 *      1. Structure of the ESM error configuration
 *      2. Structure of the initial ESM configuration
 *
 *  The SDL ESM APIs include:
 *      1. API to initialize the SDL ESM
 *      2. APIs to set/reset nERROR pin
 *      3. API to get nERROR pin status
 *      4. API to insert an ESM error
 *      5. API to execute self test of ESM module
 *      6. APIs to handle ESM high priority/low priority/config interrupts
 *      7. API to get ESM Interrupt Number corresponding to the input ESM interrupt type
 *      8. Application provided external callback function for ESM handling
 */

#ifndef SDL_ESM_H_
#define SDL_ESM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sdl_ip_esm.h"
#include <include/sdlr_intr_esm.h>
#include <include/sdlr_baseaddress.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Invalid ESM Instance */
#define SDL_ESM_INST_INVALID                   (0xFFFFFFFEU)

/** \brief Address field: Error Address invalid */
#define SDL_ESM_ERRORADDR_INVALID              ((uint32_t)0xFFFFFFFFU)

/** \brief Event number for when there's no pending event */
#define SDL_ESM_NO_EVENT_VALUE                 ((uint32_t)(0xFFFFU))

#define SDL_ESM_MASK_BIT                       ((uint32_t)(1U))

typedef void (* SDL_ESM_SelfTestCallback)(uint32_t esmBase,
                                          uint32_t intSrc,
                                          void *callbackArg);

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief This enumerator defines the values for ESM interrupt types
 */
typedef enum {
    SDL_ESM_INT_TYPE_LO = 0x1U,
    /**< Interrupt type Low  */
    SDL_ESM_INT_TYPE_HI = 0x2U,
    /**< Interrupt type High  */
    SDL_ESM_INT_TYPE_MAX = 0x3U
    /**< Interrupt type Max  */
} SDL_ESM_IntType;

/**
 * \brief Defines the different ESM instance types
 */
typedef enum {
   SDL_ESM_CPU1_INST_ESM = 0x1U,
    /**< ESM_CPU1 instance  */
   SDL_ESM_CPU2_INST_ESM = 0x2U,
    /**< ESM_CPU2 instance  */
   SDL_ESM_CPU3_INST_ESM = 0x3U,
    /**< ESM_CPU3 instance  */
   SDL_ESM_SYSTEM_INST_ESM = 0x4U,
    /**< ESM_SYSTEM instance  */
} SDL_ESM_Inst;

/**
 * \brief ESM init configuration
 *
 * This structure defines ESM Init configuration
 */
typedef struct SDL_ESM_InitConfig_s
{
    /**< Error event to be used for self test */
    uint32_t enableBitmap[SDL_ESM_NUM_EVENT_GROUPS];
    /**< ESM Event bitmap */
    uint32_t priorityBitmap[SDL_ESM_NUM_EVENT_GROUPS];
    /**< ESM Event Priority bitmap */
    uint32_t errorPinBitmap[SDL_ESM_NUM_EVENT_GROUPS];
    /**< ESM bitmap for driving error pin: When selected error event occurs
     *  the error output pin will be asserted
     *  It is the application responsibility to reset the error
     *  if the system did not crash or lockup */
} SDL_ESM_Config;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *
 * \brief   ESM Low Priority Interrupt Handler
 *
 * \param [in]  esmBase: Base Address of the ESM Registers.
 * \param [out] intrStatus: Pointer to an object to hold interrupt status.
 *
 * SDL ESM interrupt handler function that should be called from the user's
 * low priority ESM interrupt ISR. The routine will get the interrupt status
 * then process the interrupt, calling any registered self-test callbacks if
 * self-test is active and then clearing the source ESM event and ESM EOI.
 *
 * The returned interrupt status can be used to determine if the interrupt was
 * expected (self-test was active) or indicative of an unexpected error. It also
 * returns the status of any additional pending interrupts. In the user's ISR,
 * you can optionally call this handler until the "nextPend" events return the
 * \b SDL_ESM_NO_EVENT_VALUE value.
 *
 * \return  SDL_PASS if successfully executed.
 *          SDL_EBADARGS if base address or status pointer are invalid.
 */
int32_t SDL_ESM_loInterruptHandler(uint32_t esmBase, SDL_ESM_IntrStatus *intrStatus);

/**
 *
 * \brief   ESM High Priority Interrupt (NMI) Handler
 *
 * \param [in]  esmBase: Base Address of the ESM Registers.
 * \param [out] intrStatus: Pointer to an object to hold interrupt status.
 *
 * SDL ESM interrupt handler function that should be called from the user's
 * high priority ESM interrupt (NMI) ISR. The routine will get the interrupt status
 * then process the interrupt, calling any registered self-test callbacks if
 * self-test is active and then clearing the source ESM event and ESM EOI.
 *
 * The returned interrupt status can be used to determine if the interrupt was
 * expected (self-test was active) or indicative of an unexpected error. It also
 * returns the status of any additional pending interrupts. In the user's ISR,
 * you can optionally call this handler until the "nextPend" events return the
 * \b SDL_ESM_NO_EVENT_VALUE value.
 *
 * \return  SDL_PASS if successfully executed.
 *          SDL_EBADARGS if base address or status pointer are invalid.
 */
int32_t SDL_ESM_hiInterruptHandler(uint32_t esmBase, SDL_ESM_IntrStatus *intrStatus);

/**
 *
 * \brief Set the self-test status for the current CPU ESM instance
 *
 * \param selfTestStatus: Self-test status is \b SDL_ESM_SELF_TEST_ACTIVE if
 *        a self-test is active or \b SDL_ESM_SELF_TEST_NONE if not.
 *
 * This flag is used to signal to the ESM interrupt handler that a self-test
 * is active and the self-test callback should be called. A copy of the status
 * is also returned to the user to indicate whether the ESM event was caused by
 * a self-test or if it is an unexpected error.
 *
 * \return None
 */
void SDL_ESM_setSelfTestStatus(SDL_ESM_SelfTestStatus selfTestStatus);

/**
 *
 * \brief Returns the stored self-test status for the current CPU ESM instance
 *
 * \return Returns self test status (either \b SDL_ESM_SELF_TEST_ACTIVE
 *         or \b SDL_ESM_SELF_TEST_NONE).
 */
SDL_ESM_SelfTestStatus SDL_ESM_getSelfTestStatus(void);

/**
 *
 * \brief Sets the self-test callback function for the current CPU ESM instance
 *
 * \param callback:    A pointer to a callback function to be called in the ISR when
 *                     the self-test status is set to \b SDL_ESM_SELF_TEST_ACTIVE.
 * \param callbackArg: A pointer to an optional callback argument.
 *
 * \return
 */
void SDL_ESM_setSelfTestCallback(SDL_ESM_SelfTestCallback callback,
                                 void *callbackArg);

/**
 *
 * \brief Clears the self-test callback function for the current CPU ESM instance
 *
 * \param None
 *
 * This function "clears" the ESM instance self-test callback by setting it to
 * a default callback function that does nothing.
 *
 * \return None
 */
void SDL_ESM_clearSelfTestCallback(void);

/**
 *
 * \brief   SDL ESM API to get the status of the nError pin for the specified
 *          ESM instance
 *
 * \param   esmBase: Base Address of the ESM Registers.
 * \param   pStatus: Pointer to variable to store the status.
 *                   If status is 1, then error pin is not active.
 *                   If status is 0, then error pin is active.
 *
 * \return  SDL_PASS if nError pin status is successfully retrieved.
 *          SDL_EBADARGS if instance or pStatus pointer are invalid.
 *          SDL_EFAIL if fail to read the error pin.
 */
int32_t SDL_ESM_getNErrorStatus(uint32_t esmBase, uint32_t *pStatus);

/**
 *
 * \brief   SDL ESM API to read the static registers. The API reads and returns
 *          the static register configuration for the ESM module for the specified
 *          instance. This API can be used by the application to read back the
 *          static configuration. Comparision of the static configuration registers
 *          against expected values is the responsibility of the application.
 *
 * \param   esmBase: Base Address of the ESM Registers.
 * \param   pStaticRegs: Pointer to the static config register structure
 *
 * \return  SDL_PASS if registers are successfully read.
 *          SDL_EBADARGS if instance or pStaticRegs are invalid.
 */
int32_t SDL_ESM_getStaticRegisters(uint32_t esmBase, SDL_ESM_StaticRegs *pStaticRegs);

/**
 *
 * \brief   SDL ESM API to verify the written configuration of the ESM module.
 *          The API verifies the written config that was done during SDL_ESM_init
 *          against the provided configuration.
 *
 * \param   esmBase: Base Address of the ESM Registers.
 * 
 * \param   pConfig: Pointer to the ESM configuration to be used for verification.
 *
 * \return  SDL_PASS if Verification passed
 *          SDL_EBADARGS if instance or pConfig are invalid.
 *          SDL_EFAIL if verification failed.
 */
int32_t SDL_ESM_verifyConfig(uint32_t esmBase, const SDL_ESM_Config *pConfig);

/**
 *
 * \brief   SDL ESM API to clear the nError pin for the specified ESM instance
 *
 * \param   esmBase: Base Address of the ESM Registers.
 *
 * \return  SDL_PASS if nError pin status is successfully cleared.
 *          SDL_EBADARGS if instance is invalid.
 */
int32_t SDL_ESM_clearNError(uint32_t esmBase);

/**
 *
 * \brief   SDL ESM API to set the nError pin for the specified ESM instance
 *
 * \param   esmBase: Base Address of the ESM Registers.
 *
 * \return  SDL_PASS if nError pin status is successfully set.
 *          SDL_EBADARGS if instance is invalid.
 */
int32_t SDL_ESM_setNError(uint32_t esmBase);

/**
 * \brief   This API is use to set error pin out mode(LEVEL or PWM).
 *          This API must be called after the below API- #SDL_ESM_init
 *
 * \param   esmBase: Base Address of the ESM Registers.
 *
 * \param   pinOutSignal    enum value to select error pin out signal.
 *                          Refer enum #SDL_ESM_ErrPinOutSignal.
 *
 * \return                  SDL_PASS - API success
 *                          SDL_EBADARGS  - Instance is not valid.
 *                          SDL_EFAIL     - Output (LVL or PWM) is not changed.
 *
 */
int32_t SDL_ESM_setPinOutSignalMode(uint32_t esmBase, SDL_ESM_ErrPinOutSignal pinOutSignal);

/**
 *
 * \brief   SDL ESM API to initialize an ESM instance. The API initializes the
 *          specified ESM instance with the provided configuration. The
 *          configuration will allow the application to specify for each event
 *          whether the interrupt is enabled or disabled, the priority of the
 *          event, and whether the nErrorPin assertion is enabled or disabled for
 *          the event.
 *
 * \param   esmBase: Base Address of the ESM Registers.
 * \param   pConfig: Pointer to the ESM configuration structure
 *
 * \return  SDL_PASS if success.
 *          SDL_EBADARGS if invalid argument is passed.
 *          SDL_EFAIL if other failure.
 */
int32_t SDL_ESM_init(uint32_t esmBase, const SDL_ESM_Config *pConfig);

/** @} */

#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* SDL_ESM_H_ */
