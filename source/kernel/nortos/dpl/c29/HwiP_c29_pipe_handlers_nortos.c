//#############################################################################
//
//   FILE:  HwiP_c29_pipe_handlers_nortos.c
//
//   TITLE: 
//
//#############################################################################
//  $ Copyright: $
//#############################################################################

#include <kernel/dpl/HwiP.h>
#include <kernel/nortos/dpl/c29/HwiP_c29_pipe.h>

void __attribute__((interrupt("INT"), section(".text.hwi"))) HwiP_int_handler(void)
{
    uint8_t intPriority;
    int32_t status;

    status = HwiP_getIntPriority(&intPriority);
    if(status==SystemP_SUCCESS)
    {
        HwiP_FxnCallback isr;
        void *args;
        isr = gHwiCtrl.isr[intPriority];
        args = gHwiCtrl.isrArgs[intPriority];
        if(isr!=NULL)
        {
            isr(args);
        }
    }
    else
    {
        gHwiCtrl.spuriousINTCount++;
    }
}

void __attribute__((interrupt("INT"), section(".text.hwi"))) HwiP_default_handler(void)
{
    volatile uint32_t loop = 1;
    while(loop!=0U)
    {
        ;
    }
}

