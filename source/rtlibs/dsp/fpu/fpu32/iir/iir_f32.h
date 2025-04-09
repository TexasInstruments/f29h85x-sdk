//#############################################################################
//
//
// $Copyright:
//#############################################################################
#ifndef _IIR_F32_H_
#define _IIR_F32_H_
//#############################################################################
//
// FILE:   iir_f32.h
//
// TITLE:  IIR structures and prototypes
//
//
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>
#include "math.h"
//!
//! \defgroup DSP_IIR_F32 IIR

//!
//! \addtogroup DSP_IIR_F32
// @{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************


//*****************************************************************************
// typedefs
//*****************************************************************************
typedef float float32_t;

//! \brief Function pointer with a void pointer argument returning nothing
//!
typedef void (*v_pfn_v)(void *);

//! \brief 32-bit Single Precision Float
//! The union of a single precision value, an unsigned long and a signed
//! long allows for manipulation of the hex representation of the floating
//! point value as well as signed and unsigned arithmetic to determine error 
//! metrics.
//!
typedef union
{
    uint32_t    ui32; //!< Unsigned long representation
    int32_t     i32;  //!< Signed long represntaion 
    float32_t   f32;  //!< Single precision (32-bit) representation
} float32u_t;

//*****************************************************************************
// defines
//*****************************************************************************
//#define NULL    0
#if (USE_LEGACY_NAMES==0U)
//! FIR_FP is the legacy name of the FIR structure
#define FIR_FP          FIR_f32          
//! FIR_FP_Handle is the legacy name of the FIR structure handle
#define FIR_FP_Handle   FIR_f32_Handle  
//! FIR_FP_init is the legacy name of the FIR initialization function
#define FIR_FP_init     FIR_f32_init 
//! FIR_FP_calc is the legacy name of the FIR calculation function
#define FIR_FP_calc     FIR_f32_calc    
#endif // USE_LEGACY_NAMES

//*****************************************************************************
// typedefs
//*****************************************************************************
//! Structure for the Finite Impulse Response Filter
//!
typedef struct { 
    float *coeff_ptr;        //!<  Pointer to Filter coefficient
    float *dbuffer_ptr;      //!<  Delay buffer pointer
    int16_t cbindex;         //!<  Circular Buffer Index
    int16_t order;           //!<  Order of the Filter
    float input;             //!<  Latest Input sample
    float output;            //!<  Filter Output
    void (*init)(void *);    //!<  Pointer to Initialization function
    void (*calc)(void *);    //!<  Pointer to the calculation function
    }FIR_f32;

//! Handle to the Filter Structure Object
typedef FIR_f32     *FIR_f32_Handle;

//! The default FIR object initializer
#define FIR_f32_DEFAULTS { (float *)NULL, \
             (float *)NULL,  \
             0,              \
             50,             \
             0,              \
             0,              \
             (void (*)(void *))FIR_f32_init,\
             (void (*)(void *))FIR_f32_calc}    

//! Structure defintion for the Infinite Impulse Response Filter
//!             
typedef struct { 
    float *p_coeff_A;        //!<  Pointer to the denominator coefficients
    float *p_coeff_B;        //!<  Pointer to the numerator coefficients
    float *p_dbuffer;        //!<  Delay buffer pointer
    float *p_input;          //!<  Pointer to the latest input sample
    float *p_output;         //!<  Pointer to the filter output
    float *p_scale;          //!<  Pointer to the biquad(s) scale values
    uint16_t order;          //!<  Order of the filter
    void (*init)(void *);    //!<  Pointer to the initialization function
    void (*calc)(void *);    //!<  Pointer to the calculation function
}IIR_f32;

//! Handle to the Filter Structure Object
typedef IIR_f32 *IIR_f32_Handle;

//*****************************************************************************
// 'inline' function
//*****************************************************************************
//! \brief Set the coefficients pointer
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] pc  pointer to the coefficients
//!
static inline void FIR_f32_setCoefficientsPtr(FIR_f32_Handle fh,
        const float *pc)
{
    fh->coeff_ptr = (float *)pc;
}

//! \brief Get the coefficients pointer
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pc  pointer to the coefficients
//!
static inline float * FIR_f32_getCoefficientsPtr(FIR_f32_Handle fh)
{
    return(fh->coeff_ptr);
}

//! \brief Set the delay line pointer
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] pdl  pointer to the delay line
//!
static inline void FIR_f32_setDelayLinePtr(FIR_f32_Handle fh,
        const float *pdl)
{
    fh->dbuffer_ptr = (float *)pdl;
}

//! \brief Get the delay line pointer
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pdl  pointer to the delay line
//!
static inline float * FIR_f32_getDelayLinePtr(FIR_f32_Handle fh)
{
    return(fh->dbuffer_ptr);
}

//! \brief Set the input
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] in  current input
//!
static inline void FIR_f32_setInput(FIR_f32_Handle fh,
        const float in)
{
    fh->input = in;
}

//! \brief Get the input
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pin  current input pointer
//!
static inline float FIR_f32_getInput(FIR_f32_Handle fh)
{
    return(fh->input);
}

//! \brief Set the output
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] out  current output
//!
static inline void FIR_f32_setOutput(FIR_f32_Handle fh,
        const float out)
{
    fh->output = out;
}

//! \brief Get the output
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return out  current output
//!
static inline float FIR_f32_getOutput(FIR_f32_Handle fh)
{
    return(fh->output);
}


//! \brief Set the order of the filter
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] order  Order of the filter
//!
static inline void FIR_f32_setOrder(FIR_f32_Handle fh, const uint16_t order)
{
    fh->order = order;
}

//! \brief Get the order of the filter
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return order  Order of the filter
//!
static inline uint16_t FIR_f32_getOrder(FIR_f32_Handle fh)
{
    return(fh->order);
}

//! \brief Set the init function
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] pfn  pointer to the init function
//!
static inline void FIR_f32_setInitFunction(FIR_f32_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->init = pfn;
}

//! \brief Get the init function
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pfn  pointer to the init function
//!
static inline v_pfn_v FIR_f32_getInitFunction(FIR_f32_Handle fh)
{
    return(fh->init);
}

//! \brief Set the calc function
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] pfn  pointer to the calc function
//!
static inline void FIR_f32_setCalcFunction(FIR_f32_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->calc = pfn;
}

//! \brief Get the calc function
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pfn  pointer to the calc function
//!
static inline v_pfn_v FIR_f32_getCalcFunction(FIR_f32_Handle fh)
{
    return(fh->calc);
}

//! \brief Set the denominator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pca  pointer to the denominator coefficients
//!
static inline void IIR_f32_setCoefficientsAPtr(IIR_f32_Handle fh,
        const float *pca)
{
    fh->p_coeff_A = (float *)pca;
}

//! \brief Get the denominator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pca  pointer to the denominator coefficients
//!
static inline float * IIR_f32_getCoefficientsAPtr(IIR_f32_Handle fh)
{
    return(fh->p_coeff_A);
}

//! \brief Set the numerator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pcb  pointer to the numerator coefficients
//!
static inline void IIR_f32_setCoefficientsBPtr(IIR_f32_Handle fh,
        const float *pcb)
{
    fh->p_coeff_B = (float *)pcb;
}

//! \brief Get the numerator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pca  pointer to the numerator coefficients
//!
static inline float * IIR_f32_getCoefficientsBPtr(IIR_f32_Handle fh)
{
    return(fh->p_coeff_B);
}

//! \brief Set the delay line pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pdl  pointer to the delay line
//!
static inline void IIR_f32_setDelayLinePtr(IIR_f32_Handle fh,
        const float *pdl)
{
    fh->p_dbuffer = (float *)pdl;
}

//! \brief Get the delay line pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pdl  pointer to the delay line
//!
static inline float * IIR_f32_getDelayLinePtr(IIR_f32_Handle fh)
{
    return(fh->p_dbuffer);
}

//! \brief Set the input pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pi  pointer to the current input
//!
static inline void IIR_f32_setInputPtr(IIR_f32_Handle fh,
        const float *pi)
{
    fh->p_input = (float *)pi;
}

//! \brief Get the input pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pi  pointer to the current input
//!
static inline float * IIR_f32_getInputPtr(IIR_f32_Handle fh)
{
    return(fh->p_input);
}

//! \brief Set the output pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] po  pointer to the current output
//!
static inline void IIR_f32_setOutputPtr(IIR_f32_Handle fh,
        const float *po)
{
    fh->p_output = (float *)po;
}

//! \brief Get the output pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return po  pointer to the current output
//!
static inline float * IIR_f32_getOutputPtr(IIR_f32_Handle fh)
{
    return(fh->p_output);
}

//! \brief Set the scale value pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] psv  pointer to the scale values for the biquads
//!
static inline void IIR_f32_setScalePtr(IIR_f32_Handle fh,
        const float *psv)
{
    fh->p_scale = (float *)psv;
}

//! \brief Get the scale value pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return psv  pointer to the scale values for the biquads
//!
static inline float * IIR_f32_getScalePtr(IIR_f32_Handle fh)
{
    return(fh->p_scale);
}

//! \brief Set the order of the filter
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] order  Order of the filter
//!
static inline void IIR_f32_setOrder(IIR_f32_Handle fh, const uint16_t order)
{
    fh->order = order;
}

//! \brief Get the order of the filter
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return order  Order of the filter
//!
static inline uint16_t IIR_f32_getOrder(IIR_f32_Handle fh)
{
    return(fh->order);
}

//! \brief Set the init function
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pfn  pointer to the init function
//!
static inline void IIR_f32_setInitFunction(IIR_f32_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->init = pfn;
}

//! \brief Get the init function
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pfn  pointer to the init function
//!
static inline v_pfn_v IIR_f32_getInitFunction(IIR_f32_Handle fh)
{
    return(fh->init);
}

//! \brief Set the calc function
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pfn  pointer to the calc function
//!
static inline void IIR_f32_setCalcFunction(IIR_f32_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->calc = pfn;
}

//! \brief Get the calc function
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pfn  pointer to the calc function
//!
static inline v_pfn_v IIR_f32_getCalcFunction(IIR_f32_Handle fh)
{
    return(fh->calc);
}

//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//
// Function: iir_f32
// Optimized C implementation
// iir_f32_sample filters a single input sample
// iir_f32_loop filters a block of samples
//
extern void iir_f32_sample(IIR_f32_Handle hndIIR_f32);
extern void iir_f32_loop(IIR_f32_Handle hndIIR_f32, uint32_t N);


//! \brief Finite Impulse Response Filter.
//!
//! This routine implements the non-recursive difference equation of an
//! all-zero filter (FIR), of order N. All the coefficients of all-zero filter
//! are assumed to be less than 1 in magnitude.
//! \param hndFIR_f32 Handle to the FIR_f32 object
//! \attention
//! -# The delay and coefficients buffer must be aligned to a minimum of 
//! 2 x (order + 1) words.
//! For example, if the filter order is 31, it will have 32 taps or 
//! coefficients each a 32-bit floating point value. A minimum of 
//! (2 * 32) = 64 words will need to be allocated for the delay and 
//! coefficients buffer.
//! -# To align the buffer, use the DATA_SECTION pragma to assign the buffer to
//! a code section and then align the buffer to the proper offset in the linker
//! command file. In the code example the buffer is assigned to the \b firldb 
//! section while the coefficients are assigned to the \b coefffilt section.
//! -# This routine requires the --c2xlp_src_compatible option to be enabled 
//! in the file specific properties when accepting 24x assembly instructions.
//! This option is ONLY used if you are migrating C24x code to the C28x, and is
//! not available for compilers after v6.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Number of Taps (Order + 1) <th> Cycles 
//! <tr><td> 28                         <td> 103
//! <tr><td> 59                         <td> 165
//! <tr><td> 117                        <td> 281
//! </table>
//
extern void FIR_f32_calc(FIR_f32_Handle hndFIR_f32);

//! \brief Finite Impulse Response Filter Initialization.
//!
//! Zeros out the delay line 
//! \param hndFIR_f32 Handle to the FIR_f32 object
//! \attention
//! -# The delay and coefficients buffer must be aligned to a minimum of 
//! 2 x (order + 1) words.
//! For example, if the filter order is 31, it will have 32 taps or 
//! coefficients each a 32-bit floating point value. A minimum of (2 * 32) = 64 
//! words will need to be allocated for the delay and coefficients buffer.
//! -# The delay buffer needs to be aligned to word boundary of 2 * number of 
//! taps
//! -# To align the buffer, use the DATA_SECTION pragma to assign the buffer to
//! a code section and then align the buffer to the proper offset in the linker
//! command file. In the code example the buffer is assigned to the \b firldb
//! section while the coefficients are assigned to the \b coefffilt section.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Number of Taps (Order + 1) <th> Cycles 
//! <tr><td> 28                         <td>  79
//! <tr><td> 59                         <td> 141
//! <tr><td> 117                        <td> 257
//! </table>
//
extern void FIR_f32_init(FIR_f32_Handle hndFIR_f32);

//! \brief Infinite Impulse Response Filter.
//!
//! This routine implements the Transposed Direct form II recursive 
//! difference equation of an N pole-zero filter(IIR). 
//! \param hndIIR_f32 Handle to the IIR_f32 object
//! \attention
//! -# The delay line buffer must be 2*(n_biquads*n_delay_elements_per_biquad),
//! since there are 4 delay elements per biquad that are single precision
//! (32-bits) we require a total of 8*n_biquads words
//! For example, if the filter is an 8th order filter it would require 4 
//! biquads (each biqaud is a 2nd order construct) hence 8*4 = 32 words
//! If the filter were a 9th order filter, it would require 5 biquads; the 
//! first four would be quadratic while the last is linear. The last biquad
//! will be implemented with the B[2] and A[2] coefficients zero.
//! We would require a total of 8*5 = 40 words
//! -# In the code example the buffer is assigned to the \b .ebss
//! section while the coefficients are assigned to the \b .econst section.
//! 
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Filter Order <th> Number of Biquads <th> Cycles 
//! <tr><td> 2            <td> 1                 <td>  68
//! <tr><td> 6            <td> 3                 <td> 116
//! <tr><td> 12           <td> 6                 <td> 188
//! </table>
//
extern void IIR_f32_calc(IIR_f32_Handle hndIIR_f32);

//! \brief Infinite Impulse Response Filter Initialization.
//!
//! Zeros out the delay line 
//! \param hndIIR_f32 Handle to the IIR_f32 object
//! \attention Please see the description of IIR_f32_calc for more details
//! on the space requirements for the delay line and coefficients
//! 
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Filter Order <th> Number of Biquads <th> Cycles 
//! <tr><td> 2            <td> 1                 <td> 30
//! <tr><td> 6            <td> 3                 <td> 46
//! <tr><td> 12           <td> 6                 <td> 70
//! </table>
//
extern void IIR_f32_init(IIR_f32_Handle hndIIR_f32);


// @} //addtogroup


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_FILTER_H_

// End of File
