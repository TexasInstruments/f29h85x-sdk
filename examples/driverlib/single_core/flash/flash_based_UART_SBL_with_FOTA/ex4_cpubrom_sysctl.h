//###########################################################################
//
// FILE:   ex4_cpubrom_sysctl.h
//
// TITLE:  BootROM Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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

#ifndef C_BOOTROM_SYSCTL_H
#define C_BOOTROM_SYSCTL_H
//
//  Includes
//
#include "device.h"

/**
*Function to reset the device.
*
*Arguments:
*
*
*/
static inline void SysCtl_resetDevice(void)
{
    //
    //  Configure XRSn as CTL reset source
    //  ->  Clear bit 'ASYSCTL_CTLRSTSRC_SRC'
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CTLRSTSRCCLR) = ASYSCTL_CTLRSTSRCCLR_SRC;
    //
    //  WD is RESET mode
    //
    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_RESET);
    SysCtl_enableWatchdog();
    //
    //  Writing bad value causes WD reset
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = 0U;
    //
    //  Wait for ever
    //
    for( ; ; )
    {
        ;
    }
}

#endif //C_BOOTROM_SYSCTL_H
