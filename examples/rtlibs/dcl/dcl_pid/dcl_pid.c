/*
 * Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "dcl_pid.h"
    
int main(void)
{
    Board_init();
    
    //
    // Available PID controllers are:
    // - DCL_runPIDSeries
    // - DCL_runPIDParallel
    //
    PID_runTest(pid_controller, &DCL_runPIDSeries); 
}
        float32_t rk,yk,lk,uk;

int PID_runTest(DCL_PID *ctrl_handle, DCL_PID_FUNC dcl_pid_func)
{   
    //
    // Define DFLOG pointers that will be used to access the data buffer
    //
    DCL_FDLOG rkBuf, ykBuf, lkBuf, outBuf, ctlBuf;

    //
    // Update controller parameters and reset controller
    //
    PID_updateParams(ctrl_handle);
    DCL_resetPID(ctrl_handle);

    //
    // Initialize Log pointers to the data buffer
    //
    DCL_initLog(&rkBuf, (float32_t*)rk_buffer, DATA_LENGTH);
    DCL_initLog(&ykBuf, (float32_t*)yk_buffer, DATA_LENGTH);
    DCL_initLog(&lkBuf, (float32_t*)lk_buffer, DATA_LENGTH);
    DCL_initLog(&outBuf, (float32_t*)out_buffer, DATA_LENGTH);
    DCL_initLog(&ctlBuf, (float32_t*)ctl_buffer, DATA_LENGTH);
    DCL_clearLog(&outBuf);

    int i;
    for (i = 0; i < NUM_ELEMENTS; i++)
    {   
        //
        // rk = Target referenced value
        // yk = Current feedback value
        // uk = Output control effort
        //

        
        //
        // Read the input data buffers
        //
        rk = DCL_readLog(&rkBuf);
        yk = DCL_readLog(&ykBuf);
        lk = DCL_readLog(&lkBuf);

        //
        // Run the controller
        // Equivalent to uk = DCL_runPID_series(ctrl_handle, rk, yk, lk);
        //
        uk = (*dcl_pid_func)(ctrl_handle, rk, yk, lk); 

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
    for (i = 0; i < NUM_ELEMENTS; i++)
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

bool PID_updateParams(DCL_PID *pid_ptr)
{
    bool is_updated;
    float32_t targetbw_hz;

	pid_ptr->sps->Kp = 0.1693591151f;
	pid_ptr->sps->Ki = 0.0075683544f;
	pid_ptr->sps->Kd = 0.0252412200f;
    pid_ptr->sps->Kr = 1.0f;
	pid_ptr->css->T = (float32_t) 1/500;
	pid_ptr->sps->Umax = 1.0f;
	pid_ptr->sps->Umin = -1.0f;

    // Calculate and set the filter coefficients
    targetbw_hz = 45;
    DCL_setPIDfilterBW(pid_ptr, targetbw_hz);

    // Update NLPID params from SPS
    DCL_setUpdateStatus(pid_ptr);
    is_updated = DCL_updatePID(pid_ptr);

    // Reset internal controller values
    DCL_resetPID(pid_ptr);

    return is_updated;
}


