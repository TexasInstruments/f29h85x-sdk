//-------------------------------------------------------------------------------------------------
// Scheduler includes.
//-------------------------------------------------------------------------------------------------
#include "FreeRTOS.h"
#include "task.h"

#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #if ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.
    #endif
#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

//-------------------------------------------------------------------------------------------------
// Implementation of functions defined in portable.h for the C29x port.
//-------------------------------------------------------------------------------------------------

// Constants required for hardware setup.
#define portINITIAL_CRITICAL_NESTING  ( ( uint16_t ) 10 )
#define portFLAGS_INT_ENABLED         ( ( StackType_t ) 0x010000 )  //DSTS LP INT ENABLE 

// Register descriptions of C29 Architecture
#define A_REGISTERS 16 //Address pointers
#define D_REGISTERS 16 //Fixed point registers
#define M_REGISTERS 32 //Floating point registers
#define A4_REGISTER_POSITION    4U

void vPortSetupTimerInterrupt( void );
void vPortSetupSWInterrupt( void );

// Each task maintains a count of the critical section nesting depth.  Each
// time a critical section is entered the count is incremented.  Each time a
// critical section is exited the count is decremented - with interrupts only
// being re-enabled if the count is zero.
//
// ulCriticalNesting will get set to zero when the scheduler starts, but must
// not be initialised to zero as this will cause problems during the startup
// sequence.
// ulCriticalNesting should be 32 bit value to keep stack alignment unchanged.
volatile uint32_t ulCriticalNesting = portINITIAL_CRITICAL_NESTING;
volatile uint16_t bYield = 0;
volatile uint16_t bPreemptive = 0;

// Saved as part of the task context, off be default. Set to pdTRUE if task
// requires FPU.
uint32_t ulTaskHasFPUContext = 0;

//-------------------------------------------------------------------------------------------------
// Initialise the stack of a task to look exactly as if
// timer interrupt was executed.
//-------------------------------------------------------------------------------------------------
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
    uint16_t i;
    uint16_t base = 0;
    pxTopOfStack[base] = (uint32_t)vPortEndScheduler; base+=1;  // Alignment
    pxTopOfStack[base] = 0x07F90001; base+=1;  // Alignment , DSTS if RETI
    pxTopOfStack[base]  = 0xABABABAB; base+=1; // A14
    pxTopOfStack[base] = ((uint32_t)pxCode) & 0xFFFFFFFEU;
    base+=1;      //RPC or PC (first task) after return
    pxTopOfStack[base]  = 0x07F90001; base+=1; // DSTS
    pxTopOfStack[base]  = 0x00020101; base+=1; // ESTS

    // Fill the rest of the registers with dummy values.
    for(i = 0; i <= (A_REGISTERS + D_REGISTERS -2 -1); i++)
    {
        uint32_t value  = 0xDEADDEAD;

        /* Function parameters are passed in A4. */
        if(i == A4_REGISTER_POSITION)
        {
            value = (uint32_t)pvParameters;
        }
        pxTopOfStack[base + i] = value;
    }
    base += i ;

    // Initially not saving FPU registers
    pxTopOfStack[base] = pdFALSE; base+=1;  //FPU context
    base+=1; // Alignment

    // Return a pointer to the top of the stack we have generated so this can
    // be stored in the task control block for the task.
    return pxTopOfStack + base;
}

//-------------------------------------------------------------------------------------------------
void vPortEndScheduler( void )
{
    // It is unlikely that the TMS320 port will get stopped.
    // If required simply disable the tick interrupt here.
}

//-------------------------------------------------------------------------------------------------
// See header file for description.
//-------------------------------------------------------------------------------------------------
BaseType_t xPortStartScheduler(void)
{
    vPortSetupTimerInterrupt();
    vPortSetupSWInterrupt();

    ulCriticalNesting = 0;

#if(configUSE_PREEMPTION == 1)
    bPreemptive = 1;
#else
    bPreemptive = 0;
#endif

    portENABLE_INTERRUPTS();
    portRESTORE_FIRST_CONTEXT();

    // Should not get here!
    return pdFAIL;
}

//-------------------------------------------------------------------------------------------------
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" variables. The "freq" is
// CPU frequency in Hz and the period in uSeconds. The timer is held in
// the stopped state after configuration.
//

void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);
}


//-------------------------------------------------------------------------------------------------
void vPortSetupTimerInterrupt( void )
{
    // Start the timer than activate timer interrupt to switch into first task.
    Interrupt_register(INT_TIMER2, &portTICK_ISR);

    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFF);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0);
    CPUTimer_stopTimer(CPUTIMER2_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);

    configCPUTimer(CPUTIMER2_BASE, configCPU_CLOCK_HZ, 1000000 / configTICK_RATE_HZ);

    CPUTimer_enableInterrupt(CPUTIMER2_BASE);

    Interrupt_enable(INT_TIMER2);
    CPUTimer_startTimer(CPUTIMER2_BASE);
}

//-------------------------------------------------------------------------------------------------
void vPortSetupSWInterrupt( void )
{
    Interrupt_enable(INT_SW1);
    Interrupt_register(INT_SW1, &vPortYield);
}

//-------------------------------------------------------------------------------------------------
void vPortEnterCritical( void )
{
    portDISABLE_INTERRUPTS();
    ulCriticalNesting++;
}

//-------------------------------------------------------------------------------------------------
void vPortExitCritical( void )
{
    ulCriticalNesting--;
    if( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}

//-------------------------------------------------------------------------------------------------
void vPortTaskUsesFPU( void )
{
    ulTaskHasFPUContext = pdTRUE;
}
