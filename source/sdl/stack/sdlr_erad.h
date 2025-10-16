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
#ifndef SDLR_ERAD_H_
#define SDLR_ERAD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_ERAD_GLBL_ERAD_ID                (0x00000000U)                  /* Debug Peripheral ID */
#define SDL_ERAD_GLBL_EVENT_STAT             (0x00000004U)                  /* Global Event Status Register */
#define SDL_ERAD_EBC_OWNER(i)                (0x00000040U + ((i) * 64U))    /* EBC Owner Register */
#define SDL_ERAD_EBC_CNTL(i)                 (0x00000044U + ((i) * 64U))    /* EBC Control Register */
#define SDL_ERAD_EBC_STATUS(i)               (0x00000048U + ((i) * 64U))    /* EBC Status Register */
#define SDL_ERAD_EBC_STATUSCLEAR(i)          (0x0000004CU + ((i) * 64U))    /* EBC Clear Register */
#define SDL_ERAD_EBC_REFL(i)                 (0x00000050U + ((i) * 64U))    /* EBC Reference Low Register */
#define SDL_ERAD_EBC_REFH(i)                 (0x00000054U + ((i) * 64U))    /* EBC Reference High Register */
#define SDL_ERAD_EBC_MASKL(i)                (0x00000058U + ((i) * 64U))    /* EBC Mask Low Register */
#define SDL_ERAD_EBC_MASKH(i)                (0x0000005CU + ((i) * 64U))    /* EBC Mask High Register */
#define SDL_ERAD_EBC_WP_PC(i)                (0x00000060U + ((i) * 64U))    /* EBC Watchpoint PC Register */
#define SDL_ERAD_SEC_OWNER(i)                (0x00000440U + ((i) * 64U))    /* SEC Owner Register */
#define SDL_ERAD_SEC_CNTL(i)                 (0x00000444U + ((i) * 64U))    /* SEC Control Register */
#define SDL_ERAD_SEC_STATUS(i)               (0x00000448U + ((i) * 64U))    /* SEC Status Register */
#define SDL_ERAD_SEC_STATUSCLEAR(i)          (0x0000044CU + ((i) * 64U))    /* SEC Clear Register */
#define SDL_ERAD_SEC_REF(i)                  (0x00000450U + ((i) * 64U))    /* SEC Reference Register */
#define SDL_ERAD_SEC_INPUT_SEL1(i)           (0x00000454U + ((i) * 64U))    /* SEC Input Select Register1 */
#define SDL_ERAD_SEC_INPUT_SEL2(i)           (0x00000458U + ((i) * 64U))    /* SEC Input Select Register2 */
#define SDL_ERAD_SEC_INPUT_COND(i)           (0x0000045CU + ((i) * 64U))    /* SEC Input Conditioning Register */
#define SDL_ERAD_SEC_COUNT(i)                (0x00000460U + ((i) * 64U))    /* SEC Counter Register */
#define SDL_ERAD_SEC_MAX_COUNT(i)            (0x00000464U + ((i) * 64U))    /* SEC Max Count Register */ 
#define SDL_ERAD_SEC_MIN_COUNT(i)            (0x00000468U + ((i) * 64U))    /* SEC Min Count Register */
#define SDL_ERAD_AND_MASK_OWNER(i)           (0x00000640U + ((i) * 32U))    /* AND Owner Register */
#define SDL_ERAD_AND_MASK_CTL(i)             (0x00000644U + ((i) * 32U))    /* AND Control Register */
#define SDL_ERAD_EVENT_AND_MASK(i)           (0x00000648U + ((i) * 32U))    /* AND Event Selection Register*/
#define SDL_ERAD_OR_MASK_OWNER(i)            (0x00000740U + ((i) * 32U))    /* OR Owner Register */
#define SDL_ERAD_OR_MASK_CTL(i)              (0x00000744U + ((i) * 32U))    /* OR Control Register */
#define SDL_ERAD_EVENT_OR_MASK(i)            (0x00000748U + ((i) * 32U))    /* OR Event Selection Register */
#define SDL_ERAD_PCTRACE_OWNER               (0x00000840U)                  /* PCTRACE Owner Register */               
#define SDL_ERAD_PCTRACE_GLOBAL              (0x00000844U)                  /* PCTRACE Global Control Register */                 
#define SDL_ERAD_PCTRACE_BUFFER              (0x00000848U)                  /* Trace Buffer pointer register*/
#define SDL_ERAD_PCTRACE_QUAL1               (0x0000084CU)                  /* Trace Qualifier register 1 */
#define SDL_ERAD_PCTRACE_QUAL2               (0x00000850U)                  /* Trace Qualifier register 2 */
#define SDL_ERAD_PCTRACE_LOGPC_SOFTENABLE    (0x00000854U)                  /* PC when PC Trace was last enabled by software */
#define SDL_ERAD_PCTRACE_LOGPC_SOFTDISABLE   (0x00000858U)                  /* PC when PC Trace was last disabled by software */
#define SDL_ERAD_PCTRACE_BUFFER_BASE(i)      (0x00001000U + ((i) * 0x4U))   /* Trace Buffer Base address */

/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* GLBL_ERAD_ID */

#define SDL_ERAD_GLBL_ERAD_ID_MINOR_SHIFT                   (0x00000000U)
#define SDL_ERAD_GLBL_ERAD_ID_MINOR_MASK                    (0x0000003FU)        
#define SDL_ERAD_GLBL_ERAD_ID_CUSTOM_SHIFT                  (0x00000006U)
#define SDL_ERAD_GLBL_ERAD_ID_CUSTOM_MASK                   (0x000000C0U)        
#define SDL_ERAD_GLBL_ERAD_ID_MAJOR_SHIFT                   (0x00000008U)
#define SDL_ERAD_GLBL_ERAD_ID_MAJOR_MASK                    (0x00000700U)       
#define SDL_ERAD_GLBL_ERAD_ID_FUNC_SHIFT                    (0x00000016U)
#define SDL_ERAD_GLBL_ERAD_ID_FUNC_MASK                     (0x0FFF0000U)   

/* GLBL_EVENT_STAT */

#define SDL_ERAD_GLBL_EVENT_STAT_EBC_SHIFT                  (0x00000000U)
#define SDL_ERAD_GLBL_EVENT_STAT_EBC_MASK                   (0x0000FFFFU)
#define SDL_ERAD_GLBL_EVENT_STAT_SEC_SHIFT                  (0x00000016U)
#define SDL_ERAD_GLBL_EVENT_STAT_SEC_MASK                   (0xFFFF0000U)

/* EBC_OWNER */

#define SDL_ERAD_EBC_OWNER_OWNER_SHIFT                      (0x00000000U)
#define SDL_ERAD_EBC_OWNER_OWNER_MASK                       (0x00000003U)
#define SDL_ERAD_EBC_OWNER_ZONE_SHIFT                       (0x00000008U)
#define SDL_ERAD_EBC_OWNER_ZONE_MASK                        (0x00000F00U)
#define SDL_ERAD_EBC_OWNER_SROOT                            (0x00001000U)
#define SDL_ERAD_EBC_OWNER_SEM                              (0x00010000U)
#define SDL_ERAD_EBC_OWNER_CONFIG_SHIFT                     (0x00000017U)
#define SDL_ERAD_EBC_OWNER_CONFIG_MASK                      (0x00060000U)

/* EBC_CNTL */

#define SDL_ERAD_EBC_CNTL_EN                                (0x00000001U)
#define SDL_ERAD_EBC_CNTL_BUS_SEL_SHIFT                     (0x00000001U)
#define SDL_ERAD_EBC_CNTL_BUS_SEL_MASK                      (0x0000003EU)
#define SDL_ERAD_EBC_CNTL_HALT                              (0x00000040U)
#define SDL_ERAD_EBC_CNTL_INTERRUPT                         (0x00000080U)
#define SDL_ERAD_EBC_CNTL_NMI_EN                            (0x00000100U)
#define SDL_ERAD_EBC_CNTL_COMP_MODE_SHIFT                   (0x00000009U)
#define SDL_ERAD_EBC_CNTL_COMP_MODE_MASK                    (0x00000E00U)
#define SDL_ERAD_EBC_CNTL_STACK_QUAL                        (0x00001000U)
#define SDL_ERAD_EBC_CNTL_SPSEL_MATCH_EN                    (0x00002000U)
#define SDL_ERAD_EBC_CNTL_SPSEL_SHIFT                       (0x00000014U)
#define SDL_ERAD_EBC_CNTL_SPSEL_MASK                        (0x0003C000U)

/* EBC_STATUS */

#define SDL_ERAD_EBC_STATUS_EVENT_FIRED                     (0x00000001U)
#define SDL_ERAD_EBC_STATUS_STATUS_SHIFT                    (0x00000008U)
#define SDL_ERAD_EBC_STATUS_STATUS_MASK                     (0x00000300U)

/* EBC_STATUSCLEAR */
#define SDL_ERAD_EBC_STATUSCLEAR_EVENT_FIRED                (0x00000001U)

/* SEC_OWNER */

#define SDL_ERAD_SEC_OWNER_OWNER_SHIFT                      (0x00000000U)
#define SDL_ERAD_SEC_OWNER_OWNER_MASK                       (0x00000003U)   
#define SDL_ERAD_SEC_OWNER_ZONE_SHIFT                       (0x00000008U)
#define SDL_ERAD_SEC_OWNER_ZONE_MASK                        (0x00000F00U) 
#define SDL_ERAD_SEC_OWNER_SROOT                            (0x00001000U)
#define SDL_ERAD_SEC_OWNER_SEM                              (0x00010000U)
#define SDL_ERAD_SEC_OWNER_CONFIG_SHIFT                     (0x00000017U)
#define SDL_ERAD_SEC_OWNER_CONFIG_MASK                      (0x00060000U)

/* SEC_CNTL */
#define SDL_ERAD_SEC_CNTL_EN                                (0x00000001U)
#define SDL_ERAD_SEC_CNTL_EDGE_LEVEL                        (0x00000002U)
#define SDL_ERAD_SEC_CNTL_START_STOP_MODE                   (0x00000004U)
#define SDL_ERAD_SEC_CNTL_START_STOP_CUMULATIVE             (0x00000008U)
#define SDL_ERAD_SEC_CNTL_RST_ON_MATCH                      (0x00000010U)
#define SDL_ERAD_SEC_CNTL_HALT                              (0x00000020U)
#define SDL_ERAD_SEC_CNTL_INTERRUPT                         (0x00000040U)
#define SDL_ERAD_SEC_CNTL_NMI_EN                            (0x00000080U)
#define SDL_ERAD_SEC_CNTL_CNT_INP_SEL_EN                    (0x00000100U)
#define SDL_ERAD_SEC_CNTL_RST_INP_SEL_EN                    (0x00000200U)
#define SDL_ERAD_SEC_CNTL_FREE_RUN                          (0x00000400U)

/* SEC_STATUS */
#define SDL_ERAD_SEC_STATUS_EVENT_FIRED                     (0x00000001U)
#define SDL_ERAD_SEC_STATUS_OVERFLOW                        (0x00000002U)
#define SDL_ERAD_SEC_STATUS_STATUS_SHIFT                    (0x00000008U)
#define SDL_ERAD_SEC_STATUS_STATUS_MASK                     (0x00000300U)

/* SEC_STATUSCLEAR */
#define SDL_ERAD_SEC_STATUSCLEAR_EVENT_FIRED                (0x00000001U)
#define SDL_ERAD_SEC_STATUSCLEAR_OVERFLOW                   (0x00000002U)

/* SEC_INPUT_SEL1 */
#define SDL_ERAD_SEC_INP_SEL1_CNT_SEL_SHIFT                 (0x00000000U)
#define SDL_ERAD_SEC_INP_SEL1_CNT_SEL_MASK                  (0x000000FFU)
#define SDL_ERAD_SEC_INP_SEL1_RST_SEL_SHIFT                 (0x00000016U)
#define SDL_ERAD_SEC_INP_SEL1_RST_SEL_MASK                  (0x00FF0000U)

/* SEC_INPUT_SEL2 */
#define SDL_ERAD_SEC_INP_SEL2_STA_SEL_SHIFT                 (0x00000000U)
#define SDL_ERAD_SEC_INP_SEL2_STA_SEL_MASK                  (0x000000FFU)
#define SDL_ERAD_SEC_INP_SEL2_STO_SEL_SHIFT                 (0x00000016U)
#define SDL_ERAD_SEC_INP_SEL2_STO_SEL_MASK                  (0x00FF0000U)

/* SEC_INPUT_COND */
#define SDL_ERAD_SEC_INPUT_COND_SEC_INP_INV                 (0x00000001U)
#define SDL_ERAD_SEC_INPUT_COND_STA_INP_INV                 (0x00000010U)
#define SDL_ERAD_SEC_INPUT_COND_STO_INP_INV                 (0x00000100U)
#define SDL_ERAD_SEC_INPUT_COND_RST_INP_INV                 (0x00001000U)

/* AND_MASK_OWNER */
#define SDL_ERAD_AND_MASK_OWNER_OWNER_SHIFT                 (0x00000000U)
#define SDL_ERAD_AND_MASK_OWNER_OWNER_MASK                  (0x00000003U)
#define SDL_ERAD_AND_MASK_OWNER_ZONE_SHIFT                  (0x00000008U)
#define SDL_ERAD_AND_MASK_OWNER_ZONE_MASK                   (0x00000F00U)
#define SDL_ERAD_AND_MASK_OWNER_SROOT                       (0x00001000U)
#define SDL_ERAD_AND_MASK_OWNER_SEM                         (0x00010000U)

/* AND_MASK_CTL */
#define SDL_ERAD_AND_MASK_CTL_HALT                          (0x00000001U)
#define SDL_ERAD_AND_MASK_CTL_INTERRUPT                     (0x00000002U)
#define SDL_ERAD_AND_MASK_CTL_NMI_EN                        (0x00000004U)

/* EVENT_AND_MASK */
#define SDL_ERAD_EVENT_AND_MASK_EBC_SHIFT                   (0x00000000U)
#define SDL_ERAD_EVENT_AND_MASK_EBC_MASK                    (0x00FFFFFFU)

/* OR_MASK_OWNER */
#define SDL_ERAD_OR_MASK_OWNER_OWNER_SHIFT                  (0x00000000U)
#define SDL_ERAD_OR_MASK_OWNER_OWNER_MASK                   (0x00000003U)
#define SDL_ERAD_OR_MASK_OWNER_ZONE_SHIFT                   (0x00000008U)
#define SDL_ERAD_OR_MASK_OWNER_ZONE_MASK                    (0x00000F00U)
#define SDL_ERAD_OR_MASK_OWNER_SROOT                        (0x00001000U)
#define SDL_ERAD_OR_MASK_OWNER_SEM                          (0x00010000U)

/* OR_MASK_CTL */
#define SDL_ERAD_OR_MASK_CTL_HALT                           (0x00000001U)
#define SDL_ERAD_OR_MASK_CTL_INTERRUPT                      (0x00000002U)
#define SDL_ERAD_OR_MASK_CTL_NMI_EN                         (0x00000004U)

/* EVENT_OR_MASK */
#define SDL_ERAD_EVENT_OR_MASK_EBC_SHIFT                    (0x00000000U)
#define SDL_ERAD_EVENT_OR_MASK_EBC_MASK                     (0x00FFFFFFU)

/* PCTRACE_OWNER */
#define SDL_ERAD_PCTRACE_OWNER_OWNER_SHIFT                  (0x00000000U)
#define SDL_ERAD_PCTRACE_OWNER_OWNER_MASK                   (0x00000003U)
#define SDL_ERAD_PCTRACE_OWNER_ZONE_SHIFT                   (0X00000008U)
#define SDL_ERAD_PCTRACE_OWNER_ZONE_MASK                    (0x00000F00U)
#define SDL_ERAD_PCTRACE_OWNER_SROOT                        (0x00001000U)
#define SDL_ERAD_PCTRACE_OWNER_SEM                          (0x00010000U)

/* PCTRACE_GLOBAL */
#define SDL_ERAD_PCTRACE_GLOBAL_EN                          (0x00000001U)
#define SDL_ERAD_PCTRACE_GLOBAL_INIT                        (0x00000100U)
#define SDL_ERAD_PCTRACE_GLOBAL_BUFFER_SIZE_SHIFT           (0x00000016U)
#define SDL_ERAD_PCTRACE_GLOBAL_BUFFER_SIZE_MASK            (0x00030000U)

/* PCTRACE_BUFFER */
#define SDL_ERAD_PCTRACE_BUFFER_PTR_SHIFT                   (0x00000000U)
#define SDL_ERAD_PCTRACE_BUFFER_PTR_MASK                    (0x0000FFFFU)
#define SDL_ERAD_PCTRACE_BUFFER_BUFFER_FULL                 (0x00010000U)

/* PCTRACE_QUAL1 */
#define SDL_ERAD_PCTRACE_QUAL1_WINDOWED_INP_SEL_SHIFT       (0x00000000U)
#define SDL_ERAD_PCTRACE_QUAL1_WINDOWED_INP_SEL_MASK        (0x000000FFU)
#define SDL_ERAD_PCTRACE_QUAL1_TRACE_MODE_SHIFT             (0x00000016U)
#define SDL_ERAD_PCTRACE_QUAL1_TRACE_MODE_MASK              (0x00030000U)
#define SDL_ERAD_PCTRACE_QUAL1_WINDOWED_INP_INV             (0x00040000U)
#define SDL_ERAD_PCTRACE_QUAL1_START_INP_INV                (0x00100000U)
#define SDL_ERAD_PCTRACE_QUAL1_STOP_INP_INV                 (0x00400000U)

/* PCTRACE_QUAL2 */
#define SDL_ERAD_PCTRACE_QUAL2_START_INP_SEL_SHIFT          (0x00000000U)
#define SDL_ERAD_PCTRACE_QUAL2_START_INP_SEL_MASK           (0x000000FFU)
#define SDL_ERAD_PCTRACE_QUAL2_STOP_INP_SEL_SHIFT           (0x00000016U)
#define SDL_ERAD_PCTRACE_QUAL2_STOP_INP_SEL_MASK            (0x00FF0000U)

/* PCTRACE_BUFFER_BASE */
#define SDL_ERAD_PCTRACE_BUFFER_BASE_BLOCKED                (0x00000001U)
#define SDL_ERAD_PCTRACE_BUFFER_BASE_PROGRAM_COUNTER_SHIFT  (0x00000001U)
#define SDL_ERAD_PCTRACE_BUFFER_BASE_PROGRAM_COUNTER_MASK   (0xFFFFFFFEU)

#ifdef __cplusplus
}
#endif
#endif /* SDLR_ERAD_H_ */
