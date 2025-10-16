/********************************************************************
*
* ESM INTERRUPT MAP. header file
*
* Copyright (C) 2025 Texas Instruments Incorporated.
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
#ifndef SDLR_ESM_INTERRUPT_H_
#define SDLR_ESM_INTERRUPT_H_

#ifdef __cplusplus
extern "C"
{
#endif

/** Number of EVENTS in a GROUP */
#define SDL_ESM_EVENTS_PER_GROUP                                      ((uint32_t)32U)

/** Maximum number of EVENT GROUPS */
#define SDL_ESM_NUM_EVENT_GROUPS                                      ((uint32_t)8U)

/** Maximum number of EVENTS */
#define SDL_ESM_MAX_NUM_EVENTS                                        (SDL_ESM_EVENTS_PER_GROUP* \
                                                                       SDL_ESM_NUM_EVENT_GROUPS)

/* Group Number for the ESM Interrupt */
#define groupNumber(intrNum)                                          (intrNum / SDL_ESM_EVENTS_PER_GROUP)

/* Bit Number to be enabled for the ESM Interrupt */
#define bitNumber(intrNum)                                            (intrNum % SDL_ESM_EVENTS_PER_GROUP)

/*
* List of intr sources for receiver: ESM
*/

#define SDL_ESM_EVENT_ErrorAggregator_CPU1_HPERR                      0U
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_HPERR                      1U
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_HPERR                      2U
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_HPERR                  3U
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_HPERR                  4U
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_HPERR                  5U
#define SDL_ESM_EVENT_CLOCKFAIL                                       32U
#define SDL_ESM_EVENT_DCC1_ERR                                        33U
#define SDL_ESM_EVENT_DCC2_ERR                                        34U
#define SDL_ESM_EVENT_DCC3_ERR                                        35U
#define SDL_ESM_EVENT_SYS_PLL_SLIP                                    36U
#define SDL_ESM_EVENT_CPU1RSn                                         37U
#define SDL_ESM_EVENT_CPU1WD                                          38U
#define SDL_ESM_EVENT_CPU1_ERAD_INT                                   39U
#define SDL_ESM_EVENT_CPU1_ERAD_NMI                                   40U
#define SDL_ESM_EVENT_ESM_CPU1_LOW_PRIORITY_INT                       41U
#define SDL_ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT                      42U
#define SDL_ESM_EVENT_LCM_CPU1SS_LCMPERR                              43U
#define SDL_ESM_EVENT_CPU2RSn                                         44U
#define SDL_ESM_EVENT_CPU2WD                                          45U
#define SDL_ESM_EVENT_CPU2_ERAD_INT                                   46U
#define SDL_ESM_EVENT_CPU2_ERAD_NMI                                   47U
#define SDL_ESM_EVENT_ESM_CPU2_LOW_PRIORITY_INT                       48U
#define SDL_ESM_EVENT_ESM_CPU2_HIGH_PRIORITY_INT                      49U
#define SDL_ESM_EVENT_CPU3RSn                                         50U
#define SDL_ESM_EVENT_CPU3WD                                          51U
#define SDL_ESM_EVENT_CPU3_ERAD_INT                                   52U
#define SDL_ESM_EVENT_CPU3_ERAD_NMI                                   53U
#define SDL_ESM_EVENT_ESM_CPU3_LOW_PRIORITY_INT                       54U
#define SDL_ESM_EVENT_ESM_CPU3_HIGH_PRIORITY_INT                      55U
#define SDL_ESM_EVENT_RTDMA_LCM_CMP_ERR                               56U
#define SDL_ESM_EVENT_ESM_ERRPIN_MON_EVT                              58U
#define SDL_ESM_EVENT_ESM_PARITY_ERROR                                59U
#define SDL_ESM_EVENT_HSM_HEA_INT_LO                                  63U
#define SDL_ESM_EVENT_HSM_HEA_INT_HI                                  64U
#define SDL_ESM_EVENT_INPUTXBAR63                                     65U
#define SDL_ESM_EVENT_INPUTXBAR64                                     66U
#define SDL_ESM_EVENT_EPWMXBAR1                                       67U
#define SDL_ESM_EVENT_EPWMXBAR2                                       68U
#define SDL_ESM_EVENT_EPWMXBAR3                                       69U
#define SDL_ESM_EVENT_EPWMXBAR4                                       70U
#define SDL_ESM_EVENT_EPWMXBAR5                                       71U
#define SDL_ESM_EVENT_EPWMXBAR6                                       72U
#define SDL_ESM_EVENT_EPWMXBAR7                                       73U
#define SDL_ESM_EVENT_EPWMXBAR8                                       74U
#define SDL_ESM_EVENT_EPWMXBAR9                                       75U
#define SDL_ESM_EVENT_EPWMXBAR10                                      76U
#define SDL_ESM_EVENT_EPWMXBAR11                                      77U
#define SDL_ESM_EVENT_EPWMXBAR12                                      78U
#define SDL_ESM_EVENT_EPWMXBAR13                                      79U
#define SDL_ESM_EVENT_EPWMXBAR14                                      80U
#define SDL_ESM_EVENT_EPWMXBAR15                                      81U
#define SDL_ESM_EVENT_EPWMXBAR16                                      82U
#define SDL_ESM_EVENT_OUTPUTXBAR1                                     83U
#define SDL_ESM_EVENT_OUTPUTXBAR2                                     84U
#define SDL_ESM_EVENT_OUTPUTXBAR3                                     85U
#define SDL_ESM_EVENT_OUTPUTXBAR4                                     86U
#define SDL_ESM_EVENT_OUTPUTXBAR5                                     87U
#define SDL_ESM_EVENT_OUTPUTXBAR6                                     88U
#define SDL_ESM_EVENT_OUTPUTXBAR7                                     89U
#define SDL_ESM_EVENT_OUTPUTXBAR8                                     90U
#define SDL_ESM_EVENT_OUTPUTXBAR9                                     91U
#define SDL_ESM_EVENT_OUTPUTXBAR10                                    92U
#define SDL_ESM_EVENT_OUTPUTXBAR11                                    93U
#define SDL_ESM_EVENT_OUTPUTXBAR12                                    94U
#define SDL_ESM_EVENT_OUTPUTXBAR13                                    95U
#define SDL_ESM_EVENT_OUTPUTXBAR14                                    96U
#define SDL_ESM_EVENT_OUTPUTXBAR15                                    97U
#define SDL_ESM_EVENT_OUTPUTXBAR16                                    98U
#define SDL_ESM_EVENT_WADI1_INTN_O                                    99U
#define SDL_ESM_EVENT_WADI2_INTN_O                                    100U
#define SDL_ESM_EVENT_CLB1_NMI                                        102U
#define SDL_ESM_EVENT_CLB2_NMI                                        103U
#define SDL_ESM_EVENT_CLB3_NMI                                        104U
#define SDL_ESM_EVENT_CLB4_NMI                                        105U
#define SDL_ESM_EVENT_CLB5_NMI                                        106U
#define SDL_ESM_EVENT_CLB6_NMI                                        107U
#define SDL_ESM_EVENT_EPG_INT                                         108U
#define SDL_ESM_EVENT_ECAT_NMIn                                       109U
#define SDL_ESM_EVENT_MCANA_ECC_CORR_PLS                              110U
#define SDL_ESM_EVENT_MCANA_ECC_UNCORR_TS_PLS                         111U
#define SDL_ESM_EVENT_MCANB_ECC_CORR_PLS                              112U
#define SDL_ESM_EVENT_MCANB_ECC_UNCORR_TS_PLS                         113U
#define SDL_ESM_EVENT_MCANC_ECC_CORR_PLS                              114U
#define SDL_ESM_EVENT_MCANC_ECC_UNCORR_TS_PLS                         115U
#define SDL_ESM_EVENT_MCAND_ECC_CORR_PLS                              116U
#define SDL_ESM_EVENT_MCAND_ECC_UNCORR_TS_PLS                         117U
#define SDL_ESM_EVENT_MCANE_ECC_CORR_PLS                              118U
#define SDL_ESM_EVENT_MCANE_ECC_UNCORR_TS_PLS                         119U
#define SDL_ESM_EVENT_MCANF_ECC_CORR_PLS                              120U
#define SDL_ESM_EVENT_MCANF_ECC_UNCORR_TS_PLS                         121U
#define SDL_ESM_EVENT_EMIF1_ERR                                       122U
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU1                       123U
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU2                       124U
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU3                       125U
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_LPERR                      128U
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_LPERR                      130U
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_LPERR                      132U
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_LPERR                  134U
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_LPERR                  136U
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_LPERR                  138U
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA1_HPERR                    139U
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA1_LPERR                    140U
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA2_HPERR                    141U
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA2_LPERR                    142U
#define SDL_ESM_EVENT_ErrorAggregator_SSU_HPERR                       143U
#define SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_HPERR                  146U
#define SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_LPERR                  147U
#define SDL_ESM_EVENT_MCANA_FEVT0                                     162U
#define SDL_ESM_EVENT_MCANA_FEVT1                                     163U
#define SDL_ESM_EVENT_MCANA_FEVT2                                     164U
#define SDL_ESM_EVENT_MCANB_FEVT0                                     165U
#define SDL_ESM_EVENT_MCANB_FEVT1                                     166U
#define SDL_ESM_EVENT_MCANB_FEVT2                                     167U
#define SDL_ESM_EVENT_MCANC_FEVT0                                     168U
#define SDL_ESM_EVENT_MCANC_FEVT1                                     169U
#define SDL_ESM_EVENT_MCANC_FEVT2                                     170U
#define SDL_ESM_EVENT_MCAND_FEVT0                                     171U
#define SDL_ESM_EVENT_MCAND_FEVT1                                     172U
#define SDL_ESM_EVENT_MCAND_FEVT2                                     173U
#define SDL_ESM_EVENT_MCANE_FEVT0                                     174U
#define SDL_ESM_EVENT_MCANE_FEVT1                                     175U
#define SDL_ESM_EVENT_MCANE_FEVT2                                     176U
#define SDL_ESM_EVENT_MCANF_FEVT0                                     177U
#define SDL_ESM_EVENT_MCANF_FEVT1                                     178U
#define SDL_ESM_EVENT_MCANF_FEVT2                                     179U
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG1ERROR_BUS_O_0                  180U
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG2ERROR_BUS_O_1                  181U
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG_TO_SIGERROR_BUS_O_2            182U
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG1ERROR_BUS_O_0                  183U
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG2ERROR_BUS_O_1                  184U
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG_TO_SIGERROR_BUS_O_2            185U
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG1ERROR_BUS_O_0                  186U
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG2ERROR_BUS_O_1                  187U
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG_TO_SIGERROR_BUS_O_2            188U
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG1ERROR_BUS_O_0                  189U
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG2ERROR_BUS_O_1                  190U
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG_TO_SIGERROR_BUS_O_2            191U
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG1ERROR_BUS_O_0                  192U
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG2ERROR_BUS_O_1                  193U
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG_TO_SIGERROR_BUS_O_2            194U
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG1ERROR_BUS_O_0                  195U
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG2ERROR_BUS_O_1                  196U
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG_TO_SIGERROR_BUS_O_2            197U
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG1ERROR_BUS_O_0                  198U
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG2ERROR_BUS_O_1                  199U
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG_TO_SIGERROR_BUS_O_2            200U
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG1ERROR_BUS_O_0                  201U
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG2ERROR_BUS_O_1                  202U
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG_TO_SIGERROR_BUS_O_2            203U
#define SDL_ESM_EVENT_EQEPERR                                         233U
#define SDL_ESM_EVENT_CPU1_OVFINT                                     235U
#define SDL_ESM_EVENT_CPU1_UVFINT                                     236U
#define SDL_ESM_EVENT_CPU1_DOVINT                                     237U
#define SDL_ESM_EVENT_CPU2_OVFINT                                     238U
#define SDL_ESM_EVENT_CPU2_UVFINT                                     239U
#define SDL_ESM_EVENT_CPU2_DOVINT                                     240U
#define SDL_ESM_EVENT_CPU3_OVFINT                                     241U
#define SDL_ESM_EVENT_CPU3_UVFINT                                     242U
#define SDL_ESM_EVENT_CPU3_DOVINT                                     243U
#define SDL_ESM_EVENT_MEMSS_REG_PAR_ERR                               244U
#define SDL_ESM_EVENT_FRI_REG_PAR_ERR                                 245U
#define SDL_ESM_EVENT_SYSCTL_REG_PAR_ERR                              246U
#define SDL_ESM_EVENT_LCM_CPU1SS_REG_PAR_ERR                          247U
#define SDL_ESM_EVENT_LCM_RTDMA_REG_PAR_ERR                           248U
#define SDL_ESM_EVENT_WADI_REG_PAR_ERR                                249U
#define SDL_ESM_EVENT_CPU1_TMUROM_PAR_ERR                             250U
#define SDL_ESM_EVENT_CPU2_TMUROM_PAR_ERR                             251U
#define SDL_ESM_EVENT_CPU3_TMUROM_PAR_ERR                             252U


/* SDL_ESM_EVENT_ErrorAggregator_CPU1_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_HPERR_GROUP                groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU1_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_HPERR_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU1_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU2_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_HPERR_GROUP                groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU2_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_HPERR_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU2_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU3_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_HPERR_GROUP                groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU3_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_HPERR_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU3_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_HPERR_GROUP            groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_HPERR_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_HPERR_GROUP            groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_HPERR_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_HPERR_GROUP            groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_HPERR_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_HPERR))

/* SDL_ESM_EVENT_CLOCKFAIL */
#define SDL_ESM_EVENT_CLOCKFAIL_GROUP                                 groupNumber(SDL_ESM_EVENT_CLOCKFAIL)
#define SDL_ESM_EVENT_CLOCKFAIL_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CLOCKFAIL))

/* SDL_ESM_EVENT_DCC1_ERR */
#define SDL_ESM_EVENT_DCC1_ERR_GROUP                                  groupNumber(SDL_ESM_EVENT_DCC1_ERR)
#define SDL_ESM_EVENT_DCC1_ERR_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_DCC1_ERR))

/* SDL_ESM_EVENT_DCC2_ERR */
#define SDL_ESM_EVENT_DCC2_ERR_GROUP                                  groupNumber(SDL_ESM_EVENT_DCC2_ERR)
#define SDL_ESM_EVENT_DCC2_ERR_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_DCC2_ERR))

/* SDL_ESM_EVENT_DCC3_ERR */
#define SDL_ESM_EVENT_DCC3_ERR_GROUP                                  groupNumber(SDL_ESM_EVENT_DCC3_ERR)
#define SDL_ESM_EVENT_DCC3_ERR_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_DCC3_ERR))

/* SDL_ESM_EVENT_SYS_PLL_SLIP */
#define SDL_ESM_EVENT_SYS_PLL_SLIP_GROUP                              groupNumber(SDL_ESM_EVENT_DCC3_ERR)
#define SDL_ESM_EVENT_SYS_PLL_SLIP_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_DCC3_ERR))

/* SDL_ESM_EVENT_CPU1RSn */
#define SDL_ESM_EVENT_CPU1RSn_GROUP                                   groupNumber(SDL_ESM_EVENT_CPU1RSn)
#define SDL_ESM_EVENT_CPU1RSn_MASK                                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU1RSn))

/* SDL_ESM_EVENT_CPU1WD */
#define SDL_ESM_EVENT_CPU1WD_GROUP                                    groupNumber(SDL_ESM_EVENT_CPU1WD)
#define SDL_ESM_EVENT_CPU1WD_MASK                                     ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU1WD))

/* SDL_ESM_EVENT_CPU1_ERAD_INT */
#define SDL_ESM_EVENT_CPU1_ERAD_INT_GROUP                             groupNumber(SDL_ESM_EVENT_CPU1_ERAD_INT)
#define SDL_ESM_EVENT_CPU1_ERAD_INT_MASK                              ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU1_ERAD_INT))

/* SDL_ESM_EVENT_CPU1_ERAD_NMI */
#define SDL_ESM_EVENT_CPU1_ERAD_NMI_GROUP                             groupNumber(SDL_ESM_EVENT_CPU1_ERAD_NMI)
#define SDL_ESM_EVENT_CPU1_ERAD_NMI_MASK                              ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU1_ERAD_NMI))

/* SDL_ESM_EVENT_ESM_CPU1_LOW_PRIORITY_INT */
#define SDL_ESM_EVENT_ESM_CPU1_LOW_PRIORITY_INT_GROUP                 groupNumber(SDL_ESM_EVENT_ESM_CPU1_LOW_PRIORITY_INT)
#define SDL_ESM_EVENT_ESM_CPU1_LOW_PRIORITY_INT_MASK                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ESM_CPU1_LOW_PRIORITY_INT))

/* SDL_ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT */
#define SDL_ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT_GROUP                groupNumber(SDL_ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT)
#define SDL_ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ESM_CPU1_HIGH_PRIORITY_INT))

/* SDL_ESM_EVENT_LCM_CPU1SS_LCMPERR */
#define SDL_ESM_EVENT_LCM_CPU1SS_LCMPERR_GROUP                        groupNumber(SDL_ESM_EVENT_LCM_CPU1SS_LCMPERR)
#define SDL_ESM_EVENT_LCM_CPU1SS_LCMPERR_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_LCM_CPU1SS_LCMPERR))

/* SDL_ESM_EVENT_CPU2RSn */
#define SDL_ESM_EVENT_CPU2RSn_GROUP                                   groupNumber(SDL_ESM_EVENT_CPU2RSn)
#define SDL_ESM_EVENT_CPU2RSn_MASK                                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU2RSn))

/* SDL_ESM_EVENT_CPU2WD */
#define SDL_ESM_EVENT_CPU2WD_GROUP                                    groupNumber(SDL_ESM_EVENT_CPU2WD)
#define SDL_ESM_EVENT_CPU2WD_MASK                                     ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU2WD))

/* SDL_ESM_EVENT_CPU2_ERAD_INT */
#define SDL_ESM_EVENT_CPU2_ERAD_INT_GROUP                             groupNumber(SDL_ESM_EVENT_CPU2_ERAD_INT)
#define SDL_ESM_EVENT_CPU2_ERAD_INT_MASK                              ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU2_ERAD_INT))

/* SDL_ESM_EVENT_CPU2_ERAD_NMI */
#define SDL_ESM_EVENT_CPU2_ERAD_NMI_GROUP                             groupNumber(SDL_ESM_EVENT_CPU2_ERAD_NMI)
#define SDL_ESM_EVENT_CPU2_ERAD_NMI_MASK                              ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU2_ERAD_NMI))

/* SDL_ESM_EVENT_ESM_CPU2_LOW_PRIORITY_INT*/
#define SDL_ESM_EVENT_ESM_CPU2_LOW_PRIORITY_INT_GROUP                 groupNumber(SDL_ESM_EVENT_ESM_CPU2_LOW_PRIORITY_INT)
#define SDL_ESM_EVENT_ESM_CPU2_LOW_PRIORITY_INT_MASK                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ESM_CPU2_LOW_PRIORITY_INT))

/* SDL_ESM_EVENT_ESM_CPU2_HIGH_PRIORITY_INT */
#define SDL_ESM_EVENT_ESM_CPU2_HIGH_PRIORITY_INT_GROUP                groupNumber(SDL_ESM_EVENT_ESM_CPU2_HIGH_PRIORITY_INT)
#define SDL_ESM_EVENT_ESM_CPU2_HIGH_PRIORITY_INT_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ESM_CPU2_HIGH_PRIORITY_INT))

/* SDL_ESM_EVENT_CPU3RSn */
#define SDL_ESM_EVENT_CPU3RSn_GROUP                                   groupNumber(SDL_ESM_EVENT_CPU3RSn)
#define SDL_ESM_EVENT_CPU3RSn_MASK                                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU3RSn))

/* SDL_ESM_EVENT_CPU3WD */
#define SDL_ESM_EVENT_CPU3WD_GROUP                                    groupNumber(SDL_ESM_EVENT_CPU3WD)
#define SDL_ESM_EVENT_CPU3WD_MASK                                     ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU3WD))

/* SDL_ESM_EVENT_CPU3_ERAD_INT */
#define SDL_ESM_EVENT_CPU3_ERAD_INT_GROUP                             groupNumber(SDL_ESM_EVENT_CPU3_ERAD_INT)
#define SDL_ESM_EVENT_CPU3_ERAD_INT_MASK                              ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU3_ERAD_INT))

/* SDL_ESM_EVENT_CPU3_ERAD_NMI */
#define SDL_ESM_EVENT_CPU3_ERAD_NMI_GROUP                             groupNumber(SDL_ESM_EVENT_CPU3_ERAD_NMI)
#define SDL_ESM_EVENT_CPU3_ERAD_NMI_MASK                              ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU3_ERAD_NMI))

/* SDL_ESM_EVENT_ESM_CPU3_LOW_PRIORITY_INT */
#define SDL_ESM_EVENT_ESM_CPU3_LOW_PRIORITY_INT_GROUP                 groupNumber(SDL_ESM_EVENT_ESM_CPU3_LOW_PRIORITY_INT)
#define SDL_ESM_EVENT_ESM_CPU3_LOW_PRIORITY_INT_MASK                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ESM_CPU3_LOW_PRIORITY_INT))

/* SDL_ESM_EVENT_ESM_CPU3_HIGH_PRIORITY_INT */
#define SDL_ESM_EVENT_ESM_CPU3_HIGH_PRIORITY_INT_GROUP                groupNumber(SDL_ESM_EVENT_ESM_CPU3_HIGH_PRIORITY_INT)
#define SDL_ESM_EVENT_ESM_CPU3_HIGH_PRIORITY_INT_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ESM_CPU3_HIGH_PRIORITY_INT))

/* SDL_ESM_EVENT_RTDMA_LCM_CMP_ERR */
#define SDL_ESM_EVENT_RTDMA_LCM_CMP_ERR_GROUP                         groupNumber(SDL_ESM_EVENT_RTDMA_LCM_CMP_ERR)
#define SDL_ESM_EVENT_RTDMA_LCM_CMP_ERR_MASK                          ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_RTDMA_LCM_CMP_ERR))

/* SDL_ESM_EVENT_ESM_ERRPIN_MON_EVT */
#define SDL_ESM_EVENT_ESM_ERRPIN_MON_EVT_GROUP                        groupNumber(SDL_ESM_EVENT_ESM_ERRPIN_MON_EVT)
#define SDL_ESM_EVENT_ESM_ERRPIN_MON_EVT_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ESM_ERRPIN_MON_EVT))

/* SDL_ESM_EVENT_ESM_PARITY_ERROR */
#define SDL_ESM_EVENT_ESM_PARITY_ERROR_GROUP                          groupNumber(SDL_ESM_EVENT_ESM_PARITY_ERROR)
#define SDL_ESM_EVENT_ESM_PARITY_ERROR_MASK                           ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ESM_PARITY_ERROR))

/* SDL_ESM_EVENT_HSM_HEA_INT_LO */
#define SDL_ESM_EVENT_HSM_HEA_INT_LO_GROUP                            groupNumber(SDL_ESM_EVENT_HSM_HEA_INT_LO)
#define SDL_ESM_EVENT_HSM_HEA_INT_LO_MASK                             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_HSM_HEA_INT_LO))

/* SDL_ESM_EVENT_HSM_HEA_INT_HI */
#define SDL_ESM_EVENT_HSM_HEA_INT_HI_GROUP                            groupNumber(SDL_ESM_EVENT_HSM_HEA_INT_HI)
#define SDL_ESM_EVENT_HSM_HEA_INT_HI_MASK                             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_HSM_HEA_INT_HI))

/* SDL_ESM_EVENT_INPUTXBAR63 */
#define SDL_ESM_EVENT_INPUTXBAR63_GROUP                               groupNumber(SDL_ESM_EVENT_INPUTXBAR63)
#define SDL_ESM_EVENT_INPUTXBAR63_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_INPUTXBAR63))

/* SDL_ESM_EVENT_INPUTXBAR64 */
#define SDL_ESM_EVENT_INPUTXBAR64_GROUP                               groupNumber(SDL_ESM_EVENT_INPUTXBAR64)
#define SDL_ESM_EVENT_INPUTXBAR64_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_INPUTXBAR64))

/* SDL_ESM_EVENT_EPWMXBAR1 */
#define SDL_ESM_EVENT_EPWMXBAR1_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR1)
#define SDL_ESM_EVENT_EPWMXBAR1_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR1))

/* SDL_ESM_EVENT_EPWMXBAR2 */
#define SDL_ESM_EVENT_EPWMXBAR2_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR2)
#define SDL_ESM_EVENT_EPWMXBAR2_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR2))

/* SDL_ESM_EVENT_EPWMXBAR3 */
#define SDL_ESM_EVENT_EPWMXBAR3_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR3)
#define SDL_ESM_EVENT_EPWMXBAR3_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR3))

/* SDL_ESM_EVENT_EPWMXBAR4 */
#define SDL_ESM_EVENT_EPWMXBAR4_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR4)
#define SDL_ESM_EVENT_EPWMXBAR4_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR4))

/* SDL_ESM_EVENT_EPWMXBAR5 */
#define SDL_ESM_EVENT_EPWMXBAR5_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR5)
#define SDL_ESM_EVENT_EPWMXBAR5_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR5))

/* SDL_ESM_EVENT_EPWMXBAR6 */
#define SDL_ESM_EVENT_EPWMXBAR6_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR6)
#define SDL_ESM_EVENT_EPWMXBAR6_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR6))

/* SDL_ESM_EVENT_EPWMXBAR7 */
#define SDL_ESM_EVENT_EPWMXBAR7_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR7)
#define SDL_ESM_EVENT_EPWMXBAR7_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR7))

/* SDL_ESM_EVENT_EPWMXBAR8 */
#define SDL_ESM_EVENT_EPWMXBAR8_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR8)
#define SDL_ESM_EVENT_EPWMXBAR8_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR8))

/* SDL_ESM_EVENT_EPWMXBAR9 */
#define SDL_ESM_EVENT_EPWMXBAR9_GROUP                                 groupNumber(SDL_ESM_EVENT_EPWMXBAR9)
#define SDL_ESM_EVENT_EPWMXBAR9_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR9))

/* SDL_ESM_EVENT_EPWMXBAR10 */
#define SDL_ESM_EVENT_EPWMXBAR10_GROUP                                groupNumber(SDL_ESM_EVENT_EPWMXBAR10)
#define SDL_ESM_EVENT_EPWMXBAR10_MASK                                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR10))

/* SDL_ESM_EVENT_EPWMXBAR11 */
#define SDL_ESM_EVENT_EPWMXBAR11_GROUP                                groupNumber(SDL_ESM_EVENT_EPWMXBAR11)
#define SDL_ESM_EVENT_EPWMXBAR11_MASK                                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR11))

/* SDL_ESM_EVENT_EPWMXBAR12 */
#define SDL_ESM_EVENT_EPWMXBAR12_GROUP                                groupNumber(SDL_ESM_EVENT_EPWMXBAR12)
#define SDL_ESM_EVENT_EPWMXBAR12_MASK                                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR12))

/* SDL_ESM_EVENT_EPWMXBAR13 */
#define SDL_ESM_EVENT_EPWMXBAR13_GROUP                                groupNumber(SDL_ESM_EVENT_EPWMXBAR13)
#define SDL_ESM_EVENT_EPWMXBAR13_MASK                                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR13))

/* SDL_ESM_EVENT_EPWMXBAR14 */
#define SDL_ESM_EVENT_EPWMXBAR14_GROUP                                groupNumber(SDL_ESM_EVENT_EPWMXBAR14)
#define SDL_ESM_EVENT_EPWMXBAR14_MASK                                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR14))

/* SDL_ESM_EVENT_EPWMXBAR15 */
#define SDL_ESM_EVENT_EPWMXBAR15_GROUP                                groupNumber(SDL_ESM_EVENT_EPWMXBAR15)
#define SDL_ESM_EVENT_EPWMXBAR15_MASK                                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR15))

/* SDL_ESM_EVENT_EPWMXBAR16 */
#define SDL_ESM_EVENT_EPWMXBAR16_GROUP                                groupNumber(SDL_ESM_EVENT_EPWMXBAR16)
#define SDL_ESM_EVENT_EPWMXBAR16_MASK                                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPWMXBAR16))

/* SDL_ESM_EVENT_OUTPUTXBAR1 */
#define SDL_ESM_EVENT_OUTPUTXBAR1_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR1)
#define SDL_ESM_EVENT_OUTPUTXBAR1_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR1))

/* SDL_ESM_EVENT_OUTPUTXBAR2 */
#define SDL_ESM_EVENT_OUTPUTXBAR2_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR2)
#define SDL_ESM_EVENT_OUTPUTXBAR2_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR2))

/* SDL_ESM_EVENT_OUTPUTXBAR3 */
#define SDL_ESM_EVENT_OUTPUTXBAR3_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR3)
#define SDL_ESM_EVENT_OUTPUTXBAR3_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR3))

/* SDL_ESM_EVENT_OUTPUTXBAR4 */
#define SDL_ESM_EVENT_OUTPUTXBAR4_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR4)
#define SDL_ESM_EVENT_OUTPUTXBAR4_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR4))

/* SDL_ESM_EVENT_OUTPUTXBAR5 */
#define SDL_ESM_EVENT_OUTPUTXBAR5_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR5)
#define SDL_ESM_EVENT_OUTPUTXBAR5_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR5))

/* SDL_ESM_EVENT_OUTPUTXBAR6 */
#define SDL_ESM_EVENT_OUTPUTXBAR6_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR6)
#define SDL_ESM_EVENT_OUTPUTXBAR6_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR6))

/* SDL_ESM_EVENT_OUTPUTXBAR7 */
#define SDL_ESM_EVENT_OUTPUTXBAR7_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR7)
#define SDL_ESM_EVENT_OUTPUTXBAR7_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR7))

/* SDL_ESM_EVENT_OUTPUTXBAR8 */
#define SDL_ESM_EVENT_OUTPUTXBAR8_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR8)
#define SDL_ESM_EVENT_OUTPUTXBAR8_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR8))

/* SDL_ESM_EVENT_OUTPUTXBAR9 */
#define SDL_ESM_EVENT_OUTPUTXBAR9_GROUP                               groupNumber(SDL_ESM_EVENT_OUTPUTXBAR9)
#define SDL_ESM_EVENT_OUTPUTXBAR9_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR9))

/* SDL_ESM_EVENT_OUTPUTXBAR10 */
#define SDL_ESM_EVENT_OUTPUTXBAR10_GROUP                              groupNumber(SDL_ESM_EVENT_OUTPUTXBAR10)
#define SDL_ESM_EVENT_OUTPUTXBAR10_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR10))

/* SDL_ESM_EVENT_OUTPUTXBAR11 */
#define SDL_ESM_EVENT_OUTPUTXBAR11_GROUP                              groupNumber(SDL_ESM_EVENT_OUTPUTXBAR11)
#define SDL_ESM_EVENT_OUTPUTXBAR11_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR11))

/* SDL_ESM_EVENT_OUTPUTXBAR12 */
#define SDL_ESM_EVENT_OUTPUTXBAR12_GROUP                              groupNumber(SDL_ESM_EVENT_OUTPUTXBAR12)
#define SDL_ESM_EVENT_OUTPUTXBAR12_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR12))

/* SDL_ESM_EVENT_OUTPUTXBAR13 */
#define SDL_ESM_EVENT_OUTPUTXBAR13_GROUP                              groupNumber(SDL_ESM_EVENT_OUTPUTXBAR13)
#define SDL_ESM_EVENT_OUTPUTXBAR13_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR13))

/* SDL_ESM_EVENT_OUTPUTXBAR14 */
#define SDL_ESM_EVENT_OUTPUTXBAR14_GROUP                              groupNumber(SDL_ESM_EVENT_OUTPUTXBAR14)
#define SDL_ESM_EVENT_OUTPUTXBAR14_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR14))

/* SDL_ESM_EVENT_OUTPUTXBAR15 */
#define SDL_ESM_EVENT_OUTPUTXBAR15_GROUP                              groupNumber(SDL_ESM_EVENT_OUTPUTXBAR15)
#define SDL_ESM_EVENT_OUTPUTXBAR15_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR15))

/* SDL_ESM_EVENT_OUTPUTXBAR16 */
#define SDL_ESM_EVENT_OUTPUTXBAR16_GROUP                              groupNumber(SDL_ESM_EVENT_OUTPUTXBAR16)
#define SDL_ESM_EVENT_OUTPUTXBAR16_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_OUTPUTXBAR16))

/* SDL_ESM_EVENT_WADI1_INTN_O */
#define SDL_ESM_EVENT_WADI1_INTN_O_GROUP                              groupNumber(SDL_ESM_EVENT_WADI1_INTN_O)
#define SDL_ESM_EVENT_WADI1_INTN_O_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_INTN_O))

/* SDL_ESM_EVENT_WADI2_INTN_O */
#define SDL_ESM_EVENT_WADI2_INTN_O_GROUP                              groupNumber(SDL_ESM_EVENT_WADI2_INTN_O)
#define SDL_ESM_EVENT_WADI2_INTN_O_MASK                               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_INTN_O))

/* SDL_ESM_EVENT_CLB1_NMI */
#define SDL_ESM_EVENT_CLB1_NMI_GROUP                                  groupNumber(SDL_ESM_EVENT_CLB1_NMI)
#define SDL_ESM_EVENT_CLB1_NMI_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CLB1_NMI))

/* SDL_ESM_EVENT_CLB2_NMI */
#define SDL_ESM_EVENT_CLB2_NMI_GROUP                                  groupNumber(SDL_ESM_EVENT_CLB2_NMI)
#define SDL_ESM_EVENT_CLB2_NMI_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CLB2_NMI))

/* SDL_ESM_EVENT_CLB3_NMI */
#define SDL_ESM_EVENT_CLB3_NMI_GROUP                                  groupNumber(SDL_ESM_EVENT_CLB3_NMI)
#define SDL_ESM_EVENT_CLB3_NMI_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CLB3_NMI))

/* SDL_ESM_EVENT_CLB4_NMI */
#define SDL_ESM_EVENT_CLB4_NMI_GROUP                                  groupNumber(SDL_ESM_EVENT_CLB4_NMI)
#define SDL_ESM_EVENT_CLB4_NMI_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CLB4_NMI))

/* SDL_ESM_EVENT_CLB5_NMI */
#define SDL_ESM_EVENT_CLB5_NMI_GROUP                                  groupNumber(SDL_ESM_EVENT_CLB5_NMI)
#define SDL_ESM_EVENT_CLB5_NMI_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CLB5_NMI))

/* SDL_ESM_EVENT_CLB6_NMI */
#define SDL_ESM_EVENT_CLB6_NMI_GROUP                                  groupNumber(SDL_ESM_EVENT_CLB6_NMI)
#define SDL_ESM_EVENT_CLB6_NMI_MASK                                   ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CLB6_NMI))

/* SDL_ESM_EVENT_EPG_INT */
#define SDL_ESM_EVENT_EPG_INT_GROUP                                   groupNumber(SDL_ESM_EVENT_EPG_INT)
#define SDL_ESM_EVENT_EPG_INT_MASK                                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EPG_INT))

/* SDL_ESM_EVENT_ECAT_NMIn */
#define SDL_ESM_EVENT_ECAT_NMIn_GROUP                                 groupNumber(SDL_ESM_EVENT_ECAT_NMIn)
#define SDL_ESM_EVENT_ECAT_NMIn_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ECAT_NMIn))

/* SDL_ESM_EVENT_MCANA_ECC_CORR_PLS */
#define SDL_ESM_EVENT_MCANA_ECC_CORR_PLS_GROUP                        groupNumber(SDL_ESM_EVENT_MCANA_ECC_CORR_PLS)
#define SDL_ESM_EVENT_MCANA_ECC_CORR_PLS_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANA_ECC_CORR_PLS))

/* SDL_ESM_EVENT_MCANA_ECC_UNCORR_TS_PLS */
#define SDL_ESM_EVENT_MCANA_ECC_UNCORR_TS_PLS_GROUP                   groupNumber(SDL_ESM_EVENT_MCANA_ECC_UNCORR_TS_PLS)
#define SDL_ESM_EVENT_MCANA_ECC_UNCORR_TS_PLS_MASK                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANA_ECC_UNCORR_TS_PLS))

/* SDL_ESM_EVENT_MCANB_ECC_CORR_PLS */
#define SDL_ESM_EVENT_MCANB_ECC_CORR_PLS_GROUP                        groupNumber(SDL_ESM_EVENT_MCANB_ECC_CORR_PLS)
#define SDL_ESM_EVENT_MCANB_ECC_CORR_PLS_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANB_ECC_CORR_PLS))

/* SDL_ESM_EVENT_MCANB_ECC_UNCORR_TS_PLS */
#define SDL_ESM_EVENT_MCANB_ECC_UNCORR_TS_PLS_GROUP                   groupNumber(SDL_ESM_EVENT_MCANB_ECC_UNCORR_TS_PLS)
#define SDL_ESM_EVENT_MCANB_ECC_UNCORR_TS_PLS_MASK                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANB_ECC_UNCORR_TS_PLS))

/* SDL_ESM_EVENT_MCANC_ECC_CORR_PLS */
#define SDL_ESM_EVENT_MCANC_ECC_CORR_PLS_GROUP                        groupNumber(SDL_ESM_EVENT_MCANC_ECC_CORR_PLS)
#define SDL_ESM_EVENT_MCANC_ECC_CORR_PLS_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANC_ECC_CORR_PLS))

/* SDL_ESM_EVENT_MCANC_ECC_UNCORR_TS_PLS */
#define SDL_ESM_EVENT_MCANC_ECC_UNCORR_TS_PLS_GROUP                   groupNumber(SDL_ESM_EVENT_MCANC_ECC_UNCORR_TS_PLS)
#define SDL_ESM_EVENT_MCANC_ECC_UNCORR_TS_PLS_MASK                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANC_ECC_UNCORR_TS_PLS))

/* SDL_ESM_EVENT_MCAND_ECC_CORR_PLS */
#define SDL_ESM_EVENT_MCAND_ECC_CORR_PLS_GROUP                        groupNumber(SDL_ESM_EVENT_MCAND_ECC_CORR_PLS)
#define SDL_ESM_EVENT_MCAND_ECC_CORR_PLS_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCAND_ECC_CORR_PLS))

/* SDL_ESM_EVENT_MCAND_ECC_UNCORR_TS_PLS */
#define SDL_ESM_EVENT_MCAND_ECC_UNCORR_TS_PLS_GROUP                   groupNumber(SDL_ESM_EVENT_MCAND_ECC_UNCORR_TS_PLS)
#define SDL_ESM_EVENT_MCAND_ECC_UNCORR_TS_PLS_MASK                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCAND_ECC_UNCORR_TS_PLS))

/* SDL_ESM_EVENT_MCANE_ECC_CORR_PLS */
#define SDL_ESM_EVENT_MCANE_ECC_CORR_PLS_GROUP                        groupNumber(SDL_ESM_EVENT_MCANE_ECC_CORR_PLS)
#define SDL_ESM_EVENT_MCANE_ECC_CORR_PLS_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANE_ECC_CORR_PLS))

/* SDL_ESM_EVENT_MCANE_ECC_UNCORR_TS_PLS */
#define SDL_ESM_EVENT_MCANE_ECC_UNCORR_TS_PLS_GROUP                   groupNumber(SDL_ESM_EVENT_MCANE_ECC_UNCORR_TS_PLS)
#define SDL_ESM_EVENT_MCANE_ECC_UNCORR_TS_PLS_MASK                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANE_ECC_UNCORR_TS_PLS))

/* SDL_ESM_EVENT_MCANF_ECC_CORR_PLS */
#define SDL_ESM_EVENT_MCANF_ECC_CORR_PLS_GROUP                        groupNumber(SDL_ESM_EVENT_MCANF_ECC_CORR_PLS)
#define SDL_ESM_EVENT_MCANF_ECC_CORR_PLS_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANF_ECC_CORR_PLS))

/* SDL_ESM_EVENT_MCANF_ECC_UNCORR_TS_PLS */
#define SDL_ESM_EVENT_MCANF_ECC_UNCORR_TS_PLS_GROUP                   groupNumber(SDL_ESM_EVENT_MCANF_ECC_UNCORR_TS_PLS)
#define SDL_ESM_EVENT_MCANF_ECC_UNCORR_TS_PLS_MASK                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANF_ECC_UNCORR_TS_PLS))

/* SDL_ESM_EVENT_EMIF1_ERR */
#define SDL_ESM_EVENT_EMIF1_ERR_GROUP                                 groupNumber(SDL_ESM_EVENT_EMIF1_ERR)
#define SDL_ESM_EVENT_EMIF1_ERR_MASK                                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EMIF1_ERR))

/* SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU1 */
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU1_GROUP                 groupNumber(SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU1)
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU1_MASK                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU1))

/* SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU2 */
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU2_GROUP                 groupNumber(SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU2)
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU2_MASK                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU2))

/* SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU3 */
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU3_GROUP                 groupNumber(SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU3)
#define SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU3_MASK                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU3))

/* SDL_ESM_EVENT_ErrorAggregator_CPU1_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_LPERR_GROUP                groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU1_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_LPERR_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU1_LPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU2_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_LPERR_GROUP                groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU2_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_LPERR_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU2_LPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU3_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_LPERR_GROUP                groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU3_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_LPERR_MASK                 ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU3_LPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_LPERR_GROUP            groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_LPERR_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU1_INT_LPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_LPERR_GROUP            groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_LPERR_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU2_INT_LPERR))

/* SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_LPERR_GROUP            groupNumber(SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_LPERR_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_CPU3_INT_LPERR))

/* SDL_ESM_EVENT_ErrorAggregator_RTDMA1_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA1_HPERR_GROUP              groupNumber(SDL_ESM_EVENT_ErrorAggregator_RTDMA1_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA1_HPERR_MASK               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_RTDMA1_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_RTDMA1_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA1_LPERR_GROUP              groupNumber(SDL_ESM_EVENT_ErrorAggregator_RTDMA1_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA1_LPERR_MASK               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_RTDMA1_LPERR))

/* SDL_ESM_EVENT_ErrorAggregator_RTDMA2_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA2_HPERR_GROUP              groupNumber(SDL_ESM_EVENT_ErrorAggregator_RTDMA2_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA2_HPERR_MASK               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_RTDMA2_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_RTDMA2_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA2_LPERR_GROUP              groupNumber(SDL_ESM_EVENT_ErrorAggregator_RTDMA2_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_RTDMA2_LPERR_MASK               ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_RTDMA2_LPERR))

/* SDL_ESM_EVENT_ErrorAggregator_SSU_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_SSU_HPERR_GROUP                 groupNumber(SDL_ESM_EVENT_ErrorAggregator_SSU_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_SSU_HPERR_MASK                  ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_SSU_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_HPERR */
#define SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_HPERR_GROUP            groupNumber(SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_HPERR)
#define SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_HPERR_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_HPERR))

/* SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_LPERR */
#define SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_LPERR_GROUP            groupNumber(SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_LPERR)
#define SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_LPERR_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_ErrorAggregator_ECAT_MEM_LPERR))

/* SDL_ESM_EVENT_MCANA_FEVT0 */
#define SDL_ESM_EVENT_MCANA_FEVT0_GROUP                               groupNumber(SDL_ESM_EVENT_MCANA_FEVT0)
#define SDL_ESM_EVENT_MCANA_FEVT0_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANA_FEVT0))

/* SDL_ESM_EVENT_MCANA_FEVT1 */
#define SDL_ESM_EVENT_MCANA_FEVT1_GROUP                               groupNumber(SDL_ESM_EVENT_MCANA_FEVT1)
#define SDL_ESM_EVENT_MCANA_FEVT1_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANA_FEVT1))

/* SDL_ESM_EVENT_MCANA_FEVT2 */
#define SDL_ESM_EVENT_MCANA_FEVT2_GROUP                               groupNumber(SDL_ESM_EVENT_MCANA_FEVT2)
#define SDL_ESM_EVENT_MCANA_FEVT2_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANA_FEVT2))

/* SDL_ESM_EVENT_MCANB_FEVT0 */
#define SDL_ESM_EVENT_MCANB_FEVT0_GROUP                               groupNumber(SDL_ESM_EVENT_MCANB_FEVT0)
#define SDL_ESM_EVENT_MCANB_FEVT0_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANB_FEVT0))

/* SDL_ESM_EVENT_MCANB_FEVT1 */
#define SDL_ESM_EVENT_MCANB_FEVT1_GROUP                               groupNumber(SDL_ESM_EVENT_MCANB_FEVT1)
#define SDL_ESM_EVENT_MCANB_FEVT1_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANB_FEVT1))

/* SDL_ESM_EVENT_MCANB_FEVT2 */
#define SDL_ESM_EVENT_MCANB_FEVT2_GROUP                               groupNumber(SDL_ESM_EVENT_MCANB_FEVT2)
#define SDL_ESM_EVENT_MCANB_FEVT2_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANB_FEVT2))

/* SDL_ESM_EVENT_MCANC_FEVT0 */
#define SDL_ESM_EVENT_MCANC_FEVT0_GROUP                               groupNumber(SDL_ESM_EVENT_MCANC_FEVT0)
#define SDL_ESM_EVENT_MCANC_FEVT0_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANC_FEVT0))

/* SDL_ESM_EVENT_MCANC_FEVT1 */
#define SDL_ESM_EVENT_MCANC_FEVT1_GROUP                               groupNumber(SDL_ESM_EVENT_MCANC_FEVT1)
#define SDL_ESM_EVENT_MCANC_FEVT1_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANC_FEVT1))

/* SDL_ESM_EVENT_MCANC_FEVT2 */
#define SDL_ESM_EVENT_MCANC_FEVT2_GROUP                               groupNumber(SDL_ESM_EVENT_MCANC_FEVT2)
#define SDL_ESM_EVENT_MCANC_FEVT2_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANC_FEVT2))

/* SDL_ESM_EVENT_MCAND_FEVT0 */
#define SDL_ESM_EVENT_MCAND_FEVT0_GROUP                               groupNumber(SDL_ESM_EVENT_MCAND_FEVT0)
#define SDL_ESM_EVENT_MCAND_FEVT0_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCAND_FEVT0))

/* SDL_ESM_EVENT_MCAND_FEVT1 */
#define SDL_ESM_EVENT_MCAND_FEVT1_GROUP                               groupNumber(SDL_ESM_EVENT_MCAND_FEVT1)
#define SDL_ESM_EVENT_MCAND_FEVT1_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCAND_FEVT1))

/* SDL_ESM_EVENT_MCAND_FEVT2 */
#define SDL_ESM_EVENT_MCAND_FEVT2_GROUP                               groupNumber(SDL_ESM_EVENT_MCAND_FEVT2)
#define SDL_ESM_EVENT_MCAND_FEVT2_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCAND_FEVT2))

/* SDL_ESM_EVENT_MCANE_FEVT0 */
#define SDL_ESM_EVENT_MCANE_FEVT0_GROUP                               groupNumber(SDL_ESM_EVENT_MCANE_FEVT0)
#define SDL_ESM_EVENT_MCANE_FEVT0_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANE_FEVT0))

/* SDL_ESM_EVENT_MCANE_FEVT1 */
#define SDL_ESM_EVENT_MCANE_FEVT1_GROUP                               groupNumber(SDL_ESM_EVENT_MCANE_FEVT1)
#define SDL_ESM_EVENT_MCANE_FEVT1_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANE_FEVT1))

/* SDL_ESM_EVENT_MCANE_FEVT2 */
#define SDL_ESM_EVENT_MCANE_FEVT2_GROUP                               groupNumber(SDL_ESM_EVENT_MCANE_FEVT2)
#define SDL_ESM_EVENT_MCANE_FEVT2_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANE_FEVT2))

/* SDL_ESM_EVENT_MCANF_FEVT0 */
#define SDL_ESM_EVENT_MCANF_FEVT0_GROUP                               groupNumber(SDL_ESM_EVENT_MCANF_FEVT0)
#define SDL_ESM_EVENT_MCANF_FEVT0_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANF_FEVT0))

/* SDL_ESM_EVENT_MCANF_FEVT1 */
#define SDL_ESM_EVENT_MCANF_FEVT1_GROUP                               groupNumber(SDL_ESM_EVENT_MCANF_FEVT1)
#define SDL_ESM_EVENT_MCANF_FEVT1_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANF_FEVT1))

/* SDL_ESM_EVENT_MCANF_FEVT2 */
#define SDL_ESM_EVENT_MCANF_FEVT2_GROUP                               groupNumber(SDL_ESM_EVENT_MCANF_FEVT2)
#define SDL_ESM_EVENT_MCANF_FEVT2_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MCANF_FEVT2))

/* SDL_ESM_EVENT_WADI1_BLOCK1_SIG1ERROR_BUS_O_0 */
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG1ERROR_BUS_O_0_GROUP            groupNumber(SDL_ESM_EVENT_WADI1_BLOCK1_SIG1ERROR_BUS_O_0)
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG1ERROR_BUS_O_0_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK1_SIG1ERROR_BUS_O_0))

/* SDL_ESM_EVENT_WADI1_BLOCK1_SIG2ERROR_BUS_O_1 */
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG2ERROR_BUS_O_1_GROUP            groupNumber(SDL_ESM_EVENT_WADI1_BLOCK1_SIG2ERROR_BUS_O_1)
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG2ERROR_BUS_O_1_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK1_SIG2ERROR_BUS_O_1))

/* SDL_ESM_EVENT_WADI1_BLOCK1_SIG_TO_SIGERROR_BUS_O_2 */
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG_TO_SIGERROR_BUS_O_2_GROUP      groupNumber(SDL_ESM_EVENT_WADI1_BLOCK1_SIG_TO_SIGERROR_BUS_O_2)
#define SDL_ESM_EVENT_WADI1_BLOCK1_SIG_TO_SIGERROR_BUS_O_2_MASK       ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK1_SIG_TO_SIGERROR_BUS_O_2))

/* SDL_ESM_EVENT_WADI1_BLOCK2_SIG1ERROR_BUS_O_0 */
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG1ERROR_BUS_O_0_GROUP            groupNumber(SDL_ESM_EVENT_WADI1_BLOCK2_SIG1ERROR_BUS_O_0)
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG1ERROR_BUS_O_0_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK2_SIG1ERROR_BUS_O_0))

/* SDL_ESM_EVENT_WADI1_BLOCK2_SIG2ERROR_BUS_O_1 */
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG2ERROR_BUS_O_1_GROUP            groupNumber(SDL_ESM_EVENT_WADI1_BLOCK2_SIG2ERROR_BUS_O_1)
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG2ERROR_BUS_O_1_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK2_SIG2ERROR_BUS_O_1))

/* SDL_ESM_EVENT_WADI1_BLOCK2_SIG_TO_SIGERROR_BUS_O_2 */
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG_TO_SIGERROR_BUS_O_2_GROUP      groupNumber(SDL_ESM_EVENT_WADI1_BLOCK2_SIG_TO_SIGERROR_BUS_O_2)
#define SDL_ESM_EVENT_WADI1_BLOCK2_SIG_TO_SIGERROR_BUS_O_2_MASK       ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK2_SIG_TO_SIGERROR_BUS_O_2))

/* SDL_ESM_EVENT_WADI1_BLOCK3_SIG1ERROR_BUS_O_0 */
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG1ERROR_BUS_O_0_GROUP            groupNumber(SDL_ESM_EVENT_WADI1_BLOCK3_SIG1ERROR_BUS_O_0)
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG1ERROR_BUS_O_0_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK3_SIG1ERROR_BUS_O_0))

/* SDL_ESM_EVENT_WADI1_BLOCK3_SIG2ERROR_BUS_O_1 */
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG2ERROR_BUS_O_1_GROUP            groupNumber(SDL_ESM_EVENT_WADI1_BLOCK3_SIG2ERROR_BUS_O_1)
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG2ERROR_BUS_O_1_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK3_SIG2ERROR_BUS_O_1))

/* SDL_ESM_EVENT_WADI1_BLOCK3_SIG_TO_SIGERROR_BUS_O_2 */
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG_TO_SIGERROR_BUS_O_2_GROUP      groupNumber(SDL_ESM_EVENT_WADI1_BLOCK3_SIG_TO_SIGERROR_BUS_O_2)
#define SDL_ESM_EVENT_WADI1_BLOCK3_SIG_TO_SIGERROR_BUS_O_2_MASK       ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK3_SIG_TO_SIGERROR_BUS_O_2))

/* SDL_ESM_EVENT_WADI1_BLOCK4_SIG1ERROR_BUS_O_0 */
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG1ERROR_BUS_O_0_GROUP            groupNumber(SDL_ESM_EVENT_WADI1_BLOCK4_SIG1ERROR_BUS_O_0)
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG1ERROR_BUS_O_0_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK4_SIG1ERROR_BUS_O_0))

/* SDL_ESM_EVENT_WADI1_BLOCK4_SIG2ERROR_BUS_O_1 */
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG2ERROR_BUS_O_1_GROUP            groupNumber(SDL_ESM_EVENT_WADI1_BLOCK4_SIG2ERROR_BUS_O_1)
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG2ERROR_BUS_O_1_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK4_SIG2ERROR_BUS_O_1))

/* SDL_ESM_EVENT_WADI1_BLOCK4_SIG_TO_SIGERROR_BUS_O_2 */
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG_TO_SIGERROR_BUS_O_2_GROUP      groupNumber(SDL_ESM_EVENT_WADI1_BLOCK4_SIG_TO_SIGERROR_BUS_O_2)
#define SDL_ESM_EVENT_WADI1_BLOCK4_SIG_TO_SIGERROR_BUS_O_2_MASK       ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI1_BLOCK4_SIG_TO_SIGERROR_BUS_O_2))

/* SDL_ESM_EVENT_WADI2_BLOCK1_SIG1ERROR_BUS_O_0 */
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG1ERROR_BUS_O_0_GROUP            groupNumber(SDL_ESM_EVENT_WADI2_BLOCK1_SIG1ERROR_BUS_O_0)
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG1ERROR_BUS_O_0_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK1_SIG1ERROR_BUS_O_0))

/* SDL_ESM_EVENT_WADI2_BLOCK1_SIG2ERROR_BUS_O_1 */
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG2ERROR_BUS_O_1_GROUP            groupNumber(SDL_ESM_EVENT_WADI2_BLOCK1_SIG2ERROR_BUS_O_1)
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG2ERROR_BUS_O_1_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK1_SIG2ERROR_BUS_O_1))

/* SDL_ESM_EVENT_WADI2_BLOCK1_SIG_TO_SIGERROR_BUS_O_2 */
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG_TO_SIGERROR_BUS_O_2_GROUP      groupNumber(SDL_ESM_EVENT_WADI2_BLOCK1_SIG_TO_SIGERROR_BUS_O_2)
#define SDL_ESM_EVENT_WADI2_BLOCK1_SIG_TO_SIGERROR_BUS_O_2_MASK       ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK1_SIG_TO_SIGERROR_BUS_O_2))

/* SDL_ESM_EVENT_WADI2_BLOCK2_SIG1ERROR_BUS_O_0 */
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG1ERROR_BUS_O_0_GROUP            groupNumber(SDL_ESM_EVENT_WADI2_BLOCK2_SIG1ERROR_BUS_O_0)
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG1ERROR_BUS_O_0_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK2_SIG1ERROR_BUS_O_0))

/* SDL_ESM_EVENT_WADI2_BLOCK2_SIG2ERROR_BUS_O_1 */
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG2ERROR_BUS_O_1_GROUP            groupNumber(SDL_ESM_EVENT_WADI2_BLOCK2_SIG2ERROR_BUS_O_1)
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG2ERROR_BUS_O_1_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK2_SIG2ERROR_BUS_O_1))

/* SDL_ESM_EVENT_WADI2_BLOCK2_SIG_TO_SIGERROR_BUS_O_2 */
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG_TO_SIGERROR_BUS_O_2_GROUP      groupNumber(SDL_ESM_EVENT_WADI2_BLOCK2_SIG_TO_SIGERROR_BUS_O_2)
#define SDL_ESM_EVENT_WADI2_BLOCK2_SIG_TO_SIGERROR_BUS_O_2_MASK       ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK2_SIG_TO_SIGERROR_BUS_O_2))

/* SDL_ESM_EVENT_WADI2_BLOCK3_SIG1ERROR_BUS_O_0 */
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG1ERROR_BUS_O_0_GROUP            groupNumber(SDL_ESM_EVENT_WADI2_BLOCK3_SIG1ERROR_BUS_O_0)
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG1ERROR_BUS_O_0_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK3_SIG1ERROR_BUS_O_0))

/* SDL_ESM_EVENT_WADI2_BLOCK3_SIG2ERROR_BUS_O_1 */
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG2ERROR_BUS_O_1_GROUP            groupNumber(SDL_ESM_EVENT_WADI2_BLOCK3_SIG2ERROR_BUS_O_1)
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG2ERROR_BUS_O_1_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK3_SIG2ERROR_BUS_O_1))

/* SDL_ESM_EVENT_WADI2_BLOCK3_SIG_TO_SIGERROR_BUS_O_2 */
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG_TO_SIGERROR_BUS_O_2_GROUP      groupNumber(SDL_ESM_EVENT_WADI2_BLOCK3_SIG_TO_SIGERROR_BUS_O_2)
#define SDL_ESM_EVENT_WADI2_BLOCK3_SIG_TO_SIGERROR_BUS_O_2_MASK       ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK3_SIG_TO_SIGERROR_BUS_O_2))

/* SDL_ESM_EVENT_WADI2_BLOCK4_SIG1ERROR_BUS_O_0 */
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG1ERROR_BUS_O_0_GROUP            groupNumber(SDL_ESM_EVENT_WADI2_BLOCK4_SIG1ERROR_BUS_O_0)
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG1ERROR_BUS_O_0_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK4_SIG1ERROR_BUS_O_0))

/* SDL_ESM_EVENT_WADI2_BLOCK4_SIG2ERROR_BUS_O_1 */
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG2ERROR_BUS_O_1_GROUP            groupNumber(SDL_ESM_EVENT_WADI2_BLOCK4_SIG2ERROR_BUS_O_1)
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG2ERROR_BUS_O_1_MASK             ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK4_SIG2ERROR_BUS_O_1))

/* SDL_ESM_EVENT_WADI2_BLOCK4_SIG_TO_SIGERROR_BUS_O_2 */
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG_TO_SIGERROR_BUS_O_2_GROUP      groupNumber(SDL_ESM_EVENT_WADI2_BLOCK4_SIG_TO_SIGERROR_BUS_O_2)
#define SDL_ESM_EVENT_WADI2_BLOCK4_SIG_TO_SIGERROR_BUS_O_2_MASK       ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI2_BLOCK4_SIG_TO_SIGERROR_BUS_O_2))

/* SDL_ESM_EVENT_EQEPERR */
#define SDL_ESM_EVENT_EQEPERR_GROUP                                   groupNumber(SDL_ESM_EVENT_EQEPERR)
#define SDL_ESM_EVENT_EQEPERR_MASK                                    ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_EQEPERR))

/* SDL_ESM_EVENT_CPU1_OVFINT */
#define SDL_ESM_EVENT_CPU1_OVFINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU1_OVFINT)
#define SDL_ESM_EVENT_CPU1_OVFINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU1_OVFINT))

/* SDL_ESM_EVENT_CPU1_UVFINT */
#define SDL_ESM_EVENT_CPU1_UVFINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU1_UVFINT)
#define SDL_ESM_EVENT_CPU1_UVFINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU1_UVFINT))

/* SDL_ESM_EVENT_CPU1_DOVINT */
#define SDL_ESM_EVENT_CPU1_DOVINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU1_DOVINT)
#define SDL_ESM_EVENT_CPU1_DOVINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU1_DOVINT))

/* SDL_ESM_EVENT_CPU2_OVFINT */
#define SDL_ESM_EVENT_CPU2_OVFINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU2_OVFINT)
#define SDL_ESM_EVENT_CPU2_OVFINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU2_OVFINT))

/* SDL_ESM_EVENT_CPU2_UVFINT */
#define SDL_ESM_EVENT_CPU2_UVFINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU2_UVFINT)
#define SDL_ESM_EVENT_CPU2_UVFINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU2_UVFINT))

/* SDL_ESM_EVENT_CPU2_DOVINT */
#define SDL_ESM_EVENT_CPU2_DOVINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU2_DOVINT)
#define SDL_ESM_EVENT_CPU2_DOVINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU2_DOVINT))

/* SDL_ESM_EVENT_CPU3_OVFINT */
#define SDL_ESM_EVENT_CPU3_OVFINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU3_OVFINT)
#define SDL_ESM_EVENT_CPU3_OVFINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU3_OVFINT))

/* SDL_ESM_EVENT_CPU3_UVFINT */
#define SDL_ESM_EVENT_CPU3_UVFINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU3_UVFINT)
#define SDL_ESM_EVENT_CPU3_UVFINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU3_UVFINT))

/* SDL_ESM_EVENT_CPU3_DOVINT */
#define SDL_ESM_EVENT_CPU3_DOVINT_GROUP                               groupNumber(SDL_ESM_EVENT_CPU3_DOVINT)
#define SDL_ESM_EVENT_CPU3_DOVINT_MASK                                ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU3_DOVINT))

/* SDL_ESM_EVENT_MEMSS_REG_PAR_ERR */
#define SDL_ESM_EVENT_MEMSS_REG_PAR_ERR_GROUP                         groupNumber(SDL_ESM_EVENT_MEMSS_REG_PAR_ERR)
#define SDL_ESM_EVENT_MEMSS_REG_PAR_ERR_MASK                          ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_MEMSS_REG_PAR_ERR))

/* SDL_ESM_EVENT_FRI_REG_PAR_ERR */
#define SDL_ESM_EVENT_FRI_REG_PAR_ERR_GROUP                           groupNumber(SDL_ESM_EVENT_FRI_REG_PAR_ERR)
#define SDL_ESM_EVENT_FRI_REG_PAR_ERR_MASK                            ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_FRI_REG_PAR_ERR))

/* SDL_ESM_EVENT_SYSCTL_REG_PAR_ERR */
#define SDL_ESM_EVENT_SYSCTL_REG_PAR_ERR_GROUP                        groupNumber(SDL_ESM_EVENT_SYSCTL_REG_PAR_ERR)
#define SDL_ESM_EVENT_SYSCTL_REG_PAR_ERR_MASK                         ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_SYSCTL_REG_PAR_ERR))

/* SDL_ESM_EVENT_LCM_CPU1SS_REG_PAR_ERR */
#define SDL_ESM_EVENT_LCM_CPU1SS_REG_PAR_ERR_GROUP                    groupNumber(SDL_ESM_EVENT_LCM_CPU1SS_REG_PAR_ERR)
#define SDL_ESM_EVENT_LCM_CPU1SS_REG_PAR_ERR_MASK                     ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_LCM_CPU1SS_REG_PAR_ERR))

/* SDL_ESM_EVENT_LCM_RTDMA_REG_PAR_ERR */
#define SDL_ESM_EVENT_LCM_RTDMA_REG_PAR_ERR_GROUP                     groupNumber(SDL_ESM_EVENT_LCM_RTDMA_REG_PAR_ERR)
#define SDL_ESM_EVENT_LCM_RTDMA_REG_PAR_ERR_MASK                      ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_LCM_RTDMA_REG_PAR_ERR))

/* SDL_ESM_EVENT_WADI_REG_PAR_ERR */
#define SDL_ESM_EVENT_WADI_REG_PAR_ERR_GROUP                          groupNumber(SDL_ESM_EVENT_WADI_REG_PAR_ERR)
#define SDL_ESM_EVENT_WADI_REG_PAR_ERR_MASK                           ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_WADI_REG_PAR_ERR))

/* SDL_ESM_EVENT_CPU1_TMUROM_PAR_ERR */
#define SDL_ESM_EVENT_CPU1_TMUROM_PAR_ERR_GROUP                       groupNumber(SDL_ESM_EVENT_CPU1_TMUROM_PAR_ERR)
#define SDL_ESM_EVENT_CPU1_TMUROM_PAR_ERR_MASK                        ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU1_TMUROM_PAR_ERR))

/* SDL_ESM_EVENT_CPU2_TMUROM_PAR_ERR */
#define SDL_ESM_EVENT_CPU2_TMUROM_PAR_ERR_GROUP                       groupNumber(SDL_ESM_EVENT_CPU2_TMUROM_PAR_ERR)
#define SDL_ESM_EVENT_CPU2_TMUROM_PAR_ERR_MASK                        ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU2_TMUROM_PAR_ERR))

/* SDL_ESM_EVENT_CPU3_TMUROM_PAR_ERR */
#define SDL_ESM_EVENT_CPU3_TMUROM_PAR_ERR_GROUP                       groupNumber(SDL_ESM_EVENT_CPU3_TMUROM_PAR_ERR)
#define SDL_ESM_EVENT_CPU3_TMUROM_PAR_ERR_MASK                        ((uint32_t) 0x1U << bitNumber(SDL_ESM_EVENT_CPU3_TMUROM_PAR_ERR))

#ifdef __cplusplus
}
#endif
#endif /* SDLR_ESM_INTERRUPT_H_ */
