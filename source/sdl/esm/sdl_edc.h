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
 *  \addtogroup sdl_esm_group
 *
 *  @{
 */

/**
 *  \file     sdl_edc.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of EDC.
 *            This also contains some related macros.
 */

#ifndef SDL_EDC_H_
#define SDL_EDC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <sdl_esm.h>
#include "sdlr_edc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SDL_EDC_PARITYCHECK_ENABLE                (uint32_t)(0x1U)
#define SDL_EDC_PARITYCHECK_DISABLE               (uint32_t)(0x0U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*!
 * @brief Represents different types of Data pattern.
 *
 * This enum defines the Data pattern to use for Error Injection.
 */
typedef enum
{
    SDL_EDC_PATTERN_D0 = 0x0U,  /*!< Data Pattern with all 0s. */
    SDL_EDC_PATTERN_DF = 0x1U,  /*!< Data Pattern with all Fs. */
    SDL_EDC_PATTERN_DA = 0x2U,  /*!< Data Pattern with all As. */
    SDL_EDC_PATTERN_D5 = 0x3U   /*!< Data Pattern with all 5s. */
} SDL_EDC_Pattern;

/*!
 * @brief Represents Bit type.
 *
 * This enum defines bit type for Error Injection.
 */
typedef enum
{
    SDL_EDC_FORCE_SINGLEBIT_ERROR = 0x1U, /*!< Force Single Bit Error Injection. */
    SDL_EDC_FORCE_DOUBLEBIT_ERROR = 0x2U  /*!< Force Double Bit Error Injection. */
} SDL_EDC_BitSize;

/*!
 * @brief Represents After Injection Setting.
 *
 * This enum defines whether to keep current or incremental settings
 * after Error Injection.
 */
typedef enum
{
    SDL_EDC_FORCE_CURRSETTG_AFTINJ = 0x0U,  /*!< keep Current Settings After Injection. */
    SDL_EDC_FORCE_INC_NXTBIT_AFTINJ = 0x1U  /*!< Increment to next Bit or Group After Injection. */
} SDL_EDC_AfterInject;

/*!
 * @brief Represents EDC Control.
 *
 * This enum defines EDC Control Register settings.
 */
typedef struct {
    SDL_EDC_Pattern pattern;          /*!< Data pattern to use for Injection. */
    SDL_EDC_AfterInject forceNBit;    /*!< Injection Field Setting. */
    SDL_EDC_BitSize forceBitError;    /*!< Error Bit size (Single or Double). */
    uint32_t enableParityChecker;     /*!< Parity Checker enabler. */
}SDL_EDC_CtrlReg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used to Enable the Parity Checker.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 * 
 * \param   edcCtrlReg      structure to pass the required configurations refer #SDL_EDC_CtrlReg
 * 
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr  = SDL_ESMSAFETYAGG_BASE;
       int32_t                retVal;
       retVal = SDL_EDC_setControlReg(baseAddr, edcCtrlReg);

   @endverbatim
 *
 */
int32_t SDL_EDC_setControlReg(uint32_t safetyAggrBase, SDL_EDC_CtrlReg edcCtrlReg);

/**
 * \brief   This API is used to get the Parity checker Status.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   pStatus       pointer to Status of the ECC checker
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               pStatus;
       int32_t                retVal;
       retVal = SDL_EDC_getParityCheckerStatus(baseAddr, &pStatus);

   @endverbatim
 *
 */
int32_t SDL_EDC_getParityCheckerStatus(uint32_t safetyAggrBase, uint32_t *pStatus);

/**
 * \brief   This API is used to get the data Pattern Status.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   pStatus         pointer to Status of the data pattern
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               pStatus;
       int32_t                retVal;
       retVal = SDL_EDC_getParityPattern(baseAddr, &pStatus);

   @endverbatim
 *
 */
int32_t SDL_EDC_getParityPattern(uint32_t safetyAggrBase, uint32_t *pStatus);

/**
 * \brief   This API is used to set the value of Group Number to inject in the EDC Error1 Reg.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   groupNum        Group Number to the checker to inject the error
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               groupNum = 0x1U;
       int32_t                retVal;
       retVal = SDL_EDC_injectErr1GroupNum(baseAddr, groupNum);

   @endverbatim
 *
 */
int32_t SDL_EDC_injectErr1GroupNum(uint32_t safetyAggrBase, uint32_t groupNum);

/**
 * \brief   This API is used to set the first bit to inject an error to the EDC Error1 Reg.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   bitIndex        First bit to inject the error
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               bitIndex = 0x1U;
       int32_t                retVal;
       retVal = SDL_EDC_injectBitErr(baseAddr, bitIndex);

   @endverbatim
 *
 */
int32_t SDL_EDC_injectBitErr(uint32_t safetyAggrBase, uint32_t bitIndex);

/**
 * \brief   This API is used to set the second bit to inject an error to the EDC Error2 Reg.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   bitIndex        Second bit to inject the error
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               bitIndex = 0x1U;
       int32_t                retVal;
       retVal = SDL_EDC_injectDoubleBitErr(baseAddr, bitIndex);

   @endverbatim
 *
 */
int32_t SDL_EDC_injectDoubleBitErr(uint32_t safetyAggrBase, uint32_t bitIndex);

/**
 * \brief   This API is used to get the Error1 Status.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   errStatus       pointer to Status of Error1 status
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               errStatus;
       int32_t                retVal;
       retVal = SDL_EDC_getErr1Status(baseAddr, &errStatus);

   @endverbatim
 *
 */
int32_t SDL_EDC_getErr1Status(uint32_t safetyAggrBase, uint32_t *errStatus);

/**
 * \brief   This API is used to set the Error1 Status
 *          to increment/decrement the pending interrupts.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   statusVal       Value to decrement the pending interrupts
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr = SDL_ESMSAFETYAGG_BASE;
       uint32_t               statusVal = 0x1U;
       int32_t                retVal;
       retVal = SDL_EDC_setErr1Status(baseAddr, statusVal);

   @endverbatim
 *
 */
int32_t SDL_EDC_setErr1Status(uint32_t safetyAggrBase, uint32_t statusVal);

/**
 * \brief   This API is used to get the Error2 Status.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   errStatus       pointer to Status of Error2 status
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr = SDL_ESMSAFETYAGG_BASE;
       uint32_t               errStatus;
       int32_t                retVal;
       retVal = SDL_EDC_getErr2Status(baseAddr, &errStatus);

   @endverbatim
 *
 */
int32_t SDL_EDC_getErr2Status(uint32_t safetyAggrBase, uint32_t *errStatus);

#ifdef __cplusplus
}
#endif /*extern "C" */

#endif /* SDL_EDC_H_ */

/** @} */