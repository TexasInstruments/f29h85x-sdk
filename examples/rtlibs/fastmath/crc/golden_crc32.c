//#############################################################################
//
// FILE:   golden_crc32.c
//
// TITLE:  
//
//
//#############################################################################

#include <stdint.h>
// P1 is 0x04C11DB7
// Test this with https://www.lddgo.net/en/encrypt/crc, Algorithm=CRC-32-MPEG2 (paste hex values without the '0x') for polynomial 0x04C11DB7 with Initial value = 0xFFFFFFFF
const uint32_t test_golden_P1 = 0xE8610DC1;

// P2 is 0x1EDC6F41
//  Test this with https://www.lddgo.net/en/encrypt/crc, use Algorithm=Custom with Polynomial 1EDC6F41 with Initial value = 0 , RefIn, RefOut unchecked, XOROUT = 0
const uint32_t test_golden_P2 = 0xA598634E;


// End of File
