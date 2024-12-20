//###########################################################################
//
// FILE:   ssu.c
//
// TITLE:  C29x Safety & Security Unit (SSU) driver.
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

#include "ssu.h"


//**************************************************************************************************
//
// SSU_setAccessProtection
//
//**************************************************************************************************
void
SSU_setAccessProtection(SSU_CPUID cpu, SSU_APConfig config[], int length)
{
    int i;
    uint32_t apCfg;

    for(i = 0U; i < length; i++)
    {
        ASSERT(config[i].region < SSU_TOTAL_AP);

        //
        // Check if the last 12 bits of start address is 0,
        // and last 12 bits of end address is 0xFFF
        //
        ASSERT(((config[i].startAddr & 0xFFFU) == 0U) &&
               ((config[i].endAddr   & 0xFFFU) == 0xFFFU));

        //
        // If the region is not AP_EXT, check if the first 8 bits are same and
        // and the reserved bits are 0
        //
        ASSERT((config[i].region <  SSU_TOTAL_AP_EXT) ||
               (
                 ((config[i].startAddr >> 24U) == (config[i].endAddr >> 24U)) &&
                 ((config[i].startAddr & 0x8F000000U) == 0U) &&
                 ((config[i].endAddr   & 0x8F000000U) == 0U)
               ));


        if(config[i].exelinkID != SSU_EXE_DISABLE)
        {
            //
            // Enable execution from this region and set the LINKID
            //
            apCfg = SSU_AP_CFG_XE | ((uint32_t)config[i].exelinkID << SSU_AP_CFG_LINKID_S);
        }
        else
        {
            //
            // Set the LINKID as 2. LINKID is not valid if execution is disabled from this region.
            //
            apCfg = 2U << SSU_AP_CFG_LINKID_S;
        }

        if(config[i].apiLinkID != SSU_API_DISABLE)
        {
            apCfg |= SSU_AP_CFG_APILINKE | ((uint32_t)config[i].apiLinkID << SSU_AP_CFG_APILINK_S);
        }

        HWREG(SSU_AP_CFG(cpu, config[i].region))    = apCfg;
        HWREG(SSU_AP_ACCESS(cpu, config[i].region)) = config[i].linkAccess;


        HWREG(SSU_AP_START(cpu, config[i].region)) = config[i].startAddr;
        HWREG(SSU_AP_END(cpu, config[i].region))   = config[i].endAddr;
    }
}
