//#############################################################################
//
// FILE:   transfer_epwm_dlt.c
//
// TITLE:  ePWM Using The Synch Chain and Phase Shift.
//         Using DLT to datalog counter values and 
//         Visualize data
//
//! \addtogroup driver_example_list
//! <h1>ePWM Synchronization</h1>
//!
//! To enable this example, make sure to go to
//! Build -> Variables and set GUI_SUPPORT to value of 1 and DLT_SUPPORT to 1
//! This will create the GUI in CCS which can be opened by going to
//! View -> Plugins -> transfer_customlog_export_uart
//! If there are no plugins after buliding, 
//! please reload the window by doing Help -> Reload Window
//! This example configures ePWM1, ePWM2, ePWM3 and ePWM4 as follows
//!  - ePWM1 without phase shift as sync source
//!  - ePWM2 with phase shift of 300 TBCLKs
//!  - ePWM3 with phase shift of 600 TBCLKs
//!  - ePWM4 with phase shift of 900 TBCLKs
//!
//! \b External \b Connections \n
//! - GPIO0 EPWM1A
//! - GPIO1 EPWM1B
//! - GPIO2 EPWM2A
//! - GPIO3 EPWM2B
//! - GPIO4 EPWM3A
//! - GPIO5 EPWM3B
//! - GPIO6 EPWM4A
//! - GPIO7 EPWM4B
//!
//! \b Watch \b Variables \n
//! - None.
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

//#############################################################################
//
// Included Files
//
#include "board.h"
#include "bitfield_structs.h"
#include "export/export_log.h"
#include "dlt/export_dltpackage.h"

void epwm1ISR(void);
void epwm2ISR(void);
void epwm3ISR(void);
void epwm4ISR(void);

//
// Main
//
uint16_t epwm1Interrupt;
uint16_t epwm2Interrupt;
uint16_t epwm3Interrupt;
uint16_t epwm4Interrupt;
uint16_t empty_dlt_fifo = 0;

int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    epwm1Interrupt = 0;
    epwm2Interrupt = 0;
    epwm3Interrupt = 0;
    epwm4Interrupt = 0;

    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //

    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 and GPIO6/7 as
    // ePWM1A/1B, ePWM2A/2B, ePWM3A/3B, ePWM4A/4B pins respectively
    // Configure EPWM Modules
    //
    Board_init();
    cpuDltRegs.TIMER_CONTROL.bit.TIMER2_RST = 0;
    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start DLT log
    //
    __builtin_c29_datalog_tag(0x1);
    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        uint32_t dlt_packet[2] = {0,0};

        while (empty_dlt_fifo && DLT_getFIFOWordStatus())
        {
            //
            // Export data to GUI via UART
            //
            dlt_packet[1] = CPU1DLTFifoRegs.FIFO_BUF_L;
            dlt_packet[0] = CPU1DLTFifoRegs.FIFO_BUF_H;
            EXPORTDLTLOG_logUint32Array(dlt_packet, 2);
            
            if(DLT_getFIFOWordStatus() == 0)
            {
                //
                // Start DLT log when FIFO is empty
                //
                __builtin_c29_datalog_tag(0x1);
                empty_dlt_fifo = 0;
            }
        }
    }
}

//
// epwm1ISR - ePWM 1 ISR
//
void epwm1ISR(void)
{
    //
    // Insert TAG or code marker at beginning of ISR
    //
    __builtin_c29_datalog_tag(0x2);
    epwm1Interrupt++;
    uint16_t epwm1ctr = EPWM_getTimeBaseCounterValue(myEPWM1_BASE);
    //
    // Data log variables using intrinsic
    //
    __builtin_c29_datalog_write(epwm1ctr);
    __builtin_c29_datalog_write(epwm1Interrupt);
    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

}

//
// epwm2ISR - ePWM 2 ISR
//
void epwm2ISR(void)
{
    //
    // Insert TAG or code marker at beginning of ISR
    //
    __builtin_c29_datalog_tag(0x3);
    epwm2Interrupt++;
    uint16_t epwm2ctr = EPWM_getTimeBaseCounterValue(myEPWM2_BASE);
    //
    // Data log variables using intrinsic
    //
    __builtin_c29_datalog_write(epwm2ctr);
    __builtin_c29_datalog_write(epwm2Interrupt);
    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM2_BASE);

}

//
// epwm3ISR - ePWM 3 ISR
//
void epwm3ISR(void)
{
    //
    // Insert TAG or code marker at beginning of ISR
    //
    __builtin_c29_datalog_tag(0x4);
    epwm3Interrupt++;
    uint16_t epwm3ctr = EPWM_getTimeBaseCounterValue(myEPWM3_BASE);
    //
    // Data log variables using intrinsic
    //
    __builtin_c29_datalog_write(epwm3ctr);
    __builtin_c29_datalog_write(epwm3Interrupt);
    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM3_BASE);

}

//
// epwm4ISR - ePWM 4 ISR
//
void epwm4ISR(void)
{
    //
    // Insert TAG or code marker at beginning of ISR
    //
    __builtin_c29_datalog_tag(0x5);
    epwm4Interrupt++;
    uint16_t epwm4ctr = EPWM_getTimeBaseCounterValue(myEPWM4_BASE);
    //
    // Data log variables using intrinsic
    //
    __builtin_c29_datalog_write(epwm4ctr);
    __builtin_c29_datalog_write(epwm4Interrupt);
    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM4_BASE);

}

//
// DLT ISR export data when data logging level is reached
//
void INT_myDLT_ISR(void)
{
    //
    // Stop data logging after reaching
    // FIFO trigger count
    //
    __builtin_c29_datalog_tag(0x20);
    empty_dlt_fifo = 1;
    //
    // Clear DLT Interrupt events to receive more
    //
    DLT_clearEvent(DLT_INT_FIFO_TRIG | DLT_INT_INT);
}