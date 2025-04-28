//#############################################################################
//
// FILE:   erad_ex5_stack_overflow_detect_no_syscfg.c
//
// TITLE:  ERAD Bus Comparator Stack Overflow Detection.
//
//! \addtogroup driver_example_list
//! <h1>ERAD Bus Comparator Stack Overflow Detection</h1>
//!
//!  This example uses BUSCOMP7 to monitor the stack. The Bus comparator is
//!  set to monitor the data write access bus and generate an interrupt to
//!  CPU when a write is detected beyond the dedicated STACK.
//!  The example is built with optimization=O0 and might not function as
//!  intended with higher optimizations.
//!
//!  Note: The Enhanced Bus Comparator (EBC) modules are used in the
//!  decreasing order of their instances in this example. This is because, in
//!  FLASH configuration/ when hardware breakpoints are used while debugging,
//!  the first few ERAD EBCs are owned by the Debugger and are blocked for the
//!  application to use.
//!
//!  \b Watch \b Variables \n
//!  - functionCallCount - the number of times the recursive function
//!    overflowing the STACK is called.
//!  - x indicates that the ISR has been entered
//!
//! \b External \b Connections \n
//!  None
//
//#############################################################################

//
//Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Global Variables
//
volatile uint32_t functionCallCount = 0;
uint32_t x = 0;
volatile uint32_t dummyValue = 0;

//
// Function Prototypes
//
void INT_myERAD_ISR(void);
void recursiveFunction(uint32_t delay);
void ERAD_enableInterruptOnStackOverflow(ERAD_BusCompInstance instance);

//
// Main
//
int main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Initializes PIPE
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
    // Parameters for generating interrupt on a write access to the
    // threshold address
    //
    ERAD_AddressHit_Params addr_params;
    addr_params.bus_sel = ERAD_BUSCOMP_BUS_DWAB;

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;

    //
    // Sets up ERAD for stack overflow detection
    //
    ERAD_enableInterruptOnStackOverflow(ERAD_BUSCOMP7);

    Interrupt_enableGlobal();

    recursiveFunction(1);

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {

    }
}

void
ERAD_enableInterruptOnStackOverflow(ERAD_BusCompInstance instance)
{
    ERAD_BusComp_Config buscomp_params;

    //
    // Set the ownership of the modules as APPLICATION
    //
    ERAD_setBusCompOwnership(instance, ERAD_OWNER_APPLICATION);

    //
    // Disable the bus comparator
    //
    ERAD_disableBusCompModule(instance);

    //
    // Clear any previous events
    //
    ERAD_clearBusCompEvent(instance);

    //
    // Disable CPU halt
    // and enable Interrupt
    //
    buscomp_params.enable_stop = false;
    buscomp_params.enable_int = true;
    buscomp_params.enable_nmi = false;

    //
    // Comparison mode is set to greater than to
    // and the bus to be monitored is the
    // Data Write Address Bus
    //
    buscomp_params.reference = 0x200E0400; // End of stack address
    buscomp_params.mask = 0x0;
    buscomp_params.bus_sel = ERAD_BUSCOMP_BUS_DWAB;
    buscomp_params.comp_mode = ERAD_BUSCOMP_COMPMODE_GT;

    //
    // Configure the Stack qualification
    //
    buscomp_params.enable_stack_qual = true;

    //
    // Configure the Stack pointer select
    //
    buscomp_params.enable_spsel_match = false;
    buscomp_params.spsel = 0x0U;

    //
    // Configure the bus comparator
    //
    ERAD_configBusComp(instance, &buscomp_params);

    //
    // Enable the bus comparator
    //
    ERAD_enableBusCompModule(instance);
}

//
// Recursive function to fill the stack
//
void recursiveFunction(uint32_t delay)
{
    //
    // Reserves space on stack
    //
    uint32_t    buffer[100];
    uint32_t    clobber = delay;

    functionCallCount++;

    // The following lines are here just to give a meaning to
    // local variables, so that they aren't considered unused;
    // buffer[1] ... buffer[99] are untouched
    buffer[0] = functionCallCount + 1;
    dummyValue = clobber + buffer[0];

    //
    // Recursive function
    //
    recursiveFunction(delay + 1UL);
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
    x++;
    ESTOP0;
}

//
// End of File
//
