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

#ifndef _DCL_C28_COMPATIBILITY_H_
#define _DCL_C28_COMPATIBILITY_H_

/**
 * 
 *  @{
 *  
 *  \file       dcl_c28_compatibility.h
 *  \brief      Contains backward compatbility mapping to C28 DCL's naming scheme
 *  \note       Not included in dcl.h by default, be sure to include this file seperately when needed.
 *
 *              Note:
 *              All C28 ASM functions will be alias into its equivalent C functions
 *
 *              CLA functions are not compatible, nonetheless its direct equivalent are listed in comments below
 */            

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// PI
//*****************************************************************************
#define DCL_runPI_C1      DCL_runPISeries       // C28 ASM function
#define DCL_runPI_C2      DCL_runPISeries          
#define DCL_runPI_C3      DCL_runPIParallel
#define DCL_runPI_C4      DCL_runPIParallel     // C28 ASM function
#define DCL_runPI_C5      DCL_runPIParallelEnhanced 
#define DCL_runPI_C6      DCL_runPISeriesTustin
#define DCL_runPI_C7      DCL_runPISeriesTustin // C28 ASM function
#define DCL_fupdatePI     DCL_updatePI          // C28 ASM function
/* 
// C28 CLA Functions
#define DCL_runPI_L1      DCL_runPISeries
#define DCL_runPI_L2      DCL_runPIParallel
#define DCL_runPI_L3      DCL_runPISeries
#define DCL_runPI_L4      DCL_runPIParallel
#define DCL_runPI_L5      DCL_runPISeriesTustin
*/

//*****************************************************************************
// PI2
//*****************************************************************************
#define DCL_runPI2_C1     DCL_runPI2Series
#define DCL_runPI2_C2     DCL_runPI2Series      // C28 ASM function
#define DCL_fupdatePI2    DCL_updatePI2         // C28 ASM function

//*****************************************************************************
// PID
//*****************************************************************************
#define DCL_runPID_C1     DCL_runPIDSeries      // C28 ASM function
#define DCL_runPID_C2     DCL_runPIDSeries  
#define DCL_runPID_C3     DCL_runPIDParallel
#define DCL_runPID_C4     DCL_runPIDParallel    // C28 ASM function
#define DCL_fupdatePID    DCL_updatePID         // C28 ASM function
/*
// C28 CLA Functions
#define DCL_runPID_L1     DCL_runPIDSeries
#define DCL_runPID_L2     DCL_runPIDParallel
#define DCL_runPID_L3     DCL_runPIDSeries
#define DCL_runPID_L4     DCL_runPIDParallel
*/

//*****************************************************************************
// NLPID
//*****************************************************************************
#define DCL_runNLPID_C1   DCL_runNLPIDParallel
#define DCL_runNLPID_C2   DCL_runNLPIDSeries 
#define DCL_runNLPID_C3   DCL_runNLPIDSeries    // C28 ASM function
#define DCL_runNLF_C1     DCL_runNLF 
#define DCL_calcGamma     DCL_getNLPIDgamma

//*****************************************************************************
// PID64 - 64 bit
//*****************************************************************************
#define DCL_runPIDF64_S1            DCL_runPIDF64Series

//*****************************************************************************
// DF11
//*****************************************************************************
#define DCL_runDF11_C1    DCL_runDF11           // C28 ASM function
#define DCL_runDF11_C2    DCL_runDF11
#define DCL_fupdateDF11   DCL_updateDF11        // C28 ASM function
/*
// C28 CLA Functions
#define DCL_runDF11_L1    DCL_runDF11
*/

//*****************************************************************************
// DF13
//*****************************************************************************
/*  
 *  Note that due to incompatible changes with running DF13 w/ Clamp, the legacy
 *  implementation for both DCL_runDF13_C5 and DCL_runDF13_C6 are still included. 
 *  
 *  It is advised to use the new function DCL_runDF13Clamp() for running DF13 w/ Clamp.
 *  For more info, refer to \details section of DCL_runDF13Clamp() in dcl_df13.h 
*/
#define DCL_runDF13_C1    DCL_runDF13           // C28 ASM function
#define DCL_runDF13_C2    DCL_runDF13_C5        // Alias into local implementation of legacy function C5
#define DCL_runDF13_C3    DCL_runDF13_C6        // Alias into local implementation of legacy function C6
#define DCL_runDF13_C4    DCL_runDF13
#define DCL_fupdateDF13   DCL_updateDF13        // C28 ASM function
/*
// C28 CLA Functions
#define DCL_runDF13_L1    DCL_runDF13
#define DCL_runDF13_L2    DCL_runDF13_C5
#define DCL_runDF13_L3    DCL_runDF13_C6
#define DCL_runDF13_L4    DCL_runDF13
#define DCL_runDF13_L5    DCL_runDF13_C5
#define DCL_runDF13_L6    DCL_runDF13_C6
*/

//*****************************************************************************
// DF22
//*****************************************************************************
#define DCL_runDF22_C1    DCL_runDF22               // C28 ASM function
#define DCL_runDF22_C2    DCL_runDF22PartialCompute // C28 ASM function
#define DCL_runDF22_C3    DCL_runDF22PartialUpdate  // C28 ASM function
#define DCL_runDF22_C4    DCL_runDF22               
#define DCL_runDF22_C5    DCL_runDF22PartialCompute
#define DCL_runDF22_C6    DCL_runDF22PartialUpdate  
#define DCL_fupdateDF22   DCL_updateDF22            // C28 ASM function
/*
// C28 CLA Functions
#define DCL_runDF22_L1    DCL_runDF22      
#define DCL_runDF22_L2    DCL_runDF22PartialCompute
#define DCL_runDF22_L3    DCL_runDF22PartialUpdate
#define DCL_runDF22_L4    DCL_runDF22
*/

//*****************************************************************************
// DF23
//*****************************************************************************
#define DCL_runDF23_C1    DCL_runDF23               // C28 ASM function
#define DCL_runDF23_C2    DCL_runDF23PartialCompute // C28 ASM function
#define DCL_runDF23_C3    DCL_runDF23PartialUpdate  // C28 ASM function
#define DCL_runDF23_C4    DCL_runDF23
#define DCL_runDF23_C5    DCL_runDF23PartialCompute
#define DCL_runDF23_C6    DCL_runDF23PartialUpdate
#define DCL_fupdateDF23   DCL_updateDF23            // C28 ASM function
/*
// C28 CLA Functions
#define DCL_runDF23_L1    DCL_runDF23     
#define DCL_runDF23_L2    DCL_runDF23PartialCompute
#define DCL_runDF23_L3    DCL_runDF23PartialUpdate
*/

//*****************************************************************************
// Clamp
//*****************************************************************************
#define DCL_runClamp_C1   DCL_runClamp              // C28 ASM function
#define DCL_runClamp_C2   DCL_runClamp
#define DCL_runClamp_S1   DCL_runClampF64
/*
// C28 CLA Functions
#define DCL_runClamp_L1   DCL_runClamp
*/

//*****************************************************************************
// Macro Functions
//*****************************************************************************
#define F32_IS_VALUE       DCL_isValue 
#define F64_IS_VALUE       DCL_isValueF64
#define F32_IS_ZERO        DCL_isZero
#define F64_IS_ZERO        DCL_isZeroF64
#define DCL_randf          DCL_rand
#define DCL_randf64        DCL_rand64
#define DCL_C2_LIMIT_32    DCL_c2Limit
#define DCL_C2_LIMIT_64    DCL_c2LimitF64
#define DCL_BREAK_POINT    DCL_setBreakPoint  
#define DCL_DISABLE_INTS   DCL_disableInts 
#define DCL_RESTORE_INTS   DCL_restoreInts 
#define DCL_SET_CONTROLLER_PERIOD   DCL_setControllerPeriod
#define DCL_SET_SAMPLE_RATE         DCL_setControllerPeriod
#define DCL_REQUEST_UPDATE          DCL_setUpdateStatus
#define DCL_CLEAR_UPDATE_REQUEST    DCL_clearUpdateStatus
#define DCL_UPDATE_WAITING          DCL_getUpdateStatus 
#define DCL_CONTROLLER_BEGIN        DCL_setControllerStatus
#define DCL_CONTROLLER_END          DCL_clearControllerStatus
#define DCL_CONTROLLER_IN_PROGRESS  DCL_getControllerStatus
#define DCL_SET_ERROR               DCL_setError
#define DCL_CLEAR_ERROR_CODE        DCL_clearError
#define DCL_RUN_ERROR_HANDLER       DCL_runErrorHandler
#define DCL_GET_ERROR_LOC           DCL_getErrorInfo

//*****************************************************************************
// Macro Constants
//*****************************************************************************
#define CONST_PI_32        CONST_PI
#define CONST_2PI_32       CONST_2PI
#define CONST_PI_64        CONST_PI_F64
#define CONST_2PI_64       CONST_2PI_F64
#define DCL_DEFAULT_T_F32  DCL_DEFAULT_PERIOD_S
#define DCL_DEFAULT_T_F64  DCL_DEFAULT_PERIODF64_S
#define DEFAULT_FPU32_TOL  DCL_FPU32_TOL
#define DEFAULT_FPU64_TOL  DCL_FPU64_TOL
#define NULL_ADDR          NULL

//*****************************************************************************
// FDLOG
//*****************************************************************************
#define DCL_createLog      DCL_initLog
#define FDLOG_SPACE        DCL_getLogRemain
#define FDLOG_SIZE         DCL_getLogSize
#define FDLOG_ELEMENT      DCL_getLogIndex
#define FDLOG_DEFAULT_SIZE 0x0400
typedef struct dcl_fdlog   FDLOG;
typedef struct dcl_mlog    MLOG;


//*****************************************************************************
// TCM
//*****************************************************************************
#define DCL_runITAE_C1     DCL_runITAE      // C28 ASM function
#define DCL_runITAE_C2     DCL_runITAE
#define DCL_runIAE_C1      DCL_runIAE       // C28 ASM function
#define DCL_runIAE_C2      DCL_runIAE
#define DCL_runIES_C1      DCL_runIES       // C28 ASM function
#define DCL_runIES_C2      DCL_runIES
typedef struct dcl_tcm            TCM;

//*****************************************************************************
// GSM
//*****************************************************************************
#define DCL_runGSM_C1      DCL_runGSM
#define DCL_fupdateGSM     DCL_updateGSM    // C28 ASM function

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_C28_COMPATIBILITY_H_
