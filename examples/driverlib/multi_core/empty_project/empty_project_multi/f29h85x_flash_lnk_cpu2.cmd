--entry_point="code_start"
--retain="reset_vector"
--retain="nmi_vector"

/* Specify the system memory map */

MEMORY
{
    /*
     *  RAM
     */
    SRAM_LDAx    	: origin = 0x200E8000, length = 0x08000
    SRAM_LPA1       : origin = 0x20108000, length = 0x08000
}


/* Specify the sections allocation into memory */

SECTIONS
{
    resetvector     : {} > 0x20108000,  palign(8)
    nmivector       : {} > 0x20108040,  palign(8)
    codestart       : {} > SRAM_LPA1,   palign(8)
    .text           : {} > SRAM_LPA1,   palign(8)
    .cinit          : {} > SRAM_LPA1,   palign(8)
    .const          : {} > SRAM_LPA1,   palign(8)
    .rodata         : {} > SRAM_LPA1,   palign(8)
    .init_array     : {} > SRAM_LPA1,   palign(8)
    .TI.ramfunc     : {} > SRAM_LPA1,   palign(8)

    .data           : {} > SRAM_LDAx
    .bss            : {} > SRAM_LDAx
    .stack          : {} > SRAM_LDAx
    .sysmem         : {} > SRAM_LDAx
    .cio            : {} > SRAM_LDAx
}
