//###########################################################################
//
// FILE:   main.c
//
// TITLE:  PMBUS Controller Demo Code
//
// Note: Requires connection to PMBus target running target demo
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
#include "board.h"
//
// Defines
//
#define ZERO_BYTES               0U
#define FOUR_BYTES               4U
#define PMBSTS_EOM_S             5U
#define PMBSTS_NACK_S            6U
#define PMBSTS_DATAREQUEST_S     4U
#define PMBSTS_PEC_VALID_S       7U
#define PMBSTS_ALERT_EDGE_S      16U
#define PMBSTS_CLK_LOW_TIMEOUT_S 8U

//
// Globals
//
PMBus_StackObject pmbusStackController;
PMBus_StackHandle pmbusStackControllerHandle = &pmbusStackController;
uint16_t pmbusControllerBuffer[256];

volatile bool targetAckReceived = false;
volatile bool controllerDataAvailable = false;
volatile bool controllerDataRequested = false;
volatile bool receivedPecValid = false;
volatile bool endOfMessage = false;
volatile bool alertEdgeAsserted = false;
volatile bool clockLowTimeout = false;
volatile uint16_t bytesReceived = ZERO_BYTES;
volatile uint32_t pmbusStatus = 0UL;
volatile int16_t pass = 0U, fail = 0U;

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
    uint16_t i, counter;
    uint32_t moduleFreq = 0U;
    PMBusStack_errorHandler = PMBusStack_defaultErrorHandler;
#if defined(_FLASH)
    //
    // Setup the Flash banks
    //
    PMBusExample_setupFlash();
#endif // _FLASH

    //
    // Device initialization
    //
    Device_init();


    //
    // Board initialization
    //
    Board_init();

    //
    // Setup the PMBUS Library Stack Object
    //
    PMBusStackObject_setMode(pmbusStackControllerHandle, PMBUS_STACK_MODE_CONTROLLER);
    PMBusStack_initModule(pmbusStackControllerHandle, PMBUSA_BASE,
                          &pmbusControllerBuffer[0]);

    //
    // Configure the PMBUS module clock to be less than PMBUS_MODULE_FREQ_MAX
    //
    //moduleFreq = PMBus_configModuleClock(PMBUSA_BASE, PMBUS_MODULE_FREQ_MAX,
    //                                     PMBUS_SYS_FREQ_MAX);

    //
    // Configure the PMBUS bus clock
    //
    //PMBus_configBusClock(PMBUSA_BASE, PMBUS_CLOCKMODE_STANDARD, moduleFreq);

    //
    // Call each test sequentially and check the outputs
    //
    for(i = 0; i < NTESTS; i++)
    {
        //
        // Clear the buffer
        // Set the buffer to some default non-zero value
        //
        memset(pmbusControllerBuffer, 0xBAADU, sizeof(pmbusControllerBuffer));

        handle = &PMBUS_TESTS[i];
        handle->init = (void (*)(void *))initTestList[i];
        handle->run = (void (*)(void *))runTestList[i];

        if(handle->init != NULL)
        {
            handle->init(handle);
        }

        //
        // Reset pass, fail statuses
        //
        handle->pass = 0;
        handle->fail = 0;

        //
        // Run test when enabled
        //
        if(handle->enabled == true)
        {
            //
            // Run test
            //
            handle->run(handle);

            //
            // Wait some time to allow the target to complete processing the
            // transaction before proceeding
            //
            for(counter = 0U; counter < 1000U; counter++)
            {
            }

            //
            // Tally the pass/fail metrics
            //
            pass += handle->pass;
            fail += handle->fail;

            //
            // Halt debugger if test failed
            //
            if(handle->fail > 0U)
            {
                __asm(" EMUSTOP0");
            }
        }
        //
        // Test is disabled
        //
        else
        {
            handle->pass = -1;
            handle->fail = -1;
        }
    }

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
// pmbusIntHandler - This is the main PMBus interrupt handler. Read out the data
//                   from the PMBus module status register and acknowledge the
//                   interrupt.
//
__attribute__((interrupt("INT"))) void INT_myPMBUS0_ISR(void)
{
    //
    // Read the PMBus module status register
    //
    pmbusStatus = PMBus_getStatus(PMBUSA_BASE);

    //
    // Write to the PMBUS_STACK object
    //
    PMBusStackObject_setModuleStatus(pmbusStackControllerHandle, pmbusStatus);

    //
    // Read out individual status information into global variables
    //
    bytesReceived = (pmbusStatus & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                    PMBUS_PMBSTS_RD_BYTE_COUNT_S;
    endOfMessage = (bool)((pmbusStatus & PMBUS_PMBSTS_EOM) >> PMBSTS_EOM_S);
    targetAckReceived = (bool)((~pmbusStatus & PMBUS_PMBSTS_NACK) >>
                              PMBSTS_NACK_S);
    controllerDataRequested = (bool)((pmbusStatus & PMBUS_PMBSTS_DATA_REQUEST) >>
                                 PMBSTS_DATAREQUEST_S);
    receivedPecValid = (bool)((pmbusStatus & PMBUS_PMBSTS_PEC_VALID) >>
                              PMBSTS_PEC_VALID_S);
    alertEdgeAsserted = (bool)((pmbusStatus & PMBUS_PMBSTS_ALERT_EDGE) >>
                               PMBSTS_ALERT_EDGE_S);
    clockLowTimeout = (bool)((pmbusStatus & PMBUS_PMBSTS_CLK_LOW_TIMEOUT) >>
                             PMBSTS_CLK_LOW_TIMEOUT_S);

    //
    // Check if data is available for controller
    // (Bytes of data received isn't zero or is equal to 4 bytes with
    //  data ready status set)
    //
    if((bytesReceived != ZERO_BYTES) ||
       ((bytesReceived == FOUR_BYTES) &&
        ((pmbusStatus & PMBUS_PMBSTS_DATA_READY) != 0U)))
    {
        controllerDataAvailable = true;
    }
}
void PMBusStack_defaultErrorHandler(void)
{
    // User must rewrite this to handle error
    for(;;);
}
//
// End of File
//
