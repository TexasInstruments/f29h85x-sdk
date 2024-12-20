//###########################################################################
//
// FILE:    hwbf_ipc.h
//
// TITLE:   Definitions for the IPC registers.
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

#ifndef HWBF_IPC_H
#define HWBF_IPC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// IPC Individual Register Bit Definitions:

struct IPC_COUNTER_REGS {
    uint32_t                                 IPCCOUNTERL;                  // IPCCOUNTERL Register
    uint32_t                                 IPCCOUNTERH;                  // IPCCOUNTERH Register
};

struct IPC_CPU1TOCPU2INTIPCSET_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU1TOCPU2INTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU2INTIPCSET_BITS  bit;
};

struct IPC_CPU1TOCPU2INTIPCCLR_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU1TOCPU2IPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU1TOCPU2IPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU1TOCPU2IPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU1TOCPU2IPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU1TOCPU2IPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU1TOCPU2IPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU1TOCPU2IPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU1TOCPU2IPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU1TOCPU2IPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU1TOCPU2IPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU1TOCPU2IPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU1TOCPU2IPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU1TOCPU2IPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU1TOCPU2IPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU1TOCPU2IPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU1TOCPU2IPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU1TOCPU2IPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU1TOCPU2IPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU1TOCPU2IPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU1TOCPU2IPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU1TOCPU2IPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU1TOCPU2IPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU1TOCPU2IPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU1TOCPU2IPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU1TOCPU2IPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU1TOCPU2IPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU1TOCPU2IPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU1TOCPU2IPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU1TOCPU2IPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU1TOCPU2IPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU1TOCPU2IPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU1TOCPU2IPCFLG.IPC31 Flag
};

union IPC_CPU1TOCPU2INTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU2INTIPCCLR_BITS  bit;
};

struct IPC_CPU1TOCPU2INTIPCFLG_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 CPU1 to CPU2 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 CPU1 to CPU2 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 CPU1 to CPU2 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 CPU1 to CPU2 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 CPU1 to CPU2 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 CPU1 to CPU2 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 CPU1 to CPU2 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 CPU1 to CPU2 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 CPU1 to CPU2 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 CPU1 to CPU2 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 CPU1 to CPU2 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 CPU1 to CPU2 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 CPU1 to CPU2 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 CPU1 to CPU2 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 CPU1 to CPU2 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 CPU1 to CPU2 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 CPU1 to CPU2 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 CPU1 to CPU2 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 CPU1 to CPU2 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 CPU1 to CPU2 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 CPU1 to CPU2 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 CPU1 to CPU2 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 CPU1 to CPU2 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 CPU1 to CPU2 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 CPU1 to CPU2 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 CPU1 to CPU2 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 CPU1 to CPU2 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 CPU1 to CPU2 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 CPU1 to CPU2 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 CPU1 to CPU2 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 CPU1 to CPU2 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 CPU1 to CPU2 IPC31 Flag Status
};

union IPC_CPU1TOCPU2INTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU2INTIPCFLG_BITS  bit;
};

struct CPU1_IPC_SEND_REGS_RegisterFile0_REGS {
    union   IPC_CPU1TOCPU2INTIPCSET_REG      CPU1TOCPU2INTIPCSET;          // CPU1TOCPU2INTIPCSET Register
    union   IPC_CPU1TOCPU2INTIPCCLR_REG      CPU1TOCPU2INTIPCCLR;          // CPU1TOCPU2INTIPCCLR Register
    union   IPC_CPU1TOCPU2INTIPCFLG_REG      CPU1TOCPU2INTIPCFLG;          // CPU1TOCPU2INTIPCFLG Register
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 CPU1TOCPU2INTIPCSENDCOM;      // CPU1TOCPU2INTIPCSENDCOM Register
    uint32_t                                 CPU1TOCPU2INTIPCSENDADDR;     // CPU1TOCPU2INTIPCSENDADDR Register
    uint32_t                                 CPU1TOCPU2INTIPCSENDDATA;     // CPU1TOCPU2INTIPCSENDDATA Register
    uint32_t                                 CPU2TOCPU1INTREMOTEREPLY;     // CPU2TOCPU1INTREMOTEREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU1TOCPU3INTIPCSET_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU1TOCPU3INTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU3INTIPCSET_BITS  bit;
};

struct IPC_CPU1TOCPU3INTIPCCLR_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU1TOCPU3IPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU1TOCPU3IPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU1TOCPU3IPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU1TOCPU3IPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU1TOCPU3IPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU1TOCPU3IPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU1TOCPU3IPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU1TOCPU3IPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU1TOCPU3IPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU1TOCPU3IPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU1TOCPU3IPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU1TOCPU3IPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU1TOCPU3IPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU1TOCPU3IPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU1TOCPU3IPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU1TOCPU3IPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU1TOCPU3IPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU1TOCPU3IPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU1TOCPU3IPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU1TOCPU3IPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU1TOCPU3IPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU1TOCPU3IPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU1TOCPU3IPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU1TOCPU3IPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU1TOCPU3IPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU1TOCPU3IPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU1TOCPU3IPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU1TOCPU3IPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU1TOCPU3IPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU1TOCPU3IPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU1TOCPU3IPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU1TOCPU3IPCFLG.IPC31 Flag
};

union IPC_CPU1TOCPU3INTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU3INTIPCCLR_BITS  bit;
};

struct IPC_CPU1TOCPU3INTIPCFLG_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 CPU1 to CPU3 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 CPU1 to CPU3 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 CPU1 to CPU3 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 CPU1 to CPU3 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 CPU1 to CPU3 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 CPU1 to CPU3 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 CPU1 to CPU3 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 CPU1 to CPU3 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 CPU1 to CPU3 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 CPU1 to CPU3 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 CPU1 to CPU3 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 CPU1 to CPU3 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 CPU1 to CPU3 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 CPU1 to CPU3 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 CPU1 to CPU3 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 CPU1 to CPU3 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 CPU1 to CPU3 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 CPU1 to CPU3 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 CPU1 to CPU3 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 CPU1 to CPU3 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 CPU1 to CPU3 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 CPU1 to CPU3 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 CPU1 to CPU3 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 CPU1 to CPU3 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 CPU1 to CPU3 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 CPU1 to CPU3 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 CPU1 to CPU3 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 CPU1 to CPU3 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 CPU1 to CPU3 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 CPU1 to CPU3 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 CPU1 to CPU3 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 CPU1 to CPU3 IPC31 Flag Status
};

union IPC_CPU1TOCPU3INTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU3INTIPCFLG_BITS  bit;
};

struct CPU1_IPC_SEND_REGS_RegisterFile1_REGS {
    union   IPC_CPU1TOCPU3INTIPCSET_REG      CPU1TOCPU3INTIPCSET;          // CPU1TOCPU3INTIPCSET Register
    union   IPC_CPU1TOCPU3INTIPCCLR_REG      CPU1TOCPU3INTIPCCLR;          // CPU1TOCPU3INTIPCCLR Register
    union   IPC_CPU1TOCPU3INTIPCFLG_REG      CPU1TOCPU3INTIPCFLG;          // CPU1TOCPU3INTIPCFLG Register
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 CPU1TOCPU3INTIPCSENDCOM;      // CPU1TOCPU3INTIPCSENDCOM Register
    uint32_t                                 CPU1TOCPU3INTIPCSENDADDR;     // CPU1TOCPU3INTIPCSENDADDR Register
    uint32_t                                 CPU1TOCPU3INTIPCSENDDATA;     // CPU1TOCPU3INTIPCSENDDATA Register
    uint32_t                                 CPU3TOCPU1INTREMOTEREPLY;     // CPU3TOCPU1INTREMOTEREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU1TOHSMINTIPCSET_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU1TOHSMINTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU1TOHSMINTIPCSET_BITS  bit;
};

struct IPC_CPU1TOHSMINTIPCCLR_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU1TOHSMIPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU1TOHSMIPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU1TOHSMIPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU1TOHSMIPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU1TOHSMIPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU1TOHSMIPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU1TOHSMIPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU1TOHSMIPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU1TOHSMIPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU1TOHSMIPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU1TOHSMIPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU1TOHSMIPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU1TOHSMIPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU1TOHSMIPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU1TOHSMIPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU1TOHSMIPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU1TOHSMIPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU1TOHSMIPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU1TOHSMIPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU1TOHSMIPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU1TOHSMIPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU1TOHSMIPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU1TOHSMIPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU1TOHSMIPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU1TOHSMIPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU1TOHSMIPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU1TOHSMIPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU1TOHSMIPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU1TOHSMIPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU1TOHSMIPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU1TOHSMIPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU1TOHSMIPCFLG.IPC31 Flag
};

union IPC_CPU1TOHSMINTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU1TOHSMINTIPCCLR_BITS  bit;
};

struct IPC_CPU1TOHSMINTIPCFLG_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 HSM to CPU1 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 HSM to CPU1 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 HSM to CPU1 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 HSM to CPU1 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 HSM to CPU1 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 HSM to CPU1 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 HSM to CPU1 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 HSM to CPU1 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 HSM to CPU1 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 HSM to CPU1 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 HSM to CPU1 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 HSM to CPU1 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 HSM to CPU1 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 HSM to CPU1 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 HSM to CPU1 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 HSM to CPU1 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 HSM to CPU1 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 HSM to CPU1 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 HSM to CPU1 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 HSM to CPU1 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 HSM to CPU1 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 HSM to CPU1 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 HSM to CPU1 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 HSM to CPU1 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 HSM to CPU1 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 HSM to CPU1 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 HSM to CPU1 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 HSM to CPU1 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 HSM to CPU1 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 HSM to CPU1 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 HSM to CPU1 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 HSM to CPU1 IPC31 Flag Status
};

union IPC_CPU1TOHSMINTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU1TOHSMINTIPCFLG_BITS  bit;
};

struct CPU1_IPC_SEND_REGS_RegisterFile2_REGS {
    union   IPC_CPU1TOHSMINTIPCSET_REG       CPU1TOHSMINTIPCSET;           // CPU1TOHSMINTIPCSET Register
    union   IPC_CPU1TOHSMINTIPCCLR_REG       CPU1TOHSMINTIPCCLR;           // CPU1TOHSMINTIPCCLR Register
    union   IPC_CPU1TOHSMINTIPCFLG_REG       CPU1TOHSMINTIPCFLG;           // CPU1TOHSMINTIPCFLG Register
    uint8_t                                  rsvd1[4084];                  // Reserved
};

struct CPU1_IPC_SEND_REGS {
    struct CPU1_IPC_SEND_REGS_RegisterFile0_REGS CPU1_IPC_SEND_RegisterFile0[4]; // 
    struct CPU1_IPC_SEND_REGS_RegisterFile1_REGS CPU1_IPC_SEND_RegisterFile1[4]; // 
    uint8_t                                  rsvd1[8192];                  // Reserved
    struct CPU1_IPC_SEND_REGS_RegisterFile2_REGS CPU1_IPC_SEND_RegisterFile2[2]; // 
};

struct IPC_CPU2TOCPU1INTIPCSTS_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Local IPC Flag 0 Status
    uint16_t IPC1:1;                    // 1 Local IPC Flag 1 Status
    uint16_t IPC2:1;                    // 2 Local IPC Flag 2 Status
    uint16_t IPC3:1;                    // 3 Local IPC Flag 3 Status
    uint16_t IPC4:1;                    // 4 Local IPC Flag 4 Status
    uint16_t IPC5:1;                    // 5 Local IPC Flag 5 Status
    uint16_t IPC6:1;                    // 6 Local IPC Flag 6 Status
    uint16_t IPC7:1;                    // 7 Local IPC Flag 7 Status
    uint16_t IPC8:1;                    // 8 Local IPC Flag 8 Status
    uint16_t IPC9:1;                    // 9 Local IPC Flag 9 Status
    uint16_t IPC10:1;                   // 10 Local IPC Flag 10 Status
    uint16_t IPC11:1;                   // 11 Local IPC Flag 11 Status
    uint16_t IPC12:1;                   // 12 Local IPC Flag 12 Status
    uint16_t IPC13:1;                   // 13 Local IPC Flag 13 Status
    uint16_t IPC14:1;                   // 14 Local IPC Flag 14 Status
    uint16_t IPC15:1;                   // 15 Local IPC Flag 15 Status
    uint16_t IPC16:1;                   // 16 Local IPC Flag 16 Status
    uint16_t IPC17:1;                   // 17 Local IPC Flag 17 Status
    uint16_t IPC18:1;                   // 18 Local IPC Flag 18 Status
    uint16_t IPC19:1;                   // 19 Local IPC Flag 19 Status
    uint16_t IPC20:1;                   // 20 Local IPC Flag 20 Status
    uint16_t IPC21:1;                   // 21 Local IPC Flag 21 Status
    uint16_t IPC22:1;                   // 22 Local IPC Flag 22 Status
    uint16_t IPC23:1;                   // 23 Local IPC Flag 23 Status
    uint16_t IPC24:1;                   // 24 Local IPC Flag 24 Status
    uint16_t IPC25:1;                   // 25 Local IPC Flag 25 Status
    uint16_t IPC26:1;                   // 26 Local IPC Flag 26 Status
    uint16_t IPC27:1;                   // 27 Local IPC Flag 27 Status
    uint16_t IPC28:1;                   // 28 Local IPC Flag 28 Status
    uint16_t IPC29:1;                   // 29 Local IPC Flag 29 Status
    uint16_t IPC30:1;                   // 30 Local IPC Flag 30 Status
    uint16_t IPC31:1;                   // 31 Local IPC Flag 31 Status
};

union IPC_CPU2TOCPU1INTIPCSTS_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU1INTIPCSTS_BITS  bit;
};

struct IPC_CPU1TOCPU2INTIPCACK_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC0 bit
    uint16_t IPC1:1;                    // 1 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC1 bit
    uint16_t IPC2:1;                    // 2 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC2 bit
    uint16_t IPC3:1;                    // 3 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC3 bit
    uint16_t IPC4:1;                    // 4 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC4 bit
    uint16_t IPC5:1;                    // 5 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC5 bit
    uint16_t IPC6:1;                    // 6 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC6 bit
    uint16_t IPC7:1;                    // 7 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC7 bit
    uint16_t IPC8:1;                    // 8 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC8 bit
    uint16_t IPC9:1;                    // 9 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC9 bit
    uint16_t IPC10:1;                   // 10 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC10 bit
    uint16_t IPC11:1;                   // 11 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC11 bit
    uint16_t IPC12:1;                   // 12 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC12 bit
    uint16_t IPC13:1;                   // 13 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC13 bit
    uint16_t IPC14:1;                   // 14 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC14 bit
    uint16_t IPC15:1;                   // 15 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC15 bit
    uint16_t IPC16:1;                   // 16 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC16 bit
    uint16_t IPC17:1;                   // 17 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC17 bit
    uint16_t IPC18:1;                   // 18 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC18 bit
    uint16_t IPC19:1;                   // 19 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC19 bit
    uint16_t IPC20:1;                   // 20 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC20 bit
    uint16_t IPC21:1;                   // 21 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC21 bit
    uint16_t IPC22:1;                   // 22 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC22 bit
    uint16_t IPC23:1;                   // 23 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC23 bit
    uint16_t IPC24:1;                   // 24 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC24 bit
    uint16_t IPC25:1;                   // 25 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC25 bit
    uint16_t IPC26:1;                   // 26 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC26 bit
    uint16_t IPC27:1;                   // 27 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC27 bit
    uint16_t IPC28:1;                   // 28 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC28 bit
    uint16_t IPC29:1;                   // 29 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC29 bit
    uint16_t IPC30:1;                   // 30 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC30 bit
    uint16_t IPC31:1;                   // 31 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC31 bit
};

union IPC_CPU1TOCPU2INTIPCACK_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU2INTIPCACK_BITS  bit;
};

struct CPU1_IPC_RCV_REGS_RegisterFile0_REGS {
    union   IPC_CPU2TOCPU1INTIPCSTS_REG      CPU2TOCPU1INTIPCSTS;          // CPU2TOCPU1INTIPCSTS Register
    union   IPC_CPU1TOCPU2INTIPCACK_REG      CPU1TOCPU2INTIPCACK;          // CPU1TOCPU2INTIPCACK Register
    uint8_t                                  rsvd1[8];                     // Reserved
    uint32_t                                 CPU2TOCPU1INTIPCRECVCOM;      // CPU2TOCPU1INTIPCRECVCOM Register
    uint32_t                                 CPU2TOCPU1INTIPCRECVADDR;     // CPU2TOCPU1INTIPCRECVADDR Register
    uint32_t                                 CPU2TOCPU1INTIPCRECVDATA;     // CPU2TOCPU1INTIPCRECVDATA Register
    uint32_t                                 CPU1TOCPU2INTLOCALREPLY;      // CPU1TOCPU2INTLOCALREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU3TOCPU1INTIPCSTS_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Local IPC Flag 0 Status
    uint16_t IPC1:1;                    // 1 Local IPC Flag 1 Status
    uint16_t IPC2:1;                    // 2 Local IPC Flag 2 Status
    uint16_t IPC3:1;                    // 3 Local IPC Flag 3 Status
    uint16_t IPC4:1;                    // 4 Local IPC Flag 4 Status
    uint16_t IPC5:1;                    // 5 Local IPC Flag 5 Status
    uint16_t IPC6:1;                    // 6 Local IPC Flag 6 Status
    uint16_t IPC7:1;                    // 7 Local IPC Flag 7 Status
    uint16_t IPC8:1;                    // 8 Local IPC Flag 8 Status
    uint16_t IPC9:1;                    // 9 Local IPC Flag 9 Status
    uint16_t IPC10:1;                   // 10 Local IPC Flag 10 Status
    uint16_t IPC11:1;                   // 11 Local IPC Flag 11 Status
    uint16_t IPC12:1;                   // 12 Local IPC Flag 12 Status
    uint16_t IPC13:1;                   // 13 Local IPC Flag 13 Status
    uint16_t IPC14:1;                   // 14 Local IPC Flag 14 Status
    uint16_t IPC15:1;                   // 15 Local IPC Flag 15 Status
    uint16_t IPC16:1;                   // 16 Local IPC Flag 16 Status
    uint16_t IPC17:1;                   // 17 Local IPC Flag 17 Status
    uint16_t IPC18:1;                   // 18 Local IPC Flag 18 Status
    uint16_t IPC19:1;                   // 19 Local IPC Flag 19 Status
    uint16_t IPC20:1;                   // 20 Local IPC Flag 20 Status
    uint16_t IPC21:1;                   // 21 Local IPC Flag 21 Status
    uint16_t IPC22:1;                   // 22 Local IPC Flag 22 Status
    uint16_t IPC23:1;                   // 23 Local IPC Flag 23 Status
    uint16_t IPC24:1;                   // 24 Local IPC Flag 24 Status
    uint16_t IPC25:1;                   // 25 Local IPC Flag 25 Status
    uint16_t IPC26:1;                   // 26 Local IPC Flag 26 Status
    uint16_t IPC27:1;                   // 27 Local IPC Flag 27 Status
    uint16_t IPC28:1;                   // 28 Local IPC Flag 28 Status
    uint16_t IPC29:1;                   // 29 Local IPC Flag 29 Status
    uint16_t IPC30:1;                   // 30 Local IPC Flag 30 Status
    uint16_t IPC31:1;                   // 31 Local IPC Flag 31 Status
};

union IPC_CPU3TOCPU1INTIPCSTS_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU1INTIPCSTS_BITS  bit;
};

struct IPC_CPU1TOCPU3INTIPCACK_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC0 bit
    uint16_t IPC1:1;                    // 1 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC1 bit
    uint16_t IPC2:1;                    // 2 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC2 bit
    uint16_t IPC3:1;                    // 3 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC3 bit
    uint16_t IPC4:1;                    // 4 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC4 bit
    uint16_t IPC5:1;                    // 5 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC5 bit
    uint16_t IPC6:1;                    // 6 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC6 bit
    uint16_t IPC7:1;                    // 7 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC7 bit
    uint16_t IPC8:1;                    // 8 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC8 bit
    uint16_t IPC9:1;                    // 9 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC9 bit
    uint16_t IPC10:1;                   // 10 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC10 bit
    uint16_t IPC11:1;                   // 11 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC11 bit
    uint16_t IPC12:1;                   // 12 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC12 bit
    uint16_t IPC13:1;                   // 13 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC13 bit
    uint16_t IPC14:1;                   // 14 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC14 bit
    uint16_t IPC15:1;                   // 15 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC15 bit
    uint16_t IPC16:1;                   // 16 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC16 bit
    uint16_t IPC17:1;                   // 17 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC17 bit
    uint16_t IPC18:1;                   // 18 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC18 bit
    uint16_t IPC19:1;                   // 19 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC19 bit
    uint16_t IPC20:1;                   // 20 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC20 bit
    uint16_t IPC21:1;                   // 21 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC21 bit
    uint16_t IPC22:1;                   // 22 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC22 bit
    uint16_t IPC23:1;                   // 23 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC23 bit
    uint16_t IPC24:1;                   // 24 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC24 bit
    uint16_t IPC25:1;                   // 25 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC25 bit
    uint16_t IPC26:1;                   // 26 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC26 bit
    uint16_t IPC27:1;                   // 27 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC27 bit
    uint16_t IPC28:1;                   // 28 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC28 bit
    uint16_t IPC29:1;                   // 29 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC29 bit
    uint16_t IPC30:1;                   // 30 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC30 bit
    uint16_t IPC31:1;                   // 31 Acknowledgement from CPU3 to CPU1TOCPU3IPCFLG.IPC31 bit
};

union IPC_CPU1TOCPU3INTIPCACK_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU3INTIPCACK_BITS  bit;
};

struct CPU1_IPC_RCV_REGS_RegisterFile1_REGS {
    union   IPC_CPU3TOCPU1INTIPCSTS_REG      CPU3TOCPU1INTIPCSTS;          // CPU3TOCPU1INTIPCSTS Register
    union   IPC_CPU1TOCPU3INTIPCACK_REG      CPU1TOCPU3INTIPCACK;          // CPU1TOCPU3INTIPCACK Register
    uint8_t                                  rsvd1[8];                     // Reserved
    uint32_t                                 CPU3TOCPU1INTIPCRECVCOM;      // CPU3TOCPU1INTIPCRECVCOM Register
    uint32_t                                 CPU3TOCPU1INTIPCRECVADDR;     // CPU3TOCPU1INTIPCRECVADDR Register
    uint32_t                                 CPU3TOCPU1INTIPCRECVDATA;     // CPU3TOCPU1INTIPCRECVDATA Register
    uint32_t                                 CPU1TOCPU3INTLOCALREPLY;      // CPU1TOCPU3INTLOCALREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct CPU1_IPC_RCV_REGS {
    struct CPU1_IPC_RCV_REGS_RegisterFile0_REGS CPU1_IPC_RCV_RegisterFile0[4]; // 
    struct CPU1_IPC_RCV_REGS_RegisterFile1_REGS CPU1_IPC_RCV_RegisterFile1[4]; // 
};

struct IPC_CPU2TOCPU1INTIPCSET_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU2TOCPU1INTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU1INTIPCSET_BITS  bit;
};

struct IPC_CPU2TOCPU1INTIPCCLR_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU2TOCPU1IPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU2TOCPU1IPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU2TOCPU1IPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU2TOCPU1IPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU2TOCPU1IPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU2TOCPU1IPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU2TOCPU1IPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU2TOCPU1IPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU2TOCPU1IPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU2TOCPU1IPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU2TOCPU1IPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU2TOCPU1IPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU2TOCPU1IPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU2TOCPU1IPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU2TOCPU1IPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU2TOCPU1IPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU2TOCPU1IPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU2TOCPU1IPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU2TOCPU1IPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU2TOCPU1IPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU2TOCPU1IPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU2TOCPU1IPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU2TOCPU1IPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU2TOCPU1IPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU2TOCPU1IPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU2TOCPU1IPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU2TOCPU1IPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU2TOCPU1IPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU2TOCPU1IPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU2TOCPU1IPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU2TOCPU1IPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU2TOCPU1IPCFLG.IPC31 Flag
};

union IPC_CPU2TOCPU1INTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU1INTIPCCLR_BITS  bit;
};

struct IPC_CPU2TOCPU1INTIPCFLG_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 CPU2 to CPU1 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 CPU2 to CPU1 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 CPU2 to CPU1 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 CPU2 to CPU1 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 CPU2 to CPU1 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 CPU2 to CPU1 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 CPU2 to CPU1 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 CPU2 to CPU1 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 CPU2 to CPU1 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 CPU2 to CPU1 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 CPU2 to CPU1 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 CPU2 to CPU1 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 CPU2 to CPU1 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 CPU2 to CPU1 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 CPU2 to CPU1 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 CPU2 to CPU1 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 CPU2 to CPU1 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 CPU2 to CPU1 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 CPU2 to CPU1 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 CPU2 to CPU1 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 CPU2 to CPU1 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 CPU2 to CPU1 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 CPU2 to CPU1 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 CPU2 to CPU1 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 CPU2 to CPU1 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 CPU2 to CPU1 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 CPU2 to CPU1 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 CPU2 to CPU1 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 CPU2 to CPU1 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 CPU2 to CPU1 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 CPU2 to CPU1 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 CPU2 to CPU1 IPC31 Flag Status
};

union IPC_CPU2TOCPU1INTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU1INTIPCFLG_BITS  bit;
};

struct CPU2_IPC_SEND_REGS_RegisterFile0_REGS {
    union   IPC_CPU2TOCPU1INTIPCSET_REG      CPU2TOCPU1INTIPCSET;          // CPU2TOCPU1INTIPCSET Register
    union   IPC_CPU2TOCPU1INTIPCCLR_REG      CPU2TOCPU1INTIPCCLR;          // CPU2TOCPU1INTIPCCLR Register
    union   IPC_CPU2TOCPU1INTIPCFLG_REG      CPU2TOCPU1INTIPCFLG;          // CPU2TOCPU1INTIPCFLG Register
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 CPU2TOCPU1INTIPCSENDCOM;      // CPU2TOCPU1INTIPCSENDCOM Register
    uint32_t                                 CPU2TOCPU1INTIPCSENDADDR;     // CPU2TOCPU1INTIPCSENDADDR Register
    uint32_t                                 CPU2TOCPU1INTIPCSENDDATA;     // CPU2TOCPU1INTIPCSENDDATA Register
    uint32_t                                 CPU1TOCPU2INTREMOTEREPLY;     // CPU1TOCPU2INTREMOTEREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU2TOCPU3INTIPCSET_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU2TOCPU3INTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU3INTIPCSET_BITS  bit;
};

struct IPC_CPU2TOCPU3INTIPCCLR_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU2TOCPU3IPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU2TOCPU3IPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU2TOCPU3IPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU2TOCPU3IPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU2TOCPU3IPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU2TOCPU3IPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU2TOCPU3IPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU2TOCPU3IPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU2TOCPU3IPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU2TOCPU3IPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU2TOCPU3IPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU2TOCPU3IPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU2TOCPU3IPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU2TOCPU3IPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU2TOCPU3IPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU2TOCPU3IPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU2TOCPU3IPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU2TOCPU3IPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU2TOCPU3IPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU2TOCPU3IPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU2TOCPU3IPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU2TOCPU3IPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU2TOCPU3IPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU2TOCPU3IPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU2TOCPU3IPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU2TOCPU3IPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU2TOCPU3IPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU2TOCPU3IPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU2TOCPU3IPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU2TOCPU3IPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU2TOCPU3IPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU2TOCPU3IPCFLG.IPC31 Flag
};

union IPC_CPU2TOCPU3INTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU3INTIPCCLR_BITS  bit;
};

struct IPC_CPU2TOCPU3INTIPCFLG_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 CPU2 to CPU3 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 CPU2 to CPU3 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 CPU2 to CPU3 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 CPU2 to CPU3 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 CPU2 to CPU3 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 CPU2 to CPU3 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 CPU2 to CPU3 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 CPU2 to CPU3 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 CPU2 to CPU3 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 CPU2 to CPU3 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 CPU2 to CPU3 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 CPU2 to CPU3 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 CPU2 to CPU3 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 CPU2 to CPU3 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 CPU2 to CPU3 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 CPU2 to CPU3 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 CPU2 to CPU3 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 CPU2 to CPU3 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 CPU2 to CPU3 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 CPU2 to CPU3 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 CPU2 to CPU3 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 CPU2 to CPU3 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 CPU2 to CPU3 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 CPU2 to CPU3 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 CPU2 to CPU3 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 CPU2 to CPU3 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 CPU2 to CPU3 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 CPU2 to CPU3 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 CPU2 to CPU3 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 CPU2 to CPU3 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 CPU2 to CPU3 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 CPU2 to CPU3 IPC31 Flag Status
};

union IPC_CPU2TOCPU3INTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU3INTIPCFLG_BITS  bit;
};

struct CPU2_IPC_SEND_REGS_RegisterFile1_REGS {
    union   IPC_CPU2TOCPU3INTIPCSET_REG      CPU2TOCPU3INTIPCSET;          // CPU2TOCPU3INTIPCSET Register
    union   IPC_CPU2TOCPU3INTIPCCLR_REG      CPU2TOCPU3INTIPCCLR;          // CPU2TOCPU3INTIPCCLR Register
    union   IPC_CPU2TOCPU3INTIPCFLG_REG      CPU2TOCPU3INTIPCFLG;          // CPU2TOCPU3INTIPCFLG Register
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 CPU2TOCPU3INTIPCSENDCOM;      // CPU2TOCPU3INTIPCSENDCOM Register
    uint32_t                                 CPU2TOCPU3INTIPCSENDADDR;     // CPU2TOCPU3INTIPCSENDADDR Register
    uint32_t                                 CPU2TOCPU3INTIPCSENDDATA;     // CPU2TOCPU3INTIPCSENDDATA Register
    uint32_t                                 CPU3TOCPU2INTREMOTEREPLY;     // CPU3TOCPU2INTREMOTEREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU2TOHSMINTIPCSET_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU2TOHSMINTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU2TOHSMINTIPCSET_BITS  bit;
};

struct IPC_CPU2TOHSMINTIPCCLR_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU2TOHSMIPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU2TOHSMIPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU2TOHSMIPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU2TOHSMIPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU2TOHSMIPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU2TOHSMIPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU2TOHSMIPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU2TOHSMIPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU2TOHSMIPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU2TOHSMIPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU2TOHSMIPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU2TOHSMIPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU2TOHSMIPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU2TOHSMIPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU2TOHSMIPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU2TOHSMIPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU2TOHSMIPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU2TOHSMIPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU2TOHSMIPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU2TOHSMIPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU2TOHSMIPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU2TOHSMIPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU2TOHSMIPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU2TOHSMIPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU2TOHSMIPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU2TOHSMIPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU2TOHSMIPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU2TOHSMIPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU2TOHSMIPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU2TOHSMIPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU2TOHSMIPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU2TOHSMIPCFLG.IPC31 Flag
};

union IPC_CPU2TOHSMINTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU2TOHSMINTIPCCLR_BITS  bit;
};

struct IPC_CPU2TOHSMINTIPCFLG_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 HSM to CPU2 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 HSM to CPU2 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 HSM to CPU2 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 HSM to CPU2 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 HSM to CPU2 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 HSM to CPU2 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 HSM to CPU2 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 HSM to CPU2 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 HSM to CPU2 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 HSM to CPU2 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 HSM to CPU2 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 HSM to CPU2 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 HSM to CPU2 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 HSM to CPU2 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 HSM to CPU2 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 HSM to CPU2 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 HSM to CPU2 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 HSM to CPU2 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 HSM to CPU2 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 HSM to CPU2 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 HSM to CPU2 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 HSM to CPU2 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 HSM to CPU2 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 HSM to CPU2 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 HSM to CPU2 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 HSM to CPU2 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 HSM to CPU2 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 HSM to CPU2 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 HSM to CPU2 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 HSM to CPU2 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 HSM to CPU2 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 HSM to CPU2 IPC31 Flag Status
};

union IPC_CPU2TOHSMINTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU2TOHSMINTIPCFLG_BITS  bit;
};

struct CPU2_IPC_SEND_REGS_RegisterFile2_REGS {
    union   IPC_CPU2TOHSMINTIPCSET_REG       CPU2TOHSMINTIPCSET;           // CPU2TOHSMINTIPCSET Register
    union   IPC_CPU2TOHSMINTIPCCLR_REG       CPU2TOHSMINTIPCCLR;           // CPU2TOHSMINTIPCCLR Register
    union   IPC_CPU2TOHSMINTIPCFLG_REG       CPU2TOHSMINTIPCFLG;           // CPU2TOHSMINTIPCFLG Register
    uint8_t                                  rsvd1[4084];                  // Reserved
};

struct CPU2_IPC_SEND_REGS {
    struct CPU2_IPC_SEND_REGS_RegisterFile0_REGS CPU2_IPC_SEND_RegisterFile0[4]; // 
    struct CPU2_IPC_SEND_REGS_RegisterFile1_REGS CPU2_IPC_SEND_RegisterFile1[4]; // 
    uint8_t                                  rsvd1[8192];                  // Reserved
    struct CPU2_IPC_SEND_REGS_RegisterFile2_REGS CPU2_IPC_SEND_RegisterFile2[2]; // 
};

struct IPC_CPU1TOCPU2INTIPCSTS_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Local IPC Flag 0 Status
    uint16_t IPC1:1;                    // 1 Local IPC Flag 1 Status
    uint16_t IPC2:1;                    // 2 Local IPC Flag 2 Status
    uint16_t IPC3:1;                    // 3 Local IPC Flag 3 Status
    uint16_t IPC4:1;                    // 4 Local IPC Flag 4 Status
    uint16_t IPC5:1;                    // 5 Local IPC Flag 5 Status
    uint16_t IPC6:1;                    // 6 Local IPC Flag 6 Status
    uint16_t IPC7:1;                    // 7 Local IPC Flag 7 Status
    uint16_t IPC8:1;                    // 8 Local IPC Flag 8 Status
    uint16_t IPC9:1;                    // 9 Local IPC Flag 9 Status
    uint16_t IPC10:1;                   // 10 Local IPC Flag 10 Status
    uint16_t IPC11:1;                   // 11 Local IPC Flag 11 Status
    uint16_t IPC12:1;                   // 12 Local IPC Flag 12 Status
    uint16_t IPC13:1;                   // 13 Local IPC Flag 13 Status
    uint16_t IPC14:1;                   // 14 Local IPC Flag 14 Status
    uint16_t IPC15:1;                   // 15 Local IPC Flag 15 Status
    uint16_t IPC16:1;                   // 16 Local IPC Flag 16 Status
    uint16_t IPC17:1;                   // 17 Local IPC Flag 17 Status
    uint16_t IPC18:1;                   // 18 Local IPC Flag 18 Status
    uint16_t IPC19:1;                   // 19 Local IPC Flag 19 Status
    uint16_t IPC20:1;                   // 20 Local IPC Flag 20 Status
    uint16_t IPC21:1;                   // 21 Local IPC Flag 21 Status
    uint16_t IPC22:1;                   // 22 Local IPC Flag 22 Status
    uint16_t IPC23:1;                   // 23 Local IPC Flag 23 Status
    uint16_t IPC24:1;                   // 24 Local IPC Flag 24 Status
    uint16_t IPC25:1;                   // 25 Local IPC Flag 25 Status
    uint16_t IPC26:1;                   // 26 Local IPC Flag 26 Status
    uint16_t IPC27:1;                   // 27 Local IPC Flag 27 Status
    uint16_t IPC28:1;                   // 28 Local IPC Flag 28 Status
    uint16_t IPC29:1;                   // 29 Local IPC Flag 29 Status
    uint16_t IPC30:1;                   // 30 Local IPC Flag 30 Status
    uint16_t IPC31:1;                   // 31 Local IPC Flag 31 Status
};

union IPC_CPU1TOCPU2INTIPCSTS_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU2INTIPCSTS_BITS  bit;
};

struct IPC_CPU2TOCPU1INTIPCACK_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC0 bit
    uint16_t IPC1:1;                    // 1 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC1 bit
    uint16_t IPC2:1;                    // 2 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC2 bit
    uint16_t IPC3:1;                    // 3 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC3 bit
    uint16_t IPC4:1;                    // 4 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC4 bit
    uint16_t IPC5:1;                    // 5 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC5 bit
    uint16_t IPC6:1;                    // 6 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC6 bit
    uint16_t IPC7:1;                    // 7 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC7 bit
    uint16_t IPC8:1;                    // 8 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC8 bit
    uint16_t IPC9:1;                    // 9 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC9 bit
    uint16_t IPC10:1;                   // 10 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC10 bit
    uint16_t IPC11:1;                   // 11 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC11 bit
    uint16_t IPC12:1;                   // 12 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC12 bit
    uint16_t IPC13:1;                   // 13 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC13 bit
    uint16_t IPC14:1;                   // 14 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC14 bit
    uint16_t IPC15:1;                   // 15 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC15 bit
    uint16_t IPC16:1;                   // 16 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC16 bit
    uint16_t IPC17:1;                   // 17 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC17 bit
    uint16_t IPC18:1;                   // 18 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC18 bit
    uint16_t IPC19:1;                   // 19 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC19 bit
    uint16_t IPC20:1;                   // 20 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC20 bit
    uint16_t IPC21:1;                   // 21 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC21 bit
    uint16_t IPC22:1;                   // 22 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC22 bit
    uint16_t IPC23:1;                   // 23 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC23 bit
    uint16_t IPC24:1;                   // 24 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC24 bit
    uint16_t IPC25:1;                   // 25 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC25 bit
    uint16_t IPC26:1;                   // 26 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC26 bit
    uint16_t IPC27:1;                   // 27 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC27 bit
    uint16_t IPC28:1;                   // 28 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC28 bit
    uint16_t IPC29:1;                   // 29 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC29 bit
    uint16_t IPC30:1;                   // 30 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC30 bit
    uint16_t IPC31:1;                   // 31 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC31 bit
};

union IPC_CPU2TOCPU1INTIPCACK_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU1INTIPCACK_BITS  bit;
};

struct CPU2_IPC_RCV_REGS_RegisterFile0_REGS {
    union   IPC_CPU1TOCPU2INTIPCSTS_REG      CPU1TOCPU2INTIPCSTS;          // CPU1TOCPU2INTIPCSTS Register
    union   IPC_CPU2TOCPU1INTIPCACK_REG      CPU2TOCPU1INTIPCACK;          // CPU2TOCPU1INTIPCACK Register
    uint8_t                                  rsvd1[8];                     // Reserved
    uint32_t                                 CPU1TOCPU2INTIPCRECVCOM;      // CPU1TOCPU2INTIPCRECVCOM Register
    uint32_t                                 CPU1TOCPU2INTIPCRECVADDR;     // CPU1TOCPU2INTIPCRECVADDR Register
    uint32_t                                 CPU1TOCPU2INTIPCRECVDATA;     // CPU1TOCPU2INTIPCRECVDATA Register
    uint32_t                                 CPU2TOCPU1INTLOCALREPLY;      // CPU2TOCPU1INTLOCALREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU3TOCPU2INTIPCSTS_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Local IPC Flag 0 Status
    uint16_t IPC1:1;                    // 1 Local IPC Flag 1 Status
    uint16_t IPC2:1;                    // 2 Local IPC Flag 2 Status
    uint16_t IPC3:1;                    // 3 Local IPC Flag 3 Status
    uint16_t IPC4:1;                    // 4 Local IPC Flag 4 Status
    uint16_t IPC5:1;                    // 5 Local IPC Flag 5 Status
    uint16_t IPC6:1;                    // 6 Local IPC Flag 6 Status
    uint16_t IPC7:1;                    // 7 Local IPC Flag 7 Status
    uint16_t IPC8:1;                    // 8 Local IPC Flag 8 Status
    uint16_t IPC9:1;                    // 9 Local IPC Flag 9 Status
    uint16_t IPC10:1;                   // 10 Local IPC Flag 10 Status
    uint16_t IPC11:1;                   // 11 Local IPC Flag 11 Status
    uint16_t IPC12:1;                   // 12 Local IPC Flag 12 Status
    uint16_t IPC13:1;                   // 13 Local IPC Flag 13 Status
    uint16_t IPC14:1;                   // 14 Local IPC Flag 14 Status
    uint16_t IPC15:1;                   // 15 Local IPC Flag 15 Status
    uint16_t IPC16:1;                   // 16 Local IPC Flag 16 Status
    uint16_t IPC17:1;                   // 17 Local IPC Flag 17 Status
    uint16_t IPC18:1;                   // 18 Local IPC Flag 18 Status
    uint16_t IPC19:1;                   // 19 Local IPC Flag 19 Status
    uint16_t IPC20:1;                   // 20 Local IPC Flag 20 Status
    uint16_t IPC21:1;                   // 21 Local IPC Flag 21 Status
    uint16_t IPC22:1;                   // 22 Local IPC Flag 22 Status
    uint16_t IPC23:1;                   // 23 Local IPC Flag 23 Status
    uint16_t IPC24:1;                   // 24 Local IPC Flag 24 Status
    uint16_t IPC25:1;                   // 25 Local IPC Flag 25 Status
    uint16_t IPC26:1;                   // 26 Local IPC Flag 26 Status
    uint16_t IPC27:1;                   // 27 Local IPC Flag 27 Status
    uint16_t IPC28:1;                   // 28 Local IPC Flag 28 Status
    uint16_t IPC29:1;                   // 29 Local IPC Flag 29 Status
    uint16_t IPC30:1;                   // 30 Local IPC Flag 30 Status
    uint16_t IPC31:1;                   // 31 Local IPC Flag 31 Status
};

union IPC_CPU3TOCPU2INTIPCSTS_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU2INTIPCSTS_BITS  bit;
};

struct IPC_CPU2TOCPU3INTIPCACK_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC0 bit
    uint16_t IPC1:1;                    // 1 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC1 bit
    uint16_t IPC2:1;                    // 2 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC2 bit
    uint16_t IPC3:1;                    // 3 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC3 bit
    uint16_t IPC4:1;                    // 4 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC4 bit
    uint16_t IPC5:1;                    // 5 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC5 bit
    uint16_t IPC6:1;                    // 6 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC6 bit
    uint16_t IPC7:1;                    // 7 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC7 bit
    uint16_t IPC8:1;                    // 8 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC8 bit
    uint16_t IPC9:1;                    // 9 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC9 bit
    uint16_t IPC10:1;                   // 10 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC10 bit
    uint16_t IPC11:1;                   // 11 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC11 bit
    uint16_t IPC12:1;                   // 12 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC12 bit
    uint16_t IPC13:1;                   // 13 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC13 bit
    uint16_t IPC14:1;                   // 14 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC14 bit
    uint16_t IPC15:1;                   // 15 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC15 bit
    uint16_t IPC16:1;                   // 16 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC16 bit
    uint16_t IPC17:1;                   // 17 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC17 bit
    uint16_t IPC18:1;                   // 18 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC18 bit
    uint16_t IPC19:1;                   // 19 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC19 bit
    uint16_t IPC20:1;                   // 20 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC20 bit
    uint16_t IPC21:1;                   // 21 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC21 bit
    uint16_t IPC22:1;                   // 22 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC22 bit
    uint16_t IPC23:1;                   // 23 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC23 bit
    uint16_t IPC24:1;                   // 24 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC24 bit
    uint16_t IPC25:1;                   // 25 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC25 bit
    uint16_t IPC26:1;                   // 26 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC26 bit
    uint16_t IPC27:1;                   // 27 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC27 bit
    uint16_t IPC28:1;                   // 28 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC28 bit
    uint16_t IPC29:1;                   // 29 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC29 bit
    uint16_t IPC30:1;                   // 30 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC30 bit
    uint16_t IPC31:1;                   // 31 Acknowledgement from CPU3 to CPU2TOCPU3IPCFLG.IPC31 bit
};

union IPC_CPU2TOCPU3INTIPCACK_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU3INTIPCACK_BITS  bit;
};

struct CPU2_IPC_RCV_REGS_RegisterFile1_REGS {
    union   IPC_CPU3TOCPU2INTIPCSTS_REG      CPU3TOCPU2INTIPCSTS;          // CPU3TOCPU2INTIPCSTS Register
    union   IPC_CPU2TOCPU3INTIPCACK_REG      CPU2TOCPU3INTIPCACK;          // CPU2TOCPU3INTIPCACK Register
    uint8_t                                  rsvd1[8];                     // Reserved
    uint32_t                                 CPU3TOCPU2INTIPCRECVCOM;      // CPU3TOCPU2INTIPCRECVCOM Register
    uint32_t                                 CPU3TOCPU2INTIPCRECVADDR;     // CPU3TOCPU2INTIPCRECVADDR Register
    uint32_t                                 CPU3TOCPU2INTIPCRECVDATA;     // CPU3TOCPU2INTIPCRECVDATA Register
    uint32_t                                 CPU2TOCPU3INTLOCALREPLY;      // CPU2TOCPU3INTLOCALREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct CPU2_IPC_RCV_REGS {
    struct CPU2_IPC_RCV_REGS_RegisterFile0_REGS CPU2_IPC_RCV_RegisterFile0[4]; // 
    struct CPU2_IPC_RCV_REGS_RegisterFile1_REGS CPU2_IPC_RCV_RegisterFile1[4]; // 
};

struct IPC_CPU3TOCPU1INTIPCSET_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU3TOCPU1INTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU1INTIPCSET_BITS  bit;
};

struct IPC_CPU3TOCPU1INTIPCCLR_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU3TOCPU1IPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU3TOCPU1IPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU3TOCPU1IPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU3TOCPU1IPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU3TOCPU1IPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU3TOCPU1IPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU3TOCPU1IPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU3TOCPU1IPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU3TOCPU1IPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU3TOCPU1IPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU3TOCPU1IPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU3TOCPU1IPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU3TOCPU1IPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU3TOCPU1IPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU3TOCPU1IPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU3TOCPU1IPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU3TOCPU1IPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU3TOCPU1IPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU3TOCPU1IPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU3TOCPU1IPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU3TOCPU1IPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU3TOCPU1IPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU3TOCPU1IPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU3TOCPU1IPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU3TOCPU1IPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU3TOCPU1IPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU3TOCPU1IPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU3TOCPU1IPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU3TOCPU1IPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU3TOCPU1IPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU3TOCPU1IPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU3TOCPU1IPCFLG.IPC31 Flag
};

union IPC_CPU3TOCPU1INTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU1INTIPCCLR_BITS  bit;
};

struct IPC_CPU3TOCPU1INTIPCFLG_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 CPU3 to CPU1 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 CPU3 to CPU1 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 CPU3 to CPU1 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 CPU3 to CPU1 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 CPU3 to CPU1 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 CPU3 to CPU1 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 CPU3 to CPU1 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 CPU3 to CPU1 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 CPU3 to CPU1 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 CPU3 to CPU1 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 CPU3 to CPU1 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 CPU3 to CPU1 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 CPU3 to CPU1 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 CPU3 to CPU1 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 CPU3 to CPU1 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 CPU3 to CPU1 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 CPU3 to CPU1 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 CPU3 to CPU1 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 CPU3 to CPU1 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 CPU3 to CPU1 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 CPU3 to CPU1 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 CPU3 to CPU1 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 CPU3 to CPU1 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 CPU3 to CPU1 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 CPU3 to CPU1 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 CPU3 to CPU1 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 CPU3 to CPU1 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 CPU3 to CPU1 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 CPU3 to CPU1 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 CPU3 to CPU1 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 CPU3 to CPU1 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 CPU3 to CPU1 IPC31 Flag Status
};

union IPC_CPU3TOCPU1INTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU1INTIPCFLG_BITS  bit;
};

struct CPU3_IPC_SEND_REGS_RegisterFile0_REGS {
    union   IPC_CPU3TOCPU1INTIPCSET_REG      CPU3TOCPU1INTIPCSET;          // CPU3TOCPU1INTIPCSET Register
    union   IPC_CPU3TOCPU1INTIPCCLR_REG      CPU3TOCPU1INTIPCCLR;          // CPU3TOCPU1INTIPCCLR Register
    union   IPC_CPU3TOCPU1INTIPCFLG_REG      CPU3TOCPU1INTIPCFLG;          // CPU3TOCPU1INTIPCFLG Register
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 CPU3TOCPU1INTIPCSENDCOM;      // CPU3TOCPU1INTIPCSENDCOM Register
    uint32_t                                 CPU3TOCPU1INTIPCSENDADDR;     // CPU3TOCPU1INTIPCSENDADDR Register
    uint32_t                                 CPU3TOCPU1INTIPCSENDDATA;     // CPU3TOCPU1INTIPCSENDDATA Register
    uint32_t                                 CPU1TOCPU3INTREMOTEREPLY;     // CPU1TOCPU3INTREMOTEREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU3TOCPU2INTIPCSET_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU3TOCPU2INTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU2INTIPCSET_BITS  bit;
};

struct IPC_CPU3TOCPU2INTIPCCLR_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU3TOCPU2IPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU3TOCPU2IPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU3TOCPU2IPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU3TOCPU2IPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU3TOCPU2IPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU3TOCPU2IPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU3TOCPU2IPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU3TOCPU2IPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU3TOCPU2IPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU3TOCPU2IPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU3TOCPU2IPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU3TOCPU2IPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU3TOCPU2IPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU3TOCPU2IPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU3TOCPU2IPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU3TOCPU2IPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU3TOCPU2IPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU3TOCPU2IPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU3TOCPU2IPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU3TOCPU2IPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU3TOCPU2IPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU3TOCPU2IPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU3TOCPU2IPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU3TOCPU2IPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU3TOCPU2IPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU3TOCPU2IPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU3TOCPU2IPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU3TOCPU2IPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU3TOCPU2IPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU3TOCPU2IPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU3TOCPU2IPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU3TOCPU2IPCFLG.IPC31 Flag
};

union IPC_CPU3TOCPU2INTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU2INTIPCCLR_BITS  bit;
};

struct IPC_CPU3TOCPU2INTIPCFLG_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 CPU3 to CPU2 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 CPU3 to CPU2 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 CPU3 to CPU2 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 CPU3 to CPU2 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 CPU3 to CPU2 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 CPU3 to CPU2 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 CPU3 to CPU2 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 CPU3 to CPU2 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 CPU3 to CPU2 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 CPU3 to CPU2 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 CPU3 to CPU2 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 CPU3 to CPU2 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 CPU3 to CPU2 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 CPU3 to CPU2 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 CPU3 to CPU2 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 CPU3 to CPU2 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 CPU3 to CPU2 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 CPU3 to CPU2 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 CPU3 to CPU2 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 CPU3 to CPU2 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 CPU3 to CPU2 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 CPU3 to CPU2 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 CPU3 to CPU2 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 CPU3 to CPU2 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 CPU3 to CPU2 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 CPU3 to CPU2 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 CPU3 to CPU2 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 CPU3 to CPU2 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 CPU3 to CPU2 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 CPU3 to CPU2 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 CPU3 to CPU2 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 CPU3 to CPU2 IPC31 Flag Status
};

union IPC_CPU3TOCPU2INTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU2INTIPCFLG_BITS  bit;
};

struct CPU3_IPC_SEND_REGS_RegisterFile1_REGS {
    union   IPC_CPU3TOCPU2INTIPCSET_REG      CPU3TOCPU2INTIPCSET;          // CPU3TOCPU2INTIPCSET Register
    union   IPC_CPU3TOCPU2INTIPCCLR_REG      CPU3TOCPU2INTIPCCLR;          // CPU3TOCPU2INTIPCCLR Register
    union   IPC_CPU3TOCPU2INTIPCFLG_REG      CPU3TOCPU2INTIPCFLG;          // CPU3TOCPU2INTIPCFLG Register
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 CPU3TOCPU2INTIPCSENDCOM;      // CPU3TOCPU2INTIPCSENDCOM Register
    uint32_t                                 CPU3TOCPU2INTIPCSENDADDR;     // CPU3TOCPU2INTIPCSENDADDR Register
    uint32_t                                 CPU3TOCPU2INTIPCSENDDATA;     // CPU3TOCPU2INTIPCSENDDATA Register
    uint32_t                                 CPU2TOCPU3INTREMOTEREPLY;     // CPU2TOCPU3INTREMOTEREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU3TOHSMINTIPCSET_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 Set Remote IPC0 Flag
    uint16_t IPC1:1;                    // 1 Set Remote IPC1 Flag
    uint16_t IPC2:1;                    // 2 Set Remote IPC2 Flag
    uint16_t IPC3:1;                    // 3 Set Remote IPC3 Flag
    uint16_t IPC4:1;                    // 4 Set Remote IPC4 Flag
    uint16_t IPC5:1;                    // 5 Set Remote IPC5 Flag
    uint16_t IPC6:1;                    // 6 Set Remote IPC6 Flag
    uint16_t IPC7:1;                    // 7 Set Remote IPC7 Flag
    uint16_t IPC8:1;                    // 8 Set Remote IPC8 Flag
    uint16_t IPC9:1;                    // 9 Set Remote IPC9 Flag
    uint16_t IPC10:1;                   // 10 Set Remote IPC10 Flag
    uint16_t IPC11:1;                   // 11 Set Remote IPC11 Flag
    uint16_t IPC12:1;                   // 12 Set Remote IPC12 Flag
    uint16_t IPC13:1;                   // 13 Set Remote IPC13 Flag
    uint16_t IPC14:1;                   // 14 Set Remote IPC14 Flag
    uint16_t IPC15:1;                   // 15 Set Remote IPC15 Flag
    uint16_t IPC16:1;                   // 16 Set Remote IPC16 Flag
    uint16_t IPC17:1;                   // 17 Set Remote IPC17 Flag
    uint16_t IPC18:1;                   // 18 Set Remote IPC18 Flag
    uint16_t IPC19:1;                   // 19 Set Remote IPC19 Flag
    uint16_t IPC20:1;                   // 20 Set Remote IPC20 Flag
    uint16_t IPC21:1;                   // 21 Set Remote IPC21 Flag
    uint16_t IPC22:1;                   // 22 Set Remote IPC22 Flag
    uint16_t IPC23:1;                   // 23 Set Remote IPC23 Flag
    uint16_t IPC24:1;                   // 24 Set Remote IPC24 Flag
    uint16_t IPC25:1;                   // 25 Set Remote IPC25 Flag
    uint16_t IPC26:1;                   // 26 Set Remote IPC26 Flag
    uint16_t IPC27:1;                   // 27 Set Remote IPC27 Flag
    uint16_t IPC28:1;                   // 28 Set Remote IPC28 Flag
    uint16_t IPC29:1;                   // 29 Set Remote IPC29 Flag
    uint16_t IPC30:1;                   // 30 Set Remote IPC30 Flag
    uint16_t IPC31:1;                   // 31 Set Remote IPC31 Flag
};

union IPC_CPU3TOHSMINTIPCSET_REG {
    uint32_t  all;
    struct  IPC_CPU3TOHSMINTIPCSET_BITS  bit;
};

struct IPC_CPU3TOHSMINTIPCCLR_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 Clear CPU3TOHSMIPCFLG.IPC0 Flag
    uint16_t IPC1:1;                    // 1 Clear CPU3TOHSMIPCFLG.IPC1 Flag
    uint16_t IPC2:1;                    // 2 Clear CPU3TOHSMIPCFLG.IPC2 Flag
    uint16_t IPC3:1;                    // 3 Clear CPU3TOHSMIPCFLG.IPC3 Flag
    uint16_t IPC4:1;                    // 4 Clear CPU3TOHSMIPCFLG.IPC4 Flag
    uint16_t IPC5:1;                    // 5 Clear CPU3TOHSMIPCFLG.IPC5 Flag
    uint16_t IPC6:1;                    // 6 Clear CPU3TOHSMIPCFLG.IPC6 Flag
    uint16_t IPC7:1;                    // 7 Clear CPU3TOHSMIPCFLG.IPC7 Flag
    uint16_t IPC8:1;                    // 8 Clear CPU3TOHSMIPCFLG.IPC8 Flag
    uint16_t IPC9:1;                    // 9 Clear CPU3TOHSMIPCFLG.IPC9 Flag
    uint16_t IPC10:1;                   // 10 Clear CPU3TOHSMIPCFLG.IPC10 Flag
    uint16_t IPC11:1;                   // 11 Clear CPU3TOHSMIPCFLG.IPC11 Flag
    uint16_t IPC12:1;                   // 12 Clear CPU3TOHSMIPCFLG.IPC12 Flag
    uint16_t IPC13:1;                   // 13 Clear CPU3TOHSMIPCFLG.IPC13 Flag
    uint16_t IPC14:1;                   // 14 Clear CPU3TOHSMIPCFLG.IPC14 Flag
    uint16_t IPC15:1;                   // 15 Clear CPU3TOHSMIPCFLG.IPC15 Flag
    uint16_t IPC16:1;                   // 16 Clear CPU3TOHSMIPCFLG.IPC16 Flag
    uint16_t IPC17:1;                   // 17 Clear CPU3TOHSMIPCFLG.IPC17 Flag
    uint16_t IPC18:1;                   // 18 Clear CPU3TOHSMIPCFLG.IPC18 Flag
    uint16_t IPC19:1;                   // 19 Clear CPU3TOHSMIPCFLG.IPC19 Flag
    uint16_t IPC20:1;                   // 20 Clear CPU3TOHSMIPCFLG.IPC20 Flag
    uint16_t IPC21:1;                   // 21 Clear CPU3TOHSMIPCFLG.IPC21 Flag
    uint16_t IPC22:1;                   // 22 Clear CPU3TOHSMIPCFLG.IPC22 Flag
    uint16_t IPC23:1;                   // 23 Clear CPU3TOHSMIPCFLG.IPC23 Flag
    uint16_t IPC24:1;                   // 24 Clear CPU3TOHSMIPCFLG.IPC24 Flag
    uint16_t IPC25:1;                   // 25 Clear CPU3TOHSMIPCFLG.IPC25 Flag
    uint16_t IPC26:1;                   // 26 Clear CPU3TOHSMIPCFLG.IPC26 Flag
    uint16_t IPC27:1;                   // 27 Clear CPU3TOHSMIPCFLG.IPC27 Flag
    uint16_t IPC28:1;                   // 28 Clear CPU3TOHSMIPCFLG.IPC28 Flag
    uint16_t IPC29:1;                   // 29 Clear CPU3TOHSMIPCFLG.IPC29 Flag
    uint16_t IPC30:1;                   // 30 Clear CPU3TOHSMIPCFLG.IPC30 Flag
    uint16_t IPC31:1;                   // 31 Clear CPU3TOHSMIPCFLG.IPC31 Flag
};

union IPC_CPU3TOHSMINTIPCCLR_REG {
    uint32_t  all;
    struct  IPC_CPU3TOHSMINTIPCCLR_BITS  bit;
};

struct IPC_CPU3TOHSMINTIPCFLG_BITS {    // bits description
    uint16_t IPC0:1;                    // 0 HSM to CPU3 IPC0 Flag Status
    uint16_t IPC1:1;                    // 1 HSM to CPU3 IPC1 Flag Status
    uint16_t IPC2:1;                    // 2 HSM to CPU3 IPC2 Flag Status
    uint16_t IPC3:1;                    // 3 HSM to CPU3 IPC3 Flag Status
    uint16_t IPC4:1;                    // 4 HSM to CPU3 IPC4 Flag Status
    uint16_t IPC5:1;                    // 5 HSM to CPU3 IPC5 Flag Status
    uint16_t IPC6:1;                    // 6 HSM to CPU3 IPC6 Flag Status
    uint16_t IPC7:1;                    // 7 HSM to CPU3 IPC7 Flag Status
    uint16_t IPC8:1;                    // 8 HSM to CPU3 IPC8 Flag Status
    uint16_t IPC9:1;                    // 9 HSM to CPU3 IPC9 Flag Status
    uint16_t IPC10:1;                   // 10 HSM to CPU3 IPC10 Flag Status
    uint16_t IPC11:1;                   // 11 HSM to CPU3 IPC11 Flag Status
    uint16_t IPC12:1;                   // 12 HSM to CPU3 IPC12 Flag Status
    uint16_t IPC13:1;                   // 13 HSM to CPU3 IPC13 Flag Status
    uint16_t IPC14:1;                   // 14 HSM to CPU3 IPC14 Flag Status
    uint16_t IPC15:1;                   // 15 HSM to CPU3 IPC15 Flag Status
    uint16_t IPC16:1;                   // 16 HSM to CPU3 IPC16 Flag Status
    uint16_t IPC17:1;                   // 17 HSM to CPU3 IPC17 Flag Status
    uint16_t IPC18:1;                   // 18 HSM to CPU3 IPC18 Flag Status
    uint16_t IPC19:1;                   // 19 HSM to CPU3 IPC19 Flag Status
    uint16_t IPC20:1;                   // 20 HSM to CPU3 IPC20 Flag Status
    uint16_t IPC21:1;                   // 21 HSM to CPU3 IPC21 Flag Status
    uint16_t IPC22:1;                   // 22 HSM to CPU3 IPC22 Flag Status
    uint16_t IPC23:1;                   // 23 HSM to CPU3 IPC23 Flag Status
    uint16_t IPC24:1;                   // 24 HSM to CPU3 IPC24 Flag Status
    uint16_t IPC25:1;                   // 25 HSM to CPU3 IPC25 Flag Status
    uint16_t IPC26:1;                   // 26 HSM to CPU3 IPC26 Flag Status
    uint16_t IPC27:1;                   // 27 HSM to CPU3 IPC27 Flag Status
    uint16_t IPC28:1;                   // 28 HSM to CPU3 IPC28 Flag Status
    uint16_t IPC29:1;                   // 29 HSM to CPU3 IPC29 Flag Status
    uint16_t IPC30:1;                   // 30 HSM to CPU3 IPC30 Flag Status
    uint16_t IPC31:1;                   // 31 HSM to CPU3 IPC31 Flag Status
};

union IPC_CPU3TOHSMINTIPCFLG_REG {
    uint32_t  all;
    struct  IPC_CPU3TOHSMINTIPCFLG_BITS  bit;
};

struct CPU3_IPC_SEND_REGS_RegisterFile2_REGS {
    union   IPC_CPU3TOHSMINTIPCSET_REG       CPU3TOHSMINTIPCSET;           // CPU3TOHSMINTIPCSET Register
    union   IPC_CPU3TOHSMINTIPCCLR_REG       CPU3TOHSMINTIPCCLR;           // CPU3TOHSMINTIPCCLR Register
    union   IPC_CPU3TOHSMINTIPCFLG_REG       CPU3TOHSMINTIPCFLG;           // CPU3TOHSMINTIPCFLG Register
    uint8_t                                  rsvd1[4084];                  // Reserved
};

struct CPU3_IPC_SEND_REGS {
    struct CPU3_IPC_SEND_REGS_RegisterFile0_REGS CPU3_IPC_SEND_RegisterFile0[4]; // 
    struct CPU3_IPC_SEND_REGS_RegisterFile1_REGS CPU3_IPC_SEND_RegisterFile1[4]; // 
    uint8_t                                  rsvd1[8192];                  // Reserved
    struct CPU3_IPC_SEND_REGS_RegisterFile2_REGS CPU3_IPC_SEND_RegisterFile2[2]; // 
};

struct IPC_CPU1TOCPU3INTIPCSTS_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Local IPC Flag 0 Status
    uint16_t IPC1:1;                    // 1 Local IPC Flag 1 Status
    uint16_t IPC2:1;                    // 2 Local IPC Flag 2 Status
    uint16_t IPC3:1;                    // 3 Local IPC Flag 3 Status
    uint16_t IPC4:1;                    // 4 Local IPC Flag 4 Status
    uint16_t IPC5:1;                    // 5 Local IPC Flag 5 Status
    uint16_t IPC6:1;                    // 6 Local IPC Flag 6 Status
    uint16_t IPC7:1;                    // 7 Local IPC Flag 7 Status
    uint16_t IPC8:1;                    // 8 Local IPC Flag 8 Status
    uint16_t IPC9:1;                    // 9 Local IPC Flag 9 Status
    uint16_t IPC10:1;                   // 10 Local IPC Flag 10 Status
    uint16_t IPC11:1;                   // 11 Local IPC Flag 11 Status
    uint16_t IPC12:1;                   // 12 Local IPC Flag 12 Status
    uint16_t IPC13:1;                   // 13 Local IPC Flag 13 Status
    uint16_t IPC14:1;                   // 14 Local IPC Flag 14 Status
    uint16_t IPC15:1;                   // 15 Local IPC Flag 15 Status
    uint16_t IPC16:1;                   // 16 Local IPC Flag 16 Status
    uint16_t IPC17:1;                   // 17 Local IPC Flag 17 Status
    uint16_t IPC18:1;                   // 18 Local IPC Flag 18 Status
    uint16_t IPC19:1;                   // 19 Local IPC Flag 19 Status
    uint16_t IPC20:1;                   // 20 Local IPC Flag 20 Status
    uint16_t IPC21:1;                   // 21 Local IPC Flag 21 Status
    uint16_t IPC22:1;                   // 22 Local IPC Flag 22 Status
    uint16_t IPC23:1;                   // 23 Local IPC Flag 23 Status
    uint16_t IPC24:1;                   // 24 Local IPC Flag 24 Status
    uint16_t IPC25:1;                   // 25 Local IPC Flag 25 Status
    uint16_t IPC26:1;                   // 26 Local IPC Flag 26 Status
    uint16_t IPC27:1;                   // 27 Local IPC Flag 27 Status
    uint16_t IPC28:1;                   // 28 Local IPC Flag 28 Status
    uint16_t IPC29:1;                   // 29 Local IPC Flag 29 Status
    uint16_t IPC30:1;                   // 30 Local IPC Flag 30 Status
    uint16_t IPC31:1;                   // 31 Local IPC Flag 31 Status
};

union IPC_CPU1TOCPU3INTIPCSTS_REG {
    uint32_t  all;
    struct  IPC_CPU1TOCPU3INTIPCSTS_BITS  bit;
};

struct IPC_CPU3TOCPU1INTIPCACK_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC0 bit
    uint16_t IPC1:1;                    // 1 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC1 bit
    uint16_t IPC2:1;                    // 2 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC2 bit
    uint16_t IPC3:1;                    // 3 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC3 bit
    uint16_t IPC4:1;                    // 4 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC4 bit
    uint16_t IPC5:1;                    // 5 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC5 bit
    uint16_t IPC6:1;                    // 6 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC6 bit
    uint16_t IPC7:1;                    // 7 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC7 bit
    uint16_t IPC8:1;                    // 8 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC8 bit
    uint16_t IPC9:1;                    // 9 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC9 bit
    uint16_t IPC10:1;                   // 10 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC10 bit
    uint16_t IPC11:1;                   // 11 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC11 bit
    uint16_t IPC12:1;                   // 12 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC12 bit
    uint16_t IPC13:1;                   // 13 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC13 bit
    uint16_t IPC14:1;                   // 14 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC14 bit
    uint16_t IPC15:1;                   // 15 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC15 bit
    uint16_t IPC16:1;                   // 16 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC16 bit
    uint16_t IPC17:1;                   // 17 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC17 bit
    uint16_t IPC18:1;                   // 18 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC18 bit
    uint16_t IPC19:1;                   // 19 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC19 bit
    uint16_t IPC20:1;                   // 20 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC20 bit
    uint16_t IPC21:1;                   // 21 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC21 bit
    uint16_t IPC22:1;                   // 22 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC22 bit
    uint16_t IPC23:1;                   // 23 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC23 bit
    uint16_t IPC24:1;                   // 24 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC24 bit
    uint16_t IPC25:1;                   // 25 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC25 bit
    uint16_t IPC26:1;                   // 26 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC26 bit
    uint16_t IPC27:1;                   // 27 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC27 bit
    uint16_t IPC28:1;                   // 28 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC28 bit
    uint16_t IPC29:1;                   // 29 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC29 bit
    uint16_t IPC30:1;                   // 30 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC30 bit
    uint16_t IPC31:1;                   // 31 Acknowledgement from CPU1 to CPU3TOCPU1IPCFLG.IPC31 bit
};

union IPC_CPU3TOCPU1INTIPCACK_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU1INTIPCACK_BITS  bit;
};

struct CPU3_IPC_RCV_REGS_RegisterFile0_REGS {
    union   IPC_CPU1TOCPU3INTIPCSTS_REG      CPU1TOCPU3INTIPCSTS;          // CPU1TOCPU3INTIPCSTS Register
    union   IPC_CPU3TOCPU1INTIPCACK_REG      CPU3TOCPU1INTIPCACK;          // CPU3TOCPU1INTIPCACK Register
    uint8_t                                  rsvd1[8];                     // Reserved
    uint32_t                                 CPU1TOCPU3INTIPCRECVCOM;      // CPU1TOCPU3INTIPCRECVCOM Register
    uint32_t                                 CPU1TOCPU3INTIPCRECVADDR;     // CPU1TOCPU3INTIPCRECVADDR Register
    uint32_t                                 CPU1TOCPU3INTIPCRECVDATA;     // CPU1TOCPU3INTIPCRECVDATA Register
    uint32_t                                 CPU3TOCPU1INTLOCALREPLY;      // CPU3TOCPU1INTLOCALREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct IPC_CPU2TOCPU3INTIPCSTS_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Local IPC Flag 0 Status
    uint16_t IPC1:1;                    // 1 Local IPC Flag 1 Status
    uint16_t IPC2:1;                    // 2 Local IPC Flag 2 Status
    uint16_t IPC3:1;                    // 3 Local IPC Flag 3 Status
    uint16_t IPC4:1;                    // 4 Local IPC Flag 4 Status
    uint16_t IPC5:1;                    // 5 Local IPC Flag 5 Status
    uint16_t IPC6:1;                    // 6 Local IPC Flag 6 Status
    uint16_t IPC7:1;                    // 7 Local IPC Flag 7 Status
    uint16_t IPC8:1;                    // 8 Local IPC Flag 8 Status
    uint16_t IPC9:1;                    // 9 Local IPC Flag 9 Status
    uint16_t IPC10:1;                   // 10 Local IPC Flag 10 Status
    uint16_t IPC11:1;                   // 11 Local IPC Flag 11 Status
    uint16_t IPC12:1;                   // 12 Local IPC Flag 12 Status
    uint16_t IPC13:1;                   // 13 Local IPC Flag 13 Status
    uint16_t IPC14:1;                   // 14 Local IPC Flag 14 Status
    uint16_t IPC15:1;                   // 15 Local IPC Flag 15 Status
    uint16_t IPC16:1;                   // 16 Local IPC Flag 16 Status
    uint16_t IPC17:1;                   // 17 Local IPC Flag 17 Status
    uint16_t IPC18:1;                   // 18 Local IPC Flag 18 Status
    uint16_t IPC19:1;                   // 19 Local IPC Flag 19 Status
    uint16_t IPC20:1;                   // 20 Local IPC Flag 20 Status
    uint16_t IPC21:1;                   // 21 Local IPC Flag 21 Status
    uint16_t IPC22:1;                   // 22 Local IPC Flag 22 Status
    uint16_t IPC23:1;                   // 23 Local IPC Flag 23 Status
    uint16_t IPC24:1;                   // 24 Local IPC Flag 24 Status
    uint16_t IPC25:1;                   // 25 Local IPC Flag 25 Status
    uint16_t IPC26:1;                   // 26 Local IPC Flag 26 Status
    uint16_t IPC27:1;                   // 27 Local IPC Flag 27 Status
    uint16_t IPC28:1;                   // 28 Local IPC Flag 28 Status
    uint16_t IPC29:1;                   // 29 Local IPC Flag 29 Status
    uint16_t IPC30:1;                   // 30 Local IPC Flag 30 Status
    uint16_t IPC31:1;                   // 31 Local IPC Flag 31 Status
};

union IPC_CPU2TOCPU3INTIPCSTS_REG {
    uint32_t  all;
    struct  IPC_CPU2TOCPU3INTIPCSTS_BITS  bit;
};

struct IPC_CPU3TOCPU2INTIPCACK_BITS {   // bits description
    uint16_t IPC0:1;                    // 0 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC0 bit
    uint16_t IPC1:1;                    // 1 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC1 bit
    uint16_t IPC2:1;                    // 2 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC2 bit
    uint16_t IPC3:1;                    // 3 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC3 bit
    uint16_t IPC4:1;                    // 4 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC4 bit
    uint16_t IPC5:1;                    // 5 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC5 bit
    uint16_t IPC6:1;                    // 6 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC6 bit
    uint16_t IPC7:1;                    // 7 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC7 bit
    uint16_t IPC8:1;                    // 8 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC8 bit
    uint16_t IPC9:1;                    // 9 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC9 bit
    uint16_t IPC10:1;                   // 10 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC10 bit
    uint16_t IPC11:1;                   // 11 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC11 bit
    uint16_t IPC12:1;                   // 12 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC12 bit
    uint16_t IPC13:1;                   // 13 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC13 bit
    uint16_t IPC14:1;                   // 14 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC14 bit
    uint16_t IPC15:1;                   // 15 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC15 bit
    uint16_t IPC16:1;                   // 16 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC16 bit
    uint16_t IPC17:1;                   // 17 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC17 bit
    uint16_t IPC18:1;                   // 18 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC18 bit
    uint16_t IPC19:1;                   // 19 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC19 bit
    uint16_t IPC20:1;                   // 20 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC20 bit
    uint16_t IPC21:1;                   // 21 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC21 bit
    uint16_t IPC22:1;                   // 22 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC22 bit
    uint16_t IPC23:1;                   // 23 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC23 bit
    uint16_t IPC24:1;                   // 24 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC24 bit
    uint16_t IPC25:1;                   // 25 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC25 bit
    uint16_t IPC26:1;                   // 26 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC26 bit
    uint16_t IPC27:1;                   // 27 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC27 bit
    uint16_t IPC28:1;                   // 28 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC28 bit
    uint16_t IPC29:1;                   // 29 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC29 bit
    uint16_t IPC30:1;                   // 30 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC30 bit
    uint16_t IPC31:1;                   // 31 Acknowledgement from CPU2 to CPU3TOCPU2IPCFLG.IPC31 bit
};

union IPC_CPU3TOCPU2INTIPCACK_REG {
    uint32_t  all;
    struct  IPC_CPU3TOCPU2INTIPCACK_BITS  bit;
};

struct CPU3_IPC_RCV_REGS_RegisterFile1_REGS {
    union   IPC_CPU2TOCPU3INTIPCSTS_REG      CPU2TOCPU3INTIPCSTS;          // CPU2TOCPU3INTIPCSTS Register
    union   IPC_CPU3TOCPU2INTIPCACK_REG      CPU3TOCPU2INTIPCACK;          // CPU3TOCPU2INTIPCACK Register
    uint8_t                                  rsvd1[8];                     // Reserved
    uint32_t                                 CPU2TOCPU3INTIPCRECVCOM;      // CPU2TOCPU3INTIPCRECVCOM Register
    uint32_t                                 CPU2TOCPU3INTIPCRECVADDR;     // CPU2TOCPU3INTIPCRECVADDR Register
    uint32_t                                 CPU2TOCPU3INTIPCRECVDATA;     // CPU2TOCPU3INTIPCRECVDATA Register
    uint32_t                                 CPU3TOCPU2INTLOCALREPLY;      // CPU3TOCPU2INTLOCALREPLY Register
    uint8_t                                  rsvd2[2016];                  // Reserved
};

struct CPU3_IPC_RCV_REGS {
    struct CPU3_IPC_RCV_REGS_RegisterFile0_REGS CPU3_IPC_RCV_RegisterFile0[4]; // 
    struct CPU3_IPC_RCV_REGS_RegisterFile1_REGS CPU3_IPC_RCV_RegisterFile1[4]; // 
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
