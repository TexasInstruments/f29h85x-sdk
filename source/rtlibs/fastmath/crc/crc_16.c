//#############################################################################
//! \file source/common/C/crc/crc_16.c
//!
//! \brief  16-bit CRC
// Test this with https://www.lddgo.net/en/encrypt/crc, Algorithm=CRC-16-XMODEM 
// (paste hex values without the '0x') for polynomial 0x1021 with 
// Initial value = 0
// or Algorithm=CRC-16-CCITT-FALSE with Initial value = FFFF
// For Polynomial 0x8005, use Algorithm=CRC-16-IBM for polynomial 0x8005 with 
// Initial value = 0, Bit reverse inputs 
// In cases where the inputs need to be bit-reversed
// The C LUT approach handles this through a Reflected table, without the 
// need to explicitly bit reverse the inputs prior to providing them to the 
// CRC compute - this is for the C LUT approach)
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
void CRC_run16BitTableLookupC(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the high byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator >> 8) ^ pInputVector[parity];
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

__attribute__((section("kernel_opt")))
void CRC_run16BitTableLookupC_16(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i+=2, parity+=2){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the high byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator >> 8) ^ pInputVector[parity+1];
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
		tableIndex  = (accumulator >> 8) ^ pInputVector[parity];
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

__attribute__((section("kernel_opt")))
void CRC_run16BitTableLookupC_32(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i+=4, parity+=4){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the high byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator >> 8) ^ pInputVector[parity+3];
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
		tableIndex  = (accumulator >> 8) ^ pInputVector[parity+2];
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
		tableIndex  = (accumulator >> 8) ^ pInputVector[parity+1];
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
		tableIndex  = (accumulator >> 8) ^ pInputVector[parity];
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run16BitReflectedTableLookupC(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the low byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator & 0x00FF) ^ pInputVector[parity];
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run16BitReflectedTableLookupC_16(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i+=2, parity+=2){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the low byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator & 0x00FF) ^ pInputVector[parity+1];
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
		tableIndex  = (accumulator & 0x00FF) ^ pInputVector[parity];
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run16BitReflectedTableLookupC_32(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint8_t *pInputVector = (uint8_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i+=4, parity+=4){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the low byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator & 0x00FF) ^ pInputVector[parity+3];
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
		tableIndex  = (accumulator & 0x00FF) ^ pInputVector[parity+2];
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
		tableIndex  = (accumulator & 0x00FF) ^ pInputVector[parity+1];
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
		tableIndex  = (accumulator & 0x00FF) ^ pInputVector[parity];
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

__attribute__((section("kernel_asm")))
void CRC_run16BitAsm(CRC_Handle hndCRC)
{
    uint32_t crc_config;		
	if(hndCRC->reflected == 0) {
		// D1[15]=8 (no bit reversing), D1[10:8]=7 (8b input data), D1[4:0]=15 (16b CRC polynomial)
		crc_config = 0x870f;
	} else {
		// D1[15]=0 (bit reversing), D1[10:8]=7 (8b input data), D1[4:0]=15 (16b CRC polynomial)
		crc_config = 0x070f;
	}
	// Save the CRC result, send the decremented byte count so that it is directly used in ASM DECB instruction.	
	hndCRC->crcResult = crc_asm((uint8_t *)hndCRC->pMsgBuffer, hndCRC->polynomial, crc_config, (hndCRC->nMsgBytes - 1),(uint16_t)hndCRC->seedValue);
    
}

__attribute__((section("kernel_asm")))
void CRC_run16BitAsm_16(CRC_Handle hndCRC)
{
    uint32_t crc_config;		
	if(hndCRC->reflected == 0) {
		// D1[15]=8 (no bit reversing), D1[10:8]=7 (8b input data), D1[4:0]=15 (16b CRC polynomial)
		crc_config = 0x870f;
	} else {
		// D1[15]=0 (bit reversing), D1[10:8]=7 (8b input data), D1[4:0]=15 (16b CRC polynomial)
		crc_config = 0x070f;
	}
	// Save the CRC result, send the decremented byte count so that it is directly used in ASM DECB instruction.	
	hndCRC->crcResult = crc_asm_16((uint16_t *)hndCRC->pMsgBuffer, hndCRC->polynomial, crc_config, (hndCRC->nMsgBytes - 1),(uint16_t)hndCRC->seedValue);
    
}

__attribute__((section("kernel_asm")))
void CRC_run16BitAsm_32(CRC_Handle hndCRC)
{
    uint32_t crc_config;		
	if(hndCRC->reflected == 0) {
		// D1[15]=8 (no bit reversing), D1[10:8]=7 (8b input data), D1[4:0]=15 (16b CRC polynomial)
		crc_config = 0x870f;
	} else {
		// D1[15]=0 (bit reversing), D1[10:8]=7 (8b input data), D1[4:0]=15 (16b CRC polynomial)
		crc_config = 0x070f;
	}
	// Save the CRC result, send the decremented byte count so that it is directly used in ASM DECB instruction.	
	hndCRC->crcResult = crc_asm_32((uint32_t *)hndCRC->pMsgBuffer, hndCRC->polynomial, crc_config, (hndCRC->nMsgBytes - 1),(uint16_t)hndCRC->seedValue);
    
}
// End of file
