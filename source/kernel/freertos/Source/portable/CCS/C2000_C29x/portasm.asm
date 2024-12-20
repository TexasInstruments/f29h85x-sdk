    .extern pxCurrentTCB
    .extern bYield
    .extern bPreemptive
    .extern ulCriticalNesting
    .extern xTaskIncrementTick
    .extern vTaskSwitchContext
    .extern ulTaskHasFPUContext

    .global portTICK_ISR
    .global portRESTORE_FIRST_CONTEXT
    .global vPortYield
    .global profile1_start, profile1_end, profile2_start, profile2_end


    .macro portSAVE_CONTEXT
        ST.32 *(A15++#8), A14
        || MV A14, RPC
        ST.32 *(A15-#4), A14
        ST.32 *(A15++#8), DSTS
        ST.32 *(A15-#4), ESTS
        ST.64 *(A15++#8), XA0
        ST.64 *(A15++#8), XA2
        ST.64 *(A15++#8), XA4
        ST.64 *(A15++#8), XA6
        ST.64 *(A15++#8), XA8
        ST.64 *(A15++#8), XA10
        ST.64 *(A15++#8), XA12
        ST.64 *(A15++#8), XD0
        ST.64 *(A15++#8), XD2
        ST.64 *(A15++#8), XD4
        ST.64 *(A15++#8), XD6
        
        ;Check if task has FPU context
        || LD.32	 D0, @ulTaskHasFPUContext

        ST.64 *(A15++#8), XD8
        || BCMPZD  .+0x54, D.EQ, D0
        ST.64 *(A15++#8), XD10
        ST.64 *(A15++#8), XD12
        ST.64 *(A15++#8), XD14

        ST.64 *(A15++#8), XM0
        ST.64 *(A15++#8), XM2
        ST.64 *(A15++#8), XM4
        ST.64 *(A15++#8), XM6
        ST.64 *(A15++#8), XM8
        ST.64 *(A15++#8), XM10
        ST.64 *(A15++#8), XM12
        ST.64 *(A15++#8), XM14
        ST.64 *(A15++#8), XM16
        ST.64 *(A15++#8), XM18
        ST.64 *(A15++#8), XM20
        ST.64 *(A15++#8), XM22
        ST.64 *(A15++#8), XM24
        ST.64 *(A15++#8), XM26
        ST.64 *(A15++#8), XM28
        ST.64 *(A15++#8), XM30

        ; Store FPU context indicator
        ST.32 *(A15++#8), D0 
        ; Store the new top of stack for the task.
        || LD.32	A14, @pxCurrentTCB
        ST.32	*A14, A15
    .endm

    .macro portRESTORE_CONTEXT
        LD.32 A0, @pxCurrentTCB
        LD.32 A15, *A0

        ;Check if task has FPU context
        LD.32	 D0, *(A15-=#8)
        ST.32 @ulTaskHasFPUContext, D0
        || BCMPZ  .+0x4a, D.EQ, D0

        LD.64 XM30, *(A15-=#8)
        LD.64 XM28, *(A15-=#8)
        LD.64 XM26, *(A15-=#8)
        LD.64 XM24, *(A15-=#8)
        LD.64 XM22, *(A15-=#8)
        LD.64 XM20, *(A15-=#8)
        LD.64 XM18, *(A15-=#8)
        LD.64 XM16, *(A15-=#8)
        LD.64 XM14, *(A15-=#8)
        LD.64 XM12, *(A15-=#8)
        LD.64 XM10, *(A15-=#8)
        LD.64 XM8,  *(A15-=#8)
        LD.64 XM6,  *(A15-=#8)
        LD.64 XM4,  *(A15-=#8)
        LD.64 XM2,  *(A15-=#8)
        LD.64 XM0,  *(A15-=#8)
        
        LD.64 XD14, *(A15-=#8)
        LD.64 XD12, *(A15-=#8)
        LD.64 XD10, *(A15-=#8)
        LD.64 XD8,  *(A15-=#8)
        LD.64 XD6,  *(A15-=#8)
        LD.64 XD4,  *(A15-=#8)
        LD.64 XD2,  *(A15-=#8)
        LD.64 XD0,  *(A15-=#8)
        LD.64 XA12, *(A15-=#8)
        LD.64 XA10, *(A15-=#8)
        LD.64 XA8,  *(A15-=#8)
        LD.64 XA6,  *(A15-=#8)
        LD.64 XA4,  *(A15-=#8)
        LD.64 XA2,  *(A15-=#8)
        LD.64 XA0,  *(A15-=#8)
        LD.32 DSTS, *(A15-=#8)
        LD.32 ESTS, *(A15+#4)
        LD.32 A14,  *(A15-=#8)
        LD.32 RPC,  *(A15+#4)

    .endm

portTICK_ISR:
profile1_start:
	; Save the context of the current task.
    portSAVE_CONTEXT
profile1_end:

    ;ENINT

    ; Increment tick counter
    CALL     xTaskIncrementTick
    BCMPZ    skipTaskSwitchContext, D.EQ, D0
    CALL     @vTaskSwitchContext

skipTaskSwitchContext:
profile2_start:
    ; Restore the context of the task selected to execute.
    portRESTORE_CONTEXT
profile2_end:

    RETI.INT


vPortYield:
	; Save the context of the current task.
    portSAVE_CONTEXT

    ;ENINT

    ; Select the next task to execute.
    CALL      @vTaskSwitchContext

    ; Restore the context of the task selected to execute.
    portRESTORE_CONTEXT
    RETI.INT


portRESTORE_FIRST_CONTEXT:
    portRESTORE_CONTEXT
    RET