//#############################################################################
//
//
// $Copyright:
//#############################################################################

#include "dcl_nlpid.h"

//
// rk = Target referenced value
// yk = Current feedback value
// lk = External clamp flag
// uk = Output control effort
//
float32_t rk, yk, lk, uk;

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

  // Calculate the overhead of an empty timer
  CPUTimer_startTimer(CPUTIMER0_BASE);
  startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
  __builtin_instrumentation_label("overhead_start");
  endCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
  __builtin_instrumentation_label("overhead_end");
  overheadCount = startCounter - endCounter;
  CPUTimer_stopTimer(CPUTIMER0_BASE);

  NLPID_runTest(nlpid_controller);

  uint32_t avgCount = totalCount / NUM_ELEMENTS;
  printf("DCL NLPID total cycles = %d\nDCL NLPID average cycles = %d\n", totalCount,
         avgCount);
}

int NLPID_runTest(DCL_NLPID *ctrl_handle) {
  //
  // Define DFLOG pointers that will be used to access the data buffer
  //
  DCL_FDLOG rkBuf, ykBuf, lkBuf, outBuf, ctlBuf;

  //
  // update NLPID parameters
  //
  NLPID_updateParams(ctrl_handle);

  //
  // Initialize Log pointers to the data buffer
  //
  DCL_initLog(&rkBuf, (float32_t *)rk_buffer, DATA_LENGTH);
  DCL_initLog(&ykBuf, (float32_t *)yk_buffer, DATA_LENGTH);
  DCL_initLog(&lkBuf, (float32_t *)lk_buffer, DATA_LENGTH);
  DCL_initLog(&outBuf, (float32_t *)out_buffer, DATA_LENGTH);
  DCL_initLog(&ctlBuf, (float32_t *)ctl_buffer, DATA_LENGTH);
  DCL_clearLog(&outBuf);

  int i;
  for (i = 0; i < NUM_ELEMENTS; i++) {

    //
    // Read the input data buffers
    //
    rk = DCL_readLog(&rkBuf);
    yk = DCL_readLog(&ykBuf);
    lk = DCL_readLog(&lkBuf);

    CPUTimer_startTimer(CPUTIMER0_BASE);
    startCounter = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    // Prevent instructions to be optimized out of order
    __builtin_instrumentation_label("profiling_start");

    //
    // Run the controller
    //
    uk = DCL_runNLPIDSeries(ctrl_handle, rk, yk, lk);

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
  int errors = 0;
  for (i = 0; i < NUM_ELEMENTS; i++) {
    float32_t output = DCL_readLog(&outBuf);   // out_buffer[i]
    float32_t expected = DCL_readLog(&ctlBuf); // ctl_buffer[i]
    if (!DCL_isValue(output, expected)) {
      errors++;
      printf("FAIL at sample %d, outputs %f, should be %f\n", i, output,
             expected);
    }
  }
  printf("NLPID test produced %d error\n", errors);

  return errors;
}

bool NLPID_updateParams(DCL_NLPID *nlpid_ptr) {
  bool is_updated;

  nlpid_ptr->sps->Kp = 3.5f;
  nlpid_ptr->sps->Ki = 0.04f;
  nlpid_ptr->sps->Kd = 0.325f;
  nlpid_ptr->sps->alpha_p = 0.8f;
  nlpid_ptr->sps->alpha_i = 0.95f;
  nlpid_ptr->sps->alpha_d = 1.0f;
  nlpid_ptr->sps->delta_p = 0.15f;
  nlpid_ptr->sps->delta_i = 0.15f;
  nlpid_ptr->sps->delta_d = 0.15f;
  nlpid_ptr->sps->Umax = 0.5f;
  nlpid_ptr->sps->Umin = -0.25f;
  nlpid_ptr->css->T = 100.0e-06f;

  // Caclulate derivative LP filter coefficients in SPS (c1/c2)
  float32_t filterbw_hz = 40;
  DCL_setNLPIDfilterBW(nlpid_ptr, filterbw_hz);

  // Calculate and set the linearized gain variable in SPS (gamma_p/i/d)
  DCL_setNLPIDgamma(nlpid_ptr);

  // Update NLPID params from SPS
  DCL_setUpdateStatus(nlpid_ptr);
  is_updated = DCL_updateNLPID(nlpid_ptr);

  // Reset internal controller values
  DCL_resetNLPID(nlpid_ptr);

  return is_updated;
}
