//###########################################################################
//
// FILE:   fsi.h
//
// TITLE:  C29x FSI driver
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

#ifndef FSI_H
#define FSI_H

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
//! \addtogroup fsi_api FSI
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_fsi.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// FSI Tx defines
//
//*****************************************************************************

//*****************************************************************************
//
// FSI Tx events defines
//
// Values that can be passed to APIs to enable/disable interrupts and
// also to set/get/clear event status on FSI Tx operation.
//
// There are 4 supported interrupts related to Tx events-
// All are available as event status as well except 4th one.
//
//*****************************************************************************
#define FSI_TX_EVT_FRAME_DONE       (0x0001U) //!< Frame transmission done
#define FSI_TX_EVT_BUF_UNDERRUN     (0x0002U) //!< Transmit buffer is underrun
#define FSI_TX_EVT_BUF_OVERRUN      (0x0004U) //!< Transmit buffer is overrun
#define FSI_TX_EVT_PING_TIMEOUT     (0x0008U) //!< Ping Timer event


//*****************************************************************************
//
//! \brief Flag for event status not available as interrupt
//!
//! Ping frame transmission upon hardware trigger(ping watchdog or
//! external trigger) is shown as event status.
//
//*****************************************************************************
#define FSI_TX_EVT_PING_HW_TRIG     (0x0008U)

//*****************************************************************************
//
//! \brief Mask of all Tx Events, ORing all event defines
//
//*****************************************************************************
#define FSI_TX_EVTMASK              (0x000FU)

//*****************************************************************************
//
//! \brief Maximum number of external input for triggering frame-transmission
//
//*****************************************************************************
#define FSI_TX_MAX_NUM_EXT_TRIGGERS (0x0080U)

//*****************************************************************************
//
//! \brief Shifts needed to control FSI Tx interrupt generation on INT2
//
//*****************************************************************************
#define FSI_TX_INT2_CTRL_S (0x8U)

//*****************************************************************************
//
// FSI Rx Defines
//
//*****************************************************************************

//*****************************************************************************
//
// FSI Rx event defines
//
// Values that can be passed to APIs to enable/disable interrupts and
// also to set/get/clear event status on FSI Rx operation.
//
// There are 15 supported interrupts related to Rx events.
// All are available as event status as well.
//
//*****************************************************************************
#define FSI_RX_EVT_PING_WD_TIMEOUT       (0x0001U) //!< Ping Watchdog times out
#define FSI_RX_EVT_FRAME_WD_TIMEOUT      (0x0002U) //!< Frame Watchdog times out
#define FSI_RX_EVT_CRC_ERR               (0x0004U) //!< Hardware computed CRC error
#define FSI_RX_EVT_TYPE_ERR              (0x0008U) //!< Invalid Frame type detected
#define FSI_RX_EVT_EOF_ERR               (0x0010U) //!< Invalid EndofFrame bit-pattern
#define FSI_RX_EVT_OVERRUN               (0x0020U) //!< Buffer Overrun in Rx buffer
#define FSI_RX_EVT_FRAME_DONE            (0x0040U) //!< Received frame without errors
#define FSI_RX_EVT_UNDERRUN              (0x0080U) //!< Software reads empty Rx buffer
#define FSI_RX_EVT_ERR_FRAME             (0x0100U) //!< Received error frame
#define FSI_RX_EVT_PING_FRAME            (0x0200U) //!< Received ping frame
#define FSI_RX_EVT_FRAME_OVERRUN         (0x0400U) //!< FRAME_DONE not cleared
                                                   //!< on receiving new frame
#define FSI_RX_EVT_DATA_FRAME            (0x0800U) //!< Received data frame
#define FSI_RX_EVT_PING_FRAME_TAG_MATCH  (0x1000U) //!< Recieved ping frame with matched tag
#define FSI_RX_EVT_DATA_FRAME_TAG_MATCH  (0x2000U) //!< Recieved data frame with matched tag
#define FSI_RX_EVT_ERR_FRAME_TAG_MATCH   (0x4000U) //!< Recieved error frame with tag match

//*****************************************************************************
//
//! \brief Mask of all Rx Events, ORing all event defines
//
//*****************************************************************************
#define FSI_RX_EVTMASK              (0x7FFFU)

//*****************************************************************************
//
//! \brief Maximum value in Rx delay line tap control
//
//*****************************************************************************
#define FSI_RX_MAX_DELAY_LINE_VAL   (0x001FU)

//*****************************************************************************
//
// Common defines for both FSI Tx and Rx
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Maximum data length(16 words) for user/software defined data frame
//
//*****************************************************************************
#define FSI_MAX_LEN_NWORDS_DATA     (0x000FU)

//*****************************************************************************
//
//! \brief Maximum value for user data field(8 bits)
//
//*****************************************************************************
#define FSI_MAX_VALUE_USERDATA      (0x00FFU)

//*****************************************************************************
//
//! \brief Maximum value of Buffer pointer offset(4 bits)
//
//*****************************************************************************
#define FSI_MAX_VALUE_BUF_PTR_OFF   (0x000FU)

//*****************************************************************************
//
//! \brief Key value for writing some FSI Tx/Rx registers
//
//*****************************************************************************
#define FSI_CTRL_REG_KEY            (0x00A5U)

//*****************************************************************************
//
// typedefs
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Data lines used for transmit/receive operation
//!
//! \details Supported number of data lines is only 2 - 1 lane or 2 lanes
//
//*****************************************************************************
typedef enum
{
    FSI_DATA_WIDTH_1_LANE = 0x0000U,
    FSI_DATA_WIDTH_2_LANE = 0x0001U
} FSI_DataWidth;

//*****************************************************************************
//
//! \brief List of TX submodules that can be reset, can be used with reset APIs
//!
//! \details Three kind of resets can be made-
//!          1) reset entire Tx Module
//!          2) reset only TX clock
//!          3) reset ping timeout counter
//
//*****************************************************************************
typedef enum
{
    FSI_TX_MAIN_CORE_RESET        = 0x0000U,
    FSI_TX_CLOCK_RESET            = 0x0001U,
    FSI_TX_PING_TIMEOUT_CNT_RESET = 0x0002U
} FSI_TxSubmoduleInReset;

//*****************************************************************************
//
//! \brief Start Mode for Tx frame transmission
//!
//! \details Three start modes(that is, how transmission will start) are
//! supported-
//!          1. SW write of START bit in \b TX_PKT_CTRL register
//!          2. Rising edge on external trigger
//!          3. Either SW write of START bit or Frame completion
//
//*****************************************************************************
typedef enum
{
 FSI_TX_START_FRAME_CTRL               = 0x0000U,
 FSI_TX_START_EXT_TRIG                 = 0x0001U,
 FSI_TX_START_FRAME_CTRL_OR_UDATA_TAG  = 0x0002U
} FSI_TxStartMode;

//*****************************************************************************
//
//! \brief Various FSI frame types
//!
//! \details Three frame types exist-
//!          - \b Ping: Used for checking line integrity, can be sent by
//!                     software or automatically by hardware.
//!          - \b Error: Used typically during error conditions or when one
//!                      side wants to signal the other side for attention.
//!          - \b Data: Two subtypes exist based on data-length-
//!                     a) \b Fixed (1/2/4/6 words)
//!                     b) \b Nwords Software programs number of data words
//!
//!  \note 4 bit code for frame types- 0x1, 0x2 and 0x8 to 0xE are reserved
//
//*****************************************************************************
typedef enum
{
    FSI_FRAME_TYPE_PING       = 0x0000U,
    FSI_FRAME_TYPE_ERROR      = 0x000FU,
    FSI_FRAME_TYPE_1WORD_DATA = 0x0004U,
    FSI_FRAME_TYPE_2WORD_DATA = 0x0005U,
    FSI_FRAME_TYPE_4WORD_DATA = 0x0006U,
    FSI_FRAME_TYPE_6WORD_DATA = 0x0007U,
    FSI_FRAME_TYPE_NWORD_DATA = 0x0003U
} FSI_FrameType;

//*****************************************************************************
//
//! \brief Possible values of a FSI frame
//!
//! \details 4 bit field inside FSI frame is available to set tag value(0-15)
//
//*****************************************************************************
typedef enum
{
    FSI_FRAME_TAG0  = 0x0000U,
    FSI_FRAME_TAG1  = 0x0001U,
    FSI_FRAME_TAG2  = 0x0002U,
    FSI_FRAME_TAG3  = 0x0003U,
    FSI_FRAME_TAG4  = 0x0004U,
    FSI_FRAME_TAG5  = 0x0005U,
    FSI_FRAME_TAG6  = 0x0006U,
    FSI_FRAME_TAG7  = 0x0007U,
    FSI_FRAME_TAG8  = 0x0008U,
    FSI_FRAME_TAG9  = 0x0009U,
    FSI_FRAME_TAG10 = 0x000AU,
    FSI_FRAME_TAG11 = 0x000BU,
    FSI_FRAME_TAG12 = 0x000CU,
    FSI_FRAME_TAG13 = 0x000DU,
    FSI_FRAME_TAG14 = 0x000EU,
    FSI_FRAME_TAG15 = 0x000FU
} FSI_FrameTag;

//*****************************************************************************
//
//! \brief Ping timeout mode
//!
//! \details Ping timeout can reset and restart only on hardware initiated PING
//!          frames (PING Watchdog timeout)
//!          OR
//!          on any software initiated frame being sent out also based on
//!          which mode is selected
//
//*****************************************************************************
typedef enum
{
    FSI_PINGTIMEOUT_ON_HWINIT_PING_FRAME   = 0x0000U,
    FSI_PINGTIMEOUT_ON_HWSWINIT_PING_FRAME = 0x0001U
} FSI_PingTimeoutMode;

//! \brief ECC Computation width- 16 bit or 32 bit
//!
typedef enum
{
    FSI_32BIT_ECC_COMPUTE = 0x0000U,
    FSI_16BIT_ECC_COMPUTE = 0x0001U
} FSI_ECCComputeWidth;

//*****************************************************************************
//
//! \brief Interrupt lines supported in FSI
//!
//! \details Any event on FSI Tx or Rx can be enabled to trigger interrupt on 2
//!          interrupt lines to CPU/CLA- \b INT1 and \b INT2
//
//*****************************************************************************
typedef enum
{
    FSI_INT1 = 0x0000U,
    FSI_INT2 = 0x0001U
} FSI_InterruptNum;

//*****************************************************************************
//
//! \brief List of RX modules that can be reset, can be used with reset APIs
//!
//! \details Three submodules can be reset-
//!          1) RX main core
//!          2) frame watchdog counter
//!          3) ping watchdog counter
//
//*****************************************************************************
typedef enum
{
    FSI_RX_MAIN_CORE_RESET    = 0x0000U,
    FSI_RX_FRAME_WD_CNT_RESET = 0x0001U,
    FSI_RX_PING_WD_CNT_RESET  = 0x0002U
} FSI_RxSubmoduleInReset;

//*****************************************************************************
//
//! \brief Available Rx lines for delay tap selection
//!
//! \details Delay tapping can be done on 3 lines- 1)RXCLK 2)RXD0 and 3)RXD1
//
//*****************************************************************************
typedef enum
{
    FSI_RX_DELAY_CLK = 0x0000U,
    FSI_RX_DELAY_D0  = 0x0001U,
    FSI_RX_DELAY_D1  = 0x0002U
} FSI_RxDelayTapType;

//*****************************************************************************
//
//! \brief Indexes of available FSI triggers
//!
//! \details There are 128 events as external triggers for FSI frame
//!          transfers. Indexes 83:86, 91:94 and 99:127 are reserved
//!          out of total 128 muxed external triggers.
//
//*****************************************************************************

typedef enum
{
	FSI_EXT_TRIGSRC_EPWM_XBARTRIP4		 = 0,	//!EXT TRIGSRC EPWM XBARTRIP4
	FSI_EXT_TRIGSRC_EPWM_XBARTRIP5		 = 1,	//!EXT TRIGSRC EPWM XBARTRIP5
	FSI_EXT_TRIGSRC_EPWM_XBARTRIP7		 = 2,	//!EXT TRIGSRC EPWM XBARTRIP7
	FSI_EXT_TRIGSRC_EPWM_XBARTRIP8		 = 3,	//!EXT TRIGSRC EPWM XBARTRIP8
	FSI_EXT_TRIGSRC_EPWM_XBARTRIP9		 = 4,	//!EXT TRIGSRC EPWM XBARTRIP9
	FSI_EXT_TRIGSRC_EPWM_XBARTRIP10		 = 5,	//!EXT TRIGSRC EPWM XBARTRIP10
	FSI_EXT_TRIGSRC_EPWM_XBARTRIP11		 = 6,	//!EXT TRIGSRC EPWM XBARTRIP11
	FSI_EXT_TRIGSRC_EPWM_XBARTRIP12		 = 7,	//!EXT TRIGSRC EPWM XBARTRIP12
	FSI_EXT_TRIGSRC_EPWM1_SOCA		 = 8,	//!EXT TRIGSRC EPWM1 SOCA
	FSI_EXT_TRIGSRC_EPWM1_SOCB		 = 9,	//!EXT TRIGSRC EPWM1 SOCB
	FSI_EXT_TRIGSRC_EPWM2_SOCA		 = 10,	//!EXT TRIGSRC EPWM2 SOCA
	FSI_EXT_TRIGSRC_EPWM2_SOCB		 = 11,	//!EXT TRIGSRC EPWM2 SOCB
	FSI_EXT_TRIGSRC_EPWM3_SOCA		 = 12,	//!EXT TRIGSRC EPWM3 SOCA
	FSI_EXT_TRIGSRC_EPWM3_SOCB		 = 13,	//!EXT TRIGSRC EPWM3 SOCB
	FSI_EXT_TRIGSRC_EPWM4_SOCA		 = 14,	//!EXT TRIGSRC EPWM4 SOCA
	FSI_EXT_TRIGSRC_EPWM4_SOCB		 = 15,	//!EXT TRIGSRC EPWM4 SOCB
	FSI_EXT_TRIGSRC_EPWM5_SOCA		 = 16,	//!EXT TRIGSRC EPWM5 SOCA
	FSI_EXT_TRIGSRC_EPWM5_SOCB		 = 17,	//!EXT TRIGSRC EPWM5 SOCB
	FSI_EXT_TRIGSRC_EPWM6_SOCA		 = 18,	//!EXT TRIGSRC EPWM6 SOCA
	FSI_EXT_TRIGSRC_EPWM6_SOCB		 = 19,	//!EXT TRIGSRC EPWM6 SOCB
	FSI_EXT_TRIGSRC_EPWM7_SOCA		 = 20,	//!EXT TRIGSRC EPWM7 SOCA
	FSI_EXT_TRIGSRC_EPWM7_SOCB		 = 21,	//!EXT TRIGSRC EPWM7 SOCB
	FSI_EXT_TRIGSRC_EPWM8_SOCA		 = 22,	//!EXT TRIGSRC EPWM8 SOCA
	FSI_EXT_TRIGSRC_EPWM8_SOCB		 = 23,	//!EXT TRIGSRC EPWM8 SOCB
	FSI_EXT_TRIGSRC_EPWM9_SOCA		 = 24,	//!EXT TRIGSRC EPWM9 SOCA
	FSI_EXT_TRIGSRC_EPWM9_SOCB		 = 25,	//!EXT TRIGSRC EPWM9 SOCB
	FSI_EXT_TRIGSRC_EPWM10_SOCA		 = 26,	//!EXT TRIGSRC EPWM10 SOCA
	FSI_EXT_TRIGSRC_EPWM10_SOCB		 = 27,	//!EXT TRIGSRC EPWM10 SOCB
	FSI_EXT_TRIGSRC_EPWM11_SOCA		 = 28,	//!EXT TRIGSRC EPWM11 SOCA
	FSI_EXT_TRIGSRC_EPWM11_SOCB		 = 29,	//!EXT TRIGSRC EPWM11 SOCB
	FSI_EXT_TRIGSRC_EPWM12_SOCA		 = 30,	//!EXT TRIGSRC EPWM12 SOCA
	FSI_EXT_TRIGSRC_EPWM12_SOCB		 = 31,	//!EXT TRIGSRC EPWM12 SOCB
	FSI_EXT_TRIGSRC_EPWM13_SOCA		 = 32,	//!EXT TRIGSRC EPWM13 SOCA
	FSI_EXT_TRIGSRC_EPWM13_SOCB		 = 33,	//!EXT TRIGSRC EPWM13 SOCB
	FSI_EXT_TRIGSRC_EPWM14_SOCA		 = 34,	//!EXT TRIGSRC EPWM14 SOCA
	FSI_EXT_TRIGSRC_EPWM14_SOCB		 = 35,	//!EXT TRIGSRC EPWM14 SOCB
	FSI_EXT_TRIGSRC_EPWM15_SOCA		 = 36,	//!EXT TRIGSRC EPWM15 SOCA
	FSI_EXT_TRIGSRC_EPWM15_SOCB		 = 37,	//!EXT TRIGSRC EPWM15 SOCB
	FSI_EXT_TRIGSRC_EPWM16_SOCA		 = 38,	//!EXT TRIGSRC EPWM16 SOCA
	FSI_EXT_TRIGSRC_EPWM16_SOCB		 = 39,	//!EXT TRIGSRC EPWM16 SOCB
	FSI_EXT_TRIGSRC_CLB1_CLBOUT30		 = 40,	//!EXT TRIGSRC CLB1 CLBOUT30
	FSI_EXT_TRIGSRC_CLB1_CLBOUT31		 = 41,	//!EXT TRIGSRC CLB1 CLBOUT31
	FSI_EXT_TRIGSRC_CLB2_CLBOUT30		 = 42,	//!EXT TRIGSRC CLB2 CLBOUT30
	FSI_EXT_TRIGSRC_CLB2_CLBOUT31		 = 43,	//!EXT TRIGSRC CLB2 CLBOUT31
	FSI_EXT_TRIGSRC_CLB3_CLBOUT30		 = 44,	//!EXT TRIGSRC CLB3 CLBOUT30
	FSI_EXT_TRIGSRC_CLB3_CLBOUT31		 = 45,	//!EXT TRIGSRC CLB3 CLBOUT31
	FSI_EXT_TRIGSRC_CLB4_CLBOUT30		 = 46,	//!EXT TRIGSRC CLB4 CLBOUT30
	FSI_EXT_TRIGSRC_CLB4_CLBOUT31		 = 47,	//!EXT TRIGSRC CLB4 CLBOUT31
	FSI_EXT_TRIGSRC_CLB5_CLBOUT30		 = 48,	//!EXT TRIGSRC CLB5 CLBOUT30
	FSI_EXT_TRIGSRC_CLB5_CLBOUT31		 = 49,	//!EXT TRIGSRC CLB5 CLBOUT31
	FSI_EXT_TRIGSRC_CLB6_CLBOUT30		 = 50,	//!EXT TRIGSRC CLB6 CLBOUT30
	FSI_EXT_TRIGSRC_CLB6_CLBOUT31		 = 51,	//!EXT TRIGSRC CLB6 CLBOUT31
	FSI_EXT_TRIGSRC_ADC_SOCA		 = 52,	//!EXT TRIGSRC ADC SOCA
	FSI_EXT_TRIGSRC_ADC_SOCB		 = 53,	//!EXT TRIGSRC ADC SOCB
	FSI_EXT_TRIGSRC_CPU1_TIMER0INT		 = 54,	//!EXT TRIGSRC CPU1 TIMER0INT
	FSI_EXT_TRIGSRC_CPU1_TIMER1INT		 = 55,	//!EXT TRIGSRC CPU1 TIMER1INT
	FSI_EXT_TRIGSRC_CPU1_TIMER2INT		 = 56,	//!EXT TRIGSRC CPU1 TIMER2INT
	FSI_EXT_TRIGSRC_CPU2_TIMER0INT		 = 57,	//!EXT TRIGSRC CPU2 TIMER0INT
	FSI_EXT_TRIGSRC_CPU2_TIMER1INT		 = 58,	//!EXT TRIGSRC CPU2 TIMER1INT
	FSI_EXT_TRIGSRC_CPU2_TIMER2INT		 = 59,	//!EXT TRIGSRC CPU2 TIMER2INT
	FSI_EXT_TRIGSRC_CPU3_TIMER0INT		 = 60,	//!EXT TRIGSRC CPU3 TIMER0INT
	FSI_EXT_TRIGSRC_CPU3_TIMER1INT		 = 61,	//!EXT TRIGSRC CPU3 TIMER1INT
	FSI_EXT_TRIGSRC_CPU3_TIMER2INT		 = 62,	//!EXT TRIGSRC CPU3 TIMER2INT
	FSI_EXT_TRIGSRC_RTDMA1_CH1		 = 63,	//!EXT TRIGSRC RTDMA1 CH1
	FSI_EXT_TRIGSRC_RTDMA1_CH2		 = 64,	//!EXT TRIGSRC RTDMA1 CH2
	FSI_EXT_TRIGSRC_RTDMA1_CH3		 = 65,	//!EXT TRIGSRC RTDMA1 CH3
	FSI_EXT_TRIGSRC_RTDMA1_CH4		 = 66,	//!EXT TRIGSRC RTDMA1 CH4
	FSI_EXT_TRIGSRC_RTDMA1_CH5		 = 67,	//!EXT TRIGSRC RTDMA1 CH5
	FSI_EXT_TRIGSRC_RTDMA1_CH6		 = 68,	//!EXT TRIGSRC RTDMA1 CH6
	FSI_EXT_TRIGSRC_RTDMA1_CH7		 = 69,	//!EXT TRIGSRC RTDMA1 CH7
	FSI_EXT_TRIGSRC_RTDMA1_CH8		 = 70,	//!EXT TRIGSRC RTDMA1 CH8
	FSI_EXT_TRIGSRC_RTDMA1_CH9		 = 71,	//!EXT TRIGSRC RTDMA1 CH9
	FSI_EXT_TRIGSRC_RTDMA1_CH10		 = 72,	//!EXT TRIGSRC RTDMA1 CH10
	FSI_EXT_TRIGSRC_RTDMA2_CH1		 = 73,	//!EXT TRIGSRC RTDMA2 CH1
	FSI_EXT_TRIGSRC_RTDMA2_CH2		 = 74,	//!EXT TRIGSRC RTDMA2 CH2
	FSI_EXT_TRIGSRC_RTDMA2_CH3		 = 75,	//!EXT TRIGSRC RTDMA2 CH3
	FSI_EXT_TRIGSRC_RTDMA2_CH4		 = 76,	//!EXT TRIGSRC RTDMA2 CH4
	FSI_EXT_TRIGSRC_RTDMA2_CH5		 = 77,	//!EXT TRIGSRC RTDMA2 CH5
	FSI_EXT_TRIGSRC_RTDMA2_CH6		 = 78,	//!EXT TRIGSRC RTDMA2 CH6
	FSI_EXT_TRIGSRC_RTDMA2_CH7		 = 79,	//!EXT TRIGSRC RTDMA2 CH7
	FSI_EXT_TRIGSRC_RTDMA2_CH8		 = 80,	//!EXT TRIGSRC RTDMA2 CH8
	FSI_EXT_TRIGSRC_RTDMA2_CH9		 = 81,	//!EXT TRIGSRC RTDMA2 CH9
	FSI_EXT_TRIGSRC_RTDMA2_CH10		 = 82,	//!EXT TRIGSRC RTDMA2 CH10
	FSI_EXT_TRIGSRC_FSIACBDRX_TRIG0		 = 87,	//!EXT TRIGSRC FSIACBDRX TRIG0
	FSI_EXT_TRIGSRC_FSIABCDRX_TRIG1		 = 88,	//!EXT TRIGSRC FSIABCDRX TRIG1
	FSI_EXT_TRIGSRC_FSIABCDRX_TRIG2		 = 89,	//!EXT TRIGSRC FSIABCDRX TRIG2
	FSI_EXT_TRIGSRC_FSIABCDRX_TRIG3		 = 90,	//!EXT TRIGSRC FSIABCDRX TRIG3
	FSI_EXT_TRIGSRC_EPWM17_SOCA		 = 95,	//!EXT TRIGSRC EPWM17 SOCA
	FSI_EXT_TRIGSRC_EPWM17_SOCB		 = 96,	//!EXT TRIGSRC EPWM17 SOCB
	FSI_EXT_TRIGSRC_EPWM18_SOCA		 = 97,	//!EXT TRIGSRC EPWM18 SOCA
	FSI_EXT_TRIGSRC_EPWM18_SOCB		 = 98	//!EXT TRIGSRC EPWM18 SOCB
} FSI_ExtFrameTriggerSrc;

//*****************************************************************************
//
// FSI Tx function prototypes/defintion
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Validates if FSI-Tx base address is correct
//!
//! \param[in] base is the base address of the FSI-Tx module
//!
//! \return returns \b true if the base address is valid and \b false otherwise
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
FSI_isTxBaseValid(uint32_t base)
{
    return(
           ((base & BASE_ADDR_MASK) == FSITXA_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == FSITXB_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == FSITXC_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == FSITXD_BASE_FRAME(0U))
          );
}
#endif

//*****************************************************************************
//
//! \brief Sends FLUSH pattern
//!
//! \details FLUSH pattern (toggle data lines followed by toggle on clocks)
//!          should be sent only when FSI Tx is not under \b SOFT_RESET and the
//!          clock to the transmit core has been turned ON.
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_sendTxFlush(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_MAIN_CTRL) |= ((uint16_t)FSI_TX_MAIN_CTRL_FLUSH |
                                           (FSI_CTRL_REG_KEY <<
                                           FSI_TX_MAIN_CTRL_KEY_S));
}

//*****************************************************************************
//
//! \brief Stops FLUSH pattern transmission
//!
//! \details Transmission of FLUSH pattern should be stopped before starting
//!          sending frames. Generally during initilization a pair of send/stop
//!          APIs for FLUSH pattern is called to clear data/clock lines.
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_stopTxFlush(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_MAIN_CTRL) = (((~FSI_TX_MAIN_CTRL_FLUSH) &
                                          HWREGH(base + FSI_O_TX_MAIN_CTRL)) |
                                          (FSI_CTRL_REG_KEY <<
                                          FSI_TX_MAIN_CTRL_KEY_S));
}

//*****************************************************************************
//
//! \brief Selects PLL clock as source for clock dividers
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_selectTxPLLClock(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    //
    // Set PLLCLK as source for clock divider
    //
    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) |= FSI_TX_OPER_CTRL_LO_SEL_PLLCLK;
}

//*****************************************************************************
//
//! \brief Sets clock division prescalar and enables the transmit clock
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxClock(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    //
    // Enable Tx clock
    //
    HWREGH(base + FSI_O_TX_CLK_CTRL) |= FSI_TX_CLK_CTRL_CLK_EN;
}


//*****************************************************************************
//
//! \brief Disables transmit clock
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxClock(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    //
    // Disable Tx clock
    //
    HWREGH(base + FSI_O_TX_CLK_CTRL) &= ~FSI_TX_CLK_CTRL_CLK_EN;
}

//*****************************************************************************
//
//! \brief Configures the prescalar clock keeping the transmit clock in reset
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] preScaleValue used to generate transmit clock, it defines the
//!            division value of /2,/3,/4,etc. of \b PLLCLK. Prescale value is
//!            is to be set while keeping the clock in reset.

//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_configPrescalar(uint32_t base, uint16_t preScaleValue)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));
    ASSERT(preScaleValue <= 0xFFU );

    //
    // Disable Tx clock
    //
    HWREGH(base + FSI_O_TX_CLK_CTRL) &= ~FSI_TX_CLK_CTRL_CLK_EN;

    //
    // Set prescalar value
    //
    HWREGH(base + FSI_O_TX_CLK_CTRL) = (HWREGH(base + FSI_O_TX_CLK_CTRL) &
                                       (~FSI_TX_CLK_CTRL_PRESCALE_VAL_M)) |
                                       (preScaleValue <<
                                       FSI_TX_CLK_CTRL_PRESCALE_VAL_S);
}

//*****************************************************************************
//
//! \brief Sets data width for transmission
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] dataWidth selection between 1 or 2 lane transmission
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxDataWidth(uint32_t base, FSI_DataWidth dataWidth)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) =
                                (HWREGH(base + FSI_O_TX_OPER_CTRL_LO) &
                                 (~FSI_TX_OPER_CTRL_LO_DATA_WIDTH_M)) |
                                (uint16_t)dataWidth;
}

//*****************************************************************************
//
//! \brief Enables SPI compatible mode
//!
//! \details FSI supports a \b compatibility mode in order to communicate with
//!          \b legacy peripherals like \b SPI. Only the 16-bit mode of SPI will
//!          be supported. All the frame structures, CRC checks and will be
//!          identical to the normal FSI frames.
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxSPIMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));


    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) |= FSI_TX_OPER_CTRL_LO_SPI_MODE;
}

//*****************************************************************************
//
//! \brief Disables SPI compatible mode
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxSPIMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) &= ~FSI_TX_OPER_CTRL_LO_SPI_MODE;
}

//*****************************************************************************
//
//! \brief Sets start mode for any frame transmission
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] txStartMode is one of supported 3 start modes in transmission
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxStartMode(uint32_t base, FSI_TxStartMode txStartMode)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) =
                    (HWREGH(base + FSI_O_TX_OPER_CTRL_LO) &
                     (~FSI_TX_OPER_CTRL_LO_START_MODE_M)) |
                    ((uint16_t)txStartMode << FSI_TX_OPER_CTRL_LO_START_MODE_S);
}

//*****************************************************************************
//
//! \brief Setting for when Ping timeout can reset and restart
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] pingTimeoutMode can be HW or both HW/SW initiated
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxPingTimeoutMode(uint32_t base, FSI_PingTimeoutMode pingTimeoutMode)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));


    if(pingTimeoutMode == FSI_PINGTIMEOUT_ON_HWSWINIT_PING_FRAME)
    {
        HWREGH(base + FSI_O_TX_OPER_CTRL_LO) |=
                                    FSI_TX_OPER_CTRL_LO_PING_TO_MODE;
    }
    else
    {
        HWREGH(base + FSI_O_TX_OPER_CTRL_LO) &=
                                    ~FSI_TX_OPER_CTRL_LO_PING_TO_MODE;
    }
}

//*****************************************************************************
//
//! \brief Enables the Tx TDM mode for multi-node configuration
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxTDMMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    //
    // Enable Tx TDM Mode
    //
    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) |= FSI_TX_OPER_CTRL_LO_TDM_ENABLE;
}

//*****************************************************************************
//
//! \brief Disables the Tx TDM mode.
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxTDMMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) &= ~FSI_TX_OPER_CTRL_LO_TDM_ENABLE;
}

//*****************************************************************************
//
//! \brief Enables RX TDM as TDM source.
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxTDMMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    //
    // Enable Rx TDM Mode
    //
    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) |= FSI_TX_OPER_CTRL_LO_SEL_TDM_IN;
}

//*****************************************************************************
//
//! \brief Disables the Rx TDM mode.
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxTDMMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) &= ~FSI_TX_OPER_CTRL_LO_SEL_TDM_IN;
}

//*****************************************************************************
//
//! \brief Sets a particular external input to trigger transmission
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] extInputNum can be one of ports from 0 to 127. See also
//! FSI_ExtFrameTriggerSrc enum members for valid external triggers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxExtFrameTrigger(uint32_t base, uint16_t extInputNum)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));
    ASSERT(extInputNum < FSI_TX_MAX_NUM_EXT_TRIGGERS);

    HWREGH(base + FSI_O_TX_OPER_CTRL_HI) =
                          (HWREGH(base + FSI_O_TX_OPER_CTRL_HI) &
                           (~FSI_TX_OPER_CTRL_HI_EXT_TRIG_SEL_M)) |
                          (extInputNum << FSI_TX_OPER_CTRL_HI_EXT_TRIG_SEL_S);
}

//*****************************************************************************
//
//! \brief Enables CRC value of a data frame to be forced to zero
//!
//! \details CRC value of the data frame will be forced to 0 whenever there is
//!          a transmission and buffer over-run or under-run condition happens.
//!          The idea is to force a corruption of the CRC since the data is not
//!          guaranteed to be reliable
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxCRCForceError(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_HI) |= FSI_TX_OPER_CTRL_HI_FORCE_ERR;
}

//*****************************************************************************
//
//! \brief Disables forcing of CRC value of a data frame to zero
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxCRCForceError(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_HI) &= ~FSI_TX_OPER_CTRL_HI_FORCE_ERR;
}

//*****************************************************************************
//
//! \brief Select between 16-bit and 32-bit ECC computation
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] eccComputeWidth is ECC Computation width
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxECCComputeWidth(uint32_t base, FSI_ECCComputeWidth eccComputeWidth)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    if(eccComputeWidth == FSI_16BIT_ECC_COMPUTE)
    {
        HWREGH(base + FSI_O_TX_OPER_CTRL_HI) |= FSI_TX_OPER_CTRL_HI_ECC_SEL;
    }
    else
    {
        HWREGH(base + FSI_O_TX_OPER_CTRL_HI) &= ~FSI_TX_OPER_CTRL_HI_ECC_SEL;
    }
}

//*****************************************************************************
//
//! \brief Sets frame type for transmission
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] frameType value of frame type
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxFrameType(uint32_t base, FSI_FrameType frameType)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_FRAME_CTRL) = (HWREGH(base + FSI_O_TX_FRAME_CTRL) &
                                         (~FSI_TX_FRAME_CTRL_FRAME_TYPE_M)) |
                                         (uint16_t)frameType;
}

//*****************************************************************************
//
//! \brief Sets the frame size if frame type is user/software defined frame
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] nWords is number of data words in a software defined frame
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxSoftwareFrameSize(uint32_t base, uint16_t nWords)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));
    ASSERT((nWords != 0U) && ((nWords - 1U) <= FSI_MAX_LEN_NWORDS_DATA));

    HWREGH(base + FSI_O_TX_FRAME_CTRL) = (HWREGH(base + FSI_O_TX_FRAME_CTRL) &
                                         (~FSI_TX_FRAME_CTRL_N_WORDS_M)) |
                                         ((nWords - 1U) <<
                                          FSI_TX_FRAME_CTRL_N_WORDS_S);
}

//*****************************************************************************
//
//! \brief Starts transmitting frames
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_startTxTransmit(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_FRAME_CTRL) |= FSI_TX_FRAME_CTRL_START;
}

//*****************************************************************************
//
//! \brief Sets frame tag for transmission
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] frameTag is value of frame tag, 4 bit value (0 to 15)
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxFrameTag(uint32_t base, FSI_FrameTag frameTag)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_FRAME_TAG_UDATA) =
                            (HWREGH(base + FSI_O_TX_FRAME_TAG_UDATA) &
                             (~FSI_TX_FRAME_TAG_UDATA_FRAME_TAG_M)) |
                            (uint16_t)frameTag;
}

//*****************************************************************************
//
//! \brief Sets user defined data for transmission
//!        It is an extra data field(8 bit) apart from regular data
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] userDefData is 8 bit user defined data value
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxUserDefinedData(uint32_t base, uint16_t userDefData)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));
    ASSERT(userDefData <= FSI_MAX_VALUE_USERDATA);

    HWREGH(base + FSI_O_TX_FRAME_TAG_UDATA) =
                            (HWREGH(base + FSI_O_TX_FRAME_TAG_UDATA) &
                             (~FSI_TX_FRAME_TAG_UDATA_USER_DATA_M)) |
                            (userDefData << FSI_TX_FRAME_TAG_UDATA_USER_DATA_S);
}

//*****************************************************************************
//
//! \brief Sets the value for transmit buffer pointer at desired location
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] bufPtrOff is a 4 bit offset pointer in Tx buffer from where
//!            transmitter will pick the data
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxBufferPtr(uint32_t base, uint16_t bufPtrOff)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));
    ASSERT(bufPtrOff <= FSI_MAX_VALUE_BUF_PTR_OFF);

    HWREGH(base + FSI_O_TX_BUF_PTR_LOAD) = bufPtrOff;
}

//*****************************************************************************
//
//! \brief Returns current buffer pointer location
//!
//! \param[in]  base is the FSI Tx module base address
//!
//! \return Current buffer pointer location
//!
//! \note   There could be lag due to synchronization hence value is accurate
//!         only when no current transmission is happening
//
//*****************************************************************************
static inline uint16_t
FSI_getTxBufferPtr(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return(HWREGH(base + FSI_O_TX_BUF_PTR_STS) &
           FSI_TX_BUF_PTR_STS_CURR_BUF_PTR_M);
}

//*****************************************************************************
//
//! \brief Returns valid number of data words present in buffer which have not
//!        been transmitted yet
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return Number of data words present in buffer which have not been
//!         transmitted yet
//! \note   There could be lag due to synchronization hence value is accurate
//!         only when no current transmission is happening
//
//*****************************************************************************
static inline uint16_t
FSI_getTxWordCount(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return((HWREGH(base + FSI_O_TX_BUF_PTR_STS) &
            FSI_TX_BUF_PTR_STS_CURR_WORD_CNT_M) >>
            FSI_TX_BUF_PTR_STS_CURR_WORD_CNT_S);
}

//*****************************************************************************
//
//! \brief Enables ping timer logic and once set time elapses it sends signal
//!        to transmitter to send ping frame
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] refValue is 32 bit reference value for ping time-out counter
//! \param[in] pingFrameTag is 4 bit tag value for ping time-out counter
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxPingTimer(uint32_t base, uint32_t refValue,
                FSI_FrameTag pingFrameTag)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_PING_TAG) = (uint16_t)pingFrameTag;


    HWREG(base + FSI_O_TX_PING_TO_REF) = refValue;
    HWREGH(base + FSI_O_TX_PING_CTRL) |= FSI_TX_PING_CTRL_TIMER_EN;
}

//*****************************************************************************
//
//! \brief Sets the ping tag value, used by either timeout counter initiated
//!        PING frame transfer or by external ping trigger input.
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] frameTag is 4 bit tag value for ping time-out counter
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxPingTag(uint32_t base, FSI_FrameTag frameTag)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_PING_TAG) = (uint16_t)frameTag;
}

//*****************************************************************************
//
//! \brief  Disables ping timer logic
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxPingTimer(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_PING_CTRL) &= ~FSI_TX_PING_CTRL_TIMER_EN;
}

//*****************************************************************************
//
//! \brief Enables external trigger to transmit a ping frame
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] extTrigSel can be one of the external inputs from 0 to 127.
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxExtPingTrigger(uint32_t base, uint16_t extTrigSel)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));
    ASSERT(extTrigSel < FSI_TX_MAX_NUM_EXT_TRIGGERS);

    //
    // Select external input trigger
    //
    HWREGH(base + FSI_O_TX_PING_CTRL) = (HWREGH(base + FSI_O_TX_PING_CTRL) &
                                        (~FSI_TX_PING_CTRL_EXT_TRIG_SEL_M)) |
                                        (extTrigSel <<
                                        FSI_TX_PING_CTRL_EXT_TRIG_SEL_S);
    //
    // Enable ping frame transmission through external trigger
    //
    HWREGH(base + FSI_O_TX_PING_CTRL) |= FSI_TX_PING_CTRL_EXT_TRIG_EN;
}

//*****************************************************************************
//
//! \brief Disables external trigger logic
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxExtPingTrigger(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_PING_CTRL) &= ~FSI_TX_PING_CTRL_EXT_TRIG_EN;
}

//*****************************************************************************
//
//! \brief Gives Current value of Ping Timeout Logic Counter
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return Current value of counter is returned
//
//*****************************************************************************
static inline uint32_t
FSI_getTxCurrentPingTimeoutCounter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return(HWREG(base + FSI_O_TX_PING_TO_CNT));
}

//*****************************************************************************
//
//! \brief Enables to generate DMA event on completion of a frame transfer
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxDMAEvent(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_DMA_CTRL) |= FSI_TX_DMA_CTRL_DMA_EVT_EN;
}

//*****************************************************************************
//
//! \brief Disable to generate DMA event on completion of a frame transfer
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxDMAEvent(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_DMA_CTRL) &= ~FSI_TX_DMA_CTRL_DMA_EVT_EN;
}

//*****************************************************************************
//
//! \brief Locks the control of all transmit control registers, once locked
//!        further writes will not take effect until system reset occurs
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \note System reset only can unlock registers once locked.
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_lockTxCtrl(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_LOCK_CTRL) = ((uint16_t)FSI_TX_LOCK_CTRL_LOCK |
                                        (FSI_CTRL_REG_KEY <<
                                        FSI_TX_LOCK_CTRL_KEY_S));
}

//*****************************************************************************
//
//! \brief Returns current status of all the error flags
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return Status of error flags, each bit of integer is associated with
//!         one error flag.
//!
//! Example Usage - function will set the bits corresponding to respective
//!                 error flag in return value
//!     evtStatus = FSI_getTxEventStatus(FSI_base)
//!     if bit value of evtStatus is 12(01100) means
//!     FSI_TX_EVT_OVERRUN and FSI_TX_EVT_PING_HW_TRIG flags are set
//
//*****************************************************************************
static inline uint16_t
FSI_getTxEventStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return(HWREGH(base + FSI_O_TX_EVT_STS) & FSI_TX_EVTMASK);
}

//*****************************************************************************
//
//! \brief Enables user to set TX error flags
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] evtFlags contains list of event and error flags that are
//!             supposed to be set.
//!
//! \details Writing a 1 to this bit position will cause the corresponding bit
//!          in \b TX_EVT_ERR_STATUS register to get set. The purpose of this
//!          register is to allow software to simulate the effect of the event
//!          and test the associated software/ISR.
//!
//! Example Usage
//!     evtFlags = FSI_TX_EVT_FRAME_DONE & FSI_TX_EVT_OVERRUN
//!     FSI_forceTxEvents(FSI_base,evtFlags)
//!     Above call sets error flag to frameDone and overRun events
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_forceTxEvents(uint32_t base, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_EVT_FRC) = (evtFlags & FSI_TX_EVTMASK);
}

//*****************************************************************************
//
//! \brief Enables user to clear TX error flags
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] evtFlags contains list of event and error flags that are
//!             supposed to be cleared.
//!
//! \details Writing a 1 to this bit position will cause the corresponding bit
//!          in the TX_EVT_ERR_STATUS register to get cleared to 0
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_clearTxEvents(uint32_t base, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_EVT_CLR) = (evtFlags & FSI_TX_EVTMASK);
}

//*****************************************************************************
//
//! \brief Sets the CRC value to be picked transmission if transmission is
//!        configured to use user defined SW CRC
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] userCRCValue is user defined CRC
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxUserCRC(uint32_t base, uint16_t userCRCValue)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) |= FSI_TX_OPER_CTRL_LO_SW_CRC;

    HWREGH(base + FSI_O_TX_USER_CRC) = userCRCValue;
}

//*****************************************************************************
//
//! \brief Sets the CRC value to be picked transmission if transmission is
//!        configured to use user defined SW CRC
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxUserCRC(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) &= ~FSI_TX_OPER_CTRL_LO_SW_CRC;
}

//*****************************************************************************
//
//! \brief Sets data for ECC logic computaion
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] data is the data value for which ECC needs to be computed
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setTxECCdata(uint32_t base, uint32_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREG(base + FSI_O_TX_ECC_DATA) = data;
}

//*****************************************************************************
//
//! \brief Returns ECC value evaluated for 16/32 bit data
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return ECC value for input data
//
//*****************************************************************************
static inline uint16_t
FSI_getTxECCValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return(HWREGH(base + FSI_O_TX_ECC_VAL) & FSI_TX_ECC_VAL_ECC_VAL_M);
}

//*****************************************************************************
//
//! \brief  Enables user to generate interrupt on occurrence of FSI_TxEventList
//!         events
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] intNum is the type of interrupt to be generated
//!                    interrupt1 or interrupt2
//! \param[in] intFlags contains list of events on which interrupt
//!             should be generated.
//!
//! Example Usage
//!     intFlags = FSI_TX_EVT_FRAME_DONE && FSI_TX_EVT_BUF_OVERRUN
//!                             && FSI_TX_EVT_PING_TIMEOUT
//!     FSI_enableTxInterrupt(FSI_base, FSI_INT1, intFlags)
//!     above configuration will generate signal on interrupt line 1 upon
//!     frameDone, BufOverRun and PingTimeOut event
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableTxInterrupt(uint32_t base, FSI_InterruptNum intNum,
                      uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    if(intNum == FSI_INT1)
    {
        HWREGH(base + FSI_O_TX_INT_CTRL) |= (intFlags & FSI_TX_EVTMASK);
    }
    else
    {
        HWREGH(base + FSI_O_TX_INT_CTRL) |= ((intFlags & FSI_TX_EVTMASK) <<
                                            FSI_TX_INT2_CTRL_S);
    }
}

//*****************************************************************************
//
//! \brief Enables user to disable generation interrupt on occurrence of
//!        FSI_TxEventList events
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] intNum is the type of interrupt to be generated
//!                    interrupt1 or interrupt2
//! \param[in] intFlags contains list of events on which interrupt
//!            generation has to be disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableTxInterrupt(uint32_t base, FSI_InterruptNum intNum,
                       uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    if(intNum == FSI_INT1)
    {
        HWREGH(base + FSI_O_TX_INT_CTRL) &= ~(intFlags & FSI_TX_EVTMASK);
    }
    else
    {
        HWREGH(base + FSI_O_TX_INT_CTRL) &= ((~(intFlags & FSI_TX_EVTMASK) <<
                                            FSI_TX_INT2_CTRL_S) | 0xFFU);
    }
}

//*****************************************************************************
//
//! \brief Returns address of Tx data buffer
//!
//! \details Data buffer is consisting of 16 words from offset- 0x40 to 0x4e
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return Tx data buffer address
//
//*****************************************************************************
static inline uint32_t
FSI_getTxBufferAddress(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return(base + FSI_O_TX_BUF_BASE(0U));
}

//*****************************************************************************
//
//! \brief Resets clock or ping timeout counter or entire TX module
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] submodule is name of submodule which is supposed to be reset
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_resetTxModule(uint32_t base, FSI_TxSubmoduleInReset submodule);

//*****************************************************************************
//
//! \brief Clears reset on clock or ping timeout counter or entire TX module
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] submodule is name of submodule, to be brought out of reset
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_clearTxModuleReset(uint32_t base, FSI_TxSubmoduleInReset submodule);

//*****************************************************************************
//
//! \brief Writes data in FSI Tx buffer
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] array is the address of the array of words to be transmitted.
//! \param[in] length is the number of words in the array to be transmitted.
//! \param[in] bufOffset is the offset in Tx buffer where data will be written
//!
//! \note Data Overwrite protection is implemented in this function by ensuring
//!       not more than 16 words are written and also wrap around case is taken
//!       care when more words need to be written if last write happens at
//!       maximum offset in Tx buffer
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_writeTxBuffer(uint32_t base, const uint16_t array[], uint16_t length,
                  uint16_t bufOffset);

//*****************************************************************************



//*****************************************************************************
//
// FSI Rx function prototypes/definitions
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Checks the FSI-Rx base address
//!
//! \param base is the base address of the FSI-Rx module
//!
//! \return returns \b true if the base address is valid and \b false otherwise
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
FSI_isRxBaseValid(uint32_t base)
{
    return(
           ((base & BASE_ADDR_MASK) == FSIRXA_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == FSIRXB_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == FSIRXC_BASE_FRAME(0U)) ||
           ((base & BASE_ADDR_MASK) == FSIRXD_BASE_FRAME(0U))
          );
}
#endif

//*****************************************************************************
//
//! \brief Enables internal loopback where MUX will select
//!  internal pins coming from TX module instead of what comes from pins
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxInternalLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_MAIN_CTRL) |=
                                ((uint16_t)FSI_RX_MAIN_CTRL_INT_LOOPBACK |
                                (FSI_CTRL_REG_KEY << FSI_RX_MAIN_CTRL_KEY_S));
}

//*****************************************************************************
//
//! \brief Disables internal loopback where mux will not use internal pins
//!        coming from TX module
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxInternalLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_MAIN_CTRL) =
                            (HWREGH(base + FSI_O_RX_MAIN_CTRL) &
                             (~FSI_RX_MAIN_CTRL_INT_LOOPBACK)) |
                            (FSI_CTRL_REG_KEY << FSI_RX_MAIN_CTRL_KEY_S);
}

//*****************************************************************************
//
//! \brief Receive clock is selected from the internal port coming
//!        from TX module
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxSPIPairing(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_MAIN_CTRL) |=
                            ((uint16_t)FSI_RX_MAIN_CTRL_SPI_PAIRING |
                             (FSI_CTRL_REG_KEY << FSI_RX_MAIN_CTRL_KEY_S));
}

//*****************************************************************************
//
//! \brief Selects regular receive clock coming from the pins
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxSPIPairing(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_MAIN_CTRL) = (HWREGH(base + FSI_O_RX_MAIN_CTRL) &
                                          (~FSI_RX_MAIN_CTRL_SPI_PAIRING)) |
                                          (FSI_CTRL_REG_KEY <<
                                          FSI_RX_MAIN_CTRL_KEY_S);
}

//*****************************************************************************
//
//! \brief Selects number of data lines used for receiving
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] dataWidth selection between 1 or 2 lane receive operation
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setRxDataWidth(uint32_t base, FSI_DataWidth dataWidth)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_OPER_CTRL) = (HWREGH(base + FSI_O_RX_OPER_CTRL) &
                                        (~FSI_RX_OPER_CTRL_DATA_WIDTH_M)) |
                                        (uint16_t)dataWidth;
}

//*****************************************************************************
//
//! \brief Enables SPI compatible mode in FSI Rx
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxSPIMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_OPER_CTRL) |= FSI_RX_OPER_CTRL_SPI_MODE;
}

//*****************************************************************************
//
//! \brief Disables SPI compatible mode in FSI Rx
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxSPIMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_OPER_CTRL) &= ~FSI_RX_OPER_CTRL_SPI_MODE;
}

//*****************************************************************************
//
//! \brief Sets the frame size if frame type is user/software defined frame
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] nWords is number of data words in a software defined frame
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setRxSoftwareFrameSize(uint32_t base, uint16_t nWords)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));
    ASSERT((nWords != 0U) && ((nWords - 1U) <= FSI_MAX_LEN_NWORDS_DATA));

    HWREGH(base + FSI_O_RX_OPER_CTRL) = (HWREGH(base + FSI_O_RX_OPER_CTRL) &
                                         (~FSI_RX_OPER_CTRL_N_WORDS_M)) |
                                        ((nWords - 1U) <<
                                         FSI_RX_OPER_CTRL_N_WORDS_S);
}

//*****************************************************************************
//
//! \brief Select between 16-bit and 32-bit ECC computation
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] eccComputeWidth is ECC Computation width
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setRxECCComputeWidth(uint32_t base, FSI_ECCComputeWidth eccComputeWidth)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    if(eccComputeWidth == FSI_16BIT_ECC_COMPUTE)
    {
        HWREGH(base + FSI_O_RX_OPER_CTRL) |= FSI_RX_OPER_CTRL_ECC_SEL;
    }
    else
    {
        HWREGH(base + FSI_O_RX_OPER_CTRL) &= ~FSI_RX_OPER_CTRL_ECC_SEL;
    }
}

//*****************************************************************************
//
//! \brief Setting for when Ping timeout can reset and restart
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] pingTimeoutMode can be HW or both HW/SW initiated
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setRxPingTimeoutMode(uint32_t base, FSI_PingTimeoutMode pingTimeoutMode)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    if(pingTimeoutMode == FSI_PINGTIMEOUT_ON_HWSWINIT_PING_FRAME)
    {
        HWREGH(base + FSI_O_RX_OPER_CTRL) |= FSI_RX_OPER_CTRL_PING_WD_RST_MODE;
    }
    else
    {
        HWREGH(base + FSI_O_RX_OPER_CTRL) &= ~FSI_RX_OPER_CTRL_PING_WD_RST_MODE;
    }
}

//*****************************************************************************
//
//! \brief Gets frame type received in the last successful frame
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return value of Frame type received on last successful frame
//
//*****************************************************************************
static inline FSI_FrameType
FSI_getRxFrameType(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return((FSI_FrameType)(HWREGH(base + FSI_O_RX_FRAME_INFO) &
            FSI_RX_FRAME_INFO_FRAME_TYPE_M));
}

//*****************************************************************************
//
//! \brief Enables generation of DMA event on completion of a successful
//!        frame reception
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxDMAEvent(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_DMA_CTRL) |= FSI_RX_DMA_CTRL_DMA_EVT_EN;
}

//*****************************************************************************
//
//! \brief Disables the DMA event generation on completion of a successful
//!        frame reception
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxDMAEvent(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_DMA_CTRL) &= ~FSI_RX_DMA_CTRL_DMA_EVT_EN;
}

//*****************************************************************************
//
//! \brief Returns Frame tag received for the last successful frame
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return Frame tag value.
//
//*****************************************************************************
static inline uint16_t
FSI_getRxFrameTag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return((HWREGH(base + FSI_O_RX_FRAME_TAG_UDATA) &
            FSI_RX_FRAME_TAG_UDATA_FRAME_TAG_M) >>
            FSI_RX_FRAME_TAG_UDATA_FRAME_TAG_S);
}

//*****************************************************************************
//
//! \brief Returns User-Data (8-bit) field for received data frame.
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return User data field value.
//
//*****************************************************************************
static inline uint16_t
FSI_getRxUserDefinedData(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return((HWREGH(base + FSI_O_RX_FRAME_TAG_UDATA) &
            FSI_RX_FRAME_TAG_UDATA_USER_DATA_M) >>
            FSI_RX_FRAME_TAG_UDATA_USER_DATA_S);
}

//*****************************************************************************
//
//! \brief Returns current status of all the event/error flags
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return Status of error flags,each bit of integer is associated
//!         with one error flag.
//!
//! Example Usage - function will set the bits corresponding to respective
//!     error flag in return value
//!     evtFlags = FSI_getRxEventStatus(FSI_base)
//!     if value of evtFlags is 1036(0100000001100) means
//!     FSI_RX_EVT_FRAME_OVERRUN,FSI_RX_EVT_TYPE_ERR and
//!     FSI_RX_EVT_CRC_ERR flags are set
//
//*****************************************************************************
static inline uint16_t
FSI_getRxEventStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return(HWREGH(base + FSI_O_RX_EVT_STS) & FSI_RX_EVTMASK);
}

//*****************************************************************************
//
//! \brief Enables user to set RX event/error flags
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] evtFlags contains list of error flags to be set
//!
//! \return None.
//!
//! Example Usage
//!     evtFlags = FSI_RX_EVT_EOF_ERR && FSI_RX_EVT_TYPE_ERR
//!     FSI_forceRxEvents(FSI_base,evtFlags)
//!     Above call sets error flag to FSI_RX_ERR_EOF_ERR and
//!     FSI_RX_ERR_TYPE_ERR events
//
//*****************************************************************************
static inline void
FSI_forceRxEvents(uint32_t base, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_EVT_FRC) = (evtFlags & FSI_RX_EVTMASK);
}

//*****************************************************************************
//
//! \brief Enables user to clear RX event/error flags
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] evtFlags contains list of error flags to be cleared
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_clearRxEvents(uint32_t base, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_EVT_CLR) = (evtFlags & FSI_RX_EVTMASK);
}

//*****************************************************************************
//
//! \brief Returns CRC value received in data frame/frame
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return  CRC value received in data frame
//
//*****************************************************************************
static inline uint16_t
FSI_getRxReceivedCRC(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return(HWREGH(base + FSI_O_RX_CRC_INFO) & FSI_RX_CRC_INFO_RX_CRC_M);
}

//*****************************************************************************
//
//! \brief Computes and returns CRC value for data received
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return CRC value computed on received data
//
//*****************************************************************************
static inline uint16_t
FSI_getRxComputedCRC(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return((HWREGH(base + FSI_O_RX_CRC_INFO) &
            FSI_RX_CRC_INFO_CALC_CRC_M) >> FSI_RX_CRC_INFO_CALC_CRC_S);
}

//*****************************************************************************
//
//! \brief Sets the value for receive buffer pointer at desired location
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] bufPtrOff is 4 bit offset pointer in Rx buffer from where
//!            received data will be read
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setRxBufferPtr(uint32_t base, uint16_t bufPtrOff)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));
    ASSERT(bufPtrOff <= FSI_MAX_VALUE_BUF_PTR_OFF);

    HWREGH(base + FSI_O_RX_BUF_PTR_LOAD) = bufPtrOff;
}

//*****************************************************************************
//
//! \brief Returns current buffer pointer location
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return Current buffer pointer location
//!
//! \note   There could be lag due to synchronization, hence value is accurate
//!         only when no current reception is happening
//
//*****************************************************************************
static inline uint16_t
FSI_getRxBufferPtr(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return(HWREGH(base + FSI_O_RX_BUF_PTR_STS) &
           FSI_RX_BUF_PTR_STS_CURR_BUF_PTR_M);
}

//*****************************************************************************
//
//! \brief Returns valid number of data words present in buffer which have
//!        not been read out yet
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return Number of data words present in buffer which have not been read
//!         out yet
//!
//! \note   There could be lag due to synchronization, hence value is accurate
//!         only when no current reception is happening
//
//*****************************************************************************
static inline uint16_t
FSI_getRxWordCount(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return((HWREGH(base + FSI_O_RX_BUF_PTR_STS) &
            FSI_RX_BUF_PTR_STS_CURR_WORD_CNT_M) >>
            FSI_RX_BUF_PTR_STS_CURR_WORD_CNT_S);
}

//*****************************************************************************
//
//! \brief Enables the frame watchdog counter logic to count every time it
//!        start to receive a frame
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] wdRef is reference value for ping watchdog time-out counter
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxFrameWatchdog(uint32_t base, uint32_t wdRef)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREG(base + FSI_O_RX_FRAME_WD_REF)   = wdRef;
    HWREGH(base + FSI_O_RX_FRAME_WD_CTRL) |= FSI_RX_FRAME_WD_CTRL_FRAME_WD_EN;
}

//*****************************************************************************
//
//! \brief Disables the frame watchdog counter logic
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxFrameWatchdog(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_FRAME_WD_CTRL) &= ~FSI_RX_FRAME_WD_CTRL_FRAME_WD_EN;
}

//*****************************************************************************
//
//! \brief Returns current value of frame watchdog counter
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return Current value of frame watchdog counter
//
//*****************************************************************************
static inline uint32_t
FSI_getRxFrameWatchdogCounter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return(HWREG(base + FSI_O_RX_FRAME_WD_CNT));
}

//*****************************************************************************
//
//! \brief Enables the ping watchdog counter logic and once the set time
//!        elapses it will indicate ping watchdog time-out has occurred
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] wdRef is reference value for ping watchdog time-out counter
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxPingWatchdog(uint32_t base, uint32_t wdRef)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREG(base + FSI_O_RX_PING_WD_REF)   = wdRef;
    HWREGH(base + FSI_O_RX_PING_WD_CTRL) |= FSI_RX_PING_WD_CTRL_PING_WD_EN;
}

//*****************************************************************************
//
//! \brief Disables the ping watchdog counter logic
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxPingWatchdog(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_PING_WD_CTRL) &= ~FSI_RX_PING_WD_CTRL_PING_WD_EN;
}

//*****************************************************************************
//
//! \brief Returns current value of ping watchdog counter
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return Current value(32 bit) of ping watchdog counter
//
//*****************************************************************************
static inline uint32_t
FSI_getRxPingWatchdogCounter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return(HWREG(base + FSI_O_RX_PING_WD_CNT));
}

//*****************************************************************************
//
//! \brief Returns the value of tag received for last ping frame
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return Tag Value received for last ping frame
//
//*****************************************************************************
static inline uint16_t
FSI_getRxPingTag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return((HWREGH(base + FSI_O_RX_PING_TAG) & FSI_RX_PING_TAG_PING_TAG_M) >>
            FSI_RX_PING_TAG_PING_TAG_S);
}

//*****************************************************************************
//
//! \brief  Locks the control of all receive control registers,
//!         once locked further writes will not take effect until system
//!         reset occurs
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_lockRxCtrl(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREGH(base + FSI_O_RX_LOCK_CTRL) = ((uint16_t)FSI_RX_LOCK_CTRL_LOCK |
                                        (FSI_CTRL_REG_KEY <<
                                        FSI_RX_LOCK_CTRL_KEY_S));
}

//*****************************************************************************
//
//! \brief Sets Rx ECC data on which ECC (SEC-DED) computaion logic runs
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] rxECCdata Data for ECC logic
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setRxECCData(uint32_t base, uint32_t rxECCdata)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREG(base + FSI_O_RX_ECC_DATA) = rxECCdata;
}

//*****************************************************************************
//
//! \brief Sets received ECC value on which ECC (SEC-DED) computaion logic runs
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] rxECCvalue Received ECC value in a data frame
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_setRxReceivedECCValue(uint32_t base, uint16_t rxECCvalue)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));
    //
    // ECC value can be passed as 8 bit value in USERDATA field in a frame
    //
    ASSERT(rxECCvalue <= FSI_MAX_VALUE_USERDATA);

    HWREGH(base + FSI_O_RX_ECC_VAL) = rxECCvalue;
}

//*****************************************************************************
//
//! \brief Returns ECC Corrected data
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return 32 bit ECC corrected data
//
//*****************************************************************************
static inline uint32_t
FSI_getRxECCCorrectedData(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return(HWREG(base + FSI_O_RX_ECC_SEC_DATA));
}

//*****************************************************************************
//
//! \brief Returns ECC Log details
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return ECC Log value(8 bit)
//
//*****************************************************************************
static inline uint16_t
FSI_getRxECCLog(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return(HWREGH(base + FSI_O_RX_ECC_LOG) &
           (FSI_RX_ECC_LOG_SBE | FSI_RX_ECC_LOG_MBE));
}

//*****************************************************************************
//
//! \brief Let user generate interrupt on occurrence of Rx events
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] intNum the type of interrupt to be generated interrupt1
//!             or interrupt2
//! \param[in] intFlags contains list of events on which interrupt
//!             should be generated. Each bit will represent one event,bits for
//!             the events on which user want to generate interrupt will be set
//!             others remain clear
//!
//! \return None.
//!
//! Example Usage
//!     evtFlags = FSI_RX_EVT_PING_WD_TIMEOUT & FSI_RX_INT_TYPE_ERR
//!     FSI_enableRxInterrupt(FSI_base,FSI_INT1,evtFlags)
//!     Above call will generate interrupt1 on events
//!     FSI_RX_INT_PING_WD_TIMEOUT and FSI_RX_INT_TYPE_ERR
//
//*****************************************************************************
static inline void
FSI_enableRxInterrupt(uint32_t base, FSI_InterruptNum intNum,
                      uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    if(intNum == FSI_INT1)
    {
        HWREGH(base + FSI_O_RX_INT1_CTRL) |= (intFlags &
                                             FSI_RX_EVTMASK);
    }
    else
    {
        HWREGH(base + FSI_O_RX_INT2_CTRL) |= (intFlags &
                                             FSI_RX_EVTMASK);
    }
}

//*****************************************************************************
//
//! \brief Let user disable interrupt generation on Rx events
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] intNum the type of interrupt to be generated interrupt1
//!             or interrupt2
//! \param[in] intFlags contains list of events on which interrupt
//!             generation has to be disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxInterrupt(uint32_t base, FSI_InterruptNum intNum,
                       uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    if(intNum == FSI_INT1)
    {
        HWREGH(base + FSI_O_RX_INT1_CTRL) &= ~(intFlags &
                                              FSI_RX_EVTMASK);
    }
    else
    {
        HWREGH(base + FSI_O_RX_INT2_CTRL) &= ~(intFlags &
                                              FSI_RX_EVTMASK);
    }
}

//*****************************************************************************
//
//! \brief Returns address of Rx data buffer
//!
//! \details Data buffer is consisting of 16 words from offset- 0x40 to 0x4e
//!
//! \param[in]  base is the FSI Rx module base address
//!
//! \return Rx data buffer address
//
//*****************************************************************************
static inline uint32_t
FSI_getRxBufferAddress(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return(base + FSI_O_RX_BUF_BASE(0U));
}

//*****************************************************************************
//
//! \brief Sets the Rx Frame Reference Tag Value
//!
//! \details The reference tag is used to check against when comparing the
//! TAG_MASK and the incoming frame tag.
//!
//! \param[in]  base is the FSI Rx module base address
//! \param[in]  refVal is the Rx frame reference tag value to be set
//!
//! \return None
//
//*****************************************************************************
static inline void
FSI_setRxFrameTagRef(uint32_t base, uint16_t refVal)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Sets the Rx frame tag reference.
    //
    HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) =
          ((HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) &
           ~((uint16_t)FSI_RX_FRAME_TAG_CMP_TAG_REF_M)) |
           (refVal << FSI_RX_FRAME_TAG_CMP_TAG_REF_S));
}

//*****************************************************************************
//
//! \brief Returns the Rx Frame Reference Tag Value
//!
//! \details The reference tag is used to check against when comparing the
//! TAG_MASK and the incoming frame tag.
//!
//! \param[in]  base is the FSI Rx module base address
//!
//! \return Rx frame reference tag
//
//*****************************************************************************
static inline uint16_t
FSI_getRxFrameTagRef(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Returns the Rx frame tag reference.
    //
    return((HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) &
           FSI_RX_FRAME_TAG_CMP_TAG_REF_M) >> FSI_RX_FRAME_TAG_CMP_TAG_REF_S);
}

//*****************************************************************************
//
//! \brief Sets the Rx Frame Tag Mask Value
//!
//! \details Any bit position set to 0 will be used in the comparison of
//! incoming tag & the reference tag. A bit position set to 1 will be ignored
//! in the tag comparison.
//!
//! \param[in]  base is the FSI Rx module base address
//! \param[in]  maskVal is the Rx frame tag mask value to be set
//!
//! \return None
//
//*****************************************************************************
static inline void
FSI_setRxFrameTagMask(uint32_t base, uint16_t maskVal)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Sets the Rx frame tag mask.
    //
    HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) =
          ((HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) &
           ~((uint16_t)FSI_RX_FRAME_TAG_CMP_TAG_MASK_M)) |
           (maskVal << FSI_RX_FRAME_TAG_CMP_TAG_MASK_S));
}

//*****************************************************************************
//
//! \brief Returns the Rx Frame Tag Mask Value
//!
//! \details Any bit position set to 0 will be used in the comparison of
//! incoming tag & the reference tag. A bit position set to 1 will be ignored
//! in the tag comparison.
//!
//! \param[in]  base is the FSI Rx module base address
//!
//! \return Rx frame tag mask
//
//*****************************************************************************
static inline uint16_t
FSI_getRxFrameTagMask(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Returns the frame tag mask.
    //
    return((HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) &
          FSI_RX_FRAME_TAG_CMP_TAG_MASK_M) >> FSI_RX_FRAME_TAG_CMP_TAG_MASK_S);
}

//*****************************************************************************
//
//! \brief Enables the Rx Frame Compare Mode
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxFrameTagCompare(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Enables the frame tag compare mode.
    //
    HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) |= FSI_RX_FRAME_TAG_CMP_CMP_EN;
}

//*****************************************************************************
//
//! \brief Disables the Rx Frame Compare Mode
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxFrameTagCompare(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Disables the Rx frame tag compare mode.
    //
    HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) &=
                                   ~(uint16_t)FSI_RX_FRAME_TAG_CMP_CMP_EN;
}

//*****************************************************************************
//
//! \brief Enables the Rx Frame Broadcast Mode
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxFrameBroadcast(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Enables Rx frame broadcast mode.
    //
    HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) |= FSI_RX_FRAME_TAG_CMP_BROADCAST_EN;
}

//*****************************************************************************
//
//! \brief Disables the Rx Frame Broadcast Mode
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxFrameBroadcast(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Disables Rx frame broadcast mode.
    //
    HWREGH(base + FSI_O_RX_FRAME_TAG_CMP) &=
                                  ~(uint16_t)FSI_RX_FRAME_TAG_CMP_BROADCAST_EN;
}

//
// Ping frame related APIs
//

//*****************************************************************************
//
//! \brief Sets the Rx Ping Tag Reference Value
//!
//! \details The reference tag is used to check against when comparing the
//! TAG_MASK and the incoming ping tag.
//!
//! \param[in]  base is the FSI Rx module base address
//! \param[in]  refVal is the Rx frame reference tag value to be set
//!
//! \return None
//
//*****************************************************************************
static inline void
FSI_setRxPingTagRef(uint32_t base, uint16_t refVal)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Set Rx ping tag reference value.
    //
    HWREGH(base + FSI_O_RX_PING_TAG_CMP) =
          ((HWREGH(base + FSI_O_RX_PING_TAG_CMP) &
           ~((uint16_t)FSI_RX_PING_TAG_CMP_TAG_REF_M)) |
           (refVal << FSI_RX_PING_TAG_CMP_TAG_REF_S));
}

//*****************************************************************************
//
//! \brief Returns the Rx Ping Reference Tag Value
//!
//! \details The reference tag is used to check against when comparing the
//! TAG_MASK and the incoming ping tag.
//!
//! \param[in]  base is the FSI Rx module base address
//!
//! \return Rx ping frame reference tag
//
//*****************************************************************************
static inline uint16_t
FSI_getRxPingTagRef(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Returns Rx ping tag reference.
    //
    return((HWREGH(base + FSI_O_RX_PING_TAG_CMP) &
            FSI_RX_PING_TAG_CMP_TAG_REF_M) >> FSI_RX_PING_TAG_CMP_TAG_REF_S);
}

//*****************************************************************************
//
//! \brief Sets the Rx Ping Tag Mask Value
//!
//! \details Any bit position set to 0 will be used in the comparison of
//! incoming tag & the reference tag. A bit position set to 1 will be ignored
//! in the tag comparison.
//!
//! \param[in]  base is the FSI Rx module base address
//! \param[in]  maskVal is the Rx frame tag mask value to be set
//!
//! \return Rx ping tag mask
//
//*****************************************************************************
static inline void
FSI_setRxPingTagMask(uint32_t base, uint16_t maskVal)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Set Rx ping tag mask.
    //
    HWREGH(base + FSI_O_RX_PING_TAG_CMP) =
          ((HWREGH(base + FSI_O_RX_PING_TAG_CMP) &
           ~((uint16_t)FSI_RX_PING_TAG_CMP_TAG_MASK_M)) |
           (maskVal << FSI_RX_PING_TAG_CMP_TAG_MASK_S));
}

//*****************************************************************************
//
//! \brief Returns the Rx Ping Tag Mask Value
//!
//! \details Any bit position set to 0 will be used in the comparison of
//! incoming tag & the reference tag. A bit position set to 1 will be ignored
//! in the tag comparison.
//!
//! \param[in]  base is the FSI Rx module base address
//!
//! \return Rx ping frame reference tag mask
//
//*****************************************************************************
static inline uint16_t
FSI_getRxPingTagMask(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Returns ping tag mask.
    //
    return((HWREGH(base + FSI_O_RX_PING_TAG_CMP) &
            FSI_RX_PING_TAG_CMP_TAG_MASK_M) >> FSI_RX_PING_TAG_CMP_TAG_MASK_S);
}

//*****************************************************************************
//
//! \brief Enables the Rx Ping Compare Mode
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxPingTagCompare(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Enables the Rx ping tag compare mode.
    //
    HWREGH(base + FSI_O_RX_PING_TAG_CMP) |= FSI_RX_PING_TAG_CMP_CMP_EN;
}

//*****************************************************************************
//
//! \brief Disables the Rx Ping Compare Mode
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxPingTagCompare(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Disables Rx ping tag compare mode.
    //
    HWREGH(base + FSI_O_RX_PING_TAG_CMP) &=
                                   ~(uint16_t)FSI_RX_PING_TAG_CMP_CMP_EN;
}

//*****************************************************************************
//
//! \brief Enables the Rx Ping Broadcast Mode
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_enableRxPingBroadcast(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Enables the Rx ping broadcast mode.
    //
    HWREGH(base + FSI_O_RX_PING_TAG_CMP) |= FSI_RX_PING_TAG_CMP_BROADCAST_EN;
}

//*****************************************************************************
//
//! \brief Disables the Rx Ping Broadcast Mode
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void
FSI_disableRxPingBroadcast(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // Disables the Rx ping broadcast.
    //
    HWREGH(base + FSI_O_RX_PING_TAG_CMP) &=
                                  ~(uint16_t)FSI_RX_PING_TAG_CMP_BROADCAST_EN;
}

//*****************************************************************************
//
//! \brief Resets frame watchdog,ping watchdog or entire RX module
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] submodule is the name of module which is supposed to be reset
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_resetRxModule(uint32_t base, FSI_RxSubmoduleInReset submodule);

//*****************************************************************************
//
//! \brief Clears resets on frame watchdog,ping watchdog or entire RX module
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] submodule is the module which is to be brought out of reset
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_clearRxModuleReset(uint32_t base, FSI_RxSubmoduleInReset submodule);

//*****************************************************************************
//
//! \brief Reads data from FSI Rx buffer
//!
//! \param[in]  base is the FSI Rx module base address
//! \param[out] array is the address of the array of words to receive the data
//! \param[in]  length is the number of words in the array to be received
//! \param[in]  bufOffset is the offset in Rx buffer from where data will
//!             be read
//!
//! \note This function ensures that not more than 16 words are read and
//!       wrap around case is also taken care when more words need to be read
//!       wherein last read happens at maximum offset in Rx buffer
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_readRxBuffer(uint32_t base, uint16_t array[], uint16_t length,
                 uint16_t bufOffset);

//*****************************************************************************
//
//! \brief Adds delay for selected tap line
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] delayTapType is the line for which delay needs to be added
//!            it can be either RXCLK,RXD0 or RXD1
//! \param[in] tapValue is 5 bit value of the amount of delay to be added
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_configRxDelayLine(uint32_t base, FSI_RxDelayTapType delayTapType,
                      uint16_t tapValue);

//*****************************************************************************
//
//! \brief Initializes FSI Tx module
//!
//! \details Software based initialization of the FSI transmitter IP. This is
//!          typically needed only once during initialization or if the module
//!          needs to be reset due to an underrun condition that occurred during
//!          operation.
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] prescalar is the user configurable clock divider for PLL input
//!            clock
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_performTxInitialization(uint32_t base, uint16_t prescalar);

//*****************************************************************************
//
//! \brief Initializes FSI Rx module
//!
//! \details Software based initialization of the FSI receiver module.This is
//!         typically needed only once during initialization. However, if there
//!          are framing errors in the received frames, then the receive module
//!          needs to be reset so that subsequent frames/packets can be handled
//!          fresh.
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_performRxInitialization(uint32_t base);

//*****************************************************************************
//
//! \brief Sends Flush pattern sequence
//!
//! \details Flush pattern sequence sent by a FSI transmit module will bring
//!          the FSI receive module out of reset so that it will then be
//!          ready to receive subsequent frames.
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] prescalar is the user configurable clock divider for PLL input
//!            clock
//!
//! \return None.
//
//*****************************************************************************
extern void
FSI_executeTxFlushSequence(uint32_t base, uint16_t prescalar);

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

#endif // FSI_H