//#############################################################################
//
// FILE:   buffdac_ex2_random.c
//
// TITLE:   Buffered DAC Random Output Example
//
//! \addtogroup driver_example_list
//! <h1> Buffered DAC Random </h1>
//!
//! This example generates random voltages on the buffered DAC output,
//! DACOUTA/ADCINA0 and uses the default DAC reference setting of
//! VDAC.
//!
//! \b External \b Connections \n
//!  - When the DAC reference is set to VDAC, an external reference voltage
//!    must be applied to the VDAC pin. This can accomplished by connecting a
//!    jumper wire from 3.3V to ADCINB0.
//!
//! \b Watch \b Variables \n
//!  - None.
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
#include <time.h>
#include <stdlib.h>
#include "board.h"

//
// Globals
//
uint16_t lowLimit = 410;
uint16_t highLimit = 3686;

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
    // Initialize a random time seed
    //
    srand(time(NULL));

    //
    // Configure the DAC module
    // Configure DAC - Setup the reference voltage and output value for the DAC
    //
    Board_init();

    //
    // Continuously set the DAC output value based on random value
    //
    while(1)
    {
        DAC_setShadowValue(myDAC0_BASE, ((rand() % (highLimit - lowLimit)) +
                                       lowLimit));
        DEVICE_DELAY_US(1);
    }
}

//
// End of File
//
