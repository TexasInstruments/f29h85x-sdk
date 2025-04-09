#include "board.h"
#include "c2000_freertos.h"

//
// Function prototypes
//
void task_comms(void * pvParameters);
void INT_SPI_Receive_ISR(void);
void INT_Hi_Prio_SWINT_ISR(void);
