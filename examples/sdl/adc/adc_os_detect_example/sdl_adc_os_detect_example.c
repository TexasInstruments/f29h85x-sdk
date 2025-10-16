/*
 *  \file     sdl_adc_os_detect_example.c
 *
 *  \brief    SDL ADC Open/Short Detection test example
 *
 *  \details  SDL example demonstrating how to test the integrity of an ADC
 *            signal using the ADC's OSDETECT feature.
 *
 *  Copyright (C) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include "board.h"

#include <kernel/dpl/DebugP.h>
#include <include/sdl_types.h>

/*===========================================================================*/
/*                            Defines                                        */
/*===========================================================================*/

#define FULL_SCALE              0
#define SEVENbyTWELVE_SCALE     1
#define FIVEbyTWELVE_SCALE      2
#define ZERO_SCALE              3
#define NUMBER_OF_MEASUREMENTS  4

#define OSDETECT_SETTLING_2US (((((float64_t)2.0) / ((float64_t)1000000.0 / (float64_t)DEVICE_SYSCLK_FREQ)) - \
                                (float64_t)11.0) / (float64_t)4.0)

/*===========================================================================*/
/*                        Type definitions                                   */
/*===========================================================================*/

typedef struct
{
    uint32_t adcBase;           /* Base address of ADC instance to test */
    uint32_t adcResBase;        /* Corresponding base address of ADC results */
    ADC_ClkPrescale prescale;   /* Prescale on ADCCLK */
    ADC_Resolution resolution;  /* ADC resolution (12 or 16-bit) */
    ADC_SignalMode signalMode;  /* Single or differential  */
} SDL_ADC_Config;

typedef struct
{
    ADC_Channel adcInputChannel;    /* ADC channel number */
    uint32_t sampleWindow;          /* ACQPS value */
    uint32_t settlingTime;          /* Time between OSDETECT setting and conversion */
    /* Expected results for full, 7/12, 5/12, and zero scale */
    uint16_t expectedResults[NUMBER_OF_MEASUREMENTS];
    uint16_t allowedError;          /* Allowed ADC result deviation */
} SDL_ADC_ChannelOSTest;

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

/*
 * Initialize ADC instance
 */
void initADC(SDL_ADC_Config *adcConfig)
{
    ADC_setPrescaler(adcConfig->adcBase, adcConfig->prescale);
    ADC_setMode(adcConfig->adcBase, adcConfig->resolution, adcConfig->signalMode);
    ADC_setInterruptPulseMode(adcConfig->adcBase, ADC_PULSE_END_OF_CONV);
    ADC_enableConverter(adcConfig->adcBase);

    /* ADC requires time to power on */
    DEVICE_DELAY_US(5000);

    ADC_enableInterrupt(adcConfig->adcBase, ADC_INT_NUMBER1);
    ADC_disableContinuousMode(adcConfig->adcBase, ADC_INT_NUMBER1);
    ADC_setInterruptSource(adcConfig->adcBase, ADC_INT_NUMBER1, ADC_INT_TRIGGER_EOC0);
    ADC_setInterruptSOCTrigger(adcConfig->adcBase, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
}

/*
 * For the specified ADC channel, walk through ADC OSDETECT circuit settings and measure results.
 */
int32_t testADCOpenShort(SDL_ADC_Config *adcConfig, SDL_ADC_ChannelOSTest *channelConfig)
{
    int32_t retVal = SDL_PASS;
    int16_t resError, testIndex;
    uint16_t testResults[NUMBER_OF_MEASUREMENTS] = {0, 0, 0, 0};

    ADC_setupSOC(adcConfig->adcBase, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY,
                 channelConfig->adcInputChannel, channelConfig->sampleWindow);

    /*
     * Test full scale
     */
    ADC_configOSDetectMode(adcConfig->adcBase, ADC_OSDETECT_MODE_VDDA);
    SysCtl_delay(channelConfig->settlingTime);
    ADC_clearInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1);
    ADC_forceSOC(adcConfig->adcBase, ADC_SOC_NUMBER0);
    while(!ADC_getInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1))
    {
        ; /* Wait for conversion to complete */
    }
    testResults[FULL_SCALE] = ADC_readResult(adcConfig->adcResBase, ADC_SOC_NUMBER0);

    /*
     * Test 7/12 scale
     */
    ADC_configOSDetectMode(adcConfig->adcBase, ADC_OSDETECT_MODE_7BY12_VDDA);
    SysCtl_delay(channelConfig->settlingTime);
    ADC_clearInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1);
    ADC_forceSOC(adcConfig->adcBase, ADC_SOC_NUMBER0);
    while(!ADC_getInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1))
    {
        ; /* Wait for conversion to complete */
    }
    testResults[SEVENbyTWELVE_SCALE] = ADC_readResult(adcConfig->adcResBase, ADC_SOC_NUMBER0);

    /*
     * Test 5/12 scale
     */
    ADC_configOSDetectMode(adcConfig->adcBase, ADC_OSDETECT_MODE_5BY12_VDDA);
    SysCtl_delay(channelConfig->settlingTime);
    ADC_clearInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1);
    ADC_forceSOC(adcConfig->adcBase, ADC_SOC_NUMBER0);
    while(!ADC_getInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1))
    {
        ; /* Wait for conversion to complete */
    }
    testResults[FIVEbyTWELVE_SCALE] = ADC_readResult(adcConfig->adcResBase, ADC_SOC_NUMBER0);

    /*
     * Test zero scale
     */
    ADC_configOSDetectMode(adcConfig->adcBase, ADC_OSDETECT_MODE_VSSA);
    SysCtl_delay(channelConfig->settlingTime);
    ADC_clearInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1);
    ADC_forceSOC(adcConfig->adcBase, ADC_SOC_NUMBER0);
    while(!ADC_getInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1))
    {
        ; /* Wait for conversion to complete */
    }
    testResults[ZERO_SCALE] = ADC_readResult(adcConfig->adcResBase, ADC_SOC_NUMBER0);

    ADC_configOSDetectMode(adcConfig->adcBase, ADC_OSDETECT_MODE_DISABLED);

    /*
     * Check the results against the expected values
     */
    for(testIndex = 0U; testIndex < NUMBER_OF_MEASUREMENTS; testIndex++)
    {
        resError = channelConfig->expectedResults[testIndex] - testResults[testIndex];
        if(__builtin_c29_i32_abs32_d(resError) > channelConfig->allowedError)
        {
            retVal = SDL_EFAIL;
            break;
        }
    }

    return(retVal);
}

int main(void)
{
    int16_t retVal;
    SDL_ADC_Config adcConfig;
    SDL_ADC_ChannelOSTest adcChannel;

    /*
     * Initialize device clock, peripheral clocks and interrupts
     */
    Device_init();

    /*
     * Board Initialization
     */
    Board_init();

    /*
     * Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
     */
    ENINT;
    Interrupt_enableGlobal();

    DebugP_log("\n ADC OSDETECT Example Test Application\r\n");

    /*
     * Configure ADCA
     */
    adcConfig.adcBase = ADCA_BASE;
    adcConfig.adcResBase = ADCARESULT_BASE;
    adcConfig.prescale = ADC_CLK_DIV_4_0;
    adcConfig.resolution = ADC_RESOLUTION_12BIT;
    adcConfig.signalMode = ADC_MODE_SINGLE_ENDED;

    initADC(&adcConfig);

    /*
     * Test ADCINA0
     *
     * Note that a larger than usual sample window is required for OS detect
     * testing because of high drive impedance. See TRM for more details. This
     * example uses the largest possible window, but you may be able to use a
     * shorter one. See the SysConfig Sample Time Calculator.
     */
    adcChannel.sampleWindow = 512;

    adcChannel.adcInputChannel = ADC_CH_ADCIN0;
    adcChannel.settlingTime = OSDETECT_SETTLING_2US;

    /*
     * Expected results will vary based on your system hardware. For this
     * example, we are testing with a SOM and the ADC pins are not connected to
     * anything. Also note that the OSDETECT divider resistance tolerances can
     * vary widely, so this should not serve as a test of conversion accuracy,
     * and the allowedError should be large enough to handle this variance.
     */
    adcChannel.expectedResults[FULL_SCALE] = 4095;
    adcChannel.expectedResults[SEVENbyTWELVE_SCALE] = 2500;
    adcChannel.expectedResults[FIVEbyTWELVE_SCALE] = 1800;
    adcChannel.expectedResults[ZERO_SCALE] = 0;
    adcChannel.allowedError = 100;

    retVal = testADCOpenShort(&adcConfig, &adcChannel);

    if (retVal == SDL_PASS)
    {
        DebugP_log("   ADCINA0 Passed\r\n");
    }
    else
    {
        DebugP_log("   ADCINA0 Failed\r\n");
    }

    /*
     * Test ADCINA1
     */
    if (retVal == SDL_PASS)
    {
        adcChannel.sampleWindow = 512;

        adcChannel.adcInputChannel = ADC_CH_ADCIN1;
        adcChannel.settlingTime = OSDETECT_SETTLING_2US;

        adcChannel.expectedResults[FULL_SCALE] = 4095;
        adcChannel.expectedResults[SEVENbyTWELVE_SCALE] = 2500;
        adcChannel.expectedResults[FIVEbyTWELVE_SCALE] = 1800;
        adcChannel.expectedResults[ZERO_SCALE] = 0;
        adcChannel.allowedError = 100;

        retVal = testADCOpenShort(&adcConfig, &adcChannel);

        if (retVal == SDL_PASS)
        {
            DebugP_log("   ADCINA1 Passed\r\n");
        }
        else
        {
            DebugP_log("   ADCINA1 Failed\r\n");
        }
    }

    /*
     * Configure ADCB
     */
    if (retVal == SDL_PASS)
    {
        adcConfig.adcBase = ADCB_BASE;
        adcConfig.adcResBase = ADCBRESULT_BASE;
        adcConfig.prescale = ADC_CLK_DIV_4_0;
        adcConfig.resolution = ADC_RESOLUTION_12BIT;
        adcConfig.signalMode = ADC_MODE_SINGLE_ENDED;

        initADC(&adcConfig);

        /*
        * Test ADCINB2
        */
        adcChannel.sampleWindow = 512;

        adcChannel.adcInputChannel = ADC_CH_ADCIN2;
        adcChannel.settlingTime = OSDETECT_SETTLING_2US;

        adcChannel.expectedResults[FULL_SCALE] = 4095;
        adcChannel.expectedResults[SEVENbyTWELVE_SCALE] = 2500;
        adcChannel.expectedResults[FIVEbyTWELVE_SCALE] = 1800;
        adcChannel.expectedResults[ZERO_SCALE] = 0;
        adcChannel.allowedError = 100;

        retVal = testADCOpenShort(&adcConfig, &adcChannel);

        if (retVal == SDL_PASS)
        {
            DebugP_log("   ADCINB2 Passed\r\n");
        }
        else
        {
            DebugP_log("   ADCINB2 Failed\r\n");
        }
    }

    /*
     * Configure ADCC
     */
    if (retVal == SDL_PASS)
    {
        adcConfig.adcBase = ADCC_BASE;
        adcConfig.adcResBase = ADCCRESULT_BASE;
        adcConfig.prescale = ADC_CLK_DIV_4_0;
        adcConfig.resolution = ADC_RESOLUTION_12BIT;
        adcConfig.signalMode = ADC_MODE_SINGLE_ENDED;

        initADC(&adcConfig);

        /*
        * Test ADCINC12
        */
        adcChannel.sampleWindow = 512;

        adcChannel.adcInputChannel = ADC_CH_ADCIN12;
        adcChannel.settlingTime = OSDETECT_SETTLING_2US;

        adcChannel.expectedResults[FULL_SCALE] = 4095;
        adcChannel.expectedResults[SEVENbyTWELVE_SCALE] = 2500;
        adcChannel.expectedResults[FIVEbyTWELVE_SCALE] = 1800;
        adcChannel.expectedResults[ZERO_SCALE] = 0;
        adcChannel.allowedError = 100;

        retVal = testADCOpenShort(&adcConfig, &adcChannel);

        if (retVal == SDL_PASS)
        {
            DebugP_log("   ADCINC12 Passed\r\n");
        }
        else
        {
            DebugP_log("   ADCINC12 Failed\r\n");
        }
    }

    if (retVal == SDL_PASS)
    {
        DebugP_log("All tests have passed.\r\n");
    }
    else
    {
        DebugP_log("Few/all tests Failed \r\n");
    }

    while(1)
    {
        ;
    }
}

/* Nothing past this point */