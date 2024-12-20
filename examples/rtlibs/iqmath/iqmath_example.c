//############################################################################
//
// FILE:    iqmath_example.c
//
// TITLE:  iqmath_example, allows testing the iqmath fixed-point library
// specify the GLOBAL_Q (i.e. the Q format)
// It will print statements as it executes the example, along with
// Pass/Fail information
// The APIs are F28x compatible
//############################################################################

// Select the global Q value to use:
#define GLOBAL_Q    24
long GlobalQ = GLOBAL_Q;      // Used for legacy GEL & Graph Debug.

// Include The Following Definition Files:
#include <stdio.h>
#include <stdlib.h>
#include "IQmathLib.h"

// Specify the data logging size:
#define DATA_LOG_SIZE   64

#define TI_profile_start()
#define TI_profile_stop()

// Define constants used:
#define X_GAIN          1.0
#define X_FREQ          1.0
#define Y_GAIN          1.0
#define Y_FREQ          1.0
#define PI2             1.570796327f
#define PI              3.141592654f
#define STEP_X_SIZE     0.314159265f
#define STEP_Y_SIZE     -0.314159265f

// Allocate data log buffers:
struct  DATA_LOG_C {
    _iq   Xwaveform[DATA_LOG_SIZE];
    _iq   Ywaveform[DATA_LOG_SIZE];
    long  Phase[DATA_LOG_SIZE];
    _iq   Mag[DATA_LOG_SIZE];
    _iq   Exp[DATA_LOG_SIZE];
	_iq   Asin[DATA_LOG_SIZE];
    _iq   Log[DATA_LOG_SIZE];
} Dlog;

// Define waveform global variables:
struct  STEP {
    _iq   Xsize;
    _iq  Ysize;
    _iq   Yoffset;
    _iq   X;
    _iq   Y;
    _iq   GainX;
    _iq   GainY;
    _iq   FreqX;
    _iq   FreqY;
} Step;

//----------------------------------------------------------------------------
// Main code:
//----------------------------------------------------------------------------
int main(void)
{
    unsigned int  i;

    int32_t fail;

    _iq tempX, tempY, tempZ, tempP, tempM, tempMmax;

    tempX = _IQ(STEP_X_SIZE);
    tempY = _IQ(STEP_Y_SIZE);
    tempZ = _IQ(PI2);
    Step.Yoffset = 0;
    Step.X = 0;
    Step.Y = Step.Yoffset;


    // _IQ test case
    asm("BM1_START:");
    TI_profile_start();
    tempP = _IQ(PI);
    TI_profile_stop();
    asm("BM1_END:");
    fail = 0;
    if(tempP != 52707180)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQ() test case passed\n");
    }
    
    // _IQsin test case
    asm("BM2_START:");
    TI_profile_start();
    tempP = _IQsin(tempX);
    TI_profile_stop();
    asm("BM2_END:");
    fail = 0;
    if(tempP != 5184445)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQsin() test case passed\n");
    }
    
    // _IQmpy test case
    asm("BM3_START:");
    TI_profile_start();
    tempP = _IQmpy(tempX,tempY);
    TI_profile_stop();
    asm("BM3_END:");
    fail = 0;
    if(tempP != -1655845)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQmpy() test case passed\n");
    }

    // _IQabs test case
    asm("BM4_START:");
    TI_profile_start();
    tempP = _IQabs(tempY);
    TI_profile_stop();
    asm("BM4_END:");
    fail = 0;
    if(tempP != 5270718)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQabs() test case passed\n");
    }

    // _IQmag test case
    asm("BM5_START:");
    TI_profile_start();
    tempP = _IQmag(tempX,tempZ);
    TI_profile_stop();
    asm("BM5_END:");
    fail = 0;
    if(tempP != 26875494)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQmag() test case passed\n");
    }

    // _IQdiv test case
    asm("BM6_START:");
    TI_profile_start();
    tempP = _IQdiv(tempX,tempZ);
    TI_profile_stop();
    asm("BM6_END:");
    if(tempP != 3355443)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQdiv() test case passed\n");
    }

    // _IQatan2PU test case
    asm("BM7_START:");
    TI_profile_start();
    tempP = _IQatan2PU(tempZ,tempX);
    TI_profile_stop();
    asm("BM7_END:");
    if(tempP != 3667223)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQatan2PU() test case passed\n");
    }

    // _IQmpyI32int test case
    asm("BM8_START:");
    TI_profile_start();
    tempP = _IQmpyI32int(tempP, 360);
    TI_profile_stop();
    asm("BM8_END:");
    if(tempP != 78)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQmpyI32int() test case passed\n");
    }

    // _IQexp test case
    asm("BM9_START:");
    TI_profile_start();
    tempP = _IQexp(tempX);
    TI_profile_stop();
    asm("BM9_END:");
    if(tempP != 22969817)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQexp() test case passed\n");
    }

    // _IQlog test case
    asm("BM10_START:");
    TI_profile_start();
    tempP = _IQlog(tempP);
    TI_profile_stop();
    asm("BM10_END:");
    if(tempP != 5270717)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQlog() test case passed\n");
    }

    // _IQasin test case
    asm("BM11_START:");
    TI_profile_start();
    tempP = _IQasin(tempX);
    TI_profile_stop();
    asm("BM11_END:");
    if(tempP != 5361511)
    {
        fail = 1;
        #ifdef __TMS320C28XX__
            printf("%ld\n",tempP);
        #else
            printf("%d\n",tempP);
        #endif
    } else {
        printf("_IQasin() test case passed\n");
    }


    // Loop test case
    asm("BM12_START:");
    TI_profile_start();
    // Fill the buffers with some initial value
    for(i=0; i < DATA_LOG_SIZE; i++)
    {
        Dlog.Xwaveform[i] = _IQ(0.0);
        Dlog.Ywaveform[i] = _IQ(0.0);
        Dlog.Mag[i] = _IQ(0.0);
        Dlog.Phase[i] = _IQ(0.0);
        Dlog.Exp[i] = _IQ(0.0);
        Dlog.Log[i] = _IQ(0.0);
    }

    Step.GainX = _IQ(X_GAIN);
	Step.FreqX = _IQ(X_FREQ);
	Step.GainY = _IQ(Y_GAIN);
	Step.FreqY = _IQ(Y_FREQ);

    // Calculate maximum magnitude value:
    tempMmax = _IQmag(Step.GainX, Step.GainY);

    for(i=0; i < DATA_LOG_SIZE; i++)
    {
        Dlog.Xwaveform[i] = tempX = _IQmpy(_IQsin(Step.X), Step.GainX);
        Dlog.Ywaveform[i] = tempY = _IQmpy(_IQabs(_IQsin(Step.Y)), Step.GainY);

        // Calculate normalized magnitude:
        //
        // Mag = sqrt(X^2 + Y^2)/sqrt(GainX^2 + GainY^2);
        tempM = _IQmag(tempX, tempY);
        Dlog.Mag[i] = _IQdiv(tempM, tempMmax);

        // Calculate normalized phase:
        //
        // Phase = (long) (atan2PU(X,Y) * 360);
        tempP = _IQatan2PU(tempY,tempX);
        Dlog.Phase[i] = _IQmpyI32int(tempP, 360);

        // Use the exp function
        Dlog.Exp[i] = _IQexp(_IQmpy(_IQ(.075L),_IQ(i)));
        
        // Use the Log function
        Dlog.Log[i] = _IQlog(Dlog.Exp[i]);

		// Use the asin function
		Dlog.Asin[i] = _IQasin(Dlog.Xwaveform[i]);
                
        // Calculate next offset
        // Sweep from 0 to 2pi, then start over
        Step.X = Step.X + _IQmpy(Step.Xsize, Step.FreqX);
        if( Step.X > _IQ(2*PI) )
            Step.X -= _IQ(2*PI);

        Step.Y = Step.Y + _IQmpy(Step.Ysize, Step.FreqY);
        if( Step.Y > _IQ(2*PI) )
            Step.Y -= _IQ(2*PI);        
    }
    TI_profile_stop();
    asm("BM12_END:");
    fail=0;
    #ifdef __TMS320C28XX__
        printf("%ld\n",Dlog.Xwaveform[DATA_LOG_SIZE-1]);
        printf("%ld\n",Dlog.Ywaveform[DATA_LOG_SIZE-1]);
        printf("%ld\n",Dlog.Phase[DATA_LOG_SIZE-1]);
        printf("%ld\n",Dlog.Mag[DATA_LOG_SIZE-1]);
        printf("%ld\n",Dlog.Exp[DATA_LOG_SIZE-1]);
        printf("%ld\n",Dlog.Asin[DATA_LOG_SIZE-1]);
        printf("%ld\n",Dlog.Log[DATA_LOG_SIZE-1]);
    #else
        printf("%d\n",Dlog.Xwaveform[DATA_LOG_SIZE-1]);
        printf("%d\n",Dlog.Ywaveform[DATA_LOG_SIZE-1]);
        printf("%ld\n",Dlog.Phase[DATA_LOG_SIZE-1]);
        printf("%d\n",Dlog.Mag[DATA_LOG_SIZE-1]);
        printf("%d\n",Dlog.Exp[DATA_LOG_SIZE-1]);
        printf("%d\n",Dlog.Asin[DATA_LOG_SIZE-1]);
        printf("%d\n",Dlog.Log[DATA_LOG_SIZE-1]);
    #endif
    
    printf("IQmath example complete\n");
    

}

//############################################################################
// End of file
//############################################################################
