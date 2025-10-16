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
#ifndef SDLR_ESM_H_
#define SDLR_ESM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************
* Hardware Region  : ESM Registers
**************************************************************************/
/* None */

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CRIT_EN_SET;               /* Error Group Critical Priority Interrupt Influence Set Register */
    volatile uint32_t CRIT_EN_CLR;               /* Error Group Critical Priority Interrupt Influence Clear Register */
    volatile uint32_t Resv_9[6];
}SDL_esmRegs_ERR_EXT_GRP;

typedef struct {
    volatile uint32_t RAW;                       /* Error Group Event Raw Status/Set Register */
    volatile uint32_t STS;                       /* Error Group Interrupt Enable Status/Clear Register */
    volatile uint32_t INTR_EN_SET;               /* Error Group Interrupt Enable Set Register */
    volatile uint32_t INTR_EN_CLR;               /* Error Group Interrupt Enabled Clear Register */
    volatile uint32_t INT_PRIO;                  /* Error Group Interrupt Priority Register */
    volatile uint32_t PIN_EN_SET;                /* Error Group Error Pin Influence Set Register */
    volatile uint32_t PIN_EN_CLR;                /* Error Group Error Pin Influence Clear Register */
    volatile uint32_t Resv_8[1];
} SDL_esmRegs_ERR_GRP;


typedef struct {
    volatile uint32_t PID;                       /* Revision Register */
    volatile uint32_t INFO;                      /* Info Register */
    volatile uint32_t EN;                        /* Global Enable Register */
    volatile uint32_t SFT_RST;                   /* Global Soft Reset Register */
    volatile uint32_t Resv_0[4];
    volatile uint32_t LOW_PRI;                   /* Low Priority Prioritized Register */
    volatile uint32_t HI_PRI;                    /* High Priority Prioritized Register */
    volatile uint32_t LOW;                       /* Low Priority Interrupt Status Register */
    volatile uint32_t HI;                        /* High Priority Interrupt Status Register */
    volatile uint32_t EOI;                       /* EOI Interrupt Register */
    volatile uint32_t Resv_1[3];
    volatile uint32_t PIN_CTRL;                  /* Error Pin Control Register */
    volatile uint32_t PIN_STS;                   /* Error Pin Status Register */
    volatile uint32_t PIN_CNTR;                  /* Error Counter Value Register */
    volatile uint32_t PIN_CNTR_PRE;              /* Error Counter Value Pre-Load Register */
    volatile uint32_t PWMH_PIN_CNTR;             /* Error PWM High Counter Value Register */
    volatile uint32_t PWMH_PIN_CNTR_PRE;         /* Error PWM High Counter Value Pre-Load Register */
    volatile uint32_t PWML_PIN_CNTR;             /* Error PWM Low Counter Value Register */
    volatile uint32_t PWML_PIN_CNTR_PRE;         /* Error PWM Low Counter Value Pre-Load Register */
    volatile uint32_t Resv_2[8];
    volatile uint32_t HI_PRI_WD_CFG;             /* High Priority Watchdog Config Register */
    volatile uint32_t HI_PRI_WD_CNTR;            /* High Priority Watchdog Counter Value Register */
    volatile uint32_t HI_PRI_WD_CNTR_PRE;        /* High Priority Watchdog Pre-Load Register */
    volatile uint32_t HI_PRI_WD_INTR_SET;        /* High Priority Watchdog Interrupt Status/Set Register */
    volatile uint32_t HI_PRI_WD_INTR_CLR;        /* High Priority Watchdog Interrupt Status/Clear Register */
    volatile uint32_t  Resv_3[3];
    volatile uint32_t ERRPIN_MON_CFG;            /* Error Pin Monitor Config Register */
    volatile uint32_t ERRPIN_MON_INTR_SET;       /* Error Pin Monitor Interrupt Status/Set Register */
    volatile uint32_t ERRPIN_MON_INTR_CLR;       /* Error Pin Monitor Interrupt Status/Clear Register */
    volatile uint32_t Resv_4[21];
    volatile uint32_t GROUP_N_LOCK;              /* Group N Interrupt Lock Register */
    volatile uint32_t GROUP_N_COMMIT;            /* Group N Interrupt Commit Register */
    volatile uint32_t Resv_5[2];
    volatile uint32_t ERR_PIN_INFLUENCE_LOCK;    /* Error Pin Influence Lock Register */
    volatile uint32_t ERR_PIN_INFLUENCE_COMMIT;  /* Error Pin Influence Commit Register */
    volatile uint32_t CRI_PRI_INFLUENCE_LOCK;    /* Critical Prioirty Interrupt Influence Lock Register */
    volatile uint32_t CRI_PRI_INFLUENCE_COMMIT;  /* Critical Priority Interrupt Influence Lock Register */
    volatile uint32_t MMR_CONFIG_LOCK;           /* MMR Config Lock Register */
    volatile uint32_t MMR_CONFIG_COMMIT;         /* MMR Config Commit Register */
    volatile uint32_t Resv_6[182];
    SDL_esmRegs_ERR_GRP ERR_GRP[8];
    volatile uint32_t Resv_7[192];
    SDL_esmRegs_ERR_EXT_GRP ERR_EXT_GRP[8];
} SDL_esmRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_ESM_PID                                                            (0x00000000U)
#define SDL_ESM_INFO                                                           (0x00000004U)
#define SDL_ESM_EN                                                             (0x00000008U)
#define SDL_ESM_SFT_RST                                                        (0x0000000CU)
#define SDL_ESM_LOW_PRI                                                        (0x00000020U)
#define SDL_ESM_HI_PRI                                                         (0x00000024U)
#define SDL_ESM_LOW                                                            (0x00000028U)
#define SDL_ESM_HI                                                             (0x0000002CU)
#define SDL_ESM_EOI                                                            (0x00000030U)

#define SDL_ESM_GROUP_N_LOCK                                                   (0x00000100U)
#define SDL_ESM_GROUP_N_COMMIT                                                 (0x00000104U)

#define SDL_ESM_CRI_PRI_INFLUENCE_LOCK                                         (0x00000118U)
#define SDL_ESM_CRI_PRI_INFLUENCE_COMMIT                                       (0x0000011CU)
#define SDL_ESM_MMR_CONFIG_LOCK                                                (0x00000120U)
#define SDL_ESM_MMR_CONFIG_COMMIT                                              (0x00000124U)

#define SDL_ESM_ERR_GRP_RAW(ERR_GRP)                                           (0x00000400U + ((ERR_GRP) * 0x20U))
#define SDL_ESM_ERR_GRP_STS(ERR_GRP)                                           (0x00000404U + ((ERR_GRP) * 0x20U))
#define SDL_ESM_ERR_GRP_INTR_EN_SET(ERR_GRP)                                   (0x00000408U + ((ERR_GRP) * 0x20U))
#define SDL_ESM_ERR_GRP_INTR_EN_CLR(ERR_GRP)                                   (0x0000040CU + ((ERR_GRP) * 0x20U))
#define SDL_ESM_ERR_GRP_INT_PRIO(ERR_GRP)                                      (0x00000410U + ((ERR_GRP) * 0x20U))

#define SDL_ESM_ERR_GRP_CRIT_EN_SET(ERR_GRP)                                   (0x00000800U + ((ERR_GRP) * 0x20U))
#define SDL_ESM_ERR_GRP_CRIT_EN_CLR(ERR_GRP)                                   (0x00000804U + ((ERR_GRP) * 0x20U))

/* Applied only when ESM System instance is enabled */
#define SDL_ESM_SYS_PIN_CTRL                                                   (0x00000040U)
#define SDL_ESM_SYS_PIN_STS                                                    (0x00000044U)
#define SDL_ESM_SYS_PIN_CNTR                                                   (0x00000048U)
#define SDL_ESM_SYS_PIN_CNTR_PRE                                               (0x0000004CU)
#define SDL_ESM_SYS_PWMH_PIN_CNTR                                              (0x00000050U)
#define SDL_ESM_SYS_PWMH_PIN_CNTR_PRE                                          (0x00000054U)
#define SDL_ESM_SYS_PWML_PIN_CNTR                                              (0x00000058U)
#define SDL_ESM_SYS_PWML_PIN_CNTR_PRE                                          (0x0000005CU)
#define SDL_ESM_SYS_ERRPIN_MON_CFG                                             (0x000000A0U)
#define SDL_ESM_SYS_ERRPIN_MON_INTR_SET                                        (0x000000A4U)
#define SDL_ESM_SYS_ERRPIN_MON_INTR_CLR                                        (0x000000A8U)
#define SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK                                     (0x00000110U)
#define SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT                                   (0x00000114U)

#define SDL_ESM_SYS_ERR_GRP_PIN_EN_SET(ERR_GRP)                                (0x00000414U + ((ERR_GRP) * 0x20U))
#define SDL_ESM_SYS_ERR_GRP_PIN_EN_CLR(ERR_GRP)                                (0x00000418U + ((ERR_GRP) * 0x20U))

/* Applied only when ESM CPU instance is enabled */
#define SDL_ESM_CPU_HI_PRI_WD_CFG                                              (0x00000080U)
#define SDL_ESM_CPU_HI_PRI_WD_CNTR                                             (0x00000084U)
#define SDL_ESM_CPU_HI_PRI_WD_CNTR_PRE                                         (0x00000088U)
#define SDL_ESM_CPU_HI_PRI_WD_INTR_SET                                         (0x0000008CU)
#define SDL_ESM_CPU_HI_PRI_WD_INTR_CLR                                         (0x00000090U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* RAW */

#define SDL_ESM_ERR_GRP_RAW_STS_MASK                                           (0xFFFFFFFFU)
#define SDL_ESM_ERR_GRP_RAW_STS_SHIFT                                          (0x00000000U)
#define SDL_ESM_ERR_GRP_RAW_STS_MAX                                            (0xFFFFFFFFU)

/* STS */

#define SDL_ESM_ERR_GRP_STS_MSK_MASK                                           (0xFFFFFFFFU)
#define SDL_ESM_ERR_GRP_STS_MSK_SHIFT                                          (0x00000000U)
#define SDL_ESM_ERR_GRP_STS_MSK_MAX                                            (0xFFFFFFFFU)

/* INTR_EN_SET */

#define SDL_ESM_ERR_GRP_INTR_EN_SET_MSK_MASK                                   (0xFFFFFFFFU)
#define SDL_ESM_ERR_GRP_INTR_EN_SET_MSK_SHIFT                                  (0x00000000U)
#define SDL_ESM_ERR_GRP_INTR_EN_SET_MSK_MAX                                    (0xFFFFFFFFU)

/* INTR_EN_CLR */

#define SDL_ESM_ERR_GRP_INTR_EN_CLR_MSK_MASK                                   (0xFFFFFFFFU)
#define SDL_ESM_ERR_GRP_INTR_EN_CLR_MSK_SHIFT                                  (0x00000000U)
#define SDL_ESM_ERR_GRP_INTR_EN_CLR_MSK_MAX                                    (0xFFFFFFFFU)

/* INT_PRIO */

#define SDL_ESM_ERR_GRP_INT_PRIO_MSK_MASK                                      (0xFFFFFFFFU)
#define SDL_ESM_ERR_GRP_INT_PRIO_MSK_SHIFT                                     (0x00000000U)
#define SDL_ESM_ERR_GRP_INT_PRIO_MSK_MAX                                       (0xFFFFFFFFU)

/* PIN_EN_SET */

#define SDL_ESM_SYS_ERR_GRP_PIN_EN_SET_MSK_MASK                                (0xFFFFFFFFU)
#define SDL_ESM_SYS_ERR_GRP_PIN_EN_SET_MSK_SHIFT                               (0x00000000U)
#define SDL_ESM_SYS_ERR_GRP_PIN_EN_SET_MSK_MAX                                 (0xFFFFFFFFU)

/* PIN_EN_CLR */

#define SDL_ESM_SYS_ERR_GRP_PIN_EN_CLR_MSK_MASK                                (0xFFFFFFFFU)
#define SDL_ESM_SYS_ERR_GRP_PIN_EN_CLR_MSK_SHIFT                               (0x00000000U)
#define SDL_ESM_SYS_ERR_GRP_PIN_EN_CLR_MSK_MAX                                 (0xFFFFFFFFU)

/* PID */

#define SDL_ESM_PID_MINOR_MASK                                                 (0x0000003FU)
#define SDL_ESM_PID_MINOR_SHIFT                                                (0x00000000U)
#define SDL_ESM_PID_MINOR_MAX                                                  (0x0000003FU)

#define SDL_ESM_PID_CUSTOM_MASK                                                (0x000000C0U)
#define SDL_ESM_PID_CUSTOM_SHIFT                                               (0x00000006U)
#define SDL_ESM_PID_CUSTOM_MAX                                                 (0x00000003U)

#define SDL_ESM_PID_MAJOR_MASK                                                 (0x00000700U)
#define SDL_ESM_PID_MAJOR_SHIFT                                                (0x00000008U)
#define SDL_ESM_PID_MAJOR_MAX                                                  (0x00000007U)

#define SDL_ESM_PID_RTL_MASK                                                   (0x0000F800U)
#define SDL_ESM_PID_RTL_SHIFT                                                  (0x0000000BU)
#define SDL_ESM_PID_RTL_MAX                                                    (0x0000001FU)

#define SDL_ESM_PID_FUNC_MASK                                                  (0x0FFF0000U)
#define SDL_ESM_PID_FUNC_SHIFT                                                 (0x00000010U)
#define SDL_ESM_PID_FUNC_MAX                                                   (0x00000FFFU)

#define SDL_ESM_PID_BU_MASK                                                    (0x30000000U)
#define SDL_ESM_PID_BU_SHIFT                                                   (0x0000001CU)
#define SDL_ESM_PID_BU_MAX                                                     (0x00000003U)

#define SDL_ESM_PID_SCHEME_MASK                                                (0xC0000000U)
#define SDL_ESM_PID_SCHEME_SHIFT                                               (0x0000001EU)
#define SDL_ESM_PID_SCHEME_MAX                                                 (0x00000003U)

/* INFO */

#define SDL_ESM_INFO_GROUPS_MASK                                               (0x000000FFU)
#define SDL_ESM_INFO_GROUPS_SHIFT                                              (0x00000000U)
#define SDL_ESM_INFO_GROUPS_MAX                                                (0x000000FFU)

#define SDL_ESM_INFO_PULSE_GROUPS_MASK                                         (0x0000FF00U)
#define SDL_ESM_INFO_PULSE_GROUPS_SHIFT                                        (0x00000008U)
#define SDL_ESM_INFO_PULSE_GROUPS_MAX                                          (0x000000FFU)

#define SDL_ESM_INFO_CRIT_INTR_MASK                                            (0x40000000U)
#define SDL_ESM_INFO_CRIT_INTR_SHIFT                                           (0x0000001EU)
#define SDL_ESM_INFO_CRIT_INTR_MAX                                             (0x00000001U)

#define SDL_ESM_INFO_LAST_RESET_MASK                                           (0x80000000U)
#define SDL_ESM_INFO_LAST_RESET_SHIFT                                          (0x0000001FU)
#define SDL_ESM_INFO_LAST_RESET_MAX                                            (0x00000001U)

/* EN */

#define SDL_ESM_EN_KEY_MASK                                                    (0x0000000FU)
#define SDL_ESM_EN_KEY_SHIFT                                                   (0x00000000U)
#define SDL_ESM_EN_KEY_MAX                                                     (0x0000000FU)

#define SDL_ESM_EN_KEY_ENABLE                                                  (0x0000000FU)
#define SDL_ESM_EN_KEY_DISABLE                                                 (0x00000000U)

/* SFT_RST */

#define SDL_ESM_SFT_RST_KEY_MASK                                               (0x0000000FU)
#define SDL_ESM_SFT_RST_KEY_SHIFT                                              (0x00000000U)
#define SDL_ESM_SFT_RST_KEY_MAX                                                (0x0000000FU)

#define SDL_ESM_GLOBAL_SFT_RST_VAL                                             (0x0000000FU)
/* LOW_PRI */

#define SDL_ESM_LOW_PRI_PLS_MASK                                               (0xFFFF0000U)
#define SDL_ESM_LOW_PRI_PLS_SHIFT                                              (0x00000010U)
#define SDL_ESM_LOW_PRI_PLS_MAX                                                (0x0000FFFFU)

#define SDL_ESM_LOW_PRI_LVL_MASK                                               (0x0000FFFFU)
#define SDL_ESM_LOW_PRI_LVL_SHIFT                                              (0x00000000U)
#define SDL_ESM_LOW_PRI_LVL_MAX                                                (0x0000FFFFU)

/* HI_PRI */

#define SDL_ESM_HI_PRI_PLS_MASK                                                (0xFFFF0000U)
#define SDL_ESM_HI_PRI_PLS_SHIFT                                               (0x00000010U)
#define SDL_ESM_HI_PRI_PLS_MAX                                                 (0x0000FFFFU)

#define SDL_ESM_HI_PRI_LVL_MASK                                                (0x0000FFFFU)
#define SDL_ESM_HI_PRI_LVL_SHIFT                                               (0x00000000U)
#define SDL_ESM_HI_PRI_LVL_MAX                                                 (0x0000FFFFU)

/* LOW */

#define SDL_ESM_LOW_STS_MASK                                                   (0xFFFFFFFFU)
#define SDL_ESM_LOW_STS_SHIFT                                                  (0x00000000U)
#define SDL_ESM_LOW_STS_MAX                                                    (0xFFFFFFFFU)

/* HI */

#define SDL_ESM_HI_STS_MASK                                                    (0xFFFFFFFFU)
#define SDL_ESM_HI_STS_SHIFT                                                   (0x00000000U)
#define SDL_ESM_HI_STS_MAX                                                     (0xFFFFFFFFU)

/* EOI */

#define SDL_ESM_EOI_KEY_MASK                                                   (0x000007FFU)
#define SDL_ESM_EOI_KEY_SHIFT                                                  (0x00000000U)
#define SDL_ESM_EOI_KEY_MAX                                                    (0x000007FFU)


/* GROUP_N_LOCK */

#define SDL_ESM_GROUP_LOCK_MASK                                                (0xFFFFFFFFU)
#define SDL_ESM_GROUP_LOCK_SHIFT                                               (0x00000000U)
#define SDL_ESM_GROUP_LOCK_MAX                                                 (0xFFFFFFFFU)

/* GROUP_N_COMMIT */

#define SDL_ESM_GROUP_COMMIT_MASK                                              (0xFFFFFFFFU)
#define SDL_ESM_GROUP_COMMIT_SHIFT                                             (0x00000000U)
#define SDL_ESM_GROUP_COMMIT_MAX                                               (0xFFFFFFFFU)

/* CRI_PRI_INFLUENCE_LOCK */

#define SDL_ESM_LOCK_CRI_PRI_INFLUENCE_MASK                                    (0xFFFFFFFFU)
#define SDL_ESM_LOCK_CRI_PRI_INFLUENCE_SHIFT                                   (0x00000000U)
#define SDL_ESM_LOCK_CRI_PRI_INFLUENCE_MAX                                     (0xFFFFFFFFU)

/* CRI_PRI_INFLUENCE_COMMIT */

#define SDL_ESM_COMMIT_CRI_PRI_INFLUENCE_MASK                                  (0xFFFFFFFFU)
#define SDL_ESM_COMMIT_CRI_PRI_INFLUENCE_SHIFT                                 (0x00000000U)
#define SDL_ESM_COMMIT_CRI_PRI_INFLUENCE_MAX                                   (0xFFFFFFFFU)

/* MMR_CONFIG_LOCK */
#define SDL_ESM_MMR_CONFIG_LOCK_MASK                                           (0x00000127U)
#define SDL_ESM_MMR_CONFIG_LOCK_SHIFT                                          (0x00000000U)
#define SDL_ESM_MMR_CONFIG_LOCK_MAX                                            (0xFFFFFFFFU)

/* MMR_CONFIG_COMMIT */
#define SDL_ESM_MMR_CONFIG_COMMIT_MASK                                         (0x00000127U)
#define SDL_ESM_MMR_CONFIG_COMMIT_SHIFT                                        (0x00000000U)
#define SDL_ESM_MMR_CONFIG_COMMIT_MAX                                          (0xFFFFFFFFU)

/* PIN_CTRL */

#define SDL_ESM_SYS_PIN_CTRL_KEY_MASK                                          (0x0000000FU)
#define SDL_ESM_SYS_PIN_CTRL_KEY_SHIFT                                         (0x00000000U)
#define SDL_ESM_SYS_PIN_CTRL_KEY_MAX                                           (0x0000000FU)

#define SDL_ESM_SYS_PIN_CTRL_PWM_EN_MASK                                       (0x000000F0U)
#define SDL_ESM_SYS_PIN_CTRL_PWM_EN_SHIFT                                      (0x00000004U)
#define SDL_ESM_SYS_PIN_CTRL_PWM_EN_MAX                                        (0x0000000FU)

#define SDL_ESM_SYS_PIN_CTRL_POLARITY_MASK                                     (0x00000F00U)
#define SDL_ESM_SYS_PIN_CTRL_POLARITY_SHIFT                                    (0x00000008U)
#define SDL_ESM_SYS_PIN_CTRL_POLARITY_MAX                                      (0x00000F00U)

/* PIN_STS */

#define SDL_ESM_SYS_PIN_STS_VAL_MASK                                           (0x00000001U)
#define SDL_ESM_SYS_PIN_STS_VAL_SHIFT                                          (0x00000000U)
#define SDL_ESM_SYS_PIN_STS_VAL_MAX                                            (0x00000001U)

#define SDL_ESM_SYS_PIN_INACTIVE                                               (0x00000001U)
#define SDL_ESM_SYS_PIN_ACTIVE                                                 (0x00000000U)

/* PIN_CNTR */

#define SDL_ESM_SYS_PIN_CNTR_COUNT_MASK                                        (0x00FFFFFFU)
#define SDL_ESM_SYS_PIN_CNTR_COUNT_SHIFT                                       (0x00000000U)
#define SDL_ESM_SYS_PIN_CNTR_COUNT_MAX                                         (0x00FFFFFFU)

/* PIN_CNTR_PRE */

#define SDL_ESM_SYS_PIN_CNTR_PRE_COUNT_MASK                                    (0x00FFFFFFU)
#define SDL_ESM_SYS_PIN_CNTR_PRE_COUNT_SHIFT                                   (0x00000000U)
#define SDL_ESM_SYS_PIN_CNTR_PRE_COUNT_MAX                                     (0x00FFFFFFU)

/* HI_PRI_WD_CFG */

#define SDL_ESM_CPU_HI_PRI_WD_CFG_MAX                                          (0x00000A0AU)

#define SDL_ESM_CPU_HI_PRI_WD_CFG_EN_MASK                                      (0x0000000AU)
#define SDL_ESM_CPU_HI_PRI_WD_CFG_EN_SHIFT                                     (0x00000000U)
#define SDL_ESM_CPU_HI_PRI_WD_CFG_EN_MAX                                       (0x0000000AU)

#define SDL_ESM_CPU_HI_PRI_WATCHDOG_ENABLE                                     (0x0000000AU)
#define SDL_ESM_CPU_HI_PRI_WATCHDOG_DISABLE                                    (0x00000000U)

#define SDL_ESM_CPU_HI_PRI_WD_CFG_EMU_MASK                                     (0x00000A00U)
#define SDL_ESM_CPU_HI_PRI_WD_CFG_EMU_SHIFT                                    (0x00000008U)
#define SDL_ESM_CPU_HI_PRI_WD_CFG_EMU_MAX                                      (0x00000A00U)

/* HI_PRI_WD_CNTR */

#define SDL_ESM_CPU_HI_PRI_WD_CNTR_COUNT_MASK                                  (0X0000FFFFU)
#define SDL_ESM_CPU_HI_PRI_WD_CNTR_COUNT_SHIFT                                 (0X00000000U)
#define SDL_ESM_CPU_HI_PRI_WD_CNTR_COUNT_MAX                                   (0X0000FFFFU)

/* HI_PRI_WD_CNTR_PRE */

#define SDL_ESM_CPU_HI_PRI_WD_PRE_COUNT_MASK                                   (0x00FFFFFFU)
#define SDL_ESM_CPU_HI_PRI_WD_PRE_COUNT_SHIFT                                  (0x00000000U)
#define SDL_ESM_CPU_HI_PRI_WD_PRE_COUNT_MAX                                    (0x00FFFFFFU)

/* HI_PRI_WD_INTR_SET */

#define SDL_ESM_CPU_SET_HI_PRI_WD_INTR_MASK                                    (0x00000001U)
#define SDL_ESM_CPU_SET_HI_PRI_WD_INTR_SHIFT                                   (0x00000000U)
#define SDL_ESM_CPU_SET_HI_PRI_WD_INTR_MAX                                     (0x00000001U)

/* HI_PRI_WD_INTR_CLR */

#define SDL_ESM_CPU_CLR_HI_PRI_WD_INTR_MASK                                    (0x00000001U)
#define SDL_ESM_CPU_CLR_HI_PRI_WD_INTR_SHIFT                                   (0x00000000U)
#define SDL_ESM_CPU_CLR_HI_PRI_WD_INTR_MAX                                     (0x00000001U)

/* ERRPIN_MON_CFG */

#define SDL_ESM_SYS_CFG_ERRPIN_MON_MASK                                        (0x0000000AU)
#define SDL_ESM_SYS_CFG_ERRPIN_MON_SHIFT                                       (0x00000000U)
#define SDL_ESM_SYS_CFG_ERRPIN_MON_MAX                                         (0x0000000AU)

#define SDL_ESM_SYS_CFG_ERRPIN_MON_EN_KEY                                      (0x0000000AU)
#define SDL_ESM_SYS_CFG_ERRPIN_MON_DIS_KEY                                     (0x00000000U)

/* ERRPIN_MON_INTR_SET */

#define SDL_ESM_SYS_SET_ERRPIN_MON_INTR_MASK                                   (0x00000001U)
#define SDL_ESM_SYS_SET_ERRPIN_MON_INTR_SHIFT                                  (0x00000000U)
#define SDL_ESM_SYS_SET_ERRPIN_MON_INTR_MAX                                    (0x00000001U)

/* ERRPIN_MON_INTR_CLR */

#define SDL_ESM_SYS_CLR_ERRPIN_MON_INTR_MASK                                   (0x00000001U)
#define SDL_ESM_SYS_CLR_ERRPIN_MON_INTR_SHIFT                                  (0x00000000U)
#define SDL_ESM_SYS_CLR_ERRPIN_MON_INTR_MAX                                    (0x00000001U)

/* ERRPIN_INFLUENCE_LOCK */

#define SDL_ESM_SYS_LOCK_ERRPIN_INFLUENCE_MASK                                 (0xFFFFFFFFU)
#define SDL_ESM_SYS_LOCK_ERRPIN_INFLUENCE_SHIFT                                (0x00000000U)
#define SDL_ESM_SYS_LOCK_ERRPIN_INFLUENCE_MAX                                  (0xFFFFFFFFU)

/* ERR_PIN_INFLUENCE_COMMIT */

#define SDL_ESM_SYS_COMMIT_ERRPIN_INFLUENCE_MASK                               (0xFFFFFFFFU)
#define SDL_ESM_SYS_COMMIT_ERRPIN_INFLUENCE_SHIFT                              (0x00000000U)
#define SDL_ESM_SYS_COMMIT_ERRPIN_INFLUENCE_MAX                                (0xFFFFFFFFU)

/* ERR_PIN_INFLUENCE_LOCK */

#define SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK_MASK                                (0xFFFFFFFFU)
#define SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK_SHIFT                               (0x00000000U)
#define SDL_ESM_SYS_ERR_PIN_INFLUENCE_LOCK_MAX                                 (0x00000008U)

/* ERR_PIN_INFLUENCE_COMMIT */

#define SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT_MASK                              (0xFFFFFFFFU)
#define SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT_SHIFT                             (0x00000000U)
#define SDL_ESM_SYS_ERR_PIN_INFLUENCE_COMMIT_MAX                               (0x00000008U)


#ifdef __cplusplus
}
#endif
#endif /* SDLR_ESM_H_ */
