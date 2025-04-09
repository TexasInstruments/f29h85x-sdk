//#############################################################################
//
//
// $Copyright:
//#############################################################################
#include "cfft_f32.h"

#define bit(a,b) ( ( (b)>>(a) ) & 0x1)
#define PI 3.14159265358979F

// this is the out-of-place hand-optimized assembly implementation
// assumes that the input array has already been bit-reversed.
// this function is in C, and wraps around the 4 hand-optimized assembly functions
// the 4 hand-optimized assembly functions are for (stages 1,2), (stage 3), (stage 4), (stages 5 and up)
__attribute__((section("kernel_asm"))) void
CFFT_f32_asm(CFFT_F32_STRUCT_Handle hndCFFT_F32) {
  
  complex_T *v;
  complex_T *twiddle;
  int32_t buf_size;
  int32_t num_stages;
  complex_T *swap_buf;
  int32_t swap_buf_int;

  // map the F28x handle to the F29x function arguments
  v = (complex_T *)(hndCFFT_F32->InPtr);
  twiddle = (complex_T *)(hndCFFT_F32->CoefPtr);
  buf_size = hndCFFT_F32->FFTSize;
  num_stages = hndCFFT_F32->Stages;
  swap_buf = (complex_T *)(hndCFFT_F32->OutPtr);
  swap_buf_int = (int32_t)(swap_buf);

  // hand optimized assembly
  CFFT_f32_stage_1_2_asm_opt(buf_size, hndCFFT_F32->OutPtr, hndCFFT_F32->InPtr);
  
  CFFT_f32_stages_3_asm_opt(buf_size, hndCFFT_F32->InPtr,  hndCFFT_F32->OutPtr, buf_size/2, (float *)twiddle);

  CFFT_f32_stages_4_asm_opt(buf_size, hndCFFT_F32->OutPtr,  hndCFFT_F32->InPtr, buf_size/2, (float *)twiddle);

  CFFT_f32_stages_5plus_asm_opt(v, twiddle, buf_size, num_stages,swap_buf_int);
  
}


// this is the in-place optimized C implementation
// assumes that the input array has already been bit-reversed.
// The table_size_factor is used whenever you are using a Twiddle factor table
// size which is larger than the FFT size. For example, if you use a 16-point
// FFT and the twiddle_factor tables were generated for 256 points, then use a
// table_size_factor of 4 (256/16 = 16 which is 2^4 and hence 4)
__attribute__((section("kernel_opt"))) void
CFFT_f32_c(CFFT_F32_STRUCT_Handle hndCFFT_F32) {
  
  complex_T *v;
  complex_T *twiddle;
  int32_t buf_size;
  int32_t num_stages;
  int32_t table_size_factor=0;

  // map the F28x handle to the F29x function arguments
  v = (complex_T *)(hndCFFT_F32->InPtr);
  twiddle = (complex_T *)(hndCFFT_F32->CoefPtr);
  buf_size = hndCFFT_F32->FFTSize;
  num_stages = hndCFFT_F32->Stages;

  complex_T tmp;
  int32_t DFTStage;
  int32_t SampleIndex;
  int32_t GroupIndex;
  int32_t NumberOfSamplesInGroup;
  int32_t NumberOfGroups;
  int32_t CombinedIndex;
  int32_t HalfOfSamplesInGroup;
  int32_t t_index = 0, t_increment = 0;

  // v aligned as a local in driver
  v = __builtin_assume_aligned(v, 8);
  // twiddle aligned at definition in idat.c
  twiddle = __builtin_assume_aligned(twiddle, 8);

  // Peeled iteration (DFTStage = 0)
  NumberOfGroups = buf_size / 2;

  // Perform the Butterfly calculation on each group
  for (GroupIndex = 0; GroupIndex < NumberOfGroups; GroupIndex++) {
    t_index = 0;
    CombinedIndex = 2 * GroupIndex;

    tmp.Re = ((v[CombinedIndex + 1].Re *
               twiddle[t_index << table_size_factor].Re) +
              (v[CombinedIndex + 1].Im *
               twiddle[t_index << table_size_factor].Im));
    tmp.Im = ((v[CombinedIndex + 1].Im *
               twiddle[t_index << table_size_factor].Re) -
              (v[CombinedIndex + 1].Re *
               twiddle[t_index << table_size_factor].Im));

    // The Butterfly operation.
    v[CombinedIndex + 1].Re =
        v[CombinedIndex].Re - tmp.Re;
    v[CombinedIndex + 1].Im =
        v[CombinedIndex].Im - tmp.Im;

    v[CombinedIndex].Re = v[CombinedIndex].Re + tmp.Re;
    v[CombinedIndex].Im = v[CombinedIndex].Im + tmp.Im;
    t_index = (t_index + t_increment);
  }
  t_increment = NumberOfGroups >> 1;

  NumberOfSamplesInGroup = 4;
  NumberOfGroups = buf_size >> 2;
  HalfOfSamplesInGroup = 2;

  // Main FFT calculation loop
  __builtin_assume(num_stages >= 5);
  for (DFTStage = 1; DFTStage < num_stages; DFTStage++) {
    // Perform the Butterfly calculation on each group
    for (GroupIndex = 0; GroupIndex < NumberOfGroups; GroupIndex++) {
      t_index = 0;
      for (SampleIndex = 0; SampleIndex < HalfOfSamplesInGroup; SampleIndex++) {
        CombinedIndex = NumberOfSamplesInGroup * GroupIndex + SampleIndex;

        tmp.Re = ((v[CombinedIndex + HalfOfSamplesInGroup].Re *
                   twiddle[t_index << table_size_factor].Re) +
                  (v[CombinedIndex + HalfOfSamplesInGroup].Im *
                   twiddle[t_index << table_size_factor].Im));
        tmp.Im = ((v[CombinedIndex + HalfOfSamplesInGroup].Im *
                   twiddle[t_index << table_size_factor].Re) -
                  (v[CombinedIndex + HalfOfSamplesInGroup].Re *
                   twiddle[t_index << table_size_factor].Im));

        // The Butterfly operation.
        v[CombinedIndex + HalfOfSamplesInGroup].Re =
            v[CombinedIndex].Re - tmp.Re;
        v[CombinedIndex + HalfOfSamplesInGroup].Im =
            v[CombinedIndex].Im - tmp.Im;

        v[CombinedIndex].Re = v[CombinedIndex].Re + tmp.Re;
        v[CombinedIndex].Im = v[CombinedIndex].Im + tmp.Im;
        t_index = (t_index + t_increment);
      }
    }
    HalfOfSamplesInGroup = NumberOfSamplesInGroup;
    NumberOfSamplesInGroup <<= 1;
    NumberOfGroups >>= 1;
    t_increment = NumberOfGroups;
  }
}


__attribute__((aligned(8)))    // align object on 8-byte boundary
// Bit reverse the inputs - the function bit reverses the input array and returns it in the same array	(in place)
void CFFT_f32_bitrev(complex_T *in, complex_T *out, uint32_t buf_size) {
 int32_t i;
 uint32_t tmp_array[32], in_index, oper1, oper2;

 oper2 = buf_size/2;
 for (i=0; i<=31; i++)
   tmp_array[i] = bit( (31-i), oper2);
   oper2 = 0;
 for (i=0; i<=31; i++)
   oper2 = oper2 | (tmp_array[i]<<i) ;
 // Now oper2 contains Bit-reversed value of buf_size;

// The algorithm is as follows.
// Bit-reverse the input_index. The addition value is already bit-reversed in oper2
// Add the two. Bit-reverse the result. This will be bit-reversed output index
//  
out[0].Re = in[0].Re;
out[0].Im = in[0].Im;

 oper1 = 0;
 for (in_index = 1; in_index < buf_size; in_index++) {
	 //// This is the bit-reversal
	 for (i=0; i<=31; i++)
	   tmp_array[i] = bit( (31-i), oper1);   	
	oper1 = 0;
 	for (i=0; i<=31; i++)
	   oper1 = oper1 | (tmp_array[i]<<i) ;
 

	oper1 = oper1 + oper2;

	 //// This is the bit-reversal
	 for (i=0; i<=31; i++)
	   tmp_array[i] = bit( (31-i), oper1);   	
	oper1 = 0;
 	for (i=0; i<=31; i++)
	   oper1 = oper1 | (tmp_array[i]<<i) ;
	   
//	printf("BR - %d\n", oper1);
	out[in_index].Re = in[oper1].Re;
	out[in_index].Im = in[oper1].Im;	
 }
  
  // Put it back into the input array. 
 for (in_index = 1; in_index < buf_size; in_index++)  {
	in[in_index].Re = out[in_index].Re;
	in[in_index].Im = out[in_index].Im;	
         
 }
}

// computes the twiddle factors
void CFFT_f32_computeTwiddle(CFFT_F32_STRUCT_Handle cfft)
{
    int16_t    i, j;

    for (i = 0, j=0; i < cfft->FFTSize; i++,j+=2) {
        cfft->CoefPtr[j] = cosf((float32_t)(2*PI*i/cfft->FFTSize));
        cfft->CoefPtr[j+1] = sinf((float32_t)(2*PI*i/cfft->FFTSize)); 
    }

}

// computes the magnitude
void CFFT_f32_mag(CFFT_F32_STRUCT_Handle cfft)
{
    int16_t    i,j;

    for (i = 0,j=0; i < cfft->FFTSize; i++,j+=2) {
        cfft->CurrentOutPtr[i] = sqrtf((cfft->CurrentInPtr[j]*cfft->CurrentInPtr[j]) + (cfft->CurrentInPtr[j+1]*cfft->CurrentInPtr[j+1]));         
    }

}

// computes the phase
void CFFT_f32_phase(CFFT_F32_STRUCT_Handle cfft)
{
    int16_t    i,j;

    for (i = 0,j=0; i < cfft->FFTSize; i++,j+=2) {
        cfft->CurrentOutPtr[i] = atan2f(cfft->CurrentInPtr[j+1],cfft->CurrentInPtr[j]);         
    }

}

// interleaves 0s to convert a real input to a complex input
void CFFT_f32_unpack(CFFT_F32_STRUCT_Handle cfft)
{
  int16_t    i,j;
    for (i = 0,j=0; i < cfft->FFTSize; i++,j+=2) {      
        cfft->OutPtr[j] = cfft->InPtr[i];
        cfft->OutPtr[j+1] = 0.0f;
    }
}
//
// End of File
//
