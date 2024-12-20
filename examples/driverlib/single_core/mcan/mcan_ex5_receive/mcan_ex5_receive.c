//#############################################################################
//
// FILE:   mcan_ex5_receive.c
//
// TITLE:  MCAN receive using Rx Buffer
//
//! \addtogroup driver_example_list
//! <h1> MCAN receive using Rx Buffer </h1>
//!
//! This example demonstrates the MCAN receive function. Communication is done
//! between two CAN nodes. The transmitting node could be another MCU or a
//! CAN bus analysis tool capable of transmitting CAN FD frames. The transmit
//! and receive pins of the MCAN module should be connected to a CAN
//! transceiver. Nominal Bit Rate of 1 mbps & Data bit rate of 2 Mbps is used
//!
//! Only Standard frame with message ID 0x4 is received.
//!
//! If another C2000 MCU is used as the transmitter, mcan_ex4_transmit.c can be
//! run on it for the transmit function.
//!
//! NOTE -  Select XTAL clock source by doing the following change in device.h file:
//!         #define USE_PLL_SRC_XTAL
//!         //#define USE_PLL_SRC_INTOSC
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!
//! \b External \b Connections \n
//!   Both nodes should communicate through CAN FD capable transceivers.
//!
//!  - MCAN is on GPIO_65_MCANA_RX (MCANRXA)
//!  - and GPIO_64_MCANA_TX (MCANTXA)
//!
//! \b Watch \b Variables \n
//!  - rxMsg
//!
//
//#############################################################################

//
// Include Files
//
#include "inc/stw_types.h"
#include "device.h"
#include "driverlib.h"

//
// Defines.
//
#define NUM_OF_MSG                      (1U)
#define MCAN_STD_ID_FILTER_NUM          (1U)
#define MCAN_EXT_ID_FILTER_NUM          (0U)
#define MCAN_FIFO_0_NUM                 (0U)
#define MCAN_FIFO_0_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_FIFO_1_NUM                 (0U)
#define MCAN_FIFO_1_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_RX_BUFF_NUM                (10U)
#define MCAN_RX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_BUFF_SIZE               (0U)
#define MCAN_TX_FQ_SIZE                 (0U)
#define MCAN_TX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_EVENT_SIZE              (0U)

//
//  Defining Starting Addresses for Message RAM Sections,
//  (Calculated from Macros based on User defined configuration above)
//
#define MCAN_STD_ID_FILT_START_ADDR     (0x0U)
#define MCAN_EXT_ID_FILT_START_ADDR     (MCAN_STD_ID_FILT_START_ADDR + ((MCAN_STD_ID_FILTER_NUM * MCANSS_STD_ID_FILTER_SIZE_WORDS * 4U)))
#define MCAN_FIFO_0_START_ADDR          (MCAN_EXT_ID_FILT_START_ADDR + ((MCAN_EXT_ID_FILTER_NUM * MCANSS_EXT_ID_FILTER_SIZE_WORDS * 4U)))
#define MCAN_FIFO_1_START_ADDR          (MCAN_FIFO_0_START_ADDR + (MCAN_getMsgObjSize(MCAN_FIFO_0_ELEM_SIZE) * 4U * MCAN_FIFO_0_NUM))
#define MCAN_RX_BUFF_START_ADDR         (MCAN_FIFO_1_START_ADDR + (MCAN_getMsgObjSize(MCAN_FIFO_1_ELEM_SIZE) * 4U * MCAN_FIFO_1_NUM))
#define MCAN_TX_BUFF_START_ADDR         (MCAN_RX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_RX_BUFF_ELEM_SIZE) * 4U * MCAN_RX_BUFF_NUM))
#define MCAN_TX_EVENT_START_ADDR        (MCAN_TX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_TX_BUFF_ELEM_SIZE) * 4U * (MCAN_TX_BUFF_SIZE + MCAN_TX_FQ_SIZE)))

//
// Global Variables.
//
uint32_t            error = 0;
MCAN_RxBufElement   rxMsg[NUM_OF_MSG], rxMsg1;
uint32_t            loopCnt = 0U;

//
// Function Prototype.
//
static void MCANConfig(void);
static void MCANIntrConfig(void);
__attribute__((interrupt("INT"))) void MCANIntr1ISR(void);

int main(void)
{
    uint32_t    i = 0;
    uint32_t    dataBytes = 64;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and unlock the GPIO configuration registers
    //
    Device_initGPIO();

    //
    // Configure the divisor for the MCAN bit-clock
    // -> MCAN_CLOCK = SYSPLLCLK/10 = 200/10 = 20 MHz
    //
    SysCtl_setMCANClock(
                SYSCTL_MCAN_A,
                SYSCTL_MCANCLK_SOURCE_SYS,
                SYSCTL_MCANCLK_DIV_10);

    //
    // ISR Configuration.
    //
    MCANIntrConfig();

    //
    // Configure GPIO pins for MCANTX/MCANRX operation
    //
	GPIO_setPinConfig(GPIO_65_MCANA_RX);
	GPIO_setPadConfig(65, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(65, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(GPIO_64_MCANA_TX);
	GPIO_setPadConfig(64, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(64, GPIO_QUAL_ASYNC);

    //
    // Initialize message to receive
    //
    rxMsg[loopCnt].id   = 0U;
    rxMsg[loopCnt].rtr  = 0U;
    rxMsg[loopCnt].xtd  = 0U;
    rxMsg[loopCnt].esi  = 0U;
    rxMsg[loopCnt].rxts = 0U;   // Rx Timestamp
    rxMsg[loopCnt].dlc  = 0U;
    rxMsg[loopCnt].brs  = 0U;
    rxMsg[loopCnt].fdf  = 0U;
    rxMsg[loopCnt].fidx = 0U;   // Filter Index
                                // (of matching Rx acceptance filter element)
    rxMsg[loopCnt].anmf = 0U;   // Accepted Non-matching Frame

    for(i = 0; i < dataBytes; i++)  // Initialize receive buffer to 0
    {
        rxMsg[loopCnt].data[i]  = 0;
    }

    //
    // Configure the MCAN Module.
    //
    MCANConfig();

    //
    // Enable Interrupts.
    //
    MCAN_enableIntr(MCANA_DRIVER_BASE, MCAN_INTR_MASK_ALL, 1U);

    //
    // Select Interrupt Line.
    //
    MCAN_selectIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_MASK_ALL, MCAN_INTR_LINE_NUM_1);

    //
    // Enable Interrupt Line.
    //
    MCAN_enableIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_LINE_NUM_1, 1U);

    while(1)
    {
        //
        //  Adding delay of 1 second
        //
        DEVICE_DELAY_US(1000000);

        //
        //  Message Handling Code goes here
        //
    }

    //
    // Stop Application.
    //
    ESTOP0;
}

static void MCANConfig(void)
{
    MCAN_InitParams             initParams;
    MCAN_MsgRAMConfigParams     msgRAMConfigParams;
    MCAN_StdMsgIDFilterElement  stdFiltelem;
    MCAN_BitTimingParams        bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&stdFiltelem, 0, sizeof(stdFiltelem));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // Configure MCAN initialization parameters
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching enabled

    //
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.flssa                = MCAN_STD_ID_FILT_START_ADDR;
    // Standard ID Filter List Start Address.
    msgRAMConfigParams.lss                  = MCAN_STD_ID_FILTER_NUM;
    // List Size: Standard ID.
    msgRAMConfigParams.rxBufStartAddr       = MCAN_RX_BUFF_START_ADDR;
    // Rx Buffer Start Address.
    msgRAMConfigParams.rxBufElemSize        = MCAN_RX_BUFF_ELEM_SIZE;
    // Rx Buffer Element Size.

    //
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0x0U; // Standard Filter ID 2.
    // Configuring received frame to be stored in buffer element 0
    stdFiltelem.sfid1              = 0x4U; // Standard Filter ID 1.
    // Confifuring frames with msg ID = 0x4U to be accepted by filter element
    stdFiltelem.sfec               = 0x7U; // Store into Rx Buffer
                                           // configuration of SFT[1:0] ignored

    //
    // Initialize bit timings.
    // -> NOM_BITRATE = (MCAN_CLOCK/(bitTimes.nomRatePrescalar + 1))/(bitTimes.nomTimeSeg1 + bitTimes.nomTimeSeg2 + 3)
    //                = (20/(0 + 1))/(9 + 8 + 3) = 20/20 = 1 mbps
    // -> DAT_BITRATE = (MCAN_CLOCK/(bitTimes.dataRatePrescalar + 1))/(bitTimes.dataTimeSeg1 + bitTimes.dataTimeSeg2 + 3)
    //                = (20/(0 + 1))/(4 + 3 + 3) = 20/10 = 2 mbps
    //
    bitTimes.nomRatePrescalar   = 0x0U; // Nominal Baud Rate Pre-scaler
    bitTimes.nomTimeSeg1        = 0x9U; // Nominal Time segment before SP
    bitTimes.nomTimeSeg2        = 0x8U; // Nominal Time segment after SP
    bitTimes.nomSynchJumpWidth  = 0x8U; // Nominal SJW
    bitTimes.dataRatePrescalar  = 0x0U; // Data Baud Rate Pre-scaler
    bitTimes.dataTimeSeg1       = 0x4U; // Data Time segment before SP
    bitTimes.dataTimeSeg2       = 0x3U; // Data Time segment after SP
    bitTimes.dataSynchJumpWidth = 0x3U; // Data SJW

    //
    // Wait for memory initialization to happen.
    //
    while(FALSE == MCAN_isMemInitDone(MCANA_DRIVER_BASE))
    {
        ;
    }

    //
    // Put MCAN in SW initialization mode.
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_SW_INIT);

    //
    // Wait till MCAN is not initialized.
    //
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(MCANA_DRIVER_BASE))
    {
        ;
    }

    //
    // Initialize MCAN module.
    //
    MCAN_init(MCANA_DRIVER_BASE, &initParams);

    //
    // Configure Bit timings.
    //
    MCAN_setBitTime(MCANA_DRIVER_BASE, &bitTimes);

    //
    // Configure Message RAM Sections
    //
    MCAN_msgRAMConfig(MCANA_DRIVER_BASE, &msgRAMConfigParams);

    //
    // Configure Standard ID filter element
    //
    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 0U, &stdFiltelem);

    //
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_NORMAL);

    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCANA_DRIVER_BASE))
    {
        ;
    }
}

//
// This function will configure X-BAR for MCAN interrupts.
//
static void MCANIntrConfig(void)
{
    //
    // Set the threshold for RTINT.
    //
    Interrupt_setThreshold(20);

    //
    //  INT stack pointer setting
    //
    Interrupt_setINTSP(SSU_STACK2);

    Interrupt_register(INT_MCANA_1, &MCANIntr1ISR);
	Interrupt_enable(INT_MCANA_1);
	Interrupt_setPriority(INT_MCANA_1, 255);
	Interrupt_setContextID(INT_MCANA_1, INTERRUPT_CONTEXTID_0);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();
}

//
// This is Interrupt Service Routine for MCAN interrupt 1.
//
__attribute__((interrupt("INT"))) void MCANIntr1ISR(void)
{
    uint32_t intrStatus;
    MCAN_RxNewDataStatus newData;

    intrStatus = MCAN_getIntrStatus(MCANA_DRIVER_BASE);

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    //  Clearing the interrupt lineNum
    //
    MCAN_clearInterrupt(MCANA_DRIVER_BASE, 0x2);

    //
    //  Check to see if the interrupt is caused by a message being
    //  received in dedicated RX Buffers
    //
    if((MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG & intrStatus) == MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        //
        // Read the NewData registers
        //
        MCAN_getNewDataStatus(MCANA_DRIVER_BASE, &newData);

        //  If message is received in buffer element 0
        if((newData.statusLow & (1UL << 0U)) != 0)
        {
            MCAN_readMsgRam(
                    MCANA_DRIVER_BASE,
                    MCAN_MEM_TYPE_BUF,
                    0U,
                    0,
                    &rxMsg1);

            rxMsg[loopCnt] = rxMsg1;
        }

        //
        //  Clearing the NewData registers
        //
        MCAN_clearNewDataStatus(MCANA_DRIVER_BASE, &newData);
    }
    else
    {
        error++;

        //
        //  Interrupt handling for other interrupt sources goes here
        //
    }
}
