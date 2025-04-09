//#############################################################################
//
// FILE:   freertos_ssu_demo.c
//
// TITLE:  FreeRTOS + SSU operation demo
//
//!
//! This example demonstrates usage of FreeRTOS with SSU functionality.
//! Sysconfig is used to setup all the peripherals, FreeRTOS, and also the SSU
//! settings
//! The SSU configuration divides the application into 3 LINKS as follows:
//!
//!     - LINK2 : Secure LINK. The FreeRTOS kernel code, and Secure tasks are
//!       placed in LINK2, along with all ISR Wrapper functions
//!     - LINK3 : CommonCode LINK. This is the API configured LINK, and belongs
//!       to a separate SSU STACK
//!     - LINK4 : Comms LINK. The Comms task and SPI interrupt are placed here
//!     - LINK5 : Control LINK. The Control task and TIMER0 interrupt are 
//!       placed here
//!
//! Since an interrupt is out of the control of the FreeRTOS kernel & can occur
//! at any point during execution, all the PIPE-registered ISRs are placed in
//! LINK2. This enables the interrupt to save and restore registers to the task
//! stack safely. The User ISRs are placed in whichever LINK the interrupt is
//! actually meant to execute from. This stack switching is implemented in
//! assembly in the commonIsr_secure file. This code switches to a common ISR
//! stack, and also handles nesting.
//!
//! Interrupt nesting is demonstrated with the help of software triggered
//! interrupts. The CPUTIMER0 interrupt in LINK5 triggers a Medium Priority
//! SW interrupt in LINK2. This interrupt triggers a High Priority SW interrupt
//! in LINK4 and unblocks the Secure task. 
//!
//! The Secure task periodically polls various conter globals and transmits them
//! to the Comms task via SPI. The Comms task aggregates these values into a
//! struct variable, and logs a success message to UART. The Control task is a 
//! simple high frequency loop for demonstration purposes. There are also some
//! helper functions re-defined in LINK2 for writing to specific registers that
//! not all LINKs have access to. 
//! 
//! After loading the example.out power cycle EVM to run and debug the example
//!
//! \b External \b Connections \n
//!  Connect the UARTA port to a PC via a transceiver and cable.
//!  - GPIO43 is UARTA RX
//!  - GPIO42 is UARTA TX
//!
//! \b Watch \b Variables \n
//! - countTracker : Strcture containing the count values received from 
//!   Secure task
//!
//
//#############################################################################

//
// Included Files
//
#include "appMdl_secure.h"

//
// Main
//
int main(void)
{
    //
    // Initialize system configuration
    //
    systemInit();

    //
    // Should not reach
    //
    for(;;)
    {
    }
}
