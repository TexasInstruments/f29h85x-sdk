//###########################################################################
//
//  FILE:    sbl_command_flow.h
//
//  TITLE:   SBL's top-level command execution flow
//  <h1> CPU SBL's top-level command execution flow</h1>
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
#include <board.h>
#include <ti_drivers_config.h>
#include "cpubrom.h"
#include "sbl_flash_programming.h"
#include "sbl_key_provisioning.h"
#include "sbl_code_provisioning.h"
#include "sbl_packet_interface.h"
#include "sbl_device_utils.h"
#include "ram_sbl_dpl_config.h"

#ifdef _FLASH
// Flash address
#define CPU3_RESET_VECTOR   0x10401000U
#define CPU3_NMI_VECTOR     0x10401040U
#else
// RAM address
#define CPU3_RESET_VECTOR   0x20110000U
#define CPU3_NMI_VECTOR     0x20110040U
#endif

void cpu1DFUFlow(void);
void cpu3DFUFlow(void);
void loadKeyFlow(void);
void loadRamHSMRtFlow(void);
void secureCodeProvisionFlow(uint16_t command);
void programSecCfgFlow(void);
void runCPU3(void);
void sendSOCIDFlow(void);
void sendBromStatusFlow(void);
void programBankmodeFlow(uint16_t command);

#endif // SBL_COMMAND_FLOW_H