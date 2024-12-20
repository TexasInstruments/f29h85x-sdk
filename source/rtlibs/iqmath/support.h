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
#ifndef __SUPPORTH__
#define __SUPPORTH__

#include "math.h"
#define __STATIC_INLINE static inline

/* Common value defines. */
#define q15_ln2          0x58b9
#define q13_pi           0x6488
#define q14_pi           0xc910
#define q14_halfPi       0x6488
#define q14_quarterPi    0x3244
#define q15_halfPi       0xc910
#define q15_quarterPi    0x6488
#define q15_invRoot2     0x5a82
#define q15_tanSmall     0x0021
#define q15_pointOne     0x0ccd
#define q15_oneTenth     0x0ccd
#define iq28_twoPi       0x6487ed51
#define iq29_pi          0x6487ed51
#define iq29_halfPi      0x3243f6a8
#define iq30_pi          0xc90fdaa2
#define iq30_halfPi      0x6487ed51
#define iq30_quarterPi   0x3243f6a8
#define iq31_halfPi      0xc90fdaa2
#define iq31_quarterPi   0x6487ed51
#define iq31_invRoot2    0x5a82799a
#define iq31_tanSmall    0x0020c49b
#define iq31_ln2         0x58b90bfc
#define iq31_twoThird    0x55555555
#define iq31_pointOne    0x0ccccccd
#define iq31_oneTenth    0x0ccccccd
#define iq31_one         0x7fffffff

//#if defined(__RTS_SUPPORT__)
//    #include "RTS_support.h"
//#elif defined(__IQMPYSW__)
//    #include "MPYSW_support.h"
//#elif defined(__IQMPY32_4XX__)
//    #include "MPY32_support.h"
//#elif defined(__IQMPY32_5XX__)
//    #include "MPY32_support.h"
//#else
// #include "MPYSW_support.h"
    // #error MUST DEFINE MULTIPLIER SUPPORT METHOD (__RTS_SUPPORT__, __IQMPYSW__, __IQMPY32_4XX__, __IQMPY32_5XX__).
    #include "RTS_support.h"
//#endif

#endif //__SUPPORTH__
