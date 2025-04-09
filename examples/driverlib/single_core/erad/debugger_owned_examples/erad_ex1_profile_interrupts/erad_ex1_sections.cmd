
SECTIONS
{
#if defined (_FLASH)
    .funcToProfile :> FLASH_RP0
                    LOAD_START(funcStart),
                    LOAD_END(funcEnd)
#else
    .funcToProfile :> SRAM_LPAx
                    LOAD_START(funcStart),
                    LOAD_END(funcEnd)
#endif
}
