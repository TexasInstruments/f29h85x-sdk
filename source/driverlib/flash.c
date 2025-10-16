//###########################################################################
//
// FILE:   flash.c
//
// TITLE:  C29x Flash driver.
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

#include "flash.h"


//*****************************************************************************
//
// Flash_initModule
//
//*****************************************************************************

__attribute__((section(".TI.ramfunc.link2")))
void
Flash_initModule(uint16_t waitstates)
{
    //
    // Check the arguments.
    //
    ASSERT(waitstates <= 0xFU);
    ASSERT(waitstates >= 0x1U);


    //
    // Disable data cache, code cache, prefetch, and data preread before changing wait states
    //
    Flash_configFRI(FLASH_FRI1, FLASH_DATAPREREAD_DISABLE | FLASH_CODECACHE_DISABLE | FLASH_DATACACHE_DISABLE | FLASH_PREFETCH_DISABLE);
    Flash_configFRI(FLASH_FRI2, FLASH_DATAPREREAD_DISABLE | FLASH_CODECACHE_DISABLE | FLASH_DATACACHE_DISABLE | FLASH_PREFETCH_DISABLE);
    Flash_configFRI(FLASH_FRI3, FLASH_DATAPREREAD_DISABLE | FLASH_CODECACHE_DISABLE | FLASH_DATACACHE_DISABLE | FLASH_PREFETCH_DISABLE);
    Flash_configFRI(FLASH_FRI4, FLASH_DATAPREREAD_DISABLE | FLASH_CODECACHE_DISABLE | FLASH_DATACACHE_DISABLE | FLASH_PREFETCH_DISABLE);

    //
    // Set waitstates according to frequency.
    //
    Flash_setWaitstates(waitstates);

    //
    // Configure TRIMCOMMITREAD and TRIMCOMMITOTHER in TRIMCOMMIT register
    //
    Flash_writeTrims(ASYSCTL_O_FLASHTRIMCOMMIT, ASYSCTL_FLASHTRIMCOMMIT_FLC0TRIMCOMMITREAD,
                     0, ASYSCTL_FLASHTRIMCOMMIT_FLC0TRIMCOMMITREAD);
    Flash_writeTrims(ASYSCTL_O_FLASHTRIMCOMMIT, ASYSCTL_FLASHTRIMCOMMIT_FLC0TRIMCOMMITOTHER,
                     0, ASYSCTL_FLASHTRIMCOMMIT_FLC0TRIMCOMMITOTHER);

    Flash_writeTrims(ASYSCTL_O_FLASHTRIMCOMMIT, ASYSCTL_FLASHTRIMCOMMIT_FLC1TRIMCOMMITREAD,
                     0, ASYSCTL_FLASHTRIMCOMMIT_FLC1TRIMCOMMITREAD);
    Flash_writeTrims(ASYSCTL_O_FLASHTRIMCOMMIT, ASYSCTL_FLASHTRIMCOMMIT_FLC1TRIMCOMMITOTHER,
                     0, ASYSCTL_FLASHTRIMCOMMIT_FLC1TRIMCOMMITOTHER);

    Flash_writeTrims(ASYSCTL_O_FLASHTRIMCOMMIT, ASYSCTL_FLASHTRIMCOMMIT_FLC2TRIMCOMMITREAD,
                     0, ASYSCTL_FLASHTRIMCOMMIT_FLC2TRIMCOMMITREAD);
    Flash_writeTrims(ASYSCTL_O_FLASHTRIMCOMMIT, ASYSCTL_FLASHTRIMCOMMIT_FLC2TRIMCOMMITOTHER,
                     0, ASYSCTL_FLASHTRIMCOMMIT_FLC2TRIMCOMMITOTHER);

    //
    // Enable data cache, code cache, and prefetch to improve performance of code
    // executed from flash. Data Preread is not enabled as it should only be used in 
    // very specific cases where data is sequentially accessed.
    //
    Flash_configFRI(FLASH_FRI1, FLASH_CODECACHE_ENABLE | FLASH_DATACACHE_ENABLE | FLASH_PREFETCH_ENABLE);
    Flash_configFRI(FLASH_FRI2, FLASH_CODECACHE_ENABLE | FLASH_DATACACHE_ENABLE | FLASH_PREFETCH_ENABLE);
    Flash_configFRI(FLASH_FRI3, FLASH_CODECACHE_ENABLE | FLASH_DATACACHE_ENABLE | FLASH_PREFETCH_ENABLE);
    Flash_configFRI(FLASH_FRI4, FLASH_CODECACHE_ENABLE | FLASH_DATACACHE_ENABLE | FLASH_PREFETCH_ENABLE);

    //
    // Force a pipeline flush to ensure that the write to the last register
    // configured occurs before returning.
    //

    FLASH_DELAY_CONFIG;
}

