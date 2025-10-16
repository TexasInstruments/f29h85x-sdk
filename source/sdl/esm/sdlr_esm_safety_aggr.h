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
#ifndef SDLR_ESM_SAFETY_AGGREGATOR_H_
#define SDLR_ESM_SAFETY_AGGREGATOR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

/* None */

/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_ESM_SAFETYAGGR_REVISION                              (0x00000000U)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR                            (0x00000008U)
#define SDL_ESM_SAFETYAGGR_MISC_STATUS                           (0x0000000CU)
#define SDL_ESM_SAFETYAGGR_RSVD_SVBUS(Y)                         ((0x00000010U) + (Y * 0x4U))
#define SDL_ESM_SAFETYAGGR_DED_EOI_REG                           (0x0000013CU)
#define SDL_ESM_SAFETYAGGR_DED_STATUS_REG0                       (0x00000140U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0                   (0x00000180U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0                   (0x000001C0U)
#define SDL_ESM_SAFETYAGGR_ENABLE_SET                            (0x00000200U)
#define SDL_ESM_SAFETYAGGR_ENABLE_CLR                            (0x00000204U)
#define SDL_ESM_SAFETYAGGR_STATUS_SET                            (0x00000208U)
#define SDL_ESM_SAFETYAGGR_STATUS_CLR                            (0x0000020CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* ESM_SAFETYAGGR_REVISION */

#define SDL_ESM_SAFETYAGGR_MASK                                                 (0xFFFFFFFFU)
#define SDL_ESM_SAFETYAGGR_SHIFT                                                (0x00000000U)

#define SDL_ESM_SAFETYAGGR_REV_SCHEME_MASK                                      (0xC0000000U)
#define SDL_ESM_SAFETYAGGR_REV_SCHEME_SHIFT                                     (0x0000001EU)

#define SDL_ESM_SAFETYAGGR_REV_BU_MASK                                          (0x30000000U)
#define SDL_ESM_SAFETYAGGR_REV_BU_SHIFT                                         (0x0000001CU)

#define SDL_ESM_SAFETYAGGR_REV_MODULE_ID_MASK                                   (0x0FFF0000U)
#define SDL_ESM_SAFETYAGGR_REV_MODULE_ID_SHIFT                                  (0x00000016U)

#define SDL_ESM_SAFETYAGGR_REV_RTLVER_MASK                                      (0x0000F800U)
#define SDL_ESM_SAFETYAGGR_REV_RTLVER_SHIFT                                     (0x0000000BU)

#define SDL_ESM_SAFETYAGGR_REV_MAJORVER_MASK                                    (0x00000700U)
#define SDL_ESM_SAFETYAGGR_REV_MAJORVER_SHIFT                                   (0x00000008U)

#define SDL_ESM_SAFETYAGGR_REV_CUSTOMVER_MASK                                   (0x000000C0U)
#define SDL_ESM_SAFETYAGGR_REV_CUSTOMVER_SHIFT                                  (0x00000006U)

#define SDL_ESM_SAFETYAGGR_REV_MINORVER_MASK                                    (0x0000003FU)
#define SDL_ESM_SAFETYAGGR_REV_MINORVER_SHIFT                                   (0x00000000U)

/* ESM_SAFETYAGGR_ECC_VECTOR */

#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_DONE_MASK                        (0x01000000U)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_DONE_SHIFT                       (0x00000018U)

#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_ADDR_MASK                        (0x00FF0000U)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_ADDR_SHIFT                       (0x00000010U)

#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_MASK                             (0x00008000U)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_RD_SVBUS_SHIFT                            (0x0000000FU)

#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_MASK                                      (0x000007FFU)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_ESM_CPU3                                  (0x00000003U)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_ESM_CPU2                                  (0x00000002U)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_ESM_CPU1                                  (0x00000001U)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_ESM_SYS                                   (0x00000000U)
#define SDL_ESM_SAFETYAGGR_ECC_VECTOR_SHIFT                                     (0x00000000U)

/* ESM_SAFETYAGGR_MISC_STATUS */

#define SDL_ESM_SAFETYAGGR_MISC_STATUS_MASK                                     (0x000007FFU)
#define SDL_ESM_SAFETYAGGR_MISC_STATUS_SHIFT                                    (0x00000000U)

/* ESM_SAFETYAGGR_RSVD_SVBUS */

#define SDL_ESM_SAFETYAGGR_RSVD_SVBUS_MASK                                      (0xFFFFFFFFU)
#define SDL_ESM_SAFETYAGGR_RSVD_SVBUS_SHIFT                                     (0x00000000U)

/* ESM_SAFETYAGGR_DED_EOI_REG */

#define SDL_ESM_SAFETYAGGR_DED_EOI_REG_MASK                                     (0x00000001U)
#define SDL_ESM_SAFETYAGGR_DED_EOI_REG_SHIFT                                    (0x00000000U)

/* ESM_SAFETYAGGR_DED_STATUS_REG0 */

#define SDL_ESM_SAFETYAGGR_DED_STATUS_REG0_MASK                                 (0x0000000FU)
#define SDL_ESM_SAFETYAGGR_DED_STATUS_REG0_ESM2_EDC_CTRL_BUSECC_PEND            (0x00000008U)
#define SDL_ESM_SAFETYAGGR_DED_STATUS_REG0_ESM1_EDC_CTRL_BUSECC_PEND            (0x00000004U)
#define SDL_ESM_SAFETYAGGR_DED_STATUS_REG0_ESM0_EDC_CTRL_BUSECC_PEND            (0x00000002U)
#define SDL_ESM_SAFETYAGGR_DED_STATUS_REG0_ESMSYS_EDC_CTRL_BUSECC_PEND          (0x00000001U)
#define SDL_ESM_SAFETYAGGR_DED_STATUS_REG0_SHIFT                                (0x00000000U)

/* ESM_SAFETYAGGR_DED_ENABLE_SET_REG0 */

#define SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0_ESM2_EDC_CTRL_BUSECC_ENABLE      (0x00000008U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0_ESM1_EDC_CTRL_BUSECC_ENABLE      (0x00000004U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0_ESM0_EDC_CTRL_BUSECC_ENABLE      (0x00000002U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0_ESMSYS_EDC_CTRL_BUSECC_ENABLE    (0x00000001U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0_SHIFT                            (0x00000000U)

/* ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0 */
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0_ESM2_EDC_CTRL_BUSECC_CLR         (0x00000008U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0_ESM1_EDC_CTRL_BUSECC_CLR         (0x00000004U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0_ESM0_EDC_CTRL_BUSECC_CLR         (0x00000002U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0_ESMSYS_EDC_CTRL_BUSECC_CLR       (0x00000001U)
#define SDL_ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0_SHIFT                            (0x00000000U)

/* ESM_SAFETYAGGR_ENABLE_SET */

#define SDL_ESM_SAFETYAGGR_ENABLE_SET_MASK                                      (0x00000003U)
#define SDL_ESM_SAFETYAGGR_ENABLE_SET_SHIFT                                     (0x00000000U)

#define SDL_ESM_SAFETYAGGR_ENABLE_SET_TIMEOUT_MASK                              (0x00000002U)
#define SDL_ESM_SAFETYAGGR_ENABLE_SET_TIMEOUT_SHIFT                             (0x00000001U)

#define SDL_ESM_SAFETYAGGR_ENABLE_SET_PARITY_MASK                               (0x00000001U)
#define SDL_ESM_SAFETYAGGR_ENABLE_SET_PARITY_SHIFT                              (0x00000000U)

/* ESM_SAFETYAGGR_ENABLE_CLR */

#define SDL_ESM_SAFETYAGGR_ENABLE_CLR_MASK                                      (0x00000003U)
#define SDL_ESM_SAFETYAGGR_ENABLE_CLR_SHIFT                                     (0x00000000U)

#define SDL_ESM_SAFETYAGGR_ENABLE_CLR_TIMEOUT_MASK                              (0x00000002U)
#define SDL_ESM_SAFETYAGGR_ENABLE_CLR_TIMEOUT_SHIFT                             (0x00000001U)

#define SDL_ESM_SAFETYAGGR_ENABLE_CLR_PARITY_MASK                               (0x00000001U)
#define SDL_ESM_SAFETYAGGR_ENABLE_CLR_PARITY_SHIFT                               (0x00000000U)

/* ESM_SAFETYAGGR_STATUS_SET */

#define SDL_ESM_SAFETYAGGR_STATUS_SET_MASK                                      (0x000000FFU)
#define SDL_ESM_SAFETYAGGR_STATUS_SET_SHIFT                                     (0x00000000U)

#define SDL_ESM_SAFETYAGGR_STATUS_SET_TIMEOUT_MASK                              (0x0000000CU)
#define SDL_ESM_SAFETYAGGR_STATUS_SET_TIMEOUT_SHIFT                             (0x00000002U)

#define SDL_ESM_SAFETYAGGR_STATUS_SET_PARITY_MASK                               (0x00000003U)
#define SDL_ESM_SAFETYAGGR_STATUS_SET_PARITY_SHIFT                              (0x00000000U)

/* ESM_SAFETYAGGR_STATUS_CLR */

#define SDL_ESM_SAFETYAGGR_STATUS_CLR_MASK                                      (0x0000000FU)
#define SDL_ESM_SAFETYAGGR_STATUS_CLR_SHIFT                                     (0x00000000U)

#define SDL_ESM_SAFETYAGGR_STATUS_CLR_TIMEOUT_MASK                              (0x0000000FU)
#define SDL_ESM_SAFETYAGGR_STATUS_CLR_TIMEOUT_SHIFT                             (0x00000002U)

#define SDL_ESM_SAFETYAGGR_STATUS_CLR_PARITY_MASK                               (0x0000000FU)
#define SDL_ESM_SAFETYAGGR_STATUS_CLR_PARITY_SHIFT                              (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif /* SDLR_ESM_SAFETY_AGGREGATOR_H_ */