//#############################################################################
//
// FILE:   epwm_ex15_xcmp_multiple_edges.c
//
// TITLE:  ePWM Using XCMP Mode
//
//! \addtogroup driver_example_list
//! <h1>ePWM XCMP Mode</h1>
//!
//! (Note - base frequency and duty cycle of all ePWM's are 50 KHz and 50%
//!  respectively. Value of TBPRD = 1999)
//! This example configures ePWM1, ePWM2, ePWM4, ePWM6 and ePWM8 as follows
//!  - ePWM1A is allocated all XCMP1-8 registers. ePWM1B has no output.
//!      - New duty cycle = 50%, new frequency = 200 KHz
//!      - No Shadow registers used
//!  - ePWM2A is allocated XCMP1-4 and ePWM2B is allocated XCMP5-8 registers.
//!      - A and B waveforms are complimentary
//!      - New duty cycle = 50%, new frequency = 100 KHz
//!      - No Shadow registers used
//!  - ePWM4 is configured same as ePWM2 with Minimum Deadband.
//!      - Minimum Deadband of 200 SYSCLK cycles provided
//!        (200 * (1/200 MHz) = 1 micro second)
//!      - This implies dead band of 1 us is visible on output of
//!        ePWM4A and ePWM4B after their falling edge
//!      - New duty cycle = 40%, new frequency = 100 KHz
//!  - ePWM6A is allocated XCMP1-4 registers.
//!      - 3 Shadow register sets used with LOADMULTIPLE mode
//!      - Shadow set 2 repeated 2 times, Shadow set 3 repeated 4 times
//!      - ISR to update all Shadow registers with new values after they repeat
//!      - This means Shadow3 is active for 5 periods,
//!        Shadow2 is active for 3 periods and Shadow1 is active for 1 period
//!        before their new values are visible in output
//!  - ePWM8A is allocated XCMP1-4 registers.
//!      - 3 Shadow register sets used with LOADONCE mode
//!      - Only Shadow set 3 is loaded from every period
//!      - ISR updates Shadow 3 register with new values every 5 periods
//!
//!  \b External \b Connections \n
//!  - ePWM1A is on GPIO0
//!  - ePWM2A is on GPIO2 and ePWM2B is on GPIO3
//!  - ePWM4A is on GPIO6 and ePWM4B is on GPIO7
//!  - ePWM6A is on GPIO14
//!  - ePWM8A is on GPIO10
//!  - Monitor GPIO24 for ePWM6A new Shadow register value loading
//!  - Monitor GPIO25 for ePWM8A new Shadow register value loading
//!
//! Shadow register updations for ePWM6 and ePWM8:
//!   - Only XCMP1 and XCMP4 are updated
//!   - Update values are +/- 20 TBCTR steps depending on direction of updation
//!   - GPIO24 is toggled every 9 cycles for ePWM6 after cycling through all 
//!     Shadow buffers and loading new values
//!     Similarly GPIO25 is toggled every 5 cycles for ePWM8
//!
//
//#############################################################################
//
//
// $Copyright:
//#############################################################################

//
// Included Files
//
#include "board.h"

//
// Defines
//
#define XTBPRD 1999U        //Period register common for all PWM's

#define EPWM_MIN_XCMP1 0U
#define EPWM_MAX_XCMP1 450U
#define EPWM_MIN_XCMP4 1500U
#define EPWM_MAX_XCMP4 1950U

#define EPWM_CMP_UP 1U
#define EPWM_CMP_DOWN 0U

//
// Globals
//
typedef struct
{
    uint32_t epwmBase;
    uint16_t epwmXCMP1Direction;
    uint16_t epwmXCMP4Direction;
    uint16_t epwmIntCount;
    uint16_t epwmMaxXCMP1;
    uint16_t epwmMinXCMP1;
    uint16_t epwmMaxXCMP4;
    uint16_t epwmMinXCMP4;
    uint16_t xcmp1Val;
    uint16_t xcmp4Val;
} epwmInfo;

epwmInfo epwm6_Info;
epwmInfo epwm8_Info;

//
// Function Prototypes
//
void init_epwm6_Info(void);
void init_epwm8_Info(void);

void updateShadow1_forEpwm6(void);
void updateShadow2_forEpwm6(void);
void updateShadow3_forEpwm6(void);
void updateShadow3_forEpwm8(void);

__attribute__((interrupt("INT"))) void epwm6_ISR(void);
__attribute__((interrupt("INT"))) void epwm8_ISR(void);

//
// Main
//
int main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set EPWM Clock Divider to 1 to feed 200 MHz SysClock.
    // Note: Default value is 2.
    //
    SysCtl_setEPWMClock(SYSCTL_EPWMCLK_DIV_1);

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    init_epwm6_Info();
    init_epwm8_Info();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Initial Shadow to Active load strobe
    //
    EPWM_enableXLoad(myEPWM6_BASE);
    EPWM_enableXLoad(myEPWM8_BASE);

    while(1)
    {

    }
}

void init_epwm6_Info(void)
{
    epwm6_Info.epwmBase = myEPWM6_BASE;

    epwm6_Info.epwmXCMP1Direction = EPWM_CMP_UP;
    epwm6_Info.epwmXCMP4Direction = EPWM_CMP_DOWN;

    epwm6_Info.epwmIntCount = 0U;

    epwm6_Info.epwmMaxXCMP1 = EPWM_MAX_XCMP1;
    epwm6_Info.epwmMinXCMP1 = EPWM_MIN_XCMP1;
    epwm6_Info.epwmMaxXCMP4 = EPWM_MAX_XCMP4;
    epwm6_Info.epwmMinXCMP4 = EPWM_MIN_XCMP4;

    epwm6_Info.xcmp1Val = 0U;
    epwm6_Info.xcmp4Val = 1500U;
}

void init_epwm8_Info(void)
{
    epwm8_Info.epwmBase = myEPWM8_BASE;

    epwm8_Info.epwmXCMP1Direction = EPWM_CMP_UP;
    epwm8_Info.epwmXCMP4Direction = EPWM_CMP_DOWN;

    epwm8_Info.epwmIntCount  =  0U;

    epwm8_Info.epwmMaxXCMP1 = EPWM_MAX_XCMP1;
    epwm8_Info.epwmMinXCMP1 = EPWM_MIN_XCMP1;
    epwm8_Info.epwmMaxXCMP4 = EPWM_MAX_XCMP4;
    epwm8_Info.epwmMinXCMP4 = EPWM_MIN_XCMP4;

    epwm8_Info.xcmp1Val = 0U;
    epwm8_Info.xcmp4Val = 1500U;
}


__attribute__((interrupt("INT"))) void epwm6_ISR(void)
{
    epwm6_Info.epwmIntCount++;

    if(epwm6_Info.epwmIntCount == 4U)
    {
        updateShadow3_forEpwm6();
    }

    else if(epwm6_Info.epwmIntCount == 6U)
    {
        updateShadow2_forEpwm6();
    }

    else if(epwm6_Info.epwmIntCount == 8U)
    {
        updateShadow1_forEpwm6();

    }
    if(epwm6_Info.epwmIntCount == 9U)
    {
        epwm6_Info.epwmIntCount = 0U;

        //
        // Toggling GPIO to indicate new shadow to active loading
        // 
        GPIO_togglePin(myGPIO1);

        //
        // Next load initiation, done after every 9 cycles.
        //
        EPWM_enableXLoad(myEPWM6_BASE);
    }

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM6_BASE);

}

__attribute__((interrupt("INT"))) void epwm8_ISR(void)
{
    epwm8_Info.epwmIntCount++;

    if(epwm8_Info.epwmIntCount == 5U)
    {
        epwm8_Info.epwmIntCount = 0U;
        updateShadow3_forEpwm8();

        //
        // Toggling GPIO to indicate new shadow to active loading
        // 
        GPIO_togglePin(myGPIO2);

        //
        //Next load initiation, done after every 5 cycles.
        //
        EPWM_enableXLoad(myEPWM8_BASE);
    }

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM8_BASE);

}

//
// Function to update XCMP1,4,5,8 based on their directions.
//
void updateShadow3_forEpwm6(void)
{
    if(epwm6_Info.epwmXCMP1Direction == EPWM_CMP_UP)
    {
        if(epwm6_Info.xcmp1Val < EPWM_MAX_XCMP1)
        {
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW3,
                                 epwm6_Info.xcmp1Val + 20U);
        }
        else
        {
            epwm6_Info.epwmXCMP1Direction = EPWM_CMP_DOWN;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW3,
                                 epwm6_Info.xcmp1Val - 20U);
        }
    }
    else
    {
        if(epwm6_Info.xcmp1Val > EPWM_MIN_XCMP1)
        {
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW3,
                                 epwm6_Info.xcmp1Val - 20U);
        }
        else
        {
            epwm6_Info.epwmXCMP1Direction = EPWM_CMP_UP;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW3,
                                 epwm6_Info.xcmp1Val + 20U);
        }
    }
    if(epwm6_Info.epwmXCMP4Direction == EPWM_CMP_UP)
    {
        if(epwm6_Info.xcmp4Val < EPWM_MAX_XCMP4)
        {
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW3,
                                 epwm6_Info.xcmp4Val + 20U);
        }
        else
        {
            epwm6_Info.epwmXCMP4Direction = EPWM_CMP_DOWN;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW3, 
                                 epwm6_Info.xcmp4Val - 20U);
        }
    }
    else
    {
        if(epwm6_Info.xcmp4Val > EPWM_MIN_XCMP4)
        {
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW3,
                                 epwm6_Info.xcmp4Val - 20U);
        }
        else
        {
            epwm6_Info.epwmXCMP4Direction = EPWM_CMP_UP;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW3,
                                 epwm6_Info.xcmp4Val + 20U);
        }
    }
}

//
// Function to update XCMP1,4,5,8 based on their directions.
//
void updateShadow2_forEpwm6()
{
    if(epwm6_Info.epwmXCMP1Direction == EPWM_CMP_UP)
    {
        if(epwm6_Info.xcmp1Val < EPWM_MAX_XCMP1)
        {
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW2,
                                 epwm6_Info.xcmp1Val + 20U);
        }
        else
        {
            epwm6_Info.epwmXCMP1Direction = EPWM_CMP_DOWN;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW2,
                                 epwm6_Info.xcmp1Val - 20U);
        }
    }
    else
    {
        if(epwm6_Info.xcmp1Val > EPWM_MIN_XCMP1)
        {
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW2,
                                 epwm6_Info.xcmp1Val - 20U);
        }
        else
        {
            epwm6_Info.epwmXCMP1Direction = EPWM_CMP_UP;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW2,
                                 epwm6_Info.xcmp1Val + 20U);
        }
    }
    if(epwm6_Info.epwmXCMP4Direction == EPWM_CMP_UP)
    {
        if(epwm6_Info.xcmp4Val < EPWM_MAX_XCMP4)
        {
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW2,
                                 epwm6_Info.xcmp4Val + 20U);
        }
        else
        {
            epwm6_Info.epwmXCMP4Direction = EPWM_CMP_DOWN;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW2,
                                 epwm6_Info.xcmp4Val - 20U);
        }
    }
    else
    {
        if(epwm6_Info.xcmp4Val > EPWM_MIN_XCMP4)
        {
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW2,
                                 epwm6_Info.xcmp4Val - 20U);
        }
        else
        {
            epwm6_Info.epwmXCMP4Direction = EPWM_CMP_UP;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW2,
                                 epwm6_Info.xcmp4Val + 20U);
        }
    }
}

//
// Function to update XCMP1,4,5,8 based on their directions.
//
void updateShadow1_forEpwm6()
{

    if(epwm6_Info.epwmXCMP1Direction == EPWM_CMP_UP)
    {
        if(epwm6_Info.xcmp1Val < EPWM_MAX_XCMP1)
        {
            epwm6_Info.xcmp1Val += 20U;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW1,
                                 epwm6_Info.xcmp1Val);
        }
        else
        {
            epwm6_Info.epwmXCMP1Direction = EPWM_CMP_DOWN;
            epwm6_Info.xcmp1Val -= 20U;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW1,
                                 epwm6_Info.xcmp1Val);
        }
    }
    else
    {
        if(epwm6_Info.xcmp1Val > EPWM_MIN_XCMP1)
        {
            epwm6_Info.xcmp1Val -= 20U;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW1,
                                 epwm6_Info.xcmp1Val);
        }
        else
        {
            epwm6_Info.epwmXCMP1Direction = EPWM_CMP_UP;
            epwm6_Info.xcmp1Val += 20U;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP1_SHADOW1,
                                 epwm6_Info.xcmp1Val);
        }
    }
    if(epwm6_Info.epwmXCMP4Direction == EPWM_CMP_UP)
    {
        if(epwm6_Info.xcmp4Val < EPWM_MAX_XCMP4)
        {
            epwm6_Info.xcmp4Val += 20U;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW1,
                                 epwm6_Info.xcmp4Val);
        }
        else
        {
            epwm6_Info.epwmXCMP4Direction = EPWM_CMP_DOWN;
            epwm6_Info.xcmp4Val -= 20U;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW1,
                                 epwm6_Info.xcmp4Val);
        }
    }
    else
    {
        if(epwm6_Info.xcmp4Val > EPWM_MIN_XCMP4)
        {
            epwm6_Info.xcmp4Val -= 20U;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW1,
                                 epwm6_Info.xcmp4Val);
        }
        else
        {
            epwm6_Info.epwmXCMP4Direction = EPWM_CMP_UP;
            epwm6_Info.xcmp4Val += 20U;
            EPWM_setXCMPRegValue(epwm6_Info.epwmBase, EPWM_XCMP4_SHADOW1,
                                 epwm6_Info.xcmp4Val);
        }
    }
}

//
// Function to update XCMP1,4,5,8 based on their directions.
//
void updateShadow3_forEpwm8()
{
    if(epwm8_Info.epwmXCMP1Direction == EPWM_CMP_UP)
    {
        if(epwm8_Info.xcmp1Val < EPWM_MAX_XCMP1)
        {
            epwm8_Info.xcmp1Val += 20U;
            EPWM_setXCMPRegValue(epwm8_Info.epwmBase, EPWM_XCMP1_SHADOW3,
                                 epwm8_Info.xcmp1Val);
        }
        else
        {
            epwm8_Info.epwmXCMP1Direction = EPWM_CMP_DOWN;
            epwm8_Info.xcmp1Val -= 20U;
            EPWM_setXCMPRegValue(epwm8_Info.epwmBase, EPWM_XCMP1_SHADOW3,
                                 epwm8_Info.xcmp1Val);
        }
    }
    else
    {
        if(epwm8_Info.xcmp1Val > EPWM_MIN_XCMP1)
        {
            epwm8_Info.xcmp1Val -= 20U;
            EPWM_setXCMPRegValue(epwm8_Info.epwmBase, EPWM_XCMP1_SHADOW3,
                                 epwm8_Info.xcmp1Val);
        }
        else
        {
            epwm8_Info.epwmXCMP1Direction = EPWM_CMP_UP;
            epwm8_Info.xcmp1Val += 20U;
            EPWM_setXCMPRegValue(epwm8_Info.epwmBase, EPWM_XCMP1_SHADOW3,
                                 epwm8_Info.xcmp1Val);
        }
    }
    if(epwm8_Info.epwmXCMP4Direction == EPWM_CMP_UP)
    {
        if(epwm8_Info.xcmp4Val < EPWM_MAX_XCMP4)
        {
            epwm8_Info.xcmp4Val += 20U;
            EPWM_setXCMPRegValue(epwm8_Info.epwmBase, EPWM_XCMP4_SHADOW3,
                                    epwm8_Info.xcmp4Val);
        }
        else
        {
            epwm8_Info.epwmXCMP4Direction = EPWM_CMP_DOWN;
            epwm8_Info.xcmp4Val -= 20U;
            EPWM_setXCMPRegValue(epwm8_Info.epwmBase, EPWM_XCMP4_SHADOW3,
                                 epwm8_Info.xcmp4Val);
        }
    }
    else
    {
        if(epwm8_Info.xcmp4Val > EPWM_MIN_XCMP4)
        {
            epwm8_Info.xcmp4Val -= 20U;
            EPWM_setXCMPRegValue(epwm8_Info.epwmBase, EPWM_XCMP4_SHADOW3,
                                 epwm8_Info.xcmp4Val);
        }
        else
        {
            epwm8_Info.epwmXCMP4Direction = EPWM_CMP_UP;
            epwm8_Info.xcmp4Val += 20U;
            EPWM_setXCMPRegValue(epwm8_Info.epwmBase, EPWM_XCMP4_SHADOW3,
                                 epwm8_Info.xcmp4Val);
        }
    }
}

//
// End of File
//
