/*
 *  Copyright (c) 2025 Texas Instruments Incorporated
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
 *  \defgroup SECURITY_DTHE_SM3_MODULE APIs for DTHE SM3
 *  \ingroup  SECURITY_MODULE
 *
 *  This module contains APIs to program and use the DTHE SM3.
 *
 *  @{
 */

/**
 *  \file dthe_sm3.h
 *
 *  \brief This file contains the prototype of DTHE SM3 driver APIs
 */

#ifndef DTHE_SM3_H_
#define DTHE_SM3_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <security/drivers/crypto/dthe/dthe.h>
#include <kernel/dpl/SystemP.h>
#include <security/drivers/hw_include/cslr.h>
#include <security/drivers/crypto/dthe/hw_include/cslr_sm3.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Macro for SM3 Hash algo*/
#define DTHE_SM3_ALGO_HASH                 (0x1U)

/** \brief SM3 only supports hash 256 hence, the maximum digest size should be 32 bytes*/
#define DTHE_SM3_MAX_DIGEST_SIZE_BYTES      (32U)



/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 * \brief
 *  DTHE SM3 Driver Error code
 *
 * \details
 *  The enumeration describes all the possible return and error codes which
 *  the DTHE SM3 Driver can return
 */
typedef enum DTHE_SM3_Return_e
{
    DTHE_SM3_RETURN_SUCCESS                  = 0xE7A42DD9U, /*!< Success/pass return code */
    DTHE_SM3_RETURN_FAILURE                  = 0x06C2B4ABU, /*!< General or unspecified failure/error */
}DTHE_SM3_Return_t;

/**
 * \brief
 *  DTHE SM3 Driver Last Block State
 *
 * \details
 *  The enumeration describes the possible status code for
 *  the DTHE SM3 Driver last block
 */
typedef enum DTHE_SM3_LastBlockState_e
{
    DTHE_SM3_LAST_BLOCK_TRUE                  = 0x3A240A96U, /*!< Last Block True State */
    DTHE_SM3_LAST_BLOCK_FALSE                 = 0x3473409AU, /*!< Last Block False State */
}DTHE_SM3_LastBlockState_t;

/**
 * \brief
 *  DTHE SM3 Driver Last Block State
 *
 * \details
 *  The enumeration describes the possible status code for
 *  the DTHE SM3 Driver last block
 */
typedef enum DTHE_SM3_CryptoStateMachine_e
{
    DTHE_SM3_CRYPTO_STATEMACHINE_NEW              = 0x9A3F2B1CU, /*!< Crypto state = NEW */
    DTHE_SM3_CRYPTO_STATEMACHINE_INPROGRESS       = 0x58E7D064U, /*!< Crypto state = IN PROGRESS */
}DTHE_SM3_CryptoStateMachine_t;

/**
 * \brief Parameters required for SM3 Driver
 *
 */
typedef struct DTHE_SM3_Params_t
{
    /** \brief Pointer to the Plain Text data buffer */
    uint32_t            *ptrDataBuffer;
    /** \brief Size of the data in bytes */
    uint64_t            dataLenBytes;
    /** \brief output buffer for storing SM3 degest */
    uint32_t            digest[DTHE_SM3_MAX_DIGEST_SIZE_BYTES/4U];
}DTHE_SM3_Params;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                              Function Declarations                         */
/* ========================================================================== */

/**
 * \brief               Function to Open DTHE SM3 Driver.
 *
 * \param  handle       #DTHE_Handle returned from #DTHE_open().
 *
 * \return              #DTHE_SM3_RETURN_SUCCESS if requested operation completed.
 *                      #DTHE_SM3_RETURN_FAILURE if requested operation not completed.
 */
DTHE_SM3_Return_t DTHE_SM3_open(DTHE_Handle handle);

/**
 * \brief               The function is used to execute the SM3 Driver with the specified parameters.
 *
 * \param  handle       #DTHE_Handle returned from #DTHE_open().
 *
 * \param ptrSM3Params  Pointer to the parameters to be used to execute the driver.
 *
 * \param isLastBlock   Used for singleshot and multishot SM3.
 *
 * \return              #DTHE_SM3_RETURN_SUCCESS if requested operation completed.
 *                      #DTHE_SM3_RETURN_FAILURE if requested operation not completed.
 */
DTHE_SM3_Return_t DTHE_SM3_compute(DTHE_Handle handle, DTHE_SM3_Params* ptrSM3Params, DTHE_SM3_LastBlockState_t isLastBlock);


/**
 * \brief               Function to close DTHE SM3 Driver.
 *
 * \param  handle       #DTHE_Handle returned from #DTHE_open().
 *
 * \return              #DTHE_SM3_RETURN_SUCCESS if requested operation completed.
 *                      #DTHE_SM3_RETURN_FAILURE if requested operation not completed.
 */
DTHE_SM3_Return_t DTHE_SM3_close(DTHE_Handle handle);

#ifdef __cplusplus
}
#endif

#endif
/** @} */
