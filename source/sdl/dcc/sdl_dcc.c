/* ###########################################################################
 *
 *  \file     sdl_dcc.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of DCC.
 *            This also contains some related macros.
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

#include "sdl_dcc.h"
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static bool SDL_DCC_isBaseValid(uint32_t dccBase)
{
    return(
           ((dccBase & SDL_BASE_ADDR_MASK) == SDL_DCC1_BASE_FRAME(0U)) ||
           ((dccBase & SDL_BASE_ADDR_MASK) == SDL_DCC2_BASE_FRAME(0U)) ||
           ((dccBase & SDL_BASE_ADDR_MASK) == SDL_DCC3_BASE_FRAME(0U))
          );
}

/********************************************************************************************************
*   API for configuring the DCC module
*********************************************************************************************************/

/**
 *  Design: C2000DL-833
 */

int32_t SDL_DCC_configure(uint32_t dccBase, const SDL_DCC_Config *pConfig)
{
    int32_t sdlResult = SDL_EFAIL;
    uint32_t clksrcVal;

    if((SDL_DCC_isBaseValid(dccBase)) && (pConfig != NULL))
    {
        if ((pConfig->clk0Seed      <= DCC_SRC0_COUNT_MAX) &&
            (pConfig->clk0ValidSeed <= DCC_SRC0_VALID_MAX) &&
            (pConfig->clk1Seed      <= DCC_SRC1_COUNT_MAX))
        {

            /* Configure DCC mode of operation */
            HW_WR_FIELD32(dccBase + SDL_DCC_DCCGCTRL, DCC_DCCGCTRL_SINGLESHOT,
                        pConfig->mode);

            /* Select clock source for COUNT0 */
            clksrcVal = (((uint32_t)pConfig->clk0Src & DCC_DCCCLKSRC0_CLKSRC0_MASK)) |
                    (((uint32_t)DCC_DCCCLKSRC0_KEY_ENABLE << DCC_DCCCLKSRC0_KEY_SHIFT));

            HW_WR_REG32(dccBase + SDL_DCC_DCCCLKSRC0, clksrcVal);


            /* Select clock source for COUNT1*/
            /* Enable clock source selection for COUNT1 */
            clksrcVal = ((((uint32_t)pConfig->clk1Src % 16U) << DCC_DCCCLKSRC1_CLKSRC_SHIFT) |
                        ((uint32_t)DCC_DCCCLKSRC1_KEY_ENABLE << DCC_DCCCLKSRC1_KEY_SHIFT));

            HW_WR_REG32(dccBase + SDL_DCC_DCCCLKSRC1, clksrcVal);

            /* Configure COUNT0 preload/seed value */
            HW_WR_FIELD32(dccBase + SDL_DCC_DCCCNTSEED0, DCC_DCCCNT0_COUNT0,
                        pConfig->clk0Seed);

            if(pConfig->clk0ValidSeed < DCC_SRC0_VALID_MIN)
            {
                /* Configure VALID0 preload/seed value */
                HW_WR_FIELD32(dccBase + SDL_DCC_DCCVALIDSEED0, DCC_DCCVALID0_VALID0,
                            DCC_SRC0_VALID_MIN);
            }
            else
            {
                /* Configure VALID0 preload/seed value */
                HW_WR_FIELD32(dccBase + SDL_DCC_DCCVALIDSEED0, DCC_DCCVALID0_VALID0,
                            pConfig->clk0ValidSeed);
            }
            /* Configure COUNT1 preload/seed value */
            HW_WR_FIELD32(dccBase + SDL_DCC_DCCCNTSEED1, DCC_DCCCNT1_COUNT1,
                        pConfig->clk1Seed);
            sdlResult = SDL_PASS;
        }
        else
        {
            sdlResult = SDL_EBADARGS;
        }
    }
    else
    {
        sdlResult = SDL_EBADARGS;
    }
    return sdlResult;
}

/*******************************************************************************
 *  API for verify the configuration of DCC module
*********************************************************************************************************/

/**
 *  Design: C2000DL-835
 */
int32_t
SDL_DCC_verifyConfig(uint32_t dccBase, const SDL_DCC_Config *pConfig)
{
    uint32_t mode_chk;
    uint32_t clk0Src_chk, clk1Src_chk;
    uint32_t clk0Seed_chk, clk0ValidSeed_chk, clk1Seed_chk;
    int32_t  sdlResult;


    if((SDL_DCC_isBaseValid(dccBase)) && (pConfig != NULL) )
    {
        /* Get the configured mode of operation for DCC module */
        mode_chk = HW_RD_FIELD32(dccBase + SDL_DCC_DCCGCTRL,
                                        DCC_DCCGCTRL_SINGLESHOT);

        /* Get the clock source for COUNT0 */
        clk0Src_chk = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCLKSRC0,
                                                DCC_DCCCLKSRC0_CLKSRC0);

        /* Get the clock source for COUNT1 */
        clk1Src_chk = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCLKSRC1,
                                                    DCC_DCCCLKSRC1_CLKSRC);

        /* Get the current value of COUNT0 */
        clk0Seed_chk = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCNTSEED0,
                                                        DCC_DCCCNT0_COUNT0);

        /* Get the current value of VALID0 */
        clk0ValidSeed_chk = HW_RD_FIELD32(dccBase + SDL_DCC_DCCVALIDSEED0,
                                                                DCC_DCCVALID0_VALID0);

        /* Get the current value of COUNT1 */
        clk1Seed_chk = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCNTSEED1,
                                                    DCC_DCCCNT1_COUNT1);

        if( (mode_chk == (uint32_t)pConfig->mode) && (clk0Src_chk == (uint32_t)pConfig->clk0Src) && (clk1Src_chk == (uint32_t)pConfig->clk1Src) \
            && (clk0Seed_chk == pConfig->clk0Seed) && (clk0ValidSeed_chk == pConfig->clk0ValidSeed) && (clk1Seed_chk == pConfig->clk1Seed) )
        {
            sdlResult = SDL_PASS;
        }
        else
        {
            sdlResult = SDL_EFAIL;
        }
    }
    else
    {
        sdlResult = SDL_EBADARGS;
    }

    return sdlResult;
}

/********************************************************************************************************
*   API for Enabling the DCC module
*********************************************************************************************************/

/**
 *  Design: C2000DL-836
 */
int32_t SDL_DCC_enable(uint32_t dccBase)
{
    int32_t sdlResult;

    if(SDL_DCC_isBaseValid(dccBase))
    {
        /* Enable DCC */
        HW_WR_FIELD32(dccBase + SDL_DCC_DCCGCTRL, DCC_DCCGCTRL_DCCENA,
                      DCC_DCCGCTRL_DCCENA_ENABLE);
        sdlResult = SDL_PASS;
    }
    else
    {
        sdlResult = SDL_EBADARGS;
    }

    return sdlResult;
}

/********************************************************************************************************
*   API for Disabling the DCC module
*********************************************************************************************************/

/**
 *  Design: C2000DL-837
 */
int32_t SDL_DCC_disable(uint32_t dccBase)
{
    int32_t sdlResult;

    if(SDL_DCC_isBaseValid(dccBase))
    {
        /* Disable DCC */
        HW_WR_FIELD32(dccBase + SDL_DCC_DCCGCTRL, DCC_DCCGCTRL_DCCENA,
                      DCC_DCCGCTRL_DCCENA_DISABLE);

        sdlResult = SDL_PASS;
    }
    else
    {
        sdlResult = SDL_EBADARGS;
    }

    return sdlResult;
}

/********************************************************************************************************
*   API for getting the status of DCC
*********************************************************************************************************/

/**
 *  Design: C2000DL-838
 */
int32_t SDL_DCC_getStatus(uint32_t dccBase, SDL_DCC_Status *pStatus)
{
    int32_t sdlResult, intrStatus;

    if((SDL_DCC_isBaseValid(dccBase)) && (pStatus != NULL))
    {
        /* Checking if DONE Interrupt occured or not */
        /* TRUE = Interrupt pending, FALSE = INTERRUPT not pending */
        intrStatus = (int32_t)HW_RD_FIELD32(dccBase + SDL_DCC_DCCSTAT, DCC_DCCSTAT_DONEFLG);
        if(intrStatus !=  (int32_t)0U)
        {
            pStatus->doneIntr = TRUE;
        }
        else
        {
            pStatus->doneIntr = FALSE;
        }

        /* Checking if ERROR Interrupt occured or not */
        /* TRUE = Interrupt pending, FALSE = INTERRUPT not pending */
        intrStatus = (int32_t)HW_RD_FIELD32(dccBase + SDL_DCC_DCCSTAT, DCC_DCCSTAT_ERRFLG);
        if(intrStatus != (int32_t)0U)
        {
            pStatus->errIntr = TRUE;
        }
        else
        {
            pStatus->errIntr = FALSE;
        }

        /* Getting Current configuration of DCC */
        /* Get the configured mode of operation for DCC module */
        pStatus->config.mode          = HW_RD_FIELD32(dccBase + SDL_DCC_DCCGCTRL,
                                        DCC_DCCGCTRL_SINGLESHOT);
        /* Get the clock source for COUNT0 */
        pStatus->config.clk0Src       = (HW_RD_FIELD32(dccBase + SDL_DCC_DCCCLKSRC0,
                                                DCC_DCCCLKSRC0_CLKSRC0));
        /* Get the clock source for COUNT1 */
        pStatus->config.clk1Src          = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCLKSRC1,
                                                    DCC_DCCCLKSRC1_CLKSRC);
        /* Get the current value of COUNT0 */
        pStatus->config.clk0Seed      = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCNTSEED0,
                                                        DCC_DCCCNT0_COUNT0);
        /* Get the current value of VALID0 */
        pStatus->config.clk0ValidSeed = HW_RD_FIELD32(dccBase + SDL_DCC_DCCVALIDSEED0,
                                                                DCC_DCCVALID0_VALID0);
        /* Get the current value of COUNT1 */
        pStatus->config.clk1Seed      = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCNTSEED1,
                                                    DCC_DCCCNT1_COUNT1);


        /* Current values of counters  */
        /* Get the current value of COUNT0 */
        pStatus->clk0Cnt = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCNT0,
                                                        DCC_DCCCNT0_COUNT0);

        /* Get the current value of VALID0 */
        pStatus->clk0Valid = HW_RD_FIELD32(dccBase + SDL_DCC_DCCVALID0,
                                                                DCC_DCCVALID0_VALID0);

        /* Get the current value of COUNT1 */
        pStatus->clk1Cnt = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCNT1,
                                                    DCC_DCCCNT1_COUNT1);

        sdlResult = SDL_PASS;
    }
    else
    {
        sdlResult = SDL_EBADARGS;
    }

    return sdlResult;
}

/********************************************************************************************************
*   API for Enabling the Error and Done Interrupts
*********************************************************************************************************/

/**
 *  Design: C2000DL-839
 */
int32_t SDL_DCC_enableIntr(uint32_t dccBase, SDL_DCC_IntrType intr)
{
    int32_t sdlResult = SDL_EFAIL;

    if(SDL_DCC_isBaseValid(dccBase))
    {
        switch (intr)
        {
            case SDL_DCC_INTERRUPT_ERR:
                /* Enable ERROR interrupt */
                HW_WR_FIELD32(dccBase + SDL_DCC_DCCGCTRL, DCC_DCCGCTRL_ERRENA,
                            DCC_DCCGCTRL_ERRENA_ENABLE);
                sdlResult = SDL_PASS;
                break;
            case SDL_DCC_INTERRUPT_DONE:
                /* Enable DONE interrupt(only for single shot mode) */
                HW_WR_FIELD32(dccBase + SDL_DCC_DCCGCTRL, DCC_DCCGCTRL_DONEENA,
                            DCC_DCCGCTRL_DONEENA_ENABLE);
                sdlResult = SDL_PASS;
                break;
            default:
                sdlResult = SDL_EFAIL;
                break;
        }
    }
    else
    {
        sdlResult = SDL_EBADARGS;
    }

    return sdlResult;

}

/********************************************************************************************************
*   API for clearing the Interrupt
*********************************************************************************************************/

/**
 *  Design: C2000DL-840
 */
int32_t SDL_DCC_clearIntr(uint32_t dccBase, SDL_DCC_IntrType intr)
{
    int32_t sdlResult = SDL_EFAIL;

    if(SDL_DCC_isBaseValid(dccBase))
    {

        switch (intr)
        {
            case SDL_DCC_INTERRUPT_ERR:
                /* Disable ERROR interrupt */
                HW_WR_REG32(dccBase + SDL_DCC_DCCSTAT,
                            DCC_DCCSTAT_ERRFLG_DISABLE << DCC_DCCSTAT_ERRFLG_SHIFT);
                HW_WR_FIELD32(dccBase + SDL_DCC_DCCGCTRL, DCC_DCCGCTRL_ERRENA,
                            DCC_DCCGCTRL_ERRENA_DISABLE);
                sdlResult = SDL_PASS;
                break;
            case SDL_DCC_INTERRUPT_DONE:
                /* Disable DONE interrupt(only for single shot mode) */
                HW_WR_REG32(dccBase + SDL_DCC_DCCSTAT,
                            DCC_DCCSTAT_DONEFLG_DISABLE << DCC_DCCSTAT_DONEFLG_SHIFT);
                HW_WR_FIELD32(dccBase + SDL_DCC_DCCGCTRL, DCC_DCCGCTRL_DONEENA,
                            DCC_DCCGCTRL_DONEENA_DISABLE);
                sdlResult = SDL_PASS;
                break;
            default:
                sdlResult = SDL_EBADARGS;
                break;
        }
    }
    else
    {
        sdlResult = SDL_EBADARGS;
    }
    return sdlResult;
}

/********************************************************************************************************
*   API for reading the static registers values
*********************************************************************************************************/

/**
 *  Design: C2000DL-841
 */
int32_t SDL_DCC_getStaticRegs(uint32_t dccBase, SDL_DCC_StaticRegs *pStaticRegs)
{
    int32_t  sdlResult;


    if((SDL_DCC_isBaseValid(dccBase)) && (pStaticRegs != NULL))
    {

        /* Get the complete DCC_REV register value */
        pStaticRegs->DCC_REV = HW_RD_REG32_RAW(dccBase + SDL_DCC_DCCREV);

        /* Get the clock source for COUNT0 */
        pStaticRegs->DCC_CLKSRC0 = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCLKSRC0,
                                                DCC_DCCCLKSRC0_CLKSRC0);

        /* Get the clock source for COUNT1 */
        pStaticRegs->DCC_CLKSRC1 = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCLKSRC1,
                                                    DCC_DCCCLKSRC1_CLKSRC);

        /* Get the current value of COUNT0 */
        pStaticRegs->DCC_CNTSEED0 = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCNTSEED0,
                                                        DCC_DCCCNT0_COUNT0);

        /* Get the current value of VALID0 */
        pStaticRegs->DCC_VALIDSEED0 = HW_RD_FIELD32(dccBase + SDL_DCC_DCCVALIDSEED0,
                                                                DCC_DCCVALID0_VALID0);

        /* Get the current value of COUNT1 */
        pStaticRegs->DCC_CNTSEED1 = HW_RD_FIELD32(dccBase + SDL_DCC_DCCCNTSEED1,
                                                    DCC_DCCCNT1_COUNT1);

        sdlResult = SDL_PASS;
    }
    else
    {
        sdlResult = SDL_EBADARGS;
    }

    return sdlResult;

}

