/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <drivers/soc.h>
#include <kernel/dpl/CpuIdP.h>

#if defined(__C29__)
#include <driverlib/clockconfig.h>
#include <device.h>
#endif

uint64_t SOC_virtToPhy(void *virtAddr) {
    volatile uintptr_t temp = (uintptr_t)virtAddr;
    /* Default case */
    uint64_t phyAddr = (uint64_t)temp;

#if defined(__C29__)
    if ((temp >= LDA7_RAM_BASE) && (temp <= (LPA0_RAM_BASE - 1))) {
        phyAddr += LDA_ADDRESS_TRANSLATION_MASK;
    } else if ((temp >= C29_MAILBOX_VIEW_START) && (temp <= C29_MAILBOX_VIEW_END)) {
        phyAddr += MBOX_ADDRESS_TRANSLATION_MASK;
    } else if ((temp >= C29FLASH_MAP_BEGIN) && (temp <= C29FLASHBANKFR4RP0BANKMGMTENDADDRESSPLUS1)) {
        phyAddr += FLASH_ADDRESS_TRANSLATION_MASK;
    }
#else
    if ((temp >= Hsm_C29FlashBankFR1RP0StartAddress) && (temp <= Hsm_C29FlashBankFR4RP0EndAddressPlus1)) {
        phyAddr += FLASH_ADDRESS_TRANSLATION_MASK;
    } else if ((temp >= Hsm_C29FlashBankFR1RP0EccStartAddress) && (temp <= Hsm_C29FlashBankFR4RP0EccEndAddressPlus1)) {
        phyAddr += FLASH_ADDRESS_TRANSLATION_MASK;
    } else if ((temp >= Hsm_C29FlashBankFR1RP0BnkmgmtStartAddress)
                && (temp <= Hsm_C29FlashBankFR4RP0BnkmgmtEndAddressPlus1)) {
        phyAddr += FLASH_ADDRESS_TRANSLATION_MASK;
    } else if ((temp >= Hsm_C29FlashBankFR1RP0BnkmgmtEccStartAddress)
                && (temp <= Hsm_C29FlashBankFR4RP0BnkmgmtEccEndAddressPlus1)) {
        phyAddr += FLASH_ADDRESS_TRANSLATION_MASK;
    }

#endif
    return (phyAddr);
}

void *SOC_phyToVirt(uint64_t phyAddr) {
    /* Default case */
    void *virtAddr = (void *)((uintptr_t)phyAddr);

#if defined(__C29__)
    if ((virtAddr >= (LDA7_RAM_BASE + LDA_ADDRESS_TRANSLATION_MASK))
        && (virtAddr <= ((LPA0_RAM_BASE - 1) + LDA_ADDRESS_TRANSLATION_MASK))) {
        virtAddr -= LDA_ADDRESS_TRANSLATION_MASK;
    } else if ((virtAddr >= (C29_MAILBOX_VIEW_START + MBOX_ADDRESS_TRANSLATION_MASK))
                && (virtAddr <= (C29_MAILBOX_VIEW_END + MBOX_ADDRESS_TRANSLATION_MASK))) {
        virtAddr -= MBOX_ADDRESS_TRANSLATION_MASK;
    } else if ((virtAddr >= (C29FLASH_MAP_BEGIN + FLASH_ADDRESS_TRANSLATION_MASK))
                && (virtAddr <= (C29FLASHBANKFR4RP0BANKMGMTENDADDRESSPLUS1 + FLASH_ADDRESS_TRANSLATION_MASK))) {
        virtAddr -= FLASH_ADDRESS_TRANSLATION_MASK;
    }
#endif

    return (virtAddr);
}

uint64_t SOC_getSelfCpuClk(void) {
    uint64_t cpuClockRate = 0U;

#if defined(__C29__)
    cpuClockRate = (uint64_t)SysCtl_getClock(DEVICE_OSCSRC_FREQ);
#endif

    return cpuClockRate;
}