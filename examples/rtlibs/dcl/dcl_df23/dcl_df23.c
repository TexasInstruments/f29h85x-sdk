//#############################################################################
//
//
// $Copyright:
//#############################################################################

#include "dcl_df23.h"

volatile const uint32_t testSize = NUM_ELEMENTS; 
int errors = 0;

//
// ek = Servo error value
// uk = Output control effort
//
float32_t ek, uk;

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

  DF23_runTest(df23_controller);

  uint32_t avgCount = totalCount / testSize;
  printf("DCL DF23 total cycles = %d\nDCL DF23 average cycles = %d\n",
         totalCount, avgCount);
  while(1)
  {}
}

int DF23_runTest(DCL_DF23 *ctrl_handle) 
{
  //
  // Define DFLOG pointers that will be used to access the data buffer
  //
  DCL_FDLOG inBuf, outBuf, ctlBuf;
  DCL_resetDF23(ctrl_handle);

  //
  // Initialize Log pointers to the data buffer
  //
  DCL_initLog(&inBuf, (float32_t *)in_buffer, DATA_LENGTH);
  DCL_initLog(&outBuf, (float32_t *)out_buffer, DATA_LENGTH);
  DCL_initLog(&ctlBuf, (float32_t *)ctl_buffer, DATA_LENGTH);
  DCL_clearLog(&outBuf);

  int i;
  for (i = 0; i < testSize; i++) 
  {

    //
    // Read the input data buffers
    //
    ek = DCL_readLog(&inBuf);

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    // Prevent instructions to be optimized out of order
    __builtin_instrumentation_label("profiling_start");

    //
    // Run the controller
    // Note: DCL_runDF23() does not have an internal clamp
    //       Use DCL_runDF23Clamp(ctrl_handle, ek, max, min)
    //       instead if an internal clamp is needed.
    //       DCL also provides external clamp DCL_runClamp(*data, max, min)
    //
    uk = DCL_runDF23(ctrl_handle, ek);

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
  // Check output against reference output with tolerance
  //
  for (int i = 0; i < testSize; i++) 
  {
    float32_t output = DCL_readLog(&outBuf);   // out_buffer[i]
    float32_t expected = DCL_readLog(&ctlBuf); // ctl_buffer[i]
    if (!DCL_isZero(output - expected)) 
    {
      errors++;

      printf("FAIL at sample %d, outputs %f, should be %f\n", i, output,
             expected);
    }
  }

  printf("DF23 test produced %d error\n", errors);

  return errors;
}