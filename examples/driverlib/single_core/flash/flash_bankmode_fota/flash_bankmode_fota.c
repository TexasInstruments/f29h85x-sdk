//#############################################################################
//
// FILE:   flash_bankmode_fota.c
//
// TITLE:  Flash example for changing bankmode for FOTA
//
//! \addtogroup driver_example_list
//! <h1> FLASH </h1>
//!
//! This example programs the BANKMGMT sectors to change the bankmode in case of FOTA
//!
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - None
//!
//
//#############################################################################

//
//  Includes
//
#include "board.h"
#include "FlashTech_F29H85x_C29x.h"
#include "fota_bankmode.h"

//
//  Globals
//

//
//  Function definitions
//
//
//  main
//
int main(void)
{
    Fapi_StatusType retVal = Fapi_Status_Success;
    //
    //  Device Init
    //
    Device_init();
    //
    //  Board init
    //
    Board_init();
    //
    //  Interrupt Init
    //
    Interrupt_initModule();
    //
    //  Interrupt vector table init
    //
    Interrupt_initVectorTable();
    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();
    //
    //  Flash init
    //
    Flash_initModule(3U);
    //
    //  Bankmode change
    //
    retVal = Fota_SetBankMode(FOTA_BANKMODE_1);
    if(Fapi_Status_Success != retVal)
    {
        //
        //  Break here if bankmode change fails
        //
        ESTOP0;
    }
    else
    {
        //
        //  Do nothing
        //
    }
    //
    //  Wait forever
    //
    while(1U)
    {
        ;
    }
}