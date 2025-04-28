--entry_point="code_start"

/* Specify the system memory map */

MEMORY
{
    /*
     *  RAM
     */
    SRAM_LDAx       : o=0x200E0000, l=0x008000
    SRAM_LPAx       : o=0x20108000, l=0x5000
    /*
     *  FLASH
     */

    FLASH_RP0       : o=0x10020000, l=0x00F000

}


/* Specify the sections allocation into memory */

SECTIONS
{
    codestart       : {} > 0x10020000,  palign(8)
    .text           : {} > FLASH_RP0,   palign(8)
    .binit          : {} > FLASH_RP0,   palign(8)
    .cinit          : {} > FLASH_RP0,   palign(8)
    .const          : {} > FLASH_RP0,   palign(8)
    .rodata         : {} > FLASH_RP0,   palign(8)
    .init_array     : {} > FLASH_RP0,   palign(8)
    .TI.ramfunc     : {} LOAD=FLASH_RP0, RUN=SRAM_LPAx, table(BINIT), palign(8)


    .data           : {} > SRAM_LPAx
    .bss            : {} > SRAM_LPAx
    .stack          : {} > SRAM_LPAx
    .sysmem         : {} > SRAM_LPAx
    .cio            : {} > SRAM_LPAx
}