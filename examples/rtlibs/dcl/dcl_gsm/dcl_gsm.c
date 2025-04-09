//#############################################################################
//
//
// $Copyright:
//#############################################################################

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


