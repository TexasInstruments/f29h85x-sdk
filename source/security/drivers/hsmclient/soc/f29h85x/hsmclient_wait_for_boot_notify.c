/*
 *  Copyright (c) 2025-24 Texas Instruments Incorporated
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
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdlib.h>
#include <stdint.h>
#include <inc/hw_types.h>
#include <security/drivers/hsmclient/hsmclient.h>

/********************************************************************************
 *                                  Macros
 ****************************************************************************** */
/* Register to read boot notify status */
#define READ_BOOT_NOTIFY_REG    (0x301804E4U)
/* Boot notify status indicating that HSM firmware is now running */
#define BOOT_NOTIFY_DONE_STATUS (0x5A5A5A5AU)

/*==============================================================================*
 *                          Public Function definition.
 *==============================================================================*/

int32_t HsmClient_waitForBootNotify(HsmClient_t* HsmClient, uint32_t timeout)
{
    int32_t status = SystemP_FAILURE;
    volatile uint32_t bootNotifyStatus = 0;
    (void) timeout;
    
    while(BOOT_NOTIFY_DONE_STATUS != bootNotifyStatus)
    {
        bootNotifyStatus = HWREG(READ_BOOT_NOTIFY_REG);
    }
    status = SystemP_SUCCESS;

    return status;
}
