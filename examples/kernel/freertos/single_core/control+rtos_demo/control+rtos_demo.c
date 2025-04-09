//#############################################################################
//
// FILE:   control_rtos_demo.c
//
// TITLE:   Control + RTOS application demo
//
//!  This example implements a control application running alongside FreeRTOS
//!  tasks, in order to demonstrate C29x performance and interrupt latencies.
//!  Control app. : EPWM with varying duty cycles, operating on RTINT
//!  RTOS app.  : FreeRTOS with multiple tasks, operating on INT
//!  Profiling of RTINT and INT performance is done through ERAD module,
//!  for which configuration is done using bitfield structures, and runtime
//!  modifications using C29x driverlib functions. GPIOs can be probed to
//!  visualize the interrupt switching patterns and latencies
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - RTINT_latency_max - Max # cycles b/w RTINT event and start of EPWM ISR
//!  - RTINT_latency_min - Min # cycles b/w RTINT event and start of EPWM ISR
//!  - INT_latency_max - Max # cycles b/w INT event and start of Timer ISR
//!  - INT_latency_min - Max # cycles b/w INT event and start of Timer ISR
//!
//
//#############################################################################

//
// Included Files
//
#include "board.h"
#include "c2000_freertos.h"
#include "bitfield_structs.h"

//
// Defines
//
#define EPWM1_TIMER_TBPRD  1000U
#define EPWM1_MAX_CMPA      950U
#define EPWM1_MIN_CMPA       50U
#define EPWM1_MAX_CMPB      950U
#define EPWM1_MIN_CMPB       50U

#define EPWM_CMP_UP           1U
#define EPWM_CMP_DOWN         0U

//
// Globals
//
typedef struct
{
    uint32_t epwmModule;
    uint16_t epwmCompADirection;
    uint16_t epwmCompBDirection;
    uint16_t epwmTimerIntCount;
    uint16_t epwmMaxCompA;
    uint16_t epwmMinCompA;
    uint16_t epwmMaxCompB;
    uint16_t epwmMinCompB;
}epwmInformation;

//
// Globals to hold the information used in this demo
//
epwmInformation epwm1Info;
volatile uint16_t epwm1Interrupt=0;

uint32_t RTINT_latency_max=0,RTINT_latency_min=0xFFFF;
uint32_t INT_latency_max=0,INT_latency_min=0xFFFF;
volatile uint32_t Task1_count, Task2_count, semaphore_timer_counter;

ERAD_BusComp_Config buscomp1_params, buscomp2_params;
ERAD_Counter_Config counter1_params, counter2_params;

//
// Function Prototypes
//
void initEPWM1(void);
void updateCompare(epwmInformation *epwmInfo);

//-------------------------------------------------------------------------------------------------

void EradSetup()
{
    //
    // Set the ownership of the modules as APPLICATION
    //
    ERAD_setBusCompOwnership(ERAD_BUSCOMP7, ERAD_OWNER_APPLICATION);
    ERAD_setBusCompOwnership(ERAD_BUSCOMP6, ERAD_OWNER_APPLICATION);
    ERAD_setCounterOwnership(ERAD_COUNTER1, ERAD_OWNER_APPLICATION);
    ERAD_setCounterOwnership(ERAD_COUNTER2, ERAD_OWNER_APPLICATION);

    //
    // Disable the modules
    //
    ERAD_disableBusCompModule(ERAD_BUSCOMP7);
    ERAD_disableBusCompModule(ERAD_BUSCOMP6);

    ERAD_disableCounterModule(ERAD_COUNTER1);
    ERAD_disableCounterModule(ERAD_COUNTER2);

    //
    // Clear any previous events
    //
    ERAD_clearBusCompEvent(ERAD_BUSCOMP7);
    ERAD_clearBusCompEvent(ERAD_BUSCOMP6);

    //
    // Clear any previous events and overflow
    //
    ERAD_clearCounterEvent(ERAD_COUNTER1);
    ERAD_clearCounterOverflow(ERAD_COUNTER1);

    ERAD_clearCounterEvent(ERAD_COUNTER2);
    ERAD_clearCounterOverflow(ERAD_COUNTER2);

    //
    // Configure the first bus comparator
    // No interrupt or CPU halt. Compare for equality. No mask.
    // Reference is 1st read instruction in the Timer ISR
    //
    buscomp1_params.bus_sel = ERAD_BUSCOMP_BUS_DRAB_W;
    buscomp1_params.comp_mode = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp1_params.enable_stop = 0;
    buscomp1_params.enable_int = 0;
    buscomp1_params.enable_nmi = 0;
    buscomp1_params.mask = 0x0;
    buscomp1_params.enable_stack_qual = 0;
    buscomp1_params.enable_spsel_match = 0;
    buscomp1_params.reference = (uint32_t)&semaphore_timer_counter;
    ERAD_configBusComp(ERAD_BUSCOMP7, &buscomp1_params);

    //
    // Configure the second bus comparator
    // No interrupt or CPU halt. Compare for equality. No mask.
    // Reference is 1st read instruction in the EPWM ISR
    //
    buscomp2_params.bus_sel = ERAD_BUSCOMP_BUS_DRAB_W;
    buscomp2_params.comp_mode = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp2_params.enable_stop = 0;
    buscomp2_params.enable_int = 0;
    buscomp2_params.enable_nmi = 0;
    buscomp2_params.mask = 0x0;
    buscomp2_params.enable_stack_qual = 0;
    buscomp2_params.enable_spsel_match = 0;
    buscomp2_params.reference = (uint32_t)&epwm1Interrupt;
    ERAD_configBusComp(ERAD_BUSCOMP6, &buscomp2_params);

    //
    // Configure the first counter
    // No interrupt, no CPU halt, no reset on match, no reference.
    // Counting the number of CPU cycles
    // Start event is the Timer Interrupt event
    // Stop event is the first EBC
    //
    counter1_params.enable_int = 0;
    counter1_params.enable_nmi = 0;
    counter1_params.enable_stop = 0;
    counter1_params.rst_on_match = 0;
    counter1_params.reference = 0xFFFFFFFF;
    counter1_params.event_mode = ERAD_COUNTER_MODE_ACTIVE;
    counter1_params.event = ERAD_EVENT_NO_EVENT;
    ERAD_Counter_Input_Event start1 = ERAD_EVENT_CPU1_TIMER0_INT;
    ERAD_Counter_Input_Event stop1 = (ERAD_Counter_Input_Event)ERAD_BUSCOMP7;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER1, &counter1_params, start1, stop1);

    //
    // Configure the second counter
    // No interrupt, no CPU halt, no reset on match, no reference.
    // Counting the number of CPU cycles
    // Start event is the RTINT event
    // Stop event is the second EBC
    //
    counter2_params.enable_int = 0;
    counter2_params.enable_nmi = 0;
    counter2_params.enable_stop = 0;
    counter2_params.rst_on_match = 0;
    counter2_params.reference = 0xFFFFFFFF;
    counter2_params.event_mode = ERAD_COUNTER_MODE_ACTIVE;
    counter2_params.event = ERAD_EVENT_NO_EVENT;
    ERAD_Counter_Input_Event start2 = ERAD_EVENT_PIPE_RTINT;
    ERAD_Counter_Input_Event stop2 = (ERAD_Counter_Input_Event) ERAD_BUSCOMP6;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER2, &counter2_params, start2, stop2);

    //
    // Enable the modules
    //
    ERAD_enableBusCompModule(ERAD_BUSCOMP7);
    ERAD_enableBusCompModule(ERAD_BUSCOMP6);

    ERAD_enableCounterModule(ERAD_COUNTER1);
    ERAD_enableCounterModule(ERAD_COUNTER2);
}

//-------------------------------------------------------------------------------------------------

void Task1(void * pvParameters)
{
    for(;;)
    {
        GPIO_togglePin(myGPIOTask1);
        Task1_count++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

//-------------------------------------------------------------------------------------------------

void Task2(void * pvParameters)
{
    for(;;)
    {
        GPIO_togglePin(myGPIOTask2);
        if(xSemaphoreTake( binarySemaphore0Handle, portMAX_DELAY ) == pdTRUE)
        {
            Task2_count++;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void Task3(void * pvParameters)
{
    EradSetup();

    for(;;)
    {
        GPIO_togglePin(myGPIOTask3);

        INT_latency_max =  ERAD_getMaxCount(ERAD_COUNTER1);
        INT_latency_min =  ERAD_getMinCount(ERAD_COUNTER1);

        RTINT_latency_max =  ERAD_getMaxCount(ERAD_COUNTER2);
        RTINT_latency_min =  ERAD_getMinCount(ERAD_COUNTER2);
    }
}

//-------------------------------------------------------------------------------------------------

void timer1_ISR( void )
{
    semaphore_timer_counter++;

    if(semaphore_timer_counter == 1){
        ERAD_setMaxCount(ERAD_COUNTER1, 0x0);
        ERAD_setMinCount(ERAD_COUNTER1, 0xFFFFFFFF);
    }

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR( binarySemaphore0Handle, &xHigherPriorityTaskWoken );

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_EPWM1);

    epwm1Interrupt = 0;

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Board initialization
    //
    Board_init();

    Interrupt_enableGlobal();

    //
    // EPWM initialization
    //
    initEPWM1();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // FreeRTOS initialization
    //
    FreeRTOS_init();

    //
    // Queue, Mutex and Semaphore objects must be added to registry
    // in order to view in ROV
    //
    vQueueAddToRegistry( binarySemaphore0Handle, "binary-sem" );
    vQueueSetQueueNumber( binarySemaphore0Handle, 0xa1a2a3a4 );

    vTaskStartScheduler();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    ENINT;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        __asm(" NOP #1");
    }
}

//
// epwm1ISR - ePWM 1 ISR
//
void epwm1ISR(void)
{
    epwm1Interrupt++;

    // Start of ISR
    GPIO_togglePin(myGPIOisrRTINT);

    //
    // Update the CMPA and CMPB values
    //
    updateCompare(&epwm1Info);

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

    // End of ISR
    GPIO_togglePin(myGPIOisrRTINT);
}


//
// initEPWM1 - Configure ePWM1
//
void initEPWM1()
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct ePWM registers
    //
    epwm1Info.epwmCompADirection = EPWM_CMP_UP;
    epwm1Info.epwmCompBDirection = EPWM_CMP_DOWN;
    epwm1Info.epwmTimerIntCount = 0U;
    epwm1Info.epwmModule = myEPWM1_BASE;
    epwm1Info.epwmMaxCompA = EPWM1_MAX_CMPA;
    epwm1Info.epwmMinCompA = EPWM1_MIN_CMPA;
    epwm1Info.epwmMaxCompB = EPWM1_MAX_CMPB;
    epwm1Info.epwmMinCompB = EPWM1_MIN_CMPB;
}


//
// updateCompare - Function to update the frequency
//
void updateCompare(epwmInformation *epwmInfo)
{
    uint16_t compAValue;
    uint16_t compBValue;

    compAValue = EPWM_getCounterCompareValue(epwmInfo->epwmModule,
                                             EPWM_COUNTER_COMPARE_A);

    compBValue = EPWM_getCounterCompareValue(epwmInfo->epwmModule,
                                             EPWM_COUNTER_COMPARE_B);

    //
    //  Change the CMPA/CMPB values every 10th interrupt.
    //
    if(epwmInfo->epwmTimerIntCount == 5U)
    {
        epwmInfo->epwmTimerIntCount = 0U;

        //
        // If we were increasing CMPA, check to see if we reached the max
        // value. If not, increase CMPA else, change directions and decrease
        // CMPA
        //
        if(epwmInfo->epwmCompADirection == EPWM_CMP_UP)
        {
            if(compAValue < (epwmInfo->epwmMaxCompA))
            {
                compAValue+=10;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_A,
                                            compAValue);
            }
            else
            {
                compAValue-=10;
                epwmInfo->epwmCompADirection = EPWM_CMP_DOWN;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_A,
                                            compAValue);
            }
        }
        //
        // If we were decreasing CMPA, check to see if we reached the min
        // value. If not, decrease CMPA else, change directions and increase
        // CMPA
        //
        else
        {
            if( compAValue == (epwmInfo->epwmMinCompA))
            {
                compAValue+=10;
                epwmInfo->epwmCompADirection = EPWM_CMP_UP;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_A,
                                            compAValue);
            }
            else
            {
                compAValue-=10;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_A,
                                            compAValue);
            }
        }

        //
        // If we were increasing CMPB, check to see if we reached the max
        // value. If not, increase CMPB else, change directions and decrease
        // CMPB
        //
        if(epwmInfo->epwmCompBDirection == EPWM_CMP_UP)
        {
            if(compBValue < (epwmInfo->epwmMaxCompB))
            {
                compBValue+=10;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            compBValue);
            }
            else
            {
                compBValue-=10;
                epwmInfo->epwmCompBDirection = EPWM_CMP_DOWN;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            compBValue);
            }
        }
        //
        // If we were decreasing CMPB, check to see if we reached the min
        // value. If not, decrease CMPB else, change directions and increase
        // CMPB
        //
        else
        {
            if(compBValue == (epwmInfo->epwmMinCompB))
            {
                compBValue+=10;
                epwmInfo->epwmCompBDirection = EPWM_CMP_UP;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            compBValue);
            }
            else
            {
                compBValue-=10;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            compBValue);
            }
        }
    }
    else
    {
        epwmInfo->epwmTimerIntCount++;
    }
}
