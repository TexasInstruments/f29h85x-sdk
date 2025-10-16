//###########################################################################
//
// FILE:   sbl_device_utils.h
//
// TITLE:  Common Macros Used and Helper APIs
//
//###########################################################################
// $TI Release:  $
// $Release Date:   $
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

#ifndef SBL_DEVICE_UTILS_H
#define SBL_DEVICE_UTILS_H

//
//  Includes
//
#include <device.h>
#include "cpubrom.h"

//
// Function Definitions
//
void Example_Error(void);
void CPU_jumpToAddr(uint32_t jumpAddr);
uint32_t getMaxFlashImageSize(void);
void enableFlashEraseAndWrite(void);
void storeAndDisableFlashWEPROT(void);
void restoreFlashWEPROT(void);

static inline uint8_t getDeviceState(void);
static inline uint8_t getBankMode(void);

//
//  Device State value (HSM DEVICE_HS_SUB_TYPE)
//
#define HS_FS   (0b1010)
#define HS_KP   (0b0011)
#define HS_SE   (0b0000) // any other 4bit value could also represent SE 
#define HS_FA   (0b1111)        

//
// Returns device state (DEVICE_HS_SUB_TYPE)
//
static inline uint8_t getDeviceState(void) 
{
    //
    // Read DEVCFG_BASE.DEVLIFECYCLE.HSSUBTYPE to determine device state
    //
    return ((HWREG((DEVCFG_BASE + 0x3D4)) & 0xF00) >> 8);
}

//
// Returns CPU1 Bank Mode
//
static inline uint8_t getBankMode(void)
{
    return((HWREG(SSUGEN_BASE + 0x5C)));
}

#endif //SBL_DEVICE_UTILS_H
