//###########################################################################
//
// FILE:    hwbf_cputimer.h
//
// TITLE:   Definitions for the CPUTIMER registers.
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

#ifndef HWBF_CPUTIMER_H
#define HWBF_CPUTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// CPUTIMER Individual Register Bit Definitions:

struct CPUTIMER_TIM_BITS {              // bits description
    uint16_t LSW:16;                    // 15:0 CPU-Timer Counter Registers
    uint16_t MSW:16;                    // 31:16 CPU-Timer Counter Registers High
};

union CPUTIMER_TIM_REG {
    uint32_t  all;
    struct  CPUTIMER_TIM_BITS  bit;
};

struct CPUTIMER_PRD_BITS {              // bits description
    uint16_t LSW:16;                    // 15:0 CPU-Timer Period Registers
    uint16_t MSW:16;                    // 31:16 CPU-Timer Period Registers High
};

union CPUTIMER_PRD_REG {
    uint32_t  all;
    struct  CPUTIMER_PRD_BITS  bit;
};

struct CPUTIMER_TCR_BITS {              // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t TSS:1;                     // 4 CPU-Timer stop status bit.
    uint16_t TRB:1;                     // 5 Timer reload
    uint16_t rsvd2:4;                   // 9:6 Reserved
    uint16_t SOFT:1;                    // 10 Emulation modes
    uint16_t FREE:1;                    // 11 Emulation modes
    uint16_t rsvd3:2;                   // 13:12 Reserved
    uint16_t TIE:1;                     // 14 CPU-Timer Interrupt Enable.
    uint16_t TIF:1;                     // 15 CPU-Timer Interrupt Flag.
};

union CPUTIMER_TCR_REG {
    uint16_t  all;
    struct  CPUTIMER_TCR_BITS  bit;
};

struct CPUTIMER_TPR_BITS {              // bits description
    uint16_t TDDR:8;                    // 7:0 CPU-Timer Divide-Down.
    uint16_t PSC:8;                     // 15:8 CPU-Timer Prescale Counter.
};

union CPUTIMER_TPR_REG {
    uint16_t  all;
    struct  CPUTIMER_TPR_BITS  bit;
};

struct CPUTIMER_TPRH_BITS {             // bits description
    uint16_t TDDRH:8;                   // 7:0 CPU-Timer Divide-Down.
    uint16_t PSCH:8;                    // 15:8 CPU-Timer Prescale Counter.
};

union CPUTIMER_TPRH_REG {
    uint16_t  all;
    struct  CPUTIMER_TPRH_BITS  bit;
};

struct CPUTIMER_REGS {
    union   CPUTIMER_TIM_REG                 TIM;                          // CPU-Timer, Counter Register
    union   CPUTIMER_PRD_REG                 PRD;                          // CPU-Timer, Period Register
    union   CPUTIMER_TCR_REG                 TCR;                          // CPU-Timer, Control Register
    uint8_t                                  rsvd1[2];                     // Reserved
    union   CPUTIMER_TPR_REG                 TPR;                          // CPU-Timer, Prescale Register
    union   CPUTIMER_TPRH_REG                TPRH;                         // CPU-Timer, Prescale Register High
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
