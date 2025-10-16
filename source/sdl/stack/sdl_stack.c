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

#include "sdl_stack.h"
#include "sdlr_erad.h"
#include <include/hw_types.h>

int32_t SDL_Stack_configBusComp(SDL_Stack_BusCompInstance instance,
                                const SDL_Stack_Config *configParams)
{
    int32_t retVal = SDL_EBADARGS;

    if((instance == SDL_STACK_INVALID) || (configParams == NULL))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        /* Set the ownership of the modules as APPLICATION */
        SDL_Stack_setBusCompOwnership(instance, SDL_STACK_OWNER_APPLICATION);

        /* Check if owner is APPLICATION */
        if(SDL_Stack_getBusCompOwnership(instance) == SDL_STACK_OWNER_APPLICATION)
        {
            retVal = SDL_PASS;
        }
        else
        {
            retVal = SDL_EFAIL;
        }

        if(retVal == SDL_PASS)
        {
            /* Disable the bus comparator*/
            SDL_Stack_disableBusCompModule(instance);

            /* Clear any previous events */
            SDL_Stack_clearBusCompEvent(instance);

            /* Check if the bus comparator is in STACK_STATE_IDLE */
            if(SDL_Stack_getBusCompStatus(instance) == SDL_STACK_STATE_IDLE)
            {
                retVal = SDL_PASS;
            }

        }
        
        if(retVal == SDL_PASS)
        {
            /* Write into necessary registers to configure the bus comparator */
            HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_MASKH((uint32_t)instance),
                        (uint32_t)(configParams->mask >> 32U));

            HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_MASKL((uint32_t)instance),
                        (uint32_t)configParams->mask);
                                                
            HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_REFL((uint32_t)instance), 
                        (uint32_t)configParams->reference);
                                                
            HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_REFH((uint32_t)instance), 
                        (uint32_t)(configParams->reference >> 32U));
                                    
            /* Set the comparison mode and the CPU bus to be monitored
            *   enable interrupt and CPU halt if specified in the parameters
            */

            HWREGH(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance)) =
                ((uint32_t)SDL_STACK_BUSCOMP_COMPMODE_GT   << SDL_ERAD_EBC_CNTL_COMP_MODE_SHIFT) |
                (SDL_STACK_BUSCOMP_BUS_DWAB     << SDL_ERAD_EBC_CNTL_BUS_SEL_SHIFT);

            if(configParams->enableInt || configParams->enableNMI)
            {
                HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance), 
                            (HW_RD_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance)) | SDL_ERAD_EBC_CNTL_INTERRUPT));
                                                    
                if(configParams->enableNMI)
                {
                    HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance), 
                                (HW_RD_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance)) |SDL_ERAD_EBC_CNTL_NMI_EN));
                }
            }

            if(configParams->enableStop)
            {
                HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance), 
                            (HW_RD_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance)) | SDL_ERAD_EBC_CNTL_HALT));
            }

            /*
            * Configure stack qualification.
            * This is relevant only for data read and data write address comparison.
            * These settings are ignored for busses other than data read / data write.
            */
            HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance), 
                        (HW_RD_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance)) | SDL_ERAD_EBC_CNTL_STACK_QUAL));
            
            if(configParams->enableSpselMatch)
            {
                HW_WR_REG32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance), 
                            (uint32_t)SDL_ERAD_EBC_CNTL_SPSEL_MATCH_EN >> 16U);
                                                    
                HW_WR_FIELD32(SDL_ERAD_BASE + SDL_ERAD_EBC_CNTL((uint32_t)instance), 
                            SDL_ERAD_EBC_CNTL_SPSEL, (configParams->spsel << SDL_ERAD_EBC_CNTL_SPSEL_SHIFT));
            }

            /* Enable the bus comparator */
            SDL_Stack_enableBusCompModule(instance);

        }

    }
    
    return retVal;

}