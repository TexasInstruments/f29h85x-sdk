
SECTIONS
{
#if defined (_FLASH)
    .delayFunc :> FLASH_RP0
                    LOAD_START(delayFuncStart),
                    LOAD_END(delayFuncEnd)
#else
    .delayFunc :> SRAM_LPAx
                    LOAD_START(delayFuncStart),
                    LOAD_END(delayFuncEnd)
#endif
}
