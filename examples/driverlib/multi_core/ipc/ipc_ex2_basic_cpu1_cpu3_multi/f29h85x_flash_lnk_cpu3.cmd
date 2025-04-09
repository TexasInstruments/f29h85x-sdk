--entry_point="code_start"
--retain="reset_vector"
--retain="nmi_vector"

/* Specify the system memory map */

MEMORY
{
    /*
     *  RAM
     */
    SRAM_CPA0 : o=0x20110000, l=0x008000
    SRAM_CDAx : o=0x20120000, l=0x008000

    CERT : o=0x10400000, l=0x1000
    FLASH_RP0 : o=0x10401000, l=0xFF000
}


/* Specify the sections allocation into memory */

SECTIONS
{
    cert          : {} > CERT,          palign(8)
    resetvector   : {} > 0x10401000,    palign(8)
    nmivector     : {} > 0x10401040,    palign(8)
    codestart     : {} > FLASH_RP0,     palign(8)
    .text         : {} > FLASH_RP0,     palign(8)
    .binit        : {} > FLASH_RP0,     palign(8)
    .cinit        : {} > FLASH_RP0,     palign(8)
    .const        : {} > FLASH_RP0,     palign(8)
    .rodata       : {} > FLASH_RP0,     palign(8)
    .init_array   : {} > FLASH_RP0,     palign(8)
    .TI.ramfunc   : {} LOAD=FLASH_RP0, RUN=SRAM_CPA0, table(BINIT),     palign(8)

    .data         : {} > SRAM_CDAx
    .bss          : {} > SRAM_CDAx
    .stack        : {} > SRAM_CDAx
    .sysmem       : {} > SRAM_CDAx
    .cio          : {} > SRAM_CDAx
}
