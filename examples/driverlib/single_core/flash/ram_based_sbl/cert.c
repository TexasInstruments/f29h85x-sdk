//###########################################################################
// $TI Release:  $
// $Release Date:  $
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

//###########################################################################

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/
//#include <stdint.h>
//#include <string.h>

/* RBL Include Files: */
#include <cert.h>

/**************************************************************************
 ************************* Local Definitions ******************************
 **************************************************************************/

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

/**************************************************************************
 ************************** Local Constants *******************************
 **************************************************************************/

/**
 * @brief   This is the X509 Boot Information Extension Object Identifier
 * This has the encoded object id for the following:
 *      Type      = Object Id (0x6)
 *      Length    = 9U
 *      Object Id = 1.3.6.1.4.1.294.1.1
 */
const uint8_t gCertBootInfoOID[] =
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

/**************************************************************************
 ************************** Local Structures ******************************
 **************************************************************************/

/**
 * @brief
 *  Certificate Info
 *
 * @details
 *  The structure creates a reference information which points to the data
 *  in the X509 certificate.
 */
typedef struct Cert_Ref_t
{
    /**
     * @brief   Pointer to the value into the X509 certificate buffer
     */
    uint8_t*        ptrValue;

    /**
     * @brief   Size of the value
     */
    uint32_t        sizeValue;

    /**
     * @brief   Size of the value + Tag
     */
    uint32_t        totalSize;
}Cert_Ref;

/**
 * @brief
 *  Certificate Context Object
 *
 * @details
 *  The certificate context object holds all the relevant
 *  information associated with the module.
 */
typedef struct Cert_Context_Obj_t
{
    /**
     * @brief   Length in bytes of the certificate data buffer
     */
    uint32_t        certLength;

    /**
     * @brief   Size of the boot image in bytes
     */
    uint32_t        imageSize;

    /**
     * @brief   Pointer to the certificate buffer:
     */
    uint8_t*        ptrCertificateBuffer;
}Cert_Context_Obj;

/**************************************************************************
 ************************** Global Variables ******************************
 **************************************************************************/

/**
 * @brief   Global variable which tracks the certificate context object
 */
Cert_Context_Obj      gCertContextObj;

/**************************************************************************
 ************************** Local Function Prototype ***************************
 **************************************************************************/
static Cert_Return_t Cert_patternMatch
(
    const uint8_t*          ptrPattern,
    const uint32_t          sizePattern,
    uint32_t*               ptrDataPostPatternIndex
);
static void Cert_copyData (uint8_t* ptrDst, const uint8_t* ptrSrc, uint32_t length);
static Cert_Return_t Cert_getReference
(
    const Cert_Context_Obj*     ptrCertContextObj,
    uint8_t                     expectedTag,
    uint32_t*                   ptrIndex,
    Cert_Ref*                   ptrRef
);
static uint32_t Cert_getValueSize (const uint8_t* ptrDERTag);
static Cert_Return_t Cert_decodeLength
(
    const uint8_t*      ptrCertBuffer,
    uint32_t            maxSizeBuffer,
    uint32_t*           ptrCertLength
);
static uint32_t Cert_decodeLengthSize (const uint8_t* ptrDERTag);
static Cert_Return_t Cert_decodeBootInfo (Cert_Context_Obj* ptrCertContextObj, uint32_t postPatternIndex);

/**************************************************************************
 ************************** Certificate Functions *************************
 **************************************************************************/

/**
 *  @b Description
 *  @n
 *      The function is used to get the size of the length. This
 *      is a helper function which does not perform any range
 *      validations
 *
 *  @param[in]  ptrDERTag
 *      Pointer to the DER Tag which is to be decoded
 *
 *  @retval
 *      Length Size in Bytes
 */
static uint32_t Cert_decodeLengthSize (const uint8_t* ptrDERTag)
{
    uint32_t    lengthSize;

    /* DER Specification: Length can be in Long/Short Form. */
    if (CSL_FEXTR (ptrDERTag[1], 7U, 7U) == 0U)
    {
        /* Short Format: */
        lengthSize = 1U;
    }
    else
    {
        /* Long Format: Get the number of bytes which make up the length. */
        lengthSize = CSL_FEXTR ((uint32_t)ptrDERTag[1], 6U, 0U);
    }
    return lengthSize;
}

/**
 *  @b Description
 *  @n
 *      The function is used to get the size of the value. This
 *      is a helper function which does not perform any range
 *      validations
 *
 *  @param[in]  ptrDERTag
 *      Pointer to the DER Tag which is to be decoded
 *
 *  @retval
 *      Size of the value
 */
static uint32_t Cert_getValueSize (const uint8_t* ptrDERTag)
{
    uint32_t    length = 0U;
    uint32_t    lengthSize;
    uint32_t    index;

    /* DER Specification: Length can be in Long/Short Form. */
    if (CSL_FEXTR (ptrDERTag[1], 7U, 7U) == 0U)
    {
        /* Short Format: */
        length = CSL_FEXTR ((uint32_t)ptrDERTag[1], 6U, 0U);
    }
    else
    {
        /* Long Format: Get the number of bytes which make up the length. */
        lengthSize = CSL_FEXTR ((uint32_t)ptrDERTag[1], 6U, 0U);

        /* Compute the size of the value */
        for (index = 0U; index < lengthSize; index++)
        {
            length = (length << 8U) + (uint32_t)ptrDERTag[2U + index];
        }
    }
    return length;
}

/**
 *  @b Description
 *  @n
 *      The function is used to copy the data from the source to the
 *      destination in reverse order.
 *
 *  @param[in]  ptrDst
 *      Pointer to the destination buffer
 *  @param[in]  ptrSrc
 *      Pointer to the source buffer
 *  @param[in]  length
 *      Length of the data to be copied
 *
 *  @retval
 *      None
 */
static void Cert_copyData (uint8_t* ptrDst, const uint8_t* ptrSrc, uint32_t length)
{
    uint32_t index;
    for (index = 0U; index < length; index++)
    {
        ptrDst[length - 1U - index] = ptrSrc[index];
    }
}

/**
 *  @b Description
 *  @n
 *      This is the function which is used to get the length of the
 *      certificate by decoding the X509 certificate
 *
 *  @param[in]  ptrCertBuffer
 *      Pointer to the X509 certificate buffer
 *  @param[in]  maxSizeBuffer
 *      Maximum size of the X509 certificate buffer
 *  @param[out]  ptrCertLength
 *      Pointer to the actual size of the X509 Certificate populated
 *      by parsing the X509 certificate.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Errro   -   <0
 */
static Cert_Return_t Cert_decodeLength
(
    const uint8_t*      ptrCertBuffer,
    uint32_t            maxSizeBuffer,
    uint32_t*           ptrCertLength
)
{
    Cert_Return_t   retVal = CERT_RETURN_SUCCESS;
    uint8_t         index;
    uint8_t         lengthSize;

    /* Initialize the certificate length: */
    *ptrCertLength = 0U;

    /*****************************************************************************************
     * Sanity Check: We should have at least minimal amount of data to be able to
     * parse the x509 certificate
     *****************************************************************************************/
    if (maxSizeBuffer < CONFIG_CERT_SIZE)
    {
        //LOGS_ENTRY (Log_Type_ERROR, maxSizeBuffer, 0U, "Certificate buffer is too small");
        retVal = CERT_RETURN_ERROR;
    }

    /************************************************************************
     * Step1: Certificates start with the SEQUENCE i.e. the Encoded Tag
     ************************************************************************/
    if (retVal == CERT_RETURN_SUCCESS)
    {
        if (ptrCertBuffer[0] != CERT_DER_SEQUENCE_TAG)
        {
            //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)ptrCertBuffer[0], 0U, "Not a DER sequence");
            retVal = CERT_RETURN_PARSE_FAIL;
        }
    }

    /************************************************************************
     * Step2: Extract the length
     ************************************************************************/
     if (retVal == CERT_RETURN_SUCCESS)
     {
        /* DER Specification: Length can be in Long/Short Form. */
        if (CSL_FEXTR (ptrCertBuffer[1], 7U, 7U) == 0U)
        {
            /* Short Format: */
            *ptrCertLength = CSL_FEXTR ((uint32_t)ptrCertBuffer[1], 6U, 0U);

            /* Account for the tag + length */
            *ptrCertLength = *ptrCertLength + 2U;
        }
        else
        {
            /* Long Format: Get the number of bytes which make up the length. */
            lengthSize = ((uint8_t)CSL_FEXTR (ptrCertBuffer[1], 6U, 0U));

            /* Compute the certificate size: */
            for (index = 0U; index < lengthSize; index++)
            {
                *ptrCertLength = (*ptrCertLength << 8U) + (uint32_t)ptrCertBuffer[2U + index];
            }

            /* Account for the tag + length + N bytes of the length */
            *ptrCertLength = *ptrCertLength + 2U + lengthSize;
        }
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      The function is used to get the reference to the expected
 *      tag in the X509 certificate. It might be possible that
 *      the *expected tag* is not found in this case the function
 *      return a specific BAD_PARAMS error code. This would be useful
 *      to handle scenarios where the *expected tag* is optional.
 *
 *  @param[in]  ptrCertContextObj
 *      Pointer to the certificate object
 *  @param[in]  expectedTag
 *      Expected Tag
 *  @param[in]  ptrIndex
 *      Pointer to the index which has tag
 *  @param[out]  ptrRef
 *      Pointer to the reference information which is populated by the API
 *
 *  @retval
 *      Success -   CERT_RETURN_SUCCESS
 *  @retval
 *      Error   -   Cert Error codes (\ref Cert_Return_t)
 */
static Cert_Return_t Cert_getReference
(
    const Cert_Context_Obj*     ptrCertContextObj,
    uint8_t                     expectedTag,
    uint32_t*                   ptrIndex,
    Cert_Ref*                   ptrRef
)
{
    Cert_Return_t   retVal = CERT_RETURN_SUCCESS;
    uint32_t        lengthSize;
    uint32_t        index;

    /* Keep track of the index in the certificate buffer which is to be processed: */
    index = *ptrIndex;

    /******************************************************************************
     * The DER Transfer Syntax states that all tags need to have the following:-
     *      Tag (1byte) + Length (1Byte) + Value (N bytes)
     *
     * Length can further be encoded into Short or Long Form. But at this time we
     * know for sure we need at least 1byte of length to proceed. Ensure that we
     * are within range and not going beyond the certificate limits
     ******************************************************************************/
    if ((index + 1U) < ptrCertContextObj->certLength)
    {
        /* Is this the tag we are processing? */
        if (ptrCertContextObj->ptrCertificateBuffer[index] != expectedTag)
        {
            /* Error: Unexpected Tag */
            retVal = CERT_RETURN_BAD_PARAMS;
        }

        /************************************************************************
         * Decode the Length Size:
         *  Short Form - 1byte
         *  Long  Form - Nbytes
         * Ensure that we dont exceed the limits.
         ************************************************************************/
        if (retVal == CERT_RETURN_SUCCESS)
        {
            /* Decode the size of the length */
            lengthSize = Cert_decodeLengthSize (&ptrCertContextObj->ptrCertificateBuffer[index]);
        }

        /************************************************************************
         * Create the reference:
         ************************************************************************/
        if (retVal == CERT_RETURN_SUCCESS)
        {
            if ((index + lengthSize) < ptrCertContextObj->certLength)
            {
                /* Get the size of the value: */
                ptrRef->sizeValue = Cert_getValueSize (&ptrCertContextObj->ptrCertificateBuffer[index]);

                /* If we access the value are we still within range? */
                if ((index + lengthSize + ptrRef->sizeValue) < ptrCertContextObj->certLength)
                {
                    /* Setup the reference to point to the value: */
                    ptrRef->ptrValue = &ptrCertContextObj->ptrCertificateBuffer[index + 1U + lengthSize];
                    ptrRef->totalSize = ptrRef->sizeValue + 1U + lengthSize;

                    /* Update the index: */
                    *ptrIndex = index + 1U + lengthSize;
                }
                else
                {
                    /* Error: Value exceeds the certficate buffer */
                    retVal = CERT_RETURN_PARSE_FAIL;
                    //LOGS_ENTRY (Log_Type_ERROR, (index + lengthSize + ptrRef->sizeValue), ptrCertContextObj->certLength, "Value exceeds certificate length");
                }
            }
        }
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      The function is used to match a pattern in the certificate
 *
 *  @param[in]  ptrPattern
 *      Pointer to the pattern to be matched
 *  @param[in]  sizePattern
 *      Size of the pattern to be matched
 *  @param[out]  ptrDataPostPatternIndex
 *      Pointer to the index after the matching pattern in the
 *      certificate
 *
 *  @retval
 *      Success -   CERT_RETURN_SUCCESS
 *  @retval
 *      Error   -   Cert Error codes (\ref Cert_Return_t)
 */
static Cert_Return_t Cert_patternMatch
(
    const uint8_t*          ptrPattern,
    const uint32_t          sizePattern,
    uint32_t*               ptrDataPostPatternIndex
)
{
    Cert_Return_t       retVal;
    Cert_Context_Obj*   ptrCertContextObj;
    uint8_t*            ptrCertificate;
    uint32_t            certLimit;
    uint32_t            certIndex;
    uint32_t            patternIndex;
    uint8_t             patternSearchingDone;

    /* Get the pointer to the certificate object: */
    ptrCertContextObj = &gCertContextObj;

    /* Get the pointer to the X509 certificate: */
    ptrCertificate = &ptrCertContextObj->ptrCertificateBuffer[0];

    /* Initialize the return value: */
    retVal = CERT_RETURN_PARSE_FAIL;

    /* Start from the beginning of the certificate: */
    certIndex = 0U;

    /* Compute the outer loop limit:
     * - In order to totally match the pattern we need to have at least pattern bytes
     *   left in the certificate. If there is less data than pattern bytes we cannot
     *   perform a full match. Also since we expect data to be always there after the
     *   pattern we need at least 1 additional data byte. */
    certLimit = ptrCertContextObj->certLength - sizePattern - 1U;

    /**************************************************************************************
     * Outer Loop: Cycle through the entire certificate
     **************************************************************************************/
    while ((certIndex < certLimit) && (retVal == CERT_RETURN_PARSE_FAIL))
    {
        /**************************************************************************************
         * Inner Loop: Cycle through the entire pattern
         **************************************************************************************/
        patternIndex         = 0U;
        patternSearchingDone = 0U;
        while (patternSearchingDone == 0U)
        {
            /* Does the certificate match the pattern? */
            if (ptrCertificate[certIndex + patternIndex] == ptrPattern[patternIndex])
            {
                /* Yes: Try and match the next element */
                patternIndex = patternIndex + 1U;

                /* Did we match all the elements? */
                if (patternIndex == sizePattern)
                {
                    /* Yes: We are done with the pattern searching */
                    patternSearchingDone = 1U;

                    /* Setup the post pattern index: */
                    *ptrDataPostPatternIndex = certIndex + patternIndex;

                    /* Setup the return code: */
                    retVal = CERT_RETURN_SUCCESS;
                }
            }
            else
            {
                /* No: There is no match we will need to start with the next element. */
                patternSearchingDone = 1U;
            }
        }

        /* Did we get a perfect match? */
        if (retVal == CERT_RETURN_PARSE_FAIL)
        {
            /* No: Continue to the next element in the certificate */
            certIndex = certIndex + 1U;
        }
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      The function is used to decode the boot information extension
 *      This is encoded as per the following rules:-
 *
 *  extension ::=  SEQUENCE  {
 *              extnID      OBJECT IDENTIFIER,
 *              critical    BOOLEAN DEFAULT FALSE,
 *              extnValue   OCTET STRING
 *                          -- contains the DER encoding of an ASN.1 value
 *                          -- corresponding to the extension type identified
 *                          -- by extnID
 *              }
 *
 *  So the case we are handling here the extnID is 1.3.6.1.4.1.294.1.1
 *  We will skip the critical field if present. The extnValue which is
 *  then defined as an OCTET STRING has the following ASN encoding:-
 *
 *  bootInfo ::=  SEQUENCE {
 *         cert_type:  INTEGER,      -- identifies the certificate type
 *         boot_core:  INTEGER,      -- identifies the boot core
 *         core_opts:  INTEGER,      -- 32 or 64 bit boot core target
 *         load_addr:  OCTET STRING, -- Global address image destination
 *         image_size: INTEGER,      -- Image size in bytes
 *         }
 *
 *  @param[in]  ptrCertContextObj
 *      Pointer to the certificate object
 *  @param[in]  postPatternIndex
 *      Pointer to the post pattern index from where the decoding needs
 *      to be started
 *
 *  @retval
 *      Success -   CERT_RETURN_SUCCESS
 *  @retval
 *      Error   -   Cert Error codes (\ref Cert_Return_t)
 */
static Cert_Return_t Cert_decodeBootInfo (Cert_Context_Obj* ptrCertContextObj, uint32_t postPatternIndex)
{
    Cert_Return_t   retVal = CERT_RETURN_SUCCESS;
    Cert_Ref        refValue;
    Cert_Ref        sequenceRefValue;
    uint32_t        index;

    /* Initialize the index: */
    index = postPatternIndex;

    /* Step1: [Optional] Critical Boolean Flag */
    retVal = Cert_getReference(ptrCertContextObj, CERT_DER_BOOLEAN_TAG, &index, &refValue);
    if (retVal == CERT_RETURN_SUCCESS)
    {
        /* Debug Message: This is an optional field. Log an informational message to indicate
         * its detection. */
        //LOGS_ENTRY (Log_Type_INFO, 0U, 0U, "Optional Critical field detected");
    }
    else if (retVal == CERT_RETURN_BAD_PARAMS)
    {
        /* Since this is an optional field the error code here indicates that the boolean
         * tag was not detected. This is not an error. */
        retVal = CERT_RETURN_SUCCESS;
    }
    else
    {
        //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)retVal, index, "Certificate Limit Exceeded");
    }

    /* Skip the OCTET String Tag: */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        retVal = Cert_getReference(ptrCertContextObj, CERT_DER_OCTET_STRING_TAG, &index, &refValue);
        if (retVal != CERT_RETURN_SUCCESS)
        {
            //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)retVal, 0U, "OCTET Reference failed");
        }
    }

    /* Skip the SEQUENCE Tag: */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        retVal = Cert_getReference(ptrCertContextObj, CERT_DER_SEQUENCE_TAG, &index, &sequenceRefValue);
        if (retVal != CERT_RETURN_SUCCESS)
        {
            //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)retVal, 0U, "SEQUENCE Reference failed");
        }
    }

    /* Get the Certificate Type: */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        retVal = Cert_getReference (ptrCertContextObj, CERT_DER_INTEGER_TAG, &index, &refValue);
        if (retVal != CERT_RETURN_SUCCESS)
        {
            //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)retVal, 0U, "Extracting Cert Type failed");
        }
        else
        {
            /* Account for the type: */
            index = index + refValue.sizeValue;

            /* Decrement the sequence reference size: */
            sequenceRefValue.sizeValue = sequenceRefValue.sizeValue - refValue.totalSize;
        }
    }

    /* Get the Boot Core: */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        retVal = Cert_getReference (ptrCertContextObj, CERT_DER_INTEGER_TAG, &index, &refValue);
        if (retVal != CERT_RETURN_SUCCESS)
        {
            //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)retVal, 0U, "Extracting Boot Core failed");
        }
        else
        {
            /* Account for the Boot Core: */
            index = index + refValue.sizeValue;

            /* Decrement the sequence reference size: */
            sequenceRefValue.sizeValue = sequenceRefValue.sizeValue - refValue.totalSize;
        }
    }

    /* Get the Boot Core Options: */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        retVal = Cert_getReference (ptrCertContextObj, CERT_DER_INTEGER_TAG, &index, &refValue);
        if (retVal != CERT_RETURN_SUCCESS)
        {
            //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)retVal, 0U, "Extracting Boot Core Options failed");
        }
        else
        {
            /* Account for the Boot Core Options: */
            index = index + refValue.sizeValue;

            /* Decrement the sequence reference size: */
            sequenceRefValue.sizeValue = sequenceRefValue.sizeValue - refValue.totalSize;
        }
    }

    /* Get the Load Address: */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        retVal = Cert_getReference (ptrCertContextObj, CERT_DER_OCTET_STRING_TAG, &index, &refValue);
        if (retVal != CERT_RETURN_SUCCESS)
        {
            //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)retVal, 0U, "Extracting Boot Core Options failed");
        }
        else
        {
            /* Account for the Load Address: */
            index = index + refValue.sizeValue;

            /* Decrement the sequence reference size: */
            sequenceRefValue.sizeValue = sequenceRefValue.sizeValue - refValue.totalSize;
        }
    }

    /* Get the Image Size : */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        retVal = Cert_getReference (ptrCertContextObj, CERT_DER_INTEGER_TAG, &index, &refValue);
        if (retVal != CERT_RETURN_SUCCESS)
        {
            //LOGS_ENTRY (Log_Type_ERROR, (uint32_t)retVal, 0U, "Extracting Boot Core Options failed");
        }
        else
        {
            /* Copy the data: */
            Cert_copyData ((uint8_t*)&ptrCertContextObj->imageSize, refValue.ptrValue, refValue.sizeValue);

            /* Decrement the sequence reference size: */
            sequenceRefValue.sizeValue = sequenceRefValue.sizeValue - refValue.totalSize;
        }
    }

    /* Did the sequence close? */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        if (sequenceRefValue.sizeValue != 0U)
        {
            retVal = CERT_RETURN_PARSE_FAIL;
            //LOGS_ENTRY (Log_Type_ERROR, sequenceRefValue.sizeValue, 0U, "Boot Core Sequence failed to close");
        }
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      The function is used to get the length of the certificate from the
 *      X509 certificate.
 *
 *      At this point in time the length of the X509 certificate is unknown
 *      so the application should have provided at least the mimimal amount of
 *      data \ref CONFIG_CERT_SIZE to allow the decoding of the length
 *      of the certificate.
 *
 *  @param[in]  ptrCertBuffer
 *      Pointer to the X509 Certificate
 *  @param[out] sizeBuffer
 *      Size of the certificate buffer which is valid and has the necessary
 *      data which can be decoded to get the length of the certificate
 *  @param[out]  ptrCertLength
 *      Pointer to the certificate length populated by the API
 *
 *  @retval
 *      Success -   CERT_RETURN_SUCCESS
 *  @retval
 *      Error   -   Cert Error codes (\ref Cert_Return_t)
 */
Cert_Return_t Cert_getLength (uint8_t* ptrCertBuffer, uint32_t sizeBuffer, uint32_t* ptrCertLength)
{
    Cert_Context_Obj*   ptrCertContextObj;
    Cert_Return_t       retVal;

    /* Get the pointer to the certificate object: */
    ptrCertContextObj = &gCertContextObj;

    /* Store the certificate buffer: */
    ptrCertContextObj->ptrCertificateBuffer = ptrCertBuffer;

    /* Get the length of the certificate */
    retVal = Cert_decodeLength (ptrCertBuffer, sizeBuffer, &ptrCertContextObj->certLength);
    if (retVal == CERT_RETURN_SUCCESS)
    {
        /* Certificate Length: */
        *ptrCertLength = ptrCertContextObj->certLength;
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      The function is used to get the image size from the
 *      X509 certificate. This information is only available
 *      once the module has been successfully opened.
 *
 *  @param[out]  ptrImageSize
 *      Pointer to the image size populated by the API
 *
 *  @retval
 *      Success -   CERT_RETURN_SUCCESS
 *  @retval
 *      Error   -   Cert Error codes (\ref Cert_Return_t)
 */
Cert_Return_t Cert_getImageSize (uint32_t* ptrImageSize)
{
    Cert_Context_Obj*   ptrCertContextObj;
    Cert_Return_t       retVal;
    uint32_t            postPatternIndex;

    /* Get the pointer to the certificate object: */
    ptrCertContextObj = &gCertContextObj;

    /* Get the boot information object id: */
    retVal = Cert_patternMatch (&gCertBootInfoOID[0],
                                sizeof(gCertBootInfoOID),
                                &postPatternIndex);

    /* Decode the Boot Information Extension */
    if (retVal == CERT_RETURN_SUCCESS)
    {
        retVal = Cert_decodeBootInfo (ptrCertContextObj, postPatternIndex);
        if (retVal == CERT_RETURN_SUCCESS)
        {
            /* Return the image size */
            *ptrImageSize = ptrCertContextObj->imageSize;
        }
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      The function is used to close the certificate module
 *
 *  @retval
 *      Success -   CERT_RETURN_SUCCESS
 *  @retval
 *      Error   -   Cert Error codes (\ref Cert_Return_t)
 */
Cert_Return_t Cert_close (void)
{
    Cert_Return_t ret = CERT_RETURN_SUCCESS;
    /* Reset the global certificate object */
    CPU_BROM_memset ((uint8_t*)&gCertContextObj, 0, sizeof(Cert_Context_Obj));
    return ret;
}

/**
 *  @b Description
 *  @n
 *      The function is used to initialize the certificate module
 *
 *  @retval
 *      Success -   CERT_RETURN_SUCCESS
 *  @retval
 *      Error   -   Cert Error codes (\ref Cert_Return_t)
 */
Cert_Return_t Cert_init (void)
{
    Cert_Return_t ret = CERT_RETURN_SUCCESS;
    /* Initialize the global certificate object */
    CPU_BROM_memset ((uint8_t*)&gCertContextObj, 0, sizeof(Cert_Context_Obj));
    return ret;
}

