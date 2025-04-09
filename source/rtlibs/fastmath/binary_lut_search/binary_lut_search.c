//###########################################################################
//
// FILE:   binary_lut_search_loop.c
//
// TITLE:  Binary LUT search loop
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated -
//	All rights reserved not granted herein.
//	Limited License.
//
//    Texas Instruments Incorporated grants a world-wide, royalty-free,
//    non-exclusive license under copyrights and patents it now or hereafter
//    owns or controls to make, have made, use, import, offer to sell and sell
//    ("Utilize") this software subject to the terms herein. With respect to the
//    foregoing patent license, such license is granted solely to the extent that
//    any such patent is necessary to Utilize the software alone. The patent
//    license shall not apply to any combinations which include this software,
//    other than combinations with devices manufactured by or for TI 
//    ("TI Devices").
//    No hardware patent is licensed hereunder.
//
//    Redistributions must preserve existing copyright notices and reproduce this
//    license (including the above copyright notice and the disclaimer and
//    (if applicable) source code license limitations below) in the documentation
//     and/or other materials provided with the distribution.
//
//    Redistribution and use in binary form, without modification, are permitted
//    provided that the following conditions are met:
//
//    * No reverse engineering, decompilation, or disassembly of this software is 
//    permitted with respect to any software provided in binary form.
//    * Any redistribution and use are licensed by TI for use only 
//      with TI Devices.
//    * Nothing shall obligate TI to provide you with source code for the 
//      software licensed and provided to you in object code.
//
//    If software source code is provided to you, modification and redistribution
//    of the source code are permitted provided that the following conditions 
//    are met:
//
//    * any redistribution and use of the source code, including any resulting
//      derivative works, are licensed by TI for use only with TI Devices.
//    * any redistribution and use of any object code compiled from the source
//      code and any resulting derivative works, are licensed by TI for use 
//      only with TI Devices.
//
//    Neither the name of Texas Instruments Incorporated nor the names of its
//    suppliers may be used to endorse or promote products derived from this 
//    software without specific prior written permission.
//
//	DISCLAIMER.
//
//	THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
//	BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//	IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
//	OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//	POSSIBILITY OF SUCH DAMAGE.

//###########################################################################

#include "binary_lut_search.h"
#include <string.h>
#include <stdio.h>

typedef union {
float f32;
uint32_t ui32;
} F32_UI32;

__attribute__((section("kernel_opt")))
void binary_lut_search_closest_match(int32_t search_val, uint32_t size, int32_t lut[], uint32_t *piLeft, uint32_t *piRght)
{	
  uint32_t   Left = 0;
  uint32_t   Right = size-1;
  uint32_t   i, j; 
  F32_UI32   LoopCount;
  
  /* Find the location of current input value in the data table. */
  if (search_val <= lut[0] ) 
    {
    /* Less than or equal to the smallest point in the table. */      
    Right = 0U;
    } 
  else if (search_val >= lut[size-1] ) 
    {
    /* Greater than or equal to the largest point in the table. */
    Left = size-1;
    } 
  else 
    {
	// NOTE the neat little trick to obtain the loop count for the binary lut search
	// using this union applied on the LUT size -> identify the exponent
	// then the loop is made a fixed size loop        
    LoopCount.f32 = (float)(size);
    LoopCount.ui32 = (LoopCount.ui32 >> 23) - 126;
    
    /* Loop until end of search: */
    for(j = LoopCount.ui32; j > 0; j--)
      {
      
      i = (Left + Right) >> 1;   
      /* Move either the right index or the left index so that */
      /*  LeftDataPoint <= CurrentValue < RightDataPoint */
      if (search_val < lut[i] ) 
      {
        Right = i;
      } 
      else 
      {
        Left = i;
      }  
      }
   } 
   *piRght = Right;
   *piLeft = Left;

}

__attribute__((section("kernel_opt")))
int32_t binary_lut_search_exact_match(int32_t search_val, uint32_t size, int32_t lut[])
{
   uint32_t middle_index;
   uint32_t Left = 0;
   uint32_t Right = size-1;
   uint32_t found,j;
   F32_UI32   LoopCount;

   middle_index = 0u;
   found        = 0x0u;
   
   LoopCount.f32 = (float)(size);
   LoopCount.ui32 = (LoopCount.ui32 >> 23) - 126;

   for(j = LoopCount.ui32; j > 0; j--)
   {
      middle_index = (Right + Left)/2u;

      if (lut[middle_index] == search_val)
      {
          found = 1;
          break;
      }
      else
      {
         if (lut[middle_index] < search_val)
         {
             Left = middle_index + 1u;
         }
         else
         {
             Right = middle_index - 1u;
         }
      }
   }

   if(found)
   {
       return middle_index;
   }
   else
   {
       return -1;
   }
}

//
// End of File
//
