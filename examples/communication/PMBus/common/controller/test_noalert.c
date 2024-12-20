//###########################################################################
//
// FILE:   test_noalert.c
//
// TITLE:  Alert Response to a different target Test
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
// PMBusController_initNoAlertTest
//
//*****************************************************************************
void PMBusController_initNoAlertTest(PMBus_TestHandle handle)
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
    // Set count to 1
    //
    handle->count = 1U;

    //
    // Enable the test
    //
#if ENABLE_TEST_16 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_16 == 1
}

//*****************************************************************************
//
// PMBusController_runNoAlertTest
//
//*****************************************************************************
void PMBusController_runNoAlertTest(PMBus_TestHandle handle)
{
    //
    // Important: A 2nd target is required to be on the network to assert
    // the alert line in order to test the 1st target software stack response.
    //
    // Lets assume 2nd target address is 0x39
    //

    //
    // Increment fail, a DATA_REQUEST should set it back to 0
    //
    handle->fail++;

    //
    // Do a Quick command
    // Config the controller enable Write (by omitting the read
    // option from the configWord, you enable write), 0 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_2_ADDRESS, 0U, PMBUS_ENABLE_WRITE);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
        if(controllerDataRequested == true)
        {
            //
            // decrement fail if DATA_REQUEST was asserted
            //
            handle->fail--;

            //
            // Reset the flag
            //
            controllerDataRequested = false;

            //
            // NACK the transaction to complete the quick command
            //
            PMBus_nackTransaction(PMBUSA_BASE);
        }
    }

    //
    // Reset the EOM flag
    //
    endOfMessage = false;

    //
    // Once the bus is free, if the target NACK'd its a failure
    //
    (targetAckReceived == true) ? handle->pass++ : handle->fail++;

    //
    // Loop till the alert signal is asserted
    //
    while(alertEdgeAsserted == false)
    {
    }

    //
    // Clear the spot where the alerting target's address will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // An alert was recevied
    // Configure the controller to set the address to the alert address,
    // enable Read and expect the alerting target's address (no PEC)
    //
    PMBus_configController(PMBUSA_BASE, ALERT_RESPONSE_ADDRESS, 1U,
                       PMBUS_CONTROLLER_ENABLE_READ);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
    }
    PMBus_getControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0],
                        pmbusStatus);

    //
    // NOTE:  the alert line needs to be asserted for the target to respond
    // to the alert response address, if you de-assert early the target
    // ignores the alert response address line. The target state machine will
    // de-assert when it detects an EOM, NACK and ALERT_EDGE
    //

    //
    // Check DATA_READY is asserted at the end of alert response
    //
    (controllerDataAvailable == true) ? handle->pass++ : handle->fail++;

    //
    // Check that the alerting target sent its address
    //
    (bytesReceived == 1U) ? handle->pass++ : handle->fail++;

    //
    // Target sends its address in the 7 most significant bits with a
    // 0 or 1 in the LSb, which we dont care about
    //
    ((pmbusControllerBuffer[0] & TARGET_ADDRESS_MASK) == (TARGET_2_ADDRESS << 1U)) ?
                                                    handle->pass++ :
                                                    handle->fail++;

    //
    // Reset flags
    //
    PMBusController_resetGlobalFlags();

    //
    // Increment fail, a DATA_REQUEST should set it back to 0
    //
    handle->fail++;

    //
    // Do a Quick command to 1st target
    // Config the controller enable Write (by omitting the read
    // option from the configWord, you enable write), 0 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 0U, 0U);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
        if(controllerDataRequested == true)
        {
            //
            // decrement fail if DATA_REQUEST was asserted
            //
            handle->fail--;

            //
            // Reset the flag
            //
            controllerDataRequested = false;

            //
            // NACK the transaction to complete the quick command
            //
            PMBus_nackTransaction(PMBUSA_BASE);
        }
    }

    //
    // Once the bus is free, if the target NACK'd its a failure
    //
    (targetAckReceived == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 5U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
