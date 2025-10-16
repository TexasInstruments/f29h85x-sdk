//#############################################################################
//
// FILE:  rtdma_ex1_basic_cpu1_cpu2_multi_c29x2.c
//
// TITLE: RTDMA Multi-core example with Memory Allocator tool
//
//! \addtogroup driver_multicore_example_list
//! <h1> RTDMA Example </h1>
//!
//! This example uses RTDMA1 and RTDMA2 channels to transfer data from a buffer to
//! another buffer in RAM. The example first disables Lock-step to use both the
//! RTDMA instances. RTDMA1 and RTDMA2 global settings and MPU are configured
//! by CPU1 application.
//!
//! The data to be transmitted by RTDMA2 is written by CPU1 application. This data is
//! in an MPU region to which RTDMA2 channel has only read access.
//! 
//! The data to be transmitted by RTDMA1 is written by CPU2 application. This data is
//! in an MPU region to which RTDMA1 channel has only read access.
//!
//! The example triggers the DMA channel repeatedly until the transfer of 16
//! bursts (where each burst is 4 8-bit words) has been completed. When the
//! whole transfer is complete it will trigger the DMA interrupt.
//!
//! Follow these steps to use CCS to debug this multi-core example. After 
//! launching the debug session:
//!     1. Connect to CPU1.
//!     2. Using the Flash Plug-In, 
//!         - In 'User Config Settings', Program FLASH BANKMODE to BANKMODE2, if not already done.
//!         - In 'Download Settings', Unselect 'Verify Flash after Program (SSU Mode 1 Usage Only)', if not already done.
//!         - In 'Download Settings', Unselect 'Perform Blank Check before loading data to Flash memory (SSU Mode 1 Usage Only)', if not already done.
//!         - In 'NonMain Erase Settings', Select 'Allow NonMain Flash erase before loading data to Flash memory' (click checkbox), if not already done. 
//!          Refer to Flash Plug-In documentation for further instructions.
//!     3. Issue an XRSN to the device.
//!     4. Load only the CPU1.out.
//!     5. After the program is loaded, issue an XRSN to the device. 
//!        Connect to CPU1 and load CPU1 symbols. 
//!     6. At this point, CPU1 configures and releases CPU2 out of reset. CPU2 program
//!     has started execution. To further debug, connect to CPU2 and load the CPU2 symbols. 
//!
//! \note For FLASH configuration, this example is run in FLASH BANKMODE2,
//! where CPU2 has access to FLASH (FRI-2). Refer to the Flash Plugin
//! documentation to know about changing FLASH BANKMODEs and more.
//! Additionally, the CPAx and CDAx RAMs are used for allocating various
//! RAM sections.
//!
//!  CPU2 SSU Configurations:
//!  APRs   - sbox_Comms_stackmem_apr, sbox_DMA_stackmem_apr, sbox_CommonCode_stackmem_apr, Comms_dataAPR_RW, DMA_dataAPR_RW, 
//!           STACK2_stackmem_apr, STACK1_stackmem_apr, CommonCodeModule_dataAPR_RW, LINK2_dataAPR_RW, LINK2_codeAPR_RAM, 
//!          CommonCodeModule_codeAPR_RAM, DMA_codeAPR_RAM, Comms_codeAPR_RAM, LINK2_dataAPR_RO, CommonCodeModule_dataAPR_RO, ipc_shared_SHARED_CPU1
//!  LINKs  - LINK1 (Bootloader), LINK2 (System Configuration), LINK3 (CommonCode), LINK4 (DMA), LINK5 (Comms)
//!  STACKs - STACK1 (Bootloader), STACK2 (System Configuration), STACK3 (CommonCode), STACK4 (DMA), STACK5 (Comms)
//!
//! Refer to linker.cmd files and Memory Allocation tool (View > Memory Allocation) for more insight on memory usage.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b RxData - Received data from RTDMA2
//!  - \b done - RTDMA2 initiated transfer successful
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
#include "app_cpu2.h"

void systemInit_cpu2(void);

//
// Main
//
__attribute__((section(".text.main")))
int main(void)
{
    //
    // Initialize system configuration
    //
    systemInit_cpu2();

    //
    // Loop.
    //
    for(;;)
    {
    }
}

//
// End of File
//
