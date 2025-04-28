--entry_point="code_start"

/* Specify the system memory map */

MEMORY
{
    /*
     *  RAM
     */
    SRAM_LDAx       : o=0x200E0000, l=0x008000
    SRAM_LPA0       : o=0x20100000, l=0x008000
    /*
     *  FLASH
     */
    CERT            : o=0x10000000, l=0x001000
    FLASH_RP0       : o=0x10001000, l=0x0FF000
    /*
     *  CPU2 and CPU3 load and run memories
     */
    CPU2_SRAM_LPA1  : o=0x20108000, l=0x008000
    CPU2_FLASH_RP0  : o=0x10100000, l=0x008000
    CPU3_FLASH_RP0  : o=0x10400000, l=0x100000
}


/* Specify the sections allocation into memory */

SECTIONS
{
    codestart       : {} > 0x10001000,  palign(8)
    cert            : {} > CERT,        palign(8)
    .text           : {} > FLASH_RP0,   palign(8)
    .binit          : {} > FLASH_RP0,   palign(8)
    .cinit          : {} > FLASH_RP0,   palign(8)
    .const          : {} > FLASH_RP0,   palign(8)
    .rodata         : {} > FLASH_RP0,   palign(8)
    .init_array     : {} > FLASH_RP0,   palign(8)
    .TI.ramfunc     : {} LOAD=FLASH_RP0, RUN=SRAM_LPA0, table(BINIT), palign(8)

    cpu2app         : {} LOAD=CPU2_FLASH_RP0, RUN=CPU2_SRAM_LPA1, table(BINIT), palign(8)
    cpu3app         : {} > CPU3_FLASH_RP0,    palign(8)

    .data           : {} > SRAM_LDAx
    .bss            : {} > SRAM_LDAx
    .stack          : {} > SRAM_LDAx
    .sysmem         : {} > SRAM_LDAx
    .cio            : {} > SRAM_LDAx
}