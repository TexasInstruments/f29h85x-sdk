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
#define CERT_BOOTINFO_ID_SIZE           (11U)
/**
 * @brief   This is the DER SEQUENCE Tag as defined by the standard.
 */
#define CERT_DER_SEQUENCE_TAG           (0x30U)

/**
 * @brief   This is the DER Boolean Tag as defined by the standard.
 */
#define CERT_DER_BOOLEAN_TAG            (0x1U)

/**
 * @brief   This is the DER Integer Tag as defined by the standard.
 */
#define CERT_DER_INTEGER_TAG            (0x2U)

/**
 * @brief   This is the DER Octet String Tag as defined by the standard.
 */
#define CERT_DER_OCTET_STRING_TAG       (0x4U)

/**
 * @brief   This is the DER Object Id Tag as defined by the standard.
 */
#define CERT_DER_OBJECT_ID_TAG          (0x6U)

/**
*  @b Description
*  @n
*      Get Image Size Index into the certificate
*
*  @param[in] cert
*      Certificate file pointer
*
*  @retval
*      Image size index
*/
int32_t parseTag(FILE *cert, uint32_t tag, uint32_t *certIndex, uint32_t *tagSize)
{
    uint8_t data    = 0U;
    int32_t retVal  = 0;
    //
    //  Read tag
    //
    fseek(cert, *certIndex, SEEK_SET);
    if(1U == fread(&data, 1U, 1U, cert))
    {
        if(data == tag)
        {
            //
            //  Read the tag size
            //
            if(1U == fread(&data, 1U, 1U, cert))
            {
                *tagSize    = data;
                //
                //  Move to next tag
                //
                *certIndex += 2U;
            }
            else
            {
                retVal = -1;
            }
        }
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}

/**
*  @b Description
*  @n
*      Get Image Size Index into the certificate
*
*  @param[in] cert
*      Certificate file pointer
*
*  @retval
*      Image size index
*/
uint32_t getImageSizeIndex(FILE *cert, uint32_t *imageSizeSize)
{
    int32_t  retVal                         = 0;
    uint32_t imageSizeIndex                 = 0U;
    uint32_t readIdx                        = 0U;
    uint32_t tagSize                        = 0U;
    uint8_t  readBuf[CERT_BOOTINFO_ID_SIZE] = {0U};
    static const uint8_t certBootInfoId[CERT_BOOTINFO_ID_SIZE] =
    {
        0x06U,
        0x09U,
        0x2BU,
        0x06U,
        0x01U,
        0x04U,
        0x01U,
        0x82U,
        0x26U,
        0x01U,
        0x01U
    };
    //
    //  Find bootinfo id
    //
    readIdx = 0U;
    fseek(cert, readIdx, SEEK_SET);
    while(CERT_BOOTINFO_ID_SIZE == fread(readBuf, 1U, CERT_BOOTINFO_ID_SIZE, cert))
    {
        if(0U == memcmp(readBuf, certBootInfoId, CERT_BOOTINFO_ID_SIZE))
        {
            //
            //  The bootinfo id pattern is found
            //
            imageSizeIndex = ftell(cert) & 0xFFFFFFU;
            break;
        }
        else
        {
            //
            //  Move by one byte
            //
            readIdx++;
            fseek(cert, readIdx, SEEK_SET);
        }
    }

    if(0U != imageSizeIndex)
    {
        retVal = parseTag(cert, CERT_DER_BOOLEAN_TAG, &imageSizeIndex, &tagSize);
        if(0 == retVal)
        {
            retVal = parseTag(cert, CERT_DER_OCTET_STRING_TAG, &imageSizeIndex, &tagSize);
        }
        if(0 == retVal)
        {
            retVal = parseTag(cert, CERT_DER_SEQUENCE_TAG, &imageSizeIndex, &tagSize);
        }
        if(0 == retVal)
        {
            retVal = parseTag(cert, CERT_DER_INTEGER_TAG, &imageSizeIndex, &tagSize);
            imageSizeIndex += tagSize;
        }
        if(0 == retVal)
        {
            retVal = parseTag(cert, CERT_DER_INTEGER_TAG, &imageSizeIndex, &tagSize);
            imageSizeIndex += tagSize;
        }
        if(0 == retVal)
        {
            retVal = parseTag(cert, CERT_DER_INTEGER_TAG, &imageSizeIndex, &tagSize);
            imageSizeIndex += tagSize;
        }
        if(0 == retVal)
        {
            retVal = parseTag(cert, CERT_DER_OCTET_STRING_TAG, &imageSizeIndex, &tagSize);
            imageSizeIndex += tagSize;
        }
        if(0 == retVal)
        {
            retVal = parseTag(cert, CERT_DER_INTEGER_TAG, &imageSizeIndex, &tagSize);
            if(0 == retVal)
            {
                *imageSizeSize = tagSize;
            }
        }

        if(0 != retVal)
        {
            imageSizeIndex = 0U;
        }
    }

    return imageSizeIndex;
}

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
    FILE        *cert           = NULL;
    FILE        *image          = NULL;
    uint32_t    imageSize       = 0U;
    uint8_t     writeData       = 0U;
    uint32_t    imgSizeIndex    = 0U;
    uint32_t    imageSizeSize   = 0U;
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
    //  Get the index of the image size in the certificate
    //
    imgSizeIndex = getImageSizeIndex(cert, &imageSizeSize);
    if(0U != imgSizeIndex)
    {
        //
        //  Update the Image size in the cert
        //  ->  The image size shall be 3 bytes and is written in big endian format
        //
        fseek(cert, imgSizeIndex, SEEK_SET);
        if(3U == imageSizeSize)
        {
            //
            //  Write 3rd byte
            //
            writeData = (uint8_t)((imageSize >> 16U) & 0xFFU);
            fwrite(&writeData, 1U, 1U, cert);
        }
        if(2U <= imageSizeSize)
        {
            //
            //  Write 2nd byte
            //
            writeData = (uint8_t)((imageSize >> 8U) & 0xFFU);
            fwrite(&writeData, 1U, 1U, cert);
        }
        //
        //  Write 1st byte
        //
        writeData = (uint8_t)(imageSize & 0xFFU);
        fwrite(&writeData, 1U, 1U, cert);
    }
    else
    {
        printf("Error: Image size index\n");
        return -1;
    }
    //
    //  Close the files
    //
    fclose(cert);
    fclose(image);

    return 0;
}
