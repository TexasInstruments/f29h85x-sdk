//#############################################################################
//
//
// $Copyright:
//#############################################################################

#include "fir_f32.h"
#include <string.h>

#if defined __has_builtin
#  if __has_builtin(__builtin_c29_inccirc)
#    define INCCIRC(x, y) __builtin_c29_inccirc((x), (y))
#  else
#    define INCCIRC(x, y) inccirc((x), (y))
#  endif
#else
#  define INCCIRC(x, y) inccirc((x), (y))
#endif

#if defined __has_builtin
#  if __has_builtin(__builtin_c29_deccirc)
#    define DECCIRC(x, y) __builtin_c29_deccirc((x), (y))
#  else
#    define DECCIRC(x, y) deccirc((x), (y))
#  endif
#else
#  define DECCIRC(x, y) deccirc((x), (y))
#endif
// this function runs with optimal performance if the compiler option to enable debug (-g) is removed
__attribute__((section("kernel_opt")))
void fir_f32_c(FIR_f32_Handle hndFIR_f32,float32_t *restrict out, float32_t *restrict in, uint32_t input_size)
{
    uint32_t filt_size;
    float32_t *filt;
    float32_t *hist;
    int32_t circular_buff_index;
    // map the F28x handle to the F29x function arguments
    filt_size = hndFIR_f32->order;
    filt = hndFIR_f32->coeff_ptr;
    hist = hndFIR_f32->dbuffer_ptr;
    circular_buff_index = hndFIR_f32->cbindex;

    //
    // the FIR filter function
    //
    float32_t acc;
    int32_t n;
    int32_t j;
    
    //
    // apply the filter to each input sample
    //
    for ( n = 0; n < input_size; n++ ) 
    {
        hist[circular_buff_index] = in[n];
        
        //
        // calculate output n
        //
        acc = 0;
        filt = hndFIR_f32->coeff_ptr;
        for ( j = 0; j < filt_size; j++ ) {
            acc += (*filt++) * hist[circular_buff_index];
            circular_buff_index = DECCIRC(circular_buff_index, (filt_size - 1));
        }
        out[n] = acc;
        
        circular_buff_index = INCCIRC(circular_buff_index,(filt_size - 1));
    }
    hndFIR_f32->cbindex = circular_buff_index;
}

__attribute__((section("kernel_asm")))
void fir_f32_casm(FIR_f32_Handle hndFIR_f32,float32_t *restrict out, float32_t *restrict in, uint32_t input_size)
{
    //
    // the FIR filter function
    //
    float32_t acc;
    float32_t *coeffp; // pointer to coefficients
    int32_t n;
    int32_t k , circ_buffer_limit;
    int16_t cbindex;

    circ_buffer_limit = ((hndFIR_f32->order)/2) - 1;
    coeffp = (hndFIR_f32->coeff_ptr);

    //
    // apply the filter to each input sample
    //
    for ( n = 0; n < input_size; n++ ) 
    {
        cbindex = hndFIR_f32->cbindex * 2;
        (hndFIR_f32->dbuffer_ptr)[cbindex+ 1] = (hndFIR_f32->dbuffer_ptr)[cbindex];
        (hndFIR_f32->dbuffer_ptr)[cbindex] = in[n];

        //
        // calculate output n
        //
        k = hndFIR_f32->cbindex;

        out[n] =  c29_fir_sample_asm(hndFIR_f32, coeffp, &k, circ_buffer_limit);

        hndFIR_f32->cbindex = INCCIRC(hndFIR_f32->cbindex, circ_buffer_limit);
    }
}

void FIR_f32_init(FIR_f32_Handle hndFIR_f32)
{
    memset(hndFIR_f32->dbuffer_ptr,0U,sizeof(float32_t)*(hndFIR_f32->order));
    hndFIR_f32->cbindex = 0;
}
