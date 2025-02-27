//###########################################################################
//
// FILE:   cpu.h
//
// TITLE:  Useful C29x CPU defines and driver.
//
//###########################################################################
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

#ifndef CPU_H
#define CPU_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"


//
// Define to enable interrupts
//
#ifndef EINT
#define EINT    __asm(" ENINT")
#endif
#ifndef ENINT
#define ENINT   __asm(" ENINT")
#endif

//
// Define to disable interrupts
//
#ifndef DINT
#define DINT    __asm(" DISINT")
#endif
#ifndef DISINT
#define DISINT  __asm(" DISINT")
#endif

//
// Define for emulation stop
//
#ifndef ESTOP0
#define ESTOP0   __asm(" EMUSTOP0")
#endif
#ifndef EMUSTOP0
#define EMUSTOP0 __asm(" EMUSTOP0")
#endif

//
// Define for no operation
//
#ifndef NOP
#define NOP    __asm(" NOP #1")
#endif

//
// Define for putting processor into a low-power mode
//
#ifndef IDLE
#define IDLE   __asm(" IDLE")
#endif

//
// Define for rounding to nearest even instead of rounding towards 0
//
#ifndef ROUND_TO_NEAREST_EVEN
#define ROUND_TO_NEAREST_EVEN   __asm__("MV ESTS,0x10000")
#endif

//*****************************************************************************
//
//! \addtogroup cpu_api C29CPU
//! @{
//
//*****************************************************************************
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_cpu.h"

//*****************************************************************************
//
//! Values that can be passed to CPU_lockRegister(),
//! CPU_unlockRegister(), CPU_commitRegister() as the \e registers
//! parameter.
//
//*****************************************************************************
#define CPU_C29_RTINT_STACK_REGS     CPU_C29_REGS_LOCK_C29_RTINT_STACK
#define CPU_C29_SECCALL_STACK_REGS   CPU_C29_REGS_LOCK_C29_SECCALL_STACK
#define CPU_C29_SECURE_REGS          CPU_C29_REGS_LOCK_C29_SECURE_REGS
#define CPU_C29_DIAG_REGS            CPU_C29_REGS_LOCK_C29_DIAG_REGS
#define CPU_C29_SELFTEST_REGS        CPU_C29_REGS_LOCK_C29_SELFTEST_REGS


//*****************************************************************************
//
//! Lock CPU registers
//!
//! \param registers Registers to be locked. Can be OR of the following -
//!                     - CPU_C29_RTINT_STACK
//!                     - CPU_C29_SECCALL_STACK
//!                     - CPU_C29_SECURE_REGS
//!                     - CPU_C29_DIAG_REGS
//!                     - CPU_C29_SELFTEST_REGS
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
CPU_lockRegister(uint32_t registers)
{
    HWREG(C29CPUSECURE_BASE + CPU_O_C29_REGS_LOCK) =
                (HWREG(C29CPUSECURE_BASE + CPU_O_C29_REGS_LOCK) | registers);
}

//*****************************************************************************
//
//! Unlock CPU registers
//!
//! \param registers Registers to be unlocked. Can be OR of the following -
//!                     - CPU_C29_RTINT_STACK
//!                     - CPU_C29_SECCALL_STACK
//!                     - CPU_C29_SECURE_REGS
//!                     - CPU_C29_DIAG_REGS
//!                     - CPU_C29_SELFTEST_REGS
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
CPU_unlockRegister(uint32_t registers)
{
    HWREG(C29CPUSECURE_BASE + CPU_O_C29_REGS_LOCK) =
                (HWREG(C29CPUSECURE_BASE + CPU_O_C29_REGS_LOCK) & ~registers);
}

//*****************************************************************************
//
//! Commit CPU registers
//!
//! \param registers Registers to be committed. Can be OR of the following -
//!                     - CPU_C29_RTINT_STACK
//!                     - CPU_C29_SECCALL_STACK
//!                     - CPU_C29_SECURE_REGS
//!                     - CPU_C29_DIAG_REGS
//!                     - CPU_C29_SELFTEST_REGS
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
CPU_commitRegister(uint32_t registers)
{
    HWREG(C29CPUSECURE_BASE + CPU_O_C29_REGS_COMMIT) =
              (HWREG(C29CPUSECURE_BASE + CPU_O_C29_REGS_COMMIT) | registers);
}

//*****************************************************************************
//
//! Set the warning level for protected call stack pointer
//!
//! \param level is the warning level set.
//!
//! Set the warning level for protected call stack pointer.
//! External logic may compare PSP with WARNPSP to generate early warning
//! interrupt to avoid protected call stack overflow.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
CPU_setPSPWarningLevel(uint16_t level)
{
    HWREGH(C29CPUSECURE_BASE + CPU_O_WARNPSP) = level;
}

//*****************************************************************************
//
//! Force TMU ROM Parity error
//!
//! This function forces the TMU ROM Parity Error. The key 0xA5 must be
//! written along with the force bit, otherwise, writes are ignored. The key
//! is cleared immediately after writing, so it must be written again for
//! every change to this bit.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
CPU_forceTMUROMParityError(void)
{
    HWREG(C29CPUDIAG_BASE + CPU_O_TMU_ROM_PAR_FORCE) =
          CPU_TMU_ROM_PAR_FORCE_KEY | CPU_TMU_ROM_PAR_FORCE_TMU_ROM_PAR_FORCE;
}

//*****************************************************************************
//
//! Clear TMU ROM Parity error
//!
//! This function clears the TMU ROM Parity Error. The key 0xA5 must be
//! written along with a write of 0 to the force bit, otherwise, writes are
//! ignored.
//!
//! \return None
//
//*****************************************************************************
__attribute__((always_inline))
static inline void
CPU_clearTMUROMParityError(void)
{
    HWREG(C29CPUDIAG_BASE + CPU_O_TMU_ROM_PAR_FORCE) =
                                                    CPU_TMU_ROM_PAR_FORCE_KEY;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // CPU_H
