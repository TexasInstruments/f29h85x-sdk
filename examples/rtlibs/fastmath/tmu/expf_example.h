//#############################################################################
//
// FILE:   expf_example.h
//
// TITLE:  
//
//
//#############################################################################

//*****************************************************************************
// defines
//*****************************************************************************
#define INPUT_SIZE 18
typedef float float32_t;

__attribute__((section("kernel_opt")))
static float32_t expf_opt(float32_t in)
{	
	float32_t in_scale = in * -1.44269504f;
	if(in>0.0f){
		return (1.0f/__builtin_c29_i32_iexp2f32_m(in_scale));
	}else{
		return __builtin_c29_i32_iexp2f32_m(in_scale);
	}	   
}