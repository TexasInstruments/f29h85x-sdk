/*!****************************************************************************
 *  @file       _IQNmpy.c
 *  @brief      Functions to multiply two values of IQN type.
 *
 *  
 ******************************************************************************/
 /*
 *	Copyright (C) Texas Instruments Incorporated
 *
 *	All rights reserved not granted herein.
 *	Limited License.

 *	Texas Instruments Incorporated grants a world-wide, royalty-free,
 *	non-exclusive license under copyrights and patents it now or hereafter
 *	owns or controls to make, have made, use, import, offer to sell and sell ("Utilize")
 *	this software subject to the terms herein.  With respect to the foregoing patent
 *	license, such license is granted  solely to the extent that any such patent is necessary
 *	to Utilize the software alone.  The patent license shall not apply to any combinations which
 *	include this software, other than combinations with devices manufactured by or for TI ("TI Devices").
 *	No hardware patent is licensed hereunder.

 *	Redistributions must preserve existing copyright notices and reproduce this license (including the
 *	above copyright notice and the disclaimer and (if applicable) source code license limitations below)
 *	in the documentation and/or other materials provided with the distribution

 *	Redistribution and use in binary form, without modification, are permitted provided that the following
 *	conditions are met:

 *	  - No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any
 *		 software provided in binary form.
 *	  - Any redistribution and use are licensed by TI for use only with TI Devices.
 *	  - Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.

 *	If software source code is provided to you, modification and redistribution of the source code are permitted
 *	provided that the following conditions are met:
 *
 *	  - any redistribution and use of the source code, including any resulting derivative works, are licensed by
 *		TI for use only with TI Devices.
 *	  - any redistribution and use of any object code compiled from the source code and any resulting derivative
 *		works, are licensed by TI for use only with TI Devices.
 *
 *	Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or
 *	promote products derived from this software without specific prior written permission.

 *	DISCLAIMER.
 *
 *	THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 *	BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *	IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 *	OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef ti_iq_iqnmpy__include
#define ti_iq_iqnmpy__include
#include <stdint.h>

#include "support.h"

#if ((!defined (__IQMATH_USE_MATHACL__)) || (!defined (__MSPM0_HAS_MATHACL__)))
/**
 * @brief Multiply two values of IQN type.
 *
 * @param iqNInput1       IQN type value input to be multiplied.
 * @param iqNInput2       IQN type value input to be multiplied.
 * @param q_value         IQ format.
 *
 * @return                IQN type result of the multiplication.
 */
#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__IQNmpy)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
__STATIC_INLINE int_fast32_t __IQNmpy(int_fast32_t iqNInput1, int_fast32_t iqNInput2, const int8_t q_value)
{
    int_fast64_t iqNResult;
    
    iqNResult = (int_fast64_t)iqNInput1 * (int_fast64_t)iqNInput2;
    iqNResult = iqNResult >> q_value;

    return (int_fast32_t)iqNResult;
}
#else
/**
 * @brief Multiply two values of IQN type, using MathACL.
 *
 * @param iqNInput1       IQN type value input to be multiplied.
 * @param iqNInput2       IQN type value input to be multiplied.
 * @param q_value         IQ format.
 *
 * @return                IQN type result of the multiplication.
 */
#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__IQNmpy)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
__STATIC_INLINE int_fast32_t __IQNmpy(int_fast32_t iqNInput1, int_fast32_t iqNInput2, const int8_t q_value)
{
    /* write control */
    MATHACL->CTL = 6 | (q_value<<8) | (1 << 5);
    /* write operands to HWA */
    MATHACL->OP2 = iqNInput2;
    /* write trigger word last */
    MATHACL->OP1 = iqNInput1;
    /* read iqmpy product */
    return MATHACL->RES1;
}
#endif
#endif
