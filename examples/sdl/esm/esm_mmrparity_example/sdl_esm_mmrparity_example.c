/* Copyright (c) 2025 Texas Instruments Incorporated
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

 /**
 *  \file     sdl_esm_mmrparity_example.c
 *
 *  \brief    This file contains ESM MMR Parity Testcase .
 *
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include "sdl_esm_mmrparity_example.h"

/*===========================================================================*/
/*                         Macros and Structures                             */
/*===========================================================================*/

/* None*/

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/

volatile uint32_t isrFlag = 0U;
uint32_t svBusStatus = 0U, dedStatus = 0xFU;

/*===========================================================================*/
/*                   Internal & External function declarations               */
/*===========================================================================*/

__attribute__((interrupt("RTINT"))) void INT_ESM_PARITYERR_ISR(void);

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

SDL_ESM_Config pConfig =
{
    .enableBitmap =   {0x00000000U,     /* Group 0 is enabled by default */
                       SDL_ESM_EVENT_ESM_PARITY_ERROR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
    .priorityBitmap = {0x00000000U,
                       SDL_ESM_EVENT_ESM_PARITY_ERROR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U}
};

SDL_EDC_CtrlReg setEDCControlReg =
{
    .pattern = SDL_EDC_PATTERN_D0,
    .forceNBit = SDL_EDC_FORCE_CURRSETTG_AFTINJ,
    .forceBitError = SDL_EDC_FORCE_SINGLEBIT_ERROR,
    .enableParityChecker = SDL_EDC_PARITYCHECK_ENABLE
};

static void safetyAggregatorErrorInjection(void)
{
    int32_t result;

    /* Enable the ESM Error Aggregator parity error interrupt */
    result = SDL_ESM_SAFETYAGGR_enableAggrIntrErr(SDL_ESMSAFETYAGG_BASE,
                                                  SDL_ESM_SAFETYAGGR_INTR_PARITYERR_EN);

    /* Enable ESM Instance */
    SDL_ESM_SAFETYAGGR_enableEDCIntr(SDL_ESMSAFETYAGG_BASE,
                                    SDL_ESM_SAFETYAGGR_DED_ENABLE_SET_REG0_ESM0_EDC_CTRL_BUSECC_ENABLE);

    /* Config the ESM Instance for control */
    SDL_ESM_SAFETYAGGR_configECCVectESMInst(SDL_ESMSAFETYAGG_BASE,
                                           SDL_ESM_CPU1_INST_ESM);

    /* Inject the group number for the error enabling */
    SDL_EDC_injectErr1GroupNum(SDL_ESMSAFETYAGG_BASE, SDL_ESM_EVENT_ESM_PARITY_ERROR_GROUP);
    SDL_EDC_injectBitErr(SDL_ESMSAFETYAGG_BASE, SDL_ESM_EVENT_ESM_PARITY_ERROR_MASK);

    /* Set the EDC control register */
    SDL_EDC_setControlReg(SDL_ESMSAFETYAGG_BASE, setEDCControlReg);
}

void SDL_ESM_applicationCallbackFunction(void)
{
    SDL_ESM_SAFETYAGGR_disableAggrIntrErr(SDL_ESMSAFETYAGG_BASE,
                                          SDL_ESM_SAFETYAGGR_INTR_PARITYERR_DIS);

    SDL_ESM_SAFETYAGGR_disableEDCIntr(SDL_ESMSAFETYAGG_BASE,
                                      SDL_ESM_SAFETYAGGR_DED_ENABLE_CLR_REG0_ESM0_EDC_CTRL_BUSECC_CLR);
}

int main(void)
{
    int32_t result;
    Device_init();

    /* Board Initialization */
    Board_init();

    /* Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU. */
    ENINT;
    Interrupt_enableGlobal();

    Interrupt_register(INT_NMI, &INT_ESM_PARITYERR_ISR);

    result = SDL_ESM_init(SDL_ESMCPU1_BASE, &pConfig);

    if (result != SDL_PASS)
    {
        /* print error and quit */
        DebugP_log("Error initializing ESM: result = %d\n", result);
    }
    else
    {
        DebugP_log("\nInit ESM complete \n");
    }

    safetyAggregatorErrorInjection();

    /* Loop Forever and wait for Parity interrupt trigger from Safety Aggregator */

    while(isrFlag == 0U)
    {
    }

    if(isrFlag == 1U)
    {
        DebugP_log("\n Error Flag %d\n MMR Parity Test Passed\n", isrFlag);
    }
    else
    {
        DebugP_log("\n Error Flag %d\n MMR Parity Test Failed\n", isrFlag);
    }
    while(1)
    {
        /* End of the Example */
    }
}

/* ISR for Safety Aggregator Parity Interrupt Output */
__attribute__((interrupt("RTINT"))) void INT_ESM_PARITYERR_ISR(void)
{
    SDL_ESM_IntrStatus intrStatus;

    do
    {
        /* Get ESM interrupt status and try to clear event */
        SDL_ESM_hiInterruptHandler(SDL_ESMCPU1_BASE, &intrStatus);

        if(intrStatus.highestPendPulseEvent == SDL_ESM_EVENT_ESM_PARITY_ERROR)
        {
            isrFlag = 1U;

            /*
            Writing to the Vector Register to set read adrress 0x20 (Error Status 1 register) and set connection with ESM_CPU1
            for read transaction on SVBUS. Read bit should be set at this stage to configure safety aggregator is do read operation
            through svbus on choosen Vector ID instance
            */
            SDL_ESM_SAFETYAGGR_SvBusAddrtoRead(SDL_ESMSAFETYAGG_BASE, SDL_EDC_ERRORSTATUS1);
            SDL_ESM_SAFETYAGGR_triggerSvBusRead(SDL_ESMSAFETYAGG_BASE);

            /* Check output of Error Status 1 read operation at address ESMSAFETYAGG_BASE + 0x10 */
            while (svBusStatus != 0x1U)
            {
                /* Wait till read svbus done bit is set */
                SDL_ESM_SAFETYAGGR_getSvBusStatus(SDL_ESMSAFETYAGG_BASE, &svBusStatus);
            }

            /* Writing to the Vector Register to set svbus connection with ESM_CPU1 for SVBUS write transaction to clear the injected error */
            SDL_ESM_SAFETYAGGR_clearSvBusStatus(SDL_ESMSAFETYAGG_BASE);
            SDL_ESM_SAFETYAGGR_configECCVectESMInst(SDL_ESMSAFETYAGG_BASE, SDL_ESM_CPU1_INST_ESM);
            /* Writing to the Error Status 1 Register to clear the injected uncorrectable error
            this step also clears the DED_STATUS_REG */
            SDL_EDC_setErr1Status(SDL_ESMSAFETYAGG_BASE, 0x00008000U);

            while (dedStatus != 0x0U)
            {
                /* Wait till ded status is not cleared */
                SDL_ESM_SAFETYAGGR_getPendingIntrStatus(SDL_ESMSAFETYAGG_BASE, &dedStatus);
            }

            /* After the Injected error is cleared, write EOI register to acknowledge future parity error interrupts */
            SDL_ESM_SAFETYAGGR_setDEDEOIReg(SDL_ESMSAFETYAGG_BASE);
        }
        else
        {
            /* Unexpected ESM event */
            ESTOP0;
        }

    }while(intrStatus.nextPendPulseEvent != SDL_ESM_NO_EVENT_VALUE);

    SDL_ESM_writeEOI(SDL_ESMCPU1_BASE, SDL_ESM_INTR_TYPE_HIGH_PRIO_ERROR);
}