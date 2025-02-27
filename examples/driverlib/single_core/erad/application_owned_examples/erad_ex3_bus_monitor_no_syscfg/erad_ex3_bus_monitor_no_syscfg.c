//#############################################################################
//
// FILE:   erad_ex3_bus_monitor_no_syscfg.c
//
// TITLE:  ERAD Monitoring instruction and data address buses.
//
//! \addtogroup driver_example_list
//! <h1>ERAD Bus Comparator Monitor Program Counter</h1>
//!
//!  In this example, the function delayFunction is called multiple times.
//!  The function does read and writes to the global variables startCount and
//!  endCount.
//!
//!  The BUSCOMP7 and COUNTER0 is used to count the number of times the function
//!  delayFunction was invoked. BUSCOMP6 is used to generate an interrupt when
//!  there is read access to the startCount variable and BUSCOMP5 is used to
//!  generate an interrupt when there is a write access to the endCount variable
//!
//!  Note: The Enhanced Bus Comparator (EBC) modules are used in the
//!  decreasing order of their instances in this example. This is because, in
//!  FLASH configuration/ when hardware breakpoints are used while debugging,
//!  the first few ERAD EBCs are owned by the Debugger and are blocked for the
//!  application to use.
//!
//!  \b Watch \b Variables \n
//!  - funcCount - number of times the function delayFunction was invoked
//!  - isrCount  - number of times the ISR was invoked
//!
//! \b External \b Connections \n
//!  - None
//
//#############################################################################

//
//Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Globals
//
uint32_t isrCount = 0;
uint32_t funcCount = 0;
volatile uint32_t startCount, endCount;

//
// Function prototypes
//
__attribute__((interrupt("INT"))) void INT_myERAD_ISR(void);
__attribute__((noinline)) void delayFunction();

//
// Main
//
int main(void)
{
    ERAD_AddressHit_Params addr_params;
    int i;

    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Initializes PIPE control registers
    //
    Interrupt_initModule();

    //
    // Initializes the PIPE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    Interrupt_Config cfg ={
        .enable        = true,
        .priority      = 40,
        .linkOwner     = SSU_LINK2,
        .contextID     = INTERRUPT_CONTEXT_AGNOSTIC,
        .apiLinkID     = SSU_API_DISABLE
    };

    cfg.handler = &INT_myERAD_ISR;
    Interrupt_configChannel(INT_ERAD, cfg);

    //
    // Set the threshold for RTINT.
    // The ERAD interrupt is configured as normal interrupt
    //
    Interrupt_setThreshold(20);

    Interrupt_setINTSP(SSU_STACK2);

    //
    // Configure BUSCOMP7 and COUNTER0 to count the number of times the
    // delayFunction was invoked.
    // The PC value is being monitored here.
    //
    addr_params.address = (uint32_t)&delayFunction;
    addr_params.mask    = 0x0;
    addr_params.bus_sel = ERAD_BUSCOMP_BUS_VPC_I_ALIGNED;
    ERAD_countAddressHits(&addr_params, ERAD_BUSCOMP7, ERAD_COUNTER0);

    //
    // Configure BUSCOMP6 to generate an interrupt when the startCount variable
    // is read.
    // The Data Read Address Bus is being monitored here.
    //
    addr_params.address = (uint32_t)&startCount;
    addr_params.mask    = 0x0;
    addr_params.bus_sel = ERAD_BUSCOMP_BUS_DRAB_W;
    ERAD_enableInterruptOnAddressHit(&addr_params, ERAD_BUSCOMP6);

    //
    // Configure BUSCOMP5 to generate an interrupt when the endCount variable
    // is written.
    // The Data Write Address Bus is being monitored here.
    //
    addr_params.address = (uint32_t)&endCount;
    addr_params.mask    = 0x0;
    addr_params.bus_sel = ERAD_BUSCOMP_BUS_DWAB;
    ERAD_enableInterruptOnAddressHit(&addr_params, ERAD_BUSCOMP5);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();;

    //
    // Loop to call the delay function multiple times
    //
    for(i = 0; i < 10; i++)
    {
        //
        // Call the delay function
        //
        delayFunction();

        //
        // Get the current count of COUNTER0 to get the number of times
        // function delayFunction was invoked
        //
        funcCount = ERAD_getCurrentCount(ERAD_COUNTER0);
    }

    ESTOP0;
    while(1);
}

//
// delay function
//
void delayFunction()
{
    uint32_t temp = startCount;
    startCount = temp + 1;

    uint16_t i=0;
    for (; i<100; i++)
    {
        NOP;
    }

    endCount = temp + 1;
}


//
// ISR to be executed on interrupt generation
// Program will halt at this ESTOP0
//
void INT_myERAD_ISR(void)
{
    //
    // Indicate that the ISR was executed
    //
    isrCount++;

    if(ERAD_getBusCompStatus(ERAD_BUSCOMP6) == ERAD_STATE_COMPLETED)
    {
        //
        // ISR was raised because of BUSCOMP6 - Read to startCount variable
        //
        ESTOP0;
       	ERAD_clearBusCompEvent(ERAD_BUSCOMP6);
    }
    if(ERAD_getBusCompStatus(ERAD_BUSCOMP5) == ERAD_STATE_COMPLETED)
    {
        //
        // ISR was raised because of BUSCOMP5 - Write to endCount variable
        //
        ESTOP0;
       	ERAD_clearBusCompEvent(ERAD_BUSCOMP5);
    }

}