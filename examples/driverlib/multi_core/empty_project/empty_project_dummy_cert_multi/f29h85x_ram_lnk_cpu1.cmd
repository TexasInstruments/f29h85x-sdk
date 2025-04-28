--entry_point="code_start"

/* Specify the system memory map */

MEMORY
{
    /*
     *  RAM
     */
    SRAM_LDAx   : origin = 0x200E0000, length = 0x008000
    SRAM_LPA0   : origin = 0x20100000, length = 0x008000
    /*
     *  CPU2 and CPU3 load and run memories
     */
    CPU2_LPAX   : origin = 0x20108000, length = 0x008000
    CPU3_CPAX   : origin = 0x20110000, length = 0x008000
}


/* Specify the sections allocation into memory */

SECTIONS
{
    codestart   : {} > SRAM_LPA0,        palign(8)
    .text       : {} > SRAM_LPA0,        palign(8)
    .binit      : {} > SRAM_LPA0,        palign(8)
    .cinit      : {} > SRAM_LPA0,        palign(8)
    .const      : {} > SRAM_LPA0,        palign(8)
    .rodata     : {} > SRAM_LPA0,        palign(8)
    .init_array : {} > SRAM_LPA0,        palign(8)
    .TI.ramfunc : {} > SRAM_LPA0,        palign(8)

    cpu2app     : {} > CPU2_LPAX,   palign(8)
    cpu3app     : {} > CPU3_CPAX,   palign(8)

    .data       : {} > SRAM_LDAx
    .bss        : {} > SRAM_LDAx
    .stack      : {} > SRAM_LDAx
    .sysmem     : {} > SRAM_LDAx
    .cio        : {} > SRAM_LDAx
}
