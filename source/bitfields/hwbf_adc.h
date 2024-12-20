//###########################################################################
//
// FILE:    hwbf_adc.h
//
// TITLE:   Definitions for the ADC registers.
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

#ifndef HWBF_ADC_H
#define HWBF_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// ADC Individual Register Bit Definitions:

struct ADC_ADCCTL1_BITS {               // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t INTPULSEPOS:1;             // 2 ADC Interrupt Pulse Position
    uint16_t rsvd2:4;                   // 6:3 Reserved
    uint16_t ADCPWDNZ:1;                // 7 ADC Power Down
    uint16_t ADCBSYCHN:5;               // 12:8 ADC Busy Channel
    uint16_t ADCBSY:1;                  // 13 ADC Busy
    uint16_t EXTMUXPRESELECTEN:1;       // 14 External Mux Preselect Enable
    uint16_t TDMAEN:1;                  // 15 Enable Alternate DMA Timings
};

union ADC_ADCCTL1_REG {
    uint16_t  all;
    struct  ADC_ADCCTL1_BITS  bit;
};

struct ADC_ADCCTL2_BITS {               // bits description
    uint16_t PRESCALE:4;                // 3:0 ADC Clock Prescaler
    uint16_t rsvd1:2;                   // 5:4 Reserved
    uint16_t RESOLUTION:1;              // 6 SOC Conversion Resolution
    uint16_t SIGNALMODE:1;              // 7 SOC Signaling Mode
    uint16_t OFFTRIMMODE:1;             // 8 Offset Trim Mode
    uint16_t rsvd2:4;                   // 12:9 Reserved
    uint16_t rsvd3:3;                   // 15:13 Reserved
};

union ADC_ADCCTL2_REG {
    uint16_t  all;
    struct  ADC_ADCCTL2_BITS  bit;
};

struct ADC_ADCBURSTCTL_BITS {           // bits description
    uint16_t BURSTTRIGSEL:7;            // 6:0 SOC Burst Trigger Source Select
    uint16_t rsvd1:1;                   // 7 Reserved
    uint16_t BURSTSIZE:5;               // 12:8 SOC Burst Size Select
    uint16_t rsvd2:2;                   // 14:13 Reserved
    uint16_t BURSTEN:1;                 // 15 SOC Burst Mode Enable
};

union ADC_ADCBURSTCTL_REG {
    uint16_t  all;
    struct  ADC_ADCBURSTCTL_BITS  bit;
};

struct ADC_ADCINTFLG_BITS {             // bits description
    uint16_t ADCINT1:1;                 // 0 ADC Interrupt 1 Flag
    uint16_t ADCINT2:1;                 // 1 ADC Interrupt 2 Flag
    uint16_t ADCINT3:1;                 // 2 ADC Interrupt 3 Flag
    uint16_t ADCINT4:1;                 // 3 ADC Interrupt 4 Flag
    uint16_t ADCINT1RESULT:1;           // 4 ADC Interrupt 1 Results Ready
    uint16_t ADCINT2RESULT:1;           // 5 ADC Interrupt 2 Results Ready
    uint16_t ADCINT3RESULT:1;           // 6 ADC Interrupt 3 Results Ready
    uint16_t ADCINT4RESULT:1;           // 7 ADC Interrupt 4 Results Ready
    uint16_t rsvd1:8;                   // 15:8 Reserved
};

union ADC_ADCINTFLG_REG {
    uint16_t  all;
    struct  ADC_ADCINTFLG_BITS  bit;
};

struct ADC_ADCINTFLGCLR_BITS {          // bits description
    uint16_t ADCINT1:1;                 // 0 ADC Interrupt 1 Flag Clear
    uint16_t ADCINT2:1;                 // 1 ADC Interrupt 2 Flag Clear
    uint16_t ADCINT3:1;                 // 2 ADC Interrupt 3 Flag Clear
    uint16_t ADCINT4:1;                 // 3 ADC Interrupt 4 Flag Clear
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union ADC_ADCINTFLGCLR_REG {
    uint16_t  all;
    struct  ADC_ADCINTFLGCLR_BITS  bit;
};

struct ADC_ADCINTOVF_BITS {             // bits description
    uint16_t ADCINT1:1;                 // 0 ADC Interrupt 1 Overflow Flags
    uint16_t ADCINT2:1;                 // 1 ADC Interrupt 2 Overflow Flags
    uint16_t ADCINT3:1;                 // 2 ADC Interrupt 3 Overflow Flags
    uint16_t ADCINT4:1;                 // 3 ADC Interrupt 4 Overflow Flags
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union ADC_ADCINTOVF_REG {
    uint16_t  all;
    struct  ADC_ADCINTOVF_BITS  bit;
};

struct ADC_ADCINTOVFCLR_BITS {          // bits description
    uint16_t ADCINT1:1;                 // 0 ADC Interrupt 1 Overflow Clear Bits
    uint16_t ADCINT2:1;                 // 1 ADC Interrupt 2 Overflow Clear Bits
    uint16_t ADCINT3:1;                 // 2 ADC Interrupt 3 Overflow Clear Bits
    uint16_t ADCINT4:1;                 // 3 ADC Interrupt 4 Overflow Clear Bits
    uint16_t rsvd1:12;                  // 15:4 Reserved
};

union ADC_ADCINTOVFCLR_REG {
    uint16_t  all;
    struct  ADC_ADCINTOVFCLR_BITS  bit;
};

struct ADC_ADCINTSEL1N2_BITS {          // bits description
    uint16_t INT1SEL:6;                 // 5:0 ADCINT1 EOC Source Select
    uint16_t INT1CONT:1;                // 6 ADCINT1 Continue to Interrupt Mode
    uint16_t INT1E:1;                   // 7 ADCINT1 Interrupt Enable
    uint16_t INT2SEL:6;                 // 13:8 ADCINT2 EOC Source Select
    uint16_t INT2CONT:1;                // 14 ADCINT2 Continue to Interrupt Mode
    uint16_t INT2E:1;                   // 15 ADCINT2 Interrupt Enable
};

union ADC_ADCINTSEL1N2_REG {
    uint16_t  all;
    struct  ADC_ADCINTSEL1N2_BITS  bit;
};

struct ADC_ADCINTSEL3N4_BITS {          // bits description
    uint16_t INT3SEL:6;                 // 5:0 ADCINT3 EOC Source Select
    uint16_t INT3CONT:1;                // 6 ADCINT3 Continue to Interrupt Mode
    uint16_t INT3E:1;                   // 7 ADCINT3 Interrupt Enable
    uint16_t INT4SEL:6;                 // 13:8 ADCINT4 EOC Source Select
    uint16_t INT4CONT:1;                // 14 ADCINT4 Continue to Interrupt Mode
    uint16_t INT4E:1;                   // 15 ADCINT4 Interrupt Enable
};

union ADC_ADCINTSEL3N4_REG {
    uint16_t  all;
    struct  ADC_ADCINTSEL3N4_BITS  bit;
};

struct ADC_ADCSOCPRICTL_BITS {          // bits description
    uint16_t SOCPRIORITY:6;             // 5:0 SOC Priority
    uint16_t RRPOINTER:6;               // 11:6 Round Robin Pointer
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union ADC_ADCSOCPRICTL_REG {
    uint16_t  all;
    struct  ADC_ADCSOCPRICTL_BITS  bit;
};

struct ADC_ADCINTSOCSEL1_BITS {         // bits description
    uint16_t SOC0:2;                    // 1:0 SOC0 ADC Interrupt Trigger Select
    uint16_t SOC1:2;                    // 3:2 SOC1 ADC Interrupt Trigger Select
    uint16_t SOC2:2;                    // 5:4 SOC2 ADC Interrupt Trigger Select
    uint16_t SOC3:2;                    // 7:6 SOC3 ADC Interrupt Trigger Select
    uint16_t SOC4:2;                    // 9:8 SOC4 ADC Interrupt Trigger Select
    uint16_t SOC5:2;                    // 11:10 SOC5 ADC Interrupt Trigger Select
    uint16_t SOC6:2;                    // 13:12 SOC6 ADC Interrupt Trigger Select
    uint16_t SOC7:2;                    // 15:14 SOC7 ADC Interrupt Trigger Select
    uint16_t SOC8:2;                    // 17:16 SOC8 ADC Interrupt Trigger Select
    uint16_t SOC9:2;                    // 19:18 SOC9 ADC Interrupt Trigger Select
    uint16_t SOC10:2;                   // 21:20 SOC10 ADC Interrupt Trigger Select
    uint16_t SOC11:2;                   // 23:22 SOC11 ADC Interrupt Trigger Select
    uint16_t SOC12:2;                   // 25:24 SOC12 ADC Interrupt Trigger Select
    uint16_t SOC13:2;                   // 27:26 SOC13 ADC Interrupt Trigger Select
    uint16_t SOC14:2;                   // 29:28 SOC14 ADC Interrupt Trigger Select
    uint16_t SOC15:2;                   // 31:30 SOC15 ADC Interrupt Trigger Select
};

union ADC_ADCINTSOCSEL1_REG {
    uint32_t  all;
    struct  ADC_ADCINTSOCSEL1_BITS  bit;
};

struct ADC_ADCINTSOCSEL2_BITS {         // bits description
    uint16_t SOC16:2;                   // 1:0 SOC16 ADC Interrupt Trigger Select
    uint16_t SOC17:2;                   // 3:2 SOC17 ADC Interrupt Trigger Select
    uint16_t SOC18:2;                   // 5:4 SOC18 ADC Interrupt Trigger Select
    uint16_t SOC19:2;                   // 7:6 SOC19 ADC Interrupt Trigger Select
    uint16_t SOC20:2;                   // 9:8 SOC20 ADC Interrupt Trigger Select
    uint16_t SOC21:2;                   // 11:10 SOC21 ADC Interrupt Trigger Select
    uint16_t SOC22:2;                   // 13:12 SOC22 ADC Interrupt Trigger Select
    uint16_t SOC23:2;                   // 15:14 SOC23 ADC Interrupt Trigger Select
    uint16_t SOC24:2;                   // 17:16 SOC24 ADC Interrupt Trigger Select
    uint16_t SOC25:2;                   // 19:18 SOC25 ADC Interrupt Trigger Select
    uint16_t SOC26:2;                   // 21:20 SOC26 ADC Interrupt Trigger Select
    uint16_t SOC27:2;                   // 23:22 SOC27 ADC Interrupt Trigger Select
    uint16_t SOC28:2;                   // 25:24 SOC28 ADC Interrupt Trigger Select
    uint16_t SOC29:2;                   // 27:26 SOC29 ADC Interrupt Trigger Select
    uint16_t SOC30:2;                   // 29:28 SOC30 ADC Interrupt Trigger Select
    uint16_t SOC31:2;                   // 31:30 SOC31 ADC Interrupt Trigger Select
};

union ADC_ADCINTSOCSEL2_REG {
    uint32_t  all;
    struct  ADC_ADCINTSOCSEL2_BITS  bit;
};

struct ADC_ADCSOCFLG1_BITS {            // bits description
    uint16_t SOC0:1;                    // 0 SOC0 Start of Conversion Flag
    uint16_t SOC1:1;                    // 1 SOC1 Start of Conversion Flag
    uint16_t SOC2:1;                    // 2 SOC2 Start of Conversion Flag
    uint16_t SOC3:1;                    // 3 SOC3 Start of Conversion Flag
    uint16_t SOC4:1;                    // 4 SOC4 Start of Conversion Flag
    uint16_t SOC5:1;                    // 5 SOC5 Start of Conversion Flag
    uint16_t SOC6:1;                    // 6 SOC6 Start of Conversion Flag
    uint16_t SOC7:1;                    // 7 SOC7 Start of Conversion Flag
    uint16_t SOC8:1;                    // 8 SOC8 Start of Conversion Flag
    uint16_t SOC9:1;                    // 9 SOC9 Start of Conversion Flag
    uint16_t SOC10:1;                   // 10 SOC10 Start of Conversion Flag
    uint16_t SOC11:1;                   // 11 SOC11 Start of Conversion Flag
    uint16_t SOC12:1;                   // 12 SOC12 Start of Conversion Flag
    uint16_t SOC13:1;                   // 13 SOC13 Start of Conversion Flag
    uint16_t SOC14:1;                   // 14 SOC14 Start of Conversion Flag
    uint16_t SOC15:1;                   // 15 SOC15 Start of Conversion Flag
    uint16_t SOC16:1;                   // 16 SOC16 Start of Conversion Flag
    uint16_t SOC17:1;                   // 17 SOC17 Start of Conversion Flag
    uint16_t SOC18:1;                   // 18 SOC18 Start of Conversion Flag
    uint16_t SOC19:1;                   // 19 SOC19 Start of Conversion Flag
    uint16_t SOC20:1;                   // 20 SOC20 Start of Conversion Flag
    uint16_t SOC21:1;                   // 21 SOC21 Start of Conversion Flag
    uint16_t SOC22:1;                   // 22 SOC22 Start of Conversion Flag
    uint16_t SOC23:1;                   // 23 SOC23 Start of Conversion Flag
    uint16_t SOC24:1;                   // 24 SOC24 Start of Conversion Flag
    uint16_t SOC25:1;                   // 25 SOC25 Start of Conversion Flag
    uint16_t SOC26:1;                   // 26 SOC26 Start of Conversion Flag
    uint16_t SOC27:1;                   // 27 SOC27 Start of Conversion Flag
    uint16_t SOC28:1;                   // 28 SOC28 Start of Conversion Flag
    uint16_t SOC29:1;                   // 29 SOC29 Start of Conversion Flag
    uint16_t SOC30:1;                   // 30 SOC30 Start of Conversion Flag
    uint16_t SOC31:1;                   // 31 SOC31 Start of Conversion Flag
};

union ADC_ADCSOCFLG1_REG {
    uint32_t  all;
    struct  ADC_ADCSOCFLG1_BITS  bit;
};

struct ADC_ADCSOCFRC1_BITS {            // bits description
    uint16_t SOC0:1;                    // 0 SOC0 Force Start of Conversion Bit
    uint16_t SOC1:1;                    // 1 SOC1 Force Start of Conversion Bit
    uint16_t SOC2:1;                    // 2 SOC2 Force Start of Conversion Bit
    uint16_t SOC3:1;                    // 3 SOC3 Force Start of Conversion Bit
    uint16_t SOC4:1;                    // 4 SOC4 Force Start of Conversion Bit
    uint16_t SOC5:1;                    // 5 SOC5 Force Start of Conversion Bit
    uint16_t SOC6:1;                    // 6 SOC6 Force Start of Conversion Bit
    uint16_t SOC7:1;                    // 7 SOC7 Force Start of Conversion Bit
    uint16_t SOC8:1;                    // 8 SOC8 Force Start of Conversion Bit
    uint16_t SOC9:1;                    // 9 SOC9 Force Start of Conversion Bit
    uint16_t SOC10:1;                   // 10 SOC10 Force Start of Conversion Bit
    uint16_t SOC11:1;                   // 11 SOC11 Force Start of Conversion Bit
    uint16_t SOC12:1;                   // 12 SOC12 Force Start of Conversion Bit
    uint16_t SOC13:1;                   // 13 SOC13 Force Start of Conversion Bit
    uint16_t SOC14:1;                   // 14 SOC14 Force Start of Conversion Bit
    uint16_t SOC15:1;                   // 15 SOC15 Force Start of Conversion Bit
    uint16_t SOC16:1;                   // 16 SOC16 Force Start of Conversion Bit
    uint16_t SOC17:1;                   // 17 SOC17 Force Start of Conversion Bit
    uint16_t SOC18:1;                   // 18 SOC18 Force Start of Conversion Bit
    uint16_t SOC19:1;                   // 19 SOC19 Force Start of Conversion Bit
    uint16_t SOC20:1;                   // 20 SOC20 Force Start of Conversion Bit
    uint16_t SOC21:1;                   // 21 SOC21 Force Start of Conversion Bit
    uint16_t SOC22:1;                   // 22 SOC22 Force Start of Conversion Bit
    uint16_t SOC23:1;                   // 23 SOC23 Force Start of Conversion Bit
    uint16_t SOC24:1;                   // 24 SOC24 Force Start of Conversion Bit
    uint16_t SOC25:1;                   // 25 SOC25 Force Start of Conversion Bit
    uint16_t SOC26:1;                   // 26 SOC26 Force Start of Conversion Bit
    uint16_t SOC27:1;                   // 27 SOC27 Force Start of Conversion Bit
    uint16_t SOC28:1;                   // 28 SOC28 Force Start of Conversion Bit
    uint16_t SOC29:1;                   // 29 SOC29 Force Start of Conversion Bit
    uint16_t SOC30:1;                   // 30 SOC30 Force Start of Conversion Bit
    uint16_t SOC31:1;                   // 31 SOC31 Force Start of Conversion Bit
};

union ADC_ADCSOCFRC1_REG {
    uint32_t  all;
    struct  ADC_ADCSOCFRC1_BITS  bit;
};

struct ADC_ADCSOCOVF1_BITS {            // bits description
    uint16_t SOC0:1;                    // 0 SOC0 Start of Conversion Overflow Flag
    uint16_t SOC1:1;                    // 1 SOC1 Start of Conversion Overflow Flag
    uint16_t SOC2:1;                    // 2 SOC2 Start of Conversion Overflow Flag
    uint16_t SOC3:1;                    // 3 SOC3 Start of Conversion Overflow Flag
    uint16_t SOC4:1;                    // 4 SOC4 Start of Conversion Overflow Flag
    uint16_t SOC5:1;                    // 5 SOC5 Start of Conversion Overflow Flag
    uint16_t SOC6:1;                    // 6 SOC6 Start of Conversion Overflow Flag
    uint16_t SOC7:1;                    // 7 SOC7 Start of Conversion Overflow Flag
    uint16_t SOC8:1;                    // 8 SOC8 Start of Conversion Overflow Flag
    uint16_t SOC9:1;                    // 9 SOC9 Start of Conversion Overflow Flag
    uint16_t SOC10:1;                   // 10 SOC10 Start of Conversion Overflow Flag
    uint16_t SOC11:1;                   // 11 SOC11 Start of Conversion Overflow Flag
    uint16_t SOC12:1;                   // 12 SOC12 Start of Conversion Overflow Flag
    uint16_t SOC13:1;                   // 13 SOC13 Start of Conversion Overflow Flag
    uint16_t SOC14:1;                   // 14 SOC14 Start of Conversion Overflow Flag
    uint16_t SOC15:1;                   // 15 SOC15 Start of Conversion Overflow Flag
    uint16_t SOC16:1;                   // 16 SOC16 Start of Conversion Overflow Flag
    uint16_t SOC17:1;                   // 17 SOC17 Start of Conversion Overflow Flag
    uint16_t SOC18:1;                   // 18 SOC18 Start of Conversion Overflow Flag
    uint16_t SOC19:1;                   // 19 SOC19 Start of Conversion Overflow Flag
    uint16_t SOC20:1;                   // 20 SOC20 Start of Conversion Overflow Flag
    uint16_t SOC21:1;                   // 21 SOC21 Start of Conversion Overflow Flag
    uint16_t SOC22:1;                   // 22 SOC22 Start of Conversion Overflow Flag
    uint16_t SOC23:1;                   // 23 SOC23 Start of Conversion Overflow Flag
    uint16_t SOC24:1;                   // 24 SOC24 Start of Conversion Overflow Flag
    uint16_t SOC25:1;                   // 25 SOC25 Start of Conversion Overflow Flag
    uint16_t SOC26:1;                   // 26 SOC26 Start of Conversion Overflow Flag
    uint16_t SOC27:1;                   // 27 SOC27 Start of Conversion Overflow Flag
    uint16_t SOC28:1;                   // 28 SOC28 Start of Conversion Overflow Flag
    uint16_t SOC29:1;                   // 29 SOC29 Start of Conversion Overflow Flag
    uint16_t SOC30:1;                   // 30 SOC30 Start of Conversion Overflow Flag
    uint16_t SOC31:1;                   // 31 SOC31 Start of Conversion Overflow Flag
};

union ADC_ADCSOCOVF1_REG {
    uint32_t  all;
    struct  ADC_ADCSOCOVF1_BITS  bit;
};

struct ADC_ADCSOCOVFCLR1_BITS {         // bits description
    uint16_t SOC0:1;                    // 0 SOC0 Clear Start of Conversion Overflow Bit
    uint16_t SOC1:1;                    // 1 SOC1 Clear Start of Conversion Overflow Bit
    uint16_t SOC2:1;                    // 2 SOC2 Clear Start of Conversion Overflow Bit
    uint16_t SOC3:1;                    // 3 SOC3 Clear Start of Conversion Overflow Bit
    uint16_t SOC4:1;                    // 4 SOC4 Clear Start of Conversion Overflow Bit
    uint16_t SOC5:1;                    // 5 SOC5 Clear Start of Conversion Overflow Bit
    uint16_t SOC6:1;                    // 6 SOC6 Clear Start of Conversion Overflow Bit
    uint16_t SOC7:1;                    // 7 SOC7 Clear Start of Conversion Overflow Bit
    uint16_t SOC8:1;                    // 8 SOC8 Clear Start of Conversion Overflow Bit
    uint16_t SOC9:1;                    // 9 SOC9 Clear Start of Conversion Overflow Bit
    uint16_t SOC10:1;                   // 10 SOC10 Clear Start of Conversion Overflow Bit
    uint16_t SOC11:1;                   // 11 SOC11 Clear Start of Conversion Overflow Bit
    uint16_t SOC12:1;                   // 12 SOC12 Clear Start of Conversion Overflow Bit
    uint16_t SOC13:1;                   // 13 SOC13 Clear Start of Conversion Overflow Bit
    uint16_t SOC14:1;                   // 14 SOC14 Clear Start of Conversion Overflow Bit
    uint16_t SOC15:1;                   // 15 SOC15 Clear Start of Conversion Overflow Bit
    uint16_t SOC16:1;                   // 16 SOC16 Clear Start of Conversion Overflow Bit
    uint16_t SOC17:1;                   // 17 SOC17 Clear Start of Conversion Overflow Bit
    uint16_t SOC18:1;                   // 18 SOC18 Clear Start of Conversion Overflow Bit
    uint16_t SOC19:1;                   // 19 SOC19 Clear Start of Conversion Overflow Bit
    uint16_t SOC20:1;                   // 20 SOC20 Clear Start of Conversion Overflow Bit
    uint16_t SOC21:1;                   // 21 SOC21 Clear Start of Conversion Overflow Bit
    uint16_t SOC22:1;                   // 22 SOC22 Clear Start of Conversion Overflow Bit
    uint16_t SOC23:1;                   // 23 SOC23 Clear Start of Conversion Overflow Bit
    uint16_t SOC24:1;                   // 24 SOC24 Clear Start of Conversion Overflow Bit
    uint16_t SOC25:1;                   // 25 SOC25 Clear Start of Conversion Overflow Bit
    uint16_t SOC26:1;                   // 26 SOC26 Clear Start of Conversion Overflow Bit
    uint16_t SOC27:1;                   // 27 SOC27 Clear Start of Conversion Overflow Bit
    uint16_t SOC28:1;                   // 28 SOC28 Clear Start of Conversion Overflow Bit
    uint16_t SOC29:1;                   // 29 SOC29 Clear Start of Conversion Overflow Bit
    uint16_t SOC30:1;                   // 30 SOC30 Clear Start of Conversion Overflow Bit
    uint16_t SOC31:1;                   // 31 SOC31 Clear Start of Conversion Overflow Bit
};

union ADC_ADCSOCOVFCLR1_REG {
    uint32_t  all;
    struct  ADC_ADCSOCOVFCLR1_BITS  bit;
};

struct ADC_ADCSOC0CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC0 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC0 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC0 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC0 External Channel Mux Select
};

union ADC_ADCSOC0CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC0CTL_BITS  bit;
};

struct ADC_ADCSOC1CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC1 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC1 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC1 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC1 External Channel Mux Select
};

union ADC_ADCSOC1CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC1CTL_BITS  bit;
};

struct ADC_ADCSOC2CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC2 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC2 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC2 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC2 External Channel Mux Select
};

union ADC_ADCSOC2CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC2CTL_BITS  bit;
};

struct ADC_ADCSOC3CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC3 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC3 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC3 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC3 External Channel Mux Select
};

union ADC_ADCSOC3CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC3CTL_BITS  bit;
};

struct ADC_ADCSOC4CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC4 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC4 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC4 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC4 External Channel Mux Select
};

union ADC_ADCSOC4CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC4CTL_BITS  bit;
};

struct ADC_ADCSOC5CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC5 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC5 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC5 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC5 External Channel Mux Select
};

union ADC_ADCSOC5CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC5CTL_BITS  bit;
};

struct ADC_ADCSOC6CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC6 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC6 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC6 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC6 External Channel Mux Select
};

union ADC_ADCSOC6CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC6CTL_BITS  bit;
};

struct ADC_ADCSOC7CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC7 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC7 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC7 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC7 External Channel Mux Select
};

union ADC_ADCSOC7CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC7CTL_BITS  bit;
};

struct ADC_ADCSOC8CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC8 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC8 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC8 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC8 External Channel Mux Select
};

union ADC_ADCSOC8CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC8CTL_BITS  bit;
};

struct ADC_ADCSOC9CTL_BITS {            // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC9 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC9 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC9 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC9 External Channel Mux Select
};

union ADC_ADCSOC9CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC9CTL_BITS  bit;
};

struct ADC_ADCSOC10CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC10 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC10 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC10 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC10 External Channel Mux Select
};

union ADC_ADCSOC10CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC10CTL_BITS  bit;
};

struct ADC_ADCSOC11CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC11 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC11 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC11 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC11 External Channel Mux Select
};

union ADC_ADCSOC11CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC11CTL_BITS  bit;
};

struct ADC_ADCSOC12CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC12 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC12 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC12 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC12 External Channel Mux Select
};

union ADC_ADCSOC12CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC12CTL_BITS  bit;
};

struct ADC_ADCSOC13CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC13 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC13 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC13 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC13 External Channel Mux Select
};

union ADC_ADCSOC13CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC13CTL_BITS  bit;
};

struct ADC_ADCSOC14CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC14 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC14 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC14 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC14 External Channel Mux Select
};

union ADC_ADCSOC14CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC14CTL_BITS  bit;
};

struct ADC_ADCSOC15CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC15 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC15 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC15 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC15 External Channel Mux Select
};

union ADC_ADCSOC15CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC15CTL_BITS  bit;
};

struct ADC_ADCSOC16CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC16 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC16 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC16 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC16 External Channel Mux Select
};

union ADC_ADCSOC16CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC16CTL_BITS  bit;
};

struct ADC_ADCSOC17CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC17 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC17 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC17 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC17 External Channel Mux Select
};

union ADC_ADCSOC17CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC17CTL_BITS  bit;
};

struct ADC_ADCSOC18CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC18 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC18 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC18 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC18 External Channel Mux Select
};

union ADC_ADCSOC18CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC18CTL_BITS  bit;
};

struct ADC_ADCSOC19CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC19 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC19 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC19 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC19 External Channel Mux Select
};

union ADC_ADCSOC19CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC19CTL_BITS  bit;
};

struct ADC_ADCSOC20CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC20 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC20 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC20 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC20 External Channel Mux Select
};

union ADC_ADCSOC20CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC20CTL_BITS  bit;
};

struct ADC_ADCSOC21CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC21 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC21 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC21 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC21 External Channel Mux Select
};

union ADC_ADCSOC21CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC21CTL_BITS  bit;
};

struct ADC_ADCSOC22CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC22 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC22 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC22 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC22 External Channel Mux Select
};

union ADC_ADCSOC22CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC22CTL_BITS  bit;
};

struct ADC_ADCSOC23CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC23 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC23 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC23 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC23 External Channel Mux Select
};

union ADC_ADCSOC23CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC23CTL_BITS  bit;
};

struct ADC_ADCSOC24CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC24 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC24 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC24 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC24 External Channel Mux Select
};

union ADC_ADCSOC24CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC24CTL_BITS  bit;
};

struct ADC_ADCSOC25CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC25 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC25 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC25 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC25 External Channel Mux Select
};

union ADC_ADCSOC25CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC25CTL_BITS  bit;
};

struct ADC_ADCSOC26CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC26 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC26 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC26 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC26 External Channel Mux Select
};

union ADC_ADCSOC26CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC26CTL_BITS  bit;
};

struct ADC_ADCSOC27CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC27 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC27 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC27 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC27 External Channel Mux Select
};

union ADC_ADCSOC27CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC27CTL_BITS  bit;
};

struct ADC_ADCSOC28CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC28 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC28 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC28 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC28 External Channel Mux Select
};

union ADC_ADCSOC28CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC28CTL_BITS  bit;
};

struct ADC_ADCSOC29CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC29 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC29 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC29 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC29 External Channel Mux Select
};

union ADC_ADCSOC29CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC29CTL_BITS  bit;
};

struct ADC_ADCSOC30CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC30 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC30 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC30 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC30 External Channel Mux Select
};

union ADC_ADCSOC30CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC30CTL_BITS  bit;
};

struct ADC_ADCSOC31CTL_BITS {           // bits description
    uint16_t ACQPS:9;                   // 8:0 SOC31 Acquisition Prescale
    uint16_t rsvd1:1;                   // 9 Reserved
    uint16_t rsvd2:2;                   // 11:10 Reserved
    uint16_t rsvd3:3;                   // 14:12 Reserved
    uint32_t CHSEL:5;                   // 19:15 SOC31 Channel Select
    uint16_t TRIGSEL:7;                 // 26:20 SOC31 Trigger Source Select
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EXTCHSEL:4;                // 31:28 SOC31 External Channel Mux Select
};

union ADC_ADCSOC31CTL_REG {
    uint32_t  all;
    struct  ADC_ADCSOC31CTL_BITS  bit;
};

struct ADC_ADCEVTSTAT_BITS {            // bits description
    uint16_t PPB1TRIPHI:1;              // 0 Post Processing Block 1 Trip High Flag
    uint16_t PPB1TRIPLO:1;              // 1 Post Processing Block 1 Trip Low Flag
    uint16_t PPB1ZERO:1;                // 2 Post Processing Block 1 Zero Crossing Flag
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t PPB2TRIPHI:1;              // 4 Post Processing Block 2 Trip High Flag
    uint16_t PPB2TRIPLO:1;              // 5 Post Processing Block 2 Trip Low Flag
    uint16_t PPB2ZERO:1;                // 6 Post Processing Block 2 Zero Crossing Flag
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t PPB3TRIPHI:1;              // 8 Post Processing Block 3 Trip High Flag
    uint16_t PPB3TRIPLO:1;              // 9 Post Processing Block 3 Trip Low Flag
    uint16_t PPB3ZERO:1;                // 10 Post Processing Block 3 Zero Crossing Flag
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t PPB4TRIPHI:1;              // 12 Post Processing Block 4 Trip High Flag
    uint16_t PPB4TRIPLO:1;              // 13 Post Processing Block 4 Trip Low Flag
    uint16_t PPB4ZERO:1;                // 14 Post Processing Block 4 Zero Crossing Flag
    uint16_t rsvd4:1;                   // 15 Reserved
};

union ADC_ADCEVTSTAT_REG {
    uint16_t  all;
    struct  ADC_ADCEVTSTAT_BITS  bit;
};

struct ADC_ADCEVTCLR_BITS {             // bits description
    uint16_t PPB1TRIPHI:1;              // 0 Post Processing Block 1 Trip High Clear
    uint16_t PPB1TRIPLO:1;              // 1 Post Processing Block 1 Trip Low Clear
    uint16_t PPB1ZERO:1;                // 2 Post Processing Block 1 Zero Crossing Clear
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t PPB2TRIPHI:1;              // 4 Post Processing Block 2 Trip High Clear
    uint16_t PPB2TRIPLO:1;              // 5 Post Processing Block 2 Trip Low Clear
    uint16_t PPB2ZERO:1;                // 6 Post Processing Block 2 Zero Crossing Clear
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t PPB3TRIPHI:1;              // 8 Post Processing Block 3 Trip High Clear
    uint16_t PPB3TRIPLO:1;              // 9 Post Processing Block 3 Trip Low Clear
    uint16_t PPB3ZERO:1;                // 10 Post Processing Block 3 Zero Crossing Clear
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t PPB4TRIPHI:1;              // 12 Post Processing Block 4 Trip High Clear
    uint16_t PPB4TRIPLO:1;              // 13 Post Processing Block 4 Trip Low Clear
    uint16_t PPB4ZERO:1;                // 14 Post Processing Block 4 Zero Crossing Clear
    uint16_t rsvd4:1;                   // 15 Reserved
};

union ADC_ADCEVTCLR_REG {
    uint16_t  all;
    struct  ADC_ADCEVTCLR_BITS  bit;
};

struct ADC_ADCEVTSEL_BITS {             // bits description
    uint16_t PPB1TRIPHI:1;              // 0 Post Processing Block 1 Trip High Event Enable
    uint16_t PPB1TRIPLO:1;              // 1 Post Processing Block 1 Trip Low Event Enable
    uint16_t PPB1ZERO:1;                // 2 Post Processing Block 1 Zero Crossing Event Enable
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t PPB2TRIPHI:1;              // 4 Post Processing Block 2 Trip High Event Enable
    uint16_t PPB2TRIPLO:1;              // 5 Post Processing Block 2 Trip Low Event Enable
    uint16_t PPB2ZERO:1;                // 6 Post Processing Block 2 Zero Crossing Event Enable
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t PPB3TRIPHI:1;              // 8 Post Processing Block 3 Trip High Event Enable
    uint16_t PPB3TRIPLO:1;              // 9 Post Processing Block 3 Trip Low Event Enable
    uint16_t PPB3ZERO:1;                // 10 Post Processing Block 3 Zero Crossing Event Enable
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t PPB4TRIPHI:1;              // 12 Post Processing Block 4 Trip High Event Enable
    uint16_t PPB4TRIPLO:1;              // 13 Post Processing Block 4 Trip Low Event Enable
    uint16_t PPB4ZERO:1;                // 14 Post Processing Block 4 Zero Crossing Event Enable
    uint16_t rsvd4:1;                   // 15 Reserved
};

union ADC_ADCEVTSEL_REG {
    uint16_t  all;
    struct  ADC_ADCEVTSEL_BITS  bit;
};

struct ADC_ADCEVTINTSEL_BITS {          // bits description
    uint16_t PPB1TRIPHI:1;              // 0 Post Processing Block 1 Trip High Interrupt Enable
    uint16_t PPB1TRIPLO:1;              // 1 Post Processing Block 1 Trip Low Interrupt Enable
    uint16_t PPB1ZERO:1;                // 2 Post Processing Block 1 Zero Crossing Interrupt Enable
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t PPB2TRIPHI:1;              // 4 Post Processing Block 2 Trip High Interrupt Enable
    uint16_t PPB2TRIPLO:1;              // 5 Post Processing Block 2 Trip Low Interrupt Enable
    uint16_t PPB2ZERO:1;                // 6 Post Processing Block 2 Zero Crossing Interrupt Enable
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t PPB3TRIPHI:1;              // 8 Post Processing Block 3 Trip High Interrupt Enable
    uint16_t PPB3TRIPLO:1;              // 9 Post Processing Block 3 Trip Low Interrupt Enable
    uint16_t PPB3ZERO:1;                // 10 Post Processing Block 3 Zero Crossing Interrupt Enable
    uint16_t rsvd3:1;                   // 11 Reserved
    uint16_t PPB4TRIPHI:1;              // 12 Post Processing Block 4 Trip High Interrupt Enable
    uint16_t PPB4TRIPLO:1;              // 13 Post Processing Block 4 Trip Low Interrupt Enable
    uint16_t PPB4ZERO:1;                // 14 Post Processing Block 4 Zero Crossing Interrupt Enable
    uint16_t rsvd4:1;                   // 15 Reserved
};

union ADC_ADCEVTINTSEL_REG {
    uint16_t  all;
    struct  ADC_ADCEVTINTSEL_BITS  bit;
};

struct ADC_ADCOSDETECT_BITS {           // bits description
    uint16_t DETECTCFG:3;               // 2:0 ADC Opens and Shorts Detect Configuration
    uint16_t rsvd1:13;                  // 15:3 Reserved
};

union ADC_ADCOSDETECT_REG {
    uint16_t  all;
    struct  ADC_ADCOSDETECT_BITS  bit;
};

struct ADC_ADCCOUNTER_BITS {            // bits description
    uint16_t FREECOUNT:12;              // 11:0 ADC Free Running Counter Value
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union ADC_ADCCOUNTER_REG {
    uint16_t  all;
    struct  ADC_ADCCOUNTER_BITS  bit;
};

struct ADC_ADCREV_BITS {                // bits description
    uint16_t TYPE:8;                    // 7:0 ADC Type
    uint16_t REV:8;                     // 15:8 ADC Revision
};

union ADC_ADCREV_REG {
    uint16_t  all;
    struct  ADC_ADCREV_BITS  bit;
};

struct ADC_ADCOFFTRIM_BITS {            // bits description
    uint16_t OFFTRIM:8;                 // 7:0 ADC Offset Trim 12B SE Even
    uint16_t OFFTRIM12BSEODD:8;         // 15:8 ADC Offset Trim 12B SE Odd
};

union ADC_ADCOFFTRIM_REG {
    uint16_t  all;
    struct  ADC_ADCOFFTRIM_BITS  bit;
};

struct ADC_ADCOFFTRIM2_BITS {           // bits description
    uint16_t OFFTRIM16BSEEVEN:8;        // 7:0 ADC Offset Trim 16B SE Even
    uint16_t OFFTRIM16BSEODD:8;         // 15:8 ADC Offset Trim 16B SE Odd
};

union ADC_ADCOFFTRIM2_REG {
    uint16_t  all;
    struct  ADC_ADCOFFTRIM2_BITS  bit;
};

struct ADC_ADCOFFTRIM3_BITS {           // bits description
    uint16_t OFFTRIM12BDE:8;            // 7:0 ADC Offset Trim 12B DE
    uint16_t OFFTRIM16BDE:8;            // 15:8 ADC Offset Trim 16B DE
};

union ADC_ADCOFFTRIM3_REG {
    uint16_t  all;
    struct  ADC_ADCOFFTRIM3_BITS  bit;
};

struct ADC_ADCPPB1CONFIG_BITS {         // bits description
    uint16_t CONFIG:5;                  // 4:0 ADC Post Processing Block 1 Configuration
    uint16_t CBCEN:1;                   // 5 Cycle By Cycle Enable
    uint16_t ABSEN:1;                   // 6 ADC Post Processing Block 1 Absolute Enable
    uint16_t TWOSCOMPEN:1;              // 7 ADC Post Processing Block 1 Two's Complement Enable
    uint16_t DELTAEN:1;                 // 8 ADC Post Processing Block 1 Last Sample Delta Enable
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union ADC_ADCPPB1CONFIG_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1CONFIG_BITS  bit;
};

struct ADC_ADCPPB1STAMP_BITS {          // bits description
    uint16_t DLYSTAMP:12;               // 11:0 ADC Post Processing Block 1 Delay Time Stamp
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union ADC_ADCPPB1STAMP_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1STAMP_BITS  bit;
};

struct ADC_ADCPPB1OFFCAL_BITS {         // bits description
    uint16_t OFFCAL:10;                 // 9:0 ADC Post Processing Block Offset Correction
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB1OFFCAL_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1OFFCAL_BITS  bit;
};

struct ADC_ADCPPB1TRIPHI_BITS {         // bits description
    uint32_t LIMITHI:24;                // 23:0 ADC Post Processing Block 1 Trip High Limit
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_ADCPPB1TRIPHI_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1TRIPHI_BITS  bit;
};

struct ADC_ADCPPB1TRIPLO_BITS {         // bits description
    uint16_t LIMITLO:16;                // 15:0 ADC Post Processing Block 1 Trip Low Limit
    uint16_t LSIGN:1;                   // 16 Low Limit Sign Bit
    uint16_t rsvd1:2;                   // 18:17 Reserved
    uint16_t LIMITLO2EN:1;              // 19 Extended Low Limit 2 Enable
    uint16_t REQSTAMP:12;               // 31:20 ADC Post Processing Block 1 Request Time Stamp
};

union ADC_ADCPPB1TRIPLO_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1TRIPLO_BITS  bit;
};

struct ADC_ADCPPBTRIP1FILCTL_BITS {     // bits description
    uint16_t FILTHIEN:1;                // 0 ADCPPB1 TRIPHI Filter Enable
    uint16_t FILTLOEN:1;                // 1 ADCPPB1 TRIPLO Filter Enable
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t SAMPWIN:6;                 // 8:3 Sample Window
    uint16_t THRESH:6;                  // 14:9 Majority Voting Threshold
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union ADC_ADCPPBTRIP1FILCTL_REG {
    uint16_t  all;
    struct  ADC_ADCPPBTRIP1FILCTL_BITS  bit;
};

struct ADC_ADCPPBTRIP1FILCLKCTL_BITS {  // bits description
    uint16_t CLKPRESCALE:16;            // 15:0 Filter Clock Prescale
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_ADCPPBTRIP1FILCLKCTL_REG {
    uint32_t  all;
    struct  ADC_ADCPPBTRIP1FILCLKCTL_BITS  bit;
};

struct ADC_ADCPPB2CONFIG_BITS {         // bits description
    uint16_t CONFIG:5;                  // 4:0 ADC Post Processing Block 2 Configuration
    uint16_t CBCEN:1;                   // 5 Cycle By Cycle Enable
    uint16_t ABSEN:1;                   // 6 ADC Post Processing Block 2 Absolute Enable
    uint16_t TWOSCOMPEN:1;              // 7 ADC Post Processing Block 2 Two's Complement Enable
    uint16_t DELTAEN:1;                 // 8 ADC Post Processing Block 2 Last Sample Delta Enable
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union ADC_ADCPPB2CONFIG_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2CONFIG_BITS  bit;
};

struct ADC_ADCPPB2STAMP_BITS {          // bits description
    uint16_t DLYSTAMP:12;               // 11:0 ADC Post Processing Block 2 Delay Time Stamp
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union ADC_ADCPPB2STAMP_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2STAMP_BITS  bit;
};

struct ADC_ADCPPB2OFFCAL_BITS {         // bits description
    uint16_t OFFCAL:10;                 // 9:0 ADC Post Processing Block Offset Correction
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB2OFFCAL_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2OFFCAL_BITS  bit;
};

struct ADC_ADCPPB2TRIPHI_BITS {         // bits description
    uint32_t LIMITHI:24;                // 23:0 ADC Post Processing Block 2 Trip High Limit
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_ADCPPB2TRIPHI_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2TRIPHI_BITS  bit;
};

struct ADC_ADCPPB2TRIPLO_BITS {         // bits description
    uint16_t LIMITLO:16;                // 15:0 ADC Post Processing Block 2 Trip Low Limit
    uint16_t LSIGN:1;                   // 16 Low Limit Sign Bit
    uint16_t rsvd1:2;                   // 18:17 Reserved
    uint16_t LIMITLO2EN:1;              // 19 Extended Low Limit 2 Enable
    uint16_t REQSTAMP:12;               // 31:20 ADC Post Processing Block 2 Request Time Stamp
};

union ADC_ADCPPB2TRIPLO_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2TRIPLO_BITS  bit;
};

struct ADC_ADCPPBTRIP2FILCTL_BITS {     // bits description
    uint16_t FILTHIEN:1;                // 0 ADCPPB2 TRIPHI Filter Enable
    uint16_t FILTLOEN:1;                // 1 ADCPPB2 TRIPLO Filter Enable
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t SAMPWIN:6;                 // 8:3 Sample Window
    uint16_t THRESH:6;                  // 14:9 Majority Voting Threshold
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union ADC_ADCPPBTRIP2FILCTL_REG {
    uint16_t  all;
    struct  ADC_ADCPPBTRIP2FILCTL_BITS  bit;
};

struct ADC_ADCPPBTRIP2FILCLKCTL_BITS {  // bits description
    uint16_t CLKPRESCALE:16;            // 15:0 Filter Clock Prescale
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_ADCPPBTRIP2FILCLKCTL_REG {
    uint32_t  all;
    struct  ADC_ADCPPBTRIP2FILCLKCTL_BITS  bit;
};

struct ADC_ADCPPB3CONFIG_BITS {         // bits description
    uint16_t CONFIG:5;                  // 4:0 ADC Post Processing Block 3 Configuration
    uint16_t CBCEN:1;                   // 5 Cycle By Cycle Enable
    uint16_t ABSEN:1;                   // 6 ADC Post Processing Block 3 Absolute Enable
    uint16_t TWOSCOMPEN:1;              // 7 ADC Post Processing Block 3 Two's Complement Enable
    uint16_t DELTAEN:1;                 // 8 ADC Post Processing Block 3 Last Sample Delta Enable
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union ADC_ADCPPB3CONFIG_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3CONFIG_BITS  bit;
};

struct ADC_ADCPPB3STAMP_BITS {          // bits description
    uint16_t DLYSTAMP:12;               // 11:0 ADC Post Processing Block 3 Delay Time Stamp
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union ADC_ADCPPB3STAMP_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3STAMP_BITS  bit;
};

struct ADC_ADCPPB3OFFCAL_BITS {         // bits description
    uint16_t OFFCAL:10;                 // 9:0 ADC Post Processing Block Offset Correction
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB3OFFCAL_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3OFFCAL_BITS  bit;
};

struct ADC_ADCPPB3TRIPHI_BITS {         // bits description
    uint32_t LIMITHI:24;                // 23:0 ADC Post Processing Block 3 Trip High Limit
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_ADCPPB3TRIPHI_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3TRIPHI_BITS  bit;
};

struct ADC_ADCPPB3TRIPLO_BITS {         // bits description
    uint16_t LIMITLO:16;                // 15:0 ADC Post Processing Block 3 Trip Low Limit
    uint16_t LSIGN:1;                   // 16 Low Limit Sign Bit
    uint16_t rsvd1:2;                   // 18:17 Reserved
    uint16_t LIMITLO2EN:1;              // 19 Extended Low Limit 2 Enable
    uint16_t REQSTAMP:12;               // 31:20 ADC Post Processing Block 3 Request Time Stamp
};

union ADC_ADCPPB3TRIPLO_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3TRIPLO_BITS  bit;
};

struct ADC_ADCPPBTRIP3FILCTL_BITS {     // bits description
    uint16_t FILTHIEN:1;                // 0 ADCPPB3 TRIPHI Filter Enable
    uint16_t FILTLOEN:1;                // 1 ADCPPB3 TRIPLO Filter Enable
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t SAMPWIN:6;                 // 8:3 Sample Window
    uint16_t THRESH:6;                  // 14:9 Majority Voting Threshold
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union ADC_ADCPPBTRIP3FILCTL_REG {
    uint16_t  all;
    struct  ADC_ADCPPBTRIP3FILCTL_BITS  bit;
};

struct ADC_ADCPPBTRIP3FILCLKCTL_BITS {  // bits description
    uint16_t CLKPRESCALE:16;            // 15:0 Filter Clock Prescale
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_ADCPPBTRIP3FILCLKCTL_REG {
    uint32_t  all;
    struct  ADC_ADCPPBTRIP3FILCLKCTL_BITS  bit;
};

struct ADC_ADCPPB4CONFIG_BITS {         // bits description
    uint16_t CONFIG:5;                  // 4:0 ADC Post Processing Block 4 Configuration
    uint16_t CBCEN:1;                   // 5 Cycle By Cycle Enable
    uint16_t ABSEN:1;                   // 6 ADC Post Processing Block 4 Absolute Enable
    uint16_t TWOSCOMPEN:1;              // 7 ADC Post Processing Block 4 Two's Complement Enable
    uint16_t DELTAEN:1;                 // 8 ADC Post Processing Block 4 Last Sample Delta Enable
    uint16_t rsvd1:7;                   // 15:9 Reserved
};

union ADC_ADCPPB4CONFIG_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4CONFIG_BITS  bit;
};

struct ADC_ADCPPB4STAMP_BITS {          // bits description
    uint16_t DLYSTAMP:12;               // 11:0 ADC Post Processing Block 4 Delay Time Stamp
    uint16_t rsvd1:4;                   // 15:12 Reserved
};

union ADC_ADCPPB4STAMP_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4STAMP_BITS  bit;
};

struct ADC_ADCPPB4OFFCAL_BITS {         // bits description
    uint16_t OFFCAL:10;                 // 9:0 ADC Post Processing Block Offset Correction
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB4OFFCAL_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4OFFCAL_BITS  bit;
};

struct ADC_ADCPPB4TRIPHI_BITS {         // bits description
    uint32_t LIMITHI:24;                // 23:0 ADC Post Processing Block 4 Trip High Limit
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_ADCPPB4TRIPHI_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4TRIPHI_BITS  bit;
};

struct ADC_ADCPPB4TRIPLO_BITS {         // bits description
    uint16_t LIMITLO:16;                // 15:0 ADC Post Processing Block 4 Trip Low Limit
    uint16_t LSIGN:1;                   // 16 Low Limit Sign Bit
    uint16_t rsvd1:2;                   // 18:17 Reserved
    uint16_t LIMITLO2EN:1;              // 19 Extended Low Limit 2 Enable
    uint16_t REQSTAMP:12;               // 31:20 ADC Post Processing Block 4 Request Time Stamp
};

union ADC_ADCPPB4TRIPLO_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4TRIPLO_BITS  bit;
};

struct ADC_ADCPPBTRIP4FILCTL_BITS {     // bits description
    uint16_t FILTHIEN:1;                // 0 ADCPPB4 TRIPHI Filter Enable
    uint16_t FILTLOEN:1;                // 1 ADCPPB4 TRIPLO Filter Enable
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t SAMPWIN:6;                 // 8:3 Sample Window
    uint16_t THRESH:6;                  // 14:9 Majority Voting Threshold
    uint16_t FILINIT:1;                 // 15 Filter Initialization Bit
};

union ADC_ADCPPBTRIP4FILCTL_REG {
    uint16_t  all;
    struct  ADC_ADCPPBTRIP4FILCTL_BITS  bit;
};

struct ADC_ADCPPBTRIP4FILCLKCTL_BITS {  // bits description
    uint16_t CLKPRESCALE:16;            // 15:0 Filter Clock Prescale
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_ADCPPBTRIP4FILCLKCTL_REG {
    uint32_t  all;
    struct  ADC_ADCPPBTRIP4FILCLKCTL_BITS  bit;
};

struct ADC_ADCSAFECHECKRESEN_BITS {     // bits description
    uint16_t SOC0CHKEN:2;               // 1:0 ADC SOC0 Safety Checker Result Enable
    uint16_t SOC1CHKEN:2;               // 3:2 ADC SOC1 Safety Checker Result Enable
    uint16_t SOC2CHKEN:2;               // 5:4 ADC SOC2 Safety Checker Result Enable
    uint16_t SOC3CHKEN:2;               // 7:6 ADC SOC3 Safety Checker Result Enable
    uint16_t SOC4CHKEN:2;               // 9:8 ADC SOC4 Safety Checker Result Enable
    uint16_t SOC5CHKEN:2;               // 11:10 ADC SOC5 Safety Checker Result Enable
    uint16_t SOC6CHKEN:2;               // 13:12 ADC SOC6 Safety Checker Result Enable
    uint16_t SOC7CHKEN:2;               // 15:14 ADC SOC7 Safety Checker Result Enable
    uint16_t SOC8CHKEN:2;               // 17:16 ADC SOC8 Safety Checker Result Enable
    uint16_t SOC9CHKEN:2;               // 19:18 ADC SOC9 Safety Checker Result Enable
    uint16_t SOC10CHKEN:2;              // 21:20 ADC SOC10 Safety Checker Result Enable
    uint16_t SOC11CHKEN:2;              // 23:22 ADC SOC11 Safety Checker Result Enable
    uint16_t SOC12CHKEN:2;              // 25:24 ADC SOC12 Safety Checker Result Enable
    uint16_t SOC13CHKEN:2;              // 27:26 ADC SOC13 Safety Checker Result Enable
    uint16_t SOC14CHKEN:2;              // 29:28 ADC SOC14 Safety Checker Result Enable
    uint16_t SOC15CHKEN:2;              // 31:30 ADC SOC15 Safety Checker Result Enable
};

union ADC_ADCSAFECHECKRESEN_REG {
    uint32_t  all;
    struct  ADC_ADCSAFECHECKRESEN_BITS  bit;
};

struct ADC_ADCSAFECHECKRESEN2_BITS {    // bits description
    uint16_t SOC16CHKEN:2;              // 1:0 ADC SOC16 Safety Checker Result Enable
    uint16_t SOC17CHKEN:2;              // 3:2 ADC SOC17 Safety Checker Result Enable
    uint16_t SOC18CHKEN:2;              // 5:4 ADC SOC18 Safety Checker Result Enable
    uint16_t SOC19CHKEN:2;              // 7:6 ADC SOC19 Safety Checker Result Enable
    uint16_t SOC20CHKEN:2;              // 9:8 ADC SOC20 Safety Checker Result Enable
    uint16_t SOC21CHKEN:2;              // 11:10 ADC SOC21 Safety Checker Result Enable
    uint16_t SOC22CHKEN:2;              // 13:12 ADC SOC22 Safety Checker Result Enable
    uint16_t SOC23CHKEN:2;              // 15:14 ADC SOC23 Safety Checker Result Enable
    uint16_t SOC24CHKEN:2;              // 17:16 ADC SOC24 Safety Checker Result Enable
    uint16_t SOC25CHKEN:2;              // 19:18 ADC SOC25 Safety Checker Result Enable
    uint16_t SOC26CHKEN:2;              // 21:20 ADC SOC26 Safety Checker Result Enable
    uint16_t SOC27CHKEN:2;              // 23:22 ADC SOC27 Safety Checker Result Enable
    uint16_t SOC28CHKEN:2;              // 25:24 ADC SOC28 Safety Checker Result Enable
    uint16_t SOC29CHKEN:2;              // 27:26 ADC SOC29 Safety Checker Result Enable
    uint16_t SOC30CHKEN:2;              // 29:28 ADC SOC30 Safety Checker Result Enable
    uint16_t SOC31CHKEN:2;              // 31:30 ADC SOC31 Safety Checker Result Enable
};

union ADC_ADCSAFECHECKRESEN2_REG {
    uint32_t  all;
    struct  ADC_ADCSAFECHECKRESEN2_BITS  bit;
};

struct ADC_ADCREV2_BITS {               // bits description
    uint16_t WRAPPERTYPE:8;             // 7:0 ADC Wrapper Type
    uint16_t WRAPPERREV:8;              // 15:8 ADC Wrapper Revision
};

union ADC_ADCREV2_REG {
    uint16_t  all;
    struct  ADC_ADCREV2_BITS  bit;
};

struct ADC_REP1CTL_BITS {               // bits description
    uint16_t MODE:1;                    // 0 ADC Trigger Repeater 1 Mode Select
    uint16_t ACTIVEMODE:1;              // 1 ADC Trigger Repeater 1 Active Mode
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t MODULEBUSY:1;              // 3 ADC Trigger Repeater 1 Module Busy
    uint16_t rsvd2:1;                   // 4 Reserved
    uint16_t rsvd3:1;                   // 5 Reserved
    uint16_t PHASEOVF:1;                // 6 ADC Trigger Repeater 1 Phase Delay Overflow
    uint16_t TRIGGEROVF:1;              // 7 ADC Trigger Repeater 1 Oversampled Trigger Overflow
    uint16_t TRIGGER:7;                 // 14:8 ADC Trigger Repeater 1 Trigger Select
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t SYNCINSEL:6;               // 21:16 ADC Trigger Repeater 1 Sync. In Select
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t SWSYNC:1;                  // 23 ADC Trigger Repeater 1 Software Sync.
    uint16_t rsvd6:8;                   // 31:24 Reserved
};

union ADC_REP1CTL_REG {
    uint32_t  all;
    struct  ADC_REP1CTL_BITS  bit;
};

struct ADC_REP1N_BITS {                 // bits description
    uint16_t NSEL:7;                    // 6:0 ADC Trigger Repeater 1 Trigger Number Selection
    uint16_t rsvd1:9;                   // 15:7 Reserved
    uint16_t NCOUNT:7;                  // 22:16 ADC Trigger Repeater 1 Trigger Counter
    uint16_t rsvd2:9;                   // 31:23 Reserved
};

union ADC_REP1N_REG {
    uint32_t  all;
    struct  ADC_REP1N_BITS  bit;
};

struct ADC_REP1PHASE_BITS {             // bits description
    uint16_t PHASE:16;                  // 15:0 ADC Trigger Repeater 1 Phase Delay Configuration
    uint16_t PHASECOUNT:16;             // 31:16 ADC Trigger Repeater 1 Phase Delay Status
};

union ADC_REP1PHASE_REG {
    uint32_t  all;
    struct  ADC_REP1PHASE_BITS  bit;
};

struct ADC_REP1SPREAD_BITS {            // bits description
    uint16_t SPREAD:16;                 // 15:0 ADC Trigger Repeater 1 Spread Delay Configuration
    uint16_t SPREADCOUNT:16;            // 31:16 ADC Trigger Repeater 1 Spread Delay Status
};

union ADC_REP1SPREAD_REG {
    uint32_t  all;
    struct  ADC_REP1SPREAD_BITS  bit;
};

struct ADC_REP1FRC_BITS {               // bits description
    uint16_t SWFRC:1;                   // 0 ADC Trigger Repeater 1 Software Force
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union ADC_REP1FRC_REG {
    uint16_t  all;
    struct  ADC_REP1FRC_BITS  bit;
};

struct ADC_REP2CTL_BITS {               // bits description
    uint16_t MODE:1;                    // 0 ADC Trigger Repeater 2 Mode Select
    uint16_t ACTIVEMODE:1;              // 1 ADC Trigger Repeater 2 Active Mode
    uint16_t rsvd1:1;                   // 2 Reserved
    uint16_t MODULEBUSY:1;              // 3 ADC Trigger Repeater 2 Module Busy
    uint16_t rsvd2:1;                   // 4 Reserved
    uint16_t rsvd3:1;                   // 5 Reserved
    uint16_t PHASEOVF:1;                // 6 ADC Trigger Repeater 2 Phase Delay Overflow
    uint16_t TRIGGEROVF:1;              // 7 ADC Trigger Repeater 2 Oversampled Trigger Overflow
    uint16_t TRIGGER:7;                 // 14:8 ADC Trigger Repeater 2 Trigger Select
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t SYNCINSEL:6;               // 21:16 ADC Trigger Repeater 2 Sync. In Select
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t SWSYNC:1;                  // 23 ADC Trigger Repeater 2 Software Sync.
    uint16_t rsvd6:8;                   // 31:24 Reserved
};

union ADC_REP2CTL_REG {
    uint32_t  all;
    struct  ADC_REP2CTL_BITS  bit;
};

struct ADC_REP2N_BITS {                 // bits description
    uint16_t NSEL:7;                    // 6:0 ADC Trigger Repeater 2 Trigger Number Selection
    uint16_t rsvd1:9;                   // 15:7 Reserved
    uint16_t NCOUNT:7;                  // 22:16 ADC Trigger Repeater 2 Trigger Counter
    uint16_t rsvd2:9;                   // 31:23 Reserved
};

union ADC_REP2N_REG {
    uint32_t  all;
    struct  ADC_REP2N_BITS  bit;
};

struct ADC_REP2PHASE_BITS {             // bits description
    uint16_t PHASE:16;                  // 15:0 ADC Trigger Repeater 2 Phase Delay Configuration
    uint16_t PHASECOUNT:16;             // 31:16 ADC Trigger Repeater 2 Phase Delay Status
};

union ADC_REP2PHASE_REG {
    uint32_t  all;
    struct  ADC_REP2PHASE_BITS  bit;
};

struct ADC_REP2SPREAD_BITS {            // bits description
    uint16_t SPREAD:16;                 // 15:0 ADC Trigger Repeater 2 Spread Delay Configuration
    uint16_t SPREADCOUNT:16;            // 31:16 ADC Trigger Repeater 2 Spread Delay Status
};

union ADC_REP2SPREAD_REG {
    uint32_t  all;
    struct  ADC_REP2SPREAD_BITS  bit;
};

struct ADC_REP2FRC_BITS {               // bits description
    uint16_t SWFRC:1;                   // 0 ADC Trigger Repeater 2 Software Force
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union ADC_REP2FRC_REG {
    uint16_t  all;
    struct  ADC_REP2FRC_BITS  bit;
};

struct ADC_ADCPPB1LIMIT_BITS {          // bits description
    uint16_t LIMIT:10;                  // 9:0 Post Processing Block 1 Limit
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB1LIMIT_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1LIMIT_BITS  bit;
};

struct ADC_ADCPPBP1PCOUNT_BITS {        // bits description
    uint16_t PCOUNT:10;                 // 9:0 Post Processing Block 1 Partial Count
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPBP1PCOUNT_REG {
    uint16_t  all;
    struct  ADC_ADCPPBP1PCOUNT_BITS  bit;
};

struct ADC_ADCPPB1CONFIG2_BITS {        // bits description
    uint16_t SHIFT:4;                   // 3:0 Post Processing Block 1 Right Shift
    uint16_t SYNCINSEL:6;               // 9:4 Post Processing Block 1 Sync. Input Select
    uint16_t rsvd1:1;                   // 10 Reserved
    uint16_t SWSYNC:1;                  // 11 Post Processing Block 1 Software Force Sync.
    uint16_t OSINTSEL:1;                // 12 Post Processing Block 1 Interrupt Source Select
    uint16_t rsvd2:1;                   // 13 Reserved
    uint16_t COMPSEL:2;                 // 15:14 Post Processing Block 1 Compare Source Select
};

union ADC_ADCPPB1CONFIG2_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1CONFIG2_BITS  bit;
};

struct ADC_ADCPPB1PSUM_BITS {           // bits description
    uint32_t PSUM:24;                   // 23:0 Post Processing Block 1 Oversampling Partial Sum
    uint16_t SIGN:8;                    // 31:24 Sign Extended Bits
};

union ADC_ADCPPB1PSUM_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1PSUM_BITS  bit;
};

struct ADC_ADCPPB1PMAX_BITS {           // bits description
    uint32_t PMAX:17;                   // 16:0 Post Processing Block 1 Oversampling Partial Max
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB1PMAX_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1PMAX_BITS  bit;
};

struct ADC_ADCPPB1PMAXI_BITS {          // bits description
    uint16_t PMAXI:10;                  // 9:0 Post Processing Block 1 Oversampling Partial Index of Max
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB1PMAXI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1PMAXI_BITS  bit;
};

struct ADC_ADCPPB1PMIN_BITS {           // bits description
    uint32_t PMIN:17;                   // 16:0 Post Processing Block 1 Oversampling Partial Min
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB1PMIN_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1PMIN_BITS  bit;
};

struct ADC_ADCPPB1PMINI_BITS {          // bits description
    uint16_t PMINI:10;                  // 9:0 Post Processing Block 1 Oversampling Partial Index of Min
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB1PMINI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1PMINI_BITS  bit;
};

struct ADC_ADCPPB1TRIPLO2_BITS {        // bits description
    uint32_t LIMITLO:24;                // 23:0 ADC Post Processing Block 1 Trip Low Limit
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_ADCPPB1TRIPLO2_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1TRIPLO2_BITS  bit;
};

struct ADC_ADCPPB2LIMIT_BITS {          // bits description
    uint16_t LIMIT:10;                  // 9:0 Post Processing Block 2 Limit
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB2LIMIT_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2LIMIT_BITS  bit;
};

struct ADC_ADCPPBP2PCOUNT_BITS {        // bits description
    uint16_t PCOUNT:10;                 // 9:0 Post Processing Block 2 Partial Count
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPBP2PCOUNT_REG {
    uint16_t  all;
    struct  ADC_ADCPPBP2PCOUNT_BITS  bit;
};

struct ADC_ADCPPB2CONFIG2_BITS {        // bits description
    uint16_t SHIFT:4;                   // 3:0 Post Processing Block 2 Right Shift
    uint16_t SYNCINSEL:6;               // 9:4 Post Processing Block 2 Sync. Input Select
    uint16_t rsvd1:1;                   // 10 Reserved
    uint16_t SWSYNC:1;                  // 11 Post Processing Block 2 Software Force Sync.
    uint16_t OSINTSEL:1;                // 12 Post Processing Block 2 Interrupt Source Select
    uint16_t rsvd2:1;                   // 13 Reserved
    uint16_t COMPSEL:2;                 // 15:14 Post Processing Block 2 Compare Source Select
};

union ADC_ADCPPB2CONFIG2_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2CONFIG2_BITS  bit;
};

struct ADC_ADCPPB2PSUM_BITS {           // bits description
    uint32_t PSUM:24;                   // 23:0 Post Processing Block 2 Oversampling Partial Sum
    uint16_t SIGN:8;                    // 31:24 Sign Extended Bits
};

union ADC_ADCPPB2PSUM_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2PSUM_BITS  bit;
};

struct ADC_ADCPPB2PMAX_BITS {           // bits description
    uint32_t PMAX:17;                   // 16:0 Post Processing Block 2 Oversampling Partial Max
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB2PMAX_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2PMAX_BITS  bit;
};

struct ADC_ADCPPB2PMAXI_BITS {          // bits description
    uint16_t PMAXI:10;                  // 9:0 Post Processing Block 2 Oversampling Partial Index of Max
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB2PMAXI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2PMAXI_BITS  bit;
};

struct ADC_ADCPPB2PMIN_BITS {           // bits description
    uint32_t PMIN:17;                   // 16:0 Post Processing Block 2 Oversampling Partial Min
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB2PMIN_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2PMIN_BITS  bit;
};

struct ADC_ADCPPB2PMINI_BITS {          // bits description
    uint16_t PMINI:10;                  // 9:0 Post Processing Block 2 Oversampling Partial Index of Min
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB2PMINI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2PMINI_BITS  bit;
};

struct ADC_ADCPPB2TRIPLO2_BITS {        // bits description
    uint32_t LIMITLO:24;                // 23:0 ADC Post Processing Block 2 Trip Low Limit
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_ADCPPB2TRIPLO2_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2TRIPLO2_BITS  bit;
};

struct ADC_ADCPPB3LIMIT_BITS {          // bits description
    uint16_t LIMIT:10;                  // 9:0 Post Processing Block 3 Limit
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB3LIMIT_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3LIMIT_BITS  bit;
};

struct ADC_ADCPPBP3PCOUNT_BITS {        // bits description
    uint16_t PCOUNT:10;                 // 9:0 Post Processing Block 3 Partial Count
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPBP3PCOUNT_REG {
    uint16_t  all;
    struct  ADC_ADCPPBP3PCOUNT_BITS  bit;
};

struct ADC_ADCPPB3CONFIG2_BITS {        // bits description
    uint16_t SHIFT:4;                   // 3:0 Post Processing Block 3 Right Shift
    uint16_t SYNCINSEL:6;               // 9:4 Post Processing Block 3 Sync. Input Select
    uint16_t rsvd1:1;                   // 10 Reserved
    uint16_t SWSYNC:1;                  // 11 Post Processing Block 3 Software Force Sync.
    uint16_t OSINTSEL:1;                // 12 Post Processing Block 3 Interrupt Source Select
    uint16_t rsvd2:1;                   // 13 Reserved
    uint16_t COMPSEL:2;                 // 15:14 Post Processing Block 3 Compare Source Select
};

union ADC_ADCPPB3CONFIG2_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3CONFIG2_BITS  bit;
};

struct ADC_ADCPPB3PSUM_BITS {           // bits description
    uint32_t PSUM:24;                   // 23:0 Post Processing Block 3 Oversampling Partial Sum
    uint16_t SIGN:8;                    // 31:24 Sign Extended Bits
};

union ADC_ADCPPB3PSUM_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3PSUM_BITS  bit;
};

struct ADC_ADCPPB3PMAX_BITS {           // bits description
    uint32_t PMAX:17;                   // 16:0 Post Processing Block 3 Oversampling Partial Max
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB3PMAX_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3PMAX_BITS  bit;
};

struct ADC_ADCPPB3PMAXI_BITS {          // bits description
    uint16_t PMAXI:10;                  // 9:0 Post Processing Block 3 Oversampling Partial Index of Max
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB3PMAXI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3PMAXI_BITS  bit;
};

struct ADC_ADCPPB3PMIN_BITS {           // bits description
    uint32_t PMIN:17;                   // 16:0 Post Processing Block 3 Oversampling Partial Min
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB3PMIN_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3PMIN_BITS  bit;
};

struct ADC_ADCPPB3PMINI_BITS {          // bits description
    uint16_t PMINI:10;                  // 9:0 Post Processing Block 3 Oversampling Partial Index of Min
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB3PMINI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3PMINI_BITS  bit;
};

struct ADC_ADCPPB3TRIPLO2_BITS {        // bits description
    uint32_t LIMITLO:24;                // 23:0 ADC Post Processing Block 3 Trip Low Limit
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_ADCPPB3TRIPLO2_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3TRIPLO2_BITS  bit;
};

struct ADC_ADCPPB4LIMIT_BITS {          // bits description
    uint16_t LIMIT:10;                  // 9:0 Post Processing Block 4 Limit
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB4LIMIT_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4LIMIT_BITS  bit;
};

struct ADC_ADCPPBP4PCOUNT_BITS {        // bits description
    uint16_t PCOUNT:10;                 // 9:0 Post Processing Block 4 Partial Count
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPBP4PCOUNT_REG {
    uint16_t  all;
    struct  ADC_ADCPPBP4PCOUNT_BITS  bit;
};

struct ADC_ADCPPB4CONFIG2_BITS {        // bits description
    uint16_t SHIFT:4;                   // 3:0 Post Processing Block 4 Right Shift
    uint16_t SYNCINSEL:6;               // 9:4 Post Processing Block 4 Sync. Input Select
    uint16_t rsvd1:1;                   // 10 Reserved
    uint16_t SWSYNC:1;                  // 11 Post Processing Block 4 Software Force Sync.
    uint16_t OSINTSEL:1;                // 12 Post Processing Block 4 Interrupt Source Select
    uint16_t rsvd2:1;                   // 13 Reserved
    uint16_t COMPSEL:2;                 // 15:14 Post Processing Block 4 Compare Source Select
};

union ADC_ADCPPB4CONFIG2_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4CONFIG2_BITS  bit;
};

struct ADC_ADCPPB4PSUM_BITS {           // bits description
    uint32_t PSUM:24;                   // 23:0 Post Processing Block 4 Oversampling Partial Sum
    uint16_t SIGN:8;                    // 31:24 Sign Extended Bits
};

union ADC_ADCPPB4PSUM_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4PSUM_BITS  bit;
};

struct ADC_ADCPPB4PMAX_BITS {           // bits description
    uint32_t PMAX:17;                   // 16:0 Post Processing Block 4 Oversampling Partial Max
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB4PMAX_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4PMAX_BITS  bit;
};

struct ADC_ADCPPB4PMAXI_BITS {          // bits description
    uint16_t PMAXI:10;                  // 9:0 Post Processing Block 4 Oversampling Partial Index of Max
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB4PMAXI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4PMAXI_BITS  bit;
};

struct ADC_ADCPPB4PMIN_BITS {           // bits description
    uint32_t PMIN:17;                   // 16:0 Post Processing Block 4 Oversampling Partial Min
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB4PMIN_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4PMIN_BITS  bit;
};

struct ADC_ADCPPB4PMINI_BITS {          // bits description
    uint16_t PMINI:10;                  // 9:0 Post Processing Block 4 Oversampling Partial Index of Min
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB4PMINI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4PMINI_BITS  bit;
};

struct ADC_ADCPPB4TRIPLO2_BITS {        // bits description
    uint32_t LIMITLO:24;                // 23:0 ADC Post Processing Block 4 Trip Low Limit
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_ADCPPB4TRIPLO2_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4TRIPLO2_BITS  bit;
};

struct ADC_REGS {
    union   ADC_ADCCTL1_REG                  ADCCTL1;                      // ADC Control 1 Register
    union   ADC_ADCCTL2_REG                  ADCCTL2;                      // ADC Control 2 Register
    uint8_t                                  rsvd1[8];                     // Reserved
    union   ADC_ADCBURSTCTL_REG              ADCBURSTCTL;                  // ADC Burst Control Register
    union   ADC_ADCINTFLG_REG                ADCINTFLG;                    // ADC Interrupt Flag Register
    union   ADC_ADCINTFLGCLR_REG             ADCINTFLGCLR;                 // ADC Interrupt Flag Clear Register
    union   ADC_ADCINTOVF_REG                ADCINTOVF;                    // ADC Interrupt Overflow Register
    union   ADC_ADCINTOVFCLR_REG             ADCINTOVFCLR;                 // ADC Interrupt Overflow Clear Register
    union   ADC_ADCINTSEL1N2_REG             ADCINTSEL1N2;                 // ADC Interrupt 1 and 2 Selection Register
    union   ADC_ADCINTSEL3N4_REG             ADCINTSEL3N4;                 // ADC Interrupt 3 and 4 Selection Register
    union   ADC_ADCSOCPRICTL_REG             ADCSOCPRICTL;                 // ADC SOC Priority Control Register
    union   ADC_ADCINTSOCSEL1_REG            ADCINTSOCSEL1;                // ADC Interrupt SOC Selection 1 Register
    union   ADC_ADCINTSOCSEL2_REG            ADCINTSOCSEL2;                // ADC Interrupt SOC Selection 2 Register
    union   ADC_ADCSOCFLG1_REG               ADCSOCFLG1;                   // ADC SOC Flag 1 Register
    union   ADC_ADCSOCFRC1_REG               ADCSOCFRC1;                   // ADC SOC Force 1 Register
    union   ADC_ADCSOCOVF1_REG               ADCSOCOVF1;                   // ADC SOC Overflow 1 Register
    union   ADC_ADCSOCOVFCLR1_REG            ADCSOCOVFCLR1;                // ADC SOC Overflow Clear 1 Register
    union   ADC_ADCSOC0CTL_REG               ADCSOC0CTL;                   // ADC SOC0 Control Register
    union   ADC_ADCSOC1CTL_REG               ADCSOC1CTL;                   // ADC SOC1 Control Register
    union   ADC_ADCSOC2CTL_REG               ADCSOC2CTL;                   // ADC SOC2 Control Register
    union   ADC_ADCSOC3CTL_REG               ADCSOC3CTL;                   // ADC SOC3 Control Register
    union   ADC_ADCSOC4CTL_REG               ADCSOC4CTL;                   // ADC SOC4 Control Register
    union   ADC_ADCSOC5CTL_REG               ADCSOC5CTL;                   // ADC SOC5 Control Register
    union   ADC_ADCSOC6CTL_REG               ADCSOC6CTL;                   // ADC SOC6 Control Register
    union   ADC_ADCSOC7CTL_REG               ADCSOC7CTL;                   // ADC SOC7 Control Register
    union   ADC_ADCSOC8CTL_REG               ADCSOC8CTL;                   // ADC SOC8 Control Register
    union   ADC_ADCSOC9CTL_REG               ADCSOC9CTL;                   // ADC SOC9 Control Register
    union   ADC_ADCSOC10CTL_REG              ADCSOC10CTL;                  // ADC SOC10 Control Register
    union   ADC_ADCSOC11CTL_REG              ADCSOC11CTL;                  // ADC SOC11 Control Register
    union   ADC_ADCSOC12CTL_REG              ADCSOC12CTL;                  // ADC SOC12 Control Register
    union   ADC_ADCSOC13CTL_REG              ADCSOC13CTL;                  // ADC SOC13 Control Register
    union   ADC_ADCSOC14CTL_REG              ADCSOC14CTL;                  // ADC SOC14 Control Register
    union   ADC_ADCSOC15CTL_REG              ADCSOC15CTL;                  // ADC SOC15 Control Register
    union   ADC_ADCSOC16CTL_REG              ADCSOC16CTL;                  // ADC SOC16 Control Register
    union   ADC_ADCSOC17CTL_REG              ADCSOC17CTL;                  // ADC SOC17 Control Register
    union   ADC_ADCSOC18CTL_REG              ADCSOC18CTL;                  // ADC SOC18 Control Register
    union   ADC_ADCSOC19CTL_REG              ADCSOC19CTL;                  // ADC SOC19 Control Register
    union   ADC_ADCSOC20CTL_REG              ADCSOC20CTL;                  // ADC SOC20 Control Register
    union   ADC_ADCSOC21CTL_REG              ADCSOC21CTL;                  // ADC SOC21 Control Register
    union   ADC_ADCSOC22CTL_REG              ADCSOC22CTL;                  // ADC SOC22 Control Register
    union   ADC_ADCSOC23CTL_REG              ADCSOC23CTL;                  // ADC SOC23 Control Register
    union   ADC_ADCSOC24CTL_REG              ADCSOC24CTL;                  // ADC SOC24 Control Register
    union   ADC_ADCSOC25CTL_REG              ADCSOC25CTL;                  // ADC SOC25 Control Register
    union   ADC_ADCSOC26CTL_REG              ADCSOC26CTL;                  // ADC SOC26 Control Register
    union   ADC_ADCSOC27CTL_REG              ADCSOC27CTL;                  // ADC SOC27 Control Register
    union   ADC_ADCSOC28CTL_REG              ADCSOC28CTL;                  // ADC SOC28 Control Register
    union   ADC_ADCSOC29CTL_REG              ADCSOC29CTL;                  // ADC SOC29 Control Register
    union   ADC_ADCSOC30CTL_REG              ADCSOC30CTL;                  // ADC SOC30 Control Register
    union   ADC_ADCSOC31CTL_REG              ADCSOC31CTL;                  // ADC SOC31 Control Register
    union   ADC_ADCEVTSTAT_REG               ADCEVTSTAT;                   // ADC Event Status Register
    uint8_t                                  rsvd2[2];                     // Reserved
    union   ADC_ADCEVTCLR_REG                ADCEVTCLR;                    // ADC Event Clear Register
    uint8_t                                  rsvd3[2];                     // Reserved
    union   ADC_ADCEVTSEL_REG                ADCEVTSEL;                    // ADC Event Selection Register
    uint8_t                                  rsvd4[2];                     // Reserved
    union   ADC_ADCEVTINTSEL_REG             ADCEVTINTSEL;                 // ADC Event Interrupt Selection Register
    uint8_t                                  rsvd5[2];                     // Reserved
    union   ADC_ADCOSDETECT_REG              ADCOSDETECT;                  // ADC Open and Shorts Detect Register
    union   ADC_ADCCOUNTER_REG               ADCCOUNTER;                   // ADC Counter Register
    union   ADC_ADCREV_REG                   ADCREV;                       // ADC Revision Register
    union   ADC_ADCOFFTRIM_REG               ADCOFFTRIM;                   // ADC Offset Trim Register 1
    union   ADC_ADCOFFTRIM2_REG              ADCOFFTRIM2;                  // ADC Offset Trim Register 2
    union   ADC_ADCOFFTRIM3_REG              ADCOFFTRIM3;                  // ADC Offset Trim Register 3
    uint8_t                                  rsvd6[4];                     // Reserved
    union   ADC_ADCPPB1CONFIG_REG            ADCPPB1CONFIG;                // ADC PPB{#} Config Register
    union   ADC_ADCPPB1STAMP_REG             ADCPPB1STAMP;                 // ADC PPB1 Sample Delay Time Stamp Register
    union   ADC_ADCPPB1OFFCAL_REG            ADCPPB1OFFCAL;                // ADC PPB1 Offset Calibration Register
    uint16_t                                 ADCPPB1OFFREF;                // ADC PPB1 Offset Reference Register
    union   ADC_ADCPPB1TRIPHI_REG            ADCPPB1TRIPHI;                // ADC PPB1 Trip High Register
    union   ADC_ADCPPB1TRIPLO_REG            ADCPPB1TRIPLO;                // ADC PPB1 Trip Low/Trigger Time Stamp Register
    union   ADC_ADCPPBTRIP1FILCTL_REG        ADCPPBTRIP1FILCTL;            // ADCEVT1 Trip High Filter Control Register
    uint8_t                                  rsvd7[2];                     // Reserved
    union   ADC_ADCPPBTRIP1FILCLKCTL_REG     ADCPPBTRIP1FILCLKCTL;         // ADCEVT1 Trip High Filter Prescale Control Register
    uint8_t                                  rsvd8[8];                     // Reserved
    union   ADC_ADCPPB2CONFIG_REG            ADCPPB2CONFIG;                // ADC PPB{#} Config Register
    union   ADC_ADCPPB2STAMP_REG             ADCPPB2STAMP;                 // ADC PPB2 Sample Delay Time Stamp Register
    union   ADC_ADCPPB2OFFCAL_REG            ADCPPB2OFFCAL;                // ADC PPB2 Offset Calibration Register
    uint16_t                                 ADCPPB2OFFREF;                // ADC PPB2 Offset Reference Register
    union   ADC_ADCPPB2TRIPHI_REG            ADCPPB2TRIPHI;                // ADC PPB2 Trip High Register
    union   ADC_ADCPPB2TRIPLO_REG            ADCPPB2TRIPLO;                // ADC PPB2 Trip Low/Trigger Time Stamp Register
    union   ADC_ADCPPBTRIP2FILCTL_REG        ADCPPBTRIP2FILCTL;            // ADCEVT2 Trip High Filter Control Register
    uint8_t                                  rsvd9[2];                     // Reserved
    union   ADC_ADCPPBTRIP2FILCLKCTL_REG     ADCPPBTRIP2FILCLKCTL;         // ADCEVT2 Trip High Filter Prescale Control Register
    uint8_t                                  rsvd10[8];                    // Reserved
    union   ADC_ADCPPB3CONFIG_REG            ADCPPB3CONFIG;                // ADC PPB{#} Config Register
    union   ADC_ADCPPB3STAMP_REG             ADCPPB3STAMP;                 // ADC PPB3 Sample Delay Time Stamp Register
    union   ADC_ADCPPB3OFFCAL_REG            ADCPPB3OFFCAL;                // ADC PPB3 Offset Calibration Register
    uint16_t                                 ADCPPB3OFFREF;                // ADC PPB3 Offset Reference Register
    union   ADC_ADCPPB3TRIPHI_REG            ADCPPB3TRIPHI;                // ADC PPB3 Trip High Register
    union   ADC_ADCPPB3TRIPLO_REG            ADCPPB3TRIPLO;                // ADC PPB3 Trip Low/Trigger Time Stamp Register
    union   ADC_ADCPPBTRIP3FILCTL_REG        ADCPPBTRIP3FILCTL;            // ADCEVT3 Trip High Filter Control Register
    uint8_t                                  rsvd11[2];                    // Reserved
    union   ADC_ADCPPBTRIP3FILCLKCTL_REG     ADCPPBTRIP3FILCLKCTL;         // ADCEVT3 Trip High Filter Prescale Control Register
    uint8_t                                  rsvd12[8];                    // Reserved
    union   ADC_ADCPPB4CONFIG_REG            ADCPPB4CONFIG;                // ADC PPB{#} Config Register
    union   ADC_ADCPPB4STAMP_REG             ADCPPB4STAMP;                 // ADC PPB4 Sample Delay Time Stamp Register
    union   ADC_ADCPPB4OFFCAL_REG            ADCPPB4OFFCAL;                // ADC PPB4 Offset Calibration Register
    uint16_t                                 ADCPPB4OFFREF;                // ADC PPB4 Offset Reference Register
    union   ADC_ADCPPB4TRIPHI_REG            ADCPPB4TRIPHI;                // ADC PPB4 Trip High Register
    union   ADC_ADCPPB4TRIPLO_REG            ADCPPB4TRIPLO;                // ADC PPB4 Trip Low/Trigger Time Stamp Register
    union   ADC_ADCPPBTRIP4FILCTL_REG        ADCPPBTRIP4FILCTL;            // ADCEVT4 Trip High Filter Control Register
    uint8_t                                  rsvd13[2];                    // Reserved
    union   ADC_ADCPPBTRIP4FILCLKCTL_REG     ADCPPBTRIP4FILCLKCTL;         // ADCEVT4 Trip High Filter Prescale Control Register
    uint8_t                                  rsvd14[8];                    // Reserved
    union   ADC_ADCSAFECHECKRESEN_REG        ADCSAFECHECKRESEN;            // ADC Safe Check Result Enable Register
    union   ADC_ADCSAFECHECKRESEN2_REG       ADCSAFECHECKRESEN2;           // ADC Safe Check Result Enable 2 Register
    uint8_t                                  rsvd15[22];                   // Reserved
    uint16_t                                 ADCINTCYCLE;                  // ADC Early Interrupt Generation Cycle
    uint32_t                                 ADCINLTRIM1;                  // ADC Linearity Trim 1 Register
    uint32_t                                 ADCINLTRIM2;                  // ADC Linearity Trim 2 Register
    uint32_t                                 ADCINLTRIM3;                  // ADC Linearity Trim 3 Register
    uint32_t                                 ADCINLTRIM4;                  // ADC Linearity Trim 4 Register
    uint32_t                                 ADCINLTRIM5;                  // ADC Linearity Trim 5 Register
    uint32_t                                 ADCINLTRIM6;                  // ADC Linearity Trim 6 Register
    uint8_t                                  rsvd16[2];                    // Reserved
    union   ADC_ADCREV2_REG                  ADCREV2;                      // ADC Wrapper Revision Register
    uint8_t                                  rsvd17[4];                    // Reserved
    union   ADC_REP1CTL_REG                  REP1CTL;                      // ADC Trigger Repeater 1 Control Register
    union   ADC_REP1N_REG                    REP1N;                        // ADC Trigger Repeater 1 N Select Register
    union   ADC_REP1PHASE_REG                REP1PHASE;                    // ADC Trigger Repeater 1 Phase Select Register
    union   ADC_REP1SPREAD_REG               REP1SPREAD;                   // ADC Trigger Repeater 1 Spread Select Register
    union   ADC_REP1FRC_REG                  REP1FRC;                      // ADC Trigger Repeater 1 Software Force Register
    uint8_t                                  rsvd18[14];                   // Reserved
    union   ADC_REP2CTL_REG                  REP2CTL;                      // ADC Trigger Repeater 2 Control Register
    union   ADC_REP2N_REG                    REP2N;                        // ADC Trigger Repeater 2 N Select Register
    union   ADC_REP2PHASE_REG                REP2PHASE;                    // ADC Trigger Repeater 2 Phase Select Register
    union   ADC_REP2SPREAD_REG               REP2SPREAD;                   // ADC Trigger Repeater 2 Spread Select Register
    union   ADC_REP2FRC_REG                  REP2FRC;                      // ADC Trigger Repeater 2 Software Force Register
    uint8_t                                  rsvd19[14];                   // Reserved
    union   ADC_ADCPPB1LIMIT_REG             ADCPPB1LIMIT;                 // ADC PPB1Conversion Count Limit Register
    uint8_t                                  rsvd20[2];                    // Reserved
    union   ADC_ADCPPBP1PCOUNT_REG           ADCPPBP1PCOUNT;               // ADC PPB1 Partial Conversion Count Register
    uint8_t                                  rsvd21[2];                    // Reserved
    union   ADC_ADCPPB1CONFIG2_REG           ADCPPB1CONFIG2;               // ADC PPB1 Sum Shift Register
    uint8_t                                  rsvd22[2];                    // Reserved
    union   ADC_ADCPPB1PSUM_REG              ADCPPB1PSUM;                  // ADC PPB1 Partial Sum Register
    union   ADC_ADCPPB1PMAX_REG              ADCPPB1PMAX;                  // ADC PPB1 Partial Max Register
    union   ADC_ADCPPB1PMAXI_REG             ADCPPB1PMAXI;                 // ADC PPB1 Partial Max Index Register
    uint8_t                                  rsvd23[2];                    // Reserved
    union   ADC_ADCPPB1PMIN_REG              ADCPPB1PMIN;                  // ADC PPB1 Partial MIN Register
    union   ADC_ADCPPB1PMINI_REG             ADCPPB1PMINI;                 // ADC PPB1 Partial Min Index Register
    uint8_t                                  rsvd24[2];                    // Reserved
    union   ADC_ADCPPB1TRIPLO2_REG           ADCPPB1TRIPLO2;               // ADC PPB1 Extended Trip Low Register
    uint8_t                                  rsvd25[16];                   // Reserved
    union   ADC_ADCPPB2LIMIT_REG             ADCPPB2LIMIT;                 // ADC PPB2Conversion Count Limit Register
    uint8_t                                  rsvd26[2];                    // Reserved
    union   ADC_ADCPPBP2PCOUNT_REG           ADCPPBP2PCOUNT;               // ADC PPB2 Partial Conversion Count Register
    uint8_t                                  rsvd27[2];                    // Reserved
    union   ADC_ADCPPB2CONFIG2_REG           ADCPPB2CONFIG2;               // ADC PPB2 Sum Shift Register
    uint8_t                                  rsvd28[2];                    // Reserved
    union   ADC_ADCPPB2PSUM_REG              ADCPPB2PSUM;                  // ADC PPB2 Partial Sum Register
    union   ADC_ADCPPB2PMAX_REG              ADCPPB2PMAX;                  // ADC PPB2 Partial Max Register
    union   ADC_ADCPPB2PMAXI_REG             ADCPPB2PMAXI;                 // ADC PPB2 Partial Max Index Register
    uint8_t                                  rsvd29[2];                    // Reserved
    union   ADC_ADCPPB2PMIN_REG              ADCPPB2PMIN;                  // ADC PPB2 Partial MIN Register
    union   ADC_ADCPPB2PMINI_REG             ADCPPB2PMINI;                 // ADC PPB2 Partial Min Index Register
    uint8_t                                  rsvd30[2];                    // Reserved
    union   ADC_ADCPPB2TRIPLO2_REG           ADCPPB2TRIPLO2;               // ADC PPB2 Extended Trip Low Register
    uint8_t                                  rsvd31[16];                   // Reserved
    union   ADC_ADCPPB3LIMIT_REG             ADCPPB3LIMIT;                 // ADC PPB3Conversion Count Limit Register
    uint8_t                                  rsvd32[2];                    // Reserved
    union   ADC_ADCPPBP3PCOUNT_REG           ADCPPBP3PCOUNT;               // ADC PPB3 Partial Conversion Count Register
    uint8_t                                  rsvd33[2];                    // Reserved
    union   ADC_ADCPPB3CONFIG2_REG           ADCPPB3CONFIG2;               // ADC PPB3 Sum Shift Register
    uint8_t                                  rsvd34[2];                    // Reserved
    union   ADC_ADCPPB3PSUM_REG              ADCPPB3PSUM;                  // ADC PPB3 Partial Sum Register
    union   ADC_ADCPPB3PMAX_REG              ADCPPB3PMAX;                  // ADC PPB3 Partial Max Register
    union   ADC_ADCPPB3PMAXI_REG             ADCPPB3PMAXI;                 // ADC PPB3 Partial Max Index Register
    uint8_t                                  rsvd35[2];                    // Reserved
    union   ADC_ADCPPB3PMIN_REG              ADCPPB3PMIN;                  // ADC PPB3 Partial MIN Register
    union   ADC_ADCPPB3PMINI_REG             ADCPPB3PMINI;                 // ADC PPB3 Partial Min Index Register
    uint8_t                                  rsvd36[2];                    // Reserved
    union   ADC_ADCPPB3TRIPLO2_REG           ADCPPB3TRIPLO2;               // ADC PPB3 Extended Trip Low Register
    uint8_t                                  rsvd37[16];                   // Reserved
    union   ADC_ADCPPB4LIMIT_REG             ADCPPB4LIMIT;                 // ADC PPB4Conversion Count Limit Register
    uint8_t                                  rsvd38[2];                    // Reserved
    union   ADC_ADCPPBP4PCOUNT_REG           ADCPPBP4PCOUNT;               // ADC PPB4 Partial Conversion Count Register
    uint8_t                                  rsvd39[2];                    // Reserved
    union   ADC_ADCPPB4CONFIG2_REG           ADCPPB4CONFIG2;               // ADC PPB4 Sum Shift Register
    uint8_t                                  rsvd40[2];                    // Reserved
    union   ADC_ADCPPB4PSUM_REG              ADCPPB4PSUM;                  // ADC PPB4 Partial Sum Register
    union   ADC_ADCPPB4PMAX_REG              ADCPPB4PMAX;                  // ADC PPB4 Partial Max Register
    union   ADC_ADCPPB4PMAXI_REG             ADCPPB4PMAXI;                 // ADC PPB4 Partial Max Index Register
    uint8_t                                  rsvd41[2];                    // Reserved
    union   ADC_ADCPPB4PMIN_REG              ADCPPB4PMIN;                  // ADC PPB4 Partial MIN Register
    union   ADC_ADCPPB4PMINI_REG             ADCPPB4PMINI;                 // ADC PPB4 Partial Min Index Register
    uint8_t                                  rsvd42[2];                    // Reserved
    union   ADC_ADCPPB4TRIPLO2_REG           ADCPPB4TRIPLO2;               // ADC PPB4 Extended Trip Low Register
};

struct ADC_ADCPPB1RESULT_BITS {         // bits description
    uint16_t PPBRESULT:16;              // 15:0 ADC Post Processing Block Result
    uint16_t SIGN:16;                   // 31:16 Sign Extended Bits
};

union ADC_ADCPPB1RESULT_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1RESULT_BITS  bit;
};

struct ADC_ADCPPB2RESULT_BITS {         // bits description
    uint16_t PPBRESULT:16;              // 15:0 ADC Post Processing Block Result
    uint16_t SIGN:16;                   // 31:16 Sign Extended Bits
};

union ADC_ADCPPB2RESULT_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2RESULT_BITS  bit;
};

struct ADC_ADCPPB3RESULT_BITS {         // bits description
    uint16_t PPBRESULT:16;              // 15:0 ADC Post Processing Block Result
    uint16_t SIGN:16;                   // 31:16 Sign Extended Bits
};

union ADC_ADCPPB3RESULT_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3RESULT_BITS  bit;
};

struct ADC_ADCPPB4RESULT_BITS {         // bits description
    uint16_t PPBRESULT:16;              // 15:0 ADC Post Processing Block Result
    uint16_t SIGN:16;                   // 31:16 Sign Extended Bits
};

union ADC_ADCPPB4RESULT_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4RESULT_BITS  bit;
};

struct ADC_ADCPPB1SUM_BITS {            // bits description
    uint32_t SUM:24;                    // 23:0 Post Processing Block 1 Oversampling Sum
    uint16_t SIGN:8;                    // 31:24 Sign Extended Bits
};

union ADC_ADCPPB1SUM_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1SUM_BITS  bit;
};

struct ADC_ADCPPB1COUNT_BITS {          // bits description
    uint16_t COUNT:10;                  // 9:0 Post Processing Block 1 Final Count
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB1COUNT_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1COUNT_BITS  bit;
};

struct ADC_ADCPPB2SUM_BITS {            // bits description
    uint32_t SUM:24;                    // 23:0 Post Processing Block 2 Oversampling Sum
    uint16_t SIGN:8;                    // 31:24 Sign Extended Bits
};

union ADC_ADCPPB2SUM_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2SUM_BITS  bit;
};

struct ADC_ADCPPB2COUNT_BITS {          // bits description
    uint16_t COUNT:10;                  // 9:0 Post Processing Block 2 Final Count
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB2COUNT_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2COUNT_BITS  bit;
};

struct ADC_ADCPPB3SUM_BITS {            // bits description
    uint32_t SUM:24;                    // 23:0 Post Processing Block 3 Oversampling Sum
    uint16_t SIGN:8;                    // 31:24 Sign Extended Bits
};

union ADC_ADCPPB3SUM_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3SUM_BITS  bit;
};

struct ADC_ADCPPB3COUNT_BITS {          // bits description
    uint16_t COUNT:10;                  // 9:0 Post Processing Block 3 Final Count
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB3COUNT_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3COUNT_BITS  bit;
};

struct ADC_ADCPPB4SUM_BITS {            // bits description
    uint32_t SUM:24;                    // 23:0 Post Processing Block 4 Oversampling Sum
    uint16_t SIGN:8;                    // 31:24 Sign Extended Bits
};

union ADC_ADCPPB4SUM_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4SUM_BITS  bit;
};

struct ADC_ADCPPB4COUNT_BITS {          // bits description
    uint16_t COUNT:10;                  // 9:0 Post Processing Block 4 Final Count
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB4COUNT_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4COUNT_BITS  bit;
};

struct ADC_ADCPPB1MAX_BITS {            // bits description
    uint32_t MAX:17;                    // 16:0 Post Processing Block 1 Oversampling Max
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB1MAX_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1MAX_BITS  bit;
};

struct ADC_ADCPPB1MAXI_BITS {           // bits description
    uint16_t MAXI:10;                   // 9:0 Post Processing Block 1 Oversampling Index of Max
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB1MAXI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1MAXI_BITS  bit;
};

struct ADC_ADCPPB1MIN_BITS {            // bits description
    uint32_t MIN:17;                    // 16:0 Post Processing Block 1 Oversampling Min
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB1MIN_REG {
    uint32_t  all;
    struct  ADC_ADCPPB1MIN_BITS  bit;
};

struct ADC_ADCPPB1MINI_BITS {           // bits description
    uint16_t MINI:10;                   // 9:0 Post Processing Block 1 Oversampling Index of Min
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB1MINI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB1MINI_BITS  bit;
};

struct ADC_ADCPPB2MAX_BITS {            // bits description
    uint32_t MAX:17;                    // 16:0 Post Processing Block 2 Oversampling Max
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB2MAX_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2MAX_BITS  bit;
};

struct ADC_ADCPPB2MAXI_BITS {           // bits description
    uint16_t MAXI:10;                   // 9:0 Post Processing Block 2 Oversampling Index of Max
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB2MAXI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2MAXI_BITS  bit;
};

struct ADC_ADCPPB2MIN_BITS {            // bits description
    uint32_t MIN:17;                    // 16:0 Post Processing Block 2 Oversampling Min
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB2MIN_REG {
    uint32_t  all;
    struct  ADC_ADCPPB2MIN_BITS  bit;
};

struct ADC_ADCPPB2MINI_BITS {           // bits description
    uint16_t MINI:10;                   // 9:0 Post Processing Block 2 Oversampling Index of Min
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB2MINI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB2MINI_BITS  bit;
};

struct ADC_ADCPPB3MAX_BITS {            // bits description
    uint32_t MAX:17;                    // 16:0 Post Processing Block 3 Oversampling Max
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB3MAX_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3MAX_BITS  bit;
};

struct ADC_ADCPPB3MAXI_BITS {           // bits description
    uint16_t MAXI:10;                   // 9:0 Post Processing Block 3 Oversampling Index of Max
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB3MAXI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3MAXI_BITS  bit;
};

struct ADC_ADCPPB3MIN_BITS {            // bits description
    uint32_t MIN:17;                    // 16:0 Post Processing Block 3 Oversampling Min
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB3MIN_REG {
    uint32_t  all;
    struct  ADC_ADCPPB3MIN_BITS  bit;
};

struct ADC_ADCPPB3MINI_BITS {           // bits description
    uint16_t MINI:10;                   // 9:0 Post Processing Block 3 Oversampling Index of Min
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB3MINI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB3MINI_BITS  bit;
};

struct ADC_ADCPPB4MAX_BITS {            // bits description
    uint32_t MAX:17;                    // 16:0 Post Processing Block 4 Oversampling Max
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB4MAX_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4MAX_BITS  bit;
};

struct ADC_ADCPPB4MAXI_BITS {           // bits description
    uint16_t MAXI:10;                   // 9:0 Post Processing Block 4 Oversampling Index of Max
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB4MAXI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4MAXI_BITS  bit;
};

struct ADC_ADCPPB4MIN_BITS {            // bits description
    uint32_t MIN:17;                    // 16:0 Post Processing Block 4 Oversampling Min
    uint16_t SIGN:15;                   // 31:17 Sign Extended Bits
};

union ADC_ADCPPB4MIN_REG {
    uint32_t  all;
    struct  ADC_ADCPPB4MIN_BITS  bit;
};

struct ADC_ADCPPB4MINI_BITS {           // bits description
    uint16_t MINI:10;                   // 9:0 Post Processing Block 4 Oversampling Index of Min
    uint16_t rsvd1:6;                   // 15:10 Reserved
};

union ADC_ADCPPB4MINI_REG {
    uint16_t  all;
    struct  ADC_ADCPPB4MINI_BITS  bit;
};

struct ADC_RESULT_REGS {
    uint16_t                                 ADCRESULT0;                   // ADC Result 0 Register
    uint16_t                                 ADCRESULT1;                   // ADC Result 1 Register
    uint16_t                                 ADCRESULT2;                   // ADC Result 2 Register
    uint16_t                                 ADCRESULT3;                   // ADC Result 3 Register
    uint16_t                                 ADCRESULT4;                   // ADC Result 4 Register
    uint16_t                                 ADCRESULT5;                   // ADC Result 5 Register
    uint16_t                                 ADCRESULT6;                   // ADC Result 6 Register
    uint16_t                                 ADCRESULT7;                   // ADC Result 7 Register
    uint16_t                                 ADCRESULT8;                   // ADC Result 8 Register
    uint16_t                                 ADCRESULT9;                   // ADC Result 9 Register
    uint16_t                                 ADCRESULT10;                  // ADC Result 10 Register
    uint16_t                                 ADCRESULT11;                  // ADC Result 11 Register
    uint16_t                                 ADCRESULT12;                  // ADC Result 12 Register
    uint16_t                                 ADCRESULT13;                  // ADC Result 13 Register
    uint16_t                                 ADCRESULT14;                  // ADC Result 14 Register
    uint16_t                                 ADCRESULT15;                  // ADC Result 15 Register
    uint16_t                                 ADCRESULT16;                  // ADC Result 16 Register
    uint16_t                                 ADCRESULT17;                  // ADC Result 17 Register
    uint16_t                                 ADCRESULT18;                  // ADC Result 18 Register
    uint16_t                                 ADCRESULT19;                  // ADC Result 19 Register
    uint16_t                                 ADCRESULT20;                  // ADC Result 20 Register
    uint16_t                                 ADCRESULT21;                  // ADC Result 21 Register
    uint16_t                                 ADCRESULT22;                  // ADC Result 22 Register
    uint16_t                                 ADCRESULT23;                  // ADC Result 23 Register
    uint16_t                                 ADCRESULT24;                  // ADC Result 24 Register
    uint16_t                                 ADCRESULT25;                  // ADC Result 25 Register
    uint16_t                                 ADCRESULT26;                  // ADC Result 26 Register
    uint16_t                                 ADCRESULT27;                  // ADC Result 27 Register
    uint16_t                                 ADCRESULT28;                  // ADC Result 28 Register
    uint16_t                                 ADCRESULT29;                  // ADC Result 29 Register
    uint16_t                                 ADCRESULT30;                  // ADC Result 30 Register
    uint16_t                                 ADCRESULT31;                  // ADC Result 31 Register
    union   ADC_ADCPPB1RESULT_REG            ADCPPB1RESULT;                // ADC Post Processing Block 1 Result Register
    union   ADC_ADCPPB2RESULT_REG            ADCPPB2RESULT;                // ADC Post Processing Block 2 Result Register
    union   ADC_ADCPPB3RESULT_REG            ADCPPB3RESULT;                // ADC Post Processing Block 3 Result Register
    union   ADC_ADCPPB4RESULT_REG            ADCPPB4RESULT;                // ADC Post Processing Block 4 Result Register
    union   ADC_ADCPPB1SUM_REG               ADCPPB1SUM;                   // ADC PPB 1 Final Sum Result Register
    union   ADC_ADCPPB1COUNT_REG             ADCPPB1COUNT;                 // ADC PPB1 Final Conversion Count Register
    uint8_t                                  rsvd1[2];                     // Reserved
    union   ADC_ADCPPB2SUM_REG               ADCPPB2SUM;                   // ADC PPB 2 Final Sum Result Register
    union   ADC_ADCPPB2COUNT_REG             ADCPPB2COUNT;                 // ADC PPB2 Final Conversion Count Register
    uint8_t                                  rsvd2[2];                     // Reserved
    union   ADC_ADCPPB3SUM_REG               ADCPPB3SUM;                   // ADC PPB 3 Final Sum Result Register
    union   ADC_ADCPPB3COUNT_REG             ADCPPB3COUNT;                 // ADC PPB3 Final Conversion Count Register
    uint8_t                                  rsvd3[2];                     // Reserved
    union   ADC_ADCPPB4SUM_REG               ADCPPB4SUM;                   // ADC PPB 4 Final Sum Result Register
    union   ADC_ADCPPB4COUNT_REG             ADCPPB4COUNT;                 // ADC PPB4 Final Conversion Count Register
    uint8_t                                  rsvd4[2];                     // Reserved
    union   ADC_ADCPPB1MAX_REG               ADCPPB1MAX;                   // ADC PPB 1 Final Max Result Register
    union   ADC_ADCPPB1MAXI_REG              ADCPPB1MAXI;                  // ADC PPB 1 Final Max Index Result Register
    uint8_t                                  rsvd5[2];                     // Reserved
    union   ADC_ADCPPB1MIN_REG               ADCPPB1MIN;                   // ADC PPB 1 Final Min Result Register
    union   ADC_ADCPPB1MINI_REG              ADCPPB1MINI;                  // ADC PPB 1 Final Min Index Result Register
    uint8_t                                  rsvd6[2];                     // Reserved
    union   ADC_ADCPPB2MAX_REG               ADCPPB2MAX;                   // ADC PPB 2 Final Max Result Register
    union   ADC_ADCPPB2MAXI_REG              ADCPPB2MAXI;                  // ADC PPB 2 Final Max Index Result Register
    uint8_t                                  rsvd7[2];                     // Reserved
    union   ADC_ADCPPB2MIN_REG               ADCPPB2MIN;                   // ADC PPB 2 Final Min Result Register
    union   ADC_ADCPPB2MINI_REG              ADCPPB2MINI;                  // ADC PPB 2 Final Min Index Result Register
    uint8_t                                  rsvd8[2];                     // Reserved
    union   ADC_ADCPPB3MAX_REG               ADCPPB3MAX;                   // ADC PPB 3 Final Max Result Register
    union   ADC_ADCPPB3MAXI_REG              ADCPPB3MAXI;                  // ADC PPB 3 Final Max Index Result Register
    uint8_t                                  rsvd9[2];                     // Reserved
    union   ADC_ADCPPB3MIN_REG               ADCPPB3MIN;                   // ADC PPB 3 Final Min Result Register
    union   ADC_ADCPPB3MINI_REG              ADCPPB3MINI;                  // ADC PPB 3 Final Min Index Result Register
    uint8_t                                  rsvd10[2];                    // Reserved
    union   ADC_ADCPPB4MAX_REG               ADCPPB4MAX;                   // ADC PPB 4 Final Max Result Register
    union   ADC_ADCPPB4MAXI_REG              ADCPPB4MAXI;                  // ADC PPB 4 Final Max Index Result Register
    uint8_t                                  rsvd11[2];                    // Reserved
    union   ADC_ADCPPB4MIN_REG               ADCPPB4MIN;                   // ADC PPB 4 Final Min Result Register
    union   ADC_ADCPPB4MINI_REG              ADCPPB4MINI;                  // ADC PPB 4 Final Min Index Result Register
};

struct ADC_CHECKCONFIG_BITS {           // bits description
    uint16_t rsvd1:5;                   // 4:0 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t SWSYNC:1;                  // 6 Result Safe Check SW Force Sync.
    uint16_t rsvd3:8;                   // 14:7 Reserved
    uint16_t CHKEN:1;                   // 15 Result Safe Check Module Enable
};

union ADC_CHECKCONFIG_REG {
    uint16_t  all;
    struct  ADC_CHECKCONFIG_BITS  bit;
};

struct ADC_CHECKSTATUS_BITS {           // bits description
    uint16_t RES1READY:1;               // 0 Result Safe Check Result 1 Arrived
    uint16_t RES2READY:1;               // 1 Result Safe Check Result 2 Arrived
    uint16_t OOT:1;                     // 2 Safe Check OOT Flag
    uint16_t rsvd1:13;                  // 15:3 Reserved
};

union ADC_CHECKSTATUS_REG {
    uint16_t  all;
    struct  ADC_CHECKSTATUS_BITS  bit;
};

struct ADC_ADCRESSEL1_BITS {            // bits description
    uint16_t ADCSEL:3;                  // 2:0 Result Safe Check ADC Select 1
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t ADCRESULTSEL:6;            // 9:4 Result Safe Check Result Select 1
    uint16_t rsvd2:6;                   // 15:10 Reserved
};

union ADC_ADCRESSEL1_REG {
    uint16_t  all;
    struct  ADC_ADCRESSEL1_BITS  bit;
};

struct ADC_ADCRESSEL2_BITS {            // bits description
    uint16_t ADCSEL:3;                  // 2:0 Result Safe Check ADC Select 2
    uint16_t rsvd1:1;                   // 3 Reserved
    uint16_t ADCRESULTSEL:6;            // 9:4 Result Safe Check Result Select 2
    uint16_t rsvd2:6;                   // 15:10 Reserved
};

union ADC_ADCRESSEL2_REG {
    uint16_t  all;
    struct  ADC_ADCRESSEL2_BITS  bit;
};

struct ADC_TOLERANCE_BITS {             // bits description
    uint32_t TOLERANCE:24;              // 23:0 Result Safe Check Tolerance
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_TOLERANCE_REG {
    uint32_t  all;
    struct  ADC_TOLERANCE_BITS  bit;
};

struct ADC_CHECKRESULT1_BITS {          // bits description
    uint32_t RESULT:24;                 // 23:0 Result Safe Check Captured Result
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_CHECKRESULT1_REG {
    uint32_t  all;
    struct  ADC_CHECKRESULT1_BITS  bit;
};

struct ADC_CHECKRESULT2_BITS {          // bits description
    uint32_t RESULT:24;                 // 23:0 Result Safe Check Captured Result
    uint16_t rsvd1:8;                   // 31:24 Reserved
};

union ADC_CHECKRESULT2_REG {
    uint32_t  all;
    struct  ADC_CHECKRESULT2_BITS  bit;
};

struct ADC_SAFECHECK_REGS {
    union   ADC_CHECKCONFIG_REG              CHECKCONFIG;                  // ADC Check Configuration Register
    uint8_t                                  rsvd1[2];                     // Reserved
    union   ADC_CHECKSTATUS_REG              CHECKSTATUS;                  // ADC Check Status Register
    uint8_t                                  rsvd2[2];                     // Reserved
    union   ADC_ADCRESSEL1_REG               ADCRESSEL1;                   // ADC Check 1 Select Register
    uint8_t                                  rsvd3[2];                     // Reserved
    union   ADC_ADCRESSEL2_REG               ADCRESSEL2;                   // ADC Check 2 Select Register
    uint8_t                                  rsvd4[2];                     // Reserved
    union   ADC_TOLERANCE_REG                TOLERANCE;                    // ADC Check Tolerance Register
    uint8_t                                  rsvd5[4];                     // Reserved
    union   ADC_CHECKRESULT1_REG             CHECKRESULT1;                 // ADC Check Captured Result 1
    union   ADC_CHECKRESULT2_REG             CHECKRESULT2;                 // ADC Check Captured Result 2
};

struct ADC_OOTFLG_BITS {                // bits description
    uint16_t OOT1:1;                    // 0 Checker 1 Out-of-Tolerance Flag
    uint16_t OOT2:1;                    // 1 Checker 2 Out-of-Tolerance Flag
    uint16_t OOT3:1;                    // 2 Checker 3 Out-of-Tolerance Flag
    uint16_t OOT4:1;                    // 3 Checker 4 Out-of-Tolerance Flag
    uint16_t OOT5:1;                    // 4 Checker 5 Out-of-Tolerance Flag
    uint16_t OOT6:1;                    // 5 Checker 6 Out-of-Tolerance Flag
    uint16_t OOT7:1;                    // 6 Checker 7 Out-of-Tolerance Flag
    uint16_t OOT8:1;                    // 7 Checker 8 Out-of-Tolerance Flag
    uint16_t OOT9:1;                    // 8 Checker 9 Out-of-Tolerance Flag
    uint16_t OOT10:1;                   // 9 Checker 10 Out-of-Tolerance Flag
    uint16_t OOT11:1;                   // 10 Checker 11 Out-of-Tolerance Flag
    uint16_t OOT12:1;                   // 11 Checker 12 Out-of-Tolerance Flag
    uint16_t OOT13:1;                   // 12 Checker 13 Out-of-Tolerance Flag
    uint16_t OOT14:1;                   // 13 Checker 14 Out-of-Tolerance Flag
    uint16_t OOT15:1;                   // 14 Checker 15 Out-of-Tolerance Flag
    uint16_t OOT16:1;                   // 15 Checker 16 Out-of-Tolerance Flag
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_OOTFLG_REG {
    uint32_t  all;
    struct  ADC_OOTFLG_BITS  bit;
};

struct ADC_OOTFLGCLR_BITS {             // bits description
    uint16_t OOT1:1;                    // 0 Checker 1 OOT Flag Clear
    uint16_t OOT2:1;                    // 1 Checker 2 OOT Flag Clear
    uint16_t OOT3:1;                    // 2 Checker 3 OOT Flag Clear
    uint16_t OOT4:1;                    // 3 Checker 4 OOT Flag Clear
    uint16_t OOT5:1;                    // 4 Checker 5 OOT Flag Clear
    uint16_t OOT6:1;                    // 5 Checker 6 OOT Flag Clear
    uint16_t OOT7:1;                    // 6 Checker 7 OOT Flag Clear
    uint16_t OOT8:1;                    // 7 Checker 8 OOT Flag Clear
    uint16_t OOT9:1;                    // 8 Checker 9 OOT Flag Clear
    uint16_t OOT10:1;                   // 9 Checker 10 OOT Flag Clear
    uint16_t OOT11:1;                   // 10 Checker 11 OOT Flag Clear
    uint16_t OOT12:1;                   // 11 Checker 12 OOT Flag Clear
    uint16_t OOT13:1;                   // 12 Checker 13 OOT Flag Clear
    uint16_t OOT14:1;                   // 13 Checker 14 OOT Flag Clear
    uint16_t OOT15:1;                   // 14 Checker 15 OOT Flag Clear
    uint16_t OOT16:1;                   // 15 Checker 16 OOT Flag Clear
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_OOTFLGCLR_REG {
    uint32_t  all;
    struct  ADC_OOTFLGCLR_BITS  bit;
};

struct ADC_RES1OVF_BITS {               // bits description
    uint16_t RES1OVF1:1;                // 0 Checker 1 Result 1 Overflow Flag
    uint16_t RES1OVF2:1;                // 1 Checker 2 Result 1 Overflow Flag
    uint16_t RES1OVF3:1;                // 2 Checker 3 Result 1 Overflow Flag
    uint16_t RES1OVF4:1;                // 3 Checker 4 Result 1 Overflow Flag
    uint16_t RES1OVF5:1;                // 4 Checker 5 Result 5 Overflow Flag
    uint16_t RES1OVF6:1;                // 5 Checker 6 Result 1 Overflow Flag
    uint16_t RES1OVF7:1;                // 6 Checker 7 Result 1 Overflow Flag
    uint16_t RES1OVF8:1;                // 7 Checker 8 Result 1 Overflow Flag
    uint16_t RES1OVF9:1;                // 8 Checker 9 Result 1 Overflow Flag
    uint16_t RES1OVF10:1;               // 9 Checker 10 Result 1 Overflow Flag
    uint16_t RES1OVF11:1;               // 10 Checker 11 Result 1 Overflow Flag
    uint16_t RES1OVF12:1;               // 11 Checker 12 Result 1 Overflow Flag
    uint16_t RES1OVF13:1;               // 12 Checker 13 Result 5 Overflow Flag
    uint16_t RES1OVF14:1;               // 13 Checker 14 Result 1 Overflow Flag
    uint16_t RES1OVF15:1;               // 14 Checker 15 Result 1 Overflow Flag
    uint16_t RES1OVF16:1;               // 15 Checker 16 Result 1 Overflow Flag
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_RES1OVF_REG {
    uint32_t  all;
    struct  ADC_RES1OVF_BITS  bit;
};

struct ADC_RES1OVFCLR_BITS {            // bits description
    uint16_t RES1OVF1:1;                // 0 Checker 1 Result 1  OVF Flag Clear
    uint16_t RES1OVF2:1;                // 1 Checker 2 Result 1 OVF Flag Clear
    uint16_t RES1OVF3:1;                // 2 Checker 3 Result 1 OVF Flag Clear
    uint16_t RES1OVF4:1;                // 3 Checker 4 Result 1 OVF Flag Clear
    uint16_t RES1OVF5:1;                // 4 Checker 5 Result 1  OVF Flag Clear
    uint16_t RES1OVF6:1;                // 5 Checker 6 Result 1 OVF Flag Clear
    uint16_t RES1OVF7:1;                // 6 Checker 7 Result 1 OVF Flag Clear
    uint16_t RES1OVF8:1;                // 7 Checker 8 Result 1 OVF Flag Clear
    uint16_t RES1OVF9:1;                // 8 Checker 9 Result 1  OVF Flag Clear
    uint16_t RES1OVF10:1;               // 9 Checker 10 Result 1 OVF Flag Clear
    uint16_t RES1OVF11:1;               // 10 Checker 11 Result 1 OVF Flag Clear
    uint16_t RES1OVF12:1;               // 11 Checker 12 Result 1 OVF Flag Clear
    uint16_t RES1OVF13:1;               // 12 Checker 13 Result 1  OVF Flag Clear
    uint16_t RES1OVF14:1;               // 13 Checker 14 Result 1 OVF Flag Clear
    uint16_t RES1OVF15:1;               // 14 Checker 15 Result 1 OVF Flag Clear
    uint16_t RES1OVF16:1;               // 15 Checker 16 Result 1 OVF Flag Clear
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_RES1OVFCLR_REG {
    uint32_t  all;
    struct  ADC_RES1OVFCLR_BITS  bit;
};

struct ADC_RES2OVF_BITS {               // bits description
    uint16_t RES2OVF1:1;                // 0 Checker 1 Result 2 Overflow Flag
    uint16_t RES2OVF2:1;                // 1 Checker 2 Result 2 Overflow Flag
    uint16_t RES2OVF3:1;                // 2 Checker 3 Result 2 Overflow Flag
    uint16_t RES2OVF4:1;                // 3 Checker 4 Result 2 Overflow Flag
    uint16_t RES2OVF5:1;                // 4 Checker 5 Result 2 Overflow Flag
    uint16_t RES2OVF6:1;                // 5 Checker 6 Result 2 Overflow Flag
    uint16_t RES2OVF7:1;                // 6 Checker 7 Result 2 Overflow Flag
    uint16_t RES2OVF8:1;                // 7 Checker 8 Result 2 Overflow Flag
    uint16_t RES2OVF9:1;                // 8 Checker 9 Result 2 Overflow Flag
    uint16_t RES2OVF10:1;               // 9 Checker 10 Result 2 Overflow Flag
    uint16_t RES2OVF11:1;               // 10 Checker 11 Result 2 Overflow Flag
    uint16_t RES2OVF12:1;               // 11 Checker 12 Result 2 Overflow Flag
    uint16_t RES2OVF13:1;               // 12 Checker 13 Result 2 Overflow Flag
    uint16_t RES2OVF14:1;               // 13 Checker 14 Result 2 Overflow Flag
    uint16_t RES2OVF15:1;               // 14 Checker 15 Result 2 Overflow Flag
    uint16_t RES2OVF16:1;               // 15 Checker 16 Result 2 Overflow Flag
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_RES2OVF_REG {
    uint32_t  all;
    struct  ADC_RES2OVF_BITS  bit;
};

struct ADC_RES2OVFCLR_BITS {            // bits description
    uint16_t RES2OVF1:1;                // 0 Checker 1 Result 2  OVF Flag Clear
    uint16_t RES2OVF2:1;                // 1 Checker 2 Result 2 OVF Flag Clear
    uint16_t RES2OVF3:1;                // 2 Checker 3 Result 2 OVF Flag Clear
    uint16_t RES2OVF4:1;                // 3 Checker 4 Result 2 OVF Flag Clear
    uint16_t RES2OVF5:1;                // 4 Checker 5 Result 2  OVF Flag Clear
    uint16_t RES2OVF6:1;                // 5 Checker 6 Result 2 OVF Flag Clear
    uint16_t RES2OVF7:1;                // 6 Checker 7 Result 2 OVF Flag Clear
    uint16_t RES2OVF8:1;                // 7 Checker 8 Result 2 OVF Flag Clear
    uint16_t RES2OVF9:1;                // 8 Checker 9 Result 2  OVF Flag Clear
    uint16_t RES2OVF10:1;               // 9 Checker 10 Result 2 OVF Flag Clear
    uint16_t RES2OVF11:1;               // 10 Checker 11 Result 2 OVF Flag Clear
    uint16_t RES2OVF12:1;               // 11 Checker 12 Result 2 OVF Flag Clear
    uint16_t RES2OVF13:1;               // 12 Checker 13 Result 2  OVF Flag Clear
    uint16_t RES2OVF14:1;               // 13 Checker 14 Result 2 OVF Flag Clear
    uint16_t RES2OVF15:1;               // 14 Checker 15 Result 2 OVF Flag Clear
    uint16_t RES2OVF16:1;               // 15 Checker 16 Result 2 OVF Flag Clear
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_RES2OVFCLR_REG {
    uint32_t  all;
    struct  ADC_RES2OVFCLR_BITS  bit;
};

struct ADC_CHECKINTFLG_BITS {           // bits description
    uint16_t CHECKINT:1;                // 0 ADC Safety Checker Subsystem Interrupt Flag
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union ADC_CHECKINTFLG_REG {
    uint16_t  all;
    struct  ADC_CHECKINTFLG_BITS  bit;
};

struct ADC_CHECKINTFLGCLR_BITS {        // bits description
    uint16_t CHECKINTCLR:1;             // 0 ADC Safety Checker Subsystem Interrupt Flag Clear
    uint16_t rsvd1:15;                  // 15:1 Reserved
};

union ADC_CHECKINTFLGCLR_REG {
    uint16_t  all;
    struct  ADC_CHECKINTFLGCLR_BITS  bit;
};

struct ADC_CHECKINTSEL1_BITS {          // bits description
    uint16_t RES1OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 1
    uint16_t RES1OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 1
    uint16_t RES1OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 1
    uint16_t RES1OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 1
    uint16_t RES1OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 1
    uint16_t RES1OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 1
    uint16_t RES1OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 1
    uint16_t RES1OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 1
    uint16_t RES1OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 1
    uint16_t RES1OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 1
    uint16_t RES1OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 1
    uint16_t RES1OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 1
    uint16_t RES1OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 1
    uint16_t RES1OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 1
    uint16_t RES1OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 1
    uint16_t RES1OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 1
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKINTSEL1_REG {
    uint32_t  all;
    struct  ADC_CHECKINTSEL1_BITS  bit;
};

struct ADC_CHECKINTSEL2_BITS {          // bits description
    uint16_t RES2OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 2
    uint16_t RES2OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 2
    uint16_t RES2OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 2
    uint16_t RES2OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 2
    uint16_t RES2OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 2
    uint16_t RES2OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 2
    uint16_t RES2OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 2
    uint16_t RES2OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 2
    uint16_t RES2OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 2
    uint16_t RES2OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 2
    uint16_t RES2OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 2
    uint16_t RES2OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 2
    uint16_t RES2OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 2
    uint16_t RES2OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 2
    uint16_t RES2OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 2
    uint16_t RES2OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 2
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKINTSEL2_REG {
    uint32_t  all;
    struct  ADC_CHECKINTSEL2_BITS  bit;
};

struct ADC_CHECKINTSEL3_BITS {          // bits description
    uint16_t OOT1EN:1;                  // 0 Out-of-Tolerance Enable from Checker 1
    uint16_t OOT2EN:1;                  // 1 Out-of-Tolerance Enable from Checker 2
    uint16_t OOT3EN:1;                  // 2 Out-of-Tolerance Enable from Checker 3
    uint16_t OOT4EN:1;                  // 3 Out-of-Tolerance Enable from Checker 4
    uint16_t OOT5EN:1;                  // 4 Out-of-Tolerance Enable from Checker 5
    uint16_t OOT6EN:1;                  // 5 Out-of-Tolerance Enable from Checker 6
    uint16_t OOT7EN:1;                  // 6 Out-of-Tolerance Enable from Checker 7
    uint16_t OOT8EN:1;                  // 7 Out-of-Tolerance Enable from Checker 8
    uint16_t OOT9EN:1;                  // 8 Out-of-Tolerance Enable from Checker 9
    uint16_t OOT10EN:1;                 // 9 Out-of-Tolerance Enable from Checker 10
    uint16_t OOT11EN:1;                 // 10 Out-of-Tolerance Enable from Checker 11
    uint16_t OOT12EN:1;                 // 11 Out-of-Tolerance Enable from Checker 12
    uint16_t OOT13EN:1;                 // 12 Out-of-Tolerance Enable from Checker 13
    uint16_t OOT14EN:1;                 // 13 Out-of-Tolerance Enable from Checker 14
    uint16_t OOT15EN:1;                 // 14 Out-of-Tolerance Enable from Checker 15
    uint16_t OOT16EN:1;                 // 15 Out-of-Tolerance Enable from Checker 16
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKINTSEL3_REG {
    uint32_t  all;
    struct  ADC_CHECKINTSEL3_BITS  bit;
};

struct ADC_CHECKEVT1SEL1_BITS {         // bits description
    uint16_t RES1OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 1
    uint16_t RES1OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 1
    uint16_t RES1OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 1
    uint16_t RES1OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 1
    uint16_t RES1OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 1
    uint16_t RES1OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 1
    uint16_t RES1OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 1
    uint16_t RES1OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 1
    uint16_t RES1OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 1
    uint16_t RES1OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 1
    uint16_t RES1OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 1
    uint16_t RES1OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 1
    uint16_t RES1OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 1
    uint16_t RES1OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 1
    uint16_t RES1OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 1
    uint16_t RES1OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 1
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT1SEL1_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT1SEL1_BITS  bit;
};

struct ADC_CHECKEVT1SEL2_BITS {         // bits description
    uint16_t RES2OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 2
    uint16_t RES2OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 2
    uint16_t RES2OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 2
    uint16_t RES2OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 2
    uint16_t RES2OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 2
    uint16_t RES2OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 2
    uint16_t RES2OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 2
    uint16_t RES2OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 2
    uint16_t RES2OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 2
    uint16_t RES2OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 2
    uint16_t RES2OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 2
    uint16_t RES2OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 2
    uint16_t RES2OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 2
    uint16_t RES2OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 2
    uint16_t RES2OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 2
    uint16_t RES2OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 2
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT1SEL2_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT1SEL2_BITS  bit;
};

struct ADC_CHECKEVT1SEL3_BITS {         // bits description
    uint16_t OOT1EN:1;                  // 0 Out-of-Tolerance Enable from Checker 1
    uint16_t OOT2EN:1;                  // 1 Out-of-Tolerance Enable from Checker 2
    uint16_t OOT3EN:1;                  // 2 Out-of-Tolerance Enable from Checker 3
    uint16_t OOT4EN:1;                  // 3 Out-of-Tolerance Enable from Checker 4
    uint16_t OOT5EN:1;                  // 4 Out-of-Tolerance Enable from Checker 5
    uint16_t OOT6EN:1;                  // 5 Out-of-Tolerance Enable from Checker 6
    uint16_t OOT7EN:1;                  // 6 Out-of-Tolerance Enable from Checker 7
    uint16_t OOT8EN:1;                  // 7 Out-of-Tolerance Enable from Checker 8
    uint16_t OOT9EN:1;                  // 8 Out-of-Tolerance Enable from Checker 9
    uint16_t OOT10EN:1;                 // 9 Out-of-Tolerance Enable from Checker 10
    uint16_t OOT11EN:1;                 // 10 Out-of-Tolerance Enable from Checker 11
    uint16_t OOT12EN:1;                 // 11 Out-of-Tolerance Enable from Checker 12
    uint16_t OOT13EN:1;                 // 12 Out-of-Tolerance Enable from Checker 13
    uint16_t OOT14EN:1;                 // 13 Out-of-Tolerance Enable from Checker 14
    uint16_t OOT15EN:1;                 // 14 Out-of-Tolerance Enable from Checker 15
    uint16_t OOT16EN:1;                 // 15 Out-of-Tolerance Enable from Checker 16
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT1SEL3_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT1SEL3_BITS  bit;
};

struct ADC_CHECKEVT2SEL1_BITS {         // bits description
    uint16_t RES1OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 1
    uint16_t RES1OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 1
    uint16_t RES1OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 1
    uint16_t RES1OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 1
    uint16_t RES1OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 1
    uint16_t RES1OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 1
    uint16_t RES1OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 1
    uint16_t RES1OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 1
    uint16_t RES1OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 1
    uint16_t RES1OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 1
    uint16_t RES1OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 1
    uint16_t RES1OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 1
    uint16_t RES1OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 1
    uint16_t RES1OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 1
    uint16_t RES1OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 1
    uint16_t RES1OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 1
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT2SEL1_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT2SEL1_BITS  bit;
};

struct ADC_CHECKEVT2SEL2_BITS {         // bits description
    uint16_t RES2OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 2
    uint16_t RES2OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 2
    uint16_t RES2OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 2
    uint16_t RES2OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 2
    uint16_t RES2OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 2
    uint16_t RES2OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 2
    uint16_t RES2OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 2
    uint16_t RES2OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 2
    uint16_t RES2OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 2
    uint16_t RES2OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 2
    uint16_t RES2OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 2
    uint16_t RES2OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 2
    uint16_t RES2OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 2
    uint16_t RES2OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 2
    uint16_t RES2OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 2
    uint16_t RES2OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 2
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT2SEL2_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT2SEL2_BITS  bit;
};

struct ADC_CHECKEVT2SEL3_BITS {         // bits description
    uint16_t OOT1EN:1;                  // 0 Out-of-Tolerance Enable from Checker 1
    uint16_t OOT2EN:1;                  // 1 Out-of-Tolerance Enable from Checker 2
    uint16_t OOT3EN:1;                  // 2 Out-of-Tolerance Enable from Checker 3
    uint16_t OOT4EN:1;                  // 3 Out-of-Tolerance Enable from Checker 4
    uint16_t OOT5EN:1;                  // 4 Out-of-Tolerance Enable from Checker 5
    uint16_t OOT6EN:1;                  // 5 Out-of-Tolerance Enable from Checker 6
    uint16_t OOT7EN:1;                  // 6 Out-of-Tolerance Enable from Checker 7
    uint16_t OOT8EN:1;                  // 7 Out-of-Tolerance Enable from Checker 8
    uint16_t OOT9EN:1;                  // 8 Out-of-Tolerance Enable from Checker 9
    uint16_t OOT10EN:1;                 // 9 Out-of-Tolerance Enable from Checker 10
    uint16_t OOT11EN:1;                 // 10 Out-of-Tolerance Enable from Checker 11
    uint16_t OOT12EN:1;                 // 11 Out-of-Tolerance Enable from Checker 12
    uint16_t OOT13EN:1;                 // 12 Out-of-Tolerance Enable from Checker 13
    uint16_t OOT14EN:1;                 // 13 Out-of-Tolerance Enable from Checker 14
    uint16_t OOT15EN:1;                 // 14 Out-of-Tolerance Enable from Checker 15
    uint16_t OOT16EN:1;                 // 15 Out-of-Tolerance Enable from Checker 16
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT2SEL3_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT2SEL3_BITS  bit;
};

struct ADC_CHECKEVT3SEL1_BITS {         // bits description
    uint16_t RES1OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 1
    uint16_t RES1OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 1
    uint16_t RES1OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 1
    uint16_t RES1OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 1
    uint16_t RES1OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 1
    uint16_t RES1OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 1
    uint16_t RES1OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 1
    uint16_t RES1OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 1
    uint16_t RES1OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 1
    uint16_t RES1OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 1
    uint16_t RES1OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 1
    uint16_t RES1OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 1
    uint16_t RES1OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 1
    uint16_t RES1OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 1
    uint16_t RES1OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 1
    uint16_t RES1OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 1
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT3SEL1_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT3SEL1_BITS  bit;
};

struct ADC_CHECKEVT3SEL2_BITS {         // bits description
    uint16_t RES2OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 2
    uint16_t RES2OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 2
    uint16_t RES2OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 2
    uint16_t RES2OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 2
    uint16_t RES2OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 2
    uint16_t RES2OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 2
    uint16_t RES2OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 2
    uint16_t RES2OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 2
    uint16_t RES2OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 2
    uint16_t RES2OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 2
    uint16_t RES2OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 2
    uint16_t RES2OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 2
    uint16_t RES2OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 2
    uint16_t RES2OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 2
    uint16_t RES2OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 2
    uint16_t RES2OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 2
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT3SEL2_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT3SEL2_BITS  bit;
};

struct ADC_CHECKEVT3SEL3_BITS {         // bits description
    uint16_t OOT1EN:1;                  // 0 Out-of-Tolerance Enable from Checker 1
    uint16_t OOT2EN:1;                  // 1 Out-of-Tolerance Enable from Checker 2
    uint16_t OOT3EN:1;                  // 2 Out-of-Tolerance Enable from Checker 3
    uint16_t OOT4EN:1;                  // 3 Out-of-Tolerance Enable from Checker 4
    uint16_t OOT5EN:1;                  // 4 Out-of-Tolerance Enable from Checker 5
    uint16_t OOT6EN:1;                  // 5 Out-of-Tolerance Enable from Checker 6
    uint16_t OOT7EN:1;                  // 6 Out-of-Tolerance Enable from Checker 7
    uint16_t OOT8EN:1;                  // 7 Out-of-Tolerance Enable from Checker 8
    uint16_t OOT9EN:1;                  // 8 Out-of-Tolerance Enable from Checker 9
    uint16_t OOT10EN:1;                 // 9 Out-of-Tolerance Enable from Checker 10
    uint16_t OOT11EN:1;                 // 10 Out-of-Tolerance Enable from Checker 11
    uint16_t OOT12EN:1;                 // 11 Out-of-Tolerance Enable from Checker 12
    uint16_t OOT13EN:1;                 // 12 Out-of-Tolerance Enable from Checker 13
    uint16_t OOT14EN:1;                 // 13 Out-of-Tolerance Enable from Checker 14
    uint16_t OOT15EN:1;                 // 14 Out-of-Tolerance Enable from Checker 15
    uint16_t OOT16EN:1;                 // 15 Out-of-Tolerance Enable from Checker 16
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT3SEL3_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT3SEL3_BITS  bit;
};

struct ADC_CHECKEVT4SEL1_BITS {         // bits description
    uint16_t RES1OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 1
    uint16_t RES1OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 1
    uint16_t RES1OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 1
    uint16_t RES1OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 1
    uint16_t RES1OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 1
    uint16_t RES1OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 1
    uint16_t RES1OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 1
    uint16_t RES1OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 1
    uint16_t RES1OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 1
    uint16_t RES1OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 1
    uint16_t RES1OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 1
    uint16_t RES1OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 1
    uint16_t RES1OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 1
    uint16_t RES1OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 1
    uint16_t RES1OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 1
    uint16_t RES1OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 1
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT4SEL1_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT4SEL1_BITS  bit;
};

struct ADC_CHECKEVT4SEL2_BITS {         // bits description
    uint16_t RES2OVF1EN:1;              // 0 Overflow Enable from Checker 1 Result 2
    uint16_t RES2OVF2EN:1;              // 1 Overflow Enable from Checker 2 Result 2
    uint16_t RES2OVF3EN:1;              // 2 Overflow Enable from Checker 3 Result 2
    uint16_t RES2OVF4EN:1;              // 3 Overflow Enable from Checker 4 Result 2
    uint16_t RES2OVF5EN:1;              // 4 Overflow Enable from Checker 5 Result 2
    uint16_t RES2OVF6EN:1;              // 5 Overflow Enable from Checker 6 Result 2
    uint16_t RES2OVF7EN:1;              // 6 Overflow Enable from Checker 7 Result 2
    uint16_t RES2OVF8EN:1;              // 7 Overflow Enable from Checker 8 Result 2
    uint16_t RES2OVF9EN:1;              // 8 Overflow Enable from Checker 9 Result 2
    uint16_t RES2OVF10EN:1;             // 9 Overflow Enable from Checker 10 Result 2
    uint16_t RES2OVF11EN:1;             // 10 Overflow Enable from Checker 11 Result 2
    uint16_t RES2OVF12EN:1;             // 11 Overflow Enable from Checker 12 Result 2
    uint16_t RES2OVF13EN:1;             // 12 Overflow Enable from Checker 13 Result 2
    uint16_t RES2OVF14EN:1;             // 13 Overflow Enable from Checker 14 Result 2
    uint16_t RES2OVF15EN:1;             // 14 Overflow Enable from Checker 15 Result 2
    uint16_t RES2OVF16EN:1;             // 15 Overflow Enable from Checker 16 Result 2
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT4SEL2_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT4SEL2_BITS  bit;
};

struct ADC_CHECKEVT4SEL3_BITS {         // bits description
    uint16_t OOT1EN:1;                  // 0 Out-of-Tolerance Enable from Checker 1
    uint16_t OOT2EN:1;                  // 1 Out-of-Tolerance Enable from Checker 2
    uint16_t OOT3EN:1;                  // 2 Out-of-Tolerance Enable from Checker 3
    uint16_t OOT4EN:1;                  // 3 Out-of-Tolerance Enable from Checker 4
    uint16_t OOT5EN:1;                  // 4 Out-of-Tolerance Enable from Checker 5
    uint16_t OOT6EN:1;                  // 5 Out-of-Tolerance Enable from Checker 6
    uint16_t OOT7EN:1;                  // 6 Out-of-Tolerance Enable from Checker 7
    uint16_t OOT8EN:1;                  // 7 Out-of-Tolerance Enable from Checker 8
    uint16_t OOT9EN:1;                  // 8 Out-of-Tolerance Enable from Checker 9
    uint16_t OOT10EN:1;                 // 9 Out-of-Tolerance Enable from Checker 10
    uint16_t OOT11EN:1;                 // 10 Out-of-Tolerance Enable from Checker 11
    uint16_t OOT12EN:1;                 // 11 Out-of-Tolerance Enable from Checker 12
    uint16_t OOT13EN:1;                 // 12 Out-of-Tolerance Enable from Checker 13
    uint16_t OOT14EN:1;                 // 13 Out-of-Tolerance Enable from Checker 14
    uint16_t OOT15EN:1;                 // 14 Out-of-Tolerance Enable from Checker 15
    uint16_t OOT16EN:1;                 // 15 Out-of-Tolerance Enable from Checker 16
    uint16_t rsvd1:16;                  // 31:16 Reserved
};

union ADC_CHECKEVT4SEL3_REG {
    uint32_t  all;
    struct  ADC_CHECKEVT4SEL3_BITS  bit;
};

struct ADC_SAFECHECK_INTEVT_REGS {
    union   ADC_OOTFLG_REG                   OOTFLG;                       // Checker Out-of-Tolerance Flag Register
    union   ADC_OOTFLGCLR_REG                OOTFLGCLR;                    // Checker Out-of-Tolerance Flag Clear Register
    union   ADC_RES1OVF_REG                  RES1OVF;                      // Checker Overflow Result 1 Flag Register
    union   ADC_RES1OVFCLR_REG               RES1OVFCLR;                   // Checker Overflow Result 1 Flag Clear Register
    union   ADC_RES2OVF_REG                  RES2OVF;                      // Checker Overflow Result 2 Flag Register
    union   ADC_RES2OVFCLR_REG               RES2OVFCLR;                   // Checker Overflow Result 2 Flag Clear Register
    union   ADC_CHECKINTFLG_REG              CHECKINTFLG;                  // Checker Interrupt Flag Register
    uint8_t                                  rsvd1[2];                     // Reserved
    union   ADC_CHECKINTFLGCLR_REG           CHECKINTFLGCLR;               // Checker Interrupt Flag Clear Register
    uint8_t                                  rsvd2[2];                     // Reserved
    union   ADC_CHECKINTSEL1_REG             CHECKINTSEL1;                 // Checker Interrupt Source Select Register 1
    union   ADC_CHECKINTSEL2_REG             CHECKINTSEL2;                 // Checker Interrupt Source Select Register 2
    union   ADC_CHECKINTSEL3_REG             CHECKINTSEL3;                 // Checker Interrupt Source Select Register 3
    uint8_t                                  rsvd3[4];                     // Reserved
    union   ADC_CHECKEVT1SEL1_REG            CHECKEVT1SEL1;                // Checker X-Bar EVT1 Source Select Register 1
    union   ADC_CHECKEVT1SEL2_REG            CHECKEVT1SEL2;                // Checker X-Bar EVT1 Source Select Register 2
    union   ADC_CHECKEVT1SEL3_REG            CHECKEVT1SEL3;                // Checker X-Bar EVT1 Source Select Register 3
    uint8_t                                  rsvd4[4];                     // Reserved
    union   ADC_CHECKEVT2SEL1_REG            CHECKEVT2SEL1;                // Checker X-Bar EVT2 Source Select Register 1
    union   ADC_CHECKEVT2SEL2_REG            CHECKEVT2SEL2;                // Checker X-Bar EVT2 Source Select Register 2
    union   ADC_CHECKEVT2SEL3_REG            CHECKEVT2SEL3;                // Checker X-Bar EVT2 Source Select Register 3
    uint8_t                                  rsvd5[4];                     // Reserved
    union   ADC_CHECKEVT3SEL1_REG            CHECKEVT3SEL1;                // Checker X-Bar EVT3 Source Select Register 1
    union   ADC_CHECKEVT3SEL2_REG            CHECKEVT3SEL2;                // Checker X-Bar EVT3 Source Select Register 2
    union   ADC_CHECKEVT3SEL3_REG            CHECKEVT3SEL3;                // Checker X-Bar EVT3 Source Select Register 3
    uint8_t                                  rsvd6[4];                     // Reserved
    union   ADC_CHECKEVT4SEL1_REG            CHECKEVT4SEL1;                // Checker X-Bar EVT4 Source Select Register 1
    union   ADC_CHECKEVT4SEL2_REG            CHECKEVT4SEL2;                // Checker X-Bar EVT4 Source Select Register 2
    union   ADC_CHECKEVT4SEL3_REG            CHECKEVT4SEL3;                // Checker X-Bar EVT4 Source Select Register 3
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
