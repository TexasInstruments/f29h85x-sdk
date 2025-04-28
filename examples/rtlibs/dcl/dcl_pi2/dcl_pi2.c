//#############################################################################
//
//
// $Copyright:
//#############################################################################

#include "dcl_pi2.h"

volatile const uint32_t testSize = NUM_ELEMENTS; 
int errors = 0;

//
// rk = Target referenced value
// yk = Current feedback value
// uk = Output control effort
//
float32_t rk, yk, uk;

//
// profiling variables
//
uint32_t startCounter = 0;
uint32_t endCounter = 0;
uint32_t overheadCount = 0;
uint32_t totalCount = 0;

int main(void) 
{
  // Timer configured in Sysconfig (Period set to 10s)
  Board_init();

  // Calculate the overhead of an empty timer
  CPUTimer_startTimer(CPUTIMER0_BASE);
  startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
  __builtin_instrumentation_label("overhead_start");
  endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
  __builtin_instrumentation_label("overhead_end");
  overheadCount = startCounter - endCounter;
  CPUTimer_stopTimer(CPUTIMER0_BASE);

  PI2_runTest(pi2_controller);

  uint32_t avgCount = totalCount / testSize;
  printf("DCL PI2 total cycles = %d\nDCL PI2 average cycles = %d\n", totalCount,
         avgCount);
  while(1)
  {}
}

int PI2_runTest(DCL_PI2 *ctrl_handle) 
{
  //
  // Define DFLOG pointers that will be used to access the data buffer
  //
  DCL_FDLOG rkBuf, ykBuf, outBuf, ctlBuf;
  DCL_resetPI(ctrl_handle);

  //
  // Initialize Log pointers to the data buffer
  //
  DCL_initLog(&rkBuf, (float32_t *)rk_buffer, DATA_LENGTH);
  DCL_initLog(&ykBuf, (float32_t *)yk_buffer, DATA_LENGTH);
  DCL_initLog(&outBuf, (float32_t *)out_buffer, DATA_LENGTH);
  DCL_initLog(&ctlBuf, (float32_t *)ctl_buffer, DATA_LENGTH);
  DCL_clearLog(&outBuf);

  for (int i = 0; i < testSize; i++) 
  {
    //
    // Read the input data buffers
    //
    rk = DCL_readLog(&rkBuf);
    yk = DCL_readLog(&ykBuf);

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    // Prevent instructions to be optimized out of order
    __builtin_instrumentation_label("profiling_start");

    //
    // Run the controller
    // Equivalent to uk = DCL_runPI_series(ctrl_handle, rk, yk);
    //
    uk = DCL_runPI2Series(ctrl_handle, rk, yk);

    __builtin_instrumentation_label("profiling_end");
    endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    totalCount += startCounter - endCounter - overheadCount;
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // Write the results to the output buffer
    //
    DCL_writeLog(&outBuf, uk);
  }

  //
  // Reset the log pointer so it starts from the beginning
  //
  DCL_resetLog(&outBuf);

  //
  // Check output against expected output with tolerance (1e-06)
  //
  for (int i = 0; i < testSize; i++) {
    float32_t output = DCL_readLog(&outBuf);   // out_buffer[i]
    float32_t expected = DCL_readLog(&ctlBuf); // ctl_buffer[i]
    if (!DCL_isZero(output - expected)) {
      errors++;

      printf("FAIL at sample %d, outputs %f, should be %f\n", i, output,
             expected);
    }
  }

  printf("PI2 test produced %d error\n", errors);

  return errors;
}
