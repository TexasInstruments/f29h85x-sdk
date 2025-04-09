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

;; This is the 64-bit version
;;; NOTE !!!! This scheme will ONLY WORK for fir->order values which are a multiple of 8.
.section   kernel_asm, "ax"
.global c29_fir_sample_asm  
.type c29_fir_sample_asm,@function


;;; (pointer)fir : A4
;;; (pointer)coeffp : A5 
;;; (pointer) k_in : A6
;;; (int32_t) limit;
;;; For the example where fir->order = 64, limit will be 31. Total 32 executions of the dual-mac are needed.
					  ;; limit/31 is also the circular buffer threshold

;;;#define k_in A6
;;;#define limit D0

;;; Load coeffs and data 64-bits at a time.
c29_fir_sample_asm:
    ADD.U16	A15,A15,#0x20 ;; Allocate stack
;; M0, M1 = acc1, acc2
;; A0 = k_lcl
    LD.32 A0, *(A6)
    || ST.32 *(A15 - #0x10), A14
    MV A8, D0  ;; Limit count for the loop  for ( j = 0; j <= limit; j++ ) 
    || LD.32 A7, *(A4+#0x4) ;;;;; A7 will point to fir->dbuffer_ptr[]
    || ZERO M6

    ZERO M7 ;;;;;; Zero acc1
    || MV A9, A8  ;; A9 is used as circular buffer 
    || SUB.U16 A14, A8, #4     ;; Adjust the loop count as follows sw_count = (count - 4)/4 ;
    || ZERO M14

       LSR A14, A14, #2	       	;; This will result in A14 = 6. Hence, the 'kernel_loop' body will iterate (6+1) 7 times
    || ZERO M15		       	;; 4 dual-macs are executed as part of the prologue and epilogue.
				;; Each kernel_loop iteration executes 4 dual-MACs. So, total dual-MACs in this example will be 
				;; (7*4) + 4(part of prologue and epilogue) = 32 dual-MACs. which is 64 (fir->order)
;;; prologue
    || LD.64 XM0, *(A5++)
    || LD.64 XM2, *(A7+A0<<3)
    || DEC.CIRC A0, A9

    LD.64 XM8, *(A5++)
    || LD.64 XM10, *(A7+A0<<3)
    || SMPYF M4, M0, M2
    || SMPYF M5, M1, M3
    || DEC.CIRC A0, A9

    LD.64 XM0, *(A5++)
    || LD.64 XM2, *(A7+A0<<3)
    || DEC.CIRC A0, A9
    || SMPYF M12, M8, M10
    || SMPYF M13, M9, M11

.align 16
kernel_loop:
    SDECBD A14, #1, @kernel_loop
    || LD.64 XM8, *(A5++)
    || LD.64 XM10, *(A7+A0<<3)
    || DEC.CIRC A0, A9
    || SMPYF M4, M0, M2
    || SMPYF M5, M1, M3
    || SADDF M6, M6, M4
    || SADDF M7, M7, M5

       LD.64 XM0, *(A5++)
    || LD.64 XM2, *(A7+A0<<3)
    || DEC.CIRC A0, A9
    || SMPYF M12, M8, M10
    || SMPYF M13, M9, M11
    || SADDF M14, M14, M12
    || SADDF M15, M15, M13

       LD.64 XM8, *(A5++)
    || LD.64 XM10, *(A7+A0<<3)
    || DEC.CIRC A0, A9
    || SMPYF M4, M0, M2
    || SMPYF M5, M1, M3
    || SADDF M6, M6, M4
    || SADDF M7, M7, M5

       LD.64 XM0, *(A5++)
    || LD.64 XM2, *(A7+A0<<3)
    || DEC.CIRC A0, A9
    || SMPYF M12, M8, M10
    || SMPYF M13, M9, M11
    || SADDF M14, M14, M12
    || SADDF M15, M15, M13

;;; Epilogue
       LD.64 XM8, *(A5++)
    || LD.64 XM10, *(A7+A0<<3)
    || DEC.CIRC A0, A9
    || SADDF M6, M6, M4
    || SADDF M7, M7, M5
    || SMPYF M4, M0, M2
    || SMPYF M5, M1, M3

       SMPYF M12, M8, M10
    || SMPYF M13, M9, M11
    || SADDF M14, M14, M12
    || SADDF M15, M15, M13

       SADDF M6, M6, M4
    || SADDF M7, M7, M5

       SADDF M14, M14, M12
    || SADDF M15, M15, M13

    || RETD	*(ADDR1)(A15-=#0x28) ;;;;; De-allocate stack and return
    || LD.32 A14, *(A15 - #0x10)
    SADDF M6, M6, M7
    ADDF M0, M14, M15 ;;;;; Final value returned in M0
    ||ST.32 *A6, A0 ;;;;; *k_in = k_lcl
    SADDF M0, M0, M6



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; End of file ;;;;;;;;;;;;;;;;;;;;