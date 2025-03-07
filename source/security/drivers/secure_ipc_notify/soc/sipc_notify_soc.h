
/*
 *  Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
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
#ifndef SIPC_NOTIFY_SOC_H_
#define SIPC_NOTIFY_SOC_H_

#ifdef __cplusplus
extern "C"
{
#endif


#if defined (SOC_AM263X)
#include <security/drivers/secure_ipc_notify/soc/am263x/sipc_notify_cfg.h>
#elif defined (SOC_AM263PX)
#include <security/drivers/secure_ipc_notify/soc/am263px/sipc_notify_cfg.h>
#elif defined (SOC_F29H85X)
#include <security/drivers/secure_ipc_notify/soc/f29h85x/sipc_notify_cfg.h>
#elif defined (SOC_AM261X)
#include <security/drivers/secure_ipc_notify/soc/am261x/sipc_notify_cfg.h>
#elif defined (SOC_AM273X)
#include <security/drivers/secure_ipc_notify/soc/am273x/sipc_notify_cfg.h>
#elif defined (SOC_AWR294X)
#include <security/drivers/secure_ipc_notify/soc/awr294x/sipc_notify_cfg.h>
#endif


#ifdef __cplusplus
}
#endif

#endif
