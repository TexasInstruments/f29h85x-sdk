//###########################################################################
//
// FILE:    hwbf_mdl_xbar.h
//
// TITLE:   Definitions for the MDL_XBAR registers.
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

#ifndef HWBF_MDL_XBAR_H
#define HWBF_MDL_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// MDL_XBAR Individual Register Bit Definitions:

struct MDL_XBAR_MDLXBARG0SEL_BITS {     // bits description
    uint16_t INPUT0:1;                  // 0 Select bit for INPUT0
    uint16_t INPUT1:1;                  // 1 Select bit for INPUT1
    uint16_t INPUT2:1;                  // 2 Select bit for INPUT2
    uint16_t INPUT3:1;                  // 3 Select bit for INPUT3
    uint16_t INPUT4:1;                  // 4 Select bit for INPUT4
    uint16_t INPUT5:1;                  // 5 Select bit for INPUT5
    uint16_t INPUT6:1;                  // 6 Select bit for INPUT6
    uint16_t INPUT7:1;                  // 7 Select bit for INPUT7
    uint16_t INPUT8:1;                  // 8 Select bit for INPUT8
    uint16_t INPUT9:1;                  // 9 Select bit for INPUT9
    uint16_t INPUT10:1;                 // 10 Select bit for INPUT10
    uint16_t INPUT11:1;                 // 11 Select bit for INPUT11
    uint16_t INPUT12:1;                 // 12 Select bit for INPUT12
    uint16_t INPUT13:1;                 // 13 Select bit for INPUT13
    uint16_t INPUT14:1;                 // 14 Select bit for INPUT14
    uint16_t INPUT15:1;                 // 15 Select bit for INPUT15
    uint16_t INPUT16:1;                 // 16 Select bit for INPUT16
    uint16_t INPUT17:1;                 // 17 Select bit for INPUT17
    uint16_t INPUT18:1;                 // 18 Select bit for INPUT18
    uint16_t INPUT19:1;                 // 19 Select bit for INPUT19
    uint16_t INPUT20:1;                 // 20 Select bit for INPUT20
    uint16_t INPUT21:1;                 // 21 Select bit for INPUT21
    uint16_t INPUT22:1;                 // 22 Select bit for INPUT22
    uint16_t INPUT23:1;                 // 23 Select bit for INPUT23
    uint16_t INPUT24:1;                 // 24 Select bit for INPUT24
    uint16_t INPUT25:1;                 // 25 Select bit for INPUT25
    uint16_t INPUT26:1;                 // 26 Select bit for INPUT26
    uint16_t INPUT27:1;                 // 27 Select bit for INPUT27
    uint16_t INPUT28:1;                 // 28 Select bit for INPUT28
    uint16_t INPUT29:1;                 // 29 Select bit for INPUT29
    uint16_t INPUT30:1;                 // 30 Select bit for INPUT30
    uint16_t INPUT31:1;                 // 31 Select bit for INPUT31
};

union MDL_XBAR_MDLXBARG0SEL_REG {
    uint32_t  all;
    struct  MDL_XBAR_MDLXBARG0SEL_BITS  bit;
};

struct MDL_XBAR_MDLXBARG1SEL_BITS {     // bits description
    uint16_t INPUT0:1;                  // 0 Select bit for INPUT0
    uint16_t INPUT1:1;                  // 1 Select bit for INPUT1
    uint16_t INPUT2:1;                  // 2 Select bit for INPUT2
    uint16_t INPUT3:1;                  // 3 Select bit for INPUT3
    uint16_t INPUT4:1;                  // 4 Select bit for INPUT4
    uint16_t INPUT5:1;                  // 5 Select bit for INPUT5
    uint16_t INPUT6:1;                  // 6 Select bit for INPUT6
    uint16_t INPUT7:1;                  // 7 Select bit for INPUT7
    uint16_t INPUT8:1;                  // 8 Select bit for INPUT8
    uint16_t INPUT9:1;                  // 9 Select bit for INPUT9
    uint16_t INPUT10:1;                 // 10 Select bit for INPUT10
    uint16_t INPUT11:1;                 // 11 Select bit for INPUT11
    uint16_t INPUT12:1;                 // 12 Select bit for INPUT12
    uint16_t INPUT13:1;                 // 13 Select bit for INPUT13
    uint16_t INPUT14:1;                 // 14 Select bit for INPUT14
    uint16_t INPUT15:1;                 // 15 Select bit for INPUT15
    uint16_t INPUT16:1;                 // 16 Select bit for INPUT16
    uint16_t INPUT17:1;                 // 17 Select bit for INPUT17
    uint16_t INPUT18:1;                 // 18 Select bit for INPUT18
    uint16_t INPUT19:1;                 // 19 Select bit for INPUT19
    uint16_t INPUT20:1;                 // 20 Select bit for INPUT20
    uint16_t INPUT21:1;                 // 21 Select bit for INPUT21
    uint16_t INPUT22:1;                 // 22 Select bit for INPUT22
    uint16_t INPUT23:1;                 // 23 Select bit for INPUT23
    uint16_t INPUT24:1;                 // 24 Select bit for INPUT24
    uint16_t INPUT25:1;                 // 25 Select bit for INPUT25
    uint16_t INPUT26:1;                 // 26 Select bit for INPUT26
    uint16_t INPUT27:1;                 // 27 Select bit for INPUT27
    uint16_t INPUT28:1;                 // 28 Select bit for INPUT28
    uint16_t INPUT29:1;                 // 29 Select bit for INPUT29
    uint16_t INPUT30:1;                 // 30 Select bit for INPUT30
    uint16_t INPUT31:1;                 // 31 Select bit for INPUT31
};

union MDL_XBAR_MDLXBARG1SEL_REG {
    uint32_t  all;
    struct  MDL_XBAR_MDLXBARG1SEL_BITS  bit;
};

struct MDL_XBAR_MDLXBARG2SEL_BITS {     // bits description
    uint16_t INPUT0:1;                  // 0 Select bit for INPUT0
    uint16_t INPUT1:1;                  // 1 Select bit for INPUT1
    uint16_t INPUT2:1;                  // 2 Select bit for INPUT2
    uint16_t INPUT3:1;                  // 3 Select bit for INPUT3
    uint16_t INPUT4:1;                  // 4 Select bit for INPUT4
    uint16_t INPUT5:1;                  // 5 Select bit for INPUT5
    uint16_t INPUT6:1;                  // 6 Select bit for INPUT6
    uint16_t INPUT7:1;                  // 7 Select bit for INPUT7
    uint16_t INPUT8:1;                  // 8 Select bit for INPUT8
    uint16_t INPUT9:1;                  // 9 Select bit for INPUT9
    uint16_t INPUT10:1;                 // 10 Select bit for INPUT10
    uint16_t INPUT11:1;                 // 11 Select bit for INPUT11
    uint16_t INPUT12:1;                 // 12 Select bit for INPUT12
    uint16_t INPUT13:1;                 // 13 Select bit for INPUT13
    uint16_t INPUT14:1;                 // 14 Select bit for INPUT14
    uint16_t INPUT15:1;                 // 15 Select bit for INPUT15
    uint16_t INPUT16:1;                 // 16 Select bit for INPUT16
    uint16_t INPUT17:1;                 // 17 Select bit for INPUT17
    uint16_t INPUT18:1;                 // 18 Select bit for INPUT18
    uint16_t INPUT19:1;                 // 19 Select bit for INPUT19
    uint16_t INPUT20:1;                 // 20 Select bit for INPUT20
    uint16_t INPUT21:1;                 // 21 Select bit for INPUT21
    uint16_t INPUT22:1;                 // 22 Select bit for INPUT22
    uint16_t INPUT23:1;                 // 23 Select bit for INPUT23
    uint16_t INPUT24:1;                 // 24 Select bit for INPUT24
    uint16_t INPUT25:1;                 // 25 Select bit for INPUT25
    uint16_t INPUT26:1;                 // 26 Select bit for INPUT26
    uint16_t INPUT27:1;                 // 27 Select bit for INPUT27
    uint16_t INPUT28:1;                 // 28 Select bit for INPUT28
    uint16_t INPUT29:1;                 // 29 Select bit for INPUT29
    uint16_t INPUT30:1;                 // 30 Select bit for INPUT30
    uint16_t INPUT31:1;                 // 31 Select bit for INPUT31
};

union MDL_XBAR_MDLXBARG2SEL_REG {
    uint32_t  all;
    struct  MDL_XBAR_MDLXBARG2SEL_BITS  bit;
};

struct MDL_XBAR_REGS_RegisterFile0_REGS {
    union   MDL_XBAR_MDLXBARG0SEL_REG        MDLXBARG0SEL;                 // MDLXBAR G0 Input Select
    union   MDL_XBAR_MDLXBARG1SEL_REG        MDLXBARG1SEL;                 // MDLXBAR G1 Input Select
    union   MDL_XBAR_MDLXBARG2SEL_REG        MDLXBARG2SEL;                 // MDLXBAR G2 Input Select
    uint8_t                                  rsvd1[52];                    // Reserved
};

struct MDL_XBAR_MDLXBAROutInvert_BITS { // bits description
    uint16_t XBAR1:1;                   // 0 Invert XBAR Output Select for XBAR1
    uint16_t XBAR2:1;                   // 1 Invert XBAR Output Select for XBAR2
    uint16_t XBAR3:1;                   // 2 Invert XBAR Output Select for XBAR3
    uint16_t XBAR4:1;                   // 3 Invert XBAR Output Select for XBAR4
    uint16_t XBAR5:1;                   // 4 Invert XBAR Output Select for XBAR5
    uint16_t XBAR6:1;                   // 5 Invert XBAR Output Select for XBAR6
    uint16_t XBAR7:1;                   // 6 Invert XBAR Output Select for XBAR7
    uint16_t XBAR8:1;                   // 7 Invert XBAR Output Select for XBAR8
    uint16_t XBAR9:1;                   // 8 Invert XBAR Output Select for XBAR9
    uint16_t XBAR10:1;                  // 9 Invert XBAR Output Select for XBAR10
    uint16_t XBAR11:1;                  // 10 Invert XBAR Output Select for XBAR11
    uint16_t XBAR12:1;                  // 11 Invert XBAR Output Select for XBAR12
    uint16_t XBAR13:1;                  // 12 Invert XBAR Output Select for XBAR13
    uint16_t XBAR14:1;                  // 13 Invert XBAR Output Select for XBAR14
    uint16_t XBAR15:1;                  // 14 Invert XBAR Output Select for XBAR15
    uint16_t XBAR16:1;                  // 15 Invert XBAR Output Select for XBAR16
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union MDL_XBAR_MDLXBAROutInvert_REG {
    uint32_t  all;
    struct  MDL_XBAR_MDLXBAROutInvert_BITS  bit;
};

struct MDL_XBAR_MDLXBARLock_BITS {      // bits description
    uint16_t LOCK:1;                    // 0 Locks the configuration for EMDL-XBAR
    uint16_t rsvd1:15;                  // 15:1 Reserved
    uint16_t KEY:16;                    // 31:16 Write protection KEY
};

union MDL_XBAR_MDLXBARLock_REG {
    uint32_t  all;
    struct  MDL_XBAR_MDLXBARLock_BITS  bit;
};

struct MDL_XBAR_REGS {
    uint8_t                                  rsvd1[48];                    // Reserved
    union   MDL_XBAR_MDLXBAROutInvert_REG    MDLXBAROutInvert;             // Output Signal Invert Select
    uint8_t                                  rsvd2[76];                    // Reserved
    union   MDL_XBAR_MDLXBARLock_REG         MDLXBARLock;                  // Configuration Lock register
    uint8_t                                  rsvd3[124];                   // Reserved
    struct MDL_XBAR_REGS_RegisterFile0_REGS  MDL_XBAR_RegisterFile0[16];   // 
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
