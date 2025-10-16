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
 * \addtogroup sdl_err_aggr_group
 *
 * @{
 */

#ifndef SDL_ERR_AGGR_H_
#define SDL_ERR_AGGR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <include/sdl_types.h>
#include <include/hw_types.h>
#include <include/sdlr_baseaddress.h>
#include <err_aggr/sdlr_err_aggr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* BootROM ESM Error Aggregator status Address */
#define SDL_BOOTROM_ESM_RAW_STATUS_ADDR                 (SDL_M0_RAM_BASE + 0x0868U)

/* Error Aggregator Offset for Error Source */

#define SDL_ERR_AGGR_O_HIGHPRIO_ERRADDR                 (0x0000U)
#define SDL_ERR_AGGR_O_LOWPRIO_ERRADDR                  (0x0004U)
#define SDL_ERR_AGGR_O_ERRTYPE                          (0x0008U)
#define SDL_ERR_AGGR_O_ERRTYPE_FRC                      (0x000CU)
#define SDL_ERR_AGGR_O_ERRTYPE_CLR                      (0x0010U)
#define SDL_ERR_AGGR_O_PC                               (0x0014U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef enum {
    SDL_ERR_AGGR_SRC_CPU1_PR   = SDL_ERR_AGGR_CPU1_PR_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU1_DR1  = SDL_ERR_AGGR_CPU1_DR1_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU1_DR2  = SDL_ERR_AGGR_CPU1_DR2_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU1_DW   = SDL_ERR_AGGR_CPU1_DW_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU1_INT  = SDL_ERR_AGGR_CPU1_INT_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU2_PR   = SDL_ERR_AGGR_CPU2_PR_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU2_DR1  = SDL_ERR_AGGR_CPU2_DR1_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU2_DR2  = SDL_ERR_AGGR_CPU2_DR2_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU2_DW   = SDL_ERR_AGGR_CPU2_DW_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU2_INT  = SDL_ERR_AGGR_CPU2_INT_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU3_PR   = SDL_ERR_AGGR_CPU3_PR_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU3_DR1  = SDL_ERR_AGGR_CPU3_DR1_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU3_DR2  = SDL_ERR_AGGR_CPU3_DR2_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU3_DW   = SDL_ERR_AGGR_CPU3_DW_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_CPU3_INT  = SDL_ERR_AGGR_CPU3_INT_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_RTDMA1_DR = SDL_ERR_AGGR_RTDMA1_DR_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_RTDMA1_DW = SDL_ERR_AGGR_RTDMA1_DW_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_RTDMA2_DR = SDL_ERR_AGGR_RTDMA2_DR_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_RTDMA2_DW = SDL_ERR_AGGR_RTDMA2_DW_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_SSU       = SDL_ERR_AGGR_SSU_HIGHPRIO_ERRADDR,
    SDL_ERR_AGGR_SRC_ETHERCAT  = SDL_ERR_AGGR_ETHERCAT_HIGHPRIO_ERRADDR
} SDL_ERR_AGGR_ErrSource;

typedef struct {
    volatile uint32_t ESM_RAW_STATUS;
    volatile uint32_t PR_EA_HI_PRIO_ERROR_ADDR;
    volatile uint32_t PR_EA_LOW_PRIO_ERROR_ADDR;
    volatile uint32_t PR_EA_ERROR_TYPE;
    volatile uint32_t PR_EA_PC_VALUE;
    volatile uint32_t DR1_EA_HI_PRIO_ERROR_ADDR;
    volatile uint32_t DR1_EA_LOW_PRIO_ERROR_ADDR;
    volatile uint32_t DR1_EA_ERROR_TYPE;
    volatile uint32_t DR1_EA_PC_VALUE;
    volatile uint32_t DR2_EA_HI_PRIO_ERROR_ADDR;
    volatile uint32_t DR2_EA_LOW_PRIO_ERROR_ADDR;
    volatile uint32_t DR2_EA_ERROR_TYPE;
    volatile uint32_t DR2_EA_PC_VALUE;
    volatile uint32_t DW_EA_HI_PRIO_ERROR_ADDR;
    volatile uint32_t DW_EA_LOW_PRIO_ERROR_ADDR;
    volatile uint32_t DW_EA_ERROR_TYPE;
    volatile uint32_t DW_EA_PC_VALUE;
    volatile uint32_t INT_EA_HI_PRIO_ERROR_ADDR;
    volatile uint32_t INT_EA_LOW_PRIO_ERROR_ADDR;
    volatile uint32_t INT_EA_ERROR_TYPE;
    volatile uint32_t INT_EA_PC_VALUE;
} SDL_ESM_CPU1BootErrorStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used to get the High priority Error Address.
 *
 * \param   baseAddr        Base Address of the Error Aggregator.
 *
 * \param   source          Error Aggregator Source module
 * 
 * \param   errAddr         pointer to get the high priority error address
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

       uint32_t               baseAddr = SDL_ERRORAGGREGATOR_BASE;
       SDL_ERR_AGGR_ErrSource source   = SDL_ERR_AGGR_SRC_CPU1_PR;
       uint32_t               errAddr;
       retVal = SDL_ERR_AGGR_getHighPrioErrorAddr(baseAddr, source, &errAddr);

   @endverbatim
 *
 */
int32_t SDL_ERR_AGGR_getHighPrioErrorAddr(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t *errAddr);

/**
 * \brief   This API is used to get the Low priority Error Address.
 *
 * \param   baseAddr        Base Address of the Error Aggregator.
 *
 * \param   source          Error Aggregator Source module
 * 
 * \param   errAddr         pointer to get the high priority error address 
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

       uint32_t               baseAddr = SDL_ERRORAGGREGATOR_BASE;
       SDL_ERR_AGGR_ErrSource source   = SDL_ERR_AGGR_SRC_CPU1_PR;
       uint32_t               errAddr;
       retVal = SDL_ERR_AGGR_getLowPrioErrorAddr(baseAddr, source, &errAddr);

   @endverbatim
 *
 */
int32_t SDL_ERR_AGGR_getLowPrioErrorAddr(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t *errAddr);

/**
 * \brief   This API is used to get the Error type.
 *
 * \param   baseAddr        Base Address of the Error Aggregator.
 *
 * \param   source          Error Aggregator Source module
 * 
 * \param   errTypeVal      pointer to the Value of the register and 
 *                          when compared with masked values 
 *                          can decode the error type which is enabled 
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

       uint32_t               baseAddr  = SDL_ERRORAGGREGATOR_BASE;
       SDL_ERR_AGGR_ErrSource source = SDL_ERR_AGGR_SRC_CPU1_PR;
       uint32_t               errTypeVal;
       int32_t                retVal;
       retVal = SDL_ERR_AGGR_getErrorType(baseAddr, source, &errTypeVal);

   @endverbatim
 *
 */
int32_t SDL_ERR_AGGR_getErrorType(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t *errTypeVal);

/**
 * \brief   This API is used to set the Error Type.
 *
 * \param   baseAddr        Base Address of the Error Aggregator.
 *
 * \param   source          Error Aggregator Source module
 * 
 * \param   errTypeMask     Error Type Mask of errors to be forced
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

       uint32_t               baseAddr    = SDL_ERRORAGGREGATOR_BASE;
       SDL_ERR_AGGR_ErrSource source      = SDL_ERR_AGGR_SRC_CPU1_PR;
       uint32_t               errTypeMask = SDL_ERR_AGGR_TYPE_LP_SOFTWARE_MASK;
       int32_t                retVal;
       retVal = SDL_ERR_AGGR_setErrorType(baseAddr, source, errTypeMask);

   @endverbatim
 *
 */
int32_t SDL_ERR_AGGR_setErrorType(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t errTypeMask);

/**
 * \brief   This API is used to clear the Error Type.
 *
 * \param   baseAddr        Base Address of the Error Aggregator.
 *
 * \param   source          Error Aggregator Source module
 * 
 * \param   errTypeMask     Error Type Mask of errors to be cleared
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

       uint32_t               baseAddr    = SDL_ERRORAGGREGATOR_BASE;
       SDL_ERR_AGGR_ErrSource source      = SDL_ERR_AGGR_SRC_CPU1_PR;
       uint32_t               errTypeMask = SDL_ERR_AGGR_TYPE_LP_SOFTWARE_MASK;
       int32_t                retVal;
       retVal = SDL_ERR_AGGR_clearErrorType(baseAddr, source, errTypeMask);

   @endverbatim
 *
 */
int32_t SDL_ERR_AGGR_clearErrorType(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t errTypeMask);

/**
 * \brief   This API is used to get the program counter value.
 *
 * \param   baseAddr        Base Address of the Error Aggregator.
 *
 * \param   source          Error Aggregator Source module
 * 
 * \param   errAddr         pointer to the stored PC Value at the 
 *                          first high priority error event 
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

       uint32_t               baseAddr = SDL_ERRORAGGREGATOR_BASE;
       SDL_ERR_AGGR_ErrSource source   = SDL_ERR_AGGR_SRC_CPU1_PR;
       uint32_t               pcVal;
       retVal = SDL_ERR_AGGR_getStoredPCValue(baseAddr, source, &pcVal);

   @endverbatim
 *
 */
int32_t SDL_ERR_AGGR_getStoredPCValue(uint32_t baseAddr, SDL_ERR_AGGR_ErrSource source, uint32_t *pcVal);

/**
 * \brief   This API is used to read the boot error status.
 *
 * \param   pBootAddr        Pointer to the bootrom Address structure
 *
 * \return                   None
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       SDL_ESM_CPU1BootErrorStatus pBootAddr;
       retVal = SDL_ESM_getBootErrorStatus(&pBootAddr);

   @endverbatim
 *
 */
void SDL_ESM_getBootErrorStatus(SDL_ESM_CPU1BootErrorStatus *pBootAddr);

/** @} */

#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* SDL_ERR_AGGR_H_ */