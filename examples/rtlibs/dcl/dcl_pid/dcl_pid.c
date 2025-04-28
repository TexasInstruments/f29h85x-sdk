//#############################################################################
//
//
// $Copyright:
//#############################################################################

#include "dcl_pid.h"
#include "device.h"

volatile const uint32_t testSize = NUM_ELEMENTS; 
int errors = 0;

//
// rk = Target referenced value
// yk = Current feedback value
// lk = Clamp control value
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

    //
    // Available PID controllers are:
    // - DCL_runPIDSeries
    // - DCL_runPIDParallel
    //
    PID_runTest(pid_controller, &DCL_runPIDSeries); 

    uint32_t avgCount = totalCount / testSize;
    printf("DCL PID total cycles = %d\nDCL PID average cycles = %d\n", totalCount, avgCount);
    while(1)
    {}
}

int PID_runTest(DCL_PID *ctrl_handle, DCL_PID_FUNC dcl_pid_func)
{   
    //
    // Define DFLOG pointers that will be used to access the data buffer
    //
    DCL_FDLOG rkBuf, ykBuf, lkBuf, outBuf, ctlBuf;

    //
    // Update controller parameters
    //
    PID_updateParams(ctrl_handle, PID_TESTCASE);

    //
    // Initialize Log pointers to the data buffer
    //
    DCL_initLog(&rkBuf, (float32_t*)rk_buffer, DATA_LENGTH);
    DCL_initLog(&ykBuf, (float32_t*)yk_buffer, DATA_LENGTH);
    DCL_initLog(&lkBuf, (float32_t*)lk_buffer, DATA_LENGTH);
    DCL_initLog(&outBuf, (float32_t*)out_buffer, DATA_LENGTH);
    DCL_initLog(&ctlBuf, (float32_t*)ctl_buffer, DATA_LENGTH);
    DCL_clearLog(&outBuf);

    for (int i = 0; i < testSize; i++)
    {   
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
        // Equivalent to uk = DCL_runPIDSeries(ctrl_handle, rk, yk, lk);
        //
        uk = (*dcl_pid_func)(ctrl_handle, rk, yk, lk); 

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
    for (int i = 0; i < testSize; i++)
    {
        float32_t output = DCL_readLog(&outBuf);   // out_buffer[i]
        float32_t expected = DCL_readLog(&ctlBuf); // ctl_buffer[i]
        if (!DCL_isZero(output - expected))
        {
            errors++;
            printf("FAIL at sample %d, outputs %f, should be %f\n", i, output, expected);
        }
    }

    printf("PID test produced %d error\n",errors);
      
    return errors;
}

bool PID_updateParams(DCL_PID *pid_ptr, uint32_t testCase)
{
    bool is_updated;
    float32_t targetbw_hz;

    switch (testCase) 
    {
        default:
        case 1:
            pid_ptr->sps->Kp = 0.1693591151f;
	        pid_ptr->sps->Ki = 0.0075683544f;
	        pid_ptr->sps->Kd = 0.0252412200f;
            pid_ptr->sps->Kr = 1.0f;
	        pid_ptr->css->T = (float32_t) 1/500;
	        pid_ptr->sps->Umax = 1.0f;
	        pid_ptr->sps->Umin = -1.0f;
            // Calculate and set the filter coefficients
            targetbw_hz = 45;

            break;
        case 2:
	        pid_ptr->sps->Kp = 1.8540138247f;
	        pid_ptr->sps->Ki = 0.0081723506f;
	        pid_ptr->sps->Kd = 0.0f;
            pid_ptr->sps->Kr = 1.0f;
	        pid_ptr->css->T = (float32_t) 1/2000;
	        pid_ptr->sps->Umax = 100.0f;
	        pid_ptr->sps->Umin = -100.0f;
            // Calculate and set the filter coefficients
            targetbw_hz = 1;

            break;
        case 3:
	        pid_ptr->sps->Kp = 2.50000f;
	        pid_ptr->sps->Ki = 0.01000f;
	        pid_ptr->sps->Kd = 0.05200f;
            pid_ptr->sps->Kr = 1.0f;
	        pid_ptr->css->T = (float32_t) 0.05;
	        pid_ptr->sps->Umax = 100.0f;
	        pid_ptr->sps->Umin = -100.0f;
            // Calculate and set the filter coefficients
            targetbw_hz = 8;     

            break;
    }
    DCL_setPIDfilterBW(pid_ptr, targetbw_hz);

    // Update PID params from SPS
    DCL_setUpdateStatus(pid_ptr);
    is_updated = DCL_updatePID(pid_ptr);

    // Reset internal controller values
    DCL_resetPID(pid_ptr);

    return is_updated;
}
