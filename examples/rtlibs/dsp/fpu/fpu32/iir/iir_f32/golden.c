//#############################################################################
//
// FILE:   golden.c
//
// TITLE:  
//
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary formsF, with or without 
// modificationF, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   noticeF, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   noticeF, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIESF, INCLUDINGF, BUT NOT 
// LIMITED TOF, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECTF, INDIRECTF, INCIDENTALF, 
// SPECIALF, EXEMPLARYF, OR CONSEQUENTIAL DAMAGES (INCLUDINGF, BUT NOT 
// LIMITED TOF, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USEF,
// DATAF, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITYF, WHETHER IN CONTRACTF, STRICT LIABILITYF, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWAREF, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################
#include "iir_f32_example.h"
#include <iir_f32.h>

const float32_t test_golden[100] = {
 13.7502909F, 39.600769F, 62.973877F, 69.0921555F,
53.8437271F, 22.7257996F,-14.5270061F,-46.1555328F,
-61.443203F,-57.2179985F,-40.0605164F,-19.8626442F,
-2.90206861F,8.36967182F,13.0486326F,12.0670404F,
8.20343971F,3.82709217F,0.449020863F,0.505976677F,
5.78060293F,13.2966537F,17.0899296F,15.524477F,
12.7241297F,11.2687216F,8.13967037F,0.366657019F,
-9.51029301F,-16.6449165F,-19.35783F,-18.8256435F,
-16.1814404F,-12.2718477F,-7.8657093F,-2.41384578F,
4.94840908F,12.2123642F,15.4736147F,14.1176491F,
11.5966282F,10.0262737F,7.74037838F,3.23115683F,
-2.67719126F,-9.79800415F,-18.8193836F,-26.301815F,
-24.3043938F,-8.93306923F,13.2853851F,30.3004837F,
34.0296364F,24.2935658F,7.17339373F,-8.43206501F,
-15.9494257F,-15.5966272F,-12.3471165F,-9.25716877F,
-5.76831198F,-2.25844717F,-1.16548419F,-2.10539889F,
-0.782804251F,4.68139076F,10.2740793F,11.4020205F,
8.1988678F,3.40999794F,-1.36334658F,-4.91536236F,
-5.41030216F,-2.9320755F,-0.60459125F,-1.02307129F,
-3.53903484F,-5.99503517F,-6.47941065F,-3.03009415F,
4.54348993F,11.6792479F,12.2291031F,6.188591F,
0.206856966F,-1.2108345F,-0.677035213F,-2.08000135F,
-4.26498032F,-3.65425682F,0.104667783F,3.96495128F,
4.54750872F,-0.317904234F,-10.0625477F,-19.4867859F,
-21.3471317F,-12.9661922F,1.5236094F,15.7489719F,
};

// End of File
