//#############################################################################
//! \file source/common/C/crc/crc_24.c
//!
// In cases where the inputs need to be bit-reversed
// The C LUT approach handles this through a Reflected table, without the 
// need to explicitly bit reverse the inputs prior to providing them to the 
// CRC compute - this is for the C LUT approach)
// for the Asm approach, the architecture is able to be configured to bit 
// reverse the inputs - so again, there is no need to explicitly bit 
// reverse the inputs
//! \brief  24-bit CRC
//#############################################################################
//#############################################################################
//
//
// $Copyright:
//#############################################################################

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
void CRC_run24BitTableLookupC(CRC_Handle hndCRC)
{
	uint16_t i;
	uint32_t tableIndex;
	uint16_t parity        = hndCRC->parity;
	uint32_t accumulator   = hndCRC->seedValue;
	uint32_t *pInputVector = (uint32_t *)hndCRC->pMsgBuffer;
	uint32_t *pCrcTable    = (uint32_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 32-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D01_|_D02_|
	// 0x0001 |_D03_|_D04_|
	// 0x0002 |_D11_|_D12_|
	// 0x0003 |_D13_|_D14_|
	// 0x0004 |_D21_|_D22_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the high byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		// High byte of [23:0] of the Accumulator after bitwise ANDing with 0x00FFFFFF
		tableIndex  = ((accumulator & 0x00FFFFFF)>> 16) ^ __byte((int *)pInputVector, parity);
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator & 0x00FFFFFF;
}

void CRC_run24BitReflectedTableLookupC(CRC_Handle hndCRC)
{
	uint16_t i;
	uint32_t tableIndex;
	uint16_t parity        = hndCRC->parity;
	uint32_t accumulator   = hndCRC->seedValue;
	uint32_t *pInputVector = (uint32_t *)hndCRC->pMsgBuffer;
	uint32_t *pCrcTable    = (uint32_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 32-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D01_|_D02_|
	// 0x0001 |_D03_|_D04_|
	// 0x0002 |_D11_|_D12_|
	// 0x0003 |_D13_|_D14_|
	// 0x0004 |_D21_|_D22_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the low byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator & 0x000000FF) ^ __byte((int *)pInputVector, parity);
		accumulator = ((accumulator >> 8) ^ pCrcTable[tableIndex]);
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}
// End of file
