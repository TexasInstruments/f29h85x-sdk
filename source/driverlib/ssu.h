//##################################################################################################
//
// FILE:   ssu.h
//
// TITLE:  C29x Safety & Security Unit (SSU) driver.
//
//##################################################################################################
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

//##################################################################################################

#ifndef SSU_H
#define SSU_H

//**************************************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//**************************************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//**************************************************************************************************
//
//! \addtogroup ssu_api Ssu
//! @{
//
//**************************************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssu.h"
#include "cpu.h"
#include "debug.h"

//**************************************************************************************************
//
//! Number of APRs available in the device
//
//**************************************************************************************************
#define SSU_TOTAL_AP        64U
#define SSU_TOTAL_AP_EXT    2U

//**************************************************************************************************
//
//! Values that can be passed as parameter \e linkAccess in
//! SSU_setAccessProtection() function
//
//**************************************************************************************************
#define SSU_LINK_NO_ACCESS(x)    (0U)
#define SSU_LINK_RD_ACCESS(x)    (1U << ((x) * 2U))
#define SSU_LINK_RW_ACCESS(x)    (3U << ((x) * 2U))

//**************************************************************************************************
//
//! Values that can be passed as parameter \e wipeOnClear in
//! SSU_forceRAMOPEN() function
//
//**************************************************************************************************
#define SSU_WIPE_ON_CLR_ENABLE    true
#define SSU_WIPE_ON_CLR_DSIABLE   false

//**************************************************************************************************
//
// Macros for accessing SSU registers.
//
//**************************************************************************************************
#define SSU_AP_CFG(cpu, x)     (SSUCPU1AP_BASE + (0x1000U * ((uint32_t)cpu)) + SSU_O_AP_CFG(x))
#define SSU_AP_START(cpu, x)   (SSUCPU1AP_BASE + (0x1000U * ((uint32_t)cpu)) + SSU_O_AP_START(x))
#define SSU_AP_END(cpu, x)     (SSUCPU1AP_BASE + (0x1000U * ((uint32_t)cpu)) + SSU_O_AP_END(x))
#define SSU_AP_LOCK(cpu, x)    (SSUCPU1AP_BASE + (0x1000U * ((uint32_t)cpu)) + SSU_O_AP_LOCK(x))
#define SSU_AP_COMMIT(cpu, x)  (SSUCPU1AP_BASE + (0x1000U * ((uint32_t)cpu)) + SSU_O_AP_COMMIT(x))
#define SSU_AP_ACCESS(cpu, x)  (SSUCPU1AP_BASE + (0x1000U * ((uint32_t)cpu)) + SSU_O_AP_ACCESS(x))

//**************************************************************************************************
//
//! Values that can be passed as parameter \e cpu in all the functions
//
//**************************************************************************************************
typedef enum
{
    SSU_CPU1 = 0,
    SSU_CPU2 = 1,
    SSU_CPU3 = 2
} SSU_CPUID;

//**************************************************************************************************
//
//! SSU Modes. Value returned by SSU_getSSUMode() function
//
//**************************************************************************************************
typedef enum
{
    SSU_MODE1 = 0x30,
    SSU_MODE2 = 0x0C,
    SSU_MODE3 = 0x03
} SSU_Mode;

//**************************************************************************************************
//
//! SSU Links
//
//**************************************************************************************************
typedef enum{
    SSU_LINK0   = 0,
    SSU_LINK1   = 1,
    SSU_LINK2   = 2,
    SSU_LINK3   = 3,
    SSU_LINK4   = 4,
    SSU_LINK5   = 5,
    SSU_LINK6   = 6,
    SSU_LINK7   = 7,
    SSU_LINK8   = 8,
    SSU_LINK9   = 9,
    SSU_LINK10  = 10,
    SSU_LINK11  = 11,
    SSU_LINK12  = 12,
    SSU_LINK13  = 13,
    SSU_LINK14  = 14,
    SSU_LINK15  = 15,
} SSU_Link;

typedef enum
{
    SSU_EXE_LINK1   = 1,
    SSU_EXE_LINK2   = 2,
    SSU_EXE_LINK3   = 3,
    SSU_EXE_LINK4   = 4,
    SSU_EXE_LINK5   = 5,
    SSU_EXE_LINK6   = 6,
    SSU_EXE_LINK7   = 7,
    SSU_EXE_LINK8   = 8,
    SSU_EXE_LINK9   = 9,
    SSU_EXE_LINK10  = 10,
    SSU_EXE_LINK11  = 11,
    SSU_EXE_LINK12  = 12,
    SSU_EXE_LINK13  = 13,
    SSU_EXE_LINK14  = 14,
    SSU_EXE_LINK15  = 15,
    SSU_EXE_DISABLE = 16
} SSU_APExeLink;

typedef enum
{
    SSU_API_LINK0   = 0,
    SSU_API_LINK1   = 1,
    SSU_API_LINK2   = 2,
    SSU_API_LINK3   = 3,
    SSU_API_LINK4   = 4,
    SSU_API_LINK5   = 5,
    SSU_API_LINK6   = 6,
    SSU_API_LINK7   = 7,
    SSU_API_LINK8   = 8,
    SSU_API_LINK9   = 9,
    SSU_API_LINK10  = 10,
    SSU_API_LINK11  = 11,
    SSU_API_LINK12  = 12,
    SSU_API_LINK13  = 13,
    SSU_API_LINK14  = 14,
    SSU_API_LINK15  = 15,
    SSU_API_DISABLE = 16
}SSU_APILink;

//**************************************************************************************************
//
//! SSU STACKs
//
//**************************************************************************************************
typedef enum
{
    SSU_STACK1 = 1,
    SSU_STACK2 = 2,
    SSU_STACK3 = 3,
    SSU_STACK4 = 4,
    SSU_STACK5 = 5,
    SSU_STACK6 = 6,
    SSU_STACK7 = 7
} SSU_Stack;

//**************************************************************************************************
//
//! SSU Zones
//
//**************************************************************************************************
typedef enum
{
    SSU_ZONE1 = 1,
    SSU_ZONE2 = 2,
    SSU_ZONE3 = 3,
} SSU_Zone;

//**************************************************************************************************
//
//! Values that can be passed as parameter \e reset in SSU_controlCPUReset()
//! functions
//
//**************************************************************************************************
typedef enum
{
    SSU_CORE_RESET_ACTIVE     = 0xC9,  //! CPU is held in reset
    SSU_CORE_RESET_DEACTIVE   = 0x36   //! CPU reset is released (if no HSM) or
                                       //! determined by HSM input
} SSU_CoreReset;

//**************************************************************************************************
//
//! Struct used as parameter to SSU_setAccessProtection() function
//
//**************************************************************************************************
typedef struct
{
    //! AP region number
    uint8_t       region;

    //! Start address (granularity of 4KB, must end with 000)
    uint32_t      startAddr;

    //! End address (granularity of 4KB, must end with FFF)
    uint32_t      endAddr;

    //! LinkID the range is associated with when run as code.
    //! Use SSU_EXE_LINK1..15 to enable execution.
    //! Use SSU_EXE_DISABLE to disable execution.
    SSU_APExeLink exelinkID;

    //! Access Protection Inheritance Link.
    //! Use SSU_API_LINK1..15 to enable Access Protection Inheritance.
    //! Use SSU_API_DISABLE to disable Access Protection Inheritance
    SSU_APILink   apiLinkID;

    //! Link Access. Can be OR'ed value of SSU_LINK_NO_ACCESS(linkID) or
    //! SSU_LINK_RD_ACCESS(linkID) or SSU_LINK_RW_ACCESS(linkID)
    //! for each link ID
    uint32_t      linkAccess;

} SSU_APConfig;

//**************************************************************************************************
//
//! SSU SECCFG sector
//
//**************************************************************************************************
typedef struct
{
    struct
    {
        uint32_t LOCK     : 1;
        uint32_t rsvd1    : 11;
        uint32_t START    : 20;
        uint32_t COMMIT   : 1;
        uint32_t rsvd2    : 11;
        uint32_t END      : 20;
        uint32_t ACCESS;
        uint16_t rsvd3;
        uint32_t LINKID   : 4;
        uint32_t rsvd4    : 2;
        uint32_t DISABLE  : 1;
        uint32_t XE       : 1;
        uint32_t APILINK  : 4;
        uint32_t rsvd5    : 2;
        uint32_t APILINKE : 1;
        uint32_t rsvd6    : 1;
    } AP_REGS[96];                      // 0x000 - 0x5F8

    uint8_t   rsvd_0[0x68];             // 0x600 - 0x660

    uint8_t   WEPROT_CODE_BANKS;        // 0x668
    uint8_t   WEPROT_CODE_LOCK;
    uint8_t   WEPROT_CODE_COMMIT;
    uint8_t   rsvd_1;
    uint8_t   WEPROT_DATA_BANKS;
    uint8_t   WEPROT_DATA_LOCK;
    uint8_t   WEPROT_DATA_COMMIT;
    uint8_t   rsvd_2;

    uint32_t  WEPROT_FLC1_B0_A;         // 0x670
    uint16_t  rsvd_3;
    uint8_t   WEPROT_FLC1_B0_LOCK;
    uint8_t   WEPROT_FLC1_B0_COMMIT;

    uint32_t  WEPROT_FLC1_B0_B;         // 0x678
    uint32_t  rsvd_4;

    uint32_t  WEPROT_FLC1_B2_A;         // 0x680
    uint16_t  rsvd_5;
    uint8_t   WEPROT_FLC1_B2_LOCK;
    uint8_t   WEPROT_FLC1_B2_COMMIT;

    uint32_t  WEPROT_FLC1_B2_B;         // 0x688
    uint32_t  rsvd_6;

    uint32_t  WEPROT_FLC2_B0_A;         // 0x690
    uint16_t  rsvd_7;
    uint8_t   WEPROT_FLC2_B0_LOCK;
    uint8_t   WEPROT_FLC2_B0_COMMIT;

    uint32_t  WEPROT_FLC2_B0_B;         // 0x698
    uint32_t  rsvd_8;

    uint32_t  WEPROT_FLC2_B2_A;         // 0x6A0
    uint16_t  rsvd_9;
    uint8_t   WEPROT_FLC2_B2_LOCK;
    uint8_t   WEPROT_FLC2_B2_COMMIT;

    uint32_t  WEPROT_FLC2_B2_B;         // 0x6A8
    uint32_t  rsvd_10;

    uint64_t  rsvd_11;                  // 0x6B0

    struct
    {
        uint16_t LINK      : 4;
        uint16_t rsvd1     : 4;
        uint16_t CPU       : 3;
        uint16_t rsvd2     : 1;
        uint16_t UPDATE_EN : 4;
    } ZONE1_CFG,  ZONE2_CFG,  ZONE3_CFG, SECCFG_UPDATE_CFG; // 0x6B8

    uint64_t  ZONE1_PDBGPSWD_L;         // 0x6C0
    uint64_t  ZONE1_PDBGPSWD_H;         // 0x6C8
    uint64_t  rsvd_12[2];               // 0x6D0 - 0x6D8
    uint64_t  ZONE1_FDBGPSWD_L;         // 0x6E0
    uint64_t  ZONE1_FDBGPSWD_H;         // 0x6E8
    uint64_t  rsvd_13[2];               // 0x6F0 - 0x6F8
    uint64_t  ZONE2_PDBGPSWD_L;         // 0x700
    uint64_t  ZONE2_PDBGPSWD_H;         // 0x708
    uint64_t  rsvd_14[2];               // 0x710 - 0x718
    uint64_t  ZONE2_FDBGPSWD_L;         // 0x720
    uint64_t  ZONE2_FDBGPSWD_H;         // 0x728
    uint64_t  rsvd_15[2];               // 0x730 - 0x738
    uint64_t  ZONE3_PDBGPSWD_L;         // 0x740
    uint64_t  ZONE3_PDBGPSWD_H;         // 0x748
    uint64_t  rsvd_16[2];               // 0x750 - 0x758
    uint64_t  ZONE3_FDBGPSWD_L;         // 0x760
    uint64_t  ZONE3_FDBGPSWD_H;         // 0x768
    uint64_t  rsvd_17[2];               // 0x770 - 0x778
    uint64_t  C29DBGEN_PSWD_L;          // 0x780
    uint64_t  C29DBGEN_PSWD_H;          // 0x788
    uint64_t  rsvd_18[2];               // 0x790 - 0x798

    struct
    {
        uint16_t C29DBGEN_CFG : 3;
        uint16_t rsvd1        : 1;
        uint16_t ZONE1        : 3;
        uint16_t rsvd2        : 1;
        uint16_t ZONE2        : 3;
        uint16_t rsvd3        : 1;
        uint16_t ZONE3        : 3;
        uint16_t rsvd4        : 1;
    } DEBUG_CFG;                        // 0x7A0
    uint8_t   DEBUG_CFG_LOCK;
    uint8_t   DEBUG_CFG_COMMIT;
    uint8_t   HSM_LOCKOUT;
    uint8_t   ENABLE_XTAL;
    uint16_t  rsvd_19;

    uint32_t  BOOTPIN_CONFIG;           // 0x7A8
    uint8_t   LPOST_MPOST_EN;
    uint8_t   ERROR_STS_PIN;
    uint8_t   BOOT_LOADER_LOCK;
    uint8_t   rsvd_20;

    uint8_t   rsvd_21;                  // 0x7B0
    uint8_t   EMU_BOOTEN;
    uint8_t   RAMOPEN_LOCK;
    uint8_t   RAMOPEN_COMMIT;
    uint32_t  rsvd_22;

    uint64_t  SECT_STATUS;              // 0x7B8
    uint64_t  SECT_UPDATE_CTR;          // 0x7C0

    uint32_t  BOOTDEF_LOW;              // 0x7C8
    uint32_t  BOOTDEF_HIGH;

    uint8_t   rsvd_23[3];               // 0x7D0
    uint8_t   STACK3_CFG;
    uint8_t   STACK4_CFG;
    uint8_t   STACK5_CFG;
    uint8_t   STACK6_CFG;
    uint8_t   STACK7_CFG;

    uint8_t   rsvd_24[3];               // 0x7D8
    uint8_t   LINK3_CFG;
    uint8_t   LINK4_CFG;
    uint8_t   LINK5_CFG;
    uint8_t   LINK6_CFG;
    uint8_t   LINK7_CFG;

    uint8_t   LINK8_CFG;                // 0x7E0
    uint8_t   LINK9_CFG;
    uint8_t   LINK10_CFG;
    uint8_t   LINK11_CFG;
    uint8_t   LINK12_CFG;
    uint8_t   LINK13_CFG;
    uint8_t   LINK14_CFG;
    uint8_t   LINK15_CFG;

    uint64_t  rsvd_25;                  // 0x7E8

    uint8_t   SECCFG_FORMAT_VER;        // 0x7F0
    uint8_t   rsvd_26[3];
    uint32_t  SECCFG_CRC;

    uint32_t  SSU_MODE;                 //  0x7F8
    uint16_t  UPP_REVISION;
    uint16_t  rsvd_27;
} SSU_SECCFG;



//**************************************************************************************************
//
// Prototypes for the APIs.
//
//**************************************************************************************************

//**************************************************************************************************
//
//! Sets the Access Protection Region
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \param config  Array of AP region configurations. Refer to the struct SSU_APConfig for details
//! \param length  Length of the config array
//!
//! Example usage :
//!     - SSU_APConfig config[] =
//!         {
//!             {5, 0x200F0000, 0x200F0FFF, SSU_EXE_DISABLE, SSU_API_LINK10,
//!                 SSU_LINK_RD_ACCESS(SSU_LINK6) | SSU_LINK_RW_ACCESS(SSU_LINK7)},
//!
//!             {3, 0x80000000, 0x80001FFF, SSU_EXE_LINK4, SSU_API_DISABLE,
//!                 0},
//!         };
//!     - SSU_setAccessProtection(SSU_CPU1, config, 2);
//!
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_setAccessProtection")))
extern void
SSU_setAccessProtection(SSU_CPUID cpu, SSU_APConfig config[], int length);

//**************************************************************************************************
//
//! Enables the Access Protection Region
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \param region  AP region number
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_enableAccessProtection")))
__attribute__((always_inline))
static inline void
SSU_enableAccessProtection(SSU_CPUID cpu, uint32_t region)
{
    HWREG(SSU_AP_CFG(cpu, region)) &= ~(uint32_t)SSU_AP_CFG_APD;
}

//**************************************************************************************************
//
//! Disables the Access Protection Region
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \param region  AP region number
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_disableAccessProtection")))
__attribute__((always_inline))
static inline void
SSU_disableAccessProtection(SSU_CPUID cpu, uint32_t region)
{
    HWREG(SSU_AP_CFG(cpu, region)) |= SSU_AP_CFG_APD;
}

//**************************************************************************************************
//
//! Returns the SSU Mode
//!
//! \return SSU Mode (SSU_MODE1 / SSU_MODE2 / SSU_MODE3).
//
//**************************************************************************************************
__attribute__((always_inline))
static inline SSU_Mode
SSU_getSSUMode(void)
{
    return((SSU_Mode)HWREG(SSUGEN_BASE + SSU_O_MODE));
}

//**************************************************************************************************
//
//! Returns the CPU ID
//!
//! \return CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//
//**************************************************************************************************
__attribute__((always_inline))
static inline SSU_CPUID
SSU_getCPUID(void)
{
    return((SSU_CPUID)((HWREG(SSUGEN_BASE + SSU_O_CPUID) & SSU_CPUID_CPUID_M) - 1U));
}

//**************************************************************************************************
//
//! Locks the AP registers
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \param region  AP region number
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_lockAPRegisters")))
__attribute__((always_inline))
static inline void
SSU_lockAPRegisters(SSU_CPUID cpu, uint32_t region)
{
    HWREG(SSU_AP_LOCK(cpu, region)) = 1U;
}

//**************************************************************************************************
//
//! Unlocks the AP registers
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \param region  AP region number
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_unlockAPRegisters")))
__attribute__((always_inline))
static inline void
SSU_unlockAPRegisters(SSU_CPUID cpu, uint32_t region)
{
    HWREG(SSU_AP_LOCK(cpu, region)) = 0U;
}

//**************************************************************************************************
//
//! Commits the AP registers
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \param region  AP region number
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_commitAPRegisters")))
__attribute__((always_inline))
static inline void
SSU_commitAPRegisters(SSU_CPUID cpu, uint32_t region)
{
    HWREG(SSU_AP_COMMIT(cpu, region)) = 1U;
}

//**************************************************************************************************
//
//! Locks all the AP registers
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_lockAllAPRegisters")))
__attribute__((always_inline))
static inline void
SSU_lockAllAPRegisters(SSU_CPUID cpu)
{
    uint32_t i;
    for(i = 0U; i < SSU_TOTAL_AP; i++)
    {
        HWREG(SSU_AP_LOCK(cpu, i)) = 1U;
    }
}

//**************************************************************************************************
//
//! Commits all the AP registers
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_commitAllAPRegisters")))
__attribute__((always_inline))
static inline void
SSU_commitAllAPRegisters(SSU_CPUID cpu)
{
    uint32_t i;
    for(i = 0U; i < SSU_TOTAL_AP; i++)
    {
        HWREG(SSU_AP_COMMIT(cpu, i)) = 1U;
    }
}

//**************************************************************************************************
//
//! Enable LINK2 AP Override
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_enableLink2APOverride")))
__attribute__((always_inline))
static inline void
SSU_enableLink2APOverride(SSU_CPUID cpu)
{
    HWREG(SSUGEN_BASE + SSU_O_LINK2_AP_OVERRIDE) |= 1U << (uint8_t)cpu;
}

//**************************************************************************************************
//
//! Disable LINK2 AP Override
//!
//! \param cpu     CPU ID (SSU_CPU1 / SSU_CPU2 / SSU_CPU3)
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_disableLink2APOverride")))
__attribute__((always_inline))
static inline void
SSU_disableLink2APOverride(SSU_CPUID cpu)
{
    HWREG(SSUGEN_BASE + SSU_O_LINK2_AP_OVERRIDE) &= ~(1U << (uint8_t)cpu);
}

//**************************************************************************************************
//
//! Configure CPU2/ CPU3 Boot
//!
//! \param cpu is the CPU whose boot is to be configured (SSU_CPU2 / SSU_CPU3)
//! \param addr is the address to which the CPU should boot (Reset vctor).
//! \param link is the SSU link to which the CPU should boot.
//!
//! This function configures the address and link to which CPU2/ CPU3 should boot to.
//!
//! \note This API can be called by CPU1.LINK2 only. The call must be in the applictaion
//! code prior to releasing the corresponding CPU from reset.
//!
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_configBootAddress")))
__attribute__((always_inline))
static inline void
SSU_configBootAddress(SSU_CPUID cpu, uint32_t addr, SSU_Link link)
{
    if(cpu == SSU_CPU2)
    {
        HWREG(SSUCPU2CFG_BASE + SSU_O_RST_VECT) = addr;
        HWREG(SSUCPU2CFG_BASE + SSU_O_RST_LINK) = link;
    }
    else if(cpu == SSU_CPU3)
    {
        HWREG(SSUCPU3CFG_BASE + SSU_O_RST_VECT) = addr;
        HWREG(SSUCPU3CFG_BASE + SSU_O_RST_LINK) = link;
    }
    else
    {
        //
        // Invalid option
        //
    }
}

//**************************************************************************************************
//
//! Configure CPU2/ CPU3 NMI
//!
//! \param cpu is the CPU whose NMI is to be configured (SSU_CPU2 / SSU_CPU3)
//! \param addr is the address of NMI vector.
//! \param link is the SSU link of the NMI vector.
//!
//! This function configures the address and link of CPU2/ CPU3 NMI.
//!
//! \note This API can be called by CPU1.LINK2 only. The call must be in the applictaion
//! code prior to releasing the corresponding CPU from reset.
//!
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_configNmiAddress")))
__attribute__((always_inline))
static inline void
SSU_configNmiAddress(SSU_CPUID cpu, uint32_t addr, SSU_Link link)
{
    if(cpu == SSU_CPU2)
    {
        HWREG(SSUCPU2CFG_BASE + SSU_O_DEF_NMI_VECT) = addr;
        HWREG(SSUCPU2CFG_BASE + SSU_O_DEF_NMI_LINK) = link;
    }
    else if(cpu == SSU_CPU3)
    {
        HWREG(SSUCPU3CFG_BASE + SSU_O_DEF_NMI_VECT) = addr;
        HWREG(SSUCPU3CFG_BASE + SSU_O_DEF_NMI_LINK) = link;
    }
    else
    {
        //
        // Invalid option
        //
    }
}

//**************************************************************************************************
//
//! Controls the reset of CPU2/CPU3 by CPU1
//!
//! \param cpu is the CPU which is reset (SSU_CPU2 / SSU_CPU3)
//! \param control is to deactivate / activate the reset to the CPU.
//!
//! This function lets CPU1 control the reset of CPU2/ CPU3. The CPU is held in reset or the reset
//! is released depending on the \e control parameter passed. \e control must be a value from the
//! enumeration SSU_CoreReset.
//!
//! \note This API is applicable only for the CPU1 subsystem.
//!
//! \return None.
//
//**************************************************************************************************
__attribute__((section(".text.link2.SSU_controlCPUReset")))
__attribute__((always_inline))
static inline void
SSU_controlCPUReset(SSU_CPUID cpu, SSU_CoreReset control)
{
    if(cpu == SSU_CPU2)
    {
        HWREG(SSUCPU2CFG_BASE + SSU_O_CPU_RST_CTRL) = control;
    }
    else if(cpu == SSU_CPU3)
    {
        HWREG(SSUCPU3CFG_BASE + SSU_O_CPU_RST_CTRL) = control;
    }
    else
    {
        //
        // Invalid option
        //
    }
}


//**************************************************************************************************
//
//! Claim Flash Semaphore
//!
//! \return true if the semaphore is successfully assigned, false if semaphore is already assigned
//! to a different CPU or LINK .
//
//**************************************************************************************************
__attribute__((always_inline))
static inline bool
SSU_claimFlashSemaphore(void)
{
    bool status = false;

    //
    // Check if the semaphore is already assigned
    //
    if((HWREG(SSUGEN_BASE + SSU_O_FLSEMSTAT) & SSU_FLSEMSTAT_ASSIGNED) == 0U)
    {
        //
        // Claim the semaphore
        //
        HWREG(SSUGEN_BASE + SSU_O_FLSEMREQ) = 1U;

        //
        // Check if the semaphore is assigned to the current CPU and LINK
        //
        if((HWREG(SSUGEN_BASE + SSU_O_FLSEMSTAT) & SSU_FLSEMSTAT_MATCH) != 0U)
        {
            status = true;
        }
    }
    return(status);
}

//**************************************************************************************************
//
//! Release Flash Semaphore
//!
//! \return true if the semaphore is successfully released, false if semaphore was not already
//! assigned to the current CPU or LINK
//
//**************************************************************************************************
__attribute__((always_inline))
static inline bool
SSU_releaseFlashSemaphore(void)
{
    bool status = false;

    //
    // Check if the semaphore is already assigned to the current CPU and LINK
    //
    if((HWREG(SSUGEN_BASE + SSU_O_FLSEMSTAT) & SSU_FLSEMSTAT_MATCH) != 0U)
    {
        //
        // Release the semaphore
        //
        HWREG(SSUGEN_BASE + SSU_O_FLSEMCLR) = 1U;
        status = true;
    }
    return(status);
}

//**************************************************************************************************
//
//! Force RAMOPEN
//!
//! \param wipeOnClear defines whether the HW has to perform a RAMINIT when RAMOPEN is cleared. Use
//!                     macro SSU_WIPE_ON_CLR_ENABLE or SSU_WIPE_ON_CLR_DISABLE
//! \note This function is only applicable to CPU1
//! \return None
//!
//**************************************************************************************************
__attribute__((section(".text.link1")))
__attribute__((always_inline))
static inline void
SSU_forceRAMOPEN(bool wipeOnClear)
{
    if(wipeOnClear)
    {
        HWREG(SSUCPU1CFG_BASE  + SSU_O_RAMOPENFRC) = SSU_RAMOPENFRC_SET_LINK1 |
                                                     SSU_RAMOPENFRC_WIPE_ON_LINK1_CLR;
    }
    else
    {
        HWREG(SSUCPU1CFG_BASE  + SSU_O_RAMOPENFRC) = SSU_RAMOPENFRC_SET_LINK1;
    }
}

//**************************************************************************************************
//
//! Clear RAMOPEN
//!
//! \note This function is only applicable to CPU1
//! \return None
//!
//**************************************************************************************************
__attribute__((section(".text.link1")))
__attribute__((always_inline))
static inline void
SSU_clearRAMOPEN(void)
{
    HWREG(SSUCPU1CFG_BASE  + SSU_O_RAMOPENCLR) = SSU_RAMOPENCLR_CLEAR_LINK1;
}

//**************************************************************************************************
//
//! Get RAMOPEN status
//!
//! \note This function is only applicable to CPU1
//! \return Returns true if RAMOPEN is active, false otherwise
//! RAMs have become unsecured
//!
//**************************************************************************************************
__attribute__((section(".text.link1")))
__attribute__((always_inline))
static inline bool
SSU_getRAMOPENStatus(void)
{
    return((HWREG(SSUCPU1CFG_BASE  + SSU_O_RAMOPENSTAT) & SSU_RAMOPENSTAT_LINK1_RAMOPENS) != 0U);
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // SSU_H
