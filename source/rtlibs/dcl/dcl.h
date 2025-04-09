//#############################################################################
//
//
// $Copyright:
//#############################################################################

#ifndef _DCL_H_
#define _DCL_H_

#ifdef __cplusplus
extern "C" {
#endif

 /**
 * \defgroup RTLIBS_API APIs for Real Time Libraries
 *
 * This module contains APIs for real time libraries in this SDK.
 */

/**
 *  \defgroup DCL_API_MODULE APIs for Digital Control Library
 *  \ingroup  RTLIBS_API
 *  
 *  Here is the list of APIs used for Digital Control Library
 *  @{
 *
 *  \file     dcl.h
 *  \brief    Top level header that contains all collections of Digital Controller Library functions
 *  
 *  \details  To use this library, simply use
 *  \code     #include "dcl.h" \endcode
 *            while making sure the path to this file is added as a compiler include path
 */

//! \brief          Library version number formatted for numerical comparison
//!                 v4.02.00.00
#define DCL_VERSION 4020000

//! \brief          Enable voltaile flag for dcl strcutures
//!                 Disabled by default
//#define DCL_VOLATILE_ENABLED

//! \brief          Build the library with error handling enabled
//!                 Performs error checks on various update and
//!                 stability functions
//!                 Disabled by default
//#define DCL_ERROR_HANDLING_ENABLED

//! \brief          Build the library with test points enabled
//!                 during arthmetic operations
//!                 Disabled by default
//#define DCL_TESTPOINTS_ENABLED

/* Includes legacy API */
#ifndef DCL_NO_LEGACY_API
#include "misc/dcl_c28_compatibility.h"
#endif

/* utilities */
#include "misc/dcl_error.h"
#include "misc/dcl_fdlog.h"
#include "misc/dcl_gsm.h"
#include "misc/dcl_mlog.h"
#include "misc/dcl_refgen.h"
#include "misc/dcl_tcm.h"

/* 32bit arithmetic */
#include "pi/dcl_pi.h"
#include "pi/dcl_pi2.h"
#include "pid/dcl_pid.h"
#include "pid/dcl_nlpid.h"

#include "df/dcl_df11.h"
#include "df/dcl_df12.h"
#include "df/dcl_df13.h"
#include "df/dcl_df22.h"
#include "df/dcl_df23.h"

/* 64bit arithmetic */
#include "pid/dcl_pidf64.h"

/** @} */

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _DCL_H_
