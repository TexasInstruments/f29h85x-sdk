/*
 * SDL ESM
 *
 * Software Diagnostics Reference module for ESM
 *
 *  Copyright (c) Texas Instruments Incorporated 2025
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

#ifndef SDL_ESM_PRIV_H_
#define SDL_ESM_PRIV_H_

#include <stdbool.h>
#include "sdl_esm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* ESM self-test flag */
    SDL_ESM_SelfTestStatus selfTestStatus;
    /* Self-test callback arg */
    void *callbackArg;
    /* Self-test callback to be called during interrupt handlers */
    SDL_ESM_SelfTestCallback selfTestCallback;
    /* Store instance init config */
    SDL_ESM_Config esmInitConfig;
}SDL_ESM_Instance_t;

/**
 *
 * \brief        Clear additional event flags related to the back-to-back CPU
 *               fault errata workaround.
 *
 * \param [in]   esmBase: Base Address of the ESM Registers.
 *
 * This is related to the workaround for an issue where the NMI handler fails to
 * execute when multiple back-to-back CPU faults occur. The workaround involves
 * rerouting the high priority CPU faults through the EPWMXBAR to ERAD to the
 * ERAD NMI ESM event.
 *
 * \return       None
 */
void SDL_ESM_clearNMIFetchErrataWorkaround(uint32_t esmBase);

/**
 *
 * \brief        Gets the ESM interrupt status and processes the interrupt
 *
 * \param [in]   esmBase: Base Address of the ESM Registers.
 * \param [in]   esmIntrPriorityLvlType: Priority level of the interrupt
 * \param [out]  intrStatus: Pointer to an object to hold interrupt status.
 *
 * \return       None
 */
void SDL_ESM_interruptHandler(uint32_t esmBase,
                              SDL_ESM_IntrType esmIntrPriorityLvlType,
                              SDL_ESM_IntrStatus *intrStatus);

/**
 *
 * \brief        Check that ESM instance type is valid for this device, and fill the
 *               SDL_ESM instance
 *
 * \param [in]   esmBase: Base Address of the ESM Registers.
 * \param [out]  pEsmInstancePtr: Pointer to location of ESM instance structure
 *
 * \return       true: if valid instance type; false: if not valid instance type
 */
bool SDL_ESM_selectESMInst(const uint32_t esmBase,
                           SDL_ESM_Instance_t **pEsmInstancePtr);

#ifdef __cplusplus
}
#endif
#endif /* SDL_ESM_PRIV_H_ */
