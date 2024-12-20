//#############################################################################
//
// FILE:   ESM_ex2_safetyaggregator.c
//
// TITLE:  Safety Aggregator Error Injection Example
//
//! \addtogroup driver_example_list
//! <h1> ESM </h1>
//!
//! This example shows how to do parity error injection for safety aggregator and generate
//! parity error interrupt using the safety aggregator. For parity error generation, the example
//! injects a single bit error and waits for the code execution to jump to parity error ISR in for loop.
//! The parity error ISR clears the DED_STATUS_REG and sets EOI to acknowledge future Parity interrupts.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - ISRCount - The number of times entered into the ESM Parity Error ISR
//!  - loopCount - The number of loops performed while not in ISR
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
#include "board.h"
#include "inc/hw_types.h"

//
// Globals
//
uint32_t ISRCount;
uint32_t loopCount;


//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();

    //
    // Clear the counters
    //
    ISRCount = 0;
    loopCount = 0;

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    // Enable the Aggregator Parity Interrupts
    HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_AGGR_ENABLE_SET) = (ESM_SAFETY_AGGREGATOR_AGGR_ENABLE_SET_PARITY|ESM_SAFETY_AGGREGATOR_AGGR_ENABLE_SET_TIMEOUT) ;

    // Enable the ded Parity Interrupt for ESM_CPU1
    HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_DED_ENABLE_SET_REG0) = ESM_SAFETY_AGGREGATOR_DED_ENABLE_SET_REG0_ESMSS_ESM0_EDC_CTRL_BUSECC_ENABLE_SET;

    // Writing to the Vector Register to set svbus connection with ESM_CPU1 for SVBUS transaction - (Vector ID -0x1 for ESM_CPU1)
    // Read bit must not be set at this stage so that the aggregator is configured to do write operations through svbus on choosen Vector ID instance
    HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_ECC_VECTOR) = 0x1;

    // Writing to the Error 1 Register to set the Error Group2 and bit1
    HWREG(ESMSAFETYAGG_BASE + 0x18) = 0x00010002; 

    // Writing to the Control Register through SVBUS transaction to trigger error using the Error 1 register configurations
    HWREG(ESMSAFETYAGG_BASE + 0x14) = 0x0000010A;

    //
    // Loop Forever and wait for Parity interrupt trigger from Safety Aggregator
    //
    for(;;)
    {
        loopCount++;

    }
}


// ISR for Safety Aggregator Parity Interrupt Output 
void INT_ESM_PARITYERR_ISR(void)
{
    ISRCount++;

    // Writing to the Vector Register to set read adrress 0x20 (Error Status 1 register) and set connection with ESM_CPU1 for read transaction on SVBUS
    // Read bit should be set at this stage to configure safety aggregator is do read operation through svbus on choosen Vector ID instance
    HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_ECC_VECTOR) = 0x00208001;

    //Check output of Error Status 1 read operation at address ESMSAFETYAGG_BASE + 0x10

    while (HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_ECC_VECTOR) != (HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_ECC_VECTOR) |ESM_SAFETY_AGGREGATOR_ECC_VECTOR_RD_SVBUS_DONE)){
        
        // Wait till read svbus done bit is set
    }

    // Writing to the Vector Register to set svbus connection with ESM_CPU1 for SVBUS write transaction to clear the injected error
    HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_ECC_VECTOR) = 0x1;
 
    // Writing to the Error Status 1 Register to clear the injected uncorrectable error
    // this step also clears the DED_STATUS_REG
    HWREG(ESMSAFETYAGG_BASE + 0x20) = 0x00008000;

    
    while (HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_DED_STATUS_REG0) != 0x0){
        
        // Wait till ded status is not cleared
    }

    //After the Injected error is cleared, write EOI register to acknowledge future parity error interrupts
    HWREG(ESMSAFETYAGG_BASE + ESM_SAFETY_AGGREGATOR_O_DED_EOI_REG) = ESM_SAFETY_AGGREGATOR_DED_EOI_REG_EOI_WR;
}
//
// End of File
//