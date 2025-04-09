;;//*****************************************************************************
;;// Title:   CASM Version Of 4x4 Matrix Multiply
;;//
;;// CPU:     C29 with FPU64
;;//
;;// Call:    void    matrix_mpy_f64_4by4_casm(double Ma_f64[][4], double Mb_f64[][4], double Mc_f64[][4]);
;;//
;;//
;;// Cycles:  4 (CALL) + 25 + 16 + 16 + 16 =  77 (running from RAM, Mc,Mb,Ma in seperate RAM blocks)
;;//          4 (CALL) + 34 + 24 + 24 + 18 = 104 (running from RAM, Mc,Mb,Ma in same RAM block)
;;//*****************************************************************************
;; Registers that need saving/restoring if used:
;;  A10-A14, D10-D15, and M26-M31
;;

		.text
		.globl	matrix_mpy_f64_4by4_casm
		.type	matrix_mpy_f64_4by4_casm,@function

matrix_mpy_f64_4by4_casm:
;; On Entry:
;; A4 => Ma_f64[0][0]
;; A5 => Mb_f64[0][0]
;; A6 => Mc_f64[0][0]

;;    Mc_f64[0][0] = (Mb_f64[0][0] * Ma_f64[0][0]) + (Mb_f64[0][1] * Ma_f64[1][0]) + (Mb_f64[0][2] * Ma_f64[2][0]) + (Mb_f64[0][3] * Ma_f64[3][0]);
;;    Mc_f64[0][1] = (Mb_f64[0][0] * Ma_f64[0][1]) + (Mb_f64[0][1] * Ma_f64[1][1]) + (Mb_f64[0][2] * Ma_f64[2][1]) + (Mb_f64[0][3] * Ma_f64[3][1]);
;;    Mc_f64[0][2] = (Mb_f64[0][0] * Ma_f64[0][2]) + (Mb_f64[0][1] * Ma_f64[1][2]) + (Mb_f64[0][2] * Ma_f64[2][2]) + (Mb_f64[0][3] * Ma_f64[3][2]);
;;    Mc_f64[0][3] = (Mb_f64[0][0] * Ma_f64[0][3]) + (Mb_f64[0][1] * Ma_f64[1][3]) + (Mb_f64[0][2] * Ma_f64[2][3]) + (Mb_f64[0][3] * Ma_f64[3][3]);

		LD.64		XM0,*(A5+#0)		; XM0  = Mb[0][0]
		||LD.64		XM2,*(A6+#0)		; XM2  = Ma[0][0]

		LD.64		XM2,*(A6+#8)		; XM2  = Ma[0][1]
		||MPYF		XM4,XM0,XM2			; XM4  = Mb[0][0] * Ma[0][0]

		LD.64		XM2,*(A6+#16)		; XM2  = Ma[0][2]
		||MPYF		XM6,XM0,XM2			; XM6  = Mb[0][0] * Ma[0][1]

		LD.64		XM2,*(A6+#24)		; XM2  = Ma[0][3]
		||MPYF		XM8,XM0,XM2			; XM8  = Mb[0][0] * Ma[0][2]

		LD.64		XM2,*(A6+#32)		; XM2  = Ma[1][0]
		||MPYF		XM10,XM0,XM2		; XM10 = Mb[0][0] * Ma[0][3]

		LD.64		XM0,*(A5+#8)		; XM0  = Mb[0][1]
		||LD.64		XM2,*(A6+#40)		; XM2  = Ma[1][1]
		||MPYF		XM12,XM0,XM2		; XM12 = Mb[0][1] * Ma[1][0]

		LD.64		XM2,*(A6+#48)		; XM2  = Ma[1][2]
		||MPYF		XM14,XM0,XM2		; XM14 = Mb[0][1] * Ma[1][1]

		LD.64		XM2,*(A6+#56)		; XM2  = Ma[1][3]
		||MPYF		XM16,XM0,XM2		; XM16 = Mb[0][1] * Ma[1][2]

		LD.64		XM2,*(A6+#64)		; XM2  = Ma[2][0]
		||MPYF		XM18,XM0,XM2		; XM18 = Mb[0][1] * Ma[1][3]

		LD.64		XM0,*(A5+#16)		; XM0  = Mb[0][2]
		||LD.64		XM2,*(A6+#72)		; XM2  = Ma[2][1]
		||MPYF		XM4,XM0,XM2			; XM4  = Mb[0][2] * Ma[2][0]
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#80)		; XM2  = Ma[2][2]
		||MPYF		XM6,XM0,XM2			; XM6  = Mb[0][2] * Ma[2][1]
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#88)		; XM2  = Ma[2][3]
		||MPYF		XM8,XM0,XM2			; XM8  = Mb[0][2] * Ma[2][2]
		||ADDF		XM16,XM16,XM8

		LD.64		XM2,*(A6+#96)		; XM2  = Ma[3][0]
		||MPYF		XM10,XM0,XM2		; XM10 = Mb[0][2] * Ma[2][3]
		||ADDF		XM18,XM18,XM10

		LD.64		XM0,*(A5+#24)		; XM0  = Mb[0][3]
		||LD.64		XM2,*(A6+#104)		; XM2  = Ma[3][1]
		||MPYF		XM4,XM0,XM2			; XM4  = Mb[0][3] * Ma[3][0]
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#112)		; XM2  = Ma[3][2]
		||MPYF		XM6,XM0,XM2			; XM6  = Mb[0][3] * Ma[3][1]
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#120)		; XM2  = Ma[3][3]
		||MPYF		XM8,XM0,XM2			; XM8  = Mb[0][3] * Ma[3][2]
		||ADDF		XM16,XM16,XM8

		LD.64		XM0,*(A5+#32)		; XM0  = Mb[1][0]
		||LD.64		XM2,*(A6+#0)
		||MPYF		XM10,XM0,XM2		; XM10 = Mb[0][3] * Ma[3][3]
		||ADDF		XM18,XM18,XM10

		LD.64		XM2,*(A6+#8)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#16)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#24)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		LD.64		XM2,*(A6+#32)
		||MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		LD.64		XM0,*(A5+#40)		; XM0  = Mb[1][1]
		||LD.64		XM2,*(A6+#40)
		||MPYF		XM12,XM0,XM2
		||ST.64		*(A4+#0),XM12		; Mc[0][0] = XM12

		LD.64		XM2,*(A6+#48)
		||MPYF		XM14,XM0,XM2
		||ST.64		*(A4+#8),XM14		; Mc[0][1] = XM14

		LD.64		XM2,*(A6+#56)
		||MPYF		XM16,XM0,XM2
		||ST.64		*(A4+#16),XM16		; Mc[0][2] = XM16

		LD.64		XM2,*(A6+#64)
		||MPYF		XM18,XM0,XM2
		||ST.64		*(A4+#24),XM18		; Mc[0][3] = XM18
		; 25 cycles no memory conflicts 	(Mc,Mb,Ma in seperate RAM blocks)
		; 34 cycles with memory conflicts 	(Mc,Mb,Ma in same RAM block)

;;    Mc_f64[1][0] = (Mb_f64[1][0] * Ma_f64[0][0]) + (Mb_f64[1][1] * Ma_f64[1][0]) + (Mb_f64[1][2] * Ma_f64[2][0]) + (Mb_f64[1][3] * Ma_f64[3][0]);
;;    Mc_f64[1][1] = (Mb_f64[1][0] * Ma_f64[0][1]) + (Mb_f64[1][1] * Ma_f64[1][1]) + (Mb_f64[1][2] * Ma_f64[2][1]) + (Mb_f64[1][3] * Ma_f64[3][1]);
;;    Mc_f64[1][2] = (Mb_f64[1][0] * Ma_f64[0][2]) + (Mb_f64[1][1] * Ma_f64[1][2]) + (Mb_f64[1][2] * Ma_f64[2][2]) + (Mb_f64[1][3] * Ma_f64[3][2]);
;;    Mc_f64[1][3] = (Mb_f64[1][0] * Ma_f64[0][3]) + (Mb_f64[1][1] * Ma_f64[1][3]) + (Mb_f64[1][2] * Ma_f64[2][3]) + (Mb_f64[1][3] * Ma_f64[3][3]);

		LD.64		XM0,*(A5+#48)		; XM0  = Mb[1][2]
		||LD.64		XM2,*(A6+#72)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#80)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#88)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		LD.64		XM2,*(A6+#96)
		||MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		LD.64		XM0,*(A5+#56)		; XM0  = Mb[1][3]
		||LD.64		XM2,*(A6+#104)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#112)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#120)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		LD.64		XM0,*(A5+#64)		; XM0  = Mb[2][0]
		||LD.64		XM2,*(A6+#0)
		||MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		LD.64		XM2,*(A6+#8)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#16)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#24)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		LD.64		XM2,*(A6+#32)
		||MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		LD.64		XM0,*(A5+#72)		; XM0  = Mb[2][1]
		||LD.64		XM2,*(A6+#40)
		||MPYF		XM12,XM0,XM2
		||ST.64		*(A4+#32),XM12		; Mc[1][0] = XM12

		LD.64		XM2,*(A6+#48)
		||MPYF		XM14,XM0,XM2
		||ST.64		*(A4+#40),XM14		; Mc[1][1] = XM14

		LD.64		XM2,*(A6+#56)
		||MPYF		XM16,XM0,XM2
		||ST.64		*(A4+#48),XM16		; Mc[1][2] = XM16

		LD.64		XM2,*(A6+#64)
		||MPYF		XM18,XM0,XM2
		||ST.64		*(A4+#56),XM18		; Mc[1][3] = XM18
		; 16 cycles no memory conflicts 	(Mc,Mb,Ma in seperate RAM blocks)
		; 24 cycles with memory conflicts 	(Mc,Mb,Ma in same RAM block)

;;    Mc_f64[2][0] = (Mb_f64[2][0] * Ma_f64[0][0]) + (Mb_f64[2][1] * Ma_f64[1][0]) + (Mb_f64[2][2] * Ma_f64[2][0]) + (Mb_f64[2][3] * Ma_f64[3][0]);
;;    Mc_f64[2][1] = (Mb_f64[2][0] * Ma_f64[0][1]) + (Mb_f64[2][1] * Ma_f64[1][1]) + (Mb_f64[2][2] * Ma_f64[2][1]) + (Mb_f64[2][3] * Ma_f64[3][1]);
;;    Mc_f64[2][2] = (Mb_f64[2][0] * Ma_f64[0][2]) + (Mb_f64[2][1] * Ma_f64[1][2]) + (Mb_f64[2][2] * Ma_f64[2][2]) + (Mb_f64[2][3] * Ma_f64[3][2]);
;;    Mc_f64[2][3] = (Mb_f64[2][0] * Ma_f64[0][3]) + (Mb_f64[2][1] * Ma_f64[1][3]) + (Mb_f64[2][2] * Ma_f64[2][3]) + (Mb_f64[2][3] * Ma_f64[3][3]);

		LD.64		XM0,*(A5+#80)		; XM0  = Mb[2][2]
		||LD.64		XM2,*(A6+#72)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#80)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#88)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		LD.64		XM2,*(A6+#96)
		||MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		LD.64		XM0,*(A5+#88)		; XM0  = Mb[2][3]
		||LD.64		XM2,*(A6+#104)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#112)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#120)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		LD.64		XM0,*(A5+#96)		; XM0  = Mb[3][0]
		||LD.64		XM2,*(A6+#0)
		||MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		LD.64		XM2,*(A6+#8)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#16)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#24)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		LD.64		XM2,*(A6+#32)
		||MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		LD.64		XM0,*(A5+#104)		; XM0  = Mb[3][1]
		||LD.64		XM2,*(A6+#40)
		||MPYF		XM12,XM0,XM2
		||ST.64		*(A4+#64),XM12		; Mc[2][0] = XM12

		LD.64		XM2,*(A6+#48)
		||MPYF		XM14,XM0,XM2
		||ST.64		*(A4+#72),XM14		; Mc[2][1] = XM14

		LD.64		XM2,*(A6+#56)
		||MPYF		XM16,XM0,XM2
		||ST.64		*(A4+#80),XM16		; Mc[2][2] = XM16

		LD.64		XM2,*(A6+#64)
		||MPYF		XM18,XM0,XM2
		||ST.64		*(A4+#88),XM18		; Mc[2][3] = XM18
		; 16 cycles no memory conflicts 	(Mc,Mb,Ma in seperate RAM blocks)
		; 24 cycles with memory conflicts 	(Mc,Mb,Ma in same RAM block)

;;    Mc_f64[3][0] = (Mb_f64[3][0] * Ma_f64[0][0]) + (Mb_f64[3][1] * Ma_f64[1][0]) + (Mb_f64[3][2] * Ma_f64[2][0]) + (Mb_f64[3][3] * Ma_f64[3][0]);
;;    Mc_f64[3][1] = (Mb_f64[3][0] * Ma_f64[0][1]) + (Mb_f64[3][1] * Ma_f64[1][1]) + (Mb_f64[3][2] * Ma_f64[2][1]) + (Mb_f64[3][3] * Ma_f64[3][1]);
;;    Mc_f64[3][2] = (Mb_f64[3][0] * Ma_f64[0][2]) + (Mb_f64[3][1] * Ma_f64[1][2]) + (Mb_f64[3][2] * Ma_f64[2][2]) + (Mb_f64[3][3] * Ma_f64[3][2]);
;;    Mc_f64[3][3] = (Mb_f64[3][0] * Ma_f64[0][3]) + (Mb_f64[3][1] * Ma_f64[1][3]) + (Mb_f64[3][2] * Ma_f64[2][3]) + (Mb_f64[3][3] * Ma_f64[3][3]);

		LD.64		XM0,*(A5+#112)		; XM0  = Mb[3][2]
		||LD.64		XM2,*(A6+#72)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#80)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#88)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		LD.64		XM2,*(A6+#96)
		||MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		LD.64		XM0,*(A5+#120)		; XM0  = Mb[3][3]
		||LD.64		XM2,*(A6+#104)
		||MPYF		XM4,XM0,XM2
		||ADDF		XM12,XM12,XM4

		LD.64		XM2,*(A6+#112)
		||MPYF		XM6,XM0,XM2
		||ADDF		XM14,XM14,XM6

		LD.64		XM2,*(A6+#120)
		||MPYF		XM8,XM0,XM2
		||ADDF		XM16,XM16,XM8

		MPYF		XM10,XM0,XM2
		||ADDF		XM18,XM18,XM10

		ADDF		XM12,XM12,XM4

		ADDF		XM14,XM14,XM6

		ADDF		XM16,XM16,XM8

		ADDF		XM18,XM18,XM10

		RETD
		||ST.64		*(A4+#96),XM12		; Mc[3][0] = XM12

		ST.64		*(A4+#104),XM14		; Mc[3][1] = XM14

		ST.64		*(A4+#112),XM16		; Mc[3][2] = XM16

		ST.64		*(A4+#120),XM18		; Mc[3][3] = XM18
		; 16 cycles no memory conflicts 	(Mc,Mb,Ma in seperate RAM blocks)
		; 18 cycles with memory conflicts 	(Mc,Mb,Ma in same RAM block)

;;=============================================================================
;; End of file.
;;=============================================================================
