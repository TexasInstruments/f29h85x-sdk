/* ###########################################################################
 *
 * FILE:  sdl_sic.h
 *
 * TITLE: Diagnostic Library SIC software module header
 *
 *
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

########################################################################### */

#ifndef SDL_SIC_H
#define SDL_SIC_H

/*****************************************************************************
 *
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 *
 *****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*
 *
 * Includes
 */

#include <stdint.h>
#include <include/hw_types.h>
#include <include/sdl_types.h>
#include <include/sdlr_baseaddress.h>
#include <include/sdlr_sysctl.h>
#include <err_aggr/sdlr_err_aggr.h>
#include <err_aggr/sdl_err_aggr.h>
#include <sdl_esm.h>
#include <sdl_memss.h>

/**
 *
 * \addtogroup sdl_sic_group
 *
 * @{
 *
 */

/*
 *
 * Defines
 */

#define SDL_SIC_WRITE_KEY          ((uint32_t)0x5A5A << 16)
#define SDL_SIC_RESET_VECTOR       0x00000000U
#define SDL_SIC_SET_VECTOR         0xFFFFFFFFU
#define SDL_SIC_ENABLE             0x1U
#define SDL_SIC_FLTEMU             0xA501U
#define SDL_SIC_FLTDIS             0xA500U
#define SDL_SIC_FLTEMU_UNC         0xA503U
#define SDL_SIC_FLTEMU_ACCGRPSEL   0x4U
#define SDL_SIC_FLTEMU_BITSEL      0x8U
#define SDL_SIC_FLTEMU_ADDR        0xCU
#define SDL_SIC_FLTEMU_CONFIG      0x0U
#define SDL_SIC_CPU_DR1CTL         0x2U
#define SDL_SIC_CPU_DR2CTL         0x4U
#define SDL_SIC_CPU_DWCTL          0x8U
#define SDL_SIC_CPU_PRCTL          0x1U
#define SDL_SIC_RTDMA_DRCTL        0x1U
#define SDL_SIC_RTDMA_DWCTL        0x2U
#define SDL_SIC_RTDMA_DRDATA       0x100U
#define SDL_SIC_RTDMA_DWDATA       0x200U
#define SDL_SIC_CPU_DR1DATA        0x200U
#define SDL_SIC_CPU_DR2DATA        0x400U
#define SDL_SIC_CPU_DWDATA         0x800U
#define SDL_SIC_CPU_PRDATA         0x100U
#define SDL_SIC_CLEAR              0x0U
#define SDL_SIC_READY_ERROR        0x37U
#define SDL_SIC_RTDMA_HALT         0x2U
#define SDL_SIC_RTDMA_PERINTE      0x800U

#define SDL_SIC_NO_INTERRUPT   (0u)
#define SDL_SIC_INTERRUPT      (1u)

/*
 *
 * Prototypes
 */

/**
 *
 * \brief Enables the SIC logic.
 *
 * This function enables the safety logic in the system. Though this logic is
 * Enabled by default but if user deliberately disables it for some reason, we
 * can use this API to enable it again.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_enableSafety")))
int32_t SDL_SIC_enableSafety(void);

/**
 *
 * \brief Disables the SIC logic.
 *
 * This function disables the safety logic in the system.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_disableSafety")))
int32_t SDL_SIC_disableSafety(void);

/**
 *
 * \brief Sets the SIC timeout.
 *
 * \param timeout is used to get the user defined timeout.
 *
 * This function sets the timeout for the SIC in the system.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_setTimeout")))
int32_t SDL_SIC_setTimeout(uint16_t timeout);

/**
 * \brief Emulates fault in the PIPE vector table.
 *
 * \param errAggrBase Base address of Error Aggregator.
 * \param intNum offset to calculate interrupt vector address.
 *
 * This function emulates a fault at the specified interrupt vector in the PIPE
 * vector table. The \p intNum parameter determines which interrupt vector is
 * targeted. Users must ensure that the corresponding interrupt is not enabled
 * during this test, as the fault injection may interfere with normal interrupt
 * handling and lead to unexpected behavior.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the intNum is out
 * of range.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_PIPE_emulateFault")))
int32_t SDL_SIC_PIPE_emulateFault(uint32_t errAggrBase, uint32_t intNum);

/**
 *
 * \brief Emulates a fault in the CPU(DW).
 *
 * \param errAggrBase Base address of Error Aggregator.
 * \param memAddr Memory address at which the fault should be emulated.
 *
 * This function simulates a fault in the CPU by configuring a specified RAM
 * address. The user must ensure that the provided address is not currently
 * in use by the program or part of the stack, as the fault emulation will
 * corrupt the memory at that address, rendering it unusable during normal
 * program execution.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the memAddr
 * is invalid.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_CPU_DW_emulateFault")))
int32_t SDL_SIC_CPU_DW_emulateFault(uint32_t errAggrBase, uint32_t *memAddr);

/**
 *
 * \brief Emulates a fault in the CPU(DR1).
 *
 * \param errAggrBase Base address of Error Aggregator.
 * \param memAddr Memory address at which the fault should be emulated.
 *
 * This function simulates a fault in the CPU by configuring a specified RAM
 * address. The user must ensure that the provided address is not currently
 * in use by the program or part of the stack, as the fault emulation will
 * corrupt the memory at that address, rendering it unusable during normal
 * program execution.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the memAddr
 * is invalid.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_CPU_DR1_emulateFault")))
int32_t SDL_SIC_CPU_DR1_emulateFault(uint32_t errAggrBase, uint32_t *memAddr);

/**
 *
 * \brief Emulates a fault in the CPU(DR2).
 *
 * \param errAggrBase Base address of Error Aggregator.
 * \param memAddr Memory address at which the fault should be emulated.
 *
 * This function simulates a fault in the CPU by configuring a specified RAM
 * address. The user must ensure that the provided address is not currently
 * in use by the program or part of the stack, as the fault emulation will
 * corrupt the memory at that address, rendering it unusable during normal
 * program execution.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the memAddr
 * is invalid.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_CPU_DR2_emulateFault")))
int32_t SDL_SIC_CPU_DR2_emulateFault(uint32_t errAggrBase, uint32_t *memAddr);

/**
 *
 * \brief Emulates a fault in the CPU(PR).
 *
 * \param errAggrBase Base address of Error Aggregator.
 * \param memAddr Memory address at which the fault should be emulated.
 *
 * This function simulates a fault in the CPU by configuring a specified RAM
 * address. The user must ensure that the provided address is not currently
 * in use by the program or part of the stack, as the fault emulation will
 * corrupt the memory at that address, rendering it unusable during normal
 * program execution.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the memAddr
 * is invalid.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_CPU_PR_emulateFault")))
int32_t SDL_SIC_CPU_PR_emulateFault(uint32_t errAggrBase, uint32_t *memAddr);

/**
 *
 * \brief Emulates fault in the RTDMA(DR).
 *
 * \param errAggrBase Base address of Error Aggregator.
 * \param dmaBase   Base address of RTDMA(RTDMA1/RTDMA2).
 * \param dmaChBase Base address of the RTDMA channel.
 * \param destAddr  Destination address to setup the RTDMA transfer.
 * \param srcAddr   Source address to setup the RTDMA transfer.
 *
 * This function emulates the fault for the RTDMA(both RTDMA1/RTDMA2). This
 * function reconfigures the RTDMA module and uses channel 1 to perform the
 * fault injection test. Users should note that this function does not save
 * or restore the original RTDMA configuration registers. Therefore, any
 * existing RTDMA settings will be overwritten, and the module will not be
 * restored to its previous state after the test completes.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the instance or
 * destAddr or srcAddr is invalid.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_RTDMA_DR_emulateFault")))
int32_t SDL_SIC_RTDMA_DR_emulateFault(uint32_t errAggrBase, uint32_t dmaBase, uint32_t dmaChBase,
                                      const void *destAddr, const void *srcAddr);

/**
 *
 * \brief Emulates fault in the RTDMA(DW).
 *
 * \param errAggrBase Base address of Error Aggregator.
 * \param dmaBase     Base address of RTDMA (RTDMA1/RTDMA2).
 * \param dmaChBase   Base address of the RTDMA channel.
 * \param destAddr    Destination address to setup the RTDMA transfer.
 * \param srcAddr     Source address to setup the RTDMA transfer.
 *
 * This function emulates the fault for the RTDMA(both RTDMA1/RTDMA2). This
 * function reconfigures the RTDMA module and uses channel 1 to perform the
 * fault injection test. Users should note that this function does not save
 * or restore the original RTDMA configuration registers. Therefore, any
 * existing RTDMA settings will be overwritten, and the module will not be
 * restored to its previous state after the test completes.
 *
 * \return If the test passes, it returns \b SDL_PASS. If the test
 * fails, then it returns \b SDL_EFAIL or \b SDL_EBADARGS if the instance or
 * destAddr or srcAddr is invalid.
 *
 */
__attribute__((section(".text.link2.SDL_SIC_RTDMA_DW_emulateFault")))
int32_t SDL_SIC_RTDMA_DW_emulateFault(uint32_t errAggrBase, uint32_t dmaBase, uint32_t dmaChBase,
                                      const void *destAddr, const void *srcAddr);

/**
 *
 * \brief Helper Assembly function to Emulate fault in the CPU(DR2).
 *
 */
void SDL_SIC_dr2Read(uint32_t memAddr);

/**
 *
 * \brief Helper Assembly function to Emulate fault in the CPU(PR).
 *
 */
void SDL_SIC_exec(uint32_t memAddr);

/**
 *
 * \brief Handles ESM interrupts.
 * 
 * This function handles ESM interrupts triggered by SIC tests.
 * When an interrupt occurs, the ESM triggers the ISR, which in turn calls this 
 * function to safely and appropriately handle the interrupt.
 *
 */
void SDL_SIC_handleESMIntr(uint32_t esmBase, uint32_t intSrc, void *callbackArg);

/**
 *
 * \brief Determines and returns the memory region type for the specified address.
 * 
 * \param memAddr Specified memory address.
 * 
 * This function is used to checks and returns the memory type of the given 
 * address (e.g., LDA, LPA ,CDA, etc.) or returns SDL_MEMSS_RAM_INVALID if the provided
 * address doesn't fit in any of the expected ranges.
 *
 */
SDL_MEMSS_RAM SDL_MEMSS_getRAMBlock(uint32_t memAddr);

/** @} */

/*****************************************************************************
 *
 * Mark the end of the C bindings section for C++ compilers.
 *
 *****************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* SDL_SIC_H */
