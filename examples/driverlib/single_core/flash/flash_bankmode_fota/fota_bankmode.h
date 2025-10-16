//#############################################################################
//
// FILE:   fota_bankmode.h
//
// TITLE:  API definition to change the BANKMODE for FOTA
//
//#############################################################################
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

#ifndef FOTA_BANKMODE_
#define FOTA_BANKMODE_

//
//  Macro definitions
//
//
//  Bank status offset
//
#define BANKMMGMT_O_BANK_STATUS             (0x0U)
//
//  Bank update counter offset
//
#define BANKMMGMT_O_BANK_UPDATE_CTR         (0x8U)
//
//  Valid bank status
//
#define BANKMGMT_VALID_BANK_STATUS          (0x5555555555555555U)
//
//  Invalid bank status
//
#define BANKMGMT_INVALID_BANK_STATUS        (0xFFFFFFFFFFFFFFFFU)
//
//  Invalid update counter
//
#define BANKMGMT_INVALID_UPDATE_CTR         (0x0000000000000000U)
//
//  2KB sector in 4 bytes
//
#define SECTOR2KB_IN_4BYTES                 (0x200U)
//
//  Flash controller base address
//
#define FlashTech_CPU0_BASE_ADDRESS         ((Fapi_FmcRegistersType *)FLASHCONTROLLER1_BASE)
//
//  Bankmgmt sector address used for programming
//
#define BANKMGMT_PROG_ADDR                  (0x10D80000U)

//
//  Enum
//
//
//  Bankmode
//
typedef enum
{
    FOTA_BANKMODE_0     = 0U,
    FOTA_BANKMODE_1     = 1U,
    FOTA_BANKMODE_2     = 2U,
    FOTA_BANKMODE_3     = 3U,
    FOTA_BANKMODE_MAX   = 4U
} fota_bankMode;

//
//  Function declaration
//
//
//  Fota_SetBankMode
//
Fapi_StatusType Fota_SetBankMode(fota_bankMode fotaBankMode);

#endif /* FOTA_BANKMODE_ */
