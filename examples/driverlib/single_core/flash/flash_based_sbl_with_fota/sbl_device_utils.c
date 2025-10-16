//###########################################################################
//
// FILE:   sbl_device_utils.c
//
// TITLE:  Common Helper APIs
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

//
//  Includes
//
#include "sbl_device_utils.h"

extern void sblRoutine(void);

// FLC1_B0_A/B, FLC1_B2_A/B, FLC2_B0_A/B, FLC2_B2_A/B
uint32_t Prev_WEPROT_FLC[8] =
{
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};
bool hasStoredFLCStat = false;


//
// CPU long branch, similar to 
//  asm(" MV A7, D0");
//  asm(" LB A7");
void CPU_jumpToAddr(uint32_t jumpAddr)
{
    ((void (*)(void)) jumpAddr)();
}

//
// Returns maximum size of a flash image
//
uint32_t getMaxFlashImageSize(void)
{
    uint32_t imageSize;
    flashBankMode_t bankMode; 
    bankMode = getBankMode();
    
    switch (bankMode)
    {
        // Bankmode 0
        case FLASH_BANK_MODE_0:
            imageSize = 0x400000U - MAX_CERT_SIZE; // 4MB - Cert size
            break;
        // Bankmode 1 & 2
        case FLASH_BANK_MODE_1:
        case FLASH_BANK_MODE_2:
            imageSize = 0x200000U - MAX_CERT_SIZE; // 2MB - Cert size
            break;
        // Bankmode 3 and in case if bank mode invalid
        case FLASH_BANK_MODE_3:
        case FLASH_BANK_MODE_INVALID:
        default:
            imageSize = 0x100000U - MAX_CERT_SIZE; // 1MB - Cert size
            break;
    }
    return imageSize;
}

//
// Enable flash write and erase (Only in HS-KP is disabled by default for CPU1)
//
void enableFlashEraseAndWrite(void)
{
    // Update WEPROT_FLC1_B0_A register to enable flash erase and program for region
    HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B0_A) &= 0x00000000U;
    // Update WEPROT_FLC1_B0_B register to enable flash erase and program for region
    HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B0_B) &= 0x0000000FU;
    // Update WEPROT_FLC1_B2_A register to enable flash erase and program for region
    HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B2_A) &= 0x00000000U;
    // Update WEPROT_FLC1_B2_B register to enable flash erase and program for region
    HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B2_B) &= 0x0000000FU;
    // Update WEPROT_FLC2_B0_A register to enable flash erase and program for region
    HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B0_A) &= 0x00000000U;
    // Update WEPROT_FLC2_B0_B register to enable flash erase and program for region
    HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B0_B) &= 0x0000000FU;
    // Update WEPROT_FLC2_B2_A register to enable flash erase and program for region
    HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B2_A) &= 0x00000000U;
    // Update WEPROT_FLC2_B2_B register to enable flash erase and program for region
    HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B2_B) &= 0x0000000FU;
}

//
// Store flash write-earse protection settings and disable write erase protection
//
void storeAndDisableFlashWEPROT(void)
{
    Prev_WEPROT_FLC[0] = HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B0_A);
    Prev_WEPROT_FLC[1] = HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B0_B);
    Prev_WEPROT_FLC[2] = HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B2_A);
    Prev_WEPROT_FLC[3] = HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B2_B);
    Prev_WEPROT_FLC[4] = HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B0_A);
    Prev_WEPROT_FLC[5] = HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B0_B);
    Prev_WEPROT_FLC[6] = HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B2_A);
    Prev_WEPROT_FLC[7] = HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B2_B);

    hasStoredFLCStat = true;

    enableFlashEraseAndWrite();
}

//
// Restore write erase protection
//
void restoreFlashWEPROT(void)
{
    if (hasStoredFLCStat)
    {
        hasStoredFLCStat = false;
        HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B0_A) = Prev_WEPROT_FLC[0];
        HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B0_B) = Prev_WEPROT_FLC[1];
        HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B2_A) = Prev_WEPROT_FLC[2];
        HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC1_B2_B) = Prev_WEPROT_FLC[3];
        HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B0_A) = Prev_WEPROT_FLC[4];
        HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B0_B) = Prev_WEPROT_FLC[5];
        HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B2_A) = Prev_WEPROT_FLC[6];
        HWREG(SSUGEN_BASE + SSU_O_WEPROT_FLC2_B2_B) = Prev_WEPROT_FLC[7];
    }
}

//******************************************************************************
// For this example, reset back to the normal kernel routine
//******************************************************************************
void Example_Error()
{
#if defined(NONSECURE) || defined(NONSECURE_DFU)
    // try releasing flash semaphore (in case if set)
    SSU_releaseFlashSemaphore();
#endif /* defined(NONSECURE) || defined(NONSECURE_DFU) */
#if defined(SECURE_CP)
    // try restoring Flash WEPROT (in case if set)
    restoreFlashWEPROT();
#endif /* defined(SECURE_CP) */

    // Wait for any device communication to finish prior to halting the device (100ms)
    DEVICE_DELAY_US(0.1 * 1000000U);
    
    //
    //  Uncomment this for debugging
    //  Error code will be in the status parameter
    //
    //__asm(" EMUSTOP0");

    //
    // Reset back to the normal SBL routine
    //
    asm(" LB @(sblRoutine)");
}
