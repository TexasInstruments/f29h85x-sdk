//###########################################################################
//
// FILE:    hwbf_elt.h
//
// TITLE:   Definitions for the ELT registers.
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

#ifndef HWBF_ELT_H
#define HWBF_ELT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// ELT Individual Register Bit Definitions:

struct ELT_ELTCTL_BITS {                // bits description
    uint16_t ENA:1;                     // 0 ENABLE
    uint16_t LOGCTLENA:1;               // 1 Log Control Enable
    uint16_t LOGCTLRDY:1;               // 2 Log Control Ready
    uint16_t FIFORSTPR:1;               // 3 FIFO Reset Pointer
    uint16_t rsvd1:12;                  // 15:4 Reserved
    uint16_t FIFOTHRESHOLD:5;           // 20:16 FIFO Threshold for Int or DMA Req event
    uint16_t rsvd2:3;                   // 23:21 Reserved
    uint16_t FIFOST:5;                  // 28:24 FIFO Status
    uint16_t rsvd3:3;                   // 31:29 Reserved
};

union ELT_ELTCTL_REG {
    uint32_t  all;
    struct  ELT_ELTCTL_BITS  bit;
};

struct ELT_ELTSWINPEVT_BITS {           // bits description
    uint16_t SWINPEVT0:1;               // 0 SW Input Event 0
    uint16_t SWINPEVT1:1;               // 1 SW Input Event 1
    uint16_t SWINPEVT2:1;               // 2 SW Input Event 2
    uint16_t SWINPEVT3:1;               // 3 SW Input Event 3
    uint16_t SWINPEVT4:1;               // 4 SW Input Event 4
    uint16_t SWINPEVT5:1;               // 5 SW Input Event 5
    uint16_t SWINPEVT6:1;               // 6 SW Input Event 6
    uint16_t SWINPEVT7:1;               // 7 SW Input Event 7
    uint16_t SWINPEVT8:1;               // 8 SW Input Event 8
    uint16_t SWINPEVT9:1;               // 9 SW Input Event 9
    uint16_t SWINPEVT10:1;              // 10 SW Input Event 10
    uint16_t SWINPEVT11:1;              // 11 SW Input Event 11
    uint16_t SWINPEVT12:1;              // 12 SW Input Event 12
    uint16_t SWINPEVT13:1;              // 13 SW Input Event 13
    uint16_t SWINPEVT14:1;              // 14 SW Input Event 14
    uint16_t SWINPEVT15:1;              // 15 SW Input Event 15
    uint16_t SWINPEVT16:1;              // 16 SW Input Event 16
    uint16_t SWINPEVT17:1;              // 17 SW Input Event 17
    uint16_t SWINPEVT18:1;              // 18 SW Input Event 18
    uint16_t SWINPEVT19:1;              // 19 SW Input Event 19
    uint16_t SWINPEVT20:1;              // 20 SW Input Event 20
    uint16_t SWINPEVT21:1;              // 21 SW Input Event 21
    uint16_t SWINPEVT22:1;              // 22 SW Input Event 22
    uint16_t SWINPEVT23:1;              // 23 SW Input Event 23
    uint16_t SWINPEVT24:1;              // 24 SW Input Event 24
    uint16_t SWINPEVT25:1;              // 25 SW Input Event 25
    uint16_t SWINPEVT26:1;              // 26 SW Input Event 26
    uint16_t SWINPEVT27:1;              // 27 SW Input Event 27
    uint16_t SWINPEVT28:1;              // 28 SW Input Event 28
    uint16_t SWINPEVT29:1;              // 29 SW Input Event 29
    uint16_t SWINPEVT30:1;              // 30 SW Input Event 30
    uint16_t SWINPEVT31:1;              // 31 SW Input Event 31
};

union ELT_ELTSWINPEVT_REG {
    uint32_t  all;
    struct  ELT_ELTSWINPEVT_BITS  bit;
};

struct ELT_ELTPOLARITY_BITS {           // bits description
    uint16_t MUXOUT0POL:1;              // 0 Mux Output 0 Polarity
    uint16_t MUXOUT1POL:1;              // 1 Mux Output 1 Polarity
    uint16_t MUXOUT2POL:1;              // 2 Mux Output 2 Polarity
    uint16_t MUXOUT3POL:1;              // 3 Mux Output 3 Polarity
    uint16_t MUXOUT4POL:1;              // 4 Mux Output 4 Polarity
    uint16_t MUXOUT5POL:1;              // 5 Mux Output 5 Polarity
    uint16_t MUXOUT6POL:1;              // 6 Mux Output 6 Polarity
    uint16_t MUXOUT7POL:1;              // 7 Mux Output 7 Polarity
    uint16_t MUXOUT8POL:1;              // 8 Mux Output 8 Polarity
    uint16_t MUXOUT9POL:1;              // 9 Mux Output 9 Polarity
    uint16_t MUXOUT10POL:1;             // 10 Mux Output 10 Polarity
    uint16_t MUXOUT11POL:1;             // 11 Mux Output 11 Polarity
    uint16_t MUXOUT12POL:1;             // 12 Mux Output 12 Polarity
    uint16_t MUXOUT13POL:1;             // 13 Mux Output 13 Polarity
    uint16_t MUXOUT14POL:1;             // 14 Mux Output 14 Polarity
    uint16_t MUXOUT15POL:1;             // 15 Mux Output 15 Polarity
    uint16_t MUXOUT16POL:1;             // 16 Mux Output 16 Polarity
    uint16_t MUXOUT17POL:1;             // 17 Mux Output 17 Polarity
    uint16_t MUXOUT18POL:1;             // 18 Mux Output 18 Polarity
    uint16_t MUXOUT19POL:1;             // 19 Mux Output 19 Polarity
    uint16_t MUXOUT20POL:1;             // 20 Mux Output 20 Polarity
    uint16_t MUXOUT21POL:1;             // 21 Mux Output 21 Polarity
    uint16_t MUXOUT22POL:1;             // 22 Mux Output 22 Polarity
    uint16_t MUXOUT23POL:1;             // 23 Mux Output 23 Polarity
    uint16_t MUXOUT24POL:1;             // 24 Mux Output 24 Polarity
    uint16_t MUXOUT25POL:1;             // 25 Mux Output 25 Polarity
    uint16_t MUXOUT26POL:1;             // 26 Mux Output 26 Polarity
    uint16_t MUXOUT27POL:1;             // 27 Mux Output 27 Polarity
    uint16_t MUXOUT28POL:1;             // 28 Mux Output 28 Polarity
    uint16_t MUXOUT29POL:1;             // 29 Mux Output 29 Polarity
    uint16_t MUXOUT30POL:1;             // 30 Mux Output 30 Polarity
    uint16_t MUXOUT31POL:1;             // 31 Mux Output 31 Polarity
};

union ELT_ELTPOLARITY_REG {
    uint32_t  all;
    struct  ELT_ELTPOLARITY_BITS  bit;
};

struct ELT_ELTLOGCTL_BITS {             // bits description
    uint16_t LOGCTL:5;                  // 4:0 Log Control
    uint16_t rsvd1:11;                  // 15:5 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTLOGCTL_REG {
    uint32_t  all;
    struct  ELT_ELTLOGCTL_BITS  bit;
};

struct ELT_ELTEDGE_BITS {               // bits description
    uint16_t MUXOUT0EDGE:1;             // 0 Mux Output 0 Edge to Capture Data
    uint16_t MUXOUT1EDGE:1;             // 1 Mux Output 1 Edge to Capture Data
    uint16_t MUXOUT2EDGE:1;             // 2 Mux Output 2 Edge to Capture Data
    uint16_t MUXOUT3EDGE:1;             // 3 Mux Output 3 Edge to Capture Data
    uint16_t MUXOUT4EDGE:1;             // 4 Mux Output 4 Edge to Capture Data
    uint16_t MUXOUT5EDGE:1;             // 5 Mux Output 5 Edge to Capture Data
    uint16_t MUXOUT6EDGE:1;             // 6 Mux Output 6 Edge to Capture Data
    uint16_t MUXOUT7EDGE:1;             // 7 Mux Output 7 Edge to Capture Data
    uint16_t MUXOUT8EDGE:1;             // 8 Mux Output 8 Edge to Capture Data
    uint16_t MUXOUT9EDGE:1;             // 9 Mux Output 9 Edge to Capture Data
    uint16_t MUXOUT10EDGE:1;            // 10 Mux Output 10 Edge to Capture Data
    uint16_t MUXOUT11EDGE:1;            // 11 Mux Output 11 Edge to Capture Data
    uint16_t MUXOUT12EDGE:1;            // 12 Mux Output 12 Edge to Capture Data
    uint16_t MUXOUT13EDGE:1;            // 13 Mux Output 13 Edge to Capture Data
    uint16_t MUXOUT14EDGE:1;            // 14 Mux Output 14 Edge to Capture Data
    uint16_t MUXOUT15EDGE:1;            // 15 Mux Output 15 Edge to Capture Data
    uint16_t MUXOUT16EDGE:1;            // 16 Mux Output 16 Edge to Capture Data
    uint16_t MUXOUT17EDGE:1;            // 17 Mux Output 17 Edge to Capture Data
    uint16_t MUXOUT18EDGE:1;            // 18 Mux Output 18 Edge to Capture Data
    uint16_t MUXOUT19EDGE:1;            // 19 Mux Output 19 Edge to Capture Data
    uint16_t MUXOUT20EDGE:1;            // 20 Mux Output 20 Edge to Capture Data
    uint16_t MUXOUT21EDGE:1;            // 21 Mux Output 21 Edge to Capture Data
    uint16_t MUXOUT22EDGE:1;            // 22 Mux Output 22 Edge to Capture Data
    uint16_t MUXOUT23EDGE:1;            // 23 Mux Output 23 Edge to Capture Data
    uint16_t MUXOUT24EDGE:1;            // 24 Mux Output 24 Edge to Capture Data
    uint16_t MUXOUT25EDGE:1;            // 25 Mux Output 25 Edge to Capture Data
    uint16_t MUXOUT26EDGE:1;            // 26 Mux Output 26 Edge to Capture Data
    uint16_t MUXOUT27EDGE:1;            // 27 Mux Output 27 Edge to Capture Data
    uint16_t MUXOUT28EDGE:1;            // 28 Mux Output 28 Edge to Capture Data
    uint16_t MUXOUT29EDGE:1;            // 29 Mux Output 29 Edge to Capture Data
    uint16_t MUXOUT30EDGE:1;            // 30 Mux Output 30 Edge to Capture Data
    uint16_t MUXOUT31EDGE:1;            // 31 Mux Output 31 Edge to Capture Data
};

union ELT_ELTEDGE_REG {
    uint32_t  all;
    struct  ELT_ELTEDGE_BITS  bit;
};

struct ELT_ELTINT_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t FIFOTHRESHOLD:1;           // 1 FIFO Pointer Equal to Threshold Interrupt Enable
    uint16_t FIFOOVF:1;                 // 2 FIFO Overflow Interrupt Enable
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ELT_ELTINT_REG {
    uint32_t  all;
    struct  ELT_ELTINT_BITS  bit;
};

struct ELT_ELTFLG_BITS {                // bits description
    uint16_t INT:1;                     // 0 Global Flag
    uint16_t FIFOTHRESHOLD:1;           // 1 FIFO Pointer Equal to Threshold Interrupt Flag
    uint16_t FIFOOVF:1;                 // 2 FIFO Overflow Interrupt Flag
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTFLG_REG {
    uint32_t  all;
    struct  ELT_ELTFLG_BITS  bit;
};

struct ELT_ELTCLR_BITS {                // bits description
    uint16_t INT:1;                     // 0 Global Interrupt Status Clear
    uint16_t FIFOTHRESHOLD:1;           // 1 FIFO Pointer Equal to Threshold Status Clear
    uint16_t FIFOOVF:1;                 // 2 FIFO Overflow Status Clear
    uint16_t rsvd1:13;                  // 15:3 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTCLR_REG {
    uint32_t  all;
    struct  ELT_ELTCLR_BITS  bit;
};

struct ELT_ELTFRC_BITS {                // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t FIFOTHRESHOLD:1;           // 1 FIFO Pointer Equal to Threshold Force Interrupt
    uint16_t FIFOOVF:1;                 // 2 FIFO Overflow Force  Interrupt
    uint16_t rsvd2:13;                  // 15:3 Reserved
    uint16_t rsvd3:16;                  // 31:16 Reserved
};

union ELT_ELTFRC_REG {
    uint32_t  all;
    struct  ELT_ELTFRC_BITS  bit;
};

struct ELT_ELTMUXSEL0_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL0_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL0_BITS  bit;
};

struct ELT_ELTMUXSEL1_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL1_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL1_BITS  bit;
};

struct ELT_ELTMUXSEL2_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL2_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL2_BITS  bit;
};

struct ELT_ELTMUXSEL3_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL3_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL3_BITS  bit;
};

struct ELT_ELTMUXSEL4_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL4_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL4_BITS  bit;
};

struct ELT_ELTMUXSEL5_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL5_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL5_BITS  bit;
};

struct ELT_ELTMUXSEL6_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL6_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL6_BITS  bit;
};

struct ELT_ELTMUXSEL7_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL7_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL7_BITS  bit;
};

struct ELT_ELTMUXSEL8_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL8_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL8_BITS  bit;
};

struct ELT_ELTMUXSEL9_BITS {            // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL9_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL9_BITS  bit;
};

struct ELT_ELTMUXSEL10_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL10_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL10_BITS  bit;
};

struct ELT_ELTMUXSEL11_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL11_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL11_BITS  bit;
};

struct ELT_ELTMUXSEL12_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL12_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL12_BITS  bit;
};

struct ELT_ELTMUXSEL13_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL13_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL13_BITS  bit;
};

struct ELT_ELTMUXSEL14_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL14_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL14_BITS  bit;
};

struct ELT_ELTMUXSEL15_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL15_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL15_BITS  bit;
};

struct ELT_ELTMUXSEL16_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL16_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL16_BITS  bit;
};

struct ELT_ELTMUXSEL17_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL17_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL17_BITS  bit;
};

struct ELT_ELTMUXSEL18_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL18_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL18_BITS  bit;
};

struct ELT_ELTMUXSEL19_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL19_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL19_BITS  bit;
};

struct ELT_ELTMUXSEL20_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL20_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL20_BITS  bit;
};

struct ELT_ELTMUXSEL21_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL21_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL21_BITS  bit;
};

struct ELT_ELTMUXSEL22_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL22_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL22_BITS  bit;
};

struct ELT_ELTMUXSEL23_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL23_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL23_BITS  bit;
};

struct ELT_ELTMUXSEL24_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL24_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL24_BITS  bit;
};

struct ELT_ELTMUXSEL25_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL25_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL25_BITS  bit;
};

struct ELT_ELTMUXSEL26_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL26_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL26_BITS  bit;
};

struct ELT_ELTMUXSEL27_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL27_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL27_BITS  bit;
};

struct ELT_ELTMUXSEL28_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL28_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL28_BITS  bit;
};

struct ELT_ELTMUXSEL29_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL29_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL29_BITS  bit;
};

struct ELT_ELTMUXSEL30_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL30_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL30_BITS  bit;
};

struct ELT_ELTMUXSEL31_BITS {           // bits description
    uint16_t MUXSEL:9;                  // 8:0 MUX Select
    uint16_t rsvd1:7;                   // 15:9 Reserved
    uint16_t rsvd2:16;                  // 31:16 Reserved
};

union ELT_ELTMUXSEL31_REG {
    uint32_t  all;
    struct  ELT_ELTMUXSEL31_BITS  bit;
};

struct ELT_REGS {
    union   ELT_ELTCTL_REG                   ELTCTL;                       // Control Register
    union   ELT_ELTSWINPEVT_REG              ELTSWINPEVT;                  // Software Input Event
    uint8_t                                  rsvd1[4];                     // Reserved
    union   ELT_ELTPOLARITY_REG              ELTPOLARITY;                  // Polarity Select
    union   ELT_ELTLOGCTL_REG                ELTLOGCTL;                    // Log Control
    union   ELT_ELTEDGE_REG                  ELTEDGE;                      // Edge Select
    uint8_t                                  rsvd2[4];                     // Reserved
    uint32_t                                 ELTMUXOUT;                    // MUX Output
    uint8_t                                  rsvd3[4];                     // Reserved
    union   ELT_ELTINT_REG                   ELTINT;                       // Interrupt Enable Register
    union   ELT_ELTFLG_REG                   ELTFLG;                       // Interrupt Flag Register
    union   ELT_ELTCLR_REG                   ELTCLR;                       // Interrupt Clear Register
    union   ELT_ELTFRC_REG                   ELTFRC;                       // Interrupt Force Register
    uint8_t                                  rsvd4[12];                    // Reserved
    uint32_t                                 ELTFIFOBUF_L;                 // FIFO Buffer Low (31:0)
    uint32_t                                 ELTFIFOBUF_M;                 // FIFO Buffer Mid (63:32)
    uint32_t                                 ELTFIFOBUF_H;                 // FIFO Buffer High (95:64)
    uint8_t                                  rsvd5[180];                   // Reserved
    union   ELT_ELTMUXSEL0_REG               ELTMUXSEL0;                   // MUX# Select
    union   ELT_ELTMUXSEL1_REG               ELTMUXSEL1;                   // MUX# Select
    union   ELT_ELTMUXSEL2_REG               ELTMUXSEL2;                   // MUX# Select
    union   ELT_ELTMUXSEL3_REG               ELTMUXSEL3;                   // MUX# Select
    union   ELT_ELTMUXSEL4_REG               ELTMUXSEL4;                   // MUX# Select
    union   ELT_ELTMUXSEL5_REG               ELTMUXSEL5;                   // MUX# Select
    union   ELT_ELTMUXSEL6_REG               ELTMUXSEL6;                   // MUX# Select
    union   ELT_ELTMUXSEL7_REG               ELTMUXSEL7;                   // MUX# Select
    union   ELT_ELTMUXSEL8_REG               ELTMUXSEL8;                   // MUX# Select
    union   ELT_ELTMUXSEL9_REG               ELTMUXSEL9;                   // MUX# Select
    union   ELT_ELTMUXSEL10_REG              ELTMUXSEL10;                  // MUX# Select
    union   ELT_ELTMUXSEL11_REG              ELTMUXSEL11;                  // MUX# Select
    union   ELT_ELTMUXSEL12_REG              ELTMUXSEL12;                  // MUX# Select
    union   ELT_ELTMUXSEL13_REG              ELTMUXSEL13;                  // MUX# Select
    union   ELT_ELTMUXSEL14_REG              ELTMUXSEL14;                  // MUX# Select
    union   ELT_ELTMUXSEL15_REG              ELTMUXSEL15;                  // MUX# Select
    union   ELT_ELTMUXSEL16_REG              ELTMUXSEL16;                  // MUX# Select
    union   ELT_ELTMUXSEL17_REG              ELTMUXSEL17;                  // MUX# Select
    union   ELT_ELTMUXSEL18_REG              ELTMUXSEL18;                  // MUX# Select
    union   ELT_ELTMUXSEL19_REG              ELTMUXSEL19;                  // MUX# Select
    union   ELT_ELTMUXSEL20_REG              ELTMUXSEL20;                  // MUX# Select
    union   ELT_ELTMUXSEL21_REG              ELTMUXSEL21;                  // MUX# Select
    union   ELT_ELTMUXSEL22_REG              ELTMUXSEL22;                  // MUX# Select
    union   ELT_ELTMUXSEL23_REG              ELTMUXSEL23;                  // MUX# Select
    union   ELT_ELTMUXSEL24_REG              ELTMUXSEL24;                  // MUX# Select
    union   ELT_ELTMUXSEL25_REG              ELTMUXSEL25;                  // MUX# Select
    union   ELT_ELTMUXSEL26_REG              ELTMUXSEL26;                  // MUX# Select
    union   ELT_ELTMUXSEL27_REG              ELTMUXSEL27;                  // MUX# Select
    union   ELT_ELTMUXSEL28_REG              ELTMUXSEL28;                  // MUX# Select
    union   ELT_ELTMUXSEL29_REG              ELTMUXSEL29;                  // MUX# Select
    union   ELT_ELTMUXSEL30_REG              ELTMUXSEL30;                  // MUX# Select
    union   ELT_ELTMUXSEL31_REG              ELTMUXSEL31;                  // MUX# Select
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
