//#############################################################################
//
// FILE:   mcan_ex2_loopback_polling.c
//
// TITLE:   MCAN Loopback with Polling Example Using SYSCONFIG Tool
//
//! \addtogroup driver_example_list
//! <h1> MCAN Loopback with Polling Example Using SYSCONFIG Tool </h1>
//!
//! This example illustrates the MCAN Loopback functionality. The internal
//! loopback mode is entered. The message transmitted would be received by the
//! node. The last address of memory is used for the Rx buffer.
//! Peripheral configuration is done through SYSCONFIG
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - msgCount - No of messages received and should be 1
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
// Include Files
//
#include "board.h"

//
// Defines
//

//
// Global Variables.
//
volatile uint32_t msgCount = 0;

//
// Function Prototype.
//

//
// Main
//
int main(void)
{
    MCAN_TxBufElement    txMsg;
    MCAN_RxBufElement    rxMsg;
    MCAN_RxNewDataStatus newData;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Initialize message to transmit.
    //
    txMsg.id       = ((uint32_t)(0x4)) << 18U; // Identifier Value.
    txMsg.rtr      = 0U; // Transmit data frame.
    txMsg.xtd      = 0U; // 11-bit standard identifier.
    txMsg.esi      = 0U; // ESI bit in CAN FD format depends only on error
                         // passive flag.
    txMsg.dlc      = 4U; // CAN + CAN FD: transmit frame has 0-8 data bytes.
    txMsg.brs      = 1U; // CAN FD frames transmitted with bit rate
                         // switching.
    txMsg.fdf      = 1U; // Frame transmitted in CAN FD format.
    txMsg.efc      = 1U; // Store Tx events.
    txMsg.mm       = 0xAAU; // Message Marker.

    //
    // Data bytes.
    //
    txMsg.data[0]  = 0x12;
    txMsg.data[1]  = 0x34;
    txMsg.data[2]  = 0x56;
    txMsg.data[3]  = 0x78;

    //
    // Write Tx Message to the Message RAM.
    //
    MCAN_writeMsgRam(myMCAN0_BASE, MCAN_MEM_TYPE_BUF, 1U, &txMsg);

    //
    // Add request for transmission.
    //
    MCAN_txBufAddReq(myMCAN0_BASE, 1U);

    //
    // Wait for the transmission to be complete
    //
    while(MCAN_getTxBufReqPend(myMCAN0_BASE))
    {
    }

    //
    // Get the New Data Status.
    //
    MCAN_getNewDataStatus(myMCAN0_BASE, &newData);

    while(((newData.statusLow) & 0x1) != 0x1)
    {
        //
        // Get the New Data Status.
        //
        MCAN_getNewDataStatus(myMCAN0_BASE, &newData);
    }

    //
    // Read Message RAM.
    //
    MCAN_readMsgRam(myMCAN0_BASE, MCAN_MEM_TYPE_BUF, 0U, MCAN_RX_FIFO_NUM_1,
                    &rxMsg);

    //
    // Clear the New Data Status
    //
    MCAN_clearNewDataStatus(myMCAN0_BASE, &newData);

    //
    // Check that received data matches sent data.
    // Device will halt here during debug if data doesn't match.
    //
    if((txMsg.data[0] != rxMsg.data[0]) ||
       (txMsg.data[1] != rxMsg.data[1]) ||
       (txMsg.data[2] != rxMsg.data[2]) ||
       (txMsg.data[3] != rxMsg.data[3]))
    {
        //
        // Device will halt here if transmitted and received data are
        // not same.
        //
        ESTOP0;
    }
    else
    {
        //
        // Increment message count if message is received.
        //
        msgCount++;
    }

    //
    // Stop Application.
    //
    ESTOP0;
}
