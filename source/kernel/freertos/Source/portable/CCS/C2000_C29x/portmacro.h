#ifndef PORTMACRO_H
#define PORTMACRO_H

#include "interrupt.h"

//-------------------------------------------------------------------------------------------------
// Port specific definitions.
//
// The settings in this file configure FreeRTOS correctly for the
// given hardware and compiler.
//
// These settings should not be altered.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Hardware includes
//-------------------------------------------------------------------------------------------------
#include "cputimer.h"

//-------------------------------------------------------------------------------------------------
// Type definitions.
//-------------------------------------------------------------------------------------------------
#define portCHAR        uint8_t
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        uint32_t
#define portSHORT       uint16_t
#define portBASE_TYPE   long
#define portSTACK_TYPE  uint32_t

typedef portSTACK_TYPE StackType_t;
typedef int32_t          BaseType_t;
typedef uint32_t         UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
  typedef uint16_t TickType_t;
  #define portMAX_DELAY ( TickType_t ) 0xffff
#else
  typedef uint32_t TickType_t;
  #define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#endif

//-------------------------------------------------------------------------------------------------
// Interrupt control macros.
//-------------------------------------------------------------------------------------------------
#define portDISABLE_INTERRUPTS()  __asm__(" DISINT")
#define portENABLE_INTERRUPTS()   __asm__(" ENINT")

static inline UBaseType_t portSET_INTERRUPT_MASK_FROM_ISR()
{
   volatile UBaseType_t dsts;
   __asm__(" ST.32 *(A15-#8), DSTS");
   __asm__(" DISINT");
   return ( ( dsts >> 16 ) & 1 );
}
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    if( x ) __asm__(" ENINT") //enable only if x is set

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
before any floating point instructions are executed. */
void vPortTaskUsesFPU( void );

//-------------------------------------------------------------------------------------------------
// Architecture specific optimisations.
//-------------------------------------------------------------------------------------------------
#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities )    uxTopPriority = ( 31 - __builtin_c29_i32_clzeros_d( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

//-------------------------------------------------------------------------------------------------
// Critical section control macros.
//-------------------------------------------------------------------------------------------------
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );
#define portENTER_CRITICAL()  vPortEnterCritical()
#define portEXIT_CRITICAL()   vPortExitCritical()

//-------------------------------------------------------------------------------------------------
// Task utilities.
//-------------------------------------------------------------------------------------------------
#define portYIELD()                 {Interrupt_force(INT_SW1); asm(" NOP #8"); asm(" NOP #5");}
#define portYIELD_FROM_ISR( x )     if( x ) portYIELD()

extern void portTICK_ISR( void );
extern void vPortYield( void );
extern void portRESTORE_FIRST_CONTEXT( void );
extern void vTaskSwitchContext( void );
extern volatile uint16_t bYield;

//-------------------------------------------------------------------------------------------------
// Hardware specifics.
//-------------------------------------------------------------------------------------------------
#define portBYTE_ALIGNMENT      8
#define portSTACK_GROWTH        ( 1 )
#define portTICK_PERIOD_MS      ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()               __asm(" NOP")

//-------------------------------------------------------------------------------------------------
// Task function macros as described on the FreeRTOS.org WEB site.
//-------------------------------------------------------------------------------------------------
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )

#endif /* PORTMACRO_H */
