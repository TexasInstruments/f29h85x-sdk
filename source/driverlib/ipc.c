//###########################################################################
//
// FILE:   ipc.c
//
// TITLE:  C29x IPC driver.
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

#include "ipc.h"

//*****************************************************************************
//
// IPC_sendCommand
//
//*****************************************************************************
bool IPC_sendCommand(IPC_Channel_t ipcChannel, uint32_t flags,
                     uint32_t command, uint32_t addr, uint32_t data)
{
    bool ret;

    //
    // Check whether the flags are not busy
    //
    if((HWREG(IPC_REG_FLG(ipcChannel)) & flags) == 0U)
    {
        ret = true;

        //
        // Update the command registers
        //
        HWREG(IPC_REG_SENDCOM(ipcChannel))  = command;
        HWREG(IPC_REG_SENDDATA(ipcChannel)) = data;
        HWREG(IPC_REG_SENDADDR(ipcChannel)) = addr;

        //
        // Set the flags to indicate the remote core
        //
        HWREG(IPC_REG_SET(ipcChannel)) = flags;
    }
    else
    {
        ret = false;
    }

    return(ret);
}

//*****************************************************************************
//
// IPC_readCommand
//
//*****************************************************************************
bool IPC_readCommand(IPC_Channel_t ipcChannel, uint32_t flags,
                     uint32_t *command, uint32_t *addr, uint32_t *data)
{
    bool ret;
    uint32_t addrReg;

    //
    // Check whether the flags are not empty
    //
    if((HWREG(IPC_REG_STS(ipcChannel)) & flags) != 0U)
    {
        ret = true;

        //
        // Read the command registers
        //
        *command = HWREG(IPC_REG_RECVCOM(ipcChannel));
        *addr    = HWREG(IPC_REG_RECVADDR(ipcChannel));
        *data    = HWREG(IPC_REG_RECVDATA(ipcChannel));
    }
    else
    {
        ret = false;
    }

    return(ret);
}