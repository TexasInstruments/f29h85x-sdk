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
 .global crc_asm
 .type   crc_asm,@function

;;; 
;;;; uint32_t crc_asm(char *buf_ptr, uint32_t poly, uint32_t crc_config, uint32_t byte_count, uint32_t seed);
;;; A4 = buf_ptr
;;; D0 = poly
;;; D1 = crc_config
;;; D2 = byte_count - 1 (This decrement happens in C, so decbd can directly use this)
;;; D3 = seed

crc_asm: 
	MV A7, D2
crc_loop_2:
	LD.U8   D4, *(A4++#1)
	CRC    D3, D4, D0, D1
	DECB   A7, #1, @crc_loop_2
    RET
	|| MV D0, D3
;; end of function

.section   kernel_asm, "ax"
.global crc_asm_16
.type   crc_asm_16,@function

;;; 
;;;; uint32_t crc_asm_16(uint16_t *buf_ptr, uint32_t poly, uint32_t crc_config, uint32_t byte_count, uint32_t seed);
;;; A4 = buf_ptr
;;; D0 = poly
;;; D1 = crc_config
;;; D2 = byte_count - 1 (This decrement happens in C, so decbd can directly use this)
;;; D3 = seed

crc_asm_16: 
	MV A7, D2
crc_loop_16:
	LD.U8   D4, *(A4+#1)
	LD.U8   D5, *(A4++#2)
	|| CRC    D3, D4, D0, D1
	CRC    D3, D5, D0, D1
	DECB   A7, #2, @crc_loop_16
    RET
	|| MV D0, D3
;; end of function

.section   kernel_asm, "ax"
.global crc_asm_32
.type   crc_asm_32,@function

;;; 
;;;; uint32_t crc_asm_32(uint32_t *buf_ptr, uint32_t poly, uint32_t crc_config, uint32_t byte_count, uint32_t seed);
;;; A4 = buf_ptr
;;; D0 = poly
;;; D1 = crc_config
;;; D2 = byte_count - 1 (This decrement happens in C, so decbd can directly use this)
;;; D3 = seed

crc_asm_32: 
	MV A7, D2
crc_loop_32:
	LD.U8   D4, *(A4+#3)
	LD.U8   D5, *(A4+#2)
	|| CRC    D3, D4, D0, D1
	LD.U8   D6, *(A4+#1)
	|| CRC    D3, D5, D0, D1
	LD.U8   D7, *(A4++#4)
	|| CRC    D3, D6, D0, D1
	CRC    D3, D7, D0, D1
	DECB   A7, #4, @crc_loop_32
    RET
	|| MV D0, D3
;; end of function
