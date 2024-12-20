//#############################################################################
//
// FILE:   bootrom.h
//
// TITLE:  Bootrom structures.
//
//#############################################################################
//
//
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

//#############################################################################

#ifndef __BOOTROM_H__
#define __BOOTROM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

//
//  Defines
//
/**
 * @brief   This is the length of the TI/Customer key public hash.
 */
#define CONFIG_SOCID_ROOTKEYHASH_LEN_BYTES      (64U)

/**
 * @brief   This is the length of the Unique identifier.
 */
#define CONFIG_SOCID_UNIQUEID_LEN_BYTES         (64U)

/**
 * @brief   This is the length of the device name
 */
#define CONFIG_SOCID_DEVNAME_LEN_BYTES          (12U)

/**
 * @brief   This is the size of the RFFT twiddle table
 */
#define RFFT_TABLE_SIZE                         (1020U)

/**
 * @brief   This is the size of the CFFT twiddle table
 */
#define CFFT_TABLE_SIZE                         (768U)

//
//  Enumerations
//

/**
 * @brief
 *  Bootrom Flow Status
 *
 * @details
 *  The enumeration describes the Bootrom flow status
 */
typedef enum
{
    /**
     * @brief   Flow status is NOT RUN
     */
    STATUS_NA   = 0x1,

    /**
     * @brief   Flow status is PASS
     */
    STATUS_PASS = 0x2,

    /**
     * @brief   Flow status is FAIL
     */
    STATUS_FAIL = 0x3
} status_t;

/**
 * @brief
 *  SOC Identifier Device Type
 *
 * @details
 *  The enumeration describes all the device types which are supported
 */
typedef enum
{
    SOCID_DeviceType_GP     = 0xABCD0001U,  /*!< General Purpose Device */
    SOCID_DeviceType_TEST,                  /*!< Test Device            */
    SOCID_DeviceType_EMU_FS,                /*!< EMU-FS Device          */
    SOCID_DeviceType_HS_FS,                 /*!< HS-FS Device           */
    SOCID_DeviceType_EMU_SE,                /*!< EMU-SE Device          */
    SOCID_DeviceType_HS_SE,                 /*!< HS-SE Device           */
    SOCID_DeviceType_EMU_KP,                /*!< EMU-KP Device          */
    SOCID_DeviceType_HS_KP,                 /*!< HS-KP Device           */
    SOCID_DeviceType_EMU_FA,                /*!< EMU-FA Device          */
    SOCID_DeviceType_HS_FA,                 /*!< HS-FA Device           */
}SOCID_DeviceType;

/**
 * @brief
 *  Flash Bank Mode
 *
 * @details
 *  The enumeration describes Flash Bank Modes
 */
typedef enum
{
    FLASH_BANK_MODE_0       = 0x03U,
    FLASH_BANK_MODE_1       = 0x06U,
    FLASH_BANK_MODE_2       = 0x09U,
    FLASH_BANK_MODE_3       = 0x0CU,
    FLASH_BANK_MODE_INVALID = 0x55U
}flashBankMode_t;

/**
 * @brief
 *  Flash Bank Swap
 *
 * @details
 *  The enumeration describes Flash Bank Swap settings
 */
typedef enum
{
    FLASH_BANK_SWAP_DEFAULT   = 0xC9U,
    FLASH_BANK_SWAP_ALTERNATE = 0x36U,
    FLASH_BANK_SWAP_INVALID   = 0x5555U
}flashBankSwap_t;

/**
 * @brief
 *  Secvalid
 *
 * @details
 *  The enumeration describes Secvalid settings
 */
typedef enum
{
    SECVALID_BASE      = 0xC9U,
    SECVALID_ALTERNATE = 0x36U,
    SECVALID_INVALID   = 0x550055U
}secValid_t;

/**
 * @brief
 *  Ssumode
 *
 * @details
 *  The enumeration describes Ssumode settings
 */
typedef enum
{
    SSUMODE_1       = 0x30U,
    SSUMODE_2       = 0x0CU,
    SSUMODE_3       = 0x03U,
    SSUMODE_INVALID = 0x55U
}ssuMode_t;

/**
 * @brief
 *  Device Life Cycle States
 *
 * @details
 *  The enumeration describes the Device Life Cycle States
 */
typedef enum
{
    /**
     * @brief   BAD state
     */
    DEV_LIFE_CYCLE_STATE_BAD    = 0x11123D7DU,

    /**
     * @brief   TEST state
     */
    DEV_LIFE_CYCLE_STATE_TEST   = 0xB5A66409U,

    /**
     * @brief   GP state
     */
    DEV_LIFE_CYCLE_STATE_GP     = 0x021CCF0FU,

    /**
     * @brief   EMU SE state
     */
    DEV_LIFE_CYCLE_STATE_EMU_SE = 0xEFC02492U,

    /**
     * @brief   EMU KP state
     */
    DEV_LIFE_CYCLE_STATE_EMU_KP = 0x0562C717U,

    /**
     * @brief   EMU FS state
     */
    DEV_LIFE_CYCLE_STATE_EMU_FS = 0x4A8038E3U,

    /**
     * @brief   EMU FA state
     */
    DEV_LIFE_CYCLE_STATE_EMU_FA = 0x3DC57F36U,

    /**
     * @brief   HS SE state
     */
    DEV_LIFE_CYCLE_STATE_HS_SE  = 0xA4B45974U,

    /**
     * @brief   HS KP state
     */
    DEV_LIFE_CYCLE_STATE_HS_KP  = 0x2D3B68E5U,

    /**
     * @brief   HS FS state
     */
    DEV_LIFE_CYCLE_STATE_HS_FS  = 0xA5401C71U,

    /**
     * @brief   HS FA state
     */
    DEV_LIFE_CYCLE_STATE_HS_FA  = 0x2C6DB3FAU
} devLifeCycleState_t;

/**
 * @brief
 *  Link0 error ids
 *
 * @details
 *  The enumeration describes the Link0 error ids
 */
typedef enum
{
    /**
     * @brief   No error
     */
    LINK0_ERR_ID_NONE           = 0xF487DA78U,

    /**
     * @brief   LINK0 APR configurtation error
     */
    LINK0_ERR_ID_APR_CONFIG     = 0x2AC69B4FU,

    /**
     * @brief   SSU POST error
     */
    LINK0_ERR_ID_SSU_POST       = 0xADF53EF6U,

    /**
     * @brief   SSU configurtation error
     */
    LINK0_ERR_ID_SSU_CONFIG     = 0x57DE827CU,

    /**
     * @brief   NMI error
     */
    LINK0_ERR_ID_NMI            = 0xCDF5847DU,

    /**
     * @brief   NMI error
     */
    LINK0_ERR_ID_SECCFG_APR     = 0x69D473BEU,

    /**
     * @brief   WDG Sync Busy
     */
    LINK0_ERR_ID_WDG_SYNCBUSY   = 0xFE3BC723U,

    /**
     * @brief   XTAL Sync Busy
     */
    LINK0_ERR_ID_XTAL_SYNCBUSY  = 0x9BC4EA4CU
} link0ErrId_t;

//
//  Structures
//

/**
 * @brief
 *  Bootrom flow Status Bitfields
 *
 * @details
 *  This is a bitfield structure whose members reflect the following flow status:
 *  STATUS_NA   - Step Not Run.
 *  STATUS_PASS - Step Pass.
 *  STATUS_FAIL - Step Fail.
 */
typedef struct
{
    /**
     * @brief   Flow status for RAM Initialization:
     */
    status_t ramInit:2;

    /**
     * @brief   Flow status for ROM Hardware Patching:
     */
    status_t hwpatch:2;

    /**
     * @brief   Flow status for Error status pin configuration:
     */
    status_t errorStsPin:2;

    /**
     * @brief   Flow status for ZONE0 debug passwsrd:
     */
    status_t zone0pswd:2;

    /**
     * @brief   Flow status for Unique Id:
     */
    status_t uid:2;

    /**
     * @brief   Flow status for FRI wait states:
     */
    status_t friws:2;

    /**
     * @brief   Flow status for Watchdog enable:
     */
    status_t wdEnable:2;

    /**
     * @brief   Flow status for PMM Trim:
     */
    status_t pmmtrim:2;

    /**
     * @brief   Flow status for OSC Trim:
     */
    status_t osctrim:2;

    /**
     * @brief   Flow status for APLL Trim:
     */
    status_t aplltrim:2;

    /**
     * @brief   Flow status for Flash Trim:
     */
    status_t flashtrim:2;

    /**
     * @brief   Flow status for Overall Critical Trim:
     */
    status_t criticaltrim:2;

    /**
     * @brief   Flow status for Device Configuration:
     */
    status_t devconfig:2;

    /**
     * @brief   Flow status for DCx Lock:
     */
    status_t lockDcx:2;

    /**
     * @brief   Flow status for Reset Cause Clear:
     */
    status_t rescClr:2;

    /**
     * @brief   Flow status for Flash Trim Lock:
     */
    status_t flashTrimLock:2;

    /**
     * @brief   Flow status for ESM Lock and Commit Group 0 error events:
     */
    status_t esmLockCommit:2;


    /**
     * @brief   Flow status for UPP revision:
     */
    status_t uppRev:2;


    /**
     * @brief   Flow status for external crystal power up:
     */
    status_t xtalEn:2;

    /**
     * @brief   Flow status for SSU post:
     */
    status_t ssuPost:2;

    /**
     * @brief   Flow status for SSU Initialization:
     */
    status_t ssuInit:2;

    /**
     * @brief   Flow status for PMM Debug Trim:
     */
    status_t pmmDbgtrim:2;

    /**
     * @brief   Flow status for ADC Reference Trim:
     */
    status_t adcReftrim:2;

    /**
     * @brief   Flow status for ADC offset Trim:
     */
    status_t adcOfftrim:2;

    /**
     * @brief   Flow status for ADCINL Trim:
     */
    status_t adcInltrim:2;

    /**
     * @brief   Flow status for DAC Offset Trim:
     */
    status_t dacOfftrim:2;

} bromStatus_t;

/**
 * @brief
 *  SSU Status
 *
 * @details
 *  This is a SSU status structure.
 */
typedef struct
{
    /**
     * @brief   Flow status for CPU1 bank mgmt
     */
    status_t            bankMgmtCpu1:2;

    /**
     * @brief   Flow status for CPU3 bank mgmt
     */
    status_t            bankMgmtCpu3:2;

    /**
     * @brief   Flow status for Bank mode ECC
     */
    status_t            eccBankMode:2;

    /**
     * @brief   Flow status for Get bankmode
     */
    status_t            getBankMode:2;

    /**
     * @brief   Flow status for sector read error
     */
    status_t            readError:2;

    /**
     * @brief   Flow status for SSU mode ECC
     */
    status_t            eccSsuMode:2;

    /**
     * @brief   Flow status for Get SSU mode
     */
    status_t            getSsuMode:2;

    /**
     * @brief   Flow status for CPU1 seccfg
     */
    status_t            secCfgCpu1:2;

    /**
     * @brief   Flow status for CPU3 seccfg
     */
    status_t            secCfgCpu3:2;

    /**
     * @brief   Flow status for CPU1 SSU config
     */
    status_t            ssuCfgCpu1:2;

    /**
     * @brief   Flow status for CPU3 SSU config
     */
    status_t            ssuCfgCpu3:2;

    /**
     * @brief   Flow status for CPU1, CPU2 and CPU3 APR configuration
     */
    status_t            aprCfg:2;

    /**
     * @brief   Winning bank mgmt sector found for CPU1
     */
    uint32_t            winningBankMgmtCpu1;

    /**
     * @brief   Winning bank mgmt sector found for CPU3
     */
    uint32_t            winningBankMgmtCpu3;

    /**
     * @brief   Valid SECCFG sector found for CPU1
     */
    uint32_t            validSecCfgCpu1;

    /**
     * @brief   Valid SECCFG sector found for CPU3
     */
    uint32_t            validSecCfgCpu3;

    /**
     * @brief   Bankmode got from bank mgmt sector
     */
    flashBankMode_t     bankMode;

    /**
     * @brief   Decoded CPU1 swap settings
     */
    flashBankSwap_t     cpu1swap;

    /**
     * @brief   Decoded CPU3 swap settings
     */
    flashBankSwap_t     cpu3swap;

    /**
     * @brief   Decoded CPU1 SECVALID settings
     */
    secValid_t          secvalidCpu1;

    /**
     * @brief   Decoded CPU3 SECVALID settings
     */
    secValid_t          secvalidCpu3;

    /**
     * @brief   SSU mode setting
     */
    ssuMode_t           ssuMode;
} ssuStatus_t;

/**
 * @brief
 *  NMI Status
 *
 * @details
 *  This is a EA status structure.
 */
typedef struct
{
    /**
     * @brief   EA High priority address
     */
    uint32_t            highPriAddr;

    /**
     * @brief   EA Low priority address
     */
    uint32_t            lowPriAddr;

    /**
     * @brief   EA Error Type
     */
    uint32_t            errType;

    /**
     * @brief   Program Counter
     */
    uint32_t            pcAddr;
} eaStatus_t;

/**
 * @brief
 *  NMI Status
 *
 * @details
 *  This is a NMI status structure.
 */
typedef struct
{
    /**
     * @brief   ESM RAW status
     */
    uint32_t            esmRawStatus;

    /**
     * @brief   EA CPU1 PR status
     */
    eaStatus_t          eaCpu1Pr;

    /**
     * @brief   EA CPU1 DR1 status
     */
    eaStatus_t          eaCpu1Dr1;

    /**
     * @brief   EA CPU1 DR2 status
     */
    eaStatus_t          eaCpu1Dr2;

    /**
     * @brief   EA CPU1 DW status
     */
    eaStatus_t          eaCpu1Dw;

    /**
     * @brief   EA CPU1 INT status
     */
    eaStatus_t          eaCpu1Int;
} nmiStatus_t;

/**
 * @brief
 *  Bootrom Status
 *
 * @details
 *  This is a Bootrom status structure placed in M0 RAM.
 */
typedef struct
{
    /**
     * @brief   Link0 start cycle count
     */
    uint64_t            link0StartCycleCount;

    /**
     * @brief   Link0 end cycle count
     */
    uint64_t            link0EndCycleCount;

    /**
     * @brief   Reset count
     */
    uint32_t            resetCnt;

    /**
     * @brief   Reset cause
     */
    uint32_t            resetCause;

    /**
     * @brief   System Clock in Hertz
     */
    uint32_t            sysclk;

    /**
     * @brief   ECC Error Address for DR1:
     */
    uint32_t            eccErrAddrDR1;

    /**
     * @brief   ECC Error Address for DR2:
     */
    uint32_t            eccErrAddrDR2;

    /**
     * @brief   Boot Mode:
     */
    uint32_t            bootMode;

    /**
     * @brief   Bootloader Lock:
     */
    uint32_t            bootLoaderLock;

    /**
     * @brief   Device life cycle state
     */
    devLifeCycleState_t deviceLifeCycleState;

    /**
     * @brief   Link0 Error Id
     */
    link0ErrId_t        link0ErrId;

    /**
     * @brief   Boot rom status
     */
    bromStatus_t        bromStatus;

    /**
     * @brief   SSU status
     */
    ssuStatus_t         ssuStatus;

    /**
     * @brief   NMI status
     */
    nmiStatus_t         nmiStatus;

} brom_status;

/**
 * @brief
 *  SoC ID Public Info
 *
 * @details
 *  This is a structure for SoC ID Public Info.
 */
typedef struct
{
    /**
     * @brief   Device Name: This is the ASCII null terminated string.
     */
    uint8_t             devName[CONFIG_SOCID_DEVNAME_LEN_BYTES];

    /**
     * @brief   Device Type:
     */
    SOCID_DeviceType    devType;

    /**
     * @brief   Version of the HSM Boot ROM:
     *  - Reserved     : Bit31-Bit24
     *  - Major Version: Bit23-Bit16
     *  - Minor Version: Bit15-Bit8
     *  - Patch Version: Bit7-Bit0
     */
    uint32_t            hsmBootROMVersion;
}SOCID_HSMPublicInfo;

/**
 * @brief
 *  SoC ID Secure Info
 *
 * @details
 *  This is a structure for SoC ID Secure Info.
 */
typedef struct
{
    /**
     * @brief   Prime or Non-Prime device:
     * - Prime Device     = 1
     * - Non Prime Device = 0
     * All other values are reserved.
     */
    uint32_t    isPrime;

    /**
     * @brief   Key Count: This is the number of keys which have been provisioned.
     *  - 0 indicates that no keys have been provisioned
     *  - Non Zero indicates that customer keys have been provisioned.
     */
    uint32_t    keyCount;

    /**
     * @brief   Key Revision: The key revision indicates the manufacturer key which will
     * be used i.e. the Secondary or Backup Manufacturer.
     * - Secondary Manufacturer Key = 1
     * - Backup Manufacturer Key    = 2
     * All other values are reserved. This is only applicable for HS-SE devices.
     */
    uint32_t    keyRevision;

    /**
     * @brief   Software Revision for the R5 SBL: The software revision is used to
     * support the software anti-rollback feature.
     */
    uint32_t    swRevSBL;

    /**
     * @brief   Software Revision for the HSM Runtime: The software revision is used to
     * support the software anti-rollback feature.
     */
    uint32_t    swRevHSM;

    /**
     * @brief   Software Revision for the SSU : The software revision is used to
     * support the software anti-rollback feature.
     */
    uint32_t    swRevSSU;

    /**
     * @brief   Software Revision for the FLW : The software revision is used to
     * support the software anti-rollback feature.
     */
    uint32_t    swRevFLW;

    /**
     * @brief   TI Public Key Hash:
     */
    uint8_t     tiKeyHash[CONFIG_SOCID_ROOTKEYHASH_LEN_BYTES];

    /**
     * @brief   Active Customer Public Key Hash:
     */
    uint8_t     custKeyHash[CONFIG_SOCID_ROOTKEYHASH_LEN_BYTES];

    /**
     * @brief   Unique Identifier:
     */
    uint8_t     uniqueID[CONFIG_SOCID_UNIQUEID_LEN_BYTES];
}SOCID_HSMSecureInfo;

/**
 * @brief
 *  SoC ID
 *
 * @details
 *  This is a structure for SoC ID.
 */
typedef struct
{
    /**
     * @brief   Public Information:
     */
    SOCID_HSMPublicInfo    publicInfo;

    /**
     * @brief   Secure Information:
     */
    SOCID_HSMSecureInfo    secureInfo;
}SOCIDHSM_Info;

/**
 * @brief
 *  SOCID C29 Information
 *
 * @details
 *  The structure holds the R5 bootrom information.
 */
typedef struct
{
    /**
     * @brief   R5 Boot ROM version information
     *  - Reserved   : Bit31-Bit24
     *  - Major Version: Bit23-Bit16
     *  - Minor Version: Bit15-Bit8
     *  - Patch Version: Bit7-Bit0
     */
    uint32_t            c29BootROMVersion;
}SOCIDC29_Info;

/**
 * @brief
 *  SOCID hardware Information
 *
 * @details
 *  The structure holds the hardware verion information.
 */
typedef struct
{
    /**
     * @brief   EFuse to differentiate between Automotive parts, industrial parts,
     *          Secure parts, Non-secure parts and RnD parts. Only 11-0 are valid
     */
    uint16_t          partID;

    /**
     * @brief   Efuse for part number (TPR12, TPR22). Only 1-0 bits are valid
     */
    uint8_t           partNumber;

    /**
     * @brief   Efuse for PG version. Only 3-0 bits are valid
     */
    uint8_t           PGVersion;

    /**
     * @brief   Efuse for ROM version. Only 2-0 bits are valid
     */
    uint8_t           ROMVersion;

    /**
     * @brief   Efuse for Metal version. Only 2-0 bits are valid
     */
    uint8_t           metalVersion;

    /**
     * @brief   Padding to make 32bits aligned
     */
    uint16_t          padding;
}SOCIDHW_Info;

/**
 * @brief
 *  SOCID Information
 *
 * @details
 *  The structure holds the information pertinent to the SOC. This
 *  information is sent out via peripheral boot interface when
 *  is suitable.
 */
typedef struct
{
    /**
     * @brief   Hardware Information:
     */
    SOCIDHW_Info        hwInfo;

    /**
     * @brief   C29 Information:
     */
    SOCIDC29_Info        c29Info;

    /**
     * @brief   HSM Information:
     */
    SOCIDHSM_Info       hsmInfo;
}SOCID_Info;

/**
 * @brief
 *  Device Calibration Data
 *
 * @details
 *  The structure holds the device calibration data
 *  I2V, ADC, DAC and TS trims
 */
typedef struct
{
    /**
     * @brief   I2V R1 30C
     */
    uint32_t    devcalI2vR130C;
    /**
     * @brief   I2V R2 30C
     */
    uint32_t    devcalI2vR230C;
    /**
     * @brief   I2V R3 30C
     */
    uint32_t    devcalI2vR330C;
    /**
     * @brief   I2V R1 N40C
     */
    uint32_t    devcalI2vR1N40C;
    /**
     * @brief   I2V R2 N40C
     */
    uint32_t    devcalI2vR2N40C;
    /**
     * @brief   I2V R3 N40C
     */
    uint32_t    devcalI2vR3N40C;
    /**
     * @brief   I2V R1 125C
     */
    uint32_t    devcalI2vR1125C;
    /**
     * @brief   I2V R2 125C
     */
    uint32_t    devcalI2vR2125C;
    /**
     * @brief   I2V R3 125C
     */
    uint32_t    devcalI2vR3125C;
    /**
     * @brief   Reserved 11 MP1
     */
    uint32_t    rsvd11Mp1;
    /**
     * @brief   Dfwtrev MP1
     */
    uint32_t    dfwtRevMp1;
    /**
     * @brief   Boardid MP1
     */
    uint32_t    boardIdMp1;
    /**
     * @brief   Chksumlsb MP1
     */
    uint32_t    chkSumLsbMp1;
    /**
     * @brief   Reserved 14 MP3
     */
    uint32_t    rsvd14Mp3;
    /**
     * @brief   Dfwtrev MP1
     */
    uint32_t    dfwtRevMp3;
    /**
     * @brief   Boardid MP3
     */
    uint32_t    boardIdMp3;
    /**
     * @brief   Chksumlsb MP3
     */
    uint32_t    chkSumLsbMp3;
    /**
     * @brief   Bootrom reserved 0
     */
    uint32_t    bootromRsvd0;
    /**
     * @brief   Bootrom reserved 2
     */
    uint32_t    bootromRsvd2;
    /**
     * @brief   Bootrom reserved 4
     */
    uint32_t    bootromRsvd4;
    /**
     * @brief   Dfwtrev FT
     */
    uint32_t    dfwtRevFt;
    /**
     * @brief   PMM Config Debug 0
     */
    uint32_t    pmmConfigDebug0;
    /**
     * @brief   PMM Config Debug 1
     */
    uint32_t    pmmConfigDebug1;
    /**
     * @brief   ANAREFTRIMA1P65
     */
    uint32_t    anaRefTrimA1P65;
    /**
     * @brief   ANAREFTRIMA2P5
     */
    uint32_t    anaRefTrimA2P5;
    /**
     * @brief   ANAREFTRIMC1P65
     */
    uint32_t    anaRefTrimC1P65;
    /**
     * @brief   ANAREFTRIMC2P5
     */
    uint32_t    anaRefTrimC2P5;
    /**
     * @brief   ADCA OFF TRIM
     */
    uint32_t    adcAoffTrim;
    /**
     * @brief   ADCA OFF TRIM 2
     */
    uint32_t    adcAoffTrim2;
    /**
     * @brief   ADCA OFF TRIM 3
     */
    uint32_t    adcAoffTrim3;
    /**
     * @brief   ADCB OFF TRIM
     */
    uint32_t    adcBoffTrim;
    /**
     * @brief   ADCB OFF TRIM 2
     */
    uint32_t    adcBoffTrim2;
    /**
     * @brief   ADCB OFF TRIM 3
     */
    uint32_t    adcBoffTrim3;
    /**
     * @brief   ADCC OFF TRIM
     */
    uint32_t    adcCoffTrim;
    /**
     * @brief   ADCD OFF TRIM
     */
    uint32_t    adcDoffTrim;
    /**
     * @brief   ADCE OFF TRIM
     */
    uint32_t    adcEoffTrim;
    /**
     * @brief   ADCA INL TRIM 1-6
     */
    uint32_t    adcAInlTrim[6U];
    /**
     * @brief   ADCB INL TRIM 1-6
     */
    uint32_t    adcBInlTrim[6U];
    /**
     * @brief   ADCC INL TRIM 1-3
     */
    uint32_t    adcCInlTrim[3U];
    /**
     * @brief   ADCD INL TRIM 1-3
     */
    uint32_t    adcDInlTrim[3U];
    /**
     * @brief   ADCE INL TRIM 1-3
     */
    uint32_t    adcEInlTrim[3U];
    /**
     * @brief   DACA OFF TRIM
     */
    uint32_t    dacAOffTrim;
    /**
     * @brief   DACC OFF TRIM
     */
    uint32_t    dacCOffTrim;
    /**
     * @brief   Hole 0
     */
    uint32_t    hole0;
    /**
     * @brief   Hole 1
     */
    uint32_t    hole1;
    /**
     * @brief   Hole 2
     */
    uint32_t    hole2;
    /**
     * @brief   DEVCAL TS Gain Extref
     */
    uint32_t    devcalTsGainExtref;
    /**
     * @brief   DEVCAL TS Offset Extref
     */
    uint32_t    devcalTsOffsetExtref;
    /**
     * @brief   DEVCAL TS Gain Intref
     */
    uint32_t    devcalTsGainIntref;
    /**
     * @brief   DEVCAL TS Offset Intref
     */
    uint32_t    devcalTsOffsetIntref;
    /**
     * @brief   DEVCAL Revision
     */
    uint32_t    devcalRev;
}devcal_data;

/**
 * @brief
 *  Bootrom structure and tables
 *
 * @details
 *  Declarations for the bootrom structures and tables
 */
extern const brom_status g_bootromStatus;
extern const SOCID_Info  g_socId;
extern const devcal_data g_devcalData;
extern const double      g_FPU64RFFTtwiddletable[RFFT_TABLE_SIZE];
extern const double      g_FPU64CFFTtwiddletable[CFFT_TABLE_SIZE];
extern const float       g_FPU32RFFTtwiddletable[RFFT_TABLE_SIZE];
extern const float       g_FPU32CFFTtwiddletable[CFFT_TABLE_SIZE];

#ifdef __cplusplus
}
#endif

#endif // __BOOTROM_H__
