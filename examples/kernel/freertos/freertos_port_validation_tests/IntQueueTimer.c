/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "IntQueueTimer.h"
#include "IntQueue.h"

/* Hardware includes. */
#include "device.h"
#include "cputimer.h"
#include "interrupt.h"

void configCPUTimer(uint32_t cpuTimer, float freq, float period);
void Timer1_Handler(void);

/*-----------------------------------------------------------*/

void vInitialiseTimerForIntQueueTest( void )
{
	/* Initialize a hardware timer. */
    Interrupt_register(INT_TIMER1, &Timer1_Handler);

    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);

    configCPUTimer(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ, 1000000 / 200);

    CPUTimer_enableInterrupt(CPUTIMER1_BASE);

    Interrupt_setPriority(INT_TIMER1, 10);
    Interrupt_enable(INT_TIMER1);
    CPUTimer_startTimer(CPUTIMER1_BASE);
}

/*-----------------------------------------------------------*/

__attribute__((interrupt("INT"))) void Timer1_Handler(void)
{
    IntQueueTestTimerHandler();
}

void IntQueueTestTimerHandler( void )
{
    portYIELD_FROM_ISR( xSecondTimerHandler() );
}
/*-----------------------------------------------------------*/