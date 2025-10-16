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
}


/* Specify the sections allocation into memory */

SECTIONS
{
    resetvector   : {} > 0x20110000,    palign(8)
    nmivector     : {} > 0x20110040,    palign(8)
    codestart     : {} > SRAM_CPA0,     palign(8)
    .text         : {} > SRAM_CPA0,     palign(8)
    .binit        : {} > SRAM_CPA0,     palign(8)
    .cinit        : {} > SRAM_CPA0,     palign(8)
    .const        : {} > SRAM_CPA0,     palign(8)
    .rodata       : {} > SRAM_CPA0,     palign(8)
    .init_array   : {} > SRAM_CPA0,     palign(8)

    .data         : {} > SRAM_CDAx
    .bss          : {} > SRAM_CDAx
    .stack        : {} > SRAM_CDAx
    .sysmem       : {} > SRAM_CDAx
    .cio          : {} > SRAM_CDAx
}
