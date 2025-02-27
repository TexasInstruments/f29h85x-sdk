//#############################################################################
//
// FILE:   device.c
//
// TITLE:  Device setup for examples.
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
#include "device.h"
#include "driverlib.h"
#include <cpy_tbl.h>

#ifdef __cplusplus
using std::memcpy;
#endif

#ifdef _FLASH
#if !defined(__CPU2__) && !defined(__CPU3__)
    //
    //  Dummy certificate section which is updated when actual certitifcate is generated
    //  as part of the post build steps
    //
    __attribute__((retain, section("cert"))) const uint8_t certificate[4096U] = {0U};
#endif
#endif

//*****************************************************************************
//
// Device_copy_in
//
//*****************************************************************************
void Device_copy_in(COPY_TABLE *tp)
{
   unsigned short i;

   for (i = 0; i < tp->num_recs; i++)
   {
      COPY_RECORD crp = tp->recs[i];
      char *load_addr = (char*)crp.load_addr;
      char *run_addr = (char *)crp.run_addr;

      if (crp.size)
      {
         /*------------------------------------------------------------------*/
         /* Copy record has a non-zero size so the data is not compressed.   */
         /* Just copy the data.                                              */
         /*------------------------------------------------------------------*/
         memcpy(run_addr, load_addr, crp.size);
      }
   }
}

//*****************************************************************************
//
// Function to initialize the device. Primarily initializes system control to a
// known state by disabling the watchdog, setting up the SYSCLKOUT frequency,
// and enabling the clocks to the peripherals.
//
//*****************************************************************************
void Device_init(void)
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

    //
    // Errata workaround
    //
    Device_errataWorkaroundNMIVectorFetch();

#ifdef _FLASH
    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(DEVICE_FLASH_WAITSTATES);

#endif
#if ((!defined(__CPU2__)) && (!defined(__CPU3__)))
    //
    // Set up PLL
    //
#if defined(USE_PLL_SRC_INTOSC)
    SysCtl_setClock(SYSCTL_OSCSRC_OSC2, SYSCTL_PLL_ENABLE, SYSCTL_REFDIV_1,
					SYSCTL_IMULT_40, SYSCTL_ODIV_2, SYSCTL_SYSDIV_1, DCC1_BASE);
#elif defined(USE_PLL_SRC_XTAL)
    SysCtl_setClock(SYSCTL_OSCSRC_XTAL_SE, SYSCTL_PLL_ENABLE, SYSCTL_REFDIV_2,
					SYSCTL_IMULT_32, SYSCTL_ODIV_2, SYSCTL_SYSDIV_1, DCC1_BASE);
#endif
	ASSERT(SysCtl_getClock(DEVICE_OSCSRC_FREQ) == DEVICE_SYSCLK_FREQ);

    //
    // Configure HSM Clock
    //
    SysCtl_setHSMClock(SYSCTL_HSMCLK_DIV_2);

#endif
    //
    // Turn on all peripherals
    //
    Device_enableAllPeripherals();

    //
    // Initialize PIPE and clear PIPE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIPE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();
}

//*****************************************************************************
//
// Function to turn on all peripherals, enabling reads and writes to the
// peripherals' registers.
//
// Note that to reduce power, unused peripherals should be disabled.
// Use function Sysctl_enablePeripheral function to selectively enable
// peripherals. Eg: Sysctl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUTIMER0)
//
//*****************************************************************************
void Device_enableAllPeripherals(void)
{
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR0)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR1)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR2)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR3)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR4)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR6)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR7)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR8)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR9)  = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR10) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR13) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR14) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR16) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR17) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR18) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR19) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR20) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR21) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR23) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR25) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR27) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR28) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR30) = 0xFFFFFFFF;
    HWREG(CPUPERCFG_BASE + SYSCTL_O_PCLKCR32) = 0xFFFFFFFF;
}

//*****************************************************************************
//
// Function to disable pin locks and enable pullups on GPIOs.
//
//*****************************************************************************
void Device_initGPIO(void)
{
    //
    // Disable pin locks.
    //
    GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_C, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_D, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_F, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_G, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_H, 0xFFFFFFFF);
}

//*****************************************************************************
//
// Function to verify the XTAL frequency
//
// Note that this function assumes that the PLL is not already configured and
// hence uses SysClk freq = 10MHz for DCC calculation
//
//*****************************************************************************
bool Device_verifyXTAL(float freq)
{
    //
    // Use DCC to verify the XTAL frequency using INTOSC2 as reference clock
    //

    //
    // Turn on XTAL and wait for it to power up using X1CNT
    //
    SysCtl_turnOnXTAL();
    SysCtl_clearExternalOscCounterValue();
    while(SysCtl_getExternalOscCounterValue() != SYSCTL_X1CNT_X1CNT_M);

    //
    // Enable DCC1 clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC1);

    //
    // Insert atleast 5 cycles delay after enabling the peripheral clock
    //
    NOP;
    NOP;
    NOP;
    NOP;
    NOP;

    //
    // Configures XTAL as CLKSRC0 and INTOSC2 as CLKSRC1
    // Fclk0 = XTAL frequency (input parameter)
    // Fclk1 = INTOSC2 frequency = 10MHz
    //
    // Configuring DCC error tolerance of +/-1%
    // INTOSC2 can have a variance in frequency of +/-10%
    //
    // Assuming PLL is not already configured, SysClk freq = 10MHz
    //
    // Note : Update the tolerance and INTOSC2 frequency variance as necessary.
    //
    return (DCC_verifyClockFrequency(DCC1_BASE,
                                     DCC_COUNT1SRC_INTOSC2, 10.0F,
                                     DCC_COUNT0SRC_XTAL, freq,
                                     1.0F, 10.0F, 10.0F));
}

#if ((!defined(__CPU2__)) && (!defined(__CPU3__)))
//*****************************************************************************
//
// Function to boot CPU2
//
//*****************************************************************************
void Device_bootCPU2(COPY_TABLE *copyTable, uint32_t reset_vector,
                     SSU_Link link)
{
#ifdef _FLASH
    //
    // Copy the CPU2 application code from FLASH to CPU2 RAM
    // The copyTable is created by the linker. Please see the CPU2 linker
    // command file for its definition.
    //
    Device_copy_in(copyTable);
#endif //FLASH

    //
    // Set the address and link to which CPU2 Boots
    //
    SSU_configBootAddress(SSU_CPU2, reset_vector, link);

    //
    // Bring CPU2 out of reset. Wait for CPU2 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU2, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU2Reset() == 0x1U);
}

//*****************************************************************************
//
// Function to boot CPU3
//
//*****************************************************************************
void Device_bootCPU3(COPY_TABLE *copyTable, uint32_t reset_vector,
                     SSU_Link link)
{
#ifdef _FLASH
    //
    // When CPU3 does not have dedicated FLASH region, copy the CPU3
    // application code from CPU1 FLASH to CPU3 RAM.
    // The copyTable is created by the linker. Please see the CPU3 linker
    // command file for its definition.
    //
    if(copyTable != 0U)
    {
        Device_copy_in(copyTable);
    }
#endif //FLASH

    //
    // Set the address and link to which CPU3 Boots
    //
    SSU_configBootAddress(SSU_CPU3, reset_vector, link);

    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU3, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU3Reset() == 0x1U);
}
#endif //CPU

//*****************************************************************************
//!
//! Errata Workaround for System: Pending Misaligned Reads in the
//! Pipeline After CPU Goes to Fault State Preventing NMI Vector Fetch.
//!
//*****************************************************************************
void Device_errataWorkaroundNMIVectorFetch()
{
#if ((defined(__CPU2__)))
    // Configure CPU2_ESM to generate an NMI on CPU1_ERAD_NMI event
    ESM_enableGlobal(ESMCPU2_BASE);
    ESM_setInterruptPriorityLevel(ESMCPU2_BASE, ESM_EVENT_CPU1_ERAD_NMI, ESM_INTERRUPT_PRIORITY_LEVEL_HIGH);
    ESM_enableInterrupt(ESMCPU2_BASE, ESM_EVENT_CPU1_ERAD_NMI);

    // Disable group 0 NMI generation in CPU2 ESM
    HWREG(ESMCPU2_BASE + ESM_CPU_O_INTR_EN_CLR(0U)) |= 0x3FU;
#elif ((defined(__CPU3__)))
    // Configure CPU3_ESM to generate an NMI on CPU1_ERAD_NMI event
    ESM_enableGlobal(ESMCPU3_BASE);
    ESM_setInterruptPriorityLevel(ESMCPU3_BASE, ESM_EVENT_CPU1_ERAD_NMI, ESM_INTERRUPT_PRIORITY_LEVEL_HIGH);
    ESM_enableInterrupt(ESMCPU3_BASE, ESM_EVENT_CPU1_ERAD_NMI);

    // Disable group 0 NMI generation in CPU3 ESM
    HWREG(ESMCPU3_BASE + ESM_CPU_O_INTR_EN_CLR(0U)) |= 0x3FU;
#else
    ESM_triggerSoftReset(ESMCPU1_BASE);
    ESM_triggerSoftReset(ESMSYSTEM_BASE);

    // Enable the global interrupt for SYSESM
    ESM_enableGlobal(ESMSYSTEM_BASE);

    // Enable group 0 errors to generate low priority Interrupt (GEN EVT)
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_INTR_EN_SET(0U)) |= 0x3FU;
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_INT_PRIO(0U)) &= ~(0x3FU);

    // Route ESM SYS GEN EVENT to EPWMXBAR TRIP signal
    XBAR_selectEpwmXbarInputSource(XBAR_TRIP1, XBAR_EPWM_ESM_GEN_EVENT);

    // Configuring SEC3 in START STOP mode, counting SYSCLK. StartInp = EPWMXBAR1 event, StopInp = SEC3 event
    ERAD_Counter_Config counter_params;
    ERAD_setCounterOwnership(ERAD_COUNTER3, ERAD_OWNER_APPLICATION);
    ERAD_disableCounterModule(ERAD_COUNTER3);
    counter_params.enable_stop = false;
    counter_params.enable_int = true;
    counter_params.enable_nmi = true;
    counter_params.event = ERAD_EVENT_NO_EVENT;
	counter_params.event_mode = ERAD_COUNTER_MODE_RISING_EDGE;
    counter_params.rst_on_match = true;
    counter_params.reference = 0x32U;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER3, &counter_params, ERAD_EVENT_EPWMXBAR_OUT1, ERAD_EVENT_COUNTER3_EVENT);
	ERAD_enableCounterModule(ERAD_COUNTER3);

    // Configure CPU1_ESM to generate an NMI on CPU1_ERAD_NMI event
    ESM_enableGlobal(ESMCPU1_BASE);
    ESM_setInterruptPriorityLevel(ESMCPU1_BASE, ESM_EVENT_CPU1_ERAD_NMI, ESM_INTERRUPT_PRIORITY_LEVEL_HIGH);
    ESM_enableInterrupt(ESMCPU1_BASE, ESM_EVENT_CPU1_ERAD_NMI);

    // Disable group 0 NMI generation in CPU1 ESM
    HWREG(ESMCPU1_BASE + ESM_CPU_O_INTR_EN_CLR(0U)) |= 0x3FU;
#endif
}

//*****************************************************************************
//!
//! The default NMI handlers for CPU2 and CPU3, this function is placed at
//! fixed address in section 'nmivector', and CPU1 configures SSU registers
//! of CPU2 and CPU3
//!
//*****************************************************************************
#if (defined(__CPU2__) || defined(__CPU3__))
__attribute__((interrupt("RTINT"), section("nmivector")))
void nmi_vector(void)
{
    Interrupt_NmiStatus nmiStatus;
    //
    //  Clear ESM and EA error flags
    //
    Interrupt_clearEsmEaFlags(&nmiStatus);

    //
    //  Spin forever
    //
    for(;;)
    {
        ;
    }
}
#endif

//*****************************************************************************
//
// Error handling function to be called when an ASSERT is violated
//
//*****************************************************************************
void __error__(const char *filename, uint32_t line)
{
    //
    // An ASSERT condition was evaluated as false. You can use the filename and
    // line parameters to determine what went wrong.
    //
    ESTOP0;
}
