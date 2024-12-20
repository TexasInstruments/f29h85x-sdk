//###########################################################################
//
// FILE:   dlt.c
//
// TITLE:  C29x Data Logger and Trace (DLT) driver.
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

#include "dlt.h"


//*****************************************************************************
//
// DLT_configTagFilter
//
//*****************************************************************************
void DLT_configTagFilter(const DLT_ConfigTagFilterParams *configParams)
{
    HWREGH(CPUDLT_BASE + DLT_O_TAG_FILTER_START_REF) =
                                               configParams->startReference;
    HWREGH(CPUDLT_BASE + DLT_O_TAG_FILTER_START_MASK) =
                                                    configParams->startMask;
    HWREGH(CPUDLT_BASE + DLT_O_TAG_FILTER_END_REF) =
                                                 configParams->endReference;
    HWREGH(CPUDLT_BASE + DLT_O_TAG_FILTER_END_MASK) = configParams->endMask;
}

//*****************************************************************************
//
// DLT_configERADFilter
//
//*****************************************************************************
void DLT_configERADFilter(uint64_t startEvents, uint64_t endEvents)
{
    HWREG(CPUDLT_BASE + DLT_O_ERAD_START_MASK_L) = (uint32_t)startEvents;
    HWREG(CPUDLT_BASE + DLT_O_ERAD_START_MASK_H) =
                                            (uint32_t)(startEvents >> 32U);
    HWREG(CPUDLT_BASE + DLT_O_ERAD_END_MASK_L) = (uint32_t)endEvents;
    HWREG(CPUDLT_BASE + DLT_O_ERAD_END_MASK_H) =
                                            (uint32_t)(endEvents >> 32U);
}


//
// End of file
//
