//###########################################################################
//
// FILE:   sent.h
//
// TITLE:  C29x SENT driver.
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

#ifndef SENT_H
#define SENT_H

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
//! \addtogroup sent_api SENT
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_sent.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#define SENT_DATAxMAP_STEP          (SENT_O_DATA1_MAP - SENT_O_DATA0_MAP)


#define SENT_MTP_CHANNEL_STEP   (SENT_O_S1_MTP_EN - SENT_O_BC_MTP_EN)
#define SENT_MTP_PERIOD_STEP    (SENT_O_S1_MTP_PERIOD - SENT_O_BC_MTP_PERIOD)
#define SENT_MTP_TRIGSEL_STEP   (SENT_O_S1_TRIGSEL - SENT_O_BC_TRIGSEL)
#define SENT_MTP_SWTR_STEP      (SENT_O_S1_MTP_SWTR - SENT_O_BC_MTP_SWTR)
#define SENT_MTP_TIMEOUT_STEP   (SENT_O_S2_MTP_TO - SENT_O_S1_MTP_TO)
#define SENT_MTP_TOGGLETIME_STEP    (SENT_O_BC_MTP_CMP2 - SENT_O_BC_MTP_CMP1)

//*****************************************************************************
//
// Values that can be passed to SENT_enableInterrupt(),
// SENT_disableInterrupt(), SENT_clearInterruptStatus(), SENT_setSWInterrupt(),
// SENT_readInterruptStatus() and SENT_clearInterruptFlag()
// as the intFlags parameter.
//
//*****************************************************************************
#define SENT_INT_GLOBAL             0x1U        //!< Global interrupt
#define SENT_INT_RFAST_S1DV         0x2U        //!< Sensor 1 Fast channel
                                                //!< valid data interrupt
#define SENT_INT_RFAST_S2DV         0x4U        //!< Sensor 2 Fast channel
                                                //!< valid data interrupt
#define SENT_INT_RFAST_S3DV         0x8U        //!< Sensor 3 Fast channel
                                                //!< valid data interrupt
#define SENT_INT_RFAST_S4DV         0x10U       //!< Sensor 4 Fast channel
                                                //!< valid data interrupt
#define SENT_INT_RSLOW_DV           0x20U       //!< Slow channel data with
                                                //!< valid data interrupt
#define SENT_INT_RSLOW_CRCERR       0x40U       //!< Slow channel data with
                                                //!< CRC Error interrupt
#define SENT_INT_RSLOW_FORMATERR    0x80U       //!< Slow channel data with
                                                //!< Format Error interrupt
#define SENT_INT_RFAST_S1CRCE       0x100U      //!< Sensor 1 Fast channel data
                                                //!< with CRC Error interrupt
#define SENT_INT_RFAST_S2CRCE       0x200U      //!< Sensor 2 Fast channel data
                                                //!< with CRC Error interrupt
#define SENT_INT_RFAST_S3CRCE       0x400U      //!< Sensor 3 Fast channel data
                                                //!< with CRC Error interrupt
#define SENT_INT_RFAST_S4CRCE       0x800U      //!< Sensor 4 Fast channel data
                                                //!< with CRC Error interrupt
#define SENT_INT_RFAST_S1FRME       0x1000U     //!< Sensor 1 Fast channel data
                                                //!< with Frame Error interrupt
#define SENT_INT_RFAST_S2FRME       0x2000U     //!< Sensor 2 Fast channel data
                                                //!< with Frame Error interrupt
#define SENT_INT_RFAST_S3FRME       0x4000U     //!< Sensor 3 Fast channel data
                                                //!< with Frame Error interrupt
#define SENT_INT_RFAST_S4FRME       0x8000U     //!< Sensor 4 Fast channel data
                                                //!< with Frame Error interrupt
#define SENT_INT_RTIMEOUT_S1ERR     0x10000U    //!< Sensor 1 timeout error
                                                //!< interrupt
#define SENT_INT_RTIMEOUT_S2ERR     0x20000U    //!< Sensor 2 timeout error
                                                //!< interrupt
#define SENT_INT_RTIMEOUT_S3ERR     0x40000U    //!< Sensor 3 timeout error
                                                //!< interrupt
#define SENT_INT_RTIMEOUT_S4ERR     0x80000U    //!< Sensor 4 timeout error
                                                //!< interrupt
#define SENT_INT_RFAST_SYNCERR25    0x100000U   //!< Fast channel sync pulse
                                                //!< interrupt
#define SENT_INT_RFAST_SYNCERR      0x200000U   //!< Successive calibration
                                                //!< pulse error interrupt
#define SENT_INT_FREQDRIFT_ERR      0x400000U   //!< Frequency drift error event
                                                //!< interrupt
#define SENT_INT_RFIFO_TRIGGER      0x800000U   //!< FIFO trigger event
                                                //!< interrupt
#define SENT_INT_RFIFO_OVFERR       0x1000000U  //!< FIFO Overflow Error event
                                                //!< interrupt
#define SENT_INT_RFIFO_UNDFERR      0x2000000U  //!< FIFO Underflow Error event
                                                //!< interrupt
#define SENT_INT_OVFTRIG_BCERR      0x4000000U  //!< Broadcast channel overflow
                                                //!< trigger error interrupt
#define SENT_INT_OVFTRIG_S1ERR      0x8000000U  //!< Sensor 1 overflow trigger
                                                //!< error interrupt
#define SENT_INT_OVFTRIG_S2ERR      0x10000000U //!< Sensor 2 overflow trigger
                                                //!< error interrupt
#define SENT_INT_OVFTRIG_S3ERR      0x20000000U //!< Sensor 3 overflow trigger
                                                //!< error interrupt
#define SENT_INT_OVFTRIG_S4ERR      0x40000000U //!< Sensor 4 overflow trigger
                                                //!< error interrupt

//*****************************************************************************
//
//! Values that can be passed to SENT_setCRCType() as the \e crcType
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_CRC_RECOMMENDED  = 0U,  //!< Recommended CRC (J2716 2010 or newer spec)
    SENT_CRC_ORIGINAL     = 0x800U //!< Original Legacy CRC (J2716 2007 spec)

} SENT_CRCType;

//*****************************************************************************
//
//! Values that can be passed to SENT_setCRCWidth() as the \e crcWidth
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_CRC_4BIT = 0U,       //!< 4 bit CRC
    SENT_CRC_6BIT = 1U,       //!< 6 bit CRC
    SENT_CRC_8BIT = 2U        //!< 8 bit CRC

} SENT_CRCWidth;

//*****************************************************************************
//
//! Values that can be passed to SENT_configureFIFOMode() as the \e fifoMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_FIFOMODE_MEMMAPPED = 0U,   //!< Direct Mapping Mode
    SENT_FIFOMODE_FIFO = 1U         //!< FIFO mode

} SENT_FIFOMode;

//*****************************************************************************
//
//! Values that can be passed to SENT_setDataNibble() as the \e dataNibble
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_RX_DNIB1 = 1U,              //!< 1 data nibble per-frame
    SENT_RX_DNIB2 = 2U,              //!< 2 data nibble per-frame
    SENT_RX_DNIB3 = 3U,              //!< 3 data nibble per-frame
    SENT_RX_DNIB4 = 4U,              //!< 4 data nibble per-frame
    SENT_RX_DNIB5 = 5U,              //!< 5 data nibble per-frame
    SENT_RX_DNIB6 = 6U,              //!< 6 data nibble per-frame
    SENT_RX_DNIB7 = 7U,              //!< 7 data nibble per-frame
    SENT_RX_DNIB8 = 8U               //!< 8 data nibble per-frame
} SENT_DataNibble;

//*****************************************************************************
//
//! Values that can be passed to SENT_setDataNibble() as the \e dataNibble
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_RX_CRC_WITHOUT_STATUS = 0x000U,    //!< CRC calculation without status
    SENT_RX_CRC_WITH_STATUS    = 0x400U     //!< CRC calculatin with status
} SENT_RxCRC;

//*****************************************************************************
//
//! Values that can be passed to SENT_setRFIFOTriggerLevel() as the
//! \e triggerLevel parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_TRIGDISABLE    = 0U,       //!< Trigger disable
    SENT_TRIGLEV1       = 1U,       //!< Trigger level 1
    SENT_TRIGLEV2       = 2U,       //!< Trigger level 2
    SENT_TRIGLEV3       = 3U,       //!< Trigger level 3
    SENT_TRIGLEV4       = 4U,       //!< Trigger level 4
    SENT_TRIGLEV5       = 5U,       //!< Trigger level 5
    SENT_TRIGLEV6       = 6U,       //!< Trigger level 6
    SENT_TRIGLEV7       = 7U,       //!< Trigger level 7
    SENT_TRIGLEV8       = 8U,       //!< Trigger level 8
    SENT_TRIGLEV9       = 9U,       //!< Trigger level 9
    SENT_TRIGLEV10      = 10,       //!< Trigger level 10
    SENT_TRIGLEV11      = 11U,      //!< Trigger level 11
    SENT_TRIGLEV12      = 12U,      //!< Trigger level 12
    SENT_TRIGLEV13      = 13U,      //!< Trigger level 13
    SENT_TRIGLEV14      = 14U,      //!< Trigger level 14
    SENT_TRIGLEV15      = 15U,      //!< Trigger level 15
    SENT_TRIGLEV16      = 16U       //!< Trigger level 16
} SENT_TriggerLevel;

//*****************************************************************************
//
//! Values that can be passed to SENT_setMTPTriggerSelect() as the \e triggerSel
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_TRIGGER_DISABLE   = 0U,      //!< Trigger is disable
    SENT_TRIGGER_BROADCAST = 1U,      //!< Broadcast Channel Trigger Source
    SENT_TRIGGER_SENSOR1   = 2U,      //!< Sensor 1 Trigger Source
    SENT_TRIGGER_SENSOR2   = 3U,      //!< Sensor 2 Trigger Source
    SENT_TRIGGER_SENSOR3   = 4U,      //!< Sensor 3 Trigger Source
    SENT_TRIGGER_SENSOR4   = 5U       //!< Sensor 4 Trigger Source
} SENT_Trigger;

//*****************************************************************************
//
//! Values that can be passed to SENT_setDataSortingFormat() as the
//! \e dataNumber parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_RECEIVER_DATA0 = 0x0U,    //!< Receiver Data 0
    SENT_RECEIVER_DATA1 = 0x1U     //!< Receiver Data 1
} SENT_DataNumber;

//*****************************************************************************
//
//! Values that can be passed to SENT_setDataSortingFormat() as the
//! \e nibbleNum parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_DATAX_NIB0 = 0x0U,    //!< DataX Nibble Number 0
    SENT_DATAX_NIB1 = 0x1U,    //!< DataX Nibble Number 1
    SENT_DATAX_NIB2 = 0x2U,    //!< DataX Nibble Number 2
    SENT_DATAX_NIB3 = 0x3U,    //!< DataX Nibble Number 3
    SENT_DATAX_NIB4 = 0x4U,    //!< DataX Nibble Number 4
    SENT_DATAX_NIB5 = 0x5U,    //!< DataX Nibble Number 5
    SENT_DATAX_NIB6 = 0x6U,    //!< DataX Nibble Number 6
    SENT_DATAX_NIB7 = 0x7U     //!< DataX Nibble Number 7
} SENT_NibbleNumber;

//*****************************************************************************
//
//! Values that can be passed to SENT_setDataSortingFormat() as the \e nibble
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_NO_NIBBLE      = 0x0U,   //!< No Nibble Selected
    SENT_DATA_NIBBLE1   = 0x1U,   //!< Data Nibble 1
    SENT_DATA_NIBBLE2   = 0x2U,   //!< Data Nibble 2
    SENT_DATA_NIBBLE3   = 0x3U,   //!< Data Nibble 3
    SENT_DATA_NIBBLE4   = 0x4U,   //!< Data Nibble 4
    SENT_DATA_NIBBLE5   = 0x5U,   //!< Data Nibble 5
    SENT_DATA_NIBBLE6   = 0x6U,   //!< Data Nibble 6
    SENT_DATA_NIBBLE7   = 0x7U,   //!< Data Nibble 7
    SENT_DATA_NIBBLE8   = 0x8U,   //!< Data Nibble 8
    SENT_CRC_NIBBLE1    = 0xAU,   //!< CRC Nibble 1
    SENT_CRC_NIBBLE2    = 0xBU,   //!< CRC Nibble 2
    SENT_STATUS_NIBBLE  = 0xFU    //!< Status Nibble
} SENT_Nibble;

//*****************************************************************************
//
//! Values that can be passed to SENT_enableMTPChannel(),
//! SENT_disableMTPChannel(), SENT_setMTPPeriod(), SENT_setMTPTriggerSelect(),
//! SENT_enableMTPSoftwareTrigger() and SENT_disableMTPSoftwareTrigger() as
//! the \e channel parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_BROADCAST_CHANNEL  = 0x0U,   //!< Broadcase Channel
    SENT_SENSOR_1_CHANNEL   = 0x1U,   //!< Sensor 1
    SENT_SENSOR_2_CHANNEL   = 0x2U,   //!< Sensor 2
    SENT_SENSOR_3_CHANNEL   = 0x3U,   //!< Sensor 3
    SENT_SENSOR_4_CHANNEL   = 0x4U    //!< Sensor 4
} SENT_Channel;

//*****************************************************************************
//
//! Values that can be passed to SENT_configureMTPTimeout() as the \e sensorNum
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_SENSOR_1           = 0x0U,   //!< Sensor 1
    SENT_SENSOR_2           = 0x1U,   //!< Sensor 2
    SENT_SENSOR_3           = 0x2U,   //!< Sensor 3
    SENT_SENSOR_4           = 0x3U    //!< Sensor 4
} SENT_SensorNumber;

//*****************************************************************************
//
//! Values that can be passed to SENT_configureMTPTimeout() as the \e sensorNum
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SENT_MTP_CMP_1           = 0x0U,   //!< MTP Compare 1
    SENT_MTP_CMP_2           = 0x1U,   //!< MTP Compare 2
    SENT_MTP_CMP_3           = 0x2U,   //!< MTP Compare 3
    SENT_MTP_CMP_4           = 0x3U,   //!< MTP Compare 4
    SENT_MTP_CMP_5           = 0x4U,   //!< MTP Compare 5
    SENT_MTP_CMP_6           = 0x5U,   //!< MTP Compare 6
    SENT_MTP_CMP_7           = 0x6U,   //!< MTP Compare 7
    SENT_MTP_CMP_8           = 0x7U,   //!< MTP Compare 8
    SENT_MTP_CMP_9           = 0x8U    //!< MTP Compare 9

} SENT_CompareNumber;


//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an SENT base address.
//!
//! \param base specifies the SENT module base address.
//!
//! This function determines if a SENT module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
SENT_isBaseValid(uint32_t base)
{
return (
           ((base & BASE_ADDR_MASK) == SENT1_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == SENT2_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == SENT3_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == SENT4_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == SENT5_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == SENT6_BASE_FRAME(0U))
          );
}
#endif


//*****************************************************************************
//
//! Enables CSENT receiver
//!
//! \param base is the base address of the SENT module.
//!
//! This function enables the CSENT receiver to monitor the SENT bus. When using
//! a master trigger pulse to trigger a sensor, the RX_ENB must be set to 0 and
//! the CSENT receiver is controlled by MTPG module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableSENTReceiver(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable SENT reveiver to monitor the SENT bus.
    //

    HWREG(base + SENT_O_RCFG) |= SENT_RCFG_RX_ENB;

}

//*****************************************************************************
//
//! Disables CSENT receiver
//!
//! \param base is the base address of the SENT module.
//!
//! This function disables the CSENT Receiver.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableSENTReceiver(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable SENT receiver.
    //

    HWREG(base + SENT_O_RCFG) &= ~SENT_RCFG_RX_ENB;

}

//*****************************************************************************
//
//! Enables CRC for fast and slow channel.
//!
//! \param base is the base address of the SENT module.
//!
//! This function enables CRC for fast channel and slow channel to calculate
//! and check.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableSENTCRC(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable the CRC for fast and slow channel.
    //

    HWREG(base + SENT_O_RCFG) |= SENT_RCFG_RX_CRCENB;

}

//*****************************************************************************
//
//! Disables CRC for fast and slow channel.
//!
//! \param base is the base address of the SENT module.
//!
//! This function disables CRC calculation and check.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableSENTCRC(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable the CRC for fast and slow channel.
    //

    HWREG(base + SENT_O_RCFG) &= ~SENT_RCFG_RX_CRCENB;

}

//*****************************************************************************
//
//! Enables Pause Pulse after the CRC.
//!
//! \param base is the base address of the SENT module.
//!
//! This function enables Pause Pulse which will be expected after the CRC.
//! The RX_PPENB must be enabled for frequency drift's detection on the
//! fixed length frames.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableSENTPausePulse(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable the pause pulse after the CRC.
    //

    HWREG(base + SENT_O_RCFG) |= SENT_RCFG_RX_PPENB;

}

//*****************************************************************************
//
//! Disables Pause Pulse after the CRC.
//!
//! \param base is the base address of the SENT module.
//!
//! This function disables the pause pulse and sensor will continuously
//! supplying SENT data that calibration pulse follows immediately after CRC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableSENTPausePulse(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable the pause pulse after the CRC.
    //

    HWREG(base + SENT_O_RCFG) &= ~SENT_RCFG_RX_PPENB;

}

//*****************************************************************************
//
//! Set CRC Type for CRC checksum calculation.
//!
//! \param base is the base address of the SENT module.
//! \param crcType indicates the type for CRC checksum calculation.
//!
//! This function sets the type for CRC checksum calculation. The \e CRCType
//! specifies the type of CRC used. Valid values can be refered from the
//! enum \e SENT_CRCType.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setCRCType(uint32_t base, SENT_CRCType crcType)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));


    //
    // Set CRC type.
    //

    HWREG(base + SENT_O_RCFG) = (HWREG(base + SENT_O_RCFG) &
                                ~SENT_RCFG_RX_CRCTYPE) | (uint32_t)crcType;

}

//*****************************************************************************
//
//! Set CRC Width for fast channel.
//!
//! \param base is the base address of the SENT module.
//! \param crcWidth is the number of CRC bits for fast channel.
//!
//! This function sets the CRC Width for fast channel.
//!
//! The \e CRCWidth specifies the expected number of CRC bits. Valid values
//! can be refered from the enum \e SENT_CRCWidth.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setCRCWidth(uint32_t base, SENT_CRCWidth crcWidth)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Set CRC width for fast channel.
    //
    HWREG(base + SENT_O_RCFG) = (HWREG(base + SENT_O_RCFG) &
                                 ~SENT_RCFG_CRC_WIDTH_M) |
                                 ((uint32_t)crcWidth << SENT_RCFG_CRC_WIDTH_S);

}

//*****************************************************************************
//
//! Configures the number of data nibbles for standard SENT.
//!
//! \param base is the base address of the SENT module.
//! \param dataNibble is the number of data nibbles.
//!
//! This function configures the number of data nibbles for standard SENT.
//!
//! The \e dataNibble specifies the number of number of data nibbles should be
//! expected for standard SENT. Some of the enhanced sensors support 7 and 8
//! nibbles. Valid values can be refered from the enum \e SENT_DataNibble.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setDataNibble(uint32_t base, SENT_DataNibble dataNibble)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Set the number of data nibbles for standard SENT.
    //

    HWREG(base + SENT_O_RCFG) =
                            (HWREG(base + SENT_O_RCFG) & ~SENT_RCFG_RX_DNIB_M) |
                            ((uint32_t)dataNibble) << SENT_RCFG_RX_DNIB_S;

}

//*****************************************************************************
//
//! Configures the number of clock cycle per Tick.
//!
//! \param base is the base address of the SENT module.
//! \param ttClock is the number of clock cycle per tick.
//!
//! This function configures the number of clock cycle per tick when generating
//! the internal tick clock. This tick clock is used for the initial calculation
//! of calibration Sync errors (25% differential). The default is 300 (12Ch),
//! which is typically 3 us ticks for 100 Mhz clock.
//!
//! The \e ttClock specifies the number of clock cycle per tick. It should be
//! a value between 1 and 65536 clock cycles inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setTTClock(uint32_t base, uint32_t ttClock)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Set the number of clock cycle per tick time.
    //

    HWREG(base + SENT_O_RCFG) = (HWREG(base + SENT_O_RCFG) &
                                ~SENT_RCFG_TTCLK_M) |
                                ((uint32_t)ttClock << SENT_RCFG_TTCLK_S);

}

//*****************************************************************************
//
//! Set the CRC checksum calculation.
//!
//! \param base is the base address of the SENT module.
//! \param rxCRC is the CRC checksum calculation for data nibbles.
//!
//! This function sets the CRC checksum calculation.
//!
//! Valid values for \e rxCRC parameter are:
//! - \e SENT_RX_CRC_WITHOUT_STATUS - CRC checksum calculation for the data
//!   nibbles only
//! - \e SENT_RX_CRC_WITH_STATUS - CRC checksum calculation for status nibble
//!   and data nibble
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setRxCRC(uint32_t base, SENT_RxCRC rxCRC)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Set the number of clock cycle per tick time.
    //

    HWREG(base + SENT_O_RCFG) = (HWREG(base + SENT_O_RCFG) &
                        ~SENT_RCFG_RX_CRC_WITH_STATUS) | ((uint32_t)rxCRC);

}

//*****************************************************************************
//
//! Get SENT FIFO data.
//!
//! \param base is the base address of the SENT module.
//!
//! This function returns the received SENT fast channel data located at the
//! top of the receive FIFO. The read data can be timestamp or data0 or data1.
//!
//! \return the received SENT fast channel data.
//
//*****************************************************************************
static inline uint32_t
SENT_getFIFO(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Return the received SENT fast channel data located at the
    // top of the receive FIFO.
    //

    return(HWREG(base + SENT_O_RFDATA));

}

//*****************************************************************************
//
//! Enables DMA Trigger.
//!
//! \param base is the base address of the SENT module.
//!
//! This function enables DMA Trigger. The receiver FIFO DMA trigger is
//! generated when the FIFO level is >= trigger level (RFIFO_TRIGLEV)
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableDMAtrigger(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable DMA trigger.
    //

    HWREG(base + SENT_O_RCFG2) |= SENT_RCFG2_DMA_ENB;

}

//*****************************************************************************
//
//! Disables DMA Trigger.
//!
//! \param base is the base address of the SENT module.
//!
//! This function disables DMA Trigger.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableDMAtrigger(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable DMA trigger.
    //

    HWREG(base + SENT_O_RCFG2) &= ~SENT_RCFG2_DMA_ENB;

}

//*****************************************************************************
//
//! Configure the FIFO Mode.
//!
//! \param base is the base address of the SENT module.
//! \param fifoMode is the FIFO mode.
//!
//! This function configures the FIFO mode.
//!
//! The \e fifoMode specifies whether the Timestamp, data0 and data1 data
//! will be mapped directly to a memory or in FIFO. Valid values
//! can be refered from the enum \e SENT_FIFOMode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_configureFIFOMode(uint32_t base, SENT_FIFOMode fifoMode)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Configure FIFO Mode.
    //

    HWREG(base + SENT_O_RCFG2) = (HWREG(base + SENT_O_RCFG2) &
                                 ~SENT_RCFG2_FIFO_MODE) | (uint32_t)fifoMode;


}

//*****************************************************************************
//
//! Configures the number of clock cycle on the Receiver Serial Data input to
//! be filtered out.
//!
//! \param base is the base address of the SENT module.
//! \param gFiltClock is the number of clock cycle to be filtered out.
//!
//! This function configures the number of clock cycle pulse on the Receiver
//! Serial Data input that will be filtered out. Valid values for \e gFiltClock
//! parameter is range from 0 (bypass) to 255 clock cycles.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setGFILTClockCycle(uint32_t base, uint32_t gFiltClock)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Set the number of clock cycle to be filtered out.
    //

    HWREG(base + SENT_O_RCFG2) = (HWREG(base + SENT_O_RCFG2) &
                                ~SENT_RCFG2_GFILT_M) |
                                ((uint32_t)gFiltClock << SENT_RCFG2_GFILT_S);

}

//*****************************************************************************
//
//! Enables Time Stamp and record at the start of the incoming frame.
//!
//! \param base is the base address of the SENT module.
//!
//! This function enables Time Stamp. The timestamp will be written to the
//! memory and will be recorded at the start of the incoming frame.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableTimeStamp(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable Time Stamp.
    //

    HWREG(base + SENT_O_RCFG2) &= ~SENT_RCFG2_TSTAMP_DIS;

}

//*****************************************************************************
//
//! Disables Time Stamp.
//!
//! \param base is the base address of the SENT module.
//!
//! This function disables the Time Stamp.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableTimeStamp(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable Time Stamp.
    //

    HWREG(base + SENT_O_RCFG2) |= SENT_RCFG2_TSTAMP_DIS;

}

//*****************************************************************************
//
//! Enables write to the memory although data contains error.
//!
//! \param base is the base address of the SENT module.
//!
//! This function enables ERRDATA write which will write to the
//! memory although the data contains errors.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableERRDATAwrite(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable Time Stamp
    //

    HWREG(base + SENT_O_RCFG2) &= ~SENT_RCFG2_NOWR_ERRDATA;

}

//*****************************************************************************
//
//! Disables write to the memory if data contains error.
//!
//! \param base is the base address of the SENT module.
//!
//! This function disables NOWR_ERRDATA. The received message with
//! errors will not be written to the FIFO or memory.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableERRDATAwrite(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable Time Stamp
    //

    HWREG(base + SENT_O_RCFG2) |= SENT_RCFG2_NOWR_ERRDATA;

}

//*****************************************************************************
//
//! Enables MTP Mode
//!
//! \param base is the base address of the SENT module.
//!
//! This function enables MTP_Mode. This mode indicates that the Receiver
//! will send the master trigger pulse(s) and then expects Sensor's
//! data response.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableMTPMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable the MTP Mode
    //

    HWREG(base + SENT_O_RCFG2) |= SENT_RCFG2_MTP_MODE;

}

//*****************************************************************************
//
//! Disables MTP Mode.
//!
//! \param base is the base address of the SENT module.
//!
//! This function disables MTP_Mode. The receiver will not send the master
//! trigger pulses.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableMTPMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable MTP Mode.
    //

    HWREG(base + SENT_O_RCFG2) &= ~SENT_RCFG2_MTP_MODE;

}

//*****************************************************************************
//
//! Set the trigger level for receiver FIFO triggerinterrupt and DMA trigger.
//!
//! \param base is the base address of the SENT module.
//! \param triggerLevel is the trigger level.
//!
//! This function sets the trigger level for the receiver FIFO trigger interrupt
//! and the DMA trigger. The \e triggerLevel level can be from 1 up to the
//! maximum level of the FIFOs depth (16). This field is used only when the
//! FIFO_MODE is 1. Receiver FIFO trigger interrupt will be disabled if
//! RFIFO_TRIGLEV is set to 0 (default value)
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setRFIFOTriggerLevel(uint32_t base, SENT_TriggerLevel triggerLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Configure the trigger level for the receiver FIFO trigger interrupt and
    // DMA trigger.
    //

    HWREG(base + SENT_O_RCFG2) = (HWREG(base + SENT_O_RCFG2) &
                        ~SENT_RCFG2_RFIFO_TRIGLEV_M) |
                        ((uint32_t)triggerLevel << SENT_RCFG2_RFIFO_TRIGLEV_S);

}

//*****************************************************************************
//
//! Enables software reset for SENT module.
//!
//! \param base is the base address of the SENT module.
//!
//! This function enables software reset for the SENT module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableSoftwareReset(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable software reset.
    //

    HWREG(base + SENT_O_CSENT_SWR) |= SENT_CSENT_SWR_SWR;

}

//*****************************************************************************
//
//! Disables software reset for SENT module.
//!
//! \param base is the base address of the SENT module.
//!
//! This function disables software reset for SENT module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableSoftwareReset(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable software reset.
    //

    HWREG(base + SENT_O_CSENT_SWR) &= ~SENT_CSENT_SWR_SWR;

}

//*****************************************************************************
//
//! Configure the receiver data sorting format.
//!
//! \param base is the base address of the SENT module.
//! \param dataNumber indicates the number of data where the nibbles will be
//! stored.
//! \param nibbleNum is the number of nibble which will be stored.
//! \param nibble is the type of nibble.
//!
//! This function configures where the received nibbles are stored in data0/1
//! map, as well as where the data nibble or CRC nibble are stored in
//! corresponding FIFO or direct memory location.
//!
//! The \e dataNumber number is a desired data number for the received nibbles
//! to be stored. Valid values for this parameter can be referred from enum
//! \e SENT_DataNumber.
//!
//! The \e nibbleNum specifies where the specified \e nibble will be stored in
//! data 0 or 1.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setDataSortingFormat(uint32_t base, SENT_DataNumber dataNumber,
                        SENT_NibbleNumber nibbleNum, SENT_Nibble nibble)
{
    uint32_t dataOffset;
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    dataOffset = (SENT_DATAxMAP_STEP * (uint32_t)dataNumber) + SENT_O_DATA0_MAP;
    shiftVal = (uint32_t)nibbleNum * 4;

    //
    // Configure the trigger level for the receiver FIFO trigger interrupt.
    //

    HWREG(base + dataOffset) = (HWREG(base + dataOffset) &
                        ~(SENT_DATA0_MAP_D0_NIB0_M << shiftVal)) |
                        ((uint32_t)nibble << shiftVal);

}

//*****************************************************************************
//
//! Configures the timout in clock tick for SENT module.
//!
//! \param base is the base address of the SENT module.
//! \param timeOut is specified timout in clock tick unit.
//!
//! This function configures the timeout setting to indicate that
//! no synchronization pulse has been received within the timeout specified.
//! This can be used for functional safety and a timeout interrupt will occur
//! when this time as expired. The Timeout functionality is enabled only after
//! receiving a synchronization pulse.
//!
//! The \e timeOut value is specified in clock tick units and it can be disabled
//! by setting the value to 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_configureTimeout(uint32_t base, uint32_t timeOut)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Configure the timout for SENT module.
    //

    HWREG(base + SENT_O_CSENT_TO) = timeOut;

}

//*****************************************************************************
//
//! Reads the synchronized serial data input value.
//!
//! \param base is the base address of the SENT module.
//!
//! This function returns the synchronized serial data input value that
//! corresponds to the base address passed into \e base. It is used to debug
//! 1 bit of the SENT receive at a time.
//!
//! \return Returns the synchronized serial data input value.
//
//*****************************************************************************
static inline uint32_t
SENT_readSerialDataIn(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Returns the synchronized serial data input value.
    //
    return(HWREG(base + SENT_O_CSENT_RXD));
}

//*****************************************************************************
//
//! Enables an SENT interrupt source.
//!
//! \param base is the base address of the SENT module.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! This function enables the interrupts for the specified interrupt sources.
//!
//! To set individual flags, the \e intFlags parameter can be the logical
//! OR of any of the following:
//! - \b SENT_INT_RFAST_S1DV        - Sensor 1 Fast channel valid data
//! - \b SENT_INT_RFAST_S2DV        - Sensor 2 Fast channel valid data
//! - \b SENT_INT_RFAST_S3DV        - Sensor 3 Fast channel valid data
//! - \b SENT_INT_RFAST_S4DV        - Sensor 4 Fast channel valid data
//! - \b SENT_INT_RSLOW_DV          - Slow channel data with valid data
//! - \b SENT_INT_RSLOW_CRCERR      - Slow channel data with CRC Error
//! - \b SENT_INT_RSLOW_FORMATERR   - Slow channel data with Format Error
//! - \b SENT_INT_RFAST_S1CRCE      - Sensor 1 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S2CRCE      - Sensor 2 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S3CRCE      - Sensor 3 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S4CRCE      - Sensor 4 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S1FRME      - Sensor 1 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S2FRME      - Sensor 2 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S3FRME      - Sensor 3 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S4FRME      - Sensor 4 Fast channel data with Frame Err
//! - \b SENT_INT_RTIMEOUT_S1ERR    - Sensor 1 timeout error
//! - \b SENT_INT_RTIMEOUT_S2ERR    - Sensor 2 timeout error
//! - \b SENT_INT_RTIMEOUT_S3ERR    - Sensor 3 timeout error
//! - \b SENT_INT_RTIMEOUT_S4ERR    - Sensor 4 timeout error
//! - \b SENT_INT_RFAST_SYNCERR25   - Fast channel sync pulse
//! - \b SENT_INT_RFAST_SYNCERR     - Successive calibration pulse error
//! - \b SENT_INT_FREQDRIFT_ERR     - Frequency drift error event
//! - \b SENT_INT_RFIFO_TRIGGER     - FIFO trigger event
//! - \b SENT_INT_RFIFO_OVFERR      - FIFO Overflow Error event
//! - \b SENT_INT_RFIFO_UNDFERR     - FIFO Underflow Error event
//! - \b SENT_INT_OVFTRIG_BCERR     - Broadcast channel overflow trigger error
//! - \b SENT_INT_OVFTRIG_S1ERR     - Sensor 1 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S2ERR     - Sensor 2 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S3ERR     - Sensor 3 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S4ERR     - Sensor 4 overflow trigger error
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableInterrupt(uint32_t base, uint32_t intFlags)
{

    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Enable the specified interrupt.
    //

    HWREG(base + SENT_O_REINT) |= intFlags;

}

//*****************************************************************************
//
//! Disables an SENT interrupt source.
//!
//! \param base is the base address of the SENT module.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! This function disables the interrupts for the specified interrupt sources.
//!
//! To disable individual flags, the \e intFlags parameter can be the logical
//! OR of any of the following:
//! - \b SENT_INT_RFAST_S1DV        - Sensor 1 Fast channel valid data
//! - \b SENT_INT_RFAST_S2DV        - Sensor 2 Fast channel valid data
//! - \b SENT_INT_RFAST_S3DV        - Sensor 3 Fast channel valid data
//! - \b SENT_INT_RFAST_S4DV        - Sensor 4 Fast channel valid data
//! - \b SENT_INT_RSLOW_DV          - Slow channel data with valid data
//! - \b SENT_INT_RSLOW_CRCERR      - Slow channel data with CRC Error
//! - \b SENT_INT_RSLOW_FORMATERR   - Slow channel data with Format Error
//! - \b SENT_INT_RFAST_S1CRCE      - Sensor 1 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S2CRCE      - Sensor 2 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S3CRCE      - Sensor 3 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S4CRCE      - Sensor 4 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S1FRME      - Sensor 1 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S2FRME      - Sensor 2 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S3FRME      - Sensor 3 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S4FRME      - Sensor 4 Fast channel data with Frame Err
//! - \b SENT_INT_RTIMEOUT_S1ERR    - Sensor 1 timeout error
//! - \b SENT_INT_RTIMEOUT_S2ERR    - Sensor 2 timeout error
//! - \b SENT_INT_RTIMEOUT_S3ERR    - Sensor 3 timeout error
//! - \b SENT_INT_RTIMEOUT_S4ERR    - Sensor 4 timeout error
//! - \b SENT_INT_RFAST_SYNCERR25   - Fast channel sync pulse
//! - \b SENT_INT_RFAST_SYNCERR     - Successive calibration pulse error
//! - \b SENT_INT_FREQDRIFT_ERR     - Frequency drift error event
//! - \b SENT_INT_RFIFO_TRIGGER     - FIFO trigger event
//! - \b SENT_INT_RFIFO_OVFERR      - FIFO Overflow Error event
//! - \b SENT_INT_RFIFO_UNDFERR     - FIFO Underflow Error event
//! - \b SENT_INT_OVFTRIG_BCERR     - Broadcast channel overflow trigger error
//! - \b SENT_INT_OVFTRIG_S1ERR     - Sensor 1 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S2ERR     - Sensor 2 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S3ERR     - Sensor 3 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S4ERR     - Sensor 4 overflow trigger error
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableInterrupt(uint32_t base, uint32_t intFlags)
{

    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable the specified interrupt.
    //

    HWREG(base + SENT_O_REINT) &= ~intFlags;

}

//*****************************************************************************
//
//! Gets an SENT interrupt source status.
//!
//! \param base is the base address of the SENT module.
//! \param intFlags is the bit mask of the interrupt sources to get the status.
//!
//! This function returns the interrupt status for the specified interrupt
//! sources.
//!
//! To get individual flags, the \e intFlags parameter can be the logical
//! OR of any of the following:
//! - \b SENT_INT_GLBL              - whenever interrupt occurs
//! - \b SENT_INT_RFAST_S1DV        - Sensor 1 Fast channel valid data
//! - \b SENT_INT_RFAST_S2DV        - Sensor 2 Fast channel valid data
//! - \b SENT_INT_RFAST_S3DV        - Sensor 3 Fast channel valid data
//! - \b SENT_INT_RFAST_S4DV        - Sensor 4 Fast channel valid data
//! - \b SENT_INT_RSLOW_DV          - Slow channel data with valid data
//! - \b SENT_INT_RSLOW_CRCERR      - Slow channel data with CRC Error
//! - \b SENT_INT_RSLOW_FORMATERR   - Slow channel data with Format Error
//! - \b SENT_INT_RFAST_S1CRCE      - Sensor 1 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S2CRCE      - Sensor 2 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S3CRCE      - Sensor 3 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S4CRCE      - Sensor 4 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S1FRME      - Sensor 1 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S2FRME      - Sensor 2 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S3FRME      - Sensor 3 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S4FRME      - Sensor 4 Fast channel data with Frame Err
//! - \b SENT_INT_RTIMEOUT_S1ERR    - Sensor 1 timeout error
//! - \b SENT_INT_RTIMEOUT_S2ERR    - Sensor 2 timeout error
//! - \b SENT_INT_RTIMEOUT_S3ERR    - Sensor 3 timeout error
//! - \b SENT_INT_RTIMEOUT_S4ERR    - Sensor 4 timeout error
//! - \b SENT_INT_RFAST_SYNCERR25   - Fast channel sync pulse
//! - \b SENT_INT_RFAST_SYNCERR     - Successive calibration pulse error
//! - \b SENT_INT_FREQDRIFT_ERR     - Frequency drift error event
//! - \b SENT_INT_RFIFO_TRIGGER     - FIFO trigger event
//! - \b SENT_INT_RFIFO_OVFERR      - FIFO Overflow Error event
//! - \b SENT_INT_RFIFO_UNDFERR     - FIFO Underflow Error event
//! - \b SENT_INT_OVFTRIG_BCERR     - Broadcast channel overflow trigger error
//! - \b SENT_INT_OVFTRIG_S1ERR     - Sensor 1 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S2ERR     - Sensor 2 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S3ERR     - Sensor 3 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S4ERR     - Sensor 4 overflow trigger error
//!
//! \return None.
//
//*****************************************************************************
static inline uint32_t
SENT_readInterruptStatus(uint32_t base, uint32_t intFlags)
{

    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Disable the specified interrupt.
    //
    return(HWREG(base + SENT_O_RINTFLAG) & intFlags);

}

//*****************************************************************************
//
//! Sets an SENT Software interrupt source.
//!
//! \param base is the base address of the SENT module.
//! \param intFlags is the bit mask of the interrupt sources to be set.
//!
//! This function sets the interrupts for the specified interrupt sources.
//!
//! To set individual flags, the \e intFlags parameter can be the logical
//! OR of any of the following:
//! - \b SENT_INT_RFAST_S1DV        - Sensor 1 Fast channel valid data
//! - \b SENT_INT_RFAST_S2DV        - Sensor 2 Fast channel valid data
//! - \b SENT_INT_RFAST_S3DV        - Sensor 3 Fast channel valid data
//! - \b SENT_INT_RFAST_S4DV        - Sensor 4 Fast channel valid data
//! - \b SENT_INT_RSLOW_DV          - Slow channel data with valid data
//! - \b SENT_INT_RSLOW_CRCERR      - Slow channel data with CRC Error
//! - \b SENT_INT_RSLOW_FORMATERR   - Slow channel data with Format Error
//! - \b SENT_INT_RFAST_S1CRCE      - Sensor 1 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S2CRCE      - Sensor 2 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S3CRCE      - Sensor 3 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S4CRCE      - Sensor 4 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S1FRME      - Sensor 1 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S2FRME      - Sensor 2 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S3FRME      - Sensor 3 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S4FRME      - Sensor 4 Fast channel data with Frame Err
//! - \b SENT_INT_RTIMEOUT_S1ERR    - Sensor 1 timeout error
//! - \b SENT_INT_RTIMEOUT_S2ERR    - Sensor 2 timeout error
//! - \b SENT_INT_RTIMEOUT_S3ERR    - Sensor 3 timeout error
//! - \b SENT_INT_RTIMEOUT_S4ERR    - Sensor 4 timeout error
//! - \b SENT_INT_RFAST_SYNCERR25   - Fast channel sync pulse
//! - \b SENT_INT_RFAST_SYNCERR     - Successive calibration pulse error
//! - \b SENT_INT_FREQDRIFT_ERR     - Frequency drift error event
//! - \b SENT_INT_RFIFO_TRIGGER     - FIFO trigger event
//! - \b SENT_INT_RFIFO_OVFERR      - FIFO Overflow Error event
//! - \b SENT_INT_RFIFO_UNDFERR     - FIFO Underflow Error event
//! - \b SENT_INT_OVFTRIG_BCERR     - Broadcast channel overflow trigger error
//! - \b SENT_INT_OVFTRIG_S1ERR     - Sensor 1 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S2ERR     - Sensor 2 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S3ERR     - Sensor 3 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S4ERR     - Sensor 4 overflow trigger error
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setSWInterrupt(uint32_t base, uint32_t intFlags)
{

    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Set the specified interrupt.
    //

    HWREG(base + SENT_O_RSETINT) |= intFlags;

}

//*****************************************************************************
//
//! Clears an SENT Software interrupt source.
//!
//! \param base is the base address of the SENT module.
//! \param intFlags is the bit mask of the interrupt sources to be cleared.
//!
//! This function clears the interrupts for the specified interrupt sources.
//!
//! To clear individual flags, the \e intFlags parameter can be the logical
//! OR of any of the following:
//! - \b SENT_INT_RFAST_S1DV        - Sensor 1 Fast channel valid data
//! - \b SENT_INT_RFAST_S2DV        - Sensor 2 Fast channel valid data
//! - \b SENT_INT_RFAST_S3DV        - Sensor 3 Fast channel valid data
//! - \b SENT_INT_RFAST_S4DV        - Sensor 4 Fast channel valid data
//! - \b SENT_INT_RSLOW_DV          - Slow channel data with valid data
//! - \b SENT_INT_RSLOW_CRCERR      - Slow channel data with CRC Error
//! - \b SENT_INT_RSLOW_FORMATERR   - Slow channel data with Format Error
//! - \b SENT_INT_RFAST_S1CRCE      - Sensor 1 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S2CRCE      - Sensor 2 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S3CRCE      - Sensor 3 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S4CRCE      - Sensor 4 Fast channel data with CRC Error
//! - \b SENT_INT_RFAST_S1FRME      - Sensor 1 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S2FRME      - Sensor 2 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S3FRME      - Sensor 3 Fast channel data with Frame Err
//! - \b SENT_INT_RFAST_S4FRME      - Sensor 4 Fast channel data with Frame Err
//! - \b SENT_INT_RTIMEOUT_S1ERR    - Sensor 1 timeout error
//! - \b SENT_INT_RTIMEOUT_S2ERR    - Sensor 2 timeout error
//! - \b SENT_INT_RTIMEOUT_S3ERR    - Sensor 3 timeout error
//! - \b SENT_INT_RTIMEOUT_S4ERR    - Sensor 4 timeout error
//! - \b SENT_INT_RFAST_SYNCERR25   - Fast channel sync pulse
//! - \b SENT_INT_RFAST_SYNCERR     - Successive calibration pulse error
//! - \b SENT_INT_FREQDRIFT_ERR     - Frequency drift error event
//! - \b SENT_INT_RFIFO_TRIGGER     - FIFO trigger event
//! - \b SENT_INT_RFIFO_OVFERR      - FIFO Overflow Error event
//! - \b SENT_INT_RFIFO_UNDFERR     - FIFO Underflow Error event
//! - \b SENT_INT_OVFTRIG_BCERR     - Broadcast channel overflow trigger error
//! - \b SENT_INT_OVFTRIG_S1ERR     - Sensor 1 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S2ERR     - Sensor 2 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S3ERR     - Sensor 3 overflow trigger error
//! - \b SENT_INT_OVFTRIG_S4ERR     - Sensor 4 overflow trigger error
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_clearInterruptFlag(uint32_t base, uint32_t intFlags)
{

    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Clear the specified interrupt.
    //

    HWREG(base + SENT_O_RCLRINT) |= intFlags;

}

//*****************************************************************************
//
//! Get SENT Memory data
//!
//! \param base is the base address of the SENT module.
//! \param SENTWord is the number of word you want to read from memory
//!
//! This function will return the SENT fast channel data located at
//! the receive FIFO. The read data can be timestamp or data0 or data1.
//! Valid values for SENTWord are between 0 to 15 inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline uint32_t
SENT_getFrameData(uint32_t base, uint16_t SENTWord)
{
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Return the received work from SENT Fast channel data when FIFO is
    // not enabled and it is memory mapped.
    //

    return(HWREG(base + SENT_O_MDATA(SENTWord)));

}

//*****************************************************************************
//
//! Enables channels to generate trigger pulses.
//!
//! \param base is the base address of the SENT module.
//! \param channel is the desired MTPG channel.
//!
//! This function enables channels specified by \e channel to generate trigger
//! pulses when it is triggered via Hardware or Softwar.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableMTPChannel(uint32_t base, SENT_Channel channel)
{
    uint32_t channelOffset;
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    channelOffset = (SENT_MTP_CHANNEL_STEP * (uint32_t)channel) +
                    SENT_O_BC_MTP_EN;

    //
    // Enable the channel to generate trigger pulses.
    //

    HWREG(base + channelOffset) |= SENT_BC_MTP_EN_MTP_EN;

}

//*****************************************************************************
//
//! Disables channels to generate trigger pulses.
//!
//! \param base is the base address of the SENT module.
//! \param channel is the desired MTPG channel.
//!
//! This function disables channels specified by \e channel to generate trigger
//! pulses when it is triggered via Hardware or Softwar.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableMTPChannel(uint32_t base, SENT_Channel channel)
{

    uint32_t channelOffset;
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    channelOffset = (SENT_MTP_CHANNEL_STEP * (uint32_t)channel) +
                    SENT_O_BC_MTP_EN;

    //
    // Disable the channel to generate trigger pulses.
    //

    HWREG(base + channelOffset) &= ~SENT_BC_MTP_EN_MTP_EN;

}

//*****************************************************************************
//
//! Sets the period for Master Trigger Pulse Generator channels.
//!
//! \param base is the base address of the SENT module.
//! \param channel is the desired MTPG channel.
//! \param period is the period for MTPG channels.
//!
//! This function sets the total time that the master trigger pulse output
//! waveform is active for the desired channel specified by \e channel.
//! The \e period must be larger than all desired Channel Compares'
//! TOGGLETIME value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setMTPPeriod(uint32_t base, SENT_Channel channel, uint32_t period)
{
    uint32_t periodOffset;

    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    periodOffset = (SENT_MTP_PERIOD_STEP * (uint32_t)channel) +
                    SENT_O_BC_MTP_PERIOD;

    //
    // Set the period that the master trigger pulse output waveform is active.
    //

    HWREG(base + periodOffset) = (HWREG(base + periodOffset) &
                                    ~SENT_BC_MTP_PERIOD_PERIOD_M) | period;

}

//*****************************************************************************
//
//! Select hardware trigger source for Master Trigger Pulse Generator channels.
//!
//! \param base is the base address of the SENT module.
//! \param channel is the desired MTPG channel.
//! \param triggerSel is the trigger source for MTPG.
//!
//! This function specifies which hardware trigger source enables the Master
//! Trigger Pulse Generator for specified channel. When the SENT bus is idle
//! and the trigger is received, the start of the pulse trigger is generated
//! by the selected source from \e triggerSel in the respective \e channel.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setMTPTriggerSelect(uint32_t base, SENT_Channel channel,
                        SENT_Trigger triggerSel)
{
    uint32_t triggerOffset;
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    triggerOffset = (SENT_MTP_TRIGSEL_STEP * (uint32_t)channel) +
                    SENT_O_BC_TRIGSEL;

    //
    // Set the trigger source which enables the MTPG.
    //

    HWREG(base + triggerOffset) = (HWREG(base + triggerOffset) &
                                    ~SENT_BC_TRIGSEL_TRIGSEL_M) | triggerSel;

}

//*****************************************************************************
//
//! Enables software trigger for Master Trigger Pulse Generator channels.
//!
//! \param base is the base address of the SENT module.
//! \param channel is the desired MTPG channel.
//!
//! This function enables software trigger request for the desired channel
//! specified by the \e channel. This bit will be cleared automatically after
//! the software trigger request is in service.
//!
//! \note The MTPG must be enabled before for desired channel by
//! SENT_enableMTPChannel() API.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_enableMTPSoftwareTrigger(uint32_t base, SENT_Channel channel)
{
    uint32_t triggerOffset;
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    triggerOffset = (SENT_MTP_SWTR_STEP + (uint32_t)channel) +
                    SENT_O_BC_MTP_SWTR;

    //
    // Enable broadcast channel's software trigger.
    //

    HWREG(base + triggerOffset) |= SENT_BC_MTP_SWTR_SWTR;

}

//*****************************************************************************
//
//! Disables software trigger for Master Trigger Pulse Generator channels.
//!
//! \param base is the base address of the SENT module.
//! \param channel is the desired MTPG channel.
//!
//! This function disables software trigger request for the desired channel
//! specified by the \e channel.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_disableMTPSoftwareTrigger(uint32_t base, SENT_Channel channel)
{
    uint32_t triggerOffset;
    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    triggerOffset = (SENT_MTP_SWTR_STEP + (uint32_t)channel) +
                    SENT_O_BC_MTP_SWTR;

    //
    // Enable broadcast channel's software trigger.
    //

    HWREG(base + triggerOffset) &= ~SENT_BC_MTP_SWTR_SWTR;

}

//*****************************************************************************
//
//! Configures the timout for Sensor channels.
//!
//! \param base is the base address of the SENT module.
//! \param timeOut is specified timout in clock tick unit.
//!
//! This function configures the timeout setting to indicate that
//! no synchronization pulse has been received within the timeout specified.
//! This can be used for functional safety and a timeout interrupt will occur
//! when this time as expired. The Timeout functionality is enabled only after
//! receiving a synchronization pulse.
//!
//! The \e timeOut value is specified in clock tick units and it can be disabled
//! by setting the value to 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_configureMTPTimeout(uint32_t base, SENT_SensorNumber sensorNum,
                            uint32_t sensorTimeout)
{
    uint32_t sensorOffset;
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    sensorOffset = (SENT_MTP_TIMEOUT_STEP * (uint32_t)sensorNum) +
                    SENT_O_S1_MTP_TO;

    //
    // Configure the timout for Sensor channels.
    //

    HWREG(base + sensorOffset) = sensorTimeout;

}

//*****************************************************************************
//
//! Sets the toggle time for MTPG output of broadcast channel.
//!
//! \param base is the base address of the SENT module.
//! \param compare is the desired compare register.
//! \param toggleTime contains the time of the broadcast channel's MTPG output
//! to be toggled.
//!
//! This function sets the toggle time to toggle the broadcast channel's
//! output when the channel couter matches the value specified by \e compare.
//! The maximum number of toggles possible are limited by the number of compare
//! register (9 for the broadcast channel). To generate one trigger pulse, two
//! compare registers must be non-zero. It is because the compare registers are
//! triggered in sequence, so for example the BC_MTP_CMP9 register must be
//! larger than BC_MTP_CMP8, which must be larger than BC_MTP_CMP7, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setBroadcastChMTPToggleTime(uint32_t base,
                            SENT_CompareNumber compareNum, uint32_t toggleTime)
{
    uint32_t toggleOffset;

    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    toggleOffset = (SENT_MTP_TOGGLETIME_STEP * (uint32_t)compareNum) +
                    SENT_O_BC_MTP_CMP1;

    //
    // Set the toggle time for MTPG output of broadcast channel.
    //

    HWREG(base + toggleOffset) = (HWREG(base + toggleOffset) &
                                 ~SENT_BC_MTP_CMP1_TOGGLETIME_M) | toggleTime;

}

//*****************************************************************************
//
//! Sets the toggle time for MTPG output of Sensor 1.
//!
//! \param base is the base address of the SENT module.
//! \param compare is the desired compare register.
//! \param toggleTime contains the time of the Sensor 1 channel's MTPG output
//! to be toggled.
//!
//! This function sets the toggle time to toggle the Sensor 1 channel's
//! output when the channel couter matches the value specified by \e compare.
//! The maximum number of toggles possible are limited by the number of compare
//! register (9 for the Sensor1 channel and 10th control when the receiver is
//! enabled to sample the RX line). To generate one trigger pulse, two
//! compare registers must be non-zero. It is because the compare registers are
//! triggered in sequence, so for example the S1_MTP_CMP9 register must be
//! larger than S1_MTP_CMP8, which must be larger than S1_MTP_CMP7, and so on.
//! The Sx_MTP_CMP10RE register (where x is 1 to 4) is only used if receiver
//! input gating needs to occur earlier than the period time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setSensor1MTPToggleTime(uint32_t base, SENT_CompareNumber compareNum,
                            uint32_t toggleTime)
{
    uint32_t toggleOffset;

    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    toggleOffset = (SENT_MTP_TOGGLETIME_STEP * (uint32_t)compareNum) +
                    SENT_O_S1_MTP_CMP1;

    //
    // Set the toggle time for MTPG output of broadcast channel.
    //

    HWREG(base + toggleOffset) = (HWREG(base + toggleOffset) &
                                 ~SENT_S1_MTP_CMP1_TOGGLETIME_M) | toggleTime;

}

//*****************************************************************************
//
//! Sets the toggle time for MTPG output of Sensor 2.
//!
//! \param base is the base address of the SENT module.
//! \param compare is the desired compare register.
//! \param toggleTime contains the time of the Sensor 2 channel's MTPG output
//! to be toggled.
//!
//! This function sets the toggle time to toggle the Sensor 2 channel's
//! output when the channel couter matches the value specified by \e compare.
//! The maximum number of toggles possible are limited by the number of compare
//! register (9 for the Sensor2 channel and 10th control when the receiver is
//! enabled to sample the RX line). To generate one trigger pulse, two
//! compare registers must be non-zero. It is because the compare registers are
//! triggered in sequence, so for example the S2_MTP_CMP9 register must be
//! larger than S2_MTP_CMP8, which must be larger than S2_MTP_CMP7, and so on.
//! The Sx_MTP_CMP10RE register (where x is 1 to 4) is only used if receiver
//! input gating needs to occur earlier than the period time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setSensor2MTPToggleTime(uint32_t base, SENT_CompareNumber compareNum,
                            uint32_t toggleTime)
{
    uint32_t toggleOffset;

    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    toggleOffset = (SENT_MTP_TOGGLETIME_STEP * (uint32_t)compareNum) +
                    SENT_O_S2_MTP_CMP1;

    //
    // Set the toggle time for MTPG output of broadcast channel.
    //

    HWREG(base + toggleOffset) = (HWREG(base + toggleOffset) &
                                 ~SENT_S2_MTP_CMP1_TOGGLETIME_M) | toggleTime;

}

//*****************************************************************************
//
//! Sets the toggle time for MTPG output of Sensor 3.
//!
//! \param base is the base address of the SENT module.
//! \param compare is the desired compare register.
//! \param toggleTime contains the time of the Sensor 3 channel's MTPG output
//! to be toggled.
//!
//! This function sets the toggle time to toggle the Sensor 3 channel's
//! output when the channel couter matches the value specified by \e compare.
//! The maximum number of toggles possible are limited by the number of compare
//! register (9 for the Sensor3 channel and 10th control when the receiver is
//! enabled to sample the RX line). To generate one trigger pulse, two
//! compare registers must be non-zero. It is because the compare registers are
//! triggered in sequence, so for example the S3_MTP_CMP9 register must be
//! larger than S3_MTP_CMP8, which must be larger than S3_MTP_CMP7, and so on.
//! The Sx_MTP_CMP10RE register (where x is 1 to 4) is only used if receiver
//! input gating needs to occur earlier than the period time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setSensor3MTPToggleTime(uint32_t base, SENT_CompareNumber compareNum,
                            uint32_t toggleTime)
{
    uint32_t toggleOffset;

    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    toggleOffset = (SENT_MTP_TOGGLETIME_STEP * (uint32_t)compareNum) +
                    SENT_O_S3_MTP_CMP1;

    //
    // Set the toggle time for MTPG output of Sensor 3 channel.
    //

    HWREG(base + toggleOffset) = (HWREG(base + toggleOffset) &
                                 ~SENT_S3_MTP_CMP1_TOGGLETIME_M) | toggleTime;

}

//*****************************************************************************
//
//! Sets the toggle time for MTPG output of Sensor 4.
//!
//! \param base is the base address of the SENT module.
//! \param compare is the desired compare register.
//! \param toggleTime contains the time of the Sensor 4 channel's MTPG output
//! to be toggled.
//!
//! This function sets the toggle time to toggle the Sensor 4 channel's
//! output when the channel couter matches the value specified by \e compare.
//! The maximum number of toggles possible are limited by the number of compare
//! register (9 for the Sensor4 channel and 10th control when the receiver is
//! enabled to sample the RX line). To generate one trigger pulse, two
//! compare registers must be non-zero. It is because the compare registers are
//! triggered in sequence, so for example the S4_MTP_CMP9 register must be
//! larger than S4_MTP_CMP8, which must be larger than S4_MTP_CMP7, and so on.
//! The Sx_MTP_CMP10RE register (where x is 1 to 4) is only used if receiver
//! input gating needs to occur earlier than the period time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setSensor4MTPToggleTime(uint32_t base, SENT_CompareNumber compareNum,
                            uint32_t toggleTime)
{
    uint32_t toggleOffset;

    //
    // Check the arguments
    //
    ASSERT(SENT_isBaseValid(base));

    toggleOffset = (SENT_MTP_TOGGLETIME_STEP * (uint32_t)compareNum) +
                    SENT_O_S4_MTP_CMP1;

    //
    // Set the toggle time for MTPG output of Sensor 4 channel.
    //

    HWREG(base + toggleOffset) = (HWREG(base + toggleOffset) &
                                 ~SENT_S4_MTP_CMP1_TOGGLETIME_M) | toggleTime;

}

//*****************************************************************************
//
//! Configures the global wait time in clock tick for MTP module.
//!
//! \param base is the base address of the SENT module.
//! \param waitTime is specified global wait time in clock tick unit.
//!
//! This function configures the global wait time which indicates the delay
//! between the last data frame received to the new master trigger pulse
//! to be generated. After the Sensor's frame received, the trigger generator
//! will wait for WAITTIME before processing the next trigger request.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setMTPWaitTime(uint32_t base, uint32_t waitTime)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Configure the global wait time in clock tick unit.
    //

    HWREG(base + SENT_O_WAITTIME) = (HWREG(base + SENT_O_WAITTIME) &
                                    ~SENT_WAITTIME_WAITTIME_M) | waitTime;

}

//*****************************************************************************
//
//! Configures the MTPG global software reset.
//!
//! \param base is the base address of the SENT module.
//!
//! This function configures the MTPG global software reset and all the
//! registers will have their default value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SENT_setMTPSoftwareReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SENT_isBaseValid(base));

    //
    // Configure the MTPG global software reset.
    //

    HWREG(base + SENT_O_MTP_SWR) |= SENT_MTP_SWR_SWR;

}

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // SENT_H