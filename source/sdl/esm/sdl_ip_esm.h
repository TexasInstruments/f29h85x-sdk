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
 *  \addtogroup sdl_esm_group
 *
 *  @{
 */

/**
 *  \file     sdl_ip_esm.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of ESM.
 *            This also contains some related macros.
 */

#ifndef SDL_IP_ESM_H
#define SDL_IP_ESM_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <include/sdl_types.h>
#include <include/hw_types.h>
#include <include/sdlr_intr_esm.h>
#include <include/sdlr_baseaddress.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SDL_ESM_INTRSTATUS_EN                 ((uint32_t)1U)
#define SDL_ESM_INTRSTATUS_DIS                ((uint32_t)0U)

/**
 *  \anchor SDL_ESM_OperationMode
 *  \name ESM Operation Mode type
 *  @{
 */

/**
 * \brief  ESM Operation Mode type.
 */
typedef uint32_t SDL_ESM_OperationMode;

#define SDL_ESM_OPERATION_MODE_NORMAL         ((uint32_t)0x0U)
    /**< Configure ESM operation mode to normal mode */
#define SDL_ESM_OPERATION_MODE_CLEAR_EVENT    ((uint32_t)0x5U)
    /**< Configure ESM operation mode to clear event mode */
#define SDL_ESM_OPERATION_MODE_ERROR_FORCE    ((uint32_t)0xAU)
    /**< Configure ESM operation mode to error force mode */
/** @} */

/**
 *  \anchor SDL_ESM_ErrPinOutSignal
 *  \name ESM Error Output Signal type
 *  @{
 */

/**
 * \brief  ESM Error Output Signal type.
 */
typedef uint32_t SDL_ESM_ErrPinOutSignal;

#define SDL_ESM_LVL_PINOUT 0x0U
    /**< Configure ESM error output mode to LEVEL output */
#define SDL_ESM_PWM_PINOUT 0xFU
    /**< Configure ESM error output mode to PWM output */
/** @} */


/**
 *  \anchor SDL_ESM_IntrType
 *  \name ESM Interrupt Type to select level for interrupt.
 *  @{
 */

typedef uint32_t SDL_ESM_IntrType;

#define SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR       ((uint32_t)0x0U)
    /**< Configure interrupt to low priority interrupt */
#define SDL_ESM_INTR_TYPE_HIGH_PRIO_ERROR      ((uint32_t)0x1U)
    /**< Configure interrupt to high priority interrupt */
#define SDL_ESM_INTR_TYPE_HIGH_PRIO_WATCHDOG   ((uint32_t)0x2U)
    /**< Configure interrupt to high priority watchdog interrupt. This option
     *   is only applicable to SDL_ESM_writeEOI()!
     */
/** @} */

/**
 *  \anchor SDL_ESM_MMRConfig
 *  \name ESM MMR Configurations
 *  @{
 */

typedef uint32_t SDL_ESM_MMRConfig;

#define SDL_ESM_MMRCONFIG_GLOBAL_EN           (0x100U)
  /**< Configure to lock/commit global enable Register */
#define SDL_ESM_MMRCONFIG_GLOBAL_SOFT_RESET   (0x20U)
  /**< Configure to lock/commit global Soft reset Register */
#define SDL_ESM_MMRCONFIG_ERROR_PIN           (0x4U)
  /**< Configure to lock/commit Error Pin Config Register */
#define SDL_ESM_MMRCONFIG_ERRORPIN_MON        (0x2U)
  /**< Configure to lock/commit Error Pin Monitor Config Register */
#define SDL_ESM_MMRCONFIG_HIGHPRIO_WD         (0x1U)
  /**< Configure to lock/commit High Priority Watchdog Config Register */
/** @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Defines the self-test states
 */
typedef enum {
    SDL_ESM_SELF_TEST_NONE = 0x0000,
    /**< The ESM interrupt was not caused by a self test */
    SDL_ESM_SELF_TEST_ACTIVE = 0xA5A5
    /**< The ESM interrupt was caused by a self test */
} SDL_ESM_SelfTestStatus;

/**
 * \brief This enumerator defines the polarity type for Error Pin
 */
typedef enum {
    SDL_ESM_LVL_MODE_POLARITY = 0x0U,
    /**< Level mode polarity  */
    SDL_ESM_PWM_MODE_POLARITY = 0xFU
    /**< PWM mode polarity */
}SDL_ESM_PolarityType;

/**
 * \brief  Structure for accessing Revision ID of ESM module.
 */
typedef struct sdlesmRevisionID
{
    uint32_t scheme;
    /**< Scheme */
    uint32_t bu;
    /**< Business Unit */
    uint32_t func;
    /**< Functional number */
    uint32_t rtlRev;
    /**< RTL revision */
    uint32_t major;
    /**< Major revision */
    uint32_t custom;
    /**< Custom revision */
    uint32_t minor;
    /**< Minor revision */
}SDL_ESM_RevisionID_t;

/**
 * \brief  Structure for accessing information register of ESM module.
 */
typedef struct sdlesmInfo
{
    uint32_t lastRstType;
    /**< Last reset type
     *   0 - Last reset was a Power On Reset
     *   1 - Last reset was a Warm Reset
     */
    uint32_t critIntr;
    /**< Critical priority Interrupt Indication
     *   0 - Critical Priority Interrupt not triggered
     *   1 - Critical Priority Interrupt has triggered
     */
    uint32_t plsGrpNum;
    /**< Number of event groups that are pulse */
    uint32_t lvlGrpNum;
    /**< Number of event groups that are level */
}SDL_ESM_Info_t;

/**
 * \brief  Structure to access the status of interrupts belonging to a High or
 *         Low priority interrupt.
 */
typedef struct
{
    uint32_t highestPendPulseEvent;
    /**< Indicates what is the highest priority pending pulse event. */
    uint32_t highestPendLevelEvent;
    /**< Indicates what is the highest priority pending level event. */
    uint32_t nextPendPulseEvent;
    /**< Indicates what is the highest priority pending pulse event. */
    uint32_t nextPendLevelEvent;
    /**< Indicates what is the highest priority pending level event. */
    uint32_t grpIntrStatus;
    /**< Indicates which Event Groups have one or more interrupts
     *   pending. This register is bit oriented where bit 0 is for
     *   Event Group 0, bit 1 is for Event Group 1, etc…
     *   (bit N is for Event Group N).
     */
    SDL_ESM_SelfTestStatus selfTestStatus;
    /**< ESM self tests status */
}SDL_ESM_IntrStatus;

/**
 * \brief  ESM Error Group static registers list.
 */
typedef struct {
    volatile uint32_t RAW;                       /* Config Error Group Event Raw Status/Set Register */
    volatile uint32_t STATUS;                    /* Config Error Group Interrupt Enable Status/Clear Register */
    volatile uint32_t INTR_EN_SET;               /* Error Group Interrupt Enable Set Register */
    volatile uint32_t INTR_EN_CLR;               /* Error Group Interrupt Enable Clear Register */
    volatile uint32_t INT_PRIO;                  /* Error Group Interrupt Priority Register */
    volatile uint32_t CRIT_EN_SET;               /* Error Group Critical Priority Interrupt Influence Set Register */
    volatile uint32_t CRIT_EN_CLR;               /* Error Group Critical Priority Interrupt Influence Clear Register */
    volatile uint32_t PIN_EN_SET;                /* Error Group Error Pin Influence Set Register */
    volatile uint32_t PIN_EN_CLR;                /* Error Group Error Pin Influence Clear Register */
} SDL_ESM_ErrGrp_StaticRegs;

/**
 * \brief  ESM static registers list.
 */
typedef struct {
    SDL_ESM_ErrGrp_StaticRegs ERR_GRP[SDL_ESM_NUM_EVENT_GROUPS];
    volatile uint32_t PID;                       /* Revision Register */
    volatile uint32_t INFO;                      /* Info Register */
    volatile uint32_t EN;                        /* Global Enable Register */
    volatile uint32_t SFT_RST;
    volatile uint32_t LOW_PRI;                   /* Low Priority Prioritized Register */
    volatile uint32_t HI_PRI;                    /* High Priority Prioritized Register */
    volatile uint32_t LOW;                       /* Low Priority Interrupt Status Register */
    volatile uint32_t HI;                        /* High Priority Interrupt Status Register */
    volatile uint32_t EOI;
    volatile uint32_t HI_PRI_WD_CFG;
    volatile uint32_t HI_PRI_WD_CNTR;
    volatile uint32_t HI_PRI_WD_CNTR_PRE;
    volatile uint32_t HI_PRI_WD_INTR_SET;
    volatile uint32_t HI_PRI_WD_INTR_CLR;
    volatile uint32_t GROUP_N_LOCK;
    volatile uint32_t GROUP_N_COMMIT;
    volatile uint32_t CRI_PRI_INFLUENCE_LOCK;
    volatile uint32_t CRI_PRI_INFLUENCE_COMMIT;
    volatile uint32_t MMR_CONFIG_LOCK;
    volatile uint32_t MMR_CONFIG_COMMIT;
    volatile uint32_t PIN_CTRL;                  /* Error Pin Control Register */
    volatile uint32_t PIN_STS;
    volatile uint32_t PIN_CNTR;
    volatile uint32_t PIN_CNTR_PRE;
    volatile uint32_t PWMH_PIN_CNTR;
    volatile uint32_t PWMH_PIN_CNTR_PRE;
    volatile uint32_t PWML_PIN_CNTR;
    volatile uint32_t PWML_PIN_CNTR_PRE;
    volatile uint32_t ERRPIN_MON_CFG;
    volatile uint32_t ERRPIN_MON_INTR_SET;
    volatile uint32_t ERRPIN_MON_INTR_CLR;
    volatile uint32_t ERR_PIN_INFLUENCE_LOCK;
    volatile uint32_t ERR_PIN_INFLUENCE_COMMIT;
}SDL_ESM_StaticRegs;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *
 * \brief   Checks that that esmBase address is valid
 *
 * \param  esmBase: ESM instance base address
 *
 * \return None
 */
__attribute__((always_inline))
static inline bool SDL_ESM_isBaseValid(uint32_t esmBase)
{
    return(
           ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMCPU1_BASE_FRAME(0U)) ||
           ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMCPU2_BASE_FRAME(0U)) ||
           ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMCPU3_BASE_FRAME(0U)) ||
           ((esmBase & SDL_BASE_ADDR_MASK) == SDL_ESMSYSTEM_BASE_FRAME(0U))
          );
}

/**
 * \brief   This API is used get the ESM revision ID.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pRevId          Pointer to Revision ID of ESM module..
 *                          Refer struct #SDL_ESM_RevisionID_t.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr = SDL_ESMCPU1_BASE;
       SDL_ESM_RevisionID_t   revId;
       int32_t                sdlRet;
       sdlRet = SDL_ESM_getRevisionId (baseAddr, &revId);

   @endverbatim
 *
 */
int32_t SDL_ESM_getRevisionId(uint32_t esmBase, SDL_ESM_RevisionID_t *pRevId);

/**
 * \brief   This API is used read the ESM information register.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pInfo           pointer to variable that
 *                          Contains information register contents of ESM module..
 *                          Refer struct #SDL_ESM_Info_t.
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

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       SDL_ESM_Info_t      esmInfo;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getInfo (baseAddr, &esmInfo);

   @endverbatim
 *
 */
int32_t SDL_ESM_getInfo(uint32_t esmBase, SDL_ESM_Info_t *pInfo);

/**
 * \brief   This API is used to enable Global control of interrupt.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_enableGlobalIntr (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_enableGlobalIntr(uint32_t esmBase);

/**
 * \brief   This API is used to disable Global control of interrupt.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            sdlRet;
       sdlRet = SDL_ESM_disableGlobalIntr (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_disableGlobalIntr(uint32_t esmBase);

/**
 * \brief   This API is used read the ESM information register.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pStatus         pointer to is global Interrupt enabled status
 *                          0h: all interrupts are enabled
 *                          Fh: all interrupts are disabled
 *                         -others: interrupts are in invalid state.Software should never write
 *                          these values. If these values are ever read, they indicate that an
 *                          error has occurred. In this state, all interrupts are enabled (biased to
 *                          false enable).
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

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            enStatus;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getGlobalIntrEnabledStatus (baseAddr, &enStatus);

   @endverbatim
 *
 */
int32_t SDL_ESM_getGlobalIntrEnabledStatus(uint32_t esmBase, uint32_t *pStatus);

/**
 * \brief   This API is used to reset ESM module.
 *          Reset is used to reset all enables and raw status bits.
 *
 * \param   esmBase         Base Address of the ESM Registers.
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

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            sdlRet;
       sdlRet = SDL_ESM_reset (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_reset(uint32_t esmBase);

/**
 * \brief   This API is used to get the interrupt/error status for a group.
 *          This will also return highest pending interrupt for pulse as well
 *          as for level interrupts.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrPrioType    Group for which status to return.
 *                          Refer enum #SDL_ESM_IntrType.
 *
 * \param   intrStatus     pointer to Interrupt status.
 *                         Refer struct #SDL_ESM_IntrStatus.
 *
 * \return                 SDL_PASS - success
 * @n                      SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t                    baseAddr = SDL_ESMCPU1_BASE;
       SDL_ESM_IntrType            priType  = SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR;
       SDL_ESM_IntrStatus          intrStatus;
       int32_t                     sdlRet;

       sdlRet = SDL_ESM_getGroupIntrStatus(baseAddr, priType, &intrStatus);

   @endverbatim
 *
 */
int32_t SDL_ESM_getGroupIntrStatus(uint32_t esmBase, SDL_ESM_IntrType intrPrioType,
                                   SDL_ESM_IntrStatus *intrStatus);

/**
 * \brief   This API is used to write EOI.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrType        Type of interrupt for which to write EOI.
 *                          Refer enum #SDL_ESM_IntrType.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       SDL_ESM_IntrType    intrType  = SDL_ESM_INTR_TYPE_HIGH_PRIO_ERROR;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_writeEOI (baseAddr, intrType);

   @endverbatim
 *
 */
int32_t SDL_ESM_writeEOI(uint32_t esmBase, SDL_ESM_IntrType intrType);

/**
 * \brief   This API is used to configure operation mode of ESM module.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   mode            Channel number for which reset is to be done.
 *                          Refer enum #SDL_ESM_OperationMode.
 *
 * \return                  SDL_PASS - API success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr = SDL_ESMSYSTEM_BASE;
       SDL_ESM_OperationMode  mode     = SDL_ESM_OPERATION_MODE_ERROR_FORCE;
       int32_t                sdlRet;

       sdlRet = SDL_ESM_setPinControlMode (baseAddr, mode);

   @endverbatim
 *
 */
int32_t SDL_ESM_setPinControlMode(uint32_t esmBase, SDL_ESM_OperationMode mode);

/**
 * \brief   This API is used to read operation mode of ESM module.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pMode           pointer to variable to hold ESM operation Mode.
 *                          Refer enum #SDL_ESM_OperationMode.
 *
 * \return                  SDL_PASS - API success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t               baseAddr = SDL_ESMSYSTEM_BASE;
       SDL_ESM_OperationMode  mode;
       uint32_t               sdlRet;

       sdlRet = SDL_ESM_getPinControlMode (baseAddr, &mode);

   @endverbatim
 *
 */
int32_t SDL_ESM_getPinControlMode(uint32_t esmBase, SDL_ESM_OperationMode *pMode);

/**
 * \brief   This API is used to read Error Out Signal (LVL or PWM) of ESM module.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pSignal         pointer to variable to hold ESM Pinout Signal Mode.
 *                          Refer enum #SDL_ESM_ErrPinOutSignal.
 *
 * \return                  SDL_PASS - API success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t                 baseAddr = SDL_ESMSYSTEM_BASE;
       SDL_ESM_ErrPinoutSignal  pSignal;
       uint32_t                 sdlRet;

       sdlRet = SDL_ESM_getErrPinOutSignal(baseAddr, &pSignal);

   @endverbatim
 *
 */
int32_t SDL_ESM_getErrPinOutSignal(uint32_t esmBase, SDL_ESM_ErrPinOutSignal *pSignal);

/**
 * \brief   This API is used to Set the Error Out polarity (LVL or PWM) of ESM module.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pType           enum to set the Error Output Pin polarity.
 *                          Refer enum #SDL_ESM_PolarityType.
 *
 * \return                  SDL_PASS - API success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t                 baseAddr = SDL_ESMSYSTEM_BASE;
       SDL_ESM_PolarityType     pType = SDL_ESM_PWM_MODE_POLARITY;
       uint32_t                 sdlRet;

       sdlRet = SDL_ESM_setErrPinOutPolarity(baseAddr, pType);

   @endverbatim
 *
 */
int32_t SDL_ESM_setErrPinOutPolarity(uint32_t esmBase, SDL_ESM_PolarityType pType);

/**
 * \brief   This API is used to read Error Out Polarity (LVL or PWM) of ESM module.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pType           pointer to variable to hold ESM Pinout Polarity Mode.
 *                          Refer enum #SDL_ESM_PolarityType.
 *
 * \return                  SDL_PASS - API success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t                 baseAddr = SDL_ESMSYSTEM_BASE;
       SDL_ESM_PolarityType     pType;
       uint32_t                 sdlRet;

       sdlRet = SDL_ESM_getErrPinOutPolarity(baseAddr, &pType);

   @endverbatim
 *
 */
int32_t SDL_ESM_getErrPinOutPolarity(uint32_t esmBase, SDL_ESM_PolarityType *pType);

/**
 * \brief   This API is used to reset the nERROR pin.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \note    This will set the nERROR pin to high.
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_resetErrPin (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_resetErrPin(uint32_t esmBase);

/**
 * \brief   This API is used to get the current status of nERROR pin.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pStatus         pointer to Current nERROR pin status.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            status;
       uint32_t            sdlRet;
       sdlRet = SDL_ESM_getErrPinStatus (baseAddr, &status);

   @endverbatim
 *
 */
int32_t SDL_ESM_getErrPinStatus(uint32_t esmBase, uint32_t *pStatus);

/**
 * \brief   This API is used to get the current value of low time counter.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pPinCntrPre     pointer to Counter value Current low time count.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            pinCntrPre;
       int32_t             sdlRet;
       sdlRet  = SDL_ESM_getCurrErrPinLowTimeCnt (baseAddr, &pinCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_getCurrErrPinLowTimeCnt(uint32_t esmBase, uint32_t *pPinCntrPre);

/**
 * \brief   This API is used to configure the low time counter pre-load value.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   lowTime         Time to be configured as LTCP.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * This is the value that will be pre-loaded in to the counter field of the
 * ESM_PIN_CNTR register whenever the ESM enters the
 * ESM_ERROR state from ESM_IDLE. The default value is
 * determined based on the ESM clock frequency, so that there is a
 * minimum low time of 100 micro seconds.
 * This field is only reset by a Power-On-Reset (not warm reset). A
 * global soft reset will set this field to 0h.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            pinCntrPre  = 100;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_setErrPinLowTimePreload (baseAddr, pinCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_setErrPinLowTimePreload(uint32_t esmBase, uint32_t lowTime);

/**
 * \brief   This API is used to read the low time counter pre-load value.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pLowTime        pointer to Time to be read as LTCP.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * This is the value that will be pre-loaded in to the counter field of the
 * ESM_PIN_CNTR register whenever the ESM enters the
 * ESM_ERROR state from ESM_IDLE. The default value is
 * determined based on the ESM clock frequency, so that there is a
 * minimum low time of 100 micro seconds.
 * This field is only reset by a Power-On-Reset (not warm reset). A
 * global soft reset will set this field to 0h.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            inCntrPre;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getErrPinLowTimePreload (baseAddr, &inCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_getErrPinLowTimePreload(uint32_t esmBase, uint32_t *pLowTime);

/**
 * \brief   This API is used to get the current value of high time counter for PWM error.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pHighPWMHTime    pointer to Counter value Current high time count for PWM error.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            pinCntrPre;
       int32_t             sdlRet;
       sdlRet  = SDL_ESM_PWMH_getCurrErrPinHighTimeCnt(baseAddr, &pinCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_PWMH_getCurrErrPinHighTimeCnt(uint32_t esmBase, uint32_t *pHighPWMHTime);

/**
 * \brief   This API is used to configure the high time counter pre-load value for PWM error.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   highTime         Time to be configured as HTCP.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * This is the value that will be loaded in to the counter field of
 * the Error Pin PWM High Counter Value Register whenever the error
 * output pin toggles high.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            pinCntrPre  = 100;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_PWMH_setErrPinHighTimePreload(baseAddr, pinCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_PWMH_setErrPinHighTimePreload(uint32_t esmBase, uint32_t highTime);

/**
 * \brief   This API is used to read the High time counter pre-load value for PWM error.
 *
 * \param   esmBase                Base Address of the ESM Registers.
 *
 * \param   pPinPWMHCntrPre        pointer to Time to be read as HTCP.
 *
 * \return                         SDL_PASS - success
 * @n                              SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * This is the value that will be loaded in to the counter field of
 * the Error Pin PWM High Counter Value Register whenever the error
 * output pin toggles high.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            inCntrPre;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_PWMH_getErrPinHighTimePreload(baseAddr, inCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_PWMH_getErrPinHighTimePreload(uint32_t esmBase, uint32_t *pPinPWMHCntrPre);

/**
 * \brief   This API is used to get the current value of low time counter for PWM error.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   pLowPWMLTime     pointer to Counter value Current low time count for PWM error.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            pinCntrPre;
       int32_t             sdlRet;
       sdlRet  = SDL_ESM_PWML_getCurrErrPinLowTimeCnt(baseAddr, &pinCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_PWML_getCurrErrPinLowTimeCnt(uint32_t esmBase, uint32_t *pLowPWMLTime);

/**
 * \brief   This API is used to configure the low time counter pre-load value for PWM error.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   lowTime         Time to be configured as LTCP.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * This is the value that will be loaded in to the counter field of
 * the Error Pin PWM low Counter Value Register whenever the error
 * output pin toggles low.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            pinCntrPre  = 100;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_PWML_setErrPinLowTimePreload(baseAddr, pinCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_PWML_setErrPinLowTimePreload(uint32_t esmBase, uint32_t lowTime);

/**
 * \brief   This API is used to read the low time counter pre-load value for PWM error.
 *
 * \param   esmBase                Base Address of the ESM Registers.
 *
 * \param   pPinPWMLCntrPre        pointer to Time to be read as LTCP.
 *
 * \return                         SDL_PASS - success
 * @n                              SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * This is the value that will be loaded in to the counter field of
 * the Error Pin PWM Low Counter Value Register whenever the error
 * output pin toggles low.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            inCntrPre;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_PWML_getErrPinLowTimePreload(baseAddr, &inCntrPre);

   @endverbatim
 *
 */
int32_t SDL_ESM_PWML_getErrPinLowTimePreload(uint32_t esmBase, uint32_t *pPinPWMLCntrPre);

/**
 * \brief   This API is used to set the interrupt RAW status.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt for which status to return.
 *
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            intrSrc  = SDL_ESM_EVENT_CLOCKFAIL;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_setIntrStatusRAW (baseAddr, intrSrc);

   @endverbatim
 *
 */
int32_t SDL_ESM_setIntrStatusRAW(uint32_t esmBase, uint32_t intrSrc);

/**
 * \brief   This API is used to get the interrupt RAW status.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt for which status to return.
 *
 * \param   pStatus         pointer to Interrupt status.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            intrSrc  = SDL_ESM_EVENT_CLOCKFAIL;
       uitn32_t            status;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getIntrStatusRAW (baseAddr, intrSrc, &status);

   @endverbatim
 *
 */
int32_t SDL_ESM_getIntrStatusRAW(uint32_t esmBase, uint32_t intrSrc, uint32_t *pStatus);

/**
 * \brief   This API is used to get the interrupt status.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt for which status to return.
 *
 * \param   pStatus         pointer to interrupt status
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            status, intrSrc  = SDL_ESM_EVENT_CLOCKFAIL;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getIntrStatus (baseAddr, intrSrc, &status);

   @endverbatim
 *
 */
int32_t SDL_ESM_getIntrStatus(uint32_t esmBase, uint32_t intrSrc, uint32_t *pStaus);

/**
 * \brief   This API is used to clear the interrupt status.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to clear status.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            intrSrc  = SDL_ESM_EVENT_CLOCKFAIL;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_clearIntrStatus (baseAddr, intrSrc);

   @endverbatim
 *
 */
int32_t SDL_ESM_clearIntrStatus(uint32_t esmBase, uint32_t intrSrc);

/**
 * \brief   This API is used check if interrupt is enabled/disabled.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to enable.
 *
 * \param   pEnStatus       Pointer to status of interrupt enable variable
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            status, intrNum  = 0U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_isEnableIntr (baseAddr, intrNum, &status);

   @endverbatim
 *
 */
int32_t SDL_ESM_isEnableIntr(uint32_t esmBase, uint32_t intrSrc, uint32_t *pEnStatus);

/**
 * \brief   This API is used to enable interrupt.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrNum         Interrupt to enable.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            intrNum  = 0U;
       int32_t             status;
       status = SDL_ESM_enableIntr (baseAddr, intrNum);

   @endverbatim
 *
 */
int32_t SDL_ESM_enableIntr(uint32_t esmBase, uint32_t intrNum);

/**
 * \brief   This API is used to disable interrupt.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrNum         Interrupt to disable.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            intrNum  = 0U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_disableIntr (baseAddr, intrNum);

   @endverbatim
 *
 */
int32_t SDL_ESM_disableIntr(uint32_t esmBase, uint32_t intrNum);

/**
 * \brief   This API is used to set interrupt level.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to set the level.
 *
 * \param   intrPriorityLvl Interrupt level to set.
 *                          Refer enum #SDL_ESM_IntrType.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t                   baseAddr = SDL_ESMCPU1_BASE;
       uint32_t                   intrSrc  = SDL_ESM_EVENT_CLOCKFAIL;
       SDL_ESM_IntrType           pri     = SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR;
       int32_t                    sdlRet;
       sdlRet = SDL_ESM_setIntrPriorityLvl (baseAddr, intrSrc, pri);

   @endverbatim
 *
 */
int32_t SDL_ESM_setIntrPriorityLvl(uint32_t esmBase, uint32_t intrSrc,
                                   SDL_ESM_IntrType intrPriorityLvl);

/**
 * \brief   This API is used to get interrupt level.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to set the level.
 *
 * \param   pIntrPriorityLvl Pointer to Interrupt level to get.
 *                          Refer enum #SDL_ESM_IntrType.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t                    baseAddr = SDL_ESMCPU1_BASE;
       uint32_t                    sintrSrc  = SDL_ESM_EVENT_CLOCKFAIL;
       SDL_ESM_IntrType            pri;
       int32_t                     sdlRet;
       sdlRet = SDL_ESM_getIntrPriorityLvl (baseAddr, intrSrc, &pri);

   @endverbatim
 *
 */
int32_t SDL_ESM_getIntrPriorityLvl(uint32_t esmBase, uint32_t intrSrc,
                                   SDL_ESM_IntrType *pIntrPriorityLvl);

/**
 * \brief   This API is used to set the influence of interrupt on nERROR pin.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt source which will influence nERROR pin.
 *
 * \param   enable          true: Enables influence on nERROR pin if it is true.
 *                          false:Disables influence on nERROR pin if it is false.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            intrSrc  = SDL_ESM_EVENT_CLOCKFAIL;
       int32_t             sdlRet;
       sdlRet =  SDL_ESM_setInfluenceOnErrPin (baseAddr, intrSrc, true);

   @endverbatim
 *
 */
int32_t SDL_ESM_setInfluenceOnErrPin(uint32_t esmBase, uint32_t intrSrc,
                                     bool enable);

/**
 * \brief   This API is used to get the influence of interrupt on nERROR pin.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt source which will influence nERROR pin.
 *
 * \param   pInfluence      pointer to read the influence value
 *                          1: enabled
 *                          0: disabled
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            intrSrc  = SDL_ESM_EVENT_CLOCKFAIL;
       uint32_t            influence;
       int32_t             sdlRet;
       sdlRet =  SDL_ESM_getInfluenceOnErrPin (baseAddr, intrSrc, &influence);

   @endverbatim
 *
 */
int32_t SDL_ESM_getInfluenceOnErrPin(uint32_t esmBase, uint32_t intrSrc,
                                     uint32_t *pInfluence);

/**
 * \brief   This API is used check if Critical priority interrupt is enabled/disabled.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to enable.
 *
 * \param   pEnStatus       Pointer to status of interrupt enable variable
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 *
 * Note: the intrSrc check is only at the IP level max and not done at instance
 *       level, so it is expected to be done at higher layer.
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            status, intrNum  = 0U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_isEnableCriticalIntr (baseAddr, intrNum, &status);

   @endverbatim
 *
 */
int32_t SDL_ESM_isEnableCriticalIntr(uint32_t esmBase, uint32_t intrSrc, uint32_t *pEnStatus);

/**
 * \brief   This API is used to enable Critical Priority interrupt.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrNum         Interrupt to enable.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  ESM module is reset and initialized for desired operation
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            intrNum  = 0U;
       int32_t             status;
       status = SDL_ESM_enableCriticalIntr (baseAddr, intrNum);

   @endverbatim
 *
 */
int32_t SDL_ESM_enableCriticalIntr(uint32_t esmBase, uint32_t intrNum);

/**
 * \brief   This API is used to disable Critical priority interrupt.
 *
 * \param   esmBase         Base Address of the ESM Registers.
 *
 * \param   intrNum         Interrupt to disable.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            intrNum  = 0U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_disableCriticalIntr (baseAddr, intrNum);

   @endverbatim
 *
 */
int32_t SDL_ESM_disableCriticalIntr(uint32_t esmBase, uint32_t intrNum);

/**
 * \brief   This API is used to enable the High priority Watchdog Interrupt.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_enableHiPriWDConfig (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_enableHiPriWDConfig(uint32_t esmBase);

/**
 * \brief   This API is used to disable the High priority Watchdog Interrupt.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_disableHiPriWDConfig (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_disableHiPriWDConfig(uint32_t esmBase);

/**
 * \brief   This API is used to enable the Free run mode for High priority Watchdog.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_enableHiPriWDFreerun (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_enableHiPriWDFreerun(uint32_t esmBase);

/**
 * \brief   This API is used to diable the Free run mode for High priority Watchdog.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_disableHiPriWDFreerun (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_disableHiPriWDFreerun(uint32_t esmBase);

/**
 * \brief   This API is used to get the High priority Watchdog counter value.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   pWDCntrVal      Pointer to current counter value  of High Priority Watchdog
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            cntrValue;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getHiPriWDCounter (baseAddr, &cntrValue);

   @endverbatim
 *
 */
int32_t SDL_ESM_getHiPriWDCounter(uint32_t esmBase, uint32_t *pWDCntrVal);

/**
 * \brief   This API is used to load the High priority Watchdog counter.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   preloadValue    value to be loaded into the preload counter
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            value;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_setHiPriWDCntrPreload (baseAddr, value);

   @endverbatim
 *
 */
int32_t SDL_ESM_setHiPriWDCntrPreload(uint32_t esmBase, uint32_t preloadValue);

/**
 * \brief   This API is used to get the preloaded value from the
 *          the High priority Watchdog preload counter.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   pPreLoadVal     pointer to loaded value into the preload counter
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            value;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_setHiPriWDCntrPreload (baseAddr, value);

   @endverbatim
 *
 */
int32_t SDL_ESM_getHiPriWDCntrPreload(uint32_t esmBase, uint32_t *pPreLoadVal);

/**
 * \brief   This API is used to get the status of the High priority Watchdog Interrupt Register.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   pWDStatus       pointer to to the status of Watchdog Interrupt
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            status;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getHiPriWDIntrStatus(baseAddr, &status);

   @endverbatim
 *
 */
int32_t SDL_ESM_getHiPriWDIntrStatus(uint32_t esmBase, uint32_t *pWDStatus);

/**
 * \brief   This API is used to set the interrupt output of High priority Watchdog Interrupt.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_setHiPriWDIntrOutput(baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_setHiPriWDIntrOutput(uint32_t esmBase);

/**
 * \brief   This API is used to clear the interrupt output of High priority Watchdog Interrupt.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_clearHiPriWDIntrOutput(baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_clearHiPriWDIntrOutput(uint32_t esmBase);

/**
 * \brief   This API is used to enable the Error Pin Monitor Config.
 *
 * \param   esmBase         Base Address of the System ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_enableErrPinMonConfig (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_enableErrPinMonConfig(uint32_t esmBase);

/**
 * \brief   This API is used to disable the Error Pin Monitor Config.
 *
 * \param   esmBase         Base Address of the System ESM Registers.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_disableErrPinMonConfig (baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_disableErrPinMonConfig(uint32_t esmBase);

/**
 * \brief   This API is used to get the status of Error Pin Monitor.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   pStatus         status of whether the Error Pin Monitor is enabled or not
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            pStatus;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getErrPinMonConfigStatus(baseAddr, &pStatus);

   @endverbatim
 *
 */
int32_t SDL_ESM_getErrPinMonConfigStatus(uint32_t esmBase, uint32_t *pStatus);

/**
 * \brief   This API is used to set the Error Pin Monitor Register.
 *
 * \param   esmBase         System ESM Base Address.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_setErrPinMonitorIntr(baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_setErrPinMonitorIntr(uint32_t esmBase);

/**
 * \brief   This API is used to clear the Error Pin Monitor Register.
 *
 * \param   esmBase         System ESM Base Address.
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_clearErrPinMonitorIntr(baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_clearErrPinMonitorIntr(uint32_t esmBase);

/**
 * \brief   This API is used to lock the Error Pin Influence config.
 *
 * \param   esmBase         System ESM Base Address.
 *
 * \param   groupNum        Group Number to lock the error event
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            groupNum = 0x2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_lockErrPinInfluenceConfig(baseAddr, groupNum);

   @endverbatim
 *
 */
int32_t SDL_ESM_lockErrPinInfluenceConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to unlock the Error Pin Influence config.
 *
 * \param   esmBase         System ESM Base Address.
 *
 * \param   groupNum        Group Number to unlock the error event
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            groupNum = 0x2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_unlockErrPinInfluenceConfig(baseAddr, groupNum);

   @endverbatim
 *
 */
int32_t SDL_ESM_unlockErrPinInfluenceConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to commit the Error Pin Influence config.
 *
 * \param   esmBase         System ESM Base Address.
 *
 * \param   groupNum        Group Number to unlock the error event
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            groupNum = 0x2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_commitErrPinInfluenceConfig(baseAddr, groupNum);

   @endverbatim
 *
 */
int32_t SDL_ESM_commitErrPinInfluenceConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to Lock the Error Group Interrupt enabled.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   groupNumber     Group Number of Interrupt to be locked
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            groupNumber = 2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_lockErrorGroupIntrConfig(baseAddr, groupNumber);

   @endverbatim
 *
 */
int32_t SDL_ESM_lockErrorGroupIntrConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to get the Locked group Number.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   groupNumber     pointer to Group Number
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            groupNumber;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getIntrLockReg(baseAddr, &groupNumber);

   @endverbatim
 *
 */
int32_t SDL_ESM_getIntrLockReg(uint32_t esmBase, uint32_t *groupNum);

/**
 * \brief   This API is used to Unlock the Error Group Interrupt enabled.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   groupNumber     Group Number of Interrupt to be locked
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            groupNumber = 2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_unlockErrorGroupIntrConfig(baseAddr, groupNumber);

   @endverbatim
 *
 */
int32_t SDL_ESM_unlockErrorGroupIntrConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to commit the Error Group Interrupt enabled.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   groupNumber     Group Number of Interrupt to be commited
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            groupNumber = 2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_commitErrorGroupIntrConfig(baseAddr, groupNumber);

   @endverbatim
 *
 */
int32_t SDL_ESM_commitErrorGroupIntrConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to lock the Error Pin Influence Configuration.
 *
 * \param   baseAddr        Base Address of the CPU ESM Registers.
 *
 * \param   groupNumber     Group Number of Error Pin to be locked
 * 
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            groupNumber = 2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_setErrPinInfluenceLock(baseAddr, groupNumber);

   @endverbatim
 *
 */
int32_t SDL_ESM_setErrPinInfluenceLock(uint32_t esmBase, uint32_t groupNumber);

/**
 * \brief   This API is used to get the status of Error Pin Influence Configuration.
 *
 * \param   baseAddr        Base Address of the CPU ESM Registers.
 *
 * \param   errorPinlockSTS pointer to the Error Pin Status
 * 
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            errorPinlockSTS;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getErrPinInfluenceLock(baseAddr, &errorPinlockSTS);

   @endverbatim
 *
 */
int32_t SDL_ESM_getErrPinInfluenceLock(uint32_t esmBase, uint32_t *errorPinlockSTS);

/**
 * \brief   This API is used to commit the Error Pin Influence Configuration.
 *
 * \param   baseAddr        System ESM Base Address.
 * 
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_setErrPinInfluenceCommit(baseAddr);

   @endverbatim
 *
 */
int32_t SDL_ESM_setErrPinInfluenceCommit(uint32_t esmBase);

/**
 * \brief   This API is used to get the status of Error Pin Influence Configuration.
 *
 * \param   baseAddr          System ESM Base Address.
 *
 * \param   errorPinCommitSTS pointer to the Error Pin commit Status
 * 
 * \return                    SDL_PASS - success
 * @n                         SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMSYSTEM_BASE;
       uint32_t            errorPinCommitSTS;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_getErrPinInfluenceCommit(baseAddr, &errorPinCommitSTS);

   @endverbatim
 *
 */
int32_t SDL_ESM_getErrPinInfluenceCommit(uint32_t esmBase, uint32_t *errorPinCommitSTS);

/**
 * \brief   This API is used to lock the Critical priority Interrupt Config.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   groupNumber     Group Number of Interrupt to be locked
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            groupNumber = 2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_lockCriticalPriIntrInfluenceConfig(baseAddr, groupNumber);

   @endverbatim
 *
 */
int32_t SDL_ESM_lockCriticalPriIntrInfluenceConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to unlock the Critical priority Interrupt Config.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   groupNumber     Group Number of Interrupt to be unlocked
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            groupNumber = 2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_unlockCriticalPriIntrInfluenceConfig(baseAddr, groupNumber);

   @endverbatim
 *
 */
int32_t SDL_ESM_unlockCriticalPriIntrInfluenceConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to commit the Critical priority Interrupt Config.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   groupNumber     Group Number of Interrupt to be committed
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       uint32_t            groupNumber = 2U;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_commitCriticalPriIntrInfluenceConfig(baseAddr, groupNumber);

   @endverbatim
 *
 */
int32_t SDL_ESM_commitCriticalPriIntrInfluenceConfig(uint32_t esmBase, uint32_t groupNum);

/**
 * \brief   This API is used to lock the MMR Config.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   configMMR       configured MMRs
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       SDL_ESM_MMRConfig   configMMR = SDL_ESM_MMRCONFIG_GLOBAL_EN;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_lockMMRConfig(baseAddr, configMMR);

   @endverbatim
 *
 */
int32_t SDL_ESM_lockMMRConfig(uint32_t esmBase, SDL_ESM_MMRConfig configMMR);

/**
 * \brief   This API is used to unlock the MMR Config.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   configMMR       configured MMRs
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       SDL_ESM_MMRConfig   configMMR = SDL_ESM_MMRCONFIG_GLOBAL_EN;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_unlockMMRConfig(baseAddr, configMMR);

   @endverbatim
 *
 */
int32_t SDL_ESM_unlockMMRConfig(uint32_t esmBase, SDL_ESM_MMRConfig configMMR);


/**
 * \brief   This API is used to commit the MMR Config.
 *
 * \param   esmBase         Base Address of the CPU ESM Registers.
 *
 * \param   configMMR       configured MMRs
 *
 * \return                  SDL_PASS - success
 * @n                       SDL_EBADARGS - API fails due to bad input arguments
 *
 *
 * \pre
 *   @n  None
 *
 * \post
 *   @n  None
 *
 * @b Example
   @verbatim

       uint32_t            baseAddr = SDL_ESMCPU1_BASE;
       SDL_ESM_MMRConfig   configMMR = SDL_ESM_MMRCONFIG_GLOBAL_EN;
       int32_t             sdlRet;
       sdlRet = SDL_ESM_commitMMRConfig(baseAddr, configMMR);

   @endverbatim
 *
 */
int32_t SDL_ESM_commitMMRConfig(uint32_t esmBase, SDL_ESM_MMRConfig configMMR);

#ifdef __cplusplus
}
#endif /*extern "C" */

#endif /*SDL_IP_ESM_H*/

/** @} */