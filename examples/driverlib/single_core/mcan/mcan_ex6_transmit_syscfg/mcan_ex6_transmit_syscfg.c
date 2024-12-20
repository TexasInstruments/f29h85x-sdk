//#############################################################################
//
// FILE:   mcan_ex4_transmit.c
//
// TITLE:  MCAN External Transmit using Tx Buffer
//
//! \addtogroup driver_example_list
//! <h1> MCAN External Transmit using Tx Buffer </h1>
//!
//! This example demonstrates the MCAN External Transmit function. External
//! communication is done between two CAN nodes. The receiving node could be
//! another MCU or a CAN bus analysis tool capable of Receiving/ACKnowledging
//! transmitted frames. The transmit and receive pins of the MCAN module
//! should be connected to a CAN Transceiver. Nominal Bit Rate of 1 mbps and
//! Data bit rate of 2 Mbps is used.
//! Standard Identifier (STD ID) 0x4 is transmitted with 64 data bytes.
//! #defines that are not required for this test case have been commented out.
//! However, they have been left in the code should the scope of this code
//! be expanded to include Receive and FIFO functions.
//!
//! If another C2000 MCU is used as the receiver, mcan_ex5_receive.c can be
//! run on it for the receive function.
//!
//! NOTE -  Select XTAL clock source in the syscfg
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!
//! \b External \b Connections \n
//!  Both nodes should communicate through CAN FD capable transceivers.
//!
//!  - MCAN is on GPIO_65_MCANA_RX (MCANRXA)
//!  - and GPIO_64_MCANA_TX (MCANTXA)
//!
//! \b Watch \b Variables \n
//!  - txMsg
//!
//
//#############################################################################

//
// Include Files
//
#include "board.h"

//
//  main function
//
int main(void)
{
    MCAN_TxBufElement   txMsg;

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
        ;
    }

    //
    // Stop Application.
    //
    ESTOP0;
}
