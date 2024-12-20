//###############################################################################
//! \file /2838x_vcrc_config_poly/vcrc_configpoly.h
//!
//! \brief  Header file for the configurable polynomial and data sizes (VCRC and C)
//#############################################################################

//!
//! \defgroup VCRC_APIS VCRC Configurable Polynomial APIs

//!
//! \ingroup VCRC_APIS
// @{

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief Runs the CRC routine using provided polynomial
//!        with the input bits reversed, message size in bytes. 
//!
//!  The polynomial to be used is set by the element \b polynomial in the \b CRC_Obj.
//!  The size of the polynomial is set by the element \b polySize in the \b CRC_Obj.
//!  For example - to use a 1 bit polynomial \b polySize must be set to 0x0 and 
//!  to use a 32 bit polynomial \b polySize must be set to 0x1F. The size of the data is set 
//!  by the element \b dataSize in \b the CRC_Obj. \b Datasize refers to the integral unit 
//!  on which the CRC is computed. For example - to use data size of 1 bit \b dataSize must be set
//!  to 0x0 and data size of 8 bit is set by setting \b dataSize to a value of 0x7. These values
//!  finally translate to elements in the \b VCRCSIZE register - \b PSIZE and \b DSIZE fields and they are 
//!  set in the functions \b _CRC_runConfigPolyBytes implemented in the asm file \b vcrc_configpoly_asm.asm.
//!  Total size of the message on which the CRC to be computed is specified by the element \b MsgBytes 
//!  in the \b CRC_Obj.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_runConfigPolyBytesReflected(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using provided polynomial
//!        with the input bits reversed, message size in bits. 
//!
//!  The polynomial to be used is set by the element \b polynomial in the \b CRC_Obj.
//!  The size of the polynomial is set by the element \b polySize in the \b CRC_Obj.
//!  For example - to use a 1 bit polynomial \b polySize must be set to 0x0 and 
//!  to use a 32 bit polynomial \b polySize must be set to 0x1F. The size of the data is set 
//!  by the element \b dataSize in \b the CRC_Obj. \b Datasize refers to the integral unit 
//!  on which the CRC is computed. For example - to use data size of 1 bit \b dataSize must be set
//!  to 0x0 and data size of 8 bit is set by setting \b dataSize to a value of 0x7. These values
//!  finally translate to elements in the \b VCRCSIZE register - \b PSIZE and \b DSIZE fields and they are 
//!  set in the functions \b _CRC_runConfigPolyBytes implemented in the asm file \b vcrc_configpoly_asm.asm.
//!  Total size of the message on which the CRC to be computed is specified by the element \b MsgBytes 
//!  in the \b CRC_Obj.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_runConfigPolyBitsReflected(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using provided polynomial with message size in bytes. 
//!
//!  The polynomial to be used is set by the element \b polynomial in the \b CRC_Obj.
//!  The size of the polynomial is set by the element \b polySize in the \b CRC_Obj.
//!  For example - to use a 1 bit polynomial \b polySize must be set to 0x0 and 
//!  to use a 32 bit polynomial \b polySize must be set to 0x1F. The size of the data is set 
//!  by the element \b dataSize in \b the CRC_Obj. \b Datasize refers to the integral unit 
//!  on which the CRC is computed. For example - to use data size of 1 bit \b dataSize must be set
//!  to 0x0 and data size of 8 bit is set by setting \b dataSize to a value of 0x7. These values
//!  finally translate to elements in the \b VCRCSIZE register - \b PSIZE and \b DSIZE fields and they are 
//!  set in the functions \b _CRC_runConfigPolyBytes implemented in the asm file \b vcrc_configpoly_asm.asm.
//!  Total size of the message on which the CRC to be computed is specified by the element \b MsgBytes 
//!  in the \b CRC_Obj.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_runConfigPolyBytes(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using provided polynomial with message size in bits. 
//!
//!  The polynomial to be used is set by the element \b polynomial in the \b CRC_Obj.
//!  The size of the polynomial is set by the element \b polySize in the \b CRC_Obj.
//!  For example - to use a 1 bit polynomial \b polySize must be set to 0x0 and 
//!  to use a 32 bit polynomial \b polySize must be set to 0x1F. The size of the data is set 
//!  by the element \b dataSize in \b the CRC_Obj. \b Datasize refers to the integral unit 
//!  on which the CRC is computed. For example - to use data size of 1 bit \b dataSize must be set
//!  to 0x0 and data size of 8 bit is set by setting \b dataSize to a value of 0x7. These values
//!  finally translate to elements in the \b VCRCSIZE register - \b PSIZE and \b DSIZE fields and they are 
//!  set in the functions \b _CRC_runConfigPolyBytes implemented in the asm file \b vcrc_configpoly_asm.asm.
//!  Total size of the message on which the CRC to be computed is specified by the element \b MsgBytes 
//!  in the \b CRC_Obj.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_runConfigPolyBits(CRC_Handle hndCRC);

// @} //ingroup
