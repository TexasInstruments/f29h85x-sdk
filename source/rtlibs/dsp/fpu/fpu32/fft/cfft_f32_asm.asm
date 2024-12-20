;;
 ;	Copyright (C) Texas Instruments Incorporated
 ;
 ;	All rights reserved not granted herein.
 ;	Limited License.

 ;	Texas Instruments Incorporated grants a world-wide, royalty-free,
 ;	non-exclusive license under copyrights and patents it now or hereafter
 ;	owns or controls to make, have made, use, import, offer to sell and sell ("Utilize")
 ;	this software subject to the terms herein.  With respect to the foregoing patent
 ;	license, such license is granted  solely to the extent that any such patent is necessary
 ;	to Utilize the software alone.  The patent license shall not apply to any combinations which
 ;	include this software, other than combinations with devices manufactured by or for TI ("TI Devices").
 ;	No hardware patent is licensed hereunder.

 ;	Redistributions must preserve existing copyright notices and reproduce this license (including the
 ;	above copyright notice and the disclaimer and (if applicable) source code license limitations below)
 ;	in the documentation and/or other materials provided with the distribution

 ;	Redistribution and use in binary form, without modification, are permitted provided that the following
 ;	conditions are met:

 ;	  - No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any
 ;		 software provided in binary form.
 ;	  - Any redistribution and use are licensed by TI for use only with TI Devices.
 ;	  - Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.

 ;	If software source code is provided to you, modification and redistribution of the source code are permitted
 ;	provided that the following conditions are met:
 ;
 ;	  - any redistribution and use of the source code, including any resulting derivative works, are licensed by
 ;		TI for use only with TI Devices.
 ;	  - any redistribution and use of any object code compiled from the source code and any resulting derivative
 ;		works, are licensed by TI for use only with TI Devices.
 ;
 ;	Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or
 ;	promote products derived from this software without specific prior written permission.

 ;	DISCLAIMER.
 ;
 ;	THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 ;	BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 ;	IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 ;	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 ;	OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 ;	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 ;	POSSIBILITY OF SUCH DAMAGE.
;;

	.section   kernel_asm, "ax"
	.global    CFFT_f32_stage_1_2_asm
    .type     CFFT_f32_stage_1_2_asm,@function


;; This function will take two parameters and perform the first two stages of the FFT which involves only 
;; addition and subtraction. The algorithm and pseude code are given below.
;;;; ///;;              +--------------------------------------+
;;;; ///;; InPtr OutPtr | Stages 1 & 2                         |
;;;; ///;;              +-----+--------------------------------+
;;;; ///;;               R(0) | D0'  = (D0 + D2)  + (D4 + D6)  | 
;;;; ///;;               I(0) | D1'  = (D1 + D3)  + (D5 + D7)  | 
;;;; ///;;               R(1) | D2'  = (D0 - D2)  + (D5 - D7)  | 
;;;; ///;;               I(1) | D3'  = (D1 - D3)  - (D4 - D6)  | 
;;;; ///;;               R(2) | D4'  = (D0 + D2)  - (D4 + D6)  | 
;;;; ///;;               I(2) | D5'  = (D1 + D3)  - (D5 + D7)  | 
;;;; ///;;               R(3) | D6'  = (D0 - D2)  - (D5 - D7)  | 
;;;; ///;;               I(3) | D7'  = (D1 - D3)  + (D4 - D6)  | 
;;;; ///;;              +-----+--------------------------------+
;;;; 
;;;; 
;;;;   for (count = 0; count < stage_1_2_iterations; count++ ) {
;;;;      M_reg[0] = v[(count*4) + 0].Re;
;;;;      M_reg[1] = v[(count*4) + 0].Im;
;;;;      M_reg[2] = v[(count*4) + 1].Re;
;;;;      M_reg[7] = v[(count*4) + 3].Im;
;;;;      M_reg[3] = v[(count*4) + 1].Im;
;;;;      M_reg[4] = v[(count*4) + 2].Re;
;;;;      M_reg[5] = v[(count*4) + 2].Im;
;;;;      M_reg[6] = v[(count*4) + 3].Re;
;;;;      
;;;;      M_reg[8+0] = (M_reg[0] + M_reg[2])  + (M_reg[4] + M_reg[6]);
;;;;      M_reg[8+1] = (M_reg[1] + M_reg[3])  + (M_reg[5] + M_reg[7]);
;;;;      M_reg[8+2] = (M_reg[0] - M_reg[2])  + (M_reg[5] - M_reg[7]);
;;;;      M_reg[8+3] = (M_reg[1] - M_reg[3])  - (M_reg[4] - M_reg[6]);
;;;;      M_reg[8+4] = (M_reg[0] + M_reg[2])  - (M_reg[4] + M_reg[6]);
;;;;      M_reg[8+5] = (M_reg[1] + M_reg[3])  - (M_reg[5] + M_reg[7]);
;;;;      M_reg[8+6] = (M_reg[0] - M_reg[2])  - (M_reg[5] - M_reg[7]);
;;;;      M_reg[8+7] = (M_reg[1] - M_reg[3])  + (M_reg[4] - M_reg[6]);
;;;;      
;;;;      v[(count*4) + 0].Re = M_reg[8+0] ;
;;;;      v[(count*4) + 0].Im = M_reg[8+1] ;
;;;;      v[(count*4) + 1].Re = M_reg[8+2] ;
;;;;      v[(count*4) + 1].Im = M_reg[8+3] ;
;;;;      v[(count*4) + 2].Re = M_reg[8+4] ;
;;;;      v[(count*4) + 2].Im = M_reg[8+5] ;
;;;;      v[(count*4) + 3].Re = M_reg[8+6] ;
;;;;      v[(count*4) + 3].Im = M_reg[8+7] ;
;;;;    }
;;;; 

;; void  Argo_fft_stage_1_2_asm(complex_T *v, int buf_size, int swap_buffer_address);
;;   A4 *v       : pointer to complex array.
;;   D0 buf_size : integer buf_size
;;   D1 swap_buffer_address
;;   Note: We are not using any callee save registers
CFFT_f32_stage_1_2_asm:
                ADD.U16 A15, #0x28
                ST.64 *(A15- #0x8), XM26                
                ST.64 *(A15- #0x10), XM28                
                ST.64 *(A15- #0x18), XM30                
                MV.U16 A1, #0 ; This will be the loop counter.
                ;MV A5, A4 ; Keep a copy of pointer to V in A5.
		MV A5, D1
                MV A0, D0 ; Move the count to A0
                LSR A0, A0, #2;  A0 = A0/4 (A0>>2);
loop_start:
;;;;      ; M_reg[0] = v[(count*4) + 0].Re;
;;;;      ; M_reg[1] = v[(count*4) + 0].Im;
;;;;      ; M_reg[2] = v[(count*4) + 1].Re;
;;;;      ; M_reg[3] = v[(count*4) + 2].Im;
;;;;      ; M_reg[4] = v[(count*4) + 3].Re;
;;;;      ; M_reg[5] = v[(count*4) + 3].Im;
;;;;      ; M_reg[6] = v[(count*4) + 4].Re;
;;;;      ; M_reg[7] = v[(count*4) + 4].Im;
                                 
;;;;      M_reg[8+0] = (M_reg[0] + M_reg[2])M24  + (M_reg[4] + M_reg[6])M16;
;;;;      M_reg[8+1] = (M_reg[1] + M_reg[3])M25  + (M_reg[5] + M_reg[7])M17;
;;;;      M_reg[8+2] = (M_reg[0] - M_reg[2])M26  + (M_reg[5] - M_reg[7])M18;
;;;;      M_reg[8+3] = (M_reg[1] - M_reg[3])M27  - (M_reg[4] - M_reg[6])M19;
;;;;      M_reg[8+4] = (M_reg[0] + M_reg[2])M24  - (M_reg[4] + M_reg[6])M16;
;;;;      M_reg[8+5] = (M_reg[1] + M_reg[3])M25  - (M_reg[5] + M_reg[7])M17;
;;;;      M_reg[8+6] = (M_reg[0] - M_reg[2])M26  - (M_reg[5] - M_reg[7])M18;
;;;;      M_reg[8+7] = (M_reg[1] - M_reg[3])M27  + (M_reg[4] - M_reg[6])M19;
LD.64 XM0, *(A4++)
LD.64 XM2, *(A4++)
LD.64 XM4, *(A4++)
SADDF M0, M0, M2
|| SSUBF M2, M0, M2
|| LD.64 XM6, *(A4++)


SADDF M4, M4, M6
|| SSUBF M6, M4, M6
                        ||LD.64 XM16, *(A4++)                                        

SADDF M5, M5, M7
||SSUBF M7, M5, M7
||ADDF M31, M1, M3     ;; M31 is  temp scratch register which can get over-written
                        ||LD.64 XM18, *(A4++)    
SSUBF M3, M1, M3
|| ADDF M8, M0, M4
                        ||LD.64 XM20, *(A4++)  


SUBF M12, M0, M4
|| ADDF M10, M2, M7
|| ADDF M9, M31, M5
                        ||LD.64 XM22, *(A4++)    

ADDF M15, M3, M6
|| SUBF M13, M31, M5
|| SUBF M11, M3, M6
|| INC A1

;;; Next iteration starts here
SUBF M14, M2, M7
|| SADDF M16, M16, M18
|| SSUBF M18, M16, M18
       || ST.64 *A5++, XM8

SADDF M20, M20, M22
|| SSUBF M22, M20, M22
        || ST.64 *A5++, XM10

SADDF M21, M21, M23
||SSUBF M23, M21, M23
|| ADDF M1, M17, M19           ;; M1 is a scratch register and can be overwritten
        || ST.64 *A5++, XM12

SSUBF M19, M17, M19
|| ADDF M24, M16, M20
        || ST.64 *A5++, XM14    

SUBF M28, M16, M20
|| ADDF M26, M18, M23
|| ADDF M25, M1, M21
|| INC A1

ADDF M31, M19, M22
|| SUBF M29, M1, M21
|| SUBF M27, M19, M22

BCMPD @loop_start, A.NEQ, A1, A0
       || ST.64 *A5++, XM24
       || SUBF M30, M18, M23
          ST.64 *A5++, XM26
          ST.64 *A5++, XM28
          ST.64 *A5++, XM30    

          
                LD.64 XM26, *(A15- #0x8)         
             ||	RETD	*(A15-#0x30)
                LD.64 XM28, *(A15- #0x10)         
                LD.64 XM30, *(A15- #0x18)         
                SUB.U16	A15,#0x30
        
; end stage1_2        
        

    .section   kernel_asm, "ax"           
	.global    CFFT_f32_stages_3_asm_opt
	.type      CFFT_f32_stages_3_asm_opt,@function
            
CFFT_f32_stages_3_asm_opt:
                ADD.U16 A15, #0x50
                ST.64 *(A15- #0x10), XA10
                ST.64 *(A15- #0x18), XA12
                ST.32 *(A15- #0x20), A14
                ST.64 *(A15- #0x38), XM26                
                ST.64 *(A15- #0x40), XM28                
                ST.64 *(A15- #0x48), XM30                
                
                MV A9,D1                       ; D1 is swap buffer - INPUT to stg 3 (since it was the OUTPUT of Stg 1,2)
                MV D3, A4                      ; Save A4 in D3.
                MV D4, A5                      ; Save A5 in D4.
                MV A11, D0                    ; D0 is bufsize
                                
                 MV  A2, #8                     ;;;;;    (A2)NumberOfSamplesInGroup = 16;
               || LSR A11, A11, #3               ;;;;;    (A11)NumberOfGroups = buf_size/8;

                 LSL A1, A11,#3                     ;;;;;    (A1)t_increment = NumberOfGroups; Scale it by 3 for 64-bit index
               ;|| SUB.U16 A9, #4  ;;; A9 = num_stages - 4;
                                                ;;;;;    // Stage-4 calculation loop

               LSR A12, A2, #1                  ;;;;;    (A12)HalfOfSamplesInGroup = (A2)NumberOfSamplesInGroup>>1;
 
               MV A6, A4                       ;; A4 is where the OUTPUT will go for Stg3
               ||MV A10, #0

 .align 16
              loop_lev_1_opti_f2_stage3 :                                                 ;;;;;      // Perform the Butterfly calculation on each group
                                              ;;;;;     (A10) for (GroupIndex=0; GroupIndex < NumberOfGroups; GroupIndex++) {
                 ;;;;  SUB.U16 A14, A12, #4
                 ;;;;  MV A14, A12
                 ;;;   MPY A3, A2,A10            ;;;;;      
                    MV A5, D4
                 || ADD A7, A9, A12,#3         ;;A7 = (A9 + A12<<#3)

                    SUB.U16 A0, A12, #1 ;; Decrement by 1 since first store would have advanced the A6 pointer.
                 ;;;;|| LSR A14, A14, #2
                 ;;;;DEC A14                    
                 ;|| MV A6, A9			;; A6 will be the Ra store pointer. A6[A0] will be the Rb store pointer
                
                ;; This is the inner most loop which will be SW pipelined. 


LD.64    XM0, *(A5++A1)
||LD.64   XM2, *(A7++)

LD.64    XM4, *(A9++)
||SMPYF    M6,  M2, M0
||SMPYF    M7,  M3, M1


SMPYF    M1,  M2, M1
||SMPYF    M0,  M3, M0
||LD.64    XM8, *(A5++A1)
||LD.64   XM10, *(A7++)

SADDF    M6,  M6, M7
||LD.64    XM12, *(A9++)
||SMPYF    M14,  M10, M8
||SMPYF    M15,  M11, M9


SSUBF    M7,  M0, M1
||SMPYF    M9,  M10, M9
||SMPYF    M8,  M11, M8
||LD.64    XM16, *(A5++A1)
||LD.64   XM18, *(A7++)

SSUBF    M4,  M4, M6
||SADDF    M0,  M4, M6
||SADDF    M14,  M14, M15
||LD.64    XM20, *(A9++)
||SMPYF    M22,  M18, M16
||SMPYF    M23,  M19, M17


SSUBF    M5,  M5, M7
||SADDF    M1,  M5, M7
||SSUBF    M15,  M8, M9
||SMPYF    M17,  M18, M17
||SMPYF    M16,  M19, M16
 ||LD.64    XM24, *(A5++A1)
||LD.64   XM26, *(A7++)

NOP #1
||SSUBF    M12,  M12, M14
||SADDF    M8,  M12, M14
||SADDF    M22,  M22, M23
 ||LD.64    XM28, *(A9++)
||SMPYF    M30,  M26, M24
||SMPYF    M31,  M27, M25


ST.64    *(A6++), XM0
||SSUBF    M13,  M13, M15
||SADDF    M9,  M13, M15
||SSUBF    M23,  M16, M17
 ||SMPYF    M25,  M26, M25
||SMPYF    M24,  M27, M24


ST.64    *(A6 + A0<<#3), XM4
||NOP #1
||SSUBF    M20,  M20, M22
||SADDF    M16,  M20, M22
 ||SADDF    M30,  M30, M31


ST.64    *(A6++), XM8
||SSUBF    M21,  M21, M23
||SADDF    M17,  M21, M23
 ||SSUBF    M31,  M24, M25


ST.64    *(A6 + A0<<#3), XM12
 ||SSUBF    M28,  M28, M30
||SADDF    M24,  M28, M30
||                INC A10


ST.64    *(A6++), XM16
|| BCMPD @loop_lev_1_opti_f2_stage3, A.NEQ, A10, A11    
||SSUBF    M29,  M29, M31
||SADDF    M25,  M29, M31


ST.64    *(A6 + A0<<#3), XM20
|| ADD A9, A9, A12,#3	; Increment Ra pointer by HalfSamplesinGroup (for INPUT)


ST.64    *(A6++), XM24
|| ADD A7, A7, A12,#3	; Increment Ra pointer by HalfSamplesinGroup


ST.64    *(A6 + A0<<#3), XM28
|| ADD A6, A6, A12,#3	; Increment Ra pointer by HalfSamplesinGroup (for OUTPUT)

                LSR A1, A1, #1                  ;;;;;  t_increment = NumberOfGroups>>1;
                LSR A11, A11, #1                ;;;;;  NumberOfGroups>>=1;
                LSL A2, A2, #1                  ;;;;;  NumberOfSamplesInGroup<<=1;
                
                LD.64 XM26, *(A15- #0x38)         
                LD.64 XM28, *(A15- #0x40)         
                LD.64 XM30, *(A15- #0x48)         
                LD.64 XA10, *(A15- #0x10)
                LD.64 XA12, *(A15- #0x18)
                LD.32 A14, *(A15- #0x20)
                SUB.U16	A15,#0x50
                RET


; end stage3

                
	.section   kernel_asm, "ax"               
	.global    CFFT_f32_stages_4_asm_opt
    .type     CFFT_f32_stages_4_asm_opt,@function
        
;; void Argo_fft_stages_4plus_asm_opti( complex_T *v, complex_T *twiddle, int buf_size, int num_stages, int table_size_factor );

;;   A4 *v       : pointer to complex array.
;;   A5 *twiddle : pointer to twiddle factor array
;;   D0 buf_size : integer buf_size
;;   D1 num_stages : Number of FFT stages
;;   D2 table_size_factor : This is used to decide jump in twiddle factor tables when generated for a bigger size and used for a smaller FFT.
;;                        
;;;;;  ----------------------- C algorithm to be implemented.
;;;;;   complex_T tmp;
;;;;;   int DFTStage = 0;
;;;;;   int SampleIndex;
;;;;;   int GroupIndex;
;;;;;   int NumberOfSamplesInGroup;
;;;;;   int NumberOfGroups;
;;;;;   int CombinedIndex;
;;;;;   int HalfOfSamplesInGroup;
;;;;;   int t_index = 0, t_increment = 0;
;;;;;  
;;;;;    NumberOfSamplesInGroup = 16;
;;;;;    NumberOfGroups = buf_size/16;
;;;;;    t_increment = NumberOfGroups;
;;;;;    
;;;;;    // Main FFT calculation loop
;;;;;    for (DFTStage=3; DFTStage < num_stages; DFTStage++) {
;;;;;     
;;;;; //   NumberOfSamplesInGroup = (1<<(DFTStage+1)); 
;;;;; //   NumberOfGroups = buf_size/ NumberOfSamplesInGroup;
;;;;; // Orig   HalfOfSamplesInGroup = NumberOfSamplesInGroup / 2;
;;;;;    HalfOfSamplesInGroup = NumberOfSamplesInGroup>>1;
;;;;;  
;;;;;      // Perform the Butterfly calculation on each group
;;;;;      for (GroupIndex=0; GroupIndex < NumberOfGroups; GroupIndex++) {
;;;;;              t_index = 0;
;;;;;         for (SampleIndex=0; SampleIndex < HalfOfSamplesInGroup; SampleIndex++){
;;;;;                 CombinedIndex = NumberOfSamplesInGroup * GroupIndex + SampleIndex;
;;;;;                 //printf("Butterfly %2d : %d %d\n", t_index, CombinedIndex, (CombinedIndex + HalfOfSamplesInGroup)) ;
;;;;;  
;;;;;                 // v[k+n] * Wk : Complex multiplt                
;;;;;                 tmp.Re = ( (v[CombinedIndex + HalfOfSamplesInGroup].Re * twiddle[t_index<<table_size_factor].Re) - (v[CombinedIndex + HalfOfSamplesInGroup].Im * twiddle[t_index<<table_size_factor].Im) );
;;;;;                 tmp.Im = ( (v[CombinedIndex + HalfOfSamplesInGroup].Re * twiddle[t_index<<table_size_factor].Im) + (v[CombinedIndex + HalfOfSamplesInGroup].Im * twiddle[t_index<<table_size_factor].Re) );
;;;;; 
;;;;;                 // The Butterfly operation.
;;;;;                 v[CombinedIndex + HalfOfSamplesInGroup].Re = v[CombinedIndex].Re - tmp.Re;
;;;;;                 v[CombinedIndex + HalfOfSamplesInGroup].Im = v[CombinedIndex].Im - tmp.Im;
;;;;; 
;;;;;                 v[CombinedIndex].Re = v[CombinedIndex].Re + tmp.Re;
;;;;;                 v[CombinedIndex].Im = v[CombinedIndex].Im + tmp.Im;
;;;;; //                printf("T_INDEX = %d\n", t_index);
;;;;;                 t_index = (t_index + t_increment) ;
;;;;;         }
;;;;;      }
;;;;; //Orig                t_increment = NumberOfGroups/2;
;;;;;                 t_increment = NumberOfGroups>>1;
;;;;;                 NumberOfSamplesInGroup<<=1;
;;;;;                 NumberOfGroups>>=1;
;;;;;   }
;;;;; 
;;; The assumption is that you are using twiddle factors generated for this specific sized FFT.
;;;; If the twiddle factors are of a different size, then A1 which is used as the index has to be scaled appropriately

CFFT_f32_stages_4_asm_opt:
                ADD.U16 A15, #0x50
                ST.64 *(A15- #0x10), XA10
                ST.64 *(A15- #0x18), XA12
                ST.32 *(A15- #0x20), A14
                ST.64 *(A15- #0x38), XM26                
                ST.64 *(A15- #0x40), XM28                
                ST.64 *(A15- #0x48), XM30                
                
                MV A9,D1                       ; D1 is swap buffer - OUTPUT of stg 4
                MV D3, A4                      ; Save A4 in D3.
                MV D4, A5                      ; Save A5 in D4.
                MV A11, D0                    ; D0 is bufsize
                                
                 MV  A2, #16                     ;;;;;    (A2)NumberOfSamplesInGroup = 16;
               || LSR A11, A11, #4               ;;;;;    (A11)NumberOfGroups = buf_size/16;

                 LSL A1, A11,#3                     ;;;;;    (A1)t_increment = NumberOfGroups; Scale it by 3 for 64-bit index
               ;|| SUB.U16 A9, #4  ;;; A9 = num_stages - 4;
                                                ;;;;;    // Stage-4 calculation loop

               LSR A12, A2, #1                  ;;;;;    (A12)HalfOfSamplesInGroup = (A2)NumberOfSamplesInGroup>>1;
 
               MV A6, A9                       ;; Restore A4 in the outer loop since it gets consumed inside the inner loop.
              ||MV A10, #0
 .align 16
             loop_lev_1_opti_f2 :                                                 ;;;;;      // Perform the Butterfly calculation on each group
                                              ;;;;;     (A10) for (GroupIndex=0; GroupIndex < NumberOfGroups; GroupIndex++) {
                ;;;   SUB.U16 A14, A12, #4
                 ;;;;  MV A14, A12
                 ;;;   MPY A3, A2,A10            ;;;;;      
                    MV A5, D4
                 || ADD A7, A4, A12,#3         ;;A7 = (A4 + A12<<#3)

                    SUB.U16 A0, A12, #1 ;; Decrement by 1 since first store would have advanced the A6 pointer.
                 ;;;;;|| LSR A14, A14, #2
                 ;;;;;   DEC A14                    
                 ;|| MV A6, A4			;; A6 will be the Ra store pointer. A6[A0] will be the Rb store pointer
                
                ;; This is the inner most loop which will be SW pipelined. 


         loop_lev_2_opti_f2 :                            
LD.64    XM0, *(A5++A1)
||LD.64   XM2, *(A7++)

LD.64    XM4, *(A4++)
||SMPYF    M6,  M2, M0
||SMPYF    M7,  M3, M1


SMPYF    M1,  M2, M1
||SMPYF    M0,  M3, M0
||LD.64    XM8, *(A5++A1)
||LD.64   XM10, *(A7++)

SADDF    M6,  M6, M7
||LD.64    XM12, *(A4++)
||SMPYF    M14,  M10, M8
||SMPYF    M15,  M11, M9


SSUBF    M7,  M0, M1
||SMPYF    M9,  M10, M9
||SMPYF    M8,  M11, M8
||LD.64    XM16, *(A5++A1)
||LD.64   XM18, *(A7++)

SSUBF    M4,  M4, M6
||SADDF    M0,  M4, M6
||SADDF    M14,  M14, M15
||LD.64    XM20, *(A4++)
||SMPYF    M22,  M18, M16
||SMPYF    M23,  M19, M17


SSUBF    M5,  M5, M7
||SADDF    M1,  M5, M7
||SSUBF    M15,  M8, M9
||SMPYF    M17,  M18, M17
||SMPYF    M16,  M19, M16
 ||LD.64    XM24, *(A5++A1)
||LD.64   XM26, *(A7++)

NOP #1
||SSUBF    M12,  M12, M14
||SADDF    M8,  M12, M14
||SADDF    M22,  M22, M23
 ||LD.64    XM28, *(A4++)
||SMPYF    M30,  M26, M24
||SMPYF    M31,  M27, M25


##### Kernel Starts here !!

cfft_sw_pipe_kernel: // In Stage-4 , 8 butterflies are executed and no loop involved.
ST.64    *(A6++), XM0
||SSUBF    M13,  M13, M15
||SADDF    M9,  M13, M15
||SSUBF    M23,  M16, M17
 ||SMPYF    M25,  M26, M25
||SMPYF    M24,  M27, M24
||LD.64    XM0, *(A5++A1)
||LD.64   XM2, *(A7++)

ST.64    *(A6 + A0<<#3), XM4
||SSUBF    M20,  M20, M22
||SADDF    M16,  M20, M22
 ||SADDF    M30,  M30, M31
||LD.64    XM4, *(A4++)
||SMPYF    M6,  M2, M0
||SMPYF    M7,  M3, M1


ST.64    *(A6++), XM8
||SSUBF    M21,  M21, M23
||SADDF    M17,  M21, M23
||SSUBF    M31,  M24, M25
||SMPYF    M1,  M2, M1
||SMPYF    M0,  M3, M0
||LD.64    XM8, *(A5++A1)
||LD.64   XM10, *(A7++)

ST.64    *(A6 + A0<<#3), XM12
||SSUBF    M28,  M28, M30
||SADDF    M24,  M28, M30
||SADDF    M6,  M6, M7
||LD.64    XM12, *(A4++)
||SMPYF    M14,  M10, M8
||SMPYF    M15,  M11, M9


ST.64    *(A6++), XM16
||SSUBF    M29,  M29, M31
||SADDF    M25,  M29, M31
||SSUBF    M7,  M0, M1
||SMPYF    M9,  M10, M9
||SMPYF    M8,  M11, M8
||LD.64    XM16, *(A5++A1)
||LD.64   XM18, *(A7++)

ST.64    *(A6 + A0<<#3), XM20
||SSUBF    M4,  M4, M6
||SADDF    M0,  M4, M6
||SADDF    M14,  M14, M15
||LD.64    XM20, *(A4++)
||SMPYF    M22,  M18, M16
||SMPYF    M23,  M19, M17


ST.64    *(A6++), XM24
||SSUBF    M5,  M5, M7
||SADDF    M1,  M5, M7
||SSUBF    M15,  M8, M9
||SMPYF    M17,  M18, M17
||SMPYF    M16,  M19, M16
||LD.64    XM24, *(A5++A1)
||LD.64   XM26, *(A7++)

ST.64    *(A6 + A0<<#3), XM28
||SSUBF    M12,  M12, M14
||SADDF    M8,  M12, M14
||SADDF    M22,  M22, M23
||LD.64    XM28, *(A4++)
||SMPYF    M30,  M26, M24
||SMPYF    M31,  M27, M25


######## Kernel Ends here !!

ST.64    *(A6++), XM0
||SSUBF    M13,  M13, M15
||SADDF    M9,  M13, M15
||SSUBF    M23,  M16, M17
||SMPYF    M25,  M26, M25
||SMPYF    M24,  M27, M24


ST.64    *(A6 + A0<<#3), XM4
||SSUBF    M20,  M20, M22
||SADDF    M16,  M20, M22
||SADDF    M30,  M30, M31


ST.64    *(A6++), XM8
||SSUBF    M21,  M21, M23
||SADDF    M17,  M21, M23
||SSUBF    M31,  M24, M25


ST.64    *(A6 + A0<<#3), XM12
||SSUBF    M28,  M28, M30
||SADDF    M24,  M28, M30
||INC A10


ST.64    *(A6++), XM16
|| BCMPD @loop_lev_1_opti_f2, A.NEQ, A10, A11    
||SSUBF    M29,  M29, M31
||SADDF    M25,  M29, M31


ST.64    *(A6 + A0<<#3), XM20
|| ADD A4, A4, A12,#3	; Increment Ra pointer by HalfSamplesinGroup

ST.64    *(A6++), XM24
|| ADD A7, A7, A12,#3	; Increment Ra pointer by HalfSamplesinGroup


ST.64    *(A6 + A0<<#3), XM28
|| ADD A6, A6, A12,#3	; Increment Ra pointer by HalfSamplesinGroup
                                                ;;;;;   }
                ;;; DECBD A9, #1, @top_loop_opti_f2
                LSR A1, A1, #1                  ;;;;;  t_increment = NumberOfGroups>>1;
                LSR A11, A11, #1                ;;;;;  NumberOfGroups>>=1;
                LSL A2, A2, #1                  ;;;;;  NumberOfSamplesInGroup<<=1;
                
                LD.64 XM26, *(A15- #0x38)         
                LD.64 XM28, *(A15- #0x40)         
                LD.64 XM30, *(A15- #0x48)         
                LD.64 XA10, *(A15- #0x10)
                LD.64 XA12, *(A15- #0x18)
                LD.32 A14, *(A15- #0x20)
                SUB.U16	A15,#0x50
                RET
                
; end stage4                
                
    .section   kernel_asm, "ax"      
	.global    CFFT_f32_stages_5plus_asm_opt
    .type     CFFT_f32_stages_5plus_asm_opt,@function
        
;; void Argo_fft_stages_5plus_asm_opti( complex_T *v, complex_T *twiddle, int buf_size, int num_stages, int table_size_factor );

;;   A4 *v       : pointer to complex array.
;;   A5 *twiddle : pointer to twiddle factor array
;;   D0 buf_size : integer buf_size
;;   D1 num_stages : Number of FFT stages
;;   D2 table_size_factor : This is used to decide jump in twiddle factor tables when generated for a bigger size and used for a smaller FFT.
;;                        
;;;;;  ----------------------- C algorithm to be implemented.
;;;;;   complex_T tmp;
;;;;;   int DFTStage = 0;
;;;;;   int SampleIndex;
;;;;;   int GroupIndex;
;;;;;   int NumberOfSamplesInGroup;
;;;;;   int NumberOfGroups;
;;;;;   int CombinedIndex;
;;;;;   int HalfOfSamplesInGroup;
;;;;;   int t_index = 0, t_increment = 0;
;;;;;  
;;;;;    NumberOfSamplesInGroup = 32;
;;;;;    NumberOfGroups = buf_size/32;
;;;;;    t_increment = NumberOfGroups;
;;;;;    
;;;;;    // Main FFT calculation loop
;;;;;    for (DFTStage=4; DFTStage < num_stages; DFTStage++) {
;;;;;     
;;;;; //   NumberOfSamplesInGroup = (1<<(DFTStage+1)); 
;;;;; //   NumberOfGroups = buf_size/ NumberOfSamplesInGroup;
;;;;; // Orig   HalfOfSamplesInGroup = NumberOfSamplesInGroup / 2;
;;;;;    HalfOfSamplesInGroup = NumberOfSamplesInGroup>>1;
;;;;;  
;;;;;      // Perform the Butterfly calculation on each group
;;;;;      for (GroupIndex=0; GroupIndex < NumberOfGroups; GroupIndex++) {
;;;;;              t_index = 0;
;;;;;         for (SampleIndex=0; SampleIndex < HalfOfSamplesInGroup; SampleIndex++){
;;;;;                 CombinedIndex = NumberOfSamplesInGroup * GroupIndex + SampleIndex;
;;;;;                 //printf("Butterfly %2d : %d %d\n", t_index, CombinedIndex, (CombinedIndex + HalfOfSamplesInGroup)) ;
;;;;;  
;;;;;                 // v[k+n] * Wk : Complex multiplt                
;;;;;                 tmp.Re = ( (v[CombinedIndex + HalfOfSamplesInGroup].Re * twiddle[t_index<<table_size_factor].Re) - (v[CombinedIndex + HalfOfSamplesInGroup].Im * twiddle[t_index<<table_size_factor].Im) );
;;;;;                 tmp.Im = ( (v[CombinedIndex + HalfOfSamplesInGroup].Re * twiddle[t_index<<table_size_factor].Im) + (v[CombinedIndex + HalfOfSamplesInGroup].Im * twiddle[t_index<<table_size_factor].Re) );
;;;;; 
;;;;;                 // The Butterfly operation.
;;;;;                 v[CombinedIndex + HalfOfSamplesInGroup].Re = v[CombinedIndex].Re - tmp.Re;
;;;;;                 v[CombinedIndex + HalfOfSamplesInGroup].Im = v[CombinedIndex].Im - tmp.Im;
;;;;; 
;;;;;                 v[CombinedIndex].Re = v[CombinedIndex].Re + tmp.Re;
;;;;;                 v[CombinedIndex].Im = v[CombinedIndex].Im + tmp.Im;
;;;;; //                printf("T_INDEX = %d\n", t_index);
;;;;;                 t_index = (t_index + t_increment) ;
;;;;;         }
;;;;;      }
;;;;; //Orig                t_increment = NumberOfGroups/2;
;;;;;                 t_increment = NumberOfGroups>>1;
;;;;;                 NumberOfSamplesInGroup<<=1;
;;;;;                 NumberOfGroups>>=1;
;;;;;   }
;;;;; 
;;; The assumption is that you are using twiddle factors generated for this specific sized FFT.
;;;; If the twiddle factors are of a different size, then A1 which is used as the index has to be scaled appropriately

CFFT_f32_stages_5plus_asm_opt:
                ADD.U16 A15, #0x50
                ST.64 *(A15- #0x10), XA10
                ST.64 *(A15- #0x18), XA12
                ST.32 *(A15- #0x20), A14
                ST.64 *(A15- #0x38), XM26                
                ST.64 *(A15- #0x40), XM28                
                ST.64 *(A15- #0x48), XM30                
                
                MV A9,D1                       ; A9 is num_stages
                MV D3, A4                      ; Save A4 in D3.
                MV D4, A5                      ; Save A5 in D4.
                MV A11, D0                    ; D0 is bufsize
                MV A8, D2                       ;; D2 is the value of the swap buffer address
                                
                 MV  A2, #32                     ;;;;;    (A2)NumberOfSamplesInGroup = 32;
               || LSR A11, A11, #5               ;;;;;    (A11)NumberOfGroups = buf_size/32;

                 LSL A1, A11,#3                     ;;;;;    (A1)t_increment = NumberOfGroups; Scale it by 3 for 64-bit index
               || SUB.U16 A9, #5  ;;; A9 = num_stages - 5;
               || MV A13, #1        ;;; We will use A13 as a ping-pong flag register. (Initialize to 1 since INPUT is in buf swap)

                 ;;;;;    // Stage-5+ calculation loop
                 ;;; Temporarily chosen a swap buffer location of 0x12000
                 ;;; Use this to ensure loads and stores of data are always to different memory blocks to avoid stalls.
top_loop_opti_f3:
               LSR A12, A2, #1                  ;;;;;    (A12)HalfOfSamplesInGroup = (A2)NumberOfSamplesInGroup>>1;
              ||MV A10, #0
              ||CMP.U16 A13, #0
                                ;; Restore A4 in the outer loop since it gets consumed inside the inner loop. 
                XC #1, A.EQ
               ||MV A4, D3                    
               ||MV A6, A8
              
                XC #1, A.NEQ
               ||MV A4, A8                                   
               ||MV A6, D3; 
               
                SUB A6, A6, A12,#3	; This is to offset the first addition inside the loop which should not happen when entering the loop.
                XOR.U16 A13, #0x1 ;; Flip the LSB of A13. This is to create the ping-pong flag
              
             loop_lev_1_opti_f3 :                                                 ;;;;;      // Perform the Butterfly calculation on each group
                                              ;;;;;     (A10) for (GroupIndex=0; GroupIndex < NumberOfGroups; GroupIndex++) {
                   SUB.U16 A14, A12, #8
                 ;;;;  MV A14, A12
                    MPY A3, A2,A10            ;;;;;      
                 || MV A5, D4
                 || ADD A7, A4, A12,#3         ;;A7 = (A4 + A12<<#3)

                    MV  A0, A12   
                 || LSR A14, A14, #2
                 
                    DEC A14                    
;;                 || MV A6, A4			;; A6 will be the Ra store pointer. A6[A0] will be the Rb store pointer
                    ADD A6, A6, A12,#3	; Increment Ra pointer by HalfSamplesinGroup

                ;; This is the inner most loop which will be SW pipelined. 


         loop_lev_2_opti_f3 :      
         
LD.64    XM0, *(A5++A1)
||LD.64   XM2, *(A7++)

SMPYF    M6,  M2, M0
||SMPYF    M7,  M3, M1


SMPYF    M1,  M2, M1
||SMPYF    M0,  M3, M0
||LD.64    XM8, *(A5++A1)
||LD.64   XM10, *(A7++)

SMPYF    M14,  M10, M8
||SMPYF    M15,  M11, M9


SADDF    M6,  M6, M7
||SMPYF    M9,  M10, M9
||SMPYF    M8,  M11, M8
||LD.64    XM16, *(A5++A1)
||LD.64   XM18, *(A7++)

LD.64    XM4, *(A4++)
||SSUBF    M7,  M0, M1
||SMPYF    M22,  M18, M16
||SMPYF    M23,  M19, M17


SSUBF    M6,  M4, M6
||SADDF    M4,  M4, M6
||SADDF    M14,  M14, M15
||SMPYF    M17,  M18, M17
||SMPYF    M16,  M19, M16
||LD.64    XM24, *(A5++A1)
||LD.64   XM26, *(A7++)

SSUBF    M7,  M5, M7
||SADDF    M5,  M5, M7
||LD.64    XM12, *(A4++)
||SSUBF    M15,  M8, M9
||SMPYF    M30,  M26, M24
||SMPYF    M31,  M27, M25


SSUBF    M14,  M12, M14
||SADDF    M12,  M12, M14
||SADDF    M22,  M22, M23
||SMPYF    M25,  M26, M25
||SMPYF    M24,  M27, M24
||LD.64    XM0, *(A5++A1)
||LD.64   XM2, *(A7++)

ST.64    *(A6 + A0<<#3), XM6
||SSUBF    M15,  M13, M15
||SADDF    M13,  M13, M15
||LD.64    XM20, *(A4++)
||SSUBF    M23,  M16, M17
||SMPYF    M6,  M2, M0
||SMPYF    M7,  M3, M1


ST.64    *(A6++), XM4
||SSUBF    M22,  M20, M22
||SADDF    M20,  M20, M22
||SADDF    M30,  M30, M31
||SMPYF    M1,  M2, M1
||SMPYF    M0,  M3, M0
||LD.64    XM8, *(A5++A1)
||LD.64   XM10, *(A7++)

ST.64    *(A6 + A0<<#3), XM14
||SSUBF    M23,  M21, M23
||SADDF    M21,  M21, M23
||LD.64    XM28, *(A4++)
||SSUBF    M31,  M24, M25
||SMPYF    M14,  M10, M8
||SMPYF    M15,  M11, M9


ST.64    *(A6++), XM12
||SSUBF    M30,  M28, M30
||SADDF    M28,  M28, M30
||SADDF    M6,  M6, M7
||SMPYF    M9,  M10, M9
||SMPYF    M8,  M11, M8
||LD.64    XM16, *(A5++A1)
||LD.64   XM18, *(A7++)

ST.64    *(A6 + A0<<#3), XM22
 ||SSUBF    M31,  M29, M31
||SADDF    M29,  M29, M31
||LD.64    XM4, *(A4++)
||SSUBF    M7,  M0, M1
||SMPYF    M22,  M18, M16
||SMPYF    M23,  M19, M17


ST.64    *(A6++), XM20
||SSUBF    M6,  M4, M6
||SADDF    M4,  M4, M6
||SADDF    M14,  M14, M15
||SMPYF    M17,  M18, M17
||SMPYF    M16,  M19, M16
||LD.64    XM24, *(A5++A1)
||LD.64   XM26, *(A7++)



 ;;;;;;########### Prolog ends and Kernel starts here############
;; Align this to a 128-bit boundary to get best loop performance
 .align 16
sw_pipe_kernel_f3 :
ST.64    *(A6 + A0<<#3), XM30
||SSUBF    M7,  M5, M7
||SADDF    M5,  M5, M7
||LD.64    XM12, *(A4++)
||SSUBF    M15,  M8, M9
||SMPYF    M30,  M26, M24
||SMPYF    M31,  M27, M25


ST.64    *(A6++), XM28
||SSUBF    M14,  M12, M14
||SADDF    M12,  M12, M14
||SADDF    M22,  M22, M23
||SMPYF    M25,  M26, M25
||SMPYF    M24,  M27, M24
||LD.64    XM0, *(A5++A1)
||LD.64   XM2, *(A7++)

ST.64    *(A6 + A0<<#3), XM6
||SSUBF    M15,  M13, M15
||SADDF    M13,  M13, M15
||LD.64    XM20, *(A4++)
||SSUBF    M23,  M16, M17
||SMPYF    M6,  M2, M0
||SMPYF    M7,  M3, M1


ST.64    *(A6++), XM4
||SSUBF    M22,  M20, M22
||SADDF    M20,  M20, M22
||SADDF    M30,  M30, M31
||SMPYF    M1,  M2, M1
||SMPYF    M0,  M3, M0
||LD.64    XM8, *(A5++A1)
||LD.64   XM10, *(A7++)


SDECBD A14, #1, @sw_pipe_kernel_f3
|| ST.64    *(A6 + A0<<#3), XM14
||SSUBF    M23,  M21, M23
||SADDF    M21,  M21, M23
||LD.64    XM28, *(A4++)
||SSUBF    M31,  M24, M25
||SMPYF    M14,  M10, M8
||SMPYF    M15,  M11, M9


ST.64    *(A6++), XM12
||SSUBF    M30,  M28, M30
||SADDF    M28,  M28, M30
||SADDF    M6,  M6, M7
||SMPYF    M9,  M10, M9
||SMPYF    M8,  M11, M8
||LD.64    XM16, *(A5++A1)
||LD.64   XM18, *(A7++)

ST.64    *(A6 + A0<<#3), XM22
||SSUBF    M31,  M29, M31
||SADDF    M29,  M29, M31
||LD.64    XM4, *(A4++)
||SSUBF    M7,  M0, M1
||SMPYF    M22,  M18, M16
||SMPYF    M23,  M19, M17


ST.64    *(A6++), XM20
||SSUBF    M6,  M4, M6
||SADDF    M4,  M4, M6
||SADDF    M14,  M14, M15
||SMPYF    M17,  M18, M17
||SMPYF    M16,  M19, M16
||LD.64    XM24, *(A5++A1)
||LD.64   XM26, *(A7++)



 ;;;;;;########### Kernel ends and Epilog starts here############

ST.64    *(A6 + A0<<#3), XM30
||SSUBF    M7,  M5, M7
||SADDF    M5,  M5, M7
||LD.64    XM12, *(A4++)
||SSUBF    M15,  M8, M9
||SMPYF    M30,  M26, M24
||SMPYF    M31,  M27, M25


ST.64    *(A6++), XM28
||SSUBF    M14,  M12, M14
||SADDF    M12,  M12, M14
||SADDF    M22,  M22, M23
||SMPYF    M25,  M26, M25
||SMPYF    M24,  M27, M24


ST.64    *(A6 + A0<<#3), XM6
||SSUBF    M15,  M13, M15
||SADDF    M13,  M13, M15
||LD.64    XM20, *(A4++)
||SSUBF    M23,  M16, M17


ST.64    *(A6++), XM4
||SSUBF    M22,  M20, M22
||SADDF    M20,  M20, M22
||SADDF    M30,  M30, M31


ST.64    *(A6 + A0<<#3), XM14
||SSUBF    M23,  M21, M23
||SADDF    M21,  M21, M23
||LD.64    XM28, *(A4++)
||SSUBF    M31,  M24, M25


ST.64    *(A6++), XM12
||SSUBF    M30,  M28, M30
||SADDF    M28,  M28, M30
||                INC A10


                BCMPD @loop_lev_1_opti_f3, A.NEQ, A10, A11    
                || ST.64    *(A6 + A0<<#3), XM22
                ||SSUBF    M31,  M29, M31
                ||SADDF    M29,  M29, M31

                ;;;;;    }
                ST.64    *(A6++), XM20
		|| ADD A4, A4, A12,#3	; Increment Ra pointer by HalfSamplesinGroup
		ST.64    *(A6 + A0<<#3), XM30
                || ADD A7, A7, A12,#3	; Increment Ra pointer by HalfSamplesinGroup
		ST.64    *A6++, XM28

                                                ;;;;;   }
                DECBD A9, #1, @top_loop_opti_f3
                LSR A1, A1, #1                  ;;;;;  t_increment = NumberOfGroups>>1;
                LSR A11, A11, #1                ;;;;;  NumberOfGroups>>=1;
                LSL A2, A2, #1                  ;;;;;  NumberOfSamplesInGroup<<=1;
                
                LD.64 XM26, *(A15- #0x38)         
                LD.64 XM28, *(A15- #0x40)         
                LD.64 XM30, *(A15- #0x48)         
                LD.64 XA10, *(A15- #0x10)
                LD.64 XA12, *(A15- #0x18)
                LD.32 A14, *(A15- #0x20)
                SUB.U16	A15,#0x50
                RET
                
; end stage5+                

