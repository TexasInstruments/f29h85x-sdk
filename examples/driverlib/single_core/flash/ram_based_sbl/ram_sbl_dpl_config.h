//###########################################################################
//
// FILE:   ram_sbl_dpl_config.h
//
// TITLE:  SBL DPL configuration that is based on ti_dpl_config.c
//         The only difference is the hard coded SSU LINK & STACK config depending on the device state
//         HS-FS: LINK1 & STACK1, HS-KP/SE: LINK2 & STACK2
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

#ifndef RAM_SBL_DPL_CONFIG_H
#define RAM_SBL_DPL_CONFIG_H

//
//  Includes
//
#include <board.h>
#include <ti_dpl_config.h>
#include <ti_drivers_config.h>
#include "sbl_device_utils.h"

void KernelDpl_init();
void KernelSystem_init();
static inline void KernelDpl_deinit();
static inline void KernelSystem_deinit();

// DPL LINK & STACK in HS_FS state
// In HS-FS, RAMOPEN is enforced so Link & Stack defaults to 1
#define DPL_RAMOPEN_LINK     SSU_LINK1  
#define DPL_RAMOPEN_STACK    SSU_STACK1
// DPL LINK & STACK in HS_KP & HS_SE state
// Default DPL setting (Link & Stack 2)
#define DPL_NORMAL_LINK     SSU_LINK2
#define DPL_NORMAL_STACK    SSU_STACK2

static inline void KernelDpl_deinit()
{
    Dpl_deinit();
}

static inline void KernelSystem_deinit()
{
    System_deinit();
}

#endif //RAM_SBL_DPL_CONFIG_H
