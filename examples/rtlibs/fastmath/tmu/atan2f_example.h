//#############################################################################
//
// FILE:   atan2f_example.h
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
static inline float32_t puatan2f32(float32_t y, float32_t x)
{
    uint32_t flags;
    return __builtin_c29_quadf32(&flags, &y, &x) + \
           __builtin_c29_i32_puatanf32_m(y / x);
}