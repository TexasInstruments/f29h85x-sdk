--entry_point="code_start"

/* Specify the system memory map */

MEMORY
{
    /*
     *  RAM
     */
    SRAM_LDAx   : origin = 0x200E0000, length = 0x008000
    SRAM_LPAx   : origin = 0x20100000, length = 0x10000
    /*
     *  CPU3 load and run memories
     */
    CPU3_CPAX   : origin = 0x20110000, length = 0x008000
}


/* Specify the sections allocation into memory */

SECTIONS
{
    codestart   : {} > SRAM_LPAx,   palign(8)
    .text       : {} > SRAM_LPAx,   palign(8)
    .binit      : {} > SRAM_LPAx,   palign(8)
    .cinit      : {} > SRAM_LPAx,   palign(8)
    .const      : {} > SRAM_LPAx,   palign(8)
    .rodata     : {} > SRAM_LPAx,   palign(8)
    .init_array : {} > SRAM_LPAx,   palign(8)
    .TI.ramfunc : {} > SRAM_LPAx,   palign(8)

    cpu3app     : {} > CPU3_CPAX,   palign(8)

    .data       : {} > SRAM_LDAx
    .bss        : {} > SRAM_LDAx
    .stack      : {} > SRAM_LDAx
    .sysmem     : {} > SRAM_LDAx
    .cio        : {} > SRAM_LDAx
}
