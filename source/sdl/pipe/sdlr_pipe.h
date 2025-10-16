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
#ifndef SDLR_PIPE_H_
#define SDLR_PIPE_H_

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

#define SDL_PIPE_RTINT_THRESHOLD            (0x00000000U)              /* Interrupt threshold register */
#define SDL_PIPE_INT_GRP_MASK               (0x00000004U)              /* Interrupt group mask register */
#define SDL_PIPE_GLOBAL_EN                  (0x00000008U)              /* Global enable for INT and RTINT */
#define SDL_PIPE_REVISION                   (0x0000000CU)              /* Reserved */
#define SDL_PIPE_CPU_INT_STS                (0x00000020U)              /* CPU interrupt status */
#define SDL_PIPE_RST_VECT                   (0x00000024U)              /* Reset vector register */
#define SDL_PIPE_RST_LINK_OWNER             (0x00000028U)              /* Reset link owner register */
#define SDL_PIPE_NMI_STS                    (0x0000002CU)              /* Non Maskable Interrupt status register */
#define SDL_PIPE_NMI_VECT                   (0x00000030U)              /* Non Maskable Interrupt vector register */
#define SDL_PIPE_NMI_LINK_OWNER             (0x00000034U)              /* Non Maskable Interrupt link owner register */
#define SDL_PIPE_MEM_ECC_DIAG               (0x00000040U)              /* ECC diagnostics register */
#define SDL_PIPE_MEM_INIT                   (0x00000044U)              /* PIPE vector memory initialization register */
#define SDL_PIPE_MEM_INIT_STS               (0x00000048U)              /* PIPE memory initialization status register */
#define SDL_PIPE_INT_SEC_STS                (0x0000004CU)              /* Interrupt security status register */
#define SDL_PIPE_INT_SEC_CLR                (0x00000050U)              /* Interrupt security clear register */
#define SDL_PIPE_RTINT_SP_L                 (0x00000060U)              /* RTINT stack limit register */
#define SDL_PIPE_RTINT_SP_H                 (0x00000064U)              /* RTINT stack limit register */
#define SDL_PIPE_RTISP_STS                  (0x00000068U)              /* RTINT Stack pointer violation status register */
#define SDL_PIPE_INTSP                      (0x0000006CU)              /* INT stack pointer */
#define SDL_PIPE_LOCK                       (0x00000080U)              /* PIPE lock register */
#define SDL_PIPE_COMMIT                     (0x00000084U)              /* PIPE commit register */
#define SDL_PIPE_TASK_CTRL                  (0x00000090U)              /* Task control register */
#define SDL_PIPE_BOOT_LINK_CTRL             (0x00000094U)              /* Boot Link control to lock out BOOT_LINK */
#define SDL_PIPE_INT_VECT_MAPPING           (0x00000098U)              /* Interrupt vector mapping for LFU, FOTA, and INT vector 
                                                                       // swapping support */
#define SDL_PIPE_MMR_CLR                    (0x000000A0U)              /* PIPE MMR clear register */
#define SDL_PIPE_ALL_FLAG_CLR               (0x000000A4U)              /* PIPE flag clear register */
#define SDL_PIPE_REG_PARITY_DIAG_DATA       (0x000000B0U)              /* Register parity Diagnostic data */
#define SDL_PIPE_REG_PARITY_DIAG_PARITY     (0x000000B8U)              /* Register parity Diagnostic Parity */
#define SDL_PIPE_REG_PARITY_DIAG_ASSERT     (0x000000C0U)              /* Register parity Assert diagnostic */
#define SDL_PIPE_REG_PARITY_CHECK           (0x000000C8U)              /* Enabling the Parity check */
#define SDL_PIPE_REG_PARITY_READ            (0x000000CCU)              /* Enabling the Parity read */
#define SDL_PIPE_INT_CTL_L(i)               (0x1000U + ((i) * 0x4U))   /* Interrupt low flag and status control register */
#define SDL_PIPE_INT_CTL_H(i)               (0x2000U + ((i) * 0x4U))   /* Interrupt high flag and status control register */
#define SDL_PIPE_INT_CONFIG(i)              (0x3000U + ((i) * 0x4U))   /* Interrupt configuration register */
#define SDL_PIPE_INT_LINK_OWNER(i)          (0x4000U + ((i) * 0x4U))   /* Interrupt link ownership config register */
#define SDL_PIPE_INT_VECT_ADDR(i)           (0x5000U + ((i) * 0x4U))   /* Interrupt vector address */
#define SDL_PIPE_INT_LINK_OWNER_LFU(i)      (0x6000U + ((i) * 0x4U))   /* Interrupt link ownership config register */
#define SDL_PIPE_INT_VECT_ADDR_LFU(i)       (0x7000U + ((i) * 0x4U))   /* Interrupt vector address */
#define SDL_PIPE_SELFTEST_DIAG_DATA0        (0x00008000U)              /* Diagnostics data register 0 */
#define SDL_PIPE_SELFTEST_DIAG_DATA1        (0x00008004U)              /* Diagnostics data register 1 */
#define SDL_PIPE_SELFTEST_DIAG_ECC          (0x00008020U)              /* Diagnostics ECC */
#define SDL_PIPE_SELFTEST_DIAG_CONTROL      (0x00008028U)              /* Diagnostic test enable */
#define SDL_PIPE_SELFTEST_DIAG_STATUS       (0x0000802CU)              /* Diagnostic status register */
#define SDL_PIPE_SELFTEST_DIAG_STATUS_CLR   (0x00008030U)              /* Diagnostic status clear register */

/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* RTINT_THRESHOLD */
#define SDL_PIPE_RTINT_THRESHOLD_INT_SHIFT                          (0x00000000U)
#define SDL_PIPE_RTINT_THRESHOLD_INT_MASK                           (0x000000FFU)

/* INT_GRP_MASK */
#define SDL_PIPE_INT_GRP_MASK_INT_GRP_MASK_SHIFT                    (0x00000000U)
#define SDL_PIPE_INT_GRP_MASK_INT_GRP_MASK_MASK                     (0x000000FFU)

/* GLOBAL_EN */
#define SDL_PIPE_GLOBAL_EN_ENABLE_SHIFT                             (0x00000000U)
#define SDL_PIPE_GLOBAL_EN_ENABLE_MASK                              (0x00000003U)
#define SDL_PIPE_GLOBAL_EN_KEY_SHIFT                                (0x00000016U)
#define SDL_PIPE_GLOBAL_EN_KEY_MASK                                 (0xFFFF0000U)
#define SDL_PIPE_GLOBAL_EN_KEY                                      (0xFACE0000U)

/* REVISION */
#define SDL_PIPE_REVISION_MINREV_SHIFT                              (0x00000000U)
#define SDL_PIPE_REVISION_MINREV_MASK                               (0x000000FFU)
#define SDL_PIPE_REVISION_MAJREV_SHIFT                              (0x00000008U)
#define SDL_PIPE_REVISION_MAJREV_MASK                               (0x0000FF00U)

/* CPU_INT_STS */
#define SDL_PIPE_CPU_INT_STS_LAST_INTSTS_SHIFT                      (0x00000000U)
#define SDL_PIPE_CPU_INT_STS_LAST_INTSTS_MASK                       (0x00000003U)
#define SDL_PIPE_CPU_INT_STS_LAST_INT_PRIOLVL_SHIFT                 (0x00000008U)
#define SDL_PIPE_CPU_INT_STS_LAST_INT_PRIOLVL_MASK                  (0x0000FF00U)
#define SDL_PIPE_CPU_INT_STS_LAST_RTINT_PRIOLVL_SHIFT               (0x00000016U)
#define SDL_PIPE_CPU_INT_STS_LAST_RTINT_PRIOLVL_MASK                (0x00FF0000U)

/* RST_LINK_OWNER */
#define SDL_PIPE_RST_LINK_OWNER_LINK_OWNER_SHIFT                    (0x00000000U)
#define SDL_PIPE_RST_LINK_OWNER_LINK_OWNER_MASK                     (0x0000000FU)

/* NMI_STS */
#define SDL_PIPE_NMI_STS_NMI_FLAG                                   (0x00000001U)
#define SDL_PIPE_NMI_STS_NMI_CLR                                    (0x00000002U)

/* NMI_LINK_OWNER */
#define SDL_PIPE_NMI_LINK_OWNER_LINK_OWNER_SHIFT                    (0x00000000U)
#define SDL_PIPE_NMI_LINK_OWNER_LINK_OWNER_MASK                     (0x0000000FU)

/* MEM_ECC_DIAG */
#define SDL_PIPE_MEM_ECC_DIAG_ECC_VIEW                              (0x00000001U)
#define SDL_PIPE_MEM_ECC_DIAG_MEM_SIC_DIAG_EN                       (0x00000002U)
#define SDL_PIPE_MEM_ECC_DIAG_KEY_SHIFT                             (0x00000016U)
#define SDL_PIPE_MEM_ECC_DIAG_KEY_MASK                              (0xFFFF0000U)
#define SDL_PIPE_MEM_ECC_DIAG_KEY                                   (0x5A5A0000U)

/* MEM_INIT */
#define SDL_PIPE_MEM_INIT_INIT_SHIFT                                (0x00000000U)
#define SDL_PIPE_MEM_INIT_INIT_MASK                                 (0x00000003U)
#define SDL_PIPE_MEM_INIT_KEY_SHIFT                                 (0x00000016U)
#define SDL_PIPE_MEM_INIT_KEY_MASK                                  (0xFFFF0000U)
#define SDL_PIPE_MEM_INIT_KEY                                       (0x5A5A0000U)

/* MEM_INIT_STS */
#define SDL_PIPE_MEM_INIT_STS_INIT_STS_SHIFT                        (0x00000000U)
#define SDL_PIPE_MEM_INIT_STS_INIT_STS_MASK                         (0x00000003U)

/* INT_SEC_STS */
#define SDL_PIPE_INT_SEC_STS_SEC_FAIL_FLAG                          (0x00000001U)

/* INT_SEC_CLR */
#define SDL_PIPE_INT_SEC_CLR_SEC_FAIL_FLAG_CLR                      (0x00000001U)

/* RTINT_SP_L */
#define SDL_PIPE_RTINT_SP_L_RTISP_SHIFT                             (0x00000000U)
#define SDL_PIPE_RTINT_SP_L_RTISP_MASK                              (0x0000001FU)
#define SDL_PIPE_RTINT_SP_L_MAXRTISP_SHIFT                          (0x00000008U)
#define SDL_PIPE_RTINT_SP_L_MAXRTISP_MASK                           (0x00001F00U)

/* RTINT_SP_H */
#define SDL_PIPE_RTINT_SP_H_WARNRTISP_SHIFT                         (0x00000000U)
#define SDL_PIPE_RTINT_SP_H_WARNRTISP_MASK                          (0x0000001FU)
#define SDL_PIPE_RTINT_SP_H_WARNRTISP_PRIO_LEVEL_SHIFT              (0x00000008U)
#define SDL_PIPE_RTINT_SP_H_WARNRTISP_PRIO_LEVEL_MASK               (0x00001F00U)

/* RTISP_STS */
#define SDL_PIPE_RTISP_STS_WARNRTISP_STS                            (0x00000001U)
#define SDL_PIPE_RTISP_STS_MAXRTISP_STS                             (0x00000002U)

/* INTSP */
#define SDL_PIPE_INTSP_INTSP_SHIFT                                  (0x00000000U)
#define SDL_PIPE_INTSP_INTSP_MASK                                   (0x0000000FU)

/* LOCK */
#define SDL_PIPE_LOCK_LINK_LOCK                                     (0x00000001U)
#define SDL_PIPE_LOCK_CONFIG_LOCK                                   (0x00000002U)
#define SDL_PIPE_LOCK_GLOBAL_LOCK                                   (0x00000004U)
#define SDL_PIPE_LOCK_VECT_LOCK                                     (0x00000008U)
#define SDL_PIPE_LOCK_KEY_SHIFT                                     (0x00000016U)
#define SDL_PIPE_LOCK_KEY_MASK                                      (0xFFFF0000U)
#define SDL_PIPE_LOCK_KEY                                           (0x5A5A0000U)

/* COMMIT */
#define SDL_PIPE_COMMIT_LINK_COMMIT                                 (0x00000001U)
#define SDL_PIPE_COMMIT_CONFIG_COMMIT                               (0x00000002U)
#define SDL_PIPE_COMMIT_GLOBAL_COMMIT                               (0x00000004U)
#define SDL_PIPE_COMMIT_VECT_COMMIT                                 (0x00000008U)
#define SDL_PIPE_COMMIT_KEY_SHIFT                                   (0x00000016U)
#define SDL_PIPE_COMMIT_KEY_MASK                                    (0xFFFF0000U)
#define SDL_PIPE_COMMIT_KEY                                         (0x5A5A0000U)

/* TASK_CTRL */
#define SDL_PIPE_TASK_CTRL_ACTIVE_CONTEXT_ID_SHIFT                  (0x00000000U)
#define SDL_PIPE_TASK_CTRL_ACTIVE_CONTEXT_ID_MASK                   (0x00000003U)
#define SDL_PIPE_TASK_CTRL_SUP_IGN_INTE_EN                          (0x00000100U)
#define SDL_PIPE_TASK_CTRL_KEY_SHIFT                                (0x00000016U)
#define SDL_PIPE_TASK_CTRL_KEY_MASK                                 (0xFFFF0000U)
#define SDL_PIPE_TASK_CTRL_KEY                                      (0xCAFE0000U) 

/* BOOT_LINK_CTRL */
#define SDL_PIPE_BOOT_LINK_CTRL_BOOT_LINK_LOCK                      (0x00000001U)
#define SDL_PIPE_BOOT_LINK_CTRL_KEY_SHIFT                           (0x00000016U)
#define SDL_PIPE_BOOT_LINK_CTRL_KEY_MASK                            (0xFFFF0000U)
#define SDL_PIPE_BOOT_LINK_CTRL_KEY                                 (0xFACE0000U)

/* INT_VECT_MAPPING */
#define SDL_PIPE_INT_VECT_MAPPING_LFU_INT_VECT_MAPPING_SHIFT        (0x00000000U)
#define SDL_PIPE_INT_VECT_MAPPING_LFU_INT_VECT_MAPPING_MASK         (0x00000003U)
#define SDL_PIPE_INT_VECT_MAPPING_KEY_SHIFT                         (0x00000016U)
#define SDL_PIPE_INT_VECT_MAPPING_KEY_MASK                          (0xFFFF0000U)
#define SDL_PIPE_INT_VECT_MAPPING_KEY                               (0xCAFE0000U)

/* MMR_CLR */
#define SDL_PIPE_MMR_CLR_MMR_CLR_SHIFT                              (0x00000000U)
#define SDL_PIPE_MMR_CLR_MMR_CLR_MASK                               (0x00000003U)

/* ALL_FLAG_CLR */
#define SDL_PIPE_ALL_FLAG_CLR_SHIFT                                 (0x00000000U)
#define SDL_PIPE_ALL_FLAG_CLR_MASK                                  (0x00000003U)
#define SDL_PIPE_ALL_FLAG_CLR_KEY_SHIFT                             (0x00000016U)
#define SDL_PIPE_ALL_FLAG_CLR_KEY_MASK                              (0xFFFF0000U)
#define SDL_PIPE_ALL_FLAG_CLR_KEY                                   (0xFEED0000U)

/* REG_PARITY_DIAG_PARITY */
#define SDL_PIPE_REG_PARITY_DIAG_DATA_SHIFT                         (0x00000000U)
#define SDL_PIPE_REG_PARITY_DIAG_DATA_MASK                          (0x0000000FU)

/* REG_PARITY_DIAG_ASSERT */
#define SDL_PIPE_REG_PARITY_DIAG_ASSERT_DIAG_ASSERT                 (0x00000001U)
#define SDL_PIPE_REG_PARITY_DIAG_ASSERT_KEY_SHIFT                   (0x00000016U)
#define SDL_PIPE_REG_PARITY_DIAG_ASSERT_KEY_MASK                    (0xFFFF0000U)

/* REG_PARITY_CHECK */
#define SDL_PIPE_REG_PARITY_CHECK_MODE_SHIFT                        (0x00000000U)
#define SDL_PIPE_REG_PARITY_CHECK_MODE_MASK                         (0x0000000FU)
#define SDL_PIPE_REG_PARITY_CHECK_KEY_SHIFT                         (0x00000016U)
#define SDL_PIPE_REG_PARITY_CHECK_KEY_MASK                          (0xFFFF0000U)

/* REG_PARITY_READ */
#define SDL_PIPE_REG_PARITY_READ_PARITY_READ_EN_SHIFT               (0x00000000U)
#define SDL_PIPE_REG_PARITY_READ_PARITY_READ_EN_MASK                (0x0000000FU)
#define SDL_PIPE_REG_PARITY_READ_KEY_SHIFT                          (0x00000016U)
#define SDL_PIPE_REG_PARITY_READ_KEY_MASK                           (0xFFFF0000U)

/* INT_CTL_L */
#define SDL_PIPE_INT_CTL_L_EN                                       (0x00000001U)
#define SDL_PIPE_INT_CTL_L_FLAG                                     (0x00000002U)
#define SDL_PIPE_INT_CTL_L_OVERFLOW_FLAG                            (0x00000004U)

/* INT_CTL_H */
#define SDL_PIPE_INT_CTL_H_FLAG_FRC                                 (0x00000001U)
#define SDL_PIPE_INT_CTL_H_FLAG_CLR                                 (0x00000002U)
#define SDL_PIPE_INT_CTL_H_OVERFLOW_FLAG_CLR                        (0x00000004U)

/* INT_CONFIG */
#define SDL_PIPE_INT_CONFIG_PRI_LEVEL_SHIFT                         (0x00000000U)
#define SDL_PIPE_INT_CONFIG_PRI_LEVEL_MASK                          (0x000000FFU)
#define SDL_PIPE_INT_CONFIG_CONTEXT_ID_SHIFT                        (0x00000016U)
#define SDL_PIPE_INT_CONFIG_CONTEXT_ID_MASK                         (0x00030000U)

/* INT_LINK_OWNER */
#define SDL_PIPE_INT_LINK_OWNER_OWNER_LINK_SHIFT                    (0x00000000U)
#define SDL_PIPE_INT_LINK_OWNER_OWNER_LINK_MASK                     (0x0000000FU)
#define SDL_PIPE_INT_LINK_OWNER_API_LINK_SHIFT                      (0x00000004U)
#define SDL_PIPE_INT_LINK_OWNER_API_LINK_MASK                       (0x000000F0U)
#define SDL_PIPE_INT_LINK_OWNER_API_LINK_EN                         (0x00000100U)

/* INT_LINK_OWNER_LFU */
#define SDL_PIPE_INT_LINK_OWNER_LFU_OWNER_LINK_SHIFT                (0x00000000U)
#define SDL_PIPE_INT_LINK_OWNER_LFU_OWNER_LINK_MASK                 (0x0000000FU)
#define SDL_PIPE_INT_LINK_OWNER_LFU_API_LINK_SHIFT                  (0x00000004U)
#define SDL_PIPE_INT_LINK_OWNER_LFU_API_LINK_MASK                   (0x000000F0U)
#define SDL_PIPE_INT_LINK_OWNER_LFU_API_LINK_EN                     (0x00000100U)

/* SELFTEST_DIAG_DATA1 */
#define SDL_PIPE_SELFTEST_DIAG_DATA1_SHIFT                          (0x00000000U)
#define SDL_PIPE_SELFTEST_DIAG_DATA1_MASK                           (0x000FFFFFU)

/* SELFTEST_DIAG_ECC */
#define SDL_PIPE_SELFTEST_DIAG_ECC_SHIFT                            (0x00000000U)
#define SDL_PIPE_SELFTEST_DIAG_ECC_MASK                             (0x0000007FU)

/* SELFTEST_DIAG_CONTROL */
#define SDL_PIPE_SELFTEST_DIAG_CONTROL_DIAG_TEST_EN_SHIFT           (0x00000000U)
#define SDL_PIPE_SELFTEST_DIAG_CONTROL_DIAG_TEST_EN_MASK            (0x0000000FU)
#define SDL_PIPE_SELFTEST_DIAG_CONTROL_DIAG_ECC_WIDTH_SHIFT         (0x00000016U)
#define SDL_PIPE_SELFTEST_DIAG_CONTROL_DIAG_ECC_WIDTH_MASK          (0x000F0000U)
#define SDL_PIPE_SELFTEST_DIAG_CONTROL_DIAG_DATA_WIDTH_SHIFT        (0x00000024U)
#define SDL_PIPE_SELFTEST_DIAG_CONTROL_DIAG_DATA_WIDTH_MASK         (0xFF000000U)

/* SELFTEST_DIAG_STATUS */
#define SDL_PIPE_SELFTEST_DIAG_STATUS_DIAG_TEST_DONE                (0x00000002U)
#define SDL_PIPE_SELFTEST_DIAG_STATUS_DIAG_TEST_FAIL                (0x00000004U)
#define SDL_PIPE_SELFTEST_DIAG_STATUS_DIAG_FAIL_C_ERROR             (0x000000008U)
#define SDL_PIPE_SELFTEST_DIAG_STATUS_DIAG_FAIL_UC_ERROR            (0x00000010U)
#define SDL_PIPE_SELFTEST_DIAG_STATUS_DIAG_FAIL_CHECK_TYPE_SHIFT    (0x00000005U)
#define SDL_PIPE_SELFTEST_DIAG_STATUS_DIAG_FAIL_CHECK_TYPE_MASK     (0x00000060U)
#define SDL_PIPE_SELFTEST_DIAG_STATUS_DIAG_FAIL_BIT_INDEX_SHIFT     (0x00000008U)
#define SDL_PIPE_SELFTEST_DIAG_STATUS_DIAG_FAIL_BIT_INDEX_MASK      (0x0000FF00U)

/* SELFTEST_DIAG_STATUS_CLR */
#define SDL_PIPE_SELFTEST_DIAG_STATUS_CLR_DIAG_TEST_DONE            (0x00000002U)
#define SDL_PIPE_SELFTEST_DIAG_STATUS_CLR_DIAG_TEST_FAIL            (0x00000004U)

#ifdef __cplusplus
}
#endif
#endif /* SDLR_PIPE_H_ */
