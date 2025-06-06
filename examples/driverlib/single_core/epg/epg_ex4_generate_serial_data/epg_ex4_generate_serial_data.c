//#############################################################################
//
// FILE:   epg_ex4_generate_serial_data.c
//
// TITLE:  EPG Generate Serial Data
//
//! \addtogroup driver_example_list
//! <h1> EPG Generate Serial Data </h1>
//!
//! This example generates SPICLK and SPI DATA signals using the SIGGEN module.
//! For more information on this example, visit:
//! [Designing With the C2000 Embedded Pattern Generator 
//! (EPG)](https://www.ti.com/lit/spracy7)
//!
//! \b External \b Connections \n
//!  - None. Signal is generated on GPIO 2, 3. Can be visualized
//!    through oscilloscope.
//!
//
//#############################################################################
//
//
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define CLK_GEN_PERIOD      10U-1U
#define SIG_GEN_DATA_LENGTH 16U

#define CPOL_CPHA_0_0   0
#define CPOL_CPHA_0_1   1
#define CPOL_CPHA_1_0   2
#define CPOL_CPHA_1_1   3

#define EXAMPLE_MODE    CPOL_CPHA_0_1

#if EXAMPLE_MODE == CPOL_CPHA_0_1
//
// SPICLK (Rising edge with delay) CPOL=0, CPHA=1
//

//
// Data
//
#define SIG_GEN_DATA0_0_15    0b1111000011001111U

//
// Clock - Data latched on rising edge, during idle CLK is LOW
//
#define SIG_GEN_DATA0_16_31   0b1010101010101010U

#define SIG_GEN_MODE          EPG_SIGGEN_MODE_ROTATE_RIGHT_ONCE

#elif EXAMPLE_MODE == CPOL_CPHA_0_0
//
// SPICLK (SPICLK Rising edge without delay) CPOL=0, CPHA=0
//

//
// Data
//
#define SIG_GEN_DATA0_0_15    0b1110000110011111U

//
// Clock - Data latched on falling edge, during idle CLK is LOW
//
#define SIG_GEN_DATA0_16_31   0b1010101010101010U

#define SIG_GEN_MODE          EPG_SIGGEN_MODE_ROTATE_RIGHT_ONCE

#elif EXAMPLE_MODE == CPOL_CPHA_1_1
//
// SPICLK (SPICLK Falling edge with delay) CPOL=1, CPHA=1
//

//
// Data
//
#define SIG_GEN_DATA0_0_15    0b1111000011001111U

//
// Clock - Data latched on falling edge, during idle CLK is HIGH
//
#define SIG_GEN_DATA0_16_31   0b0101010101010101U

#define SIG_GEN_MODE          EPG_SIGGEN_MODE_ROTATE_RIGHT_ONCE

#elif EXAMPLE_MODE == CPOL_CPHA_1_0
//
// SPICLK (SPICLK Falling edge without delay) CPOL=1, CPHA=0
//

//
// Data
//
#define SIG_GEN_DATA0_0_15    0b1110000110011111U

//
// Clock - Data latched on rising edge, during idle CLK is HIGH
//
#define SIG_GEN_DATA0_16_31   0b0101010101010101U

#define SIG_GEN_MODE          EPG_SIGGEN_MODE_ROTATE_RIGHT_ONCE

#endif


volatile uint32_t epg1_gintsts = 0;

//
// Main
//
int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins 2, 3 for EPG OUT
    //
    Device_initGPIO();
    
    GPIO_setPinConfig(GPIO_2_OUTPUTXBAR1);
    GPIO_setDirectionMode(2, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(2, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(GPIO_3_OUTPUTXBAR2);
    GPIO_setDirectionMode(3, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(3, GPIO_QUAL_SYNC);
    
    //
    // Connect EPG Output to GPIO through xbar
    //
    XBAR_selectOutputXbarInputSource(OUTPUTXBAR_BASE, XBAR_OUTPUT1,
                            XBAR_OUT_EPG1_OUT0);
    XBAR_selectOutputXbarInputSource(OUTPUTXBAR_BASE, XBAR_OUTPUT2,
                            XBAR_OUT_EPG1_OUT1);

    //
    // Select Signal Generator output for EPG output of 0,1
    //
    EPG_selectEPGOutput(EPG_BASE, EPG_OUT0, EPG_OUT_SEL_SIG);
    EPG_selectEPGOutput(EPG_BASE, EPG_OUT1, EPG_OUT_SEL_SIG);

    EPG_selectSignalOutput(EPG_BASE, EPG_OUT0, EPG_SIGGEN0_DATATRANOUT0);
    EPG_selectSignalOutput(EPG_BASE, EPG_OUT1, EPG_SIGGEN0_DATATRANOUT2);

    //
    // Set Clock Generator 0 period
    //
    EPG_setClkGenPeriod(EPG_BASE, EPG_CLKGEN0, CLK_GEN_PERIOD);

    //
    // Set the source of signal generator 0 to clk generator output 0
    //
    EPG_selectSigGenClkSource(EPG_BASE, EPG_SIGGEN0, EPG_CLKGEN0_CLKOUT0_GCLK);

    //
    // Set offset of clock generator output 0 to 0
    //
    EPG_setClkGenOffset(EPG_BASE, EPG_CLKGEN0, 0, 0);


    EPG_setDataBitLen(EPG_BASE, EPG_SIGGEN0, SIG_GEN_DATA_LENGTH);
    EPG_setSignalGenMode(EPG_BASE, EPG_SIGGEN0, SIG_GEN_MODE);
    EPG_setData0Word(EPG_BASE, EPG_SIGGEN0, (SIG_GEN_DATA0_0_15 | (uint32_t)SIG_GEN_DATA0_16_31 << 16));

    //
    // Enable EPG
    //
    EPG_enableGlobal(EPG_BASE);

    //
    // Enable signal generator
    //
    EPG_enableSignalGen(EPG_BASE, EPG_SIGGEN0);

    while(1)
    {
        epg1_gintsts = EPG_getInterruptStatus(EPG_BASE);
        if (epg1_gintsts & EPG_INT_SIGGEN0_DONE){
            EPG_clearInterruptFlag(EPG_BASE, epg1_gintsts);
            EPG_setData0Word(EPG_BASE, EPG_SIGGEN0, (SIG_GEN_DATA0_0_15 | (uint32_t)SIG_GEN_DATA0_16_31 << 16));
            EPG_enableSignalGen(EPG_BASE, EPG_SIGGEN0);
        }
        DEVICE_DELAY_US(10);
    }

}

//
// End of File
//
