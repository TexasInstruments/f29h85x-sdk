//###########################################################################
//
// FILE:   xbar.c
//
// TITLE:  C29x X-BAR driver.
//
//###########################################################################
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//###########################################################################

#include "xbar.h"

//*****************************************************************************
//
// XBAR_selectOutputXbarInputSource
//
//*****************************************************************************
void
XBAR_selectOutputXbarInputSource(uint32_t base, XBAR_OutputNum output,
                           XBAR_OutputXbarInputSource source)
{
    ASSERT(base == OUTPUTXBAR_BASE);

    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(base + OUTPUT_XBAR_O_OUTPUTXBARG0SEL((uint32_t)output) +
                                (group * XBAR_XBARGSEL_STEP)) |= inputMask;
}

//*****************************************************************************
//
// XBAR_deselectOutputXbarInputSource
//
//*****************************************************************************
void
XBAR_deselectOutputXbarInputSource(uint32_t base, XBAR_OutputNum output,
                           XBAR_OutputXbarInputSource source)
{
    ASSERT(base == OUTPUTXBAR_BASE);

    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(base + OUTPUT_XBAR_O_OUTPUTXBARG0SEL((uint32_t)output) +
                                (group * XBAR_XBARGSEL_STEP)) &= ~inputMask;
}

//*****************************************************************************
//
// XBAR_clearOutputXbarSourceSelection
//
//*****************************************************************************
void
XBAR_clearOutputXbarSourceSelection(uint32_t base, XBAR_OutputNum output)
{
    uint32_t i;

    ASSERT(base == OUTPUTXBAR_BASE);

    for (i = 0U; i < 10U; i++)
    {
        HWREG(base + OUTPUT_XBAR_O_OUTPUTXBARG0SEL((uint32_t)output) +
                                (i * XBAR_XBARGSEL_STEP)) &= 0U;
    }
}

//*****************************************************************************
//
// XBAR_selectEpwmXbarInputSource
//
//*****************************************************************************
void
XBAR_selectEpwmXbarInputSource(XBAR_TripNum trip,
                           XBAR_EpwmXbarInputSource source)
{
    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(EPWMXBAR_BASE + EPWM_XBAR_O_PWMXBARG0SEL((uint32_t)trip) +
                                (group * XBAR_XBARGSEL_STEP)) |= inputMask;
}

//*****************************************************************************
//
// XBAR_deselectEpwmXbarInputSource
//
//*****************************************************************************
void
XBAR_deselectEpwmXbarInputSource(XBAR_TripNum trip,
                           XBAR_EpwmXbarInputSource source)
{
    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(EPWMXBAR_BASE + EPWM_XBAR_O_PWMXBARG0SEL((uint32_t)trip) +
                                (group * XBAR_XBARGSEL_STEP)) &= ~inputMask;
}

//*****************************************************************************
//
// XBAR_clearEpwmXbarSourceSelection
//
//*****************************************************************************
void
XBAR_clearEpwmXbarSourceSelection(XBAR_TripNum output)
{
    uint32_t i;

    for (i = 0U; i < 10U; i++)
    {
        HWREG(EPWMXBAR_BASE + EPWM_XBAR_O_PWMXBARG0SEL((uint32_t)output)
                                 + (i * XBAR_XBARGSEL_STEP)) &= 0U;
    }
}

//*****************************************************************************
//
// XBAR_selectClbXbarInputSource
//
//*****************************************************************************
void
XBAR_selectClbXbarInputSource(XBAR_AuxSigNum auxSignal,
                           XBAR_ClbXbarInputSource source)
{
    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(CLBXBAR_BASE + CLB_XBAR_O_CLBXBARG0SEL((uint32_t)auxSignal) +
                                 (group * XBAR_XBARGSEL_STEP)) |= inputMask;
}

//*****************************************************************************
//
// XBAR_deselectClbXbarInputSource
//
//*****************************************************************************
void
XBAR_deselectClbXbarInputSource(XBAR_AuxSigNum auxSignal,
                           XBAR_ClbXbarInputSource source)
{
    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(CLBXBAR_BASE + CLB_XBAR_O_CLBXBARG0SEL((uint32_t)auxSignal) +
                                 (group * XBAR_XBARGSEL_STEP)) &= ~inputMask;
}

//*****************************************************************************
//
// XBAR_clearClbXbarSourceSelection
//
//*****************************************************************************
void
XBAR_clearClbXbarSourceSelection(XBAR_AuxSigNum output)
{
    uint32_t i;

    for (i = 0U; i < 8U; i++)
    {
        HWREG(CLBXBAR_BASE + CLB_XBAR_O_CLBXBARG0SEL((uint32_t)output)
                                 + (i * XBAR_XBARGSEL_STEP)) &= 0U;
    }
}

//*****************************************************************************
//
// XBAR_selectMindbXbarInputSource
//
//*****************************************************************************
void
XBAR_selectMindbXbarInputSource(XBAR_OutputNum output,
                           XBAR_MindbXbarInputSource source)
{
    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(MDLXBAR_BASE + MDL_XBAR_O_MDLXBARG0SEL((uint32_t)output) +
                                 (group * XBAR_XBARGSEL_STEP)) |= inputMask;
}

//*****************************************************************************
//
// XBAR_deselectMindbXbarInputSource
//
//*****************************************************************************
void
XBAR_deselectMindbXbarInputSource(XBAR_OutputNum output,
                           XBAR_MindbXbarInputSource source)
{
    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(MDLXBAR_BASE + MDL_XBAR_O_MDLXBARG0SEL((uint32_t)output) +
                                 (group * XBAR_XBARGSEL_STEP)) &= ~inputMask;
}

//*****************************************************************************
//
// XBAR_clearMindbXbarSourceSelection
//
//*****************************************************************************
void
XBAR_clearMindbXbarSourceSelection(XBAR_OutputNum output)
{
    uint32_t i;

    for (i = 0U; i < 3U; i++)
    {
        HWREG(MDLXBAR_BASE + MDL_XBAR_O_MDLXBARG0SEL((uint32_t)output)
                                 + (i * XBAR_XBARGSEL_STEP)) &= 0U;
    }
}

//*****************************************************************************
//
// XBAR_selectIclXbarInputSource
//
//*****************************************************************************
void
XBAR_selectIclXbarInputSource(XBAR_OutputNum output,
                           XBAR_IclXbarInputSource source)
{
    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(ICLXBAR_BASE + ICL_XBAR_O_ICLXBARG0SEL((uint32_t)output) +
                                 (group * XBAR_XBARGSEL_STEP)) |= inputMask;
}

//*****************************************************************************
//
// XBAR_deselectIclXbarInputSource
//
//*****************************************************************************
void
XBAR_deselectIclXbarInputSource(XBAR_OutputNum output,
                           XBAR_IclXbarInputSource source)
{
    uint32_t group;
    uint32_t inputMask;

    group = ((uint32_t)source & XBAR_INPUT_REG_M) >> XBAR_INPUT_REG_S;

    inputMask = (uint32_t)1U << ((uint32_t)source & XBAR_INPUT_INPUT_M);

    HWREG(ICLXBAR_BASE + ICL_XBAR_O_ICLXBARG0SEL((uint32_t)output) +
                                 (group * XBAR_XBARGSEL_STEP)) &= ~inputMask;
}

//*****************************************************************************
//
// XBAR_clearIclXbarSourceSelection
//
//*****************************************************************************
void
XBAR_clearIclXbarSourceSelection(XBAR_OutputNum output)
{
    uint32_t i;

    for (i = 0U; i < 3U; i++)
    {
        HWREG(ICLXBAR_BASE + ICL_XBAR_O_ICLXBARG0SEL((uint32_t)output)
                                 + (i * XBAR_XBARGSEL_STEP)) &= 0U;
    }
}

//*****************************************************************************
//
// XBAR_getInputFlagStatus
//
//*****************************************************************************
bool
XBAR_getInputFlagStatus(XBAR_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    //
    // Determine flag register offset.
    //
    switch(((uint32_t)inputFlag & XBAR_INPUT_REG_M))
    {
        case XBAR_INPUT_FLG_REG_1:
            offset = XBAR_O_FLG1;
            break;

        case XBAR_INPUT_FLG_REG_2:
            offset = XBAR_O_FLG2;
            break;

        case XBAR_INPUT_FLG_REG_3:
            offset = XBAR_O_FLG3;
            break;

        case XBAR_INPUT_FLG_REG_4:
            offset = XBAR_O_FLG4;
            break;

        case XBAR_INPUT_FLG_REG_5:
            offset = XBAR_O_FLG5;
            break;

        case XBAR_INPUT_FLG_REG_6:
            offset = XBAR_O_FLG6;
            break;

        case XBAR_INPUT_FLG_REG_7:
            offset = XBAR_O_FLG7;
            break;

        case XBAR_INPUT_FLG_REG_8:
            offset = XBAR_O_FLG8;
            break;

        case XBAR_INPUT_FLG_REG_9:
            offset = XBAR_O_FLG9;
            break;

        case XBAR_INPUT_FLG_REG_10:
            offset = XBAR_O_FLG10;
            break;

        case XBAR_INPUT_FLG_REG_11:
            offset = XBAR_O_FLG11;
            break;

        case XBAR_INPUT_FLG_REG_12:
            offset = XBAR_O_FLG12;
            break;

        case XBAR_INPUT_FLG_REG_13:
            offset = XBAR_O_FLG13;
            break;

        case XBAR_INPUT_FLG_REG_14:
            offset = XBAR_O_FLG14;
            break;

        case XBAR_INPUT_FLG_REG_15:
            offset = XBAR_O_FLG15;
            break;

        case XBAR_INPUT_FLG_REG_16:
            offset = XBAR_O_FLG16;
            break;

        case XBAR_INPUT_FLG_REG_17:
            offset = XBAR_O_FLG17;
            break;

        case XBAR_INPUT_FLG_REG_18:
            offset = XBAR_O_FLG18;
            break;

        default:
            //
            // This should never happen if a valid inputFlag value is used.
            //
            offset = 0U;  // but offset 0U is for XBAR_O_FLG1
            break;
    }

    //
    // Get the status of the X-BAR input latch.
    //
    inputMask = (uint32_t)1U << ((uint32_t)inputFlag & XBAR_INPUT_INPUT_M);

    return((HWREG(XBAR_BASE + offset) & inputMask) != 0U);
}

//*****************************************************************************
//
// XBAR_clearInputFlag
//
//*****************************************************************************
void
XBAR_clearInputFlag(XBAR_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    //
    // Determine flag clear register offset.
    //
    switch((uint32_t)inputFlag & XBAR_INPUT_REG_M)
    {
        case XBAR_INPUT_FLG_REG_1:
            offset = XBAR_O_CLR1;
            break;

        case XBAR_INPUT_FLG_REG_2:
            offset = XBAR_O_CLR2;
            break;

        case XBAR_INPUT_FLG_REG_3:
            offset = XBAR_O_CLR3;
            break;

        case XBAR_INPUT_FLG_REG_4:
            offset = XBAR_O_CLR4;
            break;

        case XBAR_INPUT_FLG_REG_5:
            offset = XBAR_O_CLR5;
            break;

        case XBAR_INPUT_FLG_REG_6:
            offset = XBAR_O_CLR6;
            break;

        case XBAR_INPUT_FLG_REG_7:
            offset = XBAR_O_CLR7;
            break;

        case XBAR_INPUT_FLG_REG_8:
            offset = XBAR_O_CLR8;
            break;

        case XBAR_INPUT_FLG_REG_9:
            offset = XBAR_O_CLR9;
            break;

        case XBAR_INPUT_FLG_REG_10:
            offset = XBAR_O_CLR10;
            break;

        case XBAR_INPUT_FLG_REG_11:
            offset = XBAR_O_CLR11;
            break;

        case XBAR_INPUT_FLG_REG_12:
            offset = XBAR_O_CLR12;
            break;

        case XBAR_INPUT_FLG_REG_13:
            offset = XBAR_O_CLR13;
            break;

        case XBAR_INPUT_FLG_REG_14:
            offset = XBAR_O_CLR14;
            break;

        case XBAR_INPUT_FLG_REG_15:
            offset = XBAR_O_CLR15;
            break;

        case XBAR_INPUT_FLG_REG_16:
            offset = XBAR_O_CLR16;
            break;

        case XBAR_INPUT_FLG_REG_17:
            offset = XBAR_O_CLR17;
            break;

        case XBAR_INPUT_FLG_REG_18:
            offset = XBAR_O_CLR18;
            break;

        default:
            //
            // This should never happen if a valid inputFlag value is used.
            //
            offset = 0U;
            break;
    }

    //
    // Set the bit that clears the X-BAR input latch.
    //
    inputMask = (uint32_t)1U << ((uint32_t)inputFlag & XBAR_INPUT_INPUT_M);
    HWREG(XBAR_BASE + offset) = inputMask;
}
