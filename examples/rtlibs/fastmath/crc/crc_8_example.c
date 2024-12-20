//#############################################################################
//
// FILE:   crc_8_example.c
//
// TITLE:  
// The API is F28x compatible
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <math.h>

#include "device.h"
#include <crc_8_example.h>
#include "vcu2_types.h"
#include "vcu2_crc.h"
#include "crctable0x7.h"

//*****************************************************************************
// defines
//*****************************************************************************
 
//*****************************************************************************
// globals
//*****************************************************************************
// The global pass, fail values
int16_t pass = 0U, fail = 0U;

// profiling variables
uint32_t differenceCounter=0;
uint32_t startCounter=0;
uint32_t endCounter=0;
uint32_t overheadCounter=0;

// CRC object
CRC_Obj    CRC;

// Handle to the object
CRC_Handle handleCRC = &CRC;

// test input, output, golden (expected output) arrays
extern uint8_t test_input[];
extern const uint8_t test_golden;

__attribute__((location(0x200E0000))) uint8_t test_output;

//*****************************************************************************
// function definitions
//*****************************************************************************
int32_t main(void)
{
    // Locals
    int16_t i, j;
    uint8_t crcResultC;
    uint8_t crcResultAsm;
    
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    // Timer configuration for profiling (Period set to 10s)
    CPUTimer_setPeriod(CPUTIMER0_BASE, 200 * 10000000);
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    overheadCounter = startCounter - endCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    // Configure the CRC object
    printf("Configuring CRC object...\n");
    CRC.seedValue    = INIT_CRC8;
    CRC.nMsgBytes    = NUM_BYTES;
    CRC.parity       = CRC_parity_even;
    CRC.crcResult    = 0;
    CRC.pMsgBuffer   = (uint8_t *)&test_input[0];
    CRC.pCrcTable    = (uint8_t *)&crc8Table[0];
    //CRC.init         = (void (*)(void *))CRC_init8Bit;
    CRC.run          = (void (*)(void *))CRC_run8BitTableLookupC;
    CRC.polynomial   = POLYNOMIAL8;
    CRC.reflected    = 0;

    // Run the 8-bit LUT C CRC routine and save the result
    printf("Computing 8-bit LUT CRC...\n");
    //CRC.init(handleCRC);
    
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    CRC.run(handleCRC);
    crcResultC = CRC.crcResult;

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    printf("CRC-8 C Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);
    
    // Reset a few elements of the CRC object
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run8BitAsm;

    // Run the 8-bit Asm CRC routine and save the result
    printf("Computing 8-bit Asm CRC...\n");
    
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    CRC.run(handleCRC);
    crcResultAsm     = CRC.crcResult;

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    printf("CRC-8 Asm Cycles = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);

    printf("Comparing results with Expected/Golden CRC...\n");
    (test_golden == crcResultC)? pass++ : fail++;
    (test_golden == crcResultAsm)? pass++ : fail++;

    printf("Completed CRC-8 Pass_count = %d, Fail_count = %d \n", pass, fail);
    
}

// End of File
