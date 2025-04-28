/*
 * Certificate Header file
 *
 * Certificate module exported header file
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 */
#ifndef CERT_H
#define CERT_H

#include <stdint.h>

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
