;;//###########################################################################
;;//
;;// FILE:  sdl_sic_s.asm
;;//
;;// TITLE: Safety Diagnostic Library module assembly
;;//
;;//###########################################################################
;;// $Copyright:
;// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
;//
;// Redistribution and use in source and binary forms, with or without 
;// modification, are permitted provided that the following conditions 
;// are met:
;// 
;//   Redistributions of source code must retain the above copyright 
;//   notice, this list of conditions and the following disclaimer.
;// 
;//   Redistributions in binary form must reproduce the above copyright
;//   notice, this list of conditions and the following disclaimer in the 
;//   documentation and/or other materials provided with the   
;//   distribution.
;// 
;//   Neither the name of Texas Instruments Incorporated nor the names of
;//   its contributors may be used to endorse or promote products derived
;//   from this software without specific prior written permission.
;// 
;// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;// $
;;//###########################################################################

.text
  .global SDL_SIC_dr2Read
  .global SDL_SIC_exec

;;*****************************************************************************
;; Subroutine SDL_SIC_dr2Read
;;     for the SDL_SIC_CPU_DR2_emulateFault to have parallel reads.
;;*****************************************************************************

SDL_SIC_dr2Read:

      NOP     #8
      MV      A0, D0
      LD.32   D1, *(A0+#0x20)
              || LD.32 D1, *A0
              || MV A1, PC
      NOP     #8
      MV      D0, A1
      RET

;;*****************************************************************************
;; Subroutine SDL_SIC_exec
;;     for the SDL_SIC_CPU_PR_emulateFault to store and execute opcode.
;;*****************************************************************************

SDL_SIC_exec:
      NOP     #8
      MV      A0, D0
      MV      D1, #0x7A08
      ST.W0   *A0, D1
      LD.W0   D3, *A0 
      CALL    A0
              || MV A1, PC
      NOP     #8
      MV      D0, A1
      RET
