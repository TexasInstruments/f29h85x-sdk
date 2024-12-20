//###########################################################################
//
// FILE:   erad.c
//
// TITLE:  C29x ERAD driver.
//
//###########################################################################
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

#include "erad.h"

//*****************************************************************************
//
// ERAD_configBusComp
//
//*****************************************************************************
void
ERAD_configBusComp(ERAD_BusCompInstance instance,
                                        ERAD_BusComp_Config config_params)
{
    //
    // Check if owner is APPLICATION
    //
    ASSERT(ERAD_getBusCompOwnership(instance) == ERAD_OWNER_APPLICATION);

    //
    // Check if the bus comparator is in ERAD_STATE_IDLE
    //
    ASSERT(ERAD_getBusCompStatus(instance) == ERAD_STATE_IDLE);

    //
    // Write into necessary registers to configure the bus comparator
    //
    HWREG(ERAD_BASE + ERAD_O_EBC_MASKH((uint32_t)instance)) =
                                        (uint32_t)(config_params.mask >> 32U);
    HWREG(ERAD_BASE + ERAD_O_EBC_MASKL((uint32_t)instance)) =
                                            (uint32_t)config_params.mask;
    HWREG(ERAD_BASE + ERAD_O_EBC_REFL((uint32_t)instance))  =
                                            (uint32_t)config_params.reference;
    HWREG(ERAD_BASE + ERAD_O_EBC_REFH((uint32_t)instance))  =
                                   (uint32_t)(config_params.reference >> 32U);


    //
    // Set the comparison mode and the CPU bus to be monitored
    // Enable interrupt and CPU halt if specified in the parameters
    //
    HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) =
        ((uint16_t)config_params.comp_mode   << ERAD_EBC_CNTL_COMP_MODE_S) |
        ((uint16_t)config_params.bus_sel     << ERAD_EBC_CNTL_BUS_SEL_S)   ;

    if(config_params.enable_int || config_params.enable_nmi)
    {
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) |=
                                                ERAD_EBC_CNTL_INTERRUPT;
        if(config_params.enable_nmi)
        {
            HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) |=
                                                ERAD_EBC_CNTL_NMI_EN;
        }
    }

    if(config_params.enable_stop)
    {
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) |=
                                                        ERAD_EBC_CNTL_HALT;
    }

    //
    // Configure stack qualification.
    // This is relevant only for data read and data write address comparison.
    // These settings are ignored for busses other than data read / data write.
    //
    if(config_params.enable_stack_qual)
    {
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) |=
                                                    ERAD_EBC_CNTL_STACK_QUAL;
    }
    if(config_params.enable_spsel_match)
    {
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) |=
                                                ERAD_EBC_CNTL_SPSEL_MATCH_EN;
        HWREG(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) =
                    (HWREG(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) &
                    ~ERAD_EBC_CNTL_SPSEL_M) |
                    (config_params.spsel << ERAD_EBC_CNTL_SPSEL_S);
    }

}

//*****************************************************************************
//
// ERAD_configCounterInCountingMode
//
//*****************************************************************************
void
ERAD_configCounterInCountingMode(ERAD_CounterInstance instance,
                                 ERAD_Counter_Config config_params)
{
    //
    // Check if owner is APPLICATION or NO_OWNER
    //
    ASSERT(ERAD_getCounterOwnership(instance) == ERAD_OWNER_APPLICATION);

    //
    // Check if the counter is in ERAD_STATE_IDLE
    //
    ASSERT(ERAD_getCounterStatus(instance) == ERAD_STATE_IDLE);

    //
    // Write into registers to configure the counter
    //
    HWREG(ERAD_BASE + ERAD_O_SEC_REF((uint32_t)instance)) =
                                                    config_params.reference;

    if(config_params.event == ERAD_EVENT_NO_EVENT)
    {
        //
        // If ERAD_EVENT_NO_EVENT is selected, clear the counter input select
        // enable bit. The counter will count CPU cycles.
        //
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) &=
                                      ~(uint16_t)ERAD_SEC_CNTL_CNT_INP_SEL_EN;
    }
    else
    {
        //
        // For any other value, set the event to be counted and counter input
        // select enable bit.
        //
        HWREGH(ERAD_BASE + ERAD_O_SEC_INPUT_SEL1((uint32_t)instance)) =
          (((uint16_t)config_params.event << ERAD_SEC_INPUT_SEL1_CNT_INP_SEL_S)
                                          & ERAD_SEC_INPUT_SEL1_CNT_INP_SEL_M);

        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) |=
                                                  ERAD_SEC_CNTL_CNT_INP_SEL_EN;
    }

    //
    // Set the counter in Normal count mode
    // Set the event mode as Rising edge or Active
    // Enable interrupt, CPU halt and reset on match if specified in the
    // parameters
    //
    HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) =
      (HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) &
                          (~(uint16_t)(ERAD_SEC_CNTL_START_STOP_CUMULATIVE |
                                       ERAD_SEC_CNTL_INTERRUPT             |
                                       ERAD_SEC_CNTL_HALT                  |
                                       ERAD_SEC_CNTL_NMI_EN                |
                                       ERAD_SEC_CNTL_RST_ON_MATCH          |
                                       ERAD_SEC_CNTL_EDGE_LEVEL            |
                                       ERAD_SEC_CNTL_START_STOP_MODE)))    |
      ((uint16_t)config_params.enable_int  << ERAD_SEC_CNTL_INTERRUPT_S)   |
      ((uint16_t)config_params.enable_nmi  << ERAD_SEC_CNTL_NMI_S)         |
      ((uint16_t)config_params.enable_stop  << ERAD_SEC_CNTL_HALT_S)       |
      ((uint16_t)config_params.event_mode   << ERAD_SEC_CNTL_EDGE_LEVEL_S) |
      ((uint16_t)config_params.rst_on_match << ERAD_SEC_CNTL_RST_ON_MATCH_S);
}

//*****************************************************************************
//
// ERAD_configCounterInStartStopMode
//
//*****************************************************************************
void
ERAD_configCounterInStartStopMode(ERAD_CounterInstance instance,
                                  ERAD_Counter_Config config_params,
                                  ERAD_Counter_Input_Event start_event,
                                  ERAD_Counter_Input_Event stop_event)
{
    //
    // Check if owner is APPLICATION or NO_OWNER
    //
    ASSERT(ERAD_getCounterOwnership(instance) == ERAD_OWNER_APPLICATION);

    //
    // Check if the counter is in IDLE state
    //
    ASSERT(ERAD_getCounterStatus(instance) == ERAD_STATE_IDLE);

    //
    // Write into registers to configure the counter
    //
    HWREG(ERAD_BASE + ERAD_O_SEC_REF((uint32_t)instance)) =
                                                    config_params.reference;

    if(config_params.event == ERAD_EVENT_NO_EVENT)
    {
        //
        // If ERAD_EVENT_NO_EVENT is selected, clear the counter input select
        // enable bit. The counter will count CPU cycles.
        // Set start and stop events
        //
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) &=
                                      ~(uint16_t)ERAD_SEC_CNTL_CNT_INP_SEL_EN;

        HWREG(ERAD_BASE + ERAD_O_SEC_INPUT_SEL2((uint32_t)instance)) =
                ((uint32_t)start_event << ERAD_SEC_INPUT_SEL2_STA_INP_SEL_S) |
                ((uint32_t)stop_event << ERAD_SEC_INPUT_SEL2_STO_INP_SEL_S);
    }
    else
    {
        //
        // For any other value, set the counter input select enable bit and
        // configure the counter input, start event and stop event
        //
        //
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) |=
                                                ERAD_SEC_CNTL_CNT_INP_SEL_EN;

        HWREGH(ERAD_BASE + ERAD_O_SEC_INPUT_SEL1((uint32_t)instance)) =
          ((uint16_t)config_params.event << ERAD_SEC_INPUT_SEL1_CNT_INP_SEL_S);

        HWREG(ERAD_BASE + ERAD_O_SEC_INPUT_SEL2((uint32_t)instance)) =
                ((uint32_t)start_event << ERAD_SEC_INPUT_SEL2_STA_INP_SEL_S) |
                ((uint32_t)stop_event << ERAD_SEC_INPUT_SEL2_STO_INP_SEL_S);
    }

    //
    // Set the counter in Normal count mode
    // Set the event mode as Rising edge or Active
    // Enable interrupt, CPU halt and reset on match if specified in the
    // parameters
    //
    HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) =
      (HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) &
                          (~(uint16_t)(ERAD_SEC_CNTL_START_STOP_CUMULATIVE |
                                       ERAD_SEC_CNTL_INTERRUPT             |
                                       ERAD_SEC_CNTL_NMI_EN                |
                                       ERAD_SEC_CNTL_HALT                  |
                                       ERAD_SEC_CNTL_RST_ON_MATCH          |
                                       ERAD_SEC_CNTL_EDGE_LEVEL)))           |
      ERAD_SEC_CNTL_START_STOP_MODE                                          |
      ((uint16_t)config_params.enable_int  << ERAD_SEC_CNTL_INTERRUPT_S)     |
      ((uint16_t)config_params.enable_nmi  << ERAD_SEC_CNTL_NMI_S)           |
      ((uint16_t)config_params.enable_stop  << ERAD_SEC_CNTL_HALT_S)         |
      ((uint16_t)config_params.event_mode   << ERAD_SEC_CNTL_EDGE_LEVEL_S)   |
      ((uint16_t)config_params.rst_on_match << ERAD_SEC_CNTL_RST_ON_MATCH_S);
}

//*****************************************************************************
//
// ERAD_configCounterInCumulativeMode
//
//*****************************************************************************
void
ERAD_configCounterInCumulativeMode(ERAD_CounterInstance instance,
                                   ERAD_Counter_Config config_params,
                                   ERAD_Counter_Input_Event start_event,
                                   ERAD_Counter_Input_Event stop_event)
{
    //
    // Check if owner is APPLICATION or NO_OWNER
    //
    ASSERT(ERAD_getCounterOwnership(instance) == ERAD_OWNER_APPLICATION);

    //
    // Check if the counter is in IDLE state
    //
    ASSERT(ERAD_getCounterStatus(instance) == ERAD_STATE_IDLE);

    //
    // Write into registers to configure the counter
    //
    HWREG(ERAD_BASE + ERAD_O_SEC_REF((uint32_t)instance)) =
                                                config_params.reference;

    if(config_params.event == ERAD_EVENT_NO_EVENT)
    {
        //
        // If ERAD_EVENT_NO_EVENT is selected, clear the counter input select
        // enable bit. The counter will count CPU cycles.
        // Set start and stop events
        //
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) &=
                                     ~(uint16_t)ERAD_SEC_CNTL_CNT_INP_SEL_EN;

        HWREG(ERAD_BASE + ERAD_O_SEC_INPUT_SEL2((uint32_t)instance)) =
            ((uint16_t)start_event << ERAD_SEC_INPUT_SEL2_STA_INP_SEL_S) |
            ((uint32_t)stop_event << ERAD_SEC_INPUT_SEL2_STO_INP_SEL_S);

    }
    else
    {
        //
        // For any other value, set the counter input select enable bit and
        // configure the counter input, start event and stop event,
        //
        //
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) |=
                                                ERAD_SEC_CNTL_CNT_INP_SEL_EN;

        HWREGH(ERAD_BASE + ERAD_O_SEC_INPUT_SEL1((uint32_t)instance)) =
          ((uint16_t)config_params.event << ERAD_SEC_INPUT_SEL1_CNT_INP_SEL_S);

        HWREG(ERAD_BASE + ERAD_O_SEC_INPUT_SEL2((uint32_t)instance)) =
           ((uint16_t)start_event << ERAD_SEC_INPUT_SEL2_STA_INP_SEL_S) |
            ((uint32_t)stop_event << ERAD_SEC_INPUT_SEL2_STO_INP_SEL_S);

    }

    //
    // Set the counter in Normal count mode
    // Set the event mode as Rising edge or Active
    // Enable interrupt, CPU halt and reset on match if specified in the
    // parameters
    //
    HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) =
        (HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) &
                                (~(uint16_t)(ERAD_SEC_CNTL_INTERRUPT    |
                                             ERAD_SEC_CNTL_NMI_EN       |
                                             ERAD_SEC_CNTL_HALT         |
                                             ERAD_SEC_CNTL_RST_ON_MATCH |
                                             ERAD_SEC_CNTL_EDGE_LEVEL)))     |
        ERAD_SEC_CNTL_START_STOP_MODE                                        |
        ERAD_SEC_CNTL_START_STOP_CUMULATIVE                                  |
        ((uint16_t)config_params.enable_int  << ERAD_SEC_CNTL_INTERRUPT_S)   |
        ((uint16_t)config_params.enable_nmi  << ERAD_SEC_CNTL_NMI_S)         |
        ((uint16_t)config_params.enable_stop  << ERAD_SEC_CNTL_HALT_S)       |
        ((uint16_t)config_params.event_mode   << ERAD_SEC_CNTL_EDGE_LEVEL_S) |
        ((uint16_t)config_params.rst_on_match << ERAD_SEC_CNTL_RST_ON_MATCH_S);
}

//*****************************************************************************
//
// ERAD_configMask
//
//*****************************************************************************
void
ERAD_configMask(ERAD_Mask mask, uint32_t instances, bool enable_int,
                                                        bool enable_nmi)
{
    uint16_t or_mask;

    if((uint32_t)mask < ERAD_MAX_AND_MASK_INSTANCES)
    {
        HWREG(ERAD_BASE + ERAD_O_EVENT_AND_MASK((uint32_t)mask)) = instances;

        if((enable_int == true) || (enable_nmi == true))
        {
            HWREGH(ERAD_BASE + ERAD_O_AND_MASK_CTL((uint32_t)mask)) |=
                                                ERAD_AND_MASK_CTL_INTERRUPT;
            if(enable_nmi == true)
            {
               HWREGH(ERAD_BASE + ERAD_O_AND_MASK_CTL((uint32_t)mask)) |=
                                                    ERAD_AND_MASK_CTL_NMI_EN;
            }
        }
    }
    else
    {
        or_mask = (uint32_t)mask - ERAD_MAX_AND_MASK_INSTANCES;

        HWREG(ERAD_BASE + ERAD_O_EVENT_OR_MASK((uint32_t)or_mask)) = instances;

        if((enable_int == true) || (enable_nmi == true))
        {
            HWREGH(ERAD_BASE + ERAD_O_OR_MASK_CTL((uint32_t)or_mask)) |=
                                                    ERAD_OR_MASK_CTL_INTERRUPT;
            if(enable_nmi == true)
            {
               HWREGH(ERAD_BASE + ERAD_O_OR_MASK_CTL((uint32_t)or_mask)) |=
                                                    ERAD_OR_MASK_CTL_NMI_EN;
            }
        }
    }
}

//*****************************************************************************
//
// ERAD_profile
//
//*****************************************************************************
void
ERAD_profile(ERAD_Profile_Params config_params)
{
    ERAD_BusComp_Config buscomp1_params, buscomp2_params;
    ERAD_Counter_Config counter_params;

    //
    // Set the ownership of the modules as APPLICATION
    //
    ERAD_setBusCompOwnership(config_params.busComp_instance1,
                                                      ERAD_OWNER_APPLICATION);
    ERAD_setBusCompOwnership(config_params.busComp_instance2,
                                                      ERAD_OWNER_APPLICATION);
    ERAD_setCounterOwnership(config_params.counter_instance,
                                                      ERAD_OWNER_APPLICATION);

    //
    // Disable the modules
    //
    ERAD_disableBusCompModule(config_params.busComp_instance1);
    ERAD_disableBusCompModule(config_params.busComp_instance2);
    ERAD_disableCounterModule(config_params.counter_instance);

    //
    // Clear any previous events
    //
    ERAD_clearBusCompEvent(config_params.busComp_instance1);
    ERAD_clearBusCompEvent(config_params.busComp_instance2);

    //
    // Clear any previous events and overflow
    //
    ERAD_clearCounterEvent(config_params.counter_instance);
    ERAD_clearCounterOverflow(config_params.counter_instance);

    //
    // Configure the first bus comparator
    // No interrupt or CPU halt. Compare for equality. No mask.
    // Reference is the address of the first instruction
    //
    buscomp1_params.bus_sel = config_params.bus_sel;
    buscomp1_params.comp_mode = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp1_params.enable_stop = false;
    buscomp1_params.enable_int = false;
    buscomp1_params.enable_nmi = false;
    buscomp1_params.mask = 0x0U;
    buscomp1_params.reference = config_params.start_address;
    buscomp1_params.enable_stack_qual = false;
    buscomp1_params.enable_spsel_match = false;
    buscomp1_params.spsel = 0x0U;
    ERAD_configBusComp(config_params.busComp_instance1, buscomp1_params);

    //
    // Configure the second bus comparator
    // No interrupt or CPU halt. Compare for equality. No mask.
    // Reference is the address of the last instruction
    //
    buscomp2_params.bus_sel = config_params.bus_sel;
    buscomp2_params.comp_mode = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp2_params.enable_stop = false;
    buscomp2_params.enable_int = false;
    buscomp2_params.enable_nmi = false;
    buscomp2_params.mask = 0x0U;
    buscomp2_params.reference = config_params.end_address;
    buscomp2_params.enable_stack_qual = false;
    buscomp2_params.enable_spsel_match = false;
    buscomp2_params.spsel = 0x0U;
    ERAD_configBusComp(config_params.busComp_instance2, buscomp2_params);

    //
    // Configure the counter
    // No interrupt, no CPU halt, no reset on match, no reference.
    // Counting the number of CPU cycles
    // Start event is the first EBC and stop is the second
    //
    counter_params.enable_int = false;
    counter_params.enable_nmi = false;
    counter_params.enable_stop = false;
    counter_params.rst_on_match = false;
    counter_params.reference = 0xFFFFFFFFU;
    counter_params.event_mode = ERAD_COUNTER_MODE_ACTIVE;
    counter_params.event = ERAD_EVENT_NO_EVENT;
    ERAD_Counter_Input_Event start =
                    (ERAD_Counter_Input_Event)config_params.busComp_instance1;
    ERAD_Counter_Input_Event stop =
                    (ERAD_Counter_Input_Event)config_params.busComp_instance2;
    ERAD_configCounterInStartStopMode(config_params.counter_instance,
                                        counter_params, start, stop);

    //
    // Enable the modules
    //
    ERAD_enableBusCompModule(config_params.busComp_instance1);
    ERAD_enableBusCompModule(config_params.busComp_instance2);
    ERAD_enableCounterModule(config_params.counter_instance);
}

//*****************************************************************************
//
// ERAD_enableInterruptOnAddressHit
//
//*****************************************************************************
void
ERAD_enableInterruptOnAddressHit(ERAD_AddressHit_Params config_params,
                                 ERAD_BusCompInstance instance)
{
    ERAD_BusComp_Config buscomp_params;

    //
    // Set the ownership of the modules as APPLICATION
    //
    ERAD_setBusCompOwnership(instance, ERAD_OWNER_APPLICATION);

    //
    // Disable the bus comparator
    //
    ERAD_disableBusCompModule(instance);

    //
    // Clear any previous events
    //
    ERAD_clearBusCompEvent(instance);

    //
    // Set the address and mask. Disable CPU halt
    // and enable Interrupt
    //
    buscomp_params.reference = config_params.address;
    buscomp_params.mask = config_params.mask;
    buscomp_params.enable_stop = false;
    buscomp_params.enable_int = true;
    buscomp_params.enable_nmi = false;

    //
    // Comparison mode is set to equality and the bus to be
    // monitored is the Virtual Program Counter
    //
    buscomp_params.comp_mode = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_params.bus_sel = config_params.bus_sel;

    //
    // Configure the Stack qualification
    //
    buscomp_params.enable_stack_qual = false;
    buscomp_params.enable_spsel_match = false;
    buscomp_params.spsel = 0x0U;

    //
    // Configure the bus comparator
    //
    ERAD_configBusComp(instance, buscomp_params);

    //
    // Enable the bus comparator
    //
    ERAD_enableBusCompModule(instance);
}

//*****************************************************************************
//
// ERAD_countEventHits
//
//*****************************************************************************
void
ERAD_countAddressHits(ERAD_AddressHit_Params config_params,
                      ERAD_BusCompInstance busComp_instance,
                      ERAD_CounterInstance counter_instance)
{
    ERAD_BusComp_Config buscomp_params;
    ERAD_Counter_Config counter_params;

    //
    // Set the ownership of the modules as APPLICATION
    //
    ERAD_setBusCompOwnership(busComp_instance, ERAD_OWNER_APPLICATION);
    ERAD_setCounterOwnership(counter_instance, ERAD_OWNER_APPLICATION);

    //
    // Disable the modules
    //
    ERAD_disableBusCompModule(busComp_instance);
    ERAD_disableCounterModule(counter_instance);

    //
    // Clear any previous events and overflows
    //
    ERAD_clearBusCompEvent(busComp_instance);
    ERAD_clearCounterEvent(counter_instance);
    ERAD_clearCounterOverflow(counter_instance);

    //
    // Configure the bus comparator
    // No interrupt or CPU halt. Compare for equality. No mask.
    // Reference is the address of the instruction to be counted
    // Bus to be monitored is specified in the bus argument
    //
    buscomp_params.reference = config_params.address;
    buscomp_params.mask = config_params.mask;
    buscomp_params.comp_mode = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_params.enable_stop = false;
    buscomp_params.bus_sel = config_params.bus_sel;
    buscomp_params.enable_int = false;
    buscomp_params.enable_nmi = false;
    buscomp_params.enable_stack_qual = false;
    buscomp_params.enable_spsel_match = false;
    buscomp_params.spsel = 0x0U;
    ERAD_configBusComp(busComp_instance, buscomp_params);

    //
    // Configure the counter
    // No interrupt, no CPU halt, no reset on match, no reference.
    // Counting the number of rising edges of the bus comparator event
    //
    counter_params.enable_int = false;
    counter_params.enable_nmi = false;
    counter_params.enable_stop = false;
    counter_params.event_mode = ERAD_COUNTER_MODE_RISING_EDGE;
    counter_params.rst_on_match = false;
    counter_params.reference = 0xFFFFFFFFU;
    counter_params.event = (ERAD_Counter_Input_Event)busComp_instance;
    ERAD_configCounterInCountingMode(counter_instance, counter_params);

    //
    // Enable the modules
    //
    ERAD_enableBusCompModule(busComp_instance);
    ERAD_enableCounterModule(counter_instance);
}

//
// End of file
//
