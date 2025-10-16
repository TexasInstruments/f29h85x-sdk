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
#ifndef SDLR_ERR_AGGR_H_
#define SDLR_ERR_AGGR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define SDL_ERR_AGGR_CPU1_PR_HIGHPRIO_ERRADDR                      0x00000000U /* CPU1 PR Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU1_PR_LOWPRIO_ERRADDR                       0x00000004U /* CPU1 PR Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU1_PR_ERRTYPE                               0x00000008U /* CPU1 PR Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU1_PR_ERRTYPE_FRC                           0x0000000CU /* CPU1 PR Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU1_PR_ERRTYPE_CLR                           0x00000010U /* CPU1 PR Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU1_PR_PC                                    0x00000014U /* CPU1 PR Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU1_DR1_HIGHPRIO_ERRADDR                     0x00000040U /* CPU1 DR1 Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU1_DR1_LOWPRIO_ERRADDR                      0x00000044U /* CPU1 DR1 Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU1_DR1_ERRTYPE                              0x00000048U /* CPU1 DR1 Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU1_DR1_ERRTYPE_FRC                          0x0000004CU /* CPU1 DR1 Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU1_DR1_ERRTYPE_CLR                          0x00000050U /* CPU1 DR1 Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU1_DR1_PC                                   0x00000054U /* CPU1 DR1 Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU1_DR2_HIGHPRIO_ERRADDR                     0x00000080U /* CPU1 DR2 Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU1_DR2_LOWPRIO_ERRADDR                      0x00000084U /* CPU1 DR2 Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU1_DR2_ERRTYPE                              0x00000088U /* CPU1 DR2 Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU1_DR2_ERRTYPE_FRC                          0x0000008CU /* CPU1 DR2 Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU1_DR2_ERRTYPE_CLR                          0x00000090U /* CPU1 DR2 Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU1_DR2_PC                                   0x00000094U /* CPU1 DR2 Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU1_DW_HIGHPRIO_ERRADDR                      0x000000C0U /* CPU1 DW Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU1_DW_LOWPRIO_ERRADDR                       0x000000C4U /* CPU1 DW Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU1_DW_ERRTYPE                               0x000000C8U /* CPU1 DW Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU1_DW_ERRTYPE_FRC                           0x000000CCU /* CPU1 DW Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU1_DW_ERRTYPE_CLR                           0x000000D0U /* CPU1 DW Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU1_DW_PC                                    0x000000D4U /* CPU1 DW Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU1_INT_HIGHPRIO_ERRADDR                     0x00000100U /* CPU1 INT Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU1_INT_LOWPRIO_ERRADDR                      0x00000104U /* CPU1 INT Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU1_INT_ERRTYPE                              0x00000108U /* CPU1 INT Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU1_INT_ERRTYPE_FRC                          0x0000010CU /* CPU1 INT Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU1_INT_ERRTYPE_CLR                          0x00000110U /* CPU1 INT Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU1_INT_PC                                   0x00000114U /* CPU1 INT Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU2_PR_HIGHPRIO_ERRADDR                      0x00000140U /* CPU2 PR Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU2_PR_LOWPRIO_ERRADDR                       0x00000144U /* CPU2 PR Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU2_PR_ERRTYPE                               0x00000148U /* CPU2 PR Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU2_PR_ERRTYPE_FRC                           0x0000014CU /* CPU2 PR Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU2_PR_ERRTYPE_CLR                           0x00000150U /* CPU2 PR Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU2_PR_PC                                    0x00000154U /* CPU2 PR Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU2_DR1_HIGHPRIO_ERRADDR                     0x00000180U /* CPU2 DR1 Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU2_DR1_LOWPRIO_ERRADDR                      0x00000184U /* CPU2 DR1 Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU2_DR1_ERRTYPE                              0x00000188U /* CPU2 DR1 Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU2_DR1_ERRTYPE_FRC                          0x0000018CU /* CPU2 DR1 Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU2_DR1_ERRTYPE_CLR                          0x00000190U /* CPU2 DR1 Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU2_DR1_PC                                   0x00000194U /* CPU2 DR1 Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU2_DR2_HIGHPRIO_ERRADDR                     0x000001C0U /* CPU2 DR2 Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU2_DR2_LOWPRIO_ERRADDR                      0x000001C4U /* CPU2 DR2 Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU2_DR2_ERRTYPE                              0x000001C8U /* CPU2 DR2 Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU2_DR2_ERRTYPE_FRC                          0x000001CCU /* CPU2 DR2 Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU2_DR2_ERRTYPE_CLR                          0x000001D0U /* CPU2 DR2 Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU2_DR2_PC                                   0x000001D4U /* CPU2 DR2 Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU2_DW_HIGHPRIO_ERRADDR                      0x00000200U /* CPU2 DW Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU2_DW_LOWPRIO_ERRADDR                       0x00000204U /* CPU2 DW Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU2_DW_ERRTYPE                               0x00000208U /* CPU2 DW Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU2_DW_ERRTYPE_FRC                           0x0000020CU /* CPU2 DW Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU2_DW_ERRTYPE_CLR                           0x00000210U /* CPU2 DW Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU2_DW_PC                                    0x00000214U /* CPU2 DW Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU2_INT_HIGHPRIO_ERRADDR                     0x00000240U /* CPU2 INT Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU2_INT_LOWPRIO_ERRADDR                      0x00000244U /* CPU2 INT Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU2_INT_ERRTYPE                              0x00000248U /* CPU2 INT Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU2_INT_ERRTYPE_FRC                          0x0000024CU /* CPU2 INT Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU2_INT_ERRTYPE_CLR                          0x00000250U /* CPU2 INT Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU2_INT_PC                                   0x00000254U /* CPU2 INT Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU3_PR_HIGHPRIO_ERRADDR                      0x00000280U /* CPU3 PR Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU3_PR_LOWPRIO_ERRADDR                       0x00000284U /* CPU3 PR Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU3_PR_ERRTYPE                               0x00000288U /* CPU3 PR Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU3_PR_ERRTYPE_FRC                           0x0000028CU /* CPU3 PR Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU3_PR_ERRTYPE_CLR                           0x00000290U /* CPU3 PR Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU3_PR_PC                                    0x00000294U /* CPU3 DR1 Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU3_DR1_HIGHPRIO_ERRADDR                     0x000002C0U /* CPU3 DR1 Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU3_DR1_LOWPRIO_ERRADDR                      0x000002C4U /* CPU3 DR1 Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU3_DR1_ERRTYPE                              0x000002C8U /* CPU3 DR1 Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU3_DR1_ERRTYPE_FRC                          0x000002CCU /* CPU3 DR1 Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU3_DR1_ERRTYPE_CLR                          0x000002D0U /* CPU3 DR1 Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU3_DR1_PC                                   0x000002D4U /* CPU3 DR1 Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU3_DR2_HIGHPRIO_ERRADDR                     0x00000300U /* CPU3 DR2 Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU3_DR2_LOWPRIO_ERRADDR                      0x00000304U /* CPU3 DR2 Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU3_DR2_ERRTYPE                              0x00000308U /* CPU3 DR2 Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU3_DR2_ERRTYPE_FRC                          0x0000030CU /* CPU3 DR2 Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU3_DR2_ERRTYPE_CLR                          0x00000310U /* CPU3 DR2 Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU3_DR2_PC                                   0x00000314U /* CPU3 DR2 Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU3_DW_HIGHPRIO_ERRADDR                      0x00000340U /* CPU3 DW Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU3_DW_LOWPRIO_ERRADDR                       0x00000344U /* CPU3 DW Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU3_DW_ERRTYPE                               0x00000348U /* CPU3 DW Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU3_DW_ERRTYPE_FRC                           0x0000034CU /* CPU3 DW Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU3_DW_ERRTYPE_CLR                           0x00000350U /* CPU3 DW Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU3_DW_PC                                    0x00000354U /* CPU3 DW Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_CPU3_INT_HIGHPRIO_ERRADDR                     0x00000380U /* CPU3 INT Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_CPU3_INT_LOWPRIO_ERRADDR                      0x00000384U /* CPU3 INT Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_CPU3_INT_ERRTYPE                              0x00000388U /* CPU3 INT Error aggregator Error Type Register */
#define SDL_ERR_AGGR_CPU3_INT_ERRTYPE_FRC                          0x0000038CU /* CPU3 INT Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_CPU3_INT_ERRTYPE_CLR                          0x00000390U /* CPU3 INT Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_CPU3_INT_PC                                   0x00000394U /* CPU3 INT Error aggregator Register to store PC value at the first High priority error event */
#define SDL_ERR_AGGR_RTDMA1_DR_HIGHPRIO_ERRADDR                    0x00000780U /* RTDMA1 DR Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_RTDMA1_DR_LOWPRIO_ERRADDR                     0x00000784U /* RTDMA1 DR Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_RTDMA1_DR_ERRTYPE                             0x00000788U /* RTDMA1 DR Error aggregator Error Type Register */
#define SDL_ERR_AGGR_RTDMA1_DR_ERRTYPE_FRC                         0x0000078CU /* RTDMA1 DR Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_RTDMA1_DR_ERRTYPE_CLR                         0x00000790U /* RTDMA1 DR Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_RTDMA1_DW_HIGHPRIO_ERRADDR                    0x000007C0U /* RTDMA1 DW Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_RTDMA1_DW_LOWPRIO_ERRADDR                     0x000007C4U /* RTDMA1 DW Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_RTDMA1_DW_ERRTYPE                             0x000007C8U /* RTDMA1 DW Error aggregator Error Type Register */
#define SDL_ERR_AGGR_RTDMA1_DW_ERRTYPE_FRC                         0x000007CCU /* RTDMA1 DW Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_RTDMA1_DW_ERRTYPE_CLR                         0x000007D0U /* RTDMA1 DW Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_RTDMA2_DR_HIGHPRIO_ERRADDR                    0x00000800U /* RTDMA2 DR Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_RTDMA2_DR_LOWPRIO_ERRADDR                     0x00000804U /* RTDMA2 DR Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_RTDMA2_DR_ERRTYPE                             0x00000808U /* RTDMA2 DR Error aggregator Error Type Register */
#define SDL_ERR_AGGR_RTDMA2_DR_ERRTYPE_FRC                         0x0000080CU /* RTDMA2 DR Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_RTDMA2_DR_ERRTYPE_CLR                         0x00000810U /* RTDMA2 DR Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_RTDMA2_DW_HIGHPRIO_ERRADDR                    0x00000840U /* RTDMA2 DW Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_RTDMA2_DW_LOWPRIO_ERRADDR                     0x00000844U /* RTDMA2 DW Error aggregator Low Priority Error address register */
#define SDL_ERR_AGGR_RTDMA2_DW_ERRTYPE                             0x00000848U /* RTDMA2 DW Error aggregator Error Type Register */
#define SDL_ERR_AGGR_RTDMA2_DW_ERRTYPE_FRC                         0x0000084CU /* RTDMA2 DW Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_RTDMA2_DW_ERRTYPE_CLR                         0x00000850U /* RTDMA2 DW Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_SSU_HIGHPRIO_ERRADDR                          0x00000880U /* SSU Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_SSU_ERRTYPE                                   0x00000888U /* SSU Error aggregator Error Type Register */
#define SDL_ERR_AGGR_SSU_ERRTYPE_FRC                               0x0000088CU /* SSU Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_SSU_ERRTYPE_CLR                               0x00000890U /* SSU Error aggregator Error Type Clear Register */
#define SDL_ERR_AGGR_ETHERCAT_HIGHPRIO_ERRADDR                     0x000008C0U /* ETHERCAT Error aggregator High Priority Error address register */
#define SDL_ERR_AGGR_ETHERCAT_ERRTYPE                              0x000008C8U /* ETHERCAT Error aggregator Error Type Register */
#define SDL_ERR_AGGR_ETHERCAT_ERRTYPE_FRC                          0x000008CCU /* ETHERCAT Error aggregator Error Type Force Register */
#define SDL_ERR_AGGR_ETHERCAT_ERRTYPE_CLR                          0x000008D0U /* ETHERCAT Error aggregator Error Type Clear Register */

/**************************************************************************
* Field Definition Macros
**************************************************************************/

#define SDL_ERR_AGGR_TYPE_MASK                                  (0xFFFFFFFFU)
#define SDL_ERR_AGGR_TYPE_SHIFT                                 (0x00000000U)

/* CPU1_PR_HIGHPRIO_ERRADDR */

#define SDL_ERR_AGGR_TYPE_HIGHPRIO_ERRADDR_MASK                 (0xFFFFFFFFU)
#define SDL_ERR_AGGR_TYPE_HIGHPRIO_ERRADDR_SHIFT                (0x00000000U)

/* CPU1_PR_LOWPRIO_ERRADDR */

#define SDL_ERR_AGGR_TYPE_LOWPRIO_ERRADDR_MASK                  (0xFFFFFFFFU)
#define SDL_ERR_AGGR_TYPE_LOWPRIO_ERRADDR_SHIFT                 (0x00000000U)

/* ERROR_TYPE */

#define SDL_ERR_AGGR_TYPE_HP_SOFTWARE_MASK                      (0x80000000U)
#define SDL_ERR_AGGR_TYPE_HP_SOFTWARE_SHIFT                     (0x0000001FU)

#define SDL_ERR_AGGR_TYPE_LP_SOFTWARE_MASK                      (0x40000000U)
#define SDL_ERR_AGGR_TYPE_LP_SOFTWARE_SHIFT                     (0x0000001EU)

#define SDL_ERR_AGGR_TYPE_INSTR_TIMEOUT_MASK                    (0x00000800U)
#define SDL_ERR_AGGR_TYPE_INSTR_TIMEOUT_SHIFT                   (0x0000000BU)

#define SDL_ERR_AGGR_TYPE_ILLEGAL_INSTR_MASK                    (0x00000400U)
#define SDL_ERR_AGGR_TYPE_ILLEGAL_INSTR_SHIFT                   (0x0000000AU)

#define SDL_ERR_AGGR_TYPE_SW_BRKPOINT_MASK                      (0x00000200U)
#define SDL_ERR_AGGR_TYPE_SW_BRKPOINT_SHIFT                     (0x00000009U)

#define SDL_ERR_AGGR_TYPE_WARN_PSP_MASK                         (0x00000100U)
#define SDL_ERR_AGGR_TYPE_WARN_PSP_SHIFT                        (0x00000008U)

#define SDL_ERR_AGGR_TYPE_CERR_MASK                             (0x00000080U)
#define SDL_ERR_AGGR_TYPE_CERR_SHIFT                            (0x00000007U)

#define SDL_ERR_AGGR_TYPE_UNCERR_MASK                           (0x00000040U)
#define SDL_ERR_AGGR_TYPE_UNCERR_SHIFT                          (0x00000006U)

#define SDL_ERR_AGGR_TYPE_ACC_ACK_MASK                          (0x00000020U)
#define SDL_ERR_AGGR_TYPE_ACC_ACK_SHIFT                         (0x00000005U)

#define SDL_ERR_AGGR_TYPE_ACC_TIMEOUT_MASK                      (0x00000010U)
#define SDL_ERR_AGGR_TYPE_ACC_TIMEOUT_SHIFT                     (0x00000004U)

#define SDL_ERR_AGGR_TYPE_MAX_PSP_MASK                          (0x00000008U)
#define SDL_ERR_AGGR_TYPE_MAX_PSP_SHIFT                         (0x00000003U)

#define SDL_ERR_AGGR_TYPE_SEC_EXIT_VIO_MASK                     (0x00000004U)
#define SDL_ERR_AGGR_TYPE_SEC_EXIT_VIO_SHIFT                    (0x00000002U)

#define SDL_ERR_AGGR_TYPE_SEC_ENTRY_VIO_MASK                    (0x00000002U)
#define SDL_ERR_AGGR_TYPE_SEC_ENTRY_VIO_SHIFT                   (0x00000001U)

#define SDL_ERR_AGGR_TYPE_INSTR_SECURITY_VIO_MASK               (0x00000001U)
#define SDL_ERR_AGGR_TYPE_INSTR_SECURITY_VIO_SHIFT              (0x00000000U)


/* CPUx_Data_ERROR_TYPE */

#define SDL_ERR_AGGR_DTYPE_UNALIGHED_ADDR_MASK                  (0x00000100U)
#define SDL_ERR_AGGR_DTYPE_UNALIGHED_ADDR_SHIFT                 (0x00000008U)

#define SDL_ERR_AGGR_DTYPE_SECURITY_VIO_MASK                    (0x00000001U)
#define SDL_ERR_AGGR_DTYPE_SECURITY_VIO_SHIFT                   (0x00000000U)

/* CPUx_INT_ERROR_TYPE */

#define SDL_ERR_AGGR_INT_TYPE_PIPE_LOCK_KEY_MASK                (0x20000000U)
#define SDL_ERR_AGGR_INT_TYPE_PIPE_LOCK_KEY_SHIFT               (0x0000001DU)

#define SDL_ERR_AGGR_INT_TYPE_PIPE_REGPAR_DIAG_MASK             (0x10000000U)
#define SDL_ERR_AGGR_INT_TYPE_PIPE_REGPAR_DIAG_SHIFT            (0x0000001CU)

#define SDL_ERR_AGGR_INT_TYPE_PIPE_REGPAR_MASK                  (0x08000000U)
#define SDL_ERR_AGGR_INT_TYPE_PIPE_REGPAR_SHIFT                 (0x0000001BU)

#define SDL_ERR_AGGR_INT_TYPE_PIPE_SECURITY_VIO_MASK            (0x04000000U)
#define SDL_ERR_AGGR_INT_TYPE_PIPE_SECURITY_VIO_SHIFT           (0x0000001AU)

#define SDL_ERR_AGGR_INT_TYPE_MAX_ISP_MASK                      (0x02000000U)
#define SDL_ERR_AGGR_INT_TYPE_MAX_ISP_SHIFT                     (0x00000019U)

#define SDL_ERR_AGGR_INT_TYPE_WARN_ISP_MASK                     (0x01000000U)
#define SDL_ERR_AGGR_INT_TYPE_WARN_ISP_SHIFT                    (0x00000018U)

#define SDL_ERR_AGGR_INT_TYPE_VEC_UNCERR_MASK                   (0x00800000U)
#define SDL_ERR_AGGR_INT_TYPE_VEC_UNCERR_SHIFT                  (0x00000017U)

#define SDL_ERR_AGGR_INT_TYPE_VEC_CERR_MASK                     (0x00400000U)
#define SDL_ERR_AGGR_INT_TYPE_VEC_CERR_SHIFT                    (0x00000016U)

#define SDL_ERR_AGGR_INT_TYPE_NMI_CNTRESTORE_VEC_UNCERR_MASK    (0x00200000U)
#define SDL_ERR_AGGR_INT_TYPE_NMI_CNTRESTORE_VEC_UNCERR_SHIFT   (0x00000015U)

#define SDL_ERR_AGGR_INT_TYPE_NMI_CNTRESTORE_VEC_CERR_MASK      (0x00100000U)
#define SDL_ERR_AGGR_INT_TYPE_NMI_CNTRESTORE_VEC_CERR_SHIFT     (0x00000014U)

#define SDL_ERR_AGGR_INT_TYPE_NMI_INTR_RET_MASK                 (0x00080000U)
#define SDL_ERR_AGGR_INT_TYPE_NMI_INTR_RET_SHIFT                (0x00000013U)

#define SDL_ERR_AGGR_INT_TYPE_NMI_VEC_UNCERR_MASK               (0x00040000U)
#define SDL_ERR_AGGR_INT_TYPE_NMI_VEC_UNCERR_SHIFT              (0x00000012U)

#define SDL_ERR_AGGR_INT_TYPE_NMI_VEC_CERR_MASK                 (0x00020000U)
#define SDL_ERR_AGGR_INT_TYPE_NMI_VEC_CERR_SHIFT                (0x00000011U)

#define SDL_ERR_AGGR_INT_TYPE_NMI_ISRENTRY_MASK                 (0x00010000U)
#define SDL_ERR_AGGR_INT_TYPE_NMI_ISRENTRY_SHIFT                (0x00000010U)

#define SDL_ERR_AGGR_INT_TYPE_NMI_MAXISP_MASK                   (0x00008000U)
#define SDL_ERR_AGGR_INT_TYPE_NMI_MAXISP_SHIFT                  (0x0000000FU)

#define SDL_ERR_AGGR_INT_TYPE_RTINT_CNTRESTORE_VEC_UNCERR_MASK  (0x00002000U)
#define SDL_ERR_AGGR_INT_TYPE_RTINT_CNTRESTORE_VEC_UNCERR_SHIFT (0x0000000DU)

#define SDL_ERR_AGGR_INT_TYPE_RTINT_CNTRESTORE_VEC_CERR_MASK    (0x00001000U)
#define SDL_ERR_AGGR_INT_TYPE_RTINT_CNTRESTORE_VEC_CERR_SHIFT   (0x0000000CU)

#define SDL_ERR_AGGR_INT_TYPE_RTINT_INTR_RET_MASK               (0x00000800U)
#define SDL_ERR_AGGR_INT_TYPE_RTINT_INTR_RET_SHIFT              (0x0000000BU)

#define SDL_ERR_AGGR_INT_TYPE_RTINT_VEC_UNCERR_MASK             (0x00000400U)
#define SDL_ERR_AGGR_INT_TYPE_RTINT_VEC_UNCERR_SHIFT            (0x0000000AU)

#define SDL_ERR_AGGR_INT_TYPE_RTINT_VEC_CERR_MASK               (0x00000200U)
#define SDL_ERR_AGGR_INT_TYPE_RTINT_VEC_CERR_SHIFT              (0x00000009U)

#define SDL_ERR_AGGR_INT_TYPE_RTINT_ISR_ENTRY_MASK              (0x00000100U)
#define SDL_ERR_AGGR_INT_TYPE_RTINT_ISR_ENTRY_SHIFT             (0x00000008U)

#define SDL_ERR_AGGR_INT_TYPE_INT_INTR_RET_MASK                 (0x00000080U)
#define SDL_ERR_AGGR_INT_TYPE_INT_INTR_RET_SHIFT                (0x00000007U)

#define SDL_ERR_AGGR_INT_TYPE_INT_UNCERR_VEC_MASK               (0x00000040U)
#define SDL_ERR_AGGR_INT_TYPE_INT_UNCERR_VEC_SHIFT              (0x00000006U)

#define SDL_ERR_AGGR_INT_TYPE_INT_CERR_VEC_MASK                 (0x00000020U)
#define SDL_ERR_AGGR_INT_TYPE_INT_CERR_VEC_SHIFT                (0x00000005U)

#define SDL_ERR_AGGR_INT_TYPE_INT_ISR_ENTRY_MASK                (0x00000010U)
#define SDL_ERR_AGGR_INT_TYPE_INT_ISR_ENTRY_SHIFT               (0x00000004U)

#define SDL_ERR_AGGR_INT_TYPE_MAIN_INTR_RET_MASK                (0x00000008U)
#define SDL_ERR_AGGR_INT_TYPE_MAIN_INTR_RET_SHIFT               (0x00000003U)

#define SDL_ERR_AGGR_INT_TYPE_MAIN_UNCERR_VEC_MASK              (0x00000004U)
#define SDL_ERR_AGGR_INT_TYPE_MAIN_UNCERR_VEC_SHIFT             (0x00000002U)

#define SDL_ERR_AGGR_INT_TYPE_MAIN_CERR_VEC_MASK                (0x00000002U)
#define SDL_ERR_AGGR_INT_TYPE_MAIN_CERR_VEC_SHIFT               (0x00000001U)

#define SDL_ERR_AGGR_INT_TYPE_MAIN_ISR_ENTRY_MASK               (0x00000001U)
#define SDL_ERR_AGGR_INT_TYPE_MAIN_ISR_ENTRY_SHIFT              (0x00000000U)

/* SSU_ERROR_TYPE */

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_MMR_ACC_MASK                 (0x00020000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_MMR_ACC_SHIFT                (0x00000011U)              

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLBANKERASE_MASK            (0x0001C000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLBANKERASE_SHIFT           (0x0000000EU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLSIZE_MASK                 (0x00018000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLSIZE_SHIFT                (0x0000000EU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLCMD_MASK                  (0x00014000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLCMD_SHIFT                 (0x0000000EU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLMODECH_MASK               (0x00010000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLMODECH_SHIFT              (0x0000000EU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLRDVER_MASK                (0x0000C000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLRDVER_SHIFT               (0x0000000EU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLERASE_MASK                (0x00008000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLERASE_SHIFT               (0x0000000EU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLPROG_MASK                 (0x00004000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLPROG_SHIFT                (0x0000000EU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLADDR_MASK                 (0x00000000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ILLADDR_SHIFT                (0x0000000EU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ERR_STS_MASK                 (0x00002000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC2_ERR_STS_SHIFT                (0x0000000DU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_MMR_ACC_MASK                 (0x00001000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_MMR_ACC_SHIFT                (0x0000000CU)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLBANKERASE_MASK            (0x00000E00U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLBANKERASE_SHIFT           (0x00000009U)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLSIZE_MASK                 (0x00000C00U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLSIZE_SHIFT                (0x00000009U)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLCMD_MASK                  (0x00000A00U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLCMD_SHIFT                 (0x00000009U)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLMODECH_MASK               (0x00000800U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLMODECH_SHIFT              (0x00000009U)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLRDVER_MASK                (0x00000600U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLRDVER_SHIFT               (0x00000009U)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLERASE_MASK                (0x00000400U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLERASE_SHIFT               (0x00000009U)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLPROG_MASK                 (0x00000200U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLPROG_SHIFT                (0x00000009U)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLADDR_MASK                 (0x00000000U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ILLADDR_SHIFT                (0x00000009U)

#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ERR_STS_MASK                 (0x00000100U)
#define SDL_ERR_AGGR_SSU_TYPE_FLC1_ERR_STS_SHIFT                (0x00000008U)

#define SDL_ERR_AGGR_SSU_TYPE_MODE_INVALID_MASK                 (0x00000080U)
#define SDL_ERR_AGGR_SSU_TYPE_MODE_INVALID_SHIFT                (0x00000007U)

#define SDL_ERR_AGGR_SSU_TYPE_CPU3_MMR_ACC_MASK                 (0x00000008U)
#define SDL_ERR_AGGR_SSU_TYPE_CPU3_MMR_ACC_SHIFT                (0x00000003U)

#define SDL_ERR_AGGR_SSU_TYPE_CPU2_MMR_ACC_MASK                 (0x00000004U)
#define SDL_ERR_AGGR_SSU_TYPE_CPU2_MMR_ACC_SHIFT                (0x00000002U)

#define SDL_ERR_AGGR_SSU_TYPE_CPU1_MMR_ACC_MASK                 (0x00000002U)
#define SDL_ERR_AGGR_SSU_TYPE_CPU1_MMR_ACC_SHIFT                (0x00000001U)

#ifdef __cplusplus
}
#endif
#endif /* SDLR_ERR_AGGR_H_ */