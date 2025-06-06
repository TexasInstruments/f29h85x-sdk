//#############################################################################
//
// FILE:   input_crc8.c
//
// TITLE:  
//
//
//#############################################################################

#include <stdint.h>
#include "crc_8_example.h"
#if (INPUT_TYPE==8)
__attribute__((location(0x20120000))) uint8_t test_input[NUM_BYTES] = {
0x01, 0x40, 0x02, 0x80, 0x03, 0xC0, 0x04, 0x00, 0x05, 0x40, 0x06, 0x80, 0x07, 0xC0, 0x08, 0x00,
0x09, 0x40, 0x0A, 0x80, 0x0B, 0xC0, 0x0C, 0x00, 0x0D, 0x40, 0x0E, 0x80, 0x0F, 0xC0, 0x10, 0x00,
0x11, 0x40, 0x12, 0x80, 0x13, 0xC0, 0x14, 0x00, 0x15, 0x40, 0x16, 0x80, 0x17, 0xC0, 0x18, 0x00,
0x19, 0x40, 0x1A, 0x80, 0x1B, 0xC0, 0x1C, 0x00, 0x1D, 0x40, 0x1E, 0x80, 0x1F, 0xC0, 0x20, 0x00,
0x21, 0x40, 0x22, 0x80, 0x23, 0xC0, 0x24, 0x00, 0x25, 0x40, 0x26, 0x80, 0x27, 0xC0, 0x28, 0x00,
0x29, 0x40, 0x2A, 0x80, 0x2B, 0xC0, 0x2C, 0x00, 0x2D, 0x40, 0x2E, 0x80, 0x2F, 0xC0, 0x30, 0x00,
0x31, 0x40, 0x32, 0x80, 0x33, 0xC0, 0x34, 0x00, 0x35, 0x40, 0x36, 0x80, 0x37, 0xC0, 0x38, 0x00,
0x39, 0x40, 0x3A, 0x80, 0x3B, 0xC0, 0x3C, 0x00, 0x3D, 0x40, 0x3E, 0x80, 0x3F, 0xC0, 0x40, 0x00,
}; 
#elif (INPUT_TYPE==16)
__attribute__((location(0x20120000))) uint16_t test_input[NUM_BYTES>>1] = {
0x0140, 0x0280, 0x03C0, 0x0400, 0x0540, 0x0680, 0x07C0, 0x0800,
0x0940, 0x0A80, 0x0BC0, 0x0C00, 0x0D40, 0x0E80, 0x0FC0, 0x1000,
0x1140, 0x1280, 0x13C0, 0x1400, 0x1540, 0x1680, 0x17C0, 0x1800,
0x1940, 0x1A80, 0x1BC0, 0x1C00, 0x1D40, 0x1E80, 0x1FC0, 0x2000,
0x2140, 0x2280, 0x23C0, 0x2400, 0x2540, 0x2680, 0x27C0, 0x2800,
0x2940, 0x2A80, 0x2BC0, 0x2C00, 0x2D40, 0x2E80, 0x2FC0, 0x3000,
0x3140, 0x3280, 0x33C0, 0x3400, 0x3540, 0x3680, 0x37C0, 0x3800,
0x3940, 0x3A80, 0x3BC0, 0x3C00, 0x3D40, 0x3E80, 0x3FC0, 0x4000,
}; 
#elif (INPUT_TYPE==32)
__attribute__((location(0x20120000))) uint32_t test_input[NUM_BYTES>>2] = {
0x01400280, 0x03C00400, 0x05400680, 0x07C00800,
0x09400A80, 0x0BC00C00, 0x0D400E80, 0x0FC01000,
0x11401280, 0x13C01400, 0x15401680, 0x17C01800,
0x19401A80, 0x1BC01C00, 0x1D401E80, 0x1FC02000,
0x21402280, 0x23C02400, 0x25402680, 0x27C02800,
0x29402A80, 0x2BC02C00, 0x2D402E80, 0x2FC03000,
0x31403280, 0x33C03400, 0x35403680, 0x37C03800,
0x39403A80, 0x3BC03C00, 0x3D403E80, 0x3FC04000,
}; 
#endif

// End of File
