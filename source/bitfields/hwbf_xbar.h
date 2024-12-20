//###########################################################################
//
// FILE:    hwbf_xbar.h
//
// TITLE:   Definitions for the XBAR registers.
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

#ifndef HWBF_XBAR_H
#define HWBF_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// XBAR Individual Register Bit Definitions:

struct XBAR_XBARFLG1_BITS {             // bits description
    uint16_t CMPSS1_CTRIPL:1;           // 0 Input Flag for CMPSS1_CTRIPL Signal
    uint16_t CMPSS1_CTRIPH:1;           // 1 Input Flag for CMPSS1_CTRIPH Signal
    uint16_t CMPSS2_CTRIPL:1;           // 2 Input Flag for CMPSS2_CTRIPL Signal
    uint16_t CMPSS2_CTRIPH:1;           // 3 Input Flag for CMPSS2_CTRIPH Signal
    uint16_t CMPSS3_CTRIPL:1;           // 4 Input Flag for CMPSS3_CTRIPL Signal
    uint16_t CMPSS3_CTRIPH:1;           // 5 Input Flag for CMPSS3_CTRIPH Signal
    uint16_t CMPSS4_CTRIPL:1;           // 6 Input Flag for CMPSS4_CTRIPL Signal
    uint16_t CMPSS4_CTRIPH:1;           // 7 Input Flag for CMPSS4_CTRIPH Signal
    uint16_t CMPSS5_CTRIPL:1;           // 8 Input Flag for CMPSS5_CTRIPL Signal
    uint16_t CMPSS5_CTRIPH:1;           // 9 Input Flag for CMPSS5_CTRIPH Signal
    uint16_t CMPSS6_CTRIPL:1;           // 10 Input Flag for CMPSS6_CTRIPL Signal
    uint16_t CMPSS6_CTRIPH:1;           // 11 Input Flag for CMPSS6_CTRIPH Signal
    uint16_t CMPSS7_CTRIPL:1;           // 12 Input Flag for CMPSS7_CTRIPL Signal
    uint16_t CMPSS7_CTRIPH:1;           // 13 Input Flag for CMPSS7_CTRIPH Signal
    uint16_t CMPSS8_CTRIPL:1;           // 14 Input Flag for CMPSS8_CTRIPL Signal
    uint16_t CMPSS8_CTRIPH:1;           // 15 Input Flag for CMPSS8_CTRIPH Signal
    uint16_t CMPSS9_CTRIPH:1;           // 16 Input Flag for CMPSS9_CTRIPH Signal
    uint16_t CMPSS9_CTRIPL:1;           // 17 Input Flag for CMPSS9_CTRIPL Signal
    uint16_t CMPSS10_CTRIPH:1;          // 18 Input Flag for CMPSS10_CTRIPH Signal
    uint16_t CMPSS10_CTRIPL:1;          // 19 Input Flag for CMPSS10_CTRIPL Signal
    uint16_t CMPSS11_CTRIPH:1;          // 20 Input Flag for CMPSS11_CTRIPH Signal
    uint16_t CMPSS11_CTRIPL:1;          // 21 Input Flag for CMPSS11_CTRIPL Signal
    uint16_t CMPSS12_CTRIPH:1;          // 22 Input Flag for CMPSS12_CTRIPH Signal
    uint16_t CMPSS12_CTRIPL:1;          // 23 Input Flag for CMPSS12_CTRIPL Signal
    uint16_t rsvd1:1;                   // 24 Reserved
    uint16_t rsvd2:1;                   // 25 Reserved
    uint16_t rsvd3:1;                   // 26 Reserved
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t rsvd5:1;                   // 28 Reserved
    uint16_t rsvd6:1;                   // 29 Reserved
    uint16_t rsvd7:1;                   // 30 Reserved
    uint16_t rsvd8:1;                   // 31 Reserved
};

union XBAR_XBARFLG1_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG1_BITS  bit;
};

struct XBAR_XBARFLG2_BITS {             // bits description
    uint16_t CMPSS1_CTRIPOUTL:1;        // 0 Input Flag for CMPSS1_CTRIPOUTL Signal
    uint16_t CMPSS1_CTRIPOUTH:1;        // 1 Input Flag for CMPSS1_CTRIPOUTH Signal
    uint16_t CMPSS2_CTRIPOUTL:1;        // 2 Input Flag for CMPSS2_CTRIPOUTL Signal
    uint16_t CMPSS2_CTRIPOUTH:1;        // 3 Input Flag for CMPSS2_CTRIPOUTH Signal
    uint16_t CMPSS3_CTRIPOUTL:1;        // 4 Input Flag for CMPSS3_CTRIPOUTL Signal
    uint16_t CMPSS3_CTRIPOUTH:1;        // 5 Input Flag for CMPSS3_CTRIPOUTH Signal
    uint16_t CMPSS4_CTRIPOUTL:1;        // 6 Input Flag for CMPSS4_CTRIPOUTL Signal
    uint16_t CMPSS4_CTRIPOUTH:1;        // 7 Input Flag for CMPSS4_CTRIPOUTH Signal
    uint16_t CMPSS5_CTRIPOUTL:1;        // 8 Input Flag for CMPSS5_CTRIPOUTL Signal
    uint16_t CMPSS5_CTRIPOUTH:1;        // 9 Input Flag for CMPSS5_CTRIPOUTH Signal
    uint16_t CMPSS6_CTRIPOUTL:1;        // 10 Input Flag for CMPSS6_CTRIPOUTL Signal
    uint16_t CMPSS6_CTRIPOUTH:1;        // 11 Input Flag for CMPSS6_CTRIPOUTH Signal
    uint16_t CMPSS7_CTRIPOUTL:1;        // 12 Input Flag for CMPSS7_CTRIPOUTL Signal
    uint16_t CMPSS7_CTRIPOUTH:1;        // 13 Input Flag for CMPSS7_CTRIPOUTH Signal
    uint16_t CMPSS8_CTRIPOUTL:1;        // 14 Input Flag for CMPSS8_CTRIPOUTL Signal
    uint16_t CMPSS8_CTRIPOUTH:1;        // 15 Input Flag for CMPSS8_CTRIPOUTH Signal
    uint16_t CMPSS9_CTRIPOUTH:1;        // 16 Input Flag for CMPSS9_CTRIPOUTH Signal
    uint16_t CMPSS9_CTRIPOUTL:1;        // 17 Input Flag for CMPSS9_CTRIPOUTL Signal
    uint16_t CMPSS10_CTRIPOUTH:1;       // 18 Input Flag for CMPSS10_CTRIPOUTH Signal
    uint16_t CMPSS10_CTRIPOUTL:1;       // 19 Input Flag for CMPSS10_CTRIPOUTL Signal
    uint16_t CMPSS11_CTRIPOUTH:1;       // 20 Input Flag for CMPSS11_CTRIPOUTH Signal
    uint16_t CMPSS11_CTRIPOUTL:1;       // 21 Input Flag for CMPSS11_CTRIPOUTL Signal
    uint16_t CMPSS12_CTRIPOUTH:1;       // 22 Input Flag for CMPSS12_CTRIPOUTH Signal
    uint16_t CMPSS12_CTRIPOUTL:1;       // 23 Input Flag for CMPSS12_CTRIPOUTL Signal
    uint16_t rsvd1:1;                   // 24 Reserved
    uint16_t rsvd2:1;                   // 25 Reserved
    uint16_t rsvd3:1;                   // 26 Reserved
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t rsvd5:1;                   // 28 Reserved
    uint16_t rsvd6:1;                   // 29 Reserved
    uint16_t rsvd7:1;                   // 30 Reserved
    uint16_t rsvd8:1;                   // 31 Reserved
};

union XBAR_XBARFLG2_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG2_BITS  bit;
};

struct XBAR_XBARFLG3_BITS {             // bits description
    uint16_t SD1FLT1_COMPL:1;           // 0 Input Flag for SD1FLT1_COMPL Signal
    uint16_t SD1FLT1_COMPH:1;           // 1 Input Flag for SD1FLT1_COMPH Signal
    uint16_t SD1FLT2_COMPL:1;           // 2 Input Flag for SD1FLT2_COMPL Signal
    uint16_t SD1FLT2_COMPH:1;           // 3 Input Flag for SD1FLT2_COMPH Signal
    uint16_t SD1FLT3_COMPL:1;           // 4 Input Flag for SD1FLT3_COMPL Signal
    uint16_t SD1FLT3_COMPH:1;           // 5 Input Flag for SD1FLT3_COMPH Signal
    uint16_t SD1FLT4_COMPL:1;           // 6 Input Flag for SD1FLT4_COMPL Signal
    uint16_t SD1FLT4_COMPH:1;           // 7 Input Flag for SD1FLT4_COMPH Signal
    uint16_t SD2FLT1_COMPL:1;           // 8 Input Flag for SD2FLT1_COMPL Signal
    uint16_t SD2FLT1_COMPH:1;           // 9 Input Flag for SD2FLT1_COMPH Signal
    uint16_t SD2FLT2_COMPL:1;           // 10 Input Flag for SD2FLT2_COMPL Signal
    uint16_t SD2FLT2_COMPH:1;           // 11 Input Flag for SD2FLT2_COMPH Signal
    uint16_t SD2FLT3_COMPL:1;           // 12 Input Flag for SD2FLT3_COMPL Signal
    uint16_t SD2FLT3_COMPH:1;           // 13 Input Flag for SD2FLT3_COMPH Signal
    uint16_t SD2FLT4_COMPL:1;           // 14 Input Flag for SD2FLT4_COMPL Signal
    uint16_t SD2FLT4_COMPH:1;           // 15 Input Flag for SD2FLT4_COMPH Signal
    uint16_t SD3FLT1_COMPH:1;           // 16 Input Flag for SD3FLT1_COMPH Signal
    uint16_t SD3FLT1_COMPL:1;           // 17 Input Flag for SD3FLT1_COMPL Signal
    uint16_t SD3FLT2_COMPH:1;           // 18 Input Flag for SD3FLT2_COMPH Signal
    uint16_t SD3FLT2_COMPL:1;           // 19 Input Flag for SD3FLT2_COMPL Signal
    uint16_t SD3FLT3_COMPH:1;           // 20 Input Flag for SD3FLT3_COMPH Signal
    uint16_t SD3FLT3_COMPL:1;           // 21 Input Flag for SD3FLT3_COMPL Signal
    uint16_t SD3FLT4_COMPH:1;           // 22 Input Flag for SD3FLT4_COMPH Signal
    uint16_t SD3FLT4_COMPL:1;           // 23 Input Flag for SD3FLT4_COMPL Signal
    uint16_t SD4FLT1_COMPH:1;           // 24 Input Flag for SD4FLT1_COMPH Signal
    uint16_t SD4FLT1_COMPL:1;           // 25 Input Flag for SD4FLT1_COMPL Signal
    uint16_t SD4FLT2_COMPH:1;           // 26 Input Flag for SD4FLT2_COMPH Signal
    uint16_t SD4FLT2_COMPL:1;           // 27 Input Flag for SD4FLT2_COMPL Signal
    uint16_t SD4FLT3_COMPH:1;           // 28 Input Flag for SD4FLT3_COMPH Signal
    uint16_t SD4FLT3_COMPL:1;           // 29 Input Flag for SD4FLT3_COMPL Signal
    uint16_t SD4FLT4_COMPH:1;           // 30 Input Flag for SD4FLT4_COMPH Signal
    uint16_t SD4FLT4_COMPL:1;           // 31 Input Flag for SD4FLT4_COMPL Signal
};

union XBAR_XBARFLG3_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG3_BITS  bit;
};

struct XBAR_XBARFLG4_BITS {             // bits description
    uint16_t INPUT1:1;                  // 0 Input Flag for INPUT1 Signal
    uint16_t INPUT2:1;                  // 1 Input Flag for INPUT2 Signal
    uint16_t INPUT3:1;                  // 2 Input Flag for INPUT3 Signal
    uint16_t INPUT4:1;                  // 3 Input Flag for INPUT4 Signal
    uint16_t INPUT5:1;                  // 4 Input Flag for INPUT5 Signal
    uint16_t INPUT6:1;                  // 5 Input Flag for INPUT6 Signal
    uint16_t INPUT7:1;                  // 6 Input Flag for INPUT7 Signal
    uint16_t INPUT8:1;                  // 7 Input Flag for INPUT8 Signal
    uint16_t INPUT9:1;                  // 8 Input Flag for INPUT9 Signal
    uint16_t INPUT10:1;                 // 9 Input Flag for INPUT10 Signal
    uint16_t INPUT11:1;                 // 10 Input Flag for INPUT11 Signal
    uint16_t INPUT12:1;                 // 11 Input Flag for INPUT12 Signal
    uint16_t INPUT13:1;                 // 12 Input Flag for INPUT13 Signal
    uint16_t INPUT14:1;                 // 13 Input Flag for INPUT14 Signal
    uint16_t INPUT15:1;                 // 14 Input Flag for INPUT15 Signal
    uint16_t INPUT16:1;                 // 15 Input Flag for INPUT16 Signal
    uint16_t INPUT17:1;                 // 16 Input Flag for INPUT17 Signal
    uint16_t INPUT18:1;                 // 17 Input Flag for INPUT18 Signal
    uint16_t INPUT19:1;                 // 18 Input Flag for INPUT19 Signal
    uint16_t INPUT20:1;                 // 19 Input Flag for INPUT20 Signal
    uint16_t INPUT21:1;                 // 20 Input Flag for INPUT21 Signal
    uint16_t INPUT22:1;                 // 21 Input Flag for INPUT22 Signal
    uint16_t INPUT23:1;                 // 22 Input Flag for INPUT23 Signal
    uint16_t INPUT24:1;                 // 23 Input Flag for INPUT24 Signal
    uint16_t INPUT25:1;                 // 24 Input Flag for INPUT25 Signal
    uint16_t INPUT26:1;                 // 25 Input Flag for INPUT26 Signal
    uint16_t INPUT27:1;                 // 26 Input Flag for INPUT27 Signal
    uint16_t INPUT28:1;                 // 27 Input Flag for INPUT28 Signal
    uint16_t INPUT29:1;                 // 28 Input Flag for INPUT29 Signal
    uint16_t INPUT30:1;                 // 29 Input Flag for INPUT30 Signal
    uint16_t INPUT31:1;                 // 30 Input Flag for INPUT31 Signal
    uint16_t INPUT32:1;                 // 31 Input Flag for INPUT32 Signal
};

union XBAR_XBARFLG4_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG4_BITS  bit;
};

struct XBAR_XBARFLG5_BITS {             // bits description
    uint16_t ADCAEVT1:1;                // 0 Input Flag for ADCAEVT1  Signal
    uint16_t ADCAEVT2:1;                // 1 Input Flag for ADCAEVT2  Signal
    uint16_t ADCAEVT3:1;                // 2 Input Flag for ADCAEVT3  Signal
    uint16_t ADCAEVT4:1;                // 3 Input Flag for ADCAEVT4  Signal
    uint16_t ADCBEVT1:1;                // 4 Input Flag for ADCBEVT1  Signal
    uint16_t ADCBEVT2:1;                // 5 Input Flag for ADCBEVT2  Signal
    uint16_t ADCBEVT3:1;                // 6 Input Flag for ADCBEVT3  Signal
    uint16_t ADCBEVT4:1;                // 7 Input Flag for ADCBEVT4  Signal
    uint16_t ADCCEVT1:1;                // 8 Input Flag for ADCCEVT1  Signal
    uint16_t ADCCEVT2:1;                // 9 Input Flag for ADCCEVT2  Signal
    uint16_t ADCCEVT3:1;                // 10 Input Flag for ADCCEVT3  Signal
    uint16_t ADCCEVT4:1;                // 11 Input Flag for ADCCEVT4  Signal
    uint16_t ADCDEVT1:1;                // 12 Input Flag for ADCDEVT1  Signal
    uint16_t ADCDEVT2:1;                // 13 Input Flag for ADCDEVT2  Signal
    uint16_t ADCDEVT3:1;                // 14 Input Flag for ADCDEVT3  Signal
    uint16_t ADCDEVT4:1;                // 15 Input Flag for ADCDEVT4  Signal
    uint16_t ADCEEVT1:1;                // 16 Input Flag for ADCEEVT1  Signal
    uint16_t ADCEEVT2:1;                // 17 Input Flag for ADCEEVT2  Signal
    uint16_t ADCEEVT3:1;                // 18 Input Flag for ADCEEVT3  Signal
    uint16_t ADCEEVT4:1;                // 19 Input Flag for ADCEEVT4  Signal
    uint16_t CPU1_ADCCHECKEVT1:1;       // 20 Input Flag for CPU1_ADCCHECKEVT1  Signal
    uint16_t CPU1_ADCCHECKEVT2:1;       // 21 Input Flag for CPU1_ADCCHECKEVT2  Signal
    uint16_t CPU1_ADCCHECKEVT3:1;       // 22 Input Flag for CPU1_ADCCHECKEVT3  Signal
    uint16_t CPU1_ADCCHECKEVT4:1;       // 23 Input Flag for CPU1_ADCCHECKEVT4  Signal
    uint16_t CPU2_ADCCHECKEVT1:1;       // 24 Input Flag for CPU2_ADCCHECKEVT1  Signal
    uint16_t CPU2_ADCCHECKEVT2:1;       // 25 Input Flag for CPU2_ADCCHECKEVT2  Signal
    uint16_t CPU2_ADCCHECKEVT3:1;       // 26 Input Flag for CPU2_ADCCHECKEVT3  Signal
    uint16_t CPU2_ADCCHECKEVT4:1;       // 27 Input Flag for CPU2_ADCCHECKEVT4  Signal
    uint16_t CPU3_ADCCHECKEVT1:1;       // 28 Input Flag for CPU3_ADCCHECKEVT1  Signal
    uint16_t CPU3_ADCCHECKEVT2:1;       // 29 Input Flag for CPU3_ADCCHECKEVT2  Signal
    uint16_t CPU3_ADCCHECKEVT3:1;       // 30 Input Flag for CPU3_ADCCHECKEVT3  Signal
    uint16_t CPU3_ADCCHECKEVT4:1;       // 31 Input Flag for CPU3_ADCCHECKEVT4  Signal
};

union XBAR_XBARFLG5_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG5_BITS  bit;
};

struct XBAR_XBARFLG6_BITS {             // bits description
    uint16_t CLB1_OUT4:1;               // 0 Input Latch for CLB1_OUT4 Signal
    uint16_t CLB1_OUT5:1;               // 1 Input Latch for CLB1_OUT5 Signal
    uint16_t CLB2_OUT4:1;               // 2 Input Latch for CLB2_OUT4 Signal
    uint16_t CLB2_OUT5:1;               // 3 Input Latch for CLB2_OUT5 Signal
    uint16_t CLB3_OUT4:1;               // 4 Input Latch for CLB3_OUT4 Signal
    uint16_t CLB3_OUT5:1;               // 5 Input Latch for CLB3_OUT5 Signal
    uint16_t CLB4_OUT4:1;               // 6 Input Latch for CLB4_OUT4 Signal
    uint16_t CLB4_OUT5:1;               // 7 Input Latch for CLB4_OUT5 Signal
    uint16_t CLB5_OUT4:1;               // 8 Input Latch for CLB5_OUT4 Signal
    uint16_t CLB5_OUT5:1;               // 9 Input Latch for CLB5_OUT5 Signal
    uint16_t CLB6_OUT4:1;               // 10 Input Latch for CLB6_OUT4 Signal
    uint16_t CLB6_OUT5:1;               // 11 Input Latch for CLB6_OUT5 Signal
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t rsvd2:1;                   // 13 Reserved
    uint16_t rsvd3:1;                   // 14 Reserved
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t FSIA_RX_TRIG1:1;           // 16 Input Flag for FSIA_RX_TRIG1 Signal
    uint16_t FSIB_RX_TRIG1:1;           // 17 Input Flag for FSIB_RX_TRIG1 Signal
    uint16_t FSIC_RX_TRIG1:1;           // 18 Input Flag for FSIC_RX_TRIG1 Signal
    uint16_t FSID_RX_TRIG1:1;           // 19 Input Flag for FSID_RX_TRIG1 Signal
    uint16_t rsvd5:1;                   // 20 Reserved
    uint16_t rsvd6:1;                   // 21 Reserved
    uint16_t WADI1OUT0:1;               // 22 Input Flag for WADI1OUT0 Signal
    uint16_t WADI1OUT1:1;               // 23 Input Flag for WADI1OUT1 Signal
    uint16_t WADI1OUT2:1;               // 24 Input Flag for WADI1OUT2 Signal
    uint16_t WADI1OUT3:1;               // 25 Input Flag for WADI1OUT3 Signal
    uint16_t WADI1OUT4:1;               // 26 Input Flag for WADI1OUT4 Signal
    uint16_t WADI1OUT5:1;               // 27 Input Flag for WADI1OUT5 Signal
    uint16_t WADI1OUT6:1;               // 28 Input Flag for WADI1OUT6 Signal
    uint16_t WADI1OUT7:1;               // 29 Input Flag for WADI1OUT7 Signal
    uint16_t ECATSYNC0:1;               // 30 Input Latch for ECATSYNC0 Signal
    uint16_t ECATSYNC1:1;               // 31 Input Latch for ECATSYNC1 Signal
};

union XBAR_XBARFLG6_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG6_BITS  bit;
};

struct XBAR_XBARFLG7_BITS {             // bits description
    uint16_t ECAP1_OUT:1;               // 0 Input Flag for ECAP1_OUT Signal
    uint16_t ECAP2_OUT:1;               // 1 Input Flag for ECAP2_OUT Signal
    uint16_t ECAP3_OUT:1;               // 2 Input Flag for ECAP3_OUT Signal
    uint16_t ECAP4_OUT:1;               // 3 Input Flag for ECAP4_OUT Signal
    uint16_t ECAP5_OUT:1;               // 4 Input Flag for ECAP5_OUT Signal
    uint16_t ECAP6_OUT:1;               // 5 Input Flag for ECAP6_OUT Signal
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t ECAP1_TRIPOUT:1;           // 8 Input Flag for ECAP1_TRIPOUT Signal
    uint16_t ECAP2_TRIPOUT:1;           // 9 Input Flag for ECAP2_TRIPOUT Signal
    uint16_t ECAP3_TRIPOUT:1;           // 10 Input Flag for ECAP3_TRIPOUT Signal
    uint16_t ECAP4_TRIPOUT:1;           // 11 Input Flag for ECAP4_TRIPOUT Signal
    uint16_t ECAP5_TRIPOUT:1;           // 12 Input Flag for ECAP5_TRIPOUT Signal
    uint16_t ECAP6_TRIPOUT:1;           // 13 Input Flag for ECAP6_TRIPOUT Signal
    uint16_t rsvd3:1;                   // 14 Reserved
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t ADCSOCA:1;                 // 16 Input Flag for ADCSOCA Signal
    uint16_t ADCSOCB:1;                 // 17 Input Flag for ADCSOCB Signal
    uint16_t ESMGENEVT:1;               // 18 Input Flag for ESMGENEVT Signal
    uint16_t EXTSYNCOUT:1;              // 19 Input Flag for EXTSYNCOUT Signal
    uint16_t rsvd5:1;                   // 20 Reserved
    uint16_t rsvd6:1;                   // 21 Reserved
    uint16_t rsvd7:1;                   // 22 Reserved
    uint16_t rsvd8:1;                   // 23 Reserved
    uint16_t WADI2OUT0:1;               // 24 Input Flag for WADI2OUT0 Signal
    uint16_t WADI2OUT1:1;               // 25 Input Flag for WADI2OUT1 Signal
    uint16_t WADI2OUT2:1;               // 26 Input Flag for WADI2OUT2 Signal
    uint16_t WADI2OUT3:1;               // 27 Input Flag for WADI2OUT3 Signal
    uint16_t WADI2OUT4:1;               // 28 Input Flag for WADI2OUT4 Signal
    uint16_t WADI2OUT5:1;               // 29 Input Flag for WADI2OUT5 Signal
    uint16_t WADI2OUT6:1;               // 30 Input Flag for WADI2OUT6 Signal
    uint16_t WADI2OUT7:1;               // 31 Input Flag for WADI2OUT7 Signal
};

union XBAR_XBARFLG7_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG7_BITS  bit;
};

struct XBAR_XBARFLG8_BITS {             // bits description
    uint16_t EPWM1_TRIPOUT:1;           // 0 Input Flag for EPWM1_TRIPOUT Signal
    uint16_t EPWM2_TRIPOUT:1;           // 1 Input Flag for EPWM2_TRIPOUT Signal
    uint16_t EPWM3_TRIPOUT:1;           // 2 Input Flag for EPWM3_TRIPOUT Signal
    uint16_t EPWM4_TRIPOUT:1;           // 3 Input Flag for EPWM4_TRIPOUT Signal
    uint16_t EPWM5_TRIPOUT:1;           // 4 Input Flag for EPWM5_TRIPOUT Signal
    uint16_t EPWM6_TRIPOUT:1;           // 5 Input Flag for EPWM6_TRIPOUT Signal
    uint16_t EPWM7_TRIPOUT:1;           // 6 Input Flag for EPWM7_TRIPOUT Signal
    uint16_t EPWM8_TRIPOUT:1;           // 7 Input Flag for EPWM8_TRIPOUT Signal
    uint16_t EPWM9_TRIPOUT:1;           // 8 Input Flag for EPWM9_TRIPOUT Signal
    uint16_t EPWM10_TRIPOUT:1;          // 9 Input Flag for EPWM10_TRIPOUT Signal
    uint16_t EPWM11_TRIPOUT:1;          // 10 Input Flag for EPWM11_TRIPOUT Signal
    uint16_t EPWM12_TRIPOUT:1;          // 11 Input Flag for EPWM12_TRIPOUT Signal
    uint16_t EPWM13_TRIPOUT:1;          // 12 Input Flag for EPWM13_TRIPOUT Signal
    uint16_t EPWM14_TRIPOUT:1;          // 13 Input Flag for EPWM14_TRIPOUT Signal
    uint16_t EPWM15_TRIPOUT:1;          // 14 Input Flag for EPWM15_TRIPOUT Signal
    uint16_t EPWM16_TRIPOUT:1;          // 15 Input Flag for EPWM16_TRIPOUT Signal
    uint16_t EPWM17_TRIPOUT:1;          // 16 Input Flag for EPWM17_TRIPOUT Signal
    uint16_t EPWM18_TRIPOUT:1;          // 17 Input Flag for EPWM18_TRIPOUT Signal
    uint16_t rsvd1:1;                   // 18 Reserved
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t rsvd4:1;                   // 21 Reserved
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t rsvd7:1;                   // 24 Reserved
    uint16_t rsvd8:1;                   // 25 Reserved
    uint16_t rsvd9:1;                   // 26 Reserved
    uint16_t rsvd10:1;                  // 27 Reserved
    uint16_t rsvd11:1;                  // 28 Reserved
    uint16_t rsvd12:1;                  // 29 Reserved
    uint16_t rsvd13:1;                  // 30 Reserved
    uint16_t rsvd14:1;                  // 31 Reserved
};

union XBAR_XBARFLG8_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG8_BITS  bit;
};

struct XBAR_XBARFLG9_BITS {             // bits description
    uint16_t EPWM1_DEL_TRIP:1;          // 0 Input Flag for EPWM1_DEL_TRIP Signal
    uint16_t EPWM2_DEL_TRIP:1;          // 1 Input Flag for EPWM2_DEL_TRIP Signal
    uint16_t EPWM3_DEL_TRIP:1;          // 2 Input Flag for EPWM3_DEL_TRIP Signal
    uint16_t EPWM4_DEL_TRIP:1;          // 3 Input Flag for EPWM4_DEL_TRIP Signal
    uint16_t EPWM5_DEL_TRIP:1;          // 4 Input Flag for EPWM5_DEL_TRIP Signal
    uint16_t EPWM6_DEL_TRIP:1;          // 5 Input Flag for EPWM6_DEL_TRIP Signal
    uint16_t EPWM7_DEL_TRIP:1;          // 6 Input Flag for EPWM7_DEL_TRIP Signal
    uint16_t EPWM8_DEL_TRIP:1;          // 7 Input Flag for EPWM8_DEL_TRIP Signal
    uint16_t EPWM9_DEL_TRIP:1;          // 8 Input Flag for EPWM9_DEL_TRIP Signal
    uint16_t EPWM10_DEL_TRIP:1;         // 9 Input Flag for EPWM10_DEL_TRIP Signal
    uint16_t EPWM11_DEL_TRIP:1;         // 10 Input Flag for EPWM11_DEL_TRIP Signal
    uint16_t EPWM12_DEL_TRIP:1;         // 11 Input Flag for EPWM12_DEL_TRIP Signal
    uint16_t EPWM13_DEL_TRIP:1;         // 12 Input Flag for EPWM13_DEL_TRIP Signal
    uint16_t EPWM14_DEL_TRIP:1;         // 13 Input Flag for EPWM14_DEL_TRIP Signal
    uint16_t EPWM15_DEL_TRIP:1;         // 14 Input Flag for EPWM15_DEL_TRIP Signal
    uint16_t EPWM16_DEL_TRIP:1;         // 15 Input Flag for EPWM16_DEL_TRIP Signal
    uint16_t EPWM17_DEL_TRIP:1;         // 16 Input Flag for EPWM17_DEL_TRIP Signal
    uint16_t EPWM18_DEL_TRIP:1;         // 17 Input Flag for EPWM18_DEL_TRIP Signal
    uint16_t rsvd1:1;                   // 18 Reserved
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t rsvd4:1;                   // 21 Reserved
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t rsvd7:1;                   // 24 Reserved
    uint16_t rsvd8:1;                   // 25 Reserved
    uint16_t rsvd9:1;                   // 26 Reserved
    uint16_t rsvd10:1;                  // 27 Reserved
    uint16_t rsvd11:1;                  // 28 Reserved
    uint16_t rsvd12:1;                  // 29 Reserved
    uint16_t rsvd13:1;                  // 30 Reserved
    uint16_t rsvd14:1;                  // 31 Reserved
};

union XBAR_XBARFLG9_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG9_BITS  bit;
};

struct XBAR_XBARFLG10_BITS {            // bits description
    uint16_t EPWM1_DEL_ACTIVE:1;        // 0 Input Flag for EPWM1_DEL_ACTIVE Signal
    uint16_t EPWM2_DEL_ACTIVE:1;        // 1 Input Flag for EPWM2_DEL_ACTIVE Signal
    uint16_t EPWM3_DEL_ACTIVE:1;        // 2 Input Flag for EPWM3_DEL_ACTIVE Signal
    uint16_t EPWM4_DEL_ACTIVE:1;        // 3 Input Flag for EPWM4_DEL_ACTIVE Signal
    uint16_t EPWM5_DEL_ACTIVE:1;        // 4 Input Flag for EPWM5_DEL_ACTIVE Signal
    uint16_t EPWM6_DEL_ACTIVE:1;        // 5 Input Flag for EPWM6_DEL_ACTIVE Signal
    uint16_t EPWM7_DEL_ACTIVE:1;        // 6 Input Flag for EPWM7_DEL_ACTIVE Signal
    uint16_t EPWM8_DEL_ACTIVE:1;        // 7 Input Flag for EPWM8_DEL_ACTIVE Signal
    uint16_t EPWM9_DEL_ACTIVE:1;        // 8 Input Flag for EPWM9_DEL_ACTIVE Signal
    uint16_t EPWM10_DEL_ACTIVE:1;       // 9 Input Flag for EPWM10_DEL_ACTIVE Signal
    uint16_t EPWM11_DEL_ACTIVE:1;       // 10 Input Flag for EPWM11_DEL_ACTIVE Signal
    uint16_t EPWM12_DEL_ACTIVE:1;       // 11 Input Flag for EPWM12_DEL_ACTIVE Signal
    uint16_t EPWM13_DEL_ACTIVE:1;       // 12 Input Flag for EPWM13_DEL_ACTIVE Signal
    uint16_t EPWM14_DEL_ACTIVE:1;       // 13 Input Flag for EPWM14_DEL_ACTIVE Signal
    uint16_t EPWM15_DEL_ACTIVE:1;       // 14 Input Flag for EPWM15_DEL_ACTIVE Signal
    uint16_t EPWM16_DEL_ACTIVE:1;       // 15 Input Flag for EPWM16_DEL_ACTIVE Signal
    uint16_t EPWM17_DEL_ACTIVE:1;       // 16 Input Flag for EPWM17_DEL_ACTIVE Signal
    uint16_t EPWM18_DEL_ACTIVE:1;       // 17 Input Flag for EPWM18_DEL_ACTIVE Signal
    uint16_t rsvd1:1;                   // 18 Reserved
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t rsvd4:1;                   // 21 Reserved
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t rsvd7:1;                   // 24 Reserved
    uint16_t rsvd8:1;                   // 25 Reserved
    uint16_t rsvd9:1;                   // 26 Reserved
    uint16_t rsvd10:1;                  // 27 Reserved
    uint16_t rsvd11:1;                  // 28 Reserved
    uint16_t rsvd12:1;                  // 29 Reserved
    uint16_t rsvd13:1;                  // 30 Reserved
    uint16_t rsvd14:1;                  // 31 Reserved
};

union XBAR_XBARFLG10_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG10_BITS  bit;
};

struct XBAR_XBARFLG11_BITS {            // bits description
    uint16_t EPWM1_A0_sclk:1;           // 0 Input Flag for EPWM1_A0_sclk Signal
    uint16_t EPWM1_B0_sclk:1;           // 1 Input Flag for EPWM1_B0_sclk Signal
    uint16_t EPWM2_A0_sclk:1;           // 2 Input Flag for EPWM2_A0_sclk Signal
    uint16_t EPWM2_B0_sclk:1;           // 3 Input Flag for EPWM2_B0_sclk Signal
    uint16_t EPWM3_A0_sclk:1;           // 4 Input Flag for EPWM3_A0_sclk Signal
    uint16_t EPWM3_B0_sclk:1;           // 5 Input Flag for EPWM3_B0_sclk Signal
    uint16_t EPWM4_A0_sclk:1;           // 6 Input Flag for EPWM4_A0_sclk Signal
    uint16_t EPWM4_B0_sclk:1;           // 7 Input Flag for EPWM4_B0_sclk Signal
    uint16_t EPWM5_A0_sclk:1;           // 8 Input Flag for EPWM5_A0_sclk Signal
    uint16_t EPWM5_B0_sclk:1;           // 9 Input Flag for EPWM5_B0_sclk Signal
    uint16_t EPWM6_A0_sclk:1;           // 10 Input Flag for EPWM6_A0_sclk Signal
    uint16_t EPWM6_B0_sclk:1;           // 11 Input Flag for EPWM6_B0_sclk Signal
    uint16_t EPWM7_A0_sclk:1;           // 12 Input Flag for EPWM7_A0_sclk Signal
    uint16_t EPWM7_B0_sclk:1;           // 13 Input Flag for EPWM7_B0_sclk Signal
    uint16_t EPWM8_A0_sclk:1;           // 14 Input Flag for EPWM8_A0_sclk Signal
    uint16_t EPWM8_B0_sclk:1;           // 15 Input Flag for EPWM8_B0_sclk Signal
    uint16_t EPWM9_A0_sclk:1;           // 16 Input Flag for EPWM9_A0_sclk Signal
    uint16_t EPWM9_B0_sclk:1;           // 17 Input Flag for EPWM9_B0_sclk Signal
    uint16_t EPWM10_A0_sclk:1;          // 18 Input Flag for EPWM10_A0_sclk Signal
    uint16_t EPWM10_B0_sclk:1;          // 19 Input Flag for EPWM10_B0_sclk Signal
    uint16_t EPWM11_A0_sclk:1;          // 20 Input Flag for EPWM11_A0_sclk Signal
    uint16_t EPWM11_B0_sclk:1;          // 21 Input Flag for EPWM11_B0_sclk Signal
    uint16_t EPWM12_A0_sclk:1;          // 22 Input Flag for EPWM12_A0_sclk Signal
    uint16_t EPWM12_B0_sclk:1;          // 23 Input Flag for EPWM12_B0_sclk Signal
    uint16_t EPWM13_A0_sclk:1;          // 24 Input Flag for EPWM13_A0_sclk Signal
    uint16_t EPWM13_B0_sclk:1;          // 25 Input Flag for EPWM13_B0_sclk Signal
    uint16_t EPWM14_A0_sclk:1;          // 26 Input Flag for EPWM14_A0_sclk Signal
    uint16_t EPWM14_B0_sclk:1;          // 27 Input Flag for EPWM14_B0_sclk Signal
    uint16_t EPWM15_A0_sclk:1;          // 28 Input Flag for EPWM15_A0_sclk Signal
    uint16_t EPWM15_B0_sclk:1;          // 29 Input Flag for EPWM15_B0_sclk Signal
    uint16_t EPWM16_A0_sclk:1;          // 30 Input Flag for EPWM16_A0_sclk Signal
    uint16_t EPWM16_B0_sclk:1;          // 31 Input Flag for EPWM16_B0_sclk Signal
};

union XBAR_XBARFLG11_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG11_BITS  bit;
};

struct XBAR_XBARFLG12_BITS {            // bits description
    uint16_t EPWM17_A0_sclk:1;          // 0 Input Flag for EPWM17_A0_sclk Signal
    uint16_t EPWM17_B0_sclk:1;          // 1 Input Flag for EPWM17_B0_sclk Signal
    uint16_t EPWM18_A0_sclk:1;          // 2 Input Flag for EPWM18_A0_sclk Signal
    uint16_t EPWM18_B0_sclk:1;          // 3 Input Flag for EPWM18_B0_sclk Signal
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t rsvd13:1;                  // 16 Reserved
    uint16_t rsvd14:1;                  // 17 Reserved
    uint16_t rsvd15:1;                  // 18 Reserved
    uint16_t rsvd16:1;                  // 19 Reserved
    uint16_t rsvd17:1;                  // 20 Reserved
    uint16_t rsvd18:1;                  // 21 Reserved
    uint16_t rsvd19:1;                  // 22 Reserved
    uint16_t rsvd20:1;                  // 23 Reserved
    uint16_t rsvd21:1;                  // 24 Reserved
    uint16_t rsvd22:1;                  // 25 Reserved
    uint16_t rsvd23:1;                  // 26 Reserved
    uint16_t rsvd24:1;                  // 27 Reserved
    uint16_t rsvd25:1;                  // 28 Reserved
    uint16_t rsvd26:1;                  // 29 Reserved
    uint16_t rsvd27:1;                  // 30 Reserved
    uint16_t rsvd28:1;                  // 31 Reserved
};

union XBAR_XBARFLG12_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG12_BITS  bit;
};

struct XBAR_XBARFLG13_BITS {            // bits description
    uint16_t MDL1_OUTA:1;               // 0 Input Flag for MDL1_OUTA Signal
    uint16_t MDL1_OUTB:1;               // 1 Input Flag for MDL1_OUTB Signal
    uint16_t MDL2_OUTA:1;               // 2 Input Flag for MDL2_OUTA Signal
    uint16_t MDL2_OUTB:1;               // 3 Input Flag for MDL2_OUTB Signal
    uint16_t MDL3_OUTA:1;               // 4 Input Flag for MDL3_OUTA Signal
    uint16_t MDL3_OUTB:1;               // 5 Input Flag for MDL3_OUTB Signal
    uint16_t MDL4_OUTA:1;               // 6 Input Flag for MDL4_OUTA Signal
    uint16_t MDL4_OUTB:1;               // 7 Input Flag for MDL4_OUTB Signal
    uint16_t MDL5_OUTA:1;               // 8 Input Flag for MDL5_OUTA Signal
    uint16_t MDL5_OUTB:1;               // 9 Input Flag for MDL5_OUTB Signal
    uint16_t MDL6_OUTA:1;               // 10 Input Flag for MDL6_OUTA Signal
    uint16_t MDL6_OUTB:1;               // 11 Input Flag for MDL6_OUTB Signal
    uint16_t MDL7_OUTA:1;               // 12 Input Flag for MDL7_OUTA Signal
    uint16_t MDL7_OUTB:1;               // 13 Input Flag for MDL7_OUTB Signal
    uint16_t MDL8_OUTA:1;               // 14 Input Flag for MDL8_OUTA Signal
    uint16_t MDL8_OUTB:1;               // 15 Input Flag for MDL8_OUTB Signal
    uint16_t MDL9_OUTA:1;               // 16 Input Flag for MDL9_OUTA Signal
    uint16_t MDL9_OUTB:1;               // 17 Input Flag for MDL9_OUTB Signal
    uint16_t MDL10_OUTA:1;              // 18 Input Flag for MDL10_OUTA Signal
    uint16_t MDL10_OUTB:1;              // 19 Input Flag for MDL10_OUTB Signal
    uint16_t MDL11_OUTA:1;              // 20 Input Flag for MDL11_OUTA Signal
    uint16_t MDL11_OUTB:1;              // 21 Input Flag for MDL11_OUTB Signal
    uint16_t MDL12_OUTA:1;              // 22 Input Flag for MDL12_OUTA Signal
    uint16_t MDL12_OUTB:1;              // 23 Input Flag for MDL12_OUTB Signal
    uint16_t MDL13_OUTA:1;              // 24 Input Flag for MDL13_OUTA Signal
    uint16_t MDL13_OUTB:1;              // 25 Input Flag for MDL13_OUTB Signal
    uint16_t MDL14_OUTA:1;              // 26 Input Flag for MDL14_OUTA Signal
    uint16_t MDL14_OUTB:1;              // 27 Input Flag for MDL14_OUTB Signal
    uint16_t MDL15_OUTA:1;              // 28 Input Flag for MDL15_OUTA Signal
    uint16_t MDL15_OUTB:1;              // 29 Input Flag for MDL15_OUTB Signal
    uint16_t MDL16_OUTA:1;              // 30 Input Flag for MDL16_OUTA Signal
    uint16_t MDL16_OUTB:1;              // 31 Input Flag for MDL16_OUTB Signal
};

union XBAR_XBARFLG13_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG13_BITS  bit;
};

struct XBAR_XBARFLG14_BITS {            // bits description
    uint16_t MDL17_OUTA:1;              // 0 Input Flag for MDL17_OUTA Signal
    uint16_t MDL17_OUTB:1;              // 1 Input Flag for MDL17_OUTB Signal
    uint16_t MDL18_OUTA:1;              // 2 Input Flag for MDL18_OUTA Signal
    uint16_t MDL18_OUTB:1;              // 3 Input Flag for MDL18_OUTB Signal
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t rsvd13:1;                  // 16 Reserved
    uint16_t rsvd14:1;                  // 17 Reserved
    uint16_t rsvd15:1;                  // 18 Reserved
    uint16_t rsvd16:1;                  // 19 Reserved
    uint16_t rsvd17:1;                  // 20 Reserved
    uint16_t rsvd18:1;                  // 21 Reserved
    uint16_t rsvd19:1;                  // 22 Reserved
    uint16_t rsvd20:1;                  // 23 Reserved
    uint16_t rsvd21:1;                  // 24 Reserved
    uint16_t rsvd22:1;                  // 25 Reserved
    uint16_t rsvd23:1;                  // 26 Reserved
    uint16_t rsvd24:1;                  // 27 Reserved
    uint16_t rsvd25:1;                  // 28 Reserved
    uint16_t rsvd26:1;                  // 29 Reserved
    uint16_t rsvd27:1;                  // 30 Reserved
    uint16_t rsvd28:1;                  // 31 Reserved
};

union XBAR_XBARFLG14_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG14_BITS  bit;
};

struct XBAR_XBARFLG15_BITS {            // bits description
    uint16_t CLB1_OUT0:1;               // 0 Input Flag for CLB1_OUT0 Signal
    uint16_t CLB1_OUT1:1;               // 1 Input Flag for CLB1_OUT1 Signal
    uint16_t CLB1_OUT2:1;               // 2 Input Flag for CLB1_OUT2 Signal
    uint16_t CLB1_OUT3:1;               // 3 Input Flag for CLB1_OUT3 Signal
    uint16_t CLB1_OUT6:1;               // 4 Input Flag for CLB1_OUT6 Signal
    uint16_t CLB1_OUT7:1;               // 5 Input Flag for CLB1_OUT7 Signal
    uint16_t CLB2_OUT0:1;               // 6 Input Flag for CLB2_OUT0 Signal
    uint16_t CLB2_OUT1:1;               // 7 Input Flag for CLB2_OUT1 Signal
    uint16_t CLB2_OUT2:1;               // 8 Input Flag for CLB2_OUT2 Signal
    uint16_t CLB2_OUT3:1;               // 9 Input Flag for CLB2_OUT3 Signal
    uint16_t CLB2_OUT6:1;               // 10 Input Flag for CLB2_OUT6 Signal
    uint16_t CLB2_OUT7:1;               // 11 Input Flag for CLB2_OUT7 Signal
    uint16_t CLB3_OUT0:1;               // 12 Input Flag for CLB3_OUT0 Signal
    uint16_t CLB3_OUT1:1;               // 13 Input Flag for CLB3_OUT1 Signal
    uint16_t CLB3_OUT2:1;               // 14 Input Flag for CLB3_OUT2 Signal
    uint16_t CLB3_OUT3:1;               // 15 Input Flag for CLB3_OUT3 Signal
    uint16_t CLB3_OUT6:1;               // 16 Input Flag for CLB3_OUT6 Signal
    uint16_t CLB3_OUT7:1;               // 17 Input Flag for CLB3_OUT7 Signal
    uint16_t CLB4_OUT0:1;               // 18 Input Flag for CLB4_OUT0 Signal
    uint16_t CLB4_OUT1:1;               // 19 Input Flag for CLB4_OUT1 Signal
    uint16_t CLB4_OUT2:1;               // 20 Input Flag for CLB4_OUT2 Signal
    uint16_t CLB4_OUT3:1;               // 21 Input Flag for CLB4_OUT3 Signal
    uint16_t CLB4_OUT6:1;               // 22 Input Flag for CLB4_OUT6 Signal
    uint16_t CLB4_OUT7:1;               // 23 Input Flag for CLB4_OUT7 Signal
    uint16_t CLB5_OUT0:1;               // 24 Input Flag for CLB5_OUT0 Signal
    uint16_t CLB5_OUT1:1;               // 25 Input Flag for CLB5_OUT1 Signal
    uint16_t CLB5_OUT2:1;               // 26 Input Flag for CLB5_OUT2 Signal
    uint16_t CLB5_OUT3:1;               // 27 Input Flag for CLB5_OUT3 Signal
    uint16_t CLB5_OUT6:1;               // 28 Input Flag for CLB5_OUT6 Signal
    uint16_t CLB5_OUT7:1;               // 29 Input Flag for CLB5_OUT7 Signal
    uint16_t CLB6_OUT0:1;               // 30 Input Flag for CLB6_OUT0 Signal
    uint16_t CLB6_OUT1:1;               // 31 Input Flag for CLB6_OUT1 Signal
};

union XBAR_XBARFLG15_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG15_BITS  bit;
};

struct XBAR_XBARFLG16_BITS {            // bits description
    uint16_t CLB6_OUT2:1;               // 0 Input Flag for CLB6_OUT2 Signal
    uint16_t CLB6_OUT3:1;               // 1 Input Flag for CLB6_OUT3 Signal
    uint16_t CLB6_OUT6:1;               // 2 Input Flag for CLB6_OUT6 Signal
    uint16_t CLB6_OUT7:1;               // 3 Input Flag for CLB6_OUT7 Signal
    uint16_t ADCA_EXTMUXSEL0:1;         // 4 Input Flag for ADCA_EXTMUXSEL0 Signal
    uint16_t ADCA_EXTMUXSEL1:1;         // 5 Input Flag for ADCA_EXTMUXSEL1 Signal
    uint16_t ADCA_EXTMUXSEL2:1;         // 6 Input Flag for ADCA_EXTMUXSEL2 Signal
    uint16_t ADCA_EXTMUXSEL3:1;         // 7 Input Flag for ADCA_EXTMUXSEL3 Signal
    uint16_t ADCB_EXTMUXSEL0:1;         // 8 Input Flag for ADCB_EXTMUXSEL0 Signal
    uint16_t ADCB_EXTMUXSEL1:1;         // 9 Input Flag for ADCB_EXTMUXSEL1 Signal
    uint16_t ADCB_EXTMUXSEL2:1;         // 10 Input Flag for ADCB_EXTMUXSEL2 Signal
    uint16_t ADCB_EXTMUXSEL3:1;         // 11 Input Flag for ADCB_EXTMUXSEL3 Signal
    uint16_t ADCC_EXTMUXSEL0:1;         // 12 Input Flag for ADCC_EXTMUXSEL0 Signal
    uint16_t ADCC_EXTMUXSEL1:1;         // 13 Input Flag for ADCC_EXTMUXSEL1 Signal
    uint16_t ADCC_EXTMUXSEL2:1;         // 14 Input Flag for ADCC_EXTMUXSEL2 Signal
    uint16_t ADCC_EXTMUXSEL3:1;         // 15 Input Flag for ADCC_EXTMUXSEL3 Signal
    uint16_t ADCD_EXTMUXSEL0:1;         // 16 Input Flag for ADCD_EXTMUXSEL0 Signal
    uint16_t ADCD_EXTMUXSEL1:1;         // 17 Input Flag for ADCD_EXTMUXSEL1 Signal
    uint16_t ADCD_EXTMUXSEL2:1;         // 18 Input Flag for ADCD_EXTMUXSEL2 Signal
    uint16_t ADCD_EXTMUXSEL3:1;         // 19 Input Flag for ADCD_EXTMUXSEL3 Signal
    uint16_t ADCE_EXTMUXSEL0:1;         // 20 Input Flag for ADCE_EXTMUXSEL0 Signal
    uint16_t ADCE_EXTMUXSEL1:1;         // 21 Input Flag for ADCE_EXTMUXSEL1 Signal
    uint16_t ADCE_EXTMUXSEL2:1;         // 22 Input Flag for ADCE_EXTMUXSEL2 Signal
    uint16_t ADCE_EXTMUXSEL3:1;         // 23 Input Flag for ADCE_EXTMUXSEL3 Signal
    uint16_t rsvd1:1;                   // 24 Reserved
    uint16_t rsvd2:1;                   // 25 Reserved
    uint16_t rsvd3:1;                   // 26 Reserved
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EPG1_EPGOUT0:1;            // 28 Input Flag for EPG1_EPGOUT0 Signal
    uint16_t EPG1_EPGOUT1:1;            // 29 Input Flag for EPG1_EPGOUT1 Signal
    uint16_t EPG1_EPGOUT2:1;            // 30 Input Flag for EPG1_EPGOUT2 Signal
    uint16_t EPG1_EPGOUT3:1;            // 31 Input Flag for EPG1_EPGOUT3 Signal
};

union XBAR_XBARFLG16_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG16_BITS  bit;
};

struct XBAR_XBARFLG17_BITS {            // bits description
    uint16_t MCANA_FEVT0:1;             // 0 Input Flag for MCANA_FEVT0 Signal
    uint16_t MCANA_FEVT1:1;             // 1 Input Flag for MCANA_FEVT1 Signal
    uint16_t MCANA_FEVT2:1;             // 2 Input Flag for MCANA_FEVT2 Signal
    uint16_t MCANB_FEVT0:1;             // 3 Input Flag for MCANB_FEVT0 Signal
    uint16_t MCANB_FEVT1:1;             // 4 Input Flag for MCANB_FEVT1 Signal
    uint16_t MCANB_FEVT2:1;             // 5 Input Flag for MCANB_FEVT2 Signal
    uint16_t MCANC_FEVT0:1;             // 6 Input Flag for MCANC_FEVT0 Signal
    uint16_t MCANC_FEVT1:1;             // 7 Input Flag for MCANC_FEVT1 Signal
    uint16_t MCANC_FEVT2:1;             // 8 Input Flag for MCANC_FEVT2 Signal
    uint16_t MCAND_FEVT0:1;             // 9 Input Flag for MCAND_FEVT0 Signal
    uint16_t MCAND_FEVT1:1;             // 10 Input Flag for MCAND_FEVT1 Signal
    uint16_t MCAND_FEVT2:1;             // 11 Input Flag for MCAND_FEVT2 Signal
    uint16_t MCANE_FEVT0:1;             // 12 Input Flag for MCANE_FEVT0 Signal
    uint16_t MCANE_FEVT1:1;             // 13 Input Flag for MCANE_FEVT1 Signal
    uint16_t MCANE_FEVT2:1;             // 14 Input Flag for MCANE_FEVT2 Signal
    uint16_t MCANF_FEVT0:1;             // 15 Input Flag for MCANF_FEVT0 Signal
    uint16_t MCANF_FEVT1:1;             // 16 Input Flag for MCANF_FEVT1 Signal
    uint16_t MCANF_FEVT2:1;             // 17 Input Flag for MCANF_FEVT2 Signal
    uint16_t rsvd1:14;                  // 31:18 Reserved
};

union XBAR_XBARFLG17_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG17_BITS  bit;
};

struct XBAR_XBARFLG18_BITS {            // bits description
    uint16_t FSIRXA_TRIG_2:1;           // 0 Input Flag for FSIRXA_TRIG_2 Signal
    uint16_t FSIRXA_TRIG_3:1;           // 1 Input Flag for FSIRXA_TRIG_3 Signal
    uint16_t FSIRXB_TRIG_2:1;           // 2 Input Flag for FSIRXB_TRIG_2 Signal
    uint16_t FSIRXB_TRIG_3:1;           // 3 Input Flag for FSIRXB_TRIG_3 Signal
    uint16_t FSIRXC_TRIG_2:1;           // 4 Input Flag for FSIRXC_TRIG_2 Signal
    uint16_t FSIRXC_TRIG_3:1;           // 5 Input Flag for FSIRXC_TRIG_3 Signal
    uint16_t FSIRXD_TRIG_2:1;           // 6 Input Flag for FSIRXD_TRIG_2 Signal
    uint16_t FSIRXD_TRIG_3:1;           // 7 Input Flag for FSIRXD_TRIG_3 Signal
    uint16_t CPU1ERADEVT8:1;            // 8 Input Flag for CPU1ERADEVT8 Signal
    uint16_t CPU1ERADEVT9:1;            // 9 Input Flag for CPU1ERADEVT9 Signal
    uint16_t CPU1ERADEVT10:1;           // 10 Input Flag for CPU1ERADEVT10 Signal
    uint16_t CPU1ERADEVT11:1;           // 11 Input Flag for CPU1ERADEVT11 Signal
    uint16_t CPU2ERADEVT8:1;            // 12 Input Flag for CPU2ERADEVT8 Signal
    uint16_t CPU2ERADEVT9:1;            // 13 Input Flag for CPU2ERADEVT9 Signal
    uint16_t CPU2ERADEVT10:1;           // 14 Input Flag for CPU2ERADEVT10 Signal
    uint16_t CPU2ERADEVT11:1;           // 15 Input Flag for CPU2ERADEVT11 Signal
    uint16_t CPU3ERADEVT8:1;            // 16 Input Flag for CPU3ERADEVT8 Signal
    uint16_t CPU3ERADEVT9:1;            // 17 Input Flag for CPU3ERADEVT9 Signal
    uint16_t CPU3ERADEVT10:1;           // 18 Input Flag for CPU3ERADEVT10 Signal
    uint16_t CPU3ERADEVT11:1;           // 19 Input Flag for CPU3ERADEVT11 Signal
    uint16_t rsvd1:12;                  // 31:20 Reserved
};

union XBAR_XBARFLG18_REG {
    uint32_t  all;
    struct  XBAR_XBARFLG18_BITS  bit;
};

struct XBAR_XBARCLR1_BITS {             // bits description
    uint16_t CMPSS1_CTRIPL:1;           // 0 Input Flag Clear for CMPSS1_CTRIPL Signal
    uint16_t CMPSS1_CTRIPH:1;           // 1 Input Flag Clear for CMPSS1_CTRIPH Signal
    uint16_t CMPSS2_CTRIPL:1;           // 2 Input Flag Clear for CMPSS2_CTRIPL Signal
    uint16_t CMPSS2_CTRIPH:1;           // 3 Input Flag Clear for CMPSS2_CTRIPH Signal
    uint16_t CMPSS3_CTRIPL:1;           // 4 Input Flag Clear for CMPSS3_CTRIPL Signal
    uint16_t CMPSS3_CTRIPH:1;           // 5 Input Flag Clear for CMPSS3_CTRIPH Signal
    uint16_t CMPSS4_CTRIPL:1;           // 6 Input Flag Clear for CMPSS4_CTRIPL Signal
    uint16_t CMPSS4_CTRIPH:1;           // 7 Input Flag Clear for CMPSS4_CTRIPH Signal
    uint16_t CMPSS5_CTRIPL:1;           // 8 Input Flag Clear for CMPSS5_CTRIPL Signal
    uint16_t CMPSS5_CTRIPH:1;           // 9 Input Flag Clear for CMPSS5_CTRIPH Signal
    uint16_t CMPSS6_CTRIPL:1;           // 10 Input Flag Clear for CMPSS6_CTRIPL Signal
    uint16_t CMPSS6_CTRIPH:1;           // 11 Input Flag Clear for CMPSS6_CTRIPH Signal
    uint16_t CMPSS7_CTRIPL:1;           // 12 Input Flag Clear for CMPSS7_CTRIPL Signal
    uint16_t CMPSS7_CTRIPH:1;           // 13 Input Flag Clear for CMPSS7_CTRIPH Signal
    uint16_t CMPSS8_CTRIPL:1;           // 14 Input Flag Clear for CMPSS8_CTRIPL Signal
    uint16_t CMPSS8_CTRIPH:1;           // 15 Input Flag Clear for CMPSS8_CTRIPH Signal
    uint16_t CMPSS9_CTRIPH:1;           // 16 Input Flag Clear for CMPSS9_CTRIPH Signal
    uint16_t CMPSS9_CTRIPL:1;           // 17 Input Flag Clear for CMPSS9_CTRIPL Signal
    uint16_t CMPSS10_CTRIPH:1;          // 18 Input Flag Clear for CMPSS10_CTRIPH Signal
    uint16_t CMPSS10_CTRIPL:1;          // 19 Input Flag Clear for CMPSS10_CTRIPL Signal
    uint16_t CMPSS11_CTRIPH:1;          // 20 Input Flag Clear for CMPSS11_CTRIPH Signal
    uint16_t CMPSS11_CTRIPL:1;          // 21 Input Flag Clear for CMPSS11_CTRIPL Signal
    uint16_t CMPSS12_CTRIPH:1;          // 22 Input Flag Clear for CMPSS12_CTRIPH Signal
    uint16_t CMPSS12_CTRIPL:1;          // 23 Input Flag Clear for CMPSS12_CTRIPL Signal
    uint16_t rsvd1:1;                   // 24 Reserved
    uint16_t rsvd2:1;                   // 25 Reserved
    uint16_t rsvd3:1;                   // 26 Reserved
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t rsvd5:1;                   // 28 Reserved
    uint16_t rsvd6:1;                   // 29 Reserved
    uint16_t rsvd7:1;                   // 30 Reserved
    uint16_t rsvd8:1;                   // 31 Reserved
};

union XBAR_XBARCLR1_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR1_BITS  bit;
};

struct XBAR_XBARCLR2_BITS {             // bits description
    uint16_t CMPSS1_CTRIPOUTL:1;        // 0 Input Flag clear for CMPSS1_CTRIPOUTL Signal
    uint16_t CMPSS1_CTRIPOUTH:1;        // 1 Input Flag clear for CMPSS1_CTRIPOUTH Signal
    uint16_t CMPSS2_CTRIPOUTL:1;        // 2 Input Flag clear for CMPSS2_CTRIPOUTL Signal
    uint16_t CMPSS2_CTRIPOUTH:1;        // 3 Input Flag clear for CMPSS2_CTRIPOUTH Signal
    uint16_t CMPSS3_CTRIPOUTL:1;        // 4 Input Flag clear for CMPSS3_CTRIPOUTL Signal
    uint16_t CMPSS3_CTRIPOUTH:1;        // 5 Input Flag clear for CMPSS3_CTRIPOUTH Signal
    uint16_t CMPSS4_CTRIPOUTL:1;        // 6 Input Flag clear for CMPSS4_CTRIPOUTL Signal
    uint16_t CMPSS4_CTRIPOUTH:1;        // 7 Input Flag clear for CMPSS4_CTRIPOUTH Signal
    uint16_t CMPSS5_CTRIPOUTL:1;        // 8 Input Flag clear for CMPSS5_CTRIPOUTL Signal
    uint16_t CMPSS5_CTRIPOUTH:1;        // 9 Input Flag clear for CMPSS5_CTRIPOUTH Signal
    uint16_t CMPSS6_CTRIPOUTL:1;        // 10 Input Flag clear for CMPSS6_CTRIPOUTL Signal
    uint16_t CMPSS6_CTRIPOUTH:1;        // 11 Input Flag clear for CMPSS6_CTRIPOUTH Signal
    uint16_t CMPSS7_CTRIPOUTL:1;        // 12 Input Flag clear for CMPSS7_CTRIPOUTL Signal
    uint16_t CMPSS7_CTRIPOUTH:1;        // 13 Input Flag clear for CMPSS7_CTRIPOUTH Signal
    uint16_t CMPSS8_CTRIPOUTL:1;        // 14 Input Flag clear for CMPSS8_CTRIPOUTL Signal
    uint16_t CMPSS8_CTRIPOUTH:1;        // 15 Input Flag clear for CMPSS8_CTRIPOUTH Signal
    uint16_t CMPSS9_CTRIPOUTH:1;        // 16 Input Flag clear for CMPSS9_CTRIPOUTH Signal
    uint16_t CMPSS9_CTRIPOUTL:1;        // 17 Input Flag clear for CMPSS9_CTRIPOUTL Signal
    uint16_t CMPSS10_CTRIPOUTH:1;       // 18 Input Flag clear for CMPSS10_CTRIPOUTH Signal
    uint16_t CMPSS10_CTRIPOUTL:1;       // 19 Input Flag clear for CMPSS10_CTRIPOUTL Signal
    uint16_t CMPSS11_CTRIPOUTH:1;       // 20 Input Flag clear for CMPSS11_CTRIPOUTH Signal
    uint16_t CMPSS11_CTRIPOUTL:1;       // 21 Input Flag clear for CMPSS11_CTRIPOUTL Signal
    uint16_t CMPSS12_CTRIPOUTH:1;       // 22 Input Flag clear for CMPSS12_CTRIPOUTH Signal
    uint16_t CMPSS12_CTRIPOUTL:1;       // 23 Input Flag clear for CMPSS12_CTRIPOUTL Signal
    uint16_t rsvd1:1;                   // 24 Reserved
    uint16_t rsvd2:1;                   // 25 Reserved
    uint16_t rsvd3:1;                   // 26 Reserved
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t rsvd5:1;                   // 28 Reserved
    uint16_t rsvd6:1;                   // 29 Reserved
    uint16_t rsvd7:1;                   // 30 Reserved
    uint16_t rsvd8:1;                   // 31 Reserved
};

union XBAR_XBARCLR2_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR2_BITS  bit;
};

struct XBAR_XBARCLR3_BITS {             // bits description
    uint16_t SD1FLT1_COMPL:1;           // 0 Input Flag Clear for SD1FLT1_COMPL Signal
    uint16_t SD1FLT1_COMPH:1;           // 1 Input Flag Clear for SD1FLT1_COMPH Signal
    uint16_t SD1FLT2_COMPL:1;           // 2 Input Flag Clear for SD1FLT2_COMPL Signal
    uint16_t SD1FLT2_COMPH:1;           // 3 Input Flag Clear for SD1FLT2_COMPH Signal
    uint16_t SD1FLT3_COMPL:1;           // 4 Input Flag Clear for SD1FLT3_COMPL Signal
    uint16_t SD1FLT3_COMPH:1;           // 5 Input Flag Clear for SD1FLT3_COMPH Signal
    uint16_t SD1FLT4_COMPL:1;           // 6 Input Flag Clear for SD1FLT4_COMPL Signal
    uint16_t SD1FLT4_COMPH:1;           // 7 Input Flag Clear for SD1FLT4_COMPH Signal
    uint16_t SD2FLT1_COMPL:1;           // 8 Input Flag Clear for SD2FLT1_COMPL Signal
    uint16_t SD2FLT1_COMPH:1;           // 9 Input Flag Clear for SD2FLT1_COMPH Signal
    uint16_t SD2FLT2_COMPL:1;           // 10 Input Flag Clear for SD2FLT2_COMPL Signal
    uint16_t SD2FLT2_COMPH:1;           // 11 Input Flag Clear for SD2FLT2_COMPH Signal
    uint16_t SD2FLT3_COMPL:1;           // 12 Input Flag Clear for SD2FLT3_COMPL Signal
    uint16_t SD2FLT3_COMPH:1;           // 13 Input Flag Clear for SD2FLT3_COMPH Signal
    uint16_t SD2FLT4_COMPL:1;           // 14 Input Flag Clear for SD2FLT4_COMPL Signal
    uint16_t SD2FLT4_COMPH:1;           // 15 Input Flag Clear for SD2FLT4_COMPH Signal
    uint16_t SD3FLT1_COMPH:1;           // 16 Input Flag Clear for SD3FLT1_COMPH Signal
    uint16_t SD3FLT1_COMPL:1;           // 17 Input Flag Clear for SD3FLT1_COMPL Signal
    uint16_t SD3FLT2_COMPH:1;           // 18 Input Flag Clear for SD3FLT2_COMPH Signal
    uint16_t SD3FLT2_COMPL:1;           // 19 Input Flag Clear for SD3FLT2_COMPL Signal
    uint16_t SD3FLT3_COMPH:1;           // 20 Input Flag Clear for SD3FLT3_COMPH Signal
    uint16_t SD3FLT3_COMPL:1;           // 21 Input Flag Clear for SD3FLT3_COMPL Signal
    uint16_t SD3FLT4_COMPH:1;           // 22 Input Flag Clear for SD3FLT4_COMPH Signal
    uint16_t SD3FLT4_COMPL:1;           // 23 Input Flag Clear for SD3FLT4_COMPL Signal
    uint16_t SD4FLT1_COMPH:1;           // 24 Input Flag Clear for SD4FLT1_COMPH Signal
    uint16_t SD4FLT1_COMPL:1;           // 25 Input Flag Clear for SD4FLT1_COMPL Signal
    uint16_t SD4FLT2_COMPH:1;           // 26 Input Flag Clear for SD4FLT2_COMPH Signal
    uint16_t SD4FLT2_COMPL:1;           // 27 Input Flag Clear for SD4FLT2_COMPL Signal
    uint16_t SD4FLT3_COMPH:1;           // 28 Input Flag Clear for SD4FLT3_COMPH Signal
    uint16_t SD4FLT3_COMPL:1;           // 29 Input Flag Clear for SD4FLT3_COMPL Signal
    uint16_t SD4FLT4_COMPH:1;           // 30 Input Flag Clear for SD4FLT4_COMPH Signal
    uint16_t SD4FLT4_COMPL:1;           // 31 Input Flag Clear for SD4FLT4_COMPL Signal
};

union XBAR_XBARCLR3_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR3_BITS  bit;
};

struct XBAR_XBARCLR4_BITS {             // bits description
    uint16_t INPUT1:1;                  // 0 Input Flag Clear for INPUT1 Signal
    uint16_t INPUT2:1;                  // 1 Input Flag Clear for INPUT2 Signal
    uint16_t INPUT3:1;                  // 2 Input Flag Clear for INPUT3 Signal
    uint16_t INPUT4:1;                  // 3 Input Flag Clear for INPUT4 Signal
    uint16_t INPUT5:1;                  // 4 Input Flag Clear for INPUT5 Signal
    uint16_t INPUT6:1;                  // 5 Input Flag Clear for INPUT6 Signal
    uint16_t INPUT7:1;                  // 6 Input Flag Clear for INPUT7 Signal
    uint16_t INPUT8:1;                  // 7 Input Flag Clear for INPUT8 Signal
    uint16_t INPUT9:1;                  // 8 Input Flag Clear for INPUT9 Signal
    uint16_t INPUT10:1;                 // 9 Input Flag Clear for INPUT10 Signal
    uint16_t INPUT11:1;                 // 10 Input Flag Clear for INPUT11 Signal
    uint16_t INPUT12:1;                 // 11 Input Flag Clear for INPUT12 Signal
    uint16_t INPUT13:1;                 // 12 Input Flag Clear for INPUT13 Signal
    uint16_t INPUT14:1;                 // 13 Input Flag Clear for INPUT14 Signal
    uint16_t INPUT15:1;                 // 14 Input Flag Clear for INPUT15 Signal
    uint16_t INPUT16:1;                 // 15 Input Flag Clear for INPUT16 Signal
    uint16_t INPUT17:1;                 // 16 Input Flag Clear for INPUT17 Signal
    uint16_t INPUT18:1;                 // 17 Input Flag Clear for INPUT18 Signal
    uint16_t INPUT19:1;                 // 18 Input Flag Clear for INPUT19 Signal
    uint16_t INPUT20:1;                 // 19 Input Flag Clear for INPUT20 Signal
    uint16_t INPUT21:1;                 // 20 Input Flag Clear for INPUT21 Signal
    uint16_t INPUT22:1;                 // 21 Input Flag Clear for INPUT22 Signal
    uint16_t INPUT23:1;                 // 22 Input Flag Clear for INPUT23 Signal
    uint16_t INPUT24:1;                 // 23 Input Flag Clear for INPUT24 Signal
    uint16_t INPUT25:1;                 // 24 Input Flag Clear for INPUT25 Signal
    uint16_t INPUT26:1;                 // 25 Input Flag Clear for INPUT26 Signal
    uint16_t INPUT27:1;                 // 26 Input Flag Clear for INPUT27 Signal
    uint16_t INPUT28:1;                 // 27 Input Flag Clear for INPUT28 Signal
    uint16_t INPUT29:1;                 // 28 Input Flag Clear for INPUT29 Signal
    uint16_t INPUT30:1;                 // 29 Input Flag Clear for INPUT30 Signal
    uint16_t INPUT31:1;                 // 30 Input Flag Clear for INPUT31 Signal
    uint16_t INPUT32:1;                 // 31 Input Flag Clear for INPUT32 Signal
};

union XBAR_XBARCLR4_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR4_BITS  bit;
};

struct XBAR_XBARCLR5_BITS {             // bits description
    uint16_t ADCAEVT1:1;                // 0 Input Flag Clear for ADCAEVT1 Signal
    uint16_t ADCAEVT2:1;                // 1 Input Flag Clear for ADCAEVT2 Signal
    uint16_t ADCAEVT3:1;                // 2 Input Flag Clear for ADCAEVT3 Signal
    uint16_t ADCAEVT4:1;                // 3 Input Flag Clear for ADCAEVT4 Signal
    uint16_t ADCBEVT1:1;                // 4 Input Flag Clear for ADCBEVT1 Signal
    uint16_t ADCBEVT2:1;                // 5 Input Flag Clear for ADCBEVT2 Signal
    uint16_t ADCBEVT3:1;                // 6 Input Flag Clear for ADCBEVT3 Signal
    uint16_t ADCBEVT4:1;                // 7 Input Flag Clear for ADCBEVT4 Signal
    uint16_t ADCCEVT1:1;                // 8 Input Flag Clear for ADCCEVT1 Signal
    uint16_t ADCCEVT2:1;                // 9 Input Flag Clear for ADCCEVT2 Signal
    uint16_t ADCCEVT3:1;                // 10 Input Flag Clear for ADCCEVT3 Signal
    uint16_t ADCCEVT4:1;                // 11 Input Flag Clear for ADCCEVT4 Signal
    uint16_t ADCDEVT1:1;                // 12 Input Flag Clear for ADCDEVT1 Signal
    uint16_t ADCDEVT2:1;                // 13 Input Flag Clear for ADCDEVT2 Signal
    uint16_t ADCDEVT3:1;                // 14 Input Flag Clear for ADCDEVT3 Signal
    uint16_t ADCDEVT4:1;                // 15 Input Flag Clear for ADCDEVT4 Signal
    uint16_t ADCEEVT1:1;                // 16 Input Flag Clear for ADCEEVT1 Signal
    uint16_t ADCEEVT2:1;                // 17 Input Flag Clear for ADCEEVT2 Signal
    uint16_t ADCEEVT3:1;                // 18 Input Flag Clear for ADCEEVT3 Signal
    uint16_t ADCEEVT4:1;                // 19 Input Flag Clear for ADCEEVT4 Signal
    uint16_t CPU1_ADCCHECKEVT1:1;       // 20 Input Flag Clear for CPU1_ADCCHECKEVT1 Signal
    uint16_t CPU1_ADCCHECKEVT2:1;       // 21 Input Flag Clear for CPU1_ADCCHECKEVT2 Signal
    uint16_t CPU1_ADCCHECKEVT3:1;       // 22 Input Flag Clear for CPU1_ADCCHECKEVT3 Signal
    uint16_t CPU1_ADCCHECKEVT4:1;       // 23 Input Flag Clear for CPU1_ADCCHECKEVT4 Signal
    uint16_t CPU2_ADCCHECKEVT1:1;       // 24 Input Flag Clear for CPU2_ADCCHECKEVT1 Signal
    uint16_t CPU2_ADCCHECKEVT2:1;       // 25 Input Flag Clear for CPU2_ADCCHECKEVT2 Signal
    uint16_t CPU2_ADCCHECKEVT3:1;       // 26 Input Flag Clear for CPU2_ADCCHECKEVT3 Signal
    uint16_t CPU2_ADCCHECKEVT4:1;       // 27 Input Flag Clear for CPU2_ADCCHECKEVT4 Signal
    uint16_t CPU3_ADCCHECKEVT1:1;       // 28 Input Flag Clear for CPU3_ADCCHECKEVT1 Signal
    uint16_t CPU3_ADCCHECKEVT2:1;       // 29 Input Flag Clear for CPU3_ADCCHECKEVT2 Signal
    uint16_t CPU3_ADCCHECKEVT3:1;       // 30 Input Flag Clear for CPU3_ADCCHECKEVT3 Signal
    uint16_t CPU3_ADCCHECKEVT4:1;       // 31 Input Flag Clear for CPU3_ADCCHECKEVT4 Signal
};

union XBAR_XBARCLR5_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR5_BITS  bit;
};

struct XBAR_XBARCLR6_BITS {             // bits description
    uint16_t CLB1_OUT4:1;               // 0 Input Flag Clear for CLB1_OUT4 Signal
    uint16_t CLB1_OUT5:1;               // 1 Input Flag Clear for CLB1_OUT5 Signal
    uint16_t CLB2_OUT4:1;               // 2 Input Flag Clear for CLB2_OUT4 Signal
    uint16_t CLB2_OUT5:1;               // 3 Input Flag Clear for CLB2_OUT5 Signal
    uint16_t CLB3_OUT4:1;               // 4 Input Flag Clear for CLB3_OUT4 Signal
    uint16_t CLB3_OUT5:1;               // 5 Input Flag Clear for CLB3_OUT5 Signal
    uint16_t CLB4_OUT4:1;               // 6 Input Flag Clear for CLB4_OUT4 Signal
    uint16_t CLB4_OUT5:1;               // 7 Input Flag Clear for CLB4_OUT5 Signal
    uint16_t CLB5_OUT4:1;               // 8 Input Flag Clear for CLB5_OUT4 Signal
    uint16_t CLB5_OUT5:1;               // 9 Input Flag Clear for CLB5_OUT5 Signal
    uint16_t CLB6_OUT4:1;               // 10 Input Flag Clear for CLB6_OUT4 Signal
    uint16_t CLB6_OUT5:1;               // 11 Input Flag Clear for CLB6_OUT5 Signal
    uint16_t rsvd1:1;                   // 12 Reserved
    uint16_t rsvd2:1;                   // 13 Reserved
    uint16_t rsvd3:1;                   // 14 Reserved
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t FSIA_RX_TRIG1:1;           // 16 Input Flag Clear for FSIA_RX_TRIG1 Signal
    uint16_t FSIB_RX_TRIG1:1;           // 17 Input Flag Clear for FSIB_RX_TRIG1 Signal
    uint16_t FSIC_RX_TRIG1:1;           // 18 Input Flag Clear for FSIC_RX_TRIG1 Signal
    uint16_t FSID_RX_TRIG1:1;           // 19 Input Flag Clear for FSID_RX_TRIG1 Signal
    uint16_t rsvd5:1;                   // 20 Reserved
    uint16_t rsvd6:1;                   // 21 Reserved
    uint16_t WADI1OUT0:1;               // 22 Input Flag Clear for WADI1OUT0 Signal
    uint16_t WADI1OUT1:1;               // 23 Input Flag Clear for WADI1OUT1 Signal
    uint16_t WADI1OUT2:1;               // 24 Input Flag Clear for WADI1OUT2 Signal
    uint16_t WADI1OUT3:1;               // 25 Input Flag Clear for WADI1OUT3 Signal
    uint16_t WADI1OUT4:1;               // 26 Input Flag Clear for WADI1OUT4 Signal
    uint16_t WADI1OUT5:1;               // 27 Input Flag Clear for WADI1OUT5 Signal
    uint16_t WADI1OUT6:1;               // 28 Input Flag Clear for WADI1OUT6 Signal
    uint16_t WADI1OUT7:1;               // 29 Input Flag Clear for WADI1OUT7 Signal
    uint16_t ECATSYNC0:1;               // 30 Input Flag Clear for ECATSYNC0 Signal
    uint16_t ECATSYNC1:1;               // 31 Input Flag Clear for ECATSYNC1 Signal
};

union XBAR_XBARCLR6_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR6_BITS  bit;
};

struct XBAR_XBARCLR7_BITS {             // bits description
    uint16_t ECAP1_OUT:1;               // 0 Input Flag Clear for ECAP1_OUT Signal
    uint16_t ECAP2_OUT:1;               // 1 Input Flag Clear for ECAP2_OUT Signal
    uint16_t ECAP3_OUT:1;               // 2 Input Flag Clear for ECAP3_OUT Signal
    uint16_t ECAP4_OUT:1;               // 3 Input Flag Clear for ECAP4_OUT Signal
    uint16_t ECAP5_OUT:1;               // 4 Input Flag Clear for ECAP5_OUT Signal
    uint16_t ECAP6_OUT:1;               // 5 Input Flag Clear for ECAP6_OUT Signal
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t rsvd2:1;                   // 7 Reserved
    uint16_t ECAP1_TRIPOUT:1;           // 8 Input Flag Clear for ECAP1_TRIPOUT Signal
    uint16_t ECAP2_TRIPOUT:1;           // 9 Input Flag Clear for ECAP2_TRIPOUT Signal
    uint16_t ECAP3_TRIPOUT:1;           // 10 Input Flag Clear for ECAP3_TRIPOUT Signal
    uint16_t ECAP4_TRIPOUT:1;           // 11 Input Flag Clear for ECAP4_TRIPOUT Signal
    uint16_t ECAP5_TRIPOUT:1;           // 12 Input Flag Clear for ECAP5_TRIPOUT Signal
    uint16_t ECAP6_TRIPOUT:1;           // 13 Input Flag Clear for ECAP6_TRIPOUT Signal
    uint16_t rsvd3:1;                   // 14 Reserved
    uint16_t rsvd4:1;                   // 15 Reserved
    uint16_t ADCSOCA:1;                 // 16 Input Flag Clear for ADCSOCA Signal
    uint16_t ADCSOCB:1;                 // 17 Input Flag Clear for ADCSOCB Signal
    uint16_t ESMGENEVT:1;               // 18 Input Flag Clear for ESMGENEVT Signal
    uint16_t EXTSYNCOUT:1;              // 19 Input Flag Clear for EXTSYNCOUT Signal
    uint16_t rsvd5:1;                   // 20 Reserved
    uint16_t rsvd6:1;                   // 21 Reserved
    uint16_t rsvd7:1;                   // 22 Reserved
    uint16_t rsvd8:1;                   // 23 Reserved
    uint16_t WADI2OUT0:1;               // 24 Input Flag Clear for WADI2OUT0 Signal
    uint16_t WADI2OUT1:1;               // 25 Input Flag Clear for WADI2OUT1 Signal
    uint16_t WADI2OUT2:1;               // 26 Input Flag Clear for WADI2OUT2 Signal
    uint16_t WADI2OUT3:1;               // 27 Input Flag Clear for WADI2OUT3 Signal
    uint16_t WADI2OUT4:1;               // 28 Input Flag Clear for WADI2OUT4 Signal
    uint16_t WADI2OUT5:1;               // 29 Input Flag Clear for WADI2OUT5 Signal
    uint16_t WADI2OUT6:1;               // 30 Input Flag Clear for WADI2OUT6 Signal
    uint16_t WADI2OUT7:1;               // 31 Input Flag Clear for WADI2OUT7 Signal
};

union XBAR_XBARCLR7_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR7_BITS  bit;
};

struct XBAR_XBARCLR8_BITS {             // bits description
    uint16_t EPWM1_TRIPOUT:1;           // 0 Input Flag clear for EPWM1_TRIPOUT Signal
    uint16_t EPWM2_TRIPOUT:1;           // 1 Input Flag clear for EPWM2_TRIPOUT Signal
    uint16_t EPWM3_TRIPOUT:1;           // 2 Input Flag clear for EPWM3_TRIPOUT Signal
    uint16_t EPWM4_TRIPOUT:1;           // 3 Input Flag clear for EPWM4_TRIPOUT Signal
    uint16_t EPWM5_TRIPOUT:1;           // 4 Input Flag clear for EPWM5_TRIPOUT Signal
    uint16_t EPWM6_TRIPOUT:1;           // 5 Input Flag clear for EPWM6_TRIPOUT Signal
    uint16_t EPWM7_TRIPOUT:1;           // 6 Input Flag clear for EPWM7_TRIPOUT Signal
    uint16_t EPWM8_TRIPOUT:1;           // 7 Input Flag clear for EPWM8_TRIPOUT Signal
    uint16_t EPWM9_TRIPOUT:1;           // 8 Input Flag clear for EPWM9_TRIPOUT Signal
    uint16_t EPWM10_TRIPOUT:1;          // 9 Input Flag clear for EPWM10_TRIPOUT Signal
    uint16_t EPWM11_TRIPOUT:1;          // 10 Input Flag clear for EPWM11_TRIPOUT Signal
    uint16_t EPWM12_TRIPOUT:1;          // 11 Input Flag clear for EPWM12_TRIPOUT Signal
    uint16_t EPWM13_TRIPOUT:1;          // 12 Input Flag clear for EPWM13_TRIPOUT Signal
    uint16_t EPWM14_TRIPOUT:1;          // 13 Input Flag clear for EPWM14_TRIPOUT Signal
    uint16_t EPWM15_TRIPOUT:1;          // 14 Input Flag clear for EPWM15_TRIPOUT Signal
    uint16_t EPWM16_TRIPOUT:1;          // 15 Input Flag clear for EPWM16_TRIPOUT Signal
    uint16_t EPWM17_TRIPOUT:1;          // 16 Input Flag clear for EPWM17_TRIPOUT Signal
    uint16_t EPWM18_TRIPOUT:1;          // 17 Input Flag clear for EPWM18_TRIPOUT Signal
    uint16_t rsvd1:1;                   // 18 Reserved
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t rsvd4:1;                   // 21 Reserved
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t rsvd7:1;                   // 24 Reserved
    uint16_t rsvd8:1;                   // 25 Reserved
    uint16_t rsvd9:1;                   // 26 Reserved
    uint16_t rsvd10:1;                  // 27 Reserved
    uint16_t rsvd11:1;                  // 28 Reserved
    uint16_t rsvd12:1;                  // 29 Reserved
    uint16_t rsvd13:1;                  // 30 Reserved
    uint16_t rsvd14:1;                  // 31 Reserved
};

union XBAR_XBARCLR8_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR8_BITS  bit;
};

struct XBAR_XBARCLR9_BITS {             // bits description
    uint16_t EPWM1_DEL_TRIP:1;          // 0 Input Flag clear for EPWM1_DEL_TRIP Signal
    uint16_t EPWM2_DEL_TRIP:1;          // 1 Input Flag clear for EPWM2_DEL_TRIP Signal
    uint16_t EPWM3_DEL_TRIP:1;          // 2 Input Flag clear for EPWM3_DEL_TRIP Signal
    uint16_t EPWM4_DEL_TRIP:1;          // 3 Input Flag clear for EPWM4_DEL_TRIP Signal
    uint16_t EPWM5_DEL_TRIP:1;          // 4 Input Flag clear for EPWM5_DEL_TRIP Signal
    uint16_t EPWM6_DEL_TRIP:1;          // 5 Input Flag clear for EPWM6_DEL_TRIP Signal
    uint16_t EPWM7_DEL_TRIP:1;          // 6 Input Flag clear for EPWM7_DEL_TRIP Signal
    uint16_t EPWM8_DEL_TRIP:1;          // 7 Input Flag clear for EPWM8_DEL_TRIP Signal
    uint16_t EPWM9_DEL_TRIP:1;          // 8 Input Flag clear for EPWM9_DEL_TRIP Signal
    uint16_t EPWM10_DEL_TRIP:1;         // 9 Input Flag clear for EPWM10_DEL_TRIP Signal
    uint16_t EPWM11_DEL_TRIP:1;         // 10 Input Flag clear for EPWM11_DEL_TRIP Signal
    uint16_t EPWM12_DEL_TRIP:1;         // 11 Input Flag clear for EPWM12_DEL_TRIP Signal
    uint16_t EPWM13_DEL_TRIP:1;         // 12 Input Flag clear for EPWM13_DEL_TRIP Signal
    uint16_t EPWM14_DEL_TRIP:1;         // 13 Input Flag clear for EPWM14_DEL_TRIP Signal
    uint16_t EPWM15_DEL_TRIP:1;         // 14 Input Flag clear for EPWM15_DEL_TRIP Signal
    uint16_t EPWM16_DEL_TRIP:1;         // 15 Input Flag clear for EPWM16_DEL_TRIP Signal
    uint16_t EPWM17_DEL_TRIP:1;         // 16 Input Flag clear for EPWM17_DEL_TRIP Signal
    uint16_t EPWM18_DEL_TRIP:1;         // 17 Input Flag clear for EPWM18_DEL_TRIP Signal
    uint16_t rsvd1:1;                   // 18 Reserved
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t rsvd4:1;                   // 21 Reserved
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t rsvd7:1;                   // 24 Reserved
    uint16_t rsvd8:1;                   // 25 Reserved
    uint16_t rsvd9:1;                   // 26 Reserved
    uint16_t rsvd10:1;                  // 27 Reserved
    uint16_t rsvd11:1;                  // 28 Reserved
    uint16_t rsvd12:1;                  // 29 Reserved
    uint16_t rsvd13:1;                  // 30 Reserved
    uint16_t rsvd14:1;                  // 31 Reserved
};

union XBAR_XBARCLR9_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR9_BITS  bit;
};

struct XBAR_XBARCLR10_BITS {            // bits description
    uint16_t EPWM1_DEL_ACTIVE:1;        // 0 Input Flag clear for EPWM1_DEL_ACTIVE Signal
    uint16_t EPWM2_DEL_ACTIVE:1;        // 1 Input Flag clear for EPWM2_DEL_ACTIVE Signal
    uint16_t EPWM3_DEL_ACTIVE:1;        // 2 Input Flag clear for EPWM3_DEL_ACTIVE Signal
    uint16_t EPWM4_DEL_ACTIVE:1;        // 3 Input Flag clear for EPWM4_DEL_ACTIVE Signal
    uint16_t EPWM5_DEL_ACTIVE:1;        // 4 Input Flag clear for EPWM5_DEL_ACTIVE Signal
    uint16_t EPWM6_DEL_ACTIVE:1;        // 5 Input Flag clear for EPWM6_DEL_ACTIVE Signal
    uint16_t EPWM7_DEL_ACTIVE:1;        // 6 Input Flag clear for EPWM7_DEL_ACTIVE Signal
    uint16_t EPWM8_DEL_ACTIVE:1;        // 7 Input Flag clear for EPWM8_DEL_ACTIVE Signal
    uint16_t EPWM9_DEL_ACTIVE:1;        // 8 Input Flag clear for EPWM9_DEL_ACTIVE Signal
    uint16_t EPWM10_DEL_ACTIVE:1;       // 9 Input Flag clear for EPWM10_DEL_ACTIVE Signal
    uint16_t EPWM11_DEL_ACTIVE:1;       // 10 Input Flag clear for EPWM11_DEL_ACTIVE Signal
    uint16_t EPWM12_DEL_ACTIVE:1;       // 11 Input Flag clear for EPWM12_DEL_ACTIVE Signal
    uint16_t EPWM13_DEL_ACTIVE:1;       // 12 Input Flag clear for EPWM13_DEL_ACTIVE Signal
    uint16_t EPWM14_DEL_ACTIVE:1;       // 13 Input Flag clear for EPWM14_DEL_ACTIVE Signal
    uint16_t EPWM15_DEL_ACTIVE:1;       // 14 Input Flag clear for EPWM15_DEL_ACTIVE Signal
    uint16_t EPWM16_DEL_ACTIVE:1;       // 15 Input Flag clear for EPWM16_DEL_ACTIVE Signal
    uint16_t EPWM17_DEL_ACTIVE:1;       // 16 Input Flag clear for EPWM17_DEL_ACTIVE Signal
    uint16_t EPWM18_DEL_ACTIVE:1;       // 17 Input Flag clear for EPWM18_DEL_ACTIVE Signal
    uint16_t rsvd1:1;                   // 18 Reserved
    uint16_t rsvd2:1;                   // 19 Reserved
    uint16_t rsvd3:1;                   // 20 Reserved
    uint16_t rsvd4:1;                   // 21 Reserved
    uint16_t rsvd5:1;                   // 22 Reserved
    uint16_t rsvd6:1;                   // 23 Reserved
    uint16_t rsvd7:1;                   // 24 Reserved
    uint16_t rsvd8:1;                   // 25 Reserved
    uint16_t rsvd9:1;                   // 26 Reserved
    uint16_t rsvd10:1;                  // 27 Reserved
    uint16_t rsvd11:1;                  // 28 Reserved
    uint16_t rsvd12:1;                  // 29 Reserved
    uint16_t rsvd13:1;                  // 30 Reserved
    uint16_t rsvd14:1;                  // 31 Reserved
};

union XBAR_XBARCLR10_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR10_BITS  bit;
};

struct XBAR_XBARCLR11_BITS {            // bits description
    uint16_t EPWM1_A0_sclk:1;           // 0 Input Flag clear for EPWM1_A0_sclk Signal
    uint16_t EPWM1_B0_sclk:1;           // 1 Input Flag clear for EPWM1_B0_sclk Signal
    uint16_t EPWM2_A0_sclk:1;           // 2 Input Flag clear for EPWM2_A0_sclk Signal
    uint16_t EPWM2_B0_sclk:1;           // 3 Input Flag clear for EPWM2_B0_sclk Signal
    uint16_t EPWM3_A0_sclk:1;           // 4 Input Flag clear for EPWM3_A0_sclk Signal
    uint16_t EPWM3_B0_sclk:1;           // 5 Input Flag clear for EPWM3_B0_sclk Signal
    uint16_t EPWM4_A0_sclk:1;           // 6 Input Flag clear for EPWM4_A0_sclk Signal
    uint16_t EPWM4_B0_sclk:1;           // 7 Input Flag clear for EPWM4_B0_sclk Signal
    uint16_t EPWM5_A0_sclk:1;           // 8 Input Flag clear for EPWM5_A0_sclk Signal
    uint16_t EPWM5_B0_sclk:1;           // 9 Input Flag clear for EPWM5_B0_sclk Signal
    uint16_t EPWM6_A0_sclk:1;           // 10 Input Flag clear for EPWM6_A0_sclk Signal
    uint16_t EPWM6_B0_sclk:1;           // 11 Input Flag clear for EPWM6_B0_sclk Signal
    uint16_t EPWM7_A0_sclk:1;           // 12 Input Flag clear for EPWM7_A0_sclk Signal
    uint16_t EPWM7_B0_sclk:1;           // 13 Input Flag clear for EPWM7_B0_sclk Signal
    uint16_t EPWM8_A0_sclk:1;           // 14 Input Flag clear for EPWM8_A0_sclk Signal
    uint16_t EPWM8_B0_sclk:1;           // 15 Input Flag clear for EPWM8_B0_sclk Signal
    uint16_t EPWM9_A0_sclk:1;           // 16 Input Flag clear for EPWM9_A0_sclk Signal
    uint16_t EPWM9_B0_sclk:1;           // 17 Input Flag clear for EPWM9_B0_sclk Signal
    uint16_t EPWM10_A0_sclk:1;          // 18 Input Flag clear for EPWM10_A0_sclk Signal
    uint16_t EPWM10_B0_sclk:1;          // 19 Input Flag clear for EPWM10_B0_sclk Signal
    uint16_t EPWM11_A0_sclk:1;          // 20 Input Flag clear for EPWM11_A0_sclk Signal
    uint16_t EPWM11_B0_sclk:1;          // 21 Input Flag clear for EPWM11_B0_sclk Signal
    uint16_t EPWM12_A0_sclk:1;          // 22 Input Flag clear for EPWM12_A0_sclk Signal
    uint16_t EPWM12_B0_sclk:1;          // 23 Input Flag clear for EPWM12_B0_sclk Signal
    uint16_t EPWM13_A0_sclk:1;          // 24 Input Flag clear for EPWM13_A0_sclk Signal
    uint16_t EPWM13_B0_sclk:1;          // 25 Input Flag clear for EPWM13_B0_sclk Signal
    uint16_t EPWM14_A0_sclk:1;          // 26 Input Flag clear for EPWM14_A0_sclk Signal
    uint16_t EPWM14_B0_sclk:1;          // 27 Input Flag clear for EPWM14_B0_sclk Signal
    uint16_t EPWM15_A0_sclk:1;          // 28 Input Flag clear for EPWM15_A0_sclk Signal
    uint16_t EPWM15_B0_sclk:1;          // 29 Input Flag clear for EPWM15_B0_sclk Signal
    uint16_t EPWM16_A0_sclk:1;          // 30 Input Flag clear for EPWM16_A0_sclk Signal
    uint16_t EPWM16_B0_sclk:1;          // 31 Input Flag clear for EPWM16_B0_sclk Signal
};

union XBAR_XBARCLR11_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR11_BITS  bit;
};

struct XBAR_XBARCLR12_BITS {            // bits description
    uint16_t EPWM17_A0_sclk:1;          // 0 Input Flag clear for EPWM17_A0_sclk Signal
    uint16_t EPWM17_B0_sclk:1;          // 1 Input Flag clear for EPWM17_B0_sclk Signal
    uint16_t EPWM18_A0_sclk:1;          // 2 Input Flag clear for EPWM18_A0_sclk Signal
    uint16_t EPWM18_B0_sclk:1;          // 3 Input Flag clear for EPWM18_B0_sclk Signal
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t rsvd13:1;                  // 16 Reserved
    uint16_t rsvd14:1;                  // 17 Reserved
    uint16_t rsvd15:1;                  // 18 Reserved
    uint16_t rsvd16:1;                  // 19 Reserved
    uint16_t rsvd17:1;                  // 20 Reserved
    uint16_t rsvd18:1;                  // 21 Reserved
    uint16_t rsvd19:1;                  // 22 Reserved
    uint16_t rsvd20:1;                  // 23 Reserved
    uint16_t rsvd21:1;                  // 24 Reserved
    uint16_t rsvd22:1;                  // 25 Reserved
    uint16_t rsvd23:1;                  // 26 Reserved
    uint16_t rsvd24:1;                  // 27 Reserved
    uint16_t rsvd25:1;                  // 28 Reserved
    uint16_t rsvd26:1;                  // 29 Reserved
    uint16_t rsvd27:1;                  // 30 Reserved
    uint16_t rsvd28:1;                  // 31 Reserved
};

union XBAR_XBARCLR12_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR12_BITS  bit;
};

struct XBAR_XBARCLR13_BITS {            // bits description
    uint16_t MDL1_OUTA:1;               // 0 Input Flag clear for MDL1_OUTA Signal
    uint16_t MDL1_OUTB:1;               // 1 Input Flag clear for MDL1_OUTB Signal
    uint16_t MDL2_OUTA:1;               // 2 Input Flag clear for MDL2_OUTA Signal
    uint16_t MDL2_OUTB:1;               // 3 Input Flag clear for MDL2_OUTB Signal
    uint16_t MDL3_OUTA:1;               // 4 Input Flag clear for MDL3_OUTA Signal
    uint16_t MDL3_OUTB:1;               // 5 Input Flag clear for MDL3_OUTB Signal
    uint16_t MDL4_OUTA:1;               // 6 Input Flag clear for MDL4_OUTA Signal
    uint16_t MDL4_OUTB:1;               // 7 Input Flag clear for MDL4_OUTB Signal
    uint16_t MDL5_OUTA:1;               // 8 Input Flag clear for MDL5_OUTA Signal
    uint16_t MDL5_OUTB:1;               // 9 Input Flag clear for MDL5_OUTB Signal
    uint16_t MDL6_OUTA:1;               // 10 Input Flag clear for MDL6_OUTA Signal
    uint16_t MDL6_OUTB:1;               // 11 Input Flag clear for MDL6_OUTB Signal
    uint16_t MDL7_OUTA:1;               // 12 Input Flag clear for MDL7_OUTA Signal
    uint16_t MDL7_OUTB:1;               // 13 Input Flag clear for MDL7_OUTB Signal
    uint16_t MDL8_OUTA:1;               // 14 Input Flag clear for MDL8_OUTA Signal
    uint16_t MDL8_OUTB:1;               // 15 Input Flag clear for MDL8_OUTB Signal
    uint16_t MDL9_OUTA:1;               // 16 Input Flag clear for MDL9_OUTA Signal
    uint16_t MDL9_OUTB:1;               // 17 Input Flag clear for MDL9_OUTB Signal
    uint16_t MDL10_OUTA:1;              // 18 Input Flag clear for MDL10_OUTA Signal
    uint16_t MDL10_OUTB:1;              // 19 Input Flag clear for MDL10_OUTB Signal
    uint16_t MDL11_OUTA:1;              // 20 Input Flag clear for MDL11_OUTA Signal
    uint16_t MDL11_OUTB:1;              // 21 Input Flag clear for MDL11_OUTB Signal
    uint16_t MDL12_OUTA:1;              // 22 Input Flag clear for MDL12_OUTA Signal
    uint16_t MDL12_OUTB:1;              // 23 Input Flag clear for MDL12_OUTB Signal
    uint16_t MDL13_OUTA:1;              // 24 Input Flag clear for MDL13_OUTA Signal
    uint16_t MDL13_OUTB:1;              // 25 Input Flag clear for MDL13_OUTB Signal
    uint16_t MDL14_OUTA:1;              // 26 Input Flag clear for MDL14_OUTA Signal
    uint16_t MDL14_OUTB:1;              // 27 Input Flag clear for MDL14_OUTB Signal
    uint16_t MDL15_OUTA:1;              // 28 Input Flag clear for MDL15_OUTA Signal
    uint16_t MDL15_OUTB:1;              // 29 Input Flag clear for MDL15_OUTB Signal
    uint16_t MDL16_OUTA:1;              // 30 Input Flag clear for MDL16_OUTA Signal
    uint16_t MDL16_OUTB:1;              // 31 Input Flag clear for MDL16_OUTB Signal
};

union XBAR_XBARCLR13_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR13_BITS  bit;
};

struct XBAR_XBARCLR14_BITS {            // bits description
    uint16_t MDL17_OUTA:1;              // 0 Input Flag clear for MDL17_OUTA Signal
    uint16_t MDL17_OUTB:1;              // 1 Input Flag clear for MDL17_OUTB Signal
    uint16_t MDL18_OUTA:1;              // 2 Input Flag clear for MDL18_OUTA Signal
    uint16_t MDL18_OUTB:1;              // 3 Input Flag clear for MDL18_OUTB Signal
    uint16_t rsvd1:1;                   // 4 Reserved
    uint16_t rsvd2:1;                   // 5 Reserved
    uint16_t rsvd3:1;                   // 6 Reserved
    uint16_t rsvd4:1;                   // 7 Reserved
    uint16_t rsvd5:1;                   // 8 Reserved
    uint16_t rsvd6:1;                   // 9 Reserved
    uint16_t rsvd7:1;                   // 10 Reserved
    uint16_t rsvd8:1;                   // 11 Reserved
    uint16_t rsvd9:1;                   // 12 Reserved
    uint16_t rsvd10:1;                  // 13 Reserved
    uint16_t rsvd11:1;                  // 14 Reserved
    uint16_t rsvd12:1;                  // 15 Reserved
    uint16_t rsvd13:1;                  // 16 Reserved
    uint16_t rsvd14:1;                  // 17 Reserved
    uint16_t rsvd15:1;                  // 18 Reserved
    uint16_t rsvd16:1;                  // 19 Reserved
    uint16_t rsvd17:1;                  // 20 Reserved
    uint16_t rsvd18:1;                  // 21 Reserved
    uint16_t rsvd19:1;                  // 22 Reserved
    uint16_t rsvd20:1;                  // 23 Reserved
    uint16_t rsvd21:1;                  // 24 Reserved
    uint16_t rsvd22:1;                  // 25 Reserved
    uint16_t rsvd23:1;                  // 26 Reserved
    uint16_t rsvd24:1;                  // 27 Reserved
    uint16_t rsvd25:1;                  // 28 Reserved
    uint16_t rsvd26:1;                  // 29 Reserved
    uint16_t rsvd27:1;                  // 30 Reserved
    uint16_t rsvd28:1;                  // 31 Reserved
};

union XBAR_XBARCLR14_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR14_BITS  bit;
};

struct XBAR_XBARCLR15_BITS {            // bits description
    uint16_t CLB1_OUT0:1;               // 0 Input Flag clear for CLB1_OUT0 Signal
    uint16_t CLB1_OUT1:1;               // 1 Input Flag clear for CLB1_OUT1 Signal
    uint16_t CLB1_OUT2:1;               // 2 Input Flag clear for CLB1_OUT2 Signal
    uint16_t CLB1_OUT3:1;               // 3 Input Flag clear for CLB1_OUT3 Signal
    uint16_t CLB1_OUT6:1;               // 4 Input Flag clear for CLB1_OUT6 Signal
    uint16_t CLB1_OUT7:1;               // 5 Input Flag clear for CLB1_OUT7 Signal
    uint16_t CLB2_OUT0:1;               // 6 Input Flag clear for CLB2_OUT0 Signal
    uint16_t CLB2_OUT1:1;               // 7 Input Flag clear for CLB2_OUT1 Signal
    uint16_t CLB2_OUT2:1;               // 8 Input Flag clear for CLB2_OUT2 Signal
    uint16_t CLB2_OUT3:1;               // 9 Input Flag clear for CLB2_OUT3 Signal
    uint16_t CLB2_OUT6:1;               // 10 Input Flag clear for CLB2_OUT6 Signal
    uint16_t CLB2_OUT7:1;               // 11 Input Flag clear for CLB2_OUT7 Signal
    uint16_t CLB3_OUT0:1;               // 12 Input Flag clear for CLB3_OUT0 Signal
    uint16_t CLB3_OUT1:1;               // 13 Input Flag clear for CLB3_OUT1 Signal
    uint16_t CLB3_OUT2:1;               // 14 Input Flag clear for CLB3_OUT2 Signal
    uint16_t CLB3_OUT3:1;               // 15 Input Flag clear for CLB3_OUT3 Signal
    uint16_t CLB3_OUT6:1;               // 16 Input Flag clear for CLB3_OUT6 Signal
    uint16_t CLB3_OUT7:1;               // 17 Input Flag clear for CLB3_OUT7 Signal
    uint16_t CLB4_OUT0:1;               // 18 Input Flag clear for CLB4_OUT0 Signal
    uint16_t CLB4_OUT1:1;               // 19 Input Flag clear for CLB4_OUT1 Signal
    uint16_t CLB4_OUT2:1;               // 20 Input Flag clear for CLB4_OUT2 Signal
    uint16_t CLB4_OUT3:1;               // 21 Input Flag clear for CLB4_OUT3 Signal
    uint16_t CLB4_OUT6:1;               // 22 Input Flag clear for CLB4_OUT6 Signal
    uint16_t CLB4_OUT7:1;               // 23 Input Flag clear for CLB4_OUT7 Signal
    uint16_t CLB5_OUT0:1;               // 24 Input Flag clear for CLB5_OUT0 Signal
    uint16_t CLB5_OUT1:1;               // 25 Input Flag clear for CLB5_OUT1 Signal
    uint16_t CLB5_OUT2:1;               // 26 Input Flag clear for CLB5_OUT2 Signal
    uint16_t CLB5_OUT3:1;               // 27 Input Flag clear for CLB5_OUT3 Signal
    uint16_t CLB5_OUT6:1;               // 28 Input Flag clear for CLB5_OUT6 Signal
    uint16_t CLB5_OUT7:1;               // 29 Input Flag clear for CLB5_OUT7 Signal
    uint16_t CLB6_OUT0:1;               // 30 Input Flag clear for CLB6_OUT0 Signal
    uint16_t CLB6_OUT1:1;               // 31 Input Flag clear for CLB6_OUT1 Signal
};

union XBAR_XBARCLR15_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR15_BITS  bit;
};

struct XBAR_XBARCLR16_BITS {            // bits description
    uint16_t CLB6_OUT2:1;               // 0 Input Flag clear for CLB6_OUT2 Signal
    uint16_t CLB6_OUT3:1;               // 1 Input Flag clear for CLB6_OUT3 Signal
    uint16_t CLB6_OUT6:1;               // 2 Input Flag clear for CLB6_OUT6 Signal
    uint16_t CLB6_OUT7:1;               // 3 Input Flag clear for CLB6_OUT7 Signal
    uint16_t ADCA_EXTMUXSEL0:1;         // 4 Input Flag clear for ADCA_EXTMUXSEL0 Signal
    uint16_t ADCA_EXTMUXSEL1:1;         // 5 Input Flag clear for ADCA_EXTMUXSEL1 Signal
    uint16_t ADCA_EXTMUXSEL2:1;         // 6 Input Flag clear for ADCA_EXTMUXSEL2 Signal
    uint16_t ADCA_EXTMUXSEL3:1;         // 7 Input Flag clear for ADCA_EXTMUXSEL3 Signal
    uint16_t ADCB_EXTMUXSEL0:1;         // 8 Input Flag clear for ADCB_EXTMUXSEL0 Signal
    uint16_t ADCB_EXTMUXSEL1:1;         // 9 Input Flag clear for ADCB_EXTMUXSEL1 Signal
    uint16_t ADCB_EXTMUXSEL2:1;         // 10 Input Flag clear for ADCB_EXTMUXSEL2 Signal
    uint16_t ADCB_EXTMUXSEL3:1;         // 11 Input Flag clear for ADCB_EXTMUXSEL3 Signal
    uint16_t ADCC_EXTMUXSEL0:1;         // 12 Input Flag clear for ADCC_EXTMUXSEL0 Signal
    uint16_t ADCC_EXTMUXSEL1:1;         // 13 Input Flag clear for ADCC_EXTMUXSEL1 Signal
    uint16_t ADCC_EXTMUXSEL2:1;         // 14 Input Flag clear for ADCC_EXTMUXSEL2 Signal
    uint16_t ADCC_EXTMUXSEL3:1;         // 15 Input Flag clear for ADCC_EXTMUXSEL3 Signal
    uint16_t ADCD_EXTMUXSEL0:1;         // 16 Input Flag clear for ADCD_EXTMUXSEL0 Signal
    uint16_t ADCD_EXTMUXSEL1:1;         // 17 Input Flag clear for ADCD_EXTMUXSEL1 Signal
    uint16_t ADCD_EXTMUXSEL2:1;         // 18 Input Flag clear for ADCD_EXTMUXSEL2 Signal
    uint16_t ADCD_EXTMUXSEL3:1;         // 19 Input Flag clear for ADCD_EXTMUXSEL3 Signal
    uint16_t ADCE_EXTMUXSEL0:1;         // 20 Input Flag clear for ADCE_EXTMUXSEL0 Signal
    uint16_t ADCE_EXTMUXSEL1:1;         // 21 Input Flag clear for ADCE_EXTMUXSEL1 Signal
    uint16_t ADCE_EXTMUXSEL2:1;         // 22 Input Flag clear for ADCE_EXTMUXSEL2 Signal
    uint16_t ADCE_EXTMUXSEL3:1;         // 23 Input Flag clear for ADCE_EXTMUXSEL3 Signal
    uint16_t rsvd1:1;                   // 24 Reserved
    uint16_t rsvd2:1;                   // 25 Reserved
    uint16_t rsvd3:1;                   // 26 Reserved
    uint16_t rsvd4:1;                   // 27 Reserved
    uint16_t EPG1_EPGOUT0:1;            // 28 Input Flag clear for EPG1_EPGOUT0 Signal
    uint16_t EPG1_EPGOUT1:1;            // 29 Input Flag clear for EPG1_EPGOUT1 Signal
    uint16_t EPG1_EPGOUT2:1;            // 30 Input Flag clear for EPG1_EPGOUT2 Signal
    uint16_t EPG1_EPGOUT3:1;            // 31 Input Flag clear for EPG1_EPGOUT3 Signal
};

union XBAR_XBARCLR16_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR16_BITS  bit;
};

struct XBAR_XBARCLR17_BITS {            // bits description
    uint16_t MCANA_FEVT0:1;             // 0 Input Flag clear for MCANA_FEVT0 Signal
    uint16_t MCANA_FEVT1:1;             // 1 Input Flag clear for MCANA_FEVT1 Signal
    uint16_t MCANA_FEVT2:1;             // 2 Input Flag clear for MCANA_FEVT2 Signal
    uint16_t MCANB_FEVT0:1;             // 3 Input Flag clear for MCANB_FEVT0 Signal
    uint16_t MCANB_FEVT1:1;             // 4 Input Flag clear for MCANB_FEVT1 Signal
    uint16_t MCANB_FEVT2:1;             // 5 Input Flag clear for MCANB_FEVT2 Signal
    uint16_t MCANC_FEVT0:1;             // 6 Input Flag clear for MCANC_FEVT0 Signal
    uint16_t MCANC_FEVT1:1;             // 7 Input Flag clear for MCANC_FEVT1 Signal
    uint16_t MCANC_FEVT2:1;             // 8 Input Flag clear for MCANC_FEVT2 Signal
    uint16_t MCAND_FEVT0:1;             // 9 Input Flag clear for MCAND_FEVT0 Signal
    uint16_t MCAND_FEVT1:1;             // 10 Input Flag clear for MCAND_FEVT1 Signal
    uint16_t MCAND_FEVT2:1;             // 11 Input Flag clear for MCAND_FEVT2 Signal
    uint16_t MCANE_FEVT0:1;             // 12 Input Flag clear for MCANE_FEVT0 Signal
    uint16_t MCANE_FEVT1:1;             // 13 Input Flag clear for MCANE_FEVT1 Signal
    uint16_t MCANE_FEVT2:1;             // 14 Input Flag clear for MCANE_FEVT2 Signal
    uint16_t MCANF_FEVT0:1;             // 15 Input Flag clear for MCANF_FEVT0 Signal
    uint16_t MCANF_FEVT1:1;             // 16 Input Flag clear for MCANF_FEVT1 Signal
    uint16_t MCANF_FEVT2:1;             // 17 Input Flag clear for MCANF_FEVT2 Signal
    uint16_t rsvd1:14;                  // 31:18 Reserved
};

union XBAR_XBARCLR17_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR17_BITS  bit;
};

struct XBAR_XBARCLR18_BITS {            // bits description
    uint16_t FSIRXA_TRIG_2:1;           // 0 Input Flag clear for FSIRXA_TRIG_2 Signal
    uint16_t FSIRXA_TRIG_3:1;           // 1 Input Flag clear for FSIRXA_TRIG_3 Signal
    uint16_t FSIRXB_TRIG_2:1;           // 2 Input Flag clear for FSIRXB_TRIG_2 Signal
    uint16_t FSIRXB_TRIG_3:1;           // 3 Input Flag clear for FSIRXB_TRIG_3 Signal
    uint16_t FSIRXC_TRIG_2:1;           // 4 Input Flag clear for FSIRXC_TRIG_2 Signal
    uint16_t FSIRXC_TRIG_3:1;           // 5 Input Flag clear for FSIRXC_TRIG_3 Signal
    uint16_t FSIRXD_TRIG_2:1;           // 6 Input Flag clear for FSIRXD_TRIG_2 Signal
    uint16_t FSIRXD_TRIG_3:1;           // 7 Input Flag clear for FSIRXD_TRIG_3 Signal
    uint16_t CPU1ERADEVT8:1;            // 8 Input Flag clear for CPU1ERADEVT8 Signal
    uint16_t CPU1ERADEVT9:1;            // 9 Input Flag clear for CPU1ERADEVT9 Signal
    uint16_t CPU1ERADEVT10:1;           // 10 Input Flag clear for CPU1ERADEVT10 Signal
    uint16_t CPU1ERADEVT11:1;           // 11 Input Flag clear for CPU1ERADEVT11 Signal
    uint16_t CPU2ERADEVT8:1;            // 12 Input Flag clear for CPU2ERADEVT8 Signal
    uint16_t CPU2ERADEVT9:1;            // 13 Input Flag clear for CPU2ERADEVT9 Signal
    uint16_t CPU2ERADEVT10:1;           // 14 Input Flag clear for CPU2ERADEVT10 Signal
    uint16_t CPU2ERADEVT11:1;           // 15 Input Flag clear for CPU2ERADEVT11 Signal
    uint16_t CPU3ERADEVT8:1;            // 16 Input Flag clear for CPU3ERADEVT8 Signal
    uint16_t CPU3ERADEVT9:1;            // 17 Input Flag clear for CPU3ERADEVT9 Signal
    uint16_t CPU3ERADEVT10:1;           // 18 Input Flag clear for CPU3ERADEVT10 Signal
    uint16_t CPU3ERADEVT11:1;           // 19 Input Flag clear for CPU3ERADEVT11 Signal
    uint16_t rsvd1:12;                  // 31:20 Reserved
};

union XBAR_XBARCLR18_REG {
    uint32_t  all;
    struct  XBAR_XBARCLR18_BITS  bit;
};

struct XBAR_REGS {
    union   XBAR_XBARFLG1_REG                XBARFLG1;                     // X-Bar Input Flag Register 1
    union   XBAR_XBARFLG2_REG                XBARFLG2;                     // X-Bar Input Flag Register 2
    union   XBAR_XBARFLG3_REG                XBARFLG3;                     // X-Bar Input Flag Register 3
    union   XBAR_XBARFLG4_REG                XBARFLG4;                     // X-Bar Input Flag Register 4
    union   XBAR_XBARFLG5_REG                XBARFLG5;                     // X-Bar Input Flag Register 5
    union   XBAR_XBARFLG6_REG                XBARFLG6;                     // X-Bar Input Flag Register 6
    union   XBAR_XBARFLG7_REG                XBARFLG7;                     // X-Bar Input Flag Register 7
    union   XBAR_XBARFLG8_REG                XBARFLG8;                     // X-Bar Input Flag Register 8
    union   XBAR_XBARFLG9_REG                XBARFLG9;                     // X-Bar Input Flag Register 9
    union   XBAR_XBARFLG10_REG               XBARFLG10;                    // X-Bar Input Flag Register 10
    union   XBAR_XBARFLG11_REG               XBARFLG11;                    // X-Bar Input Flag Register 11
    union   XBAR_XBARFLG12_REG               XBARFLG12;                    // X-Bar Input Flag Register 12
    union   XBAR_XBARFLG13_REG               XBARFLG13;                    // X-Bar Input Flag Register 13
    union   XBAR_XBARFLG14_REG               XBARFLG14;                    // X-Bar Input Flag Register 14
    union   XBAR_XBARFLG15_REG               XBARFLG15;                    // X-Bar Input Flag Register 15
    union   XBAR_XBARFLG16_REG               XBARFLG16;                    // X-Bar Input Flag Register 16
    union   XBAR_XBARFLG17_REG               XBARFLG17;                    // X-Bar Input Flag Register 16
    union   XBAR_XBARFLG18_REG               XBARFLG18;                    // X-Bar Input Flag Register 16
    uint8_t                                  rsvd1[184];                   // Reserved
    union   XBAR_XBARCLR1_REG                XBARCLR1;                     // X-Bar Input Flag Clear Register 1
    union   XBAR_XBARCLR2_REG                XBARCLR2;                     // X-Bar Input Flag Clear Register 2
    union   XBAR_XBARCLR3_REG                XBARCLR3;                     // X-Bar Input Flag Clear Register 3
    union   XBAR_XBARCLR4_REG                XBARCLR4;                     // X-Bar Input Flag Clear Register 4
    union   XBAR_XBARCLR5_REG                XBARCLR5;                     // X-Bar Input Flag Clear Register 5
    union   XBAR_XBARCLR6_REG                XBARCLR6;                     // X-Bar Input Flag Clear Register 6
    union   XBAR_XBARCLR7_REG                XBARCLR7;                     // X-Bar Input Flag Clear Register 7
    union   XBAR_XBARCLR8_REG                XBARCLR8;                     // X-Bar Input Flag Clear Register 8
    union   XBAR_XBARCLR9_REG                XBARCLR9;                     // X-Bar Input Flag Clear Register 9
    union   XBAR_XBARCLR10_REG               XBARCLR10;                    // X-Bar Input Flag Clear Register 10
    union   XBAR_XBARCLR11_REG               XBARCLR11;                    // X-Bar Input Flag Clear Register 11
    union   XBAR_XBARCLR12_REG               XBARCLR12;                    // X-Bar Input Flag Clear Register 12
    union   XBAR_XBARCLR13_REG               XBARCLR13;                    // X-Bar Input Flag Clear Register 13
    union   XBAR_XBARCLR14_REG               XBARCLR14;                    // X-Bar Input Flag Clear Register 14
    union   XBAR_XBARCLR15_REG               XBARCLR15;                    // X-Bar Input Flag Clear Register 15
    union   XBAR_XBARCLR16_REG               XBARCLR16;                    // X-Bar Input Flag Clear Register 15
    union   XBAR_XBARCLR17_REG               XBARCLR17;                    // X-Bar Input Flag Clear Register 16
    union   XBAR_XBARCLR18_REG               XBARCLR18;                    // X-Bar Input Flag Clear Register 16
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
