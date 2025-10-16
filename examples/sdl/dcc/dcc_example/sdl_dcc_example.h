/*
 *  \file     sdl_dcc_example.h
 *
 *  \brief    This file contains DCC Example test code declarations
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

#include "board.h"
#include <sdl_dcc.h>
#include <sdl_esm.h>
#include "kernel/dpl/DebugP.h"

/* ========================================================================== */
/*                     Dependant macros in sdl_dcc_test.c                     */
/* ========================================================================== */

#define APP_DCC_STR                     "\rSDL DCC EXAMPLE TEST"
/**< Example Common display string */
#define APP_DCC_SRC0_MAX_VAL            (0xFFFFFU)
/**< Maximum value that can be held in the COUNT0 register (ref clock) */
#define APP_DCC_SRC0_VALID_MAX_VAL      (0x0FFFFU)
/**< Maximum value that can be held in the VALID0 register (ref clock) */
#define APP_DCC_SRC1_MAX_VAL            (0xFFFFFU)
/**< Maximum value that can be held in the COUNT1 register (test clock) */

#define APP_DCC_TEST_CLOCK_SRC_1_DRIFT  (5U)
/**< Allowed drift in percentage (+/-) */

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/

#define SDL_APP_TEST_NOT_RUN        (-(int32_t) (2))
#define SDL_APP_TEST_FAILED         (-(int32_t) (1))
#define SDL_APP_TEST_PASS           ( (int32_t) (0))

#define DCC_NO_INTERRUPT            (0u)
#define DCC_INTERRUPT               (1u)
#define NUM_USE_CASES               (0x9U)

/*===========================================================================*/
/*                         Declarations                                      */
/*===========================================================================*/

/* Define the test interface */
typedef struct sdlDccTest_s
{
    int32_t  (*testFunction)(void);   /* The code that runs the test */
    char      *name;                  /* The test name */
    int32_t    testStatus;            /* Test Status */
} sdlDccTest_t;

typedef struct {
    char srcStr[32];
    char testStr[32];
    uint32_t dccBase;
    SDL_DCC_Count0ClockSource clk0;
    uint32_t clk0Freq;
    SDL_DCC_Count1ClockSource clk1;
    uint32_t clk1Freq;
    SDL_DCC_Mode mode;
    uint32_t intNum; /* Interrupt Num used in case of single-shot mode */
    uint32_t errorTest; /* indicates if an error should be expected */
} DCC_TEST_UseCase;

/*===========================================================================*/
/*                         Declarations                                      */
/*===========================================================================*/
volatile uint32_t isrFlag = 0U;
/**< Flag used to indicate occurrence of the error interrupt */
volatile uint32_t doneIsrFlag = 0U;
/**< Flag used to indecate occurrence of the completion interrupt */
volatile uint32_t gCurDccBase;

SDL_ESM_Config DCC_Test_esmInitConfig =
{
    .enableBitmap =   {0x00000000U,     /* Group 0 is enabled by default */
                       SDL_ESM_EVENT_DCC1_ERR_MASK,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U,
                       0x00000000U},
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

static DCC_TEST_UseCase DCC_Test_UseCaseArray[NUM_USE_CASES] =
{
    /* Continuous - error generated */
    {
        "XTAL_CLK",
        "SYSPLL_CLK",
        SDL_DCC1_BASE,
        SDL_DCC_COUNT0SRC_XTAL,
        25000, /* 25 MHz for XTAL_CLK */
        SDL_DCC_COUNT1SRC_PLL,
        32, /*  0.032 MHz for SYSPLL_CLK */
        SDL_DCC_MODE_CONTINUOUS,
        0x0,
        0x1
    },
    /* Single Shot - No error */
    {
        "XTAL_CLK",
        "SYSPLL_CLK",
        SDL_DCC1_BASE,
        SDL_DCC_COUNT0SRC_XTAL,
        25000, /* 25 MHz for XTAL_CLK */
        SDL_DCC_COUNT1SRC_PLL,
        200000, /* 200 MHz for SYSPLL_CLK */
        SDL_DCC_MODE_SINGLE_SHOT,
        INT_DCC1,
        0x0
    },
    /* Continuous - no error */
    {
        "XTAL_CLK",
        "SYSPLL_CLK",
        SDL_DCC1_BASE,
        SDL_DCC_COUNT0SRC_XTAL,
        25000, /* 25 MHz for XTAL_CLK */
        SDL_DCC_COUNT1SRC_PLL,
        200000, /* 200 MHz for SYSPLL_CLK */
        SDL_DCC_MODE_CONTINUOUS,
        INT_DCC1,
        0x0
    },
    /* Single Shot - No error */
    {
        "INTOSC1_CLK",
        "CPU1_CLK",
        SDL_DCC1_BASE,
        SDL_DCC_COUNT0SRC_INTOSC1,
        10000, /* 10 MHz for INTOSC1_CLK */
        SDL_DCC_COUNT1SRC_CPU1_CLOCK,
        200000, /* 200 MHz for CPU1_CLK */
        SDL_DCC_MODE_SINGLE_SHOT,
        INT_DCC1,
        0x0
    },
    /* Continuous - error generated */
    {
        "AUX_CLK",
        "EPHY_CLK",
        SDL_DCC1_BASE,
        SDL_DCC_COUNT0SRC_AUXCLKIN,
        20000, /* 20 MHz for AUX_CLK */
        SDL_DCC_COUNT1SRC_ECATPHYCLK,
        32, /* 32 kHz for EPHY_CLK */
        SDL_DCC_MODE_CONTINUOUS,
        0x0,
        0x1
    },
    /* Continuous - no error */
    {
        "XTAL_CLK",
        "CPU1_CLK",
        SDL_DCC1_BASE,
        SDL_DCC_COUNT0SRC_XTAL,
        25000, /* 25 MHz for XTAL_CLK */
        SDL_DCC_COUNT1SRC_CPU1_CLOCK,
        200000, /* 200 kHz for CPU1_CLK */
        SDL_DCC_MODE_CONTINUOUS,
        INT_DCC1,
        0x0
    },
    /* Continuous - no error */
    {
        "XTAL_CLK",
        "SYSPLL_CLK",
        SDL_DCC3_BASE,
        SDL_DCC_COUNT0SRC_XTAL,
        25000, /* 25 MHz for XTAL_CLK */
        SDL_DCC_COUNT1SRC_PLL,
        200000, /* 200 MHz for SYSPLL_CLK */
        SDL_DCC_MODE_CONTINUOUS,
        INT_DCC3,
        0x0
    },
    /* Continuous - error generated */
    {
        "CPU1_CLK",
        "SYSPLL_CLK",
        SDL_DCC1_BASE,
        SDL_DCC_COUNT0SRC_CPU1_CLOCK,
        20000, /* 20 MHz for CPU1_CLK */
        SDL_DCC_COUNT1SRC_PLL,
        20000, /* 20 MHz for SYSPLL_CLK */
        SDL_DCC_MODE_CONTINUOUS,
        0x0,
        0x1
    },
    /* Continuous - no error */
    {
        "AUX_CLK",
        "CPU1_CLK",
        SDL_DCC2_BASE,
        SDL_DCC_COUNT0SRC_AUXCLKIN,
        20000, /* 20 MHz for AUX_CLK */
        SDL_DCC_COUNT1SRC_CPU1_CLOCK,
        200000, /* 200 MHz for CPU1s_CLK */
        SDL_DCC_MODE_CONTINUOUS,
        INT_DCC2,
        0x0
    },
};


/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/

static void SDL_DCCAppGetClkRatio(uint32_t ,
                                  uint32_t ,
                                  uint32_t *,
                                  uint32_t *);

static void SDL_DCCAppSetSeedVals(uint32_t,
                                  uint32_t,
                                  uint32_t,
                                  uint32_t,
                                  uint32_t,
                                  SDL_DCC_Config *);

static void SDL_DCCAppDoneIntrISR(void);
static void SDL_ESMLowPriIntrISR(void);

static void SDL_DCCAppRegisterIntr(uint32_t);
static void SDL_ESMAppRegisterIntr(void);

static void SDL_DCCAppDeRegisterIntr(uint32_t);

void test_sdl_dcc_test_app (void);

static void SDL_DCCAppPrint(char * str);

/**
 * \brief   This function waits infinitely for DCC done interrupt
 *
 * \retval  SDL_PASS on occurrence DCC completion and no error.
 *          SDL_EFAIL otherwise.
 */
static int32_t SDL_DCCAppWaitForCompletion();
