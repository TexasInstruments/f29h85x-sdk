//###########################################################################
//
// FILE:   ram_sbl_dpl_config.c
//
// TITLE:  Kernel DPL configuration that is based on ti_dpl_config.c
//         The only difference is the hard coded SSU LINK & STACK config depending on the device state
//         HS-FS: LINK1 & STACK1, HS-KP/SE: LINK2 & STACK2
//
//###########################################################################
// $TI Release:  $
// $Release Date:   $
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
#include "ram_sbl_nmi_handler.h"

extern packetInterface_t gPktIntf;

static inline __attribute__((always_inline))
void defaultNMIWrapper(void)
{
    Interrupt_defaultNMIHandler();
}

__attribute__((interrupt("RTINT")))
void kernelInterrupt_NMIHandler(void)
{
    if (gPktIntf.isInDataMode)
    {
        // Assuming NMI isn't related to the communication peripheral 
        const ErrorStatusPkt_t errPkt = 
        {
            .payloadType = (PayloadType)ErrorStatus,
            .errorMsgCode = 0x0001,              // error message decoded in comm_packet_protocol.h
            .recoveryStatus = RS_Unrecoverable,  
            .hasSprintfArgs = false,             
            .numArgs = 0U,                       
            .pArgsVal = NULL                     
        };
        //
        // send EOT packet
        //
        sblSendPacket(1, &errPkt);
    }    

    defaultNMIWrapper();
}