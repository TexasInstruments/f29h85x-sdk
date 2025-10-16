//###########################################################################
//
// FILE:   sbl_command_flow.h
//
// TITLE:  SBL's top-level command execution flow
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

#ifndef SBL_COMMAND_FLOW_H
#define SBL_COMMAND_FLOW_H

//
// Included Files
//
#include <device.h>
#include "bootrom.h"
#include "FlashTech_F29H85x_C29x.h"
#include "sbl_flash_programming.h"
#include "sbl_code_provisioning.h"

/* Register to read HSM boot notify status */
#define READ_BOOT_NOTIFY_REG    (0x301804E4U)
/* Boot notify status indicating that HSM firmware is now running */
#define BOOT_NOTIFY_DONE_STATUS (0x5A5A5A5AU)

#ifdef _FLASH
// Flash address
#define CPU3_RESET_VECTOR   0x10401000U
#define CPU3_NMI_VECTOR     0x10401040U
#else
// RAM address
#define CPU3_RESET_VECTOR   0x20110000U
#define CPU3_NMI_VECTOR     0x20110040U
#endif

//
// Function declarations
//
void cpu1FOTAFlow(void);
void cpu3FOTAFlow(void);
void secureCodeProvisionFlow(uint16_t command);
void programSecCfgFlow(void);
void runCPU3(void);
void sendSOCIDFlow(void);
void sendBromStatusFlow(void);
void programBankmodeFlow(uint16_t command);

#endif /* SBL_COMMAND_FLOW_H */
