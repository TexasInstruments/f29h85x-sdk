//#############################################################################
//
// FILE:    crypto_sm3.c
//
// TITLE:   This example demonstrates DTHE SM3
//
//! \addtogroup driver_example_list
//! <h1> This example demonstrates DTHE SM3 </h1>
//!
//! This example demonstrates the This example demonstrates DTHE SM3.
//
//#############################################################################
//
//
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//#############################################################################

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <stdint.h>
#include <drivers/crypto/dthe/dthe.h>
#include <drivers/crypto/dthe/dma.h>
#include <drivers/crypto/dthe/dthe_aes.h>
#include <drivers/crypto/dthe/dthe_sm3.h>
#include "board.h"
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* SM3 length in bytes */
#define APP_CRYPTO_SM3_LENGTH                           (32U)
/* input sm3 buff Alignment in bytes */
#define APP_CRYPTO_SM3_BUF_ALIGNMENT                    (64U)
/*Input and output buf length in bytes*/
#define APP_CRYPTO_SM3_INPUT_BUF_LENGTH                 (128U)
/* DTHE Public address */
#define CSL_DTHE_PUBLIC_U_BASE                          (0x30280000U)
/* DTHE Aes Public address */
#define CSL_DTHE_PUBLIC_AES_U_BASE                      (0x30286000U)
/* DTHE Aes Public address */
#define CSL_DTHE_PUBLIC_SHA_U_BASE                      (0x30284000U)
/* SM3_BASE Public address */
#define CSL_DTHE_PUBLIC_SM3_BASE                        (0x30289000U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

DTHE_Attrs gDTHE_Attrs[1] =
{
    {
        /* crypto accelerator base address */
        .caBaseAddr         = CSL_DTHE_PUBLIC_U_BASE,
        /* AES base address */
        .aesBaseAddr        = CSL_DTHE_PUBLIC_AES_U_BASE,
        /* SHA base address */
        .shaBaseAddr        = CSL_DTHE_PUBLIC_SHA_U_BASE,
        /* SM3 base address - using the same as SHA since they share hardware */
        .sm3BaseAddr        = CSL_DTHE_PUBLIC_SM3_BASE,
        /* For checking dthe driver open or close */
        .isOpen             = FALSE,
    },
};

DTHE_Config gDtheConfig[1]=
{
    {
        &gDTHE_Attrs[0],
        DMA_DISABLE,
    },
};

uint32_t gDtheConfigNum = 1;
DMA_Config gDmaConfig[1]={0};
uint32_t gDmaConfigNum = 1;

void loop_forever()
{
    volatile uint32_t loop = 1;
    while(loop)
        ;
}

/* Test 3 */
/* Inout test buffer for sm3 computation for DATA LEN = 128 BYTES */
static uint8_t gCryptoSm3TestInputBuf[] =
{
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
};

/* SM3 test vectors,this is expected hash for the test buffer */
static uint8_t gCryptoSm3TestSum[APP_CRYPTO_SM3_LENGTH] =
{
    0x90, 0xD5, 0x2A, 0x2E, 0x85, 0x63, 0x1A, 0x8D, 0x60, 0x35, 0x26, 0x26, 0x26, 0x94, 0x1F, 0xA1,
    0x1B, 0x85, 0xCE, 0x57, 0x0C, 0xEC, 0x1E, 0x3E, 0x99, 0x1E, 0x2D, 0xD7, 0xED, 0x25, 0x81, 0x48,
};


DTHE_Handle			gShaHandle = NULL;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void crypto_sm3_main(void *args)
{
    DTHE_SM3_Return_t   status;
    DTHE_SM3_Params     sm3Params;

    DebugP_log("[CRYPTO] SM3 example started ...\r\n");

    /* Opening crypto driver */
    gShaHandle = DTHE_open(0);
    DebugP_assert(gShaHandle != NULL);

    /* Opening sm3 driver */
    status = DTHE_SM3_open(gShaHandle);
    DebugP_assert(DTHE_SM3_RETURN_SUCCESS == status);

    /* Initialize the SM3 Parameters */
    sm3Params.ptrDataBuffer     = (uint32_t*)&gCryptoSm3TestInputBuf[0];
    sm3Params.dataLenBytes      = APP_CRYPTO_SM3_INPUT_BUF_LENGTH;

    /* Performing DTHE SM3 operation */
    status = DTHE_SM3_compute(gShaHandle, &sm3Params, DTHE_SM3_LAST_BLOCK_TRUE);
    DebugP_assert(DTHE_SM3_RETURN_SUCCESS == status);

    /* Closing sm3 driver */
    status = DTHE_SM3_close(gShaHandle);
    DebugP_assert(DTHE_SM3_RETURN_SUCCESS == status);

    /* Closing DTHE driver */
    if (DTHE_RETURN_SUCCESS == DTHE_close(gShaHandle))
    {
        status = DTHE_SM3_RETURN_SUCCESS;
    }
    else
    {
        status = DTHE_SM3_RETURN_FAILURE;
    }

    DebugP_assert(DTHE_SM3_RETURN_SUCCESS == status);

    /*comparing result with expected test results*/
    if(memcmp(sm3Params.digest, gCryptoSm3TestSum, APP_CRYPTO_SM3_LENGTH) != 0)
    {
        DebugP_log("[CRYPTO] SM3 example failed!!\r\n");
    }
    else
    {
        DebugP_log("[CRYPTO] SM3 example completed!!\r\n");
        DebugP_log("All tests have passed!!\r\n");
    }

    return;
}

int main(void)
{
    Device_init();
    Board_init();
    System_init();

    crypto_sm3_main(NULL);

    for(;;)
    {
        /* Infinite loop to prevent the program from exiting */
    }

    System_deinit();

    return 0;
}
