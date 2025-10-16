/*
 *  \file     sdl_dcc_example.c
 *
 *  \brief    This file contains DCC Example test code.
 *
 *  \details  DCC tests
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
 */

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include "sdl_dcc_example.h"
#include "board.h"

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

static void SDL_DCCAppPrint(char * str)
{
    DebugP_log(str);
}

static void SDL_DCCAppGetClkRatio(uint32_t  refClkFreq,
                                  uint32_t  testClkFreq,
                                  uint32_t *refClkRatioNum,
                                  uint32_t *testClkRatioNum)
{
    uint32_t loopCnt, hcf = 1U;

    for (loopCnt = 1;
         (loopCnt <= refClkFreq) && (loopCnt <= testClkFreq);
         loopCnt++)
    {
        if ((refClkFreq % loopCnt == 0) && (testClkFreq % loopCnt == 0))
        {
            hcf = loopCnt;
        }
    }
    *refClkRatioNum  = (refClkFreq / hcf);
    *testClkRatioNum = (testClkFreq / hcf);
}

static void SDL_DCCAppSetSeedVals(uint32_t       refClkFreq,
                                  uint32_t       testClkFreq,
                                  uint32_t       refClkRatioNum,
                                  uint32_t       testClkRatioNum,
                                  uint32_t       drfitPer,
                                  SDL_DCC_Config *configParams)
{
    uint32_t maxFreqKHz, maxCntLimit;
    uint32_t maxRefCnt, minRefCnt;
    uint64_t mulVar;

    /* Find maximum frequency between test and reference clock */
    if (refClkFreq > testClkFreq)
    {
        maxFreqKHz  = refClkFreq;
        maxCntLimit = APP_DCC_SRC0_MAX_VAL;
    }
    else
    {
        maxFreqKHz  = testClkFreq;
        maxCntLimit = APP_DCC_SRC1_MAX_VAL;
    }
    /* Calculate seed values for 0% drift */
    if (maxFreqKHz == refClkFreq)
    {
        configParams->clk0Seed = maxCntLimit / refClkRatioNum;
        configParams->clk0Seed = configParams->clk0Seed * refClkRatioNum;
        mulVar = ((uint64_t) (configParams->clk0Seed) *
                  (uint32_t) (testClkRatioNum));
        configParams->clk1Seed   = (uint32_t) (mulVar / refClkRatioNum);
        configParams->clk0ValidSeed = refClkRatioNum;
    }
    else
    {
        configParams->clk1Seed = maxCntLimit / testClkRatioNum;
        configParams->clk1Seed = configParams->clk1Seed * testClkRatioNum;
        mulVar = ((uint64_t) (configParams->clk1Seed) *
                  (uint32_t) (refClkRatioNum));
        configParams->clk0Seed   = (uint32_t) (mulVar / testClkRatioNum);
        configParams->clk0ValidSeed = 1U;
    }
    /* Applying allowed drift */
    if (((APP_DCC_SRC0_MAX_VAL + APP_DCC_SRC0_VALID_MAX_VAL) <
         (configParams->clk0Seed * (100U + drfitPer) / 100U)))
    {
        /* Seed values with drift exceeds maximum range */
        SDL_DCCAppPrint(APP_DCC_STR ": Seed values with drift exceeds"
                        " allowed range\n");
        SDL_DCCAppPrint(APP_DCC_STR ": Application will run with 0% "
                        " allowed drift\n");
    }
    else if (100U < drfitPer)
    {
        /* Error percentage is greater than 100 */
        SDL_DCCAppPrint(APP_DCC_STR ": Warning Wrong drift %,Not applying drift\n");
        SDL_DCCAppPrint(APP_DCC_STR ": Application will run with 0% drift\n");
    }
    else
    {
        maxRefCnt = (configParams->clk0Seed * (100U + drfitPer) / 100U);
        minRefCnt = (configParams->clk0Seed * (100U - drfitPer) / 100U);
        if (APP_DCC_SRC0_VALID_MAX_VAL < (maxRefCnt - minRefCnt))
        {
            SDL_DCCAppPrint(APP_DCC_STR ": Warning Seed value for valid count "
                        "exceeds allowed range.\n");
            SDL_DCCAppPrint(APP_DCC_STR ": Application will run with 0 allowed"
                        " drift.\n");
        }
        else
        {
            if (maxRefCnt == minRefCnt)
            {
                configParams->clk0ValidSeed = 1U;
            }
            else
            {
                configParams->clk0Seed   = minRefCnt;
                configParams->clk0ValidSeed = (maxRefCnt - minRefCnt);
            }
        }
    }
    SDL_DCCAppPrint(APP_DCC_STR ": Seed values calculation done.\n");
}

__attribute__((interrupt("INT")))
static void SDL_DCCAppDoneIntrISR(void)
{
    SDL_DCC_Status dccStatus;

    SDL_DCC_getStatus(gCurDccBase, &dccStatus);

    if (dccStatus.doneIntr == TRUE)
    {
        SDL_DCC_clearIntr(gCurDccBase, SDL_DCC_INTERRUPT_DONE);
        doneIsrFlag  = DCC_INTERRUPT;
    }
}

__attribute__((interrupt("INT")))
static void SDL_ESMLowPriIntrISR(void)
{
    SDL_ESM_IntrStatus intrStatus;

    do
    {
        /* Get ESM interrupt status and try to clear event */
        SDL_ESM_loInterruptHandler(SDL_ESMCPU1_BASE, &intrStatus);

        if(intrStatus.highestPendPulseEvent == SDL_ESM_EVENT_DCC1_ERR)
        {
            /* Clear DCC event */
            SDL_DCC_clearIntr(gCurDccBase, SDL_DCC_INTERRUPT_ERR);

            isrFlag = DCC_INTERRUPT;
        }
        else
        {
            /* Unexpected ESM event */
            ESTOP0;
        }

    }while(intrStatus.nextPendPulseEvent != SDL_ESM_NO_EVENT_VALUE);

    SDL_ESM_writeEOI(SDL_ESMCPU1_BASE, SDL_ESM_INTR_TYPE_LOW_PRIO_ERROR);
}

static void SDL_DCCAppRegisterIntr(uint32_t uc)
{
    Interrupt_Config intrParams;

    intrParams.enable      = true;
    intrParams.handler     = &SDL_DCCAppDoneIntrISR;
    intrParams.priority    = 30;
    intrParams.linkOwner   = SSU_LINK2;
    intrParams.contextID   = INTERRUPT_CONTEXT_AGNOSTIC;
    intrParams.apiLinkID   = SSU_API_DISABLE;

    Interrupt_configChannel(DCC_Test_UseCaseArray[uc].intNum, intrParams);
}

static void SDL_ESMAppRegisterIntr(void)
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

static void SDL_DCCAppDeRegisterIntr(uint32_t uc)
{
    Interrupt_unregister(DCC_Test_UseCaseArray[uc].intNum);
}

static int32_t SDL_DCCAppWaitForCompletion(void)
{
    int32_t retVal;

    /* Wait for completion interrupt / or error flag*/
    while ((0U == doneIsrFlag) && (0U == isrFlag));

    /* Ensure no error */
    if (isrFlag == DCC_INTERRUPT)
    {
        retVal = SDL_EFAIL;
    }
    else
    {
        retVal = SDL_PASS;
    }
    return (retVal);
}

/*===========================================================================*/
/*                         Function definition                               */
/*===========================================================================*/

void test_sdl_dcc_test_app (void)
{
    /* Declarations of variables */
    int32_t  retVal,i;
    uint32_t clk0Freq, clk1Freq, refClkRatioNum, testClkRatioNum;
    SDL_DCC_Config configParams;
    DebugP_log("\n DCC Example Test Application\r\n");

    /* Initialize MAIN DCC module */
    retVal = SDL_ESM_init(SDL_ESMCPU1_BASE, &DCC_Test_esmInitConfig);

    /* Register the SDL_ESM interrupt handler */
    SDL_ESMAppRegisterIntr();

    if (retVal == SDL_PASS)
    {

        DebugP_log("\nDCC_Test_init: Init ESM complete \r\n");
    }
    else
    {
        /* print error and quit */
        DebugP_log("DCC_Test_init: Error initializing ESM: result = %d\r\n", retVal);

    }

    for (i = 0; i < NUM_USE_CASES; i++)
    {

        DebugP_log("\nUSECASE: %d\r\n", i);

        DebugP_log("Source clock: %s \r\n", DCC_Test_UseCaseArray[i].srcStr);
        DebugP_log("Test clock: %s\r\n", DCC_Test_UseCaseArray[i].testStr);

        gCurDccBase = DCC_Test_UseCaseArray[i].dccBase;
        clk0Freq = DCC_Test_UseCaseArray[i].clk0Freq;
        clk1Freq = DCC_Test_UseCaseArray[i].clk1Freq;

        if (DCC_Test_UseCaseArray[i].errorTest == 0x1)
        {
            /* Deliberately change the Reference Clock to 2 times to
             * introduce the error in the clock ratio
             */
            clk1Freq *= 2;
        }

        if (SDL_PASS == retVal)
        {
            /* Get clock ratio */
            SDL_DCCAppGetClkRatio(clk0Freq,
                                  clk1Freq,
                                  &refClkRatioNum,
                                  &testClkRatioNum);

            configParams.mode    = DCC_Test_UseCaseArray[i].mode;
            configParams.clk0Src = DCC_Test_UseCaseArray[i].clk0;
            configParams.clk1Src = DCC_Test_UseCaseArray[i].clk1;

            /* Get the seed values for given clock selections and allowed drift */
            SDL_DCCAppSetSeedVals(clk0Freq,
                                  clk1Freq,
                                  refClkRatioNum,
                                  testClkRatioNum,
                                  APP_DCC_TEST_CLOCK_SRC_1_DRIFT,
                                  &configParams);

            retVal = SDL_DCC_configure(DCC_Test_UseCaseArray[i].dccBase, &configParams);

            if (SDL_PASS == retVal)
            {
                retVal = SDL_DCC_verifyConfig(DCC_Test_UseCaseArray[i].dccBase, &configParams);
            }
            else
            {
                retVal = SDL_EFAIL;
            }

            if (retVal == SDL_PASS)
            {
                /* Enable ERROR interrupt */
                SDL_DCC_enableIntr(DCC_Test_UseCaseArray[i].dccBase, SDL_DCC_INTERRUPT_ERR);

                /* Check for single-shot mode and enable interrupt for Done notification
                 * then wait for completion.
                 */
                if (DCC_Test_UseCaseArray[i].mode != SDL_DCC_MODE_CONTINUOUS)
                {
                    SDL_DCCAppRegisterIntr(i);

                    /* Enable DONE interrupt(only for single shot mode) */
                    SDL_DCC_enableIntr(DCC_Test_UseCaseArray[i].dccBase, SDL_DCC_INTERRUPT_DONE);

                    SDL_DCC_enable(DCC_Test_UseCaseArray[i].dccBase);

                    if (SDL_PASS == SDL_DCCAppWaitForCompletion())
                    {
                        SDL_DCCAppPrint(APP_DCC_STR ": DCC Generated completion interrupt \r\n");
                        SDL_DCCAppPrint(APP_DCC_STR ": No Clock Drift was observed \r\n");
                    }
                    else
                    {
                        SDL_DCCAppPrint(APP_DCC_STR ": Error : DCC Generated error interrupt\r\n");
                        SDL_DCCAppPrint(APP_DCC_STR ": Error interrupt is not expected \r\n");
                        retVal = SDL_EFAIL;
                    }

                    SDL_DCCAppDeRegisterIntr(i);
                    isrFlag = DCC_NO_INTERRUPT;
                    doneIsrFlag = 0x0;
                }

                else
                {
                    if (DCC_Test_UseCaseArray[i].errorTest == 0x1)
                    {
                        SDL_DCCAppPrint(APP_DCC_STR ": Enabling DCC and waiting for "
                                        "Error interrupt \r\n");
                    }
                    else
                    {
                        SDL_DCCAppPrint(APP_DCC_STR ": Enabling DCC and running for some time \r\n");
                    }

                    SDL_DCC_enable(DCC_Test_UseCaseArray[i].dccBase);

                    /* Wait for error notification */

                    volatile int32_t j = 0;
                    /* Wait for the ESM interrupt to report the error */
                    do {
                        j++;
                        if (j > 0x0FFFFFF)
                        {
                            /* Timeout for the wait */
                            break;
                        }

                    } while (isrFlag == DCC_NO_INTERRUPT);

                    if (isrFlag == DCC_INTERRUPT)
                    {
                        DebugP_log(APP_DCC_STR ": DCC Generated Error interrupt \r\n");
                        DebugP_log(APP_DCC_STR ": Indicating clock drift/change \r\n");
                        if (DCC_Test_UseCaseArray[i].errorTest == 0x0)
                        {
                            DebugP_log(APP_DCC_STR ":    Error Event was not expected \r\n");
                            retVal = SDL_EFAIL;
                        }
                    }
                    else
                    {
                        if (DCC_Test_UseCaseArray[i].errorTest == 0x1)
                        {
                            DebugP_log(APP_DCC_STR ": Could not generate Error interrupt \r\n");
                            retVal = SDL_EFAIL;
                        }
                    }
                    isrFlag = DCC_NO_INTERRUPT;
                }
                SDL_DCC_disable(DCC_Test_UseCaseArray[i].dccBase);
            }
        }
        else
        {
             DebugP_log(APP_DCC_STR ": Error : Could not derive clock "
                        "frequency!!!\r\n");
        }

        if (retVal != SDL_PASS)
        {
            DebugP_log("UC-%d Failed\r\n", i);
            break;
        }
        else
        {
            DebugP_log("UC-%d Completed Successfully\r\n", i);
        }
    }

    if (retVal == SDL_PASS)
    {
        DebugP_log("\n All tests have passed.\r\n");
    }
    else
    {
        DebugP_log("\n Few/all tests Failed \r\n");
    }
}

int main(void){
    /*
     * Initialize device clock, peripheral clocks and interrupts
     */
    Device_init();

    /*
     * Board Initialization
     */
    Board_init();

    /*
     * Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
     */
    ENINT;
    Interrupt_enableGlobal();

    test_sdl_dcc_test_app();

    while(1){}
}

/* Nothing past this point */