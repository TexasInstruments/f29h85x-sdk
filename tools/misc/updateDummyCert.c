/**
*   @file  updateDummyCert.c
*
*   @brief
*      This utility updates the size of the image into the dummy certificate
*      It only supports the dummy certificate provided in the SDK
*
*  \par
*  NOTE:
*      (C) Copyright 2025 Texas Instruments, Inc.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************
*************************** Include Files ********************************
**************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**************************************************************************
************************ Update Dummy Certificate *************************
**************************************************************************/
//
//  Defines
//
//
//  Offset into the cert where image size is stored
//  ->  This offset is fixed for the dummy certificate used in SDK
//      and will not work for any other certificate
//
#define CERT_IMAGE_SIZE_OFFSET      (0x3E0U)

/**
*  @b Description
*  @n
*      Entry point into the Update Dummy Certificate utility
*
*  @param[in] argc
*      Number of arguments
*  @param[in] argv
*      Command Line arguments
*
*  @retval
*      Success -   0
*  @retval
*      Error   -   <0
*/
int32_t main(int32_t argc, char* argv[])
{
    FILE        *cert       = NULL;
    FILE        *image      = NULL;
    uint32_t    imageSize   = 0U;
    uint8_t     writeData   = 0U;
    //
    //  Check the number of arguments
    //
    if(3U != argc)
    {
        printf("Error: Insufficient arguments\n");
        return -1;
    }
    //
    //  Open cert file in wb mode
    //
    cert = fopen(argv[1], "rb+");
    if(NULL == cert)
    {
        printf("Error: Cert file open\n");
        return -1;
    }
    //
    //  Open image file in rb mode
    //
    image = fopen(argv[2], "rb");
    if(NULL == image)
    {
        printf("Error: Image file open\n");
        return -1;
    }
    //
    //  Find size of image file
    //
    fseek(image, 0U, SEEK_END);
    imageSize = ftell(image) & 0xFFFFFFU;
    //
    //  Update the Image size in the cert
    //  ->  The image size shall be 3 bytes and is written in big endian format
    //
    fseek(cert, CERT_IMAGE_SIZE_OFFSET, SEEK_SET);
    //
    //  Write 3rd byte
    //
    writeData = (uint8_t)((imageSize >> 16U) & 0xFFU);
    fwrite(&writeData, 1U, 1U, cert);
    //
    //  Write 2nd byte
    //
    writeData = (uint8_t)((imageSize >> 8U) & 0xFFU);
    fwrite(&writeData, 1U, 1U, cert);
    //
    //  Write 1st byte
    //
    writeData = (uint8_t)(imageSize & 0xFFU);
    fwrite(&writeData, 1U, 1U, cert);
    //
    //  Close the files
    //
    fclose(cert);
    fclose(image);

    return 0;
}
