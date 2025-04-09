//###########################################################################
//
// FILE:   memss.c
//
// TITLE:  C29x MemSS driver.
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

#include "memss.h"



//******************************************************************************
//
// Memss_lockAllRegisters
//
//******************************************************************************
void
Memss_lockAllRegisters(void)
{
    Memss_lockConfig(MEMSS_RAM_LPA0);
    Memss_lockConfig(MEMSS_RAM_LPA1);
    Memss_lockConfig(MEMSS_RAM_LDA0);
    Memss_lockConfig(MEMSS_RAM_LDA1);
    Memss_lockConfig(MEMSS_RAM_LDA2);
    Memss_lockConfig(MEMSS_RAM_LDA3);
    Memss_lockConfig(MEMSS_RAM_LDA4);
    Memss_lockConfig(MEMSS_RAM_LDA5);
    Memss_lockConfig(MEMSS_RAM_LDA6);
    Memss_lockConfig(MEMSS_RAM_LDA7);
    Memss_lockConfig(MEMSS_RAM_CPA0);
    Memss_lockConfig(MEMSS_RAM_CPA1);
    Memss_lockConfig(MEMSS_RAM_CDA0);
    Memss_lockConfig(MEMSS_RAM_CDA1);
    Memss_lockConfig(MEMSS_RAM_CDA2);
    Memss_lockConfig(MEMSS_RAM_CDA3);
    Memss_lockConfig(MEMSS_RAM_CDA4);
    Memss_lockConfig(MEMSS_RAM_CDA5);
    Memss_lockConfig(MEMSS_RAM_CDA6);
    Memss_lockConfig(MEMSS_RAM_CDA7);
    Memss_lockConfig(MEMSS_RAM_CDA8);
    Memss_lockConfig(MEMSS_RAM_CDA9);
    Memss_lockConfig(MEMSS_RAM_CDA10);
    Memss_lockConfig(MEMSS_RAM_CDA11);
    Memss_lockConfig(MEMSS_RAM_M0);
}

//******************************************************************************
//
// Memss_unlockAllRegisters
//
//******************************************************************************
void
Memss_unlockAllRegisters(void)
{
    Memss_unlockConfig(MEMSS_RAM_LPA0);
    Memss_unlockConfig(MEMSS_RAM_LPA1);
    Memss_unlockConfig(MEMSS_RAM_LDA0);
    Memss_unlockConfig(MEMSS_RAM_LDA1);
    Memss_unlockConfig(MEMSS_RAM_LDA2);
    Memss_unlockConfig(MEMSS_RAM_LDA3);
    Memss_unlockConfig(MEMSS_RAM_LDA4);
    Memss_unlockConfig(MEMSS_RAM_LDA5);
    Memss_unlockConfig(MEMSS_RAM_LDA6);
    Memss_unlockConfig(MEMSS_RAM_LDA7);
    Memss_unlockConfig(MEMSS_RAM_CPA0);
    Memss_unlockConfig(MEMSS_RAM_CPA1);
    Memss_unlockConfig(MEMSS_RAM_CDA0);
    Memss_unlockConfig(MEMSS_RAM_CDA1);
    Memss_unlockConfig(MEMSS_RAM_CDA2);
    Memss_unlockConfig(MEMSS_RAM_CDA3);
    Memss_unlockConfig(MEMSS_RAM_CDA4);
    Memss_unlockConfig(MEMSS_RAM_CDA5);
    Memss_unlockConfig(MEMSS_RAM_CDA6);
    Memss_unlockConfig(MEMSS_RAM_CDA7);
    Memss_unlockConfig(MEMSS_RAM_CDA8);
    Memss_unlockConfig(MEMSS_RAM_CDA9);
    Memss_unlockConfig(MEMSS_RAM_CDA10);
    Memss_unlockConfig(MEMSS_RAM_CDA11);
    Memss_unlockConfig(MEMSS_RAM_M0);
}

//******************************************************************************
//
// Memss_commitAllRegisters
//
//******************************************************************************
void
Memss_commitAllRegisters(void)
{
    Memss_commitConfig(MEMSS_RAM_LPA0);
    Memss_commitConfig(MEMSS_RAM_LPA1);
    Memss_commitConfig(MEMSS_RAM_LDA0);
    Memss_commitConfig(MEMSS_RAM_LDA1);
    Memss_commitConfig(MEMSS_RAM_LDA2);
    Memss_commitConfig(MEMSS_RAM_LDA3);
    Memss_commitConfig(MEMSS_RAM_LDA4);
    Memss_commitConfig(MEMSS_RAM_LDA5);
    Memss_commitConfig(MEMSS_RAM_LDA6);
    Memss_commitConfig(MEMSS_RAM_LDA7);
    Memss_commitConfig(MEMSS_RAM_CPA0);
    Memss_commitConfig(MEMSS_RAM_CPA1);
    Memss_commitConfig(MEMSS_RAM_CDA0);
    Memss_commitConfig(MEMSS_RAM_CDA1);
    Memss_commitConfig(MEMSS_RAM_CDA2);
    Memss_commitConfig(MEMSS_RAM_CDA3);
    Memss_commitConfig(MEMSS_RAM_CDA4);
    Memss_commitConfig(MEMSS_RAM_CDA5);
    Memss_commitConfig(MEMSS_RAM_CDA6);
    Memss_commitConfig(MEMSS_RAM_CDA7);
    Memss_commitConfig(MEMSS_RAM_CDA8);
    Memss_commitConfig(MEMSS_RAM_CDA9);
    Memss_commitConfig(MEMSS_RAM_CDA10);
    Memss_commitConfig(MEMSS_RAM_CDA11);
    Memss_commitConfig(MEMSS_RAM_M0);
}

