//#############################################################################
//
// FILE:   freertos_amp_cpu1_cpu3_multi_c29x1.c
//
// TITLE:  FreeRTOS Asymmetric Multi-Processing example
//! <h1> FreeRTOS Asymmetric Multi-Processing example </h1>
//! 
//! This example implements a simple Asymmetric Multi Processing (AMP) core to
//! core communication mechanism implemented using FreeRTOS message buffers.
//! Message buffers are used to pass data from a single 'sending' task that
//! runs on CPU1 to two 'receiving' tasks running on CPU3. There are two data
//! message buffers, one for each receiving task.  To distinguish between the
//! receiving tasks one is assigned the task no. 0, and the other task no. 1.
//!
//! This example only has two data message buffers, so it would be reasonable
//! to have the ISR simply query both to see which contains data. However this
//! technique is inefficient if there are a large or unknown number of message
//! buffers. Therefore, this example introduces a third message buffer - a
//! 'control' message buffer as opposed to a 'data' message buffer.  After
//! the task on CPU1 writes to a data message buffer it writes the handle of
//! the message buffer that contains data to the control message buffer.  The
//! ISR running on CPU3 then reads from the control message buffer to know
//! which data message buffer contains data.
//!
//! Note: sbSEND_COMPLETED() and sbRECEIVE_COMPLETED() macros are implemented
//! in the respective FreeRTOSConfig.h files on the relevant core
//!
//! When using CCS for debugging this Multi-core example, after launching the
//! debug session,
//!     - Connect to CPU1 and load only the c29x1.out.
//!     - After the program is loaded, run CPU1.
//!     - Once c29x1 configures and releases CPU3 out of reset, the program
//!     stops.
//!     - Connect to CPU3 target now. c29x3.out would have started execution
//!     as soon as it is released from reset.
//!     - In case of RAM configuration, restart the CPU3 target and load the
//!     symbols.
//!
//! \note For FLASH configuration, this example is run in FLASH BANKMODE2,
//! where CPU3 has access to FLASH (FRI-2). Refer to the Flash Plugin
//! documentation to know about changing FLASH BANKMODEs and more.
//! Additionally, the CPAx and CDAx RAMs are used for allocating various
//! RAM sections.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - taskReceive1_count - # times Receive Task 1 has received data from its
//!    message buffer
//!  - taskReceive2_count - # times Receive Task 2 has received data from its
//!    message buffer
//!  - interrupt_Count - # times IPC interrupt has been triggered because of
//!    CPU1 send task writing to one of the Data message buffers
//!
//
//#############################################################################

//
// Included Files
//
#include "board.h"
#include "c2000_freertos.h"
#include "MessageBufferLocations.h"

//
// Fetching static Message Buffer storage elements from predefined locations
//
uint32_t *xControlMessageBufferPointer = 
(uint32_t*)(CONTROL_BUFFER_HANDLE_ADDR);
MessageBufferHandle_t *xDataMessageBuffers = 
(MessageBufferHandle_t *)(DATA_BUFFERS_HANDLE_ADDR);

//
// Globals
//
volatile uint32_t taskReceive1_count = 0, taskReceive2_count = 0;
volatile uint32_t interrupt_Count = 0;

//
// Receiving Task - Reads from the appropriate message buffer
//
void task_receive( void * pvParameters){
    
    size_t xReceivedBytes;
    //
    // Task parameter is used to pass in a task number, which is then used as
    // an index into the message buffer array
    //
    BaseType_t xTaskNumber = ( BaseType_t ) pvParameters;

    uint8_t nextValue = 0x1;
    uint8_t receivedData = 0xFF;

    for(;;){
        //
        // Wait to receive the next message from send task on CPU1
        //
        xReceivedBytes = 
        xMessageBufferReceive( /* Handle of message buffer */
                                xDataMessageBuffers[ xTaskNumber ],
                                /* Buffer into which received data is placed */
                                (void *) &receivedData,
                                /* Size of the receive buffer */
                                sizeof( receivedData ),
                                /* Time to wait for data to arrive */
                                portMAX_DELAY );

		/* Check the number of bytes received was as expected. */
		configASSERT( xReceivedBytes == sizeof( nextValue ) );

        if(receivedData == nextValue){
            if(xTaskNumber == 0){
                taskReceive1_count++;
            }
            else if(xTaskNumber == 1){
                taskReceive2_count++;
            }
        }
        else{
            ESTOP0;
        }

        //
        // Increment expected data for next transmission
        //     
        nextValue++;
    }
}


//
// Main
//
int main(void)
{
    //
    // Interrupt initialization
    //
    Device_init();
    
    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG_ALL);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable
    // for the CPU
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG31);

    //
    // Initialize FreeRTOS kernel and start scheduler
    //
    FreeRTOS_init();

    //
    // Idle loop. Should not reach.
    //
    while(1);
}

//
// Interrupt triggered after CPU1 send task writes to one of the data
// buffers, and passes the handle in the control buffer
//
void ipcInterrupt_fromCPU1(){
    
    MessageBufferHandle_t xUpdatedMessageBuffer;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    size_t xReturned;

    interrupt_Count++;

    configASSERT( 
        ( (MessageBufferHandle_t)(*xControlMessageBufferPointer) != NULL )
            && ( xDataMessageBuffers[ 0 ] != NULL )
            && ( xDataMessageBuffers[ 1 ] != NULL ) );

    //
    // Receive the handle of the message buffer that contains data from the
	// control message buffer
    //
    while (xMessageBufferReceiveFromISR(   
            (MessageBufferHandle_t) (*xControlMessageBufferPointer),
            (void *) &xUpdatedMessageBuffer,
            sizeof( xUpdatedMessageBuffer ),
            &xHigherPriorityTaskWoken ) == sizeof( xUpdatedMessageBuffer ))
    {
        //
        // Sends a notification to any task that is blocked on
        // xUpdatedMessageBuffer message buffer waiting for data to arrive
        //
        xMessageBufferSendCompletedFromISR( 
            xUpdatedMessageBuffer, &xHigherPriorityTaskWoken );
    }

    //
    //  Resolve IPC interrupt
    //
    IPC_ackFlagRtoL(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG0);
    Interrupt_clearFlag(INT_IPC_1_1);
                                            
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

//
// Generate IPC interrupt in CPU1 when Data Message Buffer read is completed
//
void generateCpu1Interrupt( void * xUpdatedMessageBuffer ){
    IPC_setFlagLtoR(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG0);
}