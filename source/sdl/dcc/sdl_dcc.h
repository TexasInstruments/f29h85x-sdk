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

/**
 *  \addtogroup sdl_dcc_group
 *
 *  @{
 */

#ifndef SDL_DCC_H_
#define SDL_DCC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include "sdlr_dcc.h"
#include <include/hw_types.h>
#include <include/sdl_types.h>
#include <include/sdlr_baseaddress.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  Macro defines maximum value of count for clock source 0.
 */
#define DCC_SRC0_COUNT_MAX      (0xFFFFFU)
/**
 * \brief  Macro defines maximum value of valid count for clock source 0.
 */
#define DCC_SRC0_VALID_MAX      (0x0FFFFU)
/**
 * \brief  Macro defines maximum value of count for clock source 1.
 */
#define DCC_SRC1_COUNT_MAX      (0xFFFFFU)

#define DCC_SRC0_VALID_MIN       (4u)

/**
 *  \anchor SDL_DCC_Mode
 *  \name DCC Operation Mode
 *  @{
 */
/**
 * \brief  Enum to select the DCC Operation Mode.
 *
 *         DCC can either operate in single shot or continuous mode.
 */
typedef uint32_t SDL_DCC_Mode;

#define SDL_DCC_MODE_SINGLE_SHOT     (DCC_DCCGCTRL_SINGLESHOT_MODE)
/**< Stop counting when counter0 and valid0 both reach zero */

/**< Stop counting when counter1 reaches zero */
#define SDL_DCC_MODE_CONTINUOUS        (DCC_DCCGCTRL_SINGLESHOT_DISABLE)
/**< Continuously repeat (until error) */
/** @} */

/**
 *  \anchor SDL_DCC_IntrType
 *  \name DCC Interrupt type
 *  @{
 */
/**
 * \brief  Enum for DCC interrupts.
 */
typedef uint32_t SDL_DCC_IntrType;

#define SDL_DCC_INTERRUPT_ERR              (0x0U)
/**< The error signal */
#define SDL_DCC_INTERRUPT_DONE             (0x1U)
/**< Done interrupt signal */
/** @} */

/**
 * \brief  Enum to select the COUNT0 clock source.
 */
typedef enum
{
    SDL_DCC_COUNT0SRC_XTAL               = 0x0U,  /**< Crystal Oscillator output */
    SDL_DCC_COUNT0SRC_INTOSC1            = 0x1U,  /**< Internal Oscillator1 output */
    SDL_DCC_COUNT0SRC_INTOSC2            = 0x2U,  /**< Internal Oscillator2 output */
    SDL_DCC_COUNT0SRC_TCK                = 0x4U,  /**< TCK pin input */
    SDL_DCC_COUNT0SRC_CPU1_CLOCK         = 0x5U,  /**< CPU1 Clock */
    SDL_DCC_COUNT0SRC_AUXCLKIN           = 0x8U,  /**< Auxiliary Clock input */
    SDL_DCC_COUNT0SRC_INPUTXBAR1_INPUT16 = 0xCU,  /**< Input 16 of INPUTXBAR */
} SDL_DCC_Count0ClockSource;

/**
 * \brief  Enum to select the COUNT1 clock source.
 */
typedef enum
{
    SDL_DCC_COUNT1SRC_PLL                 = 0x0U,  /**< Direct output of SYSPLL CLKOUT */
    SDL_DCC_COUNT1SRC_FLC1_FCLK           = 0x1U,  /**< FCLK (divided clock) output from Flash Controller 1 */
    SDL_DCC_COUNT1SRC_INTOSC1             = 0x2U,  /**< Internal Oscillator1 Output Clock */
    SDL_DCC_COUNT1SRC_INTOSC2             = 0x3U,  /**< Internal Oscillator2 Output Clock */
    SDL_DCC_COUNT1SRC_ECATPHYCLK          = 0x5U,  /**< Ethercat PHY Clock */
    SDL_DCC_COUNT1SRC_CPU1_CLOCK          = 0x6U,  /**< CPU1 Clock */
    SDL_DCC_COUNT1SRC_CPU2_CLOCK          = 0x7U,  /**< CPU2 Clock */
    SDL_DCC_COUNT1SRC_RTDMA_CLOCK         = 0x8U,  /**< RTDMA Clock */
    SDL_DCC_COUNT1SRC_INPUTXBAR1_INPUT15  = 0x9U,  /**< Input 15 of INPUTXBAR1 */
    SDL_DCC_COUNT1SRC_AUXCLKIN            = 0xAU,  /**< Auxiliary Clock input */
    SDL_DCC_COUNT1SRC_EPWMCLK             = 0xBU,  /**< Clock input to EPWM module */
    SDL_DCC_COUNT1SRC_ADCCLK              = 0xDU,  /**< ADC conversion clock */
    SDL_DCC_COUNT1SRC_WDCLK               = 0xEU,  /**< Watchdog clock after dividers */
    SDL_DCC_COUNT1SRC_FLC2_FCLK           = 0xFU,  /**< FCLK (divided clock) output!< from Flash Controller 2 */
    SDL_DCC_COUNT1SRC_CPU3_CLOCK          = 0x15U, /**< CPU3 Clock */
    SDL_DCC_COUNT1SRC_INPUTXBAR1_INPUT11  = 0x18U, /**< Input 11 of INPUTXBAR */
    SDL_DCC_COUNT1SRC_INPUTXBAR1_INPUT12  = 0x19U, /**< Input 12 of INPUTXBAR */
    SDL_DCC_COUNT1SRC_MCANA               = 0x1AU, /**< MCANA Bit Clock */
    SDL_DCC_COUNT1SRC_MCANB               = 0x1BU, /**< MCANB Bit Clock */
    SDL_DCC_COUNT1SRC_MCANC               = 0x1CU, /**< MCANC Bit Clock */
    SDL_DCC_COUNT1SRC_MCAND               = 0x1DU, /**< MCAND Bit Clock */
    SDL_DCC_COUNT1SRC_MCANE               = 0x1EU, /**< MCANE Bit Clock */
    SDL_DCC_COUNT1SRC_MCANF               = 0x1FU, /**< MCANF Bit Clock */
    SDL_DCC_COUNT1SRC_ESMCLK              = 0x20U, /**< ESM Clock */
} SDL_DCC_Count1ClockSource;

/* ========================================================================== */
/*                         Structures                                         */
/* ========================================================================== */

/**
 * \brief  Structure containing parameters for DCC module configuration.
 */
typedef struct SDL_DCC_Config_st
{
    SDL_DCC_Mode mode;
    /**< Mode of operation for DCC module.
     *  Refer enum SDL_DCC_Mode
     */
    SDL_DCC_Count0ClockSource clk0Src;
    /**< Clock source for COUNT0 i.e. reference clock.
     *  Refer enum SDL_DCC_Count0ClockSource
     */
    SDL_DCC_Count1ClockSource clk1Src;
    /**< Clock source for COUNT1 i.e. clock signal to be tested.
     *  Refer enum #SDL_DCC_Count1ClockSource.
     */
    uint32_t clk0Seed;
    /**< Preload value/seed value for COUNT0 */
    uint32_t clk0ValidSeed;
    /**< Preload value/seed value for VALID0 */
    uint32_t clk1Seed;
    /**< Preload value/seed value for COUNT1 */
}SDL_DCC_Config;


typedef struct
{
    bool doneIntr;
    /* Indicates if a done interrupt is currently pending */
    bool errIntr;
    /* Indicates if an error interrupt is currently pending */
    SDL_DCC_Config config;
    /* Pointer to DCC config structure */
    uint32_t clk0Cnt;
    /* Current COUNT0 value of clock source 0 */
    uint32_t clk0Valid;
    /* Current VALID0 value */
    uint32_t clk1Cnt;
    /* Current COUNT1 value of clock source 1 */
}SDL_DCC_Status;


typedef struct SDL_DCC_StaticRegs_st
{
    uint32_t  DCC_REV;
    /* DCC revision register */
    uint32_t DCC_CNTSEED0;
    /* COUNT0 SEED register */
    uint32_t DCC_VALIDSEED0;
    /* VALID0 SEED register */
    uint32_t DCC_CNTSEED1;
    /* COUNT1 SEED register */
    uint32_t DCC_CLKSRC1;
    /* CLOCK SOURCE1 register */
    uint32_t DCC_CLKSRC0;
    /* CLOCK SOURCE0 register */
}SDL_DCC_StaticRegs;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *
 * \brief   This API is used to configure DCC module.
 *
 * \param   instance        Holds the instance for DCC module.
 *
 * \param   pConfig         pointer to the DCC config structure
 *
 * \note    If the value of 'seedValid0' is less then 4 then it will programmed
 *          as 4. Since minimum programmable value of the 'seedValid0' is 4.
 *
 */
int32_t SDL_DCC_configure(uint32_t dccBase, const SDL_DCC_Config *pConfig);

/**
 *
 * \brief   This API is used to verify the configuration for DCC module.
 *
 * \param   instance        Holds the instance for DCC module.
 *
 * \param   pConfig         pointer to the DCC config structure
 *
 */
int32_t SDL_DCC_verifyConfig(uint32_t dccBase, const SDL_DCC_Config *pConfig);

/**
 *
 * \brief   This API is used to enable the DCC module.
 *
 * \param   instance        Holds the instance for DCC module.
 *
 */
int32_t SDL_DCC_enable(uint32_t dccBase);

/**
 *
 * \brief   This API is used to disable the DCC module.
 *
 * \param   instance        Holds the instance for DCC module.
 *
 */
int32_t SDL_DCC_disable(uint32_t dccBase);

/**
 *
 * \brief   This API is used to get the stauts of DCC module.
 *
 * \param   instance        Holds the instance for DCC module.
 *
 * \param   pStatus         pointer to the SDL_DCC_status structure
 *
 */
int32_t SDL_DCC_getStatus(uint32_t dccBase, SDL_DCC_Status *pStatus);

/**
 *
 * \brief   This API is used to Enable the interrupts.
 *
 * \param   instance        Holds the instance for DCC module.
 *
 * \param   intr            Interrupts to be enabled.
 *
 */
int32_t SDL_DCC_enableIntr(uint32_t dccBase, SDL_DCC_IntrType intr);

/**
 *
 * \brief   This API is used to clear the interrupts.
 *
 * \param   instance         Holds the instance for DCC module.
 *
 * \param   intr             Interrupts to disable.
 *
 */
int32_t SDL_DCC_clearIntr(uint32_t dccBase, SDL_DCC_IntrType intr);

/**
 *
 * \brief   This API is used to get the value of static registers for DCC module
 *
 * \param   instance         Holds the instance for DCC module.
 *
 * \param   pStaticRegs      Pointer to the SDL_DCC_staticRegs structure.
 *
 */
int32_t SDL_DCC_getStaticRegs(uint32_t dccBase, SDL_DCC_StaticRegs *pStaticRegs);

#endif /* SDL_DCC_H_ */

/** @} */