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
.global    fir_f32_asm
.type      fir_f32_asm,@function

fir_f32_asm:

;;; // circular hist buf so no need for in_with_hist
;;; void fir_f32_asm(uint32_t N, uint32_t M, float32_t *out, float32_t *in, float32_t *filt, float32_t *hist);	
; D0 = N (number of iterations)
; D1 = M (number of taps)
; A4 = *out (single sample)
; A5 = *in (circular buffer)
; A6 = *filt (filt coeffs)
; A7 = *hist (single sample)
    
    ADD.U16 A15,#0x18
    MV A8, A6 ;; Save the A6 pointer. This has to be reloaded to the start of the filter-coefficients on each iteration.
  ||ST.32 *(A15-#0x8), A14

      ;ST.64 *(A15-#0x10), XA12
ST.32 *(A15-#0x10),A12
   || ZERO A0  ;; V2
ST.32 *(A15-#0x18),A13
   || MV A13, D0
        
    DEC A13
    ||MV A12, D0  ; Save D0 (N) in A12. Need to subtract this count later.
    INC A12
           

fir_loop:
    MV  A14,D1      ;A14 = M
  || MV A6,A8   ;; Reset A6 for each iteration of the loop.
  || MV A1,A0   ;; Reset A1 also.
    
    MV.32 *(A7+A0<<#0x2),*A5	    ; Store input sample at hist[circ_buf_index]
    || MV A3, D1   ; A3 = M    
    || SUB.U16 A14, #4 ;; Adjust the count for the extra 4 iterations that will occur due to SDECBD
       DEC A3 ; A3 = M-1 
    
;;;;;;;;;;;;;;;;;;;;;;;   Fix this later. Case of Number of taps less than 4
;;;;;;;;;;;;;;;;;;;;;;;   WARNING !!! For now, this code will not handle case of TAP length less than 4
;;V2   QDECB A14, #3, @Neq0, @Neq1, @Neq2, @
;;V2   || DEC A3      ; A3 = M-1 	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

prologue:
    LD.32 M1, *A5					; A5 - this prevents a stall over using *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
	|| DEC.CIRC A1, A3
	|| ZERO M5

    LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
    	|| SMPYF M3, M2, M1
	|| DEC.CIRC A1, A3
        || ZERO M6
	
	LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
        || SMPYF M4, M2, M1
	|| DEC.CIRC A1, A3	
	|| QDECB A14, #4, @epilogue0, @epilogue1, @epilogue2, @epilogue3, @

        ;;; Align this to a 128-bit boundary to get best performance
 .align 16
kernel: 
    ;1
    LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
        || SMPYF M3, M2, M1
        || SADDF M5, M5, M3
	|| SDECBD A14, #4
	|| DEC.CIRC A1, A3

    ;2    
    LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
        || SMPYF M4, M2, M1
	|| SADDF M6, M6, M4
	|| DEC.CIRC A1, A3

    ;3    
    LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
        || SMPYF M3, M2, M1
	|| SADDF M5, M5, M3
	|| DEC.CIRC A1, A3

    ;4    
    LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
        || SMPYF M4, M2, M1
	|| SADDF M6, M6, M4
	|| DEC.CIRC A1, A3

epilogue:
    LD.32 M1, *(A7+A1<<#0x2)
    || LD.32 M2, *(A6++#0x4)
    || SMPYF M3, M2, M1
    || SADDF M5, M5, M3
    || DEC.CIRC A1, A3

    SMPYF M4, M2, M1
    || SADDF M6, M6, M4

    SADDF M5, M5, M3
    SADDF M6, M6, M4
    || QDECB A14, #3, @epilogue0, @epilogue1, @epilogue2, @

/// These codes will execute the iterations which are a non-multiples of 4
epilogue3:
    ;1
	LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
	|| DEC.CIRC A1, A3

    ;2
	LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
	|| SMPYF M3, M2, M1
	|| DEC.CIRC A1, A3
	
	;3
    LD.32 M1, *(A7+A1<<#0x2)
    || LD.32 M2, *(A6++#0x4)
    || SMPYF M4, M2, M1
    || SADDF M5, M5, M3
    || DEC.CIRC A1, A3

     SMPYF M3, M2, M1
     SADDF M6, M6, M4
     SADDF M5, M5, M3
    
    INC.CIRC A0,A3  ; A0=0 if A0>=M-1, else A0+=1
    || DECBD A13, #1, @fir_loop
    SADDF M5, M5, M6 		; no stall due to above
    ;; ST.32 *A8, A0  			; update *ptr_circ_buf_index
    ADD.U16 A5, #4        
    ST.32 *A4, M5		; no stall due to above
    || ADD.U16 A4, #4
    
    B @func_exit_point, UNC

epilogue2:	
    LD.32 M1, *(A7+A1<<#0x2)
    || LD.32 M2, *(A6++#0x4)
    || DEC.CIRC A1, A3

    ;1
	LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *A6
	|| SMPYF M3, M2, M1
	|| DEC.CIRC A1, A3
    
	SMPYF M4, M2, M1
	SADDF M5, M5, M3	; no stall
	SADDF M6, M6, M4	; no stall
	
	INC.CIRC A0,A3  ; A0=0 if A0>=M-1, else A0+=1
	|| DECBD A13, #1, @fir_loop
	SADDF M5, M5, M6 		; no stall due to above
	;; ST.32 *A8, A0  			; update *ptr_circ_buf_index
	ADD.U16 A5, #4        
	ST.32 *A4, M5		; no stall due to above
	|| ADD.U16 A4, #4

	B @func_exit_point, UNC

epilogue1:
    ;1
	LD.32 M1, *(A7+A1<<#0x2)
	|| LD.32 M2, *(A6++#0x4)
	|| DEC.CIRC A1, A3
	
	SMPYF M3, M2, M1
	SADDF M5, M5, M3

epilogue0:
	
	INC.CIRC A0,A3  ; A0=0 if A0>=M-1, else A0+=1
	
	DECBD A13, #1, @fir_loop
	SADDF M5, M5, M6 		; no stall due to above
	;; ST.32 *A8, A0  ; update *ptr_circ_buf_index
	ADD.U16 A5, #4	
	|| ST.32 *A4, M5		; no stall due to above
        ADD.U16 A4, #4

func_exit_point:
	RETD *(A15-#0x20)
	LD.32 A14, *(A15-#0x8)
       ||SUB A5, A5, A12,#2  ; Restore the A5 pointer in = in - N
        ;LD.64 XA12,*(A15-#0x10)
	LD.32 A12,*(A15-#0x10)
       || SUB A4, A4, A12,#2  ; Restore the A4 pointer out = out - N
	LD.32 A13,*(A15-#0x18)
        || SUB.U16 A15, #0x20        
