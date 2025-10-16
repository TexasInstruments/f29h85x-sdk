--entry_point="code_start"
--retain="cmdTableEntryAddr"

/* Application firmware entry address, must be the same as SBL's APP1_ENTRY address */
#define APP1_ENTRY      0x10018000
/* Address for SBL's command jump table, must be the same as SBL's CMDTABLE_ENTRY address */
#define CMDTABLE_ENTRY  0x10002000

/* Specify the system memory map */
MEMORY
{

    /* LDA1/0 reserved by SBL */
    SRAM_LDAx       : o=0x200E0000, l=0x18000
    SRAM_LPAx       : o=0x20100000, l=0x10000
    SRAM_CPAx       : o=0x20110000, l=0x10000
    /* CDA10/11 reserved by SBL */
    SRAM_CDAx       : o=0x20120000, l=0x28000

    // Bankmode 1
    CPU1_FLASH_APP  : o=APP1_ENTRY, l=0x1E8000

    /*
    // Bankmode 3
    CPU1_FLASH_APP  : o=APP1_ENTRY, l=0x0E8000
    CPU3_FLASH_APP  : o=0x10400000, l=0x100000
    */
}


/* Specify the sections allocation into memory */
SECTIONS
{   
    /* Refer to the macro comments above on entry address restrictions  */
    codestart       : {} > APP1_ENTRY,       palign(8)
    command_table   : {} > CMDTABLE_ENTRY,   type=DSECT, START(cmdTableEntryAddr) /* A dummy section to output cmdTableEntryAddr used by the application */
    cert            : {} > 0x0,              type=DSECT /* Discard cert section as it is located in SBL and part of SBL post-build steps */

    .text           : {} > CPU1_FLASH_APP,   palign(8)
    .binit          : {} > CPU1_FLASH_APP,   palign(8)
    .cinit          : {} > CPU1_FLASH_APP,   palign(8)
    .const          : {} > CPU1_FLASH_APP,   palign(8)
    .rodata         : {} > CPU1_FLASH_APP,   palign(8)
    .init_array     : {} > CPU1_FLASH_APP,   palign(8)
    .TI.ramfunc     : {} LOAD=CPU1_FLASH_APP, RUN=SRAM_LPAx, table(BINIT), palign(8)

    .data           : {} > SRAM_LDAx
    .bss            : {} > SRAM_LDAx
    .stack          : {} > SRAM_LDAx
    .sysmem         : {} > SRAM_LDAx
    .cio            : {} > SRAM_LDAx
}