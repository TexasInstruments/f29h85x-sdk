//#############################################################################
//
// FILE:   roundf_example.h
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
static float32_t roundf_opt(float32_t in)
{
	float32_t out;
	float32_t temp = in+0.5f;

	out = (temp < 0) ? (temp - __builtin_c29_i32_fracf32_m(temp) - 1.0f) : (temp - __builtin_c29_i32_fracf32_m(temp));
	return out;
}