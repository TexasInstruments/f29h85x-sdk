/* ###########################################################################
 *
 * FILE:  sdl_lcm_example.c
 *
 * TITLE: Example file for the demonstration of the LCM library.
 *
 *
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

########################################################################### */


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "board.h"
#include <kernel/dpl/DebugP.h>
#include <sdl_esm.h>
#include <sdl_lcm.h>


SDL_ESM_Config LCM_esmInitConfig =
{
    .enableBitmap =   {0x00000000U,
                       SDL_ESM_EVENT_LCM_CPU1SS_LCMPERR_MASK | SDL_ESM_EVENT_RTDMA_LCM_CMP_ERR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       SDL_ESM_EVENT_LCM_CPU1SS_REG_PAR_ERR_MASK | SDL_ESM_EVENT_LCM_RTDMA_REG_PAR_ERR_MASK},
    .priorityBitmap = {0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
    .errorPinBitmap = {0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U}
};

__attribute__((interrupt("INT")))
static void SDL_ESMLowPriIntrISR(void)
{
    SDL_ESM_IntrStatus intrStatus;

    do
    {
        /* Get ESM interrupt status and try to clear event */
        SDL_ESM_loInterruptHandler(SDL_ESMCPU1_BASE, &intrStatus);

        if(intrStatus.selfTestStatus != SDL_ESM_SELF_TEST_ACTIVE)
        {
            /* Unexpected ESM event */
            ESTOP0;
        }

    }while(intrStatus.nextPendPulseEvent != SDL_ESM_NO_EVENT_VALUE);

    SDL_ESM_writeEOI(SDL_ESMCPU1_BASE, SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR);
}

static void SDL_registerESMISR(void)
{
    Interrupt_Config intrParams;

    intrParams.enable      = true;
    intrParams.handler     = &SDL_ESMLowPriIntrISR;
    intrParams.priority    = 10;
    intrParams.linkOwner   = SSU_LINK2;
    intrParams.contextID   = INTERRUPT_CONTEXT_AGNOSTIC;
    intrParams.apiLinkID   = SSU_API_DISABLE;

    Interrupt_configChannel(INT_ESM_LOWPRI, intrParams);
}

void test_sdl_lcm_test_app (void)
{
    /* Declarations of variables */
    int32_t retval;
    int32_t result;
    uint32_t status;

    DebugP_log("\n LCM Example Test Application\r\n");

    result = SDL_ESM_init(SDL_ESMCPU1_BASE, &LCM_esmInitConfig);

    /* Register the SDL_ESM interrupt handler */
    SDL_registerESMISR();

    if (result != SDL_PASS)
    {
        /* print error and quit */
        DebugP_log("Error initializing ESM: result = %d\n", result);
        return;
    }
    else
    {
        DebugP_log("\nInit ESM complete \n");
    }

    retval = SDL_LCM_enableLockstep();

    if(retval == SDL_PASS)
    {
        DebugP_log("\n Enabled the LCM module");
    }
    else
    {
        DebugP_log("\n Enable LCM module test got failed \r\n");
        return;
    }

    /* Enable CPU LCM comparison and do self tests */
    retval = SDL_LCM_enableComparator(SDL_LCM_CPU_BASE);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n CPU: Enabled the LCM comparator");
    }
    else
    {
        DebugP_log("\n CPU: Enable LCM comparator test got failed \r\n");
        return;
    }

    retval = SDL_LCM_runSelfTest(SDL_LCM_CPU_BASE);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n CPU: Self test is working fine");
    }
    else
    {
        DebugP_log("\n CPU: Self test got Failed \r\n");
        return;
    }

    retval = SDL_LCM_checkRegisterParity(SDL_LCM_CPU_BASE);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n CPU: Register parity error is working fine");
    }
    else
    {
        DebugP_log("\n CPU: Register parity test got Failed \r\n");
        return;
    }

    retval = SDL_LCM_checkCompareError(SDL_LCM_CPU_BASE);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n CPU: Compare error is working fine");
    }
    else
    {
        DebugP_log("\n CPU: Compare error test got Failed \r\n");
        return;
    }

    retval = SDL_LCM_getStatus(SDL_LCM_CPU_BASE,&status);

    if(retval == SDL_PASS)
    {
        if(status & SDL_LCM_STATUS_LSEN)
        {
            DebugP_log("\n CPU: lockstep is enabled");
        }
        else
        {
            DebugP_log("\n CPU: lockstep is disabled");
        }
    }
    else
    {
        DebugP_log("\n CPU: could not get the status \r\n");
        return;
    }

    retval = SDL_LCM_clearStatus(SDL_LCM_CPU_BASE,SDL_LCM_STATUS_CLEAR_STPASS);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n CPU: cleared the status of the bit");
    }
    else
    {
        DebugP_log("\n CPU: could not clear the status \r\n");
        return;
    }

    retval = SDL_LCM_lockRegister(SDL_LCM_CPU_BASE,SDL_LCM_LOCK_LCM_CONTROL);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n CPU: locked the bit in the register");
    }
    else
    {
        DebugP_log("\n CPU: could not lock the bit \r\n");
        return;
    }

    retval = SDL_LCM_unlockRegister(SDL_LCM_CPU_BASE,SDL_LCM_LOCK_LCM_CONTROL);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n CPU: unlocked the bit in the register");
    }
    else
    {
        DebugP_log("\n CPU: could not unlock the bit \r\n");
        return;
    }

    retval = SDL_LCM_commitRegister(SDL_LCM_CPU_BASE,SDL_LCM_COMMIT_LCM_CONTROL);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n CPU: commited the bit in the register");
    }
    else
    {
        DebugP_log("\n CPU: could not commit the bit \r\n");
        return;
    }

    /* Enable DMA LCM comparison and do self tests */
    retval = SDL_LCM_enableComparator(SDL_LCM_DMA_BASE);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n DMA: Enabled the LCM comparator");
    }
    else
    {
        DebugP_log("\n DMA: Enable LCM comparator test got failed \r\n");
        return;
    }

    retval = SDL_LCM_runSelfTest(SDL_LCM_DMA_BASE);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n DMA: Self test is working fine");
    }
    else
    {
        DebugP_log("\n DMA: Self test got Failed \r\n");
        return;
    }

    retval = SDL_LCM_checkRegisterParity(SDL_LCM_DMA_BASE);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n DMA: Register parity error is working fine");
    }
    else
    {
        DebugP_log("\n DMA: Register parity test got Failed \r\n");
        return;
    }

    retval = SDL_LCM_checkCompareError(SDL_LCM_DMA_BASE);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n DMA: Compare error is working fine");
    }
    else
    {
        DebugP_log("\n DMA: Compare error test got Failed \r\n");
        return;
    }

    retval = SDL_LCM_getStatus(SDL_LCM_DMA_BASE,&status);

    if(retval == SDL_PASS)
    {
        if(status & SDL_LCM_STATUS_LSEN)
        {
            DebugP_log("\n DMA: lockstep is enabled");
        }
        else
        {
            DebugP_log("\n DMA: lockstep is disabled");
        }
    }
    else
    {
        DebugP_log("\n DMA: could not get the status \r\n");
        return;
    }

    retval = SDL_LCM_clearStatus(SDL_LCM_DMA_BASE,SDL_LCM_STATUS_CLEAR_STPASS);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n DMA: cleared the status of the bit");
    }
    else
    {
        DebugP_log("\n DMA: could not clear the status \r\n");
        return;
    }

    retval = SDL_LCM_lockRegister(SDL_LCM_DMA_BASE,SDL_LCM_LOCK_LCM_CONTROL);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n DMA: locked the bit in the register");
    }
    else
    {
        DebugP_log("\n DMA: could not lock the bit \r\n");
        return;
    }

    retval = SDL_LCM_unlockRegister(SDL_LCM_DMA_BASE,SDL_LCM_LOCK_LCM_CONTROL);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n DMA: unlocked the bit in the register");
    }
    else
    {
        DebugP_log("\n DMA: could not unlock the bit \r\n");
        return;
    }

    retval = SDL_LCM_commitRegister(SDL_LCM_DMA_BASE,SDL_LCM_COMMIT_LCM_CONTROL);

    if(retval == SDL_PASS)
    {
        DebugP_log("\n DMA: commited the bit in the register");
    }
    else
    {
        DebugP_log("\n DMA: could not commit the bit \r\n");
        return;
    }

    if (retval == SDL_PASS)
    {
        DebugP_log("\n All tests have passed.\r\n");
    }
    else
    {
        DebugP_log("\n Few/all tests Failed \r\n");
    }
}

int main(void)
{

    /* Initialize device clock, peripheral clocks and interrupts */
    Device_init();

    /* Board Initialization */
    Board_init();

    /* Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU. */
    ENINT;
    Interrupt_enableGlobal();

    test_sdl_lcm_test_app();

    while(1)
    {

    }
}
