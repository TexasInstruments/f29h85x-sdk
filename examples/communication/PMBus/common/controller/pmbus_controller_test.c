//###########################################################################
//
// FILE:   pmbus_controller_test.c
//
// TITLE:  Various controller transactions for testing target state machine
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

//
// Globals
//
PMBus_TestObject PMBUS_TESTS[NTESTS];
PMBus_TestHandle handle;

void (*initTestList[NTESTS])(PMBus_TestHandle) =
{
        PMBusController_initSendByteTest,
        PMBusController_initWriteByteTest,
        PMBusController_initWriteWordTest,
        PMBusController_initBlockWriteTest,
        PMBusController_initReceiveByteTest,
        PMBusController_initReadByteTest,
        PMBusController_initReadWordTest,
        PMBusController_initBlockReadTest,
        PMBusController_initBlockWriteReadProcessCallTest,
        PMBusController_initQuickCommandTest,
        PMBusController_initBlockWrite2BytesTest,
        PMBusController_initBlockWrite3BytesTest,
        PMBusController_initBlockRead3BytesTest,
        PMBusController_initProcessCallTest,
        PMBusController_initAlertTest,
        PMBusController_initNoAlertTest,
        PMBusController_initGroupCommandTest,
        PMBusController_initExtendedWriteByteTest,
        PMBusController_initExtendedWriteWordTest,
        PMBusController_initExtendedReadByteTest,
        PMBusController_initExtendedReadWordTest,
};

void (*runTestList[NTESTS])(PMBus_TestHandle) =
{
        PMBusController_runSendByteTest,
        PMBusController_runWriteByteTest,
        PMBusController_runWriteWordTest,
        PMBusController_runBlockWriteTest,
        PMBusController_runReceiveByteTest,
        PMBusController_runReadByteTest,
        PMBusController_runReadWordTest,
        PMBusController_runBlockReadTest,
        PMBusController_runBlockWriteReadProcessCallTest,
        PMBusController_runQuickCommandTest,
        PMBusController_runBlockWrite2BytesTest,
        PMBusController_runBlockWrite3BytesTest,
        PMBusController_runBlockRead3BytesTest,
        PMBusController_runProcessCallTest,
        PMBusController_runAlertTest,
        PMBusController_runNoAlertTest,
        PMBusController_runGroupCommandTest,
        PMBusController_runExtendedWriteByteTest,
        PMBusController_runExtendedWriteWordTest,
        PMBusController_runExtendedReadByteTest,
        PMBusController_runExtendedReadWordTest,
};

//
// End of File
//
