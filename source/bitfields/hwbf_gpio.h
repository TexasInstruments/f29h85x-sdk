//###########################################################################
//
// FILE:    hwbf_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
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

#ifndef HWBF_GPIO_H
#define HWBF_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//---------------------------------------------------------------------------
// GPIO Individual Register Bit Definitions:

struct GPIO_GPACTRL_BITS {              // bits description
    uint16_t QUALPRD0:8;                // 7:0 Qualification sampling period for GPIO0 to GPIO7
    uint16_t QUALPRD1:8;                // 15:8 Qualification sampling period for GPIO8 to GPIO15
    uint16_t QUALPRD2:8;                // 23:16 Qualification sampling period for GPIO16 to GPIO23
    uint16_t QUALPRD3:8;                // 31:24 Qualification sampling period for GPIO24 to GPIO31
};

union GPIO_GPACTRL_REG {
    uint32_t  all;
    struct  GPIO_GPACTRL_BITS  bit;
};

struct GPIO_GPAQSEL1_BITS {             // bits description
    uint16_t GPIO0:2;                   // 1:0 Select input qualification type for GPIO0
    uint16_t GPIO1:2;                   // 3:2 Select input qualification type for GPIO1
    uint16_t GPIO2:2;                   // 5:4 Select input qualification type for GPIO2
    uint16_t GPIO3:2;                   // 7:6 Select input qualification type for GPIO3
    uint16_t GPIO4:2;                   // 9:8 Select input qualification type for GPIO4
    uint16_t GPIO5:2;                   // 11:10 Select input qualification type for GPIO5
    uint16_t GPIO6:2;                   // 13:12 Select input qualification type for GPIO6
    uint16_t GPIO7:2;                   // 15:14 Select input qualification type for GPIO7
    uint16_t GPIO8:2;                   // 17:16 Select input qualification type for GPIO8
    uint16_t GPIO9:2;                   // 19:18 Select input qualification type for GPIO9
    uint16_t GPIO10:2;                  // 21:20 Select input qualification type for GPIO10
    uint16_t GPIO11:2;                  // 23:22 Select input qualification type for GPIO11
    uint16_t GPIO12:2;                  // 25:24 Select input qualification type for GPIO12
    uint16_t GPIO13:2;                  // 27:26 Select input qualification type for GPIO13
    uint16_t GPIO14:2;                  // 29:28 Select input qualification type for GPIO14
    uint16_t GPIO15:2;                  // 31:30 Select input qualification type for GPIO15
};

union GPIO_GPAQSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPAQSEL1_BITS  bit;
};

struct GPIO_GPAQSEL2_BITS {             // bits description
    uint16_t GPIO16:2;                  // 1:0 Select input qualification type for GPIO16
    uint16_t GPIO17:2;                  // 3:2 Select input qualification type for GPIO17
    uint16_t GPIO18:2;                  // 5:4 Select input qualification type for GPIO18
    uint16_t GPIO19:2;                  // 7:6 Select input qualification type for GPIO19
    uint16_t GPIO20:2;                  // 9:8 Select input qualification type for GPIO20
    uint16_t GPIO21:2;                  // 11:10 Select input qualification type for GPIO21
    uint16_t GPIO22:2;                  // 13:12 Select input qualification type for GPIO22
    uint16_t GPIO23:2;                  // 15:14 Select input qualification type for GPIO23
    uint16_t GPIO24:2;                  // 17:16 Select input qualification type for GPIO24
    uint16_t GPIO25:2;                  // 19:18 Select input qualification type for GPIO25
    uint16_t GPIO26:2;                  // 21:20 Select input qualification type for GPIO26
    uint16_t GPIO27:2;                  // 23:22 Select input qualification type for GPIO27
    uint16_t GPIO28:2;                  // 25:24 Select input qualification type for GPIO28
    uint16_t GPIO29:2;                  // 27:26 Select input qualification type for GPIO29
    uint16_t GPIO30:2;                  // 29:28 Select input qualification type for GPIO30
    uint16_t GPIO31:2;                  // 31:30 Select input qualification type for GPIO31
};

union GPIO_GPAQSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPAQSEL2_BITS  bit;
};

struct GPIO_GPAMUX1_BITS {              // bits description
    uint16_t GPIO0:2;                   // 1:0 Defines pin-muxing selection for GPIO0
    uint16_t GPIO1:2;                   // 3:2 Defines pin-muxing selection for GPIO1
    uint16_t GPIO2:2;                   // 5:4 Defines pin-muxing selection for GPIO2
    uint16_t GPIO3:2;                   // 7:6 Defines pin-muxing selection for GPIO3
    uint16_t GPIO4:2;                   // 9:8 Defines pin-muxing selection for GPIO4
    uint16_t GPIO5:2;                   // 11:10 Defines pin-muxing selection for GPIO5
    uint16_t GPIO6:2;                   // 13:12 Defines pin-muxing selection for GPIO6
    uint16_t GPIO7:2;                   // 15:14 Defines pin-muxing selection for GPIO7
    uint16_t GPIO8:2;                   // 17:16 Defines pin-muxing selection for GPIO8
    uint16_t GPIO9:2;                   // 19:18 Defines pin-muxing selection for GPIO9
    uint16_t GPIO10:2;                  // 21:20 Defines pin-muxing selection for GPIO10
    uint16_t GPIO11:2;                  // 23:22 Defines pin-muxing selection for GPIO11
    uint16_t GPIO12:2;                  // 25:24 Defines pin-muxing selection for GPIO12
    uint16_t GPIO13:2;                  // 27:26 Defines pin-muxing selection for GPIO13
    uint16_t GPIO14:2;                  // 29:28 Defines pin-muxing selection for GPIO14
    uint16_t GPIO15:2;                  // 31:30 Defines pin-muxing selection for GPIO15
};

union GPIO_GPAMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPAMUX1_BITS  bit;
};

struct GPIO_GPAMUX2_BITS {              // bits description
    uint16_t GPIO16:2;                  // 1:0 Defines pin-muxing selection for GPIO16
    uint16_t GPIO17:2;                  // 3:2 Defines pin-muxing selection for GPIO17
    uint16_t GPIO18:2;                  // 5:4 Defines pin-muxing selection for GPIO18
    uint16_t GPIO19:2;                  // 7:6 Defines pin-muxing selection for GPIO19
    uint16_t GPIO20:2;                  // 9:8 Defines pin-muxing selection for GPIO20
    uint16_t GPIO21:2;                  // 11:10 Defines pin-muxing selection for GPIO21
    uint16_t GPIO22:2;                  // 13:12 Defines pin-muxing selection for GPIO22
    uint16_t GPIO23:2;                  // 15:14 Defines pin-muxing selection for GPIO23
    uint16_t GPIO24:2;                  // 17:16 Defines pin-muxing selection for GPIO24
    uint16_t GPIO25:2;                  // 19:18 Defines pin-muxing selection for GPIO25
    uint16_t GPIO26:2;                  // 21:20 Defines pin-muxing selection for GPIO26
    uint16_t GPIO27:2;                  // 23:22 Defines pin-muxing selection for GPIO27
    uint16_t GPIO28:2;                  // 25:24 Defines pin-muxing selection for GPIO28
    uint16_t GPIO29:2;                  // 27:26 Defines pin-muxing selection for GPIO29
    uint16_t GPIO30:2;                  // 29:28 Defines pin-muxing selection for GPIO30
    uint16_t GPIO31:2;                  // 31:30 Defines pin-muxing selection for GPIO31
};

union GPIO_GPAMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPAMUX2_BITS  bit;
};

struct GPIO_GPAPUD_BITS {               // bits description
    uint16_t GPIO0:1;                   // 0 Pull-Up Disable control for this pin
    uint16_t GPIO1:1;                   // 1 Pull-Up Disable control for this pin
    uint16_t GPIO2:1;                   // 2 Pull-Up Disable control for this pin
    uint16_t GPIO3:1;                   // 3 Pull-Up Disable control for this pin
    uint16_t GPIO4:1;                   // 4 Pull-Up Disable control for this pin
    uint16_t GPIO5:1;                   // 5 Pull-Up Disable control for this pin
    uint16_t GPIO6:1;                   // 6 Pull-Up Disable control for this pin
    uint16_t GPIO7:1;                   // 7 Pull-Up Disable control for this pin
    uint16_t GPIO8:1;                   // 8 Pull-Up Disable control for this pin
    uint16_t GPIO9:1;                   // 9 Pull-Up Disable control for this pin
    uint16_t GPIO10:1;                  // 10 Pull-Up Disable control for this pin
    uint16_t GPIO11:1;                  // 11 Pull-Up Disable control for this pin
    uint16_t GPIO12:1;                  // 12 Pull-Up Disable control for this pin
    uint16_t GPIO13:1;                  // 13 Pull-Up Disable control for this pin
    uint16_t GPIO14:1;                  // 14 Pull-Up Disable control for this pin
    uint16_t GPIO15:1;                  // 15 Pull-Up Disable control for this pin
    uint16_t GPIO16:1;                  // 16 Pull-Up Disable control for this pin
    uint16_t GPIO17:1;                  // 17 Pull-Up Disable control for this pin
    uint16_t GPIO18:1;                  // 18 Pull-Up Disable control for this pin
    uint16_t GPIO19:1;                  // 19 Pull-Up Disable control for this pin
    uint16_t GPIO20:1;                  // 20 Pull-Up Disable control for this pin
    uint16_t GPIO21:1;                  // 21 Pull-Up Disable control for this pin
    uint16_t GPIO22:1;                  // 22 Pull-Up Disable control for this pin
    uint16_t GPIO23:1;                  // 23 Pull-Up Disable control for this pin
    uint16_t GPIO24:1;                  // 24 Pull-Up Disable control for this pin
    uint16_t GPIO25:1;                  // 25 Pull-Up Disable control for this pin
    uint16_t GPIO26:1;                  // 26 Pull-Up Disable control for this pin
    uint16_t GPIO27:1;                  // 27 Pull-Up Disable control for this pin
    uint16_t GPIO28:1;                  // 28 Pull-Up Disable control for this pin
    uint16_t GPIO29:1;                  // 29 Pull-Up Disable control for this pin
    uint16_t GPIO30:1;                  // 30 Pull-Up Disable control for this pin
    uint16_t GPIO31:1;                  // 31 Pull-Up Disable control for this pin
};

union GPIO_GPAPUD_REG {
    uint32_t  all;
    struct  GPIO_GPAPUD_BITS  bit;
};

struct GPIO_GPAINV_BITS {               // bits description
    uint16_t GPIO0:1;                   // 0 Input inversion control for this pin
    uint16_t GPIO1:1;                   // 1 Input inversion control for this pin
    uint16_t GPIO2:1;                   // 2 Input inversion control for this pin
    uint16_t GPIO3:1;                   // 3 Input inversion control for this pin
    uint16_t GPIO4:1;                   // 4 Input inversion control for this pin
    uint16_t GPIO5:1;                   // 5 Input inversion control for this pin
    uint16_t GPIO6:1;                   // 6 Input inversion control for this pin
    uint16_t GPIO7:1;                   // 7 Input inversion control for this pin
    uint16_t GPIO8:1;                   // 8 Input inversion control for this pin
    uint16_t GPIO9:1;                   // 9 Input inversion control for this pin
    uint16_t GPIO10:1;                  // 10 Input inversion control for this pin
    uint16_t GPIO11:1;                  // 11 Input inversion control for this pin
    uint16_t GPIO12:1;                  // 12 Input inversion control for this pin
    uint16_t GPIO13:1;                  // 13 Input inversion control for this pin
    uint16_t GPIO14:1;                  // 14 Input inversion control for this pin
    uint16_t GPIO15:1;                  // 15 Input inversion control for this pin
    uint16_t GPIO16:1;                  // 16 Input inversion control for this pin
    uint16_t GPIO17:1;                  // 17 Input inversion control for this pin
    uint16_t GPIO18:1;                  // 18 Input inversion control for this pin
    uint16_t GPIO19:1;                  // 19 Input inversion control for this pin
    uint16_t GPIO20:1;                  // 20 Input inversion control for this pin
    uint16_t GPIO21:1;                  // 21 Input inversion control for this pin
    uint16_t GPIO22:1;                  // 22 Input inversion control for this pin
    uint16_t GPIO23:1;                  // 23 Input inversion control for this pin
    uint16_t GPIO24:1;                  // 24 Input inversion control for this pin
    uint16_t GPIO25:1;                  // 25 Input inversion control for this pin
    uint16_t GPIO26:1;                  // 26 Input inversion control for this pin
    uint16_t GPIO27:1;                  // 27 Input inversion control for this pin
    uint16_t GPIO28:1;                  // 28 Input inversion control for this pin
    uint16_t GPIO29:1;                  // 29 Input inversion control for this pin
    uint16_t GPIO30:1;                  // 30 Input inversion control for this pin
    uint16_t GPIO31:1;                  // 31 Input inversion control for this pin
};

union GPIO_GPAINV_REG {
    uint32_t  all;
    struct  GPIO_GPAINV_BITS  bit;
};

struct GPIO_GPAODR_BITS {               // bits description
    uint16_t GPIO0:1;                   // 0 Outpout Open-Drain control for this pin
    uint16_t GPIO1:1;                   // 1 Outpout Open-Drain control for this pin
    uint16_t GPIO2:1;                   // 2 Outpout Open-Drain control for this pin
    uint16_t GPIO3:1;                   // 3 Outpout Open-Drain control for this pin
    uint16_t GPIO4:1;                   // 4 Outpout Open-Drain control for this pin
    uint16_t GPIO5:1;                   // 5 Outpout Open-Drain control for this pin
    uint16_t GPIO6:1;                   // 6 Outpout Open-Drain control for this pin
    uint16_t GPIO7:1;                   // 7 Outpout Open-Drain control for this pin
    uint16_t GPIO8:1;                   // 8 Outpout Open-Drain control for this pin
    uint16_t GPIO9:1;                   // 9 Outpout Open-Drain control for this pin
    uint16_t GPIO10:1;                  // 10 Outpout Open-Drain control for this pin
    uint16_t GPIO11:1;                  // 11 Outpout Open-Drain control for this pin
    uint16_t GPIO12:1;                  // 12 Outpout Open-Drain control for this pin
    uint16_t GPIO13:1;                  // 13 Outpout Open-Drain control for this pin
    uint16_t GPIO14:1;                  // 14 Outpout Open-Drain control for this pin
    uint16_t GPIO15:1;                  // 15 Outpout Open-Drain control for this pin
    uint16_t GPIO16:1;                  // 16 Outpout Open-Drain control for this pin
    uint16_t GPIO17:1;                  // 17 Outpout Open-Drain control for this pin
    uint16_t GPIO18:1;                  // 18 Outpout Open-Drain control for this pin
    uint16_t GPIO19:1;                  // 19 Outpout Open-Drain control for this pin
    uint16_t GPIO20:1;                  // 20 Outpout Open-Drain control for this pin
    uint16_t GPIO21:1;                  // 21 Outpout Open-Drain control for this pin
    uint16_t GPIO22:1;                  // 22 Outpout Open-Drain control for this pin
    uint16_t GPIO23:1;                  // 23 Outpout Open-Drain control for this pin
    uint16_t GPIO24:1;                  // 24 Outpout Open-Drain control for this pin
    uint16_t GPIO25:1;                  // 25 Outpout Open-Drain control for this pin
    uint16_t GPIO26:1;                  // 26 Outpout Open-Drain control for this pin
    uint16_t GPIO27:1;                  // 27 Outpout Open-Drain control for this pin
    uint16_t GPIO28:1;                  // 28 Outpout Open-Drain control for this pin
    uint16_t GPIO29:1;                  // 29 Outpout Open-Drain control for this pin
    uint16_t GPIO30:1;                  // 30 Outpout Open-Drain control for this pin
    uint16_t GPIO31:1;                  // 31 Outpout Open-Drain control for this pin
};

union GPIO_GPAODR_REG {
    uint32_t  all;
    struct  GPIO_GPAODR_BITS  bit;
};

struct GPIO_GPAGMUX1_BITS {             // bits description
    uint16_t GPIO0:2;                   // 1:0 Defines pin-muxing selection for GPIO0
    uint16_t GPIO1:2;                   // 3:2 Defines pin-muxing selection for GPIO1
    uint16_t GPIO2:2;                   // 5:4 Defines pin-muxing selection for GPIO2
    uint16_t GPIO3:2;                   // 7:6 Defines pin-muxing selection for GPIO3
    uint16_t GPIO4:2;                   // 9:8 Defines pin-muxing selection for GPIO4
    uint16_t GPIO5:2;                   // 11:10 Defines pin-muxing selection for GPIO5
    uint16_t GPIO6:2;                   // 13:12 Defines pin-muxing selection for GPIO6
    uint16_t GPIO7:2;                   // 15:14 Defines pin-muxing selection for GPIO7
    uint16_t GPIO8:2;                   // 17:16 Defines pin-muxing selection for GPIO8
    uint16_t GPIO9:2;                   // 19:18 Defines pin-muxing selection for GPIO9
    uint16_t GPIO10:2;                  // 21:20 Defines pin-muxing selection for GPIO10
    uint16_t GPIO11:2;                  // 23:22 Defines pin-muxing selection for GPIO11
    uint16_t GPIO12:2;                  // 25:24 Defines pin-muxing selection for GPIO12
    uint16_t GPIO13:2;                  // 27:26 Defines pin-muxing selection for GPIO13
    uint16_t GPIO14:2;                  // 29:28 Defines pin-muxing selection for GPIO14
    uint16_t GPIO15:2;                  // 31:30 Defines pin-muxing selection for GPIO15
};

union GPIO_GPAGMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPAGMUX1_BITS  bit;
};

struct GPIO_GPAGMUX2_BITS {             // bits description
    uint16_t GPIO16:2;                  // 1:0 Defines pin-muxing selection for GPIO16
    uint16_t GPIO17:2;                  // 3:2 Defines pin-muxing selection for GPIO17
    uint16_t GPIO18:2;                  // 5:4 Defines pin-muxing selection for GPIO18
    uint16_t GPIO19:2;                  // 7:6 Defines pin-muxing selection for GPIO19
    uint16_t GPIO20:2;                  // 9:8 Defines pin-muxing selection for GPIO20
    uint16_t GPIO21:2;                  // 11:10 Defines pin-muxing selection for GPIO21
    uint16_t GPIO22:2;                  // 13:12 Defines pin-muxing selection for GPIO22
    uint16_t GPIO23:2;                  // 15:14 Defines pin-muxing selection for GPIO23
    uint16_t GPIO24:2;                  // 17:16 Defines pin-muxing selection for GPIO24
    uint16_t GPIO25:2;                  // 19:18 Defines pin-muxing selection for GPIO25
    uint16_t GPIO26:2;                  // 21:20 Defines pin-muxing selection for GPIO26
    uint16_t GPIO27:2;                  // 23:22 Defines pin-muxing selection for GPIO27
    uint16_t GPIO28:2;                  // 25:24 Defines pin-muxing selection for GPIO28
    uint16_t GPIO29:2;                  // 27:26 Defines pin-muxing selection for GPIO29
    uint16_t GPIO30:2;                  // 29:28 Defines pin-muxing selection for GPIO30
    uint16_t GPIO31:2;                  // 31:30 Defines pin-muxing selection for GPIO31
};

union GPIO_GPAGMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPAGMUX2_BITS  bit;
};

struct GPIO_GPACSEL1_BITS {             // bits description
    uint16_t GPIO0:4;                   // 3:0 GPIO0 Controller CPU Select
    uint16_t GPIO1:4;                   // 7:4 GPIO1 Controller CPU Select
    uint16_t GPIO2:4;                   // 11:8 GPIO2 Controller CPU Select
    uint16_t GPIO3:4;                   // 15:12 GPIO3 Controller CPU Select
    uint16_t GPIO4:4;                   // 19:16 GPIO4 Controller CPU Select
    uint16_t GPIO5:4;                   // 23:20 GPIO5 Controller CPU Select
    uint16_t GPIO6:4;                   // 27:24 GPIO6 Controller CPU Select
    uint16_t GPIO7:4;                   // 31:28 GPIO7 Controller CPU Select
};

union GPIO_GPACSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPACSEL1_BITS  bit;
};

struct GPIO_GPACSEL2_BITS {             // bits description
    uint16_t GPIO8:4;                   // 3:0 GPIO8 Controller CPU Select
    uint16_t GPIO9:4;                   // 7:4 GPIO9 Controller CPU Select
    uint16_t GPIO10:4;                  // 11:8 GPIO10 Controller CPU Select
    uint16_t GPIO11:4;                  // 15:12 GPIO11 Controller CPU Select
    uint16_t GPIO12:4;                  // 19:16 GPIO12 Controller CPU Select
    uint16_t GPIO13:4;                  // 23:20 GPIO13 Controller CPU Select
    uint16_t GPIO14:4;                  // 27:24 GPIO14 Controller CPU Select
    uint16_t GPIO15:4;                  // 31:28 GPIO15 Controller CPU Select
};

union GPIO_GPACSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPACSEL2_BITS  bit;
};

struct GPIO_GPACSEL3_BITS {             // bits description
    uint16_t GPIO16:4;                  // 3:0 GPIO16 Controller CPU Select
    uint16_t GPIO17:4;                  // 7:4 GPIO17 Controller CPU Select
    uint16_t GPIO18:4;                  // 11:8 GPIO18 Controller CPU Select
    uint16_t GPIO19:4;                  // 15:12 GPIO19 Controller CPU Select
    uint16_t GPIO20:4;                  // 19:16 GPIO20 Controller CPU Select
    uint16_t GPIO21:4;                  // 23:20 GPIO21 Controller CPU Select
    uint16_t GPIO22:4;                  // 27:24 GPIO22 Controller CPU Select
    uint16_t GPIO23:4;                  // 31:28 GPIO23 Controller CPU Select
};

union GPIO_GPACSEL3_REG {
    uint32_t  all;
    struct  GPIO_GPACSEL3_BITS  bit;
};

struct GPIO_GPACSEL4_BITS {             // bits description
    uint16_t GPIO24:4;                  // 3:0 GPIO24 Controller CPU Select
    uint16_t GPIO25:4;                  // 7:4 GPIO25 Controller CPU Select
    uint16_t GPIO26:4;                  // 11:8 GPIO26 Controller CPU Select
    uint16_t GPIO27:4;                  // 15:12 GPIO27 Controller CPU Select
    uint16_t GPIO28:4;                  // 19:16 GPIO28 Controller CPU Select
    uint16_t GPIO29:4;                  // 23:20 GPIO29 Controller CPU Select
    uint16_t GPIO30:4;                  // 27:24 GPIO30 Controller CPU Select
    uint16_t GPIO31:4;                  // 31:28 GPIO31 Controller CPU Select
};

union GPIO_GPACSEL4_REG {
    uint32_t  all;
    struct  GPIO_GPACSEL4_BITS  bit;
};

struct GPIO_GPALOCK_BITS {              // bits description
    uint16_t GPIO0:1;                   // 0 Configuration Lock bit for this pin
    uint16_t GPIO1:1;                   // 1 Configuration Lock bit for this pin
    uint16_t GPIO2:1;                   // 2 Configuration Lock bit for this pin
    uint16_t GPIO3:1;                   // 3 Configuration Lock bit for this pin
    uint16_t GPIO4:1;                   // 4 Configuration Lock bit for this pin
    uint16_t GPIO5:1;                   // 5 Configuration Lock bit for this pin
    uint16_t GPIO6:1;                   // 6 Configuration Lock bit for this pin
    uint16_t GPIO7:1;                   // 7 Configuration Lock bit for this pin
    uint16_t GPIO8:1;                   // 8 Configuration Lock bit for this pin
    uint16_t GPIO9:1;                   // 9 Configuration Lock bit for this pin
    uint16_t GPIO10:1;                  // 10 Configuration Lock bit for this pin
    uint16_t GPIO11:1;                  // 11 Configuration Lock bit for this pin
    uint16_t GPIO12:1;                  // 12 Configuration Lock bit for this pin
    uint16_t GPIO13:1;                  // 13 Configuration Lock bit for this pin
    uint16_t GPIO14:1;                  // 14 Configuration Lock bit for this pin
    uint16_t GPIO15:1;                  // 15 Configuration Lock bit for this pin
    uint16_t GPIO16:1;                  // 16 Configuration Lock bit for this pin
    uint16_t GPIO17:1;                  // 17 Configuration Lock bit for this pin
    uint16_t GPIO18:1;                  // 18 Configuration Lock bit for this pin
    uint16_t GPIO19:1;                  // 19 Configuration Lock bit for this pin
    uint16_t GPIO20:1;                  // 20 Configuration Lock bit for this pin
    uint16_t GPIO21:1;                  // 21 Configuration Lock bit for this pin
    uint16_t GPIO22:1;                  // 22 Configuration Lock bit for this pin
    uint16_t GPIO23:1;                  // 23 Configuration Lock bit for this pin
    uint16_t GPIO24:1;                  // 24 Configuration Lock bit for this pin
    uint16_t GPIO25:1;                  // 25 Configuration Lock bit for this pin
    uint16_t GPIO26:1;                  // 26 Configuration Lock bit for this pin
    uint16_t GPIO27:1;                  // 27 Configuration Lock bit for this pin
    uint16_t GPIO28:1;                  // 28 Configuration Lock bit for this pin
    uint16_t GPIO29:1;                  // 29 Configuration Lock bit for this pin
    uint16_t GPIO30:1;                  // 30 Configuration Lock bit for this pin
    uint16_t GPIO31:1;                  // 31 Configuration Lock bit for this pin
};

union GPIO_GPALOCK_REG {
    uint32_t  all;
    struct  GPIO_GPALOCK_BITS  bit;
};

struct GPIO_GPACR_BITS {                // bits description
    uint16_t GPIO0:1;                   // 0 Configuration lock commit bit for this pin
    uint16_t GPIO1:1;                   // 1 Configuration lock commit bit for this pin
    uint16_t GPIO2:1;                   // 2 Configuration lock commit bit for this pin
    uint16_t GPIO3:1;                   // 3 Configuration lock commit bit for this pin
    uint16_t GPIO4:1;                   // 4 Configuration lock commit bit for this pin
    uint16_t GPIO5:1;                   // 5 Configuration lock commit bit for this pin
    uint16_t GPIO6:1;                   // 6 Configuration lock commit bit for this pin
    uint16_t GPIO7:1;                   // 7 Configuration lock commit bit for this pin
    uint16_t GPIO8:1;                   // 8 Configuration lock commit bit for this pin
    uint16_t GPIO9:1;                   // 9 Configuration lock commit bit for this pin
    uint16_t GPIO10:1;                  // 10 Configuration lock commit bit for this pin
    uint16_t GPIO11:1;                  // 11 Configuration lock commit bit for this pin
    uint16_t GPIO12:1;                  // 12 Configuration lock commit bit for this pin
    uint16_t GPIO13:1;                  // 13 Configuration lock commit bit for this pin
    uint16_t GPIO14:1;                  // 14 Configuration lock commit bit for this pin
    uint16_t GPIO15:1;                  // 15 Configuration lock commit bit for this pin
    uint16_t GPIO16:1;                  // 16 Configuration lock commit bit for this pin
    uint16_t GPIO17:1;                  // 17 Configuration lock commit bit for this pin
    uint16_t GPIO18:1;                  // 18 Configuration lock commit bit for this pin
    uint16_t GPIO19:1;                  // 19 Configuration lock commit bit for this pin
    uint16_t GPIO20:1;                  // 20 Configuration lock commit bit for this pin
    uint16_t GPIO21:1;                  // 21 Configuration lock commit bit for this pin
    uint16_t GPIO22:1;                  // 22 Configuration lock commit bit for this pin
    uint16_t GPIO23:1;                  // 23 Configuration lock commit bit for this pin
    uint16_t GPIO24:1;                  // 24 Configuration lock commit bit for this pin
    uint16_t GPIO25:1;                  // 25 Configuration lock commit bit for this pin
    uint16_t GPIO26:1;                  // 26 Configuration lock commit bit for this pin
    uint16_t GPIO27:1;                  // 27 Configuration lock commit bit for this pin
    uint16_t GPIO28:1;                  // 28 Configuration lock commit bit for this pin
    uint16_t GPIO29:1;                  // 29 Configuration lock commit bit for this pin
    uint16_t GPIO30:1;                  // 30 Configuration lock commit bit for this pin
    uint16_t GPIO31:1;                  // 31 Configuration lock commit bit for this pin
};

union GPIO_GPACR_REG {
    uint32_t  all;
    struct  GPIO_GPACR_BITS  bit;
};

struct GPIO_GPBCTRL_BITS {              // bits description
    uint16_t QUALPRD0:8;                // 7:0 Qualification sampling period for GPIO32 to GPIO39
    uint16_t QUALPRD1:8;                // 15:8 Qualification sampling period for GPIO40 to GPIO47
    uint16_t QUALPRD2:8;                // 23:16 Qualification sampling period for GPIO48 to GPIO55
    uint16_t QUALPRD3:8;                // 31:24 Qualification sampling period for GPIO56 to GPIO63
};

union GPIO_GPBCTRL_REG {
    uint32_t  all;
    struct  GPIO_GPBCTRL_BITS  bit;
};

struct GPIO_GPBQSEL1_BITS {             // bits description
    uint16_t GPIO32:2;                  // 1:0 Select input qualification type for GPIO32
    uint16_t GPIO33:2;                  // 3:2 Select input qualification type for GPIO33
    uint16_t GPIO34:2;                  // 5:4 Select input qualification type for GPIO34
    uint16_t GPIO35:2;                  // 7:6 Select input qualification type for GPIO35
    uint16_t GPIO36:2;                  // 9:8 Select input qualification type for GPIO36
    uint16_t GPIO37:2;                  // 11:10 Select input qualification type for GPIO37
    uint16_t GPIO38:2;                  // 13:12 Select input qualification type for GPIO38
    uint16_t GPIO39:2;                  // 15:14 Select input qualification type for GPIO39
    uint16_t GPIO40:2;                  // 17:16 Select input qualification type for GPIO40
    uint16_t GPIO41:2;                  // 19:18 Select input qualification type for GPIO41
    uint16_t GPIO42:2;                  // 21:20 Select input qualification type for GPIO42
    uint16_t GPIO43:2;                  // 23:22 Select input qualification type for GPIO43
    uint16_t GPIO44:2;                  // 25:24 Select input qualification type for GPIO44
    uint16_t GPIO45:2;                  // 27:26 Select input qualification type for GPIO45
    uint16_t GPIO46:2;                  // 29:28 Select input qualification type for GPIO46
    uint16_t GPIO47:2;                  // 31:30 Select input qualification type for GPIO47
};

union GPIO_GPBQSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPBQSEL1_BITS  bit;
};

struct GPIO_GPBQSEL2_BITS {             // bits description
    uint16_t GPIO48:2;                  // 1:0 Select input qualification type for GPIO48
    uint16_t GPIO49:2;                  // 3:2 Select input qualification type for GPIO49
    uint16_t GPIO50:2;                  // 5:4 Select input qualification type for GPIO50
    uint16_t GPIO51:2;                  // 7:6 Select input qualification type for GPIO51
    uint16_t GPIO52:2;                  // 9:8 Select input qualification type for GPIO52
    uint16_t GPIO53:2;                  // 11:10 Select input qualification type for GPIO53
    uint16_t GPIO54:2;                  // 13:12 Select input qualification type for GPIO54
    uint16_t GPIO55:2;                  // 15:14 Select input qualification type for GPIO55
    uint16_t GPIO56:2;                  // 17:16 Select input qualification type for GPIO56
    uint16_t GPIO57:2;                  // 19:18 Select input qualification type for GPIO57
    uint16_t GPIO58:2;                  // 21:20 Select input qualification type for GPIO58
    uint16_t GPIO59:2;                  // 23:22 Select input qualification type for GPIO59
    uint16_t GPIO60:2;                  // 25:24 Select input qualification type for GPIO60
    uint16_t GPIO61:2;                  // 27:26 Select input qualification type for GPIO61
    uint16_t GPIO62:2;                  // 29:28 Select input qualification type for GPIO62
    uint16_t GPIO63:2;                  // 31:30 Select input qualification type for GPIO63
};

union GPIO_GPBQSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPBQSEL2_BITS  bit;
};

struct GPIO_GPBMUX1_BITS {              // bits description
    uint16_t GPIO32:2;                  // 1:0 Defines pin-muxing selection for GPIO32
    uint16_t GPIO33:2;                  // 3:2 Defines pin-muxing selection for GPIO33
    uint16_t GPIO34:2;                  // 5:4 Defines pin-muxing selection for GPIO34
    uint16_t GPIO35:2;                  // 7:6 Defines pin-muxing selection for GPIO35
    uint16_t GPIO36:2;                  // 9:8 Defines pin-muxing selection for GPIO36
    uint16_t GPIO37:2;                  // 11:10 Defines pin-muxing selection for GPIO37
    uint16_t GPIO38:2;                  // 13:12 Defines pin-muxing selection for GPIO38
    uint16_t GPIO39:2;                  // 15:14 Defines pin-muxing selection for GPIO39
    uint16_t GPIO40:2;                  // 17:16 Defines pin-muxing selection for GPIO40
    uint16_t GPIO41:2;                  // 19:18 Defines pin-muxing selection for GPIO41
    uint16_t GPIO42:2;                  // 21:20 Defines pin-muxing selection for GPIO42
    uint16_t GPIO43:2;                  // 23:22 Defines pin-muxing selection for GPIO43
    uint16_t GPIO44:2;                  // 25:24 Defines pin-muxing selection for GPIO44
    uint16_t GPIO45:2;                  // 27:26 Defines pin-muxing selection for GPIO45
    uint16_t GPIO46:2;                  // 29:28 Defines pin-muxing selection for GPIO46
    uint16_t GPIO47:2;                  // 31:30 Defines pin-muxing selection for GPIO47
};

union GPIO_GPBMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPBMUX1_BITS  bit;
};

struct GPIO_GPBMUX2_BITS {              // bits description
    uint16_t GPIO48:2;                  // 1:0 Defines pin-muxing selection for GPIO48
    uint16_t GPIO49:2;                  // 3:2 Defines pin-muxing selection for GPIO49
    uint16_t GPIO50:2;                  // 5:4 Defines pin-muxing selection for GPIO50
    uint16_t GPIO51:2;                  // 7:6 Defines pin-muxing selection for GPIO51
    uint16_t GPIO52:2;                  // 9:8 Defines pin-muxing selection for GPIO52
    uint16_t GPIO53:2;                  // 11:10 Defines pin-muxing selection for GPIO53
    uint16_t GPIO54:2;                  // 13:12 Defines pin-muxing selection for GPIO54
    uint16_t GPIO55:2;                  // 15:14 Defines pin-muxing selection for GPIO55
    uint16_t GPIO56:2;                  // 17:16 Defines pin-muxing selection for GPIO56
    uint16_t GPIO57:2;                  // 19:18 Defines pin-muxing selection for GPIO57
    uint16_t GPIO58:2;                  // 21:20 Defines pin-muxing selection for GPIO58
    uint16_t GPIO59:2;                  // 23:22 Defines pin-muxing selection for GPIO59
    uint16_t GPIO60:2;                  // 25:24 Defines pin-muxing selection for GPIO60
    uint16_t GPIO61:2;                  // 27:26 Defines pin-muxing selection for GPIO61
    uint16_t GPIO62:2;                  // 29:28 Defines pin-muxing selection for GPIO62
    uint16_t GPIO63:2;                  // 31:30 Defines pin-muxing selection for GPIO63
};

union GPIO_GPBMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPBMUX2_BITS  bit;
};

struct GPIO_GPBPUD_BITS {               // bits description
    uint16_t GPIO32:1;                  // 0 Pull-Up Disable control for this pin
    uint16_t GPIO33:1;                  // 1 Pull-Up Disable control for this pin
    uint16_t GPIO34:1;                  // 2 Pull-Up Disable control for this pin
    uint16_t GPIO35:1;                  // 3 Pull-Up Disable control for this pin
    uint16_t GPIO36:1;                  // 4 Pull-Up Disable control for this pin
    uint16_t GPIO37:1;                  // 5 Pull-Up Disable control for this pin
    uint16_t GPIO38:1;                  // 6 Pull-Up Disable control for this pin
    uint16_t GPIO39:1;                  // 7 Pull-Up Disable control for this pin
    uint16_t GPIO40:1;                  // 8 Pull-Up Disable control for this pin
    uint16_t GPIO41:1;                  // 9 Pull-Up Disable control for this pin
    uint16_t GPIO42:1;                  // 10 Pull-Up Disable control for this pin
    uint16_t GPIO43:1;                  // 11 Pull-Up Disable control for this pin
    uint16_t GPIO44:1;                  // 12 Pull-Up Disable control for this pin
    uint16_t GPIO45:1;                  // 13 Pull-Up Disable control for this pin
    uint16_t GPIO46:1;                  // 14 Pull-Up Disable control for this pin
    uint16_t GPIO47:1;                  // 15 Pull-Up Disable control for this pin
    uint16_t GPIO48:1;                  // 16 Pull-Up Disable control for this pin
    uint16_t GPIO49:1;                  // 17 Pull-Up Disable control for this pin
    uint16_t GPIO50:1;                  // 18 Pull-Up Disable control for this pin
    uint16_t GPIO51:1;                  // 19 Pull-Up Disable control for this pin
    uint16_t GPIO52:1;                  // 20 Pull-Up Disable control for this pin
    uint16_t GPIO53:1;                  // 21 Pull-Up Disable control for this pin
    uint16_t GPIO54:1;                  // 22 Pull-Up Disable control for this pin
    uint16_t GPIO55:1;                  // 23 Pull-Up Disable control for this pin
    uint16_t GPIO56:1;                  // 24 Pull-Up Disable control for this pin
    uint16_t GPIO57:1;                  // 25 Pull-Up Disable control for this pin
    uint16_t GPIO58:1;                  // 26 Pull-Up Disable control for this pin
    uint16_t GPIO59:1;                  // 27 Pull-Up Disable control for this pin
    uint16_t GPIO60:1;                  // 28 Pull-Up Disable control for this pin
    uint16_t GPIO61:1;                  // 29 Pull-Up Disable control for this pin
    uint16_t GPIO62:1;                  // 30 Pull-Up Disable control for this pin
    uint16_t GPIO63:1;                  // 31 Pull-Up Disable control for this pin
};

union GPIO_GPBPUD_REG {
    uint32_t  all;
    struct  GPIO_GPBPUD_BITS  bit;
};

struct GPIO_GPBINV_BITS {               // bits description
    uint16_t GPIO32:1;                  // 0 Input inversion control for this pin
    uint16_t GPIO33:1;                  // 1 Input inversion control for this pin
    uint16_t GPIO34:1;                  // 2 Input inversion control for this pin
    uint16_t GPIO35:1;                  // 3 Input inversion control for this pin
    uint16_t GPIO36:1;                  // 4 Input inversion control for this pin
    uint16_t GPIO37:1;                  // 5 Input inversion control for this pin
    uint16_t GPIO38:1;                  // 6 Input inversion control for this pin
    uint16_t GPIO39:1;                  // 7 Input inversion control for this pin
    uint16_t GPIO40:1;                  // 8 Input inversion control for this pin
    uint16_t GPIO41:1;                  // 9 Input inversion control for this pin
    uint16_t GPIO42:1;                  // 10 Input inversion control for this pin
    uint16_t GPIO43:1;                  // 11 Input inversion control for this pin
    uint16_t GPIO44:1;                  // 12 Input inversion control for this pin
    uint16_t GPIO45:1;                  // 13 Input inversion control for this pin
    uint16_t GPIO46:1;                  // 14 Input inversion control for this pin
    uint16_t GPIO47:1;                  // 15 Input inversion control for this pin
    uint16_t GPIO48:1;                  // 16 Input inversion control for this pin
    uint16_t GPIO49:1;                  // 17 Input inversion control for this pin
    uint16_t GPIO50:1;                  // 18 Input inversion control for this pin
    uint16_t GPIO51:1;                  // 19 Input inversion control for this pin
    uint16_t GPIO52:1;                  // 20 Input inversion control for this pin
    uint16_t GPIO53:1;                  // 21 Input inversion control for this pin
    uint16_t GPIO54:1;                  // 22 Input inversion control for this pin
    uint16_t GPIO55:1;                  // 23 Input inversion control for this pin
    uint16_t GPIO56:1;                  // 24 Input inversion control for this pin
    uint16_t GPIO57:1;                  // 25 Input inversion control for this pin
    uint16_t GPIO58:1;                  // 26 Input inversion control for this pin
    uint16_t GPIO59:1;                  // 27 Input inversion control for this pin
    uint16_t GPIO60:1;                  // 28 Input inversion control for this pin
    uint16_t GPIO61:1;                  // 29 Input inversion control for this pin
    uint16_t GPIO62:1;                  // 30 Input inversion control for this pin
    uint16_t GPIO63:1;                  // 31 Input inversion control for this pin
};

union GPIO_GPBINV_REG {
    uint32_t  all;
    struct  GPIO_GPBINV_BITS  bit;
};

struct GPIO_GPBODR_BITS {               // bits description
    uint16_t GPIO32:1;                  // 0 Outpout Open-Drain control for this pin
    uint16_t GPIO33:1;                  // 1 Outpout Open-Drain control for this pin
    uint16_t GPIO34:1;                  // 2 Outpout Open-Drain control for this pin
    uint16_t GPIO35:1;                  // 3 Outpout Open-Drain control for this pin
    uint16_t GPIO36:1;                  // 4 Outpout Open-Drain control for this pin
    uint16_t GPIO37:1;                  // 5 Outpout Open-Drain control for this pin
    uint16_t GPIO38:1;                  // 6 Outpout Open-Drain control for this pin
    uint16_t GPIO39:1;                  // 7 Outpout Open-Drain control for this pin
    uint16_t GPIO40:1;                  // 8 Outpout Open-Drain control for this pin
    uint16_t GPIO41:1;                  // 9 Outpout Open-Drain control for this pin
    uint16_t GPIO42:1;                  // 10 Outpout Open-Drain control for this pin
    uint16_t GPIO43:1;                  // 11 Outpout Open-Drain control for this pin
    uint16_t GPIO44:1;                  // 12 Outpout Open-Drain control for this pin
    uint16_t GPIO45:1;                  // 13 Outpout Open-Drain control for this pin
    uint16_t GPIO46:1;                  // 14 Outpout Open-Drain control for this pin
    uint16_t GPIO47:1;                  // 15 Outpout Open-Drain control for this pin
    uint16_t GPIO48:1;                  // 16 Outpout Open-Drain control for this pin
    uint16_t GPIO49:1;                  // 17 Outpout Open-Drain control for this pin
    uint16_t GPIO50:1;                  // 18 Outpout Open-Drain control for this pin
    uint16_t GPIO51:1;                  // 19 Outpout Open-Drain control for this pin
    uint16_t GPIO52:1;                  // 20 Outpout Open-Drain control for this pin
    uint16_t GPIO53:1;                  // 21 Outpout Open-Drain control for this pin
    uint16_t GPIO54:1;                  // 22 Outpout Open-Drain control for this pin
    uint16_t GPIO55:1;                  // 23 Outpout Open-Drain control for this pin
    uint16_t GPIO56:1;                  // 24 Outpout Open-Drain control for this pin
    uint16_t GPIO57:1;                  // 25 Outpout Open-Drain control for this pin
    uint16_t GPIO58:1;                  // 26 Outpout Open-Drain control for this pin
    uint16_t GPIO59:1;                  // 27 Outpout Open-Drain control for this pin
    uint16_t GPIO60:1;                  // 28 Outpout Open-Drain control for this pin
    uint16_t GPIO61:1;                  // 29 Outpout Open-Drain control for this pin
    uint16_t GPIO62:1;                  // 30 Outpout Open-Drain control for this pin
    uint16_t GPIO63:1;                  // 31 Outpout Open-Drain control for this pin
};

union GPIO_GPBODR_REG {
    uint32_t  all;
    struct  GPIO_GPBODR_BITS  bit;
};

struct GPIO_GPBGMUX1_BITS {             // bits description
    uint16_t GPIO32:2;                  // 1:0 Defines pin-muxing selection for GPIO32
    uint16_t GPIO33:2;                  // 3:2 Defines pin-muxing selection for GPIO33
    uint16_t GPIO34:2;                  // 5:4 Defines pin-muxing selection for GPIO34
    uint16_t GPIO35:2;                  // 7:6 Defines pin-muxing selection for GPIO35
    uint16_t GPIO36:2;                  // 9:8 Defines pin-muxing selection for GPIO36
    uint16_t GPIO37:2;                  // 11:10 Defines pin-muxing selection for GPIO37
    uint16_t GPIO38:2;                  // 13:12 Defines pin-muxing selection for GPIO38
    uint16_t GPIO39:2;                  // 15:14 Defines pin-muxing selection for GPIO39
    uint16_t GPIO40:2;                  // 17:16 Defines pin-muxing selection for GPIO40
    uint16_t GPIO41:2;                  // 19:18 Defines pin-muxing selection for GPIO41
    uint16_t GPIO42:2;                  // 21:20 Defines pin-muxing selection for GPIO42
    uint16_t GPIO43:2;                  // 23:22 Defines pin-muxing selection for GPIO43
    uint16_t GPIO44:2;                  // 25:24 Defines pin-muxing selection for GPIO44
    uint16_t GPIO45:2;                  // 27:26 Defines pin-muxing selection for GPIO45
    uint16_t GPIO46:2;                  // 29:28 Defines pin-muxing selection for GPIO46
    uint16_t GPIO47:2;                  // 31:30 Defines pin-muxing selection for GPIO47
};

union GPIO_GPBGMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPBGMUX1_BITS  bit;
};

struct GPIO_GPBGMUX2_BITS {             // bits description
    uint16_t GPIO48:2;                  // 1:0 Defines pin-muxing selection for GPIO48
    uint16_t GPIO49:2;                  // 3:2 Defines pin-muxing selection for GPIO49
    uint16_t GPIO50:2;                  // 5:4 Defines pin-muxing selection for GPIO50
    uint16_t GPIO51:2;                  // 7:6 Defines pin-muxing selection for GPIO51
    uint16_t GPIO52:2;                  // 9:8 Defines pin-muxing selection for GPIO52
    uint16_t GPIO53:2;                  // 11:10 Defines pin-muxing selection for GPIO53
    uint16_t GPIO54:2;                  // 13:12 Defines pin-muxing selection for GPIO54
    uint16_t GPIO55:2;                  // 15:14 Defines pin-muxing selection for GPIO55
    uint16_t GPIO56:2;                  // 17:16 Defines pin-muxing selection for GPIO56
    uint16_t GPIO57:2;                  // 19:18 Defines pin-muxing selection for GPIO57
    uint16_t GPIO58:2;                  // 21:20 Defines pin-muxing selection for GPIO58
    uint16_t GPIO59:2;                  // 23:22 Defines pin-muxing selection for GPIO59
    uint16_t GPIO60:2;                  // 25:24 Defines pin-muxing selection for GPIO60
    uint16_t GPIO61:2;                  // 27:26 Defines pin-muxing selection for GPIO61
    uint16_t GPIO62:2;                  // 29:28 Defines pin-muxing selection for GPIO62
    uint16_t GPIO63:2;                  // 31:30 Defines pin-muxing selection for GPIO63
};

union GPIO_GPBGMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPBGMUX2_BITS  bit;
};

struct GPIO_GPBCSEL1_BITS {             // bits description
    uint16_t GPIO32:4;                  // 3:0 GPIO32 Controller CPU Select
    uint16_t GPIO33:4;                  // 7:4 GPIO33 Controller CPU Select
    uint16_t GPIO34:4;                  // 11:8 GPIO34 Controller CPU Select
    uint16_t GPIO35:4;                  // 15:12 GPIO35 Controller CPU Select
    uint16_t GPIO36:4;                  // 19:16 GPIO36 Controller CPU Select
    uint16_t GPIO37:4;                  // 23:20 GPIO37 Controller CPU Select
    uint16_t GPIO38:4;                  // 27:24 GPIO38 Controller CPU Select
    uint16_t GPIO39:4;                  // 31:28 GPIO39 Controller CPU Select
};

union GPIO_GPBCSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPBCSEL1_BITS  bit;
};

struct GPIO_GPBCSEL2_BITS {             // bits description
    uint16_t GPIO40:4;                  // 3:0 GPIO40 Controller CPU Select
    uint16_t GPIO41:4;                  // 7:4 GPIO41 Controller CPU Select
    uint16_t GPIO42:4;                  // 11:8 GPIO42 Controller CPU Select
    uint16_t GPIO43:4;                  // 15:12 GPIO43 Controller CPU Select
    uint16_t GPIO44:4;                  // 19:16 GPIO44 Controller CPU Select
    uint16_t GPIO45:4;                  // 23:20 GPIO45 Controller CPU Select
    uint16_t GPIO46:4;                  // 27:24 GPIO46 Controller CPU Select
    uint16_t GPIO47:4;                  // 31:28 GPIO47 Controller CPU Select
};

union GPIO_GPBCSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPBCSEL2_BITS  bit;
};

struct GPIO_GPBCSEL3_BITS {             // bits description
    uint16_t GPIO48:4;                  // 3:0 GPIO48 Controller CPU Select
    uint16_t GPIO49:4;                  // 7:4 GPIO49 Controller CPU Select
    uint16_t GPIO50:4;                  // 11:8 GPIO50 Controller CPU Select
    uint16_t GPIO51:4;                  // 15:12 GPIO51 Controller CPU Select
    uint16_t GPIO52:4;                  // 19:16 GPIO52 Controller CPU Select
    uint16_t GPIO53:4;                  // 23:20 GPIO53 Controller CPU Select
    uint16_t GPIO54:4;                  // 27:24 GPIO54 Controller CPU Select
    uint16_t GPIO55:4;                  // 31:28 GPIO55 Controller CPU Select
};

union GPIO_GPBCSEL3_REG {
    uint32_t  all;
    struct  GPIO_GPBCSEL3_BITS  bit;
};

struct GPIO_GPBCSEL4_BITS {             // bits description
    uint16_t GPIO56:4;                  // 3:0 GPIO56 Controller CPU Select
    uint16_t GPIO57:4;                  // 7:4 GPIO57 Controller CPU Select
    uint16_t GPIO58:4;                  // 11:8 GPIO58 Controller CPU Select
    uint16_t GPIO59:4;                  // 15:12 GPIO59 Controller CPU Select
    uint16_t GPIO60:4;                  // 19:16 GPIO60 Controller CPU Select
    uint16_t GPIO61:4;                  // 23:20 GPIO61 Controller CPU Select
    uint16_t GPIO62:4;                  // 27:24 GPIO62 Controller CPU Select
    uint16_t GPIO63:4;                  // 31:28 GPIO63 Controller CPU Select
};

union GPIO_GPBCSEL4_REG {
    uint32_t  all;
    struct  GPIO_GPBCSEL4_BITS  bit;
};

struct GPIO_GPBLOCK_BITS {              // bits description
    uint16_t GPIO32:1;                  // 0 Configuration Lock bit for this pin
    uint16_t GPIO33:1;                  // 1 Configuration Lock bit for this pin
    uint16_t GPIO34:1;                  // 2 Configuration Lock bit for this pin
    uint16_t GPIO35:1;                  // 3 Configuration Lock bit for this pin
    uint16_t GPIO36:1;                  // 4 Configuration Lock bit for this pin
    uint16_t GPIO37:1;                  // 5 Configuration Lock bit for this pin
    uint16_t GPIO38:1;                  // 6 Configuration Lock bit for this pin
    uint16_t GPIO39:1;                  // 7 Configuration Lock bit for this pin
    uint16_t GPIO40:1;                  // 8 Configuration Lock bit for this pin
    uint16_t GPIO41:1;                  // 9 Configuration Lock bit for this pin
    uint16_t GPIO42:1;                  // 10 Configuration Lock bit for this pin
    uint16_t GPIO43:1;                  // 11 Configuration Lock bit for this pin
    uint16_t GPIO44:1;                  // 12 Configuration Lock bit for this pin
    uint16_t GPIO45:1;                  // 13 Configuration Lock bit for this pin
    uint16_t GPIO46:1;                  // 14 Configuration Lock bit for this pin
    uint16_t GPIO47:1;                  // 15 Configuration Lock bit for this pin
    uint16_t GPIO48:1;                  // 16 Configuration Lock bit for this pin
    uint16_t GPIO49:1;                  // 17 Configuration Lock bit for this pin
    uint16_t GPIO50:1;                  // 18 Configuration Lock bit for this pin
    uint16_t GPIO51:1;                  // 19 Configuration Lock bit for this pin
    uint16_t GPIO52:1;                  // 20 Configuration Lock bit for this pin
    uint16_t GPIO53:1;                  // 21 Configuration Lock bit for this pin
    uint16_t GPIO54:1;                  // 22 Configuration Lock bit for this pin
    uint16_t GPIO55:1;                  // 23 Configuration Lock bit for this pin
    uint16_t GPIO56:1;                  // 24 Configuration Lock bit for this pin
    uint16_t GPIO57:1;                  // 25 Configuration Lock bit for this pin
    uint16_t GPIO58:1;                  // 26 Configuration Lock bit for this pin
    uint16_t GPIO59:1;                  // 27 Configuration Lock bit for this pin
    uint16_t GPIO60:1;                  // 28 Configuration Lock bit for this pin
    uint16_t GPIO61:1;                  // 29 Configuration Lock bit for this pin
    uint16_t GPIO62:1;                  // 30 Configuration Lock bit for this pin
    uint16_t GPIO63:1;                  // 31 Configuration Lock bit for this pin
};

union GPIO_GPBLOCK_REG {
    uint32_t  all;
    struct  GPIO_GPBLOCK_BITS  bit;
};

struct GPIO_GPBCR_BITS {                // bits description
    uint16_t GPIO32:1;                  // 0 Configuration lock commit bit for this pin
    uint16_t GPIO33:1;                  // 1 Configuration lock commit bit for this pin
    uint16_t GPIO34:1;                  // 2 Configuration lock commit bit for this pin
    uint16_t GPIO35:1;                  // 3 Configuration lock commit bit for this pin
    uint16_t GPIO36:1;                  // 4 Configuration lock commit bit for this pin
    uint16_t GPIO37:1;                  // 5 Configuration lock commit bit for this pin
    uint16_t GPIO38:1;                  // 6 Configuration lock commit bit for this pin
    uint16_t GPIO39:1;                  // 7 Configuration lock commit bit for this pin
    uint16_t GPIO40:1;                  // 8 Configuration lock commit bit for this pin
    uint16_t GPIO41:1;                  // 9 Configuration lock commit bit for this pin
    uint16_t GPIO42:1;                  // 10 Configuration lock commit bit for this pin
    uint16_t GPIO43:1;                  // 11 Configuration lock commit bit for this pin
    uint16_t GPIO44:1;                  // 12 Configuration lock commit bit for this pin
    uint16_t GPIO45:1;                  // 13 Configuration lock commit bit for this pin
    uint16_t GPIO46:1;                  // 14 Configuration lock commit bit for this pin
    uint16_t GPIO47:1;                  // 15 Configuration lock commit bit for this pin
    uint16_t GPIO48:1;                  // 16 Configuration lock commit bit for this pin
    uint16_t GPIO49:1;                  // 17 Configuration lock commit bit for this pin
    uint16_t GPIO50:1;                  // 18 Configuration lock commit bit for this pin
    uint16_t GPIO51:1;                  // 19 Configuration lock commit bit for this pin
    uint16_t GPIO52:1;                  // 20 Configuration lock commit bit for this pin
    uint16_t GPIO53:1;                  // 21 Configuration lock commit bit for this pin
    uint16_t GPIO54:1;                  // 22 Configuration lock commit bit for this pin
    uint16_t GPIO55:1;                  // 23 Configuration lock commit bit for this pin
    uint16_t GPIO56:1;                  // 24 Configuration lock commit bit for this pin
    uint16_t GPIO57:1;                  // 25 Configuration lock commit bit for this pin
    uint16_t GPIO58:1;                  // 26 Configuration lock commit bit for this pin
    uint16_t GPIO59:1;                  // 27 Configuration lock commit bit for this pin
    uint16_t GPIO60:1;                  // 28 Configuration lock commit bit for this pin
    uint16_t GPIO61:1;                  // 29 Configuration lock commit bit for this pin
    uint16_t GPIO62:1;                  // 30 Configuration lock commit bit for this pin
    uint16_t GPIO63:1;                  // 31 Configuration lock commit bit for this pin
};

union GPIO_GPBCR_REG {
    uint32_t  all;
    struct  GPIO_GPBCR_BITS  bit;
};

struct GPIO_GPCCTRL_BITS {              // bits description
    uint16_t QUALPRD0:8;                // 7:0 Qualification sampling period for GPIO64 to GPIO71
    uint16_t QUALPRD1:8;                // 15:8 Qualification sampling period for GPIO72 to GPIO79
    uint16_t QUALPRD2:8;                // 23:16 Qualification sampling period for GPIO80 to GPIO87
    uint16_t QUALPRD3:8;                // 31:24 Qualification sampling period for GPIO88 to GPIO95
};

union GPIO_GPCCTRL_REG {
    uint32_t  all;
    struct  GPIO_GPCCTRL_BITS  bit;
};

struct GPIO_GPCQSEL1_BITS {             // bits description
    uint16_t GPIO64:2;                  // 1:0 Select input qualification type for GPIO64
    uint16_t GPIO65:2;                  // 3:2 Select input qualification type for GPIO65
    uint16_t GPIO66:2;                  // 5:4 Select input qualification type for GPIO66
    uint16_t GPIO67:2;                  // 7:6 Select input qualification type for GPIO67
    uint16_t GPIO68:2;                  // 9:8 Select input qualification type for GPIO68
    uint16_t GPIO69:2;                  // 11:10 Select input qualification type for GPIO69
    uint16_t GPIO70:2;                  // 13:12 Select input qualification type for GPIO70
    uint16_t GPIO71:2;                  // 15:14 Select input qualification type for GPIO71
    uint16_t GPIO72:2;                  // 17:16 Select input qualification type for GPIO72
    uint16_t GPIO73:2;                  // 19:18 Select input qualification type for GPIO73
    uint16_t GPIO74:2;                  // 21:20 Select input qualification type for GPIO74
    uint16_t GPIO75:2;                  // 23:22 Select input qualification type for GPIO75
    uint16_t GPIO76:2;                  // 25:24 Select input qualification type for GPIO76
    uint16_t GPIO77:2;                  // 27:26 Select input qualification type for GPIO77
    uint16_t GPIO78:2;                  // 29:28 Select input qualification type for GPIO78
    uint16_t GPIO79:2;                  // 31:30 Select input qualification type for GPIO79
};

union GPIO_GPCQSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPCQSEL1_BITS  bit;
};

struct GPIO_GPCQSEL2_BITS {             // bits description
    uint16_t GPIO80:2;                  // 1:0 Select input qualification type for GPIO80
    uint16_t GPIO81:2;                  // 3:2 Select input qualification type for GPIO81
    uint16_t GPIO82:2;                  // 5:4 Select input qualification type for GPIO82
    uint16_t GPIO83:2;                  // 7:6 Select input qualification type for GPIO83
    uint16_t GPIO84:2;                  // 9:8 Select input qualification type for GPIO84
    uint16_t GPIO85:2;                  // 11:10 Select input qualification type for GPIO85
    uint16_t GPIO86:2;                  // 13:12 Select input qualification type for GPIO86
    uint16_t GPIO87:2;                  // 15:14 Select input qualification type for GPIO87
    uint16_t GPIO88:2;                  // 17:16 Select input qualification type for GPIO88
    uint16_t GPIO89:2;                  // 19:18 Select input qualification type for GPIO89
    uint16_t GPIO90:2;                  // 21:20 Select input qualification type for GPIO90
    uint16_t GPIO91:2;                  // 23:22 Select input qualification type for GPIO91
    uint16_t GPIO92:2;                  // 25:24 Select input qualification type for GPIO92
    uint16_t GPIO93:2;                  // 27:26 Select input qualification type for GPIO93
    uint16_t GPIO94:2;                  // 29:28 Select input qualification type for GPIO94
    uint16_t GPIO95:2;                  // 31:30 Select input qualification type for GPIO95
};

union GPIO_GPCQSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPCQSEL2_BITS  bit;
};

struct GPIO_GPCMUX1_BITS {              // bits description
    uint16_t GPIO64:2;                  // 1:0 Defines pin-muxing selection for GPIO64
    uint16_t GPIO65:2;                  // 3:2 Defines pin-muxing selection for GPIO65
    uint16_t GPIO66:2;                  // 5:4 Defines pin-muxing selection for GPIO66
    uint16_t GPIO67:2;                  // 7:6 Defines pin-muxing selection for GPIO67
    uint16_t GPIO68:2;                  // 9:8 Defines pin-muxing selection for GPIO68
    uint16_t GPIO69:2;                  // 11:10 Defines pin-muxing selection for GPIO69
    uint16_t GPIO70:2;                  // 13:12 Defines pin-muxing selection for GPIO70
    uint16_t GPIO71:2;                  // 15:14 Defines pin-muxing selection for GPIO71
    uint16_t GPIO72:2;                  // 17:16 Defines pin-muxing selection for GPIO72
    uint16_t GPIO73:2;                  // 19:18 Defines pin-muxing selection for GPIO73
    uint16_t GPIO74:2;                  // 21:20 Defines pin-muxing selection for GPIO74
    uint16_t GPIO75:2;                  // 23:22 Defines pin-muxing selection for GPIO75
    uint16_t GPIO76:2;                  // 25:24 Defines pin-muxing selection for GPIO76
    uint16_t GPIO77:2;                  // 27:26 Defines pin-muxing selection for GPIO77
    uint16_t GPIO78:2;                  // 29:28 Defines pin-muxing selection for GPIO78
    uint16_t GPIO79:2;                  // 31:30 Defines pin-muxing selection for GPIO79
};

union GPIO_GPCMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPCMUX1_BITS  bit;
};

struct GPIO_GPCMUX2_BITS {              // bits description
    uint16_t GPIO80:2;                  // 1:0 Defines pin-muxing selection for GPIO80
    uint16_t GPIO81:2;                  // 3:2 Defines pin-muxing selection for GPIO81
    uint16_t GPIO82:2;                  // 5:4 Defines pin-muxing selection for GPIO82
    uint16_t GPIO83:2;                  // 7:6 Defines pin-muxing selection for GPIO83
    uint16_t GPIO84:2;                  // 9:8 Defines pin-muxing selection for GPIO84
    uint16_t GPIO85:2;                  // 11:10 Defines pin-muxing selection for GPIO85
    uint16_t GPIO86:2;                  // 13:12 Defines pin-muxing selection for GPIO86
    uint16_t GPIO87:2;                  // 15:14 Defines pin-muxing selection for GPIO87
    uint16_t GPIO88:2;                  // 17:16 Defines pin-muxing selection for GPIO88
    uint16_t GPIO89:2;                  // 19:18 Defines pin-muxing selection for GPIO89
    uint16_t GPIO90:2;                  // 21:20 Defines pin-muxing selection for GPIO90
    uint16_t GPIO91:2;                  // 23:22 Defines pin-muxing selection for GPIO91
    uint16_t GPIO92:2;                  // 25:24 Defines pin-muxing selection for GPIO92
    uint16_t GPIO93:2;                  // 27:26 Defines pin-muxing selection for GPIO93
    uint16_t GPIO94:2;                  // 29:28 Defines pin-muxing selection for GPIO94
    uint16_t GPIO95:2;                  // 31:30 Defines pin-muxing selection for GPIO95
};

union GPIO_GPCMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPCMUX2_BITS  bit;
};

struct GPIO_GPCPUD_BITS {               // bits description
    uint16_t GPIO64:1;                  // 0 Pull-Up Disable control for this pin
    uint16_t GPIO65:1;                  // 1 Pull-Up Disable control for this pin
    uint16_t GPIO66:1;                  // 2 Pull-Up Disable control for this pin
    uint16_t GPIO67:1;                  // 3 Pull-Up Disable control for this pin
    uint16_t GPIO68:1;                  // 4 Pull-Up Disable control for this pin
    uint16_t GPIO69:1;                  // 5 Pull-Up Disable control for this pin
    uint16_t GPIO70:1;                  // 6 Pull-Up Disable control for this pin
    uint16_t GPIO71:1;                  // 7 Pull-Up Disable control for this pin
    uint16_t GPIO72:1;                  // 8 Pull-Up Disable control for this pin
    uint16_t GPIO73:1;                  // 9 Pull-Up Disable control for this pin
    uint16_t GPIO74:1;                  // 10 Pull-Up Disable control for this pin
    uint16_t GPIO75:1;                  // 11 Pull-Up Disable control for this pin
    uint16_t GPIO76:1;                  // 12 Pull-Up Disable control for this pin
    uint16_t GPIO77:1;                  // 13 Pull-Up Disable control for this pin
    uint16_t GPIO78:1;                  // 14 Pull-Up Disable control for this pin
    uint16_t GPIO79:1;                  // 15 Pull-Up Disable control for this pin
    uint16_t GPIO80:1;                  // 16 Pull-Up Disable control for this pin
    uint16_t GPIO81:1;                  // 17 Pull-Up Disable control for this pin
    uint16_t GPIO82:1;                  // 18 Pull-Up Disable control for this pin
    uint16_t GPIO83:1;                  // 19 Pull-Up Disable control for this pin
    uint16_t GPIO84:1;                  // 20 Pull-Up Disable control for this pin
    uint16_t GPIO85:1;                  // 21 Pull-Up Disable control for this pin
    uint16_t GPIO86:1;                  // 22 Pull-Up Disable control for this pin
    uint16_t GPIO87:1;                  // 23 Pull-Up Disable control for this pin
    uint16_t GPIO88:1;                  // 24 Pull-Up Disable control for this pin
    uint16_t GPIO89:1;                  // 25 Pull-Up Disable control for this pin
    uint16_t GPIO90:1;                  // 26 Pull-Up Disable control for this pin
    uint16_t GPIO91:1;                  // 27 Pull-Up Disable control for this pin
    uint16_t GPIO92:1;                  // 28 Pull-Up Disable control for this pin
    uint16_t GPIO93:1;                  // 29 Pull-Up Disable control for this pin
    uint16_t GPIO94:1;                  // 30 Pull-Up Disable control for this pin
    uint16_t GPIO95:1;                  // 31 Pull-Up Disable control for this pin
};

union GPIO_GPCPUD_REG {
    uint32_t  all;
    struct  GPIO_GPCPUD_BITS  bit;
};

struct GPIO_GPCINV_BITS {               // bits description
    uint16_t GPIO64:1;                  // 0 Input inversion control for this pin
    uint16_t GPIO65:1;                  // 1 Input inversion control for this pin
    uint16_t GPIO66:1;                  // 2 Input inversion control for this pin
    uint16_t GPIO67:1;                  // 3 Input inversion control for this pin
    uint16_t GPIO68:1;                  // 4 Input inversion control for this pin
    uint16_t GPIO69:1;                  // 5 Input inversion control for this pin
    uint16_t GPIO70:1;                  // 6 Input inversion control for this pin
    uint16_t GPIO71:1;                  // 7 Input inversion control for this pin
    uint16_t GPIO72:1;                  // 8 Input inversion control for this pin
    uint16_t GPIO73:1;                  // 9 Input inversion control for this pin
    uint16_t GPIO74:1;                  // 10 Input inversion control for this pin
    uint16_t GPIO75:1;                  // 11 Input inversion control for this pin
    uint16_t GPIO76:1;                  // 12 Input inversion control for this pin
    uint16_t GPIO77:1;                  // 13 Input inversion control for this pin
    uint16_t GPIO78:1;                  // 14 Input inversion control for this pin
    uint16_t GPIO79:1;                  // 15 Input inversion control for this pin
    uint16_t GPIO80:1;                  // 16 Input inversion control for this pin
    uint16_t GPIO81:1;                  // 17 Input inversion control for this pin
    uint16_t GPIO82:1;                  // 18 Input inversion control for this pin
    uint16_t GPIO83:1;                  // 19 Input inversion control for this pin
    uint16_t GPIO84:1;                  // 20 Input inversion control for this pin
    uint16_t GPIO85:1;                  // 21 Input inversion control for this pin
    uint16_t GPIO86:1;                  // 22 Input inversion control for this pin
    uint16_t GPIO87:1;                  // 23 Input inversion control for this pin
    uint16_t GPIO88:1;                  // 24 Input inversion control for this pin
    uint16_t GPIO89:1;                  // 25 Input inversion control for this pin
    uint16_t GPIO90:1;                  // 26 Input inversion control for this pin
    uint16_t GPIO91:1;                  // 27 Input inversion control for this pin
    uint16_t GPIO92:1;                  // 28 Input inversion control for this pin
    uint16_t GPIO93:1;                  // 29 Input inversion control for this pin
    uint16_t GPIO94:1;                  // 30 Input inversion control for this pin
    uint16_t GPIO95:1;                  // 31 Input inversion control for this pin
};

union GPIO_GPCINV_REG {
    uint32_t  all;
    struct  GPIO_GPCINV_BITS  bit;
};

struct GPIO_GPCODR_BITS {               // bits description
    uint16_t GPIO64:1;                  // 0 Outpout Open-Drain control for this pin
    uint16_t GPIO65:1;                  // 1 Outpout Open-Drain control for this pin
    uint16_t GPIO66:1;                  // 2 Outpout Open-Drain control for this pin
    uint16_t GPIO67:1;                  // 3 Outpout Open-Drain control for this pin
    uint16_t GPIO68:1;                  // 4 Outpout Open-Drain control for this pin
    uint16_t GPIO69:1;                  // 5 Outpout Open-Drain control for this pin
    uint16_t GPIO70:1;                  // 6 Outpout Open-Drain control for this pin
    uint16_t GPIO71:1;                  // 7 Outpout Open-Drain control for this pin
    uint16_t GPIO72:1;                  // 8 Outpout Open-Drain control for this pin
    uint16_t GPIO73:1;                  // 9 Outpout Open-Drain control for this pin
    uint16_t GPIO74:1;                  // 10 Outpout Open-Drain control for this pin
    uint16_t GPIO75:1;                  // 11 Outpout Open-Drain control for this pin
    uint16_t GPIO76:1;                  // 12 Outpout Open-Drain control for this pin
    uint16_t GPIO77:1;                  // 13 Outpout Open-Drain control for this pin
    uint16_t GPIO78:1;                  // 14 Outpout Open-Drain control for this pin
    uint16_t GPIO79:1;                  // 15 Outpout Open-Drain control for this pin
    uint16_t GPIO80:1;                  // 16 Outpout Open-Drain control for this pin
    uint16_t GPIO81:1;                  // 17 Outpout Open-Drain control for this pin
    uint16_t GPIO82:1;                  // 18 Outpout Open-Drain control for this pin
    uint16_t GPIO83:1;                  // 19 Outpout Open-Drain control for this pin
    uint16_t GPIO84:1;                  // 20 Outpout Open-Drain control for this pin
    uint16_t GPIO85:1;                  // 21 Outpout Open-Drain control for this pin
    uint16_t GPIO86:1;                  // 22 Outpout Open-Drain control for this pin
    uint16_t GPIO87:1;                  // 23 Outpout Open-Drain control for this pin
    uint16_t GPIO88:1;                  // 24 Outpout Open-Drain control for this pin
    uint16_t GPIO89:1;                  // 25 Outpout Open-Drain control for this pin
    uint16_t GPIO90:1;                  // 26 Outpout Open-Drain control for this pin
    uint16_t GPIO91:1;                  // 27 Outpout Open-Drain control for this pin
    uint16_t GPIO92:1;                  // 28 Outpout Open-Drain control for this pin
    uint16_t GPIO93:1;                  // 29 Outpout Open-Drain control for this pin
    uint16_t GPIO94:1;                  // 30 Outpout Open-Drain control for this pin
    uint16_t GPIO95:1;                  // 31 Outpout Open-Drain control for this pin
};

union GPIO_GPCODR_REG {
    uint32_t  all;
    struct  GPIO_GPCODR_BITS  bit;
};

struct GPIO_GPCGMUX1_BITS {             // bits description
    uint16_t GPIO64:2;                  // 1:0 Defines pin-muxing selection for GPIO64
    uint16_t GPIO65:2;                  // 3:2 Defines pin-muxing selection for GPIO65
    uint16_t GPIO66:2;                  // 5:4 Defines pin-muxing selection for GPIO66
    uint16_t GPIO67:2;                  // 7:6 Defines pin-muxing selection for GPIO67
    uint16_t GPIO68:2;                  // 9:8 Defines pin-muxing selection for GPIO68
    uint16_t GPIO69:2;                  // 11:10 Defines pin-muxing selection for GPIO69
    uint16_t GPIO70:2;                  // 13:12 Defines pin-muxing selection for GPIO70
    uint16_t GPIO71:2;                  // 15:14 Defines pin-muxing selection for GPIO71
    uint16_t GPIO72:2;                  // 17:16 Defines pin-muxing selection for GPIO72
    uint16_t GPIO73:2;                  // 19:18 Defines pin-muxing selection for GPIO73
    uint16_t GPIO74:2;                  // 21:20 Defines pin-muxing selection for GPIO74
    uint16_t GPIO75:2;                  // 23:22 Defines pin-muxing selection for GPIO75
    uint16_t GPIO76:2;                  // 25:24 Defines pin-muxing selection for GPIO76
    uint16_t GPIO77:2;                  // 27:26 Defines pin-muxing selection for GPIO77
    uint16_t GPIO78:2;                  // 29:28 Defines pin-muxing selection for GPIO78
    uint16_t GPIO79:2;                  // 31:30 Defines pin-muxing selection for GPIO79
};

union GPIO_GPCGMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPCGMUX1_BITS  bit;
};

struct GPIO_GPCGMUX2_BITS {             // bits description
    uint16_t GPIO80:2;                  // 1:0 Defines pin-muxing selection for GPIO80
    uint16_t GPIO81:2;                  // 3:2 Defines pin-muxing selection for GPIO81
    uint16_t GPIO82:2;                  // 5:4 Defines pin-muxing selection for GPIO82
    uint16_t GPIO83:2;                  // 7:6 Defines pin-muxing selection for GPIO83
    uint16_t GPIO84:2;                  // 9:8 Defines pin-muxing selection for GPIO84
    uint16_t GPIO85:2;                  // 11:10 Defines pin-muxing selection for GPIO85
    uint16_t GPIO86:2;                  // 13:12 Defines pin-muxing selection for GPIO86
    uint16_t GPIO87:2;                  // 15:14 Defines pin-muxing selection for GPIO87
    uint16_t GPIO88:2;                  // 17:16 Defines pin-muxing selection for GPIO88
    uint16_t GPIO89:2;                  // 19:18 Defines pin-muxing selection for GPIO89
    uint16_t GPIO90:2;                  // 21:20 Defines pin-muxing selection for GPIO90
    uint16_t GPIO91:2;                  // 23:22 Defines pin-muxing selection for GPIO91
    uint16_t GPIO92:2;                  // 25:24 Defines pin-muxing selection for GPIO92
    uint16_t GPIO93:2;                  // 27:26 Defines pin-muxing selection for GPIO93
    uint16_t GPIO94:2;                  // 29:28 Defines pin-muxing selection for GPIO94
    uint16_t GPIO95:2;                  // 31:30 Defines pin-muxing selection for GPIO95
};

union GPIO_GPCGMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPCGMUX2_BITS  bit;
};

struct GPIO_GPCCSEL1_BITS {             // bits description
    uint16_t GPIO64:4;                  // 3:0 GPIO64 Controller CPU Select
    uint16_t GPIO65:4;                  // 7:4 GPIO65 Controller CPU Select
    uint16_t GPIO66:4;                  // 11:8 GPIO66 Controller CPU Select
    uint16_t GPIO67:4;                  // 15:12 GPIO67 Controller CPU Select
    uint16_t GPIO68:4;                  // 19:16 GPIO68 Controller CPU Select
    uint16_t GPIO69:4;                  // 23:20 GPIO69 Controller CPU Select
    uint16_t GPIO70:4;                  // 27:24 GPIO70 Controller CPU Select
    uint16_t GPIO71:4;                  // 31:28 GPIO71 Controller CPU Select
};

union GPIO_GPCCSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPCCSEL1_BITS  bit;
};

struct GPIO_GPCCSEL2_BITS {             // bits description
    uint16_t GPIO72:4;                  // 3:0 GPIO72 Controller CPU Select
    uint16_t GPIO73:4;                  // 7:4 GPIO73 Controller CPU Select
    uint16_t GPIO74:4;                  // 11:8 GPIO74 Controller CPU Select
    uint16_t GPIO75:4;                  // 15:12 GPIO75 Controller CPU Select
    uint16_t GPIO76:4;                  // 19:16 GPIO76 Controller CPU Select
    uint16_t GPIO77:4;                  // 23:20 GPIO77 Controller CPU Select
    uint16_t GPIO78:4;                  // 27:24 GPIO78 Controller CPU Select
    uint16_t GPIO79:4;                  // 31:28 GPIO79 Controller CPU Select
};

union GPIO_GPCCSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPCCSEL2_BITS  bit;
};

struct GPIO_GPCCSEL3_BITS {             // bits description
    uint16_t GPIO80:4;                  // 3:0 GPIO80 Controller CPU Select
    uint16_t GPIO81:4;                  // 7:4 GPIO81 Controller CPU Select
    uint16_t GPIO82:4;                  // 11:8 GPIO82 Controller CPU Select
    uint16_t GPIO83:4;                  // 15:12 GPIO83 Controller CPU Select
    uint16_t GPIO84:4;                  // 19:16 GPIO84 Controller CPU Select
    uint16_t GPIO85:4;                  // 23:20 GPIO85 Controller CPU Select
    uint16_t GPIO86:4;                  // 27:24 GPIO86 Controller CPU Select
    uint16_t GPIO87:4;                  // 31:28 GPIO87 Controller CPU Select
};

union GPIO_GPCCSEL3_REG {
    uint32_t  all;
    struct  GPIO_GPCCSEL3_BITS  bit;
};

struct GPIO_GPCCSEL4_BITS {             // bits description
    uint16_t GPIO88:4;                  // 3:0 GPIO88 Controller CPU Select
    uint16_t GPIO89:4;                  // 7:4 GPIO89 Controller CPU Select
    uint16_t GPIO90:4;                  // 11:8 GPIO90 Controller CPU Select
    uint16_t GPIO91:4;                  // 15:12 GPIO91 Controller CPU Select
    uint16_t GPIO92:4;                  // 19:16 GPIO92 Controller CPU Select
    uint16_t GPIO93:4;                  // 23:20 GPIO93 Controller CPU Select
    uint16_t GPIO94:4;                  // 27:24 GPIO94 Controller CPU Select
    uint16_t GPIO95:4;                  // 31:28 GPIO95 Controller CPU Select
};

union GPIO_GPCCSEL4_REG {
    uint32_t  all;
    struct  GPIO_GPCCSEL4_BITS  bit;
};

struct GPIO_GPCLOCK_BITS {              // bits description
    uint16_t GPIO64:1;                  // 0 Configuration Lock bit for this pin
    uint16_t GPIO65:1;                  // 1 Configuration Lock bit for this pin
    uint16_t GPIO66:1;                  // 2 Configuration Lock bit for this pin
    uint16_t GPIO67:1;                  // 3 Configuration Lock bit for this pin
    uint16_t GPIO68:1;                  // 4 Configuration Lock bit for this pin
    uint16_t GPIO69:1;                  // 5 Configuration Lock bit for this pin
    uint16_t GPIO70:1;                  // 6 Configuration Lock bit for this pin
    uint16_t GPIO71:1;                  // 7 Configuration Lock bit for this pin
    uint16_t GPIO72:1;                  // 8 Configuration Lock bit for this pin
    uint16_t GPIO73:1;                  // 9 Configuration Lock bit for this pin
    uint16_t GPIO74:1;                  // 10 Configuration Lock bit for this pin
    uint16_t GPIO75:1;                  // 11 Configuration Lock bit for this pin
    uint16_t GPIO76:1;                  // 12 Configuration Lock bit for this pin
    uint16_t GPIO77:1;                  // 13 Configuration Lock bit for this pin
    uint16_t GPIO78:1;                  // 14 Configuration Lock bit for this pin
    uint16_t GPIO79:1;                  // 15 Configuration Lock bit for this pin
    uint16_t GPIO80:1;                  // 16 Configuration Lock bit for this pin
    uint16_t GPIO81:1;                  // 17 Configuration Lock bit for this pin
    uint16_t GPIO82:1;                  // 18 Configuration Lock bit for this pin
    uint16_t GPIO83:1;                  // 19 Configuration Lock bit for this pin
    uint16_t GPIO84:1;                  // 20 Configuration Lock bit for this pin
    uint16_t GPIO85:1;                  // 21 Configuration Lock bit for this pin
    uint16_t GPIO86:1;                  // 22 Configuration Lock bit for this pin
    uint16_t GPIO87:1;                  // 23 Configuration Lock bit for this pin
    uint16_t GPIO88:1;                  // 24 Configuration Lock bit for this pin
    uint16_t GPIO89:1;                  // 25 Configuration Lock bit for this pin
    uint16_t GPIO90:1;                  // 26 Configuration Lock bit for this pin
    uint16_t GPIO91:1;                  // 27 Configuration Lock bit for this pin
    uint16_t GPIO92:1;                  // 28 Configuration Lock bit for this pin
    uint16_t GPIO93:1;                  // 29 Configuration Lock bit for this pin
    uint16_t GPIO94:1;                  // 30 Configuration Lock bit for this pin
    uint16_t GPIO95:1;                  // 31 Configuration Lock bit for this pin
};

union GPIO_GPCLOCK_REG {
    uint32_t  all;
    struct  GPIO_GPCLOCK_BITS  bit;
};

struct GPIO_GPCCR_BITS {                // bits description
    uint16_t GPIO64:1;                  // 0 Configuration lock commit bit for this pin
    uint16_t GPIO65:1;                  // 1 Configuration lock commit bit for this pin
    uint16_t GPIO66:1;                  // 2 Configuration lock commit bit for this pin
    uint16_t GPIO67:1;                  // 3 Configuration lock commit bit for this pin
    uint16_t GPIO68:1;                  // 4 Configuration lock commit bit for this pin
    uint16_t GPIO69:1;                  // 5 Configuration lock commit bit for this pin
    uint16_t GPIO70:1;                  // 6 Configuration lock commit bit for this pin
    uint16_t GPIO71:1;                  // 7 Configuration lock commit bit for this pin
    uint16_t GPIO72:1;                  // 8 Configuration lock commit bit for this pin
    uint16_t GPIO73:1;                  // 9 Configuration lock commit bit for this pin
    uint16_t GPIO74:1;                  // 10 Configuration lock commit bit for this pin
    uint16_t GPIO75:1;                  // 11 Configuration lock commit bit for this pin
    uint16_t GPIO76:1;                  // 12 Configuration lock commit bit for this pin
    uint16_t GPIO77:1;                  // 13 Configuration lock commit bit for this pin
    uint16_t GPIO78:1;                  // 14 Configuration lock commit bit for this pin
    uint16_t GPIO79:1;                  // 15 Configuration lock commit bit for this pin
    uint16_t GPIO80:1;                  // 16 Configuration lock commit bit for this pin
    uint16_t GPIO81:1;                  // 17 Configuration lock commit bit for this pin
    uint16_t GPIO82:1;                  // 18 Configuration lock commit bit for this pin
    uint16_t GPIO83:1;                  // 19 Configuration lock commit bit for this pin
    uint16_t GPIO84:1;                  // 20 Configuration lock commit bit for this pin
    uint16_t GPIO85:1;                  // 21 Configuration lock commit bit for this pin
    uint16_t GPIO86:1;                  // 22 Configuration lock commit bit for this pin
    uint16_t GPIO87:1;                  // 23 Configuration lock commit bit for this pin
    uint16_t GPIO88:1;                  // 24 Configuration lock commit bit for this pin
    uint16_t GPIO89:1;                  // 25 Configuration lock commit bit for this pin
    uint16_t GPIO90:1;                  // 26 Configuration lock commit bit for this pin
    uint16_t GPIO91:1;                  // 27 Configuration lock commit bit for this pin
    uint16_t GPIO92:1;                  // 28 Configuration lock commit bit for this pin
    uint16_t GPIO93:1;                  // 29 Configuration lock commit bit for this pin
    uint16_t GPIO94:1;                  // 30 Configuration lock commit bit for this pin
    uint16_t GPIO95:1;                  // 31 Configuration lock commit bit for this pin
};

union GPIO_GPCCR_REG {
    uint32_t  all;
    struct  GPIO_GPCCR_BITS  bit;
};

struct GPIO_GPDCTRL_BITS {              // bits description
    uint16_t QUALPRD0:8;                // 7:0 Qualification sampling period for GPIO96 to GPIO103
    uint16_t QUALPRD1:8;                // 15:8 Qualification sampling period for GPIO104 to GPIO111
    uint16_t rsvd1:8;                   // 23:16 Reserved
    uint16_t QUALPRD3:8;                // 31:24 Qualification sampling period for GPIO120 to GPIO127
};

union GPIO_GPDCTRL_REG {
    uint32_t  all;
    struct  GPIO_GPDCTRL_BITS  bit;
};

struct GPIO_GPDQSEL1_BITS {             // bits description
    uint16_t GPIO96:2;                  // 1:0 Select input qualification type for GPIO96
    uint16_t GPIO97:2;                  // 3:2 Select input qualification type for GPIO97
    uint16_t GPIO98:2;                  // 5:4 Select input qualification type for GPIO98
    uint16_t GPIO99:2;                  // 7:6 Select input qualification type for GPIO99
    uint16_t GPIO100:2;                 // 9:8 Select input qualification type for GPIO100
    uint16_t GPIO101:2;                 // 11:10 Select input qualification type for GPIO101
    uint16_t rsvd1:2;                   // 13:12 Reserved
    uint16_t GPIO103:2;                 // 15:14 Select input qualification type for GPIO103
    uint16_t rsvd2:2;                   // 17:16 Reserved
    uint16_t GPIO105:2;                 // 19:18 Select input qualification type for GPIO105
    uint16_t rsvd3:2;                   // 21:20 Reserved
    uint16_t rsvd4:2;                   // 23:22 Reserved
    uint16_t rsvd5:2;                   // 25:24 Reserved
    uint16_t rsvd6:2;                   // 27:26 Reserved
    uint16_t rsvd7:2;                   // 29:28 Reserved
    uint16_t rsvd8:2;                   // 31:30 Reserved
};

union GPIO_GPDQSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPDQSEL1_BITS  bit;
};

struct GPIO_GPDQSEL2_BITS {             // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t rsvd2:2;                   // 3:2 Reserved
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:2;                   // 7:6 Reserved
    uint16_t rsvd5:2;                   // 9:8 Reserved
    uint16_t rsvd6:2;                   // 11:10 Reserved
    uint16_t rsvd7:2;                   // 13:12 Reserved
    uint16_t rsvd8:2;                   // 15:14 Reserved
    uint16_t rsvd9:2;                   // 17:16 Reserved
    uint16_t rsvd10:2;                  // 19:18 Reserved
    uint16_t rsvd11:2;                  // 21:20 Reserved
    uint16_t rsvd12:2;                  // 23:22 Reserved
    uint16_t rsvd13:2;                  // 25:24 Reserved
    uint16_t rsvd14:2;                  // 27:26 Reserved
    uint16_t rsvd15:2;                  // 29:28 Reserved
    uint16_t GPIO127:2;                 // 31:30 Select input qualification type for GPIO127
};

union GPIO_GPDQSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPDQSEL2_BITS  bit;
};

struct GPIO_GPDMUX1_BITS {              // bits description
    uint16_t GPIO96:2;                  // 1:0 Defines pin-muxing selection for GPIO96
    uint16_t GPIO97:2;                  // 3:2 Defines pin-muxing selection for GPIO97
    uint16_t GPIO98:2;                  // 5:4 Defines pin-muxing selection for GPIO98
    uint16_t GPIO99:2;                  // 7:6 Defines pin-muxing selection for GPIO99
    uint16_t GPIO100:2;                 // 9:8 Defines pin-muxing selection for GPIO100
    uint16_t GPIO101:2;                 // 11:10 Defines pin-muxing selection for GPIO101
    uint16_t rsvd1:2;                   // 13:12 Reserved
    uint16_t GPIO103:2;                 // 15:14 Defines pin-muxing selection for GPIO103
    uint16_t rsvd2:2;                   // 17:16 Reserved
    uint16_t GPIO105:2;                 // 19:18 Defines pin-muxing selection for GPIO105
    uint16_t rsvd3:2;                   // 21:20 Reserved
    uint16_t rsvd4:2;                   // 23:22 Reserved
    uint16_t rsvd5:2;                   // 25:24 Reserved
    uint16_t rsvd6:2;                   // 27:26 Reserved
    uint16_t rsvd7:2;                   // 29:28 Reserved
    uint16_t rsvd8:2;                   // 31:30 Reserved
};

union GPIO_GPDMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPDMUX1_BITS  bit;
};

struct GPIO_GPDMUX2_BITS {              // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t rsvd2:2;                   // 3:2 Reserved
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:2;                   // 7:6 Reserved
    uint16_t rsvd5:2;                   // 9:8 Reserved
    uint16_t rsvd6:2;                   // 11:10 Reserved
    uint16_t rsvd7:2;                   // 13:12 Reserved
    uint16_t rsvd8:2;                   // 15:14 Reserved
    uint16_t rsvd9:2;                   // 17:16 Reserved
    uint16_t rsvd10:2;                  // 19:18 Reserved
    uint16_t rsvd11:2;                  // 21:20 Reserved
    uint16_t rsvd12:2;                  // 23:22 Reserved
    uint16_t rsvd13:2;                  // 25:24 Reserved
    uint16_t rsvd14:2;                  // 27:26 Reserved
    uint16_t rsvd15:2;                  // 29:28 Reserved
    uint16_t GPIO127:2;                 // 31:30 Defines pin-muxing selection for GPIO127
};

union GPIO_GPDMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPDMUX2_BITS  bit;
};

struct GPIO_GPDPUD_BITS {               // bits description
    uint16_t GPIO96:1;                  // 0 Pull-Up Disable control for this pin
    uint16_t GPIO97:1;                  // 1 Pull-Up Disable control for this pin
    uint16_t GPIO98:1;                  // 2 Pull-Up Disable control for this pin
    uint16_t GPIO99:1;                  // 3 Pull-Up Disable control for this pin
    uint16_t GPIO100:1;                 // 4 Pull-Up Disable control for this pin
    uint16_t GPIO101:1;                 // 5 Pull-Up Disable control for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Pull-Up Disable control for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Pull-Up Disable control for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Pull-Up Disable control for this pin
};

union GPIO_GPDPUD_REG {
    uint32_t  all;
    struct  GPIO_GPDPUD_BITS  bit;
};

struct GPIO_GPDINV_BITS {               // bits description
    uint16_t GPIO96:1;                  // 0 Input inversion control for this pin
    uint16_t GPIO97:1;                  // 1 Input inversion control for this pin
    uint16_t GPIO98:1;                  // 2 Input inversion control for this pin
    uint16_t GPIO99:1;                  // 3 Input inversion control for this pin
    uint16_t GPIO100:1;                 // 4 Input inversion control for this pin
    uint16_t GPIO101:1;                 // 5 Input inversion control for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Input inversion control for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Input inversion control for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Input inversion control for this pin
};

union GPIO_GPDINV_REG {
    uint32_t  all;
    struct  GPIO_GPDINV_BITS  bit;
};

struct GPIO_GPDODR_BITS {               // bits description
    uint16_t GPIO96:1;                  // 0 Outpout Open-Drain control for this pin
    uint16_t GPIO97:1;                  // 1 Outpout Open-Drain control for this pin
    uint16_t GPIO98:1;                  // 2 Outpout Open-Drain control for this pin
    uint16_t GPIO99:1;                  // 3 Outpout Open-Drain control for this pin
    uint16_t GPIO100:1;                 // 4 Outpout Open-Drain control for this pin
    uint16_t GPIO101:1;                 // 5 Outpout Open-Drain control for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Outpout Open-Drain control for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Outpout Open-Drain control for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Outpout Open-Drain control for this pin
};

union GPIO_GPDODR_REG {
    uint32_t  all;
    struct  GPIO_GPDODR_BITS  bit;
};

struct GPIO_GPDGMUX1_BITS {             // bits description
    uint16_t GPIO96:2;                  // 1:0 Defines pin-muxing selection for GPIO96
    uint16_t GPIO97:2;                  // 3:2 Defines pin-muxing selection for GPIO97
    uint16_t GPIO98:2;                  // 5:4 Defines pin-muxing selection for GPIO98
    uint16_t GPIO99:2;                  // 7:6 Defines pin-muxing selection for GPIO99
    uint16_t GPIO100:2;                 // 9:8 Defines pin-muxing selection for GPIO100
    uint16_t GPIO101:2;                 // 11:10 Defines pin-muxing selection for GPIO101
    uint16_t rsvd1:2;                   // 13:12 Reserved
    uint16_t GPIO103:2;                 // 15:14 Defines pin-muxing selection for GPIO103
    uint16_t rsvd2:2;                   // 17:16 Reserved
    uint16_t GPIO105:2;                 // 19:18 Defines pin-muxing selection for GPIO105
    uint16_t rsvd3:2;                   // 21:20 Reserved
    uint16_t rsvd4:2;                   // 23:22 Reserved
    uint16_t rsvd5:2;                   // 25:24 Reserved
    uint16_t rsvd6:2;                   // 27:26 Reserved
    uint16_t rsvd7:2;                   // 29:28 Reserved
    uint16_t rsvd8:2;                   // 31:30 Reserved
};

union GPIO_GPDGMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPDGMUX1_BITS  bit;
};

struct GPIO_GPDGMUX2_BITS {             // bits description
    uint16_t rsvd1:2;                   // 1:0 Reserved
    uint16_t rsvd2:2;                   // 3:2 Reserved
    uint16_t rsvd3:2;                   // 5:4 Reserved
    uint16_t rsvd4:2;                   // 7:6 Reserved
    uint16_t rsvd5:2;                   // 9:8 Reserved
    uint16_t rsvd6:2;                   // 11:10 Reserved
    uint16_t rsvd7:2;                   // 13:12 Reserved
    uint16_t rsvd8:2;                   // 15:14 Reserved
    uint16_t rsvd9:2;                   // 17:16 Reserved
    uint16_t rsvd10:2;                  // 19:18 Reserved
    uint16_t rsvd11:2;                  // 21:20 Reserved
    uint16_t rsvd12:2;                  // 23:22 Reserved
    uint16_t rsvd13:2;                  // 25:24 Reserved
    uint16_t rsvd14:2;                  // 27:26 Reserved
    uint16_t rsvd15:2;                  // 29:28 Reserved
    uint16_t GPIO127:2;                 // 31:30 Defines pin-muxing selection for GPIO127
};

union GPIO_GPDGMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPDGMUX2_BITS  bit;
};

struct GPIO_GPDCSEL1_BITS {             // bits description
    uint16_t GPIO96:4;                  // 3:0 GPIO96 Controller CPU Select
    uint16_t GPIO97:4;                  // 7:4 GPIO97 Controller CPU Select
    uint16_t GPIO98:4;                  // 11:8 GPIO98 Controller CPU Select
    uint16_t GPIO99:4;                  // 15:12 GPIO99 Controller CPU Select
    uint16_t GPIO100:4;                 // 19:16 GPIO100 Controller CPU Select
    uint16_t GPIO101:4;                 // 23:20 GPIO101 Controller CPU Select
    uint16_t rsvd1:4;                   // 27:24 Reserved
    uint16_t GPIO103:4;                 // 31:28 GPIO103 Controller CPU Select
};

union GPIO_GPDCSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPDCSEL1_BITS  bit;
};

struct GPIO_GPDCSEL2_BITS {             // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t GPIO105:4;                 // 7:4 GPIO105 Controller CPU Select
    uint16_t rsvd2:4;                   // 11:8 Reserved
    uint16_t rsvd3:4;                   // 15:12 Reserved
    uint16_t rsvd4:4;                   // 19:16 Reserved
    uint16_t rsvd5:4;                   // 23:20 Reserved
    uint16_t rsvd6:4;                   // 27:24 Reserved
    uint16_t rsvd7:4;                   // 31:28 Reserved
};

union GPIO_GPDCSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPDCSEL2_BITS  bit;
};

struct GPIO_GPDCSEL4_BITS {             // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t rsvd2:4;                   // 7:4 Reserved
    uint16_t rsvd3:4;                   // 11:8 Reserved
    uint16_t rsvd4:4;                   // 15:12 Reserved
    uint16_t rsvd5:4;                   // 19:16 Reserved
    uint16_t rsvd6:4;                   // 23:20 Reserved
    uint16_t rsvd7:4;                   // 27:24 Reserved
    uint16_t GPIO127:4;                 // 31:28 GPIO127 Controller CPU Select
};

union GPIO_GPDCSEL4_REG {
    uint32_t  all;
    struct  GPIO_GPDCSEL4_BITS  bit;
};

struct GPIO_GPDLOCK_BITS {              // bits description
    uint16_t GPIO96:1;                  // 0 Configuration Lock bit for this pin
    uint16_t GPIO97:1;                  // 1 Configuration Lock bit for this pin
    uint16_t GPIO98:1;                  // 2 Configuration Lock bit for this pin
    uint16_t GPIO99:1;                  // 3 Configuration Lock bit for this pin
    uint16_t GPIO100:1;                 // 4 Configuration Lock bit for this pin
    uint16_t GPIO101:1;                 // 5 Configuration Lock bit for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Configuration Lock bit for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Configuration Lock bit for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Configuration Lock bit for this pin
};

union GPIO_GPDLOCK_REG {
    uint32_t  all;
    struct  GPIO_GPDLOCK_BITS  bit;
};

struct GPIO_GPDCR_BITS {                // bits description
    uint16_t GPIO96:1;                  // 0 Configuration lock commit bit for this pin
    uint16_t GPIO97:1;                  // 1 Configuration lock commit bit for this pin
    uint16_t GPIO98:1;                  // 2 Configuration lock commit bit for this pin
    uint16_t GPIO99:1;                  // 3 Configuration lock commit bit for this pin
    uint16_t GPIO100:1;                 // 4 Configuration lock commit bit for this pin
    uint16_t GPIO101:1;                 // 5 Configuration lock commit bit for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Configuration lock commit bit for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Configuration lock commit bit for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Configuration lock commit bit for this pin
};

union GPIO_GPDCR_REG {
    uint32_t  all;
    struct  GPIO_GPDCR_BITS  bit;
};

struct GPIO_GPFCTRL_BITS {              // bits description
    uint16_t QUALPRD0:8;                // 7:0 Qualification sampling period for GPIO160 to GPIO167
    uint16_t QUALPRD1:8;                // 15:8 Qualification sampling period for GPIO168
    uint16_t QUALPRD2:8;                // 23:16 Qualification sampling period for GPIO176 to GPIO183
    uint16_t QUALPRD3:8;                // 31:24 Qualification sampling period for GPIO184 to GPIO191
};

union GPIO_GPFCTRL_REG {
    uint32_t  all;
    struct  GPIO_GPFCTRL_BITS  bit;
};

struct GPIO_GPFQSEL1_BITS {             // bits description
    uint16_t GPIO160:2;                 // 1:0 Select input qualification type for GPIO160
    uint16_t GPIO161:2;                 // 3:2 Select input qualification type for GPIO161
    uint16_t GPIO162:2;                 // 5:4 Select input qualification type for GPIO162
    uint16_t GPIO163:2;                 // 7:6 Select input qualification type for GPIO163
    uint16_t GPIO164:2;                 // 9:8 Select input qualification type for GPIO164
    uint16_t GPIO165:2;                 // 11:10 Select input qualification type for GPIO165
    uint16_t GPIO166:2;                 // 13:12 Select input qualification type for GPIO166
    uint16_t GPIO167:2;                 // 15:14 Select input qualification type for GPIO167
    uint16_t GPIO168:2;                 // 17:16 Select input qualification type for GPIO168
    uint16_t GPIO169:2;                 // 19:18 Select input qualification type for GPIO169
    uint16_t GPIO170:2;                 // 21:20 Select input qualification type for GPIO170
    uint16_t GPIO171:2;                 // 23:22 Select input qualification type for GPIO171
    uint16_t GPIO172:2;                 // 25:24 Select input qualification type for GPIO172
    uint16_t GPIO173:2;                 // 27:26 Select input qualification type for GPIO173
    uint16_t GPIO174:2;                 // 29:28 Select input qualification type for GPIO174
    uint16_t GPIO175:2;                 // 31:30 Select input qualification type for GPIO175
};

union GPIO_GPFQSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPFQSEL1_BITS  bit;
};

struct GPIO_GPFQSEL2_BITS {             // bits description
    uint16_t GPIO176:2;                 // 1:0 Select input qualification type for GPIO176
    uint16_t GPIO177:2;                 // 3:2 Select input qualification type for GPIO177
    uint16_t GPIO178:2;                 // 5:4 Select input qualification type for GPIO178
    uint16_t GPIO179:2;                 // 7:6 Select input qualification type for GPIO179
    uint16_t GPIO180:2;                 // 9:8 Select input qualification type for GPIO180
    uint16_t GPIO181:2;                 // 11:10 Select input qualification type for GPIO181
    uint16_t GPIO182:2;                 // 13:12 Select input qualification type for GPIO182
    uint16_t GPIO183:2;                 // 15:14 Select input qualification type for GPIO183
    uint16_t GPIO184:2;                 // 17:16 Select input qualification type for GPIO184
    uint16_t GPIO185:2;                 // 19:18 Select input qualification type for GPIO185
    uint16_t GPIO186:2;                 // 21:20 Select input qualification type for GPIO186
    uint16_t GPIO187:2;                 // 23:22 Select input qualification type for GPIO187
    uint16_t GPIO188:2;                 // 25:24 Select input qualification type for GPIO188
    uint16_t GPIO189:2;                 // 27:26 Select input qualification type for GPIO189
    uint16_t GPIO190:2;                 // 29:28 Select input qualification type for GPIO190
    uint16_t GPIO191:2;                 // 31:30 Select input qualification type for GPIO191
};

union GPIO_GPFQSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPFQSEL2_BITS  bit;
};

struct GPIO_GPFMUX1_BITS {              // bits description
    uint16_t GPIO160:2;                 // 1:0 Defines pin-muxing selection for GPIO160
    uint16_t GPIO161:2;                 // 3:2 Defines pin-muxing selection for GPIO161
    uint16_t GPIO162:2;                 // 5:4 Defines pin-muxing selection for GPIO162
    uint16_t GPIO163:2;                 // 7:6 Defines pin-muxing selection for GPIO163
    uint16_t GPIO164:2;                 // 9:8 Defines pin-muxing selection for GPIO164
    uint16_t GPIO165:2;                 // 11:10 Defines pin-muxing selection for GPIO165
    uint16_t GPIO166:2;                 // 13:12 Defines pin-muxing selection for GPIO166
    uint16_t GPIO167:2;                 // 15:14 Defines pin-muxing selection for GPIO167
    uint16_t GPIO168:2;                 // 17:16 Defines pin-muxing selection for GPIO168
    uint16_t GPIO169:2;                 // 19:18 Defines pin-muxing selection for GPIO169
    uint16_t GPIO170:2;                 // 21:20 Defines pin-muxing selection for GPIO170
    uint16_t GPIO171:2;                 // 23:22 Defines pin-muxing selection for GPIO171
    uint16_t GPIO172:2;                 // 25:24 Defines pin-muxing selection for GPIO172
    uint16_t GPIO173:2;                 // 27:26 Defines pin-muxing selection for GPIO173
    uint16_t GPIO174:2;                 // 29:28 Defines pin-muxing selection for GPIO174
    uint16_t GPIO175:2;                 // 31:30 Defines pin-muxing selection for GPIO175
};

union GPIO_GPFMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPFMUX1_BITS  bit;
};

struct GPIO_GPFMUX2_BITS {              // bits description
    uint16_t GPIO176:2;                 // 1:0 Defines pin-muxing selection for GPIO176
    uint16_t GPIO177:2;                 // 3:2 Defines pin-muxing selection for GPIO177
    uint16_t GPIO178:2;                 // 5:4 Defines pin-muxing selection for GPIO178
    uint16_t GPIO179:2;                 // 7:6 Defines pin-muxing selection for GPIO179
    uint16_t GPIO180:2;                 // 9:8 Defines pin-muxing selection for GPIO180
    uint16_t GPIO181:2;                 // 11:10 Defines pin-muxing selection for GPIO181
    uint16_t GPIO182:2;                 // 13:12 Defines pin-muxing selection for GPIO182
    uint16_t GPIO183:2;                 // 15:14 Defines pin-muxing selection for GPIO183
    uint16_t GPIO184:2;                 // 17:16 Defines pin-muxing selection for GPIO184
    uint16_t GPIO185:2;                 // 19:18 Defines pin-muxing selection for GPIO185
    uint16_t GPIO186:2;                 // 21:20 Defines pin-muxing selection for GPIO186
    uint16_t GPIO187:2;                 // 23:22 Defines pin-muxing selection for GPIO187
    uint16_t GPIO188:2;                 // 25:24 Defines pin-muxing selection for GPIO188
    uint16_t GPIO189:2;                 // 27:26 Defines pin-muxing selection for GPIO189
    uint16_t GPIO190:2;                 // 29:28 Defines pin-muxing selection for GPIO190
    uint16_t GPIO191:2;                 // 31:30 Defines pin-muxing selection for GPIO191
};

union GPIO_GPFMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPFMUX2_BITS  bit;
};

struct GPIO_GPFPUD_BITS {               // bits description
    uint16_t GPIO160:1;                 // 0 Pull-Up Disable control for this pin
    uint16_t GPIO161:1;                 // 1 Pull-Up Disable control for this pin
    uint16_t GPIO162:1;                 // 2 Pull-Up Disable control for this pin
    uint16_t GPIO163:1;                 // 3 Pull-Up Disable control for this pin
    uint16_t GPIO164:1;                 // 4 Pull-Up Disable control for this pin
    uint16_t GPIO165:1;                 // 5 Pull-Up Disable control for this pin
    uint16_t GPIO166:1;                 // 6 Pull-Up Disable control for this pin
    uint16_t GPIO167:1;                 // 7 Pull-Up Disable control for this pin
    uint16_t GPIO168:1;                 // 8 Pull-Up Disable control for this pin
    uint16_t GPIO169:1;                 // 9 Pull-Up Disable control for this pin
    uint16_t GPIO170:1;                 // 10 Pull-Up Disable control for this pin
    uint16_t GPIO171:1;                 // 11 Pull-Up Disable control for this pin
    uint16_t GPIO172:1;                 // 12 Pull-Up Disable control for this pin
    uint16_t GPIO173:1;                 // 13 Pull-Up Disable control for this pin
    uint16_t GPIO174:1;                 // 14 Pull-Up Disable control for this pin
    uint16_t GPIO175:1;                 // 15 Pull-Up Disable control for this pin
    uint16_t GPIO176:1;                 // 16 Pull-Up Disable control for this pin
    uint16_t GPIO177:1;                 // 17 Pull-Up Disable control for this pin
    uint16_t GPIO178:1;                 // 18 Pull-Up Disable control for this pin
    uint16_t GPIO179:1;                 // 19 Pull-Up Disable control for this pin
    uint16_t GPIO180:1;                 // 20 Pull-Up Disable control for this pin
    uint16_t GPIO181:1;                 // 21 Pull-Up Disable control for this pin
    uint16_t GPIO182:1;                 // 22 Pull-Up Disable control for this pin
    uint16_t GPIO183:1;                 // 23 Pull-Up Disable control for this pin
    uint16_t GPIO184:1;                 // 24 Pull-Up Disable control for this pin
    uint16_t GPIO185:1;                 // 25 Pull-Up Disable control for this pin
    uint16_t GPIO186:1;                 // 26 Pull-Up Disable control for this pin
    uint16_t GPIO187:1;                 // 27 Pull-Up Disable control for this pin
    uint16_t GPIO188:1;                 // 28 Pull-Up Disable control for this pin
    uint16_t GPIO189:1;                 // 29 Pull-Up Disable control for this pin
    uint16_t GPIO190:1;                 // 30 Pull-Up Disable control for this pin
    uint16_t GPIO191:1;                 // 31 Pull-Up Disable control for this pin
};

union GPIO_GPFPUD_REG {
    uint32_t  all;
    struct  GPIO_GPFPUD_BITS  bit;
};

struct GPIO_GPFINV_BITS {               // bits description
    uint16_t GPIO160:1;                 // 0 Input inversion control for this pin
    uint16_t GPIO161:1;                 // 1 Input inversion control for this pin
    uint16_t GPIO162:1;                 // 2 Input inversion control for this pin
    uint16_t GPIO163:1;                 // 3 Input inversion control for this pin
    uint16_t GPIO164:1;                 // 4 Input inversion control for this pin
    uint16_t GPIO165:1;                 // 5 Input inversion control for this pin
    uint16_t GPIO166:1;                 // 6 Input inversion control for this pin
    uint16_t GPIO167:1;                 // 7 Input inversion control for this pin
    uint16_t GPIO168:1;                 // 8 Input inversion control for this pin
    uint16_t GPIO169:1;                 // 9 Input inversion control for this pin
    uint16_t GPIO170:1;                 // 10 Input inversion control for this pin
    uint16_t GPIO171:1;                 // 11 Input inversion control for this pin
    uint16_t GPIO172:1;                 // 12 Input inversion control for this pin
    uint16_t GPIO173:1;                 // 13 Input inversion control for this pin
    uint16_t GPIO174:1;                 // 14 Input inversion control for this pin
    uint16_t GPIO175:1;                 // 15 Input inversion control for this pin
    uint16_t GPIO176:1;                 // 16 Input inversion control for this pin
    uint16_t GPIO177:1;                 // 17 Input inversion control for this pin
    uint16_t GPIO178:1;                 // 18 Input inversion control for this pin
    uint16_t GPIO179:1;                 // 19 Input inversion control for this pin
    uint16_t GPIO180:1;                 // 20 Input inversion control for this pin
    uint16_t GPIO181:1;                 // 21 Input inversion control for this pin
    uint16_t GPIO182:1;                 // 22 Input inversion control for this pin
    uint16_t GPIO183:1;                 // 23 Input inversion control for this pin
    uint16_t GPIO184:1;                 // 24 Input inversion control for this pin
    uint16_t GPIO185:1;                 // 25 Input inversion control for this pin
    uint16_t GPIO186:1;                 // 26 Input inversion control for this pin
    uint16_t GPIO187:1;                 // 27 Input inversion control for this pin
    uint16_t GPIO188:1;                 // 28 Input inversion control for this pin
    uint16_t GPIO189:1;                 // 29 Input inversion control for this pin
    uint16_t GPIO190:1;                 // 30 Input inversion control for this pin
    uint16_t GPIO191:1;                 // 31 Input inversion control for this pin
};

union GPIO_GPFINV_REG {
    uint32_t  all;
    struct  GPIO_GPFINV_BITS  bit;
};

struct GPIO_GPFAMSEL_BITS {             // bits description
    uint16_t GPIO160:1;                 // 0 Analog Mode select for this pin
    uint16_t GPIO161:1;                 // 1 Analog Mode select for this pin
    uint16_t GPIO162:1;                 // 2 Analog Mode select for this pin
    uint16_t GPIO163:1;                 // 3 Analog Mode select for this pin
    uint16_t GPIO164:1;                 // 4 Analog Mode select for this pin
    uint16_t GPIO165:1;                 // 5 Analog Mode select for this pin
    uint16_t GPIO166:1;                 // 6 Analog Mode select for this pin
    uint16_t GPIO167:1;                 // 7 Analog Mode select for this pin
    uint16_t GPIO168:1;                 // 8 Analog Mode select for this pin
    uint16_t GPIO169:1;                 // 9 Analog Mode select for this pin
    uint16_t GPIO170:1;                 // 10 Analog Mode select for this pin
    uint16_t GPIO171:1;                 // 11 Analog Mode select for this pin
    uint16_t GPIO172:1;                 // 12 Analog Mode select for this pin
    uint16_t GPIO173:1;                 // 13 Analog Mode select for this pin
    uint16_t GPIO174:1;                 // 14 Analog Mode select for this pin
    uint16_t GPIO175:1;                 // 15 Analog Mode select for this pin
    uint16_t GPIO176:1;                 // 16 Analog Mode select for this pin
    uint16_t GPIO177:1;                 // 17 Analog Mode select for this pin
    uint16_t GPIO178:1;                 // 18 Analog Mode select for this pin
    uint16_t GPIO179:1;                 // 19 Analog Mode select for this pin
    uint16_t GPIO180:1;                 // 20 Analog Mode select for this pin
    uint16_t GPIO181:1;                 // 21 Analog Mode select for this pin
    uint16_t GPIO182:1;                 // 22 Analog Mode select for this pin
    uint16_t GPIO183:1;                 // 23 Analog Mode select for this pin
    uint16_t GPIO184:1;                 // 24 Analog Mode select for this pin
    uint16_t GPIO185:1;                 // 25 Analog Mode select for this pin
    uint16_t GPIO186:1;                 // 26 Analog Mode select for this pin
    uint16_t GPIO187:1;                 // 27 Analog Mode select for this pin
    uint16_t GPIO188:1;                 // 28 Analog Mode select for this pin
    uint16_t GPIO189:1;                 // 29 Analog Mode select for this pin
    uint16_t GPIO190:1;                 // 30 Analog Mode select for this pin
    uint16_t GPIO191:1;                 // 31 Analog Mode select for this pin
};

union GPIO_GPFAMSEL_REG {
    uint32_t  all;
    struct  GPIO_GPFAMSEL_BITS  bit;
};

struct GPIO_GPFGMUX1_BITS {             // bits description
    uint16_t GPIO160:2;                 // 1:0 Defines pin-muxing selection for GPIO160
    uint16_t GPIO161:2;                 // 3:2 Defines pin-muxing selection for GPIO161
    uint16_t GPIO162:2;                 // 5:4 Defines pin-muxing selection for GPIO162
    uint16_t GPIO163:2;                 // 7:6 Defines pin-muxing selection for GPIO163
    uint16_t GPIO164:2;                 // 9:8 Defines pin-muxing selection for GPIO164
    uint16_t GPIO165:2;                 // 11:10 Defines pin-muxing selection for GPIO165
    uint16_t GPIO166:2;                 // 13:12 Defines pin-muxing selection for GPIO166
    uint16_t GPIO167:2;                 // 15:14 Defines pin-muxing selection for GPIO167
    uint16_t GPIO168:2;                 // 17:16 Defines pin-muxing selection for GPIO168
    uint16_t GPIO169:2;                 // 19:18 Defines pin-muxing selection for GPIO169
    uint16_t GPIO170:2;                 // 21:20 Defines pin-muxing selection for GPIO170
    uint16_t GPIO171:2;                 // 23:22 Defines pin-muxing selection for GPIO171
    uint16_t GPIO172:2;                 // 25:24 Defines pin-muxing selection for GPIO172
    uint16_t GPIO173:2;                 // 27:26 Defines pin-muxing selection for GPIO173
    uint16_t GPIO174:2;                 // 29:28 Defines pin-muxing selection for GPIO174
    uint16_t GPIO175:2;                 // 31:30 Defines pin-muxing selection for GPIO175
};

union GPIO_GPFGMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPFGMUX1_BITS  bit;
};

struct GPIO_GPFGMUX2_BITS {             // bits description
    uint16_t GPIO176:2;                 // 1:0 Defines pin-muxing selection for GPIO176
    uint16_t GPIO177:2;                 // 3:2 Defines pin-muxing selection for GPIO177
    uint16_t GPIO178:2;                 // 5:4 Defines pin-muxing selection for GPIO178
    uint16_t GPIO179:2;                 // 7:6 Defines pin-muxing selection for GPIO179
    uint16_t GPIO180:2;                 // 9:8 Defines pin-muxing selection for GPIO180
    uint16_t GPIO181:2;                 // 11:10 Defines pin-muxing selection for GPIO181
    uint16_t GPIO182:2;                 // 13:12 Defines pin-muxing selection for GPIO182
    uint16_t GPIO183:2;                 // 15:14 Defines pin-muxing selection for GPIO183
    uint16_t GPIO184:2;                 // 17:16 Defines pin-muxing selection for GPIO184
    uint16_t GPIO185:2;                 // 19:18 Defines pin-muxing selection for GPIO185
    uint16_t GPIO186:2;                 // 21:20 Defines pin-muxing selection for GPIO186
    uint16_t GPIO187:2;                 // 23:22 Defines pin-muxing selection for GPIO187
    uint16_t GPIO188:2;                 // 25:24 Defines pin-muxing selection for GPIO188
    uint16_t GPIO189:2;                 // 27:26 Defines pin-muxing selection for GPIO189
    uint16_t GPIO190:2;                 // 29:28 Defines pin-muxing selection for GPIO190
    uint16_t GPIO191:2;                 // 31:30 Defines pin-muxing selection for GPIO191
};

union GPIO_GPFGMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPFGMUX2_BITS  bit;
};

struct GPIO_GPFCSEL1_BITS {             // bits description
    uint16_t GPIO160:4;                 // 3:0 GPIO160 Controller CPU Select
    uint16_t GPIO161:4;                 // 7:4 GPIO161 Controller CPU Select
    uint16_t GPIO162:4;                 // 11:8 GPIO162 Controller CPU Select
    uint16_t GPIO163:4;                 // 15:12 GPIO163 Controller CPU Select
    uint16_t GPIO164:4;                 // 19:16 GPIO164 Controller CPU Select
    uint16_t GPIO165:4;                 // 23:20 GPIO165 Controller CPU Select
    uint16_t GPIO166:4;                 // 27:24 GPIO166 Controller CPU Select
    uint16_t GPIO167:4;                 // 31:28 GPIO167 Controller CPU Select
};

union GPIO_GPFCSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPFCSEL1_BITS  bit;
};

struct GPIO_GPFCSEL2_BITS {             // bits description
    uint16_t GPIO168:4;                 // 3:0 GPIO168 Controller CPU Select
    uint16_t GPIO169:4;                 // 7:4 GPIO169 Controller CPU Select
    uint16_t GPIO170:4;                 // 11:8 GPIO170 Controller CPU Select
    uint16_t GPIO171:4;                 // 15:12 GPIO171 Controller CPU Select
    uint16_t GPIO172:4;                 // 19:16 GPIO172 Controller CPU Select
    uint16_t GPIO173:4;                 // 23:20 GPIO173 Controller CPU Select
    uint16_t GPIO174:4;                 // 27:24 GPIO174 Controller CPU Select
    uint16_t GPIO175:4;                 // 31:28 GPIO175 Controller CPU Select
};

union GPIO_GPFCSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPFCSEL2_BITS  bit;
};

struct GPIO_GPFCSEL3_BITS {             // bits description
    uint16_t GPIO176:4;                 // 3:0 GPIO176 Controller CPU Select
    uint16_t GPIO177:4;                 // 7:4 GPIO177 Controller CPU Select
    uint16_t GPIO178:4;                 // 11:8 GPIO178 Controller CPU Select
    uint16_t GPIO179:4;                 // 15:12 GPIO179 Controller CPU Select
    uint16_t GPIO180:4;                 // 19:16 GPIO180 Controller CPU Select
    uint16_t GPIO181:4;                 // 23:20 GPIO181 Controller CPU Select
    uint16_t GPIO182:4;                 // 27:24 GPIO182 Controller CPU Select
    uint16_t GPIO183:4;                 // 31:28 GPIO183 Controller CPU Select
};

union GPIO_GPFCSEL3_REG {
    uint32_t  all;
    struct  GPIO_GPFCSEL3_BITS  bit;
};

struct GPIO_GPFCSEL4_BITS {             // bits description
    uint16_t GPIO184:4;                 // 3:0 GPIO184 Controller CPU Select
    uint16_t GPIO185:4;                 // 7:4 GPIO185 Controller CPU Select
    uint16_t GPIO186:4;                 // 11:8 GPIO186 Controller CPU Select
    uint16_t GPIO187:4;                 // 15:12 GPIO187 Controller CPU Select
    uint16_t GPIO188:4;                 // 19:16 GPIO188 Controller CPU Select
    uint16_t GPIO189:4;                 // 23:20 GPIO189 Controller CPU Select
    uint16_t GPIO190:4;                 // 27:24 GPIO190 Controller CPU Select
    uint16_t GPIO191:4;                 // 31:28 GPIO191 Controller CPU Select
};

union GPIO_GPFCSEL4_REG {
    uint32_t  all;
    struct  GPIO_GPFCSEL4_BITS  bit;
};

struct GPIO_GPFLOCK_BITS {              // bits description
    uint16_t GPIO160:1;                 // 0 Configuration Lock bit for this pin
    uint16_t GPIO161:1;                 // 1 Configuration Lock bit for this pin
    uint16_t GPIO162:1;                 // 2 Configuration Lock bit for this pin
    uint16_t GPIO163:1;                 // 3 Configuration Lock bit for this pin
    uint16_t GPIO164:1;                 // 4 Configuration Lock bit for this pin
    uint16_t GPIO165:1;                 // 5 Configuration Lock bit for this pin
    uint16_t GPIO166:1;                 // 6 Configuration Lock bit for this pin
    uint16_t GPIO167:1;                 // 7 Configuration Lock bit for this pin
    uint16_t GPIO168:1;                 // 8 Configuration Lock bit for this pin
    uint16_t GPIO169:1;                 // 9 Configuration Lock bit for this pin
    uint16_t GPIO170:1;                 // 10 Configuration Lock bit for this pin
    uint16_t GPIO171:1;                 // 11 Configuration Lock bit for this pin
    uint16_t GPIO172:1;                 // 12 Configuration Lock bit for this pin
    uint16_t GPIO173:1;                 // 13 Configuration Lock bit for this pin
    uint16_t GPIO174:1;                 // 14 Configuration Lock bit for this pin
    uint16_t GPIO175:1;                 // 15 Configuration Lock bit for this pin
    uint16_t GPIO176:1;                 // 16 Configuration Lock bit for this pin
    uint16_t GPIO177:1;                 // 17 Configuration Lock bit for this pin
    uint16_t GPIO178:1;                 // 18 Configuration Lock bit for this pin
    uint16_t GPIO179:1;                 // 19 Configuration Lock bit for this pin
    uint16_t GPIO180:1;                 // 20 Configuration Lock bit for this pin
    uint16_t GPIO181:1;                 // 21 Configuration Lock bit for this pin
    uint16_t GPIO182:1;                 // 22 Configuration Lock bit for this pin
    uint16_t GPIO183:1;                 // 23 Configuration Lock bit for this pin
    uint16_t GPIO184:1;                 // 24 Configuration Lock bit for this pin
    uint16_t GPIO185:1;                 // 25 Configuration Lock bit for this pin
    uint16_t GPIO186:1;                 // 26 Configuration Lock bit for this pin
    uint16_t GPIO187:1;                 // 27 Configuration Lock bit for this pin
    uint16_t GPIO188:1;                 // 28 Configuration Lock bit for this pin
    uint16_t GPIO189:1;                 // 29 Configuration Lock bit for this pin
    uint16_t GPIO190:1;                 // 30 Configuration Lock bit for this pin
    uint16_t GPIO191:1;                 // 31 Configuration Lock bit for this pin
};

union GPIO_GPFLOCK_REG {
    uint32_t  all;
    struct  GPIO_GPFLOCK_BITS  bit;
};

struct GPIO_GPFCR_BITS {                // bits description
    uint16_t GPIO160:1;                 // 0 Configuration lock commit bit for this pin
    uint16_t GPIO161:1;                 // 1 Configuration lock commit bit for this pin
    uint16_t GPIO162:1;                 // 2 Configuration lock commit bit for this pin
    uint16_t GPIO163:1;                 // 3 Configuration lock commit bit for this pin
    uint16_t GPIO164:1;                 // 4 Configuration lock commit bit for this pin
    uint16_t GPIO165:1;                 // 5 Configuration lock commit bit for this pin
    uint16_t GPIO166:1;                 // 6 Configuration lock commit bit for this pin
    uint16_t GPIO167:1;                 // 7 Configuration lock commit bit for this pin
    uint16_t GPIO168:1;                 // 8 Configuration lock commit bit for this pin
    uint16_t GPIO169:1;                 // 9 Configuration lock commit bit for this pin
    uint16_t GPIO170:1;                 // 10 Configuration lock commit bit for this pin
    uint16_t GPIO171:1;                 // 11 Configuration lock commit bit for this pin
    uint16_t GPIO172:1;                 // 12 Configuration lock commit bit for this pin
    uint16_t GPIO173:1;                 // 13 Configuration lock commit bit for this pin
    uint16_t GPIO174:1;                 // 14 Configuration lock commit bit for this pin
    uint16_t GPIO175:1;                 // 15 Configuration lock commit bit for this pin
    uint16_t GPIO176:1;                 // 16 Configuration lock commit bit for this pin
    uint16_t GPIO177:1;                 // 17 Configuration lock commit bit for this pin
    uint16_t GPIO178:1;                 // 18 Configuration lock commit bit for this pin
    uint16_t GPIO179:1;                 // 19 Configuration lock commit bit for this pin
    uint16_t GPIO180:1;                 // 20 Configuration lock commit bit for this pin
    uint16_t GPIO181:1;                 // 21 Configuration lock commit bit for this pin
    uint16_t GPIO182:1;                 // 22 Configuration lock commit bit for this pin
    uint16_t GPIO183:1;                 // 23 Configuration lock commit bit for this pin
    uint16_t GPIO184:1;                 // 24 Configuration lock commit bit for this pin
    uint16_t GPIO185:1;                 // 25 Configuration lock commit bit for this pin
    uint16_t GPIO186:1;                 // 26 Configuration lock commit bit for this pin
    uint16_t GPIO187:1;                 // 27 Configuration lock commit bit for this pin
    uint16_t GPIO188:1;                 // 28 Configuration lock commit bit for this pin
    uint16_t GPIO189:1;                 // 29 Configuration lock commit bit for this pin
    uint16_t GPIO190:1;                 // 30 Configuration lock commit bit for this pin
    uint16_t GPIO191:1;                 // 31 Configuration lock commit bit for this pin
};

union GPIO_GPFCR_REG {
    uint32_t  all;
    struct  GPIO_GPFCR_BITS  bit;
};

struct GPIO_GPGCTRL_BITS {              // bits description
    uint16_t QUALPRD0:8;                // 7:0 Qualification sampling period for GPIO192 to GPIO199
    uint16_t QUALPRD1:8;                // 15:8 Qualification sampling period for GPIO200 to GPIO207
    uint16_t QUALPRD2:8;                // 23:16 Qualification sampling period for GPIO208 to GPIO215
    uint16_t QUALPRD3:8;                // 31:24 Qualification sampling period for GPIO216 to GPIO223
};

union GPIO_GPGCTRL_REG {
    uint32_t  all;
    struct  GPIO_GPGCTRL_BITS  bit;
};

struct GPIO_GPGQSEL1_BITS {             // bits description
    uint16_t GPIO192:2;                 // 1:0 Select input qualification type for GPIO192
    uint16_t GPIO193:2;                 // 3:2 Select input qualification type for GPIO193
    uint16_t GPIO194:2;                 // 5:4 Select input qualification type for GPIO194
    uint16_t GPIO195:2;                 // 7:6 Select input qualification type for GPIO195
    uint16_t GPIO196:2;                 // 9:8 Select input qualification type for GPIO196
    uint16_t GPIO197:2;                 // 11:10 Select input qualification type for GPIO197
    uint16_t GPIO198:2;                 // 13:12 Select input qualification type for GPIO198
    uint16_t GPIO199:2;                 // 15:14 Select input qualification type for GPIO199
    uint16_t GPIO200:2;                 // 17:16 Select input qualification type for GPIO200
    uint16_t GPIO201:2;                 // 19:18 Select input qualification type for GPIO201
    uint16_t GPIO202:2;                 // 21:20 Select input qualification type for GPIO202
    uint16_t GPIO203:2;                 // 23:22 Select input qualification type for GPIO203
    uint16_t GPIO204:2;                 // 25:24 Select input qualification type for GPIO204
    uint16_t GPIO205:2;                 // 27:26 Select input qualification type for GPIO205
    uint16_t GPIO206:2;                 // 29:28 Select input qualification type for GPIO206
    uint16_t GPIO207:2;                 // 31:30 Select input qualification type for GPIO207
};

union GPIO_GPGQSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPGQSEL1_BITS  bit;
};

struct GPIO_GPGQSEL2_BITS {             // bits description
    uint16_t GPIO208:2;                 // 1:0 Select input qualification type for GPIO208
    uint16_t GPIO209:2;                 // 3:2 Select input qualification type for GPIO209
    uint16_t GPIO210:2;                 // 5:4 Select input qualification type for GPIO210
    uint16_t GPIO211:2;                 // 7:6 Select input qualification type for GPIO211
    uint16_t GPIO212:2;                 // 9:8 Select input qualification type for GPIO212
    uint16_t GPIO213:2;                 // 11:10 Select input qualification type for GPIO213
    uint16_t rsvd1:2;                   // 13:12 Reserved
    uint16_t rsvd2:2;                   // 15:14 Reserved
    uint16_t rsvd3:2;                   // 17:16 Reserved
    uint16_t rsvd4:2;                   // 19:18 Reserved
    uint16_t rsvd5:2;                   // 21:20 Reserved
    uint16_t GPIO219:2;                 // 23:22 Select input qualification type for GPIO219
    uint16_t GPIO220:2;                 // 25:24 Select input qualification type for GPIO220
    uint16_t GPIO221:2;                 // 27:26 Select input qualification type for GPIO221
    uint16_t GPIO222:2;                 // 29:28 Select input qualification type for GPIO222
    uint16_t GPIO223:2;                 // 31:30 Select input qualification type for GPIO223
};

union GPIO_GPGQSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPGQSEL2_BITS  bit;
};

struct GPIO_GPGMUX1_BITS {              // bits description
    uint16_t GPIO192:2;                 // 1:0 Defines pin-muxing selection for GPIO192
    uint16_t GPIO193:2;                 // 3:2 Defines pin-muxing selection for GPIO193
    uint16_t GPIO194:2;                 // 5:4 Defines pin-muxing selection for GPIO194
    uint16_t GPIO195:2;                 // 7:6 Defines pin-muxing selection for GPIO195
    uint16_t GPIO196:2;                 // 9:8 Defines pin-muxing selection for GPIO196
    uint16_t GPIO197:2;                 // 11:10 Defines pin-muxing selection for GPIO197
    uint16_t GPIO198:2;                 // 13:12 Defines pin-muxing selection for GPIO198
    uint16_t GPIO199:2;                 // 15:14 Defines pin-muxing selection for GPIO199
    uint16_t GPIO200:2;                 // 17:16 Defines pin-muxing selection for GPIO200
    uint16_t GPIO201:2;                 // 19:18 Defines pin-muxing selection for GPIO201
    uint16_t GPIO202:2;                 // 21:20 Defines pin-muxing selection for GPIO202
    uint16_t GPIO203:2;                 // 23:22 Defines pin-muxing selection for GPIO203
    uint16_t GPIO204:2;                 // 25:24 Defines pin-muxing selection for GPIO204
    uint16_t GPIO205:2;                 // 27:26 Defines pin-muxing selection for GPIO205
    uint16_t GPIO206:2;                 // 29:28 Defines pin-muxing selection for GPIO206
    uint16_t GPIO207:2;                 // 31:30 Defines pin-muxing selection for GPIO207
};

union GPIO_GPGMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPGMUX1_BITS  bit;
};

struct GPIO_GPGMUX2_BITS {              // bits description
    uint16_t GPIO208:2;                 // 1:0 Defines pin-muxing selection for GPIO208
    uint16_t GPIO209:2;                 // 3:2 Defines pin-muxing selection for GPIO209
    uint16_t GPIO210:2;                 // 5:4 Defines pin-muxing selection for GPIO210
    uint16_t GPIO211:2;                 // 7:6 Defines pin-muxing selection for GPIO211
    uint16_t GPIO212:2;                 // 9:8 Defines pin-muxing selection for GPIO212
    uint16_t GPIO213:2;                 // 11:10 Defines pin-muxing selection for GPIO213
    uint16_t rsvd1:2;                   // 13:12 Reserved
    uint16_t rsvd2:2;                   // 15:14 Reserved
    uint16_t rsvd3:2;                   // 17:16 Reserved
    uint16_t rsvd4:2;                   // 19:18 Reserved
    uint16_t rsvd5:2;                   // 21:20 Reserved
    uint16_t GPIO219:2;                 // 23:22 Defines pin-muxing selection for GPIO219
    uint16_t GPIO220:2;                 // 25:24 Defines pin-muxing selection for GPIO220
    uint16_t GPIO221:2;                 // 27:26 Defines pin-muxing selection for GPIO221
    uint16_t GPIO222:2;                 // 29:28 Defines pin-muxing selection for GPIO222
    uint16_t GPIO223:2;                 // 31:30 Defines pin-muxing selection for GPIO223
};

union GPIO_GPGMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPGMUX2_BITS  bit;
};

struct GPIO_GPGPUD_BITS {               // bits description
    uint16_t GPIO192:1;                 // 0 Pull-Up Disable control for this pin
    uint16_t GPIO193:1;                 // 1 Pull-Up Disable control for this pin
    uint16_t GPIO194:1;                 // 2 Pull-Up Disable control for this pin
    uint16_t GPIO195:1;                 // 3 Pull-Up Disable control for this pin
    uint16_t GPIO196:1;                 // 4 Pull-Up Disable control for this pin
    uint16_t GPIO197:1;                 // 5 Pull-Up Disable control for this pin
    uint16_t GPIO198:1;                 // 6 Pull-Up Disable control for this pin
    uint16_t GPIO199:1;                 // 7 Pull-Up Disable control for this pin
    uint16_t GPIO200:1;                 // 8 Pull-Up Disable control for this pin
    uint16_t GPIO201:1;                 // 9 Pull-Up Disable control for this pin
    uint16_t GPIO202:1;                 // 10 Pull-Up Disable control for this pin
    uint16_t GPIO203:1;                 // 11 Pull-Up Disable control for this pin
    uint16_t GPIO204:1;                 // 12 Pull-Up Disable control for this pin
    uint16_t GPIO205:1;                 // 13 Pull-Up Disable control for this pin
    uint16_t GPIO206:1;                 // 14 Pull-Up Disable control for this pin
    uint16_t GPIO207:1;                 // 15 Pull-Up Disable control for this pin
    uint16_t GPIO208:1;                 // 16 Pull-Up Disable control for this pin
    uint16_t GPIO209:1;                 // 17 Pull-Up Disable control for this pin
    uint16_t GPIO210:1;                 // 18 Pull-Up Disable control for this pin
    uint16_t GPIO211:1;                 // 19 Pull-Up Disable control for this pin
    uint16_t GPIO212:1;                 // 20 Pull-Up Disable control for this pin
    uint16_t GPIO213:1;                 // 21 Pull-Up Disable control for this pin
    uint16_t rsvd1:1;                   // 22 Reserved
    uint16_t rsvd2:1;                   // 23 Reserved
    uint16_t rsvd3:1;                   // 24 Reserved
    uint16_t rsvd4:1;                   // 25 Reserved
    uint16_t rsvd5:1;                   // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Pull-Up Disable control for this pin
    uint16_t GPIO220:1;                 // 28 Pull-Up Disable control for this pin
    uint16_t GPIO221:1;                 // 29 Pull-Up Disable control for this pin
    uint16_t GPIO222:1;                 // 30 Pull-Up Disable control for this pin
    uint16_t GPIO223:1;                 // 31 Pull-Up Disable control for this pin
};

union GPIO_GPGPUD_REG {
    uint32_t  all;
    struct  GPIO_GPGPUD_BITS  bit;
};

struct GPIO_GPGINV_BITS {               // bits description
    uint16_t GPIO192:1;                 // 0 Input inversion control for this pin
    uint16_t GPIO193:1;                 // 1 Input inversion control for this pin
    uint16_t GPIO194:1;                 // 2 Input inversion control for this pin
    uint16_t GPIO195:1;                 // 3 Input inversion control for this pin
    uint16_t GPIO196:1;                 // 4 Input inversion control for this pin
    uint16_t GPIO197:1;                 // 5 Input inversion control for this pin
    uint16_t GPIO198:1;                 // 6 Input inversion control for this pin
    uint16_t GPIO199:1;                 // 7 Input inversion control for this pin
    uint16_t GPIO200:1;                 // 8 Input inversion control for this pin
    uint16_t GPIO201:1;                 // 9 Input inversion control for this pin
    uint16_t GPIO202:1;                 // 10 Input inversion control for this pin
    uint16_t GPIO203:1;                 // 11 Input inversion control for this pin
    uint16_t GPIO204:1;                 // 12 Input inversion control for this pin
    uint16_t GPIO205:1;                 // 13 Input inversion control for this pin
    uint16_t GPIO206:1;                 // 14 Input inversion control for this pin
    uint16_t GPIO207:1;                 // 15 Input inversion control for this pin
    uint16_t GPIO208:1;                 // 16 Input inversion control for this pin
    uint16_t GPIO209:1;                 // 17 Input inversion control for this pin
    uint16_t GPIO210:1;                 // 18 Input inversion control for this pin
    uint16_t GPIO211:1;                 // 19 Input inversion control for this pin
    uint16_t GPIO212:1;                 // 20 Input inversion control for this pin
    uint16_t GPIO213:1;                 // 21 Input inversion control for this pin
    uint16_t rsvd1:1;                   // 22 Reserved
    uint16_t rsvd2:1;                   // 23 Reserved
    uint16_t rsvd3:1;                   // 24 Reserved
    uint16_t rsvd4:1;                   // 25 Reserved
    uint16_t rsvd5:1;                   // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Input inversion control for this pin
    uint16_t GPIO220:1;                 // 28 Input inversion control for this pin
    uint16_t GPIO221:1;                 // 29 Input inversion control for this pin
    uint16_t GPIO222:1;                 // 30 Input inversion control for this pin
    uint16_t GPIO223:1;                 // 31 Input inversion control for this pin
};

union GPIO_GPGINV_REG {
    uint32_t  all;
    struct  GPIO_GPGINV_BITS  bit;
};

struct GPIO_GPGODR_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:1;                   // 4 Reserved
    uint16_t rsvd6:1;                   // 5 Reserved
    uint16_t rsvd7:1;                   // 6 Reserved
    uint16_t rsvd8:1;                   // 7 Reserved
    uint16_t rsvd9:1;                   // 8 Reserved
    uint16_t rsvd10:1;                  // 9 Reserved
    uint16_t rsvd11:1;                  // 10 Reserved
    uint16_t rsvd12:1;                  // 11 Reserved
    uint16_t rsvd13:1;                  // 12 Reserved
    uint16_t rsvd14:1;                  // 13 Reserved
    uint16_t rsvd15:1;                  // 14 Reserved
    uint16_t rsvd16:1;                  // 15 Reserved
    uint16_t rsvd17:1;                  // 16 Reserved
    uint16_t rsvd18:1;                  // 17 Reserved
    uint16_t rsvd19:1;                  // 18 Reserved
    uint16_t rsvd20:1;                  // 19 Reserved
    uint16_t rsvd21:1;                  // 20 Reserved
    uint16_t rsvd22:1;                  // 21 Reserved
    uint16_t rsvd23:1;                  // 22 Reserved
    uint16_t rsvd24:1;                  // 23 Reserved
    uint16_t rsvd25:1;                  // 24 Reserved
    uint16_t rsvd26:1;                  // 25 Reserved
    uint16_t rsvd27:1;                  // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Outpout Open-Drain control for this pin
    uint16_t GPIO220:1;                 // 28 Outpout Open-Drain control for this pin
    uint16_t GPIO221:1;                 // 29 Outpout Open-Drain control for this pin
    uint16_t GPIO222:1;                 // 30 Outpout Open-Drain control for this pin
    uint16_t GPIO223:1;                 // 31 Outpout Open-Drain control for this pin
};

union GPIO_GPGODR_REG {
    uint32_t  all;
    struct  GPIO_GPGODR_BITS  bit;
};

struct GPIO_GPGAMSEL_BITS {             // bits description
    uint16_t GPIO192:1;                 // 0 Analog Mode select for this pin
    uint16_t GPIO193:1;                 // 1 Analog Mode select for this pin
    uint16_t GPIO194:1;                 // 2 Analog Mode select for this pin
    uint16_t GPIO195:1;                 // 3 Analog Mode select for this pin
    uint16_t GPIO196:1;                 // 4 Analog Mode select for this pin
    uint16_t GPIO197:1;                 // 5 Analog Mode select for this pin
    uint16_t GPIO198:1;                 // 6 Analog Mode select for this pin
    uint16_t GPIO199:1;                 // 7 Analog Mode select for this pin
    uint16_t GPIO200:1;                 // 8 Analog Mode select for this pin
    uint16_t GPIO201:1;                 // 9 Analog Mode select for this pin
    uint16_t GPIO202:1;                 // 10 Analog Mode select for this pin
    uint16_t GPIO203:1;                 // 11 Analog Mode select for this pin
    uint16_t GPIO204:1;                 // 12 Analog Mode select for this pin
    uint16_t GPIO205:1;                 // 13 Analog Mode select for this pin
    uint16_t GPIO206:1;                 // 14 Analog Mode select for this pin
    uint16_t GPIO207:1;                 // 15 Analog Mode select for this pin
    uint16_t GPIO208:1;                 // 16 Analog Mode select for this pin
    uint16_t GPIO209:1;                 // 17 Analog Mode select for this pin
    uint16_t GPIO210:1;                 // 18 Analog Mode select for this pin
    uint16_t GPIO211:1;                 // 19 Analog Mode select for this pin
    uint16_t GPIO212:1;                 // 20 Analog Mode select for this pin
    uint16_t GPIO213:1;                 // 21 Analog Mode select for this pin
    uint16_t rsvd1:1;                   // 22 Reserved
    uint16_t rsvd2:1;                   // 23 Reserved
    uint16_t rsvd3:1;                   // 24 Reserved
    uint16_t rsvd4:1;                   // 25 Reserved
    uint16_t rsvd5:1;                   // 26 Reserved
    uint16_t rsvd6:1;                   // 27 Reserved
    uint16_t rsvd7:1;                   // 28 Reserved
    uint16_t rsvd8:1;                   // 29 Reserved
    uint16_t rsvd9:1;                   // 30 Reserved
    uint16_t rsvd10:1;                  // 31 Reserved
};

union GPIO_GPGAMSEL_REG {
    uint32_t  all;
    struct  GPIO_GPGAMSEL_BITS  bit;
};

struct GPIO_GPGGMUX1_BITS {             // bits description
    uint16_t GPIO192:2;                 // 1:0 Defines pin-muxing selection for GPIO192
    uint16_t GPIO193:2;                 // 3:2 Defines pin-muxing selection for GPIO193
    uint16_t GPIO194:2;                 // 5:4 Defines pin-muxing selection for GPIO194
    uint16_t GPIO195:2;                 // 7:6 Defines pin-muxing selection for GPIO195
    uint16_t GPIO196:2;                 // 9:8 Defines pin-muxing selection for GPIO196
    uint16_t GPIO197:2;                 // 11:10 Defines pin-muxing selection for GPIO197
    uint16_t GPIO198:2;                 // 13:12 Defines pin-muxing selection for GPIO198
    uint16_t GPIO199:2;                 // 15:14 Defines pin-muxing selection for GPIO199
    uint16_t GPIO200:2;                 // 17:16 Defines pin-muxing selection for GPIO200
    uint16_t GPIO201:2;                 // 19:18 Defines pin-muxing selection for GPIO201
    uint16_t GPIO202:2;                 // 21:20 Defines pin-muxing selection for GPIO202
    uint16_t GPIO203:2;                 // 23:22 Defines pin-muxing selection for GPIO203
    uint16_t GPIO204:2;                 // 25:24 Defines pin-muxing selection for GPIO204
    uint16_t GPIO205:2;                 // 27:26 Defines pin-muxing selection for GPIO205
    uint16_t GPIO206:2;                 // 29:28 Defines pin-muxing selection for GPIO206
    uint16_t GPIO207:2;                 // 31:30 Defines pin-muxing selection for GPIO207
};

union GPIO_GPGGMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPGGMUX1_BITS  bit;
};

struct GPIO_GPGGMUX2_BITS {             // bits description
    uint16_t GPIO208:2;                 // 1:0 Defines pin-muxing selection for GPIO208
    uint16_t GPIO209:2;                 // 3:2 Defines pin-muxing selection for GPIO209
    uint16_t GPIO210:2;                 // 5:4 Defines pin-muxing selection for GPIO210
    uint16_t GPIO211:2;                 // 7:6 Defines pin-muxing selection for GPIO211
    uint16_t GPIO212:2;                 // 9:8 Defines pin-muxing selection for GPIO212
    uint16_t GPIO213:2;                 // 11:10 Defines pin-muxing selection for GPIO213
    uint16_t rsvd1:2;                   // 13:12 Reserved
    uint16_t rsvd2:2;                   // 15:14 Reserved
    uint16_t rsvd3:2;                   // 17:16 Reserved
    uint16_t rsvd4:2;                   // 19:18 Reserved
    uint16_t rsvd5:2;                   // 21:20 Reserved
    uint16_t GPIO219:2;                 // 23:22 Defines pin-muxing selection for GPIO219
    uint16_t GPIO220:2;                 // 25:24 Defines pin-muxing selection for GPIO220
    uint16_t GPIO221:2;                 // 27:26 Defines pin-muxing selection for GPIO221
    uint16_t GPIO222:2;                 // 29:28 Defines pin-muxing selection for GPIO222
    uint16_t GPIO223:2;                 // 31:30 Defines pin-muxing selection for GPIO223
};

union GPIO_GPGGMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPGGMUX2_BITS  bit;
};

struct GPIO_GPGCSEL1_BITS {             // bits description
    uint16_t GPIO192:4;                 // 3:0 GPIO192 Controller CPU Select
    uint16_t GPIO193:4;                 // 7:4 GPIO193 Controller CPU Select
    uint16_t GPIO194:4;                 // 11:8 GPIO194 Controller CPU Select
    uint16_t GPIO195:4;                 // 15:12 GPIO195 Controller CPU Select
    uint16_t GPIO196:4;                 // 19:16 GPIO196 Controller CPU Select
    uint16_t GPIO197:4;                 // 23:20 GPIO197 Controller CPU Select
    uint16_t GPIO198:4;                 // 27:24 GPIO198 Controller CPU Select
    uint16_t GPIO199:4;                 // 31:28 GPIO199 Controller CPU Select
};

union GPIO_GPGCSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPGCSEL1_BITS  bit;
};

struct GPIO_GPGCSEL2_BITS {             // bits description
    uint16_t GPIO200:4;                 // 3:0 GPIO200 Controller CPU Select
    uint16_t GPIO201:4;                 // 7:4 GPIO201 Controller CPU Select
    uint16_t GPIO202:4;                 // 11:8 GPIO202 Controller CPU Select
    uint16_t GPIO203:4;                 // 15:12 GPIO203 Controller CPU Select
    uint16_t GPIO204:4;                 // 19:16 GPIO204 Controller CPU Select
    uint16_t GPIO205:4;                 // 23:20 GPIO205 Controller CPU Select
    uint16_t GPIO206:4;                 // 27:24 GPIO206 Controller CPU Select
    uint16_t GPIO207:4;                 // 31:28 GPIO207 Controller CPU Select
};

union GPIO_GPGCSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPGCSEL2_BITS  bit;
};

struct GPIO_GPGCSEL3_BITS {             // bits description
    uint16_t GPIO208:4;                 // 3:0 GPIO208 Controller CPU Select
    uint16_t GPIO209:4;                 // 7:4 GPIO209 Controller CPU Select
    uint16_t GPIO210:4;                 // 11:8 GPIO210 Controller CPU Select
    uint16_t GPIO211:4;                 // 15:12 GPIO211 Controller CPU Select
    uint16_t GPIO212:4;                 // 19:16 GPIO212 Controller CPU Select
    uint16_t GPIO213:4;                 // 23:20 GPIO213 Controller CPU Select
    uint16_t rsvd1:4;                   // 27:24 Reserved
    uint16_t rsvd2:4;                   // 31:28 Reserved
};

union GPIO_GPGCSEL3_REG {
    uint32_t  all;
    struct  GPIO_GPGCSEL3_BITS  bit;
};

struct GPIO_GPGCSEL4_BITS {             // bits description
    uint16_t rsvd1:4;                   // 3:0 Reserved
    uint16_t rsvd2:4;                   // 7:4 Reserved
    uint16_t rsvd3:4;                   // 11:8 Reserved
    uint16_t GPIO219:4;                 // 15:12 GPIO219 Controller CPU Select
    uint16_t GPIO220:4;                 // 19:16 GPIO220 Controller CPU Select
    uint16_t GPIO221:4;                 // 23:20 GPIO221 Controller CPU Select
    uint16_t GPIO222:4;                 // 27:24 GPIO222 Controller CPU Select
    uint16_t GPIO223:4;                 // 31:28 GPIO223 Controller CPU Select
};

union GPIO_GPGCSEL4_REG {
    uint32_t  all;
    struct  GPIO_GPGCSEL4_BITS  bit;
};

struct GPIO_GPGLOCK_BITS {              // bits description
    uint16_t GPIO192:1;                 // 0 Configuration Lock bit for this pin
    uint16_t GPIO193:1;                 // 1 Configuration Lock bit for this pin
    uint16_t GPIO194:1;                 // 2 Configuration Lock bit for this pin
    uint16_t GPIO195:1;                 // 3 Configuration Lock bit for this pin
    uint16_t GPIO196:1;                 // 4 Configuration Lock bit for this pin
    uint16_t GPIO197:1;                 // 5 Configuration Lock bit for this pin
    uint16_t GPIO198:1;                 // 6 Configuration Lock bit for this pin
    uint16_t GPIO199:1;                 // 7 Configuration Lock bit for this pin
    uint16_t GPIO200:1;                 // 8 Configuration Lock bit for this pin
    uint16_t GPIO201:1;                 // 9 Configuration Lock bit for this pin
    uint16_t GPIO202:1;                 // 10 Configuration Lock bit for this pin
    uint16_t GPIO203:1;                 // 11 Configuration Lock bit for this pin
    uint16_t GPIO204:1;                 // 12 Configuration Lock bit for this pin
    uint16_t GPIO205:1;                 // 13 Configuration Lock bit for this pin
    uint16_t GPIO206:1;                 // 14 Configuration Lock bit for this pin
    uint16_t GPIO207:1;                 // 15 Configuration Lock bit for this pin
    uint16_t GPIO208:1;                 // 16 Configuration Lock bit for this pin
    uint16_t GPIO209:1;                 // 17 Configuration Lock bit for this pin
    uint16_t GPIO210:1;                 // 18 Configuration Lock bit for this pin
    uint16_t GPIO211:1;                 // 19 Configuration Lock bit for this pin
    uint16_t GPIO212:1;                 // 20 Configuration Lock bit for this pin
    uint16_t GPIO213:1;                 // 21 Configuration Lock bit for this pin
    uint16_t rsvd1:1;                   // 22 Reserved
    uint16_t rsvd2:1;                   // 23 Reserved
    uint16_t rsvd3:1;                   // 24 Reserved
    uint16_t rsvd4:1;                   // 25 Reserved
    uint16_t rsvd5:1;                   // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Configuration Lock bit for this pin
    uint16_t GPIO220:1;                 // 28 Configuration Lock bit for this pin
    uint16_t GPIO221:1;                 // 29 Configuration Lock bit for this pin
    uint16_t GPIO222:1;                 // 30 Configuration Lock bit for this pin
    uint16_t GPIO223:1;                 // 31 Configuration Lock bit for this pin
};

union GPIO_GPGLOCK_REG {
    uint32_t  all;
    struct  GPIO_GPGLOCK_BITS  bit;
};

struct GPIO_GPGCR_BITS {                // bits description
    uint16_t GPIO192:1;                 // 0 Configuration lock commit bit for this pin
    uint16_t GPIO193:1;                 // 1 Configuration lock commit bit for this pin
    uint16_t GPIO194:1;                 // 2 Configuration lock commit bit for this pin
    uint16_t GPIO195:1;                 // 3 Configuration lock commit bit for this pin
    uint16_t GPIO196:1;                 // 4 Configuration lock commit bit for this pin
    uint16_t GPIO197:1;                 // 5 Configuration lock commit bit for this pin
    uint16_t GPIO198:1;                 // 6 Configuration lock commit bit for this pin
    uint16_t GPIO199:1;                 // 7 Configuration lock commit bit for this pin
    uint16_t GPIO200:1;                 // 8 Configuration lock commit bit for this pin
    uint16_t GPIO201:1;                 // 9 Configuration lock commit bit for this pin
    uint16_t GPIO202:1;                 // 10 Configuration lock commit bit for this pin
    uint16_t GPIO203:1;                 // 11 Configuration lock commit bit for this pin
    uint16_t GPIO204:1;                 // 12 Configuration lock commit bit for this pin
    uint16_t GPIO205:1;                 // 13 Configuration lock commit bit for this pin
    uint16_t GPIO206:1;                 // 14 Configuration lock commit bit for this pin
    uint16_t GPIO207:1;                 // 15 Configuration lock commit bit for this pin
    uint16_t GPIO208:1;                 // 16 Configuration lock commit bit for this pin
    uint16_t GPIO209:1;                 // 17 Configuration lock commit bit for this pin
    uint16_t GPIO210:1;                 // 18 Configuration lock commit bit for this pin
    uint16_t GPIO211:1;                 // 19 Configuration lock commit bit for this pin
    uint16_t GPIO212:1;                 // 20 Configuration lock commit bit for this pin
    uint16_t GPIO213:1;                 // 21 Configuration lock commit bit for this pin
    uint16_t rsvd1:1;                   // 22 Reserved
    uint16_t rsvd2:1;                   // 23 Reserved
    uint16_t rsvd3:1;                   // 24 Reserved
    uint16_t rsvd4:1;                   // 25 Reserved
    uint16_t rsvd5:1;                   // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Configuration lock commit bit for this pin
    uint16_t GPIO220:1;                 // 28 Configuration lock commit bit for this pin
    uint16_t GPIO221:1;                 // 29 Configuration lock commit bit for this pin
    uint16_t GPIO222:1;                 // 30 Configuration lock commit bit for this pin
    uint16_t GPIO223:1;                 // 31 Configuration lock commit bit for this pin
};

union GPIO_GPGCR_REG {
    uint32_t  all;
    struct  GPIO_GPGCR_BITS  bit;
};

struct GPIO_GPHCTRL_BITS {              // bits description
    uint16_t QUALPRD0:8;                // 7:0 Qualification sampling period for GPIO224 to GPIO231
    uint16_t QUALPRD1:8;                // 15:8 Qualification sampling period for GPIO232 to GPIO239
    uint16_t QUALPRD2:8;                // 23:16 Qualification sampling period for GPIO240 to GPIO247
    uint16_t QUALPRD3:8;                // 31:24 Qualification sampling period for GPIO248 to GPIO255
};

union GPIO_GPHCTRL_REG {
    uint32_t  all;
    struct  GPIO_GPHCTRL_BITS  bit;
};

struct GPIO_GPHQSEL1_BITS {             // bits description
    uint16_t GPIO224:2;                 // 1:0 Select input qualification type for this GPIO Pin
    uint16_t GPIO225:2;                 // 3:2 Select input qualification type for this GPIO Pin
    uint16_t GPIO226:2;                 // 5:4 Select input qualification type for this GPIO Pin
    uint16_t GPIO227:2;                 // 7:6 Select input qualification type for this GPIO Pin
    uint16_t GPIO228:2;                 // 9:8 Select input qualification type for this GPIO Pin
    uint16_t GPIO229:2;                 // 11:10 Select input qualification type for this GPIO Pin
    uint16_t GPIO230:2;                 // 13:12 Select input qualification type for this GPIO Pin
    uint16_t GPIO231:2;                 // 15:14 Select input qualification type for this GPIO Pin
    uint16_t GPIO232:2;                 // 17:16 Select input qualification type for this GPIO Pin
    uint16_t GPIO233:2;                 // 19:18 Select input qualification type for this GPIO Pin
    uint16_t GPIO234:2;                 // 21:20 Select input qualification type for this GPIO Pin
    uint16_t GPIO235:2;                 // 23:22 Select input qualification type for this GPIO Pin
    uint16_t GPIO236:2;                 // 25:24 Select input qualification type for this GPIO Pin
    uint16_t GPIO237:2;                 // 27:26 Select input qualification type for this GPIO Pin
    uint16_t GPIO238:2;                 // 29:28 Select input qualification type for this GPIO Pin
    uint16_t GPIO239:2;                 // 31:30 Select input qualification type for this GPIO Pin
};

union GPIO_GPHQSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPHQSEL1_BITS  bit;
};

struct GPIO_GPHQSEL2_BITS {             // bits description
    uint16_t GPIO240:2;                 // 1:0 Select input qualification type for this GPIO Pin
    uint16_t GPIO241:2;                 // 3:2 Select input qualification type for this GPIO Pin
    uint16_t GPIO242:2;                 // 5:4 Select input qualification type for this GPIO Pin
    uint16_t GPIO243:2;                 // 7:6 Select input qualification type for this GPIO Pin
    uint16_t GPIO244:2;                 // 9:8 Select input qualification type for this GPIO Pin
    uint16_t GPIO245:2;                 // 11:10 Select input qualification type for this GPIO Pin
    uint16_t GPIO246:2;                 // 13:12 Select input qualification type for this GPIO Pin
    uint16_t GPIO247:2;                 // 15:14 Select input qualification type for this GPIO Pin
    uint16_t GPIO248:2;                 // 17:16 Select input qualification type for this GPIO Pin
    uint16_t GPIO249:2;                 // 19:18 Select input qualification type for this GPIO Pin
    uint16_t rsvd1:2;                   // 21:20 Reserved
    uint16_t rsvd2:2;                   // 23:22 Reserved
    uint16_t rsvd3:2;                   // 25:24 Reserved
    uint16_t rsvd4:2;                   // 27:26 Reserved
    uint16_t rsvd5:2;                   // 29:28 Reserved
    uint16_t rsvd6:2;                   // 31:30 Reserved
};

union GPIO_GPHQSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPHQSEL2_BITS  bit;
};

struct GPIO_GPHMUX1_BITS {              // bits description
    uint16_t GPIO224:2;                 // 1:0 Defines pin-muxing selection for GPIO224
    uint16_t GPIO225:2;                 // 3:2 Defines pin-muxing selection for GPIO225
    uint16_t GPIO226:2;                 // 5:4 Defines pin-muxing selection for GPIO226
    uint16_t GPIO227:2;                 // 7:6 Defines pin-muxing selection for GPIO227
    uint16_t GPIO228:2;                 // 9:8 Defines pin-muxing selection for GPIO228
    uint16_t GPIO229:2;                 // 11:10 Defines pin-muxing selection for GPIO229
    uint16_t GPIO230:2;                 // 13:12 Defines pin-muxing selection for GPIO230
    uint16_t GPIO231:2;                 // 15:14 Defines pin-muxing selection for GPIO231
    uint16_t GPIO232:2;                 // 17:16 Defines pin-muxing selection for GPIO232
    uint16_t GPIO233:2;                 // 19:18 Defines pin-muxing selection for GPIO233
    uint16_t GPIO234:2;                 // 21:20 Defines pin-muxing selection for GPIO234
    uint16_t GPIO235:2;                 // 23:22 Defines pin-muxing selection for GPIO235
    uint16_t GPIO236:2;                 // 25:24 Defines pin-muxing selection for GPIO236
    uint16_t GPIO237:2;                 // 27:26 Defines pin-muxing selection for GPIO237
    uint16_t GPIO238:2;                 // 29:28 Defines pin-muxing selection for GPIO238
    uint16_t GPIO239:2;                 // 31:30 Defines pin-muxing selection for GPIO239
};

union GPIO_GPHMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPHMUX1_BITS  bit;
};

struct GPIO_GPHMUX2_BITS {              // bits description
    uint16_t GPIO240:2;                 // 1:0 Defines pin-muxing selection for GPIO240
    uint16_t GPIO241:2;                 // 3:2 Defines pin-muxing selection for GPIO241
    uint16_t GPIO242:2;                 // 5:4 Defines pin-muxing selection for GPIO242
    uint16_t GPIO243:2;                 // 7:6 Defines pin-muxing selection for GPIO243
    uint16_t GPIO244:2;                 // 9:8 Defines pin-muxing selection for GPIO244
    uint16_t GPIO245:2;                 // 11:10 Defines pin-muxing selection for GPIO245
    uint16_t GPIO246:2;                 // 13:12 Defines pin-muxing selection for GPIO246
    uint16_t GPIO247:2;                 // 15:14 Defines pin-muxing selection for GPIO247
    uint16_t GPIO248:2;                 // 17:16 Defines pin-muxing selection for GPIO248
    uint16_t GPIO249:2;                 // 19:18 Defines pin-muxing selection for GPIO249
    uint16_t rsvd1:2;                   // 21:20 Reserved
    uint16_t rsvd2:2;                   // 23:22 Reserved
    uint16_t rsvd3:2;                   // 25:24 Reserved
    uint16_t rsvd4:2;                   // 27:26 Reserved
    uint16_t rsvd5:2;                   // 29:28 Reserved
    uint16_t rsvd6:2;                   // 31:30 Reserved
};

union GPIO_GPHMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPHMUX2_BITS  bit;
};

struct GPIO_GPHPUD_BITS {               // bits description
    uint16_t GPIO224:1;                 // 0 Pull-Up Disable control for this pin
    uint16_t GPIO225:1;                 // 1 Pull-Up Disable control for this pin
    uint16_t GPIO226:1;                 // 2 Pull-Up Disable control for this pin
    uint16_t GPIO227:1;                 // 3 Pull-Up Disable control for this pin
    uint16_t GPIO228:1;                 // 4 Pull-Up Disable control for this pin
    uint16_t GPIO229:1;                 // 5 Pull-Up Disable control for this pin
    uint16_t GPIO230:1;                 // 6 Pull-Up Disable control for this pin
    uint16_t GPIO231:1;                 // 7 Pull-Up Disable control for this pin
    uint16_t GPIO232:1;                 // 8 Pull-Up Disable control for this pin
    uint16_t GPIO233:1;                 // 9 Pull-Up Disable control for this pin
    uint16_t GPIO234:1;                 // 10 Pull-Up Disable control for this pin
    uint16_t GPIO235:1;                 // 11 Pull-Up Disable control for this pin
    uint16_t GPIO236:1;                 // 12 Pull-Up Disable control for this pin
    uint16_t GPIO237:1;                 // 13 Pull-Up Disable control for this pin
    uint16_t GPIO238:1;                 // 14 Pull-Up Disable control for this pin
    uint16_t GPIO239:1;                 // 15 Pull-Up Disable control for this pin
    uint16_t GPIO240:1;                 // 16 Pull-Up Disable control for this pin
    uint16_t GPIO241:1;                 // 17 Pull-Up Disable control for this pin
    uint16_t GPIO242:1;                 // 18 Pull-Up Disable control for this pin
    uint16_t GPIO243:1;                 // 19 Pull-Up Disable control for this pin
    uint16_t GPIO244:1;                 // 20 Pull-Up Disable control for this pin
    uint16_t GPIO245:1;                 // 21 Pull-Up Disable control for this pin
    uint16_t GPIO246:1;                 // 22 Pull-Up Disable control for this pin
    uint16_t GPIO247:1;                 // 23 Pull-Up Disable control for this pin
    uint16_t GPIO248:1;                 // 24 Pull-Up Disable control for this pin
    uint16_t GPIO249:1;                 // 25 Pull-Up Disable control for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHPUD_REG {
    uint32_t  all;
    struct  GPIO_GPHPUD_BITS  bit;
};

struct GPIO_GPHINV_BITS {               // bits description
    uint16_t GPIO224:1;                 // 0 Input inversion control for this pin
    uint16_t GPIO225:1;                 // 1 Input inversion control for this pin
    uint16_t GPIO226:1;                 // 2 Input inversion control for this pin
    uint16_t GPIO227:1;                 // 3 Input inversion control for this pin
    uint16_t GPIO228:1;                 // 4 Input inversion control for this pin
    uint16_t GPIO229:1;                 // 5 Input inversion control for this pin
    uint16_t GPIO230:1;                 // 6 Input inversion control for this pin
    uint16_t GPIO231:1;                 // 7 Input inversion control for this pin
    uint16_t GPIO232:1;                 // 8 Input inversion control for this pin
    uint16_t GPIO233:1;                 // 9 Input inversion control for this pin
    uint16_t GPIO234:1;                 // 10 Input inversion control for this pin
    uint16_t GPIO235:1;                 // 11 Input inversion control for this pin
    uint16_t GPIO236:1;                 // 12 Input inversion control for this pin
    uint16_t GPIO237:1;                 // 13 Input inversion control for this pin
    uint16_t GPIO238:1;                 // 14 Input inversion control for this pin
    uint16_t GPIO239:1;                 // 15 Input inversion control for this pin
    uint16_t GPIO240:1;                 // 16 Input inversion control for this pin
    uint16_t GPIO241:1;                 // 17 Input inversion control for this pin
    uint16_t GPIO242:1;                 // 18 Input inversion control for this pin
    uint16_t GPIO243:1;                 // 19 Input inversion control for this pin
    uint16_t GPIO244:1;                 // 20 Input inversion control for this pin
    uint16_t GPIO245:1;                 // 21 Input inversion control for this pin
    uint16_t GPIO246:1;                 // 22 Input inversion control for this pin
    uint16_t GPIO247:1;                 // 23 Input inversion control for this pin
    uint16_t GPIO248:1;                 // 24 Input inversion control for this pin
    uint16_t GPIO249:1;                 // 25 Input inversion control for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHINV_REG {
    uint32_t  all;
    struct  GPIO_GPHINV_BITS  bit;
};

struct GPIO_GPHODR_BITS {               // bits description
    uint16_t GPIO224:1;                 // 0 Outpout Open-Drain control for this pin
    uint16_t GPIO225:1;                 // 1 Outpout Open-Drain control for this pin
    uint16_t GPIO226:1;                 // 2 Outpout Open-Drain control for this pin
    uint16_t GPIO227:1;                 // 3 Outpout Open-Drain control for this pin
    uint16_t GPIO228:1;                 // 4 Outpout Open-Drain control for this pin
    uint16_t GPIO229:1;                 // 5 Outpout Open-Drain control for this pin
    uint16_t GPIO230:1;                 // 6 Outpout Open-Drain control for this pin
    uint16_t GPIO231:1;                 // 7 Outpout Open-Drain control for this pin
    uint16_t GPIO232:1;                 // 8 Outpout Open-Drain control for this pin
    uint16_t GPIO233:1;                 // 9 Outpout Open-Drain control for this pin
    uint16_t GPIO234:1;                 // 10 Outpout Open-Drain control for this pin
    uint16_t GPIO235:1;                 // 11 Outpout Open-Drain control for this pin
    uint16_t GPIO236:1;                 // 12 Outpout Open-Drain control for this pin
    uint16_t GPIO237:1;                 // 13 Outpout Open-Drain control for this pin
    uint16_t GPIO238:1;                 // 14 Outpout Open-Drain control for this pin
    uint16_t GPIO239:1;                 // 15 Outpout Open-Drain control for this pin
    uint16_t GPIO240:1;                 // 16 Outpout Open-Drain control for this pin
    uint16_t GPIO241:1;                 // 17 Outpout Open-Drain control for this pin
    uint16_t GPIO242:1;                 // 18 Outpout Open-Drain control for this pin
    uint16_t GPIO243:1;                 // 19 Outpout Open-Drain control for this pin
    uint16_t GPIO244:1;                 // 20 Outpout Open-Drain control for this pin
    uint16_t GPIO245:1;                 // 21 Outpout Open-Drain control for this pin
    uint16_t GPIO246:1;                 // 22 Outpout Open-Drain control for this pin
    uint16_t GPIO247:1;                 // 23 Outpout Open-Drain control for this pin
    uint16_t GPIO248:1;                 // 24 Outpout Open-Drain control for this pin
    uint16_t GPIO249:1;                 // 25 Outpout Open-Drain control for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHODR_REG {
    uint32_t  all;
    struct  GPIO_GPHODR_BITS  bit;
};

struct GPIO_GPHAMSEL_BITS {             // bits description
    uint16_t GPIO224:1;                 // 0 Analog Mode select for this pin
    uint16_t GPIO225:1;                 // 1 Analog Mode select for this pin
    uint16_t GPIO226:1;                 // 2 Analog Mode select for this pin
    uint16_t GPIO227:1;                 // 3 Analog Mode select for this pin
    uint16_t GPIO228:1;                 // 4 Analog Mode select for this pin
    uint16_t GPIO229:1;                 // 5 Analog Mode select for this pin
    uint16_t GPIO230:1;                 // 6 Analog Mode select for this pin
    uint16_t GPIO231:1;                 // 7 Analog Mode select for this pin
    uint16_t GPIO232:1;                 // 8 Analog Mode select for this pin
    uint16_t GPIO233:1;                 // 9 Analog Mode select for this pin
    uint16_t GPIO234:1;                 // 10 Analog Mode select for this pin
    uint16_t GPIO235:1;                 // 11 Analog Mode select for this pin
    uint16_t GPIO236:1;                 // 12 Analog Mode select for this pin
    uint16_t GPIO237:1;                 // 13 Analog Mode select for this pin
    uint16_t GPIO238:1;                 // 14 Analog Mode select for this pin
    uint16_t GPIO239:1;                 // 15 Analog Mode select for this pin
    uint16_t GPIO240:1;                 // 16 Analog Mode select for this pin
    uint16_t GPIO241:1;                 // 17 Analog Mode select for this pin
    uint16_t GPIO242:1;                 // 18 Analog Mode select for this pin
    uint16_t GPIO243:1;                 // 19 Analog Mode select for this pin
    uint16_t GPIO244:1;                 // 20 Analog Mode select for this pin
    uint16_t GPIO245:1;                 // 21 Analog Mode select for this pin
    uint16_t GPIO246:1;                 // 22 Analog Mode select for this pin
    uint16_t GPIO247:1;                 // 23 Analog Mode select for this pin
    uint16_t GPIO248:1;                 // 24 Analog Mode select for this pin
    uint16_t GPIO249:1;                 // 25 Analog Mode select for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHAMSEL_REG {
    uint32_t  all;
    struct  GPIO_GPHAMSEL_BITS  bit;
};

struct GPIO_GPHGMUX1_BITS {             // bits description
    uint16_t GPIO224:2;                 // 1:0 Defines pin-muxing selection for GPIO224
    uint16_t GPIO225:2;                 // 3:2 Defines pin-muxing selection for GPIO225
    uint16_t GPIO226:2;                 // 5:4 Defines pin-muxing selection for GPIO226
    uint16_t GPIO227:2;                 // 7:6 Defines pin-muxing selection for GPIO227
    uint16_t GPIO228:2;                 // 9:8 Defines pin-muxing selection for GPIO228
    uint16_t GPIO229:2;                 // 11:10 Defines pin-muxing selection for GPIO229
    uint16_t GPIO230:2;                 // 13:12 Defines pin-muxing selection for GPIO230
    uint16_t GPIO231:2;                 // 15:14 Defines pin-muxing selection for GPIO231
    uint16_t GPIO232:2;                 // 17:16 Defines pin-muxing selection for GPIO232
    uint16_t GPIO233:2;                 // 19:18 Defines pin-muxing selection for GPIO233
    uint16_t GPIO234:2;                 // 21:20 Defines pin-muxing selection for GPIO234
    uint16_t GPIO235:2;                 // 23:22 Defines pin-muxing selection for GPIO235
    uint16_t GPIO236:2;                 // 25:24 Defines pin-muxing selection for GPIO236
    uint16_t GPIO237:2;                 // 27:26 Defines pin-muxing selection for GPIO237
    uint16_t GPIO238:2;                 // 29:28 Defines pin-muxing selection for GPIO238
    uint16_t GPIO239:2;                 // 31:30 Defines pin-muxing selection for GPIO239
};

union GPIO_GPHGMUX1_REG {
    uint32_t  all;
    struct  GPIO_GPHGMUX1_BITS  bit;
};

struct GPIO_GPHGMUX2_BITS {             // bits description
    uint16_t GPIO240:2;                 // 1:0 Defines pin-muxing selection for GPIO240
    uint16_t GPIO241:2;                 // 3:2 Defines pin-muxing selection for GPIO241
    uint16_t GPIO242:2;                 // 5:4 Defines pin-muxing selection for GPIO242
    uint16_t GPIO243:2;                 // 7:6 Defines pin-muxing selection for GPIO243
    uint16_t GPIO244:2;                 // 9:8 Defines pin-muxing selection for GPIO244
    uint16_t GPIO245:2;                 // 11:10 Defines pin-muxing selection for GPIO245
    uint16_t GPIO246:2;                 // 13:12 Defines pin-muxing selection for GPIO246
    uint16_t GPIO247:2;                 // 15:14 Defines pin-muxing selection for GPIO247
    uint16_t GPIO248:2;                 // 17:16 Defines pin-muxing selection for GPIO248
    uint16_t GPIO249:2;                 // 19:18 Defines pin-muxing selection for GPIO249
    uint16_t rsvd1:2;                   // 21:20 Reserved
    uint16_t rsvd2:2;                   // 23:22 Reserved
    uint16_t rsvd3:2;                   // 25:24 Reserved
    uint16_t rsvd4:2;                   // 27:26 Reserved
    uint16_t rsvd5:2;                   // 29:28 Reserved
    uint16_t rsvd6:2;                   // 31:30 Reserved
};

union GPIO_GPHGMUX2_REG {
    uint32_t  all;
    struct  GPIO_GPHGMUX2_BITS  bit;
};

struct GPIO_GPHCSEL1_BITS {             // bits description
    uint16_t GPIO224:4;                 // 3:0 GPIO224 Controller CPU Select
    uint16_t GPIO225:4;                 // 7:4 GPIO225 Controller CPU Select
    uint16_t GPIO226:4;                 // 11:8 GPIO226 Controller CPU Select
    uint16_t GPIO227:4;                 // 15:12 GPIO227 Controller CPU Select
    uint16_t GPIO228:4;                 // 19:16 GPIO228 Controller CPU Select
    uint16_t GPIO229:4;                 // 23:20 GPIO229 Controller CPU Select
    uint16_t GPIO230:4;                 // 27:24 GPIO230 Controller CPU Select
    uint16_t GPIO231:4;                 // 31:28 GPIO231 Controller CPU Select
};

union GPIO_GPHCSEL1_REG {
    uint32_t  all;
    struct  GPIO_GPHCSEL1_BITS  bit;
};

struct GPIO_GPHCSEL2_BITS {             // bits description
    uint16_t GPIO232:4;                 // 3:0 GPIO232 Controller CPU Select
    uint16_t GPIO233:4;                 // 7:4 GPIO233 Controller CPU Select
    uint16_t GPIO234:4;                 // 11:8 GPIO234 Controller CPU Select
    uint16_t GPIO235:4;                 // 15:12 GPIO235 Controller CPU Select
    uint16_t GPIO236:4;                 // 19:16 GPIO236 Controller CPU Select
    uint16_t GPIO237:4;                 // 23:20 GPIO237 Controller CPU Select
    uint16_t GPIO238:4;                 // 27:24 GPIO238 Controller CPU Select
    uint16_t GPIO239:4;                 // 31:28 GPIO239 Controller CPU Select
};

union GPIO_GPHCSEL2_REG {
    uint32_t  all;
    struct  GPIO_GPHCSEL2_BITS  bit;
};

struct GPIO_GPHCSEL3_BITS {             // bits description
    uint16_t GPIO240:4;                 // 3:0 GPIO240 Controller CPU Select
    uint16_t GPIO241:4;                 // 7:4 GPIO241 Controller CPU Select
    uint16_t GPIO242:4;                 // 11:8 GPIO242 Controller CPU Select
    uint16_t GPIO243:4;                 // 15:12 GPIO243 Controller CPU Select
    uint16_t GPIO244:4;                 // 19:16 GPIO244 Controller CPU Select
    uint16_t GPIO245:4;                 // 23:20 GPIO245 Controller CPU Select
    uint16_t GPIO246:4;                 // 27:24 GPIO246 Controller CPU Select
    uint16_t GPIO247:4;                 // 31:28 GPIO247 Controller CPU Select
};

union GPIO_GPHCSEL3_REG {
    uint32_t  all;
    struct  GPIO_GPHCSEL3_BITS  bit;
};

struct GPIO_GPHCSEL4_BITS {             // bits description
    uint16_t GPIO248:4;                 // 3:0 GPIO248 Controller CPU Select
    uint16_t GPIO249:4;                 // 7:4 GPIO249 Controller CPU Select
    uint16_t rsvd1:4;                   // 11:8 Reserved
    uint16_t rsvd2:4;                   // 15:12 Reserved
    uint16_t rsvd3:4;                   // 19:16 Reserved
    uint16_t rsvd4:4;                   // 23:20 Reserved
    uint16_t rsvd5:4;                   // 27:24 Reserved
    uint16_t rsvd6:4;                   // 31:28 Reserved
};

union GPIO_GPHCSEL4_REG {
    uint32_t  all;
    struct  GPIO_GPHCSEL4_BITS  bit;
};

struct GPIO_GPHLOCK_BITS {              // bits description
    uint16_t GPIO224:1;                 // 0 Configuration Lock bit for this pin
    uint16_t GPIO225:1;                 // 1 Configuration Lock bit for this pin
    uint16_t GPIO226:1;                 // 2 Configuration Lock bit for this pin
    uint16_t GPIO227:1;                 // 3 Configuration Lock bit for this pin
    uint16_t GPIO228:1;                 // 4 Configuration Lock bit for this pin
    uint16_t GPIO229:1;                 // 5 Configuration Lock bit for this pin
    uint16_t GPIO230:1;                 // 6 Configuration Lock bit for this pin
    uint16_t GPIO231:1;                 // 7 Configuration Lock bit for this pin
    uint16_t GPIO232:1;                 // 8 Configuration Lock bit for this pin
    uint16_t GPIO233:1;                 // 9 Configuration Lock bit for this pin
    uint16_t GPIO234:1;                 // 10 Configuration Lock bit for this pin
    uint16_t GPIO235:1;                 // 11 Configuration Lock bit for this pin
    uint16_t GPIO236:1;                 // 12 Configuration Lock bit for this pin
    uint16_t GPIO237:1;                 // 13 Configuration Lock bit for this pin
    uint16_t GPIO238:1;                 // 14 Configuration Lock bit for this pin
    uint16_t GPIO239:1;                 // 15 Configuration Lock bit for this pin
    uint16_t GPIO240:1;                 // 16 Configuration Lock bit for this pin
    uint16_t GPIO241:1;                 // 17 Configuration Lock bit for this pin
    uint16_t GPIO242:1;                 // 18 Configuration Lock bit for this pin
    uint16_t GPIO243:1;                 // 19 Configuration Lock bit for this pin
    uint16_t GPIO244:1;                 // 20 Configuration Lock bit for this pin
    uint16_t GPIO245:1;                 // 21 Configuration Lock bit for this pin
    uint16_t GPIO246:1;                 // 22 Configuration Lock bit for this pin
    uint16_t GPIO247:1;                 // 23 Configuration Lock bit for this pin
    uint16_t GPIO248:1;                 // 24 Configuration Lock bit for this pin
    uint16_t GPIO249:1;                 // 25 Configuration Lock bit for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHLOCK_REG {
    uint32_t  all;
    struct  GPIO_GPHLOCK_BITS  bit;
};

struct GPIO_GPHCR_BITS {                // bits description
    uint16_t GPIO224:1;                 // 0 Configuration lock commit bit for this pin
    uint16_t GPIO225:1;                 // 1 Configuration lock commit bit for this pin
    uint16_t GPIO226:1;                 // 2 Configuration lock commit bit for this pin
    uint16_t GPIO227:1;                 // 3 Configuration lock commit bit for this pin
    uint16_t GPIO228:1;                 // 4 Configuration lock commit bit for this pin
    uint16_t GPIO229:1;                 // 5 Configuration lock commit bit for this pin
    uint16_t GPIO230:1;                 // 6 Configuration lock commit bit for this pin
    uint16_t GPIO231:1;                 // 7 Configuration lock commit bit for this pin
    uint16_t GPIO232:1;                 // 8 Configuration lock commit bit for this pin
    uint16_t GPIO233:1;                 // 9 Configuration lock commit bit for this pin
    uint16_t GPIO234:1;                 // 10 Configuration lock commit bit for this pin
    uint16_t GPIO235:1;                 // 11 Configuration lock commit bit for this pin
    uint16_t GPIO236:1;                 // 12 Configuration lock commit bit for this pin
    uint16_t GPIO237:1;                 // 13 Configuration lock commit bit for this pin
    uint16_t GPIO238:1;                 // 14 Configuration lock commit bit for this pin
    uint16_t GPIO239:1;                 // 15 Configuration lock commit bit for this pin
    uint16_t GPIO240:1;                 // 16 Configuration lock commit bit for this pin
    uint16_t GPIO241:1;                 // 17 Configuration lock commit bit for this pin
    uint16_t GPIO242:1;                 // 18 Configuration lock commit bit for this pin
    uint16_t GPIO243:1;                 // 19 Configuration lock commit bit for this pin
    uint16_t GPIO244:1;                 // 20 Configuration lock commit bit for this pin
    uint16_t GPIO245:1;                 // 21 Configuration lock commit bit for this pin
    uint16_t GPIO246:1;                 // 22 Configuration lock commit bit for this pin
    uint16_t GPIO247:1;                 // 23 Configuration lock commit bit for this pin
    uint16_t GPIO248:1;                 // 24 Configuration lock commit bit for this pin
    uint16_t GPIO249:1;                 // 25 Configuration lock commit bit for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHCR_REG {
    uint32_t  all;
    struct  GPIO_GPHCR_BITS  bit;
};

struct GPIO_CTRL_REGS {
    union   GPIO_GPACTRL_REG                 GPACTRL;                      // GPIO A Qualification Sampling Period Control (GPIO0 to 31)
    union   GPIO_GPAQSEL1_REG                GPAQSEL1;                     // GPIO A Qualifier Select 1 Register (GPIO0 to 15)
    union   GPIO_GPAQSEL2_REG                GPAQSEL2;                     // GPIO A Qualifier Select 2 Register (GPIO16 to 31)
    union   GPIO_GPAMUX1_REG                 GPAMUX1;                      // GPIO A Mux 1 Register (GPIO0 to 15)
    union   GPIO_GPAMUX2_REG                 GPAMUX2;                      // GPIO A Mux 2 Register (GPIO16 to 31)
    uint8_t                                  rsvd1[4];                     // Reserved
    union   GPIO_GPAPUD_REG                  GPAPUD;                       // GPIO A Pull Up Disable Register (GPIO0 to 31)
    uint8_t                                  rsvd2[4];                     // Reserved
    union   GPIO_GPAINV_REG                  GPAINV;                       // GPIO A Input Polarity Invert Registers (GPIO0 to 31)
    union   GPIO_GPAODR_REG                  GPAODR;                       // GPIO A Open Drain Output Register (GPIO0 to GPIO31)
    uint8_t                                  rsvd3[24];                    // Reserved
    union   GPIO_GPAGMUX1_REG                GPAGMUX1;                     // GPIO A Peripheral Group Mux (GPIO0 to 15)
    union   GPIO_GPAGMUX2_REG                GPAGMUX2;                     // GPIO A Peripheral Group Mux (GPIO16 to 31)
    uint8_t                                  rsvd4[8];                     // Reserved
    union   GPIO_GPACSEL1_REG                GPACSEL1;                     // GPIO A Core Select Register (GPIO0 to 7)
    union   GPIO_GPACSEL2_REG                GPACSEL2;                     // GPIO A Core Select Register (GPIO8 to 15)
    union   GPIO_GPACSEL3_REG                GPACSEL3;                     // GPIO A Core Select Register (GPIO16 to 23)
    union   GPIO_GPACSEL4_REG                GPACSEL4;                     // GPIO A Core Select Register (GPIO24 to 31)
    uint8_t                                  rsvd5[24];                    // Reserved
    union   GPIO_GPALOCK_REG                 GPALOCK;                      // GPIO A Lock Configuration Register (GPIO0 to 31)
    union   GPIO_GPACR_REG                   GPACR;                        // GPIO A Lock Commit Register (GPIO0 to 31)
    union   GPIO_GPBCTRL_REG                 GPBCTRL;                      // GPIO B Qualification Sampling Period Control (GPIO32 to 63)
    union   GPIO_GPBQSEL1_REG                GPBQSEL1;                     // GPIO B Qualifier Select 1 Register (GPIO32 to 47)
    union   GPIO_GPBQSEL2_REG                GPBQSEL2;                     // GPIO B Qualifier Select 2 Register (GPIO48 to 63)
    union   GPIO_GPBMUX1_REG                 GPBMUX1;                      // GPIO B Mux 1 Register (GPIO32 to 47)
    union   GPIO_GPBMUX2_REG                 GPBMUX2;                      // GPIO B Mux 2 Register (GPIO48 to 63)
    uint8_t                                  rsvd6[4];                     // Reserved
    union   GPIO_GPBPUD_REG                  GPBPUD;                       // GPIO B Pull Up Disable Register (GPIO32 to 63)
    uint8_t                                  rsvd7[4];                     // Reserved
    union   GPIO_GPBINV_REG                  GPBINV;                       // GPIO B Input Polarity Invert Registers (GPIO32 to 63)
    union   GPIO_GPBODR_REG                  GPBODR;                       // GPIO B Open Drain Output Register (GPIO32 to GPIO63)
    uint8_t                                  rsvd8[24];                    // Reserved
    union   GPIO_GPBGMUX1_REG                GPBGMUX1;                     // GPIO B Peripheral Group Mux (GPIO32 to 47)
    union   GPIO_GPBGMUX2_REG                GPBGMUX2;                     // GPIO B Peripheral Group Mux (GPIO48 to 63)
    uint8_t                                  rsvd9[8];                     // Reserved
    union   GPIO_GPBCSEL1_REG                GPBCSEL1;                     // GPIO B Core Select Register (GPIO32 to 39)
    union   GPIO_GPBCSEL2_REG                GPBCSEL2;                     // GPIO B Core Select Register (GPIO40 to 47)
    union   GPIO_GPBCSEL3_REG                GPBCSEL3;                     // GPIO B Core Select Register (GPIO48 to 55)
    union   GPIO_GPBCSEL4_REG                GPBCSEL4;                     // GPIO B Core Select Register (GPIO56 to 63)
    uint8_t                                  rsvd10[24];                   // Reserved
    union   GPIO_GPBLOCK_REG                 GPBLOCK;                      // GPIO B Lock Configuration Register (GPIO32 to 63)
    union   GPIO_GPBCR_REG                   GPBCR;                        // GPIO B Lock Commit Register (GPIO32 to 63)
    union   GPIO_GPCCTRL_REG                 GPCCTRL;                      // GPIO C Qualification Sampling Period Control (GPIO64 to 95)
    union   GPIO_GPCQSEL1_REG                GPCQSEL1;                     // GPIO C Qualifier Select 1 Register (GPIO64 to 79)
    union   GPIO_GPCQSEL2_REG                GPCQSEL2;                     // GPIO C Qualifier Select 2 Register (GPIO80  to 95)
    union   GPIO_GPCMUX1_REG                 GPCMUX1;                      // GPIO C Mux 1 Register (GPIO64 to 79)
    union   GPIO_GPCMUX2_REG                 GPCMUX2;                      // GPIO C Mux 2 Register (GPIO80  to 95)
    uint8_t                                  rsvd11[4];                    // Reserved
    union   GPIO_GPCPUD_REG                  GPCPUD;                       // GPIO C Pull Up Disable Register (GPIO64 to 95)
    uint8_t                                  rsvd12[4];                    // Reserved
    union   GPIO_GPCINV_REG                  GPCINV;                       // GPIO C Input Polarity Invert Registers (GPIO64 to 95)
    union   GPIO_GPCODR_REG                  GPCODR;                       // GPIO C Open Drain Output Register (GPIO64 to GPIO95)
    uint8_t                                  rsvd13[24];                   // Reserved
    union   GPIO_GPCGMUX1_REG                GPCGMUX1;                     // GPIO C Peripheral Group Mux (GPIO64 to 79)
    union   GPIO_GPCGMUX2_REG                GPCGMUX2;                     // GPIO C Peripheral Group Mux (GPIO80  to 95)
    uint8_t                                  rsvd14[8];                    // Reserved
    union   GPIO_GPCCSEL1_REG                GPCCSEL1;                     // GPIO C Core Select Register (GPIO64 to 71)
    union   GPIO_GPCCSEL2_REG                GPCCSEL2;                     // GPIO C Core Select Register (GPIO72 to 79)
    union   GPIO_GPCCSEL3_REG                GPCCSEL3;                     // GPIO C Core Select Register (GPIO80  to 87)
    union   GPIO_GPCCSEL4_REG                GPCCSEL4;                     // GPIO C Core Select Register (GPIO88 to 95)
    uint8_t                                  rsvd15[24];                   // Reserved
    union   GPIO_GPCLOCK_REG                 GPCLOCK;                      // GPIO C Lock Configuration Register (GPIO64 to 95)
    union   GPIO_GPCCR_REG                   GPCCR;                        // GPIO C Lock Commit Register (GPIO64 to 95)
    union   GPIO_GPDCTRL_REG                 GPDCTRL;                      // GPIO D Qualification Sampling Period Control (GPIO96 to 127)
    union   GPIO_GPDQSEL1_REG                GPDQSEL1;                     // GPIO D Qualifier Select 1 Register (GPIO96 to 111)
    union   GPIO_GPDQSEL2_REG                GPDQSEL2;                     // GPIO D Qualifier Select 2 Register (GPIO112 to 127)
    union   GPIO_GPDMUX1_REG                 GPDMUX1;                      // GPIO D Mux 1 Register (GPIO96 to 111)
    union   GPIO_GPDMUX2_REG                 GPDMUX2;                      // GPIO D Mux 2 Register (GPIO112 to 127)
    uint8_t                                  rsvd16[4];                    // Reserved
    union   GPIO_GPDPUD_REG                  GPDPUD;                       // GPIO D Pull Up Disable Register (GPIO96 to 127)
    uint8_t                                  rsvd17[4];                    // Reserved
    union   GPIO_GPDINV_REG                  GPDINV;                       // GPIO D Input Polarity Invert Registers (GPIO96 to 127)
    union   GPIO_GPDODR_REG                  GPDODR;                       // GPIO D Open Drain Output Register (GPIO96 to GPIO127)
    uint8_t                                  rsvd18[24];                   // Reserved
    union   GPIO_GPDGMUX1_REG                GPDGMUX1;                     // GPIO D Peripheral Group Mux (GPIO96 to 111)
    union   GPIO_GPDGMUX2_REG                GPDGMUX2;                     // GPIO D Peripheral Group Mux (GPIO112 to 127)
    uint8_t                                  rsvd19[8];                    // Reserved
    union   GPIO_GPDCSEL1_REG                GPDCSEL1;                     // GPIO D Core Select Register (GPIO96 to 103)
    union   GPIO_GPDCSEL2_REG                GPDCSEL2;                     // GPIO D Core Select Register (GPIO104 to 111)
    uint8_t                                  rsvd20[4];                    // Reserved
    union   GPIO_GPDCSEL4_REG                GPDCSEL4;                     // GPIO D Core Select Register (GPIO120 to 127)
    uint8_t                                  rsvd21[24];                   // Reserved
    union   GPIO_GPDLOCK_REG                 GPDLOCK;                      // GPIO D Lock Configuration Register (GPIO96 to 127)
    union   GPIO_GPDCR_REG                   GPDCR;                        // GPIO D Lock Commit Register (GPIO96 to 127)
    uint8_t                                  rsvd22[128];                  // Reserved
    union   GPIO_GPFCTRL_REG                 GPFCTRL;                      // GPIO F Qualification Sampling Period Control (GPIO160 to 191)
    union   GPIO_GPFQSEL1_REG                GPFQSEL1;                     // GPIO F Qualifier Select 1 Register (GPIO160 to 168)
    union   GPIO_GPFQSEL2_REG                GPFQSEL2;                     // GPIO F Qualifier Select 2 Register (GPIO176 to 191)
    union   GPIO_GPFMUX1_REG                 GPFMUX1;                      // GPIO F Mux 1 Register (GPIO160 to 175)
    union   GPIO_GPFMUX2_REG                 GPFMUX2;                      // GPIO F Mux 2 Register (GPIO176 to 191)
    uint8_t                                  rsvd23[4];                    // Reserved
    union   GPIO_GPFPUD_REG                  GPFPUD;                       // GPIO F Pull Up Disable Register (GPIO160 to 191)
    uint8_t                                  rsvd24[4];                    // Reserved
    union   GPIO_GPFINV_REG                  GPFINV;                       // GPIO F Input Polarity Invert Registers (GPIO160 to 191)
    uint8_t                                  rsvd25[4];                    // Reserved
    union   GPIO_GPFAMSEL_REG                GPFAMSEL;                     // GPIO F Analog Mode Select register (GPIO160 to GPIO191)
    uint8_t                                  rsvd26[20];                   // Reserved
    union   GPIO_GPFGMUX1_REG                GPFGMUX1;                     // GPIO F Peripheral Group Mux (GPIO160 to 175)
    union   GPIO_GPFGMUX2_REG                GPFGMUX2;                     // GPIO F Peripheral Group Mux (GPIO176 to 191)
    uint8_t                                  rsvd27[8];                    // Reserved
    union   GPIO_GPFCSEL1_REG                GPFCSEL1;                     // GPIO F Core Select Register (GPIO160 to 167)
    union   GPIO_GPFCSEL2_REG                GPFCSEL2;                     // GPIO F Core Select Register (GPIO168 to 175)
    union   GPIO_GPFCSEL3_REG                GPFCSEL3;                     // GPIO F Core Select Register (GPIO176 to 183)
    union   GPIO_GPFCSEL4_REG                GPFCSEL4;                     // GPIO F Core Select Register (GPIO184 to 191)
    uint8_t                                  rsvd28[24];                   // Reserved
    union   GPIO_GPFLOCK_REG                 GPFLOCK;                      // GPIO F Lock Configuration Register (GPIO160 to 191)
    union   GPIO_GPFCR_REG                   GPFCR;                        // GPIO F Lock Commit Register (GPIO160 to 191)
    union   GPIO_GPGCTRL_REG                 GPGCTRL;                      // GPIO G Qualification Sampling Period Control (GPIO192 to 223)
    union   GPIO_GPGQSEL1_REG                GPGQSEL1;                     // GPIO G Qualifier Select 1 Register (GPIO192 to 207)
    union   GPIO_GPGQSEL2_REG                GPGQSEL2;                     // GPIO G Qualifier Select 2 Register (GPIO208 to 223)
    union   GPIO_GPGMUX1_REG                 GPGMUX1;                      // GPIO G Mux 1 Register (GPIO192 to 207)
    union   GPIO_GPGMUX2_REG                 GPGMUX2;                      // GPIO G Mux 2 Register (GPIO208 to 223)
    uint8_t                                  rsvd29[4];                    // Reserved
    union   GPIO_GPGPUD_REG                  GPGPUD;                       // GPIO G Pull Up Disable Register (GPIO192 to 223)
    uint8_t                                  rsvd30[4];                    // Reserved
    union   GPIO_GPGINV_REG                  GPGINV;                       // GPIO G Input Polarity Invert Registers (GPIO192 to 223)
    union   GPIO_GPGODR_REG                  GPGODR;                       // GPIO G Open Drain Output Register (GPIO192 to 223)
    union   GPIO_GPGAMSEL_REG                GPGAMSEL;                     // GPIO G Analog Mode Select register (GPIO192 to 223)
    uint8_t                                  rsvd31[20];                   // Reserved
    union   GPIO_GPGGMUX1_REG                GPGGMUX1;                     // GPIO G Peripheral Group Mux (GPIO192 to 207)
    union   GPIO_GPGGMUX2_REG                GPGGMUX2;                     // GPIO G Peripheral Group Mux (GPIO208 to 223)
    uint8_t                                  rsvd32[8];                    // Reserved
    union   GPIO_GPGCSEL1_REG                GPGCSEL1;                     // GPIO G Core Select Register (GPIO192 to 199)
    union   GPIO_GPGCSEL2_REG                GPGCSEL2;                     // GPIO G Core Select Register (GPIO200 to 207)
    union   GPIO_GPGCSEL3_REG                GPGCSEL3;                     // GPIO G Core Select Register (GPIO208 to 215)
    union   GPIO_GPGCSEL4_REG                GPGCSEL4;                     // GPIO G Core Select Register (GPIO216 to 223)
    uint8_t                                  rsvd33[24];                   // Reserved
    union   GPIO_GPGLOCK_REG                 GPGLOCK;                      // GPIO G Lock Configuration Register (GPIO192 to 223)
    union   GPIO_GPGCR_REG                   GPGCR;                        // GPIO G Lock Commit Register (GPIO192 to 223)
    union   GPIO_GPHCTRL_REG                 GPHCTRL;                      // GPIO H Qualification Sampling Period Control (GPIO224 to 255)
    union   GPIO_GPHQSEL1_REG                GPHQSEL1;                     // GPIO H Qualifier Select 1 Register (GPIO224 to 239)
    union   GPIO_GPHQSEL2_REG                GPHQSEL2;                     // GPIO H Qualifier Select 2 Register (GPIO240 to 255)
    union   GPIO_GPHMUX1_REG                 GPHMUX1;                      // GPIO H Mux 1 Register (GPIO224 to 239)
    union   GPIO_GPHMUX2_REG                 GPHMUX2;                      // GPIO H Mux 2 Register (GPIO240 to 255)
    uint8_t                                  rsvd34[4];                    // Reserved
    union   GPIO_GPHPUD_REG                  GPHPUD;                       // GPIO H Pull Up Disable Register (GPIO224 to 255)
    uint8_t                                  rsvd35[4];                    // Reserved
    union   GPIO_GPHINV_REG                  GPHINV;                       // GPIO H Input Polarity Invert Registers (GPIO224 to 255)
    union   GPIO_GPHODR_REG                  GPHODR;                       // GPIO H Open Drain Output Register (GPIO224 to GPIO255)
    union   GPIO_GPHAMSEL_REG                GPHAMSEL;                     // GPIO H Analog Mode Select register (GPIO224 to GPIO255)
    uint8_t                                  rsvd36[20];                   // Reserved
    union   GPIO_GPHGMUX1_REG                GPHGMUX1;                     // GPIO H Peripheral Group Mux (GPIO224 to 239)
    union   GPIO_GPHGMUX2_REG                GPHGMUX2;                     // GPIO H Peripheral Group Mux (GPIO240 to 255)
    uint8_t                                  rsvd37[8];                    // Reserved
    union   GPIO_GPHCSEL1_REG                GPHCSEL1;                     // GPIO H Core Select Register (GPIO224 to 231)
    union   GPIO_GPHCSEL2_REG                GPHCSEL2;                     // GPIO H Core Select Register (GPIO232 to 239)
    union   GPIO_GPHCSEL3_REG                GPHCSEL3;                     // GPIO H Core Select Register (GPIO240 to 247)
    union   GPIO_GPHCSEL4_REG                GPHCSEL4;                     // GPIO H Core Select Register (GPIO248 to 255)
    uint8_t                                  rsvd38[24];                   // Reserved
    union   GPIO_GPHLOCK_REG                 GPHLOCK;                      // GPIO H Lock Configuration Register (GPIO224 to 255)
    union   GPIO_GPHCR_REG                   GPHCR;                        // GPIO H Lock Commit Register (GPIO224 to 255)
};

struct GPIO_GPADAT_BITS {               // bits description
    uint16_t GPIO0:1;                   // 0 Data Register for this pin
    uint16_t GPIO1:1;                   // 1 Data Register for this pin
    uint16_t GPIO2:1;                   // 2 Data Register for this pin
    uint16_t GPIO3:1;                   // 3 Data Register for this pin
    uint16_t GPIO4:1;                   // 4 Data Register for this pin
    uint16_t GPIO5:1;                   // 5 Data Register for this pin
    uint16_t GPIO6:1;                   // 6 Data Register for this pin
    uint16_t GPIO7:1;                   // 7 Data Register for this pin
    uint16_t GPIO8:1;                   // 8 Data Register for this pin
    uint16_t GPIO9:1;                   // 9 Data Register for this pin
    uint16_t GPIO10:1;                  // 10 Data Register for this pin
    uint16_t GPIO11:1;                  // 11 Data Register for this pin
    uint16_t GPIO12:1;                  // 12 Data Register for this pin
    uint16_t GPIO13:1;                  // 13 Data Register for this pin
    uint16_t GPIO14:1;                  // 14 Data Register for this pin
    uint16_t GPIO15:1;                  // 15 Data Register for this pin
    uint16_t GPIO16:1;                  // 16 Data Register for this pin
    uint16_t GPIO17:1;                  // 17 Data Register for this pin
    uint16_t GPIO18:1;                  // 18 Data Register for this pin
    uint16_t GPIO19:1;                  // 19 Data Register for this pin
    uint16_t GPIO20:1;                  // 20 Data Register for this pin
    uint16_t GPIO21:1;                  // 21 Data Register for this pin
    uint16_t GPIO22:1;                  // 22 Data Register for this pin
    uint16_t GPIO23:1;                  // 23 Data Register for this pin
    uint16_t GPIO24:1;                  // 24 Data Register for this pin
    uint16_t GPIO25:1;                  // 25 Data Register for this pin
    uint16_t GPIO26:1;                  // 26 Data Register for this pin
    uint16_t GPIO27:1;                  // 27 Data Register for this pin
    uint16_t GPIO28:1;                  // 28 Data Register for this pin
    uint16_t GPIO29:1;                  // 29 Data Register for this pin
    uint16_t GPIO30:1;                  // 30 Data Register for this pin
    uint16_t GPIO31:1;                  // 31 Data Register for this pin
};

union GPIO_GPADAT_REG {
    uint32_t  all;
    struct  GPIO_GPADAT_BITS  bit;
};

struct GPIO_GPASET_BITS {               // bits description
    uint16_t GPIO0:1;                   // 0 Output Set bit for this pin
    uint16_t GPIO1:1;                   // 1 Output Set bit for this pin
    uint16_t GPIO2:1;                   // 2 Output Set bit for this pin
    uint16_t GPIO3:1;                   // 3 Output Set bit for this pin
    uint16_t GPIO4:1;                   // 4 Output Set bit for this pin
    uint16_t GPIO5:1;                   // 5 Output Set bit for this pin
    uint16_t GPIO6:1;                   // 6 Output Set bit for this pin
    uint16_t GPIO7:1;                   // 7 Output Set bit for this pin
    uint16_t GPIO8:1;                   // 8 Output Set bit for this pin
    uint16_t GPIO9:1;                   // 9 Output Set bit for this pin
    uint16_t GPIO10:1;                  // 10 Output Set bit for this pin
    uint16_t GPIO11:1;                  // 11 Output Set bit for this pin
    uint16_t GPIO12:1;                  // 12 Output Set bit for this pin
    uint16_t GPIO13:1;                  // 13 Output Set bit for this pin
    uint16_t GPIO14:1;                  // 14 Output Set bit for this pin
    uint16_t GPIO15:1;                  // 15 Output Set bit for this pin
    uint16_t GPIO16:1;                  // 16 Output Set bit for this pin
    uint16_t GPIO17:1;                  // 17 Output Set bit for this pin
    uint16_t GPIO18:1;                  // 18 Output Set bit for this pin
    uint16_t GPIO19:1;                  // 19 Output Set bit for this pin
    uint16_t GPIO20:1;                  // 20 Output Set bit for this pin
    uint16_t GPIO21:1;                  // 21 Output Set bit for this pin
    uint16_t GPIO22:1;                  // 22 Output Set bit for this pin
    uint16_t GPIO23:1;                  // 23 Output Set bit for this pin
    uint16_t GPIO24:1;                  // 24 Output Set bit for this pin
    uint16_t GPIO25:1;                  // 25 Output Set bit for this pin
    uint16_t GPIO26:1;                  // 26 Output Set bit for this pin
    uint16_t GPIO27:1;                  // 27 Output Set bit for this pin
    uint16_t GPIO28:1;                  // 28 Output Set bit for this pin
    uint16_t GPIO29:1;                  // 29 Output Set bit for this pin
    uint16_t GPIO30:1;                  // 30 Output Set bit for this pin
    uint16_t GPIO31:1;                  // 31 Output Set bit for this pin
};

union GPIO_GPASET_REG {
    uint32_t  all;
    struct  GPIO_GPASET_BITS  bit;
};

struct GPIO_GPACLEAR_BITS {             // bits description
    uint16_t GPIO0:1;                   // 0 Output Clear bit for this pin
    uint16_t GPIO1:1;                   // 1 Output Clear bit for this pin
    uint16_t GPIO2:1;                   // 2 Output Clear bit for this pin
    uint16_t GPIO3:1;                   // 3 Output Clear bit for this pin
    uint16_t GPIO4:1;                   // 4 Output Clear bit for this pin
    uint16_t GPIO5:1;                   // 5 Output Clear bit for this pin
    uint16_t GPIO6:1;                   // 6 Output Clear bit for this pin
    uint16_t GPIO7:1;                   // 7 Output Clear bit for this pin
    uint16_t GPIO8:1;                   // 8 Output Clear bit for this pin
    uint16_t GPIO9:1;                   // 9 Output Clear bit for this pin
    uint16_t GPIO10:1;                  // 10 Output Clear bit for this pin
    uint16_t GPIO11:1;                  // 11 Output Clear bit for this pin
    uint16_t GPIO12:1;                  // 12 Output Clear bit for this pin
    uint16_t GPIO13:1;                  // 13 Output Clear bit for this pin
    uint16_t GPIO14:1;                  // 14 Output Clear bit for this pin
    uint16_t GPIO15:1;                  // 15 Output Clear bit for this pin
    uint16_t GPIO16:1;                  // 16 Output Clear bit for this pin
    uint16_t GPIO17:1;                  // 17 Output Clear bit for this pin
    uint16_t GPIO18:1;                  // 18 Output Clear bit for this pin
    uint16_t GPIO19:1;                  // 19 Output Clear bit for this pin
    uint16_t GPIO20:1;                  // 20 Output Clear bit for this pin
    uint16_t GPIO21:1;                  // 21 Output Clear bit for this pin
    uint16_t GPIO22:1;                  // 22 Output Clear bit for this pin
    uint16_t GPIO23:1;                  // 23 Output Clear bit for this pin
    uint16_t GPIO24:1;                  // 24 Output Clear bit for this pin
    uint16_t GPIO25:1;                  // 25 Output Clear bit for this pin
    uint16_t GPIO26:1;                  // 26 Output Clear bit for this pin
    uint16_t GPIO27:1;                  // 27 Output Clear bit for this pin
    uint16_t GPIO28:1;                  // 28 Output Clear bit for this pin
    uint16_t GPIO29:1;                  // 29 Output Clear bit for this pin
    uint16_t GPIO30:1;                  // 30 Output Clear bit for this pin
    uint16_t GPIO31:1;                  // 31 Output Clear bit for this pin
};

union GPIO_GPACLEAR_REG {
    uint32_t  all;
    struct  GPIO_GPACLEAR_BITS  bit;
};

struct GPIO_GPATOGGLE_BITS {            // bits description
    uint16_t GPIO0:1;                   // 0 Output Toggle bit for this pin
    uint16_t GPIO1:1;                   // 1 Output Toggle bit for this pin
    uint16_t GPIO2:1;                   // 2 Output Toggle bit for this pin
    uint16_t GPIO3:1;                   // 3 Output Toggle bit for this pin
    uint16_t GPIO4:1;                   // 4 Output Toggle bit for this pin
    uint16_t GPIO5:1;                   // 5 Output Toggle bit for this pin
    uint16_t GPIO6:1;                   // 6 Output Toggle bit for this pin
    uint16_t GPIO7:1;                   // 7 Output Toggle bit for this pin
    uint16_t GPIO8:1;                   // 8 Output Toggle bit for this pin
    uint16_t GPIO9:1;                   // 9 Output Toggle bit for this pin
    uint16_t GPIO10:1;                  // 10 Output Toggle bit for this pin
    uint16_t GPIO11:1;                  // 11 Output Toggle bit for this pin
    uint16_t GPIO12:1;                  // 12 Output Toggle bit for this pin
    uint16_t GPIO13:1;                  // 13 Output Toggle bit for this pin
    uint16_t GPIO14:1;                  // 14 Output Toggle bit for this pin
    uint16_t GPIO15:1;                  // 15 Output Toggle bit for this pin
    uint16_t GPIO16:1;                  // 16 Output Toggle bit for this pin
    uint16_t GPIO17:1;                  // 17 Output Toggle bit for this pin
    uint16_t GPIO18:1;                  // 18 Output Toggle bit for this pin
    uint16_t GPIO19:1;                  // 19 Output Toggle bit for this pin
    uint16_t GPIO20:1;                  // 20 Output Toggle bit for this pin
    uint16_t GPIO21:1;                  // 21 Output Toggle bit for this pin
    uint16_t GPIO22:1;                  // 22 Output Toggle bit for this pin
    uint16_t GPIO23:1;                  // 23 Output Toggle bit for this pin
    uint16_t GPIO24:1;                  // 24 Output Toggle bit for this pin
    uint16_t GPIO25:1;                  // 25 Output Toggle bit for this pin
    uint16_t GPIO26:1;                  // 26 Output Toggle bit for this pin
    uint16_t GPIO27:1;                  // 27 Output Toggle bit for this pin
    uint16_t GPIO28:1;                  // 28 Output Toggle bit for this pin
    uint16_t GPIO29:1;                  // 29 Output Toggle bit for this pin
    uint16_t GPIO30:1;                  // 30 Output Toggle bit for this pin
    uint16_t GPIO31:1;                  // 31 Output Toggle bit for this pin
};

union GPIO_GPATOGGLE_REG {
    uint32_t  all;
    struct  GPIO_GPATOGGLE_BITS  bit;
};

struct GPIO_GPADIR_BITS {               // bits description
    uint16_t GPIO0:1;                   // 0 Defines direction for this pin in GPIO mode
    uint16_t GPIO1:1;                   // 1 Defines direction for this pin in GPIO mode
    uint16_t GPIO2:1;                   // 2 Defines direction for this pin in GPIO mode
    uint16_t GPIO3:1;                   // 3 Defines direction for this pin in GPIO mode
    uint16_t GPIO4:1;                   // 4 Defines direction for this pin in GPIO mode
    uint16_t GPIO5:1;                   // 5 Defines direction for this pin in GPIO mode
    uint16_t GPIO6:1;                   // 6 Defines direction for this pin in GPIO mode
    uint16_t GPIO7:1;                   // 7 Defines direction for this pin in GPIO mode
    uint16_t GPIO8:1;                   // 8 Defines direction for this pin in GPIO mode
    uint16_t GPIO9:1;                   // 9 Defines direction for this pin in GPIO mode
    uint16_t GPIO10:1;                  // 10 Defines direction for this pin in GPIO mode
    uint16_t GPIO11:1;                  // 11 Defines direction for this pin in GPIO mode
    uint16_t GPIO12:1;                  // 12 Defines direction for this pin in GPIO mode
    uint16_t GPIO13:1;                  // 13 Defines direction for this pin in GPIO mode
    uint16_t GPIO14:1;                  // 14 Defines direction for this pin in GPIO mode
    uint16_t GPIO15:1;                  // 15 Defines direction for this pin in GPIO mode
    uint16_t GPIO16:1;                  // 16 Defines direction for this pin in GPIO mode
    uint16_t GPIO17:1;                  // 17 Defines direction for this pin in GPIO mode
    uint16_t GPIO18:1;                  // 18 Defines direction for this pin in GPIO mode
    uint16_t GPIO19:1;                  // 19 Defines direction for this pin in GPIO mode
    uint16_t GPIO20:1;                  // 20 Defines direction for this pin in GPIO mode
    uint16_t GPIO21:1;                  // 21 Defines direction for this pin in GPIO mode
    uint16_t GPIO22:1;                  // 22 Defines direction for this pin in GPIO mode
    uint16_t GPIO23:1;                  // 23 Defines direction for this pin in GPIO mode
    uint16_t GPIO24:1;                  // 24 Defines direction for this pin in GPIO mode
    uint16_t GPIO25:1;                  // 25 Defines direction for this pin in GPIO mode
    uint16_t GPIO26:1;                  // 26 Defines direction for this pin in GPIO mode
    uint16_t GPIO27:1;                  // 27 Defines direction for this pin in GPIO mode
    uint16_t GPIO28:1;                  // 28 Defines direction for this pin in GPIO mode
    uint16_t GPIO29:1;                  // 29 Defines direction for this pin in GPIO mode
    uint16_t GPIO30:1;                  // 30 Defines direction for this pin in GPIO mode
    uint16_t GPIO31:1;                  // 31 Defines direction for this pin in GPIO mode
};

union GPIO_GPADIR_REG {
    uint32_t  all;
    struct  GPIO_GPADIR_BITS  bit;
};

struct GPIO_GPBDAT_BITS {               // bits description
    uint16_t GPIO32:1;                  // 0 Data Register for this pin
    uint16_t GPIO33:1;                  // 1 Data Register for this pin
    uint16_t GPIO34:1;                  // 2 Data Register for this pin
    uint16_t GPIO35:1;                  // 3 Data Register for this pin
    uint16_t GPIO36:1;                  // 4 Data Register for this pin
    uint16_t GPIO37:1;                  // 5 Data Register for this pin
    uint16_t GPIO38:1;                  // 6 Data Register for this pin
    uint16_t GPIO39:1;                  // 7 Data Register for this pin
    uint16_t GPIO40:1;                  // 8 Data Register for this pin
    uint16_t GPIO41:1;                  // 9 Data Register for this pin
    uint16_t GPIO42:1;                  // 10 Data Register for this pin
    uint16_t GPIO43:1;                  // 11 Data Register for this pin
    uint16_t GPIO44:1;                  // 12 Data Register for this pin
    uint16_t GPIO45:1;                  // 13 Data Register for this pin
    uint16_t GPIO46:1;                  // 14 Data Register for this pin
    uint16_t GPIO47:1;                  // 15 Data Register for this pin
    uint16_t GPIO48:1;                  // 16 Data Register for this pin
    uint16_t GPIO49:1;                  // 17 Data Register for this pin
    uint16_t GPIO50:1;                  // 18 Data Register for this pin
    uint16_t GPIO51:1;                  // 19 Data Register for this pin
    uint16_t GPIO52:1;                  // 20 Data Register for this pin
    uint16_t GPIO53:1;                  // 21 Data Register for this pin
    uint16_t GPIO54:1;                  // 22 Data Register for this pin
    uint16_t GPIO55:1;                  // 23 Data Register for this pin
    uint16_t GPIO56:1;                  // 24 Data Register for this pin
    uint16_t GPIO57:1;                  // 25 Data Register for this pin
    uint16_t GPIO58:1;                  // 26 Data Register for this pin
    uint16_t GPIO59:1;                  // 27 Data Register for this pin
    uint16_t GPIO60:1;                  // 28 Data Register for this pin
    uint16_t GPIO61:1;                  // 29 Data Register for this pin
    uint16_t GPIO62:1;                  // 30 Data Register for this pin
    uint16_t GPIO63:1;                  // 31 Data Register for this pin
};

union GPIO_GPBDAT_REG {
    uint32_t  all;
    struct  GPIO_GPBDAT_BITS  bit;
};

struct GPIO_GPBSET_BITS {               // bits description
    uint16_t GPIO32:1;                  // 0 Output Set bit for this pin
    uint16_t GPIO33:1;                  // 1 Output Set bit for this pin
    uint16_t GPIO34:1;                  // 2 Output Set bit for this pin
    uint16_t GPIO35:1;                  // 3 Output Set bit for this pin
    uint16_t GPIO36:1;                  // 4 Output Set bit for this pin
    uint16_t GPIO37:1;                  // 5 Output Set bit for this pin
    uint16_t GPIO38:1;                  // 6 Output Set bit for this pin
    uint16_t GPIO39:1;                  // 7 Output Set bit for this pin
    uint16_t GPIO40:1;                  // 8 Output Set bit for this pin
    uint16_t GPIO41:1;                  // 9 Output Set bit for this pin
    uint16_t GPIO42:1;                  // 10 Output Set bit for this pin
    uint16_t GPIO43:1;                  // 11 Output Set bit for this pin
    uint16_t GPIO44:1;                  // 12 Output Set bit for this pin
    uint16_t GPIO45:1;                  // 13 Output Set bit for this pin
    uint16_t GPIO46:1;                  // 14 Output Set bit for this pin
    uint16_t GPIO47:1;                  // 15 Output Set bit for this pin
    uint16_t GPIO48:1;                  // 16 Output Set bit for this pin
    uint16_t GPIO49:1;                  // 17 Output Set bit for this pin
    uint16_t GPIO50:1;                  // 18 Output Set bit for this pin
    uint16_t GPIO51:1;                  // 19 Output Set bit for this pin
    uint16_t GPIO52:1;                  // 20 Output Set bit for this pin
    uint16_t GPIO53:1;                  // 21 Output Set bit for this pin
    uint16_t GPIO54:1;                  // 22 Output Set bit for this pin
    uint16_t GPIO55:1;                  // 23 Output Set bit for this pin
    uint16_t GPIO56:1;                  // 24 Output Set bit for this pin
    uint16_t GPIO57:1;                  // 25 Output Set bit for this pin
    uint16_t GPIO58:1;                  // 26 Output Set bit for this pin
    uint16_t GPIO59:1;                  // 27 Output Set bit for this pin
    uint16_t GPIO60:1;                  // 28 Output Set bit for this pin
    uint16_t GPIO61:1;                  // 29 Output Set bit for this pin
    uint16_t GPIO62:1;                  // 30 Output Set bit for this pin
    uint16_t GPIO63:1;                  // 31 Output Set bit for this pin
};

union GPIO_GPBSET_REG {
    uint32_t  all;
    struct  GPIO_GPBSET_BITS  bit;
};

struct GPIO_GPBCLEAR_BITS {             // bits description
    uint16_t GPIO32:1;                  // 0 Output Clear bit for this pin
    uint16_t GPIO33:1;                  // 1 Output Clear bit for this pin
    uint16_t GPIO34:1;                  // 2 Output Clear bit for this pin
    uint16_t GPIO35:1;                  // 3 Output Clear bit for this pin
    uint16_t GPIO36:1;                  // 4 Output Clear bit for this pin
    uint16_t GPIO37:1;                  // 5 Output Clear bit for this pin
    uint16_t GPIO38:1;                  // 6 Output Clear bit for this pin
    uint16_t GPIO39:1;                  // 7 Output Clear bit for this pin
    uint16_t GPIO40:1;                  // 8 Output Clear bit for this pin
    uint16_t GPIO41:1;                  // 9 Output Clear bit for this pin
    uint16_t GPIO42:1;                  // 10 Output Clear bit for this pin
    uint16_t GPIO43:1;                  // 11 Output Clear bit for this pin
    uint16_t GPIO44:1;                  // 12 Output Clear bit for this pin
    uint16_t GPIO45:1;                  // 13 Output Clear bit for this pin
    uint16_t GPIO46:1;                  // 14 Output Clear bit for this pin
    uint16_t GPIO47:1;                  // 15 Output Clear bit for this pin
    uint16_t GPIO48:1;                  // 16 Output Clear bit for this pin
    uint16_t GPIO49:1;                  // 17 Output Clear bit for this pin
    uint16_t GPIO50:1;                  // 18 Output Clear bit for this pin
    uint16_t GPIO51:1;                  // 19 Output Clear bit for this pin
    uint16_t GPIO52:1;                  // 20 Output Clear bit for this pin
    uint16_t GPIO53:1;                  // 21 Output Clear bit for this pin
    uint16_t GPIO54:1;                  // 22 Output Clear bit for this pin
    uint16_t GPIO55:1;                  // 23 Output Clear bit for this pin
    uint16_t GPIO56:1;                  // 24 Output Clear bit for this pin
    uint16_t GPIO57:1;                  // 25 Output Clear bit for this pin
    uint16_t GPIO58:1;                  // 26 Output Clear bit for this pin
    uint16_t GPIO59:1;                  // 27 Output Clear bit for this pin
    uint16_t GPIO60:1;                  // 28 Output Clear bit for this pin
    uint16_t GPIO61:1;                  // 29 Output Clear bit for this pin
    uint16_t GPIO62:1;                  // 30 Output Clear bit for this pin
    uint16_t GPIO63:1;                  // 31 Output Clear bit for this pin
};

union GPIO_GPBCLEAR_REG {
    uint32_t  all;
    struct  GPIO_GPBCLEAR_BITS  bit;
};

struct GPIO_GPBTOGGLE_BITS {            // bits description
    uint16_t GPIO32:1;                  // 0 Output Toggle bit for this pin
    uint16_t GPIO33:1;                  // 1 Output Toggle bit for this pin
    uint16_t GPIO34:1;                  // 2 Output Toggle bit for this pin
    uint16_t GPIO35:1;                  // 3 Output Toggle bit for this pin
    uint16_t GPIO36:1;                  // 4 Output Toggle bit for this pin
    uint16_t GPIO37:1;                  // 5 Output Toggle bit for this pin
    uint16_t GPIO38:1;                  // 6 Output Toggle bit for this pin
    uint16_t GPIO39:1;                  // 7 Output Toggle bit for this pin
    uint16_t GPIO40:1;                  // 8 Output Toggle bit for this pin
    uint16_t GPIO41:1;                  // 9 Output Toggle bit for this pin
    uint16_t GPIO42:1;                  // 10 Output Toggle bit for this pin
    uint16_t GPIO43:1;                  // 11 Output Toggle bit for this pin
    uint16_t GPIO44:1;                  // 12 Output Toggle bit for this pin
    uint16_t GPIO45:1;                  // 13 Output Toggle bit for this pin
    uint16_t GPIO46:1;                  // 14 Output Toggle bit for this pin
    uint16_t GPIO47:1;                  // 15 Output Toggle bit for this pin
    uint16_t GPIO48:1;                  // 16 Output Toggle bit for this pin
    uint16_t GPIO49:1;                  // 17 Output Toggle bit for this pin
    uint16_t GPIO50:1;                  // 18 Output Toggle bit for this pin
    uint16_t GPIO51:1;                  // 19 Output Toggle bit for this pin
    uint16_t GPIO52:1;                  // 20 Output Toggle bit for this pin
    uint16_t GPIO53:1;                  // 21 Output Toggle bit for this pin
    uint16_t GPIO54:1;                  // 22 Output Toggle bit for this pin
    uint16_t GPIO55:1;                  // 23 Output Toggle bit for this pin
    uint16_t GPIO56:1;                  // 24 Output Toggle bit for this pin
    uint16_t GPIO57:1;                  // 25 Output Toggle bit for this pin
    uint16_t GPIO58:1;                  // 26 Output Toggle bit for this pin
    uint16_t GPIO59:1;                  // 27 Output Toggle bit for this pin
    uint16_t GPIO60:1;                  // 28 Output Toggle bit for this pin
    uint16_t GPIO61:1;                  // 29 Output Toggle bit for this pin
    uint16_t GPIO62:1;                  // 30 Output Toggle bit for this pin
    uint16_t GPIO63:1;                  // 31 Output Toggle bit for this pin
};

union GPIO_GPBTOGGLE_REG {
    uint32_t  all;
    struct  GPIO_GPBTOGGLE_BITS  bit;
};

struct GPIO_GPBDIR_BITS {               // bits description
    uint16_t GPIO32:1;                  // 0 Defines direction for this pin in GPIO mode
    uint16_t GPIO33:1;                  // 1 Defines direction for this pin in GPIO mode
    uint16_t GPIO34:1;                  // 2 Defines direction for this pin in GPIO mode
    uint16_t GPIO35:1;                  // 3 Defines direction for this pin in GPIO mode
    uint16_t GPIO36:1;                  // 4 Defines direction for this pin in GPIO mode
    uint16_t GPIO37:1;                  // 5 Defines direction for this pin in GPIO mode
    uint16_t GPIO38:1;                  // 6 Defines direction for this pin in GPIO mode
    uint16_t GPIO39:1;                  // 7 Defines direction for this pin in GPIO mode
    uint16_t GPIO40:1;                  // 8 Defines direction for this pin in GPIO mode
    uint16_t GPIO41:1;                  // 9 Defines direction for this pin in GPIO mode
    uint16_t GPIO42:1;                  // 10 Defines direction for this pin in GPIO mode
    uint16_t GPIO43:1;                  // 11 Defines direction for this pin in GPIO mode
    uint16_t GPIO44:1;                  // 12 Defines direction for this pin in GPIO mode
    uint16_t GPIO45:1;                  // 13 Defines direction for this pin in GPIO mode
    uint16_t GPIO46:1;                  // 14 Defines direction for this pin in GPIO mode
    uint16_t GPIO47:1;                  // 15 Defines direction for this pin in GPIO mode
    uint16_t GPIO48:1;                  // 16 Defines direction for this pin in GPIO mode
    uint16_t GPIO49:1;                  // 17 Defines direction for this pin in GPIO mode
    uint16_t GPIO50:1;                  // 18 Defines direction for this pin in GPIO mode
    uint16_t GPIO51:1;                  // 19 Defines direction for this pin in GPIO mode
    uint16_t GPIO52:1;                  // 20 Defines direction for this pin in GPIO mode
    uint16_t GPIO53:1;                  // 21 Defines direction for this pin in GPIO mode
    uint16_t GPIO54:1;                  // 22 Defines direction for this pin in GPIO mode
    uint16_t GPIO55:1;                  // 23 Defines direction for this pin in GPIO mode
    uint16_t GPIO56:1;                  // 24 Defines direction for this pin in GPIO mode
    uint16_t GPIO57:1;                  // 25 Defines direction for this pin in GPIO mode
    uint16_t GPIO58:1;                  // 26 Defines direction for this pin in GPIO mode
    uint16_t GPIO59:1;                  // 27 Defines direction for this pin in GPIO mode
    uint16_t GPIO60:1;                  // 28 Defines direction for this pin in GPIO mode
    uint16_t GPIO61:1;                  // 29 Defines direction for this pin in GPIO mode
    uint16_t GPIO62:1;                  // 30 Defines direction for this pin in GPIO mode
    uint16_t GPIO63:1;                  // 31 Defines direction for this pin in GPIO mode
};

union GPIO_GPBDIR_REG {
    uint32_t  all;
    struct  GPIO_GPBDIR_BITS  bit;
};

struct GPIO_GPCDAT_BITS {               // bits description
    uint16_t GPIO64:1;                  // 0 Data Register for this pin
    uint16_t GPIO65:1;                  // 1 Data Register for this pin
    uint16_t GPIO66:1;                  // 2 Data Register for this pin
    uint16_t GPIO67:1;                  // 3 Data Register for this pin
    uint16_t GPIO68:1;                  // 4 Data Register for this pin
    uint16_t GPIO69:1;                  // 5 Data Register for this pin
    uint16_t GPIO70:1;                  // 6 Data Register for this pin
    uint16_t GPIO71:1;                  // 7 Data Register for this pin
    uint16_t GPIO72:1;                  // 8 Data Register for this pin
    uint16_t GPIO73:1;                  // 9 Data Register for this pin
    uint16_t GPIO74:1;                  // 10 Data Register for this pin
    uint16_t GPIO75:1;                  // 11 Data Register for this pin
    uint16_t GPIO76:1;                  // 12 Data Register for this pin
    uint16_t GPIO77:1;                  // 13 Data Register for this pin
    uint16_t GPIO78:1;                  // 14 Data Register for this pin
    uint16_t GPIO79:1;                  // 15 Data Register for this pin
    uint16_t GPIO80:1;                  // 16 Data Register for this pin
    uint16_t GPIO81:1;                  // 17 Data Register for this pin
    uint16_t GPIO82:1;                  // 18 Data Register for this pin
    uint16_t GPIO83:1;                  // 19 Data Register for this pin
    uint16_t GPIO84:1;                  // 20 Data Register for this pin
    uint16_t GPIO85:1;                  // 21 Data Register for this pin
    uint16_t GPIO86:1;                  // 22 Data Register for this pin
    uint16_t GPIO87:1;                  // 23 Data Register for this pin
    uint16_t GPIO88:1;                  // 24 Data Register for this pin
    uint16_t GPIO89:1;                  // 25 Data Register for this pin
    uint16_t GPIO90:1;                  // 26 Data Register for this pin
    uint16_t GPIO91:1;                  // 27 Data Register for this pin
    uint16_t GPIO92:1;                  // 28 Data Register for this pin
    uint16_t GPIO93:1;                  // 29 Data Register for this pin
    uint16_t GPIO94:1;                  // 30 Data Register for this pin
    uint16_t GPIO95:1;                  // 31 Data Register for this pin
};

union GPIO_GPCDAT_REG {
    uint32_t  all;
    struct  GPIO_GPCDAT_BITS  bit;
};

struct GPIO_GPCSET_BITS {               // bits description
    uint16_t GPIO64:1;                  // 0 Output Set bit for this pin
    uint16_t GPIO65:1;                  // 1 Output Set bit for this pin
    uint16_t GPIO66:1;                  // 2 Output Set bit for this pin
    uint16_t GPIO67:1;                  // 3 Output Set bit for this pin
    uint16_t GPIO68:1;                  // 4 Output Set bit for this pin
    uint16_t GPIO69:1;                  // 5 Output Set bit for this pin
    uint16_t GPIO70:1;                  // 6 Output Set bit for this pin
    uint16_t GPIO71:1;                  // 7 Output Set bit for this pin
    uint16_t GPIO72:1;                  // 8 Output Set bit for this pin
    uint16_t GPIO73:1;                  // 9 Output Set bit for this pin
    uint16_t GPIO74:1;                  // 10 Output Set bit for this pin
    uint16_t GPIO75:1;                  // 11 Output Set bit for this pin
    uint16_t GPIO76:1;                  // 12 Output Set bit for this pin
    uint16_t GPIO77:1;                  // 13 Output Set bit for this pin
    uint16_t GPIO78:1;                  // 14 Output Set bit for this pin
    uint16_t GPIO79:1;                  // 15 Output Set bit for this pin
    uint16_t GPIO80:1;                  // 16 Output Set bit for this pin
    uint16_t GPIO81:1;                  // 17 Output Set bit for this pin
    uint16_t GPIO82:1;                  // 18 Output Set bit for this pin
    uint16_t GPIO83:1;                  // 19 Output Set bit for this pin
    uint16_t GPIO84:1;                  // 20 Output Set bit for this pin
    uint16_t GPIO85:1;                  // 21 Output Set bit for this pin
    uint16_t GPIO86:1;                  // 22 Output Set bit for this pin
    uint16_t GPIO87:1;                  // 23 Output Set bit for this pin
    uint16_t GPIO88:1;                  // 24 Output Set bit for this pin
    uint16_t GPIO89:1;                  // 25 Output Set bit for this pin
    uint16_t GPIO90:1;                  // 26 Output Set bit for this pin
    uint16_t GPIO91:1;                  // 27 Output Set bit for this pin
    uint16_t GPIO92:1;                  // 28 Output Set bit for this pin
    uint16_t GPIO93:1;                  // 29 Output Set bit for this pin
    uint16_t GPIO94:1;                  // 30 Output Set bit for this pin
    uint16_t GPIO95:1;                  // 31 Output Set bit for this pin
};

union GPIO_GPCSET_REG {
    uint32_t  all;
    struct  GPIO_GPCSET_BITS  bit;
};

struct GPIO_GPCCLEAR_BITS {             // bits description
    uint16_t GPIO64:1;                  // 0 Output Clear bit for this pin
    uint16_t GPIO65:1;                  // 1 Output Clear bit for this pin
    uint16_t GPIO66:1;                  // 2 Output Clear bit for this pin
    uint16_t GPIO67:1;                  // 3 Output Clear bit for this pin
    uint16_t GPIO68:1;                  // 4 Output Clear bit for this pin
    uint16_t GPIO69:1;                  // 5 Output Clear bit for this pin
    uint16_t GPIO70:1;                  // 6 Output Clear bit for this pin
    uint16_t GPIO71:1;                  // 7 Output Clear bit for this pin
    uint16_t GPIO72:1;                  // 8 Output Clear bit for this pin
    uint16_t GPIO73:1;                  // 9 Output Clear bit for this pin
    uint16_t GPIO74:1;                  // 10 Output Clear bit for this pin
    uint16_t GPIO75:1;                  // 11 Output Clear bit for this pin
    uint16_t GPIO76:1;                  // 12 Output Clear bit for this pin
    uint16_t GPIO77:1;                  // 13 Output Clear bit for this pin
    uint16_t GPIO78:1;                  // 14 Output Clear bit for this pin
    uint16_t GPIO79:1;                  // 15 Output Clear bit for this pin
    uint16_t GPIO80:1;                  // 16 Output Clear bit for this pin
    uint16_t GPIO81:1;                  // 17 Output Clear bit for this pin
    uint16_t GPIO82:1;                  // 18 Output Clear bit for this pin
    uint16_t GPIO83:1;                  // 19 Output Clear bit for this pin
    uint16_t GPIO84:1;                  // 20 Output Clear bit for this pin
    uint16_t GPIO85:1;                  // 21 Output Clear bit for this pin
    uint16_t GPIO86:1;                  // 22 Output Clear bit for this pin
    uint16_t GPIO87:1;                  // 23 Output Clear bit for this pin
    uint16_t GPIO88:1;                  // 24 Output Clear bit for this pin
    uint16_t GPIO89:1;                  // 25 Output Clear bit for this pin
    uint16_t GPIO90:1;                  // 26 Output Clear bit for this pin
    uint16_t GPIO91:1;                  // 27 Output Clear bit for this pin
    uint16_t GPIO92:1;                  // 28 Output Clear bit for this pin
    uint16_t GPIO93:1;                  // 29 Output Clear bit for this pin
    uint16_t GPIO94:1;                  // 30 Output Clear bit for this pin
    uint16_t GPIO95:1;                  // 31 Output Clear bit for this pin
};

union GPIO_GPCCLEAR_REG {
    uint32_t  all;
    struct  GPIO_GPCCLEAR_BITS  bit;
};

struct GPIO_GPCTOGGLE_BITS {            // bits description
    uint16_t GPIO64:1;                  // 0 Output Toggle bit for this pin
    uint16_t GPIO65:1;                  // 1 Output Toggle bit for this pin
    uint16_t GPIO66:1;                  // 2 Output Toggle bit for this pin
    uint16_t GPIO67:1;                  // 3 Output Toggle bit for this pin
    uint16_t GPIO68:1;                  // 4 Output Toggle bit for this pin
    uint16_t GPIO69:1;                  // 5 Output Toggle bit for this pin
    uint16_t GPIO70:1;                  // 6 Output Toggle bit for this pin
    uint16_t GPIO71:1;                  // 7 Output Toggle bit for this pin
    uint16_t GPIO72:1;                  // 8 Output Toggle bit for this pin
    uint16_t GPIO73:1;                  // 9 Output Toggle bit for this pin
    uint16_t GPIO74:1;                  // 10 Output Toggle bit for this pin
    uint16_t GPIO75:1;                  // 11 Output Toggle bit for this pin
    uint16_t GPIO76:1;                  // 12 Output Toggle bit for this pin
    uint16_t GPIO77:1;                  // 13 Output Toggle bit for this pin
    uint16_t GPIO78:1;                  // 14 Output Toggle bit for this pin
    uint16_t GPIO79:1;                  // 15 Output Toggle bit for this pin
    uint16_t GPIO80:1;                  // 16 Output Toggle bit for this pin
    uint16_t GPIO81:1;                  // 17 Output Toggle bit for this pin
    uint16_t GPIO82:1;                  // 18 Output Toggle bit for this pin
    uint16_t GPIO83:1;                  // 19 Output Toggle bit for this pin
    uint16_t GPIO84:1;                  // 20 Output Toggle bit for this pin
    uint16_t GPIO85:1;                  // 21 Output Toggle bit for this pin
    uint16_t GPIO86:1;                  // 22 Output Toggle bit for this pin
    uint16_t GPIO87:1;                  // 23 Output Toggle bit for this pin
    uint16_t GPIO88:1;                  // 24 Output Toggle bit for this pin
    uint16_t GPIO89:1;                  // 25 Output Toggle bit for this pin
    uint16_t GPIO90:1;                  // 26 Output Toggle bit for this pin
    uint16_t GPIO91:1;                  // 27 Output Toggle bit for this pin
    uint16_t GPIO92:1;                  // 28 Output Toggle bit for this pin
    uint16_t GPIO93:1;                  // 29 Output Toggle bit for this pin
    uint16_t GPIO94:1;                  // 30 Output Toggle bit for this pin
    uint16_t GPIO95:1;                  // 31 Output Toggle bit for this pin
};

union GPIO_GPCTOGGLE_REG {
    uint32_t  all;
    struct  GPIO_GPCTOGGLE_BITS  bit;
};

struct GPIO_GPCDIR_BITS {               // bits description
    uint16_t GPIO64:1;                  // 0 Defines direction for this pin in GPIO mode
    uint16_t GPIO65:1;                  // 1 Defines direction for this pin in GPIO mode
    uint16_t GPIO66:1;                  // 2 Defines direction for this pin in GPIO mode
    uint16_t GPIO67:1;                  // 3 Defines direction for this pin in GPIO mode
    uint16_t GPIO68:1;                  // 4 Defines direction for this pin in GPIO mode
    uint16_t GPIO69:1;                  // 5 Defines direction for this pin in GPIO mode
    uint16_t GPIO70:1;                  // 6 Defines direction for this pin in GPIO mode
    uint16_t GPIO71:1;                  // 7 Defines direction for this pin in GPIO mode
    uint16_t GPIO72:1;                  // 8 Defines direction for this pin in GPIO mode
    uint16_t GPIO73:1;                  // 9 Defines direction for this pin in GPIO mode
    uint16_t GPIO74:1;                  // 10 Defines direction for this pin in GPIO mode
    uint16_t GPIO75:1;                  // 11 Defines direction for this pin in GPIO mode
    uint16_t GPIO76:1;                  // 12 Defines direction for this pin in GPIO mode
    uint16_t GPIO77:1;                  // 13 Defines direction for this pin in GPIO mode
    uint16_t GPIO78:1;                  // 14 Defines direction for this pin in GPIO mode
    uint16_t GPIO79:1;                  // 15 Defines direction for this pin in GPIO mode
    uint16_t GPIO80:1;                  // 16 Defines direction for this pin in GPIO mode
    uint16_t GPIO81:1;                  // 17 Defines direction for this pin in GPIO mode
    uint16_t GPIO82:1;                  // 18 Defines direction for this pin in GPIO mode
    uint16_t GPIO83:1;                  // 19 Defines direction for this pin in GPIO mode
    uint16_t GPIO84:1;                  // 20 Defines direction for this pin in GPIO mode
    uint16_t GPIO85:1;                  // 21 Defines direction for this pin in GPIO mode
    uint16_t GPIO86:1;                  // 22 Defines direction for this pin in GPIO mode
    uint16_t GPIO87:1;                  // 23 Defines direction for this pin in GPIO mode
    uint16_t GPIO88:1;                  // 24 Defines direction for this pin in GPIO mode
    uint16_t GPIO89:1;                  // 25 Defines direction for this pin in GPIO mode
    uint16_t GPIO90:1;                  // 26 Defines direction for this pin in GPIO mode
    uint16_t GPIO91:1;                  // 27 Defines direction for this pin in GPIO mode
    uint16_t GPIO92:1;                  // 28 Defines direction for this pin in GPIO mode
    uint16_t GPIO93:1;                  // 29 Defines direction for this pin in GPIO mode
    uint16_t GPIO94:1;                  // 30 Defines direction for this pin in GPIO mode
    uint16_t GPIO95:1;                  // 31 Defines direction for this pin in GPIO mode
};

union GPIO_GPCDIR_REG {
    uint32_t  all;
    struct  GPIO_GPCDIR_BITS  bit;
};

struct GPIO_GPDDAT_BITS {               // bits description
    uint16_t GPIO96:1;                  // 0 Data Register for this pin
    uint16_t GPIO97:1;                  // 1 Data Register for this pin
    uint16_t GPIO98:1;                  // 2 Data Register for this pin
    uint16_t GPIO99:1;                  // 3 Data Register for this pin
    uint16_t GPIO100:1;                 // 4 Data Register for this pin
    uint16_t GPIO101:1;                 // 5 Data Register for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Data Register for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Data Register for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Data Register for this pin
};

union GPIO_GPDDAT_REG {
    uint32_t  all;
    struct  GPIO_GPDDAT_BITS  bit;
};

struct GPIO_GPDSET_BITS {               // bits description
    uint16_t GPIO96:1;                  // 0 Output Set bit for this pin
    uint16_t GPIO97:1;                  // 1 Output Set bit for this pin
    uint16_t GPIO98:1;                  // 2 Output Set bit for this pin
    uint16_t GPIO99:1;                  // 3 Output Set bit for this pin
    uint16_t GPIO100:1;                 // 4 Output Set bit for this pin
    uint16_t GPIO101:1;                 // 5 Output Set bit for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Output Set bit for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Output Set bit for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Output Set bit for this pin
};

union GPIO_GPDSET_REG {
    uint32_t  all;
    struct  GPIO_GPDSET_BITS  bit;
};

struct GPIO_GPDCLEAR_BITS {             // bits description
    uint16_t GPIO96:1;                  // 0 Output Clear bit for this pin
    uint16_t GPIO97:1;                  // 1 Output Clear bit for this pin
    uint16_t GPIO98:1;                  // 2 Output Clear bit for this pin
    uint16_t GPIO99:1;                  // 3 Output Clear bit for this pin
    uint16_t GPIO100:1;                 // 4 Output Clear bit for this pin
    uint16_t GPIO101:1;                 // 5 Output Clear bit for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Output Clear bit for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Output Clear bit for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Output Clear bit for this pin
};

union GPIO_GPDCLEAR_REG {
    uint32_t  all;
    struct  GPIO_GPDCLEAR_BITS  bit;
};

struct GPIO_GPDTOGGLE_BITS {            // bits description
    uint16_t GPIO96:1;                  // 0 Output Toggle bit for this pin
    uint16_t GPIO97:1;                  // 1 Output Toggle bit for this pin
    uint16_t GPIO98:1;                  // 2 Output Toggle bit for this pin
    uint16_t GPIO99:1;                  // 3 Output Toggle bit for this pin
    uint16_t GPIO100:1;                 // 4 Output Toggle bit for this pin
    uint16_t GPIO101:1;                 // 5 Output Toggle bit for this pin
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Output Toggle bit for this pin
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Output Toggle bit for this pin
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Output Toggle bit for this pin
};

union GPIO_GPDTOGGLE_REG {
    uint32_t  all;
    struct  GPIO_GPDTOGGLE_BITS  bit;
};

struct GPIO_GPDDIR_BITS {               // bits description
    uint16_t GPIO96:1;                  // 0 Defines direction for this pin in GPIO mode
    uint16_t GPIO97:1;                  // 1 Defines direction for this pin in GPIO mode
    uint16_t GPIO98:1;                  // 2 Defines direction for this pin in GPIO mode
    uint16_t GPIO99:1;                  // 3 Defines direction for this pin in GPIO mode
    uint16_t GPIO100:1;                 // 4 Defines direction for this pin in GPIO mode
    uint16_t GPIO101:1;                 // 5 Defines direction for this pin in GPIO mode
    uint16_t rsvd1:1;                   // 6 Reserved
    uint16_t GPIO103:1;                 // 7 Defines direction for this pin in GPIO mode
    uint16_t rsvd2:1;                   // 8 Reserved
    uint16_t GPIO105:1;                 // 9 Defines direction for this pin in GPIO mode
    uint16_t rsvd3:1;                   // 10 Reserved
    uint16_t rsvd4:1;                   // 11 Reserved
    uint16_t rsvd5:1;                   // 12 Reserved
    uint16_t rsvd6:1;                   // 13 Reserved
    uint16_t rsvd7:1;                   // 14 Reserved
    uint16_t rsvd8:1;                   // 15 Reserved
    uint16_t rsvd9:1;                   // 16 Reserved
    uint16_t rsvd10:1;                  // 17 Reserved
    uint16_t rsvd11:1;                  // 18 Reserved
    uint16_t rsvd12:1;                  // 19 Reserved
    uint16_t rsvd13:1;                  // 20 Reserved
    uint16_t rsvd14:1;                  // 21 Reserved
    uint16_t rsvd15:1;                  // 22 Reserved
    uint16_t rsvd16:1;                  // 23 Reserved
    uint16_t rsvd17:1;                  // 24 Reserved
    uint16_t rsvd18:1;                  // 25 Reserved
    uint16_t rsvd19:1;                  // 26 Reserved
    uint16_t rsvd20:1;                  // 27 Reserved
    uint16_t rsvd21:1;                  // 28 Reserved
    uint16_t rsvd22:1;                  // 29 Reserved
    uint16_t rsvd23:1;                  // 30 Reserved
    uint16_t GPIO127:1;                 // 31 Defines direction for this pin in GPIO mode
};

union GPIO_GPDDIR_REG {
    uint32_t  all;
    struct  GPIO_GPDDIR_BITS  bit;
};

struct GPIO_GPFDAT_BITS {               // bits description
    uint16_t GPIO160:1;                 // 0 Data Register for this pin
    uint16_t GPIO161:1;                 // 1 Data Register for this pin
    uint16_t GPIO162:1;                 // 2 Data Register for this pin
    uint16_t GPIO163:1;                 // 3 Data Register for this pin
    uint16_t GPIO164:1;                 // 4 Data Register for this pin
    uint16_t GPIO165:1;                 // 5 Data Register for this pin
    uint16_t GPIO166:1;                 // 6 Data Register for this pin
    uint16_t GPIO167:1;                 // 7 Data Register for this pin
    uint16_t GPIO168:1;                 // 8 Data Register for this pin
    uint16_t GPIO169:1;                 // 9 Data Register for this pin
    uint16_t GPIO170:1;                 // 10 Data Register for this pin
    uint16_t GPIO171:1;                 // 11 Data Register for this pin
    uint16_t GPIO172:1;                 // 12 Data Register for this pin
    uint16_t GPIO173:1;                 // 13 Data Register for this pin
    uint16_t GPIO174:1;                 // 14 Data Register for this pin
    uint16_t GPIO175:1;                 // 15 Data Register for this pin
    uint16_t GPIO176:1;                 // 16 Data Register for this pin
    uint16_t GPIO177:1;                 // 17 Data Register for this pin
    uint16_t GPIO178:1;                 // 18 Data Register for this pin
    uint16_t GPIO179:1;                 // 19 Data Register for this pin
    uint16_t GPIO180:1;                 // 20 Data Register for this pin
    uint16_t GPIO181:1;                 // 21 Data Register for this pin
    uint16_t GPIO182:1;                 // 22 Data Register for this pin
    uint16_t GPIO183:1;                 // 23 Data Register for this pin
    uint16_t GPIO184:1;                 // 24 Data Register for this pin
    uint16_t GPIO185:1;                 // 25 Data Register for this pin
    uint16_t GPIO186:1;                 // 26 Data Register for this pin
    uint16_t GPIO187:1;                 // 27 Data Register for this pin
    uint16_t GPIO188:1;                 // 28 Data Register for this pin
    uint16_t GPIO189:1;                 // 29 Data Register for this pin
    uint16_t GPIO190:1;                 // 30 Data Register for this pin
    uint16_t GPIO191:1;                 // 31 Data Register for this pin
};

union GPIO_GPFDAT_REG {
    uint32_t  all;
    struct  GPIO_GPFDAT_BITS  bit;
};

struct GPIO_GPGDAT_BITS {               // bits description
    uint16_t GPIO192:1;                 // 0 Data Register for this pin
    uint16_t GPIO193:1;                 // 1 Data Register for this pin
    uint16_t GPIO194:1;                 // 2 Data Register for this pin
    uint16_t GPIO195:1;                 // 3 Data Register for this pin
    uint16_t GPIO196:1;                 // 4 Data Register for this pin
    uint16_t GPIO197:1;                 // 5 Data Register for this pin
    uint16_t GPIO198:1;                 // 6 Data Register for this pin
    uint16_t GPIO199:1;                 // 7 Data Register for this pin
    uint16_t GPIO200:1;                 // 8 Data Register for this pin
    uint16_t GPIO201:1;                 // 9 Data Register for this pin
    uint16_t GPIO202:1;                 // 10 Data Register for this pin
    uint16_t GPIO203:1;                 // 11 Data Register for this pin
    uint16_t GPIO204:1;                 // 12 Data Register for this pin
    uint16_t GPIO205:1;                 // 13 Data Register for this pin
    uint16_t GPIO206:1;                 // 14 Data Register for this pin
    uint16_t GPIO207:1;                 // 15 Data Register for this pin
    uint16_t GPIO208:1;                 // 16 Data Register for this pin
    uint16_t GPIO209:1;                 // 17 Data Register for this pin
    uint16_t GPIO210:1;                 // 18 Data Register for this pin
    uint16_t GPIO211:1;                 // 19 Data Register for this pin
    uint16_t GPIO212:1;                 // 20 Data Register for this pin
    uint16_t GPIO213:1;                 // 21 Data Register for this pin
    uint16_t rsvd1:1;                   // 22 Reserved
    uint16_t rsvd2:1;                   // 23 Reserved
    uint16_t rsvd3:1;                   // 24 Reserved
    uint16_t rsvd4:1;                   // 25 Reserved
    uint16_t rsvd5:1;                   // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Data Register for this pin
    uint16_t GPIO220:1;                 // 28 Data Register for this pin
    uint16_t GPIO221:1;                 // 29 Data Register for this pin
    uint16_t GPIO222:1;                 // 30 Data Register for this pin
    uint16_t GPIO223:1;                 // 31 Data Register for this pin
};

union GPIO_GPGDAT_REG {
    uint32_t  all;
    struct  GPIO_GPGDAT_BITS  bit;
};

struct GPIO_GPGSET_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:1;                   // 4 Reserved
    uint16_t rsvd6:1;                   // 5 Reserved
    uint16_t rsvd7:1;                   // 6 Reserved
    uint16_t rsvd8:1;                   // 7 Reserved
    uint16_t rsvd9:1;                   // 8 Reserved
    uint16_t rsvd10:1;                  // 9 Reserved
    uint16_t rsvd11:1;                  // 10 Reserved
    uint16_t rsvd12:1;                  // 11 Reserved
    uint16_t rsvd13:1;                  // 12 Reserved
    uint16_t rsvd14:1;                  // 13 Reserved
    uint16_t rsvd15:1;                  // 14 Reserved
    uint16_t rsvd16:1;                  // 15 Reserved
    uint16_t rsvd17:1;                  // 16 Reserved
    uint16_t rsvd18:1;                  // 17 Reserved
    uint16_t rsvd19:1;                  // 18 Reserved
    uint16_t rsvd20:1;                  // 19 Reserved
    uint16_t rsvd21:1;                  // 20 Reserved
    uint16_t rsvd22:1;                  // 21 Reserved
    uint16_t rsvd23:1;                  // 22 Reserved
    uint16_t rsvd24:1;                  // 23 Reserved
    uint16_t rsvd25:1;                  // 24 Reserved
    uint16_t rsvd26:1;                  // 25 Reserved
    uint16_t rsvd27:1;                  // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Output Set bit for this pin
    uint16_t GPIO220:1;                 // 28 Output Set bit for this pin
    uint16_t GPIO221:1;                 // 29 Output Set bit for this pin
    uint16_t GPIO222:1;                 // 30 Output Set bit for this pin
    uint16_t GPIO223:1;                 // 31 Output Set bit for this pin
};

union GPIO_GPGSET_REG {
    uint32_t  all;
    struct  GPIO_GPGSET_BITS  bit;
};

struct GPIO_GPGCLEAR_BITS {             // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:1;                   // 4 Reserved
    uint16_t rsvd6:1;                   // 5 Reserved
    uint16_t rsvd7:1;                   // 6 Reserved
    uint16_t rsvd8:1;                   // 7 Reserved
    uint16_t rsvd9:1;                   // 8 Reserved
    uint16_t rsvd10:1;                  // 9 Reserved
    uint16_t rsvd11:1;                  // 10 Reserved
    uint16_t rsvd12:1;                  // 11 Reserved
    uint16_t rsvd13:1;                  // 12 Reserved
    uint16_t rsvd14:1;                  // 13 Reserved
    uint16_t rsvd15:1;                  // 14 Reserved
    uint16_t rsvd16:1;                  // 15 Reserved
    uint16_t rsvd17:1;                  // 16 Reserved
    uint16_t rsvd18:1;                  // 17 Reserved
    uint16_t rsvd19:1;                  // 18 Reserved
    uint16_t rsvd20:1;                  // 19 Reserved
    uint16_t rsvd21:1;                  // 20 Reserved
    uint16_t rsvd22:1;                  // 21 Reserved
    uint16_t rsvd23:1;                  // 22 Reserved
    uint16_t rsvd24:1;                  // 23 Reserved
    uint16_t rsvd25:1;                  // 24 Reserved
    uint16_t rsvd26:1;                  // 25 Reserved
    uint16_t rsvd27:1;                  // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Output Clear bit for this pin
    uint16_t GPIO220:1;                 // 28 Output Clear bit for this pin
    uint16_t GPIO221:1;                 // 29 Output Clear bit for this pin
    uint16_t GPIO222:1;                 // 30 Output Clear bit for this pin
    uint16_t GPIO223:1;                 // 31 Output Clear bit for this pin
};

union GPIO_GPGCLEAR_REG {
    uint32_t  all;
    struct  GPIO_GPGCLEAR_BITS  bit;
};

struct GPIO_GPGTOGGLE_BITS {            // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:1;                   // 4 Reserved
    uint16_t rsvd6:1;                   // 5 Reserved
    uint16_t rsvd7:1;                   // 6 Reserved
    uint16_t rsvd8:1;                   // 7 Reserved
    uint16_t rsvd9:1;                   // 8 Reserved
    uint16_t rsvd10:1;                  // 9 Reserved
    uint16_t rsvd11:1;                  // 10 Reserved
    uint16_t rsvd12:1;                  // 11 Reserved
    uint16_t rsvd13:1;                  // 12 Reserved
    uint16_t rsvd14:1;                  // 13 Reserved
    uint16_t rsvd15:1;                  // 14 Reserved
    uint16_t rsvd16:1;                  // 15 Reserved
    uint16_t rsvd17:1;                  // 16 Reserved
    uint16_t rsvd18:1;                  // 17 Reserved
    uint16_t rsvd19:1;                  // 18 Reserved
    uint16_t rsvd20:1;                  // 19 Reserved
    uint16_t rsvd21:1;                  // 20 Reserved
    uint16_t rsvd22:1;                  // 21 Reserved
    uint16_t rsvd23:1;                  // 22 Reserved
    uint16_t rsvd24:1;                  // 23 Reserved
    uint16_t rsvd25:1;                  // 24 Reserved
    uint16_t rsvd26:1;                  // 25 Reserved
    uint16_t rsvd27:1;                  // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Output Toggle bit for this pin
    uint16_t GPIO220:1;                 // 28 Output Toggle bit for this pin
    uint16_t GPIO221:1;                 // 29 Output Toggle bit for this pin
    uint16_t GPIO222:1;                 // 30 Output Toggle bit for this pin
    uint16_t GPIO223:1;                 // 31 Output Toggle bit for this pin
};

union GPIO_GPGTOGGLE_REG {
    uint32_t  all;
    struct  GPIO_GPGTOGGLE_BITS  bit;
};

struct GPIO_GPGDIR_BITS {               // bits description
    uint16_t rsvd1:1;                   // 0 Reserved
    uint16_t rsvd2:1;                   // 1 Reserved
    uint16_t rsvd3:1;                   // 2 Reserved
    uint16_t rsvd4:1;                   // 3 Reserved
    uint16_t rsvd5:1;                   // 4 Reserved
    uint16_t rsvd6:1;                   // 5 Reserved
    uint16_t rsvd7:1;                   // 6 Reserved
    uint16_t rsvd8:1;                   // 7 Reserved
    uint16_t rsvd9:1;                   // 8 Reserved
    uint16_t rsvd10:1;                  // 9 Reserved
    uint16_t rsvd11:1;                  // 10 Reserved
    uint16_t rsvd12:1;                  // 11 Reserved
    uint16_t rsvd13:1;                  // 12 Reserved
    uint16_t rsvd14:1;                  // 13 Reserved
    uint16_t rsvd15:1;                  // 14 Reserved
    uint16_t rsvd16:1;                  // 15 Reserved
    uint16_t rsvd17:1;                  // 16 Reserved
    uint16_t rsvd18:1;                  // 17 Reserved
    uint16_t rsvd19:1;                  // 18 Reserved
    uint16_t rsvd20:1;                  // 19 Reserved
    uint16_t rsvd21:1;                  // 20 Reserved
    uint16_t rsvd22:1;                  // 21 Reserved
    uint16_t rsvd23:1;                  // 22 Reserved
    uint16_t rsvd24:1;                  // 23 Reserved
    uint16_t rsvd25:1;                  // 24 Reserved
    uint16_t rsvd26:1;                  // 25 Reserved
    uint16_t rsvd27:1;                  // 26 Reserved
    uint16_t GPIO219:1;                 // 27 Defines direction for this pin in GPIO mode
    uint16_t GPIO220:1;                 // 28 Defines direction for this pin in GPIO mode
    uint16_t GPIO221:1;                 // 29 Defines direction for this pin in GPIO mode
    uint16_t GPIO222:1;                 // 30 Defines direction for this pin in GPIO mode
    uint16_t GPIO223:1;                 // 31 Defines direction for this pin in GPIO mode
};

union GPIO_GPGDIR_REG {
    uint32_t  all;
    struct  GPIO_GPGDIR_BITS  bit;
};

struct GPIO_GPHDAT_BITS {               // bits description
    uint16_t GPIO224:1;                 // 0 Data Register for this pin
    uint16_t GPIO225:1;                 // 1 Data Register for this pin
    uint16_t GPIO226:1;                 // 2 Data Register for this pin
    uint16_t GPIO227:1;                 // 3 Data Register for this pin
    uint16_t GPIO228:1;                 // 4 Data Register for this pin
    uint16_t GPIO229:1;                 // 5 Data Register for this pin
    uint16_t GPIO230:1;                 // 6 Data Register for this pin
    uint16_t GPIO231:1;                 // 7 Data Register for this pin
    uint16_t GPIO232:1;                 // 8 Data Register for this pin
    uint16_t GPIO233:1;                 // 9 Data Register for this pin
    uint16_t GPIO234:1;                 // 10 Data Register for this pin
    uint16_t GPIO235:1;                 // 11 Data Register for this pin
    uint16_t GPIO236:1;                 // 12 Data Register for this pin
    uint16_t GPIO237:1;                 // 13 Data Register for this pin
    uint16_t GPIO238:1;                 // 14 Data Register for this pin
    uint16_t GPIO239:1;                 // 15 Data Register for this pin
    uint16_t GPIO240:1;                 // 16 Data Register for this pin
    uint16_t GPIO241:1;                 // 17 Data Register for this pin
    uint16_t GPIO242:1;                 // 18 Data Register for this pin
    uint16_t GPIO243:1;                 // 19 Data Register for this pin
    uint16_t GPIO244:1;                 // 20 Data Register for this pin
    uint16_t GPIO245:1;                 // 21 Data Register for this pin
    uint16_t GPIO246:1;                 // 22 Data Register for this pin
    uint16_t GPIO247:1;                 // 23 Data Register for this pin
    uint16_t GPIO248:1;                 // 24 Data Register for this pin
    uint16_t GPIO249:1;                 // 25 Data Register for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHDAT_REG {
    uint32_t  all;
    struct  GPIO_GPHDAT_BITS  bit;
};

struct GPIO_GPHSET_BITS {               // bits description
    uint16_t GPIO224:1;                 // 0 Output Set bit for this pin
    uint16_t GPIO225:1;                 // 1 Output Set bit for this pin
    uint16_t GPIO226:1;                 // 2 Output Set bit for this pin
    uint16_t GPIO227:1;                 // 3 Output Set bit for this pin
    uint16_t GPIO228:1;                 // 4 Output Set bit for this pin
    uint16_t GPIO229:1;                 // 5 Output Set bit for this pin
    uint16_t GPIO230:1;                 // 6 Output Set bit for this pin
    uint16_t GPIO231:1;                 // 7 Output Set bit for this pin
    uint16_t GPIO232:1;                 // 8 Output Set bit for this pin
    uint16_t GPIO233:1;                 // 9 Output Set bit for this pin
    uint16_t GPIO234:1;                 // 10 Output Set bit for this pin
    uint16_t GPIO235:1;                 // 11 Output Set bit for this pin
    uint16_t GPIO236:1;                 // 12 Output Set bit for this pin
    uint16_t GPIO237:1;                 // 13 Output Set bit for this pin
    uint16_t GPIO238:1;                 // 14 Output Set bit for this pin
    uint16_t GPIO239:1;                 // 15 Output Set bit for this pin
    uint16_t GPIO240:1;                 // 16 Output Set bit for this pin
    uint16_t GPIO241:1;                 // 17 Output Set bit for this pin
    uint16_t GPIO242:1;                 // 18 Output Set bit for this pin
    uint16_t GPIO243:1;                 // 19 Output Set bit for this pin
    uint16_t GPIO244:1;                 // 20 Output Set bit for this pin
    uint16_t GPIO245:1;                 // 21 Output Set bit for this pin
    uint16_t GPIO246:1;                 // 22 Output Set bit for this pin
    uint16_t GPIO247:1;                 // 23 Output Set bit for this pin
    uint16_t GPIO248:1;                 // 24 Output Set bit for this pin
    uint16_t GPIO249:1;                 // 25 Output Set bit for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHSET_REG {
    uint32_t  all;
    struct  GPIO_GPHSET_BITS  bit;
};

struct GPIO_GPHCLEAR_BITS {             // bits description
    uint16_t GPIO224:1;                 // 0 Output Clear bit for this pin
    uint16_t GPIO225:1;                 // 1 Output Clear bit for this pin
    uint16_t GPIO226:1;                 // 2 Output Clear bit for this pin
    uint16_t GPIO227:1;                 // 3 Output Clear bit for this pin
    uint16_t GPIO228:1;                 // 4 Output Clear bit for this pin
    uint16_t GPIO229:1;                 // 5 Output Clear bit for this pin
    uint16_t GPIO230:1;                 // 6 Output Clear bit for this pin
    uint16_t GPIO231:1;                 // 7 Output Clear bit for this pin
    uint16_t GPIO232:1;                 // 8 Output Clear bit for this pin
    uint16_t GPIO233:1;                 // 9 Output Clear bit for this pin
    uint16_t GPIO234:1;                 // 10 Output Clear bit for this pin
    uint16_t GPIO235:1;                 // 11 Output Clear bit for this pin
    uint16_t GPIO236:1;                 // 12 Output Clear bit for this pin
    uint16_t GPIO237:1;                 // 13 Output Clear bit for this pin
    uint16_t GPIO238:1;                 // 14 Output Clear bit for this pin
    uint16_t GPIO239:1;                 // 15 Output Clear bit for this pin
    uint16_t GPIO240:1;                 // 16 Output Clear bit for this pin
    uint16_t GPIO241:1;                 // 17 Output Clear bit for this pin
    uint16_t GPIO242:1;                 // 18 Output Clear bit for this pin
    uint16_t GPIO243:1;                 // 19 Output Clear bit for this pin
    uint16_t GPIO244:1;                 // 20 Output Clear bit for this pin
    uint16_t GPIO245:1;                 // 21 Output Clear bit for this pin
    uint16_t GPIO246:1;                 // 22 Output Clear bit for this pin
    uint16_t GPIO247:1;                 // 23 Output Clear bit for this pin
    uint16_t GPIO248:1;                 // 24 Output Clear bit for this pin
    uint16_t GPIO249:1;                 // 25 Output Clear bit for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHCLEAR_REG {
    uint32_t  all;
    struct  GPIO_GPHCLEAR_BITS  bit;
};

struct GPIO_GPHTOGGLE_BITS {            // bits description
    uint16_t GPIO224:1;                 // 0 Output Toggle bit for this pin
    uint16_t GPIO225:1;                 // 1 Output Toggle bit for this pin
    uint16_t GPIO226:1;                 // 2 Output Toggle bit for this pin
    uint16_t GPIO227:1;                 // 3 Output Toggle bit for this pin
    uint16_t GPIO228:1;                 // 4 Output Toggle bit for this pin
    uint16_t GPIO229:1;                 // 5 Output Toggle bit for this pin
    uint16_t GPIO230:1;                 // 6 Output Toggle bit for this pin
    uint16_t GPIO231:1;                 // 7 Output Toggle bit for this pin
    uint16_t GPIO232:1;                 // 8 Output Toggle bit for this pin
    uint16_t GPIO233:1;                 // 9 Output Toggle bit for this pin
    uint16_t GPIO234:1;                 // 10 Output Toggle bit for this pin
    uint16_t GPIO235:1;                 // 11 Output Toggle bit for this pin
    uint16_t GPIO236:1;                 // 12 Output Toggle bit for this pin
    uint16_t GPIO237:1;                 // 13 Output Toggle bit for this pin
    uint16_t GPIO238:1;                 // 14 Output Toggle bit for this pin
    uint16_t GPIO239:1;                 // 15 Output Toggle bit for this pin
    uint16_t GPIO240:1;                 // 16 Output Toggle bit for this pin
    uint16_t GPIO241:1;                 // 17 Output Toggle bit for this pin
    uint16_t GPIO242:1;                 // 18 Output Toggle bit for this pin
    uint16_t GPIO243:1;                 // 19 Output Toggle bit for this pin
    uint16_t GPIO244:1;                 // 20 Output Toggle bit for this pin
    uint16_t GPIO245:1;                 // 21 Output Toggle bit for this pin
    uint16_t GPIO246:1;                 // 22 Output Toggle bit for this pin
    uint16_t GPIO247:1;                 // 23 Output Toggle bit for this pin
    uint16_t GPIO248:1;                 // 24 Output Toggle bit for this pin
    uint16_t GPIO249:1;                 // 25 Output Toggle bit for this pin
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHTOGGLE_REG {
    uint32_t  all;
    struct  GPIO_GPHTOGGLE_BITS  bit;
};

struct GPIO_GPHDIR_BITS {               // bits description
    uint16_t GPIO224:1;                 // 0 Defines direction for this pin in GPIO mode
    uint16_t GPIO225:1;                 // 1 Defines direction for this pin in GPIO mode
    uint16_t GPIO226:1;                 // 2 Defines direction for this pin in GPIO mode
    uint16_t GPIO227:1;                 // 3 Defines direction for this pin in GPIO mode
    uint16_t GPIO228:1;                 // 4 Defines direction for this pin in GPIO mode
    uint16_t GPIO229:1;                 // 5 Defines direction for this pin in GPIO mode
    uint16_t GPIO230:1;                 // 6 Defines direction for this pin in GPIO mode
    uint16_t GPIO231:1;                 // 7 Defines direction for this pin in GPIO mode
    uint16_t GPIO232:1;                 // 8 Defines direction for this pin in GPIO mode
    uint16_t GPIO233:1;                 // 9 Defines direction for this pin in GPIO mode
    uint16_t GPIO234:1;                 // 10 Defines direction for this pin in GPIO mode
    uint16_t GPIO235:1;                 // 11 Defines direction for this pin in GPIO mode
    uint16_t GPIO236:1;                 // 12 Defines direction for this pin in GPIO mode
    uint16_t GPIO237:1;                 // 13 Defines direction for this pin in GPIO mode
    uint16_t GPIO238:1;                 // 14 Defines direction for this pin in GPIO mode
    uint16_t GPIO239:1;                 // 15 Defines direction for this pin in GPIO mode
    uint16_t GPIO240:1;                 // 16 Defines direction for this pin in GPIO mode
    uint16_t GPIO241:1;                 // 17 Defines direction for this pin in GPIO mode
    uint16_t GPIO242:1;                 // 18 Defines direction for this pin in GPIO mode
    uint16_t GPIO243:1;                 // 19 Defines direction for this pin in GPIO mode
    uint16_t GPIO244:1;                 // 20 Defines direction for this pin in GPIO mode
    uint16_t GPIO245:1;                 // 21 Defines direction for this pin in GPIO mode
    uint16_t GPIO246:1;                 // 22 Defines direction for this pin in GPIO mode
    uint16_t GPIO247:1;                 // 23 Defines direction for this pin in GPIO mode
    uint16_t GPIO248:1;                 // 24 Defines direction for this pin in GPIO mode
    uint16_t GPIO249:1;                 // 25 Defines direction for this pin in GPIO mode
    uint16_t rsvd1:1;                   // 26 Reserved
    uint16_t rsvd2:1;                   // 27 Reserved
    uint16_t rsvd3:1;                   // 28 Reserved
    uint16_t rsvd4:1;                   // 29 Reserved
    uint16_t rsvd5:1;                   // 30 Reserved
    uint16_t rsvd6:1;                   // 31 Reserved
};

union GPIO_GPHDIR_REG {
    uint32_t  all;
    struct  GPIO_GPHDIR_BITS  bit;
};

struct GPIO_DATA_REGS {
    union   GPIO_GPADAT_REG                  GPADAT;                       // GPIO A Data Register (GPIO0 to 31)
    union   GPIO_GPASET_REG                  GPASET;                       // GPIO A Data Set Register (GPIO0 to 31)
    union   GPIO_GPACLEAR_REG                GPACLEAR;                     // GPIO A Data Clear Register (GPIO0 to 31)
    union   GPIO_GPATOGGLE_REG               GPATOGGLE;                    // GPIO A Data Toggle Register (GPIO0 to 31)
    union   GPIO_GPADIR_REG                  GPADIR;                       // GPIO A Direction Register (GPIO0 to 31)
    union   GPIO_GPBDAT_REG                  GPBDAT;                       // GPIO B Data Register (GPIO32 to 63)
    union   GPIO_GPBSET_REG                  GPBSET;                       // GPIO B Data Set Register (GPIO32 to 63)
    union   GPIO_GPBCLEAR_REG                GPBCLEAR;                     // GPIO B Data Clear Register (GPIO32 to 63)
    union   GPIO_GPBTOGGLE_REG               GPBTOGGLE;                    // GPIO B Data Toggle Register (GPIO32 to 63)
    union   GPIO_GPBDIR_REG                  GPBDIR;                       // GPIO B Direction Register (GPIO0 to 31)
    union   GPIO_GPCDAT_REG                  GPCDAT;                       // GPIO C Data Register (GPIO64 to 95)
    union   GPIO_GPCSET_REG                  GPCSET;                       // GPIO C Data Set Register (GPIO64 to 95)
    union   GPIO_GPCCLEAR_REG                GPCCLEAR;                     // GPIO C Data Clear Register (GPIO64 to 95)
    union   GPIO_GPCTOGGLE_REG               GPCTOGGLE;                    // GPIO C Data Toggle Register (GPIO64 to 95)
    union   GPIO_GPCDIR_REG                  GPCDIR;                       // GPIO C Direction Register (GPIO0 to 31)
    union   GPIO_GPDDAT_REG                  GPDDAT;                       // GPIO D Data Register (GPIO96 to 127)
    union   GPIO_GPDSET_REG                  GPDSET;                       // GPIO D Data Set Register (GPIO96 to 127)
    union   GPIO_GPDCLEAR_REG                GPDCLEAR;                     // GPIO D Data Clear Register (GPIO96 to 127)
    union   GPIO_GPDTOGGLE_REG               GPDTOGGLE;                    // GPIO D Data Toggle Register (GPIO96 to 127)
    union   GPIO_GPDDIR_REG                  GPDDIR;                       // GPIO D Direction Register (GPIO0 to 31)
    uint8_t                                  rsvd1[20];                    // Reserved
    union   GPIO_GPFDAT_REG                  GPFDAT;                       // GPIO F Data Register (GPIO160 to 191)
    uint8_t                                  rsvd2[16];                    // Reserved
    union   GPIO_GPGDAT_REG                  GPGDAT;                       // GPIO G Data Register (GPIO192 to 223)
    union   GPIO_GPGSET_REG                  GPGSET;                       // GPIO G Data Set Register (GPIO192 to 223)
    union   GPIO_GPGCLEAR_REG                GPGCLEAR;                     // GPIO G Data Clear Register (GPIO192 to 223)
    union   GPIO_GPGTOGGLE_REG               GPGTOGGLE;                    // GPIO G Data Toggle Register (GPIO192 to 223)
    union   GPIO_GPGDIR_REG                  GPGDIR;                       // GPIO G Direction Register (GPIO0 to 31)
    union   GPIO_GPHDAT_REG                  GPHDAT;                       // GPIO H Data Register (GPIO224 to 255)
    union   GPIO_GPHSET_REG                  GPHSET;                       // GPIO H Data Set Register (GPIO224 to 255)
    union   GPIO_GPHCLEAR_REG                GPHCLEAR;                     // GPIO H Data Clear Register (GPIO224 to 255)
    union   GPIO_GPHTOGGLE_REG               GPHTOGGLE;                    // GPIO H Data Toggle Register (GPIO224 to 255)
    union   GPIO_GPHDIR_REG                  GPHDIR;                       // GPIO H Direction Register (GPIO0 to 31)
};

struct GPIO_DATA_READ_REGS {
    uint32_t                                 GPADAT_R;                     // GPIO A Data Read Register
    uint32_t                                 GPBDAT_R;                     // GPIO B Data Read Register
    uint32_t                                 GPCDAT_R;                     // GPIO C Data Read Register
    uint32_t                                 GPDDAT_R;                     // GPIO D Data Read Register
    uint8_t                                  rsvd1[4];                     // Reserved
    uint32_t                                 GPFDAT_R;                     // GPIO F Data Read Register
    uint32_t                                 GPGDAT_R;                     // GPIO G Data Read Register
    uint32_t                                 GPHDAT_R;                     // GPIO H Data Read Register
};

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
