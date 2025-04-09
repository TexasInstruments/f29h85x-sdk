//###########################################################################
//
// FILE:   clock_config.h
//
// TITLE:  C29x system control driver (Clock Configurations).
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

#ifndef CLOCK_H
#define CLOCK_H

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
//! \addtogroup clock_api Clocks
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "cpu.h"
#include "debug.h"

//
// Default internal oscillator frequency, 10 MHz
//
#define SYSCTL_DEFAULT_OSC_FREQ     10000000U

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e oscSrc parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_OSCSRC_OSC2      = 0x00,    // Internal Oscillator 2
    SYSCTL_OSCSRC_XTAL      = 0x01,    // External XTAL
    SYSCTL_OSCSRC_XTAL_SE   = 0x11,    // External XTAL Single-ended mode
    SYSCTL_OSCSRC_OSC1      = 0x02     // Internal Oscillator 1
} Sysctl_PLLClockSource;

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e pllConfig parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PLL_ENABLE,
    SYSCTL_PLL_DISABLE,
    SYSCTL_PLL_BYPASS,
} Sysctl_PLLConfig;

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e refdiv parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_REFDIV_1,
    SYSCTL_REFDIV_2,
    SYSCTL_REFDIV_3,
    SYSCTL_REFDIV_4,
    SYSCTL_REFDIV_5,
    SYSCTL_REFDIV_6,
    SYSCTL_REFDIV_7,
    SYSCTL_REFDIV_8,
    SYSCTL_REFDIV_9,
    SYSCTL_REFDIV_10,
    SYSCTL_REFDIV_11,
    SYSCTL_REFDIV_12,
    SYSCTL_REFDIV_13,
    SYSCTL_REFDIV_14,
    SYSCTL_REFDIV_15,
    SYSCTL_REFDIV_16,
    SYSCTL_REFDIV_17,
    SYSCTL_REFDIV_18,
    SYSCTL_REFDIV_19,
    SYSCTL_REFDIV_20,
    SYSCTL_REFDIV_21,
    SYSCTL_REFDIV_22,
    SYSCTL_REFDIV_23,
    SYSCTL_REFDIV_24,
    SYSCTL_REFDIV_25,
    SYSCTL_REFDIV_26,
    SYSCTL_REFDIV_27,
    SYSCTL_REFDIV_28,
    SYSCTL_REFDIV_29,
    SYSCTL_REFDIV_30,
    SYSCTL_REFDIV_31,
    SYSCTL_REFDIV_32,
} Sysctl_PLLRefDiv;

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e imult parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_IMULT_4 = 4,
    SYSCTL_IMULT_5,
    SYSCTL_IMULT_6,
    SYSCTL_IMULT_7,
    SYSCTL_IMULT_8,
    SYSCTL_IMULT_9,
    SYSCTL_IMULT_10,
    SYSCTL_IMULT_11,
    SYSCTL_IMULT_12,
    SYSCTL_IMULT_13,
    SYSCTL_IMULT_14,
    SYSCTL_IMULT_15,
    SYSCTL_IMULT_16,
    SYSCTL_IMULT_17,
    SYSCTL_IMULT_18,
    SYSCTL_IMULT_19,
    SYSCTL_IMULT_20,
    SYSCTL_IMULT_21,
    SYSCTL_IMULT_22,
    SYSCTL_IMULT_23,
    SYSCTL_IMULT_24,
    SYSCTL_IMULT_25,
    SYSCTL_IMULT_26,
    SYSCTL_IMULT_27,
    SYSCTL_IMULT_28,
    SYSCTL_IMULT_29,
    SYSCTL_IMULT_30,
    SYSCTL_IMULT_31,
    SYSCTL_IMULT_32,
    SYSCTL_IMULT_33,
    SYSCTL_IMULT_34,
    SYSCTL_IMULT_35,
    SYSCTL_IMULT_36,
    SYSCTL_IMULT_37,
    SYSCTL_IMULT_38,
    SYSCTL_IMULT_39,
    SYSCTL_IMULT_40,
    SYSCTL_IMULT_41,
    SYSCTL_IMULT_42,
    SYSCTL_IMULT_43,
    SYSCTL_IMULT_44,
    SYSCTL_IMULT_45,
    SYSCTL_IMULT_46,
    SYSCTL_IMULT_47,
    SYSCTL_IMULT_48,
    SYSCTL_IMULT_49,
    SYSCTL_IMULT_50,
    SYSCTL_IMULT_51,
    SYSCTL_IMULT_52,
    SYSCTL_IMULT_53,
    SYSCTL_IMULT_54,
    SYSCTL_IMULT_55,
    SYSCTL_IMULT_56,
    SYSCTL_IMULT_57,
    SYSCTL_IMULT_58,
    SYSCTL_IMULT_59,
    SYSCTL_IMULT_60,
    SYSCTL_IMULT_61,
    SYSCTL_IMULT_62,
    SYSCTL_IMULT_63,
    SYSCTL_IMULT_64,
    SYSCTL_IMULT_65,
    SYSCTL_IMULT_66,
    SYSCTL_IMULT_67,
    SYSCTL_IMULT_68,
    SYSCTL_IMULT_69,
    SYSCTL_IMULT_70,
    SYSCTL_IMULT_71,
    SYSCTL_IMULT_72,
    SYSCTL_IMULT_73,
    SYSCTL_IMULT_74,
    SYSCTL_IMULT_75,
    SYSCTL_IMULT_76,
    SYSCTL_IMULT_77,
    SYSCTL_IMULT_78,
    SYSCTL_IMULT_79,
    SYSCTL_IMULT_80,
    SYSCTL_IMULT_81,
    SYSCTL_IMULT_82,
    SYSCTL_IMULT_83,
    SYSCTL_IMULT_84,
    SYSCTL_IMULT_85,
    SYSCTL_IMULT_86,
    SYSCTL_IMULT_87,
    SYSCTL_IMULT_88,
    SYSCTL_IMULT_89,
    SYSCTL_IMULT_90,
    SYSCTL_IMULT_91,
    SYSCTL_IMULT_92,
    SYSCTL_IMULT_93,
    SYSCTL_IMULT_94,
    SYSCTL_IMULT_95,
    SYSCTL_IMULT_96,
    SYSCTL_IMULT_97,
    SYSCTL_IMULT_98,
    SYSCTL_IMULT_99,
    SYSCTL_IMULT_100,
    SYSCTL_IMULT_101,
    SYSCTL_IMULT_102,
    SYSCTL_IMULT_103,
    SYSCTL_IMULT_104,
    SYSCTL_IMULT_105,
    SYSCTL_IMULT_106,
    SYSCTL_IMULT_107,
    SYSCTL_IMULT_108,
    SYSCTL_IMULT_109,
    SYSCTL_IMULT_110,
    SYSCTL_IMULT_111,
    SYSCTL_IMULT_112,
    SYSCTL_IMULT_113,
    SYSCTL_IMULT_114,
    SYSCTL_IMULT_115,
    SYSCTL_IMULT_116,
    SYSCTL_IMULT_117,
    SYSCTL_IMULT_118,
    SYSCTL_IMULT_119,
    SYSCTL_IMULT_120,
    SYSCTL_IMULT_121,
    SYSCTL_IMULT_122,
    SYSCTL_IMULT_123,
    SYSCTL_IMULT_124,
    SYSCTL_IMULT_125,
    SYSCTL_IMULT_126,
    SYSCTL_IMULT_127,
    SYSCTL_IMULT_128,
    SYSCTL_IMULT_129,
    SYSCTL_IMULT_130,
    SYSCTL_IMULT_131,
    SYSCTL_IMULT_132,
    SYSCTL_IMULT_133,
    SYSCTL_IMULT_134,
    SYSCTL_IMULT_135,
    SYSCTL_IMULT_136,
    SYSCTL_IMULT_137,
    SYSCTL_IMULT_138,
    SYSCTL_IMULT_139,
    SYSCTL_IMULT_140,
    SYSCTL_IMULT_141,
    SYSCTL_IMULT_142,
    SYSCTL_IMULT_143,
    SYSCTL_IMULT_144,
    SYSCTL_IMULT_145,
    SYSCTL_IMULT_146,
    SYSCTL_IMULT_147,
    SYSCTL_IMULT_148,
    SYSCTL_IMULT_149,
    SYSCTL_IMULT_150,
    SYSCTL_IMULT_151,
    SYSCTL_IMULT_152,
    SYSCTL_IMULT_153,
    SYSCTL_IMULT_154,
    SYSCTL_IMULT_155,
    SYSCTL_IMULT_156,
    SYSCTL_IMULT_157,
    SYSCTL_IMULT_158,
    SYSCTL_IMULT_159,
    SYSCTL_IMULT_160,
    SYSCTL_IMULT_161,
    SYSCTL_IMULT_162,
    SYSCTL_IMULT_163,
    SYSCTL_IMULT_164,
    SYSCTL_IMULT_165,
    SYSCTL_IMULT_166,
    SYSCTL_IMULT_167,
    SYSCTL_IMULT_168,
    SYSCTL_IMULT_169,
    SYSCTL_IMULT_170,
    SYSCTL_IMULT_171,
    SYSCTL_IMULT_172,
    SYSCTL_IMULT_173,
    SYSCTL_IMULT_174,
    SYSCTL_IMULT_175,
    SYSCTL_IMULT_176,
    SYSCTL_IMULT_177,
    SYSCTL_IMULT_178,
    SYSCTL_IMULT_179,
    SYSCTL_IMULT_180,
    SYSCTL_IMULT_181,
    SYSCTL_IMULT_182,
    SYSCTL_IMULT_183,
    SYSCTL_IMULT_184,
    SYSCTL_IMULT_185,
    SYSCTL_IMULT_186,
    SYSCTL_IMULT_187,
    SYSCTL_IMULT_188,
    SYSCTL_IMULT_189,
    SYSCTL_IMULT_190,
    SYSCTL_IMULT_191,
    SYSCTL_IMULT_192,
    SYSCTL_IMULT_193,
    SYSCTL_IMULT_194,
    SYSCTL_IMULT_195,
    SYSCTL_IMULT_196,
    SYSCTL_IMULT_197,
    SYSCTL_IMULT_198,
    SYSCTL_IMULT_199,
    SYSCTL_IMULT_200,
    SYSCTL_IMULT_201,
    SYSCTL_IMULT_202,
    SYSCTL_IMULT_203,
    SYSCTL_IMULT_204,
    SYSCTL_IMULT_205,
    SYSCTL_IMULT_206,
    SYSCTL_IMULT_207,
    SYSCTL_IMULT_208,
    SYSCTL_IMULT_209,
    SYSCTL_IMULT_210,
    SYSCTL_IMULT_211,
    SYSCTL_IMULT_212,
    SYSCTL_IMULT_213,
    SYSCTL_IMULT_214,
    SYSCTL_IMULT_215,
    SYSCTL_IMULT_216,
    SYSCTL_IMULT_217,
    SYSCTL_IMULT_218,
    SYSCTL_IMULT_219,
    SYSCTL_IMULT_220,
    SYSCTL_IMULT_221,
    SYSCTL_IMULT_222,
    SYSCTL_IMULT_223,
    SYSCTL_IMULT_224,
    SYSCTL_IMULT_225,
    SYSCTL_IMULT_226,
    SYSCTL_IMULT_227,
    SYSCTL_IMULT_228,
    SYSCTL_IMULT_229,
    SYSCTL_IMULT_230,
    SYSCTL_IMULT_231,
    SYSCTL_IMULT_232,
    SYSCTL_IMULT_233,
    SYSCTL_IMULT_234,
    SYSCTL_IMULT_235,
    SYSCTL_IMULT_236,
    SYSCTL_IMULT_237,
    SYSCTL_IMULT_238,
    SYSCTL_IMULT_239,
    SYSCTL_IMULT_240,
    SYSCTL_IMULT_241,
    SYSCTL_IMULT_242,
    SYSCTL_IMULT_243,
    SYSCTL_IMULT_244,
    SYSCTL_IMULT_245,
    SYSCTL_IMULT_246,
    SYSCTL_IMULT_247,
    SYSCTL_IMULT_248,
    SYSCTL_IMULT_249,
    SYSCTL_IMULT_250,
    SYSCTL_IMULT_251,
    SYSCTL_IMULT_252,
    SYSCTL_IMULT_253,
    SYSCTL_IMULT_254,
    SYSCTL_IMULT_255,
} Sysctl_PLLIMult;


//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e odiv parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_ODIV_1,
    SYSCTL_ODIV_2,
    SYSCTL_ODIV_3,
    SYSCTL_ODIV_4,
    SYSCTL_ODIV_5,
    SYSCTL_ODIV_6,
    SYSCTL_ODIV_7,
    SYSCTL_ODIV_8,
    SYSCTL_ODIV_9,
    SYSCTL_ODIV_10,
    SYSCTL_ODIV_11,
    SYSCTL_ODIV_12,
    SYSCTL_ODIV_13,
    SYSCTL_ODIV_14,
    SYSCTL_ODIV_15,
    SYSCTL_ODIV_16,
    SYSCTL_ODIV_17,
    SYSCTL_ODIV_18,
    SYSCTL_ODIV_19,
    SYSCTL_ODIV_20,
    SYSCTL_ODIV_21,
    SYSCTL_ODIV_22,
    SYSCTL_ODIV_23,
    SYSCTL_ODIV_24,
    SYSCTL_ODIV_25,
    SYSCTL_ODIV_26,
    SYSCTL_ODIV_27,
    SYSCTL_ODIV_28,
    SYSCTL_ODIV_29,
    SYSCTL_ODIV_30,
    SYSCTL_ODIV_31,
    SYSCTL_ODIV_32,
} Sysctl_PLLODiv;

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e sysdiv parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_SYSDIV_1,
    SYSCTL_SYSDIV_2,
    SYSCTL_SYSDIV_3,
    SYSCTL_SYSDIV_4,
    SYSCTL_SYSDIV_5,
    SYSCTL_SYSDIV_6,
    SYSCTL_SYSDIV_7,
    SYSCTL_SYSDIV_8,
    SYSCTL_SYSDIV_9,
    SYSCTL_SYSDIV_10,
    SYSCTL_SYSDIV_11,
    SYSCTL_SYSDIV_12,
    SYSCTL_SYSDIV_13,
    SYSCTL_SYSDIV_14,
    SYSCTL_SYSDIV_15,
    SYSCTL_SYSDIV_16,
    SYSCTL_SYSDIV_17,
    SYSCTL_SYSDIV_18,
    SYSCTL_SYSDIV_19,
    SYSCTL_SYSDIV_20,
    SYSCTL_SYSDIV_21,
    SYSCTL_SYSDIV_22,
    SYSCTL_SYSDIV_23,
    SYSCTL_SYSDIV_24,
    SYSCTL_SYSDIV_25,
    SYSCTL_SYSDIV_26,
    SYSCTL_SYSDIV_27,
    SYSCTL_SYSDIV_28,
    SYSCTL_SYSDIV_29,
    SYSCTL_SYSDIV_30,
    SYSCTL_SYSDIV_31,
    SYSCTL_SYSDIV_32,
    SYSCTL_SYSDIV_33,
    SYSCTL_SYSDIV_34,
    SYSCTL_SYSDIV_35,
    SYSCTL_SYSDIV_36,
    SYSCTL_SYSDIV_37,
    SYSCTL_SYSDIV_38,
    SYSCTL_SYSDIV_39,
    SYSCTL_SYSDIV_40,
    SYSCTL_SYSDIV_41,
    SYSCTL_SYSDIV_42,
    SYSCTL_SYSDIV_43,
    SYSCTL_SYSDIV_44,
    SYSCTL_SYSDIV_45,
    SYSCTL_SYSDIV_46,
    SYSCTL_SYSDIV_47,
    SYSCTL_SYSDIV_48,
    SYSCTL_SYSDIV_49,
    SYSCTL_SYSDIV_50,
    SYSCTL_SYSDIV_51,
    SYSCTL_SYSDIV_52,
    SYSCTL_SYSDIV_53,
    SYSCTL_SYSDIV_54,
    SYSCTL_SYSDIV_55,
    SYSCTL_SYSDIV_56,
    SYSCTL_SYSDIV_57,
    SYSCTL_SYSDIV_58,
    SYSCTL_SYSDIV_59,
    SYSCTL_SYSDIV_60,
    SYSCTL_SYSDIV_61,
    SYSCTL_SYSDIV_62,
    SYSCTL_SYSDIV_63,
    SYSCTL_SYSDIV_64,
} Sysctl_PLLSysDiv;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_selectClockOutSource() as the \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XCLKOUT_SOURCE_PLLSYS     = 0U,   //!< PLL System Clock post SYSCLKDIV
    SYSCTL_XCLKOUT_SOURCE_CPU1CLK    = 1U,   //!< CPU1.CLOCK
    SYSCTL_XCLKOUT_SOURCE_CPU2CLK    = 2U,   //!< CPU2.CLOCK
    SYSCTL_XCLKOUT_SOURCE_CPU3CLK    = 3U,   //!< CPU3.CLOCK
    SYSCTL_XCLKOUT_SOURCE_INTOSC1    = 5U,   //!< Internal Oscillator 1
    SYSCTL_XCLKOUT_SOURCE_INTOSC2    = 6U,   //!< Internal Oscillator 2
    SYSCTL_XCLKOUT_SOURCE_XTALOSC    = 7U,   //!< External Oscillator
} SysCtl_XClkSource;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setXClk() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XCLKOUT_DIV_1  = 0,      //!<  XCLKOUT =  XCLKOUT source / 1
    SYSCTL_XCLKOUT_DIV_2  = 1,      //!<  XCLKOUT =  XCLKOUT source / 2
    SYSCTL_XCLKOUT_DIV_4  = 2,      //!<  XCLKOUT =  XCLKOUT source / 4
    SYSCTL_XCLKOUT_DIV_8  = 3       //!<  XCLKOUT =  XCLKOUT source / 8
}SysCtl_XClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setMCANClock() as \e mcanInst parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_MCAN_A,
    SYSCTL_MCAN_B,
    SYSCTL_MCAN_C,
    SYSCTL_MCAN_D,
    SYSCTL_MCAN_E,
    SYSCTL_MCAN_F
}SysCtl_MCANInstance;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setMCANClock() as \e clksrc parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_MCANCLK_SOURCE_SYS       = 0x0, //! Peripheral System Clock Source
    SYSCTL_MCANCLK_SOURCE_AUXIN     = 0x2, //! Auxiliary Clock Input Source (GPIO)
    SYSCTL_MCANCLK_SOURCE_PLLRAW    = 0x3  //! PLL Raw Clock Source
}SysCtl_MCANClkSource;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setMCANClock() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_MCANCLK_DIV_1  = 0x0,   //!<  MCAN clock =  MCAN clock source / 1
    SYSCTL_MCANCLK_DIV_2  = 0x1,   //!<  MCAN clock =  MCAN clock source / 2
    SYSCTL_MCANCLK_DIV_3  = 0x2,   //!<  MCAN clock =  MCAN clock source / 3
    SYSCTL_MCANCLK_DIV_4  = 0x3,   //!<  MCAN clock =  MCAN clock source / 4
    SYSCTL_MCANCLK_DIV_5  = 0x4,   //!<  MCAN clock =  MCAN clock source / 5
    SYSCTL_MCANCLK_DIV_6  = 0x5,   //!<  MCAN clock =  MCAN clock source / 6
    SYSCTL_MCANCLK_DIV_7  = 0x6,   //!<  MCAN clock =  MCAN clock source / 7
    SYSCTL_MCANCLK_DIV_8  = 0x7,   //!<  MCAN clock =  MCAN clock source / 8
    SYSCTL_MCANCLK_DIV_9  = 0x8,   //!<  MCAN clock =  MCAN clock source / 9
    SYSCTL_MCANCLK_DIV_10 = 0x9,   //!<  MCAN clock =  MCAN clock source / 10
    SYSCTL_MCANCLK_DIV_11 = 0xA,   //!<  MCAN clock =  MCAN clock source / 11
    SYSCTL_MCANCLK_DIV_12 = 0xB,   //!<  MCAN clock =  MCAN clock source / 12
    SYSCTL_MCANCLK_DIV_13 = 0xC,   //!<  MCAN clock =  MCAN clock source / 13
    SYSCTL_MCANCLK_DIV_14 = 0xD,   //!<  MCAN clock =  MCAN clock source / 14
    SYSCTL_MCANCLK_DIV_15 = 0xE,   //!<  MCAN clock =  MCAN clock source / 15
    SYSCTL_MCANCLK_DIV_16 = 0xF,   //!<  MCAN clock =  MCAN clock source / 16
    SYSCTL_MCANCLK_DIV_17 = 0x10,  //!<  MCAN clock =  MCAN clock source / 17
    SYSCTL_MCANCLK_DIV_18 = 0x11,  //!<  MCAN clock =  MCAN clock source / 18
    SYSCTL_MCANCLK_DIV_19 = 0x12,  //!<  MCAN clock =  MCAN clock source / 19
    SYSCTL_MCANCLK_DIV_20 = 0x13   //!<  MCAN clock =  MCAN clock source / 20
}SysCtl_MCANClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setCputimer2Clock()
//! as \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_TIMER2CLK_SOURCE_SYSCLK   = 0U,   //!< System Clock
    SYSCTL_TIMER2CLK_SOURCE_INTOSC1  = 1U,   //!< Internal Oscillator 1
    SYSCTL_TIMER2CLK_SOURCE_INTOSC2  = 2U,   //!< Internal Oscillator 2
    SYSCTL_TIMER2CLK_SOURCE_XTAL     = 3U,   //!< Crystal oscillator
}SysCtl_Cputimer2ClkSource;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setCputimer2Clk() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_TIMER2CLK_DIV_1  = 0,  //!<  Cputimer2 clock =  Cputimer2 clock / 1
    SYSCTL_TIMER2CLK_DIV_2  = 1,  //!<  Cputimer2 clock =  Cputimer2 clock / 2
    SYSCTL_TIMER2CLK_DIV_4  = 2,  //!<  Cputimer2 clock =  Cputimer2 clock / 4
    SYSCTL_TIMER2CLK_DIV_8  = 3,  //!<  Cputimer2 clock =  Cputimer2 clock / 8
    SYSCTL_TIMER2CLK_DIV_16 = 4   //!<  Cputimer2 clock =  Cputimer2 clock / 16
}SysCtl_Cputimer2ClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setEPWMClockDivider()
//! as the \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_EPWMCLK_DIV_1,           //!< EPWMCLK = PLLSYSCLK / 1
    SYSCTL_EPWMCLK_DIV_2            //!< EPWMCLK = PLLSYSCLK / 2
} SysCtl_EPWMClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setEMIF1Clock() as the \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_EMIFCLK_DIV_1,         //!< EMIF1CLK = PLLSYSCLK / 1
    SYSCTL_EMIFCLK_DIV_2,         //!< EMIF1CLK = PLLSYSCLK / 2
    SYSCTL_EMIFCLK_DIV_4          //!< EMIF1CLK = PLLSYSCLK / 4
} SysCtl_EMIFClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setLINAClockDivider()
//! as the \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_LINCLK_DIV_1,           //!< LINACLK = PLLSYSCLK / 1
    SYSCTL_LINCLK_DIV_2,           //!< LINACLK = PLLSYSCLK / 2
    SYSCTL_LINCLK_DIV_4            //!< LINACLK = PLLSYSCLK / 4
} SysCtl_LINClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setECatClock() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_ECATCLKOUT_DIV_1,      //!<  ECat clock =  PLLCLK / 1
    SYSCTL_ECATCLKOUT_DIV_2,      //!<  ECat clock =  PLLCLK / 2
    SYSCTL_ECATCLKOUT_DIV_3,      //!<  ECat clock =  PLLCLK / 3
    SYSCTL_ECATCLKOUT_DIV_4,      //!<  ECat clock =  PLLCLK / 4
    SYSCTL_ECATCLKOUT_DIV_5,      //!<  ECat clock =  PLLCLK / 5
    SYSCTL_ECATCLKOUT_DIV_6,      //!<  ECat clock =  PLLCLK / 6
    SYSCTL_ECATCLKOUT_DIV_7,      //!<  ECat clock =  PLLCLK / 7
    SYSCTL_ECATCLKOUT_DIV_8       //!<  ECat clock =  PLLCLK / 8
}SysCtl_ECatClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setECatClock() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_ECAT_PHYCLK_ENABLE = SYSCTL_ETHERCATCLKCTL_PHYCLKEN,
    SYSCTL_ECAT_PHYCLK_DISABLE = 0U,
}SysCtl_ECatPhyClk;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setCLBClock() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CLBCLKOUT_DIV_1,      //!<  CLB clock =  CLB clock / 1
    SYSCTL_CLBCLKOUT_DIV_2,      //!<  CLB clock =  CLB clock / 2
    SYSCTL_CLBCLKOUT_DIV_3,      //!<  CLB clock =  CLB clock / 3
    SYSCTL_CLBCLKOUT_DIV_4,      //!<  CLB clock =  CLB clock / 4
    SYSCTL_CLBCLKOUT_DIV_5,      //!<  CLB clock =  CLB clock / 5
    SYSCTL_CLBCLKOUT_DIV_6,      //!<  CLB clock =  CLB clock / 6
    SYSCTL_CLBCLKOUT_DIV_7,      //!<  CLB clock =  CLB clock / 7
    SYSCTL_CLBCLKOUT_DIV_8       //!<  CLB clock =  CLB clock / 8
}SysCtl_CLBClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setCLBClock() as \e tdivider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CLBTCLKOUT_DIV_1,      //!<  CLBTCLKOUT =  CLB clock / 1
    SYSCTL_CLBTCLKOUT_DIV_2       //!<  CLBTCLKOUT =  CLB clock / 2
}SysCtl_CLBTClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setHSMClock() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_HSMCLK_DIV_1,      //!<  HSM Clock =  HSM clock / 1
    SYSCTL_HSMCLK_DIV_2,      //!<  HSM Clock =  HSM clock / 2
    SYSCTL_HSMCLK_DIV_4,      //!<  HSM Clock =  HSM clock / 4
    SYSCTL_HSMCLK_DIV_8,      //!<  HSM Clock =  HSM clock / 8
    SYSCTL_HSMCLK_DIV_16,     //!<  HSM Clock =  HSM clock / 16
}SysCtl_HSMClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setCLBClock() as \e cpuInst parameter.
//
//*****************************************************************************

#define SYSCTL_CLB1CLKMODE_SYNC  0U,
#define SYSCTL_CLB1CLKMODE_ASYNC SYSCTL_CLBCLKCTL_CLKMODECLB1,
#define SYSCTL_CLB2CLKMODE_SYNC  0U,
#define SYSCTL_CLB2CLKMODE_ASYNC SYSCTL_CLBCLKCTL_CLKMODECLB2,
#define SYSCTL_CLB3CLKMODE_SYNC  0U,
#define SYSCTL_CLB3CLKMODE_ASYNC SYSCTL_CLBCLKCTL_CLKMODECLB3,
#define SYSCTL_CLB4CLKMODE_SYNC  0U,
#define SYSCTL_CLB4CLKMODE_ASYNC SYSCTL_CLBCLKCTL_CLKMODECLB4,
#define SYSCTL_CLB5CLKMODE_SYNC  0U,
#define SYSCTL_CLB5CLKMODE_ASYNC SYSCTL_CLBCLKCTL_CLKMODECLB5,
#define SYSCTL_CLB6CLKMODE_SYNC  0U,
#define SYSCTL_CLB6CLKMODE_ASYNC SYSCTL_CLBCLKCTL_CLKMODECLB6

//
// Defined in sysctl.c
//
extern void SysCtl_pollSyncBusy(uint32_t mask);

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Enable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_enableMCD")))
__attribute__((always_inline))
static inline void
SysCtl_enableMCD(void)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_MCDCR) &= ~(SYSCTL_MCDCR_MCLKOFF);
}

//*****************************************************************************
//
//! Disable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_disableMCD")))
__attribute__((always_inline))
static inline void
SysCtl_disableMCD(void)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKOFF;
}

//*****************************************************************************
//
//! Get the missing clock detection Failure Status
//!
//! \note A failure means the oscillator clock is missing
//!
//! \return Returns \b true if a failure is detected or \b false if a
//! failure isn't detected
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_isMCDClockFailureDetected")))
__attribute__((always_inline))
static inline bool
SysCtl_isMCDClockFailureDetected(void)
{
    //
    //  Check the status bit to determine failure
    //
    return((HWREGH(DEVCFG_BASE + SYSCTL_O_MCDCR) & SYSCTL_MCDCR_MCLKSTS) != 0U);
}

//*****************************************************************************
//
//! Reset the missing clock detection logic after clock failure
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_resetMCD")))
__attribute__((always_inline))
static inline void
SysCtl_resetMCD(void)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKCLR;
}

//*****************************************************************************
//
//! Re-connect missing clock detection clock source to stop simulating clock
//! failure
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_connectMCDClockSource")))
__attribute__((always_inline))
static inline void
SysCtl_connectMCDClockSource(void)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_MCDCR) &= ~(SYSCTL_MCDCR_OSCOFF);
}

//*****************************************************************************
//
//! Disconnect missing clock detection clock source to simulate clock failure.
//! This is for testing the MCD functionality.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_disconnectMCDClockSource")))
__attribute__((always_inline))
static inline void
SysCtl_disconnectMCDClockSource(void)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_OSCOFF;
}

//*****************************************************************************
//
//! Sets up XCLK (External Clock out)
//!
//! \param clksrc   is the clock source to be used for the External Clock out
//! \param divider  is the clock divider to be used
//!
//! This function configures the specified clock source to be muxed to an
//! external clock out (XCLKOUT) GPIO pin.
//!
//! The \e clksrc arameter can have one enumerated value from
//! SysCtl_XClkSource
//! The \e divider parameter can have one enumerated value from
//! SysCtl_XClkDivider
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setXClk")))
__attribute__((always_inline))
static inline void
SysCtl_setXClk(SysCtl_XClkSource clksrc, SysCtl_XClkDivider divider)
{
    //
    // Configure the clock divider
    //
    HWREG(DEVCFG_BASE + SYSCTL_O_XCLKOUTDIVSEL) = divider;

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_XCLKOUTDIVSEL);

    //
    // Configure the clock source
    //
    HWREG(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL3) =
            (HWREG(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL3) &
             ~SYSCTL_CLKSRCCTL3_XCLKOUTSEL_M) |
            ((uint16_t)clksrc << SYSCTL_CLKSRCCTL3_XCLKOUTSEL_S);

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_CLKSRCCTL3);
}

//*****************************************************************************
//
//! Sets up MCAN Clock.
//!
//! \param mcanInst is the MCAN instance
//! \param clksrc   is the clock source to be used for the MCAN instance
//! \param divider  is the clock divider to be used
//!
//! This function sets up the MCANCLK divider. There is only one
//! divider that scales MCAN clock.
//!
//! The \e mcanInst parameter can have one enumerated value from
//! SysCtl_MCANInstance
//! The \e clksrc arameter can have one enumerated value from
//! SysCtl_MCANClkSource
//! The \e divider parameter can have one enumerated value from
//! SysCtl_MCANClkDivider
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setMCANClock")))
__attribute__((always_inline))
static inline void
SysCtl_setMCANClock(SysCtl_MCANInstance mcanInst, SysCtl_MCANClkSource clksrc,
                    SysCtl_MCANClkDivider divider)
{
    uint8_t bitpos;

    //
    // Configure the clock divider
    //
    bitpos = 5U * (uint8_t)mcanInst;
    HWREG(DEVCFG_BASE + SYSCTL_O_MCANCLKDIVSEL) =
            (HWREG(DEVCFG_BASE + SYSCTL_O_MCANCLKDIVSEL) &
             ~(SYSCTL_MCANCLKDIVSEL_MCANACLKDIV_M << bitpos)) |
            ((uint16_t)divider << bitpos);

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_MCANCLKDIVSEL);

    //
    // Configure the clock source
    //
    bitpos = SYSCTL_CLKSRCCTL2_MCANABCLKSEL_S + 2U * (uint8_t)mcanInst;
    HWREG(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL2) =
            (HWREG(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL2) & ~(0x3U << bitpos)) |
            ((uint16_t)clksrc << bitpos);

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_CLKSRCCTL2);
}

//*****************************************************************************
//
//! Sets up CPU Timer 2 Clock.
//!
//! \param divider is the value that configures the divider.
//! \param source is the source for the clock divider
//!
//! This function sets up the CPU Timer 2 CLK divider based on the source that
//! is selected. There is only one divider that scales the "source" to
//! CPU Timer 2 CLK.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_Cputimer2ClkDivider
//! The \e source parameter can have one enumerated value from
//! SysCtl_Cputimer2ClkSource
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setCputimer2Clock")))
__attribute__((always_inline))
static inline void
SysCtl_setCputimer2Clock(SysCtl_Cputimer2ClkSource source,
                         SysCtl_Cputimer2ClkDivider divider)
{
    HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) =
        (HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) &
            ~(SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_M |
              SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_M)) |
        ((uint16_t)divider << SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_S) |
        ((uint16_t)source << SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_S);
}

//*****************************************************************************
//
//! Sets the ePWM clock.
//!
//! \param divider is the value by which PLLSYSCLK is divided
//!
//! This function configures the clock rate of the EPWMCLK. The
//! \e divider parameter is the value by which the SYSCLK rate is divided to
//! get the EPWMCLK rate. For example, \b SYSCTL_EPWMCLK_DIV_2 will select an
//! EPWMCLK rate that is half the PLLSYSCLK rate.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setEPWMClock")))
__attribute__((always_inline))
static inline void
SysCtl_setEPWMClock(SysCtl_EPWMClkDivider divider)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_PERCLKDIVSEL) =
        (HWREGH(DEVCFG_BASE + SYSCTL_O_PERCLKDIVSEL) &
         ~SYSCTL_PERCLKDIVSEL_EPWMCLKDIV_M) | (uint16_t)divider;

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_PERCLKDIVSEL);
}

//*****************************************************************************
//
//! Sets the EMIF1 clock.
//!
//! \param divider is the value by which PLLSYSCLK (or CPU1.SYSCLK on a dual
//! core device) is divided
//!
//! This function configures the clock rate of the EMIF1CLK. The
//! \e divider parameter is the value by which the SYSCLK rate is divided to
//! get the EMIF1CLK rate.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setEMIF1Clock")))
__attribute__((always_inline))
static inline void
SysCtl_setEMIF1Clock(SysCtl_EMIFClkDivider divider)
{
    HWREG(DEVCFG_BASE + SYSCTL_O_PERCLKDIVSEL) =
            (HWREG(DEVCFG_BASE + SYSCTL_O_PERCLKDIVSEL) &
                ~SYSCTL_PERCLKDIVSEL_EMIF1CLKDIV_M) |
            ((uint32_t)divider << SYSCTL_PERCLKDIVSEL_EMIF1CLKDIV_S);

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_PERCLKDIVSEL);
}

//*****************************************************************************
//
//! Sets the LINA clock divider.
//!
//! \param divider is the value by which PLLSYSCLK is divided
//!
//! This function configures the clock rate of the LINACLK. The
//! \e divider parameter is the value by which the SYSCLK rate is divided to
//! get the LINACLK rate.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setLINAClock")))
__attribute__((always_inline))
static inline void
SysCtl_setLINAClock(SysCtl_LINClkDivider divider)
{
    HWREG(DEVCFG_BASE + SYSCTL_O_PERCLKDIVSEL) =
            (HWREG(DEVCFG_BASE + SYSCTL_O_PERCLKDIVSEL) &
                ~SYSCTL_PERCLKDIVSEL_LINACLKDIV_M) |
            ((uint32_t)divider << SYSCTL_PERCLKDIVSEL_LINACLKDIV_S);

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_PERCLKDIVSEL);
}

//*****************************************************************************
//
//! Sets the LINB clock.
//!
//! \param divider is the value by which PLLSYSCLK is divided
//!
//! This function configures the clock rate of the LINBCLK. The
//! \e divider parameter is the value by which the SYSCLK rate is divided to
//! get the LINBCLK rate.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setLINBClock")))
__attribute__((always_inline))
static inline void
SysCtl_setLINBClock(SysCtl_LINClkDivider divider)
{
    HWREG(DEVCFG_BASE + SYSCTL_O_PERCLKDIVSEL) =
            (HWREG(DEVCFG_BASE + SYSCTL_O_PERCLKDIVSEL) &
                ~SYSCTL_PERCLKDIVSEL_LINBCLKDIV_M) |
            ((uint32_t)divider << SYSCTL_PERCLKDIVSEL_LINBCLKDIV_S);

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_PERCLKDIVSEL);
}

//*****************************************************************************
//
//! Sets up Ethercat clock.
//!
//! \param divider is the value that configures the divider.
//! \param phyEnable enables/disables the etherCAT PHY clock
//!
//! This function sets up the Ethercat CLK divider based on the source that
//! is selected. There is only one divider that scales the "source" to
//! Ethercat CLK.
//! This also enables/disables the etherCAT PHY clock.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_ECatClkDivider
//! The \e source parameter can have one enumerated value from
//! SysCtl_PLLClockSource
//! The \e enable parameter can be either of these values:
//! 0x0U: etherCAT PHY clock is disabled
//! 0x1U: etherCAT PHY clock is enabled
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setECatClock")))
__attribute__((always_inline))
static inline void
SysCtl_setECatClock(SysCtl_ECatClkDivider divider, SysCtl_ECatPhyClk phyEnable)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_ETHERCATCLKCTL) =
            (HWREGH(DEVCFG_BASE + SYSCTL_O_ETHERCATCLKCTL) &
                ~(SYSCTL_ETHERCATCLKCTL_PHYCLKEN    |
                  SYSCTL_ETHERCATCLKCTL_ECATDIV_M)) |
            ((uint16_t)divider << SYSCTL_ETHERCATCLKCTL_ECATDIV_S) |
            (uint16_t)phyEnable;

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_ETHERCATCLKCTL);
}

//*****************************************************************************
//
//! Sets the CLB clock divider.
//!
//! \param divider  is the CLB clock divider.
//! \param tdivider is the CLB tile clock divider.
//! \param clkMode  is the mode for the clock for each of the instances
//!
//! This function sets up the CLB CLK configurations based on the instance
//! that is selected. There are 2 dividers that scales the "source" to CLB
//! CLK. The first one is the divider & the other the tile divider.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_CLBClkDivider
//! The \e tdivider parameter can have one enumerated value from
//! SysCtl_CLBTClkDivider
//! The \e clkMode parameter can be ORed value of :
//!  - SYSCTL_CLB1CLKMODE_SYNC or SYSCTL_CLB1CLKMODE_ASYNC
//!  - SYSCTL_CLB2CLKMODE_SYNC or SYSCTL_CLB2CLKMODE_ASYNC
//!  - SYSCTL_CLB3CLKMODE_SYNC or SYSCTL_CLB3CLKMODE_ASYNC
//!  - SYSCTL_CLB4CLKMODE_SYNC or SYSCTL_CLB4CLKMODE_ASYNC
//!  - SYSCTL_CLB5CLKMODE_SYNC or SYSCTL_CLB5CLKMODE_ASYNC
//!  - SYSCTL_CLB6CLKMODE_SYNC or SYSCTL_CLB6CLKMODE_ASYNC
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setCLBClock")))
__attribute__((always_inline))
static inline void
SysCtl_setCLBClock(SysCtl_CLBClkDivider divider, SysCtl_CLBTClkDivider tdivider,
                   uint8_t clkMode)
{
    HWREG(DEVCFG_BASE + SYSCTL_O_CLBCLKCTL) =
        ((uint32_t)divider << 0U) | ((uint32_t)tdivider << 4U) | clkMode;

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_CLKSRCCTL2);
}

//*****************************************************************************
//
//! Sets the HSM clock.
//!
//! \param divider is the value by which PLLSYSCLK is divided
//!
//! This function configures the clock rate of the HSMCLK. The
//! \e divider parameter is the value by which the SYSCLK rate is divided to
//! get the HSMCLK rate.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setHSMClock")))
__attribute__((always_inline))
static inline void
SysCtl_setHSMClock(SysCtl_HSMClkDivider divider)
{
    HWREG(DEVCFG_BASE + SYSCTL_O_HSMCLKDIVSEL) =
            (HWREG(DEVCFG_BASE + SYSCTL_O_HSMCLKDIVSEL) &
                ~SYSCTL_HSMCLKDIVSEL_HSMCLKDIV_M) |
            ((uint32_t)divider << SYSCTL_HSMCLKDIVSEL_HSMCLKDIV_S);
}

//*****************************************************************************
//
//! Gets the external oscillator counter value.
//!
//! This function returns the X1 clock counter value. When the return value
//! reaches 0x3FF, it freezes. Before switching from INTOSC2 to an external
//! oscillator (XTAL), an application should call this function to make sure
//! the counter is saturated.
//!
//! \return Returns the value of the 10-bit X1 clock counter.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_getExternalOscCounterValue")))
__attribute__((always_inline))
static inline uint16_t
SysCtl_getExternalOscCounterValue(void)
{
    return(HWREGH(DEVCFG_BASE + SYSCTL_O_X1CNT) & SYSCTL_X1CNT_X1CNT_M);
}

//*****************************************************************************
//
//! Clears the external oscillator counter value.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_clearExternalOscCounterValue")))
__attribute__((always_inline))
static inline void
SysCtl_clearExternalOscCounterValue(void)
{
    HWREG(DEVCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
}

//*****************************************************************************
//
//! Turns on the the XTAL oscillator.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_turnOnXTAL")))
__attribute__((always_inline))
static inline void
SysCtl_turnOnXTAL(void)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;
    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_XTALCR);
}

//*****************************************************************************
//
//! Turns off the the XTAL oscillator.
//!
//! \return None.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_turnOffXTAL")))
__attribute__((always_inline))
static inline void
SysCtl_turnOffXTAL(void)
{
    HWREGH(DEVCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_OSCOFF;
    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_XTALCR);
}

//*****************************************************************************
//
//! Calculates the system clock frequency (SYSCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the system clock based on the
//! frequency of the oscillator clock source (from \e clockInHz) and the PLL
//! and clock divider configuration registers.
//!
//! \return Returns the system clock frequency. If a missing clock is detected,
//! the function will return the INTOSC1 frequency. This needs to be
//! corrected and cleared (see SysCtl_resetMCD()) before trying to call this
//! function again.
//
//*****************************************************************************
extern uint32_t
SysCtl_getClock(uint32_t clockInHz);

//*****************************************************************************
//
//! Configures the clocking of the device.
//!
//! \param config is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! \param oscSrc PLL Source. Can be one of the following values :
//!     - \b SYSCTL_OSCSRC_OSC2      - Internal Oscillator 2
//!     - \b SYSCTL_OSCSRC_XTAL      - External XTAL
//!     - \b SYSCTL_OSCSRC_XTAL_SE   - External XTAL Single-ended mode
//!     - \b SYSCTL_OSCSRC_OSC1      - Internal Oscillator 1
//!
//! \param pllConfig PLL configuration. Can be one fo the following values :
//!     - \b SYSCTL_PLL_ENABLE - This is to Enable the PLL Clock to the System
//!     - \b SYSCTL_PLL_BYPASS - This is to Bypass the PLLCLK from the System,
//!        this will also power up the PLL if the user desires to power up the
//!        PLL but not use it for System.
//!     - \b SYSCTL_PLL_DISABLE - This is to Power Down the PLL and Bypass the
//!        PLLCLK to the System.
//!
//! \param refDiv Reference Clock Divider. Use Enum SYSCTL_REFDIV_1..32
//! \param iMult  Multiplier. Use Enum SYSCTL_IMULT_4..255
//! \param oDiv   Output Clock Divider. Use Enum SYSCTL_ODIV_1..32
//! \param sysDiv SYSCLK Divider. Use Enum SYSCTL_SYSDIV_1..64
//! \param dccBase Base address of DCC module for PLL output validation
//!
//! This function uses the DCC to check that the PLLRAWCLK is running at the
//! expected rate. If you are using the DCC, you must back up its configuration
//! before calling this function and restore it afterward.
//! Locking PLL sequence is only done if the multipliers are updated.
//!
//! \note See your device errata for more details about locking the PLL.
//!
//! \return Returns \b false if a missing clock error is detected. This needs
//! to be cleared (see SysCtl_resetMCD()) before trying to call this function
//! again. Also, returns \b false if the PLLRAWCLK is not running at its
//! expected rate. Otherwise, returns \b true.
//
//*****************************************************************************
__attribute__((section(".text.link2.SysCtl_setClock")))
extern bool
SysCtl_setClock(Sysctl_PLLClockSource oscSrc, Sysctl_PLLConfig pllConfig,
                Sysctl_PLLRefDiv refDiv, Sysctl_PLLIMult iMult,
                Sysctl_PLLODiv oDiv, Sysctl_PLLSysDiv sysDiv, uint32_t dccBase);


//*****************************************************************************
//
//! Selects the oscillator to be used for the clocking of the device.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function configures the oscillator to be used in the clocking of the
//! device. The \e oscSource parameter may take a value of
//! \b SYSCTL_OSCSRC_OSC2, \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE, or
//! \b SYSCTL_OSCSRC_OSC1.
//!
//! \sa SysCtl_turnOnOsc()
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectOscSource(uint32_t oscSource);


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // CLOCK_H
