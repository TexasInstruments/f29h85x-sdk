//###########################################################################
//
// FILE:   sysctl.c
//
// TITLE:  C29x system control driver.
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

#include "sysctl.h"
#include "dcc.h"

//
// Macro used to add wait cycles to allow load capacitors to charge
//
#define SYSCTL_XTAL_CHARGE_DELAY   asm(" NOP #5");

//
// Number of PLL retries for SW work around
//
#define SYSCTL_PLL_RETRIES              100U    // Number of PLL retries
#define SYSCTL_PLLLOCK_TIMEOUT          2000U   // PLL Lock timeout
#define SYSCTL_DCC_COUNTER0_TOLERANCE   1U
#define SYSCTL_DCC_COUNTER0_WINDOW      1000U   // DCC Counter0 Window

#define SYSCTL_SYNCBUSY_TIMEOUT_CYCLES   (10000U)
#define SYSCTL_X1CNT_TIMEOUT_CYCLES      (10000U)

//
// Function prototypes internal to the driver
//
void SysCtl_selectXTAL(void);
void SysCtl_selectXTALSingleEnded(void);
bool SysCtl_isPLLValid(uint32_t dccBase, Sysctl_PLLClockSource oscSrc,
                       Sysctl_PLLRefDiv refDiv, Sysctl_PLLIMult iMult,
                       Sysctl_PLLODiv oDiv);

//*****************************************************************************
//
// SysCtl_delay()
//
//*****************************************************************************
__asm("    .global SysCtl_delay         \n" \
      "    .section .TI.ramfunc, \"ax\" \n" \
      "SysCtl_delay:                    \n" \
      "    MV A0, D0                    \n" \
      "loop:                            \n" \
      "    DECB A0, #1, loop            \n" \
      "    RET                          \n" );



//*****************************************************************************
//
// SysCtl_pollSyncBusy()
//
//*****************************************************************************
void SysCtl_pollSyncBusy(uint32_t mask)
{
    uint32_t timeoutCnt = 0U;
    uint32_t status = 1U;

    //
    //  Wait for BUSY bit to clear
    //
    while((HWREG(DEVCFG_BASE + SYSCTL_O_SYNCBUSY) & mask) == mask)
    {
        if(timeoutCnt >= SYSCTL_SYNCBUSY_TIMEOUT_CYCLES)
        {
            status = 0U;
            break;
        }

        timeoutCnt++;
    }

    //
    // When a timeout occurs, error function will be invoked.
    // Users can replace this with custom code.
    //
    ASSERT(status == 1U);
}

//*****************************************************************************
//
// SysCtl_pollSyncBusyWd()
//
//*****************************************************************************
void SysCtl_pollSyncBusyWd(uint32_t mask)
{
    uint32_t timeoutCnt = 0U;
    uint32_t status = 1U;

    //
    //  Wait for BUSY bit to clear
    //
    while((HWREGH(WD_BASE + SYSCTL_O_SYNCBUSYWD) & mask) == mask)
    {
        if(timeoutCnt >= SYSCTL_SYNCBUSY_TIMEOUT_CYCLES)
        {
            status = 0U;
            break;
        }

        timeoutCnt++;
    }

    //
    // When a timeout occurs, error function will be invoked.
    // Users can replace this with custom code.
    //
    ASSERT(status == 1U);
}

//*****************************************************************************
//
// SysCtl_pollX1Counter()
//
//*****************************************************************************
static void
SysCtl_pollX1Counter(void)
{
    uint16_t loopCount = 0U;
    uint32_t timeoutCnt = 0U;
    uint32_t status = true;

    //
    // Delay for 1 ms while the XTAL powers up
    //
    // 2500 loops, 4 cycles per loop + 11 cycles overhead = 10011 cycles
    //
    SysCtl_delay(2500);

    //
    // Clear and saturate X1CNT 4 times to guarantee operation.
    // Commented since X1 Counter Clear does not work.
    //
    // do
    // {
    //     status = true;
        //
        // Keep clearing the counter until it is no longer saturated
        //
        // while(HWREG(DEVCFG_BASE + SYSCTL_O_X1CNT) > 0x1FFU)
        // {
        //     HWREG(DEVCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
        // }

        //
        // Wait for the X1 clock to saturate
        //
        // while(HWREGH(DEVCFG_BASE + SYSCTL_O_X1CNT) != SYSCTL_X1CNT_X1CNT_M)
        // {
        //     if(timeoutCnt >= SYSCTL_X1CNT_TIMEOUT_CYCLES)
        //     {
        //         status = false;
        //         break;
        //     }

        //     timeoutCnt++;
        // }

        //
        // When a timeout occurs, error function will be invoked.
        // Users can replace this with custom code.
        //
        // ASSERT(status == true);

        //
        // Increment the counter
        //
    //     loopCount++;
    // } while(loopCount < 4U);
}

//*****************************************************************************
//
// SysCtl_selectXTAL()
//
//*****************************************************************************
void
SysCtl_selectXTAL(void)
{
    uint16_t loopCount = 0U;

    //
    // Enable XOSC pads initialization and set X1, X2 high
    //
    HWREGH(DEVCFG_BASE + SYSCTL_O_XTALCR2) |= SYSCTL_XTALCR2_FEN |
                                              SYSCTL_XTALCR2_XIF |
                                              SYSCTL_XTALCR2_XOF;
    //
    // Wait for few cycles to allow load capacitors to charge
    //
    SYSCTL_XTAL_CHARGE_DELAY;

    //
    // Turn on XTAL and select crystal mode
    //
    HWREGH(DEVCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;
    HWREGH(DEVCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_SE;

    //
    // Wait for the X1 clock to saturate
    //
    SysCtl_pollX1Counter();

    //
    // Select XTAL as the oscillator source
    //
    HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) =
        (HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) &
          ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M) | 1U;

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_CLKSRCCTL1);

    //
    // If a missing clock failure was detected, try waiting for the X1 counter
    // to saturate again. Consider modifying this code to add a 10ms timeout.
    //
    while(SysCtl_isMCDClockFailureDetected())
    {
        //
        // Clear the MCD failure
        //
        SysCtl_resetMCD();

        //
        // Wait for the X1 clock to saturate
        //
        SysCtl_pollX1Counter();

        //
        // Select XTAL as the oscillator source
        //
        HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) =
            (HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) &
             ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M) | 1U;

        SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_CLKSRCCTL1);
    }
}

//*****************************************************************************
//
// SysCtl_selectXTALSingleEnded()
//
//*****************************************************************************
void
SysCtl_selectXTALSingleEnded(void)
{
    //
    // Turn on XTAL and select single-ended mode.
    //
    HWREGH(DEVCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;
    HWREGH(DEVCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_SE;

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_XTALCR);

    //
    // Wait for the X1 clock to saturate
    //
    SysCtl_pollX1Counter();

    //
    // Select XTAL as the oscillator source
    //
    HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) =
    (HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) &
      ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M) | 1U;

    SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_CLKSRCCTL1);

    //
    // Something is wrong with the oscillator module. Replace the ESTOP0 with
    // an appropriate error-handling routine.
    //
    while(SysCtl_isMCDClockFailureDetected())
    {
        ESTOP0;
    }
}

//*****************************************************************************
//
// SysCtl_selectOscSource()
//
//*****************************************************************************
void
SysCtl_selectOscSource(uint32_t oscSource)
{
    //
    // Select the specified source.
    //
    switch(oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            //
            // Clk Src = INTOSC2
            //
            HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
                ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;

            SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_CLKSRCCTL1);
            break;

        case SYSCTL_OSCSRC_XTAL:
            //
            // Select XTAL in crystal mode and wait for it to power up
            //
            SysCtl_selectXTAL();
            break;

        case SYSCTL_OSCSRC_XTAL_SE:
            //
            // Select XTAL in single-ended mode and wait for it to power up
            //
            SysCtl_selectXTALSingleEnded();
            break;

        case SYSCTL_OSCSRC_OSC1:
            //
            // Clk Src = INTOSC1
            //
            HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) =
                   (HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) &
                    ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M) | 0x2U;

            SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_CLKSRCCTL1);
            break;

        default:
            //
            // Do nothing. Not a valid oscSource value.
            //
            break;
    }
}

//*****************************************************************************
//
// SysCtl_isPLLValid()
//
//*****************************************************************************
bool
SysCtl_isPLLValid(uint32_t dccBase, Sysctl_PLLClockSource oscSrc,
                  Sysctl_PLLRefDiv refDiv, Sysctl_PLLIMult iMult,
                  Sysctl_PLLODiv oDiv)
{
    float  fclk1_0ratio, fclk0_1ratio;
    float32_t total_error, window;

    ASSERT(DCC_isBaseValid(dccBase));

    DCC_Count0ClockSource dccClkSrc0;
    DCC_Count1ClockSource dccClkSrc1;
    uint32_t dccCounterSeed0, dccCounterSeed1, dccValidSeed0;

    switch(oscSrc)
    {
        case SYSCTL_OSCSRC_OSC2:
            //
            // Select DCC Clk Src0 as INTOSC2
            //
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC2;
            break;
        case SYSCTL_OSCSRC_XTAL:
        case SYSCTL_OSCSRC_XTAL_SE:
            //
            // Select DCC Clk Src0 as XTAL
            //
            dccClkSrc0 = DCC_COUNT0SRC_XTAL;
            break;
        case SYSCTL_OSCSRC_OSC1:
            //
            // Select DCC Clk Src0 as INTOSC1
            //
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC1;
            break;
        default:
            //
            // Select DCC Clk Src0 as INTOSC1
            //
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC1;
            break;
    }

    //
    // Select DCC Clk Src1 as SYSPLL
    //
    dccClkSrc1 = DCC_COUNT1SRC_PLL;


    //
    // Retrieving PLL parameters
    //
    fclk1_0ratio = (float)iMult / (((float)oDiv + 1.0F) *
                   ((float)refDiv + 1.0F));
    fclk0_1ratio = (((float)refDiv + 1.0F) *
                   ((float)oDiv + 1.0F)) / (float)iMult;

    if(fclk1_0ratio >= 1.0F)
    {
        //
        // Setting Counter0 & Valid Seed Value with +/-1% tolerance
        // Total error is 12
        //
        window = (12U * 100U) / ((uint32_t)SYSCTL_DCC_COUNTER0_TOLERANCE);
        dccCounterSeed0 = (uint32_t)window - 12U;
        dccValidSeed0 = 24U;
    }
    else
    {
        total_error = ((2.0F * fclk0_1ratio) + 10.0F);
        window = (total_error * 100.0F) /
                 ((float32_t)SYSCTL_DCC_COUNTER0_TOLERANCE);

        //
        // Setting Counter0 & Valid Seed Value with +/-1% tolerance
        //
        dccCounterSeed0 = window - total_error;
        dccValidSeed0 = 2U * (uint32_t)total_error;
    }

    //
    // Multiplying Counter-0 window with PLL Integer Multiplier
    //
    dccCounterSeed1 = (window * fclk1_0ratio);

    //
    // Enable peripheral clock to DCC
    //
    if(dccBase == DCC1_BASE)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC1);
    }
    else if(dccBase == DCC2_BASE)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC2);
    }
    else
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC3);
    }

    //
    // Clear Error & Done Flag
    //
    DCC_clearErrorFlag(dccBase);
    DCC_clearDoneFlag(dccBase);

    //
    // Disable DCC
    //
    DCC_disableModule(dccBase);

    //
    // Disable Error Signal
    //
    DCC_disableErrorSignal(dccBase);

    //
    // Disable Done Signal
    //
    DCC_disableDoneSignal(dccBase);

    //
    // Configure Clock Source0 to whatever set as a clock source for PLL
    //
    DCC_setCounter0ClkSource(dccBase, dccClkSrc0);

    //
    // Configure Clock Source1 to PLL
    //
    DCC_setCounter1ClkSource(dccBase, dccClkSrc1);

    //
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    //
    DCC_setCounterSeeds(dccBase, dccCounterSeed0, dccValidSeed0,
                        dccCounterSeed1);

    //
    // Enable Single Shot mode
    //
    DCC_enableSingleShotMode(dccBase);

    //
    // Enable DCC to start counting
    //
    DCC_enableModule(dccBase);

    //
    // Wait until Error or Done Flag is generated
    //
    while((HWREGH(dccBase + DCC_O_STATUS) &
           (DCC_STATUS_ERR | DCC_STATUS_DONE)) == 0U)
    {
    }

    //
    // Returns true if DCC completes without error
    //
    return((HWREGH(dccBase + DCC_O_STATUS) &
            (DCC_STATUS_ERR | DCC_STATUS_DONE)) == DCC_STATUS_DONE);
}


//*****************************************************************************
//
// SysCtl_getClock()
//
//*****************************************************************************
uint32_t
SysCtl_getClock(uint32_t clockInHz)
{
    uint32_t temp;
    uint32_t oscSource;
    uint32_t clockOut;
    uint32_t imult, refDiv, oDiv, sysDiv;

    //
    // Don't proceed if an MCD failure is detected.
    //
    if(SysCtl_isMCDClockFailureDetected())
    {
        //
        // OSCCLKSRC2 failure detected. Returning the INTOSC1 rate. You need
        // to handle the MCD and clear the failure.
        //
        clockOut = SYSCTL_DEFAULT_OSC_FREQ;
    }
    else
    {
        //
        // If one of the internal oscillators is being used, start from the
        // known default frequency.  Otherwise, use clockInHz parameter.
        //
        oscSource = HWREG(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) &
                    SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;

        if((oscSource == (uint32_t)SYSCTL_OSCSRC_OSC2) ||
           (oscSource == (uint32_t)SYSCTL_OSCSRC_OSC1) )
        {
            clockOut = SYSCTL_DEFAULT_OSC_FREQ;
        }
        else
        {
            clockOut = clockInHz;
        }

        //
        // If the PLL is enabled calculate its effect on the clock
        //
        if((HWREG(DEVCFG_BASE + SYSCTL_O_SYSPLLCTL1) &
            (SYSCTL_SYSPLLCTL1_PLLEN | SYSCTL_SYSPLLCTL1_PLLCLKEN)) == 3U)
        {
            imult  = (HWREG(DEVCFG_BASE + SYSCTL_O_SYSPLLMULT) &
                      SYSCTL_SYSPLLMULT_IMULT_M)  >> SYSCTL_SYSPLLMULT_IMULT_S;

            refDiv = (HWREG(DEVCFG_BASE + SYSCTL_O_SYSPLLMULT) &
                     SYSCTL_SYSPLLMULT_REFDIV_M) >> SYSCTL_SYSPLLMULT_REFDIV_S;

            oDiv   = (HWREG(DEVCFG_BASE + SYSCTL_O_SYSPLLMULT) &
                      SYSCTL_SYSPLLMULT_ODIV_M)   >> SYSCTL_SYSPLLMULT_ODIV_S;

            //
            // Calculate integer multiplier
            //
            clockOut = clockOut * imult;

            //
            // Calculate PLL divider
            //
            temp = (refDiv + 1U) * (oDiv + 1U);

            //
            //  Divide dividers
            //
            if(temp != 0U)
            {
                clockOut /= temp;
            }
        }

        sysDiv = HWREG(DEVCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) &
                 SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M;

        clockOut /= (sysDiv + 1U);

        SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSCLKDIVSEL);
    }

    return(clockOut);
}

//*****************************************************************************
//
// SysCtl_setClock()
//
//*****************************************************************************
bool
SysCtl_setClock(Sysctl_PLLClockSource oscSrc, Sysctl_PLLConfig pllConfig,
                Sysctl_PLLRefDiv refDiv, Sysctl_PLLIMult iMult,
                Sysctl_PLLODiv oDiv, Sysctl_PLLSysDiv sysDiv, uint32_t dccBase)
{
    uint16_t divSel, pllen, oscclksrcsel, pllLockStatus, xtalval;
    uint32_t pllMult, mult, timeout;
    bool status = false;

    //
    // Don't proceed to the PLL initialization if an MCD failure is detected.
    //
    if(SysCtl_isMCDClockFailureDetected())
    {
        //
        // OSCCLKSRC2 failure detected. Returning false. You'll need to clear
        // the MCD error.
        //
        status = false;
    }
    else
    {
        //
        // Bypass PLL
        //
        HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLCTL1) &=
                                ~SYSCTL_SYSPLLCTL1_PLLCLKEN;

        //
        // Delay of at least 120 OSCCLK cycles required post PLL bypass
        //
        SysCtl_delay(28);
        SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSPLLCTL1);

        //
        // Derive the current and previous oscillator clock source values
        //
        oscclksrcsel = HWREGH(DEVCFG_BASE + SYSCTL_O_CLKSRCCTL1) &
                       SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;

        if((oscclksrcsel == (uint16_t)SYSCTL_OSCSRC_XTAL) &&
           (HWREGH(DEVCFG_BASE + SYSCTL_O_XTALCR) & SYSCTL_XTALCR_SE) != 0U)
        {
            oscclksrcsel = SYSCTL_OSCSRC_XTAL_SE;
        }

        //
        // Check if the oscillator clock source has changed
        //
        if(oscclksrcsel != (uint16_t)oscSrc)
        {
            //
            // Turn off PLL
            //
            HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLCTL1) &=
                                    ~SYSCTL_SYSPLLCTL1_PLLEN;

            //
            // Delay of at least 60 OSCCLK cycles required between
            // powerdown to powerup of PLL
            //
            SysCtl_delay(13U);
            SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSPLLCTL1);

            //
            // Configure oscillator source
            //
            SysCtl_selectOscSource(oscSrc);

            //
            // Delay of at least 60 OSCCLK cycles
            //
            SysCtl_delay(13U);
        }

        //
        // Set dividers to /1 to ensure the fastest PLL configuration
        //
        HWREGH(DEVCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) = 0U;
        SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSCLKDIVSEL);

        //
        // Configure PLL if PLL usage is enabled or bypassed in config
        //
        if((pllConfig == SYSCTL_PLL_ENABLE) || (pllConfig == SYSCTL_PLL_BYPASS))
        {
            //
            // Get the PLL multiplier settings from config
            //
            pllMult  = (uint32_t)iMult |
                       ((uint32_t)refDiv << SYSCTL_SYSPLLMULT_REFDIV_S) |
                       ((uint32_t)oDiv << SYSCTL_SYSPLLMULT_ODIV_S);

            //
            // Get the PLL multipliers currently programmed
            //
            mult  = ((HWREG(DEVCFG_BASE + SYSCTL_O_SYSPLLMULT) &
                      SYSCTL_SYSPLLMULT_IMULT_M) >> SYSCTL_SYSPLLMULT_IMULT_S);

            mult |= (HWREG(DEVCFG_BASE + SYSCTL_O_SYSPLLMULT) &
                     SYSCTL_SYSPLLMULT_REFDIV_M);

            mult |= (HWREG(DEVCFG_BASE + SYSCTL_O_SYSPLLMULT) &
                     SYSCTL_SYSPLLMULT_ODIV_M);

            pllen = (HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLCTL1) &
                     SYSCTL_SYSPLLCTL1_PLLEN);

            //
            // Lock PLL only if the multipliers need an update or PLL needs
            // to be powered on / enabled
            //
            if((mult !=  pllMult) || (pllen != 1U))
            {
                //
                // Turn off PLL
                //
                HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLCTL1) &=
                    ~SYSCTL_SYSPLLCTL1_PLLEN;

                //
                // Delay of at least 66 OSCCLK cycles required between
                // powerdown to powerup of PLL
                //
                SysCtl_delay(14U);
                SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSPLLCTL1);

                //
                // Write multiplier, which automatically turns on the PLL
                //
                HWREG(DEVCFG_BASE + SYSCTL_O_SYSPLLMULT) = pllMult;
                SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSPLLMULT);

                //
                // Enable/ turn on PLL
                //
                HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLCTL1) |=
                       SYSCTL_SYSPLLCTL1_PLLEN;

                SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSPLLCTL1);

                //
                // Wait for the SYSPLL lock counter or a timeout
                // This timeout needs to be computed based on OSCCLK
                // with a factor of REFDIV.
                // Lock time is 1024 OSCCLK * (REFDIV+1)
                //
                timeout = (1024U * ((uint32_t)refDiv + 1U));
                pllLockStatus = HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLSTS) &
                                SYSCTL_SYSPLLSTS_LOCKS;

                while((pllLockStatus != 1U) && (timeout != 0U))
                {
                    pllLockStatus = HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLSTS) &
                                    SYSCTL_SYSPLLSTS_LOCKS;
                    timeout--;
                }

                //
                // Check PLL Frequency using DCC
                //
               status = SysCtl_isPLLValid(dccBase, oscSrc, refDiv, iMult, oDiv);
            }
            else
            {
                //
                // Re-Lock of PLL not needed since the multipliers
                // are not updated
                //
                status = true;
            }
        }
        else if(pllConfig== SYSCTL_PLL_DISABLE)
        {
            //
            // Turn off PLL when the PLL is disabled in config
            //
            HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLCTL1) &=
                   ~SYSCTL_SYSPLLCTL1_PLLEN;

            SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSPLLCTL1);

            //
            // PLL is bypassed and not in use
            // Status is updated to true to allow configuring the dividers later
            //
            status = true;
        }
        else
        {
            //
            // Empty
            //
        }

        //
        // If PLL locked successfully, configure the dividers
        // Or if PLL is bypassed, only configure the dividers
        //
        if(status)
        {
            //
            // Set divider to produce slower output frequency to limit current
            // increase.
            //
            if(sysDiv > SYSCTL_SYSDIV_61)
            {
                HWREGH(DEVCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) = (uint8_t)sysDiv;
            }
            else
            {
                HWREGH(DEVCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) =
                                            (uint16_t)sysDiv + 4U;
            }

            SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSCLKDIVSEL);

            //
            // Feed system clock from SYSPLL only if PLL usage is enabled
            //
            if(pllConfig == SYSCTL_PLL_ENABLE)
            {

                //
                // Enable PLLSYSCLK is fed from system PLL clock
                //
                HWREGH(DEVCFG_BASE + SYSCTL_O_SYSPLLCTL1) |=
                       SYSCTL_SYSPLLCTL1_PLLCLKEN;
                //
                //  Disable MCD as per errata
                //
                SysCtl_disableMCD();
            }

            //
            // ~200 PLLSYSCLK delay to allow voltage regulator to stabilize
            // prior to increasing entire system clock frequency.
            //
            SysCtl_delay(48);
            SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSPLLCTL1);

            //
            // Set the divider to user value
            //
            HWREGH(DEVCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) = (uint8_t)sysDiv;
            SysCtl_pollSyncBusy(SYSCTL_SYNCBUSY_SYSCLKDIVSEL);
        }
        else
        {
            ESTOP0; // If the frequency is out of range, stop here.
        }
    }

    return(status);
}


//*****************************************************************************
//
// SysCtl_getDeviceParametric()
//
//*****************************************************************************
uint16_t
SysCtl_getDeviceParametric(SysCtl_DeviceParametric parametric)
{
    uint32_t value;

    //
    // Get requested parametric value
    //
    switch(parametric)
    {
        case SYSCTL_DEVICE_QUAL:
            //
            // Qualification Status
            //
            value = ((HWREG(DEVCFG_BASE + SYSCTL_O_PARTIDL) &
                      SYSCTL_PARTIDL_QUAL_M) >> SYSCTL_PARTIDL_QUAL_S);
            break;

        case SYSCTL_DEVICE_PINCOUNT:
            //
            // Pin Count
            //
            value = ((HWREG(DEVCFG_BASE + SYSCTL_O_PARTIDL) &
                      SYSCTL_PARTIDL_PIN_COUNT_M) >>
                     SYSCTL_PARTIDL_PIN_COUNT_S);
            break;

        case SYSCTL_DEVICE_FLASH:
            //
            // Flash Size (KB)
            //
            value = ((HWREG(DEVCFG_BASE + SYSCTL_O_PARTIDL) &
                      SYSCTL_PARTIDL_FLASH_SIZE_M) >>
                     SYSCTL_PARTIDL_FLASH_SIZE_S);
            break;

        case SYSCTL_DEVICE_PARTNO:
            //
            // Part Number
            //
            value = ((HWREG(DEVCFG_BASE + SYSCTL_O_PARTIDH) &
                      SYSCTL_PARTIDH_PARTNO_M) >> SYSCTL_PARTIDH_PARTNO_S);
            break;

        case SYSCTL_DEVICE_CLASSID:
            //
            // Class ID
            //
            value = ((HWREG(DEVCFG_BASE + SYSCTL_O_PARTIDH) &
                      SYSCTL_PARTIDH_DEVICE_CLASS_ID_M) >>
                     SYSCTL_PARTIDH_DEVICE_CLASS_ID_S);
            break;

        default:
            //
            // Not a valid value for PARTID register
            //
            value = 0U;
            break;
    }

    return((uint16_t)value);
}

//*****************************************************************************
//
// SysCtl_emulateDevice()
//
//*****************************************************************************
void
SysCtl_emulateDevice (SysCtl_DevicePartNumber partNumber)
{
    //
    // Update the MCUCNF registers value for different GPNs
    //

    switch(partNumber)
    {
        case SYSCTL_EMULATE_F29H850TU9:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0xFFFFU;
            break;
        case SYSCTL_EMULATE_F29H859TU8:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0xFFFFU;
            break;
        case SYSCTL_EMULATE_F29H859TM8:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0x00FFU;
            break;
        case SYSCTL_EMULATE_F29H850DM7:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFF7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0x00FFU;
            break;
        case SYSCTL_EMULATE_F29H850DU7:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFF7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0xFFFFU;
            break;
        case SYSCTL_EMULATE_F29H859DM6:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFF7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0x00FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0x00FFU;
            break;
        case SYSCTL_EMULATE_F29H859DU6:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFF7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0xFFFFU;
            break;
        case SYSCTL_EMULATE_F29P580DM5:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFC01FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFCFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFCFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFCFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xF0FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFC7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFF7FFF7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFDU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFEFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xF000FFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0x0000U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0x0000U;
            break;
        case SYSCTL_EMULATE_F29P589DM5:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFC01FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFCFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFCFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFCFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xF0FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFC7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFF7FFF7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFDU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFEFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xF000FFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0x0000U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0x0000U;
            break;
        case SYSCTL_EMULATE_F29P589DU5:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2) = 0xFFFC01FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4) = 0xFFCFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7) = 0xFFCFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) = 0xFCFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14) = 0xF0FFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17) = 0xFFC7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18) = 0xFFF7FFF7U;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) = 0xFFFDU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) = 0xFFFEU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31) = 0xFFFFFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64) = 0xFFEFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65) = 0xF000FFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79) = 0xFFFFU;
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81) = 0xFFFFU;
            break;
        case SYSCTL_EMULATE_F29P329SM2:
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1)   = 0xFFFFFFFEU;              //  EMIF is not preent
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF2)   = 0xFFFC00FFU;              //  EPWM        = 8/18
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF4)   = 0xFFFFFFCFU;              //  EQEP        = 4/6
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF7)   = 0xFFC3FFFFU;              //  UART        = 2/6
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10)  = 0xFFFFFC7FU;              //  MCAN        = 3/6
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF13)  = 0xFFFFFFEFU;              //  ADC         = 4/5
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF14)  = 0xFFFFF00FU;              //  CMPSS       = 4/12
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF16)  = 0xFFFCFFFFU;              //  DAC         = 0/2
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF17)  = 0xFFFFFFC0U;              //  CLB         = 0/6
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF18)  = 0xFFF3FFF3U;              //  FSI         = 2/4
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19)  = 0xFFFFFFFFU;              //  LIN         = 2/2
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23)  = 0xFFFFFFFEU;              //  Ethercat is not present
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF26)  = 0xFFFFFFFFU;              //  AES, SHA, PKA and TRNG
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF31)  = 0xFFFFFFFFU;              //  SM2, SM3 and SM4
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF64)  = 0xFFFFFFEFU;              //  CPU3 is not present
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF65)  = 0xF000FFFFU;              //  CDA0-11 are absent
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF74)  = 0xFFFFFFFFU;              //  FLC1B0/B1 flash
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF76)  = 0xFFFFFFFFU;              //  FLC1B2/B3 flash
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF78)  = 0xFFFFFF0FU;              //  FLC1B4 flash
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF79)  = 0xFFFF0000U;              //  FLC2B0/B1 flash is not present
            HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF81)  = 0xFFFF0000U;              //  FLC2B2/B3 flash is not present
            break;


        default:
            break;
    }
}