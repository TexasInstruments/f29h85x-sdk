//#############################################################################
//
// FILE:   fsi_ex1_loopback_cpucontrol.c
//
// TITLE:  CPU controlled data frame transfers with internal loopback
//
//! \addtogroup driver_example_list
//! <h1>FSI Loopback:CPU Control</h1>
//!
//! Example sets up infinite data frame transfers where trigger happens through
//! \b CPU. Automatic(Hw triggered) Ping frame transmission is also setup along
//! with data.
//!
//! User can edit some of configuration parameters as per usecase. These are as
//! below. Default values can be referred in code where these globals are defined
//!
//! - \b txUserData - User data to be sent with Data frame
//! - \b txDataFrameTag - Frame tag used for Data transfers
//! - \b txPingFrameTag - Frame tag used for Ping transfers
//!
//! For any errors during transfers i.e. \b error events such as Frame Overrun,
//! Underrun, Watchdog timeout and CRC/EOF/TYPE errors, execution will stop
//! immediately and status variables can be looked into for more details.
//! Execution will also stop for any mismatch between received data and sent
//! ones and also if transfers takes unusually long time(detected through
//! software counters - txTimeOutCntr and rxTimeOutCntr)
//!
//!\b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b dataFrameCntr  Number of Data frame transfered
//!  - \b error          Non zero for transmit/receive data mismatch
//!
//
//#############################################################################
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
// Included Files
//
#include "board.h"

//
// Globals, User can modify these parameters as per usecase
//

// Frame tag used with Data/Ping transfers
FSI_FrameTag txDataFrameTag = FSI_FRAME_TAG10, txPingFrameTag = FSI_FRAME_TAG15;

// User data to be sent with Data frame
uint16_t txUserData = 0x47;

//
// Globals, these are not config parameters, user are not required to edit them
//
uint16_t txEventSts = 0, rxEventSts = 0;
uint16_t *txBufAddr = 0, *rxBufAddr = 0;

uint16_t txBufData[16] = {0};
volatile uint32_t fsiTxInt1Received = 0,fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0,fsiRxInt2Received = 0;
uint32_t txTimeOutCntr = 0x100000, rxTimeOutCntr = 0x100000;
uint32_t dataFrameCntr = 0;
uint32_t error = 0;

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void disableAllFSIInterrupts(void);
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag);
void initFSI(void);
void prepareTxBufData(void);

//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(myFSITX0_BASE);
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(myFSIRX0_BASE);

    //
    // Flush Sequence before and after releasing Rx core reset, ensures flushing
    // of Rx data/clock lines and prepares it for reception
    //
    FSI_resetRxModule(myFSIRX0_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(myFSITX0_BASE, myFSITX0_PRESCALER_VAL);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(myFSIRX0_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(myFSITX0_BASE, myFSITX0_PRESCALER_VAL);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Setup tag and user data for transmission
    //
    FSI_setTxUserDefinedData(myFSITX0_BASE, txUserData);
    FSI_setTxFrameTag(myFSITX0_BASE, txDataFrameTag);
    FSI_setTxFrameType(myFSITX0_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    //
    // Now, start transmitting data frames
    //
    while(1)
    {
        //
        // Write data into Tx buffer and set other Frame specific fields
        //
        prepareTxBufData();
        FSI_writeTxBuffer(myFSITX0_BASE, txBufData, myFSITX0_nWords, 0U);

        //
        // Start Transfer
        //
        FSI_startTxTransmit(myFSITX0_BASE);

        //
        // Wait till frame done event is received by both Tx/Rx modules
        //
        while((fsiTxInt1Received != 1U) && (txTimeOutCntr != 0U))
        {
            txTimeOutCntr--;
        }

        while((fsiRxInt1Received != 1U) && (rxTimeOutCntr != 0U))
        {
            rxTimeOutCntr--;
        }

        if((txTimeOutCntr == 0) || (rxTimeOutCntr == 0))
        {
            //
            // Timeout for one of expected Tx/Rx evetns, so break execution here
            //
            break;
        }

        else
        {
            //
            // Re-initialize flags and buffer pointer before next transmission
            //
            fsiTxInt1Received = 0U;
            fsiRxInt1Received = 0U;
            txTimeOutCntr = 0x100000U;
            rxTimeOutCntr = 0x100000U;
            FSI_setTxBufferPtr(myFSITX0_BASE, 0U);
            FSI_setRxBufferPtr(myFSIRX0_BASE, 0U);
        }
    }

    //
    // Coming out of infinite while loop means timeout occurred for one of Tx
    // or Rx transmit/receive events. Debug further to root-cause
    //
    ESTOP0;
}

//
// prepareTxBufData - Update array which is used as source to Tx data buffer
//
void prepareTxBufData(void)
{
    uint16_t i;

    for(i = 0; i < myFSITX0_nWords; i++)
    {
        txBufData[i] = txBufData[i] + 1;
    }
}

//
// fsiTxInt1ISR - FSI Tx Interrupt on INsT1 line
//
void fsiTxInt1ISR(void)
{
    fsiTxInt1Received = 1U;

    txEventSts = FSI_getTxEventStatus(myFSITX0_BASE);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(myFSITX0_BASE, FSI_TX_EVTMASK);
}

//
// fsiTxInt2ISR - FSI Tx Interrupt on INT2 line
//
void fsiTxInt2ISR(void)
{
    fsiTxInt2Received = 1U;

    txEventSts = FSI_getTxEventStatus(myFSITX0_BASE);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(myFSITX0_BASE, FSI_TX_EVTMASK);
    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Actual Error
    // is captured in txEventSts for debug
    //
    ESTOP0;
}

//
// fsiRxInt1ISR - FSI Rx Interrupt on INT1 line
//
void fsiRxInt1ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(myFSIRX0_BASE);

    fsiRxInt1Received = 1U;
    dataFrameCntr++;

    //
    // Verify Frame attributes and data
    //
    checkReceivedFrameTypeTag(FSI_FRAME_TYPE_NWORD_DATA, txDataFrameTag);
    compare16(FSI_getRxUserDefinedData(myFSIRX0_BASE), txUserData);
    compareBufData(0, 0, myFSIRX0_nWords);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(myFSIRX0_BASE, rxEventSts);

    //
    // Stop execution if errors encountered in frame verification
    //
    if(error != 0)
    {
        disableAllFSIInterrupts();

        //
        // INT2 line is set to fire for error events, stop immediately. Error
        // is captured in rxEventSts for debug
        //
        ESTOP0;
    }
}

//
// fsiRxInt2ISR - FSI Rx Interrupt on INT2 line
//
void fsiRxInt2ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(myFSIRX0_BASE);

    fsiRxInt2Received = fsiRxInt2Received + 1U;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(myFSIRX0_BASE, rxEventSts);
    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Error
    // is captured in rxEventSts for debug
    //
    ESTOP0;
}

//
// disableAllFSIInterrupts - Disables all event interrupts in both FSI Tx/Rx,
//                           also clear them
//
void disableAllFSIInterrupts(void)
{
    FSI_disableTxInterrupt(myFSITX0_BASE, FSI_INT1, FSI_TX_EVTMASK);
    FSI_disableTxInterrupt(myFSITX0_BASE, FSI_INT2, FSI_TX_EVTMASK);
    FSI_disableRxInterrupt(myFSIRX0_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(myFSIRX0_BASE, FSI_INT2, FSI_RX_EVTMASK);

    FSI_clearTxEvents(myFSITX0_BASE, FSI_TX_EVTMASK);
    FSI_clearRxEvents(myFSIRX0_BASE, FSI_RX_EVTMASK);
}

//
// compare16 - Compares two 16 bit values and increments global error flag by 1
//             for mismatch
//
static inline void compare16(uint16_t val1, uint16_t val2)
{
    if(val1 != val2)
    {
        error++;
    }
}

//
// compareBufData - Compares if received data is same as transmitted ones
//                  It doesn't consider wrap-up cases, but, can be enhanced
//
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords)
{
    uint16_t i;
    uint16_t rxDataArray[16];

    FSI_readRxBuffer(myFSIRX0_BASE, rxDataArray, nWords, rxBufIndex);

    for(i = 0; i < nWords; i++)
    {
        if(rxDataArray[i] != txBufAddr[txBufIndex])
        {
            error++;
            return;
        }

        txBufIndex++;
    }
}

//
// checkReceivedFrameTypeTag - Checks received frame type/tag and updates global
//                             error flag
//
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag)
{
    compare16((uint16_t)FSI_getRxFrameType(myFSIRX0_BASE), (uint16_t)type);

    if(type == FSI_FRAME_TYPE_PING)
    {
        compare16(FSI_getRxPingTag(myFSIRX0_BASE), (uint16_t)tag);
    }
    else
    {
        compare16(FSI_getRxFrameTag(myFSIRX0_BASE), (uint16_t)tag);
    }
}

//
// End of File
//
