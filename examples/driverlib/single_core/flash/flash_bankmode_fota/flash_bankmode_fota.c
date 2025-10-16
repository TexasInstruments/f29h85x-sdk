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