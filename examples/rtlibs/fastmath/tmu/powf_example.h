//#############################################################################
//
// FILE:   powf_example.h
//
// TITLE:  
//
//
//#############################################################################

//*****************************************************************************
// defines
//*****************************************************************************
#define INPUT_SIZE 7
typedef float float32_t;

__attribute__((section("kernel_opt"))) 
static float powf_opt(float x, float y)
{
  float log2ofx = __builtin_c29_i32_log2f32_m (x);
  float log2ofxtimesy = log2ofx * y;

  float iexp2f = __builtin_c29_i32_iexp2f32_m(log2ofxtimesy);
	if (log2ofxtimesy > 0.0f) return (1.0f / iexp2f);
	else          return (iexp2f);
}
