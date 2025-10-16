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
 *  \file     sdl_esm_safety_aggr.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of ESM Safety Aggregator.
 *            This also contains some related macros.
 */

#ifndef SDL_ESM_SAFETY_AGGR_H_
#define SDL_ESM_SAFETY_AGGR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sdlr_esm_safety_aggr.h"
#include <include/sdl_types.h>
#include <include/hw_types.h>
#include <sdl_esm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SDL_ESM_SAFETYAGGR_INTR_PARITYERR_EN      (0x0U)
#define SDL_ESM_SAFETYAGGR_INTR_TIMEOUTERR_EN     (0x1U)
#define SDL_ESM_SAFETYAGGR_INTR_PARITYERR_DIS     (0x2U)
#define SDL_ESM_SAFETYAGGR_INTR_TIMEOUTERR_DIS    (0x3U)
#define SDL_ESM_SAFETYAGGR_INTR_MAX_COUNT         (0x3U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Structure for accessing Revision of ESM Safety Aggregator module.
 */
typedef struct sdlesmSafetyAggrRev
{
    uint32_t scheme;
    /**< Scheme */
    uint32_t bu;
    /**< Business Unit */
    uint32_t moduleID;
    /**< Module ID */
    uint32_t rtlVer;
    /**< RTL Version */
    uint32_t majorVer;
    /**< Major Version */
    uint32_t customVer;
    /**< Custom Version */
    uint32_t minorVer;
    /**< Minor Version */
}SDL_ESM_SAFETYAGGR_Rev;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used to get the Safety Aggregator Revision Reg.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   revReg          Struture which stored the Aggregator Revision values
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

       uint32_t               safetyAggrBase = SDL_ESMSAFETYAGG_BASE;
       SDL_ESM_SAFETYAGGR_Rev revReg;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getRevision(safetyAggrBase, &revReg);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getRevision(uint32_t safetyAggrBase, SDL_ESM_SAFETYAGGR_Rev *revReg);

/**
 * \brief   This API is used to Clear the SV bus read complete bit.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_clearSvBusStatus(safetyAggrBase);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_clearSvBusStatus(uint32_t safetyAggrBase);

/**
 * \brief   This API is used to pass the SV bus Address to read.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 * 
 * \param   busAddr         SvBus Address to read
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
       uint32_t               busAddr;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_SvBusAddrtoRead(baseAddr, busAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_SvBusAddrtoRead(uint32_t safetyAggrBase, uint32_t busAddr);

/**
 * \brief   This API is used to get the status of SV serial bus.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   readStatus      Pointer to the status of Serial bus
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

       uint32_t               safetyAggrBase = SDL_ESMSAFETYAGG_BASE;
       uint32_t               readStatus;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getSvBusStatus(safetyAggrBase, &readStatus);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getSvBusStatus(uint32_t safetyAggrBase, uint32_t *readStatus);

/**
 * \brief   This API is used to pass the SV serial bus address to read the data.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   busAddr         the address of to read the data
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

       uint32_t               safetyAggrBase = SDL_ESMSAFETYAGG_BASE;
       uint32_t               busAddr;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_SvBusAddrtoRead(safetyAggrBase, busAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_SvBusAddrtoRead(uint32_t safetyAggrBase, uint32_t busAddr);

/**
 * \brief   This API is used to get the SV serial bus address.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   busAddr         Pointer which stores the address of SV bus
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

       uint32_t               safetyAggrBase = SDL_ESMSAFETYAGG_BASE;
       uint32_t               busAddr;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getSvBusAddr(safetyAggrBase, &busAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getSvBusAddr(uint32_t safetyAggrBase, uint32_t *busAddr);

/**
 * \brief   This API is used to Trigger the read on the SV serial bus.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_triggerSvBusRead(safetyAggrBase);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_triggerSvBusRead(uint32_t safetyAggrBase);

/**
 * \brief   This API is used to Config the ESM Instance for control and status.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   esmInst         ESM Instance
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

       uint32_t               safetyAggrBase = SDL_ESMSAFETYAGG_BASE;
       uint32_t               esmInst = SDL_ESM_CPU1_INST_ESM;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_configECCVectESMInst(safetyAggrBase, esmInst);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_configECCVectESMInst(uint32_t safetyAggrBase, uint32_t esmInst);

/**
 * \brief   This API is used to set the Aggregator EOI Reg.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_setDEDEOIReg(safetyAggrBase);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_setDEDEOIReg(uint32_t safetyAggrBase);

/**
 * \brief   This API is used to get the value/status of Aggregator EOI Reg.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   regVal          pointer to the status of EOI reg
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               regVal;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getDEDEOIReg(safetyAggrBase, &regVal);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getDEDEOIReg(uint32_t safetyAggrBase, uint32_t *regVal);

/**
 * \brief   This API is used to get the status of pending Interrupts.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   pStatus         pointer to the status of pending interrupts
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               pStatus;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getPendingIntrStatus(safetyAggrBase, &pStatus);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getPendingIntrStatus(uint32_t safetyAggrBase, uint32_t *pStatus);

/**
 * \brief   This API is used to enable the Interrupt Enable reg for
 *          the mentioned ESM Instances.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   enableIntrESM   ESM Instance
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               enableIntrESM = SDL_ESM_CPU1_INST_ESM;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_enableEDCIntr(safetyAggrBase, enableEDC);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_enableEDCIntr(uint32_t safetyAggrBase, SDL_ESM_Inst enableIntrESM);

/**
 * \brief   This API is used to clear the Interrupt Enable reg for
 *          the mentioned ESM Instances.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   disIntrESM      ESM Instance
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               disIntrESM = SDL_ESM_CPU1_INST_ESM;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_disableEDCIntr(safetyAggrBase, disIntrESM);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_disableEDCIntr(uint32_t safetyAggrBase, SDL_ESM_Inst disIntrESM);

/**
 * \brief   This API is used to Enable the Aggregator error type.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   numInst         Number of ESM Instances serviced by the Safety Affregator
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               numInst;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getESMInstCntStatus(safetyAggrBase, &numInst);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getESMInstCntStatus(uint32_t safetyAggrBase, uint32_t *numInst);

/**
 * \brief   This API is used to Enable the Aggregator error type.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   intrDisable     SDL_ESM_SAFETYAGGR_INTR_PARITYERR_EN - Enable parity error
 *                          SDL_ESM_SAFETYAGGR_INTR_TIMEOUTERR_EN - Enable timeout error
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               intrEnable = SDL_ESM_SAFETYAGGR_INTR_PARITYERR_EN;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_enableAggrIntrErr(safetyAggrBase, intrEnable);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_enableAggrIntrErr(uint32_t safetyAggrBase, uint32_t intrEnable);

/**
 * \brief   This API is used to disable the Aggregator error type.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   intrDisable     SDL_ESM_SAFETYAGGR_INTR_PARITYERR_DIS - disable parity error
 *                          SDL_ESM_SAFETYAGGR_INTR_TIMEOUTERR_DIS - disable timeout error
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               intrDisable = SDL_ESM_SAFETYAGGR_INTR_PARITYERR_DIS;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_disableAggrIntrErr(safetyAggrBase, intrDisable);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_disableAggrIntrErr(uint32_t safetyAggrBase, uint32_t intrDisable);

/**
 * \brief   This API is used to set the number of Parity Errors.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   parityErr       Value of parity Errors to be set
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               parityErr = 2U;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_setAggrParityErr(safetyAggrBase, parityErr);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_setAggrParityErr(uint32_t safetyAggrBase, uint32_t parityErr);

/**
 * \brief   This API is used to set the number of timeout Errors.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   timeoutErr      Value of timeout Errors to be set
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               timeoutErr= 2U;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_setAggrTimeoutErr(safetyAggrBase, timeoutErr);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_setAggrTimeoutErr(uint32_t safetyAggrBase, uint32_t timeoutErr);

/**
 * \brief   This API is used to get the number of Parity Errors Occured.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   pErrStatus      Value of parity Errors occured
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               pErrStatus;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getAggrParityErrStatus(safetyAggrBase, &pErrStatus);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getAggrParityErrStatus(uint32_t safetyAggrBase, uint32_t *pErrStatus);

/**
 * \brief   This API is used to get the number of Timeout Errors Occured.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   timeoutErr      Value of timeout Errors occured
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               tErrStatus;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getAggrTimeoutErrStatus(safetyAggrBase, &tErrStatus);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getAggrTimeoutErrStatus(uint32_t safetyAggrBase, uint32_t *tErrStatus);

/**
 * \brief   This API is used to get the status of Aggregator Interrupt clear Register.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   clearStatus     pointer to the Value of the clear status register
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               clearStatus;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_getAggrClearStatus(safetyAggrBase, &clearStatus);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_getAggrClearStatus(uint32_t safetyAggrBase, uint32_t *clearStatus);

/**
 * \brief   This API is used to clear that many Aggregator Parity Error.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   parityErr       Number of parity Error to be cleared
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               parityErr = 1U;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_clearAggrParityErr(safetyAggrBase, parityErr);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_clearAggrParityErr(uint32_t safetyAggrBase, uint32_t parityErr);

/**
 * \brief   This API is used to clear that many Aggregator Timeout Error.
 *
 * \param   safetyAggrBase  ESM Safety Aggregator base address.
 *
 * \param   timeoutErr      Number of timeout Error to be cleared
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

       uint32_t               safetyAggrBase  = SDL_ESMSAFETYAGG_BASE;
       uint32_t               timeoutErr = 1U;
       int32_t                retVal;
       retVal = SDL_ESM_SAFETYAGGR_clearAggrTimeoutErr(safetyAggrBase, timeoutErr);

   @endverbatim
 *
 */
int32_t SDL_ESM_SAFETYAGGR_clearAggrTimeoutErr(uint32_t safetyAggrBase, uint32_t timeoutErr);


#ifdef __cplusplus
}
#endif /*extern "C" */

#endif /*SDL_ESM_SAFETY_AGGR_H_ */

/** @} */