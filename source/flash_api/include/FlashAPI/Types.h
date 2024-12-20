//###########################################################################
//
// FILE:   Types.h
//
// TITLE:  Flash API v21.00.00
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

#ifndef F65_TYPES_H_
#define F65_TYPES_H_

/*****************************************************************************/
/* GLOBAL DEFINITIONS                                                        */
/*****************************************************************************/

#define ATTRIBUTE_PACKED    __attribute__((packed))


#define HIGH_BYTE_FIRST     0
#define LOW_BYTE_FIRST      1

#ifndef TRUE
   #define TRUE              1
#endif

#ifndef FALSE
   #define FALSE             0
#endif

/*****************************************************************************/
/* ENDIANESS                                                                 */
/*****************************************************************************/
#if defined(_LITTLE_ENDIAN)
   #define CPU_BYTE_ORDER    LOW_BYTE_FIRST
#else
   #define CPU_BYTE_ORDER    HIGH_BYTE_FIRST
#endif

typedef unsigned char          boolean;
typedef struct
{
   uint32_t au32StatusWord[4];
}  ATTRIBUTE_PACKED Fapi_FlashStatusWordType;

/*!
    \brief This contains all the possible modes used in the Fapi_IssueAsyncProgrammingCommand().
*/
typedef enum
{
   Fapi_AutoEccGeneration, /* This is the default mode for the command and will auto generate the ecc for the provided data buffer */
   Fapi_DataOnly,       /* Command will only process the data buffer */
   Fapi_EccOnly,        /* Command will only process the ecc buffer */
   Fapi_DataAndEcc         /* Command will process data and ecc buffers */
}  ATTRIBUTE_PACKED Fapi_FlashProgrammingCommandsType;

/*!
    \brief This is used to indicate which Flash bank is being used.
*/
/*!
    \brief This is used to indicate which Flash bank is being used.
*/
typedef enum
{
    C29Bank             /* C29 CPU 1 */
}  ATTRIBUTE_PACKED Fapi_FlashBankType;

/*!
    \brief This contains all the possible Flash State Machine commands.
*/
typedef enum
{
   Fapi_ProgramData    = 0x0002,
   Fapi_EraseSector    = 0x0006,
   Fapi_EraseBank      = 0x0008,
   Fapi_ClearStatus    = 0x0010
}  ATTRIBUTE_PACKED Fapi_FlashStateCommandsType;

typedef  uint32_t Fapi_FlashStatusType;

/*!
    \brief This is the master type containing all possible returned status codes.
*/
typedef enum
{
   Fapi_Status_Success=0,           /* Function completed successfully */
   Fapi_Status_FsmBusy,             /* FSM is Busy */
   Fapi_Status_FsmReady,            /* FSM is Ready */
   Fapi_Status_AsyncBusy,           /* Async function operation is Busy */
   Fapi_Status_AsyncComplete,       /* Async function operation is Complete */
   Fapi_Error_Fail=500,             /* Generic Function Fail code */
   Fapi_Error_StateMachineTimeout,  /* State machine polling never returned ready and timed out */
   Fapi_Error_OtpChecksumMismatch,  /* Returned if OTP checksum does not match expected value */
   Fapi_Error_InvalidDelayValue,    /* Returned if the Calculated RWAIT value exceeds 15  - Legacy Error */
   Fapi_Error_InvalidHclkValue,     /* Returned if FClk is above max FClk value - FClk is a calculated from HClk and RWAIT/EWAIT */
   Fapi_Error_InvalidCpu,           /* Returned if the specified Cpu does not exist */
   Fapi_Error_InvalidBank,          /* Returned if the specified bank does not exist */
   Fapi_Error_InvalidAddress,       /* Returned if the specified Address does not exist in Flash or OTP */
   Fapi_Error_InvalidReadMode,      /* Returned if the specified read mode does not exist */
   Fapi_Error_AsyncIncorrectDataBufferLength,
   Fapi_Error_AsyncIncorrectEccBufferLength,
   Fapi_Error_AsyncDataEccBufferLengthMismatch,
   Fapi_Error_FeatureNotAvailable,  /* FMC feature is not available on this device */
   Fapi_Error_FlashRegsNotWritable, /* Returned if Flash registers are not writable due to security */
   Fapi_Error_InvalidCPUID          /* Returned if OTP has an invalid CPUID */ 
}  ATTRIBUTE_PACKED Fapi_StatusType;


/*!
    \brief
*/
typedef enum
{
   Alpha_Internal,          /* For internal TI use only.  Not intended to be used by customers */
   Alpha,                   /* Early Engineering release.  May not be functionally complete */
   Beta_Internal,           /* For internal TI use only.  Not intended to be used by customers */
   Beta,                    /* Functionally complete, to be used for testing and validation */
   Production               /* Fully validated, functionally complete, ready for production use */
}  ATTRIBUTE_PACKED Fapi_ApiProductionStatusType;

typedef struct
{
   uint8_t  u8ApiMajorVersion;
   uint8_t  u8ApiMinorVersion;
   uint8_t  u8ApiRevision;
   Fapi_ApiProductionStatusType oApiProductionStatus;
   uint32_t u32ApiBuildNumber;
   uint8_t  u8ApiTechnologyType;
   uint8_t  u8ApiTechnologyRevision;
   uint8_t  u8ApiEndianness;
   uint32_t u32ApiCompilerVersion;
} Fapi_LibraryInfoType;


typedef enum
{
   Bank0,
   Bank1,
   Bank2,
   Bank3,
   Bank4

} ATTRIBUTE_PACKED Fapi_BankID;

typedef enum
{
    FAPI_FLASHNW_FC1_BASE = (uint32_t)0x30100000U,
    FAPI_FLASHNW_FC2_BASE = (uint32_t)0x30110000U

} ATTRIBUTE_PACKED Fapi_FLCID;

/*!
    \brief
*/
typedef enum
{
   Mode0 = 0x3,    /* CPU1 4MB, No FOTA, CPU1SWAP X CPU3SWAP X */
   Mode1 = 0x6,    /* CPU1 4MB, FOTA Enabled, CPU1SWAP 0/1 CPU3SWAP X*/
   Mode2 = 0x9,    /* CPU1 2MB CPU3 2MB, No FOTA, CPU1SWAP X CPU3SWAP X*/
   Mode3 = 0xC     /* CPU1 2MB CPU3 2MB, FOTA Enabled, (CPU1SWAP 1 CPU3SWAP 1) or (CPU1SWAP 0 CPU3SWAP 0)*/
} ATTRIBUTE_PACKED Fapi_BankMode;

/*!
    \brief
*/
typedef enum
{
   CPU1Swap0 = 0xC9,        //default mapping of CPU1 Banks
   CPU1Swap1 = 0x36,        //Alternate Mapping of CPU1 Banks
} ATTRIBUTE_PACKED Fapi_CPU1BankSwap;

/*!
    \brief
*/
typedef enum
{
   CPU3Swap0 = 0xC9,        //default mapping of CPU3 Banks
   CPU3Swap1 = 0x36,        //Alternate Mapping of CPU3 Banks
} ATTRIBUTE_PACKED Fapi_CPU3BankSwap;


typedef enum
{
   FOTA_Image,    /* FOTA is enabled */
   Active_Bank    /* FOTA is disabled */
} ATTRIBUTE_PACKED Fapi_FOTAStatus;

/*!
    \brief
*/
typedef enum
{
   BankSize256KB,
   BankSize512KB,
   BankSize1MB
} ATTRIBUTE_PACKED Fapi_ECCAddressBits;


/*!
    \brief
    \\
*/
typedef enum
{
   Base = 0xC9U,    /* BASE addresses are valid */
   Alt = 0x36       /* ALT addresses are valid */
} ATTRIBUTE_PACKED Fapi_SECVALID;

#endif /*F65_TYPES_H_*/
