--entry_point="code_start"


/* Specify the system memory map */

MEMORY
{
    SRAM_LDAx_LOADABLE      : o=0x200FC000, l=0x2000                /* Address range 0x200E0000 - 0x200FC000 is reserved for HSM */
    SRAM_LDAx               : o=0x200FE000, l=0x2000                   
    APPL_ENTRY              : o=0x20100000, l=0x000040
    SRAM_LPAx_RAM           : o=0x20100040, l=0x0300
    SRAM_LPAx               : o=0x20100340, l=0x00FBC0
    SRAM_LDAX_CPAx_MIRROR   : o=0x20110000, l=0x2000
    SRAM_CPAx_LOADABLE      : o=0x20112000, l=0xE000
    SRAM_CDAx               : o=0x20120000, l=0x30000

    FLASH_RP0               : o=0x10000000, l=0x100000
    FLASH_RP1               : o=0x10100000, l=0x100000
    FLASH_RP2               : o=0x10200000, l=0x100000
    FLASH_RP3               : o=0x10300000, l=0x100000
    MAILBOX_R5F             : o=0x302C0800, l=0x000007FF
    MAILBOX_HSM             : o=0x302C1000, l=0x000007FF
}



/* Specify the sections allocation into memory */

SECTIONS
{
    codestart     : {} > APPL_ENTRY

    .TI.ramfunc   : {} > SRAM_LPAx_RAM
    .hsmlib       : {*(.text.Hsm*) *(.text.SIPC*)} RUN=SRAM_LDAx_LOADABLE, LOAD=SRAM_LDAX_CPAx_MIRROR, LOAD_START(__CPAX_START), RUN_START(__LDAX_START), RUN_END(__LDAX_END)
    .text         : {} > SRAM_LPAx
    .cinit        : {} > SRAM_LPAx
    .const        : {} > SRAM_CPAx_LOADABLE
    .rodata       : {} > SRAM_CPAx_LOADABLE
    .init_array   : {} > SRAM_CPAx_LOADABLE

    .data         : {} > SRAM_CPAx_LOADABLE
    .bss          : {} > SRAM_CDAx
    .stack        : {} > SRAM_LDAx
    .sysmem       : {} > SRAM_CDAx
    .cio          : {} > SRAM_CDAx

    .bss.sipc_hsm_queue_mem   (NOLOAD) : {} > MAILBOX_HSM
    .bss.sipc_secure_host_queue_mem   (NOLOAD) : {} > MAILBOX_R5F

}