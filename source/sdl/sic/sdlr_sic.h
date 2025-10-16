/********************************************************************
 * Copyright (C) 2025 Texas Instruments Incorporated.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef SDLR_SIC_H_
#define SDLR_SIC_H_

/***************************************************************************************************
 *
 * The following are defines for the RTDMA register offsets
 *
 ***************************************************************************************************/
#define SDL_RTDMA_O_DMACTRL                    0x0U     /*DMA Control Register*/
#define SDL_RTDMA_O_DEBUGCTRL                  0x4U     /*Debug Control Register*/
#define SDL_RTDMA_O_REVISION                   0x8U     /*RTDMA Revision Control Register*/
#define SDL_RTDMA_O_SWPRI1                     0x14U    /*Software Priority Configuration Register 1*/
#define SDL_RTDMA_O_SWPRI2                     0x18U    /*Software Priority Configuration Register 2*/
#define SDL_RTDMA_O_PRIORITYSTAT               0x1CU    /*Priority Status Register*/
#define SDL_RTDMA_O_DMACFG_LOCK                0x40U    /*Channel Configuration Temporary Lock*/
#define SDL_RTDMA_O_DMACFG_COMMIT              0x44U    /*Channel Configuration Permanent Commit Permissions*/
#define SDL_RTDMA_O_MPUCTRL                    0x800U   /*MPU Control Register*/
#define SDL_RTDMA_O_MPUCFG_LOCK                0x820U   /*Channel Configuration Temporary Lock*/
#define SDL_RTDMA_O_MPUCFG_COMMIT              0x824U   /*Channel Configuration Permanent Commit*/
#define SDL_RTDMA_O_MODE                       0x0U     /*Mode Register*/
#define SDL_RTDMA_O_CONTROL                    0x4U     /*Control Register*/
#define SDL_RTDMA_O_BURST_SIZE                 0x8U     /*Burst Size Register*/
#define SDL_RTDMA_O_BURST_COUNT                0xCU     /*Burst Count Register*/
#define SDL_RTDMA_O_SRC_BURST_STEP             0x10U    /*Source Burst Step Register*/
#define SDL_RTDMA_O_DST_BURST_STEP             0x14U    /*Destination Burst Step Register*/
#define SDL_RTDMA_O_TRANSFER_SIZE              0x18U    /*Transfer Size Register*/
#define SDL_RTDMA_O_TRANSFER_COUNT             0x1CU    /*Transfer Count Register*/
#define SDL_RTDMA_O_SRC_TRANSFER_STEP          0x20U    /*Source Transfer Step Register*/
#define SDL_RTDMA_O_DST_TRANSFER_STEP          0x24U    /*Destination Transfer Step Register*/
#define SDL_RTDMA_O_SRC_WRAP_SIZE              0x28U    /*Source Wrap Size Register*/
#define SDL_RTDMA_O_SRC_WRAP_COUNT             0x2CU    /*Source Wrap Count Register*/
#define SDL_RTDMA_O_SRC_WRAP_STEP              0x30U    /*Source Wrap Step Register*/
#define SDL_RTDMA_O_DST_WRAP_SIZE              0x34U    /*Destination Wrap Size Register*/
#define SDL_RTDMA_O_DST_WRAP_COUNT             0x38U    /*Destination Wrap Count Register*/
#define SDL_RTDMA_O_DST_WRAP_STEP              0x3CU    /*Destination Wrap Step Register*/
#define SDL_RTDMA_O_SRC_BEG_ADDR_SHADOW        0x40U    /*Source Begin Address Shadow Register*/
#define SDL_RTDMA_O_SRC_ADDR_SHADOW            0x44U    /*Source Address Shadow Register*/
#define SDL_RTDMA_O_SRC_BEG_ADDR_ACTIVE        0x48U    /*Source Begin Address Active Register*/
#define SDL_RTDMA_O_SRC_ADDR_ACTIVE            0x4CU    /*Source Address Active Register*/
#define SDL_RTDMA_O_DST_BEG_ADDR_SHADOW        0x50U    /*Destination Begin Address Shadow Register*/
#define SDL_RTDMA_O_DST_ADDR_SHADOW            0x54U    /*Destination Address Shadow Register*/
#define SDL_RTDMA_O_DST_BEG_ADDR_ACTIVE        0x58U    /*Destination Begin Address Active Register*/
#define SDL_RTDMA_O_DST_ADDR_ACTIVE            0x5CU    /*Destination Address Active Register*/
#define SDL_RTDMA_O_CHSECLAT1                  0x80U    /*Channel Security Details Latch Register*/
#define SDL_RTDMA_O_CHSECLAT2                  0x84U    /*Channel Security Details Latch Register*/
#define SDL_RTDMA_O_BURST_INTF_CTRL            0xA0U    /*Burst Interface Control Register*/
#define SDL_RTDMA_O_CHCFG_LOCK                 0x100U   /*Channel Configuration Temporary Lock*/
#define SDL_RTDMA_O_CHCFG_COMMIT               0x104U   /*Channel Configuration Permanent Commit*/

#define SDL_RTDMA_O_FLTEMU_CONFIG              0x0U     /*Fault emulation configuration registerr*/
#define SDL_RTDMA_O_FLTEMU_ACCGRPSEL           0x4U     /*Fault emulation access information group selection register*/
#define SDL_RTDMA_O_FLTEMU_BITSEL              0x8U     /*Fault emulation bitsel*/
#define SDL_RTDMA_O_FLTEMU_ADDR                0xCU     /*Fault emulation access address register*/

#define SDL_RTDMA_O_SELFTEST_DIAG_DATA0        0x0U    /*Diagnostics data register 0*/
#define SDL_RTDMA_O_SELFTEST_DIAG_DATA1        0x4U    /*Diagnostics data register 1*/
#define SDL_RTDMA_O_SELFTEST_DIAG_DATA2        0x8U    /*Diagnostics data register 2*/
#define SDL_RTDMA_O_SELFTEST_DIAG_ECC          0x20U   /*Diagnostics ECC*/
#define SDL_RTDMA_O_SELFTEST_DIAG_CONTROL      0x28U   /*Diagnostic test enable*/
#define SDL_RTDMA_O_SELFTEST_DIAG_STATUS       0x2CU   /*Diagnostic status register*/
#define SDL_RTDMA_O_SELFTEST_DIAG_STATUS_CLR   0x30U   /*Diagnostic status clear register*/

/***************************************************************************************************
 *
 * The following are defines for the bit fields in the MEM_ECC_DIAG register
 *
 ***************************************************************************************************/

#define SDL_PIPE_MEM_ECC_DIAG_MEM_SIC_DIAG_EN   0x2U      /*Memory safe interconnect diagnostics enable*/

#define SDL_PIPE_O_MEM_ECC_DIAG                 0x40U     /*ECC configuration and diagnostics register*/

/***************************************************************************************************
 *
 * The following are defines for the PIPE register offsets
 *
 ***************************************************************************************************/

#define SDL_PIPE_O_INT_VECT_ADDR(i)    (0x5000U + ((i) * 0x4U))   /*(0 <= i < 256) Interrupt vector address*/

#endif /*SDLR_SIC_H_*/