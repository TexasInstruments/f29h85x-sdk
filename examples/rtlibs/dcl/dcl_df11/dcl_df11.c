//#############################################################################
//
//
// $Copyright:
//#############################################################################

#include "dcl_df11.h"

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

int main(void) {
  // Timer configured in Sysconfig (Period set to 10s)
  Board_init();

  Dpl_init();

  // Calculate the overhead of an empty timer
  CycleCounterP_reset();
  __builtin_instrumentation_label("overhead_start");
  startCounter = CycleCounterP_getCount32();
  endCounter = CycleCounterP_getCount32();
  __builtin_instrumentation_label("overhead_end");
  overheadCount = endCounter - startCounter;

  DF11_runTest(df11_controller);

  uint32_t avgCount = totalCount / NUM_ELEMENTS;
  printf("DCL DF11 total cycles = %d\nDCL DF11 average cycles = %d\n", totalCount,
         avgCount);
}

int DF11_runTest(DCL_DF11 *ctrl_handle) {
  //
  // Define DFLOG pointers that will be used to access the data buffer
  //
  DCL_FDLOG inBuf, outBuf, ctlBuf;
  DCL_resetDF11(ctrl_handle);

  //
  // Initialize Log pointers to the data buffer
  //
  DCL_initLog(&inBuf, (float32_t *)in_buffer, DATA_LENGTH);
  DCL_initLog(&outBuf, (float32_t *)out_buffer, DATA_LENGTH);
  DCL_initLog(&ctlBuf, (float32_t *)ctl_buffer, DATA_LENGTH);
  DCL_clearLog(&outBuf);

  int i;
  for (i = 0; i < NUM_ELEMENTS; i++) {

    //
    // Read the input data buffers
    //
    ek = DCL_readLog(&inBuf);

    CycleCounterP_reset();
    
    // Prevent instructions to be optimized out of order
    __builtin_instrumentation_label("profiling_start");
    startCounter = CycleCounterP_getCount32();

    //
    // Run the controller
    //
    uk = DCL_runDF11(ctrl_handle, ek);

    endCounter = CycleCounterP_getCount32();
    __builtin_instrumentation_label("profiling_end");
    
    totalCount += endCounter - startCounter - overheadCount;

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
  int errors = 0;
  for (i = 0; i < NUM_ELEMENTS; i++) {
    float32_t output = DCL_readLog(&outBuf);   // out_buffer[i]
    float32_t expected = DCL_readLog(&ctlBuf); // ctl_buffer[i]
    if (!DCL_isZero(output - expected)) {
      errors++;

      printf("FAIL at sample %d, outputs %f, should be %f\n", i, output,
             expected);
    }
  }

  printf("DF11 test produced %d error\n", errors);

  return errors;
}