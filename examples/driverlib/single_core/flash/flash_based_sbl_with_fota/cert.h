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

#ifndef CERT_H
#define CERT_H

#include <stdint.h>
#include "cpubrom.h"

/**
@defgroup CERT_MODULE       CERT Module
@ingroup MODULE
@brief
*   CERT Module
*
@details
*   The module is used to handle the X509 certificate parsing in the
*   R5 Domain. The certificate parsing is minimal and is used to only
*   parse the certificate length and to extract the image size from the
*   boot extension.
*/

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CERT_MODULE
 @{ */

/**************************************************************************
 **************************** Configurations ******************************
 **************************************************************************/

/**
 * @brief   X509 Certificates are encoded with Tag, Length and Value.
 * With Length in Long Format; this size can support a length of 2 bytes
 * i.e. 0xFFFF. This should be sufficient for the X509 Certificate size
 */
#define CONFIG_CERT_SIZE                (4U)

#define CSL_FEXTR(reg, msb, lsb)        (((reg) >> (lsb)) & ((1 << ((msb) - (lsb) + 1)) - 1))

/**************************************************************************
 ****************************** Structures ********************************
 **************************************************************************/

/**
 * @brief
 *  Certificate Error code
 *
 * @details
 *  The enumeration describes all the possible return and error codes which
 *  the Certificate functions can return.
 */
typedef enum CERT_RETURN_TYPE_
{
    CERT_RETURN_SUCCESS     = 0x81098709U,  /*!< Success/pass return code   */
    CERT_RETURN_PARSE_FAIL  = 0x4E5EEB96U,  /*!< Parsing Error              */
    CERT_RETURN_BAD_PARAMS  = 0x20035CF9U,  /*!< Bad Parameters             */
    CERT_RETURN_ERROR       = 0xF069BBCEU,  /*!< Cert parse failed          */
}Cert_Return_t;

/**************************************************************************
 ************************* Exported Functions *****************************
 **************************************************************************/

extern Cert_Return_t Cert_init (void);
extern Cert_Return_t Cert_getLength (uint8_t* ptrCertBuffer, uint32_t sizeBuffer, uint32_t* ptrCertLength);
extern Cert_Return_t Cert_getImageSize (uint32_t* ptrImageSize);
extern Cert_Return_t Cert_close (void);

/**
@}
*/

#ifdef __cplusplus
}
#endif

#endif /* CERT_H */
