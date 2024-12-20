
SECTIONS
{
#if defined (_FLASH)
    .func1 :> FLASH_RP0
                    LOAD_START(func1Start),
                    LOAD_END(func1End)
    .func2 :> FLASH_RP0
            LOAD_START(func2Start),
            LOAD_END(func2End)
    .func3 :> FLASH_RP0
                LOAD_START(func3Start),
                LOAD_END(func3End)
#else
    .func1 :> SRAM_LPAx
                    LOAD_START(func1Start),
                    LOAD_END(func1End)
    .func2 :> SRAM_LPAx
                LOAD_START(func2Start),
                LOAD_END(func2End)
    .func3 :> SRAM_LPAx
                LOAD_START(func3Start),
                LOAD_END(func3End)
#endif
}
