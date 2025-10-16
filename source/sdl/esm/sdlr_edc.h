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
#ifndef SDLR_EDC_H_
#define SDLR_EDC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t REVISION;                 /* Revision Register */
    volatile uint32_t CONTROL;                  /* Control Register */
    volatile uint32_t ERROR1;                   /* Error 1 Register */
    volatile uint32_t ERROR2;                   /* Error 2 Register */
    volatile uint32_t ERRSTATUS1;               /* Error Status 1 Register */
    volatile uint32_t ERRSTATUS2;               /* Error Status 2 Register */
} SDL_EDCRegs;

/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_EDC_REVISION                                     (0x00000010U)
#define SDL_EDC_CONTROL                                      (0x00000014U)
#define SDL_EDC_ERROR1                                       (0x00000018U)
#define SDL_EDC_ERROR2                                       (0x0000001CU)
#define SDL_EDC_ERRORSTATUS1                                 (0x00000020U)
#define SDL_EDC_ERRORSTATUS2                                 (0x00000024U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* REVISION */

#define SDL_EDC_REVISION_MINOR_MASK                          (0x0000003FU)
#define SDL_EDC_REVISION_MINOR_SHIFT                         (0x00000000U)

#define SDL_EDC_REVISION_CUSTOM_MASK                         (0x000000C0U)
#define SDL_EDC_REVISION_CUSTOM_SHIFT                        (0x00000006U)

#define SDL_EDC_REVISION_MAJOR_MASK                          (0x00000700U)
#define SDL_EDC_REVISION_MAJOR_SHIFT                         (0x00000008U)

#define SDL_EDC_REVISION_RTL_MASK                            (0x0000F800U)
#define SDL_EDC_REVISION_RTL_SHIFT                           (0x0000000BU)

#define SDL_EDC_REVISION_FUNC_MASK                           (0x0FFF0000U)
#define SDL_EDC_REVISION_FUNC_SHIFT                          (0x00000010U)

#define SDL_EDC_REVISION_RSVD_MASK                           (0x30000000U)
#define SDL_EDC_REVISION_RSVD_SHIFT                          (0x0000001CU)

#define SDL_EDC_REVISION_SCHEME_MASK                         (0xC0000000U)
#define SDL_EDC_REVISION_SCHEME_SHIFT                        (0x0000001EU)

/* CONTROL */

#define SDL_EDC_CONTROL_ECCCHECK_MASK                        (0x00000002U)
#define SDL_EDC_CONTROL_ECCCHECK_SHIFT                       (0x00000001U)

#define SDL_EDC_CONTROL_FORCE_DE_MASK                        (0x00000008U)
#define SDL_EDC_CONTROL_FORCE_DE_SHIFT                       (0x00000003U)

#define SDL_EDC_CONTROL_FORCE_SE_MASK                        (0x00000010U)
#define SDL_EDC_CONTROL_FORCE_SE_SHIFT                       (0x00000004U)

#define SDL_EDC_CONTROL_FORCE_NBIT_MASK                      (0x00000020U)
#define SDL_EDC_CONTROL_FORCE_NBIT_SHIFT                     (0x00000005U)

#define SDL_EDC_CONTROL_ECC_PATTERN_MASK                     (0x00000F00U)
#define SDL_EDC_CONTROL_ECC_PATTERN_SHIFT                    (0x00000008U)

/* ERROR1 */

#define SDL_EDC_ERROR1_ECCGRP_MASK                           (0x0000FFFFU)
#define SDL_EDC_ERROR1_ECCGRP_SHIFT                          (0x00000000U)

#define SDL_EDC_ERROR1_ECCBIT1_MASK                          (0x01FF0000U)
#define SDL_EDC_ERROR1_ECCBIT1_SHIFT                         (0x00000010U)

/* ERROR2 */

#define SDL_EDC_ERROR2_ECCBIT2_MASK                          (0x000001FFU)
#define SDL_EDC_ERROR2_ECCBIT2_SHIFT                         (0x00000008U)

/* ERRORSTATUS1 */

#define SDL_EDC_ERRORSTATUS1_COR_PEND_MASK                   (0x00000003U)
#define SDL_EDC_ERRORSTATUS1_COR_PEND_SHIFT                  (0x00000000U)

#define SDL_EDC_ERRORSTATUS1_UNCOR_PEND_MASK                 (0x0000000CU)
#define SDL_EDC_ERRORSTATUS1_UNCOR_PEND_SHIFT                (0x00000002U)

#define SDL_EDC_ERRORSTATUS1_INJ_COR_PEND_MASK               (0x00000030U)
#define SDL_EDC_ERRORSTATUS1_INJ_COR_PEND_SHIFT              (0x00000004U)

#define SDL_EDC_ERRORSTATUS1_INJ_UNCOR_PEND_MASK             (0x000000C0U)
#define SDL_EDC_ERRORSTATUS1_INJ_UNCOR_PEND_SHIFT            (0x00000006U)

#define SDL_EDC_ERRORSTATUS1_COR_PEND_CLR_MASK               (0x00000300U)
#define SDL_EDC_ERRORSTATUS1_COR_PEND_CLR_SHIFT              (0x00000008U)

#define SDL_EDC_ERRORSTATUS1_UNCOR_PEND_CLR_MASK             (0x00000C00U)
#define SDL_EDC_ERRORSTATUS1_UNCOR_PEND_CLR_SHIFT            (0x0000000AU)

#define SDL_EDC_ERRORSTATUS1_INJ_COR_PEND_CLR_MASK           (0x00003000U)
#define SDL_EDC_ERRORSTATUS1_INJ_COR_PEND_CLR_SHIFT          (0x0000000CU)

#define SDL_EDC_ERRORSTATUS1_INJ_UNCOR_PEND_CLR_MASK         (0x0000C000U)
#define SDL_EDC_ERRORSTATUS1_INJ_UNCOR_PEND_CLR_SHIFT        (0x0000000EU)

#define SDL_EDC_ERRORSTATUS1_ERR_GROUP_MASK                  (0xFFFF0000U)
#define SDL_EDC_ERRORSTATUS1_ERR_GROUP_SHIFT                 (0x00000010U)

/* ERRORSTATUS2 */

#define SDL_EDC_ERRORSTATUS2_ERR_BIT_MASK                    (0x0000FFFFU)
#define SDL_EDC_ERRORSTATUS2_ERR_BIT_SHIFT                   (0x00000000U)

#define SDL_EDC_ERRORSTATUS2_ERROR_TYPE_MASK                 (0xFFFF0000U)
#define SDL_EDC_ERRORSTATUS2_ERROR_TYPE_SHIFT                (0x00000010U)


#ifdef __cplusplus
}
#endif
#endif /* SDLR_EDC_H_ */