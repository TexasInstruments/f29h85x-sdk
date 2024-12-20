//###########################################################################
//
// FILE:   pmbus_target_test.h
//
// TITLE:  Prototypes for the different target command handlers
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
#ifndef PMBUS_TARGET_TEST_H
#define PMBUS_TARGET_TEST_H

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

//*****************************************************************************
//
//!
//! \addtogroup PMBUS_TARGET_TESTS PMBus Target Mode Tests
//! @{
//!
//! 
// 
//
//*****************************************************************************

//
// Includes
//
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "pmbus_examples_setup.h"
#include "pmbus_stack_config.h"
#include "pmbus_stack_handler.h"
#ifdef ENABLE_MCPI  // MCPI
#include "logger.h" // MCPI
#endif              // MCPI

//
// Globals
//
extern PMBus_StackObject pmbusStackTarget;
extern PMBus_StackHandle pmbusStackTargetHandle;
extern uint16_t pmbusTargetBuffer[300U];

extern volatile uint16_t testsCompleted;
extern volatile uint16_t pass, fail;

//
// Function Prototypes
//

//*****************************************************************************
//
//! Send Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_sendByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Write Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 5
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_writeByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Write Word Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_writeWordTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Write (255 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 260
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockWriteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Receive Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_receiveByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Read Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_readByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Read Word Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_readWordTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Read (255 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockReadTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Read (3 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockRead3BytesTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Write/Read/Process Call (255 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 259
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockWriteReadProcessCallTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Quick Command Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_quickCommandTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Write (2 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note An attempted block write with 1 byte is a write byte, 2 bytes
//! a write word - the controller does not put the byte count on the line.
//!
//! \note Make sure to run the write word test before this, as the original
//! write word Handler overwrites the handler to point to this function.
//!
//! \note Expected Pass Value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockWrite2BytesTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Write (3 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note An attempted block write with 1 byte is a write byte, 2 bytes
//! a write word - the controller does not put the byte count on the line.
//!
//! \note Make sure to run the block write test before this, as the original
//! block write handler overwrites the handler to point to this function.
//!
//! \note Expected Pass Value: 8
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockWrite3BytesTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Process Call Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 5
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_processCallTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Alert Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_alertTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Alert (from 2nd target) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note This test requires a 2nd PMBus target on the network asserting
//!       the alert line.
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_noAlertTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Group Command (target 1st addressed) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_groupCommandTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Extended Write Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_extendedWriteByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Extended Write Word Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 7
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_extendedWriteWordTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Extended Read Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_extendedReadByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! ExtendedRead Word Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_extendedReadWordTestHandler(PMBus_StackHandle handle);

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

#endif  // PMBUS_TARGET_TEST_H
