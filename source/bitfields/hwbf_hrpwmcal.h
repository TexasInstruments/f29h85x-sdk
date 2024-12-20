//###########################################################################
//
// FILE:    hwbf_hrpwmcal.h
//
// TITLE:   Definitions for the HRPWMCAL registers.
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

#ifndef HWBF_HRPWMCAL_H
#define HWBF_HRPWMCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// HRPWMCAL Individual Register Bit Definitions:

struct HRPWMCAL_HRPWR_BITS {            // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t rsvd2:1;                   // 2 Reserved
    uint16_t rsvd3:1;                   // 3 Reserved
    uint16_t rsvd4:1;                   // 4 Reserved
    uint16_t rsvd5:1;                   // 5 Reserved
    uint16_t rsvd6:4;                   // 9:6 Reserved
    uint16_t rsvd7:5;                   // 14:10 Reserved
    uint16_t CALPWRON:1;                // 15 Calibration Power On
};

union HRPWMCAL_HRPWR_REG {
    uint16_t  all;
    struct  HRPWMCAL_HRPWR_BITS  bit;
};

struct HRPWMCAL_HRMSTEP_BITS {          // bits description
    uint16_t HRMSTEP:8;                 // 7:0 High Resolution Micro Step Value
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union HRPWMCAL_HRMSTEP_REG {
    uint16_t  all;
    struct  HRPWMCAL_HRMSTEP_BITS  bit;
};

struct HRPWMCAL_REGS {
    uint8_t                                  rsvd1[66];                    // Reserved
    union   HRPWMCAL_HRPWR_REG               HRPWR;                        // HRPWM Power Register
    uint8_t                                  rsvd2[8];                     // Reserved
    union   HRPWMCAL_HRMSTEP_REG             HRMSTEP;                      // HRPWM MEP Step Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
