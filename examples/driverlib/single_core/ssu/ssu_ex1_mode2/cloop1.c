
//
// Included Files
//
#include "app.h"
#include <stdint.h>

uint32_t myADC0Result;
int adc_int_count = 0;

__attribute__((interrupt("RTINT"))) void INT_myADC0_1_ISR(void);

void INT_myADC0_1_ISR(void)
{
    adc_int_count++;

    myADC0Result = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    if (ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }
}

