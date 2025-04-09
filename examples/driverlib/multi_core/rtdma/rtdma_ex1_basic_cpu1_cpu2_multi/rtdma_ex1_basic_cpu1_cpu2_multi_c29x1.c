//#############################################################################
//
// FILE:  rtdma_ex1_basic_cpu1_cpu2_multi_c29x1.c
//
// TITLE: RTDMA Multi-core example with Memory Allocator tool
//
//! \addtogroup driver_multicore_example_list
//! <h1> RTDMA </h1>
//!
//! This example uses an RTDMA2 channel to transfer data from a buffer to
//! another buffer in RAM. The example first disables Lock-step to use the
//! RTDMA2 channels. RTDMA2 global settings and RTDMA2 MPU are configured
//! by CPU1 application.
//! The data to be transmitted is written by CPU1 application. This data is
//! in an MPU region to which RTDMA2 channel has only read access.
//! 
//! The example triggers the DMA channel repeatedly until the transfer of 16
//! bursts (where each burst is 4 8-bit words) has been completed. When the
//! whole transfer is complete it will trigger the DMA interrupt.
//!
//! The linker cmd file is generated using the Memory Allocator tool in
//! SysConfig.
//!
//! When using CCS for debugging this Multi-core example, after launching the
//! debug session,
//!     - Connect to CPU1 and load only the c29x1.out.
//!     - After the program is loaded, run CPU1.
//!     - Once c29x1 disables lock-step and releases CPU2 out of reset, the
//!     program stops.
//!     - Connect to CPU2 target now. c29x2.out would have started execution
//!     as soon as it is released from reset.
//!     - Load the symbols for c29x2.out.
//!
//! \note In FLASH configuration, the CPU2 application code is loaded to CPU1
//! FLASH. At runtime, CPU1 copies it to RAM for CPU2 to execute.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - pass
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
// Defines
//
#define CPU2_RESET_VECTOR   0x20100040U
#define CPU2_NMI_VECTOR     0x20100080U

//
// Globals
//
__attribute__((location(0x20149000))) volatile uint32_t TxData[16]; // Transmit data buffer

const void *srcAddr = (const void *)TxData;

//
// Main
//
int main(void)
{
    int i;

    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Boot CPU2
    //
    SSU_configBootAddress(SSU_CPU2, CPU2_RESET_VECTOR, SSU_LINK2);
    SSU_configNmiAddress(SSU_CPU2, CPU2_NMI_VECTOR, SSU_LINK2);

    //
    // Bring CPU2 out of reset. Wait for CPU2 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU2, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU2Reset() == 0x1U);

    //
    // CPU2 is out of reset now. Connect to CPU2 and load the symbols.
    //
    ESTOP0;

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Initialize the data buffers
    //
    for(i = 0; i < 16; i++)
    {
        TxData[i] = i;
    }

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU2_R_CH0, IPC_FLAG31);

    //
    // End of example. Loop forever
    //
    while(1);
}


//
// End of File
//