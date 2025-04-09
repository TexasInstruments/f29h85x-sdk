//#############################################################################
//
// FILE:   flash_programming_F29H85x.h
//
// TITLE:  A set of Constant Values for the F29H85x Family.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################
#ifndef FLASH_PROGRAMMING_F29H85XH_
#define FLASH_PROGRAMMING_F29H85XH_

//----------------------------------------------------------------------------------------
//  C29 banks : Main Array
//----------------------------------------------------------------------------------------
//FR-1 RP0
#define C29FlashBankFR1RP0StartAddress                   (uint32_t)(0x10000000)
#define C29FlashBankFR1RP0EndAddress                     (uint32_t)(0x100FFFFF)
#define C29FlashBankFR1RP0EndAddressPlus1                (uint32_t)(0x10100000)

//FR-1 RP1
#define C29FlashBankFR1RP1StartAddress                   (uint32_t)(0x10100000)
#define C29FlashBankFR1RP1EndAddress                     (uint32_t)(0x101FFFFF)
#define C29FlashBankFR1RP1EndAddressPlus1                (uint32_t)(0x10200000)

//FR-1 RP2
#define C29FlashBankFR1RP2StartAddress                   (uint32_t)(0x10200000)
#define C29FlashBankFR1RP2EndAddress                     (uint32_t)(0x102FFFFF)
#define C29FlashBankFR1RP2EndAddressPlus1                (uint32_t)(0x10300000)

//FR-1 RP3
#define C29FlashBankFR1RP3StartAddress                   (uint32_t)(0x10300000)
#define C29FlashBankFR1RP3EndAddress                     (uint32_t)(0x103FFFFF)
#define C29FlashBankFR1RP3EndAddressPlus1                (uint32_t)(0x10400000)

//FR-2 RP0
#define C29FlashBankFR2RP0StartAddress                   (uint32_t)(0x10400000)
#define C29FlashBankFR2RP0EndAddress                     (uint32_t)(0x104FFFFF)
#define C29FlashBankFR2RP0EndAddressPlus1                (uint32_t)(0x10500000)

//FR-2 RP1
#define C29FlashBankFR2RP1StartAddress                   (uint32_t)(0x10500000)
#define C29FlashBankFR2RP1EndAddress                     (uint32_t)(0x105FFFFF)
#define C29FlashBankFR2RP1EndAddressPlus1                (uint32_t)(0x10600000)

//FR-3 RP0
#define C29FlashBankFR3RP0StartAddress                   (uint32_t)(0x10600000)
#define C29FlashBankFR3RP0EndAddress                     (uint32_t)(0x106FFFFF)
#define C29FlashBankFR3RP0EndAddressPlus1                (uint32_t)(0x10700000)

//FR-3 RP1
#define C29FlashBankFR3RP1StartAddress                   (uint32_t)(0x10700000)
#define C29FlashBankFR3RP1EndAddress                     (uint32_t)(0x107FFFFF)
#define C29FlashBankFR3RP1EndAddressPlus1                (uint32_t)(0x10800000)

//FR-4 RP0 data flash
#define C29FlashBankFR4RP0StartAddress                   (uint32_t)(0x10C00000)
#define C29FlashBankFR4RP0EndAddress                     (uint32_t)(0x10C3FFFF)
#define C29FlashBankFR4RP0EndAddressPlus1                (uint32_t)(0x10C40000)

//----------------------------------------------------------------------------------------
//  HSM C29 banks : Main Array ECC
//----------------------------------------------------------------------------------------
//FR-1 RP0 ECC
#define C29FlashBankFR1RP0EccStartAddress                   (uint32_t)(0x10E00000)
#define C29FlashBankFR1RP0EccEndAddress                     (uint32_t)(0x10E1FFFF)
#define C29FlashBankFR1RP0EccEndAddressPlus1                (uint32_t)(0x10E20000)

//FR-1 RP1 ECC
#define C29FlashBankFR1RP1EccStartAddress                   (uint32_t)(0x10E20000)
#define C29FlashBankFR1RP1EccEndAddress                     (uint32_t)(0x10E3FFFF)
#define C29FlashBankFR1RP1EccEndAddressPlus1                (uint32_t)(0x10E40000)

//FR-1 RP2 ECC
#define C29FlashBankFR1RP2EccStartAddress                   (uint32_t)(0x10E40000)
#define C29FlashBankFR1RP2EccEndAddress                     (uint32_t)(0x10E5FFFF)
#define C29FlashBankFR1RP2EccEndAddressPlus1                (uint32_t)(0x10E60000)

//FR-1 RP3 ECC
#define C29FlashBankFR1RP3EccStartAddress                   (uint32_t)(0x10E60000)
#define C29FlashBankFR1RP3EccEndAddress                     (uint32_t)(0x10E7FFFF)
#define C29FlashBankFR1RP3EccEndAddressPlus1                (uint32_t)(0x10E80000)

//FR-2 RP0 ECC
#define C29FlashBankFR2RP0EccStartAddress                   (uint32_t)(0x10E80000)
#define C29FlashBankFR2RP0EccEndAddress                     (uint32_t)(0x10E9FFFF)
#define C29FlashBankFR2RP0EccEndAddressPlus1                (uint32_t)(0x10EA0000)

//FR-2 RP1 ECC
#define C29FlashBankFR2RP1EccStartAddress                   (uint32_t)(0x10EA0000)
#define C29FlashBankFR2RP1EccEndAddress                     (uint32_t)(0x10EBFFFF)
#define C29FlashBankFR2RP1EccEndAddressPlus1                (uint32_t)(0x10EC0000)

//FR-3 RP0 ECC
#define C29FlashBankFR3RP0EccStartAddress                   (uint32_t)(0x10EC0000)
#define C29FlashBankFR3RP0EccEndAddress                     (uint32_t)(0x10EDFFFF)
#define C29FlashBankFR3RP0EccEndAddressPlus1                (uint32_t)(0x10EE0000)

//FR-3 RP1 ECC
#define C29FlashBankFR3RP1EccStartAddress                   (uint32_t)(0x10EE0000)
#define C29FlashBankFR3RP1EccEndAddress                     (uint32_t)(0x10EFFFFF)
#define C29FlashBankFR3RP1EccEndAddressPlus1                (uint32_t)(0x10F00000)


//FR-4 RP0 ECC data flash
#define C29FlashBankFR4RP0EccStartAddress                   (uint32_t)(0x10F80000)
#define C29FlashBankFR4RP0EccEndAddress                     (uint32_t)(0x10F9FFFF)
#define C29FlashBankFR4RP0EccEndAddressPlus1                (uint32_t)(0x10FA0000)

//----------------------------------------------------------------------------------------
//  HSM C29 banks : Non-Main Array
//----------------------------------------------------------------------------------------
//FR-1 RP0 Bnkmgmt
#define C29FlashBankFR1RP0BnkmgmtStartAddress                   (uint32_t)(0x10D80000)
#define C29FlashBankFR1RP0BnkmgmtEndAddress                     (uint32_t)(0x10D80FFF)
#define C29FlashBankFR1RP0BnkmgmtEndAddressPlus1                (uint32_t)(0x10D81000)

//FR-1 RP0 Seccfg
#define C29FlashBankFR1RP0SeccfgStartAddress                   (uint32_t)(0x10D81000)
#define C29FlashBankFR1RP0SeccfgEndAddress                     (uint32_t)(0x10D81FFF)
#define C29FlashBankFR1RP0SeccfgEndAddressPlus1                (uint32_t)(0x10D82000)

//FR-1 RP1 Bnkmgmt
#define C29FlashBankFR1RP1BnkmgmtStartAddress                   (uint32_t)(0x10D84000)
#define C29FlashBankFR1RP1BnkmgmtEndAddress                     (uint32_t)(0x10D84FFF)
#define C29FlashBankFR1RP1BnkmgmtEndAddressPlus1                (uint32_t)(0x10D85000)

//FR-1 RP1 Seccfg
#define C29FlashBankFR1RP1SeccfgStartAddress                   (uint32_t)(0x10D85000)
#define C29FlashBankFR1RP1SeccfgEndAddress                     (uint32_t)(0x10D85FFF)
#define C29FlashBankFR1RP1SeccfgEndAddressPlus1                (uint32_t)(0x10D86000)

//FR-1 RP2 Bnkmgmt
#define C29FlashBankFR1RP2BnkmgmtStartAddress                   (uint32_t)(0x10D88000)
#define C29FlashBankFR1RP2BnkmgmtEndAddress                     (uint32_t)(0x10D88FFF)
#define C29FlashBankFR1RP2BnkmgmtEndAddressPlus1                (uint32_t)(0x10D89000)

//FR-1 RP2 Seccfg
#define C29FlashBankFR1RP2SeccfgStartAddress                   (uint32_t)(0x10D89000)
#define C29FlashBankFR1RP2SeccfgEndAddress                     (uint32_t)(0x10D89FFF)
#define C29FlashBankFR1RP2SeccfgEndAddressPlus1                (uint32_t)(0x10D8A000)

//FR-1 RP3 Bnkmgmt
#define C29FlashBankFR1RP3BnkmgmtStartAddress                   (uint32_t)(0x10D8C000)
#define C29FlashBankFR1RP3BnkmgmtEndAddress                     (uint32_t)(0x10D8CFFF)
#define C29FlashBankFR1RP3BnkmgmtEndAddressPlus1                (uint32_t)(0x10D8D000)

//FR-1 RP3 Seccfg
#define C29FlashBankFR1RP3SeccfgStartAddress                   (uint32_t)(0x10D8D000)
#define C29FlashBankFR1RP3SeccfgEndAddress                     (uint32_t)(0x10D8DFFF)
#define C29FlashBankFR1RP3SeccfgEndAddressPlus1                (uint32_t)(0x10D8E000)

//FR-2 RP0 Bnkmgmt
#define C29FlashBankFR2RP0BnkmgmtStartAddress                   (uint32_t)(0x10D90000)
#define C29FlashBankFR2RP0BnkmgmtEndAddress                     (uint32_t)(0x10D90FFF)
#define C29FlashBankFR2RP0BnkmgmtEndAddressPlus1                (uint32_t)(0x10D91000)

//FR-2 RP0 Seccfg
#define C29FlashBankFR2RP0SeccfgStartAddress                   (uint32_t)(0x10D91000)
#define C29FlashBankFR2RP0SeccfgEndAddress                     (uint32_t)(0x10D91FFF)
#define C29FlashBankFR2RP0SeccfgEndAddressPlus1                (uint32_t)(0x10D92000)

//FR-2 RP1 Bnkmgmt
#define C29FlashBankFR2RP1BnkmgmtStartAddress                   (uint32_t)(0x10D94000)
#define C29FlashBankFR2RP1BnkmgmtEndAddress                     (uint32_t)(0x10D94FFF)
#define C29FlashBankFR2RP1BnkmgmtEndAddressPlus1                (uint32_t)(0x10D95000)

//FR-2 RP1 Seccfg
#define C29FlashBankFR2RP1SeccfgStartAddress                   (uint32_t)(0x10D95000)
#define C29FlashBankFR2RP1SeccfgEndAddress                     (uint32_t)(0x10D95FFF)
#define C29FlashBankFR2RP1SeccfgEndAddressPlus1                (uint32_t)(0x10D96000)

//FR-3 RP0 Bnkmgmt
#define C29FlashBankFR3RP0BnkmgmtStartAddress                   (uint32_t)(0x10D98000)
#define C29FlashBankFR3RP0BnkmgmtEndAddress                     (uint32_t)(0x10D98FFF)
#define C29FlashBankFR3RP0BnkmgmtEndAddressPlus1                (uint32_t)(0x10D99000)

//FR-3 RP0 Seccfg
#define C29FlashBankFR3RP0SeccfgStartAddress                   (uint32_t)(0x10D99000)
#define C29FlashBankFR3RP0SeccfgEndAddress                     (uint32_t)(0x10D99FFF)
#define C29FlashBankFR3RP0SeccfgEndAddressPlus1                (uint32_t)(0x10D9A000)

//FR-3 RP1 Bnkmgmt
#define C29FlashBankFR3RP1BnkmgmtStartAddress                   (uint32_t)(0x10D9C000)
#define C29FlashBankFR3RP1BnkmgmtEndAddress                     (uint32_t)(0x10D9CFFF)
#define C29FlashBankFR3RP1BnkmgmtEndAddressPlus1                (uint32_t)(0x10D9D000)

//FR-3 RP1 Seccfg
#define C29FlashBankFR3RP1SeccfgStartAddress                   (uint32_t)(0x10D9D000)
#define C29FlashBankFR3RP1SeccfgEndAddress                     (uint32_t)(0x10D9DFFF)
#define C29FlashBankFR3RP1SeccfgEndAddressPlus1                (uint32_t)(0x10D9E000)

//FR-4 RP0 Data Flash
#define C29FlashBankFR4RP0BnkmgmtStartAddress                   (uint32_t)(0x10D9E000)
#define C29FlashBankFR4RP0BnkmgmtEndAddress                     (uint32_t)(0x10D9EFFF)
#define C29FlashBankFR4RP0BnkmgmtEndAddressPlus1                (uint32_t)(0x10D9F000)

//----------------------------------------------------------------------------------------
//  HSM C29 banks : Non-Main Array ECC
//----------------------------------------------------------------------------------------
//FR-1 RP0 Bnkmgmt Ecc
#define C29FlashBankFR1RP0BnkmgmtEccStartAddress                   (uint32_t)(0x10FB0000)
#define C29FlashBankFR1RP0BnkmgmtEccEndAddress                     (uint32_t)(0x10FB01FF)
#define C29FlashBankFR1RP0BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB0200)

//FR-1 RP0 Seccfg Ecc
#define C29FlashBankFR1RP0SeccfgEccStartAddress                   (uint32_t)(0x10FB0200)
#define C29FlashBankFR1RP0SeccfgEccEndAddress                     (uint32_t)(0x10FB03FF)
#define C29FlashBankFR1RP0SeccfgEccEndAddressPlus1                (uint32_t)(0x10FB0400)

//FR-1 RP1 Bnkmgmt Ecc
#define C29FlashBankFR1RP1BnkmgmtEccStartAddress                   (uint32_t)(0x10FB0800)
#define C29FlashBankFR1RP1BnkmgmtEccEndAddress                     (uint32_t)(0x10FB09FF)
#define C29FlashBankFR1RP1BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB0A00)

//FR-1 RP1 Seccfg Ecc
#define C29FlashBankFR1RP1SeccfgEccStartAddress                   (uint32_t)(0x10FB0A00)
#define C29FlashBankFR1RP1SeccfgEccEndAddress                     (uint32_t)(0x10FB0BFF)
#define C29FlashBankFR1RP1SeccfgEccEndAddressPlus1                (uint32_t)(0x10FB0C00)

//FR-1 RP2 Bnkmgmt Ecc
#define C29FlashBankFR1RP2BnkmgmtEccStartAddress                   (uint32_t)(0x10FB1000)
#define C29FlashBankFR1RP2BnkmgmtEccEndAddress                     (uint32_t)(0x10FB11FF)
#define C29FlashBankFR1RP2BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB1200)

//FR-1 RP2 Seccfg Ecc
#define C29FlashBankFR1RP2SeccfgEccStartAddress                   (uint32_t)(0x10FB1200)
#define C29FlashBankFR1RP2SeccfgEccEndAddress                     (uint32_t)(0x10FB13FF)
#define C29FlashBankFR1RP2SeccfgEccEndAddressPlus1                (uint32_t)(0x10FB1400)

//FR-1 RP3 Bnkmgmt Ecc
#define C29FlashBankFR1RP3BnkmgmtEccStartAddress                   (uint32_t)(0x10FB1800)
#define C29FlashBankFR1RP3BnkmgmtEccEndAddress                     (uint32_t)(0x10FB19FF)
#define C29FlashBankFR1RP3BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB1A00)

//FR-1 RP3 Seccfg Ecc
#define C29FlashBankFR1RP3SeccfgEccStartAddress                   (uint32_t)(0x10FB1A00)
#define C29FlashBankFR1RP3SeccfgEccEndAddress                     (uint32_t)(0x10FB1BFF)
#define C29FlashBankFR1RP3SeccfgEccEndAddressPlus1                (uint32_t)(0x10FB1C00)

//FR-2 RP0 Bnkmgmt Ecc
#define C29FlashBankFR2RP0BnkmgmtEccStartAddress                   (uint32_t)(0x10FB2000)
#define C29FlashBankFR2RP0BnkmgmtEccEndAddress                     (uint32_t)(0x10FB21FF)
#define C29FlashBankFR2RP0BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB2200)

//FR-2 RP0 Seccfg Ecc
#define C29FlashBankFR2RP0SeccfgEccStartAddress                   (uint32_t)(0x10FB2200)
#define C29FlashBankFR2RP0SeccfgEccEndAddress                     (uint32_t)(0x10FB23FF)
#define C29FlashBankFR2RP0SeccfgEccEndAddressPlus1                (uint32_t)(0x10FB2400)

//FR-2 RP1 Bnkmgmt Ecc
#define C29FlashBankFR2RP1BnkmgmtEccStartAddress                   (uint32_t)(0x10FB2800)
#define C29FlashBankFR2RP1BnkmgmtEccEndAddress                     (uint32_t)(0x10FB29FF)
#define C29FlashBankFR2RP1BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB2A00)

//FR-2 RP1 Seccfg Ecc
#define C29FlashBankFR2RP1SeccfgEccStartAddress                   (uint32_t)(0x10FB2A00)
#define C29FlashBankFR2RP1SeccfgEccEndAddress                     (uint32_t)(0x10FB2BFF)
#define C29FlashBankFR2RP1SeccfgEccEndAddressPlus1                (uint32_t)(0x10FB2C00)

//FR-3 RP0 Bnkmgmt Ecc
#define C29FlashBankFR3RP0BnkmgmtEccStartAddress                   (uint32_t)(0x10FB3000)
#define C29FlashBankFR3RP0BnkmgmtEccEndAddress                     (uint32_t)(0x10FB31FF)
#define C29FlashBankFR3RP0BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB3200)

//FR-3 RP0 Seccfg Ecc
#define C29FlashBankFR3RP0SeccfgEccStartAddress                   (uint32_t)(0x10FB3200)
#define C29FlashBankFR3RP0SeccfgEccEndAddress                     (uint32_t)(0x10FB33FF)
#define C29FlashBankFR3RP0SeccfgEccEndAddressPlus1                (uint32_t)(0x10FB3400)

//FR-3 RP1 Bnkmgmt Ecc
#define C29FlashBankFR3RP1BnkmgmtEccStartAddress                   (uint32_t)(0x10FB3800)
#define C29FlashBankFR3RP1BnkmgmtEccEndAddress                     (uint32_t)(0x10FB39FF)
#define C29FlashBankFR3RP1BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB3A00)

//FR-3 RP1 Seccfg Ecc
#define C29FlashBankFR3RP1SeccfgEccStartAddress                   (uint32_t)(0x10FB3A00)
#define C29FlashBankFR3RP1SeccfgEccEndAddress                     (uint32_t)(0x10FB3BFF)
#define C29FlashBankFR3RP1SeccfgEccEndAddressPlus1                (uint32_t)(0x10FB3C00)

//FR-4 RP0 Data flash
#define C29FlashBankFR4RP0BnkmgmtEccStartAddress                   (uint32_t)(0x10FB4000)
#define C29FlashBankFR4RP0BnkmgmtEccEndAddress                     (uint32_t)(0x10FB41FF)
#define C29FlashBankFR4RP0BnkmgmtEccEndAddressPlus1                (uint32_t)(0x10FB4200)

#define     FlashC29BankOffset              0x100000U
#define     FlashC29sectorsize              0x1000
#define     FlashC29SECCFGBNKMGMTOffset     0x4000U

//Sector length in number of 32bits
#define Sector2KB_u32length                 0x200U
#define Bank256KB_u32length                 0x10000U

#endif /* FLASH_PROGRAMMING_F29H85XH_ */
