//#############################################################################
//
//   FILE:  HwiP_c29_pipe.c
//
//   TITLE: Driver porting layer (DPL): Hardware Interrupts
//
//#############################################################################
//  $ Copyright: $
//#############################################################################

#include "kernel/dpl/HwiP.h"
#include "HwiP_c29_pipe.h"

static volatile uint32_t gdummy;

typedef struct HwiP_Struct_s {

    uint32_t intNum;
    uint8_t  priority;
    uint8_t  isRTINT;

} HwiP_Struct;

HwiP_Ctrl gHwiCtrl;



//*****************************************************************************
//
// HwiP_Params_init
//
//*****************************************************************************
void HWI_SECTION HwiP_Params_init(HwiP_Params *params)
{
    params->intNum = 0;
    params->callback = NULL;
    params->args = NULL;
    params->priority = (HwiP_MAX_PRIORITY-1U);
    params->isRTINT = 0;
    params->rtintHandler = NULL;
    params->linkOwner = SSU_LINK2;
}

//*****************************************************************************
//
// HwiP_construct
//
//*****************************************************************************
int32_t HWI_SECTION HwiP_construct(HwiP_Object *handle, HwiP_Params *params)
{
    HwiP_Struct *obj = (HwiP_Struct *)handle;

#if defined(DEBUG)
    DebugP_assertNoLog( sizeof(HwiP_Struct) <= sizeof(HwiP_Object) );
    DebugP_assertNoLog( params->intNum < HwiP_MAX_INTERRUPTS );
#endif

    int32_t status = SystemP_SUCCESS;

    //
    // For RTINT:
    // - User must provide a interrupt ISR
    //   a callback function is not used. If it is supplied, it is
    //   ignored.
    // - User must provide a priority - however it does not have to be
    //   unique. This is because hardware will use the intNum
    //   as a second priority
    //
    Interrupt_disable(params->intNum);
    Interrupt_clearFlag(params->intNum);
    Interrupt_clearOverflowFlag(params->intNum);
    Interrupt_setPriority(params->intNum, params->priority);
    Interrupt_setLinkOwner(params->intNum, params->linkOwner);
    if(params->isRTINT != 0U)
    {
#if defined(DEBUG)
        DebugP_assertNoLog( params->rtintHandler != NULL );
#endif
        Interrupt_register(params->intNum, params->rtintHandler);
    }
    else
    {
        //
        // For INT:
        // - The generic HwiP int handler will be registered in the PIPE
        //   vector table
        // - User must provide a callback function which will be called
        //   by the HwiP int handler
        // - User must provide a unique priority.
        //   - The priority is used to determine which callback to
        //     use. (intNum is not available to software)
        //   - If the priority has already been used, then an error
        //     will be returned.
        //
#if defined(DEBUG)
        DebugP_assertNoLog( params->callback != NULL );
        DebugP_assertNoLog( gHwiCtrl.isr[params->priority] == NULL);
#endif

        Interrupt_register(params->intNum, &HwiP_int_handler);
        if(gHwiCtrl.isr[params->priority] == NULL)
        {
            gHwiCtrl.isr[params->priority] = params->callback;
            gHwiCtrl.isrArgs[params->priority] = params->args;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    obj->intNum = params->intNum;
    obj->priority = params->priority;
    obj->isRTINT = params->isRTINT;
    if(status == SystemP_SUCCESS) Interrupt_enable(params->intNum);
    return(status);
}


//*****************************************************************************
//
// HwiP_setArgs
//
//*****************************************************************************
int32_t HwiP_setArgs(HwiP_Object *handle, void *args)
{
    HwiP_Struct *obj = (HwiP_Struct *)handle;

    gHwiCtrl.isrArgs[obj->priority] = args;

    return SystemP_SUCCESS;
}

//*****************************************************************************
//
// HwiP_destruct
//
//*****************************************************************************
void HWI_SECTION HwiP_destruct(HwiP_Object *handle)
{
    HwiP_Struct *obj = (HwiP_Struct *)handle;

    //
    // disable interrupt, clear pending if any, lowest priority
    //
    Interrupt_disable(obj->intNum);
    Interrupt_clearFlag(obj->intNum);
    Interrupt_clearOverflowFlag(obj->intNum);
    Interrupt_setPriority(obj->intNum, HwiP_MAX_PRIORITY-1U);

    if(obj->isRTINT == 1)
    {
        //
        // For RTINT, set PIPE vector to the default handler
        //
        Interrupt_unregister(obj->intNum);
    }
    else
    {
        //
        // For INT, clear the interrupt structure
        // based on the priority of the interrupt
        //
        gHwiCtrl.isr[obj->priority] = NULL;
        gHwiCtrl.isrArgs[obj->priority] = NULL;
    }
}


//*****************************************************************************
//
// HwiP_init
//
//*****************************************************************************
void HWI_SECTION HwiP_init(void)
{
    //
    // Standard initialization for the PIPE (driverlib)
    // - Reset RTINT_THRESHOLD: all interrupts are INT
    // - Reset GRP_MASK: all interrupts can nest
    // - Reset LOCK, COMMIT, TASK registers
    // - Clear all flags (ALL_FLAG_CLEAR)
    // - Disable INT and RTINT (GLOBAL_EN) to CPU
    // - Disable all interrupt lines (INT_CTL_L registers)
    // - Reset all vector address mapping (INT_VECT_ADDR)
    // - Clear PIPE diagnostic data
    // - Populate the entire vector table with the default handler
    //   provided in driverlib
    //
    Interrupt_initModule();
    Interrupt_initVectorTable();

    uint32_t i;
    for (i = 0; i < HwiP_MAX_INTERRUPTS; i++)
    {
        gHwiCtrl.isr[i]= NULL;
        gHwiCtrl.isrArgs[i]= NULL;
    }
    gHwiCtrl.spuriousINTCount = 0;

}

//*****************************************************************************
//
// HwiP_getIntPriority
//
//*****************************************************************************
int32_t HWI_SECTION HwiP_getIntPriority(uint8_t *intPriority)
{
    uint8_t temp;
    int32_t status;
    temp = HwiP_inISR();
    if(temp == HWIP_IN_ISR_INT)
    {
       *intPriority = ( (HWREG(PIPE_BASE + PIPE_O_CPU_INT_STS)                 \
                        & PIPE_CPU_INT_STS_LAST_INT_PRIOLVL_M)                 \
                       >> PIPE_CPU_INT_STS_LAST_INT_PRIOLVL_S);
       status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return(status);
}

//*****************************************************************************
//
// HwiP_enableInt
//
//*****************************************************************************
void HWI_SECTION HwiP_enableInt(uint32_t intNum)
{
    Interrupt_enable(intNum);
}

//*****************************************************************************
//
// HwiP_disableInt
//
//*****************************************************************************
uint32_t HWI_SECTION HwiP_disableInt(uint32_t intNum)
{
    uint32_t isEnable = 0;

    isEnable = HWREGB(PIPE_BASE + PIPE_O_INT_CTL_L(intNum)) & PIPE_INT_CTL_L_EN;
    Interrupt_disable(intNum);

    return isEnable;
}

//*****************************************************************************
//
// HwiP_restoreInt
//
//*****************************************************************************
void HWI_SECTION HwiP_restoreInt(uint32_t intNum, uint32_t oldIntState)
{
    if(oldIntState!=0U)
    {
        HwiP_enableInt(intNum);
    }
    else
    {
       (void)HwiP_disableInt(intNum);
    }
}

//*****************************************************************************
//
// HwiP_clearInt
//
//*****************************************************************************
void HWI_SECTION HwiP_clearInt(uint32_t intNum)
{
    Interrupt_clearFlag(intNum);
    Interrupt_clearOverflowFlag(intNum);
    return;
}

//*****************************************************************************
//
// HwiP_post
//
//*****************************************************************************
void HWI_SECTION HwiP_post(uint32_t intNum)
{
    Interrupt_force(intNum);
    return;
}

//*****************************************************************************
//
// HwiP_disable
//
//*****************************************************************************
uintptr_t HWI_SECTION HwiP_disable(void)
{
    uint32_t isEnable = 0;
    isEnable = HWREG(PIPE_BASE + PIPE_O_GLOBAL_EN) & PIPE_GLOBAL_EN_ENABLE_M;
    Interrupt_disableGlobal();
    return(isEnable);
}

//*****************************************************************************
//
// HwiP_enable
//
//*****************************************************************************
void HWI_SECTION HwiP_enable(void)
{
    Interrupt_enableGlobal();
    return;
}

//*****************************************************************************
//
// HwiP_restore
//
//*****************************************************************************
void HWI_SECTION HwiP_restore(uintptr_t oldIntState)
{
    if(oldIntState!=0U)
    {
        Interrupt_enableGlobal();
    }
    else
    {
        Interrupt_disableGlobal();
    }
    return;
}

//*****************************************************************************
//
// HwiP_setINTSP
//
//*****************************************************************************
void HWI_SECTION HwiP_setINTSP(uint8_t intsp)
{
    Interrupt_setINTSP((SSU_Stack)intsp);
}
