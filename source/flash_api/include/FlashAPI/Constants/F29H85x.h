//###########################################################################
//
// FILE:   F65\Constants\F29H85x.h
//
// TITLE:  F65 Flash API v21.00.00
//
//###########################################################################
// //
//  Copyright: Copyright (C) Texas Instruments Incorporated
//  All rights reserved not granted herein.
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
/*!
    \file F65\Constants\F29H85x.h
    \brief A set of Constant Values for the F29H85x Family.
*/
#ifndef CONSTANTS_F29H85x_H_
#define CONSTANTS_F29H85x_H_

/*!
 *  FMC memory map defines
 */
#if defined (_F29H85x)

//----------------------------------------------------------------------------------------
//  C29 banks : Main Array
//----------------------------------------------------------------------------------------
#define C29FLASH_MAP_BEGIN                               (uint32_t)(0x10000000)
#define C29FLASH_MAP_END_PLUS1                           (uint32_t)(0x10800000)
//FR-1 RP0
#define C29FLASHBANKFR1RP0STARTADDRESS                   (uint32_t)(0x10000000)
#define C29FLASHBANKFR1RP0ENDADDRESS                     (uint32_t)(0x100FFFFF)
#define C29FLASHBANKFR1RP0ENDADDRESSPLUS1                (uint32_t)(0x10100000)

//FR-1 RP1
#define C29FLASHBANKFR1RP1STARTADDRESS                   (uint32_t)(0x10100000)
#define C29FLASHBANKFR1RP1ENDADDRESS                     (uint32_t)(0x101FFFFF)
#define C29FLASHBANKFR1RP1ENDADDRESSPLUS1                (uint32_t)(0x10200000)

//FR-1 RP2
#define C29FLASHBANKFR1RP2STARTADDRESS                   (uint32_t)(0x10200000)
#define C29FLASHBANKFR1RP2ENDADDRESS                     (uint32_t)(0x102FFFFF)
#define C29FLASHBANKFR1RP2ENDADDRESSPLUS1                (uint32_t)(0x10300000)

//FR-1 RP3
#define C29FLASHBANKFR1RP3STARTADDRESS                   (uint32_t)(0x10300000)
#define C29FLASHBANKFR1RP3ENDADDRESS                     (uint32_t)(0x103FFFFF)
#define C29FLASHBANKFR1RP3ENDADDRESSPLUS1                (uint32_t)(0x10400000)

//FR-2 RP0
#define C29FLASHBANKFR2RP0STARTADDRESS                   (uint32_t)(0x10400000)
#define C29FLASHBANKFR2RP0ENDADDRESS                     (uint32_t)(0x104FFFFF)
#define C29FLASHBANKFR2RP0ENDADDRESSPLUS1                (uint32_t)(0x10500000)

//FR-2 RP1
#define C29FLASHBANKFR2RP1STARTADDRESS                   (uint32_t)(0x10500000)
#define C29FLASHBANKFR2RP1ENDADDRESS                     (uint32_t)(0x105FFFFF)
#define C29FLASHBANKFR2RP1ENDADDRESSPLUS1                (uint32_t)(0x10600000)

//FR-3 RP0
#define C29FLASHBANKFR3RP0STARTADDRESS                   (uint32_t)(0x10600000)
#define C29FLASHBANKFR3RP0ENDADDRESS                     (uint32_t)(0x106FFFFF)
#define C29FLASHBANKFR3RP0ENDADDRESSPLUS1                (uint32_t)(0x10700000)

//FR-3 RP1
#define C29FLASHBANKFR3RP1STARTADDRESS                   (uint32_t)(0x10700000)
#define C29FLASHBANKFR3RP1ENDADDRESS                     (uint32_t)(0x107FFFFF)
#define C29FLASHBANKFR3RP1ENDADDRESSPLUS1                (uint32_t)(0x10800000)

//FR-4 RP0 data flash
#define C29FLASHBANKFR4RP0STARTADDRESS                   (uint32_t)(0x10C00000)
#define C29FLASHBANKFR4RP0ENDADDRESS                     (uint32_t)(0x10C3FFFF)
#define C29FLASHBANKFR4RP0ENDADDRESSPLUS1                (uint32_t)(0x10C40000)

//----------------------------------------------------------------------------------------
//  C29 banks : Main Array ECC
//----------------------------------------------------------------------------------------
#define C29FLASHECC_MAP_BEGIN                               (uint32_t)(0x10E00000)
#define C29FLASHECC_MAP_END_PLUS1                           (uint32_t)(0x10F00000)
//FR-1 RP0 ECC
#define C29FLASHBANKFR1RP0ECCSTARTADDRESS                   (uint32_t)(0x10E00000)
#define C29FLASHBANKFR1RP0ECCENDADDRESS                     (uint32_t)(0x10E1FFFF)
#define C29FLASHBANKFR1RP0ECCENDADDRESSPLUS1                (uint32_t)(0x10E20000)

//FR-1 RP1 ECC
#define C29FLASHBANKFR1RP1ECCSTARTADDRESS                   (uint32_t)(0x10E20000)
#define C29FLASHBANKFR1RP1ECCENDADDRESS                     (uint32_t)(0x10E3FFFF)
#define C29FLASHBANKFR1RP1ECCENDADDRESSPLUS1                (uint32_t)(0x10E40000)

//FR-1 RP2 ECC
#define C29FLASHBANKFR1RP2ECCSTARTADDRESS                   (uint32_t)(0x10E40000)
#define C29FLASHBANKFR1RP2ECCENDADDRESS                     (uint32_t)(0x10E5FFFF)
#define C29FLASHBANKFR1RP2ECCENDADDRESSPLUS1                (uint32_t)(0x10E60000)

//FR-1 RP3 ECC
#define C29FLASHBANKFR1RP3ECCSTARTADDRESS                   (uint32_t)(0x10E60000)
#define C29FLASHBANKFR1RP3ECCENDADDRESS                     (uint32_t)(0x10E7FFFF)
#define C29FLASHBANKFR1RP3ECCENDADDRESSPLUS1                (uint32_t)(0x10E80000)

//FR-2 RP0 ECC
#define C29FLASHBANKFR2RP0ECCSTARTADDRESS                   (uint32_t)(0x10E80000)
#define C29FLASHBANKFR2RP0ECCENDADDRESS                     (uint32_t)(0x10E9FFFF)
#define C29FLASHBANKFR2RP0ECCENDADDRESSPLUS1                (uint32_t)(0x10EA0000)

//FR-2 RP1 ECC
#define C29FLASHBANKFR2RP1ECCSTARTADDRESS                   (uint32_t)(0x10EA0000)
#define C29FLASHBANKFR2RP1ECCENDADDRESS                     (uint32_t)(0x10EBFFFF)
#define C29FLASHBANKFR2RP1ECCENDADDRESSPLUS1                (uint32_t)(0x10EC0000)

//FR-3 RP0 ECC
#define C29FLASHBANKFR3RP0ECCSTARTADDRESS                   (uint32_t)(0x10EC0000)
#define C29FLASHBANKFR3RP0ECCENDADDRESS                     (uint32_t)(0x10EDFFFF)
#define C29FLASHBANKFR3RP0ECCENDADDRESSPLUS1                (uint32_t)(0x10EE0000)

//FR-3 RP1 ECC
#define C29FLASHBANKFR3RP1ECCSTARTADDRESS                   (uint32_t)(0x10EE0000)
#define C29FLASHBANKFR3RP1ECCENDADDRESS                     (uint32_t)(0x10EFFFFF)
#define C29FLASHBANKFR3RP1ECCENDADDRESSPLUS1                (uint32_t)(0x10F00000)


//FR-4 RP0 ECC data flash
#define C29FLASHBANKFR4RP0ECCSTARTADDRESS                   (uint32_t)(0x10F80000)
#define C29FLASHBANKFR4RP0ECCENDADDRESS                     (uint32_t)(0x10F87FFF)
#define C29FLASHBANKFR4RP0ECCENDADDRESSPLUS1                (uint32_t)(0x10F88000)

//----------------------------------------------------------------------------------------
//  C29 banks : Non-Main Array
//----------------------------------------------------------------------------------------
//FR-1 RP0 BANKMGMT
#define C29FLASHBANKFR1RP0BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D80000)
#define C29FLASHBANKFR1RP0BANKMGMTENDADDRESS                     (uint32_t)(0x10D80FFF)
#define C29FLASHBANKFR1RP0BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D81000)

//FR-1 RP0 SECCFG
#define C29FLASHBANKFR1RP0SECCFGSTARTADDRESS                   (uint32_t)(0x10D81000)
#define C29FLASHBANKFR1RP0SECCFGENDADDRESS                     (uint32_t)(0x10D81FFF)
#define C29FLASHBANKFR1RP0SECCFGENDADDRESSPLUS1                (uint32_t)(0x10D82000)

//FR-1 RP1 BANKMGMT
#define C29FLASHBANKFR1RP1BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D84000)
#define C29FLASHBANKFR1RP1BANKMGMTENDADDRESS                     (uint32_t)(0x10D84FFF)
#define C29FLASHBANKFR1RP1BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D85000)

//FR-1 RP1 SECCFG
#define C29FLASHBANKFR1RP1SECCFGSTARTADDRESS                   (uint32_t)(0x10D85000)
#define C29FLASHBANKFR1RP1SECCFGENDADDRESS                     (uint32_t)(0x10D85FFF)
#define C29FLASHBANKFR1RP1SECCFGENDADDRESSPLUS1                (uint32_t)(0x10D86000)

//FR-1 RP2 BANKMGMT
#define C29FLASHBANKFR1RP2BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D88000)
#define C29FLASHBANKFR1RP2BANKMGMTENDADDRESS                     (uint32_t)(0x10D88FFF)
#define C29FLASHBANKFR1RP2BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D89000)

//FR-1 RP2 SECCFG
#define C29FLASHBANKFR1RP2SECCFGSTARTADDRESS                   (uint32_t)(0x10D89000)
#define C29FLASHBANKFR1RP2SECCFGENDADDRESS                     (uint32_t)(0x10D89FFF)
#define C29FLASHBANKFR1RP2SECCFGENDADDRESSPLUS1                (uint32_t)(0x10D8A000)

//FR-1 RP3 BANKMGMT
#define C29FLASHBANKFR1RP3BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D8C000)
#define C29FLASHBANKFR1RP3BANKMGMTENDADDRESS                     (uint32_t)(0x10D8CFFF)
#define C29FLASHBANKFR1RP3BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D8D000)

//FR-1 RP3 SECCFG
#define C29FLASHBANKFR1RP3SECCFGSTARTADDRESS                   (uint32_t)(0x10D8D000)
#define C29FLASHBANKFR1RP3SECCFGENDADDRESS                     (uint32_t)(0x10D8DFFF)
#define C29FLASHBANKFR1RP3SECCFGENDADDRESSPLUS1                (uint32_t)(0x10D8E000)

//FR-2 RP0 BANKMGMT
#define C29FLASHBANKFR2RP0BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D90000)
#define C29FLASHBANKFR2RP0BANKMGMTENDADDRESS                     (uint32_t)(0x10D90FFF)
#define C29FLASHBANKFR2RP0BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D91000)

//FR-2 RP0 SECCFG
#define C29FLASHBANKFR2RP0SECCFGSTARTADDRESS                   (uint32_t)(0x10D91000)
#define C29FLASHBANKFR2RP0SECCFGENDADDRESS                     (uint32_t)(0x10D91FFF)
#define C29FLASHBANKFR2RP0SECCFGENDADDRESSPLUS1                (uint32_t)(0x10D92000)

//FR-2 RP1 BANKMGMT
#define C29FLASHBANKFR2RP1BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D94000)
#define C29FLASHBANKFR2RP1BANKMGMTENDADDRESS                     (uint32_t)(0x10D94FFF)
#define C29FLASHBANKFR2RP1BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D95000)

//FR-2 RP1 SECCFG
#define C29FLASHBANKFR2RP1SECCFGSTARTADDRESS                   (uint32_t)(0x10D95000)
#define C29FLASHBANKFR2RP1SECCFGENDADDRESS                     (uint32_t)(0x10D95FFF)
#define C29FLASHBANKFR2RP1SECCFGENDADDRESSPLUS1                (uint32_t)(0x10D96000)

//FR-3 RP0 BANKMGMT
#define C29FLASHBANKFR3RP0BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D98000)
#define C29FLASHBANKFR3RP0BANKMGMTENDADDRESS                     (uint32_t)(0x10D98FFF)
#define C29FLASHBANKFR3RP0BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D99000)

//FR-3 RP0 SECCFG
#define C29FLASHBANKFR3RP0SECCFGSTARTADDRESS                   (uint32_t)(0x10D99000)
#define C29FLASHBANKFR3RP0SECCFGENDADDRESS                     (uint32_t)(0x10D99FFF)
#define C29FLASHBANKFR3RP0SECCFGENDADDRESSPLUS1                (uint32_t)(0x10D9A000)

//FR-3 RP1 BANKMGMT
#define C29FLASHBANKFR3RP1BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D9C000)
#define C29FLASHBANKFR3RP1BANKMGMTENDADDRESS                     (uint32_t)(0x10D9CFFF)
#define C29FLASHBANKFR3RP1BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D9D000)

//FR-3 RP1 SECCFG
#define C29FLASHBANKFR3RP1SECCFGSTARTADDRESS                   (uint32_t)(0x10D9D000)
#define C29FLASHBANKFR3RP1SECCFGENDADDRESS                     (uint32_t)(0x10D9DFFF)
#define C29FLASHBANKFR3RP1SECCFGENDADDRESSPLUS1                (uint32_t)(0x10D9E000)

//FR-4 RP0 Data Flash
#define C29FLASHBANKFR4RP0BANKMGMTSTARTADDRESS                   (uint32_t)(0x10D9E000)
#define C29FLASHBANKFR4RP0BANKMGMTENDADDRESS                     (uint32_t)(0x10D9EFFF)
#define C29FLASHBANKFR4RP0BANKMGMTENDADDRESSPLUS1                (uint32_t)(0x10D9F000)

//----------------------------------------------------------------------------------------
//  HSM C29 banks : Non-Main Array ECC
//----------------------------------------------------------------------------------------
//FR-1 RP0 BANKMGMT ECC
#define C29FLASHBANKFR1RP0BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB0000)
#define C29FLASHBANKFR1RP0BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB01FF)
#define C29FLASHBANKFR1RP0BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB0200)

//FR-1 RP0 SECCFG ECC
#define C29FLASHBANKFR1RP0SECCFGECCSTARTADDRESS                   (uint32_t)(0x10FB0200)
#define C29FLASHBANKFR1RP0SECCFGECCENDADDRESS                     (uint32_t)(0x10FB03FF)
#define C29FLASHBANKFR1RP0SECCFGECCENDADDRESSPLUS1                (uint32_t)(0x10FB0400)

//FR-1 RP1 BANKMGMT ECC
#define C29FLASHBANKFR1RP1BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB0800)
#define C29FLASHBANKFR1RP1BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB09FF)
#define C29FLASHBANKFR1RP1BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB0A00)

//FR-1 RP1 SECCFG ECC
#define C29FLASHBANKFR1RP1SECCFGECCSTARTADDRESS                   (uint32_t)(0x10FB0A00)
#define C29FLASHBANKFR1RP1SECCFGECCENDADDRESS                     (uint32_t)(0x10FB0BFF)
#define C29FLASHBANKFR1RP1SECCFGECCENDADDRESSPLUS1                (uint32_t)(0x10FB0C00)

//FR-1 RP2 BANKMGMT ECC
#define C29FLASHBANKFR1RP2BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB1000)
#define C29FLASHBANKFR1RP2BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB11FF)
#define C29FLASHBANKFR1RP2BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB1200)

//FR-1 RP2 SECCFG ECC
#define C29FLASHBANKFR1RP2SECCFGECCSTARTADDRESS                   (uint32_t)(0x10FB1200)
#define C29FLASHBANKFR1RP2SECCFGECCENDADDRESS                     (uint32_t)(0x10FB13FF)
#define C29FLASHBANKFR1RP2SECCFGECCENDADDRESSPLUS1                (uint32_t)(0x10FB1400)

//FR-1 RP3 BANKMGMT ECC
#define C29FLASHBANKFR1RP3BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB1800)
#define C29FLASHBANKFR1RP3BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB19FF)
#define C29FLASHBANKFR1RP3BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB1A00)

//FR-1 RP3 SECCFG ECC
#define C29FLASHBANKFR1RP3SECCFGECCSTARTADDRESS                   (uint32_t)(0x10FB1A00)
#define C29FLASHBANKFR1RP3SECCFGECCENDADDRESS                     (uint32_t)(0x10FB1BFF)
#define C29FLASHBANKFR1RP3SECCFGECCENDADDRESSPLUS1                (uint32_t)(0x10FB1C00)

//FR-2 RP0 BANKMGMT ECC
#define C29FLASHBANKFR2RP0BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB2000)
#define C29FLASHBANKFR2RP0BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB21FF)
#define C29FLASHBANKFR2RP0BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB2200)

//FR-2 RP0 SECCFG ECC
#define C29FLASHBANKFR2RP0SECCFGECCSTARTADDRESS                   (uint32_t)(0x10FB2200)
#define C29FLASHBANKFR2RP0SECCFGECCENDADDRESS                     (uint32_t)(0x10FB23FF)
#define C29FLASHBANKFR2RP0SECCFGECCENDADDRESSPLUS1                (uint32_t)(0x10FB2400)

//FR-2 RP1 BANKMGMT ECC
#define C29FLASHBANKFR2RP1BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB2800)
#define C29FLASHBANKFR2RP1BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB29FF)
#define C29FLASHBANKFR2RP1BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB2A00)

//FR-2 RP1 SECCFG ECC
#define C29FLASHBANKFR2RP1SECCFGECCSTARTADDRESS                   (uint32_t)(0x10FB2A00)
#define C29FLASHBANKFR2RP1SECCFGECCENDADDRESS                     (uint32_t)(0x10FB2BFF)
#define C29FLASHBANKFR2RP1SECCFGECCENDADDRESSPLUS1                (uint32_t)(0x10FB2C00)

//FR-3 RP0 BANKMGMT ECC
#define C29FLASHBANKFR3RP0BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB3000)
#define C29FLASHBANKFR3RP0BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB31FF)
#define C29FLASHBANKFR3RP0BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB3200)

//FR-3 RP0 SECCFG ECC
#define C29FLASHBANKFR3RP0SECCFGECCSTARTADDRESS                   (uint32_t)(0x10FB3200)
#define C29FLASHBANKFR3RP0SECCFGECCENDADDRESS                     (uint32_t)(0x10FB33FF)
#define C29FLASHBANKFR3RP0SECCFGECCENDADDRESSPLUS1                (uint32_t)(0x10FB3400)

//FR-3 RP1 BANKMGMT ECC
#define C29FLASHBANKFR3RP1BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB3800)
#define C29FLASHBANKFR3RP1BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB39FF)
#define C29FLASHBANKFR3RP1BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB3A00)

//FR-3 RP1 SECCFG ECC
#define C29FLASHBANKFR3RP1SECCFGECCSTARTADDRESS                   (uint32_t)(0x10FB3A00)
#define C29FLASHBANKFR3RP1SECCFGECCENDADDRESS                     (uint32_t)(0x10FB3BFF)
#define C29FLASHBANKFR3RP1SECCFGECCENDADDRESSPLUS1                (uint32_t)(0x10FB3C00)

//FR-4 RP0 Data flash
#define C29FLASHBANKFR4RP0BANKMGMTECCSTARTADDRESS                   (uint32_t)(0x10FB4000)
#define C29FLASHBANKFR4RP0BANKMGMTECCENDADDRESS                     (uint32_t)(0x10FB41FF)
#define C29FLASHBANKFR4RP0BANKMGMTECCENDADDRESSPLUS1                (uint32_t)(0x10FB4200)

#endif
#endif /* CONSTANTS_F29H85x_H_ */
