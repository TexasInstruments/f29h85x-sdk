/*
 *  \file     sdl_compdac_adc_loopback_example.c
 *
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

//
// Included Files
//
#include "board.h"

#include <kernel/dpl/DebugP.h>
#include <include/sdl_types.h>


/*===========================================================================*/
/*                            Defines                                        */
/*===========================================================================*/

#define COMPUTE_USDELAY(x) (((((float64_t)(x)) / ((float64_t)1000000.0 / (float64_t)DEVICE_SYSCLK_FREQ)) - \
                                (float64_t)11.0) / (float64_t)4.0)

#define DAC_RESOLUTION 6

#define COMPH          (0)
#define COMPL          (1)

/*===========================================================================*/
/*                        Type definitions                                   */
/*===========================================================================*/

typedef struct
{
    uint32_t cmpssInstance;         /* CMPSS instance number to test. Starting from 1 */
    uint32_t cmpssBase;             /* Base address of CMPSS instance to test */
    uint32_t comparatorSelection;   /* Comparator Side 0:HI, 1:LO */
} SDL_CMPSS_Config;

typedef struct
{
    uint32_t adcBase;               /* Base address of ADC instance to test */
    uint32_t adcResBase;            /* Corresponding base address of ADC results */
    ADC_ClkPrescale prescale;       /* Prescale on ADCCLK */
    ADC_Resolution resolution;      /* ADC resolution (12 or 16-bit) */
    ADC_SignalMode signalMode;      /* Single or differential  */
} SDL_ADC_Config;

typedef struct
{
    ADC_Channel adcInputChannel;    /* ADC channel number */
    uint32_t sampleWindow;          /* ACQPS value */
    uint32_t settlingTime;          /* Time between CompDAC code setting and ADC conversion start */

} SDL_ADC_ChannelConfig;

typedef struct
{
    uint32_t accumulation_count;     /* ADC accumulation count to average out noise */
    uint32_t expectedOffset;         /* 6-bit CompDAC output has an expected shift/offset of 32 LSBs*/
    uint32_t allowedOffsetError;     /* Allowed Offset Error in 12-bit LSBs */
    uint32_t allowedINLError;        /* Allowed INL Error in 12-bit LSBs */
    uint32_t allowedGainError;       /* Allowed Gain Error in 12-bit LSBs */
} SDL_Test_Config;



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

    /* Setup ADC Interrupts */
    ADC_enableInterrupt(adcConfig->adcBase, ADC_INT_NUMBER1);
    ADC_disableContinuousMode(adcConfig->adcBase, ADC_INT_NUMBER1);
    // Setup interrupt trigger for HW OverSampling (OSINT1)
    ADC_setInterruptSource(adcConfig->adcBase, ADC_INT_NUMBER1, ADC_INT_TRIGGER_OSINT1);
    ADC_setInterruptSOCTrigger(adcConfig->adcBase, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
}


/*
 *  Initializes the ADC repeater and PPB to accumulate results 
 */
void initADC_Accumulation(SDL_ADC_Config *adcConfig, uint16_t accumulation_count)
{
    ADC_RepeaterConfig RepConfig;
    RepConfig.repMode = ADC_REPMODE_OVERSAMPLING;
    RepConfig.repTrigger = ADC_TRIGGER_SW_ONLY;
    // Disable HW Sync for Repeater. Rely on SW Sync
    RepConfig.repSyncin = ADC_SYNCIN_DISABLE;
    
    RepConfig.repCount = accumulation_count - 1;
    RepConfig.repPhase = 0;
    RepConfig.repSpread = 0;

    /* Setup ADC Repeater and Post Processing Block for hardware accumulation */
    ADC_configureRepeater(adcConfig->adcBase, ADC_REPINST1, &RepConfig);
    
    ADC_setupPPB(adcConfig->adcBase, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setPPBCountLimit(adcConfig->adcBase, ADC_PPB_NUMBER1, accumulation_count);
    // Disable HW Sync for PPB. Rely on SW Sync
    ADC_selectPPBSyncInput(adcConfig->adcBase, ADC_PPB_NUMBER1, ADC_SYNCIN_DISABLE);
    
}

// Connects a specific compDAC output to INTERNAL_TEST node. comparatorInstance number assumed to start from 1.
void connectCompDACOUTtoInternalTest(uint16_t comparatorInstance, uint16_t comparatorSelection)
{
    // Determines which compDAC's output is connected to INTERNAL_TEST. See INTERNALTESTCTL register field descriptions in the TRM for more info
    uint16_t InternalTestCtlSelect;

    if(comparatorSelection == COMPH)             // high side compDAC
    {
        InternalTestCtlSelect = 5 + (comparatorInstance - 1) * 2;
    }
    else                                         // low side compDAC
    {
        InternalTestCtlSelect = 6 + (comparatorInstance - 1) * 2;
    }

    ASysCtl_selectInternalTestNode(InternalTestCtlSelect);

}

/*
 * Sweep CompDAC code and measure output with the ADC
 */
int32_t testCompDacAdcLoopback(SDL_CMPSS_Config *cmpssConfig, SDL_ADC_Config *adcConfig, SDL_ADC_ChannelConfig *channelConfig, SDL_Test_Config *testConfig)
{
    int32_t retVal = SDL_PASS;
    uint16_t testIndex, DACValue;
    float32_t ADCResult, resError, measOffsetErr;
    uint16_t DACValueIncrement = 1 << (12 - DAC_RESOLUTION);

    // Uncomment below for debug
    // float32_t adcResultArr[1 << DAC_RESOLUTION] = {0.0};
    
    initADC_Accumulation(adcConfig, testConfig->accumulation_count);


    ADC_setupSOC(adcConfig->adcBase, ADC_SOC_NUMBER0, ADC_TRIGGER_REPEATER1,
                 channelConfig->adcInputChannel, channelConfig->sampleWindow);


    
    connectCompDACOUTtoInternalTest(cmpssConfig->cmpssInstance, cmpssConfig->comparatorSelection);
    // Add an extended settling delay after closing switch because INTERNAL_TEST is a high impedance node
    SysCtl_delay(10*channelConfig->settlingTime);

    testIndex = 0;
    DACValue = 0;
    while(DACValue < 4096)
    {
        if(cmpssConfig->comparatorSelection == COMPH)
        {
            CMPSS_setDACValueHigh(cmpssConfig->cmpssBase, DACValue);
        }
        else
        {
            CMPSS_setDACValueLow(cmpssConfig->cmpssBase, DACValue);
        }
        SysCtl_delay(channelConfig->settlingTime);

        ADC_clearInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1);

        // Force Repeater and PPB Sync to clear out repeater and PPB registers
        ADC_forceRepeaterTriggerSync(adcConfig->adcBase, ADC_REPINST1);
        ADC_forcePPBSync(adcConfig->adcBase, ADC_PPB_NUMBER1);
        
        // Force Repeater trigger and commence ADC conversion with hardware accumulation
        ADC_forceRepeaterTrigger(adcConfig->adcBase, ADC_REPINST1);
        ADC_forceSOC(adcConfig->adcBase, ADC_SOC_NUMBER0);                                    // begin the ADC conversion

        while(!ADC_getInterruptStatus(adcConfig->adcBase, ADC_INT_NUMBER1)){}                 // wait for ADC conversion to finish
        // Read ADC result
        // NOTE: The repeater is limited to 128 total samples. If more averaging is required, then do interrupt ping ponging or software averaging.
        ADCResult = ADC_readPPBSum(adcConfig->adcResBase, ADC_PPB_NUMBER1);

        if(adcConfig->resolution==ADC_RESOLUTION_16BIT)
        {
            ADCResult = ADCResult/16;
        }
        ADCResult = ADCResult/testConfig->accumulation_count;

        // Uncomment below for debug
        // adcResultArr[testIndex] = ADCResult;    // store the ADC conversion results in the array
        
        resError = ADCResult - DACValue - testConfig->expectedOffset;

        if(DACValue == 0)
        {
            measOffsetErr = resError;
            if(__builtin_c29_i32_abs32_d(measOffsetErr) > testConfig->allowedOffsetError)
            {
                retVal = SDL_EFAIL;
                break;
            }

        }

        resError = resError - measOffsetErr;

        // Uncomment below for debug
        // adcResultArr[testIndex] = resError;     // store the ADC conversion residual errors in the array

        if(__builtin_c29_i32_abs32_d(resError) > testConfig->allowedINLError + ((float32_t)testConfig->allowedGainError/4095.0)*DACValue)
        {
            retVal = SDL_EFAIL;
            break;
        }

        testIndex = testIndex + 1;
        DACValue = DACValue + DACValueIncrement;
    }

    // Remove all connections to INTERNAL_TEST
    ASysCtl_selectInternalTestNode(ASYSCTL_TEST_NODE_NO_CONN);
    
    return(retVal);
}


//
// Main
//
int main(void)
{

    int16_t retVal;
    SDL_CMPSS_Config cmpssConfig;
    SDL_ADC_Config adcConfig;
    SDL_ADC_ChannelConfig adcChannelConfig;
    SDL_Test_Config testConfig;


    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board initialization
    // Configure ADC and CMPSS
    //
    /* ADC VREFHI has to be the same voltage as the CMPSS reference (VDDA/VDAC, which is usually 3.3V) 
     * for the loopback to work. Syscfg has been configured to use InternalRef 3.3V, 
     * but the user can change it to ExternalRef if VREFHI is connected to 3.3V on the board.
     * If VREFHI != VDDA/VDAC, then tweak testConfig.allowedGainError accordingly
     */
    Board_init();

    /*
     * Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
     */
    ENINT;
    Interrupt_enableGlobal();

    DebugP_log("\n CMPSS DAC - ADC Loopback Example Test Application\r\n");

    /*
     * Test CMPSS1H DAC - ADCA loopback
     */

    cmpssConfig.cmpssInstance = 1;
    cmpssConfig.cmpssBase = CMPSS1_BASE;
    cmpssConfig.comparatorSelection = COMPH;

    /*
     * Configure ADCA
     */
    adcConfig.adcBase = ADCA_BASE;
    adcConfig.adcResBase = ADCARESULT_BASE;
    adcConfig.prescale = ADC_CLK_DIV_4_0;
    adcConfig.resolution = ADC_RESOLUTION_12BIT;
    adcConfig.signalMode = ADC_MODE_SINGLE_ENDED;

    /*
     * Note that a larger than usual sample window is required for
     * testing because of high drive impedance. See the ADC Internal Test Mode section in the TRM for more details.
     * This example uses the largest possible window, but you may be able to use a
     * shorter one. See the SysConfig Sample Time Calculator.
     */
    adcChannelConfig.sampleWindow = 512;
    adcChannelConfig.adcInputChannel = ADC_CH_ADCIN16;   // Refer to Analog Subsystem Block Diagram in Datasheet for INTERNAL_TEST channels
    adcChannelConfig.settlingTime = COMPUTE_USDELAY(2);

    // Accumulation count might have to be changed based on expected noise and allowed error tolerance
    testConfig.accumulation_count = 4;
    // The 6-bit CompDAC output has an expected offset of 32LSBs
    testConfig.expectedOffset = 32;
    // Allowed error values below are currently set based on datasheet specs for CMPSS DACs + ADCs. Modify based on noise, reference voltage, etc.
    testConfig.allowedOffsetError = 34;
    testConfig.allowedINLError = 18;
    testConfig.allowedGainError = 90;

    initADC(&adcConfig);
    CMPSS_enableModule(cmpssConfig.cmpssBase);

    retVal = testCompDacAdcLoopback(&cmpssConfig, &adcConfig, &adcChannelConfig, &testConfig);

    // Optional: Disable ADC and CMPSS
    // CMPSS_disableModule(cmpssConfig->cmpssBase);
    // ADC_disableConverter(adcConfig->adcBase);

    if (retVal == SDL_PASS)
    {
        DebugP_log("   CMPSS1H DAC - ADCA loopback Passed\r\n");
    }
    else
    {
        DebugP_log("   CMPSS1H DAC - ADCA loopback Failed\r\n");
    }

    if (retVal == SDL_PASS)
    {
        /*
        * Test CMPSS1L DAC - ADCA loopback
        */
        // Change comparator side and keep the other config's the same
        cmpssConfig.comparatorSelection = COMPL;

        retVal = testCompDacAdcLoopback(&cmpssConfig, &adcConfig, &adcChannelConfig, &testConfig);

        if (retVal == SDL_PASS)
        {
            DebugP_log("   CMPSS1L DAC - ADCA loopback Passed\r\n");
        }
        else
        {
            DebugP_log("   CMPSS1L DAC - ADCA loopback Failed\r\n");
        }

    }

    if (retVal == SDL_PASS)
    {
        /*
        * Test CMPSS2H DAC - ADCB loopback
        */

        cmpssConfig.cmpssInstance = 2;
        cmpssConfig.cmpssBase = CMPSS2_BASE;
        cmpssConfig.comparatorSelection = COMPH;

        /*
        * Configure ADCB
        */
        adcConfig.adcBase = ADCB_BASE;
        adcConfig.adcResBase = ADCBRESULT_BASE;

        adcChannelConfig.adcInputChannel = ADC_CH_ADCIN23;   // Refer to Analog Subsystem Block Diagram in Datasheet for INTERNAL_TEST channels

        initADC(&adcConfig);
        CMPSS_enableModule(cmpssConfig.cmpssBase);

        retVal = testCompDacAdcLoopback(&cmpssConfig, &adcConfig, &adcChannelConfig, &testConfig);

        if (retVal == SDL_PASS)
        {
            DebugP_log("   CMPSS2H DAC - ADCB loopback Passed\r\n");
        }
        else
        {
            DebugP_log("   CMPSS2H DAC - ADCB loopback Failed\r\n");
        }

    }

    if (retVal == SDL_PASS)
    {
        /*
        * Test CMPSS2L DAC - ADCB loopback
        */

        cmpssConfig.comparatorSelection = COMPL;

        retVal = testCompDacAdcLoopback(&cmpssConfig, &adcConfig, &adcChannelConfig, &testConfig);

        if (retVal == SDL_PASS)
        {
            DebugP_log("   CMPSS2L DAC - ADCB loopback Passed\r\n");
        }
        else
        {
            DebugP_log("   CMPSS2L DAC - ADCB loopback Failed\r\n");
        }

    }

    if (retVal == SDL_PASS)
    {
        /*
        * Test CMPSS3H DAC - ADCC loopback
        */

        cmpssConfig.cmpssInstance = 3;
        cmpssConfig.cmpssBase = CMPSS3_BASE;
        cmpssConfig.comparatorSelection = COMPH;

        /*
        * Configure ADCC
        */
        adcConfig.adcBase = ADCC_BASE;
        adcConfig.adcResBase = ADCCRESULT_BASE;

        adcChannelConfig.adcInputChannel = ADC_CH_ADCIN23;   // Refer to Analog Subsystem Block Diagram in Datasheet for INTERNAL_TEST channels

        initADC(&adcConfig);
        CMPSS_enableModule(cmpssConfig.cmpssBase);

        retVal = testCompDacAdcLoopback(&cmpssConfig, &adcConfig, &adcChannelConfig, &testConfig);

        if (retVal == SDL_PASS)
        {
            DebugP_log("   CMPSS3H DAC - ADCC loopback Passed\r\n");
        }
        else
        {
            DebugP_log("   CMPSS3H DAC - ADCC loopback Failed\r\n");
        }

    }

    if (retVal == SDL_PASS)
    {
        /*
        * Test CMPSS3L DAC - ADCC loopback
        */

        cmpssConfig.comparatorSelection = COMPL;

        retVal = testCompDacAdcLoopback(&cmpssConfig, &adcConfig, &adcChannelConfig, &testConfig);

        if (retVal == SDL_PASS)
        {
            DebugP_log("   CMPSS3L DAC - ADCC loopback Passed\r\n");
        }
        else
        {
            DebugP_log("   CMPSS3L DAC - ADCC loopback Failed\r\n");
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



