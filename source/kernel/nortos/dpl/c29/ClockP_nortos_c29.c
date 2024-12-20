//#############################################################################
//
//   FILE:  ClockP_nortos_c29.c
//
//   TITLE:
//
//#############################################################################
//  $ Copyright: $
//#############################################################################

#include <kernel/nortos/dpl/common/ClockP_nortos_priv.h>
#include <kernel/dpl/TimerP.h>

void ClockP_init(void);
void ClockP_timerClearOverflowInt(uint32_t timerBaseAddr);
uint32_t ClockP_getTimerCount(uint32_t timerBaseAddr);

void ClockP_timerClearOverflowInt(uint32_t timerBaseAddr)
{
    TimerP_clearOverflowInt(timerBaseAddr);
}

uint32_t ClockP_getTimerCount(uint32_t timerBaseAddr)
{
    return TimerP_getCount(timerBaseAddr);
}

void ClockP_init(void)
{
    TimerP_Params timerParams;
    HwiP_Params timerHwiParams;

    /* These MUST not be 0 */
    DebugP_assert(gClockConfig.timerInputPreScaler != 0U);
    DebugP_assert(gClockConfig.timerInputClkHz != 0U);
    DebugP_assert(gClockConfig.usecPerTick != 0U);
    DebugP_assert(gClockConfig.timerBaseAddr != 0U);

    /* init internal data structure */
    gClockCtrl.ticks = 0;
    gClockCtrl.list = NULL;
    gClockCtrl.usecPerTick = gClockConfig.usecPerTick;
    gClockCtrl.timerBaseAddr = gClockConfig.timerBaseAddr;

    /* setup timer but dont start it */
    TimerP_Params_init(&timerParams);
    timerParams.inputPreScaler    = gClockConfig.timerInputPreScaler;
    timerParams.inputClkHz        = gClockConfig.timerInputClkHz;
    timerParams.periodInUsec      = gClockConfig.usecPerTick;
    timerParams.oneshotMode       = 0;
    timerParams.enableOverflowInt = 1;
    TimerP_setup(gClockCtrl.timerBaseAddr, &timerParams);

    /* Get timer reload count, we will use this later to compute current time in usecs */
    gClockCtrl.timerReloadCount = TimerP_getReloadCount(gClockCtrl.timerBaseAddr);

    /* setup ISR and enable it */
    HwiP_Params_init(&timerHwiParams);
    timerHwiParams.intNum = gClockConfig.timerHwiIntNum;
    timerHwiParams.linkOwner = gClockConfig.timerHwiLinkOwner;
    timerHwiParams.callback = ClockP_timerTickIsr;
    (void) HwiP_construct(&gClockCtrl.timerHwiObj, &timerHwiParams);

    /* start the tick timer */
    TimerP_start(gClockCtrl.timerBaseAddr);
}

