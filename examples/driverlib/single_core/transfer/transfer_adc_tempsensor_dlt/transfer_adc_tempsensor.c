//#############################################################################
//
// FILE:   transfer_adc_tempsensor_dlt.c
//
// TITLE:  Sample temperature sensor and convert to temperature
//         Visualize using DLT Tool through GUI Composer
//
//! \addtogroup driver_example_list
//! <h1>ADC Temperature Sensor Conversion</h1>
//!
//! This example sets up the ePWM to periodically trigger the ADC.  The
//! ADC converts the internal connection to the temperature sensor,
//! which is then interpreted as a temperature by calling the
//! ADC_getTemperatureC() function.
//! Leverages DLT to data log variables and using DLT tool for 
//! Visualization
//! To enable this example, make sure to go to
//! Build -> Variables and set GUI_SUPPORT to value of 1 and DLT_SUPPORT to 1
//! This will create the GUI in CCS which can be opened by going to
//! View -> Plugins -> adc_tempsensor_dlt
//! If there are no plugins after buliding, 
//! please reload the window by doing Help -> Reload Window
//! Please select the correct COM port in the GUI by clicking "Options"
//! then "Serial Port Settings"
//! \b Watch \b Variables \n
//! - \b sensorSample - The raw reading from the temperature sensor
//! - \b sensorTemp   - The interpretation of the sensor sample as a temperature
//!                     in degrees Celsius.
//
//#############################################################################
//
//
// $Copyright:
//#############################################################################
//

//
// Included Files
//
#include "board.h"
#include "export/export_log.h"
#include "dlt/export_dltpackage.h"
#include "bitfield_structs.h"

//
// Globals
//
uint16_t sensorSample;
int16_t sensorTemp;
uint16_t empty_dlt_fifo = 0;

//
// Function Prototypes
//
void initEPWM(void);

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
    // Board Initialization
    //  - Configure and power up ADCA.
    //  - Configure ADC's SOC0 to be triggered by ePWM1.
    //  - Enable the temperature sensor and give it 500 us to power up
    //  - Enable ADC interrupt
    //  - Signal Mode           : single-ended
    //  - Conversion Resolution : 12-bit;
    //
    Board_init();

    //
    // Set up the ePWM
    //
    initEPWM();

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Start ePWM1, enabling SOCA and putting the counter in up-count mode
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

    //
    // Loop indefinitely
    //
    while(1)
    {
        uint32_t dlt_packet[2] = {0,0};

        while (empty_dlt_fifo && DLT_getFIFOWordStatus())
        {
            //
            // Export data to GUI via UART
            //
            dlt_packet[1] = CPU1DLTFifoRegs.FIFO_BUF_L;
            dlt_packet[0] = CPU1DLTFifoRegs.FIFO_BUF_H;
            EXPORTDLTLOG_logUint32Array(dlt_packet, 2);
            
            if(DLT_getFIFOWordStatus() == 0)
            {
                //
                // Start DLT log when FIFO is empty
                //
                empty_dlt_fifo = 0;
            }
        }
        
    }
}

//
// initEPWM - Function to configure ePWM1 to generate the SOC.
//
void initEPWM(void)
{
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //
    // Set the compare A value to 1000 and the period to 1999
    // Assuming ePWM clock is 100MHz, this would give 50kHz sampling
    // 50MHz ePWM clock would give 25kHz sampling, etc. 
    // The sample rate can also be modulated by changing the ePWM period
    // directly (ensure that the compare A value is less than the period). 
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 1000);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 1999);

    //
    // Set the local ePWM module clock divider to /1
    //
    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_128,
                           EPWM_HSCLOCK_DIVIDER_14);

    //
    // Freeze the counter
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// adcA1ISR - ADC A Interrupt 1 ISR
// 
void adcA1ISR(void)
{
    //
    // Create Start Tag/Marker for DLT
    //
    __builtin_c29_datalog_tag(0x05);

    //
    // Read the raw result
    //
    sensorSample = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    //
    // Datalog sample
    //
    __builtin_c29_datalog_write(sensorSample);

    //
    // Convert the result to a temperature in degrees C
    //
    sensorTemp = ADC_getTemperatureC(sensorSample, ADC_REFERENCE_INTERNAL, 3.3f);

    //
    // Datalog temperature
    //
    __builtin_c29_datalog_write(sensorTemp);

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    
    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    }
    
}

//
// DLT ISR export data when data logging level is reached
//
void INT_myDLT_ISR(void)
{
    //
    // Stop data logging after reaching
    // FIFO trigger count
    //
    __builtin_c29_datalog_tag(0x20);
    empty_dlt_fifo = 1;
    //
    // Clear DLT Interrupt events to receive more
    //
    DLT_clearEvent(DLT_INT_FIFO_TRIG | DLT_INT_INT);
}