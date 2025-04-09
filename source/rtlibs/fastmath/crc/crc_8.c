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

__attribute__((section("kernel_opt")))
void CRC_run8BitTableLookupC_16(CRC_Handle hndCRC)
{
	uint32_t i;
	uint8_t tableIndex;
	uint8_t accumulator   = (uint8_t)hndCRC->seedValue;
	uint32_t parity        = (uint32_t)hndCRC->parity;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint8_t *pCrcTable    = (uint8_t *)hndCRC->pCrcTable;

	for(i = 0; i < hndCRC->nMsgBytes; i+=2, parity+=2){
		// low/high byte parity is not important in this case since it's an 8-bit CRC
		tableIndex = accumulator ^ pInputVector[parity+1];
		accumulator = pCrcTable[tableIndex];
		tableIndex = accumulator ^ pInputVector[parity];
		accumulator = pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)(accumulator & 0x00FF);
}

__attribute__((section("kernel_opt")))
void CRC_run8BitTableLookupC_32(CRC_Handle hndCRC)
{
	uint32_t i;
	uint8_t tableIndex;
	uint8_t accumulator   = (uint8_t)hndCRC->seedValue;
	uint32_t parity        = (uint32_t)hndCRC->parity;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint8_t *pCrcTable    = (uint8_t *)hndCRC->pCrcTable;

	for(i = 0; i < hndCRC->nMsgBytes; i+=4, parity+=4){
		// low/high byte parity is not important in this case since it's an 8-bit CRC
		tableIndex = accumulator ^ pInputVector[parity+3];
		accumulator = pCrcTable[tableIndex];
		tableIndex = accumulator ^ pInputVector[parity+2];
		accumulator = pCrcTable[tableIndex];
		tableIndex = accumulator ^ pInputVector[parity+1];
		accumulator = pCrcTable[tableIndex];
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

__attribute__((section("kernel_asm")))
void CRC_run8BitAsm_16(CRC_Handle hndCRC)
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
	hndCRC->crcResult = crc_asm_16((uint16_t *)hndCRC->pMsgBuffer, hndCRC->polynomial, crc_config, (hndCRC->nMsgBytes - 1),(uint8_t)hndCRC->seedValue);
    
}

__attribute__((section("kernel_asm")))
void CRC_run8BitAsm_32(CRC_Handle hndCRC)
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
	hndCRC->crcResult = crc_asm_32((uint32_t *)hndCRC->pMsgBuffer, hndCRC->polynomial, crc_config, (hndCRC->nMsgBytes - 1),(uint8_t)hndCRC->seedValue);
    
}

// End of file
