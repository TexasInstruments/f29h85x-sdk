//###########################################################################
//
// FILE:   main.c
//
// TITLE:  PMBUS Target Demo Code
//
// Note: Requires connection to PMBus controller running controller demo
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
#include <string.h>
#include "board.h"

//
// Globals
//
PMBus_StackObject pmbusStackTarget;
PMBus_StackHandle pmbusStackTargetHandle = &pmbusStackTarget;
uint16_t pmbusTargetBuffer[300U];
volatile uint16_t testsCompleted = 0U;
volatile uint16_t pass = 0U, fail = 0U;

//
// Function Prototypes
//
__attribute__((section(".TI.ramfunc")))
__attribute__((interrupt("INT"))) void pmbusIntHandler(void);
void PMBusStack_defaultErrorHandler(void);
void (*PMBusStack_errorHandler)(void);
//
// Main
//
int main(void)
{
    //
    // Locals
    //
    uint16_t i;
    //uint32_t moduleFreq = 0U;
    PMBusStack_errorHandler = PMBusStack_defaultErrorHandler;
#if defined(_FLASH)
    //
    // Setup the Flash banks
    //
    PMBusExample_setupFlash();
#endif //defined(_FLASH)

    //
    // Device initialization
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Transaction Handlers
    //
    // Set the default handlers, user must overwrite
    //
    for(i = 0U; i < NTRANSACTIONS; i++)
    {
        PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                        (PMBus_Transaction)i, (void (*)(void *))
                                        PMBusStack_defaultTransactionHandler);
    }

    //
    // Overwrite the send byte transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_SENDBYTE,
                              (void (*)(void *))PMBusTarget_sendByteTestHandler);

    //
    // Overwrite the write byte transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_WRITEBYTE,
                             (void (*)(void *))PMBusTarget_writeByteTestHandler);

    //
    // Overwrite the write word transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_WRITEWORD,
                             (void (*)(void *))PMBusTarget_writeWordTestHandler);

    //
    // Overwrite the block write transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_BLOCKWRITE,
                            (void (*)(void *))PMBusTarget_blockWriteTestHandler);

    //
    // Overwrite the Receive Byte transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_RECEIVEBYTE,
                           (void (*)(void *))PMBusTarget_receiveByteTestHandler);

    //
    // Overwrite the Read Byte transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_READBYTE,
                              (void (*)(void *))PMBusTarget_readByteTestHandler);

    //
    // Overwrite the Read Word transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_READWORD,
                              (void (*)(void *))PMBusTarget_readWordTestHandler);

    //
    // Overwrite the Block Read transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_BLOCKREAD,
                             (void (*)(void *))PMBusTarget_blockReadTestHandler);

    //
    // Overwrite the Block Write Read Process Call transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                 PMBUS_TRANSACTION_BLOCKWRPC, (void (*)(void *))
                               PMBusTarget_blockWriteReadProcessCallTestHandler);

    //
    // Overwrite the Quick Command transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                          PMBUS_TRANSACTION_QUICKCOMMAND,
                         (void (*)(void *))PMBusTarget_quickCommandTestHandler);

    //
    // Set the buffer to some default non-zero value
    //
    memset(pmbusTargetBuffer, 0xBAADU, sizeof(pmbusTargetBuffer));

    //
    // Setup the PMBUS Stack Object
    //
    PMBusStackObject_setMode(pmbusStackTargetHandle, PMBUS_STACK_MODE_TARGET);

    //
    // Set the target address and mask
    //
    PMBusStackObject_setTargetAddress(pmbusStackTargetHandle, TARGET_ADDRESS);
    PMBusStackObject_setTargetAddressMask(pmbusStackTargetHandle,
                                         TARGET_ADDRESSMASK);

    //
    // Initialize the state machine handler
    //
    PMBusStack_initModule(pmbusStackTargetHandle, PMBUSA_BASE,
                          &pmbusTargetBuffer[0]);

    //
    // Configure the PMBUS module clock to be PMBUS_MODULE_FREQ_MAX
    //
   // moduleFreq = PMBus_configModuleClock(PMBUSA_BASE, PMBUS_MODULE_FREQ_MAX,
   //                                      PMBUS_SYS_FREQ_MAX);

    //
    // Configure the PMBUS bus clock
    ///
    //PMBus_configBusClock(PMBUSA_BASE, PMBUS_CLOCKMODE_STANDARD, moduleFreq);

    //
    // Loop until tests complete
    //
    while(testsCompleted != NENABLEDTESTS)
    {
        if(fail > 0U)
        {
            //
            // Upon fail, halt debugger
            //
            __asm(" EMUSTOP0");
        }
    };

    //
    // Tests complete - Enter wait loop
    //
    done();

    //
    // Code does not reach this point
    //
    return(1);
}

//
// pmbusIntHandler - This is the main PMBus interrupt handler. Calls target
//                   stack state machine.
//
__attribute__((interrupt("INT"))) void INT_myPMBUS0_ISR(void)
{
    //
    // Call the library State Machine handler
    //
    PMBusStack_targetStateHandler(pmbusStackTargetHandle);

    //
    // ACK any pending interrupts (if any got set)
    //
    // Interrupt_clearACKGroup(PMBUS_INT_ACK);
}
void PMBusStack_defaultErrorHandler(void)
{
    // User must rewrite this to handle error
    for(;;);
}
//
// End of File
//
