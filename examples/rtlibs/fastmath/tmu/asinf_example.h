//#############################################################################
//
// FILE:   asinf_example.h
//
// TITLE:  
//
//
//#############################################################################

//*****************************************************************************
// defines
//*****************************************************************************
typedef float float32_t;
__attribute__((section("kernel_opt")))
static inline float32_t asinf_opt(float32_t in)
{
    uint32_t flags;
    float32_t x = __builtin_c29_i32_sqrtf32_m(1-(in*in));
    return __builtin_c29_quadf32(&flags, &in, &x) + \
           __builtin_c29_i32_puatanf32_m(in / x);
}