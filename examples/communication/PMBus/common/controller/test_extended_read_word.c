//###########################################################################
//
// FILE:   test_extended_read_word.c
//
// TITLE:  Read Word (Extended) Test
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

//
// Includes
//
#include "pmbus_controller_test.h"

//*****************************************************************************
//
// PMBusController_initExtendedReadWordTest
//
//*****************************************************************************
void PMBusController_initExtendedReadWordTest(PMBus_TestHandle handle)
{
    //
    // Reset flags
    //
    PMBusController_resetGlobalFlags();

    //
    // Reset test object
    //
    PMBusController_resetTestObject(handle);

    //
    // Set count to 2
    //
    handle->count = 2;

    //
    // Enable the test
    //
#if ENABLE_TEST_21 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_21 == 1
}

//*****************************************************************************
//
// PMBusController_runExtendedReadWordTest
//
//*****************************************************************************
void PMBusController_runExtendedReadWordTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = 0U;

    //
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Do a extended read byte
    // Configure the controller to send a read-word command (by asserting the
    // command and extended command bits) and then to issue a repeated start
    // followed by a read (i.e. enable read) and get two data bytes and a
    // PEC from the target. Also enable PEC processing on the controller side to
    // verify the PEC
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, TEST21_2BYTES,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_READ |
                        PMBUS_CONTROLLER_ENABLE_CMD | PMBUS_CONTROLLER_ENABLE_EXT_CMD));

    //
    // Load the extended command and command bytes into the transmit register,
    // in this case the PMBUS_CMD_VOUT_COMMAND command
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    pmbusControllerBuffer[1] = PMBUS_CMD_VOUT_COMMAND;
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], handle->count);

    //
    // Wait for the EOM, the target transmits all its data, the
    // controller NACKs it, and then issues an EOM on the bus
    // -- this flag is set in the ISR
    // NOTE: Although the controller issues a NACK to the target to indicate the
    // end of transmission, the NACK bit (status) is not asserted at the controller
    // end, only at the target end.
    //
    while(endOfMessage == false)
    {
    }

    nBytes = PMBus_getControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0],
                                 pmbusStatus);

    //
    // Check the received byte
    //
    (nBytes == handle->count) ? handle->pass++ : handle->fail++;

    (pmbusControllerBuffer[0] == (PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V1)) ? 
                             handle->pass++ : handle->fail++;

    (pmbusControllerBuffer[1] == (PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V2)) ?
                             handle->pass++ : handle->fail++;

    (receivedPecValid == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 4U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
