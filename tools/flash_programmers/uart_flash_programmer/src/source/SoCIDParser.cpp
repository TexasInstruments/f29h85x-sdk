//###########################################################################
//!
//! \addtogroup uart_flash_programmer_api APIs for Uart Flash Programmer
//! @{
//! 
//! \file   SoCIDParser.cpp
//! 
//! \brief  Interprets SOCID_Info
//!
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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

#include "../include/SoCIDParser.h"

//
// Internal Functions
//
int _printSocId_f29h85x(std::ostream& console, void* data, size_t length);
int _printbromStatus_f29h85x(std::ostream& console, void* data, size_t length);

//*****************************************************************************
//!
//! \brief   Prints the SoC ID Info to the provided console
//!
//! \param console      The output stream to print the SoC ID Info
//! \param data		     Pointer to the data containing SoC ID information
//! \param length		 The length of the data to be printed
//! 
//! \return             0 upon success, -1 if error occurs
//! 
//*****************************************************************************
int printSocID(std::ostream& console, void* data, size_t length)
{
    int retVal;

	if (g_bf29h85x || g_bf29p58x || g_bf29p32x)
	{
        retVal = _printSocId_f29h85x(console, data, length);
	}
	else
	{
		console << "printSocID warning: no implementation is available for the inputted device, using default F29H85x SocID parser..." << std::endl;
        retVal = _printSocId_f29h85x(console, data, length);
	}

    return retVal;
}

//*****************************************************************************
//!
//! \brief   Prints the Brom Status Info to the provided console
//!
//! \param console      The output stream to print the Brom Status Info
//! \param data		     Pointer to the data containing Brom Status information
//! \param length		 The length of the data to be printed
//! 
//! \return             0 upon success, -1 if error occurs
//! 
//*****************************************************************************
int printBromStatus(std::ostream& console, void* data, size_t length)
{
    int retVal;

    if (g_bf29h85x)
    {
        retVal = _printbromStatus_f29h85x(console, data, length);
    }
    else
    {
        console << "printBromStatus warning: no implementation is available for the inputted device, using default F29H85x BROM Status parser..." << std::endl;
        retVal = _printbromStatus_f29h85x(console, data, length);
    }

    return retVal;
}

void convertEndian(void* data, std::size_t byteSize)
{
    if (byteSize < 2)
    {
        return;
    }
    if (byteSize % 2 != 0)
    {
        throw std::invalid_argument("Byte size must be even to convert endianness");
    }

    uint8_t* byteData = static_cast<uint8_t*> (data);

    for (int i = 0; i < byteSize / 2; i++)
    {
        std::swap(byteData[i], byteData[byteSize - i - 1]);
    }
}

int _printSocId_f29h85x(std::ostream& console, void* data, size_t length)
{

#include "../include/device/bootrom_f29h85x.h"

    // SoCID size should be 252Bytes.
    const uint16_t packedSize = 252U;

    if (length < packedSize)
    {
        console << "_printSocId_f29h85x ERROR: the inputted length is less than the size of full SOCID_Info struct." << std::endl;
        console << std::dec << "Inputted: " << length << ", Expected: " << packedSize << std::endl;
        return -1;
    }

    auto convertByteArrToHexStr = [](std::string& dest, void* src, std::size_t byteSize) mutable
        {
            uint8_t* byteArr = (uint8_t*)src;
            std::ostringstream oss;
            for (std::size_t i = 0; i < byteSize; i++)
            {
                // Must cast to regular uint so oss can output hex (uint8_t would be interrupted as ascii-char)
                unsigned int byte = byteArr[i];
                oss << std::hex << std::setw(2) << std::setfill('0') << byte;
            }
            dest.clear();
            dest.reserve(byteSize);
            dest += oss.str();
        };

    uint8_t* curPtr = (uint8_t*)data;

    //
    // Parent strcture
    //
    SOCID_Info info;

    SOCIDHW_Info hwInfo;
    SOCIDC29_Info c29Info;
    SOCIDHSM_Info hsmInfo;
    std::string devTypeStr, keyRevStr, tiHashStr, custHashStr, uidStr;
    
    //
    // Note: use of memcpy assumes host machine is little-endian and paddings are consistent,
    // if not, opt for macros such as BYTES_TO_UINT32 instead.
    //
    if (length == sizeof(SOCID_Info))
    {
        std::memcpy(&info, curPtr, sizeof(SOCID_Info));
        curPtr += sizeof(SOCID_Info);

        hwInfo = info.hwInfo;
        c29Info = info.c29Info;
        hsmInfo = info.hsmInfo;
    }
    else
    {
        // Copy HW Info sequentially (first attribute of SOCID_Info)
        std::memcpy(&hwInfo.partID, curPtr, sizeof(hwInfo.partID));
        curPtr += sizeof(hwInfo.partID);
        std::memcpy(&hwInfo.partNumber, curPtr, sizeof(hwInfo.partNumber));
        curPtr += sizeof(hwInfo.partNumber);
        std::memcpy(&hwInfo.PGVersion, curPtr, sizeof(hwInfo.PGVersion));
        curPtr += sizeof(hwInfo.PGVersion);
        std::memcpy(&hwInfo.ROMVersion, curPtr, sizeof(hwInfo.ROMVersion));
        curPtr += sizeof(hwInfo.ROMVersion);
        std::memcpy(&hwInfo.metalVersion, curPtr, sizeof(hwInfo.metalVersion));
        curPtr += sizeof(hwInfo.metalVersion);
        //std::memcpy(&hwInfo.padding, curPtr, sizeof(hwInfo.padding));
        curPtr += sizeof(hwInfo.padding);

        // Copy C29 Info
        std::memcpy(&c29Info.c29BootROMVersion, curPtr, sizeof(c29Info.c29BootROMVersion));
        curPtr += sizeof(c29Info.c29BootROMVersion);

        // Copy HSM Public Info sequentailly (first attribute of SOCIDHSM_INFO)
        std::memcpy(&hsmInfo.publicInfo.devName, curPtr, sizeof(hsmInfo.publicInfo.devName));
        curPtr += sizeof(hsmInfo.publicInfo.devName);
        std::memcpy(&hsmInfo.publicInfo.devType, curPtr, sizeof(hsmInfo.publicInfo.devType));
        curPtr += sizeof(hsmInfo.publicInfo.devType);
        std::memcpy(&hsmInfo.publicInfo.hsmBootROMVersion, curPtr, sizeof(hsmInfo.publicInfo.hsmBootROMVersion));
        curPtr += sizeof(hsmInfo.publicInfo.hsmBootROMVersion);

        // Copy HSM Secure Info sequentailly (secnd attribute of SOCIDHSM_INFO)
        std::memcpy(&hsmInfo.secureInfo.isPrime, curPtr, sizeof(hsmInfo.secureInfo.isPrime));
        curPtr += sizeof(hsmInfo.secureInfo.isPrime);
        std::memcpy(&hsmInfo.secureInfo.keyCount, curPtr, sizeof(hsmInfo.secureInfo.keyCount));
        curPtr += sizeof(hsmInfo.secureInfo.keyCount);
        std::memcpy(&hsmInfo.secureInfo.keyRevision, curPtr, sizeof(hsmInfo.secureInfo.keyRevision));
        curPtr += sizeof(hsmInfo.secureInfo.keyRevision);
        std::memcpy(&hsmInfo.secureInfo.swRevSBL, curPtr, sizeof(hsmInfo.secureInfo.swRevSBL));
        curPtr += sizeof(hsmInfo.secureInfo.swRevSBL);
        std::memcpy(&hsmInfo.secureInfo.swRevHSM, curPtr, sizeof(hsmInfo.secureInfo.swRevHSM));
        curPtr += sizeof(hsmInfo.secureInfo.swRevHSM);
        std::memcpy(&hsmInfo.secureInfo.swRevSSU, curPtr, sizeof(hsmInfo.secureInfo.swRevSSU));
        curPtr += sizeof(hsmInfo.secureInfo.swRevSSU);
        std::memcpy(&hsmInfo.secureInfo.swRevFLW, curPtr, sizeof(hsmInfo.secureInfo.swRevFLW));
        curPtr += sizeof(hsmInfo.secureInfo.swRevFLW);
        std::memcpy(&hsmInfo.secureInfo.tiKeyHash, curPtr, sizeof(hsmInfo.secureInfo.tiKeyHash));
        curPtr += sizeof(hsmInfo.secureInfo.tiKeyHash);
        std::memcpy(&hsmInfo.secureInfo.custKeyHash, curPtr, sizeof(hsmInfo.secureInfo.custKeyHash));
        curPtr += sizeof(hsmInfo.secureInfo.custKeyHash);
        std::memcpy(&hsmInfo.secureInfo.uniqueID, curPtr, sizeof(hsmInfo.secureInfo.uniqueID));
        curPtr += sizeof(hsmInfo.secureInfo.uniqueID);
    }

    // Convert enums to print strings
    switch (hsmInfo.publicInfo.devType)
    {
        case SOCID_DeviceType_GP:
            devTypeStr = "GP (General Purpose)";
            break;
        case SOCID_DeviceType_TEST:
            devTypeStr = "Test (Engineering Sample)";
            break;
        case SOCID_DeviceType_EMU_FS:
            devTypeStr = "EMU_FS (Field Securable)";
            break;
        case SOCID_DeviceType_HS_FS:
            devTypeStr = "HS_FS (Field Securable)";
            break;
        case SOCID_DeviceType_EMU_SE:
            devTypeStr = "EMU_SE (Security Enforced)";
            break;
        case SOCID_DeviceType_HS_SE:
            devTypeStr = "HS_SE (Security Enforced)";
            break;
        case SOCID_DeviceType_EMU_KP:
            devTypeStr = "EMU_KP (Key Provisioned)";
            break;
        case SOCID_DeviceType_HS_KP:
            devTypeStr = "HS_KP (Key Provisioned)";
            break;
        case SOCID_DeviceType_EMU_FA:
            devTypeStr = "EMU_FA (Failure Analysis)";
            break;
        case SOCID_DeviceType_HS_FA:
            devTypeStr = "HS_FA (Failure Analysis)";
            break;
        default:
            devTypeStr = "Unknown";
            break;
    }

    switch (hsmInfo.secureInfo.keyRevision)
    {
        case 0x1:
            keyRevStr = "SMPK (Secondary Manufacturer Key)";
            break;
        case 0x2:
            keyRevStr = "BMPK (Backup Manufacturer Key)";
            break;
        default:
            keyRevStr = "Unknown (Value = " + std::to_string(hsmInfo.secureInfo.keyRevision) + ")";
            break;
    }

    // Convert all byte arrays into hex strings
    convertByteArrToHexStr(tiHashStr, hsmInfo.secureInfo.tiKeyHash, CONFIG_SOCID_ROOTKEYHASH_LEN_BYTES);
    convertByteArrToHexStr(custHashStr, hsmInfo.secureInfo.custKeyHash, CONFIG_SOCID_ROOTKEYHASH_LEN_BYTES);
    convertByteArrToHexStr(uidStr, hsmInfo.secureInfo.uniqueID, CONFIG_SOCID_UNIQUEID_LEN_BYTES);

    console << "----------------------------\n";
    console << "SoC ID HW Info:\n";
    console << "----------------------------\n";
    console << "Part ID            : " << std::showbase << std::hex << (unsigned int)hwInfo.partID << "\n";
    console << "Part number        : " << std::showbase << std::hex << (unsigned int)hwInfo.partNumber << "\n";
    console << "PG version         : " << std::showbase << std::hex << (unsigned int)hwInfo.PGVersion << "\n";
    console << "ROM version        : " << std::showbase << std::hex << (unsigned int)hwInfo.ROMVersion << "\n";
    console << "Metal version      : " << std::showbase << std::hex << (unsigned int)hwInfo.metalVersion << "\n";
    console << "----------------------------\n";
    console << "SoC ID CPU Info:\n";
    console << "----------------------------\n";
    console << "C29 BootROM version: " << std::showbase << std::hex << (unsigned int)c29Info.c29BootROMVersion << "\n";
    console << "----------------------------\n";
    console << "SoC ID HSM Public Info:\n";
    console << "----------------------------\n";
    console << "Device name        : " << hsmInfo.publicInfo.devName << "\n";
    console << "Device type        : " << devTypeStr << "\n";
    console << "HSM BootROM version: " << std::showbase << std::hex << (unsigned int)hsmInfo.publicInfo.hsmBootROMVersion << "\n";
    console << "----------------------------\n";
    console << "SoC ID HSM Secure Info:\n";
    console << "----------------------------\n";
    console << "Is prime device    : " << std::boolalpha << (bool)hsmInfo.secureInfo.isPrime << "\n";
    console << "# keys provisioned : " << std::dec << (unsigned int)hsmInfo.secureInfo.keyCount << "\n";
    console << "Key revision       : " << keyRevStr << "\t(HS-SE only)\n";
    console << "SW SBL revision    : " << std::showbase << std::hex << (unsigned int)hsmInfo.secureInfo.swRevSBL << "\n";
    console << "SW HSMRt revision  : " << std::showbase << std::hex << (unsigned int)hsmInfo.secureInfo.swRevHSM << "\n";
    console << "SW SSU revision    : " << std::showbase << std::hex << (unsigned int)hsmInfo.secureInfo.swRevSSU << "\n";
    console << "SW FLW revision    : " << std::showbase << std::hex << (unsigned int)hsmInfo.secureInfo.swRevFLW << "\n";
    console << "TI MPK hash        : " << tiHashStr << "\n";
    console << "Active MPK hash    : " << custHashStr << "\n";
    console << "Device UID         : " << uidStr << "\n";
    console << "----------------------------";
    console << std::endl;

    return 0;
}

int _printbromStatus_f29h85x(std::ostream& console, void* data, size_t length)
{

#include "../include/device/bootrom_f29h85x.h"

    // brom_status size should be 192Bytes.
    const uint16_t packedSize = 192U;

    if (length < packedSize)
    {
        console << "_printbromStatus_f29h85x ERROR: the inputted length is less than the size of full SOCID_Info struct." << std::endl;
        console << std::dec << "Inputted: " << length << ", Expected: " << packedSize << std::endl;
        return -1;
    }

    uint8_t* curPtr = (uint8_t*)data;

    //
    // Parent strcture
    //
    brom_status status;

    bromStatus_t bromStatus;
    ssuStatus_t ssuStatus;
    nmiStatus_t nmiStatus;
    std::string status_resetCause, status_bootMode, status_bootLoaderLock ,status_deviceLifeCycleState, status_link0ErrId;
    std::string status_bromFlowStatus, status_ssuFlowStatus;
    std::string ssuStatus_bankMode, ssuStatus_cpu1swap, ssuStatus_cpu3swap, ssuStatus_secvalidCpu1, ssuStatus_secvalidCpu3, ssuStatus_ssuMode;
    std::string nmiStatus_eaCpu1Pr, nmiStatus_eaCpu1Dr1, nmiStatus_eaCpu1Dr2, nmiStatus_eaCpu1Dw, nmiStatus_eaCpu1Int;


    //
    // Note: use of memcpy assumes host machine is little-endian and paddings are consistent,
    // if not, opt for macros such as BYTES_TO_UINT32 instead.
    //
    if (length == sizeof(brom_status))
    {
        std::memcpy(&status, curPtr, sizeof(brom_status));
        curPtr += sizeof(brom_status);

        bromStatus = status.bromStatus;
        ssuStatus = status.ssuStatus;
        nmiStatus = status.nmiStatus;
    }
    else
    {
        // Copy brom_status attributes sequentially
        std::memcpy(&status.link0StartCycleCount, curPtr, sizeof(status.link0StartCycleCount));
        curPtr += sizeof(status.link0StartCycleCount);
        std::memcpy(&status.link0EndCycleCount, curPtr, sizeof(status.link0EndCycleCount));
        curPtr += sizeof(status.link0EndCycleCount);
        std::memcpy(&status.resetCnt, curPtr, sizeof(status.resetCnt));
        curPtr += sizeof(status.resetCnt);
        std::memcpy(&status.resetCause, curPtr, sizeof(status.resetCause));
        curPtr += sizeof(status.resetCause);
        std::memcpy(&status.sysclk, curPtr, sizeof(status.sysclk));
        curPtr += sizeof(status.sysclk);
        std::memcpy(&status.eccErrAddrDR1, curPtr, sizeof(status.eccErrAddrDR1));
        curPtr += sizeof(status.eccErrAddrDR1);
        std::memcpy(&status.eccErrAddrDR2, curPtr, sizeof(status.eccErrAddrDR2));
        curPtr += sizeof(status.eccErrAddrDR2);
        std::memcpy(&status.bootMode, curPtr, sizeof(status.bootMode));
        curPtr += sizeof(status.bootMode);
        std::memcpy(&status.bootLoaderLock, curPtr, sizeof(status.bootLoaderLock));
        curPtr += sizeof(status.bootLoaderLock);
        std::memcpy(&status.deviceLifeCycleState, curPtr, sizeof(status.deviceLifeCycleState));
        curPtr += sizeof(status.deviceLifeCycleState);
        std::memcpy(&status.link0ErrId, curPtr, sizeof(status.link0ErrId));
        curPtr += sizeof(status.link0ErrId);

        // brom Status
        std::memcpy(&bromStatus, curPtr, sizeof(bromStatus));
        curPtr += sizeof(bromStatus);

        // ssu Status
        std::memcpy(&ssuStatus, curPtr, sizeof(ssuStatus));
        curPtr += sizeof(ssuStatus);

        // nmi status
        std::memcpy(&nmiStatus, curPtr, sizeof(nmiStatus));
        curPtr += sizeof(nmiStatus);
    }

    // Convert registers to print strings
    auto check_bit = [](uint32_t reg, uint32_t n)
    {
        return (reg & (1U << n)) ? true : false;
    };
    
    auto convertResetCauseStr = [&](uint32_t rescReg)
    {
        std::ostringstream oss;
        if (check_bit(rescReg, 0)) { oss << "Reset by PORn,"; }
        if (check_bit(rescReg, 1)) { oss << "Reset by XRSn,"; }
        if (check_bit(rescReg, 2)) { oss << "Reset by Watchdog (WDRSn),"; }
        if (check_bit(rescReg, 3)) { oss << "Reset by NMI Watchdog (NMIWDRSn),"; }
        if (check_bit(rescReg, 9)) { oss << "Reset by ECAT_RESET_OUT,"; }
        if (check_bit(rescReg, 11)) { oss << "Reset by SIMRESET_XRSn,"; }
        if (check_bit(rescReg, 12)) { oss << "Reset by ESM RESET,"; }
        if (check_bit(rescReg, 30))
        { 
            oss << " XRSn_pin ON,"; 
        }
        else
        {
            oss << " XRSn_pin OFF,";
        }
        if (check_bit(rescReg, 31))
        {
            oss << " Debugger Connected to CPU"; 
        }
        else
        {
            oss << " Debugger Disconnected";
        }

        oss << std::hex << std::showbase << " (" << (unsigned int)rescReg << ")";
        
        return oss.str();
    };

    status_resetCause = convertResetCauseStr(status.resetCause);

    // Convert enums to print strings
    switch (status.bootMode)
    {
    case 0x0:
        status_bootMode = "Parallel Boot (" + std::to_string(status.bootMode) + ")";
        break;
    case 0x1:
        status_bootMode = "UART Boot (" + std::to_string(status.bootMode) + ")";
        break;
    case 0x2:
        status_bootMode = "CAN Boot (" + std::to_string(status.bootMode) + ")";
        break;
    case 0x3:
        status_bootMode = "Flash Boot (" + std::to_string(status.bootMode) + ")";
        break;
    case 0x4:
        status_bootMode = "Wait Boot (" + std::to_string(status.bootMode) + ")";
        break;
    case 0x5:
        status_bootMode = "RAM Boot (" + std::to_string(status.bootMode) + ")";
        break;
    case 0x6:
        status_bootMode = "SPI Boot (" + std::to_string(status.bootMode) + ")";
        break;
    case 0x7:
        status_bootMode = "I2C Boot (" + std::to_string(status.bootMode) + ")";
        break;
    case 0x8:
        status_bootMode = "CAN-FD Boot (" + std::to_string(status.bootMode) + ")";
        break;
    default:
        status_bootMode = "Unknown (Value = " + std::to_string(status.bootMode) + ")";
        break;
    }

    switch (status.bootLoaderLock)
    {
    case 0xC9:
        status_bootLoaderLock = "Enabled";
        break;
    case 0xFF:
        status_bootLoaderLock = "Disabled";
        break;
    default:
        status_bootLoaderLock = "Unknown (Value = " + std::to_string(status.bootLoaderLock) + ")";
        break;
    }

    switch (status.deviceLifeCycleState)
    {
    case DEV_LIFE_CYCLE_STATE_BAD:
        status_deviceLifeCycleState = "BAD state";
        break;
    case DEV_LIFE_CYCLE_STATE_TEST:
        status_deviceLifeCycleState = "TEST state";
        break;
    case DEV_LIFE_CYCLE_STATE_GP:
        status_deviceLifeCycleState = "GP state";
        break;
    case DEV_LIFE_CYCLE_STATE_EMU_SE:
        status_deviceLifeCycleState = "EMU_SE";
        break;
    case DEV_LIFE_CYCLE_STATE_EMU_KP:
        status_deviceLifeCycleState = "EMU_KP";
        break;
    case DEV_LIFE_CYCLE_STATE_EMU_FS:
        status_deviceLifeCycleState = "EMU_FS";
        break;
    case DEV_LIFE_CYCLE_STATE_EMU_FA:
        status_deviceLifeCycleState = "EMU_FA";
        break;
    case DEV_LIFE_CYCLE_STATE_HS_SE:
        status_deviceLifeCycleState = "HS_SE";
        break;
    case DEV_LIFE_CYCLE_STATE_HS_KP:
        status_deviceLifeCycleState = "HS_KP";
        break;
    case DEV_LIFE_CYCLE_STATE_HS_FS:
        status_deviceLifeCycleState = "HS_FS";
        break;
    case DEV_LIFE_CYCLE_STATE_HS_FA:
        status_deviceLifeCycleState = "HS_FA";
        break;
    default:
        status_deviceLifeCycleState = "Unknown (Value = " + std::to_string(status.deviceLifeCycleState) + ")";
        break;
    }

    switch (status.link0ErrId)
    {
    case LINK0_ERR_ID_NONE:
        status_link0ErrId = "No Error";
        break;
    case LINK0_ERR_ID_APR_CONFIG:
        status_link0ErrId = "APR Configuration Error";
        break;
    case LINK0_ERR_ID_SSU_POST:
        status_link0ErrId = "SSU POST Error";
        break;
    case LINK0_ERR_ID_SSU_CONFIG:
        status_link0ErrId = "SSU Configuration Error";
        break;
    case LINK0_ERR_ID_NMI:
        status_link0ErrId = "NMI Error";
        break;
    case LINK0_ERR_ID_SECCFG_APR:
        status_link0ErrId = "SEC CFG APR Error";
        break;
    case LINK0_ERR_ID_WDG_SYNCBUSY:
        status_link0ErrId = "WDG Sync Busy Error";
        break;
    case LINK0_ERR_ID_XTAL_SYNCBUSY:
        status_link0ErrId = "XTAL Sync Busy Error";
        break;
    default:
        status_link0ErrId = "Unknown (Value = " + std::to_string(status.link0ErrId) + ")";
        break;
    }

    auto convertBromFlowStatusStr = [](bromStatus_t& bromFlow)
    {
        std::string retStr;
        std::ostringstream oss;
        if (bromFlow.ramInit == (status_t)STATUS_FAIL) { oss << "RAM Init FAILED\n"; }
        if (bromFlow.hwpatch == (status_t)STATUS_FAIL) { oss << "HW Patching FAILED\n"; }
        if (bromFlow.errorStsPin == (status_t)STATUS_FAIL) { oss << "ERR Status Pin FAILED\n"; }
        if (bromFlow.zone0pswd == (status_t)STATUS_FAIL) { oss << "ZONE0 Debug Password FAILED\n"; }
        if (bromFlow.uid == (status_t)STATUS_FAIL) { oss << "UID FAILED\n"; }
        if (bromFlow.friws == (status_t)STATUS_FAIL) { oss << "FRI Wait States FAILED\n"; }
        if (bromFlow.wdEnable == (status_t)STATUS_FAIL) { oss << "Watchdog Enable FAILED\n"; }
        if (bromFlow.pmmtrim == (status_t)STATUS_FAIL) { oss << "PMM Trim FAILED\n"; }
        if (bromFlow.osctrim == (status_t)STATUS_FAIL) { oss << "OSC Trim FAILED\n"; }
        if (bromFlow.aplltrim == (status_t)STATUS_FAIL) { oss << "APLL Trim FAILED\n"; }
        if (bromFlow.flashtrim == (status_t)STATUS_FAIL) { oss << "Flash Trim FAILED\n"; }
        if (bromFlow.criticaltrim == (status_t)STATUS_FAIL) { oss << "Critical Trim FAILED\n"; }
        if (bromFlow.devconfig == (status_t)STATUS_FAIL) { oss << "Device Config FAILED\n"; }
        if (bromFlow.lockDcx == (status_t)STATUS_FAIL) { oss << "DCx Lock FAILED\n"; }
        if (bromFlow.rescClr == (status_t)STATUS_FAIL) { oss << "Reset Cause Clear FAILED\n"; }
        if (bromFlow.flashTrimLock == (status_t)STATUS_FAIL) { oss << "Flash Trim Lock FAILED\n"; }
        if (bromFlow.esmLockCommit == (status_t)STATUS_FAIL) { oss << "ESM Lock & Commit 0 FAILED\n"; }
        if (bromFlow.uppRev == (status_t)STATUS_FAIL) { oss << "UPP Revision FAILED\n"; }
        if (bromFlow.xtalEn == (status_t)STATUS_FAIL) { oss << "XTAL Enable FAILED\n"; }
        if (bromFlow.ssuPost == (status_t)STATUS_FAIL) { oss << "SSU Post FAILED\n"; }
        if (bromFlow.ssuInit == (status_t)STATUS_FAIL) { oss << "SSU Init FAILED\n"; }
        if (bromFlow.pmmDbgtrim == (status_t)STATUS_FAIL) { oss << "PMM Debug Trim FAILED\n"; }
        if (bromFlow.adcReftrim == (status_t)STATUS_FAIL) { oss << "ADC Ref Trim FAILED\n"; }
        if (bromFlow.adcOfftrim == (status_t)STATUS_FAIL) { oss << "ADC Offset Trim FAILED\n"; }
        if (bromFlow.adcInltrim == (status_t)STATUS_FAIL) { oss << "ADCINL Trim FAILED\n"; }
        if (bromFlow.dacOfftrim == (status_t)STATUS_FAIL) { oss << "DAC Offset Trim FAILED\n"; }
        
        if (oss.str().empty())
        {
            oss << "No Failed Steps\n";
        }
        retStr = "(Omitting Passed or Ignored Boot Flow Execution Status)\n" + oss.str();
        return retStr;
    };

    status_bromFlowStatus = convertBromFlowStatusStr(bromStatus);

    auto convertSSUFlowStatusStr = [](ssuStatus_t& ssuFlow)
    {
        std::string retStr;
        std::ostringstream oss;
        if (ssuFlow.bankMgmtCpu1 == (status_t)STATUS_FAIL) { oss << "CPU1 Bank Mgmt FAILED\n"; }
        if (ssuFlow.bankMgmtCpu3 == (status_t)STATUS_FAIL) { oss << "CPU3 Bank Mgmt FAILED\n"; }
        if (ssuFlow.eccBankMode == (status_t)STATUS_FAIL) { oss << "ECC Bank Mode FAILED\n"; }
        if (ssuFlow.getBankMode == (status_t)STATUS_FAIL) { oss << "Get Bank Mode FAILED\n"; }
        if (ssuFlow.readError == (status_t)STATUS_FAIL) { oss << "Sector Read Error FAILED\n"; }
        if (ssuFlow.eccSsuMode == (status_t)STATUS_FAIL) { oss << "ECC SSU Mode FAILED\n"; }
        if (ssuFlow.getSsuMode == (status_t)STATUS_FAIL) { oss << "Get SSU Mode FAILED\n"; }
        if (ssuFlow.secCfgCpu1 == (status_t)STATUS_FAIL) { oss << "CPU1 Sec Cfg FAILED\n"; }
        if (ssuFlow.secCfgCpu3 == (status_t)STATUS_FAIL) { oss << "CPU3 Sec Cfg FAILED\n"; }
        if (ssuFlow.ssuCfgCpu1 == (status_t)STATUS_FAIL) { oss << "CPU1 SSU Cfg FAILED\n"; }
        if (ssuFlow.ssuCfgCpu3 == (status_t)STATUS_FAIL) { oss << "CPU3 SSU Cfg FAILED\n"; }
        if (ssuFlow.aprCfg == (status_t)STATUS_FAIL) { oss << "CPU1/2/3 APR Config FAILED\n"; }
        
        if (oss.str().empty())
        {
            oss << "No Failed Steps\n";
        }
        retStr = "(Omitting Passed or Ignored Boot Flow Execution Status)\n" + oss.str();
        return retStr;
    };

    status_ssuFlowStatus = convertSSUFlowStatusStr(ssuStatus);

    switch (ssuStatus.bankMode)
    {
        case FLASH_BANK_MODE_0:
            ssuStatus_bankMode = "Bank Mode 0";
            break;
        case FLASH_BANK_MODE_1:
            ssuStatus_bankMode = "Bank Mode 1";
            break;
        case FLASH_BANK_MODE_2:
            ssuStatus_bankMode = "Bank Mode 2";
            break;
        case FLASH_BANK_MODE_3:
            ssuStatus_bankMode = "Bank Mode 3";
            break;
        case FLASH_BANK_MODE_INVALID:
        default:
            ssuStatus_bankMode = "Invalid Bank Mode";
            break;
    }

    auto convertFlashBankSwapStr = [](uint32_t swapVal)
    {
        std::string retStr;
        switch (swapVal)
        {
            case FLASH_BANK_SWAP_DEFAULT:
                retStr = "Default Swap";
                break;
            case FLASH_BANK_SWAP_ALTERNATE:
                retStr = "Alternate Swap";
                break;
            case FLASH_BANK_SWAP_INVALID:
            default:
                retStr = "Invalid Swap";
                break;
        }
        return retStr;
    };

    ssuStatus_cpu1swap = convertFlashBankSwapStr(ssuStatus.cpu1swap);
    ssuStatus_cpu3swap = convertFlashBankSwapStr(ssuStatus.cpu3swap);

    auto convertSecValidStr = [](uint32_t secvalidVal)
        {
            std::string retStr;
            switch (secvalidVal)
            {
            case SECVALID_BASE:
                retStr = "Default Active";
                break;
            case SECVALID_ALTERNATE:
                retStr = "Alternate Active";
                break;
            case SECVALID_INVALID:
            default:
                retStr = "Invalid Sec Cfg";
                break;
            }
            return retStr;
        };

    ssuStatus_secvalidCpu1 = convertSecValidStr(ssuStatus.secvalidCpu1);
    ssuStatus_secvalidCpu3 = convertSecValidStr(ssuStatus.secvalidCpu3);

    switch (ssuStatus.ssuMode)
    {
    case SSUMODE_1:
        ssuStatus_ssuMode = "SSU Mode 1";
        break;
    case SSUMODE_2:
        ssuStatus_ssuMode = "SSU Mode 2";
        break;
    case SSUMODE_3:
        ssuStatus_ssuMode = "SSU Mode 3";
        break;
    case SSUMODE_INVALID:
    default:
        ssuStatus_ssuMode = "Invalid SSU Mode";
        break;
    }

    auto convertEAStatusStr = [](eaStatus_t& eaStatus)
        {
            std::ostringstream oss;
            
            oss << std::showbase << std::hex << "(Err Type)" << eaStatus.errType;
            oss << std::showbase << std::hex << ", (High-Pri Addr)" << eaStatus.highPriAddr;
            oss << std::showbase << std::hex << ", (Low-Pri Addr)" << eaStatus.lowPriAddr;
            oss << std::showbase << std::hex << ", (PC Addr)" << eaStatus.pcAddr;

            return oss.str();
        };

    nmiStatus_eaCpu1Pr = convertEAStatusStr(nmiStatus.eaCpu1Pr);
    nmiStatus_eaCpu1Dr1 = convertEAStatusStr(nmiStatus.eaCpu1Dr1); 
    nmiStatus_eaCpu1Dr2 = convertEAStatusStr(nmiStatus.eaCpu1Dr2);
    nmiStatus_eaCpu1Dw = convertEAStatusStr(nmiStatus.eaCpu1Dw);
    nmiStatus_eaCpu1Int = convertEAStatusStr(nmiStatus.eaCpu1Int);

    console << "----------------------------\n";
    console << "Boot ROM Checks:\n";
    console << "----------------------------\n";
    console << status_bromFlowStatus;
    console << "----------------------------\n";
    console << "SSU Checks:\n";
    console << "----------------------------\n";
    console << status_ssuFlowStatus;
    console << "----------------------------\n";
    console << "Boot ROM Status:\n";
    console << "----------------------------\n";
    //console << "Link 0 Start Cycle : " << std::dec << (uint64_t)status.link0StartCycleCount << "\n";
    //console << "Link 0 End Cycle   : " << std::dec << (uint64_t)status.link0EndCycleCount << "\n";
    console << "Link 0 Elasped Cycle: " << std::dec << (uint64_t)status.link0EndCycleCount - status.link0StartCycleCount << "\n";
    console << "Reset Count         : " << std::dec << (unsigned int)status.resetCnt << "\n";
    console << "Reset Cause (RESC)  : " << status_resetCause << "\n";
    //console << "System Clock - Hz   : " << std::dec << (unsigned int)status.sysclk << "\n";
    console << "System Clock        : " << std::dec << (unsigned int)status.sysclk / 1000000U << " MHz" << "\n";
    console << "ECC DR1 Error Addr  : " << std::showbase << std::hex << (unsigned int)status.eccErrAddrDR1 << "\n";
    console << "ECC DR2 Error Addr  : " << std::showbase << std::hex << (unsigned int)status.eccErrAddrDR2 << "\n";
    console << "Boot Mode           : " << status_bootMode << "\n";
    console << "Bootloader Lock     : " << status_bootLoaderLock << "\n";
    console << "Life Cycle State    : " << status_deviceLifeCycleState << "\n";
    console << "Link 0 Error ID     : " << status_link0ErrId << "\n";
    console << "----------------------------\n";
    console << "SSU Status:\n";
    console << "----------------------------\n";
    console << "CPU1 Active Bank Mgmt Addr: " << std::showbase << std::hex << (unsigned int)ssuStatus.winningBankMgmtCpu1 << "\n";
    console << "CPU3 Active Bank Mgmt Addr: " << std::showbase << std::hex << (unsigned int)ssuStatus.winningBankMgmtCpu3 << "\n";
    console << "CPU1 Active Sec Cfg Addr  : " << std::showbase << std::hex << (unsigned int)ssuStatus.validSecCfgCpu1 << "\n";
    console << "CPU3 Active Sec Cfg Addr  : " << std::showbase << std::hex << (unsigned int)ssuStatus.validSecCfgCpu3 << "\n";
    console << "Bank Mode      : " << ssuStatus_bankMode << "\n";
    console << "CPU1 Bank Swap : " << ssuStatus_cpu1swap << "\n";
    console << "CPU3 Bank Swap : " << ssuStatus_cpu3swap << "\n";
    console << "CPU1 Sec Cfg   : " << ssuStatus_secvalidCpu1 << "\n";
    console << "CPU3 Sec Cfg   : " << ssuStatus_secvalidCpu3 << "\n";
    console << "SSU Mode       : " << ssuStatus_ssuMode << "\n";
    console << "----------------------------\n";
    console << "NMI Status:\n";
    console << "----------------------------\n";
    console << "ESM Raw Status : " << std::showbase << std::hex << (unsigned int)nmiStatus.esmRawStatus << "\n";
    console << "EA CPU1 PR  : " << nmiStatus_eaCpu1Pr << "\n";
    console << "EA CPU1 DR1 : " << nmiStatus_eaCpu1Dr1 << "\n";
    console << "EA CPU1 DR2 : " << nmiStatus_eaCpu1Dr2 << "\n";
    console << "EA CPU1 DW  : " << nmiStatus_eaCpu1Dw << "\n";
    console << "EA CPU1 Int : " << nmiStatus_eaCpu1Int << "\n";
    console << "----------------------------";
    console << std::endl;

    return 0;
}

/** @} */