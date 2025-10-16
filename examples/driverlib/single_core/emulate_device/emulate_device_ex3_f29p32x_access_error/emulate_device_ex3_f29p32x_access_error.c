//#############################################################################
//
// FILE:    emulate_device_ex3_f29p32x_access_error.c
//
// TITLE:   Induce and handle an access error in emulated F29P32x
//
//! \addtogroup driver_example_list
//! <h1> F29P32x Access Error example </h1>
//!
//! This example demonstrates how to emulate F29P32x on F29H85x, and induce
//! an access error to check if the emulation was successful. The access error
//! is then handled in the NMI ISR.
//!
//! This example emulates F29P32x device by calling SysCtl_emulateDevice() API
//! with the appropriate part number.
//! CDAx RAM is not available on F29P32x device. When CPU1 tries to write to
//! this unavailable memory location, an access ack error is generated on the DW
//! interface, resulting in an NMI. In the NMI ISR, the address is updated
//! to a valid LPAx RAM location and the access error statuses are cleared.
//! A device LED is configured through the SysConfig file and is switched ON
//! when the access error occurs.
//!
//! \b External \b Connections \n
//!   - None
//!
//! \b Watch \b Variables \n
//!  - \b error_generated_status - Status of Error Aggregator CPU1 HPERR.
//!  - \b acc_ack_error_status - Status of ACC_ACK_ERR on CPU1 DW interface.
//!  - \b error_type - Value of Error Aggregator CPU1 DW Error Type.
//!                    This should correspond to the ACC_ACK_ERR.
//!  - \b error_address - Address where access ACK error has occurred.
//!                       This should correspond to the CDAx RAM address.
//!
//
//#############################################################################
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

uint32_t writeVal = 1;                      // Value to be written in the specified address
uint32_t *address = (uint32_t*)0x20120000;  // CDAx RAM location

bool error_generated_status = false;
bool acc_ack_error_status = false;
uint32_t error_type = 0;
uint32_t error_address = 0;

//
// Main
//
int main(void)
{
    //
    // Emulate F29P329SM2
    //
    SysCtl_emulateDevice(SYSCTL_EMULATE_F29P329SM2Q);

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();

    //
    // Loop.
    //
    for(;;)
    {
        //
        // Write to the specified address.
        // This will create an NMI when CDA address is used, as CDA is not available in F29P32x
        //
        *address = writeVal;
        writeVal++;

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(1000000);
    }
}

void myNMI_ISR(void)
{
    ErrorAggregator_CpuErrorInfo nmiStatus;

    //
    // Check if the correct error event ESM_EVENT_ErrorAggregator_CPU1_HPERR is
    // Active/Pending and Enabled using the status register
    //
    error_generated_status = ESM_getInterruptStatus(ESMSYSTEM_BASE, ESM_EVENT_ErrorAggregator_CPU1_HPERR);

    //
    // Check if the CPU1 DW Interface has the ACC_ACK_ERR set
    //
    ErrorAggregator_getCpuErrorInfo(ERRORAGGREGATOR_BASE, EA_SRC_CPU1, &nmiStatus);
    error_type = nmiStatus.dw.errorType;
    acc_ack_error_status = (error_type == 0x20);

    //
    // Turn on LED to indicate Access Acknowledgement Error (ACC_ACK_ERR)
    //
    if (acc_ack_error_status)
    {
        GPIO_writePin(myBoardLED0_GPIO, 0);
    }

    //
    // Get the address where ACK error has occurred
    //
    error_address = nmiStatus.dw.highPriErrAddr;

    ESTOP0;

    //
    // Update the address to a valid LDAx RAM location
    //
    address = (uint32_t*)0x200EC000;

    //
    // Clear Error Aggregator error type flags on CPU1 to allow further high priority errors
    //
    ErrorAggregator_clearCpuError(ERRORAGGREGATOR_BASE, EA_SRC_CPU1);

    //
    // Clear the raw status of corresponding ESM events
    //
    ESM_clearRawInterruptStatus(ESMSYSTEM_BASE,ESM_EVENT_ErrorAggregator_CPU1_HPERR);
    ESM_clearRawInterruptStatus(ESMCPU1_BASE,ESM_EVENT_CPU1_ERAD_NMI);
    ERAD_clearCounterEvent(ERAD_COUNTER3);

    //
    // Write the end of interrupt vector to the EOI Interrupt Register. In case there
    // are enabled error events pending then a new pulse is generated and level
    // interrupt remains asserted, else no new pulse is generated.
    //
    ESM_writeEOIVector(ESMSYSTEM_BASE, ESM_EOI_LOW_PRIORITY_ERROR_INTERRUPT);
    ESM_writeEOIVector(ESMCPU1_BASE, ESM_EOI_HIGH_PRIORITY_ERROR_INTERRUPT);
}

//
// End of File
//

