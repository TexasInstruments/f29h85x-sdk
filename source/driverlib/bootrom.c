//###########################################################################
//
// FILE:   bootrom.c
//
// TITLE:  Bootrom structure instances.
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

#include "bootrom.h"

//
//  Bootrom status
//
__attribute__((noinit, retain, location(0x20000800))) const brom_status g_bootromStatus;

//
//  SoCID
//
__attribute__((noinit, retain, location(0x20000980))) const SOCID_Info  g_socId;

//
//  Device calibration data
//
__attribute__((noinit, retain, location(0x20000EDC))) const devcal_data g_devcalData;

//
//  64 bit RFFT twiddle table
//
__attribute__((noinit, retain, location(0x00001000))) const double      g_FPU64RFFTtwiddletable[RFFT_TABLE_SIZE];

//
//  64 bit CFFT twiddle table
//
__attribute__((noinit, retain, location(0x00002FE0))) const double      g_FPU64CFFTtwiddletable[CFFT_TABLE_SIZE];

//
//  32 bit RFFT table
//
__attribute__((noinit, retain, location(0x000047E0))) const float       g_FPU32RFFTtwiddletable[RFFT_TABLE_SIZE];

//
//  32 bit CFFT table
//
__attribute__((noinit, retain, location(0x000057D0))) const float       g_FPU32CFFTtwiddletable[CFFT_TABLE_SIZE];

