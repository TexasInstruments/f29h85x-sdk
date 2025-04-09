/* Fixed locations to place message buffer elements */

#define CONTROL_BUFFER_HANDLE_ADDR  (0x20130000)
#define DATA_BUFFERS_HANDLE_ADDR    (0x20130004)

#define CONTROL_BUFFER_STRUCT_ADDR  (0x20130050)
#define DATA_BUFFERS_STRUCT_ADDR    (0x201300A0)

#define CONTROL_BUFFER_STORAGE_ADDR (0x20130100)
#define DATA_BUFFERS_STORAGE_ADDR   (0x20130500)


/* Storage sizes for message buffer, accounting for 1-byte length field */
#define TASK_MESSAGE_BUFFER_SIZE    ( 80 )

#define CONTROL_MESSAGE_BUFFER_SIZE ( 60 )

/* The number of instances of CPU3 that are created. */
#define NUMBER_OF_CPU3_TASKS	    2

/* A block time of 0 simply means, don't block. */
#define mbaDONT_BLOCK				0
