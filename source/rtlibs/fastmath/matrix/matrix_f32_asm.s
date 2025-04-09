;;//*****************************************************************************
;;// Title:     CASM Version Of 4x4 Matrix Multiply
;;//
;;// CPU:       C29 with FPU32
;;//
;;// Call:      void    matrix_mpy_f32_4by4_casm(float Ma_f32[][4], float Mb_f32[][4], float Mc_f32[][4]);
;;//
;;// Cycles:    4 (CALL) + 8  + 8  + 8  + 8  + 5 = 41 (running from RAM, Mc,Mb,Ma in separate RAM blocks)
;;//            4 (CALL) + 12 + 12 + 12 + 10 + 5 = 55 (running from RAM, Mc,Mb,Ma in same RAM block)
;;// Code Size: 224 Bytes
;;//*****************************************************************************
;; Registers that need saving/restoring if used:
;;  A10-A14, D10-D15, and M26-M31
;;

		.text
		.globl	matrix_mpy_f32_4by4_casm
		.type	matrix_mpy_f32_4by4_casm,@function

		.align	16
matrix_mpy_f32_4by4_casm:
		;    On Entry:
		;    A4 => Ma_f32[0][0] = MA11
		;    A5 => Mb_f32[0][0] = MB11
		;    A6 => Mc_f32[0][0] = MC11
		;-------------------------------------------------------------------------------
		;
		;    MC11 = (MA11 * MB11) + (MA12 * MB21) + (MA13 * MB31) + (MA14 * MB41);
		;    MC12 = (MA11 * MB12) + (MA12 * MB22) + (MA13 * MB32) + (MA14 * MB42);
		;    MC13 = (MA11 * MB13) + (MA12 * MB23) + (MA13 * MB33) + (MA14 * MB43);
		;    MC14 = (MA11 * MB14) + (MA12 * MB24) + (MA13 * MB34) + (MA14 * MB44);
		;
		;-----Calculate MC11, MC12, MC13, MC14------------------------------------------
		LD.32		M7,*(A4)		; 16: M7  = MA11            , A4 => MA11
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB11, M1  = MB12, A5 => MB13
		||ST.32		*(A15++#8),A14		; 32: Save A14
		SMPYF		M2,M0,M7		; 16: M2  = MA11 * MB11
		||SMPYF		M3,M1,M7		; 16: M3  = MA11 * MB12
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA11            , A4 => MA12
		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB13, M9  = MB14, A5 => MB21
		||MV.U16	A14,#2			; Loop counter. Repeat 3 times
		SMPYF		M10,M8,M15		; 16: M10 = MA11 * MB13
		||SMPYF		M11,M9,M15		; 16: M11 = MA11 * MB14
		||LD.32		M7,*(A4)		; 16: M7  = MA12            , A4 => MA12
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB21, M1  = MB22, A5 => MB23
		SMPYF		M4,M0,M7		; 16: M4  = MA12 * MB21
		||SMPYF		M5,M1,M7		; 16: M5  = MA12 * MB22
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA12            , A4 => MA13
		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB23, M9  = MB24, A5 => MB31
		SMPYF		M12,M8,M15		; 16: M12 = MA12 * MB23
		||SMPYF		M13,M9,M15		; 16: M13 = MA12 * MB24
		||LD.32		M7,*(A4)		; 16: M7  = MA13            , A4 => MA13
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB31, M1  = MB32, A5 => MB33
		SMPYF		M2,M0,M7		; 16: M2  = MA13 * MB31
		||SMPYF		M3,M1,M7		; 16: M3  = MA13 * MB32
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA13            , A4 => MA14
		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB33, M9  = MB34, A5 => MB41
		SMPYF		M10,M8,M15		; 16: M10 = MA13 * MB33
		||SMPYF		M11,M9,M15		; 16: M11 = MA13 * MB34
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A4)		; 16: M7  = MA14            , A4 => MA14
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB41, M1  = MB42, A5 => MB43
		SMPYF		M2,M0,M7		; 16: M2  = MA14 * MB41
		||SMPYF		M3,M1,M7		; 16: M3  = MA14 * MB42
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA14            , A4 => MA21
		||LD.64		XM8,*(A5--#56)		; 32: M8  = MB43, M9  = MB44, A5 => MB11
		;-------------------------------------------------------------------------------
		;
		;    MC21 = (MA21 * MB11) + (MA22 * MB21) + (MA23 * MB31) + (MA24 * MB41);
		;    MC22 = (MA21 * MB12) + (MA22 * MB22) + (MA23 * MB32) + (MA24 * MB42);
		;    MC23 = (MA21 * MB13) + (MA22 * MB23) + (MA23 * MB33) + (MA24 * MB43);
		;    MC24 = (MA21 * MB14) + (MA22 * MB24) + (MA23 * MB34) + (MA24 * MB44);
		;
		;-----Calculate MC21, MC22, MC23, MC24------------------------------------------
		.align	16
matrix_mpy_f32_4by4_casm_Loop:
		SMPYF		M10,M8,M15		; 16: M10 = MA14 * MB43				|                
		||SMPYF		M11,M9,M15		; 16: M11 = MA14 * MB44				|
		||SADDF		M12,M12,M10		; 16:						|
		||SADDF		M13,M13,M11		; 16:						|
		||LD.32		M7,*(A4)		; 16: M7  = MA21            , A4 => MA21
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB11, M1  = MB12, A5 => MB13
		SMPYF		M2,M0,M7		; 16: M2  = MA21 * MB11
		||SMPYF		M3,M1,M7		; 16: M3  = MA21 * MB12
		||SADDF		M4,M4,M2		; 16: M4  = MC11				|
		||SADDF		M5,M5,M3		; 16: M5  = MC12				|
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA21            , A4 => MA22
		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB13, M9  = MB14, A5 => MB21
		SMPYF		M10,M8,M15		; 16: M10 = MA21 * MB13
		||SMPYF		M11,M9,M15		; 16: M11 = MA21 * MB14
		||SADDF		M12,M12,M10		; 16: M12 = MC13				|
		||SADDF		M13,M13,M11		; 16: M13 = MC14				|
		||LD.32		M7,*(A4)		; 16: M7  = MA22            , A4 => MA22
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB21, M1  = MB22, A5 => MB23
		SMPYF		M4,M0,M7		; 16: M4  = MA22 * MB21
		||SMPYF		M5,M1,M7		; 16: M5  = MA22 * MB22
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA22            , A4 => MA23
		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB23, M9  = MB24, A5 => MB31
		||ST.64		*(A6++#8),XM4		; 32: Store MC11 & MC12				|
		.align	16
		SDECBD		A14,#1,matrix_mpy_f32_4by4_casm_Loop 	; 16:		 
		||SMPYF		M12,M8,M15		; 16: M12 = MA22 * MB23
		||SMPYF		M13,M9,M15		; 16: M13 = MA22 * MB24
		||LD.32		M7,*(A4)		; 16: M7  = MA23            , A4 => MA23
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB31, M1  = MB32, A5 => MB33
		||ST.64		*(A6++#8),XM12		; 32: Store MC13 & MC14				|
		SMPYF		M2,M0,M7		; 16: M2  = MA23 * MB31
		||SMPYF		M3,M1,M7		; 16: M3  = MA23 * MB32
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA23            , A4 => MA24
		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB33, M9  = MB34, A5 => MB41
		SMPYF		M10,M8,M15		; 16: M10 = MA23 * MB33
		||SMPYF		M11,M9,M15		; 16: M11 = MA23 * MB34
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A4)		; 16: M7  = MA24            , A4 => MA24
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB41, M1  = MB42, A5 => MB43
		SMPYF		M2,M0,M7		; 16: M2  = MA24 * MB41
		||SMPYF		M3,M1,M7		; 16: M3  = MA24 * MB42
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA24            , A4 => MA31
		||LD.64		XM8,*(A5--#56)		; 32: M8  = MB43, M9  = MB44, A5 => MB11
		;-------------------------------------------------------------------------------
		;
		;    MC31 = (MA31 * MB11) + (MA32 * MB21) + (MA33 * MB31) + (MA34 * MB41);
		;    MC32 = (MA31 * MB12) + (MA32 * MB22) + (MA33 * MB32) + (MA34 * MB42);
		;    MC33 = (MA31 * MB13) + (MA32 * MB23) + (MA33 * MB33) + (MA34 * MB43);
		;    MC34 = (MA31 * MB14) + (MA32 * MB24) + (MA33 * MB34) + (MA34 * MB44);
		;
		;-----Calculate MC31, MC32, MC33, MC34------------------------------------------
;		SMPYF		M10,M8,M15		; 16: M10 = MA24 * MB43				|
;		||SMPYF		M11,M9,M15		; 16: M11 = MA24 * MB44				|
;		||SADDF		M12,M12,M10		; 16:						|
;		||SADDF		M13,M13,M11		; 16:						|
;		||LD.32		M7,*(A4)		; 16: M7  = MA31            , A4 => MA31
;		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB11, M1  = MB12, A5 => MB13
;		SMPYF		M2,M0,M7		; 16: M2  = MA31 * MB11
;		||SMPYF		M3,M1,M7		; 16: M3  = MA31 * MB12
;		||SADDF		M4,M4,M2		; 16: M4  = MC21				|
;		||SADDF		M5,M5,M3		; 16: M5  = MC22				|
;		||LD.32		M15,*(A4++#4)		; 16: M15 = MA31            , A4 => MA32
;		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB13, M9  = MB14, A5 => MB21
;		SMPYF		M10,M8,M15		; 16: M10 = MA31 * MB13
;		||SMPYF		M11,M9,M15		; 16: M11 = MA31 * MB14
;		||SADDF		M12,M12,M10		; 16: M12 = MC23				|
;		||SADDF		M13,M13,M11		; 16: M13 = MC24				|
;		||LD.32		M7,*(A4)		; 16: M7  = MA32            , A4 => MA32
;		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB21, M1  = MB22, A5 => MB23
;		SMPYF		M4,M0,M7		; 16: M4  = MA32 * MB21
;		||SMPYF		M5,M1,M7		; 16: M5  = MA32 * MB22
;		||LD.32		M15,*(A4++#4)		; 16: M15 = MA32            , A4 => MA33
;		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB23, M9  = MB24, A5 => MB31
;		||ST.64		*(A6++#8),XM4		; 32: Store MC21 & MC22				|
;		SMPYF		M12,M8,M15		; 16: M12 = MA32 * MB23
;		||SMPYF		M13,M9,M15		; 16: M13 = MA32 * MB24
;		||LD.32		M7,*(A4)		; 16: M7  = MA33            , A4 => MA33
;		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB31, M1  = MB32, A5 => MB33
;		||ST.64		*(A6++#8),XM12		; 32: Store MC23 & MC24				|
;		SMPYF		M2,M0,M7		; 16: M2  = MA33 * MB31
;		||SMPYF		M3,M1,M7		; 16: M3  = MA33 * MB32
;		||SADDF		M4,M4,M2		; 16:
;		||SADDF		M5,M5,M3		; 16:
;		||LD.32		M15,*(A4++#4)		; 16: M15 = MA33            , A4 => MA34
;		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB33, M9  = MB34, A5 => MB41
;		SMPYF		M10,M8,M15		; 16: M10 = MA33 * MB33
;		||SMPYF		M11,M9,M15		; 16: M11 = MA33 * MB34
;		||SADDF		M12,M12,M10		; 16:
;		||SADDF		M13,M13,M11		; 16:
;		||LD.32		M7,*(A4)		; 16: M7  = MA34            , A4 => MA34
;		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB41, M1  = MB42, A5 => MB43
;		SMPYF		M2,M0,M7		; 16: M2  = MA34 * MB41
;		||SMPYF		M3,M1,M7		; 16: M3  = MA34 * MB42
;		||SADDF		M4,M4,M2		; 16:
;		||SADDF		M5,M5,M3		; 16:
;		||LD.32		M15,*(A4++#4)		; 16: M15 = MA34            , A4 => MA41
;		||LD.64		XM8,*(A5--#56)		; 32: M8  = MB43, M9  = MB44, A5 => MB11
		;-------------------------------------------------------------------------------
		;		
		;    MC41 = (MA41 * MB11) + (MA42 * MB21) + (MA43 * MB31) + (MA44 * MB41);
		;    MC42 = (MA41 * MB12) + (MA42 * MB22) + (MA43 * MB32) + (MA44 * MB42);
		;    MC43 = (MA41 * MB13) + (MA42 * MB23) + (MA43 * MB33) + (MA44 * MB43);
		;    MC44 = (MA41 * MB14) + (MA42 * MB24) + (MA43 * MB34) + (MA44 * MB44);
		;
		;-----Calculate MC41, MC42, MC43, MC44------------------------------------------
;		SMPYF		M10,M8,M15		; 16: M10 = MA34 * MB43				|
;		||SMPYF		M11,M9,M15		; 16: M11 = MA34 * MB44				|
;		||SADDF		M12,M12,M10		; 16:						|
;		||SADDF		M13,M13,M11		; 16:						|
;		||LD.32		M7,*(A4)		; 16: M7  = MA41            , A4 => MA41
;		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB11, M1  = MB12, A5 => MB13
;		SMPYF		M2,M0,M7		; 16: M2  = MA41 * MB11
;		||SMPYF		M3,M1,M7		; 16: M3  = MA41 * MB12
;		||SADDF		M4,M4,M2		; 16: M4  = MC31				|
;		||SADDF		M5,M5,M3		; 16: M5  = MC32				|
;		||LD.32		M15,*(A4++#4)		; 16: M15 = MA41            , A4 => MA42
;		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB13, M9  = MB14, A5 => MB21
;		SMPYF		M10,M8,M15		; 16: M10 = MA41 * MB13
;		||SMPYF		M11,M9,M15		; 16: M11 = MA41 * MB14
;		||SADDF		M12,M12,M10		; 16: M12 = MC33				|
;		||SADDF		M13,M13,M11		; 16: M13 = MC34				|
;		||LD.32		M7,*(A4)		; 16: M7  = MA42            , A4 => MA42
;		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB21, M1  = MB22, A5 => MB23
;		SMPYF		M4,M0,M7		; 16: M4  = MA42 * MB21
;		||SMPYF		M5,M1,M7		; 16: M5  = MA42 * MB22
;		||LD.32		M15,*(A4++#4)		; 16: M15 = MA42            , A4 => MA43
;		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB23, M9  = MB24, A5 => MB31
;		||ST.64		*(A6++#8),XM4		; 32: Store MC31 & MC32				|
;		SMPYF		M12,M8,M15		; 16: M12 = MA42 * MB23
;		||SMPYF		M13,M9,M15		; 16: M13 = MA42 * MB24
;		||LD.32		M7,*(A4)		; 16: M7  = MA43            , A4 => MA43
;		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB31, M1  = MB32, A5 => MB33
;		||ST.64		*(A6++#8),XM12		; 32: Store MC33 & MC34				|
;		SMPYF		M2,M0,M7		; 16: M2  = MA43 * MB31
;		||SMPYF		M3,M1,M7		; 16: M3  = MA43 * MB32
;		||SADDF		M4,M4,M2		; 16:
;		||SADDF		M5,M5,M3		; 16:
;		||LD.32		M15,*(A4++#4)		; 16: M15 = MA43            , A4 => MA44
;		||LD.64		XM8,*(A5++#8)		; 32: M8  = MB33, M9  = MB34, A5 => MB41
;		SMPYF		M10,M8,M15		; 16: M10 = MA43 * MB33
;		||SMPYF		M11,M9,M15		; 16: M11 = MA43 * MB34
;		||SADDF		M12,M12,M10		; 16:
;		||SADDF		M13,M13,M11		; 16:
;		||LD.32		M7,*(A4)		; 16: M7  = MA44            , A4 => MA44
;		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB41, M1  = MB42, A5 => MB43
;		SMPYF		M2,M0,M7		; 16: M2  = MA44 * MB41
;		||SMPYF		M3,M1,M7		; 16: M3  = MA44 * MB42
;		||SADDF		M4,M4,M2		; 16:
;		||SADDF		M5,M5,M3		; 16:
;		||LD.32		M15,*(A4--#60)		; 16: M15 = MA44            , A4 => MA11
;		||LD.64		XM8,*(A5--#56)		; 32: M8  = MB43, M9  = MB44, A5 => MB11
		;-------------------------------------------------------------------------------
		SMPYF		M10,M8,M15		; 16: M10 = MA44 * MB43				|
		||SMPYF		M11,M9,M15		; 16: M11 = MA44 * MB44				|
		||SADDF		M12,M12,M10		; 16:						|
		||SADDF		M13,M13,M11		; 16:						|
		||LD.32		A14,*(A15-=#8)		; 32: Restore A14
		RETD
		||SADDF		M4,M4,M2		; 16: M4  = MC41				|
		||SADDF		M5,M5,M3		; 16: M5  = MC42				|
		SADDF		M12,M12,M10		; 16: M12 = MC43				|
		||SADDF		M13,M13,M11		; 16: M13 = MC44				|
		ST.64		*(A6++#8),XM4		; 32: Store MC41 & MC42				|
		ST.64		*(A6++#8),XM12		; 32: Store MC43 & MC44				|

;;//*****************************************************************************
;;// Title:     CASM Version Of 4x1 Matrix Multiply
;;//
;;// CPU:       C29 with FPU32
;;//
;;// Call:      void    matrix_mpy_f32_4by1_casm(float Ma_f32[][4], float Mb_f32[], float Mc_f32[]);
;;//
;;// Cycles:    4 (CALL) + 8  + 5 = 17 (running from RAM, Mc,Mb,Ma in separate RAM blocks)
;;//            4 (CALL) + 10 + 5 = 19 (running from RAM, Mc,Mb,Ma in same RAM block)
;;// Code Size: 112 Bytes
;;//*****************************************************************************
;; Registers that need saving/restoring if used:
;;  A10-A14, D10-D15, and M26-M31
;;
		.text
		.globl	matrix_mpy_f32_4by1_casm
		.type	matrix_mpy_f32_4by1_casm,@function

		.align	16
matrix_mpy_f32_4by1_casm:
		;    On Entry:
		;    A4 => Ma_f32[0][0] = MA11
		;    A5 => Mb_f32[0]    = MB1
		;    A6 => Mc_f32[0]    = MC1
		;-------------------------------------------------------------------------------
		;
		;    MC1 = (MA11 * MB1) + (MA12 * MB2) + (MA13 * MB3) + (MA14 * MB4);
		;    MC2 = (MA21 * MB1) + (MA22 * MB2) + (MA23 * MB3) + (MA24 * MB4);
		;    MC3 = (MA31 * MB1) + (MA32 * MB2) + (MA33 * MB3) + (MA34 * MB4);
		;    MC4 = (MA41 * MB1) + (MA42 * MB2) + (MA43 * MB3) + (MA44 * MB4);
		;
		;-----Calculate MC1, MC2, MC3, MC4----------------------------------------------
		LD.32		M7,*(A5)		; 16: M7  = MB1             , A4 => MB1
		||LD.64		XM0,*(A4++#8)		; 32: M0  = MA11, M1  = MA12, A5 => MA13
		SMPYF		M2,M0,M7		; 16: M2  = MB1 * MA11
		||SMPYF		M3,M1,M7		; 16: M3  = MB1 * MA12
		||LD.32		M15,*(A5++#4)		; 16: M15 = MB1             , A4 => MB2
		||LD.64		XM8,*(A4++#8)		; 32: M8  = MA13, M9  = MA14, A5 => MA21
		SMPYF		M10,M8,M15		; 16: M10 = MB1 * MA13
		||SMPYF		M11,M9,M15		; 16: M11 = MB1 * MA14
		||LD.32		M7,*(A5)		; 16: M7  = MB2             , A4 => MB2
		||LD.64		XM0,*(A4++#8)		; 32: M0  = MA21, M1  = MA22, A5 => MA23
		SMPYF		M4,M0,M7		; 16: M4  = MB2 * MA21
		||SMPYF		M5,M1,M7		; 16: M5  = MB2 * MA22
		||LD.32		M15,*(A5++#4)		; 16: M15 = MB2             , A4 => MB3
		||LD.64		XM8,*(A4++#8)		; 32: M8  = MA23, M9  = MA24, A5 => MA31
		SMPYF		M12,M8,M15		; 16: M12 = MB2 * MA23
		||SMPYF		M13,M9,M15		; 16: M13 = MB2 * MA24
		||LD.32		M7,*(A5)		; 16: M7  = MB3             , A4 => MB3
		||LD.64		XM0,*(A4++#8)		; 32: M0  = MA31, M1  = MA32, A5 => MA33
		SMPYF		M2,M0,M7		; 16: M2  = MB3 * MA31
		||SMPYF		M3,M1,M7		; 16: M3  = MB3 * MA32
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A5++#4)		; 16: M15 = MB3             , A4 => MB4
		||LD.64		XM8,*(A4++#8)		; 32: M8  = MA33, M9  = MA34, A5 => MA41
		SMPYF		M10,M8,M15		; 16: M10 = MB3 * MA33
		||SMPYF		M11,M9,M15		; 16: M11 = MB3 * MA34
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A5)		; 16: M7  = MB4             , A4 => MB4
		||LD.64		XM0,*(A4++#8)		; 32: M0  = MBA1, M1  = MA42, A5 => MA43
		SMPYF		M2,M0,M7		; 16: M2  = MB4 * MA41
		||SMPYF		M3,M1,M7		; 16: M3  = MB4 * MA42
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A5--#12)		; 16: M15 = MB4             , A4 => MB1
		||LD.64		XM8,*(A4--#56)		; 32: M8  = MA43, M9  = MA44, A5 => MA11
		;-------------------------------------------------------------------------------
		SMPYF		M10,M8,M15		; 16: M10 = MB4 * MA43				|                
		||SMPYF		M11,M9,M15		; 16: M11 = MB4 * MA44				|
		||SADDF		M12,M12,M10		; 16:						|
		||SADDF		M13,M13,M11		; 16:						|
		RETD
		||SADDF		M4,M4,M2		; 16: M4  = MC1					|
		||SADDF		M5,M5,M3		; 16: M5  = MC2					|
		SADDF		M12,M12,M10		; 16: M12 = MC3					|
		||SADDF		M13,M13,M11		; 16: M13 = MC4					|
		ST.64		*(A6++#8),XM4		; 32: Store MC1 & MC2				|
		ST.64		*(A6++#8),XM12		; 32: Store MC3 & MC4				|

;;//*****************************************************************************
;;// Title:   CASM Version Of 6x6 Matrix Multiply
;;//
;;// CPU:     C29 with FPU32
;;//
;;// Call:    void    matrix_mpy_f32_6by6_casm(float Ma_f32[][6], float Mb_f32[][6], float Mc_f32[][6]);
;;//
;;//
;;// Cycles:  4 (CALL) + 8  + 8  + 8  + 8  + 5 = 41 (running from RAM, Mc,Mb,Ma in seperate RAM blocks)
;;//          4 (CALL) + 12 + 12 + 12 + 10 + 5 = 55 (running from RAM, Mc,Mb,Ma in same RAM block)
;;//*****************************************************************************
;; Registers that need saving/restoring if used:
;;  A10-A14, D10-D15, and M26-M31
;;

		.text
		.globl	matrix_mpy_f32_6by6_casm
		.type	matrix_mpy_f32_6by6_casm,@function

		.align	16
matrix_mpy_f32_6by6_casm:
		;    On Entry:
		;    A4 => Ma_f32[0][0] = MA11
		;    A5 => Mb_f32[0][0] = MB11
		;    A6 => Mc_f32[0][0] = MC11
		;-------------------------------------------------------------------------------
		;
		;    MC11 = (MA11 * MB11) + (MA12 * MB21) + (MA13 * MB31) + (MA14 * MB41) + (MA15 * MB51) + (MA16 * MB61);               
		;    MC12 = (MA11 * MB12) + (MA12 * MB22) + (MA13 * MB32) + (MA14 * MB42) + (MA15 * MB52) + (MA16 * MB62);
		;    MC13 = (MA11 * MB13) + (MA12 * MB23) + (MA13 * MB33) + (MA14 * MB43) + (MA15 * MB53) + (MA16 * MB63);
		;    MC14 = (MA11 * MB14) + (MA12 * MB24) + (MA13 * MB34) + (MA14 * MB44) + (MA15 * MB54) + (MA16 * MB64);
		;
		;-----Calculate MC11, MC12, MC13, MC14------------------------------------------
		LD.32		M7,*(A4)		; 16: M7  = MA11            , A4 => MA11
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB11, M1  = MB12, A5 => MB13
		||MV		A7,A4			; A7 => A4 => MA11
		SMPYF		M2,M0,M7		; 16: M2  = MA11 * MB11
		||SMPYF		M3,M1,M7		; 16: M3  = MA11 * MB12
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA11            , A4 => MA12
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB13, M9  = MB14, A5 => MB21
		SMPYF		M10,M8,M15		; 16: M10 = MA11 * MB13
		||SMPYF		M11,M9,M15		; 16: M11 = MA11 * MB14
		||LD.32		M7,*(A4)		; 16: M7  = MA12            , A4 => MA12
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB21, M1  = MB22, A5 => MB23
		SMPYF		M4,M0,M7		; 16: M4  = MA12 * MB21
		||SMPYF		M5,M1,M7		; 16: M5  = MA12 * MB22
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA12            , A4 => MA13
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB23, M9  = MB24, A5 => MB31
		SMPYF		M12,M8,M15		; 16: M12 = MA12 * MB23
		||SMPYF		M13,M9,M15		; 16: M13 = MA12 * MB24
		||LD.32		M7,*(A4)		; 16: M7  = MA13            , A4 => MA13
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB31, M1  = MB32, A5 => MB33
		SMPYF		M2,M0,M7		; 16: M2  = MA13 * MB31
		||SMPYF		M3,M1,M7		; 16: M3  = MA13 * MB32
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA13            , A4 => MA14
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB33, M9  = MB34, A5 => MB41
		SMPYF		M10,M8,M15		; 16: M10 = MA13 * MB33
		||SMPYF		M11,M9,M15		; 16: M11 = MA13 * MB34
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A4)		; 16: M7  = MA14            , A4 => MA14
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB41, M1  = MB42, A5 => MB43
		SMPYF		M2,M0,M7		; 16: M2  = MA14 * MB41
		||SMPYF		M3,M1,M7		; 16: M3  = MA14 * MB42
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA14            , A4 => MA15
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB43, M9  = MB44, A5 => MB51
		SMPYF		M10,M8,M15		; 16: M10 = MA14 * MB43
		||SMPYF		M11,M9,M15		; 16: M11 = MA14 * MB44
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A4)		; 16: M7  = MA15            , A4 => MA15
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB51, M1  = MB52, A5 => MB53
		SMPYF		M2,M0,M7		; 16: M2  = MA15 * MB51
		||SMPYF		M3,M1,M7		; 16: M3  = MA15 * MB52
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA15            , A4 => MA16
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB53, M9  = MB54, A5 => MB61
		SMPYF		M10,M8,M15		; 16: M10 = MA15 * MB53
		||SMPYF		M11,M9,M15		; 16: M11 = MA15 * MB54
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A4)		; 16: M7  = MA16            , A4 => MA15
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB61, M1  = MB62, A5 => MB63
		SMPYF		M2,M0,M7		; 16: M2  = MA16 * MB61
		||SMPYF		M3,M1,M7		; 16: M3  = MA16 * MB62
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA16            , A4 => MA21
		||LD.64		XM8,*(A5--#112)		; 32: M8  = MB63, M9  = MB64, A5 => MB15
		SMPYF		M10,M8,M15		; 16: M10 = MA16 * MB63				|                
		||SMPYF		M11,M9,M15		; 16: M11 = MA16 * MB64				|
		||SADDF		M12,M12,M10		; 16:						|
		||SADDF		M13,M13,M11		; 16:						|
		SADDF		M4,M4,M2		; 16: M4  = MC11				|
		||SADDF		M5,M5,M3		; 16: M5  = MC12				|
		SADDF		M12,M12,M10		; 16: M12 = MC13				|
		||SADDF		M13,M13,M11		; 16: M13 = MC14				|
		ST.64		*(A6++#8),XM4		; 32: Store MC11 & MC12				|
		ST.64		*(A6++#8),XM12		; 32: Store MC13 & MC14				|
		;-------------------------------------------------------------------------------
		;
		;    MC15 = (MA11 * MB15) + (MA12 * MB25) + (MA13 * MB35) + (MA14 * MB45) + (MA15 * MB55) + (MA16 * MB65);
		;    MC16 = (MA11 * MB16) + (MA12 * MB26) + (MA13 * MB36) + (MA14 * MB46) + (MA15 * MB56) + (MA16 * MB66);
		;
		;    MC21 = (MA21 * MB11) + (MA22 * MB21) + (MA23 * MB31) + (MA24 * MB41) + (MA25 * MB51) + (MA26 * MB61);
		;    MC22 = (MA21 * MB12) + (MA22 * MB22) + (MA23 * MB32) + (MA24 * MB42) + (MA25 * MB52) + (MA26 * MB62);
		;
		;-----Calculate MC15, MC16, MC21, MC22-----------------------------------------
		LD.32		M7,*(A7++#4)		; 16: M7  = MA11            , A7 => MA12
		||LD.64		XM0,*(A5--#20)		; 32: M0  = MB15, M1  = MB16, A5 => MB11
		SMPYF		M2,M0,M7		; 16: M2  = MA11 * MB15
		||SMPYF		M3,M1,M7		; 16: M3  = MA11 * MB16
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA21            , A4 => MA22
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB13, M9  = MB14, A5 => MB21
		SMPYF		M10,M8,M15		; 16: M10 = MA11 * MB13
		||SMPYF		M11,M9,M15		; 16: M11 = MA11 * MB14
		||LD.32		M7,*(A7++#4)		; 16: M7  = MA12            , A7 => MA13
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB21, M1  = MB22, A5 => MB23
		SMPYF		M4,M0,M7		; 16: M4  = MA12 * MB21
		||SMPYF		M5,M1,M7		; 16: M5  = MA12 * MB22
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA22            , A4 => MA23
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB23, M9  = MB24, A5 => MB31
		SMPYF		M12,M8,M15		; 16: M12 = MA12 * MB23
		||SMPYF		M13,M9,M15		; 16: M13 = MA12 * MB24
		||LD.32		M7,*(A7++#4)		; 16: M7  = MA13            , A7 => MA14
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB31, M1  = MB32, A5 => MB33
		SMPYF		M2,M0,M7		; 16: M2  = MA13 * MB31
		||SMPYF		M3,M1,M7		; 16: M3  = MA13 * MB32
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA23            , A4 => MA24
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB33, M9  = MB34, A5 => MB41
		SMPYF		M10,M8,M15		; 16: M10 = MA13 * MB33
		||SMPYF		M11,M9,M15		; 16: M11 = MA13 * MB34
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A7++#4)		; 16: M7  = MA14            , A7 => MA15
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB41, M1  = MB42, A5 => MB43
		SMPYF		M2,M0,M7		; 16: M2  = MA14 * MB41
		||SMPYF		M3,M1,M7		; 16: M3  = MA14 * MB42
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA24            , A4 => MA25
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB43, M9  = MB44, A5 => MB51
		SMPYF		M10,M8,M15		; 16: M10 = MA14 * MB43
		||SMPYF		M11,M9,M15		; 16: M11 = MA14 * MB44
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A7++#4)		; 16: M7  = MA15            , A7 => MA16
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB51, M1  = MB52, A5 => MB53
		SMPYF		M2,M0,M7		; 16: M2  = MA15 * MB51
		||SMPYF		M3,M1,M7		; 16: M3  = MA15 * MB52
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA25            , A4 => MA26
		||LD.64		XM8,*(A5++#16)		; 32: M8  = MB53, M9  = MB54, A5 => MB61
		SMPYF		M10,M8,M15		; 16: M10 = MA15 * MB53
		||SMPYF		M11,M9,M15		; 16: M11 = MA15 * MB54
		||SADDF		M12,M12,M10		; 16:
		||SADDF		M13,M13,M11		; 16:
		||LD.32		M7,*(A7++#4)		; 16: M7  = MA16            , A7 => MA21
		||LD.64		XM0,*(A5++#8)		; 32: M0  = MB61, M1  = MB62, A5 => MB63
		SMPYF		M2,M0,M7		; 16: M2  = MA16 * MB61
		||SMPYF		M3,M1,M7		; 16: M3  = MA16 * MB62
		||SADDF		M4,M4,M2		; 16:
		||SADDF		M5,M5,M3		; 16:
		||LD.32		M15,*(A4++#4)		; 16: M15 = MA26            , A4 => MA31
		||LD.64		XM8,*(A5--#112)		; 32: M8  = MB63, M9  = MB64, A5 => MB15
		SMPYF		M10,M8,M15		; 16: M10 = MA16 * MB63				|                
		||SMPYF		M11,M9,M15		; 16: M11 = MA16 * MB64				|
		||SADDF		M12,M12,M10		; 16:						|
		||SADDF		M13,M13,M11		; 16:						|
		SADDF		M4,M4,M2		; 16: M4  = MC11				|
		||SADDF		M5,M5,M3		; 16: M5  = MC12				|
		SADDF		M12,M12,M10		; 16: M12 = MC13				|
		||SADDF		M13,M13,M11		; 16: M13 = MC14				|
		ST.64		*(A6++#8),XM4		; 32: Store MC11 & MC12				|
		ST.64		*(A6++#8),XM12		; 32: Store MC13 & MC14				|
		;-------------------------------------------------------------------------------
		;
		;    MC23 = (MA21 * MB13) + (MA22 * MB23) + (MA23 * MB33) + (MA24 * MB43) + (MA25 * MB53) + (MA26 * MB63);
		;    MC24 = (MA21 * MB14) + (MA22 * MB24) + (MA23 * MB34) + (MA24 * MB44) + (MA25 * MB54) + (MA26 * MB64);
		;    MC25 = (MA21 * MB15) + (MA22 * MB25) + (MA23 * MB35) + (MA24 * MB45) + (MA25 * MB55) + (MA26 * MB65);
		;    MC26 = (MA21 * MB16) + (MA22 * MB26) + (MA23 * MB36) + (MA24 * MB46) + (MA25 * MB56) + (MA26 * MB66);
		;
		;-----Calculate MC23, MC24, MC25, MC26------------------------------------------
		;
		;    MC31 = (MA31 * MB11) + (MA32 * MB21) + (MA33 * MB31) + (MA34 * MB41) + (MA35 * MB51) + (MA36 * MB61);
		;    MC32 = (MA31 * MB12) + (MA32 * MB22) + (MA33 * MB32) + (MA34 * MB42) + (MA35 * MB52) + (MA36 * MB62);
		;    MC33 = (MA31 * MB13) + (MA32 * MB23) + (MA33 * MB33) + (MA34 * MB43) + (MA35 * MB53) + (MA36 * MB63);
		;    MC34 = (MA31 * MB14) + (MA32 * MB24) + (MA33 * MB34) + (MA34 * MB44) + (MA35 * MB54) + (MA36 * MB64);
		;
		;-----Calculate MC31, MC32, MC33, MC34------------------------------------------
		;-------------------------------------------------------------------------------
		;		
		;    MC35 = (MA31 * MB15) + (MA32 * MB25) + (MA33 * MB35) + (MA34 * MB45) + (MA35 * MB55) + (MA36 * MB65);
		;    MC36 = (MA31 * MB16) + (MA32 * MB26) + (MA33 * MB36) + (MA34 * MB46) + (MA35 * MB56) + (MA36 * MB66);
		;
		;    MC41 = (MA41 * MB11) + (MA42 * MB21) + (MA43 * MB31) + (MA44 * MB41) + (MA45 * MB51) + (MA46 * MB61);
		;    MC42 = (MA41 * MB12) + (MA42 * MB22) + (MA43 * MB32) + (MA44 * MB42) + (MA45 * MB52) + (MA46 * MB62);
		;
		;-----Calculate MC35, MC36, MC41, MC42------------------------------------------
		;-------------------------------------------------------------------------------
		;		
		;    MC43 = (MA41 * MB13) + (MA42 * MB23) + (MA43 * MB33) + (MA44 * MB43) + (MA45 * MB53) + (MA46 * MB63);
		;    MC44 = (MA41 * MB14) + (MA42 * MB24) + (MA43 * MB34) + (MA44 * MB44) + (MA45 * MB54) + (MA46 * MB64);
		;    MC45 = (MA41 * MB15) + (MA42 * MB25) + (MA43 * MB35) + (MA44 * MB45) + (MA45 * MB55) + (MA46 * MB65);
		;    MC46 = (MA41 * MB16) + (MA42 * MB26) + (MA43 * MB36) + (MA44 * MB46) + (MA45 * MB56) + (MA46 * MB66);
		;
		;-----Calculate MC43, MC44, MC45, MC46------------------------------------------
		;-------------------------------------------------------------------------------
		;		
		;    MC51 = (MA51 * MB11) + (MA52 * MB21) + (MA53 * MB31) + (MA54 * MB41) + (MA55 * MB51) + (MA56 * MB61);
		;    MC52 = (MA51 * MB12) + (MA52 * MB22) + (MA53 * MB32) + (MA54 * MB42) + (MA55 * MB52) + (MA56 * MB62);
		;    MC53 = (MA51 * MB13) + (MA52 * MB23) + (MA53 * MB33) + (MA54 * MB43) + (MA55 * MB53) + (MA56 * MB63);
		;    MC54 = (MA51 * MB14) + (MA52 * MB24) + (MA53 * MB34) + (MA54 * MB44) + (MA55 * MB54) + (MA56 * MB64);
		;
		;-----Calculate MC51, MC52, MC53, MC54------------------------------------------
		;-------------------------------------------------------------------------------
		;		
		;    MC55 = (MA51 * MB15) + (MA52 * MB25) + (MA53 * MB35) + (MA54 * MB45) + (MA55 * MB55) + (MA56 * MB65);
		;    MC56 = (MA51 * MB16) + (MA52 * MB26) + (MA53 * MB36) + (MA54 * MB46) + (MA55 * MB56) + (MA56 * MB66);
		;
		;    MC61 = (MA61 * MB11) + (MA62 * MB21) + (MA63 * MB31) + (MA64 * MB41) + (MA65 * MB51) + (MA66 * MB61);
		;    MC62 = (MA61 * MB12) + (MA62 * MB22) + (MA63 * MB32) + (MA64 * MB42) + (MA65 * MB52) + (MA66 * MB62);
		;
		;-----Calculate MC55, MC56, MC61, MC62------------------------------------------
		;-------------------------------------------------------------------------------
		;		
		;    MC63 = (MA61 * MB13) + (MA62 * MB23) + (MA63 * MB33) + (MA64 * MB43) + (MA65 * MB53) + (MA66 * MB63);
		;    MC64 = (MA61 * MB14) + (MA62 * MB24) + (MA63 * MB34) + (MA64 * MB44) + (MA65 * MB54) + (MA66 * MB64);
		;    MC65 = (MA61 * MB15) + (MA62 * MB25) + (MA63 * MB35) + (MA64 * MB45) + (MA65 * MB55) + (MA66 * MB65);
		;    MC66 = (MA61 * MB16) + (MA62 * MB26) + (MA63 * MB36) + (MA64 * MB46) + (MA65 * MB56) + (MA66 * MB66);
		;
		;-----Calculate MC63, MC64, MC65, MC66------------------------------------------

;;=============================================================================
;; End of file.
;;=============================================================================
