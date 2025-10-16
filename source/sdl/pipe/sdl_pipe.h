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
 *  \addtogroup sdl_pipe_group
 *
 *  @{
 */

/**
 *  \file     sdl_pipe.h
 *
 * \brief
 *  Header file contains enumerations, structure definitions and function
 *  declarations for SDL PIPE Module interface for parity check.
 */

#ifndef SDL_PIPE_H_
#define SDL_PIPE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <include/sdlr_baseaddress.h>
#include <include/hw_types.h>
#include <include/sdl_types.h>
#include <err_aggr/sdlr_err_aggr.h>
#include <err_aggr/sdl_err_aggr.h>
#include "sdlr_pipe.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define SDL_PIPE_PARITY_ASSERT_KEY   (0x5A5A0001U)
#define SDL_PIPE_PARITY_CHECK_KEY    (0x5A5A000AU)
#define SDL_PIPE_PARITY_READ         (0x5A5A000AU)
#define SDL_PIPE_INTERRUPT           (1U)
#define SDL_PIPE_NO_INTERRUPT        (0U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *
 * \brief   This API is used to validate the parity diagnostic mechanism for 
 *          the given 32 bit data value and the mismatched parity. The hardware detects
 *          the parity mismatch and sets the corresponding error status in the 
 *          Error Aggregator and ESM will generate an interrupt.
 *
 * \param   errAggrBase: Base address of the Error Aggregator.
 * \param   data:        32 bit data to be used for the parity check.
 * \param   parity:      Parity data which should not match the given data.
 *
 * \return  SDL_PASS -  success
 * @n       SDL_EFAIL - return a failure if it's unable to get interrupt
 * @n       SDL_EBADARGS - API fails due to wrong base address
 * 
 */
int32_t SDL_PIPE_checkRegisterParity(uint32_t errAggrBase, uint32_t data, uint8_t parity);

/** @} */
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* SDL_PIPE_H_ */
