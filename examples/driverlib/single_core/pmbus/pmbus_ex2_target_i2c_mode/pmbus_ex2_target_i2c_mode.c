//#############################################################################
//
// FILE:   pmbus_ex2_target_i2c_mode.c
//
// TITLE:  PMBus in I2C Mode Target
//
//! \addtogroup driver_example_list
//! <h1>PMBus in I2C Mode Target</h1>
//!
//! This example demonstrates PMBus operating in I2C target mode.
//! It receives data from a PMBus controller and stores it in a buffer.
//! The data is then compared with a reference buffer to verify correct
//! transfer.
//!
//! It is recommended to run this example with a companion PMBus controller
//! in I2C mode example to observe the complete data transfer.
//!
//! \b External \b Connections \n
//!   - Connect PMBUS SCL (Controller) to SCL (Target)
//!   - Conect PMBUS SDA (Controller) to SDA (Target)
//!   - NOTE: (2) F29x devices are required to run this example which uses
//!   - (1) PMBUS module per device.
//!
//! \b Watch \b Variables \n
//!  - \b rData - Receive data buffer
//!  - \b status - Transfer completion status
//!
//
//#############################################################################
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

//#############################################################################

//
// Included Files
//
#include "board.h"

//
// Defines
//
#define BUFFER_SIZE         4     // Transmit data buffer size
#define PASS                1     // Test pass status
#define FAIL                0     // Test fail status

//
// Globals
//
__attribute__((location(0x200E1000))) volatile uint16_t sData[BUFFER_SIZE]; // Send data buffer
__attribute__((location(0x200E2000))) volatile uint16_t rData[BUFFER_SIZE]; // Receive data buffer
unsigned int status;                                                        // Transfer status
unsigned int error;                                                         // Indicates errors
volatile uint16_t transferComplete = 0;                                     // Transfer completion check (6 = (1) ISR generated for TARGET ADDR MATCH, EOM, (4) BYTES)
volatile uint16_t transfersRemaining = 6;                                   // Expected number of transfers
volatile uint32_t target_addr = 0;

//
// Function Prototypes
//
void done(void);

//
// Main
//
int main(void)
{
    // Initialize device
    Device_init();

    // Configure GPIOs, peripherals, etc.
    Board_init();

    // Initialize source buffer
    volatile uint16_t i = 0, j = 0;
    for(i = 0; i < BUFFER_SIZE; i++)
    {
        sData[i] = i;
    }

    // Enable global interrupts
    ENINT;
    Interrupt_enableGlobal();

    // Wait for all transfers to complete
    while (!transferComplete)
    {
        // Check if all expected transfers have been processed
        if (transfersRemaining == 0)
        {
            for(j = 0; j < 4; j++)
            {
                if(sData[j] != rData[j])
                {
                    error++;
                }
            }
            Interrupt_disable(INT_PMBUSA);
            transferComplete = 1;
        }
    }

    // Set test status based on transfer completion
    if (transferComplete == 1)
    {
        status = PASS;
        done();
    } else
    {
        status = FAIL;
    }

    return status;
}

//
// PMBus ISR
// Handles three events:
// - TARGET_ADDR_READY: PMBus target address match
// - DATA_REQUEST: PMBus target receives data
// - EOM: End-of-Message received, indicating transfer completion
//
void INT_myPMBUS0_ISR(void)
{
    // Get current PMBus status register contents
    volatile uint32_t status_check = PMBus_getStatus(myPMBUS0_BASE);

    // Handle target address match event
    if(status_check & PMBUS_PMBSTS_TARGET_ADDR_READY)
    {
        transfersRemaining--;
        // Read the target address + Acknowledge if address matches our device
        PMBus_ackAddress(myPMBUS0_BASE, myPMBUS0_TARGET_ADDRESS, status_check, rData);
    }

    // Handle data request event
    if(status_check & PMBUS_PMBSTS_DATA_READY)
    {
        transfersRemaining--;
        PMBus_getData(myPMBUS0_BASE, (uint16_t*)rData, status_check);
        // Acknowledge data reception
        PMBus_ackTransaction(myPMBUS0_BASE);
    }

    // Handle end-of-message event
    if(status_check & PMBUS_PMBSTS_EOM)
    {
        transfersRemaining--;
    }
}

//
// Test finished as expected
//
void done(void)
{
    ESTOP0;
    for (;;);
}

//
// End of File
//
