//#############################################################################
//
// FILE:   emif_ex1_16bit_sdram_syscfg.c
//
// TITLE:  EMIF 16bit SDRAM Example
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 module accessing 16bit SDRAM </h1>
//!
//! This example configures EMIF1 in 16bit SYNC mode and uses CS0 as chip
//! enable.It will first write to an array in the SDRAM and then read it back
//!
//! Sysconfig inserts the required attributes to the ISR functions to inform
//! the compiler that the function is an interrupt / realtime interrupt.
//!
//! \b External \b Connections \n
//!  - Custom setup with External SDR-SDRAM memory (MT48LC32M16A2 -75) daughter card
//!    Modify pinmux based on the setup under test
//!
//! \b Watch \b Variables \n
//!
//
//#############################################################################
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

//###########################################################################

//
// Included Files
//
#include "board.h"

//
//  Defines
//
#define EMIF_SDRAM_CS0_BASE_ADDRESS         (0x80000000U)
#define EMIF_MEM_SIZE                       (0x500U)
#define DELAY_IN_CYCLES                     (200000U)

//
// Globals
//
uint32_t g_errCnt = 0U;

//
// Main
//
int main(void)
{
    uint32_t cnt;
    uint16_t *sdramAddr = (uint16_t*)EMIF_SDRAM_CS0_BASE_ADDRESS;
    uint16_t memVal;
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    //  Delay required before accessing SDRAM
    //
    SysCtl_delay(DELAY_IN_CYCLES);

    //
    //  Write known values to SDRAM
    //
    memVal = 0x0000U;
    for(cnt = 0U;cnt < EMIF_MEM_SIZE;cnt++)
    {
        *(sdramAddr + cnt) = memVal;
        memVal += 2U;
    }

    //
    //  Read from SDRAM
    //
    memVal = 0x0000U;
    for(cnt = 0U;cnt < EMIF_MEM_SIZE;cnt++)
    {
        if(memVal != *(sdramAddr + cnt))
        {
            g_errCnt++;
        }
        memVal += 2U;
    }

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {
    }
}

//
// End of File
//