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
#ifndef __RTS_SUPPORTH__
#define __RTS_SUPPORTH__

#if defined (__TMS320C28XX__)
typedef int16_t int8_t;
typedef uint16_t uint8_t;
#endif
////////////////////////////////////////////////////////////
//                                                        //
//              MPY32 control functions.                  //
//                                                        //
////////////////////////////////////////////////////////////
#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpy_start)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline void __mpy_start(uint_fast16_t *ui16IntState, uint_fast16_t *ui16MPYState)
{
    /* Do nothing. */
    return;
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_start)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline void __mpyf_start(uint_fast16_t *ui16IntState, uint_fast16_t *ui16MPYState)
{
    /* Do nothing. */
    return;
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyfs_start)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline void __mpyfs_start(uint_fast16_t *ui16IntState, uint_fast16_t *ui16MPYState)
{
    /* Do nothing. */
    return;
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpy_clear_ctl0)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline void __mpy_clear_ctl0(void)
{
    /* Do nothing. */
    return;
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpy_set_frac)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline void __mpy_set_frac(void)
{
    /* Do nothing. */
    return;
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpy_stop)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline void __mpy_stop(uint_fast16_t *ui16IntState, uint_fast16_t *ui16MPYState)
{
    /* Do nothing. */
    return;
}

////////////////////////////////////////////////////////////
//                                                        //
//                16-bit functions                        //
//                                                        //
////////////////////////////////////////////////////////////
#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpy_w)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast16_t __mpy_w(int_fast16_t arg1, int_fast16_t arg2)
{
    return (arg1 * arg2);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpy_uw)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline uint_fast16_t __mpy_uw(uint_fast16_t arg1, uint_fast16_t arg2)
{
    return (arg1 * arg2);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyx_w)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast32_t __mpyx_w(int_fast16_t arg1, int_fast16_t arg2)
{
    return ((int_fast32_t)arg1 * (int_fast32_t)arg2);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyx_uw)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline uint_fast32_t __mpyx_uw(uint_fast16_t arg1, uint_fast16_t arg2)
{
    return ((uint_fast32_t)arg1 * (uint_fast32_t)arg2);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_w)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast16_t __mpyf_w(int_fast16_t arg1, int_fast16_t arg2)
{
    return (int_fast16_t)(((int_fast32_t)arg1 * (int_fast32_t)arg2) >> 15);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_w_reuse_arg1)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast16_t __mpyf_w_reuse_arg1(int_fast16_t arg1, int_fast16_t arg2)
{
    /* This is identical to __mpyf_w */
    return (int_fast16_t)(((int_fast32_t)arg1 * (int_fast32_t)arg2) >> 15);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_uw)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline uint_fast16_t __mpyf_uw(uint_fast16_t arg1, uint_fast16_t arg2)
{
    return (uint_fast16_t)(((uint_fast32_t)arg1 * (uint_fast32_t)arg2) >> 15);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_uw_reuse_arg1)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline uint_fast16_t __mpyf_uw_reuse_arg1(uint_fast16_t arg1, uint_fast16_t arg2)
{
    /* This is identical to __mpyf_uw */
    return (uint_fast16_t)(((uint_fast32_t)arg1 * (uint_fast32_t)arg2) >> 15);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyfx_w)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast32_t __mpyfx_w(int_fast16_t arg1, int_fast16_t arg2)
{
    return (((int_fast32_t)arg1 * (int_fast32_t)arg2) << 1);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyfx_uw)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast32_t __mpyfx_uw(uint_fast16_t arg1, uint_fast16_t arg2)
{
    return (((uint_fast32_t)arg1 * (uint_fast32_t)arg2) << 1);
}


////////////////////////////////////////////////////////////
//                                                        //
//                 32-bit functions                       //
//                                                        //
////////////////////////////////////////////////////////////
#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpy_l)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast32_t __mpy_l(int_fast32_t arg1, int_fast32_t arg2)
{
    return (arg1 * arg2);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpy_ul)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline uint_fast32_t __mpy_ul(uint_fast32_t arg1, uint_fast32_t arg2)
{
    return (arg1 * arg2);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyx)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast64_t __mpyx(int_fast32_t arg1, int_fast32_t arg2)
{
    return ((int_fast64_t)arg1 * (int_fast64_t)arg2);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyx_u)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline uint_fast64_t __mpyx_u(uint_fast32_t arg1, uint_fast32_t arg2)
{
    return ((uint_fast64_t)arg1 * (uint_fast64_t)arg2);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_l)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast32_t __mpyf_l(int_fast32_t arg1, int_fast32_t arg2)
{
    return (int_fast32_t)(((int_fast64_t)arg1 * (int_fast64_t)arg2) >> 31);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_l_reuse_arg1)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast32_t __mpyf_l_reuse_arg1(int_fast32_t arg1, int_fast32_t arg2)
{
    /* This is identical to __mpyf_l */
    return (int_fast32_t)(((int_fast64_t)arg1 * (int_fast64_t)arg2) >> 31);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_ul)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline uint_fast32_t __mpyf_ul(uint_fast32_t arg1, uint_fast32_t arg2)
{
    return (uint_fast32_t)(((uint_fast64_t)arg1 * (uint_fast64_t)arg2) >> 31);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyf_ul_reuse_arg1)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast32_t __mpyf_ul_reuse_arg1(uint_fast32_t arg1, uint_fast32_t arg2)
{
    /* This is identical to __mpyf_ul */
    return (uint_fast32_t)(((uint_fast64_t)arg1 * (uint_fast64_t)arg2) >> 31);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyfx)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline int_fast64_t __mpyfx(int_fast32_t arg1, int_fast32_t arg2)
{
    return (((int_fast64_t)arg1 * (int_fast64_t)arg2) << 1);
}

#if defined (__TI_COMPILER_VERSION__)
    #pragma FUNC_ALWAYS_INLINE(__mpyfx_u)
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__ICCARM__)
    #pragma inline=forced
#elif defined(__C29__)
    __attribute__((always_inline))    
#endif
static inline uint_fast64_t __mpyfx_u(uint_fast32_t arg1, uint_fast32_t arg2)
{
    return (((uint_fast64_t)arg1 * (uint_fast64_t)arg2) << 1);
}

#endif //__RTS_SUPPORTH__
