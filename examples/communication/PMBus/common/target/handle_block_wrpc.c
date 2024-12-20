//###########################################################################
//
// FILE:   handle_block_wrpc.c
//
// TITLE:  Block Write-Read Process Call (255 bytes)
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
#include "pmbus_target_test.h"

//*****************************************************************************
//
// PMBusTarget_blockWriteReadProcessCallTestHandler
//
//*****************************************************************************
void PMBusTarget_blockWriteReadProcessCallTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = PMBusStackObject_getNumOfBytes(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t i;
    uint16_t preRunPass = pass;

    //
    // Check that target received command, byte count, 255 bytes but no PEC
    //
    (nBytes == 257U) ? pass++ : fail++;
    (buffer[0U] == PMBUS_CMD_PAGE_PLUS_READ) ? pass++ : fail++;
    (buffer[1U] == DATA_BYTE_COUNT) ? pass++ : fail++;

    for(i = 1U; i <= DATA_BYTE_COUNT; i++)
    {
        if(buffer[i + 1U] == (PMBUS_CMD_PAGE_PLUS_READ ^ i))
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }

    //
    // The Block Read portion
    // Set the number of bytes to send (inlcuding the byte count)
    //
    PMBusStackObject_setNumOfBytes(handle, (DATA_BYTE_COUNT + 1U));

    //
    // Set the byte cont as the first byte to be transmitted
    //
    buffer[0] = DATA_BYTE_COUNT;

    //
    // Send message to controller
    //
    for(i = 1U; i <= DATA_BYTE_COUNT; i++)
    {
        buffer[i] = buffer[i+1] ^ i;
    }

    //
    // Check transaction type
    //
    (transaction == PMBUS_TRANSACTION_BLOCKWRPC) ? pass++: fail++;

    //
    // Change the Block Write/Read/Process Call handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_BLOCKWRPC,
                           (void (*)(void *))PMBusTarget_processCallTestHandler);

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 259U)
    {
        fail++;
    }

    //
    // Update number of completed tests
    //
    testsCompleted++;
#ifdef ENABLE_MCPI                                  // MCPI
    if(fail > 0)                                    // MCPI
    {                                               // MCPI
        MCPI_setLogMessage("TESTCASE WRPC FAIL");  // MCPI
        MCPI_setResultFail();                       // MCPI
    }                                               // MCPI
    else                                            // MCPI
    {                                               // MCPI
        MCPI_setLogMessage("TESTCASE WRPC PASS");  // MCPI
        MCPI_setResultPass();                       // MCPI
    }                                               // MCPI
#endif                                              // MCPI    
}

//
// End of File
//
