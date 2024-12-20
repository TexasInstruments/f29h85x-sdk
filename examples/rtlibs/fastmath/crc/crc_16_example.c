//#############################################################################
//
// FILE:   crc_16_example.c
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
#include <crc_16_example.h>
#include "vcu2_types.h"
#include "vcu2_crc.h"
#include "crctable0x8005.h"
#include "crctable0x8005reflected.h"
#include "crctable0x1021reflected.h"
#include "crctable0x1021.h"


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
extern const uint16_t test_golden_P1;
extern const uint16_t test_golden_P2;

__attribute__((location(0x200E0000))) uint16_t test_output;

//*****************************************************************************
// function definitions
//*****************************************************************************
int32_t main(void)
{
    // Locals
    int16_t i, j;
    // P1 is 0x8005
    uint16_t crcResultC_P1;
    uint16_t crcResultAsm_P1;
    // P2 is 0x1021
    uint16_t crcResultC_P2;
    uint16_t crcResultAsm_P2;
    
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
    
    // Configure the CRC object for Polynomial 1
    printf("Configuring CRC object...\n");
    CRC.seedValue    = INIT_CRC16;
    CRC.nMsgBytes    = NUM_BYTES;
    CRC.parity       = CRC_parity_even;
    CRC.crcResult    = 0;
    CRC.pMsgBuffer   = (uint8_t *)&test_input[0];
    CRC.pCrcTable    = (uint8_t *)&crc16P1TableReflected[0];
    //CRC.init         = (void (*)(void *))CRC_init8Bit;
    CRC.run          = (void (*)(void *))CRC_run16BitReflectedTableLookupC;
    CRC.polynomial   = POLYNOMIAL16P1;
    CRC.reflected    = 1;

    // Run the 16-bit LUT C CRC routine and save the result
    printf("Computing 16-bit LUT CRC on Polynomial P1...\n");
    //CRC.init(handleCRC);
    
    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    CRC.run(handleCRC);
    crcResultC_P1 = CRC.crcResult;

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    printf("CRC-16 C Cycles for Polynomial 1 = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);

    // Reset a few elements of the CRC object
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run16BitAsm;

    // Run the 16-bit Asm CRC routine and save the result
    printf("Computing 16-bit Asm CRC on Polynomial 1...\n");

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    CRC.run(handleCRC);
    crcResultAsm_P1     = CRC_bitReflect(CRC.crcResult,16);

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    printf("CRC-16 Asm Cycles for Polynomial 1 = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);

    ///////////////////////////// DONE WITH POLYNOMIAL 1 ///////////

    // Configure the CRC object for Polynomial 2
    CRC.pCrcTable    = (uint16_t *)&crc16P2Table[0];
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run16BitTableLookupC;
    CRC.polynomial   = POLYNOMIAL16P2;
    CRC.reflected    = 0;

    // Run the 16-bit LUT C CRC routine and save the result
    printf("Computing 16-bit LUT CRC on Polynomial P2...\n");

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    CRC.run(handleCRC);
    crcResultC_P2 = CRC.crcResult;

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    printf("CRC-16 C Cycles for Polynomial 2 = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);

    // Reset a few elements of the CRC object
    CRC.crcResult    = 0;
    CRC.run          = (void (*)(void *))CRC_run16BitAsm;

    // Run the 16-bit Asm CRC routine and save the result
    printf("Computing 16-bit Asm CRC on Polynomial 2...\n");

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    CRC.run(handleCRC);
    crcResultAsm_P2     = CRC.crcResult;

    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    differenceCounter = startCounter - endCounter - overheadCounter;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    printf("CRC-16 Asm Cycles for Polynomial 2 = %d, Timer overhead = %d \n", differenceCounter, overheadCounter);


    printf("Comparing results with Expected/Golden CRC...\n");
    (test_golden_P1 == crcResultC_P1)? pass++ : fail++;
    (test_golden_P1 == crcResultAsm_P1)? pass++ : fail++;

    (test_golden_P2 == crcResultC_P2)? pass++ : fail++;
    (test_golden_P2 == crcResultAsm_P2)? pass++ : fail++;

    printf("Completed CRC-16 Pass_count = %d, Fail_count = %d \n", pass, fail);
    printf("Computed CRC in C for Polynomial P1 = 0x%04x  Polynomial P2 = 0x%04x \n", crcResultC_P1, crcResultC_P2);
    printf("Computed CRC in Asm for Polynomial P1 = 0x%04x  Polynomial P2 = 0x%04x \n", crcResultAsm_P1, crcResultAsm_P2);    
}

// End of File
