    .global WRAP_myCPUTIMER0_ISR
    .global WRAP_mySPI0_RX_ISR
    .global WRAP_INT_SW11_ISR
    .global WRAP_INT_SW12_ISR
    .global commonIsrSwitcher

    .macro PRE_COMMON_ISR_CALL
        ST.64	*(ADDR1)(A15++#8), XD0
    .endm

    .macro COMMON_ISR_CALL_THEN_RETURN
        CALL	@commonIsrSwitcher
        SUB.U16	A15,A15,#0x8
        RETI.INT
    .endm

WRAP_myCPUTIMER0_ISR:
    PRE_COMMON_ISR_CALL

    ; INDEX = 0
    MV      D0, #0x00000000
    COMMON_ISR_CALL_THEN_RETURN

WRAP_mySPI0_RX_ISR:
    PRE_COMMON_ISR_CALL

    ; INDEX = 1
    MV      D0, #0x00000001
    COMMON_ISR_CALL_THEN_RETURN

WRAP_INT_SW11_ISR:
    PRE_COMMON_ISR_CALL

    ; INDEX = 2
    MV      D0, #0x00000002
    COMMON_ISR_CALL_THEN_RETURN

WRAP_INT_SW12_ISR:
    PRE_COMMON_ISR_CALL

    ; INDEX = 3
    MV      D0, #0x00000003
    COMMON_ISR_CALL_THEN_RETURN

commonIsrSwitcher:
    ; Save context
    ST.32   *(ADDR1)(A15++#8), ESTS
    ST.64   *(ADDR1)(A15++#8), XM24
    ST.64   *(ADDR1)(A15++#8), XM22
    ST.64   *(ADDR1)(A15++#8), XM20
    ST.64   *(ADDR1)(A15++#8), XM18
    ST.64   *(ADDR1)(A15++#8), XM16
    ST.64   *(ADDR1)(A15++#8), XM14
    ST.64   *(ADDR1)(A15++#8), XM12
    ST.64   *(ADDR1)(A15++#8), XM10
    ST.64   *(ADDR1)(A15++#8), XM8
    ST.64   *(ADDR1)(A15++#8), XM6
    ST.64   *(ADDR1)(A15++#8), XM4
    ST.64   *(ADDR1)(A15++#8), XM2
    ST.64   *(ADDR1)(A15++#8), XM0
    ST.64   *(ADDR1)(A15++#8), XD8
    ST.64   *(ADDR1)(A15++#8), XD6
    ST.64   *(ADDR1)(A15++#8), XD4
    ST.64   *(ADDR1)(A15++#8), XD2
    ST.64   *(ADDR1)(A15++#8), XA8
    ST.64   *(ADDR1)(A15++#8), XA6
    ST.64   *(ADDR1)(A15++#8), XA4
    ST.64   *(ADDR1)(A15++#8), XA2
    ST.64   *(ADDR1)(A15++#8), XA0

    ; Nest and switch stack if required
    ; Fetch address of service routine
    MV      A1, D0
    || LD.32	D1, @intNestingLevel
    CMP.S16	TDM0, D.NEQ, D1, #0x0
    BC	    .+0x14, TDM0.NZ
    MV      A3, #lastTaskStackPtr
    ST.32   *A3, A15
    MV      A15, #isrStack
    LSL	    A1, A1, #0x2
    || MV      A2, @isrArray
    LD.32	A4, *(ADDR1)(A2 + A1)
    || LD.32	D0, @intNestingLevel
    ADD.U16	D0, D0, #0x1
    ST.32	@intNestingLevel, D0

    ; Call actual service routine code
    ENINT
    CALL	A4
    DISINT

    ; Unnest
    LD.32	D0, @intNestingLevel
    SUB.U16	D0, D0, #0x1
    CMP.S16	TDM0, D.NEQ, D0, #0x0
    ST.32	@intNestingLevel, D0
    BC	    .+0xA, TDM0.NZ
    LD.32	A15, @lastTaskStackPtr

    ; Restore context
    LD.64   XA0,	*(ADDR1)(A15-=#8)
    LD.64   XA2,	*(ADDR1)(A15-=#8)
    LD.64   XA4,	*(ADDR1)(A15-=#8)
    LD.64   XA6,	*(ADDR1)(A15-=#8)
    LD.64   XA8,	*(ADDR1)(A15-=#8)
    LD.64   XD2,	*(ADDR1)(A15-=#8)
    LD.64   XD4,	*(ADDR1)(A15-=#8)
    LD.64   XD6,	*(ADDR1)(A15-=#8)
    LD.64   XD8,	*(ADDR1)(A15-=#8)
    LD.64   XM0,	*(ADDR1)(A15-=#8)
    LD.64   XM2,	*(ADDR1)(A15-=#8)
    LD.64   XM4,	*(ADDR1)(A15-=#8)
    LD.64   XM6,	*(ADDR1)(A15-=#8)
    LD.64   XM8,	*(ADDR1)(A15-=#8)
    LD.64   XM10,	*(ADDR1)(A15-=#8)
    LD.64   XM12,	*(ADDR1)(A15-=#8)
    LD.64   XM14,	*(ADDR1)(A15-=#8)
    LD.64   XM16,	*(ADDR1)(A15-=#8)
    LD.64   XM18,	*(ADDR1)(A15-=#8)
    LD.64   XM20,	*(ADDR1)(A15-=#8)
    LD.64   XM22,	*(ADDR1)(A15-=#8)
    LD.64   XM24,	*(ADDR1)(A15-=#8)
    LD.32   ESTS,	*(ADDR1)(A15-=#8)
    LD.64   XD0,	*(ADDR1)(A15-#8)

    RET
