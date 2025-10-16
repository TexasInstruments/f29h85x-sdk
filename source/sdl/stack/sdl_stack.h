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
 *  \addtogroup sdl_stack_group
 *
 *  @{
 */

/**
 *  \file     sdl_stack.h
 *
 * \brief
 *  Header file contains enumerations, structure definitions and function
 *  declarations for SDL Stack Module interface.
 */

#ifndef SDL_STACK_H_
#define SDL_STACK_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <include/sdlr_baseaddress.h>
#include <include/hw_types.h>
#include <include/sdl_types.h>
#include "sdlr_erad.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

#define SDL_STACK_MAX_EBC_INSTANCES      8U
#define SDL_STACK_MAX_SEC_INSTANCES      4U
#define SDL_STACK_MAX_AND_MASK_INSTANCES 4U
#define SDL_STACK_MAX_OR_MASK_INSTANCES  4U

#define SDL_STACK_OWNER_APPLICATION      2U
#define SDL_STACK_BUSCOMP_COMPMODE_GT    4U
#define SDL_STACK_BUSCOMP_BUS_DWAB       1U
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief This enumerator defines the state of the respective module.
 */
typedef enum
{
    SDL_STACK_STATE_IDLE      = 0,   
    /**< Module is idle  */
    SDL_STACK_STATE_ENABLED   = 2,   
    /**< Module is enabled  */
    SDL_STACK_STATE_COMPLETED = 3    
    /**< Module was enabled and an event occurred  */
} SDL_Stack_Status;

/**
 * \brief This enumerator defines the Enhanced Bus Comparator instances.
 */
typedef enum
{
    SDL_STACK_BUSCOMP0 = 0,
    SDL_STACK_BUSCOMP1 = 1,
    SDL_STACK_BUSCOMP2 = 2,
    SDL_STACK_BUSCOMP3 = 3,
    SDL_STACK_BUSCOMP4 = 4,
    SDL_STACK_BUSCOMP5 = 5,
    SDL_STACK_BUSCOMP6 = 6,
    SDL_STACK_BUSCOMP7 = 7,
    SDL_STACK_INVALID  = 8,
} SDL_Stack_BusCompInstance;

/**
 * \brief Bus Comparator configuration
 *
 * This structure defines bus comparator configuration
 */
typedef struct
{
    /**< Mask to be used for comparing */
    uint64_t mask;
    /**< Reference value to be compared */    
    uint64_t reference;
    /**< Enable Interrupt on event match */
    bool enableInt;
    /**< Enable NMI. enableInt have to be enabled in order 
     * for enableNMI to be enabled 
     */
    bool enableNMI;
    /**< Enable CPU halt on event match */
    bool enableStop;
    /**< Enable SPSEL match */
    bool enableSpselMatch;
    /**< Stack pointer Select value to be used for SPSEL match. */
    uint32_t spsel;
} SDL_Stack_Config;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *
 * \brief  Sets the current owner of the EBC instance.
 *
 * \param  owner : Owner of the EBC instance that is to be set.
 *
 * \return None
 */
__attribute__((always_inline))
static inline void SDL_Stack_setBusCompOwnership(SDL_Stack_BusCompInstance instance, uint32_t owner)
{
    /* Set the EBC Owner as owner*/
    HW_WR_FIELD32(SDL_ERAD_BASE + SDL_ERAD_EBC_OWNER((uint32_t)instance), SDL_ERAD_EBC_OWNER_OWNER, owner);
                            
}

/**
 *
 * \brief   Disables the Enhanced bus comparator module instance.
 *
 * \param  instances: EBC instances 
 *
 * \return None
 */
__attribute__((always_inline))
static inline void SDL_Stack_disableBusCompModule(SDL_Stack_BusCompInstance instance)
{
    /* Write into the control register to disable the module */
    
    HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance), SDL_ERAD_EBC_CNTL_EN >> 1U);
}

/**
 *
 * \brief   Clears the event fired status of any of the modules.
 *
 * \param  instances: EBC instances 
 *
 * \return None
 */
__attribute__((always_inline))
static inline void SDL_Stack_clearBusCompEvent(SDL_Stack_BusCompInstance instance)
{
    /* Clear the event fired bit by writing into EVENT_CLR register */
    
    HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_STATUSCLEAR((uint32_t)instance), SDL_ERAD_EBC_STATUSCLEAR_EVENT_FIRED);
                      
}

/**
 *
 * \brief   Gets the current owner of the EBC instance.
 *
 * \param  instances: EBC instances 
 *
 * \return None
 */
__attribute__((always_inline))
static inline uint32_t SDL_Stack_getBusCompOwnership(SDL_Stack_BusCompInstance instance)
{
    /* Read EBC Owner register and return value */
    
    return (HW_RD_FIELD32(SDL_ERAD_BASE +
            SDL_ERAD_EBC_OWNER((uint32_t)instance), SDL_ERAD_EBC_OWNER_OWNER));
}

/**
 *
 * \brief   Returns the status of an Enhanced bus comparator (EBC).
 *
 * \param  instances: EBC instances 
 *
 * \return None
 */
__attribute__((always_inline))
static inline SDL_Stack_Status SDL_Stack_getBusCompStatus(SDL_Stack_BusCompInstance instance)
{
    /* Read and return status of Enhanced Bus comparator (EBC) */
    uint32_t regVal = ((HW_RD_REG32(SDL_ERAD_BASE +
            SDL_ERAD_EBC_STATUS((uint32_t)instance)) &
            SDL_ERAD_EBC_STATUS_STATUS_MASK) >> SDL_ERAD_EBC_STATUS_STATUS_SHIFT);
    return (SDL_Stack_Status) regVal;
}

/**
 *
 * \brief   Enables the Enhanced bus comparator module instance.
 *
 * \param  instances: EBC instances 
 *
 * \return None
 */
__attribute__((always_inline))
static inline void SDL_Stack_enableBusCompModule(SDL_Stack_BusCompInstance instance)
{
    /* Write into the control register to enable the module */
    HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance), 
               (HW_RD_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance)) | SDL_ERAD_EBC_CNTL_EN));
}

/**
 *
 * \brief   This function configures the Enhanced bus comparator with the given parameters.
 *
 * \param   instance: EBC instances.
 * \param   configParams: configuration parameters are used to 
 *                        configure the enhanced bus comparator for stack overflow detection.
 *
 * \return  SDL_PASS - success
 * @n       SDL_EFAIL - return a failure if it's unable to get ownership
 * @n       SDL_EBADARGS - API fails due to bad input arguments
 *
 */
int32_t SDL_Stack_configBusComp(SDL_Stack_BusCompInstance instance,
                                        const SDL_Stack_Config *configParams);

/** @} */
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* SDL_ERAD_H_ */
