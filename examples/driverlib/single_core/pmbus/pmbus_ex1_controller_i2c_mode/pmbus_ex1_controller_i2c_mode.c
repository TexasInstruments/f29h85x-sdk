//#############################################################################
//
// FILE:   pmbus_ex1_controller_i2c_mode.c
//
// TITLE:  PMBus in I2C Mode Controller
//
//! \addtogroup driver_example_list
//! <h1>PMBus in I2C Mode Controller</h1>
//!
//! This example demonstrates PMBus operating in I2C controller mode.
//! It transfers data from a buffer to the PMBus transmit buffer,
//! which is then sent to a PMBus target device.
//!
//! It is recommended to run this example with a companion PMBus target
//! in I2C mode example to observe the complete data transfer.
//!
//! \b External \b Connections \n
//!   - Connect PMBUS SCL (Controller) to SCL (Target)
//!   - Conect PMBUS SDA (Controller) to SDA (Target)
//!   - NOTE: (2) F29x devices are required to run this example which uses
//!   - (1) PMBUS module per device.
//!
//! \b Watch \b Variables \n
//!  - \b sData - Data to send
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
unsigned int status;                                                        // Transfer status
volatile uint16_t transferComplete = 0;                                     // Transfer completion check
volatile uint16_t transfersRemaining = 2;                                   // Expected number of transfers

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
    volatile uint16_t i;
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
// Handles two events:
// - DATA_REQUEST: PMBus controller needs data to transmit
// - EOM: End-of-Message received, indicating transfer completion
//
void INT_myPMBUS0_ISR(void)
{
    // Get current PMBus status register contents
    volatile uint32_t status_check = PMBus_getStatus(myPMBUS0_BASE);

    // Handle data request event
    if(status_check & PMBUS_PMBSTS_DATA_REQUEST)
    {
        transfersRemaining--;

        // Provide data to the transmit buffer
        PMBus_putControllerData(myPMBUS0_BASE, (uint16_t*)sData, BUFFER_SIZE);
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
