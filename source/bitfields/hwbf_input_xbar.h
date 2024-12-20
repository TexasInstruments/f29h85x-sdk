//###########################################################################
//
// FILE:    hwbf_input_xbar.h
//
// TITLE:   Definitions for the INPUT_XBAR registers.
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

#ifndef HWBF_INPUT_XBAR_H
#define HWBF_INPUT_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// INPUT_XBAR Individual Register Bit Definitions:

struct INPUT_XBAR_INPUTSELECT_BITS {    // bits description
    uint16_t SELECT:16;                 // 15:0 Select GPIO for INPUT{#} signal
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union INPUT_XBAR_INPUTSELECT_REG {
    uint32_t  all;
    struct  INPUT_XBAR_INPUTSELECT_BITS  bit;
};

struct INPUT_XBAR_INPUTSELECTLOCK1_BITS {// bits description
    uint16_t INPUT1SELECT:1;            // 0 Lock bit for INPUT1SELECT Register
    uint16_t INPUT2SELECT:1;            // 1 Lock bit for INPUT2SELECT Register
    uint16_t INPUT3SELECT:1;            // 2 Lock bit for INPUT3SELECT Register
    uint16_t INPUT4SELECT:1;            // 3 Lock bit for INPUT4SELECT Register
    uint16_t INPUT5SELECT:1;            // 4 Lock bit for INPUT5SELECT Register
    uint16_t INPUT6SELECT:1;            // 5 Lock bit for INPUT6SELECT Register
    uint16_t INPUT7SELECT:1;            // 6 Lock bit for INPUT7SELECT Register
    uint16_t INPUT8SELECT:1;            // 7 Lock bit for INPUT8SELECT Register
    uint16_t INPUT9SELECT:1;            // 8 Lock bit for INPUT9SELECT Register
    uint16_t INPUT10SELECT:1;           // 9 Lock bit for INPUT10SELECT Register
    uint16_t INPUT11SELECT:1;           // 10 Lock bit for INPUT11SELECT Register
    uint16_t INPUT12SELECT:1;           // 11 Lock bit for INPUT12SELECT Register
    uint16_t INPUT13SELECT:1;           // 12 Lock bit for INPUT13SELECT Register
    uint16_t INPUT14SELECT:1;           // 13 Lock bit for INPUT14SELECT Register
    uint16_t INPUT15SELECT:1;           // 14 Lock bit for INPUT15SELECT Register
    uint16_t INPUT16SELECT:1;           // 15 Lock bit for INPUT16SELECT Register
    uint16_t INPUT17SELECT:1;           // 16 Lock bit for INPUT17SELECT Register
    uint16_t INPUT18SELECT:1;           // 17 Lock bit for INPUT18SELECT Register
    uint16_t INPUT19SELECT:1;           // 18 Lock bit for INPUT19SELECT Register
    uint16_t INPUT20SELECT:1;           // 19 Lock bit for INPUT20SELECT Register
    uint16_t INPUT21SELECT:1;           // 20 Lock bit for INPUT21SELECT Register
    uint16_t INPUT22SELECT:1;           // 21 Lock bit for INPUT22SELECT Register
    uint16_t INPUT23SELECT:1;           // 22 Lock bit for INPUT23SELECT Register
    uint16_t INPUT24SELECT:1;           // 23 Lock bit for INPUT24SELECT Register
    uint16_t INPUT25SELECT:1;           // 24 Lock bit for INPUT25SELECT Register
    uint16_t INPUT26SELECT:1;           // 25 Lock bit for INPUT26SELECT Register
    uint16_t INPUT27SELECT:1;           // 26 Lock bit for INPUT27SELECT Register
    uint16_t INPUT28SELECT:1;           // 27 Lock bit for INPUT28SELECT Register
    uint16_t INPUT29SELECT:1;           // 28 Lock bit for INPUT29SELECT Register
    uint16_t INPUT30SELECT:1;           // 29 Lock bit for INPUT30SELECT Register
    uint16_t INPUT31SELECT:1;           // 30 Lock bit for INPUT31SELECT Register
    uint16_t INPUT32SELECT:1;           // 31 Lock bit for INPUT32SELECT Register
};

union INPUT_XBAR_INPUTSELECTLOCK1_REG {
    uint32_t  all;
    struct  INPUT_XBAR_INPUTSELECTLOCK1_BITS  bit;
};

struct INPUT_XBAR_INPUTSELECTLOCK2_BITS {// bits description
    uint16_t INPUT33SELECT:1;           // 0 Lock bit for INPUT33SELECT Register
    uint16_t INPUT34SELECT:1;           // 1 Lock bit for INPUT34SELECT Register
    uint16_t INPUT35SELECT:1;           // 2 Lock bit for INPUT35SELECT Register
    uint16_t INPUT36SELECT:1;           // 3 Lock bit for INPUT36SELECT Register
    uint16_t INPUT37SELECT:1;           // 4 Lock bit for INPUT37SELECT Register
    uint16_t INPUT38SELECT:1;           // 5 Lock bit for INPUT38SELECT Register
    uint16_t INPUT39SELECT:1;           // 6 Lock bit for INPUT39SELECT Register
    uint16_t INPUT40SELECT:1;           // 7 Lock bit for INPUT40SELECT Register
    uint16_t INPUT41SELECT:1;           // 8 Lock bit for INPUT41SELECT Register
    uint16_t INPUT42SELECT:1;           // 9 Lock bit for INPUT42SELECT Register
    uint16_t INPUT43SELECT:1;           // 10 Lock bit for INPUT43SELECT Register
    uint16_t INPUT44SELECT:1;           // 11 Lock bit for INPUT44SELECT Register
    uint16_t INPUT45SELECT:1;           // 12 Lock bit for INPUT45SELECT Register
    uint16_t INPUT46SELECT:1;           // 13 Lock bit for INPUT46SELECT Register
    uint16_t INPUT47SELECT:1;           // 14 Lock bit for INPUT47SELECT Register
    uint16_t INPUT48SELECT:1;           // 15 Lock bit for INPUT48SELECT Register
    uint16_t INPUT49SELECT:1;           // 16 Lock bit for INPUT49SELECT Register
    uint16_t INPUT50SELECT:1;           // 17 Lock bit for INPUT50SELECT Register
    uint16_t INPUT51SELECT:1;           // 18 Lock bit for INPUT51SELECT Register
    uint16_t INPUT52SELECT:1;           // 19 Lock bit for INPUT52SELECT Register
    uint16_t INPUT53SELECT:1;           // 20 Lock bit for INPUT53SELECT Register
    uint16_t INPUT54SELECT:1;           // 21 Lock bit for INPUT54SELECT Register
    uint16_t INPUT55SELECT:1;           // 22 Lock bit for INPUT55SELECT Register
    uint16_t INPUT56SELECT:1;           // 23 Lock bit for INPUT56SELECT Register
    uint16_t INPUT57SELECT:1;           // 24 Lock bit for INPUT57SELECT Register
    uint16_t INPUT58SELECT:1;           // 25 Lock bit for INPUT58SELECT Register
    uint16_t INPUT59SELECT:1;           // 26 Lock bit for INPUT59SELECT Register
    uint16_t INPUT60SELECT:1;           // 27 Lock bit for INPUT60SELECT Register
    uint16_t INPUT61SELECT:1;           // 28 Lock bit for INPUT61SELECT Register
    uint16_t INPUT62SELECT:1;           // 29 Lock bit for INPUT62SELECT Register
    uint16_t INPUT63SELECT:1;           // 30 Lock bit for INPUT63SELECT Register
    uint16_t INPUT64SELECT:1;           // 31 Lock bit for INPUT64SELECT Register
};

union INPUT_XBAR_INPUTSELECTLOCK2_REG {
    uint32_t  all;
    struct  INPUT_XBAR_INPUTSELECTLOCK2_BITS  bit;
};

struct INPUT_XBAR_REGS {
    union   INPUT_XBAR_INPUTSELECT_REG       INPUTSELECT[64];              // Input Select Register (GPIO0 to x)
    uint8_t                                  rsvd1[768];                   // Reserved
    union   INPUT_XBAR_INPUTSELECTLOCK1_REG  INPUTSELECTLOCK1;             // Input Select Lock Register 1
    union   INPUT_XBAR_INPUTSELECTLOCK2_REG  INPUTSELECTLOCK2;             // Input Select Lock Register 2
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
