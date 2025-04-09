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
//!  - taskSend_count - # times Send Task has written to ALL message buffers
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
// Defines
//
#ifdef _FLASH
    #define CPU3_RESET_VECTOR   0x10401000U
    #define CPU3_NMI_VECTOR     0x10401040U
#else
    #define CPU3_RESET_VECTOR   0x20110000U
    #define CPU3_NMI_VECTOR     0x20110040U
#endif

//
// Placing Message Buffer static elements at predefined locations
//
__attribute__((location(CONTROL_BUFFER_HANDLE_ADDR)))
static MessageBufferHandle_t xControlMessageBuffer;
__attribute__((location(DATA_BUFFERS_HANDLE_ADDR)))
static MessageBufferHandle_t xDataMessageBuffers[ NUMBER_OF_CPU3_TASKS ];


__attribute__((location(CONTROL_BUFFER_STRUCT_ADDR)))
static StaticStreamBuffer_t xControlMessageBufferStruct;
__attribute__((location(DATA_BUFFERS_STRUCT_ADDR)))
static StaticStreamBuffer_t xDataMessageBufferStructs[NUMBER_OF_CPU3_TASKS];


__attribute__((location(CONTROL_BUFFER_STORAGE_ADDR), aligned(8)))
static uint8_t 
ucControlBufferStorage[ CONTROL_MESSAGE_BUFFER_SIZE ];
__attribute__((location(DATA_BUFFERS_STORAGE_ADDR), aligned(8)))
static uint8_t 
ucDataBufferStorage[NUMBER_OF_CPU3_TASKS][ TASK_MESSAGE_BUFFER_SIZE ];

//
// Globals
//
volatile uint32_t taskSend_count = 0;

//
// Sending Task - Writes a message to each buffer in the array
//
void task_send( void * pvParameters){
    
    BaseType_t x;
    const TickType_t xShortDelay = pdMS_TO_TICKS(100);

    uint8_t nextMessage = 1;

    for(;;){

        for( x = 0; x < NUMBER_OF_CPU3_TASKS; x++ )
		{
            //
            // This task uses the message buffers to send messages to the tasks
            // running on CPU3.  This will result in sbSEND_COMPLETED() being
            // executed, which in turn will write the handle of the message
            // buffer written to into xControlMessageBuffer then generate an
            // interrupt on CPU3
            //
			while(( xMessageBufferSend  (xDataMessageBuffers[x],
                                        ( void * ) &nextMessage,
                                        sizeof( nextMessage ),
                                        portMAX_DELAY )) 
                                        != sizeof(nextMessage))
            {
                ;
            }
		}

        taskSend_count++;
        vTaskDelay(xShortDelay);

        //
        // Increment message for next transmission
        //        
        nextMessage++;
    }
}

//
// Main
//
int main(void)
{
    int i;
    BaseType_t x;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Defines the address at which CPU3 Boots
    //
    SSU_configBootAddress(SSU_CPU3, (uint32_t)CPU3_RESET_VECTOR, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU3, CPU3_NMI_VECTOR, SSU_LINK2);

    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU3, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU3Reset() == 0x1U);

    //
    // CPU3 is out of reset now. Connect to CPU3 and load the symbols.
    //
    ESTOP0;

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG_ALL);

    //
    // Initialize control and data message buffers
    //
    xControlMessageBuffer =
    xMessageBufferCreateStatic( CONTROL_MESSAGE_BUFFER_SIZE,
                                ucControlBufferStorage,
                                &xControlMessageBufferStruct );
	
    for( x = 0; x < NUMBER_OF_CPU3_TASKS; x++ )
	{
		xDataMessageBuffers[ x ] =
        xMessageBufferCreateStatic( TASK_MESSAGE_BUFFER_SIZE,
                                    &( ucDataBufferStorage[ x ][ 0 ] ),
                                    &( xDataMessageBufferStructs[ x ] ));
	}

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG31);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable
    // for the CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

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
// Interrupt triggered after either of the CPU3 receive tasks has finished
// reading from its Data message buffer
//
void ipcInterrupt_fromCPU3(){

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t x;

	//
    // Task can't be blocked on both so just send the notification to both
    //
	for( x = 0; x < NUMBER_OF_CPU3_TASKS; x++ )
	{
		xMessageBufferReceiveCompletedFromISR( 
            xDataMessageBuffers[ x ], 
            &xHigherPriorityTaskWoken );
	}

    //
    //  Resolve IPC interrupt
    //  
    IPC_ackFlagRtoL(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG0);
    Interrupt_clearFlag(INT_IPC_2_1);
                                       
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

//
// Generate IPC interrupt in CPU3 when Data Message Buffer send is completed
//
void generateCpu3Interrupt( void * xUpdatedMessageBuffer ){

    MessageBufferHandle_t xUpdatedBuffer =
    ( MessageBufferHandle_t ) xUpdatedMessageBuffer;

    //
    // Write the handle of the data message buffer to which data was written
    // to the control message buffer
    //
	if( xUpdatedBuffer != xControlMessageBuffer )
	{
        //
        // Send the handle of the updated buffer in Control Message Buffer
        //
		while (xMessageBufferSend( 
                xControlMessageBuffer,
                (void *) &xUpdatedBuffer,
                sizeof( xUpdatedBuffer ),
                mbaDONT_BLOCK ) != sizeof( xUpdatedBuffer ));
        
        //
        // Generate CPU3 interrupt
        //
		IPC_setFlagLtoR(IPC_CPU1_L_CPU3_R_CH0, IPC_FLAG0);
	}
}