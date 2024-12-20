//#############################################################################
//
// FILE:   golden_crc16.c
//
// TITLE:  
//
//
//#############################################################################

#include <stdint.h>
// P1 is 0x8005
// For Polynomial 0x8005, use Algorithm=CRC-16-IBM for polynomial 0x8005 with Initial value = 0, Bit reverse inputs
// In cases where the inputs need to be bit-reversed
// The C LUT approach handles this through a Reflected table, without the 
// need to explicitly bit reverse the inputs prior to providing them to the CRC compute - this is for the C LUT approach)
// for the Asm approach, the architecture is able to be configured to bit reverse the inputs - so again, there is no need to explicitly bit reverse the inputs
const uint16_t test_golden_P1 = 0xF310;

// P2 is 0x1021
//  Test this with https://www.lddgo.net/en/encrypt/crc, Algorithm=CRC-16-XMODEM (paste hex values without the '0x') for polynomial 0x1021 with Initial value = 0
// or Algorithm=CRC-16-CCITT-FALSE with Initial value = FFFF
const uint16_t test_golden_P2 = 0x67FC;


// End of File
