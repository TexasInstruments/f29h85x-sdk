//###########################################################################
//
// FILE:   test_write_word.c
//
// TITLE:  Write Word Test
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
// PMBusController_initWriteWordTest
//
//*****************************************************************************
void PMBusController_initWriteWordTest(PMBus_TestHandle handle)
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
    // Enable the test
    //
#if ENABLE_TEST_3 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_3 == 1
}

//*****************************************************************************
//
// PMBusController_runWriteWordTest
//
//*****************************************************************************
void PMBusController_runWriteWordTest(PMBus_TestHandle handle)
{
    //
    // Add command (index 0)  and
    // word data to buffer (index 1 and 2)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;
    pmbusControllerBuffer[1] = TEST3_DATA_BYTE_1;
    pmbusControllerBuffer[2] = TEST3_DATA_BYTE_2;

    //
    // Do a write word
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // 2 bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 2U,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 3U);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
    }

    //
    // Once the bus is free, if the target NACK'd its a failure
    //
    (targetAckReceived == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 1U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//