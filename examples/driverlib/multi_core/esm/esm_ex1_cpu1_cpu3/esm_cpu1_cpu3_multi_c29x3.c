//#############################################################################
//
// FILE:  ESM_cpu1_cpu3_multi_c29x3.c
//
// TITLE: ESM Multicore Example (CPU1,CPU3)
//
//! \addtogroup driver_multicore_example_list
//! <h1> ESM Multicore Example (CPU1,CPU3) </h1>
//!
//! This example demonstrates how to handle fault conditions using ESM and Error Aggregator
//! in a muli-core example (ESM_cpu1_cpu3_multi_c29x3.c).
//!
//! When using CCS for debugging this Multi-core example, after launching the
//! debug session,
//!     - Connect to CPU1 and load only the c29x1.out.
//!     - After the program is loaded, run CPU1.
//!     - Once c29x1 configures and releases CPU3 out of reset, the program
//!     stops.
//!     - Connect to CPU3 target now. c29x3.out would have started execution
//!     as soon as it is released from reset.
//!     - In case of RAM configuration, restart the CPU3 target and load the
//!     symbols.
//!
//! \note For FLASH configuration, this example is run in FLASH BANKMODE2,
//! where CPU3 has access to FLASH (FRI-2). Refer to the Flash Plugin
//! documentation to know about changing FLASH BANKMODEs and more.
//! Additionally, the CPAx and CDAx RAMs are used for allocating various
//! RAM sections.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - CPU3nmigen
//!  - Globalerroreventnumber
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
#include "cpu.h"
#include "bitfield_structs.h"
#include "inc/hw_error_aggregator.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

//Data variable to be written to M0RAM location
uint32_t M0RAM_data = 0x12;
//Global Event Number Variable, for this example it should be 2 (ErrorAggregator_CPU3_HPERR)
uint32_t Globalerroreventnumber;

bool CPU3nmigen = false;
Interrupt_NmiStatus nmiStatus;
//
// Main
//
int main(void)
{
    //
    // Initialize peripheral clocks and interrupts
    //
    Device_init();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG31);


    // Write to M0 RAM Base address - 0x2000_0000
    // Since CPU3 does not have write access to M0 RAM hence write generates a Security violation fault to CPU3 which needs to be handled using ESM
    HWREG(0x20000000) = M0RAM_data;

    //
    // Loop forever.
    //

    while(1)
    {

    }
}

void myNMI_CPU3_ISR(void)
{
    CPU3nmigen = true;

    //Find out the highest priority outstanding high priority interrupt that triggered the NMI
    Globalerroreventnumber = ESM_getHighestLowPriorityInterrupt(ESMSYSTEM_BASE);

    Interrupt_clearEsmEaFlags(&nmiStatus);

    //After errors are cleared, write End of Interrupt vector and exit the ISR
    ESM_writeEOIVector(ESMCPU3_BASE, ESM_EOI_HIGH_PRIORITY_ERROR_INTERRUPT);
}
//
// End of File
//
