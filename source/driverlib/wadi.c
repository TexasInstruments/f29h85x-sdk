//###########################################################################
//
// FILE:   wadi.c
//
// TITLE:  C29x WADI driver.
//
//#############################################################################
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

//#############################################################################
#include "wadi.h"



//*****************************************************************************
//
// WADI_configSignalAndTrigger
//
//*****************************************************************************

void WADI_configSignalAndTrigger(uint32_t base,
                        WADI_InputSignal signal1,
                        WADI_InputSignal signal2,
                        WADI_Trigger1 trigger1,
                        WADI_Trigger2 trigger2)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));


    if(WADI_isWadi1(base))
    {
        ASSERT((trigger1 & 0xF0) == 0x10);
        ASSERT((trigger2 & 0xF0) == 0x10);
    }
    else
    {
        ASSERT((trigger1 & 0xF0) == 0x20);
        ASSERT((trigger2 & 0xF0) == 0x20);
    }

    HWREG(base + WADI_O_BLKCFG)
        = (((signal1) << WADI_BLKCFG_SIG1IN_S) |
        ((signal2) << WADI_BLKCFG_SIG2IN_S) |
        ((trigger1 & 0x0F) << WADI_BLKCFG_TRIG1IN_S) |
        ((trigger2 & 0x0F) << WADI_BLKCFG_TRIG2IN_S));
}


//*****************************************************************************
//
// WADI_measurePulseWidth
//
//*****************************************************************************

void WADI_measurePulseWidth(uint32_t base,
                const WADI_SigConfig *configSignal,
                const WADI_PulseWidthConfigParams *configParams,
                const WADI_PulseWidthConfigCompare *configCompare)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    if(configSignal->signal == WADI_SIGNAL1)   // signal 1
    {
        //
        // Enable the trigger and write the trigger mode
        // in the BLKTRIGCFG register
        //
        HWREG(base + WADI_O_BLKTRIGCFG)
                |= (configSignal->triggerMode << WADI_BLKTRIGCFG_TRIG1TYPE_S);

        //
        // Write the mode configurations in the SIG1CFG register
        //
        HWREG(base + WADI_O_SIG1CFG)
                = ((configParams->aggrMode << WADI_SIG1CFG_AGGRMODE_S) |
                (configParams->numAggr << WADI_SIG1CFG_NUMAGGR_S)|
                (configParams->edgeSpan << WADI_SIG1CFG_EDGESPAN_S)|
                (configParams->polarity << WADI_SIG1CFG_SIGPOL_S));

        //
        // Write the compare values in the Compare registers
        //
        HWREG(base + WADI_O_SIG1CMPA)
                = ((configCompare->cmpAVal << WADI_SIG1CMPA_CMPA_S)|
                (configCompare->cmpAMargin << WADI_SIG1CMPA_CMPAMARGIN_S));

        HWREG(base + WADI_O_SIG1CMPB)
                = ((configCompare->cmpBVal << WADI_SIG1CMPB_CMPB_S)|
                (configCompare->cmpBMargin << WADI_SIG1CMPB_CMPBMARGIN_S));

        HWREG(base + WADI_O_SIG1AVGCFG)
                = ((configCompare->cmpAvgVal << WADI_SIG1AVGCFG_CMP_S)|
                (configCompare->cmpAvgMargin << WADI_SIG1AVGCFG_CMPMARGIN_S));

        HWREG(base + WADI_O_SIG1PKCFG)
                = ((configCompare->cmpPkVal << WADI_SIG1PKCFG_CMP_S)|
                (configCompare->cmpPkMargin << WADI_SIG1PKCFG_CMPMARGIN_S));

        //
        // Selecting the signal 1 for debug
        //
        HWREG(base + WADI_O_BLKERRCFG) = WADI_DEBUG_SIGNAL1;

    }

    else                            // signal 2
    {
        //
        // Write the trigger mode in the BLKTRIGCFG register
        //
        HWREG(base + WADI_O_BLKTRIGCFG)
                |= (configSignal->triggerMode << WADI_BLKTRIGCFG_TRIG2TYPE_S);


        //
        // Write the mode configurations in the SIG2CFG register
        //
        HWREG(base + WADI_O_SIG2CFG)
                = ((configParams->aggrMode << WADI_SIG2CFG_AGGRMODE_S) |
                (configParams->numAggr << WADI_SIG2CFG_NUMAGGR_S)|
                (configParams->edgeSpan << WADI_SIG2CFG_EDGESPAN_S)|
                (configParams->polarity << WADI_SIG2CFG_SIGPOL_S));

        //
        // Write the compare values in the Compare registers
        //
        HWREG(base + WADI_O_SIG2CMPA)
                = ((configCompare->cmpAVal << WADI_SIG2CMPA_CMPA_S)|
                (configCompare->cmpAMargin << WADI_SIG2CMPA_CMPAMARGIN_S));

        HWREG(base + WADI_O_SIG2CMPB)
                = ((configCompare->cmpBVal << WADI_SIG2CMPB_CMPB_S)|
                (configCompare->cmpBMargin << WADI_SIG2CMPB_CMPBMARGIN_S));

        HWREG(base + WADI_O_SIG2AVGCFG)
                = ((configCompare->cmpAvgVal << WADI_SIG2AVGCFG_CMP_S)|
                (configCompare->cmpAvgMargin << WADI_SIG2AVGCFG_CMPMARGIN_S));

        HWREG(base + WADI_O_SIG2PKCFG)
                = ((configCompare->cmpPkVal << WADI_SIG2PKCFG_CMP_S)|
                (configCompare->cmpPkMargin << WADI_SIG2PKCFG_CMPMARGIN_S));

        //
        // Selecting the signal 2 for debug
        //
        HWREG(base + WADI_O_BLKERRCFG) = WADI_DEBUG_SIGNAL2;

    }

}


//*****************************************************************************
//
// WADI_measureFrequency
//
//*****************************************************************************

void WADI_measureFrequency(uint32_t base,
                    const WADI_SigConfig *configSignal,
                    const WADI_FreqConfigParams *configParams,
                    const WADI_FreqConfigCompare *configCompare)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    if(configSignal->signal == WADI_SIGNAL1) // signal 1
    {
        //
        // Enable the trigger and write the trigger mode in
        // in the BLKTRIGCFG register
        //
        HWREG(base + WADI_O_BLKTRIGCFG)
                |= (configSignal->triggerMode << WADI_BLKTRIGCFG_TRIG1TYPE_S);

        //
        // Write the signal polarity in the the SIG1CFG register
        //
        // The edge span is set as 0x2U to detect every pulse of the
        // configured type
        //
        HWREG(base + WADI_O_SIG1CFG)
                = ((0x2U << WADI_SIG1CFG_EDGESPAN_S)|
                (configParams->aggrMode << WADI_SIG1CFG_AGGRMODE_S)|
                (configParams->numaggr << WADI_SIG1CFG_NUMAGGR_S)|
                (configParams->polarity << WADI_SIG1CFG_SIGPOL_S));

        if(configParams->freqMode == WADI_COMPARE_FREQ_MODE_FIXED_WINDOW)
        {
            //
            // Enabling the edge count and writing the time window.
            //
            HWREG(base + WADI_O_SIG1EDGECFG)
                = (WADI_SIG1EDGECFG_CNTEN |
                (configParams->timeWindow << WADI_SIG1EDGECFG_TIMEWNDOW_S));
        }
        else
        {
            //
            // Enabling the edge count
            //
            HWREG(base + WADI_O_SIG1EDGECFG) = (WADI_SIG1EDGECFG_CNTEN);

            //
            // Enabling the moving window mode and writing the
            // moving window count and the moving window time
            // in the SIG1EDGEMVWCFG register
            //
            HWREG(base + WADI_O_SIG1EDGEMVWCFG)
            = ((WADI_SIG1EDGEMVWCFG_MVWEN)
            | (configParams->movingCount << WADI_SIG1EDGEMVWCFG_MVWCNT_S)
            | (configParams->mvwtime << WADI_SIG1EDGEMVWCFG_MVWTIME_S));
        }

        //
        // Write the compare values in the compare registersw
        //
        HWREG(base + WADI_O_SIG1CMPA)
                = ((configCompare->cmpAVal << WADI_SIG1CMPA_CMPA_S)|
                (configCompare->cmpAMargin << WADI_SIG1CMPA_CMPAMARGIN_S));

        HWREG(base + WADI_O_SIG1CMPB)
                = ((configCompare->cmpBVal << WADI_SIG1CMPB_CMPB_S)|
                (configCompare->cmpBMargin << WADI_SIG1CMPB_CMPBMARGIN_S));

        HWREG(base + WADI_O_SIG1AVGCFG)
                = ((configCompare->cmpAvgVal << WADI_SIG1AVGCFG_CMP_S)|
                (configCompare->cmpAvgMargin << WADI_SIG1AVGCFG_CMPMARGIN_S));

        HWREG(base + WADI_O_SIG1PKCFG)
                = ((configCompare->cmpPkVal << WADI_SIG1PKCFG_CMP_S)|
                (configCompare->cmpPkMargin << WADI_SIG1PKCFG_CMPMARGIN_S));

        //
        // Selecting the signal 1 for debug
        //
        HWREG(base + WADI_O_BLKERRCFG) = WADI_DEBUG_SIGNAL1;

    }

    else                                // signal 2
    {
        //
        // Enable the trigger and write the trigger mode in
        // in the BLKTRIGCFG register
        //
        HWREG(base + WADI_O_BLKTRIGCFG)
                |= (configSignal->triggerMode << WADI_BLKTRIGCFG_TRIG2TYPE_S);

        //
        // Write the signal polarity in the the SIG2CFG register
        //
        // The edge span is set as 0x2U to detect every pulse of the
        // configured type
        //
        HWREG(base + WADI_O_SIG2CFG)
                =((0x2U << WADI_SIG2CFG_EDGESPAN_S)|
                (configParams->aggrMode << WADI_SIG2CFG_AGGRMODE_S)|
                (configParams->numaggr << WADI_SIG2CFG_NUMAGGR_S) |
                (configParams->polarity << WADI_SIG2CFG_SIGPOL_S));

        if(configParams->freqMode == WADI_COMPARE_FREQ_MODE_FIXED_WINDOW)
        {
            //
            // Enabling the edge count and writing the time window
            //
            HWREG(base + WADI_O_SIG2EDGECFG)
                = (WADI_SIG2EDGECFG_CNTEN |
                (configParams->timeWindow << WADI_SIG2EDGECFG_TIMEWNDOW_S));
        }
        else
        {
            //
            // Enabling the edge count
            //
            HWREG(base + WADI_O_SIG2EDGECFG) |= (WADI_SIG2EDGECFG_CNTEN);

            //
            // Setting the enable bit and writing the moving window tume
            // and moving window time in the SIG2EDGEMVWCFG register
            //
            HWREG(base + WADI_O_SIG2EDGEMVWCFG)
                = ((WADI_SIG2EDGEMVWCFG_MVWEN)
                | (configParams->movingCount << WADI_SIG2EDGEMVWCFG_MVWCNT_S)
                | (configParams->mvwtime << WADI_SIG2EDGEMVWCFG_MVWTIME_S));
        }

        //
        // Write the compare values in the compare registers
        //
        HWREG(base + WADI_O_SIG2CMPA)
                = ((configCompare->cmpAVal << WADI_SIG2CMPA_CMPA_S)|
                (configCompare->cmpAMargin << WADI_SIG2CMPA_CMPAMARGIN_S));

        HWREG(base + WADI_O_SIG2CMPB)
                = ((configCompare->cmpBVal << WADI_SIG2CMPB_CMPB_S)|
                (configCompare->cmpBMargin << WADI_SIG2CMPB_CMPBMARGIN_S));

        HWREG(base + WADI_O_SIG2AVGCFG)
                = ((configCompare->cmpAvgVal << WADI_SIG2AVGCFG_CMP_S)|
                (configCompare->cmpAvgMargin << WADI_SIG2AVGCFG_CMPMARGIN_S));

        HWREG(base + WADI_O_SIG2PKCFG)
                = ((configCompare->cmpPkVal << WADI_SIG2PKCFG_CMP_S)|
                (configCompare->cmpPkMargin << WADI_SIG2PKCFG_CMPMARGIN_S));

        //
        // Selecting the signal 2 for debug
        //
        HWREG(base + WADI_O_BLKERRCFG)|= WADI_DEBUG_SIGNAL2;

    }
}


//*****************************************************************************
//
// WADI_compareSigToSigPulseWidth
//
//*****************************************************************************

void WADI_compareSigToSigPulseWidth(uint32_t base,
                const WADI_SigToSigConfig *configSignals,
                const WADI_SigToSigPWConfigParams *configParams,
                const WADI_SigToSigPWConfigCompare *configCompare)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Enable the triggers and write the trigger modes in the
    // BLKTRIGCFG register
    //
    HWREG(base + WADI_O_BLKTRIGCFG)
        |= (configSignals->triggerMode1 << WADI_BLKTRIGCFG_TRIG1TYPE_S) |
        (configSignals->triggerMode2 << WADI_BLKTRIGCFG_TRIG2TYPE_S);

    //
    // Write the mode configurations in the SIG1CFG and SIG2CFG register
    //
    HWREG(base + WADI_O_SIG1CFG)
        = ((configParams->polarity << WADI_SIG1CFG_SIGPOL_S) |
        (configParams->aggrMode << WADI_SIG1CFG_AGGRMODE_S) |
        (configParams->numAggr << WADI_SIG1CFG_NUMAGGR_S) |
        (configParams->edgeSpan << WADI_SIG1CFG_EDGESPAN_S));

    HWREG(base + WADI_O_SIG2CFG)
        = ((configParams->polarity << WADI_SIG2CFG_SIGPOL_S) |
        (configParams->aggrMode << WADI_SIG2CFG_AGGRMODE_S) |
        (configParams->numAggr << WADI_SIG2CFG_NUMAGGR_S) |
        (configParams->edgeSpan << WADI_SIG2CFG_EDGESPAN_S));

    //
    // Enabling the signal to signal compare
    //
    HWREG(base + WADI_O_SIGTOSIGCFG) = WADI_SIGTOSIGCFG_SIGTOSIG_CMPEN;

    //
    // Write the compare values in the sig to sig compare registers
    //
    HWREG(base + WADI_O_SIGTOSIGCFG)
        |= ((configCompare->cmpVal << WADI_SIGTOSIGCFG_CMP_S) |
        (configCompare->cmpMargin << WADI_SIGTOSIGCFG_CMPMARGIN_S));

    HWREG(base + WADI_O_SIGTOSIG_PKCFG)
        = ((configCompare->cmpPkVal << WADI_SIGTOSIG_PKCFG_PKCMP_S) |
        (configCompare->cmpPkMargin << WADI_SIGTOSIG_PKCFG_PKCMPMARGIN_S));

    HWREG(base + WADI_O_SIGTOSIG_AVGCFG)
        = ((configCompare->cmpAvgVal << WADI_SIGTOSIG_AVGCFG_AVGCMP_S) |
        (configCompare->cmpAvgMargin << WADI_SIGTOSIG_AVGCFG_AVGCMPMARGIN_S));

    //
    // Selecting the signal to signal mode for debug
    //
    HWREG(base + WADI_O_BLKERRCFG) = WADI_DEBUG_SIGNAL_TO_SIGNAL;
}


//*****************************************************************************
//
// WADI_compareSigToSigFrequency
//
//*****************************************************************************

void WADI_compareSigToSigFrequency(uint32_t base,
                const WADI_SigToSigConfig *configSignals,
                const WADI_SigToSigFreqConfigParams *configParams,
                const WADI_SigToSigFreqConfigCompare *configCompare)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Enable the triggers and write the trigger modes
    //
    HWREG(base + WADI_O_BLKTRIGCFG)
        |= (configSignals->triggerMode1 << WADI_BLKTRIGCFG_TRIG1TYPE_S) |
        (configSignals->triggerMode2 << WADI_BLKTRIGCFG_TRIG2TYPE_S);

    //
    // Write the polarity and edgespan in the SIG2CFG and SIG2CFG registers
    //
    HWREG(base + WADI_O_SIG1CFG)
        = ((configParams->polarity << WADI_SIG1CFG_SIGPOL_S) |
        (configParams->aggrMode << WADI_SIG1CFG_AGGRMODE_S) |
        (configParams->numaggr << WADI_SIG1CFG_NUMAGGR_S) |
        (0x2U << WADI_SIG1CFG_EDGESPAN_S));

    HWREG(base + WADI_O_SIG2CFG)
        = ((configParams->polarity << WADI_SIG2CFG_SIGPOL_S) |
        (configParams->aggrMode << WADI_SIG2CFG_AGGRMODE_S) |
        (configParams->numaggr << WADI_SIG2CFG_NUMAGGR_S) |
        (0x2U << WADI_SIG2CFG_EDGESPAN_S));

    if(configParams->freqMode == 0)  // frequency fixed window mode
    {
        //
        // Enabling the edge count main mode compare and writing the time
        // window in the SIG1EDGECFG and SIG2EDGECFG registers
        //
        HWREG(base + WADI_O_SIG1EDGECFG)
            = (WADI_SIG1EDGECFG_CNTEN |
            (configParams->timeWindow << WADI_SIG1EDGECFG_TIMEWNDOW_S));

        HWREG(base + WADI_O_SIG2EDGECFG)
            = (WADI_SIG2EDGECFG_CNTEN |
            (configParams->timeWindow << WADI_SIG2EDGECFG_TIMEWNDOW_S));

    }

    else                               // frequency moving window mode
    {

        //
        // Enabling the edge count
        //
        HWREG(base + WADI_O_SIG1EDGECFG) |= (WADI_SIG1EDGECFG_CNTEN);
        HWREG(base + WADI_O_SIG2EDGECFG) |= (WADI_SIG2EDGECFG_CNTEN);

        //
        // Enabling the edge count moving window mode compare and writing the
        // moving window time and moving window count in the SIG1EDGEMVWCFG
        // and SIG2EDGEMVWCFG registers
        //
        HWREG(base + WADI_O_SIG1EDGEMVWCFG)
            = ((WADI_SIG1EDGEMVWCFG_MVWEN) |
            (configParams->mvwtime << WADI_SIG1EDGEMVWCFG_MVWTIME_S) |
            (configParams->movingCount << WADI_SIG1EDGEMVWCFG_MVWCNT_S));

        HWREG(base + WADI_O_SIG2EDGEMVWCFG)
            = ((WADI_SIG2EDGEMVWCFG_MVWEN) |
            (configParams->mvwtime << WADI_SIG2EDGEMVWCFG_MVWTIME_S) |
            (configParams->movingCount << WADI_SIG2EDGEMVWCFG_MVWCNT_S));
    }

    //
    // Enabling the signal to signal compare
    //
    HWREG(base + WADI_O_SIGTOSIGCFG) = WADI_SIGTOSIGCFG_SIGTOSIG_CMPEN;

    HWREG(base + WADI_O_SIGTOSIGCFG)
            |= ((configCompare->cmpVal << WADI_SIGTOSIGCFG_CMP_S) |
            (configCompare->cmpMargin << WADI_SIGTOSIGCFG_CMPMARGIN_S));

    HWREG(base + WADI_O_SIGTOSIG_PKCFG)
        = ((configCompare->cmpPkVal << WADI_SIGTOSIG_PKCFG_PKCMP_S) |
        (configCompare->cmpPkMargin << WADI_SIGTOSIG_PKCFG_PKCMPMARGIN_S));

    HWREG(base + WADI_O_SIGTOSIG_AVGCFG)
        = ((configCompare->cmpAvgVal << WADI_SIGTOSIG_AVGCFG_AVGCMP_S) |
        (configCompare->cmpAvgMargin << WADI_SIGTOSIG_AVGCFG_AVGCMPMARGIN_S));


    //
    // Selecting the signal to signal mode for debug
    //
    HWREG(base + WADI_O_BLKERRCFG) = WADI_DEBUG_SIGNAL_TO_SIGNAL;
}


//*****************************************************************************
//
// WADI_compareSigToSigDeadBandMode
//
//*****************************************************************************

void WADI_compareSigToSigDeadBandMode(uint32_t base,
                    const WADI_SigToSigConfig *configSignals,
                    const WADI_SigToSigDeadbandConfigParams *configParams)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Enable the triggers and write the trigger modes in the
    // BLKTRIGCFG register
    //
    HWREG(base + WADI_O_BLKTRIGCFG)
        |= (configSignals->triggerMode1 << WADI_BLKTRIGCFG_TRIG1TYPE_S) |
        (configSignals->triggerMode2 << WADI_BLKTRIGCFG_TRIG2TYPE_S);

    //
    // Enables the deadband check between two signals
    //
    HWREG(base + WADI_O_SIGTOSIGCFG)
        |= WADI_SIGTOSIGCFG_SIGTOSIG_DBCMPEN;

    //
    // Write the polarity of the configured edges in the SIG1CFG
    // SIG2CFG registers
    //
    HWREG(base + WADI_O_SIG1CFG)
        |= (configParams->polarity1 << WADI_SIG1CFG_SIGPOL_S);

    HWREG(base + WADI_O_SIG2CFG)
        |= (configParams->polarity2 << WADI_SIG2CFG_SIGPOL_S);

    //
    // Write the deadband compare type in the SIGTOSIGCFG register
    //
    if(configParams->compareType == 0)  // Deadband of configured
                                        // edge comparison
    {
        HWREG(base + WADI_O_SIGTOSIGCFG) &= ~WADI_SIGTOSIGCFG_DBCMPTYPE;
    }

    else                                // Deadband of configured and
                                        // opposite edge pairs comparison
    {
        HWREG(base + WADI_O_SIGTOSIGCFG) |= WADI_SIGTOSIGCFG_DBCMPTYPE;
    }

    //
    // Writing the compare values in the compare registers
    //
    HWREG(base + WADI_O_SIGTOSIG_DBOLAPA)
        |= (configParams->compareA << WADI_SIGTOSIG_DBOLAPA_DBCMPA_S);

    HWREG(base + WADI_O_SIGTOSIG_DBOLAPB)
        |= (configParams->compareB << WADI_SIGTOSIG_DBOLAPB_DBCMPB_S);

    //
    // Selecting the signal to signal mode for debug
    //
    HWREG(base + WADI_O_BLKERRCFG) = WADI_DEBUG_SIGNAL_TO_SIGNAL;
}


//*****************************************************************************
//
// WADI_compareSigToSigPhaseOverlapMode
//
//*****************************************************************************

void WADI_compareSigToSigPhaseOverlapMode(uint32_t base,
                    const WADI_SigToSigConfig *configSignals,
                    const WADI_SigToSigPhaseOverlapCompareParams *configParams)
{
    //
    // Check the arguments
    //
    ASSERT(WADI_isBaseValid(base));

    //
    // Enable the triggers and write the trigger modes in the
    // BLKTRIGCFG register
    //
    HWREG(base + WADI_O_BLKTRIGCFG)
        |= (configSignals->triggerMode1 << WADI_BLKTRIGCFG_TRIG1TYPE_S) |
        (configSignals->triggerMode2 << WADI_BLKTRIGCFG_TRIG2TYPE_S);

    //
    // Enables the phase overlap check between two signals
    //
    HWREG(base + WADI_O_SIGTOSIGCFG) |= WADI_SIGTOSIGCFG_SIGTOSIG_OLAPCMPEN;

    //
    // Write the polarity of the Configured edges in the SIG1CFG
    // SIG2CFG registers
    //
    HWREG(base + WADI_O_SIG1CFG)
        |= (configParams->polarity1 << WADI_SIG1CFG_SIGPOL_S);

    HWREG(base + WADI_O_SIG2CFG)
        |= (configParams->polarity2 << WADI_SIG2CFG_SIGPOL_S);

    //
    // Write the phase overlap compare type in the SIGTOSIGCFG register
    //
    if(configParams->compareType == 0) // Overlap of levels
                                        // per configuration
    {
        HWREG(base + WADI_O_SIGTOSIGCFG) &= ~WADI_SIGTOSIGCFG_OLAPCMPTYPE;
    }

    else                                // Overlap of levels per configuration
                                        // and complementary levels
    {
        HWREG(base + WADI_O_SIGTOSIGCFG)|= WADI_SIGTOSIGCFG_OLAPCMPTYPE;
    }

    //
    // Writing the compare values in the compare registers
    //
    HWREG(base + WADI_O_SIGTOSIG_DBOLAPA)
        |= (configParams->compareA << WADI_SIGTOSIG_DBOLAPA_OLAPCMPA_S);
    HWREG(base + WADI_O_SIGTOSIG_DBOLAPA)
        |= (configParams->compareAMargin <<
            WADI_SIGTOSIG_DBOLAPA_OLAPCMPAMARGIN_S);

    HWREG(base + WADI_O_SIGTOSIG_DBOLAPB)
        |= (configParams->compareB << WADI_SIGTOSIG_DBOLAPB_OLAPCMPB_S);
    HWREG(base + WADI_O_SIGTOSIG_DBOLAPB)
        |= (configParams->compareBMargin <<
            WADI_SIGTOSIG_DBOLAPB_OLAPCMPBMARGIN_S);

    //
    // Selecting the signal to signal mode for debug
    //
    HWREG(base + WADI_O_BLKERRCFG) = WADI_DEBUG_SIGNAL_TO_SIGNAL;
}