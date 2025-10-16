/********************************************************************
 * Copyright (c) 2025 Texas Instruments Incorporated.
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
 *
*/

#ifndef CSLR_SM3_H_
#define CSLR_SM3_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <security/drivers/hw_include/cslr.h>


/**
 *  Structure type to access the EIP52 SM3 Header file.
 */
typedef volatile struct CSL_EIP52_SM3Regs_t
{
    uint32_t SM3_DATA_IN[16U];      /**< 0x0000-0x003C:Data Input Register               */
    uint32_t SM3_IO_BUF_CTRL_STAT;  /**< 0X0040 : Control and status Register            */
    uint32_t SM3_MODE_IN;           /**< 0x0044 : Mode Configuration Register            */
    uint32_t SM3_LENGTH_IN_0;        /**< 0x0048-0X004C:Block Length Register             */
    uint32_t SM3_LENGTH_IN_1;
    uint32_t SM3_DIGEST_IN[8U];     /**<0X0050-0X006C:contains the inner hash digest data*/
    uint32_t SM3_DIGEST_OUT[8U];    /**<0X0070-0X008C:contains the outer hash digest data*/
    uint32_t RESERVED[26];         
    uint32_t SM3_CONFIG;            /**< 0x00F8 : Configuration register                 */
    uint32_t SM3_VERSION;           /**< 0x00FC : Version register                       */
    uint32_t SM3_SYSCONFIG;         /**< 0x0100 : System Configuration Register          */
    uint32_t SM3_IRQSTATUS;             /**< 0x0104 : Interrupt Request Register             */
    uint32_t SM3_IRQENABLE;             /**< 0x0108 : Interrupt Enable Register              */
}CSL_EIP52_SM3Regs;

/**************************************************************************
* Register Macros
**************************************************************************/

#ifdef __cplusplus
}
#endif
#endif





