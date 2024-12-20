//#############################################################################
//
// FILE:   fmodf_example.h
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
static float32_t fmodf_opt(float32_t Num, float32_t Den)
{
	float32_t Rem;
	float32_t temp_int;
	float32_t temp_div = Num/Den;

        temp_int = temp_div - __builtin_c29_i32_fracf32_m(temp_div);                
        Rem = Num - temp_int*Den;

	return	Rem;
}