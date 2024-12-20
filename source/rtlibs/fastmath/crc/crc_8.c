//#############################################################################
//! \file source/common/C/crc/crc_8.c
//!
//! \brief  8-bit CRC
// Test this with https://www.lddgo.net/en/encrypt/crc, Algorithm=CRC-8 
// (paste hex values without the '0x') for polynomial 0x07
// In cases where the inputs need to be bit-reversed
// The C LUT approach handles this through a Reflected table, without the 
// need to explicitly bit reverse the inputs prior to providing them to the CRC 
// compute - this is for the C LUT approach)
// for the Asm approach, the architecture is able to be configured to bit 
// reverse the inputs - so again, there is no need to explicitly bit reverse 
// the inputs
//#############################################################################
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

//*****************************************************************************
// includes
//*****************************************************************************
#include"vcu2_crc.h"
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************


//*****************************************************************************
// function definitions
//*****************************************************************************
__attribute__((section("kernel_opt")))
void CRC_run8BitTableLookupC(CRC_Handle hndCRC)
{
	uint32_t i;
	uint8_t tableIndex;
	uint8_t accumulator   = (uint8_t)hndCRC->seedValue;
	uint32_t parity        = (uint32_t)hndCRC->parity;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint8_t *pCrcTable    = (uint8_t *)hndCRC->pCrcTable;

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// low/high byte parity is not important in this case since it's an 8-bit CRC
		tableIndex = accumulator ^ pInputVector[parity];
		accumulator = pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)(accumulator & 0x00FF);
}


__attribute__((section("kernel_asm")))
void CRC_run8BitAsm(CRC_Handle hndCRC)
{
    uint32_t crc_config;		
	if(hndCRC->reflected == 0) {
		// D1[15]=8 (no bit reversing), D1[10:8]=7 (8b input data), D1[4:0]=7 (8b CRC polynomial)
		crc_config = 0x8707;
	} else {
		// D1[15]=0 (bit reversing), D1[10:8]=7 (8b input data), D1[4:0]=7 (8b CRC polynomial)
		crc_config = 0x0707;
	}
	// Save the CRC result, send the decremented byte count so that it is directly used in ASM DECB instruction.	
	hndCRC->crcResult = crc_asm((uint8_t *)hndCRC->pMsgBuffer, hndCRC->polynomial, crc_config, (hndCRC->nMsgBytes - 1),(uint8_t)hndCRC->seedValue);
    
}
	

// End of file
