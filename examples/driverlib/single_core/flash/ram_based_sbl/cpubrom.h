//###########################################################################
//
// FILE:   cpu1bootrom.h
//
// TITLE:  Top level BootROM Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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

#ifndef C_BOOTROM_H_
#define C_BOOTROM_H_

//
//  Includes
//
#include <stdint.h>
#include <device.h>
#include "bootrom.h"
#include "cpubrom_bootload.h"
#include "cpubrom_utils.h"

//
//  Defines
//
//
//  Status
//
#define BROM_STATUS_OK                  (0x55555555U)
#define BROM_STATUS_FAIL                (0xAAAAAAAAU)
#define BROM_STATUS_TRUE                (0x55555555U)
#define BROM_STATUS_FALSE               (0xAAAAAAAAU)
#define BROM_INVALID_ADDR               (0xDEADCAFEU)

//
//  Mask
//
#define WRITE_MASK_16_BIT               (0xFFFFU)
#define WRITE_MASK_32_BIT               (0xFFFFFFFFU)

//
//  Extern
//
extern brom_status g_bromStatus;
extern brom_status g_bromStatus_prev;
extern const SOCID_Info  g_socId;
extern uint32_t g_partidh;

#endif //C_BOOTROM_H_