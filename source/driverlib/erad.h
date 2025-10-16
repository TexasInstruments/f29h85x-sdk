//###########################################################################
//
// FILE:   erad.h
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

#ifndef ERAD_H
#define ERAD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup erad_api ERAD
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_erad.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"


//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define ERAD_MAX_EBC_INSTANCES      8U
#define ERAD_MAX_SEC_INSTANCES      4U
#define ERAD_MAX_AND_MASK_INSTANCES 4U
#define ERAD_MAX_OR_MASK_INSTANCES  4U

//
// Macros for bit positions of some register bit fields
//
#define ERAD_EBC_CNTL_INTERRUPT_S     0x07U
#define ERAD_EBC_CNTL_NMI_EN_S        0x08U

#define ERAD_SEC_CNTL_EDGE_LEVEL_S    0x01U
#define ERAD_SEC_CNTL_RST_ON_MATCH_S  0x04U
#define ERAD_SEC_CNTL_HALT_S          0x05U
#define ERAD_SEC_CNTL_INTERRUPT_S     0x06U
#define ERAD_SEC_CNTL_NMI_S           0x07U


//*****************************************************************************
//
//! Values that can be passed to ERAD_configMask() as \e instances parameter.
//
//*****************************************************************************
#define ERAD_INST_BUSCOMP0  0x00000001UL   //!< Bus Comparator 0 (EBC0)
#define ERAD_INST_BUSCOMP1  0x00000002UL   //!< Bus Comparator 1 (EBC1)
#define ERAD_INST_BUSCOMP2  0x00000004UL   //!< Bus Comparator 2 (EBC2)
#define ERAD_INST_BUSCOMP3  0x00000008UL   //!< Bus Comparator 3 (EBC3)
#define ERAD_INST_BUSCOMP4  0x00000010UL   //!< Bus Comparator 4 (EBC4)
#define ERAD_INST_BUSCOMP5  0x00000020UL   //!< Bus Comparator 5 (EBC5)
#define ERAD_INST_BUSCOMP6  0x00000040UL   //!< Bus Comparator 6 (EBC6)
#define ERAD_INST_BUSCOMP7  0x00000080UL   //!< Bus Comparator 7 (EBC7)
#define ERAD_INST_COUNTER0  0x00010000UL   //!< Counter 0 (SEC0)
#define ERAD_INST_COUNTER1  0x00020000UL   //!< Counter 1 (SEC1)
#define ERAD_INST_COUNTER2  0x00040000UL   //!< Counter 2 (SEC2)
#define ERAD_INST_COUNTER3  0x00080000UL   //!< Counter 3 (SEC3)

//*****************************************************************************
//
//! Values that can be passed to ERAD_setCounterInputConditioning() as options
//! parameter.
//
//*****************************************************************************
#define ERAD_INPUT_INVERT_DISABLE 0x00U   //!< Do not invert the input
#define ERAD_INPUT_INVERT_ENABLE  0x01U   //!< Invert the input

//*****************************************************************************
//
//! Values that can be passed to ERAD_initModule() as \e owner parameter to
//! set owner of ERAD.
//
//*****************************************************************************
typedef enum
{
    ERAD_OWNER_NOOWNER     = 0,     //!< No owner
    ERAD_OWNER_DEBUGGER    = 1,     //!< Debugger owned
    ERAD_OWNER_APPLICATION = 2,     //!< Application owned
} ERAD_Owner;

//*****************************************************************************
//
//! Values that can are returned by ERAD_getBusCompStatus() and
//! ERAD_getCounterStatus() to indicate the state of the respective module.
//
//*****************************************************************************
typedef enum
{
    ERAD_STATE_IDLE      = 0,   //!< Module is idle
    ERAD_STATE_ENABLED   = 2,   //!< Module is enabled
    ERAD_STATE_COMPLETED = 3    //!< Module was enabled and an event occurred
} ERAD_Status;

//*****************************************************************************
//
//! Values that can be passed to ERAD_configBusComp() and ERAD_profile()
//! as \e config_params.bus_sel parameter to choose which CPU bus to monitor.
//
//*****************************************************************************
typedef enum
{
    ERAD_BUSCOMP_BUS_PAB           = 0,  //!< Use the Program Address Bus (PAB)
    ERAD_BUSCOMP_BUS_DWAB          = 1,  //!< Use the Data Write Address Bus
                                         //!  (DWAB)
    ERAD_BUSCOMP_BUS_DRAB_W        = 5,  //!< Use the Data Read Address Bus
                                         //!  (DRAB_W)
    ERAD_BUSCOMP_BUS_DRAB1_W       = 6,  //!< Use the Data Read Address Bus
                                         //!  (DRAB1_W)
    ERAD_BUSCOMP_BUS_DRAB2_W       = 7,  //!< Use the Data Read Address Bus
                                         //!  (DRAB2_W)
    ERAD_BUSCOMP_BUS_DWDB          = 8,  //!< Use the Data Write Data Bus
                                         //!  (DWDB)
    ERAD_BUSCOMP_BUS_DRDB          = 9,  //!< Use the Data Read Data Bus
                                         //!  (DRDB)
    ERAD_BUSCOMP_BUS_DRDB1         = 10, //!< Use the Data Read Data Bus
                                         //!  (DRDB1)
    ERAD_BUSCOMP_BUS_DRDB2         = 11, //!< Use the Data Read Data Bus
                                         //!  (DRDB2)
    ERAD_BUSCOMP_BUS_VPC_I_ALIGNED = 12, //!< Use VPC Instruction aligned
                                         //!  match
    ERAD_BUSCOMP_BUS_VPC_W_ALIGNED = 14, //!< Use VPC Write aligned match
} ERAD_BusComp_Bus_Select;

//*****************************************************************************
//
//! Values that can be passed to ERAD_configBusComp() and ERAD_profile()
//! as \e config_params.comp_mode to indicate what kind of comparison to use
//! for the bus comparators.
//
//*****************************************************************************
typedef enum
{
    ERAD_BUSCOMP_COMPMODE_EQ = 0,  //!< Check for equality, use a mask value
    ERAD_BUSCOMP_COMPMODE_GT = 4,  //!< Check for greater than
    ERAD_BUSCOMP_COMPMODE_GE = 5,  //!< Check for greater than or equal to
    ERAD_BUSCOMP_COMPMODE_LT = 6,  //!< Check for lesser than
    ERAD_BUSCOMP_COMPMODE_LE = 7,  //!< Check for lesser than or equal to
} ERAD_BusComp_Comp_Mode;

//*****************************************************************************
//
//! Values that can be passed to ERAD_configCounterInStartStopMode()
//! and ERAD_configCounterInCountingMode() as \e config_params.event_mode to
//! indicate whether to count rising edges or the number of CPU clock cycles an
//! is active.
//
//*****************************************************************************
typedef enum
{
    ERAD_COUNTER_MODE_ACTIVE      = 0,     //!< Count number of CPU
                                           //!  Cycles event is active for
    ERAD_COUNTER_MODE_RISING_EDGE = 1      //!< Count number of Rising
                                           //!  Edges of event
} ERAD_Counter_Event_Mode;

//*****************************************************************************
//
//! Values that can be passed to ERAD_configCounterInStartStopMode()
//! and ERAD_configCounterInCountingMode() as \e config_params.event to
//! indicate what event to consider as input. Also may be passed to
//! ERAD_configCounterInStartStopMode() as \e start_event and \e stop_event
//! to indicate start and stop events for the counter.
//
//*****************************************************************************
typedef enum
{
	ERAD_EVENT_EBC0		 = 0,	//!EVENT EBC0
	ERAD_EVENT_EBC1		 = 1,	//!EVENT EBC1
	ERAD_EVENT_EBC2		 = 2,	//!EVENT EBC2
	ERAD_EVENT_EBC3		 = 3,	//!EVENT EBC3
	ERAD_EVENT_EBC4		 = 4,	//!EVENT EBC4
	ERAD_EVENT_EBC5		 = 5,	//!EVENT EBC5
	ERAD_EVENT_EBC6		 = 6,	//!EVENT EBC6
	ERAD_EVENT_EBC7		 = 7,	//!EVENT EBC7
	ERAD_EVENT_COUNTER0_EVENT		 = 8,	//!EVENT COUNTER0 EVENT
	ERAD_EVENT_COUNTER1_EVENT		 = 9,	//!EVENT COUNTER1 EVENT
	ERAD_EVENT_COUNTER2_EVENT		 = 10,	//!EVENT COUNTER2 EVENT
	ERAD_EVENT_COUNTER3_EVENT		 = 11,	//!EVENT COUNTER3 EVENT
	ERAD_EVENT_ERAD_OR_MASK0		 = 12,	//!EVENT ERAD OR MASK0
	ERAD_EVENT_ERAD_OR_MASK1		 = 13,	//!EVENT ERAD OR MASK1
	ERAD_EVENT_ERAD_OR_MASK2		 = 14,	//!EVENT ERAD OR MASK2
	ERAD_EVENT_ERAD_OR_MASK3		 = 15,	//!EVENT ERAD OR MASK3
	ERAD_EVENT_ERAD_AND_MASK0		 = 16,	//!EVENT ERAD AND MASK0
	ERAD_EVENT_ERAD_AND_MASK1		 = 17,	//!EVENT ERAD AND MASK1
	ERAD_EVENT_ERAD_AND_MASK2		 = 18,	//!EVENT ERAD AND MASK2
	ERAD_EVENT_ERAD_AND_MASK3		 = 19,	//!EVENT ERAD AND MASK3
	ERAD_EVENT_PIPE_INT		 = 20,	//!EVENT PIPE INT
	ERAD_EVENT_PIPE_RTINT		 = 21,	//!EVENT PIPE RTINT
	ERAD_EVENT_PIPE_NMI		 = 22,	//!EVENT PIPE NMI
	ERAD_EVENT_CPU1_TIMER0_INT		 = 23,	//!CPU1 TIMER0 Interrupt
	ERAD_EVENT_CPU1_TIMER1_INT		 = 24,	//!CPU1 TIMER1 Interrupt
	ERAD_EVENT_CPU1_TIMER2_INT		 = 25,	//!CPU1 TIMER2 Interrupt
	ERAD_EVENT_CPU2_TIMER0_INT		 = 26,	//!CPU2 TIMER0 Interrupt
	ERAD_EVENT_CPU2_TIMER1_INT		 = 27,	//!CPU2 TIMER1 Interrupt
	ERAD_EVENT_CPU2_TIMER2_INT		 = 28,	//!CPU2 TIMER2 Interrupt
	ERAD_EVENT_CPU3_TIMER0_INT		 = 29,	//!CPU3 TIMER0 Interrupt
	ERAD_EVENT_CPU3_TIMER1_INT		 = 30,	//!CPU3 TIMER1 Interrupt
	ERAD_EVENT_CPU3_TIMER2_INT		 = 31,	//!CPU3 TIMER2 Interrupt
	ERAD_EVENT_RTDMA1_CH1INT		 = 32,	//!EVENT RTDMA1 CH1INT
	ERAD_EVENT_RTDMA1_CH2INT		 = 33,	//!EVENT RTDMA1 CH2INT
	ERAD_EVENT_RTDMA1_CH3INT		 = 34,	//!EVENT RTDMA1 CH3INT
	ERAD_EVENT_RTDMA1_CH4INT		 = 35,	//!EVENT RTDMA1 CH4INT
	ERAD_EVENT_RTDMA1_CH5INT		 = 36,	//!EVENT RTDMA1 CH5INT
	ERAD_EVENT_RTDMA1_CH6INT		 = 37,	//!EVENT RTDMA1 CH6INT
	ERAD_EVENT_RTDMA1_CH7INT		 = 38,	//!EVENT RTDMA1 CH7INT
	ERAD_EVENT_RTDMA1_CH8INT		 = 39,	//!EVENT RTDMA1 CH8INT
	ERAD_EVENT_RTDMA1_CH9INT		 = 40,	//!EVENT RTDMA1 CH9INT
	ERAD_EVENT_RTDMA1_CH10INT		 = 41,	//!EVENT RTDMA1 CH10INT
	ERAD_EVENT_ADCAEVTINT		 = 42,	//!EVENT ADCAEVTINT
	ERAD_EVENT_ADCBEVTINT		 = 43,	//!EVENT ADCBEVTINT
	ERAD_EVENT_ADCCEVTINT		 = 44,	//!EVENT ADCCEVTINT
	ERAD_EVENT_ADCDEVTINT		 = 45,	//!EVENT ADCDEVTINT
	ERAD_EVENT_ADCEEVTINT		 = 46,	//!EVENT ADCEEVTINT
	ERAD_EVENT_ADCSOCA		 = 47,	//!EVENT ADCSOCA
	ERAD_EVENT_ADCSOCB		 = 48,	//!EVENT ADCSOCB
	ERAD_EVENT_RTDMA2_CH1INT		 = 49,	//!EVENT RTDMA2 CH1INT
	ERAD_EVENT_RTDMA2_CH2INT		 = 50,	//!EVENT RTDMA2 CH2INT
	ERAD_EVENT_RTDMA2_CH3INT		 = 51,	//!EVENT RTDMA2 CH3INT
	ERAD_EVENT_RTDMA2_CH4INT		 = 52,	//!EVENT RTDMA2 CH4INT
	ERAD_EVENT_RTDMA2_CH5INT		 = 53,	//!EVENT RTDMA2 CH5INT
	ERAD_EVENT_RTDMA2_CH6INT		 = 54,	//!EVENT RTDMA2 CH6INT
	ERAD_EVENT_RTDMA2_CH7INT		 = 55,	//!EVENT RTDMA2 CH7INT
	ERAD_EVENT_RTDMA2_CH8INT		 = 56,	//!EVENT RTDMA2 CH8INT
	ERAD_EVENT_RTDMA2_CH9INT		 = 57,	//!EVENT RTDMA2 CH9INT
	ERAD_EVENT_RTDMA2_CH10INT		 = 58,	//!EVENT RTDMA2 CH10INT
	ERAD_EVENT_EPWMXBAR_OUT1		 = 59,	//!EVENT EPWMXBAR OUT1
	ERAD_EVENT_EPWMXBAR_OUT2		 = 60,	//!EVENT EPWMXBAR OUT2
	ERAD_EVENT_EPWMXBAR_OUT3		 = 61,	//!EVENT EPWMXBAR OUT3
	ERAD_EVENT_EPWMXBAR_OUT4		 = 62,	//!EVENT EPWMXBAR OUT4
	ERAD_EVENT_EPWMXBAR_OUT5		 = 63,	//!EVENT EPWMXBAR OUT5
	ERAD_EVENT_EPWMXBAR_OUT6		 = 64,	//!EVENT EPWMXBAR OUT6
	ERAD_EVENT_EPWMXBAR_OUT7		 = 65,	//!EVENT EPWMXBAR OUT7
	ERAD_EVENT_EPWMXBAR_OUT8		 = 66,	//!EVENT EPWMXBAR OUT8
	ERAD_EVENT_INPUTXBAR1		 = 67,	//!EVENT INPUTXBAR1
	ERAD_EVENT_INPUTXBAR2		 = 68,	//!EVENT INPUTXBAR2
	ERAD_EVENT_INPUTXBAR3		 = 69,	//!EVENT INPUTXBAR3
	ERAD_EVENT_INPUTXBAR4		 = 70,	//!EVENT INPUTXBAR4
	ERAD_EVENT_INPUTXBAR5		 = 71,	//!EVENT INPUTXBAR5
	ERAD_EVENT_INPUTXBAR6		 = 72,	//!EVENT INPUTXBAR6
	ERAD_EVENT_INPUTXBAR7		 = 73,	//!EVENT INPUTXBAR7
	ERAD_EVENT_INPUTXBAR8		 = 74,	//!EVENT INPUTXBAR8
	ERAD_EVENT_INPUTXBAR9		 = 75,	//!EVENT INPUTXBAR9
	ERAD_EVENT_INPUTXBAR10		 = 76,	//!EVENT INPUTXBAR10
	ERAD_EVENT_INPUTXBAR11		 = 77,	//!EVENT INPUTXBAR11
	ERAD_EVENT_INPUTXBAR12		 = 78,	//!EVENT INPUTXBAR12
	ERAD_EVENT_INPUTXBAR13		 = 79,	//!EVENT INPUTXBAR13
	ERAD_EVENT_INPUTXBAR14		 = 80,	//!EVENT INPUTXBAR14
	ERAD_EVENT_INPUTXBAR15		 = 81,	//!EVENT INPUTXBAR15
	ERAD_EVENT_INPUTXBAR16		 = 82,	//!EVENT INPUTXBAR16
	ERAD_EVENT_CMPSS1_CTRIPH_OR_CTRIPL		 = 83,	//!EVENT CMPSS1 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS2_CTRIPH_OR_CTRIPL		 = 84,	//!EVENT CMPSS2 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS3_CTRIPH_OR_CTRIPL		 = 85,	//!EVENT CMPSS3 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS4_CTRIPH_OR_CTRIPL		 = 86,	//!EVENT CMPSS4 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS5_CTRIPH_OR_CTRIPL		 = 87,	//!EVENT CMPSS5 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS6_CTRIPH_OR_CTRIPL		 = 88,	//!EVENT CMPSS6 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS7_CTRIPH_OR_CTRIPL		 = 89,	//!EVENT CMPSS7 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS8_CTRIPH_OR_CTRIPL		 = 90,	//!EVENT CMPSS8 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS9_CTRIPH_OR_CTRIPL		 = 91,	//!EVENT CMPSS9 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS10_CTRIPH_OR_CTRIPL		 = 92,	//!EVENT CMPSS10 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS11_CTRIPH_OR_CTRIPL		 = 93,	//!EVENT CMPSS11 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS12_CTRIPH_OR_CTRIPL		 = 94,	//!EVENT CMPSS12 CTRIPH OR CTRIPL
	ERAD_EVENT_SD1FLT1_COMPH_OR_COMPL		 = 95,	//!EVENT SD1FLT1 COMPH OR COMPL
	ERAD_EVENT_SD1FLT2_COMPH_OR_COMPL		 = 96,	//!EVENT SD1FLT2 COMPH OR COMPL
	ERAD_EVENT_SD1FLT3_COMPH_OR_COMPL		 = 97,	//!EVENT SD1FLT3 COMPH OR COMPL
	ERAD_EVENT_SD1FLT4_COMPH_OR_COMPL		 = 98,	//!EVENT SD1FLT4 COMPH OR COMPL
	ERAD_EVENT_SD2FLT1_COMPH_OR_COMPL		 = 99,	//!EVENT SD2FLT1 COMPH OR COMPL
	ERAD_EVENT_SD2FLT2_COMPH_OR_COMPL		 = 100,	//!EVENT SD2FLT2 COMPH OR COMPL
	ERAD_EVENT_SD2FLT3_COMPH_OR_COMPL		 = 101,	//!EVENT SD2FLT3 COMPH OR COMPL
	ERAD_EVENT_SD2FLT4_COMPH_OR_COMPL		 = 102,	//!EVENT SD2FLT4 COMPH OR COMPL
	ERAD_EVENT_SD3FLT1_COMPH_OR_COMPL		 = 103,	//!EVENT SD3FLT1 COMPH OR COMPL
	ERAD_EVENT_SD3FLT2_COMPH_OR_COMPL		 = 104,	//!EVENT SD3FLT2 COMPH OR COMPL
	ERAD_EVENT_SD3FLT3_COMPH_OR_COMPL		 = 105,	//!EVENT SD3FLT3 COMPH OR COMPL
	ERAD_EVENT_SD3FLT4_COMPH_OR_COMPL		 = 106,	//!EVENT SD3FLT4 COMPH OR COMPL
	ERAD_EVENT_SD4FLT1_COMPH_OR_COMPL		 = 107,	//!EVENT SD4FLT1 COMPH OR COMPL
	ERAD_EVENT_SD4FLT2_COMPH_OR_COMPL		 = 108,	//!EVENT SD4FLT2 COMPH OR COMPL
	ERAD_EVENT_SD4FLT3_COMPH_OR_COMPL		 = 109,	//!EVENT SD4FLT3 COMPH OR COMPL
	ERAD_EVENT_SD4FLT4_COMPH_OR_COMPL		 = 110,	//!EVENT SD4FLT4 COMPH OR COMPL
	ERAD_EVENT_ADCAINT1		 = 111,	//!EVENT ADCAINT1
	ERAD_EVENT_ADCAINT2		 = 112,	//!EVENT ADCAINT2
	ERAD_EVENT_ADCAINT3		 = 113,	//!EVENT ADCAINT3
	ERAD_EVENT_ADCAINT4		 = 114,	//!EVENT ADCAINT4
	ERAD_EVENT_ADCBINT1		 = 115,	//!EVENT ADCBINT1
	ERAD_EVENT_ADCBINT2		 = 116,	//!EVENT ADCBINT2
	ERAD_EVENT_ADCBINT3		 = 117,	//!EVENT ADCBINT3
	ERAD_EVENT_ADCBINT4		 = 118,	//!EVENT ADCBINT4
	ERAD_EVENT_ADCCINT1		 = 119,	//!EVENT ADCCINT1
	ERAD_EVENT_ADCCINT2		 = 120,	//!EVENT ADCCINT2
	ERAD_EVENT_ADCCINT3		 = 121,	//!EVENT ADCCINT3
	ERAD_EVENT_ADCCINT4		 = 122,	//!EVENT ADCCINT4
	ERAD_EVENT_ADCDINT1		 = 123,	//!EVENT ADCDINT1
	ERAD_EVENT_ADCDINT2		 = 124,	//!EVENT ADCDINT2
	ERAD_EVENT_ADCDINT3		 = 125,	//!EVENT ADCDINT3
	ERAD_EVENT_ADCDINT4		 = 126,	//!EVENT ADCDINT4
	ERAD_EVENT_ADCEINT1		 = 127,	//!EVENT ADCEINT1
	ERAD_EVENT_ADCEINT2		 = 128,	//!EVENT ADCEINT2
	ERAD_EVENT_ADCEINT3		 = 129,	//!EVENT ADCEINT3
	ERAD_EVENT_ADCEINT4		 = 130,	//!EVENT ADCEINT4
	ERAD_EVENT_ECAT_PDI_SOF		 = 131,	//!EVENT ECAT PDI SOF
	ERAD_EVENT_ECAT_PDI_EOF		 = 132,	//!EVENT ECAT PDI EOF
	ERAD_EVENT_ECAT_PCI_WD_TRIGGER		 = 133,	//!EVENT ECAT PCI WD TRIGGER
	ERAD_EVENT_ECAT_PDI_UC_IRQ		 = 134,	//!EVENT ECAT PDI UC IRQ
	ERAD_EVENT_ECAT_SYNC_OUT0		 = 135,	//!EVENT ECAT SYNC OUT0
	ERAD_EVENT_ECAT_SYNC_OUT1		 = 136,	//!EVENT ECAT SYNC OUT1
	ERAD_EVENT_ECAT_DRAM_PARITY_ERROR		 = 137,	//!EVENT ECAT DRAM PARITY ERROR
	ERAD_EVENT_INPUTXBAR17		 = 138,	//!EVENT INPUTXBAR17
	ERAD_EVENT_INPUTXBAR18		 = 139,	//!EVENT INPUTXBAR18
	ERAD_EVENT_INPUTXBAR19		 = 140,	//!EVENT INPUTXBAR19
	ERAD_EVENT_INPUTXBAR20		 = 141,	//!EVENT INPUTXBAR20
	ERAD_EVENT_INPUTXBAR21		 = 142,	//!EVENT INPUTXBAR21
	ERAD_EVENT_INPUTXBAR22		 = 143,	//!EVENT INPUTXBAR22
	ERAD_EVENT_INPUTXBAR23		 = 144,	//!EVENT INPUTXBAR23
	ERAD_EVENT_INPUTXBAR24		 = 145,	//!EVENT INPUTXBAR24
	ERAD_EVENT_INPUTXBAR25		 = 146,	//!EVENT INPUTXBAR25
	ERAD_EVENT_INPUTXBAR26		 = 147,	//!EVENT INPUTXBAR26
	ERAD_EVENT_INPUTXBAR27		 = 148,	//!EVENT INPUTXBAR27
	ERAD_EVENT_INPUTXBAR28		 = 149,	//!EVENT INPUTXBAR28
	ERAD_EVENT_INPUTXBAR29		 = 150,	//!EVENT INPUTXBAR29
	ERAD_EVENT_INPUTXBAR30		 = 151,	//!EVENT INPUTXBAR30
	ERAD_EVENT_INPUTXBAR31		 = 152,	//!EVENT INPUTXBAR31
	ERAD_EVENT_INPUTXBAR32		 = 153,	//!EVENT INPUTXBAR32
	ERAD_EVENT_FSIA_DATA_PKT_RCVD		 = 154,	//!EVENT FSIA DATA PKT RCVD
	ERAD_EVENT_FSIA_ERROR_PKT_RCVD		 = 155,	//!EVENT FSIA ERROR PKT RCVD
	ERAD_EVENT_FSIA_PING_PKT_RCVD		 = 156,	//!EVENT FSIA PING PKT RCVD
	ERAD_EVENT_FSIA_PING_FRAME_TAG_MATCH		 = 157,	//!EVENT FSIA PING FRAME TAG MATCH
	ERAD_EVENT_FSIA_DATA_FRAME_TAG_MATCH		 = 158,	//!EVENT FSIA DATA FRAME TAG MATCH
	ERAD_EVENT_FSIA_ERROR_FRAME_TAG_MATCH		 = 159,	//!EVENT FSIA ERROR FRAME TAG MATCH
	ERAD_EVENT_FSIA_FRAME_DONE		 = 160,	//!EVENT FSIA FRAME DONE
	ERAD_EVENT_FSIB_DATA_PKT_RCVD		 = 161,	//!EVENT FSIB DATA PKT RCVD
	ERAD_EVENT_FSIB_ERROR_PKT_RCVD		 = 162,	//!EVENT FSIB ERROR PKT RCVD
	ERAD_EVENT_FSIB_PING_PKT_RCVD		 = 163,	//!EVENT FSIB PING PKT RCVD
	ERAD_EVENT_FSIB_PING_FRAME_TAG_MATCH		 = 164,	//!EVENT FSIB PING FRAME TAG MATCH
	ERAD_EVENT_FSIB_DATA_FRAME_TAG_MATCH		 = 165,	//!EVENT FSIB DATA FRAME TAG MATCH
	ERAD_EVENT_FSIB_ERROR_FRAME_TAG_MATCH		 = 166,	//!EVENT FSIB ERROR FRAME TAG MATCH
	ERAD_EVENT_FSIB_FRAME_DONE		 = 167,	//!EVENT FSIB FRAME DONE
	ERAD_EVENT_FSIC_DATA_PKT_RCVD		 = 168,	//!EVENT FSIC DATA PKT RCVD
	ERAD_EVENT_FSIC_ERROR_PKT_RCVD		 = 169,	//!EVENT FSIC ERROR PKT RCVD
	ERAD_EVENT_FSIC_PING_PKT_RCVD		 = 170,	//!EVENT FSIC PING PKT RCVD
	ERAD_EVENT_FSIC_PING_FRAME_TAG_MATCH		 = 171,	//!EVENT FSIC PING FRAME TAG MATCH
	ERAD_EVENT_FSIC_DATA_FRAME_TAG_MATCH		 = 172,	//!EVENT FSIC DATA FRAME TAG MATCH
	ERAD_EVENT_FSIC_ERROR_FRAME_TAG_MATCH		 = 173,	//!EVENT FSIC ERROR FRAME TAG MATCH
	ERAD_EVENT_FSIC_FRAME_DONE		 = 174,	//!EVENT FSIC FRAME DONE
	ERAD_EVENT_FSID_DATA_PKT_RCVD		 = 175,	//!EVENT FSID DATA PKT RCVD
	ERAD_EVENT_FSID_ERROR_PKT_RCVD		 = 176,	//!EVENT FSID ERROR PKT RCVD
	ERAD_EVENT_FSID_PING_PKT_RCVD		 = 177,	//!EVENT FSID PING PKT RCVD
	ERAD_EVENT_FSID_PING_FRAME_TAG_MATCH		 = 178,	//!EVENT FSID PING FRAME TAG MATCH
	ERAD_EVENT_FSID_DATA_FRAME_TAG_MATCH		 = 179,	//!EVENT FSID DATA FRAME TAG MATCH
	ERAD_EVENT_FSID_ERROR_FRAME_TAG_MATCH		 = 180,	//!EVENT FSID ERROR FRAME TAG MATCH
	ERAD_EVENT_FSID_FRAME_DONE		 = 181,	//!EVENT FSID FRAME DONE
	ERAD_EVENT_TRACE_HIT_EVENT		 = 182,	//!EVENT TRACE HIT EVENT
	ERAD_EVENT_CPU1_LCMCM_ERR		 = 183,	//!CPU1 EVENT LCMCM ERR
	ERAD_EVENT_RTDMA_LCM_CMP_ERR		 = 184,	//!EVENT RTDMA LCM CMP ERR
	ERAD_EVENT_MCANA_EVT0		 = 185,	//!EVENT MCANA EVT0
	ERAD_EVENT_MCANA_EVT1		 = 186,	//!EVENT MCANA EVT1
	ERAD_EVENT_MCANA_EVT2		 = 187,	//!EVENT MCANA EVT2
	ERAD_EVENT_MCANB_EVT0		 = 188,	//!EVENT MCANB EVT0
	ERAD_EVENT_MCANB_EVT1		 = 189,	//!EVENT MCANB EVT1
	ERAD_EVENT_MCANB_EVT2		 = 190,	//!EVENT MCANB EVT2
	ERAD_EVENT_MCANC_EVT0		 = 191,	//!EVENT MCANC EVT0
	ERAD_EVENT_MCANC_EVT1		 = 192,	//!EVENT MCANC EVT1
	ERAD_EVENT_MCANC_EVT2		 = 193,	//!EVENT MCANC EVT2
	ERAD_EVENT_MCAND_EVT0		 = 194,	//!EVENT MCAND EVT0
	ERAD_EVENT_MCAND_EVT1		 = 195,	//!EVENT MCAND EVT1
	ERAD_EVENT_MCAND_EVT2		 = 196,	//!EVENT MCAND EVT2
	ERAD_EVENT_MCANE_EVT0		 = 197,	//!EVENT MCANE EVT0
	ERAD_EVENT_MCANE_EVT1		 = 198,	//!EVENT MCANE EVT1
	ERAD_EVENT_MCANE_EVT2		 = 199,	//!EVENT MCANE EVT2
	ERAD_EVENT_MCANF_EVT0		 = 200,	//!EVENT MCANF EVT0
	ERAD_EVENT_MCANF_EVT1		 = 201,	//!EVENT MCANF EVT1
	ERAD_EVENT_MCANF_EVT2		 = 202,	//!EVENT MCANF EVT2
	ERAD_EVENT_CPUx_INT_ACK		 = 203,	//!CPUx INT ACK
	ERAD_EVENT_CPUx_RTINT_ACK		 = 204,	//!CPUx RTINT ACK
	ERAD_EVENT_CPUx_VIS_R1_PC_VALID		 = 205,	//!CPUx VIS R1 PC VALID
	ERAD_EVENT_CPUx_VIS_W_DR1_REQ		 = 206,	//!CPUx VIS W DR1 REQ
	ERAD_EVENT_CPUx_VIS_W_DR2_REQ		 = 207,	//!CPUx VIS W DR2 REQ
	ERAD_EVENT_CPUx_VIS_W_DW_REQ		 = 208,	//!CPUx VIS W DW REQ
	ERAD_EVENT_CPUx_CPI_D2_READY		 = 209,	//!CPUx CPI D2 READY
	ERAD_EVENT_CPUx_CPI_R1_READY		 = 210,	//!CPUx CPI R1 READY
	ERAD_EVENT_CPUx_CPI_EXE_READY		 = 211,	//!CPUx CPI EXE READY
	ERAD_EVENT_NO_EVENT					 = 256
} ERAD_Counter_Input_Event;

//*****************************************************************************
//
//! Values that can be used to specify the Enhanced Bus Comparator (EBC)
//! Instance.
//
//*****************************************************************************
typedef enum
{
    ERAD_BUSCOMP0 = 0,
    ERAD_BUSCOMP1 = 1,
    ERAD_BUSCOMP2 = 2,
    ERAD_BUSCOMP3 = 3,
    ERAD_BUSCOMP4 = 4,
    ERAD_BUSCOMP5 = 5,
    ERAD_BUSCOMP6 = 6,
    ERAD_BUSCOMP7 = 7,
} ERAD_BusCompInstance;

//*****************************************************************************
//
//! Values that can be used to specify the System Event Counter(SEC) Instance.
//
//*****************************************************************************
typedef enum
{
    ERAD_COUNTER0 = 0,
    ERAD_COUNTER1 = 1,
    ERAD_COUNTER2 = 2,
    ERAD_COUNTER3 = 3,
} ERAD_CounterInstance;

//*****************************************************************************
//
//! Values that can be used to specify the AND, OR Mask Instance.
//
//*****************************************************************************
typedef enum
{
    ERAD_AND_MASK0 = 0,
    ERAD_AND_MASK1 = 1,
    ERAD_AND_MASK2 = 2,
    ERAD_AND_MASK3 = 3,
    ERAD_OR_MASK0  = 4,
    ERAD_OR_MASK1  = 5,
    ERAD_OR_MASK2  = 6,
    ERAD_OR_MASK3  = 7
} ERAD_Mask;

//*****************************************************************************
//
//! Values that can be passed to ERAD_setCounterInputConditioning() as
//! \e input_type parameter. To specify which input to condition.
//
//*****************************************************************************
typedef enum
{
    ERAD_COUNTER_COUNT_INPUT = 0,
    ERAD_COUNTER_START_INPUT = 4,
    ERAD_COUNTER_STOP_INPUT  = 8,
    ERAD_COUNTER_RESET_INPUT = 12
} ERAD_Counter_Input_Type;

//*****************************************************************************
//
//! Values that can be passed to ERAD_setPCTraceMode_Windowed() as
//! \e qualifier parameter
//
//*****************************************************************************
typedef enum
{
    ERAD_PCTRACE_WINDOWED_QUAL_EBC0       = 1,
    ERAD_PCTRACE_WINDOWED_QUAL_EBC1       = 2,
    ERAD_PCTRACE_WINDOWED_QUAL_EBC2       = 3,
    ERAD_PCTRACE_WINDOWED_QUAL_EBC3       = 4,
    ERAD_PCTRACE_WINDOWED_QUAL_EBC4       = 5,
    ERAD_PCTRACE_WINDOWED_QUAL_EBC5       = 6,
    ERAD_PCTRACE_WINDOWED_QUAL_EBC6       = 7,
    ERAD_PCTRACE_WINDOWED_QUAL_EBC7       = 8,
    ERAD_PCTRACE_WINDOWED_QUAL_OR_MASK0   = 9,
    ERAD_PCTRACE_WINDOWED_QUAL_OR_MASK1   = 10,
    ERAD_PCTRACE_WINDOWED_QUAL_OR_MASK2   = 11,
    ERAD_PCTRACE_WINDOWED_QUAL_OR_MASK3   = 12,
    ERAD_PCTRACE_WINDOWED_QUAL_AND_MASK0  = 13,
    ERAD_PCTRACE_WINDOWED_QUAL_AND_MASK1  = 14,
    ERAD_PCTRACE_WINDOWED_QUAL_AND_MASK2  = 15,
    ERAD_PCTRACE_WINDOWED_QUAL_AND_MASK3  = 16
} ERAD_PCTrace_Windowed_Qualifier;

//*****************************************************************************
//
//! Structure that is passed to ERAD_configBusComp() as \e config_params
//! to configure a bus comparator.
//
//*****************************************************************************
typedef struct
{
    uint64_t            mask;           //!< Mask to be used for comparing
    uint64_t            reference;      //!< Reference value to be compared
    ERAD_BusComp_Comp_Mode  comp_mode;  //!< Comparison mode
    bool                enable_int;     //!< Enable Interrupt on event match
    bool                enable_nmi;     //!< Enable NMI
    bool                enable_stop;    //!< Enable CPU halt on event match
    ERAD_BusComp_Bus_Select bus_sel;    //!< Bus to be monitored
    bool                enable_stack_qual;  //!< Enable stack access qualifier
    bool                enable_spsel_match; //!< Enable SPSEL match
    uint32_t            spsel;          //!< Stack pointer Select value to be
                                        //!  used for SPSEL match.
} ERAD_BusComp_Config;

//*****************************************************************************
//
//! Structure that is passed to ERAD_profile() as \e config_params to setup
//! the required modules appropriately for each use case.
//
//*****************************************************************************
typedef struct
{
    uint32_t                start_address;  //!< Start address
    uint32_t                end_address;    //!< End address
    ERAD_BusComp_Bus_Select bus_sel;        //!< Bus to be monitored
    ERAD_BusCompInstance    busComp_instance1;  //!< EBCs to be used
    ERAD_BusCompInstance    busComp_instance2;  //!< EBCs to be used
    ERAD_CounterInstance    counter_instance;   //!< SEC to be used
} ERAD_Profile_Params;

//*****************************************************************************
//
//! Structure that is passed to ERAD_configCounterInStartStopMode() and
//! ERA_configCounterInCountingMode() as \e config_params to setup a
//! counter appropriately.
//
//*****************************************************************************
typedef struct
{
    ERAD_Counter_Input_Event event;        //!< Input Event to be counted
    ERAD_Counter_Event_Mode  event_mode;   //!< Active / rising edge
    uint32_t                 reference;    //!< Reference to be compared
    bool                     rst_on_match; //!< Enable counter reset on match
    bool                     enable_int;   //!< Enable Interrupt on match
    bool                     enable_nmi;   //!< Enable NMI
    bool                     enable_stop;  //!< Enable CPU halt on match
} ERAD_Counter_Config;

//*****************************************************************************
//
//! Structure that is passed to ERAD_enableInterruptOnAddressHit() and
//! ERAD_countAddressHits() as \e config_params to select the bus and the
//! address to compare. \e bus_Sel can be one of the following:
//! \b ERAD_EBC_BUS_PAB   : for instruction fetch at the address
//! \b ERAD_EBC_BUS_DWAB  : for data write access to the address
//! \b ERAD_EBC_BUS_DRAB  : for data read access to the address
//
//*****************************************************************************
typedef struct
{
    uint32_t                address;    //!< Address to compare
    uint32_t                mask;       //!< Mask for the address compare
    ERAD_BusComp_Bus_Select bus_sel;    //!< Bus to be monitored
} ERAD_AddressHit_Params;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Sets the current owner of all the EBC and SEC modules in ERAD.
//!
//! \param owner is the Owner of ERAD that is to be set
//!
//! This function sets the current owner of all the EBC and SEC module
//! instances in ERAD.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setOwnership(ERAD_Owner owner)
{
    uint8_t instance = 0;
    //
    // Set the Owner of all EBC instances as owner
    //
    for (instance = 0; instance < ERAD_MAX_EBC_INSTANCES; instance++)
    {
        HWREGB(ERAD_BASE + ERAD_O_EBC_OWNER((uint32_t)instance)) =
                            ((uint8_t)owner & ERAD_EBC_OWNER_OWNER_M);
    }

    //
    // Set the Owner of all SEC instances as owner
    //
    for (instance = 0; instance < ERAD_MAX_SEC_INSTANCES; instance++)
    {
        HWREGB(ERAD_BASE + ERAD_O_SEC_OWNER((uint32_t)instance)) =
                            ((uint8_t)owner & ERAD_SEC_OWNER_OWNER_M);
    }

    //
    // Set the Owner of all AND Mask instances as owner
    //
    for (instance = 0; instance < ERAD_MAX_AND_MASK_INSTANCES; instance++)
    {
        HWREGB(ERAD_BASE + ERAD_O_AND_MASK_OWNER((uint32_t)instance)) =
                            ((uint8_t)owner & ERAD_AND_MASK_OWNER_OWNER_M);
    }

    //
    // Set the Owner of all OR Mask instances as owner
    //
    for (instance = 0; instance < ERAD_MAX_OR_MASK_INSTANCES; instance++)
    {
        HWREGB(ERAD_BASE + ERAD_O_OR_MASK_OWNER((uint32_t)instance)) =
                            ((uint8_t)owner & ERAD_OR_MASK_OWNER_OWNER_M);
    }

    //
    // Set the Owner of the PC trace module as owner
    //
    HWREGB(ERAD_BASE + ERAD_O_PCTRACE_OWNER) =
                            ((uint8_t)owner & ERAD_PCTRACE_OWNER_OWNER_M);
}

//*****************************************************************************
//
//! Gets the current owner of the EBC instance.
//!
//! \param None.
//!
//! This function returns the current owner of the EBC instance
//!
//! \return Owner of ERAD.
//
//*****************************************************************************
static inline ERAD_Owner
ERAD_getBusCompOwnership(ERAD_BusCompInstance instance)
{
    //
    // Read EBC Owner register and return value
    //
    return((ERAD_Owner)(HWREGH(ERAD_BASE +
            ERAD_O_EBC_OWNER((uint32_t)instance)) & ERAD_EBC_OWNER_OWNER_M));
}

//*****************************************************************************
//
//! Sets the current owner of the EBC instance
//!
//! \param owner is the Owner of the EBC instance that is to be set.
//!
//! This function sets the current owner of the EBC instance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setBusCompOwnership(ERAD_BusCompInstance instance, ERAD_Owner owner)
{
    //
    // Set the EBC Owner as owner
    //
    HWREGB(ERAD_BASE + ERAD_O_EBC_OWNER((uint32_t)instance)) =
                                ((uint8_t)owner & ERAD_EBC_OWNER_OWNER_M);
}

//*****************************************************************************
//
//! Gets the current owner of the SEC instance.
//!
//! \param None.
//!
//! This function returns the current owner of the SEC instance.
//!
//! \return Owner of ERAD.
//
//*****************************************************************************
static inline ERAD_Owner
ERAD_getCounterOwnership(ERAD_CounterInstance instance)
{
    //
    // Read EBC Owner register and return value
    //
    return((ERAD_Owner)(HWREGH(ERAD_BASE +
            ERAD_O_SEC_OWNER((uint32_t)instance)) & ERAD_SEC_OWNER_OWNER_M));
}

//*****************************************************************************
//
//! Sets the current owner of the SEC instance.
//!
//! \param owner is the Owner of the SEC instance that is to be set
//!
//! This function sets the current owner of the SEC instance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setCounterOwnership(ERAD_CounterInstance instance, ERAD_Owner owner)
{
    //
    // Set the SEC Owner as owner
    //
    HWREGB(ERAD_BASE + ERAD_O_SEC_OWNER((uint32_t)instance)) =
                                    ((uint8_t)owner & ERAD_SEC_OWNER_OWNER_M);
}

//*****************************************************************************
//
//! Gets the current owner of the AND / OR Mask instance.
//!
//! \param None.
//!
//! This function returns the current owner of the AND / OR Mask instance.
//!
//! \return Owner of AND / OR Mask.
//
//*****************************************************************************
static inline ERAD_Owner
ERAD_getMaskOwnership(ERAD_Mask instance)
{
    //
    // Read Mask Owner register and return value
    //
    if((uint32_t)instance < ERAD_MAX_AND_MASK_INSTANCES)
    {
        return((ERAD_Owner)(HWREGH(ERAD_BASE +
                            ERAD_O_AND_MASK_OWNER((uint32_t)instance))
                            & ERAD_AND_MASK_OWNER_OWNER_M));
    }
    else
    {
        return((ERAD_Owner)(HWREGH(ERAD_BASE +
                            ERAD_O_OR_MASK_OWNER((uint32_t)instance -
                            ERAD_MAX_AND_MASK_INSTANCES)) &
                            ERAD_OR_MASK_OWNER_OWNER_M));
    }
}

//*****************************************************************************
//
//! Sets the current owner of the AND / OR Mask instance.
//!
//! \param owner is the Owner of the AND / OR Mask instance that is to be set
//!
//! This function sets the current owner of the AND / OR Mask instance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setMaskOwnership(ERAD_Mask instance, ERAD_Owner owner)
{
    //
    // Set the AND / OR Mask Owner as owner
    //
    if((uint32_t)instance < ERAD_MAX_AND_MASK_INSTANCES)
    {
        HWREGB(ERAD_BASE + ERAD_O_AND_MASK_OWNER((uint32_t)instance)) =
                            ((uint8_t)owner & ERAD_AND_MASK_OWNER_OWNER_M);
    }
    else
    {
        HWREGB(ERAD_BASE + ERAD_O_OR_MASK_OWNER((uint32_t)instance -
                            ERAD_MAX_AND_MASK_INSTANCES)) = ((uint8_t)owner &
                                                  ERAD_OR_MASK_OWNER_OWNER_M);
    }
}

//*****************************************************************************
//
//! Enables all counters and bus comparators.
//!
//! \param instances is the OR'd value of instances of the counters and bus
//! comparators. Following macros can be used:
//! - \b ERAD_INST_BUSCOMP0
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_COUNTER0
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//!
//! This function enables bus comparators and counters whose instances are
//! passed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableModules(uint32_t instances)
{
    uint8_t i;

    //
    // Enable each of the instance specified
    //
    for (i = 0U; i < ERAD_MAX_EBC_INSTANCES; i++)
    {
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL(i)) |= (uint16_t)(ERAD_EBC_CNTL_EN
                                                  & (0x1U & (instances >> i)));
    }
    for (i = 0U; i < ERAD_MAX_SEC_INSTANCES; i++)
    {
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL(i)) |= (uint16_t)(ERAD_SEC_CNTL_EN
                                         & (0x1U & (instances >> (i + 16U))));
    }
}

//*****************************************************************************
//
//! Disables counters and bus comparators.
//!
//! \param instances is the OR'd value of instances of the counters and bus
//! comparators. Following macros can be used:
//! - \b ERAD_INST_BUSCOMP0
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_COUNTER0
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//!
//! This function disables bus comparators and counters whose instances are
//! passed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableModules(uint32_t instances)
{
    uint8_t i;

    //
    // Disabling each of the instances specified
    //
    for (i = 0U; i < ERAD_MAX_EBC_INSTANCES; i++)
    {
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL(i)) &= ~(uint16_t)(ERAD_EBC_CNTL_EN
                                                  & (0x1U & (instances >> i)));
    }
    for (i = 0U; i < ERAD_MAX_SEC_INSTANCES; i++)
    {
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL(i)) &= ~(uint16_t)(ERAD_SEC_CNTL_EN
                                         & (0x1U & (instances >> (i + 16U))));
    }
}

//*****************************************************************************
//
//! Enables the Enhanced bus comparator module instance.
//!
//! \param instances is the EBC instance.
//!
//! This function enables the Enhanced bus comparators instance which is
//! passed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableBusCompModule(ERAD_BusCompInstance instance)
{
    //
    // Write into the control register to enable the module
    //
    HWREGB(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) |=
                                                            ERAD_EBC_CNTL_EN;
}

//*****************************************************************************
//
//! Disables the Enhanced bus comparator module instance.
//!
//! \param instances is the EBC instance.
//!
//! This function disables the Enhanced bus comparators instance which is
//! passed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableBusCompModule(ERAD_BusCompInstance instance)
{
    //
    // Write into the control register to disable the module
    //
    HWREGB(ERAD_BASE + ERAD_O_EBC_CNTL((uint32_t)instance)) &=
                                                            ~ERAD_EBC_CNTL_EN;
}

//*****************************************************************************
//
//! Enables the System Event Counter (SEC) module instance.
//!
//! \param instances is the SEC instance.
//!
//! This function enables the System Event Counter (SEC) instance which is
//! passed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableCounterModule(ERAD_CounterInstance instance)
{
    //
    // Write into the control register to enable the module
    //
    HWREGB(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) |=
                                                            ERAD_SEC_CNTL_EN;
}

//*****************************************************************************
//
//! Disables the System Event Counter (SEC) module instance.
//!
//! \param instances is the SEC instance.
//!
//! This function disables the System Event Counter (SEC) instance which is
//! passed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableCounterModule(ERAD_CounterInstance instance)
{
    //
    // Write into the control register to disable the module
    //
    HWREGB(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) &=
                                                            ~ERAD_SEC_CNTL_EN;
}

//*****************************************************************************
//
//! Initialises ERAD.
//!
//! \param owner is the owner of ERAD that is to be set.
//!
//! This function resets all the counters and disables all bus comparators and
//! counters.
//! Also sets the owner of the ERAD to the required owner.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_initModule(ERAD_Owner owner)
{
    //
    // Set the owner of ERAD as required
    //
    ERAD_setOwnership(owner);

    //
    // Disable all counters and bus comparators
    //
    ERAD_disableModules(ERAD_INST_BUSCOMP0 | ERAD_INST_BUSCOMP1 |
                        ERAD_INST_BUSCOMP2 | ERAD_INST_BUSCOMP3 |
                        ERAD_INST_BUSCOMP4 | ERAD_INST_BUSCOMP5 |
                        ERAD_INST_BUSCOMP6 | ERAD_INST_BUSCOMP7 |
                        ERAD_INST_COUNTER0 | ERAD_INST_COUNTER1 |
                        ERAD_INST_COUNTER2 | ERAD_INST_COUNTER3);
}

//*****************************************************************************
//
//! Returns the event fired status of any of the modules.
//!
//! \param None.
//!
//! This function returns the event fired status of the counters and bus
//! comparators as stored in the global registers. This allows us to read just
//! one register and see if any of the modules have fired.
//!
//! \return Event fired status of all the modules as stored in the global
//! register.
//
//*****************************************************************************
static inline uint32_t
ERAD_getEventStatus(void)
{
    //
    // Read and return from the global register
    //
    return(HWREG(ERAD_BASE + ERAD_O_GLBL_EVENT_STAT));
}

//*****************************************************************************
//
//! Enables an NMI for the specified modules.
//!
//! \param instances is the OR'd value of the instances of the counters and
//! bus comparator units that need to have an NMI enabled. Following macros can
//! be used:
//! - \b ERAD_INST_BUSCOMP0
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_COUNTER0
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//!
//! This function enables an NMI to be generated whenever any of the specified
//! counters or bus comparator units generate an event.
//!
//! Note: Enabling NMI will disable the interrupt unlike C28. The NMI signal is
//! routed to the Error Signaling module (ESM), where it should be configured.
//! For compatibility with the C28x ERAD_enableNMI function, the CPUx_ERAD_NMI
//! event should be configured in the ESM module to generate an NMI to CPUx
//! To just configure the NMI_EN bit, use the config_params enable_nmi field.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableNMI(uint16_t instances)
{
    uint8_t i;

    for (i = 0U; i < ERAD_MAX_EBC_INSTANCES; i++)
    {
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL(i)) |=
                      (uint16_t)(ERAD_EBC_CNTL_INTERRUPT &
                     ((0x1U & (instances >> i)) << ERAD_EBC_CNTL_INTERRUPT_S));
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL(i)) |=
                      (uint16_t)(ERAD_EBC_CNTL_NMI_EN
                      & ((0x1U & (instances >> i)) << ERAD_EBC_CNTL_NMI_EN_S));
    }
    for (i = 0U; i < ERAD_MAX_SEC_INSTANCES; i++)
    {
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL(i)) |=
                      (uint16_t)(ERAD_SEC_CNTL_INTERRUPT & ((0x1U &
                      (instances >> (i + 16U))) << ERAD_SEC_CNTL_INTERRUPT_S));
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL(i)) |=
                      (uint16_t)(ERAD_SEC_CNTL_NMI_EN & ((0x1U &
                      (instances >> (i + 16U))) << ERAD_SEC_CNTL_NMI_S));
    }
}

//*****************************************************************************
//
//! Disables an NMI for the specified modules.
//!
//! \param instances is the OR'd value of the instances of the counters and
//! bus comparator units that need to have an NMI disabled. Following macros
//! can be used:
//! - \b ERAD_INST_BUSCOMP0
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_COUNTER0
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//!
//! This function disables the NMI for the specified counters and bus
//! comparator units.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableNMI(uint16_t instances)
{
    uint8_t i;

    for (i = 0U; i < ERAD_MAX_EBC_INSTANCES; i++)
    {
        HWREGH(ERAD_BASE + ERAD_O_EBC_CNTL(i)) &=
                      ~(uint16_t)(ERAD_EBC_CNTL_NMI_EN
                      & ((0x1U & (instances >> i)) << ERAD_EBC_CNTL_NMI_EN_S));
    }
    for (i = 0U; i < ERAD_MAX_SEC_INSTANCES; i++)
    {
        HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL(i)) &=
                      ~(uint16_t)(ERAD_SEC_CNTL_NMI_EN & ((0x1U &
                      (instances >> (i + 16U))) << ERAD_SEC_CNTL_NMI_S));
    }
}

//*****************************************************************************
//
//! Returns the status of an Enhanced bus comparator (EBC).
//!
//! \param instance is the Enhanced bus comparator instance.
//!    Refer the enum ERAD_BusCompInstance for list of the supported instances.
//!
//! This function returns the status of the bus comparator whose instance was
//! passed. It may be either \b ERAD_STATE_IDLE, \b ERAD_STATE_ENABLED or
//! \b ERAD_STATE_COMPLETED.
//!
//! \return Status of bus comparator.
//
//*****************************************************************************
static inline ERAD_Status
ERAD_getBusCompStatus(ERAD_BusCompInstance instance)
{
    //
    // Read and return status of Enhanced Bus comparator (EBC)
    //
    return((ERAD_Status)((HWREGH(ERAD_BASE +
            ERAD_O_EBC_STATUS((uint32_t)instance)) &
            ERAD_EBC_STATUS_STATUS_M) >> ERAD_EBC_STATUS_STATUS_S));
}

//*****************************************************************************
//
//! Clears the event fired status of any of the modules.
//!
//! \param instance is the Enhanced bus comparator instance.
//!    Refer the enum ERAD_BusCompInstance for list of the supported instances.
//!
//! This function clears the event fired status of the EBC and
//! brings the module back to \b ERAD_STATE_IDLE .
//!
//! \return None
//
//*****************************************************************************
static inline void
ERAD_clearBusCompEvent(ERAD_BusCompInstance instance)
{
    //
    // Clear the event fired bit by writing into EVENT_CLR register
    //
    HWREGB(ERAD_BASE + ERAD_O_EBC_STATUSCLEAR((uint32_t)instance)) =
                                            ERAD_EBC_STATUSCLEAR_EVENT_FIRED;
}

//*****************************************************************************
//
//! Returns the status of the System Event Counter (SEC) instance.
//!
//! \param instance is the instance of the SEC module.
//!
//! This function returns the status of the SEC instance whose instance was
//! passed. It may be either \b ERAD_STATE_IDLE, \b ERAD_STATE_ENABLED or
//! \b ERAD_STATE_COMPLETED.
//!
//! \return Status of counter.
//
//*****************************************************************************
static inline ERAD_Status
ERAD_getCounterStatus(ERAD_CounterInstance instance)
{
    //
    // Read and return status of the System Event Counter
    //
    return((ERAD_Status)((HWREGH(ERAD_BASE +
            ERAD_O_SEC_STATUS((uint32_t)instance)) &
            ERAD_SEC_STATUS_STATUS_M) >> ERAD_SEC_STATUS_STATUS_S));
}

//*****************************************************************************
//
//! Returns the PC of instruction which caused the watchpoint.
//!
//! \param instance is the instance of the EBC module.
//!
//! This function returns the PC value of the instruction which caused the
//! watchpoint. This is valid for Data read/write related bus selects only.
//!
//! \return Watchpoint PC value.
//
//*****************************************************************************
static inline uint32_t
ERAD_getWatchpointPC(ERAD_BusCompInstance instance)
{
    //
    // Read and return watchpoint PC value.
    //
    return(HWREG(ERAD_BASE + ERAD_O_EBC_WP_PC((uint32_t)instance)));
}

//*****************************************************************************
//
//! Configures the Enhanced bus comparators (EBC).
//!
//! \param instance is the Enhanced bus comparator instance.
//!    Refer the enum ERAD_BusCompInstance for list of the supported instances.
//! \param config_params are the configuration parameters to be used to
//! configure the Enhanced bus comparator.
//!
//! This function configures the Enhanced bus comparator with the given
//! parameters.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.ERAD_configBusComp")))
extern void
ERAD_configBusComp(ERAD_BusCompInstance instance,
                                        ERAD_BusComp_Config *config_params);

//*****************************************************************************
//
//! Configures the counter in Counting mode.
//!
//! \param instance is the instance of the counter to be configured.
//! \param config_params are the configuration parameters to be used to
//! configure the counter.
//!
//! This function configures the counter with the given parameters. The counter
//! is setup in Counting mode, which means counting begins as soon as the
//! counter is enabled.
//! NOTE: This function does not enable the counter. The counter must be
//! enabled using the \b ERAD_enableModules method to begin counting.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.ERAD_configCounterInCountingMode")))
extern void
ERAD_configCounterInCountingMode(ERAD_CounterInstance instance,
                                 ERAD_Counter_Config *config_params);

//*****************************************************************************
//
//! Configures the counter in Start-Stop mode.
//!
//! \param instance is the instance of the counter to be configured.
//! \param config_params are the configuration parameters to be used to
//! configure the counter.
//! \param start_event is the event that starts the counter
//! \param stop_event is the event which stops that counter
//!
//! This function configures the counter with the given parameters. The counter
//! is setup in Start-Stop mode, which means counting will happen only between
//! two specified events. The event that will be counted can be any of the
//! \b ERAD_Counter_Input_Event and not only CPU cycles.
//! NOTE: \b ERAD_EVENT_NO_EVENT causes the counter to use the CPU cycles.
//! NOTE: This function does not enable the counter. The counter must be
//! enabled using the \b ERAD_enableModules method to begin counting.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.ERAD_configCounterInStartStopMode")))
extern void
ERAD_configCounterInStartStopMode(ERAD_CounterInstance instance,
                                  ERAD_Counter_Config *config_params,
                                  ERAD_Counter_Input_Event start_event,
                                  ERAD_Counter_Input_Event stop_event);

//*****************************************************************************
//
//! Configures the counter in Start-Stop Cumulative mode.
//!
//! \param instance is the instance of the counter to be configured.
//! \param config_params are the configuration parameters to be used to
//! configure the counter.
//! \param start_event is the event that starts the counter
//! \param stop_event is the event which stops that counter
//!
//! This function configures the counter with the given parameters. The counter
//! is setup in Cumulative mode, which means counting will happen only between
//! two specified events and the counter will not reset on \b stop_event. The
//! event that will be counted can be any of the \b ERAD_Counter_Input_Event
//! and not only CPU cycles.
//! NOTE: \b ERAD_EVENT_NO_EVENT causes the counter to use the CPU cycles.
//! NOTE: This function does not enable the counter. The counter must be
//! enabled using the \b ERAD_enableModules method to begin counting.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.ERAD_configCounterInCumulativeMode")))
extern void
ERAD_configCounterInCumulativeMode(ERAD_CounterInstance instance,
                                   ERAD_Counter_Config *config_params,
                                   ERAD_Counter_Input_Event start_event,
                                   ERAD_Counter_Input_Event stop_event);

//*****************************************************************************
//
//! Configures the AND and OR masks
//!
//! \param mask is the Mask to be used.
//!
//! \param instances is the OR'd value of the instances of the  bus comparator
//!  units whose events need to be used for the mask. Following macros can be
//!  used:
//! - \b ERAD_INST_BUSCOMP0
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_COUNTER0
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//!
//! \param enable_int True if interrupt needs to be enabled, False if not
//!
//! This function enables the event generated from the specified bus comparator
//! units to be used for the specified Mask. It also configures the interrupt
//! generation when the mask event occurs.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.ERAD_configMask")))
extern void
ERAD_configMask(ERAD_Mask mask, uint32_t instances, bool enable_int,
                                                        bool enable_nmi);

//*****************************************************************************
//
//! Configures the reset event of the counter.
//!
//! \param instance is the instance of the counter to be configured.
//! \param reset_event is the event upon which the counter must be reset.
//!
//! This function sets the event upon which the counter must reset and enables
//! reset upon such an event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableCounterResetInput(ERAD_CounterInstance instance,
                            ERAD_Counter_Input_Event reset_event)
{
    //
    // Setup up the counter such that the reset event is set and enabled
    //
    HWREG(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) |=
                                                ERAD_SEC_CNTL_RST_INP_SEL_EN;
    HWREG(ERAD_BASE + ERAD_O_SEC_INPUT_SEL1((uint32_t)instance)) =
                (HWREG(ERAD_BASE + ERAD_O_SEC_INPUT_SEL1((uint32_t)instance)) &
                ~ERAD_SEC_INPUT_SEL1_RST_INP_SEL_M) |
                ((uint32_t)reset_event << ERAD_SEC_INPUT_SEL1_RST_INP_SEL_S);
}

//*****************************************************************************
//
//! Disables the reset event of the counter.
//!
//! \param instance is the instance of the counter.
//!
//! This function disables the reset event that may have been set earlier
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableCounterResetInput(ERAD_CounterInstance instance)
{
    //
    // Disable the reset bit
    //
    HWREGH(ERAD_BASE + ERAD_O_SEC_CNTL((uint32_t)instance)) &=
                                            (~ERAD_SEC_CNTL_RST_INP_SEL_EN);
}

//*****************************************************************************
//
//! Clears an event that may have fired in the counter upon match.
//!
//! \param instance is the instance of the counter.
//!
//! This function clears a counter event that may have fired when the counter
//! hit a match.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_clearCounterEvent(ERAD_CounterInstance instance)
{
    //
    // Clear the event by writing into CTM_CLEAR register
    //
    HWREGB(ERAD_BASE + ERAD_O_SEC_STATUSCLEAR((uint32_t)instance)) =
                                        ERAD_SEC_STATUSCLEAR_EVENT_FIRED;
}

//*****************************************************************************
//
//! Clears an overflow that may have occured in the counter.
//!
//! \param instance is the instance of the counter.
//!
//! This function clears the overflow bit that may have got set when the
//! counter may have crossed 0xFFFFFFFF.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_clearCounterOverflow(ERAD_CounterInstance instance)
{
    //
    // Clear the overflow bit by writing into the CTM_CLEAR register
    //
    HWREGB(ERAD_BASE + ERAD_O_SEC_STATUSCLEAR((uint32_t)instance)) =
                                            ERAD_SEC_STATUSCLEAR_OVERFLOW;
}

//*****************************************************************************
//
//! Gets the current count of a counter.
//!
//! \param instance is the instance of the counter.
//!
//! This function returns the current count of the counter which was
//! configured earlier.
//!
//! \return Returns the value of the current count of the counter.
//
//*****************************************************************************
static inline uint32_t
ERAD_getCurrentCount(ERAD_CounterInstance instance)
{
    //
    // Return the current count
    //
    return(HWREG(ERAD_BASE + ERAD_O_SEC_COUNT((uint32_t)instance)));
}

//*****************************************************************************
//
//! Sets the current count of a counter.
//!
//! \param instance is the instance of the counter.
//! \param value is the value to be written as the current count.
//!
//! This function sets the current count of the counter which was
//! configured earlier. This can be used to reset the counter or start at
//! a value other than 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setCurrentCount(ERAD_CounterInstance instance, uint32_t value)
{
    //
    // Check if owner is APPLICATION or NO_OWNER
    //
    ASSERT(ERAD_getCounterOwnership(instance) == ERAD_OWNER_APPLICATION);

    //
    // Write the value into CTM_COUNT register
    //
    HWREG(ERAD_BASE + ERAD_O_SEC_COUNT((uint32_t)instance)) = value;
}

//*****************************************************************************
//
//! Gets the maximum count of a counter.
//!
//! \param instance is the SEC instance.
//!
//! This function returns the current maximum count of the counter which was
//! configured earlier.
//!
//! \return Returns the value of the current maximum count of the counter.
//
//*****************************************************************************
static inline uint32_t
ERAD_getMaxCount(ERAD_CounterInstance instance)
{
    //
    // Return the maximum value
    //
    return(HWREG(ERAD_BASE + ERAD_O_SEC_MAX_COUNT((uint32_t)instance)));
}

//*****************************************************************************
//
//! Sets the maximum count of a counter.
//!
//! \param instance is the SEC instance.
//! \param value is the value to be written as the maximum count.
//!
//! This function sets the current maximum count of the counter which was
//! configured earlier.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setMaxCount(ERAD_CounterInstance instance, uint32_t value)
{
    //
    // Check if owner is APPLICATION or NO_OWNER
    //
    ASSERT(ERAD_getCounterOwnership(instance) == ERAD_OWNER_APPLICATION);

    //
    // Write the value into the MAX_COUNT register
    //
    HWREG(ERAD_BASE + ERAD_O_SEC_MAX_COUNT((uint32_t)instance)) = value;
}

//*****************************************************************************
//
//! Gets the minimum count of a counter.
//!
//! \param instance is the SEC instance.
//!
//! This function returns the current minimum count of the counter which was
//! configured earlier.
//!
//! \return Returns the value of the current minimum count of the counter.
//
//*****************************************************************************
static inline uint32_t
ERAD_getMinCount(ERAD_CounterInstance instance)
{
    //
    // Return the maximum value
    //
    return(HWREG(ERAD_BASE + ERAD_O_SEC_MIN_COUNT((uint32_t)instance)));
}

//*****************************************************************************
//
//! Sets the minimum count of a counter.
//!
//! \param instance is the SEC instance.
//! \param value is the value to be written as the minimum count.
//!
//! This function sets the current minimum count of the counter which was
//! configured earlier.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setMinCount(ERAD_CounterInstance instance, uint32_t value)
{
    //
    // Check if owner is APPLICATION
    //
    ASSERT(ERAD_getCounterOwnership(instance) == ERAD_OWNER_APPLICATION);

    //
    // Write the value into the MIN_COUNT register
    //
    HWREG(ERAD_BASE + ERAD_O_SEC_MIN_COUNT((uint32_t)instance)) = value;
}

//*****************************************************************************
//
//! Sets conditioning on the inputs to the counter.
//!
//! \param instance is the instance value of the counter to be configured
//! \param input_type defines which input needs to be conditioned
//! \param options is the kind of conditioning that needs to applied. This can
//! be \b ERAD_INPUT_INVERT_ENABLE or \b ERAD_INPUT_INVERT_DISABLE.
//!
//! This function conditions the inputs to the counter specified. This includes
//! inverting the input for any 4 of the inputs: \e reset, \e stop, \e start,
//! \e count_input.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setCounterInputConditioning(ERAD_CounterInstance instance,
                                 ERAD_Counter_Input_Type input_type,
                                 uint16_t options)
{
    //
    // Write into the Input Conditioning register
    //
    HWREGH(ERAD_BASE + ERAD_O_SEC_INPUT_COND((uint32_t)instance)) =
            (HWREGH(ERAD_BASE + ERAD_O_SEC_INPUT_COND((uint32_t)instance)) &
        ~(0x03U << (uint16_t)input_type)) | (options << (uint16_t)input_type);
}

//*****************************************************************************
//
//! Enable PC Trace
//!
//! This function enables PC Trace
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enablePCTrace(void)
{
    HWREGB(ERAD_BASE + ERAD_O_PCTRACE_GLOBAL) =
                                            (uint8_t)ERAD_PCTRACE_GLOBAL_EN;
}

//*****************************************************************************
//
//! Disable PC Trace
//!
//! This function disables PC Trace
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disablePCTrace(void)
{
    HWREGB(ERAD_BASE + ERAD_O_PCTRACE_GLOBAL) =
                                        (uint8_t)~ERAD_PCTRACE_GLOBAL_EN;
}

//*****************************************************************************
//
//! Gets the current owner of the PC Trace module.
//!
//! \param None.
//!
//! This function returns the current owner of the PC Trace module.
//!
//! \return Owner of PC Trace.
//
//*****************************************************************************
static inline ERAD_Owner
ERAD_getPCTraceOwnership(void)
{
    //
    // Read PC Trace Owner register and return value
    //
    return((ERAD_Owner)(HWREGH(ERAD_BASE + ERAD_O_PCTRACE_OWNER) &
                                                ERAD_PCTRACE_OWNER_OWNER_M));
}

//*****************************************************************************
//
//! Sets the current owner of the PC Trace module.
//!
//! \param owner is the Owner of the PC Trace module that is to be set.
//!
//! This function sets the current owner of the PC Trace module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setPCTraceOwnership(ERAD_Owner owner)
{
    //
    // Set the Owner of the PC trace module as owner
    //
    HWREGB(ERAD_BASE + ERAD_O_PCTRACE_OWNER) =
                            ((uint8_t)owner & ERAD_PCTRACE_OWNER_OWNER_M);
}

//*****************************************************************************
//
//! Initialize PC Trace Buffer
//!
//! This function initilizes the Trace module for a fresh trace start with
//! buffer pointer reset and overflow flags cleared along with SOFT_START_PC
//! and SOFT_STOP_PC
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_initPCTraceBuffer(void)
{
    HWREGH(ERAD_BASE + ERAD_O_PCTRACE_GLOBAL) |= ERAD_PCTRACE_GLOBAL_INIT;
}

//*****************************************************************************
//
//! Configures the PC Trace submodule to trace without hardware qualifiers
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setPCTraceMode_NoQualifiers(void)
{
    //
    // Clear the QUAL1 and QUAL2 Registers and set Trace Mode to Trace without
    // any hardware qualifiers
    //
    HWREG(ERAD_BASE + ERAD_O_PCTRACE_QUAL1) = 0U;
    HWREG(ERAD_BASE + ERAD_O_PCTRACE_QUAL2) = 0U;
}

//*****************************************************************************
//
//! Configures the PC Trace submodule to trace using windowed mode
//!
//! \param qualifier Qualifier input to enable tracing
//! \param inputConditioning is the kind of conditioning that needs to applied
//! for the trace input. This can be \b ERAD_INPUT_INVERT_ENABLE or
//! \b ERAD_INPUT_INVERT_DISABLE.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setPCTraceMode_Windowed(ERAD_PCTrace_Windowed_Qualifier qualifier,
                             uint32_t inputConditioning)
{
    HWREG(ERAD_BASE + ERAD_O_PCTRACE_QUAL1) =
       ((uint32_t)qualifier << ERAD_PCTRACE_QUAL1_WINDOWED_INP_SEL_S) |
       (0x2UL << ERAD_PCTRACE_QUAL1_TRACE_MODE_S) | (inputConditioning << 18U);
    HWREG(ERAD_BASE + ERAD_O_PCTRACE_QUAL2) = 0U;
}

//*****************************************************************************
//
//! Configures the PC Trace submodule to trace using start stop mode
//!
//! \param startInput Start Event for the Trace
//! \param stopInput  Stop Event for the Trace
//! \param startInputConditioning is the kind of conditioning that needs to
//!  applied for the start input. This can be \b ERAD_INPUT_INVERT_ENABLE or
//! \b ERAD_INPUT_INVERT_DISABLE.
//! \param stopInputConditioning is the kind of conditioning that needs to
//!  applied for the stop input. This can be \b ERAD_INPUT_INVERT_ENABLE or
//! \b ERAD_INPUT_INVERT_DISABLE.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setPCTraceMode_StartStop(ERAD_Counter_Input_Event startInput,
                             uint32_t startInputConditioning,
                             ERAD_Counter_Input_Event stopInput,
                             uint32_t stopInputConditioning)
{
    HWREG(ERAD_BASE + ERAD_O_PCTRACE_QUAL1) =
        (0x3UL << ERAD_PCTRACE_QUAL1_TRACE_MODE_S)  |
        (startInputConditioning << 20U) | (stopInputConditioning << 22U);
    HWREG(ERAD_BASE + ERAD_O_PCTRACE_QUAL2) =
        ((uint32_t)startInput << ERAD_PCTRACE_QUAL2_START_INP_SEL_S) |
        ((uint32_t)stopInput << ERAD_PCTRACE_QUAL2_STOP_INP_SEL_S);
}

//*****************************************************************************
//
//! Configures the ERAD to profile a certain piece of code
//!
//! \param config_params are the parameters that will be used to configure ERAD
//!
//! This function configures 2 bus comparators and 1 counter to profile a
//! certain piece of code. The instance address of the bus comparators and the
//! counter to be used are specified in \e config_params.
//! Note: Use \b ERAD_getMaxCount to get the latest profiled value. The
//! maximum count of the counter being used must be reset to 0x0 to get the
//! correct value everytime.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.ERAD_profile")))
extern void
ERAD_profile(ERAD_Profile_Params *config_params);

//*****************************************************************************
//
//! Enables an interrupt at a specified address.
//!
//! \param config_params contrains the bus to be monitored and the address
//! \param instance is the instance of the EBC to be used
//!
//! This function enables an RTOS interrupt to be generated when an address
//! in memory or instruction is hit.
//!
//! If the selected bus is \b ERAD_EBC_BUS_PAB, then the ERAD will be
//! configured to trigger an interrupt when there is instruction fetch
//! happening at the specified address. Similary, if \b ERAD_EBC_BUS_DWAB is
//! selected, the ERAD will be configured to trigger an interrupt when there
//! write access to the specified address, and so on.
//!
//! Use \e
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.ERAD_enableInterruptOnAddressHit")))
extern void
ERAD_enableInterruptOnAddressHit(ERAD_AddressHit_Params *config_params,
                                 ERAD_BusCompInstance busComp_instance);

//*****************************************************************************
//
//! Configures the ERAD to count the number of times a the specified address
//! is hit
//!
//! \param config_params are the parameters that will be used to configure ERAD
//! \param EBC_instance is the instance of the EBC to be used
//! \param SEC_instance is the instance of the counter (SEC) to be used
//!
//! This function configures 1 bus comparator and 1 counter to count how many
//! times a the specified address is hit.
//!
//! If the selected bus is \b ERAD_EBC_BUS_PAB, then the ERAD will be
//! configured to count the number of times an instruction fetch happens
//! at the specified address. Similary, if \b ERAD_EBC_BUS_DWAB is selected,
//! the ERAD will be configured to count the number of times there is a write
//! access to the specified address, and so on.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.ERAD_countAddressHits")))
extern void
ERAD_countAddressHits(ERAD_AddressHit_Params *config_params,
                      ERAD_BusCompInstance busComp_instance,
                      ERAD_CounterInstance counter_instance);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // ERAD_H
