//#############################################################################
//
// FILE:   erad_ex1_profile_function_no_syscfg.c
//
// TITLE:  ERAD Profile Function.
//
//! \addtogroup driver_example_list
//! <h1>ERAD Profile Function</h1>
//!
//!  This example uses BUSCOMP7, BUSCOMP6 and COUNTER0 of the ERAD module to
//!  profile a function (delayFunction). It calculates the CPU cycles taken
//!  between the the start address of the function to the end address of the
//!  function
//!
//!  Two dummy variable are written to inside the function - startCount and
//!  endCount. BUSCOMP5, BUSCOMP4 and COUNTER1 are used to profile the time
//!  taken between the access to startCount variable till the access to
//!  endCount variable.
//!
//!  Both the counters are setup to operate in START-STOP mode and count the
//!  number of CPU cycles spend between the respective bus comparator events.
//!
//!  Note: The Enhanced Bus Comparator (EBC) modules are used in the
//!  decreasing order of their instances in this example. This is because, in
//!  FLASH configuration/ when hardware breakpoints are used while debugging,
//!  the first few ERAD EBCs are owned by the Debugger and are blocked for the
//!  application to use.
//!
//!  \b Watch \b Variables \n
//!   - cycles_Function_Max - the maximum number of cycles between the start 
//!                           of function to the end of function
//!   - cycles_Function_Min - the minimum number of cycles between the start 
//!                           of function to the end of function
//!   - cycles_Data_Max     - the maximum number of cycles taken between
//!                           accessing startCount variable to endCount 
//!                           variable
//!   - cycles_Data_Min     - the minimum number of cycles taken between
//!                           accessing startCount variable to endCount 
//!                           variable
//!
//! \b External \b Connections \n
//!  None
//
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Global Variables
//

//
// Start and end address of the function delayFunction.
// This value comes from the linker command file.
//
extern uint32_t delayFuncStart, delayFuncEnd;

//
// The variables used in the function which are monitored by bus comparators
// 3 and 4.
//
volatile uint32_t startCount = 0;
volatile uint32_t endCount = 0;

//
// Watch variables with the number of CPU cycles elapsed.
//
volatile uint32_t cycles_Function_Max = 0;
volatile uint32_t cycles_Function_Min = 0xFFFFFFFF;
volatile uint32_t cycles_Data_Max = 0;
volatile uint32_t cycles_Data_Min = 0xFFFFFFFF;

ERAD_Profile_Params params;

//
// Function Prototypes
//
__attribute__ ((section(".delayFunc"), noinline))
void delayFunction(uint16_t);

//
// Main
//
int main(void)
{
    uint16_t i;

    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Parameters for profiling function.
    // The PC value is being monitored here.
    //
    params.start_address = (uint32_t)&delayFuncStart;
    params.end_address   = (uint32_t)&delayFuncEnd - 2U;
    params.bus_sel       = ERAD_BUSCOMP_BUS_VPC_I_ALIGNED;
    params.busComp_instance1 = ERAD_BUSCOMP7;
    params.busComp_instance2 = ERAD_BUSCOMP6;
    params.counter_instance  = ERAD_COUNTER0;

    //
    // Configuring the required ERAD submodules
    //
    ERAD_profile(params);

    //
    // Parameters for profiling the time between the accesses
    // to startCount and endCount variables.
    // The address in the Data Write Address Bus is monitored here.
    //
    params.start_address = (uint32_t)&startCount;
    params.end_address   = (uint32_t)&endCount;
    params.bus_sel       = ERAD_BUSCOMP_BUS_DWAB;
    params.busComp_instance1 = ERAD_BUSCOMP5;
    params.busComp_instance2 = ERAD_BUSCOMP4;
    params.counter_instance  = ERAD_COUNTER1;

    //
    // Configuring the required ERAD submodules
    //
    ERAD_profile(params);

    //
    // Loop to call the delay function repeatedly with different delays
    //
    for(i=0; i<10; i++)
    {
        delayFunction(i % 5);

        //
        // View these variables in CCS view
        // Note that calling the function ERAD_getCurrentValue here will
        // return 0 since the stop events have already been occurred.
        //
        cycles_Function_Max = ERAD_getMaxCount(ERAD_COUNTER0);
        cycles_Data_Max     = ERAD_getMaxCount(ERAD_COUNTER1);

        cycles_Function_Min = ERAD_getMinCount(ERAD_COUNTER0);
        cycles_Data_Min     = ERAD_getMinCount(ERAD_COUNTER1);

        ESTOP0;

        //
        // Uncomment the code below to clear the maximum and minimum count
        //
        // ERAD_setMaxCount(ERAD_COUNTER0, 0);
        // ERAD_setMaxCount(ERAD_COUNTER1, 0);
        // ERAD_setMinCount(ERAD_COUNTER0, 0xFFFFFFFF);
        // ERAD_setMinCount(ERAD_COUNTER1, 0xFFFFFFFF);
    }

    ESTOP0;
    while(1);
}

//
// Delay function
//
void delayFunction(uint16_t delay)
{
    startCount++;

    uint16_t i = 0;
    for (; i < delay; i++)
    {
        NOP;
        NOP;
        NOP;
        NOP;
    }

    endCount++;
}

//
// End of File
//
