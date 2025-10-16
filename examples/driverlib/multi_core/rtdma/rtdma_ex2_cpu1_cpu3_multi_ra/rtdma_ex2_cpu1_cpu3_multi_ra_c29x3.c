//#############################################################################
//
// FILE:  rtdma_ex2_cpu1_cpu3_multi_ra_c29x3.c
//
// TITLE: SysConfig RTDMA example with Resource Allocator
//
//! \addtogroup driver_dual_example_list
//! <h1> RTDMA example with Resource Allocator </h1>
//!
//! This example shows how to initiate a DMA transfer on CPU1 from a shared
//! peripheral which is owned by CPU2.  In this specific example, a timer ISR
//! is used on CPU2 to initiate a SPI transfer which will trigger the CPU1 DMA.
//! CPU1's DMA will then in turn update the ePWM1 CMPA value for the PWM which
//! it owns.  The PWM output can be observed on the GPIO pins.
//!
//! In this example, an EPWM is allocated to CPU1 and SPI and an RTDMA channel
//! to CPU3 in the rtdma_ex2_cpu1_cpu3_multi_ra.syscfg file. This generates
//! a resourceAllocation.json file at rtdma_ex2_cpu1_cpu3_multi_ra/RA/syscfg
//! folder. The CPU specific syscfg file further configures its
//! pre-allocated resources.
//! The individual CPU projects can be built independent of each other.
//!
//! When using CCS for debugging this Multi-core example, after launching the
//! debug session,
//!     - Connect to CPU1 and load the c29x3.out first. (In case of FLASH
//!     configuration, this might not halt at main, ignore this)
//!     - Load c29x1.out next.
//!     - After the program is loaded, run CPU1.
//!     - Once c29x1 releases CPU3 out of reset, the program stops.
//!     - Connect to CPU3 target now. c29x3.out would have started execution
//!     as soon as it is released from reset.
//!     - In case of RAM configuration, load the symbols for CPU3.
//!     - In case of FLASH, do a Power-on-Reset, connect to CPU1/ CPU3 and load
//!     the respective symbols.
//!
//! \note For FLASH configuration, this example is run in FLASH BANKMODE2,
//! where CPU3 has access to FLASH (FRI-2). Refer to the Flash Plugin
//! documentation to know about changing FLASH BANKMODEs and more.
//! Additionally, the CPAx and CDAx RAMs are used for allocating various
//! RAM sections.
//!
//! When importing the Project in CCS 20.3.0, do verify if the Resource
//! allocation specific flags are set. If not, update the Project
//! Properties -> Build -> Tools -> SysConfig -> Miscellaneous -> Other flags
//! to include the appropriate flag.
//! For projects having the .syscfg file in "Define Resource Allocations" mode,
//! add the following flag:
//!      --enableResourceAllocationSetup
//! For CPUx projects having .syscfg files in "Configure using Predefined
//! Resource Allocations" mode, add the following flag:
//!      --resourceAllocation <path to resourceAllocation.json file>
//!   for example,
//!      --resourceAllocation ..\..\rtdma_ex2_cpu1_cpu3_multi_ra\RA\syscfg\resourceAllocation.json
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
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
#include "inc/hw_types.h"

//
// Globals
//
uint16_t newCMPValue;
uint32_t direction = 1;

const void *destAddr = (const void *)(EPWM1_BASE + EPWM_O_CMPA + 2);
const void *srcAddr = (const void *)&newCMPValue;

//
// Function Prototypes
//
void initSpi(void);
void loadBuffer(void);

//
// Main
//
int main(void)
{
    //
    // Interrupt initialization
    //
    Device_init();

    newCMPValue = 3000;  // Set CMP value

    //
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU3_L_CPU1_R_CH0, IPC_FLAG31);

    //
    // Setup CPU Timer 1 to interrupt every 10 ms
    //
    CPUTimer_startTimer(CPUTIMER1_BASE);

    //
    // Configure the SPI
    //
    initSpi();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Loop forever. Wait for IPC interrupt
    //
    while(1);
}


//
// initSpi - Function to Setup SPI for FIFO mode
//
void initSpi(void)
{
   //
   // A DMA transfer will be triggered here!
   //

   //
   // Load the SPI FIFO Tx Buffer
   //
   loadBuffer();

   //
   // Disable the clock to prevent continuous transfer/DMA triggers. Note that
   // this method of disabling the clock should not be used if actual data is
   // being transmitted.
   //
   SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
}

//
// loadBuffer - Function to load SPI Tx FIFO Buffer
//
void loadBuffer(void)
{
    //
    // Fill up the FIFO buffer
    //
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
    HWREGH(mySPI0_BASE + SPI_O_TXBUF) = 0xAAAA;
}


//
// INT_myCPUTIMER0_ISR - CPU Timer 1 ISR
//
void INT_myCPUTIMER0_ISR(void)
{
    //
    // Re-enable SPI clock to allow DMA trigger
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

    //
    // Wait for interrupt flag. This is when the DMA trigger will occur.
    //
    while((SPI_getInterruptStatus(mySPI0_BASE) & SPI_INT_TXFF) == 0)
    {
    }

    //
    // Reload the SPI TX buffer and clear interrupt flag
    //
    loadBuffer();
    SPI_clearInterruptStatus(mySPI0_BASE, SPI_INT_TXFF);

    //
    // Disable the clock to prevent continuous transfer/DMA triggers. Note that
    // this method of disabling the clock should not be used if actual data is
    // being transmitted.
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

    //
    // Update next value to be transferred to the ePWM
    //
    if (newCMPValue >= 4500) {
        direction = -1;
    } else if (newCMPValue <= 1500) {
        direction = 1;
    }

    newCMPValue += direction * 50;
}

void INT_myRTDMA1Ch0_ISR()
{
    // ESTOP0;
}


//
// End of File
//
