    .global    HwiP_inISR
;
; Return values:
;    0 = main code
;    1 = INT
;    2 = RINT
;    3 = NMI
;
HwiP_inISR:
     ATOMIC.REG #4					 ; Next 4 instruction packets are atomic
	 RETD	*(A15-#8)				 ; Get return address from stack
  || ST.32  *(A15-#4), DSTS		     ; - but do not deallocate spare stack space
	                        		 ; - delayed return will take effect after 3 delay slots
 								     ; In parallel use spare stack space to store DSTS register
     LD.32  D0, *(A15-4)    		 ; Delay slot 1: Copy DSTS from stack into the D0 register
     AND    D0, #(1 << 18 | 1 << 17) ; Delay slot 2: Mask all but bits 18:17 in DSTS
  || SUB.U16 A15, A15, #8            ;               and deallocate stack
     LSR     D0, D0, #17             ; Delay slot 3: Right justify result
                            		 ; Delayed return takes effect
