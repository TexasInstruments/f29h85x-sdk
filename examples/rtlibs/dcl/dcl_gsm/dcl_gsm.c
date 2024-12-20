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

/*
 * This example illustrates the setup and use of the Gain Scheduler Module. The code makes no use of the device peripherals.
 * The example is configured to construct a y = x^2 target profile. Offsets and gains are
 * loaded into the SPS, and the update performed using the DCL_updateGSM() function. 
 * User can observe the GSM input-output curve by plotting the graph of the output buffer
*/
    
#include "dcl_gsm.h"

int main(void)
{
    Board_init();
    
    GSM_Routine();

    /* infinite loop */
    while(1)

    return 1;
}

void GSM_Routine(void)
{   
    float32_t dx, xk, yk;
    uint32_t i;

    //
    // Initialize Log pointers to the data buffer
    //
    DCL_FDLOG outBuf;
    DCL_initLog(&outBuf, (float32_t*)out_buffer, BUFFER_SIZE);
    DCL_clearLog(&outBuf);

	/* load GSM offset coefficients */
    xk = 0;
    for (i = 1; i <= GSM_N; i++)
    {
        xk += gain_module.h;
        gain_module.sps->c[i] = GSM_target_fn(xk);
    }

    //
    // load GSM gain table
    //
    DCL_loadGSMgains(&gain_module);
    DCL_updateGSMNoCheck(&gain_module);

    //
	// load input-output curve
    //
	dx = 2.2f / BUFFER_SIZE;
	for (xk = -1.1f; xk < 1.1f; xk += dx)
	{
		yk = DCL_runGSM(&gain_module, xk);
		DCL_writeLog(&outBuf, yk);
	}

}

/* target function for gain scheduler profile */
float32_t GSM_target_fn(float32_t x)
{
    return x*x;
}


