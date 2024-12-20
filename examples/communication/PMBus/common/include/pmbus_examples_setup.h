//###########################################################################
//
// FILE:   pmbus_examples_setup.h
//
// TITLE:  PMBus Examples Common Code
//
//###########################################################################
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

//###########################################################################
#ifndef PMBUS_EXAMPLES_SETUP_H
#define PMBUS_EXAMPLES_SETUP_H

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

//
// Includes
//
#include <stdint.h>
#include "device.h"
#include "pmbus_examples_defines.h"

//*****************************************************************************
//
//!
//! \defgroup PMBUS_EXAMPLES_SETUP PMBus Examples Setup Code
//
//!
//! \ingroup PMBUS_EXAMPLES_SETUP
// @{
//
//*****************************************************************************

//
// Defines
//
#define NTESTS                   21U
#define NENABLEDTESTS            19U
#define TARGET_ADDRESS            0x6AU
#define TARGET_2_ADDRESS          0x39U
#define TARGET_ADDRESSMASK        0x7FU
#define ALERT_RESPONSE_ADDRESS   0x0CU
#define PMBUS_ENABLE_WRITE       0U
#define DATA_BYTE_COUNT          255U

//
// Send Byte Test
//
#define TEST1_DATA_BYTE          0x55U

//
// Write Byte Test
//
#define TEST2_DATA_BYTE          0xAAU

//
// Write Word Test
//
#define TEST3_DATA_BYTE_1        0xAAU
#define TEST3_DATA_BYTE_2        0x7EU

//
// Receive Byte Test
//
#define TEST5_DATA_BYTE          0x55U

//
// Process Call Test
//
#define TEST14_DATA_BYTE_1       0xAAU
#define TEST14_DATA_BYTE_2       0x7EU
#define TEST14_XOR_MASK          0x55U

//
// Group Command Test
//
#define TEST17_2BYTES            2U

//
// Extended Write Word Test
//
#define TEST19_2BYTES            2U
#define TEST19_4BYTES            4U

//
// Extended Read Byte Test
//
#define TEST20_2BYTES            2U

//
// Extended Read Word Test
//
#define TEST21_2BYTES            2U

//
// Generic Test Command XOR Masks
//
#define CMD_XOR_MASK_V1          0xFFU
#define CMD_XOR_MASK_V2          0x55U
#define CMD_XOR_MASK_V3          1U
#define CMD_XOR_MASK_V4          2U

//*****************************************************************************
//
//! Setup GPIO pins for PMBUS mode of operation
//!
//! This function configures the GPIO muxing for PMBus.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusExample_setupGPIO(void);

//*****************************************************************************
//
//! Setup System Control
//!
//! This function disables the watchdog, enables device PLL, and PMBus
//! peripheral clock.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusExample_setupSysCtrl(void);

//*****************************************************************************
//
//! Setup Interrupts
//!
//! \param pmbusISR is the handle to the PMBus ISR function
//!
//! This function enables device and PMBus interrupts. Additionally, the PMBus
//! ISR handler is registered.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusExample_setupInterrupts(void(*pmbusISR)(void));

//*****************************************************************************
//
//! Setup Flash
//!
//! This function initializes the flash module.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusExample_setupFlash(void);

//*****************************************************************************
//
//! Done Function
//!
//! This function is an infinite loop which is run at the end of testing.
//!
//! \return None.
//
//*****************************************************************************
extern void
done(void);

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  PMBUS_EXAMPLES_SETUP_H definition

// End of File
