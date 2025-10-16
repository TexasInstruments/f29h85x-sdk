//#############################################################################
//
//   FILE:  DebugP_main.c
//
//   TITLE:
//
//#############################################################################
//  //
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

//#############################################################################

//
// Included Files
//
#include "board.h"
#include "ti_dpl_config.h"
#include "dpl_test.h"

//
// Main
//
int main(void)
{

    uint32_t myValue1, myValue2;

    Device_init();
    Board_init();
    Dpl_init();

    DebugP_logZoneEnable(DebugP_LOG_ZONE_ERROR);
    DebugP_logZoneEnable(DebugP_LOG_ZONE_WARN);
    DebugP_logZoneEnable(DebugP_LOG_ZONE_INFO);

    DebugP_log("\r\n..........\r\n");
    DebugP_log("[DPL] Hello world!  ...\r\n");
    DebugP_logError("[DPL] This is an error! \r\n");
    DebugP_logWarn("[DPL] This is a warning! \r\n");
    DebugP_logInfo("[DPL] This is some information! \r\n");

    DebugP_log("\r\n..........\r\n");

    uint32_t myLogZoneMask;
    DebugP_log("[DPL] Turning zone error off and repeating message \r\n");
    myLogZoneMask = DebugP_logZoneDisable(DebugP_LOG_ZONE_ERROR);
    DebugP_logError("[DPL] This is an error! \r\n");
    DebugP_logWarn("[DPL] This is a warning! \r\n");
    DebugP_logInfo("[DPL] This is some information! \r\n");

    DebugP_log("\r\n..........\r\n");

    DebugP_log("[DPL] Restore error zone, turn warn off, and repeat message \r\n");
    DebugP_logZoneRestore(myLogZoneMask);
    myLogZoneMask = DebugP_logZoneDisable(DebugP_LOG_ZONE_WARN);
    DebugP_logError("[DPL] This is an error! \r\n");
    DebugP_logWarn("[DPL] This is a warning! \r\n");
    DebugP_logInfo("[DPL] This is some information! \r\n");

    DebugP_log("\r\n..........\r\n");

    DebugP_log("[DPL] Log some values.............\r\n");
    myValue1 = 10ul;
    myValue2 = 20ul;
    DebugP_log("[DPL] Logging a uint32_t %d = myValue1 ... \r\n", myValue1);
    DebugP_log("[DPL] Logging two values %d = myValue1, %d = myValue2 !!!\r\n",
        myValue1, myValue2);

    DebugP_log("\r\n..........\r\n");

    DebugP_log("This is a log with a return in the middle and a tab \r\n"
               "\tThis text is after the return and tab \"this text is in quotes\".\r\n");

    DebugP_log("\r\n..........\r\n");

    DebugP_assert(myValue2 != 0);
    DebugP_assert(myValue2 >= 0);
    DebugP_logError("Checking assert.... Next line should fail! \r\n");
    DebugP_assert(myValue2 != 20ul);

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {
    }
}

//
// End of File
//
