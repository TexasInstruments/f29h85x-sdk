//#############################################################################
//
// FILE:   mcan_ex3_loopback_interrupts_fifo.c
//
// TITLE:   MCAN Loopback with Interrupts, fifo mode Example Using SYSCONFIG Tool
//
//! \addtogroup driver_example_list
//! <h1> MCAN Loopback with Interrupts Example Using SYSCONFIG Tool </h1>
//!
//! This example illustrates the following MCAN features:
//! -> Loopback mode
//! -> Interrupt enabled
//! -> TX fifo used
//!     -> Messages are transmitted in the order in which they are added to fifo
//! -> RX fifo 0 used
//!     -> Multiple messages of same id can be received
//! -> Rx range filtering is enabled with sfid1 = 0 and sfid2 = 4
//! Multiple messages (NUM_FRAMES) are transmitted and received
//! -> Two messages have same id
//! Peripheral configuration is done through SYSCONFIG
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - rxMsgCnt - Number of received messages should be equal to 'NUM_FRAMES'
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
//  MCAN message interrupt mask
//  The following interrupt events are checked
//  -> bit[0]   - Rx FIFO 0 New Message
//  -> bit[9]   - Transmission Completed
//  -> bit[11]  - Tx FIFO Empty
//  -> bit[12]  - Tx Event FIFO New Entry
//
#define MCAN_IR_MASK        (MCAN_IR_RF0N_MASK  |   \
                             MCAN_IR_TC_MASK    |   \
                             MCAN_IR_TFE_MASK   |   \
                             MCAN_IR_TEFN_MASK)

//
//  Number of messages to transmit and receive
//
#define NUM_FRAMES          (5U)

//
// Global Variables.
//
volatile uint32_t isrIntrFlag0  = 0U;
volatile uint32_t isrIntrFlag1  = 0U;
volatile uint32_t rxMsgCnt      = 0U;

//
// Function Prototype.
//
void MCANIntr0ISR(void);
void MCANIntr1ISR(void);

//
// Main
//
int main(void)
{
    uint32_t                cnt;
    MCAN_RxFIFOStatus       rxFifoSts;
    MCAN_TxBufElement       txMsg;
    MCAN_TxEventFIFOStatus  txEventFifoSts;
    MCAN_RxBufElement       rxMsg[NUM_FRAMES];
    MCAN_TxEventFIFOElement txEvent[NUM_FRAMES];
    uint32_t                msgId[NUM_FRAMES]      = {0x4, 0x3, 0x2, 0x1, 0x1};
    uint32_t                msgMarker[NUM_FRAMES]  = {0xAA, 0x99, 0x88, 0x77, 0x66};
    uint16_t                msgData[NUM_FRAMES][4] =
                                {
                                    {0x12, 0x34, 0x56, 0x78},
                                    {0x34, 0x12, 0x78, 0x56},
                                    {0x78, 0x56, 0x34, 0x12},
                                    {0x56, 0x78, 0x12, 0x34},
                                    {0x65, 0x87, 0x21, 0x43}
                                };

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Initialize message to transmit.
    //
    txMsg.rtr      = 0U; // Transmit data frame.
    txMsg.xtd      = 0U; // 11-bit standard identifier.
    txMsg.esi      = 0U; // ESI bit in CAN FD format depends only on error
                         // passive flag.
    txMsg.dlc      = 4U; // CAN + CAN FD: transmit frame has 0-8 data bytes.
    txMsg.brs      = 1U; // CAN FD frames transmitted with bit rate
                         // switching.
    txMsg.fdf      = 1U; // Frame transmitted in CAN FD format.
    txMsg.efc      = 1U; // Store Tx events.

    //
    //  Transmit 'NUM_FRAMES' frames
    //  ->  Two frames having same id = 0x1 are transmitted
    //
    for(cnt = 0U;cnt < NUM_FRAMES;cnt++)
    {
        txMsg.id        = ((uint32_t)(msgId[cnt])) << 18U;
        txMsg.mm        = msgMarker[cnt];
        txMsg.data[0]   = msgData[cnt][0];
        txMsg.data[1]   = msgData[cnt][1];
        txMsg.data[2]   = msgData[cnt][2];
        txMsg.data[3]   = msgData[cnt][3];
        //
        // Write Tx Message to the Message RAM.
        //
        MCAN_writeMsgRam(
                    myMCAN0_BASE,
                    MCAN_MEM_TYPE_FIFO,
                    0U,                                 // unused in fifo mode
                    &txMsg);

        //
        // Enable Transmission interrupt.
        //
        MCAN_txBufTransIntrEnable(
                    myMCAN0_BASE,
                    (myMCAN0_MCAN_TX_BUFF_SIZE + cnt),  // tx fifo index start at end of tx dedicated buffers
                    1U);

        //
        // Add request for transmission.
        //
        MCAN_txBufAddReq(
                    myMCAN0_BASE,
                    (myMCAN0_MCAN_TX_BUFF_SIZE + cnt)); // tx fifo index start at end of tx dedicated buffers
    }

    //
    // Wait for an interrupt
    //
    while(0U == isrIntrFlag1)
    {
        ;
    }

    //
    //  Read the tx event fifo
    //
    for(cnt = 0U;cnt < NUM_FRAMES;cnt++)
    {
        //
        //  Get event FIFO status
        //
        MCAN_getTxEventFIFOStatus(myMCAN0_BASE, &txEventFifoSts);

        //
        //  Read event fifo if the fill level is greater than 0
        //
        if(txEventFifoSts.fillLvl > 0U)
        {
            MCAN_readTxEventFIFO(myMCAN0_BASE, &txEvent[cnt]);
            MCAN_writeTxEventFIFOAck(myMCAN0_BASE, txEventFifoSts.getIdx);
        }
    }

    //
    //  Read the received frames
    //
    rxMsgCnt = 0U;
    for(cnt = 0U;cnt < NUM_FRAMES;cnt++)
    {
        //
        //  Get RX fifo status
        //
        rxFifoSts.num = MCAN_RX_FIFO_NUM_0;
        MCAN_getRxFIFOStatus(myMCAN0_BASE, &rxFifoSts);

        //
        // Read Message RAM only if fifo fill level is greater than 0
        //
        if(rxFifoSts.fillLvl > 0U)
        {
            //
            //  Increment message count
            //
            rxMsgCnt++;

            //
            //  Read message from the fifo
            //
            MCAN_readMsgRam(
                    myMCAN0_BASE,
                    MCAN_MEM_TYPE_FIFO,
                    0U,                         // unused in rx fifo mode
                    MCAN_RX_FIFO_NUM_0,
                    &rxMsg[cnt]);

            //
            //  Acknowledge that message is read from fifo
            //  ->  Updates the fifo get index
            //
            MCAN_writeRxFIFOAck(
                    myMCAN0_BASE,
                    MCAN_RX_FIFO_NUM_0,
                    rxFifoSts.getIdx);
        }
    }

    //
    //  Check no of received messages
    //
    if(NUM_FRAMES != rxMsgCnt)
    {
        ESTOP0;
    }

    //
    // Stop Application.
    //
    ESTOP0;
}

//
// This is Interrupt Service Routine for MCAN interrupt 0.
//
void MCANIntr0ISR(void)
{
    uint32_t intrStatus;
    intrStatus = MCAN_getIntrStatus(myMCAN0_BASE);

    if (MCAN_IR_MASK == intrStatus)
    {
        isrIntrFlag0++;
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(myMCAN0_BASE, intrStatus);

    //
    //  Clearing the interrupt lineNum
    //
    MCAN_clearInterrupt(myMCAN0_BASE, 0x1);
}

//
// This is Interrupt Service Routine for MCAN interrupt 1.
//
void MCANIntr1ISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(myMCAN0_BASE);
    if (MCAN_IR_MASK == intrStatus)
    {
        isrIntrFlag1++;
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(myMCAN0_BASE, intrStatus);

    //
    //  Clearing the interrupt lineNum
    //
    MCAN_clearInterrupt(myMCAN0_BASE, 0x2);
}
